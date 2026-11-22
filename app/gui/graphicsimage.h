
#ifndef _graphicsimage_h
#define _graphicsimage_h

#define	Top				0x00
#define	Bottom			0x02
#define	Right			0x02
#define	Left			0x00
#define	Centre			0x01


#include <circle/2dgraphics.h>
#include <fatfs/ff.h>
#include <circle/util.h>
#include <circle/string.h>

enum
{
};
/**
 * @brief Adds an image from a .rgb file using RGB24 pixel format that is stored in the root directory. 
 * @details Can Generate .rgb from JPEG using ffmpeg with linux command line: 'ffmpeg -i  path/to/img.jpg -vf scale=width:height -pix_fmt rgb24 -f rawvideo path/to/SDcard/rootdir/Filename.rgb'
 * 
 */
class CImageFromFile
{
public:
	unsigned int m_nX;
	unsigned int m_nY;
	const unsigned int m_nImgWidth;
	const unsigned int m_nImgHeight;

	/**
 	* \param p2DGraphics 	> Pointer to the 2D graphics engine
	* \param Filename 		> Image filename without the '.rgb'
	* \param nImgWidth 		> Width of the image in pixels
	* \param nImgHeight 	> Height of the image in pixels
	
	*/
	CImageFromFile (	C2DGraphics *p2DGraphics,
			 	const char *pFilename,
		 	  	const unsigned int nImgWidth,
				const unsigned int nImgHeight);
	~CImageFromFile (void);
	/**
	* \param nX 			 > x coordiate of refrence point
	* \param nY 			 > y coordiate of refrence point
	* \param nXJustification > The refrence point on the image for the X position
	* \param nYJustification > The refrence point on the image for the Y position
	*/
	void Draw(unsigned int nX, unsigned int nY, u8 nXJustification = Top, u8 nYJustification = Left);

private:
	
	void DisplayErrorMessage(const char * operation, uint8_t error_number);
	C2DGraphics *m_p2DGraphics;

	T2DColor *m_pPixelBuffer;	
	unsigned int nDisplayWidth;
	unsigned int nDisplayHeight;

	static const T2DColor TextColor = COLOR2D(255, 255, 255);
	static const T2DColor ErrorColor = COLOR2D(255, 0, 0);
};

#endif
