import os
import requests
import pytest_check as check


def send_repair_request(id):

    url = f"{os.getenv('SERVER_URL')}/repair"
    headers = {'Content-Type': 'application/json'}
    json = {"id": id}
    response = requests.post(url, headers=headers, json=json)
    return response


# успешная починка
def test_repair_post_SuccessfulRepair():

    response = send_repair_request("grab_manip_001")

    assert response.status_code == 201
    assert "message" in response.json()
    assert response.json()["message"] == "Successful repair"


# Все дожны завершится успешно, так как это проверка на обработку неправильных запросов
def test_repair_post_BadData_400():

    response1 = send_repair_request(None) # не полные данные
    response2 = send_repair_request("right_leg_001") # полная ёмкость (чинить нечего)
    response3 = send_repair_request("grab_manip_001") # нет ремонтных наборов


    check.equal(response1.status_code, 400)

    check.equal(response2.status_code, 400)

    check.equal(response3.status_code, 400)


# По сути это проверка на то, все ли тесты unit-тесты работают корректно
# (если тест не проходит, можно посмотреть, что ещё исправить внутри серверных функций)
def test_repair_post_ServerError_NoErrors_5xx():

    response = send_repair_request("right_leg_001")

    assert response.status_code not in [500, 501, 503], response.json()["error"]

