#include <chrono>
#include <iomanip>
#include <ctime>

namespace booth {
  int guestCount = 0;
  class Reservation {
  public:
    Reservation();
    Reservation( std::chrono::system_clock::time_point &startTime, std::string &name, std::string &contactDetails,
                 int &computerNumber )
        : startTime( startTime ), name( name ), contactDetails( contactDetails ), computerNumber( computerNumber ),
          verificationCode( 0 ) {
      guestCount++;
      guestNumber = guestCount;
      endTime = startTime + std::chrono::seconds( 900 );
      // Generate random verification code here.
      for ( char i : name ) verificationCode += pow( int( i ), 2 );
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

  void addReservation() { /*
     if ( guestCount == 0 ) {
       timeZero = timer.count<std::chrono::seconds>();
       startTime = std::chrono::system_clock::now();
     }*/
    cligCore::console::clear();
    std::string name = "";
    std::cout << "Please input the customer's english or romanised name." << std::endl;
    while ( name == "" ) { std::getline( std::cin, name ); }
    std::cout << "Please enter one or more way to contact you(Phone, Email; Seperated by commas)." << std::endl;
    std::string contactDetails;
    std::cin >> contactDetails;
    std::clog << "1";
    std::chrono::system_clock::time_point currentTime =
        std::chrono::ceil<std::chrono::minutes>( std::chrono::system_clock::now() );
    std::clog << "2";
    bool init = false;
    int smallestNumber;
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
    std::chrono::system_clock::time_point startTime;
    if ( computers[ smallestNumber ].size() == 0 )
      startTime = currentTime;
    else if ( computers[ smallestNumber ][ computers[ smallestNumber ].size() - 1 ].endTime < currentTime )
      startTime = currentTime;
    else
      startTime = computers[ smallestNumber ][ computers[ smallestNumber ].size() - 1 ].endTime;

    Reservation guest = Reservation( startTime, name, contactDetails, smallestNumber );

    computers[ smallestNumber ].emplace_back( guest );
    guests.emplace_back( guest );

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
  }

  void verifyCode() {
    cligCore::console::clear();
    int userNumber;
    std::cout << "Please enter your user number: " << termcolor::green << std::flush;
    std::cin >> userNumber;

    int computerNumber;
    std::cout << termcolor::reset << "Please enter your computer number: " << termcolor::green << std::flush;
    std::cin >> computerNumber;

    int verificationCode;
    std::cout << termcolor::reset << "Please enter your verification code: " << termcolor::green << std::flush;
    std::cin >> verificationCode;

    cligCore::console::clear();
    if ( userNumber > 0 && guests.size() >= userNumber )
      if ( guests[ userNumber - 1 ].verificationCode == verificationCode &&
           computerNumber == guests[ userNumber - 1 ].computerNumber ) {
        std::cout << "Verification Successful." << std::endl;
        if ( guests[ userNumber - 1 ].startTime - std::chrono::system_clock::now() > std::chrono::minutes( 10 ) ) {
          std::cout << "But it is a bit early don't you think?" << std::endl
                    << "Please try again later, preferably about 5 minutes before your start time." << std::endl;
        } else
          std::cout << "A staff member will now guide you to your computer" << std::endl;
      }

      else
        std::cout << "Verification failed." << std::endl
                  << "One or more of the inputted values are incorrect" << std::endl;
    else
      std::cout << "Verification failed." << std::endl
                << "One or more of the inputted values are incorrect" << std::endl;

    std::cin.ignore();
    std::cin.ignore();
  }
} // namespace booth