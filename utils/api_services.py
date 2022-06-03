#! /usr/bin/python

from curses import raw
from email.quoprimime import quote
import requests
import json
from geopy.geocoders import Nominatim
from utils.speak import speak
import wikipediaapi

def getCrypto():
    coin='shib'
    url = 'https://cryptfolio.com/api/currencies/'
    response = requests.get(url + coin)
    print(response.text)

def getDadJoke():
    headers = {'Accept': 'text/plain'}
    url = 'https://icanhazdadjoke.com/'
    response = requests.get(url, headers=headers)
    joke = response.text
    speak(joke)

def getQuote():
    url = 'https://api.fisenko.net/v1/quotes/en/random'
    response = requests.get(url)
    raw_quote = json.loads(response.text)
    quote = raw_quote['text']
    author = raw_quote['author']['name']
    speak(author + " once said " + quote)

def getAdvice():
    url = 'https://api.adviceslip.com/advice'
    response = requests.get(url)
    raw_advice = json.loads(response.text)
    advice = raw_advice['slip']['advice']
    speak(advice)

def getAffirmation():
    url = 'https://www.affirmations.dev/'
    response = requests.get(url)
    raw_affirmation = json.loads(response.text)
    affirmation = raw_affirmation['affirmation']
    speak(affirmation)

def getPeopleInSpace():
    url = 'http://api.open-notify.org/astros.json'
    response = requests.get(url)
    raw_response = json.loads(response.text)
    number = raw_response['number']
    people = raw_response['people']
    speak(f"There are currently {number} people in space.")
    # for i in people:
    #     print(i)

def getISSPosition():
    geolocator = Nominatim(user_agent="project_vex")
    url = 'http://api.open-notify.org/iss-now.json'
    response = requests.get(url)
    raw_response = json.loads(response.text)
    location = raw_response['iss_position']
    long = location['longitude']
    lat = location['latitude']
    location = geolocator.geocode(lat + "," + long)
    # print(location)
    if location == None:
        print(f"Lat: {lat}")
        print(f"Long: {long}")
        speak("The International Space Station is not currently orbiting above a land mass.")
    else:
        print(f"Location: {location}")
        print(f"Lat: {lat}")
        print(f"Long: {long}")
        speak(f"The International Space Station is currently orbiting somewhere above {location}")

def getSpaceEvent():
    standbyMessage = "Please standby while I retrieve the requested information."
    speak(standbyMessage)
    url = 'https://ll.thespacedevs.com/2.2.0/event/?limit=1'
    response = requests.get(url)
    raw_response = json.loads(response.text)
    raw_event = raw_response['results'][0]
    event_unencoded = raw_event['description']
    event = event_unencoded.encode('utf-8')
    speak(event)

def getRonSwansonQuote():
    url = 'http://ron-swanson-quotes.herokuapp.com/v2/quotes'
    response = requests.get(url)
    quote = response.text
    speak(quote)

def getWikipediaPage(subject: str):
    wiki_wiki = wikipediaapi.Wikipedia('en')
    page = wiki_wiki.page(subject)
    if page.exists() == True:
        summary_encoded = page.summary.encode('utf-8')
        summary_length = len(page.summary)
        speak(f"Researching {subject}. Please stand by.")
        speak(summary_encoded[0:500])
    else:
        speak(f"I apologize. I could not find any information on {subject}")
