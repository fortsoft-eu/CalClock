# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · **Norsk (bokmål)** · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock er et Win32/x86-program for Windows Vista og nyere som viser flyttbare klokker og kalendere med uavhengige innstillinger på Windows-skrivebordet. Det kjører i systemstatusfeltet og trenger ikke et permanent kontrollvindu.

## Funksjoner

- Opptil 32 uavhengig konfigurerbare widgeter
- Eget språk, tidssone, tidsforskyvning, synlighet og alltid øverst-innstilling for hver widget
- Analoge klokker med valgbare urskivestørrelser og valgfri sekundviser
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
- Grensesnitt på 36 språkvarianter, med uavhengig språkvalg for programmet og hver widget

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
- Trykk `Alt+0`, `Alt+1`, `Alt+2` eller `Alt+3` på Analog klokke eller Kalender med klokke for å velge størrelsen på hovedurskiven, fra minst til størst.
- Dobbeltklikk en widget i Innstillinger for å vise den om nødvendig, velge `Synlig` og merke den kort på skrivebordet.
- Åpning av Innstillinger fra en widgets hurtigmeny velger denne widgeten umiddelbart.
- Delete fjerner valgte widgeter. `Insert` veksler markeringen av gjeldende oppføring og flytter listepekeren én rad ned.
- `Ctrl+C` kopierer valgte widgeter, og `Ctrl+V` legger kopiene sist i listerekkefølge. Kopiene får alle innstillinger og et navnetillegg på programspråket. Dupliser utfører samme handling direkte. Maksimum er 32 widgeter. Hvis ikke alle kopiene får plass, legges de som får plass til i rekkefølge, og en melding varsler om resten.

Når innstillingene åpnes fra ikonet i systemstatusfeltet, velges den sist valgte widgeten igjen.

Innstillinger husker sist åpne fane og sist tilføyde widgettype.

Kalenderdatoer kan kopieres i 33 formater: lokale, sorterbare, med dag eller måned først, tekstbaserte og med ukedag. Alle masker finnes på alle grensesnittspråk. Standard kort lokalt format følger widgetspråket, og det gjør også måneds- og ukedagsnavn. Oppføringene viser masken og et oppdatert eksempel.

Et kalenderpanel kan vise opptil to ekstra klokker. Aktiver hver klokke på Generelt og velg navn og tidssone. Navngitte soner følger egne sommertidsregler; faste UTC-forskyvninger forblir faste. Når ekstra klokker er aktivert, viser hver klokke sin lokale ukedag under tiden. De tre størrelseslistene på Utseende styrer hovedklokken, Klokke 1 og Klokke 2 i denne rekkefølgen. Høyreklikk en ekstra urskive for å velge størrelse. Ekstra klokker utelater alltid sekunder og deler widgetens språk, tidsformat, skrifter og tidsforskyvning. Når klokker legges til, fjernes eller endrer størrelse, beholdes festingen til de samme arbeidsområdekantene.

I panelet er datoen øverst en lenke som flytter kalenderen til i dag, mens tidssoneteksten nederst åpner de klassiske innstillingene for dato og klokkeslett i Windows.

`Plasser i rutenett` ordner synlige skrivebordswidgeter i et stabilt rutenett uten overlapping og beholder omtrent den manuelle plasseringen. Widgeten som startet kommandoen fra sin meny, blir stående; kommandoen fra systemstatusfeltet ordner hver skjerm separat. Skjermklokker holdes utenfor.

## Utseende

For frittstående kalendere styrer **I dag-raden** i menyen eller på Utseende den nederste raden. Valget er på som standard; fjern merket for å skjule raden og redusere kalenderen. Innstillingen lagres per widget. **Gå til i dag** er fortsatt tilgjengelig og går tilbake til månedsvisningen. Når datoen endres etter widgetens egen tid, velger kalenderen i dag automatisk uten å endre gjeldende visning.

Utseendeendringer forhåndsvises straks på valgt widget. `Avbryt` forkaster endringer som ikke er tatt i bruk; `Standardutseende` gjenoppretter standardene for widgettypen.

Digitale klokker, kalendere og kombinerte paneler deler fire rammestiler. Den enkle rammen har justerbar farge; rammebredde kan endres der widgeten støtter det. Gjennomsiktige digitale klokker tilbyr de samme stilene som ugjennomsiktige. Program- og kalenderskrifter utelater størrelse, mens digitale klokker og paneltekster inkluderer den. En frittstående Kalender støtter ikke alarm, tidssignal eller demping.

Programspråk, grensesnittskrift, skriftutjevning, visuelle stiler, lagring, Windows-oppstart og kantfesting er globale valg på Program. Tidskilden er også global. Widgetspråk, utjevning, stiler, tidssone, forskyvning, alarm og tidssignal stilles inn uavhengig. Skriftutjevning tilbyr **ClearType**, **GDI** og **Ingen**.

**Lydvolum** på Alarm styrer internt avspilte lydfiler separat for hver widget og viser nivået i dB. Standardverdien **−18 dB** bevarer filens opprinnelige nivå (**100%**). Mot høyre forsterkes lyden; maksimum **0 dB** er omtrent **794%** av opprinnelig amplitude. Helt til venstre er **−∞ dB** (stillhet). Endringer virker under lydtesten. Forsterkning gjelder dekodet lyd, inkludert WAV, MP3, WMA, AAC, M4A og FLAC når Windows støtter dem. Eldre avspilling av filer som ikke kan dekodes, for eksempel MIDI, er begrenset til 100%.

Alarmens ukedager følger første ukedag i valgt programkultur. Lagrede dager beholder betydningen ved språkbytte. Aktivering fra widgetmenyen uten valgte ukedager åpner widgetens Alarm-fane i stedet for å aktivere en alarm som ikke kan ringe.

**Innledende null** tilbyr **Ja** (standard), **Nei, behold plass** og **Nei, uten plass**. **Nei, behold plass** skjuler nullen og reserverer den faktiske bredden i valgt skrift, slik at øvrige sifre beholder plasseringen også med proporsjonale skrifter. Skjermklokker bruker hvit tekst på svart bakgrunn som standard.

## Tid og alarmer

Digitale klokker, kalenderpaneler og skjermklokker tilbyr **Etter språk**, **12 timer** og **24 timer** under **Tidsformat** på Generelt. **Etter språk** er standarden: amerikansk og australsk engelsk bruker for eksempel 12 timer, britisk engelsk 24. Et manuelt valg beholdes når widgetspråket endres. Skilletegn og AM/PM-markører følger kulturen; kulturer uten egne markører bruker **AM/PM** i 12-timersmodus.

**AM/PM** er merket som standard. Fjernes merket, skjules markøren uten å endre 12-timerssyklusen. Skjermklokker viser markøren på egen linje under tiden, som UTC. UTC bruker alltid 24-timersformat. Valget for innledende null bestemmer fortsatt om den vises, skjules med reservert plass eller utelates.

Navngitte tidssoner viser stedets sivile tid og følger automatisk stedets sommertidsregler. Forskyvningen ved navnet gjelder dagens dato og oppdateres når listen åpnes. Egne **UTC**-oppføringer gir faste forskyvninger fra **UTC−12:00** til **UTC+14:00** i trinn på 15 minutter, uten sommertid. Velg lokal sone, en annen navngitt sone eller fast UTC-forskyvning uavhengig for hver widget.

Nye widgeter bruker som standard **Gjeldende tidssone i Windows**, som følger gjeldende Windows-tidssone og innstillingen for automatisk sommertid. Eksisterende widgeter beholder sine valgte soner. Valget bestemmer tidssonen; den felles tidskilden Windows eller NTP er uavhengig av dette.

Hver widget kan bruke en hvilken som helst Windows-tidssone og en forskyvning med fortegn i formen `[-]HH:mm:ss.ff`. Kompakt inndata tolkes fra høyre, med sekunder først.

Forskyvning er nyttig i kringkastingsstudioer, for eksempel for å kompensere for forsinkelse i overføringskjeden. Ved å stille studioklokken foran med målt forsinkelse når tidssignalet lytterne til riktig tidspunkt.

Widgetens forskyvning brukes på UTC før omregning til tidssonen og forskyver derfor også tidspunktet for overgang til eller fra sommertid. En klokke som går ti sekunder foran, skifter ti sekunder tidligere; en klokke som går ti sekunder etter, skifter ti sekunder senere. Visere, digital visning, kalenderdatoer, alarmer og tidssignaler bruker den beregnede tiden.

Fanen Tid velger Windows-tid eller NTP-servere for hele programmet. NTP korrigerer bare CalClock og endrer aldri Windows. NTP er standard; det automatiske settet velger servere etter region og filtrerer målinger etter forsinkelse og avvik.

Etter synkronisering går CalClock-klokken videre uavhengig av senere endringer i systemtiden i Windows. Hvis forbindelsen brytes eller serverne endres, fortsetter klokken fra siste gyldige synkronisering til et nytt svar mottas; denne tilstanden beholdes til programmet avsluttes.

Fanen Tid registrerer NTP-serverforespørsler siden programmet startet. Hver oppføring inneholder dato og lokal datamaskintid, server og status. OK angir et gyldig svar, og θ viser tidsavviket fra Windows-systemtiden. ERR angir årsaken til feilen og en eventuell feilkode. Den siste oppføringen i en forespørselsgruppe viser også det beregnede tidsavviket Θ når brukbare målinger er tilgjengelige.

Tidsavvik vises i millisekunder med fire desimaler. En positiv verdi betyr at serverklokken går foran Windows; en negativ verdi betyr at den går etter. Θ tar hensyn til de godkjente målingene og vises også i synkroniseringsstatusen.

Lagre logg eksporterer oppføringene til CSV, inkludert tidsavvik og feildetaljer. Oppføringer beholdes ikke mellom programøkter; lagre dem før du avslutter hvis du vil beholde dem.

Klokkewidgeter støtter alarmer på individuelt valgte ukedager; alle sju er aktive som standard. En alarm viser sin skjulte widget og bringer den foran andre vinduer uten å endre alltid øverst permanent. WAV, MP3, WMA, MIDI, AAC, M4A og FLAC gjenkjennes for intern engangsavspilling eller gjentakelse; faktisk dekoding avhenger av installerte Windows-mediekomponenter. Andre filer og kommandoer sendes asynkront til Windows. En alarm kan også kalle en HTTP- eller HTTPS-adresse. Uavhengig av dette kan den bruke seks-toners tidssignalet, der første korte tone kommer fem sekunder før alarmtiden.

Alarmtonene planlegges ut fra det faktiske tidspunktet for neste alarm etter tidssoneomregning og widgetforskyvning. De begynner fem faktiske sekunder før dette tidspunktet, også når klokken hopper direkte til alarmtiden. En alarmtid som hoppes over om våren, utløser verken alarm eller toner. I den gjentatte timen om høsten utløses alarmen og tonene bare én gang for samme dato og innstilte klokkeslett.

Test viser den visuelle indikasjonen og tester fil, kommando, lyd og ekstern skriptadresse asynkront. Hvis alarmens tidssignal er valgt, spilles også hele sekvensen med seks toner; Stopp test avslutter intern lyd og signalforhåndsvisning.

Signal-fanen har avkrysningsboksen Tidssignal aktivt og alternativknapper for intervaller på 1, 5, 10, 15, 20, 30 eller 60 minutter etter widgetens viste tid. Signalet er først slått av, med et intervall på én time valgt. Å slå Signal av og på i widgetmenyen beholder intervallet. Menyen viser alarmtid og signalintervall i parentes. eller 60. minutt etter widgetens viste tid. 20-minuttersintervallet gir signal ved :00, :20 og :40. Mønsteret er **Greenwich Time Signal (GTS)**: fem korte toner markerer de siste fem sekundene og én lengre den nøyaktige grensen. Tidssoner, UTC, forskyvninger og gjeldende NTP-korreksjon tas med. Alarmens signal og Signal-fanen er uavhengige; hvis tidspunkter sammenfaller, spiller CalClock én felles sekvens. Forskyvninger på deler av sekunder tas med, og overlappende widget-, alarm- og testtoner fortsetter uten avbrudd til siste overlapping er ferdig.

**Lyd for tidssignal** på Program tilbyr **Innebygd generator** (standard) og **Systempip**. Valget gjelder alle tidssignaler, også alarmene, og lagres globalt. For **Innebygd generator** viser **Volum for tidssignal** nivået i dB for hele programmet. Høyre endepunkt er **0 dB**, maksimal uforvrengt sinusamplitude; stillhet er **−∞ dB**. Standardvolumet er **−18 dB**. Desibelskalaen har −18 dB i midten. Pågående tone får avsluttes; en lang tone kan bruke opptil et halvt sekund. **Test** ved **Lyd for tidssignal** starter kontinuerlig forhåndsvisning; **Stopp test** avslutter den. Begge lydmåter kan testes, og testtilstanden lagres ikke. Å holde volumglidebryteren nede starter også forhåndsvisning til musen slippes, med mindre knappetesten kjører. Avspilling begynner på neste hele sekund, med korte toner hvert sekund og en lang ved :00, :05, :10 osv. Forhåndsvisning og samtidige widget- eller alarmsignaler deler én tone. Lydvalget er bare tilgjengelig hvis systemet støtter begge metodene.

Alarm og tidssignal kan også slås av eller på i hurtigmenyen til widgeter med lyd. Alarmoppføringen viser tiden og aktive ukedager hvis ikke alle er valgt. Demp gjelder widgeten og gjenspeiles på Generelt. En frittstående Kalender støtter ikke alarm, tidssignal eller demping. I systemstatusfeltet heter kommandoen Demp alle; `M` på en widget gjør samme globale endring. Global oppheving gjenoppretter bare widgeter dempet av forrige globale handling. Intern lyd fortsetter lydløst og blir hørbar igjen når dempingen oppheves. En pågående tone kan fullføres; senere toner hoppes over til lyden aktiveres. Andre kommandoer og eksterne skript påvirkes ikke.

## Innstillinger og menyer

Hver widgetmeny inneholder relevante kommandoer — synlighet, alltid øverst, sekunder, analog størrelse eller datokopieringsformat — etterfulgt av `Plasser i rutenett`, Innstillinger, Hjelp, Om og Avslutt. Systemstatusmenyen viser alle widgeter med nummer, deretter Vis alle, Skjul alle og Demp alle. Den separat grupperte `Plasser i rutenett` følger før programkommandoene.

Visning eller gjenoppretting bringer widgeter foran andre vinduer uten å endre alltid øverst. CalClock sørger for minst én synlig widget etter oppstart. En ny oppstart aktiverer eksisterende instans og gjenoppretter sist skjulte widgeter hvis ingen er synlige. Ikonet registreres automatisk på nytt når Windows Utforsker starter på nytt.

## Lagring av innstillinger

Innstillingene lagres som standard under:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

XML-lagring kan aktiveres i Innstillinger og bruker:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Egendefinerte kalenderskrifter støttes med klassisk Windows-utseende eller når temaer er deaktivert for programmet eller widgeten.

Import av XML laster og lagrer innstillingene straks i valgt lagringsmåte uten å bytte type. Demping lagres per widget med lyd.

## Bygging

Krav:

- Microsoft Visual Studio med MSVC v145-verktøysettet
- Windows SDK

Åpne `CalClock.slnx`, velg `Release | x86` og bygg løsningen. Programfilen opprettes som:

```text
Release\CalClock.exe
```

Bare Win32/x86 støttes. Prosjektet tilbyr med hensikt ingen x64-konfigurasjon fordi integrasjonen med Windows-klokkekontrollen krever x86-kompatibilitet.

## Lisens

CalClock er tilgjengelig under [MIT-lisensen](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
