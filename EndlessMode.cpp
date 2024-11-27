#include "EndlessMode.h"

void EndlessMode::initMaps()
{
	maps.push_back(new Map(MAPS_DIRECTORY + "Level 3/Map0.png", sf::Vector2f(0.f, 0.f)));

	sf::Image image;
	image.loadFromFile(MAPS_DIRECTORY + "Level 3/Map0.png");
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

			switch (ColorManager::getEnemyAsColor[colorCode])
			{
			case EnemyType::GOOMBA:
				this->entities.push_back(new Goomba(sf::Vector2f(i * 50.f, j * 50.f)));
				break;
			case EnemyType::KOOPA:
				this->entities.push_back(new Koopa(sf::Vector2f(i * 50.f, j * 50.f)));
				break;
			default:
				break;
			}
		}
}

EndlessMode::EndlessMode() :
	numMap(3),
	cameraPosition(SCREEN_WIDTH / 2),
	cameraSpeed(200.f)
{
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
			sf::Color color = image.getPixel(i, j);
			int colorCode = color.toInteger();

			switch (ColorManager::getEnemyAsColor[colorCode])
			{
			case EnemyType::GOOMBA:
				this->entities.push_back(new Goomba(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE)));
				break;
			case EnemyType::KOOPA:
				this->entities.push_back(new Koopa(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE)));
				break;
			default:
				break;
			}
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
		int i = randomize(0, numMap - 1) + 1;
		this->addMap(MAPS_DIRECTORY + "Level 3/Map" + std::to_string(i) + ".png");
	}

	if (this->cameraPosition > this->maps.front()->getPosition().x + this->maps.front()->getSize().x * TILE_SIZE + SCREEN_WIDTH)
	{
		delete this->maps.front();
		this->maps.erase(this->maps.begin());
		std::cout << "Deleted\n";
	}
}

void EndlessMode::updateCollision()
{
	for (auto& e : this->entities)
	{
		for (auto& m : this->maps)
		{
			if (!e->getEnabled()) continue;
			Collision::handle_entity_map(e, m);
		}
	}
}

void EndlessMode::updateCamera(float deltaTime)
{
	this->cameraPosition += this->cameraSpeed * deltaTime;
	this->camera.update(deltaTime, sf::Vector2f(this->cameraPosition, this->player->getPosition().y));
	//this->camera.update(deltaTime, this->player->getPosition());
}

void EndlessMode::render(sf::RenderWindow& target, bool& held)
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
}
