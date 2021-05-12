/*
  ==============================================================================

    SynthVoice.h
    Created: 7 May 2021 3:09:30pm
    Author:  Cocii

  ==============================================================================
*/

#pragma once
//#pragma comment(lib,"Maximilian.lib")
#include <JuceHeader.h>
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public juce::SynthesiserVoice
{
    public:

    bool canPlaySound (juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    

    //==========================================================

    void setOscType(float* selection)
    {
        theWave = *selection;
    }

    //==========================================================

    double getOscType()
    {
        double waveSample;

        switch (theWave)
        {
        case 0:
            waveSample = osc1.sinewave(frequency);
            break;
        case 1:
            waveSample = osc1.saw(frequency);
            break;
        case 2:
            waveSample = osc1.square(frequency);
            break;
        case 3:
            waveSample = osc1.triangle(frequency);
            break;
        default:
            waveSample = osc1.sinewave(frequency);
            break;
        }

        return waveSample;

    }
    //==========================================================

    void setEnvParam(float* attack, float* release, float* sustain, float* decay)
    {
        env1.setAttack(double(*attack));
        env1.setRelease(double(*release));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
    }
    //==========================================================

    double getEnvelope()
    {
        return env1.adsr(getOscType(), env1.trigger);
    }
    void setFilParam(float* filterCutoff, float* filterRes)
    {
        cutoff = *filterCutoff;
        resonance = *filterRes;
    }
    //==========================================================

    //double setFilter()
    //{
    //    return filter1.lores(setEnvelope(), 100, 0.1);
    //}
    //==========================================================

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
     
    }
    
    //==========================================================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;

        if (velocity == 0)
            clearCurrentNote();
    }
    
    //==========================================================
    
    void pitchWheelMoved(int newPitchWheelValue)
    {
        
    }
    
    //==========================================================
    
    void controllerMoved(int controllerNumber, int newControllerValue)
    {
        
    }
    
    //==========================================================
    
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSample)
    {
        for (int sample = 0; sample < numSample; ++sample)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {

                outputBuffer.addSample(channel, startSample, 0.5 * getEnvelope());
            }
            ++startSample;
        }
    }
    
    //==========================================================
    
private:
    double level;
    double frequency;
    int theWave;
    float cutoff;
    float resonance;
    maxiOsc osc1;
    maxiEnv env1;
};