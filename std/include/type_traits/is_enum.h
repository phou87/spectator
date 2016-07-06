#ifndef SPECTATOR_IS_ENUM
#define SPECTATOR_IS_ENUM

#include "integral_constant.h"
#include "type_traits_primary_types_basic.h"
#include "is_union.h"
#include "is_member_pointer.h"
#include "is_pointer.h"
#include "is_reference.h"
#include "type_helper.h"

namespace Spectator {
namespace std {

template<typename T>
struct is_enum : public integral_constant<bool,
    !is_array<T>::value          &&
    !is_floating_point<T>::value &&
    !is_function<T>::value       &&
    !is_integral<T>::value       &&
    !is_member_pointer<T>::value &&
    !is_pointer<T>::value        &&
    !is_reference<T>::value      &&
    !SpectatorIsClassOrUnion<T>::value &&
    !is_void<T>::value
> { };

} // close namespace std
} // close namespace Spectator

#endif
