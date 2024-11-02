#pragma once
#include <iostream>

class ComplexNumber {
private:
    double realNum = 0;
    double imagenryNum = 0;
    static int complexCounter;




public: ComplexNumber(const ComplexNumber& num) {
    this->realNum = num.realNum;
    this->imagenryNum = num.imagenryNum;
    ComplexNumber::complexCounter++;
}


public: ComplexNumber() {
    ComplexNumber::complexCounter++;
}

public: ComplexNumber(double realNum, double imagenryNum) {
    this->realNum = realNum;
    this->imagenryNum = imagenryNum;
    ComplexNumber::complexCounter++;
}

public: ~ComplexNumber() {
    ComplexNumber::complexCounter--;
}

public: static ComplexNumber addComplex(ComplexNumber num1, ComplexNumber num2);

public: static ComplexNumber substractComplex(ComplexNumber num1, ComplexNumber num2);

public: void displayComplex();

public: static void getComplexCount();

public:ComplexNumber operator+(ComplexNumber right);
public:ComplexNumber operator-(ComplexNumber right);
public:bool operator==(ComplexNumber right);
public:bool operator!=(ComplexNumber right);
public:void operator=(ComplexNumber right);
public: operator int();
};