# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · **Hrvatski** · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock je izvorna aplikacija Win32/x86 za Windows Vista i noviji, s neovisno prilagodljivim plutajućim satovima i kalendarima. Radi u području obavijesti. Podržava do 32 widgeta i 36 jezičnih varijanti; jezik programa i svakog widgeta bira se zasebno.

## Upravljanje

Povucite sat ili ploču lijevom tipkom miša. Samostalni kalendar povlači se za slobodno područje. Desnom tipkom kliknite widget ili ikonu u području obavijesti za otvaranje izbornika. Lijevi klik na ikonu skriva vidljive widgete; ako su svi skriveni, vraća samo posljednje skrivene widgete.

## Widgeti i postavke

U Postavkama možete dodavati, uklanjati i duplicirati analogne i digitalne satove, kalendare, ploče kalendara sa satom i satove na zaslonu. Svaki widget ima vlastitu vidljivost, način Uvijek na vrhu, jezik, vremensku zonu i vremenski pomak. Pomak unesite kao [-]HH:mm:ss.ff. Veličina analognih satova i satova na ploči može se odabrati. Digitalni satovi podržavaju sekunde, početnu nulu, font, boje, neprozirnost i prozirnu pozadinu. Kalendar podržava brojeve tjedana i nedjelju kao prvi dan te koristi jezik widgeta.

## Alarm

Satovi i ploče mogu imati alarm. Program sam reproducira zvučnu datoteku jednom ili neprekidno, ovisno o postavci ponavljanja. Ostale datoteke i naredbe predaju se Windowsu. Kliknite brojčanik ili zaslon aktivnog alarma, odaberite Zaustavi alarm ili pritisnite Esc za zaustavljanje signalizacije i zvuka koji reproducira program.

## Prečaci i spremanje

Dvostruki klik na brojčanik ili digitalni zaslon uključuje ili isključuje sekunde. F1 otvara pomoć, B otvara Postavke, a Esc skriva widget ako ne zaustavlja alarm. Položaji widgeta spremaju se nakon povlačenja, položaji dijaloških prozora pri zatvaranju, a postavke u odabrano spremište. Ponovno pokretanje aktivira već pokrenutu instancu i zadržava widgete na najbližem dostupnom mjestu radnog područja.

## Unos vremena i radnje alarma

Vrijeme alarma prihvaća HH:mm s dvotočkom, točkom, razmakom ili drugim razdjelnikom; razdjelnik se može izostaviti. Jedna ili dvije znamenke označavaju sate, a tri ili četiri sate i minute, primjerice 7, 12, 730, 0730 ili 7:30. Nakon napuštanja polja vrijednost se pretvara u HH:mm. Pomak se čita zdesna, počevši od sekundi: 2 znači 00:00:02.00, 230 i 0230 znače 00:02:30.00, a 12345 znači 01:23:45.00. Uz razdjelnike dvije skupine znače minute i sekunde, tri sate, minute i sekunde, a četvrta sadrži stotinke; dopušten je predznak. Dani ispod opcije Alarm uključen određuju dane u tjednu kada se alarm pokreće; zadano su odabrani svi dani. Redoslijed prati jezik programa, a promjena jezika ne mijenja spremljene dane. Aktivirani alarm prikazuje skriveni widget i dovodi ga ispred drugih prozora bez trajne promjene postavke Uvijek na vrhu. Reproduciraj vremenski signal pokreće prvi kratki ton pet sekundi prije vremena alarma. Ta je opcija neovisna o kartici Signal, ali istodobni se nizovi spajaju. Testiraj uključuje treperenje odabranog brojčanika ili okvira ploče i provjerava datoteku, naredbu, zvuk, HTTP/HTTPS adresu udaljene skripte te, ako je odabrano, cijeli niz vremenskog signala. Zaustavljanje testa prekida njegov unutarnji zvuk i probni signal; zaustavljanje alarma prekida njegov unutarnji zvuk. Isključivanje zvuka ne zaustavlja reprodukciju: ona se nastavlja nečujno i ponovno se čuje nakon uključivanja zvuka. Naredbe i udaljene skripte ostaju aktivne.

Klizač Glasnoća zvuka na kartici Alarm podešava glasnoću zvučnih datoteka koje program reproducira za taj widget. Zadanih −18 dB čuva izvornu razinu datoteke (100%). Pomicanje udesno pojačava zvuk; najvećih 0 dB odgovara približno 794%. Položaj −∞ dB znači tišinu. Promjene se čuju i tijekom testa. MIDI i datoteke koje se ne mogu dekodirati pa se reproduciraju zamjenskim načinom ograničene su na 100%.

## Odabir, tipke i kopiranje datuma

Postavke pamte posljednju otvorenu karticu, a Dodaj posljednju dodanu vrstu. Ukloni ili Del uklanja sve odabrane stavke nakon primjene promjena. Dvostruki klik na stavku prikazuje skriveni widget, označava Vidljivo i nakratko ističe widget. Postavke u izborniku widgeta odabiru taj widget na popisu. Klik na dan u kalendaru odabire datum i kopira ga u međuspremnik; svaki kalendar ima vlastiti oblik u Postavkama i izborniku. Dostupna su sva 33 oblika, neovisno o jeziku; tekstualni nazivi koriste jezik widgeta. Zadani Kratki datum prati jezik widgeta. Insert mijenja odabir trenutačne stavke i pomiče pokazivač popisa jedan redak niže. Ctrl+C kopira odabrane widgete. Ctrl+V dodaje kopije redoslijedom popisa, s nastavkom naziva na jeziku programa. Dopuštena su najviše 32 widgeta. Pri dupliciranju ili lijepljenju kopije se dodaju redom do dosezanja ograničenja, a za preostale se prikazuje obavijest. Alt+0, Alt+1, Alt+2 ili Alt+3 na analognom satu ili kalendaru sa satom odabire veličinu glavnog brojčanika od najmanje do najveće.

Otvaranje postavki preko ikone u području obavijesti ponovno odabire posljednji odabrani widget.

## Raspored widgeta

Rasporedi u mrežu čuva približan ručni raspored, priljubljuje središta widgeta uz najbliže točke mreže i uklanja preklapanja. Izbornik widgeta djeluje na njegov zaslon, a ikona u području obavijesti na svaki zaslon zasebno. Ponavljanje naredbe čuva raspored. Dvostruki klik u Postavkama označava widget brzim svijetloplavim treperenjem; alarm treperi sporije i crveno. Isključivanje opcije Uvijek na vrhu šalje widget iza ostalih prozora. Na ploči kalendara sa satom gornja poveznica vraća kalendar na današnji datum, a donja otvara klasične postavke datuma i vremena Windowsa. Ako je priljubljivanje uključeno, widget se tijekom povlačenja priljubljuje uz rub radnog područja na udaljenosti do pet piksela. Promjena veličine čuva vezu s istim rubom ili parom rubova.

Za samostalni kalendar prikažite ili sakrijte Redak Danas na kartici Izgled ili u izborniku widgeta. Idi na današnji datum odabire danas i vraća mjesečni prikaz. Kada se datum promijeni prema vremenu widgeta, današnji se datum odabire automatski uz očuvanje trenutačnog prikaza kalendara.

## Izgled i spremanje postavki

Promjene izgleda odmah se prikazuju u pretpregledu. Odustani odbacuje neprimijenjene promjene, a Zadani izgled vraća zadane vrijednosti za tu vrstu widgeta. Digitalni satovi nude font, izglađivanje, boje, neprozirnost, unutarnji razmak, širinu obruba i prozirnu pozadinu. Digitalni satovi, kalendari i ploče dijele četiri stila obruba; boja jednostrukog obruba može se odabrati. Ploča ima odvojene fontove gornjeg retka, vremena i donjeg retka, početnu nulu i odabir veličine brojčanika. Prilagođeni fontovi kalendara podržani su uz klasični izgled Windowsa ili kada su teme isključene za program ili widget. Postavke se mogu izvesti u XML. Uvoz XML-a odmah učitava i sprema postavke u odabrano spremište bez promjene njegove vrste. Automatska XML datoteka je %AppData%\FortSoft\CalClock\settings.xml. Nakon zapisivanja XML-a uklanja se ključ HKCU\SOFTWARE\FortSoft\CalClock; spremanje u registar uklanja automatsku XML datoteku.

Izglađivanje fonta nudi ClearType, GDI i Nema. Početna nula nudi Prikaži (zadano), Zadrži razmak i Bez razmaka. Zadrži razmak skriva nulu, ali rezervira njezinu širinu u odabranom fontu, pa ostale znamenke zadržavaju položaj i kod proporcionalnih fontova. Satovi na zaslonu ostaju centrirani, uključujući rezervirani razmak. Redak UTC ima vlastito centriranje.

## Postavke i izbornici

Jezik programa, font, izglađivanje, teme, spremište, pokretanje s Windowsom i priljubljivanje uz rubove vrijede globalno i postavljaju se na kartici Program. Pri prvom pokretanju jezik se bira prema jeziku sučelja Windowsa; ako nije podržan, koristi se američki engleski. Jezik, izglađivanje i teme widgeta utječu samo na taj widget.

Izbornik widgeta sadrži primjenjive postavke vidljivosti, načina Uvijek na vrhu, sekundi, veličine i oblika kopiranja datuma, a zatim Rasporedi u mrežu, Postavke, Pomoć, O programu i Izlaz. Izbornik ikone u području obavijesti navodi numerirane widgete i naredbe Prikaži sve, Sakrij sve i Isključi sav zvuk. Slijedi zasebno grupirana naredba Rasporedi u mrežu. Prikazivanje ili vraćanje widgeta dovodi ga naprijed bez promjene postavke Uvijek na vrhu. Ponovno pokretanje CalClocka aktivira postojeću instancu i po potrebi vraća posljednje skrivene widgete. Dostupne veličine brojčanika i podrška sekundnoj kazaljci ovise o verziji Windowsa. Alarm i Signal mogu se uključiti u izborniku widgeta; Alarm pokazuje vrijeme i, ako nisu odabrani svi dani, aktivne dane u tjednu. Označeni Isključi zvuk odgovara opciji Zvuk isključen na kartici Općenito. Isključi sav zvuk isključuje zvuk svih widgeta, a ponovnim izvođenjem vraća zvuk samo onima koje je prethodno utišao. M na bilo kojem widgetu radi isto. Uključivanje alarma bez odabranih dana otvara njegovu karticu Alarm.

## Zvučni vremenski signal

Signal slijedi obrazac Greenwich Time Signal (GTS). Kartica Signal sadrži opciju Vremenski signal uključen i odabir intervala od 1, 5, 10, 15, 20, 30 ili 60 minuta prema prikazanom vremenu widgeta. Signal je u početku isključen, a odabran je interval od jednog sata. Isključivanje i uključivanje u izborniku čuva interval. Izbornik prikazuje vrijeme alarma i interval signala u zagradama. Granica prati vrijeme widgeta, uključujući UTC, vremensku zonu, pomak i NTP sinkronizaciju. Pet kratkih tonova označava posljednjih pet sekundi, a dugi ton točnu granicu. Istodobni signali više widgeta spajaju se u jedan niz. Nakon isključivanja zvuka trenutačni ton može završiti; sljedeći se preskaču, a nakon uključivanja zvuka čuje se tek sljedeći planirani ton. Samostalni Kalendar nema alarm, vremenski signal ni isključivanje zvuka.

Pri intervalu od 20 minuta signal se čuje na :00, :20 i :40 prema vremenu widgeta.

Na kartici Program opcija Zvuk vremenskog signala nudi Ugrađeni generator i Zvuk sustava. Izbor vrijedi za sve widgete, uključujući signale alarma. Zadani je Ugrađeni generator.

Klizač Glasnoća vremenskog signala na kartici Program prikazuje razinu generatora u dB. Krajnji desni položaj je 0 dB, najveća neizobličena amplituda sinusoide; tišina je −∞ dB. Zadana je glasnoća −18 dB. Testiraj uz izbor zvuka pokreće neprekidni pretpregled, a Zaustavi test ga završava. Oba se zvuka mogu testirati; test se ne sprema. Držanje klizača glasnoće također pokreće pretpregled do otpuštanja miša, osim ako traje test pokrenut gumbom. Reprodukcija počinje na sljedećoj punoj sekundi: kratki ton svake sekunde i dugi na :00, :05, :10 i tako dalje. Istodobni probni signali i signali widgeta ili alarma dijele jedan ton. Zaustavljanje testa dopušta završetak trenutačnog tona; dugi ton može trajati još do pola sekunde. Pomaci widgeta poštuju se i u stotinkama sekunde. Tonovi widgeta, alarma i testova koji se preklapaju zvuče kao jedan neprekidan ton do kraja posljednjeg preklapanja.

## Dodatni satovi

Na kartici Općenito kalendar sa satom može prikazivati do dva dodatna sata s vlastitim nazivima i vremenskim zonama. Tada svaki sat prikazuje i lokalni dan u tjednu. Veličina svakog brojčanika bira se zasebno na kartici Izgled ili u njegovu kontekstnom izborniku. Dodatni satovi nemaju sekundnu kazaljku. Dodavanje, uklanjanje ili promjena veličine čuva priljubljivanje widgeta uz rubove radnog područja.

Samo dvostruki klik izravno na glavni brojčanik mijenja prikaz njegove sekundne kazaljke. Izbornici dodatnih satova sadrže samo veličine. Dodatni satovi dijele jezik, oblik vremena, fontove i pomak widgeta; njihov digitalni prikaz nema sekunde.

## Oblik vremena i vremenske zone

Oblik vremena na kartici Općenito nudi Prema jeziku (zadano), 12 sati i 24 sata. Prema jeziku slijedi odabranu kulturu; ručni se izbor čuva nakon promjene jezika widgeta. Razdjelnici i oznake vremena prate jezik widgeta. AM/PM je zadano označen i upravlja samo oznakom u 12-satnom prikazu; ako kultura nema vlastite oznake, koristi se AM/PM. Satovi na zaslonu prikazuju oznaku u zasebnom retku ispod vremena. UTC uvijek koristi 24-satni oblik. Imenovane vremenske zone prate lokalno vrijeme i ljetno računanje vremena; pomak uz naziv odgovara trenutačnom datumu. Zasebne stavke UTC predstavljaju stalne pomake od -12:00 do +14:00 u koracima od 15 minuta, bez ljetnog računanja vremena.

## Izvor vremena

Kartica Vrijeme bira sustavsko vrijeme Windowsa ili zadane NTP poslužitelje za cijeli program i sve widgete. NTP mijenja samo vrijeme prikazano u CalClocku; sat Windowsa nikad se ne mijenja. Do prvog valjanog odgovora koristi se sustavsko vrijeme. NTP je zadani izbor. Automatski skup prema regiji sustava bira češke i slovačke poslužitelje, PTB za Europu ili globalni skup. Mjerenja se filtriraju prema mrežnom kašnjenju i odstupanjima od ostalih odgovora. Sinkroniziraj sada odmah pokreće novo mjerenje.

Nakon sinkronizacije sat CalClocka nastavlja raditi neovisno o naknadnim promjenama sustavskog vremena Windowsa. Pri prekidu veze ili promjeni poslužitelja nastavlja od posljednje valjane sinkronizacije do novog odgovora; stanje se čuva do zatvaranja programa.

## Zapisnik NTP sinkronizacije

Kartica Vrijeme bilježi upite NTP poslužiteljima od pokretanja programa. Svaki zapis sadrži datum i lokalno vrijeme računala, poslužitelj i stanje. OK označava valjan odgovor; θ prikazuje odstupanje od sustavskog vremena Windowsa. ERR navodi uzrok i eventualnu šifru pogreške. Posljednji zapis skupine upita prikazuje i objedinjeno odstupanje Θ ako postoje upotrebljiva mjerenja.

Odstupanja su u milisekundama s četiri decimalna mjesta. Pozitivna vrijednost znači da je sat poslužitelja ispred Windowsa, a negativna da kasni. Objedinjeno Θ temelji se na prihvaćenim mjerenjima i prikazuje se i u stanju sinkronizacije.

Spremi zapisnik izvozi zapise u CSV, uključujući odstupanja i pojedinosti pogrešaka. Zapisi se ne čuvaju između pokretanja; spremite ih prije izlaska ako ih želite zadržati.

## Sat na zaslonu

Digitalni sat može ispuniti jedan ili više zaslona i po potrebi zatamniti ostale. Veličina fonta zadaje se kao postotak visine zaslona; mogu se podesiti i font, izglađivanje, boje i unutarnji razmak. U načinu UTC oznaka UTC može biti u zasebnom retku. Zadani je izgled bijeli tekst na crnoj pozadini. Dok su Postavke otvorene, sat je mali pomični pretpregled koji čuva omjer stranica zaslona; njegov se položaj sprema. Raspoređivanje u mrežu izostavlja tu vrstu widgeta. Esc skriva sat i uklanja zatamnjenje i kada su Postavke otvorene.

Pokazivač miša skriva se nakon kratke neaktivnosti iznad sata na zaslonu i zatamnjenih zaslona te se ponovno prikazuje nakon pomicanja miša. Iznad malog pretpregleda u Postavkama ostaje vidljiv.

## Izgradnja i pakiranje

Potrebni su Microsoft Visual Studio s alatima MSVC v145 i Windows SDK. Otvorite `CalClock.slnx`, odaberite `Release | x86` i izgradite rješenje. Izvršna datoteka nastaje u `Release\CalClock.exe`. Podržana je samo konfiguracija Win32/x86 jer integracija s kontrolom sata Windowsa zahtijeva kompatibilnost s x86.

Nakon izgradnje pokrenite `.\PackageRelease.ps1` za stvaranje arhive `CalClock-<version>-win32.zip`. Verzija se čita iz `Release\CalClock.exe`. Arhiva sadrži `CalClock.exe` i `license.txt` izravno u korijenu. Neobavezni parametri potpisivanja su `-SignerName`, `-SignToolPath` i `-TimestampServer`; zadaju se pri pokretanju. Postojeći valjani potpis Authenticode provjerava se i ne zamjenjuje. Prethodne ZIP arhive CalClocka uklanjaju se na početku svakog pokretanja. Pogreška potpisivanja ili provjere zaustavlja pakiranje.

## Licencija

CalClock je dostupan pod [licencijom MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
