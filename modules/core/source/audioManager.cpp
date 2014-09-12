#include "core.h"

AudioManager* g_pAudio = 0;

bool AudioManager::SAudio::Load(const char* filename)
{
    nameHash = IwHashString(filename);
    pSoundData = CIwSoundWAV::Create(filename, 0, 0);
	if (pSoundData == 0)
        return false;
    pSoundSpec = new CIwSoundSpec();
	pSoundSpec->SetData(pSoundData);

    return true;
}

AudioManager::SAudio::~SAudio()
{
    if (pSoundSpec != 0)
		delete pSoundSpec;
    if (pSoundData != 0)
		delete pSoundData;
}

AudioManager::AudioManager()
{
    IwSoundInit();
	m_isMute = false;
}

AudioManager::~AudioManager()
{
    for (std::list<SAudio*>::iterator it = m_sounds.begin(); it !=  m_sounds.end(); it++)
        delete *it;
    IwSoundTerminate();
}

AudioManager::SAudio* AudioManager::FindSound(unsigned int nameHash)
{
	for (std::list<SAudio*>::iterator it = m_sounds.begin(); it != m_sounds.end(); it++)
		if ((*it)->nameHash == nameHash)
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
	SAudio* pSound = FindSound(IwHashString(filename));
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
	if (m_isMute)
		return;

    SAudio* pSound = PreloadSound(filename);
	if (pSound != 0)
		pSound->pSoundSpec->Play();
}