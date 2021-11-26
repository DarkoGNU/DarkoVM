load SimpleNot.asm,
output-file SimpleNot.out,
compare-to SimpleNot.cmp,
output-list RAM[0]%D2.6.2 RAM[256]%D2.6.2;

set RAM[0] 256,  // initializes the stack pointer 

repeat 30 {      // enough cycles to complete the execution
  ticktock;
}

output;          // the stack pointer and the stack base
