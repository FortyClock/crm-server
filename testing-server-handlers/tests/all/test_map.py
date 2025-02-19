import os
import requests
import pytest_check as check


def send_map_request():

    url = f"{os.getenv('SERVER_URL')}/map"
    headers = {'Content-Type': 'application/json'}
    response = requests.get(url, headers=headers)
    return response


def test_map_get_Success_and_Not404_And500():

    data = {
		"items" : [
			[
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty"
			],
			[
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty"
			],
			[
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty"
			],
			[
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty"
			],
			[
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty"
			],
			[
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty"
			],
			[
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty"
			],
			[
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty"
			],
			[
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty"
			],
			[
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty",
				"Empty"
			]
		],
		"size" : 10
	}


    response = send_map_request()

    assert response.status_code != 404
    assert response.status_code != 500
    assert response.status_code == 200
    assert "status" in response.json() and response.json()["status"] == "success"
    assert "data" in response.json() and response.jaon()["data"] == data






