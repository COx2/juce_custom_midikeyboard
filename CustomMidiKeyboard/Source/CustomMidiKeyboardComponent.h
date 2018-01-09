/*
  ==============================================================================

    CustomMidiKeyboardComponent.h
    Created: 10 Jan 2018 12:19:40am
    Author:  COx2

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class CustomMidiKeyboardComponent : public MidiKeyboardComponent
{
public:
	CustomMidiKeyboardComponent(MidiKeyboardState& state, Orientation orientation) : MidiKeyboardComponent(state, orientation) 
	{
		setKeyWidth(42);
	};

	//void paint(Graphics& g) override;

protected:

	virtual void drawWhiteNote(int midiNoteNumber,
		Graphics& g,
		int x, int y, int w, int h,
		bool isDown, bool isOver,
		const Colour& lineColour,
		const Colour& textColour) override;


	virtual void drawBlackNote(int midiNoteNumber,
		Graphics& g,
		int x, int y, int w, int h,
		bool isDown, bool isOver,
		const Colour& noteFillColour) override;
};