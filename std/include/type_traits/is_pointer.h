#ifndef SPECTATOR_IS_POINTER
#define SPECTATOR_IS_POINTER

#include "const_volatile_qualifications.h"

namespace Spectator {
namespace std {

template<typename>
struct SpectatorIsPointerHelper : public false_type { };

template<typename T>
struct SpectatorIsPointerHelper<T *> : public true_type { };

template<typename T>
struct is_pointer : public SpectatorIsPointerHelper<typename remove_cv<T>::type>::type { };

} // close namespace std
} // close namespace Spectator

#endif
