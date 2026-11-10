# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · **Polski** · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

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
- Interfejs w 36 wersjach językowych; niezależny wybór języka aplikacji i każdego widżetu

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
- W widżetach Zegar analogowy i Kalendarz z zegarem klawisze `Alt+0`, `Alt+1`, `Alt+2` i `Alt+3` wybierają rozmiar głównej tarczy od najmniejszego do największego.
- Dwuklik widżetu w Ustawieniach w razie potrzeby go pokazuje, zaznacza `Widoczny` i krótko oznacza go na pulpicie.
- Otwarcie Ustawień z menu widżetu natychmiast go wybiera.
- Usuń lub Del usuwa wszystkie zaznaczone pozycje po zastosowaniu zmian. `Insert` przełącza zaznaczenie bieżącej pozycji i przesuwa kursor listy o jeden wiersz w dół.
- `Ctrl+C` kopiuje wybrane widżety, a `Ctrl+V` dołącza kopie na końcu w kolejności listy. Kopie zawierają wszystkie ustawienia i otrzymują przyrostek nazwy w języku aplikacji. Duplikuj wykonuje tę samą operację bezpośrednio. Limit wynosi 32 widżety. Jeśli nie zmieszczą się wszystkie kopie, dodawane są kolejno te, które się mieszczą, a o pozostałych informuje komunikat.

Otwarcie ustawień z ikony w obszarze powiadomień przywraca ostatnio wybrany widżet.

Ustawienia pamiętają ostatnio otwartą kartę i ostatnio dodany typ widżetu.

Daty można kopiować w 33 formatach: lokalnych, sortowalnych, z dniem lub miesiącem na początku, tekstowych i z dniem tygodnia. Każda maska jest dostępna we wszystkich językach. Domyślny krótki format lokalny zależy od języka widżetu, podobnie jak nazwy miesięcy i dni. Pozycje pokazują maskę i aktualny przykład.

Panel kalendarza z zegarem może wyświetlać dwa dodatkowe zegary. Włącz każdy na karcie Ogólne i wybierz nazwę oraz strefę. Nazwane strefy przestrzegają własnych reguł czasu letniego; stałe przesunięcia UTC nie zmieniają się. Gdy dodatkowe zegary są aktywne, każdy zegar pokazuje lokalny dzień tygodnia pod godziną. Trzy listy rozmiarów na karcie Wygląd sterują kolejno zegarem głównym, Zegarem 1 i Zegarem 2. Prawy przycisk na dodatkowej tarczy pozwala wybrać jej rozmiar. Dodatkowe zegary zawsze pomijają sekundy i dzielą język, format, czcionki oraz przesunięcie widżetu. Dodawanie, usuwanie i zmiana rozmiarów zachowują przywiązanie do tych samych krawędzi obszaru roboczego.

W panelu górna data jest łączem przywracającym kalendarz do dzisiaj; dolny tekst strefy otwiera klasyczne ustawienia Daty i godziny Windows.

Panele kalendarza z zegarem mogą wyświetlać powiadomienia systemu Windows o dacie i godzinie nad dolnym łączem. Opcja **Powiadomienia o dacie i godzinie** na karcie **Ogólne** jest domyślnie włączona i zapisywana osobno dla każdego panelu. Jeśli ma zastosowanie kilka powiadomień, są one wyświetlane jedno pod drugim, tak jak w systemie Windows. Gdy opcja jest wyłączona lub nie ma odpowiedniego powiadomienia, panel zachowuje pierwotny rozmiar i układ, bez rezerwowania pustego miejsca.

`Ułóż w siatce` rozmieszcza widoczne widżety pulpitu w stabilnej siatce bez nakładania, w przybliżeniu zachowując układ ręczny. Widżet, z którego menu uruchomiono polecenie, pozostaje na miejscu; polecenie z obszaru powiadomień układa każdy monitor niezależnie. Zegary na monitorze są wykluczone.

## Wygląd

Dla samodzielnych kalendarzy **Wiersz Dzisiaj** w menu lub na karcie Wygląd kontroluje dolny wiersz. Domyślnie jest zaznaczony; odznaczenie ukrywa wiersz i zmniejsza kalendarz. Wybór zapisuje się dla każdego widżetu osobno. **Przejdź do dnia dzisiejszego** pozostaje dostępne i wraca do widoku miesiąca. Gdy data zmienia się według czasu widżetu, kalendarz przechodzi na nowy dzień tylko wtedy, gdy dzisiejszy dzień jest wybrany i widoczny w widoku miesiąca. Ręcznie wybrana data i inny widok pozostają zachowane; oznaczenie i wiersz Dzisiaj są zawsze aktualizowane.

Zmiany wyglądu są od razu widoczne w podglądzie wybranego widżetu. `Wygląd domyślny` przywraca domyślne wartości dla tego typu widżetu. Przy zamykaniu ustawień z niezastosowanymi zmianami pojawia się pytanie o ich zapisanie. Ostrzeżenie jest domyślnie włączone i można je wyłączyć na karcie Aplikacja.

Zegary cyfrowe, kalendarze i panele mają cztery wspólne style ramki. Prosta ramka ma konfigurowalny kolor; ustawienie szerokości jest dostępne tam, gdzie widżet je obsługuje. Przezroczyste zegary cyfrowe oferują te same style co nieprzezroczyste. Czcionki aplikacji i kalendarza nie mają wyboru rozmiaru; cyfrowe i teksty panelu mają. Własne czcionki kalendarza są obsługiwane przy klasycznym wyglądzie systemu Windows lub po wyłączeniu motywów dla widżetu.

Język aplikacji, czcionka interfejsu, wygładzanie, zapis, start z Windows i przyciąganie do krawędzi są globalne i konfigurowane na karcie Aplikacja. Wyłączenie motywów na karcie Aplikacja dotyczy tylko okien Ustawienia, Pomoc, O programie i Kalkulator czasu. Każdy widżet korzysta z własnego ustawienia motywów. Źródło czasu także jest globalne. Język widżetu, wygładzanie, style, strefa, przesunięcie, alarm i sygnał ustawia się niezależnie. Wygładzanie oferuje **ClearType**, **GDI** i **Brak**.

Styl Windows 2000 jest dostępny po wyłączeniu motywów i dotyczy tylko okien Ustawienia, Pomoc, O programie i
Kalkulator czasu. Przy domyślnej czcionce systemowej elementy sterujące tych okien używają czcionki Tahoma 8
pt; własna czcionka aplikacji ma pierwszeństwo. Dostępne jest wygładzanie GDI lub Brak. Zapisany wybór
ClearType jest tymczasowo zastępowany przez GDI i przywracany po wyłączeniu tego stylu. Gdy Windows używa
wyglądu klasycznego, obie opcje wyglądu są nieaktywne i nie są stosowane; zapisane wybory pozostają zachowane.

Suwak **Głośność dźwięku** na karcie Alarm reguluje wewnętrznie odtwarzane pliki osobno dla każdego widżetu i pokazuje poziom w dB. Domyślne **−18 dB** zachowuje poziom oryginalnego pliku (**100%**). Przesunięcie w prawo wzmacnia dźwięk; maksimum **0 dB** odpowiada około **794%** pierwotnej amplitudy. Skrajnie lewa pozycja to **−∞ dB** (cisza). Zmiany działają podczas testu. Wzmocnienie dotyczy dekodowanego audio, w tym WAV, MP3, WMA, AAC, M4A i FLAC, jeśli Windows je obsługuje. Starszy sposób odtwarzania plików, których nie można dekodować, np. MIDI, jest ograniczony do 100%.

Dni alarmu uwzględniają pierwszy dzień tygodnia wybranej kultury aplikacji. Zapisane dni zachowują znaczenie przy zmianie języka. Włączenie alarmu z menu bez wybranych dni otwiera kartę Alarm widżetu, zamiast włączać alarm, który nie może zabrzmieć.

**Zero wiodące** oferuje **Tak** (domyślnie), **Nie, zachowaj miejsce** i **Nie, bez miejsca**. **Nie, zachowaj miejsce** ukrywa zero, rezerwując jego rzeczywistą szerokość w danej czcionce. Pozostałe cyfry zachowują pozycje również przy czcionce proporcjonalnej. Domyślnie zegary na monitorze mają biały tekst na czarnym tle.

## Kalkulator czasu

Otwórz Kalkulator czasu z menu dowolnego widżetu lub ikony w obszarze powiadomień. Karta Przedział czasu
oblicza różnicę między dwiema datami i godzinami. Karta Okrągłe wartości wyróżnia w kalendarzu okrągłe
wartości, powtarzające się cyfry oraz miesięcznice i rocznice od wybranego początku. Karta Zapisane daty i
godziny umożliwia dodawanie, edycję, sortowanie i usuwanie dat i godzin z opisem. Daty i godziny są zapisywane
osobno w `%APPDATA%\FortSoft\CalClock\times.xml`. Eksport ustawień uwzględnia te wpisy. Import zachowuje
istniejące wpisy i pomija tylko te z tą samą chwilą UTC i identycznym pełnym opisem, niezależnie od strefy
wyświetlania.

Kalendarz śledzi bieżący dzień przy przejściu przez północ w strefie czasowej początku, gdy dzisiejszy dzień jest wybrany i widoczny w widoku miesiąca. Ręcznie wybrana data i inny widok pozostają zachowane; oznaczenie i wiersz Dzisiaj są zawsze aktualizowane.

Każde pole ma własną strefę czasową z tej samej listy co w Ustawieniach. Domyślna jest bieżąca strefa Windows.
Zapisywane są jednoznaczna chwila w UTC i strefa wyświetlania. Zmiana strefy zachowuje chwilę. Dla powtórzonej
godziny wybierz przesunięcie UTC; nieistniejącego czasu lokalnego nie można zapisać. Godziny mierzą upływ
czasu, a obliczenia kalendarzowe używają strefy początku. Teraz używa czasu systemowego Windows bez
przesunięcia widżetu, wyświetlanego w wybranej strefie.

Import przyjmuje również osobny plik XML z zapisanymi datami i godzinami; scala te wpisy bez zmiany ustawień
aplikacji.

Na karcie Wyróżnianie można wybrać reguły wyróżniania dat w kalendarzu. Domyślnie wyróżniane są dzień
początkowy (wartości zerowe), okrągłe wartości zakończone zerami, pierwszych dziewięć pełnych tygodni oraz
miesięcznice i rocznice. Powtarzające się cyfry 1–9 (na przykład 11, 111 lub 66, 666) można włączać osobno;
domyślnie są wyłączone.

Kliknij nagłówek kolumny, aby posortować zapisane dane według rzeczywistego momentu lub tekstu opisu. Kolejne
kliknięcie odwraca kolejność; strzałka wskazuje kierunek sortowania.

Położenie okna, aktywna karta, dane wejściowe obliczeń i opcje wyróżniania są zapisywane z ustawieniami
aplikacji w rejestrze lub pliku XML, zgodnie z wybranym magazynem ustawień.

Eksport na karcie zapisanych dat i godzin zapisuje tylko te wpisy w osobnym pliku XML. Import na tej karcie
odczytuje tylko daty i godziny, również z eksportu ustawień, i scala je z istniejącymi wpisami.

## Czas i alarmy

Zegary cyfrowe, panele kalendarza z zegarem i zegary na monitorze oferują **Według języka**, **12 godzin** i **24 godziny** w **Formacie czasu** na karcie Ogólne. Domyślne **Według języka** używa języka widżetu: np. angielski amerykański i australijski stosują 12 godzin, a brytyjski 24. Ręczny wybór pozostaje po zmianie języka. Separatory i oznaczenia AM/PM zależą od kultury; kultury bez własnych oznaczeń używają **AM/PM** w trybie 12-godzinnym.

**AM/PM** jest domyślnie zaznaczone. Odznaczenie ukrywa oznaczenie bez zmiany cyklu 12-godzinnego. Zegary na monitorze pokazują oznaczenie w osobnym wierszu pod czasem, jak UTC. UTC zawsze używa formatu 24-godzinnego. Ustawienie zera wiodącego nadal określa jego wyświetlanie, ukrycie z miejscem lub pominięcie.

Nazwane strefy pokazują czas urzędowy wybranego miejsca i automatycznie stosują jego reguły czasu letniego. Przesunięcie przy nazwie odpowiada bieżącej dacie i jest odświeżane przy otwieraniu listy. Oddzielne pozycje **UTC** udostępniają stałe przesunięcia od **UTC−12:00** do **UTC+14:00** co 15 minut, bez czasu letniego. Każdy widżet może niezależnie używać strefy lokalnej, dowolnej nazwanej strefy lub stałego przesunięcia UTC.

Nowe widżety domyślnie używają opcji **Bieżąca strefa czasowa systemu Windows**, która śledzi bieżącą strefę Windows oraz ustawienie automatycznej zmiany czasu letniego. Istniejące widżety zachowują wybrane strefy. Opcja określa strefę czasową; wspólne źródło czasu Windows lub NTP pozostaje niezależne.

Każdy widżet może używać dowolnej strefy Windows i przesunięcia ze znakiem w formacie `[-]HH:mm:ss.ff`. Zwarty zapis jest interpretowany od prawej, zaczynając od sekund.

Przesunięcie przydaje się np. w studiu nadawczym do kompensacji opóźnienia toru transmisyjnego. Przyspieszenie zegara o zmierzone opóźnienie pozwala dostarczyć sygnał czasu słuchaczom we właściwej chwili.

Przesunięcie widżetu jest stosowane do UTC przed przeliczeniem na jego strefę czasową, więc przesuwa również moment zmiany czasu. Zegar przyspieszony o dziesięć sekund zmienia czas dziesięć sekund wcześniej, a opóźniony o dziesięć sekund — dziesięć sekund później. Wskazówki, wyświetlacz cyfrowy, daty kalendarza, budziki i sygnały czasu korzystają z otrzymanego czasu.

Karta Czas wybiera dla całej aplikacji, a więc dla wszystkich widżetów, czas systemowy Windows albo skonfigurowane serwery NTP. NTP koryguje wyłącznie czas wyświetlany przez CalClock; zegar Windows nigdy nie jest zmieniany. Do pierwszej prawidłowej odpowiedzi używany jest czas systemowy. NTP jest ustawieniem domyślnym. Zestaw automatyczny wybiera według regionu systemu serwery czeskie i słowackie, PTB dla Europy albo pulę globalną. Wiele pomiarów jest filtrowanych według opóźnienia sieci i wartości odstających. Synchronizuj teraz natychmiast rozpoczyna nowy pomiar.

Po synchronizacji zegar CalClock odmierza czas niezależnie od późniejszych zmian czasu systemowego Windows. Po utracie połączenia lub zmianie serwerów kontynuuje odmierzanie od ostatniej prawidłowej synchronizacji do uzyskania nowej odpowiedzi; stan ten jest zachowywany do zamknięcia aplikacji.

Karta Czas rejestruje zapytania do serwerów NTP od uruchomienia aplikacji. Każdy wpis zawiera datę i lokalny czas komputera, serwer oraz stan. OK oznacza prawidłową odpowiedź, a θ jej odchylenie od czasu systemowego Windows. ERR podaje przyczynę niepowodzenia i ewentualny kod błędu. Ostatni wpis grupy zapytań zawiera również obliczone odchylenie Θ, jeśli dostępne są użyteczne pomiary.

Odchylenia są wyświetlane w milisekundach z czterema miejscami po przecinku. Wartość dodatnia oznacza, że zegar serwera wyprzedza Windows; ujemna oznacza, że jest opóźniony. Θ uwzględnia zaakceptowane pomiary i jest również widoczne w stanie synchronizacji.

Zapisz dziennik eksportuje wpisy do CSV wraz z odchyleniami i szczegółami błędów. Wpisy nie są zachowywane między uruchomieniami; zapisz je przed zamknięciem aplikacji, jeśli chcesz je zachować.

Widżety zegarów obsługują alarmy w wybrane dni; domyślnie aktywne są wszystkie siedem. Alarm pokazuje swój ukryty widżet i przenosi go przed inne okna, nie zmieniając trwale trybu zawsze na wierzchu. WAV, MP3, WMA, MIDI, AAC, M4A i FLAC są rozpoznawane do wewnętrznego odtwarzania raz lub w pętli; rzeczywiste dekodowanie zależy od zainstalowanych składników multimedialnych Windows. Inne pliki i polecenia przekazywane są do Windows asynchronicznie. Alarm może też wywołać adres HTTP lub HTTPS. Niezależnie może używać sześciotonowego sygnału czasu, którego pierwszy krótki ton rozlega się pięć sekund przed ustawioną godziną.

Sygnały dźwiękowe budzika są planowane według rzeczywistego momentu najbliższego budzika po przeliczeniu strefy i uwzględnieniu przesunięcia widżetu. Zaczynają się pięć rzeczywistych sekund przed tym momentem, także gdy wyświetlany zegar przeskakuje bezpośrednio do godziny budzika. Dla godziny pominiętej wiosną nie uruchamia się budzik ani jego sygnały. Podczas godziny powtarzanej jesienią budzik i jego sygnały uruchamiają się tylko raz dla tej samej daty i ustawionej godziny.

Jeśli CalClock pozostaje uruchomiony, po uśpieniu, hibernacji lub opóźnieniu przetwarzania każdy widżet jednokrotnie uruchamia ostatni pominięty alarm wraz ze skonfigurowanymi działaniami. Ponowne uruchomienie CalClock nie odtwarza dawnych alarmów; pominięte sygnały czasu i sygnały poprzedzające alarm nie są odtwarzane z opóźnieniem. Opcja „Wybudź komputer na alarm” jest domyślnie wyłączona i wymaga uruchomionego CalClock oraz obsługi przez Windows i sprzęt; powolne wybudzanie może uniemożliwić sygnały poprzedzające alarm na czas.

Gdy alarm jest wyłączony, pozostałe pola na karcie Alarm są nieaktywne, ale zachowują ustawione wartości. Test jest dostępny po włączeniu alarmu i opcji Uruchom plik lub polecenie oraz wpisaniu pliku lub polecenia.

Test pokazuje sygnalizację wizualną i asynchronicznie sprawdza plik, polecenie, audio oraz adres skryptu zdalnego. Test nie odtwarza sygnałów poprzedzających alarm. Zatrzymaj test kończy wewnętrzne audio i sygnalizację wizualną.

Karta Sygnał zawiera pole Sygnał czasu aktywny oraz przyciski opcji dla odstępów 1, 5, 10, 15, 20, 30 lub 60 minut według czasu wyświetlanego przez widżet. Początkowo sygnał jest wyłączony i wybrany jest odstęp jednej godziny. Wyłączenie i włączenie opcji Sygnał w menu widżetu zachowuje odstęp. Menu pokazuje godzinę alarmu i odstęp sygnału w nawiasach. Interwał 20 minut oznacza :00, :20 i :40 tego czasu. Wzorem jest **Greenwich Time Signal (GTS)**: pięć krótkich tonów wyznacza ostatnie pięć sekund, a dłuższy dokładną granicę. Uwzględniane są strefy, UTC, przesunięcia i bieżąca korekta NTP. Sygnał alarmu i karta Sygnał pozostają niezależne. Uwzględniane są ułamkowe przesunięcia, a nakładające się tony widżetów, alarmów i testów brzmią nieprzerwanie do końca ostatniego nałożenia na tym samym wyjściu dźwięku.

**Dźwięk sygnału czasu** na karcie Aplikacja oferuje **Wbudowany generator** (domyślny) i **Sygnał systemowy**. Wybór obejmuje wszystkie widżety i sygnały alarmów oraz jest zapisywany globalnie. Dla **Wbudowanego generatora** suwak **Głośność sygnału czasu** pokazuje poziom w dB dla całej aplikacji. Prawy skraj to **0 dB**, maksymalna niezniekształcona amplituda sinusoidy; cisza to **−∞ dB**. Domyślna głośność wynosi **−18 dB**. Bieżący ton może się zakończyć. **Testuj** obok **Dźwięku sygnału czasu** uruchamia ciągły podgląd, **Zatrzymaj test** go kończy. Można testować obydwa sposoby; stan testu nie jest zapisywany. Trzymanie suwaka głośności również uruchamia podgląd do puszczenia myszy, chyba że trwa test włączony przyciskiem. Odtwarzanie rozpoczyna się w następnej pełnej sekundzie: krótkie tony co sekundę, długi o :00, :05, :10 itd. Wybór dźwięku jest dostępny wyłącznie wtedy, gdy system obsługuje obie możliwości.

**Wyjście dźwięku**

**Wyjście dźwięku** na karcie **Sygnał** wybiera urządzenie dla regularnych sygnałów czasu każdego widżetu
obsługującego dźwięk. Strefa czasowa, przesunięcie i interwał widżetu pozostają bez zmian. Wybór generatora i głośność
nadal są globalne na karcie **Aplikacja**. Przy opcji **Sygnał systemowy** pole jest wyszarzone i pokazuje domyślne urządzenie Windows, zachowując poprzedni wybór w ustawieniach; **Wbudowany generator** ponownie je uaktywnia. Windows Vista automatycznie używa
generatora.

**Domyślne urządzenie Windows** śledzi bieżące domyślne wyjście Windows. Urządzenie wybrane bezpośrednio pozostaje
wybrane po odłączeniu i jest oznaczone jako **Urządzenie niedostępne**; jego sygnały pozostają wyciszone, dopóki nie
będzie dostępne lub nie zostanie wybrane inne wyjście. Lista urządzeń jest odświeżana po rozwinięciu. Wybór jest
zapisywany osobno dla każdego widżetu w rejestrze lub ustawieniach XML.

Sygnały są automatycznie łączone na każdym wyjściu. Urządzenie wybrane bezpośrednio i wskazująca je opcja
Domyślne urządzenie Windows współdzielą jedno wyjście. Różne urządzenia działają niezależnie; zachowane są
sinusoida, ciągłość fazy oraz początek i koniec tonów w zerze. Wyjście dźwięku testu na karcie Aplikacja
zapamiętuje urządzenie do testów generatora i podglądu głośności. Przy sygnale systemowym ta lista jest nieaktywna i pokazuje domyślne urządzenie Windows; zapisany wybór zostaje zachowany.
Dźwięk alarmu i sygnały poprzedzające alarm używają domyślnego wyjścia Windows. Tylko sygnały poprzedzające alarm łączą się z regularnymi sygnałami na tym samym wyjściu.

Alarm i sygnał można także przełączać w menu widżetu obsługującego dźwięk. Pozycja alarmu pokazuje godzinę oraz aktywne dni, jeśli nie wybrano wszystkich. Zaznaczone Wycisz dotyczy widżetu i odpowiada polu na karcie Ogólne. Samodzielny Kalendarz nie obsługuje alarmu, sygnału czasu ani wyciszenia. W obszarze powiadomień polecenie nazywa się Wycisz wszystko; `M` na dowolnym widżecie wykonuje tę samą globalną zmianę. Globalne przywrócenie dźwięku dotyczy tylko widżetów wyciszonych poprzednią akcją globalną. Wewnętrzne audio trwa bezgłośnie i staje się słyszalne po wyłączeniu wyciszenia. Rozpoczęty ton może się skończyć; następne są pomijane do włączenia dźwięku. Polecenia niedźwiękowe i zdalne skrypty pozostają bez zmian.

## Ustawienia i menu

Każde menu widżetu zawiera polecenia właściwe dla typu — widoczność, zawsze na wierzchu, sekundy, rozmiar
analogowy lub format kopiowanej daty — a potem `Ułóż w siatce`, Kalkulator czasu, Ustawienia, Pomoc, O
programie i Zakończ. Menu powiadomień wymienia widżety z numerami, a następnie Pokaż wszystkie, Ukryj
wszystkie i Wycisz wszystko. Oddzielona pozycja `Ułóż w siatce` poprzedza polecenia aplikacji.

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

Import XML natychmiast ładuje i zapisuje ustawienia w wybranym magazynie, nie zmieniając typu zapisu. Wyciszenie zapisuje się oddzielnie dla każdego widżetu z dźwiękiem.

## Kompilacja

Wymagania:

- Microsoft Visual Studio z zestawem narzędzi MSVC v145
- Windows SDK

Otwórz `CalClock.slnx`, wybierz `Release | x86` i skompiluj rozwiązanie. Plik wykonywalny powstaje jako:

```text
Release\CalClock.exe
```

Obsługiwana jest tylko konfiguracja Win32/x86. Projekt celowo nie udostępnia x64, ponieważ integracja z kontrolką zegara Windows wymaga zgodności x86.

Po kompilacji uruchom `.\PackageRelease.ps1`, aby utworzyć pakiet `CalClock-<version>-win32.zip` zawierający program i
jego licencję.

Domyślne wartości parametrów podpisywania są również odczytywane ze zmiennych środowiskowych użytkownika Windows:
`BUILD_SIGNER_NAME`, `BUILD_CERTIFICATE_THUMBPRINT`, `BUILD_SIGNTOOL_PATH`, `BUILD_TIMESTAMP_SERVER`. Jawne argumenty
wiersza poleceń mają pierwszeństwo.

## Licencja

CalClock jest dostępny na [licencji MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
