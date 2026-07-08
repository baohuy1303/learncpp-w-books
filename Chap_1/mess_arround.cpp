#include <iostream>
using namespace std;

int create_classroom(){
    int count = 30;
    return count;
}

int main(){
    int count = create_classroom();
    std::cout << count;
}