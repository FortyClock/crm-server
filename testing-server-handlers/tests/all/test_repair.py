import os
import requests
import pytest_check as check

# Уже стреляли (1 раз при тестах выстрелов) => можно
# починить "Оружие" и "Орудийный манипулятор"


# Должен быть ответ об успешной починке (починка требовалась) + 10% прочности
def test_repair_post201():

    server_url = os.getenv("SERVER_URL")
    path = f"{server_url}/repair"

    headers = {'Content-Type': 'application/json'}

    dataSuccess = {
        "id": "weapon_001" # сейчас у него 90%
    }

    assert requests.post(url=path, headers=headers, data=dataSuccess).status_code == 201


# Успешное выполнение (починка не требовалась)
def test_repair_post200():

    server_url = os.getenv("SERVER_URL")
    path = f"{server_url}/repair"

    headers = {'Content-Type': 'application/json'}

    dataSuccess = {
        "id": "gun_manip" # сейчас у него 100%
    }

    assert requests.post(url=path, headers=headers, data=dataSuccess).status_code == 200


# По сути это проверка на то, все ли тесты unit-тесты работают корректно
# (если тест не проходит, можно посмотреть, что ещё исправить внутри серверных функций)
def test_shoot_post500():

    server_url = os.getenv("SERVER_URL")
    path = f"{server_url}/repair"

    headers = {'Content-Type': 'application/json'}

    dataSuccess = {
        "id": "left_leg"
    }

    response = requests.post(url=path, headers=headers, data=dataSuccess)

    assert response.status_code not in [500, 501, 503], response.json()["error"]


# Все дожны завершится успешно, так как это проверка на обработку неправильных запросов
def test_repair_post4xx():

    server_url = os.getenv("SERVER_URL")
    path = f"{server_url}/repair"

    headers = {'Content-Type': 'application/json'}


    data_id_does_not_exist = {
        "id": "sdfsd" # предмет не существует
    }

    data_no_repair_sets = {
        "id": "gun_manip" # сейчас у него 95%, но нет рем. комплектов
    }


    check.equal(requests.post(url=path, headers=headers, 
                              json=data_id_does_not_exist).status_code, 400)
    
    check.equal(requests.post(url=path, headers=headers, 
                              json=data_no_repair_sets).status_code, 400)


