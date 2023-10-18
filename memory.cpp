#include "memory.h"

void Memory::Initialise() {
    std::fill(Data.begin(),Data.end(),0);
}

std::vector<Byte> Memory::getData() { return Data; }


// Implementacion de un elemento en la memoria
void Memory::PushMemory(const Byte &value) {

}

/* Lee un byte */
Byte operator[](u32 address) const {
    return Data[address];
}
/* Esribe un 1 byte */
Byte& operator[](u32 address) {
    return Data[address];
}