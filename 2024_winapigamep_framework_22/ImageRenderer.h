#pragma once
#include "Component.h"

class Texture;
class ImageRenderer : public Component
{
public:
	ImageRenderer();
	virtual ~ImageRenderer();

public:
	virtual void LateUpdate() override;
	virtual void Render(HDC _hdc) override;
	
	void SetTexture(const wstring& m_texId, const wstring& m_texPath);
private:
	Texture* m_pTex = nullptr;
};

