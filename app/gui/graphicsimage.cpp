#include "graphicsimage.h"

#define BYTES_PER_PIXEL 4   //  bytes per pixel in 0RGB

T2DColor TextColor = COLOR2D(255, 255, 255);
T2DColor ErrorColor = COLOR2D(255, 0, 0);
void CImageFromFile::DisplayErrorMessage(const char * Operation, uint8_t ErrorNumber)
{
    static const char * const s_Errors[] =
    {
        "Succeeded",                                       // 0: FR_OK
        "Hard error occurred in low-level disk I/O layer", // 1: FR_DISK_ERR
        "Assertion failed (internal error)",               // 2: FR_INT_ERR
        "Physical drive cannot work (not ready)",          // 3: FR_NOT_READY
        "Could not find the file",                         // 4: FR_NO_FILE
        "Could not find the path",                         // 5: FR_NO_PATH
        "Path name format is invalid",                     // 6: FR_INVALID_NAME
        "Access denied or directory full",                 // 7: FR_DENIED
        "File or directory already exists",                // 8: FR_EXIST
        "File or directory object is invalid",             // 9: FR_INVALID_OBJECT
        "Physical drive is write protected",               // 10: FR_WRITE_PROTECTED
        "Logical drive number is invalid",                 // 11: FR_INVALID_DRIVE
        "Volume has no work area (not mounted)",           // 12: FR_NOT_ENABLED
        "There is no valid FAT volume",                    // 13: FR_NO_FILESYSTEM
        "f_mkfs aborted due to parameter error",           // 14: FR_MKFS_ABORTED
        "Timed out waiting to access volume",              // 15: FR_TIMEOUT
        "Operation rejected by file sharing policy",       // 16: FR_LOCKED
        "Not enough memory for LFN working buffer",        // 17: FR_NOT_ENOUGH_CORE
        "Too many open files",                             // 18: FR_TOO_MANY_OPEN_FILES
        "Given parameter is invalid",                      // 19: FR_INVALID_PARAMETER
        "Unknown error"                                    // 20: Should not get here
    };

    m_p2DGraphics -> DrawRect(0,0,m_p2DGraphics -> GetWidth() ,60, COLOR2D(0,0,0));
    m_p2DGraphics -> DrawText(20, 20, ErrorColor, "[Error]");
    if ((ErrorNumber > 19) || (ErrorNumber < 1)){ErrorNumber = 20;};
    CString ErrorMessage;
    ErrorMessage.Format("%s %s", Operation, s_Errors[ErrorNumber]);
    m_p2DGraphics -> DrawText(80, 20, TextColor, (const char*) ErrorMessage);
    m_p2DGraphics -> UpdateDisplay();
    while (1);
};
CImageFromFile::CImageFromFile (C2DGraphics *p2DGraphics,
            const char * pFilename,
            const unsigned int nImgWidth,
            const unsigned int nImgHeight,
            const unsigned int nX,
            const unsigned int nY,
            const char *pJustification)
:   m_nX (nX),
    m_nY (nY),
    m_Justification (pJustification),
    m_nImgWidth (nImgWidth),
    m_nImgHeight (nImgHeight),
    m_p2DGraphics (p2DGraphics),
    m_pPixelBuffer (nullptr),
    m_bImageLoaded (false)
{
    CString Filepath = CString("SD:/");
    Filepath += pFilename;
    Filepath += ".rgb";

    FIL File;

    FRESULT OpenResult = f_open(&File, Filepath, FA_READ | FA_OPEN_EXISTING);

    if (OpenResult != FR_OK) {this -> DisplayErrorMessage("File failed to open,", OpenResult);};
   
    unsigned int nBytesToRead = m_nImgWidth * m_nImgHeight * BYTES_PER_PIXEL;
    unsigned int nBytesRead;
    unsigned int nImageSize = m_nImgWidth * m_nImgHeight;
    
    m_pPixelBuffer = new T2DColor[nImageSize]; //T2DColor uses 0RGB
    FRESULT ReadResult = f_read(&File, m_pPixelBuffer, nBytesToRead, &nBytesRead);
    

    if (nBytesToRead == nBytesRead)
    {
        m_bImageLoaded = true;
    }

    if ((ReadResult != FR_OK) || !m_bImageLoaded) {this -> DisplayErrorMessage("Failed to read file,", ReadResult);};

    FRESULT CloseResult = f_close(&File);
    if (CloseResult != FR_OK) {this -> DisplayErrorMessage("Failed to read close,", CloseResult);};
    
       
   
}
CImageFromFile::~CImageFromFile(void)
{
    delete[] m_pPixelBuffer;
}
void CImageFromFile::Draw(void)
{
    CString DebugLine1;
    DebugLine1.Format("Display: %u x %u | BPP: %u | Buffer: %s",
                        m_nImgWidth, m_nImgHeight, BYTES_PER_PIXEL,
                        m_pPixelBuffer != 0 ? "OK" : "NULL");

        CString DebugLine2;
        DebugLine2.Format("X: %u | Y: %u, Width: %u | Height: %u",
                          m_nX, m_nY, m_nImgWidth, m_nImgHeight);
    

        CString DebugLine3;
        DebugLine3.Format("sizeof(T2DColor): %u | COLOR2D(00,00,00): 0x%08X, Actual: 0x%08X",
                          (unsigned)sizeof(T2DColor(0xFF0000FF)), (unsigned)T2DColor(0xFF0000FF), (unsigned)m_pPixelBuffer[0]);

    m_p2DGraphics->DrawRect(300, 10, 950, 100, T2DColor(0xFFFF0000));
    m_p2DGraphics->DrawRect(300, 110, 950, 100, T2DColor(0xFF00FF00));
    m_p2DGraphics->DrawRect(300, 210, 950, 100, T2DColor(0xFF0000FF));

    m_p2DGraphics->DrawText(300, 20, TextColor, (const char *)DebugLine1);
    m_p2DGraphics->DrawText(300, 45, TextColor, (const char *)DebugLine2);
    m_p2DGraphics->DrawText(300, 70, TextColor, (const char *)DebugLine3);
    m_p2DGraphics->DrawImage(m_nX, m_nY, m_nImgWidth, m_nImgHeight, m_pPixelBuffer);

    m_p2DGraphics->UpdateDisplay();  

    while(1);
}
