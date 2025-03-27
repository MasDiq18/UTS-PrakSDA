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

// Menginisialisasi stack
void init(Stack *s) { s->top = -1; }
// Mengecek apakah stack kosong
int isEmpty(Stack *s) { return s->top == -1; }
// Menambahkan elemen ke stack
void push(Stack *s, const char *str) {
    if (s->top < MAX - 1) {
        s->top++;
        strcpy(s->arr[s->top], str);
    }
}
// Menghapus elemen dari stack
char *pop(Stack *s) {
    if (!isEmpty(s)) return s->arr[s->top--];
    return NULL;
}
// Melihat elemen teratas stack
char *peek(Stack *s) {
    if (!isEmpty(s)) return s->arr[s->top];
    return NULL;
}

// Mengembalikan prioritas operator
int precedence(char ch) {
    switch (ch) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
    }
    return -1;
}

// Mengecek apakah karakter adalah operator
int isOperator(char ch) { return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'; }

// Membalik string untuk konversi infix ke prefix
void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Mengonversi infix ke postfix
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

// Mengonversi infix ke prefix
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

// Mengonversi postfix ke infix
void postfixToInfix(const char *postfix, char *infix) {
    Stack operands;
    init(&operands);
    int i = 0;
    char token, buffer[MAX];
    
    while ((token = postfix[i++]) != '\0') {
        if (isalnum(token)) {
            int j = 0;
            while (isalnum(token)) {
                buffer[j++] = token;
                token = postfix[i++];
            }
            buffer[j] = '\0'; i--;
            push(&operands, buffer);
        } else if (isOperator(token)) {
            char op2[MAX], op1[MAX], expr[MAX];
            strcpy(op2, pop(&operands));
            strcpy(op1, pop(&operands));
            sprintf(expr, "(%s %c %s)", op1, token, op2);
            push(&operands, expr);
        }
    }
    strcpy(infix, pop(&operands));
}

// Mengonversi prefix ke infix
void prefixToInfix(const char *prefix, char *infix) {
    Stack operands;
    init(&operands);
    int len = strlen(prefix);
    
    for (int i = len - 1; i >= 0; i--) {
        if (isalnum(prefix[i])) {
            char temp[2] = {prefix[i], '\0'};
            push(&operands, temp);
        } else if (isOperator(prefix[i])) {
            char op1[MAX], op2[MAX], expr[MAX];
            strcpy(op1, pop(&operands));
            strcpy(op2, pop(&operands));
            sprintf(expr, "(%s %c %s)", op1, prefix[i], op2);
            push(&operands, expr);
        }
    }
    strcpy(infix, pop(&operands));
}

// Mengonversi prefix ke postfix
void prefixToPostfix(const char *prefix, char *postfix) {
    char infix[MAX];
    prefixToInfix(prefix, infix);
    infixToPostfix(infix, postfix);
}

// Mengonversi postfix ke prefix
void postfixToPrefix(const char *postfix, char *prefix) {
    char infix[MAX];
    postfixToInfix(postfix, infix);
    infixToPrefix(infix, prefix);
}

int main() {
    char input[MAX], output[MAX] = "";
    int pilihan;

    do {
        printf("\nPilih Konversi:\n");
        printf("1. Infix ke Postfix\n");
        printf("2. Postfix ke Infix\n");
        printf("3. Infix ke Prefix\n");
        printf("4. Prefix ke Infix\n");
        printf("5. Prefix ke Postfix\n");
        printf("6. Postfix ke Prefix\n");
        printf("0. Keluar\n");
        printf("Masukkan pilihan (0-6): ");
        scanf("%d", &pilihan);
        getchar();

        if (pilihan == 0) {
            printf("Terima kasih! Program selesai.\n");
            break;
        }

        printf("Masukkan ekspresi: ");
        fgets(input, MAX, stdin);
        input[strcspn(input, "\n")] = 0;

        if (pilihan == 1) infixToPostfix(input, output);
        else if (pilihan == 2) postfixToInfix(input, output);
        else if (pilihan == 3) infixToPrefix(input, output);
        else if (pilihan == 4) prefixToInfix(input, output);
        else if (pilihan == 5) prefixToPostfix(input, output);
        else if (pilihan == 6) postfixToPrefix(input, output);
        else {
            printf("Pilihan tidak valid.\n");
            continue;
        }

        printf("Hasil: %s\n", output);
    } while (1);

    return 0;
}
