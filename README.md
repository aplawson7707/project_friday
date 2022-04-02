Install Raspberry Pi OS
-- Add an ssh file to the root directory of the memory card
-- Add a wpa_supplicant.conf file to the root directory of the memory card
-- Plug it into a monitor and start it up - follow setup wizard.

Open terminal and run the Argon case script
```
$ curl https://download.argon40.com/argon1.sh | bash
```

Download Docker
```
$ curl -sSL https://get.docker.com | sh
```

Download Rhasspy container
```
$ docker pull rhasspy/rhasspy
```

Install VS Code
```
$ sudo apt install code
```

Install Virtualenvwrapper (optional)
```
$ mkdir ~/.virtualenvs
$ mkdir ~/projects
```
-- Find the virtualenv and Python 3 binaries (probably /usr/bin/python3 and /usr/local/bin/virtualenv) and note them for the following step.

Update ~/.bashrc with the following:
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

Reload your .bashrc
```
$ source ~/.bashrc
```
