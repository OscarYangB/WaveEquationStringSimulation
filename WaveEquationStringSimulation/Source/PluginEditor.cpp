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

    pluckSlider.setRange(juce::Range<double>(0.0, 1.0), 0.01);
    pluckSlider.setValue(audioProcessor.pluckPosition);
    pluckSlider.addListener(this);
    addAndMakeVisible(pluckSlider);

    leftMicSlider.setRange(juce::Range<double>(0.0, 1.0), 0.01);
    leftMicSlider.setValue(audioProcessor.leftMicPosition);
    leftMicSlider.addListener(this);
    addAndMakeVisible(leftMicSlider);

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

    pluckSlider.setBounds(0, 0, 400, 100);
    leftMicSlider.setBounds(0, 100, 400, 100);
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
