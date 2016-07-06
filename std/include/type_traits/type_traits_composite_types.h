#ifndef SPECTATOR_TYPE_TRAITS_COMPOSITE_TYPES
#define SPECTATOR_TYPE_TRAITS_COMPOSITE_TYPES

#include "logic_util.h"
#include "type_traits_primary_types_basic.h"

namespace Spectator {
namespace std {

template<typename T>
struct is_arithmetic : public SpectatorOr<is_integral<T>, is_floating_point<T>> { };

template<typename T>
struct is_fundamental : public SpectatorOr<is_arithmetic<T>, is_void<T>, SpectatorIsNullPointer<T>> { };

template<typename T>
struct is_compound : public SpectatorNot<is_fundamental<T>> { };

template<typename T>
struct is_reference : public SpectatorOr<is_lvalue_reference<T>, is_rvalue_reference<T>> { };

template<typename T>
struct is_object : public SpectatorNot<SpectatorOr<is_function<T>, is_void<T>, is_reference<T>>> { };

template<typename T>
struct is_scalar : public SpectatorOr<is_arithmetic<T>, is_pointer<T>, is_member_pointer<T>, is_enum<T>, SpectatorIsNullPointer<T>> { };

} // close namespace std
} // close namespace Spectator

#endif
