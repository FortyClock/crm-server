import requests
import pytest_check as check


url = "http://localhost:65000/"


def test_post_position():

    url = url + "/position"

    params_variations = {
        "v1": {
            "x": 3,
            "y": 5
        },
        "v2": {
            "x": 3,
            "y": 6
        },
        "v3": {
            "x": 2,
            "y": 6
        },
        "v4": {
            "x": 2,
            "y": 7
        }
    }


    check.not_equal(
        requests.post(
            url=url,
            params=params_variations["v1"]
        ).status_code,
        404
    )

    check.equal(
        requests.post(
            url=url,
            params=params_variations["v2"]
        ).status_code,
        200
    )

    check.equal(
        requests.get(
            url=url,
            params=params_variations["v3"]
        ).status_code,
        405
    )

    check.not_equal(
        requests.get(
            url=url,
            params=params_variations["v4"]
        ).status_code,
        500
    )
    