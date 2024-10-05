#ifndef MIDIEXECUTOR_H
#define MIDIEXECUTOR_H

#include <iostream>
#include <libremidi/libremidi.hpp>
#include <map>
#include <set>

typedef std::function<libremidi::message *(libremidi::message *)> filterFunctionType;

struct MIDIRule {
    std::string from;
    std::string to;
    std::vector<filterFunctionType> filters;
};

class MIDIExecutor {
   public:
    MIDIExecutor(std::string portName, std::vector<MIDIRule> const &rules);

   private:
    std::string portName;
    std::vector<MIDIRule> rules;
    std::map<std::string, std::unique_ptr<libremidi::midi_in>> inputs;
    std::map<std::string, std::unique_ptr<libremidi::midi_out>> outputs;
    libremidi::observer obs;

    void handleMessage(const libremidi::message &message, const std::string &portName);
};

#endif