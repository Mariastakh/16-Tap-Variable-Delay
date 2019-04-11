/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#include "maximilian.h"
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class Delay_prototype_pluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Delay_prototype_pluginAudioProcessor();
    ~Delay_prototype_pluginAudioProcessor();

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

	// Tree state:
	AudioProcessorValueTreeState& getState();

private:
	// Maximilian Objects:
	maxiOsc osc1, squareOsc, sampledWaveform, timeControl;
	maxiSample sample1, sample2, sample3, sample4, sample5, sample6, sample7, rhythmSample, volumeSample, freqAmpSample;
	maxiClock clock;
	vector<maxiSample> waveTable;

	// Tap timing variables:
	vector<maxiOsc> t;
	double tf1, tf2, tf3, tf4, tf5, tf6, ta1, ta2, ta3, ta4, ta5, ta6 = 0.0;
	vector<bool> sampleTap;
	vector<int> startPoint;
	vector<int> storedStartPoint;
	vector<double> wv;
	vector<double> rs;
	vector<double> vs;
	vector<double> fas;
	vector<double> tapVolumes;

	int waveUpdateCounter = 0;
	double wave = 0.0;
	// Buffer Traversing Variables:
	double counter = 0;
	int numSamples;
	float numSeconds;
	double outputSignal = 0.0;

	//
	vector<double> oldBuffer; // the delay line 
	vector<double> taps; // the actual sample values of each tap
	vector<double> ind; // the index of each tap
	vector<int> dt; // the delay time of each tap
	vector<double> interpTap; // interpolation samples

	// Wave table things:
	int wavetableSamplingRate = 44100;
	//double wavetableFrequency = 1.0;
	double wavetablePhase = 0.0;
	int table_len = 512;
	double table[512];

	// Slider Values:
	int numTaps = 1;
	float delayTimeGlobal = 0.1;
	float delayTimeLocal = 0.1;
	double gain = 0.0;
	int pitchPatterns = 0;
	double wavetableFrequency = 1.0;
	double wavetableAmp = 100.0;
	int readStart = 0;
	double feedbackGain = 0.0;
	double sampledWaveFrequency = 1.0;
	int bpmValue = 120;
	int beatDivision = 0;
	int sampledWaveAmplitude = 44100;
	int readStartRhythm = 0;
	float dryWetAmount = 0.5;
	int whichWave = 0;
	double dryLeft = 0.0;
	int singleWavetableLength;
	

	// Tree stuff:
	ScopedPointer<AudioProcessorValueTreeState> state;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delay_prototype_pluginAudioProcessor)
};
