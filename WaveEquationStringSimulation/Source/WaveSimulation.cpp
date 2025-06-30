/*
  ==============================================================================

    WaveSimulation.cpp
    Created: 30 Jun 2025 11:07:58am
    Author:  Oscar

  ==============================================================================
*/

#define _USE_MATH_DEFINES

#include "WaveSimulation.h"
#include <cmath>

WaveSimulation::WaveSimulation(int newNumberOfPoints)
{
    numberOfPoints = newNumberOfPoints;

    oldPoints = std::vector<double>(numberOfPoints);
    currentPoints = std::vector<double>(numberOfPoints);
    newPoints = std::vector<double>(numberOfPoints);

    /*for (int i = 1; i < numberOfPoints - 1; i++) {
        double value = 0.1 * sin(M_PI * (double)i / (double)numberOfPoints);
        oldPoints[i] = value;
        currentPoints[i] = value;
        newPoints[i] = value;
    }*/
}

void WaveSimulation::update(double deltaTime, float frequency)
{
    for (int i = 1; i < numberOfPoints - 1; i++) {
        double newValue = frequencyToCoefficient(frequency) * deltaTime * deltaTime *
            (currentPoints[i + 1] + currentPoints[i - 1] - 2 * currentPoints[i]);
        newValue /= 1.0 / (numberOfPoints - 1.0);
        newValue += 2.0 * currentPoints[i]  -oldPoints[i];
        newPoints[i] = newValue;
    }

    for (int i = 1; i < numberOfPoints - 1; i++) {
        oldPoints[i] = currentPoints[i];
        currentPoints[i] = newPoints[i];
    }
}

float WaveSimulation::getDisplacement(float position)
{
    int index = lround(position * numberOfPoints);
    return currentPoints[index];
}

void WaveSimulation::setDisplacement(float position, float displacement)
{
    for (int i = 1; i < numberOfPoints - 1; i++) {
        oldPoints[i] = 0.0;
        currentPoints[i] = 0.0;
        newPoints[i] = 0.0;
    }

    int index = lround(position * numberOfPoints);
    currentPoints[index] = displacement;
}

double WaveSimulation::frequencyToCoefficient(float frequency)
{
    return frequency*frequency*4.0;
}
