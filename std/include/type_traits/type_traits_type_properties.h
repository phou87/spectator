#ifndef SPECTATOR_TYPE_TRAITS_TYPE_PROPERTIES
#define SPECTATOR_TYPE_TRAITS_TYPE_PROPERTIES

#include "logic_util.h"
#include "is_abstract.h"
#include "is_empty.h"
#include "is_literal.h"

namespace Spectator {
namespace std {

template<typename>
struct is_const : public false_type { };

template<typename T>
struct is_const<T const> : public true_type { };

} // close namespace std
} // close namespace Spectator

#endif
