# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · **Lietuvių** · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

„CalClock“ – Win32/x86 programa, skirta „Windows Vista“ ir naujesnėms versijoms. Ji rodo nepriklausomai nustatomus slankiuosius laikrodžius ir kalendorius darbalaukyje bei veikia pranešimų srityje. Palaikomi iki 32 valdiklių ir 36 kalbų parinktys; programos ir kiekvieno valdiklio kalba pasirenkama atskirai.

Analoginiai laikrodžiai naudoja sistemos „Windows“ valdiklį `ClockWndMain`, automatiškai nustatydami galimus
dydžius ir sekundinės rodyklės palaikymą. Jei pasirinktas dydis nepalaiko sekundinės rodyklės, komanda
„Sekundės“ išjungiama, tačiau išsaugota parinktis lieka kitam palaikomam dydžiui.

## Valdymas

Vilkite laikrodį arba skydelį kairiuoju pelės mygtuku. Atskiras kalendorius velkamas už laisvos srities. Dešiniuoju mygtuku spustelėjus valdiklį arba pranešimų srities piktogramą atidaromas meniu. Kairysis piktogramos spustelėjimas paslepia matomus valdiklius; jei visi paslėpti, atkuriami tik paskutinį kartą paslėpti valdikliai.

## Valdikliai ir parametrai

Parametruose galima įtraukti, pašalinti ir dubliuoti analoginius bei skaitmeninius laikrodžius, kalendorius, kalendoriaus su laikrodžiu skydelius ir ekrano laikrodžius. Kiekvienas turi atskirą matomumą, Visada viršuje, kalbą, laiko juostą ir poslinkį [-]HH:mm:ss.ff. Ciferblatų dydžiai pasirenkami atskirai. Skaitmeniniams laikrodžiams galima nustatyti sekundes, pradinį nulį, šriftą, spalvas, nepermatomumą ir permatomą foną. Kalendorius palaiko savaičių numerius ir sekmadienį kaip pirmąją dieną; pavadinimai rodomi valdiklio kalba.

## Žadintuvas ir spartieji klavišai

Laikrodžiai ir skydeliai palaiko žadintuvą. Programa pati leidžia garso failą vieną kartą arba nuolat pagal kartojimo nuostatą; kiti failai ir komandos perduodami „Windows“. Spustelėjus skambantį ciferblatą ar ekraną, pasirinkus Stabdyti žadintuvą arba paspaudus Esc, sustabdomas vaizdinis signalas ir programos garsas. Dukart spustelėjus ciferblatą arba skaitmeninį ekraną perjungiamos sekundės. F1 atidaro žinyną, B – parametrus, Esc paslepia valdiklį, jei nestabdomas žadintuvas. Valdiklių padėtys įrašomos nuvilkus, dialogų – juos uždarius, o parametrai – pasirinktoje saugykloje. Pakartotinis paleidimas suaktyvina veikiantį egzempliorių; valdikliai paliekami artimiausioje pasiekiamoje darbo srities vietoje.

## Laiko įvedimas ir žadintuvo veiksmai

Žadintuvo laikas priima HH:mm su dvitaškiu, tašku, tarpu ar kitu skirtuku arba be skirtuko. Vienas ar du skaitmenys reiškia valandas, trys ar keturi – valandas ir minutes: 7, 12, 730, 0730 arba 7:30. Išėjus iš lauko nustatomas HH:mm formatas. Poslinkis skaitomas iš dešinės nuo sekundžių: 2 reiškia 00:00:02.00, 230 ir 0230 – 00:02:30.00, 12345 – 01:23:45.00. Su skirtukais dvi grupės reiškia minutes ir sekundes, trys – valandas, minutes ir sekundes, ketvirta – šimtąsias sekundės dalis; leidžiamas ženklas. Dienos po Žadintuvas įjungtas nustato suveikimo dienas; iš pradžių pasirinktos visos. Jų tvarka priklauso nuo programos kalbos, tačiau pakeitus kalbą įrašytos dienos nesikeičia.

Žadintuvas parodo paslėptą valdiklį ir iškelia jį į priekį nekeisdamas Visada viršuje visam laikui. Leisti laiko signalą pradeda pirmą trumpą toną likus penkioms sekundėms iki žadintuvo. Ši nuostata nepriklauso nuo skirtuko Signalas; vienalaikės sekos sujungiamos. Tikrinti įjungia ciferblato arba rėmelio mirksėjimą ir tikrina failą, komandą, garsą, nuotolinio scenarijaus HTTP/HTTPS adresą ir, jei pasirinkta, visą laiko signalą. Sustabdžius tikrinimą nutraukiamas jo vidinis garsas ir bandomasis signalas; sustabdžius žadintuvą – jo vidinis garsas. Nutildžius atkūrimas tęsiasi tyliai ir vėl girdimas įjungus garsą. Komandos ir nuotoliniai scenarijai nestabdomi.

Žadintuvo garsiniai signalai planuojami pagal tikrąjį artimiausio žadintuvo momentą po laiko juostos konvertavimo ir valdiklio poslinkio pritaikymo. Jie prasideda penkiomis tikromis sekundėmis anksčiau, net kai rodomas laikrodis peršoka tiesiai į žadintuvo laiką. Pavasarį praleistas žadintuvo laikas nesukelia nei žadintuvo, nei jo signalų. Rudenį pasikartojančią valandą žadintuvas ir jo signalai suveikia tik kartą tai pačiai datai ir nustatytam laikui.

Slankiklis Garsumas skirtuke Žadintuvas valdo šio valdiklio vidinį atkūrimą. Numatytieji −18 dB išlaiko pradinį failo lygį (100%). Slenkant dešinėn garsas stiprinamas; didžiausi 0 dB atitinka maždaug 794%. −∞ dB reiškia tylą. Pakeitimai girdimi ir tikrinant. MIDI ir failams, kurių negalima dekoduoti ir kurie atkuriami atsarginiu būdu, taikoma 100% riba.

## Pasirinkimas, klavišai ir datos kopijavimas

Parametrai įsimena paskutinį skirtuką, Įtraukti – paskutinį įtrauktą tipą. Pašalinti arba Del pašalina visus pasirinktus elementus pritaikius pakeitimus. Dukart spustelėjus elementą parodomas paslėptas valdiklis, pažymimas Matomas ir valdiklis trumpai paryškinamas. Valdiklio meniu Parametrai pasirenka jį sąraše. Spustelėjus kalendoriaus dieną pasirenkama data ir nukopijuojama į mainų sritį. Kiekvienas kalendorius turi atskirą formatą parametruose ir meniu. Visi 33 formatai prieinami visomis kalbomis; tekstiniai pavadinimai ir numatytoji Trumpoji data priklauso nuo valdiklio kalbos.

Insert perjungia dabartinio elemento pasirinkimą ir perkelia sąrašo žymeklį eilute žemyn. Ctrl+C kopijuoja valdiklius, Ctrl+V įtraukia kopijas sąrašo tvarka su pavadinimo priesaga programos kalba. Leidžiama iki 32 valdiklių. Kopijos įtraukiamos iš eilės iki ribos; dėl likusių parodomas pranešimas. Alt+0, Alt+1, Alt+2 ir Alt+3 pasirenka analoginio laikrodžio arba kalendoriaus su laikrodžiu pagrindinio ciferblato dydį nuo mažiausio iki didžiausio.

Atidarius nuostatas iš pranešimų srities piktogramos, vėl atveriamos paskutinio pasirinkto valdiklio nuostatos.

## Valdiklių išdėstymas

Išdėstyti tinkleliu išlaiko apytikslį rankinį išdėstymą, prikabina centrus prie artimiausių tinklo taškų ir pašalina persidengimą. Komandą iškvietęs valdiklis lieka vietoje. Valdiklio meniu veikia jo monitorių; pranešimų srities piktograma – kiekvieną monitorių atskirai. Pakartojimas išlaiko išdėstymą stabilų. Dukart spustelėjus parametruose valdiklis greitai mirksi šviesiai mėlynai; žadintuvas mirksi lėčiau raudonai. Išjungus Visada viršuje valdiklis nusiunčiamas už kitų langų. Viršutinis skydelio saitas grąžina kalendorių į šiandieną, apatinis atidaro klasikinius „Windows“ datos ir laiko parametrus. Įjungtas prikabinimas pritraukia velkamą valdiklį prie darbo srities krašto iki penkių pikselių atstumu. Keičiant dydį ryšys su tuo pačiu kraštu arba kraštų pora išlieka.

Kalendoriaus ir laikrodžio skydeliai virš apatinės nuorodos gali rodyti „Windows“ datos ir laiko pranešimus. Skirtuko **Bendra** parinktis **Datos ir laiko pranešimai** įjungta pagal numatytąsias nuostatas ir išsaugoma atskirai kiekvienam skydeliui. Kai aktualūs keli pranešimai, jie rodomi vienas po kito vertikaliai, kaip „Windows“. Jei parinktis išjungta arba aktualių pranešimų nėra, išlaikomas pradinis skydelio dydis ir išdėstymas, nepaliekant rezervuotos tuščios vietos.

Atskiro kalendoriaus Šiandienos eilutė skirtuke Išvaizda arba meniu rodo ar slepia apatinę eilutę. Pereiti į šiandieną pasirenka šiandienos datą ir atkuria mėnesio rodinį. Pasikeitus datai pagal valdiklio laiką šiandiena pasirenkama automatiškai išlaikant dabartinį rodinį.

## Išvaizda ir saugojimas

Išvaizdos pakeitimai iškart matomi pasirinkto valdiklio peržiūroje. `Numatytoji išvaizda` atkuria to tipo valdiklio numatytąsias reikšmes. Uždarant nuostatas su nepritaikytais pakeitimais, klausiama, ar juos išsaugoti. Šis įspėjimas įjungtas pagal numatytąsias nuostatas ir gali būti išjungtas skirtuke Programa. Skaitmeniniai laikrodžiai siūlo šriftą, glodinimą, spalvas, nepermatomumą, vidinę paraštę, kraštinės plotį ir permatomą foną. Laikrodžiai, kalendoriai ir skydeliai turi keturis bendrus kraštinių stilius; viengubai kraštinei galima pasirinkti spalvą. Skydelis turi atskirus viršutinės eilutės, laiko ir apatinės eilutės šriftus, pradinį nulį ir ciferblatų dydžius. Temos ir glodinimas nustatomi programai ir kiekvienam valdikliui. Pasirinktinius kalendoriaus šriftus galima naudoti su klasikine „Windows“ išvaizda arba išjungus programos ar valdiklio temas.

Parametrus galima eksportuoti į XML. Importas iškart įkelia ir įrašo parametrus į pasirinktą saugyklą nekeisdamas jos tipo. Automatinis XML yra %AppData%\FortSoft\CalClock\settings.xml. Įrašius XML pašalinamas HKCU\SOFTWARE\FortSoft\CalClock raktas; įrašymas į registrą pašalina automatinį XML.

Šrifto glodinimas siūlo ClearType, GDI ir Nėra. Pradinis nulis siūlo „Taip“ (numatyta), „Ne, palikti vietą“ ir „Ne, be vietos“. „Ne, palikti vietą“ slepia nulį, bet rezervuoja jo plotį pasirinktame šrifte; kiti skaitmenys nepajuda ir naudojant proporcinį šriftą. Ekrano laikrodžių centravimas įskaito rezervuotą vietą. UTC eilutė centruojama atskirai.

## Parametrai ir meniu

Programos kalba, šriftas, glodinimas, temos, saugykla, paleidimas su „Windows“ ir prikabinimas yra bendri skirtuko Programa parametrai. Pirmą kartą parenkama „Windows“ sąsajos kalba arba JAV anglų kalba, jei ji nepalaikoma. Valdiklio kalba, glodinimas ir temos taikomi tik jam.

Valdiklio meniu turi jam tinkamus matomumo, Visada viršuje, sekundžių, dydžio ir datos kopijavimo pasirinkimus, po jų – Išdėstyti tinkleliu, Parametrai, Žinynas, Apie ir Išeiti. Piktogramos meniu pateikia numeruotus valdiklius, Rodyti visus, Slėpti visus ir Nutildyti visus, tada atskirą tinklelio komandą. Rodant ar atkuriant valdiklis iškeliamas į priekį nekeičiant Visada viršuje. Pakartotinis paleidimas prireikus atkuria paskutinį kartą paslėptus valdiklius. Ciferblatų dydžiai ir sekundžių rodyklė priklauso nuo „Windows“. Žadintuvas ir Signalas perjungiami ir meniu, kuris rodo laiką, intervalą bei pasirinktas dienas, jei pažymėta ne visa savaitė. Nutildyti atitinka Nutildyta skirtuke Bendra. Nutildyti visus ir M nutildo visus valdiklius; pakartojus grąžinamas garsas tik tiems, kuriuos ši komanda nutildė. Įjungus žadintuvą be pasirinktos dienos atidaromas skirtukas Žadintuvas.

## Garsinis laiko signalas

Signalas atitinka Grinvičo laiko signalą (GTS): penki trumpi tonai paskutines penkias sekundes ir ilgas tonas tiksliai nustatytu metu. Skirtuke Signalas yra Laiko signalas įjungtas ir 1, 5, 10, 15, 20, 30 arba 60 minučių intervalai pagal valdiklio laiką. Iš pradžių išjungta, pasirinktas valandos intervalas. Perjungimas meniu išlaiko intervalą. Atsižvelgiama į UTC, juostą, poslinkį ir NTP. 20 minučių intervalas skamba :00, :20 ir :40. Nutildžius dabartinis tonas gali baigtis, kiti praleidžiami, o įjungus garsą girdimas tik kitas suplanuotas tonas. Atskiras Kalendorius neturi žadintuvo, laiko signalo ar nutildymo.

Skirtuko Programa Laiko signalo garsas siūlo Įtaisytasis generatorius (numatyta) ir Sistemos pyptelėjimas visiems valdikliams ir žadintuvams. Laiko signalo garsumas rodo generatoriaus lygį dB: dešinėje 0 dB – didžiausia neiškraipyta sinusoidės amplitudė, −∞ dB – tyla, numatyta −18 dB. Tikrinti pradeda nepertraukiamą peržiūrą, Stabdyti tikrinimą ją baigia. Tikrinami abu garsai; tikrinimas neįrašomas. Laikant slankiklį garsas taip pat leidžiamas iki pelės atleidimo, jei nevyksta mygtuko tikrinimas. Pradedama kitą pilną sekundę: trumpas tonas kas sekundę ir ilgas :00, :05, :10 ir toliau. Sustabdymas leidžia dabartiniam tonui baigtis; ilgas gali tęstis dar pusę sekundės. Įskaitomos poslinkių šimtosios dalys; persidengiantys tonai skamba nenutrūkstamai iki paskutinio persidengimo pabaigos toje pačioje garso išvestyje.

**Garso išvestis**

**Garso išvestis** skirtuke **Signalas** parenka įrenginį kiekvieno garsą palaikančio valdiklio reguliariems laiko
signalams. Valdiklio laiko juosta, poslinkis ir intervalas nesikeičia. Generatoriaus pasirinkimas ir signalo garsumas
tebėra bendri visai programai skirtuke **Programa**. Pasirinkus **Sistemos pyptelėjimas**, laukas lieka matomas, bet
papilkėja ir išsaugo pasirinktą įrenginį; **Įtaisytasis generatorius** jį vėl įjungia. Windows Vista generatorių
naudoja automatiškai.

**Numatytasis Windows įrenginys** seka dabartinę numatytąją Windows garso išvestį. Atskirai pasirinktas įrenginys
lieka pasirinktas ir atjungtas, o sąraše rodomas kaip **Įrenginys nepasiekiamas**; jo signalai nutyla, kol jis vėl
pasiekiamas arba pasirenkama kita išvestis. Įrenginių sąrašas atnaujinamas jį išskleidžiant. Pasirinkimas kiekvienam
valdikliui atskirai įrašomas į registrą arba XML parametrus.

Signalai automatiškai sujungiami kiekvienoje išvestyje. Atskirai pasirinktas įrenginys ir į tą patį įrenginį
nukreiptas **Numatytasis Windows įrenginys** naudoja vieną išvestį. Skirtingi įrenginiai veikia nepriklausomai;
išlaikoma sinusoidė, fazės tolydumas ir tonų pradžia bei pabaiga ties nuliu. Žadintuvai, įskaitant programoje
leidžiamus failus ir signalus prieš žadintuvą, bei visi bandymai tebenaudoja numatytąją Windows išvestį. Su
reguliariais signalais jie sujungiami tik bendroje išvestyje.

## Papildomi laikrodžiai

Kalendorius su laikrodžiu skirtuke Bendra gali rodyti iki dviejų papildomų laikrodžių su savais pavadinimais ir laiko juostomis. Kiekvienas tada rodo ir vietinę savaitės dieną. Dydis pasirenkamas atskirai skirtuke Išvaizda arba ciferblato kontekstiniame meniu. Papildomi laikrodžiai neturi sekundžių rodyklės. Įtraukimas, pašalinimas ir dydžio keitimas išlaiko prikabinimą prie darbo srities kraštų.

Tik dukart spustelėjus tiesiai pagrindinį ciferblatą perjungiama jo sekundžių rodyklė. Papildomų laikrodžių meniu yra tik dydžiai. Jie naudoja valdiklio kalbą, laiko formatą, šriftus ir poslinkį; skaitmeninis laikas rodomas be sekundžių.

## Laiko formatas ir laiko juostos

Laiko formatas skirtuke Bendra siūlo Pagal kalbą (numatyta), 12 valandų ir 24 valandos. Rankinis pasirinkimas išlieka pakeitus kalbą. Skyrikliai ir laiko žymos priklauso nuo valdiklio kalbos. AM/PM iš pradžių įjungta ir valdo tik 12 valandų formato žymą; jei kalba neturi savų žymų, naudojama AM/PM. Ekrano laikrodžiai žymą rodo atskiroje eilutėje po laiku. UTC visada naudoja 24 valandų formatą. Vardinės juostos laikosi vietinio ir vasaros laiko taisyklių; poslinkis atitinka dabartinę datą. Atskiros UTC parinktys yra pastovūs poslinkiai nuo −12:00 iki +14:00 kas 15 minučių be vasaros laiko.

Nauji valdikliai pagal numatytąją nuostatą naudoja **Dabartinė Windows laiko juosta**, kuri seka dabartinę Windows laiko juostą ir automatinio vasaros laiko nuostatą. Esami valdikliai išlaiko pasirinktas juostas. Šis pasirinkimas nustato laiko juostą; bendras Windows arba NTP laiko šaltinis lieka nepriklausomas.

Valdiklio poslinkis pritaikomas UTC laikui prieš konvertuojant į jo laiko juostą, todėl paslenka ir perėjimo į vasaros laiką arba iš jo momentą. Dešimčia sekundžių skubantis laikrodis persijungia dešimčia sekundžių anksčiau, o dešimčia sekundžių vėluojantis — dešimčia sekundžių vėliau. Rodyklės, skaitmeninis rodinys, kalendoriaus datos, žadintuvai ir laiko signalai naudoja gautą laiką.

## Laiko šaltinis ir NTP žurnalas

Skirtukas Laikas parenka „Windows“ sistemos laiką arba NTP serverius visai programai. NTP keičia tik „CalClock“ laiką; „Windows“ laikrodis nekeičiamas. Iki pirmo tinkamo atsakymo naudojamas sistemos laikas. NTP yra numatytasis pasirinkimas. Automatinis rinkinys pagal sistemos regioną parenka Čekijos ir Slovakijos serverius, PTB Europai arba pasaulinį rinkinį. Matavimai filtruojami pagal tinklo delsą ir nuokrypį nuo kitų atsakymų. Sinchronizuoti dabar iškart pradeda naują matavimą.

Po sinchronizavimo „CalClock“ laikrodis veikia nepriklausomai nuo vėlesnių „Windows“ sistemos laiko pakeitimų. Praradus ryšį ar pakeitus serverius tęsiama nuo paskutinio tinkamo sinchronizavimo iki naujo atsakymo; būsena išlaikoma iki programos uždarymo.

Laikas registruoja NTP užklausas nuo programos paleidimo. Įraše yra data, kompiuterio vietinis laikas, serveris ir būsena. OK žymi tinkamą atsakymą, θ – jo poslinkį nuo „Windows“ sistemos laiko. ERR pateikia priežastį ir galimą klaidos kodą. Paskutinis užklausų grupės įrašas rodo bendrą poslinkį Θ, jei yra tinkamų matavimų. Poslinkiai pateikiami milisekundėmis su keturiais skaitmenimis po kablelio: teigiamas reiškia, kad serveris skuba, neigiamas – atsilieka. Θ pagrįstas priimtais matavimais ir rodomas sinchronizavimo būsenoje. Įrašyti žurnalą eksportuoja CSV su poslinkiais ir klaidų informacija. Įrašai tarp paleidimų neišlieka; prireikus įrašykite prieš išeidami.

## Ekrano laikrodis

Skaitmeninis laikrodis gali užpildyti vieną ar kelis monitorius ir užtemdyti kitus. Šrifto dydis yra monitoriaus aukščio procentas; pasirenkamas šriftas, glodinimas, spalvos ir vidinė paraštė. UTC gali būti atskiroje eilutėje. Numatytasis vaizdas – baltas tekstas juodame fone. Kol atidaryti parametrai, rodomas mažas perkeliamas peržiūros langas, išlaikantis monitoriaus proporcijas ir įrašomą padėtį. Tinklelis šio tipo neperkelia. Esc paslepia laikrodį ir pašalina užtemdymą net atidarius parametrus.

Pelės žymeklis virš ekrano laikrodžio ir užtemdytų monitorių pasislepia po trumpos neveiklos ir vėl pasirodo pajudinus pelę. Virš mažos peržiūros jis lieka matomas.

## Kompiliavimas ir pakavimas

Reikalingi „Microsoft Visual Studio“ su MSVC v145 įrankių rinkiniu ir „Windows SDK“. Atidarykite `CalClock.slnx`, pasirinkite `Release | x86` ir sukompiliuokite sprendimą. Vykdomasis failas sukuriamas `Release\CalClock.exe`. Palaikoma tik Win32/x86 konfigūracija, nes integracija su „Windows“ laikrodžio valdikliu reikalauja x86 suderinamumo.

Po kompiliavimo `.\PackageRelease.ps1` sukuria `CalClock-<version>-win32.zip`; versija nuskaitoma iš `Release\CalClock.exe`. Archyvo šaknyje yra `CalClock.exe` ir `license.txt`. Neprivalomi pasirašymo parametrai `-SignerName`, `-SignToolPath` ir `-TimestampServer` nurodomi paleidžiant. Esamas galiojantis Authenticode parašas tikrinamas ir nekeičiamas. Ankstesni „CalClock“ ZIP paketai pašalinami kiekvieno paleidimo pradžioje; pasirašymo arba tikrinimo klaida sustabdo pakavimą.

Numatytosios pasirašymo parametrų reikšmės taip pat skaitomos iš Windows vartotojo aplinkos kintamųjų:
`BUILD_SIGNER_NAME`, `BUILD_CERTIFICATE_THUMBPRINT`, `BUILD_SIGNTOOL_PATH`, `BUILD_TIMESTAMP_SERVER`. Aiškiai pateikti
komandinės eilutės argumentai turi pirmenybę.

## Licencija

„CalClock“ platinamas pagal [MIT licenciją](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
