#include "pch.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"
#include "RectObject.h"

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


}

void ImageRenderer::SetTexture(const wstring& m_texId, const wstring& m_texPath)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(m_texId, m_texPath);
}
