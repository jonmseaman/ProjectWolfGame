#ifndef SAVABLE_H
#define SAVABLE_H
#include <string>

#define ADD_VAR(var) Savable::save( #var, var )
#define READ_VAR(var) Savable::load( #var, var )

namespace File {
  /** Writes to and loads from file */
  // TODO: Let this function have a pointer to a master savable to call
  void save(const std::string &fileName);
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
  void save(const std::string &varName, int var);
  void save(const std::string &varName, const std::string &var);

  void load(Savable& l) { l.load(); }
  void load(const std::string &varName, int &var);
  void load(const std::string &varName, std::string &var);
public:
//protected:
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
