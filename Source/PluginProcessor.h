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
    
    //My Functions:
    double tapTime(int tapIndex);
	double interpolate(double ind);
	double tapScalars(int tapIndex);
	vector<double> getWaveSamples(int a, int f);
    
	// Tree state:
	AudioProcessorValueTreeState& getState();

private:
	// Maximilian Objects:
	maxiOsc osc1, squareOsc, sampledWaveform, timeControl;
	maxiSample sample1, rhythmSample, volumeSample, freqAmpSample;
	maxiClock clock;
	vector<maxiSample> waveTable;

	// 
	vector<double> wv;
	vector<double> rs;
	vector<double> vs;
	vector<double> fas;
	vector<double> tapVolumes;
	double secondsInOneBeat;

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

	double pitchFreqArray[2][16] = { {0.01, 0.02, 0.04, 0.08, 0.16, 0.32, 0.64, 1.28, 2.56, 5.12, 10.24, 20.48, 0.01, 0.02, 0.04, 0.08}, 
									 {20.48, 10.24, 5.12, 2.56, 1.28, 0.64, 0.32, 0.16, 0.08, 0.04, 0.02, 0.01, 20.48, 10.24, 5.12, 2.56}};

	
	double pitchAmpArray[2][16] = { {5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0},
									{503.0, 30.0, 12.0, 5231.9, 2801.7, 3583.6, 30.0, 500.0, 1000.0, 2333.0, 4567.4, 4444.0, 2345.5, 400.0, 758.0, 335.7} };
									
									 
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
	int pitchAmpPatterns = 0;
	int pitchFreqPatterns = 0;
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
