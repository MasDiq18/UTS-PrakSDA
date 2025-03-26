#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Struktur stack untuk operator atau operand
typedef struct {
    char arr[MAX][MAX];
    int top;
} Stack;

// Fungsi untuk menginisialisasi stack
void init(Stack *s) {
    s->top = -1;
}

// Mengecek apakah stack kosong
int isEmpty(Stack *s) {
    return s->top == -1;
}
