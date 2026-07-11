    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>

    // Compilation: gcc -Wall -Wextra stage_one.c -o stage_one.exe

    /**
     * The possible operations.
     */
    enum Operations {
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        LT,
        GT,
        PUSH,
        JMP,
        JZ,
        PRINT,
        HALT
    };

    /**
     * A payload, comprised of an operation (the instruction) and a value (optional).
     */
    struct Instruction {
        enum Operations instruction;
        int value;
    };

    // Hard-coded for now, test basic behaviour and ammend later
    struct Instruction instructions[] = {
        { PUSH, 10 },
        { PUSH, 5 },
        { DIVIDE, 0 },
        { PUSH, 3 },
        { ADD, 0 },
        { PRINT, 0 },
        { HALT, 0 }
    };

    /**
     * The stack, storing an index to the next available index, and an array of values.
     */
    struct OperandStack {
        size_t top_index;
        int values[10];
    };

    /**
     * Pushes a value to the operand stack.
     * 
     * @param operand_instance a pointer to the OperandStack
     * @param value to be pushed
     */
    void push(struct OperandStack *operand_instance, int value) {
        if (operand_instance->top_index >= sizeof(operand_instance->values) / sizeof(operand_instance->values[0])) {
            fprintf(stderr, "Cannot push to a stack at capacity\n");
            exit(1);
        }

        operand_instance->values[operand_instance->top_index] = value;
        operand_instance->top_index++;
    }

    /**
     * Removes the peek value from the stack.
     * 
     * @param operand_instance a pointer to the OperandStack
     * @return popped entry from the stack
     */
    int pop(struct OperandStack *operand_instance) {
        if (operand_instance->top_index == 0) {
            fprintf(stderr, "Cannot pop from an empty stack\n");
            exit(1);
        }

        int popped = operand_instance->values[operand_instance->top_index - 1];

        operand_instance->values[operand_instance->top_index - 1] = 0;
        operand_instance->top_index--;

        return popped;
    }

    /**
     * Returns the value on peek of the stack without mutating it.
     * 
     * @param operand_instance a pointer to the OperandStack
     * @return the peek value on the stack 
     */
    int peek(struct OperandStack *operand_instance) {
        if (operand_instance->top_index == 0) {
            fprintf(stderr, "Cannot invoke peek on an empty stack\n");
            exit(1);
        }

        return operand_instance->values[operand_instance->top_index - 1];
    }

    int execute(struct OperandStack *operand_instance, struct Instruction *instructions, int instructions_length) {
        int current_index = 0;
        bool running = true;

        while (running) {
            if (current_index < 0 || current_index >= instructions_length) {
                fprintf(stderr, "Array index out of bounds\n");
                return 1;
            }

            struct Instruction current_instruction = instructions[current_index];
            current_index++; // Immediately advance to point at the next instruction

            switch (current_instruction.instruction) {
                case ADD: {
                    int right = pop(operand_instance);
                    int left = pop(operand_instance);
                    push(operand_instance, left + right);
                    break;
                }
                case SUBTRACT: {
                    int right = pop(operand_instance);
                    int left = pop(operand_instance);
                    push(operand_instance, left - right);
                    break;
                }
                case MULTIPLY: {
                    int right = pop(operand_instance);
                    int left = pop(operand_instance);
                    push(operand_instance, left * right);
                    break;
                }
                case DIVIDE: {
                    if (peek(operand_instance) == 0) {
                        fprintf(stderr, "Division by zero\n");
                        return 1;
                    }

                    int right = pop(operand_instance);
                    int left = pop(operand_instance);

                    push(operand_instance, left / right);
                    break;
                }
                case LT: {
                    int right = pop(operand_instance);
                    int left = pop(operand_instance);
                    int result = left < right ? 1 : 0;

                    push(operand_instance, result);
                    break;
                }
                case GT: {
                    int right = pop(operand_instance);
                    int left = pop(operand_instance);
                    int result = left > right ? 1 : 0;

                    push(operand_instance, result);
                    break;
                }
                case PUSH: {
                    push(operand_instance, current_instruction.value);
                    break;
                }
                case JMP: {
                    if (current_instruction.value < 0 || current_instruction.value >= instructions_length) {
                        fprintf(stderr, "%s target %d is out of range\n", operation_code(current_instruction.instruction), current_instruction.value);
                        return 1;
                    }

                    current_index = current_instruction.value;
                    break;
                }
                case JZ: {

                }
                case PRINT: {
                    printf("%d\n", pop(operand_instance));
                    break;
                }
                case HALT: {
                    running = false;
                    break;
                }
                default: {
                    fprintf(stderr, "Unknown operation code");
                    return 1;
                }
            }
        }

        return 0;
    }

    /**
     * Yields the operation code specific to each operation.
     * 
     * @param operation the supplied operation
     * @return a string denoting the operation
     */
    const char* operation_code(enum Operations operation) {
        switch (operation) {
            case ADD:
                return "ADD";
            case SUBTRACT:
                return "SUBTRACT";
            case MULTIPLY:
                return "MULTIPLY";
            case DIVIDE:
                return "DIVIDE";
            case LT:
                return "LT";
            case GT:
                return "GT";
            case PUSH:
                return "PUSH";
            case JMP:
                return "JMP";
            case JZ:
                return "JZ";
            case PRINT:
                return "PRINT";
            case HALT:
                return "HALT";
            default:
                return "???";
        }
    }

    // void test_operations() {
    //     size_t arr_length = sizeof(instructions) / sizeof(instructions[0]);
        
    //     for (size_t i = 0; i < arr_length; i++) {
    //         printf("%s: %d\n", operation_code(instructions[i].instruction), instructions[i].value);
    //     }
    // }

    void test_push(struct OperandStack *operands) {
        push(operands, 10);
        push(operands, 20);
        push(operands, 30);

        printf("%d\n", pop(operands));
        printf("%d\n", pop(operands));
        printf("%d\n", pop(operands));
    }

    int main(void) {
        // test_operations();

        struct OperandStack operands = {0};

        int status_code = execute(&operands, instructions, sizeof(instructions) / sizeof(instructions[0]));

        return status_code;
    }