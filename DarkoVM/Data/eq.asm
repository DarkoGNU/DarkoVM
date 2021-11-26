@SP
AM=M-1
D=M
@SP
A=M-1
D=M-D
@{0} // not equal
D;JNE
@{1} // equal
0;JMP
({0}) // not equal
@SP
A=M-1
M=0
@{2} // end
0;JMP
({1}) // equal
@SP
A=M-1
M=-1
({2}) // end
