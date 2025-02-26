FROM ubuntu:24.04

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
    libyaml-cpp-dev \
    libpq-dev \
    libmariadb-dev


ENV DROGON_PATH /opt/drogon
RUN git clone https://github.com/drogonframework/drogon $DROGON_PATH
WORKDIR $DROGON_PATH
RUN git submodule update --init
RUN mkdir build
WORKDIR $DROGON_PATH/build
RUN cmake .. && make && make install


COPY server-0.1.1-Linux.deb /root
RUN mkdir database
COPY mehConfig-example.json /root/database
COPY config-example.json /root


WORKDIR /root
RUN dpkg -i server-0.1.1-Linux.deb
RUN chmod +x /usr/bin/server


RUN echo "\033[33mConfig files pathes:\033[0m"
RUN echo "   server binary file: [/root/config-example.json]"
RUN echo "   meh config file: [/root/database/mehConfig-example.json]"

CMD [ "bash" ]

