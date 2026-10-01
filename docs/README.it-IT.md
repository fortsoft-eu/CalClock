# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · **Italiano** · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md)

CalClock è un’applicazione nativa Win32/x86 per Windows Vista e versioni successive che visualizza sul desktop orologi e calendari mobili configurabili indipendentemente. Funziona nell’area di notifica e non richiede una finestra di controllo permanente.

## Funzionalità

- Fino a 32 widget configurabili indipendentemente
- Lingua, fuso orario, scostamento, visibilità e stato sempre in primo piano per ciascun widget
- Orologi analogici basati sul controllo Windows `ClockWndMain`, con rilevamento delle dimensioni disponibili e supporto della lancetta dei secondi
- Orologi digitali con caratteri, colori, opacità, margini interni, bordi, zero iniziale facoltativo e sfondo trasparente facoltativo
- Calendari nativi di Windows con selezione della data, quattro stili di bordo, colore del bordo configurabile, numeri delle settimane, scelta del primo giorno e 33 formati di copia
- Pannelli calendario e orologio con fino a due orologi aggiuntivi dotati di nome e fusi indipendenti, dimensioni separate dei quadranti, quattro stili di bordo, colore configurabile, testo UTC, zero iniziale e carattere distinto per ogni riga di testo
- Sveglie con scelta dei giorni, indicazione visiva, riproduzione audio interna, ripetizione, comandi locali e chiamate a script HTTP/HTTPS
- Segnali orari per ogni orologio a intervalli di 1, 5, 10, 15, 20, 30 o 60 minuti, con segnali simultanei uniti in una sola sequenza
- Comando Silenzioso per ogni orologio e comando selezionabile Silenzia tutto nell’area di notifica
- Avvio automatico con Windows facoltativo
- Aggancio facoltativo ai bordi dell’area di lavoro entro cinque pixel durante il trascinamento, attivo per impostazione predefinita; l’aggancio resta valido quando cambiano le dimensioni
- Sincronizzazione NTP senza modificare l’orologio di sistema Windows
- Diverse preimpostazioni NTP per Cechia e Slovacchia, PTB, Ubuntu/NTP Pool o server personalizzati
- Impostazioni nel Registro o in XML, con importazione ed esportazione XML
- Comandi nell’area di notifica con ripristino dei widget nascosti più di recente
- Identificazione dei widget e disposizione stabile su una griglia senza sovrapposizioni
- Anteprima immediata dell’aspetto con annullamento e valori predefiniti per ogni widget
- Caratteri dell’applicazione e dei widget, stili visivi e smussatura ClearType, GDI o nessuna
- Interfacce in ceco, inglese americano, britannico e australiano, tedesco, francese, spagnolo, italiano, portoghese, polacco, slovacco, danese, finlandese, islandese, norvegese, svedese e turco

## Tipi di widget

| Widget | Descrizione |
| --- | --- |
| Orologio analogico | Quadrante Windows mobile con dimensioni e lancetta dei secondi facoltativa offerte dalla versione corrente di Windows |
| Orologio digitale | Display digitale mobile configurabile con testo UTC, zero iniziale, bordi e sfondo trasparente facoltativi |
| Calendario | Calendario mensile nativo spostabile con selezione della data, bordi configurabili e formati di copia |
| Calendario con orologio | Pannello con calendario nativo, orologio analogico, righe di testo configurabili, UTC e bordi configurabili |
| Orologio su monitor | Orologio digitale che occupa uno o più monitor selezionati, con oscuramento facoltativo e UTC su una riga separata |

Al primo avvio, CalClock sceglie la lingua dell’interfaccia Windows e usa l’inglese americano se non è supportata. Crea un orologio analogico visibile come impostazione iniziale. Ogni widget conserva posizione e impostazioni tra le esecuzioni. Quando Impostazioni è aperto, un orologio su monitor è sempre rappresentato da un’anteprima spostabile con le proporzioni del monitor scelto. `Esc` nasconde l’orologio e rimuove l’oscuramento anche con Impostazioni attivo. Il puntatore scompare dopo una breve inattività sopra gli orologi su monitor e i monitor oscurati, e riappare al movimento del mouse. Rimane visibile sulla piccola anteprima delle Impostazioni.

## Comandi

- Trascinare un orologio o pannello con il pulsante sinistro del mouse.
- Trascinare un calendario autonomo dalla sua area libera.
- Fare clic destro su un widget o sull’icona di notifica per aprirne il menu contestuale.
- Un clic sinistro sull’icona di notifica nasconde i widget visibili. Se sono tutti nascosti, il clic successivo ripristina solo quelli nascosti più di recente.
- Un doppio clic sul quadrante attiva o disattiva i secondi. Nei pannelli calendario e orologio, solo il doppio clic direttamente sul quadrante principale cambia la lancetta dei secondi. Gli orologi aggiuntivi non la possiedono.
- `F1` apre la Guida, `B` le Impostazioni, `M` commuta Silenzia tutto ed `Esc` nasconde un widget o ferma una sveglia attiva.
- Fare doppio clic su un widget nelle Impostazioni lo rende visibile se necessario, seleziona `Visibile` e lo identifica brevemente sul desktop.
- Aprire Impostazioni dal menu di un widget lo seleziona immediatamente.
- Usare `Ctrl` o `Shift` per selezionare più elementi, `Ctrl+A` per selezionarli tutti e `Del` per rimuoverli. `Insert` commuta la selezione dell’elemento corrente e sposta il cursore alla riga successiva, come in Total Commander.
- Tutte le scorciatoie dell’elenco funzionano anche con il focus su Rimuovi o Duplica. La scorciatoia porta il focus nell’elenco ed esegue l’azione. `Ctrl+C` copia i widget selezionati; `Ctrl+V` aggiunge le copie in fondo nell’ordine dell’elenco. Le copie comprendono tutte le impostazioni e ricevono un suffisso nella lingua dell’applicazione. Duplica esegue direttamente la stessa operazione. Sono ammessi fino a 32 widget. Se non c’è spazio per tutte le copie, vengono aggiunte quelle che rientrano nel limite, in ordine, e un messaggio segnala le rimanenti.
- `Ctrl+A` o un triplo clic in un campo di testo ne seleziona tutto il contenuto.

Con più widget selezionati, i loro controlli Generale, Aspetto, Sveglia e Segnale sono disattivati; le schede globali Ora e Applicazione restano disponibili. Impostazioni ricorda l’ultima scheda aperta e l’ultimo tipo aggiunto. Se l’area di lavoro è piccola, la finestra offre lo scorrimento orizzontale o verticale necessario.

Le date del calendario possono essere copiate in 33 formati: locali, ordinabili, con giorno o mese iniziale, testuali e con giorno della settimana. Ogni maschera è disponibile in ogni lingua. Il formato breve locale predefinito segue la lingua del widget, così come i nomi di mesi e giorni. Le voci mostrano la maschera e un esempio aggiornato.

Un pannello calendario e orologio può mostrare fino a due orologi aggiuntivi. Attivarli in Generale e scegliere nome e fuso. I fusi con nome seguono le proprie regole dell’ora legale; gli scostamenti UTC fissi restano costanti. Quando sono attivi orologi aggiuntivi, ogni orologio mostra il proprio giorno locale sotto l’ora. Le tre liste delle dimensioni in Aspetto controllano, nell’ordine, l’orologio principale, Orologio 1 e Orologio 2. Il clic destro su un quadrante aggiuntivo ne permette la scelta delle dimensioni. Questi orologi omettono sempre i secondi e condividono lingua, formato, caratteri e scostamento del widget. Aggiungere, rimuovere o ridimensionare orologi mantiene il widget agganciato agli stessi bordi dell’area di lavoro.

Nel pannello, la data superiore è un collegamento che riporta il calendario a oggi; il testo inferiore del fuso apre le impostazioni classiche Data e ora di Windows. Entrambi i collegamenti sono raggiungibili con `Tab`, mostrano un rettangolo di focus e si attivano da tastiera. Il calendario nativo resta completamente interattivo, ma omette la riga Oggi, ridondante in questa disposizione.

`Allinea alla griglia` dispone i widget desktop visibili su una griglia stabile senza sovrapposizioni, mantenendo approssimativamente il posizionamento manuale. Il widget dal cui menu è stato richiamato resta fermo; il comando dell’area di notifica organizza ogni monitor separatamente. Gli orologi su monitor sono esclusi.

## Aspetto

Nei calendari autonomi, **Riga Oggi** nel menu o nella scheda Aspetto controlla la visibilità della riga inferiore. È selezionata per impostazione predefinita; deselezionandola si nasconde la riga e il calendario si riduce. La scelta viene salvata per widget. **Vai a oggi** resta disponibile e torna alla vista mensile. Al cambio di data secondo l’ora del widget, il calendario seleziona automaticamente oggi mantenendo la vista attuale.

Le modifiche dell’aspetto sono mostrate subito sul widget selezionato. `Annulla` ripristina le modifiche non applicate; `Aspetto predefinito` ripristina i valori iniziali del tipo di widget.

Orologi digitali, calendari e pannelli condividono quattro stili di bordo. Il bordo semplice ha anche un colore configurabile; la larghezza è disponibile quando supportata dal widget. Gli orologi digitali trasparenti mantengono le stesse scelte di quelli opachi. Le finestre dei caratteri mostrano solo opzioni pertinenti e omettono anteprima ed effetti inutilizzati. Per applicazione e calendario non offrono la dimensione; per orologi digitali e testi del pannello sì. Un calendario nativo accetta caratteri personalizzati solo se gli stili visivi sono disattivati per esso o per tutta l’applicazione.

Lingua dell’applicazione, carattere dell’interfaccia, smussatura, stili visivi, archiviazione, avvio Windows e aggancio ai bordi sono globali e si configurano in Applicazione. Anche la sorgente dell’ora è globale. Lingua del widget, smussatura, stili, fuso, scostamento, sveglia e segnale orario sono indipendenti. Applicare un’altra lingua ricrea subito la finestra Impostazioni aperta in quella lingua. La smussatura offre **ClearType**, **GDI** e **Nessuna**. In Aspetto, smussatura e disattivazione dei temi occupano la stessa posizione per ogni tipo, con **Aspetto predefinito** sotto.

Il cursore **Volume audio** in Sveglia controlla i file riprodotti internamente per ciascun widget e mostra il livello in dB. Il valore predefinito **−18 dB** preserva il livello originale del file (**100%**). Verso destra amplifica il suono; il massimo **0 dB** equivale a circa **794%** dell’ampiezza originale. L’estremo sinistro è **−∞ dB** (silenzio). Le modifiche hanno effetto durante la prova. Il cursore è disattivato per file aperti in applicazioni esterne. L’amplificazione riguarda l’audio decodificato, inclusi WAV, MP3, WMA, AAC, M4A e FLAC quando supportati da Windows. La riproduzione precedente per file non decodificabili, come MIDI, è limitata al 100%.

I giorni della sveglia seguono il primo giorno della settimana della cultura selezionata per l’applicazione. I giorni salvati mantengono il significato dopo un cambio di lingua. Attivare dal menu una sveglia senza giorni selezionati apre la relativa scheda Sveglia invece di abilitare una sveglia che non può suonare.

La larghezza predefinita del bordo digitale è zero. **Zero iniziale** offre **Mostra** (predefinito), **Mantieni spazio** e **Senza spazio**. **Mantieni spazio** nasconde lo zero riservandone la larghezza reale nel carattere scelto; le altre cifre mantengono così la posizione anche con caratteri proporzionali. Gli orologi digitali mobili allineano l’ora a sinistra e mantengono dimensioni fisse mentre il tempo avanza. Gli orologi su monitor centrano un’area oraria fissa dimensionata per carattere e formato, con spazio per due cifre dell’ora. Il cambio dell’ora non ricentra né ridimensiona il testo. La riga AM/PM o UTC resta centrata indipendentemente. Gli orologi su monitor usano testo bianco su sfondo nero per impostazione predefinita.

## Ora e sveglie

Orologi digitali, pannelli calendario e orologio e orologi su monitor offrono **Secondo la lingua**, **12 ore** e **24 ore** in **Formato ora** su Generale. **Secondo la lingua** è la scelta predefinita: ad esempio l’inglese americano e australiano usano 12 ore, quello britannico 24. Una scelta manuale resta invariata cambiando lingua del widget. Separatori e indicatori AM/PM seguono la cultura; quelle senza indicatori propri usano **AM/PM** nel ciclo di 12 ore.

La casella **AM/PM** è selezionata per impostazione predefinita. Deselezionarla nasconde l’indicatore senza cambiare il ciclo di 12 ore. È disattivata nel ciclo di 24 ore e per widget senza ora digitale. Gli orologi su monitor mostrano l’indicatore su una riga sotto l’ora, come UTC. **UTC usa sempre 24 ore**; i controlli del ciclo e AM/PM sono disattivati in UTC e conservano i valori per tornare all’ora locale. Lo zero iniziale resta visibile, nascosto con spazio riservato o omesso secondo il suo apposito controllo.

I fusi con nome mostrano l’ora civile della località e ne seguono automaticamente le regole dell’ora legale. Lo scostamento accanto al nome corrisponde alla data corrente e viene aggiornato all’apertura dell’elenco. Le voci **UTC** separate offrono scostamenti fissi da **UTC−12:00** a **UTC+14:00**, a passi di 15 minuti e senza ora legale. Ogni widget può scegliere indipendentemente fuso locale, altro fuso con nome o scostamento UTC fisso.

Ogni widget può usare qualsiasi fuso Windows e uno scostamento con segno nella forma `[-]HH:mm:ss.ff`. L’immissione compatta viene interpretata da destra, iniziando dai secondi.

Lo scostamento è utile, ad esempio, negli studi di trasmissione per compensare il ritardo del percorso del segnale. Anticipare l’orologio dello studio del ritardo misurato permette al segnale orario di raggiungere gli ascoltatori al momento previsto.

CalClock può usare l’ora del sistema Windows o una correzione interna ottenuta dai server NTP. La scelta è globale per tutti i widget. La sincronizzazione non modifica mai l’orologio Windows. Se il collegamento NTP viene perso dopo una sincronizzazione riuscita, l’ultima correzione resta attiva nella memoria del processo. Anche il cambio dei server conserva la correzione valida fino a una nuova risposta.

I widget orologio supportano sveglie per giorni scelti individualmente; tutti e sette sono attivi per impostazione predefinita. La sveglia rende visibile il proprio widget nascosto e lo porta davanti alle altre finestre senza modificare permanentemente lo stato sempre in primo piano. WAV, MP3, WMA, MIDI, AAC, M4A e FLAC sono riconosciuti per la riproduzione interna singola o ripetuta; il supporto effettivo dipende dai componenti multimediali di Windows installati. Altri file e comandi vengono passati a Windows in modo asincrono. Una sveglia può anche richiamare un URL HTTP o HTTPS. Indipendentemente, può usare il segnale a sei bip, il cui primo tono breve suona cinque secondi prima dell’ora impostata.

Esegui file o comando attiva il campo, Sfoglia, Prova e ripetizione. Prova e ripetizione richiedono anche un campo non vuoto, ma una prova attiva può sempre essere fermata. Prova mostra l’indicazione visiva e verifica in modo asincrono file, comando, audio e URL dello script remoto. Se è selezionato il segnale della sveglia, riproduce anche tutti e sei i bip; Interrompi prova termina audio interno e anteprima del segnale.

La scheda Segnale può disattivare i segnali oppure programmarli ogni 1, 5, 10, 15, 20, 30 o 60 minuti secondo l’ora visualizzata dal widget. L’intervallo di 20 minuti segnala :00, :20 e :40 di quell’ora. Segue il **Greenwich Time Signal (GTS)**: cinque bip brevi indicano gli ultimi cinque secondi e uno più lungo il limite esatto. Sono rispettati fuso, UTC, scostamenti e correzione NTP attuale. Segnale della sveglia e scheda Segnale restano indipendenti; quando gli orari coincidono, CalClock riproduce un’unica sequenza condivisa. Sono rispettati gli scostamenti frazionari; i toni sovrapposti di widget, sveglie e prove suonano senza interruzioni fino al termine dell’ultima sovrapposizione.

**Suono del segnale orario** in Applicazione offre **Generatore integrato** (predefinito) e **Bip di sistema**. Vale per tutti i segnali dei widget, inclusi quelli delle sveglie, e viene salvato globalmente. Per il **Generatore integrato**, **Volume del segnale orario** indica il livello in dB per l’intera applicazione. A destra si trova **0 dB**, la massima ampiezza sinusoidale senza distorsione; il silenzio è **−∞ dB**. Il valore predefinito è **−18 dB**. La scala in decibel ha −18 dB al centro. Il generatore inizia e termina i toni al passaggio per lo zero, anche fermando una prova. Il bip corrente viene lasciato terminare; quello lungo può richiedere fino a mezzo secondo. **Prova** accanto a **Suono del segnale orario** avvia l’anteprima continua; **Interrompi prova** la termina. Si possono provare entrambi i modi e lo stato della prova non viene salvato. Tenere premuto il cursore del volume avvia un’anteprima fino al rilascio del mouse, salvo quando è attiva la prova avviata dal pulsante. La riproduzione inizia al successivo secondo intero, con toni brevi ogni secondo e uno lungo a :00, :05, :10 ecc. Anteprima e segnali simultanei dei widget o sveglie condividono un solo tono. Con **Bip di sistema** è disattivato soltanto il cursore del volume. La scelta è disponibile solo se il sistema supporta entrambe le modalità.

Sveglia e segnale si possono attivare anche nel menu di ogni widget con supporto audio. La voce della sveglia mostra l’ora e, se non sono selezionati tutti i giorni, quelli attivi. Silenzioso riguarda il widget e corrisponde alla casella su Generale. Un Calendario autonomo non ha sveglia, segnale né stato silenzioso, quindi questi comandi sono omessi o disattivati. Nell’area di notifica il comando è Silenzia tutto; `M` su qualsiasi widget esegue la stessa commutazione globale. La riattivazione globale ripristina soltanto i widget silenziati dall’azione globale precedente. L’audio interno continua senza suono e torna udibile alla riattivazione. Un bip già iniziato può terminare; i successivi vengono saltati fino al ritorno dell’audio. Comandi non audio e script remoti non sono interessati.

## Impostazioni e menu

`Salva` applica le modifiche e chiude Impostazioni; `Applica` le applica lasciando aperta la finestra; `Annulla` scarta quelle non ancora applicate, inclusa l’anteprima dell’aspetto. Invio attiva `Salva`; Esc attiva `Annulla`.

Ogni menu widget include i comandi pertinenti al tipo — visibilità, primo piano, secondi, dimensioni analogiche o formato della data copiata — seguiti da `Allinea alla griglia`, Impostazioni, Guida, Informazioni ed Esci. Il menu di notifica elenca i widget con il loro numero, poi Mostra tutto, Nascondi tutto e Silenzia tutto. `Allinea alla griglia`, in un gruppo separato, precede i comandi dell’applicazione.

Mostrare o ripristinare widget li porta davanti alle altre finestre senza cambiare il loro stato sempre in primo piano. CalClock assicura almeno un widget visibile all’avvio. Un secondo avvio attiva l’istanza esistente e ripristina i widget nascosti più di recente se nessuno è visibile. Dopo il riavvio di Esplora risorse l’icona di notifica viene registrata di nuovo automaticamente. Se `ClockWndMain` non supporta i secondi nelle dimensioni scelte, Secondi è disattivato, ma la preferenza resta salvata per un’altra dimensione compatibile.

## Archiviazione delle impostazioni

Per impostazione predefinita, i dati vengono salvati in:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

L’archiviazione XML si abilita in Impostazioni e usa:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Dopo un salvataggio XML riuscito, CalClock elimina il proprio stato dal Registro. Tornare al Registro elimina analogamente il file XML automatico e le cartelle CalClock vuote. Importare un XML carica e salva subito le impostazioni nell’archivio attualmente scelto senza cambiarne il tipo. Lo stato silenzioso viene salvato per ogni widget audio. L’avvio con Windows viene registrato come valore `CalClock` nella chiave standard `Run` dell’utente corrente.

## Compilazione

Requisiti:

- Microsoft Visual Studio con il set di strumenti MSVC v145
- Windows SDK

Aprire `CalClock.slnx`, scegliere `Release | Win32` e compilare la soluzione. L’eseguibile viene creato come:

```text
Release\CalClock.exe
```

È supportata solo la configurazione Win32/x86. Il progetto non offre intenzionalmente x64 perché l’integrazione con il controllo orologio Windows richiede compatibilità x86.

## Licenza

CalClock è disponibile con [licenza MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
