#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <iostream>
#include <unordered_map>

#include "Type.h"

namespace Quantix::Resources
{
	class Scene;
}

namespace Quantix::Core::DataStructure
{
	class ResourcesManager;

	class SceneManager
	{
	private:

		std::unordered_map<QXuint, QXstring> _scenes;

		QXuint _currentId{ 0 };
		QXuint _nextId{ 0 };

		Quantix::Resources::Scene* _currentScene{ nullptr };
		Quantix::Resources::Scene* _nextScene{ nullptr };

	public:
#pragma region Constructors

		SceneManager() noexcept;
		SceneManager(const SceneManager& sceneManager) = delete;
		SceneManager(SceneManager&& sceneManager) = delete;
		~SceneManager() = default;

#pragma endregion

#pragma region Functions

		void Update(const ResourcesManager& resourcesManager) noexcept;
		Quantix::Resources::Scene* Load(QXuint id, ResourcesManager* manager) noexcept;

#pragma region Operators

		SceneManager& operator=(const SceneManager& object) = delete;
		SceneManager& operator=(SceneManager&& object) = delete;

#pragma endregion

#pragma region Accessors

#pragma endregion

#pragma endregion
	};
}
#endif
