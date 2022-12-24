#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H
#include "exception"
#include "ostream"
#include "Exception.h"
#include "TreeNode.h"
class Team;
class Player {
    int m_id;
    int m_teamId;
    Team* m_team;

    int m_gamesPlayed;
    int m_goals;
    int m_cardsReceived;
    bool m_isGoalKeeper;

    friend bool operator>(const Player& p1, const Player& p2);
    friend bool operator==(const Player& p1, const Player& p2);

    friend std::ostream& operator<<(std::ostream& os,const Player& player);
    friend std::ostream& operator<<(std::ostream& os,const Player* player);
public:
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cardsReceived, bool isGoalKeeper);
    Player() = default;
    ~Player() = default;

    int getGamesPlayed() const;
    void updateGamesPlayedByFactor(int factor);

    int getGoals() const;
    int getCards() const;

    int getId() const;
    bool isGoalKeeper() const;
};

bool operator>(const Player& p1, const Player& p2);
bool operator<(const Player& p1, const Player& p2);
bool operator==(const Player& p1, const Player& p2);
bool operator!=(const Player& p1, const Player& p2);
#endif //EX1_PLAYER_H
