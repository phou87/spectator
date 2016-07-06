#ifndef SPECTATOR_CONST_VOLATILE_QUALIFICATIONS
#define SPECTATOR_CONST_VOLATILE_QUALIFICATIONS

namespace Spectator {
namespace std {

template<typename T>
struct add_const {
    typedef T const type;
};

template<typename T>
struct add_volatile {
    typedef T volatile type;
};

template<typename T>
struct add_cv {
    typedef typename add_const<typename add_volatile<T>::type>::type type;
};

template<typename T>
struct remove_const {
    typedef T type;
};

template<typename T>
struct remove_const<T const> {
    typedef T type;
};

template<typename T>
struct remove_volatile {
    typedef T type;
};

template<typename T>
struct remove_volatile<T volatile> {
    typedef T type;
};

template<typename T>
struct remove_cv {
    typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

} // close namespace std
} // close namespace Spectator

#endif
