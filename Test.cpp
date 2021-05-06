#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <fstream>
#include "doctest.h"

using namespace pandemic;
using namespace std;


TEST_CASE("make new Board and init all the details"){
    Board board = Board();
    CHECK(board.is_clean() == true);
    int a = board[City::Kinshasa];
    board[City::Kinshasa] = 5; 
    int b = board[City::Kinshasa];
	board[City::Kinshasa] = 1;
    int c = board[City::Kinshasa];
    CHECK(a == 0);
    CHECK(a != b);
    CHECK(b != c);
}

TEST_CASE("drive test:"){
    Board board;

    Player player {board, City::Bangkok};
    CHECK_THROWS(player.drive(City::Paris)); // are not connected.
    CHECK_NOTHROW(player.drive(City::Kolkata)); // are connected!

    OperationsExpert operationsExpert {board, City::Algiers};
    CHECK_THROWS(operationsExpert.drive(City::Miami)); // are not connected.
    CHECK_NOTHROW(operationsExpert.drive(City::Paris)); // are connected!

    Dispatcher dispatcher {board, City::Baghdad};
    CHECK_THROWS(dispatcher.drive(City::Paris)); // are not connected.
    CHECK_NOTHROW(dispatcher.drive(City::Istanbul)); // are connected!

    Scientist scientist {board, City::Khartoum, 3};
    CHECK_THROWS(scientist.drive(City::Paris)); // are not connected.
    CHECK_NOTHROW(scientist.drive(City::Cairo)); // are connected!

    Researcher researcher {board, City::Kolkata};
    CHECK_THROWS(researcher.drive(City::Paris)); // are not connected.
    CHECK_NOTHROW(researcher.drive(City::Delhi)); // are connected!
        
    Medic medic {board, City::Algiers};
    CHECK_THROWS(medic.drive(City::Miami)); // are not connected.
    CHECK_NOTHROW(medic.drive(City::Paris)); // are connected!

    Virologist virologist {board, City::Lagos};
    CHECK_THROWS(virologist.drive(City::Paris)); // are not connected.
    CHECK_NOTHROW(virologist.drive(City::SaoPaulo)); // are connected!
    
    GeneSplicer geneSplicer {board, City::NewYork};
    CHECK_THROWS(geneSplicer.drive(City::Miami)); // are not connected.
    CHECK_NOTHROW(geneSplicer.drive(City::London)); // are connected!

    FieldDoctor fieldDoctor {board, City::Paris};
    CHECK_THROWS(fieldDoctor.drive(City::Osaka)); // are not connected.
    CHECK_NOTHROW(fieldDoctor.drive(City::Madrid)); // are connected!
}


TEST_CASE("build test:"){
    Board board;

    // regular act:
    Player player {board, City::Baghdad};
    CHECK_THROWS(player.build());  // doesnt have accurate card!
    player.take_card(City::Baghdad);
    CHECK_NOTHROW(player.build());  // has accurate card!
    
    Dispatcher dispatcher {board, City::Baghdad};
    CHECK_THROWS(dispatcher.build());  // doesnt have accurate card!
    dispatcher.take_card(City::Baghdad);
    CHECK_NOTHROW(dispatcher.build());  // has accurate card!

    Scientist scientist {board, City::Baghdad, 2};
    CHECK_THROWS(scientist.build());  // doesnt have accurate card!
    scientist.take_card(City::Baghdad);
    CHECK_NOTHROW(scientist.build());  // has accurate card!

    Researcher researcher {board, City::Baghdad};
    CHECK_THROWS(researcher.build());  // doesnt have accurate card!
    researcher.take_card(City::Baghdad);
    CHECK_NOTHROW(researcher.build());  // has accurate card!

    Medic medic {board, City::Baghdad};
    CHECK_THROWS(medic.build());  // doesnt have accurate card!
    medic.take_card(City::Baghdad);
    CHECK_NOTHROW(medic.build());  // has accurate card!

    Virologist virologist {board, City::Baghdad};
    CHECK_THROWS(virologist.build());  // doesnt have accurate card!
    virologist.take_card(City::Baghdad);
    CHECK_NOTHROW(virologist.build());  // has accurate card!

    GeneSplicer geneSplicer {board, City::Baghdad};
    CHECK_THROWS(geneSplicer.build());  // doesnt have accurate card!
    geneSplicer.take_card(City::Baghdad);
    CHECK_NOTHROW(geneSplicer.build());  // has accurate card!

    FieldDoctor fieldDoctor {board, City::Baghdad};
    CHECK_THROWS(fieldDoctor.build());  // doesnt have accurate card!
    fieldDoctor.take_card(City::Baghdad);
    CHECK_NOTHROW(fieldDoctor.build());  // has accurate card!

    // special act - operationsExpert can build without accurate card!
    OperationsExpert operationsExpert {board, City::London};
    CHECK_NOTHROW(operationsExpert.build());  

}



TEST_CASE("fly_direct test:"){
    Board board;
    Player player {board, City::Bangkok};
    CHECK_THROWS(player.fly_direct(City::Paris)); // doesnt have accurate card!
    player.take_card(City::Paris);
    CHECK_NOTHROW(player.fly_direct(City::Paris)); // has accurate card!

    OperationsExpert operationsExpert {board, City::Algiers};
    CHECK_THROWS(operationsExpert.fly_direct(City::Miami)); // doesnt have accurate card!
    player.take_card(City::Miami);
    CHECK_NOTHROW(operationsExpert.fly_direct(City::Miami)); // has accurate card!

    // special act - dispatcher can fly_direct between cities with research stations, without card:
    Dispatcher dispatcher {board, City::Baghdad};
    CHECK_THROWS(dispatcher.fly_direct(City::Paris)); // no research stations, and no accurate card!
    dispatcher.build();
    CHECK_NOTHROW(dispatcher.fly_direct(City::Istanbul)); // there is research stations
}


TEST_CASE("fly_charter test:"){

Board board;
    Player player {board, City::Osaka};
    CHECK_THROWS(player.fly_charter(City::Paris)); // doesnt have accurate card!
    player.take_card(City::Osaka);
    CHECK_NOTHROW(player.fly_direct(City::Paris)); //  has accurate card!

    OperationsExpert operationsExpert {board, City::Paris};
    CHECK_THROWS(operationsExpert.fly_direct(City::Miami)); // doesnt have accurate card!
    player.take_card(City::Paris);
    player.take_card(City::Miami);
    CHECK_NOTHROW(operationsExpert.fly_direct(City::Miami).fly_direct(City::Istanbul)); // has accurate card!

}


TEST_CASE("fly_shuttle test:"){

    Board board;
    Player player1 {board, City::Miami};
    Player player2 {board, City::Paris};
    Player player3 {board, City::London};

    CHECK_THROWS(player1.fly_shuttle(City::Paris));
    player1.build();
    CHECK_THROWS(player1.fly_shuttle(City::Paris));
    player2.build();
    CHECK_NOTHROW(player1.fly_shuttle(City::Paris));
    player3.build();
    CHECK_NOTHROW(player2.fly_shuttle(City::Paris).fly_shuttle(City::Miami));
}


TEST_CASE("discover_cure test:"){
    Board board;
    OperationsExpert operationsExpert {board, City::Miami};
    operationsExpert.build();
    operationsExpert.take_card(City::Algiers);   // Black
    operationsExpert.take_card(City::Baghdad);   // Black
    operationsExpert.take_card(City::Cairo);   // Black
    operationsExpert.take_card(City::Kolkata);   // Black
    operationsExpert.take_card(City::Khartoum);   // Yellow

    CHECK_THROWS(operationsExpert.discover_cure(Color::Black));
    operationsExpert.take_card(City::Moscow);   // Black
    CHECK_NOTHROW(operationsExpert.discover_cure(Color::Black));    
    
    Player player {board, City::Paris};
    player.take_card(City::Algiers);   // Black
    player.take_card(City::Baghdad);   // Black
    player.take_card(City::Cairo);   // Black
    player.take_card(City::Kolkata);   // Black
    player.take_card(City::Moscow);   // Black

    CHECK_THROWS(player.discover_cure(Color::Black));  //no research stations
    player.take_card(City::Paris);
    player.build();
    CHECK_NOTHROW(player.discover_cure(Color::Black)); // there is allready cure' but its ok.

    // Researcher can discover cure with out research stations
    Researcher researcher {board, City::Riyadh};
    researcher.build();
    researcher.take_card(City::Manila);   // Red
    researcher.take_card(City::Seoul);   // Red
    researcher.take_card(City::Shanghai);   // Red
    researcher.take_card(City::Taipei);   // Red
    researcher.take_card(City::Tokyo);   // Red
    CHECK_NOTHROW(researcher.discover_cure(Color::Red));

    // Scientist can discober cure with n accurate cards:
    Scientist scientist {board, City::Washington, 1};
    scientist.take_card(City::Washington);  // Blue
    CHECK_NOTHROW(scientist.discover_cure(Color::Blue));
}

TEST_CASE("treat test - simple player:"){
    Board board;
    Player player {board, City::Bogota};

    CHECK_THROWS(player.treat(City::Bogota)); // no disease in the city
    board[City::Bogota] = 5;
    CHECK_NOTHROW(player.treat(City::Bogota));
    CHECK(board[City::Bogota] == 4);
    
    Scientist scientist {board, City::Washington, 1};
    scientist.take_card(City::Bogota);
    scientist.discover_cure(Color::Yellow);
    CHECK_NOTHROW(player.treat(City::Bogota));
    CHECK(board[City::Bogota] == 0);   //there is a cure
}


TEST_CASE("treat test - Medic:"){ //Chicago
    Board board;
    Medic medic {board, City::Chicago};

    CHECK_THROWS(medic.treat(City::Chicago)); // no disease in the city
    board[City::Chicago] = 5;
    CHECK_NOTHROW(medic.treat(City::Chicago));
    CHECK(board[City::Chicago] == 0);     // medic treatment --> o disease
    
    Scientist scientist {board, City::Washington, 1};
    scientist.take_card(City::Miami);   //  Miami color - yellow
    scientist.discover_cure(Color::Yellow);
    board[City::LosAngeles] = 5;       //LosAngeles color - yellow
    CHECK(board[City::LosAngeles] == 5);
    medic.drive(City::LosAngeles); //LosAngeles and Chicago are cinnected
    CHECK(board[City::LosAngeles] == 0 );   // medic has got to the town:)

}


TEST_CASE("treat test - Virologist:"){
    Board board;
    Virologist virologist {board, City::Miami};

    board[City::Manila] = 5;     //  put 5 disease in Miami
    CHECK_THROWS(virologist.treat(City::Manila)); // no acurrate card

    virologist.take_card(City::Manila);
    CHECK_NOTHROW(virologist.treat(City::Manila));
    CHECK(board[City::Manila] == 4);
}

TEST_CASE("treat test - FieldDoctor:"){
    Board board;
    FieldDoctor fieldDoctor {board, City::Tokyo};

    CHECK_THROWS(fieldDoctor.treat(City::Osaka)); // no disease in Osaka
    board[City::Osaka] = 7;
    CHECK_NOTHROW(fieldDoctor.treat(City::Osaka));
    CHECK(board[City::Osaka] == 4);     // fieldDoctor can treat neigbord city
}