
#ifndef _graphicshape_h
#define _graphicshape_h


#include <circle/2dgraphics.h>
#include <fatfs/ff.h>
#include <circle/util.h>

enum
{
};
/**
 * @brief Represents a user bank account.
 *
 * Manages balance tracking, deposits, and withdrawals while 
 * preventing overdrafts.
 */
class BackgroundShape
{
public:
	AddImage (C2DGraphics *p2DGraphics);
	~AddImage (void);


	void Draw (void);

private:
	static constexpr unsigned int imgWidth  = 192*9;
	static constexpr unsigned int imgHeight = 108*9;
	unsigned char* m_pImageData[imgWidth * imgHeight * 3]; 

	C2DGraphics *m_p2DGraphics;
	unsigned m_nDisplayWidth;
	unsigned m_nDisplayHeight;
 
	C2DImage m_Image;
	T2DColor *m_pPixelBuffer;
    boolean m_bImageLoaded;
};

#endif
