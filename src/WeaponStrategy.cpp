#include "WeaponStrategy.hpp"
#include <iostream>

void SingleShot::fire(float x, float y)
{
     std::cout<<"[Weapon] Tragere SIMPLA la pozitia : ( "<<x<<" , "<<y<<")\n";
}

void SpreadShot::fire(float x, float y)
{
     std::cout<<"[Weapon] Tragere TRIPLA la pozitia : ( "<<x<<" , "<<y<<")\n";
}