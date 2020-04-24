#include "Core/Tool/Serializer.h"

#include "Core/DataStructure/GameObject3D.h"
#include "Core/DataStructure/ResourcesManager.h"

#include <fstream>

namespace Quantix::Core::Tool
{
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
			DeserializeRecursive(scene, i, childs[i], "", manager);
		}

		return true;
	}

	void Serializer::WriteTransform(Physic::Transform3D* transform, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
	{
		writer.String("Transform");
		writer.StartObject();
		WriteVec3("position", transform->GetPosition(), writer);
		WriteVec3("rotation", transform->GetRotation(), writer);
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
		writer.StartObject();
		for (QXsizei i = 0; i < transform->GetChilds().size(); ++i)
			SerializeRecursive(transform->GetChilds()[i], i, writer);
		writer.EndObject();
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

	void Serializer::DeserializeRecursive(Resources::Scene* scene, QXint index, rapidjson::Value& val, const QXstring& parentName, DataStructure::ResourcesManager& manager)
	{
		rapidjson::Value::MemberIterator ret = val.FindMember("GameObject" + std::to_string(index));

		if (ret == val.MemberEnd())
			return;

		rapidjson::Value& cur_val = ret->value;
		QXstring	name = cur_val.FindMember("name")->value.GetString();
		DataStructure::GameObject3D* object = scene->AddGameObject(name, parentName);

		ReadTransform(object->GetTransform(), cur_val.FindMember("Transform")->value);

		rapidjson::Value& components = cur_val.FindMember("Components")->value;
		for (QXsizei i = 0; i < components.Size(); ++i)
			ReadComponent(object, components[i], manager);

		rapidjson::Value& childs = cur_val.FindMember("Childs")->value;
		for (QXsizei i = 0; i < childs.Size(); ++i)
			DeserializeRecursive(scene, i, childs[i], name, manager);
	}

	void Serializer::ReadTransform(Physic::Transform3D* transform, rapidjson::Value& val)
	{
		Math::QXvec3 vec;
		ReadVec3(vec, val.FindMember("position")->value);
		transform->SetPosition(vec);

		ReadVec3(vec, val.FindMember("rotation")->value);
		transform->SetRotation(vec);

		ReadVec3(vec, val.FindMember("scale")->value);
		transform->SetScale(vec);
	}

	void Serializer::ReadVec3(Math::QXvec3& vec, rapidjson::Value& val)
	{
		vec.x = (QXfloat)val.FindMember("x")->value.GetDouble();
		vec.y = (QXfloat)val.FindMember("y")->value.GetDouble();
		vec.z = (QXfloat)val.FindMember("z")->value.GetDouble();
	}

	void Serializer::ReadComponent(DataStructure::GameObject3D* object, rapidjson::Value& val, DataStructure::ResourcesManager& manager)
	{
		rapidjson::Value::MemberIterator ret = val.FindMember("Mesh");
		if (ret != val.MemberEnd())
		{
			Components::Mesh* mesh = object->AddComponent<Components::Mesh>();
			mesh->SetActive(ret->value.FindMember("Enable")->value.GetBool());
			manager.CreateMesh(mesh, ret->value.FindMember("Model")->value.GetString(), ret->value.FindMember("Material")->value.GetString());
			mesh->key = ret->value.FindMember("Key")->value.GetUint();
		}
		ret = val.FindMember("Light");
		if (ret != val.MemberEnd())
		{
			Components::Light* light = object->AddComponent<Components::Light>();
			ReadVec3(light->direction, ret->value.FindMember("direction")->value);
			ReadVec3(light->position, ret->value.FindMember("position")->value);
			ReadVec3(light->ambient, ret->value.FindMember("ambient")->value);
			ReadVec3(light->diffuse, ret->value.FindMember("diffuse")->value);
			ReadVec3(light->specular, ret->value.FindMember("specular")->value);
			light->constant = ret->value.FindMember("constant")->value.GetFloat();
			light->linear = ret->value.FindMember("linear")->value.GetFloat();
			light->quadratic = ret->value.FindMember("quadratic")->value.GetFloat();
			light->cutOff = ret->value.FindMember("cutOff")->value.GetFloat();
			light->outerCutOff = ret->value.FindMember("outerCutOff")->value.GetFloat();
			light->type = (Components::ELightType)ret->value.FindMember("type")->value.GetInt();
		}
		ret = val.FindMember("Light");
		if (ret != val.MemberEnd())
		{
			Components::Light* light = object->AddComponent<Components::Light>();
			ReadVec3(light->direction, ret->value.FindMember("direction")->value);
			ReadVec3(light->position, ret->value.FindMember("position")->value);
			ReadVec3(light->ambient, ret->value.FindMember("ambient")->value);
			ReadVec3(light->diffuse, ret->value.FindMember("diffuse")->value);
			ReadVec3(light->specular, ret->value.FindMember("specular")->value);
			light->constant = ret->value.FindMember("constant")->value.GetFloat();
			light->linear = ret->value.FindMember("linear")->value.GetFloat();
			light->quadratic = ret->value.FindMember("quadratic")->value.GetFloat();
			light->cutOff = ret->value.FindMember("cutOff")->value.GetFloat();
			light->outerCutOff = ret->value.FindMember("outerCutOff")->value.GetFloat();
			light->type = (Components::ELightType)ret->value.FindMember("type")->value.GetInt();
		}
		ret = val.FindMember("Camera");
		if (ret != val.MemberEnd())
		{
			Components::Camera* camera = object->AddComponent<Components::Camera>();
			Math::QXvec3 vec;
			ReadVec3(vec, ret->value.FindMember("Pos")->value);
			camera->SetPos(vec);
			ReadVec3(vec, ret->value.FindMember("Up")->value);
			camera->SetUp(vec);
			ReadVec3(vec, ret->value.FindMember("Dir")->value);
			camera->SetDir(vec);
		}
	}
}