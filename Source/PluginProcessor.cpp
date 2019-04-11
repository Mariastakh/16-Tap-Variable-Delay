/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

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
	state->createAndAddParameter("phasorAmp", "phasorAmp", "phasorAmp", NormalisableRange<float>(0.0, 16.0f, 1.0f), 0.0, nullptr, nullptr);
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
	// OSCILS FREQ:
	state->createAndAddParameter("tf1", "tf1", "tf1", NormalisableRange<float>(0.0f, 25.0f, 0.01f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("tf2", "tf2", "tf2", NormalisableRange<float>(0.0f, 25.0f, 0.01f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("tf3", "tf3", "tf3", NormalisableRange<float>(0.0f, 25.0f, 0.01f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("tf4", "tf4", "tf4", NormalisableRange<float>(0.0f, 25.0f, 0.01f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("tf5", "tf5", "tf5", NormalisableRange<float>(0.0f, 25.0f, 0.01f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("tf6", "tf6", "tf6", NormalisableRange<float>(0.0f, 25.0f, 0.01f), 0.0, nullptr, nullptr);
	//
	// OSCIL AMP:
	state->createAndAddParameter("ta1", "ta1", "ta1", NormalisableRange<float>(0.0f, 1200.0f, 0.1f), 0.0, nullptr, nullptr);
	state->createAndAddParameter("ta2", "ta2", "ta2", NormalisableRange<float>(0.0f, 1200.0f, 0.1f), 0.0, nullptr, nullptr);
	//

	state->state = ValueTree("NumTaps"); 
	state->state = ValueTree("wavetableFrequency");
	state->state = ValueTree("phasorAmp");
	state->state = ValueTree("dryWet");
	state->state = ValueTree("feedbackGain");
	state->state = ValueTree("drySignalVolume");
	state->state = ValueTree("wavetableAmplitude");
	state->state = ValueTree("waveSelect");
	state->state = ValueTree("sampledWaveFrequency");
	state->state = ValueTree("sampledWaveAmplitude");
	state->state = ValueTree("beatDivision");
	state->state = ValueTree("bpm");

	// OSCILS FREQ:
	state->state = ValueTree("tf1");
	state->state = ValueTree("tf2");
	state->state = ValueTree("tf3");
	state->state = ValueTree("tf4");
	state->state = ValueTree("tf5");
	state->state = ValueTree("tf6");
	//
	// OSCILS AMP:
	state->state = ValueTree("ta1");
	state->state = ValueTree("ta2");


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
	t.resize(6);
	sampleTap.resize(6);
	startPoint.resize(6);
	storedStartPoint.resize(6);
	wv.resize(6);
	tapVolumes.resize(16);
	

	//sample1.load("/Users/pootPoot/Documents/Juce_Projects/Delay_Multiple_Taps/words.wav");
	sample1.load("/Users/pootPoot/Documents/Juce_Projects/Delay_Multiple_Taps/wood.wav");
	sample2.load("/Users/pootPoot/Documents/Juce_Projects/AKWF-FREE-master/AKWF/AKWF_bw_blended/AKWF_blended_0009.wav");
	sample3.load("/Users/pootPoot/Documents/Juce_Projects/AKWF-FREE-master/AKWF/AKWF_bw_blended/AKWF_blended_0009.wav");
	sample4.load("/Users/pootPoot/Documents/Juce_Projects/AKWF-FREE-master/AKWF/AKWF_bw_blended/AKWF_blended_0009.wav");
	sample5.load("/Users/pootPoot/Documents/Juce_Projects/AKWF-FREE-master/AKWF/AKWF_bw_blended/AKWF_blended_0009.wav");
	sample6.load("/Users/pootPoot/Documents/Juce_Projects/AKWF-FREE-master/AKWF/AKWF_bw_blended/AKWF_blended_0009.wav");
	sample7.load("/Users/pootPoot/Documents/Juce_Projects/AKWF-FREE-master/AKWF/AKWF_bw_blended/AKWF_blended_0009.wav");
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
	}

	for (int i = 0; i < 6; i++)
	{
		//t[i].sinewave(0);
		sampleTap[i] = false;
		wv[i] = 0.0;
		
	}
	startPoint[0] = 44100;
	startPoint[1] = 120000;
	startPoint[2] = 435400;
	startPoint[3] = 372113;
	startPoint[4] = 282113;
	startPoint[5] = 100000;
	storedStartPoint[0] = 44100;
	storedStartPoint[1] = 120000;
	storedStartPoint[2] = 435400;
	storedStartPoint[3] = 372113;
	storedStartPoint[4] = 282113;
	storedStartPoint[5] = 100000;
	

	int k = jmap(0.129, -1.0, 1.0, 0.0, 441999.0);
	//Logger::outputDebugString(to_string(k));
	jmap(0.129, -1.0, 1.0, 0.0, 441999.0);

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
	pitchPatterns = *state->getRawParameterValue("phasorAmp");
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
	
	//OSCIL FREQ:
	tf1 = *state->getRawParameterValue("tf1");
	tf2 = *state->getRawParameterValue("tf2"); 
	tf3 = *state->getRawParameterValue("tf3"); 
	tf4 = *state->getRawParameterValue("tf4"); 
	tf5 = *state->getRawParameterValue("tf5");
	tf6 = *state->getRawParameterValue("tf6");
	// OSCILS AMP:
	ta1 = *state->getRawParameterValue("ta1");
	ta2 = *state->getRawParameterValue("ta2");
	ta3, ta4, ta5, ta6 = 0.12;
	//
	// ---------------------

	for (int sample = 0; sample < buffer.getNumSamples(); sample++)
	{

		dryLeft = sample1.play(); // buffer.getReadPointer(0)[sample]; //  

		// wavetable samples:
		if (pitchPatterns == 0)
		{
			// The global freq and amp controls set all the taps:
			for (int wave = 0; wave < wv.size(); wave++)
			{
				wv[wave] = ((freqAmpSample.play(wavetableFrequency, whichWave, whichWave + 600) + 1.0f) / 2.0f) * wavetableAmp;
			}
		}
		else {
			// Set all of the taps to individualised freq and amp:
			wv[0] = ((freqAmpSample.play(tf1, whichWave, whichWave + 600) + 1.0f) / 2.0f) * ta1;
			wv[1] = ((freqAmpSample.play(tf2, whichWave, whichWave + 600) + 1.0f) / 2.0f) * ta2;
			wv[2] = ((freqAmpSample.play(tf3, whichWave, whichWave + 600) + 1.0f) / 2.0f) * wavetableAmp;
			wv[3] = ((freqAmpSample.play(tf4, whichWave, whichWave + 600) + 1.0f) / 2.0f) *wavetableAmp;
			wv[4] = ((freqAmpSample.play(tf5, whichWave, whichWave + 600) + 1.0f) / 2.0f) * wavetableAmp;
			wv[5] = ((freqAmpSample.play(tf6, whichWave, whichWave + 600) + 1.0f) / 2.0f) *wavetableAmp;
		}
		
		
		//outputSignal = oldBuffer[counter];
		oldBuffer[counter] = dryLeft + (oldBuffer[counter] * feedbackGain);
		//oldBuffer[counter] = (dryLeft) + (oldBuffer[counter] * feedbackGain);
		double phasor = (osc1.phasor(0.5) * pitchPatterns);

		outputSignal = 0;
        
		
		counter++;

		if (counter >= (10.0 * 44100))
		{
			counter = 0;
		}

		double prevAmpInRc = 0.0;
		// Convert BPM value to milliseconds
		double beatsToMs = (60000 / bpmValue) * 1.0; // 1.0 represents a quarter note/crotchet
		double secondsInOneBeat = 60.0 / bpmValue;

		for (int i = 0; i < numTaps; i++)
		{
			// first you want to space numTaps along the rhythm wavetable buffer:, so divide the waveform buffer size by the number of taps. 
			int indexInRs = ((singleWavetableLength / numTaps)*i);
			// Find the real amplitude value in rs:
			double rcAmpVal = rs[indexInRs + readStartRhythm];
			// Re-scale that difference so it matches the audio buffer scale:
			double limit = secondsInOneBeat * 441999.0;
			double thing = jmap(rcAmpVal, 0.0, 1.0, 0.0, limit);
			dt[i] = thing;

			// final index is the current counter, plus wavetable sample, minus (tap index - offset). 
			double index = (counter + wv[i]) - ( dt[i]  ); // (d[i] + indexInDelayLine)
			
			// if index below 0, wrap-around
			if (index < 0)
			{
				index = 441000 + index;
			}
			index = fmod(index, 441000);
			
			ind[i] = index;


			// Interpolation : truncate the index so we have a whole number:
			interpTap[i] = int(ind[i]);
			// find the remainder:
			double frac = ind[i] - interpTap[i];
			double next = 0.0;
			// if we dont need to wrap around, then go ahead and read the next sample:
			if (interpTap[i] != (numSamples - 1))
			{
				next = oldBuffer[interpTap[i] + 1];
			} else { next = oldBuffer[0]; }

			double interpolatedValue = oldBuffer[interpTap[i]] + frac * (next - oldBuffer[interpTap[i]]);
			//double outS = interpolatedValue;
			taps[i] = interpolatedValue;// interpolatedValue;// oldBuffer[ind[i]];
			
			// working out the volume ratios:
			for (int j = 0; j < numTaps; j++)
			{
				// space readpointers along the volume wavetable buffer:, so divide the waveform buffer size by the number of taps. 
				//int indexInVs = (vs.size() / numTaps) * j;
				int indexInVs = readStart + ((singleWavetableLength / numTaps)*i);
				// Find the amplitude value in vs at that index, map it to the correct range:
				double vol = vs[indexInVs];
				tapVolumes[j] = vol;
			}
			// Now we need to scale the value so all of the amplitudes add up to 1:
			double scaledAmp = tapVolumes[i];
			// multiply the tap by the value:
			taps[i] *= scaledAmp;
			//

			outputSignal += taps[i];// / numtaps; // delete the ( /numtaps) once you have got volume ratio working

		}

		// do dry/wet mix vetween output signal and 
		double out = (outputSignal*dryWetAmount) + (dryLeft * (1 - dryWetAmount));
		// Output:
		*outputChannelData0 = out;// outputSignal*0.5;// *0.5;   *(1 / (numTaps + 1));
		*outputChannelData1 = out;// *0.5;

		// Increment thru DAW buffer:
		outputChannelData0++;
		outputChannelData1++;
	}

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
