#include <iostream>

#include "rover.hpp"


int main() {
    Rover rover(std::vector<Resource>{
        Resource(0, ResourceType::CAMERA),
        Resource(1, ResourceType::ANTENNA),
        Resource(2, ResourceType::ARM),
        Resource(3, ResourceType::TEMPERATURE_SENSOR)
    }, 2);

    rover.new_task(Task(0, 4, 1, ResourceType::CAMERA));
    rover.new_task(Task(1, 6, 2, ResourceType::ANTENNA));
    rover.new_task(Task(2, 3, 4, ResourceType::ARM));
    rover.new_task(Task(3, 1, 7, ResourceType::ANTENNA));
    rover.new_task(Task(4, 6, 2, ResourceType::CAMERA));
    rover.new_task(Task(5, 2, 3, ResourceType::CAMERA));
    rover.new_task(Task(6, 6, 5, ResourceType::CAMERA));

    int step = 1;
    while (rover.remaining_tasks() > 0) {
        std::cout << "Step " << step << std::endl;
        for (auto &finished: rover.step()) {
            std::cout << " " << finished << " finished" << std::endl;
        }
        ++step;
    }

    return 0;
}
