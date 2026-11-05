
#ifndef _graphicshape_h
#define _graphicshape_h

#include <circle/2dgraphics.h>
#include <circle/bcmframebuffer.h>

enum
{
};

class CGraphicShape
{
public:
	CGraphicShape (C2DGraphics *p2DGraphics);
	~CGraphicShape (void);


	void Draw (void);

private:
	C2DGraphics *m_p2DGraphics;
	unsigned m_nDisplayWidth;
	unsigned m_nDisplayHeight;

};

#endif
