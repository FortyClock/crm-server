import requests
import pytest_check as check


def test_get_state():

    url = "http://localhost:65000/state"
    response = requests.get(url)

    check.equal(response.status_code, 200)