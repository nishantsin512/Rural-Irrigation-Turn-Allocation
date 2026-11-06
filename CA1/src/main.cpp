
#include <iostream>
#include <string>
using namespace std;

class Farmer {
private:
    int farmerId;
    string name;
    string village;
    double landArea;
    string cropType;
    string waterSource;
    string turnDate;
    int startHour;
    int durationHours;
    char status;

    static int farmerCount;

public:

    void setDefaults() {
        this->farmerId = 0;
        this->name = "";
        this->village = "";
        this->landArea = 0;
        this->cropType = "";
        this->waterSource = "";
        this->turnDate = "";
        this->startHour = 0;
        this->durationHours = 0;
        this->status = 'N';
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
               !cropType.empty() &&
               !waterSource.empty() &&
               !turnDate.empty() &&
               startHour >= 0 &&
               startHour < 24 &&
               durationHours > 0 &&
               durationHours <= 24 &&
               startHour + durationHours <= 24;
    }

    void inputDetails(int id) {

        this->farmerId = id;

        cin.ignore();

        cout << "Enter farmer name: ";
        getline(cin, this->name);

        cout << "Enter village name: ";
        getline(cin, this->village);

        cout << "Enter land area in acres: ";

        if (!(cin >> this->landArea)) {
            cin.clear();
            cin.ignore(1000, '\n');
            this->farmerId = 0;
            cout << "Invalid land area.\n";
            return;
        }

        cin.ignore();

        cout << "Enter crop type: ";
        getline(cin, this->cropType);

        cout << "Enter water source (Canal/Well): ";
        getline(cin, this->waterSource);

        cout << "Enter irrigation date (DD-MM-YYYY): ";
        getline(cin, this->turnDate);

        cout << "Enter starting hour (0-23): ";

        if (!(cin >> this->startHour)) {
            cin.clear();
            cin.ignore(1000, '\n');
            this->farmerId = 0;
            cout << "Invalid starting hour.\n";
            return;
        }

        cout << "Enter duration in hours: ";

        if (!(cin >> this->durationHours)) {
            cin.clear();
            cin.ignore(1000, '\n');
            this->farmerId = 0;
            cout << "Invalid duration.\n";
            return;
        }

        if (!isValid()) {
            cout << "Invalid details. Registration cancelled.\n";
            this->farmerId = 0;
            return;
        }

        this->status = 'A';
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
        cout << "\nCrop Type: " << cropType;
        cout << "\nWater Source: " << waterSource;
        cout << "\nIrrigation Date: " << turnDate;
        cout << "\nStarting Hour: " << startHour << ":00";
        cout << "\nDuration: " << durationHours << " hours";
        cout << "\nStatus: " << status << "\n";
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
    cout << "Farmer ID: " << f.farmerId;
    cout << "\nName: " << f.name;
    cout << "\nVillage: " << f.village;
    cout << "\nWater Source: " << f.waterSource << "\n";
}

int main() {

    const int MAX = 50;

    Farmer arr[MAX];

    Farmer *ptr = arr;

    int total = 0;
    int choice = 0;

    for (int i = 0; i < MAX; i++) {
        arr[i].setDefaults();
    }

    do {

        cout << "\n================================\n";
        cout << " RURAL IRRIGATION TURN ALLOCATION\n";
        cout << "================================\n";

        cout << "1. Register Farmer\n";
        cout << "2. Display All Farmers\n";
        cout << "3. Search Farmer by ID\n";
        cout << "4. Show Total Farmers\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter a valid menu choice.\n";
            choice = 0;
            continue;
        }

        switch (choice) {

            case 1: {

                if (total >= MAX) {
                    cout << "Storage is full!\n";
                    break;
                }

                int id;
                int flag = 0;

                cout << "Enter unique Farmer ID: ";

                if (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid Farmer ID.\n";
                    break;
                }

                if (id <= 0) {
                    cout << "Farmer ID must be positive.\n";
                    break;
                }

                // check duplicate farmer ID
                for (int i = 0; i < total; i++) {

                    if (ptr[i].getFarmerId() == id) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 1) {
                    cout << "Farmer ID already exists!\n";
                }
                else {

                    arr[total].inputDetails(id);

                    if (arr[total].isValid()) {
                        total++;
                    }
                    else {
                        arr[total].setDefaults();
                    }
                }

                break;
            }

            case 2: {

                if (total == 0) {
                    cout << "No farmers registered.\n";
                }
                else {

                    for (int i = 0; i < total; i++) {
                        ptr[i].displayDetails();
                    }
                }

                break;
            }

            case 3: {

                int id;
                int found = 0;

                cout << "Enter Farmer ID to search: ";

                if (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid ID.\n";
                    break;
                }

                for (int i = 0; i < total; i++) {

                    if (ptr[i].getFarmerId() == id) {

                        ptr[i].displayDetails();

                        showFarmerSummary(ptr[i]);

                        found = 1;
                        break;
                    }
                }

                if (found == 0) {
                    cout << "Farmer not found!\n";
                }

                break;
            }

            case 4: {

                cout << "Total registered farmers: "
                     << Farmer::getFarmerCount() << "\n";

                break;
            }

            case 5: {

                cout << "Thank you for using Rural Irrigation Turn Allocation made by Nishant Kumar!\n";

                break;
            }

            default: {

                cout << "Invalid choice. Select 1 to 5.\n";

            }
        }

    } while (choice != 5);

    return 0;
}
