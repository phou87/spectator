#ifndef SPECTATOR_IS_ABSTRACT
#define SPECTATOR_IS_ABSTRACT

#include "integral_constant.h"
#include "logic_util.h"
#include "is_class.h"

namespace Spectator {
namespace std {

template<typename T, bool>
struct SpectatorIsAbstractHelper {
    template<typename U>
    static false_type isAbstractHelper(U (*)[1]);

    template<typename U>
    static true_type isAbstractHelper(...);

    // static_assert(sizeof(T) != 0);

    typedef decltype(SpectatorIsAbstractHelper<T, true>::template isAbstractHelper<T>(0)) isAbstract;
};

template<typename T>
struct SpectatorIsAbstractHelper<T, false> {
    typedef false_type isAbstract;
};

template<typename T>
struct is_abstract : public SpectatorIsAbstractHelper<T, is_class<T>::value>::isAbstract { };

} // close namespace std
} // close namespace Spectator

#endif
