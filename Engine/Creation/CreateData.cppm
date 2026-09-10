export module Engine:CreateData;

import std;
import :Fwd;

/**
 * The tables that Create builds objects from.
 *
 * These are accessors around function-local statics rather than static data
 * members. The Registration objects that fill them are globals in other
 * translation units, and the order in which globals in different translation
 * units are initialised is not defined, so a table could be inserted into
 * before it was constructed. That happened to work while the libraries were
 * shared, and segfaulted on start-up as soon as they were built static. A
 * function-local static is constructed on first use, so the ordering cannot go
 * wrong.
 */
export class CreateData {
public:
    using ItemFactory = std::function<std::unique_ptr<Engine::Entity::Item>()>;
    using ActorFactory = std::function<std::unique_ptr<Engine::Entity::Actor>()>;
    using NodeFactory = std::function<std::unique_ptr<Engine::Maps::Node>()>;
    using MapFactory = std::function<std::unique_ptr<Engine::Maps::Map>()>;

    /// Item names to item creation functions.
    static std::map<std::string, ItemFactory> &items();
    /// Actor names to actor creation functions.
    static std::map<std::string, ActorFactory> &actors();
    /// Node names to node creation functions.
    static std::map<std::string, NodeFactory> &nodes();
    /// Map names to map creation functions.
    static std::map<std::string, MapFactory> &maps();
};
