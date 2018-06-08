#pragma once
class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)

public:
	enum CHANNELID { BGM, PLAYER, TURTLE, EFFECT, UI, MAX_CHANNEL };

private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();
	void Update();
	void PlaySound(const TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(const TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void StopAll();
	void Release();

private:
	void LoadSoundFile();

private:
	map<const TCHAR*, FMOD_SOUND*>	m_MapSound;
	FMOD_CHANNEL*					m_pChannelArr[MAX_CHANNEL];
	FMOD_SYSTEM*					m_pSystem;
};

