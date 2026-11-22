#ifndef _kernel_h
#define _kernel_h

#include <circle/actled.h>
#include <circle/koptions.h>
#include <circle/devicenameservice.h>
#include <circle/2dgraphics.h>
#include <circle/exceptionhandler.h>
#include <circle/interrupt.h>
#include <circle/timer.h>
#include <circle/sched/scheduler.h>
#include <circle/types.h>
#include <SDCard/emmc.h>
#include <fatfs/ff.h>
#include "realdashGTV6.h"

enum TShutdownMode
{
	ShutdownNone,
	ShutdownHalt,
	ShutdownReboot
};

class CKernel
{
private:
	static const unsigned nShapes = 1;

public:
	CKernel (void);
	~CKernel (void);

	boolean Initialize (void);

	TShutdownMode Run (void);

private:
	// do not change this order
	CActLED				m_ActLED;
	CKernelOptions		m_Options;
	CDeviceNameService	m_DeviceNameService;

	C2DGraphics			m_2DGraphics;
	CImageFromFile	*m_pShape[nShapes];

	CExceptionHandler	m_ExceptionHandler;		// Installs ARM IRQ vector table
	CInterruptSystem	m_Interrupt;
	CTimer				m_Timer;
	CScheduler			m_Scheduler;
	CEMMCDevice			m_EMMC;
	FATFS				m_FileSystem;
};

#endif
