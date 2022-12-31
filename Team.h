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
    void increasePlayerCount(int num=1);
    bool isInSystem() const;
    void changeSystemState();
    int getId() const;
    void updatePoints(int value);
    void updateTotalAbility(int value);
    void updateTeamSpirit(permutation_t playerSpirit);
    void increaseGoalKeepers(int num);
    void updateStatsFromOtherTeam(Team* other);

    void raiseAbility(int ability);

    int getStrength() const;
    int getPoints() const;
    int getPlayersCount() const;
    bool isAbleToPlay() const;

    int getGamesPlayed() const;
    void setGamesPlayed(int value);

    int getTotalAbility() const;
    int getGoalKeepers() const;

    permutation_t getTeamSpirit() const;
    int playMatch(Team *rival);

};

bool operator>(const Team& p1, const Team& p2);
bool operator<(const Team& p1, const Team& p2);
bool operator==(const Team& p1, const Team& p2);
bool operator!=(const Team& p1, const Team& p2);


#endif //EX1_TEAM_H
