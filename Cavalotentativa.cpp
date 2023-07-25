#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int contadorDePassos = 1;

// Vetores de deslocamento para os movimentos do cavalo (horizontal e vertical)
const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

// Função para verificar se uma determinada posição é válida no tabuleiro
bool isSafe(int x, int y, std::vector<std::vector<int>>& board) {
    return (x >= 0 && y >= 0 && x < 8 && y < 8 && board[x][y] == -1);
}

// Função recursiva para realizar o Passeio do Cavalo
bool knightTour(int x, int y, int moveCount, std::vector<std::vector<int>>& board) {
    if (moveCount == 8 * 8) {
        // Todas as células foram visitadas, ou seja, temos uma solução válida
        return true;
    }

    for (int i = 0; i < 8; ++i) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        if (isSafe(nextX, nextY, board)) {
            board[nextX][nextY] = moveCount;
            if (knightTour(nextX, nextY, moveCount + 1, board)) {
                contadorDePassos = contadorDePassos + 1;
                // Se a próxima chamada recursiva retorna true, então encontramos uma solução
                return true;
            }
            board[nextX][nextY] = -1; // Backtracking: desfaz o movimento
            contadorDePassos = contadorDePassos + 1;
        }
    }

    return false; // Nenhuma solução a partir desta posição
}

// Função para iniciar o Passeio do Cavalo
void solveKnightTour(int startX, int startY) {
    vector<vector<int>> board(8, vector<int>(8, -1));
    board[startX][startY] = 0; // Marcar a posição inicial como visitada
    int moveCount = 1;

    if (knightTour(startX, startY, 1, board)) {
        // Imprimir o tabuleiro com a solução
        bool isAdjacentToStart = false;
        for (int i = 0; i < 8; ++i) {
            int finalX = startX + dx[i];
            int finalY = startY + dy[i];
            if (finalX >= 0 && finalX < 8 && finalY >= 0 && finalY < 8) {
                if (board[finalX][finalY] == 64) { // 8x8 = 64
                    isAdjacentToStart = true;
                    break;
                }
            }
        }
        
        cout << "Solucao encontrada:\n";
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                cout << board[i][j] << "\t";
            }
            cout << "\n";
        }
        cout << "\nTotal de passos: " << contadorDePassos << std::endl;
        if (isAdjacentToStart) {
            cout << "\nMovimentacao do cavalo: Fechada" << endl;
        } else {
            cout << "\nMovimentacao do cavalo: Aberta" << endl;
        }
    } else {
        cout << "Nao foi possivel encontrar uma solucao a partir da posicao inicial.\n";
    }
}

int main() {
    int startX, startY;
    startX = 0;
    startY = 7;

    if (startX < 0 || startY < 0 || startX >= 8 || startY >= 8) {
        cout << "Posicao inicial invalida. As coordenadas devem estar entre 0 e " << 8-1 << ".\n";
        return 1;
    }
    auto startTime = std::chrono::high_resolution_clock::now();
    solveKnightTour(startX, startY);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Imprime o tempo de execução em milissegundos
    cout << "\nTempo de execucao: " << duration.count() << " ms" << std::endl;


    return 0;
}
