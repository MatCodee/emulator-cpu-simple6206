#include <iostream>
#include "cpu.h"
#include "memory.h"

using namespace std;

int main() {
    cout << "Emulacion de CPU" << endl;
    Memory mem;
    CPU cpu;
    cpu.reset(mem);

    return 0;
}