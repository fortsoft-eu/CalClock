# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk](README.nb-NO.md) · [Svenska](README.sv-SE.md) · **Suomi** · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md)

CalClock on natiivi Win32/x86-sovellus Windows Vistalle ja uudemmille Windows-versioille. Se näyttää työpöydällä vapaasti sijoitettavia kelloja ja kalentereita, joiden asetukset ovat toisistaan riippumattomia. Sovellus toimii ilmoitusalueella eikä tarvitse jatkuvasti avointa ohjausikkunaa.

## Ominaisuudet

- Enintään 32 erikseen määritettävää pienoisohjelmaa
- Oma kieli, aikavyöhyke, aikasiirtymä, näkyvyys ja aina päällimmäisenä -asetus jokaiselle pienoisohjelmalle
- Windowsin `ClockWndMain`-ohjaimeen perustuvat analogiset kellot, käytettävissä olevien kokojen automaattinen tunnistus ja sekuntiviisarin tuki
- Digitaaliset kellot, joissa voi valita fontit, värit, peittävyyden, sisämarginaalit, reunukset, etunollan ja läpinäkyvän taustan
- Windowsin omat kalenterit, joissa on päivämäärän valinta, neljä reunustyyliä, säädettävä reunusväri, viikkonumerot, viikon ensimmäisen päivän valinta ja 33 kopiointimuotoa
- Kalenterin ja kellon yhdistelmäpaneelit, joissa voi olla kaksi nimettyä lisäkelloa omilla aikavyöhykkeillään, erilliset kellotaulujen koot, neljä reunustyyliä, säädettävä väri, UTC-teksti, etunolla ja oma fontti jokaiselle tekstiriville
- Herätykset, joissa voi valita viikonpäivät, visuaalisen ilmoituksen, sisäisen äänentoiston, toiston, paikalliset komennot ja HTTP/HTTPS-komentosarjakutsut
- Kellokohtaiset aikamerkit 1, 5, 10, 15, 20, 30 tai 60 minuutin välein; samanaikaiset merkit yhdistetään yhdeksi sarjaksi
- Kellokohtainen Mykistä-komento ja valittava Mykistä kaikki -komento ilmoitusalueella
- Valinnainen automaattinen käynnistys Windowsin mukana
- Valinnainen tarttuminen työalueen reunoihin viiden pikselin etäisyydeltä vedettäessä, oletuksena käytössä; reunakiinnitys säilyy koon muuttuessa
- NTP-synkronointi muuttamatta Windowsin järjestelmäkelloa
- NTP-esiasetukset Tšekille ja Slovakialle, PTB:lle, Ubuntu/NTP Poolille sekä omille palvelimille
- Asetusten tallennus rekisteriin tai XML-tiedostoon sekä XML-tuonti ja -vienti
- Ohjaus ilmoitusalueelta ja viimeksi piilotettujen pienoisohjelmien palautus
- Pienoisohjelmien tunnistus ja vakaa, päällekkäisyydet estävä ruudukkoasettelu
- Ulkoasun välitön esikatselu, muutosten peruminen ja pienoisohjelmakohtainen oletusulkoasu
- Sovelluksen ja pienoisohjelmien fontit, visuaaliset tyylit sekä ClearType-, GDI- tai ei lainkaan fontin pehmennystä
- Käyttöliittymät tšekiksi, amerikan-, britannian- ja australianenglanniksi, saksaksi, ranskaksi, espanjaksi, italiaksi, portugaliksi, puolaksi, slovakiksi, tanskaksi, suomeksi, islanniksi, norjaksi, ruotsiksi ja turkiksi

## Pienoisohjelmatyypit

| Pienoisohjelma | Kuvaus |
| --- | --- |
| Analoginen kello | Vapaasti sijoitettava Windows-kellotaulu, jonka koot ja valinnainen sekuntiviisari määräytyvät Windows-version mukaan |
| Digitaalinen kello | Muokattava digitaalinen näyttö, jossa voi käyttää UTC-tekstiä, etunollaa, reunuksia ja läpinäkyvää taustaa |
| Kalenteri | Siirrettävä Windowsin kuukausikalenteri, jossa on päivämäärän valinta, muokattavat reunukset ja kopiointimuodot |
| Kalenteri ja kello | Yhdistelmäpaneeli, jossa on kalenteri, analoginen kello, muokattavat tekstirivit, UTC-näyttö ja reunukset |
| Näyttökello | Digitaalinen kello, joka täyttää yhden tai useamman valitun näytön; valinnainen pimennys ja UTC omalla rivillään |

Ensimmäisellä käynnistyskerralla CalClock valitsee kielen Windowsin käyttöliittymäkielen mukaan. Jos kieltä ei tueta, käytetään amerikanenglantia. Oletuksena luodaan yksi näkyvä analoginen kello. Jokainen pienoisohjelma säilyttää sijaintinsa ja asetuksensa käynnistysten välillä. Kun Asetukset on avoinna, näyttökello esitetään aina siirrettävänä esikatseluna, jonka kuvasuhde vastaa valittua näyttöä. `Esc` piilottaa näyttökellon ja poistaa pimennyksen myös Asetusten ollessa käytössä. Osoitin piilotetaan lyhyen toimettomuuden jälkeen näyttökellojen ja pimennettyjen näyttöjen päällä, ja se palaa hiirtä liikutettaessa. Pienen asetusikkunan esikatselun päällä osoitin pysyy näkyvissä.

## Käyttö

- Vedä kelloa tai paneelia hiiren vasemmalla painikkeella.
- Vedä erillistä kalenteria sen vapaasta alueesta.
- Avaa pikavalikko napsauttamalla pienoisohjelmaa tai ilmoitusalueen kuvaketta hiiren oikealla painikkeella.
- Ilmoitusalueen kuvakkeen vasen napsautus piilottaa näkyvät pienoisohjelmat. Jos kaikki ovat piilossa, seuraava napsautus palauttaa vain viimeksi piilotetut.
- Kellotaulun kaksoisnapsautus vaihtaa sekuntien näyttöä. Yhdistelmäpaneelissa vain suoraan pääkellotauluun osuva kaksoisnapsautus vaihtaa sekuntiviisaria. Lisäkelloilla ei ole sekuntiviisaria.
- `F1` avaa Ohjeen, `B` Asetukset, `M` vaihtaa yleistä mykistystä ja `Esc` piilottaa pienoisohjelman tai pysäyttää aktiivisen herätyksen.
- Valitse pääkellotaulun koko pienimmästä suurimpaan näppäimillä `Alt+0`, `Alt+1`, `Alt+2` tai `Alt+3` Analoginen kello- tai Kalenteri ja kello -pienoisohjelmassa.
- Asetusten luettelossa tehty kaksoisnapsautus näyttää pienoisohjelman tarvittaessa, valitsee `Näkyvissä` ja merkitsee sen hetkeksi työpöydällä.
- Asetusten avaaminen pienoisohjelman pikavalikosta valitsee kyseisen pienoisohjelman heti.
- Käytä `Ctrl`- tai `Shift`-näppäintä monivalintaan, `Ctrl+A` valitsee kaikki ja `Del` poistaa valitut. `Insert` vaihtaa nykyisen rivin valintaa ja siirtää luettelokohdistimen seuraavalle riville, kuten Total Commanderissa.
- Kaikki luettelon pikanäppäimet toimivat myös Poista- ja Monista-painikkeiden ollessa kohdistettuina. Pikanäppäin siirtää kohdistuksen luetteloon ja suorittaa toiminnon. `Ctrl+C` kopioi valitut pienoisohjelmat, ja `Ctrl+V` lisää kopiot loppuun luettelon järjestyksessä. Kopioihin sisältyvät kaikki asetukset, ja nimeen lisätään sovelluksen kielen mukainen pääte. Monista tekee saman suoraan. Enimmäismäärä on 32 pienoisohjelmaa. Jos kaikki kopiot eivät mahdu, mahtuvat kopiot lisätään järjestyksessä ja lopuista näytetään ilmoitus.
- `Ctrl+A` tai tekstikentän kolmoisnapsautus valitsee kaiken tekstin.

Kun valittuna on useita pienoisohjelmia, niiden Yleiset-, Ulkoasu-, Herätys- ja Aikamerkki-ohjaimet poistetaan käytöstä. Yleiset Aika- ja Sovellus-välilehdet ovat edelleen käytettävissä. Asetukset muistaa viimeksi avatun välilehden ja viimeksi lisätyn pienoisohjelmatyypin. Pienellä työalueella ikkuna tarjoaa tarpeen mukaan vaaka- tai pystysuuntaisen vierityksen.

Kalenterin päivämäärät voi kopioida 33 muodossa: paikallisina, lajiteltavina, päivä tai kuukausi ensin, tekstimuotoisina ja viikonpäivän kanssa. Kaikki muotoilumallit ovat käytettävissä jokaisella käyttöliittymäkielellä. Paikallinen lyhyt oletusmuoto seuraa pienoisohjelman kieltä, samoin kuukausien ja viikonpäivien nimet. Luettelo näyttää mallin ja ajantasaisen esimerkin.

Kalenteri- ja kellopaneeli voi näyttää kaksi lisäkelloa. Ota kumpikin käyttöön Yleiset-välilehdellä ja valitse nimi sekä aikavyöhyke. Nimetyt vyöhykkeet seuraavat omia kesäaikasääntöjään, kiinteät UTC-siirtymät pysyvät muuttumattomina. Lisäkellojen ollessa käytössä jokainen kello näyttää paikallisen viikonpäivän ajan alapuolella. Ulkoasun kolme kokoluetteloa säätävät järjestyksessä pääkelloa, Kelloa 1 ja Kelloa 2. Lisäkellotaulun oikea napsautus avaa kokovalinnan. Lisäkellot jättävät sekunnit aina pois ja käyttävät pienoisohjelman kieltä, aikamuotoa, fontteja ja aikasiirtymää. Kellojen lisääminen, poistaminen ja koon muuttaminen säilyttää kiinnityksen samoihin työalueen reunoihin.

Paneelin yläpäivämäärä on linkki, joka palauttaa kalenterin tähän päivään. Alareunan aikavyöhyketeksti avaa Windowsin perinteiset päivämäärä- ja aika-asetukset. Molemmat linkit saavutetaan `Tab`-näppäimellä, näyttävät kohdistuskehyksen ja toimivat näppäimistöllä. Kalenteri säilyy täysin vuorovaikutteisena, mutta tässä yhdistelmässä tarpeeton Tänään-rivi jätetään pois.

`Järjestä ruudukkoon` sijoittaa näkyvät työpöydän pienoisohjelmat vakaaseen ruudukkoon ilman päällekkäisyyksiä säilyttäen likimain niiden käsin asetetun sijainnin. Komennon oman valikkonsa kautta käynnistänyt pienoisohjelma pysyy paikallaan; ilmoitusalueen komento järjestää jokaisen näytön erikseen. Näyttökellot eivät kuulu järjestelyyn.

## Ulkoasu

Erillisissä kalentereissa **Tänään-rivi** pikavalikossa tai Ulkoasu-välilehdellä säätää alarivin näkyvyyttä. Se on oletuksena valittuna; valinnan poistaminen piilottaa rivin ja pienentää kalenteria. Valinta tallennetaan pienoisohjelmakohtaisesti. **Siirry tähän päivään** pysyy käytettävissä ja palauttaa kuukausinäkymän. Päivämäärän vaihtuessa pienoisohjelman ajan mukaan kalenteri valitsee tämän päivän automaattisesti ja säilyttää nykyisen näkymän.

Ulkoasumuutokset näkyvät heti valitussa pienoisohjelmassa. `Peruuta` palauttaa muutokset, joita ei ole otettu käyttöön; `Oletusulkoasu` palauttaa kyseisen tyypin oletusasetukset.

Digitaaliset kellot, kalenterit ja yhdistelmäpaneelit jakavat neljä reunustyyliä. Yksinkertaisen reunuksen väriä voi muuttaa; leveys on säädettävissä sitä tukevissa pienoisohjelmissa. Läpinäkyvät digitaaliset kellot tarjoavat samat tyylit kuin peittävät. Fontti-ikkunoissa näytetään vain kohteelle sopivat valinnat, ilman käyttämätöntä esikatselua tai tehosteita. Sovelluksen ja kalenterin fonteista puuttuu kokovalinta, mutta digitaalisissa ja paneeliteksteissä se on mukana. Windows-kalenteri hyväksyy oman fontin vain, jos visuaaliset tyylit on poistettu käytöstä kalenterilta tai koko sovellukselta.

Sovelluksen kieli, käyttöliittymäfontti, pehmennys, visuaaliset tyylit, tallennus, Windows-käynnistys ja reunoihin tarttuminen ovat yleisiä asetuksia Sovellus-välilehdellä. Myös ajan lähde on yleinen. Pienoisohjelman kieli, pehmennys, tyylit, vyöhyke, siirtymä, herätys ja aikamerkki asetetaan erikseen. Uuden sovelluskielen käyttöönotto luo avoimen Asetukset-ikkunan heti uudelleen sillä kielellä. Pehmennyksessä on **ClearType**, **GDI** ja **Ei mitään**. Ulkoasussa pehmennys ja teemojen poisto ovat kaikilla tyypeillä samassa paikassa ja **Oletusulkoasu** niiden alapuolella.

Herätyksen **Äänenvoimakkuus**-liukusäädin säätää sisäisesti toistettavia tiedostoja pienoisohjelmakohtaisesti ja näyttää tason dB-yksiköissä. Oletus **−18 dB** säilyttää tiedoston alkuperäisen tason (**100%**). Oikealle siirtäminen vahvistaa ääntä; enimmäistaso **0 dB** vastaa noin **794%** alkuperäisestä amplitudista. Vasemmassa ääriasennossa **−∞ dB** tarkoittaa hiljaisuutta. Muutokset vaikuttavat äänitestin aikana. Säädin ei ole käytössä ulkoisessa sovelluksessa avattaville tiedostoille. Vahvistus koskee purettua ääntä, kuten WAV-, MP3-, WMA-, AAC-, M4A- ja FLAC-tiedostoja Windowsin tukemissa muodoissa. Vanhempi toistotapa tiedostoille, joita ei voida purkaa, kuten MIDI, rajoittuu 100%:iin.

Herätyksen viikonpäivät seuraavat sovelluksen valitun kulttuurin ensimmäistä viikonpäivää. Tallennetut päivät säilyttävät merkityksensä kieltä vaihdettaessa. Jos herätys otetaan käyttöön valikosta ilman valittuja päiviä, avataan kyseisen pienoisohjelman Herätys-välilehti sen sijaan, että käyttöön tulisi herätys, joka ei voi soida.

Digitaalikellon reunuksen oletusleveys on nolla. **Etunolla** tarjoaa **Näytä** (oletus), **Varaa tila** ja **Ei tilaa**. **Varaa tila** piilottaa nollan mutta varaa sen todellisen leveyden valitussa fontissa, joten muut numerot pysyvät paikoillaan myös suhteellisella fontilla. Vapaasti sijoitettavat digitaalikellot tasaavat ajan vasemmalle ja säilyttävät kiinteän koon ajan kuluessa. Näyttökellot keskittävät kiinteän aika-alueen, joka on mitoitettu fontin ja muodon mukaan ja varaa tilan kahdelle tuntinumerolle. Ajan muuttuminen ei keskitä tai muuta tekstin kokoa uudelleen. AM/PM- tai UTC-rivi keskitetään erikseen. Näyttökellon oletuksena on valkoinen teksti mustalla taustalla.

## Aika ja herätykset

Digitaalikellot, yhdistelmäpaneelit ja näyttökellot tarjoavat Yleiset-välilehden **Aikamuodossa** valinnat **Kielen mukaan**, **12 tuntia** ja **24 tuntia**. Oletus **Kielen mukaan** seuraa pienoisohjelman kieltä: esimerkiksi amerikan- ja australianenglanti käyttävät 12 tuntia, britannianenglanti 24. Käsin tehty valinta säilyy kieltä vaihdettaessa. Erottimet ja AM/PM-tunnukset seuraavat kulttuuria; ilman omia tunnuksia käytetään 12 tunnin tilassa **AM/PM**-tunnuksia.

**AM/PM** on oletuksena valittu. Valinnan poistaminen piilottaa tunnuksen muuttamatta 12 tunnin jaksoa. Valinta ei ole käytettävissä 24 tunnin tilassa tai ilman digitaalista aikanäyttöä. Näyttökellot näyttävät tunnuksen omalla rivillään ajan alla, kuten UTC:n. **UTC käyttää aina 24 tunnin muotoa**; jakson ja AM/PM:n ohjaimet ovat UTC:ssä poissa käytöstä, mutta arvot säilyvät paikalliseen aikaan paluuta varten. Etunollan asetus määrää edelleen, näytetäänkö nolla, piilotetaanko se varaten tila vai jätetäänkö se pois.

Nimetyt aikavyöhykkeet näyttävät valitun paikan virallisen ajan ja seuraavat automaattisesti sen kesäaikasääntöjä. Nimen vieressä oleva siirtymä vastaa nykyistä päivämäärää ja päivittyy luetteloa avattaessa. Erilliset **UTC**-valinnat tarjoavat kiinteät siirtymät välillä **UTC−12:00**–**UTC+14:00** 15 minuutin välein ilman kesäaikaa. Jokaiselle pienoisohjelmalle voi valita erikseen paikallisen vyöhykkeen, muun nimetyn vyöhykkeen tai kiinteän UTC-siirtymän.

Jokainen pienoisohjelma voi käyttää mitä tahansa Windows-aikavyöhykettä ja etumerkillistä siirtymää muodossa `[-]HH:mm:ss.ff`. Tiivis syöte tulkitaan oikealta alkaen sekunneista.

Aikasiirtymä on hyödyllinen esimerkiksi lähetysstudiossa siirtotien viiveen kompensoimiseen. Kun studiokelloa aikaistetaan mitatun viiveen verran, aikamerkki saavuttaa kuulijat tarkoitettuna hetkenä.

CalClock voi käyttää Windowsin järjestelmäaikaa tai NTP-palvelimilta saatua sovelluskohtaista korjausta. Valinta koskee kaikkia pienoisohjelmia. Synkronointi ei koskaan muuta Windows-kelloa. Jos NTP-yhteys katkeaa onnistuneen synkronoinnin jälkeen, viimeinen korjaus pysyy aktiivisena prosessin muistissa. Palvelinten vaihtaminenkin säilyttää voimassa olevan korjauksen uuden vastauksen saamiseen asti.

Kellopienoisohjelmat tukevat herätyksiä erikseen valittuina viikonpäivinä; kaikki seitsemän ovat oletuksena käytössä. Herätys näyttää piilotetun pienoisohjelmansa ja nostaa sen muiden ikkunoiden eteen muuttamatta aina päällimmäisenä -asetusta pysyvästi. WAV, MP3, WMA, MIDI, AAC, M4A ja FLAC tunnistetaan sisäiseen kerta- tai toistuvaan soittoon; todellinen purkutuki riippuu Windowsiin asennetuista multimediakomponenteista. Muut tiedostot ja komennot välitetään Windowsille asynkronisesti. Herätys voi myös kutsua HTTP- tai HTTPS-osoitetta. Näistä riippumatta se voi käyttää kuuden piippauksen aikamerkkiä, jonka ensimmäinen lyhyt piippaus alkaa viisi sekuntia ennen asetettua herätysaikaa.

Suorita tiedosto tai komento ottaa käyttöön kentän, Selaa- ja Testaa-painikkeet sekä toiston. Testaus ja toisto edellyttävät myös ei-tyhjää kenttää, mutta käynnissä olevan testin voi aina pysäyttää. Testaa näyttää visuaalisen ilmoituksen ja kokeilee tiedostoa, komentoa, ääntä ja etäkomentosarjan osoitetta asynkronisesti. Jos herätyksen aikamerkki on valittu, se toistaa myös kaikki kuusi piippausta; Lopeta testi päättää sisäisen äänen ja aikamerkin esikatselun.

Aikamerkki-välilehdellä on Äänimerkki käytössä -valintaruutu ja valintanapit 1, 5, 10, 15, 20, 30 tai 60 minuutin väleille pienoisohjelman näyttämän ajan mukaan. Äänimerkki on aluksi pois käytöstä, ja valittuna on tunnin väli. Aikamerkin poistaminen käytöstä ja ottaminen uudelleen käyttöön pienoisohjelman valikosta säilyttää aikavälin. Valikko näyttää herätysajan ja aikamerkin välin sulkeissa. 20 minuutin väli tarkoittaa :00, :20 ja :40 kyseistä aikaa. Malli on **Greenwich Time Signal (GTS)**: viisi lyhyttä piippausta merkitsee viisi viimeistä sekuntia ja pidempi piippaus täsmällisen rajan. Vyöhykkeet, UTC, siirtymät ja nykyinen NTP-korjaus huomioidaan. Herätyksen aikamerkki ja Aikamerkki-välilehti ovat riippumattomia; aikataulujen osuessa yhteen CalClock toistaa yhden yhteisen sarjan. Sekunnin osien siirtymät huomioidaan. Päällekkäiset pienoisohjelmien, herätysten ja testien äänet soivat keskeytyksettä viimeisen päällekkäisyyden loppuun asti.

Sovellus-välilehden **Aikamerkin ääni** tarjoaa **Sisäisen generaattorin** (oletus) ja **Järjestelmäpiippauksen**. Valinta koskee kaikkia aikamerkkejä, myös herätyksiä, ja tallennetaan yleisiin asetuksiin. **Sisäisen generaattorin** **Aikamerkin äänenvoimakkuus** näyttää koko sovelluksen tason dB-yksiköissä. Oikea ääriasento **0 dB** on suurin särötön siniaallon amplitudi; hiljaisuus on **−∞ dB**. Oletus on **−18 dB**. Desibeliasteikon keskellä on −18 dB. Generaattori aloittaa ja lopettaa äänet nollakohdassa myös testiä pysäytettäessä. Käynnissä oleva piippaus saa päättyä; pitkä piippaus voi kestää vielä puoli sekuntia. **Testaa** kohdassa **Aikamerkin ääni** aloittaa jatkuvan esikatselun ja **Lopeta testi** päättää sen. Molempia tapoja voi testata, eikä testin tilaa tallenneta. Myös äänenvoimakkuussäätimen pitäminen painettuna soittaa esikatselua hiiren vapauttamiseen asti, ellei painikkeella käynnistetty testi ole jo käytössä. Toisto alkaa seuraavalla tasasekunnilla: lyhyt ääni joka sekunti ja pitkä kohdissa :00, :05, :10 jne. Esikatselu ja samanaikaiset pienoisohjelmien tai herätysten merkit jakavat yhden äänen. **Järjestelmäpiippauksessa** vain äänenvoimakkuussäädin on poissa käytöstä. Äänen valinta on mahdollinen vain järjestelmän tukiessa molempia tapoja.

Herätyksen ja aikamerkin voi vaihtaa myös ääntä tukevan pienoisohjelman pikavalikossa. Herätyskohta näyttää ajan ja aktiiviset päivät, jos kaikkia päiviä ei ole valittu. Mykistä koskee kyseistä pienoisohjelmaa ja vastaa Yleiset-välilehden valintaa. Erillisessä Kalenterissa ei ole herätystä, aikamerkkiä eikä mykistystilaa, joten nämä komennot puuttuvat tai ovat poissa käytöstä. Ilmoitusalueen komento on Mykistä kaikki; `M` missä tahansa pienoisohjelmassa tekee saman yleisen vaihdon. Yleinen mykistyksen poisto palauttaa vain edellisen yleisen toiminnon mykistämät pienoisohjelmat. Sisäinen ääni jatkuu hiljaisena ja kuuluu taas mykistyksen poistuttua. Jo alkanut piippaus voi päättyä; seuraavat jätetään pois, kunnes ääni otetaan käyttöön. Muut komennot ja etäkomentosarjat eivät muutu.

## Asetukset ja valikot

`Tallenna` ottaa muutokset käyttöön ja sulkee Asetukset; `Käytä` ottaa ne käyttöön sulkematta ikkunaa; `Peruuta` hylkää käyttämättömät muutokset, myös ulkoasun esikatselun. Enter käynnistää `Tallenna`-toiminnon, Esc `Peruuta`-toiminnon.

Jokaisessa pienoisohjelmavalikossa on tyypille sopivat komennot — näkyvyys, aina päällimmäisenä, sekunnit, analoginen koko tai päivämäärän kopiointimuoto — ja sitten `Järjestä ruudukkoon`, Asetukset, Ohje, Tietoja ja Lopeta. Ilmoitusalueen valikko luettelee pienoisohjelmat järjestysnumeroineen ja tarjoaa Näytä kaikki, Piilota kaikki ja Mykistä kaikki. Erikseen ryhmitelty `Järjestä ruudukkoon` seuraa ennen sovelluksen komentoja.

Näyttäminen tai palauttaminen nostaa pienoisohjelmat muiden ikkunoiden eteen muuttamatta aina päällimmäisenä -asetusta. CalClock varmistaa ainakin yhden näkyvän pienoisohjelman käynnistyksen jälkeen. Toinen käynnistys aktivoi olemassa olevan sovellusinstanssin ja palauttaa viimeksi piilotetut pienoisohjelmat, jos yhtään ei näy. Ilmoituskuvake rekisteröidään automaattisesti uudelleen Resurssienhallinnan käynnistyessä uudelleen. Jos `ClockWndMain` ei tue sekuntiviisaria valitussa koossa, Sekunnit-komento poistuu käytöstä, mutta valinta säilytetään muuta tuettua kokoa varten.

## Asetusten tallennus

Oletuksena asetukset tallennetaan kohtaan:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

XML-tallennus otetaan käyttöön Asetuksissa. Sen tiedosto on:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Onnistuneen XML-tallennuksen jälkeen CalClock poistaa sovellustilansa rekisteristä. Paluu rekisteriin poistaa vastaavasti automaattisen XML-tiedoston ja tyhjät CalClock-kansiot. XML-tuonti lukee ja tallentaa asetukset heti valittuun tallennuspaikkaan muuttamatta tallennustapaa. Mykistys tallennetaan kullekin ääntä tukevalle pienoisohjelmalle erikseen. Windows-käynnistys tallennetaan arvona `CalClock` nykyisen käyttäjän tavalliseen `Run`-rekisteriavaimeen.

## Kääntäminen

Vaatimukset:

- Microsoft Visual Studio ja MSVC v145 -työkalut
- Windows SDK

Avaa `CalClock.slnx`, valitse `Release | Win32` ja käännä ratkaisu. Suoritettava tiedosto luodaan polkuun:

```text
Release\CalClock.exe
```

Vain Win32/x86-kokoonpanoa tuetaan. Projekti ei tarkoituksella tarjoa x64-kokoonpanoa, koska Windows-kello-ohjaimen integrointi vaatii x86-yhteensopivuuden.

## Lisenssi

CalClock on saatavilla [MIT-lisenssillä](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
