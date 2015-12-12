#ifndef SAVABLE_H
#define SAVABLE_H
#include <string>

#define ADD_VAR(var) addVariable( #var, var )
#define READ_VAR(var) readVariable( #var, var )

namespace File {
  /** Writes to and loads from file */
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

  /**
   * Should create a tree for the current savable
   */
  void start(std::string key);
  void end();

  /** Adds variables for saving */
  virtual void save() {} // TODO: Pure virtual
  /** Reads variable from tree */
  virtual void load() {} // TODO: Pure virtual

  void addVariable(const std::string &varName, int var);
  void addVariable(const std::string &varName, const std::string &var);
  void readVariable(const std::string &varName, int &var);
  void readVariable(const std::string &varName, std::string &var);

private:
  /**
  * ID number for use by the factor.
  * @usage Set so that the factory knows what type of actor to make
  */
  int id;
};
} // namespace File

#endif
