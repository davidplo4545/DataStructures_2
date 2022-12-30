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

TEST_CASE("Hash Table Tests")
{
    SECTION("simple player insert")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }
}
