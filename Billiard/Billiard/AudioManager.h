#pragma once

#include "Fmod.h"			// ÒôÆµ¿âÍ·ÎÄ¼þ
#pragma comment(lib, "fmodvc.lib")

class AudioManager
{
public:
	static AudioManager* getSingleton()
	{
		if(mgr == 0)
			mgr = new AudioManager();
		return mgr;
	}

protected:
	AudioManager(void)
		:isBgMusicPlaying(false),
		isBallHit(false)
	{
		initFMOD();
	}
	
	virtual ~AudioManager(void)
	{
		freeFMOD();
	}

	static AudioManager* mgr ;

public:
	//FMUSIC_MODULE *bg_sound;
	FSOUND_SAMPLE *bg_sound;
	FSOUND_SAMPLE *hit_sound;
	FSOUND_SAMPLE *collide_sound;
	FSOUND_SAMPLE *collideEdge_sound;
	FSOUND_SAMPLE *combo_sound;
	FSOUND_SAMPLE *pocket_sound;
	FSOUND_SAMPLE *end_sound;

	bool isBgMusicPlaying;
	bool isBallHit;

	void initFMOD(void);
	
	void freeFMOD(void);
	void playBackgroundMusic(void);
	void stopBackgroundMusic(void);
	void hitBall();
	void ballCollide();
	void ballCollideEdge();
	void playCombo();
	void ballIntoPocket();
	void gameEnd();

	void setBallHit(bool b);
};
