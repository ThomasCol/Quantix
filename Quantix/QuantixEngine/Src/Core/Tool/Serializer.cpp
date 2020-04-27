#include "Core/Tool/Serializer.h"

#include "Core/DataStructure/GameObject3D.h"
#include "Core/DataStructure/ResourcesManager.h"

#include <fstream>

namespace Quantix::Core::Tool
{
	QXbool Serializer::Deserialize(const QXstring& path, Resources::Scene* scene, DataStructure::ResourcesManager& manager)
	{
		//std::ifstream stream(path);
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


		rapidjson::Value& root = ret->value.FindMember("GameObject0")->value;
		rapidjson::Value& childs = root.FindMember("Childs")->value;
		for (QXsizei i = 0; i < childs.Size(); ++i)
		{
			DeserializeRecursive(scene, i, childs[i], nullptr, manager);
		}

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

	void Serializer::DeserializeRecursive(Resources::Scene* scene, QXint index, rapidjson::Value& val, DataStructure::GameObject3D* parent, DataStructure::ResourcesManager& manager)
	{
		rapidjson::Value::MemberIterator ret = val.FindMember("GameObject" + std::to_string(index));

		if (ret == val.MemberEnd())
			return;

		rapidjson::Value& cur_val = ret->value;
		QXstring	name = cur_val.FindMember("name")->value.GetString();
		DataStructure::GameObject3D* object = scene->AddGameObject(name, parent);

		ReadTransform(object->GetTransform(), cur_val.FindMember("Transform")->value);

		rapidjson::Value& components = cur_val.FindMember("Components")->value;
		for (QXsizei i = 0; i < components.Size(); ++i)
			ReadComponent(object, components[i], manager);

		rapidjson::Value& childs = cur_val.FindMember("Childs")->value;
		for (QXsizei i = 0; i < childs.Size(); ++i)
			DeserializeRecursive(scene, i, childs[i], object, manager);
	}

	void Serializer::ReadCamera(Components::Camera* camera, rapidjson::Value& val)
	{
		Math::QXvec3 vec;
		ReadVec3(vec, val.FindMember("Pos")->value);
		camera->SetPos(vec);
		ReadVec3(vec, val.FindMember("Up")->value);
		camera->SetUp(vec);
		ReadVec3(vec, val.FindMember("Dir")->value);
		camera->SetDir(vec);
	}

	void Serializer::ReadComponent(DataStructure::GameObject3D* object, rapidjson::Value& val, DataStructure::ResourcesManager& manager)
	{
		rapidjson::Value::MemberIterator ret = val.FindMember("Mesh");
		if (ret != val.MemberEnd())
		{
			Components::Mesh* mesh = object->AddComponent<Components::Mesh>();
			ReadMesh(mesh, ret->value, manager);
		}
		ret = val.FindMember("Light");
		if (ret != val.MemberEnd())
		{
			Components::Light* light = object->AddComponent<Components::Light>();
			ReadLight(light, ret->value);
		}
		ret = val.FindMember("Camera");
		if (ret != val.MemberEnd())
		{
			Components::Camera* camera = object->AddComponent<Components::Camera>();
			ReadCamera(camera, ret->value);
		}
	}

	void Serializer::ReadLight(Components::Light* light, rapidjson::Value& val)
	{
		ReadVec3(light->direction, val.FindMember("direction")->value);
		ReadVec3(light->position, val.FindMember("position")->value);
		ReadVec3(light->ambient, val.FindMember("ambient")->value);
		ReadVec3(light->diffuse, val.FindMember("diffuse")->value);
		ReadVec3(light->specular, val.FindMember("specular")->value);
		light->constant = val.FindMember("constant")->value.GetFloat();
		light->linear = val.FindMember("linear")->value.GetFloat();
		light->quadratic = val.FindMember("quadratic")->value.GetFloat();
		light->cutOff = val.FindMember("cutOff")->value.GetFloat();
		light->outerCutOff = val.FindMember("outerCutOff")->value.GetFloat();
		light->type = (Components::ELightType)val.FindMember("type")->value.GetInt();
	}

	void Serializer::ReadMesh(Components::Mesh* mesh, rapidjson::Value& val, DataStructure::ResourcesManager& manager)
	{
		mesh->SetActive(val.FindMember("Enable")->value.GetBool());
		manager.CreateMesh(mesh, val.FindMember("Model")->value.GetString(), val.FindMember("Material")->value.GetString());
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
		WriteTransform(transform, writer);

		writer.String("Components");
		writer.StartArray();
		writer.StartObject();
		for (QXsizei i = 0; i < transform->GetObject()->GetComponents().size(); ++i)
		{
			auto comp = transform->GetObject()->GetComponents()[i];
			if (transform->GetObject()->GetComponents()[i] != nullptr)
			{
				rttr::type t = transform->GetObject()->GetComponents()[i]->get_type();
				WriteComponent(comp, t, writer);
			}
		}
		writer.EndObject();
		writer.EndArray();

		writer.String("Childs");
		writer.StartArray();
		for (QXsizei i = 0; i < transform->GetChilds().size(); ++i)
		{
			writer.StartObject();
			SerializeRecursive(transform->GetChilds()[i], i, writer);
			writer.EndObject();
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
			writer.Uint(currentProp.get_value(inst).to_uint64());
		}
		else if (type == rttr::type::get<QXstring>())
		{
			writer.String(currentProp.get_name().to_string());
			writer.String(currentProp.get_value(inst).to_string());
		}
		else if (type == rttr::type::get<Components::ELightType>())
		{
			writer.String(currentProp.get_name().to_string());
			writer.Int(currentProp.get_value(inst).to_int());
		}
		else if (type == rttr::type::get<Math::QXvec3>())
		{
			WriteVec3(currentProp.get_name().to_string(), currentProp.get_value(inst).get_value<Math::QXvec3>(), writer);
		}
		else if (currentProp.get_type().is_class() || (currentProp.get_type().is_pointer() && currentProp.get_type().get_raw_type().is_class()))
		{
			if (currentProp.get_type() == rttr::type::get<Resources::Material>() || currentProp.get_type().get_raw_type() == rttr::type::get<Resources::Material>() ||
				currentProp.get_type() == rttr::type::get<Resources::Model>() || currentProp.get_type().get_raw_type() == rttr::type::get<Resources::Model>())
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
		Math::QXvec3 vec;
		Math::QXquaternion quat;
		ReadVec3(vec, val.FindMember("position")->value);
		transform->SetPosition(vec);

		ReadQuat(quat, val.FindMember("rotation")->value);
		transform->SetRotation(quat);

		ReadVec3(vec, val.FindMember("scale")->value);
		transform->SetScale(vec);
	}

	void Serializer::ReadVec3(Math::QXvec3& vec, rapidjson::Value& val)
	{
		vec.x = (QXfloat)val.FindMember("x")->value.GetDouble();
		vec.y = (QXfloat)val.FindMember("y")->value.GetDouble();
		vec.z = (QXfloat)val.FindMember("z")->value.GetDouble();
	}

	void Serializer::ReadQuat(Math::QXquaternion& quat, rapidjson::Value& val)
	{
		quat.v.x = (QXfloat)val.FindMember("x")->value.GetDouble();
		quat.v.y = (QXfloat)val.FindMember("y")->value.GetDouble();
		quat.v.z = (QXfloat)val.FindMember("z")->value.GetDouble();
		quat.w = (QXfloat)val.FindMember("w")->value.GetDouble();
	}
}