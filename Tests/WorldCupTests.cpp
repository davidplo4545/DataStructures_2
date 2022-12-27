#define CATCH_CONFIG_MAIN

#include <string>
#include <iostream>
#include "../HashTable.h"
#include "../Player.h"
#include <sstream>
#include <vector>
#include "catch.hpp"
#include <stdlib.h>
#include "../../DataStruct/DataEx1/worldcup23a1.h"

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
        HashTable hs = HashTable();
        for(int i=100;i<130;i++)
        {
            Player* pl = new Player(i,5,0,0,0,false);
            hs.insert(i,pl);
        }
        hs.printTable();
//        StatusType res = obj->add_team(1, 2);
//        REQUIRE(res == StatusType::SUCCESS);
//        delete obj;
    }
}
