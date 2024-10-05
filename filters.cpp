#include <libremidi/libremidi.hpp>

#include "MIDIExecutor.h"

libremidi::message* onlyNotesFilter(libremidi::message* message) {
    if (message->get_message_type() == libremidi::message_type::NOTE_ON || message->get_message_type() == libremidi::message_type::NOTE_OFF) {
        return message;
    }
    return nullptr;
}

libremidi::message* onlyNonNotesFilter(libremidi::message* message) {
    if (message->get_message_type() != libremidi::message_type::NOTE_ON && message->get_message_type() != libremidi::message_type::NOTE_OFF) {
        return message;
    }
    return nullptr;
}

libremidi::message* onlyClockFilter(libremidi::message* message) {
    if (message->get_message_type() == libremidi::message_type::TIME_CLOCK) {
        return message;
    }
    return nullptr;
}

libremidi::message* onlyTransportFilter(libremidi::message* message) {
    if (message->get_message_type() == libremidi::message_type::START || message->get_message_type() == libremidi::message_type::STOP ||
        message->get_message_type() == libremidi::message_type::CONTINUE) {
        return message;
    }
    return nullptr;
}

libremidi::message* noTransportFilter(libremidi::message* message) {
    if (message->get_message_type() != libremidi::message_type::START && message->get_message_type() != libremidi::message_type::STOP &&
        message->get_message_type() != libremidi::message_type::CONTINUE) {
        return message;
    }
    return nullptr;
}