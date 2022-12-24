//
// Created by David on 25/11/2022.
//

#include "Team.h"
Team::Team(int id, int points):m_id(id),m_points(points), m_playersNum(0), m_strength(points),m_gamesPlayed(0),m_goalKeepersNum(0), m_isOnRanked(false),m_shouldBeDeleted(false)
{

    if(id <= 0 || points <0)
        throw InvalidInput();
    m_playersTree = new AVLTree<int,Player*>();
    m_rankedPlayersTree = new AVLTree<Player,Player*>();
    m_id = id;
    m_points = points;
}

void Team::changeShouldBeDeleted() {m_shouldBeDeleted = true;}
bool Team::isInRanked() const { return m_isOnRanked;}
void Team::setIsInRanked(bool isRanked) {
    m_isOnRanked = isRanked;
}

int Team::getId() const { return m_id;}

Team::~Team() {
    delete m_rankedPlayersTree;
    delete m_playersTree;
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
    m_isOnRanked = true;
    m_playersTree = nullptr;
    m_rankedPlayersTree = nullptr;
}

void Team::resetPlayersCount() {
    m_playersNum = 0;
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
bool Team::canBeDeleted() const { return (m_playersNum == 0 || m_shouldBeDeleted);}

int Team::getPlayersCount() const {
    return m_playersNum;
}
void Team::addPlayer(Player *player) {
    try{
        m_playersTree->insert(player->getId(), player);
        addPlayerToRanked(player);

        if(player->isGoalKeeper())
            m_goalKeepersNum+=1;
        m_playersNum+=1;
        m_strength += player->getGoals() - player->getCards();
    }
    catch(std::logic_error &e){
        throw e;
    }

}

int Team::getGamesPlayed() const {
    return m_gamesPlayed;
}
int Team::getStrength() const{
    return m_strength;
}
TreeNode<Player, Player*>* Team::getRankedTopNode() {
    return m_rankedPlayersTree->getTopNode();
}
void Team::removePlayer(Player *player) {
    if(player->isGoalKeeper())
        m_goalKeepersNum -=1;

    removePlayerFromRanked(player);
    m_playersTree->deleteByKey(player->getId());

    m_playersNum-=1;
    m_strength -= player->getGoals() - player->getCards();
}

void Team::updateStrength(int goals, int cards) {
    m_strength += goals-cards;
}
void Team::removePlayerFromRanked(Player *player) {
    try{
            m_rankedPlayersTree->deleteByKey(*player);
    }
    catch(std::exception &e)
    {
        throw e;
    }
}

void Team::updatePlayersTeam(TreeNode<int, Player*>* currNode) {
    if(currNode == nullptr)
        return;
    updatePlayersTeam(currNode->m_leftSon);
    currNode->m_data->setTeam(this);
    updatePlayersTeam(currNode->m_rightSon);
}

void Team::updateRankedPlayersTeam(TreeNode<Player, Player *> *currNode) {
    if(currNode == nullptr)
        return;
    updateRankedPlayersTeam(currNode->m_leftSon);
    currNode->m_data->setTeam(this);
    updateRankedPlayersTeam(currNode->m_rightSon);
}

Player* Team::getClosestPlayer(int playerId) {
    TreeNode<int,Player*>* playerNode = m_playersTree->find(playerId);
    if(playerNode == nullptr) return nullptr;
    Player* currPlayer = playerNode->m_data;
    TreeNode<Player,Player*>* rankNode = currPlayer->getRankNode();
    Player* closestPlayer = currPlayer->getClosest(rankNode->m_closeAbove,rankNode->m_closeBelow);
    return closestPlayer;
}

void Team::addPlayerToRanked(Player *player) {
    try{
        m_rankedPlayersTree->insert(*player,player);

    }
    catch(std::logic_error &e)
    {
        throw e;
    }
}

//void Team::printTeamPlayers() const {
////    std::cout << "Normal Tree" << std::endl;
////    m_playersTree->printBT();
//    std::cout << "Ranked Tree of team:" << m_id << std::endl;
//    m_rankedPlayersTree->printBT();
//}

void Team::createPlayerTrees(TreeNode<int,Player*>* playersArr[],TreeNode<Player,Player*>* rankedPlayersArr[])
{
    m_playersTree->createTreeFromArray(playersArr, m_playersNum);
    m_rankedPlayersTree->createTreeFromArray(rankedPlayersArr, m_playersNum);
//    m_playersTree->printBT();
//    m_rankedPlayersTree->printBT();
    updatePlayersTeam(m_playersTree->getRoot());
    updateRankedPlayersTeam(m_rankedPlayersTree->getRoot());
}
void Team::getSortedPlayersArray(TreeNode<int,Player*> **playerNodes, TreeNode<Player,Player*> **rankedPlayerNodes) {
    m_playersTree->treeToArray(playerNodes);
    m_rankedPlayersTree->treeToArray(rankedPlayerNodes);

    // Update player's games played here:
    for(int i=0;i<m_playersNum;i++)
    {
        playerNodes[i]->m_data->updateGamesPlayedByFactor(-m_gamesPlayed);
    }
}

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