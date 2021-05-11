/*
  ==============================================================================

    Envelope.h
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
class Envelope    : public juce::Component
{
public:
    Envelope(CMLS_HW2_GROUP5AudioProcessor&);
    ~Envelope();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Slider releaseSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider attackSlider;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> attackVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> decayVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> sustainVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> releaseVal;


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CMLS_HW2_GROUP5AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
