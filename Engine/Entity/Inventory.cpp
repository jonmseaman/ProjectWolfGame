module;
#include "SavableMacros.h"

module Engine;

import std;

namespace Engine {
    namespace Entity {
        using namespace Creation;

        Inventory::Inventory() : Inventory("Inventory", 2) {
        }

        Inventory::Inventory(std::string name, int size) : name(name)
                                                           , slots(static_cast<std::size_t>(size))
                                                           , size(size) {
        }

        Inventory::~Inventory() {
        }

        void Inventory::clearSavable() {
            for (auto &item: slots) {
                item.reset();
            }
        }

        void Inventory::save() {
            startSave("Inventory");
            SAVE(name);
            SAVE(size);
            // Save items
            for (const auto &i: slots) {
                if (i != nullptr) {
                    i->save();
                }
            }
            endSave();
        }

        void Inventory::load() {
            clearSavable();
            startLoad("Inventory");
            LOAD(name);
            LOAD(size);
            if (size < 0) {
                throw File::SaveError("Inventory::load: saved inventory size is negative");
            }
            // The slot vector used to keep whatever size it already had, so `size` and
            // slots.size() disagreed after loading -- getSlots() read one and
            // isSlotEmpty() the other, and items past the old end were dropped.
            slots.clear();
            slots.resize(static_cast<std::size_t>(size));
            while (Savable::canLoad("Item")) {
                this->addItem(Create::loadNewItem());
            }
            endLoad();
        }

        bool Inventory::addItem(std::unique_ptr<Item> item) {
            if (hasOpenSlot()) {
                slots.at(firstEmpty()) = std::move(item);
                return true;
            }
            return false;
        }

        std::unique_ptr<Item> Inventory::removeItem(int slotIndex) {
            return std::move(slots.at(slotIndex));
        }

        std::string Inventory::getName() const {
            return name;
        }

        int Inventory::getSlots() const {
            return static_cast<int>(slots.size());
        }

        bool Inventory::hasOpenSlot() const {
            for (const auto &slot: slots) {
                if (slot == nullptr) return true;
            }
            return false;
        }

        int Inventory::firstEmpty() {
            for (int i = 0; i < static_cast<int>(slots.size()); i++) {
                if (slots.at(static_cast<std::size_t>(i)) == nullptr) {
                    return i;
                }
            }
            return -1;
        }

        void Inventory::showListOfItems() {
            std::cout << getName() << std::endl;
            for (int i = 0; i < static_cast<int>(slots.size()); i++) {
                std::size_t idx = static_cast<std::size_t>(i);
                if (slots.at(idx) == nullptr) {
                    std::cout << std::setw(3) << std::right << i + 1 << ": " << "Empty Slot\n";
                } else {
                    std::cout << std::setw(3) << std::right << i + 1 << ": " << slots.at(idx)->getName() << std::endl;
                }
            }
        }

        Item *Inventory::at(int slotIndex) {
            return this->slots.at(slotIndex).get();
        }

        bool Inventory::isSlotEmpty(int slotIndex) {
            if (slotIndex < 0 || slotIndex >= getSlots()) {
                throw std::out_of_range("isSlotEmpty: slotIndex out of range");
            }
            return slots.at(static_cast<std::size_t>(slotIndex)) == nullptr;
        }
    }
}
