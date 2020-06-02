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
		#pragma region Attributes

		Resources::Scene* _currScene;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Deserialize recursively all objects
		 * 
		 * @param scene Scene to fill
		 * @param index index of the object
		 * @param val Current value in JSON
		 * @param parent Parent of the object
		 * @param manager Resources manager to unit some components
		 */
		void DeserializeRecursive(Resources::Scene* scene, QXint index, rapidjson::Value& val, DataStructure::GameObject3D* parent,
			DataStructure::ResourcesManager* manager) noexcept;

		/**
		 * @brief Read a component
		 * 
		 * @param object Game object to fill
		 * @param val value to read
		 * @param manager Manager to init some components
		 */
		void ReadComponent(DataStructure::GameObject3D* object, rapidjson::Value& val, DataStructure::ResourcesManager* manager) noexcept;

		/**
		 * @brief Read an instance
		 * 
		 * @param inst Instance to fill
		 * @param type type of the propertie
		 * @param currentProp current property value
		 * @param value value to read
		 * @param manager Manager to init some components
		 */
		void ReadInstance(rttr::instance inst, rttr::type type, rttr::property currentProp, rapidjson::Value& value, DataStructure::ResourcesManager* manager) noexcept;

		void ReadTransform(Physic::Transform3D* transform, rapidjson::Value& val) noexcept;

		Math::QXvec3 ReadVec3(rapidjson::Value& val) noexcept;

		Math::QXquaternion ReadQuat(rapidjson::Value& val) noexcept;

		void SerializeRecursive(Physic::Transform3D* transform, QXint index, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) noexcept;

		void WriteComponent(rttr::instance comp, rttr::type type, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) noexcept;

		void WriteInstance(rttr::instance inst, rttr::property currentProp, rttr::type type,
			rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) noexcept;

		void WriteTransform(Physic::Transform3D* transform, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) noexcept;

		void WriteVec3(const QXstring& name, const Math::QXvec3& vec, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) noexcept;

		void WriteQuat(const QXstring& name, Math::QXquaternion& quat, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) noexcept;

		#pragma endregion

	public:
		#pragma region Constructors

		Serializer() = default;
		Serializer(const Serializer& serializer) = default;
		Serializer(Serializer&& serilizer) = default;

		~Serializer() = default;

		#pragma endregion

		#pragma region Functions

		QXbool		Deserialize(const QXstring& path, Resources::Scene* scene, DataStructure::ResourcesManager* manager) noexcept;

		QXstring	Serialize(Resources::Scene* scene) noexcept;

		#pragma endregion
	};
}

#endif //__SERIALIZER_H__
