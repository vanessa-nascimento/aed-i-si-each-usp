#include "filapreferencial.h"

//Vanessa Alves do Nascimento
//ACH2023 - Estrutura de Dados I

PFILA criarFila(){
	PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
	res->inicio = NULL;
	res->fimPref = NULL;
	res->inicioNaoPref = NULL;
	res->fim = NULL;
	return res;
}

int tamanho(PFILA f){
	PONT atual = f->inicio;
	int tam = 0;
	while (atual) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->inicio;
	 while (atual) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i] - Inicio:", numElementos);
	PONT atual = f->inicio;
	while (atual){
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->prox;
	}
	printf("\n\n");
}

int consultarIdade(PFILA f, int id){
	PONT atual = f->inicio;
	 while (atual) {
		if (atual->id == id) return atual->idade;
		atual = atual->prox;
	}
	return -1;
}

void inserePreferencial(PFILA f, PONT newPerson) {
    if(f->inicio == f->inicioNaoPref)
        f->inicio = newPerson;
    if(f->fim == f->fimPref)
        f->fim = newPerson;
    if(f->fimPref) {
        newPerson->prox = f->fimPref->prox;
        f->fimPref->prox = newPerson;
    }
    f->fimPref = newPerson;
}

void insereNaoPreferencial(PFILA f, PONT newPerson){
    if(f->inicio == NULL)
        f->inicio = newPerson;
    if(f->inicioNaoPref == NULL)
        f->inicioNaoPref = newPerson;
    if(f->fim)
        f->fim->prox = newPerson;
    f->fim = newPerson;
}

bool inserirPessoaNaFila(PFILA f, int id, int idade){    
	if(id < 0 || idade < 0 || buscarID(f,id) != NULL) return false;

    PONT newPerson = (PONT)malloc(sizeof(ELEMENTO));
    newPerson->id = id;
    newPerson->idade = idade;
    newPerson->prox = NULL;

    if(idade >= IDADEPREFERENCIAL) inserePreferencial(f, newPerson);
    else insereNaoPreferencial(f, newPerson);

    if(f->fimPref)
        f->fimPref->prox = f->inicioNaoPref;

	return true;
}

bool atenderPrimeiraDaFila(PFILA f, int* id) {
    if (tamanho(f) == 0) return false;
    *id = f->inicio->id;
    PONT apagar = f->inicio;
    f->inicio = f->inicio->prox;
    free(apagar);

    if (f->inicio == NULL) {
        f->fimPref = NULL;
        f->inicioNaoPref = NULL;
        f->fim = NULL;
    }

    return true;
}

PONT buscarIDAnterior(PFILA f, int id) {
    PONT atual = f->inicio;
    if(atual)
         while (atual->prox) {
            if (atual->prox->id == id) return atual;
            atual = atual->prox;
        }
    return NULL;
}

bool desistirDaFila(PFILA f, int id) {
    PONT anterior = buscarIDAnterior(f, id);
    PONT apagar = NULL;
    if(anterior == NULL) {
        if(buscarID(f, id)) {
            int temp = id;
            atenderPrimeiraDaFila(f, &temp);
        }
        else
            return false;
    }
    else {
        apagar = anterior->prox;
        anterior->prox = apagar->prox;
    }
    free(apagar);

    return true;
}