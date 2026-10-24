# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · **Nederlands** · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock is een native Win32/x86-toepassing voor Windows Vista en nieuwer met afzonderlijk instelbare zwevende klokken en kalenders op het bureaublad. Het programma werkt vanuit het systeemvak en ondersteunt maximaal 32 widgets en 36 taalkeuzes; de taal van de toepassing en elke widget is apart instelbaar.

## Bediening

Sleep een klok of paneel met de linkermuisknop. Sleep een losse kalender via de vrije ruimte. Klik met rechts op een widget of het pictogram in het systeemvak voor het menu. Klik met links op het pictogram om zichtbare widgets te verbergen; als alles verborgen is, worden alleen de laatst verborgen widgets hersteld.

## Widgets en instellingen

Via Instellingen kunt u analoge en digitale klokken, kalenders, kalenderpanelen met een klok en schermklokken toevoegen, verwijderen en dupliceren. Elke widget heeft een eigen zichtbaarheid, Altijd op voorgrond, taal, tijdzone en verschuiving [-]HH:mm:ss.ff. Wijzerplaatgroottes zijn afzonderlijk instelbaar. Digitale klokken ondersteunen seconden, een voorloopnul, lettertypen, kleuren, dekking en een transparante achtergrond. Kalenders ondersteunen weeknummers en zondag als eerste dag en gebruiken de widgettaal.

## Alarm en sneltoetsen

Klokken en panelen kunnen een alarm hebben. De toepassing speelt een geluidsbestand zelf eenmaal of voortdurend af volgens de herhaaloptie; andere bestanden en opdrachten worden aan Windows doorgegeven. Klik op de alarmerende wijzerplaat of weergave, kies Alarm stoppen of druk op Esc om de aanduiding en het geluid van de toepassing te stoppen. Dubbelklikken op een wijzerplaat of digitale weergave schakelt seconden om. F1 opent Help, B Instellingen en Esc verbergt een widget wanneer er geen alarm wordt gestopt. Widgetposities worden na slepen opgeslagen, dialoogposities bij sluiten en instellingen in de gekozen opslag. Opnieuw starten activeert de bestaande toepassing en houdt widgets op de dichtstbijzijnde beschikbare plaats in het werkgebied.

## Tijd invoeren en alarmacties

De alarmtijd accepteert HH:mm met een dubbele punt, punt, spatie of ander scheidingsteken, of zonder scheidingsteken. Een of twee cijfers zijn uren, drie of vier uren en minuten: 7, 12, 730, 0730 of 7:30. Na het verlaten van het veld wordt de waarde HH:mm. Verschuivingen worden vanaf rechts als seconden gelezen: 2 is 00:00:02.00, 230 en 0230 zijn 00:02:30.00, 12345 is 01:23:45.00. Met scheidingstekens zijn twee groepen minuten en seconden, drie uren, minuten en seconden en een vierde honderdsten; een teken is toegestaan. De dagen onder Alarm ingeschakeld bepalen de actieve weekdagen; standaard zijn alle dagen gekozen. Hun volgorde volgt de toepassingstaal; taalwijziging verandert de opgeslagen dagen niet.

Een alarm toont een verborgen widget en brengt deze naar voren zonder Altijd op voorgrond blijvend te wijzigen. Tijdsignaal afspelen begint de eerste korte toon vijf seconden vóór het alarm. Dit staat los van het tabblad Signaal; gelijktijdige reeksen worden samengevoegd. Testen laat de wijzerplaat of rand knipperen en test het bestand, de opdracht, het geluid, de HTTP/HTTPS-URL van het externe script en, indien gekozen, het volledige tijdsignaal. Test stoppen beëindigt de interne audio en het proefsignaal van de test; het alarm stoppen beëindigt de interne alarmaudio. Bij dempen loopt interne audio stil door en wordt na opheffen weer hoorbaar. Opdrachten en externe scripts blijven actief.

De pieptonen van het alarm worden gepland volgens het werkelijke tijdstip van het eerstvolgende alarm, na tijdzoneconversie en toepassing van de widgetverschuiving. Ze beginnen vijf werkelijke seconden eerder, ook als de weergegeven klok rechtstreeks naar de alarmtijd springt. Een alarmtijd die in het voorjaar wordt overgeslagen, activeert geen alarm of pieptonen. Tijdens het herhaalde uur in het najaar worden het alarm en de pieptonen voor dezelfde datum en ingestelde tijd slechts eenmaal afgespeeld.

Geluidsvolume op het tabblad Alarm regelt de interne weergave voor die widget. De standaard −18 dB behoudt het oorspronkelijke bestandsniveau (100%). Naar rechts versterkt het geluid; het maximum van 0 dB is ongeveer 794%. −∞ dB betekent stilte. Wijzigingen zijn ook tijdens een test hoorbaar. MIDI en bestanden die niet gedecodeerd kunnen worden en via een alternatieve speler worden afgespeeld, zijn beperkt tot 100%.

## Selecteren, toetsen en datums kopiëren

Instellingen onthoudt het laatste tabblad en Toevoegen het laatst toegevoegde type. Verwijderen of Del verwijdert alle geselecteerde items zodra wijzigingen worden toegepast. Dubbelklikken op een item toont een verborgen widget, selecteert Zichtbaar en markeert deze kort. Instellingen in het menu van een widget selecteert die widget in de lijst. Klikken op een kalenderdag kiest de datum en kopieert deze naar het klembord. Elke kalender heeft een eigen indeling in Instellingen en zijn menu. Alle 33 indelingen zijn in elke taal beschikbaar; tekstnamen en de standaard Korte datum volgen de widgettaal.

Insert schakelt de selectie van het huidige item om en verplaatst de lijstcursor één rij omlaag. Ctrl+C kopieert widgets, Ctrl+V voegt kopieën in lijstvolgorde toe met een naamachtervoegsel in de toepassingstaal. Er zijn maximaal 32 widgets toegestaan. Kopieën worden op volgorde toegevoegd tot de limiet; voor de rest verschijnt een melding. Alt+0, Alt+1, Alt+2 en Alt+3 kiezen op een analoge klok of kalender met klok de grootte van de hoofdwijzerplaat, van klein naar groot.

Wanneer u de instellingen opent via het systeemvakpictogram, wordt de laatst geselecteerde widget opnieuw geselecteerd.

## Widgets schikken

Schikken in raster behoudt de globale handmatige indeling, lijnt middelpunten uit op de dichtstbijzijnde rasterpunten en verwijdert overlap. De widget waarvan het menu is gebruikt blijft staan. Een widgetmenu beïnvloedt zijn beeldscherm; het systeemvakpictogram behandelt elk scherm afzonderlijk. Herhalen houdt de indeling stabiel. Dubbelklikken in Instellingen markeert een widget met snel lichtblauw knipperen; een alarm knippert langzamer rood. Altijd op voorgrond uitschakelen plaatst de widget achter andere vensters. De bovenste paneelkoppeling gaat naar vandaag, de onderste opent de klassieke Windows-instellingen voor datum en tijd. Als uitlijnen op randen is ingeschakeld, klikt een versleepte widget binnen vijf pixels vast aan de rand van het werkgebied. Bij vergroten of verkleinen blijft dezelfde rand of hetzelfde paar randen behouden.

Panelen met een kalender en klok kunnen boven de onderste koppeling Windows-meldingen over datum en tijd tonen. **Meldingen over datum en tijd** op het tabblad **Algemeen** is standaard ingeschakeld en wordt voor elk paneel afzonderlijk opgeslagen. Als meerdere meldingen van toepassing zijn, staan ze net als in Windows onder elkaar. Wanneer de optie is uitgeschakeld of er geen toepasselijke melding is, blijven de oorspronkelijke afmetingen en indeling van het paneel behouden zonder lege ruimte te reserveren.

Bij een losse kalender toont of verbergt Rij Vandaag op Vormgeving of in het menu de onderste rij. Naar vandaag kiest vandaag en herstelt de maandweergave. Bij een datumwisseling volgens de widgettijd wordt vandaag automatisch gekozen zonder de huidige kalenderweergave te veranderen.

## Vormgeving en opslag

Wijzigingen in de vormgeving verschijnen direct in het voorbeeld. Annuleren verwerpt niet-toegepaste wijzigingen; Standaardvormgeving herstelt de standaardwaarden voor dat type. Digitale klokken bieden lettertypen, vereffening, kleuren, dekking, binnenmarge, randbreedte en een transparante achtergrond. Klokken, kalenders en panelen delen vier randstijlen; een enkele rand heeft een instelbare kleur. Een paneel heeft aparte lettertypen voor de bovenste rij, tijd en onderste rij, een voorloopnul en wijzerplaatgroottes. Thema’s en lettertypevereffening worden voor de toepassing en elke widget ingesteld. Aangepaste kalenderlettertypen worden ondersteund bij de klassieke Windows-weergave of als thema’s voor de toepassing of widget zijn uitgeschakeld.

Instellingen kunnen naar XML worden geëxporteerd. Importeren laadt en bewaart de instellingen direct in de gekozen opslag zonder het opslagtype te veranderen. Automatische XML staat in %AppData%\FortSoft\CalClock\settings.xml. Na XML-opslag wordt HKCU\SOFTWARE\FortSoft\CalClock verwijderd; opslag in het register verwijdert de automatische XML.

Lettertypevereffening biedt ClearType, GDI en Geen. Voorloopnul biedt “Ja” (standaard), “Nee, ruimte behouden” en “Nee, zonder ruimte”. “Nee, ruimte behouden” verbergt de nul maar reserveert de breedte in het gekozen lettertype; andere cijfers behouden hun positie, ook bij proportionele lettertypen. Schermklokken blijven gecentreerd inclusief die ruimte. De UTC-rij heeft een eigen centrering.

## Instellingen en menu’s

Taal, lettertype, vereffening, thema’s, opslag, starten met Windows en uitlijnen op randen zijn algemene instellingen op Toepassing. Bij de eerste start wordt de Windows-weergavetaal gekozen, of Amerikaans Engels als deze niet ondersteund wordt. Widgettaal, vereffening en thema’s gelden alleen voor die widget.

Een widgetmenu bevat toepasselijke keuzes voor zichtbaarheid, Altijd op voorgrond, seconden, grootte en datumkopie, gevolgd door Schikken in raster, Instellingen, Help, Info en Afsluiten. Het pictogrammenu bevat genummerde widgets, Alles weergeven, Alles verbergen en Alles dempen, gevolgd door een afzonderlijke rasteropdracht. Tonen of herstellen brengt een widget naar voren zonder Altijd op voorgrond te wijzigen. Opnieuw starten herstelt zo nodig de laatst verborgen widgets. Wijzerplaatgroottes en de secondewijzer hangen van Windows af. Alarm en Signaal zijn ook in het menu te schakelen; daar staan de tijd, het interval en bij een gedeeltelijke week de actieve dagen. Dempen komt overeen met Gedempt op Algemeen. Alles dempen en M dempen elke widget; opnieuw schakelen herstelt alleen wat deze opdracht zelf dempte. Een alarm inschakelen zonder gekozen dag opent het tabblad Alarm.

## Hoorbaar tijdsignaal

Het signaal volgt Greenwich Time Signal (GTS): vijf korte tonen tijdens de laatste vijf seconden en een lange toon precies op de tijdgrens. Signaal biedt Tijdsignaal ingeschakeld en intervallen van 1, 5, 10, 15, 20, 30 of 60 minuten volgens de widgettijd. Aanvankelijk staat het uit met een uurinterval geselecteerd. Schakelen via het menu behoudt het interval. UTC, tijdzone, verschuiving en NTP tellen mee; bij 20 minuten klinkt het op :00, :20 en :40. Gelijktijdige widget- en alarmsignalen worden samengevoegd. Na dempen mag de huidige toon eindigen; volgende tonen worden overgeslagen tot de eerstvolgende geplande toon na opheffen. Een losse Kalender heeft geen alarm, tijdsignaal of demping.

Geluid tijdsignaal op Toepassing biedt Ingebouwde generator (standaard) en Systeempiep voor alle widgets en alarmen. Volume tijdsignaal toont het generatorniveau in dB: rechts is 0 dB de maximale onvervormde sinusamplitude, −∞ dB is stilte en −18 dB de standaard. Testen start een voortdurend voorbeeld, Test stoppen beëindigt dit. Beide geluiden zijn te testen; de test wordt niet opgeslagen. De schuifregelaar vasthouden geeft ook een voorbeeld tot de muis wordt losgelaten, tenzij de knoptest loopt. Het afspelen begint op de volgende hele seconde: een korte toon elke seconde en een lange op :00, :05, :10 enzovoort. Gelijktijdige test-, widget- en alarmsignalen delen één toon. Stoppen laat de huidige toon eindigen; een lange kan nog een halve seconde duren. Honderdsten in de verschuiving tellen mee; overlappende tonen klinken onafgebroken tot de laatste overlap eindigt.

## Extra klokken

Kalender met klok kan op Algemeen maximaal twee extra klokken met eigen namen en tijdzones tonen. Elke klok toont dan ook zijn lokale weekdag. Kies elke wijzerplaatgrootte afzonderlijk op Vormgeving of in het contextmenu. Extra klokken hebben geen secondewijzer. Toevoegen, verwijderen en vergroten of verkleinen behoudt de verbinding met de randen van het werkgebied.

Alleen dubbelklikken rechtstreeks op de hoofdwijzerplaat schakelt de secondewijzer daarvan. Menu’s van extra klokken bevatten alleen groottes. Zij delen taal, tijdnotatie, lettertypen en verschuiving van de widget; hun digitale tijd toont geen seconden.

## Tijdnotatie en tijdzones

Tijdnotatie op Algemeen biedt Volgens taal (standaard), 12 uur en 24 uur. Een handmatige keuze blijft na een taalwijziging behouden. Scheidingstekens en tijdsaanduidingen volgen de widgettaal. AM/PM is aanvankelijk ingeschakeld en regelt alleen de aanduiding bij 12 uur; zonder eigen taalaanduidingen wordt AM/PM gebruikt. Schermklokken tonen deze in een aparte rij onder de tijd. UTC gebruikt altijd de 24-uursnotatie. Benoemde zones volgen lokale tijd en zomertijd; de verschuiving geldt voor de huidige datum. Aparte UTC-items zijn vaste verschuivingen van −12:00 tot +14:00 in stappen van 15 minuten, zonder zomertijd.

Nieuwe widgets gebruiken standaard **Huidige Windows-tijdzone**. Deze optie volgt de huidige Windows-tijdzone en de instelling voor automatische zomertijd. Bestaande widgets behouden hun gekozen tijdzones. De keuze bepaalt de tijdzone; de gedeelde tijdbron Windows of NTP blijft daarvan onafhankelijk.

De verschuiving van de widget wordt op UTC toegepast vóór de omzetting naar de tijdzone en verschuift daardoor ook het moment van de zomertijdwisseling. Een klok die tien seconden voorloopt, schakelt tien seconden eerder om; een klok die tien seconden achterloopt, tien seconden later. Wijzers, digitale weergave, kalenderdatums, alarmen en tijdsignalen gebruiken de resulterende tijd.

## Tijdbron en NTP-logboek

Tijd kiest Windows-systeemtijd of NTP-servers voor de hele toepassing. NTP verandert alleen de CalClock-tijd; de Windows-klok wordt nooit aangepast. Tot het eerste geldige antwoord wordt de systeemtijd gebruikt. NTP is de standaard. De automatische groep kiest volgens de systeemregio Tsjechische en Slowaakse servers, PTB voor Europa of een wereldwijde groep. Metingen worden gefilterd op netwerkvertraging en afwijkingen van andere antwoorden. Nu synchroniseren start direct een nieuwe meting.

Na synchronisatie loopt de CalClock-klok door, onafhankelijk van latere wijzigingen van de Windows-systeemtijd. Bij verbindingsverlies of andere servers loopt deze door vanaf de laatste geldige synchronisatie tot een nieuw antwoord; de toestand blijft behouden tot de toepassing sluit.

Tijd registreert NTP-aanvragen sinds de start. Een record bevat de datum, lokale computertijd, server en status. OK is een geldig antwoord, θ de afwijking van Windows-systeemtijd. ERR geeft de oorzaak en eventuele foutcode. Het laatste record van een groep toont de gecombineerde afwijking Θ als bruikbare metingen bestaan. Afwijkingen zijn in milliseconden met vier decimalen: positief betekent dat de server voorloopt, negatief dat deze achterloopt. Θ is gebaseerd op geaccepteerde metingen en staat ook in de synchronisatiestatus. Logboek opslaan exporteert CSV met afwijkingen en foutdetails. Records worden niet tussen sessies bewaard; sla ze zo nodig vóór afsluiten op.

## Schermklok

Een digitale klok kan een of meer beeldschermen vullen en de andere verduisteren. De tekengrootte is een percentage van de schermhoogte; lettertype, vereffening, kleuren en binnenmarge zijn instelbaar. UTC kan op een aparte rij staan. Standaard is de tekst wit op zwart. Met Instellingen geopend is de klok een klein verplaatsbaar voorbeeld met de beeldverhouding van het scherm en een opgeslagen positie. Het raster verplaatst dit type niet. Esc verbergt de klok en verwijdert verduistering, ook met Instellingen geopend.

De muisaanwijzer verdwijnt na korte inactiviteit boven de schermklok en verduisterde schermen en verschijnt bij bewegen. Boven het kleine voorbeeld blijft deze zichtbaar.

## Bouwen en verpakken

Microsoft Visual Studio met de MSVC v145-toolset en Windows SDK zijn vereist. Open `CalClock.slnx`, kies `Release | x86` en bouw de oplossing. Het uitvoerbare bestand staat in `Release\CalClock.exe`. Alleen Win32/x86 wordt ondersteund omdat de integratie met de Windows-klokbesturing x86-compatibiliteit vereist.

Na het bouwen maakt `.\PackageRelease.ps1` `CalClock-<version>-win32.zip`; de versie wordt uit `Release\CalClock.exe` gelezen. Het archief bevat `CalClock.exe` en `license.txt` direct in de hoofdmap. Optionele ondertekeningsparameters `-SignerName`, `-SignToolPath` en `-TimestampServer` worden bij uitvoering opgegeven. Een bestaande geldige Authenticode-handtekening wordt gecontroleerd en niet vervangen. Eerdere CalClock-ZIP-pakketten worden aan het begin van elke uitvoering verwijderd; fouten bij ondertekenen of controleren stoppen het verpakken.

## Licentie

CalClock is beschikbaar onder de [MIT-licentie](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
