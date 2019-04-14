#include "TextField.h"
#include <stdio.h> // snprintf()


TextField::TextField(   const fp::gfx::Coord&    upLeftPos,
                        const fp::gfx::Size2D&   size,
                        const fp::GFXfont&           rFont,
                        uint8_t                      fontScaleFactor,
                        const fp::ColorRGB& color,
                        HPlacement                   hPlacement,
                        VPlacement                   vPlacement  ):
    m_upLeftPos(upLeftPos),
    m_size(size),
    m_pFont(&rFont),
    m_fontScaleFactor(fontScaleFactor),
    m_color(color),
    m_hPlacement(hPlacement),
    m_vPlacement(vPlacement),
    m_lastStrPos({0,0}),
    m_lastStrSize({0,0})
    {}

void TextField::draw(fp::RenderIf& r, const std::string& txt)
{
    draw(r, txt, m_color);
}

void TextField::draw(fp::RenderIf& r, const std::string& txt, const fp::ColorRGB& color)
{
    //clearPrev(r);
    r.setFont(*m_pFont, m_fontScaleFactor);
    fp::gfx::Size2D    strSize;
    fp::gfx::Offset2D  strOffset;
    r.getRenderedTextSize(txt, nullptr, strSize, strOffset);
    fp::gfx::Coord txtMidLinePos;
    const int32_t widthDiff = static_cast<int32_t>(m_size.w) - static_cast<int32_t>(strSize.w);
    const int32_t heightDiff = static_cast<int32_t>(m_size.h) - static_cast<int32_t>(strSize.h);

    switch(m_hPlacement)
    {
        case HPlacement::AlignLeft:
            txtMidLinePos.x = m_upLeftPos.x;
            break;
        case HPlacement::AlignRight:
            txtMidLinePos.x = m_upLeftPos.x + widthDiff;
            break;
        case HPlacement::AlignCenter:
            txtMidLinePos.x = m_upLeftPos.x + (widthDiff / 2);
            break;
    }
    switch(m_vPlacement)
    {
        case VPlacement::AlignTop:
            txtMidLinePos.y = m_upLeftPos.y;
            break;
        case VPlacement::AlignBottom:
            txtMidLinePos.y = m_upLeftPos.y + m_size.h - strSize.h;
            break;
        case VPlacement::AlignCenter:
            txtMidLinePos.y = m_upLeftPos.y + (heightDiff / 2);
            break;
    }
    txtMidLinePos = {txtMidLinePos.x - strOffset.x, txtMidLinePos.y - strOffset.y};
    //r.drawRectangle({txtMidLinePos + strOffset, strSize}, {255,255,255}, false);
    r.drawText(txtMidLinePos, color, txt);
    m_lastStrPos  = txtMidLinePos;                            
    m_lastStrSize = strSize;
}

void TextField::clearPrev(fp::RenderIf& r)
{
    r.drawRectangle(fp::gfx::Rectangle( m_lastStrPos, m_lastStrSize ),
                                   {0,0,0},
                                   true);
}

void TextField::drawFieldBorder(fp::RenderIf& r, const fp::ColorRGB& color)
{
    r.drawRectangle(fp::gfx::Rectangle(
                                        fp::gfx::Coord({m_upLeftPos.x - 1, m_upLeftPos.y - 1}),
                                        fp::gfx::Size2D({m_size.w + 2, m_size.h + 2})),
                                   color,
                                   false);
}

void TextField::clear(fp::RenderIf& r, const fp::ColorRGB& clearColor)
{
    r.drawRectangle(fp::gfx::Rectangle(
                                        fp::gfx::Coord({m_upLeftPos.x - 1, m_upLeftPos.y - 1}),
                                        fp::gfx::Size2D({m_size.w + 2, m_size.h + 2})),
                                   clearColor,
                                   true);
}

void TextField::setHPlacement(HPlacement hPlacement)
{
    m_hPlacement = hPlacement;
}

void TextField::setVPlacement(VPlacement vPlacement)
{
    m_vPlacement = vPlacement;
}

void TextField::setFont(const fp::GFXfont& font, uint8_t scale)
{
    m_pFont = &font;
    m_fontScaleFactor = scale;
}
