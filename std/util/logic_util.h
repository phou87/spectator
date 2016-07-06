#ifndef SPECTATOR_LOGIC_UTIL
#define SPECTATOR_LOGIC_UTIL

#include "integral_constant.h"

namespace Spectator {
namespace std {

template<bool, typename, typename>
struct conditional;

template<bool Condition, typename First, typename Second>
struct conditional {
    typedef First type;
};

template<typename First, typename Second>
struct conditional<false, First, Second> {
    typedef Second type;
};

template<typename...>
struct SpectatorOr;

template<>
struct SpectatorOr<> : public false_type { };

template<typename First>
struct SpectatorOr<First> : public First { };

template<typename First, typename Second>
struct SpectatorOr<First, Second> : public conditional<First::value, First, Second>::type { };

template<typename First, typename Second, typename Third, typename... Args>
struct SpectatorOr<First, Second, Third, Args...>
: public conditional<First::value, First, SpectatorOr<Second, Third, Args...>>::type { };

template<typename...>
struct SpectatorAnd;

template<>
struct SpectatorAnd<> : public true_type { };

template<typename First>
struct SpectatorAnd<First> : public First { };

template<typename First, typename Second>
struct SpectatorAnd<First, Second> : public conditional<First::value, Second, First>::type { };

template<typename First, typename Second, typename Third, typename... Args>
struct SpectatorAnd<First, Second, Third, Args...>
: public conditional<First::value, SpectatorAnd<Second, Third, Args...>, First>::type { };

template<typename Pred>
struct SpectatorNot : public integral_constant<bool, !Pred::value> { };

} // close namespace std
} // close namespace Spectator

#endif
