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
    TreeNode<Player,Player*>* m_rankNode;


    friend bool operator>(const Player& p1, const Player& p2);
    friend bool operator==(const Player& p1, const Player& p2);

    friend std::ostream& operator<<(std::ostream& os,const Player& player);
    friend std::ostream& operator<<(std::ostream& os,const Player* player);
public:
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cardsReceived, bool isGoalKeeper);
    Player() = default;
    ~Player() = default;

    void updateStats(int gamesPlayed, int scoredGoals, int cardsReceived);
    int getGamesPlayed() const;
    void updateGamesPlayedByFactor(int factor);

    int getGoals() const;
    int getCards() const;
    TreeNode<Player,Player*>* getRankNode();
    void setRankNode(TreeNode<Player,Player*>* rankNode);

    Player* getClosest(TreeNode<Player,Player*>* plNode1, TreeNode<Player,Player*>* plNode2) const;
    int getId() const;
    void setTeam(Team* team);
    Team* getTeam();
    bool isGoalKeeper() const;
};

bool operator>(const Player& p1, const Player& p2);
bool operator<(const Player& p1, const Player& p2);
bool operator==(const Player& p1, const Player& p2);
bool operator!=(const Player& p1, const Player& p2);
#endif //EX1_PLAYER_H
