/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Delay_multiple_tapsAudioProcessorEditor::Delay_multiple_tapsAudioProcessorEditor (Delay_multiple_tapsAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	addAndMakeVisible(phasorFreq = new Slider("PhasorFreq"));
	phasorFreq->setSliderStyle(Slider::SliderStyle::Rotary);
	phasorFreq->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	phasorFreq->setColour(Slider::textBoxTextColourId, Colours::black);
	phasorFreq->setLookAndFeel(&otherLookAndFeel);

	phasorFreqValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "PhasorFrequency", *phasorFreq);

	addAndMakeVisible(phasorAmp = new Slider("phasorAmp"));
	phasorAmp->setSliderStyle(Slider::SliderStyle::Rotary);
	phasorAmp->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	phasorAmp->setColour(Slider::textBoxTextColourId, Colours::black);
	phasorAmp->setLookAndFeel(&otherLookAndFeel);

	phasorAmpValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "phasorAmp", *phasorAmp);


	addAndMakeVisible(phasorStart = new Slider("phasorStart"));
	phasorStart->setSliderStyle(Slider::SliderStyle::Rotary);
	phasorStart->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	phasorStart->setColour(Slider::textBoxTextColourId, Colours::black);
	phasorStart->setLookAndFeel(&otherLookAndFeel);

	phasorStartValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "PhasorSetStart", *phasorStart);
	

	addAndMakeVisible(phasorDur = new Slider("PhasorDur"));
	phasorDur->setSliderStyle(Slider::SliderStyle::Rotary);
	phasorDur->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	phasorDur->setColour(Slider::textBoxTextColourId, Colours::black);
	phasorDur->setLookAndFeel(&otherLookAndFeel);

	phasorDurationValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "PhasorDuration", *phasorDur);

	addAndMakeVisible(setSamplesDial = new Slider("Samples"));
	setSamplesDial->setSliderStyle(Slider::SliderStyle::Rotary);
	setSamplesDial->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	setSamplesDial->setColour(Slider::textBoxTextColourId, Colours::black);
	setSamplesDial->setLookAndFeel(&otherLookAndFeel);

	setSampleDuration = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "setSampleDuration", *setSamplesDial);

	addAndMakeVisible(switchSlider = new Slider("SwitchSlider"));
	switchSlider->setSliderStyle(Slider::SliderStyle::Rotary);
	switchSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	switchSlider->setColour(Slider::textBoxTextColourId, Colours::black);
	switchSlider->setLookAndFeel(&otherLookAndFeel);

	setSwitch = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "setSwitch", *switchSlider);

	addAndMakeVisible(phasorFreqLabel = new Label("Phasor Frequency Label"));
	phasorFreqLabel->setText("1", dontSendNotification);
	phasorFreqLabel->setColour(Label::textColourId, Colours::peru);
	phasorFreqLabel->setFont(Font(16.0f, Font::bold));


	addAndMakeVisible(phasorDurationLabel = new Label("Phasor Duration Label"));
	phasorDurationLabel->setText("Tap 2", dontSendNotification);
	phasorDurationLabel->setColour(Label::textColourId, Colours::peru);
	

	addAndMakeVisible(setSamplesLabel = new Label("Sample Buffer Label"));
	setSamplesLabel->setText("Tap 1", dontSendNotification);
	setSamplesLabel->setColour(Label::textColourId, Colours::peru);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(420, 300);
   
}

Delay_multiple_tapsAudioProcessorEditor::~Delay_multiple_tapsAudioProcessorEditor()
{
}

//==============================================================================
void Delay_multiple_tapsAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(Colours::whitesmoke);
}

void Delay_multiple_tapsAudioProcessorEditor::resized()
{
	phasorFreq->setBounds(10, 10, 100, 100);
	phasorFreqLabel->setBounds(25, 115, 70, 30);

	phasorDur->setBounds(110, 10, 100, 100);
	phasorDurationLabel->setBounds(122, 115, 80, 30);

	setSamplesDial->setBounds(210, 10, 100, 100);
	setSamplesLabel->setBounds(225, 115, 70, 30);

	switchSlider->setBounds(310, 10, 100, 100);

	phasorStart->setBounds(10, 130, 100, 100);

	phasorAmp->setBounds(110, 130, 100, 100);

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
