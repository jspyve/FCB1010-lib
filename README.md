FCB1010-Lib

About 5 years ago, I started working on reverse engineering the Behringer FCB1010 MIDI foot controller.

My primary reasons for doing this, were to properly control my Fractal Audio AxeFxII, in a way that would be equivalent to Fractal's own MFC footr controller. But without any bells or whistles.

This endeavour started by providing a set of APIs, initialisation code, main application loop, and also formulating an approach to development hardware, that would allow from-scratch development.

That much was pretty successful. Also successful, was a degree of AxeFX control that I was looking for.

Unfortunately, the realisation that I was spending far too much time programming (which is also my day job!) and too little time playing guitar, coupled with the realisation that I really needed to buy a second FCB1010, so that I had road-ready hardware to accompany my development hardware platform, put the project on hold.

I purchased the Fractal MFC foot controller shortly afterwards - it was complete overkill for what I needed, but I got back to playing guitar.

It was always my intention to release the fruits of my labours for others to benefit from, preferably, in a more complete (from an application perspective, there's not a whole lot wrong with the APIs...) but it never happened.

Unfortunately, with the passage of considerable time, the details are a little vague. It shouldn't be too hard for any decent software engineer to figure out!

Code builds with GNU make and SDCC for 8051. I used Code::Blocks IDE for code editing, and there's a project included.

Development hardware consisted of removing the MCU from the FCB1010, and replacing it with an Atmel 8051 with an EEROM core, which could be programmed over TTL RS232 via an FTDI USB to TTL RS232 cable, via Atmel's own utility which worked with the MCU bootloader. A couple of external switches were fitted to control reset and to invoke the onboard bootloader. I can probably dig out more details as required, the datasheet for the MCU I used is in the datasheets folder of the repository.

This was far preferable to the alternative of programming and erasing EPROM ICs, and also worked more reliably than an EEPROM emulator I built to replace the onboard EPROM IC.

That's all for now, I hope you get something from this code, which I hereby donate to the public domain, for the benefit of all those who love hacking hardware!

With special thanks to Robert Turenne of practicalusage.com. Robert, you know why :)

Jon Spyve 15/03/2019

