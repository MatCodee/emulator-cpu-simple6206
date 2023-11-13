#include <iostream>
#include "cpu.h"
#include "memory.h"
#include "opcode.h"
using namespace std;


void test() {
    Memory mem;

    CPU cpu;
    cpu.reset(mem);
    //cpu.PrintStatus();
    mem[0xFFFC] = INS_LDA_IM;
    mem[0xFFFD] = INS_PHA;
    
    
    cout << "informacion del Stack " << endl;
    cout << mem.getData().size() << endl; 
    //cpu.execute(3,mem);
}
