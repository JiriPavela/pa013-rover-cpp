#include "task.hpp"

Task::Task(int id, int priority, std::size_t required_time, ResourceType required)
    : id{id}, priority{priority}, required_time{required_time}, required_resource{required}
{}

ResourceType Task::get_required_resource() const {
    return required_resource;
}

std::size_t Task::get_progress() const {
    return progress;
}

bool Task::has_resource() const {
    return allocated != nullptr;
}

bool Task::is_finished() const {
    return progress == required_time;
}

void Task::allocate_resource(Resource *res) {
    if (res && res->allocate_by(this))
    {
        allocated = res;
    }
}

Resource *Task::yield_resource() {
    Resource *res = nullptr;
    if (allocated)
    {
        res = allocated;
        allocated->yield_back();
        allocated = nullptr;

    }
    return res;
}

void Task::run() {
    if (!is_finished() && allocated) {
        ++progress;
    }
}

bool operator<(const Task& lhs, const Task& rhs)
{
    return lhs.priority < rhs.priority || (lhs.priority == rhs.priority && lhs.id > rhs.id);
}

std::ostream& operator<<(std::ostream& os, const Task& task)
{
    os << "Task " << task.id << " (priority " << task.priority << ") "
       << task.progress << "/" << task.required_time;
    return os;
}