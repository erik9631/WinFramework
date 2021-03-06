#include "Text.h"
#include "RenderEventInfo.h"
#include "ClassMethod.h"

void Text::SetLineAlignment(Gdiplus::StringAlignment alignment)
{
    this->lineAlignment = alignment;
}

void Text::SetAlignment(Gdiplus::StringAlignment alignment)
{
    this->alignment = alignment;
}

Gdiplus::StringAlignment Text::GetLineAlignment()
{
    return lineAlignment;
}

Gdiplus::StringAlignment Text::GetAlignment()
{
    return alignment;
}


Text::Text(std::string fontFamily) : renderBehavior(*this), reflectionContainer(*this)
{
    reflectionContainer.RegisterMethod("text-color", "SetColor", &Text::SetColor);
    reflectionContainer.RegisterMethod("font-size", "SetFontSize", &Text::SetFontSize);

    std::wstring family = std::wstring(fontFamily.begin(), fontFamily.end());
    this->fontFamily = new Gdiplus::FontFamily(family.c_str());
    font = new Gdiplus::Font(this->fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    brush = new Gdiplus::SolidBrush(Gdiplus::Color::White);
    position = Gdiplus::PointF(0, 0);
    percentualPosition = Gdiplus::PointF(0, 0);
}

void Text::SetText(std::wstring text)
{
    this->text = text;
}

std::wstring Text::GetText()
{
    return this->text;
}

void Text::SetPosition(Gdiplus::PointF position)
{
    this->position = position;
}

void Text::SetPercentualPosition(Gdiplus::PointF position)
{
    percentualPosition = position;
}

Gdiplus::PointF Text::GetPosition()
{
    return position;
}

void Text::SetColor(Gdiplus::Color color)
{
    brush->SetColor(color);
}

void Text::SetFontSize(double fontSize)
{
    this->fontSize = fontSize;
    delete font;
    font = new Gdiplus::Font(this->fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
}

void Text::OnRender(RenderEventInfo e)
{
    Gdiplus::PointF realPosition = position;
    Gdiplus::Graphics* g = e.GetGraphics();
    Gdiplus::Matrix matrix{};
    g->GetTransform(&matrix);
    g->ResetTransform();
    g->TranslateTransform(matrix.OffsetX(), matrix.OffsetY());

    g->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);


     realPosition.X += (float)e.GetParentSize().Width * percentualPosition.X;
     realPosition.Y += (float)e.GetParentSize().Height * percentualPosition.Y;

    Gdiplus::StringFormat format;
    format.SetAlignment(alignment);
    format.SetLineAlignment(lineAlignment);
    g->DrawString(text.c_str(), -1, font, realPosition, &format, brush);
    g->SetTransform(&matrix);

}

void Text::Repaint()
{

}

void Text::AddRenderable(Renderable& renderable)
{
    renderBehavior.AddRenderable(renderable);
}

void Text::RemoveRenderable(Renderable& renderable)
{
    renderBehavior.RemoveRenderable(renderable);
}

std::vector<std::reference_wrapper<Renderable>> Text::GetRenderables()
{
    return renderBehavior.GetRenderables();
}

bool Text::HasMethod(std::string method)
{
    return reflectionContainer.HasMethod(method);
}

ReflectionContainer<Text>& Text::GetReflectionContainer()
{
    return reflectionContainer;
}
