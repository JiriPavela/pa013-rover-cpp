#pragma once

#include <vector>

#include "resource.hpp"
#include "task.hpp"


// The Rover itself
class Rover {
public:
    Rover(std::vector<Resource> &&r, int max_concurrent_tasks);

    std::vector<Task>::size_type remaining_tasks() const;
    
    void new_task(Task &&t);
    std::vector<Task> step();

private:
    Resource *find_available_resource(ResourceType rtype);
    Task *find_task_to_yield(ResourceType rtype, std::vector<Task>::const_iterator upper_bound);

    int max_tasks;
    std::vector<Resource> resources;
    std::vector<Task> tasks;
};