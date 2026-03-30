#include "../src/resource.hpp"
#include "gtest/gtest.h"


TEST(ResourceTestSuite, TestResourceType){
    Resource r1(0, ResourceType::CAMERA);
    Resource r2(1, ResourceType::ARM);
    Resource r3(2, ResourceType::ANTENNA);
    Resource r4(3, ResourceType::TEMPERATURE_SENSOR);

    ASSERT_EQ(r1.get_type(), ResourceType::CAMERA);
    ASSERT_EQ(r2.get_type(), ResourceType::ARM);
    ASSERT_EQ(r3.get_type(), ResourceType::ANTENNA);
    ASSERT_EQ(r4.get_type(), ResourceType::TEMPERATURE_SENSOR);
}

TEST(ResourceTestSuite, TestIsAvailable){
    Resource r1(0, ResourceType::CAMERA);
    Resource r2(1, ResourceType::ARM);
    Resource r3(2, ResourceType::ANTENNA);
    Resource r4(3, ResourceType::TEMPERATURE_SENSOR);

    EXPECT_TRUE(r1.is_available());
    EXPECT_TRUE(r2.is_available());
    EXPECT_TRUE(r3.is_available());
    EXPECT_TRUE(r4.is_available());
}

TEST(ResourceTestSuite, TestYieldBackAvailable){
    Resource r1(0, ResourceType::CAMERA);
    Resource r2(1, ResourceType::ARM);
    Resource r3(2, ResourceType::ANTENNA);
    Resource r4(3, ResourceType::TEMPERATURE_SENSOR);

    EXPECT_TRUE(r1.is_available());
    r1.yield_back();
    EXPECT_TRUE(r1.is_available());

    EXPECT_TRUE(r2.is_available());
    r2.yield_back();
    EXPECT_TRUE(r2.is_available());

    EXPECT_TRUE(r3.is_available());
    r3.yield_back();
    EXPECT_TRUE(r3.is_available());

    EXPECT_TRUE(r4.is_available());
    r4.yield_back();
    EXPECT_TRUE(r4.is_available());
}
