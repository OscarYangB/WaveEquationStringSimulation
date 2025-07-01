/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveEquationStringSimulationAudioProcessorEditor::WaveEquationStringSimulationAudioProcessorEditor (WaveEquationStringSimulationAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    pluckLabel.setText("Pluck Position", juce::sendNotification);
    pluckLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(pluckLabel);
    pluckSlider.setRange(juce::Range<double>(0.0, 1.0), 0.01);
    pluckSlider.setValue(audioProcessor.pluckPosition);
    pluckSlider.addListener(this);
    addAndMakeVisible(pluckSlider);

    leftMicLabel.setText("Left Microphone Position", juce::sendNotification);
    leftMicLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(leftMicLabel);
    leftMicSlider.setRange(juce::Range<double>(0.0, 1.0), 0.01);
    leftMicSlider.setValue(audioProcessor.leftMicPosition);
    leftMicSlider.addListener(this);
    addAndMakeVisible(leftMicSlider);

    rightMicLabel.setText("Right Microphone Position", juce::sendNotification);
    rightMicLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(rightMicLabel);
    rightMicSlider.setRange(juce::Range<double>(0.0, 1.0), 0.01);
    rightMicSlider.setValue(audioProcessor.rightMicPosition);
    rightMicSlider.addListener(this);
    addAndMakeVisible(rightMicSlider);
}

WaveEquationStringSimulationAudioProcessorEditor::~WaveEquationStringSimulationAudioProcessorEditor()
{
}

//==============================================================================
void WaveEquationStringSimulationAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    pluckLabel.setBounds(0, -25, 400, 100);
    pluckSlider.setBounds(0, 0, 400, 100);

    leftMicLabel.setBounds(0, 75, 400, 100);
    leftMicSlider.setBounds(0, 100, 400, 100);

    rightMicLabel.setBounds(0, 175, 400, 100);
    rightMicSlider.setBounds(0, 200, 400, 100);
}

void WaveEquationStringSimulationAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void WaveEquationStringSimulationAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &pluckSlider) {
        audioProcessor.pluckPosition = pluckSlider.getValue();
    } else if (slider == &leftMicSlider) {
        audioProcessor.leftMicPosition = leftMicSlider.getValue();
    } else if (slider == &rightMicSlider) {
        audioProcessor.rightMicPosition = rightMicSlider.getValue();
    }
}
