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

private:
	juce::TabbedComponent Tab;

	juce::LookAndFeel_V4 OtherLookAndFeel;

	// All Buttons
	juce::TextButton Freeze{ "Unfrozen" }, Mute{ "Unmuted" };

	struct OscillatorPage : public juce::Component
	{
		OscillatorPage()
		{
			for (int i = 0; i < Sliders.size(); i++)
			{
				addAndMakeVisible(Sliders[i]);
				Sliders[i]->setAccessible(true);	// Accessible Functions are on for all sliders
				Osc1.setTitle("Oscilator One");
				Osc2.setTitle("Oscilator Two");
				Osc3.setTitle("Oscilator Three");
				Osc4.setTitle("Oscilator Four");
				Osc5.setTitle("Oscilator Five");
				Osc6.setTitle("Oscilator Six");


				if (i != 6)
				{
					Sliders[i]->setRange(-70, 6, 1);
					// First Slider Position in row
					if (i != 0)
					{
						Sliders[i]->setBounds(Sliders[i - 1]->getX() + 150, TopMargin, SliderWidth, SliderHeight);
					}

					else
					{
						Sliders[i]->setRange(0,4,0.01);
						Sliders[i]->setBounds(20, TopMargin, SliderWidth, SliderHeight);
					}
					// Relative Positions


					Sliders[i]->setSize(200, 200);
					// Oscilator Slider TextBox and Slider
					Sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);
					Sliders[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);
				}

			}
		}

		juce::Slider Osc1,Osc2,Osc3,Osc4,Osc5,Osc6,Spread;

		std::vector<juce::Slider*> Sliders ={ &Osc1,&Osc2,&Osc3,&Osc4,&Osc5,&Osc6,&Spread };

		int SliderWidth{ 200 }, SliderHeight{ 200 }, LeftMargin{ 24 }, TopMargin{ 24 };

	};
	/*
	 All Slider Objects
	juce::Slider 
		Osc1, 
		Osc2
		, Osc3, Osc4, Osc5, Osc6, Spread;

	// Osc Slider Objects
	std::vector<juce::Slider*> Sliders =
	{	&Osc1,&Osc2,&Osc3,&Osc4,&Osc5,&Osc6,&Spread};

	*/

	// Interface Buttons
	std::vector<juce::TextButton*> Button  =
	{ &Mute, &Freeze };


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VIVI_SynthAudioProcessor& audioProcessor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VIVI_SynthAudioProcessorEditor)
};

