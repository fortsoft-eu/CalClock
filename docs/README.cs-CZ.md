# CalClock

**Čeština** · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock je nativní aplikace Win32/x86 pro Windows Vista a novější, která na ploše Windows zobrazuje samostatně nastavitelné plovoucí hodiny a kalendáře. Běží v oznamovací oblasti a nepotřebuje trvale otevřené ovládací okno.

## Funkce

- Až 32 samostatně nastavitelných widgetů
- Vlastní jazyk, časové pásmo, časový offset, viditelnost a stav vždy navrchu pro každý widget
- Ručičkové hodiny s volitelnou velikostí ciferníku a sekundovou ručičkou
- Nastavitelné digitální hodiny s volbou písma, barev, neprůhlednosti, odsazení, rámečku, úvodní nuly a průhledného pozadí
- Nativní kalendáře Windows s výběrem data, čtyřmi styly rámečku, nastavitelnou barvou rámečku, čísly týdnů, volbou prvního dne týdne a 33 formáty kopírování data
- Kalendáře s hodinami a až dvěma dalšími pojmenovanými hodinami v samostatných časových pásmech, samostatnými velikostmi ciferníků, čtyřmi styly rámečku, nastavitelnou barvou rámečku, textem UTC, volbou úvodní nuly a samostatným písmem pro každý textový řádek
- Budíky s výběrem dnů v týdnu, vizuální signalizací, interním přehráváním zvuku, opakováním, místními příkazy a voláním skriptů přes HTTP/HTTPS
- Časové znamení pro jednotlivé hodiny v intervalu 1, 5, 10, 15, 20, 30 nebo 60 minut; souběžná znamení se sloučí do jedné sekvence
- Příkaz Ztlumeno pro jednotlivé hodiny a zaškrtávací příkaz Ztlumit vše v nabídce oznamovací oblasti
- Volitelné automatické spouštění s Windows
- Volitelné přichytávání widgetů k okrajům pracovní plochy při tažení v dosahu pěti pixelů, ve výchozím stavu zapnuté; přichycení zůstává zachováno při změně velikosti widgetu
- Synchronizace NTP bez změny systémového času Windows
- Několik předvoleb serverů NTP pro Česko a Slovensko, PTB, Ubuntu/NTP Pool a vlastní servery
- Ukládání nastavení do registru nebo XML, včetně importu a exportu XML
- Ovládání z oznamovací oblasti s obnovením naposledy skrytých widgetů
- Identifikace widgetů a stabilní zarovnání do nepřekrývající se mřížky
- Průběžný náhled vzhledu s možností zrušení změn a obnovení výchozího vzhledu jednotlivých widgetů
- Písma aplikace a widgetů, nastavení motivů a vyhlazování písma ClearType, GDI nebo žádné
- Rozhraní ve 36 jazykových variantách; samostatný výběr jazyka aplikace a každého widgetu

## Typy widgetů

| Widget | Popis |
| --- | --- |
| Ručičkové hodiny | Plovoucí ciferník Windows s velikostmi a volitelnou sekundovou ručičkou podporovanými aktuální verzí Windows |
| Digitální hodiny | Nastavitelné plovoucí digitální hodiny s volitelným textem UTC, úvodní nulou, rámečkem a průhledným pozadím |
| Kalendář | Přesouvatelný nativní měsíční kalendář s výběrem data, nastavitelným rámečkem a formáty kopírování |
| Kalendář s hodinami | Kombinovaný panel s nativním kalendářem, ručičkovými hodinami, nastavitelnými textovými řádky, zobrazením UTC a nastavitelným rámečkem |
| Hodiny na monitoru | Digitální hodiny vyplňující jeden nebo více zvolených monitorů, s volitelným zatemněním a textem UTC na samostatném řádku |

Při prvním spuštění CalClock vybere jazyk aplikace podle jazyka uživatelského rozhraní Windows. Není-li podporován, použije americkou angličtinu. Ve výchozím stavu vytvoří jedny viditelné ručičkové hodiny. Každý widget si mezi spuštěními uchovává vlastní pozici a nastavení. Když je otevřeno Nastavení, hodiny na monitoru vždy zastupuje přesouvatelný náhled s poměrem stran vybraného monitoru. `Esc` skryje hodiny na monitoru i jejich zatemnění, a to i při otevřeném Nastavení. Nad hodinami na monitoru a zatemněnými monitory se ukazatel po krátké nečinnosti skryje a po pohybu myši znovu zobrazí. Nad malým náhledem v Nastavení zůstává viditelný.

## Ovládání

- Hodiny nebo panel přesuňte tažením levým tlačítkem myši.
- Samostatný kalendář přesuňte tažením za jeho volnou plochu.
- Pravým tlačítkem na widgetu nebo ikoně v oznamovací oblasti otevřete kontextovou nabídku.
- Levým tlačítkem na ikoně v oznamovací oblasti skryjete viditelné widgety. Jsou-li všechny skryté, dalším kliknutím obnovíte pouze naposledy skryté widgety.
- Dvojklikem na ciferník přepnete zobrazení sekund. V kalendáři s hodinami přepíná sekundovou ručičku pouze dvojklik přímo na hlavní ciferník. Další hodiny sekundovou ručičku nemají.
- Klávesa `F1` otevře Nápovědu, `B` Nastavení, `M` přepne Ztlumit vše a `Esc` skryje widget nebo zastaví aktivní budík.
- Na widgetech Ručičkové hodiny a Kalendář s hodinami zvolíte pomocí `Alt+0`, `Alt+1`, `Alt+2` nebo `Alt+3` velikost hlavního ciferníku od nejmenší po největší.
- Dvojklikem na widget v seznamu Nastavení jej podle potřeby zobrazíte, zaškrtnete `Zobrazeno` a krátce jej označíte na ploše.
- Otevřením Nastavení z kontextové nabídky widgetu tento widget ihned vyberete.
- Odebrat nebo Del odstraní všechny označené položky až po použití změn. `Insert` přepne označení aktuální položky a posune kurzor seznamu o řádek dolů.
- Pomocí `Ctrl+C` zkopírujete vybrané widgety a `Ctrl+V` připojí jejich kopie na konec v pořadí seznamu. Kopie obsahují všechna nastavení widgetů a dostanou příponu názvu v jazyce aplikace. Tlačítko Duplikovat provede stejnou duplikaci přímo. Lze mít nejvýše 32 widgetů. Pokud se všechny kopie nevejdou, přidají se v pořadí seznamu jen ty, které se vejdou, a na zbývající upozorní zpráva.

Při otevření Nastavení z ikony v oznamovací oblasti se vybere naposledy zvolený widget.

Nastavení si pamatuje naposledy otevřenou kartu i typ naposledy přidaného widgetu.

Data z kalendáře lze kopírovat ve 33 formátech zahrnujících místní zápis, řaditelný zápis, den nebo měsíc na začátku, slovní zápis a den v týdnu. Každá maska je dostupná v každém jazyce rozhraní. Výchozí místní krátký formát se řídí jazykem widgetu; stejný jazyk používají i slovní názvy měsíců a dnů v týdnu. Položky formátů zobrazují masku a aktuální příklad.

Kalendář s hodinami může zobrazit až dvoje další hodiny. Každé zapněte na kartě Obecné a zvolte jejich název a časové pásmo. Pojmenovaná pásma se řídí vlastními pravidly letního času; pevné offsety UTC se nemění. Pokud jsou další hodiny zapnuté, pod časem každých hodin se zobrazuje jejich místní den v týdnu. Tři seznamy velikostí na kartě Vzhled ovládají postupně hlavní hodiny, Hodiny 1 a Hodiny 2. Velikost dalších hodin lze vybrat pravým tlačítkem na jejich ciferníku. Další hodiny vždy vynechávají sekundy a sdílejí jazyk, formát času, písma a časový offset widgetu. Přidávání, odebírání a změna velikosti hodin zachovávají přichycení widgetu ke stejným okrajům pracovní plochy.

V kalendáři s hodinami je horní datum odkazem, který vrací kalendář na dnešek, zatímco dolní text časového pásma otevírá klasické nastavení data a času Windows.

Příkaz `Zarovnat do mřížky` přichytí viditelné widgety na ploše do stabilní nepřekrývající se mřížky a přibližně zachová jejich ruční rozmístění. Widget, z jehož nabídky byl příkaz vyvolán, zůstává na místě; příkaz z oznamovací oblasti zarovnává každý monitor samostatně. Hodiny na monitoru jsou vynechány.

## Vzhled

U samostatných kalendářů volba **Řádek Dnes** v nabídce widgetu nebo na kartě Vzhled v Nastavení ovládá viditelnost spodního řádku Dnes. Ve výchozím stavu je zaškrtnutá; odškrtnutím řádek skryjete a kalendář se zmenší. Volba se ukládá samostatně pro každý widget. Příkaz **Přejít na dnešek** zůstává v nabídce dostupný a vrací kalendář do měsíčního zobrazení. Při změně data podle času příslušného widgetu kalendáře automaticky vyberou dnešek a zachovají aktuální způsob zobrazení.

Změny vzhledu se okamžitě zobrazují na vybraném widgetu. `Zrušit` zruší nepoužité změny vzhledu, zatímco `Výchozí vzhled` obnoví výchozí hodnoty pro příslušný typ widgetu.

Digitální hodiny, kalendáře a kombinované panely sdílejí čtyři styly rámečku. Jednoduchý rámeček má také nastavitelnou barvu; nastavení šířky rámečku je dostupné tam, kde je vybraný widget podporuje. Průhledné digitální hodiny nabízejí stejné styly jako neprůhledné. Vlastní písmo kalendáře se používá při klasickém vzhledu Windows nebo při vypnutých motivech aplikace či widgetu.

Jazyk aplikace, písmo rozhraní, vyhlazování písma, motivy, ukládání nastavení, spouštění s Windows a přichytávání k okrajům pracovní plochy jsou globální a nastavují se na kartě Aplikace. Globální je i zdroj času. Jazyk widgetu, vyhlazování písma, motivy, časové pásmo, offset, budík a časové znamení se nastavují samostatně. Vyhlazování písma nabízí **ClearType**, **GDI** a **Žádné**.

Jezdec **Hlasitost zvuku** na kartě Budík ovládá interně přehrávané zvukové soubory samostatně pro každý widget a zobrazuje úroveň v dB. Výchozí hodnota **−18 dB** zachovává původní úroveň souboru (**100%**). Posun doprava zvuk zesiluje; maximum **0 dB** odpovídá přibližně **794%** původní amplitudy. Levá krajní poloha je **−∞ dB** (ticho). Změny se projevují i během testu zvuku. Zesílení se vztahuje na dekódovaný zvuk včetně WAV, MP3, WMA, AAC, M4A a FLAC, pokud je Windows podporují. Starší způsob přehrávání souborů, které nelze dekódovat, například MIDI, je omezen na 100%.

Ovládací prvky dnů budíku respektují první den týdne používaný zvolenou kulturou aplikace. Uložené dny budíku si při změně jazyka aplikace zachovávají význam. Zapnutí budíku z nabídky widgetu bez vybraného dne v týdnu otevře kartu Budík příslušného widgetu, místo aby zapnulo budík, který nemůže zaznít.

**Úvodní nula** nabízí **Ano** (výchozí), **Ne, ponechat místo** a **Ne, bez místa**. Volba **Ne, ponechat místo** skryje nulu a rezervuje její skutečnou šířku ve zvoleném písmu, takže ostatní číslice drží pozice i při proporcionálním písmu. Výchozí vzhled hodin na monitoru je bílý text na černém pozadí.

## Čas a budíky

Digitální hodiny, kalendáře s hodinami a hodiny na monitoru nabízejí v položce **Formát času** na kartě Obecné volby **Podle jazyka**, **12 hodin** a **24 hodin**. Výchozí volba **Podle jazyka** se řídí jazykem widgetu: například americká a australská angličtina používají 12hodinový čas, britská angličtina 24hodinový. Ručně vybraný cyklus se při změně jazyka widgetu zachová. Oddělovače času a značky AM/PM odpovídají zvolené kultuře; kultury bez vlastních značek používají ve 12hodinovém režimu **AM/PM**.

Zatržítko **AM/PM** je ve výchozím stavu zaškrtnuté. Vypnutí skryje značku, ale nezmění 12hodinový cyklus. Hodiny na monitoru zobrazují značku na samostatném řádku pod časem stejně jako text UTC. UTC vždy používá 24hodinový formát. Nastavení úvodní nuly nadále určuje, zda je první nula zobrazena, skryta s rezervovaným místem, nebo zcela vynechána.

Pojmenovaná časová pásma zobrazují občanský čas vybraného místa a automaticky zohledňují tamní pravidla letního času. Offset u každého názvu odpovídá aktuálnímu datu a obnovuje se při otevření seznamu. Samostatné položky **UTC** poskytují pevné offsety od **UTC−12:00** do **UTC+14:00** po 15 minutách bez změn letního času. Pro každý widget lze nezávisle zvolit místní pásmo, libovolné jiné pojmenované pásmo nebo pevný offset UTC.

Každý widget může používat libovolné časové pásmo Windows a offset se znaménkem ve tvaru `[-]HH:mm:ss.ff`. Kompaktní zápis offsetu se vyhodnocuje zprava, počínaje sekundami.

Offset je vhodný například v rozhlasovém či televizním studiu ke kompenzaci zpoždění přenosové trasy. Předsunutí studiových hodin o naměřené zpoždění umožní, aby jejich časové znamení dorazilo k posluchačům ve správný okamžik.

Na kartě Čas lze pro celou aplikaci, tedy společně pro všechny widgety, vybrat systémový čas Windows nebo čas ze zadaných serverů NTP. NTP koriguje pouze čas zobrazovaný v CalClock; systémové hodiny Windows se nikdy nemění. Dokud nebyl získán platný údaj, používá se systémový čas. NTP je výchozí. Automatická sada volí podle systémové oblasti české a slovenské servery, PTB pro Evropu nebo celosvětový fond. Více měření se filtruje podle síťového zpoždění a odlehlých odpovědí. Synchronizovat nyní spustí nové měření okamžitě.

Po synchronizaci hodiny CalClock pokračují nezávisle na pozdějších změnách systémového času Windows. Při výpadku spojení nebo změně serverů pokračují od poslední platné synchronizace až do získání nové odpovědi; stav se uchovává do ukončení aplikace.

Na kartě Čas je záznam dotazů na servery NTP od spuštění aplikace. Každý záznam obsahuje datum a místní čas počítače, server a stav. OK označuje platnou odpověď a θ její odchylku vůči systémovému času Windows. ERR uvádí důvod neúspěchu a případný chybový kód. Poslední záznam skupiny obsahuje také výslednou odchylku Θ, pokud se podařilo získat použitelná měření.

Odchylky se zobrazují v milisekundách se čtyřmi desetinnými místy. Kladná hodnota znamená, že čas serveru je vůči Windows napřed; záporná, že je pozadu. Výsledná odchylka Θ zohledňuje přijatá měření a je uvedena také ve stavu synchronizace.

Uložit log uloží záznamy do CSV včetně odchylek a důvodů chyb. Záznamy se mezi spuštěními neuchovávají; chcete-li je zachovat, uložte je před ukončením aplikace.

Hodinové widgety podporují budíky pro samostatně vybrané dny v týdnu; ve výchozím stavu je zapnuto všech sedm dnů. Budík zobrazí svůj skrytý widget a přenese jej před ostatní okna, aniž by trvale změnil jeho nastavení vždy navrchu. Soubory WAV, MP3, WMA, MIDI, AAC, M4A a FLAC jsou rozpoznávány pro interní jednorázové nebo opakované přehrávání; skutečnou podporu dekódování poskytují multimediální součásti nainstalované ve Windows. Ostatní soubory a příkazy se předávají Windows asynchronně. Budík může také zavolat adresu HTTP nebo HTTPS. Nezávisle na těchto akcích může budík používat šestipípové časové znamení, jehož první krátké pípnutí zazní pět sekund před nastaveným časem budíku.

Tlačítko Test u budíku zobrazí náhled vizuální signalizace a asynchronně otestuje nastavený soubor, příkaz, zvuk i adresu vzdáleného skriptu. Je-li zvoleno časové znamení budíku, Test přehraje také celou šestipípovou sekvenci; Zastavit test ukončí interní zvuk a náhled znamení.

Na kartě Znamení je zatržítko Časové znamení aktivní a přepínače intervalů 1, 5, 10, 15, 20, 30 nebo 60 minut podle času zobrazovaného widgetem. Znamení je zpočátku vypnuté a je zvolen hodinový interval. Vypnutí a zapnutí příkazem Signál v menu widgetu interval zachovává. Menu zobrazuje čas budíku a interval znamení v závorkách. Interval 20 minut znamená :00, :20 a :40 podle tohoto času. Znamení odpovídá **Greenwich Time Signal (GTS)**: pět krátkých pípnutí označuje posledních pět sekund a delší pípnutí přesnou hranici intervalu. Zohledňují se časová pásma, režim UTC, offsety i aktuální korekce NTP. Znamení budíku a karta Znamení zůstávají nezávisle nastavitelné; pokud se jejich termíny setkají ve stejném okamžiku, CalClock přehraje jedinou společnou sekvenci. Zohledňují se i zlomkové offsety widgetů a překrývající se tóny widgetů, budíků a testů znějí souvisle do konce posledního překryvu.

**Zvuk časového znamení** na kartě Aplikace nabízí **Vlastní generátor** (výchozí) a **Systémové pípání**. Volba platí pro časová znamení všech widgetů včetně znamení budíků a ukládá se do globálního nastavení. U **Vlastního generátoru** zobrazuje jezdec **Hlasitost časového znamení** úroveň v dB pro celou aplikaci. Pravá krajní poloha je **0 dB**, maximální nezkreslená amplituda sinusovky; ticho je **−∞ dB**. Výchozí hlasitost je **−18 dB**. Zastavení testu nechá aktuální pípnutí doznít; dlouhé pípnutí může končit až půl sekundy. Tlačítko **Test** vedle **Zvuku časového znamení** zapne souvislý náhled, **Zastavit test** jej ukončí. Testovat lze **Systémové pípání** i **Vlastní generátor**; stav testu se neukládá. Držení jezdce hlasitosti také spouští náhled do uvolnění myši, pokud neběží test zapnutý tlačítkem. Přehrávání začíná v následující celé sekundě, s krátkými tóny každou sekundu a dlouhým v :00, :05, :10 atd. Náhled a současná znamení widgetů či budíků sdílejí jediný tón. Volba zvuku je dostupná jen tehdy, podporuje-li systém obě možnosti.

Budík i časové znamení lze zapínat také v kontextové nabídce každého widgetu podporujícího zvuk. Položka budíku zobrazuje jeho čas a, nejsou-li zvoleny všechny dny, také aktivní dny v týdnu. Zaškrtnutý příkaz Ztlumeno ovlivňuje svůj widget a odpovídá volbě Ztlumeno na kartě Obecné. Samostatný Kalendář nepodporuje budík, časové znamení ani ztlumení. Příkaz v oznamovací oblasti se jmenuje Ztlumit vše; `M` na libovolném widgetu provede stejné globální přepnutí. Globální zrušení ztlumení obnoví pouze widgety ztlumené předchozí globální akcí. Interní zvuk pokračuje tiše a po zrušení ztlumení je opět slyšitelný. Již probíhající pípnutí může doznít, další se vynechávají do opětovného povolení zvuku. Příkazy nesouvisející se zvukem a vzdálené skripty nejsou ovlivněny.

## Nastavení a nabídky

Nabídka každého widgetu obsahuje příkazy pro daný typ — viditelnost, vždy navrchu, sekundy, velikost ručičkových hodin nebo formát kopírování data — a dále `Zarovnat do mřížky`, Nastavení, Nápovědu, O programu a Konec. Nabídka oznamovací oblasti uvádí všechny widgety s pořadovými čísly a dále Zobrazit vše, Skrýt vše a Ztlumit vše. Samostatně oddělené `Zarovnat do mřížky` následuje před příkazy aplikace.

Zobrazení nebo obnovení widgetů je přenese před ostatní okna, aniž by změnilo jejich nastavení vždy navrchu. CalClock zajišťuje, že je po spuštění viditelný alespoň jeden widget. Druhé spuštění aktivuje již běžící instanci CalClocku a, není-li nic viditelné, obnoví naposledy skryté widgety. Po restartu Průzkumníka Windows se ikona v oznamovací oblasti automaticky znovu zaregistruje.

## Ukládání nastavení

Ve výchozím stavu se nastavení ukládá do:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

Ukládání do XML lze zapnout v Nastavení. Používá:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Import XML okamžitě načte a uloží jeho nastavení do právě zvoleného úložiště, aniž by změnil typ ukládání. Ztlumení se ukládá samostatně pro každý widget podporující zvuk.

## Sestavení

Požadavky:

- Microsoft Visual Studio se sadou nástrojů MSVC v145
- Windows SDK

Otevřete `CalClock.slnx`, vyberte `Release | x86` a sestavte řešení. Spustitelný soubor vznikne jako:

```text
Release\CalClock.exe
```

Podporována je pouze konfigurace Win32/x86. Projekt záměrně neposkytuje konfiguraci x64, protože integrace s ovládacím prvkem hodin Windows vyžaduje kompatibilitu x86.

## Licence

CalClock je dostupný pod [licencí MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
