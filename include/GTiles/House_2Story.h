#ifndef HOUSE_2STORY_H
#define HOUSE_2STORY_H
#include "Node.h"

class House_2Story : public Maps::Node
{
  public:
    House_2Story();
    virtual ~House_2Story();
    void activate();
  protected:
  private:
    Node StoryTwo{};
};

#endif // HOUSE_2STORY_H
