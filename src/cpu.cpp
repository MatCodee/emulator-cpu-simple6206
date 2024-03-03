#include <stdio.h>
#include "cpu.h"
#include "opcode.h"

void CPU::reset(Memory &memory) {
    programCounter = 0xFFFC;
    stackPointer = 0x0100;
    dm = 0;
   
    // temporal
    cf = zf = id = dm = bc = of = nf = 0;

    flag.cf = flag.zf = flag.id = flag.dm = flag.bc = flag.of = flag.nf = 0;

    A = X = Y = 0;
    memory.Initialise();
}


void CPU::PrintStatus() const {
	printf( "A: %d X: %d Y: %d\n", A, X, Y );
	printf( "PC: %d SP: %d\n", programCounter, stackPointer);
}

Byte CPU::fetchInstruction(Memory& memory) {
    Byte Data = memory[programCounter];
    programCounter++;
    return Data;
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
    cycles-=2;
    return data;
}

void CPU::loadValue(u32& cycles,Byte& addrStart, const Byte& addrEnd) {
    addrStart = addrEnd;
    cycles--;
}

void CPU::pushMemoryStack(u32& cycles,const Byte &value, Memory &memory) {
    memory[stackPointer] = value;
    cycles--;
    stackPointer--;
    cycles--;
}
Word CPU::readMemoryStack(u32& cycles, Memory& memory) {
    Word value = memory[stackPointer];
    cycles--;
    stackPointer++;
    cycles--;
    return value;
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

void CPU::writeWord(Word value, u32& cycles,const u32 address, Memory &memory) {
    Memory[address] = value & 0xFF;
    Memory[address+1] = (value >> 8);
    cycles-=2;
}


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
        Byte ins = fetchInstruction(memory);
        switch (ins) {
            // LOAD/ STORE OPERATIONS
            case INS_LDA_IM: {
                Byte value = fetchByte(cycles, memory);
                loadValue(cycles, A, value);
                LDASetStatus();
            } break;
            case INS_LDA_ZP: {
                Byte zeroPageAddress = fetchByte(cycles, memory); 
                //A = readByte( cycles, zeroPageAddress, memory); 
                loadValue(cycles, A, readByte(cycles, zeroPageAddress, memory));
                LDASetStatus();
            } break;
 
            case INS_LDA_ZPX: {
                Byte zeroPageAddressX = fetchByte(cycles, memory);
                zeroPageAddressX += X;
                cycles--;
                A = readByte(cycles, zeroPageAddressX, memory);
                cycles--;
                LDASetStatus();
            } break;

            // GOOD


            // LDX
            // Estableciendo distintas direccciones de modod de acceso para el LDX
            case INS_LDX_IM: {
                Byte value = fetchByte(cycles, memory);
                X = value;
                cycles--;
                LDXSetStatusFlags();
            } break;

            // LDY
            case INS_LDY_IM: {
                Byte value = fetchByte(cycles, memory);
                Y = value;
                cycles--;
                LDXSetStatusFlags();
            } break;

            // STA
            // Esto es malo verificar pa operacion STA
            case INS_STA_ZP: {
                Byte zeroPageAddress = fetchByte(cycles, memory);
                Word address = zeroPageAddress; 
                writeByte(A, cycles, address, memory);
                // falta un ciclo de reloj

            } break;
            case INS_STX_ZP: {
                Byte zeroPageAddress = fetchByte(cycles, memory);
                Word address = zeroPageAddress;
                writeByte(X, cycles, address, memory);
                // falta un ciclo de reloj

            } break;

            // TODO: Comprobar si esta instruccion esta correcta
            case INS_STY_ZP: {
                Byte zeroPageAddress = fetchByte(cycles, memory);
                Word address = zeroPageAddress;
                writeByte(Y, cycles, address, memory);
                // falta un ciclo de reloj

            } break;

            // REGISTER TRANSFERS

            // No esta bien implementado los ciclos de reloj
            case INS_TAX: {
                X = A;
                cycles-=2;
                TAXSetStatusFlag();
            } break;
            case INS_TAY: {
                Y = A;
                cycles-=2;
                TAYSetStatusFlag();
            } break;
            case INS_TXA: {
                A = X;
                cycles-=2;
                TXASetStatusFlag();
            } break;
            case INS_TYA: {
                A = Y;
                cycles-=2;
                TXASetStatusFlag();
            } break;

            // STACK OPERATIONS
            case INS_TSX: {
                X = stackPointer;
                cycles-=2;
                TSXSetStatusFlag();
            } break;
            case INS_TXS: {
                stackPointer = X;
                cycles-=2;
            } break;

            case INS_PHA: {
                Byte value = A;
                cycles--;
                pushMemoryStack(cycles,value, memory);
                //PrintStatus();
                //memory.printMemory();                
            } break;

            // comprobar que se esten argegando los estados de procesor
            case INS_PHP: {
                // guardar el PS, o llamado Process State en la memoria
                Byte value = ps; 
                cycles--;
                pushMemoryStack(cycles, value, memory);
            } break;
            
            case INS_PLA: {
                A = readMemoryStack(cycles, memory);
                cycles--;
                SetZeroAndNegativeFlags(A);  
                // parece que falta un ciclo de reloj aqui
            } return; 
            case INS_PLP: {
                // ps = readMemoryStack(cycles, memory);
                // Actualizar los flags dado la informacion de la memoria
            } return;

            // LOGICAL

            case INS_AND_IM: {
                Byte value = fetchByte(cycles, memory);
                A &= value;
                cycles-=2; 
                SetZeroAndNegativeFlags(A);
            } break;
            case INS_EOR_IM: {
                Byte value = fetchByte(cycles, memory);
                // XOR
                A = A ^ value; 
                cycles-=2; 
                SetZeroAndNegativeFlags(A);
            } break;
            case INS_ORA_IM: {
                Byte value = fetchByte(cycles, memory);
                A |= value;
                cycles-=2; 
                SetZeroAndNegativeFlags(A);
            } break;
            case INS_BIT_ZP: {
                //Word address = fetchByte(cycles, memory);
                // TODO: VER COMO FUNCIONA BIEN ESTA INSTRUCCION
                Byte value = 0b11001010; // ver is este valor cambia la salida o solo valor de transporte e bit
                Word address = fetchByte(cycles, memory);
                Byte memory_value = readByte(cycles, address, memory);
                Byte result = value & memory_value;
                cycles--;
                // Esttablecemos las flags
                nf = (memory_value & 0x80) >> 7;
                bc = (memory_value & 0x40) >> 6;
            } break;

            // Arithmetic
            case INS_ADC: {    
                Byte value = fetchByte(cycles, memory);
                Word result = A + value + (cf ? 1 : 0);

                // Manejo de Excepciones aqui de INS ADC

                A = result;
                cf = result > 0xFF;
                cycles--;
            } break;
            case INS_SBC: {
                Byte value = fetchByte(cycles, memory);
                Word result = A - value - (cf ? 1 : 0); // no se si esta implementacion esta correcta
                cf = result > 0xFF;
                cycles--;

            } break;
            case INS_CMP: {
                // compare A with memory value                
                Byte value = fetchByte(cycles, memory);
                // Basado en las condiciones es podible establecer las flags
                Byte result = A - value; // El exito de esta funcion es que est este bien
                nf = (result & NegativeFlagBit) > 0;
                zf = A == value;
                cf = A >= value;
                cycles--;
            } break;
            case INS_CPX: {
                Byte value = fetchByte(cycles, memory);
                Byte result = X - value;
                nf = (result & NegativeFlagBit) > 0;
                zf = X == value;
                cf = X >= value;
                cycles--;
            } break;
            case INS_CPY: {
                Byte value = fetchByte(cycles, memory);
                Byte result = Y - value;
                nf = (result & NegativeFlagBit) > 0;
                zf = Y == value;
                cf = Y >= value;
                cycles--;
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
                cf = (A & NegativeFlagBit) > 0;
                Byte result = A << 1;
                A = result;
                zf = (A == 0);
                nf = (result == 0b10000000) > 0;
                cycles-=2;
            } break;
            case INS_ASL_ZP: {
                // parece que tengo que escribir en la memoria
                Byte zeroPageAddress = fetchByte(cycles, memory);
                Byte value = readByte(cycles, zeroPageAddress, memory);
                cf = (value & NegativeFlagBit) > 0;
                Byte result = value << 1;
                zf = (A == 0);
                nf = (result == 0b10000000) > 0;
                cycles-=2;
                // filtro un ciclo de reloj aqui ver de donde es
            } break;
            case INS_LSR: {
                cf = (A & ZeroBit) > 0;
                Byte result = A >> 1;
                A = result;
                zf = (result == 0);
                nf = (result == 0b10000000) > 0;
                cycles -= 2;
            } break;

            case INS_ROL: {

            } break;
            case INS_ROR: {

            } break;
            
            //Jumps & Calls

            
            case INS_RTS: {
                programCounter = memory[programCounter - 1];
                

            } break;
            case INS_JMP_IND: {

            } break;
            // No se is esta implementacion esta correcta
            case INS_JSR: {
                Word subAddress = fetchWord(cycles, memory); // pide una direccion
                
                // guardar la ultima posicion de memoria


                memory[stackPointer] = stackPointer - 1; // guardamos la direccion de memoria en la memoria especifica del stack pointer
                // porque cuando se aplica RTS para retornar tambien se va a utilizar un acceso de 16 bits

                
                // aumento el stack pointer 
                stackPointer++;
                cycles--;
                programCounter = subAddress;
                cycles--;
            } break;

            // Branches (Esto tiene que ver con el procesador de Sattus)
            case INS_BEQ: {

            } break;
            case INS_BNE: {

            } break;
            case INS_BCS: {

            } break;
            // No entiendo muy bien este codigo     
            case INS_BCC: {
                if (cf == 0) {
                    // aplicamos la instruccion
                    Byte offset = fetchByte(cycles, memory);
                    const Word pc_old = programCounter;
                    programCounter += offset;
                    cycles--;
                    // si hay una nueva pagina 
                    const bool pageChanged = (programCounter >> 8) != (pc_old >> 8);
                    if (pageChanged) {
                        cycles--;
                    }
                }
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

