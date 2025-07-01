/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WaveEquationStringSimulationAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Slider::Listener
{
public:
    WaveEquationStringSimulationAudioProcessorEditor (WaveEquationStringSimulationAudioProcessor&);
    ~WaveEquationStringSimulationAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveEquationStringSimulationAudioProcessor& audioProcessor;

    juce::Label pluckLabel;
    juce::Label leftMicLabel;
    juce::Label rightMicLabel;

    juce::Slider pluckSlider;
    juce::Slider leftMicSlider;
    juce::Slider rightMicSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveEquationStringSimulationAudioProcessorEditor)
};
