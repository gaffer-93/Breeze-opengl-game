//
//  sound_engine.cpp
//  Lab03
//
//  Created by Ciaran Gaffney on 05/12/2014.
//  Copyright (c) 2014 Ciaran Gaffney. All rights reserved.
//

#include "sound_engine.h"

SoundEngine::SoundEngine(){
    
    //Initialize SDL_mixer
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    
    music = Mix_LoadMUS("bgm.wav");
    ding = Mix_LoadWAV("ding.wav");
    timeout = Mix_LoadWAV("countdown.wav");
    if(!ding) {
        printf("Mix_LoadMUS(\"ding.wav\"): %s\n", Mix_GetError());
    }
    if(!music) {
        printf("Mix_LoadMUS(\"bgm.wav\"): %s\n", Mix_GetError());
    }
    
    Mix_VolumeMusic(50);
    Mix_PlayMusic( music, -1 );
    
}

void SoundEngine::play_ding(){
    Mix_PlayChannel( -1, ding, 0 );
}

void SoundEngine::play_timeout(){
    Mix_PlayChannel( -1, timeout, 0 );
}

void SoundEngine::pause_music(){
    
    if(Mix_PausedMusic() != 1){
        Mix_PauseMusic();
    }
    
}

void SoundEngine::resume_music(){
    
    if(Mix_PausedMusic() == 1){
        Mix_ResumeMusic();
    }
}


