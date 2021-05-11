/*
  ==============================================================================

    Oscillator.cpp
    Created: 7 May 2021 3:09:30pm
    Author:  Cocii

  ==============================================================================
*/
#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(CMLS_HW2_GROUP5AudioProcessor& p) :
    processor(p)
{
    setSize(200, 200);

    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    oscMenu.addItem("Triangular", 4);
    oscMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&oscMenu);

    waveSelection = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype", oscMenu);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::aquamarine);
    g.drawText("Oscillator", titleArea, juce::Justification::centredTop);


    juce::Rectangle<float> area(25, 25, 150, 150);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    oscMenu.setBounds(area.removeFromTop(20));
}

void Oscillator::comboBoxChanged(juce::ComboBox* box)
{

}
