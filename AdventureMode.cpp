#include "AdventureMode.h"

void AdventureMode::initMap(std::string fileName)
{
	this->map = new Map(fileName, sf::Vector2f(0.f, 0.f));
	
	sf::Image image;
	image.loadFromFile(fileName);

	this->entities.clear();
	for (int i = 0; i < image.getSize().x; i++)
		for (int j = 0; j < image.getSize().y; j++)
		{
			sf::Color color = image.getPixel(i, j);
			int colorCode = color.toInteger();

			if (color == sf::Color(255, 0, 0, 255))
			{
				this->player = new Player(sf::Vector2f(42, 48), sf::Vector2f(i * 50.f, j * 50.f));
				this->entities.insert(this->entities.begin(), this->player);
			}

			switch (ColorManager::getEnemyAsColor[colorCode])
			{
			case EnemyType::GOOMBA:
				this->entities.push_back(new Goomba(sf::Vector2f(i * 50.f, j * 50.f)));
				break;
			default:
				break;
			}
		}
}

AdventureMode::AdventureMode(std::string fileName, sf::Vector2f cameraOrigin)
{
	this->cameraOrigin = cameraOrigin;
	this->initMap(fileName);
}

AdventureMode::~AdventureMode()
{
	delete this->map;

	while (!this->entities.empty())
	{
		delete this->entities.back();
		this->entities.pop_back();
	}
}

void AdventureMode::update(float deltaTime)
{
	this->updateEntities(deltaTime);
	this->updateMap(deltaTime);
	this->updateCollision();
	this->updateCamera(deltaTime);
	this->updateLastPosition();
}

void AdventureMode::updateEntities(float deltaTime)
{
	int counter = 0;
	for (auto& e : this->entities)
	{
		e->update(deltaTime);
		if (typeid(*e) != typeid(Player) && e->isDead())
		{
			delete e;
			this->entities.erase(this->entities.begin() + counter);
			counter--;
		}
		counter++;
	}
}

void AdventureMode::updateMap(float deltaTime)
{
	this->map->update(deltaTime);
}

void AdventureMode::updateCollision()
{
	for (auto& e : this->entities)
	{
		if (!e->getEnabled()) continue;
		Collision::handle_entity_map(e, this->map);

		if (typeid(*e) != typeid(Player))
		{
			Collision::handle_player_enemy(this->player, dynamic_cast<Enemy*>(e));
		}
	}
}

void AdventureMode::updateCamera(float deltaTime)
{
	if (!this->player) return;
	if (!this->player->getEnabled()) return;
	this->camera.update(deltaTime, this->player->getPosition() + sf::Vector2f(this->player->getGLobalBounds().width * 0.5f, 0.f) + this->cameraOrigin);
}

void AdventureMode::updateLastPosition()
{
	for (auto& e : this->entities)
		e->updateLastPosition();
}

void AdventureMode::render(sf::RenderWindow& target, bool& held)
{
	target.setView(this->camera.getView(target.getSize()));
	for (auto& e : this->entities)
		e->render(target);
	this->map->render(target);
}

GameState AdventureMode::getNextScene()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return GameState::SELECT_LEVEL;
	return GameState::ADVENTURE_MODE;
}
