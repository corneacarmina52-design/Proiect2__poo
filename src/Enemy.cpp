#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

ScoutEnemy::ScoutEnemy(sf::Texture& texture, float x, float y) : Entity(texture, 120.0f)
{
     // optionalul initializat cu textura
     sprite = sf::Sprite(texture);
     sprite->setPosition({x, y}); 
     sprite->setScale({0.04f, 0.04f});
     Entity::entityCount++;
}
ScoutEnemy::~ScoutEnemy()
{
     Entity::entityCount--;
}

void ScoutEnemy::update(float deltaTime)
{
     sprite->move({0.0f, speed * deltaTime});
}

void ScoutEnemy::draw(sf::RenderWindow& window)
{
     // daca are o valoare
     if (sprite.has_value()) {
          window.draw(*sprite);
     }
}

BossEnemy::BossEnemy(sf::Texture& texture, float x, float y) : Entity(texture, 40.0f), health(5)
{
     sprite = sf::Sprite(texture);
     sprite->setPosition({x, y});
     sprite->setScale({0.08, 0.08f});
     Entity::entityCount++;
}

BossEnemy::~BossEnemy()
{
     Entity::entityCount--;
}

void BossEnemy::update(float deltaTime)
{
     sprite->move({0.0f, speed * deltaTime});
}

void BossEnemy::draw(sf::RenderWindow& window)
{
     if (sprite.has_value()) {
          window.draw(*sprite);
     }
}