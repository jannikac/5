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
