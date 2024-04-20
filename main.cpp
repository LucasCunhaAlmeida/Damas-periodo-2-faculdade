#include <iostream>
#include <fstream>
#include <windows.h>
#include <limits>   // funcao nova
#define TAM 8

int jogadores[2];   // Escolha das pecas dos jogadores
int tabuleiro[TAM][TAM];    // Matriz global
int pontuacao_o = 0, pontuacao_x = 0;   // Pontuacao global

void menu();//Valter começa aqui
void opcoesMenu(char &opcao);
void comoJogar();
void fecharJogo();
void abrirRegras();//Termina aqui
void criarJogadores();//adilson começa aqui
void criarTabuleiro();
void imprimirTabuleiro();//Termina aqui
void imprimirPontuacao();//Bruno
void atualizarPrompt(int numeroJogador);//eu
void iniciarJogo();//Bruno
bool converterLetraNum(char letra, int &linha);//Gabriel começa aqui
bool verificarPeca(int peca, int numeroJogador, int &linOrigem, int &colOrigem);
void realizarMovimento(int linOrigem, int colOrigem, int linDestino, int colDestino);//Termina aqui
void realizarMovimento(int linOrigem, int colOrigem, int linMeio, int colMeio, int linDestino, int colDestino); // Sobrecarga de funcao Calixto
bool verificarMovimento(int numeroJogador, int peca, int &linOrigem, int &colOrigem, int &linDestino, int &colDestino);//Calixto
void movimentoInvalido(int numeroJogador, int peca, int &linOrigem, int &colOrigem, int &linDestino, int &colDestino);//Bruno começa aqui
void movimentoCaptura(int peca, int linOrigem, int colOrigem, int linDestino, int colDestino);
bool verificarCaptura(int peca, int linOrigem, int colOrigem, int linDestino, int colDestino);//Termina aqui
void capturaCadeia(int numeroJogador, int peca, int &linOrigem, int &colOrigem, int &linDestino, int &colDestino);//eu
bool verificarCapturaCadeia(int peca, int linOrigem, int colOrigem, int linDestino, int colDestino);//eu


using namespace std;


int main()
{
    menu();

    fecharJogo();

    return 0;
}

void menu()
{
    system("cls");

    char opcao;

    cout << "\t       :::::::::           :::          :::   :::           :::        ::::::::\n";
    cout << "\t      :+:    :+:        :+: :+:       :+:+: :+:+:        :+: :+:     :+:    :+:\n";
    cout << "\t     +:+    +:+       +:+   +:+     +:+ +:+:+ +:+      +:+   +:+    +:+\n";
    cout << "\t    +#+    +:+      +#++:++#++:    +#+  +:+  +#+     +#++:++#++:   +#++:++#++\n";
    cout << "\t   +#+    +#+      +#+     +#+    +#+       +#+     +#+     +#+          +#+\n";
    cout << "\t  #+#    #+#      #+#     #+#    #+#       #+#     #+#     #+#   #+#    #+#\n";
    cout << "\t #########       ###     ###    ###       ###     ###     ###    ########\n\n\n";

    opcoesMenu(opcao);

    switch(opcao)
    {
        case '1':
            system("cls");
            criarJogadores();
            criarTabuleiro();
            iniciarJogo();
            break;
        case '2':
            comoJogar();
            system("pause");
            menu();
            break;
        case '3':
            abrirRegras();
            system("pause");
            menu();
            break;
    }
}

void opcoesMenu(char &opcao)
{
    cout << "\t\t[1]  Iniciar Jogo                                     \n"
         << "\t\t[2]  Como Jogar?                                      \n"
         << "\t\t[3]  Regras                                           \n"
         << "\t\t------------------------------------------------------\n"
         << "\t\t[x]  Pressione qualquer outra tecla para fechar o jogo\n"
         << "\t\t------------------------------------------------------\n"
         << "\n\t\t-> ";

    cin >> opcao;
}

void comoJogar()
{
    system("cls");
    ifstream arq("ComoJogar.txt");
    if (arq.is_open()) {
        string linha;
        while (getline(arq, linha)) {
            cout << linha << endl;
        }
        arq.close();
    } else {
        cout << "Erro ao abrir a opcao Como Jogar!" << endl;
    }

    cout << endl;
}

void fecharJogo()
{
    int i;
    cout << "\n\n\t\tFinalizando o jogo";
    for(i = 0; i < 3; i++) {
        Sleep(500);
        cout << ".";
    }
    cout << "\n\n";
}

void abrirRegras()
{
    system("cls");
    ifstream arq("RegrasDamas.txt");
    if (arq.is_open()) {
        string linha;
        while (getline(arq, linha)) {
            cout << linha << endl;
        }
        arq.close();
    } else {
        cout << "Erro ao abrir as Regras!" << endl;
    }

    cout << endl;
}

void criarJogadores()   // Cria os jogadores e define qual ira jogar com a 'o' ou 'x'
{
    char escolha;

    cout << "Escolha sua peca jogador 1 ('o' ou 'x'): ";
    cin >> escolha;
    cout << endl;

    while(escolha != 'o' && escolha != 'O' && escolha != 'x' && escolha != 'X') {
        cout << "Escolha invalida!\nTente novamente.\n" << endl;
        cout << "Escolha sua peca jogador 1 ('o' ou 'x'): ";
        cin >> escolha;
    }

    if(escolha == 'o') {    // Condicional para definir a ordem dos jogadores
        jogadores[0] = 1; // 'o'
        jogadores[1] = 2; // 'x'
    } else {
        jogadores[0] = 2; // 'x'
        jogadores[1] = 1; // 'o'
    }

    cout << "\n\n";
}

void criarTabuleiro()    // Preencher matriz tabuleiro com valores das pecas e casas vazias.
{
    int i, j, cont;

    for(i = 0, cont = 0; i < 3; i++) {    // Pecas Pretas
        for(j = 0; j < TAM; j++) {

            if(i%2 == 0) {  // Linha par
                if(j%2 != 0) {  //Coluna impar
                    tabuleiro[i][j] = 2;    // Peca Preta
                    cont++;
                } else {
                    tabuleiro[i][j] = 8;    // Espaco vazio.
                }
            } else {    // Linha impar
                if(j%2 == 0) {  // Coluna par
                    tabuleiro[i][j] = 2;    // Peca Preta
                    cont++;
                } else {
                    tabuleiro[i][j] = 8;
                }
            }
        }
    }

    for(i = 3; i < 5; i++) {    // Meio do campo
        for(j = 0; j < TAM; j++) {
            if(i%2 == 0) {  // Linha par
                if(j%2 != 0) {  // Coluna impar
                    tabuleiro[i][j] = 0;
                } else {
                    tabuleiro[i][j] = 8;
                }
            } else {    // Linha impar
                if(j%2 == 0) {  // Coluna par
                    tabuleiro[i][j] = 0;
                } else {
                    tabuleiro[i][j] = 8;
                }
            }
        }
    }

    for(i = 5; i < TAM; i++) {  // Pecas Brancas
        for(j = 0; j < TAM; j++) {

            if(i%2 == 0) {
                if(j%2 != 0) {
                    tabuleiro[i][j] = 1;    // Peca Branca
                    cont++;
                } else {
                    tabuleiro[i][j] = 8;
                }
            } else {
                if(j%2 == 0) {
                    tabuleiro[i][j] = 1;    // Peca Branca
                    cont++;
                } else {
                    tabuleiro[i][j] = 8;
                }
            }

        }
    }
}

void imprimirTabuleiro() // Imprimir tabuleiro com simbolos.
{
    int i, j;
    char letras[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    cout << "\t\t\t\t  ";

    for(i = 0; i < TAM; i++) {  // Número colunas
        cout << i << " ";
    }

    cout << endl;

    for(i = 0; i < TAM; i++) {
        cout << "\t\t\t\t"; // Centralizar tabuleiro
        for(j = 0; j < TAM; j++) {
            if(tabuleiro[i][j] == 0) {
                if(j == 0) {
                    cout << letras[i] << " ";
                }
                cout << "  ";
            } else if(tabuleiro[i][j] == 1) {
                if(j == 0) {
                    cout << letras[i] << " ";
                }
                cout << "o ";
            } else if(tabuleiro[i][j] == 2) {
                if(j == 0) {
                    cout << letras[i] << " ";
                }
                cout << "x ";
            } else if(tabuleiro[i][j] == 3) {
                if(j == 0) {
                    cout << letras[i] << " ";
                }
                cout << "O ";
            } else if(tabuleiro[i][j] == 4) {
                if(j == 0) {
                    cout << letras[i] << " ";
                }
                cout << "X ";
            } else if(tabuleiro[i][j] == 8) {
                if(j == 0) {
                    cout << letras[i] << " ";
                }
                cout << "\xdb\xdb";
            }

        }

        cout << endl;
    }
    cout << endl;
}

void imprimirPontuacao()    // Imprime a pontuacao de acordo com a escolha do jogador 1 no comeco do jogo.
{
    cout << "Pontuacao\n";

    if(jogadores[0] == 1) // jogador 1 == 'o'
        cout << "Jogador 1: " << pontuacao_o << endl << "Jogador 2: " << pontuacao_x << "\n\n";
    else if(jogadores[0] == 2)    // jogador 1 == 'x'
        cout << "Jogador 1: " << pontuacao_x << endl << "Jogador 2: " << pontuacao_o << "\n\n";
}

void atualizarPrompt(int numeroJogador)//Limpa a tela, Imprime a pontuação atual, o tabuleiro e a ver de quem jogar
{
    system("cls");
    imprimirPontuacao();
    imprimirTabuleiro();
    cout << "\nTurno: Jogador "<< numeroJogador << "\n\n";
}

void iniciarJogo() // Faz o jogo funcionar, laço principal
{
    char res, linLetra;
    int linOrigem, colOrigem;
    int linDestino, colDestino;
    int jogadorTurno, numeroJogador;

    if(jogadores[0] == 1) { // jogador 1 escolheu "o". jogador 1 comeca
        jogadorTurno = 0;
        numeroJogador = 1;

    } else if(jogadores[0] == 2){ // jogador 1 escolheu "x". jogador 2 comeca
        jogadorTurno = 1;
        numeroJogador = 2;
    }                               // 'o' sempre comeca


    do {    // Laço para saber se os jogadores querem continuar depois de cada jogada

        imprimirTabuleiro();

        cout << "\nTurno: Jogador "<< numeroJogador
             << "\n\nEscolha uma peca: ";

        while(!(cin >> linLetra >> colOrigem) || (colOrigem > 7 || colOrigem < 0) || !(converterLetraNum(linLetra, linOrigem))) {   // Teste de verificacao de entrada de dados do teclado do jogador
            atualizarPrompt(numeroJogador);
            cout << "Comando de escolha de peca invalido!\nTente novamente: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        verificarPeca(jogadores[jogadorTurno], numeroJogador, linOrigem, colOrigem);

        cout << "Escolha um movimento: ";

        while(!(cin >> linLetra >> colDestino) || (colDestino > 7 || colDestino < 0) || !(converterLetraNum(linLetra, linDestino))) {   // Teste de verificacao de entrada de dados do teclado do jogador
            cout << "\n\nComando de escolha de movimento invalido!\nTente novamente: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        verificarMovimento(numeroJogador, jogadores[jogadorTurno], linOrigem, colOrigem, linDestino, colDestino);

        (jogadorTurno == 0) ? jogadorTurno = 1 : jogadorTurno = 0; // Condicionais que servem para trocar a o atual peca depois da jogada do mesmo.

        (numeroJogador == 1) ? numeroJogador = 2 : numeroJogador = 1;

        if(pontuacao_o != 12 && pontuacao_x != 12) {
            cout << "\nDeseja jogar novamente?(s/n): ";
            cin >> res;

            res = toupper(res);
        }

        system("cls");

        imprimirPontuacao();

    } while(res == 'S' && pontuacao_o != 12 && pontuacao_x != 12);    // Caso os jogadores decidam jogar depois de uma jogada ter sido realizada.

    imprimirTabuleiro();

    if(pontuacao_o > pontuacao_x) {

        (jogadores[0] == 1) ? cout << "\n\njogador 1 venceu!" << endl : cout << "\n\njogador 2 venceu!" << endl;

    } else if(pontuacao_o < pontuacao_x) {

        (jogadores[0] == 2) ? cout << "\n\njogador 1 venceu!" << endl : cout << "\n\njogador 2 venceu!" << endl;

    } else {

        cout << "\n\nEmpate!" << endl;

    }

    cout << "\n\nDeseja voltar para o menu?(s/n) ";
    cin >> res;

    res = toupper(res);

    if(res == 'S') {
        menu();
    }
}

bool converterLetraNum(char letra, int &linha)   // Converte as coodernadas em letras para numero.
{
    int i;
    char letraCoordenada[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    letra = toupper(letra);

    for(i = 0; i < 8; i++) {
        if(letra == letraCoordenada[i]) {
            linha = i;
            return true;
        }
    }

    return false;
}

bool verificarPeca(int peca, int numeroJogador, int &linOrigem, int &colOrigem) // Verifica se a peca do jogador e a correta
{
    char linLetra;

    if(peca == 1) {  // Brancas ('o')

        if(tabuleiro[linOrigem][colOrigem] == 1) {  // Peca 'o'
            return true;
        } else if(tabuleiro[linOrigem][colOrigem] == 3) {    // Dama 'O'
            return true;

        } else {

            do{

                cout << "\nPeca invalida!\nEscolha outra peca: ";

                while(!(cin >> linLetra >> colOrigem) || (colOrigem > 7 || colOrigem < 0) || !(converterLetraNum(linLetra, linOrigem))) {
                    atualizarPrompt(numeroJogador);
                    cout << "Comando de escolha de peca invalido!\nTente novamente: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

            } while(tabuleiro[linOrigem][colOrigem] != 1 && tabuleiro[linOrigem][colOrigem] != 3);

            return true;
        }

    } else {    // 'x'

        if(tabuleiro[linOrigem][colOrigem] == 2) {  // Peca 'x'
            return true;
        } else if(tabuleiro[linOrigem][colOrigem] == 4) {   // Dama 'X'
            return true;
        } else {

            do{

                cout << "\nPeca invalida!\nEscolha outra peca: ";

                while(!(cin >> linLetra >> colOrigem) || (colOrigem > 7 || colOrigem < 0) || !(converterLetraNum(linLetra, linOrigem))) {
                    atualizarPrompt(numeroJogador);
                    cout << "Comando de escolha de peca invalido!\nTente novamente: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

            } while(tabuleiro[linOrigem][colOrigem] != 2 && tabuleiro[linOrigem][colOrigem] != 4);

            return true;
        }

    }
}

void realizarMovimento(int linOrigem, int colOrigem, int linDestino, int colDestino)  // Realiza o movimento normal das pecas
{
    tabuleiro[linDestino][colDestino] = tabuleiro[linOrigem][colOrigem];    // Troca o valor da casa de origem com a casa de destino
    tabuleiro[linOrigem][colOrigem] = 0;    // Zera o valor da coordenada de origem
}

void realizarMovimento(int linOrigem, int colOrigem, int linMeio, int colMeio, int linDestino, int colDestino)  // Realiza o movimento de captura das pecas inimigas
{
    tabuleiro[linMeio][colMeio] = 0;    // Transforma a casa da peca inimiga que foi capturada em casa vazia.
    tabuleiro[linDestino][colDestino] = tabuleiro[linOrigem][colOrigem];    // Troca o valor da casa de origem com a casa de destino
    tabuleiro[linOrigem][colOrigem] = 0;    // Zera a casa de origem;
}

bool verificarMovimento(int numeroJogador, int peca, int &linOrigem, int &colOrigem, int &linDestino, int &colDestino)  // Verifica qual foi o tipo de movimento escolhido pelo jogador
{

    if(peca == 1) {  // 'o'

        if(tabuleiro[linOrigem][colOrigem] == 1) {  // Peca 'o' normal

            if(tabuleiro[linDestino][colDestino] == 0 ) { // Teste para saber se a casa esta vazia

                if((linDestino < linOrigem) && (colDestino == colOrigem+1 || colDestino == colOrigem-1)) {    // Movimento normal da peca 'o'.

                    realizarMovimento(linOrigem, colOrigem, linDestino, colDestino);    // Sobrecarga de funcao. Chamamos a funcao que tem o mesmo nome so que com 4 parametros

                    if((linDestino == 0) && (linDestino == linOrigem-1)) {    // 'o' chegou na linha 0.

                        tabuleiro[linDestino][colDestino] = 3;  // Dama 'O' criada

                    }

                    return true;
                } else if((linDestino < linOrigem) && verificarCaptura(peca, linOrigem, colOrigem, linDestino, colDestino)) {   // Movimento de captura da peca 'o' (nao captura para tras);

                    movimentoCaptura(peca, linOrigem, colOrigem, linDestino, colDestino);    // realiza a captura da peca inimiga.

                    while(verificarCapturaCadeia(peca, linOrigem, colOrigem, linDestino, colDestino)) {  // Captura em cadeia 'o'

                        capturaCadeia(numeroJogador, peca, linOrigem, colOrigem, linDestino, colDestino);

                    }

                    if((linDestino == 0) && (linDestino == linOrigem-2)) {

                        tabuleiro[linDestino][colDestino] = 3;  // Dama 'O' criada

                    }

                    return true;

                }
            }

        } else if(tabuleiro[linOrigem][colOrigem] == 3) {   // Dama branca 'O'

            if(tabuleiro[linDestino][colDestino] == 0) {    // Teste para saber se a casa esta vazia

                if(colDestino == colOrigem+1 || colDestino == colOrigem-1) {  // Movimento normal da Dama

                    realizarMovimento(linOrigem, colOrigem, linDestino, colDestino);    // Sobrecarga

                    return true;

                } else if(verificarCaptura(peca, linOrigem, colOrigem, linDestino, colDestino)) {    // Movimento de captura da Dama

                    movimentoCaptura(peca, linOrigem, colOrigem, linDestino, colDestino);

                    while(verificarCapturaCadeia(peca, linOrigem, colOrigem, linDestino, colDestino)) {  // Captura em cadeia. Dama 'O'

                        capturaCadeia(numeroJogador, peca, linOrigem, colOrigem, linDestino, colDestino);
                    }

                    return true;
                }

            }

        }

        movimentoInvalido(numeroJogador, peca, linOrigem, colOrigem, linDestino, colDestino);   // Caso o Movimento escolhido pelo peca seja invalido

        return true;

    } else {    // 'x'

        if(tabuleiro[linOrigem][colOrigem] == 2) {  // Peca normal 'x'

            if(tabuleiro[linDestino][colDestino] == 0 ) { // Teste para saber se a casa esta vazia

                if((linDestino > linOrigem) && (colDestino == colOrigem+1 || colDestino == colOrigem-1)) {    // Movimento normal da peca 'x';

                    realizarMovimento(linOrigem, colOrigem, linDestino, colDestino);    // Sobrecarga

                    if((linDestino == 7) && (linDestino == linOrigem+1)) {

                        tabuleiro[linDestino][colDestino] = 4;  // Dama 'X' criada

                    }

                    return true;

                } else if((linDestino > linOrigem) && verificarCaptura(peca, linOrigem, colOrigem, linDestino, colDestino)) {   // Movimento de captura da peca 'x' (nao captura para tras);

                        movimentoCaptura(peca, linOrigem, colOrigem, linDestino, colDestino);    // Caso o movimento de captura seja valido.

                        while(verificarCapturaCadeia(peca, linOrigem, colOrigem, linDestino, colDestino)) {  // Captura em cadeia. 'x'

                            capturaCadeia(numeroJogador, peca, linOrigem, colOrigem, linDestino, colDestino);
                        }

                        if((linDestino == 7) && (linDestino == linOrigem+2)) {

                            tabuleiro[linDestino][colDestino] = 4;  // Dama 'X' criada

                        }

                        return true;

                }
            }
        } else if(tabuleiro[linOrigem][colOrigem] == 4) {   // Dama 'X'

            if(tabuleiro[linDestino][colDestino] == 0) {    // Teste para saber se a casa esta vazia

                if(colDestino == colOrigem+1 || colDestino == colOrigem-1) {  // Movimento normal da Dama

                    realizarMovimento(linOrigem, colOrigem, linDestino, colDestino);    // Sobrecarga

                    return true;

                } else if(verificarCaptura(peca, linOrigem, colOrigem, linDestino, colDestino)) {    // Movimento de captura da Dama

                    movimentoCaptura(peca, linOrigem, colOrigem, linDestino, colDestino);

                    while(verificarCapturaCadeia(peca, linOrigem, colOrigem, linDestino, colDestino)) {  // Captura em cadeia. Dama 'X'

                        capturaCadeia(numeroJogador, peca, linOrigem, colOrigem, linDestino, colDestino);

                    }

                    return true;

                }

            }
        }

            movimentoInvalido(numeroJogador, peca, linOrigem, colOrigem, linDestino, colDestino);

            return true;
    }
}

void movimentoInvalido(int numeroJogador, int peca, int &linOrigem, int &colOrigem, int &linDestino, int &colDestino)   // Caso o movimento seja invalido, pede para o peca repetir a jogada
{
        char linLetra;

        cout << "\nMovimento invalido!\nEscolha uma peca: ";

        while(!(cin >> linLetra >> colOrigem) || (colOrigem > 7 || colOrigem < 0) || !(converterLetraNum(linLetra, linOrigem))) {
            atualizarPrompt(numeroJogador);
            cout << "Comando de escolha de peca invalido!\nTente novamente: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        verificarPeca(peca, numeroJogador, linOrigem, colOrigem);

        cout << "Escolha um movimento: ";

        while(!(cin >> linLetra >> colDestino) || (colDestino > 7 || colDestino < 0) || !(converterLetraNum(linLetra, linDestino))) {
            atualizarPrompt(numeroJogador);
            cout << "Comando de escolha de movimento invalido!\nTente novamente: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        verificarMovimento(numeroJogador, peca, linOrigem, colOrigem, linDestino, colDestino);
}

void movimentoCaptura(int peca, int linOrigem, int colOrigem, int linDestino, int colDestino)    // Realiza o movimento de captura de acordo com a peca escolhida pelo jogador
{
    if(peca == 1) {  // 'o'

        if(tabuleiro[linOrigem][colOrigem] == 1) {  // 'o' normal

            if((tabuleiro[linDestino+1][colDestino-1] == 2 || tabuleiro[linDestino+1][colDestino-1] == 4) &&
                colOrigem+1 == colDestino-1) { // Superior Direito

                realizarMovimento(linOrigem, colOrigem, linDestino+1, colDestino-1, linDestino, colDestino);
                pontuacao_o += 1;

            } else if((tabuleiro[linDestino+1][colDestino+1] == 2 || tabuleiro[linDestino+1][colDestino+1] == 4) &&
                       colOrigem-1 == colDestino+1){  // Superior esquerdo

                realizarMovimento(linOrigem, colOrigem, linDestino+1, colDestino+1, linDestino, colDestino);
                pontuacao_o += 1;

            }

        } else if(tabuleiro[linOrigem][colOrigem] == 3) {   // 'O' Dama

            if((tabuleiro[linDestino+1][colDestino-1] == 2 || tabuleiro[linDestino+1][colDestino-1] == 4) &&
                colOrigem+1 == colDestino-1 && linOrigem > linDestino) { // Superior Direito

                realizarMovimento(linOrigem, colOrigem, linDestino+1, colDestino-1, linDestino, colDestino);
                pontuacao_o += 1;

            } else if((tabuleiro[linDestino+1][colDestino+1] == 2 || tabuleiro[linDestino+1][colDestino+1] == 4) &&
                       colOrigem-1 == colDestino+1 && linOrigem > linDestino){  // Superior esquerdo

                realizarMovimento(linOrigem, colOrigem, linDestino+1, colDestino+1, linDestino, colDestino);
                pontuacao_o += 1;

            } else if((tabuleiro[linDestino-1][colDestino+1] == 2 || tabuleiro[linDestino-1][colDestino+1] == 4) &&
                       colOrigem-1 == colDestino+1 && linOrigem < linDestino) {   // Inferior Esquerdo

                realizarMovimento(linOrigem, colOrigem, linDestino-1, colDestino+1, linDestino, colDestino);
                pontuacao_o += 1;

            } else if((tabuleiro[linDestino-1][colDestino-1] == 2 || tabuleiro[linDestino-1][colDestino-1] == 4) &&
                       colOrigem+1 == colDestino-1 && linOrigem < linDestino) {    // Inferior Direito

                realizarMovimento(linOrigem, colOrigem, linDestino-1, colDestino-1, linDestino, colDestino);
                pontuacao_o += 1;

            }

        }

    } else if(peca == 2) {    // 'x'

        if(tabuleiro[linOrigem][colOrigem] == 2) {  // 'x' normal

            if((tabuleiro[linDestino-1][colDestino+1] == 1 || tabuleiro[linDestino-1][colDestino+1] == 3) &&
                colOrigem-1 == colDestino+1) {   // Inferior Esquerdo

                realizarMovimento(linOrigem, colOrigem, linDestino-1, colDestino+1, linDestino, colDestino);
                pontuacao_x += 1;

            } else if((tabuleiro[linDestino-1][colDestino-1] == 1 || tabuleiro[linDestino-1][colDestino-1] == 3) &&
                       colOrigem+1 == colDestino-1) {    // Inferior Direito

                realizarMovimento(linOrigem, colOrigem, linDestino-1, colDestino-1, linDestino, colDestino);
                pontuacao_x += 1;

            }

        } else if(tabuleiro[linOrigem][colOrigem] == 4) {   // 'X' Dama

            if((tabuleiro[linDestino+1][colDestino-1] == 1 || tabuleiro[linDestino+1][colDestino-1] == 3) &&
                colOrigem+1 == colDestino-1 && linOrigem > linDestino) { // Superior Direito

                realizarMovimento(linOrigem, colOrigem, linDestino+1, colDestino-1, linDestino, colDestino);
                pontuacao_x += 1;

            } else if((tabuleiro[linDestino+1][colDestino+1] == 1 || tabuleiro[linDestino+1][colDestino+1] == 3) &&
                       colOrigem-1 == colDestino+1 && linOrigem > linDestino){  // Superior esquerdo

                realizarMovimento(linOrigem, colOrigem, linDestino+1, colDestino+1, linDestino, colDestino);
                pontuacao_x += 1;

           } else if((tabuleiro[linDestino-1][colDestino+1] == 1 || tabuleiro[linDestino-1][colDestino+1] == 3) &&
                      colOrigem-1 == colDestino+1 && linOrigem < linDestino) {   // Inferior Esquerdo

                realizarMovimento(linOrigem, colOrigem, linDestino-1, colDestino+1, linDestino, colDestino);
                pontuacao_x += 1;

            } else if((tabuleiro[linDestino-1][colDestino-1] == 1 || tabuleiro[linDestino-1][colDestino-1] == 3) &&
                       colOrigem+1 == colDestino-1 && linOrigem < linDestino) {    // Inferior Direito

                realizarMovimento(linOrigem, colOrigem, linDestino-1, colDestino-1, linDestino, colDestino);
                pontuacao_x += 1;

            }
        }

    }
}

bool verificarCaptura(int peca, int linOrigem, int colOrigem, int linDestino, int colDestino)    // Verifica se o movimento de captura do jogador e valido
{
/*
     A logica dessa funcao e olhar a peca escolhida pelo jogador com a linOrigem e colOrigem e a partir disso retornar e um movimento de captura valido
    ou nao.
     Lembrando que para a captura ser valida deve exitir uma casa, na diagonal, com o inimigo da peca atual e um casa vazia depois dessa.
*/
    if(peca == 1) {  // 'o'

        if(tabuleiro[linOrigem][colOrigem] == 1) {  // 'o'

            if((tabuleiro[linDestino+1][colDestino-1] == 2 || tabuleiro[linDestino+1][colDestino-1] == 4) &&
                 colDestino == colOrigem+2) { // Superior direito. Movimento referente a captura das pecas 'o', pra cima e direita.

                return true;

            } else if((tabuleiro[linDestino+1][colDestino+1] == 2 || tabuleiro[linDestino+1][colDestino+1] == 4) &&
                       colDestino == colOrigem-2){  // Superior esquerdo. Movimento referente a captura das pecas 'o', pra cima e esquerda.

                return true;

            } else {    // Movimento de captura invalido escolhido pelo jogador

                return false;

            }

        } else if(tabuleiro[linOrigem][colOrigem] == 3) {   // 'O'.  A dama pode capturar pecas tanto para cima quanto para baixo do tabuleiro

            if((tabuleiro[linDestino+1][colDestino-1] == 2 || tabuleiro[linDestino+1][colDestino-1] == 4) &&
                colDestino == colOrigem+2) { // Superior direito

                return true;

            } else if((tabuleiro[linDestino+1][colDestino+1] == 2 || tabuleiro[linDestino+1][colDestino+1] == 4) &&
                       colDestino == colOrigem-2){  // Superior esquerdo

                return true;

            } else if((tabuleiro[linDestino-1][colDestino+1] == 2 || tabuleiro[linDestino-1][colDestino+1] == 4) &&
                       colDestino == colOrigem-2) {   // Inferior esquerdo

                return true;

            } else if((tabuleiro[linDestino-1][colDestino-1] == 2 || tabuleiro[linDestino-1][colDestino-1] == 4) &&
                       colDestino == colOrigem+2) {    // Inferior direito

                return true;

            } else {
                 // Movimento de captura invalido escolhido pelo jogador
                return false;

            }
        }

    } else {    // 'x'

        if(tabuleiro[linOrigem][colOrigem] == 2) {  // 'x'

            if((tabuleiro[linDestino-1][colDestino+1] == 1 || tabuleiro[linDestino-1][colDestino+1] == 3) &&
                colDestino == colOrigem-2) {   // Inferior esquerdo. Movimento referente a captura das pecas 'x', pra baixo e esquerda.

                return true;

            } else if((tabuleiro[linDestino-1][colDestino-1] == 1 || tabuleiro[linDestino-1][colDestino-1] == 3) &&
                       colDestino == colOrigem+2) {    // Inferior direito. Movimento referente a captura das pecas 'x', pra baixo e direita.
                return true;
            } else {    // Movimento de captura invalido escolhido pelo usuário
                return false;
            }

        } else if(tabuleiro[linOrigem][colOrigem] == 4) {   // 'X'

            if((tabuleiro[linDestino+1][colDestino-1] == 1 || tabuleiro[linDestino+1][colDestino-1] == 3) &&
                colDestino == colOrigem+2) { // Superior direito

                return true;

            } else if((tabuleiro[linDestino+1][colDestino+1] == 1 || tabuleiro[linDestino+1][colDestino+1] == 3) &&
                       colDestino == colOrigem-2){  // Superior esquerdo

                return true;

            } else if((tabuleiro[linDestino-1][colDestino+1] == 1 || tabuleiro[linDestino-1][colDestino+1] == 3) &&
                       colDestino == colOrigem-2) {   // Inferior esquerdo

                return true;

            } else if((tabuleiro[linDestino-1][colDestino-1] == 1 || tabuleiro[linDestino-1][colDestino-1] == 3) &&
                       colDestino == colOrigem+2) {    // Inferior direito

                return true;

            } else {
                return false;
            }
        }
    }
}

void capturaCadeia(int numeroJogador, int peca, int &linOrigem, int &colOrigem, int &linDestino, int &colDestino){   // Logica da captura em cadeia das pecas.
    char linLetra;

    atualizarPrompt(numeroJogador);

    cout << "Captura em cadeia disponivel!\n\n";

    linOrigem = linDestino;
    colOrigem = colDestino;

    cout << "Escolha o movimento de captura: ";

    while(!(cin >> linLetra >> colDestino) || (colDestino > 7 || colDestino < 0) || !(converterLetraNum(linLetra, linDestino))) {
        cout << "\n\nComando de escolha de movimento invalido!\nTente novamente: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while(!verificarCaptura(peca, linOrigem, colOrigem, linDestino, colDestino)) {

        cout << "\nMovimento invalido!\n\n";
        cout << "Escolha um movimento: ";
        while(!(cin >> linLetra >> colDestino) || (colDestino > 7 || colDestino < 0) || !(converterLetraNum(linLetra, linDestino))) {
            cout << "\n\nComando de escolha de movimento invalido!\nTente novamente: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    movimentoCaptura(peca, linOrigem, colOrigem, linDestino, colDestino);
}

bool verificarCapturaCadeia(int peca, int linOrigem, int colOrigem, int linDestino, int colDestino)  // Verifica se depois da captura realizada existe a possibilidade de capturar outras pecas inimigas
{
    /*
        Depois de realizado a captura normal da peca, e testado se a captura em cadeia esta disponivel para a nova posicao da peca depois da captura
    */

    linOrigem = linDestino; // A linOrigem e colOrigem irao receber os valores da linDestino e colDestino do movimento de captura realizado pelo jogador.
    colOrigem = colDestino;

    if(peca == 1) { // 'o'

        if(tabuleiro[linOrigem][colOrigem] == 1) {  // 'o'

            if((tabuleiro[linOrigem-1][colOrigem+1] == 2 ||
                tabuleiro[linOrigem-1][colOrigem+1] == 4) &&
                tabuleiro[linOrigem-2][colOrigem+2] == 0 &&
                (colOrigem < 6 && linOrigem > 1)) {    // Superior direito

                return true;

            } else if((tabuleiro[linOrigem-1][colOrigem-1] == 2 ||
                       tabuleiro[linOrigem-1][colOrigem-1] == 4) &&
                       tabuleiro[linOrigem-2][colOrigem-2] == 0 &&
                       (colOrigem > 1 && linOrigem > 1)) {   //Superior esquerdo

                return true;

            }

        } else if(tabuleiro[linOrigem][colOrigem] == 3) {   // 'O' Dama

            if((tabuleiro[linOrigem-1][colOrigem+1] == 2 ||
                tabuleiro[linOrigem-1][colOrigem+1] == 4) &&
                tabuleiro[linOrigem-2][colOrigem+2] == 0 &&
                (colOrigem < 6 && linOrigem > 1)) {    // Superior direito

                return true;

            } else if((tabuleiro[linOrigem-1][colOrigem-1] == 2 ||
                       tabuleiro[linOrigem-1][colOrigem-1] == 4) &&
                       tabuleiro[linOrigem-2][colOrigem-2] == 0 &&
                       (colOrigem > 1 && linOrigem > 1)) {   //Superior esquerdo

                return true;

            } else if((tabuleiro[linOrigem+1][colOrigem+1] == 2 ||
                       tabuleiro[linOrigem+1][colOrigem+1] == 4) &&
                       tabuleiro[linOrigem+2][colOrigem+2] == 0 &&
                       (colOrigem < 6 && linOrigem < 6)) {    // Inferior direito

                return true;

            } else if((tabuleiro[linOrigem+1][colOrigem-1] == 2 ||
                       tabuleiro[linOrigem+1][colOrigem-1] == 4) &&
                       tabuleiro[linOrigem+2][colOrigem-2] == 0 &&
                       (colOrigem > 1 && linOrigem < 6)) {   // Inferior esquerdo

                return true;

            }
        }

        return false;

    } else if(peca == 2) {

        if(tabuleiro[linOrigem][colOrigem] == 2) {  // 'x'

            if((tabuleiro[linOrigem+1][colOrigem+1] == 1 ||
                tabuleiro[linOrigem+1][colOrigem+1] == 3) &&
                tabuleiro[linOrigem+2][colOrigem+2] == 0 &&
                (colOrigem < 6 && linOrigem < 6)) {    // Inferior direito

                return true;

            } else if((tabuleiro[linOrigem+1][colOrigem-1] == 1 ||
                       tabuleiro[linOrigem+1][colOrigem-1] == 3) &&
                       tabuleiro[linOrigem+2][colOrigem-2] == 0 &&
                       (colOrigem > 1 && linOrigem < 6)) {   // Inferior esquerdo

                return true;

            }

        } else if(tabuleiro[linOrigem][colOrigem] == 4) {   // 'X' Dama

            if((tabuleiro[linOrigem-1][colOrigem+1] == 1 ||
                tabuleiro[linOrigem-1][colOrigem+1] == 3) &&
                tabuleiro[linOrigem-2][colOrigem+2] == 0 &&
                (colOrigem < 6 && linOrigem > 1)) {    // Superior direito

                return true;

            } else if((tabuleiro[linOrigem-1][colOrigem-1] == 1 ||
                       tabuleiro[linOrigem-1][colOrigem-1] == 3) &&
                       tabuleiro[linOrigem-2][colOrigem-2] == 0 &&
                       (colOrigem > 1 && linOrigem > 1)) {   //Superior esquerdo

                return true;

            } else if((tabuleiro[linOrigem+1][colOrigem+1] == 1 ||
                       tabuleiro[linOrigem+1][colOrigem+1] == 3) &&
                       tabuleiro[linOrigem+2][colOrigem+2] == 0 &&
                       (colOrigem < 6 && linOrigem < 6)) {    // Inferior direito

                return true;

            } else if((tabuleiro[linOrigem+1][colOrigem-1] == 1 ||
                       tabuleiro[linOrigem+1][colOrigem-1] == 3) &&
                       tabuleiro[linOrigem+2][colOrigem-2] == 0 &&
                       (colOrigem > 1 && linOrigem < 6)) {   // Inferior esquerdo

                return true;

            }
        }

        return false;

    }
}
