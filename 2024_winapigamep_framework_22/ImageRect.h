#pragma once
#include "RectObject.h"
class ImageRect :
    public RectObject
{
public:
    ImageRect();
    ImageRect(const wstring& texture, const wstring& texturePath);
};

