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
        std::cout << "Got here";
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

TEST_CASE("game played more tests")
{
//// GAMES PLAYED TESTS
    SECTION("simple games_played1") {
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

    SECTION("simple games_played with matches") {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(2);
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

        // second team players
        res = obj->add_player(2001, 2,permutation_t::neutral(), 10, 5,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 20, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2,permutation_t::neutral(), 40, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2,permutation_t::neutral(), 50, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resplayed = obj->play_match(1,2);
        REQUIRE(resplayed.status() == StatusType::SUCCESS);
        REQUIRE(resplayed.ans() == 3);

        output_t<int> resplayed1 = obj->play_match(2,1);
        REQUIRE(resplayed1.status() == StatusType::SUCCESS);
        REQUIRE(resplayed1.ans() == 1);

        output_t<int> resplayed2 = obj->play_match(2,1);
        REQUIRE(resplayed2.status() == StatusType::SUCCESS);
        REQUIRE(resplayed2.ans() == 1);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 4);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 5);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 6);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 7);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 8);

        output_t<int> respoints1 = obj->get_team_points(1);
        REQUIRE(respoints1.status() == StatusType::SUCCESS);
        REQUIRE(respoints1.ans() == 0);

        output_t<int> respoints2 = obj->get_team_points(2);
        REQUIRE(respoints2.status() == StatusType::SUCCESS);
        REQUIRE(respoints2.ans() == 9);

        delete obj;
    }

    SECTION("simple games_played with add cards") {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1,permutation_t::neutral(), 1, 1,40,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1,permutation_t::neutral(), 2, 1,20,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1,permutation_t::neutral(), 3, 1,15,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1,permutation_t::neutral(), 4, 1,5,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1,permutation_t::neutral(), 5, 1,30,false);
        REQUIRE(res == StatusType::SUCCESS);

        StatusType resadd1 = obj->add_player_cards(1005,0);
        REQUIRE(resadd1 == StatusType::SUCCESS);
        output_t<int> resget1 = obj->get_player_cards(1005);
        REQUIRE(resget1.status() == StatusType::SUCCESS);
        REQUIRE(resget1.ans() == 30);

        StatusType resadd2 = obj->add_player_cards(1001,0);
        REQUIRE(resadd2 == StatusType::SUCCESS);
        output_t<int> rescards2 = obj->get_player_cards(1001);
        REQUIRE(rescards2.status() == StatusType::SUCCESS);
        REQUIRE(rescards2.ans() == 40);

        StatusType resadd3 = obj->add_player_cards(1002,0);
        REQUIRE(resadd3 == StatusType::SUCCESS);
        output_t<int> rescards3 = obj->get_player_cards(1002);
        REQUIRE(rescards3.status() == StatusType::SUCCESS);
        REQUIRE(rescards3.ans() == 20);

        StatusType resadd4 = obj->add_player_cards(1004,0);
        REQUIRE(resadd4 == StatusType::SUCCESS);
        output_t<int> rescards4 = obj->get_player_cards(1004);
        REQUIRE(rescards4.status() == StatusType::SUCCESS);
        REQUIRE(rescards4.ans() == 5);

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

    SECTION("simple games_played when team buys team") {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(2);
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

        // second team players
        res = obj->add_player(2001, 2,permutation_t::neutral(), 10, 5,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2,permutation_t::neutral(), 20, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2,permutation_t::neutral(), 30, 1,1,true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2,permutation_t::neutral(), 40, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2,permutation_t::neutral(), 50, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        StatusType resbuy = obj->buy_team(1,2);
        REQUIRE(resbuy == StatusType::SUCCESS);

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

        output_t<int> resn6 = obj->num_played_games_for_player(2001);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 10);

        output_t<int> resn7 = obj->num_played_games_for_player(2002);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(resn7.ans() == 20);

        output_t<int> resn8 = obj->num_played_games_for_player(2003);
        REQUIRE(resn8.status() == StatusType::SUCCESS);
        REQUIRE(resn8.ans() == 30);

        output_t<int> resn9 = obj->num_played_games_for_player(2004);
        REQUIRE(resn9.status() == StatusType::SUCCESS);
        REQUIRE(resn9.ans() == 40);

        output_t<int> resn10 = obj->num_played_games_for_player(2005);
        REQUIRE(resn10.status() == StatusType::SUCCESS);
        REQUIRE(resn10.ans() == 50);

        // team shouldn't exist anymore
        output_t<int> respoints = obj->get_team_points(2);
        REQUIRE(respoints.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("simple games_played when team buys team and plays match") {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(3);
        REQUIRE(res == StatusType::SUCCESS);

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
        REQUIRE(resbuy == StatusType::SUCCESS);

        output_t<int> resplay1 = obj->play_match(1,2);
        REQUIRE(resplay1.status() == StatusType::FAILURE);

        output_t<int> resplay2 = obj->play_match(2,1);
        REQUIRE(resplay2.status() == StatusType::FAILURE);

        output_t<int> resplay3 = obj->play_match(2,3);
        REQUIRE(resplay3.status() == StatusType::SUCCESS);
        REQUIRE(resplay3.ans() == 1);

        output_t<int> resplay4 = obj->play_match(3,2);
        REQUIRE(resplay4.status() == StatusType::SUCCESS);
        REQUIRE(resplay4.ans() == 3);

        output_t<int> respoints1 = obj->get_team_points(2);
        REQUIRE(respoints1.status() == StatusType::SUCCESS);
        REQUIRE(respoints1.ans() == 6);

        output_t<int> respoints2 = obj->get_team_points(3);
        REQUIRE(respoints2.status() == StatusType::SUCCESS);
        REQUIRE(respoints2.ans() == 0);

        output_t<int> respoints3 = obj->get_team_points(1);
        REQUIRE(respoints3.status() == StatusType::FAILURE);

        StatusType resadd1 = obj->add_player_cards(1001,0);
        REQUIRE(resadd1 == StatusType::SUCCESS);

        StatusType resadd2 = obj->add_player_cards(2002,0);
        REQUIRE(resadd2 == StatusType::SUCCESS);

        StatusType resadd3 = obj->add_player_cards(2005,0);
        REQUIRE(resadd3 == StatusType::SUCCESS);

        StatusType resadd4 = obj->add_player_cards(1003,0);
        REQUIRE(resadd4 == StatusType::SUCCESS);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 3);

        output_t<int> resn2 = obj->num_played_games_for_player(1002);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 4);

        output_t<int> resn3 = obj->num_played_games_for_player(1003);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 5);

        output_t<int> resn4 = obj->num_played_games_for_player(1004);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 6);

        output_t<int> resn5 = obj->num_played_games_for_player(1005);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 7);

        output_t<int> resn6 = obj->num_played_games_for_player(2001);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 12);

        output_t<int> resn7 = obj->num_played_games_for_player(2002);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(resn7.ans() == 22);

        output_t<int> resn8 = obj->num_played_games_for_player(2003);
        REQUIRE(resn8.status() == StatusType::SUCCESS);
        REQUIRE(resn8.ans() == 32);

        output_t<int> resn9 = obj->num_played_games_for_player(2004);
        REQUIRE(resn9.status() == StatusType::SUCCESS);
        REQUIRE(resn9.ans() == 42);

        output_t<int> resn10 = obj->num_played_games_for_player(2005);
        REQUIRE(resn10.status() == StatusType::SUCCESS);
        REQUIRE(resn10.ans() == 52);

        // team shouldn't exist anymore
        output_t<int> respoints = obj->get_team_points(1);
        REQUIRE(respoints.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("simple games_played when team buys empty team")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(2);
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

        StatusType resbuy = obj->buy_team(1,2);
        REQUIRE(resbuy == StatusType::SUCCESS);

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

        output_t<int> respoints1 = obj->get_team_points(1);
        REQUIRE(respoints1.status() == StatusType::SUCCESS);
        REQUIRE(respoints1.ans() == 0);

        output_t<int> respoints2 = obj->get_team_points(2);
        REQUIRE(respoints2.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("simple games_played when empty team buys team")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(2);
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

        StatusType resbuy = obj->buy_team(2,1);
        REQUIRE(resbuy == StatusType::SUCCESS);

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

        output_t<int> respoints1 = obj->get_team_points(2);
        REQUIRE(respoints1.status() == StatusType::SUCCESS);
        REQUIRE(respoints1.ans() == 0);

        output_t<int> respoints2 = obj->get_team_points(1);
        REQUIRE(respoints2.status() == StatusType::FAILURE);
        delete obj;
    }

    SECTION("simple games_played when empty team buys empty team")

    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        StatusType resbuy = obj->buy_team(1,2);
        REQUIRE(resbuy == StatusType::SUCCESS);

        output_t<int> respoints1 = obj->get_team_points(1);
        REQUIRE(respoints1.status() == StatusType::SUCCESS);
        REQUIRE(respoints1.ans() == 0);

        output_t<int> respoints2 = obj->get_team_points(2);
        REQUIRE(respoints2.status() == StatusType::FAILURE);
        delete obj;

    }

    SECTION("simple games_played when team buys team and adds players"){
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

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
        REQUIRE(resbuy == StatusType::SUCCESS);

        res = obj->add_player(2006, 2,permutation_t::neutral(), 50, 1,1,false);
        REQUIRE(res == StatusType::FAILURE);

        res = obj->add_player(2006, 1,permutation_t::neutral(), 100, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(1003, 1,permutation_t::neutral(), 100, 1,1,false);
        REQUIRE(res == StatusType::FAILURE);

        res = obj->add_player(3000, 1,permutation_t::neutral(), 250, 1,1,false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn= obj->num_played_games_for_player(2006);
        REQUIRE(resn.status() == StatusType::SUCCESS);
        REQUIRE(resn.ans() == 100);

        output_t<int> resnp= obj->num_played_games_for_player(3000);
        REQUIRE(resnp.status() == StatusType::SUCCESS);
        REQUIRE(resnp.ans() == 250);

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

        output_t<int> resn6 = obj->num_played_games_for_player(2001);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 10);

        output_t<int> resn7 = obj->num_played_games_for_player(2002);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(resn7.ans() == 20);

        output_t<int> resn8 = obj->num_played_games_for_player(2003);
        REQUIRE(resn8.status() == StatusType::SUCCESS);
        REQUIRE(resn8.ans() == 30);

        output_t<int> resn9 = obj->num_played_games_for_player(2004);
        REQUIRE(resn9.status() == StatusType::SUCCESS);
        REQUIRE(resn9.ans() == 40);

        output_t<int> resn10 = obj->num_played_games_for_player(2005);
        REQUIRE(resn10.status() == StatusType::SUCCESS);
        REQUIRE(resn10.ans() == 50);

        // team shouldn't exist anymore
        output_t<int> respoints = obj->get_team_points(2);
        REQUIRE(respoints.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("games_played with multipled teams buys") {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(3);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(4);
        REQUIRE(res == StatusType::SUCCESS);

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
        REQUIRE(resbuy == StatusType::SUCCESS);

        StatusType resbuy1 = obj->buy_team(3,2);
        REQUIRE(resbuy1 == StatusType::SUCCESS);

        StatusType resbuy2 = obj->buy_team(4,2);
        REQUIRE(resbuy2 == StatusType::FAILURE);

        StatusType resbuy3 = obj->buy_team(3,4);
        REQUIRE(resbuy3 == StatusType::SUCCESS);

        StatusType resadd1 = obj->add_player_cards(1001,0);
        REQUIRE(resadd1 == StatusType::SUCCESS);

        StatusType resadd2 = obj->add_player_cards(2002,0);
        REQUIRE(resadd2 == StatusType::SUCCESS);

        StatusType resadd3 = obj->add_player_cards(3005,0);
        REQUIRE(resadd3 == StatusType::SUCCESS);

        StatusType resadd4 = obj->add_player_cards(4002,0);
        REQUIRE(resadd4 == StatusType::SUCCESS);

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

        output_t<int> resn6 = obj->num_played_games_for_player(2001);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 10);

        output_t<int> resn7 = obj->num_played_games_for_player(2002);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(resn7.ans() == 20);

        output_t<int> resn8 = obj->num_played_games_for_player(2003);
        REQUIRE(resn8.status() == StatusType::SUCCESS);
        REQUIRE(resn8.ans() == 30);

        output_t<int> resn9 = obj->num_played_games_for_player(2004);
        REQUIRE(resn9.status() == StatusType::SUCCESS);
        REQUIRE(resn9.ans() == 40);

        output_t<int> resn10 = obj->num_played_games_for_player(2005);
        REQUIRE(resn10.status() == StatusType::SUCCESS);
        REQUIRE(resn10.ans() == 50);

        ///////

        output_t<int> resn11 = obj->num_played_games_for_player(3001);
        REQUIRE(resn11.status() == StatusType::SUCCESS);
        REQUIRE(resn11.ans() == 301);

        output_t<int> resn12 = obj->num_played_games_for_player(3002);
        REQUIRE(resn12.status() == StatusType::SUCCESS);
        REQUIRE(resn12.ans() == 302);

        output_t<int> resn13 = obj->num_played_games_for_player(3003);
        REQUIRE(resn13.status() == StatusType::SUCCESS);
        REQUIRE(resn13.ans() == 303);

        output_t<int> resn14 = obj->num_played_games_for_player(3004);
        REQUIRE(resn14.status() == StatusType::SUCCESS);
        REQUIRE(resn14.ans() == 304);

        output_t<int> resn15 = obj->num_played_games_for_player(3005);
        REQUIRE(resn15.status() == StatusType::SUCCESS);
        REQUIRE(resn15.ans() == 305);

        output_t<int> resn16 = obj->num_played_games_for_player(4001);
        REQUIRE(resn16.status() == StatusType::SUCCESS);
        REQUIRE(resn16.ans() == 401);

        output_t<int> resn17 = obj->num_played_games_for_player(4002);
        REQUIRE(resn17.status() == StatusType::SUCCESS);
        REQUIRE(resn17.ans() == 402);

        output_t<int> resn18 = obj->num_played_games_for_player(4003);
        REQUIRE(resn18.status() == StatusType::SUCCESS);
        REQUIRE(resn18.ans() == 403);

        output_t<int> resn19 = obj->num_played_games_for_player(4004);
        REQUIRE(resn19.status() == StatusType::SUCCESS);
        REQUIRE(resn19.ans() == 404);

        output_t<int> resn20 = obj->num_played_games_for_player(4005);
        REQUIRE(resn20.status() == StatusType::SUCCESS);
        REQUIRE(resn20.ans() == 405);


        delete obj;
    }

}