CREATE EXTENSION IF NOT EXISTS dblink;

--1. ROLE DATABASE

DO
$do$
    BEGIN
        IF EXISTS (SELECT
                   FROM pg_catalog.pg_roles
                   WHERE rolname = 'Supervisor') THEN

            RAISE NOTICE 'Role "Supervisor" already exists. Skipping.';
        ELSE
            BEGIN
                -- nested block
                CREATE ROLE "Supervisor"
                    WITH LOGIN PASSWORD 'Supervisor'
                    SUPERUSER
                    INHERIT
                    NOCREATEDB
                    NOCREATEROLE
                    NOREPLICATION;
            EXCEPTION
                WHEN duplicate_object THEN
                    RAISE NOTICE 'Role "Supervisor" was just created by a concurrent transaction. Skipping.';
            END;
        END IF;
    END
$do$;

DO
$do$
    BEGIN
        IF EXISTS (SELECT
                   FROM pg_catalog.pg_roles
                   WHERE rolname = 'Admin') THEN

            RAISE NOTICE 'Role "Admin" already exists. Skipping.';
        ELSE
            BEGIN
                -- nested block
                CREATE ROLE "Admin"
                    WITH LOGIN PASSWORD 'Admin'
                    NOSUPERUSER
                    INHERIT
                    NOCREATEDB
                    NOCREATEROLE
                    NOREPLICATION;
            EXCEPTION
                WHEN duplicate_object THEN
                    RAISE NOTICE 'Role "Admin" was just created by a concurrent transaction. Skipping.';
            END;
        END IF;
    END
$do$;

DO
$do$
    BEGIN
        IF EXISTS (SELECT
                   FROM pg_catalog.pg_roles
                   WHERE rolname = 'Default') THEN

            RAISE NOTICE 'Role "Default" already exists. Skipping.';
        ELSE
            BEGIN
                -- nested block
                CREATE ROLE "Default"
                    NOSUPERUSER
                    INHERIT
                    NOCREATEDB
                    NOCREATEROLE
                    NOREPLICATION;
            EXCEPTION
                WHEN duplicate_object THEN
                    RAISE NOTICE 'Role "Default" was just created by a concurrent transaction. Skipping.';
            END;
        END IF;
    END
$do$;

DO
$do$
BEGIN
   IF EXISTS (SELECT FROM pg_database WHERE datname = 'bd2') THEN
      RAISE NOTICE 'Database "bd2" already exists, skipping';
   ELSE
      PERFORM dblink_exec('dbname=' || current_database() || ' user=postgres password=postgres'
                        , 'CREATE DATABASE bd2
                  WITH
                  OWNER = "Supervisor"
                  ENCODING = ''UTF8''
                  LC_COLLATE = ''Polish_Poland.1250''
                  LC_CTYPE = ''Polish_Poland.1250''
                  TABLESPACE = pg_default
                  CONNECTION LIMIT = -1');
   END IF;
END
$do$;

GRANT ALL PRIVILEGES ON DATABASE bd2 TO "Supervisor";
