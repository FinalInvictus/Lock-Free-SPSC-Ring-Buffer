#include <array>
#include <iostream>

template <typename T, std::size_t Capacity>
class SPSC_Queue {
private:
    std::array <T,Capacity> buffer{};
    std::size_t head = 0;
    std::size_t tail = 0;
    std::size_t next(std::size_t index) const{
        return (index+1)%Capacity;
    }
public:
    static_assert(Capacity>=2, "Capacity must be atleast 2");
    bool empty() const {
        return head == tail;
    }
    bool full() const {
        return next(tail)==head;
    }
    bool push(const T &val) {
        if (full()) {
            std::cout<<"The Queue is FULL!\n";
            return false;
        }
        buffer[tail] = val;
        tail = next(tail);
        return true;
    }
    bool pop(T &val) {
        if (empty()) {
            std::cout<<"The Queue is Empty!\n";
            return false;
        }
        val = buffer[head];
        head = next(head);
        return true;
    }
};

int main() {
    constexpr std::size_t Capacity = 4;
    //constexpr is used to let the compiler know that the variable can be executed at the compile time
    //Using that would move the computation to happen during compile time
    SPSC_Queue<int,Capacity> queue;
    int i =0;
    //Push into the Queue until its full!
    while (queue.push(i)) {
        std::cout<<"Pushed element: "<<i<<'\n';
        ++i;
    }
    //Pop the queue until its empty!
    while (queue.pop(i)) {
        std::cout<<"popped an elemenet\n";
        --i;
    }

}