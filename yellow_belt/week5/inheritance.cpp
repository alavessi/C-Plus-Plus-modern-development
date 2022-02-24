#include <iostream>

class Animal
{
public:
    Animal(const std::string& name): Name(name) {}

    const std::string Name;
};

class Dog: public Animal
{
public:
    Dog(const std::string& name): Animal(name) {}

    void Bark()
    {
        std::cout << Name << " barks: woof!" << std::endl;
    }
};
