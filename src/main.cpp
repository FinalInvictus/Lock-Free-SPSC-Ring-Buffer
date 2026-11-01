#include <iostream>
#include <thread>
using namespace std;
int counter =0;
void increment() {
    for (int i=0;i<1000000;++i)
        counter++;
}
int main() {
    thread a(increment);
    thread b(increment);
    a.join();
    b.join();
    cout<<counter<<'\n';
    return 0;
}
