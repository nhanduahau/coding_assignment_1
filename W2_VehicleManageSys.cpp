
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring> // for strcpy
using namespace std;

// Typedef
typedef char VIN[20];

// Enumeration
enum Color { RED, BLUE, GREEN, BLACK, WHITE };
enum PurchaseMonth { JAN=1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

class Vehicle {
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
    Vehicle(string m, string mo, int y, Color c, double w, const char* v, PurchaseMonth pm, double es) {
        maker = m;
        model = mo;
        year = y;
        color = c;
        weight = w;
        strcpy(vin, v);
        purchaseMonth = pm;
        engineSize = es;
    }

    // Getters/Setters
    string getMaker() const { return maker; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    double getWeight() const { return weight; }
    double getEngineSize() const { return engineSize; }
    void setEngineSize(double es) { engineSize = es; }

    // Display
    void display() const {
        cout << "Maker: " << maker
             << " | Model: " << model
             << " | Year: " << year
             << " | Weight: " << weight
             << " | Engine: " << engineSize << "L"
             << endl;
    }
};

// Sorting comparator example
bool compareByWeight(Vehicle* a, Vehicle* b) {
    return a->getWeight() < b->getWeight();
}

int main() {
    int n;
    cout << "Enter number of vehicles: ";
    cin >> n;

    Vehicle** vehicles = new Vehicle*[n];

    // Example: Hardcoded object creation (students expand to user input)
    vehicles[0] = new Vehicle("Toyota","Corolla",2020,RED,1300,"VIN123",MAR,1.8);
    vehicles[1] = new Vehicle("Honda","Civic",2019,BLUE,1250,"VIN456",JAN,2.0);

    // Sorting example
    sort(vehicles, vehicles+n, compareByWeight);

    cout << "\n--- Sorted Vehicles ---\n";
    for(int i=0;i<n;i++) {
        vehicles[i]->display();
    }

    // Cleanup
    for(int i=0;i<n;i++) delete vehicles[i];
    delete[] vehicles;

    return 0;
}
