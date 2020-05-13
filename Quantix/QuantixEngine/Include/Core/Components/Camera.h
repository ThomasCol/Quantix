#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Vec3.h>
#include <Mat4.h>

#include "Core/DLLHeader.h"
#include "rttrEnabled.h"
#include "Core/DataStructure/Component.h"

#define SPEED (1000)
#define SPEEDFREECAM (4.f)

namespace Quantix::Core::Components
{
	struct Rigidbody;

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
		Rigidbody* _rigid = nullptr;

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
		/**
		 * @brief Copy 
		 * 
		 * @return Camera* 
		 */
		Camera* Copy() const override;

		void	Init(Core::DataStructure::GameComponent* object) override;

		void	ActualizeRigid(Rigidbody* rig);

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

		/**
		 * @brief Destroy Component
		 * 
		 */
		void Destroy() override {};

		#pragma	region Accessor

		/**
		 * @brief Get the Look At object
		 * 
		 * @return Math::QXmat4& 
		 */
		inline Math::QXmat4&			GetLookAt() { return _lookAt; }

		/**
		 * @brief Set the Pos object
		 * 
		 * @param pos 
		 */
		inline void						SetPos(Math::QXvec3 pos) { _pos = pos; }

		/**
		 * @brief Get the Pos object
		 * 
		 * @return Math::QXvec3 
		 */
		Math::QXvec3				GetPos();

		void SetPhysicPos(Math::QXvec3 pos);

		/**
		 * @brief Set the Dir object
		 * 
		 * @param dir 
		 */
		inline void						SetDir(Math::QXvec3 dir) { _dir = dir; }

		/**
		 * @brief Get the Dir object
		 * 
		 * @return Math::QXvec3 
		 */
		inline Math::QXvec3				GetDir() { return _dir; }

		/**
		 * @brief Set the Up object
		 * 
		 * @param up 
		 */
		inline void						SetUp(Math::QXvec3 up) { _up = up; }

		/**
		 * @brief Get the Up object
		 * 
		 * @return Math::QXvec3 
		 */
		inline Math::QXvec3				GetUp() { return _up; }
		
		#pragma	endregion
		#pragma endregion Methods

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component)
	};
}

#endif // !_CAMERA_H_
