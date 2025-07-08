
#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <iomanip>
#include <vector>

#include "types.h"

namespace Emulator6502 {

    class Memory {
        public:
            Memory() : Data(MAX_MEM,0) {};
            void Initialize_memory();

            const std::vector<Byte> &getData() const;
            
            void PushMemory(const Byte &value,Byte &stackPointer);
            Byte operator[](u32 address) const;
            Byte& operator[](u32 address);
            
            void printMemory() const;
        private:
            static constexpr u32 MAX_MEM = 1024 * 64; 
            std::vector<Byte> Data;
    };

}




#endif // MEMORY_H