#include <iostream>
using namespace std;

int global_var = 5; // stored on .data, global class



int main() {
    int local_var = 2; // stored on stack, auto class
    static int static_local_var_unint; // stored on .bss (uninit), static class
    static int static_local_var_init = 1; // stored on .data (init), static class
    int* heap_var = new int(2); // pointer stored on stack, pointing to an allocation stored on heap, auto+heap allocation class

    std::cout << "Global var: " << &global_var;
    std::cout << "\nLocal var: " << &local_var;
    std::cout << "\nStatic Local uninit var: " << &static_local_var_unint;
    std::cout << "\nStatic Local init var: " << &static_local_var_init;
    std::cout << "\nHeap var: " << &heap_var;

    // Stack auto cleans, heap doesn't. If don't clean up, got a MEMORY LEAK
    // Clean up heap allocation
    delete heap_var;

}

/* 
stack: funtion scoped. If function returns a large resource/object, that means everytime it is called/passed, the stack allocates space, copy it over,
delete the space. Then if it's called again, the same process repeats. re-allocate, re-initialize, and re-delete is a PROBLEM

heap: not scoped. We init and allocate it once on the heap, then pass around the pointer to other places/funcs instead. (pointer on stack but super light ~4 bytes)
No repetition and no long processes.
*/