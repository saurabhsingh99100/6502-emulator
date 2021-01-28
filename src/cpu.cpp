#include <iostream>
#include "6502defs.hpp"

bool vb = true; //verbose

/**
 * Memory class, to emulate 64Kb memory
*/
class MEM
{
    // Mem
    Byte Data[MAX_MEM];

    public:
    
    /**
     * Resets all memory locations to 0
     */
    void reset()
    {
        for(int i = 0; i< MAX_MEM; i++)
            Data[i] = 0;
    }
    
    /**
     * Fetches a byte from memory
     * @param Address memory address
     * @returns Byte at address
     */
    inline Byte fetch(Word Address)
    {
        return Data[Address];
    }

    /**
     * Write a byte to memory
     * @param Address address
     * @param value value
     */
    inline void write(Word Address, Byte Value)
    {
        Data[Address] = Value;
    }
};

/**
 * CPU class impments the 6502 processor
 */
class CPU
{
    private:

    Word PC;    // Program counter
    Byte SP;    // Stack pointer
    MEM * mem;  // pointer to memory object

    // ========== Internal Registers ==========
    Byte A, X, Y;


    // ========== Status Flags ==========
    struct Flags
    {
        bool C, Z, I, D, B, V, N; 
    } flags;

    // ========== Flag Modifiers ==========
    /**
     * sets zero flag by checking the given value
     * @param value
     */
    inline void setZ(Byte value)
    {
        flags.Z = (value==0);
    }

    /**
     * sets negative flag by checking the given value
     * @param value
     */
    inline void setN(Byte value)
    {
        flags.N = (value & 0b10000000)>0;
    }



    // ========== Addressing Modes ==========
    
    /**
     * Load value using immidiate addressing mode
     * @returns Mem[PC];    side effect: (PC++)
     */
    Byte L_Imm_addr()
    {
        Byte data = mem->fetch(PC);
        PC++;
        return data;
    }

    /**
     * Load value using zero-page addressing mode
     * @returns MEM[MEM[PC]];   side effect: (PC++)
     */
    Byte L_ZP_addr()
    {
        Byte ZPaddr = mem->fetch(PC);
        PC++;
        return mem->fetch(ZPaddr);
    }
    
    /**
     * Load value using zero-page-X addressing mode
     * @returns MEM[MEM[PC]+X];   side effect: (PC++)
     */
    Byte L_ZPX_addr()
    {
        Byte ZPaddr = mem->fetch(PC);
        PC++;
        return mem->fetch(ZPaddr+X);
    }
    
    /**
     * Load value using zero-page-Y addressing mode
     * @returns MEM[MEM[PC]+Y];   side effect: (PC++)
     */
    Byte L_ZPY_addr()
    {
        Byte ZPaddr = mem->fetch(PC);
        PC++;
        return mem->fetch(ZPaddr+Y);
    }
    
    /**
     * Load value using absolute addressing mode
     * @returns MEM[{MEM[PC+1],MEM[PC]];   side effect: (PC+=2)
     */
    Byte L_Abs_addr()
    {
        Byte Laddr = mem->fetch(PC);
        PC++;
        Byte Uaddr = mem->fetch(PC);
        PC++;
        Word addr = ((Word)Uaddr)<<8 | (Word)Laddr;
        return mem->fetch(addr);    
    }

    /**
     * 
     */
    Byte L_Rel_addr()
    {
        SByte offset = mem->fetch(PC);
        PC++;
        return PC+offset;
    }



    public:
    
    /**
     * CPU constructor
     * @param m pointer to memory object
     */
    CPU( MEM * m)
    {
        mem = m;
    }


    /**
     * Runs the cpu for specified cycles
     * @param cycles cycles
     */
    void run(u32 cycles)
    {
        while(cycles > 0)
        {
            // Fetch Instr
            Byte Instr = mem->fetch(PC);

            if(vb)  std::cout<< std::hex<<PC<<": 0x"<<(int)Instr<<" ";

            // Increrement PC
            PC++;

            switch(Instr)
            {
                case Instr_LDA_IM:
                {
                    if(vb)  std::cout<<">> LDA_Imm"<<std::endl;
                    A = L_Imm_addr();
                    setZ(A); setN(A);
                } break;

                case Instr_LDA_ZP:
                {
                    if(vb)  std::cout<<">> LDA_ZP"<<std::endl;
                    A = L_ZP_addr();
                    setZ(A); setN(A);
                } break;

                case Instr_LDA_ZPX:
                {
                    if(vb)  std::cout<<">> LDA_ZPX"<<std::endl;
                    Byte ZPaddr = mem->fetch(PC);
                    PC++;
                    A = mem->fetch(ZPaddr+X);
                    setZ(A); setN(A);
                } break;

                case Instr_LDA_ABS:
                {
                    if(vb)  std::cout<<">> LDA_ZPY"<<std::endl;
                    Byte Laddr = mem->fetch(PC);
                    PC++;
                    Byte Uaddr = mem->fetch(PC);
                    PC++;
                    Word addr = ((Word)Uaddr)<<8 | (Word)Laddr;
                    A = mem->fetch(addr);
                    setZ(A); setN(A);
                } break;



                default: std::cout<<"Instr not defined"<<std::endl;
            }

            print_state();
            cycles--;
        }
    }
    
    /**
     * Prints current cpu state
     */
    void print_state()
    {
        std::cout<<"PC: 0x"<<std::hex<<(int)PC;
        std::cout<<"\t\tSP: 0x"<<std::hex<<(int)SP;
        std::cout<<"\t\tA: 0x"<<std::hex<<(int)A;
        std::cout<<"\t\tX: 0x"<<std::hex<<(int)X;
        std::cout<<"\t\tY: 0x"<<std::hex<<(int)Y;
        std::cout<<"\n-------------------------------------------------------------"<<std::endl;
    }

    /**
     * Resets the cpu
     */
    void reset()
    {
        PC = 0xFFFC;
        SP = 0x00;
        flags.D = 0;

        //  clear all flags
        flags.C = flags.Z = flags.I = flags.D = flags.B = flags.V = flags.N = 0;

        // clear all regs       
        A = X = Y = 0;

        // clear memory (Initialization)
        mem->reset();
    }   
};



int main()
{
    MEM memory;
    CPU cpu(&memory);
    cpu.reset();
    cpu.print_state();

    memory.write(0xFFFC,0xA9);
    memory.write(0xFFFD,0xAA);


    cpu.run(5);

    return 0;
}