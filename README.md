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
Add your user to the docker group
```
$ sudo usermod -a -G docker $USER
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
alias cpu_temp='head -n 1 /sys/class/thermal/thermal_zone0/temp | xargs -I{} awk "BEGIN {printf \"%.2f\n\", {}/1000}"'
```

## Reload your .bashrc
```
$ source ~/.bashrc
```
<br>

# Setting up Adafruit Voice Bonnet

[Adafruit Documentation](https://learn.adafruit.com/adafruit-voice-bonnet/blinka-setup)

```
$ cd ~

$ sudo pip3 install --upgrade adafruit-python-shell

$ wget https://raw.githubusercontent.com/adafruit/Raspberry-Pi-Installer-Scripts/master/raspi-blinka.py

$ sudo python3 raspi-blinka.py

$ sudo pip3 install --upgrade adafruit-circuitpython-dotstar adafruit-circuitpython-motor adafruit-circuitpython-bmp280
```

- Plug in the Voice Bonnet and make sure the onboard switch is set to "On"
- Check if the Pi is able to read the Voice Bonnet via i2c by running:

```
sudo i2cdetect -y 1
```

- You should see an entry under 1A
- Now install the seeed-voicecard drivers

```
$ cd ~

$ git clone https://github.com/HinTak/seeed-voicecard

$ cd seeed-voicecard
```

- Check your kernel version with:

```
$ uname -r
```

- If your version is 5.10 or higher, checkout the v5.9 branch.
- If your version is 5.4 or below, checkout the v5.5 branch.

```
$ git checkout v5.9

$ sudo ./install.sh
```

- Check the card number of your seeed voicecard (on mine, it's card 3):

```
$ sudo aplay -l
```

- Set the gain levels for the new sound card (set somewhere below red)

```
$ alsamixer
```

- On the Pi taskbar, right click the speaker and set the audio output to the new sound card.
- Test the speaker output (change the number in "-c3" if that is not the correct number.)

```
$ speaker-test -c3
```

- Test the microphone (watch out for feedback if speakers are near microphone)

```
$ sudo arecord -f cd -Dhw:3 | aplay -Dhw:3
```

- Install python libraries for use with new sound card

```
$ sudo pip3 install pyaudio

$ sudo apt-get install libportaudio2
```

- You can test the Voice Bonnet with the included audiotest.py file at any time

```
$ sudo python3 audiotest.py

$ aplay audiotest.wav
```
<br>

# Setting up Rhasspy

[Rhasspy Docs](https://rhasspy.readthedocs.io/en/latest/installation/)

For discrete mode (no verbose output) run the following:
```
$ docker run -d -p 12101:12101 \
      --name rhasspy \
      --restart unless-stopped \
      -v "$HOME/.config/rhasspy/profiles:/profiles" \
      -v "/etc/localtime:/etc/localtime:ro" \
      --device /dev/snd:/dev/snd \
      rhasspy/rhasspy \
      --user-profiles /profiles \
      --profile en
```
For verbose output, run the following:
```
$ docker run -it -p 12101:12101 \
      --name rhasspy \
      --restart unless-stopped \
      -v "$HOME/.config/rhasspy/profiles:/profiles" \
      -v "/etc/localtime:/etc/localtime:ro" \
      --device /dev/snd:/dev/snd \
      rhasspy/rhasspy \
      --user-profiles /profiles \
      --profile en
```
Once the container is running, Rhasspy's web interface should be accessible at http://localhost:12101

Any changes made to your Rhasspy profile will be saved to ~/.config/rhasspy
