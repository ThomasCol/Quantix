#ifndef __ARMS_H__
#define __ARMS_H__

#include "Core\Components\Behaviour.h"
#include "Core\DataStructure\GameObject3D.h"
#include "Core\Components\Rigidbody.h"
#include "Core\Components\Behaviours\Cube.h"
#include "rttrEnabled.h"

namespace Quantix::Core::Components::Behaviours
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

			QXbool								_isGrabbingObject = false;
			Physic::Transform3D*				_originOfGrabbedObject = nullptr;
			Core::DataStructure::GameObject3D*	_grabbedObject = nullptr;

			Core::DataStructure::GameObject3D*	_gameobject = nullptr;
			Core::Components::Rigidbody*		rigid = nullptr;
			Core::Components::Mesh*				_mesh = nullptr;

			EArmState _state = EArmState::FREEZE;

			Math::QXvec3 objectFrozenAmbiant;
			Math::QXvec3 objectFrozenDiffuse;
			Math::QXvec3 objectFrozenSpecular;
			#pragma endregion

			#pragma region Methods

			void	UseHands() noexcept;
			void	Grab() noexcept;
			void	Drop() noexcept;
			void	UseIce() noexcept;
			void	Freeze(Core::DataStructure::GameObject3D* cube, Cube* comp) noexcept;
			void	UnFreeze(Core::DataStructure::GameObject3D* cube, Cube* comp) noexcept;
			void	UsePunch() noexcept;
			void	UseMagnet(QXbool positiveField) noexcept;
			void	SwitchPower() noexcept;
			void	UsePower() noexcept;

			#pragma endregion
		
		public:

			Arms() = default;
			Arms(Quantix::Core::DataStructure::GameComponent * par);
			Arms(const Arms&) = default;
			Arms(Arms&&) = default;
			~Arms() = default;

			Arms*						Copy() const override;

			#pragma region Methods

			void						Awake() override;
			void						Start() override;
			void						Update(QXdouble deltaTime) override;
			void						UpdateMaterial() noexcept;
			inline EArmState			GetPower() noexcept { return _state;  };
			
			#pragma endregion
			CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif //__ARMS_H__