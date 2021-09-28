#pragma once

// get the underlying value of the enum class
#define ECLASS_VAL(EC) (static_cast<std::underlying_type_t<decltype(EC)>>(EC))
