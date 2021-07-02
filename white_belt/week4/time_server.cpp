#include <iostream>
#include <exception>
#include <string>

std::string AskTimeServer()
{
    /* Для тестирования повставляйте сюда код, реализующий различное поведение этой функии:
       * нормальный возврат строкового значения
       * выброс исключения system_error
       * выброс другого исключения с сообщением.
    */
}

class TimeServer
{
public:
    std::string GetCurrentTime()
    {
        /* Реализуйте этот метод:
            * если AskTimeServer() вернула значение, запишите его в last_fetched_time и верните
            * если AskTimeServer() бросила исключение system_error, верните текущее значение
            поля last_fetched_time
            * если AskTimeServer() бросила другое исключение, пробросьте его дальше.
        */
        try
        {
            last_fetched_time=AskTimeServer();
        }
        catch (const system_error& ex) { }
        return last_fetched_time;
    }
private:
    std::tring last_fetched_time = "00:00:00";
};

int main()
{
    // Меняя реализацию функции AskTimeServer, убедитесь, что это код работает корректно
    TimeServer ts;
    try
    {
        std::cout << ts.GetCurrentTime() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception got: " << e.what() << std::endl;
    }
    return 0;
}
