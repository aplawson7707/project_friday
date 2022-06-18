import os
from dotenv import load_dotenv
import requests
import json

load_dotenv()

TOKEN = os.getenv('HASS_TOKEN')
baseurl = os.getenv('HASS_URL')

headers = {
    "Authorization": "Bearer " + TOKEN,
    "content-type": "application/json",
}

def getAPIStatus():
    url = baseurl

    try:
        r = requests.get(url, headers=headers)
        r.raise_for_status()
    except requests.exceptions.HTTPError as err:
        raise SystemExit(err)

    print(r.text)

def getCameraSnapshots():
    cameras = [
        "camera.espcam",
        "camera.espcam2",
        "camera.living_room_camera",
    ]

    for camera in cameras:
        url = baseurl + "camera_proxy/" + camera
        response = requests.get(url, headers=headers)

        with open(camera + ".jpg", "wb") as f:
            f.write(response.content)
        print(f"{camera}: {response.status_code}")

def getEntityStates():
    entities = [
        "camera.espcam",
        "camera.espcam2",
        "camera.living_room_camera",
    ]

    for entity in entities:
        url = baseurl + "states/" + entity
        response = requests.get(url, headers=headers)
        json_object = json.loads(response.text)
        json_formatted_str = json.dumps(json_object, indent=2)

        print(json_formatted_str)

def postEvent(event_id:str):
    event = f"rhasspy_{event_id}"
    url = baseurl + "events/" + event

    try:
        r = requests.post(url, headers=headers)
        r.raise_for_status()
    except requests.exceptions.HTTPError as err:
        raise SystemExit(err)