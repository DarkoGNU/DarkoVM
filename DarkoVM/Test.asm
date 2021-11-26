// push constant 10, line 0
@10 // arg2
D=A
@SP
AM=M+1
A=A-1
M=D
// pop local 0, line 1
@0 // arg2
D=A
@local
D=D+A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 21, line 2
@21 // arg2
D=A
@SP
AM=M+1
A=A-1
M=D
// push constant 22, line 3
@22 // arg2
D=A
@SP
AM=M+1
A=A-1
M=D
// pop argument 2, line 4
@2 // arg2
D=A
@arg
D=D+A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// pop argument 1, line 5
@1 // arg2
D=A
@arg
D=D+A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 36, line 6
@36 // arg2
D=A
@SP
AM=M+1
A=A-1
M=D
// pop this 6, line 7
@6 // arg2
D=A
@that
D=D+A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 42, line 8
@42 // arg2
D=A
@SP
AM=M+1
A=A-1
M=D
// push constant 45, line 9
@45 // arg2
D=A
@SP
AM=M+1
A=A-1
M=D
// pop that 5, line 10
@5 // arg2
D=A
@arg
D=D+A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// pop that 2, line 11
@2 // arg2
D=A
@arg
D=D+A
@SP
AM=M-1
D=D+M
A=D-M
M=D-A
// push constant 510, line 12
@510 // arg2
D=A
@SP
AM=M+1
A=A-1
M=D
// pop temp 6, line 13
// push local 0, line 14
@local
D=M
@0 // arg2
A=D+A
D=M
@SP
AM=M+1
A=A-1
M=D
// push that 5, line 15
@argument
D=M
@5 // arg2
A=D+A
D=M
@SP
AM=M+1
A=A-1
M=D
// add, line 16
@SP
AM=M-1
D=M
@SP
A=M-1
M=M+D
// push argument 1, line 17
@argument
D=M
@1 // arg2
A=D+A
D=M
@SP
AM=M+1
A=A-1
M=D
// sub, line 18
@SP
AM=M-1
D=M
@SP
A=M-1
M=M-D
// push this 6, line 19
@that
D=M
@6 // arg2
A=D+A
D=M
@SP
AM=M+1
A=A-1
M=D
// push this 6, line 20
@that
D=M
@6 // arg2
A=D+A
D=M
@SP
AM=M+1
A=A-1
M=D
// add, line 21
@SP
AM=M-1
D=M
@SP
A=M-1
M=M+D
// sub, line 22
@SP
AM=M-1
D=M
@SP
A=M-1
M=M-D
// push temp 6, line 23
// add, line 24
@SP
AM=M-1
D=M
@SP
A=M-1
M=M+D
