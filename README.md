# README #

Welcome to the rt-n56u project

This project aims to improve the rt-n56u and other supported devices on the software part, allowing power user to take full control over their hardware.
This project was created in hope to be useful, but comes without warranty or support. Installing it will probably void your warranty. 
Contributors of this project are not responsible for what happens next.

### How do I get set up? ###

* [Get the tools to build the system](https://bitbucket.org/padavan/rt-n56u/wiki/EN/HowToMakeFirmware) or [Download pre-built system image](https://bitbucket.org/padavan/rt-n56u/downloads)
* Feed the device with the system image file (Follow instructions of updating your current system)
* Perform factory reset
* Open web browser on http://my.router to configure the services

### Contribution guidelines ###

* To be completed

### My Changes ###
* 1.use -O3 build.
* 2.parallel build, build time form 7min to 4min.
* 3.remove linux-3.0.x from source.
* 4.modi /etc/profile,add some alias; add speed script.
* 5.build busybox with CONFIG_SH_MATH_SUPPORT_64, so support long math.
* 6.add app mcast to test multi cast.
* 7.build hexdump to view hex files.
* 8.add gdbserver to remote debug program.
