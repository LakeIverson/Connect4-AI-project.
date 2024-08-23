#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <vector>

class Environment {
public:
    Environment();
    void applyAction(const int& action);
    void updateTurn();
    void resetBoard();
    int calculateState(const int& two, const int& three, const int& four, const int& one_b, const int& two_b, const int& three_b);
    int checkWin();
    std::vector<std::vector<int>>& getObservablePercepts();
    bool done();

protected:
    std::vector<std::vector<int>> mBoard;
    int mTurn;

};

#endif /* _ENVIRONMENT_H_ */
