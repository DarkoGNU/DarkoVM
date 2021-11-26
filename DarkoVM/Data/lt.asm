@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@{} // not smaller
D;JGE
@{} // smaller
0;JMP
({}) // not smaller
@SP
A=M-1
M=0
@{} // end
0;JMP
({}) // smaller
@SP
A=M-1
M=-1
({}) // end
