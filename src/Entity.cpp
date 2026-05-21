#include "Entity.hpp"


int Entity::entityCount= 0;

Entity::Entity(sf::Texture& texture, float speed) : sprite(texture) ,speed(speed) {}