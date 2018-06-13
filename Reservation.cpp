#include "booth.hpp"
namespace booth {
  int guestCount = 0;
  class Reservation {
  public:
    Reservation();
    Reservation( int startTime, std::string contactDetails, int computerNumber )
        : startTime( startTime ), contactDetails( contactDetails ), computerNumber( computerNumber ) {
      guestCount++;
      guestNumber = guestCount;
      endTime = startTime + 15;
      // Generate random verification code here.
    }
    int startTime;
    std::string contactDetails{""};
    int verificationCode;
    int endTime = startTime + 15;
    int computerNumber;
    int guestNumber;
  };
  std::vector<Reservation> guests{};
  std::vector<std::vector<Reservation>> computers{};

  void addReservation() {
    cligCore::console::clear();
    std::string name;
    std::cout << "Please input the customer's english or romanised name." << std::endl;
    std::cin >> name;
    int computerNumber;
    bool init = false;
    int smallestComputer;
    int computerSize;
    for ( int i = 3; i >= 0; i-- ) {
      if ( !init ) {
        smallestComputer = i;
        computerSize = computers[ i ].size();
      } else {
        if ( computers[ i ].size() <= computerSize ) {
          smallestComputer = i;
          computerSize = computers[ i ].size();
        }
      }
    }
    int startTime = computers[ smallestComputer ][ computerSize - 1 ].endTime;

    std::cout << "Successfully found a suitable time for your session." << std::endl
              << "Please enter one or more way to contact you(Phone, Email; Seperated by commas)." << std::endl;

    std::string contactDetails;
    std::cin >> contactDetails;

    Reservation guest = Reservation( startTime, contactDetails, smallestComputer );

    computers[ smallestComputer ].emplace_back( guest );
    guests.emplace_back( guest );

    cligCore::console::clear();

    std::cout << "Please write this down..." << std::endl
              << termcolor::cyan << "User number: " << guest.guestNumber << std::endl
              << "Computer number: " << guest.computerNumber << std::endl
              << "Verification code: " << guest.verificationCode << std::endl
              << std::endl
              << "Start time: " << guest.startTime << std::endl
              << "End time: " << guest.endTime << std::endl
              << std::endl
              << "It is recommended that you arrive at least 5 minutes before your start time. Failure to arrive on "
                 "time may result in your play session being shorter"
              << std::endl;
  }

  void verifyCode() {
    cligCore::console::clear();
    std::cin.ignore();
    int userNumber;
    std::cout << "Please enter your user number: " << termcolor::green << std::flush;
    std::cin >> userNumber;

    int computerNumber;
    std::cout << termcolor::reset << "Please enter your computer number: " << termcolor::green << std::flush;
    std::cin >> computerNumber;

    int verificationCode;
    std::cout << termcolor::reset << "Please enter your verification code: " << termcolor::green << std::flush;
    std::cin >> verificationCode;
  }
} // namespace booth