#ifndef SPECTATOR_TYPE_HELPER
#define SPECTATOR_TYPE_HELPER

#include "const_volatile_qualifications.h"
#include "integral_constant.h"
#include "is_union.h"
#include "logic_util.h"
#include <cstddef>

namespace Spectator {
namespace std {

template<typename T>
struct SpectatorIsClassUnionHelper {
    template<typename U>
    static constexpr true_type isClassUnionHelper(void(U::*)());
    
    template<typename U>
    static constexpr false_type isClassUnionHelper(...);

    static const bool isClass = SpectatorAnd<
        decltype(isClassUnionHelper<T>(0)),
        SpectatorNot<is_union<T>>
    >::value;

    static const bool isClassOrUnion =
        decltype(isClassUnionHelper<T>(0))::value;
};

template<typename T>
struct SpectatorIsClassOrUnion : public integral_constant<
    bool, !SpectatorIsClassUnionHelper<T>::isClassOrUnion
> { };

template<typename>
struct SpectatorIsNullPointerHelper : public false_type { };

template<>
struct SpectatorIsNullPointerHelper<::std::nullptr_t> : public true_type { };

template<typename T>
struct SpectatorIsNullPointer : public SpectatorIsNullPointerHelper<typename remove_cv<T>::type> { };

} // close namespace std
} // close namespace Spectator

#endif
