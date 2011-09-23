//
//  qbz_clam_pitchprofile.h
//  
//
//  Created by kristoffer smedlund on 08/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <CLAM/InPort.hxx>
#include <CLAM/OutPort.hxx>
#include <CLAM/Processing.hxx>
#include <CLAM/TonalAnalysis.hxx>

extern float maxTonalData;
extern float tonalData[12];

namespace qbz {

class PitchProfileEmitter : public CLAM::Processing { 
    CLAM::InPort< std::vector<CLAM::TData> > mIn;

public:
    const char* GetClassName() const { 
        return "PitchProfileEmitter"; 
    }
    
    PitchProfileEmitter(const Config& config = Config()) : mIn("Input", this) {
        std::cout << "instancing profile emitter\n";
        Configure( config );
    }
    
    bool Do() {
        bool result = Do(mIn.GetData());
        mIn.Consume();
        return result;
    }
    
    bool Do(const std::vector<CLAM::TData> & inData)
    {
        static const char * roots[] = {
            "G",
            "G#",
            "A",
            "A#",
            "B",
            "C",
            "C#",
            "D",
            "D#",
            "E",
            "F",
            "F#",
        };
        
        float max = 0.0f;
        int max_i = 0;
        for (int i=0; i<12; i++) {
            if (inData[i] > max) {
                tonalData[i] = inData[i];
                max += inData[i];
                max_i = i;
            }
        }
        maxTonalData = max;
        std::cout << "max " << max << std::endl;
    }
};

}