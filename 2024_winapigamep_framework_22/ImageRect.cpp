#include "pch.h"
#include "ImageRect.h"
#include "ImageRenderer.h"

ImageRect::ImageRect()
{
	AddComponent<ImageRenderer>();
}

ImageRect::ImageRect(const wstring& texture, const wstring& texturePath)
{
	AddComponent<ImageRenderer>();
	ImageRenderer* render = GetComponent<ImageRenderer>();

	render->SetTexture(texture, texturePath);
}
