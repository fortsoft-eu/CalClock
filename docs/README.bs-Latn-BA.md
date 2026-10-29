# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · **Bosanski** · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock je izvorna aplikacija Win32/x86 za Windows Vista i noviji, s nezavisno podesivim plutajućim satovima i kalendarima. Radi u području obavijesti. Podržava do 32 vidžeta i 36 jezičkih varijanti; jezik programa i svakog vidžeta bira se zasebno.

Analogni satovi koriste sistemsku kontrolu Windowsa `ClockWndMain`, uz automatsko otkrivanje dostupnih
veličina i podrške za sekundaru. Ako odabrana veličina ne podržava sekundaru, naredba Sekunde je onemogućena,
ali se sačuvani izbor zadržava za drugu podržanu veličinu.

## Upravljanje

Povucite sat ili ploču lijevom tipkom miša. Samostalni kalendar povlači se za slobodno područje. Desnom tipkom kliknite vidžet ili ikonu u području obavijesti za otvaranje menija. Lijevi klik na ikonu skriva vidljive vidžete; ako su svi skriveni, vraća samo posljednje skrivene vidžete.

## Vidžeti i postavke

U Postavkama možete dodavati, uklanjati i duplicirati analogne i digitalne satove, kalendare, ploče kalendara sa satom i satove na ekranu. Svaki vidžet ima vlastitu vidljivost, način Uvijek na vrhu, jezik, vremensku zonu i vremenski pomak. Pomak unesite kao [-]HH:mm:ss.ff. Veličina analognih satova i satova na ploči može se odabrati. Digitalni satovi podržavaju sekunde, početnu nulu, font, boje, neprozirnost i prozirnu pozadinu. Kalendar podržava brojeve sedmica i nedjelju kao prvi dan te koristi jezik vidžeta.

## Alarm

Satovi i ploče mogu imati alarm. Program sam reproducira zvučnu datoteku jednom ili neprekidno, zavisno o postavci ponavljanja. Ostale datoteke i naredbe predaju se Windowsu. Kliknite brojčanik ili ekran aktivnog alarma, odaberite Zaustavi alarm ili pritisnite Esc za zaustavljanje signalizacije i zvuka koji reproducira program.

## Prečaci i čuvanje

Dvostruki klik na brojčanik ili digitalni ekran uključuje ili isključuje sekunde. F1 otvara pomoć, B otvara Postavke, a Esc skriva vidžet ako ne zaustavlja alarm. Položaji vidžeta čuvaju se nakon povlačenja, položaji dijaloških prozora pri zatvaranju, a postavke u odabrano spremište. Ponovno pokretanje aktivira već pokrenutu instancu i zadržava vidžete na najbližem dostupnom mjestu radnog područja.

## Unos vremena i radnje alarma

Vrijeme alarma prihvata HH:mm s dvotačkom, tačkom, razmakom ili drugim razdjelnikom; razdjelnik se može izostaviti. Jedna ili dvije znamenke označavaju sate, a tri ili četiri sate i minute, primjerice 7, 12, 730, 0730 ili 7:30. Nakon napuštanja polja vrijednost se pretvara u HH:mm. Pomak se čita zdesna, počevši od sekundi: 2 znači 00:00:02.00, 230 i 0230 znače 00:02:30.00, a 12345 znači 01:23:45.00. Uz razdjelnike dvije skupine znače minute i sekunde, tri sate, minute i sekunde, a četvrta sadrži stotinke; dopušten je predznak. Dani ispod opcije Alarm uključen određuju dane u sedmici kada se alarm pokreće; podrazumijevano su odabrani svi dani. Redoslijed prati jezik programa, a promjena jezika ne mijenja sačuvane dane. Aktivirani alarm prikazuje skriveni vidžet i dovodi ga ispred drugih prozora bez trajne promjene postavke Uvijek na vrhu. Reproduciraj vremenski signal pokreće prvi kratki ton pet sekundi prije vremena alarma. Ta je opcija nezavisna o kartici Signal, ali istovremeni se nizovi spajaju. Testiraj uključuje treperenje odabranog brojčanika ili okvira ploče i provjerava datoteku, naredbu, zvuk, HTTP/HTTPS adresu udaljene skripte te, ako je odabrano, cijeli niz vremenskog signala. Zaustavljanje testa prekida njegov unutrašnji zvuk i probni signal; zaustavljanje alarma prekida njegov unutrašnji zvuk. Isključivanje zvuka ne zaustavlja reprodukciju: ona se nastavlja nečujno i ponovno se čuje nakon uključivanja zvuka. Naredbe i udaljene skripte ostaju aktivne.

Zvučni signali alarma planiraju se prema stvarnom trenutku sljedećeg alarma nakon pretvaranja vremenske zone i primjene pomaka vidžeta. Počinju pet stvarnih sekundi prije tog trenutka, čak i kada prikazani sat skoči direktno na vrijeme alarma. Vrijeme alarma preskočeno u proljeće ne pokreće ni alarm ni njegove signale. Tokom sata ponovljenog u jesen alarm i njegovi signali oglašavaju se samo jednom za isti datum i podešeno vrijeme.

Klizač Glasnoća zvuka na kartici Alarm podešava glasnoću zvučnih datoteka koje program reproducira za taj vidžet. Podrazumijevanih −18 dB čuva izvornu razinu datoteke (100%). Pomicanje udesno pojačava zvuk; najvećih 0 dB odgovara približno 794%. Položaj −∞ dB znači tišinu. Promjene se čuju i tokom testa. MIDI i datoteke koje se ne mogu dekodirati pa se reproduciraju zamjenskim načinom ograničene su na 100%.

## Odabir, tipke i kopiranje datuma

Postavke pamte posljednju otvorenu karticu, a Dodaj posljednju dodanu vrstu. Ukloni ili Del uklanja sve odabrane stavke nakon primjene promjena. Dvostruki klik na stavku prikazuje skriveni vidžet, označava Vidljivo i nakratko ističe vidžet. Postavke u meniju vidžeta odabiru taj vidžet na popisu. Klik na dan u kalendaru odabire datum i kopira ga u međuspremnik; svaki kalendar ima vlastiti oblik u Postavkama i meniju. Dostupna su sva 33 oblika, nezavisno o jeziku; tekstualni nazivi koriste jezik vidžeta. Podrazumijevani Kratki datum prati jezik vidžeta. Insert mijenja odabir trenutne stavke i pomiče pokazivač popisa jedan red niže. Ctrl+C kopira odabrane vidžete. Ctrl+V dodaje kopije redoslijedom popisa, s nastavkom naziva na jeziku programa. Dopuštena su najviše 32 vidžeta. Pri dupliciranju ili lijepljenju kopije se dodaju redom do dosezanja ograničenja, a za preostale se prikazuje obavijest. Alt+0, Alt+1, Alt+2 ili Alt+3 na analognom satu ili kalendaru sa satom odabire veličinu glavnog brojčanika od najmanje do najveće.

Otvaranje postavki preko ikone u području obavijesti ponovo bira posljednji odabrani vidžet.

## Raspored vidžeta

Rasporedi u mrežu čuva približan ručni raspored, priljubljuje središta vidžeta uz najbliže tačke mreže i uklanja preklapanja. Meni vidžeta djeluje na njegov ekran, a ikona u području obavijesti na svaki ekran zasebno. Ponavljanje naredbe čuva raspored. Dvostruki klik u Postavkama označava vidžet brzim svijetloplavim treperenjem; alarm treperi sporije i crveno. Isključivanje opcije Uvijek na vrhu šalje vidžet iza ostalih prozora. Na ploči kalendara sa satom gornja poveznica vraća kalendar na današnji datum, a donja otvara klasične postavke datuma i vremena Windowsa. Ako je priljubljivanje uključeno, vidžet se tokom povlačenja priljubljuje uz ivicu radnog područja na udaljenosti do pet piksela. Promjena veličine čuva vezu s istom ivicom ili parom ivica.

Ploče kalendara sa satom mogu iznad donje veze prikazivati obavještenja Windowsa o datumu i vremenu. Opcija **Obavještenja o datumu i vremenu** na kartici **Općenito** uključena je prema zadanim postavkama i čuva se zasebno za svaku ploču. Ako je primjenjivo više obavještenja, prikazuju se jedno ispod drugog kao u Windowsu. Kada je opcija isključena ili nema primjenjivih obavještenja, ploča zadržava izvornu veličinu i raspored, bez rezervisanja praznog prostora.

Za samostalni kalendar prikažite ili sakrijte Red Danas na kartici Izgled ili u meniju vidžeta. Idi na današnji datum odabire danas i vraća mjesečni prikaz. Kada se datum promijeni prema vremenu vidžeta, današnji se datum odabire automatski uz očuvanje trenutnog prikaza kalendara.

## Izgled i čuvanje postavki

Promjene izgleda odmah se prikazuju u pregledu odabranog vidžeta. `Podrazumijevani izgled` vraća podrazumijevane vrijednosti za tu vrstu vidžeta. Pri zatvaranju postavki s neprimijenjenim promjenama pojavljuje se upit o njihovom čuvanju. Upozorenje je uključeno prema zadanim postavkama i može se isključiti na kartici Program. Digitalni satovi nude font, izglađivanje, boje, neprozirnost, unutrašnji razmak, širinu obruba i prozirnu pozadinu. Digitalni satovi, kalendari i ploče dijele četiri stila obruba; boja jednostrukog obruba može se odabrati. Ploča ima odvojene fontove gornjeg reda, vremena i donjeg reda, početnu nulu i odabir veličine brojčanika. Prilagođeni fontovi kalendara podržani su uz klasični izgled Windowsa ili kada su teme isključene za program ili vidžet. Postavke se mogu izvesti u XML. Uvoz XML-a odmah učitava i čuva postavke u odabrano spremište bez promjene njegove vrste. Automatska XML datoteka je %AppData%\FortSoft\CalClock\settings.xml. Nakon zapisivanja XML-a uklanja se ključ HKCU\SOFTWARE\FortSoft\CalClock; čuvanje u registar uklanja automatsku XML datoteku.

Izglađivanje fonta nudi ClearType, GDI i Nema. Početna nula nudi „Da“ (podrazumijevano), „Ne, zadrži razmak“ i „Ne, bez razmaka“. „Ne, zadrži razmak“ skriva nulu, ali rezervira njezinu širinu u odabranom fontu, pa ostale znamenke zadržavaju položaj i kod proporcionalnih fontova. Satovi na ekranu ostaju centrirani, uključujući rezervirani razmak. Red UTC ima vlastito centriranje.

## Postavke i meniji

Jezik programa, font, izglađivanje, teme, spremište, pokretanje s Windowsom i priljubljivanje uz ivice vrijede globalno i postavljaju se na kartici Program. Pri prvom pokretanju jezik se bira prema jeziku interfejsa Windowsa; ako nije podržan, koristi se američki engleski. Jezik, izglađivanje i teme vidžeta utječu samo na taj vidžet.

Meni vidžeta sadrži primjenjive postavke vidljivosti, načina Uvijek na vrhu, sekundi, veličine i oblika kopiranja datuma, a zatim Rasporedi u mrežu, Postavke, Pomoć, O programu i Izlaz. Meni ikone u području obavijesti navodi numerisane vidžete i naredbe Prikaži sve, Sakrij sve i Isključi sav zvuk. Slijedi zasebno grupirana naredba Rasporedi u mrežu. Prikazivanje ili vraćanje vidžeta dovodi ga naprijed bez promjene postavke Uvijek na vrhu. Ponovno pokretanje CalClocka aktivira postojeću instancu i po potrebi vraća posljednje skrivene vidžete. Dostupne veličine brojčanika i podrška sekundnoj kazaljci zavise od verzije Windowsa. Alarm i Signal mogu se uključiti u meniju vidžeta; Alarm pokazuje vrijeme i, ako nisu odabrani svi dani, aktivne dane u sedmici. Označeni Isključi zvuk odgovara opciji Zvuk isključen na kartici Općenito. Isključi sav zvuk isključuje zvuk svih vidžeta, a ponovnim izvođenjem vraća zvuk samo onima koje je prethodno utišao. M na bilo kojem vidžetu radi isto. Uključivanje alarma bez odabranih dana otvara njegovu karticu Alarm.

## Zvučni vremenski signal

Signal slijedi obrazac Greenwich Time Signal (GTS). Kartica Signal sadrži opciju Vremenski signal uključen i odabir intervala od 1, 5, 10, 15, 20, 30 ili 60 minuta prema prikazanom vremenu vidžeta. Signal je u početku isključen, a odabran je interval od jednog sata. Isključivanje i uključivanje u meniju čuva interval. Meni prikazuje vrijeme alarma i interval signala u zagradama. Granica prati vrijeme vidžeta, uključujući UTC, vremensku zonu, pomak i NTP sinhronizaciju. Pet kratkih tonova označava posljednjih pet sekundi, a dugi ton tačnu granicu. Nakon isključivanja zvuka trenutni ton može završiti; sljedeći se preskaču, a nakon uključivanja zvuka čuje se tek sljedeći planirani ton. Samostalni Kalendar nema alarm, vremenski signal ni isključivanje zvuka.

Pri intervalu od 20 minuta signal se čuje na :00, :20 i :40 prema vremenu vidžeta.

Na kartici Program opcija Zvuk vremenskog signala nudi Ugrađeni generator i Zvuk sistema. Izbor vrijedi za sve vidžete, uključujući signale alarma. Podrazumijevani je Ugrađeni generator.

Klizač Glasnoća vremenskog signala na kartici Program prikazuje razinu generatora u dB. Krajnji desni položaj je 0 dB, najveća neizobličena amplituda sinusoide; tišina je −∞ dB. Podrazumijevana je glasnoća −18 dB. Testiraj uz izbor zvuka pokreće neprekidni pregled, a Zaustavi test ga završava. Oba se zvuka mogu testirati; test se ne čuva. Držanje klizača glasnoće također pokreće pregled do otpuštanja miša, osim ako traje test pokrenut dugmetom. Reprodukcija počinje na sljedećoj punoj sekundi: kratki ton svake sekunde i dugi na :00, :05, :10 i tako dalje. Zaustavljanje testa dopušta završetak trenutnog tona; dugi ton može trajati još do pola sekunde. Pomaci vidžeta poštuju se i u stotinkama sekunde. Tonovi vidžeta, alarma i testova koji se preklapaju zvuče kao jedan neprekidan ton do kraja posljednjeg preklapanja na istom audio izlazu.

**Audio izlaz**

**Audio izlaz** na kartici **Signal** bira uređaj za redovne vremenske signale svakog vidžeta koji podržava zvuk.
Vremenska zona, pomak i interval vidžeta ostaju nepromijenjeni. Izbor generatora i glasnoća signala i dalje su
zajednički za cijeli program na kartici **Program**. Uz **Zvuk sistema**, polje ostaje vidljivo, ali je zasivljeno i
onemogućeno, a odabrani uređaj se čuva; **Ugrađeni generator** ga ponovo omogućava. Windows Vista automatski koristi
generator.

**Zadani Windows uređaj** prati trenutni zadani izlaz Windowsa. Izričito odabrani uređaj ostaje odabran nakon
odspajanja i prikazuje se kao **Uređaj nije dostupan**; njegovi signali ostaju nečujni dok ne postane dostupan ili se
odabere drugi izlaz. Popis uređaja osvježava se pri otvaranju. Izbor se čuva zasebno za svaki vidžet u registru ili
XML postavkama.

Signali se automatski spajaju za svaki izlaz. Izričito odabrani uređaj i Zadani Windows uređaj koji upućuje na
isti uređaj dijele jedan izlaz. Različiti uređaji rade nezavisno; sinusni val, kontinuitet faze te početak i
završetak tonova u nuli ostaju očuvani. Zvučni izlaz testa na kartici Aplikacija pamti uređaj za testove
generatora i pregled glasnoće. Sistemski zvučni signal onemogućava samo ovaj izbor. Alarmi i dalje koriste
zadani izlaz Windowsa. S redovnim signalima spajaju se samo na zajedničkom izlazu.

## Dodatni satovi

Na kartici Općenito kalendar sa satom može prikazivati do dva dodatna sata s vlastitim nazivima i vremenskim zonama. Tada svaki sat prikazuje i lokalni dan u sedmici. Veličina svakog brojčanika bira se zasebno na kartici Izgled ili u njegovu kontekstnom meniju. Dodatni satovi nemaju sekundnu kazaljku. Dodavanje, uklanjanje ili promjena veličine čuva priljubljivanje vidžeta uz ivice radnog područja.

Samo dvostruki klik direktno na glavni brojčanik mijenja prikaz njegove sekundne kazaljke. Meniji dodatnih satova sadrže samo veličine. Dodatni satovi dijele jezik, oblik vremena, fontove i pomak vidžeta; njihov digitalni prikaz nema sekunde.

## Oblik vremena i vremenske zone

Oblik vremena na kartici Općenito nudi Prema jeziku (podrazumijevano), 12 sati i 24 sata. Prema jeziku slijedi odabranu kulturu; ručni se izbor čuva nakon promjene jezika vidžeta. Razdjelnici i oznake vremena prate jezik vidžeta. AM/PM je podrazumijevano označen i upravlja samo oznakom u 12-satnom prikazu; ako kultura nema vlastite oznake, koristi se AM/PM. Satovi na ekranu prikazuju oznaku u zasebnom redu ispod vremena. UTC uvijek koristi 24-satni oblik. Imenovane vremenske zone prate lokalno vrijeme i ljetno računanje vremena; pomak uz naziv odgovara trenutnom datumu. Zasebne stavke UTC predstavljaju stalne pomake od -12:00 do +14:00 u koracima od 15 minuta, bez ljetnog računanja vremena.

Novi vidžeti podrazumijevano koriste **Trenutna vremenska zona Windowsa**, koja prati trenutnu vremensku zonu Windowsa i postavku automatskog ljetnog računanja vremena. Postojeći vidžeti zadržavaju odabrane zone. Ova opcija određuje vremensku zonu; zajednički izvor vremena Windows ili NTP ostaje nezavisan.

Vremenski pomak vidžeta primjenjuje se na UTC prije pretvaranja u njegovu vremensku zonu, pa pomjera i trenutak prelaska na ljetno ili standardno vrijeme. Sat pomjeren deset sekundi unaprijed prelazi deset sekundi ranije; sat koji kasni deset sekundi prelazi deset sekundi kasnije. Kazaljke, digitalni prikaz, datumi kalendara, alarmi i vremenski signali koriste tako dobijeno vrijeme.

## Izvor vremena

Kartica Vrijeme bira sistemsko vrijeme Windowsa ili podešene NTP servere za cijeli program i sve vidžete. NTP mijenja samo vrijeme prikazano u CalClocku; sat Windowsa nikad se ne mijenja. Do prvog valjanog odgovora koristi se sistemsko vrijeme. NTP je podrazumijevani izbor. Automatski skup prema regiji sistema bira češke i slovačke servere, PTB za Europu ili globalni skup. Mjerenja se filtriraju prema mrežnom kašnjenju i odstupanjima od ostalih odgovora. Sinhroniziraj sada odmah pokreće novo mjerenje.

Nakon sinhronizacije sat CalClocka nastavlja raditi nezavisno od naknadnih promjena sistemskog vremena Windowsa. Pri prekidu veze ili promjeni servera nastavlja od posljednje valjane sinhronizacije do novog odgovora; stanje se čuva do zatvaranja programa.

## Zapisnik NTP sinhronizacije

Kartica Vrijeme bilježi upite NTP serverima od pokretanja programa. Svaki zapis sadrži datum i lokalno vrijeme računara, server i stanje. OK označava valjan odgovor; θ prikazuje odstupanje od sistemskog vremena Windowsa. ERR navodi uzrok i eventualnu šifru greške. Posljednji zapis skupine upita prikazuje i objedinjeno odstupanje Θ ako postoje upotrebljiva mjerenja.

Odstupanja su u milisekundama s četiri decimalna mjesta. Pozitivna vrijednost znači da je sat servera ispred Windowsa, a negativna da kasni. Objedinjeno Θ temelji se na prihvaćenim mjerenjima i prikazuje se i u stanju sinhronizacije.

Sačuvaj zapisnik izvozi zapise u CSV, uključujući odstupanja i pojedinosti grešaka. Zapisi se ne čuvaju između pokretanja; sačuvajte ih prije izlaska ako ih želite zadržati.

## Sat na ekranu

Digitalni sat može ispuniti jedan ili više ekrana i po potrebi zatamniti ostale. Veličina fonta zadaje se kao postotak visine ekrana; mogu se podesiti i font, izglađivanje, boje i unutrašnji razmak. U načinu UTC oznaka UTC može biti u zasebnom redu. Podrazumijevani je izgled bijeli tekst na crnoj pozadini. Dok su Postavke otvorene, sat je mali pomični pregled koji čuva omjer stranica ekrana; njegov se položaj čuva. Raspoređivanje u mrežu izostavlja tu vrstu vidžeta. Esc skriva sat i uklanja zatamnjenje i kada su Postavke otvorene.

Pokazivač miša skriva se nakon kratke neaktivnosti iznad sata na ekranu i zatamnjenih ekrana te se ponovno prikazuje nakon pomicanja miša. Iznad malog pregleda u Postavkama ostaje vidljiv.

## Izgradnja i pakiranje

Potrebni su Microsoft Visual Studio s alatima MSVC v145 i Windows SDK. Otvorite `CalClock.slnx`, odaberite `Release | x86` i izgradite rješenje. Izvršna datoteka nastaje u `Release\CalClock.exe`. Podržana je samo konfiguracija Win32/x86 jer integracija s kontrolom sata Windowsa zahtijeva kompatibilnost s x86.

Nakon izgradnje pokrenite `.\PackageRelease.ps1` za stvaranje arhive `CalClock-<version>-win32.zip`. Verzija se čita iz `Release\CalClock.exe`. Arhiva sadrži `CalClock.exe` i `license.txt` direktno u korijenu. Neobavezni parametri potpisivanja su `-SignerName`, `-SignToolPath` i `-TimestampServer`; zadaju se pri pokretanju. Postojeći valjani potpis Authenticode provjerava se i ne zamjenjuje. Prethodne ZIP arhive CalClocka uklanjaju se na početku svakog pokretanja. Greška potpisivanja ili provjere zaustavlja pakiranje.

Podrazumijevane vrijednosti parametara potpisivanja čitaju se i iz korisničkih varijabli okruženja Windowsa:
`BUILD_SIGNER_NAME`, `BUILD_CERTIFICATE_THUMBPRINT`, `BUILD_SIGNTOOL_PATH`, `BUILD_TIMESTAMP_SERVER`. Izričito
navedeni argumenti komandne linije imaju prednost.

## Licenca

CalClock je dostupan pod [licencom MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
