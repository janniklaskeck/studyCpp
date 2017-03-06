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
	App->GameWorld->AddGameObject(BuildStaticBox(glm::vec2(0, WindowSize.y - 10), glm::vec2(WindowSize.x, 10)));
	App->GameWorld->AddGameObject(BuildStaticBox(glm::vec2(0, 0), glm::vec2(WindowSize.x, 10)));
	App->GameWorld->AddGameObject(BuildStaticBox(glm::vec2(0, 0), glm::vec2(10, WindowSize.y)));
	App->GameWorld->AddGameObject(BuildStaticBox(glm::vec2(WindowSize.x - 10, 0), glm::vec2(10, WindowSize.y)));
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
	Description_P1.PhysicsShape.Size = sf::Vector2f(Size.width, Size.height);
	Description_P1.Type = DYNAMIC;

	PhysicsState State_P1(sf::Vector2f(50, 600), sf::Vector2f());
	PlayerOne->AddComponent(new PhysicsComponent(State_P1, Description_P1));
	PlayerOne->AddComponent(new InputComponent(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::A, sf::Keyboard::Space));

	PhysicsDescription Description_P2{};
	Description_P2.Mass = 1.0f;
	Description_P2.PhysicsShape.Type = AABB;
	Description_P2.PhysicsShape.Size = sf::Vector2f(Size.width, Size.height);
	Description_P2.Type = DYNAMIC;

	PhysicsState State_P2(sf::Vector2f(1000, 600), sf::Vector2f());
	PlayerTwo->AddComponent(new RenderComponent(ResourceManager::LoadTexture("Assets\\player2.png")));
	PlayerTwo->AddComponent(new PhysicsComponent(State_P2, Description_P2));
	PlayerTwo->AddComponent(new InputComponent(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::RControl));


	App->GameWorld->AddGameObject(PlayerOne);
	App->GameWorld->AddGameObject(PlayerTwo);
}

std::shared_ptr<GameObject> VersusPhysicsGame::BuildStaticBox(glm::vec2 Pos, glm::vec2 Size)
{
	std::shared_ptr<GameObject> Bottom = std::make_shared<GameObject>(11);
	PhysicsDescription Description{};
	Description.Mass = 1.0;
	Description.PhysicsShape.Type = AABB;
	Description.PhysicsShape.Size = sf::Vector2f(Size.x, Size.y);
	PhysicsState State(sf::Vector2f(Pos.x, Pos.y), sf::Vector2f());
	Bottom->AddComponent(new PhysicsComponent(State, Description));
	Shape Box;
	Box.Type = AABB;
	Box.Size.x = Size.x;
	Box.Size.y = Size.y;
	Bottom->AddComponent(new RenderComponent(Box));
	return Bottom;
}
