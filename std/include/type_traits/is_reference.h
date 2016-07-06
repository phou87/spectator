#ifndef SPECTATOR_IS_REFERENCE
#define SPECTATOR_IS_REFERENCE

#include "logic_util.h"

namespace Spectator {
namespace std {

template<typename>
struct is_lvalue_reference : public false_type { };

template<typename T>
struct is_lvalue_reference<T &>: public true_type { };

template<typename>
struct is_rvalue_reference: public false_type { };

template<typename T>
struct is_rvalue_reference<T &&>: public true_type { };

template<typename T>
struct is_reference : public SpectatorOr<is_lvalue_reference<T>, is_rvalue_reference<T>>::type { };

} // close namespace std
} // close namespace Spectator

#endif
