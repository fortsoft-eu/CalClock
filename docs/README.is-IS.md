# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · **Íslenska** · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

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
- Viðmót á 36 tungumálaútgáfum; hægt er að velja tungumál forritsins og hverrar græju sérstaklega

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
- Delete fjarlægir valdar græjur. `Insert` víxlar vali núverandi færslu og færir listabendilinn eina línu niður.
- `Ctrl+C` afritar valdar græjur og `Ctrl+V` bætir afritunum aftast í sömu röð. Afritin innihalda allar stillingar og fá viðskeyti við nafnið á tungumáli forritsins. Afrita framkvæmir sömu aðgerð beint. Hámarkið er 32 græjur. Ef ekki rúmast öll afrit bætast þau sem rúmast við í röð og skilaboð birtast um hin.

Þegar stillingar eru opnaðar frá tákninu á tilkynningasvæðinu er síðast valda græjan valin aftur.

Stillingar muna síðasta opna flipa og síðustu tegund græju sem var bætt við.

Dagsetningar má afrita í 33 sniðum: staðbundnum, röðanlegum, með dag eða mánuð fyrst, textasniðum og með vikudegi. Hvert sniðmynstur er tiltækt á öllum viðmótstungumálum. Sjálfgefið stutt staðbundið snið fylgir tungumáli græjunnar, eins og mánaða- og vikudagaheiti. Færslurnar sýna mynstrið og uppfært dæmi.

Dagatals- og klukkuspjald getur sýnt tvær viðbótarklukkur. Virkjaðu hvora á Almennt og veldu nafn og tímabelti. Nafngreind tímabelti fylgja eigin sumartímareglum; föst UTC-hliðrun helst óbreytt. Þegar viðbótarklukkur eru virkar sýnir hver klukka sinn staðbundna vikudag undir tímanum. Stærðarlistarnir þrír á Útlit stjórna aðalklukkunni, Klukku 1 og Klukku 2 í þeirri röð. Hægrismelltu á viðbótarskífu til að velja stærð hennar. Viðbótarklukkur sleppa alltaf sekúndum og deila tungumáli, tímasniði, letri og tímahliðrun græjunnar. Að bæta við, fjarlægja eða breyta stærð klukkna heldur græjunni fastri við sömu brúnir vinnusvæðisins.

Efri dagsetning spjaldsins er tengill sem færir dagatalið á daginn í dag; neðri tímabeltatextinn opnar hefðbundnar dagsetningar- og tímastillingar Windows.

Spjöld með dagatali og klukku geta birt tilkynningar Windows um dagsetningu og tíma fyrir ofan neðri tengilinn. Valkosturinn **Tilkynningar um dagsetningu og tíma** á flipanum **Almennt** er sjálfgefið virkur og vistaður sérstaklega fyrir hvert spjald. Ef fleiri en ein tilkynning á við birtast þær hver undir annarri eins og í Windows. Ef valkosturinn er óvirkur eða engin tilkynning á við haldast upprunaleg stærð og uppsetning spjaldsins óbreytt án þess að autt svæði sé tekið frá.

`Raða á hnitanet` raðar sýnilegum skjáborðsgræjum stöðugt án skörunar og varðveitir handvirka uppröðun nokkurn veginn. Græjan sem ræsti skipunina úr eigin valmynd helst á sínum stað; skipunin á tilkynningasvæðinu raðar hverjum skjá sjálfstætt. Skjáklukkur eru undanskildar.

## Útlit

Fyrir sjálfstæð dagatöl stjórnar **Línan Í dag** í valmynd eða á Útlit neðstu línunni. Hún er sjálfgefið valin; afveldu hana til að fela línuna og minnka dagatalið. Valið er vistað fyrir hverja græju. **Fara á daginn í dag** er áfram tiltækt og snýr aftur í mánaðarsýn. Þegar dagsetning breytist samkvæmt tíma græjunnar færist dagatalið aðeins yfir á nýja daginn ef dagurinn í dag er valinn og sýnilegur í mánaðarsýn. Handvirkt valin dagsetning og aðrar sýnir haldast óbreyttar; merkingin og línan Í dag uppfærast alltaf.

Útlitsbreytingar sjást strax í forskoðun valinnar græju. `Sjálfgefið útlit` endurheimtir sjálfgefin gildi þeirrar græjutegundar. Þegar stillingum er lokað með breytingum sem hafa ekki verið staðfestar er spurt hvort vista eigi þær. Viðvörunin er sjálfgefið virk og má slökkva á henni á flipanum Forrit.

Stafrænar klukkur, dagatöl og spjöld deila fjórum rammastílum. Einfaldi ramminn hefur stillanlegan lit; breidd má stilla þar sem græjan styður það. Gagnsæjar stafrænar klukkur bjóða sömu stíla og ógagnsæjar. Forrits- og dagatalsletur hafa ekki stærðarval, en stafrænar klukkur og spjaldtextar hafa það. Nota má sérsniðið letur í dagatali með hefðbundnu útliti Windows eða þegar slökkt er á þemum fyrir græjuna.

Tungumál forrits, viðmótsletur, leturmýking, vistun, Windows-ræsing og festing við brúnir eru almennar stillingar á Forrit. Þegar slökkt er á þemum á flipanum Forrit gildir það aðeins fyrir Stillingar, Hjálp, Um og Tímareiknivél. Hver græja notar sína eigin þemastillingu. Tímagjafinn er líka almennur. Tungumál græju, mýking, stílar, tímabelti, hliðrun, vekjari og tímamerki eru sjálfstæð. Leturmýking býður **ClearType**, **GDI** og **Engin**.

Windows 2000-stíll krefst þess að Slökkva á þemum sé valið og gildir aðeins fyrir Stillingar, Hjálp, Um og
Tímareiknivél. Stýringar þessara glugga nota Tahoma 8 pt þegar sjálfgefið kerfisletur er valið; sérvalið
forritsletur hefur forgang og leyfistextinn heldur Consolas. Aðeins GDI eða Engin leturjöfnun er í boði.
Vistað ClearType-val notar GDI tímabundið og tekur aftur gildi þegar stíllinn er felldur niður. Með hefðbundnu
Windows-útliti birtast báðir þemavalkostir ómerktir og gráir og eru ekki notaðir; vistaðar stillingar haldast
óbreyttar.

Sleðinn **Hljóðstyrkur** á Vekjari stjórnar innri spilun hljóðskráa fyrir hverja græju og sýnir styrk í dB. Sjálfgefið **−18 dB** varðveitir upprunalegan styrk skrárinnar (**100%**). Til hægri magnast hljóðið; hámarkið **0 dB** er um **794%** af upprunalegri sveifluvídd. Lengst til vinstri er **−∞ dB** (þögn). Breytingar virka meðan á prófun stendur. Mögnun gildir um afkóðað hljóð, þar á meðal WAV, MP3, WMA, AAC, M4A og FLAC þegar Windows styður það. Eldri spilun skráa sem ekki er hægt að afkóða, svo sem MIDI, er takmörkuð við 100%.

Vikudagar vekjarans fylgja fyrsta vikudegi valinnar menningarstillingar forritsins. Vistaðir dagar halda merkingu sinni þegar tungumál breytist. Ef vekjari er virkjaður úr valmynd án valinna vikudaga opnast Vekjari-flipinn í stað þess að virkja vekjara sem getur ekki hringt.

**Núll fremst** býður **Já** (sjálfgefið), **Nei, halda plássi** og **Nei, án pláss**. **Nei, halda plássi** felur núllið en tekur frá raunverulega breidd þess í völdu letri, svo að aðrir tölustafir haldi stöðu sinni líka í misbreiðu letri. Skjáklukkur nota sjálfgefið hvítan texta á svörtum bakgrunni.

## Tímareiknivél

Opnaðu Tímareiknivél úr valmynd hvaða græju sem er eða valmynd táknsins á tilkynningasvæðinu. Flipinn Tímabil
reiknar mismun tveggja dagsetninga og tíma. Flipinn Sléttar tölur auðkennir sléttar tölur, endurtekna
tölustafi og mánaðarleg og árleg tímamót í dagatalinu frá völdu upphafi. Flipinn Vistaðar dagsetningar og
tímar gerir kleift að bæta við, breyta, raða og eyða dagsetningum og tímum með lýsingu. Dagsetningar og tímar
eru vistaðir sérstaklega í `%APPDATA%\FortSoft\CalClock\times.xml`. Útflutningur stillinga inniheldur þessar
færslur. Innflutningur varðveitir fyrirliggjandi færslur og sleppir aðeins færslum með sama UTC-tímapunkt og
nákvæmlega sömu heildarlýsingu, óháð tímabelti birtingar.

Dagatalið fylgir deginum í dag yfir miðnætti á tímabelti upphafstímans þegar dagurinn í dag er valinn og sýnilegur í mánaðarsýn. Handvirkt valin dagsetning og aðrar sýnir haldast óbreyttar; merkingin og línan Í dag uppfærast alltaf.

Hvert inntak hefur eigið tímabelti úr sama lista og í stillingum. Núverandi tímabelti Windows er sjálfgefið.
Vistaður er ótvíræður tímapunktur í UTC ásamt tímabelti birtingar. Breyting á tímabelti varðveitir
tímapunktinn. Veldu UTC-hliðrun fyrir endurtekna klukkustund; ekki er hægt að vista staðartíma sem er ekki
til. Klukkustundir mæla liðinn tíma; dagatalsútreikningar nota upphafstímabeltið. Núna notar kerfistíma
Windows án hliðrunar græju, birtan á völdu tímabelti.

Innflutningur tekur einnig við sérstakri XML-skrá með vistuðum dagsetningum og tímum; færslurnar eru
sameinaðar án þess að stillingum forritsins sé breytt.

Á flipanum Auðkenning geturðu valið reglurnar sem auðkenna dagsetningar í dagatalinu. Sjálfgefið eru
upphafsdagurinn (núllgildi), sléttar tölur sem enda á núllum, fyrstu níu heilu vikurnar og mánaðar- og
ársafmæli auðkennd. Hægt er að virkja endurtekna tölustafi 1–9 (til dæmis 11, 111 eða 66, 666) hvern fyrir
sig; sjálfgefið er slökkt á þeim.

Smelltu á dálkhaus til að raða vistuðum færslum eftir raunverulegu augnabliki eða lýsingartexta. Smelltu aftur
til að snúa röðinni við; ör sýnir röðunarstefnuna.

Staðsetning gluggans, virkur flipi, inntaksgögn útreikninga og val á auðkenningu eru vistuð með
forritsstillingum í skrásetningunni eða XML eftir völdum geymslumáta.

Útflutningur á flipanum með vistuðum dagsetningum og tímum vistar aðeins þessar færslur í sérstakri XML-skrá.
Innflutningur á þessum flipa les aðeins dagsetningar og tíma, einnig úr útfluttum stillingum, og sameinar við
núverandi færslur.

## Tími og vekjarar

Stafrænar klukkur, dagatalsspjöld og skjáklukkur bjóða **Samkvæmt tungumáli**, **12 klukkustundir** og **24 klukkustundir** undir **Tímasnið** á Almennt. **Samkvæmt tungumáli** er sjálfgefið: bandarísk og áströlsk enska nota til dæmis 12 klukkustundir, bresk enska 24. Handvirkt val helst þegar tungumál græjunnar breytist. Aðskiljarar og AM/PM-merki fylgja menningarstillingunni; án eigin merkja er **AM/PM** notað í 12 klukkustunda ham.

**AM/PM** er sjálfgefið valið. Afval felur merkið án þess að breyta 12 klukkustunda kerfinu. Skjáklukkur sýna merkið á sér línu undir tímanum eins og UTC. UTC notar alltaf 24 klukkustunda snið. Stillingin Núll fremst ræður áfram hvort núllið sé sýnt, falið með fráteknu plássi eða sleppt.

Nafngreind tímabelti sýna borgaralegan tíma valins staðar og fylgja sjálfkrafa sumartímareglum hans. Hliðrun við nafnið gildir fyrir núverandi dagsetningu og uppfærist þegar listinn opnast. Sérstakar **UTC**-færslur bjóða fasta hliðrun frá **UTC−12:00** til **UTC+14:00** í 15 mínútna skrefum, án sumartíma. Veldu staðbundið belti, annað nafngreint belti eða fasta UTC-hliðrun sjálfstætt fyrir hverja græju.

Nýjar græjur nota sjálfgefið **Núverandi tímabelti Windows**, sem fylgir núverandi tímabelti Windows og stillingu fyrir sjálfvirkan sumartíma. Græjur sem þegar eru til halda völdum tímabeltum. Þetta val ákvarðar tímabeltið; sameiginlegur tímagjafi Windows eða NTP er óháður því.

Hver græja getur notað hvaða Windows-tímabelti sem er og hliðrun með formerki á sniðinu `[-]HH:mm:ss.ff`. Samþjöppuð innsláttargildi eru túlkuð frá hægri, frá sekúndum.

Hliðrun er gagnleg til dæmis í útvarpsveri til að bæta upp seinkun í flutningsleið. Með því að flýta klukku versins um mælda seinkun nær tímamerkið hlustendum á tilætluðum tíma.

Tímafráviki græjunnar er bætt við UTC áður en tímanum er breytt yfir í tímabeltið. Það færir því einnig augnablikið þegar skipt er yfir í eða úr sumartíma. Klukka sem er tíu sekúndum á undan skiptir tíu sekúndum fyrr, en klukka sem er tíu sekúndum á eftir skiptir tíu sekúndum síðar. Vísar, stafrænn tími, dagsetningar dagatals, vekjarar og tímamerki nota tímann sem þannig fæst.

Tímaflipinn velur Windows-tíma eða NTP-þjóna fyrir allt forritið. NTP leiðréttir aðeins CalClock og breytir aldrei Windows. NTP er sjálfgefið; sjálfvirka safnið velur þjóna eftir svæði og síar mælingar eftir töf og frávikum.

Eftir samstillingu gengur klukka CalClock áfram óháð síðari breytingum á kerfistíma Windows. Ef samband rofnar eða skipt er um þjóna heldur klukkan áfram frá síðustu gildu samstillingu þar til nýtt svar berst; þetta ástand helst þar til forritinu er lokað.

Tímaflipinn skráir fyrirspurnir til NTP-þjóna frá ræsingu forritsins. Hver færsla inniheldur dagsetningu og staðartíma tölvunnar, þjón og stöðu. OK merkir gilt svar og θ tímamun þess frá kerfistíma Windows. ERR sýnir ástæðu bilunar og villukóða ef við á. Síðasta færsla í hópi fyrirspurna sýnir einnig reiknaðan tímamun Θ þegar nothæfar mælingar liggja fyrir.

Tímamunur er sýndur í millisekúndum með fjórum aukastöfum. Jákvætt gildi merkir að klukka þjónsins er á undan Windows; neikvætt gildi merkir að hún er á eftir. Θ tekur mið af samþykktum mælingum og birtist einnig í samstillingarstöðu.

Vista annál flytur færslur út sem CSV, með tímamun og villuupplýsingum. Færslur varðveitast ekki milli keyrslna; vistaðu þær áður en þú lokar forritinu ef þú vilt geyma þær.

Klukkugræjur styðja vekjara á völdum vikudögum; allir sjö eru virkir sjálfgefið. Vekjari birtir sína földu græju og færir hana fram fyrir aðra glugga án þess að breyta alltaf efst varanlega. WAV, MP3, WMA, MIDI, AAC, M4A og FLAC eru þekkt til innri spilunar einu sinni eða í sífellu; raunveruleg afkóðun ræðst af uppsettum margmiðlunarhlutum Windows. Aðrar skrár og skipanir eru sendar Windows ósamstillt. Vekjari getur líka kallað HTTP- eða HTTPS-slóð. Óháð þessu getur hann notað sex-pípa tímamerkið, þar sem fyrsta stutta pípið hljómar fimm sekúndum fyrir stilltan vekjaratíma.

Hljóðmerki vekjarans miðast við raunverulegt augnablik næstu vekjarahringingar eftir umreikning í tímabeltið og beitingu tímafráviks græjunnar. Þau hefjast fimm raunverulegum sekúndum fyrr, jafnvel þótt klukkan hoppi beint á stilltan vekjaratíma. Vekjaratími sem er sleppt að vori kveikir hvorki á vekjara né hljóðmerkjum. Þegar klukkustund er endurtekin að hausti hringja vekjarinn og hljóðmerki hans aðeins einu sinni fyrir sömu dagsetningu og stilltan tíma.

Ef CalClock er áfram í gangi virkjar hver græja síðasta missta vekjarann sinn einu sinni eftir svefn, dvala eða vinnslutöf, ásamt stilltum aðgerðum. Endurræsing CalClock endurtekur ekki gamla vekjara; misst tímamerki og forhljóð vekjarans eru ekki spiluð eftir á. „Vekja tölvuna fyrir vekjarann“ er sjálfgefið óvirkt og krefst þess að CalClock sé í gangi og að Windows og vélbúnaður styðji vakningu; hæg vakning getur komið í veg fyrir að forhljóð heyrist tímanlega.

Þegar Vekjari virkur er ekki valið eru aðrir stýrihlutir á Vekjari-flipanum óvirkir, en gildin varðveitast. Slökkt er á prófun sem er í gangi þegar vekjarinn er gerður óvirkur.

Prófa sýnir sjónræna merkingu og prófar skrá, skipun, hljóð og slóð fjarskriftu ósamstillt. Prófa er tiltækt þegar Vekjari virkur og Keyra skrá eða skipun eru valin og reiturinn fyrir skrá eða skipun er ekki auður. Prófunin spilar ekki tímamerki vekjarans. Stöðva prófun lýkur innri hljóðspilun og sjónrænni forskoðun.

Tímamerkisflipinn hefur gátreitinn Tímamerki virkt og valhnappa fyrir 1, 5, 10, 15, 20, 30 eða 60 mínútna bil samkvæmt sýndum tíma græjunnar. Í upphafi er slökkt á merkinu og klukkustundarbil valið. Þegar slökkt og kveikt er á Tímamerki í valmynd græjunnar helst bilið óbreytt. Valmyndin sýnir vekjaratímann og tímamerkjabilið innan sviga. 20 mínútna bilið gefur merki við :00, :20 og :40. Mynstrið er **Greenwich Time Signal (GTS)**: fimm stutt píp merkja síðustu fimm sekúndurnar og eitt lengra nákvæm tímamörk. Tímabelti, UTC, hliðrun og gildandi NTP-leiðrétting eru virt. Merki vekjarans og Tímamerki-flipinn eru óháð. Brot úr sekúndu í hliðrun eru virt og skarandi tónar græja, vekjara og prófana hljóma samfellt þar til síðustu skörun lýkur.

**Hljóð tímamerkis** á Forrit býður **Innbyggðan hljóðgjafa** (sjálfgefið) og **Kerfishljóð**. Valið gildir fyrir öll tímamerki, líka vekjara, og vistast almennt. Fyrir **Innbyggðan hljóðgjafa** sýnir **Hljóðstyrkur tímamerkis** styrkinn í dB fyrir allt forritið. Hægri endinn er **0 dB**, mesta óbjagaða sveifluvídd sínusbylgju; þögn er **−∞ dB**. Sjálfgefið gildi er **−18 dB**. Þegar prófun er stöðvuð getur tónn sem þegar er hafinn klárast. Önnur tímamerki sem hljóma samtímis geta haldið áfram. **Prófa** við **Hljóð tímamerkis** ræsir samfellda forskoðun og **Stöðva prófun** lýkur henni. Báðar aðferðir má prófa og prófunarstaðan vistast ekki. Að halda hljóðstyrkssleðanum niðri ræsir einnig forskoðun þar til músinni er sleppt, nema hnappaprófun sé í gangi. Spilun byrjar á næstu heilu sekúndu, með stuttum tón hverja sekúndu og löngum við :00, :05, :10 o.s.frv. Hljóðvalið er aðeins tiltækt ef kerfið styður báðar aðferðir.

**Hljóðúttak**

Hljóðúttak á flipanum Tímamerki velur tæki fyrir regluleg tímamerki hverrar græju sem styður hljóð. Tímabelti,
hliðrun og bil græjunnar breytast ekki. Val á hljóðgjafa og hljóðstyrkur tímamerkja eru áfram sameiginleg á
flipanum Forrit. Með Kerfishljóð er úttakslistinn grár og sýnir Sjálfgefið tæki Windows. Vistað tækjaval helst
óbreytt og birtist aftur þegar Innbyggður hljóðgjafi er valinn. Þegar tímamerkið er óvirkt er fyrirsögnin
Hljóðúttak einnig grá. Windows Vista notar hljóðgjafann sjálfkrafa.

**Sjálfgefið tæki Windows** fylgir núverandi sjálfgefnu hljóðúttaki Windows. Tæki sem er sérstaklega valið helst valið
þegar það er aftengt og birtist sem **Tæki ekki tiltækt**; tímamerki þess eru hljóðlaus þar til það er tiltækt eða
annað úttak er valið. Tækjalistinn uppfærist þegar hann er opnaður. Valið er vistað sérstaklega fyrir hverja græju í
skrásetningunni eða XML-stillingum.

Tímamerki eru sameinuð sjálfkrafa á hverju úttaki. Sérstaklega valið tæki og Sjálfgefið tæki Windows sem vísar
á sama tæki deila einu úttaki. Mismunandi tæki vinna sjálfstætt; sínusbylgjan, samfelldur fasi og upphaf og
endir tóna við núll haldast óbreytt. Hljóðúttak prófunar á flipanum Forrit vistar tækið fyrir prófanir
hljóðgjafans og forskoðun hljóðstyrks. Kerfishljóð sýnir Sjálfgefið tæki Windows í óvirkum valreit; vistað prófunartæki helst óbreytt. Hljóð vekjarans og
tímamerkin á undan honum nota sjálfgefið úttak Windows. Aðeins tímamerki vekjarans sameinast reglulegum
tímamerkjum á sama úttaki; hljóðskrár vekjarans eru spilaðar sérstaklega.

Vekjara og tímamerki má líka kveikja og slökkva á í samhengisvalmynd hljóðgræju. Vekjarafærslan sýnir tímann og virka daga ef ekki allir eru valdir. Þöggun gildir fyrir græjuna og samsvarar valinu á Almennt. Sjálfstætt Dagatal styður hvorki vekjara, tímamerki né þöggun. Skipunin á tilkynningasvæðinu er Þagga allt; `M` á hvaða græju sem er framkvæmir sömu almennu breytingu. Almenn afþöggun endurheimtir aðeins þær græjur sem síðasta almenna aðgerð þaggaði. Innri spilun heldur áfram hljóðlaust og verður aftur heyranleg þegar þöggun lýkur. Yfirstandandi píp getur klárast; seinni pípum er sleppt þar til hljóð er virkjað. Aðrar skipanir og fjarskriftur eru óbreyttar.

## Stillingar og valmyndir

Hver græjuvalmynd inniheldur viðeigandi skipanir — sýnileika, alltaf efst, sekúndur, stærð vísaklukku eða
dagsetningarafritunarsnið — og síðan `Raða á hnitanet`, Tímareiknivél, Stillingar, Hjálp, Um og Hætta.
Tilkynningavalmyndin telur upp græjurnar með raðnúmerum og síðan Sýna allt, Fela allt og Þagga allt.
Sérstaklega aðgreind skipun `Raða á hnitanet` kemur á undan forritsskipunum.

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

XML-innflutningur les og vistar stillingar strax í valinni vistun án þess að skipta um vistunargerð. Þöggun vistast fyrir hverja hljóðgræju.

## Smíði

Kröfur:

- Microsoft Visual Studio með MSVC v145-verkfærasafninu
- Windows SDK

Opnaðu `CalClock.slnx`, veldu `Release | x86` og smíðaðu lausnina. Keyrsluskráin verður:

```text
Release\CalClock.exe
```

Aðeins Win32/x86 er stutt. Verkefnið býður vísvitandi ekki x64-stillingu því samþætting við Windows-klukkustýringuna krefst x86-samhæfni.

Eftir smíði skaltu keyra `.\PackageRelease.ps1` til að búa til `CalClock-<version>-win32.zip` með forritinu og leyfi
þess.

Sjálfgefin gildi undirritunarfæribreyta eru einnig lesin úr umhverfisbreytum Windows-notandans: `BUILD_SIGNER_NAME`,
`BUILD_CERTIFICATE_THUMBPRINT`, `BUILD_SIGNTOOL_PATH`, `BUILD_TIMESTAMP_SERVER`. Bein viðföng á skipanalínu hafa
forgang.

## Leyfi

CalClock er í boði samkvæmt [MIT-leyfinu](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
