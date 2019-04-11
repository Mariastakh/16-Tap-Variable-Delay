/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

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
	phasorAmpSlider->setLookAndFeel(&otherLookAndFeel);

	phasorAmpValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "phasorAmp", *phasorAmpSlider);

	addAndMakeVisible(phasorAmpLabel = new Label("Phasor Amplitude Label"));
	phasorAmpLabel->setText("Pitch Shift", dontSendNotification);
	phasorAmpLabel->setColour(Label::textColourId, Colours::peru);
	//___________________________
	
	addAndMakeVisible(dryWetSlider = new Slider("dryWet"));
	dryWetSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	dryWetSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	dryWetSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	dryWetSlider->setLookAndFeel(&otherLookAndFeel);

	dryWetValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "dryWet", *dryWetSlider);

	addAndMakeVisible(dryWetLabel = new Label("Dry Wet Label"));
	dryWetLabel->setText("Dry/Wet", dontSendNotification);
	dryWetLabel->setColour(Label::textColourId, Colours::peru);
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
	//____________________________
	// OSCILS:
	addAndMakeVisible(tf1Slider = new Slider("tf1"));
	tf1Slider->setSliderStyle(Slider::SliderStyle::Rotary);
	tf1Slider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	tf1Slider->setColour(Slider::textBoxTextColourId, Colours::black);
	tf1Slider->setLookAndFeel(&otherLookAndFeelBlue);

	tf1Value = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "tf1", *tf1Slider);

	addAndMakeVisible(tf1Label = new Label("tf1 Label"));
	tf1Label->setText("TF 1", dontSendNotification);
	tf1Label->setColour(Label::textColourId, Colours::peru);
	//____________________________
	
	addAndMakeVisible(tf2Slider = new Slider("tf2"));
	tf2Slider->setSliderStyle(Slider::SliderStyle::Rotary);
	tf2Slider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	tf2Slider->setColour(Slider::textBoxTextColourId, Colours::black);
	tf2Slider->setLookAndFeel(&otherLookAndFeelBlue);

	tf2Value = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "tf2", *tf2Slider);

	addAndMakeVisible(tf2Label = new Label("tf2 Label"));
	tf2Label->setText("TF 2", dontSendNotification);
	tf2Label->setColour(Label::textColourId, Colours::peru);
	//____________________________
	
	addAndMakeVisible(tf3Slider = new Slider("tf3"));
	tf3Slider->setSliderStyle(Slider::SliderStyle::Rotary);
	tf3Slider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	tf3Slider->setColour(Slider::textBoxTextColourId, Colours::black);
	tf3Slider->setLookAndFeel(&otherLookAndFeelBlue);

	tf3Value = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "tf3", *tf3Slider);

	addAndMakeVisible(tf3Label = new Label("tf3 Label"));
	tf3Label->setText("TF 3", dontSendNotification);
	tf3Label->setColour(Label::textColourId, Colours::peru);
	//____________________________
	
	addAndMakeVisible(tf4Slider = new Slider("tf4"));
	tf4Slider->setSliderStyle(Slider::SliderStyle::Rotary);
	tf4Slider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	tf4Slider->setColour(Slider::textBoxTextColourId, Colours::black);
	tf4Slider->setLookAndFeel(&otherLookAndFeelBlue);

	tf4Value = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "tf4", *tf4Slider);

	addAndMakeVisible(tf4Label = new Label("tf4 Label"));
	tf4Label->setText("TF 4", dontSendNotification);
	tf4Label->setColour(Label::textColourId, Colours::peru);
	//____________________________
	
	addAndMakeVisible(tf5Slider = new Slider("tf5"));
	tf5Slider->setSliderStyle(Slider::SliderStyle::Rotary);
	tf5Slider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	tf5Slider->setColour(Slider::textBoxTextColourId, Colours::black);
	tf5Slider->setLookAndFeel(&otherLookAndFeelBlue);

	tf5Value = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "tf5", *tf5Slider);

	addAndMakeVisible(tf5Label = new Label("tf5 Label"));
	tf5Label->setText("TF 5", dontSendNotification);
	tf5Label->setColour(Label::textColourId, Colours::peru);
	//____________________________
	
	addAndMakeVisible(tf6Slider = new Slider("tf6"));
	tf6Slider->setSliderStyle(Slider::SliderStyle::Rotary);
	tf6Slider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	tf6Slider->setColour(Slider::textBoxTextColourId, Colours::black);
	tf6Slider->setLookAndFeel(&otherLookAndFeelBlue);

	tf6Value = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "tf6", *tf6Slider);

	addAndMakeVisible(tf6Label = new Label("tf6 Label"));
	tf6Label->setText("TF 6", dontSendNotification);
	tf6Label->setColour(Label::textColourId, Colours::peru);
	//____________________________

	addAndMakeVisible(ta1Slider = new Slider("ta1"));
	ta1Slider->setSliderStyle(Slider::SliderStyle::Rotary);
	ta1Slider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	ta1Slider->setColour(Slider::textBoxTextColourId, Colours::black);
	ta1Slider->setLookAndFeel(&otherLookAndFeelBlue);

	ta1Value = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "ta1", *ta1Slider);

	addAndMakeVisible(ta1Label = new Label("ta1 Label"));
	ta1Label->setText("TA 1", dontSendNotification);
	ta1Label->setColour(Label::textColourId, Colours::peru);
	//____________________________
	
	addAndMakeVisible(ta2Slider = new Slider("ta2"));
	ta2Slider->setSliderStyle(Slider::SliderStyle::Rotary);
	ta2Slider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	ta2Slider->setColour(Slider::textBoxTextColourId, Colours::black);
	ta2Slider->setLookAndFeel(&otherLookAndFeelBlue);

	ta2Value = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "ta2", *ta2Slider);

	addAndMakeVisible(ta2Label = new Label("ta2 Label"));
	ta2Label->setText("TA 2", dontSendNotification);
	ta2Label->setColour(Label::textColourId, Colours::peru);
	//____________________________
	

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

	phasorAmpSlider->setBounds(110, 140, 100, 100);
	phasorAmpLabel->setBounds(115, 245, 100, 30);

	wavetableAmplitudeSlider->setBounds(210, 140, 100, 100);
	wavetableAmplitudeLabel->setBounds(230, 245, 110, 30);

	waveSelectSlider->setBounds(310, 140, 100, 100);
	waveSelectLabel->setBounds(310, 245, 100, 30);

	// Page 2:
	// Dry Wet:
	dryWetSlider->setBounds(310, 280, 100, 100);
	dryWetLabel->setBounds(330, 375, 80, 30);

	// Pitch Stepper:
	beatDivisionSlider->setBounds(10, 280, 100, 100);
	beatDivisionLabel->setBounds(20, 375, 100, 30);

	// OSCILS FREQUENCY:
	tf1Slider->setBounds(10, 400, 100, 100);
	tf1Label->setBounds(20, 495, 70, 30);

	tf2Slider->setBounds(110, 400, 100, 100);
	tf2Label->setBounds(120, 495, 70, 30);

	tf3Slider->setBounds(210, 400, 100, 100);
	tf3Label->setBounds(220, 495, 70, 30);

	tf4Slider->setBounds(10, 520, 100, 100);
	tf4Label->setBounds(20, 615, 70, 30);

	tf5Slider->setBounds(110, 520, 100, 100);
	tf5Label->setBounds(120, 615, 70, 30);

	tf6Slider->setBounds(210, 520, 100, 100);
	tf6Label->setBounds(220, 615, 70, 30);
	
	// OSCIL AMPLITUDE:
	ta1Slider->setBounds(320, 400, 100, 100);
	ta1Label->setBounds(340, 495, 70, 30);

	ta2Slider->setBounds(320, 520, 100, 100);
	ta2Label->setBounds(340, 615, 70, 30);


}
