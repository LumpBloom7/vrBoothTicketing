#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "cligcore/clig.cpp"
#include "Reservation.cpp"

int main() {
  while ( true ) {
    std::vector<std::string> menuContent{"1. Add entry", "2. Code Verification", "3. About", "4. Quit"};
    std::cout << "VR Booth Ticketing" << std::endl;
    int result = cligCore::menu::createMenu( "Please select an action", menuContent, false );
    switch ( result ) {
    case 0: booth::addReservation(); break;
    case 1: booth::verifyCode(); break;
    case 2: main(); break;
    case 3: exit( 0 );
    }
  }
}
