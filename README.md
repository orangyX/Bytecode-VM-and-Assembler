# Bytecode-VM-and-Assembler
## 1. Constituents of the program
* enum: comprised of the set of possible instructions
* struct: comprised of a single instruction, also carrying an (optional) number field
* array of structs: the core program, stores a collection of instructions
* program counter: tracks the index of the struct array
* operand stack: where each number lives whilst the program runs
