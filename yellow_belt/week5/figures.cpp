#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>

#define pi 3.14

class Figure
{
public:
    virtual std::string Name() const = 0;
    virtual double Perimeter() const =0;
    virtual double Area() const = 0;
};

class Triangle : public Figure
{
public:
    Triangle(unsigned int a, unsigned int b, unsigned int c) : a_(a), b_(b), c_(c) {}
    std::string Name() const override
    {
        return "TRIANGLE";
    }
    double Perimeter() const override
    {
        return a_ + b_ + c_;
    }
    double Area() const override
    {
        double p = Perimeter() / 2;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

private:
    unsigned int a_, b_, c_;
};

class Rect : public Figure
{
public:
    Rect(unsigned int width, unsigned int height) : width_(width), height_(height) {}
    std::string Name() const override
    {
        return "RECT";
    }
    double Perimeter() const override
    {
        return 2 * (width_ + height_);
    }
    double Area() const override
    {
        return width_ * height_;
    }

private:
    unsigned int width_, height_;
};

class Circle : public Figure
{
public:
    Circle(unsigned int r) : r_(r) {}
    std::string Name() const override
    {
        return "CIRCLE";
    }
    double Perimeter() const override
    {
        return 2 * pi * r_;
    }
    double Area() const override
    {
        return pi * r_ * r_;
    }

private:
    unsigned int r_;
};

std::shared_ptr<Figure> CreateFigure(std::istringstream& is)
{
    std::string type;
    is >> type;
    if (type == "RECT")
    {
        unsigned int width, height;
        is >> width >> height;
        return std::make_shared<Rect>(width, height);
    }
    else if (type == "TRIANGLE")
    {
        unsigned int a, b, c;
        is >> a >> b >> c;
        return std::make_shared<Triangle>(a, b, c);
    }
    else
    {
        unsigned int r;
        is >> r;
        return std::make_shared<Circle>(r);
    }
}

int main()
{
    std::vector<std::shared_ptr<Figure>> figures;
    for (std::string line; getline(std::cin, line); )
    {
        std::istringstream is(line);

        std::string command;
        is >> command;
        if (command == "ADD")
        {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> std::ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT")
        {
            for (const auto& current_figure : figures)
            {
                std::cout << std::fixed << std::setprecision(3)
                << current_figure->Name() << " "
                << current_figure->Perimeter() << " "
                << current_figure->Area() << std::endl;
            }
        }
    }
    return 0;
}