#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, TestInferBreach) {
    ASSERT_EQ(inferBreach(12.5, 20.0, 30.0), TOO_LOW);
    ASSERT_EQ(inferBreach(25.0, 20.0, 30.0), NORMAL);
    ASSERT_EQ(inferBreach(35.0, 20.0, 30.0), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, TestClassifyTemperatureBreach) {
    ASSERT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 25.0), NORMAL);
    ASSERT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36.0), TOO_HIGH);
    ASSERT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46.0), TOO_HIGH);
    ASSERT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 39.0), NORMAL);
}

TEST(TypeWiseAlertTestSuite, TestCheckAndAlert) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};
    checkAndAlert(TO_CONTROLLER, batteryChar, 20.0);
    checkAndAlert(TO_EMAIL, batteryChar, 36.0);    
}
