#include <iostream>
#include "cpu.h"
#include "memory.h"
#include "opcode.h"

using namespace std;


void test() {
    Memory mem;

    /*
    Intrucciones de prueba:
    INS_LDA_IM
    INS_PHA
    */

    CPU cpu;
    cpu.reset(mem);
    cpu.PrintStatus();
    mem[0xFFFC] = INS_LDA_IM;
    mem[0xFFFD] = 0x42;
    cpu.execute(2,mem);
}



int main() {
    cout << "Emulacion de CPU" << endl;
    test();
    
    return 0;
}