#include "Player.h"
#include "iostream"
Player::Player(int playerId, permutation_t spirit ,int gamesPlayed, int ability, int cardsReceived, bool isGoalKeeper):
    m_id(playerId), m_spirit(spirit), m_gamesPlayed(gamesPlayed), m_ability(ability), m_cardsReceived(cardsReceived), m_isGoalKeeper(isGoalKeeper)
{
    // Check for valid inputs
//    if(playerId <=0 || teamId <=0 || gamesPlayed < 0 || goals < 0 || cardsReceived < 0)
//    {
//        throw InvalidInput();
//    }
//
//    if(gamesPlayed == 0 && (goals > 0 || cardsReceived > 0))
//        throw InvalidInput();
}

int Player::getId() const{
    return m_id;
}

permutation_t Player::getSpirit() const { return m_spirit;}

int Player::getGamesPlayed() const{
    return m_gamesPlayed;
}

int Player::getAbility() const {
    return m_ability;
}

int Player::getCards() const {
    return m_cardsReceived;
}

bool Player::isGoalKeeper() const {
    return m_isGoalKeeper;
}

void Player::updateGamesPlayedByFactor(int factor) {
    m_gamesPlayed -= factor;
}

int absDiff(int val1, int val2)
{
    return (val1 < val2) ? val2-val1 : val1-val2;
}



std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os<< "PLAYER: ID:" << player.m_id << " | Ability: " << player.m_ability << " | Cards: " << player.m_cardsReceived;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Player* player)
{
    os<< "PLAYER: ID:" << player->m_id << " | Goals: " << player->m_ability << " | Cards: " << player->m_cardsReceived;
    return os;
}