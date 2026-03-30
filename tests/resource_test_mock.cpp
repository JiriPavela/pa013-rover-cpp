#include "../src/resource.hpp"
#include "../src/task.hpp"
#include "gtest/gtest.h"


class TaskMock: public Task {
public:
    TaskMock(int id, int priority, std::size_t required_time, ResourceType required)
        : Task(id, priority, required_time, required) {}
};

struct ResourceParamTupleM {
    int id;
    ResourceType rtype;
};

class ResourceTestFixtureM : public testing::TestWithParam<ResourceParamTupleM> {
protected:
    Resource resource{GetParam().id, GetParam().rtype};

    void SetUp() override {
        std::cout << "In SetUp: " << GetParam().id << std::endl;
    }

    void TearDown() override {
        std::cout << "In TearDown: " << GetParam().id << std::endl;
    }
};

TEST_P(ResourceTestFixtureM, TestResourceTypeM){
    ASSERT_EQ(resource.get_type(), GetParam().rtype);
}

TEST_P(ResourceTestFixtureM, TestIsAvailableM){
    EXPECT_TRUE(resource.is_available());
}

TEST_P(ResourceTestFixtureM, TestYieldBackAvailableM){
    EXPECT_TRUE(resource.is_available());
    resource.yield_back();
    EXPECT_TRUE(resource.is_available());
}

TEST_P(ResourceTestFixtureM, TestAllocateByM) {
    TaskMock mtask = TaskMock(0, 10, 3, GetParam().rtype);
    resource.allocate_by(&mtask);
    EXPECT_FALSE(resource.is_available());
    EXPECT_EQ(resource.get_allocating_task(), &mtask);
}

ResourceParamTupleM resourcesM[] = {
    {0, ResourceType::CAMERA},
    {1, ResourceType::ARM},
    {2, ResourceType::ANTENNA},
    {3, ResourceType::TEMPERATURE_SENSOR}
};

INSTANTIATE_TEST_SUITE_P(ParameterizedResourceUnitTests,
                         ResourceTestFixtureM,
                         testing::ValuesIn(resourcesM));