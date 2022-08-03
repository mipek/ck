# Cricket-Audio

This fork of Cricket-Audio implements the following features:
- Uses CMake build system
- Provides a PulseAudio backend for Linux systems (instead of ALSA)
- Improved Android support (output floating point samples directly instead of converting to fixed point on Android L and newer)