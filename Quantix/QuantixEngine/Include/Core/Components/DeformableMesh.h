#ifndef __DEFORMABLEMESH_H__
#define __DEFORMABLEMESH_H__

#include "rttrEnabled.h"
#include "Core/MathHeader.h"
#include "Core./DataStructure//Component.h"
#include "Resources/Scene.h"
#include "Physic/Joint.h"
#include "Core/Platform/Application.h"

namespace Quantix::Core::Components
{
	struct QUANTIX_API DeformableMesh : public Core::DataStructure::Component
	{
		Math::QXvec3 cubeSize {Math::QXvec3(1,1,1)};

		QXuint numCubeInWidth {1};
		QXuint numCubeInHeight {1};
		QXuint numCubeInDepth {1};

		Physic::Joint joint;

		Core::DataStructure::GameObject3D**** gameobjects;

		/**
		 * @brief Construct a new Deformable Mesh object
		 * 
		 */
		DeformableMesh() = default;

		/**
		 * @brief Construct a new Deformable Mesh object
		 * 
		 * @param src DeformableMesh to copy
		 */
		DeformableMesh(const DeformableMesh& src) = default;

		/**
		 * @brief Construct a new Deformable Mesh object
		 * 
		 * @param src DeformableMesh to move
		 */
		DeformableMesh(DeformableMesh&& src) = default;

		/**
		 * @brief Destroy the Deformable Mesh object
		 * 
		 */
		~DeformableMesh() = default;

		/**
		 * @brief Operator = per copy
		 * 
		 * @param other DeformableMesh to copy
		 * @return DeformableMesh& new DeformableMesh
		 */
		DeformableMesh& operator=(const DeformableMesh& other) noexcept = default;

		/**
		 * @brief Operator = per move
		 * 
		 * @param other DeformableMesh to move
		 * @return DeformableMesh& new DeformableMesh
		 */
		DeformableMesh& operator=(DeformableMesh&& other) noexcept = default;

		/**
		 * @brief Create a New DeformableMesh
		 * 
		 * @return DeformableMesh* 
		 */
		DeformableMesh* Copy() const override;

		/**
		 * @brief Init a new DeformableMesh
		 * 
		 * @param par GameComponent who has this component
		 */
		void Init(DataStructure::GameComponent* par) override;

		/**
		 * @brief fully Generate the deformableMesh 
		 * 
		 * @param scene Current scene
		 */
		void Generate(Core::Platform::Application* app);

		void MoveCube(Core::Platform::Application* app);
		void CreateCube(Core::Platform::Application* app);

		/**
		 * @brief addComponent for the deformableMesh during Generation
		 * 
		 * @param object 
		 */
		void AddComponent(DataStructure::GameObject3D* object, Core::Platform::Application* app);

		/**
		 * @brief Get the Num Width object
		 * 
		 * @return QXuint 
		 */
		QXuint GetNumWidth() { return numCubeInWidth; }

		/**
		 * @brief Set the Num Width object
		 * 
		 * @param i 
		 */
		void SetNumWidth(QXuint i) { numCubeInWidth = i; }

		/**
		 * @brief Get the Break Force object
		 * 
		 * @return QXuint 
		 */
		QXuint GetBreakForce() { return joint.breakForce; }

		/**
		 * @brief Set the Break Force object
		 * 
		 * @param i 
		 */
		void SetBreakForce(QXuint i) { joint.breakForce = i; }

		/**
		 * @brief Get the Break Torque object
		 * 
		 * @return QXuint 
		 */
		QXuint GetBreakTorque() { return joint.breakTorque; }

		/**
		 * @brief Set the Break Torque object
		 * 
		 * @param i 
		 */
		void SetBreakTorque(QXuint i) { joint.breakTorque = i; }

		CLASS_REGISTRATION(Core::DataStructure::Component);
	};
}

#endif
