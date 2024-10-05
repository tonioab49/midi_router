//*****************************************//
//  cmidiin.cpp
//  by Gary Scavone, 2003-2004.
//
//  Simple program to test MIDI input and
//  use of a user callback function.
//
//*****************************************//

#include "utils.hpp"

#include <libremidi/libremidi.hpp>

#include <cstdlib>
#include <iostream>

int main(int argc, const char** argv)
{
  // Read command line arguments
  libremidi::examples::arguments args{argc, argv};

  libremidi::midi_in midiin{
      {
          // Set our callback function.
          .on_message = [](const libremidi::ump& message) { std::cout << message << std::endl; },

          // Don't ignore sysex, timing, or active sensing messages.
          .ignore_sysex = false,
          .ignore_timing = false,
          .ignore_sensing = false,
      },
      libremidi::midi_in_configuration_for(
          args.api)}; // Passing the second configuration argument can be skipped to use the default MIDI API

  if (!args.open_port(midiin))
    return 1;

  std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
