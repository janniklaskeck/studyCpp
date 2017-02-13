#pragma once
#include "Application.h"

#include <memory>

class VersusPhysicsGame
{
public:
	VersusPhysicsGame();
	~VersusPhysicsGame();

	void Setup();

	void Start();

private:
	std::unique_ptr<Application> App;

	void BuildLevel();
	void CreatePlayers();

	std::shared_ptr<GameObject> BuildStaticBox(glm::vec2 Pos, glm::vec2 Size);
};

