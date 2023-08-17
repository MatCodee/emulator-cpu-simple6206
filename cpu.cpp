#include "cpu.h"

void CPU::reset(Memory &memory) {
    programCounter = 0xFFFC;
    stackPointer = 0x0100;
    dm = 0;
    cf = zf = id = dm = bc = of = 0;
    A = X = Y = 0;
    memory.Initialise();
}
Byte CPU::fetchByte(u32 cycles, Memory &memory) {
    //Byte Data = memory.getData()[programCounter];
    Byte Data = memory[programCounter];
    programCounter++;
    cycles--;
    return Data;
}

static constexpr Byte INS_LDA_IM = 0xA9;

void CPU::execute(u32 cycles,Memory &memory) {
    while( cycles > 0 ) {
        Byte ins = fetchByte( cycles, memory);
        switch (ins) {
            case INS_LDA_IM: {
                Byte value = fetchByte(cycles, memory);
                A = value;
                zf = (A == 0);
                nf = (A == 0b10000000) > 0;
                break;
            }
            default:
                std::cerr << "Instruction not handled: " << ins << std::endl;
                break;
        }
    }
}
