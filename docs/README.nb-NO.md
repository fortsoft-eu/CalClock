# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · **Norsk** · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md)

CalClock er et Win32/x86-program for Windows Vista og nyere som viser flyttbare klokker og kalendere med uavhengige innstillinger på Windows-skrivebordet. Det kjører i systemstatusfeltet og trenger ikke et permanent kontrollvindu.

## Funksjoner

- Opptil 32 uavhengig konfigurerbare widgeter
- Eget språk, tidssone, tidsforskyvning, synlighet og alltid øverst-innstilling for hver widget
- Analoge klokker basert på Windows-kontrollen `ClockWndMain`, med automatisk gjenkjenning av tilgjengelige størrelser og støtte for sekundviser
- Digitale klokker med skrifter, farger, ugjennomsiktighet, innvendig avstand, rammer, valgfri innledende null og valgfri gjennomsiktig bakgrunn
- Innebygde Windows-kalendere med datovalg, fire rammestiler, justerbar rammefarge, ukenumre, valg av første ukedag og 33 kopieringsformater
- Kalender- og klokkepaneler med opptil to ekstra navngitte klokker i egne tidssoner, separate urskivestørrelser, fire rammestiler, justerbar farge, UTC-tekst, innledende null og egen skrift for hver tekstlinje
- Alarmer med ukedagsvalg, visuell varsling, intern lydavspilling, gjentakelse, lokale kommandoer og HTTP/HTTPS-skriptkall
- Tidssignaler per klokke hvert 1., 5., 10., 15., 20., 30. eller 60. minutt; samtidige signaler slås sammen til én sekvens
- Demp-kommando per klokke og en avkryssbar Demp alle-kommando i systemstatusfeltet
- Valgfri automatisk oppstart med Windows
- Valgfri festing innen fem piksler fra arbeidsområdets kanter ved draing, aktivert som standard; festingen beholdes når størrelsen endres
- NTP-synkronisering uten å endre Windows-systemklokken
- NTP-forvalg for Tsjekkia og Slovakia, PTB, Ubuntu/NTP Pool og egendefinerte servere
- Innstillinger i registeret eller XML, inkludert XML-import og -eksport
- Styring fra systemstatusfeltet med gjenoppretting av sist skjulte widgeter
- Identifisering av widgeter og stabil plassering i et rutenett uten overlapping
- Umiddelbar forhåndsvisning av utseendet med avbryting og standardutseende per widget
- Skrifter for program og widgeter, visuelle stiler og ClearType, GDI eller ingen skriftutjevning
- Grensesnitt på tsjekkisk, amerikansk, britisk og australsk engelsk, tysk, fransk, spansk, italiensk, portugisisk, polsk, slovakisk, dansk, finsk, islandsk, norsk, svensk og tyrkisk

## Widgettyper

| Widget | Beskrivelse |
| --- | --- |
| Analog klokke | Flyttbar Windows-urskive med størrelsene og den valgfrie sekundviseren som gjeldende Windows-versjon støtter |
| Digital klokke | Konfigurerbar flyttbar digital visning med valgfri UTC-tekst, innledende null, rammer og gjennomsiktig bakgrunn |
| Kalender | Flyttbar innebygd månedskalender med datovalg, justerbare rammer og kopieringsformater |
| Kalender med klokke | Kombinert panel med innebygd kalender, analog klokke, justerbare tekstlinjer, UTC-visning og rammer |
| Skjermklokke | Digital klokke som fyller én eller flere valgte skjermer, med valgfri mørklegging og UTC på egen linje |

Ved første oppstart velger CalClock språk etter Windows-visningsspråket og bruker amerikansk engelsk hvis språket ikke støttes. Én synlig analog klokke opprettes som standard. Hver widget beholder plassering og innstillinger mellom kjøringer. Mens Innstillinger er åpent, vises en skjermklokke alltid som en flyttbar forhåndsvisning med sideforholdet til den valgte skjermen. `Esc` skjuler skjermklokken og fjerner mørkleggingen også når Innstillinger er aktivt. Pekeren skjules etter kort inaktivitet over skjermklokker og mørklagte skjermer, og vises igjen ved musebevegelse. Den forblir synlig over den lille forhåndsvisningen i Innstillinger.

## Betjening

- Dra en klokke eller et panel med venstre museknapp.
- Dra en frittstående kalender fra et ledig område.
- Høyreklikk en widget eller ikonet i systemstatusfeltet for å åpne hurtigmenyen.
- Venstreklikk ikonet i systemstatusfeltet for å skjule synlige widgeter. Hvis alle er skjult, gjenoppretter neste klikk bare de sist skjulte.
- Dobbeltklikk en urskive for å slå sekundvisningen av eller på. I et kalenderpanel er det bare dobbeltklikk direkte på hovedurskiven som endrer sekundviseren. Ekstra klokker har ingen sekundviser.
- `F1` åpner Hjelp, `B` Innstillinger, `M` veksler Demp alle, og `Esc` skjuler en widget eller stopper en aktiv alarm.
- Dobbeltklikk en widget i Innstillinger for å vise den om nødvendig, velge `Synlig` og merke den kort på skrivebordet.
- Åpning av Innstillinger fra en widgets hurtigmeny velger denne widgeten umiddelbart.
- Bruk `Ctrl` eller `Shift` for flervalg, `Ctrl+A` for å velge alle og `Del` for å fjerne valgte. `Insert` veksler valget for gjeldende element og flytter listemarkøren til neste rad, som i Total Commander.
- Alle listesnarveier fungerer også når Fjern eller Dupliser har fokus. Snarveien flytter fokus til listen og utfører handlingen. `Ctrl+C` kopierer valgte widgeter, og `Ctrl+V` legger kopiene sist i listerekkefølge. Kopiene får alle innstillinger og et navnetillegg på programspråket. Dupliser utfører samme handling direkte. Maksimum er 32 widgeter. Hvis ikke alle kopiene får plass, legges de som får plass til i rekkefølge, og en melding varsler om resten.
- `Ctrl+A` eller trippelklikk i et tekstfelt velger all tekst.

Når flere widgeter er valgt, deaktiveres deres kontroller på Generelt, Utseende, Alarm og Signal, mens de globale fanene Tid og Program fortsatt er tilgjengelige. Innstillinger husker sist åpne fane og sist tilføyde widgettype. På små arbeidsområder får vinduet vannrett eller loddrett rulling etter behov.

Kalenderdatoer kan kopieres i 33 formater: lokale, sorterbare, med dag eller måned først, tekstbaserte og med ukedag. Alle masker finnes på alle grensesnittspråk. Standard kort lokalt format følger widgetspråket, og det gjør også måneds- og ukedagsnavn. Oppføringene viser masken og et oppdatert eksempel.

Et kalenderpanel kan vise opptil to ekstra klokker. Aktiver hver klokke på Generelt og velg navn og tidssone. Navngitte soner følger egne sommertidsregler; faste UTC-forskyvninger forblir faste. Når ekstra klokker er aktivert, viser hver klokke sin lokale ukedag under tiden. De tre størrelseslistene på Utseende styrer hovedklokken, Klokke 1 og Klokke 2 i denne rekkefølgen. Høyreklikk en ekstra urskive for å velge størrelse. Ekstra klokker utelater alltid sekunder og deler widgetens språk, tidsformat, skrifter og tidsforskyvning. Når klokker legges til, fjernes eller endrer størrelse, beholdes festingen til de samme arbeidsområdekantene.

I panelet er datoen øverst en lenke som flytter kalenderen til i dag, mens tidssoneteksten nederst åpner de klassiske innstillingene for dato og klokkeslett i Windows. Begge lenkene kan nås med `Tab`, viser fokusramme og aktiveres fra tastaturet. Den innebygde kalenderen er fortsatt fullt interaktiv, men utelater den overflødige I dag-raden i denne kombinasjonen.

`Plasser i rutenett` ordner synlige skrivebordswidgeter i et stabilt rutenett uten overlapping og beholder omtrent den manuelle plasseringen. Widgeten som startet kommandoen fra sin meny, blir stående; kommandoen fra systemstatusfeltet ordner hver skjerm separat. Skjermklokker holdes utenfor.

## Utseende

For frittstående kalendere styrer **I dag-rad** i menyen eller på Utseende den nederste raden. Valget er på som standard; fjern merket for å skjule raden og redusere kalenderen. Innstillingen lagres per widget. **Gå til i dag** er fortsatt tilgjengelig og går tilbake til månedsvisningen. Når datoen endres etter widgetens egen tid, velger kalenderen i dag automatisk uten å endre gjeldende visning.

Utseendeendringer forhåndsvises straks på valgt widget. `Avbryt` gjenoppretter endringer som ikke er tatt i bruk; `Standardutseende` gjenoppretter standardene for widgettypen.

Digitale klokker, kalendere og kombinerte paneler deler fire rammestiler. Den enkle rammen har justerbar farge; rammebredde kan endres der widgeten støtter det. Gjennomsiktige digitale klokker tilbyr de samme stilene som ugjennomsiktige. Skriftdialoger viser bare relevante valg og utelater ubrukt forhåndsvisning og effekter. Program- og kalenderskrifter utelater størrelse, mens digitale klokker og paneltekster inkluderer den. En innebygd kalender bruker egendefinert skrift bare når visuelle stiler er deaktivert for kalenderen eller hele programmet.

Programspråk, grensesnittskrift, skriftutjevning, visuelle stiler, lagring, Windows-oppstart og kantfesting er globale valg på Program. Tidskilden er også global. Widgetspråk, utjevning, stiler, tidssone, forskyvning, alarm og tidssignal stilles inn uavhengig. Når nytt programspråk tas i bruk, bygges det åpne Innstillinger-vinduet straks opp på dette språket. Skriftutjevning tilbyr **ClearType**, **GDI** og **Ingen**. På Utseende står utjevning og deaktivering av temaer på samme sted for alle typer, med **Standardutseende** under.

**Lydvolum** på Alarm styrer internt avspilte lydfiler separat for hver widget og viser nivået i dB. Standardverdien **−18 dB** bevarer filens opprinnelige nivå (**100%**). Mot høyre forsterkes lyden; maksimum **0 dB** er omtrent **794%** av opprinnelig amplitude. Helt til venstre er **−∞ dB** (stillhet). Endringer virker under lydtesten. Glidebryteren er deaktivert for filer åpnet i eksterne programmer. Forsterkning gjelder dekodet lyd, inkludert WAV, MP3, WMA, AAC, M4A og FLAC når Windows støtter dem. Eldre avspilling av filer som ikke kan dekodes, for eksempel MIDI, er begrenset til 100%.

Alarmens ukedager følger første ukedag i valgt programkultur. Lagrede dager beholder betydningen ved språkbytte. Aktivering fra widgetmenyen uten valgte ukedager åpner widgetens Alarm-fane i stedet for å aktivere en alarm som ikke kan ringe.

Standard rammebredde for digitale klokker er null. **Innledende null** tilbyr **Vis** (standard), **Behold plass** og **Uten plass**. **Behold plass** skjuler nullen og reserverer den faktiske bredden i valgt skrift, slik at øvrige sifre beholder plasseringen også med proporsjonale skrifter. Flyttbare digitale klokker venstrejusterer tiden og beholder en fast størrelse mens tiden går. Skjermklokker sentrerer et fast tidsområde tilpasset skrift og format, med plass til to timesifre. Tidsendringer sentrerer eller skalerer ikke teksten på nytt. AM/PM- eller UTC-linjen er sentrert uavhengig. Skjermklokker bruker hvit tekst på svart bakgrunn som standard.

## Tid og alarmer

Digitale klokker, kalenderpaneler og skjermklokker tilbyr **Etter språk**, **12 timer** og **24 timer** under **Tidsformat** på Generelt. **Etter språk** er standarden: amerikansk og australsk engelsk bruker for eksempel 12 timer, britisk engelsk 24. Et manuelt valg beholdes når widgetspråket endres. Skilletegn og AM/PM-markører følger kulturen; kulturer uten egne markører bruker **AM/PM** i 12-timersmodus.

**AM/PM** er merket som standard. Fjernes merket, skjules markøren uten å endre 12-timerssyklusen. Valget er deaktivert i 24-timersmodus og for widgeter uten digital tid. Skjermklokker viser markøren på egen linje under tiden, som UTC. **UTC bruker alltid 24 timer**; syklus og AM/PM deaktiveres ved UTC, men verdiene beholdes for retur til lokal tid. Valget for innledende null bestemmer fortsatt om den vises, skjules med reservert plass eller utelates.

Navngitte tidssoner viser stedets sivile tid og følger automatisk stedets sommertidsregler. Forskyvningen ved navnet gjelder dagens dato og oppdateres når listen åpnes. Egne **UTC**-oppføringer gir faste forskyvninger fra **UTC−12:00** til **UTC+14:00** i trinn på 15 minutter, uten sommertid. Velg lokal sone, en annen navngitt sone eller fast UTC-forskyvning uavhengig for hver widget.

Hver widget kan bruke en hvilken som helst Windows-tidssone og en forskyvning med fortegn i formen `[-]HH:mm:ss.ff`. Kompakt inndata tolkes fra høyre, med sekunder først.

Forskyvning er nyttig i kringkastingsstudioer, for eksempel for å kompensere for forsinkelse i overføringskjeden. Ved å stille studioklokken foran med målt forsinkelse når tidssignalet lytterne til riktig tidspunkt.

CalClock kan bruke Windows-systemtid eller en programintern korreksjon fra NTP-servere. Valget gjelder alle widgeter. Synkronisering endrer aldri Windows-klokken. Hvis NTP-forbindelsen mistes etter en vellykket synkronisering, forblir siste korreksjon aktiv i prosessminnet. Serverbytte beholder også gyldig korreksjon til et nytt svar mottas.

Klokkewidgeter støtter alarmer på individuelt valgte ukedager; alle sju er aktive som standard. En alarm viser sin skjulte widget og bringer den foran andre vinduer uten å endre alltid øverst permanent. WAV, MP3, WMA, MIDI, AAC, M4A og FLAC gjenkjennes for intern engangsavspilling eller gjentakelse; faktisk dekoding avhenger av installerte Windows-mediekomponenter. Andre filer og kommandoer sendes asynkront til Windows. En alarm kan også kalle en HTTP- eller HTTPS-adresse. Uavhengig av dette kan den bruke seks-toners tidssignalet, der første korte tone kommer fem sekunder før alarmtiden.

Kjør fil eller kommando aktiverer feltet, Bla gjennom, Test og gjentakelse. Test og gjentakelse krever også et ikke-tomt felt, men en aktiv test kan alltid stoppes. Test viser den visuelle indikasjonen og tester fil, kommando, lyd og ekstern skriptadresse asynkront. Hvis alarmens tidssignal er valgt, spilles også hele sekvensen med seks toner; Stopp test avslutter intern lyd og signalforhåndsvisning.

Signal-fanen kan deaktivere tidssignaler eller planlegge dem hvert 1., 5., 10., 15., 20., 30. eller 60. minutt etter widgetens viste tid. 20-minuttersintervallet gir signal ved :00, :20 og :40. Mønsteret er **Greenwich Time Signal (GTS)**: fem korte toner markerer de siste fem sekundene og én lengre den nøyaktige grensen. Tidssoner, UTC, forskyvninger og gjeldende NTP-korreksjon tas med. Alarmens signal og Signal-fanen er uavhengige; hvis tidspunkter sammenfaller, spiller CalClock én felles sekvens. Forskyvninger på deler av sekunder tas med, og overlappende widget-, alarm- og testtoner fortsetter uten avbrudd til siste overlapping er ferdig.

**Tidssignallyd** på Program tilbyr **Innebygd generator** (standard) og **Systempip**. Valget gjelder alle tidssignaler, også alarmene, og lagres globalt. For **Innebygd generator** viser **Tidssignalvolum** nivået i dB for hele programmet. Høyre endepunkt er **0 dB**, maksimal uforvrengt sinusamplitude; stillhet er **−∞ dB**. Standardvolumet er **−18 dB**. Desibelskalaen har −18 dB i midten. Generatoren starter og slutter toner ved nullgjennomgang, også når en test stoppes. Pågående tone får avsluttes; en lang tone kan bruke opptil et halvt sekund. **Test** ved **Tidssignallyd** starter kontinuerlig forhåndsvisning; **Stopp test** avslutter den. Begge lydmåter kan testes, og testtilstanden lagres ikke. Å holde volumglidebryteren nede starter også forhåndsvisning til musen slippes, med mindre knappetesten kjører. Avspilling begynner på neste hele sekund, med korte toner hvert sekund og en lang ved :00, :05, :10 osv. Forhåndsvisning og samtidige widget- eller alarmsignaler deler én tone. For **Systempip** er bare volumglidebryteren deaktivert. Lydvalget er bare tilgjengelig hvis systemet støtter begge metodene.

Alarm og tidssignal kan også slås av eller på i hurtigmenyen til widgeter med lyd. Alarmoppføringen viser tiden og aktive ukedager hvis ikke alle er valgt. Demp gjelder widgeten og gjenspeiles på Generelt. En frittstående Kalender har verken alarm, tidssignal eller dempet tilstand, så disse kommandoene utelates eller deaktiveres. I systemstatusfeltet heter kommandoen Demp alle; `M` på en widget gjør samme globale endring. Global oppheving gjenoppretter bare widgeter dempet av forrige globale handling. Intern lyd fortsetter lydløst og blir hørbar igjen når dempingen oppheves. En pågående tone kan fullføres; senere toner hoppes over til lyden aktiveres. Andre kommandoer og eksterne skript påvirkes ikke.

## Innstillinger og menyer

`Lagre` bruker endringene og lukker Innstillinger; `Bruk` bruker dem uten å lukke; `Avbryt` forkaster endringer som ikke er tatt i bruk, også utseendeforhåndsvisningen. Enter aktiverer `Lagre`, Esc `Avbryt`.

Hver widgetmeny inneholder relevante kommandoer — synlighet, alltid øverst, sekunder, analog størrelse eller datokopieringsformat — etterfulgt av `Plasser i rutenett`, Innstillinger, Hjelp, Om og Avslutt. Systemstatusmenyen viser alle widgeter med nummer, deretter Vis alle, Skjul alle og Demp alle. Den separat grupperte `Plasser i rutenett` følger før programkommandoene.

Visning eller gjenoppretting bringer widgeter foran andre vinduer uten å endre alltid øverst. CalClock sørger for minst én synlig widget etter oppstart. En ny oppstart aktiverer eksisterende instans og gjenoppretter sist skjulte widgeter hvis ingen er synlige. Ikonet registreres automatisk på nytt når Windows Utforsker starter på nytt. Hvis `ClockWndMain` ikke støtter sekundviser i valgt størrelse, deaktiveres Sekunder, men valget beholdes for en annen støttet størrelse.

## Lagring av innstillinger

Innstillingene lagres som standard under:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

XML-lagring kan aktiveres i Innstillinger og bruker:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Etter vellykket XML-lagring fjerner CalClock sin programtilstand fra registeret. Bytte tilbake fjerner tilsvarende den automatiske XML-filen og tomme CalClock-mapper. Import av XML laster og lagrer innstillingene straks i valgt lagringsmåte uten å bytte type. Demping lagres per widget med lyd. Oppstart med Windows lagres som verdien `CalClock` i den vanlige Windows-nøkkelen `Run` for gjeldende bruker.

## Bygging

Krav:

- Microsoft Visual Studio med MSVC v145-verktøysettet
- Windows SDK

Åpne `CalClock.slnx`, velg `Release | Win32` og bygg løsningen. Programfilen opprettes som:

```text
Release\CalClock.exe
```

Bare Win32/x86 støttes. Prosjektet tilbyr med hensikt ingen x64-konfigurasjon fordi integrasjonen med Windows-klokkekontrollen krever x86-kompatibilitet.

## Lisens

CalClock er tilgjengelig under [MIT-lisensen](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
