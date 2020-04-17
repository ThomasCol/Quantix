#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <map>

#include "Type.h"

namespace Quantix::Core::DataStructure
{
	class ResourcesManager;

	class SceneManager
	{
	private:

		std::unordered_map<QXuint, QXstring> _scenes;

		QXuint _currentId{ 0 };
		QXuint _nextId{ 0 };

		Scene* _currentScene{ nullptr };
		Scene* _nextScene{ nullptr };

	public:
#pragma region Constructors

		SceneManager() noexcept;
		SceneManager(const SceneManager& sceneManager) = delete;
		SceneManager(SceneManager&& sceneManager) = delete;
		~SceneManager() = default;

#pragma endregion

#pragma region Functions

		void Update(const ResourcesManager& resourcesManager) noexcept;
		Scene* Load(QXuint id, ResourcesManager* manager) noexcept;

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
