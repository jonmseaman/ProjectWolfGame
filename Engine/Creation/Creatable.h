#pragma once
#include <memory>
#include "Registration.h"
/// <summary>
/// This macro is used to implement create method used by the Create class
/// to produce
/// </summary>
#define CREATABLE_ITEM(ClassName)   static std::unique_ptr<Engine::Entity::Item> create() { return std::make_unique<ClassName>(); }
#define CREATABLE_ACTOR(ClassName)  static std::unique_ptr<Engine::Entity::Actor> create() { return std::make_unique<ClassName>(); }
#define CREATABLE_NODE(ClassName)   static std::unique_ptr<Engine::Maps::Node> create() { return std::make_unique<ClassName>(); }
#define CREATABLE_MAP(ClassName)    static std::unique_ptr<Engine::Maps::Map> create() { return std::make_unique<ClassName>(); }

/// <summary>
/// A macro used to create a global variable which will auto-register
/// a class for creation by the Create class.
/// </summary>
#define CREATABLE_REGISTRATION(ClassName) Creation::Registration __registration##ClassName ( #ClassName, ClassName ::create )
