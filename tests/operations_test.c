#include "vm.h"

#include <stdio.h>
#include <stdlib.h>

    void push_pop_test(struct OperandStack *operands) {
        push(operands, 10);
        push(operands, 20);

        int second = pop(operands);
        int first = pop(operands);

        if (second == 20 && first == 10) {
            printf("push_pop_test passed; expected %d, %d, got %d, %d\n", second, first, second, first);
        }
        else {
            printf("push_pop_test failed; expected %d, %d, got %d, %d\n", second, first, second, first);
        }
    }

    void lt_isolation_test_false() {
            struct OperandStack operands = {0};
            struct Instruction program[] = {
                {PUSH, 5},
                {PUSH, 3},
                {LT, 0},
                {HALT, 0}
            };

            int program_size = sizeof(program) / sizeof(program[0]);

            execute(&operands, program, program_size);

            int result = peek(&operands);

            switch (result) {
                case 0:
                    printf("lt_isolation_test_false passed; expected %d, got %d\n", 0, result);
                    break;
                case 1:
                    printf("lt_isolation_test_false failed; expected %d, got %d\n", 0, result);
                    break;
            }
        }

    void lt_isolation_test_true() {
        struct OperandStack operands = {0};
        struct Instruction program[] = {
            {PUSH, 3},
            {PUSH, 5},
            {LT, 0},
            {HALT, 0}
        };

        int program_size = sizeof(program) / sizeof(program[0]);

        execute(&operands, program, program_size);

        switch (peek(&operands)) {
            case 0:
                printf("lt_isolation_test_true failed; expected %d, got %d\n", 1, peek(&operands));
                break;
            case 1:
                printf("lt_isolation_test_true passed; expected %d, got %d\n", 1, peek(&operands));
                break;
        }
    }

    void jmp_isolation_test_false() {
        
    }

    int main(void) {
        lt_isolation_test_false();
        lt_isolation_test_true();
    }

