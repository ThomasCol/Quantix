#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/prettywriter.h> // for stringify JSON
#include <rapidjson/document.h>     // rapidjson's DOM-style API

#include "Resources/Scene.h"

namespace Quantix::Core::Tool
{
	class QUANTIX_API Serializer
	{
	private:
		#pragma region Functions

		void DeserializeRecursive(Resources::Scene* scene, QXint index, rapidjson::Value& val, DataStructure::GameObject3D* parent,
			DataStructure::ResourcesManager* manager);

		void ReadComponent(DataStructure::GameObject3D* object, rapidjson::Value& val, DataStructure::ResourcesManager* manager);

		void ReadInstance(rttr::instance inst, rttr::type type, rttr::property currentProp, rapidjson::Value& value, DataStructure::ResourcesManager* manager);

		void ReadTransform(Physic::Transform3D* transform, rapidjson::Value& val);

		Math::QXvec3 ReadVec3(rapidjson::Value& val);

		Math::QXquaternion ReadQuat(rapidjson::Value& val);

		void SerializeRecursive(Physic::Transform3D* transform, QXint index, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);

		void WriteComponent(rttr::instance comp, rttr::type type, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);

		void WriteInstance(rttr::instance inst, rttr::property currentProp, rttr::type type,
			rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);

		void WriteTransform(Physic::Transform3D* transform, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);

		void WriteVec3(const QXstring& name, const Math::QXvec3& vec, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);

		void WriteQuat(const QXstring& name, Math::QXquaternion& quat, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);

		#pragma endregion

	public:
		#pragma region Constructors

		Serializer() = default;
		Serializer(const Serializer& serializer) = default;
		Serializer(Serializer&& serilizer) = default;

		~Serializer() = default;

		#pragma endregion

		#pragma region Functions

		QXbool		Deserialize(const QXstring& path, Resources::Scene* scene, DataStructure::ResourcesManager* manager);

		QXstring	Serialize(Resources::Scene* scene);

		#pragma endregion
	};
}

#endif //__SERIALIZER_H__
