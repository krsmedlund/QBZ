#include "qbz_clam.h"
#include "qbz_clam_pitchprofile.h"

#include <CLAM/MonoAudioFileReader.hxx>

using namespace qbz;



ClamController::ClamController(const char *networkname) 
{
	std::string reader = network.AddProcessing("AudioSource");
    
    std::string tonalAnalysis = network.AddProcessing("TonalAnalysis");
	network.ConnectPorts(reader + ".1", tonalAnalysis + ".Audio Input");
    
    std::string pitchEmitter = network.AddProcessing("PitchProfileEmitter");
    network.ConnectPorts(tonalAnalysis + ".Pitch Profile", pitchEmitter + ".Input");

    //std::string sink = network.AddProcessing("AudioSink");
	//network.ConnectPorts(reader + ".Samples Read", sink + ".1");
    
    network.SetPlayer(new CLAM::PANetworkPlayer);
	network.Start();
}

