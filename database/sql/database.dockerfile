# Start from a base image
FROM postgres:16.1

# Set environment variables
ENV POSTGRES_PASSWORD=postgres
ENV POSTGRES_USER=postgres

# Copy initialization scripts
COPY ./000_MIGRATE_postgres.sql /docker-entrypoint-initdb.d/
COPY ./001_init.sql /docker-entrypoint-initdb.d/

# docker build -t my-postgres-image -f database.dockerfile .
# docker run -p 5432:5432 -e POSTGRES_PASSWORD=postgres --network bd2-app-network --name my-postgres-container my-postgres-image
