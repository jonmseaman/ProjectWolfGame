#include "House_2Story.h"
#include "Dir.h"

House_2Story::House_2Story() {
  std::string upText{"Second Floor"};
  std::string downText{"First Floor"};
  setNodeLink(Maps::Up, true, &StoryTwo);
  StoryTwo.setNodeLink(Maps::Down, true, this);
}

House_2Story::~House_2Story() {
}

void House_2Story::activate() {
  Node::activate();
  StoryTwo.activate();
}
