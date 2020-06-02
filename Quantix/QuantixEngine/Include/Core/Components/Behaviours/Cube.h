#ifndef __CUBE_H__
#define __CUBE_H__

#include "Core\Components\Behaviour.h"
#include "rttrEnabled.h"
#include "Core/Components//Mesh.h"

#define ATTRACTFORCE 1000.f
#define REJECTFORCE 1000.f

namespace Quantix::Gameplay
{
	enum class QUANTIX_API ECubePhysicState
	{
		DEFAULT,
		GRABBED,
		FROZEN
	};

	enum class QUANTIX_API ECubeMagnetState
	{
		DEFAULT,
		MAGNET_NEG,
		MAGNET_POS
	};

	class QUANTIX_API Cube : public Quantix::Core::Components::Behaviour
	{
		private:

			#pragma region Attributes

			ECubePhysicState	_statePhysic			{ ECubePhysicState::DEFAULT };
			ECubeMagnetState	_stateMagnet			{ ECubeMagnetState::DEFAULT };

			QXfloat		_rangeOfMagnet	{ 3.f };

			Core::Components::Mesh* _mesh = nullptr;

			#pragma endregion

			#pragma region Methods

			void						Attract(QXdouble deltaTime) noexcept;
			void						Reject(QXdouble deltaTime) noexcept;

			#pragma endregion
		
		public:

			Cube() = default;
			Cube(Quantix::Core::DataStructure::GameComponent * par);
			Cube(const Cube&) = default;
			Cube(Cube&&) = default;
			~Cube() = default;

			Cube* Copy() const override;
			#pragma region Methods
			 
			void						Awake() override;
			void						Start() override;
			void						Update(QXdouble deltaTime) override;

			void UpdateMaterial() noexcept;

			#pragma region Accessors

			inline void					ChangeStatePhysic(ECubePhysicState newState) noexcept { _statePhysic = newState; };
			inline const ECubePhysicState&	GetStatePhysic() noexcept { return _statePhysic; };

			inline void					ChangeStateMagnet(ECubeMagnetState newState) noexcept { _stateMagnet = newState; };
			inline const ECubeMagnetState& GetStateMagnet() noexcept { return _stateMagnet; };
			
			inline const float&			GetRangeOfMagnet() noexcept { return _rangeOfMagnet; };
			inline void					SetRangeOfMagnet(QXfloat range) noexcept { _rangeOfMagnet = range; };

			#pragma endregion

			#pragma endregion

			CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif //__CUBE_H__