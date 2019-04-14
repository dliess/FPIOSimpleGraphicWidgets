#ifndef _VALUE_BAR_DRAWER_H
#define _VALUE_BAR_DRAWER_H

#include <cstdint>
#include "FpWidgetOut_Spec.h"
#include "ValueUtils.h"

class RenderIf;

class ValueBarDrawer
{
public:
    using ValueType = int32_t;
    ValueBarDrawer(const fp::Display::Coord&                        upLeft,
                   const fp::Display::Size2D&                       size,
                   const value_utils::Range<ValueType>&              valueRange,
                   const fp::ColorRGB&                     frameColor,
                   const value_utils::Range<fp::ColorRGB>& barColorRange);
    void initialDraw();
    void draw(RenderIf& r, ValueType value, ValueType modulation = 0);

private:
    struct Frame
    {
        Frame(const fp::Display::Coord&  upLeft_,
              const fp::Display::Size2D& size_) : upLeft(upLeft_),size(size_){};
        const fp::Display::Coord  upLeft;
        const fp::Display::Size2D size;
    };
    bool                                       m_initialDraw;
    Frame                                      m_frame;
    Frame                                      m_bar;
    value_utils::Range<ValueType>              m_valueRange;
    fp::ColorRGB                     m_frameColor;
    value_utils::Range<fp::ColorRGB> m_barColorRange;
    static const fp::ColorRGB        ClearColor;
    static const fp::Display::Pixel           MidLineHeight = 4;
    fp::Display::Pixel                        m_valuePosXLast;
    fp::Display::Pixel                        m_modulatedValuePosXLast;
};

#endif