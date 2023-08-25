#include <iostream>
#include "cpu.h"
#include "memory.h"
#include "opcode.h"

using namespace std;

int main() {
    cout << "Emulacion de CPU" << endl;
    Memory mem;

    CPU cpu;
    cpu.reset(mem);
    mem[0xFFFC] = INS_LDA_IM;
    mem[0xFFFD] = 0x42;
    cpu.execute(2,mem);

    return 0;
}