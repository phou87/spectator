#ifndef SPECTATOR_IS_MEMBER_OBJECT_POINTER
#define SPECTATOR_IS_MEMBER_OBJECT_POINTER

#include "integral_constant.h"

namespace Spectator {
namespace std {

template<typename>
struct SpectatorIsMemberObjectPointerHelper : public false_type { };

template<typename T, typename U>
struct SpectatorIsMemberObjectPointerHelper<T U::*> : public integral_constant<bool, !is_function<T>::value> { };

template<typename T>
struct is_member_object_pointer : public SpectatorIsMemberObjectPointerHelper<typename remove_cv<T>::type> { };

} // close namespace std
} // close namespace Spectator

#endif
