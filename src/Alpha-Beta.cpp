#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

enum Piece
{
    EMPTY,
    X,
    O
};

using Board = std::vector<Piece>;
const int BOARD_SIZE = 8;

bool checkWin(const Board &board, Piece player)
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE - 4; ++j)
        {
            if (board[i * BOARD_SIZE + j] == player &&
                board[i * BOARD_SIZE + j + 1] == player &&
                board[i * BOARD_SIZE + j + 2] == player &&
                board[i * BOARD_SIZE + j + 3] == player &&
                board[i * BOARD_SIZE + j + 4] == player)
            {
                return true;
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE - 4; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i * BOARD_SIZE + j] == player &&
                board[(i + 1) * BOARD_SIZE + j] == player &&
                board[(i + 2) * BOARD_SIZE + j] == player &&
                board[(i + 3) * BOARD_SIZE + j] == player &&
                board[(i + 4) * BOARD_SIZE + j] == player)
            {
                return true;
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE - 4; ++i)
    {
        for (int j = 0; j < BOARD_SIZE - 4; ++j)
        {
            if (board[i * BOARD_SIZE + j] == player &&
                board[(i + 1) * BOARD_SIZE + j + 1] == player &&
                board[(i + 2) * BOARD_SIZE + j + 2] == player &&
                board[(i + 3) * BOARD_SIZE + j + 3] == player &&
                board[(i + 4) * BOARD_SIZE + j + 4] == player)
            {
                return true;
            }
        }
    }

    for (int i = 4; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE - 4; ++j)
        {
            if (board[i * BOARD_SIZE + j] == player &&
                board[(i - 1) * BOARD_SIZE + j + 1] == player &&
                board[(i - 2) * BOARD_SIZE + j + 2] == player &&
                board[(i - 3) * BOARD_SIZE + j + 3] == player &&
                board[(i - 4) * BOARD_SIZE + j + 4] == player)
            {
                return true;
            }
        }
    }
    return false;
}

bool isBoardFull(const Board &board)
{
    return std::none_of(board.begin(), board.end(), [](Piece p)
                        { return p == EMPTY; });
}

int evaluate(const Board &board)
{
    if (checkWin(board, X))
    {
        return 1000;
    }
    if (checkWin(board, O))
    {
        return -1000;
    }
    return 0;
}

int alphaBeta(Board &board, int depth, bool maximizingPlayer, int alpha, int beta)
{
    if (depth == 0 || checkWin(board, X) || checkWin(board, O))
    {
        return evaluate(board);
    }

    if (maximizingPlayer)
    {
        int maxEval = -10000;
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
        {
            if (board[i] == EMPTY)
            {
                board[i] = X;
                int eval = alphaBeta(board, depth - 1, false, alpha, beta);
                board[i] = EMPTY;
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
        }
        return maxEval;
    }
    else
    {
        int minEval = 10000;
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
        {
            if (board[i] == EMPTY)
            {
                board[i] = O;
                int eval = alphaBeta(board, depth - 1, true, alpha, beta);
                board[i] = EMPTY;
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
        }
        return minEval;
    }
}

void aiMove(Board &board, Piece piece)
{
    int bestMove = -1;
    int bestValue = piece == X ? -10000 : 10000;
    std::vector<int> availableMoves;
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
    {
        if (board[i] == EMPTY)
        {
            availableMoves.push_back(i);
            board[i] = piece;
            int moveValue = alphaBeta(board, 4, piece == O, -10000, 10000); // ���Ϊ4
            board[i] = EMPTY;
            if ((piece == X && moveValue > bestValue) || (piece == O && moveValue < bestValue))
            {
                bestMove = i;
                bestValue = moveValue;
            }
        }
    }
    if (bestMove == -1 && !availableMoves.empty())
    {
        std::random_shuffle(availableMoves.begin(), availableMoves.end());
        bestMove = availableMoves[0];
    }
    board[bestMove] = piece;
}

void playGame()
{
    Board board(BOARD_SIZE * BOARD_SIZE, EMPTY);

    // 计时开始
    auto start = chrono::high_resolution_clock::now();

    while (true)
    {
        if (checkWin(board, X))
        {
            break;
        }
        if (isBoardFull(board))
        {
            break;
        }
        aiMove(board, X);
        if (checkWin(board, O))
        {
            break;
        }
        if (isBoardFull(board))
        {
            break;
        }
        aiMove(board, O);
    }

    // 计时结束
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Alpha-Beta Pruning Time: " << duration.count() << "ms" << endl;
}

int main()
{
    playGame();
    return 0;
}
