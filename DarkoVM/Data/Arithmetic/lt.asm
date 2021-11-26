@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@{0} // not smaller
D;JGE
@{1} // smaller
0;JMP
({0}) // not smaller
@SP
A=M-1
M=0
@{2} // end
0;JMP
({1}) // smaller
@SP
A=M-1
M=-1
({2}) // end
