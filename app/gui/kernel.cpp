
#include "kernel.h"

CKernel::CKernel (void)
: m_2DGraphics (m_Options.GetWidth (), m_Options.GetHeight (), TRUE)
{
	m_ActLED.Blink (5);
}

CKernel::~CKernel (void)
{
}

boolean CKernel::Initialize (void)
{
	return m_2DGraphics.Initialize ();
}

TShutdownMode CKernel::Run (void)
{
	for (unsigned i = 0; i < nShapes; i++)
	{
		m_pShape[i] = new CGraphicShape (&m_2DGraphics);
	}

	while (1)
	{
		m_2DGraphics.ClearScreen(CDisplay::Black);
		
		for(unsigned i=0; i<nShapes; i++)
		{
			m_pShape[i]->Draw();
		}
		
		m_2DGraphics.UpdateDisplay();
	}

	return ShutdownHalt;
}
