#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

// Funkcja callback dla wykonywanych zapytań SQL
static int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << endl;
    return 0;
}

int main() {
    // Otwórz połączenie z bazą danych
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        cerr << "Nie można otworzyć bazy danych: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    } else {
        cout << "Połączono z bazą danych" << endl;
    }

    // Utwórz tabelę "uzytkownicy" jeśli nie istnieje
    string createTableSQL = "CREATE TABLE IF NOT EXISTS uzytkownicy (id INTEGER PRIMARY KEY, imie TEXT, nazwisko TEXT, wiek INT)";
    char *errMsg;
    rc = sqlite3_exec(db, createTableSQL.c_str(), callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Błąd przy tworzeniu tabeli: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Utworzono tabelę 'uzytkownicy'" << endl;
    }

    // Menu
    int choice;
    do {
        cout << "Co chcesz zrobić?" << endl;
        cout << "1. Dodaj użytkownika" << endl;
        cout << "2. Zaktualizuj wiek użytkownika" << endl;
        cout << "3. Usuń użytkownika" << endl;
        cout << "4. Wyświetl użytkowników" << endl;
        cout << "0. Wyjdź" << endl;
        cout << "> ";
        cin >> choice;

        switch (choice) {
                        case 1: {
                string imie, nazwisko;
                int wiek;
                cout << "Podaj imię: ";
                cin >> imie;
                cout << "Podaj nazwisko: ";
                cin >> nazwisko;
                cout << "Podaj wiek: ";
                cin >> wiek;

                // Dodaj użytkownika
                string insertSQL = "INSERT INTO uzytkownicy (imie, nazwisko, wiek) VALUES ('" + imie + "', '" + nazwisko + "', " + to_string(wiek) + ")";
                rc = sqlite3_exec(db, insertSQL.c_str(), callback, 0, &errMsg);
                if (rc != SQLITE_OK) {
                    cerr << "Błąd przy dodawaniu użytkownika: " << errMsg << endl;
                    sqlite3_free(errMsg);
                } else {
                    cout << "Dodano użytkownika do tabeli 'uzytkownicy'" << endl;
                }
                break;
            }
            case 2: {
                int id, wiek;
                cout << "Podaj id użytkownika: ";
                cin >> id;
                cout << "Podaj nowy wiek: ";
                cin >> wiek;

                // Zaktualizuj wiek użytkownika
                string updateSQL = "UPDATE uzytkownicy SET wiek=" + to_string(wiek) + " WHERE id=" + to_string(id);
                rc = sqlite3_exec(db, updateSQL.c_str(), callback, 0, &errMsg);
                if (rc != SQLITE_OK) {
                    cerr << "Błąd przy aktualizowaniu wieku użytkownika: " << errMsg << endl;
                    sqlite3_free(errMsg);
                } else {
                    cout << "Zaktualizowano wiek użytkownika o id=" << id << endl;
                }
                break;
            }
            case 3: {
                int id;
                cout << "Podaj id użytkownika do usunięcia: ";
                cin >> id;

                // Usuń użytkownika
                string deleteSQL = "DELETE FROM uzytkownicy WHERE id=" + to_string(id);
                rc = sqlite3_exec(db, deleteSQL.c_str(), callback, 0, &errMsg);
                if (rc != SQLITE_OK) {
                    cerr << "Błąd przy usuwaniu użytkownika: " << errMsg << endl;
                    sqlite3_free(errMsg);
                } else {
                    cout << "Usunięto użytkownika o id=" << id << endl;
                }
                break;
            }
            case 4: {
                // Wyświetl użytkowników
                string selectSQL = "SELECT * FROM uzytkownicy";
                rc = sqlite3_exec(db, selectSQL.c_str(), callback, 0, &errMsg);
                if (rc != SQLITE_OK) {
                    cerr << "Błąd przy wykonaniu zapytania SQL: " << errMsg << endl;
                    sqlite3_free(errMsg);
                }
                break;
            }
            case 0:
                // Nic nie rób - wyjdź z programu
                break;
            default:
                cout << "Nieznana opcja" << endl;
                break;
        }
    } while (choice != 0);

    // Zamknij połączenie z bazą danych
    sqlite3_close(db);

    return 0;
}
