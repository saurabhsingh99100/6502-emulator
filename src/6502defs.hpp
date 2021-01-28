/**
 * Definitions related to 6502 Assembly
 * @see http://www.obelisk.me.uk/6502/reference.html
 */


// Data Types
using Byte = unsigned char;
using SByte = signed char;
using Word = unsigned short;
using SWord = signed short;
using u32 = unsigned int;
const u32 MAX_MEM = 1024*64;

// Opcode definitions

// ADC - Add with Carry

// AND - Logical AND

// ASL - Arithmetic Shift Left

// BCC - Branch if Carry Clear

// BCS - Branch if Carry Set

// BEQ - Branch if Equal

// BIT - Bit Test

// BMI - Branch if Minus

// BNE - Branch if Not Equal

// BPL - Branch if Positive

// BRK - Force Interrupt

// BVC - Branch if Overflow Clear

// BVS - Branch if Overflow Set

// CLC - Clear Carry Flag

// CLD - Clear Decimal Mode

// CLI - Clear Interrupt Disable

// CLV - Clear Overflow Flag

// CMP - Compare

// CPX - Compare X Register

// CPY - Compare Y Register

// DEC - Decrement Memory

// DEX - Decrement X Register

// DEY - Decrement Y Register

// EOR - Exclusive OR

// INC - Increment Memory

// INX - Increment X Register

// INY - Increment Y Register

// JMP - Jump

// JSR - Jump to Subroutine

// LDA - Load Accumulator
const Byte Instr_LDA_IM = 0xA9;
const Byte Instr_LDA_ZP = 0xA5;
const Byte Instr_LDA_ZPX = 0xB5;
const Byte Instr_LDA_ABS = 0xAD;
const Byte Instr_LDA_ABSX = 0xBD;
const Byte Instr_LDA_ABSY = 0xB9;
const Byte Instr_LDA_INX = 0xA1;
const Byte Instr_LDA_INY = 0xB1;

// LDX - Load X Register

// LDY - Load Y Register

// LSR - Logical Shift Right

// NOP - No Operation

// ORA - Logical Inclusive OR

// PHA - Push Accumulator

// PHP - Push Processor Status

// PLA - Pull Accumulator

// PLP - Pull Processor Status

// ROL - Rotate Left

// ROR - Rotate Right

// RTI - Return from Interrupt

// RTS - Return from Subroutine

// SBC - Subtract with Carry

// SEC - Set Carry Flag

// SED - Set Decimal Flag

// SEI - Set Interrupt Disable

// STA - Store Accumulator

// STX - Store X Register

// STY - Store Y Register

// TAX - Transfer Accumulator to X

// TAY - Transfer Accumulator to Y

// TSX - Transfer Stack Pointer to X

// TXA - Transfer X to Accumulator

// TXS - Transfer X to Stack Pointer

// TYA - Transfer Y to Accumulator
