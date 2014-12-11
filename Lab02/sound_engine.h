//
//  sound_engine.h
//  Lab03
//
//  Created by Ciaran Gaffney on 05/12/2014.
//  Copyright (c) 2014 Ciaran Gaffney. All rights reserved.
//

#ifndef __Lab03__sound_engine__
#define __Lab03__sound_engine__

#include <stdio.h>
#include <SDL_mixer.h>

class SoundEngine{
public:
    Mix_Music *music;
    Mix_Chunk *ding;
    Mix_Chunk *timeout;
    
    SoundEngine();
    void play_ding();
    void pause_music();
    void resume_music();
    void play_timeout();
    
};

#endif /* defined(__Lab03__sound_engine__) */
