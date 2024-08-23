#ifndef _RANDOM_AGENT_H_
#define _RANDOM_AGENT_H_

#include <vector>
#include "environment.h"

class Model: public Environment {
public:
    Model();
    void updateFromPercepts(std::vector<std::vector<int>>& percepts);
    std::vector<int> getLegalActions();

};

class RandomAgent {
public:
    RandomAgent();
    int agentFunction(std::vector<std::vector<int>>& percepts);

protected:
    Model mModel;

};

#endif /* _RANDOM_AGENT_H_ */
