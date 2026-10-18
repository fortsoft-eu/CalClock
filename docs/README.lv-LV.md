# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · **Latviešu** · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock ir Win32/x86 programma Windows Vista un jaunākām versijām ar atsevišķi iestatāmiem peldošiem pulksteņiem un kalendāriem darbvirsmā. Tā darbojas paziņojumu apgabalā un atbalsta līdz 32 logrīkiem un 36 valodu izvēlēm; programmas un katra logrīka valodu izvēlas atsevišķi.

## Vadība

Velciet pulksteni vai paneli ar peles kreiso pogu. Atsevišķu kalendāru velciet aiz brīvās zonas. Labais klikšķis uz logrīka vai paziņojumu apgabala ikonas atver izvēlni. Kreisais klikšķis uz ikonas paslēpj redzamos logrīkus; ja visi ir paslēpti, atjauno tikai pēdējos paslēptos.

## Logrīki un iestatījumi

Iestatījumos var pievienot, noņemt un dublēt analogos un digitālos pulksteņus, kalendārus, kalendāra un pulksteņa paneļus un ekrāna pulksteņus. Katram logrīkam ir sava redzamība, Vienmēr virspusē, valoda, laika josla un nobīde [-]HH:mm:ss.ff. Ciparnīcu lielumi ir izvēlami atsevišķi. Digitālajiem pulksteņiem ir sekundes, sākuma nulle, fonts, krāsas, necaurspīdīgums un caurspīdīgs fons. Kalendāri atbalsta nedēļu numurus un svētdienu kā pirmo dienu un izmanto logrīka valodu.

## Modinātājs un īsinājumtaustiņi

Pulksteņi un paneļi atbalsta modinātāju. Programma pati atskaņo skaņas failu vienreiz vai nepārtraukti atbilstoši atkārtošanas izvēlei; citus failus un komandas nodod Windows. Klikšķis uz aktīvā modinātāja ciparnīcas vai displeja, Apturēt modinātāju vai Esc aptur indikāciju un programmas skaņu. Dubultklikšķis uz ciparnīcas vai digitālā displeja pārslēdz sekundes. F1 atver palīdzību, B iestatījumus, Esc paslēpj logrīku, ja netiek apturēts modinātājs. Logrīka novietojumu saglabā pēc vilkšanas, dialoga novietojumu aizverot, iestatījumus izvēlētajā krātuvē. Atkārtota palaišana aktivizē esošo programmas eksemplāru un notur logrīkus tuvākajā pieejamajā darba apgabala vietā.

## Laika ievade un modinātāja darbības

Modinātāja laiks pieņem HH:mm ar kolu, punktu, atstarpi, citu atdalītāju vai bez tā. Viens vai divi cipari ir stundas, trīs vai četri – stundas un minūtes: 7, 12, 730, 0730 vai 7:30. Atstājot lauku, vērtība kļūst par HH:mm. Nobīdi lasa no labās puses, sākot ar sekundēm: 2 ir 00:00:02.00, 230 un 0230 ir 00:02:30.00, 12345 ir 01:23:45.00. Ar atdalītājiem divas grupas nozīmē minūtes un sekundes, trīs – stundas, minūtes un sekundes, ceturtā – sekundes simtdaļas; atļauta zīme. Dienas zem Modinātājs ieslēgts nosaka darbības dienas; sākumā atlasītas visas. Secība atbilst programmas valodai, bet valodas maiņa nemaina saglabātās dienas.

Modinātājs parāda paslēpto logrīku un izvirza to priekšplānā bez pastāvīgas Vienmēr virspusē maiņas. Atskaņot laika signālu sāk pirmo īso toni piecas sekundes pirms modinātāja. Šī izvēle ir neatkarīga no cilnes Signāls; vienlaicīgās virknes tiek apvienotas. Pārbaudīt ieslēdz ciparnīcas vai rāmja mirgošanu un pārbauda failu, komandu, skaņu, attālā skripta HTTP/HTTPS adresi un izvēlēto pilno laika signālu. Pārbaudes apturēšana pārtrauc tās iekšējo skaņu un izmēģinājuma signālu; modinātāja apturēšana pārtrauc tā iekšējo skaņu. Izslēdzot skaņu, atskaņošana turpinās nedzirdami un kļūst dzirdama pēc ieslēgšanas. Komandas un attālie skripti netiek apturēti.

Slīdnis Skaļums cilnē Modinātājs regulē šī logrīka iekšējo atskaņošanu. Noklusējuma −18 dB saglabā faila sākotnējo līmeni (100%). Pa labi skaņa tiek pastiprināta; lielākie 0 dB atbilst apmēram 794%. −∞ dB ir klusums. Izmaiņas dzirdamas arī pārbaudē. MIDI un faili, kurus nevar dekodēt un atskaņo rezerves atskaņotājs, ir ierobežoti līdz 100%.

## Atlase, taustiņi un datuma kopēšana

Iestatījumi atceras pēdējo cilni, Pievienot – pēdējo pievienoto tipu. Noņemt vai Del noņem visas atlasītās vienības pēc izmaiņu lietošanas. Dubultklikšķis uz vienības parāda paslēptu logrīku, atlasa Redzams un īslaicīgi izceļ logrīku. Iestatījumi logrīka izvēlnē atlasa to sarakstā. Klikšķis uz kalendāra dienas atlasa datumu un kopē to starpliktuvē. Katram kalendāram ir savs formāts iestatījumos un izvēlnē. Visi 33 formāti ir pieejami jebkurā valodā; teksta nosaukumi un noklusējuma Īsais datums atbilst logrīka valodai.

Insert pārslēdz pašreizējās vienības atlasi un pārvieto saraksta kursoru rindu uz leju. Ctrl+C kopē logrīkus, Ctrl+V pievieno kopijas saraksta secībā ar nosaukuma sufiksu programmas valodā. Atļauti līdz 32 logrīkiem. Kopijas pievieno secīgi līdz robežai; par atlikušajām parāda paziņojumu. Alt+0, Alt+1, Alt+2 un Alt+3 analogajā pulkstenī vai kalendārā ar pulksteni izvēlas galvenās ciparnīcas lielumu no mazākā līdz lielākajam.

Atverot iestatījumus no paziņojumu apgabala ikonas, tiek atlasīts pēdējais izvēlētais logrīks.

## Logrīku izkārtojums

Sakārtot režģī saglabā aptuveno manuālo izkārtojumu, pievelk centrus tuvākajiem režģa punktiem un novērš pārklāšanos. Logrīks, kura izvēlnē izsaukta komanda, paliek vietā. Logrīka izvēlne ietekmē tā monitoru, paziņojumu ikona katru monitoru atsevišķi. Atkārtojot izkārtojums paliek stabils. Dubultklikšķis iestatījumos izceļ logrīku ar ātru gaišzilu mirgošanu; modinātājs mirgo lēnāk sarkani. Izslēdzot Vienmēr virspusē, logrīks tiek novietots aiz pārējiem logiem. Paneļa augšējā saite atgriež kalendāru šodienā, apakšējā atver Windows klasiskos datuma un laika iestatījumus. Ieslēgta pievilkšana pievelk vilktu logrīku darba apgabala malai līdz piecu pikseļu attālumā. Lieluma maiņa saglabā piesaisti tai pašai malai vai malu pārim.

Atsevišķā kalendārā Šodienas rinda cilnē Izskats vai izvēlnē rāda vai slēpj apakšējo rindu. Pāriet uz šodienu atlasa šodienas datumu un atjauno mēneša skatu. Mainoties datumam pēc logrīka laika, šodiena tiek atlasīta automātiski, saglabājot pašreizējo skatu.

## Izskats un glabāšana

Izskata izmaiņas uzreiz redzamas priekšskatījumā. Atcelt atmet nelietotās izmaiņas, Noklusējuma izskats atjauno logrīka tipa noklusējumus. Digitālie pulksteņi piedāvā fontu, nogludināšanu, krāsas, necaurspīdīgumu, iekšējo atkāpi, apmales platumu un caurspīdīgu fonu. Pulksteņiem, kalendāriem un paneļiem ir četri kopīgi apmales stili; vienas līnijas apmalei var izvēlēties krāsu. Panelim ir atsevišķi augšējās rindas, laika un apakšējās rindas fonti, sākuma nulle un ciparnīcu lielumi. Dizainus un nogludināšanu iestata programmai un katram logrīkam. Pielāgotus kalendāra fontus var izmantot ar Windows klasisko izskatu vai tad, ja lietotnei vai logrīkam ir izslēgti dizaini.

Iestatījumus var eksportēt XML. Imports tos uzreiz ielādē un saglabā izvēlētajā krātuvē, nemainot tās tipu. Automātiskais XML ir %AppData%\FortSoft\CalClock\settings.xml. XML ierakstīšana noņem HKCU\SOFTWARE\FortSoft\CalClock atslēgu; saglabāšana reģistrā noņem automātisko XML.

Fonta nogludināšana piedāvā ClearType, GDI un Nav. Sākuma nulle piedāvā Rādīt (noklusējums), Saglabāt vietu un Bez vietas. Saglabāt vietu slēpj nulli, rezervējot tās platumu izvēlētajā fontā; pārējie cipari paliek vietā arī proporcionālā fontā. Ekrāna pulksteņi tiek centrēti, ieskaitot rezervēto vietu. UTC rindai ir atsevišķa centrēšana.

## Iestatījumi un izvēlnes

Programmas valoda, fonts, nogludināšana, dizaini, krātuve, palaišana kopā ar Windows un pievilkšana ir kopīgi iestatījumi cilnē Programma. Pirmajā palaišanā izmanto Windows saskarnes valodu vai ASV angļu valodu, ja tā netiek atbalstīta. Logrīka valoda, nogludināšana un dizaini ietekmē tikai to.

Logrīka izvēlnē ir tam piemērotās redzamības, Vienmēr virspusē, sekunžu, lieluma un datuma kopēšanas izvēles, tad Sakārtot režģī, Iestatījumi, Palīdzība, Par programmu un Iziet. Ikonas izvēlnē ir numurēti logrīki, Rādīt visus, Paslēpt visus un Izslēgt visu skaņu, pēc tam atsevišķa režģa komanda. Parādīšana vai atjaunošana izvirza logrīku priekšplānā bez Vienmēr virspusē maiņas. Atkārtota palaišana vajadzības gadījumā atjauno pēdējos paslēptos logrīkus. Ciparnīcas un sekunžu rādītāja atbalsts atkarīgs no Windows. Modinātāju un Signālu var pārslēgt izvēlnē, kur redzams laiks, intervāls un atlasītās dienas, ja nav atlasīta visa nedēļa. Izslēgt skaņu atbilst Skaņa izslēgta cilnē Vispārīgi. Izslēgt visu skaņu un M izslēdz visu logrīku skaņu; atkārtoti ieslēdz tikai to, ko šī komanda izslēgusi. Modinātāja ieslēgšana bez atlasītas dienas atver tā cilni.

## Skaņas laika signāls

Signāls atbilst Griničas laika signālam (GTS): pieci īsi toņi pēdējās piecās sekundēs un garš tonis precīzi noteiktajā brīdī. Cilnē Signāls ir Laika signāls ieslēgts un 1, 5, 10, 15, 20, 30 vai 60 minūšu intervāli pēc logrīka laika. Sākumā izslēgts, atlasīts stundas intervāls. Pārslēgšana izvēlnē saglabā intervālu. Ņem vērā UTC, joslu, nobīdi un NTP; 20 minūšu intervālā skan :00, :20 un :40. Vienlaicīgie logrīku un modinātāju signāli apvienojas. Izslēdzot skaņu, pašreizējais tonis var beigties; nākamie tiek izlaisti līdz nākamajam plānotajam tonim pēc skaņas ieslēgšanas. Atsevišķam Kalendāram nav modinātāja, laika signāla vai skaņas izslēgšanas.

Cilnē Programma Laika signāla skaņa piedāvā Iebūvēts ģenerators (noklusējums) un Sistēmas pīkstiens visiem logrīkiem un modinātājiem. Laika signāla skaļums rāda ģeneratora līmeni dB: labajā galā 0 dB ir maksimālā neizkropļotā sinusoīdas amplitūda, −∞ dB klusums, noklusējums −18 dB. Pārbaudīt sāk nepārtrauktu priekšskatījumu, Apturēt pārbaudi to beidz. Pārbaudāmas abas skaņas; pārbaude netiek saglabāta. Turot slīdni, skaņa skan līdz peles atlaišanai, ja nenotiek pogas pārbaude. Atskaņošana sākas nākamajā veselajā sekundē: īss tonis katru sekundi un garš :00, :05, :10 utt. Vienlaicīgie pārbaudes, logrīku un modinātāju signāli izmanto vienu toni. Apturot pašreizējais tonis drīkst beigties; garais var turpināties vēl pussekundi. Ņem vērā nobīdes simtdaļas; pārklājušies toņi skan nepārtraukti līdz pēdējā pārklājuma beigām.

## Papildu pulksteņi

Kalendārs ar pulksteni cilnē Vispārīgi var rādīt līdz diviem papildu pulksteņiem ar saviem nosaukumiem un laika joslām. Tad katrs rāda arī vietējo nedēļas dienu. Lielumu izvēlas atsevišķi cilnē Izskats vai ciparnīcas kontekstizvēlnē. Papildu pulksteņiem nav sekunžu rādītāja. Pievienošana, noņemšana un lieluma maiņa saglabā piesaisti darba apgabala malām.

Tikai dubultklikšķis tieši uz galvenās ciparnīcas pārslēdz tās sekunžu rādītāju. Papildu pulksteņu izvēlnēs ir tikai lielumi. Tie izmanto logrīka valodu, laika formātu, fontus un nobīdi; digitālajā laikā nav sekunžu.

## Laika formāts un laika joslas

Laika formāts cilnē Vispārīgi piedāvā Atbilstoši valodai (noklusējums), 12 stundas un 24 stundas. Manuālā izvēle paliek pēc valodas maiņas. Atdalītāji un laika apzīmējumi atbilst logrīka valodai. AM/PM sākumā ieslēgts un ietekmē tikai apzīmējumu 12 stundu režīmā; ja valodai nav savu apzīmējumu, lieto AM/PM. Ekrāna pulksteņi to rāda atsevišķā rindā zem laika. UTC vienmēr izmanto 24 stundu formātu. Nosauktās joslas ievēro vietējo un vasaras laiku; nobīde atbilst pašreizējam datumam. Atsevišķās UTC izvēles ir nemainīgas nobīdes no −12:00 līdz +14:00 ar 15 minūšu soli bez vasaras laika.

## Laika avots un NTP žurnāls

Cilne Laiks izvēlas Windows sistēmas laiku vai NTP serverus visai programmai. NTP maina tikai CalClock laiku; Windows pulkstenis netiek mainīts. Līdz pirmajai derīgajai atbildei izmanto sistēmas laiku. NTP ir noklusējums. Automātiskā kopa pēc sistēmas reģiona izvēlas Čehijas un Slovākijas serverus, PTB Eiropai vai pasaules kopu. Mērījumus filtrē pēc tīkla aizkaves un novirzēm no citām atbildēm. Sinhronizēt tūlīt nekavējoties sāk jaunu mērījumu.

Pēc sinhronizācijas CalClock pulkstenis darbojas neatkarīgi no turpmākām Windows sistēmas laika izmaiņām. Zūdot savienojumam vai mainot serverus, tas turpina no pēdējās derīgās sinhronizācijas līdz jaunai atbildei; stāvoklis paliek līdz programmas aizvēršanai.

Laiks reģistrē NTP vaicājumus kopš palaišanas. Ierakstā ir datums, datora vietējais laiks, serveris un statuss. OK nozīmē derīgu atbildi, θ – tās nobīdi no Windows laika. ERR sniedz iemeslu un iespējamo kļūdas kodu. Grupas pēdējais ieraksts rāda arī apvienoto nobīdi Θ, ja ir derīgi mērījumi. Nobīdes ir milisekundēs ar četrām zīmēm aiz komata: pozitīva vērtība nozīmē, ka serveris ir priekšā, negatīva – atpaliek. Θ balstās uz pieņemtajiem mērījumiem un redzama arī sinhronizācijas statusā. Saglabāt žurnālu eksportē CSV ar nobīdēm un kļūdu informāciju. Ieraksti starp palaišanām nepaliek; saglabājiet pirms iziešanas, ja vajadzīgs.

## Ekrāna pulkstenis

Digitālais pulkstenis var aizpildīt vienu vai vairākus monitorus un aptumšot pārējos. Fonta lielums ir procenti no monitora augstuma; izvēlami fonts, nogludināšana, krāsas un iekšējā atkāpe. UTC var būt atsevišķā rindā. Noklusējums ir balts teksts uz melna fona. Kamēr atvērti iestatījumi, redzams mazs pārvietojams priekšskatījums ar monitora malu attiecību un saglabājamu novietojumu. Režģis šo tipu nepārvieto. Esc paslēpj pulksteni un noņem aptumšojumu arī tad, ja iestatījumi ir atvērti.

Peles rādītājs virs ekrāna pulksteņa un aptumšotajiem monitoriem pēc īsas neaktivitātes pazūd un atgriežas, pakustinot peli. Virs mazā priekšskatījuma tas paliek redzams.

## Būvēšana un pakošana

Nepieciešams Microsoft Visual Studio ar MSVC v145 rīkkopu un Windows SDK. Atveriet `CalClock.slnx`, atlasiet `Release | x86` un būvējiet risinājumu. Izpildāmais fails tiek izveidots `Release\CalClock.exe`. Atbalstīta tikai Win32/x86 konfigurācija, jo integrācijai ar Windows pulksteņa vadīklu nepieciešama x86 saderība.

Pēc būvēšanas `.\PackageRelease.ps1` izveido `CalClock-<version>-win32.zip`; versiju nolasa no `Release\CalClock.exe`. Arhīva saknē ir `CalClock.exe` un `license.txt`. Neobligātie parakstīšanas parametri `-SignerName`, `-SignToolPath` un `-TimestampServer` tiek norādīti palaižot. Esošs derīgs Authenticode paraksts tiek pārbaudīts un netiek aizstāts. Iepriekšējie CalClock ZIP arhīvi tiek noņemti katras palaišanas sākumā; parakstīšanas vai pārbaudes kļūda aptur pakošanu.

## Licence

CalClock ir pieejams saskaņā ar [MIT licenci](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
