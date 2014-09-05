#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

class ResourceManager
{
public:
	static const uint s_kMaxGraphics = 64;
	static const uint s_kMaxAtlases = 32;
	static const uint s_kMaxFonts = 8;
	

private:
	CIw2DImage *m_graphics[s_kMaxGraphics];
	CustomAtlas *m_atlases[s_kMaxAtlases];
	CIw2DFont *m_fonts[s_kMaxFonts];

public:
	ResourceManager();
	~ResourceManager();

	void Init();
	void Destroy();

	void RegisterGraphic(uint index, const char * fileName);
	CIw2DImage *GetGraphic(uint index);
	void RegisterAtlas(uint textureIndex, const char * fileName);
	CustomAtlas *GetAtlas(uint index);
	void RegisterFont(uint index, const char * fileName);
	CIw2DFont *GetFont(uint index);

};

extern ResourceManager* g_pResourceManager;


#endif //__RESOURCE_MANAGER_H__