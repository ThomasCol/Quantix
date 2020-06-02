#ifndef __CUBEGENERATOR_H__
#define __CUBEGENERATOR_H__

#include "Core\Components\Behaviour.h"
#include "Core\Components\Behaviours\Cube.h"
#include "Core\DataStructure\GameObject3D.h"
#include "Core\Platform\Application.h"
#include "rttrEnabled.h"

//Color Top Plate
#define COLORTAMBIENT Math::QXvec3(106, 184, 255)/255
#define COLORTDIFFUSE Math::QXvec3(123, 183, 255)/255

//Color Bottom Plates
#define COLORB Math::QXvec3(255, 255, 255)/255

//Color Pole
#define COLORPAMBIENT Math::QXvec3(72, 23, 18)/255
#define COLORPDIFFUSE Math::QXvec3(35, 8, 3)/255
#define COLORPSPECULAR Math::QXvec3(10, 10, 10)/255

namespace Quantix::Gameplay
{
	class QUANTIX_API CubeGenerator : public Quantix::Core::Components::Behaviour
	{
	private:

		#pragma region Attributes

		std::list<Core::DataStructure::GameObject3D*>	_cubes;
		QXfloat											_distForGeneration	{ 5.f };
		QXuint											_nbMaxOfCubes		{ 1 };
		Core::DataStructure::GameObject3D*				_gameobject			{ nullptr };

		Quantix::Resources::Scene*						_scene;
		Quantix::Core::DataStructure::ResourcesManager*	_manager;

		QXbool											_IsGeneratorCreated { false };

		#pragma endregion

		#pragma region Methods

		void					CreateCube();
		void					ReUseCube(Core::DataStructure::GameObject3D* cube);

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
		void					Destroy() override;
		void					GenerateMesh(QXstring name, Math::QXvec3 pos, Math::QXvec3 scale, Math::QXvec3 ambient, Math::QXvec3 diffuse, Math::QXvec3 specular);
		void					CreateGenerator();

		#pragma region Accessors

		inline void				SetDistForGeneration(const QXfloat& newDistforGeneration) { _distForGeneration = newDistforGeneration; };
		inline const QXfloat&	GetDistForGeneration() { return _distForGeneration; };

		inline void				SetNbMaxOfCubes(const QXuint& newNbMaxOfCubes) { _nbMaxOfCubes = newNbMaxOfCubes; };
		inline const QXuint&	GetNbMaxOfCubes() { return _nbMaxOfCubes; };

		void					SetSceneAndResourcesManager(Quantix::Resources::Scene* scene, Quantix::Core::DataStructure::ResourcesManager* rm);

		#pragma endregion

		#pragma endregion

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif //__CUBEGENERATOR_H__