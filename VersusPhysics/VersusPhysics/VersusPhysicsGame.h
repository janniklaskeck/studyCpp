#pragma once
#include "Application.h"
#include "Vector2.hpp"
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

	std::shared_ptr<GameObject> BuildStaticBox(Vector2 Pos, Vector2 Size);
};

