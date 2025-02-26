FROM ubuntu:24.04



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
    tree \
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



RUN mkdir -p /root/crm-server/server



# Копируем исходный код сервера в контейнер
COPY . /root/crm-server/server

WORKDIR /root/crm-server/server

RUN rm -rf build

RUN mkdir build

# Переходим в директорию для сборки
WORKDIR /root/crm-server/server/build



# Указываем CMake, где искать JsonCpp
ENV CMAKE_PREFIX_PATH=/usr

ENV CRM_SERVER_DB_DIR=/root/crm-server/server/database/
ENV CRM_SERVER_CONFIG_DIR=/root/crm-server/server/config-example.json


# Собираем проект с помощью CMake
RUN rm -rf CMakeCache.txt && cmake ..

# Собираем проект
RUN make



# Запускаем unit-тесты и сервер
CMD tree && cd /root/crm-server/server/build && ./test/utils_test && ./server

