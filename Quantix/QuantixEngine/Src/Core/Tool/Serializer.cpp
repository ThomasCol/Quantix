#include "Core/Tool/Serializer.h"

#include <fstream>

#include "Core/Components/Rigidbody.h"
#include "Core/Components/CubeCollider.h"
#include "Core/Components/SphereCollider.h"
#include "Core/Components/Behaviours/CubeGenerator.h"
#include "Core/Components/DeformableMesh.h"

namespace Quantix::Core::Tool
{
	QXbool Serializer::Deserialize(const QXstring& path, Resources::Scene* scene, DataStructure::ResourcesManager* manager)
	{
		std::ifstream stream(path, std::ios::ate);
		if (!stream.is_open())
			return false;

		QXsizei file_size = (QXsizei)stream.tellg();
		QXstring data(file_size, ' ');

		stream.seekg(0);
		stream.read(&data[0], file_size);
		stream.close();

		data[file_size] = '\0';

		rapidjson::Document doc;
		if (doc.Parse(data).HasParseError())
			return false;

		rapidjson::Value::MemberIterator ret = doc.FindMember("Scene");
		scene->Rename(ret->value.FindMember("name")->value.GetString());

		_currScene = scene;

		rapidjson::Value& root = ret->value.FindMember("GameObject0")->value;
		rapidjson::Value& childs = root.FindMember("Childs")->value;
		for (QXint i = 0; i < (QXint)childs.Size(); ++i)
		{
			DeserializeRecursive(scene, i, childs[i], nullptr, manager);
		}

		scene->SetReady(true);

		return true;
	}

	QXstring Serializer::Serialize(Resources::Scene* scene)
	{
		rapidjson::StringBuffer sb;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
		writer.StartObject();
		writer.String("Scene");
		writer.StartObject();
		writer.String("name");
		writer.String(scene->GetName().c_str());

		SerializeRecursive(scene->GetRoot()->GetTransform(), 0, writer);

		writer.EndObject();
		writer.EndObject();

		return sb.GetString();
	}

	void Serializer::DeserializeRecursive(Resources::Scene* scene, QXint index, rapidjson::Value& val, DataStructure::GameObject3D* parent, DataStructure::ResourcesManager* manager)
	{
		rapidjson::Value::MemberIterator ret = val.FindMember("GameObject" + std::to_string(index));

		if (ret == val.MemberEnd())
			return;

		rapidjson::Value& cur_val = ret->value;
		QXstring	name = cur_val.FindMember("name")->value.GetString();
		DataStructure::GameObject3D* object = scene->AddGameObject(name, parent);

		DataStructure::Layer layer = (DataStructure::Layer)cur_val.FindMember("layer")->value.GetUint();
		object->SetLayer(layer);

		ReadTransform(object->GetTransform(), cur_val.FindMember("Transform")->value);

		rapidjson::Value& components = cur_val.FindMember("Components")->value;
		for (rapidjson::SizeType i = 0; i < components.Size(); ++i)
			ReadComponent(object, components[i], manager);

		rapidjson::Value& childs = cur_val.FindMember("Childs")->value;
		for (QXint i = 0; i < (QXint)childs.Size(); ++i)
			DeserializeRecursive(scene, i, childs[i], object, manager);
	}

	void Serializer::ReadComponent(DataStructure::GameObject3D* object, rapidjson::Value& val, DataStructure::ResourcesManager* manager)
	{
		rttr::array_range componentsAvailable = rttr::type::get<Quantix::Core::DataStructure::Component>().get_derived_classes();
		rapidjson::Value& val2 = val.GetObject().MemberBegin()[0].value;
		for (auto it : componentsAvailable)
		{
			if (it.get_name() == val.GetObject().MemberBegin()[0].name.GetString())
			{
				object->AddComponent(it.invoke("Copy", it.create(), {}).get_value<Quantix::Core::DataStructure::Component*>());
				Quantix::Core::DataStructure::Component* comp = object->GetComponents().back();
				comp->Init(object);
				rttr::type type = comp->get_type();
				if (type == rttr::type::get<Gameplay::CubeGenerator>() || type.get_raw_type() == rttr::type::get<Gameplay::CubeGenerator>())
				{
					type.invoke("SetSceneAndResourcesManager", comp, { _currScene, manager });
				}
				else if (type == rttr::type::get<Core::Components::DeformableMesh>() || type.get_raw_type() == rttr::type::get<Core::Components::DeformableMesh>())
				{
					type.invoke("Generate", comp, {_currScene, manager});
				}
				for (QXsizei i = 0; i < val2.MemberCount(); ++i)
				{
					for (auto it = type.get_properties().begin(); it != type.get_properties().end(); ++it)
					{
						if ((*it).get_name() == val2.MemberBegin()[i].name.GetString())
							ReadInstance(comp, (*it).get_type(), (*it), val2.MemberBegin()[i].value, manager);
					}
				}
			}
		}
	}

	void Serializer::ReadInstance(rttr::instance inst, rttr::type type, rttr::property currentProp, rapidjson::Value& value, DataStructure::ResourcesManager* manager)
	{
		if (type == rttr::type::get<QXbool>())
		{
			QXbool tesGrandMort = value.GetBool();
			currentProp.set_value(inst, value.GetBool());
		}
		else if (type == rttr::type::get<QXfloat>())
		{
			currentProp.set_value(inst, value.GetFloat());
		}
		else if (type == rttr::type::get<QXdouble>())
		{
			currentProp.set_value(inst, value.GetDouble());
		}
		else if (type == rttr::type::get<QXint>())
		{
			currentProp.set_value(inst, value.GetInt());
		}
		else if (type == rttr::type::get<QXuint32>())
		{
			currentProp.set_value(inst, value.GetUint());
		}
		else if (type == rttr::type::get<QXsizei>())
		{
			currentProp.set_value(inst, value.GetUint64());
		}
		else if (type == rttr::type::get<QXstring>())
		{
			currentProp.set_value(inst, value.GetString());
		}
		else if (currentProp.is_enumeration())
		{
			currentProp.set_value(inst, currentProp.get_enumeration().name_to_value(value.GetString()));
		}
		else if (type == rttr::type::get<Math::QXvec3>())
		{
			Math::QXvec3 vec = ReadVec3(value);
			currentProp.set_value(inst, ReadVec3(value));
		}
		else if (type == rttr::type::get<Math::QXquaternion>())
		{
			currentProp.set_value(inst, ReadQuat(value));
		}
		else if (type.is_class() || (type.is_pointer() && type.get_raw_type().is_class()))
		{
			if (type == rttr::type::get<Resources::Material*>() || type.get_raw_type() == rttr::type::get<Resources::Material*>())
			{
				currentProp.set_value(inst, manager->CreateMaterial(value.GetString()));
				return;
			}
			else if (type == rttr::type::get<Resources::Model*>() || type.get_raw_type() == rttr::type::get<Resources::Model*>())
			{
				currentProp.set_value(inst, manager->CreateModel(value.GetString()));
				return;
			}
			else if (type == rttr::type::get<Resources::Sound*>() || type.get_raw_type() == rttr::type::get<Resources::Sound*>())
			{
				currentProp.set_value(inst, manager->CreateSound(value.GetString()));
				return;
			}
			
			for (QXsizei i = 0; i < value.MemberCount(); ++i)
			{
				for (auto it = type.get_properties().begin(); it != type.get_properties().end(); ++it)
				{
					if ((*it).get_name() == value.MemberBegin()[0].name.GetString())
						ReadInstance(currentProp.get_value(inst), (*it).get_type(), (*it), value.MemberBegin()[0].value, manager);
				}
			}
		}
	}

	void Serializer::WriteTransform(Physic::Transform3D* transform, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
	{
		writer.String("Transform");
		writer.StartObject();
		WriteVec3("position", transform->GetPosition(), writer);
		WriteQuat("rotation", transform->GetRotation(), writer);
		WriteVec3("scale", transform->GetScale(), writer);
		writer.EndObject();
	}

	void Serializer::WriteVec3(const QXstring& name, const Math::QXvec3& vec, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
	{
		writer.String(name);
		writer.StartObject();
		writer.String("x");
		writer.Double(vec.x);
		writer.String("y");
		writer.Double(vec.y);
		writer.String("z");
		writer.Double(vec.z);
		writer.EndObject();
	}

	void Serializer::WriteQuat(const QXstring& name, Math::QXquaternion& quat, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
	{
		writer.String(name);
		writer.StartObject();
		writer.String("x");
		writer.Double(quat.v.x);
		writer.String("y");
		writer.Double(quat.v.y);
		writer.String("z");
		writer.Double(quat.v.z);
		writer.String("w");
		writer.Double(quat.w);
		writer.EndObject();
	}

	void Serializer::SerializeRecursive(Physic::Transform3D* transform, QXint index, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
	{
		writer.String("GameObject" + std::to_string(index));
		writer.StartObject();
		writer.String("name");
		writer.String(transform->GetObject()->GetName());
		writer.String("layer");
		writer.Uint((QXuint)transform->GetObject()->GetLayer());
		WriteTransform(transform, writer);

		QXbool is_deformable = false;

		writer.String("Components");
		writer.StartArray();
		for (QXsizei i = 0; i < transform->GetObject()->GetComponents().size(); ++i)
		{
			writer.StartObject();
			auto comp = transform->GetObject()->GetComponents()[i];
			if (comp->get_type().get_name() == "DeformableMesh")
				is_deformable = true;
			if (transform->GetObject()->GetComponents()[i] != nullptr)
			{
				rttr::type t = transform->GetObject()->GetComponents()[i]->get_type();
				WriteComponent(comp, t, writer);
			}
			writer.EndObject();
		}
		writer.EndArray();

		if (is_deformable)
			return;

		writer.String("Childs");
		writer.StartArray();
		QXuint idx = 0;
		for (auto it = transform->GetChilds().begin(); it != transform->GetChilds().end(); ++it)
		{
			writer.StartObject();
			SerializeRecursive((*it), idx, writer);
			writer.EndObject();
			idx++;
		}
		writer.EndArray();
		writer.EndObject();
	}

	void Serializer::WriteComponent(rttr::instance comp, rttr::type type, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
	{
		QXstring name;
		if (type.is_pointer())
		{
			name = type.get_name().to_string();
			name.pop_back();
		}
		else
			name = type.get_name().to_string();

		QXint index = 0;
		writer.String(name);
		writer.StartObject();
		for (auto it = type.get_properties().begin(); it != type.get_properties().end(); ++it)
		{
			rttr::property currentProp = *(it);

			rttr::type t = currentProp.get_type();
			WriteInstance(comp, currentProp, t, writer);
			index++;
		}
		writer.EndObject();
	}

	void Serializer::WriteInstance(rttr::instance inst, rttr::property currentProp, rttr::type type,
		rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
	{
		if (type == rttr::type::get<QXbool>())
		{
			writer.String(currentProp.get_name().to_string());
			writer.Bool(currentProp.get_value(inst).to_bool());
		}
		else if (type == rttr::type::get<QXfloat>())
		{
			writer.String(currentProp.get_name().to_string());
			writer.Double(currentProp.get_value(inst).to_double());
		}
		else if (type == rttr::type::get<QXdouble>())
		{
			writer.String(currentProp.get_name().to_string());
			writer.Double(currentProp.get_value(inst).to_double());
		}
		else if (type == rttr::type::get<QXint>())
		{
			writer.String(currentProp.get_name().to_string());
			writer.Int(currentProp.get_value(inst).to_int());
		}
		else if (type == rttr::type::get<QXuint32>())
		{
			writer.String(currentProp.get_name().to_string());
			writer.Int(currentProp.get_value(inst).to_uint32());
		}
		else if (type == rttr::type::get<QXsizei>())
		{
			writer.String(currentProp.get_name().to_string());
			writer.Uint(currentProp.get_value(inst).to_uint32());
		}
		else if (type == rttr::type::get<QXstring>())
		{
			writer.String(currentProp.get_name().to_string());
			writer.String(currentProp.get_value(inst).to_string());
		}
		else if (currentProp.is_enumeration())
		{
			writer.String(currentProp.get_name().to_string());
			writer.String(currentProp.get_enumeration().value_to_name(currentProp.get_value(inst)).to_string());
		}
		else if (type == rttr::type::get<Math::QXvec3>())
		{
			WriteVec3(currentProp.get_name().to_string(), currentProp.get_value(inst).get_value<Math::QXvec3>(), writer);
		}
		else if (type == rttr::type::get<Math::QXquaternion>())
		{
			WriteQuat(currentProp.get_name().to_string(), currentProp.get_value(inst).get_value<Math::QXquaternion>(), writer);
		}
		else if (currentProp.get_type().is_class() || (currentProp.get_type().is_pointer() && currentProp.get_type().get_raw_type().is_class()))
		{
			if (currentProp.get_type() == rttr::type::get<Resources::Material>() || currentProp.get_type().get_raw_type() == rttr::type::get<Resources::Material>() ||
				currentProp.get_type() == rttr::type::get<Resources::Model>() || currentProp.get_type().get_raw_type() == rttr::type::get<Resources::Model>() ||
				currentProp.get_type() == rttr::type::get<Resources::Sound>() || currentProp.get_type().get_raw_type() == rttr::type::get<Resources::Sound>())
			{
				QXstring str = currentProp.get_type().invoke("GetPath", currentProp.get_value(inst), {}).get_value<QXstring>();
				writer.String(currentProp.get_name().to_string());
				writer.String(str);
				return;
			}
			WriteComponent(currentProp.get_value(inst), type, writer);
		}
	}

	void Serializer::ReadTransform(Physic::Transform3D* transform, rapidjson::Value& val)
	{
		transform->SetPosition(ReadVec3(val.FindMember("position")->value));

		transform->SetRotation(ReadQuat(val.FindMember("rotation")->value));

		transform->SetScale(ReadVec3(val.FindMember("scale")->value));
	}

	Math::QXvec3 Serializer::ReadVec3(rapidjson::Value& val)
	{
		Math::QXvec3 vec;
		vec.x = (QXfloat)val.FindMember("x")->value.GetDouble();
		vec.y = (QXfloat)val.FindMember("y")->value.GetDouble();
		vec.z = (QXfloat)val.FindMember("z")->value.GetDouble();

		return vec;
	}

	Math::QXquaternion Serializer::ReadQuat(rapidjson::Value& val)
	{
		Math::QXquaternion quat;
		quat.v.x = (QXfloat)val.FindMember("x")->value.GetDouble();
		quat.v.y = (QXfloat)val.FindMember("y")->value.GetDouble();
		quat.v.z = (QXfloat)val.FindMember("z")->value.GetDouble();
		quat.w = (QXfloat)val.FindMember("w")->value.GetDouble();

		return quat;
	}
}
