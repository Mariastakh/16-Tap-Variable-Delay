#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================

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

// bpm sliders:
class OtherLookAndFeelBlue : public LookAndFeel_V4
{
public:
	OtherLookAndFeelBlue()
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
		g.setColour(Colours::cornflowerblue);
		g.fillEllipse(rx, ry, rw, rw);
		// outline
		g.setColour(Colours::blue);
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

//----------------
class Delay_prototype_pluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Delay_prototype_pluginAudioProcessorEditor (Delay_prototype_pluginAudioProcessor&);
    ~Delay_prototype_pluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
	//// Sliders:
	ScopedPointer<Slider> numTapSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> numTapSliderValue;

	ScopedPointer<Slider> wavetableFrequencySlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> wavetableFrequencyValue;

	ScopedPointer<Slider> phasorAmpSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> phasorAmpValue;

	ScopedPointer<Slider> dryWetSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dryWetValue;

	ScopedPointer<Slider> feedbackGainSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> feedbackGainValue;

	ScopedPointer<Slider> drySignalVolumeSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> drySignalVolumeValue;

	ScopedPointer<Slider> wavetableAmplitudeSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> wavetableAmplitudeValue;

	ScopedPointer<Slider> waveSelectSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> waveSelectValue;

	ScopedPointer<Slider> sampledWaveFrequencySlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sampledWaveFrequencyValue;

	ScopedPointer<Slider> sampledWaveAmplitudeSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sampledWaveAmplitudeValue;

	ScopedPointer<Slider> beatDivisionSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> beatDivisionValue;

	ScopedPointer<Slider> bpmSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> bpmValue;
	
	ScopedPointer<Slider> pitchFreqSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pitchFreqValue;

	//
	ScopedPointer<Label> numTapsLabel;
	ScopedPointer<Label> wavetableFrequencyLabel;
	ScopedPointer<Label> phasorAmpLabel;
	ScopedPointer<Label> dryWetLabel;
	ScopedPointer<Label> feedbackGainLabel;
	ScopedPointer<Label> drySignalVolumeLabel;
	ScopedPointer<Label> wavetableAmplitudeLabel;
	ScopedPointer<Label> waveSelectLabel;
	ScopedPointer<Label> sampledWaveFrequencyLabel;
	ScopedPointer<Label> sampledWaveAmplitudeLabel;
	ScopedPointer<Label> beatDivisionLabel;
	ScopedPointer<Label> bpmLabel;
	ScopedPointer<Label> pitchFreqLabel;

	OtherLookAndFeel otherLookAndFeel;
	OtherLookAndFeelBlue otherLookAndFeelBlue;

    Delay_prototype_pluginAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delay_prototype_pluginAudioProcessorEditor)
};
