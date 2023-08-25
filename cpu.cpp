#include "cpu.h"
#include "opcode.h"

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


void CPU::execute(u32 cycles,Memory &memory) {
    while( cycles > 0 ) {
        Byte ins = fetchByte( cycles, memory);

        std::cout << "Instruccion" << std::endl;
        std::cout << ins << std::endl;
        
        switch (ins) {
            case INS_LDA_IM: {
                Byte value = fetchByte(cycles, memory);
                A = value;
                zf = (A == 0);
                nf = (A == 0b10000000) > 0;
                std::cout << "Entrando a la instruccion: " << std::endl;
                std::cout << "Cargando memoria en el acumulador: " << A << std::endl;
                std::cout << "Modificando las flags: zerp flags " << zf << ", negative flags " << nf << std::endl;
                break;
            }
            default:
                std::cerr << "Instruction not handled: " << ins << std::endl;
                break;
        }
    }
}
