#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class ScoutEnemy : public Entity //primul inamic : o nava rapida
{public:
     ScoutEnemy(sf::Texture& texture , float x , float y); //cum arata
     ~ScoutEnemy () override; //pt a scade contorul static

     void update(float deltaTime) override;
     void draw(sf::RenderWindow& window) override;
};

//al doilea inamic : o nava mai lenta si mai mare
class BossEnemy : public Entity
{
     private:
          int health;
     public:
          BossEnemy(sf::Texture& texture, float x, float y);
          ~BossEnemy() override;

          void takeDamage() {health--;}
          int getHealth() const { return health;}
          void update(float deltaTime) override;
          void draw(sf::RenderWindow& window) override;
};

#endif