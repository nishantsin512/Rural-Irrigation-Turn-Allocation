# 🌾 Rural Irrigation Turn Allocation System

## 1. Project Overview

The **Rural Irrigation Turn Allocation System** is a console-based application developed using C++. It is designed to manage farmer registration and irrigation scheduling in rural areas.

The system allows users to register farmers, store their agricultural details, assign irrigation schedules, display registered farmer information, and search for farmers using their unique Farmer ID.

This project demonstrates the practical implementation of Object-Oriented Programming (OOP) concepts in C++.

## 2. Objectives

- To maintain farmer registration records.
- To store agricultural information such as village, land area, and crop type.
- To manage irrigation schedules.
- To prevent duplicate Farmer IDs.
- To validate irrigation timing and duration.
- To provide searching and displaying functionality.
- To demonstrate fundamental OOP concepts in C++.

## 3. Features

1. **Farmer Registration:** Register farmers with unique IDs and personal details.
2. **Farmer Details:** Store name, village, land area, crop type, and water source.
3. **Irrigation Scheduling:** Store irrigation date, starting hour, and duration.
4. **Input Validation:** Validate farmer details and irrigation time.
5. **Duplicate ID Prevention:** Prevent registration with an existing Farmer ID.
6. **Display All Farmers:** Display all successfully registered farmers.
7. **Search Farmer:** Search for a farmer using their unique ID.
8. **Farmer Summary:** Display a summary using a friend function.
9. **Total Farmer Count:** Maintain and display the total number of registered farmers.
10. **Fixed Storage:** Store up to 50 farmer records using an array.

## 4. Technologies Used

| Technology | Purpose |
|---|---|
| C++ | Programming Language |
| OOP | Object-Oriented Programming |
| iostream | Input and Output |
| string | String Data Management |
| VS Code / Code::Blocks | Development Environment |

## 5. Object-Oriented Programming Concepts Used

The project implements the following C++ concepts:

- **Class and Object:** The `Farmer` class represents farmer records.
- **Encapsulation:** Farmer data members are declared private.
- **Static Data Member:** `farmerCount` maintains the total number of registered farmers.
- **Static Member Function:** `getFarmerCount()` returns the total farmer count.
- **Inline Function:** `getFarmerId()` is implemented as an inline function.
- **Friend Function:** `showFarmerSummary()` accesses private members of the Farmer class.
- **this Pointer:** Used to access the current object's data members.
- **Object Array:** A fixed-size array stores up to 50 Farmer objects.
- **Object Pointer:** A pointer accesses farmer records.
- **std::string:** Used to store textual information.

## 6. System Requirements

**Hardware Requirements**
- Basic computer or laptop.
- Minimum 2 GB RAM.
- Keyboard and display.

**Software Requirements**
- Windows, Linux, or macOS.
- C++ compiler (GCC, MinGW, or equivalent).
- VS Code, Code::Blocks, or any C++ IDE.

## 7. How to Run the Project

### Step 1: Save the Source Code

Save the program as:

`main.cpp`

### Step 2: Compile the Program

Using GCC:

```bash
g++ main.cpp -o irrigation
```

### Step 3: Execute the Program

For Windows:

```bash
irrigation.exe
```

For Linux/macOS:

```bash
./irrigation
```

## 8. Main Menu

After executing the program, the following menu is displayed:

```text
================================
 RURAL IRRIGATION TURN ALLOCATION
================================

1. Register Farmer
2. Display All Farmers
3. Search Farmer by ID
4. Show Total Farmers
5. Exit

Enter your choice:
```

## 9. Functional Description

| Option | Functionality |
|---|---|
| 1 | Register a new farmer |
| 2 | Display all registered farmers |
| 3 | Search farmer using Farmer ID |
| 4 | Display total registered farmers |
| 5 | Exit the application |

## 10. Sample Output

### Farmer Registration

```text
Enter your choice: 1

Enter unique Farmer ID: 101
Enter farmer name: Rahul Kumar
Enter village name: Rampur
Enter land area in acres: 5
Enter crop type: Wheat
Enter water source (Canal/Well): Canal
Enter irrigation date (DD-MM-YYYY): 10-11-2026
Enter starting hour (0-23): 6
Enter duration in hours: 4

Farmer registered successfully!
```

### Display Farmer Details

```text
Farmer ID: 101
Name: Rahul Kumar
Village: Rampur
Land Area: 5 acres
Crop Type: Wheat
Water Source: Canal
Irrigation Date: 10-11-2026
Starting Hour: 6:00
Duration: 4 hours
Status: A
```

### Search Farmer

```text
Enter Farmer ID to search: 101

Farmer ID: 101
Name: Rahul Kumar
Village: Rampur
Land Area: 5 acres
Crop Type: Wheat
Water Source: Canal
Irrigation Date: 10-11-2026
Starting Hour: 6:00
Duration: 4 hours
Status: A

--- Farmer Summary ---
Farmer ID: 101
Name: Rahul Kumar
Village: Rampur
Water Source: Canal
```

### Total Registered Farmers

```text
Total registered farmers: 1
```

## 11. Input Validation Rules

- Farmer ID must be a positive integer.
- Duplicate Farmer IDs are not allowed.
- Farmer name and village name cannot be empty.
- Land area must be greater than zero.
- Crop type and water source cannot be empty.
- Starting hour must be between 0 and 23.
- Irrigation duration must be between 1 and 24 hours.
- Starting hour plus irrigation duration must not exceed 24.
- Invalid farmer records are not registered.

## 12. Limitations

- The application supports a maximum of 50 farmer records.
- Records are stored temporarily in memory.
- Data is lost when the application terminates.
- The application does not use a database.
- Irrigation scheduling is maintained as individual farmer information; automatic conflict detection is not implemented.

## 13. Future Enhancements

The project can be enhanced in future phases by adding:

- File handling for permanent data storage.
- Automatic irrigation turn allocation.
- Conflict detection between irrigation schedules.
- Farmer record modification and deletion.
- Inheritance and polymorphism.
- Operator overloading.
- Database integration.
- Graphical User Interface (GUI).

## 14. Conclusion

The Rural Irrigation Turn Allocation System provides a basic and structured approach to managing farmer registration and irrigation scheduling.

The project demonstrates important C++ Object-Oriented Programming concepts through a practical real-world application. It provides a foundation for future enhancements and the development of a more advanced irrigation management system.

---

**Project Name:** Rural Irrigation Turn Allocation  
**Programming Language:** C++  
**Course:** CAP455 – Object-Oriented Programming using C++  
**Project Type:** Console-Based Application  
**Storage Capacity:** 50 Farmer Records