#include <iostream>
#include <string>
#include <vector>

#include "cligcore/clig.cpp"

int main() {
  std::vector<std::string> menuContent{"1. Add entry", "2. Remove entry", "3. Code Verification", "4. About",
                                       "5. Quit"};

  std::cout << "VR Booth Ticketing" << std::endl;
  int result = cligCore::menu::createMenu( "Please select an action", menuContent, false );
  switch ( result ) {
  case 0:
  case 1:
  case 2:
  case 3: main(); break;
  case 4: exit( 0 );
  }
}
