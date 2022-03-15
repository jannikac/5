#include "string.hpp"
#include "c_exception.cpp"
#include <cstring>
#include <stdexcept>

const int NOT_FOUND = -1;

// Erstellt eine `string`-Instanz mit der Zeichenfolge ""
string::string() : str((char *)malloc(sizeof(char))), length(0) {
  // Weist Heap-Speicher mit der Größe von einem char zu
  // werfen, wenn malloc fehlschlägt
  if (str == NULL) {
    throw my_exception_class("Fehler bei der Speicherzuweisung", __FILE__,
                             __LINE__);
  }
}

// Erstellt eine `string` Instanz aus einem Zeiger auf ein `char` Array.
string::string(const char *inputString) {
  // inputString auf nullptr überprüfen, damit strlen() keinen segfault erzeugt.
  // Bei einem nullptr wird eine Exception geworfen
  if (!inputString)
    throw std::invalid_argument("recieved nullptr");

  length = strlen(inputString);

  // größe für internen str festlegen
  str = (char *)malloc(sizeof(char) * length);

  // exception werfen wenn malloc fehlschlägt
  if (str == NULL) {
    throw my_exception_class("Fehler bei der Speicherzuweisung", __FILE__,
                             __LINE__);
  }

  // c-string von der Eingabe in den internen str kopieren
  strcpy(str, inputString);
}

// Copy Konstruktor.
string::string(const string &other) {
  str = (char *)malloc(sizeof(char) * other.length);
  // werfen falls malloc fehlschlägy
  if (str == NULL) {
    throw my_exception_class("Fehler bei der Speicherzuweisung", __FILE__,
                             __LINE__);
  }
  strcpy(str, other.str);
  length = other.length;
}

// Move Konstruktor.
string::string(string &&other) {
  str = (char *)malloc(sizeof(char) * other.length);

  // werfen falls malloc fehlschlägy
  if (str == NULL) {
    throw my_exception_class("Fehler bei der Speicherzuweisung", __FILE__,
                             __LINE__);
  }

  str = other.str;
  length = other.length;

  other.str = nullptr;
}

// Fügt ein `char` Array an einen den internen `str` an.
void string::append(const char *inputString) {
  // inputString auf nullptr überprüfen, damit strlen() keinen segfault erzeugt.
  // Bei einem nullptr wird eine exception geworfen
  if (!inputString)
    throw std::invalid_argument("recieved nullptr");

  // Größe des internen str um Länge des inputStrings erweitern
  str = (char *)realloc(str, sizeof(char) * (strlen(inputString) + length));
  // werfen falls realloc fehlschlägy
  if (str == NULL) {
    throw my_exception_class("Fehler bei der Speicherzuweisung", __FILE__,
                             __LINE__);
  }

  // inputString an bestehenden str anhängen
  strcat(str, inputString);

  // Länge aktualisieren
  length = strlen(str);
}

// Verkettet 2 strings miteinander und gibt einen neuen string zurück
string string::operator+(const string &other) {
  string result = string(str);
  result.append(other.str);
  return result;
};

// Kann nur für lesenden Zugriff genutzt werden -> rvalue
const char &string::operator[](const int index) const { return str[index]; };

const char &string::at(const int index) const {
  // Werfen, wenn index out of range
  if (index >= length)
    throw std::out_of_range("index is greater or equals to length");
  return str[index];
};

// Kann für schreibenden Zugriff genutzt werden -> lvalue
char &string::operator[](const int index) { return str[index]; };

char &string::at(const int index) {
  // Werfen, wenn index out of range
  if (index >= length)
    throw std::out_of_range("index is greater or equals to length");
  return str[index];
};

// Gibt den internen `str` zurück.
// Kann keinen `nullptr` zurückgeben, da bei eingabe eines `nullptrs` eine
// Exception geworfen wird.
char *string::data() { return str; }

const char *string::data() const { return str; }

// Findet den ersten `char` im internen `str`, welcher mit `c` übereinstimmt und
// gibt den entsprechenden Index zurück. Wird char nicht gefunden, wird `-1`
// zurück gegeben.
int string::find(char c) const {
  // Gibt Zeiger auf gefundenen char zurück und speichert ihn als res
  char *res = strchr(str, c);
  // Wenn res nullptr zurückgibt, wurde kein char gefunden, also -1 als index
  if (!res)
    return NOT_FOUND;

  // Wenn res keinen nullptr zurückgibt, wurde char gefunden
  // Adresse des gefundenen Zeigers - Adresse des Strings = Index
  int index = (int)(res - str);
  return index;
}

// Interner `str` wird mit `std::cout` ausgegeben.
void string::print() const { std::cout << str << std::endl; }

// `str` wird mit 0 gefüllt und dann auf die Länge 1 zurückgesetzt, damit
// dieser mit `string::append` wiederverwendet werden kann.
void string::clear() {
  // str mit 0 füllen.
  memset(str, 0, length);
  // Größe zurücksetzen
  str = (char *)realloc(str, sizeof(char));
  // werfen falls malloc fehlschlägy
  if (str == NULL) {
    throw my_exception_class("Fehler bei der Speicherzuweisung", __FILE__,
                             __LINE__);
  }
}

// Destruktor
string::~string() {
  // Speicher an der Stelle des str pointers freigeben.
  // Clear aufzurufen reicht nicht, da der Speicher dadurch nicht freigegeben
  // wird.
  free(str);
  // Zeiger auf nullptr setzen, um dangling pointers zu vermeiden
  str = nullptr;
}