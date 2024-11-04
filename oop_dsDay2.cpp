#include <iostream>
#include <vector>





class GeometricShape {
public: virtual double getArea() = 0;

public: static double getAverage(std::vector<GeometricShape*> shapes) {
    int size = GeometricShape::getSize(shapes);

    double totalArea = 0;

    for (GeometricShape* shape : shapes) {
        totalArea += shape->getArea();
    }

    return totalArea / size;
}


public: static int getSize(std::vector<GeometricShape*> shapes) {
    return shapes.size();
}
};



class Circle : public GeometricShape {
private: double r;

public:Circle(double r) {
    this->r = r;
}

public: double getArea() override {
    double area = 3.14 * (r * r);
    return area;
};
};



class Square : public GeometricShape {
private: double s;

public:Square(double s) {
    this->s = s;
}

public: double getArea() override {
    double area = s * s;
    return area;
};
};

class Rectangle : public GeometricShape {
private: double s1;
private: double s2;

public:Rectangle(double s1, double s2) {
    this->s1 = s1;
    this->s2 = s2;
}

public: double getArea() override {
    double area = s1 * s2;
    return area;
};
};

class Tringle : public GeometricShape {
private: double base;
private: double hight;

public:Tringle(double base, double hight) {
    this->base = base;
    this->hight = hight;
}

public: double getArea() override {
    double area = 0.5 * base * hight;
    return area;
};
};





void getArea(GeometricShape& g) {
    g.getArea();
}

int main()
{

    int choice;

    std::vector<GeometricShape*> shapes;

    while (true) {
        std::cout << "please select a shape:" << std::endl;
        std::cout << "1- circle" << std::endl;
        std::cout << "2- rectangle" << std::endl;
        std::cout << "3- triangle" << std::endl;
        std::cout << "4- square" << std::endl;
        std::cout << "5- get average now" << std::endl;
        std::cout << "6- get number of shapes you entered" << std::endl;
        std::cout << "7- exit" << std::endl;

        std::cin >> choice;

        if (choice == 7) return 0;

        else if (choice == 1) {
            double r;
            std::cout << "enter radius: " << std::endl;
            std::cin >> r;
            Circle* circle = new Circle(r);
            shapes.push_back(circle);
        }
        else if (choice == 2) {
            double w, h;
            std::cout << "enter width and height separated by space: " << std::endl;
            std::cin >> w >> h;
            Rectangle* rec = new Rectangle(w, h);
            shapes.push_back(rec);
        }
        else if (choice == 3) {
            double base, height;
            std::cout << "enter base and height separated by space: " << std::endl;
            std::cin >> base >> height;
            Tringle* triangle = new Tringle(base, height);
            shapes.push_back(triangle);
        }
        else if (choice == 4) {
            double s;
            std::cout << "enter side lenght:  " << std::endl;
            std::cin >> s;
            Square* square = new Square(s);
            shapes.push_back(square);
        }
        else if (choice == 5) {
            double average = GeometricShape::getAverage(shapes);
            std::cout << "Number of shapes entered: " << average << std::endl;
        }
        else if (choice == 6) {
            int size = GeometricShape::getSize(shapes);
            std::cout << "average of area of shapes entered: " << size << std::endl;
        }
        else {
            std::cout << "Enter valid entry! " << std::endl;
        }


    }

    // Circle c(5);
    // Square s(5);
    // Rectangle r(5, 6);
    // Tringle t(5, 6);

    // getArea(c);
    // getArea(s);
    // getArea(r);
    // getArea(t);


    return 0;
}