#include <vector>
#include <cstdlib>
#include <ctime>
#include "random_agent.h"

Model::Model() 
    : Environment() { }

void Model::updateFromPercepts(std::vector<std::vector<int>>& percepts) {
    unsigned int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            mBoard[i][j] = percepts[i][j];
        }
    }
}

std::vector<int> Model::getLegalActions() {
    std::vector<int> actions;
    unsigned int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            if (mBoard[i][j] == 0) {
                actions.push_back(i);
                break;
            }
        }
    }
    return actions;
}

RandomAgent::RandomAgent() 
    : mModel(Model()) { 
        srand(time(0));
    }

int RandomAgent::agentFunction(std::vector<std::vector<int>>& percepts) {
    mModel.updateFromPercepts(percepts);
    std::vector<int> actions = mModel.getLegalActions();
    unsigned int random_action = rand() % actions.size();
    return actions[random_action];
}
