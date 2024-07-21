#include <iostream>
#include <cstdlib> // For srand and rand
#include <ctime>   // For time used with srand

using namespace std;

// Node structure for the queue
struct No {
    int senha;
    No *prox;
};

// Queue structure
struct Fila {
    No *ini;
    No *fim;
};

// Function prototypes
Fila* init();
int isEmpty(Fila *f);
void enqueue(Fila *f, int senha);
int dequeue(Fila *f);
int count(Fila *f);
void printQueue(Fila *f);
void freeQueue(Fila *f);
int generateUniqueCode();

int main() {
    Fila *senhasGeradas = init();
    Fila *senhasAtendidas = init();

    int opcao;

    srand(time(0)); // Seed for random number generation

    do {
        cout << "Selecione uma opcao:" << endl;
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Realizar atendimento" << endl;

        cin >> opcao;

        switch (opcao) {
            case 1:

                enqueue(senhasGeradas, generateUniqueCode());
                break;
            case 2:

                if (!isEmpty(senhasGeradas)) {
                    int senhaAtendida = dequeue(senhasGeradas);
                    enqueue(senhasAtendidas, senhaAtendida);
                    cout << "Atendendo senha: " << senhaAtendida << endl;
                } else {
                    cout << "Nenhuma senha aguardando atendimento." << endl;
                }
                break;
            default:
                cout << "Opcao invalida. Por favor, selecione novamente." << endl;
        }


        if (!isEmpty(senhasGeradas)) {
            printQueue(senhasGeradas);
        } else {
            cout << "Nenhuma senha aguardando atendimento." << endl;
        }

        cout << endl;

    } while (opcao != 0);


    cout << "Total de senhas atendidas: " << count(senhasAtendidas) << endl;


    freeQueue(senhasGeradas);
    freeQueue(senhasAtendidas);

    return 0;
}

Fila* init() {
    Fila *f = new Fila;
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

int isEmpty(Fila *f) {
    return (f->ini == NULL);
}

void enqueue(Fila *f, int senha) {
    No *no = new No;
    no->senha = senha;
    no->prox = NULL;
    if (isEmpty(f)) {
        f->ini = no;
    }
    else {
        f->fim->prox = no;
    }
    f->fim = no;
}

int dequeue(Fila *f) {
    int ret = -1;
    if (!isEmpty(f)) {
        No *no = f->ini;
        ret = no->senha;
        f->ini = no->prox;
        if (f->ini == NULL) {
            f->fim = NULL;
        }
        delete no;
    }
    return ret;
}

int count(Fila *f) {
    int qtde = 0;
    No *no = f->ini;
    while (no != NULL) {
        qtde++;
        no = no->prox;
    }
    return qtde;
}

void printQueue(Fila *f) {
    No *no = f->ini;
    cout << "-- Qtde de senhas aguardando atendimento: " << count(f) << endl;
    while (no != NULL) {
        cout << "Senha: " << no->senha << endl;
        no = no->prox;
    }
}

void freeQueue(Fila *f) {
    No *no = f->ini;
    while (no != NULL) {
        No *temp = no->prox;
        delete no;
        no = temp;
    }
    delete f;
}

int generateUniqueCode() {
    static int counter = 1;
    return counter++;
}