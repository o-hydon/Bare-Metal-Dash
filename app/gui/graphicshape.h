
#ifndef _graphicshape_h
#define _graphicshape_h


#include <circle/2dgraphics.h>

enum
{
};

class BackgroundShape
{
public:
	BackgroundShape (C2DGraphics *p2DGraphics);
	~BackgroundShape (void);


	void Draw (void);

private:
	static constexpr unsigned int imgWidth  = 1080;
	static constexpr unsigned int imgHeight = 1920;
	const unsigned char* m_pImageData; 

	C2DGraphics *m_p2DGraphics;
	unsigned m_nDisplayWidth;
	unsigned m_nDisplayHeight;
 
	T2DColor m_PixelBuffer[imgWidth * imgHeight];
	C2DImage m_Image;
};

#endif
