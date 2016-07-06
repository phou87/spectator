#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
#include "allocator_traits.h"
#include "type_traits.h"

struct ManagedClass {
    static int counter;

    ManagedClass() {}
    ManagedClass(const ManagedClass &)
    { ++counter; }
    explicit ManagedClass(int)
    { ++counter; }
    ManagedClass(int, int)
    { ++counter; }
    ManagedClass(int, int, int)
    { ++counter; }
};

int ManagedClass::counter = 0;

// Class that provides value_type and allocate/deallocate
template<typename T>
struct CustomAllocator1 {
    int counter;
    CustomAllocator1() noexcept : counter(0) {}

    typedef T value_type;

    template<class U>
    CustomAllocator1(const CustomAllocator1<U> &) noexcept : counter(0) {}

    T * allocate(::std::size_t n)
    { return static_cast<T *>((T *)::operator new(n * sizeof(T))); }

    void deallocate(T *p, std::size_t n)
    { ::delete(p); }

    void construct(T *p)
    { ++counter; }

    // Omit constructor with one integer parameter to test allocator_traits'
    // behavior (should call ::new instead of construct)

    void construct(T *p, int, int)
    { ++counter; }
};

// Class that provides explicit definitions of all traits
template<typename T>
struct CustomAllocator2 {
    typedef T value_type;
    typedef int * pointer;
    typedef const int * const_pointer;
    typedef int * void_pointer;
    typedef int * const_void_pointer;
    typedef char difference_type;
    typedef char size_type;

    CustomAllocator2() noexcept {}

    template<class U>
    CustomAllocator2(const CustomAllocator2<U> &) noexcept {}

    T * allocate(::std::size_t n)
    { return static_cast<T *>((T *)::operator new(n * sizeof(T))); }

    void deallocate(T *p, std::size_t n)
    { ::delete(p); }
};

template<typename Traits, typename Alloc>
struct StaticAllocatorTraitsVerifier {
    static void verifyExplicitTypes()
    {
        static_assert(
            std::is_same<typename Traits::allocator_type, Alloc>::value,
            "allocator_type must be of type Alloc!"
        );
        static_assert(
            std::is_same<typename Traits::value_type, typename Alloc::value_type>::value,
            "value_type must be of type Alloc::value_type!"
        );
        static_assert(
            std::is_same<typename Traits::pointer, typename Alloc::pointer>::value,
            "pointer must be of type Alloc::pointer!"
        );
        static_assert(
            std::is_same<typename Traits::const_pointer, typename Alloc::const_pointer>::value,
            "const_pointer must be of type Alloc::const_pointer!"
        );
        static_assert(
            std::is_same<typename Traits::void_pointer, typename Alloc::void_pointer>::value,
            "void_pointer must be of type Alloc::void_pointer!"
        );
        static_assert(
            std::is_same<typename Traits::const_void_pointer, typename Alloc::const_void_pointer>::value,
            "const_void_pointer must be of type Alloc::const_void_pointer!"
        );
        static_assert(
            std::is_same<typename Traits::difference_type, typename Alloc::difference_type>::value,
            "difference_type must be of type Alloc::difference_type!"
        );
        static_assert(
            std::is_same<typename Traits::size_type, typename Alloc::size_type>::value,
            "size_type must be of type Alloc::size_type!"
        );
    }

    static void verifyDefaultTypes()
    {
        static_assert(hasDefaultTypes(), "allocator_traits doesn't contain the proper default member types!");
    }

    static void verifyNonDefaultTypes()
    {
        static_assert(!hasDefaultTypes(), "allocator_traits doesn't properly overload its default member types!");
    }

    static void verifyDefaultTypesVerbose()
    {
        if (std::is_same<typename Traits::pointer, typename Alloc::value_type *>::value)
            std::cout << "pointer is properly set" << std::endl;

        if (std::is_same<
            typename Traits::const_pointer,
            typename std::pointer_traits<typename Traits::pointer>::template rebind<const typename Traits::value_type>
        >::value)
            std::cout << "const_pointer is properly set" << std::endl;

        if (std::is_same<
            typename Traits::void_pointer,
            typename std::pointer_traits<typename Traits::pointer>::template rebind<void>
        >::value)
            std::cout << "void_pointer is properly set" << std::endl;

        if (std::is_same<
            typename Traits::const_void_pointer,
            typename std::pointer_traits<typename Traits::pointer>::template rebind<const void>
        >::value)
            std::cout << "const_void_pointer is properly set" << std::endl;

        if (std::is_same<
            typename Traits::difference_type,
            typename std::pointer_traits<typename Traits::pointer>::difference_type
        >::value)
            std::cout << "difference_type is properly set" << std::endl;

        if (std::is_same<
            typename Traits::size_type,
            typename std::make_unsigned<typename Traits::difference_type>::type
        >::value)
            std::cout << "size_type is properly set" << std::endl;

        if (std::is_same<
            typename Traits::propagate_on_container_copy_assignment,
            typename Spectator::std::false_type
        >::value)
            std::cout << "propagate_on_container_copy_assignment is properly set" << std::endl;

        if (std::is_same<
            typename Traits::propagate_on_container_move_assignment,
            typename Spectator::std::false_type
        >::value)
            std::cout << "propagate_on_container_move_assignment is properly set" << std::endl;

        if (std::is_same<
            typename Traits::propagate_on_container_swap,
            typename Spectator::std::false_type
        >::value)
            std::cout << "propagate_on_container_swap is properly set" << std::endl;
    }

    static bool constexpr hasDefaultTypes()
    {
       return
            std::is_same<typename Traits::pointer, typename Alloc::value_type *>::value &&
            std::is_same<
                typename Traits::const_pointer,
                typename std::pointer_traits<typename Traits::pointer>::template rebind<const typename Traits::value_type>
            >::value &&
            std::is_same<
                typename Traits::void_pointer,
                typename std::pointer_traits<typename Traits::pointer>::template rebind<void>
            >::value &&
            std::is_same<
                typename Traits::const_void_pointer,
                typename std::pointer_traits<typename Traits::pointer>::template rebind<const void>
            >::value &&
            std::is_same<
                typename Traits::difference_type,
                typename std::pointer_traits<typename Traits::pointer>::difference_type
            >::value &&
            std::is_same<
                typename Traits::size_type,
                typename std::make_unsigned<typename Traits::difference_type>::type
            >::value &&
            std::is_same<
                typename Traits::propagate_on_container_copy_assignment,
                typename Spectator::std::false_type
            >::value &&
            std::is_same<
                typename Traits::propagate_on_container_move_assignment,
                typename Spectator::std::false_type
            >::value &&
            std::is_same<
                typename Traits::propagate_on_container_swap,
                typename Spectator::std::false_type
            >::value;
    }
};

int main() {
    typedef Spectator::std::allocator_traits<CustomAllocator1<ManagedClass>> Traits_t;
    typedef Traits_t::allocator_type Alloc_t;
    
    typedef StaticAllocatorTraitsVerifier<Traits_t, Alloc_t> Verify_t;
    Verify_t::verifyDefaultTypes();

    typedef Spectator::std::allocator_traits<CustomAllocator2<ManagedClass>> Traits2_t;
    typedef Traits2_t::allocator_type Alloc2_t;

    typedef StaticAllocatorTraitsVerifier<Traits2_t, Alloc2_t> Verify2_t;
    Verify2_t::verifyExplicitTypes();
    Verify2_t::verifyNonDefaultTypes();

    Alloc_t a;

    ManagedClass *ptr = Traits_t::allocate(a, 1);
    Traits_t::construct(a, ptr);

    assert(a.counter == 1);

    Traits_t::construct(a, ptr, 0);
    
    assert(a.counter == 1);
    assert(ManagedClass::counter == 1);

    Traits_t::destroy(a, ptr);
    Traits_t::construct(a, ptr, 1, 1);

    assert(a.counter == 2);
    assert(ManagedClass::counter == 1);

    Traits_t::construct(a, ptr, 1, 1, 1);

    assert(a.counter == 2);
    assert(ManagedClass::counter == 2);

    Traits_t::destroy(a, ptr);
    Traits_t::deallocate(a, ptr, 1);

    std::vector<int, CustomAllocator1<int>> foo = {10, 20, 30};
    for (auto x: foo) std::cout << x << " ";
    std::cout << '\n';

    return 0;
}
