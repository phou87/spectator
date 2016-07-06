#ifndef __SPECTATOR_VECTOR_H
#define __SPECTATOR_VECTOR_H

namespace Spectator {
namespace std {

template <typename T>
class vector {

    public:
        
        typedef T       value_type;
        typedef T*      pointer;

        vector();
        vector(size_type n, const value_type &val = value_type());
        vector(const vector &x);

        template <class InputIterator>
        vector(InputIterator first, InputIterator last);

    private:

        pointer        

};

} // close namespace std
} // close namespace Spectator

#endif
