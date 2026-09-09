export module Engine;

// Engine's API exposes File::Savable as a base class of nearly every type it
// declares, so a consumer cannot use Engine without it. Re-exported so that
// `import Engine;` is enough.
export import Savable;

// The rest of this unit exists only to gather the partitions, so that
// consumers write `import Engine;` rather than naming partitions individually.
export import :Fwd;
export import :Dir;
export import :Input;
export import :Stats;
export import :Item;
export import :Inventory;
export import :Equipment;
export import :Creature;
export import :Node;
export import :Actor;
export import :Map;
export import :MapManager;
export import :Registration;
export import :CreateData;
export import :Create;
