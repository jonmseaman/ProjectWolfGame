#pragma once
#include "Registration.h"
/// <summary>
/// This macro is used to implement create method used by the Create class
/// to produce 
/// </summary>
#define CREATABLE_ITEM(ClassName)   static Engine::Entity::Item* create() { return new ClassName; }
#define CREATABLE_ACTOR(ClassName)  static Engine::Entity::Actor* create() { return new ClassName; }
#define CREATABLE_NODE(ClassName)   static Engine::Maps::Node* create() { return new ClassName; }
#define CREATABLE_MAP(ClassName)    static Engine::Maps::Map* create() { return new ClassName; }

/// <summary>
/// A macro used to create a global variable which will auto-register
/// a class for creation by the Create class.
/// </summary>
#define CREATEABLE_REGISTRATION(ClassName) Creation::Registration __registration##ClassName ( #ClassName, ClassName ::create )
