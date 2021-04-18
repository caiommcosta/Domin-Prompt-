#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <time.h>
using namespace std;

bool teste (char vetor[], int i, char domino[][3]) // PARA NÃO CRIAR PEÇAS REPETIDAS
{
    int cont = 0;

    for (int x=0; x <= i; x++)
    {
        for (int y=0; y < 2; y++)
        {
            if (vetor[y] == domino[x][y])
                cont++;
        }
        if (cont == 2)
        {
            return true;
        }
        cont = 0;
        for (int y=1, z=0; y >= 0; y--, z++)
        {
            if (vetor[z] == domino[x][y])
                cont++;
        }
        if (cont == 2)
        {
            return true;
        }
        cont = 0;
    }
    return false;
}
void leitura (char domino[][3]) // CRIANDO PEÇAS RANDÔMICAS
{
    char aux[3];

    srand(time(NULL));
    for (int i=0; i < 28; i++)
    {
        for (int j=0; j < 2; j++)
        {
            aux[j] = rand() % 7 + 48;
        }

        if (!teste(aux, i, domino))
        {
            for (int j=0; j < 2; j++)
            {
                domino[i][j] = aux[j];
            }
        }
        else
            i--;
    }

    for (int i=0; i < 28; i++)
    {
        cout << "|";
        for (int j=0; j < 2; j++)
        {
            if (j == 1)
                cout << domino[i][j];
            else
                cout << domino[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << endl;
}
void recebe_pecas (char domino[][3], char jogador_1[][3], char jogador_2[][3])
{
    for (int i=0, k=0; i < 7; i++, k += 2)
    {
        for (int j=0; j < 2; j++)
        {
            jogador_1[i][j] = domino[k][j]; // 1º RECEBE AS PEÇAS DAS POSIÇÕES 0, 2, 4, 6, 8, 10, 12
            jogador_2[i][j] = domino[k+1][j]; // 2º RECEBE AS PEÇAS DAS POSIÇÕES 1, 3, 5, 7, 9, 11, 13
        }
    }

    cout << "Jogador 1" << endl;
    for (int i=0; i < 7; i++)
    {
        for (int j=0; j < 2; j++)
        {
            cout << jogador_1[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Jogador 2" << endl;
    for (int i=0; i < 7; i++)
    {
        for (int j=0; j < 2; j++)
        {
            cout << jogador_2[i][j] << " ";
        }
        cout << endl;
    }
}
void verifica_carreirao (char carreirao_jogador_1[], char carreirao_jogador_2[], char jogador_1[][3],
                         char jogador_2[][3], int &aux1, int &aux2)
{
    // PARA SABER SE O JOGADOR POSSUI ALGUM CARREIRÃO
    for (int i=0; i < 7; i++)
    {
        if (jogador_1[i][0] == jogador_1[i][1])
        {
            carreirao_jogador_1[0] = jogador_1[i][0];
            carreirao_jogador_1[1] = jogador_1[i][1];
            aux1++;
        }
        if (jogador_2[i][0] == jogador_2[i][1])
        {
            carreirao_jogador_2[0] = jogador_2[i][0];
            carreirao_jogador_2[1] = jogador_2[i][1];
            aux2++;
        }
    }
    // SE TEM CARREIRÃO VERIFICAR O MAIOR DA MÃO 1
    if (aux1 > 0)
    {
        for (int i=0; i < 7; i++)
        {
            if (jogador_1[i][0] == jogador_1[i][1])
            {
                if ((strcmp(carreirao_jogador_1, jogador_1[i])) == 1)
                {
                    carreirao_jogador_1[0] = jogador_1[i][0];
                    carreirao_jogador_1[1] = jogador_1[i][1];
                }
            }
        }
    }
    // SE TEM CARREIRÃO VERIFICAR O MAIOR DA MÃO 2
    if (aux2 > 0)
    {
        for (int i=0; i < 7; i++)
        {
            if (jogador_2[i][0] == jogador_2[i][1])
            {
                if ((strcmp(carreirao_jogador_2, jogador_2[i])) == 1)
                {
                    carreirao_jogador_2[0] = jogador_2[i][0];
                    carreirao_jogador_2[1] = jogador_2[i][1];
                }
            }
        }
    }
}
void verifica_quem_inicia (char jogador_1[][3], char jogador_2[][3], int &aux1, int &aux2, int &x)
{
    char carreirao_jogador_1[3], carreirao_jogador_2[3];

    verifica_carreirao(carreirao_jogador_1, carreirao_jogador_2, jogador_1, jogador_2, aux1, aux2);
    cout << "Jogador 1 possui " << aux1 << " carreiroes" << endl;
    cout << "Jogador 2 possui " << aux2 << " carreiroes" << endl;

    if ((aux1 > 0) && (aux2 == 0))
    {
        x = 1;
        cout << "\nO jogador 1 inicia" << endl;
    }
    else
    {
        if ((aux2 > 0) && (aux1 == 0))
        {
            x = 2;
            cout << "\nO jogador 2 inicia." << endl;
        }
        else
        {
            if ((aux1 > 0) && (aux2 > 0))
            {
                x = strcmp(carreirao_jogador_1, carreirao_jogador_2);
                if ((x == -1))
                {
                    x = 1;
                    cout << "O jogador 1 inicia" << endl;
                }
                else
                {
                    x = 2;
                    cout << "O jogador 2 inicia" << endl;
                }
            }
            else
            {
                cout << "Início aleatorio... ";
                srand(time(NULL));
                cout << "O jogador " << rand() % 2 + 1 << " inicia" << endl;
            }
        }
    }
}
void imprime_mao (char entrada[][3], int tam)
{
    for (int i=0; i < tam; i++)
    {
        cout << i << " - ";
        for (int j=0; j < 2; j++)
        {
            cout << entrada[i][j] << " ";
        }
        cout << endl;
    }
}
void inverte_peca (char entrada[])
{
    int aux;

    aux = entrada[1];
    entrada[1] = entrada[0];
    entrada[0] = aux;
}
void colocar_peca (char entrada[], int tam, char mesa[29][3])
{
    char c;
    if (tam == 0)
    {
        for (int j=0; j <= 2; j++)
            mesa[0][j] = entrada[j];
    }
    else
    {
        cout << "Escolha onde colocar a peça. (E/D)" << endl;
        cin >> c;

        if ((c == 'E') || (c == 'e'))
        {
            if (mesa[0][0] != entrada[1])
            {
                inverte_peca(entrada);
                cout << "PEÇA INVERTIDA..." << endl;
            }

            for (int i = 0; i < tam; i++)
            {
                for (int j=0; j < 2; j++)
                {
                    mesa[tam-i][j] = mesa[tam-i-1][j];
                }
            }
            for (int j=0; j < 2; j++)
            {
                mesa[0][j] = entrada[j];
            }
        }
        else
        {
            if (mesa[tam][1] != entrada[0])
            {
                inverte_peca(entrada);
                cout << "PEÇA INVERTIDA..." << endl;
            }
            for (int j=0; j < 2; j++)
            {
                mesa[tam][j] = entrada[j];
            }
        }
    }
    //IMPRIMINDO A MESA
    cout << "---------------------" << endl;
    for (int i=0; i<=tam; i++)
    {
        cout << "|";
        for (int j=0; j<2; j++)
        {
            if (j == 1)
                cout << mesa[i][j];
            else
                cout << mesa[i][j] << " ";
        }
        cout << "|";
    }
    cout << "\n--------------------";
    cout << endl;
}
void organizar_mao (char entrada[][3], int p, int tam)
{
    tam--;
    for (int i=p; i < tam;i++)
    {
        for (int j=0; j < 2; j++)
        {
            entrada[i][j] = entrada[i+1][j];
        }
    }
}
void comeca (char jogador_1[][3], char jogador_2[][3], char mesa[][3], int &x, int &tam, int &tam1, int &tam2)
{
    int p;

    cout << "Escolha o número de uma peça iniciar a partida: " << endl;
    if (x == 1)
    {
        imprime_mao(jogador_1, tam1);
        do
        {
            cin >> p;
            colocar_peca(jogador_1[p], tam, mesa);
            organizar_mao(jogador_1, p, tam1);
            tam++;
            tam1--;
            x = 2;
        } while (p > tam1);
    }
    else
    {
        imprime_mao(jogador_2, tam2);
        do
        {
            cin >> p;
            colocar_peca(jogador_2[p], tam, mesa);
            organizar_mao(jogador_2, p, tam2);
            tam++;
            tam2--;
            x = 1;
        } while (p > tam2);
    }
}
bool condicao (void)
{
    int n;

    cout << "Digite\n1. para comprar peça\n0. para NÃO comprar peça" << endl;
    cin >> n;
    if (n == 1)
        return true;
    else
        return false;
}
void comprar_peca (char domino[][3], char entrada[][3], int &tam, int &num_peca)
{
    for (int j=0; j < 2; j++)
    {
        entrada[tam][j] = domino[num_peca][j];
    }
    cout << "Peça |" << domino[num_peca][0] << " " << domino[num_peca][1] << "| adicionada à mão do jogador." << endl;
    num_peca++;
    tam++;
}
void jogando (char domino[][3], char jogador_1[][3], char jogador_2[][3], char mesa[][3],
              int &x, int &tam, int &tam1, int &tam2)
{
    int p, num_peca = 14;
    while ((tam1 > 0) || (tam2 > 0))
    {
        cout << "É a vez do jogador " << x << endl;
        if (x == 1)
        {
            imprime_mao(jogador_1, tam1);
            if (!condicao())
            {
                cout << "Escolha o número da peça a jogar: ";
                cin >> p;
                colocar_peca(jogador_1[p], tam, mesa);
                organizar_mao(jogador_1, p, tam1);
                tam++;
                tam1--;
            }
            else
            {
                if (num_peca >= 28)
                {
                    cout << "NÃO HÁ PEÇAS PARA COMPRAR" << endl;
                    x = 2;
                    continue;
                }
                else
                {
                    comprar_peca(domino, jogador_1, tam1, num_peca);
                    continue;
                }
            }
        }
        if (x == 2)
        {
            imprime_mao(jogador_2, tam2);
            if (!condicao())
            {
                cout << "Escolha o número da peça a jogar: ";
                cin >> p;
                colocar_peca(jogador_2[p], tam, mesa);
                organizar_mao(jogador_2, p, tam2);
                tam++;
                tam2--;
            }
            else
            {
                if (num_peca >= 28)
                {
                    cout << "NÃO HÁ PEÇAS PARA COMPRR" << endl;
                    x = 1;
                    continue;
                }
                comprar_peca(domino, jogador_2, tam2, num_peca);
                continue;
            }
        }

        if (x == 1)
            x = 2;
        else
            x = 1;
    }
}
int main()
{
    setlocale(LC_ALL, "Portuguese");

    int x, aux1 = 0, aux2 = 0, tam = 0, tam1 = 7, tam2 = 7;
    char domino[29][3], jogador_1[22][3], jogador_2[22][3], mesa[29][3];
    leitura(domino);
    recebe_pecas(domino, jogador_1, jogador_2);
    verifica_quem_inicia(jogador_1, jogador_2, aux1, aux2, x);
    comeca(jogador_1, jogador_2, mesa, x, tam, tam1, tam2);
    jogando(domino, jogador_1, jogador_2, mesa, x, tam, tam1, tam2);

    return 0;
}
