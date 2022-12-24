#include "Player.h"
#include "iostream"
Player::Player(int playerId, int teamId, int gamesPlayed, int goals, int cardsReceived, bool isGoalKeeper):
    m_id(playerId), m_teamId(teamId), m_team(nullptr), m_gamesPlayed(gamesPlayed), m_goals(goals), m_cardsReceived(cardsReceived), m_isGoalKeeper(isGoalKeeper)
{
    // Check for valid inputs
    if(playerId <=0 || teamId <=0 || gamesPlayed < 0 || goals < 0 || cardsReceived < 0)
    {
        throw InvalidInput();
    }

    if(gamesPlayed == 0 && (goals > 0 || cardsReceived > 0))
        throw InvalidInput();
}


bool Player::isGoalKeeper() const {
    return m_isGoalKeeper;
}
int Player::getId() const{
    return m_id;
}

int Player::getGoals() const {
    return m_goals;
}

int Player::getCards() const {
    return m_cardsReceived;
}

void Player::updateGamesPlayedByFactor(int factor) {
    m_gamesPlayed -= factor;
}

int absDiff(int val1, int val2)
{
    return (val1 < val2) ? val2-val1 : val1-val2;
}

bool operator>(const Player& p1, const Player& p2)
{
    if(p1.m_goals != p2.m_goals)
    {
        return p1.m_goals > p2.m_goals;
    }
    else{
        if(p1.m_cardsReceived != p2.m_cardsReceived)
            return p1.m_cardsReceived < p2.m_cardsReceived;
        else
        {
            return p1.m_id > p2.m_id;
        }
    }
}

bool operator==(const Player& p1, const Player& p2)
{
    return (p1.m_goals == p2.m_goals && p1.m_cardsReceived == p2.m_cardsReceived &&
        p1.m_id == p2.m_id);
}

bool operator!=(const Player& p1, const Player& p2)
{
    return !(p1 == p2);
}

bool operator<(const Player& p1, const Player&p2)
{
    return !(p1 > p2) && !(p1 == p2);
}

int Player::getGamesPlayed() const{
    return m_gamesPlayed;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os<< "PLAYER: ID:" << player.m_id << " | Goals: " << player.m_goals << " | Cards: " << player.m_cardsReceived;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Player* player)
{
    os<< "PLAYER: ID:" << player->m_id << " | Goals: " << player->m_goals << " | Cards: " << player->m_cardsReceived;
    return os;
}