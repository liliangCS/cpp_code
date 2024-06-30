#include <iostream>

// 类A
class A {
public:
    void memberFunction() {
        std::cout << "Class A member function called" << std::endl;
    }
};

// 类B
class B {
public:
    // 定义类A的成员函数指针类型
    typedef void (A::*MemberFunctionPointer)();

    // 类B中的字段，指向类A的成员函数
    MemberFunctionPointer functionPtr;

    // 用于调用成员函数的成员方法
    void callMemberFunction(A& a) {
        if (functionPtr) {
            (a.*functionPtr)();
        }
    }
};

int main() {
    A a;
    B b;

    // 设置类B的字段，指向类A的成员函数
    b.functionPtr = &A::memberFunction;

    // 使用类B的方法调用类A的成员函数
    b.callMemberFunction(a);

    return 0;
}
