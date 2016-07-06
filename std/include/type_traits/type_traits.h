#ifndef SPECTATOR_TYPE_TRAITS
#define SPECTATOR_TYPE_TRAITS

#include "type_traits_primary_types.h"

namespace Spectator {
namespace std {


template<typename T>
struct remove_reference {
    typedef T type;
};

template<typename T>
struct remove_reference<T &> {
    typedef T type;
};

template<typename T>
struct remove_reference<T &&> {
    typedef T type;
};

} // close namespace std
} // close namespace Spectator

#endif
