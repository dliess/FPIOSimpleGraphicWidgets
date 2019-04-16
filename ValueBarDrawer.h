#ifndef _VALUE_BAR_DRAWER_H
#define _VALUE_BAR_DRAWER_H

#include <cstdint>
#include "ValueUtils.h"
#include "FpGfxTypes.h"
#include "FpColorRGB.h"

namespace fp
{
class RenderIf;
}

namespace gfxWidget
{

class ValueBarDrawer
{
public:
    using ValueType = int32_t;
    ValueBarDrawer(const fp::gfx::Coord&                   upLeft,
                   const fp::gfx::Size2D&                  size,
                   const value_utils::Range<ValueType>&    valueRange,
                   const fp::ColorRGB&                     frameColor,
                   const value_utils::Range<fp::ColorRGB>& barColorRange);
    void initialDraw();
    void draw(fp::RenderIf& r, ValueType value, ValueType modulation = 0);

private:
    struct Frame
    {
        Frame(const fp::gfx::Coord&  upLeft_,
              const fp::gfx::Size2D& size_) : upLeft(upLeft_),size(size_){};
        const fp::gfx::Coord  upLeft;
        const fp::gfx::Size2D size;
    };
    bool                                       m_initialDraw;
    Frame                                      m_frame;
    Frame                                      m_bar;
    value_utils::Range<ValueType>              m_valueRange;
    fp::ColorRGB                     m_frameColor;
    value_utils::Range<fp::ColorRGB> m_barColorRange;
    static const fp::ColorRGB        ClearColor;
    static const fp::gfx::Pixel           MidLineHeight = 4;
    fp::gfx::Pixel                        m_valuePosXLast;
    fp::gfx::Pixel                        m_modulatedValuePosXLast;
};

} // namespace gfxWidget
#endif