#pragma once
#include "Component.h"
#include "Text.h"
#include "Background.h"
#include "TextInputBehavior.h"
#include "SimpleBorder.h"
class TextInput : public Component
{
private:
	Background background;
	SimpleBorder border;
	Text text;
	TextInputBehavior inputBehavior;

public:
	TextInput();
	/**
	 * \param x the X position of the grid.
	 * \param y the Y position of the grid
	 * \param width the width of the grid
	 * \param height the height of the grid.
	 * \param name the identification name of the grid. This is not a display value.
	 */
	TextInput(int x, int y, int width, int height, string windowName);

	/**
	 * \param name the identification name of the grid. This is not a display value.
	 */
	TextInput(string name);


	void SetText(wstring text) override;
	wstring GetText() override;
	/**
	 * \return returns the background color.
	 */
	Color GetBackgroundColor();

	/**
	 * \param state sets whether the text field is multiline.
	 */
	void SetMultiline(bool state);
	
	/**
	 * \return returns whether the textfield is multiline.
	 */
	bool IsMultiLine();

	/**
	 * \param color sets the background color.
	 */
	void SetBackgroundColor(Color color);
};

