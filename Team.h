//
// Created by David on 25/11/2022.
//

#ifndef EX1_TEAM_H
#define EX1_TEAM_H
#include "AVLTree.h"
#include "wet2util.h"
#include "Player.h"
#include "Exception.h"
#include "UnionNode.h"
struct UnionNode;
class Player;
class Team {
    int m_id, m_points;
    permutation_t m_teamSpirit;
    int m_playersNum;
    int m_totalAbility;
    int m_gamesPlayed = 0;
    int m_goalKeepersNum;
    bool m_isInSystem;
    UnionNode* m_rootUniNode;

    friend bool operator>(const Team& p1, const Team& p2);
    friend bool operator==(const Team& p1, const Team& p2);

    friend std::ostream& operator<<(std::ostream& os,const Team& team);


public:
    Team(int id);
    Team() = default;
    ~Team();

    Team(const Team& team);

    UnionNode* getRootUnionNode();
    void setRootUnionNode(UnionNode* uniNode);
    void increasePlayerCount();
    bool isInSystem() const;
    void changeSystemState();
    int getId() const;
    int getPoints() const;
    void updatePointsAfterGame(int value);
    int getStrength() const;
    void updateStatsFromTeams(Team* t1, Team* t2);
    void raiseAbility(int ability);

    int getPlayersCount() const;
    bool isAbleToPlay() const;
    int getGamesPlayed() const;

    Team* playMatch(Team *rival);

};

bool operator>(const Team& p1, const Team& p2);
bool operator<(const Team& p1, const Team& p2);
bool operator==(const Team& p1, const Team& p2);
bool operator!=(const Team& p1, const Team& p2);


#endif //EX1_TEAM_H
