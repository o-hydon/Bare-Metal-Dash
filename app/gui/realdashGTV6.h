
#ifndef _realdashGTV6_h
#define _realdashGTV6_h
#include "graphicsimage.h"
class CRealDashGTV6Objects
{

public:

    CRealDashGTV6Objects(C2DGraphics *p2DGraphics);
    ~CRealDashGTV6Objects(void);
private:
    C2DGraphics *m_p2DGraphics;
    unsigned int m_nDisplayWidth;
    unsigned int m_nDisplayHeight;
    void AddBGObjects(void);
    void AddDataObjects(void);

    static const T2DColor TextColor = COLOR2D(255, 255, 255);
    static const T2DColor SubTextColor = COLOR2D(190, 190, 190);
    static const T2DColor SubSubTextColor = COLOR2D(100, 100, 100);
    void AddBarLevel(unsigned nLevel, unsigned nMax,unsigned nX, unsigned nY);
};
#endif
