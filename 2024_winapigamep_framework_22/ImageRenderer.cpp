#include "pch.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"
#include "RectObject.h"
#include "Texture.h"

ImageRenderer::ImageRenderer()
{
}

ImageRenderer::~ImageRenderer()
{
	if (m_pTex != nullptr)
		delete m_pTex;
}

void ImageRenderer::LateUpdate()
{

}

void ImageRenderer::Render(HDC _hdc)
{
	RectObject* owner = dynamic_cast<RectObject*>(GetOwner());
	assert(owner != nullptr);

	RECT rect;
	owner->GetRect(&rect);

	Vec2 size = owner->GetSize();

	::TransparentBlt(_hdc
		, rect.left
		, rect.top
		, size.x, size.y,
		m_pTex->GetTexDC()
		, 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), RGB(255, 0, 255));
}

void ImageRenderer::SetTexture(const wstring& m_texId, const wstring& m_texPath)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(m_texId, m_texPath);
}
