# Start from a base image
FROM ubuntu:20.04

# Set environment variable to disable interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary tools
RUN apt-get update && apt-get install -y \
    git \
    wget \
    libpq-dev \
    libssl-dev \
    g++ \
    make \
    ninja-build \
    postgresql-server-dev-all

# Download and install CMake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.22.0/cmake-3.22.0.tar.gz \
    && tar -xzvf cmake-3.22.0.tar.gz \
    && cd cmake-3.22.0 \
    && ./bootstrap \
    && make \
    && make install

# Copy your source code into the Docker image
COPY . /module

# Install oatpp modules
WORKDIR /module/cmake-build-debug/_deps/oatpp-postgresql-src/utility
RUN chmod +x ./install-oatpp-modules.sh

# Set the working directory
WORKDIR /module/build

# Build the application
ARG PG_HOST=postgres
RUN cmake ..
RUN make

# Specify the command to run your application
CMD ["./uni_bd2_backend-exe"]

# docker build -t my-backend-image -f backend.dockerfile .
# docker run -p 8000:8000 --name my-backend-container my-backend-image
