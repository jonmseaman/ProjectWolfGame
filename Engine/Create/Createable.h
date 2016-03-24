#pragma once
#include "Registration.h"
/// <summary>
/// This macro is used to implement create method used by the Create class
/// to produce 
/// </summary>
#define CREATABLE_CLASS_MEMBERS(ClassName) static virtual ClassName* create() const { return new ClassName; }

/// <summary>
/// A macro used to create a global variable which will auto-register
/// a class for creation by the Create class.
/// </summary>
#define CREATEABLE_REGISTRATION(ClassName) Registration __registration##ClassName(#ClassName, ClassName)
