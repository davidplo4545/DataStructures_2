#include "Player.h"
#include "iostream"
Player::Player(int playerId, int teamId, int gamesPlayed, int goals, int cardsReceived, bool isGoalKeeper):
    m_id(playerId), m_teamId(teamId), m_team(nullptr), m_gamesPlayed(gamesPlayed), m_goals(goals), m_cardsReceived(cardsReceived), m_isGoalKeeper(isGoalKeeper), m_rankNode(nullptr)
{
    // Check for valid inputs
    if(playerId <=0 || teamId <=0 || gamesPlayed < 0 || goals < 0 || cardsReceived < 0)
    {
        throw InvalidInput();
    }

    if(gamesPlayed == 0 && (goals > 0 || cardsReceived > 0))
        throw InvalidInput();
}

void Player::setRankNode(TreeNode<Player, Player *> *rankNode) {
    m_rankNode = rankNode;
}

TreeNode<Player,Player*>* Player::getRankNode() {
    return m_rankNode;
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
Player* Player::getClosest(TreeNode<Player,Player*>* plNode1, TreeNode<Player,Player*>* plNode2) const
{
    if(plNode1 == nullptr && plNode2 == nullptr)
        return nullptr;
    if(plNode1 == nullptr && plNode2 != nullptr)
        return plNode2->m_data;
    if(plNode1 != nullptr && plNode2 == nullptr)
        return plNode1->m_data;

    Player* pl1 = plNode1->m_data;
    Player* pl2 = plNode2->m_data;
    if(absDiff(pl2->m_goals,m_goals) != absDiff(pl1->m_goals,m_goals) )
    {
        if(absDiff(pl2->m_goals,m_goals) > absDiff(pl1->m_goals,m_goals))
            return pl1;
        else
            return pl2;
    }
    else if(absDiff(pl2->m_cardsReceived,m_cardsReceived) != absDiff(pl1->m_cardsReceived,m_cardsReceived))
    {
        if(absDiff(pl2->m_cardsReceived,m_cardsReceived) > absDiff(pl1->m_cardsReceived,m_cardsReceived))
            return pl1;
        else
            return pl2;
    }
    else if(absDiff(pl2->m_id,m_id) != absDiff(pl1->m_id,m_id))
    {
        if(absDiff(pl2->m_id,m_id) > absDiff(pl1->m_id,m_id))
            return pl1;
        else
            return pl2;
    }
    return (pl2->m_id > pl1->m_id) ? pl2 : pl1;
}
void Player::updateStats(int gamesPlayed, int scoredGoals, int cardsReceived){
    m_gamesPlayed += gamesPlayed;
    m_goals += scoredGoals;
    m_cardsReceived += cardsReceived;
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

Team* Player::getTeam() {
    return m_team;
}

void Player::setTeam(Team* team)
{
    m_team = team;
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