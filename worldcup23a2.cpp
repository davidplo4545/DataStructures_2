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
    Team* team;

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
        m_teamsNum -=1;
        if(team->getPlayersCount() == 0)
        {
            delete team;
        }
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    if(playerId <=0 || teamId <=0 || !(spirit.isvalid()) || gamesPlayed < 0 || cards < 0)
        return StatusType::INVALID_INPUT;

    // Check if team exists
    TreeNode<int, Team*>* teamNode = m_idTeamsTree->find(teamId);
    if(teamNode == nullptr)
        return StatusType::FAILURE;

    Team* team = teamNode->m_data;
    Player* player = new Player(playerId, spirit, gamesPlayed, ability, cards, goalKeeper);
    // Check if player exists
    try{
        m_playersUF->insertPlayer(player, teamNode->m_data);
    }
    catch(FailureError &e)
    {
        return StatusType::FAILURE;
    }
    // Remove team from the ability sorted tree and
    // insert it again to its new location
    m_abilityTeamsTree->deleteByKey(*team);
    team->raiseAbility(ability);
    m_abilityTeamsTree->insert(*team, team);
    
    team->updateTeamSpirit(spirit);

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;
    TreeNode<int, Team*>*  teamNode1= m_idTeamsTree->find(teamId1);
    TreeNode<int, Team*>*  teamNode2= m_idTeamsTree->find(teamId2);
    if(!teamNode1 || !teamNode2) return StatusType::FAILURE;
    Team* team1 = teamNode1->m_data;
    Team* team2 = teamNode2->m_data;
    if(!team1->isAbleToPlay() || !team2->isAbleToPlay()) return StatusType::FAILURE;

    int result = team1->playMatch(team2);

	return output_t<int>(result);
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if(playerId <=0) return output_t<int>(StatusType::INVALID_INPUT);

    int gamesPlayed;
    try{
        gamesPlayed = m_playersUF->calculateGamesPlayed(playerId);
    }
    catch(FailureError &e)
    {
        return output_t<int>(StatusType::FAILURE);
    }

	return output_t<int>(gamesPlayed);
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	if(playerId <=0 || cards <0) return StatusType::INVALID_INPUT;

    // Check if players exists/ team is still in system
    UnionNode* teamUniNode = m_playersUF->find(playerId);
    if(teamUniNode == nullptr || !(teamUniNode->m_team->isInSystem())) return StatusType::FAILURE;

    HashTable* table = m_playersUF->getTable();
    HashNode * hs = table->find(playerId);

    Player* pl = hs->m_player;
    pl->addCards(cards);

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
    if(teamNode == nullptr)
    {
        return StatusType::FAILURE;
    }
    else
    {
        Team* team = teamNode->m_data;
        return output_t<int>(team->getPoints());
    }
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if(i < 0 || i>=m_teamsNum) return output_t<int>(StatusType::INVALID_INPUT);
	// use select from ability tree and return the id
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if(playerId <=0) return output_t<permutation_t>(StatusType::INVALID_INPUT);
    // Check if players exists/ team is still in system
    UnionNode* teamUniNode = m_playersUF->find(playerId);
    if(teamUniNode == nullptr || !(teamUniNode->m_team->isInSystem())) return StatusType::FAILURE;

    // TODO: call calculatePartialSpirit

	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) return StatusType::INVALID_INPUT;

    // check if both teams exist
    TreeNode<int, Team*>*  teamNode1= m_idTeamsTree->find(teamId1);
    TreeNode<int, Team*>*  teamNode2= m_idTeamsTree->find(teamId2);
    if(!teamNode1 || !teamNode2) return StatusType::FAILURE;
    Team* team1 = teamNode1->m_data;
    Team* team2 = teamNode2->m_data;

    m_playersUF->buyTeam(team1,team2);

    // remove the "Buyer" team and insert it back with the
    // new calculated total ability
    m_abilityTeamsTree->deleteByKey(*team1);
    team1->updateStatsFromOtherTeam(team2);
    m_abilityTeamsTree->insert(*team1, team1);

    // Remove the second team
    m_idTeamsTree->deleteByKey(team2->getId());
    m_abilityTeamsTree->deleteByKey(*team2);

    m_teamsNum -=1;
    m_playersUF->print();
	return StatusType::SUCCESS;
}
