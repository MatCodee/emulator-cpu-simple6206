#include <algorithm>
#include "memory.h"

using namespace Emulator6502;


// Inicializa toda la memoria en cero
void Memory::Initialize_memory() { 
    std::fill(Data.begin(), Data.end(),0);
}

const std::vector<Byte>& Memory::getData() const { return Data; }


// Esta operacion logica no debe estar en la memoria ya que es una unidad de almacenameinto
void Memory::PushMemory(const Byte &value, Byte &StackPointer) {
    if (Data.size() < MAX_MEM) {
        Data[StackPointer] = value;        
    } else {
        std::cerr << "Memory Error" << std::endl;
    }
}

// Este codigo es el mismo verificar su funcionamiento

/* Lee un byte */
Byte Memory::operator[](u32 address) const {
    return Data[address];
}
/* Esribe un 1 byte */
Byte& Memory::operator[](u32 address) {
    return Data[address];
}


void Memory::printMemory() const {
    std::cout << "Memory Dump:" << std::endl;
    for (u32 i = 0; i < MAX_MEM; ++i) {
        if (i % 16 == 0 && i != 0) {
            std::cout << std::endl;
        }
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(Data[i]) << " ";
    }
    std::cout << std::dec << std::endl;
}
