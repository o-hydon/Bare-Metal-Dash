#include "graphicshape.h"
#include <circle/string.h>
#include <circle/util.h>

#define BYTES_PER_PIXEL 3   // 3 bytes per pixel in BG.rgb (RGB888)

T2DColor textColor = COLOR2D(255, 255, 255);

static FRESULT g_OpenResult   = FR_OK;
static FRESULT g_ReadResult   = FR_OK;
static UINT    g_nFileSize    = 0;
static UINT    g_nBytesWanted = 0;
static UINT    g_nBytesRead   = 0;

BackgroundShape::BackgroundShape(C2DGraphics *p2DGraphics)
:   m_p2DGraphics(p2DGraphics),
    m_nDisplayWidth(p2DGraphics->GetWidth()),
    m_nDisplayHeight(p2DGraphics->GetHeight()),
    m_Image(p2DGraphics),
    m_pPixelBuffer(0),
    m_bImageLoaded(FALSE)
{
    UINT nPixels = imgHeight * imgWidth;
    UINT nRowBytes = imgWidth * BYTES_PER_PIXEL;
    g_nBytesWanted = nPixels * BYTES_PER_PIXEL;
    g_nBytesRead = 0;

    FIL File;
    g_OpenResult = f_open(&File, "SD:/BG.rgb", FA_READ | FA_OPEN_EXISTING);
    if (g_OpenResult == FR_OK)
    {
        g_nFileSize = (UINT)f_size(&File);

        // Allocate the final screen buffer and only a 1-row temporary read buffer
        m_pPixelBuffer = new T2DColor[nPixels];
        u8 *pRow = new u8[nRowBytes];

        if (pRow != 0 && m_pPixelBuffer != 0)
        {
            for (UINT y = 0; y < imgHeight; y++)
            {
                UINT nRead = 0;
                g_ReadResult = f_read(&File, pRow, nRowBytes, &nRead);
                if (g_ReadResult != FR_OK || nRead != nRowBytes)
                {
                    break;
                }

                UINT rowOffset = y * imgWidth;
                for (UINT x = 0; x < imgWidth; x++)
                {
                    u8 r = pRow[x * 3 + 0];
                    u8 g = pRow[x * 3 + 1];
                    u8 b = pRow[x * 3 + 2];
                    m_pPixelBuffer[rowOffset + x] = COLOR2D(r, g, b);
                }

                g_nBytesRead += nRead;
            }

            if (g_nBytesRead == g_nBytesWanted)
            {
                m_bImageLoaded = TRUE;
            }
        }

        delete[] pRow;
        f_close(&File);
    }
}

void BackgroundShape::Draw(void)
{

        // Blit the full pixel buffer to the screen using C2DGraphics
        m_p2DGraphics->DrawImage(0, 0, imgWidth, imgHeight, m_pPixelBuffer);


        CString DebugLine1;
        DebugLine1.Format("Display: %u x %u | BPP: %u | Buffer: %s",
                          imgWidth, imgHeight, BYTES_PER_PIXEL,
                          m_pPixelBuffer != 0 ? "OK" : "NULL");

        CString DebugLine2;
        DebugLine2.Format("f_open: %d | f_read: %d | FileSize: %u | Wanted: %u | Read: %u",
                          (int)g_OpenResult, (int)g_ReadResult,
                          g_nFileSize, g_nBytesWanted, g_nBytesRead);

        T2DColor testColor = COLOR2D(0xab, 0xcd, 0xef);
        CString DebugLine3;
        DebugLine3.Format("sizeof(T2DColor): %u | COLOR2D(ab,cd,ef): 0x%08X",
                          (unsigned)sizeof(T2DColor), (unsigned)testColor);

        m_p2DGraphics->DrawRect(300, 10, 950, 100, COLOR2D(0, 0, 0));
        m_p2DGraphics->DrawText(300, 20, textColor, (const char *)DebugLine1);
        m_p2DGraphics->DrawText(300, 45, textColor, (const char *)DebugLine2);
        m_p2DGraphics->DrawText(300, 70, textColor, (const char *)DebugLine3);
        m_p2DGraphics->UpdateDisplay();    
}
