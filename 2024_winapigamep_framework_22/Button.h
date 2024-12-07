#pragma once
#include "RectObject.h"
#include "Delegate.h"
class Button :
    public RectObject
{
public:
    Button();
    ~Button();
public:
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;
public:
    Delegate<void> OnClick;
    Delegate<void> OnHover;
    Delegate<void> ExitHover;
    void Refresh();
private:
    bool b_isHover;
    RECT* rect;
};

