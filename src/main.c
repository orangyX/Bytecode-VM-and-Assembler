#include "vm.h"

#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    struct OperandStack operands = {0};
    struct Instruction program[] = {
        {PUSH, 1},
        {PUSH, 2},
        {LT, 0},
        {PRINT, 0},
        {HALT}
    };
    int program_size = sizeof(program) / sizeof(program[0]);

    int status_code = execute(&operands, program, program_size);

    return status_code;
}