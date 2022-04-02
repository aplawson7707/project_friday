# Project Friday

> A home-built robotic assistant project based on Raspberry Pi, Arduino, Python, and Rhasspy (an open-source virtual assistant framework).

Project Friday (named by my children after their beloved Tony Stark's artifically intelligent assistant) was started as Project Vex back in 2020. Project Vex contained three major components - what I called the Cerebral Cortex (a Raspberry Pi 4), the Motor Cortex (an Arduino Mega), and the Sensory Cortex (a series of sensors and Arduino Nano boards connected to the Motor Cortex). A head and neck prototype was designed, 3D printed, and assembled. All three Cortex components were contained within the head of the robot (Vex) and development began.

Unfortunately, the development cycle and subsequent project structure were piecemeal, inconsistent, and generally problematic. Additionally, the Operating System and configuration of the Cerebral Cortex were heavily modified and poorly documented. This eventually led me to the decision to start again from scratch - but to document the build process more extensively this time. It is my hope that Project Friday will not only be much easier to build from scratch if I ever need to start over again, but will also be documented well enough that anybody reading this would be able to build a Friday unit of their own.

<hr>
<br>

# Parts Needed:

<br>

- [Raspberry Pi 4 (8gb)](https://www.amazon.com/CanaKit-Raspberry-Basic-Kit-8GB/dp/B08DJ9MLHV/ref=sr_1_1?keywords=raspberry+pi+4+canakit&qid=1648933415&sr=8-1)
- [Argon One Pi 4 V2 Case](https://www.amazon.com/Argon-Raspberry-Aluminum-Heatsink-Supports/dp/B07WP8WC3V/ref=sr_1_3?keywords=argon+one+pi+4+v2&qid=1648933352&sprefix=argon+one+pi+4+v2%2Caps%2C597&sr=8-3)
- [Powered Speakers](https://www.amazon.com/Logitech-Multi-Device-Stereo-Speaker/dp/B074KJ6JQW/ref=sr_1_4?keywords=logitech+bluetooth+speakers&qid=1648933309&sr=8-4)
- [Adafruit Voice Bonnet](https://www.adafruit.com/product/4757)
- [Raspberry Pi Camera (Arducam Noir 5mp)](https://www.amazon.com/Arducam-Camera-Raspberry-Infrared-Sensitive/dp/B07SPRQMCW/ref=sr_1_3?crid=1CMMCFFTVCG43&keywords=arducam+noir+camera&qid=1648933589&sprefix=arducam+noir+camera%2Caps%2C239&sr=8-3)

<br>

# Setup:

<br>

## Install Raspberry Pi OS
- Add an ssh file to the root directory of the memory card
- Add a wpa_supplicant.conf file to the root directory of the memory card
- Plug it into a monitor and start it up - follow setup wizard.

<br>

## Open terminal and run the Argon case script
```
$ curl https://download.argon40.com/argon1.sh | bash
```

<br>

## Download Docker
```
$ curl -sSL https://get.docker.com | sh
```

<br>

## Download Rhasspy container
```
$ docker pull rhasspy/rhasspy
```

<br>

## Install VS Code
```
$ sudo apt install code
```

<br>

## Install Virtualenvwrapper (optional)
```
$ mkdir ~/.virtualenvs
$ mkdir ~/projects
```

<br>

>Note: Find the virtualenv and Python 3 binaries (probably /usr/bin/python3 and /usr/local/bin/virtualenv) and note them for the following step.

<br>

## Update ~/.bashrc with the following:
```
# Virtualenvwrapper things
export WORKON_HOME=$HOME/.virtualenvs
export PROJECT_HOME=$HOME/projects
export VIRTUALENVWRAPPER_PYTHON=/usr/bin/python3
export VIRTUALENVWRAPPER_VIRTUALENV=/usr/local/bin/virtualenv
source /usr/local/bin/virtualenvwrapper.sh

# My own alias list
alias bashconfig='sudo nano ~/.bashrc'
alias reload='source ~/.bashrc'
```

## Reload your .bashrc
```
$ source ~/.bashrc
```
