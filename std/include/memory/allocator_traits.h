#ifndef SPECTATOR_ALLOCATOR_TRAITS
#define SPECTATOR_ALLOCATOR_TRAITS

#include <memory>
#include <type_traits>
#include "static_type_util.h"
#include "alloc_helper.h"
#include "pointer_traits.h"
#include "logic_util.h"

namespace Spectator {
namespace std {

template<typename Alloc>
struct allocator_traits {

    typedef Alloc allocator_type;
    typedef typename allocator_type::value_type value_type;

    SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT_USING_NAME(Alloc, pointer, value_type*)
    SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT_USING_NAME(Alloc, const_pointer, typename pointer_traits<pointer>::template rebind<const value_type>)
    SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT_USING_NAME(Alloc, void_pointer, typename pointer_traits<pointer>::template rebind<void>)
    SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT_USING_NAME(Alloc, const_void_pointer, typename pointer_traits<pointer>::template rebind<const void>)
    SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT_USING_NAME(Alloc, difference_type, typename pointer_traits<pointer>::difference_type)
    SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT_USING_NAME(Alloc, size_type, typename ::std::make_unsigned<difference_type>::type)
    SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT_USING_NAME(Alloc, propagate_on_container_copy_assignment, false_type)
    SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT_USING_NAME(Alloc, propagate_on_container_move_assignment, false_type)
    SPECTATOR_M_SET_TYPEDEF_WITH_DEFAULT_USING_NAME(Alloc, propagate_on_container_swap, false_type)

    template<typename T>
    using rebind_alloc = typename SpectatorAllocRebind<Alloc, T>::type;
    template<typename T>
    using rebind_traits = allocator_traits<rebind_alloc<T>>;

    static pointer allocate(Alloc& a, size_type n)
    { return a.allocate(n); }

    static pointer allocate(Alloc &a, size_type n, const_void_pointer hint)
    { return SpectatorAllocAllocate(a, n, hint); }

    static void deallocate(Alloc &a, pointer p, size_type n)
    { a.deallocate(p, n); }

    template<typename T, typename... Args>
    static auto construct(Alloc &a, T *p, Args&&... args)
    -> decltype(SpectatorAllocConstruct(a, p, ::std::forward<Args>(args)...))
    { SpectatorAllocConstruct(a, p, ::std::forward<Args>(args)...); }

    template<typename T>
    static void destroy(Alloc &a, T *p)
    { SpectatorAllocDestroy(a, p); }

    static size_type max_size(const Alloc &a) noexcept
    { return SpectatorAllocMaxsize(a); }

    static Alloc select_on_container_copy_construction(const Alloc &rhs)
    { return SpectatorAllocSelect(rhs); }
};

} // close namespace std
} // close namespace Spectator

#endif
