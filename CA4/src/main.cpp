
#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Farmer {
private:
    int farmerId;
    string name;
    string village;
    double landArea;
    string cropType;

    static int farmerCount;

public:
    Farmer() {
        this->farmerId = 0;
        this->name = "";
        this->village = "";
        this->landArea = 0;
        this->cropType = "";
    }

    inline int getFarmerId() const {
        return this->farmerId;
    }

    static int getFarmerCount() {
        return farmerCount;
    }

    bool isValid() const {
        return farmerId > 0 &&
               !name.empty() &&
               !village.empty() &&
               landArea > 0 &&
               !cropType.empty();
    }

    void inputDetails(int id) {
        this->farmerId = id;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter farmer name: ";
        getline(cin, this->name);

        cout << "Enter village name: ";
        getline(cin, this->village);

        cout << "Enter land area in acres: ";

        if (!(cin >> this->landArea)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            this->landArea = 0;
            this->farmerId = 0;
            cout << "Invalid land area. Registration cancelled.\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter crop type: ";
        getline(cin, this->cropType);

        if (!isValid()) {
            cout << "Invalid details. Registration cancelled.\n";
            this->farmerId = 0;
            return;
        }

        farmerCount++;
        cout << "Farmer registered successfully!\n";
    }

    void displayDetails() const {
        if (!isValid()) {
            return;
        }

        cout << "\nFarmer ID: " << farmerId;
        cout << "\nName: " << name;
        cout << "\nVillage: " << village;
        cout << "\nLand Area: " << landArea << " acres";
        cout << "\nCrop: " << cropType << "\n";
    }

    friend void showFarmerSummary(const Farmer& f);
};

int Farmer::farmerCount = 0;

void showFarmerSummary(const Farmer& f) {
    if (!f.isValid()) {
        cout << "Invalid farmer record.\n";
        return;
    }

    cout << "\n--- Farmer Summary ---\n";
    cout << "ID: " << f.farmerId;
    cout << "\nName: " << f.name;
    cout << "\nVillage: " << f.village << "\n";
}

class IrrigationTurn {
private:
    int turnId;
    int farmerId;
    string waterSource;
    string turnDate;
    int startHour;
    int durationHours;

    static int turnCount;

public:
    IrrigationTurn() {
        this->turnId = 0;
        this->farmerId = 0;
        this->waterSource = "";
        this->turnDate = "";
        this->startHour = 0;
        this->durationHours = 0;
    }

    int getTurnId() const {
        return this->turnId;
    }

    int getFarmerId() const {
        return this->farmerId;
    }

    string getWaterSource() const {
        return this->waterSource;
    }

    string getTurnDate() const {
        return this->turnDate;
    }

    int getStartHour() const {
        return this->startHour;
    }

    int getDurationHours() const {
        return this->durationHours;
    }

    int getEndHour() const {
        return this->startHour + this->durationHours;
    }

    static int getTurnCount() {
        return turnCount;
    }

    bool isValid() const {
        return turnId > 0 &&
               farmerId > 0 &&
               !waterSource.empty() &&
               !turnDate.empty() &&
               startHour >= 0 &&
               startHour < 24 &&
               durationHours > 0 &&
               durationHours <= 24 &&
               startHour + durationHours <= 24;
    }

    void inputDetails(int id, int fId) {
        this->turnId = id;
        this->farmerId = fId;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter water source (canal/well): ";
        getline(cin, this->waterSource);

        cout << "Enter date (DD-MM-YYYY): ";
        getline(cin, this->turnDate);

        cout << "Enter starting hour (0-23): ";

        if (!(cin >> this->startHour)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            this->turnId = 0;
            cout << "Invalid start hour. Turn cancelled.\n";
            return;
        }

        cout << "Enter duration in hours (1-24): ";

        if (!(cin >> this->durationHours)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            this->turnId = 0;
            cout << "Invalid duration. Turn cancelled.\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!isValid()) {
            cout << "Invalid turn details. Turn cancelled.\n";
            this->turnId = 0;
            return;
        }

        turnCount++;
        cout << "Irrigation turn added successfully!\n";
    }

    void displayTurn() const {
        if (!isValid()) {
            return;
        }

        cout << "\nTurn ID: " << turnId;
        cout << "\nFarmer ID: " << farmerId;
        cout << "\nWater Source: " << waterSource;
        cout << "\nDate: " << turnDate;
        cout << "\nStart Hour: " << startHour << ":00";
        cout << "\nEnd Hour: " << getEndHour() << ":00";
        cout << "\nDuration: " << durationHours << " hour(s)\n";
    }
};

int IrrigationTurn::turnCount = 0;

int main() {
    const int MAX_FARMERS = 100;
    const int MAX_TURNS = 200;

    Farmer farmers[MAX_FARMERS];
    IrrigationTurn turns[MAX_TURNS];

    Farmer* farmerPointer = farmers;
    IrrigationTurn* turnPointer = turns;

    int totalFarmers = 0;
    int totalTurns = 0;
    int choice = 0;

    do {
        cout << "\n========================================\n";
        cout << "   RURAL IRRIGATION TURN ALLOCATION\n";
        cout << "========================================\n";
        cout << "1. Register Farmer\n";
        cout << "2. Display All Farmers\n";
        cout << "3. Search Farmer by ID\n";
        cout << "4. Add Irrigation Turn\n";
        cout << "5. Display All Irrigation Turns\n";
        cout << "6. Search Turn by ID\n";
        cout << "7. Show Total Farmers and Turns\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a numeric menu choice.\n";
            continue;
        }

        if (choice == 1) {
            if (totalFarmers >= MAX_FARMERS) {
                cout << "Farmer storage is full!\n";
                continue;
            }

            int id;
            cout << "Enter unique Farmer ID: ";

            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Farmer ID.\n";
                continue;
            }

            bool duplicate = false;

            for (int i = 0; i < totalFarmers; i++) {
                if (farmerPointer[i].getFarmerId() == id) {
                    duplicate = true;
                    break;
                }
            }

            if (id <= 0) {
                cout << "Farmer ID must be positive.\n";
            } else if (duplicate) {
                cout << "Farmer ID already exists!\n";
            } else {
                farmers[totalFarmers].inputDetails(id);

                if (farmers[totalFarmers].isValid()) {
                    totalFarmers++;
                }
            }
        }

        else if (choice == 2) {
            if (totalFarmers == 0) {
                cout << "No farmers registered.\n";
            }

            for (int i = 0; i < totalFarmers; i++) {
                farmerPointer[i].displayDetails();
            }
        }

        else if (choice == 3) {
            int id;
            bool found = false;

            cout << "Enter Farmer ID to search: ";

            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID.\n";
                continue;
            }

            for (int i = 0; i < totalFarmers; i++) {
                if (farmerPointer[i].getFarmerId() == id) {
                    farmerPointer[i].displayDetails();
                    showFarmerSummary(farmerPointer[i]);
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Farmer not found!\n";
            }
        }

        else if (choice == 4) {
            if (totalTurns >= MAX_TURNS) {
                cout << "Turn storage is full!\n";
                continue;
            }

            int turnId;
            int farmerId;

            cout << "Enter unique Turn ID: ";

            if (!(cin >> turnId)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Turn ID.\n";
                continue;
            }

            bool duplicateTurn = false;

            for (int i = 0; i < totalTurns; i++) {
                if (turnPointer[i].getTurnId() == turnId) {
                    duplicateTurn = true;
                    break;
                }
            }

            if (turnId <= 0 || duplicateTurn) {
                cout << "Turn ID must be positive and unique.\n";
                continue;
            }

            cout << "Enter Farmer ID for this turn: ";

            if (!(cin >> farmerId)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Farmer ID.\n";
                continue;
            }

            bool farmerFound = false;

            for (int i = 0; i < totalFarmers; i++) {
                if (farmerPointer[i].getFarmerId() == farmerId) {
                    farmerFound = true;
                    break;
                }
            }

            if (!farmerFound) {
                cout << "Register the farmer before allocating a turn.\n";
                continue;
            }

            turns[totalTurns].inputDetails(turnId, farmerId);

            if (!turns[totalTurns].isValid()) {
                continue;
            }

            bool overlap = false;

            for (int i = 0; i < totalTurns; i++) {
                if (turnPointer[i].getWaterSource() ==
                        turns[totalTurns].getWaterSource() &&
                    turnPointer[i].getTurnDate() ==
                        turns[totalTurns].getTurnDate()) {

                    int newStart = turns[totalTurns].getStartHour();
                    int newEnd = turns[totalTurns].getEndHour();

                    int oldStart = turnPointer[i].getStartHour();
                    int oldEnd = turnPointer[i].getEndHour();

                    if (newStart < oldEnd && oldStart < newEnd) {
                        overlap = true;
                        break;
                    }
                }
            }

            if (overlap) {
                cout << "Time conflict! This water source is already allocated during that period.\n";
                cout << "Please add the turn again with a different ID or time.\n";
                continue;
            }

            totalTurns++;
            cout << "Turn allocated successfully.\n";
        }

        else if (choice == 5) {
            if (totalTurns == 0) {
                cout << "No irrigation turns available.\n";
            }

            for (int i = 0; i < totalTurns; i++) {
                turnPointer[i].displayTurn();
            }
        }

        else if (choice == 6) {
            int id;
            bool found = false;

            cout << "Enter Turn ID to search: ";

            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Turn ID.\n";
                continue;
            }

            for (int i = 0; i < totalTurns; i++) {
                if (turnPointer[i].getTurnId() == id) {
                    turnPointer[i].displayTurn();
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Irrigation turn not found!\n";
            }
        }

        else if (choice == 7) {
            cout << "Total farmers registered: "
                 << Farmer::getFarmerCount() << "\n";

            cout << "Total irrigation turns: "
                 << IrrigationTurn::getTurnCount() << "\n";
        }

        else if (choice == 8) {
            cout << "Thank you for using the system made by Nishant Kumar!\n";
        }

        else {
            cout << "Invalid choice. Select 1 to 8.\n";
        }

    } while (choice != 8);

    return 0;
}
