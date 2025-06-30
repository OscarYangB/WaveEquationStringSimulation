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

    oldPoints = std::vector<long double>(numberOfPoints);
    currentPoints = std::vector<long double>(numberOfPoints);
    newPoints = std::vector<long double>(numberOfPoints);

    /*for (int i = 1; i < numberOfPoints - 1; i++) {
        double value = 0.1 * sin(M_PI * (double)i / (double)numberOfPoints);
        oldPoints[i] = value;
        currentPoints[i] = value;
        newPoints[i] = value;
    }*/
}

void WaveSimulation::update(long double deltaTime, float frequency)
{
    for (int i = 1; i < numberOfPoints - 1; i++) {
        long double newValue = frequencyToCoefficient(frequency) * deltaTime * deltaTime *
            (currentPoints[i + 1] + currentPoints[i - 1] - 2 * currentPoints[i]);
        newValue /= 1.0 / (numberOfPoints - 1.0);
        newValue += 2.0 * currentPoints[i]  -oldPoints[i];
        newPoints[i] = newValue;
    }

    newPoints[1] /= 1.1;
    newPoints[numberOfPoints - 1] /= 1.1;

    for (int i = 1; i < numberOfPoints - 1; i++) {
        oldPoints[i] = currentPoints[i];
        currentPoints[i] = newPoints[i];
    }
}

float WaveSimulation::getDisplacement(float position)
{
    return currentPoints[getIndexFromPosition(position)];
}

void WaveSimulation::setDisplacement(float position, float displacement)
{
    for (int i = 1; i < numberOfPoints - 1; i++) {
        oldPoints[i] = 0.0;
        currentPoints[i] = 0.0;
        newPoints[i] = 0.0;
    }

    currentPoints[getIndexFromPosition(position)] = displacement;
}

long double WaveSimulation::frequencyToCoefficient(float frequency)
{
    return frequency*frequency*4.0;
}

int WaveSimulation::getIndexFromPosition(float position)
{
    int index = lround(position * numberOfPoints);

    if (index == 0) index++;
    if (index >= numberOfPoints - 1) index--;

    return index;
}
