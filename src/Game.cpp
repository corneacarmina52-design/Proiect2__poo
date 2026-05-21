#include "Game.hpp"
#include "EnemyFactory.hpp"
#include "../hpp/WeaponStrategy.hpp"
#include <iostream>
#include <cmath>

Game::Game() : window(sf::VideoMode({800,600}), "POO")
{
     textureManager.load("scout_tex", "assets/scout.png");
     textureManager.load("boss_tex", "assets/boss.png");
     textureManager.load("player_tex", "assets/player.jpeg");
     if (!gameFont.openFromFile("assets/font.ttf")) 
     {
          if (!gameFont.openFromFile("build/assets/font.ttf")) 
          {
               std::cout << "EROARE: Nu s-a gasit font.ttf in folderul assets!" << std::endl;
          }
     }
     currentWeapon = std::make_unique<SingleShot>(); //arma initiala

     enemies.push_back(EnemyFactory::createEnemy(EnemyType::SCOUT, textureManager, 150, -50));
     enemies.push_back(EnemyFactory::createEnemy(EnemyType::SCOUT, textureManager, 350, -100));
     enemies.push_back(EnemyFactory::createEnemy(EnemyType::BOSS, textureManager, 400, -200));   
     
     std::cout<<" INAMICI ACTIVI: "<<Entity::entityCount<<std::endl;


}
Game::~Game() = default;

void Game::processEvents()
{
     while (const std::optional event = window.pollEvent())
     {
          // daca s a inchis fereatsra
          if (event->is<sf::Event::Closed>()) {
               window.close();
          }
          if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) 
          {
               //arma simpla
               if (keyPressed->code == sf::Keyboard::Key::Num1) 
               {    currentWeapon = std::make_unique<SingleShot>();
                    weaponType = 1; 
               }
               //arma tripla
               if (keyPressed->code == sf::Keyboard::Key::Num2) 
               {
                    currentWeapon = std::make_unique<SpreadShot>();
                    weaponType = 2; 
               }

               if (keyPressed->code == sf::Keyboard::Key::Space) 
               {
                    //  polimorfie
                    if (currentWeapon) {
                         currentWeapon->fire(playerPos.x, playerPos.y);
                    }

                    //gloantele triple
                    if (weaponType == 2) 
                    {
                         gameBullets.push_back({playerPos.x + 20.0f, playerPos.y});        // mijloc
                         gameBullets.push_back({playerPos.x + 5.0f, playerPos.y + 5.0f});   // stanga
                         gameBullets.push_back({playerPos.x + 35.0f, playerPos.y + 5.0f});  // dreapta
                    } 
                    else 
                    {
                         //un singur glont pe mijloc
                         gameBullets.push_back({playerPos.x + 20.0f, playerPos.y}); 
                    }
               }
          }
     }
}

void Game::update(float deltaTime)
{
     //se opreste jocul
     if (isGameOver) {
          return;
     }

     //directia jucatorului
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
          playerPos.x -= playerSpeed * deltaTime;
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
          playerPos.x += playerSpeed * deltaTime;
     }

     if (playerPos.x < 0.0f) playerPos.x = 0.0f;
     if (playerPos.x > 760.0f) playerPos.x = 760.0f;

     //generarea corabiilor
     spawnTimer += deltaTime;
     if (spawnTimer >= 3.0f) 
     {
          float randomX = static_cast<float>(rand() % 650 + 50);
          if (rand() % 10 < 7) {
               enemies.push_back(EnemyFactory::createEnemy(EnemyType::SCOUT, textureManager, randomX, -100.0f)); 
          } else {
               enemies.push_back(EnemyFactory::createEnemy(EnemyType::BOSS, textureManager, randomX, -100.0f)); 
          }
          spawnTimer = 0.0f;
     }

     //pt ca corabiile sa coboare
     for (auto& enemy : enemies) {
          enemy->update(deltaTime);
     }

     //miscarea gloantelor
     for (auto& bullet : gameBullets) {
          bullet.y -= 600.0f * deltaTime; 
     }

     // intersectia gloantelor cu corabiile si puncte calculate
     for (auto bulletIt = gameBullets.begin(); bulletIt != gameBullets.end(); ) 
     {
          bool bulletHit = false;

          for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) 
          {
               sf::FloatRect eBounds = (*enemyIt)->getBounds();
               
               float dx = (*bulletIt).x - (eBounds.position.x + eBounds.size.x / 2.0f);
               float dy = (*bulletIt).y - (eBounds.position.y + eBounds.size.y / 2.0f);
               float distance = std::sqrt(dx * dx + dy * dy);

               if (distance < 35.0f) 
               {
                    bulletHit = true;
                    
                    auto* boss = dynamic_cast<BossEnemy*>(enemyIt->get());
                    if (boss) {
                         boss->takeDamage(); 
                         if (boss->getHealth() <= 0) {
                              score += 10; 
                              enemyIt = enemies.erase(enemyIt); 
                         } else {
                              enemyIt++; 
                         }
                    } else {
                         score += 5;
                         enemyIt = enemies.erase(enemyIt); 
                    }
                    break; 
               } 
               else 
               {
                    enemyIt++; 
               }
          }

          if (bulletHit) {
               bulletIt = gameBullets.erase(bulletIt);
          } else {
               bulletIt++;
          }
     }

     //intersectia corabii cu jucatorul si cu a "pamantului"
     for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) 
     {
          sf::FloatRect eBounds = (*enemyIt)->getBounds();

          //distanta dintre centru inamicului si centru jucatorului
          float dx = (eBounds.position.x + eBounds.size.x / 2.0f) - (playerPos.x + 20.0f);
          float dy = (eBounds.position.y + eBounds.size.y / 2.0f) - (playerPos.y + 20.0f);
          float distance = std::sqrt(dx * dx + dy * dy);

          // cand inamicul ma loveste
          if (distance < 40.0f) 
          {
               playerHealth--; 
               std::cout << "AI FOST LOVIT! Vieti ramase: " << playerHealth << std::endl;

               enemyIt = enemies.erase(enemyIt);

               if (playerHealth <= 0) {
                    isGameOver = true; 
               }
          } 
          // cand inamicul cade pe jos
          else if (eBounds.position.y > 600.0f) 
          {
               playerHealth--; 
               std::cout << "A SCAPAT O CORABIE! Vieti ramase: " << playerHealth << std::endl;

               enemyIt = enemies.erase(enemyIt); 

               if (playerHealth <= 0) {
                    isGameOver = true; 
               }
          }
          else 
          {
               enemyIt++; // merge mai departe in jos
          }
     }
}
void Game::render()
{
     
     window.clear(sf::Color::Black);

     if (!isGameOver)
     { // 1.eu/ jucatorul
          sf::Sprite playerSprite(textureManager.get("player_tex"));
          playerSprite.setPosition(playerPos);
          playerSprite.setScale({0.05f, 0.05f}); 
          window.draw(playerSprite);

          // inamicii
          for (auto& enemy : enemies) {
               enemy->draw(window);
          }
          //gloantele
          sf::RectangleShape bulletShape({5.0f, 15.0f});
          bulletShape.setFillColor(sf::Color::Magenta);
          for (auto& bullet : gameBullets) {
               bulletShape.setPosition(bullet);
               window.draw(bulletShape);
          }

          // scorul acumulat
          sf::Text scoreText(gameFont);
          scoreText.setString("Score: " + std::to_string(score));
          scoreText.setCharacterSize(30); 
          scoreText.setFillColor(sf::Color::Magenta); 
          scoreText.setPosition({20.0f, 20.0f});
          window.draw(scoreText);
          
          // vietile ramase
          sf::Text healthText(gameFont);
          healthText.setString("ViETI RAMASE: " + std::to_string(playerHealth));
          healthText.setCharacterSize(30);
          healthText.setFillColor(sf::Color::Red);
          healthText.setPosition({500.0f, 20.0f});
          window.draw(healthText);
     }
     else
     {
          //CAND JOCUL s a terminat
          sf::Text gameOverText(gameFont);
          gameOverText.setString("GAME OVER");
          gameOverText.setCharacterSize(60); // Foarte mare
          gameOverText.setFillColor(sf::Color::Magenta); // Tot magenta!
          gameOverText.setPosition({250.0f, 180.0f}); 
          window.draw(gameOverText);

          // punctele
          sf::Text finalScoreText(gameFont);
          finalScoreText.setString("Puncte obtinute: " + std::to_string(score));
          finalScoreText.setCharacterSize(35);
          finalScoreText.setFillColor(sf::Color::White);
          finalScoreText.setPosition({230.0f, 280.0f});
          window.draw(finalScoreText);
          // mesaj de iesire
          sf::Text exitText(gameFont);
          exitText.setString("Inchide fereastra pentru a iesi.");
          exitText.setCharacterSize(20);
          exitText.setFillColor(sf::Color::Cyan);
          exitText.setPosition({255.0f, 380.0f});
          window.draw(exitText);
     }

     //pt a pune pe ecran
     window.display();
}
void Game::run()
{
     while (window.isOpen()) {
          float deltaTime = clock.restart().asSeconds();
          processEvents();
          update(deltaTime);
          render();
     }    
}
