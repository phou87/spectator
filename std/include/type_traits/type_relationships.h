#ifndef SPECTATOR_TYPE_RELATIONSHIPS
#define SPECTATOR_TYPE_RELATIONSHIPS

#include <type_traits>

namespace Spectator {
namespace std {

template<typename From, typename To>
struct SpectatorIsConvertibleHelper {
    template<typename T>
    static true_type isConvertibleHelper(T);

    template<typename T>
    static false_type isConvertibleHelper(...);

    typedef decltype(isConvertibleHelper<To>(::std::declval<From>())) IsConvertible;
};

template<typename From, typename To>
struct is_convertible : SpectatorIsConvertibleHelper<From, To>::IsConvertible { };

} // close namespace std
} // close namespace Spectator

#endif
