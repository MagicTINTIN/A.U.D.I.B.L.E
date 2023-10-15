# A.U.D.I.B.L.E
**A**udio **U**ploader & **D**ownloader via **I**nternet **B**etween **L**AN **E**quipments 
> *Pour écouter le temps de tempêtes sur un autre ordinateur*

![A.U.D.I.B.L.E logo](./sources/images/logo.png)<br>

# Installation
## Requirements
The librairies needed are : Boost and PulseAudio if it is not yet installed<br>
- Linux
  - Debian/Ubuntu
```bash
sudo apt install libboost-all-dev pulseaudio
```
  - Arch Linux
```bash
sudo pacman -Sy boost pulseaudio
```
## Build A.U.D.I.B.L.E
Then to compile the program, use the following 
```bash
git clone https://github.com/MagicTINTIN/A.U.D.I.B.L.E
cd A.U.D.I.B.L.E
./cmake.sh --release
```

# Start and use A.U.D.I.B.L.E
To start a server to receive the sounds from another computer
```bash
build/Audible -s <port>
```
To start a client to send the computer sound to a server
```bash
build/Audible <server ip adress> <port>
```
And that's it !<br>
You should now be able to listen the sound output of your other computer.<br>
You should also be able to modify the input and output levels in your settings, the application name is A.U.D.I.B.L.E (client or server).<br>
## Error : pa_simple_new() failed: No such entity
If you have this error, you might check that the source exists.<br>
To do that, follow the instructions in `./source.cfg`