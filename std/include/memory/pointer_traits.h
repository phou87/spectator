#ifndef SPECTATOR_POINTER_TRAITS
#define SPECTATOR_POINTER_TRAITS

#include "ptr_helper.h"
#include "static_type_util.h"
#include <cstddef>

namespace Spectator {
namespace std {

template<typename Ptr>
struct pointer_traits {
    typedef Ptr pointer;
    typedef typename SpectatorPtrElementTypeHelper<Ptr>::element_type element_type;

    SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT_USING_NAME(Ptr, difference_type, ::std::ptrdiff_t)

    template<typename U>
    using rebind = typename SpectatorPtrRebind<Ptr, U>::type;

    static pointer pointer_to(element_type &e)
    { return Ptr::pointer_to(e); }
};

template<typename T>
struct pointer_traits<T *> {
    typedef T * pointer;
    typedef T element_type;
    typedef ::std::ptrdiff_t difference_type;

    template<typename U>
    using rebind = U *;

    static pointer pointer_to(element_type &e) noexcept
    { return ::std::addressof(e); }
};

} // close namespace std
} // close namespace Spectator

#endif
