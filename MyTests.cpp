//
// Created by David on 25/11/2022.
//
#include "iostream"
#include "Player.h"
#include "worldcup23a2.h"
//#include "wet2util.h"
#include <assert.h>
#define AGREGATE_TEST_RESULT(res, cond) (res) = ((res) && (cond))

namespace MyTests {

    //// ABILITY TREE TESTS
    bool simpleAbilityTest()
    {
        world_cup_t *obj = new world_cup_t();

//        output_t<int> resn1 = obj->get_ith_pointless_ability(0);
//        assert(resn1.status() == StatusType::FAILURE);
        StatusType res = obj->add_team(3);
//        output_t<int> resn = obj->get_ith_pointless_ability(0);
//        assert(resn.status() == StatusType::SUCCESS);
//        assert(resn.ans() == 3);
        res = obj->add_team(10);
        res = obj->add_team(4);
        res = obj->add_team(2);
        res = obj->add_team(5);
        res = obj->add_team(6);
        res = obj->add_team(7);


//        output_t<int> resn2 = obj->get_ith_pointless_ability(1);
//        assert(resn2.status() == StatusType::SUCCESS);
//        assert(resn2.ans() == 4);
//        output_t<int> resn3 = obj->get_ith_pointless_ability(2);
//        assert(resn3.status() == StatusType::SUCCESS);
//        assert(resn3.ans() == 5);
//        output_t<int> resn4 = obj->get_ith_pointless_ability(3);
//        assert(resn4.status() == StatusType::SUCCESS);
//        assert(resn4.ans() == 6);
        delete obj;
        return res == StatusType::SUCCESS;
    }

    //// PLAYER TESTS
    bool simplePlayerInsert() {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(3);
        delete obj;
        return res == StatusType::SUCCESS;
    };

    bool invalidInputPlayerInsert();

    bool failedPlayerInsert();

    //// TEAM AND RANKED TREE TESTS
    bool simpleTeamInsert() {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(3);
        delete obj;
        return res == StatusType::SUCCESS;
    }

    bool invalidTeamInsert()
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(-5);
        delete obj;
        return res == StatusType::INVALID_INPUT;

    }

    bool failedTeamInsert()
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(3);
        bool result = res == StatusType::SUCCESS && obj->add_team(3) == StatusType::FAILURE;
        delete obj;
        return  result;
    }

    //// GAMES PLAYED TESTS
    bool simpleGamesPlayed() {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        assert(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 2, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 3, 1,1,true);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 4, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 5, 1,1,false);
        assert(res == StatusType::SUCCESS);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        assert(resn1.status() == StatusType::SUCCESS);
        assert(resn1.ans() == 1);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        assert(resn2.status() == StatusType::SUCCESS);
        assert(resn2.ans() == 2);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        assert(resn3.status() == StatusType::SUCCESS);
        assert(resn3.ans() == 3);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        assert(resn4.status() == StatusType::SUCCESS);
        assert(resn4.ans() == 4);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        assert(resn5.status() == StatusType::SUCCESS);
        assert(resn5.ans() == 5);

        delete obj;
        return true;
    }

    bool simpleGamesPlayedWithMatches() {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        assert(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        assert(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 2, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 3, 1,1,true);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 4, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 5, 1,1,false);
        assert(res == StatusType::SUCCESS);

        // second team players
        res = obj->add_player(2001, 2,permutation_t::neutral(), 10, 5,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 20, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 30, 1,1,true);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2,permutation_t::neutral(), 40, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2,permutation_t::neutral(), 50, 1,1,false);
        assert(res == StatusType::SUCCESS);

        output_t<int> resplayed = obj->play_match(1,2);
        assert(resplayed.status() == StatusType::SUCCESS);
        assert(resplayed.ans() == 3);

        output_t<int> resplayed1 = obj->play_match(2,1);
        assert(resplayed1.status() == StatusType::SUCCESS);
        assert(resplayed1.ans() == 1);

        output_t<int> resplayed2 = obj->play_match(2,1);
        assert(resplayed1.status() == StatusType::SUCCESS);
        assert(resplayed1.ans() == 1);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        assert(resn1.status() == StatusType::SUCCESS);
        assert(resn1.ans() == 4);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        assert(resn2.status() == StatusType::SUCCESS);
        assert(resn2.ans() == 5);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        assert(resn3.status() == StatusType::SUCCESS);
        assert(resn3.ans() == 6);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        assert(resn4.status() == StatusType::SUCCESS);
        assert(resn4.ans() == 7);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        assert(resn5.status() == StatusType::SUCCESS);
        assert(resn5.ans() == 8);

        output_t<int> respoints1 = obj->get_team_points(1);
        assert(respoints1.status() == StatusType::SUCCESS);
        assert(respoints1.ans() == 0);

        output_t<int> respoints2 = obj->get_team_points(2);
        assert(respoints2.status() == StatusType::SUCCESS);
        assert(respoints2.ans() == 9);

        delete obj;
        return true;
    }

    bool simpleGamesPlayedWithGetCards() {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        assert(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,40,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 2, 1,20,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 3, 1,15,true);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 4, 1,5,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 5, 1,30,false);
        assert(res == StatusType::SUCCESS);

        StatusType resadd1 = obj->add_player_cards(1005,0);
        assert(resadd1 == StatusType::SUCCESS);
        output_t<int> resget1 = obj->get_player_cards(1005);
        assert(resget1.status() == StatusType::SUCCESS);
        assert(resget1.ans() == 30);

        StatusType resadd2 = obj->add_player_cards(1001,0);
        assert(resadd2 == StatusType::SUCCESS);
        output_t<int> rescards2 = obj->get_player_cards(1001);
        assert(rescards2.status() == StatusType::SUCCESS);
        assert(rescards2.ans() == 40);

        StatusType resadd3 = obj->add_player_cards(1002,0);
        assert(resadd3 == StatusType::SUCCESS);
        output_t<int> rescards3 = obj->get_player_cards(1002);
        assert(rescards3.status() == StatusType::SUCCESS);
        assert(rescards3.ans() == 20);

        StatusType resadd4 = obj->add_player_cards(1004,0);
        assert(resadd4 == StatusType::SUCCESS);
        output_t<int> rescards4 = obj->get_player_cards(1004);
        assert(rescards4.status() == StatusType::SUCCESS);
        assert(rescards4.ans() == 5);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        assert(resn1.status() == StatusType::SUCCESS);
        assert(resn1.ans() == 1);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        assert(resn2.status() == StatusType::SUCCESS);
        assert(resn2.ans() == 2);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        assert(resn3.status() == StatusType::SUCCESS);
        assert(resn3.ans() == 3);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        assert(resn4.status() == StatusType::SUCCESS);
        assert(resn4.ans() == 4);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        assert(resn5.status() == StatusType::SUCCESS);
        assert(resn5.ans() == 5);

        delete obj;
        return true;
    }

    bool simpleTeamBuysTeam() {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        assert(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        assert(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 2, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 3, 1,1,true);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 4, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 5, 1,1,false);
        assert(res == StatusType::SUCCESS);

        // second team players
        res = obj->add_player(2001, 2,permutation_t::neutral(), 10, 5,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 20, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 30, 1,1,true);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2,permutation_t::neutral(), 40, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2,permutation_t::neutral(), 50, 1,1,false);
        assert(res == StatusType::SUCCESS);

        StatusType resbuy = obj->buy_team(1,2);
        assert(resbuy == StatusType::SUCCESS);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        assert(resn1.status() == StatusType::SUCCESS);
        assert(resn1.ans() == 1);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        assert(resn2.status() == StatusType::SUCCESS);
        assert(resn2.ans() == 2);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        assert(resn3.status() == StatusType::SUCCESS);
        assert(resn3.ans() == 3);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        assert(resn4.status() == StatusType::SUCCESS);
        assert(resn4.ans() == 4);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        assert(resn5.status() == StatusType::SUCCESS);
        assert(resn5.ans() == 5);

        output_t<int> resn6 = obj->num_played_games_for_player(2001);
        assert(resn6.status() == StatusType::SUCCESS);
        assert(resn6.ans() == 10);

        output_t<int> resn7 = obj->num_played_games_for_player(2002);
        assert(resn7.status() == StatusType::SUCCESS);
        assert(resn7.ans() == 20);

        output_t<int> resn8 = obj->num_played_games_for_player(2003);
        assert(resn8.status() == StatusType::SUCCESS);
        assert(resn8.ans() == 30);

        output_t<int> resn9 = obj->num_played_games_for_player(2004);
        assert(resn9.status() == StatusType::SUCCESS);
        assert(resn9.ans() == 40);

        output_t<int> resn10 = obj->num_played_games_for_player(2005);
        assert(resn10.status() == StatusType::SUCCESS);
        assert(resn10.ans() == 50);

        // team shouldn't exist anymore
        output_t<int> respoints = obj->get_team_points(2);
        assert(respoints.status() == StatusType::FAILURE);

        delete obj;
        return true;
    }

    bool buyTeamAndPlayMatch() {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        assert(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        assert(res == StatusType::SUCCESS);

        res = obj->add_team(3);
        assert(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,1,false);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 2, 1,1,false);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 3, 1,1,true);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 4, 1,1,false);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 5, 1,1,false);

        // second team players
        res = obj->add_player(2001, 2,permutation_t::neutral(), 10, 5,1,false);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 20, 1,1,false);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 30, 1,1,true);
        res = obj->add_player(2004, 2,permutation_t::neutral(), 40, 1,1,false);
        res = obj->add_player(2005, 2,permutation_t::neutral(), 50, 1,1,false);

        // third team players
        res = obj->add_player(3001, 3,permutation_t::neutral(), 10, 5,1,false);
        res = obj->add_player(3002, 3,permutation_t::neutral(), 20, 1,1,false);
        res = obj->add_player(3003, 3,permutation_t::neutral(), 30, 1,1,true);
        res = obj->add_player(3004, 3,permutation_t::neutral(), 40, 1,1,false);
        res = obj->add_player(3005, 3,permutation_t::neutral(), 50, 1,1,false);

        StatusType resbuy = obj->buy_team(2,1);
        assert(resbuy == StatusType::SUCCESS);

        output_t<int> resplay1 = obj->play_match(1,2);
        assert(resplay1.status() == StatusType::FAILURE);

        output_t<int> resplay2 = obj->play_match(2,1);
        assert(resplay2.status() == StatusType::FAILURE);

        output_t<int> resplay3 = obj->play_match(2,3);
        assert(resplay3.status() == StatusType::SUCCESS);
        assert(resplay3.ans() == 1);

        output_t<int> resplay4 = obj->play_match(3,2);
        assert(resplay4.status() == StatusType::SUCCESS);
        assert(resplay4.ans() == 3);

        output_t<int> respoints1 = obj->get_team_points(2);
        assert(respoints1.status() == StatusType::SUCCESS);
        assert(respoints1.ans() == 6);

        output_t<int> respoints2 = obj->get_team_points(3);
        assert(respoints2.status() == StatusType::SUCCESS);
        assert(respoints2.ans() == 0);

        output_t<int> respoints3 = obj->get_team_points(1);
        assert(respoints3.status() == StatusType::FAILURE);

        StatusType resadd1 = obj->add_player_cards(1001,0);
        assert(resadd1 == StatusType::SUCCESS);

        StatusType resadd2 = obj->add_player_cards(2002,0);
        assert(resadd2 == StatusType::SUCCESS);

        StatusType resadd3 = obj->add_player_cards(2005,0);
        assert(resadd3 == StatusType::SUCCESS);

        StatusType resadd4 = obj->add_player_cards(1003,0);
        assert(resadd4 == StatusType::SUCCESS);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        assert(resn1.status() == StatusType::SUCCESS);
        assert(resn1.ans() == 3);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        assert(resn2.status() == StatusType::SUCCESS);
        assert(resn2.ans() == 4);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        assert(resn3.status() == StatusType::SUCCESS);
        assert(resn3.ans() == 5);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        assert(resn4.status() == StatusType::SUCCESS);
        assert(resn4.ans() == 6);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        assert(resn5.status() == StatusType::SUCCESS);
        assert(resn5.ans() == 7);

        output_t<int> resn6 = obj->num_played_games_for_player(2001);
        assert(resn6.status() == StatusType::SUCCESS);
        assert(resn6.ans() == 12);

        output_t<int> resn7 = obj->num_played_games_for_player(2002);
        assert(resn7.status() == StatusType::SUCCESS);
        assert(resn7.ans() == 22);

        output_t<int> resn8 = obj->num_played_games_for_player(2003);
        assert(resn8.status() == StatusType::SUCCESS);
        assert(resn8.ans() == 32);

        output_t<int> resn9 = obj->num_played_games_for_player(2004);
        assert(resn9.status() == StatusType::SUCCESS);
        assert(resn9.ans() == 42);

        output_t<int> resn10 = obj->num_played_games_for_player(2005);
        assert(resn10.status() == StatusType::SUCCESS);
        assert(resn10.ans() == 52);

        // team shouldn't exist anymore
        output_t<int> respoints = obj->get_team_points(1);
        assert(respoints.status() == StatusType::FAILURE);

        delete obj;
        return true;
    }

    bool teamBuysEmptyTeam()
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        assert(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        assert(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 2, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 3, 1,1,true);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 4, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 5, 1,1,false);
        assert(res == StatusType::SUCCESS);

        StatusType resbuy = obj->buy_team(1,2);
        assert(resbuy == StatusType::SUCCESS);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        assert(resn1.status() == StatusType::SUCCESS);
        assert(resn1.ans() == 1);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        assert(resn2.status() == StatusType::SUCCESS);
        assert(resn2.ans() == 2);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        assert(resn3.status() == StatusType::SUCCESS);
        assert(resn3.ans() == 3);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        assert(resn4.status() == StatusType::SUCCESS);
        assert(resn4.ans() == 4);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        assert(resn5.status() == StatusType::SUCCESS);
        assert(resn5.ans() == 5);

        output_t<int> respoints1 = obj->get_team_points(1);
        assert(respoints1.status() == StatusType::SUCCESS);
        assert(respoints1.ans() == 0);

        output_t<int> respoints2 = obj->get_team_points(2);
        assert(respoints2.status() == StatusType::FAILURE);

        delete obj;
        return true;
    }

    bool emptyTeamBuysTeam()
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        assert(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        assert(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 2, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 3, 1,1,true);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 4, 1,1,false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 5, 1,1,false);
        assert(res == StatusType::SUCCESS);

        StatusType resbuy = obj->buy_team(2,1);
        assert(resbuy == StatusType::SUCCESS);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        assert(resn1.status() == StatusType::SUCCESS);
        assert(resn1.ans() == 1);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        assert(resn2.status() == StatusType::SUCCESS);
        assert(resn2.ans() == 2);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        assert(resn3.status() == StatusType::SUCCESS);
        assert(resn3.ans() == 3);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        assert(resn4.status() == StatusType::SUCCESS);
        assert(resn4.ans() == 4);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        assert(resn5.status() == StatusType::SUCCESS);
        assert(resn5.ans() == 5);

        output_t<int> respoints1 = obj->get_team_points(2);
        assert(respoints1.status() == StatusType::SUCCESS);
        assert(respoints1.ans() == 0);

        output_t<int> respoints2 = obj->get_team_points(1);
        assert(respoints2.status() == StatusType::FAILURE);
        delete obj;
        return true;
    }

    bool emptyTeamBuysEmptyTeam()
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        assert(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        assert(res == StatusType::SUCCESS);

        StatusType resbuy = obj->buy_team(1,2);
        assert(resbuy == StatusType::SUCCESS);

        output_t<int> respoints1 = obj->get_team_points(1);
        assert(respoints1.status() == StatusType::SUCCESS);
        assert(respoints1.ans() == 0);

        output_t<int> respoints2 = obj->get_team_points(2);
        assert(respoints2.status() == StatusType::FAILURE);
        delete obj;
        return true;
    }

    bool teamBuysTeamAndAddPlayers(){
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        assert(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        assert(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,1,false);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 2, 1,1,false);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 3, 1,1,true);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 4, 1,1,false);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 5, 1,1,false);

        // second team players
        res = obj->add_player(2001, 2,permutation_t::neutral(), 10, 5,1,false);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 20, 1,1,false);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 30, 1,1,true);
        res = obj->add_player(2004, 2,permutation_t::neutral(), 40, 1,1,false);
        res = obj->add_player(2005, 2,permutation_t::neutral(), 50, 1,1,false);

        StatusType resbuy = obj->buy_team(1,2);
        assert(resbuy == StatusType::SUCCESS);

        res = obj->add_player(2006, 2,permutation_t::neutral(), 50, 1,1,false);
        assert(res == StatusType::FAILURE);

        res = obj->add_player(2006, 1,permutation_t::neutral(), 100, 1,1,false);
        assert(res == StatusType::SUCCESS);

        res = obj->add_player(1003, 1,permutation_t::neutral(), 100, 1,1,false);
        assert(res == StatusType::FAILURE);

        res = obj->add_player(3000, 1,permutation_t::neutral(), 250, 1,1,false);
        assert(res == StatusType::SUCCESS);

        output_t<int> resn= obj->num_played_games_for_player(2006);
        assert(resn.status() == StatusType::SUCCESS);
        assert(resn.ans() == 100);

        output_t<int> resnp= obj->num_played_games_for_player(3000);
        assert(resnp.status() == StatusType::SUCCESS);
        assert(resnp.ans() == 250);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        assert(resn1.status() == StatusType::SUCCESS);
        assert(resn1.ans() == 1);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        assert(resn2.status() == StatusType::SUCCESS);
        assert(resn2.ans() == 2);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        assert(resn3.status() == StatusType::SUCCESS);
        assert(resn3.ans() == 3);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        assert(resn4.status() == StatusType::SUCCESS);
        assert(resn4.ans() == 4);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        assert(resn5.status() == StatusType::SUCCESS);
        assert(resn5.ans() == 5);

        output_t<int> resn6 = obj->num_played_games_for_player(2001);
        assert(resn6.status() == StatusType::SUCCESS);
        assert(resn6.ans() == 10);

        output_t<int> resn7 = obj->num_played_games_for_player(2002);
        assert(resn7.status() == StatusType::SUCCESS);
        assert(resn7.ans() == 20);

        output_t<int> resn8 = obj->num_played_games_for_player(2003);
        assert(resn8.status() == StatusType::SUCCESS);
        assert(resn8.ans() == 30);

        output_t<int> resn9 = obj->num_played_games_for_player(2004);
        assert(resn9.status() == StatusType::SUCCESS);
        assert(resn9.ans() == 40);

        output_t<int> resn10 = obj->num_played_games_for_player(2005);
        assert(resn10.status() == StatusType::SUCCESS);
        assert(resn10.ans() == 50);

        // team shouldn't exist anymore
        output_t<int> respoints = obj->get_team_points(2);
        assert(respoints.status() == StatusType::FAILURE);

        delete obj;
        return true;
    }

    bool multipleTeamBuys() {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        assert(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        assert(res == StatusType::SUCCESS);

        res = obj->add_team(3);
        assert(res == StatusType::SUCCESS);

        res = obj->add_team(4);
        assert(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,1,false);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 2, 1,1,false);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 3, 1,1,true);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 4, 1,1,false);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 5, 1,1,false);

        // second team players
        res = obj->add_player(2001, 2,permutation_t::neutral(), 10, 5,1,false);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 20, 1,1,false);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 30, 1,1,true);
        res = obj->add_player(2004, 2,permutation_t::neutral(), 40, 1,1,false);
        res = obj->add_player(2005, 2,permutation_t::neutral(), 50, 1,1,false);

        // third team players
        res = obj->add_player(3001, 3,permutation_t::neutral(), 301, 5,1,false);
        res = obj->add_player(3002, 3,permutation_t::neutral(), 302, 1,1,false);
        res = obj->add_player(3003, 3,permutation_t::neutral(), 303, 1,1,true);
        res = obj->add_player(3004, 3,permutation_t::neutral(), 304, 1,1,false);
        res = obj->add_player(3005, 3,permutation_t::neutral(), 305, 1,1,false);

        // fourth team players
        res = obj->add_player(4001, 4,permutation_t::neutral(), 401, 5,1,false);
        res = obj->add_player(4002, 4,permutation_t::neutral(), 402, 1,1,false);
        res = obj->add_player(4003, 4,permutation_t::neutral(), 403, 1,1,true);
        res = obj->add_player(4004, 4,permutation_t::neutral(), 404, 1,1,false);
        res = obj->add_player(4005, 4,permutation_t::neutral(), 405, 1,1,false);

        StatusType resbuy = obj->buy_team(2,1);
        assert(resbuy == StatusType::SUCCESS);

        StatusType resbuy1 = obj->buy_team(3,2);
        assert(resbuy1 == StatusType::SUCCESS);

        StatusType resbuy2 = obj->buy_team(4,2);
        assert(resbuy2 == StatusType::FAILURE);

        StatusType resbuy3 = obj->buy_team(3,4);
        assert(resbuy3 == StatusType::SUCCESS);

        StatusType resadd1 = obj->add_player_cards(1001,0);
        assert(resadd1 == StatusType::SUCCESS);

        StatusType resadd2 = obj->add_player_cards(2002,0);
        assert(resadd2 == StatusType::SUCCESS);

        StatusType resadd3 = obj->add_player_cards(3005,0);
        assert(resadd3 == StatusType::SUCCESS);

        StatusType resadd4 = obj->add_player_cards(4002,0);
        assert(resadd4 == StatusType::SUCCESS);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        assert(resn1.status() == StatusType::SUCCESS);
        assert(resn1.ans() == 1);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        assert(resn2.status() == StatusType::SUCCESS);
        assert(resn2.ans() == 2);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        assert(resn3.status() == StatusType::SUCCESS);
        assert(resn3.ans() == 3);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        assert(resn4.status() == StatusType::SUCCESS);
        assert(resn4.ans() == 4);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        assert(resn5.status() == StatusType::SUCCESS);
        assert(resn5.ans() == 5);

        output_t<int> resn6 = obj->num_played_games_for_player(2001);
        assert(resn6.status() == StatusType::SUCCESS);
        assert(resn6.ans() == 10);

        output_t<int> resn7 = obj->num_played_games_for_player(2002);
        assert(resn7.status() == StatusType::SUCCESS);
        assert(resn7.ans() == 20);

        output_t<int> resn8 = obj->num_played_games_for_player(2003);
        assert(resn8.status() == StatusType::SUCCESS);
        assert(resn8.ans() == 30);

        output_t<int> resn9 = obj->num_played_games_for_player(2004);
        assert(resn9.status() == StatusType::SUCCESS);
        assert(resn9.ans() == 40);

        output_t<int> resn10 = obj->num_played_games_for_player(2005);
        assert(resn10.status() == StatusType::SUCCESS);
        assert(resn10.ans() == 50);

        ///////

        output_t<int> resn11 = obj->num_played_games_for_player(3001);
        assert(resn11.status() == StatusType::SUCCESS);
        assert(resn11.ans() == 301);

        output_t<int> resn12 = obj->num_played_games_for_player(3002);
        assert(resn12.status() == StatusType::SUCCESS);
        assert(resn12.ans() == 302);

        output_t<int> resn13 = obj->num_played_games_for_player(3003);
        assert(resn13.status() == StatusType::SUCCESS);
        assert(resn13.ans() == 303);

        output_t<int> resn14 = obj->num_played_games_for_player(3004);
        assert(resn14.status() == StatusType::SUCCESS);
        assert(resn14.ans() == 304);

        output_t<int> resn15 = obj->num_played_games_for_player(3005);
        assert(resn15.status() == StatusType::SUCCESS);
        assert(resn15.ans() == 305);

        output_t<int> resn16 = obj->num_played_games_for_player(4001);
        assert(resn16.status() == StatusType::SUCCESS);
        assert(resn16.ans() == 401);

        output_t<int> resn17 = obj->num_played_games_for_player(4002);
        assert(resn17.status() == StatusType::SUCCESS);
        assert(resn17.ans() == 402);

        output_t<int> resn18 = obj->num_played_games_for_player(4003);
        assert(resn18.status() == StatusType::SUCCESS);
        assert(resn18.ans() == 403);

        output_t<int> resn19 = obj->num_played_games_for_player(4004);
        assert(resn19.status() == StatusType::SUCCESS);
        assert(resn19.ans() == 404);

        output_t<int> resn20 = obj->num_played_games_for_player(4005);
        assert(resn20.status() == StatusType::SUCCESS);
        assert(resn20.ans() == 405);


        delete obj;
        return true;
    }



}