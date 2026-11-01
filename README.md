# Lock-Free-SPSC-Ring-Buffer
A high-performance lock-free Single-Producer Single-Consumer (SPSC) Ring Buffer implemented in C++ designed for efficient inter-thread communication with minimal synchronization overhead.

# Lock Free queues
1. head - insertion to the queue is made
2. tail - consumer reads from here
when we reach end of the queue --> wrap back to the beginning

## Fast Wrap-Around
- Cant do index%size because it takes 10 - 20 CPU cycles
- WE can have the capacity as power of 2 and do bitwise AND mask
- index & (capacity -1) because AND bitwise takes 1 cycle

# Cache Coherence
- Memory is derived from RAM to l1/l2 cache in 64-byte chunks and these are called cache lines
- MESI - CPU's cache coherence protocol
- To maximize performance --> CPUs execute instructions out of order and compliers optimize memory accesses
- By doing this, the work of core 1 will be visible later to the core 2 thus creating a data race


## Data race that we want to prevent
### 1. The Code: 

![img.png](Data/img.png)
### 2. The Output: 

![img_1.png](Data/img_1.png)

## Analysis: 
- Here we can see that more than half of our progress is lost
- counter++ --> RMW (read-move-write) operation
- CPU cores fetch the value from the memory into their own private L1 cache
- both independently add 1 and upload it to the main memory
- This causes one thread to overwrite the others
- This entire ordeal can be solved by using Lock Free Queue

# Distinguishing Empty Queue from Full Queue:
We can do this in 2 ways:

## Approach 1: Reserving one empty slot in the end:
- For an array of n slots, n-1 slots can only be filled leaving the nth slot empty
- Empty: head == tail
- Full: (tail+1)%capacity == head
- Trade off: We waste one memory slot but we dont have to worry about integer limits

## Approach 2: Monotonic increasing counters:
- head, tail --> Unsigned integers
- Empty: head == tail
- Full: tail - head == capacity
- Trade off: Heavily depends on c++ unsigned integer rules 
- Works very well if capacity is a power of 2 because it can be optimized to a bitwise AND



