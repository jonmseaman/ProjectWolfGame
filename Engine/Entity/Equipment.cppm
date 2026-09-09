module;
#include "EngineMacros.h"

export module Engine:Equipment;

import :Inventory;

export namespace Engine {
namespace Entity {

class ENGINE_API Equipment : public Inventory {};

}
}
