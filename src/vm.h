#ifndef VM_H
#define VM_H

#include <stdbool.h>
#include <stdlib.h>

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

    /**
     * The stack, storing an index to the next available index, and an array of values.
     */
    struct OperandStack {
        size_t top_index;
        int values[10];
    };


    void push(struct OperandStack *operand_instance, int value);

    int pop(struct OperandStack *operand_instance);

    int peek(struct OperandStack *operand_instance);

    const char* operation_code(enum Operations operation);

    bool is_valid_target(struct Instruction current_instruction, int program_size);

    int execute(struct OperandStack *operand_instance, struct Instruction *program, int program_size);

    #endif