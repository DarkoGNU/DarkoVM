@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@{} // not equal
D;JNE
@{} // equal
0;JMP
({}) // not equal
@SP
A=M-1
M=0
@ {} // end
0;JMP
({}) // equal
@SP
A=M-1
M=-1
({}) // end
