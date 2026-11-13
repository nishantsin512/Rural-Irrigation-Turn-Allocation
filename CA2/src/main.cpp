#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
 
using namespace std;
 
const char FILE_NAME[] = "farmers.dat";
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
private:
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
 
    ~Farmer()
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
 
    bool isValid() const
    {
        return farmerId > 0 && !name.empty() && !village.empty() &&
               landArea > 0 && !cropType.empty() && !waterSource.empty() &&
               !turnDate.empty() && startHour >= 0 && startHour < 24 &&
               durationHours > 0 && durationHours <= 24 &&
               startHour + durationHours <= 24 && status == 'A';
    }
 
    void displayDetails() const
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
             << "\nStatus: " << status << "\n";
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
 
    friend void showFarmerSummary(const Farmer& f);
};
 
int Farmer::farmerCount = 0;
 
void showFarmerSummary(const Farmer& f)
{
    cout << "\n--- Farmer Summary ---"
         << "\nFarmer ID: " << f.farmerId
         << "\nName: " << f.name
         << "\nVillage: " << f.village
         << "\nWater Source: " << f.waterSource << "\n";
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
 
    Farmer arr[MAX];
    Farmer* ptr = arr;
    FarmerRecord r;
    int total = 0;
 
    while (total < MAX && file.read(reinterpret_cast<char*>(&r), sizeof(r)))
    {
        ptr[total].fromRecord(r);
        total++;
    }
 
    file.close();
 
    if (total == 0)
        cout << "No farmer records found.\n";
 
    for (int i = 0; i < total; i++)
        ptr[i].displayDetails();
 
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
 
    Farmer f;
    f.fromRecord(r);
    f.displayDetails();
    showFarmerSummary(f);
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
 
    Farmer f(id, name, village, area, crop, source, date, hour, duration, 'A');
 
    if (!f.isValid())
    {
        cout << "Invalid details. Record was not updated.\n";
        return;
    }
 
    fstream file(FILE_NAME, ios::in | ios::out | ios::binary);
    if (!file)
    {
        cout << "Unable to open data file.\n";
        return;
    }
 
    FarmerRecord r = f.toRecord();
    file.seekp(static_cast<streamoff>(pos) * sizeof(r), ios::beg);
    file.write(reinterpret_cast<const char*>(&r), sizeof(r));
 
    if (file.good())
        cout << "Farmer record updated successfully!\n";
    else
        cout << "Record update failed.\n";
 
    file.close();
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
        cout << "5. Show Total Farmers\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
 
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter a valid menu choice.\n";
            choice = 0;
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
 
            Farmer f(temp);
 
            if (saveRecord(f))
            {
                Farmer::addFarmerCount();
                cout << "Farmer registered and saved successfully!\n";
            }
            else
            {
                cout << "Unable to save record.\n";
            }
 
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
            cout << "Total registered farmers: " << Farmer::getFarmerCount() << "\n";
            break;
 
        case 6:
            cout << "Thank you for using Rural Irrigation Turn Allocation!\n";
            break;
 
        default:
            cout << "Invalid choice. Select 1 to 6.\n";
        }
 
    } while (choice != 6);
 
    return 0;
}

 