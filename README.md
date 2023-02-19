# SQL w C++11

Prosty program demonstrujący połączenie z bazą danych SQL oraz operacje na bazie danych, takie jak dodawanie, aktualizowanie i usuwanie rekordów oraz wykonywanie zapytań SQL.

## Wymagania

Program wymaga kompilatora C++ z obsługą standardu C++11 oraz biblioteki SQLite3. Można je zainstalować na systemie Ubuntu za pomocą następującego polecenia:
sudo apt-get install g++ libsqlite3-dev


## Kompilacja

Program można skompilować za pomocą kompilatora g++:

g++ -std=c++11 -lsqlite3 main.cpp -o program

## Użycie

Po uruchomieniu programu użytkownik może wybrać jedną z kilku opcji, w tym dodanie użytkownika, aktualizowanie wieku użytkownika, usunięcie użytkownika oraz wyświetlenie listy użytkowników. Program łączy się z bazą danych SQLite i wykorzystuje prosty interfejs wiersza poleceń do obsługi operacji na bazie danych.

## Autor

Program napisany przez Michała Lewandowskiego.
