
#include "kernel.h"

CKernel::CKernel (void)
: m_2DGraphics (m_Options.GetWidth (), m_Options.GetHeight (), TRUE),
m_Timer (&m_Interrupt),
m_EMMC (&m_Interrupt, &m_Timer, &m_ActLED)
{
	m_ActLED.Blink (5);
}

CKernel::~CKernel (void)
{
}

boolean CKernel::Initialize (void)
{
	boolean bOK = TRUE;
	if (bOK) bOK = m_2DGraphics.Initialize ();
	if (!m_Interrupt.Initialize ())
	{
		m_2DGraphics.ClearScreen (COLOR2D (0, 255, 0));
		m_2DGraphics.UpdateDisplay ();
		while (1) {}
	}
	if (!m_Timer.Initialize ())
	{
		m_2DGraphics.ClearScreen (COLOR2D (255, 0, 0));
		m_2DGraphics.UpdateDisplay ();
		while (1) {}
	}
	if (bOK)
	{
		if (!m_EMMC.Initialize ())
		{
			// CYAN = m_EMMC.Initialize() failed (hardware/scheduler issue)
			m_2DGraphics.ClearScreen (COLOR2D (0, 255, 255));
			m_2DGraphics.UpdateDisplay ();
			while (1) {}
		}

		FRESULT res = f_mount (&m_FileSystem, "SD:", 1);
		if (res != FR_OK)
		{
			// MAGENTA = m_EMMC worked, but f_mount("SD:") failed
			m_2DGraphics.ClearScreen (COLOR2D (255, 0, 255));
			m_2DGraphics.UpdateDisplay ();
			while (1) {}
		}
	}

	return bOK;
}
TShutdownMode CKernel::Run (void)
{
	CRealDashGTV6Objects Objects = CRealDashGTV6Objects(&m_2DGraphics);

	while (1);


	return ShutdownHalt;
}
