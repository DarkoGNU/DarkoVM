@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@NOT{0} // not smaller
D;JGE
@{0} // smaller
0;JMP
(NOT{0}) // not smaller
@SP
A=M-1
M=0
@{0}END // end
0;JMP
({0}) // smaller
@SP
A=M-1
M=-1
({0}END) // end
