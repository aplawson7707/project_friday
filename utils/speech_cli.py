from speak import speak

speak("Speech interface activated.")
print(f"Enter text you'd like Vex to speak and hit 'Enter'")
try:
    while True:
        cmd=input("Say: ")
        speak(cmd)
except KeyboardInterrupt:
    speak("Exiting speech interface.")