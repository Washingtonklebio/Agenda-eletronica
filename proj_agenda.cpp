#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define C 256
#define L 50

void sobre(void);//sobre o programa agenda
char validaresp(void);// validação de resposta
void ler (char [][C], char [][C], char[][C], int*); //Realiza a leitura do arquivo
void escrever(char[][C], char [][C], char[][C], int*); //Realiza a escrita no aquivo
void adicionar(char[][C], char [][C], char[][C], int*); //Adiciona um novo dado a sua lista de contatos
void listar_contatos(char[][C], char [][C], char[][C], int*); //Mostrar todos contatos cadastrados
void excluirContato(char[][C], char [][C], char[][C], int*);//função para exclusão do contato
void ordenarContato(char[][C], char [][C], char[][C], int*);//função responsavel por ordenação dos contatos
void pesquisarContato(char[][C], char [][C], char[][C], int*);// função de pesquisa de contato
void menu(void);//Menu principal
// declaração de variáveis globais
char nomes[L][C];
char email[L][C];
char numero[L][C];
int i, quant = 0;
int qtd_adicionados = 0;
int opcao = 1;
// função principal
int main()
{


    setlocale(LC_ALL, "Portuguese");//habilita a acentuação para o português
    system("color A");//mudando a cor dos caracteres do console
    system("title   AGENDA ELETRÔNICA");//colocando o nome no titulo do console
    ler(nomes, email, numero, &qtd_adicionados); //Essa função sempre deverá ser após a declaração para carregar os dados
    //sempre irá carregar os dados do arquivo, se ja existir, para que possam ser alterados no decorrer do programa.
    //chamada da função principal
    menu();

    return 0;
}
//função responsável por chamar todas as funções contidas no código
void menu(void)
{
    char variavel_entrada;

    system("cls");

    printf("\n\n");
    printf("                                   .::AGENDA ELETRÔNICA::.  \n\n");
    printf("                        Veja todas as funcoes disponiveis no menu   \n");
    printf("                       use os números para selecionar a opção desejada.  \n");
    printf("\n\n");
    printf("\n                                    MENU PRINCIPAL:");
    printf("\n                     +----------------------------------------------+ ");
    printf("\n                     | (1) - Cadastrar contatos                     |");
    printf("\n                     | (2) - Listar todos os contatos               |");
    printf("\n                     | (3) - Excluir contato                        |");
    printf("\n                     | (4) - Listar contatos em ordem alfabética    |");
    printf("\n                     | (5) - Pesquisar contatos                     |");
    printf("\n                     | (6) - Sobre                                  |");
    printf("\n                     | (0) - Sair                                   |");
    printf("\n                     +----------------------------------------------+ ");


    printf("\n\n                    Selecione a opção desejada: ");

    scanf(" %c",&variavel_entrada);// recebendo a variável de controle da estrutura swicht

    switch (variavel_entrada)
    {
    case '0':

        system("cls");
        printf("Programa encerrado pressione uma tecla para sair.\n");
        exit(0);//saindo do sistema quando usuário digitar 0

    case '1':

        system("cls");// limpando o console
        //chamada da função adicionar
        adicionar(nomes, email, numero, &qtd_adicionados);
        menu();//chamada do menu novamente usando recursividade
        break;
    case '2':
        system("cls");// limpando o console
        listar_contatos(nomes, email, numero, &qtd_adicionados);
        system("pause");
        menu();
        break;

    case '3':
        system("cls");
        excluirContato(nomes, email, numero, &qtd_adicionados);
        menu();
        break;
    case '4':
        system("cls");
        ordenarContato(nomes, email, numero, &qtd_adicionados);
        menu();
        break;
    case '5':
        system("cls");
        pesquisarContato(nomes, email, numero, &qtd_adicionados);
        system("pause");
        menu();
        break;
    case '6':
        system("cls");
        sobre();
        system("pause");
        menu();
        break;
    default:
        system("cls");
        printf("Opção inválida!\n");
        system("cls");
        menu();
    }

}
//função responsavel por validadr resposta do usuario
char validaresp(void)
{
    char op = 's';

    printf(" \nDeseja inserir novos dados? [S ou N] ? " );
    scanf("%s",&op);
    printf("\n" );
    system("cls");
    return op;
}
//função responsavel por a leitura do arquivo dados.txt
void ler(char n[][C], char email[][C], char num[][C], int *qtd)
{

    FILE *arquivo; //declarando apontador do tipo FILE que irá apontar para o arquivo desejado(pode ser dado qualquer nome).
    int i;
    char aux[200];
    arquivo = fopen("dados.txt", "r");//Abre o aquivo no modo leitura

    if(arquivo == NULL)
    {
        arquivo = fopen("dados.txt", "w");//Se não existir o arquivo, a função criará.
        fclose(arquivo);
    }
    else
    {
        fscanf(arquivo, "Pessoas cadastradas: %d\n", qtd);//Varia dependendo do padrão que você deseja utilizar para armazenar
        for(i = 0; i < *qtd; i++)
        {
            fgets(aux, 100, arquivo); //função de leitura de string
            strtok(aux, "\n"); //função pra retirar o \n que pura linha da string lida
            strcpy(n[i], aux); //apenas copiando o aux pra posição do array de nomes.
            fflush(stdin);//limpando o buffer do teclado
            fgets(aux, 100, arquivo);
            strtok(aux, "\n");
            strcpy(email[i], aux);
            fflush(stdin);
            fgets(aux, 100, arquivo);
            strtok(aux, "\n");
            strcpy(num[i], aux);
            fflush(stdin);
        }
        fclose(arquivo);//fechando o arquivo de texto dados.txt
    }
    return ;
}
//função responsavel por a escrita no arquivo dados.txt
void escrever(char n[][C], char email[][C], char num[][C], int *qtd)
{

    FILE *arquivo;
    int i;

    arquivo = fopen("dados.txt", "w");

    if(arquivo == NULL) //Ele não conseguiu abrir o arquivo/criar. Deve estar em algum lugar que precisa de permissão de ADM por exemplo
    {
        printf("Erro. \n");
    }
    else
    {
        fprintf(arquivo, "Pessoas cadastradas: %d\n", *qtd); //Escrevendo a quantidade no arquivo, para que possa ser recuperado quando o programa for aberto novamente
        for(i = 0; i < *qtd; i++)
        {
            fputs( n[i], arquivo);
            fprintf(arquivo, "\n");
            fputs(email[i], arquivo);
            fprintf(arquivo, "\n");
            fputs(num[i], arquivo);
            fprintf(arquivo, "\n");

        }
        fclose(arquivo);
    }
    return ;
}
//função para adicionar contatos na agenda
void adicionar(char n[][C], char email [][C], char num[][C], int *qtd)
{
    char op = 's';
    while(op == 's' || op == 'S')
    {
        fflush(stdin);//limpando o buffer do teclado
        printf("Digite o nome:\n");
        gets(n[*qtd]);//recebendo o nome e armazenando na matriz na posição apontada por o ponteiro *qtd
        fflush(stdin);//limpando o buffer do teclado
        printf("Digite o email:\n");
        gets(email[*qtd]);
        fflush(stdin);//limpando o buffer do teclado
        printf("Digite o telefone:\n");
        gets(num[*qtd]);
        fflush(stdin);//limpando o buffer do teclado

        *qtd = *qtd + 1;//Adiciona um no contador de cadastros
        op = validaresp();//chamada do metodo adicionar o valor de retorno é armazenado na variavel op
        quant ++;
    }
    escrever(nomes, email, numero, &qtd_adicionados); //Escreve todas as atualizações que as variaveis sofreram, no arquivo txt localizado na pasta do codigo
}
//listando todos os contatos da agenda
void listar_contatos(char n[][C], char email[][C], char num[][C], int *qtd)
{
    int i;
    //printa tudo que tem salvo
    for( i = 0; i < *qtd; i++)
    {
        printf("\nNome: ");
        puts(n[i]);
        printf("\nE-mail: ");
        puts(email[i]);
        printf("\nFone: ");
        puts(num[i]);
    }

}
//função para exclusão de um ou mais contatos
void excluirContato(char n[][C], char email[][C], char num[][C], int *qtd)
{
    int i, k = 0, j;
    char op;
    char aux[C]; //nome a ser excluido
    printf("\nDigite o nome do contato que deseja excluir. ");
    fflush(stdin);
    gets(aux); // nome digitado pelo usuario
    fflush(stdin);

    for (i = 0; i < *qtd; i++)
    {

        if (strcmp(n[i], aux) == 0)
        {
            fflush(stdin);
            printf("\n                                     Nome encontrado!\n");
            printf("\nNome: ");
            puts(n[i]);
            printf("\nEmail: ");
            puts(email[i]);
            printf("\nFone: ");
            puts(num[i]);
            k++;
            printf("-----------------------------ATENÇÃO------------------------------\n");
            printf("\n      Deseja realmente excluir os dados? [S/N]\n");
            scanf("%s", &op);

            if(op == 's'||op == 'S')
            {
                int w;

                for(j = i; j < *qtd - 1; j++)
                {
                    strcpy(n[j], n[j + 1]);
                    strcpy(email[j], email[j + 1]);
                    strcpy(num[j], num[j + 1]);

                }

                *qtd = *qtd - 1;
                escrever(nomes, email, numero, &qtd_adicionados); //Escreve todas as atualizações que as variaveis sofreram, no arquivo txt localizado na pasta do codigo
                printf("NOME EXCLUIDO COM SUCESSO\n\n");
                system("pause");
                menu();
            }

        }

    }
    if(k == 0)
    {
        system("cls");
        printf("\n\n     **** O nome digitado não encontra-se na agenda. ****\n\n\n");
        system("pause");
        menu();
    }
}
//função para ordenação dos contatos salvos na agenda
void ordenarContato(char n[][C], char email[][C], char num[][C], int *qtd)
{
    char aux[256];

    int i, j;

    for ( i = 0; i < *qtd - 1; i++)
    {

        for(j = 0; j < *qtd - 1; j++)
        {
            if(strcmp(n[j], n[j + 1]) > 0)
            {

                strcpy(aux, n[j]);//copiando o conteúdo de n[i] p/ aux
                strcpy(n[j], n[j + 1]);//copiando o conteúdo de n[i+1] p/ n[i]
                strcpy(n[j + 1], aux);//copiando o conteúdo de aux p/ n[i+1]

                strcpy(aux, email[j]);
                strcpy(email[j], email[j + 1]);
                strcpy(email[j + 1], aux);

                strcpy(aux, num[j]);
                strcpy(num[j], num[j + 1]);
                strcpy(num[j + 1], aux);

            }

        }

    }

    printf("Lista ordenada com sucesso..");
    listar_contatos(nomes, email, numero, &qtd_adicionados);//chamada da função listar_contatos
    system("pause");
    escrever(nomes, email, numero, &qtd_adicionados); //Escreve todas as atualizações que as variaveis sofreram, no arquivo txt localizado na pasta do codigo
    menu();
}
//função responsavel por pesquisar contatos
void pesquisarContato(char n[][C], char email[][C], char num[][C], int *qtd)
{
    int op, i, k = 0, j;
    char aux[C];//vetor aux

    printf("\nDeseja pesquisar o contato por nome ou telefone? \nNome[1] | Telefone[2]\n");
    fflush(stdin);//limpando o buffer do teclado

    scanf("%d", &op);//recebendo a 1 p/ pesquisar por nome e 2 p/ pesquisar por fone


    if (op == 1)
    {
        system("cls");
        printf("\nDigite o nome do contato que deseja pesquisar.\n");
        fflush(stdin);
        gets(aux); // nome digitado pelo usuario
        fflush(stdin);
        for (i = 0; i < *qtd; i++)
        {
            if (strcmp(n[i], aux) == 0)
            {
                printf("\nNome:");
                puts(n[i]);
                printf("\nEmail:");
                puts(email[i]);
                printf("\nFone:");
                puts(num[i]);
                k++;

            }
        }


        if(k == 0)
        {
            printf("Nao foi encontrado nome pesquisado!\n");
        }



    }
    else
    {
        system("cls");
        printf("\nDigite o numero do contato que deseja pesquisar.\n ");
        fflush(stdin);
        gets(aux); // nome digitado pelo usuario
        fflush(stdin);
        k=0;
        for (i = 0; i < *qtd; i++)
        {
            if (strcmp(num[i], aux) == 0)
            {
                printf("\n Nome:");
                puts(n[i]);
                printf("\nEmail:");
                puts(email[i]);
                printf("\nFone:");
                puts(num[i]);
                k++;
            }
        }

        if(k == 0)
        {
            printf("Nao foi encontrado o contato pesquisado!\n");

        }

    }
}

//função sobre para mostar informações sobre o programa
void sobre()
{
    printf("Agenda Eletrônica para o armazenamento de contatos.\n\n\nRecursos de: \n\n");
    printf("pesquisar contato, adicionar contato,remover contato, listar todos os contatos,\ndeixar todos em ordem alfabéticas.\n\n\n");
    printf("Guia: [S/N] = SIM/NÂO\n\n\n*ATENÇÃO* Para evitar possíveis falhas de ordenação/pesquisa e/ou erros. Deve-se seguir um padrão.\n\n");
    printf("Ao digitar caracteres especiais e/ou letras maiusculas você pode está causando um erro de pesquisa e/ou \n\n");
    printf("ordenação, os motivos são os os valores da tabela ASCII. Ex1.: {a =/= A} Ex2.: { A > a} \n");
    printf("\n\n--Desenvolvido por Washington Klébio--\n\n");
}
