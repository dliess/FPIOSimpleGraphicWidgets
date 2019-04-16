#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <cstdint>
#include "FpFont.h"
#include "FpGfxTypes.h"
#include "FpColorRGB.h"
#include <string>

namespace fp
{
class RenderIf;
}

namespace gfxWidget
{

class TextField
{
public:
    enum class HPlacement
    {
        AlignLeft   = 0,
        AlignRight  = 1,
        AlignCenter = 2
    };
    enum class VPlacement
    {
        AlignTop     = 0,
        AlignBottom  = 1,
        AlignCenter  = 2       
    };
    TextField(  const fp::gfx::Coord&    upLeftPos,
                const fp::gfx::Size2D&   size,
                const fp::GfxFont&       rFont,
                uint8_t                  fontScaleFactor,
                const fp::ColorRGB& color,
                HPlacement hPlacement = HPlacement::AlignLeft,
                VPlacement vPlacement = VPlacement::AlignTop  );

    void draw(fp::RenderIf& r, const std::string& txt);
    void draw(fp::RenderIf& r, const std::string& txt, const fp::ColorRGB& color);
    void drawFieldBorder(fp::RenderIf& r, const fp::ColorRGB& color);
    void clear(fp::RenderIf& r, const fp::ColorRGB& clearColor = {0,0,0});

    void setHPlacement(HPlacement hPlacement);
    void setVPlacement(VPlacement vPlacement);
    void setFont(const fp::GfxFont& font, uint8_t scale = 1);

private:
    fp::gfx::Coord      m_upLeftPos;
    fp::gfx::Size2D     m_size;
    const fp::GfxFont*      m_pFont;
    uint8_t                 m_fontScaleFactor;
    fp::ColorRGB   m_color;
    HPlacement              m_hPlacement;
    VPlacement              m_vPlacement;

    fp::gfx::Coord     m_lastStrPos;
    fp::gfx::Size2D    m_lastStrSize;

    void clearPrev(fp::RenderIf& r);
};

} // namespace gfxwidget
#endif