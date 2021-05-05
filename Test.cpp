#include "doctest.h"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Scientist.hpp"
#include "Researcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"
#include "GeneSplicer.hpp"
#include "FieldDoctor.hpp"

#include <iostream>

using namespace pandemic;
using namespace std;

TEST_CASE("Test board")
{
    Board board;

    board[City::Madrid] = 3;
    board[City::Chicago] = 2;
    board[City::Tehran] = 1;
    board[City::Bangkok] = 2;
    board[City::HongKong] = 3;
    board[City::Miami] = 4;

    CHECK_EQ(board[City::Madrid], 3);
    CHECK_EQ(board[City::Chicago], 2);
    CHECK_EQ(board[City::Tehran], 1);
    CHECK_EQ(board[City::Bangkok], 2);
    CHECK_EQ(board[City::HongKong], 3);
    CHECK_EQ(board[City::Miami], 4);

    CHECK_THROWS(board[City::Madrid] = 2);
    CHECK_THROWS(board[City::Chicago] = 5);
    CHECK_THROWS(board[City::Tehran] = 9);
    CHECK_THROWS(board[City::Bangkok] = 3);
    CHECK_THROWS(board[City::HongKong] = 7);
    CHECK_THROWS(board[City::Miami] = 2);
}

TEST_CASE("Test drive")
{
    Board board;
    OperationsExpert operationsExpertPlayer{board, City::MexicoCity}; //OperationsExpert

    operationsExpertPlayer.take_card(City::Algiers)
        .take_card(City::Atlanta)
        .take_card(City::Baghdad)
        .take_card(City::Bangkok)
        .take_card(City::LosAngeles);

    CHECK_NOTHROW(operationsExpertPlayer.drive(City::Chicago));
    CHECK_NOTHROW(operationsExpertPlayer.drive(City::Bogota));
    CHECK_NOTHROW(operationsExpertPlayer.drive(City::SaoPaulo));
    CHECK_NOTHROW(operationsExpertPlayer.drive(City::Lagos));

    CHECK_THROWS(operationsExpertPlayer.drive(City::Paris));
    CHECK_THROWS(operationsExpertPlayer.drive(City::Riyadh));
    CHECK_THROWS(operationsExpertPlayer.drive(City::SanFrancisco));
    CHECK_THROWS(operationsExpertPlayer.drive(City::Sydney));
}

TEST_CASE("Test- fly_direct, fly_charter, fly_shuttle, build")
{
    Board board;
    Researcher researcherPlayer{board, City::Milan};    //Scientist
    Dispatcher dispatcherPlayer{board, City::Santiago}; //Dispatcher

    researcherPlayer.take_card(City::London)
        .take_card(City::Tokyo)
        .take_card(City::Washington)
        .take_card(City::Lima)
        .take_card(City::Shanghai)
        .take_card(City::Taipei)
        .take_card(City::Moscow)
        .take_card(City::Istanbul);

    // fly_direct + build
    CHECK_NOTHROW(researcherPlayer.fly_direct(City::Tokyo));
    CHECK_NOTHROW(researcherPlayer.fly_direct(City::London));
    CHECK_NOTHROW(researcherPlayer.fly_direct(City::Washington));
    CHECK_NOTHROW(researcherPlayer.fly_direct(City::Istanbul));

    CHECK_THROWS(researcherPlayer.fly_direct(City::Tokyo));
    CHECK_THROWS(researcherPlayer.fly_direct(City::London));
    CHECK_THROWS(researcherPlayer.fly_direct(City::Washington));
    CHECK_THROWS(researcherPlayer.fly_direct(City::Istanbul));

    dispatcherPlayer.take_card(City::Santiago);

    CHECK_NOTHROW(dispatcherPlayer.build());
    CHECK_NOTHROW(dispatcherPlayer.fly_direct(City::Seoul)); // no card thrown (Dispatcher)

    // fly_charter
    researcherPlayer.take_card(City::Istanbul);

    CHECK_NOTHROW(researcherPlayer.fly_charter(City::Shanghai));
    CHECK_NOTHROW(researcherPlayer.fly_charter(City::Lima));
    CHECK_NOTHROW(researcherPlayer.fly_charter(City::Taipei));
    CHECK_NOTHROW(researcherPlayer.fly_charter(City::Moscow));

    CHECK_THROWS(researcherPlayer.fly_charter(City::Shanghai));
    CHECK_THROWS(researcherPlayer.fly_charter(City::Lima));
    CHECK_THROWS(researcherPlayer.fly_charter(City::Taipei));
    CHECK_THROWS(researcherPlayer.fly_charter(City::Istanbul));

    // fly_shuttle + build
    CHECK_NOTHROW(researcherPlayer.fly_shuttle(City::Tokyo));
    CHECK_NOTHROW(researcherPlayer.fly_shuttle(City::London));
    CHECK_NOTHROW(researcherPlayer.fly_shuttle(City::Washington));
    CHECK_NOTHROW(researcherPlayer.fly_shuttle(City::Istanbul));

    CHECK_THROWS(researcherPlayer.fly_shuttle(City::Tokyo));
    CHECK_THROWS(researcherPlayer.fly_shuttle(City::London));
    CHECK_THROWS(researcherPlayer.fly_shuttle(City::Washington));
    CHECK_THROWS(researcherPlayer.fly_shuttle(City::Istanbul));

    dispatcherPlayer.take_card(City::Seoul);

    CHECK_NOTHROW(dispatcherPlayer.build());
    CHECK_NOTHROW(dispatcherPlayer.fly_shuttle(City::Santiago));
    CHECK_THROWS(dispatcherPlayer.fly_shuttle(City::Paris));
}
TEST_CASE("Test discover_cure")
{
    Board board;

    // Scientist
    Scientist scientistPlayer{board, City::Paris, 2};

    scientistPlayer.take_card(City::Bangkok)
        .take_card(City::Beijing)
        .take_card(City::HoChiMinhCity);

    scientistPlayer.build();
    CHECK_NOTHROW(scientistPlayer.discover_cure(Color::Red));
    CHECK_THROWS(scientistPlayer.discover_cure(Color::Yellow));

    board.remove_cures();

    // Researcher
    Researcher researcherPlayer{board, City::Essen};

    researcherPlayer.take_card(City::Algiers)
        .take_card(City::Baghdad)
        .take_card(City::Cairo)
        .take_card(City::Chennai)
        .take_card(City::Delhi);

    CHECK_NOTHROW(researcherPlayer.discover_cure(Color::Black));
    CHECK_THROWS(researcherPlayer.discover_cure(Color::Blue));

    board.remove_cures();

    // GeneSplicer
    GeneSplicer geneSplicerPlayer{board, City::HongKong};

    geneSplicerPlayer.take_card(City::Sydney)
        .take_card(City::StPetersburg)
        .take_card(City::Shanghai)
        .take_card(City::Seoul)
        .take_card(City::SaoPaulo);

    geneSplicerPlayer.build();

    CHECK_NOTHROW(geneSplicerPlayer.discover_cure(Color::Black));
    CHECK_THROWS(geneSplicerPlayer.discover_cure(Color::Red));

    board.remove_cures();
}
TEST_CASE("Test treat")
{
    Board board;

    board[City::Khartoum] = 2;
    board[City::Santiago] = 3;
    board[City::Taipei] = 0;
    board[City::NewYork] = 1;
    board[City::SaoPaulo] = 5;

    // Medic
    Medic medicPlayer1{board, City::Khartoum};

    Medic medicPlayer2{board, City::Santiago};
    medicPlayer2.take_card(City::Santiago) 
        .take_card(City::SaoPaulo)
        .take_card(City::Miami)
        .take_card(City::MexicoCity)
        .take_card(City::LosAngeles)
        .take_card(City::Lima);

    CHECK_NOTHROW(medicPlayer1.treat(City::Khartoum));
    CHECK(board[City::Khartoum] == 0);

    medicPlayer2.build();
    medicPlayer2.discover_cure(Color::Yellow); 
    CHECK(board[City::Santiago] == 0);        

    board.remove_cures();

    //Virologist
    Virologist virologistPlayer{board, City::Osaka};
    virologistPlayer.take_card(City::Paris);
    board[City::Paris] = 3;
    CHECK_NOTHROW(virologistPlayer.treat(City::Paris));
    CHECK(board[City::Sydney] == 2);                

    //FieldDoctor
    FieldDoctor fieldDoctorPlayer{board, City::Sydney};
    board[City::Manila] = 2;
    CHECK_NOTHROW(fieldDoctorPlayer.treat(City::Manila)); 
    CHECK(board[City::Manila] == 1);                    
}

TEST_CASE("Test role")
{
    Board board;

    OperationsExpert operationsExpertPlayer{board, City::Bangkok};
    Dispatcher dispatcherPlayer{board, City::Cairo};
    GeneSplicer geneSplicerPlayer{board, City::Essen};
    Scientist scientistPlayer{board, City::HongKong, 1};
    Researcher researcherPlayer{board, City::Jakarta};
    Medic medicPlayer{board, City::Kinshasa};
    Virologist virologistPlayer{board, City::LosAngeles};
    FieldDoctor fieldDoctorPlayer{board, City::Manila};

    CHECK(operationsExpertPlayer.role() == "OperationsExpert");
    CHECK(dispatcherPlayer.role() == "Dispatcher");
    CHECK(geneSplicerPlayer.role() == "GeneSplicer");
    CHECK(scientistPlayer.role() == "Scientist");
    CHECK(researcherPlayer.role() == "Researcher");
    CHECK(medicPlayer.role() == "Medic");
    CHECK(virologistPlayer.role() == "Virologist");
    CHECK(fieldDoctorPlayer.role() == "FieldDoctor");
}
