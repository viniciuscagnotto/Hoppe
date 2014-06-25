#include "include.h"

AudioManager*  g_pAudio;

bool AudioManager::SAudio::Load(const char* filename)
{
    m_nameHash = IwHashString(filename);
    m_pSoundData = CIwSoundWAV::Create(filename, 0, 0);
	if (m_pSoundData == 0)
        return false;
    m_pSoundSpec = new CIwSoundSpec();
	m_pSoundSpec->SetData(m_pSoundData);

    return true;
}

AudioManager::SAudio::~SAudio()
{
    if (m_pSoundSpec != 0)
		delete m_pSoundSpec;
    if (m_pSoundData != 0)
		delete m_pSoundData;
}

AudioManager::AudioManager()
{
    IwSoundInit();
}

AudioManager::~AudioManager()
{
    for (std::list<SAudio*>::iterator it = m_sounds.begin(); it !=  m_sounds.end(); it++)
        delete *it;
    IwSoundTerminate();
}

AudioManager::SAudio* AudioManager::findSound(unsigned int name_hash)
{
	for (std::list<SAudio*>::iterator it = m_sounds.begin(); it != m_sounds.end(); it++)
        if ((*it)->m_nameHash == name_hash)
            return *it;
    return 0;
}

void AudioManager::Update()
{
    IwGetSoundManager()->Update();
}

void AudioManager::PlayMusic(const char* filename, bool repeat)
{
    // We only support play back of MP3 music
    if (s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_MP3))
        s3eAudioPlay(filename, repeat ? 0 : 1);
}

void AudioManager::StopMusic()
{
    s3eAudioStop();
}

AudioManager::SAudio* AudioManager::PreloadSound(const char* filename)
{
	SAudio* pSound = findSound(IwHashString(filename));
	if (pSound == 0)
    {
		pSound = new SAudio();
		if (!pSound->Load(filename))
        {
			delete pSound;
            return 0;
        }
		m_sounds.push_back(pSound);
    }

	return pSound;
}

void AudioManager::PlaySound(const char* filename)
{
    SAudio* pSound = PreloadSound(filename);
	if (pSound != 0)
		pSound->m_pSoundSpec->Play();
}