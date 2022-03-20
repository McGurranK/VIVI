/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Effects.h"

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
struct Oscillatorpage;

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


	OscillatorPage* OscPointer = new OscillatorPage();
	EffectsPage* EffectPointer = new EffectsPage();

private:

	// Get Screen Size to set reletive size and position
	juce::Rectangle<int> r = juce::Desktop::getInstance().getDisplays().getMainDisplay().userArea;
	int x = r.getWidth();
	int y = r.getHeight();



	// Tabbed Setup and variables
	juce::TabbedComponent Tab;

	float TabIndent{(float) y / 100 }, TabDepth{ (float) y / 10 };

	// Button One Position X & Y and Size W & H
	float   ButtonTwoY{0}
		,	ButtonOneD{(float)x/10};


	// Custom Look
	juce::LookAndFeel_V4 OtherLookAndFeel;

	// Buttons and Vectors
	juce::TextButton Freeze{ "Unfrozen" }, Mute{ "Unmuted" };

	std::vector<juce::TextButton*> Button  ={ &Mute, &Freeze };

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VIVI_SynthAudioProcessor& audioProcessor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VIVI_SynthAudioProcessorEditor)
};

