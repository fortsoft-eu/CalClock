# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · **Polski** · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md)

CalClock to natywna aplikacja Win32/x86 dla Windows Vista i nowszych wersji, wyświetlająca na pulpicie niezależnie konfigurowane, swobodnie rozmieszczane zegary i kalendarze. Działa w obszarze powiadomień i nie wymaga stale otwartego okna sterowania.

## Funkcje

- Do 32 niezależnie konfigurowanych widżetów
- Osobny język, strefa czasowa, przesunięcie czasu, widoczność i tryb zawsze na wierzchu dla każdego widżetu
- Zegary analogowe oparte na kontrolce Windows `ClockWndMain`, z wykrywaniem dostępnych rozmiarów i obsługą wskazówki sekundowej
- Zegary cyfrowe z ustawieniami czcionek, kolorów, nieprzezroczystości, odstępów wewnętrznych, ramek, opcjonalnego zera wiodącego i przezroczystego tła
- Natywne kalendarze Windows z wyborem daty, czterema stylami ramki, konfigurowalnym kolorem ramki, numerami tygodni, pierwszym dniem tygodnia i 33 formatami kopiowania
- Panele kalendarza z zegarem i maksymalnie dwoma dodatkowymi nazwanymi zegarami w osobnych strefach, niezależnymi rozmiarami tarcz, czterema stylami ramki, kolorem ramki, tekstem UTC, zerem wiodącym i osobną czcionką każdego wiersza tekstu
- Alarmy z wyborem dni tygodnia, sygnalizacją wizualną, wewnętrznym odtwarzaniem dźwięku, powtarzaniem, poleceniami lokalnymi i wywołaniami skryptów HTTP/HTTPS
- Sygnały czasu dla poszczególnych zegarów co 1, 5, 10, 15, 20, 30 lub 60 minut; jednoczesne sygnały są łączone w jedną sekwencję
- Polecenie Wycisz dla poszczególnych zegarów i zaznaczane polecenie Wycisz wszystko w obszarze powiadomień
- Opcjonalne uruchamianie z Windows
- Opcjonalne przyciąganie do krawędzi obszaru roboczego podczas przeciągania w zasięgu pięciu pikseli, domyślnie włączone; przywiązanie do krawędzi jest zachowywane przy zmianie rozmiaru
- Synchronizacja NTP bez zmiany zegara systemowego Windows
- Zestawy serwerów NTP dla Czech i Słowacji, PTB, Ubuntu/NTP Pool oraz serwery własne
- Zapis ustawień w rejestrze lub XML, z importem i eksportem XML
- Sterowanie z obszaru powiadomień z przywracaniem ostatnio ukrytych widżetów
- Identyfikacja widżetów i stabilne rozmieszczanie w siatce bez nakładania
- Bieżący podgląd wyglądu z anulowaniem i przywracaniem domyślnego wyglądu każdego widżetu
- Czcionki aplikacji i widżetów, style wizualne oraz wygładzanie ClearType, GDI lub brak wygładzania
- Interfejs czeski, angielski amerykański, brytyjski i australijski, niemiecki, francuski, hiszpański, włoski, portugalski, polski, słowacki, duński, fiński, islandzki, norweski, szwedzki i turecki

## Typy widżetów

| Widżet | Opis |
| --- | --- |
| Zegar analogowy | Swobodnie rozmieszczana tarcza Windows z rozmiarami i opcjonalną wskazówką sekundową dostępnymi w aktualnej wersji Windows |
| Zegar cyfrowy | Konfigurowalny zegar cyfrowy z opcjonalnym tekstem UTC, zerem wiodącym, ramką i przezroczystym tłem |
| Kalendarz | Przesuwany natywny kalendarz miesięczny z wyborem daty, konfigurowalną ramką i formatami kopiowania |
| Kalendarz z zegarem | Panel łączący natywny kalendarz, zegar analogowy, konfigurowalne wiersze tekstu, UTC i ramkę |
| Zegar na monitorze | Zegar cyfrowy zajmujący jeden lub kilka wybranych monitorów, z opcjonalnym zaciemnieniem i UTC w osobnym wierszu |

Przy pierwszym uruchomieniu CalClock wybiera język interfejsu Windows, a jeśli nie jest obsługiwany, używa angielskiego amerykańskiego. Domyślnie tworzy jeden widoczny zegar analogowy. Każdy widżet zachowuje pozycję i ustawienia między uruchomieniami. Przy otwartych Ustawieniach zegar na monitorze jest zawsze reprezentowany przez przesuwany podgląd o proporcjach wybranego monitora. `Esc` ukrywa zegar i usuwa jego zaciemnienie również wtedy, gdy Ustawienia są aktywne. Kursor znika po krótkiej bezczynności nad zegarami na monitorze i zaciemnionymi monitorami, a pojawia się po ruchu myszy. Nad małym podglądem w Ustawieniach pozostaje widoczny.

## Obsługa

- Przeciągaj zegar lub panel lewym przyciskiem myszy.
- Samodzielny kalendarz przeciągaj za jego wolny obszar.
- Kliknij prawym przyciskiem widżet lub ikonę powiadomień, aby otworzyć menu kontekstowe.
- Lewy przycisk na ikonie powiadomień ukrywa widoczne widżety. Jeśli wszystkie są ukryte, kolejne kliknięcie przywraca wyłącznie ostatnio ukryte.
- Dwukrotne kliknięcie tarczy przełącza sekundy. W panelu kalendarza z zegarem wskazówkę sekundową przełącza tylko dwuklik bezpośrednio na głównej tarczy. Dodatkowe zegary nie mają sekundnika.
- `F1` otwiera Pomoc, `B` Ustawienia, `M` przełącza Wycisz wszystko, a `Esc` ukrywa widżet lub zatrzymuje aktywny alarm.
- Dwuklik widżetu w Ustawieniach w razie potrzeby go pokazuje, zaznacza `Widoczny` i krótko oznacza go na pulpicie.
- Otwarcie Ustawień z menu widżetu natychmiast go wybiera.
- `Ctrl` lub `Shift` umożliwia wybór wielu pozycji, `Ctrl+A` wybiera wszystkie, a `Del` usuwa wybrane. `Insert` przełącza zaznaczenie bieżącej pozycji i przesuwa kursor listy do następnego wiersza, jak w Total Commanderze.
- Wszystkie skróty listy działają również przy fokusie na Usuń lub Duplikuj. Skrót przenosi fokus na listę i wykonuje akcję. `Ctrl+C` kopiuje wybrane widżety, a `Ctrl+V` dołącza kopie na końcu w kolejności listy. Kopie zawierają wszystkie ustawienia i otrzymują przyrostek nazwy w języku aplikacji. Duplikuj wykonuje tę samą operację bezpośrednio. Limit wynosi 32 widżety. Jeśli nie zmieszczą się wszystkie kopie, dodawane są kolejno te, które się mieszczą, a o pozostałych informuje komunikat.
- `Ctrl+A` lub potrójne kliknięcie pola tekstowego zaznacza cały tekst.

Przy wyborze wielu widżetów ich kontrolki na kartach Ogólne, Wygląd, Alarm i Sygnał są nieaktywne; globalne karty Czas i Aplikacja pozostają dostępne. Ustawienia pamiętają ostatnio otwartą kartę i ostatnio dodany typ widżetu. Na małym obszarze roboczym okno udostępnia w razie potrzeby przewijanie poziome lub pionowe.

Daty można kopiować w 33 formatach: lokalnych, sortowalnych, z dniem lub miesiącem na początku, tekstowych i z dniem tygodnia. Każda maska jest dostępna we wszystkich językach. Domyślny krótki format lokalny zależy od języka widżetu, podobnie jak nazwy miesięcy i dni. Pozycje pokazują maskę i aktualny przykład.

Panel kalendarza z zegarem może wyświetlać dwa dodatkowe zegary. Włącz każdy na karcie Ogólne i wybierz nazwę oraz strefę. Nazwane strefy przestrzegają własnych reguł czasu letniego; stałe przesunięcia UTC nie zmieniają się. Gdy dodatkowe zegary są aktywne, każdy zegar pokazuje lokalny dzień tygodnia pod godziną. Trzy listy rozmiarów na karcie Wygląd sterują kolejno zegarem głównym, Zegarem 1 i Zegarem 2. Prawy przycisk na dodatkowej tarczy pozwala wybrać jej rozmiar. Dodatkowe zegary zawsze pomijają sekundy i dzielą język, format, czcionki oraz przesunięcie widżetu. Dodawanie, usuwanie i zmiana rozmiarów zachowują przywiązanie do tych samych krawędzi obszaru roboczego.

W panelu górna data jest łączem przywracającym kalendarz do dzisiaj; dolny tekst strefy otwiera klasyczne ustawienia Daty i godziny Windows. Oba łącza są dostępne przez `Tab`, pokazują prostokąt fokusu i można je aktywować klawiaturą. Natywny kalendarz pozostaje w pełni interaktywny, ale pomija zbędny w tym układzie wiersz Dzisiaj.

`Wyrównaj do siatki` rozmieszcza widoczne widżety pulpitu w stabilnej siatce bez nakładania, w przybliżeniu zachowując układ ręczny. Widżet, z którego menu uruchomiono polecenie, pozostaje na miejscu; polecenie z obszaru powiadomień układa każdy monitor niezależnie. Zegary na monitorze są wykluczone.

## Wygląd

Dla samodzielnych kalendarzy **Wiersz Dzisiaj** w menu lub na karcie Wygląd kontroluje dolny wiersz. Domyślnie jest zaznaczony; odznaczenie ukrywa wiersz i zmniejsza kalendarz. Wybór zapisuje się dla każdego widżetu osobno. **Przejdź do dzisiaj** pozostaje dostępne i wraca do widoku miesiąca. Przy zmianie daty według czasu widżetu kalendarze automatycznie wybierają dzisiaj, zachowując bieżący widok.

Zmiany wyglądu są natychmiast widoczne na wybranym widżecie. `Anuluj` przywraca niezastosowane zmiany; `Wygląd domyślny` przywraca wartości danego typu.

Zegary cyfrowe, kalendarze i panele mają cztery wspólne style ramki. Prosta ramka ma konfigurowalny kolor; ustawienie szerokości jest dostępne tam, gdzie widżet je obsługuje. Przezroczyste zegary cyfrowe oferują te same style co nieprzezroczyste. Okna czcionek pokazują tylko używane opcje, bez niepotrzebnego podglądu i efektów. Czcionki aplikacji i kalendarza nie mają wyboru rozmiaru; cyfrowe i teksty panelu mają. Natywny kalendarz akceptuje własną czcionkę tylko przy wyłączonych stylach wizualnych kalendarza lub całej aplikacji.

Język aplikacji, czcionka interfejsu, wygładzanie, style wizualne, zapis, start z Windows i przyciąganie do krawędzi są globalne i konfigurowane na karcie Aplikacja. Źródło czasu także jest globalne. Język widżetu, wygładzanie, style, strefa, przesunięcie, alarm i sygnał ustawia się niezależnie. Zastosowanie nowego języka od razu odtwarza otwarte Ustawienia w tym języku. Wygładzanie oferuje **ClearType**, **GDI** i **Brak**. Na karcie Wygląd wygładzanie i wyłączenie motywów znajdują się w tym samym miejscu dla wszystkich typów, z **Wyglądem domyślnym** poniżej.

Suwak **Głośność dźwięku** na karcie Alarm reguluje wewnętrznie odtwarzane pliki osobno dla każdego widżetu i pokazuje poziom w dB. Domyślne **−18 dB** zachowuje poziom oryginalnego pliku (**100%**). Przesunięcie w prawo wzmacnia dźwięk; maksimum **0 dB** odpowiada około **794%** pierwotnej amplitudy. Skrajnie lewa pozycja to **−∞ dB** (cisza). Zmiany działają podczas testu. Dla plików otwieranych w zewnętrznej aplikacji suwak jest nieaktywny. Wzmocnienie dotyczy dekodowanego audio, w tym WAV, MP3, WMA, AAC, M4A i FLAC, jeśli Windows je obsługuje. Starszy sposób odtwarzania plików, których nie można dekodować, np. MIDI, jest ograniczony do 100%.

Dni alarmu uwzględniają pierwszy dzień tygodnia wybranej kultury aplikacji. Zapisane dni zachowują znaczenie przy zmianie języka. Włączenie alarmu z menu bez wybranych dni otwiera kartę Alarm widżetu, zamiast włączać alarm, który nie może zabrzmieć.

Domyślna szerokość ramki zegara cyfrowego wynosi zero. **Zero wiodące** oferuje **Pokaż** (domyślnie), **Zachowaj miejsce** i **Bez miejsca**. **Zachowaj miejsce** ukrywa zero, rezerwując jego rzeczywistą szerokość w danej czcionce. Pozostałe cyfry zachowują pozycje również przy czcionce proporcjonalnej. Zegary cyfrowe na pulpicie wyrównują czas do lewej i zachowują stały rozmiar podczas jego upływu. Zegary na monitorze centrują stały obszar czasu dopasowany do czcionki i formatu, z miejscem na dwie cyfry godziny. Zmiana czasu nie centruje ani nie skaluje tekstu ponownie. Wiersz AM/PM lub UTC jest centrowany niezależnie. Domyślnie zegary na monitorze mają biały tekst na czarnym tle.

## Czas i alarmy

Zegary cyfrowe, panele kalendarza z zegarem i zegary na monitorze oferują **Według języka**, **12 godzin** i **24 godziny** w **Formacie czasu** na karcie Ogólne. Domyślne **Według języka** używa języka widżetu: np. angielski amerykański i australijski stosują 12 godzin, a brytyjski 24. Ręczny wybór pozostaje po zmianie języka. Separatory i oznaczenia AM/PM zależą od kultury; kultury bez własnych oznaczeń używają **AM/PM** w trybie 12-godzinnym.

**AM/PM** jest domyślnie zaznaczone. Odznaczenie ukrywa oznaczenie bez zmiany cyklu 12-godzinnego. W trybie 24-godzinnym i widżetach bez cyfrowego czasu pole jest nieaktywne. Zegary na monitorze pokazują oznaczenie w osobnym wierszu pod czasem, jak UTC. **UTC zawsze używa 24 godzin**; kontrolki cyklu i AM/PM są w UTC nieaktywne, a wybory pozostają zapisane do powrotu na czas lokalny. Ustawienie zera wiodącego nadal określa jego wyświetlanie, ukrycie z miejscem lub pominięcie.

Nazwane strefy pokazują czas urzędowy wybranego miejsca i automatycznie stosują jego reguły czasu letniego. Przesunięcie przy nazwie odpowiada bieżącej dacie i jest odświeżane przy otwieraniu listy. Oddzielne pozycje **UTC** udostępniają stałe przesunięcia od **UTC−12:00** do **UTC+14:00** co 15 minut, bez czasu letniego. Każdy widżet może niezależnie używać strefy lokalnej, dowolnej nazwanej strefy lub stałego przesunięcia UTC.

Każdy widżet może używać dowolnej strefy Windows i przesunięcia ze znakiem w formacie `[-]HH:mm:ss.ff`. Zwarty zapis jest interpretowany od prawej, zaczynając od sekund.

Przesunięcie przydaje się np. w studiu nadawczym do kompensacji opóźnienia toru transmisyjnego. Przyspieszenie zegara o zmierzone opóźnienie pozwala dostarczyć sygnał czasu słuchaczom we właściwej chwili.

CalClock może używać czasu systemowego Windows albo korekty wewnętrznej z serwerów NTP. Wybór jest globalny dla wszystkich widżetów. Synchronizacja nigdy nie zmienia zegara Windows. Po utracie NTP po udanej synchronizacji ostatnia korekta pozostaje aktywna w pamięci procesu. Zmiana serwerów również zachowuje ważną korektę do otrzymania nowej odpowiedzi.

Widżety zegarów obsługują alarmy w wybrane dni; domyślnie aktywne są wszystkie siedem. Alarm pokazuje swój ukryty widżet i przenosi go przed inne okna, nie zmieniając trwale trybu zawsze na wierzchu. WAV, MP3, WMA, MIDI, AAC, M4A i FLAC są rozpoznawane do wewnętrznego odtwarzania raz lub w pętli; rzeczywiste dekodowanie zależy od zainstalowanych składników multimedialnych Windows. Inne pliki i polecenia przekazywane są do Windows asynchronicznie. Alarm może też wywołać adres HTTP lub HTTPS. Niezależnie może używać sześciotonowego sygnału czasu, którego pierwszy krótki ton rozlega się pięć sekund przed ustawioną godziną.

Uruchom plik lub polecenie aktywuje pole, Przeglądaj, Test i powtarzanie. Test i powtarzanie wymagają dodatkowo niepustego pola, ale działający test zawsze można zatrzymać. Test pokazuje sygnalizację wizualną i asynchronicznie sprawdza plik, polecenie, audio oraz adres skryptu zdalnego. Jeśli wybrano sygnał czasu alarmu, odtwarza także pełną sekwencję sześciu tonów; Zatrzymaj test kończy wewnętrzne audio i podgląd sygnału.

Karta Sygnał wyłącza sygnały lub planuje je co 1, 5, 10, 15, 20, 30 albo 60 minut według czasu widżetu. Interwał 20 minut oznacza :00, :20 i :40 tego czasu. Wzorem jest **Greenwich Time Signal (GTS)**: pięć krótkich tonów wyznacza ostatnie pięć sekund, a dłuższy dokładną granicę. Uwzględniane są strefy, UTC, przesunięcia i bieżąca korekta NTP. Sygnał alarmu i karta Sygnał pozostają niezależne; gdy terminy się pokrywają, CalClock odtwarza jedną wspólną sekwencję. Uwzględniane są ułamkowe przesunięcia, a nakładające się tony widżetów, alarmów i testów brzmią nieprzerwanie do końca ostatniego nałożenia.

**Dźwięk sygnału czasu** na karcie Aplikacja oferuje **Wbudowany generator** (domyślny) i **Sygnał systemowy**. Wybór obejmuje wszystkie widżety i sygnały alarmów oraz jest zapisywany globalnie. Dla **Wbudowanego generatora** suwak **Głośność sygnału czasu** pokazuje poziom w dB dla całej aplikacji. Prawy skraj to **0 dB**, maksymalna niezniekształcona amplituda sinusoidy; cisza to **−∞ dB**. Domyślna głośność wynosi **−18 dB**. Skala decybelowa ma −18 dB pośrodku. Generator zaczyna i kończy tony w przejściu przez zero, także przy zatrzymaniu testu. Bieżący ton może się zakończyć; długi może trwać jeszcze do pół sekundy. **Test** obok **Dźwięku sygnału czasu** uruchamia ciągły podgląd, **Zatrzymaj test** go kończy. Można testować obydwa sposoby; stan testu nie jest zapisywany. Trzymanie suwaka głośności również uruchamia podgląd do puszczenia myszy, chyba że trwa test włączony przyciskiem. Odtwarzanie rozpoczyna się w następnej pełnej sekundzie: krótkie tony co sekundę, długi o :00, :05, :10 itd. Podgląd i jednoczesne sygnały widżetów lub alarmów dzielą jeden ton. Przy **Sygnale systemowym** nieaktywny jest tylko suwak głośności. Wybór dźwięku jest dostępny wyłącznie wtedy, gdy system obsługuje obie możliwości.

Alarm i sygnał można także przełączać w menu widżetu obsługującego dźwięk. Pozycja alarmu pokazuje godzinę oraz aktywne dni, jeśli nie wybrano wszystkich. Zaznaczone Wycisz dotyczy widżetu i odpowiada polu na karcie Ogólne. Samodzielny Kalendarz nie ma alarmu, sygnału ani wyciszenia, więc te polecenia są pomijane lub nieaktywne. W obszarze powiadomień polecenie nazywa się Wycisz wszystko; `M` na dowolnym widżecie wykonuje tę samą globalną zmianę. Globalne przywrócenie dźwięku dotyczy tylko widżetów wyciszonych poprzednią akcją globalną. Wewnętrzne audio trwa bezgłośnie i staje się słyszalne po wyłączeniu wyciszenia. Rozpoczęty ton może się skończyć; następne są pomijane do włączenia dźwięku. Polecenia niedźwiękowe i zdalne skrypty pozostają bez zmian.

## Ustawienia i menu

`Zapisz` stosuje zmiany i zamyka Ustawienia, `Zastosuj` stosuje je bez zamykania, a `Anuluj` odrzuca niezastosowane zmiany wraz z podglądem wyglądu. Enter uruchamia `Zapisz`, Esc `Anuluj`.

Każde menu widżetu zawiera polecenia właściwe dla typu — widoczność, zawsze na wierzchu, sekundy, rozmiar analogowy lub format kopiowanej daty — a potem `Wyrównaj do siatki`, Ustawienia, Pomoc, Informacje i Zakończ. Menu powiadomień wymienia widżety z numerami, a następnie Pokaż wszystko, Ukryj wszystko i Wycisz wszystko. Oddzielona pozycja `Wyrównaj do siatki` poprzedza polecenia aplikacji.

Pokazanie lub przywrócenie widżetów przenosi je przed inne okna bez zmiany stanu zawsze na wierzchu. CalClock zapewnia co najmniej jeden widoczny widżet po starcie. Drugie uruchomienie aktywuje istniejącą instancję i przywraca ostatnio ukryte widżety, jeśli żaden nie jest widoczny. Po restarcie Eksploratora Windows ikona powiadomień rejestruje się automatycznie ponownie. Jeśli `ClockWndMain` nie obsługuje sekundnika w danym rozmiarze, Sekundy są nieaktywne, ale wybór pozostaje zapisany dla innego obsługiwanego rozmiaru.

## Zapis ustawień

Domyślnie ustawienia są zapisywane pod:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

Zapis XML można włączyć w Ustawieniach. Używa on:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Po udanym zapisie XML CalClock usuwa swój stan z rejestru. Powrót do rejestru analogicznie usuwa automatyczny XML i puste katalogi CalClock. Import XML natychmiast ładuje i zapisuje ustawienia w wybranym magazynie, nie zmieniając typu zapisu. Wyciszenie zapisuje się oddzielnie dla każdego widżetu z dźwiękiem. Start z Windows jest zapisywany jako wartość `CalClock` w standardowym kluczu `Run` bieżącego użytkownika.

## Kompilacja

Wymagania:

- Microsoft Visual Studio z zestawem narzędzi MSVC v145
- Windows SDK

Otwórz `CalClock.slnx`, wybierz `Release | Win32` i skompiluj rozwiązanie. Plik wykonywalny powstaje jako:

```text
Release\CalClock.exe
```

Obsługiwana jest tylko konfiguracja Win32/x86. Projekt celowo nie udostępnia x64, ponieważ integracja z kontrolką zegara Windows wymaga zgodności x86.

## Licencja

CalClock jest dostępny na [licencji MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
