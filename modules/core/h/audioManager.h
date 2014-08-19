#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

class AudioManager
{
public:
	struct SAudio{
		SAudio() :m_pSoundData(0), m_pSoundSpec(0) {}
		~SAudio();
		unsigned int m_nameHash; // Hashed string name of sound effect
		CIwSoundData* m_pSoundData; // Sound effect data
		CIwSoundSpec* m_pSoundSpec; // Sound effect specification

		bool Load(const char* filename);
	};

private:
	std::list<SAudio*> m_sounds;

public:
	AudioManager();
	~AudioManager();

	SAudio* findSound(unsigned int name_hash);
	void Update();
	
	static void PlayMusic(const char* filename, bool repeat = true);
    static void StopMusic();
    
	SAudio* PreloadSound(const char* filename);
    void PlaySound(const char* filename);
};

extern AudioManager*   g_pAudio;

#endif  // __AUDIO_MANAGER_H__


