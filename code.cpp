#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Flight {
public:
    int flightNumber;
    string departure;
    string destination;
    int seatsAvailable;

    Flight(int flightNumber, string departure, string destination, int seatsAvailable)
        : flightNumber(flightNumber), departure(departure), destination(destination), seatsAvailable(seatsAvailable) {}
};

class Booking {
public:
    int bookingID;
    int flightNumber;
    string passengerName;

    Booking(int bookingID, int flightNumber, string passengerName)
        : bookingID(bookingID), flightNumber(flightNumber), passengerName(passengerName) {}
};

class AirlineBookingSystem {
    vector<Flight> flights;
    vector<Booking> bookings;
    int nextBookingID;

public:
    AirlineBookingSystem() : nextBookingID(1) {}

    void addFlight(int flightNumber, string departure, string destination, int seatsAvailable) {
        flights.push_back(Flight(flightNumber, departure, destination, seatsAvailable));
    }

    void searchFlights(string departure, string destination) {
        cout << "Available flights from " << departure << " to " << destination << ":\n";
        bool found = false;
        for (const auto& flight : flights) {
            if (flight.departure == departure && flight.destination == destination) {
                cout << "Flight Number: " << flight.flightNumber << ", Seats Available: " << flight.seatsAvailable << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No flights available for the selected route.\n";
        }
    }

    void bookTicket(int flightNumber, string passengerName) {
        for (auto& flight : flights) {
            if (flight.flightNumber == flightNumber) {
                if (flight.seatsAvailable > 0) {
                    flight.seatsAvailable--;
                    bookings.push_back(Booking(nextBookingID++, flightNumber, passengerName));
                    cout << "Ticket booked successfully! Booking ID: " << nextBookingID - 1 << endl;
                } else {
                    cout << "No seats available on this flight.\n";
                }
                return;
            }
        }
        cout << "Flight number not found.\n";
    }

    void cancelBooking(int bookingID) {
        auto it = find_if(bookings.begin(), bookings.end(), [=](const Booking& b) { return b.bookingID == bookingID; });
        if (it != bookings.end()) {
            for (auto& flight : flights) {
                if (flight.flightNumber == it->flightNumber) {
                    flight.seatsAvailable++;
                    break;
                }
            }
            bookings.erase(it);
            cout << "Booking canceled successfully.\n";
        } else {
            cout << "Booking ID not found.\n";
        }
    }

    void checkTicketStatus(int bookingID) {
        auto it = find_if(bookings.begin(), bookings.end(), [=](const Booking& b) { return b.bookingID == bookingID; });
        if (it != bookings.end()) {
            cout << "Booking ID: " << it->bookingID << ", Flight Number: " << it->flightNumber << ", Passenger Name: " << it->passengerName << endl;
        } else {
            cout << "Booking ID not found.\n";
        }
    }

    void displayFlights() {
        cout << "Flight Information:\n";
        for (const auto& flight : flights) {
            cout << "Flight Number: " << flight.flightNumber << ", Departure: " << flight.departure << ", Destination: " << flight.destination << ", Seats Available: " << flight.seatsAvailable << endl;
        }
    }
};

int main() {
    AirlineBookingSystem system;

    // Adding some sample flights
    system.addFlight(101, "New York", "Los Angeles", 50);
    system.addFlight(102, "New York", "Chicago", 30);
    system.addFlight(103, "Los Angeles", "Chicago", 20);
    system.addFlight(104, "Chicago", "New York", 15);

    int choice;
    do {
        cout << "\n--- Airline Flight Booking System ---\n";
        cout << "1. Search Flights\n";
        cout << "2. Book Ticket\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Check Ticket Status\n";
        cout << "5. Display All Flights\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string departure, destination;
            cout << "Enter departure location: ";
            cin >> departure;
            cout << "Enter destination location: ";
            cin >> destination;
            system.searchFlights(departure, destination);
            break;
        }
        case 2: {
            int flightNumber;
            string passengerName;
            cout << "Enter flight number: ";
            cin >> flightNumber;
            cout << "Enter passenger name: ";
            cin >> passengerName;
            system.bookTicket(flightNumber, passengerName);
            break;
        }
        case 3: {
            int bookingID;
            cout << "Enter booking ID: ";
            cin >> bookingID;
            system.cancelBooking(bookingID);
            break;
        }
        case 4: {
            int bookingID;
            cout << "Enter booking ID: ";
            cin >> bookingID;
            system.checkTicketStatus(bookingID);
            break;
        }
        case 5:
            system.displayFlights();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
