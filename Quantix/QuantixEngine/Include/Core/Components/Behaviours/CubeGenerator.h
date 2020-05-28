#ifndef __CUBEGENERATOR_H__
#define __CUBEGENERATOR_H__

#include "Core\Components\Behaviour.h"
#include "Core\Components\Behaviours\Cube.h"
#include "Core\DataStructure\GameObject3D.h"
#include "rttrEnabled.h"

namespace Quantix::Gameplay
{
	class QUANTIX_API CubeGenerator : public Quantix::Core::Components::Behaviour
	{
	private:

		#pragma region Attributes

		std::list<Core::DataStructure::GameObject3D*>		_cubes;
		QXuint												_nbOfCubes	{ 1 };
		Core::DataStructure::GameObject3D*					_gameobject = nullptr;

		#pragma endregion

		#pragma region Methods

		void					CreateCube();

		#pragma endregion

	public:

		CubeGenerator() = default;
		CubeGenerator(Quantix::Core::DataStructure::GameComponent* par);
		CubeGenerator(const CubeGenerator&) = default;
		CubeGenerator(CubeGenerator&&) = default;
		~CubeGenerator() = default;

		CubeGenerator* Copy() const override;

		#pragma region Methods

		void					Awake() override;
		void					Start() override;
		void					Update(QXdouble deltaTime) override;

		#pragma region Accessors

		inline void				SetNbOfCubes(const QXuint& newNbOfCubes) { _nbOfCubes = newNbOfCubes; };
		inline const QXuint&	GetNbOfCubes() { return _nbOfCubes; };

		#pragma endregion

		#pragma endregion

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif //__CUBEGENERATOR_H__