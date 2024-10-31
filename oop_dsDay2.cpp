#include <iostream>
#include "./headers/ComplexNumber.hpp"
#include "./headers/TreasureGame.hpp"

int main() {
    int choice;

    while (true) {
        std::cout << "Please choose 1 for the first challenge, 2 for the second, 3 to play the game, or any other number to exit: ";
        std::cin >> choice;

        if (choice == 1) {
            ComplexNumber num1(5, 6);
            ComplexNumber num2(7, 10.5);

            num1.displayComplex();
            num2.displayComplex();

            ComplexNumber num3 = ComplexNumber::addComplex(num1, num2);
            num3.displayComplex();

            ComplexNumber num4 = ComplexNumber::substractComplex(num1, num2);
            num4.displayComplex();
        }
        else if (choice == 2) {
            ComplexNumber userNum1 = ComplexNumber(3, 4);
            ComplexNumber userNum2 = ComplexNumber(5, 6);
            ComplexNumber emptyNum = ComplexNumber();

            emptyNum.displayComplex();


            ComplexNumber::getComplexCount();

            emptyNum.~ComplexNumber();

            ComplexNumber::getComplexCount();

            userNum1.displayComplex();
            userNum2.displayComplex();

            ComplexNumber userNum3 = ComplexNumber::addComplex(userNum1, userNum2);
            userNum3.displayComplex();


            ComplexNumber userNum4 = ComplexNumber::substractComplex(userNum1, userNum2);
            userNum4.displayComplex();

            ComplexNumber::getComplexCount();

        }
        else if (choice == 3) {
            Game game;
            game.play();
        }
        else {
            break;
        }
    }

    return 0;
}
