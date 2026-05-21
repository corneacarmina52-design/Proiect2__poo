//pentru a schimba tipul de tragere in timpul jocului 

#ifndef  WEAPONSTRATEGY_HPP
#define WEAPONSTRATEGY_HPP

class WeaponStrategy
{
     public :
          virtual ~WeaponStrategy() = default;
          virtual void fire(float x, float y) = 0;
};


class SingleShot : public WeaponStrategy
{
     public:
          void fire(float x , float y) override;
};

class SpreadShot: public WeaponStrategy
{
     public:
          void fire(float x, float y) override;
};

#endif