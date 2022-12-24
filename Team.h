//
// Created by David on 25/11/2022.
//

#ifndef EX1_TEAM_H
#define EX1_TEAM_H
#include "AVLTree.h"
#include "wet1util.h"
#include "Player.h"
#include "wet1util.h"
#include "Exception.h"

class Player;
class Team {
    static const int MIN_VALID_SIZE = 11;
    int m_id, m_points;
    int m_playersNum;
    int m_strength; // points + sum of (goals - cards) of each player
    int m_gamesPlayed = 0;
    int m_goalKeepersNum;
    bool m_isOnRanked;
    bool m_shouldBeDeleted;

    AVLTree<int,Player*>* m_playersTree; // Sorted by ids
    AVLTree<Player,Player*>* m_rankedPlayersTree; // Sorted by goals > cards> ids

    friend bool operator>(const Team& p1, const Team& p2);
    friend bool operator==(const Team& p1, const Team& p2);

    friend std::ostream& operator<<(std::ostream& os,const Team& team);

    void updatePlayersTeam(TreeNode<int,Player*>* currNode);
    void updateRankedPlayersTeam(TreeNode<Player,Player*>* currNode);

public:
    Team(int id, int points);
    Team() = default;
    ~Team();
    Team& operator=(const Team& team);
    Team(const Team& team);

    void changeShouldBeDeleted();

    bool isInRanked() const;
    void setIsInRanked(bool isRanked);
    int getId() const;
    void removePlayer(Player *player);
    void removePlayerFromRanked(Player *player);
    void addPlayer(Player *player);
    void addPlayerToRanked(Player *player);
    int getPoints() const;
    void updatePointsAfterGame(int value);
    int getStrength() const;
    void updateStatsFromTeams(Team* t1, Team* t2);
    void updateStrength(int goals, int cards);
    void createPlayerTrees(TreeNode<int,Player*>* playersArr[],TreeNode<Player,Player*>* rankedPlayersArr[]);

    bool canBeDeleted() const;
    Player* getClosestPlayer(int playerId);
    int getPlayersCount() const;
    void resetPlayersCount();
    TreeNode<Player, Player*>* getRankedTopNode();
    bool isAbleToPlay() const;
    int getGamesPlayed() const;

    Team* playMatch(Team *rival);
    void getSortedPlayersArray(TreeNode<int,Player*>* playerNodes[], TreeNode<Player,Player*>* rankedPlayerNodes[]);

    void printTeamPlayers() const;

};

bool operator>(const Team& p1, const Team& p2);
bool operator<(const Team& p1, const Team& p2);
bool operator==(const Team& p1, const Team& p2);
bool operator!=(const Team& p1, const Team& p2);


#endif //EX1_TEAM_H
