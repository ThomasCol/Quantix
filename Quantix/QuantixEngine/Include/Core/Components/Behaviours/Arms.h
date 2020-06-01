#ifndef __ARMS_H__
#define __ARMS_H__

#include "Core\Components\Behaviour.h"
#include "Core\DataStructure\GameObject3D.h"
#include "Core\Components\Rigidbody.h"
#include "rttrEnabled.h"

namespace Quantix::Gameplay
{
	enum class QUANTIX_API EArmState
	{
		FREEZE,
		MAGNET_NEG,
		MAGNET_POS
	};

	class QUANTIX_API Arms : public Quantix::Core::Components::Behaviour
	{
		private:

			#pragma region Attributes

			QXbool								_isGrabbingObject		{ false };
			Core::DataStructure::GameObject3D*	_grabbedObject			{ nullptr };

			Core::DataStructure::GameObject3D*	_gameobject				{ nullptr };
			Core::Components::Mesh*				_mesh					{ nullptr };

			EArmState							_state					{ EArmState::FREEZE };

			Math::QXvec3						_objectFrozenVelocity;

			/*Math::QXvec3						_objectFrozenAmbiant;
			Math::QXvec3						_objectFrozenDiffuse;
			Math::QXvec3						_objectFrozenSpecular;*/
			#pragma endregion

			#pragma region Methods

			/**
			 * @brief Use the hands to grab or drop a cube
			 *
			 */
			void	UseHands();

			/**
			 * @brief Grab a cube
			 *
			 */
			void	Grab();

			/**
			 * @brief Drop the cube
			 *
			 */
			void	Drop();

			/**
			 * @brief Use the ice power to freeze or unfreeze a cube
			 *
			 */
			void	UseIce();

			/**
			 * @brief Freeze a cube
			 *
			 */
			void	Freeze(Core::DataStructure::GameObject3D* cube, Core::Components::Rigidbody* rigid);

			/**
			 * @brief Unfreeze a cube
			 *
			 */
			void	UnFreeze(Core::DataStructure::GameObject3D* cube, Core::Components::Rigidbody* rigid);

			/**
			 * @brief Throw the cube the hands are grabbing
			 *
			 */
			void	Throw();

			/**
			 * @brief Magnetize a cube
			 *
			 */
			void	UseMagnet(QXbool positiveField);

			/**
			 * @brief Change current power selected in the arms
			 *
			 */
			void	SwitchPower();

			/**
			 * @brief Use current power selected in the arms
			 *
			 */
			void	UsePower();

			/**
			 * @brief Change the materials of the arms for better feebacks
			 *
			 */
			void	UpdateMaterial();

			#pragma endregion
		
		public:

			#pragma region Constructors & Destructor

			/**
			 * @brief Construct a new Arms object
			 *
			 */
			Arms() = default;

			/**
			 * @brief Construct a new Arms object
			 *
			 * @param par GameComponent who has this component
			 */
			Arms(Quantix::Core::DataStructure::GameComponent * par);

			/**
			 * @brief Construct a new Arms object per copy
			 *
			 */
			Arms(const Arms&) = default;

			/**
			 * @brief Construct a new Arms object per move
			 *
			 */
			Arms(Arms&&) = default;

			/**
			 * @brief Destroy the Arms object
			 *
			 */
			~Arms() = default;

			#pragma enregion

			/**
			 * @brief Create a new Arms object
			 *
			 * @return Arms* new Arms
			 */
			Arms*						Copy() const override;

			#pragma region Methods

			/**
			 * @brief Called when the Arms object is created
			 *
			 */
			void						Awake() override;

			/**
			 * @brief Called when the scene is played
			 *
			 */
			void						Start() override;

			/**
			 * @brief Called each frame of the game
			 *
			 * @param deltaTime
			 */
			void						Update(QXdouble deltaTime) override;

			#pragma region Accessors

			/**
			 * @brief Get the current power
			 *
			 * @param const EArmState& the current power activated on the arms
			 */
			inline const EArmState&		GetPower() { return _state;  };
			
			#pragma endregion

			#pragma endregion
			CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif //__ARMS_H__