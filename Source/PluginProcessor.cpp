#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Delay_prototype_pluginAudioProcessor::Delay_prototype_pluginAudioProcessor()
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
	state->createAndAddParameter("NumTaps", "NumTaps", "NumTaps", NormalisableRange<float>(0.0f, 16.0f, 1.0f), 1.0f, nullptr, nullptr);
	state->createAndAddParameter("phasorAmp", "phasorAmp", "phasorAmp", NormalisableRange<float>(0.0, 2.0f, 1.0f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("pitchFreq", "pitchFreq", "pitchFreq", NormalisableRange<float>(0.0, 2.0f, 1.0f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("wavetableFrequency", "wavetableFrequency", "wavetableFrequency", NormalisableRange<float>(0.001f, 30.0f, 0.01f), 1.0, nullptr, nullptr);
	//
	state->createAndAddParameter("dryWet", "dryWet", "dryWet", NormalisableRange<float>(0.0f, 1.0f, 0.1f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("feedbackGain", "feedbackGain", "feedbackGain", NormalisableRange<float>(0.0f, 0.9f, 0.1f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("drySignalVolume", "drySignalVolume", "drySignalVolume", NormalisableRange<float>(0.0f, 7800.0f, 600.0f), 0.0, nullptr, nullptr);
	//
	state->createAndAddParameter("wavetableAmplitude", "wavetableAmplitude", "wavetableAmplitude", NormalisableRange<float>(0.0f, 12000.0f, 0.1f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("waveSelect", "waveSelect", "waveSelect", NormalisableRange<float>(0.0f, 7800.0f, 600.0f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("sampledWaveFrequency", "sampledWaveFrequency", "sampledWaveFrequency", NormalisableRange<float>(0.01, 5.0, 0.01f), 0.01, nullptr, nullptr);
	//
	state->createAndAddParameter("sampledWaveAmplitude", "sampledWaveAmplitude", "sampledWaveAmplitude", NormalisableRange<float>(0.0f, 220500.0f, 1.0f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("beatDivision", "beatDivision", "beatDivision", NormalisableRange<float>(0.0f, 7800.0f, 600.0f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("bpm", "bpm", "bpm", NormalisableRange<float>(20.0f, 710.0f, 1.0f), 120.0, nullptr, nullptr);

	//

	state->state = ValueTree("NumTaps"); 
	state->state = ValueTree("wavetableFrequency");
	state->state = ValueTree("phasorAmp");
	state->state = ValueTree("pitchFreq");
	state->state = ValueTree("dryWet");
	state->state = ValueTree("feedbackGain");
	state->state = ValueTree("drySignalVolume");
	state->state = ValueTree("wavetableAmplitude");
	state->state = ValueTree("waveSelect");
	state->state = ValueTree("sampledWaveFrequency");
	state->state = ValueTree("sampledWaveAmplitude");
	state->state = ValueTree("beatDivision");
	state->state = ValueTree("bpm");


	//==============================================
	//
	// Buffer initialisations:
	numSeconds = 10.0; // need to be able to vary this. also the max Duration of the phasor will be determined by the storage buffer size
	numSamples = numSeconds * 44100;
	// desiredSamples = numSamples;
	oldBuffer.resize(numSamples);
	taps.resize(16);
	ind.resize(16);
	dt.resize(16);
	interpTap.resize(16);
	wv.resize(16);
	tapVolumes.resize(16);
	

	//sample1.load("/Users/pootPoot/Documents/Juce_Projects/Delay_Multiple_Taps/words.wav");
	sample1.load("/Users/pootPoot/Documents/Juce_Projects/Delay_Multiple_Taps/wood.wav");
	//rhythmSample.load("/Users/pootPoot/Documents/Juce_Projects/AKWF-FREE-master/AKWF/AKWF_bw_blended/AKWF_blended_0015.wav");
	//rhythmSample.load("/Users/Pootpoot/Documents/Juce_Projects/Delay_Prototype_Plugin/fifteen_wavetables_from_AWF_001.wav");
	rhythmSample.load("/Users/Pootpoot/Documents/Juce_Projects/Delay_Prototype_Plugin/fifteen_wavetables_from_AWF_001.wav");
	volumeSample.load("/Users/Pootpoot/Documents/Juce_Projects/Delay_Prototype_Plugin/fifteen_wavetables_from_AWF_001.wav");
	freqAmpSample.load("/Users/Pootpoot/Documents/Juce_Projects/Delay_Prototype_Plugin/fifteen_wavetables_from_AWF_001.wav");
	
	// transferring the samples from the rhythm wavetable into an array:
	int rsize = rhythmSample.getLength();
	rs.resize(rsize);
	
	// transferring the samples from the volume wavetable into an array:
	int vsize = volumeSample.getLength();
	vs.resize(vsize);
	singleWavetableLength = vsize / 14; // should be 600

	for(int i = 0;i < rsize; i++)
	{
		rs[i] = (rhythmSample.play()+1) / 2;
		vs[i] = (volumeSample.play() + 1) / 2;
		//fas[i] = (freqAmpSample.play() + 1) / 2;
	}


	
	for (int i = 0; i < numSamples; i++)
	{
		oldBuffer[i] = 0.0;
	}

	for (int i = 0;i < 16; i++)
	{
		taps[i] = 0.0;
		ind[i] = 0.0;
		dt[i] = 0;
		interpTap[i] = 0.0;
		tapVolumes[i] = 0.0;
		wv[i] = 0.0;
	}

	//Logger::outputDebugString(to_string(k));
}

Delay_prototype_pluginAudioProcessor::~Delay_prototype_pluginAudioProcessor()
{
}

//==============================================================================
const String Delay_prototype_pluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Delay_prototype_pluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Delay_prototype_pluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Delay_prototype_pluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Delay_prototype_pluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Delay_prototype_pluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Delay_prototype_pluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Delay_prototype_pluginAudioProcessor::setCurrentProgram (int index)
{
}

const String Delay_prototype_pluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Delay_prototype_pluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Delay_prototype_pluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Delay_prototype_pluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Delay_prototype_pluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Delay_prototype_pluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	
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

	// Grab UI Variables here
	numTaps = *state->getRawParameterValue("NumTaps");
	pitchAmpPatterns = *state->getRawParameterValue("phasorAmp");
	pitchFreqPatterns = *state->getRawParameterValue("pitchFreq");
	wavetableFrequency = *state->getRawParameterValue("wavetableFrequency");
	dryWetAmount = *state->getRawParameterValue("dryWet");
	feedbackGain = *state->getRawParameterValue("feedbackGain");
	readStart = *state->getRawParameterValue("drySignalVolume");
	wavetableAmp = *state->getRawParameterValue("wavetableAmplitude");
	whichWave = *state->getRawParameterValue("waveSelect");
	readStartRhythm = *state->getRawParameterValue("beatDivision");
	bpmValue = *state->getRawParameterValue("bpm");
	sampledWaveAmplitude = *state->getRawParameterValue("sampledWaveAmplitude");
	sampledWaveFrequency = *state->getRawParameterValue("sampledWaveFrequency");
	
	
	// Convert BPM value to milliseconds
	// ---------------------
		double beatsToMs = (60000 / bpmValue) * 1.0; // 1.0 represents a quarter note/crotchet
		secondsInOneBeat = 60.0 / bpmValue;
		
	//------------------------------------
	
	// Calculate Volume Scalars:
	//---------------------------------------------
	double volSum = 0.0;
	for (int j = 0; j < numTaps; j++)
	{

			tapVolumes[j] = tapScalars(j);
			/* Now we need to scale the value so all of the amplitudes add up to 1:
			 ......

			*/
			volSum += tapVolumes[j];
			
	}
	
	for(int j = 0; j < numTaps; j++)
	{
	        tapVolumes[j] =  tapVolumes[j] / volSum * 1;
	}
	//-------------------------------------------
	
	
    // AUDIO LOOP
    //---------------------------------------------------
	for (int sample = 0; sample < buffer.getNumSamples(); sample++)
	{
		dryLeft = sample1.play(); // buffer.getReadPointer(0)[sample]; //  

		// Fill the Wavetable samples array:
		wv = getWaveSamples(pitchAmpPatterns, pitchFreqPatterns);

		// Delay Line WriteHead and Feedback:
		oldBuffer[counter] = dryLeft + (oldBuffer[counter] * feedbackGain);

		//Reset output:
		outputSignal = 0;  
			

		// Taps loop:
		//---------------------------------------------
		for (int i = 0; i < numTaps; i++)
		{
		    // Tap Times:
			dt[i] = tapTime(i);

			// indexInBuffer: currentCounter + wavetableSample - (delayTime)
			double index = (counter + wv[i]) - ( dt[i]  );
			
			// if index below 0, wrap-around
			if (index < 0)
			{
				index = (1000 * 441) + index;
			}
			index = fmod(index, 1000*441);
			
			ind[i] = index;

			// Interpolate:
			taps[i] = interpolate(ind[i]);

			// Scale the individual tap volume:
			double scaledAmp = tapVolumes[i];

			// multiply the tap by the value:
			taps[i] *= scaledAmp;

			// Sum:
			outputSignal += taps[i];// / numtaps; // delete the ( /numtaps) once you have got volume ratio working

		}
		//---------------------------------------------------------
		
		// do dry/wet mix :
		double out = (outputSignal*dryWetAmount) + (dryLeft * (1 - dryWetAmount));
		
		// Output:
		*outputChannelData0 = out; 
		*outputChannelData1 = out;

		// Increment WriteHead:
		counter++;
		if (counter >= (1000*441))
		{
			counter = 0;
		}

		// Increment thru DAW buffer:
		outputChannelData0++;
		outputChannelData1++;
	}
	//-------------------------------------------------------------

}

//=======================================================
vector<double> Delay_prototype_pluginAudioProcessor::getWaveSamples(int a, int f)
{
	if (pitchAmpPatterns == 0 && f == pitchFreqPatterns)
	{
		for (int i = 0; i < wv.size(); i++)
		{
			wv[i] = ((freqAmpSample.play(wavetableFrequency, whichWave, whichWave + 600) + 1.0f) / 2.0f) * wavetableAmp;
		}
	}
	else if (pitchAmpPatterns == 0 && pitchFreqPatterns != 0)
	{
		// The global freq and amp controls set all the taps:
		for (int i = 0; i < wv.size(); i++)
		{
			wv[i] = ((freqAmpSample.play(pitchFreqArray[pitchFreqPatterns - 1][i], whichWave, whichWave + 600) + 1.0f) / 2.0f) * wavetableAmp;
		}
	}
	else if (pitchAmpPatterns != 0 && pitchFreqPatterns == 0)
	{
		for (int i = 0; i < numTaps; i++)
		{
			wv[i] = ((freqAmpSample.play(wavetableFrequency, whichWave, whichWave + 600) + 1.0f) / 2.0f) * pitchAmpArray[pitchAmpPatterns - 1][i];
		}
	}
	else if (pitchAmpPatterns != 0 && pitchFreqPatterns != 0)
	{
		for (int i = 0; i < numTaps; i++)
		{
			wv[i] = ((freqAmpSample.play(pitchFreqArray[pitchFreqPatterns - 1][i], whichWave, whichWave + 600) + 1.0f) / 2.0f) * pitchAmpArray[pitchAmpPatterns - 1][i];
		}
	}

	return wv;
}

//=======================================================
double Delay_prototype_pluginAudioProcessor::tapScalars(int tapIndex)
{
	// space readpointers along the volume wavetable buffer:, so divide the waveform buffer size by the number of taps. 
			//int indexInVs = (vs.size() / numTaps) * j;
	int indexInVs = readStart + ((singleWavetableLength / numTaps)* tapIndex);
	// Find the amplitude value in vs at that index, map it to the correct range:
	double vol = vs[indexInVs];
	double output= vol;
	return output;
}
//=======================================================
double Delay_prototype_pluginAudioProcessor::interpolate(double ind)
{
	// Interpolation : truncate the index so we have a whole number:
	double interpTap = int(ind);
	// find the remainder:
	double frac = ind - interpTap;
	double next = 0.0;
	// if we dont need to wrap around, then go ahead and read the next sample:
	if (interpTap!= (numSamples - 1))
	{
		next = oldBuffer[interpTap + 1];
	}
	else { next = oldBuffer[0]; }

	double interpolatedValue = oldBuffer[interpTap] + frac * (next - oldBuffer[interpTap]);
	//double outS = interpolatedValue;
	double out = interpolatedValue;// interpolatedValue;// oldBuffer[ind[i]];

	return out;
}
//=======================================================
double Delay_prototype_pluginAudioProcessor::tapTime(int tapIndex)
{
	// first you want to space numTaps along the rhythm wavetable buffer:, so divide the waveform buffer size by the number of taps. 
	int indexInRs = ((singleWavetableLength / numTaps)* tapIndex);
	// Find the real amplitude value in rs:
	double rcAmpVal = rs[indexInRs + readStartRhythm];
	// Re-scale that difference so it matches the audio buffer scale:
	double limit = secondsInOneBeat * 441999.0;
	double output = jmap(rcAmpVal, 0.0, 1.0, 0.0, limit);
	return output;
}
 //=======================================================
AudioProcessorValueTreeState&  Delay_prototype_pluginAudioProcessor::getState()
{
	// returns reference to state
	return *state;
}
//==============================================================================
bool Delay_prototype_pluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Delay_prototype_pluginAudioProcessor::createEditor()
{
    return new Delay_prototype_pluginAudioProcessorEditor (*this);
}

//==============================================================================
void Delay_prototype_pluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Delay_prototype_pluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Delay_prototype_pluginAudioProcessor();
}
