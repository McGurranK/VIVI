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

struct OscillatorPage: juce::Component, Themes, juce::Slider::Listener
{
public:

	// Oscillator Sliders and Vector Storage
	juce::Slider Osc1, Osc2, Osc3, Osc4, Osc5, Osc6, Spread;
	std::vector<juce::Slider*> Sliders = { &Osc1,&Osc2,&Osc3,&Osc4,&Osc5,&Osc6, &Spread };

	// Constructor method
	OscillatorPage(VIVI_SynthAudioProcessor &p, Themes &T)
	: ProcessorRef(p), Theme(T)
	{	

		// Loop through vector of objects to seteverything up
		for (auto i = 0; i < Sliders.capacity(); i++)
		{	
			// Making components visible
			addAndMakeVisible(OscLabels[i]);
			addAndMakeVisible(Sliders[i]);

			// Keyboard Functionality
			Sliders[i]->setWantsKeyboardFocus(true);
			Sliders[i]->setHasFocusOutline(true);
			Sliders[i]->setName(OscilllatorNames[i]);
			Sliders[i]->addListener(this);

			// Look and text
			Sliders[i]->setTitle(OscilllatorNames[i]);	// Set all names of variables
			Sliders[i]->setLookAndFeel(&OtherLookAndFeel);

			//Label Setup
			OscLabels[i]->setText(OscillatorLabelNames[i], juce::NotificationType::dontSendNotification);
			OscLabels[i]->setLookAndFeel(&OtherLookAndFeel);
			OscLabels[i]->setAccessible(false);

			// Slider Layout
			if (i < 6) {
			Sliders[i]->setSliderStyle(juce::Slider::SliderStyle::Rotary);              // Set Slider style
			Sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 200, 30);    // Text Box Setup
			OscLabels[i]->setFont(juce::Font(72.0f, juce::Font::bold));
			OscLabels[i]->setJustificationType(juce::Justification::centred);
			OscLabels[i]->attachToComponent(Sliders[i],false);
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
				OscLabels[i]->setFont(juce::Font(38.0f, juce::Font::bold));
				OscLabels[i]->setJustificationType(juce::Justification::centredTop);

			}
		}

		// Initalise all slider Linking to APVTS
		mOscAttachment = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts,"OscOneVol",Osc1);

		mOscTwoAttachment = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "OscTwoVol", Osc2);

		mOscThreeAttachment = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "OscThreeVol", Osc3);

		mOscFourAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "OscFourVol", Osc4);

		mOscFiveAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "OscFiveVol", Osc5);

		mOscSixAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "OscSixVol", Osc6);

		SpreadAttachment = std::make_unique
			<juce::AudioProcessorValueTreeState::SliderAttachment>
			(ProcessorRef.apvts, "Spread", Spread);

		
	}

	// Destructor
	~OscillatorPage()
	{
		/*
		Sliders.clear();
		Sliders.shrink_to_fit();
		OscLabels.clear();
		OscLabels.shrink_to_fit();
		*/
	}

	// Positioning Labels for componenets
	void resized()
	{
		for (int i = 0; i < Sliders.size(); i++)
		{	
			int SliderY = Sliders[i]->getY();
			int SliderX = Sliders[i]->getX();
			if (i < 6) 
			{

				OscLabels[i]->setBounds(SliderX + 50, SliderY + 30, 100, 100);
			}
			else
			{	

				OscLabels[i]->setBounds(SliderX , SliderY , 100, 100);
			}
		}

	}

	// Grab foucus and debugging with slider listener
	void sliderValueChanged(juce::Slider* sliderThatMoved) override;

	double NewValue{ 0 };

private:

	// Initalising Slider variables
	int SliderWidth{ 200 }, SliderHeight{ 200 }, LeftMargin{ 20 }, TopMargin{ 20 }
	, SliderDistance{ 250 };

	// APVTS Parameter Linking for Oscillator Page parameters
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscTwoAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscThreeAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscFourAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscFiveAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mOscSixAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>SpreadAttachment;

	// Slider Labels and label text
	juce::Label OscillatorOneLabel, OscillatorTwoLabel,
		OscillatorThreeLabel, OscillatorFourLabel, OscillatorFiveLabel,
		OscillatorSixLabel, SpreadLabel;

	std::vector<juce::Label*> OscLabels = { &OscillatorOneLabel, &OscillatorTwoLabel,
		&OscillatorThreeLabel, &OscillatorFourLabel, &OscillatorFiveLabel,
		&OscillatorSixLabel, &SpreadLabel };

	// Labels for Oscillator
	std::array<std::string, 7> OscillatorLabelNames =
	{ "1","2","3","4","5","6","Spread" };

	// Array with all slider names to step through
	std::array < std::string, 7 > OscilllatorNames =
	{
	  "Oscillator One","Oscillator Two","Oscilator Three","Oscillator Four",
	  "Oscillator Five","Oscillator Six","Spread"
	};
	// Gen Slider Allocations
	std::array<int, 7> GenReferenceNumbers = { 9, 12, 11, 8, 7, 10, 14 };
	
	Themes &Theme;

	// Processor Refernece
	VIVI_SynthAudioProcessor& ProcessorRef;	
};