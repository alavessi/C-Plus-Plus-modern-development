#include <iostream>
#include <vector>

class Human
{
protected:
    const std::string Name;

public:
    const std::string Type;

    Human(const std::string name, std::string type) : Name(name), Type(type) {}

    virtual void Walk(const std::string& destination)
    {
        std::cout << Type << ": " << Name << " walks to: " << destination << std::endl;
    }
};


class Student : public Human
{
public:
    Student(const std::string& name, const std::string& favouriteSong) : Human(name, "Student"), FavouriteSong(favouriteSong) {}

    std::ostream& Log()
    {
        std::cout << "Student: " << Name;
        return std::cout;
    }

    void Learn()
    {
        Log() << " learns" << std::endl;
    }

    void SingSong()
    {
        Log() << " sings a song: " << FavouriteSong << std::endl;
    }

    void Walk(const std::string& destination)
    {
        Log() << " walks to: " << destination << std::endl;
        SingSong();
    }

private:
    const std::string FavouriteSong;
};


class Teacher : public Human
{
public:
    Teacher(const std::string& name, const std::string& subject) : Human(name, "Teacher"), Subject(subject) {}

    void Teach() const
    {
        std::cout << "Teacher: " << Name << " teaches: " << Subject << std::endl;
    }

private:
    const std::string Subject;
};


class Policeman : public Human
{
public:
    Policeman(const std::string& name) : Human(name, "Policeman") {}

    void Check(const Human& h) const
    {
        std::cout << "Policeman: " << Name << " checks " << h.Type << ". " << h.Type << "'s name is: " << h.Type << std::endl;
    }
};

void VisitPlaces(Human& h, const std::vector<std::string>& places)
{
    for (auto p : places)
    {
        h.Walk(p);
    }
}

int main()
{
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
