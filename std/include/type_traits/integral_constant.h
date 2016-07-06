#ifndef SPECTATOR_INTEGRAL_CONSTANT
#define SPECTATOR_INTEGRAL_CONSTANT

namespace Spectator {
namespace std {

template<typename T, T v>
struct integral_constant {
    static constexpr T value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;
    constexpr operator T() const { return v; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

} // close namespace std
} // close namespace Spectator

#endif
