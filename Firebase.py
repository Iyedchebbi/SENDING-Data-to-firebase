import serial
import requests
import json

firebase_url = "https://tempdat-2770b-default-rtdb.firebaseio.com/Temperature.json"
api_key = "belHkxFfbmI7EeTLUwvHjiECzB3WfsYYBD43W44n"

port = 'COM3'  
baud_rate = 9600


ser = serial.Serial(port, baud_rate)

def envoyer_temperature_firebase(temperature):
    data = {
        "temperature": temperature
    }

    url = f"{firebase_url}?auth={api_key}"

    response = requests.post(url, data=json.dumps(data))

    if response.status_code == 200:
        print("Données envoyées avec succès à Firebase!")
    else:
        print(f"Erreur lors de l'envoi des données à Firebase. Code d'erreur : {response.status_code}")
        print(response.text)

try:
    while True:
        data = ser.readline().decode().strip()

        if data.startswith("Temperature:"):
            temperature_str = data.split("Temperature:")[1].split("°C")[0].strip()

            try:
                temperature = float(temperature_str)
                print(f"Température lue depuis Arduino : {temperature} °C")
                envoyer_temperature_firebase(temperature)
            except ValueError as e:
                print(f"Erreur de conversion en float : {e}")

except KeyboardInterrupt:
    ser.close()
    print("Connexion série fermée.")
