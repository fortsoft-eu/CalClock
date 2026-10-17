# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · **Crnogorski** · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock je izvorna aplikacija Win32/x86 za Windows Vista i novije verzije, sa nezavisno podesivim plutajućim satovima i kalendarima. Radi u oblasti za obavještenja. Podržava do 32 vidžeta i 36 jezičkih varijanti; jezik programa i svakog vidžeta bira se zasebno.

## Upravljanje

Povucite sat ili panel lijevim tasterom miša. Samostalni kalendar se pomjera preko slobodne površine. Desni klik na vidžet ili ikonu u oblasti za obavještenja otvara meni. Lijevi klik na ikonu skriva vidljive vidžete; ako su svi skriveni, vraća samo posljednje skrivene.

## Vidžeti i podešavanja

U Podešavanjima možete dodavati, uklanjati i duplirati analogne i digitalne satove, kalendare, panele kalendara sa satom i satove na monitoru. Svaki vidžet ima sopstvenu vidljivost, režim Uvijek na vrhu, jezik, vremensku zonu i pomak u obliku [-]HH:mm:ss.ff. Veličine analognih satova i satova na panelu biraju se posebno. Digitalni satovi podržavaju sekunde, vodeću nulu, font, boje, neprozirnost i providnu pozadinu. Kalendar podržava brojeve nedjelja i nedjelju kao prvi dan i koristi jezik vidžeta.

## Alarm i prečice

Satovi i paneli podržavaju alarm. Program sam pušta zvučnu datoteku jednom ili neprekidno, u zavisnosti od ponavljanja. Ostale datoteke i naredbe predaje Windows-u. Klik na brojčanik ili prikaz aktivnog alarma, Zaustavi alarm ili Esc zaustavljaju indikaciju i zvuk programa. Dvoklik na brojčanik ili digitalni prikaz prebacuje sekunde. F1 otvara pomoć, B Podešavanja, a Esc skriva vidžet ako ne zaustavlja alarm. Položaji vidžeta čuvaju se poslije pomjeranja, položaji dijaloga pri zatvaranju, a podešavanja u izabranom skladištu. Ponovno pokretanje aktivira postojeću instancu i zadržava vidžete na najbližem dostupnom mjestu radne površine.

## Unos vremena i radnje alarma

Vrijeme alarma prihvata HH:mm sa dvotačkom, tačkom, razmakom ili drugim razdvajačem, a može i bez njega. Jedna ili dvije cifre znače sate, tri ili četiri sate i minute: 7, 12, 730, 0730 ili 7:30. Po napuštanju polja vrijednost se pretvara u HH:mm. Pomak se čita zdesna, počev od sekundi: 2 znači 00:00:02.00, 230 i 0230 znače 00:02:30.00, a 12345 znači 01:23:45.00. Sa razdvajačima dvije grupe su minuti i sekunde, tri sati, minuti i sekunde, a četvrta sadrži stotinke; dozvoljen je predznak. Dani ispod Alarm uključen određuju dane pokretanja; podrazumijevano su izabrani svi. Redoslijed prati jezik programa, a promjena jezika ne mijenja sačuvane dane. Alarm prikazuje skriveni vidžet i dovodi ga ispred drugih prozora bez trajne promjene Uvijek na vrhu. Pusti vremenski signal počinje prvi kratak ton pet sekundi prije alarma. Postavka je nezavisna od kartice Signal; istovremene sekvence se spajaju. Testiraj uključuje treperenje brojčanika ili okvira i provjerava datoteku, naredbu, zvuk, HTTP/HTTPS adresu udaljene skripte i, ako je izabrano, cijeli vremenski signal. Zaustavljanje testa zaustavlja njegov unutrašnji zvuk i probni signal; zaustavljanje alarma zaustavlja njegov unutrašnji zvuk. Isključivanje zvuka ne prekida reprodukciju: ona se nastavlja nečujno i ponovo se čuje nakon uključivanja. Naredbe i udaljene skripte ostaju aktivne.

Klizač Jačina zvuka na kartici Alarm podešava unutrašnju reprodukciju za taj vidžet. Podrazumijevanih −18 dB čuva izvorni nivo datoteke (100%). Pomjeranje udesno pojačava zvuk; najvećih 0 dB odgovara približno 794%. −∞ dB je tišina. Promjene se čuju i tokom testa. MIDI i datoteke koje ne mogu da se dekodiraju i puštaju se rezervnim načinom ograničeni su na 100%.

## Izbor, tasteri i kopiranje datuma

Podešavanja pamte posljednju otvorenu karticu, a Dodaj posljednju dodatu vrstu. Ukloni ili Del uklanja sve izabrane stavke po primjeni promjena. Dvoklik stavke prikazuje skriveni vidžet, označava Vidljivo i nakratko osvjetljava vidžet. Podešavanja iz menija vidžeta biraju taj vidžet u spisku. Klik na dan kalendara bira datum i kopira ga u ostavu; svaki kalendar ima sopstveni oblik u Podešavanjima i meniju. Sva 33 oblika su dostupna u svakom jeziku; tekstualni nazivi i podrazumijevani Kratak datum prate jezik vidžeta. Insert prebacuje izbor trenutne stavke i pomjera pokazivač spiska red niže. Ctrl+C kopira izabrane vidžete, Ctrl+V dodaje kopije redom spiska sa nastavkom naziva na jeziku programa. Dozvoljena su najviše 32 vidžeta. Kopije se dodaju redom do ograničenja, a za preostale se prikazuje obavještenje. Alt+0, Alt+1, Alt+2 i Alt+3 na analognom satu ili kalendaru sa satom biraju veličinu glavnog brojčanika od najmanje do najveće.

Otvaranje podešavanja preko ikone u oblasti za obavještenja ponovo bira posljednji izabrani vidžet.

## Raspored vidžeta

Rasporedi u mrežu čuva približan ručni raspored, priljepljuje središta uz najbliže tačke mreže i uklanja preklapanja. Meni vidžeta djeluje na njegov monitor, ikona za obavještenja na svaki monitor posebno. Ponavljanje čuva raspored. Dvoklik u Podešavanjima označava vidžet brzim svijetloplavim treperenjem; alarm treperi sporije i crveno. Isključivanje Uvijek na vrhu šalje vidžet iza ostalih prozora. Gornja veza na panelu vraća kalendar na danas, donja otvara klasična podešavanja datuma i vremena Windows-a. Uključeno priljepljivanje privlači pomjerani vidžet uz ivicu radne površine sa razdaljine do pet piksela. Promjena veličine čuva vezu sa istom ivicom ili parom ivica.

U samostalnom kalendaru Red Danas na kartici Izgled ili u meniju prikazuje ili skriva donji red. Idi na današnji datum bira danas i vraća mjesečni prikaz. Pri promjeni datuma po vremenu vidžeta današnji datum se bira automatski uz očuvanje trenutnog prikaza kalendara.

## Izgled i čuvanje

Promjene izgleda odmah se vide u pregledu. Otkaži odbacuje neprimijenjene promjene, a Podrazumijevani izgled vraća podrazumijevane vrijednosti za vrstu vidžeta. Digitalni satovi nude font, umekšavanje, boje, neprozirnost, unutrašnji razmak, širinu okvira i providnu pozadinu. Digitalni satovi, kalendari i paneli dijele četiri stila okvira; jednostrukom okviru može se birati boja. Panel ima zasebne fontove za gornji red, vrijeme i donji red, vodeću nulu i izbor veličine brojčanika. Teme i umekšavanje zadaju se za program i svaki vidžet. Prilagođeni fontovi kalendara podržani su uz klasični izgled Windows-a ili kada su teme isključene za program ili vidžet. Podešavanja se mogu izvesti u XML. Uvoz XML-a odmah učitava i čuva podešavanja u izabranom skladištu bez promjene njegove vrste. Automatski XML je %AppData%\FortSoft\CalClock\settings.xml. Po zapisivanju XML-a uklanja se ključ HKCU\SOFTWARE\FortSoft\CalClock; čuvanje u registru uklanja automatski XML.

Umekšavanje fonta nudi ClearType, GDI i Nema. Vodeća nula nudi Prikaži (podrazumijevano), Zadrži razmak i Bez razmaka. Zadrži razmak skriva nulu, ali čuva njenu širinu u izabranom fontu; ostale cifre zadržavaju položaje i kod proporcionalnih fontova. Satovi na monitoru ostaju centrirani sa uračunatim razmakom. Red UTC ima sopstveno centriranje.

## Podešavanja i meniji

Jezik programa, font, umekšavanje, teme, skladište, pokretanje uz Windows i priljepljivanje su zajedničke postavke na kartici Program. Pri prvom pokretanju bira se jezik interfejsa Windows-a; ako nije podržan, koristi se američki engleski. Jezik, umekšavanje i teme vidžeta utiču samo na njega.

Meni vidžeta sadrži primjenjive postavke vidljivosti, Uvijek na vrhu, sekundi, veličine i kopiranja datuma, zatim Rasporedi u mrežu, Podešavanja, Pomoć, O programu i Izlaz. Meni ikone navodi numerisane vidžete, Prikaži sve, Sakrij sve i Isključi sav zvuk, pa odvojeno Rasporedi u mrežu. Prikaz ili vraćanje dovodi vidžet naprijed bez promjene Uvijek na vrhu. Ponovni start aktivira postojeću instancu i po potrebi vraća posljednje skrivene vidžete. Veličine brojčanika i sekundna kazaljka zavise od Windows-a. Alarm i Signal prebacuju se i iz menija; Alarm pokazuje vrijeme i aktivne dane kada nije izabrana cijela nedjelja. Označeno Isključi zvuk odgovara opciji Zvuk isključen na kartici Opšte. Isključi sav zvuk isključuje zvuk svih vidžeta, a ponovljena radnja vraća zvuk samo onima koje je sama isključila. M na svakom vidžetu radi isto. Uključivanje alarma bez izabranih dana otvara njegovu karticu Alarm.

## Zvučni vremenski signal

Signal prati obrazac Greenwich Time Signal (GTS). Kartica Signal ima Vremenski signal uključen i intervale 1, 5, 10, 15, 20, 30 ili 60 minuta prema vremenu vidžeta. Signal je prvobitno isključen, a izabran je jednočasovni interval. Prebacivanje u meniju čuva interval; vrijeme alarma i interval prikazani su u zagradama. Granica prati UTC, vremensku zonu, pomak i NTP. Pet kratkih tonova obilježava posljednjih pet sekundi, dugi tačnu granicu. Istovremeni signali spajaju se u jednu sekvencu. Poslije isključivanja zvuka trenutni ton može da završi; sljedeći se preskaču, a nakon uključivanja čuje se tek sljedeći planirani ton. Samostalni Kalendar nema alarm, vremenski signal ni isključivanje zvuka.

Pri intervalu 20 minuta signal se čuje na :00, :20 i :40 po vremenu vidžeta. Na kartici Program Zvuk vremenskog signala nudi Ugrađeni generator (podrazumijevano) i Sistemski zvučni signal. Izbor važi za sve vidžete, uključujući signale alarma.

Jačina vremenskog signala pokazuje nivo generatora u dB. Desni kraj je 0 dB, najveća neizobličena amplituda sinusoide; tišina je −∞ dB. Podrazumijevano je −18 dB. Testiraj pored izbora zvuka pokreće neprekidan probni zvuk, Zaustavi test ga završava. Obje vrste zvuka mogu se testirati; test se ne čuva. Držanje klizača takođe pušta probni zvuk do otpuštanja miša, osim ako traje test dugmetom. Reprodukcija počinje na sljedećoj cijeloj sekundi: kratak ton svake sekunde i dugi na :00, :05, :10 i tako dalje. Istovremeni probni signali i signali vidžeta ili alarma dijele jedan ton. Zaustavljanje dopušta da trenutni ton završi; dugi može trajati još pola sekunde. Uračunavaju se i stotinke pomaka. Tonovi koji se preklapaju zvuče neprekidno do kraja posljednjeg preklapanja.

## Dodatni satovi

Kalendar sa satom na kartici Opšte može prikazati do dva dodatna sata sa sopstvenim nazivima i vremenskim zonama. Svaki tada pokazuje i lokalni dan nedjelje. Veličina brojčanika bira se posebno na kartici Izgled ili u njegovom kontekstnom meniju. Dodatni satovi nemaju sekundnu kazaljku. Dodavanje, uklanjanje i promjena veličine čuvaju priljepljivanje uz ivice radne površine.

Samo dvoklik neposredno na glavni brojčanik prebacuje njegovu sekundnu kazaljku. Meniji dodatnih satova sadrže samo veličine. Oni dijele jezik, oblik vremena, fontove i pomak vidžeta; njihov digitalni prikaz nema sekunde.

## Oblik vremena i vremenske zone

Oblik vremena na kartici Opšte nudi Prema jeziku (podrazumijevano), 12 sati i 24 sata. Prva opcija prati jezik, a ručni izbor ostaje nakon njegove promjene. Razdvajači i oznake vremena prate jezik vidžeta. AM/PM je prvobitno uključen i upravlja samo oznakom u 12-časovnom režimu; ako jezik nema sopstvene oznake, koristi se AM/PM. Satovi na monitoru prikazuju oznaku u zasebnom redu ispod vremena. UTC uvijek koristi 24-časovni prikaz. Imenovane zone prate lokalno i ljetnje računanje vremena; pomak uz naziv važi za trenutni datum. Zasebne stavke UTC su stalni pomaci od -12:00 do +14:00 u koracima od 15 minuta bez ljetnjeg računanja vremena.

## Izvor vremena

Kartica Vrijeme bira sistemsko vrijeme Windows-a ili NTP servere za cijeli program. NTP mijenja samo prikaz CalClock-a; sat Windows-a se nikada ne mijenja. Do prvog ispravnog odgovora koristi se sistemsko vrijeme. NTP je podrazumijevan. Automatska grupa prema regionu sistema bira češke i slovačke servere, PTB za Evropu ili globalni skup. Mjerenja se filtriraju prema mrežnom kašnjenju i odstupanjima od ostalih odgovora. Sinhronizuj sada odmah počinje novo mjerenje.

Poslije sinhronizacije sat CalClock-a nastavlja nezavisno od kasnijih promjena sistemskog vremena Windows-a. Pri gubitku veze ili promjeni servera nastavlja od posljednje ispravne sinhronizacije do novog odgovora; stanje se čuva do zatvaranja programa.

## Dnevnik NTP sinhronizacije

Kartica Vrijeme bilježi upite NTP serverima od pokretanja programa. Zapis sadrži datum i lokalno vrijeme računara, server i stanje. OK označava ispravan odgovor; θ njegovo odstupanje od sistemskog vremena Windows-a. ERR navodi uzrok i eventualnu šifru greške. Posljednji zapis grupe upita pokazuje i objedinjeno odstupanje Θ kada postoje upotrebljiva mjerenja.

Odstupanja su u milisekundama sa četiri decimale. Pozitivna vrijednost znači da je server ispred Windows-a, negativna da kasni. Θ se zasniva na prihvaćenim mjerenjima i vidi se i u stanju sinhronizacije. Sačuvaj dnevnik izvozi zapise u CSV sa odstupanjima i detaljima grešaka. Zapisi se ne čuvaju između pokretanja; sačuvajte ih prije izlaska ako želite da ostanu.

## Sat na monitoru

Digitalni sat može popuniti jedan ili više monitora i zatamniti ostale. Veličina fonta zadaje se kao procenat visine monitora; podešavaju se i font, umekšavanje, boje i unutrašnji razmak. UTC može biti u zasebnom redu. Podrazumijevan je bijeli tekst na crnoj pozadini. Dok su Podešavanja otvorena, sat je mali pokretni pregled sa odnosom stranica monitora; njegov položaj se čuva. Rasporedi u mrežu ne premješta tu vrstu vidžeta. Esc skriva sat i uklanja zatamnjenje i kada su Podešavanja otvorena.

Pokazivač miša skriva se poslije kratke neaktivnosti iznad sata na monitoru i zatamnjenih monitora, a pojavljuje pri pomjeranju miša. Iznad malog pregleda ostaje vidljiv.

## Izgradnja i pakovanje

Potrebni su Microsoft Visual Studio sa alatima MSVC v145 i Windows SDK. Otvorite `CalClock.slnx`, izaberite `Release | x86` i izgradite rješenje. Izvršna datoteka nastaje u `Release\CalClock.exe`. Podržana je samo konfiguracija Win32/x86 jer integracija sa kontrolom sata Windows-a zahtijeva kompatibilnost sa x86.

Poslije izgradnje pokrenite `.\PackageRelease.ps1` za pravljenje arhive `CalClock-<version>-win32.zip`. Verzija se čita iz `Release\CalClock.exe`. Arhiva sadrži `CalClock.exe` i `license.txt` neposredno u korijenu. Neobavezni parametri za potpisivanje `-SignerName`, `-SignToolPath` i `-TimestampServer` zadaju se pri pokretanju. Postojeći ispravan potpis Authenticode provjerava se i ne zamjenjuje. Prethodne ZIP arhive CalClock-a uklanjaju se na početku svakog pokretanja. Greška potpisivanja ili provjere zaustavlja pakovanje.

## Licenca

CalClock je dostupan pod [licencom MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
