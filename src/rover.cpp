#include "rover.hpp"

#include <utility>


Rover::Rover(std::vector<Resource> &&r, int max_concurrent_tasks)
    : max_tasks{max_concurrent_tasks}, resources{std::move(r)}
{}

std::vector<Task>::size_type Rover::remaining_tasks() const {
    return tasks.size();
}

void Rover::new_task(Task &&t) {
    auto it = tasks.cbegin();
    for (auto end = tasks.cend(); it != end && *it < t; ++it) {}
    tasks.insert(it, std::move(t));
}

std::vector<Task> Rover::step()
{
    int running_tasks_num = 0;
    std::vector<Task> finished_tasks;
    for (auto it = tasks.rbegin(); it != tasks.rend() && running_tasks_num != max_tasks; ++it) {
        if (it->has_resource()) {
            continue;
        }
        Resource *res = find_available_resource(it->get_required_resource());
        if (res) {
            it->allocate_resource(res);
            ++running_tasks_num;
        }
        else {
            Task *victim = find_task_to_yield(
                it->get_required_resource(), std::vector<Task>::const_iterator((it+1).base()));
            if (victim) {
                res = victim->yield_resource();
                it->allocate_resource(res);
                ++running_tasks_num;
            }
        }
    }
    for (auto it = tasks.begin(); it != tasks.end();) {
        if (it->has_resource()) {
            it->run();
            if (it->is_finished()) {
                it->yield_resource();
                finished_tasks.push_back(*it);
                it = tasks.erase(it);
                continue;
            }
        }
        ++it;
    }
    return finished_tasks;
}

Resource *Rover::find_available_resource(ResourceType rtype) {
    for (auto &res: resources) {
        if (res.get_type() == rtype && res.is_available()) {
            return &res;
        }
    }
    return nullptr;
}

Task *Rover::find_task_to_yield(ResourceType rtype, std::vector<Task>::const_iterator upper_bound) {
    for (auto it = tasks.begin(); it != upper_bound; ++it) {
        if (it->has_resource() && it->get_required_resource() == rtype) {
            return &*it;
        }
    }
    return nullptr;
}
