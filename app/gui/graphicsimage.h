
#ifndef _graphicimage_h
#define _graphicimage_h


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
class DrawImageFromFile
{
public:
	unsigned int m_nX;
	unsigned int m_nY;
	CString m_Justification;
	const unsigned int m_nImgWidth;
	const unsigned int m_nImgHeight;

	/**
 	* @param p2DGraphics 	> Pointer to the 2D graphics engine
	* @param Filename 		> Image filename without the '.rgb'
	* @param nImgWidth 		> Width of the image in pixels
	* @param nImgHeight 	> Height of the image in pixels
	* @param nX 			> x coordiate of refrence point
	* @param nY 			> y coordiate of refrence point
	* @param Justification 	> The refrence point for the images position
	*/
	DrawImageFromFile (	C2DGraphics *p2DGraphics,
			 	const char *pFilename,
		 	  	const unsigned int nImgWidth,
				const unsigned int nImgHeight,
			  	const unsigned int nx,
				const unsigned int ny,
				const char *pJustification = "Centre");
	~DrawImageFromFile (void);


	void Draw (void);

private:
	
	//unsigned char* m_pImageData[nImgWidth * imgHeight * 3]; 

	C2DGraphics *m_p2DGraphics;

	T2DColor *m_pPixelBuffer;
    boolean m_bImageLoaded;
};

#endif
