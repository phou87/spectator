#ifndef SPECTATOR_IS_EMPTY
#define SPECTATOR_IS_EMPTY

#include "integral_constant.h"
#include "type_helper.h"

namespace Spectator {
namespace std {

namespace {

const int ALIGNMENT_EDGE = 256;

} // close unnamed namespace

template<typename T>
struct SpectatorIsEmptyClass1 : public T {
    int pad[ALIGNMENT_EDGE];
};

struct SpectatorIsEmptyClass2 {
    int pad[ALIGNMENT_EDGE];
}

template<typename T, bool>
struct SpectatorIsEmptyClassCmp {
    typedef false_type isSameSize;
};

template<typename T>
struct SpectatorIsEmptyClassCmp<T, true> {
    static constexpr bool sameSizes = (
        sizeof(SpectatorIsEmptyClass1<T>) ==
        sizeof(SpectatorIsEmptyClass2)
    );

    typedef integral_constant<bool, sameSizes> isSameSize;
};

template<typename T>
struct SpectatorIsEmptyHelper {
    typedef SpectatorIsEmptyClassCmp<
        typename remove_cv<T>::type, is_class<T>::value
    >::isSameSize isEmpty;
};

template<typename T>
struct is_empty : public SpectatorIsEmptyHelper<T>::isEmpty { };

} // close namespace std
} // close namespace Spectator

#endif
