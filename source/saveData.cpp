#include "header.h"

SaveData* g_pSaveData = 0;

SaveData::SaveData(){
	m_fileName = "savedata.txt";
	m_saveData = SSaveData();
	LoadSave();
}

SaveData::~SaveData(){

}

void SaveData::LoadSave(){
	CSVCommands::SParsedCSV *data = CSVCommands::ReadFile(m_fileName.c_str());
	if (!data){
		Save();
		return;
	}

	CSVCommands::SCommand row = data->rows[0];
	m_saveData.topScore = row.GetAsInt(0);
	m_saveData.mute = row.GetAsBool(1);
	m_saveData.tutorial = row.GetAsBool(2);
	delete data;
}

void SaveData::Save(){
	s3eFile* data = s3eFileOpen(m_fileName.c_str(), "wb");

	std::string dataText;
	dataText.reserve(100);

	std::ostringstream topScore;
	topScore << m_saveData.topScore;
	dataText.append(topScore.str());
	dataText.append(";");
	
	dataText.append(m_saveData.mute ? "1" : "0");
	dataText.append(";");

	dataText.append(m_saveData.tutorial ? "1" : "0");
	dataText.append(";");

	s3eFileWrite(dataText.c_str(), dataText.length(), 1, data);
	s3eFileClose(data);
}