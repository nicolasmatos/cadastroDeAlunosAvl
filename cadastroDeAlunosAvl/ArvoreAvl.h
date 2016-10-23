typedef struct arvore Arvore;
typedef struct no No;
typedef struct aluno Aluno;

Arvore * criar();
void destruir(Arvore * a);
void imprimirPre(Arvore * a);
void imprimirIn(Arvore * a);
void imprimirPos(Arvore * a);

void inserir(Arvore * a, int matricula, char nome[], char email[], char telefone[]);
Aluno * buscar(Arvore * a, int v);
int buscar_maior(Arvore * a);
int remover(Arvore * a, int v);

int consultar(Arvore * a, int matricula);
int editarAluno(Arvore * a, int matricula);
void remover_todos(Arvore * a);
void salvar_em_arquivo(Arvore * a, char arquivo[]);
int esta_vazia(Arvore * a);

void checar_no_avl(Arvore * a);
void atualizar_fb(Arvore * a);