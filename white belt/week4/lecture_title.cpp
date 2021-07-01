#include <string>

struct Specialization
{
    std::string name;
    explicit Specialization(const std::string& new_name)
    {
        name=new_name;
    }
};
struct Course
{
    std::string name;
    explicit Course(const std::string& new_name)
    {
        name=new_name;
    }
};
struct Week
{
    std::string name;
    explicit Week(const std::string& new_name)
    {
        name=new_name;
    }
};
struct LectureTitle
{
    std::string specialization, course, week;
    LectureTitle(Specialization new_specialization, Course new_course, Week new_week)
    {
        specialization=new_specialization.name;
        course=new_course.name;
        week=new_week.name;
    }
};
