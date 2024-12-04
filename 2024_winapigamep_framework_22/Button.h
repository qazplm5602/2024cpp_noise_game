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
    Delegate<void> OnClick;
    Delegate<void> OnHover;
    Delegate<void> ExitHover;
    virtual void Update() override;
    void Refresh();
private:
    bool b_isHover;
    RECT* rect;
};

