# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · **Dansk** · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

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
- Slå lyd fra-kommando for hvert ur og en markerbar Slå al lyd fra-kommando i meddelelsesområdet
- Valgfri automatisk start med Windows
- Valgfri fastgørelse inden for fem pixels af arbejdsområdets kanter ved træk, aktiveret som standard; fastgørelsen bevares ved ændring af størrelsen
- NTP-synkronisering uden ændring af Windows-systemuret
- NTP-forvalg til Tjekkiet og Slovakiet, PTB, Ubuntu/NTP Pool eller egne servere
- Indstillinger i registreringsdatabasen eller XML, med XML-import og -eksport
- Betjening fra meddelelsesområdet med gendannelse af sidst skjulte widgets
- Identifikation af widgets og stabil placering i et gitter uden overlapning
- Øjeblikkelig forhåndsvisning af udseende med annullering og standardudseende for hver widget
- Skrifttyper til program og widgets, visuelle typografier og ClearType, GDI eller ingen skriftudjævning
- Brugerflade på 36 sprogvarianter med særskilt sprogvalg for programmet og hver widget

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
- Tryk `Alt+0`, `Alt+1`, `Alt+2` eller `Alt+3` på Analogt ur eller Kalender med ur for at vælge hovedurskivens størrelse, fra mindst til størst.
- Dobbeltklik på en widget i Indstillinger for om nødvendigt at vise den, markere `Synlig` og kort identificere den på skrivebordet.
- Åbning af Indstillinger fra en widgets genvejsmenu vælger straks den pågældende widget.
- Delete fjerner markerede widgets. `Insert` skifter markeringen af det aktuelle element og flytter listemarkøren én række ned.
- `Ctrl+C` kopierer valgte widgets, og `Ctrl+V` føjer kopierne til sidst i listens rækkefølge. Kopierne indeholder alle indstillinger og får en navnetilføjelse på programsproget. Dupliker udfører samme handling direkte. Der tillades højst 32 widgets. Hvis alle kopier ikke kan være der, tilføjes dem, der er plads til, i rækkefølge, og der vises en besked om resten.

Når indstillingerne åbnes fra ikonet i meddelelsesområdet, vælges den sidst valgte widget igen.

Indstillinger husker den sidst åbne fane og den sidst tilføjede widgettype.

Kalenderdatoer kan kopieres i 33 formater: lokale, sorterbare, med dag eller måned først, tekstbaserede og med ugedag. Alle masker findes på alle brugerfladesprog. Det korte lokale standardformat følger widgetens sprog, ligesom måneds- og ugedagsnavne. Punkterne viser masken og et aktuelt eksempel.

Et kalenderpanel kan vise op til to ekstra ure. Aktivér hvert ur på Generelt og vælg navn og tidszone. Navngivne zoner følger deres egne sommertidsregler; faste UTC-forskydninger forbliver faste. Når ekstra ure er aktive, viser hvert ur sin lokale ugedag under tiden. De tre størrelseslister på Udseende styrer hoveduret, Ur 1 og Ur 2 i den rækkefølge. Højreklik på en ekstra urskive for at vælge størrelse. Ekstra ure udelader altid sekunder og deler widgetens sprog, tidsformat, skrifttyper og tidsforskydning. Når ure tilføjes, fjernes eller ændrer størrelse, bevares fastgørelsen til de samme kanter af arbejdsområdet.

I panelet er datoen øverst et link, som fører kalenderen til i dag. Tidszoneteksten nederst åbner Windows’ klassiske indstillinger for dato og klokkeslæt.

Paneler med kalender og ur kan vise Windows-meddelelser om dato og klokkeslæt over det nederste link. **Meddelelser om dato og klokkeslæt** på fanen **Generelt** er slået til som standard og gemmes separat for hvert panel. Når flere meddelelser er relevante, vises de under hinanden som i Windows. Hvis indstillingen er slået fra, eller der ikke er nogen relevant meddelelse, bevarer panelet sin oprindelige størrelse og sit layout uden at reservere tom plads.

`Arranger i et gitter` placerer synlige skrivebordswidgets i et stabilt gitter uden overlapning og bevarer omtrent den manuelle placering. Widgeten, hvis menu startede kommandoen, bliver stående; kommandoen fra meddelelsesområdet arrangerer hver skærm særskilt. Skærmure er undtaget.

## Udseende

For selvstændige kalendere styrer **Rækken I dag** i menuen eller på Udseende den nederste række. Den er markeret som standard; fjern markeringen for at skjule rækken og gøre kalenderen mindre. Valget gemmes pr. widget. **Gå til i dag** forbliver tilgængeligt og vender tilbage til månedsvisningen. Når datoen skifter efter widgetens tid, går kalenderen kun videre til den nye dag, hvis i dag er valgt og synlig i månedsvisningen. En manuelt valgt dato eller en anden visning bevares; markeringen og rækken I dag opdateres altid.

Udseendeændringer vises straks som et eksempel på den valgte widget. `Standardudseende` gendanner standardværdierne for denne widgettype. Når Indstillinger lukkes med ændringer, der ikke er anvendt, bliver du spurgt, om de skal gemmes. Advarslen er slået til som standard og kan slås fra på fanen Program.

Digitale ure, kalendere og paneler deler fire rammestile. Den enkle ramme har justerbar farve; rammebredde kan ændres, hvor widgeten understøtter det. Gennemsigtige digitale ure tilbyder samme stile som uigennemsigtige. Program- og kalenderskrifter har intet størrelsesvalg, mens digitale ure og paneltekster har. En indbygget kalender kan bruge en egen skrifttype med Windows klassiske udseende eller med temaer slået fra for widgeten.

Programsprog, brugerfladeskrift, udjævning, lagring, Windows-start og fastgørelse til kanter er globale indstillinger på Program. Deaktivering af temaer på Program gælder kun Indstillinger, Hjælp, Om og Tidsberegner. Hver widget bruger sin egen temaindstilling. Tidskilden er også global. Widgetsprog, udjævning, typografier, tidszone, forskydning, alarm og tidssignal indstilles uafhængigt. Udjævning tilbyder **ClearType**, **GDI** og **Ingen**.

Windows 2000-stil kræver Deaktiver temaer og gælder kun Indstillinger, Hjælp, Om og Tidsberegner. Med
systemets standardskrifttype bruger disse vinduers kontrolelementer Tahoma 8 pt; en brugerdefineret
programskrifttype har forrang. Licensen beholder skrifttypen med fast tegnbredde. I denne tilstand er kun GDI
og Ingen tilgængelige for skriftudjævning: et gemt valg af ClearType bruger midlertidigt GDI og gendannes, når
tilstanden slås fra. Hvis visuelle typografier er deaktiveret i Windows, vises begge stilvalg som umarkerede
og deaktiverede, uden at de gemte valg ændres.

Skyderen **Lydstyrke** på Alarm styrer internt afspillede lydfiler separat for hver widget og viser niveauet i dB. Standardværdien **−18 dB** bevarer filens oprindelige niveau (**100%**). Mod højre forstærkes lyden; maksimum **0 dB** svarer til cirka **794%** af oprindelig amplitude. Yderst til venstre er **−∞ dB** (stilhed). Ændringer virker under lydtesten. Forstærkning gælder afkodet lyd, herunder WAV, MP3, WMA, AAC, M4A og FLAC, når Windows understøtter dem. Ældre afspilning af filer, der ikke kan afkodes, eksempelvis MIDI, er begrænset til 100%.

Alarmens ugedage følger første ugedag i den valgte programkultur. Gemte dage bevarer deres betydning ved sprogskift. Aktivering fra menuen uden valgte ugedage åbner widgetens Alarm-fane i stedet for at aktivere en alarm, der ikke kan ringe.

**Foranstillet nul** tilbyder **Ja** (standard), **Nej, bevar plads** og **Nej, uden plads**. **Nej, bevar plads** skjuler nullet, men reserverer dets faktiske bredde i den valgte skrifttype, så øvrige cifre bevarer positionen, også med proportionale skrifttyper. Skærmure bruger som standard hvid tekst på sort baggrund.

## Tidsberegner

Åbn Tidsberegner fra en widgets menu eller menuen for ikonet i meddelelsesområdet. Tidsinterval beregner
forskellen mellem to datoer og tider. Runde værdier fremhæver runde værdier, gentagne cifre samt månedlige og
årlige mærkedage i kalenderen fra den valgte start. Gemte datoer og tider giver mulighed for at tilføje,
redigere, sortere og slette datoer og tider med beskrivelser. Datoer og tider gemmes separat i
`%APPDATA%\FortSoft\CalClock\times.xml`. Eksport af indstillinger medtager disse poster. Import bevarer
eksisterende poster og springer kun poster over med samme UTC-tidspunkt og identisk fuld beskrivelse, uanset
visningens tidszone.

Kalenderen følger dagens dato over midnat i starttidens tidszone, når i dag er valgt og synlig i månedsvisningen. En manuelt valgt dato eller en anden visning bevares; markeringen og rækken I dag opdateres altid.

Hvert input har sin egen tidszone fra samme liste som i Indstillinger. Den aktuelle Windows-tidszone er
standard. Et entydigt UTC-tidspunkt og visningszonen gemmes. Et zoneskift bevarer tidspunktet. Vælg
UTC-forskydningen ved en gentaget time; lokale tidspunkter, der ikke findes, kan ikke gemmes. Timer måler
forløbet tid; kalenderberegninger bruger startzonen. Nu bruger Windows-systemtiden uden widgetforskydning,
vist i den valgte zone.

Import accepterer også en separat XML-fil med gemte datoer og klokkeslæt; posterne flettes uden at ændre
programmets indstillinger.

På fanen Fremhævning kan du vælge reglerne for fremhævning af datoer i kalenderen. Som standard fremhæves
startdagen (nulværdier), runde værdier, der ender på nuller, de første ni hele uger samt måneds- og årsdage.
Gentagne cifre 1–9 (for eksempel 11, 111 eller 66, 666) kan aktiveres enkeltvis og er slået fra som standard.

Klik på en kolonneoverskrift for at sortere gemte poster efter det faktiske tidspunkt eller beskrivelsens
tekst. Klik igen for at vende rækkefølgen; en pil viser retningen.

Vinduets placering, den aktive fane, beregningsdata og fremhævningsvalg gemmes med programindstillingerne i
registreringsdatabasen eller XML afhængigt af det valgte lager.

Eksport på fanen med gemte datoer og tider gemmer kun disse poster i en separat XML-fil. Import på denne fane
udtrækker kun datoer og tider, også fra eksporterede indstillinger, og fletter dem med eksisterende poster.

## Tid og alarmer

Digitale ure, kalenderpaneler og skærmure tilbyder **Efter sprog**, **12 timer** og **24 timer** under **Tidsformat** på Generelt. **Efter sprog** er standard: amerikansk og australsk engelsk bruger eksempelvis 12 timer, britisk engelsk 24. Et manuelt valg bevares, når widgetsproget ændres. Skilletegn og AM/PM-markører følger kulturen; kulturer uden egne markører bruger **AM/PM** i 12-timerstilstand.

**AM/PM** er markeret som standard. Fjernes markeringen, skjules markøren uden at ændre 12-timerscyklussen. Skærmure viser markøren på en særskilt linje under tiden, som UTC. UTC bruger altid 24-timersformat. Valget for foranstillet nul bestemmer fortsat, om det vises, skjules med reserveret plads eller udelades.

Navngivne tidszoner viser stedets civile tid og følger automatisk dets sommertidsregler. Forskydningen ved navnet gælder den aktuelle dato og opdateres, når listen åbnes. Særskilte **UTC**-punkter tilbyder faste forskydninger fra **UTC−12:00** til **UTC+14:00** i trin på 15 minutter uden sommertid. Vælg lokal zone, en anden navngiven zone eller fast UTC-forskydning uafhængigt for hver widget.

Nye widgets bruger som standard **Aktuel Windows-tidszone**, som følger den aktuelle Windows-tidszone og indstillingen for automatisk sommertid. Eksisterende widgets beholder deres valgte zoner. Valget bestemmer tidszonen; den fælles tidskilde Windows eller NTP er uafhængig af det.

Hver widget kan bruge en vilkårlig Windows-tidszone og en forskydning med fortegn i formen `[-]HH:mm:ss.ff`. Kompakt indtastning fortolkes fra højre, begyndende med sekunder.

Forskydning er nyttig i eksempelvis radiostudier til at kompensere for forsinkelsen i transmissionsvejen. Ved at stille studiets ur foran med den målte forsinkelse når tidssignalet lytterne på det tilsigtede tidspunkt.

Widgettens forskydning anvendes på UTC før omregning til tidszonen og forskyder derfor også tidspunktet for skift til eller fra sommertid. Et ur, der går ti sekunder foran, skifter ti sekunder tidligere; et ur, der går ti sekunder bagefter, skifter ti sekunder senere. Visere, digital visning, kalenderdatoer, alarmer og tidssignaler bruger den beregnede tid.

Fanen Tid vælger Windows-tid eller NTP-servere for hele programmet. NTP korrigerer kun CalClock og ændrer aldrig Windows. NTP er standard; det automatiske sæt vælger servere efter område og filtrerer målinger efter forsinkelse og afvigelser.

Efter synkronisering går CalClock-uret videre uafhængigt af senere ændringer af systemtiden i Windows. Hvis forbindelsen afbrydes, eller serverne ændres, fortsætter uret fra den seneste gyldige synkronisering, indtil et nyt svar modtages; denne tilstand bevares, indtil programmet lukkes.

Fanen Tid registrerer NTP-serverforespørgsler siden programmets start. Hver post indeholder dato og computerens lokale tid, server og status. OK angiver et gyldigt svar, og θ viser tidsafvigelsen fra Windows-systemtiden. ERR angiver fejlårsagen og en eventuel fejlkode. Den sidste post i en forespørgselsgruppe viser også den beregnede tidsafvigelse Θ, når brugbare målinger er tilgængelige.

Tidsafvigelser vises i millisekunder med fire decimaler. En positiv værdi betyder, at serveruret går foran Windows; en negativ værdi betyder, at det går bagefter. Θ tager hensyn til de godkendte målinger og vises også i synkroniseringsstatussen.

Gem log eksporterer posterne til CSV, inklusive tidsafvigelser og fejloplysninger. Poster beholdes ikke mellem programstarter; gem dem før afslutning, hvis du vil beholde dem.

Urwidgets understøtter alarmer på individuelt valgte ugedage; alle syv er aktive som standard. En alarm viser sin skjulte widget og bringer den foran andre vinduer uden permanent at ændre altid øverst. WAV, MP3, WMA, MIDI, AAC, M4A og FLAC genkendes til intern engangsafspilning eller gentagelse; faktisk afkodning afhænger af installerede Windows-mediekomponenter. Andre filer og kommandoer sendes asynkront til Windows. En alarm kan også kalde en HTTP- eller HTTPS-adresse. Uafhængigt heraf kan den bruge tidssignalet med seks bip, hvor første korte bip lyder fem sekunder før alarmtiden.

Alarmtonerne planlægges efter det faktiske tidspunkt for den kommende alarm, efter tidszoneomregning og widgetforskydning. De begynder fem reelle sekunder før dette tidspunkt, også når det viste ur springer direkte til alarmtiden. En alarmtid, der springes over om foråret, udløser hverken alarm eller toner. I den gentagne time om efteråret udløses alarmen og dens toner kun én gang for samme dato og indstillede klokkeslæt.

Hvis CalClock fortsat kører, udløser hver widget sin senest overskredne alarm én gang efter slumretilstand, dvale eller forsinket behandling, inklusive de indstillede handlinger. En ny start af CalClock afspiller ikke gamle alarmer; overskredne tidssignaler og alarmens forudgående bip afspilles ikke bagefter. „Væk computeren til alarmen“ er som standard slået fra og kræver, at CalClock kører, og at Windows og hardwaren understøtter vækning; langsom vækning kan forhindre rettidige alarmbip.

Test får urskiven eller panelrammen til at blinke og afprøver den indstillede fil, kommando, lyd og
HTTP/HTTPS-adresse til fjernscriptet. Bippene før alarmen afspilles ikke. Stop test afslutter den visuelle
markering og testens interne lyd; stop af alarmen afslutter dens interne lyd. Hvis Alarm aktiv slås fra,
deaktiveres de øvrige kontroller på fanen Alarm, uden at deres værdier slettes. Testen kræver en aktiv alarm,
at Kør en fil eller kommando er markeret, og at fil- eller kommandofeltet er udfyldt.

Signal-fanen har afkrydsningsfeltet Tidssignal aktivt og alternativknapper til intervaller på 1, 5, 10, 15, 20, 30 eller 60 minutter efter widgetens viste tid. Signalet er som udgangspunkt slået fra med et interval på én time valgt. Når Signal slås fra og til i widgetmenuen, bevares intervallet. Menuen viser alarmtid og signalinterval i parentes. 20-minuttersintervallet lyder ved :00, :20 og :40. Mønstret er **Greenwich Time Signal (GTS)**: fem korte bip markerer de sidste fem sekunder og et længere den nøjagtige grænse. Tidszoner, UTC, forskydninger og aktuel NTP-korrektion respekteres. Alarmens signal og Signal-fanen indstilles uafhængigt. Brøkdele af sekunder i forskydningen respekteres, og overlappende widget-, alarm- og testtoner fortsætter uafbrudt til den sidste overlapning slutter på samme lydudgang.

**Lyd for tidssignal** på Program tilbyder **Indbygget generator** (standard) og **Systembip**. Valget gælder
alle signaler, også alarmer, og gemmes globalt. For **Indbygget generator** viser **Lydstyrke for tidssignal**
niveauet i dB for hele programmet. Højre endepunkt er **0 dB**, den største uforvrængede sinusamplitude;
stilhed er **−∞ dB**. Standardniveauet er **−18 dB**. Decibelskalaen har −18 dB i midten. Et bip, der allerede
er begyndt, kan afsluttes, efter at testen er stoppet. **Test** ved **Lyd for tidssignal** starter en
kontinuerlig forhåndsvisning; **Stop test** afslutter den. Begge lydmetoder kan testes, og testtilstanden
gemmes ikke. Holdes lydstyrkeskyderen nede, starter også en forhåndsvisning indtil musen slippes, medmindre
knaptesten kører. Afspilningen starter på næste hele sekund, med korte toner hvert sekund og en lang ved :00,
:05, :10 osv. Lydvalget er kun tilgængeligt, hvis systemet understøtter begge metoder.

**Lydudgang**

**Lydudgang** på fanen **Signal** vælger en enhed til de regelmæssige tidssignaler fra hver widget med lyd.
Widgetens tidszone, forskydning og interval ændres ikke. Valget af generator og signalets lydstyrke er fortsat
globale på fanen **Program**. Med Systembip er feltet deaktiveret og viser Windows-standardenheden. Den valgte
enhed gemmes og gendannes, når Indbygget generator vælges igen. Hvis Tidssignal aktivt slås fra, deaktiveres
både lydudgangens etiket og feltet, uden at valget slettes. Windows Vista bruger automatisk generatoren.

**Windows-standardenhed** følger den aktuelle standardudgang i Windows. En bestemt enhed forbliver valgt, hvis den
frakobles, og vises som **Enhed ikke tilgængelig**; dens signaler er tavse, indtil den er tilgængelig, eller en anden
udgang vælges. Enhedslisten opdateres, når den åbnes. Valget gemmes særskilt for hver widget i registreringsdatabasen
eller XML-indstillingerne.

Signaler flettes automatisk for hver udgang. En bestemt enhed og Windows-standardenhed, som peger på samme
enhed, deler én udgang. Forskellige enheder arbejder uafhængigt; sinuskurven, den sammenhængende fase samt
tonernes begyndelse og afslutning ved nul bevares. Lydudgang til test på fanen Program gemmer enheden til
generatortest og lydstyrkeprøver. Med Systembip er dette felt deaktiveret og viser Windows-standardenheden,
mens det gemte valg bevares. Alarmlyd og bippene før alarmen bruger Windows-standardudgangen. Kun bippene
flettes med regelmæssige tidssignaler på denne udgang.

Alarm og tidssignal kan også slås til eller fra i genvejsmenuen for widgets med lyd. Alarmens punkt viser tiden og aktive ugedage, medmindre alle er valgt. Slå lyd fra gælder widgeten og svarer til Lyd fra på Generelt. En selvstændig Kalender understøtter ikke alarm, tidssignal eller dæmpning. Global genaktivering gendanner kun de widgets, som blev gjort lydløse af forrige globale handling. Intern lyd fortsætter lydløst og bliver hørbar igen ved genaktivering. Et igangværende bip kan afsluttes; efterfølgende bip springes over, til lyden aktiveres. Andre kommandoer og fjernscripts påvirkes ikke.

## Indstillinger og menuer

Hver widgetmenu indeholder relevante kommandoer — synlighed, altid øverst, sekunder, analog størrelse eller
datokopiformat — efterfulgt af `Arranger i et gitter`, Tidsberegner, Indstillinger, Hjælp, Om og Afslut.
Meddelelsesområdets menu viser alle widgets med nummer, derefter Vis alle, Skjul alle og Slå al lyd fra. Det
særskilt grupperede `Arranger i et gitter` følger før programkommandoerne.

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

Brugerdefinerede kalenderskrifttyper understøttes med Windows' klassiske udseende, eller når temaer er slået fra for widgeten.

XML-import indlæser og gemmer straks indstillingerne i den valgte lagring uden at skifte type. Lydløs-tilstanden gemmes pr. widget med lyd.

## Kompilering

Krav:

- Microsoft Visual Studio med MSVC v145-værktøjssættet
- Windows SDK

Åbn `CalClock.slnx`, vælg `Release | x86`, og byg løsningen. Programfilen oprettes som:

```text
Release\CalClock.exe
```

Kun Win32/x86 understøttes. Projektet tilbyder bevidst ingen x64-konfiguration, fordi integrationen med Windows-urkontrollen kræver x86-kompatibilitet.

Kør `.\PackageRelease.ps1` efter kompilering for at oprette `CalClock-<version>-win32.zip` med programmet og dets
licens.

Standardværdier for signeringsparametre læses også fra Windows-brugerens miljøvariabler: `BUILD_SIGNER_NAME`,
`BUILD_CERTIFICATE_THUMBPRINT`, `BUILD_SIGNTOOL_PATH`, `BUILD_TIMESTAMP_SERVER`. Udtrykkelige kommandolinjeargumenter
har forrang.

## Licens

CalClock er tilgængeligt under [MIT-licensen](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
