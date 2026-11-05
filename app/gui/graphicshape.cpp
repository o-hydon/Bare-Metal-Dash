
#include "graphicshape.h"

T2DColor textColor  = COLOR2D(255, 255, 255); 

CGraphicShape::CGraphicShape (C2DGraphics *p2DGraphics)
:	m_p2DGraphics (p2DGraphics),
	m_nDisplayWidth (p2DGraphics->GetWidth ()),
	m_nDisplayHeight (p2DGraphics->GetHeight ())
{
}	

void CGraphicShape::Draw (void)
{
	m_p2DGraphics->DrawText(100, 100, textColor, "Hello World!", C2DGraphics::AlignCenter);
};
