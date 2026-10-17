# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · **Slovenčina** · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock je natívna aplikácia Win32/x86 pre Windows Vista a novšie verzie, ktorá na pracovnej ploche Windows zobrazuje samostatne nastaviteľné plávajúce hodiny a kalendáre. Beží v oblasti oznámení a nepotrebuje trvalo otvorené ovládacie okno.

## Funkcie

- Až 32 samostatne nastaviteľných widgetov
- Vlastný jazyk, časové pásmo, časový posun, viditeľnosť a stav vždy navrchu pre každý widget
- Ručičkové hodiny s voliteľnou veľkosťou ciferníka a sekundovou ručičkou
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
- Rozhranie v 36 jazykových variantoch; samostatný výber jazyka aplikácie a každého widgetu

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
- Na widgetoch Ručičkové hodiny a Kalendár s hodinami zvolíte pomocou `Alt+0`, `Alt+1`, `Alt+2` alebo `Alt+3` veľkosť hlavného ciferníka od najmenšej po najväčšiu.
- Dvojklik na widget v Nastaveniach ho podľa potreby zobrazí, zaškrtne `Zobrazené` a krátko označí na ploche.
- Otvorenie Nastavení z ponuky widgetu tento widget okamžite vyberie.
- Odobrať alebo Del odstráni po použití zmien všetky označené položky. `Insert` prepne označenie aktuálnej položky a posunie kurzor zoznamu o riadok nižšie.
- `Ctrl+C` skopíruje vybrané widgety a `Ctrl+V` pripojí kópie na koniec v poradí zoznamu. Kópie obsahujú všetky nastavenia a dostanú príponu názvu v jazyku aplikácie. Duplikovať vykoná rovnakú operáciu priamo. Povolených je najviac 32 widgetov. Ak sa nezmestia všetky kópie, pridajú sa v poradí len tie, ktoré sa zmestia, a správa upozorní na ostatné.

Nastavenia otvorené z ikony v oblasti oznámení obnovia naposledy vybraný widget.

Nastavenia si pamätajú poslednú otvorenú kartu a naposledy pridaný typ widgetu.

Dátumy možno kopírovať v 33 formátoch: miestnych, zoraditeľných, s dňom alebo mesiacom na začiatku, slovných a s dňom v týždni. Každá maska je dostupná vo všetkých jazykoch. Predvolený miestny krátky formát sa riadi jazykom widgetu, rovnako ako názvy mesiacov a dní. Položky zobrazujú masku a aktuálny príklad.

Kalendár s hodinami môže zobrazovať až dvoje ďalšie hodiny. Každé zapnite na karte Všeobecné a vyberte názov a pásmo. Pomenované pásma dodržiavajú vlastné pravidlá letného času; pevné posuny UTC sa nemenia. Ak sú ďalšie hodiny zapnuté, pod časom každých hodín sa zobrazuje ich miestny deň v týždni. Tri zoznamy veľkostí na karte Vzhľad ovládajú postupne hlavné hodiny, Hodiny 1 a Hodiny 2. Pravým tlačidlom na ďalšom ciferníku vyberiete jeho veľkosť. Ďalšie hodiny vždy vynechávajú sekundy a zdieľajú jazyk, formát času, písma a časový posun widgetu. Pridávanie, odoberanie či zmena veľkosti zachovávajú prichytenie k rovnakým okrajom pracovnej plochy.

Horný dátum panela je odkazom vracajúcim kalendár na dnešok; dolný text pásma otvára klasické nastavenia dátumu a času Windows.

`Zarovnať do mriežky` usporiada viditeľné widgety do stabilnej neprekrývajúcej sa mriežky a približne zachová ich ručné rozmiestnenie. Widget, z ktorého ponuky bol príkaz vyvolaný, zostáva na mieste; príkaz z oblasti oznámení usporadúva každý monitor samostatne. Hodiny na monitore sú vynechané.

## Vzhľad

Pri samostatných kalendároch voľba **Riadok Dnes** v ponuke alebo na karte Vzhľad ovláda spodný riadok. Predvolene je zaškrtnutá; odškrtnutím sa riadok skryje a kalendár zmenší. Voľba sa ukladá samostatne. **Prejsť na dnešok** zostáva dostupné a vracia mesačné zobrazenie. Pri zmene dátumu podľa času widgetu kalendáre automaticky vyberú dnešok a zachovajú aktuálny spôsob zobrazenia.

Zmeny vzhľadu sa okamžite zobrazujú na vybranom widgete. `Zrušiť` zruší nepoužité zmeny; `Predvolený vzhľad` obnoví hodnoty daného typu.

Digitálne hodiny, kalendáre a panely zdieľajú štyri štýly rámčeka. Jednoduchý rámček má nastaviteľnú farbu; šírka je dostupná tam, kde ju widget podporuje. Priehľadné digitálne hodiny ponúkajú rovnaké štýly ako nepriehľadné. Pri písme aplikácie a kalendára neponúkajú veľkosť, pri digitálnych hodinách a textoch panela áno. Vlastné písmo kalendára sa používa pri klasickom vzhľade Windows alebo pri vypnutých motívoch aplikácie či widgetu.

Jazyk aplikácie, písmo rozhrania, vyhladzovanie, motívy, ukladanie, spúšťanie s Windows a prichytávanie k okrajom sú globálne a nastavujú sa na karte Aplikácia. Globálny je aj zdroj času. Jazyk widgetu, vyhladzovanie, motívy, pásmo, posun, budík a znamenie sa nastavujú samostatne. Vyhladzovanie ponúka **ClearType**, **GDI** a **Žiadne**.

Jazdec **Hlasitosť zvuku** na karte Budík ovláda interne prehrávané súbory samostatne pre každý widget a zobrazuje úroveň v dB. Predvolených **−18 dB** zachováva pôvodnú úroveň súboru (**100%**). Posun doprava zosilňuje; maximum **0 dB** predstavuje približne **794%** pôvodnej amplitúdy. Ľavá krajná poloha je **−∞ dB** (ticho). Zmeny sa prejavujú aj počas testu. Zosilnenie sa týka dekódovaného zvuku vrátane WAV, MP3, WMA, AAC, M4A a FLAC, ak ich Windows podporuje. Starší spôsob prehrávania nedekódovateľných súborov, napríklad MIDI, je obmedzený na 100%.

Dni budíka rešpektujú prvý deň týždňa zvolenej kultúry aplikácie. Uložené dni si pri zmene jazyka zachovávajú význam. Zapnutie budíka z ponuky bez vybraného dňa otvorí príslušnú kartu Budík namiesto zapnutia budíka, ktorý nemôže zaznieť.

**Úvodná nula** ponúka **Zobraziť** (predvolené), **S miestom** a **Bez miesta**. **S miestom** skryje nulu a rezervuje jej skutočnú šírku v zvolenom písme, takže ostatné číslice držia pozície aj pri proporcionálnom písme. Predvolene majú hodiny na monitore biely text na čiernom pozadí.

## Čas a budíky

Digitálne hodiny, kalendáre s hodinami a hodiny na monitore ponúkajú vo **Formáte času** na karte Všeobecné **Podľa jazyka**, **12 hodín** a **24 hodín**. Predvolené **Podľa jazyka** používa jazyk widgetu: americká a austrálska angličtina napríklad používajú 12 hodín, britská 24. Ručný výber sa pri zmene jazyka zachováva. Oddeľovače a značky AM/PM sa riadia kultúrou; kultúry bez vlastných značiek používajú v 12-hodinovom režime **AM/PM**.

**AM/PM** je predvolene zaškrtnuté. Vypnutie skryje značku bez zmeny 12-hodinového cyklu. Hodiny na monitore zobrazujú značku v samostatnom riadku pod časom ako UTC. UTC vždy používa 24-hodinový formát. Úvodná nula je naďalej zobrazená, skrytá s rezervovaným miestom alebo vynechaná podľa príslušného nastavenia.

Pomenované pásma zobrazujú občiansky čas vybraného miesta a automaticky dodržiavajú jeho pravidlá letného času. Posun pri názve zodpovedá aktuálnemu dátumu a obnovuje sa pri otvorení zoznamu. Samostatné položky **UTC** poskytujú pevné posuny od **UTC−12:00** do **UTC+14:00** po 15 minútach bez letného času. Každý widget môže nezávisle používať miestne pásmo, iné pomenované pásmo alebo pevný posun UTC.

Každý widget môže používať ľubovoľné pásmo Windows a posun so znamienkom v tvare `[-]HH:mm:ss.ff`. Kompaktný zápis sa vyhodnocuje sprava, počnúc sekundami.

Posun je vhodný napríklad vo vysielacom štúdiu na kompenzáciu oneskorenia prenosovej trasy. Predsunutie štúdiových hodín o namerané oneskorenie umožní, aby znamenie dorazilo k poslucháčom v určenom okamihu.

Na karte Čas možno pre celú aplikáciu, teda spoločne pre všetky widgety, vybrať systémový čas Windows alebo čas zo zadaných serverov NTP. NTP koriguje iba čas zobrazený v CalClock; systémové hodiny Windows sa nikdy nemenia. Do prvej platnej odpovede sa používa systémový čas. NTP je predvolené. Automatická sada vyberie podľa systémovej oblasti české a slovenské servery, PTB pre Európu alebo celosvetový fond. Viaceré merania sa filtrujú podľa sieťového oneskorenia a odľahlých odpovedí. Synchronizovať teraz spustí nové meranie ihneď.

Po synchronizácii hodiny CalClock pokračujú nezávisle od neskorších zmien systémového času Windows. Pri výpadku spojenia alebo zmene serverov pokračujú od poslednej platnej synchronizácie až do získania novej odpovede; stav sa uchováva do ukončenia aplikácie.

Na karte Čas je záznam dotazov na servery NTP od spustenia aplikácie. Každý záznam obsahuje dátum a miestny čas počítača, server a stav. OK označuje platnú odpoveď a θ jej odchýlku voči systémovému času Windows. ERR uvádza dôvod neúspechu a prípadný chybový kód. Posledný záznam skupiny obsahuje aj výslednú odchýlku Θ, ak sa podarilo získať použiteľné merania.

Odchýlky sa zobrazujú v milisekundách so štyrmi desatinnými miestami. Kladná hodnota znamená, že čas servera je voči Windows vpred; záporná, že zaostáva. Výsledná odchýlka Θ zohľadňuje prijaté merania a je uvedená aj v stave synchronizácie.

Uložiť log uloží záznamy do CSV vrátane odchýlok a dôvodov chýb. Záznamy sa medzi spusteniami neuchovávajú; ak ich chcete zachovať, uložte ich pred ukončením aplikácie.

Hodinové widgety podporujú budíky pre jednotlivo vybrané dni; predvolene je aktívnych všetkých sedem. Budík zobrazí svoj skrytý widget a prenesie ho pred ostatné okná bez trvalej zmeny nastavenia vždy navrchu. WAV, MP3, WMA, MIDI, AAC, M4A a FLAC sa rozpoznávajú na interné jednorazové alebo opakované prehrávanie; skutočné dekódovanie závisí od multimediálnych súčastí Windows. Ostatné súbory a príkazy sa odovzdávajú Windows asynchrónne. Budík môže tiež zavolať adresu HTTP alebo HTTPS. Nezávisle od toho môže používať šesťpípové znamenie, ktorého prvé krátke pípnutie zaznie päť sekúnd pred časom budíka.

Test zobrazí vizuálnu signalizáciu a asynchrónne otestuje súbor, príkaz, zvuk a adresu vzdialeného skriptu. Pri zvolenom znamení budíka prehrá aj celú šesťpípovú sekvenciu; Zastaviť test ukončí interný zvuk aj náhľad znamenia.

Na karte Znamenie je začiarkavacie políčko Časové znamenie aktívne a prepínače intervalov 1, 5, 10, 15, 20, 30 alebo 60 minút podľa času zobrazovaného widgetom. Znamenie je spočiatku vypnuté a je zvolený hodinový interval. Vypnutie a zapnutie príkazom Signál v menu widgetu zachováva interval. Menu zobrazuje čas budíka a interval znamenia v zátvorkách. Interval 20 minút znamená :00, :20 a :40 daného času. Vzorom je **Greenwich Time Signal (GTS)**: päť krátkych pípnutí označuje posledných päť sekúnd a dlhšie presnú hranicu. Zohľadňujú sa pásma, UTC, posuny a aktuálna korekcia NTP. Znamenie budíka a karta Znamenie zostávajú nezávislé; pri rovnakom okamihu CalClock prehrá jedinú spoločnú sekvenciu. Zohľadňujú sa zlomkové posuny a prekrývajúce sa tóny widgetov, budíkov a testov znejú súvisle do konca posledného prekryvu.

**Zvuk časového znamenia** na karte Aplikácia ponúka **Vlastný generátor** (predvolený) a **Systémové pípanie**. Platí pre všetky znamenia vrátane budíkov a ukladá sa globálne. Pri **Vlastnom generátore** jazdec **Hlasitosť časového znamenia** ukazuje úroveň v dB pre celú aplikáciu. Pravá krajná poloha je **0 dB**, maximálna neskreslená amplitúda sínusovky; ticho je **−∞ dB**. Predvolená hlasitosť je **−18 dB**. Generátor začína aj končí tóny v priechode nulou vrátane zastavenia testu. Aktuálne pípnutie nechá doznieť; dlhé môže končiť až pol sekundy. **Test** vedľa **Zvuku časového znamenia** zapne súvislý náhľad, **Zastaviť test** ho ukončí. Testovať možno oba spôsoby a stav testu sa neukladá. Držanie jazdca hlasitosti tiež spúšťa náhľad do uvoľnenia myši, pokiaľ nebeží test zapnutý tlačidlom. Prehrávanie začína v nasledujúcej celej sekunde, s krátkymi tónmi každú sekundu a dlhým v :00, :05, :10 atď. Náhľad a súčasné znamenia widgetov či budíkov zdieľajú jediný tón. Voľba zvuku je dostupná len v systéme podporujúcom oba spôsoby.

Budík a znamenie možno zapínať aj v ponuke každého widgetu so zvukom. Položka budíka zobrazuje čas a, ak nie sú zvolené všetky dni, aktívne dni. Zaškrtnuté Stlmené ovplyvňuje widget a zodpovedá voľbe na karte Všeobecné. Samostatný Kalendár nepodporuje budík, časové znamenie ani stlmenie. V oblasti oznámení sa príkaz nazýva Stlmiť všetko; `M` na ľubovoľnom widgete vykoná rovnaké globálne prepnutie. Globálne zrušenie stlmenia obnoví iba widgety stlmené predchádzajúcou globálnou akciou. Interný zvuk pokračuje potichu a po obnovení je znovu počuteľný. Rozbehnuté pípnutie môže doznieť; ďalšie sa vynechávajú do povolenia zvuku. Nezvukové príkazy a vzdialené skripty nie sú ovplyvnené.

## Nastavenia a ponuky

Ponuka widgetu obsahuje príkazy platné pre daný typ — viditeľnosť, vždy navrchu, sekundy, veľkosť ručičkových hodín či formát kopírovania dátumu — a potom `Zarovnať do mriežky`, Nastavenia, Pomocníka, O programe a Koniec. Ponuka oblasti oznámení uvádza widgety s poradovými číslami, potom Zobraziť všetko, Skryť všetko a Stlmiť všetko. Oddelené `Zarovnať do mriežky` nasleduje pred príkazmi aplikácie.

Zobrazenie alebo obnovenie widgetov ich prenesie pred ostatné okná bez zmeny stavu vždy navrchu. CalClock zabezpečuje aspoň jeden viditeľný widget po spustení. Druhé spustenie aktivuje existujúcu inštanciu a, ak nič nie je viditeľné, obnoví naposledy skryté widgety. Po reštarte Prieskumníka Windows sa ikona oznámení automaticky znovu zaregistruje.

## Ukladanie nastavení

Predvolene sa nastavenia ukladajú do:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

Ukladanie XML možno zapnúť v Nastaveniach. Používa:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Import XML okamžite načíta a uloží nastavenia do aktuálne zvoleného úložiska bez zmeny typu. Stlmenie sa ukladá samostatne pre každý zvukový widget.

## Zostavenie

Požiadavky:

- Microsoft Visual Studio so súpravou nástrojov MSVC v145
- Windows SDK

Otvorte `CalClock.slnx`, vyberte `Release | x86` a zostavte riešenie. Spustiteľný súbor vznikne ako:

```text
Release\CalClock.exe
```

Podporovaná je iba konfigurácia Win32/x86. Projekt zámerne neposkytuje x64, pretože integrácia s ovládacím prvkom hodín Windows vyžaduje kompatibilitu x86.

## Licencia

CalClock je dostupný pod [licenciou MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
