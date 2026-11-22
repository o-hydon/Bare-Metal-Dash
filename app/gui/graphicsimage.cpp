#include "graphicsimage.h"

#define BYTES_PER_PIXEL 4   //  bytes per pixel in 0BGR


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
        "Position out of bounds",                          // 21: Draw failed
    };

    m_p2DGraphics -> DrawRect(0,0,m_p2DGraphics -> GetWidth() ,60, COLOR2D(0,0,0));
    m_p2DGraphics -> DrawText(20, 20, ErrorColor, "[Error]");
    if ((ErrorNumber > 21) || (ErrorNumber < 1)){ErrorNumber = 20;};
    CString ErrorMessage;
    ErrorMessage.Format("%s %s", Operation, s_Errors[ErrorNumber]);
    m_p2DGraphics -> DrawText(80, 20, TextColor, (const char*) ErrorMessage);
    m_p2DGraphics -> UpdateDisplay();
    while (1);
};
CImageFromFile::CImageFromFile (C2DGraphics *p2DGraphics,
            const char * pFilename,
            const unsigned int nImgWidth,
            const unsigned int nImgHeight)
:   m_nImgWidth (nImgWidth),
    m_nImgHeight (nImgHeight),
    m_p2DGraphics (p2DGraphics),
    m_pPixelBuffer (nullptr),
    nDisplayWidth (p2DGraphics -> GetWidth()),
    nDisplayHeight (p2DGraphics -> GetHeight())
{
    CString Filepath = CString("SD:/");
    Filepath += pFilename;
    Filepath += ".rgb";

    FIL File;

    FRESULT OpenResult = f_open(&File, Filepath, FA_READ | FA_OPEN_EXISTING);

    if (OpenResult != FR_OK) {this -> DisplayErrorMessage("File failed to open:", OpenResult);};
   
    unsigned int nBytesToRead = m_nImgWidth * m_nImgHeight * BYTES_PER_PIXEL;
    unsigned int nBytesRead;
    unsigned int nImageSize = m_nImgWidth * m_nImgHeight;
    
    m_pPixelBuffer = new T2DColor[nImageSize]; //T2DColor uses 0RGB
    FRESULT ReadResult = f_read(&File, m_pPixelBuffer, nBytesToRead, &nBytesRead);

    if (ReadResult != FR_OK) {this -> DisplayErrorMessage("Failed to read file:", ReadResult);};

    FRESULT CloseResult = f_close(&File);
    if (CloseResult != FR_OK) {this -> DisplayErrorMessage("Failed to read close:", CloseResult);};
    
       
   
}
CImageFromFile::~CImageFromFile(void)
{
    delete[] m_pPixelBuffer;
}
void CImageFromFile::Draw(unsigned int nX, unsigned int nY, u8 pXJustification, u8 pYJustification)
{
    unsigned int nXJustified = nX - 0.5 * pXJustification * m_nImgWidth;
    unsigned int nYJustified = nY - 0.5 * pYJustification * m_nImgHeight;    


    if (((nXJustified + m_nImgWidth) > nDisplayWidth)
      ||((nYJustified + m_nImgHeight) > nDisplayHeight)
      ||( nXJustified < 0 )
      ||( nYJustified < 0 )) {DisplayErrorMessage("Image cannot be displayed:", 21);};

    m_p2DGraphics->DrawImage(nXJustified, nYJustified, m_nImgWidth, m_nImgHeight, m_pPixelBuffer);
}
