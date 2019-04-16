#include "ValueBarDrawer.h"
#include "FpRenderIf.h"

#include <iostream>

using namespace gfxWidget;

const fp::ColorRGB ValueBarDrawer::ClearColor = {0,0,0};


ValueBarDrawer::ValueBarDrawer( const fp::gfx::Coord&                        upLeft,
                                const fp::gfx::Size2D&                       size,
                                const value_utils::Range<ValueType>&         valueRange,
                                const fp::ColorRGB&                     frameColor,
                                const value_utils::Range<fp::ColorRGB>& barColorRange  ) :
    m_initialDraw(true),
    m_frame(upLeft, size),
    m_bar({upLeft.x + 1, upLeft.y + 1}, {size.w - 2, size.h - 2}),
    m_valueRange(valueRange),
    m_frameColor(frameColor),
    m_barColorRange(barColorRange),
    m_valuePosXLast(0),
    m_modulatedValuePosXLast(0)
{
}

void ValueBarDrawer::initialDraw()
{
    m_initialDraw = true;
}

void ValueBarDrawer::draw(fp::RenderIf& r, ValueType value, ValueType modulation)
{
    if(m_initialDraw)
    {
        m_initialDraw = false;
        r.drawRectangle( fp::gfx::Rectangle(
                                            fp::gfx::Coord(m_frame.upLeft.x, m_frame.upLeft.y-6),
                                            fp::gfx::Size2D(m_frame.size.w, m_frame.size.h + 12)),
                                        {0,0,0},
                                        true);
        r.drawRectangle( fp::gfx::Rectangle(m_frame.upLeft, m_frame.size),
                                        m_frameColor,
                                        false);
    }
    value_utils::limitToRange(value, m_valueRange);
    const value_utils::Range<fp::gfx::Pixel> barLengthPix(0, m_bar.size.w - 1);
    auto valuePosX = value_utils::mapValue(value, m_valueRange, barLengthPix);

    ValueType modulatedValue = value + modulation;
    value_utils::limitToRange(modulatedValue, m_valueRange);

    fp::gfx::Pixel modulatedValuePosX = value_utils::mapValue(modulatedValue, m_valueRange, barLengthPix);

    if (modulatedValuePosX > m_modulatedValuePosXLast)
    {
        for (fp::gfx::Pixel i = m_modulatedValuePosXLast; i <= modulatedValuePosX; ++i)
        {
            const int Xpos = m_bar.upLeft.x + i;
            fp::ColorRGB lineColor(
                value_utils::mapValue(i, barLengthPix, value_utils::Range<uint8_t>(m_barColorRange.min.r(), m_barColorRange.max.r())),
                value_utils::mapValue(i, barLengthPix, value_utils::Range<uint8_t>(m_barColorRange.min.g(), m_barColorRange.max.g())),
                value_utils::mapValue(i, barLengthPix, value_utils::Range<uint8_t>(m_barColorRange.min.b(), m_barColorRange.max.b()))   
            );
            r.drawLine(  fp::gfx::Coord( Xpos, m_bar.upLeft.y ),
                                        fp::gfx::Coord( Xpos, m_bar.upLeft.y + m_bar.size.h - 1 ),
                                        lineColor  );
        }
    }
    else if (modulatedValuePosX < m_modulatedValuePosXLast)
    {
        for (int i = m_modulatedValuePosXLast; i > modulatedValuePosX; --i)
        {
            const int Xpos = m_bar.upLeft.x + i;
            r.drawLine(  fp::gfx::Coord( Xpos, m_bar.upLeft.y ),
                                        fp::gfx::Coord( Xpos, m_bar.upLeft.y + m_bar.size.h - 1 ),
                                        ClearColor );
        }
    }

    if (valuePosX != m_valuePosXLast)
    {
        const int XposNew = m_bar.upLeft.x + valuePosX;
        const int XposOld = m_bar.upLeft.x + m_valuePosXLast;
        r.drawVLine( fp::gfx::Coord(XposOld, m_frame.upLeft.y - MidLineHeight),
                                    MidLineHeight,
                                    ClearColor);
        r.drawVLine( fp::gfx::Coord(XposNew, m_frame.upLeft.y - MidLineHeight),
                                    MidLineHeight,
                                    m_frameColor);
        r.drawVLine( fp::gfx::Coord(XposOld, m_frame.upLeft.y + m_frame.size.h),
                                    MidLineHeight,
                                    ClearColor);
        r.drawVLine( fp::gfx::Coord(XposNew, m_frame.upLeft.y + m_frame.size.h),
                                    MidLineHeight,
                                    m_frameColor);
    }
    m_modulatedValuePosXLast = modulatedValuePosX;
    m_valuePosXLast = valuePosX;
}
