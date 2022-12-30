#define CATCH_CONFIG_MAIN

#include <string>
#include <iostream>
#include "../HashTable.h"
#include "../Player.h"
#include "../wet2util.h"
#include "../worldcup23a2.h"
#include <sstream>
#include <vector>
#include "catch.hpp"
#include <stdlib.h>

using namespace std;

static const char *StatusTypeStr[] =
    {
        "SUCCESS",
        "ALLOCATION_ERROR",
        "INVALID_INPUT",
        "FAILURE"};

void print(string cmd, StatusType res)
{
    cout << cmd << ": " << StatusTypeStr[(int)res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS)
    {
        cout << cmd << ": " << StatusTypeStr[(int)res.status()] << ", " << res.ans() << endl;
    }
    else
    {
        cout << cmd << ": " << StatusTypeStr[(int)res.status()] << endl;
    }
}

TEST_CASE("Insert and remove team")
{
    SECTION("simple insert team")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("insert team with negative id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(-1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }


    SECTION("insert team with 0 id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(0);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }


    SECTION("insert team that exists")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(1);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("simple remove team")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("remove team that doesn't exist")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->remove_team(1);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("remove team twice")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_team(1);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("remove team with negative id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->remove_team(-1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("remove team with 0 id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->remove_team(0);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }
}

TEST_CASE("add player")
{

    SECTION("simple add player")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1,permutation_t::neutral(), 5, 5,5,false);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("simple add goal keeper player")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 2,permutation_t::neutral(), 5, 5,5,true);

        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("add player with negative id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(-1, 2,permutation_t::neutral(), 5, 5,5,false);

        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with negative team id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, -2,permutation_t::neutral(), 5, 5,5,false);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with negative games")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 2,permutation_t::neutral(), -5, 5,5,false);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with 0 id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(0, 2,permutation_t::neutral(), 5, 5,5,false);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with 0 team id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 0,permutation_t::neutral(), 5, 5,5,false);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with negative cards")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1,permutation_t::neutral(), 5, 5,-5,false);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }



    SECTION("add player with 0 id and 0 team id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(0, 0,permutation_t::neutral(), 5, 5,5,false);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with many zeroes")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(0, 1,permutation_t::neutral(), 0, 0,0,true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with zero all")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(0, 0,permutation_t::invalid(), 0, 0,0,true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player that exists")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1,permutation_t::neutral(), 2, 2,2,true);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("add player with team that doesn't exist")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4, 4,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("add teams and players - segel test")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(3);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(4);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1012, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(2001, 2,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(3001, 3,permutation_t::neutral(), 3, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3002, 3,permutation_t::neutral(), 3, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3003, 3,permutation_t::neutral(), 3, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3004, 3,permutation_t::neutral(), 3, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3005, 3,permutation_t::neutral(), 3, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3006, 3,permutation_t::neutral(), 3, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3007, 3,permutation_t::neutral(), 3, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3008, 3,permutation_t::neutral(), 3, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3009, 3,permutation_t::neutral(), 3, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3010, 3,permutation_t::neutral(), 3, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3011, 3,permutation_t::neutral(), 3, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(4001, 4,permutation_t::neutral(), 4, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4002, 4,permutation_t::neutral(), 4, 3,3,false);
        REQUIRE(res == StatusType::SUCCESS);

        delete obj;
    }
}


TEST_CASE("get num played games")
{
    SECTION("simple get played")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn = obj->num_played_games_for_player(1001);
        REQUIRE(resn.status() == StatusType::SUCCESS);
        REQUIRE(resn.ans() == 10);

        delete obj;
    }

    SECTION("simple get played")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 0, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn = obj->num_played_games_for_player(1002);
        REQUIRE(resn.status() == StatusType::SUCCESS);
        REQUIRE(resn.ans() == 0);

        delete obj;
    }

    SECTION("get num played for non exist player")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 0, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn = obj->num_played_games_for_player(1003);
        REQUIRE(resn.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("get num played for non exist player2")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn = obj->num_played_games_for_player(1003);
        REQUIRE(resn.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("get_num_played for negative player id")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn = obj->num_played_games_for_player(-1);
        REQUIRE(resn.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("get_num_played for 0 player id")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn = obj->num_played_games_for_player(0);
        REQUIRE(resn.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("segel test")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(3);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(4);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn1 = obj->num_played_games_for_player(1002);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 10);

        res = obj->add_player(1003, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn2 = obj->num_played_games_for_player(1006);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 10);

        res = obj->add_player(1008, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1,permutation_t::neutral(), 10, 1,1,true);

        output_t<int> resn3 = obj->num_played_games_for_player(1010);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 10);

        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1012, 1,permutation_t::neutral(), 10, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(2001, 2,permutation_t::neutral(), 20, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 20, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 20, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2,permutation_t::neutral(), 20, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2,permutation_t::neutral(), 20, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2,permutation_t::neutral(), 20, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2,permutation_t::neutral(), 20, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2,permutation_t::neutral(), 20, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2,permutation_t::neutral(), 20, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2,permutation_t::neutral(), 0, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2,permutation_t::neutral(), 20, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(3001, 3,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3002, 3,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3003, 3,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3004, 3,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3005, 3,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3006, 3,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3007, 3,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3008, 3,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3009, 3,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3010, 3,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3011, 3,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(4001, 4,permutation_t::neutral(), 2, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4002, 4,permutation_t::neutral(), 2, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn4 = obj->num_played_games_for_player(3001);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 30);

        output_t<int> resn5 = obj->num_played_games_for_player(3011);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 30);

        output_t<int> resn6 = obj->num_played_games_for_player(1001);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 10);

        output_t<int> resn7 = obj->num_played_games_for_player(4001);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(resn7.ans() == 2);

        delete obj;
    }
}

TEST_CASE("get team points")
{
    SECTION("simple get_team_points")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_team_points(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 0);

        delete obj;
    }

    SECTION("get_team_points negative teamid")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_team_points(-6);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("get_team_points 0 teamid")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_team_points(0);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("get_team_points no team id")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_team_points(1);
        REQUIRE(resn1.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("get_team_points 2 teams")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_team_points(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 0);
        output_t<int> resn2 = obj->get_team_points(2);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 0);

        delete obj;
    }

    SECTION("get_team_points with add player")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3001, 1,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_team_points(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 0);

        delete obj;
    }

}

TEST_CASE("play_match")
{
    SECTION("simple play_match")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        // second team players
        res = obj->add_player(2001, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> result = obj->play_match(1, 2).status();
        REQUIRE(StatusType::SUCCESS == result.status());
        REQUIRE(result.ans() == 0);

        delete obj;
    }

    SECTION("play_match invalid input")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->play_match(0, 1).status();
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->play_match(1, 0).status();
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->play_match(0, 0).status();
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->play_match(3, 3).status();
        REQUIRE(res == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("play_match failure")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->play_match(1, 2).status();
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(2, 1).status();
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(1, 2).status();
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 5,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2001, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(1, 2).status();
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(1, 2).status();
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1006 ,1,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2,permutation_t::neutral(), 1, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> result = obj->play_match(1, 2);
        REQUIRE(result.status() == StatusType::SUCCESS);
        REQUIRE(result.ans() == 1);

        res = obj->add_player(2007, 2,permutation_t::neutral(), 1, 15,1,true);

        output_t<int> resn = obj->play_match(1, 2);
        REQUIRE(resn.status() == StatusType::SUCCESS);
        REQUIRE(resn.ans() == 3);

        delete obj;
    }

    SECTION("play_match no goal keepers")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        // second team players
        res = obj->add_player(2001, 2,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->play_match(1, 2).status();
        REQUIRE(res == StatusType::FAILURE);

        delete obj;
    }

    SECTION("play_match goal keepers only on one")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 1, 15,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        // second team players
        res = obj->add_player(2001, 2,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 1, 15,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->play_match(1, 2).status();
        REQUIRE(res == StatusType::FAILURE);

        delete obj;
    }

}

TEST_CASE("games played testing")
{
    SECTION("simple games_played")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 2, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 3, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 4, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 5, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 2);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 3);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 4);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 5);

        delete obj;
    }


}

