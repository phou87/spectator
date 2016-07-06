#ifndef SPECTATOR_IS_MEMBER_POINTER
#define SPECTATOR_IS_MEMBER_POINTER

#include "integral_constant.h"
#include "logic_util.h"
#include "is_member_function_pointer.h"
#include "is_member_object_pointer.h"

namespace Spectator {
namespace std {

template<typename T>
struct is_member_pointer : public integral_constant<bool, SpectatorOr<is_member_object_pointer<T>, is_member_function_pointer<T>>::value> { };

} // close namespace std
} // close namespace Spectator

#endif
