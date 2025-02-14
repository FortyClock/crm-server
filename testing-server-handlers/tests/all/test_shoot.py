import os
import requests
import pytest_check as check


# Проверка со 100% успешными данными
def test_shoot_post200():

    server_url = os.getenv("SERVER_URL")
    path = f"{server_url}/shoot"

    headers = {'Content-Type': 'application/json'}
    dataSuccess = {
        "x": 2,
        "y": 3
    }

    assert requests.post(url=path, headers=headers, json=dataSuccess).status_code == 200


# Все дожны завершится успешно, так как это проверка на обработку неправильных запросов
def test_shoot_post4xx():

    server_url = os.getenv("SERVER_URL")
    path = f"{server_url}/shoot"

    headers = {'Content-Type': 'application/json'}
    dataError_Empty_Parm1 = {
        "x": 0,
    }
    dataError_Empty_Parm2 = {
        "y": 0,
    }
    dataError_OtherFace_to1 = {
        "x": 2,
        "y": 2
    }
    dataError_OtherFace_to2 = {
        "x": 3,
        "y": 2
    }
    dataError_OtherFace_to3 = {
        "x": 4,
        "y": 2
    }
    dataError_OtherFace_to4 = {
        "x": 4,
        "y": 3
    }
    dataError_OtherFace_to5 = {
        "x": 4,
        "y": 4
    }
    dataError_OtherFace_to6 = {
        "x": 3,
        "y": 4
    }
    dataError_OtherFace_to7 = {
        "x": 2,
        "y": 4
    }
    dataError_NotNear = {
        "x": 6,
        "y": 7
    }

    assert requests.post(url=path, headers=headers, json={"x": 2, "y": 3}).status_code != 404

    check.equal(requests.post(url=path, headers=headers, 
                              json=dataError_Empty_Parm1).status_code, 400)
    check.equal(requests.post(url=path, headers=headers, 
                              json=dataError_Empty_Parm2).status_code, 400)
    

    check.equal(requests.post(url=path, headers=headers, 
                              json=dataError_OtherFace_to1).status_code, 400)
    check.equal(requests.post(url=path, headers=headers, 
                              json=dataError_OtherFace_to2).status_code, 400)
    check.equal(requests.post(url=path, headers=headers, 
                              json=dataError_OtherFace_to3).status_code, 400)
    check.equal(requests.post(url=path, headers=headers, 
                              json=dataError_OtherFace_to4).status_code, 400)
    check.equal(requests.post(url=path, headers=headers, 
                              json=dataError_OtherFace_to5).status_code, 400)
    check.equal(requests.post(url=path, headers=headers, 
                              json=dataError_OtherFace_to6).status_code, 400)
    check.equal(requests.post(url=path, headers=headers, 
                              json=dataError_OtherFace_to7).status_code, 400)
    

    check.equal(requests.post(url=path, headers=headers, 
                              json=dataError_NotNear).status_code, 400)


# По сути это проверка на то, все ли тесты unit-тесты работают корректно
# (если тест не проходит, можно посмотреть, что ещё исправить внутри серверных функций)
def test_shoot_post500():

    server_url = os.getenv("SERVER_URL")
    path = f"{server_url}/shoot"

    headers = {'Content-Type': 'application/json'}

    dataSuccess = {
        "x": 2,
        "y": 3
    }

    response = requests.post(url=path, headers=headers, data=dataSuccess)

    assert response.status_code not in [500, 501, 503], response.json()["error"]

