#include <functional>
#include <iostream>
#include "TestUtils.h"

namespace MyTests{
    bool simpleTeamInsert();
    bool invalidTeamInsert();
    bool failedTeamInsert();
    bool simpleAbilityTest();
//
    bool simplePlayerInsert();
//    bool invalidInputPlayerInsert();
//    bool failedPlayerInsert();
    bool simpleGamesPlayed();
    bool simpleGamesPlayedWithGetCards();
    bool simpleGamesPlayedWithMatches();
    bool simpleTeamBuysTeam();
    bool buyTeamAndPlayMatch();
    bool teamBuysEmptyTeam();
    bool emptyTeamBuysTeam();
    bool emptyTeamBuysEmptyTeam();
    bool teamBuysTeamAndAddPlayers();
    bool multipleTeamBuys();
}

std::function<bool()> testsList[] = {
        MyTests::simpleAbilityTest,
//        MyTests::simpleGamesPlayed,
//        MyTests::simpleGamesPlayedWithGetCards,
//        MyTests::simpleGamesPlayedWithMatches,
//        MyTests::simpleTeamBuysTeam,
//        MyTests::buyTeamAndPlayMatch,
//        MyTests::teamBuysEmptyTeam,
//        MyTests::emptyTeamBuysTeam,
//        MyTests::emptyTeamBuysEmptyTeam,
//        MyTests::teamBuysTeamAndAddPlayers,
//        MyTests::multipleTeamBuys,
//         Team Tests
//        MyTests::simpleTeamInsert,
//        MyTests::invalidTeamInsert,
//        MyTests::failedTeamInsert,
//
//        // Player Tests
//        MyTests::simplePlayerInsert,
//        MyTests::invalidInputPlayerInsert,
//        MyTests::failedPlayerInsert,
};

const int NUMBER_OF_TESTS = sizeof(testsList)/sizeof(std::function<bool()>);
int main(int argc, char *argv[])
{
    if (argc < 2) {
        for (int i = 0; i < NUMBER_OF_TESTS; ++i) {
            runTest(testsList[i], "Test " + std::to_string(i + 1));
        }
    }
    else {
        int idx = -1;
        try {
            idx = std::stoi(argv[1]) - 1;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: invalid argument: " << argv[1] << std::endl;
            return 1;
        }
        if (idx < 0 || idx > NUMBER_OF_TESTS - 1) {
            std::cerr << "Error: index out of range: " << argv[1] << std::endl;
            return 1;
        }
        runTest(testsList[idx], "Test " + std::to_string(idx + 1));
    }


    return 0;
}