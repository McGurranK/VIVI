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
#include "SettingsPage.h"

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif

//==============================================================================
/**
*/
class VIVI_SynthAudioProcessorEditor   : public juce::AudioProcessorEditor,
	juce::Slider::Listener
	//juce::Button::Listener 
{
public:
    VIVI_SynthAudioProcessorEditor (VIVI_SynthAudioProcessor&,Themes&);
    ~VIVI_SynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
	
	// override slider functionality
	//void buttonClicked(juce::Button* toggledButton) override;
	void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;
	void KeyboardCommandsForPages(int TabIndex, int SliderRef);
	void KeyboardControl(bool NegOrPlus);
	void ArrowTraverser(bool UpDown);
	void MainComponentSelect(int MainComp, bool PlusNeg);

	// Sliders and vector container
	juce::Slider Volume, Gate;
	std::vector<juce::Slider*> MainControls = { &Volume, &Gate };

	// Slider labels, text array and label vector
	juce::Label VolumeLabel, GateLabel;
	std::vector<juce::Label*> MainControlLabels = { &VolumeLabel,&GateLabel };
	std::array<std::string, 2> MainControlsLabelText = {"Vol","Gate"};

	double NewValue{ 0 }, OscValue{ 0 }, EffectsValue{0}, Effects{ 0 }
	, MainValue{0};
	
	juce::String Name, Focus, NameOsc, FocusOsc,
		// Juce Strings For Effects Page
		NameEffects, FocusEffects, FreezeEffects, FreezeFocusEffects, VolumeMain,
		VolumeFocusMain, GateMain, GateFocusMain;
		
private:

	// Get Screen Size to set reletive size and position
	juce::Rectangle<int> r = juce::Desktop::getInstance().getDisplays().getMainDisplay().userArea;
	int x = r.getWidth();
	int y = r.getHeight();

	// Tabbed Setup and variables
	juce::TabbedComponent Tab;
	float TabIndent{(float) y / 100 }, TabDepth{ (float) y / 10 };

	// Creating Slide objects
	float mainControlHeight{ 520 }, mainControlWidth{ 100 }, mainControlY{TabDepth+TabIndent+50};

	// Button One Position X & Y and Size W & H
	float   ButtonTwoY{0},	ButtonOneD{(float)x/10};


	// Custom Look
	juce::LookAndFeel_V4 OtherLookAndFeel;

	// Buttons and Vectors
	juce::TextButton  Mute{ "Unmuted" };

	// Key Presses
	bool keyPressed(const juce::KeyPress & press) override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	
	VIVI_SynthAudioProcessor& audioProcessor;
	Themes &Theme;

	OscillatorPage* OscReference = new OscillatorPage(audioProcessor, Theme);
	size_t OscSize =  OscReference->Sliders.size();
	

	EffectsPage* EffectsReference = new EffectsPage(audioProcessor);
	SettingsPage* SettingsReference = new SettingsPage();


	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mVolAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>mGateAttachment;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VIVI_SynthAudioProcessorEditor)
};