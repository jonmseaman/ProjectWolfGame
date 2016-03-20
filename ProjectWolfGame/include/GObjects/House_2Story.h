#ifndef HOUSE_2STORY_H
#define HOUSE_2STORY_H
#include "Node.h"

using namespace Engine::Maps;

class House_2Story : public Node
{
  public:
    House_2Story();
    virtual ~House_2Story();
    void activate();
  protected:
  private:
    Node secondFloor{};
};

#endif // HOUSE_2STORY_H
