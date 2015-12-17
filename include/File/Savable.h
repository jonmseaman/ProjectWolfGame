#ifndef SAVABLE_H
#define SAVABLE_H
#include <string>

#define ADD_VAR(var) Savable::save( #var, var )
#define READ_VAR(var) Savable::load( #var, var )
#define SAVABLE void save(); void load()

namespace File {
  /**
   * Takes the current master tree and writes it to a file
   * with filename fileName.
   * Data saved with Savable::save() will be written to disk.
   * @param fileName The name of the file on disk.
   */
  void save(const std::string &fileName);
  /**
   * Loads a tree from a file to the masterTree.
   * Allows Savable::load() to be used for loading.
   * @param fileName The name of the file being loaded from disk.
   */
  void load(const std::string &fileName);

class Savable
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

  void save(Savable& s) { s.save(); }
  void save(const std::string &varName, int var) const;
  void save(const std::string &varName, const std::string &var) const;

  void load(Savable& l) { l.load(); }
  void load(const std::string &varName, int &var);
  void load(const std::string &varName, std::string &var);
protected:
  /**
   * Should create a tree for the current savable
   */
  void startSave(const std::string& key);
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
