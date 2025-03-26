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

// Push ke stack
void push(Stack *s, char *str) {
    if (s->top < MAX - 1) {
        s->top++;
        strcpy(s->arr[s->top], str);
    }
}

// Pop dari stack
char *pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->arr[s->top--];
    }
    return NULL;
}

// Peek stack
char *peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->arr[s->top];
    }
    return NULL;
}
