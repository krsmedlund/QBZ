//
//  qbz_clam_pitchprofile.cpp
//  
//
//  Created by kristoffer smedlund on 08/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "qbz_clam_pitchprofile.h"
#include <CLAM/ProcessingFactory.hxx>

static const char * metadata[] = {
	"key", "PitchProfileEmitter",
	"category", "QBZ signal emitter",
	0
};
static CLAM::FactoryRegistrator<CLAM::ProcessingFactory, qbz::PitchProfileEmitter> registrator(metadata);