FROM postgres:16.1

COPY backend/src /app/
COPY CMakeLists.txt /app/
COPY CPM.cmake /app/

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libpq-dev \
    libpqxx-dev \
    libboost-all-dev \
    libssl-dev \
    libcurl4-openssl-dev \
    libjsoncpp-dev \
    libmicrohttpd-dev \
    libpqxx-dev \
    libpq-dev

RUN cmake .

EXPOSE 8000

CMD ["make", "run"]
