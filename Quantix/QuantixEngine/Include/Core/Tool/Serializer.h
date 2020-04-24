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

		void WriteTransform(Physic::Transform3D* transform, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);

		void WriteVec3(const QXstring& name, const Math::QXvec3& vec, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);

		void SerializeRecursive(Physic::Transform3D* transform, QXint index, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);

		void WriteComponent(rttr::instance comp, rttr::type type, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);

		void WriteInstance(rttr::instance inst, rttr::property currentProp, rttr::type type,
			rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);

		void DeserializeRecursive(Resources::Scene* scene, QXint index, rapidjson::Value& val, const QXstring& parentName, DataStructure::ResourcesManager& manager);

		void ReadComponent(DataStructure::GameObject3D* object, rapidjson::Value& val, DataStructure::ResourcesManager& manager);

		void ReadTransform(Physic::Transform3D* transform, rapidjson::Value& val);

		void ReadVec3(Math::QXvec3& vec, rapidjson::Value& val);

	public:
		Serializer() = default;
		~Serializer() = default;

		QXstring	Serialize(Resources::Scene* scene);

		QXbool		Deserialize(const QXstring& path, Resources::Scene* scene, DataStructure::ResourcesManager& manager);
	};
}

#endif //__SERIALIZER_H__