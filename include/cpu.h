#ifndef CPU_H
#define CPU_H
#include "memory.h"
#include "types.h"


namespace Emulator6502 {
    class StatusFlag {
        public:
            Byte cf : 1;
            Byte zf : 1;
            Byte id : 1;
            Byte dm : 1;
            Byte bc : 1;
            Byte of : 1;
            Byte nf : 1;
            Byte Unused : 1;
    };

    class CPU {
        public:
            void reset(Memory &memory);
            void execute(u32 cycles,Memory &memory);

            Byte fetchInstruction(Memory& memory);
            Byte fetchByte(u32 &cycles, Memory &memory);
            Word fetchWord(u32 &cycles, Memory &memory);

            Byte readByte(u32 &cycles,const Byte &address,const Memory &memory);
            void writeByte(const Byte &value,u32 &cycles, const Byte &address, Memory &memory);
            
            void writeByteMemory(u32 &cycles, const Byte &address,const Byte &value, Memory &memory);
            void pushMemoryStack(u32& cycles, const Byte& value, Memory& memory);
            Word readMemoryStack(u32& cycles, Memory& memory);
        
            void loadValue(u32& cycles, Byte& addrStart, const Byte& addrEnd);

            void writeWord(Word value, u32& cycles, const u32 address, Memory& memory);

            // Flags
            void LDASetStatus(); // Establece los estados para un Instruccion LDA
            void LDXSetStatusFlags();
            void TSXSetStatusFlag();
            void TAXSetStatusFlag();
            void TAYSetStatusFlag();
            void TXASetStatusFlag();
            void SetZeroAndNegativeFlags(Byte &reg);


            void PrintStatus() const;
        private:
            bool act;
            Word programCounter; // almacena la sigueinte direccion
            Byte stackPointer;
            Byte A,X,Y; // Acumlador puede almacenar operacioes a excepcione de incrementos o decrementos

            bool carryFlag = false;
            
            union {
                Byte ps;
                StatusFlag flag;
            };

            // Status flags 
            Byte cf : 1;
            Byte zf : 1;
            Byte id : 1;
            Byte dm : 1;
            Byte bc : 1;
            Byte of : 1;
            Byte nf : 1;
    };
    

}


#endif // CPU_