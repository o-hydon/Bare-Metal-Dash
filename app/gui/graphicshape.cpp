
#include "graphicshape.h"

T2DColor textColor  = COLOR2D(255, 255, 255); 
T2DColor* myPixelBuffer = new T2DColor[1920*1080];
const unsigned int imgWidth = 1920;
const unsigned int imgHeight = 1080;
CGraphicShape::CGraphicShape (C2DGraphics *p2DGraphics)
:	m_p2DGraphics (p2DGraphics),
	m_nDisplayWidth (p2DGraphics->GetWidth ()),
	m_nDisplayHeight (p2DGraphics->GetHeight ())
{
}	

void CGraphicShape::Draw (void)
{
	m_p2DGraphics->DrawText(m_nDisplayWidth/2, m_nDisplayHeight/2, textColor, "Hello World!", C2DGraphics::AlignCenter);
	for (unsigned int y = 0; y < imgWidth; y++) {
        for (unsigned int x = 0; x < imgHeight; x++) {
            
            // Define color components (0 to 255)
            u8 red   = x % 256;
            u8 green = y % 256;
            u8 blue  = 128;

            // Use Circle's hardware-aware macro to convert RGB into the right TScreenColor format
            T2DColor finalColor = COLOR2D(red, green, blue);

            // Compute the simple 1D array index for the staging buffer
            // (No hardware screen pitch math is required here!)
            unsigned int bufferIndex = (y * imgWidth) + x;
            
            myPixelBuffer[bufferIndex] = finalColor;
        }
    }

    // 4. Pass your populated buffer to Circle's rendering engine
    // This draws the image at screen coordinates X=50, Y=50
    m_p2DGraphics->DrawImage(m_nDisplayWidth/2, m_nDisplayHeight/2, imgWidth, imgHeight, myPixelBuffer);

    // 5. Clean up your allocated heap memory to avoid leaks
    delete[] myPixelBuffer;
};
