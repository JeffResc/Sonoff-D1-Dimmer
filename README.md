# Sonoff-D1-Dimmer
This project contains three subprojects for different use cases. Please read them below in order to tell which project best fits your use case.

# Please Read!
There is now a [native ESPHome compontent](https://esphome.io/components/light/sonoff_d1.html) for the Sonoff D1 Dimmer. It is recommended to use the native compontent rather than this custom implementation.

---

# Note About Project
This project is still heavily a work-in-progress. If you find an problem, please [open a new issue](https://github.com/JeffResc/Sonoff-D1-Dimmer/issues/new) and ensure to include the ESPHome logs as well.

# Note About Ghost Switching/Dimming
Many users both at the [Sonoff Forums](https://support.itead.cc/support/discussions/topics/11000030765) and [Tasmota Project](https://github.com/arendst/Tasmota/issues/7598) have mentioned issues of ghost switching/dimming. But even on the stock firmware, [this is an issue](https://github.com/arendst/Tasmota/issues/7598#issuecomment-691650308). It is outside of my control to fix this issue, but I believe the ghost dimming is coming from the onboard RF controller so theoretically, if you remove it or Solder the RF directly to the ESP8285, it may fix your issues, but I have not yet verified this.

# Other Sources
I have a complete write-up guide for this project [on my website](https://jeffresc.dev/blog/2020-10-10). Please check it out if you are confused or looking for more information.

## No RF
If you do not need RF support, please use `d1_dimmer.yaml` and `d1_dimmer.h`.

## Default RF
If you would like default RF support, please use `d1_dimmer.yaml` and `d1_dimmer_rf.h`.

## Soldered RF
If you have soldered RF to GPIO4, please use `d1_dimmer_rf.yaml` and `d1_dimmer.h`. To learn how or why to solder your RF to GPIO4, [check here](https://jeffresc.dev/blog/2020-10-10#soldering-for-433mhz-remote).
