#pragma once
#include "Debug\TestMacro.h"

#include "TextBox.h"
#include "TwoStateButton.h"


class TextBackground : public LayerColor
{
public:
	virtual bool init();
	CREATE_FUNC(AVGDialogBox);

	void nextText();

	virtual void showTextBox();
	virtual void hideTextBox();

	virtual void onEnter() override;

	void hideBtnCallback();

	virtual void enterScene();
private:
	//ÎÄ±¾Óë±³¾°Í¼²ãË³Ðò
	const short BK_Z_ORDER = 0;
	const short TEXT_Z_ORDER = 1;

	void loadAllText();

	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	void onTouchEnded(Touch* pTouch, Event* pEvent);

	//TextBoxLayerColor* _nameBox;
	HideButton* _hideBtn;

	void onNotifyTextBox(EventCustom* pEvent);


};

/*class NameTextBox : public TextBoxLayerColor
{
public:
	CREATE_FUNC(NameTextBox);
	virtual bool init();

};*/