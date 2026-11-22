//
// chargenerator.cpp
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
#include <circle/chargenerator.h>

CCharGenerator::CCharGenerator (const TFont &rFont, TFontFlags Flags)
:	m_rFont (rFont),
	m_nWidthMult (Flags & FontFlagsDoubleWidth ? 2 : 1),
	m_nHeightMult (Flags & FontFlagsDoubleHeight ? 2 : 1),
	m_nCharWidth (rFont.width * m_nWidthMult),
	m_nCharStride (((rFont.width + 7) / 8)),
	m_nCharHeight ((rFont.height + rFont.extra_height) * m_nHeightMult),
	m_nUnderline (rFont.height * m_nHeightMult),
	m_nWordsPerLine (m_nCharStride < 4 ? 1 : (m_nCharStride + 3) / 4),
	m_nWordLength (m_nCharStride < 4 ? m_nCharStride*8 : 32)
{
}

CCharGenerator::TPixelWord CCharGenerator::GetPixelWord (char chAscii, unsigned nWordPos) const
{
	unsigned nAscii = (u8) chAscii;
	if (   nAscii < m_rFont.first_char
	    || nAscii > m_rFont.last_char
	    || nWordPos >= m_nWordsPerLine *  m_nCharHeight)
	{
		return FALSE;
	}

	if (m_nHeightMult == 2)
	{
		nWordPos >>= 1;
	}

	switch (m_nCharStride)
	{
	case 1: {
		const u8 *pFontData = static_cast<const u8 *> (m_rFont.data);
		return pFontData[(nAscii - m_rFont.first_char) * m_rFont.height * m_nWordsPerLine + nWordPos];
		}

	case 2: {
		const u16 *pFontData = static_cast<const u16 *> (m_rFont.data);
		return pFontData[(nAscii - m_rFont.first_char) * m_rFont.height * m_nWordsPerLine + nWordPos];
		}

	default: {
		const u32 *pFontData = static_cast<const u32 *> (m_rFont.data);
		return pFontData[(nAscii - m_rFont.first_char) * m_rFont.height * m_nWordsPerLine + nWordPos];
		}
	}

	return 0;
}
