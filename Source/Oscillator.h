/*
  ==============================================================================

	Effects.h
	Created: 16 Mar 2022 9:40:04am
	Author:  Kristian

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Themes.h"

struct OscillatorPage: juce::Component,
	juce::Slider::Listener,Themes
{
public:
	
	// Oscillator Sliders and Vector Storage
	juce::Slider Osc1, Osc2, Osc3, Osc4, Osc5, Osc6, Spread;
	std::vector<juce::Slider*> Sliders = { &Osc1,&Osc2,&Osc3,&Osc4,&Osc5,&Osc6, &Spread};

	// Array with all slider names to step through
	std::array < std::string, 7 > OscilllatorNames = 
	{ "Oscillator One",
	  "Oscillator Two",
	  "Oscilator Three",
	  "Oscillator Four",
	  "Oscillator Five",
	  "Oscillator Six",
	  "Spread"};

	juce::Label Oscil{ "1" }, Oscil1{ "2" }, Oscil2{ "3" }, Oscil3{ "4" };


	// Initalising Slider variables
	int SliderWidth{ 200 }, SliderHeight{ 200 }, LeftMargin{ 20 }, TopMargin{ 20 }
	, SliderDistance{ 250 };

	Themes Theme;

	// Constructor 
	OscillatorPage(VIVI_SynthAudioProcessor &p): ProcessorRef(p)
	{	
		Theme;
		// Loop through vector of objects to seteverything up
		for (auto i = 0; i < Sliders.capacity(); i++)
		{	
			addAndMakeVisible(Oscil);
			Oscil.setFont(juce::Font(16.0f, juce::Font::bold));
			addAndMakeVisible(Sliders[i]);				// Make all Sliders Visible
			Sliders[i]->setValue(0.00);					// Set Default Value
			Sliders[i]->setWantsKeyboardFocus(true);    // Set focus for accessibility
			Sliders[i]->setTitle(OscilllatorNames[i]);	// Set all names of variables
			Sliders[i]->addListener(this);
			Sliders[i]->setLookAndFeel(&OtherLookAndFeel);

			// Slider Layout
			if (i < 6) {
			Sliders[i]->setRange(-100, 6, 1);
			Sliders[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);              // Set Slider style
			Sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);    // Text Box Setup

			// Positional Information
				if (i == 0)
					Sliders[i]->setBounds(20, TopMargin, SliderWidth, SliderHeight);

				// Slider Two and three
				else if (i < 3)
					Sliders[i]->setBounds(Sliders[i - 1]->getX() + SliderDistance, TopMargin, SliderWidth, SliderHeight);

				// Sliders 4-6 Position
				else
					if (i == 3)
						Sliders[i]->setBounds(20, TopMargin + 220, SliderWidth, SliderHeight);
					else
						Sliders[i]->setBounds(Sliders[i - 1]->getX() + SliderDistance, TopMargin + 220, SliderWidth, SliderHeight);

			}

			else
			{
				Sliders[i]->setSliderStyle(juce::Slider::SliderStyle::LinearBar);
				Sliders[i]->setBounds(20, Sliders[3]->getY() + SliderHeight + 50, 700, 75);
				Sliders[i]->setRange(0, 4, 0.01);
				Sliders[i]->setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 30);    // Text Box Setup
			}
		}
	}

	// Destructor
	~OscillatorPage()
	{
	}

	float converter(float oscValue, float minusInfinity);
	void sliderValueChanged(juce::Slider* sliderThatMoved) override;
	bool OscillatorPage::keyPressed(const juce::KeyPress & press) override;
	juce::KeyPress key;

private:
	VIVI_SynthAudioProcessor& ProcessorRef;
};