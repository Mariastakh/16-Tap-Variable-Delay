/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Delay_multiple_tapsAudioProcessor::Delay_multiple_tapsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{	


	// Tree stuff:
	state = new AudioProcessorValueTreeState(*this, nullptr);
	state->createAndAddParameter("PhasorFrequency", "PhasorFreq", "PhasorFreq", NormalisableRange<float>(0.0f, 16.0f, 1.0f), 1.0f, nullptr, nullptr);
	state->createAndAddParameter("PhasorDuration", "PhasorDur", "PhasorDur", NormalisableRange<float>(0.0f, 1.0f, 0.1f), 0.0, nullptr, nullptr); // doesnt like th 5000.0f
	state->createAndAddParameter("setSampleDuration", "Samples", "Samples", NormalisableRange<float>(0.1f, 10.0f, 0.1f), 1.0, nullptr, nullptr);
	state->createAndAddParameter("setSwitch", "SwitchSlider", "SwitchSlider", NormalisableRange<float>(0.0f, 1.0f, 0.0f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("PhasorSetStart", "phasorStart", "phasorStart", NormalisableRange<float>(0.1f, 10.0f, 0.1f), 1.0, nullptr, nullptr);
	state->createAndAddParameter("phasorAmp", "phasorAmp", "phasorAmp", NormalisableRange<float>(-100000.0, 100000.0f, 1.0f), 1.0, nullptr, nullptr);
	
	state->state = ValueTree("PhasorFrequency");
	state->state = ValueTree("PhasorDuration");
	state->state = ValueTree("setSampleDuration");
	state->state = ValueTree("setSwitch");
	state->state = ValueTree("PhasorSetStart");
	state->state = ValueTree("phasorAmp");

	numSeconds = 10.0; // need to be able to vary this. also the max Duration of the phasor will be determined by the storage buffer size
	numSamples = numSeconds * 44100;
	// desiredSamples = numSamples;
	oldBuffer.resize(numSamples);
	taps.resize(16);
	ind.resize(16);
	dt.resize(16);
	interpTap.resize(16);

	clock.setTicksPerBeat(1); //not sure if needed. seems to be MIDI related
	clock.setTempo(120.0);
	
	sample1.load("/Users/pootPoot/Documents/Juce_Projects/Delay_Multiple_Taps/words.wav");
	//promisesbroken_Fm.wav
	//wood.wav

	for (int i = 0; i < numSamples; i++)
	{
		oldBuffer[i] = 0.0;
		
	}

	for (int i = 0; i < 16; i++)
	{
		taps[i] = 0.0;
		ind[i] = 0.0;
		dt[i] = 0;
		interpTap[i] = 0.0;
	
	}

	

}

Delay_multiple_tapsAudioProcessor::~Delay_multiple_tapsAudioProcessor()
{
}

//==============================================================================
const String Delay_multiple_tapsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Delay_multiple_tapsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Delay_multiple_tapsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Delay_multiple_tapsAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Delay_multiple_tapsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Delay_multiple_tapsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Delay_multiple_tapsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Delay_multiple_tapsAudioProcessor::setCurrentProgram (int index)
{
}

const String Delay_multiple_tapsAudioProcessor::getProgramName (int index)
{
    return {};
}

void Delay_multiple_tapsAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Delay_multiple_tapsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	//maxSettings.setup(sampleRate, 2, samplesPerBlock);
//	auto* device = deviceManager.getCurrentAudioDevice();

	// AudioPlayHead::CurrentPositionInfo info;
	// getPlayHead()->getCurrentPosition(info);

}

void Delay_multiple_tapsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Delay_multiple_tapsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void Delay_multiple_tapsAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	playHead = this->getPlayHead();
	playHead->getCurrentPosition(currentPositionInfo);
	int tempo = currentPositionInfo.bpm;

	clock.ticker(); // run the clock

	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// Get incoming Daw samples from buffer:
	auto* channelData0 = buffer.getReadPointer(0);
	auto* channelData1 = buffer.getReadPointer(1);

	// Get write pointer to buffer:
	auto* outputChannelData0 = buffer.getWritePointer(0);
	auto* outputChannelData1 = buffer.getWritePointer(1);

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());
		
	// Grab values from the sliders:
	int numTaps = *state->getRawParameterValue("PhasorFrequency");
	float delayTimeGlobal = *state->getRawParameterValue("setSampleDuration");
	float delayTimeLocal = *state->getRawParameterValue("PhasorDuration");
	double gain = *state->getRawParameterValue("setSwitch");
	double pFreq = *state->getRawParameterValue("PhasorSetStart");
	double pAmp = *state->getRawParameterValue("phasorAmp");
	
	vdt = (delayTimeGlobal * 44100);
	
	double dryLeft;

	for (int sample = 0; sample < buffer.getNumSamples(); sample++)
	{
		
		
		// acquire the dry signal:
		dryLeft = buffer.getReadPointer(0)[sample]; // sample1.play();

		// Set the current buffer index to the new dry signal:
		oldBuffer[counter] = dryLeft;

		counter++;
		if (counter >= (10.0 * 44100))
		{
			counter = 0;
		}
		double phasor = (osc1.phasor(0.1) *pAmp); // 10, 10000 * // pAmp
		//double phasor = (osc1.phasor(0.1) * 1000); // flanger

		outputSignal = 0;// dryLeft + (outputSignal * gain);
		for (int i = 0; i < numTaps; i++)
		{
			// one issue here is tap indexes exceeding the maximum delaytime index:
			// this is because the global delay time doesn't exceed the buffer limit,
			// but adding stuff to it does. so we need either to wrap around, or not include outliers.
			// i take care of this further down below in the next loop. 
			dt[i] = (delayTimeGlobal * 44100) +(i *(delayTimeLocal * 44100));
			//
		
			// Find the indexes of all of the taps:
			// by subtracting each tap's delaytime from the write pointer:
			ind[i] = (counter + phasor) - dt[i]; //  counter -dt[i]; 

			if (ind[i] >= 0 & ind[i] < (10 * 44100))
			{
				ind[i] = ind[i];
			}
			else if (ind[i] >= (10 * 44100)) {
				ind[i] = ind[i] - (10 * 44100);
			}
			else {
				ind[i] = ind[i] + (10 * 44100);
			}


			// if the overall delay time of any of the taps is larger than the delay buffer, than don't include it:
			if (dt[i] > 441000)
			{
				taps[i] = 0;

			}
			else { 
				
				// Interpolation : truncate the index so we have a whole number:
				interpTap[i] = int(ind[i]);
				// find the remainder:
				double frac = ind[i] - interpTap[i];
				double next = 0.0;
				// if we dont need to wrap around, then go ahead and read the next sample:
				if (interpTap[i] != (numSamples - 1))
				{
					next = oldBuffer[interpTap[i] + 1];
				} else { // else wrap-around:
					next = oldBuffer[0];
				}

				double interpolatedValue = oldBuffer[interpTap[i]] + frac * (next - oldBuffer[interpTap[i]]);
				//double outS = interpolatedValue;
				taps[i] = interpolatedValue;// interpolatedValue;// oldBuffer[ind[i]];
			}

			outputSignal += taps[i];
		}
	
		//Logger::outputDebugString(to_string(dryLeft));
		// Output:
		*outputChannelData0 = outputSignal;// *0.5;   *(1 / (numTaps + 1));
		*outputChannelData1 = outputSignal;// *0.5;

		// Increment thru DAW buffer:
		outputChannelData0++;
		outputChannelData1++;

	
			//Logger::outputDebugString(to_string(clock.currentCount)); 
		

	}


		//Logger::outputDebugString(to_string(buffer.getNumSamples()));




	
}

//========
AudioProcessorValueTreeState&  Delay_multiple_tapsAudioProcessor::getState()
{
	// returns reference to state
	return *state;
}


//==============================================================================
bool Delay_multiple_tapsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Delay_multiple_tapsAudioProcessor::createEditor()
{
    return new Delay_multiple_tapsAudioProcessorEditor (*this);
}

//==============================================================================
void Delay_multiple_tapsAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Delay_multiple_tapsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Delay_multiple_tapsAudioProcessor();
}
