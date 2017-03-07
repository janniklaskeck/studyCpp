#include "World.h"
#include "Constants.h"
#include "PhysicsEngine.h"

void World::Update()
{
	CurrentMilliseconds += UPDATE_INTERVAL_MS;
	for (int i = 0; i < GameObjects.size(); i++)
	{
		GameObject* Object = GameObjects[i].get();
		if (Object)
		{
			Object->Update();
		}
	}
}

void World::AddGameObject(GameObject* NewGameObject)
{
	GameObjects.push_back(std::shared_ptr<GameObject>(NewGameObject));
	NewGameObject->Register(this);
}

void World::AddGameObject(std::shared_ptr<GameObject> NewGameObject)
{
	GameObjects.push_back(NewGameObject);
	NewGameObject->Register(this);
}

World::World()
{
	Physics = std::make_unique<PhysicsEngine>();
}

World::~World()
{
}
