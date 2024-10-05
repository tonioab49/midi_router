#ifndef FILTERS_H
#define FILTERS_H

#include <libremidi/libremidi.hpp>

#include "MIDIExecutor.h"

extern libremidi::message* onlyNotesFilter(libremidi::message* message);
extern libremidi::message* onlyNonNotesFilter(libremidi::message* message);
extern libremidi::message* onlyClockFilter(libremidi::message* message);
extern libremidi::message* onlyTransportFilter(libremidi::message* message);
extern libremidi::message* noTransportFilter(libremidi::message* message);

#endif