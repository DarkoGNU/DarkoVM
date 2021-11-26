@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@{0} // not greater
D;JLE
@{1} // greater
0;JMP
({0}) // not greater
@SP
A=M-1
M=0
@{2} // end
0;JMP
({1}) // greater
@SP
A=M-1
M=-1
({2}) // end
