#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H
#include "exception"
#include "ostream"
#include "Exception.h"
#include "TreeNode.h"
#include "wet2util.h"
class Team;
class Player {
    int m_id;
    permutation_t m_spirit;
    int m_gamesPlayed;
    int m_ability;
    int m_cardsReceived;
    bool m_isGoalKeeper;

    friend std::ostream& operator<<(std::ostream& os,const Player& player);
    friend std::ostream& operator<<(std::ostream& os,const Player* player);
public:
    Player(int playerId, permutation_t spirit, int gamesPlayed, int ability, int cardsReceived, bool isGoalKeeper);
    Player() = default;
    ~Player() = default;

    void updateGamesPlayedByFactor(int factor);

    int getId() const;
    permutation_t getSpirit() const;
    int getGamesPlayed() const;
    int getAbility() const;
    int getCards() const;

    bool isGoalKeeper() const;
};

#endif //EX1_PLAYER_H
