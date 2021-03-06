#include "RenderEventInfo.h"

RenderEventInfo::RenderEventInfo(Gdiplus::Graphics* g, Gdiplus::Size parentSize)
{
	this->parentSize = parentSize;
	graphics = g;
}

RenderEventInfo::RenderEventInfo(Gdiplus::Graphics* g) : RenderEventInfo(g, Gdiplus::Size(0, 0))
{
}

Gdiplus::Graphics* RenderEventInfo::GetGraphics()
{
	return graphics;
}

Gdiplus::Size RenderEventInfo::GetParentSize()
{
	return parentSize;
}

void RenderEventInfo::SetParentSize(Gdiplus::Size parentSize)
{
	this->parentSize = parentSize;
}
