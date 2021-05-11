/*
  ==============================================================================

    Filter.h
    Created: 7 May 2021 3:09:30pm
    Author:  Cocii

  ==============================================================================
*/
#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter: public juce::Component
{
public:
    Filter(CMLS_HW2_GROUP5AudioProcessor&);
    ~Filter();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider filterCutoff;
    juce::Slider filterRes;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> filterVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> resVal;



    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CMLS_HW2_GROUP5AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
