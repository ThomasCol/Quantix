#ifndef __CUBE_H__
#define __CUBE_H__

#include "Core\Components\Behaviour.h"
#include "rttrEnabled.h"
#include "Core/Components//Mesh.h"

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

			Core::DataStructure::GameObject3D*	_gameobject		{ nullptr };
			ECubeState							_state			{ ECubeState::DEFAULT };
			QXfloat								_rangeOfMagnet	{ 3.f };

			Core::Components::Mesh* _mesh = nullptr;

			#pragma endregion

			#pragma region Methods

			/**
			 * @brief Attract the other cubes by positive magnetization
			 *
			 */
			void						Attract(QXdouble deltaTime);

			/**
			 * @brief Reject the other cubes by negative magnetization
			 *
			 */
			void						Reject(QXdouble deltaTime);

			#pragma endregion
		
		public:

			#pragma region Constructors & Destructor

			/**
			 * @brief Construct a new Cube object
			 *
			 */
			Cube() = default;

			/**
			 * @brief Construct a new Cube object
			 *
			 * @param par GameComponent who has this component
			 */
			Cube(Quantix::Core::DataStructure::GameComponent * par);

			/**
			 * @brief Construct a new Cube object per copy
			 *
			 */
			Cube(const Cube&) = default;

			/**
			 * @brief Construct a new Cube object per move
			 *
			 */
			Cube(Cube&&) = default;

			/**
			 * @brief Destroy the Cube object
			 *
			 */
			~Cube() = default;

			#pragma endregion

			/**
			 * @brief Create a new Cube object
			 *
			 * @return Cube* new Cube
			 */
			Cube* Copy() const override;

			#pragma region Methods
			 
			/**
			 * @brief Called when the Cube object is created
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

			/**
			 * @brief Change the materials of the cube for better feebacks
			 *
			 */
			void UpdateMaterial();

			#pragma region Accessors

			/**
			 * @brief Set the new state of the cube
			 *
			 * @param newState the power of the arms activated on the cube
			 */
			inline void					ChangeState(const ECubeState& newState) { _state = newState; };

			/**
			 * @brief Get the current state of the cube
			 *
			 * @param const ECubeState& the current power of the arms activated on the cube
			 */
			inline const ECubeState&	GetState() { return _state; };
			
			/**
			 * @brief Get the current magnet range of the cube
			 *
			 * @param const QXfloat& the current magnet range of the cube
			 */
			inline const QXfloat&		GetRangeOfMagnet() { return _rangeOfMagnet; };

			/**
			 * @brief Set the new magnet range of the cube
			 *
			 * @param newRange the magnet range of the cube
			 */
			inline void					SetRangeOfMagnet(const QXfloat& newRange) { _rangeOfMagnet = newRange; };

			#pragma endregion

			#pragma endregion

			CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif //__CUBE_H__