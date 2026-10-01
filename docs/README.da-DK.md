# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · **Dansk** · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md)

CalClock er et Win32/x86-program til Windows Vista og nyere, som viser frit placerbare ure og kalendere med uafhængige indstillinger på Windows-skrivebordet. Det kører i meddelelsesområdet og kræver ikke et permanent kontrolvindue.

## Funktioner

- Op til 32 widgets med uafhængige indstillinger
- Eget sprog, tidszone, tidsforskydning, synlighed og altid øverst-indstilling for hver widget
- Analoge ure baseret på Windows-kontrollen `ClockWndMain`, med automatisk registrering af tilgængelige størrelser og understøttelse af sekundviser
- Digitale ure med skrifttyper, farver, uigennemsigtighed, indvendige margener, rammer, valgfrit foranstillet nul og gennemsigtig baggrund
- Windows’ egne kalendere med datovalg, fire rammestile, justerbar rammefarve, ugenumre, valg af første ugedag og 33 kopiformater
- Kalender- og urpaneler med op til to ekstra navngivne ure i egne tidszoner, separate urskivestørrelser, fire rammestile, justerbar farve, UTC-tekst, foranstillet nul og egen skrifttype til hver tekstlinje
- Alarmer med valg af ugedage, visuel markering, intern lydafspilning, gentagelse, lokale kommandoer og HTTP/HTTPS-scriptkald
- Tidssignaler pr. ur hvert 1., 5., 10., 15., 20., 30. eller 60. minut; samtidige signaler samles i én sekvens
- Lydløs-kommando for hvert ur og en markerbar Slå al lyd fra-kommando i meddelelsesområdet
- Valgfri automatisk start med Windows
- Valgfri fastgørelse inden for fem pixels af arbejdsområdets kanter ved træk, aktiveret som standard; fastgørelsen bevares ved ændring af størrelsen
- NTP-synkronisering uden ændring af Windows-systemuret
- NTP-forvalg til Tjekkiet og Slovakiet, PTB, Ubuntu/NTP Pool eller egne servere
- Indstillinger i registreringsdatabasen eller XML, med XML-import og -eksport
- Betjening fra meddelelsesområdet med gendannelse af sidst skjulte widgets
- Identifikation af widgets og stabil placering i et gitter uden overlapning
- Øjeblikkelig forhåndsvisning af udseende med annullering og standardudseende for hver widget
- Skrifttyper til program og widgets, visuelle typografier og ClearType, GDI eller ingen skriftudjævning
- Brugerflader på tjekkisk, amerikansk, britisk og australsk engelsk, tysk, fransk, spansk, italiensk, portugisisk, polsk, slovakisk, dansk, finsk, islandsk, norsk, svensk og tyrkisk

## Widgettyper

| Widget | Beskrivelse |
| --- | --- |
| Analogt ur | Frit placerbar Windows-urskive med de størrelser og den valgfrie sekundviser, som den aktuelle Windows-version tilbyder |
| Digitalt ur | Justerbar digital visning med valgfri UTC-tekst, foranstillet nul, rammer og gennemsigtig baggrund |
| Kalender | Flytbar indbygget månedskalender med datovalg, justerbare rammer og kopiformater |
| Kalender med ur | Kombineret panel med kalender, analogt ur, justerbare tekstlinjer, UTC-visning og rammer |
| Skærmur | Digitalt ur, der fylder en eller flere valgte skærme, med valgfri mørklægning og UTC på en separat linje |

Ved første start vælger CalClock sprog efter Windows’ visningssprog og bruger amerikansk engelsk, hvis sproget ikke understøttes. Der oprettes ét synligt analogt ur som standard. Hver widget bevarer sin placering og sine indstillinger mellem kørsler. Mens Indstillinger er åbent, vises et skærmur altid som en flytbar forhåndsvisning med den valgte skærms størrelsesforhold. `Esc` skjuler skærmuret og fjerner mørklægningen, også når Indstillinger er aktivt. Markøren skjules efter kort inaktivitet over skærmure og mørklagte skærme og vises igen, når musen bevæges. Den forbliver synlig over den lille forhåndsvisning i Indstillinger.

## Betjening

- Træk et ur eller panel med venstre museknap.
- Træk en selvstændig kalender i et ledigt område.
- Højreklik på en widget eller ikonet i meddelelsesområdet for at åbne genvejsmenuen.
- Venstreklik på ikonet i meddelelsesområdet for at skjule synlige widgets. Er alle skjult, gendanner næste klik kun de sidst skjulte.
- Dobbeltklik på en urskive for at skifte sekundvisningen. I et kalenderpanel ændres sekundviseren kun ved dobbeltklik direkte på hovedurskiven. Ekstra ure har ingen sekundviser.
- `F1` åbner Hjælp, `B` Indstillinger, `M` skifter den globale lydløs-tilstand, og `Esc` skjuler en widget eller stopper en aktiv alarm.
- Dobbeltklik på en widget i Indstillinger for om nødvendigt at vise den, markere `Synlig` og kort identificere den på skrivebordet.
- Åbning af Indstillinger fra en widgets genvejsmenu vælger straks den pågældende widget.
- Brug `Ctrl` eller `Shift` til flervalg, `Ctrl+A` til at vælge alle og `Del` til at fjerne de valgte. `Insert` skifter markeringen af det aktuelle element og flytter listemarkøren til næste række, som i Total Commander.
- Alle listens genveje virker også, når Fjern eller Dupliker har fokus. Genvejen flytter fokus til listen og udfører handlingen. `Ctrl+C` kopierer valgte widgets, og `Ctrl+V` føjer kopierne til sidst i listens rækkefølge. Kopierne indeholder alle indstillinger og får en navnetilføjelse på programsproget. Dupliker udfører samme handling direkte. Der tillades højst 32 widgets. Hvis alle kopier ikke kan være der, tilføjes dem, der er plads til, i rækkefølge, og der vises en besked om resten.
- `Ctrl+A` eller et tredobbelt klik i et tekstfelt markerer hele teksten.

Når flere widgets er valgt, deaktiveres deres kontrolelementer på Generelt, Udseende, Alarm og Signal; de globale faner Tid og Program er fortsat tilgængelige. Indstillinger husker den sidst åbne fane og den sidst tilføjede widgettype. På et lille arbejdsområde får vinduet vandret eller lodret rulning efter behov.

Kalenderdatoer kan kopieres i 33 formater: lokale, sorterbare, med dag eller måned først, tekstbaserede og med ugedag. Alle masker findes på alle brugerfladesprog. Det korte lokale standardformat følger widgetens sprog, ligesom måneds- og ugedagsnavne. Punkterne viser masken og et aktuelt eksempel.

Et kalenderpanel kan vise op til to ekstra ure. Aktivér hvert ur på Generelt og vælg navn og tidszone. Navngivne zoner følger deres egne sommertidsregler; faste UTC-forskydninger forbliver faste. Når ekstra ure er aktive, viser hvert ur sin lokale ugedag under tiden. De tre størrelseslister på Udseende styrer hoveduret, Ur 1 og Ur 2 i den rækkefølge. Højreklik på en ekstra urskive for at vælge størrelse. Ekstra ure udelader altid sekunder og deler widgetens sprog, tidsformat, skrifttyper og tidsforskydning. Når ure tilføjes, fjernes eller ændrer størrelse, bevares fastgørelsen til de samme kanter af arbejdsområdet.

I panelet er datoen øverst et link, som fører kalenderen til i dag. Tidszoneteksten nederst åbner Windows’ klassiske indstillinger for dato og klokkeslæt. Begge links kan nås med `Tab`, viser et fokusrektangel og aktiveres med tastaturet. Kalenderen er fortsat fuldt interaktiv, men udelader den overflødige I dag-række i den kombinerede visning.

`Arranger i gitter` placerer synlige skrivebordswidgets i et stabilt gitter uden overlapning og bevarer omtrent den manuelle placering. Widgeten, hvis menu startede kommandoen, bliver stående; kommandoen fra meddelelsesområdet arrangerer hver skærm særskilt. Skærmure er undtaget.

## Udseende

For selvstændige kalendere styrer **I dag-række** i menuen eller på Udseende den nederste række. Den er markeret som standard; fjern markeringen for at skjule rækken og gøre kalenderen mindre. Valget gemmes pr. widget. **Gå til i dag** forbliver tilgængeligt og vender tilbage til månedsvisningen. Når datoen skifter efter widgetens tid, vælger kalenderen automatisk i dag og bevarer sin aktuelle visning.

Udseendeændringer vises straks på den valgte widget. `Annuller` gendanner ændringer, der ikke er anvendt; `Standardudseende` gendanner standarderne for widgettypen.

Digitale ure, kalendere og paneler deler fire rammestile. Den enkle ramme har justerbar farve; rammebredde kan ændres, hvor widgeten understøtter det. Gennemsigtige digitale ure tilbyder samme stile som uigennemsigtige. Skrifttypedialoger viser kun relevante valg og udelader ubrugt forhåndsvisning og effekter. Program- og kalenderskrifter har intet størrelsesvalg, mens digitale ure og paneltekster har. En indbygget kalender bruger kun en egen skrifttype, når visuelle typografier er slået fra for kalenderen eller hele programmet.

Programsprog, brugerfladeskrift, udjævning, visuelle typografier, lagring, Windows-start og fastgørelse til kanter er globale indstillinger på Program. Tidskilden er også global. Widgetsprog, udjævning, typografier, tidszone, forskydning, alarm og tidssignal indstilles uafhængigt. Når et nyt programsprog anvendes, genskabes det åbne Indstillinger-vindue straks på dette sprog. Udjævning tilbyder **ClearType**, **GDI** og **Ingen**. På Udseende står udjævning og deaktivering af temaer samme sted for alle typer, med **Standardudseende** under.

Skyderen **Lydstyrke** på Alarm styrer internt afspillede lydfiler separat for hver widget og viser niveauet i dB. Standardværdien **−18 dB** bevarer filens oprindelige niveau (**100%**). Mod højre forstærkes lyden; maksimum **0 dB** svarer til cirka **794%** af oprindelig amplitude. Yderst til venstre er **−∞ dB** (stilhed). Ændringer virker under lydtesten. Skyderen deaktiveres for filer, der åbnes i eksterne programmer. Forstærkning gælder afkodet lyd, herunder WAV, MP3, WMA, AAC, M4A og FLAC, når Windows understøtter dem. Ældre afspilning af filer, der ikke kan afkodes, eksempelvis MIDI, er begrænset til 100%.

Alarmens ugedage følger første ugedag i den valgte programkultur. Gemte dage bevarer deres betydning ved sprogskift. Aktivering fra menuen uden valgte ugedage åbner widgetens Alarm-fane i stedet for at aktivere en alarm, der ikke kan ringe.

Standardrammebredden for digitale ure er nul. **Foranstillet nul** tilbyder **Vis** (standard), **Bevar plads** og **Uden plads**. **Bevar plads** skjuler nullet, men reserverer dets faktiske bredde i den valgte skrifttype, så øvrige cifre bevarer positionen, også med proportionale skrifttyper. Frit placerbare digitale ure venstrejusterer tiden og beholder en fast størrelse, mens tiden går. Skærmure centrerer et fast tidsområde tilpasset skrifttype og format, med plads til to timecifre. Tidsændringer centrerer eller skalerer ikke teksten på ny. AM/PM- eller UTC-linjen centreres uafhængigt. Skærmure bruger som standard hvid tekst på sort baggrund.

## Tid og alarmer

Digitale ure, kalenderpaneler og skærmure tilbyder **Efter sprog**, **12 timer** og **24 timer** under **Tidsformat** på Generelt. **Efter sprog** er standard: amerikansk og australsk engelsk bruger eksempelvis 12 timer, britisk engelsk 24. Et manuelt valg bevares, når widgetsproget ændres. Skilletegn og AM/PM-markører følger kulturen; kulturer uden egne markører bruger **AM/PM** i 12-timerstilstand.

**AM/PM** er markeret som standard. Fjernes markeringen, skjules markøren uden at ændre 12-timerscyklussen. Valget er deaktiveret i 24-timerstilstand og for widgets uden digital tid. Skærmure viser markøren på en særskilt linje under tiden, som UTC. **UTC bruger altid 24 timer**; cyklus og AM/PM er deaktiveret ved UTC, men værdierne gemmes til tilbagevenden til lokal tid. Valget for foranstillet nul bestemmer fortsat, om det vises, skjules med reserveret plads eller udelades.

Navngivne tidszoner viser stedets civile tid og følger automatisk dets sommertidsregler. Forskydningen ved navnet gælder den aktuelle dato og opdateres, når listen åbnes. Særskilte **UTC**-punkter tilbyder faste forskydninger fra **UTC−12:00** til **UTC+14:00** i trin på 15 minutter uden sommertid. Vælg lokal zone, en anden navngiven zone eller fast UTC-forskydning uafhængigt for hver widget.

Hver widget kan bruge en vilkårlig Windows-tidszone og en forskydning med fortegn i formen `[-]HH:mm:ss.ff`. Kompakt indtastning fortolkes fra højre, begyndende med sekunder.

Forskydning er nyttig i eksempelvis radiostudier til at kompensere for forsinkelsen i transmissionsvejen. Ved at stille studiets ur foran med den målte forsinkelse når tidssignalet lytterne på det tilsigtede tidspunkt.

CalClock kan bruge Windows-systemtid eller en programlokal korrektion fra NTP-servere. Valget gælder alle widgets. Synkronisering ændrer aldrig Windows-uret. Hvis NTP-forbindelsen mistes efter en vellykket synkronisering, forbliver den seneste korrektion aktiv i proceshukommelsen. Serverskift bevarer også gyldig korrektion, indtil et nyt svar modtages.

Urwidgets understøtter alarmer på individuelt valgte ugedage; alle syv er aktive som standard. En alarm viser sin skjulte widget og bringer den foran andre vinduer uden permanent at ændre altid øverst. WAV, MP3, WMA, MIDI, AAC, M4A og FLAC genkendes til intern engangsafspilning eller gentagelse; faktisk afkodning afhænger af installerede Windows-mediekomponenter. Andre filer og kommandoer sendes asynkront til Windows. En alarm kan også kalde en HTTP- eller HTTPS-adresse. Uafhængigt heraf kan den bruge tidssignalet med seks bip, hvor første korte bip lyder fem sekunder før alarmtiden.

Kør fil eller kommando aktiverer feltet, Gennemse, Test og gentagelse. Test og gentagelse kræver også et ikke-tomt felt, men en igangværende test kan altid stoppes. Test viser den visuelle markering og afprøver fil, kommando, lyd og fjernscriptets adresse asynkront. Hvis alarmens tidssignal er valgt, afspilles også hele sekvensen på seks bip; Stop test afslutter intern lyd og signalforhåndsvisning.

Signal-fanen kan deaktivere signaler eller planlægge dem hvert 1., 5., 10., 15., 20., 30. eller 60. minut efter widgetens viste tid. 20-minuttersintervallet lyder ved :00, :20 og :40. Mønstret er **Greenwich Time Signal (GTS)**: fem korte bip markerer de sidste fem sekunder og et længere den nøjagtige grænse. Tidszoner, UTC, forskydninger og aktuel NTP-korrektion respekteres. Alarmens signal og Signal-fanen indstilles uafhængigt; falder tiderne sammen, spiller CalClock én fælles sekvens. Brøkdele af sekunder i forskydningen respekteres, og overlappende widget-, alarm- og testtoner fortsætter uafbrudt til den sidste overlapning slutter.

**Tidssignalets lyd** på Program tilbyder **Indbygget generator** (standard) og **Systembip**. Valget gælder alle signaler, også alarmer, og gemmes globalt. For **Indbygget generator** viser **Tidssignalets lydstyrke** niveauet i dB for hele programmet. Højre endepunkt er **0 dB**, den største uforvrængede sinusamplitude; stilhed er **−∞ dB**. Standardniveauet er **−18 dB**. Decibelskalaen har −18 dB i midten. Generatoren starter og afslutter toner ved nulgennemgang, også når en test stoppes. Et igangværende bip får lov at afslutte; et langt bip kan tage op til et halvt sekund. **Test** ved **Tidssignalets lyd** starter en kontinuerlig forhåndsvisning; **Stop test** afslutter den. Begge lydmetoder kan testes, og testtilstanden gemmes ikke. Holdes lydstyrkeskyderen nede, starter også en forhåndsvisning indtil musen slippes, medmindre knaptesten kører. Afspilningen starter på næste hele sekund, med korte toner hvert sekund og en lang ved :00, :05, :10 osv. Forhåndsvisning og samtidige widget- eller alarmsignaler deler én tone. For **Systembip** deaktiveres kun lydstyrkeskyderen. Lydvalget er kun tilgængeligt, hvis systemet understøtter begge metoder.

Alarm og tidssignal kan også slås til eller fra i genvejsmenuen for widgets med lyd. Alarmens punkt viser tiden og aktive ugedage, medmindre alle er valgt. Lydløs gælder widgeten og svarer til valget på Generelt. En selvstændig Kalender har hverken alarm, tidssignal eller lydløs-tilstand, så disse kommandoer udelades eller deaktiveres. I meddelelsesområdet hedder kommandoen Slå al lyd fra; `M` på en widget udfører samme globale skift. Global genaktivering gendanner kun de widgets, som blev gjort lydløse af forrige globale handling. Intern lyd fortsætter lydløst og bliver hørbar igen ved genaktivering. Et igangværende bip kan afsluttes; efterfølgende bip springes over, til lyden aktiveres. Andre kommandoer og fjernscripts påvirkes ikke.

## Indstillinger og menuer

`Gem` anvender ændringer og lukker Indstillinger; `Anvend` gør det uden at lukke; `Annuller` forkaster ikke-anvendte ændringer, herunder forhåndsvisningen af udseendet. Enter aktiverer `Gem`, Esc `Annuller`.

Hver widgetmenu indeholder relevante kommandoer — synlighed, altid øverst, sekunder, analog størrelse eller datokopiformat — efterfulgt af `Arranger i gitter`, Indstillinger, Hjælp, Om og Afslut. Meddelelsesområdets menu viser alle widgets med nummer, derefter Vis alle, Skjul alle og Slå al lyd fra. Det særskilt grupperede `Arranger i gitter` følger før programkommandoerne.

Visning eller gendannelse bringer widgets foran andre vinduer uden at ændre altid øverst. CalClock sørger for mindst én synlig widget efter start. En ny start aktiverer den eksisterende instans og gendanner sidst skjulte widgets, hvis ingen er synlige. Ikonet registreres automatisk igen, når Windows Stifinder genstarter. Hvis `ClockWndMain` ikke understøtter sekundviser i valgt størrelse, deaktiveres Sekunder, men valget bevares til en anden understøttet størrelse.

## Lagring af indstillinger

Indstillingerne gemmes som standard under:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

XML-lagring kan aktiveres i Indstillinger og bruger:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Efter vellykket XML-lagring fjerner CalClock sin programtilstand fra registreringsdatabasen. Skift tilbage fjerner tilsvarende den automatiske XML-fil og tomme CalClock-mapper. XML-import indlæser og gemmer straks indstillingerne i den valgte lagring uden at skifte type. Lydløs-tilstanden gemmes pr. widget med lyd. Start med Windows gemmes som værdien `CalClock` i den normale Windows-nøgle `Run` for den aktuelle bruger.

## Kompilering

Krav:

- Microsoft Visual Studio med MSVC v145-værktøjssættet
- Windows SDK

Åbn `CalClock.slnx`, vælg `Release | Win32`, og byg løsningen. Programfilen oprettes som:

```text
Release\CalClock.exe
```

Kun Win32/x86 understøttes. Projektet tilbyder bevidst ingen x64-konfiguration, fordi integrationen med Windows-urkontrollen kræver x86-kompatibilitet.

## Licens

CalClock er tilgængeligt under [MIT-licensen](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
