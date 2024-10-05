#if defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#endif

#include <csignal>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

#include "MIDIExecutor.h"
#include "filters.h"
#include "log.h"

int main() {
    console->info("Starting MIDI Router");
    // DIGITAKT ONLY
    // MIDIExecutor midiExecutor("MIDI Router", {
    //                                              {"Rev2", "Elektron Digitakt", {onlyNotesFilter}},
    //                                              {"Rev2", "Rev2", {onlyNonNotesFilter}},
    //                                              {"Elektron Digitakt", "Rev2", {midiChannelFilter(2)}},
    //                                              {"Moog Sub 37", "Elektron Digitakt", {onlyNotesFilter}},
    //                                              {"Moog Sub 37", "Moog Sub 37", {onlyNonNotesFilter}},
    //                                              {"Elektron Digitakt", "Moog Sub 37", {midiChannelFilter(1)}},
    //                                              {"COBALT8", "Elektron Digitakt", {onlyNotesFilter}},
    //                                              {"COBALT8", "COBALT8", {onlyNonNotesFilter}},
    //                                              {"Elektron Digitakt", "COBALT8", {midiChannelFilter(6)}},
    //                                          });

    // DIGITAKT AND RK8 as co-brains - April 2024
    // MIDIExecutor midiExecutor("MIDI Router", {
    //                                              {"Rev2", "Elektron Digitakt", {onlyNotesFilter}},
    //                                              {"Rev2", "X18/XR18", {onlyNonNotesFilter}},
    //                                              {"Elektron Digitakt", "X18/XR18", {midiChannelFilter(2)}},
    //                                              {"X18/XR18", "Rev2", {midiChannelFilter(2)}},
    //                                              {"Moog Sub 37", "Elektron Digitakt", {onlyNotesFilter}},
    //                                              {"Moog Sub 37", "Moog Sub 37", {onlyNonNotesFilter}},
    //                                              {"Elektron Digitakt", "X18/XR18", {midiChannelFilter(1)}},
    //                                              {"X18/XR18", "Moog Sub 37", {midiChannelFilter(1)}},
    //                                              {"COBALT8", "Elektron Digitakt", {onlyNotesFilter}},
    //                                              {"COBALT8", "COBALT8", {onlyNonNotesFilter}},
    //                                              {"Elektron Digitakt", "X18/XR18", {midiChannelFilter(6)}},
    //                                              {"X18/XR18", "COBALT8", {midiChannelFilter(6)}},
    //                                              // Clock and Transport
    //                                              {"X18/XR18", "Elektron Digitakt", {onlyClockFilter}},
    //                                              {"X18/XR18", "Elektron Digitakt", {onlyTransportFilter}},
    //                                              {"X18/XR18", "Elektron Digitakt", {midiChannelFilter(10)}},
    // });
    // RK8
    // MIDIExecutor midiExecutor("MIDI Router", {
    //                                              {"Rev2", "X18/XR18", {midiChannelFilter(2)}},
    //                                              {"Moog Sub 37", "X18/XR18", {midiChannelFilter(1)}},
    //                                              // Note that this includes clock and transport
    //                                              {"OCTATRACK UM-ONE", "X18/XR18", {}},
    //                                              {"X18/XR18", "Rev2", {noTransportFilter}},
    //                                              {"X18/XR18", "Moog Sub 37", {noTransportFilter}},
    //                                              {"X18/XR18", "Boutique JU-06A", {noTransportFilter}},
    //                                              {"X18/XR18", "TB-03", {}},
    //                                          });
    // Hardware Proto

    MIDIExecutor midiExecutor("MIDI Router", {
                                                 // RK8 is the clock and transport
                                                 // Loop CCs back to the Rev2
                                                 {"Rev2", "Rev2", {onlyNonNotesFilter}},
                                                 // Rev2 is the main keyboard for RK8
                                                 {"Rev2", "X18/XR18", {onlyNotesFilter}},
                                                 {"X18/XR18", "Rev2", {}},
                                                 // Send to Moog, which will forward to other via MIDI chain
                                                 {"X18/XR18", "Moog Sub 37", {}},
                                             });
#if defined(__APPLE__)
    // On macOS, observation can *only* be done in the main thread
    // with an active CFRunLoop.
    CFRunLoopRun();
#else
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
#endif
    return 0;
}
