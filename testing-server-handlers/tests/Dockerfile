FROM python:3.9


# Устанавливаем необходимые пакеты Python
RUN pip install --no-cache-dir pytest pytest_check requests


# Копируем файлы тестов в контейнер
COPY . /app


# Устанавливаем рабочую директорию
WORKDIR /app


# Запускаем интеграционные тесты из tests.py
CMD ["pytest", "tests.py"]
