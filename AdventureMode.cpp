#include "AdventureMode.h"
#include <cmath>

void AdventureMode::initMap(std::string fileName)
{
	this->map = new Map(fileName, sf::Vector2f(0.f, 0.f));
}

void AdventureMode::addEntitiesAndCoins(std::string fileName, sf::Vector2f cornerPosition)
{
	sf::Image image;
	image.loadFromFile(fileName);

	this->entities.reserve(500);
	for (int i = 0; i < image.getSize().x; i++)
		for (int j = 0; j < image.getSize().y; j++)
		{
			sf::Color color = image.getPixel(i, j);
			int colorCode = color.toInteger();

			if (ColorManager::getObject.find(colorCode) != ColorManager::getObject.end())
			{
				std::string name = ColorManager::getObject[colorCode];
				sf::Vector2f position = cornerPosition + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);

				if (name == "player")
				{
					this->player = EntityFactory::createPlayer(position);
					this->player->setCoins(&this->coins);
					this->entities.insert(this->entities.begin(), this->player);
				}
				else if (name == "coin" || name == "coin under water")
				{
					Coin* coin = new Coin(cornerPosition + sf::Vector2f(i * TILE_SIZE + 0.5f * (TILE_SIZE - COIN_WIDTH), j * TILE_SIZE + 0.5f * (TILE_SIZE - COIN_HEIGHT)));
					this->coins.push_back(coin);
				}
				else if (name == "goomba")
				{
					Entity* goomba  = EntityFactory::createGoomba(position);
					this->entities.push_back(goomba);
				}
				else if (name == "koopa")
				{
					Entity* koopa = EntityFactory::createKoopa(position);
					this->entities.push_back(koopa);
				}
				else if (name == "bird")
				{
					Entity* bird = EntityFactory::createBird(position);
					this->entities.push_back(bird);
				}
				else if (name == "bowser")
				{
					Entity* bowser = EntityFactory::createBowser(position);
					this->entities.push_back(bowser);
				}
				else if (name == "wukong")
				{
					Entity * wukong = EntityFactory::createWukong(position);
					this->entities.push_back(wukong);
				}
			}
			/*if (!this->entities.empty())
			{
				this->entities.back()->setAddressOfWorld(this->entities);
				if(this->map) this->entities.back()->setMap(this->map);
			}*/
		}
	for (auto& entity : this->entities)
	{
		entity->setAddressOfWorld(this->entities);
		entity->setMap(this->map);
	}
	this->setEnemiesBehaviors();
}

AdventureMode::AdventureMode()
{
	this->typeMap = GameState::LEVEL1;
	this->cameraOrigin = sf::Vector2f(0.f, 0.f);
	this->map = nullptr;
	this->player = nullptr;
	this->entities.clear();
}

AdventureMode::AdventureMode(std::string fileName, sf::Vector2f cameraOrigin)
{
	if (fileName == MAPS_DIRECTORY + "Level 1.png")
	{
		typeMap = GameState::LEVEL1;
		currentMusic = "MARIO_MAIN_THEME";
	}
	else if (fileName == MAPS_DIRECTORY + "Level 2.png")
	{
		typeMap = GameState::LEVEL2;
		currentMusic = "MARIO_UNDERGROUND";
	}
	Resources::sounds[currentMusic].play();
	Resources::sounds[currentMusic].setLoop(true);
	this->cameraOrigin = cameraOrigin;
	this->initMap(fileName);
	this->entities.reserve(100);
	this->addEntitiesAndCoins(fileName, this->map->getPosition());

}

AdventureMode::~AdventureMode()
{
	if (this->map) delete this->map;

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
	for (auto& entity : this->entities)
	{
		Enemy* enemy = nullptr;
		if (isDerivedFrom<Enemy>(*entity)) enemy = dynamic_cast<Enemy*>(entity);
		else continue;

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
		else if (isType<Bird>(*enemy))
		{
			enemy->addBehavior(std::make_shared<PaceFly>(enemy, player, BIRD_PACE_X, BIRD_PACE_Y, BIRD_PACE_SPEED));
			enemy->addBehavior(std::make_shared<FollowPlayer>(enemy, player, BIRD_FOLLOW_SPEED, BIRD_DETECTION_RADIUS, 6));

		}
		else if (isType<Bowser>(*enemy))
		{
			enemy->addBehavior(std::make_shared<Pace>(enemy, player, BOWSER_PACE_SPEED));
			enemy->addBehavior(std::make_shared<FollowPlayer>(enemy, player, BOWSER_FOLLOW_SPEED,BOWSER_DETECTION_RADIUS, 5));
			enemy->addBehavior(std::make_shared<FireAttack>(enemy, player, BOWSER_DETECTION_RADIUS, 3));
		}

		else if (isType<Wukong>(*enemy))
		{
			enemy->addBehavior(std::make_shared<PaceFly>(enemy, player, WUKONG_PACE_X, WUKONG_PACE_Y, WUKONG_PACE_SPEED));
			enemy->addBehavior(std::make_shared<WukongAttack>(enemy, player, WUKONG_FOLLOW_SPEED, WUKONG_DETECTION_RADIUS, 5));
			enemy->addBehavior(std::make_shared<MagicRodAttack>(enemy, player, WUKONG_DETECTION_RADIUS, 5));
			//enemy->addBehavior(std::make_shared<FireAttack>(enemy, player, WUKONG_DETECTION_RADIUS, 3));
		}
	}
}
void AdventureMode::update(float deltaTime, bool& held)
{

	this->updateEntities(deltaTime);
	this->updateCoins(deltaTime);
	this->updateCollision();
	this->updateMap(deltaTime);
	this->updateCamera(deltaTime);
	this->updateLastPosition();
	
}

void AdventureMode::updateEntities(float deltaTime)
{
	auto it = this->entities.begin();

	sf::Vector2f center = this->camera.getPosition();
	while (it != this->entities.end()) 
	{
		auto& e = *it;
		sf::Vector2f direction = center - e->getPosition();
		float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
		if (distance < UPDATE_DISTANCE || isType<Player>(*e)) e->update(deltaTime);

		if (!isType<Player>(*e) && e->isDead())
		{
			delete e;
			it = this->entities.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void AdventureMode::updateCoins(float deltaTime)
{
	for (auto& coin : this->coins)
	{
		coin->update(deltaTime);
	}

	int counter = 0;
	for (auto& coin : coins)
	{
		if (coin->isCollected())
		{
			delete coins.at(counter);
			coins.erase(coins.begin() + counter);
			counter--;
		}
		counter++;
	}
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
			e->setOnGround(false);
			e->setUnderWater(false);
			Collision::handle_entity_map(e, this->map);
		}

	for (auto& coin : this->coins)
	{
		if (!coin->getEnabled()) continue;
		Collision::handle_player_coin(this->player, coin);
	}

	for (int i = 0; i < this->entities.size(); i++)
		for (int j = i + 1; j < this->entities.size(); j++)
		{
			auto& b = this->entities[i];
			auto& a = this->entities[j];
			if (!a->getEnabled() || !b->getEnabled()) continue;
			Collision::handle_entity_entity(a, b);
		}
}

void AdventureMode::updateCamera(float deltaTime)
{
	if (!this->player) return;
	if (!this->player->getEnabled()) return;
	this->camera.update(deltaTime, this->player->getPosition() + sf::Vector2f(this->player->getGLobalBounds().width * 0.5f, 0.f) + this->cameraOrigin);

	sf::Vector2f position = this->camera.getPosition();
	position.x = std::max(position.x, this->map->getPosition().x + this->camera.getSize().x / 2);
	position.x = std::min(position.x, this->map->getPosition().x + this->map->getSize().x * TILE_SIZE - this->camera.getSize().x / 2);

	position.y = std::max(position.y, this->map->getPosition().y + this->camera.getSize().y / 2 - this->player->getGLobalBounds().height * 4);
	position.y = std::min(position.y, this->map->getPosition().y + this->map->getSize().y * TILE_SIZE - this->camera.getSize().y / 2);

	if (this->map->getSize().x * TILE_SIZE < this->camera.getSize().x)
	{
		position.x = this->map->getSize().x * TILE_SIZE / 2;
	}

	this->camera.setPosition(position);
}

void AdventureMode::updateLastPosition()
{
	for (auto& e : this->entities)
		e->updateLastPosition();
}

void AdventureMode::render(sf::RenderWindow& target)
{
	target.setView(this->camera.getView(target.getSize()));
	sf::Vector2f center = this->camera.getPosition();

	for (auto& e : this->entities)
	{
		sf::Vector2f direction = center - e->getPosition();
		float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
		if (distance < RENDER_DISTANCE) e->render(target);
	}
	for (auto& coin : this->coins)
	{
		sf::Vector2f direction = center - coin->getPosition();
		float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
		if (distance < RENDER_DISTANCE) coin->render(target);
	}
	if (this->map) this->map->render(target, center);
}

GameState AdventureMode::getNextScene()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !this->player->isDying())
		return GameState::PAUSE;
	if (this->player->isDying())
	{
		cooldownTime -= 0.001;
		if (cooldownTime <= 0)
			return typeMap;
		return GameState::REPLAY;

	}
	return typeMap;
}
