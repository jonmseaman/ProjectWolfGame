#ifndef SAVABLE_H
#define SAVABLE_H


#ifdef SAVABLE_EXPORTS
#define SAVABLE_EXPORTS_API __declspec(dllexport) 
#else
#define SAVABLE_EXPORTS_API __declspec(dllimport) 
#endif

#include <string>

#define ADD_VAR(var) Savable::save( #var, var )
#define READ_VAR(var) Savable::load( #var, var )

/** Makes it easier to declare necessary savable functions. */
#define SAVABLE void save(); void load()

namespace File {
  /**
   * Takes the all variables and objects which have been saved and writes
   * them to a file.
   * @param fileName The name of the file on disk. If fileName has
   * a relative path or extension, these are removed.
   */
  void SAVABLE_EXPORTS_API save(const std::string &fileName);
  /**
   * Gets data of variables and objects from a file. These are ready to be
   * loaded after this function is called.
   * @param fileName The name of the file being loaded from disk.
   * If fileName has a relative path or extension, these are removed.
   */
  void SAVABLE_EXPORTS_API load(const std::string &fileName);

  /** Clears a save in progress. */
  void SAVABLE_EXPORTS_API close();

class SAVABLE_EXPORTS_API Savable
{
public:
  Savable();
  ~Savable();

  /**
   * Used so that the save file has information on the actual type
   * of the Actor.
   */
  int getID() { return id; }
  void setID(int idNum) { this->id = idNum; }

  /** Adds variables for saving */
  virtual void save() = 0;
  /** Reads variable from tree */
  virtual void load() = 0;

  /**
   * Adds a variable to the current location in the save tree.
   * The variable will be written to disk when File::save() is called.
   * @param varName A key for identifying the variable upon load.
   */
  void save(const std::string &varName, int var) const;
  void save(const std::string &varName, const std::string &var) const;

  /**
   * Reads variables in from load tree.
   * @param varName The key which the variable was saved with.
   */
  void load(const std::string &varName, int &var);
  void load(const std::string &varName, std::string &var);
protected:
  /**
   * Creates a tree for the current savable.
   * @usage Inside of a derived class implementation of Savable::save()
   * before adding variables.
   */
  void startSave(const std::string& key);
  /**
   * Stops writing to the current tree. Moves point of saving to parent node.
   */
  void endSave();
  /**
   * Looks for next element available for loading that matches key.
   * Calls to read a variable access
   */
  void startLoad(const std::string& key);
  void endLoad();
private:
  /**
  * ID number for use by the factor.
  * @usage Set so that the factory knows what type of actor to make
  */
  int id;
};
} // namespace File

#endif
