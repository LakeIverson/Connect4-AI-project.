#include <vector>
#include "environment.h"

Environment::Environment() 
    : mBoard({{},{},{},{},{},{},{}}), mTurn(1) {
    unsigned int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            mBoard[i].push_back(0);
        } 
    }
}

void Environment::applyAction(const int& action) {
    unsigned int i;
    for (i = 0; i < 6; i++) {
        if (mBoard[action][i] == 0) {
            mBoard[action][i] = mTurn; 
            break;
        }
    }
    updateTurn(); 
}

void Environment::updateTurn() {
    if (mTurn == 1) {
        mTurn = 2;
    } else {
        mTurn = 1;
    }
}

void Environment::resetBoard() {
    unsigned int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            mBoard[i][j] = 0;
        }
    }
}

int Environment::calculateState(const int& two, const int& three, const int& four, const int& one_b, const int& two_b, const int& three_b) {
    int score = 0;
    bool player;
    unsigned int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            if (mBoard[i][j] != 0) {
                // Figuring Out Token ~ True: 1, False: 2 //
                if (mBoard[i][j] == 1) {
                    player = true; 
                } else {
                    player = false;
                }

                // Common Cases (Without Influence from Adversary; i.e: oo.. ooo. oooo) //
                // Vertical //
                if (j <= 4) {
                    if (mBoard[i][j] == mBoard[i][j+1]) {
                        if (player) {
                            score += two;
                        } else {
                            score -= two;
                        }
                        if (j <= 3) {
                            if (mBoard[i][j+1] == mBoard[i][j+2]) {
                                if (player) {
                                    score += three - two; 
                                } else {
                                    score -= three - two;
                                } 
                                if (j <= 2) {
                                    if (mBoard[i][j+2] == mBoard[i][j+3]) {
                                        if (player) {
                                            score += four - three - two;
                                        } else {
                                            score -= four - three - two;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // Diagonal-Right //
                if (i <= 5 && j <= 4) {
                    if (mBoard[i][j] == mBoard[i+1][j+1]) {
                        if (player) {
                            score += two;
                        } else {
                            score -= two;
                        }
                        if (i <= 4 && j <= 3) {
                            if (mBoard[i+1][j+1] == mBoard[i+2][j+2]) {
                                if (player) {
                                    score += three - two;
                                } else {
                                    score -= three - two;
                                } 
                                if (i <= 3 && j <= 2) {
                                    if (mBoard[i+2][j+2] == mBoard[i+3][j+3]) {
                                        if (player) {
                                            score += four - three - two;
                                        } else {
                                            score -= four - three - two;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // Horizontal //
                if (i <= 5) {
                    if (mBoard[i][j] == mBoard[i+1][j]) {
                        if (player) {
                            score += two;
                        } else {
                            score -= two;
                        }
                        if (i <= 4) {
                            if (mBoard[i+1][j] == mBoard[i+2][j]) {
                                if (player) {
                                    score += three - two;
                                } else {
                                    score -= three - two;
                                } 
                                if (i <= 3) {
                                    if (mBoard[i+2][j] == mBoard[i+3][j]) {
                                        if (player) {
                                            score += four - three - two;
                                        } else {
                                            score -= four - three - two;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // Diagonal-Left //
                if (i > 0 && j <= 4) {
                    if (mBoard[i][j] == mBoard[i-1][j+1]) {
                        if (player) {
                            score += two;
                        } else {
                            score -= two;
                        }
                        if (i > 1 && j <= 3) {
                            if (mBoard[i-1][j+1] == mBoard[i-2][j+2]) {
                                if (player) {
                                    score += three - two;
                                } else {
                                    score -= three - two;
                                } 
                                if (i > 2 && j <= 2) {
                                    if (mBoard[i-2][j+2] == mBoard[i-3][j+3]) {
                                        if (player) {
                                            score += four - three - two;
                                        } else {
                                            score -= four - three - two;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // Special Cases, i.e: ox.. oox. ooox //
                // Vertical //
                if (j <= 4) {
                    if (mBoard[i][j] != mBoard[i][j+1] && mBoard[i][j+1] != 0) { // ox??
                        if (player) {
                            score -= one_b;
                        } else {
                            score += one_b;
                        }
                        if (j <= 3) {
                            if (mBoard[i][j] == mBoard[i][j+2]) { // oxo?
                                if (player) {
                                    score -= two_b - one_b;
                                } else {
                                    score += two_b - one_b;
                                }
                                if (j <= 2)  {
                                    if (mBoard[i][j] == mBoard[i][j+3]) { // oxoo
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            }
                        } 
                    } else if (mBoard[i][j] == mBoard[i][j+1]) {
                        if (j <= 3) {
                            if (mBoard[i][j] != mBoard[i][j+2] && mBoard[i][j+2] != 0) { // oox?
                                if (player) {
                                    score -= two_b - one_b;
                                } else {
                                    score += two_b - one_b;
                                }
                                if (j <= 2) {
                                    if (mBoard[i][j] == mBoard[i][j+3]) { // ooxo
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            } else if (mBoard[i][j] == mBoard[i][j+2]) {
                                if (j <= 2) {
                                    if (mBoard[i][j] != mBoard[i][j+3] && mBoard[i][j+3] != 0) { // ooox
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                
                // Diagonal-Right //
                if (i <= 5 && j <= 4) {
                    if (mBoard[i][j] != mBoard[i+1][j+1] && mBoard[i+1][j+1] != 0) { // ox??
                        if (player) {
                            score -= one_b;
                        } else {
                            score += one_b;
                        }
                        if (i <= 4 && j <= 3) {
                            if (mBoard[i][j] == mBoard[i+2][j+2]) { // oxo?
                                if (player) {
                                    score -= two_b - one_b;
                                } else {
                                    score += two_b - one_b;
                                }
                                if (i <= 3 && j <= 2)  {
                                    if (mBoard[i][j] == mBoard[i+3][j+3]) { // oxoo
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            }
                        } 
                    } else if (mBoard[i][j] == mBoard[i+1][j+1]) {
                        if (i <= 4 && j <= 3) {
                            if (mBoard[i][j] != mBoard[i+2][j+2] && mBoard[i+2][j+2] != 0) { // oox?
                                if (player) {
                                    score -= two_b - one_b;
                                } else {
                                    score += two_b - one_b;
                                }
                                if (i <= 3 && j <= 2) {
                                    if (mBoard[i][j] == mBoard[i+3][j+3]) { // ooxo
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            } else if (mBoard[i][j] == mBoard[i+2][j+2]) {
                                if (i <= 3 && j <= 2) {
                                    if (mBoard[i][j] != mBoard[i+3][j+3] && mBoard[i+3][j+3] != 0) { // ooox
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // Horizontal //
                if (i <= 5) {
                    if (mBoard[i][j] != mBoard[i+1][j] && mBoard[i+1][j] != 0) { // ox??
                        if (player) {
                            score -= one_b;
                        } else {
                            score += one_b;
                        }
                        if (i <= 4) {
                            if (mBoard[i][j] == mBoard[i+2][j]) { // oxo?
                                if (player) {
                                    score -= two_b - one_b;
                                } else {
                                    score += two_b - one_b;
                                }
                                if (i <= 3)  {
                                    if (mBoard[i][j] == mBoard[i+3][j]) { // oxoo
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            }
                        } 
                    } else if (mBoard[i][j] == mBoard[i+1][j]) {
                        if (i <= 4) {
                            if (mBoard[i][j] != mBoard[i+2][j] && mBoard[i+2][j] != 0) { // oox?
                                if (player) {
                                    score -= two_b - one_b;
                                } else {
                                    score += two_b - one_b;
                                }
                                if (i <= 3) {
                                    if (mBoard[i][j] == mBoard[i+3][j]) { // ooxo
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            } else if (mBoard[i][j] == mBoard[i+2][j]) {
                                if (i <= 3) {
                                    if (mBoard[i][j] != mBoard[i+3][j] && mBoard[i+3][j] != 0) { // ooox
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // Diagonal-Left //
                if (i > 0 && j <= 4) {
                    if (mBoard[i][j] != mBoard[i-1][j+1] && mBoard[i-1][j+1] != 0) { // ox??
                        if (player) {
                            score -= one_b;
                        } else {
                            score += one_b;
                        }
                        if (i > 1 && j <= 3) {
                            if (mBoard[i][j] == mBoard[i-2][j+2]) { // oxo?
                                if (player) {
                                    score -= two_b - one_b;
                                } else {
                                    score += two_b - one_b;
                                }
                                if (i > 2 && j <= 2)  {
                                    if (mBoard[i][j] == mBoard[i-3][j+3]) { // oxoo
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            }
                        } 
                    } else if (mBoard[i][j] == mBoard[i-1][j+1]) {
                        if (i > 1 && j <= 3) {
                            if (mBoard[i][j] != mBoard[i-2][j+2] && mBoard[i-2][j+2] != 0) { // oox?
                                if (player) {
                                    score -= two_b - one_b;
                                } else {
                                    score += two_b - one_b;
                                }
                                if (i > 2 && j <= 2) {
                                    if (mBoard[i][j] == mBoard[i-3][j+3]) { // ooxo
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            } else if (mBoard[i][j] == mBoard[i-2][j+2]) {
                                if (i > 2 && j <= 2) {
                                    if (mBoard[i][j] != mBoard[i-3][j+3] && mBoard[i-3][j+3] != 0) { // ooox
                                        if (player) {
                                            score -= three_b - two_b - one_b;
                                        } else {
                                            score += three_b - two_b - one_b;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
        
            }
        }    
    }    
    return score;
}

int Environment::checkWin() {

    if (calculateState(1, 10, 2000, 2, 20, 100) > 1500) {
        return 1;
    } else if (calculateState(1, 10, 2000, 2, 20, 100) < -1500) {
        return 2;
    } else {
        return 0;
    }

/* Old Function
    unsigned int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            if (mBoard[i][j] != 0) {

                // Vertical //
                if (j <= 2) {
                    if (mBoard[i][j] == mBoard[i][j+1] && mBoard[i][j+1] == mBoard[i][j+2] && mBoard[i][j+2] == mBoard[i][j+3]) {
                        return mBoard[i][j];
                    }
                }

                // Diagonal-Right //
                if (j <= 2 && i <= 3) {
                    if (mBoard[i][j] == mBoard[i+1][j+1] && mBoard[i+1][j+1] == mBoard[i+2][j+2] && mBoard[i+2][j+2] == mBoard[i+3][j+3]) {
                        return mBoard[i][j];
                    }
                }

                // Horizontal //
                if (i <= 3) {
                    if (mBoard[i][j] == mBoard[i+1][j] && mBoard[i+1][j] == mBoard[i+2][j] && mBoard[i+2][j] == mBoard[i+3][j]) {
                        return mBoard[i][j];
                    }
                }

                // Diagonal-Left //
                if (j <= 2 && i > 2) {
                    if (mBoard[i][j] == mBoard[i-1][j+1] && mBoard[i-1][j+1] == mBoard[i-2][j+2] && mBoard[i-2][j+2] == mBoard[i-3][j+3]) {
                        return mBoard[i][j];
                    }
                }

            }       
        }
    }
    return 0;
*/
}

std::vector<std::vector<int>>& Environment::getObservablePercepts() {
    return mBoard;
}

bool Environment::done() {
    if (checkWin() >= 1) {
        return true;
    }

    bool good = false;
    unsigned int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++){
            if (mBoard[i][j] == 0) {
                good = true;
            }
        }
    }
    return !good;
}
