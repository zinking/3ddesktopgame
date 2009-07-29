#include "StdAfx.h"
#include "AudioManager.h"

AudioManager* AudioManager::mgr ;

void AudioManager::initFMOD(void)
{
	if (FSOUND_Init(44100, 32, 0))					// 把声音初始化为44khz
	{
		collideEdge_sound=FSOUND_Sample_Load(5, "data/sound/CollideEdge.wav", FSOUND_LOOP_OFF, 0);
		hit_sound = FSOUND_Sample_Load(4, "data/sound/Hit.wav", FSOUND_LOOP_OFF, 0);
		
		collide_sound = FSOUND_Sample_Load(6, "data/sound/Collide.wav",  FSOUND_LOOP_OFF, 0);
		bg_sound=FSOUND_Sample_Load(7, "data/sound/CaromHall.wav", FSOUND_LOOP_NORMAL, 0);

		combo_sound = FSOUND_Sample_Load(8, "data/sound/Combo.wav", FSOUND_LOOP_OFF, 0);
		pocket_sound = FSOUND_Sample_Load(9, "data/sound/Pocket3.wav", FSOUND_LOOP_OFF, 0);
		end_sound = FSOUND_Sample_Load(10, "data/sound/End.wav", FSOUND_LOOP_OFF, 0);
	}
}

void AudioManager::freeFMOD(void)
{
	if(bg_sound) FSOUND_Sample_Free(bg_sound);
	if(collideEdge_sound) FSOUND_Sample_Free(collideEdge_sound);
	if(hit_sound) FSOUND_Sample_Free(hit_sound);
	if(collide_sound) FSOUND_Sample_Free(collide_sound);
	if(combo_sound) FSOUND_Sample_Free(combo_sound);
	if(pocket_sound) FSOUND_Sample_Free(pocket_sound);
	if(end_sound) FSOUND_Sample_Free(end_sound);
	
}

void AudioManager::playBackgroundMusic(void)
{
	if(!this->isBgMusicPlaying)
	{
		//FMUSIC_PlaySong(bg_sound);
		FSOUND_PlaySound(7,bg_sound);
		this->isBgMusicPlaying = true;
	}
}

void AudioManager::stopBackgroundMusic(void)
{
	if(this->isBgMusicPlaying)
	{
		FSOUND_StopSound(7);
		//FMUSIC_StopSong(bg_sound);
		this->isBgMusicPlaying = false;
	}
}

void AudioManager::hitBall()
{
	//if(!isBallHit)
	//{
		FSOUND_PlaySound(4,hit_sound);
		this->isBallHit = true;
	//}
}

void AudioManager::ballCollide()
{
	FSOUND_PlaySound(6,collide_sound);
}

void AudioManager::ballCollideEdge()
{
	FSOUND_PlaySound(5,collideEdge_sound);
}

void AudioManager::playCombo()
{
	FSOUND_PlaySound(8,combo_sound);
}

void AudioManager::ballIntoPocket()
{
	FSOUND_PlaySound(9,pocket_sound);
}

void AudioManager::gameEnd()
{
	if(this->isBgMusicPlaying)
		this->stopBackgroundMusic();
	FSOUND_PlaySound(10,end_sound);
}

void AudioManager::setBallHit(bool b)
{
	this->isBallHit = b;
}