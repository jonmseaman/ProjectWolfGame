#ifndef RAT_H
#define RAT_H

#include <Entity/Actor.h>
using namespace Engine::Entity;

/**
 * This class is supposed to represent a rat.
 * It should be a weak enemy and should be easily killed.
 */
class Rat : public Actor
{
  public:
    Rat();
    virtual ~Rat();
  protected:
  private:
};

#endif // RAT_H
