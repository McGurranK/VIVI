/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif

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
	
	// Tabbed Interface
	juce::TabbedComponent Tab;

	// Custom Look
	juce::LookAndFeel_V4 OtherLookAndFeel;

	struct OscillatorPage : juce::Component
	{
		// Oscillator Sliders and Vector Storage

		juce::Slider Osc1, Osc2, Osc3, Osc4, Osc5, Osc6;
		std::vector<juce::Slider*> Sliders = { &Osc1,&Osc2,&Osc3,&Osc4,&Osc5,&Osc6 };

		int SliderWidth{ 300 }, SliderHeight{ 300 }, LeftMargin{ 24 }, TopMargin{ 24 }
		, SliderDistance{500};

		OscillatorPage()
		{
			for (auto i = 0; i < Sliders.size(); i++)
			{
				addAndMakeVisible(Sliders[i]);		// Make all Sliders Visible
				Sliders[i]->setValue(0.00);			// Set Default Value
				Sliders[i]->setAccessible(true);	// Accessible Functions are on for all sliders

				// Oscilator Slider TextBox and Slider
				Sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);
				Sliders[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);


				if (i == 0)
				{

					Sliders[i]->setBounds(20, TopMargin, SliderWidth, SliderHeight);

				}
				else if (i < 3)
				{
					Sliders[i]->setBounds(Sliders[i - 1]->getX() + SliderDistance, TopMargin, SliderWidth, SliderHeight);

				}

				else
				{
					if (i == 3)
					{
						Sliders[i]->setBounds(20, TopMargin+ 300, SliderWidth, SliderHeight);
					}
					else
					{
						Sliders[i]->setBounds(Sliders[i - 1]->getX() + SliderDistance, TopMargin + 300, SliderWidth, SliderHeight);
					}

				}

			}

		}

	};

	struct EffectsPage : juce::Component
	{
		// Oscillator Sliders and Vector Storage

	// Effects Page
		juce::Slider Redux, Bitcrush, DelayLFO, AM, FilterCut, FilterQ;	   // Declare Sliders
		std::vector<juce::Slider*> Effects =							   // Create Slider Vector
		{ &Redux,&Bitcrush,&DelayLFO, &AM, &FilterCut, &FilterQ };

		int SliderWidth{ 300 }, SliderHeight{ 300 }, LeftMargin{ 24 }, TopMargin{ 24 }
		, SliderDistance{ 500 };

		EffectsPage()
		{
			for (auto i = 0; i < Effects.size(); i++)
			{
				addAndMakeVisible(Effects[i]);		// Make all Sliders Visible
				Effects[i]->setValue(0.00);			// Set Default Value
				Effects[i]->setAccessible(true);	// Accessible Functions are on for all sliders

				// Oscilator Slider TextBox and Slider
				Effects[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);
				Effects[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);


				if (i == 0)
				{

					Effects[i]->setBounds(20, TopMargin, SliderWidth, SliderHeight);

				}
				else if (i < 3)
				{
					Effects[i]->setBounds(Effects[i - 1]->getX() + SliderDistance, TopMargin, SliderWidth, SliderHeight);

				}

				else
				{
					if (i == 3)
					{
						Effects[i]->setBounds(20, TopMargin + 300, SliderWidth, SliderHeight);
					}
					else
					{
						Effects[i]->setBounds(Effects[i - 1]->getX() + SliderDistance, TopMargin + 300, SliderWidth, SliderHeight);
					}

				}

			}

		}

	};

	// Effects Page
	juce::Slider Redux, Bitcrush, DelayLFO, AM, FilterCut, FilterQ;	   // Declare Sliders
	std::vector<juce::Slider*> Effects =							   // Create Slider Vector
	{ &Redux,&Bitcrush,&DelayLFO, &AM, &FilterCut, &FilterQ };


	// Buttons and Vectors
	
	juce::TextButton Freeze{ "Unfrozen" }, Mute{ "Unmuted" };

	std::vector<juce::TextButton*> Button  ={ &Mute, &Freeze };

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VIVI_SynthAudioProcessor& audioProcessor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VIVI_SynthAudioProcessorEditor)
};

