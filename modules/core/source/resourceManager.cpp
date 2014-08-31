#include "core.h"

ResourceManager* g_pResourceManager = 0;

ResourceManager::ResourceManager(){
	uint i;
	for (i = 0; i < s_kMaxGraphics; i++){
		m_graphics[i] = 0;
	}

	for (i = 0; i < s_kMaxAtlases; i++){
		m_atlases[i] = 0;
	}

	for (i = 0; i < s_kMaxFonts; i++){
		m_fonts[i] = 0;
	}
}

ResourceManager::~ResourceManager(){
	Destroy();
}

void ResourceManager::Destroy(){
	uint i;
	for (i = 0; i < s_kMaxGraphics; i++){
		if (m_graphics[i])
			delete m_graphics[i];
		m_graphics[i] = 0;
	}

	for (i = 0; i < s_kMaxAtlases; i++){
		if (m_atlases[i])
			delete m_atlases[i];
		m_atlases[i] = 0;
	}

	for (i = 0; i < s_kMaxFonts; i++){
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

void ResourceManager::RegisterAtlas(uint textureIndex, uint atlasIndex, const char *fileName){
	std::string spritesheetName = fileName;
	spritesheetName += ".png";
	RegisterGraphic(textureIndex, spritesheetName.c_str());

	std::string coordinatesName = fileName;
	coordinatesName += ".csv";
	CSVCommands::SParsedCSV *pCoord = CSVCommands::ReadFile(coordinatesName.c_str());

	if (!pCoord || !pCoord->numRows)
		return;

	m_atlases[atlasIndex] = new CustomAtlas(GetGraphic(textureIndex));
	for (uint i = 0; i < pCoord->numRows; i++){
		int16 x = (int16)pCoord->rows[i].GetAsInt(2);
		int16 y = (int16)pCoord->rows[i].GetAsInt(3);
		int16 width = (int16)pCoord->rows[i].GetAsInt(4);
		int16 height = (int16)pCoord->rows[i].GetAsInt(5);
		m_atlases[atlasIndex]->SetFrameSize(width, height);
		m_atlases[atlasIndex]->AddFrame(x, y, width, height);
	}

	delete pCoord;
}

CustomAtlas *ResourceManager::GetAtlas(uint index){
	return m_atlases[index];
}

void ResourceManager::RegisterFont(uint index, const char * fileName){
	m_fonts[index] = Iw2DCreateFont(fileName);
}

CIw2DFont *ResourceManager::GetFont(uint index){
	return m_fonts[index];
}