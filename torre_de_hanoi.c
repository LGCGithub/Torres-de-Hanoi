#include <stdio.h>
#include <stdlib.h>

//Criando a pilha:
typedef struct stack {
	char name;
	int top;
	int size;
	int* arr;
} Stack;

//Funcoes para a pilha:
Stack* create_stack(char name, int size) { //Cria a pilha
    Stack* p = (Stack*)malloc(sizeof(Stack));
    p->name = name;
    p->top = 0;
    p->size = size;
    p->arr = (int*)malloc(size * sizeof(int));
    return p;
}

void push(Stack* p, int elem) { //Adiciona um elemento na pilha
    if (full_stack(p)) {
        exit(1);
    }
    p->arr[p->top] = elem;
    p->top++;
}

int pop(Stack* p) { //Retira um elemento da pilha
    if (empty_stack(p)) {
        exit(1);
    }
    p->top--;
    return p->arr[p->top];
}

int empty_stack(Stack* p) { //Retorna se a pilha esta vazia
    return (p->top == 0);
}

int full_stack(Stack* p) { //Retorna se a pilha esta cheia
    return (p->top == p->size);
}

void destroy_stack(Stack* p) { //Libera a pilha
    free(p->arr);
    free(p);
}


//Funcao recursiva para resolver a torre:
void solveTower(Stack* start, Stack* aux, Stack* end, int n) {
	if (n == 0) { return; }
	else {
		solveTower(start, end, aux, n - 1);
		movePiece(start, end);
		solveTower(aux, start, end, n - 1);
	}
}

//Funcao que remove o disco de um pino e passa para outro pino:
int movePiece(Stack* start, Stack* end) {
	int disc = pop(start);
	push(end, disc);

	printf("%c -> %c \n", start->name, end->name);
}

int main() {

	//Lendo o valor de n e garantindo que n sera positivo:
	int n = 0;
	do {
		printf("Digite um n positivo.\nn = ");
		scanf("%d", &n);
	} while (n <= 0);

	//Criando 3 pilhas:
	Stack* stackA = create_stack('A', n);
	Stack* stackB = create_stack('B', n);
	Stack* stackC = create_stack('C', n);

	//Enchendo a primeira torre:
	for (int i = n; i > 0; i--) push(stackA, i);

	//Resolvendo a torre:
	solveTower(stackA, stackB, stackC, n);

	//Liberando as pilhas:
	destroy_stack(stackA);
	destroy_stack(stackB);
	destroy_stack(stackC);

	return 0;
}