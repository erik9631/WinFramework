#pragma once
#include "MouseStateSubject.h"
#include "MouseStateSubscriber.h"
#include <string>
#include <vector>

class Button;
class ComboSelection;

class ComboElement : public MouseStateSubscriber, public MouseStateSubject
{
private:
	std::wstring text;
	Button* elementGui;
	ComboSelection& comboSelection;
	std::vector<std::reference_wrapper<MouseStateSubscriber>> mouseSubscribers;
	bool isSelected = false;

public:
	ComboElement(ComboSelection& comboSelection, std::wstring displayText);
	std::wstring GetText();
	void SetText(std::wstring text);

	void DisplayElementGui();
	void RemoveElementGui();

	bool IsSelected();
	void SetSelected(bool selected);
	

	// Inherited via MouseStateSubject
	virtual void NotifyOnMouseDown(EventMouseStateInfo e) override;

	virtual void NotifyOnMouseUp(EventMouseStateInfo e) override;

	virtual void NotifyOnMousePressed(EventMouseStateInfo e) override;

	virtual void NotifyOnMouseMove(EventMouseStateInfo e) override;

	virtual void NotifyOnMouseEnter(EventMouseStateInfo e) override;

	virtual void NotifyOnMouseLeave(EventMouseStateInfo e) override;

	virtual void AddMouseStateSubscriber(MouseStateSubscriber& subscriber) override;

	virtual void RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber) override;

	virtual bool HasMouseEntered() override;


	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;

	virtual void OnMouseUp(EventMouseStateInfo e) override;

	virtual void OnMousePressed(EventMouseStateInfo e) override;

	virtual void OnMouseMove(EventMouseStateInfo e) override;

	virtual void OnMouseEntered(EventMouseStateInfo e) override;

	virtual void OnMouseLeft(EventMouseStateInfo e) override;

};

