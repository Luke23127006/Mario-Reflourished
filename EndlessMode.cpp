#include "EndlessMode.h"

void EndlessMode::initMaps()
{
	this->map = nullptr;
	this->maps.push_back(new Map(MAPS_DIRECTORY + "Level 3/Map0.png", sf::Vector2f(0.f, 0.f)));

	sf::Image image;
	image.loadFromFile(MAPS_DIRECTORY + "Level 3/Map0.png");
	this->spikeWall = new SpikeWall(sf::Vector2f(-2.f * CAMERA_FOLLOW_DISTANCE, 0.f));
	this->spikeWall->move(sf::Vector2f(0.f, TILE_SIZE * image.getSize().y - this->spikeWall->getGlobalBounds().height));

	for (int i = 0; i < image.getSize().x; i++)
		for (int j = 0; j < image.getSize().y; j++)
		{
			sf::Color color = image.getPixel(i, j);
			int colorCode = color.toInteger();

			if (color == sf::Color(255, 0, 0, 255))
			{
				this->player = EntityFactory::createPlayer(sf::Vector2f(i * 50.f, j * 50.f));
				this->entities.insert(this->entities.begin(), this->player);
			}

			if (ColorManager::getObject.find(colorCode) != ColorManager::getObject.end())
			{
				std::string enemyName = ColorManager::getObject[colorCode];

				if (enemyName == "goomba")
				{
					this->entities.push_back(new Goomba(sf::Vector2f(i * 50.f, j * 50.f)));
				}
				else if (enemyName == "koopa")
				{
					this->entities.push_back(new Koopa(sf::Vector2f(i * 50.f, j * 50.f)));
				}
			}
		}
}

EndlessMode::EndlessMode() :
	numMap(18),
	cameraPosition(SCREEN_WIDTH / 2),
	gameSpeed(SPIKE_WALL_SPEED),
	spikeSpeed(100.f)
{
	this->camera.setPosition(sf::Vector2f(cameraPosition, TILE_SIZE * MINIMAP_HEIGHT - SCREEN_HEIGHT / 2));
	this->cameraHeightMax = this->camera.getPosition().y;
	this->initMaps();
}

EndlessMode::~EndlessMode()
{
	while (!this->maps.empty())
	{
		delete this->maps.back();
		this->maps.pop_back();
	}

	while (!this->entities.empty())
	{
		delete this->entities.back();
		this->entities.pop_back();
	}

	delete this->spikeWall;
}

void EndlessMode::addMap(std::string fileName)
{
	sf::Vector2f position = this->maps.back()->getPosition() + TILE_SIZE * sf::Vector2f(this->maps.back()->getSize().x, 0.f);
	this->maps.push_back(new Map(fileName, position));
	sf::Image image;
	image.loadFromFile(fileName);
	for (int i = 0; i < image.getSize().x; i++)
		for (int j = 0; j < image.getSize().y; j++)
		{
			//sf::Color color = image.getPixel(i, j);
			//int colorCode = color.toInteger();

			/*switch (ColorManager::getEnemyAsColor[colorCode])
			{
			case EnemyType::GOOMBA:
				this->entities.push_back(new Goomba(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE)));
				break;
			case EnemyType::KOOPA:
				this->entities.push_back(new Koopa(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE)));
				break;
			default:
				break;
			}*/
		}
}

void EndlessMode::updateMap(float deltaTime)
{
	for (auto& m : this->maps)
	{
		m->update(deltaTime, this->entities);
	}

	if (this->cameraPosition > this->maps.back()->getPosition().x + this->maps.back()->getSize().x * TILE_SIZE - SCREEN_WIDTH)
	{
		int i;
		do
		{
			i = randomize(1, this->numMap);
		} while (i == 16 || i == 17);

		if (i != 15)
		{
			this->addMap(MAPS_DIRECTORY + "Level 3/Map" + std::to_string(i) + ".png");
		}
		else
		{
			this->addMap(MAPS_DIRECTORY + "Level 3/Map" + std::to_string(i) + ".png");
			this->addMap(MAPS_DIRECTORY + "Level 3/Map" + std::to_string(i + 1) + ".png");
			this->addMap(MAPS_DIRECTORY + "Level 3/Map" + std::to_string(i + 2) + ".png");
		}
	}

	if (this->cameraPosition > this->maps.front()->getPosition().x + this->maps.front()->getSize().x * TILE_SIZE + SCREEN_WIDTH)
	{
		std::cout << "Deleted\n";
		delete this->maps.front();
		this->maps.erase(this->maps.begin());
	}
}

void EndlessMode::updateCollision()
{
	for (auto& e : this->entities)
	{
		if (!e->getEnabled()) continue;
		for (auto& m : this->maps)
		{
			Collision::handle_entity_map(e, m);
		}
		Collision::handle_entity_spikeWall(e, this->spikeWall);
	}

	AdventureMode::updateCollision();
}

void EndlessMode::updateCamera(float deltaTime)
{
	if (this->player->isDead()) return;

	this->gameSpeed = std::min(this->gameSpeed + SPIKE_WALL_ACCERATION * deltaTime, SPIKE_WALL_MAX_SPEED); // spike speed up

	// player can not leave the spike wall far away
	if (this->player->getPosition().x - SCREEN_WIDTH * 1.0f > this->spikeWall->getPosition().x)
	{
		this->spikeSpeed = std::max(this->gameSpeed, this->player->getVelocity().x);
	}

	this->spikeWall->move(sf::Vector2f(spikeSpeed * deltaTime, 0.f));

	float pos1 = this->player->getPosition().x;
	float pos2 = this->spikeWall->getPosition().x + SCREEN_WIDTH * 0.56f;
	this->cameraPosition = std::max(pos1, pos2);
	this->camera.update(deltaTime, sf::Vector2f(this->cameraPosition, this->player->getPosition().y + SCREEN_HEIGHT * 0.4f));

	if (this->camera.getPosition().y > this->cameraHeightMax)
	{
		this->camera.setPosition(sf::Vector2f(this->camera.getPosition().x, this->cameraHeightMax));
	}
}

void EndlessMode::render(sf::RenderWindow& target)
{
	target.setView(this->camera.getView(target.getSize()));
	for (auto& e : this->entities)
	{
		e->render(target);
	}
	for (auto& m : this->maps)
	{
		m->render(target);
	}
	spikeWall->render(target);
}

GameState EndlessMode::getNextScene()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return GameState::PAUSE;
	}
	return GameState::LEVEL3;
}