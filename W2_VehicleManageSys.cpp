#include <iostream>
#include <string>
#include <algorithm>
#include <cstring> // for strcpy
#include <vector>  // Using vector for easier management
#include <limits>  // Required for numeric_limits

const int EXIT_CHOICE = 4;

using namespace std;

// Typedef
typedef char VIN[20];

// Enumeration
enum Color
{
    RED,
    BLUE,
    GREEN,
    BLACK,
    WHITE
};
enum PurchaseMonth
{
    JAN = 1,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC
};

class Vehicle
{
private:
    string maker;
    string model;
    int year;
    Color color;
    double weight;
    VIN vin;
    PurchaseMonth purchaseMonth;
    double engineSize; // NEW ATTRIBUTE

public:
    // Constructor
    Vehicle(string m, string mo, int y, Color c, double w, const char *v, PurchaseMonth pm, double es)
    {
        maker = m;
        model = mo;
        year = y;
        color = c;
        weight = w;
        strncpy(vin, v, 19);
        vin[19] = '\0'; // Ensure null termination
        purchaseMonth = pm;
        engineSize = es;
    }

    // Getters
    string getMaker() const { return maker; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    Color getColor() const { return color; }
    double getWeight() const { return weight; }
    const char *getVIN() const { return vin; }
    PurchaseMonth getPurchaseMonth() const { return purchaseMonth; }
    double getEngineSize() const { return engineSize; }

    // Setters
    void setMaker(string m) { maker = m; }
    void setModel(string mo) { model = mo; }
    void setYear(int y) { year = y; }
    void setColor(Color c) { color = c; }
    void setWeight(double w) { weight = w; }
    void setVIN(const char *v)
    {
        strncpy(vin, v, 19);
        vin[19] = '\0';
    }
    void setPurchaseMonth(PurchaseMonth pm) { purchaseMonth = pm; }
    void setEngineSize(double es) { engineSize = es; }

    // Helper methods to convert enums to strings
    string colorToString() const
    {
        switch (color)
        {
        case RED:
            return "Red";
        case BLUE:
            return "Blue";
        case GREEN:
            return "Green";
        case BLACK:
            return "Black";
        case WHITE:
            return "White";
        default:
            return "Unknown";
        }
    }

    string monthToString() const
    {
        switch (purchaseMonth)
        {
        case JAN:
            return "January";
        case FEB:
            return "February";
        case MAR:
            return "March";
        case APR:
            return "April";
        case MAY:
            return "May";
        case JUN:
            return "June";
        case JUL:
            return "July";
        case AUG:
            return "August";
        case SEP:
            return "September";
        case OCT:
            return "October";
        case NOV:
            return "November";
        case DEC:
            return "December";
        default:
            return "Unknown";
        }
    }

    // Display
    void display() const
    {
        cout << "Maker: " << maker
             << " | Model: " << model
             << " | Year: " << year
             << " | Color: " << colorToString()
             << " | Weight: " << weight
             << " | VIN: " << vin
             << " | Purchase Month: " << monthToString()
             << " | Engine: " << engineSize << "L"
             << endl;
    }
};

// Sorting comparators
bool compareByMaker(const Vehicle *a, const Vehicle *b)
{
    return a->getMaker() < b->getMaker();
}

bool compareByYear(const Vehicle *a, const Vehicle *b)
{
    return a->getYear() < b->getYear();
}

bool compareByWeight(const Vehicle *a, const Vehicle *b)
{
    return a->getWeight() < b->getWeight();
}

bool compareByColor(const Vehicle *a, const Vehicle *b)
{
    return a->getColor() < b->getColor();
}

// Function to get a valid integer input
int getValidInt(const string &prompt)
{
    int value;
    cout << prompt;
    while (!(cin >> value))
    {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // No clearInputBuffer() here as it's handled in the loop or after the call
    return value;
}

// Function to get a valid double input
double getValidDouble(const string &prompt)
{
    double value;
    cout << prompt;
    while (!(cin >> value))
    {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // No clearInputBuffer() here as it's handled in the loop or after the call
    return value;
}

void clearInputBuffer()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void addNewVehicle(vector<Vehicle *> &vehicles)
{
    string maker, model;
    int year, monthInt, colorInt;
    double weight, engineSize;
    VIN vin;

    cout << "\nEnter details for the new vehicle:\n";
    cout << "Maker: ";
    getline(cin, maker);
    cout << "Model: ";
    getline(cin, model);
    year = getValidInt("Year: ");
    colorInt = getValidInt("Color (0:RED, 1:BLUE, 2:GREEN, 3:BLACK, 4:WHITE): ");
    weight = getValidDouble("Weight: ");
    cout << "VIN: ";
    cin >> vin;
    monthInt = getValidInt("Purchase Month (1-12): ");
    engineSize = getValidDouble("Engine Size (in Liters): ");
    clearInputBuffer();

    Color color = static_cast<Color>(colorInt);
    PurchaseMonth purchaseMonth = static_cast<PurchaseMonth>(monthInt);

    vehicles.push_back(new Vehicle(maker, model, year, color, weight, vin, purchaseMonth, engineSize));
    cout << "Vehicle added successfully!\n";
}

int main()
{
    vector<Vehicle *> vehicles;
    int n;

    cout << "Enter number of vehicles to create initially: ";
    cin >> n;
    clearInputBuffer();

    for (int i = 0; i < n; ++i)
    {
        cout << "\n--- Enter Vehicle " << i + 1 << " ---";
        addNewVehicle(vehicles);
    }

    int choice = 0;
    do
    {
        cout << "\n--- Vehicle Management System ---\n";
        cout << "1. Display all vehicles\n";
        cout << "2. Sort vehicles\n";
        cout << "3. Add a new vehicle\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            cout << "\n--- All Vehicles ---\n";
            for (const auto &v : vehicles)
            {
                v->display();
            }
            break;
        case 2:
            char sortChoice;
            cout << "\nSort by:\n";
            cout << " (m)aker, (y)ear, (w)eight, (c)olor: ";
            cin >> sortChoice;
            clearInputBuffer();

            if (sortChoice == 'm')
            {
                sort(vehicles.begin(), vehicles.end(), compareByMaker);
                cout << "Sorted by maker.\n";
            }
            else if (sortChoice == 'y')
            {
                sort(vehicles.begin(), vehicles.end(), compareByYear);
                cout << "Sorted by year.\n";
            }
            else if (sortChoice == 'w')
            {
                sort(vehicles.begin(), vehicles.end(), compareByWeight);
                cout << "Sorted by weight.\n";
            }
            else if (sortChoice == 'c')
            {
                sort(vehicles.begin(), vehicles.end(), compareByColor);
                cout << "Sorted by color.\n";
            }
            else
            {
                cout << "Invalid choice.\n";
            }

            cout << "\n--- Sorted Vehicles ---\n";
            for (const auto &v : vehicles)
            {
                v->display();
            }
            break;
        case 3:
            addNewVehicle(vehicles);
            break;
        case EXIT_CHOICE:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != EXIT_CHOICE);

    // Cleanup
    for (Vehicle *v : vehicles)
    {
        delete v;
    }
    vehicles.clear();

    return 0;
}
