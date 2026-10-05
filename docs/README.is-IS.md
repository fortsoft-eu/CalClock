# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · **Íslenska** · [Türkçe](README.tr-TR.md)

CalClock er Win32/x86-forrit fyrir Windows Vista og nýrri útgáfur sem sýnir færanlegar klukkur og dagatöl með sjálfstæðum stillingum á Windows-skjáborðinu. Það keyrir á tilkynningasvæðinu og þarf ekki stjórnglugga sem er alltaf opinn.

## Eiginleikar

- Allt að 32 græjur með sjálfstæðum stillingum
- Sérstakt tungumál, tímabelti, tímahliðrun, sýnileiki og stilling um að vera alltaf efst fyrir hverja græju
- Vísaklukkur byggðar á Windows-stýringunni `ClockWndMain`, með sjálfvirkri greiningu á tiltækum stærðum og stuðningi við sekúnduvísi
- Stafrænar klukkur með leturgerðum, litum, ógagnsæi, innri spássíum, römmum, valfrjálsu upphafsnúlli og gagnsæjum bakgrunni
- Innbyggð Windows-dagatöl með dagsetningarvali, fjórum rammastílum, stillanlegum rammalit, vikunúmerum, vali á fyrsta vikudegi og 33 afritunarsniðum
- Dagatals- og klukkuspjöld með allt að tveimur viðbótarklukkum með nöfnum og sjálfstæðum tímabeltum, sér stærðum skífa, fjórum rammastílum, stillanlegum lit, UTC-texta, upphafsnúlli og sér letri fyrir hverja textalínu
- Vekjarar með vali á vikudögum, sjónrænni vísbendingu, innri hljóðspilun, endurtekningu, staðbundnum skipunum og HTTP/HTTPS-skriftuköllum
- Tímamerki fyrir hverja klukku á 1, 5, 10, 15, 20, 30 eða 60 mínútna fresti; samtímamerki sameinast í eina runu
- Þöggun fyrir hverja klukku og valanleg skipun til að þagga allt á tilkynningasvæðinu
- Valfrjáls sjálfvirk ræsing með Windows
- Valfrjáls festing við brúnir vinnusvæðisins innan fimm myndpunkta við drátt, virk sjálfgefið; festingin helst þegar stærð breytist
- NTP-samstilling án þess að breyta kerfisklukku Windows
- NTP-forstillingar fyrir Tékkland og Slóvakíu, PTB, Ubuntu/NTP Pool eða eigin þjóna
- Stillingar í skrásetningunni eða XML, með XML-innflutningi og -útflutningi
- Stjórnun frá tilkynningasvæðinu með endurheimt síðast földu græjanna
- Auðkenning græja og stöðug röðun í hnitanet án skörunar
- Tafarlaus forskoðun útlits með afturköllun og sjálfgefnu útliti hverrar græju
- Letur fyrir forrit og græjur, sjónrænir stílar og ClearType, GDI eða engin leturmýking
- Viðmót á tékknesku, bandarískri, breskri og ástralskri ensku, þýsku, frönsku, spænsku, ítölsku, portúgölsku, pólsku, slóvakísku, dönsku, finnsku, íslensku, norsku, sænsku og tyrknesku

## Tegundir græja

| Græja | Lýsing |
| --- | --- |
| Vísaklukka | Færanleg Windows-klukkuskífa með stærðum og valfrjálsum sekúnduvísi sem núverandi Windows-útgáfa styður |
| Stafræn klukka | Stillanleg stafræn birting með valfrjálsum UTC-texta, upphafsnúlli, römmum og gagnsæjum bakgrunni |
| Dagatal | Færanlegt innbyggt mánaðardagatal með dagsetningarvali, stillanlegum römmum og afritunarsniðum |
| Dagatal með klukku | Sameinað spjald með dagatali, vísaklukku, stillanlegum textalínum, UTC-birtingu og römmum |
| Skjáklukka | Stafræn klukka sem fyllir einn eða fleiri valda skjái, með valfrjálsri myrkvun og UTC á sér línu |

Við fyrstu ræsingu velur CalClock tungumál eftir viðmótstungumáli Windows og notar bandaríska ensku ef það er ekki stutt. Ein sýnileg vísaklukka er búin til sjálfgefið. Hver græja heldur staðsetningu og stillingum milli keyrslna. Meðan Stillingar eru opnar er skjáklukka alltaf sýnd sem færanleg forskoðun með hlutföllum valda skjásins. `Esc` felur skjáklukkuna og fjarlægir myrkvunina, líka þegar Stillingar eru virkar. Bendillinn hverfur eftir stutta kyrrstöðu yfir skjáklukkum og myrkvuðum skjám og birtist aftur þegar músin hreyfist. Hann helst sýnilegur yfir litlu forskoðuninni í Stillingum.

## Notkun

- Dragðu klukku eða spjald með vinstri músarhnappi.
- Dragðu sjálfstætt dagatal með því að grípa í laust svæði þess.
- Hægrismelltu á græju eða táknið á tilkynningasvæðinu til að opna samhengisvalmynd.
- Vinstrismellur á tilkynningatáknið felur sýnilegar græjur. Ef allar eru faldar endurheimtir næsti smellur aðeins þær sem voru faldar síðast.
- Tvísmelltu á klukkuskífu til að skipta um birtingu sekúndna. Í dagatals- og klukkuspjaldi breytir aðeins tvísmellur beint á aðalskífuna sekúnduvísinum. Viðbótarklukkur hafa engan sekúnduvísi.
- `F1` opnar Hjálp, `B` Stillingar, `M` skiptir um almenna þöggun og `Esc` felur græju eða stöðvar virkan vekjara.
- Ýttu á `Alt+0`, `Alt+1`, `Alt+2` eða `Alt+3` á græjunum Vísaklukka og Dagatal með klukku til að velja stærð aðalskífunnar, frá minnstu til stærstu.
- Tvísmellur á græju í Stillingum birtir hana ef þarf, velur `Sýnilegt` og auðkennir hana stuttlega á skjáborðinu.
- Að opna Stillingar úr valmynd græju velur þá græju strax.
- Notaðu `Ctrl` eða `Shift` fyrir margval, `Ctrl+A` til að velja allt og `Del` til að fjarlægja valið. `Insert` víxlar vali núverandi færslu og færir listabendilinn á næstu línu, eins og í Total Commander.
- Allir flýtilyklar listans virka líka þegar Fjarlægja eða Afrita hefur fókus. Flýtilykillinn færir fókus í listann og framkvæmir aðgerðina. `Ctrl+C` afritar valdar græjur og `Ctrl+V` bætir afritunum aftast í sömu röð. Afritin innihalda allar stillingar og fá viðskeyti við nafnið á tungumáli forritsins. Afrita framkvæmir sömu aðgerð beint. Hámarkið er 32 græjur. Ef ekki rúmast öll afrit bætast þau sem rúmast við í röð og skilaboð birtast um hin.
- `Ctrl+A` eða þrefaldur smellur í textareit velur allan textann.

Þegar margar græjur eru valdar eru stýringar þeirra á Almennt, Útlit, Vekjari og Tímamerki óvirkar; almennu fliparnir Tími og Forrit eru áfram tiltækir. Stillingar muna síðasta opna flipa og síðustu tegund græju sem var bætt við. Á litlu vinnusvæði býður glugginn upp á lárétt eða lóðrétt skrun eftir þörfum.

Dagsetningar má afrita í 33 sniðum: staðbundnum, röðanlegum, með dag eða mánuð fyrst, textasniðum og með vikudegi. Hvert sniðmynstur er tiltækt á öllum viðmótstungumálum. Sjálfgefið stutt staðbundið snið fylgir tungumáli græjunnar, eins og mánaða- og vikudagaheiti. Færslurnar sýna mynstrið og uppfært dæmi.

Dagatals- og klukkuspjald getur sýnt tvær viðbótarklukkur. Virkjaðu hvora á Almennt og veldu nafn og tímabelti. Nafngreind tímabelti fylgja eigin sumartímareglum; föst UTC-hliðrun helst óbreytt. Þegar viðbótarklukkur eru virkar sýnir hver klukka sinn staðbundna vikudag undir tímanum. Stærðarlistarnir þrír á Útlit stjórna aðalklukkunni, Klukku 1 og Klukku 2 í þeirri röð. Hægrismelltu á viðbótarskífu til að velja stærð hennar. Viðbótarklukkur sleppa alltaf sekúndum og deila tungumáli, tímasniði, letri og tímahliðrun græjunnar. Að bæta við, fjarlægja eða breyta stærð klukkna heldur græjunni fastri við sömu brúnir vinnusvæðisins.

Efri dagsetning spjaldsins er tengill sem færir dagatalið á daginn í dag; neðri tímabeltatextinn opnar hefðbundnar dagsetningar- og tímastillingar Windows. Báðir tenglar eru aðgengilegir með `Tab`, sýna fókusramma og má virkja með lyklaborði. Dagatalið heldur fullri virkni en sleppir óþarfa Í dag-línunni í þessari samsetningu.

`Raða í hnitanet` raðar sýnilegum skjáborðsgræjum stöðugt án skörunar og varðveitir handvirka uppröðun nokkurn veginn. Græjan sem ræsti skipunina úr eigin valmynd helst á sínum stað; skipunin á tilkynningasvæðinu raðar hverjum skjá sjálfstætt. Skjáklukkur eru undanskildar.

## Útlit

Fyrir sjálfstæð dagatöl stjórnar **Í dag-lína** í valmynd eða á Útlit neðstu línunni. Hún er sjálfgefið valin; afveldu hana til að fela línuna og minnka dagatalið. Valið er vistað fyrir hverja græju. **Fara á daginn í dag** er áfram tiltækt og snýr aftur í mánaðarsýn. Þegar dagsetning breytist samkvæmt tíma græjunnar velur dagatalið daginn í dag sjálfkrafa en heldur núverandi sýn.

Útlitsbreytingar sjást strax á valinni græju. `Hætta við` endurheimtir breytingar sem hafa ekki verið notaðar; `Sjálfgefið útlit` endurheimtir gildi viðkomandi tegundar.

Stafrænar klukkur, dagatöl og spjöld deila fjórum rammastílum. Einfaldi ramminn hefur stillanlegan lit; breidd má stilla þar sem græjan styður það. Gagnsæjar stafrænar klukkur bjóða sömu stíla og ógagnsæjar. Leturgluggar sýna aðeins viðeigandi valkosti og sleppa ónotaðri forskoðun og áhrifum. Forrits- og dagatalsletur hafa ekki stærðarval, en stafrænar klukkur og spjaldtextar hafa það. Innbyggt dagatal notar eigið letur aðeins þegar sjónrænir stílar hafa verið gerðir óvirkir fyrir dagatalið eða allt forritið.

Tungumál forrits, viðmótsletur, leturmýking, sjónrænir stílar, vistun, Windows-ræsing og festing við brúnir eru almennar stillingar á Forrit. Tímagjafinn er líka almennur. Tungumál græju, mýking, stílar, tímabelti, hliðrun, vekjari og tímamerki eru sjálfstæð. Þegar nýtt tungumál er notað er opni Stillinga-glugginn strax endurgerður á því tungumáli. Leturmýking býður **ClearType**, **GDI** og **Engin**. Á Útlit eru mýking og afvirkjun þema á sama stað fyrir allar tegundir, með **Sjálfgefið útlit** fyrir neðan.

Sleðinn **Hljóðstyrkur** á Vekjari stjórnar innri spilun hljóðskráa fyrir hverja græju og sýnir styrk í dB. Sjálfgefið **−18 dB** varðveitir upprunalegan styrk skrárinnar (**100%**). Til hægri magnast hljóðið; hámarkið **0 dB** er um **794%** af upprunalegri sveifluvídd. Lengst til vinstri er **−∞ dB** (þögn). Breytingar virka meðan á prófun stendur. Sleðinn er óvirkur fyrir skrár sem opnast í utanaðkomandi forriti. Mögnun gildir um afkóðað hljóð, þar á meðal WAV, MP3, WMA, AAC, M4A og FLAC þegar Windows styður það. Eldri spilun skráa sem ekki er hægt að afkóða, svo sem MIDI, er takmörkuð við 100%.

Vikudagar vekjarans fylgja fyrsta vikudegi valinnar menningarstillingar forritsins. Vistaðir dagar halda merkingu sinni þegar tungumál breytist. Ef vekjari er virkjaður úr valmynd án valinna vikudaga opnast Vekjari-flipinn í stað þess að virkja vekjara sem getur ekki hringt.

Sjálfgefin rammabreidd stafrænnar klukku er núll. **Upphafsnúll** býður **Sýna** (sjálfgefið), **Halda plássi** og **Án pláss**. **Halda plássi** felur núllið en tekur frá raunverulega breidd þess í völdu letri, svo að aðrir tölustafir haldi stöðu sinni líka í misbreiðu letri. Færanlegar stafrænar klukkur vinstrijafna tímann og halda fastri stærð meðan tíminn líður. Skjáklukkur miðja fast tímasvæði sem miðast við letur og snið og rúmar tvo tölustafi klukkustundar. Breytingar á tíma miðja eða stækka ekki textann aftur. AM/PM- eða UTC-línan er miðjuð sjálfstætt. Skjáklukkur nota sjálfgefið hvítan texta á svörtum bakgrunni.

## Tími og vekjarar

Stafrænar klukkur, dagatalsspjöld og skjáklukkur bjóða **Eftir tungumáli**, **12 klukkustundir** og **24 klukkustundir** undir **Tímasnið** á Almennt. **Eftir tungumáli** er sjálfgefið: bandarísk og áströlsk enska nota til dæmis 12 klukkustundir, bresk enska 24. Handvirkt val helst þegar tungumál græjunnar breytist. Aðskiljarar og AM/PM-merki fylgja menningarstillingunni; án eigin merkja er **AM/PM** notað í 12 klukkustunda ham.

**AM/PM** er sjálfgefið valið. Afval felur merkið án þess að breyta 12 klukkustunda kerfinu. Valkosturinn er óvirkur í 24 klukkustunda ham og fyrir græjur án stafræns tíma. Skjáklukkur sýna merkið á sér línu undir tímanum eins og UTC. **UTC notar alltaf 24 klukkustundir**; tímasnið og AM/PM eru óvirk við UTC en valið er varðveitt fyrir endurkomu í staðartíma. Upphafsnúllsstillingin ræður áfram hvort núllið sé sýnt, falið með fráteknu plássi eða sleppt.

Nafngreind tímabelti sýna borgaralegan tíma valins staðar og fylgja sjálfkrafa sumartímareglum hans. Hliðrun við nafnið gildir fyrir núverandi dagsetningu og uppfærist þegar listinn opnast. Sérstakar **UTC**-færslur bjóða fasta hliðrun frá **UTC−12:00** til **UTC+14:00** í 15 mínútna skrefum, án sumartíma. Veldu staðbundið belti, annað nafngreint belti eða fasta UTC-hliðrun sjálfstætt fyrir hverja græju.

Hver græja getur notað hvaða Windows-tímabelti sem er og hliðrun með formerki á sniðinu `[-]HH:mm:ss.ff`. Samþjöppuð innsláttargildi eru túlkuð frá hægri, frá sekúndum.

Hliðrun er gagnleg til dæmis í útvarpsveri til að bæta upp seinkun í flutningsleið. Með því að flýta klukku versins um mælda seinkun nær tímamerkið hlustendum á tilætluðum tíma.

CalClock getur notað Windows-kerfistíma eða leiðréttingu frá NTP-þjónum sem gildir aðeins í forritinu. Valið gildir fyrir allar græjur. Samstilling breytir aldrei Windows-klukkunni. Ef NTP-tenging tapast eftir heppnaða samstillingu helst síðasta leiðrétting virk í minni ferlisins. Þjónaskipti varðveita líka gilda leiðréttingu þar til nýtt svar berst.

Klukkugræjur styðja vekjara á völdum vikudögum; allir sjö eru virkir sjálfgefið. Vekjari birtir sína földu græju og færir hana fram fyrir aðra glugga án þess að breyta alltaf efst varanlega. WAV, MP3, WMA, MIDI, AAC, M4A og FLAC eru þekkt til innri spilunar einu sinni eða í sífellu; raunveruleg afkóðun ræðst af uppsettum margmiðlunarhlutum Windows. Aðrar skrár og skipanir eru sendar Windows ósamstillt. Vekjari getur líka kallað HTTP- eða HTTPS-slóð. Óháð þessu getur hann notað sex-pípa tímamerkið, þar sem fyrsta stutta pípið hljómar fimm sekúndum fyrir stilltan vekjaratíma.

Keyra skrá eða skipun virkjar reitinn, Fletta, Prófa og endurtekningu. Prófun og endurtekning krefjast líka þess að reiturinn sé ekki tómur, en alltaf má stöðva virka prófun. Prófa sýnir sjónræna merkingu og prófar skrá, skipun, hljóð og slóð fjarskriftu ósamstillt. Ef tímamerki vekjarans er valið er öll sex-pípa runan líka spiluð; Stöðva prófun lýkur innri hljóðspilun og forskoðun merkisins.

Tímamerkisflipinn hefur gátreitinn Tímamerki virkt og valhnappa fyrir 1, 5, 10, 15, 20, 30 eða 60 mínútna bil samkvæmt sýndum tíma græjunnar. Í upphafi er slökkt á merkinu og klukkustundarbil valið. Þegar slökkt og kveikt er á Tímamerki í valmynd græjunnar helst bilið óbreytt. Valmyndin sýnir vekjaratímann og tímamerkjabilið innan sviga. 20 mínútna bilið gefur merki við :00, :20 og :40. Mynstrið er **Greenwich Time Signal (GTS)**: fimm stutt píp merkja síðustu fimm sekúndurnar og eitt lengra nákvæm tímamörk. Tímabelti, UTC, hliðrun og gildandi NTP-leiðrétting eru virt. Merki vekjarans og Tímamerki-flipinn eru óháð; ef tímar falla saman spilar CalClock eina sameiginlega runu. Brot úr sekúndu í hliðrun eru virt og skarandi tónar græja, vekjara og prófana hljóma samfellt þar til síðustu skörun lýkur.

**Hljóð tímamerkis** á Forrit býður **Innbyggðan hljóðgjafa** (sjálfgefið) og **Kerfispíp**. Valið gildir fyrir öll tímamerki, líka vekjara, og vistast almennt. Fyrir **Innbyggðan hljóðgjafa** sýnir **Hljóðstyrkur tímamerkis** styrkinn í dB fyrir allt forritið. Hægri endinn er **0 dB**, mesta óbjagaða sveifluvídd sínusbylgju; þögn er **−∞ dB**. Sjálfgefið gildi er **−18 dB**. Desíbelakvarðinn hefur −18 dB í miðjunni. Hljóðgjafinn byrjar og endar tóna við núllþverun, líka þegar prófun er stöðvuð. Yfirstandandi píp fær að enda; langt píp getur tekið allt að hálfa sekúndu. **Prófa** við **Hljóð tímamerkis** ræsir samfellda forskoðun og **Stöðva prófun** lýkur henni. Báðar aðferðir má prófa og prófunarstaðan vistast ekki. Að halda hljóðstyrkssleðanum niðri ræsir einnig forskoðun þar til músinni er sleppt, nema hnappaprófun sé í gangi. Spilun byrjar á næstu heilu sekúndu, með stuttum tón hverja sekúndu og löngum við :00, :05, :10 o.s.frv. Forskoðun og samtímamerki græja eða vekjara deila einum tóni. Við **Kerfispíp** er aðeins hljóðstyrkssleðinn óvirkur. Hljóðvalið er aðeins tiltækt ef kerfið styður báðar aðferðir.

Vekjara og tímamerki má líka kveikja og slökkva á í samhengisvalmynd hljóðgræju. Vekjarafærslan sýnir tímann og virka daga ef ekki allir eru valdir. Þöggun gildir fyrir græjuna og samsvarar valinu á Almennt. Sjálfstætt Dagatal hefur hvorki vekjara, tímamerki né þöggunarstöðu, svo þessar skipanir eru ekki sýndar eða eru óvirkar. Skipunin á tilkynningasvæðinu er Þagga allt; `M` á hvaða græju sem er framkvæmir sömu almennu breytingu. Almenn afþöggun endurheimtir aðeins þær græjur sem síðasta almenna aðgerð þaggaði. Innri spilun heldur áfram hljóðlaust og verður aftur heyranleg þegar þöggun lýkur. Yfirstandandi píp getur klárast; seinni pípum er sleppt þar til hljóð er virkjað. Aðrar skipanir og fjarskriftur eru óbreyttar.

## Stillingar og valmyndir

`Vista` notar breytingar og lokar Stillingum; `Nota` notar þær án þess að loka; `Hætta við` fellir niður ónotaðar breytingar, þar á meðal forskoðun útlits. Enter virkjar `Vista`, Esc `Hætta við`.

Hver græjuvalmynd inniheldur viðeigandi skipanir — sýnileika, alltaf efst, sekúndur, stærð vísaklukku eða dagsetningarafritunarsnið — og síðan `Raða í hnitanet`, Stillingar, Hjálp, Um og Hætta. Tilkynningavalmyndin telur upp græjurnar með raðnúmerum og síðan Sýna allt, Fela allt og Þagga allt. Sérstaklega aðgreind skipun `Raða í hnitanet` kemur á undan forritsskipunum.

Að sýna eða endurheimta græjur færir þær fram fyrir aðra glugga án breytingar á alltaf efst. CalClock tryggir að minnst ein græja sé sýnileg eftir ræsingu. Önnur ræsing virkjar fyrirliggjandi keyrslu og endurheimtir síðast földu græjurnar ef engin er sýnileg. Tilkynningatáknið skráist sjálfkrafa aftur þegar Windows Explorer endurræsist. Ef `ClockWndMain` styður ekki sekúnduvísi í valdri stærð er Sekúndur óvirkt, en valið varðveitist fyrir aðra studda stærð.

## Vistun stillinga

Stillingar vistast sjálfgefið undir:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

XML-vistun má virkja í Stillingum og notar:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Eftir heppnaða XML-vistun fjarlægir CalClock eigin forritsstöðu úr skrásetningunni. Þegar skipt er aftur yfir er sjálfvirka XML-skráin og tómar CalClock-möppur fjarlægðar á sama hátt. XML-innflutningur les og vistar stillingar strax í valinni vistun án þess að skipta um vistunargerð. Þöggun vistast fyrir hverja hljóðgræju. Ræsing með Windows vistast sem gildið `CalClock` í hefðbundna Windows-lyklinum `Run` hjá núverandi notanda.

## Smíði

Kröfur:

- Microsoft Visual Studio með MSVC v145-verkfærasafninu
- Windows SDK

Opnaðu `CalClock.slnx`, veldu `Release | Win32` og smíðaðu lausnina. Keyrsluskráin verður:

```text
Release\CalClock.exe
```

Aðeins Win32/x86 er stutt. Verkefnið býður vísvitandi ekki x64-stillingu því samþætting við Windows-klukkustýringuna krefst x86-samhæfni.

## Leyfi

CalClock er í boði samkvæmt [MIT-leyfinu](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
