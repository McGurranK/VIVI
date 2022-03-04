/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VIVI_SynthAudioProcessorEditor  : public juce::AudioProcessorEditor 
{
public:
    VIVI_SynthAudioProcessorEditor (VIVI_SynthAudioProcessor&);
    ~VIVI_SynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
	void Themes(int SelectedTheme);


	int SliderWidth{ 200 }, SliderHeight{ 200 }, LeftMargin{ 24 }, TopMargin{ 24 };



private:
	juce::TabbedComponent Tab;

	juce::LookAndFeel_V4 OtherLookAndFeel;

	// All Buttons
	juce::TextButton Freeze{ "Unfrozen" }, Mute{ "Unmuted" };

	// All Slider Objects
	juce::Slider 
		Osc1, 
		Osc2
		, Osc3, Osc4, Osc5, Osc6, Spread;

	// Osc Slider Objects
	std::vector<juce::Slider*> Sliders =
	{	&Osc1,&Osc2,&Osc3,&Osc4,&Osc5,&Osc6,&Spread};

	// Interface Buttons
	std::vector<juce::TextButton*> Button  =
	{ &Mute, &Freeze };

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VIVI_SynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VIVI_SynthAudioProcessorEditor)
};
