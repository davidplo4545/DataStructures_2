#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
	m_idTeamsTree = new AVLTree<int, Team*>();
    m_abilityTeamsTree = new AVLTree<Team, Team*>();
    m_playersUF = new UnionFind();
    m_teamsNum = 0;
    m_playersNum = 0;
}

world_cup_t::~world_cup_t()
{
	delete m_idTeamsTree;
    delete m_abilityTeamsTree;
    delete m_playersUF;
}

StatusType world_cup_t::add_team(int teamId)
{
    if(teamId <= 0) return StatusType::INVALID_INPUT;
    TreeNode<int, Team*>* teamNode = m_idTeamsTree->find(teamId);
    if(teamNode != nullptr)
        return StatusType::FAILURE;
    try{
        Team* newTeam = new Team(teamId);
        m_idTeamsTree->insert(teamId, newTeam);
        m_abilityTeamsTree->insert(*newTeam, newTeam);
        m_teamsNum +=1;
    }
    catch(std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0) return StatusType::INVALID_INPUT;
    Team* team = nullptr;

    TreeNode<int,Team*>* teamNodeToDelete = m_idTeamsTree->find(teamId);
    if(teamNodeToDelete == nullptr)
    {
        return StatusType::FAILURE;
    }
    else
    {
        team = teamNodeToDelete->m_data;
        team->changeSystemState();
        m_idTeamsTree->deleteByKey(teamId);
        m_abilityTeamsTree->deleteByKey(*team);
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    // TODO: CHECK INVALID INPUT

    //TODO: Check if team exists

    //TODO: Insert player and check if it exists

    //TODO: Update team/player stats: gamesPlayed/teamSpirit
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if(playerId <= 0) return output_t<int>(StatusType::INVALID_INPUT);
    HashTable* table = m_playersUF->getTable();
    HashNode * hs = table->find(playerId);
    if(hs == nullptr) return output_t<int>(StatusType::FAILURE);
    return output_t<int>(hs->m_player->getCards());
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0) return output_t<int>(StatusType::INVALID_INPUT);
    TreeNode<int,Team*>* teamNode = m_idTeamsTree->find(teamId);
    Team* team = nullptr;
    if(teamNode == nullptr)
    {
        return StatusType::FAILURE;
    }
    else
    {
        team = teamNode->m_data;
        return output_t<int>(team->getPoints());
    }
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
