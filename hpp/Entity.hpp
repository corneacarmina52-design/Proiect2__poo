#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <optional>

class Entity
{
     protected:
          std::optional<sf::Sprite> sprite; //pt a retien coordonatele si a lucra cu ele
          float speed;
     public:
          sf::FloatRect getBounds() const {
               if (sprite.has_value()) {
                    return sprite->getGlobalBounds();
               }
               return sf::FloatRect({0.0f, 0.0f}, {0.0f, 0.0f});
          }
          Entity(sf::Texture& texture, float speed);
          virtual ~Entity() = default;

          virtual void update (float deltaTime) =0;
          virtual void draw(sf::RenderWindow& window) = 0; //fereastra pe care sa deseneze/monitorul 

          static int entityCount;
};
#endif