#if !defined(__RESOURCE_MANAGER_H__)
#define __RESOURCE_MANAGER_H__

class ResourceManager
{
public:
	enum EResources{
		kResource_Entity_Player = 0,
		kResource_Entity_Vortex,

		kResource_Background_Space,
		kResource_Background_Earth,
		kResource_Background_Satellite,
		
		kResource_Button_StartGame,

		kResource_Count
	};

private:
	CIw2DImage *m_resourcesMap[kResource_Count];

public:
	ResourceManager();
	~ResourceManager();

	void Init();
	void Destroy();
	void RegisterResource(EResources id, const char * fileName);
	CIw2DImage *GetResource(EResources id);

};

extern ResourceManager* g_pResourceManager;


#endif //__RESOURCE_MANAGER_H__