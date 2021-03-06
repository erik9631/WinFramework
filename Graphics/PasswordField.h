#pragma once
#include "Component.h"
#include "Text.h"
#include "TextInputBehavior.h"

class PasswordField : public Component
{
private:
	Text text;
	wstring realText;
	Background background;
	SimpleBorder border;
	TextInputBehavior behavior;

public:
	PasswordField();

	/**
	 * \param x the X position of the grid.
	 * \param y the Y position of the grid
	 * \param width the width of the grid
	 * \param height the height of the grid.
	 * \param name the identification name of the grid. This is not a display value.
	 */
	PasswordField(int x, int y, int width, int height, string windowName);

	/**
	 * \param name the identification name of the grid. This is not a display value.
	 */
	PasswordField(string name);

	
	void SetText(wstring text) override;
	wstring GetText() override;

	/**
	 * \return returns the background color.
	 */
	Color GetBackgroundColor();

	/**
	 * \param color sets the background color.
	 */
	void SetBackgroundColor(Color color);
};

