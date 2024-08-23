## CS4300 - Adversarial Environment - Lake Iverson

**Legal Moves**
Legal moves are defined as any column in which a player or agent can place a piece. I represent the legal moves using a `std::vector<int>` which looks like `[0,1,2,3,4,5,6]`.

**Performance Measure**
The performance measure calculates who wins more games. It keeps track of player 1 wins, player 2 wins, and draw games. The favored agent is the one who has the most wins after 1000 simulations.

**Evaluation Function**
For heuristic function the agent will look at the state of the board and calculate a score based on tokens that are placed in a row. Therefore, if a state places a token to achieve a 3 in a row, that is favored over one that places a token randomly.

The values of these boards will be calculated using the following scores:
*o represents the agent, x represents the adversary.*
```
oooo ~ +2000
ooo. ~ +10
oo.. ~ +1
xx.. ~ -1
xxx. ~ -10
xxxx ~ -2000
```
There are also special cases with differing points.
```
xxxo ~ +100
xxo. ~ +20
xo.. ~ +2
ox.. ~ -2
oox. ~ -20
ooox ~ -100
```
By doing this the agent will be rewarded more for stopping a potential win rather than going for it's own goals. The absurdly high points for winning also makes sure the agent takes this path no matter what. Likewise the extremely large penalty for losing, as well as some bonus points for stopping the adversary from winning will also make sure the agent doesn't allow the adversary any ground to win.
