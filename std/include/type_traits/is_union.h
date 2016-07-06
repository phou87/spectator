#ifndef SPECTATOR_IS_UNION
#define SPECTATOR_IS_UNION

#include "integral_constant.h"

namespace Spectator {
namespace std {

#if defined(__GNUC__) && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 3) || __GNUC__ > 4)
template<typename T>
struct is_union : public integral_constant<bool, __is_union(T)> { };
#else
template<typename T>
struct is_union : public integral_constant<bool, false> { };
#endif

} // close namespace std
} // close namespace Spectator

#endif
