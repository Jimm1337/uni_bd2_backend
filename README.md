# Administrative Regions of The Czech Republic - Databases 2 Project
Created by:
- Oskar Gusta (back-end - C++ + SQL)
- Konrad Skowron (front-end, separate repository)

## Summary
This server is designed to deliver a CRUD REST service for a project centered around organizing and presenting in a searchable, visual way the administrative regions of the Czech Republic. It supports subregions and has enchanced support build into the SQL for searches. Currently, SwaggerUI integration is complete but migration is not so manual setup of the DB is nececarry.

## Check out the demo!
#### This project's demo is currently deployed [Here](http://map.eurasianskylark.pl)

## Compile and implement
This project handles dependancies automatically, so it is not necessary to install anything but CMake, Ninja and a compiler.

- Create a postgres database
- Fill out the connection string https://github.com/Jimm1337/uni_bd2_backend/blob/5302a7904280882b318215e07d7fa61c256d6fe3/CMakeLists.txt#L135
- Compile and run
```
$ mkdir build && cd build
$ cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja
$ ninja
$ ./src/uni_bd2_backend-exe
```
