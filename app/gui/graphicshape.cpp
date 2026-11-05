
#include "graphicshape.h"

T2DColor textColor  = COLOR2D(255, 255, 255); 

CGraphicShape::CGraphicShape (C2DGraphics *p2DGraphics)
:	m_p2DGraphics (p2DGraphics),
	m_nDisplayWidth (p2DGraphics->GetWidth ()),
	m_nDisplayHeight (p2DGraphics->GetHeight ()),
    m_Image (p2DGraphics)
{
    
    if (m_p2DGraphics == 0)
        return;

    static const T2DColor s_Turquoise = COLOR2D(0x00, 0xFF, 0xFF);
    for (unsigned int y = 0; y < imgHeight; y++)
    {
        for (unsigned int x = 0; x < imgWidth; x++)
        {
            m_PixelBuffer[(y * imgWidth) + x] = s_Turquoise;
        }
    }
    m_Image.Set(imgWidth, imgHeight, m_PixelBuffer);
}
CGraphicShape::~CGraphicShape()
{

}
void CGraphicShape::Draw(void)
{
    if (m_p2DGraphics == 0)
        return;

    // m_PixelBuffer decays to a pointer automatically, same as .data().
    m_p2DGraphics->DrawImage(0, 0, m_nDisplayWidth, m_nDisplayHeight, m_Image.GetPixels());
    // m_p2DGraphics->DrawText(
    //         10,10,
    //         textColor,
    //         "Hello World!",
    //         C2DGraphics::AlignLeft);
    m_p2DGraphics->UpdateDisplay();
}
