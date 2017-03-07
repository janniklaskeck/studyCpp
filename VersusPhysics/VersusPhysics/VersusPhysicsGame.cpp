#include "VersusPhysicsGame.h"
#include "RenderComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "UpdateComponent.h"
#include "GameObject.h"


VersusPhysicsGame::VersusPhysicsGame()
{
	App = std::make_unique<Application>();
}


VersusPhysicsGame::~VersusPhysicsGame()
{
}

void VersusPhysicsGame::Setup()
{
	App->Start();
	BuildLevel();
	CreatePlayers();
}

void VersusPhysicsGame::Start()
{
	App->Init();
	App->GameLoop();
	App->Stop();
}

void VersusPhysicsGame::BuildLevel()
{
	sf::Vector2u WindowSize = App->GetWindowSize();
	App->GameWorld->AddGameObject(BuildStaticBox(Vector2(0.0f, WindowSize.y - 10.0f), Vector2(WindowSize.x, 10.0f)));
	App->GameWorld->AddGameObject(BuildStaticBox(Vector2(0.0f, 0.0f), Vector2(WindowSize.x, 10.0f)));
	App->GameWorld->AddGameObject(BuildStaticBox(Vector2(0.0f, 0.0f), Vector2(10.0f, WindowSize.y)));
	App->GameWorld->AddGameObject(BuildStaticBox(Vector2(WindowSize.x - 10.0f, 0.0f), Vector2(10.0f, WindowSize.y)));
}

void VersusPhysicsGame::CreatePlayers()
{
	std::shared_ptr<GameObject> PlayerOne = std::make_shared<GameObject>(1);
	std::shared_ptr<GameObject> PlayerTwo = std::make_shared<GameObject>(2);


	PlayerOne->AddComponent(new RenderComponent(ResourceManager::LoadTexture("Assets\\player1.png")));

	sf::FloatRect Size(0.0f, 0.0f, 16.0f, 16.0f);

	PhysicsDescription Description_P1{};
	Description_P1.Mass = 1.0f;
	Description_P1.PhysicsShape.Type = AABB;
	Description_P1.PhysicsShape.Size = Vector2(Size.width, Size.height);
	Description_P1.Type = DYNAMIC;

	PhysicsState State_P1(Vector2(50, 600), Vector2());
	PlayerOne->AddComponent(new PhysicsComponent(State_P1, Description_P1));
	PlayerOne->AddComponent(new InputComponent(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::A, sf::Keyboard::Space));

	PhysicsDescription Description_P2{};
	Description_P2.Mass = 1.0f;
	Description_P2.PhysicsShape.Type = AABB;
	Description_P2.PhysicsShape.Size = Vector2(Size.width, Size.height);
	Description_P2.Type = DYNAMIC;

	PhysicsState State_P2(Vector2(1000, 600), Vector2());
	PlayerTwo->AddComponent(new RenderComponent(ResourceManager::LoadTexture("Assets\\player2.png")));
	PlayerTwo->AddComponent(new PhysicsComponent(State_P2, Description_P2));
	PlayerTwo->AddComponent(new InputComponent(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::RControl));


	App->GameWorld->AddGameObject(PlayerOne);
	App->GameWorld->AddGameObject(PlayerTwo);
}

std::shared_ptr<GameObject> VersusPhysicsGame::BuildStaticBox(Vector2 Pos, Vector2 Size)
{
	std::shared_ptr<GameObject> Bottom = std::make_shared<GameObject>(11);
	PhysicsDescription Description{};
	Description.Mass = 1.0;
	Description.PhysicsShape.Type = AABB;
	Description.PhysicsShape.Size = Vector2(Size.X, Size.Y);
	Description.Resitution = 0.0f;
	PhysicsState State(Vector2(Pos.X, Pos.Y), Vector2());
	Bottom->AddComponent(new PhysicsComponent(State, Description));
	Shape Box;
	Box.Type = AABB;
	Box.Size.X = Size.X;
	Box.Size.Y = Size.Y;
	Bottom->AddComponent(new RenderComponent(Box));
	return Bottom;
}
