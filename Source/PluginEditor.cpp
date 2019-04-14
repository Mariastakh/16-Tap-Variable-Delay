#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Delay_prototype_pluginAudioProcessorEditor::Delay_prototype_pluginAudioProcessorEditor (Delay_prototype_pluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	addAndMakeVisible(numTapSlider = new Slider("NumTaps"));
	numTapSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	numTapSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	numTapSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	numTapSlider->setLookAndFeel(&otherLookAndFeel);

	numTapSliderValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "NumTaps", *numTapSlider);

	addAndMakeVisible(numTapsLabel = new Label("Number of Taps Label"));
	numTapsLabel->setText("Num Taps", dontSendNotification);
	numTapsLabel->setColour(Label::textColourId, Colours::peru);
	//_____________________________________

	addAndMakeVisible(wavetableFrequencySlider = new Slider("wavetableFrequency"));
	wavetableFrequencySlider->setSliderStyle(Slider::SliderStyle::Rotary);
	wavetableFrequencySlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	wavetableFrequencySlider->setColour(Slider::textBoxTextColourId, Colours::black);
	wavetableFrequencySlider->setLookAndFeel(&otherLookAndFeel);

	wavetableFrequencyValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "wavetableFrequency", *wavetableFrequencySlider);

	addAndMakeVisible(wavetableFrequencyLabel = new Label("wavetable Frequency Label"));
	wavetableFrequencyLabel->setText("W F", dontSendNotification);
	wavetableFrequencyLabel->setColour(Label::textColourId, Colours::peru);
	//____________________________________________-

	addAndMakeVisible(phasorAmpSlider = new Slider("phasorAmp"));
	phasorAmpSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	phasorAmpSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	phasorAmpSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	phasorAmpSlider->setLookAndFeel(&otherLookAndFeelBlue);

	phasorAmpValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "phasorAmp", *phasorAmpSlider);

	addAndMakeVisible(phasorAmpLabel = new Label("Phasor Amplitude Label"));
	phasorAmpLabel->setText("Pitch A", dontSendNotification);
	phasorAmpLabel->setColour(Label::textColourId, Colours::blue);
	//___________________________
	
	addAndMakeVisible(pitchFreqSlider = new Slider("pitchFreq"));
	pitchFreqSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	pitchFreqSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	pitchFreqSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	pitchFreqSlider->setLookAndFeel(&otherLookAndFeelBlue);
	
	pitchFreqValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "pitchFreq", *pitchFreqSlider);


	addAndMakeVisible(pitchFreqLabel = new Label("Pitch Frequency Label"));
	pitchFreqLabel->setText("Pitch F", dontSendNotification);
	pitchFreqLabel->setColour(Label::textColourId, Colours::blue);
	
	//___________________________
	addAndMakeVisible(dryWetSlider = new Slider("dryWet"));
	dryWetSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	dryWetSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	dryWetSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	dryWetSlider->setLookAndFeel(&otherLookAndFeelBlue);

	dryWetValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "dryWet", *dryWetSlider);

	addAndMakeVisible(dryWetLabel = new Label("Dry Wet Label"));
	dryWetLabel->setText("Dry/Wet", dontSendNotification);
	dryWetLabel->setColour(Label::textColourId, Colours::blue);
	//_____________________________
	
	addAndMakeVisible(feedbackGainSlider = new Slider("feedbackGain"));
	feedbackGainSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	feedbackGainSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	feedbackGainSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	feedbackGainSlider->setLookAndFeel(&otherLookAndFeel);

	feedbackGainValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "feedbackGain", *feedbackGainSlider);

	addAndMakeVisible(feedbackGainLabel = new Label("Feedback Gain Label"));
	feedbackGainLabel->setText("Feedback", dontSendNotification);
	feedbackGainLabel->setColour(Label::textColourId, Colours::peru);
	//__________________________________
	
	addAndMakeVisible(drySignalVolumeSlider = new Slider("drySignalVolume"));
	drySignalVolumeSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	drySignalVolumeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	drySignalVolumeSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	drySignalVolumeSlider->setLookAndFeel(&otherLookAndFeel);

	drySignalVolumeValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "drySignalVolume", *drySignalVolumeSlider);
	
	addAndMakeVisible(drySignalVolumeLabel = new Label("Volume Gain Label"));
	drySignalVolumeLabel->setText("Vol Ratio", dontSendNotification);
	drySignalVolumeLabel->setColour(Label::textColourId, Colours::peru);
	//___________________________
	
	addAndMakeVisible(wavetableAmplitudeSlider = new Slider("wavetableAmplitude"));
	wavetableAmplitudeSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	wavetableAmplitudeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	wavetableAmplitudeSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	wavetableAmplitudeSlider->setLookAndFeel(&otherLookAndFeel);
		
	wavetableAmplitudeValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "wavetableAmplitude", *wavetableAmplitudeSlider);
	
	addAndMakeVisible(wavetableAmplitudeLabel = new Label("Wavetable Amplitude Label"));
	wavetableAmplitudeLabel->setText("W A", dontSendNotification);
	wavetableAmplitudeLabel->setColour(Label::textColourId, Colours::peru);
	//____________________________
	
	addAndMakeVisible(waveSelectSlider = new Slider("waveSelect"));
	waveSelectSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	waveSelectSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	waveSelectSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	waveSelectSlider->setLookAndFeel(&otherLookAndFeel);

	waveSelectValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "waveSelect", *waveSelectSlider);

	addAndMakeVisible(waveSelectLabel = new Label("Wavetable Select Label"));
	waveSelectLabel->setText("Wave Select", dontSendNotification);
	waveSelectLabel->setColour(Label::textColourId, Colours::peru);
	//___________________________________
	
	addAndMakeVisible(sampledWaveFrequencySlider = new Slider("sampledWaveFrequency"));
	sampledWaveFrequencySlider->setSliderStyle(Slider::SliderStyle::Rotary);
	sampledWaveFrequencySlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	sampledWaveFrequencySlider->setColour(Slider::textBoxTextColourId, Colours::black);
	sampledWaveFrequencySlider->setLookAndFeel(&otherLookAndFeelBlue);

	sampledWaveFrequencyValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "sampledWaveFrequency", *sampledWaveFrequencySlider);
	
	addAndMakeVisible(sampledWaveFrequencyLabel = new Label("Sampled Wave Frequency Value Label"));
	sampledWaveFrequencyLabel->setText("W 2 F", dontSendNotification);
	sampledWaveFrequencyLabel->setColour(Label::textColourId, Colours::peru);
	//________________________________
	
	addAndMakeVisible(sampledWaveAmplitudeSlider = new Slider("sampledWaveAmplitude"));
	sampledWaveAmplitudeSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	sampledWaveAmplitudeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	sampledWaveAmplitudeSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	sampledWaveAmplitudeSlider->setLookAndFeel(&otherLookAndFeel);

	sampledWaveAmplitudeValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "sampledWaveAmplitude", *sampledWaveAmplitudeSlider);

	addAndMakeVisible(sampledWaveAmplitudeLabel = new Label("Sampled Wave Amplitude Label"));
	sampledWaveAmplitudeLabel->setText("Hop Size", dontSendNotification);
	sampledWaveAmplitudeLabel->setColour(Label::textColourId, Colours::peru);
	//_____________________________
	
	addAndMakeVisible(beatDivisionSlider = new Slider("beatDivision"));
	beatDivisionSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	beatDivisionSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	beatDivisionSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	beatDivisionSlider->setLookAndFeel(&otherLookAndFeel);

	beatDivisionValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "beatDivision", *beatDivisionSlider);

	addAndMakeVisible(beatDivisionLabel = new Label("Beat Division Label"));
	beatDivisionLabel->setText("Rhythm", dontSendNotification);
	beatDivisionLabel->setColour(Label::textColourId, Colours::peru);
	//____________________________
	
	addAndMakeVisible(bpmSlider = new Slider("bpm"));
	bpmSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	bpmSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	bpmSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	bpmSlider->setLookAndFeel(&otherLookAndFeel);

	bpmValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "bpm", *bpmSlider);

	addAndMakeVisible(bpmLabel = new Label("BPM Label"));
	bpmLabel->setText("BPM", dontSendNotification);
	bpmLabel->setColour(Label::textColourId, Colours::peru);
	//

	

	setSize(620, 700);
}

Delay_prototype_pluginAudioProcessorEditor::~Delay_prototype_pluginAudioProcessorEditor()
{
}

//==============================================================================
void Delay_prototype_pluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::whitesmoke);
}

void Delay_prototype_pluginAudioProcessorEditor::resized()
{
	// Page One:

// Number of Taps:
	numTapSlider->setBounds(10, 10, 100, 100);
	numTapsLabel->setBounds(15, 115, 170, 30);
 
	// volume ratio:
	drySignalVolumeSlider->setBounds(110, 10, 100, 100);
	drySignalVolumeLabel->setBounds(122, 115, 80, 30);

	//
	feedbackGainSlider->setBounds(210, 10, 100, 100);
	feedbackGainLabel->setBounds(220, 115, 170, 30);

	// BPM:
	bpmSlider->setBounds(310, 10, 100, 100);
	bpmLabel->setBounds(335, 115, 80, 30);


	// Next row:
	wavetableFrequencySlider->setBounds(10, 140, 100, 100);
	wavetableFrequencyLabel->setBounds(35, 245, 80, 30);

	// Tap Time Slider (rhythm):
	beatDivisionSlider->setBounds(110, 140, 100, 100);
	beatDivisionLabel->setBounds(115, 245, 100, 30);

	wavetableAmplitudeSlider->setBounds(210, 140, 100, 100);
	wavetableAmplitudeLabel->setBounds(230, 245, 110, 30);

	waveSelectSlider->setBounds(310, 140, 100, 100);
	waveSelectLabel->setBounds(310, 245, 100, 30);

	// Page 2:
	// Dry Wet:
	dryWetSlider->setBounds(310, 280, 100, 100);
	dryWetLabel->setBounds(330, 375, 80, 30);

	phasorAmpSlider->setBounds(10, 280, 100, 100);
	phasorAmpLabel->setBounds(20, 375, 100, 30);

	pitchFreqSlider->setBounds(110, 280, 100, 100);
	pitchFreqLabel->setBounds(105, 375, 70, 30);
}
