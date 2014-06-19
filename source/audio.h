#if !defined(__AUDIO_H__)
#define __AUDIO_H__

class AudioSound
{
public:
    AudioSound() : m_SoundData(0), m_SoundSpec(0) {}
    ~AudioSound();
    unsigned int    m_NameHash;         // Hashed string name of sound effect
    CIwSoundData*   m_SoundData;        // Sound effect data
    CIwSoundSpec*   m_SoundSpec;        // Sound effect specification

    bool            Load(const char* filename);
};

class Audio
{
protected:
public:
    Audio();
    ~Audio();

    std::list<AudioSound*> m_Sounds;
    AudioSound* findSound(unsigned int name_hash);
	void Update();
	
	static void PlayMusic(const char* filename, bool repeat = true);
    static void StopMusic();
    
	AudioSound* PreloadSound(const char* filename);
    void PlaySound(const char* filename);
};

extern Audio*   g_pAudio;

#endif  // __AUDIO_H__


