#ifndef SPECTATOR_IS_MEMBER_FUNCTION_POINTER
#define SPECTATOR_IS_MEMBER_FUNCTION_POINTER

#include "integral_constant.h"

namespace Spectator {
namespace std {

template<typename>
struct SpectatorIsMemberFunctionPointerHelper : public false_type { };

template<typename T, typename U>
struct SpectatorIsMemberFunctionPointerHelper<T U::*> : public integral_constant<bool, is_function<T>::value> { };

template<typename T>
struct is_member_function_pointer : public SpectatorIsMemberFunctionPointerHelper<typename remove_cv<T>::type> { };

} // close namespace std
} // close namespace Spectator

#endif
