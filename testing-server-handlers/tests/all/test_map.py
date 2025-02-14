import os
import requests
import pytest_check as check


def test_get_map_200():

    server_url = os.getenv("SERVER_URL")
    path = f"{server_url}/map"

    response = requests.get(url=path)

    assert response.status_code == 200

    json = response.json()

    assert "map" in json

    assert all(item in ["Empty", "Enemy"] for item in json["map"])

def test_get_map_500():
    
    server_url = os.getenv("SERVER_URL")
    path = f"{server_url}/map"

    response = requests.get(url=path)

    assert response.status_code not in [500, 501, 503], response.json()["error"]

