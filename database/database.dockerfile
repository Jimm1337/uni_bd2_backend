FROM postgres:16.1

ENV POSTGRES_PASSWORD=postgres
ENV POSTGRES_USER=postgres

COPY ./sql/000_MIGRATE_postgres.sql /docker-entrypoint-initdb.d/
COPY ./sql/001_init.sql /docker-entrypoint-initdb.d/

# docker build -t my-postgres-image -f database.dockerfile .
# docker run -p 5432:5432 -e POSTGRES_PASSWORD=postgres --name my-postgres-container my-postgres-image
