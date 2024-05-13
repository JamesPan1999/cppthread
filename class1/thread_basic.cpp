#include <thread>
#include <iostream>

class Background_task {
public:
    void operator()(std::string str) {
        std::cout << "str is " << str << std::endl;
    }
    void  operator()(){
        std::cout << "no input" << std::endl;
    }
};
int func();

int main(int argc, char* argv[]) {
    Background_task task;
    std::thread t((Background_task()));
    std::thread t1{Background_task(), "hello"};
    std::thread t2(Background_task());

    t.join();
    t1.join();
//    task("hello2");
    return 0;
}