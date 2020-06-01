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
		//QXuint											_savedNbOfCubes		{ 0 };

		Core::Platform::Application*					_app;

		#pragma endregion

		#pragma region Methods

		/**
		 * @brief Generate a cube entirely
		 *
		 */
		void					CreateCube();

		/**
		 * @brief Generate one of the meshs of the generator
		 *
		 */
		void					GenerateMesh(QXstring name, Math::QXvec3 pos, Math::QXvec3 scale, Math::QXvec3 ambient, Math::QXvec3 diffuse, Math::QXvec3 specular);

		#pragma endregion

	public:

		#pragma region Constructors & Destructor

		/**
		 * @brief Construct a new Cube Generator object
		 *
		 */
		CubeGenerator() = default;

		/**
		 * @brief Construct a new Cube Generator object
		 *
		 * @param par GameComponent who has this component
		 */
		CubeGenerator(Quantix::Core::DataStructure::GameComponent* par);

		/**
		 * @brief Construct a new Cube Generator object per copy
		 *
		 */
		CubeGenerator(const CubeGenerator&) = default;

		/**
		 * @brief Construct a new Cube Generator object per move
		 *
		 */
		CubeGenerator(CubeGenerator&&) = default;

		/**
		 * @brief Destroy the Cube Generator object
		 *
		 */
		~CubeGenerator() = default;

		#pragma endregion

		/**
		 * @brief Create a new Cube Generator object
		 *
		 * @return CubeGenerator* new CubeGenerator
		 */
		CubeGenerator*			Copy() const override;

		#pragma region Methods

		/**
		 * @brief Called when the Cube Generator object is created
		 *
		 */
		void					Awake() override;

		/**
		 * @brief Called when the scene is played
		 *
		 */
		void					Start() override;

		/**
		 * @brief Called each frame of the game
		 *
		 * @param deltaTime
		 */
		void					Update(QXdouble deltaTime) override;

		/**
		 * @brief Destroy the Cube Generator object
		 *
		 */
		void					Destroy() override;

		/**
		 * @brief Create the Cube Generator prefabricate object
		 *
		 */
		void					CreateGenerator();

		#pragma region Accessors

		/**
		 * @brief Set the distance for the generator to create another cube
		 *
		 * @param newDistforGeneration the distance for a cube to be to generate another cube
		 */
		inline void				SetDistForGeneration(const QXfloat& newDistforGeneration) { _distForGeneration = newDistforGeneration; };

		/**
		 * @brief Get the distance for the generator to create another cube
		 *
		 * @param const QXfloat& the distance for a cube to be to generate another cube
		 */
		inline const QXfloat&	GetDistForGeneration() { return _distForGeneration; };

		/**
		 * @brief Set the maximum number of cubes a generator can create
		 *
		 * @param newNbMaxOfCubes the maximum number of cubes a generator can create
		 */
		inline void				SetNbMaxOfCubes(const QXuint& newNbMaxOfCubes) { _nbMaxOfCubes = newNbMaxOfCubes; };

		/**
		 * @brief Get the maximum number of cubes a generator can create
		 *
		 * @param const QXuint& the maximum number of cubes a generator can create
		 */
		inline const QXuint&	GetNbMaxOfCubes() { return _nbMaxOfCubes; };

		/**
		 * @brief Set the application reference
		 *
		 * @param app the application reference
		 */
		inline void				SetApplication(Core::Platform::Application* app) { _app = app; CreateGenerator(); };

		#pragma endregion

		#pragma endregion

		CLASS_REGISTRATION(Quantix::Core::DataStructure::Component, Quantix::Core::Components::Behaviour);
	};
}
#endif //__CUBEGENERATOR_H__