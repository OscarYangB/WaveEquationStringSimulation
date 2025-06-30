/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveEquationStringSimulationAudioProcessor::WaveEquationStringSimulationAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

WaveEquationStringSimulationAudioProcessor::~WaveEquationStringSimulationAudioProcessor()
{
}

//==============================================================================
const juce::String WaveEquationStringSimulationAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaveEquationStringSimulationAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WaveEquationStringSimulationAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WaveEquationStringSimulationAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WaveEquationStringSimulationAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaveEquationStringSimulationAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaveEquationStringSimulationAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaveEquationStringSimulationAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WaveEquationStringSimulationAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaveEquationStringSimulationAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WaveEquationStringSimulationAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void WaveEquationStringSimulationAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WaveEquationStringSimulationAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void WaveEquationStringSimulationAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (juce::MidiBufferIterator it = midiMessages.begin(); it != midiMessages.end(); it++) {
        juce::MidiMessage message = (*it).getMessage();

        if (!message.isNoteOnOrOff()) {
            continue;
        }

        if (noteOnIndex >= 0 != message.isNoteOn()) {
            noteOnIndex = message.isNoteOn() ? message.getTimeStamp() : -1;
            //timeSinceEvent = 0.f;
        }

        int noteNumber = message.getNoteNumber();
        frequency = juce::MidiMessage::getMidiNoteInHertz(noteNumber);
    }
    
    float* const* samples = buffer.getArrayOfWritePointers();

    for (int sampleNumber = 0; sampleNumber < buffer.getNumSamples(); sampleNumber++)
    {
        if (noteOnIndex == sampleNumber) {
            simulation.setDisplacement(0.2f, 0.1f);
        }

        simulation.update(1.0 / getSampleRate(), frequency);
        float output = simulation.getDisplacement(0.7f);

        for (int channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            samples[channel][sampleNumber] = output;
        }
    }

    noteOnIndex = -1;
}

//==============================================================================
bool WaveEquationStringSimulationAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WaveEquationStringSimulationAudioProcessor::createEditor()
{
    return new WaveEquationStringSimulationAudioProcessorEditor (*this);
}

//==============================================================================
void WaveEquationStringSimulationAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WaveEquationStringSimulationAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaveEquationStringSimulationAudioProcessor();
}
