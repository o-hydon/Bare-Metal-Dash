//
// chargenerator.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2025  R. Stange <rsta2@gmx.net>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _circle_chargenerator_h
#define _circle_chargenerator_h

#include <circle/font.h>
#include <circle/macros.h>
#include <circle/types.h>

class CCharGenerator	/// Gives pixel information for console font
{
public:
	enum TFontFlags : u8
	{
		FontFlagsNone		= 0,
		FontFlagsDoubleWidth	= BIT (0),
		FontFlagsDoubleHeight	= BIT (1),
		FontFlagsDoubleBoth	= FontFlagsDoubleWidth | FontFlagsDoubleHeight
	};

	typedef u32 TPixelWord;

public:
	/// \param rFont Font to be used
	/// \param Flags Font flags (can build with MakeFlags)
	CCharGenerator (const TFont &rFont = DEFAULT_FONT, TFontFlags Flags = FontFlagsNone);

	static TFontFlags MakeFlags (boolean bDoubleWidth, boolean bDoubleHeight)
	{
		return (TFontFlags) (  (bDoubleWidth ? FontFlagsDoubleWidth : 0)
				     | (bDoubleHeight ? FontFlagsDoubleHeight : 0));
	}

	/// \return Horizontal number of pixel per character
	unsigned GetCharWidth (void) const	{ return m_nCharWidth; }
	/// \return Vertical number of pixel per character (including underline space)
	unsigned GetCharHeight (void) const	{ return m_nCharHeight; }
	/// \return Vertical pixel start position of underline space
	unsigned GetUnderline (void) const	{ return m_nUnderline; }
	/// \return Horizontal number of pixel per word
	unsigned GetWordLength (void) const	{ return m_nWordLength; }
		 
	unsigned GetWordsPerLine (void) const { return m_nWordsPerLine; }
	/// \param chAscii Character code (normally Latin1)
	/// \param nWordPos Word index (0-based)
	/// \return Horizontal pixel information for the line
	TPixelWord GetPixelWord (char chAscii, unsigned nWordPos) const;

	/// \param nPosX Horizontal pixel position inside the line (Left is 0)
	/// \param Word Horizontal pixel information for the line
	/// \return Is pixel is set?
	boolean GetPixel (unsigned nPosX, TPixelWord Word) const
	{
		if (m_nWidthMult == 2)
		{
			nPosX >>= 1;
		}

		return !!(Word & (1 << (m_nWordLength-1 - nPosX)));
	}

	/// \param chAscii Character code (normally Latin1)
	/// \param nPosX Horizontal pixel position inside the line (Left is 0)
	/// \param nPosY Number of pixel line inside the character (0-based)
	/// \return Is pixel is set?
	boolean GetPixel (char chAscii, unsigned nPosX, unsigned nPosY) const
	{
		return GetPixel (nPosX, GetPixelWord (chAscii, nPosY));
	}

private:
	const TFont &m_rFont;
	unsigned m_nWidthMult;
	unsigned m_nHeightMult;

	unsigned m_nCharWidth;
	unsigned m_nCharStride;
	unsigned m_nCharHeight;
	unsigned m_nUnderline;
	unsigned m_nWordsPerLine;
	unsigned m_nWordLength;
};

#endif
