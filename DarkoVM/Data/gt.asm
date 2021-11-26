@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@{} // not greater
D;JLE
@{} // greater
0;JMP
({}) // not greater
@SP
A=M-1
M=0
@{} // end
0;JMP
({}) // greater
@SP
A=M-1
M=-1
({}) // end
