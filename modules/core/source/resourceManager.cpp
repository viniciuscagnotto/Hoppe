#include "core.h"

ResourceManager* g_pResourceManager = 0;

ResourceManager::ResourceManager(){
	for (unsigned int i = 0; i < s_kMaxGraphics; i++){
		m_graphics[i] = 0;
	}

	for (unsigned int i = 0; i < s_kMaxFonts; i++){
		m_fonts[i] = 0;
	}
}

ResourceManager::~ResourceManager(){
	Destroy();
}

void ResourceManager::Destroy(){
	for (unsigned int i = 0; i < s_kMaxGraphics; i++){
		if (m_graphics[i])
			delete m_graphics[i];
		m_graphics[i] = 0;
	}

	for (unsigned int i = 0; i < s_kMaxFonts; i++){
		if (m_fonts[i])
			delete m_fonts[i];
		m_fonts[i] = 0;
	}
}

void ResourceManager::RegisterGraphic(uint index, const char * fileName){
	m_graphics[index] = Iw2DCreateImage(fileName);
}

CIw2DImage *ResourceManager::GetGraphic(uint index){
	return m_graphics[index];
}

void ResourceManager::RegisterFont(uint index, const char * fileName){
	m_fonts[index] = Iw2DCreateFont(fileName);
}

CIw2DFont *ResourceManager::GetFont(uint index){
	return m_fonts[index];
}