#pragma once
#include "GameObject.h"

#include <memory>
#include <vector>

class World
{
public:
	void Update();
	void AddGameObject(GameObject* NewGameObject);
	void AddGameObject(std::shared_ptr<GameObject> NewGameObject);

	double GetElapsedTime() const
	{
		return CurrentMilliseconds;
	}

	std::vector<std::shared_ptr<GameObject>> GetGameObjects() const
	{
		return GameObjects;
	}

	World();
	~World();

private:
	double CurrentMilliseconds;
	std::vector<std::shared_ptr<GameObject>> GameObjects;
};

