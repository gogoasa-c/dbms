
# Database Management System

Database Management System running in the CLI, designed using object-oriented programming principles for the object-oriented programming course laboratory, implemented using C++17.








## Table of Contents

* [Phase 1](#Phase-1)
* [Phase 2](#Phase-2)
* [Phase 3](#Phase-3)
* [Screenshots](#Screenshots)
## Phase 1
The first phase consisted of thinking up a class structure for our program, implementing command parser function set, which checks if the command is correct, checks for conflicts, and interprets it, and command functionality for a variety of commands:
* CREATE TABLE tableName ((nameColumn1, type, size, defaultValue),  ...);
* DROP TABLE tableName;
* DISPLAY TABLE tableName;
* INSERT INTO tableName VALUES ((valueColumn1, valueColumn2, valueColumn3, ...), ...);
* DELETE FROM tableName WHERE columnName = value;
* SELECT (column1, column2, ...)/ALL FROM tableName [WHERE columnName = value];
* UPDATE tableName SET columnName = value where otherColumnName = otherValue;

The class structure consists of:
* Entry - contains a line of a specific table
* Header - contains the information concerning a table's columns
* Table - contains header and std::vector of entries
* Database - collection class for tables, implemented using singleton design pattern
## Phase 2

The second phase consisted of storing the database's tables and data in text and binary files, as well as functionality for running commands directly from .txt files on execution and importing tables from .csv files using the IMPORT tableName fileName.csv command.

Implemented interface-like abstract classes for reading and writing to files featuring pure virtual methods, now inherited by the Entry, Header, Table, and Database classes.

Automated generation of .txt file outputs for all of the SELECT commands used. They get deleted after rerunning the application.



## Phase 3

Added further uses of standard template library (STL) data structures, such as Maps and Sets, slight refactoring, and menu for ease of use actived through MENU command.
## Screenshots

![Screenshot 1](https://user-images.githubusercontent.com/108761872/228919121-eb59ff82-d308-482e-ba63-2c2b2db56667.png)
![Screenshot 2](https://user-images.githubusercontent.com/108761872/228919221-b098a7c9-138b-453c-92df-f005a1e4b295.png)
![Screenshot 3](https://user-images.githubusercontent.com/108761872/228919280-2954a0cc-ea72-4680-abad-6ef6d1010821.png)

## Authors

- [@gogoasa-c](https://www.github.com/gogoasa-c)
- [@Brescar](https://www.github.com/Brescar)
- [@ChowderChan](https://www.github.com/ChowderChan)

