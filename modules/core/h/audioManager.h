#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

class AudioManager
{
public:
	struct SAudio{
		SAudio() :pSoundData(0), pSoundSpec(0) {}
		~SAudio();
		unsigned int nameHash; // Hashed string name of sound effect
		CIwSoundData* pSoundData; // Sound effect data
		CIwSoundSpec* pSoundSpec; // Sound effect specification

		bool Load(const char* filename);
	};

private:
	std::list<SAudio*> m_sounds;
	bool m_isMute;

public:
	AudioManager();
	~AudioManager();

	SAudio* FindSound(unsigned int nameHash);
	void Update();
	
	static void PlayMusic(const char* filename, bool repeat = true);
    static void StopMusic();
    
	SAudio* PreloadSound(const char* filename);
    void PlaySound(const char* filename);

	void SetMute(bool mute){ m_isMute = mute; };
	bool IsMute(){ return m_isMute; };
};

extern AudioManager* g_pAudio;

#endif  // __AUDIO_MANAGER_H__


