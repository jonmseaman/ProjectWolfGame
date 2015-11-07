#ifndef CREATURE_INTERFACE_H
#define CREATURE_INTERFACE_H


class Creature_Interface
{
  // This class was originally created for use by items
  public:
    virtual void onAssistDamage(int dmg) = 0; // Tries to damage this creature's target
    virtual void onAssistHeal(int heal) = 0; // Tries to heal this creature's target
    virtual int onDamage(int dmg) = 0; // Returns damage taken
    virtual int onHeal(int heal) = 0; // Returns health gained
  protected:
  private:
};

#endif // CREATURE_INTERFACE_H
