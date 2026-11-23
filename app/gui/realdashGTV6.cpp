#include "realdashGTV6.h"

CRealDashGTV6Objects::CRealDashGTV6Objects(C2DGraphics *p2DGraphics)
: m_p2DGraphics(p2DGraphics),
  m_nDisplayWidth(m_p2DGraphics->GetWidth()),
  m_nDisplayHeight(m_p2DGraphics->GetHeight())
{
    m_p2DGraphics -> ClearScreen(COLOR2D(0,0,0));
    this -> AddBGObjects();
    this -> AddDataObjects();
    m_p2DGraphics -> UpdateDisplay();
}
CRealDashGTV6Objects::~CRealDashGTV6Objects(void)
{   
    
}

void CRealDashGTV6Objects::AddBGObjects(void)
{
    CImageFromFile BottomBar = CImageFromFile(m_p2DGraphics, "BottomBar", 1064, 82);
    BottomBar.Draw(m_nDisplayWidth / 2, 735, Centre, Top);
    CImageFromFile FuelTempBars = CImageFromFile(m_p2DGraphics, "Fuel+TempBars", 219, 142);
    FuelTempBars.Draw(45, m_nDisplayHeight / 2, Left, Centre);
    CImageFromFile LeftRightBar = CImageFromFile(m_p2DGraphics, "LeftRightBar", 308, 7);
    LeftRightBar.Draw(m_nDisplayWidth / 2 + 300, 560, Left, Centre);
    CImageFromFile RightLeftBar = CImageFromFile(m_p2DGraphics, "RightLeftBar", 308, 7);
    RightLeftBar.Draw(m_nDisplayWidth / 2 - 300, 560 , Right, Centre);

    m_p2DGraphics -> DrawText(1770, 360, SubSubTextColor, "GEAR", C2DGraphics::AlignCenter, FontOpenSansAll40);
    m_p2DGraphics -> DrawText(m_nDisplayWidth / 2, 360, SubSubTextColor, "M/H", C2DGraphics::AlignCenter, FontOpenSansAll40);

}

void CRealDashGTV6Objects::AddBarLevel(unsigned nLevel, unsigned nMax, unsigned nX, unsigned nY)
{
    unsigned RectWidth = ((nLevel * 200) / nMax);
    RectWidth += 4 * (RectWidth - 1) / 50;

    if (RectWidth > 0)
    {
        m_p2DGraphics -> DrawRect(nX, nY, RectWidth,  6, TextColor);
    }
    if (RectWidth < 212)
    {
        m_p2DGraphics -> DrawRect(nX + RectWidth+1, nY, 212 - RectWidth,  6, SubSubTextColor);
    }
    m_p2DGraphics -> DrawRect(nX + 50, nY, 4, 6, COLOR2D(0,0,0));
    m_p2DGraphics -> DrawRect(nX + 104, nY, 4, 6, COLOR2D(0,0,0));
    m_p2DGraphics -> DrawRect(nX + 158, nY, 4, 6, COLOR2D(0,0,0));
    
}

void CRealDashGTV6Objects::AddDataObjects(void)
{
    m_p2DGraphics -> DrawText(m_nDisplayWidth / 2, 400, TextColor, "123", C2DGraphics::AlignCenter, FontOpenSansNumbers320);

    m_p2DGraphics -> DrawText(1770, 400, SubTextColor, "5", C2DGraphics::AlignCenter, FontOpenSansNumbers320);
    
    m_p2DGraphics -> DrawText(20, 20, SubSubTextColor, "mm:hh", C2DGraphics::AlignLeft, FontOpenSansAll40);
    m_p2DGraphics -> DrawText(1900, 20, SubSubTextColor, "DD.MM.YYYY", C2DGraphics::AlignRight, FontOpenSansAll40);

    AddBarLevel(17, 102, 48, 518);
    AddBarLevel(17, 102, 48, 596);

}