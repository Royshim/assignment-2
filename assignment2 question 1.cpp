#include <iostream>

using namespace std;

const int MAX_STRING_LENGTH = 100;

class Vehicle {
protected:
    char make[MAX_STRING_LENGTH];
    char model[MAX_STRING_LENGTH];
    int year;

public:
    virtual double calculateRentalCost() const = 0;

    void setDetails(const char* m, const char* mod, int y) {
        int i;
        for (i = 0; m[i] && i < MAX_STRING_LENGTH - 1; i++) {
            make[i] = m[i];
        }
        make[i] = '\0';

        for (i = 0; mod[i] && i < MAX_STRING_LENGTH - 1; i++) {
            model[i] = mod[i];
        }
        model[i] = '\0';

        year = y;
    }

    void displayInfo() const {
        cout << year << " " << make << " " << model << endl;
    }
};

class Car : public Vehicle {
private:
    int numDoors;

public:
    void setNumDoors(int doors) {
        numDoors = doors;
    }

    double calculateRentalCost() const override {
        return 50.0 * numDoors;
    }

    void displayInfo() const {
        Vehicle::displayInfo();
        cout << "Number of doors: " << numDoors << endl;
    }
};

class SUV : public Vehicle {
private:
    bool fourWheelDrive;

public:
    void setFourWheelDrive(bool fwd) {
        fourWheelDrive = fwd;
    }

    double calculateRentalCost() const override {
        return 70.0 + (fourWheelDrive ? 30.0 : 0.0);
    }

    void displayInfo() const {
        Vehicle::displayInfo();
        cout << "Four-wheel drive: " << (fourWheelDrive ? "Yes" : "No") << endl;
    }
};

class Truck : public Vehicle {
private:
    double cargoCapacity;

public:
    void setCargoCapacity(double capacity) {
        cargoCapacity = capacity;
    }

    double calculateRentalCost() const override {
        return 80.0 + (cargoCapacity * 0.1);
    }

    void displayInfo() const {
        Vehicle::displayInfo();
        cout << "Cargo capacity: " << cargoCapacity << " tonnes" << endl;
    }
};

Vehicle* createVehicle() {
    char make[MAX_STRING_LENGTH], model[MAX_STRING_LENGTH];
    int year, type;
    
    cout << "Enter vehicle type (1: Car, 2: SUV, 3: Truck): ";
    cin >> type;
    cout << "Enter make: ";
    cin >> make;
    cout << "Enter model: ";
    cin >> model;
    cout << "Enter year: ";
    cin >> year;

    Vehicle* vehicle = nullptr;

    switch(type) {
        case 1: {
            int numDoors;
            cout << "Enter number of doors: ";
            cin >> numDoors;
            Car* car = new Car();
            car->setDetails(make, model, year);
            car->setNumDoors(numDoors);
            vehicle = car;
            break;
        }
        case 2: {
            bool fourWheelDrive;
            cout << "Is it four-wheel drive? (1 for Yes, 0 for No): ";
            cin >> fourWheelDrive;
            SUV* suv = new SUV();
            suv->setDetails(make, model, year);
            suv->setFourWheelDrive(fourWheelDrive);
            vehicle = suv;
            break;
        }
        case 3: {
            double cargoCapacity;
            cout << "Enter cargo capacity (in kg): ";
            cin >> cargoCapacity;
            Truck* truck = new Truck();
            truck->setDetails(make, model, year);
            truck->setCargoCapacity(cargoCapacity);
            vehicle = truck;
            break;
        }
        default:
            cout << "Invalid vehicle type." << endl;
    }

    return vehicle;
}

int main() {
    Vehicle* fleet[100];
    int fleetSize = 0;
    char addMore;

    do {
        Vehicle* vehicle = createVehicle();
        if (vehicle) {
            fleet[fleetSize++] = vehicle;
        }
        cout << "Add another vehicle? (y/n): ";
        cin >> addMore;
    } while (addMore == 'y' || addMore == 'Y' && fleetSize < 100);

    cout << "\n fleet Information:\n";
    for (int i = 0; i < fleetSize; i++) {
        fleet[i]->displayInfo();
        cout << "Rental cost: $" << fleet[i]->calculateRentalCost() << "/day\n\n";
    }

    
    for (int i = 0; i < fleetSize; i++) {
        delete fleet[i];
    }

    return 0;
}
