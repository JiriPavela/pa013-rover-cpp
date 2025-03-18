#include "resource.hpp"


Resource::Resource(int id, ResourceType t) : res_id{id}, type{t}
{}

ResourceType Resource::get_type() const
{
    return type;
}

const Task *Resource::get_allocating_task() const {
    return allocated_to;
}

bool Resource::is_available() const
{
    return status == ResourceStatus::AVAILABLE;
}

bool Resource::allocate_by(Task *task)
{
    if (task && is_available())
    {
        allocated_to = task;
        status = ResourceStatus::IN_USE;
        return true;
    }
    return false;
}

void Resource::yield_back()
{
    allocated_to = nullptr;
    status = ResourceStatus::AVAILABLE;
}