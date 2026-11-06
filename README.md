# Rural Irrigation Turn Allocation System

**Course:** CAP455 – C++ Minor Project  
**Project type:** Console-based C++ application  
**Current phase:** CA1 – In-memory prototype

## 1. Project overview

The Rural Irrigation Turn Allocation System is a menu-driven C++ application for maintaining farmer records and recording irrigation turns associated with a shared water source such as a canal or well.

The current prototype supports:
- Registering farmers with a unique positive Farmer ID.
- Storing farmer name, village, land area (acres) and crop type.
- Displaying all registered farmers and searching by Farmer ID.
- Adding irrigation turns for already registered farmers.
- Storing Turn ID, Farmer ID, water source, date, start hour and duration.
- Displaying all turns and searching by Turn ID.
- Rejecting basic invalid inputs and duplicate IDs.
- Checking overlapping time slots for the same water source and date.

## 2. Current implementation status

This README describes the supplied CA1 source code. The application stores data in fixed-size arrays while it is running. **Records are not saved permanently** and will be lost when the program exits.

Implemented C++ concepts include:
- `Farmer` and `IrrigationTurn` classes and objects
- Private data members and public member functions
- Static data members and static getter functions
- Inline getter in `Farmer`
- Friend function `showFarmerSummary`
- Arrays of objects
- Pointers to arrays
- `this` pointer
- `std::string`
- Input validation and linear search

Not yet implemented in this CA1 version: binary file persistence, constructors/copy constructor/destructor requirements beyond the default constructors, inheritance, operator overloading, dynamic memory management, complete Update/Delete, exception handling, templates and STL algorithm workflows. These are planned for later phases as per the course guide.

## 3. Requirements

- C++ compiler supporting a standard C++ version (C++11 or later recommended)
- Terminal / Command Prompt
- GCC (`g++`) or an equivalent C++ compiler

## 4. Folder structure

A simple single-file layout is sufficient for the current CA1 prototype:

```text
Rural-Irrigation-Turn-Allocation/
├── main.cpp
├── README.md
├── docs/
│   ├── Proposal.docx
│   └── ...
├── data/
└── tests/
```

If your source file is currently inside `src/`, keep it there and use the corresponding compile command below. Do not keep empty `.h` or `.cpp` files unless they are actually included in the project.

## 5. Compile and run

### Windows (PowerShell / CMD), if `main.cpp` is in the project root

```bash
g++ -std=c++11 -Wall -Wextra main.cpp -o irrigation
./irrigation
```

In Windows PowerShell, you can also run:

```powershell
g++ -std=c++11 -Wall -Wextra main.cpp -o irrigation.exe
.\irrigation.exe
```

### If the source file is in `src/main.cpp`

```bash
g++ -std=c++11 -Wall -Wextra src/main.cpp -o irrigation
./irrigation
```

## 6. Menu options

1. Register Farmer
2. Display All Farmers
3. Search Farmer by ID
4. Add Irrigation Turn
5. Display All Irrigation Turns
6. Search Turn by ID
7. Show Total Farmers and Turns
8. Exit

## 7. Input rules in the current version

### Farmer
- Farmer ID must be positive and unique.
- Name, village and crop type must not be empty.
- Land area must be greater than zero.

### Irrigation turn
- Turn ID must be positive and unique.
- The Farmer ID must already exist.
- Water source and date must not be empty.
- Start hour must be from 0 to 23.
- Duration must be from 1 to 24 hours.
- The end hour must not exceed 24:00.
- A time conflict is rejected when the new interval overlaps an existing interval for the same source and date.

**Known limitation:** the date is currently stored as text and checked only for non-empty input. A malformed date such as an impossible calendar date may pass this basic check. Date-format/calendar validation can be added in a later revision.

## 8. Testing checklist

Test the following before demonstrating the application:
- Register a valid farmer.
- Try a duplicate Farmer ID.
- Try empty name/village/crop and zero or negative land area.
- Add a turn for an unknown Farmer ID.
- Try invalid start hour and duration.
- Try a turn whose end time exceeds 24:00.
- Add two overlapping turns for the same source/date and confirm the second is rejected.
- Add non-overlapping turns for the same source/date and confirm they are accepted.
- Search for existing and non-existing IDs.
- Exit and run again to observe that CA1 data is not persistent.

Record actual outcomes and attach screenshots in `tests/`. Do not mark tests as passed until you have run them.

## 9. Planned development by CA

- **CA1:** Entity classes, arrays, pointers, validation, in-memory Create/Read and search.
- **CA2:** Required constructors/destructor and binary file storage using `fstream`; file-based search and update.
- **CA3:** Inheritance, operator overloading, type conversion, `new/delete`, virtual functions and safe Update/Delete.
- **CA4:** Complete CRUD, custom exceptions, templates, STL containers/algorithms and an advanced feature such as backup or CSV export.

These are planned milestones, not features of the current CA1 executable.

## 10. Academic integrity and contribution

The student is responsible for understanding, compiling, testing and being able to explain every part of the submitted code. Any AI assistance must be disclosed according to the faculty/institution policy. Replace placeholders in the proposal and report with your actual details, and use only genuine test results and screenshots.

## 11. Author details

- Name: Nishant Kumar
- Roll number: 12623156
- Faculty guide: Aadarsh Kumar Singh
- Section: D1P2635
