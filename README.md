# Simple Virtual Machine

This is an experimental pure C implementation of virtual machine with 64kb of memory.

## Architecture

<table>
	<tr> 
		<th colspan="16"> Encodings </th>
	</tr>
	<tr>
		<td> 15 </td>
		<td> 14 </td>
		<td> 13 </td>
		<td> 12 </td>
		<td> 11 </td>
		<td> 10 </td>
		<td> 9 </td>
		<td> 8 </td>
		<td> 7 </td>
		<td> 6 </td>
		<td> 5 </td>
		<td> 4 </td>
		<td> 3 </td>
		<td> 2 </td>
		<td> 1 </td>
		<td> 0 </td>
	</tr>
	<tr>
		<td colspan="4"> OP code </td>
		<td colspan="3"> Addr 1 </td>
		<td> mode </td>
		<td colspan="3"> Addr 2 </td>
		<td colspan="5"> </td>
	</tr>
	<tr>
		<td colspan="4"> OP code </td>
		<td colspan="3"> Addr 1 </td>
		<td> mode </td>
		<td colspan="8"> Immediate value </td>
	</tr>
</table>
<br>

Instruction | Description
-|-
ADD | Adds the destination operand (Addr 1) to the source operand and then stores the result in the destination operand. The source operand can be a register (Addr 2) or a immediate value. When an immediate value is used as an operand, the mod bit shall be set to 1.
SUB | Subtracts the source operand from the destination operand (Addr 1) and then stores the result in the destination operand. The source operand can be a register (Addr 2) or a immediate value. When an immediate value is used as an operand, the mod bit shall be set to 1.
MUL | Performs a multiplication of the destination operand (Addr 1) and the source operand and then stores the result in the destination operand. The source operand can be a register (Addr 2) or a immediate value. When an immediate value is used as an operand, the mod bit shall be set to 1.
DIV | Divides the value in the destination operand (Addr 1) by the source operand and then stores the result in the destination operand. The source operand can be a register (Addr 2) or a immediate value. When an immediate value is used as an operand, the mod bit shall be set to 1.
MOD | Divides the value in the destination operand (Addr 1) by the source operand and then stores the modulo in the destination operand. The source operand can be a register (Addr 2) or a immediate value. When an immediate value is used as an operand, the mod bit shall be set to 1.
AND | Performs a bitwise AND between the destination operand (Addr 1) and the source operand and then stores the result in the destination operand. The source operand can be a register (Addr 2) or a immediate value. When an immediate value is used as an operand, the mod bit shall be set to 1.
OR | Performs a bitwise OR between the destination operand (Addr 1) and the source operand and then stores the result in the destination operand. The source operand can be a register (Addr 2) or a immediate value. When an immediate value is used as an operand, the mod bit shall be set to 1.
CMP | Compares the first source operand (Addr 1) with the second source operand and sets the FLAGS register according to the results. The second source operand can be a register (Addr 2) or a immediate value. When an immediate value is used as an operand, the mod bit shall be set to 1.
NOT | If the mod bit set to 1, performs a bitwise NOT operation on the source operand (Addr 2) and stores the result in the destination operand (Addr 1). If the mod bit set to 0, sets the inverse boolean value in the destination operand (Addr 1).
LDR | Loads the first source operand (Addr 1) from the memory location specified by second source operand. The second source operand can be a register (Addr 2) or a value pointed by register PC. When a register is used as an operand, the mod bit shall be set to 1. 
STR | Stores the first source operand (Addr 1) in the memory location specified by second source operand. The second source operand can be a register (Addr 2) or a value pointed by register PC. When a register is used as an operand, the mod bit shall be set to 1. 
MOV | Copies the source operand to the destination operand (Addr 1). The source operand can be a register (Addr 2) or a value pointed by register PC. When a register is used as an operand, the mod bit shall be set to 1. 
PUSH | Stores the source operand (Addr 1) on the top of the stack and then decrements the stack pointer.
POP | Increments the stack pointer and then loads the value from the top of the stack to the destination operand (Addr 1)
JMP | If immediate value is equal to UINT8_MAX or FLAGS register, transfers program control to a different point in the memory. The destination operand specifies memory location being jumped to. The destination operand can be a register (Addr 1) or a value pointed by register PC. When a register is used as an operand, the mod bit shall be set to 1. 
TRAP | Execute trap routine.
<br>

 Register | Description
 -|-
AX | Accumulator register.
BX | Base register
CX | Counter register
DX | Data register
PC | Program counter register
SP | Stack pointer register
HP | Heap pointer register
FLAGS | Flag register
<br>

AX | Trap routine | BX | Description
 -|-|-|-
0 | EXIT | Error code | Halt the program and return the error code
1 | PRINT STR | String location | Output the null-terminated string  
2 | PRINT INT | Integer | Output the number
3 | PUTCHAR | Character | Output single character
4 | GET INT || Get int and store it in BX register, error code in AX

## License
This code is released under an MIT License. You are free to use, modify, distribute, or sell it under those terms.
