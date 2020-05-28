#ifndef __CUBE_H__
#define __CUBE_H__

#include "Core\Components\Behaviour.h"
#include "rttrEnabled.h"

namespace Quantix::Gameplay
{
	enum class QUANTIX_API ECubeState
	{
		DEFAULT,
		GRABBED,
		FROZEN,
		MAGNET_NEG,
		MAGNET_POS,
	};

	class QUANTIX_API Cube : public Quantix::Core::Components::Behaviour
	{
		private:

			#pragma region Attributes

			ECubeState	_state			{ ECubeState::DEFAULT };
			QXfloat		_rangeOfMagnet	{ 3.f };

			#pragma endregion

			#pragma region Methods

			void						Attract(QXdouble deltaTime);
			void						Reject(QXdouble deltaTime);

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

			#pragma region Accessors

			inline void					ChangeState(ECubeState newState) { _state = newState; };
			inline const ECubeState&	GetState() { return _state; };
			
			inline const float&			GetRangeOfMagnet() { return _rangeOfMagnet; };
			inline void					SetRangeOfMagnet(QXfloat range) { _rangeOfMagnet = range; };

			#pragma endregion

			#pragma endregion

			CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif //__CUBE_H__