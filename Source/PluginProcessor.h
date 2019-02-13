/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#include "maximilian.h"
#include "libs/maxim.h"
#include "../JuceLibraryCode/JuceHeader.h"

#include <chrono>

//==============================================================================
/**
*/
class Delay_multiple_tapsAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Delay_multiple_tapsAudioProcessor();
    ~Delay_multiple_tapsAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	float pitchShifter(vector<double> &arr, double index)
	{
		int x0 = (int)index;
		int x1 = (int)(index + 1.0);
		double f0, f1;

		f0 = arr[x0];
		f1 = arr[x1];

		double result = f0 + ((f1 - f0) * (index - x0));

		return result;
	}

	// Tree state:
	AudioProcessorValueTreeState& getState();

private:

	// Tree stuff:
	ScopedPointer<AudioProcessorValueTreeState> state;

	maxiSettings maxSettings;
	maxiOsc osc1, osc2, osc3;
	maxiSample sample1, sample2;
	maxiClock clock;

	// each tap has its own counter, 
	// this is the location of the tap in the buffer:
	// We initialise the tap to different values:
	double counter = 0.0;
	int counter2 = 0;// 9 * 44100;
	int counter3 = 0;// 7 * 44100;

	/*correspondingly, if we want to change the position of the
	tap, we move it along the buffer index*/


	int bufferIndex;
	int numSamples;
	
	//int desiredSamples;
	float numSeconds;
	float dlout;
	bool resetPhase = false;
	bool changeTapLocation = false;
	float previousUserSetPosition = 1.0*44100;
	float vdt = 1.0 * 44100;

	double vol = 0.3;
	
	double outputSignal = 0.0;


	vector<double> oldBuffer;
	vector<double> taps;
	vector<double> ind;
	vector<int> dt;
	int numTaps;

	vector<double> interpTap;
	double speed = 1.0;

	AudioPlayHead* playHead;
	AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delay_multiple_tapsAudioProcessor)
};
