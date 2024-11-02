#include <iostream>
#include "./headers/ComplexNumber.hpp"

class Stairs {
private:
    int stepsRemaining;

public:
    Stairs() : stepsRemaining(0) {}

    void describe() {
        std::cout << "These are stairs." << std::endl;
    }

    void climb(int steps) {
        stepsRemaining = steps;
        while (stepsRemaining > 0) {
            std::cout << "Climbing... " << stepsRemaining << " steps left." << std::endl;
            --stepsRemaining;
        }
        std::cout << "Reached the destination!" << std::endl;
    }
};

class Shower {
public:
    void describe() {
        std::cout << "This is a shower." << std::endl;
    }

    void useShower() {
        std::cout << "Using the shower." << std::endl;
    }
};

class Lamp {
private:
    bool isOn;

public:
    Lamp() : isOn(false) {}

    void describe() {
        std::cout << "This is a lamp." << std::endl;
        std::cout << (isOn ? "The lamp is currently on." : "The lamp is currently off.") << std::endl;
    }

    void turnOn() {
        isOn = true;
        std::cout << "Lamp turned on." << std::endl;
    }

    void turnOff() {
        isOn = false;
        std::cout << "Lamp turned off." << std::endl;
    }
};

class Building {
private:
    Stairs* stairs;
    int floors;
    int roomCount;

public:
    Building(Stairs* stairs, int floors = 1, int roomCount = 0) : stairs(stairs), floors(floors), roomCount(roomCount) {}

    void describe() {
        std::cout << "This is a building with " << floors << " floors and " << roomCount << " rooms." << std::endl;
        if (stairs) {
            stairs->describe();
        }
    }

    int getFloorCount() const {
        return floors;
    }

    void addFloor() {
        ++floors;
        std::cout << "Added a floor. Total floors: " << floors << std::endl;
    }

    void addRoom() {
        ++roomCount;
        std::cout << "Added a room. Total rooms: " << roomCount << std::endl;
    }
};

class Room {
protected:
    Building* building;

public:
    Room(Building* building) : building(building) {}
    virtual void describe() = 0;
};

class Bathroom : public Room {
private:
    Shower shower;
    Lamp* lamp;
    bool isOccupied;

public:
    Bathroom(Building* building, Lamp* lamp) : Room(building), lamp(lamp), isOccupied(false) {}

    void describe() override {
        std::cout << "This is a bathroom." << std::endl;
        shower.describe();
        if (lamp) {
            lamp->describe();
        }
    }

    void useShower() {
        if (!isOccupied) {
            std::cout << "Using the bathroom shower." << std::endl;
            shower.useShower();
            isOccupied = true;
        }
        else {
            std::cout << "Bathroom is occupied. Please wait." << std::endl;
        }
    }

    void cleanBathroom() {
        std::cout << "Cleaning the bathroom..." << std::endl;
        isOccupied = false;
    }

    bool isBathroomOccupied() const {
        return isOccupied;
    }
};

class Bedroom : public Room {
private:
    Lamp* lamp;
    bool occupied;
    bool nightMode;

public:
    Bedroom(Building* building, Lamp* lamp) : Room(building), lamp(lamp), occupied(false), nightMode(false) {}

    void describe() override {
        std::cout << "This is a bedroom." << std::endl;
        if (lamp) {
            lamp->describe();
        }
        std::cout << (occupied ? "The bedroom is occupied." : "The bedroom is empty.") << std::endl;
    }

    void setOccupancy(bool status) {
        occupied = status;
        std::cout << (occupied ? "The bedroom is now occupied." : "The bedroom is now empty.") << std::endl;
    }

    bool isOccupied() const {
        return occupied;
    }

    void turnOnNightMode() {
        nightMode = true;
        std::cout << "Night mode activated: dimming lights and setting quiet ambiance." << std::endl;
        if (lamp) lamp->turnOff();
    }

    void turnOffNightMode() {
        nightMode = false;
        std::cout << "Night mode deactivated." << std::endl;
        if (lamp) lamp->turnOn();
    }
};

int main() {
    int choice;

    while (true) {
        std::cout << "Please choose 1 for the first challenge, 2 for the second, or any other number to exit: ";
        std::cin >> choice;

        if (choice == 1) {
            ComplexNumber num1(5, 6);
            ComplexNumber num2(7, 10.5);

            num1.displayComplex();
            num2.displayComplex();

            ComplexNumber num3 = num1 + num2;
            num3.displayComplex();

            ComplexNumber num4 = num1 - num2;
            num4.displayComplex();

            ComplexNumber num5(7, 10.5);

            if (num5 == num2) std::cout << "both equal" << std::endl;
            if (num5 != num1) std::cout << "both not equal" << std::endl;

            num5 = num1;

            num5.displayComplex();

            int num6 = int(num2);
            num2.displayComplex();
            std::cout << num6 << std::endl;

        }
        else if (choice == 2) {
            Stairs stairs;

            Building building(&stairs, 3);
            building.addRoom();
            building.describe();

            Lamp lamp1;
            Lamp lamp2;
            Lamp lamp3;

            Bathroom bathroom1(&building, &lamp1);
            Bathroom bathroom2(&building, &lamp2);
            Bedroom bedroom1(&building, &lamp1);
            Bedroom bedroom2(&building, &lamp3);

            std::cout << "Describing rooms in the building:" << std::endl;

            bathroom1.describe();
            bathroom2.describe();
            bedroom1.describe();
            bedroom2.describe();

            bathroom1.useShower();
            bathroom1.cleanBathroom();

            bedroom1.setOccupancy(true);
            bedroom2.turnOnNightMode();

            stairs.climb(5);

        }
        else {
            break;
        }
    }

    return 0;
}
