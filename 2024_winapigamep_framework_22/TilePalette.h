#pragma once
class Texture;
class TilePalette
{
public:
	virtual void Init() abstract;
	Texture* GetTexture(const UCHAR& type) {
		return m_textures[type];
	}

private:
	void RegisterTile(const UCHAR type, const wstring& key, const wstring& path);

private:
	map<UCHAR, Texture*> m_textures;
};

