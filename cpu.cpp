#include <stdio.h>
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

Byte CPU::fetchByte(u32 &cycles, Memory &memory) {
    //Byte Data = memory.getData()[programCounter];
    Byte Data = memory[programCounter];
    programCounter++;
    cycles--;
    return Data;
}


Byte CPU::writeByteMemory(u32 &cycle,const Byte &address,const Byte &value, Memory& memory) {
    if(memory[address] == 0) {
        memory[address] = value;
        cycle--;
    } else {
        // Generar un error
    }
}

Byte CPU::readByte(u32 &cycles,const Byte &address, Memory& memory) {
    Byte Data = memory[address];
    cycles--;
    return Data;
}

void CPU::LDASetStatus() {
    zf = (A == 0);
    nf = (A == 0b10000000) > 0;
}

void CPU::LDXSetStatusFlags() {
    zf = (X == 0);
    nf = (X == 0b10000000) > 0;
}

void CPU::execute(u32 cycles,Memory &memory) {
    while( cycles > 0 ) {
        Byte ins = fetchByte( cycles, memory);        
        switch (ins) {
            // Estableciendo distintos modos de acceso para el LDA
            case INS_LDA_IM: {
                Byte value = fetchByte(cycles, memory);
                A = value;
                LDASetStatus();
                break;
            }
            case INS_LDA_ZP: {
                Byte zeroPageAddress = fetchByte(cycles, memory);
                A = readByte( cycles, zeroPageAddress, memory);
                LDASetStatus();
                break;
            }


            // Estableciendo distintas direccciones de modod de acceso para el LDX
            case INS_LDX_IM: {
                Byte value = fetchByte(cycles, memory);
                X = value;
                LDXSetStatusFlags();
                break;
            }

            case INS_LDY_IM: {
                Byte value = fetchByte(cycles, memory);
                Y = value;
                LDXSetStatusFlags();
                break;
            }

            case INS_STA_ZP: {
                // TODO: Comprobar si tienen un acumulador
                Byte acumulator_data = A; 
                for (size_t i = 0; i < memory.getData().size(); i++) {
                    if(memory[i] == 0) {
                        memory[i] = acumulator_data;
                    }
                }
                break;
            }
            default:
                std::cerr << "Instruction not handled: " << ins << std::endl;
                break;
        }
    }
}


void CPU::PrintStatus() const
{
	printf( "A: %d X: %d Y: %d\n", A, X, Y );
	printf( "PC: %d SP: %d\n", programCounter, stackPointer);
}