# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · **Slovenščina** · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock je izvorni program Win32/x86 za Windows Vista in novejše različice z neodvisno nastavljivimi plavajočimi urami in koledarji. Deluje v območju za obvestila. Podpira do 32 gradnikov in 36 jezikovnih različic; jezik programa in vsakega gradnika izberete ločeno.

## Upravljanje

Uro ali ploščo povlecite z levim miškinim gumbom. Samostojni koledar premikate za prosti del. Desni klik na gradnik ali ikono v območju za obvestila odpre meni. Levi klik na ikono skrije vidne gradnike; če so vsi skriti, obnovi samo nazadnje skrite.

## Gradniki in nastavitve

V Nastavitvah lahko dodajate, odstranjujete in podvajate analogne in digitalne ure, koledarje, plošče koledarja z uro ter ure na zaslonu. Vsak gradnik ima lastno vidnost, možnost Vedno na vrhu, jezik, časovni pas in odmik v obliki [-]HH:mm:ss.ff. Velikost analognih ur in ur na plošči je nastavljiva. Digitalne ure podpirajo sekunde, vodilno ničlo, pisavo, barve, neprosojnost in prosojno ozadje. Koledar podpira številke tednov in nedeljo kot prvi dan ter uporablja jezik gradnika.

## Budilka in bližnjice

Ure in plošče podpirajo budilko. Program sam predvaja zvočno datoteko enkrat ali neprekinjeno glede na ponavljanje; druge datoteke in ukaze preda sistemu Windows. Klik na številčnico ali prikaz aktivne budilke, Ustavi budilko ali Esc ustavi opozarjanje in zvok programa. Dvoklik na številčnico ali digitalni prikaz preklopi sekunde. F1 odpre pomoč, B Nastavitve, Esc pa skrije gradnik, kadar ne ustavlja budilke. Položaji gradnikov se shranijo po premikanju, položaji pogovornih oken ob zaprtju, nastavitve pa v izbrano shrambo. Ponovni zagon aktivira obstoječi primerek in ohrani gradnike na najbližjem dosegljivem mestu delovnega območja.

## Vnos časa in dejanja budilke

Čas budilke sprejema HH:mm z dvopičjem, piko, presledkom ali drugim ločilom, lahko tudi brez ločila. Ena ali dve števki pomenita ure, tri ali štiri pa ure in minute: 7, 12, 730, 0730 ali 7:30. Po odhodu iz polja se vrednost poenoti v HH:mm. Odmik se bere z desne, od sekund: 2 pomeni 00:00:02.00, 230 in 0230 pomenita 00:02:30.00, 12345 pa 01:23:45.00. Z ločili dve skupini pomenita minute in sekunde, tri ure, minute in sekunde, četrta pa stotinke; dovoljen je predznak. Dnevi pod Budilka vključena določajo dneve sprožitve; privzeto so izbrani vsi. Vrstni red sledi jeziku programa, sprememba jezika pa ne spremeni shranjenih dni. Budilka pokaže skriti gradnik in ga postavi v ospredje brez trajne spremembe Vedno na vrhu. Predvajaj časovni signal začne prvi kratek pisk pet sekund pred budilko. Nastavitev je neodvisna od zavihka Signal; sočasna zaporedja se združijo. Preizkusi sproži utripanje številčnice ali okvira ter preveri datoteko, ukaz, zvok, naslov HTTP/HTTPS oddaljenega skripta in po potrebi celoten časovni signal. Ustavitev preizkusa ustavi njegov notranji zvok in poskusni signal; ustavitev budilke ustavi njen notranji zvok. Izklop zvoka ne ustavi predvajanja: nadaljuje se neslišno in po vklopu spet postane slišno. Ukazi in oddaljeni skripti niso prizadeti.

Drsnik Glasnost zvoka na zavihku Budilka uravnava notranje predvajanje za posamezni gradnik. Privzetih −18 dB ohrani izvirno raven datoteke (100%). Pomik v desno ojača zvok; največjih 0 dB pomeni približno 794%. −∞ dB pomeni tišino. Spremembe se slišijo tudi med preizkusom. MIDI in datoteke, ki jih ni mogoče dekodirati in se predvajajo z nadomestnim načinom, so omejene na 100%.

## Izbiranje, tipke in kopiranje datuma

Nastavitve pomnijo zadnji odprti zavihek, Dodaj pa zadnjo dodano vrsto. Odstrani ali Del odstrani vse izbrane elemente ob uporabi sprememb. Dvoklik elementa pokaže skriti gradnik, označi Vidno in ga na kratko osvetli. Nastavitve v meniju gradnika izberejo ta gradnik na seznamu. Klik dneva v koledarju izbere datum in ga kopira v odložišče. Vsak koledar ima lastno obliko v Nastavitvah in meniju. Vseh 33 oblik je na voljo v vseh jezikih; besedilna imena in privzeti Kratki datum sledijo jeziku gradnika. Insert preklopi izbor trenutnega elementa in premakne kazalec seznama vrstico navzdol. Ctrl+C kopira izbrane gradnike, Ctrl+V pa doda kopije po vrstnem redu seznama s pripono imena v jeziku programa. Dovoljenih je do 32 gradnikov. Kopije se dodajajo po vrsti do omejitve; za preostale se prikaže obvestilo. Alt+0, Alt+1, Alt+2 in Alt+3 na analogni uri ali koledarju z uro izberejo velikost glavne številčnice od najmanjše do največje.

Ob odpiranju nastavitev prek ikone v območju za obvestila je znova izbran nazadnje izbrani gradnik.

## Razporeditev gradnikov

Razporedi v mrežo ohrani približno ročno razporeditev, pripne središča na najbližje mrežne točke in odpravi prekrivanje. Meni gradnika deluje na njegovem zaslonu, ikona za obvestila pa na vsakem zaslonu posebej. Ponovitev ohrani razporeditev. Dvoklik v Nastavitvah označi gradnik s hitrim svetlomodrim utripanjem; budilka utripa počasneje in rdeče. Izklop Vedno na vrhu pošlje gradnik v ozadje. Na plošči koledarja z uro zgornja povezava vrne koledar na danes, spodnja pa odpre klasične nastavitve datuma in časa Windows. Vključeno pripenjanje pritegne vlečeni gradnik do roba delovnega območja na razdalji petih slikovnih pik. Spreminjanje velikosti ohrani pripetost na isti rob ali par robov.

V samostojnem koledarju možnost Vrstica Danes na zavihku Videz ali v meniju pokaže ali skrije spodnjo vrstico. Pojdi na današnji datum izbere danes in vrne mesečni pogled. Ob spremembi datuma po času gradnika se današnji datum izbere samodejno, trenutni pogled koledarja pa se ohrani.

## Videz in shranjevanje

Spremembe videza so vidne takoj v predogledu. Prekliči zavrže neuporabljene spremembe, Privzeti videz pa obnovi privzete vrednosti vrste gradnika. Digitalne ure ponujajo pisavo, glajenje, barve, neprosojnost, notranji odmik, širino obrobe in prosojno ozadje. Digitalne ure, koledarji in plošče imajo štiri skupne sloge obrob; enojni obrobi lahko določite barvo. Plošča ima ločene pisave zgornje vrstice, časa in spodnje vrstice, vodilno ničlo in izbiro velikosti številčnic. Teme in glajenje se določijo za program in vsak gradnik. Pisavo koledarja po meri lahko uporabljate pri klasičnem videzu sistema Windows ali ko so teme izključene za program ali gradnik. Nastavitve je mogoče izvoziti v XML. Uvoz XML takoj naloži in shrani nastavitve v izbrano shrambo, ne da bi spremenil njeno vrsto. Samodejni XML je %AppData%\FortSoft\CalClock\settings.xml. Zapis XML odstrani ključ HKCU\SOFTWARE\FortSoft\CalClock; shranjevanje v register odstrani samodejni XML.

Glajenje pisave ponuja ClearType, GDI in Brez. Vodilna ničla ponuja Pokaži (privzeto), Ohrani prostor in Brez prostora. Ohrani prostor skrije ničlo in rezervira njeno širino v izbrani pisavi; druge števke ostanejo na mestu tudi pri proporcionalnih pisavah. Ure na zaslonu ostanejo sredinsko poravnane z upoštevanjem rezerviranega prostora. Vrstica UTC ima lastno sredinsko poravnavo.

## Nastavitve in meniji

Jezik, pisava, glajenje, teme, shramba, zagon z Windows in pripenjanje so skupne nastavitve na zavihku Program. Ob prvem zagonu se jezik izbere po jeziku vmesnika Windows; če ni podprt, se uporabi ameriška angleščina. Jezik, glajenje in teme gradnika vplivajo samo nanj.

Meni gradnika vsebuje ustrezne izbire vidnosti, Vedno na vrhu, sekund, velikosti in kopiranja datuma, nato Razporedi v mrežo, Nastavitve, Pomoč, O programu in Izhod. Meni ikone vsebuje oštevilčene gradnike ter Pokaži vse, Skrij vse in Izklopi ves zvok; sledi ločeni ukaz Razporedi v mrežo. Prikaz ali obnova postavi gradnik v ospredje brez spremembe Vedno na vrhu. Ponovni zagon aktivira obstoječi primerek in po potrebi obnovi nazadnje skrite gradnike. Velikosti številčnic in podpora sekundnemu kazalcu so odvisne od Windows. Budilko in Signal lahko preklopite v meniju; budilka kaže čas in pri delnem tednu izbrane dneve. Označeni Izklopi zvok ustreza možnosti Zvok izklopljen na zavihku Splošno. Izklopi ves zvok utiša vse gradnike, ob ponovitvi pa obnovi zvok samo tistim, ki jih je sam utišal. Tipka M na katerem koli gradniku naredi isto. Vklop budilke brez izbranega dneva odpre njen zavihek Budilka.

## Zvočni časovni signal

Signal sledi vzorcu Greenwich Time Signal (GTS). Zavihek Signal ponuja Časovni signal vključen in intervale 1, 5, 10, 15, 20, 30 ali 60 minut po prikazanem času gradnika. Signal je sprva izključen, izbran pa je enourni interval. Preklop v meniju ohrani interval; čas budilke in interval sta prikazana v oklepajih. Časovna meja upošteva UTC, časovni pas, odmik in NTP. V zadnjih petih sekundah se oglasi pet kratkih piskov, natanko na meji pa dolg. Sočasni signali se združijo v eno zaporedje. Ob izklopu zvoka se trenutni pisk lahko konča, nadaljnji se izpustijo, po vklopu pa se zasliši šele naslednji načrtovani pisk. Samostojni Koledar nima budilke, časovnega signala ali utišanja.

Pri intervalu 20 minut se signal oglasi ob :00, :20 in :40 po času gradnika. Na zavihku Program Zvok časovnega signala ponuja Vgrajeni generator (privzeto) in Sistemski pisk. Izbira velja za vse gradnike, tudi za signale budilk.

Glasnost časovnega signala kaže raven generatorja v dB. Desni konec je 0 dB, največja nepopačena amplituda sinusoide; tišina je −∞ dB. Privzeto je −18 dB. Preizkusi ob izbiri zvoka začne neprekinjeni predogled, Ustavi preizkus pa ga konča. Preizkusiti je mogoče obe možnosti; preizkus se ne shrani. Držanje drsnika prav tako predvaja predogled do izpusta miške, razen če teče preizkus z gumbom. Predvajanje se začne ob naslednji polni sekundi: kratko vsako sekundo in dolgo ob :00, :05, :10 in tako naprej. Sočasni poskusni, gradniški in budilkini signali imajo skupen ton. Ob ustavitvi se trenutni pisk konča; dolg lahko traja še pol sekunde. Upoštevane so tudi stotinke odmikov. Prekrivajoči se toni trajajo neprekinjeno do konca zadnjega prekrivanja.

## Dodatne ure

Koledar z uro lahko na zavihku Splošno prikaže do dve dodatni uri z lastnima imenoma in časovnima pasovoma. Vsaka nato kaže tudi svoj krajevni dan v tednu. Velikost številčnice izberete posebej na zavihku Videz ali v njenem kontekstnem meniju. Dodatne ure nimajo sekundnega kazalca. Dodajanje, odstranjevanje in spreminjanje velikosti ohrani pripetost gradnika na robove delovnega območja.

Sekundni kazalec preklopi le dvoklik neposredno na glavno številčnico. Meniji dodatnih ur vsebujejo le velikosti. Dodatne ure uporabljajo jezik, obliko časa, pisave in odmik gradnika; njihov digitalni čas ne kaže sekund.

## Oblika časa in časovni pasovi

Oblika časa na zavihku Splošno ponuja Glede na jezik (privzeto), 12 ur in 24 ur. Privzeta možnost sledi jeziku gradnika, ročna izbira pa ostane tudi po spremembi jezika. Ločila in časovne oznake sledijo jeziku. AM/PM je privzeto označen in določa le prikaz oznake v 12-urnem načinu. Če jezik nima svoje oznake, se uporabi AM/PM. Ure na zaslonu jo kažejo v ločeni vrstici pod časom. UTC vedno uporablja 24-urni prikaz. Imenovani pasovi sledijo krajevnemu času in poletnemu času; odmik ob imenu velja za trenutni datum. Samostojne izbire UTC so stalni odmiki od -12:00 do +14:00 v korakih po 15 minut brez poletnega časa.

## Vir časa

Zavihek Čas izbere sistemski čas Windows ali strežnike NTP za celoten program. NTP spremeni le čas CalClocka, ure Windows nikoli. Do prvega veljavnega odgovora se uporablja sistemski čas. NTP je privzet. Samodejni nabor glede na regijo izbere češke in slovaške strežnike, PTB za Evropo ali svetovni nabor. Meritve se filtrirajo po omrežni zakasnitvi in odstopanjih. Sinhroniziraj zdaj takoj sproži novo meritev.

Po sinhronizaciji ura CalClock teče neodvisno od poznejših sprememb sistemske ure Windows. Ob izgubi povezave ali menjavi strežnikov teče od zadnje veljavne sinhronizacije do novega odgovora; stanje se ohrani do zaprtja programa.

## Dnevnik sinhronizacije NTP

Zavihek Čas beleži poizvedbe strežnikom NTP od zagona programa. Zapis vsebuje datum in krajevni čas računalnika, strežnik in stanje. OK označuje veljaven odgovor s θ kot odmikom od ure Windows. ERR navede razlog in morebitno kodo napake. Zadnji zapis skupine poizvedb vsebuje tudi skupni odmik Θ, če so na voljo uporabne meritve.

Odmiki so v milisekundah s štirimi decimalnimi mesti. Pozitivna vrednost pomeni, da je strežnik pred uro Windows, negativna pa za njo. Θ upošteva sprejete meritve in je prikazan tudi v stanju sinhronizacije. Shrani dnevnik izvozi zapise v CSV z odmiki in podrobnostmi napak. Zapisi se ne ohranijo med zagoni; pred izhodom jih shranite, če jih želite obdržati.

## Ura na zaslonu

Digitalna ura lahko zapolni enega ali več zaslonov in po potrebi zatemni druge. Velikost pisave je odstotek višine zaslona; nastavljivi so tudi pisava, glajenje, barve in notranji odmik. UTC je lahko v ločeni vrstici. Privzet je bel napis na črni podlagi. Med odprtimi Nastavitvami je ura majhen premakljiv predogled z razmerjem stranic izbranega zaslona; njegov položaj se shrani. Razporeditev v mrežo tega gradnika ne premika. Esc skrije uro in odstrani zatemnitev tudi med odprtimi Nastavitvami.

Kazalec se po kratki nedejavnosti nad uro na zaslonu ali zatemnjenimi zasloni skrije in ob premiku miške spet pokaže. Nad majhnim predogledom ostane viden.

## Gradnja in pakiranje

Potrebujete Microsoft Visual Studio z orodji MSVC v145 in Windows SDK. Odprite `CalClock.slnx`, izberite `Release | x86` in zgradite rešitev. Izvedljiva datoteka nastane v `Release\CalClock.exe`. Podprta je samo konfiguracija Win32/x86, ker povezava s kontrolnikom ure Windows zahteva združljivost z x86.

Po gradnji zaženite `.\PackageRelease.ps1`, da ustvarite arhiv `CalClock-<version>-win32.zip`. Različica se prebere iz `Release\CalClock.exe`. Arhiv vsebuje `CalClock.exe` in `license.txt` neposredno v korenu. Izbirne parametre za podpisovanje `-SignerName`, `-SignToolPath` in `-TimestampServer` podate ob zagonu. Obstoječi veljavni podpis Authenticode se preveri in se ne nadomesti. Prejšnji arhivi ZIP programa CalClock se odstranijo na začetku vsakega zagona. Napaka pri podpisovanju ali preverjanju ustavi pakiranje.

## Licenca

CalClock je na voljo pod [licenco MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
