#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>
#include <memory>
#include <iostream>

template <typename T>
class ResourceManager 
{
     private:
          std::map<std::string, std::unique_ptr<T>> resources; // pt a cauta dupa denumire
     public:
          ResourceManager() = default;

          ResourceManager(const ResourceManager& ) = delete; //dezactivez copierea pentru a nu avea probleme de memorie
          ResourceManager& operator= ( const ResourceManager& ) = delete; // la fel si cel de atribuire


          //incarca o resursa dintr-un fisier
          void load(const std::string& id, const std::string& fileName)
          {
               auto resource = std::make_unique<T>(); 
               
               if ( !resource->loadFromFile(fileName)) //daca  fisierul nu exista sau nu e bun
               {
                    std::cerr<<"EROARE LA INCARCAREA RESURSEI: "<<fileName<<std::endl;
                    return;
               }

               resources[id] = std::move(resource); //daca e bun pun in mapul meu cu id dat
          }

          T& get(const std::string& id)
          {
               return *resources.at(id);
          }
          //returneaza referinta catre id ul dat
};

#endif