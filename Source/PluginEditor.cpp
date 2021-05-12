/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CMLS_HW2_GROUP5AudioProcessorEditor::CMLS_HW2_GROUP5AudioProcessorEditor(CMLS_HW2_GROUP5AudioProcessor& p)
 : AudioProcessorEditor (&p), processor (p), oscGUI(p), envGUI(p), filterGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //setSize (400, 300);
    //setSize (600, 400);
    setSize (600, 200);
    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
}

CMLS_HW2_GROUP5AudioProcessorEditor::~CMLS_HW2_GROUP5AudioProcessorEditor()
{
}

//==============================================================================
void CMLS_HW2_GROUP5AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    /*g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);*/
}

void CMLS_HW2_GROUP5AudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;

    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));

}

//void CMLS_HW2_GROUP5AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
//{
//    if (slider == &attackSlider)
//    {
//        processor.attackTime = attackSlider.getValue();
//    }
//    if (slider == &releaseSlider)
//    {
//        processor.attackTime = releaseSlider.getValue();
//    }
//}