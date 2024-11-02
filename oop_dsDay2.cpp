#include <iostream>
#include "./headers/ComplexNumber.hpp"

class Stairs {
public:
    void describe() {
        std::cout << "These are stairs." << std::endl;
    }
};

class Shower {
public:
    void describe() {
        std::cout << "This is a Shower." << std::endl;
    }
};

class Lamp {
public:
    void describe() {
        std::cout << "This is a lamp." << std::endl;
    }
};

class Building {
private:
    Stairs* stairs;

public:
    Building(Stairs* stairs) : stairs(stairs) {}

    void describe() {
        std::cout << "This is a building." << std::endl;
        if (stairs) {
            stairs->describe();
        }
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

public:
    Bathroom(Building* building, Lamp* lamp) : Room(building), lamp(lamp) {}
    void describe() override {
        std::cout << "This is a bathroom." << std::endl;
        shower.describe();
        if (lamp) {
            lamp->describe();
        }
    }
};

class Bedroom : public Room {
private:
    Lamp* lamp;

public:
    Bedroom(Building* building, Lamp* lamp) : Room(building), lamp(lamp) {}
    void describe() override {
        std::cout << "This is a bedroom." << std::endl;
        if (lamp) {
            lamp->describe();
        }
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

            Building building(&stairs);
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

        }
        else {
            break;
        }
    }

    return 0;
}
