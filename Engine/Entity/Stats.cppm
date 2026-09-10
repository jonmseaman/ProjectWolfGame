module;
#include "SavableMacros.h"

export module Engine:Stats;

import Savable;

export namespace Engine::Entity {
    class Stats : public File::Savable {
    public:
        Stats(int stamina = 0, int strength = 0, int intellect = 0);

        SAVABLE;

        // Get and set methods
        int getStamina() const { return stamina; }
        int getStrength() const { return strength; }
        int getIntellect() const { return intellect; }
        void setStamina(int newStamina) { stamina = newStamina; }
        void setStrength(int newStrength) { strength = newStrength; }
        void setIntellect(int newIntellect) { intellect = newIntellect; }

        /**
         * Shows a list of stats and their values
         * 3 lines, Stamina on one, strength, the intellect
         */
        void showStats() const;

        Stats operator+(const Stats &r) const;

        bool operator==(const Stats &r) const;

    private:
        // Base stats
        int stamina; // Boosts max health points
        int strength; // boosts physical damage
        int intellect; // Boosts spell damage
    };
}
