#include "TableElement.h"


TableElement::TableElement() : TableElement("")
{
}

TableElement::TableElement(std::string name)
{
}

TableElement::TableElement(int x, int y, int width, int height, std::string name) : Label(x, y, width, height, name)
{
	highlightColor = Color(100, 100, 100);
	originalcolor = GetBackground();
}

void TableElement::SetValue(std::any value)
{
	this->value = value;
}

std::any TableElement::GetValue()
{
	return value;
}

bool TableElement::IsSelected()
{
	return selected;
}

void TableElement::SetSelected(bool selected)
{
	if (selected == true)
		SetBackground(highlightColor);
	else
		SetBackground(originalcolor);
	this->selected = selected;
}
