#include <iostream>
#include <string>
#include <map>
#include <utility>

// Перечислимый тип для статуса задачи
enum class TaskStatus
{
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks
{
private:
    std::map<std::string, TasksInfo> dev_tasks;
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const std::string& person) const
    {
        return dev_tasks.at(person);
    }
    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const std::string& person)
    {
        dev_tasks[person][TaskStatus::NEW]++;
    }
  
    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count)
    {
        if (!dev_tasks.count(person))
        {
            TasksInfo updated_tasks,untouched_tasks;
            return std::make_tuple(updated_tasks,untouched_tasks);
        }
        TasksInfo tasks = dev_tasks[person];
        TasksInfo reserve = tasks;
        TasksInfo in=tasks, out=tasks;
        for (auto status: TaskStatus)
        {
            in[status]=0;
            out[status]=0;
        }
        for (auto status = TaskStatus::NEW; status != TaskStatus::DONE; status++)
        {
            if (tasks[status] >= task_count)
            {
                out[status] += task_count;
                in[status+1] += task_count;
                task_count = 0;
            }
            else
            {
                task_count -= tasks[status];
                in[status+1] += tasks[status];
                out[status] += tasks[status];
            }
        }

        for (auto status = TaskStatus::NEW; status != TaskStatus::DONE; status++)
        {
            if (tasks[status] >= task_count)
            {
                reserve[status] -= task_count;
                reserve[status+1] += task_count;
                task_count = 0;
            }
            else
            {
                task_count -= tasks[status];
                reserve[status+1] += tasks[status];
                tasks[status] = 0;
            }
        }

    }
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info)
{
    std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}

int main()
{
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; i++)
    {
        tasks.AddNewTask("Ivan");
    }
    std::cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    std::cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
    TasksInfo updated_tasks, untouched_tasks;
  
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
  
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}
