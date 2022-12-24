//
// Created by David on 25/11/2022.
//

#include "Team.h"
Team::Team(int id, int points):m_id(id),m_points(points), m_playersNum(0), m_strength(points),m_gamesPlayed(0),m_goalKeepersNum(0), m_isInSystem(true)
{

    if(id <= 0 || points <0)
        throw InvalidInput();
    m_id = id;
    m_points = points;
}

bool Team::isInSystem() const {return m_isInSystem;}
void Team::setIsInSystem(bool isInSystem) {
    m_isInSystem = isInSystem;
}

int Team::getId() const { return m_id;}

Team::~Team() {
}
Team* Team::playMatch(Team* rival) {
    if(m_strength > rival->getStrength())
    {
        updateStrength(rival->getStrength()+3,0);
        return this;
    }
    else if (m_strength < rival->getStrength())
    {
        rival->updateStrength(m_strength+3,0);
        return rival;
    }
    else{
        if(m_id > rival->getId())
        {
            updateStrength(rival->getStrength()+3,0);
            return this;
        }
        else
        {
            rival->updateStrength(m_strength+3,0);
            return rival;
        }
    }
}

Team::Team(const Team& team)
{
    m_strength = team.m_strength;
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


bool Team::isAbleToPlay() const { return m_playersNum >= MIN_VALID_SIZE && m_goalKeepersNum > 0;}
int Team::getPoints() const { return m_points;}
void Team::updatePointsAfterGame(int value) {
    m_points += value;
    m_strength += value;
    m_gamesPlayed +=1;
}

void Team::updateStatsFromTeams(Team *t1, Team *t2) {
    m_strength = t1->m_strength + t2->m_strength;
    m_points = t1->m_points + t2->m_points;
    m_playersNum = t1->m_playersNum + t2->m_playersNum;
    m_goalKeepersNum = t1->m_goalKeepersNum + t2->m_goalKeepersNum;
    m_gamesPlayed = 0;
}

int Team::getPlayersCount() const {
    return m_playersNum;
}


int Team::getGamesPlayed() const {
    return m_gamesPlayed;
}
int Team::getStrength() const{
    return m_strength;
}


void Team::updateStrength(int goals, int cards) {
    m_strength += goals-cards;
}




//void Team::printTeamPlayers() const {
////    std::cout << "Normal Tree" << std::endl;
////    m_playersTree->printBT();
//    std::cout << "Ranked Tree of team:" << m_id << std::endl;
//    m_rankedPlayersTree->printBT();
//}


bool operator>(const Team& t1, const Team& t2)
{
    return t1.m_id > t2.m_id;
}

bool operator==(const Team& t1, const Team& t2)
{
    return t1.m_id == t2.m_id;
}

bool operator!=(const Team& t1, const Team& t2)
{
    return !(t1 == t2);
}

bool operator<(const Team& t1, const Team&t2)
{
    return !(t1 > t2) && !(t1 == t2);
}