//
// Created by conrad on 3/15/20.
//

#pragma once

// run all tests
void testAll();

// light should transmit smoothly from von (0,0,0) to (1,0,0)
void testAddLed();

// led Cube should appear to have the same brightness the whole time
void testBrightnessTransition();

// test hsv to rgb
void testColour();

// tests if loading a Preset works
void testPreset();

// test how fast the drivers are
void testBenchmarkSpeed();

void testStraight();

void testPlain();
