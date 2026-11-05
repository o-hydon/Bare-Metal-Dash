
#ifndef _kernel_h
#define _kernel_h

#include <circle/actled.h>
#include <circle/koptions.h>
#include <circle/2dgraphics.h>
#include <circle/types.h>
#include "graphicshape.h"


enum TShutdownMode
{
	ShutdownNone,
	ShutdownHalt,
	ShutdownReboot
};

class CKernel
{
private:
	static const unsigned nShapes = 32;

public:
	CKernel (void);
	~CKernel (void);

	boolean Initialize (void);

	TShutdownMode Run (void);

private:
	// do not change this order
	CActLED			m_ActLED;
	CKernelOptions		m_Options;

	C2DGraphics		m_2DGraphics;
	CGraphicShape		*m_pShape[nShapes];
};

#endif
