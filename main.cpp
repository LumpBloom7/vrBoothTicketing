#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "cligcore/clig.cpp"
#include "Reservation.cpp"

void about() {
  cligCore::console::clear();
  std::string tmp;
  std::cout << "Booth ticketing system for CHKL 2018 Festival" << std::endl
            << "Developed by the CHKL Computer Society under the MIT license." << std::endl
            << std::endl
            << "Git repository: https://github.com/LumpBloom7/VRBoothTicketing/" << std::endl
            << "Git Version: " << GIT_VERSION << std::endl
            << "Git Commit: " << GIT_COMMIT << std::endl
            << "Git Date: " << GIT_DATE << std::endl
            << "Build Date: " << BUILD_DATE << std::endl;

  std::getline( std::cin, tmp );
}
int main() {
  while ( true ) {
    std::vector<std::string> menuContent{"1. Add entry", "2. Code Verification", "3. About", "4. Quit"};
    std::cout << "VR Booth Ticketing" << std::endl;
    int result = cligCore::menu::createMenu( "Please select an action", menuContent, false );
    switch ( result ) {
    case 0: booth::addReservation(); break;
    case 1: booth::verifyCode(); break;
    case 2: about(); break;
    case 3: exit( 0 );
    }
  }
}
