/*
  ==============================================================================

    Oscillator.h
    Created: 7 May 2021 3:09:30pm
    Author:  Cocii

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public juce::Component,
                      private juce::ComboBox::Listener
{
public:
    Oscillator(CMLS_HW2_GROUP5AudioProcessor&);
    ~Oscillator();

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox*) override;

private:
    juce::ComboBox oscMenu;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CMLS_HW2_GROUP5AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
