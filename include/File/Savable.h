#ifndef SAVABLE_H
#define SAVABLE_H
#include <string>

#define STRINGIFY_VALUE_PAIR(var) #var, var
namespace File {

class Savable
{
public:
  Savable();
  ~Savable();

  int getID() { return id; }
  void setID(int idNum) { this->id = idNum; }


  // hide the implementation
  // Stack of update from iterators from boost

  // Writes to a tree, returns self
  virtual Savable& toTree() = 0;
  /** Should pop from the stack of iterators and load from that pair */
  virtual void fromTree() = 0;

  void addSavable(Savable& s);
  void addVariableToTree(std::string varName, int var);
  void addVariableToTree(std::string varName, std::string var);
  void resetSaveTree();

  static void saveMasterTree(std::string fileName);

private:
  /**
  * ID number for use by the factor.
  * @usage Set so that the factory knows what type of actor to make
  */
  int id;

  /** Removes all children from the tree. */
  void clearSaveTree();
  /* Creates the tree*/
  void initSaveTree();
};
} // namespace File

#endif
