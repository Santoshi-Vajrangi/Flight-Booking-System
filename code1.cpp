 #include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Abstract Base Flight class (encapsulation and abstraction)
class Flight {
public:
    int flightNumber;
    string departure;
    string destination;
    int seatsAvailable;

    Flight(int flightNumber, string departure, string destination, int seatsAvailable)
        : flightNumber(flightNumber), departure(departure), destination(destination), seatsAvailable(seatsAvailable) {}

    // Pure virtual function for flight type
    virtual string getAirlineName() = 0;

    virtual void displayInfo() {
        cout << "Flight Number: " << flightNumber 
             << ", Airline: " << getAirlineName() 
             << ", Departure: " << departure 
             << ", Destination: " << destination 
             << ", Seats Available: " << seatsAvailable << endl;
    }

    virtual ~Flight() {}
};

// Derived class: AirIndia
class AirIndia : public Flight {
public:
    AirIndia(int flightNumber, string departure, string destination, int seatsAvailable)
        : Flight(flightNumber, departure, destination, seatsAvailable) {}

    string getAirlineName() override {
        return "Air India";
    }
};

// Derived class: Vistara
class Vistara : public Flight {
public:
    Vistara(int flightNumber, string departure, string destination, int seatsAvailable)
        : Flight(flightNumber, departure, destination, seatsAvailable) {}

    string getAirlineName() override {
        return "Vistara";
    }
};

// Derived class: Indigo
class Indigo : public Flight {
public:
    Indigo(int flightNumber, string departure, string destination, int seatsAvailable)
        : Flight(flightNumber, departure, destination, seatsAvailable) {}

    string getAirlineName() override {
        return "Indigo";
    }
};

// Booking class for managing ticket bookings (encapsulation)
class Booking {
public:
    int bookingID;
    int flightNumber;
    string passengerName;

    Booking(int bookingID, int flightNumber, string passengerName)
        : bookingID(bookingID), flightNumber(flightNumber), passengerName(passengerName) {}
};

// AirlineBookingSystem class for managing flights and bookings
class AirlineBookingSystem {
    vector<Flight*> flights; // Using pointers to handle polymorphism
    vector<Booking> bookings;
    int nextBookingID;

public:
    AirlineBookingSystem() : nextBookingID(1) {}

    // Adding flights (Air India, Vistara, Indigo)
    void addFlight(Flight* flight) {
        flights.push_back(flight);
    }

    // Searching flights based on departure and destination
    void searchFlights(string departure, string destination) {
        cout << "Available flights from " << departure << " to " << destination << ":\n";
        bool found = false;
        for (const auto& flight : flights) {
            if (flight->departure == departure && flight->destination == destination) {
                flight->displayInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "No flights available for the selected route.\n";
        }
    }

    // Booking a ticket for a passenger
    void bookTicket(int flightNumber, string passengerName) {
        for (auto& flight : flights) {
            if (flight->flightNumber == flightNumber && flight->seatsAvailable > 0) {
                flight->seatsAvailable--;
                bookings.push_back(Booking(nextBookingID++, flightNumber, passengerName));
                cout << "Ticket booked successfully! Booking ID: " << nextBookingID - 1 << endl;
                return;
            }
        }
        cout << "Flight number not found or no seats available.\n";
    }

    // Canceling a booking
    void cancelBooking(int bookingID) {
        auto it = find_if(bookings.begin(), bookings.end(), [=](const Booking& b) { return b.bookingID == bookingID; });
        if (it != bookings.end()) {
            for (auto& flight : flights) {
                if (flight->flightNumber == it->flightNumber) {
                    flight->seatsAvailable++;
                    break;
                }
            }
            bookings.erase(it);
            cout << "Booking canceled successfully.\n";
        } else {
            cout << "Booking ID not found.\n";
        }
    }

    // Checking the status of a booking
    void checkTicketStatus(int bookingID) {
        auto it = find_if(bookings.begin(), bookings.end(), [=](const Booking& b) { return b.bookingID == bookingID; });
        if (it != bookings.end()) {
            cout << "Booking ID: " << it->bookingID << ", Flight Number: " << it->flightNumber << ", Passenger Name: " << it->passengerName << endl;
        } else {
            cout << "Booking ID not found.\n";
        }
    }

    // Display all flights with their details (polymorphism at work)
    void displayFlights() {
        cout << "Flight Information:\n";
        for (const auto& flight : flights) {
            flight->displayInfo();
        }
    }
};

// Main program
int main() {
    AirlineBookingSystem system;

    // Adding flights for AirIndia, Vistara, and Indigo (inheritance and polymorphism)
    system.addFlight(new AirIndia(101, "New York", "Los Angeles", 50));
    system.addFlight(new Vistara(102, "New York", "Chicago", 30));
    system.addFlight(new Indigo(103, "Los Angeles", "Chicago", 20));

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
