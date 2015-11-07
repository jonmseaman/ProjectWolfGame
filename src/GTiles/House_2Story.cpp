#include "House_2Story.h"
#include "Dir.h"

House_2Story::House_2Story()
{
  std::string upText{"Second Floor"};
  std::string downText{"First Floor"};
  setMoveData(Maps::Up, upText, &StoryTwo );
  setNodeLink(Maps::Up, &StoryTwo );
  StoryTwo.setMoveData(Maps::Down, downText, this);
  StoryTwo.setNodeLink(Maps::Down, this);
}

House_2Story::~House_2Story()
{
}

void House_2Story::activate()
{
  Node::activate();
  StoryTwo.activate();
}
