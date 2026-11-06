
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>
using namespace std;

// Fixed-size binary records
struct FarmerRecord {
    int id;
    char name[50];
    char village[50];
    double landArea;
    char crop[40];
};

struct TurnRecord {
    int turnId;
    int farmerId;
    char source[40];
    char date[20];
    int startHour;
    int duration;
};

// Safe string copy into fixed-size character arrays
void copyText(char* dest, const string& src, int size) {
    strncpy(dest, src.c_str(), size - 1);
    dest[size - 1] = '\0';
}

// ================= FARMER CLASS =================

class Farmer {
private:
    int id;
    string name, village, crop;
    double landArea;

    static int count;

public:

    // Default constructor
    Farmer() {
        id = 0;
        name = "";
        village = "";
        crop = "";
        landArea = 0;
    }

    // Parameterized constructor
    Farmer(int i, string n, string v, double a, string c) {
        id = i;
        name = n;
        village = v;
        landArea = a;
        crop = c;
    }

    // Copy constructor
    Farmer(const Farmer& f) {
        id = f.id;
        name = f.name;
        village = f.village;
        landArea = f.landArea;
        crop = f.crop;
    }

    // Destructor
    ~Farmer() {
    }

    int getId() const {
        return id;
    }

    static int getCount() {
        return count;
    }

    bool isValid() const {
        return id > 0 && !name.empty() &&
               !village.empty() && landArea > 0 &&
               !crop.empty();
    }

    void input(int farmerId) {
        id = farmerId;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter name: ";
        getline(cin, name);

        cout << "Enter village: ";
        getline(cin, village);

        cout << "Enter land area: ";
        if (!(cin >> landArea)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            id = 0;
            cout << "Invalid land area.\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter crop: ";
        getline(cin, crop);

        if (!isValid()) {
            id = 0;
            cout << "Invalid farmer details.\n";
            return;
        }

        count++;
    }

    void display() const {
        cout << "\nFarmer ID: " << id;
        cout << "\nName: " << name;
        cout << "\nVillage: " << village;
        cout << "\nLand: " << landArea << " acres";
        cout << "\nCrop: " << crop << "\n";
    }

    FarmerRecord toRecord() const {
        FarmerRecord r{};
        r.id = id;
        copyText(r.name, name, 50);
        copyText(r.village, village, 50);
        r.landArea = landArea;
        copyText(r.crop, crop, 40);
        return r;
    }

    void fromRecord(const FarmerRecord& r) {
        id = r.id;
        name = r.name;
        village = r.village;
        landArea = r.landArea;
        crop = r.crop;
    }

    void update() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "New name: ";
        getline(cin, name);

        cout << "New village: ";
        getline(cin, village);

        cout << "New land area: ";
        if (!(cin >> landArea)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            landArea = 0;
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "New crop: ";
        getline(cin, crop);
    }
};

int Farmer::count = 0;

// ================= IRRIGATION TURN CLASS =================

class IrrigationTurn {
private:
    int turnId, farmerId;
    string source, date;
    int startHour, duration;

public:

    // Default constructor
    IrrigationTurn() {
        turnId = 0;
        farmerId = 0;
        source = "";
        date = "";
        startHour = 0;
        duration = 0;
    }

    // Parameterized constructor
    IrrigationTurn(int t, int f, string s, string d,
                   int h, int durationHours) {
        turnId = t;
        farmerId = f;
        source = s;
        date = d;
        startHour = h;
        duration = durationHours;
    }

    // Copy constructor
    IrrigationTurn(const IrrigationTurn& t) {
        turnId = t.turnId;
        farmerId = t.farmerId;
        source = t.source;
        date = t.date;
        startHour = t.startHour;
        duration = t.duration;
    }

    // Destructor
    ~IrrigationTurn() {
    }

    int getId() const {
        return turnId;
    }

    bool isValid() const {
        return turnId > 0 && farmerId > 0 &&
               !source.empty() && !date.empty() &&
               startHour >= 0 && startHour < 24 &&
               duration > 0 && duration <= 24 &&
               startHour + duration <= 24;
    }

    void input(int t, int f) {
        turnId = t;
        farmerId = f;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter water source: ";
        getline(cin, source);

        cout << "Enter date (DD-MM-YYYY): ";
        getline(cin, date);

        cout << "Enter starting hour (0-23): ";
        if (!(cin >> startHour)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            turnId = 0;
            return;
        }

        cout << "Enter duration in hours: ";
        if (!(cin >> duration)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            turnId = 0;
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!isValid()) {
            turnId = 0;
            cout << "Invalid turn details.\n";
        }
    }

    void display() const {
        cout << "\nTurn ID: " << turnId;
        cout << "\nFarmer ID: " << farmerId;
        cout << "\nWater Source: " << source;
        cout << "\nDate: " << date;
        cout << "\nStart: " << startHour << ":00";
        cout << "\nEnd: " << startHour + duration << ":00";
        cout << "\nDuration: " << duration << " hours\n";
    }

    TurnRecord toRecord() const {
        TurnRecord r{};
        r.turnId = turnId;
        r.farmerId = farmerId;
        copyText(r.source, source, 40);
        copyText(r.date, date, 20);
        r.startHour = startHour;
        r.duration = duration;
        return r;
    }

    void fromRecord(const TurnRecord& r) {
        turnId = r.turnId;
        farmerId = r.farmerId;
        source = r.source;
        date = r.date;
        startHour = r.startHour;
        duration = r.duration;
    }

    void update() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "New water source: ";
        getline(cin, source);

        cout << "New date: ";
        getline(cin, date);

        cout << "New starting hour: ";
        if (!(cin >> startHour)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            turnId = 0;
            return;
        }

        cout << "New duration: ";
        if (!(cin >> duration)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            turnId = 0;
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
};

// ================= MAIN SYSTEM CLASS =================

class IrrigationSystem {
private:
    const char* farmerFile = "data/farmers.dat";
    const char* turnFile = "data/turns.dat";

public:

    void initializeFiles() {
        fstream f;

        f.open(farmerFile, ios::in | ios::binary);
        if (!f) {
            f.clear();
            f.open(farmerFile, ios::out | ios::binary);
        }
        f.close();

        f.open(turnFile, ios::in | ios::binary);
        if (!f) {
            f.clear();
            f.open(turnFile, ios::out | ios::binary);
        }
        f.close();
    }

    bool farmerExists(int id) {
        fstream f(farmerFile, ios::in | ios::binary);
        FarmerRecord r;

        while (f.read((char*)&r, sizeof(r))) {
            if (r.id == id) {
                f.close();
                return true;
            }
        }

        f.close();
        return false;
    }

    bool turnExists(int id) {
        fstream f(turnFile, ios::in | ios::binary);
        TurnRecord r;

        while (f.read((char*)&r, sizeof(r))) {
            if (r.turnId == id) {
                f.close();
                return true;
            }
        }

        f.close();
        return false;
    }

    void addFarmer() {
        int id;

        cout << "Enter Farmer ID: ";
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID.\n";
            return;
        }

        if (id <= 0 || farmerExists(id)) {
            cout << "Invalid or duplicate ID.\n";
            return;
        }

        Farmer f;
        f.input(id);

        if (!f.isValid()) return;

        FarmerRecord r = f.toRecord();

        fstream file(farmerFile,
                     ios::out | ios::app | ios::binary);

        if (!file) {
            cout << "File opening error.\n";
            return;
        }

        file.write((char*)&r, sizeof(r));
        file.close();

        if (file) cout << "Farmer saved successfully!\n";
        else cout << "Error saving farmer.\n";
    }

    void displayFarmers() {
        fstream file(farmerFile, ios::in | ios::binary);
        FarmerRecord r;
        bool found = false;

        while (file.read((char*)&r, sizeof(r))) {
            Farmer f;
            f.fromRecord(r);
            f.display();
            found = true;
        }

        if (!found) cout << "No farmer records found.\n";

        file.close();
    }

    void searchFarmer() {
        int id;
        cout << "Enter Farmer ID: ";
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID.\n";
            return;
        }

        fstream file(farmerFile, ios::in | ios::binary);
        FarmerRecord r;
        bool found = false;

        while (file.read((char*)&r, sizeof(r))) {
            if (r.id == id) {
                Farmer f;
                f.fromRecord(r);
                f.display();
                found = true;
                break;
            }
        }

        if (!found) cout << "Farmer not found.\n";

        file.close();
    }

    void updateFarmer() {
        int id;
        cout << "Enter Farmer ID to update: ";
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID.\n";
            return;
        }

        fstream file(farmerFile,
                     ios::in | ios::out | ios::binary);

        FarmerRecord r;
        bool found = false;

        while (true) {
            streampos position = file.tellg();

            if (!file.read((char*)&r, sizeof(r))) break;

            if (r.id == id) {
                found = true;

                Farmer f;
                f.fromRecord(r);
                f.display();

                cout << "\nEnter updated details:\n";
                f.update();

                if (!f.isValid()) {
                    cout << "Invalid details. Update cancelled.\n";
                    break;
                }

                FarmerRecord updated = f.toRecord();

                file.clear();
                file.seekp(position);

                file.write((char*)&updated, sizeof(updated));

                if (file) cout << "Farmer updated successfully!\n";
                else cout << "Update failed.\n";

                break;
            }
        }

        if (!found) cout << "Farmer not found.\n";

        file.close();
    }

    void addTurn() {
        int tId, fId;

        cout << "Enter Turn ID: ";
        if (!(cin >> tId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Turn ID.\n";
            return;
        }

        if (tId <= 0 || turnExists(tId)) {
            cout << "Invalid or duplicate Turn ID.\n";
            return;
        }

        cout << "Enter Farmer ID: ";
        if (!(cin >> fId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Farmer ID.\n";
            return;
        }

        if (!farmerExists(fId)) {
            cout << "Farmer does not exist. Register first.\n";
            return;
        }

        IrrigationTurn t;
        t.input(tId, fId);

        if (!t.isValid()) return;

        TurnRecord r = t.toRecord();

        fstream file(turnFile,
                     ios::out | ios::app | ios::binary);

        if (!file) {
            cout << "File opening error.\n";
            return;
        }

        file.write((char*)&r, sizeof(r));
        file.close();

        if (file) cout << "Irrigation turn saved!\n";
        else cout << "Error saving turn.\n";
    }

    void displayTurns() {
        fstream file(turnFile, ios::in | ios::binary);
        TurnRecord r;
        bool found = false;

        while (file.read((char*)&r, sizeof(r))) {
            IrrigationTurn t;
            t.fromRecord(r);
            t.display();
            found = true;
        }

        if (!found) cout << "No turns found.\n";

        file.close();
    }

    void searchTurn() {
        int id;
        cout << "Enter Turn ID: ";
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID.\n";
            return;
        }

        fstream file(turnFile, ios::in | ios::binary);
        TurnRecord r;
        bool found = false;

        while (file.read((char*)&r, sizeof(r))) {
            if (r.turnId == id) {
                IrrigationTurn t;
                t.fromRecord(r);
                t.display();
                found = true;
                break;
            }
        }

        if (!found) cout << "Turn not found.\n";

        file.close();
    }

    void updateTurn() {
        int id;
        cout << "Enter Turn ID to update: ";
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID.\n";
            return;
        }

        fstream file(turnFile,
                     ios::in | ios::out | ios::binary);

        TurnRecord r;
        bool found = false;

        while (true) {
            streampos position = file.tellg();

            if (!file.read((char*)&r, sizeof(r))) break;

            if (r.turnId == id) {
                found = true;

                IrrigationTurn t;
                t.fromRecord(r);
                t.display();

                cout << "\nEnter updated details:\n";
                t.update();

                if (!t.isValid()) {
                    cout << "Invalid details. Update cancelled.\n";
                    break;
                }

                TurnRecord updated = t.toRecord();

                file.clear();
                file.seekp(position);

                file.write((char*)&updated, sizeof(updated));

                if (file) cout << "Turn updated successfully!\n";
                else cout << "Update failed.\n";

                break;
            }
        }

        if (!found) cout << "Turn not found.\n";

        file.close();
    }
};

// ================= MAIN FUNCTION =================

int main() {
    IrrigationSystem system;
    system.initializeFiles();

    int choice;

    do {
        cout << "\n====================================\n";
        cout << " RURAL IRRIGATION TURN ALLOCATION\n";
        cout << "             CA2\n";
        cout << "====================================\n";

        cout << "1. Add Farmer\n";
        cout << "2. Display Farmers\n";
        cout << "3. Search Farmer (seekg)\n";
        cout << "4. Update Farmer (seekp)\n";
        cout << "5. Add Irrigation Turn\n";
        cout << "6. Display Irrigation Turns\n";
        cout << "7. Search Turn (seekg)\n";
        cout << "8. Update Turn (seekp)\n";
        cout << "9. Exit\n";

        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1: system.addFarmer(); break;
            case 2: system.displayFarmers(); break;
            case 3: system.searchFarmer(); break;
            case 4: system.updateFarmer(); break;
            case 5: system.addTurn(); break;
            case 6: system.displayTurns(); break;
            case 7: system.searchTurn(); break;
            case 8: system.updateTurn(); break;
            case 9:
                cout << "Program closed. Records remain saved.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 9);

    return 0;
}
