    #include "vm.h"
    
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>

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
    
    /**
     * Basic helper function, verifies if the instruction's value is within a valid bound of the program's length.
     * 
     * @param current_instruction the instruction (operation, and value)
     * @param ` the length of the program
     */
    bool is_valid_target(struct Instruction current_instruction, int program_size) {
        bool result = current_instruction.value < program_size && current_instruction.value >= 0;

        if (!result) {
            fprintf(stderr, "%s target %d is out of range\n", operation_code(current_instruction.instruction), current_instruction.value);
        }

        return result;
    }

    int execute(struct OperandStack *operand_instance, struct Instruction *program, int program_size) {
        int current_index = 0;
        bool running = true;

        while (running) {
            if (current_index < 0 || current_index >= program_size) {
                fprintf(stderr, "Array index out of bounds\n");
                return 1;
            }

            struct Instruction current_instruction = program[current_index];
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
                    if (!is_valid_target(current_instruction, program_size)) { 
                        return 1; 
                    }

                    current_index = current_instruction.value;
                    break;
                }
                case JZ: {
                    int result = pop(operand_instance);

                    if (result == 0) {
                        if (!is_valid_target(current_instruction, program_size)) { 
                            return 1; 
                        }

                        current_index = current_instruction.value;
                    }

                    break; 
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