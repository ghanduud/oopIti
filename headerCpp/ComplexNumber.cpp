#include "../headers/ComplexNumber.hpp"
#include <iostream>

int ComplexNumber::complexCounter = 0;

ComplexNumber ComplexNumber::addComplex(ComplexNumber num1, ComplexNumber num2) {
    ComplexNumber num = ComplexNumber(num1.realNum + num2.realNum, num1.imagenryNum + num2.imagenryNum);
    return num;
}

ComplexNumber ComplexNumber::substractComplex(ComplexNumber num1, ComplexNumber num2) {
    ComplexNumber num = ComplexNumber(num1.realNum - num2.realNum, num1.imagenryNum - num2.imagenryNum);
    return num;
}

void ComplexNumber::displayComplex() {
    std::cout << this->realNum << " + " << this->imagenryNum << "i" << std::endl;
}

void ComplexNumber::getComplexCount() {
    std::cout << "current count is : " << complexCounter << std::endl;
}