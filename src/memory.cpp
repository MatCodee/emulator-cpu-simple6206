#include "memory.h"


void Memory::Initialise() {
    std::fill(Data.begin(),Data.end(),0);
}

std::vector<Byte> Memory::getData() { return Data; }


// Implementacion de un elemento en la memoria
void Memory::PushMemory(const Byte &value, Byte &StackPointer) {
    if (Data.size() < MAX_MEM) {
        Data[StackPointer] = value;        
    } else {
        std::cerr << "Memory Error" << std::endl;
    }
}

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
