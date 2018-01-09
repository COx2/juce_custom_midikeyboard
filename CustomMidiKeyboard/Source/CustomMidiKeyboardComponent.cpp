/*
  ==============================================================================

    CustomMidiKeyboardComponent.cpp
    Created: 10 Jan 2018 12:19:40am
    Author:  COx2

  ==============================================================================
*/

#include "CustomMidiKeyboardComponent.h"

//void CustomMidiKeyboardComponent::paint(Graphics & g)
//{
//	g.fillAll(findColour(whiteNoteColourId));
//
//	const Colour lineColour(findColour(keySeparatorLineColourId));
//	const Colour textColour(findColour(textLabelColourId));
//
//	for (int octave = 0; octave < 128; octave += 12)
//	{
//		for (int white = 0; white < 7; ++white)
//		{
//			const int noteNum = octave + whiteNotes[white];
//
//			if (noteNum >= rangeStart && noteNum <= rangeEnd)
//			{
//				Rectangle<int> pos = getRectangleForKey(noteNum);
//
//				drawWhiteNote(noteNum, g, pos.getX(), pos.getY(), pos.getWidth(), pos.getHeight(),
//					state.isNoteOnForChannels(midiInChannelMask, noteNum),
//					mouseOverNotes.contains(noteNum), lineColour, textColour);
//			}
//		}
//	}
//
//	float x1 = 0.0f, y1 = 0.0f, x2 = 0.0f, y2 = 0.0f;
//	const int width = getWidth();
//	const int height = getHeight();
//
//	if (getOrientation() == verticalKeyboardFacingLeft)
//	{
//		x1 = width - 1.0f;
//		x2 = width - 5.0f;
//	}
//	else if (getOrientation() == verticalKeyboardFacingRight)
//		x2 = 5.0f;
//	else
//		y2 = 5.0f;
//
//	int x, w;
//	getKeyPos(getRangeEnd(), x, w);
//	x += w;
//
//	const Colour shadowCol(findColour(shadowColourId));
//
//	if (!shadowCol.isTransparent())
//	{
//		g.setGradientFill(ColourGradient(shadowCol, x1, y1, shadowCol.withAlpha(0.0f), x2, y2, false));
//
//		switch (getOrientation())
//		{
//		case horizontalKeyboard:            g.fillRect(0, 0, x, 5); break;
//		case verticalKeyboardFacingLeft:    g.fillRect(width - 5, 0, 5, x); break;
//		case verticalKeyboardFacingRight:   g.fillRect(0, 0, 5, x); break;
//		default: break;
//		}
//	}
//
//	if (!lineColour.isTransparent())
//	{
//		g.setColour(lineColour);
//
//		switch (getOrientation())
//		{
//		case horizontalKeyboard:            g.fillRect(0, height - 1, x, 1); break;
//		case verticalKeyboardFacingLeft:    g.fillRect(0, 0, 1, x); break;
//		case verticalKeyboardFacingRight:   g.fillRect(width - 1, 0, 1, x); break;
//		default: break;
//		}
//	}
//
//	const Colour blackNoteColour(findColour(blackNoteColourId));
//
//	for (int octave = 0; octave < 128; octave += 12)
//	{
//		for (int black = 0; black < 5; ++black)
//		{
//			const int noteNum = octave + blackNotes[black];
//
//			if (noteNum >= rangeStart && noteNum <= rangeEnd)
//			{
//				Rectangle<int> pos = getRectangleForKey(noteNum);
//
//				drawBlackNote(noteNum, g, pos.getX(), pos.getY(), pos.getWidth(), pos.getHeight(),
//					state.isNoteOnForChannels(midiInChannelMask, noteNum),
//					mouseOverNotes.contains(noteNum), blackNoteColour);
//			}
//		}
//	}
//}

void CustomMidiKeyboardComponent::drawWhiteNote(int midiNoteNumber, Graphics & g, int x, int y, int w, int h, bool isDown, bool isOver, const Colour & lineColour, const Colour & textColour)
  {
	Colour c(Colours::limegreen);
	g.setColour(c);
	g.fillRect(x, y, w, h);

	c = Colours::black;
	g.setColour(c);
	g.fillRect(x + 1, y + 2, w - 2, h - 3);


	c = Colours::transparentWhite;

	if (isDown)  c = findColour(keyDownOverlayColourId);
	if (isOver)  c = c.overlaidWith(findColour(mouseOverKeyOverlayColourId));

	g.setColour(c);
	g.fillRect(x, y, w, h);

	const String text(getWhiteNoteText(midiNoteNumber));

	if (text.isNotEmpty())
	{
		const float fontHeight = jmin(12.0f, getKeyWidth() * 0.9f);

		//g.setColour(textColour);
		g.setColour(Colours::cyan);
		g.setFont(Font(fontHeight).withHorizontalScale(0.8f));

		switch (getOrientation())
		{
		case horizontalKeyboard:            g.drawText(text, x + 1, y, w - 1, h - 2, Justification::centredBottom, false); break;
		case verticalKeyboardFacingLeft:    g.drawText(text, x + 2, y + 2, w - 4, h - 4, Justification::centredLeft, false); break;
		case verticalKeyboardFacingRight:   g.drawText(text, x + 2, y + 2, w - 4, h - 4, Justification::centredRight, false); break;
		default: break;
		}
	}

	if (!lineColour.isTransparent())
	{
		g.setColour(lineColour);

		switch (getOrientation())
		{
		case horizontalKeyboard:            g.fillRect(x, y, 1, h); break;
		case verticalKeyboardFacingLeft:    g.fillRect(x, y, w, 1); break;
		case verticalKeyboardFacingRight:   g.fillRect(x, y + h - 1, w, 1); break;
		default: break;
		}

		if (midiNoteNumber == getRangeEnd())
		{
			switch (getOrientation())
			{
			case horizontalKeyboard:            g.fillRect(x + w, y, 1, h); break;
			case verticalKeyboardFacingLeft:    g.fillRect(x, y + h, w, 1); break;
			case verticalKeyboardFacingRight:   g.fillRect(x, y - 1, w, 1); break;
			default: break;
			}
		}
	}
  }

void CustomMidiKeyboardComponent::drawBlackNote(int midiNoteNumber, Graphics & g, int x, int y, int w, int h, bool isDown, bool isOver, const Colour & noteFillColour)
{

	Colour c(Colours::limegreen);
	g.setColour(c);
	g.fillRect(x, y, w, h);

	c = Colours::black;
	g.setColour(c);
	g.fillRect(x + 1, y + 2, w - 2, h - 3);

	c = Colours::transparentWhite; //noteFillColour;

	if (isDown)  c = c.overlaidWith(findColour(keyDownOverlayColourId));
	if (isOver)  c = c.overlaidWith(findColour(mouseOverKeyOverlayColourId));

	g.setColour(c);
	g.fillRect(x, y, w, h);


	if (isDown)
	{
		g.setColour(noteFillColour);
		g.drawRect(x, y, w, h);
	}
	else
	{
		//g.setColour(c.brighter());
		//const int xIndent = jmax(1, jmin(w, h) / 8);

		//switch (getOrientation())
		//{
		//case horizontalKeyboard:            g.fillRect(x + xIndent, y, w - xIndent * 2, 7 * h / 8); break;
		//case verticalKeyboardFacingLeft:    g.fillRect(x + w / 8, y + xIndent, w - w / 8, h - xIndent * 2); break;
		//case verticalKeyboardFacingRight:   g.fillRect(x, y + xIndent, 7 * w / 8, h - xIndent * 2); break;
		//default: break;
		//}
	}
}
