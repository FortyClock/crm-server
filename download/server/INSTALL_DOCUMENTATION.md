# Документация по установке и запуску проекта


# О проекте
Данный проект представляет собой серверное приложение, разработанное с использованием фреймворка Drogon на C++17. Сервер является одной из двух частей проекта, так как другая часть включает клиентское приложение, о котором также написано в основной документации, расположенной в корневой директории проекта. Он предназначен для хранения и обработки конфигурации робота, который имеет телеметрические параметры, карту местности и информацию о своем положении на карте. На карте могут находиться враги, что позволяет роботу стрелять в них, а также выполнять ремонт своего снаряжения и самого себя. Для всех этих задач реализованы функции обработки HTTP-запросов через предоставленный API. Подробную информацию можно найти в основной документации, расположенной в корневой директории проекта.

# Системные требования
Операционная система: Ubuntu 24.04 / Ubuntu 24.04 LTS.
Необходимые библиотеки/пакеты для установки:
- для from-source установки: git.
- для with-deb установки: запустить скрипт "inst-depends", он установит необходимые зависимости.


# О настройке "mehConfig-example.json"

Важно что все id в файле "mehConfig-example.json" должны начинаться с имени своего блока, а заканчиваться символом "_" + его уникальный номер.
```
Пример:
id grab_manip - "grab_manip" + "_001"

"grab_manip" : 
		{
			"capacity" : 60,
			"id" : "grab_manip_001"
		}
```


# "from-source" установка
- Перейдите в корневую директорию пользователя:
```
cd ~
```
- Клонируйте репозиторий проекта:
```
git clone https://github.com/FortyClock/crm-server.git
```
- (Рекомендуется) Дайте права на выполнение файла инсталляции: 
```
chmod +x ./crm-server/download.server/crmserverinst
```
- Запустите файл инсталляции:
```
./crm-server/download/server/crmserverinst
```
- Дождитесь завершения инсталляции и выполните требуемые действия, указанные инсталлером.


# "with-deb" установка
- Скачать себе все файлы директории "with-deb" любым способом.
- Установить все зависимости, самостоятельно или скриптом "inst-depends".
- Установить deb:
```
dpkg -i server-0.1.1-Linux.deb
```
- Настроить файлы "config-example.json", "mehConfig-example.json".
- БИНАРНИК СЕРВЕРА и UNIT-ТЕСТЫ УСТАНАВЛИВАЕТСЯ В "/usr/bin/".