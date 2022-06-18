#!/usr/bin/env python3

import sys
import json
import random
import datetime
from hassio import *

def speech(text):
    global o
    o["speech"] = {"text": text}

# Get JSON from stdin and load into python dict
o = json.loads(sys.stdin.read())

intent = o["intent"]["name"]

greetings = [
    "Hi",
    "Hello",
    "Hello there",
]

morning_greetings = [
    "Good morning sir",
    "Good morning to you as well",
    "Good to see you sir",
]

if intent == "GetTime":
    now = datetime.datetime.now()
    speech("It's %s %d %s." % (now.strftime('%H'), now.minute, now.strftime('%p')))

elif intent == "Greeting":
    speech(random.choice(greetings))

elif intent == "GuessWhat":
    speech("Chicken Butt")

elif intent == "KnockKnock":
    speech("Nobody's home")

elif intent == "GoodMorning":
    speech(random.choice(morning_greetings))

elif intent == "GoodNight":
    speech("Ive received the Good Night Intent")
    postEvent("GoodNight")

elif intent == "DorfusTVPlay":
    postEvent("DorfusTVPlay")

elif intent == "DorfusTVPause":
    postEvent("DorfusTVPause")

# Convert dict to JSON and print to stdout
print(json.dumps(o))
