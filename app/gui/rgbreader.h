#ifndef _rgbreader_h
#define _rgbreader_h

#include <circle/fs/fat/fatfs.h>

class CRGBReader
{
public:
    // Constructor: Pass the mounted FATFS object (e.g., from your Kernel)
    CRGBReader(CFATFileSystem *pFileSystem);
    ~CRGBReader(void);

    // Opens a specified .rgb file from the root directory (filename should include the .rgb)
    // Returns True if file sucessfully opened, False if non-exisitent or error
    bool Open(const char *pFilename);

    // Reads a specified chunks contents into pBuffer.
    // Returns the number of bytes read, or 0 on failure.
    unsigned ReadChunk(const char *pFilename, u8 *pBuffer, unsigned nBufferSize);

    //Accessors for the internal buffer and current chunk size
    const u8 *GetBuffer(void) const;
    unsigned GetChunkSize(void) const;

    //Returns the total file size in bytes
    unsigned GetFileSize(void) const;

    //Close an open file should one exist
    void Close(void);

private:
    CFATFileSystem *m_pFileSystem;
};

#endif