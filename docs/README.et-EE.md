# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · **Eesti** · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock on Windows Vista ja uuemate versioonide Win32/x86-rakendus, mis kuvab töölaual eraldi seadistatavaid hõljuvaid kelli ja kalendreid. See töötab olekualal ning toetab kuni 32 vidinat ja 36 keelevalikut; rakenduse ja iga vidina keel valitakse eraldi.

## Juhtimine

Lohistage kella või paneeli hiire vasaku nupuga. Eraldi kalendrit saab lohistada vabast alast. Paremklõps vidinal või olekuala ikoonil avab menüü. Vasakklõps ikoonil peidab nähtavad vidinad; kui kõik on peidetud, taastab see ainult viimati peidetud vidinad.

## Vidinad ja sätted

Sätetes saab lisada, eemaldada ja dubleerida analoogkelli, digitaalkelli, kalendreid, kalendri ja kella paneele ning ekraanikelli. Igal vidinal on oma nähtavus, suvand Alati pealmine, keel, ajavöönd ja nihe kujul [-]HH:mm:ss.ff. Analoogkella ja paneeli kellade suurust saab valida eraldi. Digitaalkellal on sekundite, algusnulli, fondi, värvide, läbipaistmatuse ja läbipaistva tausta sätted. Kalender toetab nädalanumbreid ja pühapäeva nädala esimese päevana ning kasutab vidina keelt.

## Äratus ja kiirklahvid

Kelladel ja paneelidel võib olla äratus. Rakendus esitab helifaili ise ühe korra või pidevalt vastavalt kordamise sättele; muud failid ja käsud edastatakse Windowsile. Klõps ärataval sihverplaadil või kuval, Peata äratus või Esc peatab nii äratuse tähistuse kui ka rakenduse heli. Topeltklõps sihverplaadil või digitaalkuval lülitab sekundeid. F1 avab spikri, B sätted ja Esc peidab vidina, kui ei peatata äratust. Vidina asukoht salvestatakse lohistamise järel, dialoogi asukoht sulgemisel ja sätted valitud salvestuskohta. Korduskäivitus aktiveerib töötava eksemplari ning vidinad jäävad tööala lähimasse saadaolevasse punkti.

## Aja sisestamine ja äratuse toimingud

Äratuse aeg lubab vormingut HH:mm kooloni, punkti, tühiku või muu eraldajaga või eraldajata. Üks või kaks numbrit tähendavad tunde, kolm või neli tunde ja minuteid: 7, 12, 730, 0730 või 7:30. Väljalt lahkumisel teisendatakse väärtus vormingusse HH:mm. Nihet loetakse paremalt alates sekunditest: 2 tähendab 00:00:02.00, 230 ja 0230 tähendavad 00:02:30.00 ning 12345 tähendab 01:23:45.00. Eraldajatega tähendavad kaks rühma minuteid ja sekundeid, kolm tunde, minuteid ja sekundeid ning neljas sajandiksekundeid; märk on lubatud. Päevad suvandi Äratus lubatud all määravad äratuspäevad; vaikimisi on valitud kõik. Järjestus järgib rakenduse keelt, kuid keele muutmine ei muuda salvestatud päevi.

Äratus kuvab peidetud vidina ja toob selle ette, muutmata püsivalt suvandit Alati pealmine. Esita ajasignaal alustab esimest lühikest tooni viis sekundit enne äratust. See on vahekaardist Signaal sõltumatu; samaaegsed jadad ühendatakse. Testi paneb sihverplaadi või raami vilkuma ja kontrollib faili, käsku, heli, kaugskripti HTTP/HTTPS-aadressi ning valitud ajasignaali kogu jada. Testi peatamine lõpetab selle sisemise heli ja proovisignaali; äratuse peatamine lõpetab selle sisemise heli. Vaigistamisel esitus jätkub hääletult ja muutub vaigistuse eemaldamisel taas kuuldavaks. Käske ja kaugskripte see ei peata.

Vahekaardi Äratus liugur Helitugevus määrab selle vidina sisemise heliesituse tugevuse. Vaikimisi −18 dB säilitab faili algtaseme (100%). Paremale liikumine võimendab heli; maksimaalne 0 dB vastab ligikaudu 794%-le. −∞ dB tähendab vaikust. Muutus kostab ka testi ajal. MIDI ja failid, mida ei saa dekodeerida ning esitatakse varumängijaga, on piiratud 100%-ga.

## Valimine, klahvid ja kuupäeva kopeerimine

Sätted jätavad meelde viimase vahekaardi ja Lisa viimati lisatud tüübi. Eemalda või Del eemaldab kõik valitud üksused muudatuste rakendamisel. Topeltklõps üksusel kuvab peidetud vidina, märgib Nähtav ja tõstab vidina korraks esile. Vidina menüü Sätted valib loendis selle vidina. Kalendripäeval klõpsamine valib kuupäeva ja kopeerib selle lõikelauale. Igal kalendril on oma kopeerimisvorming sätetes ja menüüs. Kõik 33 vormingut on saadaval igas keeles; tekstilised nimetused ja vaikevalik Lühike kuupäev järgivad vidina keelt.

Insert muudab praeguse üksuse valikut ja viib loendikursori ühe rea alla. Ctrl+C kopeerib valitud vidinad, Ctrl+V lisab koopiad loendi järjekorras ning nimelaiendi rakenduse keeles. Lubatud on kuni 32 vidinat. Koopiad lisatakse järjekorras piirini ja ülejäänute kohta kuvatakse teade. Alt+0, Alt+1, Alt+2 ja Alt+3 valivad analoogkella või kalendri ja kella paneeli peamise sihverplaadi suuruse väikseimast suurimani.

Olekuala ikoonilt seadete avamisel taastatakse viimati valitud vidin.

## Vidinate paigutus

Paiguta ruudustikku säilitab ligikaudse käsitsi paigutuse, tõmbab keskpunktid lähimatele ruudustikupunktidele ja kõrvaldab kattumised. Käsu käivitanud vidin jääb paigale. Vidina menüü mõjutab selle kuvarit, olekuala ikoon iga kuvarit eraldi. Kordamine säilitab stabiilse paigutuse. Sätete topeltklõps tõstab vidina esile kiire helesinise vilkumisega; äratus vilgub aeglasemalt punaselt. Alati pealmine väljalülitamine saadab vidina teiste akende taha. Paneeli ülemine link toob kalendri tänasele kuupäevale ja alumine avab Windowsi klassikalised kuupäeva ja kellaaja sätted. Servatõmme haarab lohistatava vidina tööala serva külge kuni viie piksli kauguselt. Suuruse muutmisel säilib kinnitus sama serva või servapaari külge.

Eraldi kalendris kuvab või peidab Tänase kuupäeva rida vahekaardil Ilme või menüüs alumise rea. Mine tänasele kuupäevale valib tänase päeva ja taastab kuuvaate. Kui vidina aja järgi kuupäev muutub, valitakse tänane kuupäev automaatselt praegust kalendrivaadet säilitades.

## Ilme ja salvestamine

Ilme muutused on kohe eelvaates näha. Loobu hülgab rakendamata muudatused ja Vaikeilme taastab vidinatüübi vaikesätted. Digitaalkell toetab fonti, silumist, värve, läbipaistmatust, siseveerist, äärise laiust ja läbipaistvat tausta. Kellad, kalendrid ja paneelid jagavad nelja ääriselaadi; ühekordse äärise värvi saab valida. Paneelil on eraldi fondid ülemisele reale, kellaajale ja alumisele reale, algusnull ning valitavad sihverplaadisuurused. Kujundused ja silumine määratakse rakendusele ja igale vidinale eraldi. Kohandatud kalendrifonte saab kasutada Windowsi klassikalise ilmega või siis, kui rakenduse või vidina kujundused on välja lülitatud.

Sätteid saab eksportida XML-i. Import laadib ja salvestab sätted kohe praegusesse salvestuskohta selle tüüpi muutmata. Automaatne XML asub failis %AppData%\FortSoft\CalClock\settings.xml. XML-i kirjutamine eemaldab võtme HKCU\SOFTWARE\FortSoft\CalClock; registrisse salvestamine eemaldab automaatse XML-i.

Fondi silumine pakub ClearType, GDI ja Puudub. Algusnull pakub Kuva (vaikimisi), Säilita ruum ja Ilma ruumita. Säilita ruum peidab nulli, kuid reserveerib selle laiuse valitud fondis; ülejäänud numbrid säilitavad asukoha ka proportsionaalse fondiga. Ekraanikella keskjoondus arvestab reserveeritud ruumi. UTC-real on oma keskjoondus.

## Sätted ja menüüd

Rakenduse keel, font, silumine, kujundused, salvestuskoht, Windowsiga käivitamine ja servatõmme on ühised sätted vahekaardil Rakendus. Esmakäivitamisel kasutatakse Windowsi kasutajaliidese keelt või selle puudumisel USA inglise keelt. Vidina keel, silumine ja kujundused mõjutavad vaid seda vidinat.

Vidina menüüs on selle tüübile sobivad nähtavuse, esiplaanil hoidmise, sekundite, suuruse ja kuupäeva kopeerimise valikud, seejärel Paiguta ruudustikku, Sätted, Spikker, Teave ja Välju. Olekuala menüü loetleb nummerdatud vidinad, Kuva kõik, Peida kõik ja Vaigista kõik ning eraldi ruudustikukäsu. Kuvamine või taastamine toob vidina ette suvandit Alati pealmine muutmata. Korduskäivitus taastab vajaduse korral viimati peidetud vidinad. Sihverplaadisuurused ja sekundiosuti tugi sõltuvad Windowsist. Äratus ja Signaal on lülitatavad ka menüüs, kus kuvatakse aeg, intervall ning osalise nädala korral aktiivsed päevad. Vaigista vastab vahekaardi Üldine valikule Vaigistatud. Vaigista kõik ja klahv M vaigistavad kõik vidinad ning järgmisel korral taastavad heli ainult neil, mille nad ise vaigistasid. Päevadeta äratuse lubamine avab vahekaardi Äratus.

## Kuuldav ajasignaal

Signaal järgib Greenwichi ajasignaali (GTS): viis lühikest tooni viimase viie sekundi jooksul ja pikk toon täpsel ajahetkel. Vahekaardil Signaal on Ajasignaal lubatud ja intervallid 1, 5, 10, 15, 20, 30 või 60 minutit vidina kuvatava aja järgi. Vaikimisi on signaal väljas ja valitud tunnine intervall. Menüü lülitus säilitab intervalli. Ajapiir arvestab UTC-d, ajavööndit, nihet ja NTP-d. 20-minutilise intervalliga kõlab signaal :00, :20 ja :40. Samaaegsed vidina- ja äratussignaalid ühendatakse. Vaigistamisel võib praegune toon lõppeda; järgmised jäetakse vahele ja heli taastamisel kõlab alles järgmine kavandatud toon. Eraldi Kalender ei toeta äratust, ajasignaali ega vaigistamist.

Vahekaardi Rakendus Ajasignaali heli pakub Sisseehitatud generaatorit (vaikimisi) ja Süsteemi helisignaali. Valik kehtib kõigile vidinatele ja äratustele. Ajasignaali helitugevus näitab generaatori taset dB-des: parempoolne 0 dB on suurim moonutuseta siinusamplituud, −∞ dB vaikus ja vaikesäte −18 dB. Testi käivitab pideva prooviesituse ning Peata test lõpetab selle. Testida saab mõlemat heli; testi ei salvestata. Liuguri hoidmine esitab samuti heli kuni hiire vabastamiseni, kui nuputest pole käimas. Esitus algab järgmisel täissekundil: lühike toon igal sekundil ja pikk toon :00, :05, :10 jne. Kõik samaaegsed proovi-, vidina- ja äratussignaalid jagavad ühte tooni. Peatamine lubab praegusel toonil lõppeda; pikk toon võib kesta veel pool sekundit. Arvestatakse ka nihke sajandikke ning kattuvad toonid kõlavad katkestuseta viimase kattumise lõpuni.

## Lisakellad

Kalender ja kell võib vahekaardil Üldine kuvada kuni kahte lisakella oma nime ja ajavööndiga. Iga kell kuvab siis ka kohaliku nädalapäeva. Sihverplaadi suurus valitakse eraldi vahekaardil Ilme või selle paremklõpsumenüüs. Lisakelladel pole sekundiosutit. Lisamine, eemaldamine ja suuruse muutmine säilitavad kinnituse tööala servade külge.

Ainult otse peamisel sihverplaadil tehtud topeltklõps lülitab selle sekundiosutit. Lisakella menüüs on ainult suurused. Lisakellad jagavad vidina keelt, ajavormingut, fonte ja nihet; nende digitaalkuva ei näita sekundeid.

## Kellaajavorming ja ajavööndid

Kellaajavorming vahekaardil Üldine pakub Keele vaikesätet, 12 tundi ja 24 tundi. Esimene järgib vidina keelt; käsivalik säilib keele vahetamisel. Eraldajad ja ajatähised järgivad keelt. AM/PM on vaikimisi sees ja juhib ainult 12-tunnise kuva tähist; keele oma tähise puudumisel kasutatakse AM/PM-i. Ekraanikell kuvab tähise eraldi real kellaaja all. UTC kasutab alati 24-tunnist vormingut. Nimega ajavööndid arvestavad kohalikku ja suveaega; nime kõrval olev nihe kehtib praegusele kuupäevale. Eraldi UTC-valikud on püsinihked −12:00 kuni +14:00 15-minutilise sammuga, ilma suveajata.

## Aja allikas ja NTP-logi

Vahekaart Aeg valib Windowsi süsteemiaja või NTP-serverid kogu rakendusele. NTP muudab ainult CalClocki aega; Windowsi kella ei muudeta. Esimese sobiva vastuseni kasutatakse süsteemiaega. NTP on vaikevalik. Automaatrühm valib süsteemi piirkonna järgi Tšehhi ja Slovakkia serverid, Euroopa jaoks PTB või ülemaailmse rühma. Mõõtmisi filtreeritakse võrgulatentsuse ja teistest vastustest kõrvalekallete järgi. Sünkrooni kohe alustab uut mõõtmist.

Pärast sünkroonimist käib CalClocki kell sõltumata Windowsi süsteemiaja hilisematest muutustest. Ühenduse kadumisel või serverite vahetamisel jätkab kell viimasest sobivast sünkroonimisest uue vastuseni; olek säilib rakenduse sulgemiseni.

Vahekaart Aeg logib NTP-päringud käivitamisest alates. Kirje sisaldab kuupäeva, arvuti kohalikku aega, serverit ja olekut. OK näitab sobivat vastust ja θ selle nihet Windowsi süsteemiajast. ERR annab põhjuse ja võimaliku veakoodi. Päringurühma viimane kirje näitab ka ühendatud nihet Θ, kui on kasutatavaid mõõtmisi. Nihked on millisekundites nelja kümnendkohaga: positiivne tähendab serveri edestamist ja negatiivne mahajäämist. Θ põhineb vastu võetud mõõtmistel ja ilmub ka sünkroonimisolekus. Salvesta logi ekspordib CSV koos nihete ja veateabega. Logi ei säili käivituste vahel; vajaduse korral salvestage see enne väljumist.

## Ekraanikell

Digitaalkell võib täita ühe või mitu kuvarit ja tumendada ülejäänud. Fondisuurus on protsent kuvari kõrgusest; valida saab ka fondi, silumise, värvid ja siseveerise. UTC võib olla eraldi real. Vaikimisi on tekst valge ja taust must. Avatud sätetega esitatakse kella väikese liigutatava eelvaatena, mis säilitab kuvari kuvasuhte ja mille asukoht salvestatakse. Ruudustikupaigutus seda tüüpi ei liiguta. Esc peidab kella ja eemaldab tumenduse ka avatud sätetega.

Hiirekursor peitub ekraanikella või tumendatud kuvarite kohal pärast lühikest tegevusetust ning ilmub hiire liigutamisel. Väikese eelvaate kohal jääb see nähtavaks.

## Koostamine ja pakkimine

Vaja on Microsoft Visual Studiot MSVC v145 tööriistakomplektiga ja Windows SDK-d. Avage `CalClock.slnx`, valige `Release | x86` ja koostage lahendus. Käivitatav fail tekib asukohta `Release\CalClock.exe`. Toetatakse ainult Win32/x86 konfiguratsiooni, sest Windowsi kellajuhtelemendi kasutamine nõuab x86-ühilduvust.

Pärast koostamist loob `.\PackageRelease.ps1` arhiivi `CalClock-<version>-win32.zip`; versioon loetakse failist `Release\CalClock.exe`. Arhiivi juures on `CalClock.exe` ja `license.txt`. Soovi korral antakse allkirjastamisparameetrid `-SignerName`, `-SignToolPath` ja `-TimestampServer` käivitamisel. Olemasolevat sobivat Authenticode-allkirja kontrollitakse ja seda ei asendata. Varasemad CalClocki ZIP-arhiivid eemaldatakse iga käivituse alguses; allkirjastamis- või kontrollitõrge peatab pakkimise.

## Litsents

CalClock on saadaval [MIT-litsentsiga](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
