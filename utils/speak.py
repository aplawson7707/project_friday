#! /usr/bin/python

import requests
import random

greetings = [
    "Hello ",
    "Good day",
    "Greetings ",
    "Good to see you ",
    "Pleasure to see you ",
    "It's very good to see you ",
    "Hello there ",
    # "How do you do "
]

random_greeting = random.randrange(len(greetings))

# if __name__ == '__main__':

def speak(message):
    message=message
    url = 'http://localhost:12101/api/text-to-speech?play=true'
    headers = {
        'accept': 'audio/wav',
        'Content-Type': 'text/plain'
    }
    requests.post(url, headers=headers, data=message)

# speak(greetings[random_greeting] + " fellow human.")
# speak("I can talk just like a person. Blah blah blah.")
# speak("The human torch was denied a bank loan.")
# speak("Your mother was a hamster and your father smelt of elderberries.")