/*
 * main.cpp
 *
 * Created: 21.08.2018 09:43:03
 * Author : Conrad
 */


#include "hardware/hardware.h"
#include "animations/animations.h"
#include "test/interfaceTest.h"

int main() {
    hardwareSetup();

    // benchmark(testBenchmarkSpeed, 1);
    // testAll();
    // basic();

    runAnimations();    // while loop
}
