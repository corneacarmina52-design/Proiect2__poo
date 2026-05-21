#ifndef ENEMYFACTORY_HPP
#define ENEMYFACTORY_HPP

#include "Entity.hpp"
#include "Enemy.hpp"
#include "ResourceManager.hpp"
#include <memory>

enum class EnemyType { SCOUT , BOSS};

class EnemyFactory
{
     public:
          static std::unique_ptr<Entity> createEnemy(EnemyType type, ResourceManager<sf::Texture>& rm, float x, float y)
          {
               switch (type)
               {
                    case EnemyType::SCOUT:
                         return std::make_unique<ScoutEnemy>(rm.get("scout_tex"), x , y);
                    case EnemyType::BOSS:
                         return std::make_unique<BossEnemy>(rm.get("boss_tex"), x, y);
                    default:
                         return nullptr;
               }
          }
};

#endif
