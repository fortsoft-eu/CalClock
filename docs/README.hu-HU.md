# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · **Magyar** · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

A CalClock natív Win32/x86-alkalmazás Windows Vista és újabb rendszerekhez, amely egymástól függetlenül beállítható lebegő órákat és naptárakat jelenít meg az asztalon. Az értesítési területen fut, legfeljebb 32 minialkalmazást és 36 nyelvi változatot támogat; a program és minden minialkalmazás nyelve külön választható.

## Kezelés

Az órát vagy panelt a bal egérgombbal húzhatja. Az önálló naptárt a szabad területénél fogva mozgathatja. A minialkalmazásra vagy az értesítési terület ikonjára kattintva a jobb gombbal menüt nyithat. Az ikonra kattintva a bal gombbal elrejtheti a látható minialkalmazásokat; ha mind rejtett, csak a legutóbb elrejtettek térnek vissza.

## Minialkalmazások és beállítások

A Beállítások között analóg és digitális órákat, naptárakat, naptárat és órát tartalmazó paneleket, valamint képernyőórákat adhat hozzá, távolíthat el és másolhat. Minden minialkalmazás külön láthatósággal, Mindig felül állapottal, nyelvvel, időzónával és [-]HH:mm:ss.ff eltolással rendelkezik. A számlapméretek külön választhatók. A digitális órák másodperceket, vezető nullát, betűtípust, színeket, átlátszatlanságot és átlátszó hátteret támogatnak. A naptár megjeleníti a hétszámokat, kezdődhet vasárnappal, és a minialkalmazás nyelvét használja.

## Ébresztés és billentyűparancsok

Az órákhoz és panelekhez ébresztés állítható be. A program a hangfájlt maga játssza le egyszer vagy folyamatosan az ismétlés szerint; a többi fájlt és parancsot átadja a Windowsnak. Az ébresztő számlapra vagy kijelzőre kattintva, az Ébresztés leállítása paranccsal vagy az Esc billentyűvel a jelzés és a program hangja leállítható. A számlapra vagy digitális kijelzőre duplán kattintva a másodperceket kapcsolhatja. Az F1 a Súgót, a B a Beállításokat nyitja meg; az Esc elrejti a minialkalmazást, ha nem ébresztést állít le. A helyzetet húzás után, a párbeszédablak helyét bezáráskor, a beállításokat a kiválasztott tárolóban menti a program. Az újabb indítás a futó példányt aktiválja, és a minialkalmazásokat a munkaterület legközelebbi elérhető pontján tartja.

## Időbevitel és ébresztési műveletek

Az ébresztési idő HH:mm formátumú lehet kettősponttal, ponttal, szóközzel, más elválasztóval vagy anélkül. Egy vagy két számjegy órát, három vagy négy órát és percet jelent: 7, 12, 730, 0730 vagy 7:30. A mező elhagyásakor HH:mm alakra vált. Az eltolást jobbról, a másodpercektől olvassa: 2 jelentése 00:00:02.00, 230 és 0230 jelentése 00:02:30.00, 12345 jelentése 01:23:45.00. Elválasztóval két csoport percet és másodpercet, három órát, percet és másodpercet, a negyedik századmásodpercet jelent; előjel megadható. Az Ébresztés engedélyezve alatti napok adják a működés napjait; alapból mind kijelölt. Sorrendjük a program nyelvét követi, de a nyelvváltás nem módosítja a mentett napokat.

Az ébresztés megjeleníti a rejtett minialkalmazást, és előtérbe hozza a Mindig felül tartós módosítása nélkül. Az Időjelzés lejátszása az első rövid hangot öt másodperccel az ébresztés előtt indítja. Ez független az Időjelzés fültől; az egyidejű sorozatok egyesülnek. A Tesztelés villogtatja a számlapot vagy keretet, és ellenőrzi a fájlt, parancsot, hangot, távoli parancsfájl HTTP/HTTPS-címét és a kiválasztott teljes időjelzést. A teszt leállítása annak belső hangját és próbajelzését, az ébresztés leállítása annak belső hangját állítja le. Némításkor a lejátszás hangtalanul folytatódik, feloldáskor ismét hallható. A parancsok és távoli parancsfájlok nem állnak le.

Az Ébresztés fül Hangerő csúszkája az adott minialkalmazás belső lejátszását szabályozza. Az alapértelmezett −18 dB megőrzi a fájl eredeti szintjét (100%). Jobbra erősíti a hangot; a legnagyobb 0 dB körülbelül 794%. A −∞ dB csendet jelent. A változtatás teszt közben is hallható. A MIDI és a nem dekódolható, tartalék lejátszóval kezelt fájlok legfeljebb 100%-osak.

## Kijelölés, billentyűk és dátummásolás

A Beállítások az utolsó fület, a Hozzáadás az utoljára hozzáadott típust jegyzi meg. Az Eltávolítás vagy Del a módosítások alkalmazásakor minden kijelölt elemet eltávolít. Dupla kattintás megjeleníti a rejtett minialkalmazást, bejelöli a Látható értéket, és röviden kiemeli azt. A minialkalmazás menüjének Beállítások parancsa kiválasztja azt a listában. A naptár napjára kattintva a dátum kijelölődik és a vágólapra másolódik. Minden naptárnak külön formátuma van a beállításokban és menüjében. Mind a 33 formátum minden nyelven elérhető; a szöveges nevek és az alapértelmezett Rövid dátum a minialkalmazás nyelvét követik.

Az Insert átváltja az aktuális elem kijelölését, és egy sorral lejjebb lépteti a listakurzort. A Ctrl+C másol, a Ctrl+V a lista sorrendjében illeszti hozzá a másolatokat a program nyelvén adott névutótaggal. Legfeljebb 32 minialkalmazás lehet. A másolatok sorrendben kerülnek be a határig, a többiről értesítés jelenik meg. Az Alt+0, Alt+1, Alt+2 és Alt+3 analóg órán vagy naptár órával típuson a fő számlap méretét választja ki a legkisebbtől a legnagyobbig.

Az értesítési terület ikonjáról megnyitott beállításokban a legutóbb kiválasztott minialkalmazás beállításai jelennek meg.

## Elrendezés

A Rácsba rendezés megőrzi a hozzávetőleges kézi elrendezést, a középpontokat a legközelebbi rácspontokhoz illeszti és megszünteti az átfedéseket. A parancsot indító minialkalmazás helyben marad. A saját menü a saját monitorra, az értesítési ikon minden monitorra külön hat. Ismételve az elrendezés stabil marad. A beállításokbeli dupla kattintás gyors világoskék villogással jelöl; az ébresztés lassabban, pirosan villog. A Mindig felül kikapcsolása a többi ablak mögé küldi a minialkalmazást. A panel felső hivatkozása a mai napra tér vissza, az alsó a Windows klasszikus dátum- és időbeállításait nyitja meg. Az engedélyezett szélhez illesztés öt képponton belül a munkaterület széléhez húzza a mozgatott minialkalmazást. Átméretezéskor ugyanahhoz a szélhez vagy sarokhoz csatlakozik.

Önálló naptárban a Mai dátum sora a Megjelenés fülön vagy menüben az alsó sort kapcsolja. Az Ugrás a mai napra kiválasztja a mai dátumot és visszaállítja a havi nézetet. A minialkalmazás szerinti dátumváltáskor a mai nap automatikusan kijelölődik az aktuális nézet megtartásával.

## Megjelenés és tárolás

A megjelenés változásai azonnal láthatók az előnézetben. A Mégse elveti az alkalmazatlan változtatásokat, az Alapértelmezett megjelenés visszaállítja a típus alapértékeit. A digitális órához betűtípus, élsimítás, színek, átlátszatlanság, belső margó, szegélyvastagság és átlátszó háttér választható. Az órák, naptárak és panelek négy közös szegélystílust használnak; az egysoros szegély színezhető. A panel felső sorának, idejének és alsó sorának külön betűtípusa van, vezető nullával és számlapméretekkel. A témák és élsimítás a programhoz és minden minialkalmazáshoz külön adhatók meg. Egyéni naptárbetűtípusok a Windows klasszikus megjelenésével, illetve az alkalmazás vagy a minialkalmazás témáinak kikapcsolásával használhatók.

A beállítások XML-be exportálhatók. Az importálás azonnal betölti és a kijelölt tárolóba menti őket, a tárolótípus megváltoztatása nélkül. Az automatikus XML helye %AppData%\FortSoft\CalClock\settings.xml. Az XML írása törli a HKCU\SOFTWARE\FortSoft\CalClock kulcsot; a beállításjegyzékbe mentés törli az automatikus XML-t.

A Betűtípus élsimítása lehet ClearType, GDI vagy Nincs. A Vezető nulla választásai: „Igen” (alapértelmezett), „Nem, hely megtartása” és „Nem, hely nélkül”. A „Nem, hely megtartása” elrejti a nullát, de fenntartja a szélességét; a többi számjegy arányos betűtípusnál sem mozdul el. A képernyőórák középre igazítása ezt a helyet is figyelembe veszi. Az UTC-sor külön igazodik középre.

## Beállítások és menük

A nyelv, betűtípus, élsimítás, témák, tároló, Windowszal indítás és szélhez illesztés közös beállítás az Alkalmazás fülön. Első indításkor a Windows felületének nyelve, nem támogatott nyelvnél az amerikai angol lesz aktív. A minialkalmazás nyelve, élsimítása és témái csak arra érvényesek.

A minialkalmazás menüje az alkalmazható láthatóság-, Mindig felül-, másodperc-, méret- és dátummásolási választásokat, majd a Rácsba rendezés, Beállítások, Súgó, Névjegy és Kilépés parancsokat tartalmazza. Az ikon menüje számozott minialkalmazásokat, Összes megjelenítése, Összes elrejtése és Összes némítása parancsot, majd külön rácsparancsot ad. A megjelenítés vagy visszaállítás előtérbe hoz a Mindig felül módosítása nélkül. Az újabb indítás szükség esetén visszahozza a legutóbb elrejtetteket. A számlapméret és másodpercmutató a Windowstól függ. Az Ébresztés és Időjelzés a menüből is kapcsolható; az idő, intervallum és részleges hétnél a kijelölt napok is látszanak. A Némítás a Némítva állapotnak felel meg az Általános fülön. Az Összes némítása és az M mindent némít, ismételve csak az általa némított hangokat állítja vissza. Nap nélküli ébresztés engedélyezése megnyitja az Ébresztés fület.

## Hallható időjelzés

A jelzés a Greenwich Time Signal (GTS) mintáját követi: öt rövid hang az utolsó öt másodpercben, majd hosszú hang a pontos időhatáron. Az Időjelzés fülön az Időjelzés engedélyezve és 1, 5, 10, 15, 20, 30 vagy 60 perces intervallum választható a minialkalmazás ideje szerint. Kezdetben kikapcsolt, órás intervallummal. A menübeli kapcsolás megőrzi az intervallumot. Figyelembe veszi az UTC-t, időzónát, eltolást és NTP-t; 20 percnél :00, :20 és :40 időpontban szól. Az egyidejű óra- és ébresztési jelzések egyesülnek. Némítás után az aktuális hang befejeződhet; a következők kimaradnak, és feloldáskor csak a következő ütemezett hang szól. Az önálló Naptárnak nincs ébresztése, időjelzése vagy némítása.

Az Alkalmazás fül Időjelzés hangja beállítása Beépített generátor (alapértelmezett) vagy Rendszerhang lehet minden órához és ébresztéshez. Az Időjelzés hangereje dB-ben mutatja a generátor szintjét: a jobb szélső 0 dB a legnagyobb torzítatlan szinuszamplitúdó, −∞ dB a csend, −18 dB az alapérték. A Tesztelés folyamatos próbát indít, a Teszt leállítása befejezi. Mindkét hang tesztelhető; a teszt nem mentődik. A csúszka nyomva tartása is szól az egér felengedéséig, ha nincs gombbal indított teszt. A lejátszás a következő egész másodpercnél indul: rövid hang másodpercenként és hosszú :00, :05, :10 stb. időpontban. Az egyidejű teszt-, óra- és ébresztési hangok egyetlen hangot használnak. A rendszerhangnál csak a hangerőcsúszka tiltott. Leállításkor az aktuális hang befejeződik; a hosszú még fél másodpercig tarthat. A századmásodperces eltolás is számít; az átfedő hangok az utolsó átfedés végéig megszakítás nélkül szólnak.

## További órák

A Naptár órával az Általános fülön legfeljebb két további órát mutathat saját névvel és időzónával. Ekkor mindegyik a hét helyi napját is jelzi. A méret külön választható a Megjelenés fülön vagy a számlap helyi menüjében. A további óráknak nincs másodpercmutatójuk. Hozzáadás, eltávolítás és átméretezés megtartja a munkaterület széleihez csatlakozást.

Csak a fő számlapra közvetlenül történő dupla kattintás kapcsolja a másodpercmutatóját. A további órák menüje csak méretet tartalmaz. Közös a minialkalmazás nyelve, időformátuma, betűtípusai és eltolása; digitális idejük másodpercek nélküli.

## Időformátum és időzónák

Az Általános fül Időformátum beállítása Nyelv szerinti (alapértelmezett), 12 órás vagy 24 órás. A kézi választás nyelvváltáskor is megmarad. Az elválasztók és időjelölések a minialkalmazás nyelvét követik. Az AM/PM alapból bekapcsolt, csak a 12 órás jelölést szabályozza; saját nyelvi jelölés hiányában AM/PM használatos. A képernyőórák külön sorban, az idő alatt jelzik. Az UTC mindig 24 órás formátumot használ. A név szerinti zónák követik a helyi és nyári időszámítást; az eltolás az aktuális dátumra érvényes. A külön UTC-elemek állandó eltolások −12:00 és +14:00 között 15 perces lépéssel, nyári időszámítás nélkül.

## Időforrás és NTP-napló

Az Idő fül a Windows rendszeridejét vagy NTP-kiszolgálókat választ az egész programhoz. Az NTP csak a CalClock idejét módosítja, a Windows óráját soha. Az első érvényes válaszig a rendszeridő használatos. Az NTP az alapértelmezett. Az automatikus csoport a rendszer régiója szerint cseh és szlovák kiszolgálókat, Európához PTB-t vagy világméretű csoportot választ. A méréseket a hálózati késés és a többi választól való eltérés szerint szűri. A Szinkronizálás most azonnal új mérést indít.

Szinkronizálás után a CalClock órája a Windows rendszeridejének későbbi változásaitól függetlenül jár. Kapcsolatvesztés vagy kiszolgálóváltás esetén az utolsó érvényes szinkronizálástól folytatja az új válaszig; az állapot a program bezárásáig marad meg.

Az Idő fül indítás óta naplózza az NTP-lekérdezéseket. A bejegyzés dátumot, helyi gépidőt, kiszolgálót és állapotot tartalmaz. Az OK érvényes válasz, θ az eltérés a Windows idejétől. Az ERR az okot és az esetleges hibakódot adja. A csoport utolsó bejegyzése az összevont Θ eltolást is mutatja, ha vannak használható mérések. Az eltolás milliszekundumban, négy tizedesjeggyel jelenik meg: pozitívnál a kiszolgáló előrébb jár, negatívnál késik. A Θ az elfogadott mérésekre épül, és a szinkronizálási állapotban is látható. A Napló mentése CSV-be exportálja a bejegyzéseket eltolásokkal és hibarészletekkel. A napló nem marad meg két indítás között; kilépés előtt mentse, ha szükséges.

## Képernyőóra

A digitális óra egy vagy több monitort kitölthet, a többit elsötétítheti. A betűméret a monitor magasságának százaléka; betűtípus, élsimítás, színek és belső margó is választható. Az UTC külön sorban lehet. Alapból fehér szöveg jelenik meg fekete háttéren. Nyitott Beállítások mellett az óra kicsi, mozgatható előnézet a monitor képarányával, mentett helyzettel. A rács ezt a típust nem mozgatja. Az Esc nyitott Beállítások mellett is elrejti az órát és megszünteti az elsötétítést.

Az egérmutató rövid tétlenség után eltűnik a képernyőóra és az elsötétített monitorok fölött, és egérmozgáskor visszatér. A kis előnézet fölött látható marad.

## Fordítás és csomagolás

Microsoft Visual Studio, MSVC v145 eszközkészlet és Windows SDK szükséges. Nyissa meg a `CalClock.slnx` fájlt, válassza a `Release | x86` konfigurációt, és fordítsa le a megoldást. A program a `Release\CalClock.exe` helyen készül el. Csak Win32/x86 támogatott, mert a Windows óravezérlőjének használata x86-kompatibilitást igényel.

Fordítás után a `.\PackageRelease.ps1` létrehozza a `CalClock-<version>-win32.zip` archívumot; a verziót a `Release\CalClock.exe` fájlból olvassa. A gyökérben `CalClock.exe` és `license.txt` található. Az opcionális `-SignerName`, `-SignToolPath` és `-TimestampServer` aláírási paraméterek futtatáskor adhatók meg. A meglévő érvényes Authenticode-aláírást ellenőrzi és nem cseréli le. A régi CalClock ZIP-csomagokat minden futtatás elején eltávolítja; aláírási vagy ellenőrzési hiba leállítja a csomagolást.

## Licenc

A CalClock az [MIT-licenc](../license.txt) feltételeivel érhető el.

Copyright © Petr Červinka — FortSoft 2026
