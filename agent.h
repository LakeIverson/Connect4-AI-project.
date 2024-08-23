#ifndef _AGENT_H_
#define _AGENT_H_

#include <vector>
#include "random_agent.h"

class Agent {
public:
    Agent();
    Agent(int two, int three, int four, int one_b, int two_b, int three_b, bool player);
    int agentFunction(std::vector<std::vector<int>>& percepts);
    unsigned int findAction(std::vector<int>& actions);
    int findAction_R(unsigned int action, bool min, int& depth, Model model, int alpha, int beta);

protected:
    Model mModel;
    int mTwo, mThree, mFour, mOne_b, mTwo_b, mThree_b;
    bool mPlayer; //true = 1, false = 2

};

#endif /* _AGENT_H_ */
