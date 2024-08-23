#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "environment.h"
#include "random_agent.h"
#include "agent.h"

void clearBoard() {
    int i;
    for (i = 0; i < 5; i++) {
        std::cout << std::endl;
    }
}

void displayBoard(Environment& env) {
    std::vector<std::vector<int>> board;
    board = env.getObservablePercepts();
    unsigned int row, column;
    for (column = 6; column > 0; column--) {
        for (row = 0; row < 7; row++) {
            if (board[row][column-1] == 0) {
                std::cout << ".";
            } else {
                std::cout << board[row][column-1];
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    } 
}

void displayWinner(Environment& env) {
    int winner = env.checkWin();
    if (winner == 0) {
        std::cout << "Draw." << std::endl;
    } else {
        std::cout << "Player " << winner << " wins!" << std::endl;
    }
}

void playGame(Environment& env, Agent& agent_1, Agent& agent_2, bool display_boards) {
    std::vector<std::vector<int>> percepts;
    int action;

    while (!env.done()) {
        if (display_boards) {
            clearBoard();
        }

        percepts = env.getObservablePercepts();
        action = agent_1.agentFunction(percepts);
        env.applyAction(action);

        if (display_boards) {
            displayBoard(env);
            std::cout << std::endl;
            std::cout << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if (env.done()) {
            break;
        }
    
        if (display_boards) {
            clearBoard();
        }

        percepts = env.getObservablePercepts();
        action = agent_2.agentFunction(percepts);
        env.applyAction(action);

        if (display_boards) {
            displayBoard(env);
            std::cout << std::endl;
            std::cout << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    displayWinner(env);

}

void performanceMeasure(Environment& env, Agent& agent_1, Agent& agent_2, int games) {
    int draws = 0, player_1_wins = 0, player_2_wins = 0;
    for (int i = 0; i < games; i++) {
        playGame(env, agent_1, agent_2, false);
        std::cout << "Game " << i << ": ";
        if (env.checkWin() == 0) {
            draws++;
        } else if (env.checkWin() == 1) {
            player_1_wins++;
        } else if (env.checkWin() == 2) {
            player_2_wins++;
        }
        env.resetBoard();
    }   
    std::cout << "Player 1 won: " << player_1_wins << " and Player 2 won: " << player_2_wins << " of " << games << " games. They drawed: " << draws;
    if (draws == 1) {
        std::cout << " time." << std::endl;
    } else {
        std::cout << " times." << std::endl;
    }
}

int main() {
    srand(time(0));
    Environment env;
    Agent agent_1(1, 10, 2000, 2, 20, 100, true);
    Agent agent_2(2, 20, 2000, 2, 20, 100, true);

    //playGame(env, agent_1, agent_2, true); 
    performanceMeasure(env, agent_1, agent_2, 1000);

    return 0;
}
