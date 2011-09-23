/*
 *  qbz_baseapp.h
 *  QBZ
 *
 *  Created by kristoffer smedlund on 10/30/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _QBZ_ANIMATOR_H
#define _QBZ_ANIMATOR_H

#include "CppTweener.h"
#include "qbz.h"

extern QTime* global_time;

namespace qbz {

    enum {
        LINEAR,
        SINE,
        QUINT,
        QUART,
        QUAD,
        EXPO,
        ELASTIC,
        CUBIC,
        CIRC,
        BOUNCE,
        BACK
        
    };

    enum {
        EASE_IN,
        EASE_OUT,
        EASE_IN_OUT
    };
    
    enum {
        INTERPOLATE_FOREVER,
        INTERPOLATE_BETWEEN,
        INTERPOLATE_ONCE,
    };


    class Animation : public tween::TweenerParam {
    public:
        Animation(float time, 
                  short transition=qbz::EXPO, 
                  short equation=qbz::EASE_OUT, 
                  short interpolation=qbz::INTERPOLATE_ONCE, 
                  float delay=0
                  ) 
            : tween::TweenerParam(time, transition, equation, delay) 
        {
            is_active = true;
        };
        
        void add_animation_value(float* var, float final_value) 
        {
            this->addProperty(var, final_value);
        };
        
        void set_repeat(int repeat) 
        {
            this->setRepeatWithReverse(repeat, false);
        };
        
        void set_repeat_reverse(int repeat) 
        {
            this->setRepeatWithReverse(repeat, true);
        };
        
        bool is_active;
    };
    
    
    class Animator : public tween::TweenerListener {
	public:
        Animator();
        
        short interpolate;
        tween::Tweener tweener;
        
        bool playing;
        
        void update() 
        { 
            this->tweener.step(global_time->elapsed()); 
        };
        
        void onStart(tween::TweenerParam& param);
        void onStep(tween::TweenerParam& param);
        void onComplete(tween::TweenerParam& param);
        
        qbz::Animation* create_animation(float time, short transition=qbz::EXPO, short equation=qbz::EASE_OUT, short interpolation=qbz::INTERPOLATE_ONCE, float delay=0) 
        {
            this->interpolate = interpolation;
            qbz::Animation* anim = new qbz::Animation(time, transition, equation, delay);
            anim->setRepeatWithReverse(1, true);
            return anim;
        };
        
        void play_animation(qbz::Animation anim) 
        {
            this->tweener.addTween(anim);
        };
        
        void restart_animation(qbz::Animation anim) 
        {
            this->tweener.addTween(anim);
        };

    };
};

#endif