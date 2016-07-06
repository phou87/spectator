#ifndef SPECTATOR_PTR_HELPER
#define SPECTATOR_PTR_HELPER

namespace Spectator {
namespace std {

template<typename Ptr>
struct SpectatorPtrElementTypeHelper {
    template<typename T>
    static typename T::element_type determineType(T *);

    template<template<typename, typename...> class Ptr2, typename T, typename... Args>
    static T determineType(...);
    typedef decltype(
        determineType((Ptr *)0)) element_type;
};

template<typename Ptr, typename U>
struct SpectatorPtrRebindHelper {
    template<typename Ptr2>
    static constexpr bool hasRebindHint(typename Ptr2::template rebind<U> *)
    { return true; }

    template<typename>
    static constexpr bool hasRebindHint(...)
    { return false; }

    static const bool check = hasRebindHint<Ptr>(nullptr);
};

template<typename Ptr, typename U, bool = SpectatorPtrRebindHelper<Ptr, U>::check>
struct SpectatorPtrRebind;

template<typename Ptr, typename U>
struct SpectatorPtrRebind<Ptr, U, true> {
    typedef typename Ptr::template rebind<U> type;
};

template<template<typename, typename...> class Ptr, typename U, typename T, typename... Args>
struct SpectatorPtrRebind<Ptr<T, Args...>, U, false> {
    typedef Ptr<U, Args...> type;
};

} // close namespace std
} // close namespace Spectator

#endif
