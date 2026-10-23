# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · **Deutsch** · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock ist eine native Win32/x86-Anwendung für Windows Vista und neuer, die unabhängig konfigurierbare, frei platzierbare Uhren und Kalender auf dem Windows-Desktop anzeigt. Sie läuft im Infobereich und benötigt kein dauerhaft geöffnetes Steuerungsfenster.

## Funktionen

- Bis zu 32 unabhängig konfigurierbare Widgets
- Sprache, Zeitzone, Zeitversatz, Sichtbarkeit und „Immer im Vordergrund“ für jedes Widget
- Analoguhren mit wählbarer Zifferblattgröße und optionalem Sekundenzeiger
- Konfigurierbare Digitaluhren mit Schriftarten, Farben, Deckkraft, Innenabständen, Rahmen, optionaler führender Null und optional transparentem Hintergrund
- Native Windows-Kalender mit Datumsauswahl, vier Rahmenstilen, einstellbarer Rahmenfarbe, Wochennummern, wählbarem Wochenanfang und 33 Kopierformaten
- Kalender-Uhr-Panels mit bis zu zwei zusätzlichen benannten Uhren in eigenen Zeitzonen, getrennten Zifferblattgrößen, vier Rahmenstilen, einstellbarer Rahmenfarbe, UTC-Text, führender Null und einer eigenen Schriftart für jede Textzeile
- Wecker mit Wochentagsauswahl, visueller Anzeige, interner Audiowiedergabe, Wiederholung, lokalen Befehlen und HTTP/HTTPS-Skriptaufrufen
- Zeitzeichen pro Uhr im Abstand von 1, 5, 10, 15, 20, 30 oder 60 Minuten; zeitgleiche Signale werden zu einer Folge zusammengeführt
- Stummschaltung einzelner Uhren und ein markierbarer Befehl „Alle stummschalten“ im Infobereich
- Optionaler automatischer Start mit Windows
- Optionales Einrasten beim Ziehen innerhalb von fünf Pixeln an den Rändern des Arbeitsbereichs, standardmäßig aktiviert; die Randbindung bleibt bei Größenänderungen erhalten
- NTP-Synchronisierung ohne Änderung der Windows-Systemzeit
- Mehrere NTP-Voreinstellungen für Tschechien und die Slowakei, PTB, Ubuntu/NTP Pool sowie eigene Server
- Einstellungen in der Registrierung oder in XML, einschließlich XML-Import und -Export
- Steuerung über den Infobereich mit Wiederherstellung der zuletzt ausgeblendeten Widgets
- Identifizierung der Widgets und stabile Anordnung in einem überlappungsfreien Raster
- Sofortige Vorschau des Erscheinungsbilds mit Abbruchmöglichkeit und Standarddarstellung pro Widget
- Schriftarten für Anwendung und Widgets, visuelle Stile sowie ClearType, GDI oder keine Schriftglättung
- Oberfläche in 36 Sprachvarianten; Sprache der Anwendung und jedes Widgets unabhängig wählbar

## Widget-Typen

| Widget | Beschreibung |
| --- | --- |
| Analoguhr | Frei platzierbares Windows-Zifferblatt mit den Größen und dem optionalen Sekundenzeiger der aktuellen Windows-Version |
| Digitaluhr | Konfigurierbare frei platzierbare Digitalanzeige mit optionalem UTC-Text, führender Null, Rahmen und transparentem Hintergrund |
| Kalender | Verschiebbarer nativer Monatskalender mit Datumsauswahl, konfigurierbaren Rahmen und Kopierformaten |
| Kalender mit Uhr | Kombiniertes Panel mit nativem Kalender, Analoguhr, konfigurierbaren Textzeilen, UTC-Anzeige und Rahmen |
| Monitoruhr | Digitaluhr auf einem oder mehreren ausgewählten Monitoren mit optionaler Verdunkelung und UTC in einer eigenen Zeile |

Beim ersten Start wählt CalClock die Anwendungssprache anhand der Windows-Anzeigesprache. Wird diese nicht unterstützt, verwendet es US-Englisch. Standardmäßig wird eine sichtbare Analoguhr erstellt. Jedes Widget behält Position und Einstellungen zwischen den Programmstarts bei. Solange die Einstellungen geöffnet sind, erscheint eine Monitoruhr als verschiebbare Vorschau im Seitenverhältnis ihres ausgewählten Monitors. `Esc` blendet Monitoruhr und Verdunkelung auch bei geöffneten Einstellungen aus. Über Monitoruhren und verdunkelten Monitoren wird der Mauszeiger nach kurzer Inaktivität ausgeblendet und bei Mausbewegung wieder angezeigt. Über der kleinen Einstellungsvorschau bleibt er sichtbar.

## Bedienung

- Uhren und Panels mit der linken Maustaste ziehen.
- Einen eigenständigen Kalender an seiner freien Fläche ziehen.
- Mit der rechten Maustaste auf ein Widget oder das Symbol im Infobereich klicken, um das Kontextmenü zu öffnen.
- Ein Linksklick auf das Symbol im Infobereich blendet die sichtbaren Widgets aus. Sind alle ausgeblendet, stellt ein weiterer Klick nur die zuletzt ausgeblendeten wieder her.
- Ein Doppelklick auf ein Zifferblatt schaltet die Sekundenanzeige um. Bei einem Kalender mit Uhr schaltet nur ein Doppelklick direkt auf das Hauptzifferblatt den Sekundenzeiger um. Zusätzliche Uhren haben keinen Sekundenzeiger.
- `F1` öffnet die Hilfe, `B` die Einstellungen, `M` schaltet die globale Stummschaltung um und `Esc` blendet ein Widget aus oder beendet einen aktiven Wecker.
- Mit `Alt+0`, `Alt+1`, `Alt+2` oder `Alt+3` wählen Sie bei Analoguhr und Kalender mit Uhr die Größe des Hauptzifferblatts von der kleinsten bis zur größten.
- Ein Doppelklick auf ein Widget in den Einstellungen macht es bei Bedarf sichtbar, aktiviert `Sichtbar` und kennzeichnet es kurz auf dem Desktop.
- Einstellungen aus dem Kontextmenü eines Widgets öffnen, um dieses sofort auszuwählen.
- Entfernen oder Entf löscht beim Anwenden alle ausgewählten Einträge. `Einfg` schaltet die Markierung des aktuellen Eintrags um und bewegt den Listencursor eine Zeile nach unten.
- `Strg+C` kopiert die ausgewählten Widgets; `Strg+V` hängt Kopien in Listenreihenfolge an. Kopien enthalten sämtliche Widget-Einstellungen und erhalten einen Namenszusatz in der Anwendungssprache. Duplizieren führt dieselbe Aktion direkt aus. Höchstens 32 Widgets sind möglich. Reicht der Platz nicht für alle Kopien, werden die passenden in Listenreihenfolge hinzugefügt; auf die übrigen weist eine Meldung hin.

Beim Öffnen der Einstellungen über das Infobereichsymbol werden die Einstellungen des zuletzt ausgewählten Widgets angezeigt.

Die Einstellungen merken sich die zuletzt geöffnete Registerkarte und den zuletzt hinzugefügten Widget-Typ. Auf einem kleinen Arbeitsbereich bietet das Einstellungsfenster bei Bedarf horizontales oder vertikales Scrollen.

Kalenderdaten lassen sich in 33 Formaten kopieren: lokal, sortierbar, mit Tag oder Monat zuerst, ausgeschrieben und mit Wochentag. Jede Maske ist in jeder Oberflächensprache verfügbar. Das lokale kurze Standardformat richtet sich nach der Widget-Sprache; ausgeschriebene Monats- und Wochentagsnamen verwenden ebenfalls diese Sprache. Die Formateinträge zeigen Maske und aktuelles Beispiel.

Ein Kalender mit Uhr kann bis zu zwei zusätzliche Uhren anzeigen. Jede Uhr wird auf Allgemein aktiviert und erhält dort Namen und Zeitzone. Benannte Zonen folgen ihren eigenen Sommerzeitregeln; feste UTC-Versätze bleiben unverändert. Bei aktivierten zusätzlichen Uhren zeigt jede Uhr ihren örtlichen Wochentag unter der Uhrzeit. Die drei Größenlisten auf Darstellung steuern nacheinander die Hauptuhr, Uhr 1 und Uhr 2. Ein Rechtsklick auf ein zusätzliches Zifferblatt öffnet dessen Größenauswahl. Zusätzliche Uhren zeigen nie Sekunden und teilen Sprache, Zeitformat, Schriftarten und Zeitversatz mit dem Widget. Beim Hinzufügen, Entfernen oder Vergrößern von Uhren bleibt das Widget an denselben Rändern des Arbeitsbereichs befestigt.

Im Kalender-Uhr-Panel führt der Datumslink oben den Kalender zum heutigen Tag zurück. Der Zeitzonentext unten öffnet die klassischen Windows-Einstellungen für Datum und Uhrzeit.

`Am Raster ausrichten` ordnet sichtbare Desktop-Widgets in einem stabilen, überlappungsfreien Raster an und erhält ihre ungefähre manuelle Positionierung. Das Widget, aus dessen Menü der Befehl stammt, bleibt an seinem Platz; der Befehl im Infobereich ordnet jeden Monitor unabhängig an. Monitoruhren sind ausgenommen.

## Darstellung

Bei eigenständigen Kalendern bestimmt **Heute-Zeile** im Widget-Menü oder auf Darstellung, ob die untere Heute-Zeile sichtbar ist. Ein einzelner Kalender unterstützt weder Wecker noch Zeitzeichen oder Stummschaltung. Die Wahl wird pro Widget gespeichert. **Zu heute wechseln** bleibt im Menü verfügbar und kehrt zur Monatsansicht zurück. Beim Datumswechsel gemäß der Zeit des jeweiligen Widgets wählen Kalender automatisch den heutigen Tag aus und behalten dabei ihre aktuelle Ansicht bei.

Darstellungsänderungen erscheinen sofort am ausgewählten Widget. `Abbrechen` setzt noch nicht übernommene Änderungen zurück; `Standarddarstellung` stellt die Standardwerte dieses Widget-Typs wieder her.

Digitaluhren, Kalender und kombinierte Panels teilen vier Rahmenstile. Der einfache Rahmen bietet eine einstellbare Farbe; die Rahmenbreite lässt sich dort ändern, wo das Widget dies unterstützt. Transparente Digitaluhren bieten dieselben Stile wie undurchsichtige. Für Anwendungs- und Kalenderschrift gibt es keine Größenwahl, für Digitaluhren und Paneltexte dagegen schon. Eigene Kalenderschriftarten werden beim klassischen Windows-Erscheinungsbild oder bei deaktivierten Designs für die Anwendung oder das Widget unterstützt.

Anwendungssprache, Oberflächenschrift, Schriftglättung, visuelle Stile, Speicherung, Windows-Autostart und Einrasten an Arbeitsbereichsrändern sind global und werden auf Anwendung konfiguriert. Auch die Zeitquelle ist global. Widget-Sprache, Schriftglättung, visuelle Stile, Zeitzone, Versatz, Wecker und Zeitzeichen sind unabhängig einstellbar. Die Schriftglättung bietet **ClearType**, **GDI** und **Keine**.

Der Regler **Audiolautstärke** auf Wecker steuert intern abgespielte Audiodateien für jedes Widget getrennt und zeigt den Pegel in dB. Der Standard **−18 dB** erhält den ursprünglichen Dateipegel (**100%**). Nach rechts wird verstärkt; das Maximum **0 dB** entspricht ungefähr **794%** der ursprünglichen Amplitude. Ganz links liegt **−∞ dB** (Stille). Änderungen wirken auch während des Audiotests. Die Verstärkung gilt für dekodiertes Audio einschließlich WAV, MP3, WMA, AAC, M4A und FLAC, sofern Windows diese unterstützt. Die ältere Wiedergabe nicht dekodierbarer Dateien, etwa MIDI, ist auf 100% begrenzt.

Die Wochentagsauswahl des Weckers folgt dem Wochenanfang der gewählten Anwendungskultur. Gespeicherte Weckertage behalten beim Sprachwechsel ihre Bedeutung. Wird ein Wecker ohne ausgewählte Wochentage über das Widget-Menü aktiviert, öffnet sich dessen Registerkarte Wecker, statt einen nicht ausführbaren Wecker einzuschalten.

**Führende Null** bietet **Ja** (Standard), **Nein, Platz freihalten** und **Nein, ohne Platz**. **Nein, Platz freihalten** verbirgt die Null, reserviert aber ihre tatsächliche Breite in der gewählten Schrift. So bleiben die übrigen Ziffern auch bei proportionalen Schriften an ihrem Platz. Monitoruhren verwenden standardmäßig weiße Schrift auf schwarzem Hintergrund.

## Zeit und Wecker

Digitaluhren, Kalender-Uhr-Panels und Monitoruhren bieten unter **Zeitformat** auf Allgemein **Nach Sprache**, **12 Stunden** und **24 Stunden**. **Nach Sprache** ist die Vorgabe und folgt der Widget-Sprache: US- und australisches Englisch verwenden beispielsweise 12 Stunden, britisches Englisch 24 Stunden. Eine manuelle Auswahl bleibt beim Sprachwechsel erhalten. Trennzeichen und AM/PM-Kennzeichnungen folgen der Kultur; Kulturen ohne eigene Kennzeichnungen verwenden im 12-Stunden-Modus **AM/PM**.

**AM/PM** ist standardmäßig aktiviert. Deaktivieren verbirgt die Kennzeichnung, ohne den 12-Stunden-Zyklus zu ändern. Monitoruhren zeigen die Kennzeichnung wie UTC in einer eigenen Zeile unter der Zeit. UTC verwendet immer das 24-Stunden-Format. Die Einstellung der führenden Null bestimmt weiterhin, ob die Null sichtbar, mit reserviertem Platz unsichtbar oder vollständig ausgelassen ist.

Benannte Zeitzonen zeigen die gesetzliche Ortszeit des gewählten Ortes und berücksichtigen dessen Sommerzeitregeln automatisch. Der Versatz neben dem Namen gilt für das aktuelle Datum und wird beim Öffnen der Liste aktualisiert. Eigenständige **UTC**-Einträge bieten feste Versätze von **UTC−12:00** bis **UTC+14:00** in 15-Minuten-Schritten ohne Sommerzeitwechsel. Pro Widget können Ortszone, eine beliebige andere benannte Zone oder ein fester UTC-Versatz gewählt werden.

Neue Widgets verwenden standardmäßig **Aktuelle Windows-Zeitzone**. Diese Option folgt der aktuellen Windows-Zeitzone und der Einstellung für die automatische Sommerzeit. Vorhandene Widgets behalten ihre ausgewählten Zonen. Die gemeinsame Zeitquelle Windows oder NTP ist davon unabhängig.

Jedes Widget kann eine beliebige Windows-Zeitzone und einen vorzeichenbehafteten Versatz im Format `[-]HH:mm:ss.ff` verwenden. Kompakte Eingaben werden von rechts, beginnend mit Sekunden, ausgewertet.

Der Versatz ist beispielsweise im Rundfunkstudio nützlich, um die Verzögerung der Übertragungsstrecke auszugleichen. Wird die Studiouhr um die gemessene Verzögerung vorgestellt, erreicht ihr Zeitzeichen die Hörer zum vorgesehenen Zeitpunkt.

Der Widget-Versatz wird vor der Umrechnung in die Zeitzone auf UTC angewendet und verschiebt damit auch den Zeitpunkt einer Zeitumstellung. Eine um zehn Sekunden vorgestellte Uhr stellt sich zehn Sekunden früher um; eine um zehn Sekunden nachgestellte Uhr zehn Sekunden später. Zeiger, Digitalanzeige, Kalenderdatum, Wecker und Zeitzeichen verwenden die so berechnete Zeit.

Auf der Registerkarte Zeit wird für die gesamte Anwendung und damit für alle Widgets die Windows-Systemzeit oder die Zeit der eingestellten NTP-Server gewählt. NTP korrigiert nur die in CalClock angezeigte Zeit; die Windows-Uhr wird nie geändert. Bis zur ersten gültigen Antwort wird die Systemzeit verwendet. NTP ist voreingestellt. Die automatische Gruppe wählt nach der Systemregion die tschechisch-slowakischen Server, PTB für Europa oder den globalen Pool. Mehrere Messungen werden nach Netzverzögerung und Ausreißern gefiltert. Jetzt synchronisieren startet sofort eine neue Messung.

Nach der Synchronisierung läuft die CalClock-Uhr unabhängig von späteren Änderungen der Windows-Systemzeit weiter. Bei einem Verbindungsausfall oder Serverwechsel läuft sie ab der letzten gültigen Synchronisierung weiter, bis eine neue Antwort vorliegt; dieser Zustand bleibt bis zum Beenden der Anwendung erhalten.

Die Registerkarte Zeit protokolliert NTP-Serverabfragen seit dem Programmstart. Jeder Eintrag enthält Datum und lokale Computerzeit, Server und Status. OK bezeichnet eine gültige Antwort; θ zeigt deren Abweichung von der Windows-Systemzeit. ERR nennt den Fehlergrund und gegebenenfalls einen Fehlercode. Der letzte Eintrag einer Abfragegruppe enthält auch die berechnete Abweichung Θ, sofern verwertbare Messungen vorliegen.

Abweichungen werden in Millisekunden mit vier Nachkommastellen angezeigt. Ein positiver Wert bedeutet, dass die Serveruhr Windows voraus ist; ein negativer Wert bedeutet, dass sie nachgeht. Θ berücksichtigt die angenommenen Messungen und wird auch im Synchronisierungsstatus angezeigt.

Protokoll speichern exportiert die Einträge einschließlich Abweichungen und Fehlerdetails als CSV. Einträge werden nicht über Programmstarts hinweg aufbewahrt; speichern Sie sie vor dem Beenden, wenn Sie sie behalten möchten.

Uhr-Widgets unterstützen Wecker für einzeln wählbare Wochentage; standardmäßig sind alle sieben Tage aktiv. Ein Wecker macht sein ausgeblendetes Widget sichtbar und holt es vor andere Fenster, ohne „Immer im Vordergrund“ dauerhaft zu verändern. WAV, MP3, WMA, MIDI, AAC, M4A und FLAC werden für einmalige oder wiederholte interne Wiedergabe erkannt; die tatsächliche Dekodierung hängt von den installierten Windows-Multimediakomponenten ab. Andere Dateien und Befehle werden asynchron an Windows übergeben. Ein Wecker kann auch eine HTTP- oder HTTPS-Adresse aufrufen. Unabhängig davon kann er ein Zeitzeichen aus sechs Tönen verwenden, dessen erster kurzer Ton fünf Sekunden vor der Weckzeit erklingt.

Die Weckertöne werden anhand des tatsächlich bevorstehenden Weckzeitpunkts nach Zeitzonenumrechnung und Widget-Versatz geplant. Sie beginnen fünf tatsächlich verstrichene Sekunden davor, auch wenn die angezeigte Uhr direkt zur Weckzeit springt. Eine im Frühjahr übersprungene Weckzeit löst weder Wecker noch Töne aus. In der im Herbst wiederholten Stunde ertönen Wecker und Töne für dasselbe Datum und dieselbe eingestellte Uhrzeit nur einmal.

Test zeigt die visuelle Weckeranzeige und prüft Datei, Befehl, Audio und entfernte Skriptadresse asynchron. Ist das Weckerzeitzeichen ausgewählt, spielt Test auch die gesamte Folge aus sechs Tönen; Test stoppen beendet interne Audiowiedergabe und Signalvorschau.

Auf der Registerkarte Zeitzeichen gibt es das Kontrollkästchen Zeitzeichen aktiv und Optionsfelder für Intervalle von 1, 5, 10, 15, 20, 30 oder 60 Minuten gemäß der angezeigten Widget-Zeit. Anfangs ist das Signal ausgeschaltet und das Stundenintervall ausgewählt. Aus- und Einschalten über Zeitzeichen im Widget-Menü behält das Intervall bei. Das Menü zeigt die Weckzeit und das Signalintervall in Klammern. Das 20-Minuten-Intervall ertönt zu :00, :20 und :40 dieser Zeit. Das Signal folgt dem **Greenwich Time Signal (GTS)**: Fünf kurze Töne markieren die letzten fünf Sekunden, ein längerer Ton den genauen Intervallbeginn. Zeitzonen, UTC-Modus, Versätze und aktuelle NTP-Korrektur werden berücksichtigt. Weckerzeitzeichen und Registerkarte Signal bleiben getrennt konfigurierbar; treffen Termine zusammen, spielt CalClock nur eine gemeinsame Folge. Auch Sekundenbruchteile im Widget-Versatz werden berücksichtigt. Überlappende Widget-, Wecker- und Testtöne erklingen durchgehend bis zum Ende der letzten Überlappung.

**Zeitzeichenklang** auf Anwendung bietet **Interner Generator** (Standard) und **Systemsignalton**. Die Auswahl gilt für alle Widget-Zeitzeichen einschließlich der Wecker und wird global gespeichert. Beim **Internen Generator** zeigt **Zeitzeichenlautstärke** den Pegel für die ganze Anwendung in dB. Ganz rechts liegen **0 dB**, die maximale unverzerrte Sinusamplitude; Stille entspricht **−∞ dB**. Die Vorgabe ist **−18 dB**. Der aktuelle Ton darf ausklingen; ein langer Ton kann dafür bis zu einer halben Sekunde benötigen. **Test** neben **Zeitzeichenklang** startet die fortlaufende Vorschau, **Test stoppen** beendet sie. Sowohl **Systemsignalton** als auch **Interner Generator** sind testbar; der Testzustand wird nicht gespeichert. Das Festhalten des Lautstärkereglers startet ebenfalls eine Vorschau bis zum Loslassen, sofern kein per Taste gestarteter Test läuft. Die Wiedergabe beginnt mit der nächsten vollen Sekunde: kurze Töne jede Sekunde und ein langer zu :00, :05, :10 usw. Vorschau und gleichzeitige Widget- oder Weckersignale teilen einen einzigen Ton. Die Klangwahl ist nur verfügbar, wenn das System beide Verfahren unterstützt.

Wecker und Zeitzeichen lassen sich auch im Kontextmenü jedes klangfähigen Widgets umschalten. Der Weckereintrag zeigt die Zeit und, sofern nicht alle Tage aktiv sind, die ausgewählten Wochentage. Der markierte Befehl Stumm betrifft sein Widget und entspricht Stumm auf Allgemein. Ein einzelner Kalender unterstützt weder Wecker noch Zeitzeichen oder Stummschaltung. Im Infobereich heißt der Befehl Alle stummschalten; `M` auf einem Widget führt dieselbe globale Aktion aus. Das globale Aufheben der Stummschaltung stellt nur die durch die vorherige globale Aktion stummgeschalteten Widgets wieder her. Interne Audiowiedergabe läuft lautlos weiter und wird danach wieder hörbar. Ein bereits laufender Ton darf enden; weitere Töne werden bis zur erneuten Freigabe übersprungen. Andere Befehle und entfernte Skripte bleiben unbeeinflusst.

## Einstellungen und Menüs

Jedes Widget-Menü enthält die für den Typ passenden Befehle — Sichtbarkeit, Vordergrund, Sekunden, Analoggröße oder Datumskopierformat — gefolgt von `Am Raster ausrichten`, Einstellungen, Hilfe, Info und Beenden. Das Infobereichsmenü führt alle Widgets mit ihrer laufenden Nummer auf, danach Alle anzeigen, Alle ausblenden und Alle stummschalten. Der getrennt gruppierte Befehl `Am Raster ausrichten` folgt vor den Anwendungsbefehlen.

Anzeigen oder Wiederherstellen holt Widgets vor andere Fenster, ohne ihren Vordergrundstatus zu ändern. CalClock sorgt nach dem Start für mindestens ein sichtbares Widget. Ein zweiter Start aktiviert die vorhandene Instanz und stellt die zuletzt ausgeblendeten Widgets wieder her, falls keines sichtbar ist. Nach einem Neustart des Windows-Explorers wird das Infobereichssymbol automatisch neu registriert.

## Speicherung der Einstellungen

Standardmäßig werden Einstellungen hier gespeichert:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

Die XML-Speicherung lässt sich in den Einstellungen aktivieren und verwendet:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Ein XML-Import lädt die Einstellungen sofort und speichert sie im aktuell gewählten Speicher, ohne dessen Typ zu ändern. Der Stummzustand wird pro klangfähigem Widget gespeichert.

## Kompilieren

Voraussetzungen:

- Microsoft Visual Studio mit dem MSVC-v145-Toolset
- Windows SDK

`CalClock.slnx` öffnen, `Release | x86` auswählen und die Projektmappe erstellen. Die ausführbare Datei entsteht unter:

```text
Release\CalClock.exe
```

Nur Win32/x86 wird unterstützt. Das Projekt bietet bewusst keine x64-Konfiguration, da die Integration des Windows-Uhr-Steuerelements x86-Kompatibilität voraussetzt.

## Lizenz

CalClock ist unter der [MIT-Lizenz](../license.txt) verfügbar.

Copyright © Petr Červinka — FortSoft 2026
