# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · **Slovenčina** · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md)

CalClock je natívna aplikácia Win32/x86 pre Windows Vista a novšie verzie, ktorá na pracovnej ploche Windows zobrazuje samostatne nastaviteľné plávajúce hodiny a kalendáre. Beží v oblasti oznámení a nepotrebuje trvalo otvorené ovládacie okno.

## Funkcie

- Až 32 samostatne nastaviteľných widgetov
- Vlastný jazyk, časové pásmo, časový posun, viditeľnosť a stav vždy navrchu pre každý widget
- Ručičkové hodiny využívajúce ovládací prvok Windows `ClockWndMain`, s automaticky zistenými podporovanými veľkosťami a podporou sekundovej ručičky
- Nastaviteľné digitálne hodiny s písmom, farbami, nepriehľadnosťou, vnútorným odsadením, rámčekom, voliteľnou úvodnou nulou a priehľadným pozadím
- Natívne kalendáre Windows s výberom dátumu, štyrmi štýlmi rámčeka, nastaviteľnou farbou rámčeka, číslami týždňov, prvým dňom týždňa a 33 formátmi kopírovania
- Kalendáre s hodinami a až dvomi ďalšími pomenovanými hodinami v samostatných pásmach, samostatnými veľkosťami ciferníkov, štyrmi štýlmi rámčeka, nastaviteľnou farbou, textom UTC, úvodnou nulou a samostatným písmom každého textového riadka
- Budíky s výberom dní, vizuálnou signalizáciou, interným prehrávaním zvuku, opakovaním, miestnymi príkazmi a volaním skriptov cez HTTP/HTTPS
- Časové znamenie pre jednotlivé hodiny každú 1, 5, 10, 15, 20, 30 alebo 60 minút; súčasné znamenia sa zlúčia do jednej sekvencie
- Príkaz Stlmené pre jednotlivé hodiny a zaškrtávací príkaz Stlmiť všetko v oblasti oznámení
- Voliteľné automatické spúšťanie s Windows
- Voliteľné prichytávanie k okrajom pracovnej plochy pri ťahaní v dosahu piatich pixelov, predvolene zapnuté; prichytenie sa zachováva pri zmene veľkosti
- Synchronizácia NTP bez zmeny systémového času Windows
- Predvoľby serverov NTP pre Česko a Slovensko, PTB, Ubuntu/NTP Pool a vlastné servery
- Ukladanie nastavení do registra alebo XML vrátane importu a exportu XML
- Ovládanie z oblasti oznámení s obnovením naposledy skrytých widgetov
- Identifikácia widgetov a stabilné zarovnanie do neprekrývajúcej sa mriežky
- Priebežný náhľad vzhľadu s možnosťou zrušenia a predvoleným vzhľadom pre každý widget
- Písma aplikácie a widgetov, motívy a vyhladzovanie ClearType, GDI alebo žiadne
- Rozhranie v češtine, americkej, britskej a austrálskej angličtine, nemčine, francúzštine, španielčine, taliančine, portugalčine, poľštine, slovenčine, dánčine, fínčine, islandčine, nórčine, švédčine a turečtine

## Typy widgetov

| Widget | Popis |
| --- | --- |
| Ručičkové hodiny | Plávajúci ciferník Windows s veľkosťami a voliteľnou sekundovou ručičkou podporovanými aktuálnou verziou Windows |
| Digitálne hodiny | Nastaviteľné plávajúce digitálne hodiny s voliteľným textom UTC, úvodnou nulou, rámčekom a priehľadným pozadím |
| Kalendár | Presúvateľný natívny mesačný kalendár s výberom dátumu, nastaviteľným rámčekom a formátmi kopírovania |
| Kalendár s hodinami | Kombinovaný panel s natívnym kalendárom, ručičkovými hodinami, nastaviteľnými textovými riadkami, UTC a rámčekom |
| Hodiny na monitore | Digitálne hodiny vypĺňajúce jeden alebo viac zvolených monitorov, s voliteľným zatemnením a UTC na samostatnom riadku |

Pri prvom spustení CalClock vyberie jazyk podľa používateľského rozhrania Windows. Ak nie je podporovaný, použije americkú angličtinu. Predvolene vytvorí jedny viditeľné ručičkové hodiny. Každý widget si medzi spusteniami uchováva polohu a nastavenia. Pri otvorených Nastaveniach hodiny na monitore vždy zastupuje presúvateľný náhľad s pomerom strán vybraného monitora. `Esc` skryje hodiny na monitore aj ich zatemnenie, a to aj pri aktívnych Nastaveniach. Ukazovateľ sa po krátkej nečinnosti nad hodinami na monitore a zatemnenými monitormi skryje a po pohybe myši znovu zobrazí. Nad malým náhľadom v Nastaveniach zostáva viditeľný.

## Ovládanie

- Hodiny alebo panel presuňte ťahaním ľavým tlačidlom myši.
- Samostatný kalendár presuňte ťahaním za jeho voľnú plochu.
- Pravým tlačidlom na widgete alebo ikone v oblasti oznámení otvorte kontextovú ponuku.
- Ľavým tlačidlom na ikone v oblasti oznámení skryjete viditeľné widgety. Ak sú všetky skryté, ďalším kliknutím obnovíte len naposledy skryté.
- Dvojklik na ciferník prepína sekundy. V kalendári s hodinami sekundovú ručičku prepína iba dvojklik priamo na hlavný ciferník. Ďalšie hodiny sekundovú ručičku nemajú.
- `F1` otvorí Pomocníka, `B` Nastavenia, `M` prepne Stlmiť všetko a `Esc` skryje widget alebo zastaví aktívny budík.
- Dvojklik na widget v Nastaveniach ho podľa potreby zobrazí, zaškrtne `Zobrazené` a krátko označí na ploche.
- Otvorenie Nastavení z ponuky widgetu tento widget okamžite vyberie.
- Pomocou `Ctrl` alebo `Shift` vyberiete viac položiek, `Ctrl+A` vyberie všetky a `Del` odstráni vybrané. `Insert` prepne výber aktuálnej položky a posunie kurzor zoznamu na ďalší riadok ako v Total Commanderi.
- Všetky skratky zoznamu fungujú aj pri fokuse na Odobrať alebo Duplikovať. Skratka presunie fokus do zoznamu a vykoná akciu. `Ctrl+C` skopíruje vybrané widgety a `Ctrl+V` pripojí kópie na koniec v poradí zoznamu. Kópie obsahujú všetky nastavenia a dostanú príponu názvu v jazyku aplikácie. Duplikovať vykoná rovnakú operáciu priamo. Povolených je najviac 32 widgetov. Ak sa nezmestia všetky kópie, pridajú sa v poradí len tie, ktoré sa zmestia, a správa upozorní na ostatné.
- `Ctrl+A` alebo trojklik v textovom poli vyberie celý text.

Pri výbere viacerých widgetov sú ich ovládacie prvky na kartách Všeobecné, Vzhľad, Budík a Znamenie neaktívne; globálne karty Čas a Aplikácia zostávajú dostupné. Nastavenia si pamätajú poslednú otvorenú kartu a naposledy pridaný typ widgetu. Na malej pracovnej ploche umožňuje okno podľa potreby vodorovné alebo zvislé posúvanie.

Dátumy možno kopírovať v 33 formátoch: miestnych, zoraditeľných, s dňom alebo mesiacom na začiatku, slovných a s dňom v týždni. Každá maska je dostupná vo všetkých jazykoch. Predvolený miestny krátky formát sa riadi jazykom widgetu, rovnako ako názvy mesiacov a dní. Položky zobrazujú masku a aktuálny príklad.

Kalendár s hodinami môže zobrazovať až dvoje ďalšie hodiny. Každé zapnite na karte Všeobecné a vyberte názov a pásmo. Pomenované pásma dodržiavajú vlastné pravidlá letného času; pevné posuny UTC sa nemenia. Ak sú ďalšie hodiny zapnuté, pod časom každých hodín sa zobrazuje ich miestny deň v týždni. Tri zoznamy veľkostí na karte Vzhľad ovládajú postupne hlavné hodiny, Hodiny 1 a Hodiny 2. Pravým tlačidlom na ďalšom ciferníku vyberiete jeho veľkosť. Ďalšie hodiny vždy vynechávajú sekundy a zdieľajú jazyk, formát času, písma a časový posun widgetu. Pridávanie, odoberanie či zmena veľkosti zachovávajú prichytenie k rovnakým okrajom pracovnej plochy.

Horný dátum panela je odkazom vracajúcim kalendár na dnešok; dolný text pásma otvára klasické nastavenia dátumu a času Windows. Oba odkazy možno vybrať klávesom `Tab`, zobrazujú obdĺžnik fokusu a dajú sa aktivovať klávesnicou. Natívny kalendár zostáva plne interaktívny, ale v tomto rozložení vynecháva nadbytočný riadok Dnes.

`Zarovnať do mriežky` usporiada viditeľné widgety do stabilnej neprekrývajúcej sa mriežky a približne zachová ich ručné rozmiestnenie. Widget, z ktorého ponuky bol príkaz vyvolaný, zostáva na mieste; príkaz z oblasti oznámení usporadúva každý monitor samostatne. Hodiny na monitore sú vynechané.

## Vzhľad

Pri samostatných kalendároch voľba **Riadok Dnes** v ponuke alebo na karte Vzhľad ovláda spodný riadok. Predvolene je zaškrtnutá; odškrtnutím sa riadok skryje a kalendár zmenší. Voľba sa ukladá samostatne. **Prejsť na dnešok** zostáva dostupné a vracia mesačné zobrazenie. Pri zmene dátumu podľa času widgetu kalendáre automaticky vyberú dnešok a zachovajú aktuálny spôsob zobrazenia.

Zmeny vzhľadu sa okamžite zobrazujú na vybranom widgete. `Zrušiť` vráti nepoužité zmeny; `Predvolený vzhľad` obnoví hodnoty daného typu.

Digitálne hodiny, kalendáre a panely zdieľajú štyri štýly rámčeka. Jednoduchý rámček má nastaviteľnú farbu; šírka je dostupná tam, kde ju widget podporuje. Priehľadné digitálne hodiny ponúkajú rovnaké štýly ako nepriehľadné. Dialógy písiem zobrazujú iba použiteľné voľby a vynechávajú nevyužitý náhľad a efekty. Pri písme aplikácie a kalendára neponúkajú veľkosť, pri digitálnych hodinách a textoch panela áno. Natívny kalendár prijíma vlastné písmo iba pri vypnutých motívoch kalendára alebo celej aplikácie.

Jazyk aplikácie, písmo rozhrania, vyhladzovanie, motívy, ukladanie, spúšťanie s Windows a prichytávanie k okrajom sú globálne a nastavujú sa na karte Aplikácia. Globálny je aj zdroj času. Jazyk widgetu, vyhladzovanie, motívy, pásmo, posun, budík a znamenie sa nastavujú samostatne. Použitie nového jazyka okamžite znovu vytvorí otvorené Nastavenia v danom jazyku. Vyhladzovanie ponúka **ClearType**, **GDI** a **Žiadne**. Na karte Vzhľad sú vyhladzovanie a zákaz motívov na rovnakom mieste pri všetkých typoch a pod nimi je **Predvolený vzhľad**.

Jazdec **Hlasitosť zvuku** na karte Budík ovláda interne prehrávané súbory samostatne pre každý widget a zobrazuje úroveň v dB. Predvolených **−18 dB** zachováva pôvodnú úroveň súboru (**100%**). Posun doprava zosilňuje; maximum **0 dB** predstavuje približne **794%** pôvodnej amplitúdy. Ľavá krajná poloha je **−∞ dB** (ticho). Zmeny sa prejavujú aj počas testu. Pre súbory otvorené v externej aplikácii je jazdec neaktívny. Zosilnenie sa týka dekódovaného zvuku vrátane WAV, MP3, WMA, AAC, M4A a FLAC, ak ich Windows podporuje. Starší spôsob prehrávania nedekódovateľných súborov, napríklad MIDI, je obmedzený na 100%.

Dni budíka rešpektujú prvý deň týždňa zvolenej kultúry aplikácie. Uložené dni si pri zmene jazyka zachovávajú význam. Zapnutie budíka z ponuky bez vybraného dňa otvorí príslušnú kartu Budík namiesto zapnutia budíka, ktorý nemôže zaznieť.

Predvolená šírka rámčeka digitálnych hodín je nula. **Úvodná nula** ponúka **Zobraziť** (predvolené), **Ponechať miesto** a **Bez miesta**. **Ponechať miesto** skryje nulu a rezervuje jej skutočnú šírku v zvolenom písme, takže ostatné číslice držia pozície aj pri proporcionálnom písme. Plávajúce digitálne hodiny zarovnávajú čas vľavo a pri jeho plynutí si zachovávajú pevnú veľkosť. Hodiny na monitore centrujú pevnú oblasť dimenzovanú podľa písma a formátu vrátane miesta pre dve číslice hodín. Zmena času text znovu necentruje ani nemení jeho veľkosť. Riadok AM/PM alebo UTC sa centruje samostatne. Predvolene majú hodiny na monitore biely text na čiernom pozadí.

## Čas a budíky

Digitálne hodiny, kalendáre s hodinami a hodiny na monitore ponúkajú vo **Formáte času** na karte Všeobecné **Podľa jazyka**, **12 hodín** a **24 hodín**. Predvolené **Podľa jazyka** používa jazyk widgetu: americká a austrálska angličtina napríklad používajú 12 hodín, britská 24. Ručný výber sa pri zmene jazyka zachováva. Oddeľovače a značky AM/PM sa riadia kultúrou; kultúry bez vlastných značiek používajú v 12-hodinovom režime **AM/PM**.

**AM/PM** je predvolene zaškrtnuté. Vypnutie skryje značku bez zmeny 12-hodinového cyklu. V 24-hodinovom režime a pri widgetoch bez digitálneho času je neaktívne. Hodiny na monitore zobrazujú značku v samostatnom riadku pod časom ako UTC. **UTC vždy používa 24-hodinový čas**; ovládanie cyklu a AM/PM je pri UTC neaktívne a uložené voľby sa zachovajú pre návrat k miestnemu času. Úvodná nula je naďalej zobrazená, skrytá s rezervovaným miestom alebo vynechaná podľa príslušného nastavenia.

Pomenované pásma zobrazujú občiansky čas vybraného miesta a automaticky dodržiavajú jeho pravidlá letného času. Posun pri názve zodpovedá aktuálnemu dátumu a obnovuje sa pri otvorení zoznamu. Samostatné položky **UTC** poskytujú pevné posuny od **UTC−12:00** do **UTC+14:00** po 15 minútach bez letného času. Každý widget môže nezávisle používať miestne pásmo, iné pomenované pásmo alebo pevný posun UTC.

Každý widget môže používať ľubovoľné pásmo Windows a posun so znamienkom v tvare `[-]HH:mm:ss.ff`. Kompaktný zápis sa vyhodnocuje sprava, počnúc sekundami.

Posun je vhodný napríklad vo vysielacom štúdiu na kompenzáciu oneskorenia prenosovej trasy. Predsunutie štúdiových hodín o namerané oneskorenie umožní, aby znamenie dorazilo k poslucháčom v určenom okamihu.

CalClock používa systémový čas Windows alebo korekciu získanú zo serverov NTP a platnú iba v aplikácii. Voľba je globálna. Synchronizácia nikdy nemení hodiny Windows. Pri strate NTP po úspešnej synchronizácii zostáva posledná korekcia aktívna v pamäti procesu. Aj zmena serverov zachováva platnú korekciu do prijatia novej odpovede.

Hodinové widgety podporujú budíky pre jednotlivo vybrané dni; predvolene je aktívnych všetkých sedem. Budík zobrazí svoj skrytý widget a prenesie ho pred ostatné okná bez trvalej zmeny nastavenia vždy navrchu. WAV, MP3, WMA, MIDI, AAC, M4A a FLAC sa rozpoznávajú na interné jednorazové alebo opakované prehrávanie; skutočné dekódovanie závisí od multimediálnych súčastí Windows. Ostatné súbory a príkazy sa odovzdávajú Windows asynchrónne. Budík môže tiež zavolať adresu HTTP alebo HTTPS. Nezávisle od toho môže používať šesťpípové znamenie, ktorého prvé krátke pípnutie zaznie päť sekúnd pred časom budíka.

Spustiť súbor alebo príkaz aktivuje pole, Prehľadávať, Test a opakovanie. Test a opakovanie navyše vyžadujú neprázdne pole; bežiaci test však možno vždy zastaviť. Test zobrazí vizuálnu signalizáciu a asynchrónne otestuje súbor, príkaz, zvuk a adresu vzdialeného skriptu. Pri zvolenom znamení budíka prehrá aj celú šesťpípovú sekvenciu; Zastaviť test ukončí interný zvuk aj náhľad znamenia.

Karta Znamenie vypína znamenia alebo ich plánuje po 1, 5, 10, 15, 20, 30 či 60 minútach podľa času widgetu. Interval 20 minút znamená :00, :20 a :40 daného času. Vzorom je **Greenwich Time Signal (GTS)**: päť krátkych pípnutí označuje posledných päť sekúnd a dlhšie presnú hranicu. Zohľadňujú sa pásma, UTC, posuny a aktuálna korekcia NTP. Znamenie budíka a karta Znamenie zostávajú nezávislé; pri rovnakom okamihu CalClock prehrá jedinú spoločnú sekvenciu. Zohľadňujú sa zlomkové posuny a prekrývajúce sa tóny widgetov, budíkov a testov znejú súvisle do konca posledného prekryvu.

**Zvuk časového znamenia** na karte Aplikácia ponúka **Vlastný generátor** (predvolený) a **Systémové pípanie**. Platí pre všetky znamenia vrátane budíkov a ukladá sa globálne. Pri **Vlastnom generátore** jazdec **Hlasitosť časového znamenia** ukazuje úroveň v dB pre celú aplikáciu. Pravá krajná poloha je **0 dB**, maximálna neskreslená amplitúda sínusovky; ticho je **−∞ dB**. Predvolená hlasitosť je **−18 dB**. Decibelová stupnica má −18 dB uprostred. Generátor začína aj končí tóny v priechode nulou vrátane zastavenia testu. Aktuálne pípnutie nechá doznieť; dlhé môže končiť až pol sekundy. **Test** vedľa **Zvuku časového znamenia** zapne súvislý náhľad, **Zastaviť test** ho ukončí. Testovať možno oba spôsoby a stav testu sa neukladá. Držanie jazdca hlasitosti tiež spúšťa náhľad do uvoľnenia myši, pokiaľ nebeží test zapnutý tlačidlom. Prehrávanie začína v nasledujúcej celej sekunde, s krátkymi tónmi každú sekundu a dlhým v :00, :05, :10 atď. Náhľad a súčasné znamenia widgetov či budíkov zdieľajú jediný tón. Pri **Systémovom pípaní** je neaktívny iba jazdec hlasitosti. Voľba zvuku je dostupná len v systéme podporujúcom oba spôsoby.

Budík a znamenie možno zapínať aj v ponuke každého widgetu so zvukom. Položka budíka zobrazuje čas a, ak nie sú zvolené všetky dni, aktívne dni. Zaškrtnuté Stlmené ovplyvňuje widget a zodpovedá voľbe na karte Všeobecné. Samostatný Kalendár nemá budík, znamenie ani stlmenie, takže príslušné príkazy sú vynechané alebo neaktívne. V oblasti oznámení sa príkaz nazýva Stlmiť všetko; `M` na ľubovoľnom widgete vykoná rovnaké globálne prepnutie. Globálne zrušenie stlmenia obnoví iba widgety stlmené predchádzajúcou globálnou akciou. Interný zvuk pokračuje potichu a po obnovení je znovu počuteľný. Rozbehnuté pípnutie môže doznieť; ďalšie sa vynechávajú do povolenia zvuku. Nezvukové príkazy a vzdialené skripty nie sú ovplyvnené.

## Nastavenia a ponuky

`Uložiť` použije zmeny a zavrie Nastavenia, `Použiť` ich použije a ponechá okno otvorené, `Zrušiť` zahodí nepoužité zmeny vrátane náhľadu vzhľadu. Enter aktivuje `Uložiť`, Esc `Zrušiť`.

Ponuka widgetu obsahuje príkazy platné pre daný typ — viditeľnosť, vždy navrchu, sekundy, veľkosť ručičkových hodín či formát kopírovania dátumu — a potom `Zarovnať do mriežky`, Nastavenia, Pomocníka, O programe a Koniec. Ponuka oblasti oznámení uvádza widgety s poradovými číslami, potom Zobraziť všetko, Skryť všetko a Stlmiť všetko. Oddelené `Zarovnať do mriežky` nasleduje pred príkazmi aplikácie.

Zobrazenie alebo obnovenie widgetov ich prenesie pred ostatné okná bez zmeny stavu vždy navrchu. CalClock zabezpečuje aspoň jeden viditeľný widget po spustení. Druhé spustenie aktivuje existujúcu inštanciu a, ak nič nie je viditeľné, obnoví naposledy skryté widgety. Po reštarte Prieskumníka Windows sa ikona oznámení automaticky znovu zaregistruje. Ak `ClockWndMain` nepodporuje sekundovú ručičku pri vybranej veľkosti, Sekundy sú neaktívne, ale voľba zostáva uložená pre inú podporovanú veľkosť.

## Ukladanie nastavení

Predvolene sa nastavenia ukladajú do:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

Ukladanie XML možno zapnúť v Nastaveniach. Používa:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Po úspešnom zápise XML CalClock odstráni svoj stav z registra. Prepnutie späť do registra obdobne odstráni automatické XML a prázdne adresáre CalClocku. Import XML okamžite načíta a uloží nastavenia do aktuálne zvoleného úložiska bez zmeny typu. Stlmenie sa ukladá samostatne pre každý zvukový widget. Spúšťanie s Windows sa ukladá ako hodnota `CalClock` do štandardného kľúča `Run` aktuálneho používateľa.

## Zostavenie

Požiadavky:

- Microsoft Visual Studio so súpravou nástrojov MSVC v145
- Windows SDK

Otvorte `CalClock.slnx`, vyberte `Release | Win32` a zostavte riešenie. Spustiteľný súbor vznikne ako:

```text
Release\CalClock.exe
```

Podporovaná je iba konfigurácia Win32/x86. Projekt zámerne neposkytuje x64, pretože integrácia s ovládacím prvkom hodín Windows vyžaduje kompatibilitu x86.

## Licencia

CalClock je dostupný pod [licenciou MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
