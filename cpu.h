#ifndef CPU_H
#define CPU_H
#include "memory.h"

using Byte = unsigned char;
using Word = unsigned short;

class CPU {
    public:
        void reset(Memory &memory);
        void execute(u32 cycles,Memory &memory);
        Byte fetchByte(u32 cycles,Memory &memory);
    private:
        bool act;
        Word programCounter;
        Byte stackPointer;
        Byte A,X,Y;
        // Status flags
        Byte cf : 1;
        Byte zf : 1;
        Byte id : 1;
        Byte dm : 1;
        Byte bc : 1;
        Byte of : 1;
        Byte nf : 1;
};
#endif // CPU_