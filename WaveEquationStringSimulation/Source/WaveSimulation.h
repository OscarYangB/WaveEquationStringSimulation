/*
  ==============================================================================

    WaveSimulation.h
    Created: 30 Jun 2025 11:07:58am
    Author:  Oscar

  ==============================================================================
*/

#pragma once
#include <vector>

class WaveSimulation {
public:
    WaveSimulation(int newNumberOfPoints);

    void update(double deltaTime, float frequency);

    // Position is a fraction of the string length from 0.0 to 1.0
    float getDisplacement(float position);
    void setDisplacement(float position, float displacement);

private:
    int numberOfPoints;

    std::vector<double> oldPoints;
    std::vector<double> currentPoints;
    std::vector<double> newPoints;

    // Converts frequency to Tension divided by Density of the string
    double frequencyToCoefficient(float frequency);
};
