export module Engine:Fwd;

// Declared here so that partitions which only need to name these types do not
// have to import the partitions that define them, which would make the
// partition dependency graph cyclic. The definitions live in :Item, :Actor,
// :Node and :Map, and attach to this same module.
export namespace Engine {
namespace Entity {
class Item;
class Actor;
}
namespace Maps {
class Node;
class Map;
}
}
