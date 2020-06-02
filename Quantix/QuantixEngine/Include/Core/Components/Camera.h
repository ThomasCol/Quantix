#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Vec3.h>
#include <Mat4.h>

#include "Core/DLLHeader.h"
#include "rttrEnabled.h"
#include "Core/DataStructure/Component.h"

#define SPEED (3.f)
#define SPEEDJUMP (25.F)
#define SPEEDFREECAM (5.f)

namespace Quantix::Core::Components
{
	struct CharacterController;

	class QUANTIX_API Camera : public virtual Core::DataStructure::Component
	{
	private:
		#pragma region Attributes
		Math::QXvec3	_up;
		Math::QXvec3	_dir;
		Math::QXvec3	_angle;

		Math::QXmat4	_lookAt;
		Math::QXmat4	_trs;

		#pragma endregion Attributes
	public:
		CharacterController* _controller = nullptr;
		Math::QXvec3	_pos;

#pragma region Constructors/Destructor
		/**
		 * @brief Construct a new Camera object
		 * 
		 */
		Camera() noexcept;

		/**
		 * @brief Construct a new Camera object
		 *
		 * @param pos Vector
		 * @param dir Vector
		 * @param up Vector
		 */
		Camera(const Math::QXvec3& pos, const Math::QXvec3& dir, const Math::QXvec3& up) noexcept;

		/**
		 * @brief Construct a new Camera object by copy
		 *
		 * @param camera Camera
		 */
		Camera(const Camera& camera) noexcept;

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

		/**
		 * @brief Init Component Camera
		 *
		 * @param object
		 */
		void	Init(Core::DataStructure::GameComponent * object) override;

		/**
		 * @brief Actualize Character Controller
		 *
		 * @param rig
		 */
		void	ActualizeRigid(CharacterController * rig) noexcept;

		/**
		 * @brief Update the LookAtMatrix of the Camera
		 *
		 * @param pos Vector
		 * @return Math::QXmat4 LookAtMatrix of the Camera
		 */
		void							UpdateLookAt(Math::QXvec3 pos) noexcept;

		/**
		 * @brief Change the view of the Camera
		 *
		 * @param posX int Value
		 * @param posY int Value
		 * @param width int Value
		 * @param height int Value
		 * @param frameTime double Value
		 */
		void							ChangeView(QXfloat posX, QXfloat posY, QXint width, QXint height, QXdouble frameTime) noexcept;

		/**
		 * @brief Rotate The dir of the Camera
		 *
		 * @param rotate Math::QxVec3
		 */
		void							Rotate(Math::QXvec3 rotate) noexcept;

		/**
		 * @brief Destroy Component
		 *
		 */
		void							Destroy() override {};

#pragma	region Accessor

		/**
		 * @brief Get the Look At object
		 *
		 * @return Math::QXmat4&
		 */
		inline Math::QXmat4&			GetLookAt()  noexcept { return _lookAt; }

		/**
		 * @brief Set the Pos object
		 *
		 * @param pos
		 */
		void							SetPos(Math::QXvec3 pos) noexcept;

		/**
		 * @brief Get the Pos object
		 *
		 * @return Math::QXvec3
		 */
		Math::QXvec3					GetPos() noexcept;

		/**
		 * @brief Set the Dir object
		 *
		 * @param dir
		 */
		inline void						SetDir(Math::QXvec3 dir)  noexcept { _dir = dir; }

		/**
		 * @brief Get the Dir object
		 *
		 * @return Math::QXvec3
		 */
		inline Math::QXvec3				GetDir()  noexcept { return _dir; }

		/**
		 * @brief Set the Up object
		 *
		 * @param up
		 */
		inline void						SetUp(Math::QXvec3 up)  noexcept { _up = up; }

		/**
		 * @brief Get the Up object
		 *
		 * @return Math::QXvec3
		 */
		inline Math::QXvec3				GetUp()  noexcept { return _up; }
		
		#pragma	endregion
		#pragma endregion Methods

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component)
	};
}

#endif // !_CAMERA_H_
