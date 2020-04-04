#ifndef _GAMEOBJECT3D_H_
#define _GAMEOBJECT3D_H_

#include "Core/DataStructure/GameComponent.h"
//#include "Core/DataStructure/Transform3D.h"

namespace Core::DataStructure
{
	/**
	 * @brief class GameObject3D
	 * 
	 */
	class QUANTIX_API GameObject3D : public GameComponent
	{
	protected:
		#pragma region Attributes
		//Transform3D		_transform;
		#pragma endregion Attributes
	public:
		#pragma region Constructors/Destructor
		GameObject3D() = default;
		GameObject3D(std::string name) noexcept;
		GameObject3D(const GameObject3D& g3d) noexcept;
		GameObject3D(GameObject3D&& g3d) noexcept;
		~GameObject3D();
		#pragma endregion Constructors/Destructor

		#pragma region Methods
		/**
		 * @brief Add Child to a GameObject
		 *
		 * @param object GameObject Child
		 */
		void					AddChild(GameObject3D* object);

		/**
		 * @brief Add Child to a GameObject
		 *
		 * @param object const GameObject Child
		 */
		void					AddChild(const GameObject3D* object);
		#pragma region Accessors
		/**
		 * @brief Set the Global Position object
		 *
		 * @param pos QXvec3
		 */
		void					SetGlobalPosition(Math::QXvec3 pos);

		/**
		 * @brief Set the Global Rotation object
		 *
		 * @param rot QXvec3
		 */
		void					SetGlobalRotation(Math::QXvec3 rot);

		/**
		* @brief Get the Global Position object
		*
		*/
		//Math::QXvec3			GetGlobalPosition() const { return _transform.GetGlobalPosition(); };

		/**
		* @brief Get the Global Rotation object
		*
		*/
		//Math::QXvec3			GetGlobalRotation() const { return _transform.GetGlobalRotation(); };

		/**
		* @brief Set the Local Position object
		*
		* @param pos QXvec3
		*/
		void					SetLocalPosition(Math::QXvec3 pos);

		/**
		 * @brief Set the Local Rotation object
		 *
		 * @param rot QXvec3
		 */
		void					SetLocalRotation(Math::QXvec3 rot);

		/**
		 * @brief Set the Local Scale object
		 *
		 * @param scale QXvec3
		 */
		void					SetLocalScale(Math::QXvec3 scale);

		/**
		* @brief Get the Local Position object
		*
		*/
		//Math::QXvec3			GetLocalPosition() const { return _transform.GetLocalPosition(); };

		/**
		* @brief Get the Local Rotation object
		*
		*/
		//Math::QXvec3			GetLocalRotation() const { return _transform.GetLocalRotation(); };

		/**
		* @brief Get the Local Scale object
		*
		*/
		//Math::QXvec3			GetLocalScale() const { return _transform.GetLocalScale(); };

		/**
		* @brief Set the Transform object
		*
		* @param mat QXmat4
		*/
		void					SetTransform(const Math::QXmat4& mat);

		/**
		 * @brief Set the Transform object
		 *
		 * @param pos QXvec3
		 * @param rot QXvec3
		 * @param scale QXvec3
		 */
		void					SetTransform(const Math::QXvec3& pos, const Math::QXvec3& rot, const Math::QXvec3& scale);

		/**
		 * @brief Get the Transform object
		 *
		 */
		//Transform3D			GetTransform() const { return _transform; };
		#pragma endregion Accessors
		GameObject3D&			operator=(const GameObject3D& object);
		#pragma endregion Methods
	};
}

#endif // !_GAMEOBJECT3D_H_
