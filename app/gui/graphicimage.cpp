#include "graphicsimage.h"

#define BYTES_PER_PIXEL 3   // 3 bytes per pixel in RGB24

T2DColor textColor = COLOR2D(255, 255, 255);

DrawImageFromFile::DrawImageFromFile (C2DGraphics *p2DGraphics,
            const char * pFilename,
            const unsigned int nImgWidth,
            const unsigned int nImgHeight,
            const unsigned int nX,
            const unsigned int nY,
            const char *pJustification)
:   m_nX (nX),
    m_nY (nY),
    m_Justification (pJustification),
    m_nImgHeight (nImgHeight),
    m_nImgWidth (nImgWidth),
    m_p2DGraphics (p2DGraphics),
    m_pPixelBuffer (nullptr),
    m_bImageLoaded (false)
{
    CString Filepath = CString("SD:/");
    Filepath += pFilename;
    Filepath += ".rgb";

    FIL File;

    FRESULT OpenResult = f_open(&File, Filepath, FA_READ | FA_OPEN_EXISTING);

    if (OpenResult == FR_OK)
    {

        unsigned int nBytesToRead = m_nImgWidth * m_nImgHeight * BYTES_PER_PIXEL;
        unsigned int nBytesRead;
        unsigned int nImageSize = m_nImgWidth * m_nImgHeight;

        m_pPixelBuffer = new T2DColor[nImageSize];
        f_read(&File, m_pPixelBuffer, nBytesToRead, &nBytesRead);

        if (nBytesToRead == nBytesRead)
        {
            m_bImageLoaded = true;
        }
        f_close(&File);
    }
}
DrawImageFromFile::~DrawImageFromFile(void)
{
    delete[] m_pPixelBuffer;
}
void DrawImageFromFile::Draw(void)
{
        m_p2DGraphics->DrawImage(m_nX, m_nY, m_nImgWidth, m_nImgHeight, m_pPixelBuffer);


        // CString DebugLine1;
        // DebugLine1.Format("Display: %u x %u | BPP: %u | Buffer: %s",
        //                   imgWidth, imgHeight, BYTES_PER_PIXEL,
        //                   m_pPixelBuffer != 0 ? "OK" : "NULL");

        // CString DebugLine2;
        // DebugLine2.Format("f_open: %d | f_read: %d | FileSize: %u | Wanted: %u | Read: %u",
        //                   (int)g_OpenResult, (int)g_ReadResult,
        //                   g_nFileSize, g_nBytesWanted, g_nBytesRead);

        // T2DColor testColor = COLOR2D(0xab, 0xcd, 0xef);
        // CString DebugLine3;
        // DebugLine3.Format("sizeof(T2DColor): %u | COLOR2D(ab,cd,ef): 0x%08X",
        //                   (unsigned)sizeof(T2DColor), (unsigned)testColor);

        // m_p2DGraphics->DrawRect(300, 10, 950, 100, COLOR2D(0, 0, 0));
        // m_p2DGraphics->DrawText(300, 20, textColor, (const char *)DebugLine1);
        // m_p2DGraphics->DrawText(300, 45, textColor, (const char *)DebugLine2);
        // m_p2DGraphics->DrawText(300, 70, textColor, (const char *)DebugLine3);
        m_p2DGraphics->UpdateDisplay();    
}
