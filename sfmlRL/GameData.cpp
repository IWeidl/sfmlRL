#include "GameData.h"

GameData::GameData(sf::RenderWindow& gameWindow)
	: gameWindow(gameWindow)
{
}

GameData::~GameData()
{
	for (auto& entity : entities)
	{
		delete entity;
	}
	
	for (auto& texture : textures)
	{
		delete texture;
	}
}

json GameData::FileToJSON(std::string fileName)
{
	try {
		std::ifstream f(fileName, std::ifstream::in);
		json tempJson;
		f >> tempJson;
		return tempJson;
	}
	catch (std::exception e)
	{
		std::cout << e.what();
		return nullptr;
	}	
}

int GameData::LoadEntity(json object, std::string entityName)
{
	try {
		json temp = object.at(entityName);
		int texture = temp.at("TextureID");
		sf::Vector2f coords(temp.at("Position").at(0), temp.at("Position").at(1));
		Entity* entity = new Entity(gameWindow, coords);
		entity->CreateSprite(*textures[texture]);
		entities.push_back(entity);
		return entities.size() - 1;	// Returns the index of last vector pushed back
	}
	catch (std::exception e) {
		std::cout << e.what();
		return -1;
	}
}

void GameData::LoadTextures(json jsonData)
{
	
	for (auto& el : jsonData.items())
	{
		sf::Texture* texture = new sf::Texture;
		if (!texture->loadFromFile(el.value()))
		{
			std::cout << "ERROR: Entity::LoadTexture(): Error loading texture: " << el.key() << " at file path: " << el.key() << std::endl;
		}
		std::cout << "Successfully loaded texture: " << el.key() << " at file path: " << el.value() << std::endl;
		textures.push_back(texture);
	}
}

void GameData::LoadEntities(json jsonData)
{

}