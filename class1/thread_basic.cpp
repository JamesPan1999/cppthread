#include <thread>
#include <iostream>

class Background_task {
public:
    Background_task(std::string &&str) {
        // 假装对成员进行初始化
    }

    Background_task() {
        // 假装对成员进行初始化
    }

    void operator()(std::string str) {
        std::cout << "str is " << str << std::endl;
    }
    void  operator()(){
        std::cout << "no input" << std::endl;
    }
};

static void catch_exception() {
    std::string some_local_state = "str";
    Background_task task{std::string("hello")};
    std::thread th_task{task, "helloexcp"};
    try {
        // do something but wrong
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } catch (std::exception& e) {
        // 进行一些信号量同步，以使得一些阻塞的线程能够执行下去
        // 。。。
        th_task.join();  // 最简单的情况是要保证主线程突然崩掉的时候等待子线程先返回
        throw;
        // std::cout << "exception: " << e.what() << std::endl;
    }
    th_task.join();
}

int main(int argc, char* argv[]) {
    Background_task task;
    std::thread t((Background_task()));
    std::thread t1{Background_task(), "hello"};
    std::thread t2(Background_task());

    t.join();
    t1.join();
//    task("hello2");
    catch_exception();
    return 0;
}