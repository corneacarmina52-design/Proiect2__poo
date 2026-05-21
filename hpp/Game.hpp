#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "ResourceManager.hpp"
#include "WeaponStrategy.hpp"
#include "Entity.hpp"

class Game
{
     private:
          int weaponType = 1;
          sf::RenderWindow window;
          ResourceManager<sf::Texture> textureManager;
          std::unique_ptr<WeaponStrategy> currentWeapon; 
          std::vector<std::unique_ptr<Entity>> enemies; //colectie polimorfica inamici
          sf::Clock clock; //pt calculul deltaTime
          std::vector<sf::Vector2f> gameBullets;
          sf::Vector2f playerPos{400.0f, 550.0f};
          int playerHealth = 3; //vietile jucatorului
          float playerSpeed = 300.0f; // Viteza cu care ma misc
          float spawnTimer = 0.0f;       
          int score = 0;
          bool isGameOver = false;
          sf::Font gameFont;       
          void processEvents();
          void update(float deltaTime);
          void render();
     public:
          Game();
          ~Game();

          void run(); //pt a porni jocul

};

#endif