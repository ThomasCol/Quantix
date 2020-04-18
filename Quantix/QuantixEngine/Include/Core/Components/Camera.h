#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Vec3.h>
#include <Mat4.h>

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "rttrEnabled.h"

namespace Quantix::Core::Components
{
	class QUANTIX_API Camera : public virtual Core::DataStructure::Component
	{
	private:
		#pragma region Attributes
		Math::QXvec3	_up;
		Math::QXvec3	_pos;
		Math::QXvec3	_dir;
		Math::QXvec3	_angle;

		Math::QXmat4	_lookAt;
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
		Camera(const Math::QXvec3& pos, const Math::QXvec3& dir, const Math::QXvec3& up);
		
		Camera(Core::DataStructure::GameComponent* object);

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
		Camera(Camera&& camera) noexcept;

		/**
		 * @brief Destroy the Camera object
		 * 
		 */
		~Camera() = default;
		#pragma endregion Constructors/Destructor

		#pragma region Methods
		Camera* Copy() const override;

		/**
		 * @brief Init the camera component
		 * 
		 * @param pos Vector
		 * @param dir Vector
		 * @param up Vector
		 */
		void							Init(Math::QXvec3 pos, Math::QXvec3 dir, Math::QXvec3 up);

		/**
		 * @brief Update the LookAtMatrix of the Camera
		 * 
		 * @param pos Vector
		 * @return Math::QXmat4 LookAtMatrix of the Camera
		 */
		void							UpdateLookAt(Math::QXvec3 pos);

		/**
		 * @brief Change the view of the Camera
		 * 
		 * @param posX int Value
		 * @param posY int Value
		 * @param width int Value
		 * @param height int Value
		 * @param frameTime double Value
		 */
		void							ChangeView(QXfloat posX, QXfloat posY, QXint width, QXint height, QXdouble frameTime);

		/**
		 * @brief Rotate The dir of the Camera
		 * 
		 * @param rotate Math::QxVec3
		 */
		void							Rotate(Math::QXvec3 rotate);

		#pragma	region Accessor

		inline Math::QXmat4				GetLookAt() { return _lookAt; }

		inline void						SetPos(Math::QXvec3 pos) { _pos = pos; }

		inline Math::QXvec3				GetPos() { return _pos; }

		inline void						SetDir(Math::QXvec3 dir) { _dir = dir; }

		inline Math::QXvec3				GetDir() { return _dir; }

		inline void						SetUp(Math::QXvec3 up) { _up = up; }

		inline Math::QXvec3				GetUp() { return _up; }
		
		#pragma	endregion
		#pragma endregion Methods

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component)
	};
}

#endif // !_CAMERA_H_
