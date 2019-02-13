/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
// Custom Juce Look and Feel Method
class OtherLookAndFeel : public LookAndFeel_V4
{
public:
	OtherLookAndFeel()
	{
		setColour(Slider::thumbColourId, Colours::black);
	}


	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		auto radius = jmin(width / 2, height / 2) - 4.0f;
		auto centreX = x + width * 0.5f;
		auto centreY = y + height * 0.5f;
		auto rx = centreX - radius;
		auto ry = centreY - radius;
		auto rw = radius * 2.0f;
		auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

		// fill
		g.setColour(Colours::orange);
		g.fillEllipse(rx, ry, rw, rw);
		// outline
		g.setColour(Colours::orange);
		g.drawEllipse(rx, ry, rw, rw, 1.0f);

		Path p;
		auto pointerLength = radius * 0.33f;
		auto pointerThickness = 2.0f;
		p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
		p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

		// pointer
		g.setColour(Colours::black);
		g.fillPath(p);
	}

private:
	//OtherLookAndFeel otherLookAndFeel; // [2]
	Slider dial1;
	Slider dial2;
	TextButton button1;
	TextButton button2;
};

class Delay_multiple_tapsAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Delay_multiple_tapsAudioProcessorEditor (Delay_multiple_tapsAudioProcessor&);
    ~Delay_multiple_tapsAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	//// Sliders:
	ScopedPointer<Slider> phasorFreq;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> phasorFreqValue;

	ScopedPointer<Slider> phasorStart;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> phasorStartValue;

	ScopedPointer<Slider> phasorAmp;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> phasorAmpValue;

	ScopedPointer<Slider> phasorDur;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> phasorDurationValue;

	ScopedPointer<Slider> setSamplesDial;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> setSampleDuration;

	ScopedPointer<Slider> switchSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> setSwitch;

	ScopedPointer<Label> phasorFreqLabel;
	ScopedPointer<Label> phasorDurationLabel;
	ScopedPointer<Label> setSamplesLabel;

	OtherLookAndFeel otherLookAndFeel;
    Delay_multiple_tapsAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delay_multiple_tapsAudioProcessorEditor)
};
