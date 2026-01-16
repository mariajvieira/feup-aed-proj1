cmake_minimum_required(VERSION 3.26)
project(schedule)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.idea)

add_executable(
        schedule
        .idea/.gitignore
        .idea/modules.xml
        .idea/schedule.iml
        Lecture.cpp
        Lecture.h
        classes.csv
        classes_per_uc.csv
        students_classes.csv
        UC.cpp
        UC.h
        Student.h
        Student.cpp
        data_parsing.cpp
        main.cpp
        data_parsing.h
        consult_functions.cpp
        consult_functions.h
        Class.h
        Class.cpp
        requests_functions.h
        requests_functions.cpp
)

