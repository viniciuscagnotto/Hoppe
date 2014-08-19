#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

class ResourceManager
{
public:
	enum EResources{
		kResource_Entity_Player = 0,
		kResource_Entity_Vortex,
		kResource_Entity_Asteroid_Small,
		kResource_Entity_Asteroid_Big,
		kResource_Entity_Comet,
		kResource_Entity_Satellite,
		kResource_Entity_BlackHole,
		kResource_Entity_Star,

		kResource_Background_Space,
		kResource_Background_Earth,
		kResource_Background_Satellite,
		
		kResource_Button_StartGame,

		kResource_Count
	};

	enum EFonts{
		kFont_Arial_8 = 0,

		kFont_Count
	};

private:
	CIw2DImage *m_resourcesMap[kResource_Count];
	CIw2DFont *m_fontsMap[kFont_Count];

public:
	ResourceManager();
	~ResourceManager();

	void Init();
	void Destroy();

	void RegisterResource(EResources id, const char * fileName);
	CIw2DImage *GetResource(EResources id);
	void RegisterFont(EFonts id, const char * fileName);
	CIw2DFont *GetFont(EFonts id);
};

extern ResourceManager* g_pResourceManager;


#endif //__RESOURCE_MANAGER_H__