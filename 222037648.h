// DEFINES
#define TAM_MAX 101
#define TAM_CPF 15
#define CADASTRAR_PESSOA 1
#define CONSULTAR_PESSOA 2
#define LISTAR_PESSOAS_CIDADE 3
#define GERAR_RELATORIO 4
#define EXCLUIR_PESSOA 5
#define SAIR 6
#define TAM_UF 4
#define TAM_MAX_CIDADE 200
#define QTD_PESSOAS 100

// DEFINIÇÃO DOS STRUCTS
typedef struct Pessoa{
    char cpf[TAM_CPF];
    char nome_completo[TAM_MAX];
    char sexo;
    int data_nasc, mes_nasc, ano_nasc;  
} USUARIO;

typedef struct Cidades{
    char uf[TAM_UF];
    char nome_cidade[TAM_MAX_CIDADE];
    char nome_com_acento[TAM_MAX_CIDADE];
    char nome_sem_acento[TAM_MAX_CIDADE];
    int cod_municipio;
} CIDADE;

// Função utilizada para limpar o buffer
void limpar_buffer(){
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Função utilizada para limpar o terminal
void limpar_tela(){
#if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

// Procedimento que irá imprimir o menu do SGBS
void impressao_menu(){
    printf("....... MENU DE OPCOES .......\n");
    printf("1) Cadastrar Pessoa\n");
    printf("2) Consultar Pessoa\n");
    printf("3) Listar pessoa por Cidade\n");
    printf("4) Gerar Relatorio\n");
    printf("5) Excluir Pessoa\n");
    printf("6) Encerrar Programa\n\n");
}