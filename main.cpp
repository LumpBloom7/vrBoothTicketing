#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

void logFile( const std::string &logMessage, int depth );
#include "cereal/types/vector.hpp"
#include "cereal/types/chrono.hpp"
#include "cereal/types/string.hpp"
#include "cereal/archives/json.hpp"

#include "cligcore/clig.cpp"
#include "Reservation.cpp"

std::ofstream flog( "runtime.log" );
bool justStarted = true;

void logFile( const std::string &logMessage, int depth ) {
  std::string indent = "";
  for ( int i = 0; i < depth; i++ ) indent += "  ";
  std::time_t logTime = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
  flog << std::put_time( std::localtime( &logTime ), "%H:%M:%S" ) << " - " << indent << logMessage << std::endl;
}

void about() {
  logFile( "Entered about screen.", 0 );
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
  logFile( "About screen closed.", 0 );
}
int main() {
  if ( cligCore::filesystem::fileExists( "computers.json" ) && cligCore::filesystem::fileExists( "guests.json" ) )
    booth::load();
  if ( justStarted ) {
    logFile( "Program started", 0 );
    justStarted = false;
  }
  logFile( "Main menu shown.", 0 );
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
