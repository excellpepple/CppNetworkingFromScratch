//
// Created by excel on 6/30/2025.
//
#include <iostream>
#include <thread>

int run(int * arg, int * res) {
    int *a = arg;
    std::cout << "Thread: is Running! with arg "<< *a << std::endl;
    std::cout << "Hello Thread!" << std::endl;
    *res = 12;
    return 0;
}


int main() {

    int arg = 2003, result;
    std::thread thread1(run, &arg, &result);
    std::thread::id threadID = thread1.get_id();

    std::cout << "Main line is busy...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    thread1.join();
    std::cout << "Thread joined!\n";
    std::cout << "Thread ID: " << threadID << " |Returned: "<< result << std::endl;
    std::cout << "Done!\n";
    std::cin.get();

}