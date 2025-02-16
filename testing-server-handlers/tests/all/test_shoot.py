import os
import requests
import pytest_check as check


def send_shoot_request(x, y):

    url = f"{os.getenv('SERVER_URL')}/shoot"
    headers = {'Content-Type': 'application/json'}
    json = {"x": x, "y": y}
    response = requests.post(url, headers=headers, json=json)
    return response


# успешно, враг убит
def test_shoot_post201():

    response = send_shoot_request(2, 3)

    assert response.status_code == 201
    assert "message" in response.json()
    assert response.json()["message"] == "Shot Enemy killed"


# успешно врага не было
def test_shoot_post200():

    response = send_shoot_request(2, 3)

    assert response.status_code == 200
    assert "message" in response.json()
    assert response.json()["message"] == "Shot"


# Все дожны завершится успешно, так как это проверка на обработку неправильных запросов
def test_shoot_post4xx():

    response1_1 = send_shoot_request(0, None) # не полные данные
    response1_2 = send_shoot_request(None, 0) # не полные данные
    response2 = send_shoot_request(2, 2) # взгляд не в ту сторону
    response3 = send_shoot_request(10, 2) # не в видимом поле


    check.equal(response1_1.status_code, 400)
    check.equal(response1_2.status_code, 400)

    check.equal(response2.status_code, 400)

    check.equal(response3.status_code, 400)


# По сути это проверка на то, все ли тесты unit-тесты работают корректно
# (если тест не проходит, можно посмотреть, что ещё исправить внутри серверных функций)
def test_shoot_post500():

    response = send_shoot_request(2, 3)

    assert response.status_code not in [500, 501, 503], response.json()["error"]


def test_shoot_post400():

    response = send_shoot_request(2, 3)

    assert response.status_code == 400 and response.json()["error"] == "no cartridges"

