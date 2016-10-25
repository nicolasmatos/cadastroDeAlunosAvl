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
	long long int matricula;
	char nome[50];
	char email[50];
	char telefone[50];
};

struct no {
	int fb;
	No * pai;
	No * esq;
	No * dir;
	Aluno * aluno;
};

Arvore * criar() {
	Arvore * a = (Arvore *)malloc(sizeof(Arvore));
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
		printf("%s |", raiz->aluno->telefone);
		printf("%d \n\n", raiz->fb);
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
		printf("%s |", raiz->aluno->telefone);
		printf("%d \n\n", raiz->fb);
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

int atualizar_fb_rec(No * raiz) {
	if (raiz != NULL) {
		int ae = atualizar_fb_rec(raiz->esq);
		int ad = atualizar_fb_rec(raiz->dir);
		int fb = ad - ae;
		raiz->fb = fb;
		return ae > ad ? ae + 1 : ad + 1;
	}
	return -1;
}

void atualizar_fb(Arvore * a) {
	atualizar_fb_rec(a->raiz);
}

int atualizar_fb_no(No * raiz) {
	if (raiz != NULL) {
		if (raiz->dir == NULL && raiz->esq != NULL) {
			raiz->fb = raiz->esq - 1;
			atualizar_fb_no(raiz->esq);
			atualizar_fb_no(raiz->dir);
		}
		else if (raiz->esq == NULL && raiz->dir != NULL) {
			raiz->fb = raiz->dir + 1;
			atualizar_fb_no(raiz->esq);
			atualizar_fb_no(raiz->dir);
		}
		else if (raiz->esq != NULL && raiz->dir != NULL) {
			raiz->fb = raiz->dir->fb - raiz->esq->fb;
			atualizar_fb_no(raiz->esq);
			atualizar_fb_no(raiz->dir);
		}
	}
	
}

No * rotacionar_esq(No * raiz) {
	No * aux = raiz->dir;
	raiz->dir = aux->esq != NULL ? aux->esq : NULL;
	aux->esq = raiz;
	return aux;
}

No * rotacionar_dir(No * raiz) {
	No * aux = raiz->esq;
	raiz->esq = aux->dir != NULL ? aux->dir : NULL;
	aux->dir = raiz;
	return aux;
}

int inserir_rec(Arvore * a, No * * pRaiz, Aluno * aluno) {
	No* raiz = *pRaiz;
	if (raiz != NULL) {
		if (aluno->matricula < raiz->aluno->matricula) {
			int fb_c = inserir_rec(a, &raiz->esq, aluno);
			if (raiz->fb == -2) {
				if (fb_c == 1) {
					//rotacao dupla esquerda direita
					//rotacao esquerda
					raiz->esq = rotacionar_esq(raiz->esq);
				}
				//rotacao direita
				raiz = rotacionar_dir(raiz);
				*pRaiz = raiz;
			}
		}
		if (aluno->matricula > raiz->aluno->matricula) {
			int fb_c = inserir_rec(a, &raiz->dir, aluno);
			if (raiz->fb == 2) {
				if (fb_c == -1) {
					//rotacao dupla direita esquerda
					//rotacao direita
					raiz->dir = rotacionar_dir(raiz->dir);
				}
				//rotacao esquerda
				raiz = rotacionar_esq(raiz);
				*pRaiz = raiz;
			}
		}

		atualizar_fb(a);
		return raiz->fb;

	}
	else {
		raiz = (No *)malloc(sizeof(No));
		raiz->aluno = aluno;
		raiz->esq = NULL;
		raiz->dir = NULL;
		raiz->fb = 0;

		*pRaiz = raiz;

		return raiz->fb;
	}
}

void inserir(Arvore * a, int matricula, char nome[], char email[], char telefone[]) {
	Aluno * aluno = (Aluno *)malloc(sizeof(Aluno));
	aluno->matricula = matricula;
	strcpy(aluno->nome, nome);
	strcpy(aluno->email, email);
	strcpy(aluno->telefone, telefone);

	inserir_rec(a, &a->raiz, aluno);
}

void imprimirAluno(Aluno * a) {
	printf("%d | ", a->matricula);
	printf("%s | ", a->nome);
	printf("%s | ", a->email);
	printf("%s \n\n", a->telefone);
}

Aluno * buscar_rec(No * raiz, int matricula) {
	if (raiz != NULL) {
		if (matricula < raiz->aluno->matricula) return buscar_rec(raiz->esq, matricula);
		if (matricula > raiz->aluno->matricula) return buscar_rec(raiz->dir, matricula);
		return raiz->aluno;
	}
	return NULL;
}

int consultar(Arvore * a, int matricula) {
	Aluno * aluno = buscar_rec(a->raiz, matricula);
	if (aluno != NULL) {
		imprimirAluno(aluno);
		return 1;
	}
	return 0;
}

int editarAluno(Arvore * a, int matricula) {
	Aluno * aluno = buscar_rec(a->raiz, matricula);
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

int remover_maior_rec(No * * pRaiz) {
	No * raiz = *pRaiz;
	if (raiz->dir != NULL) {
		return remover_maior_rec(&raiz->dir);
	}
	*pRaiz = raiz->esq;
	int info = raiz->aluno->matricula;
	free(raiz->aluno);
	free(raiz);
	return info;
}

int remover_menor_rec(Arvore * a, No * * pRaiz, No * * pAnt, int c, No * * ref) {
	No * raiz = *pRaiz;
	No * ant = *pAnt;
	if (raiz->esq != NULL) {
		return c == 1 ? remover_menor_rec(a, &raiz->esq, &raiz, 2, pRaiz) : remover_menor_rec(a, &raiz->esq, &raiz, 0, NULL);
	}
	if (ant != NULL) {
		*pRaiz = raiz->dir;
		atualizar_fb(a);

		if (ant->fb == 2) {
			if (ant->dir->fb == -1) {
				//rotacao dupla direita esquerda
				//rotacao direita
				ant->dir = rotacionar_dir(ant->dir);
			}
			//rotacao esquerda
			ant = rotacionar_esq(ant);
			
			if (c == 2) {
				*ref = ant;
			}
			else {
				*pAnt = ant;
			}

			atualizar_fb(a);
		}
	}

	int info = raiz->aluno->matricula;
	free(raiz->aluno);
	free(raiz);
	return info;
}

int remover_rec(Arvore * a, No * * pRaiz, int matricula) {
	No * raiz = *pRaiz;
	if (raiz != NULL) {
		if (matricula < raiz->aluno->matricula) {
			int fb_c = remover_rec(a, &raiz->esq, matricula);
			if (raiz->fb == 2) {
				if (fb_c == -1) {
					//rotacao dupla esquerda direita
					//rotacao esquerda
					raiz->esq = rotacionar_dir(raiz->esq);
				}
				//rotacao direita
				raiz = rotacionar_esq(raiz);
				*pRaiz = raiz;
				atualizar_fb(a);
				return raiz->fb;
			}
		}
		else if (matricula > raiz->aluno->matricula) {
			int fb_c =	remover_rec(a, &raiz->dir, matricula);
			raiz->fb = raiz->fb - 1;
			if (raiz->fb == -2) {
				if (fb_c == 1) {
					//rotacao dupla direita esquerda
					//rotacao direita
					raiz->dir = rotacionar_esq(raiz->dir);
				}
				//rotacao esquerda
				raiz = rotacionar_dir(raiz);
				*pRaiz = raiz;
				atualizar_fb(a);
				return raiz->fb;
			}
		}
		else {
			//Folha
			if (raiz->esq == NULL && raiz->dir == NULL) {
				*pRaiz = NULL;
				free(raiz->aluno);
				free(raiz);
			}
			else {
				//Dois filhos
				if (raiz->esq != NULL && raiz->dir != NULL) {
					raiz->aluno->matricula = //remover_maior_rec(&raiz->esq);
						remover_menor_rec(a, &raiz->dir, &raiz->dir, 1, NULL);
				}
				else {//Um filho
					if (raiz->esq != NULL) {
						*pRaiz = raiz->esq;
					}
					else {
						*pRaiz = raiz->dir;
					}
					free(raiz->aluno);
					free(raiz);
				}
			}
			return raiz->fb != NULL ? raiz->fb : NULL;
		}
	}
}

int remover(Arvore * a, int matricula) {
	Aluno * aluno = buscar_rec(a->raiz, matricula);
	if (aluno != NULL) {
		remover_rec(a, &a->raiz, matricula);
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
		exit(1);
	}
	salva_aluno(a->raiz, fp);
	fclose(fp);
}

int esta_vazia(Arvore * a) {
	return a->raiz == NULL ? 1 : 0;
}

int checar_no_avl_rec(No * raiz) {
	if (raiz != NULL) {
		int ae = checar_no_avl_rec(raiz->esq);
		int ad = checar_no_avl_rec(raiz->dir);
		int fb = ad - ae;
		if ((fb < -1) || (fb > 1)) {
			printf("%d ", raiz->aluno->matricula);
		}
		return ae > ad ? ae + 1 : ad + 1;
	}
	return -1;
}

void checar_no_avl(Arvore * a) {
	checar_no_avl_rec(a->raiz);
}