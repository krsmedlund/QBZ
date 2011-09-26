//
//  light.cpp
//  
//
//  Created by kristoffer smedlund on 04/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "animator.h"

using namespace qbz;

Animator::Animator() {
    this->tweener.addListener(this);
    this->playing = false;

}

void Animator::onStart(tween::TweenerParam& param) {
    this->playing = true;
}

void Animator::onStep(tween::TweenerParam& param) {}

void Animator::onComplete(tween::TweenerParam& param) {
    this->playing = false;
}
