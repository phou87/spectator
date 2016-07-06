#ifndef SPECTATOR_IS_CLASS
#define SPECTATOR_IS_CLASS

#include "integral_constant.h"
#include "type_helper.h"

namespace Spectator {
namespace std {

template<typename T>
struct is_class : public integral_constant<bool, SpectatorIsClassUnionHelper<T>::isClass> { };

} // close namespace std
} // close namespace Spectator

#endif
