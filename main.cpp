#include <iostream>

#include <fmt/format.h>

#include "cpu.h"
#include "memory.h"
#include "opcode.h"



using namespace std;

void test() {
    Memory mem;

    CPU cpu;
    cpu.reset(mem);
    mem[0xFFFC] = INS_LDA_IM;
    mem[0xFFFD] = 0x42;
    mem[0x0042] = 0x84;
    cpu.execute(3,mem);
}


int main() {
    cout << "Emulacion de CPU" << endl;
    //test();
    cout << "hola comol estas" << endl;
    int number = 1;
    fmt::print(stdout,"Yout code = {}\n",number);

    return 0;
}