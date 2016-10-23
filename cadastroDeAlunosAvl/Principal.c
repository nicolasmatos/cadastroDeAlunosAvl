#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreAvl.h"

/*
1.	Carregar os alunos para memória a partir da base de dados.
2.	Inserir um novo aluno na memória a partir de nome, email e telefone fornecidos. O valor da nova matrícula deve ser gerado automaticamente, sendo sempre a maior matrícula na base de dados mais 1.
3.	Listar os dados de todos os alunos por ordem de matrícula.
4.	Listar os dados de todos os alunos cujas matrículas estão contidas em um arquivo (ver anexos).
5.	Consultar dados do aluno a partir da matrícula fornecida.
6.	Alterar os dados de nome, email e telefone a partir da matrícula fornecida.
7.	Remover um aluno a partir da matrícula fornecida.
8.	Remover os dados de todos os alunos cujas matrículas estão contidas em um arquivo (ver anexos).
9.	Remover todos os alunos.
10.	Salvar os alunos na base de dados a partir da memória, refletindo qualquer inclusão, exclusão ou alteração feita através do programa.
*/

void carregaAlunos(Arvore * a, FILE * fp) {
	int i = 0;
	char c = fgetc(fp);

	while (c != EOF) {
		char matricula[50];
		char nome[50];
		char email[50];
		char telefone[50];
		int mat;

		while (c != ' ') {
			matricula[i] = c;
			i++;
			c = fgetc(fp);
		}
		matricula[i] = '\0';
		c = fgetc(fp);
		c = fgetc(fp);
		c = fgetc(fp);
		i = 0;

		while (c != '|') {
			nome[i] = c;
			i++;
			c = fgetc(fp);
		}
		nome[i - 1] = '\0';
		c = fgetc(fp);
		c = fgetc(fp);
		i = 0;

		while (c != ' ') {
			email[i] = c;
			i++;
			c = fgetc(fp);
		}
		email[i] = '\0';
		c = fgetc(fp);
		c = fgetc(fp);
		c = fgetc(fp);
		i = 0;

		while (c != '\n') {
			telefone[i] = c;
			i++;
			c = fgetc(fp);
		}
		telefone[i] = '\0';
		i = 0;

		mat = atoi(matricula);

		inserir(a, mat, nome, email, telefone);

		atualizar_fb(a);

		c = fgetc(fp);
	}
	fclose(fp);
}

void removerAlunos(Arvore * a, FILE * fp) {
	int i = 0;
	char c = fgetc(fp);

	while (c != EOF) {
		char matricula[50];
		int mat;

		while (c != '\n') {
			matricula[i] = c;
			i++;
			c = fgetc(fp);
		}
		matricula[i] = '\0';
		i = 0;
		mat = atoi(matricula);
		remover(a, mat);

		c = fgetc(fp);
	}
	fclose(fp);
}

void consultarAlunos(Arvore * a, FILE * fp) {
	int i = 0;
	char c = fgetc(fp);

	while (c != EOF) {
		char matricula[50];
		int mat;

		while (c != '\n') {
			matricula[i] = c;
			i++;
			c = fgetc(fp);
		}
		matricula[i] = '\0';
		i = 0;
		mat = atoi(matricula);
		consultar(a, mat);

		c = fgetc(fp);
	}
	fclose(fp);
}

void chamaArquivo(Arvore * a, char arquivo[]) {
	char caminho[100];
	strcpy(caminho, "Arquivos\\");
	strcat(caminho, arquivo);
	strcat(caminho, ".txt");

	FILE * fp;
	fp = fopen(caminho, "r");
	if (fp == NULL) {
		printf("\nErro na abertura do arquivo: %s\n", arquivo);
		printf("OBS: Verifique o nome do arquivo\n\n");
	}
	else {
		printf("Carregando alunos...\n\n");
		carregaAlunos(a, fp);
	}
}

void chamaArquivoR(Arvore * a, char arquivo[]) {
	char caminho[100];
	strcpy(caminho, "Arquivos\\");
	strcat(caminho, arquivo);
	strcat(caminho, ".txt");

	FILE * fp;
	fp = fopen(caminho, "r");
	if (fp == NULL) {
		printf("\nErro na abertura do arquivo: %s\n", arquivo);
		printf("OBS: Verifique o nome do arquivo\n\n");
	}
	printf("Removendo alunos...\n\n");
	removerAlunos(a, fp);
}

void chamaArquivoC(Arvore * a, char arquivo[]) {
	char caminho[100];
	strcpy(caminho, "Arquivos\\");
	strcat(caminho, arquivo);
	strcat(caminho, ".txt");

	FILE * fp;
	fp = fopen(caminho, "r");
	if (fp == NULL) {
		printf("\nErro na abertura do arquivo: %s\n", arquivo);
		printf("OBS: Verifique o nome do arquivo\n\n");
	}
	printf("Consultando alunos...\n\n");
	consultarAlunos(a, fp);
}

int main() {
	Arvore * a = criar();
	int opcao = 1;
	char arquivoCarregado[50];

	while (opcao != 11) {
		printf("================================Menu de opcoes================================\n");
		printf("1\. Carregar os alunos\n"
			"2\. Inserir um novo aluno\n"
			"3\. Listar os dados de todos os alunos por ordem de matricula\n"
			"4\. Listar os dados de todos os alunos de um arquivo\n"
			"5\. Consultar dados do aluno por matricula\n"
			"6\. Alterar os dados do aluno por matricula\n"
			"7\. Remover um aluno por matricula\n"
			"8\. Remover os dados de todos os alunos de um arquivo\n"
			"9\. Remover todos os alunos\n"
			"10\. Salvar os alunos \n"
			"11\. Sair do programa\n");
		printf("===============================================================================\n");
		printf("\nQual opcao do menu deseja executar?\n");
		scanf("%d", &opcao);
		if (opcao != 1 && opcao != 11) {
			if (esta_vazia(a)) {
				opcao = 3;
				while (opcao != 1 && opcao != 2) {
					system("cls");
					printf("Carregue o arquivo para a memoria ou insira um aluno.\n\n");
					printf("================================Menu de opcoes================================\n");
					printf("1\. Carregar os alunos\n"
						"2\. Inserir um novo aluno\n");
					printf("===============================================================================\n");
					printf("\nQual opcao do menu deseja executar?\n");
					scanf("%d", &opcao);
				}
			}
		}
		if (opcao == 1) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|     Carregar alunos    |\n"
				"|                        |\n"
				"--------------------------\n");
			fflush(stdin);
			printf("Nome do arquivo a ser carregado: ");
			scanf("%s", arquivoCarregado);
			fflush(stdin);

			chamaArquivo(a, arquivoCarregado);
			imprimirPre(a);
			checar_no_avl(a);
		}
		if (opcao == 2) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|     Inserir aluno      |\n"
				"|                        |\n"
				"--------------------------\n");
			int matricula;
			char nome[50];
			char email[50];
			char telefone[50];
			fflush(stdin);
			printf("\nNome: ");
			scanf("%s", nome);
			fflush(stdin);
			printf("\nEmail: ");
			scanf("%s", email);
			fflush(stdin);
			printf("\nTelefone: ");
			scanf("%s", telefone);
			fflush(stdin);

			matricula = buscar_maior(a);

			inserir(a, matricula + 1, nome, email, telefone);
			printf("\n");
			imprimirPre(a);
		}
		if (opcao == 3) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"| Listando por matricula |\n"
				"|                        |\n"
				"--------------------------\n");
			imprimirIn(a);
		}
		if (opcao == 4) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|  Listando de arquivo   |\n"
				"|                        |\n"
				"--------------------------\n");
			char arquivo[50];
			fflush(stdin);
			printf("Nome do arquivo a ser carregado: ");
			scanf("%s", arquivo);
			fflush(stdin);

			chamaArquivoC(a, arquivo);
		}
		if (opcao == 5) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"| Consulta por matricula |\n"
				"|                        |\n"
				"--------------------------\n");
			int matricula;
			printf("\nMatricula: ");
			scanf("%d", &matricula);
			int result = consultar(a, matricula);
			if (result == 0) printf("\nO aluno nao foi encontrado.\n");
		}
		if (opcao == 6) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|  Edicao por matricula  |\n"
				"|                        |\n"
				"--------------------------\n");
			int matricula;
			printf("\nMatricula: ");
			scanf("%d", &matricula);
			int result = editarAluno(a, matricula);
			if (result == 0) printf("\nO aluno nao foi encontrado.\n");
		}
		if (opcao == 7) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"| Remocao por matricula  |\n"
				"|                        |\n"
				"--------------------------\n");
			int matricula;
			printf("\nMatricula: ");
			scanf("%d", &matricula);
			int result = remover(a, matricula);
			if (result == 0) printf("\nO aluno nao foi encontrado.\n");
		}
		if (opcao == 8) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|  Remocao por arquivo   |\n"
				"|                        |\n"
				"--------------------------\n");
			char arquivo[50];
			fflush(stdin);
			printf("Nome do arquivo a ser carregado: ");
			scanf("%s", arquivo);
			fflush(stdin);

			chamaArquivoR(a, arquivo);
		}
		if (opcao == 9) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|    Removendo todos     |\n"
				"|                        |\n"
				"--------------------------\n");
			remover_todos(a);
		}
		if (opcao == 10) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|  Salvando interacoes   |\n"
				"|                        |\n"
				"--------------------------\n");
			char caminho[100];
			strcpy(caminho, "Arquivos\\");
			strcat(caminho, arquivoCarregado);
			strcat(caminho, ".txt");
			printf("%s\n", caminho);
			salvar_em_arquivo(a, caminho);
		}
		if (opcao == 11) {
			system("cls");
			printf("\n\n============================");
			printf("A operacao foi encerrada.");
			printf("===========================\n\n");
		}
		if (opcao < 1 || opcao > 11) {
			system("cls");
			printf("\n=============================");
			printf("Operacao invalida.");
			printf("================================\n");
		}
	}
	destruir(a);
	system("pause");
}