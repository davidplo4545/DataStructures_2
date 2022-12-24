//
// Created by David on 25/11/2022.
//

#ifndef EX1_TEAM_H
#define EX1_TEAM_H
#include "AVLTree.h"
#include "wet2util.h"
#include "Player.h"
#include "Exception.h"

class Player;
class Team {
    static const int MIN_VALID_SIZE = 11;
    int m_id, m_points;
    int m_playersNum;
    int m_strength; // points + sum of (goals - cards) of each player
    int m_gamesPlayed = 0;
    int m_goalKeepersNum;
    bool m_isInSystem;

    friend bool operator>(const Team& p1, const Team& p2);
    friend bool operator==(const Team& p1, const Team& p2);

    friend std::ostream& operator<<(std::ostream& os,const Team& team);


public:
    Team(int id, int points);
    Team() = default;
    ~Team();
    Team& operator=(const Team& team);
    Team(const Team& team);

    bool isInSystem() const;
    void setIsInSystem(bool isRanked);
    int getId() const;
    int getPoints() const;
    void updatePointsAfterGame(int value);
    int getStrength() const;
    void updateStatsFromTeams(Team* t1, Team* t2);
    void updateStrength(int goals, int cards);

    int getPlayersCount() const;
    bool isAbleToPlay() const;
    int getGamesPlayed() const;

    Team* playMatch(Team *rival);

    void printTeamPlayers() const;

};

bool operator>(const Team& p1, const Team& p2);
bool operator<(const Team& p1, const Team& p2);
bool operator==(const Team& p1, const Team& p2);
bool operator!=(const Team& p1, const Team& p2);


#endif //EX1_TEAM_H
