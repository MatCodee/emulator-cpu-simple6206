
#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;


class Memory {
    public:
        Memory() : Data(MAX_MEM,0) {}
        void Initialise() {
            std::fill(Data.begin(),Data.end(),0);
        }
        std::vector<Byte> getData() { return Data; }
        Byte& operator[](u32 address) {
            return Data[address];
        }
    private:
        static constexpr u32 MAX_MEM = 1024 * 64; 
        std::vector<Byte> Data;
};

#endif // MEMORY_H