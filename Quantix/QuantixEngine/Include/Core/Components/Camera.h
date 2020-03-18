#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Vec3.h>
#include <Mat4.h>
//#include "Component.h"

namespace Core::Components
{
	class Camera //: public virtual Core::DataStructure::Component
	{
	private:
		#pragma region Attributes
		Math::QXvec3	_up;
		Math::QXvec3	_pos;
		Math::QXvec3	_dir;
		Math::QXvec3	_angle;
		#pragma endregion Attributes
	public:
		#pragma region Constructors/Destructor
		/**
		 * @brief Construct a new Camera object
		 * 
		 */
		Camera();

		/**
		 * @brief Construct a new Camera object
		 * 
		 * @param pos Vector
		 * @param dir Vector
		 * @param up Vector
		 */
		Camera(Math::QXvec3 pos, Math::QXvec3 dir, Math::QXvec3 up);
		//Camera(Core::DataStructure::GameObject* object);

		/**
		 * @brief Construct a new Camera object by copy 
		 * 
		 * @param camera Camera
		 */
		Camera(const Camera& camera);

		/**
		 * @brief Construct a new Camera object by move
		 * 
		 * @param camera Camera
		 */
		Camera(Camera&& camera) = default;

		/**
		 * @brief Destroy the Camera object
		 * 
		 */
		~Camera() {};
		#pragma endregion Constructors/Destructor

		#pragma region Methods
		/**
		 * @brief Init the camera component
		 * 
		 * @param pos Vector
		 * @param dir Vector
		 * @param up Vector
		 */
		void							Init(Math::QXvec3 pos, Math::QXvec3 dir, Math::QXvec3 up);
		//const std::type_info&			GetType() const override;
		//Core::DataStructure:Component*	Copy() const override;
		//inline void						Destroy() override {};

		/**
		 * @brief Update the LookAtMatrix of the Camera
		 * 
		 * @param pos Vector
		 * @return Math::QXmat4 LookAtMatrix of the Camera
		 */
		Math::QXmat4					UpdateLookAt(Math::QXvec3 pos);

		/**
		 * @brief Change the view of the Camera
		 * 
		 * @param posX int Value
		 * @param posY int Value
		 * @param width int Value
		 * @param height int Value
		 * @param frameTime double Value
		 */
		void							ChangeView(int posX, int posY, int width, int height, double frameTime);

		/**
		 * @brief Rotate The dir of the Camera
		 * 
		 * @param rotate Math::QxVec3
		 */
		void							Rotate(Math::QXvec3 rotate);
		#pragma endregion Methods
	};
}

#endif // !_CAMERA_H_
