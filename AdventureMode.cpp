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

			if (ColorManager::getObject.find(colorCode) != ColorManager::getObject.end())
			{
				std::string name = ColorManager::getObject[colorCode];
				
				if (name == "player")
				{
					this->player = EntityFactory::createPlayer(sf::Vector2f(i * 50.f, j * 50.f));
					this->entities.insert(this->entities.begin(), this->player);
				}
				if (name == "goomba")
				{
					Goomba* goomba = new Goomba(sf::Vector2f(i * 50.f, j * 50.f));
					this->entities.push_back(goomba);
					this->enemies.push_back(goomba);
				}
				else if (name == "koopa")
				{
					Koopa* koopa = new Koopa(sf::Vector2f(i * 50.f, j * 50.f));
					this->entities.push_back(koopa);
					this->enemies.push_back(koopa);
				}
			}
		}
	this->setEnemiesBehaviors();
}

AdventureMode::AdventureMode()
{
	this->cameraOrigin = sf::Vector2f(0.f, 0.f);
	this->map = nullptr;
	this->player = nullptr;
	this->entities.clear();
}

AdventureMode::AdventureMode(std::string fileName, sf::Vector2f cameraOrigin)
{
	if (fileName == MAPS_DIRECTORY + "Level 1.png")
		typeMap = GameState::LEVEL1;
	else if (fileName == MAPS_DIRECTORY + "Level 2.png")
		typeMap = GameState::LEVEL2;
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

	while (!this->coins.empty())
	{
		delete this->coins.back();
		this->coins.pop_back();
	}
}

void AdventureMode::setEnemiesBehaviors()
{
	for (auto& enemy : enemies)
	{
		if (isType<Goomba>(*enemy))
		{
			enemy->addBehavior(std::make_shared<Pace>(enemy, player, GOOMBA_PACE_SPEED));
			enemy->addBehavior(std::make_shared<FollowPlayer>(enemy, player, GOOMBA_FOLLOW_SPEED));
			enemy->addBehavior(std::make_shared<EnemiesJump>(enemy, player));
		}
		else if (isType<Koopa>(*enemy))
		{
			enemy->addBehavior(std::make_shared<Pace>(enemy, player, KOOPA_PACE_SPEED));
			enemy->addBehavior(std::make_shared<FollowPlayer>(enemy, player, KOOPA_FOLLOW_SPEED));
			enemy->addBehavior(std::make_shared<EnemiesJump>(enemy, player));
			
		}
	}
}
void AdventureMode::update(float deltaTime, bool& held)
{
	this->updateEntities(deltaTime);
	this->updateCollision();
	this->updateMap(deltaTime);
	this->updateCamera(deltaTime);
	this->updateLastPosition();
}

void AdventureMode::updateEntities(float deltaTime)
{
	std::vector<Entity*> newEntities;
	auto it = this->entities.begin();

	while (it != this->entities.end()) {
		auto& e = *it;
		e->update(deltaTime);

		if (isType<Player>(*e))
		{
			Bullet* bullet = dynamic_cast<Player*>(e)->shoot();
			if (bullet) newEntities.push_back(bullet);
		}
		

		if (!isType<Player>(*e) && e->isDead())
		{
			if (isType<Koopa>(*e))
			{
				newEntities.push_back(new Shell(e->getPosition()));
			}
			delete e;
			it = this->entities.erase(it);
		}
		else
		{
			++it;
		}
	}

	this->entities.insert(this->entities.end(), newEntities.begin(), newEntities.end());
}

void AdventureMode::updateMap(float deltaTime)
{
	this->map->update(deltaTime, this->entities);
}

void AdventureMode::updateCollision()
{
	if (map)
		for (auto& e : this->entities)
		{
			if (!e->getEnabled()) continue;
			Collision::handle_entity_map(e, this->map);
		}

	for (int i = 0; i < this->entities.size(); i++)
	{
		for (int j = 0; j < this->entities.size(); j++)
		{
			if (i == j) continue;
			auto& a = this->entities[i];
			auto& b = this->entities[j];
			if (!a->getEnabled() || !b->getEnabled()) continue;

			if (isType<Player>(*a))
			{
				if (isDerivedFrom<Enemy>(*b))
				{
					Collision::handle_player_enemy(dynamic_cast<Player*>(a), dynamic_cast<Enemy*>(b));
				}
				if (isDerivedFrom<Shell>(*b))
				{
					Collision::handle_entity_shell(dynamic_cast<Player*>(a), dynamic_cast<Shell*>(b));
				}
				if (isDerivedFrom<PowerUp>(*b))
				{
					Collision::handle_player_powerUp(dynamic_cast<Player*>(a), dynamic_cast<PowerUp*>(b));
				}
			}

			if (isDerivedFrom<Enemy>(*a))
			{
				if (isDerivedFrom<Shell>(*b))
				{
					Collision::handle_entity_shell(dynamic_cast<Enemy*>(a), dynamic_cast<Shell*>(b));
				}
				if (isDerivedFrom<Bullet>(*b))
				{
					Collision::handle_bullet_enemy(dynamic_cast<Bullet*>(b), dynamic_cast<Enemy*>(a));
				}
			}
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

void AdventureMode::render(sf::RenderWindow& target)
{
	target.setView(this->camera.getView(target.getSize()));
	for (auto& e : this->entities)
		e->render(target);
	this->map->render(target);
}

GameState AdventureMode::getNextScene()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return GameState::PAUSE;
	if (typeMap == GameState::LEVEL1)
	{
		return GameState::LEVEL1;
	}
	else if (typeMap == GameState::LEVEL2)
	{
		return GameState::LEVEL2;
	}
}
