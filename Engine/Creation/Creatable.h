#ifndef CREATABLE_H
#define CREATABLE_H

// Macros are not exported by modules, so these are included textually. Code
// using them needs `import Engine;` for Creation::Registration and the entity
// types, and `import std;` for unique_ptr.

/// Implements the create() method the Create class uses to produce an object.
#define CREATABLE_ITEM(ClassName)   static std::unique_ptr<Engine::Entity::Item> create() { return std::make_unique<ClassName>(); }
#define CREATABLE_ACTOR(ClassName)  static std::unique_ptr<Engine::Entity::Actor> create() { return std::make_unique<ClassName>(); }
#define CREATABLE_NODE(ClassName)   static std::unique_ptr<Engine::Maps::Node> create() { return std::make_unique<ClassName>(); }
#define CREATABLE_MAP(ClassName)    static std::unique_ptr<Engine::Maps::Map> create() { return std::make_unique<ClassName>(); }

/// Declares a global whose construction registers the class with the factory.
#define CREATABLE_REGISTRATION(ClassName) Creation::Registration __registration##ClassName ( #ClassName, ClassName ::create )

#endif // CREATABLE_H
