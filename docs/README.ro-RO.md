# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · **Română** · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock este o aplicație nativă Win32/x86 pentru Windows Vista și versiuni ulterioare, care afișează pe desktop ceasuri și calendare flotante configurabile independent. Rulează în zona de notificare și acceptă până la 32 de widgeturi și 36 de variante de limbă; limba aplicației și a fiecărui widget se aleg separat.

## Comenzi

Glisați ceasul sau panoul cu butonul stâng al mouse-ului. Un calendar separat se glisează din zona liberă. Un clic dreapta pe widget sau pe pictograma din zona de notificare deschide meniul. Un clic stânga pe pictogramă ascunde widgeturile vizibile; dacă toate sunt ascunse, le restabilește numai pe cele ascunse ultima dată.

## Widgeturi și setări

În Setări puteți adăuga, elimina și dubla ceasuri analogice și digitale, calendare, panouri calendar cu ceas și ceasuri pe ecran. Fiecare are propria vizibilitate, Întotdeauna deasupra, limbă, fus orar și decalaj [-]HH:mm:ss.ff. Dimensiunile cadranelor se aleg separat. Ceasurile digitale oferă secunde, zero inițial, fonturi, culori, opacitate și fundal transparent. Calendarele acceptă numere de săptămâni și duminica drept prima zi și folosesc limba widgetului.

## Alarmă și comenzi rapide

Ceasurile și panourile pot avea alarmă. Aplicația redă singură fișierul audio o dată sau continuu, conform repetării; alte fișiere și comenzi sunt transmise către Windows. Un clic pe cadranul sau afișajul alarmei active, Oprire alarmă ori Esc oprește indicația și sunetul aplicației. Un dublu clic pe cadran sau afișaj digital comută secundele. F1 deschide Ajutor, B Setări, iar Esc ascunde widgetul dacă nu oprește o alarmă. Pozițiile widgeturilor se salvează după glisare, cele ale dialogurilor la închidere, iar setările în spațiul de stocare ales. O nouă pornire activează instanța existentă și păstrează widgeturile în cel mai apropiat punct disponibil al zonei de lucru.

## Introducerea orei și acțiunile alarmei

Ora alarmei acceptă HH:mm cu două puncte, punct, spațiu, alt separator sau fără separator. Una ori două cifre înseamnă ore, trei sau patru ore și minute: 7, 12, 730, 0730 sau 7:30. La ieșirea din câmp, valoarea devine HH:mm. Decalajul se citește de la dreapta, începând cu secundele: 2 înseamnă 00:00:02.00, 230 și 0230 înseamnă 00:02:30.00, iar 12345 înseamnă 01:23:45.00. Cu separatori, două grupuri înseamnă minute și secunde, trei ore, minute și secunde, al patrulea sutimi; se acceptă semn. Zilele de sub Alarmă activată stabilesc zilele de declanșare; implicit sunt selectate toate. Ordinea urmează limba aplicației, dar schimbarea limbii nu modifică zilele salvate.

Alarma afișează widgetul ascuns și îl aduce în față fără a modifica permanent Întotdeauna deasupra. Redare semnal orar pornește primul ton scurt cu cinci secunde înaintea alarmei. Este independent de fila Semnal; secvențele simultane sunt îmbinate. Testare face să clipească cadranul sau rama și verifică fișierul, comanda, sunetul, adresa HTTP/HTTPS a scriptului la distanță și, dacă este selectat, întregul semnal orar. Oprirea testului oprește sunetul intern și semnalul de probă ale acestuia; oprirea alarmei oprește sunetul ei intern. Dezactivarea sunetului nu oprește redarea: aceasta continuă în liniște și se aude din nou după reactivare. Comenzile și scripturile la distanță nu sunt oprite.

Semnalele sonore ale alarmei sunt programate după momentul real al următoarei alarme, după conversia fusului orar și aplicarea decalajului widgetului. Ele încep cu cinci secunde reale înainte, chiar dacă ceasul afișat sare direct la ora alarmei. O oră de alarmă omisă primăvara nu declanșează nici alarma, nici semnalele sale. În ora repetată toamna, alarma și semnalele sale se declanșează o singură dată pentru aceeași dată și oră configurată.

Glisorul Volum audio din fila Alarmă controlează redarea internă a widgetului. Valoarea implicită −18 dB păstrează nivelul inițial al fișierului (100%). Spre dreapta se amplifică sunetul; maximul de 0 dB corespunde la aproximativ 794%. −∞ dB înseamnă liniște. Modificările se aud și în timpul testului. MIDI și fișierele care nu pot fi decodificate și sunt redate prin metoda de rezervă sunt limitate la 100%.

## Selecție, taste și copierea datei

Setări reține ultima filă, iar Adăugare ultimul tip adăugat. Eliminare sau Del elimină toate elementele selectate când se aplică modificările. Un dublu clic pe un element afișează widgetul ascuns, bifează Vizibil și îl evidențiază scurt. Setări din meniul unui widget îl selectează în listă. Un clic pe o zi selectează data și o copiază în clipboard. Fiecare calendar are propriul format în setări și meniu. Toate cele 33 de formate sunt disponibile în orice limbă; numele textuale și formatul implicit Dată scurtă urmează limba widgetului.

Insert comută selecția elementului curent și deplasează cursorul listei un rând în jos. Ctrl+C copiază widgeturile, Ctrl+V adaugă copii în ordinea listei, cu un sufix al numelui în limba aplicației. Sunt permise până la 32 de widgeturi. Copiile se adaugă în ordine până la limită; pentru restul apare o notificare. Alt+0, Alt+1, Alt+2 și Alt+3 pe un ceas analogic sau calendar cu ceas aleg dimensiunea cadranului principal de la cea mai mică la cea mai mare.

La deschiderea setărilor din pictograma din zona de notificare, este selectat din nou ultimul widget ales.

## Aranjarea widgeturilor

Aranjare în grilă păstrează aproximativ pozițiile manuale, aliniază centrele la cele mai apropiate puncte ale grilei și elimină suprapunerile. Widgetul din al cărui meniu s-a lansat comanda rămâne pe loc. Meniul widgetului afectează monitorul său; pictograma de notificare tratează fiecare monitor separat. Repetarea păstrează aranjarea stabilă. Dublul clic din Setări identifică widgetul prin clipire rapidă albastru-deschis; alarma clipește mai lent în roșu. Dezactivarea Întotdeauna deasupra trimite widgetul în spatele ferestrelor. Legătura superioară a panoului revine la azi, cea inferioară deschide setările clasice Windows pentru dată și oră. Alinierea la margini atrage widgetul glisat la marginea zonei de lucru de la cel mult cinci pixeli. Redimensionarea păstrează atașarea la aceeași margine sau pereche de margini.

Panourile cu calendar și ceas pot afișa notificările Windows despre dată și oră deasupra legăturii de jos. Opțiunea **Notificări despre dată și oră** din fila **General** este activată implicit și se salvează separat pentru fiecare panou. Dacă sunt aplicabile mai multe notificări, acestea apar una sub alta, ca în Windows. Dacă opțiunea este dezactivată sau nu există nicio notificare aplicabilă, panoul își păstrează dimensiunea și aspectul inițial, fără a rezerva spațiu gol.

Pentru un calendar separat, Rândul Azi din Aspect sau meniu afișează ori ascunde rândul inferior. Salt la ziua de azi selectează azi și restabilește vizualizarea lunară. Când data se schimbă după ora widgetului, ziua de azi se selectează automat, păstrând vizualizarea curentă.

## Aspect și stocare

Modificările de aspect sunt afișate imediat în previzualizarea widgetului selectat. `Aspect implicit` restabilește valorile implicite ale acelui tip de widget. La închiderea setărilor cu modificări neaplicate, vi se cere să confirmați dacă doriți să le salvați. Avertismentul este activat implicit și poate fi dezactivat din fila Aplicație. Ceasurile digitale oferă font, netezire, culori, opacitate, spațiere interioară, grosime a bordurii și fundal transparent. Ceasurile, calendarele și panourile au patru stiluri comune de bordură; bordura simplă are culoare configurabilă. Panoul are fonturi separate pentru rândul superior, oră și rândul inferior, zero inițial și dimensiuni ale cadranelor. Temele și netezirea sunt configurate pentru aplicație și fiecare widget. Fonturile personalizate ale calendarului sunt acceptate cu aspectul clasic Windows sau când temele sunt dezactivate pentru aplicație ori widget.

Setările pot fi exportate în XML. Importul încarcă și salvează imediat setările în stocarea aleasă fără a-i schimba tipul. XML-ul automat este %AppData%\FortSoft\CalClock\settings.xml. Scrierea XML elimină cheia HKCU\SOFTWARE\FortSoft\CalClock; stocarea în registry elimină XML-ul automat.

Netezire font oferă ClearType, GDI și Fără. Zero inițial oferă „Da” (implicit), „Nu, păstrează spațiul” și „Nu, fără spațiu”. „Nu, păstrează spațiul” ascunde zero, rezervând lățimea lui în fontul ales; celelalte cifre rămân pe poziție și cu fonturi proporționale. Ceasurile pe ecran rămân centrate incluzând spațiul rezervat. Rândul UTC are centrare separată.

## Setări și meniuri

Limba aplicației, fontul, netezirea, temele, stocarea, pornirea cu Windows și alinierea la margini sunt comune în fila Aplicație. La prima pornire se alege limba interfeței Windows sau engleza americană dacă nu este acceptată. Limba, netezirea și temele widgetului afectează numai acel widget.

Meniul widgetului conține alegerile aplicabile de vizibilitate, Întotdeauna deasupra, secunde, dimensiune și copiere a datei, apoi Aranjare în grilă, Setări, Ajutor, Despre și Ieșire. Meniul pictogramei enumeră widgeturile numerotate, Afișare totală, Ascundere totală și Dezactivare totală sunet, apoi comanda de grilă separată. Afișarea sau restabilirea aduce widgetul în față fără schimbarea Întotdeauna deasupra. O nouă pornire restabilește la nevoie ultimele widgeturi ascunse. Dimensiunile și secundarul depind de Windows. Alarmă și Semnal se pot comuta din meniu, care arată ora, intervalul și zilele active când nu este selectată întreaga săptămână. Dezactivare sunet corespunde cu Sunet dezactivat din General. Dezactivare totală sunet și M dezactivează sunetul tuturor widgeturilor; repetarea îl restabilește numai celor afectate de acea comandă. Activarea unei alarme fără zi selectată deschide fila Alarmă.

## Semnal orar sonor

Semnalul urmează Greenwich Time Signal (GTS): cinci tonuri scurte în ultimele cinci secunde și un ton lung exact la momentul stabilit. Semnal oferă Semnal orar activat și intervale de 1, 5, 10, 15, 20, 30 sau 60 de minute după ora widgetului. Inițial este dezactivat, cu interval orar selectat. Comutarea din meniu păstrează intervalul. Sunt respectate UTC, fusul, decalajul și NTP; la 20 de minute sună la :00, :20 și :40. Semnalele simultane ale widgeturilor și alarmelor se îmbină. După dezactivarea sunetului, tonul curent se poate încheia; următoarele sunt omise până la următorul ton programat după reactivare. Un Calendar separat nu are alarmă, semnal orar sau dezactivare de sunet.

Sunet semnal orar din Aplicație oferă Generator încorporat (implicit) și Bip de sistem pentru toate widgeturile și alarmele. Volum semnal orar arată nivelul generatorului în dB: 0 dB la dreapta este amplitudinea sinusoidală maximă nedistorsionată, −∞ dB liniște, iar −18 dB valoarea implicită. Testare începe o previzualizare continuă, Oprire test o încheie. Se pot testa ambele sunete; testul nu se salvează. Menținerea glisorului redă și ea sunet până la eliberarea mouse-ului, dacă nu rulează testul din buton. Redarea începe la următoarea secundă întreagă: ton scurt în fiecare secundă și lung la :00, :05, :10 etc. Semnalele simultane de test, widget și alarmă folosesc un singur ton. Oprirea lasă tonul curent să se încheie; unul lung poate dura încă o jumătate de secundă. Sunt luate în calcul sutimile decalajului; tonurile suprapuse sună continuu până la sfârșitul ultimei suprapuneri.

## Ceasuri suplimentare

Calendar cu ceas poate afișa în General până la două ceasuri suplimentare cu nume și fusuri orare proprii. Fiecare arată atunci și ziua locală a săptămânii. Dimensiunea se alege separat în Aspect sau meniul contextual al cadranului. Ceasurile suplimentare nu au secundar. Adăugarea, eliminarea și redimensionarea păstrează atașarea la marginile zonei de lucru.

Numai dublul clic direct pe cadranul principal comută secundarul acestuia. Meniurile ceasurilor suplimentare conțin doar dimensiuni. Ele folosesc limba, formatul orei, fonturile și decalajul widgetului; afișajul digital nu are secunde.

## Formatul orei și fusuri orare

Format oră din General oferă Conform limbii (implicit), 12 ore și 24 de ore. Alegerea manuală rămâne după schimbarea limbii. Separatorii și marcajele urmează limba widgetului. AM/PM este inițial activat și controlează numai marcajul în modul de 12 ore; dacă limba nu are marcaje proprii, se utilizează AM/PM. Ceasurile pe ecran îl arată pe un rând separat sub oră. UTC folosește întotdeauna formatul de 24 de ore. Fusurile denumite urmează ora locală și ora de vară; decalajul este pentru data curentă. Opțiunile UTC separate sunt decalaje fixe de la −12:00 la +14:00 în pași de 15 minute fără oră de vară.

Widgeturile noi folosesc implicit **Fusul orar curent din Windows**, care urmărește fusul orar curent din Windows și setarea automată a orei de vară. Widgeturile existente își păstrează fusurile alese. Această opțiune stabilește fusul orar; sursa de timp comună, Windows sau NTP, rămâne independentă.

Decalajul widgetului se aplică orei UTC înaintea conversiei în fusul său orar, astfel încât deplasează și momentul trecerii la ora de vară sau înapoi. Un ceas avansat cu zece secunde schimbă ora cu zece secunde mai devreme; unul întârziat cu zece secunde o schimbă cu zece secunde mai târziu. Limbile ceasului, afișajul digital, datele calendarului, alarmele și semnalele orare folosesc ora rezultată.

## Sursa de timp și jurnalul NTP

Oră alege ora sistemului Windows sau servere NTP pentru întreaga aplicație. NTP modifică numai ora CalClock; ceasul Windows nu se schimbă. Până la primul răspuns valid se folosește ora sistemului. NTP este implicit. Grupul automat alege după regiunea sistemului servere cehe și slovace, PTB pentru Europa sau un grup mondial. Măsurătorile sunt filtrate după întârzierea rețelei și abaterile față de alte răspunsuri. Sincronizare acum începe imediat o măsurătoare nouă.

După sincronizare, ceasul CalClock funcționează independent de modificările ulterioare ale orei sistemului Windows. La pierderea conexiunii sau schimbarea serverelor continuă de la ultima sincronizare validă până la un nou răspuns; starea se păstrează până la închiderea aplicației.

Oră înregistrează cererile NTP de la pornire. Intrarea conține data, ora locală a calculatorului, serverul și starea. OK indică un răspuns valid; θ abaterea față de ora Windows. ERR oferă cauza și eventualul cod de eroare. Ultima intrare a grupului arată și abaterea combinată Θ dacă există măsurători utilizabile. Abaterile sunt în milisecunde cu patru zecimale: pozitiv înseamnă că serverul este înainte, negativ că rămâne în urmă. Θ se bazează pe măsurătorile acceptate și apare în starea sincronizării. Salvare jurnal exportă CSV cu abateri și detalii de eroare. Înregistrările nu rămân între sesiuni; salvați înainte de ieșire dacă sunt necesare.

## Ceas pe ecran

Un ceas digital poate umple unul sau mai multe monitoare și le poate întuneca pe celelalte. Dimensiunea fontului este procent din înălțimea monitorului; se pot alege fontul, netezirea, culorile și spațierea interioară. UTC poate fi pe un rând separat. Implicit, textul este alb pe fundal negru. Cu Setări deschis, ceasul este o previzualizare mică, mobilă, cu proporțiile monitorului și poziție salvată. Grila nu mută acest tip. Esc ascunde ceasul și elimină întunecarea chiar cu Setări deschis.

Indicatorul mouse-ului se ascunde după o scurtă inactivitate deasupra ceasului și monitoarelor întunecate și reapare la mișcare. Deasupra previzualizării mici rămâne vizibil.

## Compilare și împachetare

Sunt necesare Microsoft Visual Studio cu setul de instrumente MSVC v145 și Windows SDK. Deschideți `CalClock.slnx`, alegeți `Release | x86` și compilați soluția. Fișierul executabil este creat în `Release\CalClock.exe`. Este acceptată numai configurația Win32/x86 deoarece integrarea cu controlul de ceas Windows necesită compatibilitate x86.

După compilare, `.\PackageRelease.ps1` creează `CalClock-<version>-win32.zip`; versiunea se citește din `Release\CalClock.exe`. Arhiva conține `CalClock.exe` și `license.txt` direct în rădăcină. Parametrii opționali de semnare `-SignerName`, `-SignToolPath` și `-TimestampServer` se dau la rulare. O semnătură Authenticode validă existentă este verificată și nu se înlocuiește. Pachetele ZIP CalClock anterioare se elimină la începutul fiecărei rulări; erorile de semnare sau verificare opresc împachetarea.

## Licență

CalClock este disponibil sub [licența MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
