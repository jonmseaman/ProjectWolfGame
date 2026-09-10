module;
#include "SavableMacros.h"

export module Savable;

import std;

export namespace File {
    /**
     * Thrown when a save file is missing, cannot be written, or does not
     * contain the data that is being asked for.
     */
    class SaveError : public std::runtime_error {
    public:
        explicit SaveError(const std::string &what) : std::runtime_error(what) {
        }
    };

    /**
     * Takes the all variables and objects which have been saved and writes
     * them to a file. The save in progress is cleared afterwards.
     * @param fileName The name of the file on disk, without a path or an
     * extension. ".xml" and the save directory are added by this function.
     * @throws std::invalid_argument if fileName contains a character which is
     * not alphanumeric and not '_', or if it is empty.
     * @throws SaveError if the file could not be written.
     */
    void save(const std::string &fileName);

    /**
     * Gets data of variables and objects from a file. These are ready to be
     * loaded after this function is called. Any save in progress and any
     * previously loaded data is discarded first, so that loading the same file
     * twice does not make every entry appear twice.
     * @param fileName The name of the file being loaded from disk, without a
     * path or an extension.
     * @throws std::invalid_argument if fileName contains a character which is
     * not alphanumeric and not '_', or if it is empty.
     * @throws SaveError if the file does not exist or could not be read.
     */
    void load(const std::string &fileName);

    /** Clears a save in progress. */
    void clear();

    class Savable {
    public:
        Savable();

        /** Virtual because Savable is a base class with virtual functions. */
        virtual ~Savable();

        typedef std::string idType;

        /**
         * Used so that the save file has information on the actual type
         * of the Actor.
         */
        idType getID() { return id; }
        void setID(idType newID) { id = newID; }

        /**
         * Returns the id value of the first thing that can be loaded
         * which also has key matching the param.
         * Calling this method does not change any data.
         * @param key the key of the item being loaded
         * @throws SaveError if nothing with that key is available to load, or if
         * the entry that was found has no id.
         */
        static idType nextID(const std::string &key);

        /** Adds variables for saving */
        virtual void save() = 0;

        /** Reads variable from tree */
        virtual void load() = 0;

        /**
         * Checks if there is a Savable with a specific key.
         * @param key The key that will be checked.
         * @return True if there is a Savable that can be lodaed
         * with the specified key.
         */
        bool canLoad(const std::string &key);

        /**
         * Adds a variable to the current location in the save tree.
         * The variable will be written to disk when File::save() is called.
         * @param varName A key for identifying the variable upon load.
         */
        void save(const std::string &varName, int var) const;

        void save(const std::string &varName, const char *var) const;

        void save(const std::string &varName, const std::string &var) const;

        /**
         * Reads variables in from load tree.
         * @param varName The key which the variable was saved with.
         * @throws SaveError if no value was saved under varName, or if the saved
         * value cannot be converted to the type being loaded.
         */
        void load(const std::string &varName, int &var);

        void load(const std::string &varName, std::string &var);

        virtual void clearSavable();

    protected:
        /**
         * Creates a tree for the current savable.
         * @usage Inside of a derived class implementation of Savable::save()
         * before adding variables.
         */
        void startSave(const std::string &key);

        /**
         * Stops writing to the current tree. Moves point of saving to parent node.
         */
        void endSave();

        /**
         * Looks for next element available for loading that matches key.
         * Subsequent calls to load() read variables out of that element.
         * @throws SaveError if nothing with that key is available to load.
         */
        void startLoad(const std::string &key);

        void endLoad();

    private:
        /**
        * ID number for use by the factor.
        * @usage Set so that the factory knows what type of actor to make
        */
        idType id;
    };
} // namespace File
