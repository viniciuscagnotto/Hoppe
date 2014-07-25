#include "include.h"

ResourceManager* g_pResourceManager = 0;

ResourceManager::ResourceManager(){
	for (unsigned int i = 0; i < kResource_Count; i++){
		m_resourcesMap[i] = 0;
	}

	for (unsigned int i = 0; i < kFont_Count; i++){
		m_fontsMap[i] = 0;
	}

	Init();
}

ResourceManager::~ResourceManager(){
	Destroy();
}

void ResourceManager::Init(){
	//Resources
	RegisterResource(kResource_Entity_Player, "textures/star.png");
	RegisterResource(kResource_Entity_Vortex, "textures/vortex.png");
	RegisterResource(kResource_Entity_Asteroid, "textures/asteroid.png");
	RegisterResource(kResource_Entity_Comet, "textures/vortex.png");
	RegisterResource(kResource_Entity_Satellite, "textures/vortex.png");
	RegisterResource(kResource_Entity_BlackHole, "textures/vortex.png");
	RegisterResource(kResource_Entity_Star, "textures/vortex.png");

	RegisterResource(kResource_Background_Space, "textures/back_space.jpg");
	RegisterResource(kResource_Background_Earth, "textures/back_earth.png");
	RegisterResource(kResource_Background_Satellite, "textures/back_sate.png");
	
	RegisterResource(kResource_Button_StartGame, "textures/start_game.png");

	//Fonts
	RegisterFont(kFont_Arial_8, "fonts/arial8.gxfont");
}

void ResourceManager::Destroy(){
	for (unsigned int i = 0; i < kResource_Count; i++){
		if (m_resourcesMap[i])
			delete m_resourcesMap[i];
		m_resourcesMap[i] = 0;
	}

	for (unsigned int i = 0; i < kFont_Count; i++){
		if (m_fontsMap[i])
			delete m_fontsMap[i];
		m_fontsMap[i] = 0;
	}
}

void ResourceManager::RegisterResource(EResources id, const char * fileName){
	m_resourcesMap[id] = Iw2DCreateImage(fileName);
}

CIw2DImage *ResourceManager::GetResource(EResources id){
	return m_resourcesMap[id];
}

void ResourceManager::RegisterFont(EFonts id, const char * fileName){
	m_fontsMap[id] = Iw2DCreateFont(fileName);
}

CIw2DFont *ResourceManager::GetFont(EFonts id){
	return m_fontsMap[id];
}