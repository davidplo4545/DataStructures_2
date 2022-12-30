//
// Created by David on 25/11/2022.
//
#include "iostream"
#include "Player.h"
#include "worldcup23a2.h"
//#include "wet2util.h"
#define AGREGATE_TEST_RESULT(res, cond) (res) = ((res) && (cond))

namespace MyTests{

    //// PLAYER TESTS
    bool simplePlayerInsert() { return true;};
    bool invalidInputPlayerInsert();
    bool failedPlayerInsert();


    //// TEAM AND RANKED TREE TESTS
    bool simpleTeamInsert()
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(3);
        delete obj;
        return res == StatusType::SUCCESS;
    }
    bool invalidTeamInsert();
    bool failedTeamInsert();
}