# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk](README.nb-NO.md) · **Svenska** · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md)

CalClock är ett nativt Win32/x86-program för Windows Vista och senare som visar fritt placerbara klockor och kalendrar med oberoende inställningar på Windows-skrivbordet. Det körs i meddelandefältet och kräver inget permanent kontrollfönster.

## Funktioner

- Upp till 32 widgetar med oberoende inställningar
- Eget språk, tidszon, tidsförskjutning, synlighet och läge alltid överst för varje widget
- Analoga klockor baserade på Windows-kontrollen `ClockWndMain`, med automatisk identifiering av tillgängliga storlekar och stöd för sekundvisare
- Digitala klockor med teckensnitt, färger, opacitet, inre marginaler, ramar, valfri inledande nolla och genomskinlig bakgrund
- Inbyggda Windows-kalendrar med datumval, fyra ramstilar, justerbar ramfärg, veckonummer, val av första veckodag och 33 kopieringsformat
- Kalender- och klockpaneler med upp till två extra namngivna klockor i egna tidszoner, separata urtavlestorlekar, fyra ramstilar, justerbar färg, UTC-text, inledande nolla och eget teckensnitt för varje textrad
- Alarm med veckodagsval, visuell indikering, intern ljuduppspelning, upprepning, lokala kommandon och HTTP/HTTPS-skriptanrop
- Tidssignaler per klocka med intervall på 1, 5, 10, 15, 20, 30 eller 60 minuter; samtidiga signaler slås ihop till en sekvens
- Tyst-kommando per klocka och ett markerbart Tysta alla-kommando i meddelandefältet
- Valfri automatisk start med Windows
- Valfri fästning vid arbetsytans kanter inom fem bildpunkter under dragning, aktiverad som standard; kantfästningen bevaras när storleken ändras
- NTP-synkronisering utan att ändra Windows-systemklockan
- NTP-förval för Tjeckien och Slovakien, PTB, Ubuntu/NTP Pool eller egna servrar
- Inställningar i registret eller XML, med XML-import och -export
- Styrning via meddelandefältet med återställning av senast dolda widgetar
- Identifiering av widgetar och stabil placering i ett rutnät utan överlappning
- Direkt förhandsvisning av utseendet med möjlighet att avbryta och återställa standardutseendet per widget
- Teckensnitt för program och widgetar, visuella format och ClearType, GDI eller ingen teckensnittsutjämning
- Gränssnitt på tjeckiska, amerikansk, brittisk och australisk engelska, tyska, franska, spanska, italienska, portugisiska, polska, slovakiska, danska, finska, isländska, norska, svenska och turkiska

## Widgettyper

| Widget | Beskrivning |
| --- | --- |
| Analog klocka | Fritt placerbar Windows-urtavla med de storlekar och den valfria sekundvisare som den aktuella Windows-versionen erbjuder |
| Digital klocka | Inställbar digital visning med valfri UTC-text, inledande nolla, ramar och genomskinlig bakgrund |
| Kalender | Flyttbar inbyggd månadskalender med datumval, justerbara ramar och kopieringsformat |
| Kalender med klocka | Kombinerad panel med inbyggd kalender, analog klocka, inställbara textrader, UTC-visning och ramar |
| Skärmklocka | Digital klocka som fyller en eller flera valda skärmar, med valfri mörkläggning och UTC på en egen rad |

Vid första starten väljer CalClock språk efter Windows visningsspråk och använder amerikansk engelska om språket inte stöds. En synlig analog klocka skapas som standard. Varje widget behåller position och inställningar mellan körningarna. När Inställningar är öppet representeras en skärmklocka alltid av en flyttbar förhandsvisning med den valda skärmens proportioner. `Esc` döljer skärmklockan och tar bort mörkläggningen även när Inställningar är aktivt. Pekaren döljs efter kort inaktivitet över skärmklockor och mörklagda skärmar och visas igen när musen rör sig. Den förblir synlig över den lilla förhandsvisningen i Inställningar.

## Användning

- Dra en klocka eller panel med vänster musknapp.
- Dra en fristående kalender från ett ledigt område.
- Högerklicka en widget eller ikonen i meddelandefältet för att öppna snabbmenyn.
- Vänsterklicka ikonen i meddelandefältet för att dölja synliga widgetar. Om alla är dolda återställer nästa klick endast de senast dolda.
- Dubbelklicka en urtavla för att växla sekundvisningen. I en kalenderpanel ändras sekundvisaren endast genom dubbelklick direkt på huvudurtavlan. Extra klockor har ingen sekundvisare.
- `F1` öppnar Hjälp, `B` Inställningar, `M` växlar Tysta alla och `Esc` döljer en widget eller stoppar ett aktivt alarm.
- Dubbelklicka en widget i Inställningar för att visa den vid behov, markera `Synlig` och kort identifiera den på skrivbordet.
- Öppna Inställningar från en widgets snabbmeny för att välja den direkt.
- Använd `Ctrl` eller `Shift` för flerval, `Ctrl+A` för att välja alla och `Del` för att ta bort valda. `Insert` växlar markeringen för aktuell post och flyttar listmarkören till nästa rad, som i Total Commander.
- Alla listans kortkommandon fungerar även när Ta bort eller Duplicera har fokus. Kortkommandot flyttar fokus till listan och utför åtgärden. `Ctrl+C` kopierar valda widgetar och `Ctrl+V` lägger kopiorna sist i listordning. Kopiorna innehåller alla inställningar och får ett namntillägg på programspråket. Duplicera utför samma åtgärd direkt. Högst 32 widgetar tillåts. Om alla kopior inte får plats läggs de som ryms till i ordning och ett meddelande visas för resten.
- `Ctrl+A` eller trippelklick i ett textfält markerar all text.

När flera widgetar är valda inaktiveras deras kontroller på Allmänt, Utseende, Alarm och Signal; de globala flikarna Tid och Program är fortfarande tillgängliga. Inställningar kommer ihåg senast öppna flik och senast tillagda widgettyp. På en liten arbetsyta får fönstret vågrät eller lodrät rullning efter behov.

Kalenderdatum kan kopieras i 33 format: lokala, sorterbara, med dag eller månad först, textbaserade och med veckodag. Alla masker finns på alla gränssnittsspråk. Det korta lokala standardformatet följer widgetens språk, liksom månads- och veckodagsnamn. Posterna visar masken och ett aktuellt exempel.

En kalenderpanel kan visa upp till två extra klockor. Aktivera varje klocka på Allmänt och välj namn och tidszon. Namngivna zoner följer sina egna sommartidsregler; fasta UTC-förskjutningar förblir fasta. När extra klockor är aktiva visar varje klocka sin lokala veckodag under tiden. De tre storlekslistorna på Utseende styr huvudklockan, Klocka 1 och Klocka 2 i den ordningen. Högerklicka en extra urtavla för att välja storlek. Extra klockor utelämnar alltid sekunder och delar widgetens språk, tidsformat, teckensnitt och tidsförskjutning. När klockor läggs till, tas bort eller ändrar storlek bevaras fästningen vid samma kanter på arbetsytan.

I panelen är datumet överst en länk som återför kalendern till idag. Tidszonstexten nederst öppnar de klassiska inställningarna för Datum och tid i Windows. Båda länkarna nås med `Tab`, visar en fokusrektangel och kan aktiveras med tangentbordet. Den inbyggda kalendern är fortfarande helt interaktiv men utelämnar den överflödiga Idag-raden i den kombinerade layouten.

`Ordna i rutnät` placerar synliga skrivbordswidgetar i ett stabilt rutnät utan överlappning och bevarar ungefär den manuella placeringen. Widgeten vars meny startade kommandot stannar på plats; kommandot i meddelandefältet ordnar varje skärm oberoende. Skärmklockor undantas.

## Utseende

För fristående kalendrar styr **Idag-rad** i menyn eller på Utseende den nedersta raden. Den är markerad som standard; avmarkera för att dölja raden och minska kalendern. Valet sparas separat per widget. **Gå till idag** finns kvar i menyn och återgår till månadsvyn. När datumet ändras enligt widgetens tid väljer kalendern idag automatiskt och behåller sin aktuella vy.

Utseendeändringar förhandsvisas direkt på vald widget. `Avbryt` återställer ändringar som inte verkställts; `Standardutseende` återställer värdena för widgettypen.

Digitala klockor, kalendrar och kombinerade paneler delar fyra ramstilar. Enkelramen har justerbar färg; rambredden kan ändras där widgeten stöder det. Genomskinliga digitala klockor har samma stilval som ogenomskinliga. Teckensnittsdialoger visar endast användbara val och utelämnar oanvänd förhandsvisning och effekter. Program- och kalenderteckensnitt saknar storleksval, medan digitala klockor och paneltexter har det. En inbyggd kalender använder eget teckensnitt bara när visuella format är avstängda för kalendern eller hela programmet.

Programspråk, gränssnittsteckensnitt, utjämning, visuella format, lagring, Windows-start och kantfästning är globala och ställs in på Program. Tidskällan är också global. Widgetspråk, utjämning, format, tidszon, förskjutning, alarm och tidssignal ställs in separat. Ett nytt programspråk återskapar omedelbart det öppna Inställningar-fönstret på det språket. Utjämningen erbjuder **ClearType**, **GDI** och **Ingen**. På Utseende har utjämning och avstängning av teman samma position för alla typer, med **Standardutseende** under.

Reglaget **Ljudvolym** på Alarm styr internt uppspelade ljudfiler separat per widget och visar nivån i dB. Standardvärdet **−18 dB** bevarar filens ursprungliga nivå (**100%**). Åt höger förstärks ljudet; maximum **0 dB** motsvarar cirka **794%** av ursprunglig amplitud. Längst till vänster är **−∞ dB** (tystnad). Ändringar gäller under ljudtestet. Reglaget är avstängt för filer som öppnas i externa program. Förstärkning gäller avkodat ljud, inklusive WAV, MP3, WMA, AAC, M4A och FLAC när Windows stöder dem. Äldre uppspelning av filer som inte kan avkodas, exempelvis MIDI, är begränsad till 100%.

Alarmets veckodagar följer första veckodagen i vald programkultur. Sparade dagar behåller sin innebörd när språket ändras. Om ett alarm utan valda veckodagar aktiveras från menyn öppnas dess Alarm-flik i stället för att aktivera ett alarm som inte kan ljuda.

Standardrambredden för digitala klockor är noll. **Inledande nolla** erbjuder **Visa** (standard), **Behåll utrymme** och **Utan utrymme**. **Behåll utrymme** döljer nollan men reserverar dess verkliga bredd i valt teckensnitt, så att övriga siffror står still även med proportionella teckensnitt. Fristående digitala klockor vänsterjusterar tiden och behåller fast storlek medan tiden går. Skärmklockor centrerar ett fast tidsområde anpassat till teckensnitt och format, med plats för två timsiffror. Tidsändringar centrerar eller skalar inte om texten. AM/PM- eller UTC-raden centreras oberoende. Skärmklockor använder vit text på svart bakgrund som standard.

## Tid och alarm

Digitala klockor, kalenderpaneler och skärmklockor erbjuder **Enligt språk**, **12 timmar** och **24 timmar** under **Tidsformat** på Allmänt. **Enligt språk** är standard: amerikansk och australisk engelska använder exempelvis 12 timmar, brittisk engelska 24. Ett manuellt val behålls när widgetspråket ändras. Avgränsare och AM/PM-markörer följer kulturen; kulturer utan egna markörer använder **AM/PM** i 12-timmarsläge.

**AM/PM** är markerat som standard. Avmarkering döljer markören utan att ändra 12-timmarscykeln. Valet är inaktiverat i 24-timmarsläge och för widgetar utan digital tid. Skärmklockor visar markören på en egen rad under tiden, som UTC. **UTC använder alltid 24 timmar**; cykel och AM/PM är inaktiverade vid UTC, men värdena sparas för återgång till lokal tid. Valet för inledande nolla avgör fortfarande om den visas, döljs med reserverad plats eller utelämnas.

Namngivna tidszoner visar ortens civila tid och följer automatiskt dess sommartidsregler. Förskjutningen bredvid namnet gäller aktuellt datum och uppdateras när listan öppnas. Separata **UTC**-poster erbjuder fasta förskjutningar från **UTC−12:00** till **UTC+14:00** i steg om 15 minuter utan sommartid. Välj lokal zon, valfri annan namngiven zon eller fast UTC-förskjutning oberoende för varje widget.

Varje widget kan använda valfri Windows-tidszon och en förskjutning med tecken i formen `[-]HH:mm:ss.ff`. Kompakt inmatning tolkas från höger, med sekunder först.

Förskjutningen är användbar exempelvis i sändningsstudior för att kompensera för överföringskedjans fördröjning. Om studioklockan ställs fram med den uppmätta fördröjningen når tidssignalen lyssnarna vid avsedd tidpunkt.

CalClock kan använda Windows-systemtid eller en programlokal korrigering från NTP-servrar. Valet är globalt för alla widgetar. Synkronisering ändrar aldrig Windows-klockan. Om NTP-kontakten förloras efter en lyckad synkronisering ligger senaste korrigering kvar aktiv i processminnet. Serverbyte behåller också giltig korrigering tills ett nytt svar tas emot.

Klockwidgetar har alarm för individuellt valda veckodagar; alla sju är aktiva som standard. Ett alarm visar sin dolda widget och för den framför andra fönster utan att permanent ändra alltid överst. WAV, MP3, WMA, MIDI, AAC, M4A och FLAC identifieras för intern engångs- eller upprepad uppspelning; faktisk avkodning beror på installerade Windows-mediekomponenter. Andra filer och kommandon skickas asynkront till Windows. Ett alarm kan även anropa en HTTP- eller HTTPS-adress. Oberoende av detta kan det använda sex-toners tidssignalen, vars första korta ton ljuder fem sekunder före alarmtiden.

Kör fil eller kommando aktiverar fältet, Bläddra, Test och upprepning. Test och upprepning kräver också ett icke-tomt fält, men ett pågående test kan alltid stoppas. Test visar den visuella indikeringen och provar fil, kommando, ljud och fjärrskriptadress asynkront. Om alarmets tidssignal valts spelas också hela sekvensen med sex toner; Stoppa test avslutar internt ljud och signalens förhandsvisning.

Signal-fliken kan stänga av signaler eller schemalägga dem med intervall på 1, 5, 10, 15, 20, 30 eller 60 minuter enligt widgetens visade tid. 20-minutersintervallet ljuder vid :00, :20 och :40. Mönstret är **Greenwich Time Signal (GTS)**: fem korta toner markerar de sista fem sekunderna och en längre den exakta gränsen. Tidszoner, UTC, förskjutningar och aktuell NTP-korrigering beaktas. Alarmets signal och Signal-fliken är oberoende; sammanfaller tiderna spelar CalClock en gemensam sekvens. Även förskjutningar med delar av sekunder beaktas, och överlappande widget-, alarm- och testtoner fortsätter oavbrutet tills sista överlappningen slutar.

**Tidssignalens ljud** på Program erbjuder **Inbyggd generator** (standard) och **Systempip**. Valet gäller alla signaler, inklusive alarm, och sparas globalt. För **Inbyggd generator** visar **Tidssignalens volym** nivån i dB för hela programmet. Höger ändläge är **0 dB**, den högsta oförvrängda sinusamplituden; tystnad är **−∞ dB**. Standardnivån är **−18 dB**. Decibelskalan har −18 dB i mitten. Generatorn startar och avslutar toner vid nollgenomgång, även när ett test stoppas. Pågående pip får avslutas; ett långt pip kan ta upp till en halv sekund. **Test** vid **Tidssignalens ljud** startar fortlöpande förhandsvisning; **Stoppa test** avslutar den. Båda ljudsätten kan testas, och testläget sparas inte. Att hålla volymreglaget nedtryckt startar också förhandsvisning tills musen släpps, om inte knapptestet körs. Uppspelning börjar vid nästa hela sekund, med korta toner varje sekund och en lång vid :00, :05, :10 osv. Förhandsvisning och samtidiga widget- eller alarmsignaler delar en enda ton. För **Systempip** är bara volymreglaget avstängt. Ljudvalet är tillgängligt endast när systemet stöder båda metoderna.

Alarm och tidssignal kan också växlas i snabbmenyn för widgetar med ljud. Alarmets post visar tiden och aktiva veckodagar om inte alla valts. Markerat Tyst gäller widgeten och motsvarar valet på Allmänt. En fristående Kalender har inget alarm, tidssignal eller tyst läge; dessa kommandon utelämnas eller inaktiveras. Meddelandefältets kommando heter Tysta alla; `M` på valfri widget gör samma globala växling. Global återaktivering återställer bara de widgetar som tystades av föregående globala åtgärd. Internt ljud fortsätter tyst och blir hörbart igen när tystningen upphävs. Ett pågående pip kan avslutas; kommande pip hoppas över tills ljudet åter aktiveras. Andra kommandon och fjärrskript påverkas inte.

## Inställningar och menyer

`Spara` verkställer ändringar och stänger Inställningar; `Verkställ` gör det utan att stänga; `Avbryt` kastar ändringar som inte verkställts, inklusive förhandsvisning av utseendet. Enter aktiverar `Spara`, Esc `Avbryt`.

Varje widgetmeny innehåller relevanta kommandon — synlighet, alltid överst, sekunder, analog storlek eller datumkopieringsformat — följt av `Ordna i rutnät`, Inställningar, Hjälp, Om och Avsluta. Meddelandefältets meny listar alla widgetar med löpnummer, sedan Visa alla, Dölj alla och Tysta alla. Separat grupperade `Ordna i rutnät` följer före programkommandona.

Visning eller återställning placerar widgetar framför andra fönster utan att ändra alltid överst. CalClock säkerställer minst en synlig widget efter start. En andra start aktiverar den befintliga instansen och återställer senast dolda widgetar om ingen syns. Ikonen registreras automatiskt igen när Utforskaren startas om. Om `ClockWndMain` inte stöder sekundvisare vid vald storlek inaktiveras Sekunder, men det sparade valet behålls för en annan kompatibel storlek.

## Lagring av inställningar

Inställningar sparas som standard under:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

XML-lagring kan aktiveras i Inställningar och använder:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Efter lyckad XML-skrivning tar CalClock bort sitt programtillstånd från registret. Byte tillbaka tar på motsvarande sätt bort den automatiska XML-filen och tomma CalClock-mappar. XML-import läser och sparar inställningarna direkt i vald lagring utan att ändra lagringstyp. Tyst läge sparas per widget med ljud. Start med Windows sparas som värdet `CalClock` i den vanliga Windows-nyckeln `Run` för aktuell användare.

## Bygga programmet

Krav:

- Microsoft Visual Studio med verktygsuppsättningen MSVC v145
- Windows SDK

Öppna `CalClock.slnx`, välj `Release | Win32` och bygg lösningen. Programfilen skapas som:

```text
Release\CalClock.exe
```

Endast Win32/x86 stöds. Projektet erbjuder avsiktligt ingen x64-konfiguration eftersom integrationen med Windows klockkontroll kräver x86-kompatibilitet.

## Licens

CalClock är tillgängligt under [MIT-licensen](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
