//
// This file was generated by the Retargetable Decompiler
// Website: https://retdec.com
// Copyright (c) 2018 Retargetable Decompiler <info@retdec.com>
//

#include <stdint.h>
#include <stdio.h>
#include <string.h>

// ------------------- Function Prototypes --------------------

int32_t _bar(void);
int32_t _foo(char * str2);

// ------------------------ Functions -------------------------

// Address range: 0x401460 - 0x40149d
int32_t _foo(char * str2) {
    int32_t v1;
    printf("My stack looks like:\n%p\n%p\n%p\n%p\n%p\n% p\n\n", (char *)v1);
    int32_t str;
    strcpy((char *)&str, str2);
    puts((char *)&str);
    return printf("Now the stack looks like:\n%p\n%p\n%p\n%p\n%p\n%p\n\n", str2);
}

// Address range: 0x40149e - 0x4014b2
int32_t _bar(void) {
    // 0x40149e
    return puts("Augh! I've been hacked!");
}

// Address range: 0x4014b3 - 0x40153f
int main(int argc, char ** argv) {
    // 0x4014b3
    ___main();
    printf("Address of foo = %p\n", (int32_t *)_foo);
    printf("Address of bar = %p\n", (int32_t *)_bar);
    int32_t * str = (int32_t *)((int32_t)argv + 4); // 0x4014ef_0
    printf("strlen of input string is: %i\n", strlen((char *)*str));
    int32_t result;
    if (argc == 2) {
        // 0x401522
        _foo((char *)*str);
        result = 0;
        // branch -> 0x401537
    } else {
        // 0x40150f
        puts("Please supply a string as an argument!");
        result = -1;
        // branch -> 0x401537
    }
    // 0x401537
    return result;
}

// --------------- Statically Linked Functions ----------------

// void ___main(void);

// --------------- Dynamically Linked Functions ---------------

// int printf(const char * restrict format, ...);
// int puts(const char * s);
// char * strcpy(char * restrict dest, const char * restrict src);
// size_t strlen(const char * s);

// --------------------- Meta-Information ---------------------

// Detected compiler/packer: gcc (6.3.0)
// Detected language: C
// Detected functions: 3
// Decompiler release: v2.2.1 (2016-09-07)
// Decompilation date: 2018-05-29 19:38:29
