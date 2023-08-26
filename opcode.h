
using Byte = unsigned char;

// opcodes
static constexpr Byte INS_LDA_IM = 0xA9;
static constexpr Byte INS_LDX_IM = 0xA2;
static constexpr Byte INS_LDY_IM = 0xA0;
static constexpr Byte INS_STA_IM = 0x85; // Esta instruccion indica que guardamos el acumulador en la memoria