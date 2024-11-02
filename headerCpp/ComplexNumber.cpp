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

ComplexNumber ComplexNumber::operator+(ComplexNumber right) {
    ComplexNumber result;
    result.realNum = this->realNum + right.realNum;
    result.imagenryNum = this->imagenryNum + right.imagenryNum;
    return result;
};

ComplexNumber ComplexNumber::operator-(ComplexNumber right) {
    ComplexNumber result;
    result.realNum = this->realNum - right.realNum;
    result.imagenryNum = this->imagenryNum - right.imagenryNum;
    return result;
};

bool ComplexNumber::operator==(ComplexNumber right) {
    if (this->realNum == right.realNum && this->imagenryNum == this->imagenryNum)
        return true;
    return false;
};
bool ComplexNumber::operator!=(ComplexNumber right) {
    if (this->realNum != right.realNum || this->imagenryNum != this->imagenryNum)
        return true;
    return false;
};

void ComplexNumber::operator=(ComplexNumber right) {
    this->realNum = right.realNum;
    this->imagenryNum = right.imagenryNum;
}


ComplexNumber::operator int() {
    return int(this->realNum) + int(this->imagenryNum);
}