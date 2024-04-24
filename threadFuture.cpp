#include<iostream>
#include<thread>
#include<future>

// std::future provides the programmers with the method for thread communication in asynchronous programming in C++ in an easy way.
// It is especially helpful in cases where we need to do some tasks in the background and need the result of that task in the main process.

int main() {
    // lambda expression that returns 7 into a std::packaged_task
    std::packaged_task<int()> task([](){return 7;});
    // get the future of task
    std::future<int> result = task.get_future();    // // run task in a thread

    std::thread(std::move(task)).detach();

    std::cout << "Waiting...";

    result.wait();  // block until future arrives

    std::cout << "\t Done!" << "\nfuture result is: " << result.get();

    return 0;
}