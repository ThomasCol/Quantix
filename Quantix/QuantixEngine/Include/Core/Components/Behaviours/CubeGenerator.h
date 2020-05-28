#ifndef __CUBEGENERATOR_H__
#define __CUBEGENERATOR_H__

#include "Core\Components\Behaviour.h"
#include "Core\Components\Behaviours\Cube.h"
#include "Core\DataStructure\GameObject3D.h"
#include "Core\Platform\Application.h"
#include "rttrEnabled.h"

namespace Quantix::Gameplay
{
	class QUANTIX_API CubeGenerator : public Quantix::Core::Components::Behaviour
	{
	private:

		#pragma region Attributes

		std::list<Core::DataStructure::GameObject3D*>	_cubes;
		QXfloat											_distMinBtwCubesAndGenerator	{ 5.f };
		QXuint											_nbMaxOfCubes					{ 1 };
		Core::DataStructure::GameObject3D*				_gameobject = nullptr;

		Core::Platform::Application*					_app;

		#pragma endregion

		#pragma region Methods

		void					CreateCube();

		#pragma endregion

	public:

		#pragma region Constructors & Destructor

		CubeGenerator() = default;
		CubeGenerator(Quantix::Core::DataStructure::GameComponent* par);
		CubeGenerator(const CubeGenerator&) = default;
		CubeGenerator(CubeGenerator&&) = default;
		~CubeGenerator() = default;

		#pragma endregion

		CubeGenerator*			Copy() const override;

		#pragma region Methods

		void					Awake() override;
		void					Start() override;
		void					Update(QXdouble deltaTime) override;

		#pragma region Accessors

		inline void				SetDistMinBtwCubesAndGenerator(const QXfloat& newDistMinBtwCubesAndGenerator) { _distMinBtwCubesAndGenerator = newDistMinBtwCubesAndGenerator; };
		inline const QXfloat&	GetDistMinBtwCubesAndGenerator() { return _distMinBtwCubesAndGenerator; };

		inline void				SetNbMaxOfCubes(const QXuint& newNbMaxOfCubes) { _nbMaxOfCubes = newNbMaxOfCubes; };
		inline const QXuint&	GetNbMaxOfCubes() { return _nbMaxOfCubes; };

		inline void				SetApplication(Core::Platform::Application* app) { _app = app; };

		#pragma endregion

		#pragma endregion

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif //__CUBEGENERATOR_H__