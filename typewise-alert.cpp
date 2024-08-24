#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return TOO_LOW;
    } else if (value > upperLimit) {
        return TOO_HIGH;
    } else {
        return NORMAL;
    }
}

void determineTemperatureLimits(CoolingType coolingType, int* lowerLimit, int* upperLimit) {
    const int lowerLimits[] = {0, 0, 0}; 
    const int upperLimits[] = {35, 45, 40}; 

    *lowerLimit = lowerLimits[coolingType];
    *upperLimit = upperLimits[coolingType];
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    int lowerLimit = 0;
    int upperLimit = 0;
    determineTemperatureLimits(coolingType, &lowerLimit, &upperLimit);
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
    const char* recepient = "a.b@c.com";
    const char* messages[] = {"", "Hi, the temperature is too low\n", "Hi, the temperature is too high\n"};

    if (breachType != NORMAL) {
        printf("To: %s\n", recepient);
        printf("%s", messages[breachType]);
    }
}

void alertByTarget(AlertTarget alertTarget, BreachType breachType) {
    void (*alertFunctions[])(BreachType) = {sendToController, sendToEmail};
    alertFunctions[alertTarget](breachType);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    alertByTarget(alertTarget, breachType); 
}
