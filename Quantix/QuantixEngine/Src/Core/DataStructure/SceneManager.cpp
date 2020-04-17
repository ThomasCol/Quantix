#include "../Include/Core/DataStructure/SceneManager.h"

namespace Quantix::Core::DataStructure
{
	SceneManager::SceneManager() noexcept
	{}

	void SceneManager::Update(const ResourcesManager& resourcesManager) noexcept	
	{
	}

	Scene* SceneManager::Load(QXuint id, ResourcesManager* manager) noexcept
	{
		if (id != _currentId)
		{
			_nextScene = manager->CreateScene(_scenes[id]);
			return _nextScene;
		}
		else
		{
			_currentScene->Reset();
			return _currentScene;
		}
	}
}