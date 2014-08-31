#include "core.h"

CSVCommands::SParsedCSV *CSVCommands::ReadFile(const char *fileName){
	SParsedCSV *parsed = new SParsedCSV();

	s3eFile *pFile = s3eFileOpen(fileName, "rb");
	if (pFile){
		int32 fileSize = s3eFileGetSize(pFile);
		char* data = (char*)s3eMallocBase(fileSize + 1);
		memset(data, 0, fileSize);

		if (s3eFileRead(&data[0], fileSize, 1, pFile) == 1)
		{
			data[fileSize] = '\0';
			std::string dataString = data;
				
			std::string row;
			std::stringstream dataStream(dataString);
			while (getline(dataStream, row, '\n')){
				SCommand *pCommand = &parsed->rows[parsed->numRows++];
				
				std::string col;
				std::stringstream rowStream(row);
				while (getline(rowStream, col, ';')){
					pCommand->cols[pCommand->numCols++] = col;
				}
			}
		}

		s3eFreeBase((void*)data);
		s3eFileClose(pFile);
	}

	return parsed;
}