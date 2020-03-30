#ifndef _GAMEOBJECT2D_H_
#define _GAMEOBJECT2D_H_

#include "Core/DataStructure/GameComponent.h"
//#include "Core/DataStructure/Transform2D.h"

namespace Core::DataStructure
{
	/**
	 * @brief class GameObject2D
	 * 
	 */
	class GameObject2D : GameComponent
	{
	protected:
		#pragma region Attributes
		//Transform2D		_transform;
		#pragma endregion Attributes
	public:
		#pragma region Constructors/Destructor
		GameObject2D() noexcept;
		GameObject2D(const GameObject2D& g2d) noexcept;
		GameObject2D(GameObject2D&& g2d) noexcept;
		~GameObject2D();
		#pragma endregion Constructors/Destructor

		#pragma region Methods
		/**
		 * @brief Add Child to a GameObject
		 *
		 * @param object GameObject Child
		 */
		void					AddChild(GameObject2D* object);

		/**
		 * @brief Add Child to a GameObject
		 *
		 * @param object const GameObject Child
		 */
		void					AddChild(const GameObject2D* object);
		#pragma region Accessors
		/**
		 * @brief Set the Global Position object
		 * 
		 * @param pos Math::QXvec2 pos
		 */
		void					SetGlobalPosition(Math::QXvec2 pos);

		/**
		 * @brief Set the Global Rotation object
		 * 
		 * @param rot QXfloat angle
		 */
		void					SetGlobalRotation(QXfloat rot);

		/**
		 * @brief Get the Global Position object
		 * 
		 * @return Math::QXvec2 position
		 */
		 //Math::QXvec2			GetGlobalPosition() const { return _transform.GetGlobalPosition(); };

		/**
		 * @brief Get the Global Rotation object
		 * 
		 * @return QXfloat rotation
		 */
		//QXfloat				GetGlobalRotation() const { return _transform.GetGlobalRotation(); };

		/**
		 * @brief Set the Local Position object
		 * 
		 * @param pos Math::QXvec2 position
		 */
		void					SetLocalPosition(Math::QXvec2 pos);

		/**
		 * @brief Set the Local Rotation object
		 * 
		 * @param rot QXfloat rotation
		 */
		void					SetLocalRotation(QXfloat rot);

		/**
		 * @brief Set the Local Scale object
		 *
		 * @param scale QXvec2
		 */
		void					SetLocalScale(Math::QXvec2 scale);

		/**
		 * @brief Get the Local Position object
		 * 
		 * @return Math::QXvec2 position
		 */
		 //Math::QXvec2			GetLocalPosition() const { return _transform.GetLocalPosition(); };

		/**
		 * @brief Get the Local Rotation object
		 * 
		 * @return QXfloat rotation
		 */
		//QXfloat				GetLocalRotation() const { return _transform.GetLocalRotation(); };

		/**
		 * @brief Get the Local Scale object
		 * 
		 * @return Math::QXvec2 scale
		 */
		//Math::QXvec2			GetLocalScale() const { return _transform.GetLocalScale(); };

		/**
		* @brief Set the Transform object
		*
		* @param mat QXmat4
		*/
		void					SetTransform(const Math::QXmat4& mat);

		/**
		 * @brief Set the Transform object
		 *
		 * @param pos QXvec2 position
		 * @param rot QXfloat rotation
		 * @param scale QXvec2 scale
		 */
		void					SetTransform(const Math::QXvec2& pos, const QXfloat rot, const Math::QXvec2& scale);

		/**
		 * @brief Get the Transform object
		 * 
		 * @return Transform2D transform
		 */
		//Transform2D			GetTransform() const { return _transform; };
		#pragma endregion Accessors
		#pragma endregion Methods
	};
}

#endif // !_GAMEOBJECT3D_H_