#ifndef SPECTATOR_UTILITY
#define SPECTATOR_UTILITY

namespace Spectator {
namespace std {

template<typename T>
T&& forward(typename remove_reference<T>::type &arg) noexcept
{ return static_cast<T &&>(arg); }

template<typename T>
T&& forward(typename remove_reference<T>::type &&arg) noexcept
{ return static_cast<T &&>(arg); }

} // close namespace std
} // close namespace Spectator

#endif
