#ifndef __CSV_COMMANDS_H__
#define __CSV_COMMANDS_H__

class CSVCommands{
public:
	static const uint s_kMaxCommandCols = 32;
	static const uint s_kMaxLines = 128;
	
	struct SCommand{
		EasyArray<std::string, s_kMaxCommandCols> cols;
		uint numCols;

		SCommand(){
			for (uint i = 0; i < s_kMaxCommandCols; i++)
				cols[i] = "";
			numCols = 0;
		};

		void Cleanup(){
			for (uint i = 0; i < s_kMaxCommandCols; i++)
				cols[i].clear();
			numCols = 0;
		};

		bool isValidIndex(uint index){ return index < numCols;};

		int GetAsInt(uint index){ return (isValidIndex(index) ? atoi((char *)cols[index].c_str()) : 0); };
		float GetAsFloat(uint index){ return (isValidIndex(index) ? (float)atof((char *)cols[index].c_str()) : 0.0f); };
		bool GetAsBool(uint index){ return (isValidIndex(index) ? (bool)atoi((char *)cols[index].c_str()) : false); };
		char * GetAsString(uint index){ return (isValidIndex(index) ? (char *)cols[index].c_str() : 0); };
		uint32 GetAsHash(uint index){ return (isValidIndex(index) ? IwHashString((char *)cols[index].c_str()) : 0); };
	};

	struct SParsedCSV{
		EasyArray<SCommand, s_kMaxLines> rows;
		uint numRows;

		SParsedCSV(){
			for (uint i = 0; i < s_kMaxLines; i++){
				rows[i] = SCommand();
			}
			numRows = 0;
		};

		~SParsedCSV(){
			Cleanup();
		}

		void Cleanup(){
			for (uint i = 0; i < numRows; i++){
				rows[i].Cleanup();
			}
			numRows = 0;
		};
	};

public:
	CSVCommands() {};
	static SParsedCSV *ReadFile(const char *fileName);
};

#endif //__CSV_COMMANDS_H__