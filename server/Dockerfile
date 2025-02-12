FROM ubuntu:latest



# Устанавливаем необходимые пакеты
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    unzip \
    libjsoncpp-dev \
    libssl-dev \
    uuid-dev \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*
    # последняя команда удаляет кэш списка пакетов, доступных в репозиториях APT.



# Установка Drogon
# Определяем рабочую директорию для Drogon
ENV DROGON_PATH /opt/drogon

# Клонируем репозиторий Drogon
RUN git clone https://github.com/drogonframework/drogon $DROGON_PATH

# Переходим в директорию Drogon
WORKDIR $DROGON_PATH

# Инициализируем подмодули
RUN git submodule update --init

# Создаём директорию сборки для Drogon
RUN mkdir build

# Переходим в директорию сборки Drogon
WORKDIR $DROGON_PATH/build

# Собираем и устанавливаем Drogon
RUN cmake .. && make && make install



# Устанавливаем GTest здесь больше не нужна, он устанавливается во время сборки



# Копируем исходный код сервера в контейнер
COPY . /app

WORKDIR /app

RUN rm -rf build

RUN mkdir build

# Переходим в директорию для сборки
WORKDIR /app/build



# Собираем проект с помощью CMake
RUN rm -rf CMakeCache.txt && cmake ..

# Собираем проект
RUN make



# Запускаем unit-тесты и сервер
CMD cd /app/build && ./test/utils_test && ./server

