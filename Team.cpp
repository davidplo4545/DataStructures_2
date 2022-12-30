//
// Created by David on 25/11/2022.
//

#include "Team.h"
Team::Team(int id):m_id(id),m_points(0), m_teamSpirit(permutation_t::neutral()), m_playersNum(0), m_totalAbility(0),m_gamesPlayed(0),m_goalKeepersNum(0), m_isInSystem(true), m_rootUniNode(nullptr)
{
    m_id = id;
}

bool Team::isInSystem() const {return m_isInSystem;}
void Team::changeSystemState() {
    m_isInSystem = !m_isInSystem;
}

int Team::getId() const { return m_id;}

void Team::increasePlayerCount(int num) { m_playersNum +=num;}
Team::~Team() {
}

void Team::updateTeamSpirit(permutation_t playerSpirit) {
//    m_teamSpirit
}
int Team::playMatch(Team* rival) {

    m_gamesPlayed +=1;
    rival->m_gamesPlayed +=1;
    if(this->getStrength() > rival->getStrength())
    {
        this->updatePointsAfterGame(3);
        return 1;
    }
    else if (this->getStrength() < rival->getStrength())
    {
        rival->updatePointsAfterGame(3);
        return 3;
    }

    if(m_teamSpirit.strength() > rival->m_teamSpirit.strength())
    {
        this->updatePointsAfterGame(3);
        return 2;
    }
    else if(m_teamSpirit.strength() > rival->m_teamSpirit.strength())
    {
        rival->updatePointsAfterGame(3);
        return 4;
    }

    // ITS A TIE
    this->updatePointsAfterGame(1);
    rival->updatePointsAfterGame(1);
    return 0;
}

Team::Team(const Team& team)
{
//    m_strength = team.m_strength;
    m_id = team.m_id;
    m_playersNum = 0;
    m_gamesPlayed = 0;
    m_goalKeepersNum = 1;
    m_isInSystem = true;
}


std::ostream& operator<<(std::ostream& os, const Team& team)
{
    return os;
}


bool Team::isAbleToPlay() const { return m_goalKeepersNum > 0;}
int Team::getPoints() const { return m_points;}

UnionNode* Team::getRootUnionNode() { return m_rootUniNode;}
void Team::setRootUnionNode(UnionNode *uniNode) {
    m_rootUniNode = uniNode;
}
void Team::updatePointsAfterGame(int value) {
    m_points += value;
}

void Team::increaseGoalKeepers(int num) {
    m_goalKeepersNum += num;
}

void Team::updateStatsFromTeams(Team *t1, Team *t2) {
//    m_strength = t1->m_strength + t2->m_strength;
//    m_points = t1->m_points + t2->m_points;
//    m_playersNum = t1->m_playersNum + t2->m_playersNum;
//    m_goalKeepersNum = t1->m_goalKeepersNum + t2->m_goalKeepersNum;
//    m_gamesPlayed = 0;
}

int Team::getPlayersCount() const {
    return m_playersNum;
}

int Team::getGoalKeepers() const {
    return m_goalKeepersNum;
}

int Team::getGamesPlayed() const {
    return m_gamesPlayed;
}

// Calculated by points + sum of players ability
int Team::getStrength() const{
    return m_points+m_totalAbility;
}


void Team::raiseAbility(int ability) {
    m_totalAbility += ability;
}


bool operator>(const Team& t1, const Team& t2)
{
    if(t1.m_totalAbility != t2.m_totalAbility)
    {
        return t1.m_totalAbility > t2.m_totalAbility;
    }
    else{
        return t1.m_id > t2.m_id;
    }
}

bool operator==(const Team& t1, const Team& t2)
{
    return t1.m_totalAbility == t2.m_totalAbility && (t1.m_id == t2.m_id);
}

bool operator!=(const Team& t1, const Team& t2)
{
    return !(t1 == t2);
}

bool operator<(const Team& t1, const Team&t2)
{
    return !(t1 > t2) && !(t1 == t2);
}