#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "Core/DLLHeader.h"
#include "Core/DataStructure/Component.h"
#include "rttrEnabled.h"

#include "Physic/IPhysicType.h"
#include "Physic/PhysicHandler.h"
#include "Core/MathHeader.h"

#include "Physic/PhysicSetting.h"

namespace Quantix::Core::DataStructure
{
	class GameComponent;
}

namespace Quantix::Core::Components
{
	struct QUANTIX_API Rigidbody : public virtual Core::DataStructure::Component
	{
#pragma region Attributes
		Physic::PhysicDynamic* actorPhysic{ nullptr };

		Physic::ActorFlag actorFlag;
		Physic::RigidBodyFlag rigidFlag;
		QXfloat mass {1.f};

#pragma endregion

#pragma region Constructors

		/**
		 * @brief Construct a new Rigidbody object
		 * 
		 */
		Rigidbody() = default;

		/**
		 * @brief Construct a new Rigidbody object
		 * 
		 * @param par Parent of the Rigidbody
		 */
		Rigidbody(DataStructure::GameComponent* par);

		/**
		 * @brief Construct a new Rigidbody object
		 * 
		 * @param src Rigidbody to copy
		 */
		Rigidbody(const Rigidbody& src) noexcept;

		/**
		 * @brief Construct a new Rigidbody object
		 * 
		 * @param src Rigidbody to move
		 */
		Rigidbody(Rigidbody&& src) noexcept;

		/**
		 * @brief Destroy the Rigidbody object
		 * 
		 */
		~Rigidbody() noexcept = default;

#pragma endregion

#pragma region Functions

		/**
		 * @brief Add Force On The Rigidbody
		 * 
		 * @param vec Force To Add
		 */
		void AddForce(Math::QXvec3 vec) noexcept;

		/**
		 * @brief Copy a Rigidbody
		 * 
		 * @return Rigidbody* new Rigidbody
		 */
		Rigidbody* Copy() const;

		/**
		 * @brief Init a Rigidbody
		 * 
		 * @param par Parent of the Rigidbody
		 */
		void Init(DataStructure::GameComponent* par);

		/**
		 * @brief Destory the RigidBody
		 * 
		 */
		void Destroy() override;

#pragma endregion

#pragma region Accessors 

		/**
		 * @brief Get the Mass object
		 * 
		 * @return QXfloat Value of the Mass
		 */
		QXfloat GetMass();

		/**
		 * @brief Set the Mass object
		 * 
		 * @param mass new value of Mass
		 */
		void SetMass(QXfloat mass);

		/**
		 * @brief Get the Linear Velocity object
		 * 
		 * @return Math::QXvec3 Value of Linear Velocity
		 */
		Math::QXvec3 GetLinearVelocity();

		/**
		 * @brief Set the Linear Velocity object
		 * 
		 * @param linVelo New Value of LinearVelocity
		 */
		void SetLinearVelocity(Math::QXvec3 linVelo);

		/**
		 * @brief Get the Angular Velocity object
		 * 
		 * @return Math::QXvec3 Value of Angular Velocity
		 */
		Math::QXvec3 GetAngularVelocity();

		/**
		 * @brief Set the Angular Velocity object
		 * 
		 * @param angVelo new Value of Angular Velocity
		 */
		void SetAngularVelocity(Math::QXvec3 angVelo);

		/**
		 * @brief Get the Transform Position object
		 * 
		 * @return Math::QXvec3 Position value
		 */
		Math::QXvec3 GetTransformPosition();

		/**
		 * @brief Set the Transform Position object
		 * 
		 * @param v new Position
		 */
		void SetTransformPosition(Math::QXvec3 v);

		/**
		 * @brief Get the Transform Rotation object
		 * 
		 * @return Math::QXquaternion Value of Rotation
		 */
		Math::QXquaternion GetTransformRotation();

		/**
		 * @brief Set the Transform Rotation object
		 * 
		 * @param q New Rotation Value
		 */
		void SetTransformRotation(Math::QXquaternion q);

		/**
		 * @brief Set the Actor Flag Disable Gravity object
		 * 
		 * @param b new Value of the Flag
		 */
		void SetActorFlagDisableGravity(bool b);

		/**
		 * @brief Get the Actor Flag Disable Gravity object
		 * 
		 * @return Value of the flag 
		 */
		bool GetActorFlagDisableGravity();

		/**
		 * @brief Set the Actor Flag Disable Simulation object
		 * 
		 * @param b new Value of the Flag
		 */
		void SetActorFlagDisableSimulation(bool b);

		/**
		 * @brief Get the Actor Flag Disable Simulation object
		 * 
		 * @return Value of the flag 
		 */
		bool GetActorFlagDisableSimulation();
		void SetActorFlagSendSleepNotifies(bool b);
		bool GetActorFlagSendSleepNotifies();
		
		void SetActorFlagVisualization(bool b); // to delete
		bool GetActorFlagVisualization(); // to delete

		void SetRigidFlagCCD(bool b);
		bool GetRigidFlagCCD();
		void SetRigidFlagCCDFriction(bool b);
		bool GetRigidFlagCCDFriction();
		void SetRigidFlagSpeculativeCCD(bool b);
		bool GetRigidFlagSpeculativeCCD();

		/**
		 * @brief Set the Rigid Flag Kinematic object
		 * 
		 * @param b new Value of the flag
		 */
		void SetRigidFlagKinematic(bool b);

		/**
		 * @brief Get the Rigid Flag Kinematic object
		 * 
		 * @return Value of the Flag
		 */
		bool GetRigidFlagKinematic();
		
		void SetRigidFlagRetainAcceleration(bool b);
		bool GetRigidFlagRetainAcceleration();
		void SetRigidFlagKineForQueries(bool b);
		bool GetRigidFlagKineForQueries();
		void SetRigidFlagPosePreview(bool b);
		bool GetActorFlagPosePreview();
		void SetActorFlagCCDMaxContactImpulse(bool b);
		bool GetActorFlagCCDMaxContactImpulse();

#pragma endregion 

		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif

