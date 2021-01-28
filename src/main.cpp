#include "cpu.cpp"

int main(int argc, char **argv)
{
    MEM memory;
    CPU cpu(&memory);
    cpu.reset();

    if(argc>1) 
        memory.fill(argv[1]);


    cpu.run(5);

    return 0;
}