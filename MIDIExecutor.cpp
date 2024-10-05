#include "MIDIExecutor.h"

#include <chrono>
#include <functional>
#include <libremidi/libremidi.hpp>
#include <thread>

#include "log.h"

MIDIExecutor::MIDIExecutor(std::string portName, std::vector<MIDIRule> const &rules) {
    this->portName = portName;
    this->rules = rules;
    libremidi::observer_configuration conf;
    conf.input_added = [&](const libremidi::input_port &port) {
        auto portName = port.device_name;
        auto midi = std::make_unique<libremidi::midi_in>(
            libremidi::input_configuration{.on_message = [this, portName](const libremidi::message &message) { this->handleMessage(message, portName); }});
        midi->open_port(port);
        this->inputs.insert({port.device_name, std::move(midi)});
        console->info("Added new MIDI input: {}", port.device_name);
    };
    conf.input_removed = [&](const libremidi::input_port &port) {
        this->inputs.erase(port.device_name);
        console->info("Removed MIDI input: {}", port.device_name);
    };
    conf.output_added = [&](const libremidi::output_port &port) {
        auto midi = std::make_unique<libremidi::midi_out>(libremidi::output_configuration{});
        midi->open_port(port);
        this->outputs.insert({port.device_name, std::move(midi)});
        console->info("Added new MIDI output: {}", port.device_name);
    };
    conf.output_removed = [&](const libremidi::output_port &port) {
        this->outputs.erase(port.device_name);
        console->info("Removed MIDI output: {}", port.device_name);
    };
    this->obs = libremidi::observer{std::move(conf)};
}

void MIDIExecutor::handleMessage(const libremidi::message &message, const std::string &portName) {
    for (auto rule : this->rules) {
        if (rule.from == portName) {
            libremidi::message messageCopy = message;
            auto filterMessage = &messageCopy;
            for (auto filter : rule.filters) {
                if (filterMessage) {
                    filterMessage = filter(filterMessage);
                }
            }
            if (filterMessage) {
                for (auto &output : this->outputs) {
                    if (rule.to == output.first) {
                        output.second->send_message(*filterMessage);
                    }
                }
            }
        }
    }
}