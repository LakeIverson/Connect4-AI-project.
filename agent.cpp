#include <vector>
#include <cstdlib>
#include <ctime>
#include "agent.h"
#include "random_agent.h"

#include <iostream>

Agent::Agent() 
    : mModel(Model()), mTwo(1), mThree(10), mFour(2000), mOne_b(2), mTwo_b(20), mThree_b(100), mPlayer(true) {}

Agent::Agent(int two, int three, int four, int one_b, int two_b, int three_b, bool player) 
    : mModel(Model()), mTwo(two), mThree(three), mFour(four), mOne_b(one_b), mTwo_b(two_b), mThree_b(three_b), mPlayer(player) { }

unsigned int Agent::findAction(std::vector<int>& actions) {
    unsigned int i;
    unsigned int action;
    int depth = 0;
    int test_value;
    int best = -10000;
    std::vector<int> possible_choices;
    for (i = 0; i < actions.size(); i++) {
        test_value = findAction_R(i, false, depth, mModel, -10000, 10000);
        if (test_value > best) {
            best = test_value;
            possible_choices.clear();
            action = i;
        } else if (test_value == best) {
            possible_choices.push_back(i);
        }
    }
    if (possible_choices.size() > 0) {
        unsigned int random_action = rand() % possible_choices.size();
        action = possible_choices[random_action]; 
    }

    return action;
}

int Agent::findAction_R(unsigned int action, bool min, int& depth, Model model, int alpha, int beta) {
    depth++;
    model.applyAction(action);
    int a, b, best;
    if (min) {
        best = 10000;
    } else {
        best = -10000;
    }
    if (depth >= 20) {
        if (mPlayer) {
            depth -= 1;
            return model.calculateState(mTwo, mThree, mFour, mOne_b, mTwo_b, mThree_b);
        } else {
            depth -= 1;
            return model.calculateState(mTwo, mThree, mFour, mOne_b, mTwo_b, mThree_b) * -1;
        }
    }
    if (min) {
        if (beta < model.calculateState(mTwo, mThree, mFour, mOne_b, mTwo_b, mThree_b)) {
            return model.calculateState(mTwo, mThree, mFour, mOne_b, mTwo_b, mThree_b);
        }
        a = model.calculateState(mTwo, mThree, mFour, mOne_b, mTwo_b, mThree_b);
        b = beta;
    } else {
        if (alpha > model.calculateState(mTwo, mThree, mFour, mOne_b, mTwo_b, mThree_b)) {
            return model.calculateState(mTwo, mThree, mFour, mOne_b, mTwo_b, mThree_b);
        }
        a = alpha;
        b = model.calculateState(mTwo, mThree, mFour, mOne_b, mTwo_b, mThree_b);
    }

    unsigned int i;
    for (i = 0; i < 7; i++) {
        
        if (min) {
            if (findAction_R(i, !min, depth, model, a, b) < best) {
                best = findAction_R(i, min, depth, model, a, b);
            }
        } else {
            if (findAction_R(i, !min, depth, model, a, b) > best) {
                best = findAction_R(i, min, depth, model, a, b);
            }
        }
    }
    depth -= 1;
    return best;
}

int Agent::agentFunction(std::vector<std::vector<int>>& percepts) {
    mModel.updateFromPercepts(percepts);
    std::vector<int> actions = mModel.getLegalActions();

    unsigned int action = findAction(actions); 

    return actions[action];
}
