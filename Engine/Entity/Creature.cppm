module;
#include "SavableMacros.h"

export module Engine:Creature;

import std;
import Savable;
import :Equipment;
import :Inventory;
import :Item;
import :Stats;

export namespace Engine {
    namespace Entity {
        /**
         * This class should store all functions for defining what a creature is.
         */
        class Creature : public File::Savable {
            // The data structure for the creatures.
            // This class should contain the data and tools for making functioning
            // actors in the game world, but not actually include a way to _act_

        public:
            Creature();

            ~Creature() override;

            SAVABLE; // load / save

            void combatStop(); // Takes creature out of combat and removes targets

            // Data Access
            const std::string &getName() const { return name; }

            void setName(const std::string &newName); // sets the name of the creature
            bool getIsInCombat() const { return isInCombat; }
            bool getIsLiving() const { return isLiving; }

            void setHealth(int newHealth);

            void setMaxHealth(int newMaxHealth); // Set max hp, also sets hp
            void setIsLiving(bool living); // Can be used to kill a creature

            // Experience
            void levelUp();

            int experienceToNextLevel();

            void addExperience(int xp);

            // Creature stuff

            /**
              * Uses an item. Applies effects to this if the item is 'defensive'
              * or applies the effects to the target if offensive
              * @param item The item being used.
              * @param usedOn The creature that the item is being used on.
              */
            void useItem(Item &item, Creature &usedOn);

            /**
             * This function handles creatures being damaged.
             * Kills the creature if the damage is sufficient.
             * @param dmg The amount of damage that this creature takes
             */
            void onDamage(int dmg);

            void onHeal(int heal);

            void kill(); // Reduces creature health to zero. Sets isLiving to false

            // Display
            void displayHUDLine();

            Equipment equipment;
            Inventory inventory;

            // Stats
            Stats stats;

        protected:
            void flagInCombat(bool val); // sets combat status
        private:
            std::string name = "Creature";
            // Utility vars
            bool isLiving = false; // TODO: Remove this variable
            bool isInCombat = false;

            // XP Variables
            int level = 1; // Creatures level
            int experience = 0; // Experience earned this level

            // Derived stats
            int health = 0;
            int maxHealth = 0; // This should be calculated.
        };
    }
}
