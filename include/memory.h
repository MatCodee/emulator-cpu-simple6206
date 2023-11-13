
#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <iomanip>
#include <vector>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;


class Memory {
    public:
        Memory() : Data(MAX_MEM,0) {}
        void Initialise();

        std::vector<Byte> getData();
        // Operaciones
        void PushMemory(const Byte &value,Byte &stackPointer);
        
        // Operadores
        Byte operator[](u32 address) const;
        Byte& operator[](u32 address);


        void printMemory() const;
    private:
        static constexpr u32 MAX_MEM = 1024 * 64; 
        std::vector<Byte> Data;
};

#endif // MEMORY_H