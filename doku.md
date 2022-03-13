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

### a)
Der Aufruf von `std::terminate()` gilt es im Allgemeinen zu verhindern, da das Programm im Fehlerfall kompromisslos terminiert wird. Mit dem Aufruf wird der Callstack aufgelöst und der Anwendungsspeicher (Heap und Stack) werden geleert. Damit wird debugging unmöglich, da die Fehlerursache nur schwer eingegrenzt werden kann. Dies bedeutet, gehe nach Folgender Faustregel vor:
>Eine Ausnahme wird genau einmal werfen und einmal fangen. Das fangen vom Typ `const&`.

Z2 meint ein Programm, dessen Programmablauf kein undefiniertes Verhalten, memory leaks, exception Slicing usw. beinhaltet. Zusammenfassend sich an gewissen best-practices schemes orientiert, sodass keine unerwünschten Seiteneffekte auftreten.

| Faustregel | Ziel     | Begründung                                                                                                                                                                                                                                                                                                                                           |
| ---------- | -------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| F1         | Z2       | Exception Slicing führt dazu, dass die abgeleitete Klasse aus `std::exception` abgeschnitten wird. Damit ist in der Exception ein Informationsverlust.                                                                                                                                                                                               |
| F2         | Z2/Z3    | Umständlicher Code, der methodenspezifische detailierte Exceptions ausgibt. Führt bei geschachtelten Fkt.-Aufrufen zu Umverpacken, da die geschachtelte Fkt. eine Exception wirft, die von der übergordneten Funktion abgefangen wird und in eine neue spezifische Exception eingebettet wird. Möglicher Informationsverlust und Fehleranfälligkeit. |
| F3         | Z3       | Allgemeine Ausnahmeklassen für möglichst große Wiederverwendung in verschiedenen Programmmodulen und übersichtlichen Code. Beispielsweise `out-of-memory` Exception anstelle methodenspezifscher Ausnahme.                                                                                                                                           |
| F4         | Z1/Z2/Z3 | `std::terminate()` wird aufgerufen, falls geworfene Ausnahme nicht der Ausnahmespezifikation entspricht -> beliebige Ausnahme bei Weglassen des Ausnahmespezifizierers möglich.                                                                                                                                                                      |
| F5         | Z1/Z2    | Ungültiges Objekt kann nicht kontruiert werden, somit automatische Freigabe des Objektspeichers (Stack oder Heap)                                                                                                                                                                                                                                    |
| F6         | Z2       | Automatische Zeiger sind notwendig, um geschachtelte `new` Aufrufe abzusichern. Im Fehlerfall wird geschachteltes `new` Object bei vollständiger Kontruktion nicht zerstört -> memory leak. Automatischer Zeiger kümmert sich bei Exception um die Zerstörung des geschachtelten `new` Objekts.                                                      |
| F7         | Z1/Z2/Z3 | Wenn ein Stack Unwinding aufgrund ener Ausnahme oder return auftritt, würde bei einem Destruktoraufruf mit einer Exception zu einer neuen Ausnahme außerhalb des Benutzercodes erfolgen und ein kompromissloses `std::terminate()` wird aufgerufen. `throw → ~bug_thread() → throw → std::terminate()`                                               |
| F8         | Z1       | Wenn Ausnahmeklassen beim Kopieren oder Zuweisen werfen würden, führt dies zu einem `std::terminate()` aufgrund der Ausnahme außerhalb des Benutzercodes. Realisierung mithilfe von shared_ptr möglich.                                                                                                                                              |
| F9         | Z1/Z2/Z3 | Grund siehe Faustformel F1-F8.                                                                                                                                                                                                                                                                                                                       |

### f)
Es tritt Object Slicing auf, da im Funktionskopf `made_talk` ein Parameter vom Type `base` entgegengenommen wird. Die "zusätzliche" information der Objektzugörigkeit zur Klasse `derived` geht verloren, sodass die Ausgabe `B` ist. In Zeile 6 wird die Funktion `talk()` implizit aufgerufen, da der eigentliche Objekttyp ein anderer ist. 


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
