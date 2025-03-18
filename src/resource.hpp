#pragma once

class Task;

enum class ResourceType {
    CAMERA,
    ARM,
    ANTENNA,
    TEMPERATURE_SENSOR
};


enum class ResourceStatus {
    AVAILABLE,
    IN_USE,
    BROKEN
};


class Resource {
public:
    Resource(int id, ResourceType t);

    ResourceType get_type() const;
    const Task *get_allocating_task() const;
    bool is_available() const;

    bool allocate_by(Task *task);
    void yield_back();

private:
    int res_id{-1};
    ResourceType type;
    ResourceStatus status{ResourceStatus::AVAILABLE};
    Task *allocated_to{nullptr};
};