#include <iostream>
#include <array>
#include <vector>
#include <new>
using namespace std;

/*
Stack size is limited. Heap is large but slower.
void* is generic ptr. can point to any. need to cast before dereference
*/

// --- L8 ---
void func_1(int arr[]){
    std::cout << sizeof(arr) << std::endl;
}
void func_2(int* arr, size_t size){
    int sum = 0;
    for ( int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    
    std::cout << sum << std::endl;
}
template<size_t N>
void process(int (&arr)[N]){
    int sum = 0;
    for ( int i = 0; i < N; i++)
    {
        sum += arr[i];
    }
    
    std::cout << sum << std::endl;
}

// --- L8.2 ---
void print_fixed(const std::array<int, 4> &arr){
    int sum = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    
    std::cout << sum << std::endl;
}
void print_dynamic(const std::vector<int> &arr){
    int sum = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    for (int num: arr){
        sum += num;
    }
    
    std::cout << sum << std::endl;
}

int main(){
    // L1: Intro
    int health = 100;
    int *ptr = &health;
    std::cout << ptr << std::endl;

    // L2: Dereferencing
    int gold = 50;
    int *ptr_gold = &gold;
    *ptr_gold = 100;
    std::cout << gold << "\n";

    // L3: Heap
    int *heap_ptr = new int(42);
    std::cout << *heap_ptr << std::endl;
    delete heap_ptr;

    // L4: Void ptr
    void *void_ptr;
    double a = 3.14;
    void_ptr = &a;
    std::cout << *static_cast<double*>(void_ptr) << std::endl; // inside <> is the type we want to cast to

    // L5: Pointer size type
    char b = 'b';
    char *ptr_b = &b;
    std::cout << sizeof(void_ptr) << std::endl;
    std::cout << sizeof(ptr)<< std::endl;
    std::cout << sizeof(ptr_b) << std::endl;

    // L6: Arrays and Pointer Arithmetic
    // arr is equivalent to &arr[0]; *arr is equivalent to arr[0]
    // arr is a constant pointer, always pointing to the 1st element i.e: cant be re-assigned. But pointers to the arr can point to any elements and diff arrs.
    int int_arr[3] = {10, 20, 30};
    int *arr_ptr = int_arr; // cant do: &int_arr because that will give address of the entire block -> mismatch type int* != int(*)[3]
    std::cout << *(arr_ptr+1) << std::endl;

    // L7: Dynamic Arrays (heap)
    int *heap_arr = new int[5];
    heap_arr[0] = 10;
    heap_arr[1] = 20;
    heap_arr[2] = 30;
    heap_arr[3] = 40;
    heap_arr[4] = 50;
    for(int i = 0; i < 5; i++){
        std::cout << heap_arr[i] << std::endl;
    }
    delete[] heap_arr;

    // L8: Passing Arrays to Functions
    int test_arr[4] = {10, 20, 30, 40};
    std::cout << sizeof(test_arr) << std::endl;
    func_1(test_arr);
    func_2(test_arr, 4);
    process(test_arr);

    // L8.2: Modern Array
    // std::array<T, N>: used if size N is known. Else use: std::vector<T> for dynamic arrays (T is type)
    std::cout << "Modern arrays:" << std::endl;
    std::array<int, 4> std_arr = {1, 2, 3, 4};
    print_fixed(std_arr);
    std::vector<int> vector_arr = {1, 2, 3, 4};
    print_dynamic(vector_arr);

    // L9: Multi-dimensional Arrays
    std::cout << "Multi-dimensional Arrays:" << std::endl;
    // Static 2D array
    int matrix[3][4];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = i * 10 + j;
        }
        
    }
    std::cout << matrix[1][2] << std::endl; //1
    std::cout << *(*(matrix + 1) + 2) << std::endl; //2
    
    // Dynamic 2D array
    int **matrix_dynamic = new int*[3];
    for (size_t i = 0; i < 3; i++)
    {
        matrix_dynamic[i] = new int[4];
    }
    matrix_dynamic[1][2] = 12;
    std::cout << matrix_dynamic[1][2] << std::endl; //3

    for (size_t i = 0; i < 3; i++)
    {
        delete[] matrix_dynamic[i];
    }
    delete[] matrix_dynamic;

    // Contiguous Dynamic 2D array
    int* cont_matrix = new int[3 * 4];
    int rows = 3, cols = 4;
    cont_matrix[1 * cols + 2] = 12; // cont_matrix[1][2]

    auto at = [&](int r, int c) -> int&{
        return cont_matrix[r * cols + c];
    }; // & behind a type means reference. because the each element is an int, we ref the int by using int&.
    // if dont ref then it's a copy, not the original value.

    at(1, 2) = 12;
    std::cout << at(1, 2) << std::endl; //4
    delete[] cont_matrix;

    // Modern 2D array
    std::vector <std::vector <int>> vector_matrix(3, std::vector<int>(4));
    vector_matrix[1][2] = 12;
    std::cout << vector_matrix[1][2] << std::endl; //5

    // L10: Const and Pointers
    int org = 10;
    int* normal_ptr = &org;
    const int* ptr_to_const = &org; // cant change value from ptr
    int* const const_ptr = &org; // cant change ptr address
    const int* const const_ptr_to_const = &org; // both of the 2 above

    //illegal ops
    /* *ptr_to_const = 20; 
    const_ptr = &rows; */
    //expression must be a modifiable lvalue

    // L11: Breaking constness
    // use const for memory and readability, always start with const unless we can prove that the var will change
    int non_const_int = 1;
    const int* ptr_to_non_const_int = &non_const_int;
    int* change_ptr = const_cast<int*>(ptr_to_non_const_int);
    *change_ptr = 2;
    std::cout << non_const_int << std::endl;
    std::cout << *change_ptr << std::endl;
        // non-const int displays 2 for both, const int displays 1 and then 2
        // use this for when a legacy func or api doesnt use const correctly or missing const, then we can const_cast

    // L12: Placement New
    // Instead of using just new ... (which allocates memo on heap and constructs object then returns pointer all at once)
    // We can use placement new, which constructs on pre-allocated memory we've made elsewhere. 
    // We can decide what we want to construct on that allocated memo
    // Would also return a pointer, but we have much more control over how we want to mangage the space.
    // Use cases: memo pool with offsets (faster than heap allocation new), reconstructing in place (avoid overhead of requesting and deallocating), custom allocators
    char buffer[sizeof(int)];
    int* placement_new_ptr = new (buffer) int(42);
    std::cout << *placement_new_ptr << std::endl;
    //placement_new_ptr -> ~int();

    class MyClass
    {
    public:
        MyClass(int x, double y){
            std::cout << "Constructed" << std::endl;
        };
        ~MyClass(){
            std::cout << "Destroyed" << std::endl;
        };
    };

    alignas(MyClass) char class_buffer[sizeof(MyClass) * 2]; //alignas ensures that the buffer is byte-algined
    MyClass* my_class_ptr1 = new (class_buffer) MyClass(1, 2);
    MyClass* my_class_ptr2 = new (class_buffer + sizeof(MyClass)) MyClass(3, 4);

    my_class_ptr2->~MyClass();
    my_class_ptr1->~MyClass();
    // In-place construction
    MyClass* bonus = new MyClass(3, 5);
    bonus->~MyClass(); // if we don't deconstruct, it will just overwrite the old object (which is bad depending on what the deconstruction does)
    new (bonus) MyClass(2, 1); // this takes the old space left by the 1st object
    delete bonus; // deletes 2nd object


    // L13: 
}

