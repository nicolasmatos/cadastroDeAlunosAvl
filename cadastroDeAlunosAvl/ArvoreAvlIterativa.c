#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreAvl.h"

typedef struct no No;
typedef struct aluno Aluno;

struct arvore {
	No * raiz;
};

struct aluno {
	int matricula;
	char nome[50];
	char email[50];
	char telefone[50];
};

struct no {
	No * pai;
	No * esq;
	No * dir;
	Aluno * aluno;
};

Arvore * criar() {
	Arvore * a = (Arvore*) malloc(sizeof(Arvore));
	a->raiz = NULL;
	return a;
}

void destruir(Arvore * a) {
	free(a);
}

void pre_ordem(No * raiz) {
	if (raiz != NULL) {
		printf("%d | ", raiz->aluno->matricula);
		printf("%s | ", raiz->aluno->nome);
		printf("%s | ", raiz->aluno->email);
		printf("%s \n\n", raiz->aluno->telefone);
		pre_ordem(raiz->esq);
		pre_ordem(raiz->dir);
	}
}

void in_ordem(No * raiz) {
	if (raiz != NULL) {
		in_ordem(raiz->esq);
		printf("%d | ", raiz->aluno->matricula);
		printf("%s | ", raiz->aluno->nome);
		printf("%s | ", raiz->aluno->email);
		printf("%s \n\n", raiz->aluno->telefone);
		in_ordem(raiz->dir);
	}
}

void pos_ordem(No * raiz) {
	if (raiz != NULL) {
		pos_ordem(raiz->esq);
		pos_ordem(raiz->dir);
		printf("%d | ", raiz->aluno->matricula);
		printf("%s | ", raiz->aluno->nome);
		printf("%s | ", raiz->aluno->email);
		printf("%s \n\n", raiz->aluno->telefone);
	}
}

void imprimirPre(Arvore * a) {
	pre_ordem(a->raiz);
}

void imprimirIn(Arvore * a) {
	in_ordem(a->raiz);
}

void imprimirPos(Arvore * a) {
	pos_ordem(a->raiz);
}

int buscar_maior_rec(No * raiz) {
	if (raiz->dir != NULL) {
		return buscar_maior_rec(raiz->dir);
	}
	return raiz->aluno->matricula;
}

int buscar_maior(Arvore * a) {
	return a->raiz != NULL ? buscar_maior_rec(a->raiz) : 0;
}

void inserir(Arvore * a, int matricula, char nome[], char email[], char telefone[]) {
	Aluno * aluno = (Aluno *)malloc(sizeof(Aluno));
	aluno->matricula = matricula;
	strcpy(aluno->nome, nome);
	strcpy(aluno->email, email);
	strcpy(aluno->telefone, telefone);

	No *ant = NULL, *raiz = a->raiz;
	while (raiz != NULL && raiz->aluno->matricula != aluno->matricula) {
		ant = raiz;
		raiz = aluno->matricula < raiz->aluno->matricula ? raiz->esq : raiz->dir;
	}
	if (raiz == NULL) {
		raiz = (No *)malloc(sizeof(No));
		raiz->aluno = aluno;
		raiz->esq = NULL;
		raiz->dir = NULL;
		if (ant == NULL) {
			a->raiz = raiz;
		}
		else {
			if (aluno->matricula < ant->aluno->matricula) {
				ant->esq = raiz;
			}
			else {
				ant->dir = raiz;
			}
		}
	}
}

void imprimirAluno(Aluno * a) {
	printf("%d | ", a->matricula);
	printf("%s | ", a->nome);
	printf("%s | ", a->email);
	printf("%s \n\n", a->telefone);
}

Aluno * buscar(Arvore * a, int matricula) {
	No * raiz = a->raiz;
	while (raiz != NULL && raiz->aluno->matricula != matricula) {
		raiz = matricula < raiz->aluno->matricula ? raiz->esq : raiz->dir;
	}
	return raiz != NULL ? raiz->aluno : NULL;
}

int consultar(Arvore * a, int matricula) {
	Aluno * aluno = buscar(a, matricula);
	if (aluno != NULL) {
		imprimirAluno(aluno);
		return 1;
	}
	return 0;
}

int editarAluno(Arvore * a, int matricula) {
	Aluno * aluno = buscar(a, matricula);
	if (aluno != NULL) {
		int opcao = 1;
		while (opcao != 5) {
			printf("======================Menu de edicao======================\n");
			printf("1\. Alterar nome\n"
				"2\. Alterar email\n"
				"3\. Alterar telefone\n"
				"4\. Alterar tudo\n"
				"5\. Sair da edicao\n");
			printf("==========================================================\n");
			printf("\nQual opcao do menu deseja executar?\n");
			scanf("%d", &opcao);
			if (opcao == 1) {
				system("cls");
				printf("--------------------------\n"
					"|                        |\n"
					"|      Alterar nome      |\n"
					"|                        |\n"
					"--------------------------\n");
				fflush(stdin);
				printf("\nNome: ");
				scanf("%s", aluno->nome);
			}
			if (opcao == 2) {
				system("cls");
				printf("--------------------------\n"
					"|                        |\n"
					"|      Alterar email     |\n"
					"|                        |\n"
					"--------------------------\n");
				fflush(stdin);
				printf("\nEmail: ");
				scanf("%s", aluno->email);
			}
			if (opcao == 3) {
				system("cls");
				printf("--------------------------\n"
					"|                        |\n"
					"|    Alterar telefone    |\n"
					"|                        |\n"
					"--------------------------\n");
				fflush(stdin);
				printf("\nTelefone: ");
				scanf("%s", aluno->telefone);
			}
			if (opcao == 4) {
				system("cls");
				printf("--------------------------\n"
					"|                        |\n"
					"|      Alterar tudo      |\n"
					"|                        |\n"
					"--------------------------\n");
				fflush(stdin);
				printf("\nNome: ");
				scanf("%s", aluno->nome);
				fflush(stdin);
				printf("\nEmail: ");
				scanf("%s", aluno->email);
				fflush(stdin);
				printf("\nTelefone: ");
				scanf("%s", aluno->telefone);
				fflush(stdin);
			}
			if (opcao == 5) {
				system("cls");
				printf("\n\n============================");
				printf("A operacao de edicao encerrada.");
				printf("===========================\n\n");
			}
			if (opcao < 1 || opcao > 5) {
				system("cls");
				printf("\n=============================");
				printf("Operacao invalida.");
				printf("================================\n");
			}
		}
		return 1;
	}
	return 0;
}

int remover_maior(No * * pRaiz) {
	No * ant = NULL, *raiz = *pRaiz;
	while (raiz->dir != NULL) {
		ant = raiz;
		raiz = raiz->dir;
	}
	if (ant == NULL) {
		*pRaiz = raiz->esq;
	}
	else {
		ant->dir = raiz->esq;
	}
	int info = raiz->aluno->matricula;
	free(raiz);
	return info;
}

int remover_menor(No * * pRaiz) {
	No * ant = NULL, *raiz = *pRaiz;
	while (raiz->esq != NULL) {
		ant = raiz;
		raiz = raiz->esq;
	}
	if (ant == NULL) {
		*pRaiz = raiz->dir;
	}
	else {
		ant->esq = raiz->dir;
	}
	int info = raiz->aluno->matricula;
	free(raiz);
	return info;
}

void ajustar_anterior(Arvore * a, No * ant, int matricula, No * no) {
	if (ant == NULL) {
		a->raiz = no;
	}
	else {
		if (matricula < ant->aluno->matricula) {
			ant->esq = no;
		}
		else {
			ant->dir = no;
		}
	}
}

int remover(Arvore * a, int matricula) {
	Aluno * aluno = buscar(a, matricula);
	if (aluno != NULL) {
		No * ant = NULL, *raiz = a->raiz;
		while (raiz != NULL && raiz->aluno->matricula != matricula) {
			ant = raiz;
			raiz = matricula < raiz->aluno->matricula ? raiz->esq : raiz->dir;
		}
		if (raiz != NULL) {
			//Folha
			if (raiz->esq == NULL && raiz->dir == NULL) {
				ajustar_anterior(a, ant, matricula, NULL);
				free(raiz->aluno);
				free(raiz);
			}
			else {
				//Dois filhos
				if (raiz->esq != NULL && raiz->dir != NULL) {
					raiz->aluno->matricula = //remover_maior(&raiz->esq);
						remover_menor(&raiz->dir);
				}
				else {//Um filho
					if (raiz->esq != NULL) {
						ajustar_anterior(a, ant, matricula, raiz->esq);
					}
					else {
						ajustar_anterior(a, ant, matricula, raiz->dir);
					}
					free(raiz->aluno);
					free(raiz);
				}
			}
		}
		return 1;
	}
	return 0;
}

void remover_todos_rec(Arvore * a, No * raiz) {
	if (raiz != NULL) {
		remover_todos_rec(a, raiz->esq);
		remover_todos_rec(a, raiz->dir);
		remover(a, raiz->aluno->matricula);
	}
}

void remover_todos(Arvore * a) {
	remover_todos_rec(a, a->raiz);
}

void salva_aluno(No * raiz, FILE * fp) {
	if (raiz != NULL) {
		fprintf(fp, "%d | ", raiz->aluno->matricula);
		fprintf(fp, "%s | ", raiz->aluno->nome);
		fprintf(fp, "%s | ", raiz->aluno->email);
		fprintf(fp, "%s\n", raiz->aluno->telefone);
		salva_aluno(raiz->esq, fp);
		salva_aluno(raiz->dir, fp);
	}
}

void salvar_em_arquivo(Arvore * a, char arquivo[]) {
	FILE * fp;
	No * raiz = a->raiz;

	if ((fp = fopen(arquivo, "w")) == NULL) {
		printf("Erro, nao foi possivel abrir o arquivo\n");
	}
	salva_aluno(a->raiz, fp);
	fclose(fp);
}

int esta_vazia(Arvore * a) {
	return a->raiz == NULL ? 1 : 0;
}