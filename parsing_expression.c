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

// Prioritas operator
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
    }
    return -1;
}

// Mengecek apakah karakter adalah operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Fungsi konversi dari Infix ke Postfix
void infixToPostfix(char *infix, char *postfix) {
    Stack operators;
    init(&operators);
    int i = 0, k = 0;
    char token, temp[MAX];
    while ((token = infix[i++]) != '\0') {
        if (isalnum(token)) {
            postfix[k++] = token; // Operand langsung dimasukkan ke hasil
        } else if (token == '(') {
            push(&operators, (char[]){token, '\0'});
        } else if (token == ')') {
            while (!isEmpty(&operators) && (peek(&operators))[0] != '(') {
                postfix[k++] = pop(&operators)[0];
            }
            pop(&operators);
        } else if (isOperator(token)) {
            while (!isEmpty(&operators) && precedence(peek(&operators)[0]) >= precedence(token)) {
                postfix[k++] = pop(&operators)[0];
            }
            push(&operators, (char[]){token, '\0'});
        }
    }
    while (!isEmpty(&operators)) {
        postfix[k++] = pop(&operators)[0];
    }
    postfix[k] = '\0';
}
