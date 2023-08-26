#ifndef CPU_H
#define CPU_H
#include "memory.h"

using Byte = unsigned char;
using Word = unsigned short;

class CPU {
    public:
        void reset(Memory &memory);
        void execute(u32 cycles,Memory &memory);

        Byte fetchByte(u32 &cycles, Memory &memory);
        Byte readByte(u32 &cycles, Byte address, Memory &memory);

        void LDASetStatus();
    private:
        bool act;
        Word programCounter; // almacena la sigueinte idreccion
        Byte stackPointer; 
        Byte A,X,Y; // Acumlador puede almacenar operacioes a excepcione de incrementos o decrementos
        
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