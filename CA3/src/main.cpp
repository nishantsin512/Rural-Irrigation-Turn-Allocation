#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>
using namespace std;

const char FILE_NAME[] = "farmers.dat";
const char TEMP_FILE[] = "farmers_temp.dat";
const char BACKUP_FILE[] = "farmers_backup_before_delete.dat";
const int MAX = 50;

struct FarmerRecord
{
    int farmerId;
    char name[50];
    char village[50];
    double landArea;
    char cropType[40];
    char waterSource[30];
    char turnDate[20];
    int startHour;
    int durationHours;
    char status;
};

class Farmer
{
protected:
    int farmerId;
    string name, village, cropType, waterSource, turnDate;
    double landArea;
    int startHour, durationHours;
    char status;
    static int farmerCount;

    void copyText(char* dest, const string& src, int size) const
    {
        strncpy(dest, src.c_str(), size - 1);
        dest[size - 1] = '\0';
    }

public:
    Farmer()
    {
        farmerId = 0;
        name = "";
        village = "";
        landArea = 0;
        cropType = "";
        waterSource = "";
        turnDate = "";
        startHour = 0;
        durationHours = 0;
        status = 'N';
    }

    Farmer(int id, string n, string v, double area, string crop,
           string source, string date, int hour, int duration, char st)
    {
        this->farmerId = id;
        this->name = n;
        this->village = v;
        this->landArea = area;
        this->cropType = crop;
        this->waterSource = source;
        this->turnDate = date;
        this->startHour = hour;
        this->durationHours = duration;
        this->status = st;
    }

    Farmer(const Farmer& f)
    {
        farmerId = f.farmerId;
        name = f.name;
        village = f.village;
        landArea = f.landArea;
        cropType = f.cropType;
        waterSource = f.waterSource;
        turnDate = f.turnDate;
        startHour = f.startHour;
        durationHours = f.durationHours;
        status = f.status;
    }

    virtual ~Farmer()
    {
    }

    inline int getFarmerId() const
    {
        return farmerId;
    }

    static int getFarmerCount()
    {
        return farmerCount;
    }

    static void setFarmerCount(int n)
    {
        farmerCount = n;
    }

    static void addFarmerCount()
    {
        farmerCount++;
    }

    virtual string getCategory() const
    {
        return "General Irrigation Farmer";
    }

    virtual void displayDetails() const
    {
        cout << "\nFarmer ID: " << farmerId
             << "\nName: " << name
             << "\nVillage: " << village
             << "\nLand Area: " << landArea << " acres"
             << "\nCrop Type: " << cropType
             << "\nWater Source: " << waterSource
             << "\nIrrigation Date: " << turnDate
             << "\nStarting Hour: " << startHour << ":00"
             << "\nDuration: " << durationHours << " hours"
             << "\nStatus: " << status
             << "\nFarmer Category: " << getCategory() << "\n";
    }

    bool isValid() const
    {
        return farmerId > 0 && !name.empty() && !village.empty() &&
               landArea > 0 && !cropType.empty() && !waterSource.empty() &&
               !turnDate.empty() && startHour >= 0 && startHour < 24 &&
               durationHours > 0 && durationHours <= 24 &&
               startHour + durationHours <= 24 && status == 'A';
    }

    FarmerRecord toRecord() const
    {
        FarmerRecord r = {};
        r.farmerId = farmerId;
        copyText(r.name, name, 50);
        copyText(r.village, village, 50);
        r.landArea = landArea;
        copyText(r.cropType, cropType, 40);
        copyText(r.waterSource, waterSource, 30);
        copyText(r.turnDate, turnDate, 20);
        r.startHour = startHour;
        r.durationHours = durationHours;
        r.status = status;
        return r;
    }

    void fromRecord(const FarmerRecord& r)
    {
        farmerId = r.farmerId;
        name = r.name;
        village = r.village;
        landArea = r.landArea;
        cropType = r.cropType;
        waterSource = r.waterSource;
        turnDate = r.turnDate;
        startHour = r.startHour;
        durationHours = r.durationHours;
        status = r.status;
    }

    void setFarmerId(int id)
    {
        farmerId = id;
    }

    operator double() const
    {
        return landArea;
    }

    friend void showFarmerSummary(const Farmer& f);
    friend ostream& operator<<(ostream& out, const Farmer& f);
    friend istream& operator>>(istream& in, Farmer& f);
    friend bool operator==(const Farmer& a, const Farmer& b);
    friend bool operator<(const Farmer& a, const Farmer& b);
    friend bool operator>(const Farmer& a, const Farmer& b);
};

class CanalFarmer : public Farmer
{
public:
    CanalFarmer() : Farmer()
    {
        waterSource = "Canal";
    }

    CanalFarmer(const Farmer& f) : Farmer(f)
    {
    }

    string getCategory() const
    {
        return "Canal Irrigation Farmer";
    }
};

class WellFarmer : public Farmer
{
public:
    WellFarmer() : Farmer()
    {
        waterSource = "Well";
    }

    WellFarmer(const Farmer& f) : Farmer(f)
    {
    }

    string getCategory() const
    {
        return "Well Irrigation Farmer";
    }
};

int Farmer::farmerCount = 0;

void showFarmerSummary(const Farmer& f)
{
    cout << "\n--- Farmer Summary ---"
         << "\nFarmer ID: " << f.farmerId
         << "\nName: " << f.name
         << "\nVillage: " << f.village
         << "\nWater Source: " << f.waterSource
         << "\nCategory: " << f.getCategory() << "\n";
}

ostream& operator<<(ostream& out, const Farmer& f)
{
    out << "Farmer ID: " << f.farmerId
        << "\nName: " << f.name
        << "\nVillage: " << f.village
        << "\nWater Source: " << f.waterSource
        << "\nCategory: " << f.getCategory();
    return out;
}

istream& operator>>(istream& in, Farmer& f)
{
    cout << "Enter farmer name: ";
    getline(in >> ws, f.name);
    cout << "Enter village name: ";
    getline(in, f.village);
    cout << "Enter land area in acres: ";
    if (!(in >> f.landArea))
        return in;
    cout << "Enter crop type: ";
    getline(in >> ws, f.cropType);
    cout << "Enter water source (Canal/Well): ";
    getline(in, f.waterSource);
    cout << "Enter irrigation date (DD-MM-YYYY): ";
    getline(in, f.turnDate);
    cout << "Enter starting hour (0-23): ";
    if (!(in >> f.startHour))
        return in;
    cout << "Enter duration in hours: ";
    if (!(in >> f.durationHours))
        return in;
    f.status = 'A';
    return in;
}

bool operator==(const Farmer& a, const Farmer& b)
{
    return a.farmerId == b.farmerId;
}

bool operator<(const Farmer& a, const Farmer& b)
{
    return a.farmerId < b.farmerId;
}

bool operator>(const Farmer& a, const Farmer& b)
{
    return a.landArea > b.landArea;
}

string lowerText(string value)
{
    for (int i = 0; value[i]; i++)
    {
        if (value[i] >= 'A' && value[i] <= 'Z')
            value[i] = value[i] + 32;
    }
    return value;
}

Farmer* makeFarmer(const FarmerRecord& r)
{
    string source = lowerText(r.waterSource);
    Farmer* p = 0;

    if (source == "canal")
        p = new CanalFarmer();
    else if (source == "well")
        p = new WellFarmer();
    else
        p = new Farmer();

    p->fromRecord(r);
    return p;
}

void readDetails(string& name, string& village, double& area,
                 string& crop, string& source, string& date,
                 int& hour, int& duration)
{
    cin.ignore(1000, '\n');
    cout << "Enter farmer name: ";
    getline(cin, name);
    cout << "Enter village name: ";
    getline(cin, village);
    cout << "Enter land area in acres: ";
    while (!(cin >> area) || area <= 0)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "Enter a valid positive land area: ";
    }
    cin.ignore(1000, '\n');
    cout << "Enter crop type: ";
    getline(cin, crop);
    cout << "Enter water source (Canal/Well): ";
    getline(cin, source);
    cout << "Enter irrigation date (DD-MM-YYYY): ";
    getline(cin, date);
    cout << "Enter starting hour (0-23): ";
    while (!(cin >> hour) || hour < 0 || hour > 23)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "Enter a valid starting hour (0-23): ";
    }
    cout << "Enter duration in hours: ";
    while (!(cin >> duration) || duration <= 0 || duration > 24 ||
           hour + duration > 24)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "Enter a valid duration that ends by hour 24: ";
    }
}

int getFileCount()
{
    fstream file(FILE_NAME, ios::in | ios::binary);
    if (!file)
        return 0;
    file.seekg(0, ios::end);
    streamoff size = file.tellg();
    file.close();
    if (size < 0)
        return 0;
    return static_cast<int>(size / sizeof(FarmerRecord));
}

int findRecord(int id)
{
    fstream file(FILE_NAME, ios::in | ios::binary);
    if (!file)
        return -1;
    file.seekg(0, ios::end);
    streamoff size = file.tellg();
    int count = static_cast<int>(size / sizeof(FarmerRecord));
    FarmerRecord r;

    for (int i = 0; i < count; i++)
    {
        file.seekg(static_cast<streamoff>(i) * sizeof(FarmerRecord), ios::beg);
        file.read(reinterpret_cast<char*>(&r), sizeof(r));
        if (file && r.farmerId == id)
        {
            file.close();
            return i;
        }
    }
    file.close();
    return -1;
}

int saveRecord(const Farmer& f)
{
    fstream file(FILE_NAME, ios::out | ios::binary | ios::app);
    if (!file)
        return 0;
    FarmerRecord r = f.toRecord();
    file.write(reinterpret_cast<const char*>(&r), sizeof(r));
    int ok = file.good();
    file.close();
    return ok;
}

void displayAll()
{
    fstream file(FILE_NAME, ios::in | ios::binary);
    if (!file)
    {
        cout << "No farmer records found.\n";
        return;
    }

    FarmerRecord r;
    int total = 0;
    while (total < MAX && file.read(reinterpret_cast<char*>(&r), sizeof(r)))
    {
        Farmer* ptr = makeFarmer(r);
        ptr->displayDetails();
        delete ptr;
        total++;
    }
    file.close();

    if (total == 0)
        cout << "No farmer records found.\n";
    if (getFileCount() > MAX)
        cout << "\nOnly first 50 records are displayed.\n";
}

void searchFarmer(int id)
{
    int pos = findRecord(id);
    if (pos == -1)
    {
        cout << "Farmer not found!\n";
        return;
    }

    fstream file(FILE_NAME, ios::in | ios::binary);
    if (!file)
    {
        cout << "Unable to open data file.\n";
        return;
    }

    FarmerRecord r;
    file.seekg(static_cast<streamoff>(pos) * sizeof(r), ios::beg);
    file.read(reinterpret_cast<char*>(&r), sizeof(r));
    bool ok = file.good();
    file.close();

    if (!ok)
    {
        cout << "Error while reading record.\n";
        return;
    }

    Farmer* p = makeFarmer(r);
    p->displayDetails();
    showFarmerSummary(*p);
    delete p;
}

void updateFarmer(int id)
{
    int pos = findRecord(id);
    if (pos == -1)
    {
        cout << "Farmer not found!\n";
        return;
    }

    string name, village, crop, source, date;
    double area = 0;
    int hour = 0, duration = 0;
    cout << "\nEnter updated details:\n";
    readDetails(name, village, area, crop, source, date, hour, duration);

    Farmer temp(id, name, village, area, crop, source, date, hour, duration, 'A');
    if (!temp.isValid())
    {
        cout << "Invalid details. Record was not updated.\n";
        return;
    }

    FarmerRecord oldRecord;
    fstream readFile(FILE_NAME, ios::in | ios::binary);
    if (!readFile)
    {
        cout << "Unable to open data file.\n";
        return;
    }
    readFile.seekg(static_cast<streamoff>(pos) * sizeof(oldRecord), ios::beg);
    readFile.read(reinterpret_cast<char*>(&oldRecord), sizeof(oldRecord));
    bool readOk = readFile.good();
    readFile.close();

    if (!readOk)
    {
        cout << "Unable to read existing record.\n";
        return;
    }

    if (lowerText(oldRecord.waterSource) != lowerText(source))
    {
        cout << "Water source category cannot be changed during update.\n";
        return;
    }

    Farmer* p = makeFarmer(oldRecord);
    Farmer updated(temp);
    p->fromRecord(updated.toRecord());

    fstream file(FILE_NAME, ios::in | ios::out | ios::binary);
    if (!file)
    {
        cout << "Unable to open data file.\n";
        delete p;
        return;
    }

    FarmerRecord r = p->toRecord();
    file.seekp(static_cast<streamoff>(pos) * sizeof(r), ios::beg);
    file.write(reinterpret_cast<const char*>(&r), sizeof(r));

    if (file.good())
        cout << "Farmer record updated successfully!\n";
    else
        cout << "Record update failed.\n";

    file.close();
    delete p;
}

void deleteFarmer(int id)
{
    int pos = findRecord(id);
    if (pos == -1)
    {
        cout << "Farmer not found!\n";
        return;
    }

    char ans;
    cout << "Confirm deletion of Farmer ID " << id << "? (Y/N): ";
    cin >> ans;

    if (ans != 'Y' && ans != 'y')
    {
        cout << "Delete cancelled. Record remains unchanged.\n";
        return;
    }

    fstream in(FILE_NAME, ios::in | ios::binary);
    fstream out(TEMP_FILE, ios::out | ios::binary);

    if (!in || !out)
    {
        cout << "Unable to open files for deletion.\n";
        in.close();
        out.close();
        remove(TEMP_FILE);
        return;
    }

    FarmerRecord r;
    int index = 0;
    bool writeOk = true;

    while (in.read(reinterpret_cast<char*>(&r), sizeof(r)))
    {
        if (index != pos)
        {
            out.write(reinterpret_cast<const char*>(&r), sizeof(r));
            if (!out.good())
            {
                writeOk = false;
                break;
            }
        }
        index++;
    }

    bool readOk = in.eof();
    in.close();
    out.close();

    if (!readOk || !writeOk || index != getFileCount())
    {
        cout << "Delete cancelled because file verification failed.\n";
        remove(TEMP_FILE);
        return;
    }

    remove(BACKUP_FILE);
    if (rename(FILE_NAME, BACKUP_FILE) != 0)
    {
        cout << "Could not back up original data file.\n";
        remove(TEMP_FILE);
        return;
    }

    if (rename(TEMP_FILE, FILE_NAME) != 0)
    {
        cout << "Could not install updated file. Restoring original data.\n";
        if (rename(BACKUP_FILE, FILE_NAME) != 0)
            cout << "WARNING: Original data remains in " << BACKUP_FILE << "\n";
        return;
    }

    Farmer::setFarmerCount(getFileCount());
    cout << "Farmer deleted successfully!\n";
    cout << "Backup created: " << BACKUP_FILE << "\n";
}

int main()
{
    int choice = 0, id = 0;
    Farmer::setFarmerCount(getFileCount());

    do
    {
        cout << "\n================================\n";
        cout << " RURAL IRRIGATION TURN ALLOCATION\n";
        cout << "================================\n";
        cout << "1. Register Farmer\n";
        cout << "2. Display All Farmers\n";
        cout << "3. Search Farmer by ID\n";
        cout << "4. Update Farmer by ID\n";
        cout << "5. Delete Farmer by ID\n";
        cout << "6. Show Total Farmers\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            if (cin.eof())
                break;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter a valid menu choice.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            if (getFileCount() >= MAX)
            {
                cout << "Maximum capacity of 50 farmers reached.\n";
                break;
            }

            cout << "Enter unique Farmer ID: ";
            if (!(cin >> id))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Farmer ID.\n";
                break;
            }

            if (id <= 0)
            {
                cout << "Farmer ID must be positive.\n";
                break;
            }

            if (findRecord(id) != -1)
            {
                cout << "Farmer ID already exists!\n";
                break;
            }

            string name, village, crop, source, date;
            double area = 0;
            int hour = 0, duration = 0;
            readDetails(name, village, area, crop, source, date, hour, duration);

            Farmer temp(id, name, village, area, crop, source, date, hour, duration, 'A');
            if (!temp.isValid())
            {
                cout << "Invalid details. Registration cancelled.\n";
                break;
            }

            Farmer* p = 0;
            if (lowerText(source) == "canal")
                p = new CanalFarmer(temp);
            else if (lowerText(source) == "well")
                p = new WellFarmer(temp);
            else
            {
                cout << "Water source must be Canal or Well.\n";
                break;
            }

            Farmer f(*p);
            double farmerArea = *p;

            if (saveRecord(f))
            {
                Farmer::addFarmerCount();
                cout << "Farmer registered and saved successfully!\n";
                cout << "Category: " << p->getCategory() << "\n";
                cout << "Type conversion to double: " << farmerArea << " acres\n";
                cout << f << "\n";
            }
            else
            {
                cout << "Unable to save record.\n";
            }

            delete p;
            break;
        }

        case 2:
            displayAll();
            break;

        case 3:
            cout << "Enter Farmer ID to search: ";
            if (!(cin >> id))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid ID.\n";
                break;
            }
            searchFarmer(id);
            break;

        case 4:
            cout << "Enter Farmer ID to update: ";
            if (!(cin >> id))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid ID.\n";
                break;
            }
            updateFarmer(id);
            break;

        case 5:
            cout << "Enter Farmer ID to delete: ";
            if (!(cin >> id))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid ID.\n";
                break;
            }
            deleteFarmer(id);
            break;

        case 6:
            cout << "Total registered farmers: " << Farmer::getFarmerCount() << "\n";
            break;

        case 7:
            cout << "Thank you for using Rural Irrigation Turn Allocation!\n";
            break;

        default:
            cout << "Invalid choice. Select 1 to 7.\n";
        }
    } while (choice != 7);

    return 0;
}

