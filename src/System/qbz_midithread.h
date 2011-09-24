
#ifndef _QBZ_MIDITHREAD_H
#define _QBZ_MIDITHREAD_H

#include "qbz.h"
#include "Ext/RtMidi.h"

class MidiPort : public QObject 
{
    Q_OBJECT

public:
    MidiPort(int portid);
    void registerPort(int portid, const std::string & name);

private:
    int portid;
    std::string * name;
};


class MidiEvent : public QEvent
{
public:
    static const QEvent::Type MidiType = static_cast<QEvent::Type>(2000);
    
    MidiEvent(int channel, int value);    
    int channel;
    int value;
};


class MidiThread : public QThread 
{
    Q_OBJECT

public:
    MidiThread(QObject* parent);
    void run();
    
private:
    std::vector<unsigned char> message;
    RtMidiIn* midiin;
    QObject* parent;
    
};

#endif
