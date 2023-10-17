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

Word CPU::fetchWord(u32 &cycles, Memory &memory) {
    Word data = memory[programCounter];
    programCounter++;

    data = (memory[programCounter] );
    programCounter++;
    cycles+=2;
    return data;
}


void CPU::writeByteMemory(u32 &cycle,const Byte &address,const Byte &value, Memory& memory) {
    if(memory[address] == 0) {
        memory[address] = value;
        cycle--;
    } else {
        // Generar un error
    }
}

Byte CPU::readByte(u32 &cycles,const Byte &address,const Memory& memory) {
    Byte Data = memory[address];
    cycles--;
    return Data;
}


void CPU::writeByte(const Byte &value,u32 &cycles, const Byte &address, Memory &memory) {
    memory[address] = value; 
    cycles--;
}

/* Escribe 2 bytes */
/*
void CPU::writeWord(Word value, u32 cycles, u32 address) {
    Data[address] = value & 0xFF;
    Data[addresss + 1] = (value >> 8);   
    cycles--;
}
*/

// Funciones que resetean los estados del proceso
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
            // LDA
            // Estableciendo distintos modos de acceso para el LDA
            case INS_LDA_IM: {
                Byte value = fetchByte(cycles, memory);
                A = value;
                LDASetStatus();
            } break;
            case INS_LDA_ZP: {
                Byte zeroPageAddress = fetchByte(cycles, memory);
                A = readByte( cycles, zeroPageAddress, memory);
                LDASetStatus();
            } break;
            
            // No entiendo muy bien esta operacion REPASAR en el futuro
            case INS_LDA_ZPX: {
                Byte zeroPageAddressX = fetchByte(cycles, memory);
                zeroPageAddressX += X;
                cycles--;
                A = readByte(cycles, zeroPageAddressX, memory);
                LDASetStatus();
            } break;

            // LDX
            // Estableciendo distintas direccciones de modod de acceso para el LDX
            case INS_LDX_IM: {
                Byte value = fetchByte(cycles, memory);
                X = value;
                LDXSetStatusFlags();
            } break;

            // LDY
            case INS_LDY_IM: {
                Byte value = fetchByte(cycles, memory);
                Y = value;
                LDXSetStatusFlags();
            } break;

            // STA
            // Esto es malo verificar pa operacion STA
            case INS_STA_ZP: {
                Byte zeroPageAddress = fetchByte(cycles, memory);
                Word address = zeroPageAddress;
                writeByte(A, cycles, address, memory);
            } break;

            case INS_STX_ZP: {

            } break;
            case INS_STY_ZP: {

            } break;
            /*
            // No se is esta implementacion esta correcta
            case INS_JSR: {
                Word subAddress = fetchWord(cycles, memory);
                memory[stackPointer] = stackPointer - 1;
                stackPointer++;
                cycles--;
                programCounter = subAddress;
                cycles--;
            } break;
            */
            default:
                std::cerr << "Instruction not handled: " << ins << std::endl;
                break;
        }
    }
}

void CPU::PrintStatus() const {
	printf( "A: %d X: %d Y: %d\n", A, X, Y );
	printf( "PC: %d SP: %d\n", programCounter, stackPointer);
}