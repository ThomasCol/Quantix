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

		Resources::Scene*	_currScene;

		void*				_lastObj;

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

		/**
		 * @brief Read a trasform object
		 * 
		 * @param transform Transform to fill
		 * @param val Value to read
		 */
		void ReadTransform(Physic::Transform3D* transform, rapidjson::Value& val) noexcept;

		/**
		 * @brief Read a vec3 object
		 * 
		 * @param val Value to read
		 * @return Math::QXvec3 Readed vec3
		 */
		Math::QXvec3 ReadVec3(rapidjson::Value& val) noexcept;

		/**
		 * @brief Read a quaternion object
		 * 
		 * @param val Value to read
		 * @return Math::QXquaternion Readed quaternion
		 */
		Math::QXquaternion ReadQuat(rapidjson::Value& val) noexcept;

		/**
		 * @brief Serialize object recursively
		 * 
		 * @param transform Transform of the object
		 * @param index Index of the object
		 * @param writer Writer for write in file
		 */
		void SerializeRecursive(Physic::Transform3D* transform, QXint index, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, QXbool& isDeformable) noexcept;

		/**
		 * @brief Write a component in file
		 * 
		 * @param comp Component to write
		 * @param type Type of the component
		 * @param writer writer to use
		 */
		void WriteComponent(rttr::instance comp, rttr::type type, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) noexcept;

		/**
		 * @brief Write an instance in file
		 * 
		 * @param inst Instance to write
		 * @param currentProp Current property of components
		 * @param type type of the property
		 * @param writer writer to use
		 */
		void WriteInstance(rttr::instance inst, rttr::property currentProp, rttr::type type,
			rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) noexcept;

		/**
		 * @brief Write a transform to file
		 * 
		 * @param transform Transform to write
		 * @param writer writer to use
		 */
		void WriteTransform(Physic::Transform3D* transform, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) noexcept;

		/**
		 * @brief Write a vec3 object
		 * 
		 * @param name Name of the variable
		 * @param vec vec3 to write
		 * @param writer writer to use
		 */
		void WriteVec3(const QXstring& name, const Math::QXvec3& vec, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) noexcept;

		/**
		 * @brief Write a quaternion to file
		 * 
		 * @param name Name of the variable
		 * @param quat Quaternion to write
		 * @param writer writer to use
		 */
		void WriteQuat(const QXstring& name, Math::QXquaternion& quat, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) noexcept;

		#pragma endregion

	public:
		#pragma region Constructors

		/**
		 * @brief Construct a new Serializer object
		 * 
		 */
		Serializer() = default;

		/**
		 * @brief Construct a new Serializer object
		 * 
		 * @param serializer serializer to copy
		 */
		Serializer(const Serializer& serializer) = default;

		/**
		 * @brief Construct a new Serializer object
		 * 
		 * @param serilizer serializer to move
		 */
		Serializer(Serializer&& serilizer) = default;

		/**
		 * @brief Destroy the Serializer object
		 * 
		 */
		~Serializer() = default;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Deserilize a scene
		 * 
		 * @param path Path to the scene
		 * @param scene scene to fill
		 * @param manager Manager to init some components
		 * @return QXbool Deserialize successfully
		 */
		QXbool		Deserialize(const QXstring& path, Resources::Scene* scene, DataStructure::ResourcesManager* manager) noexcept;

		/**
		 * @brief Serialize a scene
		 * 
		 * @param scene Scene to serialize
		 * @return QXstring String with scene data
		 */
		QXstring	Serialize(Resources::Scene* scene) noexcept;

		#pragma endregion
	};
}

#endif //__SERIALIZER_H__
