#pragma once

#include <cstddef>
#include <ostream>

#include "resource.hpp"

class Task {
public:
    Task(int id, int priority, std::size_t required_time, ResourceType required);

    ResourceType get_required_resource() const;
    std::size_t get_progress() const;
    bool has_resource() const;
    bool is_finished() const;
    
    void allocate_resource(Resource *res);
    Resource *yield_resource();
    void run();

    friend bool operator<(const Task& lhs, const Task& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Task& task);

private:
    int id{-1};
    int priority{0};
    std::size_t required_time{0};
    std::size_t progress{0};
    ResourceType required_resource;
    Resource *allocated{nullptr};
};