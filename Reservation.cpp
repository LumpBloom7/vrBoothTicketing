#include <chrono>
#include <iomanip>
#include <ctime>
#include <cmath>

namespace booth {
  int guestCount = 0;
  class Reservation {
  public:
    Reservation();
    Reservation( std::chrono::system_clock::time_point &startTime, std::string &name, std::string &contactDetails,
                 int &computerNumber )
        : startTime( startTime ), name( name ), contactDetails( contactDetails ), computerNumber( computerNumber ),
          verificationCode( 0 ) {
      logFile( "Initialized variables with user data.", 2 );
      guestCount++;
      logFile( "Incrementing guest counter.", 2 );
      guestNumber = guestCount;
      logFile( "Assigning current number to user.", 2 );
      endTime = startTime + std::chrono::seconds( 900 );
      logFile( "Calculated user end time.", 2 );
      // Generate random verification code here.
      logFile( "Generating verification code.", 2 );
      for ( char i : name ) verificationCode += pow( int( i ), 2 );
      logFile( "Successfully generated verification code.", 2 );
    }
    std::string name;
    std::chrono::system_clock::time_point startTime;
    std::string contactDetails{""};
    int verificationCode = 0;
    std::chrono::system_clock::time_point endTime = startTime + std::chrono::seconds( 900 );
    int computerNumber;
    int guestNumber;
  };
  std::vector<Reservation> guests{};
  std::vector<std::vector<Reservation>> computers = std::vector<std::vector<Reservation>>( 4 );

  void addReservation() {
    logFile( "Entered reservation screen.", 0 );
    cligCore::console::clear();
    std::string name = "";
    std::cout << "Please input the customer's english or romanised name. Leave blank to cancel." << std::endl;
    std::getline( std::cin, name );
    if ( name == "" ) {
      logFile( "Reservation process failed. (Cancelled by user)", 0 );
      return;
    }
    logFile( "Successfully retrieved name from input.", 1 );
    std::cout << "Please enter one or more way to contact you(Phone, Email; Seperated by commas)." << std::endl;
    std::string contactDetails;
    std::cin >> contactDetails;
    logFile( "Successfully retrieved contact info from input.", 1 );
    std::chrono::system_clock::time_point currentTime =
        std::chrono::ceil<std::chrono::minutes>( std::chrono::system_clock::now() );
    logFile( "Successfully retrieved current system time.", 1 );
    bool init = false;
    int smallestNumber;
    logFile( "Finding suitable computer for user.", 1 );
    for ( int i = 0; i < 4; i++ ) {
      if ( computers[ i ].size() == 0 ) {
        smallestNumber = i;
        break;
      } else {
        if ( i == 0 )
          smallestNumber = i;
        else {
          if ( computers[ i ][ computers[ i ].size() - 1 ].endTime <
               computers[ smallestNumber ][ computers[ smallestNumber ].size() - 1 ].endTime )
            smallestNumber = i;
        }
      }
    }
    logFile( "Found suitable computer for user.", 1 );
    logFile( "Assigning time slot for user.", 1 );
    std::chrono::system_clock::time_point startTime;
    if ( computers[ smallestNumber ].size() == 0 )
      startTime = currentTime;
    else if ( computers[ smallestNumber ][ computers[ smallestNumber ].size() - 1 ].endTime < currentTime )
      startTime = currentTime;
    else
      startTime = computers[ smallestNumber ][ computers[ smallestNumber ].size() - 1 ].endTime;
    logFile( "Successfully assigned time slot for user.", 1 );
    logFile( "Placing user data into \"Reservation\" data type", 1 );
    Reservation guest = Reservation( startTime, name, contactDetails, smallestNumber );
    logFile( "Successfully placed user data into \"Reservation\" data type", 1 );

    logFile( "Adding user to the guest list", 1 );
    computers[ smallestNumber ].emplace_back( guest );
    guests.emplace_back( guest );
    logFile( "Successfully Added user to the guest list", 1 );

    logFile( "Outputting user data to screen.", 1 );
    cligCore::console::clear();
    std::time_t start = std::chrono::system_clock::to_time_t( guest.startTime );
    std::time_t end = std::chrono::system_clock::to_time_t( guest.endTime );
    std::cout << "Successfully found a suitable time for your session." << std::endl;
    std::cout << "Please write this down..." << std::endl
              << termcolor::cyan << "User name: " << guest.name << std::endl
              << "User number: " << guest.guestNumber << std::endl
              << "Computer number: " << guest.computerNumber << std::endl
              << "Verification code: " << guest.verificationCode << std::endl
              << std::endl
              << "Start time: " << std::put_time( std::localtime( &start ), "%H:%M" ) << std::endl
              << "End time: " << std::put_time( std::localtime( &end ), "%H:%M" ) << std::endl
              << std::endl
              << "It is recommended that you arrive at least 5 minutes before your start time." << std::endl
              << "Failure to arrive on time may result in your play session being shorter" << std::endl;
    std::cin.ignore();
    std::cin.ignore();
    logFile( "Reservation successful!", 0 );
  }
  int inputCheck() {
    if ( std::cin.fail() ) {
      std::cin.clear();
      std::cin.ignore();
      std::cin.ignore();
      std::string tmp;
      std::cout << termcolor::red << "Invalid input entered, returning to main menu." << std::endl;
      logFile( "Verification failed. (Invalid input)", 1 );
      logFile( "Verification screen closed.", 0 );
      std::getline( std::cin, tmp );
      return -1;
    }
    return 0;
  }
  void verifyCode() {
    logFile( "Entered verification screen.", 0 );
    cligCore::console::clear();
    logFile( "Requesting user input.", 1 );
    int userNumber;
    std::cout << "Please enter your user number: " << termcolor::green << std::flush;
    std::cin >> userNumber;
    if ( inputCheck() == -1 ) { return; }
    logFile( "Received user number.", 2 );

    int computerNumber;
    std::cout << termcolor::reset << "Please enter your computer number: " << termcolor::green << std::flush;
    std::cin >> computerNumber;
    if ( inputCheck() == -1 ) { return; }
    logFile( "Received computer number.", 2 );
    int verificationCode;
    std::cout << termcolor::reset << "Please enter your verification code: " << termcolor::green << std::flush;
    std::cin >> verificationCode;
    if ( inputCheck() == -1 ) { return; }
    logFile( "Received verification code.", 2 );

    logFile( "Checking if information is valid.", 1 );
    cligCore::console::clear();
    if ( userNumber > 0 && guests.size() >= userNumber ) {
      if ( guests[ userNumber - 1 ].verificationCode == verificationCode &&
           computerNumber == guests[ userNumber - 1 ].computerNumber ) {
        std::cout << "Verification Successful." << std::endl;
        if ( guests[ userNumber - 1 ].startTime - std::chrono::system_clock::now() > std::chrono::minutes( 10 ) ) {
          std::cout << "But it is a bit early don't you think?" << std::endl
                    << "Please try again later, preferably about 5 minutes before your start time." << std::endl;
          logFile( "Verification failed. (User arrived too early)", 2 );
        } else {
          std::cout << "A staff member will now guide you to your computer" << std::endl;
          logFile( "Verification successful.", 2 );
        }
      } else {
        std::cout << "Verification failed." << std::endl
                  << "One or more of the inputted values are incorrect" << std::endl;
        logFile( "Verification failed1. (Incorrect info)", 2 );
      }
    } else {
      std::cout << "Verification failed." << std::endl
                << "One or more of the inputted values are incorrect" << std::endl;
      logFile( "Verification failed2. (Incorrect info)", 2 );
    }
    logFile( "Finished checking.", 1 );

    std::cin.ignore();
    std::cin.ignore();
    logFile( "Verification screen closed.", 0 );
  }
} // namespace booth