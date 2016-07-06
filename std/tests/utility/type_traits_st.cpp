#include "type_traits.h"
#include "is_abstract.h"
#include <iostream>

using namespace std;

class TestAbstractClass {
    virtual void foo() = 0;
};

class TestClass {

};

struct TestStruct {

};

union TestUnion {

};

enum TestEnum {

};

int main() {
    cout << boolalpha;

    cout << Spectator::std::is_abstract<TestClass>::value << endl;
    cout << Spectator::std::is_abstract<TestAbstractClass>::value << endl;
    cout << Spectator::std::is_abstract<TestEnum>::value << endl;

    cout << Spectator::std::is_class<TestClass>::value << endl;
    cout << Spectator::std::is_class<TestStruct>::value << endl;
    cout << Spectator::std::is_class<TestUnion>::value << endl;
    cout << Spectator::std::is_class<TestEnum>::value << endl;
    cout << Spectator::std::is_class<int>::value << endl;

    cout << Spectator::std::is_enum<TestClass>::value << endl;
    cout << Spectator::std::is_enum<TestStruct>::value << endl;
    cout << Spectator::std::is_enum<TestUnion>::value << endl;
    cout << Spectator::std::is_enum<TestEnum>::value << endl;
    cout << Spectator::std::is_enum<int>::value << endl;

    return 0;
}
