#include <Entity/Actor.h>
#include <Creation/Creatable.h>
using namespace Engine::Entity;

/**
* This class is supposed to represent a rat.
* It should be a weak enemy and should be easily killed.
*/
class Rat : public Actor {
public:
  CREATABLE_ACTOR(Rat)
    Rat() {
    setName("Rat");
    setHealth(2);
    setMaxHealth(2);
    stats = Stats{ 2, 1, 1 };
  }
};

CREATABLE_REGISTRATION(Rat);