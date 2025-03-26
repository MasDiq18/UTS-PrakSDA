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

void init(Stack *s) { s->top = -1; }
int isEmpty(Stack *s) { return s->top == -1; }
void push(Stack *s, const char *str) {
    if (s->top < MAX - 1) {
        s->top++;
        strcpy(s->arr[s->top], str);
    }
}
char *pop(Stack *s) {
    if (!isEmpty(s)) return s->arr[s->top--];
    return NULL;
}
char *peek(Stack *s) {
    if (!isEmpty(s)) return s->arr[s->top];
    return NULL;
}

int precedence(char ch) {
    switch (ch) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
    }
    return -1;
}

int isOperator(char ch) { return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'; }

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void infixToPostfix(const char *infix, char *postfix) {
    Stack operators;
    init(&operators);
    int i = 0, k = 0;
    char token, buffer[MAX];

    while ((token = infix[i++]) != '\0') {
        if (isalnum(token)) {
            int j = 0;
            while (isalnum(token)) {
                buffer[j++] = token;
                token = infix[i++];
            }
            buffer[j] = '\0'; i--;
            sprintf(postfix + k, "%s ", buffer);
            k += strlen(buffer) + 1;
        } else if (token == '(') {
            push(&operators, "(");
        } else if (token == ')') {
            while (!isEmpty(&operators) && strcmp(peek(&operators), "(") != 0) {
                sprintf(postfix + k, "%s ", pop(&operators));
                k += 2;
            }
            pop(&operators);
        } else if (isOperator(token)) {
            while (!isEmpty(&operators) && precedence(peek(&operators)[0]) >= precedence(token)) {
                sprintf(postfix + k, "%s ", pop(&operators));
                k += 2;
            }
            char opStr[2] = {token, '\0'};
            push(&operators, opStr);
        }
    }
    while (!isEmpty(&operators)) {
        sprintf(postfix + k, "%s ", pop(&operators));
        k += 2;
    }
    postfix[k - 1] = '\0';
}

void infixToPrefix(const char *infix, char *prefix) {
    char reversed[MAX], postfix[MAX] = "";
    strcpy(reversed, infix);
    reverseString(reversed);
    
    for (int i = 0; i < strlen(reversed); i++) {
        if (reversed[i] == '(') reversed[i] = ')';
        else if (reversed[i] == ')') reversed[i] = '(';
    }
    infixToPostfix(reversed, postfix);
    reverseString(postfix);
    strcpy(prefix, postfix);
}

void postfixToInfix(const char *postfix, char *infix) {
    Stack operands;
    init(&operands);
    int i = 0;
    char token;
    char buffer[MAX];

    while ((token = postfix[i++]) != '\0') {
        if (isalnum(token)) {
            int j = 0;
            while (isalnum(token)) {
                buffer[j++] = token;
                token = postfix[i++];
            }
            buffer[j] = '\0';
            i--;
            push(&operands, buffer);
        } else if (isOperator(token)) {
            char op2[MAX], op1[MAX], expr[MAX];
            strcpy(op2, pop(&operands));
            strcpy(op1, pop(&operands));
            sprintf(expr, "(%s %c %s)", op1, token, op2);
            push(&operands, expr);
        }
    }

    if (!isEmpty(&operands)) {
        strcpy(infix, pop(&operands));
    }
}

int main() {
    char input[MAX], output[MAX] = "";
    int pilihan;

    printf("Pilih Konversi:\n");
    printf("1. Infix ke Postfix\n");
    printf("2. Postfix ke Infix\n");
    printf("3. Infix ke Prefix\n");
    printf("4. Prefix ke Infix\n");
    printf("Masukkan pilihan (1/2/3/4): ");
    scanf("%d", &pilihan);
    getchar();

    printf("Masukkan ekspresi: ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0;

    if (pilihan == 1) {
        infixToPostfix(input, output);
        printf("Ekspresi dalam Postfix: %s\n", output);
    } else if (pilihan == 2) {
        postfixToInfix(input, output);
        printf("Ekspresi dalam Infix: %s\n", output);
    } else if (pilihan == 3) {
        infixToPrefix(input, output);
        printf("Ekspresi dalam Prefix: %s\n", output);
    } else if (pilihan == 4) {
        printf("Fungsi Prefix ke Infix belum diimplementasikan.\n");
    } else {
        printf("Pilihan tidak valid.\n");
    }

    return 0;
}
