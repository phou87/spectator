#ifndef SPECTATOR_STATIC_TYPE_UTIL
#define SPECTATOR_STATIC_TYPE_UTIL

#include "const_volatile_qualifications.h"

namespace Spectator {
namespace std {

#define SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT(TYPE, NAME, DEFAULT, TYPEDEF)  \
    struct SpectatorSetTypedefWithDefault##NAME {                           \
        template<typename T>                                                \
        static typename T::NAME determineType(T *);                         \
                                                                            \
        static DEFAULT determineType(...);                                  \
        typedef decltype(                                                   \
            determineType((TYPE *)0)) TYPEDEF;                              \
    };                                                                      \
    typedef typename SpectatorSetTypedefWithDefault##NAME::TYPEDEF TYPEDEF;
                       
#define SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT_USING_NAME(TYPE, NAME, DEFAULT) \
    SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT(TYPE, NAME, DEFAULT, NAME) 

#define SPECTATOR_M_IS_TRAIT_BASE(CLASSNAME, BOOL) \
    template<typename>                             \
    struct CLASSNAME : public BOOL { };

#define SPECTATOR_M_IS_TRAIT_DEFAULT(TRAIT, BOOL)     \
    SPECTATOR_M_IS_TRAIT_BASE(Spectator##TRAIT, BOOL) 

#define SPECTATOR_M_IS_TRAIT_SPEC(TRAIT, TYPE, BOOL) \
    template<>                                       \
    struct Spectator##TRAIT<TYPE> : public BOOL { };

#define SPECTATOR_M_IS_TRAIT_REMOVE_CV_WRAPPER(TRAIT)                              \
    template<typename T>                                                           \
    struct TRAIT : public Spectator##TRAIT<typename remove_cv<T>::type>::type { };


} // close namespace std
} // close namespace Spectator

#endif
