#! /usr/bin/python3

from typing import Optional
import docker
from speak import speak

def is_container_running(container_name: str) -> Optional[bool]:
    """ Verify the status of a container by name
    
    :param container_name: the name of the container
    :return: boolean or None
    """
    RUNNING = "running"
    docker_client = docker.from_env()

    try:
        container = docker_client.containers.get(container_name)
    except docker.errors.NotFound as exc:
        print(f"Double check that container name!\n{exc.explanation}")
    else:
        container_state = container.attrs["State"]
        return container_state["Status"] == RUNNING

if __name__ == "__main__":
    container_name = "rhasspy"
    result = is_container_running(container_name)
    print(result)
    if result == True:
        speak("Vocalization protocol is running and active")
        