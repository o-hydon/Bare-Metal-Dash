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

    m_p2DGraphics -> DrawText(1770, 320, SubSubTextColor, "GEAR", C2DGraphics::AlignCenter, Font8x10);
    m_p2DGraphics -> DrawText(m_nDisplayWidth / 2, 360, SubSubTextColor, "M/H", C2DGraphics::AlignCenter, FontOpenSansNumbers40);

}

void CRealDashGTV6Objects::AddDataObjects(void)
{
    m_p2DGraphics -> DrawText(m_nDisplayWidth / 2, 400, TextColor, "123", C2DGraphics::AlignCenter, FontOpenSansNumbers320);
    
    m_p2DGraphics -> DrawText(1770, 400, SubTextColor, "5", C2DGraphics::AlignCenter, FontOpenSansNumbers320);

}