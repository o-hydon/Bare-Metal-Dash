
#include "graphicshape.h"

T2DColor textColor  = COLOR2D(255, 255, 255); 

BackgroundShape::BackgroundShape (C2DGraphics *p2DGraphics)
:   m_p2DGraphics (p2DGraphics),
	m_nDisplayWidth (p2DGraphics->GetWidth ()),
	m_nDisplayHeight (p2DGraphics->GetHeight ()),
    m_Image (p2DGraphics)
{
    
    if (m_p2DGraphics == 0)
        return;
    unsigned hFile = m_pFileSystem->FileOpen("BG.RGB")
    for (unsigned int y = 0; y < imgHeight; y++)
    {
        for (unsigned int x = 0; x < imgWidth; x++)
        {
            T2DColor pixelColor = COLOR2D(*pPixel, *(pPixel+1), *(pPixel+2));
            m_PixelBuffer[(y * imgWidth) + x] = pixelColor;
            pPixel +=3;
        }
    }
    m_Image.Set(imgWidth, imgHeight, m_PixelBuffer);
}
BackgroundShape::~BackgroundShape()
{

}
void BackgroundShape::Draw(void)
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
