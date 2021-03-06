#pragma once
#include "Component.h"
#include "SimpleBorder.h"
#include "Text.h"
#include "Background.h"
#include "CheckboxBehavior.h"

class Checkbox : public Component, public CheckboxStateSubject
{
private:
	SimpleBorder border;
	SimpleBorder checkboxBorder;
	Background background;
	CheckBoxBehavior checkboxBehavior;
	bool checked = false;

	Text checkBoxChar;
	Text text;
public:
	/**
	 * \param text unicode text of the button which is to be displayed.
	 */
	void SetText(std::wstring text) override;

	/**
	 * Invokes a check operation on the button. If checked the checkbox gets unchecked otherwise it gets checked.
	 */
	void Check();


	/**
	 * \return returns the identification text of the checkbox.
	 */
	std::wstring GetText() override;

	/**
	 * \param state sets the checked state of the checkbox. True for checked false for unchecked.
	 */
	void SetChecked(bool state);

	/**
	 * \return returns whether the checkbox is checked.
	 */
	bool IsChecked();

	/**
	 * Creates a new checkbox with no name 0 width and height and 0 x position and y position.
	 */
	Checkbox();

	/**
	 * Creates a new checkbox with 0 width and height and 0 x position and y position.
	 * \param name the name used to identify the checkbox. This is not a display value.
	*/
	Checkbox(string name);

	/**
	 * \param x the x position where the checkbox should be located
	 * \param y the y position where the checkbox should be located
	 * \param width the width of the checkbox
	 * \param height the height of the checkbox
	 * \param name the name used to identify the checkbox. This is not a display value.
	*/
	Checkbox(int x, int y, int width, int height, string name);

	// Inherited via CheckboxStateSubject
	virtual void AddCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber) override;
	virtual void RemoveCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber) override;
	virtual void NotifyOnChecked(EventCheckboxStateInfo info) override;
};

