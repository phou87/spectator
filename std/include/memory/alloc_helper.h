#ifndef SPECTATOR_ALLOC_HELPER
#define SPECTATOR_ALLOC_HELPER

#include <type_traits>
#include <limits>

namespace Spectator {
namespace std {

template<typename Alloc>
struct SpectatorAllocAllocatorHelper {
    template<typename Alloc2, typename = decltype(
        ::std::declval<Alloc2 *>()->allocate(
            ::std::declval<typename Alloc::size_type>(),
            ::std::declval<typename Alloc::const_void_pointer>()
        )
    )>
    static constexpr bool hasAllocateHint(int)
    { return true; }

    template<typename>
    static constexpr bool hasAllocateHint(...)
    { return false; }

    static const bool check = hasAllocateHint<Alloc>(0);
};

template<typename Alloc>
static typename ::std::enable_if<SpectatorAllocAllocatorHelper<Alloc>::check, typename Alloc::pointer>::type
SpectatorAllocAllocate(Alloc &a, typename Alloc::size_type n, typename Alloc::const_void_pointer hint)
{ return a.allocate(n, hint); }

template<typename Alloc>
static typename ::std::enable_if<!SpectatorAllocAllocatorHelper<Alloc>::check, typename Alloc::pointer>::type
SpectatorAllocAllocate(Alloc &a, typename Alloc::size_type n, ...)
{ return a.allocate(n); }

template<typename Alloc, typename T, typename... Args>
struct SpectatorAllocConstructHelper {
    template<typename Alloc2, typename = decltype(
        ::std::declval<Alloc2 *>()->construct(
            ::std::declval<T *>(),
            ::std::declval<Args>()...
        )
    )>
    static constexpr bool hasConstructHint(int)
    { return true; }

    template<typename>
    static constexpr bool hasConstructHint(...)
    { return false; }

    static const bool check = hasConstructHint<Alloc>(0);
};

template<typename Alloc, typename T, typename... Args>
static typename ::std::enable_if<SpectatorAllocConstructHelper<Alloc, T, Args...>::check, void>::type
SpectatorAllocConstruct(Alloc &a, T *p, Args&&... args)
{ a.construct(p, ::std::forward<Args>(args)...); }

template<typename Alloc, typename T, typename... Args>
static typename ::std::enable_if<!SpectatorAllocConstructHelper<Alloc, T, Args...>::check, void>::type
SpectatorAllocConstruct(Alloc &a, T *p, Args&&... args)
{ ::new ((void *)p) T(::std::forward<Args>(args)...); }

template<typename Alloc, typename T>
struct SpectatorAllocDestroyHelper {
    template<typename Alloc2, typename = decltype(
        ::std::declval<Alloc2 *>()->destroy(
            ::std::declval<T*>()
        )
    )>
    static constexpr bool hasDestroyHint(int)
    { return true; }

    template<typename>
    static constexpr bool hasDestroyHint(...)
    { return false; }

    static const bool check = hasDestroyHint<Alloc>(0);
};

template<typename Alloc, typename T>
static typename ::std::enable_if<SpectatorAllocDestroyHelper<Alloc, T>::check, void>::type
SpectatorAllocDestroy(Alloc &a, T *p)
{ a.destroy(p); }

template<typename Alloc, typename T>
static typename ::std::enable_if<!SpectatorAllocDestroyHelper<Alloc, T>::check, void>::type
SpectatorAllocDestroy(Alloc &a, T *p)
{ p->~T(); }

template<typename Alloc>
struct SpectatorAllocMaxsizeHelper {
    template<typename Alloc2, typename = decltype(
        ::std::declval<Alloc2 *>()->max_size()
    )>
    static constexpr bool hasMaxsizeHint(int)
    { return true; }

    template<typename>
    static constexpr bool hasMaxsizeHint(...)
    { return false; }

    static const bool check = hasMaxsizeHint<Alloc>(0);
};

template<typename Alloc>
static typename ::std::enable_if<SpectatorAllocMaxsizeHelper<Alloc>::check, typename Alloc::size_type>::type
SpectatorAllocMaxsize(Alloc &a)
{ return a.max_size(); }

template<typename Alloc>
static typename ::std::enable_if<!SpectatorAllocMaxsizeHelper<Alloc>::check, typename Alloc::size_type>::type
SpectatorAllocMaxsize(Alloc &a)
{ return ::std::numeric_limits<typename Alloc::size_type>::max(); }

template<typename Alloc>
struct SpectatorAllocSelectHelper {
    template<typename Alloc2, typename = decltype(
        ::std::declval<Alloc2 *>()->select_on_container_copy_construction()
    )>
    static constexpr bool hasSelectHint(int)
    { return true; }

    template<typename>
    static constexpr bool hasSelectHint(...)
    { return false; }

    static const bool check = hasSelectHint<Alloc>(0);
};

template<typename Alloc>
static typename ::std::enable_if<SpectatorAllocSelectHelper<Alloc>::check, Alloc>::type
SpectatorAllocSelect(Alloc &a)
{ return a.select_on_container_copy_construction(); }

template<typename Alloc>
static typename ::std::enable_if<!SpectatorAllocSelectHelper<Alloc>::check, Alloc>::type
SpectatorAllocSelect(Alloc &a)
{ return a; }

template<typename Alloc, typename T>
struct SpectatorAllocRebindHelper {
    template<typename Alloc2>
    static constexpr bool hasRebindOther(typename Alloc2::template rebind<T>::other *)
    { return true; }

    template<typename>
    static constexpr bool hasRebindOther(...)
    { return false; }

    static const bool check = hasRebindOther<Alloc>(nullptr);
};

/*
template<typename Alloc, typename T>
const bool SpectatorAllocRebindHelper<Alloc, T>::check;
*/

template<typename Alloc, typename T, bool = SpectatorAllocRebindHelper<Alloc, T>::check>
struct SpectatorAllocRebind;

template<typename Alloc, typename T>
struct SpectatorAllocRebind<Alloc, T, true> {
    typedef typename Alloc::template rebind<T>::other type;
};

template<template<typename, typename...> class Alloc, typename T, typename U, typename... Args>
struct SpectatorAllocRebind<Alloc<U, Args...>, T, false> {
    typedef Alloc<T, Args...> type;
};

} // close namespace std
} // close namespace Spectator

#endif
