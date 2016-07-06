#ifndef SPECTATOR_PRIMARY_TYPES_BASIC
#define SPECTATOR_PRIMARY_TYPES_BASIC

#include "static_type_util.h"
#include "type_helper.h"
#include "type_relationships.h"
#include <cstddef>

namespace Spectator {
namespace std {

SPECTATOR_M_IS_TRAIT_BASE(is_array, false_type)

template<typename T, ::std::size_t Size>
struct is_array<T[Size]> : public true_type { };

template<typename T>
struct is_array<T[]> : public true_type { };

SPECTATOR_M_IS_TRAIT_DEFAULT(is_floating_point, false_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_floating_point, float, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_floating_point, double, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_floating_point, long double, true_type)
SPECTATOR_M_IS_TRAIT_REMOVE_CV_WRAPPER(is_floating_point)

template<typename T>
struct is_function : public integral_constant<bool, !is_convertible<T *, const volatile void *>::value> { };

SPECTATOR_M_IS_TRAIT_DEFAULT(is_integral, false_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, bool, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, short, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, unsigned short, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, int, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, unsigned int, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, long, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, unsigned long, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, long long, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, unsigned long long, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, char, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, signed char, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, unsigned char, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, wchar_t, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, char16_t, true_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_integral, char32_t, true_type)
SPECTATOR_M_IS_TRAIT_REMOVE_CV_WRAPPER(is_integral)

SPECTATOR_M_IS_TRAIT_DEFAULT(is_void, false_type)
SPECTATOR_M_IS_TRAIT_SPEC(is_void, void, true_type)
SPECTATOR_M_IS_TRAIT_REMOVE_CV_WRAPPER(is_void)

} // close namespace std
} // close namespace Spectator

#endif
