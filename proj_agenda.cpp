#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define C 256
#define L 50

void sobre(void);//sobre o programa agenda
char validaresp(void);// valida��o de resposta
void ler (char [][C], char [][C], char[][C], int*); //Realiza a leitura do arquivo
void escrever(char[][C], char [][C], char[][C], int*); //Realiza a escrita no aquivo
void adicionar(char[][C], char [][C], char[][C], int*); //Adiciona um novo dado a sua lista de contatos
void listar_contatos(char[][C], char [][C], char[][C], int*); //Mostrar todos contatos cadastrados
void excluirContato(char[][C], char [][C], char[][C], int*);//fun��o para exclus�o do contato
void ordenarContato(char[][C], char [][C], char[][C], int*);//fun��o responsavel por ordena��o dos contatos
void pesquisarContato(char[][C], char [][C], char[][C], int*);// fun��o de pesquisa de contato
void menu(void);//Menu principal
// declara��o de vari�veis globais
char nomes[L][C];
char email[L][C];
char numero[L][C];
int i, quant = 0;
int qtd_adicionados = 0;
int opcao = 1;
// fun��o principal
int main()
{


    setlocale(LC_ALL, "Portuguese");//habilita a acentua��o para o portugu�s
    system("color A");//mudando a cor dos caracteres do console
    system("title   AGENDA ELETR�NICA");//colocando o nome no titulo do console
    ler(nomes, email, numero, &qtd_adicionados); //Essa fun��o sempre dever� ser ap�s a declara��o para carregar os dados
    //sempre ir� carregar os dados do arquivo, se ja existir, para que possam ser alterados no decorrer do programa.
    //chamada da fun��o principal
    menu();

    return 0;
}
//fun��o respons�vel por chamar todas as fun��es contidas no c�digo
void menu(void)
{
    char variavel_entrada;

    system("cls");

    printf("\n\n");
    printf("                                   .::AGENDA ELETR�NICA::.  \n\n");
    printf("                        Veja todas as funcoes disponiveis no menu   \n");
    printf("                       use os n�meros para selecionar a op��o desejada.  \n");
    printf("\n\n");
    printf("\n                                    MENU PRINCIPAL:");
    printf("\n                     +----------------------------------------------+ ");
    printf("\n                     | (1) - Cadastrar contatos                     |");
    printf("\n                     | (2) - Listar todos os contatos               |");
    printf("\n                     | (3) - Excluir contato                        |");
    printf("\n                     | (4) - Listar contatos em ordem alfab�tica    |");
    printf("\n                     | (5) - Pesquisar contatos                     |");
    printf("\n                     | (6) - Sobre                                  |");
    printf("\n                     | (0) - Sair                                   |");
    printf("\n                     +----------------------------------------------+ ");


    printf("\n\n                    Selecione a op��o desejada: ");

    scanf(" %c",&variavel_entrada);// recebendo a vari�vel de controle da estrutura swicht

    switch (variavel_entrada)
    {
    case '0':

        system("cls");
        printf("Programa encerrado pressione uma tecla para sair.\n");
        exit(0);//saindo do sistema quando usu�rio digitar 0

    case '1':

        system("cls");// limpando o console
        //chamada da fun��o adicionar
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
        printf("Op��o inv�lida!\n");
        system("cls");
        menu();
    }

}
//fun��o responsavel por validadr resposta do usuario
char validaresp(void)
{
    char op = 's';

    printf(" \nDeseja inserir novos dados? [S ou N] ? " );
    scanf("%s",&op);
    printf("\n" );
    system("cls");
    return op;
}
//fun��o responsavel por a leitura do arquivo dados.txt
void ler(char n[][C], char email[][C], char num[][C], int *qtd)
{

    FILE *arquivo; //declarando apontador do tipo FILE que ir� apontar para o arquivo desejado(pode ser dado qualquer nome).
    int i;
    char aux[200];
    arquivo = fopen("dados.txt", "r");//Abre o aquivo no modo leitura

    if(arquivo == NULL)
    {
        arquivo = fopen("dados.txt", "w");//Se n�o existir o arquivo, a fun��o criar�.
        fclose(arquivo);
    }
    else
    {
        fscanf(arquivo, "Pessoas cadastradas: %d\n", qtd);//Varia dependendo do padr�o que voc� deseja utilizar para armazenar
        for(i = 0; i < *qtd; i++)
        {
            fgets(aux, 100, arquivo); //fun��o de leitura de string
            strtok(aux, "\n"); //fun��o pra retirar o \n que pura linha da string lida
            strcpy(n[i], aux); //apenas copiando o aux pra posi��o do array de nomes.
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
//fun��o responsavel por a escrita no arquivo dados.txt
void escrever(char n[][C], char email[][C], char num[][C], int *qtd)
{

    FILE *arquivo;
    int i;

    arquivo = fopen("dados.txt", "w");

    if(arquivo == NULL) //Ele n�o conseguiu abrir o arquivo/criar. Deve estar em algum lugar que precisa de permiss�o de ADM por exemplo
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
//fun��o para adicionar contatos na agenda
void adicionar(char n[][C], char email [][C], char num[][C], int *qtd)
{
    char op = 's';
    while(op == 's' || op == 'S')
    {
        fflush(stdin);//limpando o buffer do teclado
        printf("Digite o nome:\n");
        gets(n[*qtd]);//recebendo o nome e armazenando na matriz na posi��o apontada por o ponteiro *qtd
        fflush(stdin);//limpando o buffer do teclado
        printf("Digite o email:\n");
        gets(email[*qtd]);
        fflush(stdin);//limpando o buffer do teclado
        printf("Digite o telefone:\n");
        gets(num[*qtd]);
        fflush(stdin);//limpando o buffer do teclado

        *qtd = *qtd + 1;//Adiciona um no contador de cadastros
        op = validaresp();//chamada do metodo adicionar o valor de retorno � armazenado na variavel op
        quant ++;
    }
    escrever(nomes, email, numero, &qtd_adicionados); //Escreve todas as atualiza��es que as variaveis sofreram, no arquivo txt localizado na pasta do codigo
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
//fun��o para exclus�o de um ou mais contatos
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
            printf("-----------------------------ATEN��O------------------------------\n");
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
                escrever(nomes, email, numero, &qtd_adicionados); //Escreve todas as atualiza��es que as variaveis sofreram, no arquivo txt localizado na pasta do codigo
                printf("NOME EXCLUIDO COM SUCESSO\n\n");
                system("pause");
                menu();
            }

        }

    }
    if(k == 0)
    {
        system("cls");
        printf("\n\n     **** O nome digitado n�o encontra-se na agenda. ****\n\n\n");
        system("pause");
        menu();
    }
}
//fun��o para ordena��o dos contatos salvos na agenda
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

                strcpy(aux, n[j]);//copiando o conte�do de n[i] p/ aux
                strcpy(n[j], n[j + 1]);//copiando o conte�do de n[i+1] p/ n[i]
                strcpy(n[j + 1], aux);//copiando o conte�do de aux p/ n[i+1]

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
    listar_contatos(nomes, email, numero, &qtd_adicionados);//chamada da fun��o listar_contatos
    system("pause");
    escrever(nomes, email, numero, &qtd_adicionados); //Escreve todas as atualiza��es que as variaveis sofreram, no arquivo txt localizado na pasta do codigo
    menu();
}
//fun��o responsavel por pesquisar contatos
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

//fun��o sobre para mostar informa��es sobre o programa
void sobre()
{
    printf("Agenda Eletr�nica para o armazenamento de contatos.\n\n\nRecursos de: \n\n");
    printf("pesquisar contato, adicionar contato,remover contato, listar todos os contatos,\ndeixar todos em ordem alfab�ticas.\n\n\n");
    printf("Guia: [S/N] = SIM/N�O\n\n\n*ATEN��O* Para evitar poss�veis falhas de ordena��o/pesquisa e/ou erros. Deve-se seguir um padr�o.\n\n");
    printf("Ao digitar caracteres especiais e/ou letras maiusculas voc� pode est� causando um erro de pesquisa e/ou \n\n");
    printf("ordena��o, os motivos s�o os os valores da tabela ASCII. Ex1.: {a =/= A} Ex2.: { A > a} \n");
    printf("\n\n--Desenvolvido por Washington Kl�bio--\n\n");
}
