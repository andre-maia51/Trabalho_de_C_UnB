// Inclusão das bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "222037648.h"


// Protótipo das funções e procedimentos
void impressao_menu(); // Se encontra na biblioteca
void limpar_buffer(); // Se encontra na biblioteca
void limpar_tela(); // Se encontra na biblioteca

void cadastar_pessoa();
void consultar_pessoa();
void listar_pessoas_cidade();
void gerar_relatorio();
void excluir_pessoa();

int verificacao_cpf(char vetor_cpf[]);
int verificacao_data(int dia, int mes, int ano);
int verificacao_sexo(char sexo);
int achar_cpf(char cpf_pessoa[]);
int achar_cidade(char cidade_pessoa[], char uf_cidade[]);
int calcula_idade (int dia_nasc, int mes_nasc, int ano_nasc);


// Função main do código
int main() {
    // Declarações de variáveis
    int escolha_opcao;

    do {
        // Procedimento que limpará o terminal
        limpar_tela();

        // Impressão do menu e leitura da opção escolhida pelo usuário
        impressao_menu();
        printf("- Informe a opcao desejada: ");
        scanf("%d", &escolha_opcao);

        // Switch case que irá retornar a função escolhida pelo usuário
        switch (escolha_opcao) {
        case CADASTRAR_PESSOA:
            cadastar_pessoa();
            break;
        case CONSULTAR_PESSOA:
            consultar_pessoa();
            break;
        case LISTAR_PESSOAS_CIDADE:
            listar_pessoas_cidade();
            break;
        case GERAR_RELATORIO:
            gerar_relatorio();
            break;
        case EXCLUIR_PESSOA:
            excluir_pessoa();
            break;
        case SAIR:
            printf("Programa Finalizado!");
            break;
        default:
            printf("Valor Invalido!\n");
        }

        // Procedimento que irá limpar o buffer
        limpar_buffer();
        getchar();

    } while (escolha_opcao != SAIR);
}


// DEFINIÇÃO DAS FUNÇÕES E PROCEDIMENTOS

// Procedimento que realiza o cadastro do usuário
void cadastar_pessoa() {
    // Declaração de Variáveis
    FILE *arquivo;
    USUARIO p1;
    CIDADE c1;
    int verifica_pessoa;

    // Printf para ler o CPF do usuário
    printf("Informe o CPF da pessoa a ser cadastrada. O CPF deve seguir o formato '000.000.000-00': ");
    limpar_buffer();
    scanf("%[^\n]s", p1.cpf);

    // Condicional que verifica se o CPF é válido
    if (verificacao_cpf(p1.cpf) == 0) {
        printf("CPF Invalido!\n");
    } else {

        // Printf que le o nome do usuário
        printf("Informe o Nome Completo da pessoa a ser cadastrada: ");
        limpar_buffer();
        scanf("%[^\n]s", p1.nome_completo);

        // Condicional que verifica se o nome é válido
        if (strlen(p1.nome_completo) < 3) {
            printf("Nome Invalido!\n");
        }
        else {

            // Printf que le o sexo do usuário
            printf("Informe o sexo da pessoa a ser cadastrada (M para masculino ou F para feminino): ");
            limpar_buffer();
            scanf("%c", &p1.sexo);

            // Condicional se verifica se o sexo é válido
            if (verificacao_sexo(p1.sexo) == 0) {
                printf("Sexo Invalido!\n");
            }
            else {

                // Printf que le o dia, mes e ano de nascimento do usuário
                printf("Informe sua data de nascimento. A data deve seguir o formato 'XX/XX/XXXX': ");
                scanf("%d/%d/%d", &p1.data_nasc, &p1.mes_nasc, &p1.ano_nasc);

                // Condicional que verifica se o dia, mes e ano são válidos
                if (verificacao_data(p1.data_nasc, p1.mes_nasc, p1.ano_nasc) == 0) {
                    printf("Data, Mes ou Ano Invalido!\n");
                }
                else {
                    // Leitura da cidade do usuário
                    printf("Informe a Cidade da pessoa a ser cadastrada: ");
                    limpar_buffer();
                    scanf("%[^\n]s", c1.nome_cidade);

                    // Leitura da UF da cidade digitada pelo usuário
                    printf("Informe a UF da Cidade digitada: ");
                    limpar_buffer();
                    scanf("%[^\n]s", c1.uf);

                    if (achar_cidade(c1.nome_cidade, c1.uf) == 0) {
                        printf("Essa cidade nao consta no nosso banco de dados. Por favor tente novamente!");
                    } else {
                        // Condicional que cadastra o usuário no arquivo TXT corretamente caso o CPF dado seja diferente
                        if (achar_cpf(p1.cpf) == 1) {
                            arquivo = fopen("dados_usuarios.txt", "a");

                            if (arquivo != NULL) {
                                fprintf(arquivo, "%s\n", p1.cpf);
                                fprintf(arquivo, "%s\n", p1.nome_completo);
                                fprintf(arquivo, "%c\n", p1.sexo);
                                fprintf(arquivo, "%d\n", p1.data_nasc);
                                fprintf(arquivo, "%d\n", p1.mes_nasc);
                                fprintf(arquivo, "%d\n", p1.ano_nasc);
                                fprintf(arquivo, "%s\n", c1.nome_cidade);
                                fprintf(arquivo, "%s\n", c1.uf);

                                printf("Usuario cadastrado com sucesso!\n");

                                fclose(arquivo);
                            }
                        } else {
                            // Printf que informa ao usuário que não é possível cadastrar o usuário
                            printf("Nao e possivel cadastrar o usuario, pois esse CPF ja esta cadastrado!\n");
                        }
                    }
                }
            }
        }
    }
}


// Procedimento que serve para Consultar o usuário cadastrado
void consultar_pessoa() {
    // Declaração de Variáveis
    FILE *consulta_dados;
    USUARIO pessoa_consulta, leitura_pessoa;
    CIDADE cidade_pessoa_consulta;
    int valida_consulta = 0;

    // Leitura do CPF do usuario para consulta
    printf("Informe o CPF do usuario para a consulta. O CPF deve seguir o formato '000.000.000-00': ");
    limpar_buffer();
    scanf("%[^\n]", pessoa_consulta.cpf);

    // Comando que abre o arquivo
    consulta_dados = fopen("dados_usuarios.txt", "r");

    if (consulta_dados != NULL) {
        // Loop que irá ler os dados do arquivo
        while (!feof(consulta_dados)) {
            fscanf(consulta_dados, "%[^\n]\n", leitura_pessoa.cpf);
            fscanf(consulta_dados, "%[^\n]\n", leitura_pessoa.nome_completo);
            fscanf(consulta_dados, "%c\n", &leitura_pessoa.sexo);
            fscanf(consulta_dados, "%d\n", &leitura_pessoa.data_nasc);
            fscanf(consulta_dados, "%d\n", &leitura_pessoa.mes_nasc);
            fscanf(consulta_dados, "%d\n", &leitura_pessoa.ano_nasc);
            fscanf(consulta_dados, "%[^\n]\n", cidade_pessoa_consulta.nome_cidade);
            fscanf(consulta_dados, "%[^\n]\n", cidade_pessoa_consulta.uf);

            // Se o CPF dado for igual a algum registrado no arquivo o int irá receber 1
            if (strcmp(pessoa_consulta.cpf, leitura_pessoa.cpf) == 0) {
                valida_consulta = 1;
                break;
            } else {
                valida_consulta = 0;
            }
        }

        // Caso o int seja igual a 1, o programa imprime os dados do usuário. Caso contrário o CPF não foi cadastrado
        if (valida_consulta == 1) {
            printf("\n....... DADOS DO USUARIO .......\n\n");
            printf("CPF: %s\n", leitura_pessoa.cpf);
            printf("NOME COMPLETO: %s\n", leitura_pessoa.nome_completo);
            printf("SEXO: %c\n", leitura_pessoa.sexo);
            printf("DATA DE NASCIMENTO: %d/%d/%d\n", leitura_pessoa.data_nasc, leitura_pessoa.mes_nasc, leitura_pessoa.ano_nasc);
            printf("CIDADE E UF: %s - %s\n", cidade_pessoa_consulta.nome_cidade, cidade_pessoa_consulta.uf);
        } else {
            printf("Esse CPF nao esta cadastrado no nosso sistema!\n");
        }

        // Comando que fecha o arquivo
        fclose(consulta_dados);
    }
}


// Procedimento que lista alfabéticamente as pessoas que estão cadastradas na cidade informada pelo usuário
void listar_pessoas_cidade() {
    // Declaração de variáveis
    FILE *arq_usuarios;
    CIDADE cidade_informada, info_cidades;
    USUARIO info_usuario;
    char pessoas[QTD_PESSOAS][TAM_MAX], auxiliar[TAM_MAX];
    int cont = 0, i, j, x;

    // Comando para ler a cidade escolhida pelo usuário
    printf("Informe a cidade desejada: ");
    limpar_buffer();
    scanf("%[^\n]", cidade_informada.nome_cidade);

    // Comando para ler a UF da cidade escolhida pelo usuário
    printf("Infome a UF da cidade digitada: ");
    limpar_buffer();
    scanf("%[^\n]", cidade_informada.uf);

    // Condicional para validar se a cidade consta no arquivo de municipios ou não
    if(achar_cidade(cidade_informada.nome_cidade, cidade_informada.uf) == 0){
        printf("Essa cidade nao consta no nosso banco de dados!\n");
    } else {
        // Comando para abrir o arquivo com os dados dos usuários
        arq_usuarios = fopen("dados_usuarios.txt", "r");

        if(arq_usuarios != NULL) {
            // Repetição que irá percorrer o arquivo até o fim
            while(!feof(arq_usuarios)) {
                fscanf(arq_usuarios, "%[^\n]\n", info_usuario.cpf);
                fscanf(arq_usuarios, "%[^\n]\n", info_usuario.nome_completo);
                fscanf(arq_usuarios, "%c\n", &info_usuario.sexo);
                fscanf(arq_usuarios, "%d\n", &info_usuario.data_nasc);
                fscanf(arq_usuarios, "%d\n", &info_usuario.mes_nasc);
                fscanf(arq_usuarios, "%d\n", &info_usuario.ano_nasc);
                fscanf(arq_usuarios, "%[^\n]\n", info_cidades.nome_cidade);
                fscanf(arq_usuarios, "%[^\n]\n", info_cidades.uf);

                if((strcmp(cidade_informada.nome_cidade, info_cidades.nome_cidade) == 0) && (strcmp(cidade_informada.uf, info_cidades.uf) == 0)){
                    strcpy(pessoas[cont], info_usuario.nome_completo);
                    cont++;
                }
            }  

            for(i = 0; i <= cont; i++){
                for(j = i + 1; j <= cont; j++){
                    x = strcmp(pessoas[i], pessoas[j]);
                    if(x > 0){
                        strcpy(auxiliar, pessoas[i]);
                        strcpy(pessoas[i], pessoas[j]);
                        strcpy(pessoas[j], auxiliar);
                    }
                }
            }

            for(i = 0; i <= cont; i++){
                printf("%s\n", pessoas[i]);
            }

            fclose(arq_usuarios);
        }
    }
}


// Procedimento que irá gerar um relatorio baseado nos dados ja cadastrados
void gerar_relatorio() {
    // Declaração de variáveis
    FILE *arquivo_relatorio;
    USUARIO pessoa_relatorio;
    CIDADE municipio;
    int idade_usuario = 0;
    float total = 0, qtd15 = 0, qtd29 = 0, qtd49 = 0, qtd60 = 0, qtd_mais60 = 0;
    float percentual15, percentual29, percentual49, percentual60, percentual_mais60;
    float total_masculino = 0, total_feminino = 0;
    float percentual_masc, percentual_fem;

    // Comando para abrir o arquivo
    arquivo_relatorio = fopen("dados_usuarios.txt", "r");
    
    if(arquivo_relatorio != NULL){
        // Loop para ler o arquivo inteiro
        while (!feof(arquivo_relatorio)){
            fscanf(arquivo_relatorio, "%[^\n]\n", pessoa_relatorio.cpf);
            fscanf(arquivo_relatorio, "%[^\n]\n", pessoa_relatorio.nome_completo);
            fscanf(arquivo_relatorio, "%c\n", &pessoa_relatorio.sexo);
            fscanf(arquivo_relatorio, "%d\n", &pessoa_relatorio.data_nasc);
            fscanf(arquivo_relatorio, "%d\n", &pessoa_relatorio.mes_nasc);
            fscanf(arquivo_relatorio, "%d\n", &pessoa_relatorio.ano_nasc);
            fscanf(arquivo_relatorio, "%[^\n]\n", municipio.nome_cidade);
            fscanf(arquivo_relatorio, "%[^\n]\n", municipio.uf);

            // Calculo aproximado da idade da pessoa
            idade_usuario = calcula_idade(pessoa_relatorio.data_nasc, pessoa_relatorio.mes_nasc, pessoa_relatorio.ano_nasc);
            total++;

            // Verificação da idade dos usuários
            if(idade_usuario >= 0 && idade_usuario <= 15){
                qtd15++;
            } else if(idade_usuario > 15 && idade_usuario <= 30){
                qtd29++;
            } else if(idade_usuario > 29 && idade_usuario < 50){
                qtd49++;
            } else if (idade_usuario > 40 && idade_usuario <= 60){
                qtd60++;
            } else if (idade_usuario > 60){
                qtd_mais60++;
            }

            // Verificação do sexo dos usuários
            if(pessoa_relatorio.sexo == 'M' || pessoa_relatorio.sexo == 'm'){
                total_masculino++;
            } else if(pessoa_relatorio.sexo == 'F' || pessoa_relatorio.sexo == 'f'){
                total_feminino++;
            }

        }

        // Comando para fechar o arquivo
        fclose(arquivo_relatorio);

        // Calculo das porcentagens das idades
        percentual15 = (qtd15 / total) * 100;
        percentual29 = (qtd29 / total) * 100;
        percentual49 = (qtd49 / total) * 100;
        percentual60 = (qtd60 / total) * 100;
        percentual_mais60 = (qtd_mais60 / total) * 100;

        // Calculo da porcentagem dos sexos
        percentual_masc = (total_masculino / total) * 100;
        percentual_fem = (total_feminino / total) * 100;


        // Printf do relatório com as porcentagens de idade e de sexo
        printf("\n");
        printf("TOTAL DE PESSOAS BENEFICIADAS:\n");
        printf("0 A 15 ANOS: %.2f%%\n", percentual15);
        printf("16 A 29 ANOS: %.2f%%\n", percentual29);
        printf("30 A 49 ANOS: %.2f%%\n", percentual49);
        printf("50 A 60 ANOS: %.2f%%\n", percentual60);
        printf("ACIMA DE 60 ANOS: %.2f%%\n", percentual_mais60);
        printf("\n");
        printf("PERCENTUAL DE PESSOAS POR SEXO\n");
        printf("MASCULINO: %.2f%%\n", percentual_masc);
        printf("FEMININO: %.2f%%\n", percentual_fem);
    }
}


// Procedimento que realizará a exclusão dos dados do usuário
void excluir_pessoa(){
    // Declaração de variáveis
    USUARIO pessoa1, pessoa2;
    CIDADE city;
    FILE *novo_arq, *arq_original;
    int cont, verifica_cpf = 0;

    printf("Informe o CPF do usuario a ser excluido. O CPF deve seguir o formato '000.000.000-00': ");
    limpar_buffer();
    scanf("%[^\n]", pessoa1.cpf);

    arq_original = fopen("dados_usuarios.txt", "r");

    if(arq_original != NULL && novo_arq != NULL) {
        while(!feof(arq_original)){
            fscanf(arq_original, "%[^\n]\n", pessoa2.cpf);
            fscanf(arq_original, "%[^\n]\n", pessoa2.nome_completo);
            fscanf(arq_original, "%c\n", &pessoa2.sexo);
            fscanf(arq_original, "%d\n", &pessoa2.data_nasc);
            fscanf(arq_original, "%d\n", &pessoa2.mes_nasc);
            fscanf(arq_original, "%d\n", &pessoa2.ano_nasc);
            fscanf(arq_original, "%[^\n]\n", city.nome_cidade);
            fscanf(arq_original, "%[^\n]\n", city.uf);

            if(strcmp(pessoa1.cpf, pessoa2.cpf) == 0){
                printf("\n....... DADOS DO USUARIO .......\n\n");
                printf("CPF: %s\n", pessoa2.cpf);
                printf("NOME COMPLETO: %s\n", pessoa2.nome_completo);
                printf("SEXO: %c\n", pessoa2.sexo);
                printf("DATA DE NASCIMENTO: %d/%d/%d\n", pessoa2.data_nasc, pessoa2.mes_nasc, pessoa2.ano_nasc);
                printf("CIDADE E UF: %s - %s\n", city.nome_cidade, city.uf);
                printf("\nDESEJA EXCLUIR O USUARIO?\n");
                printf("1 - SIM\n");
                printf("2 - NAO\n");
                printf(">> ");
                scanf("%d", &cont);
                verifica_cpf = 0;
                break;
            }
            verifica_cpf++;
        }
        
        if(verifica_cpf == 0){

            if(cont == 1){
                novo_arq = fopen("temporario.txt", "a+");
                rewind(arq_original);

                while(!feof(arq_original)){

                    fscanf(arq_original, "%[^\n]\n", pessoa2.cpf);
                    fscanf(arq_original, "%[^\n]\n", pessoa2.nome_completo);
                    fscanf(arq_original, "%c\n", &pessoa2.sexo);
                    fscanf(arq_original, "%d\n", &pessoa2.data_nasc);
                    fscanf(arq_original, "%d\n", &pessoa2.mes_nasc);
                    fscanf(arq_original, "%d\n", &pessoa2.ano_nasc);
                    fscanf(arq_original, "%[^\n]\n", city.nome_cidade);
                    fscanf(arq_original, "%[^\n]\n", city.uf);

                    if(strcmp(pessoa1.cpf, pessoa2.cpf) != 0){
                        fprintf(novo_arq, "%s\n", pessoa2.cpf);
                        fprintf(novo_arq, "%s\n", pessoa2.nome_completo);
                        fprintf(novo_arq, "%c\n", pessoa2.sexo);
                        fprintf(novo_arq, "%d\n", pessoa2.data_nasc);
                        fprintf(novo_arq, "%d\n", pessoa2.mes_nasc);
                        fprintf(novo_arq, "%d\n", pessoa2.ano_nasc);
                        fprintf(novo_arq, "%s\n", city.nome_cidade);
                        fprintf(novo_arq, "%s\n", city.uf);
                    }
                }

                fclose(arq_original);
                fclose(novo_arq);

                remove("dados_usuarios.txt");
                rename("temporario.txt", "dados_usuarios.txt");

                printf("O usuario foi excluido com sucesso!\n");
                
            } else {
                printf("A exclusao do usuario foi cancelada!\n");
            }
            
        }
    }
    

}


// Função que irá validar o CPF informado
int verificacao_cpf(char vetor_cpf[]) {
    // Declaração de variáveis
    int cpf_num[TAM_CPF], n = 0, soma1, res1, soma2, res2;

    // Condicional que verifica se o CPF é válido
    if (strlen(vetor_cpf) != TAM_CPF - 1) {
        return 0;
    } else {
        if (vetor_cpf[0] >= '0' && vetor_cpf[0] <= '9' &&
            vetor_cpf[1] >= '0' && vetor_cpf[1] <= '9' &&
            vetor_cpf[2] >= '0' && vetor_cpf[2] <= '9' &&
            vetor_cpf[3] == '.' &&
            vetor_cpf[4] >= '0' && vetor_cpf[4] <= '9' &&
            vetor_cpf[5] >= '0' && vetor_cpf[5] <= '9' &&
            vetor_cpf[6] >= '0' && vetor_cpf[6] <= '9' &&
            vetor_cpf[7] == '.' &&
            vetor_cpf[8] >= '0' && vetor_cpf[8] <= '9' &&
            vetor_cpf[9] >= '0' && vetor_cpf[9] <= '9' &&
            vetor_cpf[10] >= '0' && vetor_cpf[10] <= '9' &&
            vetor_cpf[11] == '-' &&
            vetor_cpf[12] >= '0' && vetor_cpf[12] <= '9' &&
            vetor_cpf[13] >= '0' && vetor_cpf[13] <= '9')
        {

            // Converter CPF de string para numero inteiro
            for (int i = 0; i < 14; i++) {
                if (vetor_cpf[i] == '1') {
                    cpf_num[i] = 1;
                } else if (vetor_cpf[i] == '2') {
                    cpf_num[i] = 2;
                } else if (vetor_cpf[i] == '3') {
                    cpf_num[i] = 3;
                } else if (vetor_cpf[i] == '4') {
                    cpf_num[i] = 4;
                } else if (vetor_cpf[i] == '5') {
                    cpf_num[i] = 5;
                } else if (vetor_cpf[i] == '6') {
                    cpf_num[i] = 6;
                } else if (vetor_cpf[i] == '7') {
                    cpf_num[i] = 7;
                } else if (vetor_cpf[i] == '8') {
                    cpf_num[i] = 8;
                } else if (vetor_cpf[i] == '9') {
                    cpf_num[i] = 9;
                } else if (vetor_cpf[i] == '0') {
                    cpf_num[i] = 0;
                }
            }

            // Condicional que verifica se os numeros do CPF são repetidos
            if (cpf_num[0] == cpf_num[1] && cpf_num[1] == cpf_num[2]) {
                n == 1;
            } else {
                n == 0;
            }

            // Caso n seja igual a 0 ira para a condicional que fará o calculo de validação do CPF
            if (n == 0) {
                // Calculo que verifica o primeiro digito após o hífen
                soma1 = (cpf_num[0] * 10) + (cpf_num[1] * 9) + (cpf_num[2] * 8) + (cpf_num[4] * 7) + (cpf_num[5] * 6) + (cpf_num[6] * 5) +
                        (cpf_num[8] * 4) + (cpf_num[9] * 3) + (cpf_num[10] * 2);
                res1 = (soma1 * 10) % 11;

                if (res1 == 10) {
                    res1 = 0;
                }

                // Calculo que verifica o segundo digito após o hífen
                soma2 = (cpf_num[0] * 11) + (cpf_num[1] * 10) + (cpf_num[2] * 9) + (cpf_num[4] * 8) + (cpf_num[5] * 7) + (cpf_num[6] * 6) +
                        (cpf_num[8] * 5) + (cpf_num[9] * 4) + (cpf_num[10] * 3) + (cpf_num[12] * 2);
                res2 = (soma2 * 10) % 11;

                if (res2 == 10) {
                    res2 = 0;
                }

                // Se o res1 for igual ao primeiro digito e o res2 for igual ao segundo digito, o CPF é válido
                if (res1 == cpf_num[12] && res2 == cpf_num[13]) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
}


// Função que procura se o CPF dado já existe no arquivo com os dados de usuários
int achar_cpf(char cpf_pessoa[]) {
    // Declaração de variáveis
    FILE *dados;
    USUARIO p2;
    CIDADE c2;
    int verifica_cpf = 0;

    // Instrução para abrir o arquivo para leitura
    dados = fopen("dados_usuarios.txt", "r");

    if (dados != NULL) {
        // Repetição que irá ler os dados do arquivo e comparar com o que foi dado
        while (!feof(dados)) {

            fscanf(dados, "%[^\n]\n", p2.cpf);
            fscanf(dados, "%[^\n]\n", p2.nome_completo);
            fscanf(dados, "%c\n", &p2.sexo);
            fscanf(dados, "%d\n", &p2.data_nasc);
            fscanf(dados, "%d\n", &p2.mes_nasc);
            fscanf(dados, "%d\n", &p2.ano_nasc);
            fscanf(dados, "%[^\n]\n", c2.nome_cidade);
            fscanf(dados, "%[^\n]\n", c2.uf);

            if (strcmp(cpf_pessoa, p2.cpf) == 0) {
                verifica_cpf = 0;
                break;
            } else {
                verifica_cpf = 1;
            }
        }

        fclose(dados);
    }

    if (verifica_cpf == 0) {
        return 0;
    } else {
        return 1;
    }
}


// Função que verifica se a cidade existe ou não no banco de dados
int achar_cidade(char cidade_pessoa[], char uf_cidade[]) {
    // Declaração de variáveis
    FILE *lista_cidades;
    CIDADE cidade_cadastrada;
    int verifica_cidade = 0;
    char cabecalho[TAM_MAX];

    // Abrir o arquivo
    lista_cidades = fopen("municipios.csv", "r");

    if (lista_cidades != NULL) {
        fgets(cabecalho, TAM_MAX, lista_cidades);

        while (!feof(lista_cidades)) {
            // Leitura dos dados do arquivo
            fscanf(lista_cidades, "%d;%[^;];%[^;];%[^\n]", &cidade_cadastrada.cod_municipio, cidade_cadastrada.uf, cidade_cadastrada.nome_com_acento, cidade_cadastrada.nome_sem_acento);

            // Caso as strings sejam iguais a cidade é válida e consta no arquivo
            if ((strcmp(cidade_pessoa, cidade_cadastrada.nome_sem_acento) == 0) && (strcmp(uf_cidade, cidade_cadastrada.uf) == 0)) {
                verifica_cidade = 1;
                break;
            } else {
                verifica_cidade = 0;
            }
        }
        fclose(lista_cidades);

        if (verifica_cidade == 1) {
            return 1;
        } else {
            return 0;
        }
    }
}


// Função que verifica se a data informada pelo usuário é válida
int verificacao_data(int dia, int mes, int ano) {

    // Checagem do ano
    if (ano >= 1000 && ano <= 9999) {

        // Checagem do mes
        if (mes >= 1 && mes <= 12) {

            // Checagem do dia
            if ((dia >= 1 && dia <= 31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)) {
                return 1;
            } else if ((dia >= 1 && dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) {
                return 1;
            } else if ((dia >= 1 && dia <= 28) && (mes == 2)) {
                return 1;
            } else if (dia == 29 && mes == 2 && (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0))) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}


// Função que irá verificar se o sexo dado pelo usuário é válido
int verificacao_sexo(char sexo) {
    if (sexo == 'M' || sexo == 'm' || sexo == 'F' || sexo == 'f') {
        return 1;
    } else {
        return 0;
    }
}


// Função que realizará o calculo da idade do usuário de acordo com a data atual
int calcula_idade (int dia_nasc, int mes_nasc, int ano_nasc){
    struct tm *a;
    time_t local;
    int dia_atual = 0, mes_atual = 0, ano_atual = 0, idade;

    time(&local);
    a = localtime(&local);

    dia_atual = a->tm_mday;
    mes_atual = a->tm_mon + 1;
    ano_atual = a->tm_year + 1900;

    if (mes_nasc < mes_atual){
        idade = ano_atual - ano_nasc;
    } else if (mes_nasc > mes_atual){
        idade = (ano_atual - 1) - ano_nasc;
    } else if (mes_nasc == mes_atual){
        if (dia_nasc <= dia_atual) {
            idade = ano_atual - ano_nasc;
        } else if (dia_nasc > dia_atual){
            idade = (ano_atual - 1) - ano_nasc;
        } 
    }

    return idade;
}