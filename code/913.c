#include <stdlib.h>
#include <string.h>

#define DRAW 0
#define MOUSE_WIN 1
#define CAT_WIN 2
#define MOUSE_TURN 0
#define CAT_TURN 1

int catMouseGame(int** graph, int graphSize, int* graphColSize) {
    int n = graphSize;

    int states[50][50][2];
    memset(states, DRAW, sizeof(states));

    int out_degree[50][50][2];

    int queue[50 * 50 * 2][4];
    int head = 0, tail = 0;

    for (int m = 0; m < n; m++) {
        for (int c = 0; c < n; c++) {
            out_degree[m][c][MOUSE_TURN] = graphColSize[m];
            out_degree[m][c][CAT_TURN] = graphColSize[c];
            for (int i = 0; i < graphColSize[c]; i++) {
                if (graph[c][i] == 0) {
                    out_degree[m][c][CAT_TURN]--;
                    break;
                }
            }
        }
    }

    for (int i = 1; i < n; i++) {
        states[0][i][MOUSE_TURN] = MOUSE_WIN;
        states[0][i][CAT_TURN] = MOUSE_WIN;
        queue[tail][0] = 0; queue[tail][1] = i; queue[tail][2] = MOUSE_TURN; queue[tail][3] = MOUSE_WIN; tail++;
        queue[tail][0] = 0; queue[tail][1] = i; queue[tail][2] = CAT_TURN; queue[tail][3] = MOUSE_WIN; tail++;

        states[i][i][MOUSE_TURN] = CAT_WIN;
        states[i][i][CAT_TURN] = CAT_WIN;
        queue[tail][0] = i; queue[tail][1] = i; queue[tail][2] = MOUSE_TURN; queue[tail][3] = CAT_WIN; tail++;
        queue[tail][0] = i; queue[tail][1] = i; queue[tail][2] = CAT_TURN; queue[tail][3] = CAT_WIN; tail++;
    }

    while (head < tail) {
        int m_pos = queue[head][0];
        int c_pos = queue[head][1];
        int turn = queue[head][2];
        int winner = queue[head][3];
        head++;

        int prev_turn = 1 - turn;

        if (prev_turn == MOUSE_TURN) {
            for (int i = 0; i < graphColSize[m_pos]; i++) {
                int m_prev = graph[m_pos][i];
                if (states[m_prev][c_pos][MOUSE_TURN] == DRAW) {
                    if (winner == MOUSE_WIN) {
                        states[m_prev][c_pos][MOUSE_TURN] = MOUSE_WIN;
                        queue[tail][0] = m_prev; queue[tail][1] = c_pos; queue[tail][2] = MOUSE_TURN; queue[tail][3] = MOUSE_WIN; tail++;
                    } else {
                        out_degree[m_prev][c_pos][MOUSE_TURN]--;
                        if (out_degree[m_prev][c_pos][MOUSE_TURN] == 0) {
                            states[m_prev][c_pos][MOUSE_TURN] = CAT_WIN;
                            queue[tail][0] = m_prev; queue[tail][1] = c_pos; queue[tail][2] = MOUSE_TURN; queue[tail][3] = CAT_WIN; tail++;
                        }
                    }
                }
            }
        } else {
            for (int i = 0; i < graphColSize[c_pos]; i++) {
                int c_prev = graph[c_pos][i];
                if (c_prev == 0) continue; 

                if (states[m_pos][c_prev][CAT_TURN] == DRAW) {
                    if (winner == CAT_WIN) {
                        states[m_pos][c_prev][CAT_TURN] = CAT_WIN;
                        queue[tail][0] = m_pos; queue[tail][1] = c_prev; queue[tail][2] = CAT_TURN; queue[tail][3] = CAT_WIN; tail++;
                    } else {
                        out_degree[m_pos][c_prev][CAT_TURN]--;
                        if (out_degree[m_pos][c_prev][CAT_TURN] == 0) {
                            states[m_pos][c_prev][CAT_TURN] = MOUSE_WIN;
                            queue[tail][0] = m_pos; queue[tail][1] = c_prev; queue[tail][2] = CAT_TURN; queue[tail][3] = MOUSE_WIN; tail++;
                        }
                    }
                }
            }
        }
    }

    return states[1][2][MOUSE_TURN];
}