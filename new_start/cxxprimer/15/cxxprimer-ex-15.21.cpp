/******************************************************************************
* File:             cxxprimer-ex-15.21.cpp
*
* Author:           yychi  
* Created:          2019-07-12 20:03 
*****************************************************************************/

#include <iostream>
#include <cmath>

const double PI = 3.141592653;

namespace shape
{

class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default;
    virtual double Area() = 0;
    virtual double Volume() = 0;
};

class Rect : public Shape {
public:
    Rect() = delete;
    
    Rect(double w, double h):
        width_(w), height_(h) { }

    virtual double Area() override { return width_ * height_; } 

    virtual double Volume() override { return 0; }

protected:
    double width_;
    double height_;
};

class Circle : public Shape {
public:
    Circle() = delete;

    Circle(double r): radius_(r) { }

    virtual double Area() override { return PI * pow(radius_, 2); } 

    virtual double Volume() override { return 0; }

protected:
    double radius_;
};

class Ball : public Circle {
public:
    Ball() = delete;

    Ball(double r): Circle(r) { }

    virtual double Area() override { return Circle::Area(); }

    virtual double Volume() override {
        return 4.0 / 3 * PI * pow(radius_, 3); 
    }
};

class CirCone : public Circle {
public:
    CirCone() = delete;

    CirCone(double r, double h):
        Circle(r), height_(h) { }

    virtual double Area() override { return Circle::Area(); }

    virtual double Volume() override
    {
        return 1.0 / 3 * PI * pow(radius_, 2) * height_;
    }

private:
    double height_;
};

void printer(Shape& shape)
{
    std::cout << "Area: " << shape.Area()
        << "\nVolume: " << shape.Volume() << std::endl;
}

} // namespace shape

// test
int main()
{
    double radius = 5.5;
    double height = 10.1;
    shape::Rect rect(radius, height);
    shape::Circle circle(radius);
    shape::Ball ball(radius);
    shape::CirCone  circone(radius, height);
    shape::printer(rect);
    shape::printer(circle);
    shape::printer(ball);
    shape::printer(circone);
    std::cout << circone.Volume();

    return 0;
}
