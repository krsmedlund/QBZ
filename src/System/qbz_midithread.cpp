#include "qbz_midithread.h"

bool done;

MidiPort::MidiPort(int portid) {
    std::cout << "Midi port detected with id " << portid << std::endl;
}

void MidiPort::registerPort(int portid, const std::string & name) {
    std::cout << "Midi port registered with id " << portid << " and name " << name << std::endl;
}
    
MidiEvent::MidiEvent(int channel, int value) : QEvent(MidiEvent::MidiType) {
    this->channel = channel;
    this->value = value;
};

MidiThread::MidiThread(QObject* parent) {
    this->parent = parent;
    try {
        this->midiin = new RtMidiIn();
    } catch (RtError &error) {
        error.printMessage();
    }
    
    unsigned int nPorts = midiin->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
    std::string portName;
    
    for (unsigned int i=0; i<nPorts; i++) {
        try {
            portName = midiin->getPortName(i);
        } catch (RtError &error) {
            error.printMessage();
        }
        std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
    }
    if (nPorts > 0) {
        midiin->openPort( 0 );
        midiin->ignoreTypes( false, false, false );
    } else {
        done = true;
    }
}

void MidiThread::run() {
    while (true) {
        if (done) return;
        double stamp = this->midiin->getMessage( &message );
        int nBytes = message.size();
        if (nBytes > 2) {
            QApplication::postEvent(parent, new MidiEvent((int)message[1], (int)message[2])); 
        }
    }
}
