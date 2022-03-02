# Aufgaben 5 - Ausnahmebehandlung

## Aufgabe 1

### a)

Mit Zeigern auf Members kann auf nichtstatische Mitglieder von Klassenobjekten verwiesen werden. Einen Zeiger auf ein Member kann nicht verwendet werden, um auf ein statisches Klassenmember zu zeigen, da die Adresse eines statischen Members mit keinem bestimmten Objekt verbunden ist. Um auf ein statisches Klassenmember zu zeigen, muss einen normalen Zeiger verwendet werden.

Man kann Zeiger auf Memberfunktionen auf die gleiche Weise verwenden wie Zeiger auf Funktionen. Man kann Zeiger auf Memberfunktionen vergleichen, ihnen Werte zuweisen und sie zum Aufrufen von Memberfunktionen verwenden. Zu beachten ist, dass eine Member-Funktion nicht den gleichen Typ hat wie eine Nicht-Member-Funktion, die die gleiche Anzahl und den gleichen Typ von Argumenten und den gleichen Rückgabetyp hat.

#### Beispiel A

Korrekt.

#### Beispiel B

Kompilierfehler in Zeile 21.

Es wird versucht einem Zeiger auf einen `int` einen Zeiger auf eine nicht-statische Member Variable zuzuweisen, was nicht möglich ist, da ein nicht-statischer Member ohne ein Objektinstanz nicht im Speicher existiert.

#### Beispiel C

Korrekt.

#### Beispiel D

Kompilierfehler in Zeile 41.

Der `iptr` zeigt auf ein Objekt vom Typ `store` mit einem Offset zu dem Ziel. Die rechte Seite von Zeile 41 zeigt allerdings auf genau die Speicheradresse der Membervariable `s.store_id`. Somit sind die Typen der Werte links und rechts vom Gleichheitszeichen unterschiedlich und eine Zuweisung ist nicht möglich.

#### Beispiel E

Kompilierfehler in Zeile 51.

Es wird versucht ein Funktionszeiger auf eine nicht-statische Member Funktion zu erstellen. Das funktioniert nicht, da ein nicht-statischer Member ohne eine Instanz des Objekts nicht im Speicher existiert.

#### Beispiel F

Kompilerfehler in Zeile 62.

Es wird ein Funktionszeiger `fptr` auf eine beliebige Funktion im Typ `store` erstellt. Diesem Zeiger wird die nicht-statische Funktion `&store::sell_item` zugewiesen. Wenn 2 Instanzen von `store` existieren würden und versucht wird diese Funktion in Zeile 62 aufzurufen, weiß der Compiler nicht, welches Objekt genau angesprochen werden soll, da der Zeiger auf eine beliebige Funktion zeigen könnte.

#### Beispiel G

Korrekt.

#### Beispiel H

Kompilierfehler in Zeile 81.

Es wird versucht einen nicht-`const` Zeiger auf eine nicht-statische Member Funktion zu erstellen.

## Aufgabe 2

## Aufgabe 3

### a)

Der Fehler ist, dass ein Memory Leak entsteht. Dieser entsteht, wenn die überprüfung, ob ein Zeiger valide ist fehlschlägt. Wirft der Konstruktor, wird der Destruktor nie aufgerufen und somit wird der Speicher, auf den `assembly_ptr_ ` zeigt nie freigegeben.

#### Alternative 1

Man könnte statt eines nativen C-Zeigers einen Smart Pointer verwenden. Ein Unique Pointer zum Beispiel würde automatisch den Speicher an `assembly_ptr_` freigeben, wenn der Zeiger zerstört wird.

```cpp
class assembly_container {
public:
  assembly_container(const std::vector<part> &parts)
      : assembly_ptr_(new assembly(parts)) {
    if (!assembly_ptr_->valid())
      throw invalid_assembly();
  };
  ~assembly_container() {}

private:
  std::unique_ptr<assembly> assembly_ptr_;
};
```

#### Alternative 2

#### Alternative 3

Möchte man das Problem mit nativen C-Zeigern lösen, muss man daran denken den allokierten Speicher an der Stelle des `assembly_ptr_` wieder freizugeben bevor geworfen wird.

```cpp
class assembly_container {
public:
  assembly_container(const std::vector<part> &parts)
      : assembly_ptr_(new assembly(parts)) {
    if (!assembly_ptr_->valid()) {
      delete assembly_ptr_;
      throw invalid_assembly();
    }
  };
  ~assembly_container() { delete assembly_ptr_; }

private:
  assembly *assembly_ptr_;
};
```

### b)

Es Destruktor darf "nur" keine Ausnahmen werfen, während das Stack Unwinding z.B. durch eine andere Ausnahme oder ein Returns geschieht. In diesem Fall wird sofort `std::terminate` aufgerufen. Der Operator `<<` kann zwar werfen, allerdings könnte man das auch in einen Try-Catch block verpacken. Dieser Block müsste dann die Ausnahme einfach ignorieren (z.B. leerer Catch block). Somit könnten in den meisten Fällen trotzdem Daten in die Logdatei geschrieben werden. Alternativ könnte man im Falle einer Ausnahme im Catch block `std::cout` verwenden, um das Fehlschlagen zu signalisieren.
