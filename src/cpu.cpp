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

void CPU::PrintStatus() const {
	printf( "A: %d X: %d Y: %d\n", A, X, Y );
	printf( "PC: %d SP: %d\n", programCounter, stackPointer);
}

Byte CPU::fetchByte(u32 &cycles, Memory &memory) {
    //Byte Data = memory.getData()[programCounter];
    Byte Data = memory[programCounter];
    programCounter++;
    cycles--;
    return Data;
}

// Analizar la informacion de este contenido no entiendo este proceso de fetchWord
Word CPU::fetchWord(u32 &cycles, Memory &memory) {
    Word data = memory[programCounter];

    programCounter++;
    data |= (memory[programCounter] << 8);
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
void CPU::TSXSetStatusFlag() {
    zf = (X == 0);
    nf = (X & 0x80) != 0;
}
void CPU::TAXSetStatusFlag() {
    zf = (X == 0);
    nf = (X & 0x80) != 0;
}
void CPU::TAYSetStatusFlag() {
    zf = (X == 0);
    nf = (X & 0x80) != 0;
}
void CPU::TXASetStatusFlag() {
    zf = (A == 0);
    nf = (X & 0x80) != 0;
}

// Estatus flag para incrementos y decrementos  en las instrucciones
void CPU::SetZeroAndNegativeFlags(Byte &reg) {
    zf = (reg == 0);
    nf = (reg & 0x80) != 0;
}

void CPU::execute(u32 cycles,Memory &memory) {
    while( cycles > 0 ) {
        Byte ins = fetchByte( cycles, memory);        
        switch (ins) {
            // LOAD/ STORE OPERATIONS
            // Estableciendo distintos modos de acceso para el LDA
            case INS_LDA_IM: {
                Byte value = fetchByte(cycles, memory);
                A = value;
                LDASetStatus();
                PrintStatus();
                memory.printMemory();
            } break;

            // Aqui hago una comprobacion de lectura
            case INS_LDA_ZP: {
                Byte zeroPageAddress = fetchByte(cycles, memory);
                A = readByte( cycles, zeroPageAddress, memory);
                LDASetStatus();
                PrintStatus();
                //memory.printMemory();
            } break;
 
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
                Byte zeroPageAddress = fetchByte(cycles, memory);
                Word address = zeroPageAddress;
                writeByte(X, cycles, address, memory);
            } break;

            // TODO: Comprobar si esta instruccion esta correcta
            case INS_STY_ZP: {
                Byte zeroPageAddress = fetchByte(cycles, memory);
                Word address = zeroPageAddress;
                writeByte(Y, cycles, address, memory);
            } break;

            // REGISTER TRANSFERS
            case INS_TAX: {
                X = A;
                cycles--;
                TAXSetStatusFlag();

            } break;
            case INS_TAY: {
                Y = A;
                cycles--;
                TAYSetStatusFlag();
            } break;
            case INS_TXA: {
                A = X;
                cycles--;
                TXASetStatusFlag();
            } break;
            case INS_TYA: {
                A = Y;
                cycles--;
                TXASetStatusFlag();
            } break;

            // STACK OPERATIONS
            case INS_TSX: {
                X = stackPointer;
                TSXSetStatusFlag();
            } break;
            case INS_TXS: {
                stackPointer = X;
            } break;

            case INS_PHA: {
                Byte value = A;
                stackPointer--;
                memory.PushMemory(value,stackPointer);
                PrintStatus();
                memory.printMemory();                
            } break;

            
            // LOGICAL

            case INS_AND_IM: {
                Byte value = fetchByte(cycles, memory);
                A &= value;
                cycles--; //  ver si es necesario restar el cycle
                SetZeroAndNegativeFlags(A);
            } break;
            case INS_EOR_IM: {
                Byte value = fetchByte(cycles, memory);
                // XOR
                A = A ^ value; 
                cycles--; //  ver si es necesario restar el cycle
                SetZeroAndNegativeFlags(A);
            } break;
            case INS_ORA_IM: {
                Byte value = fetchByte(cycles, memory);
                A |= value;
                cycles--; //  ver si es necesario restar el cycle
                SetZeroAndNegativeFlags(A);
            } break;
            case INS_BIT_ZP: {
                //Word address = fetchByte(cycles, memory);
                // TODO: VER COMO FUNCIONA BIEN ESTA INSTRUCCION
            } break;

            // Arithmetic
            case INS_ADC: {    
                Byte value = fetchByte(cycles, memory);
                
                
                Word result = A + value + (carryFlag ? 1 : 0);

                // Manejo de Excepciones aqui de INS ADC

                A = result;
                carryFlag = result > 0xFF;
                cycles--;
            } break;
            case INS_SBC: {
                Byte value = fetchByte(cycles, memory);
                Word result = A - value - (carryFlag ? 1 : 0); // no se si esta implementacion esta correcta
                carryFlag = result > 0xFF;
                cycles--;

            } break;
            case INS_CMP: {
                // compare A with memory value
                Byte value = fetchByte(cycles, memory);
                Byte compare = value & A; // No se si esta implementacion esta correcta
                carryFlag = result > 0xFF;
                cycles--;
            } break;
            case INS_CPX: {

            } break;
            case INS_CPY: {

            } break;

            // Increments & Decrements

            case INS_INC_ZP: {
                Word address = fetchByte(cycles, memory);
                Byte value = readByte(cycles, address, memory);
                value++;
                cycles--;
                writeByte(value, cycles, address, memory);
                // Flags
                SetZeroAndNegativeFlags(value);
                // Set Status flag
            } break;
            case INS_INX: {
                X++;
                cycles--;
                SetZeroAndNegativeFlags(X);
            } break;
            case INS_INY: {
                Y++;
                cycles--;
                SetZeroAndNegativeFlags(Y);
            } break;
            case INS_DEC_ZP: {
                Word address = fetchByte(cycles, memory);
                Byte value = readByte(cycles, address, memory);
                value--;
                cycles--;
                writeByte(value, cycles, address, memory);
                SetZeroAndNegativeFlags(value);
                // Set Status flag
            } break;
            case INS_DEX: {
                X--;
                cycles--;
                SetZeroAndNegativeFlags(X);
            } break;
            case INS_DEY: {
                Y--;
                cycles--;
                SetZeroAndNegativeFlags(Y);
            } break;


            // Shifts
            case INS_ASL: {

            } break;

            case INS_LSR: {

            } break;

            case INS_ROL: {

            } break;
            case INS_ROR: {

            } break;
            
            //Jumps & Calls

            /*
            case INS_RTS: {
                programCounter = memory[programCounter - 1];
                // Quitar el ultimo elemento de la direccion 
            
            } break;
            */
            // No se is esta implementacion esta correcta
            //
            case INS_JSR: {
                Word subAddress = fetchWord(cycles, memory);

                memory[stackPointer] = stackPointer - 1;
                stackPointer++;
                cycles--;
                programCounter = subAddress;
                cycles--;
            } break;

            // Branches
            case INS_BEQ: {

            } break;
            case INS_BNE: {

            } break;
            case INS_BCS: {

            } break;
            case INS_BCC: {

            } break;
            case INS_BMI: {

            } break;
            case INS_BPL: {

            } break;
            case INS_BVC: {

            } break;
            case INS_BVS: {

            } break;
            // Status Flag Changes
 
            case INS_CLC: {

            } break;
            case INS_SEC: {

            } break;
            case INS_CLD: {

            } break;
            case INS_SED: {

            } break;
            case INS_CLI: {

            } break;
            case INS_SEI: {

            } break;
            case INS_CLV: {

            } break;

            // System Functions


            default:
                std::cerr << "Instruction not handled: " << ins << std::endl;
                break;
        }
    }
}

