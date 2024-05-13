//
// Created by ubuntu64 on 2024/5/13.
//
#include <thread>
#include <iostream>
#include <memory>
#include <chrono>
#include <functional>
#include <unistd.h>
#include <string>
#include <stdio.h>

struct Func {
        int& _i;
        explicit Func(int & i): _i(i){}
        void operator()() {
            for (int i = 0; i < 4; i++) {
                _i = i;
                std::cout << "_i is " << _i << std::endl;
                // write(STDOUT_FILENO, std::to_string(_i).c_str(), 1);  // 系统调用
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
};
void oops() {
    int some_local_state = 0;
    Func myfunc(some_local_state);
    std::thread functhread(myfunc);  // 传入可执行对象
    //隐患，访问局部变量，局部变量可能会随着}结束而回收或随着主线程退出而回收
    functhread.detach();

//    functhread.join();
}
// 伪闭包   感觉错误
void oops2() {
    int some_local_state = 0;
    auto myfunc = std::make_shared<Func>(some_local_state); // 使用std::make_shared更安全
    std::function<void()> function = std::bind(&Func::operator(), myfunc, std::placeholders::_1); // 正确绑定成员函数
//    std::thread functhread(myfunc);  //报错
    std::thread functhread(function);  // 由于智能指针本身不是可执行对象，所以必须在外面包一层函数指针

    functhread.detach();
}   // myfunc被析构  但其所指向的内存并没有

// detach 注意事项
int main() {

    oops();
//    oops2();   //出oops2的作用域后，局部资源如果没有智能指针的保护将被释放

    //防止主线程退出过快，需要停顿一下，让子线程跑起来detach
    std::this_thread::sleep_for(std::chrono::seconds(5));  //如果提前结束会导致子线程打印的东西没有地方显示
}
