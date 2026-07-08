#include <stdio.h>
#include <stdlib.h>

enum Operations {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    PUSH
};

struct Instruction {
    enum Operations instruction;
    int value;
};

struct Instruction instructions[5] = {
    { PUSH, 10 },
    { PUSH, 5 },
    { DIVIDE, 0 },
    { PUSH, 3 },
    { ADD, 0 }
};

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
        case PUSH:
            return "PUSH";
        default:
            return "???";
    }
}

void test_operations() {
    size_t arr_length = sizeof(instructions) / sizeof(instructions[0]);
    
    for (size_t i = 0; i < arr_length; i++) {
        printf("%s: %d\n", instructions[i].instruction, instructions[i].value);
    }
}


int main(void) {
    test_operations();

    return 0;
}