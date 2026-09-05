#include "Localization.h"

const wchar_t* TEXT[LANG_COUNT][TXT_COUNT] = {
    {
        L"Hodiny a kalendáře",
        L"Nastavení",
        L"Přidat",
        L"Odebrat...",
        L"Duplikovat",
        L"Obecné",
        L"Vzhled",
        L"Budík",
        L"Název:",
        L"Typ:",
        L"Zobrazeno",
        L"Vždy navrchu",
        L"Sekundy",
        L"Čas UTC",
        L"Časové pásmo:",
        L"Offset [-]HH:mm:ss.ff:",
        L"Velikost:",
        L"Neprůhlednost:",
        L"Velikost písma:",
        L"Úvodní nula",
        L"Průhledné pozadí",
        L"Barva textu...",
        L"Barva pozadí...",
        L"Čísla týdnů",
        L"Neděle jako první den",
        L"Budík aktivní",
        L"Čas budíku:",
        L"Spustit soubor nebo příkaz",
        L"Zvuk přehrávat stále dokola",
        L"Vybrat...",
        L"Jazyk:",
        L"Zakázat motivy",
        L"Uložit",
        L"Použít",
        L"Zrušit",
        L"Zobrazit vše",
        L"Skrýt vše",
        L"Zastavit budík",
        L"Nápověda",
        L"O programu",
        L"Konec",
        L"Ručičkové hodiny",
        L"Digitální hodiny",
        L"Kalendář",
        L"Kalendář s hodinami",
        L"Zadejte offset ve formátu [-]HH:mm:ss.ff.",
        L"Zadejte platný čas 0:00 až 23:59.",
        L"Opravdu odebrat označené widgety?",
        L"Musí zůstat alespoň jeden widget.",
        L"Zavřít"
    },
    {
        L"Clocks and calendars",
        L"Settings",
        L"Add",
        L"Remove...",
        L"Duplicate",
        L"General",
        L"Appearance",
        L"Alarm",
        L"Name:",
        L"Type:",
        L"Visible",
        L"Always on top",
        L"Seconds",
        L"UTC time",
        L"Time zone:",
        L"Offset [-]HH:mm:ss.ff:",
        L"Size:",
        L"Opacity:",
        L"Font size:",
        L"Leading zero",
        L"Transparent background",
        L"Text color...",
        L"Background color...",
        L"Week numbers",
        L"Sunday first",
        L"Alarm enabled",
        L"Alarm time:",
        L"Run a file or command",
        L"Loop audio continuously",
        L"Browse...",
        L"Language:",
        L"Disable themes",
        L"Save",
        L"Apply",
        L"Cancel",
        L"Show all",
        L"Hide all",
        L"Stop alarm",
        L"Help",
        L"About",
        L"Exit",
        L"Analog clock",
        L"Digital clock",
        L"Calendar",
        L"Calendar with clock",
        L"Enter the offset as [-]HH:mm:ss.ff.",
        L"Enter a valid time from 0:00 to 23:59.",
        L"Remove the selected widgets?",
        L"At least one widget must remain.",
        L"Close"
    },
    {
        L"Uhren und Kalender",
        L"Einstellungen",
        L"Hinzufügen",
        L"Entfernen...",
        L"Duplizieren",
        L"Allgemein",
        L"Darstellung",
        L"Wecker",
        L"Name:",
        L"Typ:",
        L"Sichtbar",
        L"Immer im Vordergrund",
        L"Sekunden",
        L"UTC-Zeit",
        L"Zeitzone:",
        L"Versatz [-]HH:mm:ss.ff:",
        L"Größe:",
        L"Deckkraft:",
        L"Schriftgröße:",
        L"Führende Null",
        L"Transparenter Hintergrund",
        L"Textfarbe...",
        L"Hintergrundfarbe...",
        L"Wochennummern",
        L"Sonntag zuerst",
        L"Wecker aktiv",
        L"Weckzeit:",
        L"Datei oder Befehl starten",
        L"Audio endlos wiederholen",
        L"Durchsuchen...",
        L"Sprache:",
        L"Designs deaktivieren",
        L"Speichern",
        L"Übernehmen",
        L"Abbrechen",
        L"Alle anzeigen",
        L"Alle ausblenden",
        L"Wecker stoppen",
        L"Hilfe",
        L"Info",
        L"Beenden",
        L"Analoguhr",
        L"Digitaluhr",
        L"Kalender",
        L"Kalender mit Uhr",
        L"Versatz als [-]HH:mm:ss.ff eingeben.",
        L"Gültige Zeit von 0:00 bis 23:59 eingeben.",
        L"Ausgewähltes Element entfernen?",
        L"Mindestens ein Element muss bleiben.",
        L"Schließen"
    },
    {
        L"Horloges et calendriers",
        L"Paramètres",
        L"Ajouter",
        L"Supprimer...",
        L"Dupliquer",
        L"Général",
        L"Apparence",
        L"Alarme",
        L"Nom :",
        L"Type :",
        L"Visible",
        L"Toujours visible",
        L"Secondes",
        L"Heure UTC",
        L"Fuseau horaire :",
        L"Décalage [-]HH:mm:ss.ff :",
        L"Taille :",
        L"Opacité :",
        L"Taille de police :",
        L"Zéro initial",
        L"Fond transparent",
        L"Couleur du texte...",
        L"Couleur du fond...",
        L"Numéros de semaine",
        L"Dimanche en premier",
        L"Alarme active",
        L"Heure de l’alarme :",
        L"Lancer un fichier ou une commande",
        L"Lire le son en boucle",
        L"Parcourir...",
        L"Langue :",
        L"Désactiver les thèmes",
        L"Enregistrer",
        L"Appliquer",
        L"Annuler",
        L"Tout afficher",
        L"Tout masquer",
        L"Arrêter l’alarme",
        L"Aide",
        L"À propos",
        L"Quitter",
        L"Horloge analogique",
        L"Horloge numérique",
        L"Calendrier",
        L"Calendrier avec horloge",
        L"Entrez le décalage au format [-]HH:mm:ss.ff.",
        L"Entrez une heure de 0:00 à 23:59.",
        L"Supprimer le panneau sélectionné ?",
        L"Au moins un panneau doit rester.",
        L"Fermer"
    },
    {
        L"Relojes y calendarios",
        L"Configuración",
        L"Añadir",
        L"Quitar...",
        L"Duplicar",
        L"General",
        L"Apariencia",
        L"Alarma",
        L"Nombre:",
        L"Tipo:",
        L"Visible",
        L"Siempre visible",
        L"Segundos",
        L"Hora UTC",
        L"Zona horaria:",
        L"Desfase [-]HH:mm:ss.ff:",
        L"Tamaño:",
        L"Opacidad:",
        L"Tamaño de fuente:",
        L"Cero inicial",
        L"Fondo transparente",
        L"Color de texto...",
        L"Color de fondo...",
        L"Números de semana",
        L"Domingo primero",
        L"Alarma activa",
        L"Hora de alarma:",
        L"Ejecutar archivo o comando",
        L"Repetir audio continuamente",
        L"Examinar...",
        L"Idioma:",
        L"Desactivar temas",
        L"Guardar",
        L"Aplicar",
        L"Cancelar",
        L"Mostrar todo",
        L"Ocultar todo",
        L"Detener alarma",
        L"Ayuda",
        L"Acerca de",
        L"Salir",
        L"Reloj analógico",
        L"Reloj digital",
        L"Calendario",
        L"Calendario con reloj",
        L"Introduzca el desfase como [-]HH:mm:ss.ff.",
        L"Introduzca una hora de 0:00 a 23:59.",
        L"¿Quitar el panel seleccionado?",
        L"Debe quedar al menos un panel.",
        L"Cerrar"
    },
    {
        L"Orologi e calendari",
        L"Impostazioni",
        L"Aggiungi",
        L"Rimuovi...",
        L"Duplica",
        L"Generali",
        L"Aspetto",
        L"Sveglia",
        L"Nome:",
        L"Tipo:",
        L"Visibile",
        L"Sempre in primo piano",
        L"Secondi",
        L"Ora UTC",
        L"Fuso orario:",
        L"Offset [-]HH:mm:ss.ff:",
        L"Dimensione:",
        L"Opacità:",
        L"Dimensione carattere:",
        L"Zero iniziale",
        L"Sfondo trasparente",
        L"Colore testo...",
        L"Colore sfondo...",
        L"Numeri settimana",
        L"Domenica per prima",
        L"Sveglia attiva",
        L"Ora sveglia:",
        L"Esegui file o comando",
        L"Ripeti audio continuamente",
        L"Sfoglia...",
        L"Lingua:",
        L"Disattiva temi",
        L"Salva",
        L"Applica",
        L"Annulla",
        L"Mostra tutto",
        L"Nascondi tutto",
        L"Ferma sveglia",
        L"Guida",
        L"Informazioni",
        L"Esci",
        L"Orologio analogico",
        L"Orologio digitale",
        L"Calendario",
        L"Calendario con orologio",
        L"Inserire l’offset come [-]HH:mm:ss.ff.",
        L"Inserire un’ora da 0:00 a 23:59.",
        L"Rimuovere il pannello selezionato?",
        L"Deve restare almeno un pannello.",
        L"Chiudi"
    },
    {
        L"Zegary i kalendarze",
        L"Ustawienia",
        L"Dodaj",
        L"Usuń...",
        L"Duplikuj",
        L"Ogólne",
        L"Wygląd",
        L"Alarm",
        L"Nazwa:",
        L"Typ:",
        L"Widoczny",
        L"Zawsze na wierzchu",
        L"Sekundy",
        L"Czas UTC",
        L"Strefa czasowa:",
        L"Przesunięcie [-]HH:mm:ss.ff:",
        L"Rozmiar:",
        L"Krycie:",
        L"Rozmiar czcionki:",
        L"Zero wiodące",
        L"Przezroczyste tło",
        L"Kolor tekstu...",
        L"Kolor tła...",
        L"Numery tygodni",
        L"Niedziela pierwsza",
        L"Alarm aktywny",
        L"Czas alarmu:",
        L"Uruchom plik lub polecenie",
        L"Powtarzaj dźwięk",
        L"Wybierz...",
        L"Język:",
        L"Wyłącz motywy",
        L"Zapisz",
        L"Zastosuj",
        L"Anuluj",
        L"Pokaż wszystkie",
        L"Ukryj wszystkie",
        L"Zatrzymaj alarm",
        L"Pomoc",
        L"O programie",
        L"Zakończ",
        L"Zegar analogowy",
        L"Zegar cyfrowy",
        L"Kalendarz",
        L"Kalendarz z zegarem",
        L"Wprowadź przesunięcie jako [-]HH:mm:ss.ff.",
        L"Wprowadź czas od 0:00 do 23:59.",
        L"Usunąć wybrany panel?",
        L"Musi pozostać co najmniej jeden panel.",
        L"Zamknij"
    },
    {
        L"Hodiny a kalendáre",
        L"Nastavenia",
        L"Pridať",
        L"Odobrať...",
        L"Duplikovať",
        L"Všeobecné",
        L"Vzhľad",
        L"Budík",
        L"Názov:",
        L"Typ:",
        L"Zobrazené",
        L"Vždy navrchu",
        L"Sekundy",
        L"Čas UTC",
        L"Časové pásmo:",
        L"Offset [-]HH:mm:ss.ff:",
        L"Veľkosť:",
        L"Nepriehľadnosť:",
        L"Veľkosť písma:",
        L"Úvodná nula",
        L"Priehľadné pozadie",
        L"Farba textu...",
        L"Farba pozadia...",
        L"Čísla týždňov",
        L"Nedeľa ako prvý deň",
        L"Budík aktívny",
        L"Čas budíka:",
        L"Spustiť súbor alebo príkaz",
        L"Zvuk prehrávať dookola",
        L"Vybrať...",
        L"Jazyk:",
        L"Zakázať motívy",
        L"Uložiť",
        L"Použiť",
        L"Zrušiť",
        L"Zobraziť všetko",
        L"Skryť všetko",
        L"Zastaviť budík",
        L"Pomoc",
        L"O programe",
        L"Koniec",
        L"Ručičkové hodiny",
        L"Digitálne hodiny",
        L"Kalendár",
        L"Kalendár s hodinami",
        L"Zadajte offset vo formáte [-]HH:mm:ss.ff.",
        L"Zadajte čas 0:00 až 23:59.",
        L"Odobrať vybraný panel?",
        L"Musí zostať aspoň jeden panel.",
        L"Zavrieť"
    },
    {
        L"Clocks and calendars",
        L"Settings",
        L"Add",
        L"Remove...",
        L"Duplicate",
        L"General",
        L"Appearance",
        L"Alarm",
        L"Name:",
        L"Type:",
        L"Visible",
        L"Always on top",
        L"Seconds",
        L"UTC time",
        L"Time zone:",
        L"Offset [-]HH:mm:ss.ff:",
        L"Size:",
        L"Opacity:",
        L"Font size:",
        L"Leading zero",
        L"Transparent background",
        L"Text color...",
        L"Background color...",
        L"Week numbers",
        L"Sunday first",
        L"Alarm enabled",
        L"Alarm time:",
        L"Run a file or command",
        L"Loop audio continuously",
        L"Browse...",
        L"Language:",
        L"Disable themes",
        L"Save",
        L"Apply",
        L"Cancel",
        L"Show all",
        L"Hide all",
        L"Stop alarm",
        L"Help",
        L"About",
        L"Exit",
        L"Analog clock",
        L"Digital clock",
        L"Calendar",
        L"Calendar with clock",
        L"Enter the offset as [-]HH:mm:ss.ff.",
        L"Enter a valid time from 0:00 to 23:59.",
        L"Remove the selected widgets?",
        L"At least one widget must remain.",
        L"Close"
    },
    {
        L"Clocks and calendars",
        L"Settings",
        L"Add",
        L"Remove...",
        L"Duplicate",
        L"General",
        L"Appearance",
        L"Alarm",
        L"Name:",
        L"Type:",
        L"Visible",
        L"Always on top",
        L"Seconds",
        L"UTC time",
        L"Time zone:",
        L"Offset [-]HH:mm:ss.ff:",
        L"Size:",
        L"Opacity:",
        L"Font size:",
        L"Leading zero",
        L"Transparent background",
        L"Text color...",
        L"Background color...",
        L"Week numbers",
        L"Sunday first",
        L"Alarm enabled",
        L"Alarm time:",
        L"Run a file or command",
        L"Loop audio continuously",
        L"Browse...",
        L"Language:",
        L"Disable themes",
        L"Save",
        L"Apply",
        L"Cancel",
        L"Show all",
        L"Hide all",
        L"Stop alarm",
        L"Help",
        L"About",
        L"Exit",
        L"Analog clock",
        L"Digital clock",
        L"Calendar",
        L"Calendar with clock",
        L"Enter the offset as [-]HH:mm:ss.ff.",
        L"Enter a valid time from 0:00 to 23:59.",
        L"Remove the selected widgets?",
        L"At least one widget must remain.",
        L"Close"
    },
    {
        L"Relógios e calendários",
        L"Definições",
        L"Adicionar",
        L"Remover...",
        L"Duplicar",
        L"Geral",
        L"Aspeto",
        L"Alarme",
        L"Nome:",
        L"Tipo:",
        L"Visível",
        L"Sempre no topo",
        L"Segundos",
        L"Hora UTC",
        L"Fuso horário:",
        L"Desvio [-]HH:mm:ss.ff:",
        L"Tamanho:",
        L"Opacidade:",
        L"Tamanho da letra:",
        L"Zero à esquerda",
        L"Fundo transparente",
        L"Cor do texto...",
        L"Cor de fundo...",
        L"Números das semanas",
        L"Domingo primeiro",
        L"Alarme ativo",
        L"Hora do alarme:",
        L"Executar um ficheiro ou comando",
        L"Repetir áudio continuamente",
        L"Procurar...",
        L"Idioma:",
        L"Desativar temas",
        L"Guardar",
        L"Aplicar",
        L"Cancelar",
        L"Mostrar tudo",
        L"Ocultar tudo",
        L"Parar alarme",
        L"Ajuda",
        L"Acerca de",
        L"Sair",
        L"Relógio analógico",
        L"Relógio digital",
        L"Calendário",
        L"Calendário com relógio",
        L"Introduza o desvio como [-]HH:mm:ss.ff.",
        L"Introduza uma hora válida entre 0:00 e 23:59.",
        L"Remover os widgets selecionados?",
        L"Tem de permanecer pelo menos um widget.",
        L"Fechar"
    },
    {
        L"Klokker og kalendere",
        L"Innstillinger",
        L"Legg til",
        L"Fjern...",
        L"Dupliser",
        L"Generelt",
        L"Utseende",
        L"Alarm",
        L"Navn:",
        L"Type:",
        L"Synlig",
        L"Alltid øverst",
        L"Sekunder",
        L"UTC-tid",
        L"Tidssone:",
        L"Forskyvning [-]HH:mm:ss.ff:",
        L"Størrelse:",
        L"Ugjennomsiktighet:",
        L"Skriftstørrelse:",
        L"Innledende null",
        L"Gjennomsiktig bakgrunn",
        L"Tekstfarge...",
        L"Bakgrunnsfarge...",
        L"Ukenumre",
        L"Søndag først",
        L"Alarm aktiv",
        L"Alarmtid:",
        L"Kjør en fil eller kommando",
        L"Gjenta lyd kontinuerlig",
        L"Bla gjennom...",
        L"Språk:",
        L"Deaktiver temaer",
        L"Lagre",
        L"Bruk",
        L"Avbryt",
        L"Vis alle",
        L"Skjul alle",
        L"Stopp alarm",
        L"Hjelp",
        L"Om",
        L"Avslutt",
        L"Analog klokke",
        L"Digital klokke",
        L"Kalender",
        L"Kalender med klokke",
        L"Angi forskyvningen som [-]HH:mm:ss.ff.",
        L"Angi et gyldig klokkeslett fra 0:00 til 23:59.",
        L"Fjerne de valgte widgetene?",
        L"Minst én widget må beholdes.",
        L"Lukk"
    },
    {
        L"Klockor och kalendrar",
        L"Inställningar",
        L"Lägg till",
        L"Ta bort...",
        L"Duplicera",
        L"Allmänt",
        L"Utseende",
        L"Alarm",
        L"Namn:",
        L"Typ:",
        L"Synlig",
        L"Alltid överst",
        L"Sekunder",
        L"UTC-tid",
        L"Tidszon:",
        L"Förskjutning [-]HH:mm:ss.ff:",
        L"Storlek:",
        L"Opacitet:",
        L"Teckenstorlek:",
        L"Inledande nolla",
        L"Genomskinlig bakgrund",
        L"Textfärg...",
        L"Bakgrundsfärg...",
        L"Veckonummer",
        L"Söndag först",
        L"Alarm aktivt",
        L"Alarmtid:",
        L"Kör en fil eller ett kommando",
        L"Upprepa ljud kontinuerligt",
        L"Bläddra...",
        L"Språk:",
        L"Inaktivera teman",
        L"Spara",
        L"Verkställ",
        L"Avbryt",
        L"Visa alla",
        L"Dölj alla",
        L"Stoppa alarm",
        L"Hjälp",
        L"Om",
        L"Avsluta",
        L"Analog klocka",
        L"Digital klocka",
        L"Kalender",
        L"Kalender med klocka",
        L"Ange förskjutningen som [-]HH:mm:ss.ff.",
        L"Ange en giltig tid mellan 0:00 och 23:59.",
        L"Ta bort de markerade widgetarna?",
        L"Minst en widget måste finnas kvar.",
        L"Stäng"
    },
    {
        L"Kellot ja kalenterit",
        L"Asetukset",
        L"Lisää",
        L"Poista...",
        L"Monista",
        L"Yleiset",
        L"Ulkoasu",
        L"Herätys",
        L"Nimi:",
        L"Tyyppi:",
        L"Näkyvissä",
        L"Aina päällimmäisenä",
        L"Sekunnit",
        L"UTC-aika",
        L"Aikavyöhyke:",
        L"Poikkeama [-]HH:mm:ss.ff:",
        L"Koko:",
        L"Peittävyys:",
        L"Fonttikoko:",
        L"Etunolla",
        L"Läpinäkyvä tausta",
        L"Tekstin väri...",
        L"Taustaväri...",
        L"Viikkonumerot",
        L"Sunnuntai ensin",
        L"Herätys käytössä",
        L"Herätysaika:",
        L"Suorita tiedosto tai komento",
        L"Toista ääntä jatkuvasti",
        L"Selaa...",
        L"Kieli:",
        L"Poista teemat käytöstä",
        L"Tallenna",
        L"Käytä",
        L"Peruuta",
        L"Näytä kaikki",
        L"Piilota kaikki",
        L"Pysäytä herätys",
        L"Ohje",
        L"Tietoja",
        L"Lopeta",
        L"Analoginen kello",
        L"Digitaalinen kello",
        L"Kalenteri",
        L"Kalenteri ja kello",
        L"Anna poikkeama muodossa [-]HH:mm:ss.ff.",
        L"Anna kelvollinen aika väliltä 0:00–23:59.",
        L"Poistetaanko valitut pienoisohjelmat?",
        L"Vähintään yhden pienoisohjelman on jäätävä.",
        L"Sulje"
    },
    {
        L"Ure og kalendere",
        L"Indstillinger",
        L"Tilføj",
        L"Fjern...",
        L"Dupliker",
        L"Generelt",
        L"Udseende",
        L"Alarm",
        L"Navn:",
        L"Type:",
        L"Synlig",
        L"Altid øverst",
        L"Sekunder",
        L"UTC-tid",
        L"Tidszone:",
        L"Forskydning [-]HH:mm:ss.ff:",
        L"Størrelse:",
        L"Uigennemsigtighed:",
        L"Skriftstørrelse:",
        L"Foranstillet nul",
        L"Gennemsigtig baggrund",
        L"Tekstfarve...",
        L"Baggrundsfarve...",
        L"Ugenumre",
        L"Søndag først",
        L"Alarm aktiv",
        L"Alarmtid:",
        L"Kør en fil eller kommando",
        L"Gentag lyd kontinuerligt",
        L"Gennemse...",
        L"Sprog:",
        L"Deaktiver temaer",
        L"Gem",
        L"Anvend",
        L"Annuller",
        L"Vis alle",
        L"Skjul alle",
        L"Stop alarm",
        L"Hjælp",
        L"Om",
        L"Afslut",
        L"Analogt ur",
        L"Digitalt ur",
        L"Kalender",
        L"Kalender med ur",
        L"Angiv forskydningen som [-]HH:mm:ss.ff.",
        L"Angiv et gyldigt tidspunkt fra 0:00 til 23:59.",
        L"Fjern de valgte widgets?",
        L"Mindst én widget skal bevares.",
        L"Luk"
    },
    {
        L"Klukkur og dagatöl",
        L"Stillingar",
        L"Bæta við",
        L"Fjarlægja...",
        L"Afrita",
        L"Almennt",
        L"Útlit",
        L"Vekjari",
        L"Heiti:",
        L"Tegund:",
        L"Sýnilegt",
        L"Alltaf efst",
        L"Sekúndur",
        L"UTC-tími",
        L"Tímabelti:",
        L"Hliðrun [-]HH:mm:ss.ff:",
        L"Stærð:",
        L"Ógegnsæi:",
        L"Leturstærð:",
        L"Núll fremst",
        L"Gegnsær bakgrunnur",
        L"Textalitur...",
        L"Bakgrunnslitur...",
        L"Vikunúmer",
        L"Sunnudagur fyrst",
        L"Vekjari virkur",
        L"Tími vekjara:",
        L"Keyra skrá eða skipun",
        L"Endurtaka hljóð stöðugt",
        L"Velja...",
        L"Tungumál:",
        L"Slökkva á þemum",
        L"Vista",
        L"Nota",
        L"Hætta við",
        L"Sýna allt",
        L"Fela allt",
        L"Stöðva vekjara",
        L"Hjálp",
        L"Um",
        L"Loka",
        L"Skífuklukka",
        L"Stafræn klukka",
        L"Dagatal",
        L"Dagatal með klukku",
        L"Sláðu inn hliðrun sem [-]HH:mm:ss.ff.",
        L"Sláðu inn gildan tíma frá 0:00 til 23:59.",
        L"Fjarlægja valdar græjur?",
        L"Að minnsta kosti ein græja verður að vera eftir.",
        L"Loka"
    },
    {
        L"Saatler ve takvimler",
        L"Ayarlar",
        L"Ekle",
        L"Kaldır...",
        L"Çoğalt",
        L"Genel",
        L"Görünüm",
        L"Alarm",
        L"Ad:",
        L"Tür:",
        L"Görünür",
        L"Her zaman üstte",
        L"Saniyeler",
        L"UTC saati",
        L"Saat dilimi:",
        L"Ofset [-]HH:mm:ss.ff:",
        L"Boyut:",
        L"Opaklık:",
        L"Yazı tipi boyutu:",
        L"Baştaki sıfır",
        L"Saydam arka plan",
        L"Metin rengi...",
        L"Arka plan rengi...",
        L"Hafta numaraları",
        L"Pazar ilk gün",
        L"Alarm etkin",
        L"Alarm saati:",
        L"Dosya veya komut çalıştır",
        L"Sesi sürekli yinele",
        L"Gözat...",
        L"Dil:",
        L"Temaları devre dışı bırak",
        L"Kaydet",
        L"Uygula",
        L"İptal",
        L"Tümünü göster",
        L"Tümünü gizle",
        L"Alarmı durdur",
        L"Yardım",
        L"Hakkında",
        L"Çıkış",
        L"Analog saat",
        L"Dijital saat",
        L"Takvim",
        L"Saatli takvim",
        L"Ofseti [-]HH:mm:ss.ff biçiminde girin.",
        L"0:00 ile 23:59 arasında geçerli bir saat girin.",
        L"Seçili araçlar kaldırılsın mı?",
        L"En az bir araç kalmalıdır.",
        L"Kapat"
    }
};

const wchar_t* LANGUAGE_NAMES[LANG_COUNT] = {
    L"Čeština",
    L"English (US)",
    L"Deutsch",
    L"Français",
    L"Español",
    L"Italiano",
    L"Polski",
    L"Slovenčina",
    L"English (UK)",
    L"English (Australia)",
    L"Português",
    L"Norsk",
    L"Svenska",
    L"Suomi",
    L"Dansk",
    L"Íslenska",
    L"Türkçe"
};

const wchar_t* FULLSCREEN_WIDGET_NAMES[LANG_COUNT] = {
    L"Hodiny na monitoru",
    L"Monitor clock",
    L"Monitoruhr",
    L"Horloge sur moniteur",
    L"Reloj de monitor",
    L"Orologio su monitor",
    L"Zegar na monitorze",
    L"Hodiny na monitore",
    L"Monitor clock",
    L"Monitor clock",
    L"Relógio no monitor",
    L"Skjermklokke",
    L"Skärmklocka",
    L"Näyttökello",
    L"Skærmur",
    L"Skjákukka",
    L"Monitör saati"
};

const wchar_t* COMMAND_FILE_FILTERS[LANG_COUNT] = {
    L"Zvuk a programy\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Všechny soubory\0*.*\0",
    L"Audio and programs\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0All files\0*.*\0",
    L"Audio und Programme\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Alle Dateien\0*.*\0",
    L"Audio et programmes\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Tous les fichiers\0*.*\0",
    L"Audio y programas\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Todos los archivos\0*.*\0",
    L"Audio e programmi\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Tutti i file\0*.*\0",
    L"Dźwięk i programy\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Wszystkie pliki\0*.*\0",
    L"Zvuk a programy\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Všetky súbory\0*.*\0",
    L"Audio and programs\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0All files\0*.*\0",
    L"Audio and programs\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0All files\0*.*\0",
    L"Áudio e programas\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Todos os ficheiros\0*.*\0",
    L"Lyd og programmer\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Alle filer\0*.*\0",
    L"Ljud och program\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Alla filer\0*.*\0",
    L"Ääni ja ohjelmat\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Kaikki tiedostot\0*.*\0",
    L"Lyd og programmer\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Alle filer\0*.*\0",
    L"Hljóð og forrit\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Allar skrár\0*.*\0",
    L"Ses ve programlar\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Tüm dosyalar\0*.*\0"
};

const wchar_t* LANGUAGE_LOCALES[LANG_COUNT] = {
    L"cs-CZ",
    L"en-US",
    L"de-DE",
    L"fr-FR",
    L"es-ES",
    L"it-IT",
    L"pl-PL",
    L"sk-SK",
    L"en-GB",
    L"en-AU",
    L"pt-PT",
    L"nb-NO",
    L"sv-SE",
    L"fi-FI",
    L"da-DK",
    L"is-IS",
    L"tr-TR"
};

const wchar_t* WIDGET_LANGUAGE_LABELS[LANG_COUNT] = {
    L"Jazyk widgetu:",
    L"Widget language:",
    L"Widget-Sprache:",
    L"Langue du widget :",
    L"Idioma del widget:",
    L"Lingua del widget:",
    L"Język widżetu:",
    L"Jazyk widgetu:",
    L"Widget language:",
    L"Widget language:",
    L"Idioma do widget:",
    L"Widgetspråk:",
    L"Widgetspråk:",
    L"Pienoisohjelman kieli:",
    L"Widgetsprog:",
    L"Tungumál græju:",
    L"Araç dili:"
};

const wchar_t* APPLICATION_LANGUAGE_LABELS[LANG_COUNT] = {
    L"&Jazyk aplikace:",
    L"Application &language:",
    L"&Anwendungssprache:",
    L"&Langue de l’application :",
    L"&Idioma de la aplicación:",
    L"&Lingua applicazione:",
    L"Język &aplikacji:",
    L"&Jazyk aplikácie:",
    L"Application &language:",
    L"Application &language:",
    L"&Idioma da aplicação:",
    L"Program&språk:",
    L"Program&språk:",
    L"Sovelluksen &kieli:",
    L"Program&sprog:",
    L"&Tungumál forrits:",
    L"Uygulama &dili:"
};

const wchar_t* APPLICATION_FONT_LABELS[LANG_COUNT] = {
    L"&Písmo aplikace:",
    L"Application &font:",
    L"Anwendungs&schrift:",
    L"&Police de l’application :",
    L"&Fuente de la aplicación:",
    L"&Carattere applicazione:",
    L"&Czcionka aplikacji:",
    L"&Písmo aplikácie:",
    L"Application &font:",
    L"Application &font:",
    L"&Tipo de letra da aplicação:",
    L"Program&skrift:",
    L"Program&teckensnitt:",
    L"Sovelluksen &fontti:",
    L"Program&skrifttype:",
    L"&Letur forrits:",
    L"Uygulama &yazı tipi:"
};

const wchar_t* SYSTEM_DEFAULT_FONT_LABELS[LANG_COUNT] = {
    L"Výchozí systémové",
    L"System default",
    L"Systemstandard",
    L"Valeur système",
    L"Predeterminada del sistema",
    L"Predefinito di sistema",
    L"Domyślna systemowa",
    L"Predvolené systémové",
    L"System default",
    L"System default",
    L"Predefinição do sistema",
    L"Systemstandard",
    L"Systemstandard",
    L"Järjestelmän oletus",
    L"Systemstandard",
    L"Sjálfgefið kerfisletur",
    L"Sistem varsayılanı"
};

const wchar_t* DATE_COPY_LABELS[LANG_COUNT] = {
    L"&Formát kopírovaného data",
    L"Copied &date format",
    L"Format des kopierten &Datums",
    L"Format de date &copié",
    L"Formato de fecha &copiada",
    L"Formato data &copiata",
    L"Format &kopiowanej daty",
    L"Formát &kopírovaného dátumu",
    L"Copied &date format",
    L"Copied &date format",
    L"&Formato da data copiada",
    L"Format for kopiert &dato",
    L"Format för kopierat &datum",
    L"Kopioidun &päivämäärän muoto",
    L"Format for kopieret &dato",
    L"Snið afritaðrar &dagsetningar",
    L"Kopyalanan &tarih biçimi"
};

const wchar_t* DATE_FORMAT_LABELS[LANG_COUNT] = {
    L"Formát &kopírovaného data:",
    L"Copied &date format:",
    L"Format des kopierten &Datums:",
    L"Format de date &copié :",
    L"Formato de fecha &copiada:",
    L"Formato data &copiata:",
    L"Format &kopiowanej daty:",
    L"Formát &kopírovaného dátumu:",
    L"Copied &date format:",
    L"Copied &date format:",
    L"&Formato da data copiada:",
    L"Format for kopiert &dato:",
    L"Format för kopierat &datum:",
    L"Kopioidun &päivämäärän muoto:",
    L"Format for kopieret &dato:",
    L"Snið afritaðrar &dagsetningar:",
    L"Kopyalanan &tarih biçimi:"
};

const wchar_t* LOCAL_SHORT_LABELS[LANG_COUNT] = {
    L"Krátké datum",
    L"Short date",
    L"Kurzes Datum",
    L"Date courte",
    L"Fecha corta",
    L"Data breve",
    L"Data krótka",
    L"Krátky dátum",
    L"Short date",
    L"Short date",
    L"Data abreviada",
    L"Kort dato",
    L"Kort datum",
    L"Lyhyt päivämäärä",
    L"Kort dato",
    L"Stutt dagsetning",
    L"Kısa tarih"
};

const wchar_t* LOCAL_LONG_LABELS[LANG_COUNT] = {
    L"Dlouhé datum",
    L"Long date",
    L"Langes Datum",
    L"Date longue",
    L"Fecha larga",
    L"Data estesa",
    L"Data długa",
    L"Dlhý dátum",
    L"Long date",
    L"Long date",
    L"Data por extenso",
    L"Lang dato",
    L"Långt datum",
    L"Pitkä päivämäärä",
    L"Lang dato",
    L"Löng dagsetning",
    L"Uzun tarih"
};

const wchar_t* ARRANGE_WIDGET_LABELS[LANG_COUNT] = {
    L"&Zarovnat do mřížky",
    L"&Arrange in a grid",
    L"Im &Raster anordnen",
    L"&Aligner sur une grille",
    L"&Alinear en cuadrícula",
    L"&Disponi in griglia",
    L"&Ułóż w siatce",
    L"&Zarovnať do mriežky",
    L"&Arrange in a grid",
    L"&Arrange in a grid",
    L"&Dispor numa grelha",
    L"&Ordne i et rutenett",
    L"&Ordna i ett rutnät",
    L"&Järjestä ruudukkoon",
    L"&Arranger i et gitter",
    L"&Raða á hnitanet",
    L"&Izgarada düzenle"
};

const wchar_t* SHOW_WIDGET_LABELS[LANG_COUNT] = {
    L"&Zobrazit",
    L"&Show",
    L"&Anzeigen",
    L"&Afficher",
    L"&Mostrar",
    L"&Mostra",
    L"&Pokaż",
    L"&Zobraziť",
    L"&Show",
    L"&Show",
    L"&Mostrar",
    L"&Vis",
    L"&Visa",
    L"&Näytä",
    L"&Vis",
    L"&Sýna",
    L"&Göster"
};

const wchar_t* HIDE_WIDGET_LABELS[LANG_COUNT] = {
    L"&Skrýt",
    L"&Hide",
    L"A&usblenden",
    L"&Masquer",
    L"&Ocultar",
    L"&Nascondi",
    L"&Ukryj",
    L"&Skryť",
    L"&Hide",
    L"&Hide",
    L"&Ocultar",
    L"&Skjul",
    L"&Dölj",
    L"&Piilota",
    L"&Skjul",
    L"&Fela",
    L"&Gizle"
};

const wchar_t* UTC_TEXT_LABELS[LANG_COUNT] = {
    L"Zobrazit text &UTC",
    L"Show &UTC text",
    L"&UTC-Text anzeigen",
    L"Afficher le texte &UTC",
    L"Mostrar texto &UTC",
    L"Mostra testo &UTC",
    L"Pokaż tekst &UTC",
    L"Zobraziť text &UTC",
    L"Show &UTC text",
    L"Show &UTC text",
    L"Mostrar texto &UTC",
    L"Vis &UTC-tekst",
    L"Visa &UTC-text",
    L"Näytä &UTC-teksti",
    L"Vis &UTC-tekst",
    L"Sýna &UTC-texta",
    L"&UTC metnini göster"
};

const wchar_t* MONITOR_LABELS[LANG_COUNT] = {
    L"&Monitory:",
    L"&Monitors:",
    L"&Monitore:",
    L"&Moniteurs :",
    L"&Monitores:",
    L"&Monitor:",
    L"&Monitory:",
    L"&Monitory:",
    L"&Monitors:",
    L"&Monitors:",
    L"&Monitores:",
    L"&Skjermer:",
    L"&Bildskärmar:",
    L"&Näytöt:",
    L"&Skærme:",
    L"&Skjáir:",
    L"&Monitörler:"
};

const wchar_t* BLACKOUT_MONITOR_LABELS[LANG_COUNT] = {
    L"Zatemnit &ostatní monitory",
    L"Black out &other monitors",
    L"&Andere Monitore abdunkeln",
    L"Assombrir les &autres moniteurs",
    L"Oscurecer &otros monitores",
    L"Oscura gli &altri monitor",
    L"Wygasz &pozostałe monitory",
    L"Stmaviť &ostatné monitory",
    L"Black out &other monitors",
    L"Black out &other monitors",
    L"Escurecer os &outros monitores",
    L"Mørklegg &andre skjermer",
    L"Släck &andra bildskärmar",
    L"Pimennä &muut näytöt",
    L"Mørklæg &andre skærme",
    L"Myrkva &aðra skjái",
    L"&Diğer monitörleri karart"
};

const wchar_t* FONT_BUTTON_LABELS[LANG_COUNT] = {
    L"Vybrat &písmo...",
    L"Choose &font...",
    L"&Schriftart wählen...",
    L"Choisir la &police...",
    L"Elegir &fuente...",
    L"Scegli &carattere...",
    L"Wybierz &czcionkę...",
    L"Vybrať &písmo...",
    L"Choose &font...",
    L"Choose &font...",
    L"Escolher &tipo de letra...",
    L"Velg &skrift...",
    L"Välj &teckensnitt...",
    L"Valitse &fontti...",
    L"Vælg &skrifttype...",
    L"Velja &letur...",
    L"&Yazı tipi seç..."
};

const wchar_t* CALENDAR_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &kalendáře...",
    L"&Calendar font...",
    L"&Kalenderschrift...",
    L"Police du &calendrier...",
    L"Fuente del &calendario...",
    L"Carattere del &calendario...",
    L"Czcionka &kalendarza...",
    L"Písmo &kalendára...",
    L"&Calendar font...",
    L"&Calendar font...",
    L"Tipo de letra do &calendário...",
    L"&Kalenderskrift...",
    L"&Kalenderteckensnitt...",
    L"&Kalenterin fontti...",
    L"&Kalenderskrifttype...",
    L"Letur &dagatals...",
    L"&Takvim yazı tipi..."
};

const wchar_t* PANEL_TOP_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &horního řádku...",
    L"&Top row font...",
    L"Schrift der &oberen Zeile...",
    L"Police de la ligne &supérieure...",
    L"Fuente de la línea &superior...",
    L"Carattere riga &superiore...",
    L"Czcionka &górnego wiersza...",
    L"Písmo &horného riadka...",
    L"&Top row font...",
    L"&Top row font...",
    L"Tipo de letra da linha &superior...",
    L"Skrift for &øverste rad...",
    L"Teckensnitt för &översta raden...",
    L"&Ylärivin fontti...",
    L"Skrifttype for &øverste linje...",
    L"Letur &efri línu...",
    L"&Üst satır yazı tipi..."
};

const wchar_t* PANEL_TODAY_TOOLTIP[LANG_COUNT] = {
    L"Přejít na dnešek",
    L"Go to Today",
    L"Gehe zu Heute",
    L"Aller à aujourd’hui",
    L"Ir a hoy",
    L"Vai a oggi",
    L"Przejdź do dnia dzisiejszego",
    L"Prejsť na dnešný deň",
    L"Go to Today",
    L"Go to Today",
    L"Ir para hoje",
    L"Gå til i dag",
    L"Gå till i dag",
    L"Siirry tähän päivään",
    L"Gå til i dag",
    L"Fara á daginn í dag",
    L"Bugüne git"
};

const wchar_t* PANEL_TIME_FONT_LABELS[LANG_COUNT] = {
    L"Písmo č&asu...",
    L"&Time font...",
    L"&Zeitschrift...",
    L"Police de l’&heure...",
    L"Fuente de la &hora...",
    L"Carattere dell’&ora...",
    L"Czcionka &czasu...",
    L"Písmo č&asu...",
    L"&Time font...",
    L"&Time font...",
    L"Tipo de letra da &hora...",
    L"&Tidsskrift...",
    L"&Tidsteckensnitt...",
    L"&Ajan fontti...",
    L"Skrifttype for &tid...",
    L"Letur &tíma...",
    L"&Saat yazı tipi..."
};

const wchar_t* PANEL_BOTTOM_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &spodního řádku...",
    L"&Bottom row font...",
    L"Schrift der &unteren Zeile...",
    L"Police de la ligne &inférieure...",
    L"Fuente de la línea &inferior...",
    L"Carattere riga &inferiore...",
    L"Czcionka &dolnego wiersza...",
    L"Písmo &spodného riadka...",
    L"&Bottom row font...",
    L"&Bottom row font...",
    L"Tipo de letra da linha &inferior...",
    L"Skrift for &nederste rad...",
    L"Teckensnitt för &nedersta raden...",
    L"&Alarivin fontti...",
    L"Skrifttype for &nederste linje...",
    L"Letur &neðri línu...",
    L"&Alt satır yazı tipi..."
};

const wchar_t* DEFAULT_FONT_LABELS[LANG_COUNT] = {
    L"Vý&chozí",
    L"&Default",
    L"&Standard",
    L"Par &défaut",
    L"&Predeterminada",
    L"&Predefinito",
    L"&Domyślna",
    L"&Predvolené",
    L"&Default",
    L"&Default",
    L"&Predefinição",
    L"&Standard",
    L"&Standard",
    L"&Oletus",
    L"&Standard",
    L"&Sjálfgefið",
    L"&Varsayılan"
};

const wchar_t* ALARM_TEXT_COLOR_LABELS[LANG_COUNT] = {
    L"Barva &textu budíku...",
    L"Alarm &text color...",
    L"&Wecker-Textfarbe...",
    L"Couleur du &texte d’alarme...",
    L"Color del &texto de alarma...",
    L"Colore &testo sveglia...",
    L"Kolor &tekstu alarmu...",
    L"Farba &textu budíka...",
    L"Alarm &text color...",
    L"Alarm &text color...",
    L"Cor do &texto do alarme...",
    L"Alarmens &tekstfarge...",
    L"Alarmets &textfärg...",
    L"Herätyksen &tekstiväri...",
    L"Alarmens &tekstfarve...",
    L"&Textalitur vekjara...",
    L"Alarm &metin rengi..."
};

const wchar_t* ALARM_BACKGROUND_COLOR_LABELS[LANG_COUNT] = {
    L"Barva &pozadí budíku...",
    L"Alarm &background...",
    L"Wecker-&Hintergrund...",
    L"&Fond de l’alarme...",
    L"&Fondo de alarma...",
    L"&Sfondo sveglia...",
    L"&Tło alarmu...",
    L"Farba &pozadia budíka...",
    L"Alarm &background...",
    L"Alarm &background...",
    L"Cor de &fundo do alarme...",
    L"Alarmens &bakgrunn...",
    L"Alarmets &bakgrund...",
    L"Herätyksen &tausta...",
    L"Alarmens &baggrund...",
    L"&Bakgrunnslitur vekjara...",
    L"Alarm &arka planı..."
};

const wchar_t* PADDING_LABELS[LANG_COUNT] = {
    L"&Odsazení:",
    L"&Padding:",
    L"&Innenabstand:",
    L"&Marge interne :",
    L"&Relleno:",
    L"&Margine:",
    L"&Odstęp:",
    L"&Odsadenie:",
    L"&Padding:",
    L"&Padding:",
    L"&Margem:",
    L"&Luft:",
    L"&Utfyllnad:",
    L"&Täyttö:",
    L"&Luft:",
    L"&Bil:",
    L"&Dolgu:"
};

const wchar_t* BORDER_LABELS[LANG_COUNT] = {
    L"&Styl rámečku:",
    L"&Border style:",
    L"&Rahmenstil:",
    L"Style de &bordure :",
    L"Estilo de &borde:",
    L"Stile &bordo:",
    L"Styl &ramki:",
    L"Štýl &rámčeka:",
    L"&Border style:",
    L"&Border style:",
    L"&Estilo da moldura:",
    L"&Rammestil:",
    L"&Ramstil:",
    L"&Reunatyyli:",
    L"&Rammestil:",
    L"&Rammastíll:",
    L"&Çerçeve stili:"
};

const wchar_t* BORDER_COLOR_LABELS[LANG_COUNT] = {
    L"Barva rámečku...",
    L"Border color...",
    L"Rahmenfarbe...",
    L"Couleur de bordure...",
    L"Color del borde...",
    L"Colore bordo...",
    L"Kolor ramki...",
    L"Farba rámčeka...",
    L"Border colour...",
    L"Border colour...",
    L"Cor da moldura...",
    L"Rammefarge...",
    L"Ramfärg...",
    L"Reunuksen väri...",
    L"Rammefarve...",
    L"Litur ramma...",
    L"Çerçeve rengi..."
};

const wchar_t* BORDER_WIDTH_LABELS[LANG_COUNT] = {
    L"Šíř&ka rámečku:",
    L"Border &width:",
    L"Rahmen&breite:",
    L"É&paisseur :",
    L"&Ancho:",
    L"&Spessore:",
    L"&Szerokość:",
    L"Šír&ka rám.:",
    L"Border &width:",
    L"Border &width:",
    L"&Largura:",
    L"Ramme&bredde:",
    L"Ram&bredd:",
    L"Reunan &leveys:",
    L"Ramme&bredde:",
    L"&Breidd ramma:",
    L"Çerçeve &genişliği:"
};

const wchar_t* TIME_SIGNAL_TAB_LABELS[LANG_COUNT] = {
    L"Znamení",
    L"Signal",
    L"Zeitzeichen",
    L"Signal",
    L"Señal",
    L"Segnale",
    L"Sygnał",
    L"Znamenie",
    L"Signal",
    L"Signal",
    L"Sinal",
    L"Signal",
    L"Signal",
    L"Aikamerkki",
    L"Signal",
    L"Tímamerki",
    L"Sinyal"
};

const wchar_t* TIME_SIGNAL_MENU_LABELS[LANG_COUNT] = {
    L"&Signál",
    L"&Signal",
    L"&Zeitzeichen",
    L"&Signal",
    L"&Señal",
    L"&Segnale",
    L"&Sygnał",
    L"&Signál",
    L"&Signal",
    L"&Signal",
    L"&Sinal",
    L"&Signal",
    L"&Signal",
    L"&Aikamerkki",
    L"&Signal",
    L"&Tímamerki",
    L"&Sinyal"
};

const wchar_t* TIME_SIGNAL_FIELD_LABELS[LANG_COUNT] = {
    L"Zvukové &časové znamení:",
    L"&Audible time signal:",
    L"Akustisches &Zeitzeichen:",
    L"&Signal horaire sonore :",
    L"Señal horaria &sonora:",
    L"Segnale orario &acustico:",
    L"&Dźwiękowy sygnał czasu:",
    L"Zvukové č&asové znamenie:",
    L"&Audible time signal:",
    L"&Audible time signal:",
    L"&Sinal horário sonoro:",
    L"&Hørbart tidssignal:",
    L"&Hörbar tidssignal:",
    L"&Äänimerkki:",
    L"&Hørbart tidssignal:",
    L"&Hljóðtímamerki:",
    L"&Sesli zaman sinyali:"
};

const wchar_t* TIME_SIGNAL_MODE_LABELS[LANG_COUNT][TIME_SIGNAL_COUNT] = {
    {
        L"Žádné",
        L"Každou minutu",
        L"Každých 5 minut",
        L"Každých 10 minut",
        L"Každou čtvrthodinu",
        L"Každých 20 minut",
        L"Každou půlhodinu",
        L"Každou hodinu"
    },
    {
        L"None",
        L"Every minute",
        L"Every 5 minutes",
        L"Every 10 minutes",
        L"Every quarter hour",
        L"Every 20 minutes",
        L"Every half hour",
        L"Every hour"
    },
    {
        L"Kein",
        L"Jede Minute",
        L"Alle 5 Minuten",
        L"Alle 10 Minuten",
        L"Jede Viertelstunde",
        L"Alle 20 Minuten",
        L"Jede halbe Stunde",
        L"Jede Stunde"
    },
    {
        L"Aucun",
        L"Chaque minute",
        L"Toutes les 5 minutes",
        L"Toutes les 10 minutes",
        L"Chaque quart d’heure",
        L"Toutes les 20 minutes",
        L"Chaque demi-heure",
        L"Chaque heure"
    },
    {
        L"Ninguno",
        L"Cada minuto",
        L"Cada 5 minutos",
        L"Cada 10 minutos",
        L"Cada cuarto de hora",
        L"Cada 20 minutos",
        L"Cada media hora",
        L"Cada hora"
    },
    {
        L"Nessuno",
        L"Ogni minuto",
        L"Ogni 5 minuti",
        L"Ogni 10 minuti",
        L"Ogni quarto d’ora",
        L"Ogni 20 minuti",
        L"Ogni mezz’ora",
        L"Ogni ora"
    },
    {
        L"Brak",
        L"Co minutę",
        L"Co 5 minut",
        L"Co 10 minut",
        L"Co kwadrans",
        L"Co 20 minut",
        L"Co pół godziny",
        L"Co godzinę"
    },
    {
        L"Žiadne",
        L"Každú minútu",
        L"Každých 5 minút",
        L"Každých 10 minút",
        L"Každú štvrťhodinu",
        L"Každých 20 minút",
        L"Každú polhodinu",
        L"Každú hodinu"
    },
    {
        L"None",
        L"Every minute",
        L"Every 5 minutes",
        L"Every 10 minutes",
        L"Every quarter hour",
        L"Every 20 minutes",
        L"Every half hour",
        L"Every hour"
    },
    {
        L"None",
        L"Every minute",
        L"Every 5 minutes",
        L"Every 10 minutes",
        L"Every quarter hour",
        L"Every 20 minutes",
        L"Every half hour",
        L"Every hour"
    },
    {
        L"Nenhum",
        L"A cada minuto",
        L"A cada 5 minutos",
        L"A cada 10 minutos",
        L"A cada quarto de hora",
        L"A cada 20 minutos",
        L"A cada meia hora",
        L"A cada hora"
    },
    {
        L"Ingen",
        L"Hvert minutt",
        L"Hvert 5. minutt",
        L"Hvert 10. minutt",
        L"Hvert kvarter",
        L"Hvert 20. minutt",
        L"Hver halvtime",
        L"Hver time"
    },
    {
        L"Ingen",
        L"Varje minut",
        L"Var 5:e minut",
        L"Var 10:e minut",
        L"Varje kvart",
        L"Var 20:e minut",
        L"Varje halvtimme",
        L"Varje timme"
    },
    {
        L"Ei mitään",
        L"Minuutin välein",
        L"5 minuutin välein",
        L"10 minuutin välein",
        L"15 minuutin välein",
        L"20 minuutin välein",
        L"30 minuutin välein",
        L"Tunnin välein"
    },
    {
        L"Intet",
        L"Hvert minut",
        L"Hvert 5. minut",
        L"Hvert 10. minut",
        L"Hvert kvarter",
        L"Hvert 20. minut",
        L"Hver halve time",
        L"Hver time"
    },
    {
        L"Ekkert",
        L"Á hverri mínútu",
        L"Á 5 mínútna fresti",
        L"Á 10 mínútna fresti",
        L"Á stundarfjórðungs fresti",
        L"Á 20 mínútna fresti",
        L"Á hálftíma fresti",
        L"Á klukkustundar fresti"
    },
    {
        L"Yok",
        L"Her dakika",
        L"Her 5 dakikada",
        L"Her 10 dakikada",
        L"Her çeyrek saatte",
        L"Her 20 dakikada",
        L"Her yarım saatte",
        L"Her saat"
    }
};

const wchar_t* TIME_SIGNAL_NOTE[LANG_COUNT] = {
    L"Pět krátkých tónů zazní v posledních pěti sekundách a dlouhý tón přesně na zvolené časové hranici. Souběžná znamení více widgetů se přehrají pouze jednou.",
    L"Five short pips sound during the final five seconds and a long pip exactly at the selected time boundary. Coincident signals from multiple widgets play only once.",
    L"Fünf kurze Töne erklingen in den letzten fünf Sekunden und ein langer Ton genau an der gewählten Zeitgrenze. Gleichzeitige Signale mehrerer Widgets werden nur einmal wiedergegeben.",
    L"Cinq bips courts retentissent pendant les cinq dernières secondes et un bip long exactement à la limite choisie. Les signaux simultanés de plusieurs widgets ne sont joués qu’une fois.",
    L"Cinco pitidos cortos suenan durante los últimos cinco segundos y uno largo exactamente en el límite elegido. Las señales simultáneas de varios widgets se reproducen una sola vez.",
    L"Cinque segnali brevi suonano negli ultimi cinque secondi e uno lungo esattamente al limite scelto. I segnali simultanei di più widget vengono riprodotti una sola volta.",
    L"Pięć krótkich sygnałów rozlega się w ostatnich pięciu sekundach, a długi dokładnie na wybranej granicy czasu. Zbieżne sygnały wielu widżetów są odtwarzane tylko raz.",
    L"Päť krátkych tónov zaznie v posledných piatich sekundách a dlhý tón presne na zvolenej časovej hranici. Súbežné znamenia viacerých widgetov sa prehrajú iba raz.",
    L"Five short pips sound during the final five seconds and a long pip exactly at the selected time boundary. Coincident signals from multiple widgets play only once.",
    L"Five short pips sound during the final five seconds and a long pip exactly at the selected time boundary. Coincident signals from multiple widgets play only once.",
    L"Cinco sinais curtos soam nos últimos cinco segundos e um sinal longo exatamente no limite escolhido. Sinais coincidentes de vários widgets são reproduzidos apenas uma vez.",
    L"Fem korte pip høres i de siste fem sekundene og et langt pip nøyaktig på den valgte tidsgrensen. Samtidige signaler fra flere widgeter spilles bare én gang.",
    L"Fem korta pip hörs under de sista fem sekunderna och ett långt pip exakt vid den valda tidsgränsen. Samtidiga signaler från flera widgetar spelas bara en gång.",
    L"Viisi lyhyttä äänimerkkiä kuuluu viimeisten viiden sekunnin aikana ja pitkä merkki täsmälleen valitulla aikarajalla. Samanaikaiset merkit toistetaan vain kerran.",
    L"Fem korte bip lyder i de sidste fem sekunder og et langt bip præcis ved den valgte tidsgrænse. Samtidige signaler fra flere widgets afspilles kun én gang.",
    L"Fimm stutt píp hljóma síðustu fimm sekúndurnar og langt píp nákvæmlega á völdum tímamörkum. Samtímamerki frá mörgum græjum eru aðeins spiluð einu sinni.",
    L"Son beş saniyede beş kısa ses ve seçili zaman sınırında tam olarak bir uzun ses çalar. Birden çok aracın çakışan sinyalleri yalnızca bir kez çalınır."
};

const wchar_t* TIME_TAB_LABELS[LANG_COUNT] = {
    L"Čas",
    L"Time",
    L"Zeit",
    L"Heure",
    L"Hora",
    L"Ora",
    L"Czas",
    L"Čas",
    L"Time",
    L"Time",
    L"Hora",
    L"Tid",
    L"Tid",
    L"Aika",
    L"Tid",
    L"Tími",
    L"Zaman"
};

const wchar_t* TIME_SOURCE_LABELS[LANG_COUNT] = {
    L"&Zdroj času:",
    L"Time &source:",
    L"Zeit&quelle:",
    L"&Source de l’heure :",
    L"&Origen de hora:",
    L"&Origine ora:",
    L"Źródło &czasu:",
    L"&Zdroj času:",
    L"Time &source:",
    L"Time &source:",
    L"&Origem da hora:",
    L"Tids&kilde:",
    L"Tids&källa:",
    L"Ajan &lähde:",
    L"Tids&kilde:",
    L"&Tímagjafi:",
    L"Zaman &kaynağı:"
};

const wchar_t* SYSTEM_TIME_LABELS[LANG_COUNT] = {
    L"Systémový čas Windows",
    L"Windows system time",
    L"Windows-Systemzeit",
    L"Heure système Windows",
    L"Hora del sistema Windows",
    L"Ora di sistema Windows",
    L"Czas systemowy Windows",
    L"Systémový čas Windows",
    L"Windows system time",
    L"Windows system time",
    L"Hora do sistema Windows",
    L"Systemtid i Windows",
    L"Systemtid i Windows",
    L"Windowsin järjestelmäaika",
    L"Windows-systemtid",
    L"Kerfistími Windows",
    L"Windows sistem zamanı"
};

const wchar_t* NTP_TIME_LABELS[LANG_COUNT] = {
    L"Čas ze serverů NTP",
    L"Time from NTP servers",
    L"Zeit von NTP-Servern",
    L"Heure des serveurs NTP",
    L"Hora de servidores NTP",
    L"Ora dai server NTP",
    L"Czas z serwerów NTP",
    L"Čas zo serverov NTP",
    L"Time from NTP servers",
    L"Time from NTP servers",
    L"Hora dos servidores NTP",
    L"Tid fra NTP-servere",
    L"Tid från NTP-servrar",
    L"Aika NTP-palvelimilta",
    L"Tid fra NTP-servere",
    L"Tími frá NTP-þjónum",
    L"NTP sunucularından zaman"
};

const wchar_t* NTP_SERVERS_LABELS[LANG_COUNT] = {
    L"&Servery NTP (oddělené středníkem):",
    L"&NTP servers (semicolon-separated):",
    L"&NTP-Server (durch Semikolon getrennt):",
    L"Serveurs &NTP (séparés par des points-virgules) :",
    L"Servidores &NTP (separados por punto y coma):",
    L"Server &NTP (separati da punto e virgola):",
    L"Serwery &NTP (oddzielone średnikami):",
    L"Servery &NTP (oddelené bodkočiarkou):",
    L"&NTP servers (semicolon-separated):",
    L"&NTP servers (semicolon-separated):",
    L"Servidores &NTP (separados por ponto e vírgula):",
    L"&NTP-servere (atskilt med semikolon):",
    L"&NTP-servrar (avgränsade med semikolon):",
    L"&NTP-palvelimet (puolipistein eroteltuina):",
    L"&NTP-servere (adskilt med semikolon):",
    L"&NTP-þjónar (aðskildir með semíkommu):",
    L"&NTP sunucuları (noktalı virgülle ayrılmış):"
};

const wchar_t* NTP_PRESET_FIELD_LABELS[LANG_COUNT] = {
    L"Výchozí &sada:",
    L"Default &set:",
    L"Standard&gruppe:",
    L"&Jeu par défaut :",
    L"Conjunto &predeterminado:",
    L"Gruppo &predefinito:",
    L"&Zestaw domyślny:",
    L"Predvolená &sada:",
    L"Default &set:",
    L"Default &set:",
    L"Conjunto &predefinido:",
    L"Standard&sett:",
    L"Standard&uppsättning:",
    L"Oletus&joukko:",
    L"Standard&sæt:",
    L"Sjálfgefið &safn:",
    L"Varsayılan &küme:"
};

const wchar_t* NTP_PRESET_LABELS[LANG_COUNT][NTP_PRESET_COUNT] = {
    {
        L"Automaticky podle oblasti",
        L"Česko a Slovensko – CESNET/NIC.CZ",
        L"PTB – Německo a Evropa",
        L"Celý svět – Ubuntu / NTP Pool",
        L"Vlastní"
    },
    {
        L"Automatic by region",
        L"Czechia and Slovakia – CESNET/NIC.CZ",
        L"PTB – Germany and Europe",
        L"Worldwide – Ubuntu / NTP Pool",
        L"Custom"
    },
    {
        L"Automatisch nach Region",
        L"Tschechien und Slowakei – CESNET/NIC.CZ",
        L"PTB – Deutschland und Europa",
        L"Weltweit – Ubuntu / NTP Pool",
        L"Benutzerdefiniert"
    },
    {
        L"Automatique selon la région",
        L"Tchéquie et Slovaquie – CESNET/NIC.CZ",
        L"PTB – Allemagne et Europe",
        L"Monde entier – Ubuntu / NTP Pool",
        L"Personnalisé"
    },
    {
        L"Automático según la región",
        L"Chequia y Eslovaquia – CESNET/NIC.CZ",
        L"PTB – Alemania y Europa",
        L"Todo el mundo – Ubuntu / NTP Pool",
        L"Personalizado"
    },
    {
        L"Automatico in base all’area",
        L"Cechia e Slovacchia – CESNET/NIC.CZ",
        L"PTB – Germania ed Europa",
        L"Tutto il mondo – Ubuntu / NTP Pool",
        L"Personalizzato"
    },
    {
        L"Automatycznie według regionu",
        L"Czechy i Słowacja – CESNET/NIC.CZ",
        L"PTB – Niemcy i Europa",
        L"Cały świat – Ubuntu / NTP Pool",
        L"Własny"
    },
    {
        L"Automaticky podľa oblasti",
        L"Česko a Slovensko – CESNET/NIC.CZ",
        L"PTB – Nemecko a Európa",
        L"Celý svet – Ubuntu / NTP Pool",
        L"Vlastné"
    },
    {
        L"Automatic by region",
        L"Czechia and Slovakia – CESNET/NIC.CZ",
        L"PTB – Germany and Europe",
        L"Worldwide – Ubuntu / NTP Pool",
        L"Custom"
    },
    {
        L"Automatic by region",
        L"Czechia and Slovakia – CESNET/NIC.CZ",
        L"PTB – Germany and Europe",
        L"Worldwide – Ubuntu / NTP Pool",
        L"Custom"
    },
    {
        L"Automático por região",
        L"Chéquia e Eslováquia – CESNET/NIC.CZ",
        L"PTB – Alemanha e Europa",
        L"Mundial – Ubuntu / NTP Pool",
        L"Personalizado"
    },
    {
        L"Automatisk etter region",
        L"Tsjekkia og Slovakia – CESNET/NIC.CZ",
        L"PTB – Tyskland og Europa",
        L"Hele verden – Ubuntu / NTP Pool",
        L"Egendefinert"
    },
    {
        L"Automatiskt efter region",
        L"Tjeckien och Slovakien – CESNET/NIC.CZ",
        L"PTB – Tyskland och Europa",
        L"Hela världen – Ubuntu / NTP Pool",
        L"Anpassad"
    },
    {
        L"Automaattinen alueen mukaan",
        L"Tšekki ja Slovakia – CESNET/NIC.CZ",
        L"PTB – Saksa ja Eurooppa",
        L"Maailmanlaajuinen – Ubuntu / NTP Pool",
        L"Mukautettu"
    },
    {
        L"Automatisk efter område",
        L"Tjekkiet og Slovakiet – CESNET/NIC.CZ",
        L"PTB – Tyskland og Europa",
        L"Hele verden – Ubuntu / NTP Pool",
        L"Brugerdefineret"
    },
    {
        L"Sjálfvirkt eftir svæði",
        L"Tékkland og Slóvakía – CESNET/NIC.CZ",
        L"PTB – Þýskaland og Evrópa",
        L"Allur heimurinn – Ubuntu / NTP Pool",
        L"Sérsniðið"
    },
    {
        L"Bölgeye göre otomatik",
        L"Çekya ve Slovakya – CESNET/NIC.CZ",
        L"PTB – Almanya ve Avrupa",
        L"Dünya çapında – Ubuntu / NTP Pool",
        L"Özel"
    }
};

const wchar_t* NTP_SYNC_LABELS[LANG_COUNT] = {
    L"&Synchronizovat nyní",
    L"&Synchronize now",
    L"Jetzt &synchronisieren",
    L"&Synchroniser maintenant",
    L"&Sincronizar ahora",
    L"&Sincronizza ora",
    L"&Synchronizuj teraz",
    L"&Synchronizovať teraz",
    L"&Synchronize now",
    L"&Synchronize now",
    L"&Sincronizar agora",
    L"&Synkroniser nå",
    L"&Synkronisera nu",
    L"&Synkronoi nyt",
    L"&Synkroniser nu",
    L"&Samstilla núna",
    L"Şimdi &eşitle"
};

const wchar_t* TIME_GLOBAL_NOTE[LANG_COUNT] = {
    L"Zdroj a synchronizace času platí globálně pro všechny widgety.",
    L"The time source and synchronization apply globally to all widgets.",
    L"Zeitquelle und Synchronisierung gelten global für alle Widgets.",
    L"La source et la synchronisation de l’heure s’appliquent globalement à tous les widgets.",
    L"La fuente y la sincronización de hora se aplican globalmente a todos los widgets.",
    L"L’origine e la sincronizzazione dell’ora si applicano globalmente a tutti i widget.",
    L"Źródło i synchronizacja czasu obowiązują globalnie dla wszystkich widżetów.",
    L"Zdroj a synchronizácia času platia globálne pre všetky widgety.",
    L"The time source and synchronization apply globally to all widgets.",
    L"The time source and synchronization apply globally to all widgets.",
    L"A origem e a sincronização da hora aplicam-se globalmente a todos os widgets.",
    L"Tidskilde og synkronisering gjelder globalt for alle widgeter.",
    L"Tidskälla och synkronisering gäller globalt för alla widgetar.",
    L"Aikalähde ja synkronointi koskevat kaikkia pienoisohjelmia.",
    L"Tidskilde og synkronisering gælder globalt for alle widgets.",
    L"Tímagjafi og samstilling gilda fyrir allar græjur.",
    L"Zaman kaynağı ve eşitleme tüm araçlara genel olarak uygulanır."
};

const wchar_t* NTP_STATUS_SYSTEM[LANG_COUNT] = {
    L"Používá se systémový čas; Windows se nemění.",
    L"System time is used; Windows is not changed.",
    L"Die Systemzeit wird verwendet; Windows wird nicht geändert.",
    L"L’heure système est utilisée ; Windows n’est pas modifié.",
    L"Se usa la hora del sistema; Windows no se modifica.",
    L"Viene usata l’ora di sistema; Windows non viene modificato.",
    L"Używany jest czas systemowy; system Windows nie jest zmieniany.",
    L"Používa sa systémový čas; Windows sa nemení.",
    L"System time is used; Windows is not changed.",
    L"System time is used; Windows is not changed.",
    L"É utilizada a hora do sistema; o Windows não é alterado.",
    L"Systemtid brukes; Windows endres ikke.",
    L"Systemtid används; Windows ändras inte.",
    L"Järjestelmäaikaa käytetään; Windowsia ei muuteta.",
    L"Systemtid bruges; Windows ændres ikke.",
    L"Kerfistími er notaður; Windows er ekki breytt.",
    L"Sistem zamanı kullanılıyor; Windows değiştirilmez."
};

const wchar_t* NTP_STATUS_WAITING[LANG_COUNT] = {
    L"Čeká se na synchronizaci NTP…",
    L"Waiting for NTP synchronization…",
    L"NTP-Synchronisierung wird erwartet…",
    L"Synchronisation NTP en attente…",
    L"Esperando la sincronización NTP…",
    L"In attesa della sincronizzazione NTP…",
    L"Oczekiwanie na synchronizację NTP…",
    L"Čaká sa na synchronizáciu NTP…",
    L"Waiting for NTP synchronization…",
    L"Waiting for NTP synchronization…",
    L"A aguardar a sincronização NTP…",
    L"Venter på NTP-synkronisering…",
    L"Väntar på NTP-synkronisering…",
    L"Odotetaan NTP-synkronointia…",
    L"Venter på NTP-synkronisering…",
    L"Bíður eftir NTP-samstillingu…",
    L"NTP eşitlemesi bekleniyor…"
};

const wchar_t* NTP_STATUS_FAILED[LANG_COUNT] = {
    L"Servery NTP nejsou dostupné; dočasně se používá systémový čas.",
    L"NTP servers are unavailable; system time is used temporarily.",
    L"NTP-Server sind nicht erreichbar; vorübergehend wird die Systemzeit verwendet.",
    L"Les serveurs NTP sont indisponibles ; l’heure système est utilisée temporairement.",
    L"Los servidores NTP no están disponibles; se usa temporalmente la hora del sistema.",
    L"I server NTP non sono disponibili; viene usata temporaneamente l’ora di sistema.",
    L"Serwery NTP są niedostępne; tymczasowo używany jest czas systemowy.",
    L"Servery NTP nie sú dostupné; dočasne sa používa systémový čas.",
    L"NTP servers are unavailable; system time is used temporarily.",
    L"NTP servers are unavailable; system time is used temporarily.",
    L"Os servidores NTP estão indisponíveis; a hora do sistema é utilizada temporariamente.",
    L"NTP-serverne er utilgjengelige; systemtid brukes midlertidig.",
    L"NTP-servrarna är inte tillgängliga; systemtid används tillfälligt.",
    L"NTP-palvelimia ei tavoiteta; järjestelmäaikaa käytetään tilapäisesti.",
    L"NTP-serverne er ikke tilgængelige; systemtid bruges midlertidigt.",
    L"NTP-þjónar eru ekki tiltækir; kerfistími er notaður tímabundið.",
    L"NTP sunucuları kullanılamıyor; geçici olarak sistem zamanı kullanılıyor."
};

const wchar_t* NTP_STATUS_RETAINED[LANG_COUNT] = {
    L"Servery NTP nejsou dostupné; používá se poslední korekce v paměti:",
    L"NTP servers are unavailable; the last in-memory correction is used:",
    L"NTP-Server sind nicht erreichbar; die letzte Korrektur im Speicher wird verwendet:",
    L"Les serveurs NTP sont indisponibles ; la dernière correction en mémoire est utilisée :",
    L"Los servidores NTP no están disponibles; se usa la última corrección guardada en memoria:",
    L"I server NTP non sono disponibili; viene usata l’ultima correzione in memoria:",
    L"Serwery NTP są niedostępne; używana jest ostatnia korekta przechowywana w pamięci:",
    L"Servery NTP nie sú dostupné; používa sa posledná korekcia v pamäti:",
    L"NTP servers are unavailable; the last in-memory correction is used:",
    L"NTP servers are unavailable; the last in-memory correction is used:",
    L"Os servidores NTP estão indisponíveis; é utilizada a última correção em memória:",
    L"NTP-serverne er utilgjengelige; siste korreksjon i minnet brukes:",
    L"NTP-servrarna är inte tillgängliga; den senaste korrigeringen i minnet används:",
    L"NTP-palvelimia ei tavoiteta; viimeisintä muistissa olevaa korjausta käytetään:",
    L"NTP-serverne er ikke tilgængelige; den seneste korrektion i hukommelsen bruges:",
    L"NTP-þjónar eru ekki tiltækir; síðasta leiðrétting í minni er notuð:",
    L"NTP sunucuları kullanılamıyor; bellekteki son düzeltme kullanılıyor:"
};

const wchar_t* NTP_STATUS_SYNCHRONIZED[LANG_COUNT] = {
    L"Synchronizováno se serverem",
    L"Synchronized with",
    L"Synchronisiert mit",
    L"Synchronisé avec",
    L"Sincronizado con",
    L"Sincronizzato con",
    L"Zsynchronizowano z",
    L"Synchronizované so serverom",
    L"Synchronized with",
    L"Synchronized with",
    L"Sincronizado com",
    L"Synkronisert med",
    L"Synkroniserad med",
    L"Synkronoitu palvelimeen",
    L"Synkroniseret med",
    L"Samstillt við",
    L"Şununla eşitlendi"
};

const wchar_t* ANTIALIASING_LABELS[LANG_COUNT] = {
    L"&Vyhlazování písma:",
    L"Font &antialiasing:",
    L"Schrift&glättung:",
    L"&Lissage des polices :",
    L"&Suavizado de fuente:",
    L"&Antialiasing carattere:",
    L"&Wygładzanie czcionki:",
    L"&Vyhladzovanie písma:",
    L"Font &antialiasing:",
    L"Font &antialiasing:",
    L"&Suavização do tipo de letra:",
    L"Skrift&utjevning:",
    L"Teckensnitts&utjämning:",
    L"Fontin &pehmennys:",
    L"Skrift&udjævning:",
    L"&Leturjöfnun:",
    L"Yazı tipi &kenar yumuşatma:"
};

const wchar_t* ANTIALIASING_NAMES[FONT_ANTIALIAS_COUNT] = {
    L"GDI",
    L"ClearType"
};

const wchar_t* DEFAULT_APPEARANCE_LABELS[LANG_COUNT] = {
    L"&Výchozí vzhled",
    L"&Default appearance",
    L"&Standarddarstellung",
    L"Apparence par &défaut",
    L"Aspecto &predeterminado",
    L"Aspetto &predefinito",
    L"Wygląd &domyślny",
    L"&Predvolený vzhľad",
    L"&Default appearance",
    L"&Default appearance",
    L"Aspeto &predefinido",
    L"&Standardutseende",
    L"&Standardutseende",
    L"&Oletusulkoasu",
    L"&Standardudseende",
    L"&Sjálfgefið útlit",
    L"&Varsayılan görünüm"
};

const wchar_t* TEST_COMMAND_LABELS[LANG_COUNT] = {
    L"V&yzkoušet",
    L"&Test",
    L"&Testen",
    L"&Tester",
    L"&Probar",
    L"&Prova",
    L"&Testuj",
    L"V&yskúšať",
    L"&Test",
    L"&Test",
    L"&Testar",
    L"&Test",
    L"&Testa",
    L"&Testaa",
    L"&Test",
    L"&Prófa",
    L"&Test et"
};

const wchar_t* STOP_TEST_LABELS[LANG_COUNT] = {
    L"&Zastavit test",
    L"S&top test",
    L"Test &stoppen",
    L"&Arrêter le test",
    L"&Detener prueba",
    L"&Ferma prova",
    L"&Zatrzymaj test",
    L"&Zastaviť test",
    L"S&top test",
    L"S&top test",
    L"&Parar teste",
    L"&Stopp test",
    L"&Stoppa test",
    L"&Pysäytä testi",
    L"&Stop test",
    L"&Stöðva prófun",
    L"Testi &durdur"
};

const wchar_t* ALARM_TIME_SIGNAL_LABELS[LANG_COUNT] = {
    L"Pípat časové &znamení",
    L"Sound the time si&gnal",
    L"Akustisches &Zeitzeichen",
    L"Émettre le signal &horaire",
    L"Emitir la señal h&oraria",
    L"Emetti il segnale &orario",
    L"Odtwarzaj sygnał &czasu",
    L"Pípať časové &znamenie",
    L"Sound the time si&gnal",
    L"Sound the time si&gnal",
    L"Emitir o &sinal horário",
    L"Spill tids&signalet",
    L"Spela tids&signalen",
    L"Toista aika&merkki",
    L"Afspil tids&signalet",
    L"Spila tíma&merki",
    L"Zaman &sinyalini çal"
};

const wchar_t* REMOTE_SCRIPT_LABELS[LANG_COUNT] = {
    L"Zavolat &vzdálený skript",
    L"Call a &remote script",
    L"&Remote-Skript aufrufen",
    L"Appeler un script &distant",
    L"Llamar a un script &remoto",
    L"Chiama script &remoto",
    L"Wywołaj skrypt &zdalny",
    L"Zavolať &vzdialený skript",
    L"Call a &remote script",
    L"Call a &remote script",
    L"Chamar um script &remoto",
    L"Kall et &eksternt skript",
    L"Anropa ett &fjärrskript",
    L"Kutsu &etäkomentosarjaa",
    L"Kald et &fjernscript",
    L"Kalla á &fjarskriftu",
    L"&Uzak betiği çağır"
};

const wchar_t* REMOTE_SCRIPT_URL_LABELS[LANG_COUNT] = {
    L"Adresa URL:",
    L"URL:",
    L"URL:",
    L"URL :",
    L"URL:",
    L"URL:",
    L"Adres URL:",
    L"Adresa URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"Vefslóð:",
    L"URL:"
};

const wchar_t* INVALID_REMOTE_SCRIPT_URL[LANG_COUNT] = {
    L"Zadejte platnou adresu vzdáleného skriptu HTTP nebo HTTPS.",
    L"Enter a valid HTTP or HTTPS remote script URL.",
    L"Geben Sie eine gültige HTTP- oder HTTPS-Adresse des Remote-Skripts ein.",
    L"Entrez une adresse HTTP ou HTTPS valide pour le script distant.",
    L"Introduzca una dirección HTTP o HTTPS válida para el script remoto.",
    L"Immettere un indirizzo HTTP o HTTPS valido per lo script remoto.",
    L"Wprowadź prawidłowy adres HTTP lub HTTPS zdalnego skryptu.",
    L"Zadajte platnú adresu HTTP alebo HTTPS vzdialeného skriptu.",
    L"Enter a valid HTTP or HTTPS remote script URL.",
    L"Enter a valid HTTP or HTTPS remote script URL.",
    L"Introduza um URL HTTP ou HTTPS válido para o script remoto.",
    L"Angi en gyldig HTTP- eller HTTPS-adresse til det eksterne skriptet.",
    L"Ange en giltig HTTP- eller HTTPS-adress till fjärrskriptet.",
    L"Anna kelvollinen etäkomentosarjan HTTP- tai HTTPS-osoite.",
    L"Angiv en gyldig HTTP- eller HTTPS-adresse til fjernscriptet.",
    L"Sláðu inn gilda HTTP- eða HTTPS-vefslóð fjarskriftu.",
    L"Geçerli bir HTTP veya HTTPS uzak betik URL'si girin."
};

const wchar_t* IMPORT_SETTINGS_LABELS[LANG_COUNT] = {
    L"Importovat &XML...",
    L"Import &XML...",
    L"&XML importieren...",
    L"Importer &XML...",
    L"Importar &XML...",
    L"Importa &XML...",
    L"Importuj &XML...",
    L"Importovať &XML...",
    L"Import &XML...",
    L"Import &XML...",
    L"Importar &XML...",
    L"Importer &XML...",
    L"Importera &XML...",
    L"Tuo &XML...",
    L"Importer &XML...",
    L"Flytja inn &XML...",
    L"&XML içe aktar..."
};

const wchar_t* EXPORT_SETTINGS_LABELS[LANG_COUNT] = {
    L"Exportovat X&ML...",
    L"Export X&ML...",
    L"XML &exportieren...",
    L"Exporter X&ML...",
    L"Exportar X&ML...",
    L"Esporta X&ML...",
    L"Eksportuj X&ML...",
    L"Exportovať X&ML...",
    L"Export X&ML...",
    L"Export X&ML...",
    L"Exportar X&ML...",
    L"Eksporter X&ML...",
    L"Exportera X&ML...",
    L"Vie X&ML...",
    L"Eksporter X&ML...",
    L"Flytja út X&ML...",
    L"X&ML dışa aktar..."
};

const wchar_t* INVALID_SETTINGS_FILE[LANG_COUNT] = {
    L"Soubor neobsahuje platné nastavení CalClock.",
    L"The file does not contain valid CalClock settings.",
    L"Die Datei enthält keine gültigen CalClock-Einstellungen.",
    L"Le fichier ne contient pas de paramètres CalClock valides.",
    L"El archivo no contiene una configuración válida de CalClock.",
    L"Il file non contiene impostazioni CalClock valide.",
    L"Plik nie zawiera prawidłowych ustawień CalClock.",
    L"Súbor neobsahuje platné nastavenia CalClock.",
    L"The file does not contain valid CalClock settings.",
    L"The file does not contain valid CalClock settings.",
    L"O ficheiro não contém definições válidas do CalClock.",
    L"Filen inneholder ikke gyldige CalClock-innstillinger.",
    L"Filen innehåller inte giltiga CalClock-inställningar.",
    L"Tiedosto ei sisällä kelvollisia CalClock-asetuksia.",
    L"Filen indeholder ikke gyldige CalClock-indstillinger.",
    L"Skráin inniheldur ekki gildar CalClock-stillingar.",
    L"Dosya geçerli CalClock ayarları içermiyor."
};

const wchar_t* SETTINGS_EXPORT_FAILED[LANG_COUNT] = {
    L"Nastavení se nepodařilo exportovat.",
    L"Settings could not be exported.",
    L"Die Einstellungen konnten nicht exportiert werden.",
    L"Impossible d’exporter les paramètres.",
    L"No se pudo exportar la configuración.",
    L"Impossibile esportare le impostazioni.",
    L"Nie udało się wyeksportować ustawień.",
    L"Nastavenia sa nepodarilo exportovať.",
    L"Settings could not be exported.",
    L"Settings could not be exported.",
    L"Não foi possível exportar as definições.",
    L"Innstillingene kunne ikke eksporteres.",
    L"Inställningarna kunde inte exporteras.",
    L"Asetuksia ei voitu viedä.",
    L"Indstillingerne kunne ikke eksporteres.",
    L"Ekki tókst að flytja stillingarnar út.",
    L"Ayarlar dışa aktarılamadı."
};

const wchar_t* XML_STORAGE_LABELS[LANG_COUNT] = {
    L"Ukládat do &XML",
    L"Save to &XML",
    L"In &XML speichern",
    L"Enregistrer en &XML",
    L"Guardar en &XML",
    L"Salva in &XML",
    L"Zapisuj do &XML",
    L"Ukladať do &XML",
    L"Save to &XML",
    L"Save to &XML",
    L"Guardar em &XML",
    L"Lagre i &XML",
    L"Spara i &XML",
    L"Tallenna &XML-muodossa",
    L"Gem i &XML",
    L"Vista í &XML",
    L"&XML'e kaydet"
};

const wchar_t* START_WITH_WINDOWS_LABELS[LANG_COUNT] = {
    L"Spouštět s &Windows",
    L"Start with &Windows",
    L"Mit &Windows starten",
    L"Démarrer avec &Windows",
    L"Iniciar con &Windows",
    L"Avvia con &Windows",
    L"Uruchamiaj z &systemem Windows",
    L"Spúšťať s &Windows",
    L"Start with &Windows",
    L"Start with &Windows",
    L"Iniciar com o &Windows",
    L"Start med &Windows",
    L"Starta med &Windows",
    L"Käynnistä &Windowsin mukana",
    L"Start med &Windows",
    L"Ræsa með &Windows",
    L"&Windows ile başlat"
};

const wchar_t* MUTE_LABELS[LANG_COUNT] = {
    L"&Ztlumit",
    L"&Mute",
    L"&Stummschalten",
    L"Couper le &son",
    L"&Silenciar",
    L"Disattiva &audio",
    L"&Wycisz",
    L"&Stlmiť",
    L"&Mute",
    L"&Mute",
    L"&Silenciar",
    L"&Demp",
    L"&Tysta",
    L"&Mykistä",
    L"&Slå lyd fra",
    L"&Þagga",
    L"&Sessize al"
};

const wchar_t* MUTE_ALL_LABELS[LANG_COUNT] = {
    L"&Ztlumit vše",
    L"&Mute all",
    L"&Alles stummschalten",
    L"Couper &tous les sons",
    L"&Silenciar todo",
    L"Disattiva &tutto l'audio",
    L"&Wycisz wszystko",
    L"&Stlmiť všetko",
    L"&Mute all",
    L"&Mute all",
    L"Silenciar &tudo",
    L"Demp &alle",
    L"Tysta &alla",
    L"Mykistä &kaikki",
    L"Slå al lyd &fra",
    L"Þagga &allt",
    L"&Tümünü sessize al"
};

const wchar_t* MUTED_LABELS[LANG_COUNT] = {
    L"Zt&lumeno",
    L"&Muted",
    L"Stummgesch&altet",
    L"Son &coupé",
    L"Si&lenciado",
    L"Audio &disattivato",
    L"&Wyciszony",
    L"St&lmené",
    L"&Muted",
    L"&Muted",
    L"Si&lenciado",
    L"De&mpet",
    L"&Tyst",
    L"&Mykistetty",
    L"Lyd &fra",
    L"&Þaggað",
    L"Sessi&z"
};

const wchar_t* HELP_TEXT[LANG_COUNT] = {
    L"OVLÁDÁNÍ\r\nLevým tlačítkem a tažením přesunete hodiny nebo panel. Samostatný kalendář se přesouvá za volnou plochu; kliknutím na den měníte vybrané datum a šipkami, "
    L"záhlavím nebo odkazem Dnes kalendář procházíte. Pravým tlačítkem na widgetu nebo na ikoně v oznamovací oblasti otevřete nabídku. Levé kliknutí na ikonu skryje právě "
    L"viditelné widgety; jsou-li všechny skryté, obnoví pouze naposledy skryté widgety.\r\n\r\nWIDGETY A NASTAVENÍ\r\nV Nastavení lze přidat, odebrat a duplikovat libovolný "
    L"počet ručičkových hodin, digitálních hodin, kalendářů a panelů s kalendářem a hodinami i hodin na monitoru. Každý widget má vlastní viditelnost, režim vždy navrchu, jazyk, "
    L"časové pásmo a offset. Offset zadávejte jako [-]HH:mm:ss.ff. Ručičkové hodiny a hodiny v panelu mají čtyři velikosti. U digitálních hodin lze nastavit sekundy, úvodní "
    L"nulu, písmo, barvy, neprůhlednost a průhledné pozadí. Kalendář podporuje čísla týdnů, neděli jako první den a používá zvolený jazyk widgetu.\r\n\r\nBUDÍK\r\nBudík "
    L"lze nastavit pro hodiny a panel. Zvukový soubor aplikace přehrává sama jednou nebo stále dokola podle volby. Ostatní soubor nebo příkaz předá systému Windows. Kliknutím "
    L"na budící ciferník či displej, příkazem Zastavit budík nebo klávesou Esc zastavíte blikání i zvuk přehrávaný aplikací.\r\n\r\nZKRATKY A UKLÁDÁNÍ\r\nDvojklik na hodiny "
    L"přepne sekundy, F1 otevře nápovědu, B otevře Nastavení a Esc skryje widget, pokud právě nezastavuje budík. Polohy widgetů se ukládají po přesunutí, polohy formulářů "
    L"při zavření a nastavení do zvoleného úložiště. Další spuštění programu aktivuje již běžící instanci a zachová widgety u nejbližšího dostupného okraje pracovní plochy.",
    L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a standalone calendar by its free area; click a day to change the selection and use the arrows, header "
    L"or Today link to navigate. Right-click a widget or notification icon for its menu. Left-click the notification icon to hide the currently visible widgets; when all "
    L"are hidden, it restores only the widgets hidden most recently.\r\n\r\nWIDGETS AND SETTINGS\r\nSettings can add, remove and duplicate any number of analog clocks, digital "
    L"clocks, calendars, calendar-and-clock panels and monitor clocks. Each widget has its own visibility, always-on-top state, language, time zone and offset. Enter "
    L"offsets as [-]HH:mm:ss.ff. Analog clocks and panel clocks have four sizes. Digital clocks support seconds, a leading zero, font, colours, opacity and a transparent background. "
    L"Calendars support week numbers and Sunday as the first day and use the widget language.\r\n\r\nALARM\r\nClocks and panels can have an alarm. The application plays "
    L"an audio file itself, once or continuously according to the loop option. Other files or commands are passed to Windows. Click the alarming clock face or display, choose "
    L"Stop alarm, or press Esc to stop both the alarm indication and audio played by the application.\r\n\r\nSHORTCUTS AND SAVING\r\nDouble-click a clock to toggle seconds, "
    L"press F1 for Help, B for Settings, and Esc to hide a widget when no alarm is being stopped. Widget positions are saved after dragging, dialog positions when closed, "
    L"and all settings in the selected storage. Starting the program again activates the running instance and keeps widgets at the nearest available point in the work area.",
    L"BEDIENUNG\r\nZiehen Sie eine Uhr oder ein Panel mit der linken Maustaste. Einen einzelnen Kalender ziehen Sie an seiner freien Fläche; ein Klick auf einen Tag ändert die Auswahl. "
    L"Rechtsklick auf Widget oder Infobereichsymbol öffnet das Menü. Linksklick auf das Symbol verbirgt die gerade sichtbaren Widgets; sind alle verborgen, werden nur die zuletzt "
    L"verborgenen Widgets wiederhergestellt.\r\n\r\nWIDGETS UND EINSTELLUNGEN\r\nSie können beliebig viele Analoguhren, Digitaluhren, Kalender, Kalender-Uhr-Panels und Monitoruhren "
    L"hinzufügen, entfernen oder duplizieren. Jedes Widget besitzt eigene Sichtbarkeit, Vordergrundlage, Sprache, Zeitzone und einen Versatz im Format [-]HH:mm:ss.ff. Analoguhren haben "
    L"vier Größen. Digitaluhren bieten Sekunden, führende Null, Schrift, Farben, Deckkraft und transparenten Hintergrund. Kalender bieten Wochennummern, Sonntag als ersten Tag und "
    L"verwenden die Widget-Sprache.\r\n\r\nWECKER\r\nEine Audiodatei wird intern einmal oder in Schleife abgespielt; andere Dateien oder Befehle werden an Windows übergeben. Ein Klick auf "
    L"das alarmierende Zifferblatt bzw. Display, Wecker stoppen oder Esc beendet Anzeige und intern abgespielten Ton.\r\n\r\nTASTEN UND SPEICHERN\r\nDoppelklick schaltet Sekunden um, "
    L"F1 öffnet Hilfe, B die Einstellungen. Positionen und sämtliche Einstellungen werden im gewählten Speicher gespeichert. Ein erneuter Programmstart aktiviert die laufende Instanz.",
    L"COMMANDES\r\nFaites glisser une horloge ou un panneau avec le bouton gauche. Déplacez un calendrier autonome par sa zone libre ; cliquez sur un jour pour changer la sélection. Un clic "
    L"droit sur un widget ou l’icône de notification ouvre le menu. Un clic gauche sur l’icône masque les widgets visibles ; s’ils sont tous masqués, il rétablit uniquement les widgets masqués "
    L"le plus récemment.\r\n\r\nWIDGETS ET PARAMÈTRES\r\nVous pouvez ajouter, supprimer et dupliquer autant d’horloges analogiques, numériques, calendriers, panneaux combinés et horloges "
    L"sur moniteur que nécessaire. Chaque widget possède sa visibilité, son maintien au premier plan, sa langue, son fuseau et son décalage au format [-]HH:mm:ss.ff. Les horloges analogiques "
    L"ont quatre tailles. Les horloges numériques proposent secondes, zéro initial, police, couleurs, opacité et fond transparent. Le calendrier propose numéros de semaine, dimanche en premier "
    L"et la langue du widget.\r\n\r\nALARME\r\nL’application lit elle-même un fichier audio une fois ou en boucle ; les autres fichiers ou commandes sont confiés à Windows. Cliquez sur le "
    L"cadran ou l’affichage en alarme, choisissez Arrêter l’alarme ou appuyez sur Échap pour arrêter l’indication et le son interne.\r\n\r\nRACCOURCIS ET ENREGISTREMENT\r\nUn double-clic bascule "
    L"les secondes, F1 ouvre l’aide et B les paramètres. Les positions et tous les réglages sont enregistrés dans le stockage sélectionné. Un nouveau lancement active l’instance existante.",
    L"CONTROLES\r\nArrastre un reloj o panel con el botón izquierdo. El calendario independiente se arrastra por su zona libre; haga clic en un día para cambiar la selección. El "
    L"botón derecho sobre un widget o el icono de notificación abre el menú. Un clic izquierdo sobre el icono oculta los widgets visibles; si todos están ocultos, restaura solo "
    L"los ocultados más recientemente.\r\n\r\nWIDGETS Y CONFIGURACIÓN\r\nPuede añadir, quitar y duplicar cualquier número de relojes analógicos, digitales, calendarios, paneles "
    L"combinados y relojes de monitor. Cada widget tiene visibilidad, primer plano, idioma, zona horaria y desfase propios; use [-]HH:mm:ss.ff. Los relojes analógicos tienen cuatro "
    L"tamaños. Los digitales permiten segundos, cero inicial, fuente, colores, opacidad y fondo transparente. El calendario permite números de semana, domingo primero y usa el "
    L"idioma del widget.\r\n\r\nALARMA\r\nLa aplicación reproduce internamente un archivo de audio una vez o en bucle; los demás archivos o comandos se entregan a Windows. Haga clic "
    L"en la esfera o pantalla con alarma, elija Detener alarma o pulse Esc para detener la indicación y el audio interno.\r\n\r\nATAJOS Y GUARDADO\r\nEl doble clic cambia los "
    L"segundos, F1 abre la ayuda y B la configuración. Las posiciones y todos los ajustes se guardan en el almacenamiento seleccionado. Otra ejecución activa la instancia existente.",
    L"COMANDI\r\nTrascinare un orologio o pannello con il pulsante sinistro. Il calendario autonomo si trascina dall’area libera; fare clic su un giorno per cambiare la selezione. "
    L"Il pulsante destro su widget o icona di notifica apre il menu. Il clic sinistro sull’icona nasconde i widget visibili; se sono tutti nascosti, ripristina soltanto quelli "
    L"nascosti più di recente.\r\n\r\nWIDGET E IMPOSTAZIONI\r\nÈ possibile aggiungere, rimuovere e duplicare un numero qualsiasi di orologi analogici, digitali, calendari, "
    L"pannelli combinati e orologi su monitor. Ogni widget ha visibilità, primo piano, lingua, fuso orario e offset propri; usare [-]HH:mm:ss.ff. Gli orologi analogici hanno quattro "
    L"dimensioni. Quelli digitali offrono secondi, zero iniziale, carattere, colori, opacità e sfondo trasparente. Il calendario offre numeri di settimana, domenica per prima e "
    L"usa la lingua del widget.\r\n\r\nSVEGLIA\r\nL’applicazione riproduce internamente un file audio una volta o in ciclo; gli altri file o comandi vengono affidati a Windows. "
    L"Fare clic sul quadrante o display in allarme, scegliere Ferma sveglia o premere Esc per fermare indicazione e audio interno.\r\n\r\nSCORCIATOIE E SALVATAGGIO\r\nIl doppio "
    L"clic commuta i secondi, F1 apre la guida e B le impostazioni. Posizioni e impostazioni vengono salvate nell’archivio selezionato. Un nuovo avvio attiva l’istanza esistente.",
    L"STEROWANIE\r\nPrzeciągnij zegar lub panel lewym przyciskiem. Samodzielny kalendarz przeciąga się za wolne miejsce; kliknięcie dnia zmienia wybór. Prawy przycisk na widżecie lub ikonie "
    L"obszaru powiadomień otwiera menu. Lewy przycisk na ikonie ukrywa widoczne widżety; gdy wszystkie są ukryte, przywraca tylko ostatnio ukryte widżety.\r\n\r\nWIDŻETY I USTAWIENIA\r\nMożna "
    L"dodać, usunąć i powielić dowolną liczbę zegarów analogowych, cyfrowych, kalendarzy, paneli łączonych i zegarów na monitorze. Każdy widżet ma własną widoczność, tryb na "
    L"wierzchu, język, strefę czasową i przesunięcie w formacie [-]HH:mm:ss.ff. Zegary analogowe mają cztery rozmiary. Cyfrowe oferują sekundy, zero wiodące, czcionkę, kolory, krycie i "
    L"przezroczyste tło. Kalendarz oferuje numery tygodni, niedzielę jako pierwszy dzień i język widżetu.\r\n\r\nALARM\r\nAplikacja sama odtwarza plik audio raz lub w pętli; inne pliki i polecenia "
    L"przekazuje systemowi Windows. Kliknięcie alarmującej tarczy lub wyświetlacza, polecenie Zatrzymaj alarm albo Esc zatrzymuje wskazanie i dźwięk wewnętrzny.\r\n\r\nSKRÓTY I "
    L"ZAPIS\r\nDwuklik przełącza sekundy, F1 otwiera pomoc, a B ustawienia. Pozycje i wszystkie ustawienia są zapisywane w wybranym magazynie. Ponowne uruchomienie aktywuje istniejącą instancję.",
    L"OVLÁDANIE\r\nĽavým tlačidlom a ťahaním presuniete hodiny alebo panel. Samostatný kalendár sa presúva za voľnú plochu; kliknutím na deň zmeníte výber. Pravé tlačidlo na widgete "
    L"alebo ikone v oznamovacej oblasti otvorí ponuku. Ľavé kliknutie na ikonu skryje viditeľné widgety; ak sú všetky skryté, obnoví iba naposledy skryté widgety.\r\n\r\nWIDGETY A "
    L"NASTAVENIA\r\nMožno pridať, odobrať a duplikovať ľubovoľný počet ručičkových hodín, digitálnych hodín, kalendárov, kombinovaných panelov a hodín na monitore. Každý widget má vlastnú "
    L"viditeľnosť, režim vždy navrchu, jazyk, časové pásmo a offset vo formáte [-]HH:mm:ss.ff. Ručičkové hodiny majú štyri veľkosti. Digitálne hodiny ponúkajú sekundy, úvodnú nulu, "
    L"písmo, farby, priehľadnosť a priehľadné pozadie. Kalendár ponúka čísla týždňov, nedeľu ako prvý deň a používa jazyk widgetu.\r\n\r\nBUDÍK\r\nAplikácia prehrá zvukový súbor sama "
    L"raz alebo dookola; ostatné súbory a príkazy odovzdá systému Windows. Kliknutie na budík, príkaz Zastaviť budík alebo Esc zastaví signalizáciu aj interný zvuk.\r\n\r\nSKRATKY A "
    L"UKLADANIE\r\nDvojklik prepne sekundy, F1 otvorí pomoc a B nastavenia. Polohy a všetky nastavenia sa ukladajú do zvoleného úložiska. Ďalšie spustenie aktivuje existujúcu inštanciu.",
    L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a standalone calendar by its free area; click a day to change the selection and use the arrows, header "
    L"or Today link to navigate. Right-click a widget or notification icon for its menu. Left-click the notification icon to hide the currently visible widgets; when all "
    L"are hidden, it restores only the widgets hidden most recently.\r\n\r\nWIDGETS AND SETTINGS\r\nSettings can add, remove and duplicate any number of analog clocks, digital "
    L"clocks, calendars, calendar-and-clock panels and monitor clocks. Each widget has its own visibility, always-on-top state, language, time zone and offset. Enter "
    L"offsets as [-]HH:mm:ss.ff. Analog clocks and panel clocks have four sizes. Digital clocks support seconds, a leading zero, font, colours, opacity and a transparent background. "
    L"Calendars support week numbers and Sunday as the first day and use the widget language.\r\n\r\nALARM\r\nClocks and panels can have an alarm. The application plays "
    L"an audio file itself, once or continuously according to the loop option. Other files or commands are passed to Windows. Click the alarming clock face or display, choose "
    L"Stop alarm, or press Esc to stop both the alarm indication and audio played by the application.\r\n\r\nSHORTCUTS AND SAVING\r\nDouble-click a clock to toggle seconds, "
    L"press F1 for Help, B for Settings, and Esc to hide a widget when no alarm is being stopped. Widget positions are saved after dragging, dialog positions when closed, "
    L"and all settings in the selected storage. Starting the program again activates the running instance and keeps widgets at the nearest available point in the work area.",
    L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a standalone calendar by its free area; click a day to change the selection and use the arrows, header "
    L"or Today link to navigate. Right-click a widget or notification icon for its menu. Left-click the notification icon to hide the currently visible widgets; when all "
    L"are hidden, it restores only the widgets hidden most recently.\r\n\r\nWIDGETS AND SETTINGS\r\nSettings can add, remove and duplicate any number of analog clocks, digital "
    L"clocks, calendars, calendar-and-clock panels and monitor clocks. Each widget has its own visibility, always-on-top state, language, time zone and offset. Enter "
    L"offsets as [-]HH:mm:ss.ff. Analog clocks and panel clocks have four sizes. Digital clocks support seconds, a leading zero, font, colours, opacity and a transparent background. "
    L"Calendars support week numbers and Sunday as the first day and use the widget language.\r\n\r\nALARM\r\nClocks and panels can have an alarm. The application plays "
    L"an audio file itself, once or continuously according to the loop option. Other files or commands are passed to Windows. Click the alarming clock face or display, choose "
    L"Stop alarm, or press Esc to stop both the alarm indication and audio played by the application.\r\n\r\nSHORTCUTS AND SAVING\r\nDouble-click a clock to toggle seconds, "
    L"press F1 for Help, B for Settings, and Esc to hide a widget when no alarm is being stopped. Widget positions are saved after dragging, dialog positions when closed, "
    L"and all settings in the selected storage. Starting the program again activates the running instance and keeps widgets at the nearest available point in the work area.",
    L"CONTROLOS\r\nArraste um relógio ou painel com o botão esquerdo. Arraste um calendário autónomo pela área livre e clique num dia para o selecionar. O botão direito "
    L"abre o menu do widget. Um clique esquerdo no ícone de notificação oculta os widgets visíveis ou repõe os ocultados mais recentemente.\r\n\r\nWIDGETS E DEFINIÇÕES\r\nPode "
    L"adicionar, remover e duplicar relógios analógicos, digitais, calendários, painéis combinados e relógios de monitor. Cada widget tem visibilidade, posição no topo, "
    L"idioma, fuso horário e desvio próprios.\r\n\r\nALARME\r\nRelógios e painéis podem ter um alarme. Clique no mostrador ou visor em alarme, escolha Parar alarme ou "
    L"prima Esc para parar a indicação e o áudio interno.\r\n\r\nATALHOS\r\nUm duplo clique alterna os segundos, F1 abre a Ajuda, B abre as Definições e Esc oculta o widget.",
    L"KONTROLLER\r\nDra en klokke eller et panel med venstre museknapp. Dra en frittstående kalender i det ledige området og klikk en dag for å velge den. Høyreklikk åpner "
    L"widgetmenyen. Et venstreklikk på systemstatusikonet skjuler synlige widgeter eller gjenoppretter de sist skjulte.\r\n\r\nWIDGETER OG INNSTILLINGER\r\nDu kan legge "
    L"til, fjerne og duplisere analoge klokker, digitale klokker, kalendere, kombinerte paneler og skjermklokker. Hver widget har egne innstillinger for synlighet, alltid "
    L"øverst, språk, tidssone og forskyvning.\r\n\r\nALARM\r\nKlokker og paneler kan ha en alarm. Klikk urskiven eller skjermen som alarmerer, velg Stopp alarm eller "
    L"trykk Esc for å stoppe indikasjonen og intern lyd.\r\n\r\nSNARVEIER\r\nDobbeltklikk veksler sekunder, F1 åpner Hjelp, B åpner Innstillinger og Esc skjuler widgeten.",
    L"KONTROLLER\r\nDra en klocka eller panel med vänster musknapp. Dra en fristående kalender i det fria området och klicka på en dag för att välja den. Högerklick öppnar "
    L"widgetmenyn. Ett vänsterklick på meddelandeikonen döljer synliga widgetar eller återställer de senast dolda.\r\n\r\nWIDGETAR OCH INSTÄLLNINGAR\r\nDu kan lägga till, "
    L"ta bort och duplicera analoga klockor, digitala klockor, kalendrar, kombinerade paneler och skärmklockor. Varje widget har egna inställningar för synlighet, alltid "
    L"överst, språk, tidszon och förskjutning.\r\n\r\nALARM\r\nKlockor och paneler kan ha ett alarm. Klicka på urtavlan eller displayen som larmar, välj Stoppa alarm eller "
    L"tryck Esc för att stoppa indikeringen och internt ljud.\r\n\r\nGENVÄGAR\r\nDubbelklick växlar sekunder, F1 öppnar Hjälp, B öppnar Inställningar och Esc döljer widgeten.",
    L"OHJAUS\r\nVedä kelloa tai paneelia hiiren vasemmalla painikkeella. Vedä erillistä kalenteria vapaalta alueelta ja valitse päivä napsauttamalla. Napsauta hiiren kakkospainikkeella "
    L"avataksesi pienoisohjelman valikon. Ilmoitusalueen kuvakkeen napsautus piilottaa näkyvät pienoisohjelmat tai palauttaa viimeksi piilotetut.\r\n\r\nPIENOISOHJELMAT JA "
    L"ASETUKSET\r\nVoit lisätä, poistaa ja monistaa analogisia ja digitaalisia kelloja, kalentereita, yhdistelmäpaneeleita ja näyttökelloja. Jokaisella on omat näkyvyys-, päällimmäisyys-, "
    L"kieli-, aikavyöhyke- ja poikkeama-asetukset.\r\n\r\nHERÄTYS\r\nKelloissa ja paneeleissa voi olla herätys. Pysäytä ilmaisin ja sisäinen ääni napsauttamalla hälyttävää "
    L"näyttöä, valitsemalla Pysäytä herätys tai painamalla Esc.\r\n\r\nPIKANÄPPÄIMET\r\nKaksoisnapsautus vaihtaa sekunnit, F1 avaa ohjeen, B asetukset ja Esc piilottaa pienoisohjelman.",
    L"BETJENING\r\nTræk et ur eller panel med venstre museknap. Træk en selvstændig kalender i det frie område og klik på en dag for at vælge den. Højreklik åbner "
    L"widgetmenuen. Et venstreklik på meddelelsesikonet skjuler synlige widgets eller gendanner de senest skjulte.\r\n\r\nWIDGETS OG INDSTILLINGER\r\nDu kan tilføje, "
    L"fjerne og duplikere analoge ure, digitale ure, kalendere, kombinerede paneler og skærmure. Hver widget har egne indstillinger for synlighed, altid øverst, "
    L"sprog, tidszone og forskydning.\r\n\r\nALARM\r\nUre og paneler kan have en alarm. Klik på den alarmerende urskive eller visning, vælg Stop alarm eller tryk "
    L"Esc for at stoppe indikationen og intern lyd.\r\n\r\nGENVEJE\r\nDobbeltklik skifter sekunder, F1 åbner Hjælp, B åbner Indstillinger og Esc skjuler widgeten.",
    L"STJÓRNUN\r\nDragðu klukku eða spjald með vinstri músarhnappi. Dragðu sjálfstætt dagatal á auðu svæði og smelltu á dag til að velja hann. Hægrismellur opnar "
    L"valmynd græju. Vinstrismellur á tilkynningatáknið felur sýnilegar græjur eða endurheimtir þær sem síðast voru faldar.\r\n\r\nGRÆJUR OG STILLINGAR\r\nHægt "
    L"er að bæta við, fjarlægja og afrita skífuklukkur, stafrænar klukkur, dagatöl, samsett spjöld og skjáklukkur. Hver græja hefur eigið sýnileika-, efst-, "
    L"tungumála-, tímabeltis- og hliðrunargildi.\r\n\r\nVEKJARI\r\nKlukkur og spjöld geta haft vekjara. Smelltu á skífuna eða skjáinn, veldu Stöðva vekjara eða ýttu "
    L"á Esc til að stöðva merkingu og innra hljóð.\r\n\r\nFLÝTILEIÐIR\r\nTvísmellur skiptir um sekúndur, F1 opnar Hjálp, B opnar Stillingar og Esc felur græjuna.",
    L"DENETİMLER\r\nBir saati veya paneli sol fare düğmesiyle sürükleyin. Bağımsız takvimi boş alanından sürükleyin ve seçmek için bir güne tıklayın. Sağ tıklama araç "
    L"menüsünü açar. Bildirim simgesine sol tıklamak görünür araçları gizler veya en son gizlenenleri geri getirir.\r\n\r\nARAÇLAR VE AYARLAR\r\nAnalog saatler, dijital "
    L"saatler, takvimler, birleşik paneller ve monitör saatleri ekleyebilir, kaldırabilir ve çoğaltabilirsiniz. Her aracın görünürlük, her zaman üstte, dil, saat dilimi "
    L"ve ofset ayarları ayrıdır.\r\n\r\nALARM\r\nSaatlerde ve panellerde alarm olabilir. Alarm veren kadrana veya ekrana tıklayın, Alarmı durdur'u seçin ya da göstergeyi "
    L"ve dahili sesi durdurmak için Esc tuşuna basın.\r\n\r\nKISAYOLLAR\r\nÇift tıklama saniyeleri açıp kapatır, F1 Yardım'ı, B Ayarlar'ı açar ve Esc aracı gizler."
};

const wchar_t* HELP_ALARM_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZADÁVÁNÍ ČASU A AKCE BUDÍKU\r\nČas budíku přijímá běžný tvar HH:mm s dvojtečkou, tečkou, mezerou či jiným oddělovačem; oddělovač lze také vynechat. Jedna nebo dvě "
    L"číslice znamenají hodiny, tři nebo čtyři číslice hodiny a minuty, například 7, 12, 730, 0730 nebo 7:30. Po opuštění pole se čas sjednotí na HH:mm. Offset se zadává zprava "
    L"od sekund: 2 znamená 00:00:02.00, 230 i 0230 znamená 00:02:30.00 a 12345 znamená 01:23:45.00. Při odděleném zápisu jsou dvě skupiny minuty a sekundy, tři skupiny hodiny, "
    L"minuty a sekundy a čtvrtá skupina setiny; lze použít znaménko. Dny pod volbou Budík aktivní určují, ve které dny se budík spustí; výchozí jsou všechny dny. Jejich "
    L"pořadí se řídí kulturou aplikace a změna jazyka nemění uložené dny. Při spuštění budík zobrazí skrytý widget a přenese jej před ostatní okna, aniž trvale změní Vždy "
    L"navrchu. Volba Pípat časové znamení spustí první krátký tón pět sekund před časem budíku. Je nezávislá na kartě Znamení; souběžné sekvence se však sloučí. Tlačítko "
    L"Vyzkoušet rozbliká aktuální ciferník či rám panelu a asynchronně vyzkouší soubor, příkaz, zvuk, HTTP/HTTPS adresu vzdáleného skriptu a při zapnuté volbě i celé "
    L"časové znamení. Zastavení testu ukončí jeho interní zvuk a náhled znamení; zastavení budíku ukončí jeho interní zvuk. Ztlumení interní přehrávání nezastaví: "
    L"pokračuje potichu a po zrušení ztlumení je znovu slyšet. Příkazy a vzdálené skripty ztlumení neovlivňuje. Spustit soubor nebo příkaz zpřístupní pole, "
    L"Vybrat, Vyzkoušet a opakování; Vyzkoušet a opakování navíc vyžadují neprázdný údaj, probíhající test však lze vždy zastavit.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, space or another separator; the separator may also be omitted. One or two digits mean hours, "
    L"while three or four digits mean hours and minutes, for example 7, 12, 730, 0730 or 7:30. The value is normalized to HH:mm after leaving the field. Offset entry starts from seconds "
    L"on the right: 2 means 00:00:02.00, 230 and 0230 mean 00:02:30.00, and 12345 means 01:23:45.00. With separators, two groups mean minutes and seconds, three mean hours, minutes and "
    L"seconds, and a fourth group contains hundredths; a sign is accepted. The days below Alarm enabled select the weekdays on which the alarm runs; all days are selected by default. "
    L"Their order follows the application culture, and changing the language does not change the stored weekdays. When triggered, the alarm shows a hidden widget and brings it in "
    L"front without permanently changing Always on top. Sound the time signal starts its first short pip five seconds before the alarm. It is independent of the Signal tab, "
    L"although coincident sequences are merged. Test flashes the selected clock face or panel frame and asynchronously tests the file, command, audio, HTTP/HTTPS remote-script URL "
    L"and, when selected, the complete time-signal sequence. Stopping the test stops its internal audio and signal preview; stopping the alarm stops its internal audio. "
    L"Muting does not stop internal playback: it continues silently and becomes audible again after unmuting. Commands and remote scripts are unaffected. Run a file or "
    L"command enables its field, Browse, Test and looping; Test and looping also require a nonblank value, but a running test can always be stopped.",
    L"\r\n\r\nZEITEINGABE UND WECKERAKTIONEN\r\nDie Weckzeit akzeptiert HH:mm mit Doppelpunkt, Punkt, Leerzeichen oder einem anderen Trennzeichen; das Trennzeichen kann entfallen. Eine oder "
    L"zwei Ziffern bedeuten Stunden, drei oder vier Ziffern Stunden und Minuten, z. B. 7, 12, 730, 0730 oder 7:30. Beim Verlassen des Feldes wird HH:mm verwendet. Der Versatz wird von "
    L"rechts ab den Sekunden eingegeben: 2 bedeutet 00:00:02.00, 230 und 0230 bedeuten 00:02:30.00 und 12345 bedeutet 01:23:45.00. Mit Trennzeichen stehen zwei Gruppen für Minuten und "
    L"Sekunden, drei für Stunden, Minuten und Sekunden und eine vierte für Hundertstel; ein Vorzeichen ist zulässig. Die Tage unter Wecker aktiv bestimmen, an welchen Wochentagen der "
    L"Wecker läuft; standardmäßig sind alle gewählt. Ihre Reihenfolge folgt der Anwendungskultur; ein Sprachwechsel ändert die gespeicherten Wochentage nicht. Beim Auslösen zeigt der "
    L"Wecker ein verborgenes Widget und bringt es nach vorn, ohne Immer im Vordergrund dauerhaft zu ändern. Akustisches Zeitzeichen startet den ersten kurzen Ton fünf Sekunden vor dem "
    L"Wecker. Diese Wahl ist von der Registerkarte Zeitzeichen unabhängig; gleichzeitige Folgen werden jedoch zusammengeführt. Testen lässt Zifferblatt oder Panelrahmen blinken und "
    L"prüft Datei, Befehl, Audio, eine HTTP/HTTPS-Adresse eines Remote-Skripts sowie bei aktivierter Option die vollständige Zeitzeichenfolge asynchron. Das Stoppen des Tests "
    L"beendet dessen internes Audio und die Signalvorschau; das Stoppen des Weckers beendet sein internes Audio. Stummschalten beendet die interne Wiedergabe nicht: Sie läuft "
    L"lautlos weiter und wird nach dem Aufheben wieder hörbar. Befehle und Remote-Skripte bleiben unberührt. Datei oder Befehl starten aktiviert Feld, Durchsuchen, Test "
    L"und Wiederholung; Test und Wiederholung erfordern zusätzlich einen nicht leeren Wert, ein laufender Test kann jedoch immer gestoppt werden.",
    L"\r\n\r\nSAISIE DE L’HEURE ET ACTIONS D’ALARME\r\nL’heure accepte HH:mm avec deux-points, point, espace ou un autre séparateur, qui peut aussi être omis. Un ou deux chiffres "
    L"indiquent les heures, trois ou quatre les heures et les minutes, par exemple 7, 12, 730, 0730 ou 7:30. La valeur devient HH:mm à la sortie du champ. Le décalage se saisit de "
    L"droite à partir des secondes : 2 signifie 00:00:02.00, 230 et 0230 signifient 00:02:30.00, et 12345 signifie 01:23:45.00. Avec séparateurs, deux groupes représentent minutes et "
    L"secondes, trois représentent heures, minutes et secondes, et un quatrième les centièmes ; un signe est accepté. Les jours sous Alarme active déterminent les jours où l’alarme "
    L"fonctionne ; tous sont sélectionnés par défaut. Leur ordre suit la culture de l’application ; changer de langue ne modifie pas les jours enregistrés. Lors du déclenchement, "
    L"l’alarme affiche un widget masqué et le ramène devant sans modifier durablement Toujours visible. Émettre le signal horaire lance le premier bip court cinq secondes avant "
    L"l’alarme. Ce choix est indépendant de l’onglet Signal, mais les séquences simultanées sont fusionnées. Tester fait clignoter le cadran ou le cadre du panneau et teste de "
    L"façon asynchrone le fichier, la commande, l’audio, l’URL HTTP/HTTPS du script distant et, si l’option est activée, la séquence complète du signal horaire. Arrêter le "
    L"test coupe son audio interne et son aperçu du signal ; arrêter l’alarme coupe son audio interne. Couper le son n’arrête pas la lecture interne : elle continue "
    L"silencieusement et redevient audible après rétablissement. Les commandes et scripts distants ne sont pas affectés. Lancer un fichier ou une commande active le "
    L"champ, Parcourir, Tester et la boucle ; Tester et la boucle exigent aussi une valeur non vide, mais un test en cours peut toujours être arrêté.",
    L"\r\n\r\nENTRADA DE HORA Y ACCIONES DE ALARMA\r\nLa hora admite HH:mm con dos puntos, punto, espacio u otro separador, que también puede omitirse. Uno o dos dígitos indican horas; tres o "
    L"cuatro, horas y minutos, por ejemplo 7, 12, 730, 0730 o 7:30. Al salir del campo se normaliza a HH:mm. El desfase se introduce desde la derecha empezando por los segundos: 2 es "
    L"00:00:02.00, 230 y 0230 son 00:02:30.00, y 12345 es 01:23:45.00. Con separadores, dos grupos son minutos y segundos, tres son horas, minutos y segundos, y un cuarto contiene centésimas; "
    L"se admite signo. Los días bajo Alarma activa determinan los días de la semana en que funciona; todos están seleccionados de forma predeterminada. Su orden sigue la cultura de la "
    L"aplicación; cambiar el idioma no modifica los días guardados. Al activarse, la alarma muestra un widget oculto y lo lleva al frente sin cambiar permanentemente Siempre visible. Emitir "
    L"la señal horaria inicia el primer pitido corto cinco segundos antes de la alarma. Es independiente de la pestaña Señal, aunque las secuencias coincidentes se combinan. Probar hace "
    L"parpadear la esfera o el marco del panel y prueba de forma asíncrona el archivo, el comando, el audio, la URL HTTP/HTTPS del script remoto y, si está activada, la secuencia "
    L"completa de la señal horaria. Detener la prueba también detiene su audio interno y la vista previa de la señal; detener la alarma detiene su audio interno. Silenciar no "
    L"detiene la reproducción interna: continúa en silencio y vuelve a oírse al reactivar el sonido. No afecta a comandos ni scripts remotos. Ejecutar archivo o comando activa "
    L"el campo, Examinar, Probar y la repetición; Probar y repetir también requieren un valor no vacío, pero una prueba en curso siempre puede detenerse.",
    L"\r\n\r\nIMMISSIONE DELL’ORA E AZIONI SVEGLIA\r\nL’ora accetta HH:mm con due punti, punto, spazio o un altro separatore, che può anche essere omesso. Una o due cifre indicano "
    L"le ore; tre o quattro indicano ore e minuti, per esempio 7, 12, 730, 0730 o 7:30. Uscendo dal campo il valore diventa HH:mm. L’offset si inserisce da destra partendo dai "
    L"secondi: 2 significa 00:00:02.00, 230 e 0230 significano 00:02:30.00 e 12345 significa 01:23:45.00. Con separatori, due gruppi sono minuti e secondi, tre sono ore, minuti "
    L"e secondi e un quarto contiene i centesimi; è ammesso il segno. I giorni sotto Sveglia attiva stabiliscono in quali giorni suona; per impostazione predefinita sono "
    L"selezionati tutti. L’ordine segue la cultura dell’applicazione; cambiare lingua non modifica i giorni memorizzati. All’attivazione, la sveglia mostra un widget nascosto "
    L"e lo porta davanti senza cambiare in modo permanente Sempre in primo piano. Emetti il segnale orario avvia il primo segnale breve cinque secondi prima della sveglia. "
    L"È indipendente dalla scheda Segnale, ma le sequenze coincidenti vengono unite. Prova fa lampeggiare il quadrante o il bordo del pannello e verifica in modo "
    L"asincrono file, comando, audio, URL HTTP/HTTPS dello script remoto e, se selezionata, l’intera sequenza del segnale orario. L’arresto della prova interrompe il suo "
    L"audio interno e l’anteprima del segnale; l’arresto della sveglia interrompe il suo audio interno. Disattivare l’audio non ferma la riproduzione interna: "
    L"continua silenziosa e torna udibile alla riattivazione. Comandi e script remoti non sono interessati. Esegui file o comando abilita il campo, Sfoglia, "
    L"Prova e la ripetizione; Prova e ripetizione richiedono anche un valore non vuoto, ma una prova in corso può sempre essere interrotta.",
    L"\r\n\r\nWPROWADZANIE CZASU I AKCJE ALARMU\r\nCzas alarmu przyjmuje HH:mm z dwukropkiem, kropką, spacją lub innym separatorem; separator można pominąć. Jedna lub dwie cyfry "
    L"oznaczają godziny, trzy lub cztery godziny i minuty, np. 7, 12, 730, 0730 albo 7:30. Po opuszczeniu pola wartość przyjmuje postać HH:mm. Przesunięcie wpisuje się od prawej, "
    L"zaczynając od sekund: 2 oznacza 00:00:02.00, 230 i 0230 oznaczają 00:02:30.00, a 12345 oznacza 01:23:45.00. Przy separatorach dwie grupy oznaczają minuty i sekundy, trzy godziny, "
    L"minuty i sekundy, a czwarta setne części; znak jest dozwolony. Dni pod opcją Alarm aktywny określają dni tygodnia działania alarmu; domyślnie zaznaczone są wszystkie. Ich "
    L"kolejność zależy od kultury aplikacji; zmiana języka nie zmienia zapisanych dni. Po uruchomieniu alarm pokazuje ukryty widżet i przenosi go do przodu bez trwałej zmiany Zawsze "
    L"na wierzchu. Odtwarzaj sygnał czasu uruchamia pierwszy krótki sygnał pięć sekund przed alarmem. Opcja jest niezależna od karty Sygnał, lecz zbieżne sekwencje są łączone. "
    L"Test miga tarczą lub ramką panelu i asynchronicznie sprawdza plik, polecenie, dźwięk, adres HTTP/HTTPS zdalnego skryptu oraz, jeśli wybrano tę opcję, pełną sekwencję "
    L"sygnału czasu. Zatrzymanie testu wyłącza jego dźwięk wewnętrzny i podgląd sygnału; zatrzymanie alarmu wyłącza jego dźwięk wewnętrzny. Wyciszenie nie zatrzymuje "
    L"odtwarzania wewnętrznego: trwa ono bezgłośnie i po włączeniu dźwięku znów jest słyszalne. Polecenia i zdalne skrypty pozostają bez zmian. Uruchom plik lub polecenie "
    L"uaktywnia pole, Wybierz, Test i powtarzanie; Test i powtarzanie wymagają też niepustej wartości, ale trwający test zawsze można zatrzymać.",
    L"\r\n\r\nZADÁVANIE ČASU A AKCIE BUDÍKA\r\nČas budíka prijíma HH:mm s dvojbodkou, bodkou, medzerou alebo iným oddeľovačom; oddeľovač možno aj vynechať. Jedna alebo dve "
    L"číslice znamenajú hodiny, tri alebo štyri hodiny a minúty, napríklad 7, 12, 730, 0730 alebo 7:30. Po opustení poľa sa hodnota upraví na HH:mm. Offset sa zadáva sprava od "
    L"sekúnd: 2 znamená 00:00:02.00, 230 aj 0230 znamená 00:02:30.00 a 12345 znamená 01:23:45.00. Pri oddelenom zápise sú dve skupiny minúty a sekundy, tri skupiny hodiny, "
    L"minúty a sekundy a štvrtá skupina stotiny; možno použiť znamienko. Dni pod voľbou Budík aktívny určujú, v ktoré dni sa budík spustí; predvolene sú vybrané všetky. Ich "
    L"poradie sa riadi kultúrou aplikácie a zmena jazyka nemení uložené dni. Po spustení budík zobrazí skrytý widget a prenesie ho pred ostatné okná bez trvalej zmeny "
    L"Vždy navrchu. Voľba Pípať časové znamenie spustí prvý krátky tón päť sekúnd pred časom budíka. Je nezávislá od karty Znamenie; súbežné sekvencie sa však zlúčia. "
    L"Vyskúšať rozbliká ciferník alebo rám panela a asynchrónne otestuje súbor, príkaz, zvuk, HTTP/HTTPS adresu vzdialeného skriptu a pri zapnutej voľbe aj celé "
    L"časové znamenie. Zastavenie testu ukončí jeho interný zvuk a náhľad znamenia; zastavenie budíka ukončí interný zvuk. Stlmenie interné prehrávanie nezastaví: "
    L"pokračuje potichu a po zrušení stlmenia je znovu počuť. Príkazy a vzdialené skripty stlmenie neovplyvňuje. Spustiť súbor alebo príkaz sprístupní pole, "
    L"Vybrať, Vyskúšať a opakovanie; Vyskúšať a opakovanie navyše vyžadujú neprázdny údaj, ale prebiehajúci test možno vždy zastaviť.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, space or another separator; the separator may also be omitted. One or two digits mean hours, "
    L"while three or four digits mean hours and minutes, for example 7, 12, 730, 0730 or 7:30. The value is normalized to HH:mm after leaving the field. Offset entry starts from seconds "
    L"on the right: 2 means 00:00:02.00, 230 and 0230 mean 00:02:30.00, and 12345 means 01:23:45.00. With separators, two groups mean minutes and seconds, three mean hours, minutes and "
    L"seconds, and a fourth group contains hundredths; a sign is accepted. The days below Alarm enabled select the weekdays on which the alarm runs; all days are selected by default. "
    L"Their order follows the application culture, and changing the language does not change the stored weekdays. When triggered, the alarm shows a hidden widget and brings it in "
    L"front without permanently changing Always on top. Sound the time signal starts its first short pip five seconds before the alarm. It is independent of the Signal tab, "
    L"although coincident sequences are merged. Test flashes the selected clock face or panel frame and asynchronously tests the file, command, audio, HTTP/HTTPS remote-script URL "
    L"and, when selected, the complete time-signal sequence. Stopping the test stops its internal audio and signal preview; stopping the alarm stops its internal audio. "
    L"Muting does not stop internal playback: it continues silently and becomes audible again after unmuting. Commands and remote scripts are unaffected. Run a file or "
    L"command enables its field, Browse, Test and looping; Test and looping also require a nonblank value, but a running test can always be stopped.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, space or another separator; the separator may also be omitted. One or two digits mean hours, "
    L"while three or four digits mean hours and minutes, for example 7, 12, 730, 0730 or 7:30. The value is normalized to HH:mm after leaving the field. Offset entry starts from seconds "
    L"on the right: 2 means 00:00:02.00, 230 and 0230 mean 00:02:30.00, and 12345 means 01:23:45.00. With separators, two groups mean minutes and seconds, three mean hours, minutes and "
    L"seconds, and a fourth group contains hundredths; a sign is accepted. The days below Alarm enabled select the weekdays on which the alarm runs; all days are selected by default. "
    L"Their order follows the application culture, and changing the language does not change the stored weekdays. When triggered, the alarm shows a hidden widget and brings it in "
    L"front without permanently changing Always on top. Sound the time signal starts its first short pip five seconds before the alarm. It is independent of the Signal tab, "
    L"although coincident sequences are merged. Test flashes the selected clock face or panel frame and asynchronously tests the file, command, audio, HTTP/HTTPS remote-script URL "
    L"and, when selected, the complete time-signal sequence. Stopping the test stops its internal audio and signal preview; stopping the alarm stops its internal audio. "
    L"Muting does not stop internal playback: it continues silently and becomes audible again after unmuting. Commands and remote scripts are unaffected. Run a file or "
    L"command enables its field, Browse, Test and looping; Test and looping also require a nonblank value, but a running test can always be stopped.",
    L"\r\n\r\nHORA E AÇÕES DO ALARME\r\nA hora aceita HH:mm com ou sem separador: 7, 12, 730, 0730 ou 7:30. O desvio é lido da direita a partir dos segundos: 2 é "
    L"00:00:02.00, 230 é 00:02:30.00 e 12345 é 01:23:45.00. Os dias definem quando o alarme funciona e todos vêm selecionados. A ordem segue a cultura da aplicação; "
    L"mudar o idioma não altera os dias guardados. Ao disparar, mostra um widget oculto e leva-o à frente sem alterar permanentemente Sempre no topo. O sinal "
    L"começa cinco segundos antes. Testar verifica de forma assíncrona a indicação, o áudio, o comando e o script remoto. Silenciar não para a reprodução "
    L"interna; continua sem som e volta a ouvir-se depois. Comandos e scripts remotos não são afetados. Executar um ficheiro ou comando ativa o campo, "
    L"Procurar, Testar e a repetição; Testar e repetir exigem também um valor não vazio, mas um teste em curso pode sempre ser parado.",
    L"\r\n\r\nTIDSANGIVELSE OG ALARMHANDLINGER\r\nAlarmtid godtar HH:mm med eller uten skilletegn: 7, 12, 730, 0730 eller 7:30. Forskyvningen leses fra høyre fra "
    L"sekundene: 2 er 00:00:02.00, 230 er 00:02:30.00 og 12345 er 01:23:45.00. Dagene angir når alarmen kjører, og alle er valgt som standard. Rekkefølgen følger "
    L"programkulturen; språkbytte endrer ikke de lagrede ukedagene. Når alarmen utløses, vises en skjult widget og bringes frem uten å endre Alltid øverst permanent. "
    L"Tidssignalet starter fem sekunder før. Test kontrollerer indikasjon, lyd, kommando og eksternt skript asynkront. Demping stopper ikke intern avspilling; "
    L"den fortsetter lydløst og blir hørbar igjen etterpå. Kommandoer og eksterne skript påvirkes ikke. Kjør en fil eller kommando aktiverer feltet, Bla "
    L"gjennom, Test og gjentakelse; Test og gjentakelse krever også en verdi som ikke er tom, men en pågående test kan alltid stoppes.",
    L"\r\n\r\nTIDSINMATNING OCH ALARMÅTGÄRDER\r\nAlarmtiden godtar HH:mm med eller utan avgränsare: 7, 12, 730, 0730 eller 7:30. Förskjutningen läses från höger med "
    L"sekunder först: 2 är 00:00:02.00, 230 är 00:02:30.00 och 12345 är 01:23:45.00. Dagarna anger när alarmet körs och alla är valda från början. Ordningen följer "
    L"programkulturen; ett språkbyte ändrar inte de sparade veckodagarna. När alarmet utlöses visas en dold widget och förs fram utan att Alltid överst ändras "
    L"permanent. Tidssignalen börjar fem sekunder före. Test provar indikering, ljud, kommando och fjärrskript asynkront. Tystning stoppar inte intern uppspelning; "
    L"den fortsätter tyst och hörs igen efter återaktivering. Kommandon och fjärrskript påverkas inte. Kör en fil eller ett kommando aktiverar fältet, "
    L"Bläddra, Testa och upprepning; Testa och upprepning kräver också ett värde som inte är tomt, men ett pågående test kan alltid stoppas.",
    L"\r\n\r\nAJAN SYÖTTÖ JA HERÄTYKSEN TOIMINNOT\r\nHerätysaika hyväksyy HH:mm-muodon erottimella tai ilman: 7, 12, 730, 0730 tai 7:30. Poikkeama luetaan oikealta sekunneista "
    L"alkaen: 2 on 00:00:02.00, 230 on 00:02:30.00 ja 12345 on 01:23:45.00. Päivät määräävät milloin herätys toimii; kaikki ovat oletuksena valittuina. Järjestys seuraa "
    L"sovelluksen kulttuuria, eikä kielen vaihto muuta tallennettuja viikonpäiviä. Hälytys näyttää piilotetun pienoisohjelman ja tuo sen eteen muuttamatta pysyvästi Aina "
    L"päällimmäisenä -tilaa. Aikamerkki alkaa viisi sekuntia ennen. Testi tarkistaa ilmaisimen, äänen, komennon ja etäkomentosarjan asynkronisesti. Mykistys ei pysäytä "
    L"sisäistä toistoa; se jatkuu äänettömänä ja kuuluu taas mykistyksen jälkeen. Komennot ja etäkomentosarjat eivät muutu. Suorita tiedosto tai komento ottaa käyttöön "
    L"kentän, Selaa-, Testaa- ja toistovalinnat; Testaa ja toisto vaativat muun kuin tyhjän arvon, mutta käynnissä olevan testin voi aina pysäyttää.",
    L"\r\n\r\nTIDSINDTASTNING OG ALARMHANDLINGER\r\nAlarmtid accepterer HH:mm med eller uden skilletegn: 7, 12, 730, 0730 eller 7:30. Forskydningen læses fra højre fra "
    L"sekunderne: 2 er 00:00:02.00, 230 er 00:02:30.00 og 12345 er 01:23:45.00. Dagene bestemmer hvornår alarmen kører, og alle er valgt som standard. Rækkefølgen "
    L"følger programkulturen; et sprogskift ændrer ikke de gemte ugedage. Når alarmen udløses, vises en skjult widget og føres frem uden permanent at ændre Altid "
    L"øverst. Tidssignalet starter fem sekunder før. Test afprøver indikationen, lyd, kommando og fjernscript asynkront. Dæmpning stopper ikke intern afspilning; "
    L"den fortsætter lydløst og kan høres igen efter ophævelse. Kommandoer og fjernscripts påvirkes ikke. Kør en fil eller kommando aktiverer feltet, "
    L"Gennemse, Test og gentagelse; Test og gentagelse kræver også en værdi, der ikke er tom, men en igangværende test kan altid stoppes.",
    L"\r\n\r\nINNSLÁTTUR TÍMA OG AÐGERÐIR VEKJARA\r\nVekjaratími tekur við HH:mm með eða án skilmerkis: 7, 12, 730, 0730 eða 7:30. Hliðrun er lesin frá hægri frá sekúndum: "
    L"2 er 00:00:02.00, 230 er 00:02:30.00 og 12345 er 01:23:45.00. Dagarnir ákvarða hvenær vekjarinn virkar og allir eru sjálfgefið valdir. Röðin fylgir menningu "
    L"forritsins; tungumálaskipti breyta ekki vistuðum vikudögum. Þegar vekjari fer af stað sýnir hann falda græju og færir hana fremst án þess að breyta varanlega "
    L"Alltaf efst. Tímamerkið hefst fimm sekúndum fyrr. Prófun kannar merkingu, hljóð, skipun og fjarskriftu ósamstillt. Þöggun stöðvar ekki innri spilun; hún "
    L"heldur hljóðlaus áfram og heyrist aftur þegar þöggun er aflétt. Skipanir og fjarskriftur breytast ekki. Keyra skrá eða skipun virkjar reitinn, Velja, "
    L"Prófa og endurtekningu; Prófa og endurtekning krefjast einnig gildis sem er ekki autt, en alltaf má stöðva prófun sem er í gangi.",
    L"\r\n\r\nZAMAN GİRİŞİ VE ALARM EYLEMLERİ\r\nAlarm zamanı ayırıcıyla veya ayırıcı olmadan HH:mm kabul eder: 7, 12, 730, 0730 ya da 7:30. Ofset sağdan saniyelerden "
    L"başlayarak okunur: 2 değeri 00:00:02.00, 230 değeri 00:02:30.00 ve 12345 değeri 01:23:45.00 olur. Günler alarmın ne zaman çalışacağını belirler ve varsayılan olarak "
    L"tümü seçilidir. Sıralama uygulama kültürünü izler; dil değişikliği kayıtlı günleri değiştirmez. Alarm tetiklendiğinde gizli aracı gösterir ve kalıcı üstte durumunu "
    L"değiştirmeden öne getirir. Zaman sinyali beş saniye önce başlar. Test; göstergeyi, sesi, komutu ve uzak betiği eşzamansız olarak sınar. Sessize alma dahili "
    L"oynatmayı durdurmaz; sessizce sürer ve ses açılınca yeniden duyulur. Komutlar ve uzak betikler etkilenmez. Dosya veya komut çalıştır; alanı, Gözat, Test "
    L"ve yinelemeyi etkinleştirir. Test ve yineleme ayrıca boş olmayan bir değer gerektirir, ancak çalışan test her zaman durdurulabilir."
};

const wchar_t* HELP_SELECTION_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nVÝBĚR, KLÁVESY A KOPÍROVÁNÍ DATA\r\nV seznamu widgetů označíte více položek pomocí Ctrl, Shift nebo Ctrl+A. Ovládací prvky na kartách Obecné, Vzhled, Budík a Znamení se "
    L"potom zneaktivní, globální karty Čas a Aplikace však zůstanou dostupné. Nastavení si pamatuje poslední otevřenou kartu a Přidat poslední skutečně přidaný typ. Odebrat nebo "
    L"Del odstraní všechny označené položky až po použití změn. Dvojklik položky zobrazí případně skrytý widget, nastaví Zobrazeno a krátce jej zvýrazní. Volba Nastavení v "
    L"nabídce konkrétního widgetu jej v seznamu rovnou vybere. Ctrl+A i trojklik označí celý obsah textového pole. Kliknutí na den v kalendáři datum vybere a zkopíruje do "
    L"schránky; všechny masky jsou dostupné v každém jazyce a slovní formáty používají jazyk widgetu. Výchozí Krátké datum se řídí jazykem widgetu. "
    L"Insert přepne označení aktuální položky a posune kurzor seznamu o řádek dolů.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nUse Ctrl, Shift or Ctrl+A to select several widgets. Controls on the General, Appearance, Alarm and Signal tabs are "
    L"then disabled, while the global Time and Application tabs remain available. Settings remembers the last open tab, and Add remembers the last type actually "
    L"added. Remove or Del removes all selected items when the changes are applied. Double-clicking an item makes a hidden widget visible, selects Visible and "
    L"identifies the widget briefly. Settings in a specific widget menu selects that widget in the list. Ctrl+A and a triple-click select all text in an edit "
    L"field. Clicking a calendar day selects it and copies it to the clipboard; each calendar has its own format in Settings and its menu. Every pattern is "
    L"available in every language, while textual formats use the widget language. The default Short date follows the widget language. "
    L"Insert toggles the current item and moves the list cursor down one row.",
    L"\r\n\r\nAUSWAHL, TASTEN UND DATUMSKOPIE\r\nMit Strg, Umschalt oder Strg+A wählen Sie mehrere Widgets. Die Bedienelemente der Registerkarten Allgemein, Darstellung, "
    L"Wecker und Zeitzeichen werden dann deaktiviert; die globalen Registerkarten Zeit und Anwendung bleiben verfügbar. Einstellungen merkt sich die zuletzt geöffnete "
    L"Registerkarte, Hinzufügen den zuletzt hinzugefügten Typ. Entfernen oder Entf löscht beim Anwenden alle ausgewählten Einträge. Ein Doppelklick macht ein "
    L"verborgenes Widget sichtbar, aktiviert Sichtbar und kennzeichnet das Widget kurz; Einstellungen im Widget-Menü wählt es in der Liste aus. Strg+A und "
    L"Dreifachklick markieren den gesamten Text eines Eingabefelds. Ein Klick auf einen Kalendertag wählt und kopiert ihn im je Widget eingestellten Format. Alle "
    L"Muster sind in jeder Sprache verfügbar; Textformate verwenden die Widget-Sprache. Das voreingestellte Kurze Datum folgt der Widget-Sprache. "
    L"Einfg schaltet die Markierung des aktuellen Eintrags um und bewegt den Listencursor eine Zeile nach unten.",
    L"\r\n\r\nSÉLECTION, TOUCHES ET COPIE DE DATE\r\nCtrl, Maj ou Ctrl+A sélectionne plusieurs widgets. Les commandes des onglets Général, Apparence, Alarme et Signal sont alors désactivées, "
    L"mais les onglets globaux Heure et Application restent disponibles. Paramètres mémorise le dernier onglet ouvert et Ajouter le dernier type réellement ajouté. Supprimer ou Suppr "
    L"retire toute la sélection lors de l’application. Un double-clic rend visible un widget masqué, coche Visible et l’identifie brièvement ; Paramètres dans son menu le sélectionne "
    L"dans la liste. Ctrl+A et un triple-clic sélectionnent tout le texte d’un champ. Cliquer sur un jour le sélectionne et le copie selon le format propre au calendrier. Tous les "
    L"modèles sont disponibles dans chaque langue ; les formats textuels utilisent la langue du widget. La Date courte par défaut suit la langue du widget. "
    L"Inser bascule la sélection de l’élément courant et descend le curseur de liste d’une ligne.",
    L"\r\n\r\nSELECCIÓN, TECLAS Y COPIA DE FECHA\r\nCtrl, Mayús o Ctrl+A selecciona varios widgets. Los controles de General, Apariencia, Alarma y Señal se desactivan, pero las "
    L"pestañas globales Hora y Aplicación siguen disponibles. Configuración recuerda la última pestaña abierta y Añadir el último tipo realmente añadido. Quitar o Supr elimina todos "
    L"los seleccionados al aplicar los cambios. Un doble clic muestra un widget oculto, activa Visible y lo identifica brevemente; Configuración en su menú lo selecciona en la "
    L"lista. Ctrl+A y un triple clic seleccionan todo el texto de un campo. Pulsar un día lo selecciona y copia según el formato propio del calendario; los formatos de texto "
    L"usan el idioma del widget. Todos los patrones están disponibles en cualquier idioma y la Fecha corta predeterminada sigue el idioma del widget. "
    L"Insert alterna la selección del elemento actual y baja el cursor de la lista una fila.",
    L"\r\n\r\nSELEZIONE, TASTI E COPIA DELLA DATA\r\nCtrl, Maiusc o Ctrl+A seleziona più widget. I controlli delle schede Generale, Aspetto, Sveglia e Segnale vengono disattivati, mentre le "
    L"schede globali Ora e Applicazione restano disponibili. Impostazioni ricorda l’ultima scheda aperta e Aggiungi l’ultimo tipo realmente aggiunto. Rimuovi o Canc elimina tutti gli "
    L"elementi selezionati quando si applicano le modifiche. Un doppio clic rende visibile un widget nascosto, seleziona Visibile e lo identifica brevemente; Impostazioni nel suo "
    L"menu lo seleziona nell’elenco. Ctrl+A e un triplo clic selezionano tutto il testo di un campo. Il clic su un giorno lo seleziona e lo copia nel formato del calendario; i "
    L"formati testuali usano la lingua del widget. Tutti i modelli sono disponibili in ogni lingua e la Data breve predefinita segue la lingua del widget. "
    L"Ins commuta la selezione dell’elemento corrente e sposta il cursore dell’elenco una riga in basso.",
    L"\r\n\r\nZAZNACZANIE, KLAWISZE I KOPIOWANIE DATY\r\nCtrl, Shift lub Ctrl+A zaznacza wiele widżetów. Elementy kart Ogólne, Wygląd, Alarm i Sygnał są wtedy wyłączone, "
    L"ale globalne karty Czas i Aplikacja pozostają dostępne. Ustawienia pamiętają ostatnio otwartą kartę, a Dodaj ostatnio rzeczywiście dodany typ. Usuń lub Del "
    L"usuwa wszystkie zaznaczone pozycje po zastosowaniu zmian. Dwuklik pokazuje ukryty widżet, zaznacza Widoczny i krótko go wskazuje; Ustawienia w jego menu "
    L"wybierają go na liście. Ctrl+A i potrójne kliknięcie zaznaczają cały tekst pola. Kliknięcie dnia wybiera go i kopiuje w formacie danego kalendarza. "
    L"Wszystkie wzorce są dostępne w każdym języku, a formaty słowne używają języka widżetu. Domyślna Data krótka zależy od języka widżetu. "
    L"Insert przełącza zaznaczenie bieżącej pozycji i przesuwa kursor listy o jeden wiersz w dół.",
    L"\r\n\r\nVÝBER, KLÁVESY A KOPÍROVANIE DÁTUMU\r\nPomocou Ctrl, Shift alebo Ctrl+A označíte viac widgetov. Prvky kariet Všeobecné, Vzhľad, Budík a Znamenie sa "
    L"deaktivujú, globálne karty Čas a Aplikácia však zostanú dostupné. Nastavenie si pamätá poslednú otvorenú kartu a Pridať posledný skutočne pridaný typ. "
    L"Odobrať alebo Del odstráni po použití zmien všetky označené položky. Dvojklik zobrazí skrytý widget, začiarkne Zobrazené a krátko ho zvýrazní; Nastavenia v "
    L"jeho ponuke ho vyberú v zozname. Ctrl+A aj trojklik označia celý text poľa. Kliknutie na deň ho vyberie a skopíruje vo formáte daného kalendára. Všetky "
    L"masky sú dostupné v každom jazyku, slovné formáty používajú jazyk widgetu a predvolený Krátky dátum sa riadi jazykom widgetu. "
    L"Insert prepne označenie aktuálnej položky a posunie kurzor zoznamu o riadok nižšie.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nUse Ctrl, Shift or Ctrl+A to select several widgets. Controls on the General, Appearance, Alarm and Signal tabs are "
    L"then disabled, while the global Time and Application tabs remain available. Settings remembers the last open tab, and Add remembers the last type actually "
    L"added. Remove or Del removes all selected items when the changes are applied. Double-clicking an item makes a hidden widget visible, selects Visible and "
    L"identifies the widget briefly. Settings in a specific widget menu selects that widget in the list. Ctrl+A and a triple-click select all text in an edit "
    L"field. Clicking a calendar day selects it and copies it to the clipboard; each calendar has its own format in Settings and its menu. Every pattern is "
    L"available in every language, while textual formats use the widget language. The default Short date follows the widget language. "
    L"Insert toggles the current item and moves the list cursor down one row.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nUse Ctrl, Shift or Ctrl+A to select several widgets. Controls on the General, Appearance, Alarm and Signal tabs are "
    L"then disabled, while the global Time and Application tabs remain available. Settings remembers the last open tab, and Add remembers the last type actually "
    L"added. Remove or Del removes all selected items when the changes are applied. Double-clicking an item makes a hidden widget visible, selects Visible and "
    L"identifies the widget briefly. Settings in a specific widget menu selects that widget in the list. Ctrl+A and a triple-click select all text in an edit "
    L"field. Clicking a calendar day selects it and copies it to the clipboard; each calendar has its own format in Settings and its menu. Every pattern is "
    L"available in every language, while textual formats use the widget language. The default Short date follows the widget language. "
    L"Insert toggles the current item and moves the list cursor down one row.",
    L"\r\n\r\nSELEÇÃO E DATA\r\nUm clique direito e Definições seleciona o widget correspondente. Ctrl+A seleciona todos os widgets ou monitores; "
    L"Delete remove os widgets selecionados. Um duplo clique numa entrada torna o widget visível e realça-o brevemente. Num calendário, clicar num "
    L"dia seleciona-o e copia-o no formato escolhido; todos os formatos estão disponíveis em todos os idiomas. Se forem selecionados vários "
    L"widgets, as opções específicas ficam desativadas, mas os separadores globais Hora e Aplicação permanecem disponíveis. Insert alterna a seleção do item "
    L"atual e desloca o cursor da lista uma linha para baixo.",
    L"\r\n\r\nVALG OG DATO\r\nHøyreklikk og Innstillinger velger den aktuelle widgeten. Ctrl+A velger alle widgeter eller skjermer; Delete fjerner valgte widgeter. "
    L"Dobbeltklikk på en oppføring gjør widgeten synlig og fremhever den kort. Klikk på en dag i kalenderen for å velge og kopiere den i valgt format; alle formater er "
    L"tilgjengelige på alle språk. Når flere widgeter er valgt, deaktiveres widgetvalgene, men de globale fanene Tid og Program forblir tilgjengelige. Insert "
    L"veksler markeringen av gjeldende oppføring og flytter listepekeren én rad ned.",
    L"\r\n\r\nMARKERING OCH DATUM\r\nHögerklick och Inställningar markerar den aktuella widgeten. Ctrl+A markerar alla widgetar eller bildskärmar; Delete tar bort markerade "
    L"widgetar. Dubbelklick på en post visar widgeten och markerar den kort. Klicka på en dag i kalendern för att välja och kopiera den i valt format; alla format finns "
    L"på alla språk. När flera widgetar är markerade inaktiveras widgetalternativen, men de globala flikarna Tid och Program förblir tillgängliga. Insert "
    L"växlar markeringen av den aktuella posten och flyttar listmarkören en rad ned.",
    L"\r\n\r\nVALINTA JA PÄIVÄMÄÄRÄ\r\nNapsauta hiiren kakkospainikkeella ja valitse Asetukset valitaksesi kyseisen pienoisohjelman. Ctrl+A valitsee kaikki "
    L"pienoisohjelmat tai näytöt; Delete poistaa valitut pienoisohjelmat. Luettelon kaksoisnapsautus näyttää pienoisohjelman ja korostaa sen hetkeksi. "
    L"Kalenteripäivän napsautus valitsee ja kopioi sen valitussa muodossa; kaikki muodot ovat käytettävissä kaikilla kielillä. Kun useita "
    L"pienoisohjelmia on valittu, niiden asetukset poistetaan käytöstä, mutta yleiset Aika- ja Sovellus-välilehdet pysyvät käytettävissä. Insert vaihtaa "
    L"nykyisen kohteen valinnan ja siirtää luettelokohdistinta yhden rivin alaspäin.",
    L"\r\n\r\nMARKERING OG DATO\r\nHøjreklik og Indstillinger markerer den pågældende widget. Ctrl+A markerer alle widgets eller skærme; Delete fjerner markerede "
    L"widgets. Dobbeltklik på en post viser widgeten og fremhæver den kort. Klik på en kalenderdag for at vælge og kopiere den i det valgte format; alle formater "
    L"findes på alle sprog. Når flere widgets er markeret, deaktiveres widgetvalgene, men de globale faner Tid og Program forbliver tilgængelige. Insert skifter "
    L"markeringen af det aktuelle element og flytter listemarkøren én række ned.",
    L"\r\n\r\nVAL OG DAGSETNING\r\nHægrismellur og Stillingar velja viðkomandi græju. Ctrl+A velur allar græjur eða skjái; Delete fjarlægir valdar græjur. "
    L"Tvísmellur á færslu sýnir græjuna og auðkennir hana stuttlega. Smelltu á dag í dagatali til að velja og afrita hann á völdu sniði; öll snið eru tiltæk á "
    L"öllum tungumálum. Þegar margar græjur eru valdar óvirkjast græjustillingarnar, en almennu fliparnir Tími og Forrit eru áfram tiltækir. Insert víxlar vali "
    L"núverandi færslu og færir listabendilinn eina línu niður.",
    L"\r\n\r\nSEÇİM VE TARİH\r\nSağ tıklayıp Ayarlar'ı seçmek ilgili aracı seçer. Ctrl+A tüm araçları veya monitörleri seçer; Delete seçili araçları kaldırır. Listedeki bir "
    L"öğeye çift tıklamak aracı görünür yapar ve kısa süre vurgular. Takvimde bir güne tıklamak günü seçili biçimde panoya kopyalar; tüm biçimler tüm dillerde "
    L"kullanılabilir. Birden çok araç seçildiğinde araca özgü seçenekler devre dışı kalır, ancak genel Zaman ve Uygulama sekmeleri kullanılabilir. Insert "
    L"geçerli öğenin seçimini değiştirir ve liste imlecini bir satır aşağı taşır."
};

const wchar_t* HELP_LAYOUT_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nROZLOŽENÍ WIDGETŮ\r\nPříkaz Zarovnat do mřížky zachová přibližné ruční rozmístění, posune středy widgetů na nejbližší body mřížky a odstraní "
    L"překrytí. V nabídce widgetu se upraví jeho monitor, z ikony všechny monitory samostatně. Opakování rozložení nemění. Dvojklik v Nastavení označí widget "
    L"rychlým světlemodrým blikáním; budík bliká pomaleji červeně. Vypnutí Vždy navrchu pošle widget dozadu. V panelu s kalendářem a hodinami je horní datum "
    L"odkaz na dnešek; spodní odkaz otevře klasické nastavení data a času Windows. Oba odkazy lze ovládat myší i klávesnicí. Kalendář proto neukazuje "
    L"duplicitní řádek Dnes. Je-li přichytávání zapnuté, při tažení se widget do vzdálenosti pěti pixelů "
    L"přichytí k hraně pracovní plochy. Při změně velikosti zůstane přichycený ke stejnému okraji nebo ke stejným dvěma okrajům.",
    L"\r\n\r\nWIDGET LAYOUT\r\nArrange in a grid preserves the approximate manual layout, snaps widget centres to the nearest grid points and removes overlaps. "
    L"A widget menu affects its monitor; the notification icon applies it to every monitor separately. Repeating the command keeps the layout stable. A Settings "
    L"double-click identifies a widget with a fast light-blue flash; an alarm flashes more slowly in red. Turning off Always on top sends the widget to the back. "
    L"In a calendar-and-clock panel, the upper link returns the calendar to today and the lower link opens the classic Windows Date and Time settings. Both links "
    L"work with the mouse and keyboard, and the calendar omits its duplicate Today row. When edge snapping is enabled, a "
    L"dragged widget within five pixels snaps to a work-area edge. When resized, it remains attached to the same edge or pair of edges.",
    L"\r\n\r\nWIDGET-ANORDNUNG\r\nIm Raster anordnen behält die ungefähre manuelle Anordnung bei, richtet die Mittelpunkte am nächsten Rasterpunkt aus und beseitigt "
    L"Überlappungen. Das Widget-Menü wirkt auf seinen Monitor, das Symbol auf alle Monitore einzeln. Wiederholen ändert die Anordnung nicht. Die Kennzeichnung blinkt "
    L"schnell hellblau, der Alarm langsamer rot. Das Abschalten von Immer im Vordergrund schickt das Widget nach hinten. Im Kalender-Uhr-Panel ist das obere Datum ein "
    L"Link zum heutigen Tag, der untere Link öffnet die klassischen Windows-Einstellungen für Datum und Uhrzeit. Beide Links lassen sich mit Maus und Tastatur bedienen; "
    L"der Kalender lässt daher seine doppelte Heute-Zeile weg. Wenn das Einrasten aktiviert ist, rastet ein Widget beim Ziehen innerhalb "
    L"von fünf Pixeln am Rand der Arbeitsfläche ein. Beim Ändern der Größe bleibt es am selben Rand oder an demselben Randpaar angeheftet.",
    L"\r\n\r\nDISPOSITION\r\nAligner sur une grille conserve leur disposition manuelle approximative, aligne leurs centres sur la grille la plus proche et supprime les "
    L"chevauchements. Le menu du widget agit sur son écran, l’icône sur chaque écran séparément. La commande répétée reste stable. L’identification clignote rapidement en "
    L"bleu clair, l’alarme plus lentement en rouge. Désactiver Toujours visible envoie le widget à l’arrière-plan. Dans le panneau calendrier-horloge, la date supérieure "
    L"est un lien vers aujourd’hui et le lien inférieur ouvre les paramètres classiques Date et heure de Windows. Les deux liens fonctionnent à la souris et au clavier ; "
    L"le calendrier omet donc sa ligne Aujourd’hui en double. Lorsque l’accrochage est activé, le widget déplacé s’accroche au bord "
    L"de la zone de travail à moins de cinq pixels. Lors du redimensionnement, il reste accroché au même bord ou à la même paire de bords.",
    L"\r\n\r\nDISTRIBUCIÓN\r\nAlinear en cuadrícula conserva la distribución manual aproximada, ajusta sus centros a la cuadrícula más cercana y elimina "
    L"superposiciones. El menú del widget actúa en su monitor; el icono, en cada monitor por separado. Repetir no cambia la distribución. La identificación parpadea "
    L"rápido en azul claro y la alarma más despacio en rojo. Desactivar Siempre visible envía el widget al fondo. En el panel de calendario y reloj, la fecha "
    L"superior es un enlace a hoy y el enlace inferior abre la configuración clásica de Fecha y hora de Windows. Ambos enlaces funcionan con el ratón y el teclado; "
    L"por ello el calendario omite su fila Hoy duplicada. Con el ajuste activado, el widget se acopla al borde del área de "
    L"trabajo al arrastrarlo a menos de cinco píxeles. Al cambiar de tamaño, permanece acoplado al mismo borde o al mismo par de bordes.",
    L"\r\n\r\nDISPOSIZIONE\r\nDisponi in griglia conserva la disposizione manuale approssimativa, allinea i centri alla griglia più vicina ed elimina le sovrapposizioni. "
    L"Il menu del widget agisce sul suo monitor, l’icona su ogni monitor separatamente. Ripetere il comando non cambia la disposizione. L’identificazione lampeggia rapidamente "
    L"in azzurro, la sveglia più lentamente in rosso. Disattivando Sempre in primo piano il widget viene mandato dietro. Nel pannello calendario-orologio, la data "
    L"superiore è un collegamento a oggi e quello inferiore apre le impostazioni classiche Data e ora di Windows. Entrambi funzionano con mouse e tastiera; il calendario "
    L"omette quindi la riga Oggi duplicata. Se l’aggancio è attivo, durante il trascinamento il widget si aggancia al "
    L"bordo dell’area di lavoro entro cinque pixel. Quando viene ridimensionato, resta agganciato allo stesso bordo o alla stessa coppia di bordi.",
    L"\r\n\r\nUKŁAD WIDŻETÓW\r\nUłóż w siatce zachowuje przybliżony układ ręczny, przyciąga środki widżetów do najbliższych punktów siatki i usuwa "
    L"nakładanie. Menu widżetu działa na jego monitorze, a ikona na każdym monitorze osobno. Powtórzenie nie zmienia układu. Identyfikacja miga szybko "
    L"jasnoniebiesko, alarm wolniej na czerwono. Wyłączenie Zawsze na wierzchu wysyła widżet do tyłu. W panelu kalendarza z zegarem górna data jest odsyłaczem do "
    L"dzisiejszego dnia, a dolny odsyłacz otwiera klasyczne ustawienia daty i godziny systemu Windows. Oba działają za pomocą myszy i klawiatury; dlatego kalendarz "
    L"pomija powielony wiersz Dzisiaj. Po włączeniu przyciągania widżet przeciągnięty na odległość najwyżej pięciu pikseli "
    L"przyciąga się do krawędzi obszaru roboczego. Po zmianie rozmiaru pozostaje przyciągnięty do tej samej krawędzi lub pary krawędzi.",
    L"\r\n\r\nROZLOŽENIE WIDGETOV\r\nZarovnať do mriežky zachová približné ručné rozmiestnenie, pritiahne stredy widgetov k najbližším bodom mriežky a "
    L"odstráni prekrývanie. Ponuka widgetu upraví jeho monitor, ikona každý monitor samostatne. Opakovanie rozloženie nemení. Identifikácia bliká rýchlo "
    L"svetlomodro, budík pomalšie načerveno. Vypnutie Vždy navrchu pošle widget dozadu. V paneli s kalendárom a hodinami je horný dátum odkazom na dnešok; "
    L"spodný odkaz otvorí klasické nastavenie dátumu a času Windows. Oba odkazy možno ovládať myšou aj klávesnicou; kalendár preto nezobrazuje duplicitný riadok "
    L"Dnes. Ak je prichytávanie zapnuté, pri ťahaní sa widget vo vzdialenosti najviac piatich pixelov "
    L"prichytí k okraju pracovnej plochy. Pri zmene veľkosti zostane prichytený k rovnakému okraju alebo k rovnakej dvojici okrajov.",
    L"\r\n\r\nWIDGET LAYOUT\r\nArrange in a grid preserves the approximate manual layout, snaps widget centres to the nearest grid points and removes overlaps. "
    L"A widget menu affects its monitor; the notification icon applies it to every monitor separately. Repeating the command keeps the layout stable. A Settings "
    L"double-click identifies a widget with a fast light-blue flash; an alarm flashes more slowly in red. Turning off Always on top sends the widget to the back. "
    L"In a calendar-and-clock panel, the upper link returns the calendar to today and the lower link opens the classic Windows Date and Time settings. Both links "
    L"work with the mouse and keyboard, and the calendar omits its duplicate Today row. When edge snapping is enabled, a "
    L"dragged widget within five pixels snaps to a work-area edge. When resized, it remains attached to the same edge or pair of edges.",
    L"\r\n\r\nWIDGET LAYOUT\r\nArrange in a grid preserves the approximate manual layout, snaps widget centres to the nearest grid points and removes overlaps. "
    L"A widget menu affects its monitor; the notification icon applies it to every monitor separately. Repeating the command keeps the layout stable. A Settings "
    L"double-click identifies a widget with a fast light-blue flash; an alarm flashes more slowly in red. Turning off Always on top sends the widget to the back. "
    L"In a calendar-and-clock panel, the upper link returns the calendar to today and the lower link opens the classic Windows Date and Time settings. Both links "
    L"work with the mouse and keyboard, and the calendar omits its duplicate Today row. When edge snapping is enabled, a "
    L"dragged widget within five pixels snaps to a work-area edge. When resized, it remains attached to the same edge or pair of edges.",
    L"\r\n\r\nDISPOSIÇÃO\r\nQuando o ajuste está ativado, os widgets prendem-se às margens da área de trabalho a cinco píxeis e permanecem presos ao redimensionar. Dispor "
    L"numa grelha move os outros widgets para posições próximas sem sobreposição, mantendo o widget de referência no lugar. Os relógios de monitor são ignorados. No painel "
    L"com calendário e relógio, a ligação superior volta a hoje e a inferior abre as definições clássicas de Data e Hora do Windows; ambas funcionam com rato e teclado.",
    L"\r\n\r\nPLASSERING\r\nNår kantfesting er aktivert, festes widgeter til kanten av arbeidsområdet innen fem piksler og forblir festet ved størrelsesendring. Ordne i et "
    L"rutenett flytter de andre widgetene til nærliggende plasser uten overlapping, mens referansewidgeten blir stående. Skjermklokker ignoreres. I kalender- og klokke-panelet "
    L"går den øvre lenken til i dag, og den nedre åpner de klassiske innstillingene for dato og klokkeslett i Windows; begge virker med mus og tastatur.",
    L"\r\n\r\nPLACERING\r\nNär kantfästning är aktiverad fäster widgetar vid arbetsytans kanter inom fem bildpunkter och förblir fästa när storleken ändras. Ordna i "
    L"rutnät flyttar de andra widgetarna till närliggande platser utan överlappning medan referenswidgeten står kvar. Skärmklockor ignoreras. I kalender- och klockpanelen "
    L"går den övre länken till i dag och den nedre öppnar Windows klassiska inställningar för datum och tid; båda fungerar med mus och tangentbord.",
    L"\r\n\r\nASETTELU\r\nKun reunakiinnitys on käytössä, pienoisohjelmat tarttuvat työalueen reunoihin viiden kuvapisteen etäisyydellä ja pysyvät kiinni koon muuttuessa. Järjestä "
    L"ruudukkoon siirtää muut pienoisohjelmat läheisiin, päällekkäisyyksiä välttäviin paikkoihin ja pitää viiteohjelman paikallaan. Näyttökellot ohitetaan. Kalenteri- ja kellopaneelin "
    L"ylälinkki palauttaa tämän päivän ja alalinkki avaa Windowsin perinteiset päivämäärä- ja aika-asetukset; molempia voi käyttää hiirellä ja näppäimistöllä.",
    L"\r\n\r\nPLACERING\r\nNår kantfastgørelse er slået til, fastgøres widgets til arbejdsområdets kanter inden for fem pixel og forbliver fastgjort ved størrelsesændring. "
    L"Arranger i gitter flytter de øvrige widgets til nærliggende pladser uden overlapning og lader referencewidgeten blive stående. Skærmure ignoreres. I kalender- og urpanelet "
    L"går det øverste link til i dag, og det nederste åbner Windows' klassiske indstillinger for dato og klokkeslæt; begge virker med mus og tastatur.",
    L"\r\n\r\nUPPRÖÐUN\r\nÞegar festing við brúnir er virk festast græjur við brúnir vinnusvæðisins innan fimm mynddíla og haldast fastar þegar stærð "
    L"breytist. Raða á hnitanet færir aðrar græjur á nálæga staði án skörunar en heldur viðmiðunargræjunni kyrrri. Skjáklukkur eru hunsaðar. Í dagatals- og klukkuspjaldinu "
    L"fer efri tengillinn á daginn í dag og sá neðri opnar hefðbundnar dagsetningar- og tímastillingar Windows; báðir virka með mús og lyklaborði.",
    L"\r\n\r\nDÜZEN\r\nKenar yapışması etkinleştirildiğinde araçlar çalışma alanının kenarlarına beş piksel içinde yapışır ve boyut değişirken yapışık kalır. "
    L"Izgarada düzenle, başvuru aracını yerinde tutarak diğer araçları çakışmayan yakın konumlara taşır. Monitör saatleri hesaba katılmaz. Takvim ve saat panelinde üst "
    L"bağlantı bugüne döner, alt bağlantı Windows'un klasik Tarih ve Saat ayarlarını açar; ikisi de fare ve klavyeyle çalışır."
};

const wchar_t* HELP_STORAGE_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nVZHLED A ÚLOŽIŠTĚ\r\nZměny vzhledu se ukazují ihned v živém náhledu; Zrušit vrátí nepoužitý vzhled a Výchozí vzhled obnoví výchozí hodnoty daného typu. Digitální "
    L"hodiny nabízejí písmo, vyhlazování, barvy, neprůhlednost, odsazení, šířku rámečku a průhledné pozadí. Digitální hodiny, kalendář a panel mají stejné čtyři styly "
    L"rámečku; u jednoduchého rámečku lze zvolit jeho barvu. Panel má samostatná písma horního řádku, času a spodního řádku, úvodní nulu a čtyři velikosti "
    L"ciferníku. Motivy a vyhlazování lze nastavit pro aplikaci i widget; písmo nativního kalendáře lze měnit jen při zakázaných motivech. Dialogy písem zobrazují "
    L"jen použitelné volby a skrývají náhled a efekty; velikost je dostupná "
    L"pouze pro digitální texty a texty panelu. Nastavení lze exportovat do XML a importovat přímo do stavu aplikace. Automatické XML je v "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Po úspěšném zápisu XML se odstraní větev HKCU\\SOFTWARE\\FortSoft\\CalClock; při ukládání do registru se automatické XML odstraní.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live preview; Cancel restores unapplied appearance and Default appearance restores the defaults for "
    L"that widget type. Digital clocks provide font, smoothing, colours, opacity, padding, border width and a transparent background. Digital clocks, calendars and panels share four border "
    L"styles; the single-line border has a selectable colour. The panel has separate fonts for its top row, time and bottom row, a leading zero and four clock-face sizes. Themes and font "
    L"smoothing can be set for the application and each widget; the native calendar font is selectable only when themes are disabled. Font dialogs show only applicable choices and hide "
    L"the preview and effects; size is available only for digital and panel text. Settings can be exported to XML and imported directly into application "
    L"state. Automatic XML is %AppData%\\FortSoft\\CalClock\\settings.xml. After writing XML, HKCU\\SOFTWARE\\FortSoft\\CalClock is removed; registry storage removes the automatic XML.",
    L"\r\n\r\nDARSTELLUNG UND SPEICHERUNG\r\nDarstellungsänderungen erscheinen sofort in der Vorschau; Abbrechen stellt nicht angewandte Werte wieder her, Standarddarstellung die Vorgaben "
    L"des Widget-Typs. Digitaluhren bieten Schrift, Glättung, Farben, Deckkraft, Innenabstand, Rahmenbreite und transparenten Hintergrund. Digitaluhren, Kalender und Panel verwenden dieselben "
    L"vier Rahmenarten; für den einfachen Rahmen ist die Farbe wählbar. Das Panel besitzt getrennte Schriften für obere Zeile, Zeit und untere Zeile, eine führende Null und vier "
    L"Zifferblattgrößen. Designs und Schriftglättung gelten wahlweise für Anwendung oder Widget; die native Kalenderschrift ist nur bei deaktivierten Designs wählbar. "
    L"Schriftdialoge zeigen nur anwendbare Optionen und blenden Vorschau und Effekte "
    L"aus; die Größe ist nur für Digital- und Paneltext verfügbar. XML-Export und -Import wirken direkt auf den Anwendungszustand. Automatisches "
    L"XML liegt in %AppData%\\FortSoft\\CalClock\\settings.xml; XML-Speicherung entfernt HKCU\\SOFTWARE\\FortSoft\\CalClock, Registrierungsspeicherung entfernt das automatische XML.",
    L"\r\n\r\nAPPARENCE ET STOCKAGE\r\nLes changements d’apparence sont prévisualisés immédiatement ; Annuler restaure les valeurs non appliquées et Apparence par défaut celles du type "
    L"de widget. Les horloges numériques proposent police, lissage, couleurs, opacité, marge, largeur de bordure et fond transparent. Horloges numériques, calendriers et panneaux partagent "
    L"quatre styles de bordure ; la couleur de la bordure simple est sélectionnable. Le panneau possède des polices distinctes pour les lignes supérieure, horaire et inférieure, un zéro "
    L"initial et quatre tailles de cadran. Thèmes et lissage se règlent pour l’application et le widget ; la police du calendrier natif n’est sélectionnable que si les thèmes sont "
    L"désactivés. Les boîtes de dialogue de police n’affichent que les "
    L"choix applicables et masquent aperçu et effets ; la taille n’est disponible que pour les textes numériques et du panneau. L’export et l’import XML agissent directement "
    L"sur l’état. Le XML automatique est %AppData%\\FortSoft\\CalClock\\settings.xml ; son écriture retire HKCU\\SOFTWARE\\FortSoft\\CalClock, tandis que le registre retire ce XML.",
    L"\r\n\r\nAPARIENCIA Y ALMACENAMIENTO\r\nLos cambios de apariencia se previsualizan al instante; Cancelar restaura los no aplicados y Apariencia predeterminada los valores del "
    L"tipo de widget. Los relojes digitales ofrecen fuente, suavizado, colores, opacidad, relleno, ancho de borde y fondo transparente. Los relojes digitales, calendarios y paneles comparten "
    L"cuatro estilos de borde; el color del borde simple es seleccionable. El panel tiene fuentes separadas para la línea superior, la hora y la inferior, cero inicial y cuatro tamaños de "
    L"esfera. Temas y suavizado se configuran para la aplicación y para cada widget; la fuente del calendario nativo solo se elige con temas desactivados. Los diálogos de fuente "
    L"muestran solo las opciones aplicables y ocultan la vista "
    L"previa y los efectos; el tamaño solo está disponible para textos digitales y del panel. La exportación e importación XML actúan directamente sobre el estado. El "
    L"XML automático es %AppData%\\FortSoft\\CalClock\\settings.xml; al escribirlo se elimina HKCU\\SOFTWARE\\FortSoft\\CalClock y al usar el registro se elimina el XML automático.",
    L"\r\n\r\nASPETTO E ARCHIVIAZIONE\r\nLe modifiche all’aspetto sono mostrate subito nell’anteprima; Annulla ripristina quelle non applicate e Aspetto predefinito i valori del "
    L"tipo di widget. Gli orologi digitali offrono carattere, antialiasing, colori, opacità, margine, larghezza del bordo e sfondo trasparente. Orologi digitali, calendari e pannelli condividono "
    L"quattro stili di bordo; il colore del bordo semplice è selezionabile. Il pannello ha caratteri separati per riga superiore, ora e riga inferiore, zero iniziale e quattro "
    L"dimensioni del quadrante. Temi e antialiasing si impostano per applicazione e widget; il carattere del calendario nativo è selezionabile solo con temi disattivati. Le finestre "
    L"dei caratteri mostrano solo le opzioni applicabili e nascondono "
    L"anteprima ed effetti; la dimensione è disponibile solo per testi digitali e del pannello. Esportazione e importazione XML agiscono direttamente "
    L"sullo stato. L’XML automatico è %AppData%\\FortSoft\\CalClock\\settings.xml; scriverlo rimuove HKCU\\SOFTWARE\\FortSoft\\CalClock, mentre il registro rimuove l’XML automatico.",
    L"\r\n\r\nWYGLĄD I ZAPIS\r\nZmiany wyglądu są od razu widoczne w podglądzie; Anuluj przywraca niezastosowane wartości, a Wygląd domyślny wartości danego typu "
    L"widżetu. Zegary cyfrowe oferują czcionkę, wygładzanie, kolory, krycie, odstęp, szerokość ramki i przezroczyste tło. Zegary cyfrowe, kalendarze i panele mają te same cztery style "
    L"ramki; kolor prostej ramki można wybrać. Panel ma osobne czcionki górnego wiersza, czasu i dolnego wiersza, zero wiodące oraz cztery rozmiary tarczy. Motywy i "
    L"wygładzanie ustawia się dla aplikacji i widżetu; czcionkę natywnego kalendarza można wybrać tylko przy wyłączonych motywach. Okna wyboru czcionki pokazują tylko "
    L"używane opcje i ukrywają podgląd oraz efekty; rozmiar "
    L"jest dostępny tylko dla tekstów cyfrowych i panelu. Eksport i import XML działają bezpośrednio na stan. "
    L"Automatyczny XML to %AppData%\\FortSoft\\CalClock\\settings.xml; zapis XML usuwa HKCU\\SOFTWARE\\FortSoft\\CalClock, a zapis w rejestrze usuwa automatyczny XML.",
    L"\r\n\r\nVZHĽAD A UKLADANIE\r\nZmeny vzhľadu sa ihneď ukazujú v náhľade; Zrušiť vráti nepoužité hodnoty a Predvolený vzhľad hodnoty daného typu widgetu. "
    L"Digitálne hodiny ponúkajú písmo, vyhladzovanie, farby, nepriehľadnosť, odsadenie, šírku rámčeka aj priehľadné pozadie. Digitálne hodiny, kalendár a panel majú rovnaké štyri štýly "
    L"rámčeka; pri jednoduchom rámčeku možno zvoliť farbu. Panel má samostatné písma horného riadka, času a spodného riadka, úvodnú nulu a štyri veľkosti ciferníka. "
    L"Motívy a vyhladzovanie sa nastavujú pre aplikáciu aj widget; písmo natívneho kalendára možno vybrať iba pri zakázaných motívoch. Dialógy písiem zobrazujú len "
    L"použiteľné voľby a skrývajú náhľad a efekty; veľkosť je dostupná "
    L"iba pre digitálne texty a texty panela. Export a import XML pôsobia priamo na stav. Automatické XML "
    L"je %AppData%\\FortSoft\\CalClock\\settings.xml; zápis XML odstráni HKCU\\SOFTWARE\\FortSoft\\CalClock a ukladanie do registra odstráni automatické XML.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live preview; Cancel restores unapplied appearance and Default appearance restores the defaults for "
    L"that widget type. Digital clocks provide font, smoothing, colours, opacity, padding, border width and a transparent background. Digital clocks, calendars and panels share four border "
    L"styles; the single-line border has a selectable colour. The panel has separate fonts for its top row, time and bottom row, a leading zero and four clock-face sizes. Themes and font "
    L"smoothing can be set for the application and each widget; the native calendar font is selectable only when themes are disabled. Font dialogs show only applicable choices and hide "
    L"the preview and effects; size is available only for digital and panel text. Settings can be exported to XML and imported directly into application "
    L"state. Automatic XML is %AppData%\\FortSoft\\CalClock\\settings.xml. After writing XML, HKCU\\SOFTWARE\\FortSoft\\CalClock is removed; registry storage removes the automatic XML.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live preview; Cancel restores unapplied appearance and Default appearance restores the defaults for "
    L"that widget type. Digital clocks provide font, smoothing, colours, opacity, padding, border width and a transparent background. Digital clocks, calendars and panels share four border "
    L"styles; the single-line border has a selectable colour. The panel has separate fonts for its top row, time and bottom row, a leading zero and four clock-face sizes. Themes and font "
    L"smoothing can be set for the application and each widget; the native calendar font is selectable only when themes are disabled. Font dialogs show only applicable choices and hide "
    L"the preview and effects; size is available only for digital and panel text. Settings can be exported to XML and imported directly into application "
    L"state. Automatic XML is %AppData%\\FortSoft\\CalClock\\settings.xml. After writing XML, HKCU\\SOFTWARE\\FortSoft\\CalClock is removed; registry storage removes the automatic XML.",
    L"\r\n\r\nARMAZENAMENTO\r\nAs definições são guardadas no registo em HKCU\\SOFTWARE\\FortSoft\\CalClock ou num XML em "
    L"AppData\\Roaming\\FortSoft\\CalClock. Relógios digitais, calendários e painéis partilham quatro estilos de moldura; a cor da moldura simples pode ser escolhida. Os diálogos de tipo de "
    L"letra mostram apenas as opções aplicáveis e ocultam a pré-visualização e os efeitos. A mudança de "
    L"armazenamento remove apenas os dados CalClock anteriores. Importar XML carrega as "
    L"definições na aplicação sem alterar ou apagar o armazenamento atual; Guardar ou Aplicar grava-as depois no destino escolhido.",
    L"\r\n\r\nLAGRING\r\nInnstillinger lagres i registeret under HKCU\\SOFTWARE\\FortSoft\\CalClock eller som XML i AppData\\Roaming\\FortSoft\\CalClock. "
    L"Digitale klokker, kalendere og paneler har fire felles kantstiler; fargen på den enkle kanten kan velges. Skriftdialoger viser bare aktuelle valg og skjuler forhåndsvisning og effekter. "
    L"Bytte av lagring fjerner bare tidligere CalClock-data. Import av XML "
    L"laster inn innstillinger uten å endre eller slette gjeldende lagring; Lagre eller Bruk skriver dem senere til valgt mål.",
    L"\r\n\r\nLAGRING\r\nInställningar sparas i registret under HKCU\\SOFTWARE\\FortSoft\\CalClock eller som XML i AppData\\Roaming\\FortSoft\\CalClock. "
    L"Digitala klockor, kalendrar och paneler har fyra gemensamma kantstilar; färgen på den enkla kanten kan väljas. Teckensnittsdialoger visar bara tillämpliga val och döljer förhandsvisning och "
    L"effekter. Byte av lagring tar bara bort tidigare CalClock-data. Import av XML "
    L"läser in inställningar utan att ändra eller radera aktuell lagring; Spara eller Verkställ skriver dem sedan till valt mål.",
    L"\r\n\r\nTALLENNUS\r\nAsetukset tallennetaan rekisteriin kohtaan HKCU\\SOFTWARE\\FortSoft\\CalClock tai XML-tiedostoon kansiossa AppData\\Roaming\\FortSoft\\CalClock. "
    L"Digitaalikelloilla, kalentereilla ja paneeleilla on neljä yhteistä reunatyyliä; yksinkertaisen reunan väri voidaan valita. Fonttivalinta näyttää vain käytettävät vaihtoehdot ja piilottaa "
    L"esikatselun ja tehosteet. Tallennustavan vaihto poistaa vain aiemmat CalClock-tiedot. "
    L"XML-tuonti lataa asetukset muuttamatta tai poistamatta nykyistä tallennusta; Tallenna tai Käytä kirjoittaa ne myöhemmin valittuun kohteeseen.",
    L"\r\n\r\nLAGRING\r\nIndstillinger gemmes i registreringsdatabasen under HKCU\\SOFTWARE\\FortSoft\\CalClock eller som XML i AppData\\Roaming\\FortSoft\\CalClock. "
    L"Digitale ure, kalendere og paneler har fire fælles kanttyper; farven på den enkle kant kan vælges. Skrifttypedialoger viser kun relevante valg og skjuler forhåndsvisning og effekter. Skift "
    L"af lager fjerner kun tidligere CalClock-data. Import af XML indlæser "
    L"indstillinger uden at ændre eller slette det aktuelle lager; Gem eller Anvend skriver dem derefter til det valgte mål.",
    L"\r\n\r\nGEYMSLA\r\nStillingar eru vistaðar í skrásetningu undir HKCU\\SOFTWARE\\FortSoft\\CalClock eða sem XML í AppData\\Roaming\\FortSoft\\CalClock. "
    L"Stafrænar klukkur, dagatöl og spjöld hafa fjórar sameiginlegar rammagerðir; velja má lit einfalda rammans. Leturgluggar sýna aðeins viðeigandi val og fela forskoðun og áhrif. Skipti um "
    L"geymslu fjarlægja aðeins eldri CalClock-gögn. Innflutningur "
    L"XML hleður stillingum án þess að breyta eða eyða núverandi geymslu; Vista eða Nota skrifar þær síðar á valinn stað.",
    L"\r\n\r\nDEPOLAMA\r\nAyarlar HKCU\\SOFTWARE\\FortSoft\\CalClock altındaki kayıt defterinde veya AppData\\Roaming\\FortSoft\\CalClock içindeki XML dosyasında saklanır. "
    L"Dijital saatler, takvimler ve paneller aynı dört kenarlık stilini kullanır; basit kenarlığın rengi seçilebilir. Yazı tipi iletişim kutuları yalnızca uygulanabilir seçenekleri gösterir, önizleme "
    L"ve efektleri gizler. Depolamayı değiştirmek yalnızca önceki CalClock verilerini kaldırır. "
    L"XML içe aktarma mevcut depolamayı değiştirmeden veya silmeden ayarları yükler; Kaydet ya da Uygula bunları seçili hedefe yazar."
};

const wchar_t* HELP_SETTINGS_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nNASTAVENÍ A NABÍDKY\r\nUložit použije změny a zavře Nastavení, Použít je provede bez zavření a Zrušit zahodí dosud nepoužité změny včetně živého náhledu vzhledu. Enter "
    L"aktivuje Uložit a Esc Zrušit. Na malé pracovní ploše dostane formulář potřebné posuvníky. Jazyk, písmo, vyhlazování, motivy, úložiště, spouštění s Windows a přichytávání jsou "
    L"globální a nastavují se na kartě Aplikace. Při prvním spuštění se jazyk volí podle uživatelského jazyka Windows, neznámý jazyk se nahradí angličtinou (USA); jazyk, "
    L"vyhlazování a motivy widgetu platí jen pro něj. Změna jazyka se po použití promítne i do otevřeného formuláře.\r\n\r\nNabídka widgetu obsahuje příslušné volby viditelnosti, "
    L"režimu navrchu, sekund, velikosti a kopírování data a dále Zarovnat do mřížky, Nastavení, Nápovědu, O programu a Konec. Nabídka ikony uvádí widgety s pořadovými "
    L"čísly a příkazy Zobrazit vše, Skrýt vše a Ztlumit vše. Samostatně oddělený příkaz Zarovnat do mřížky následuje za nimi. Zobrazení či obnovení přenese widgety "
    L"dopředu bez změny Vždy navrchu. Další spuštění aktivuje běžící instanci a v případě potřeby "
    L"obnoví naposledy skryté widgety. Dostupné rozměry ciferníku a možnost sekundové ručičky vycházejí ze systémového ClockWndMain; nedostupné Sekundy jsou šedivé, ale "
    L"uložená volba se zachová pro podporovanou velikost. Budík a signál lze zapnout přímo v nabídce widgetu; položka Budík "
    L"ukazuje čas a při částečném týdnu také aktivní dny. Zaškrtnutí Ztlumit v nabídce widgetu odpovídá volbě Ztlumeno na kartě Obecné. Ztlumit vše v nabídce ikony "
    L"ztlumí všechny widgety a při dalším přepnutí obnoví jen ty, které samo ztlumilo. Totéž globální přepnutí provede klávesa M na kterémkoli widgetu. Zapnutí budíku "
    L"bez vybraného dne otevře kartu Budík daného widgetu. Po restartu Průzkumníka Windows se ikona v oznamovací oblasti automaticky obnoví.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nSave applies changes and closes Settings, Apply performs them without closing, and Cancel discards changes not yet applied, including the live appearance "
    L"preview. Enter activates Save and Esc activates Cancel. The dialog gains the required scroll bars on a small work area. Application language, font, smoothing, themes, storage, Windows "
    L"startup and edge snapping are global and are configured on the Application tab. On first launch, the application language follows the Windows user-interface language, with US English "
    L"as the fallback; widget language, smoothing and themes affect that widget only. An applied language change also updates the open dialog.\r\n\r\nA widget menu contains the "
    L"applicable visibility, always-on-top, seconds, size and date-copy choices, followed by Arrange in a grid, Settings, Help, About and Exit. The notification-icon menu lists "
    L"numbered widgets and provides Show all, Hide all and Mute all. The separately grouped Arrange in a grid command follows. Showing or restoring widgets brings them forward "
    L"without changing Always on top. Starting CalClock again activates the "
    L"running instance and restores the most recently hidden widgets when needed. Available face sizes and second-hand support come from the system ClockWndMain control; Seconds is "
    L"disabled when unavailable, but its saved choice is retained for a supported size. Alarm and Signal can be toggled directly in a widget "
    L"menu; Alarm shows its time and, for a partial week, its active weekdays. Checked Mute in a widget menu corresponds to Muted on the General tab. Mute all in the "
    L"notification-icon menu mutes every widget and, when toggled again, restores only those it muted. Pressing M on any widget performs the same global toggle. Enabling an "
    L"alarm with no weekday selected opens that widget’s Alarm tab. The notification icon is restored automatically after Windows Explorer restarts.",
    L"\r\n\r\nEINSTELLUNGEN UND MENÜS\r\nSpeichern wendet Änderungen an und schließt die Einstellungen, Anwenden übernimmt sie ohne Schließen, und Abbrechen verwirft noch nicht angewandte "
    L"Änderungen einschließlich der Live-Vorschau. Eingabe aktiviert Speichern, Esc Abbrechen. Auf einer kleinen Arbeitsfläche erscheinen die erforderlichen Bildlaufleisten. "
    L"Anwendungssprache, Schrift, Glättung, Designs, Speicher, Windows-Start und Randeinrasten sind global und werden auf der Registerkarte Anwendung eingestellt. Beim ersten Start folgt "
    L"die Sprache der Windows-Anzeigesprache; sonst wird US-Englisch verwendet. Widget-Sprache, Glättung und Designs gelten nur für dieses Widget. Eine angewandte Sprachänderung "
    L"aktualisiert auch den offenen Dialog.\r\n\r\nDas Widget-Menü enthält die zutreffenden Optionen für Sichtbarkeit, Vordergrund, Sekunden, Größe und Datumskopie sowie Im Raster anordnen, "
    L"Einstellungen, Hilfe, Info und Beenden. Das Infobereichsmenü listet nummerierte Widgets und bietet Alle anzeigen, Alle ausblenden und Alles stummschalten. Im Raster anordnen "
    L"folgt als getrennte Gruppe. Anzeigen oder Wiederherstellen "
    L"bringt Widgets nach vorn, ohne Immer im Vordergrund zu ändern. Ein erneuter Start aktiviert die laufende Instanz und stellt bei Bedarf die zuletzt verborgenen Widgets wieder her. "
    L"Verfügbare Zifferblattgrößen und Sekundenzeiger hängen vom systemeigenen ClockWndMain ab; nicht verfügbare Sekunden sind deaktiviert, die gespeicherte Wahl bleibt jedoch für eine "
    L"unterstützte Größe erhalten. Wecker und Zeitzeichen lassen sich direkt im Widget-Menü schalten; Wecker zeigt Zeit und bei einer Teilwoche die "
    L"aktiven Tage. Stummschalten im Widget-Menü entspricht Stummgeschaltet unter Allgemein. Alles stummschalten im Infobereich stellt beim nächsten Umschalten nur die von ihm "
    L"stummgeschalteten Widgets wieder her. M auf einem Widget schaltet denselben Gesamtzustand um. Wird ein Wecker ohne ausgewählten Wochentag aktiviert, öffnet sich "
    L"die Registerkarte Wecker dieses Widgets. Nach einem Neustart des Windows-Explorers wird das Infobereichssymbol automatisch wiederhergestellt.",
    L"\r\n\r\nPARAMÈTRES ET MENUS\r\nEnregistrer applique les changements et ferme Paramètres, Appliquer les effectue sans fermer, et Annuler abandonne ceux qui ne sont pas encore appliqués, "
    L"y compris l’aperçu d’apparence. Entrée active Enregistrer et Échap Annuler. Des barres de défilement apparaissent si l’espace de travail est petit. Langue, police, lissage, thèmes, "
    L"stockage, démarrage avec Windows et accrochage sont globaux et se règlent dans l’onglet Application. Au premier lancement, la langue suit celle de l’interface Windows, avec l’anglais "
    L"américain par défaut ; langue, lissage et thèmes du widget ne concernent que lui. Un changement de langue appliqué actualise aussi la fenêtre ouverte.\r\n\r\nLe menu d’un widget "
    L"contient les choix applicables de visibilité, premier plan, secondes, taille et copie de date, puis Aligner sur une grille, Paramètres, Aide, À propos et Quitter. Le menu de "
    L"notification liste les widgets numérotés et propose Tout afficher, Tout masquer et Couper tous les sons. Aligner sur une grille suit dans un groupe séparé. Afficher ou restaurer "
    L"les widgets les ramène devant sans modifier Toujours visible. Un "
    L"nouveau lancement active l’instance existante et restaure au besoin les derniers widgets masqués. Les tailles de cadran et la trotteuse disponibles viennent du contrôle système "
    L"ClockWndMain ; Secondes est désactivé si indisponible, mais le choix est conservé pour une taille compatible. Alarme et Signal se "
    L"commutent dans le menu du widget ; Alarme affiche l’heure et, pour une semaine partielle, les jours actifs. Couper le son dans le menu du widget correspond à Son coupé "
    L"dans Général. Tout couper rétablit ensuite uniquement les widgets qu’il a coupés. M sur un widget effectue la même bascule globale. Activer l’alarme sans jour "
    L"sélectionné ouvre l’onglet Alarme de ce widget. L’icône de notification est restaurée automatiquement après le redémarrage de l’Explorateur Windows.",
    L"\r\n\r\nCONFIGURACIÓN Y MENÚS\r\nGuardar aplica los cambios y cierra Configuración, Aplicar los realiza sin cerrar y Cancelar descarta los aún no aplicados, incluida la vista previa de "
    L"apariencia. Intro activa Guardar y Esc Cancelar. En un área de trabajo pequeña aparecen las barras de desplazamiento necesarias. Idioma, fuente, suavizado, temas, almacenamiento, "
    L"inicio con Windows y acoplamiento son globales y se configuran en la pestaña Aplicación. En el primer inicio, el idioma sigue al de la interfaz de Windows y usa inglés de EE. UU. "
    L"como alternativa; idioma, suavizado y temas del widget solo afectan a este. Un cambio de idioma aplicado también actualiza la ventana abierta.\r\n\r\nEl menú del widget contiene "
    L"las opciones aplicables de visibilidad, primer plano, segundos, tamaño y copia de fecha, además de Alinear en cuadrícula, Configuración, Ayuda, Acerca de y Salir. El menú del "
    L"icono muestra widgets numerados y ofrece Mostrar todo, Ocultar todo y Silenciar todo. Alinear en cuadrícula aparece después como grupo separado. Mostrar o restaurar lleva los "
    L"widgets al frente sin cambiar Siempre visible. Otra ejecución activa la "
    L"instancia existente y restaura cuando haga falta los últimos widgets ocultos. Los tamaños de esfera y la disponibilidad del segundero proceden del ClockWndMain del sistema; "
    L"Segundos aparece desactivado cuando no está disponible, pero la elección guardada se conserva para un tamaño compatible. Alarma y Señal se "
    L"conmutan en el menú del widget; Alarma muestra la hora y, para una semana parcial, los días activos. Silenciar en el menú del widget corresponde a Silenciado en General. "
    L"Silenciar todo restaura después solo los widgets que silenció. M sobre un widget realiza la misma conmutación global. Activar la alarma sin ningún día seleccionado "
    L"abre la pestaña Alarma de ese widget. El icono de notificación se restaura automáticamente después de reiniciar el Explorador de Windows.",
    L"\r\n\r\nIMPOSTAZIONI E MENU\r\nSalva applica le modifiche e chiude Impostazioni, Applica le esegue senza chiudere e Annulla scarta quelle non ancora applicate, compresa l’anteprima "
    L"dell’aspetto. Invio attiva Salva ed Esc Annulla. In un’area di lavoro piccola compaiono le barre di scorrimento necessarie. Lingua, carattere, antialiasing, temi, archivio, avvio "
    L"con Windows e aggancio sono globali e si configurano nella scheda Applicazione. Al primo avvio la lingua segue quella dell’interfaccia di Windows, con inglese USA come ripiego; "
    L"lingua, antialiasing e temi del widget valgono solo per esso. Una modifica della lingua applicata aggiorna anche la finestra aperta.\r\n\r\nIl menu del widget contiene le scelte "
    L"pertinenti per visibilità, primo piano, secondi, dimensione e copia della data, oltre a Disponi in griglia, Impostazioni, Guida, Informazioni ed Esci. Il menu dell’icona elenca "
    L"i widget numerati e offre Mostra tutto, Nascondi tutto e Disattiva tutto l'audio. Disponi in griglia segue come gruppo separato. Mostrare o ripristinare porta i widget davanti "
    L"senza cambiare Sempre in primo piano. Un nuovo avvio "
    L"attiva l’istanza esistente e, se necessario, ripristina gli ultimi widget nascosti. Dimensioni del quadrante e lancetta dei secondi disponibili dipendono dal ClockWndMain di "
    L"sistema; Secondi è disabilitato se non disponibile, ma la scelta viene conservata per una dimensione supportata. Sveglia e Segnale si "
    L"attivano dal menu del widget; Sveglia mostra l’ora e, per una settimana parziale, i giorni attivi. Disattiva audio nel menu del widget corrisponde ad Audio disattivato "
    L"in Generale. Disattiva tutto ripristina poi solo i widget che aveva disattivato. M su un widget esegue lo stesso comando globale. Attivare la sveglia senza "
    L"giorni selezionati apre la scheda Sveglia del widget. L’icona di notifica viene ripristinata automaticamente dopo il riavvio di Esplora file.",
    L"\r\n\r\nUSTAWIENIA I MENU\r\nZapisz stosuje zmiany i zamyka Ustawienia, Zastosuj wykonuje je bez zamykania, a Anuluj odrzuca jeszcze niezastosowane zmiany wraz z podglądem "
    L"wyglądu. Enter uruchamia Zapisz, a Esc Anuluj. Na małym obszarze roboczym pojawiają się potrzebne paski przewijania. Język, czcionka, wygładzanie, motywy, magazyn ustawień, "
    L"uruchamianie z Windows i przyciąganie są globalne i ustawia się je na karcie Aplikacja. Przy pierwszym uruchomieniu język wynika z języka interfejsu Windows, a nieznany "
    L"zastępuje angielski (USA); język, wygładzanie i motywy widżetu dotyczą tylko jego. Zastosowana zmiana języka aktualizuje również otwarte okno.\r\n\r\nMenu widżetu zawiera "
    L"odpowiednie opcje widoczności, położenia na wierzchu, sekund, rozmiaru i kopiowania daty oraz Ułóż w siatce, Ustawienia, Pomoc, O programie i Zakończ. Menu ikony "
    L"wyświetla numerowane widżety oraz Pokaż wszystkie, Ukryj wszystkie i Wycisz wszystko. Ułóż w siatce znajduje się dalej w oddzielnej grupie. Pokazanie lub przywrócenie "
    L"przenosi widżety do przodu bez zmiany Zawsze na wierzchu. Ponowne "
    L"uruchomienie aktywuje istniejącą instancję i w razie potrzeby przywraca ostatnio ukryte widżety. Dostępne rozmiary tarczy i sekundnik zależą od systemowego ClockWndMain; "
    L"niedostępna opcja Sekundy jest wyłączona, lecz zapisany wybór pozostaje dla obsługiwanego rozmiaru. Alarm i Sygnał "
    L"można przełączać w menu widżetu; Alarm pokazuje czas i, dla części tygodnia, aktywne dni. Wycisz w menu widżetu odpowiada opcji Wyciszony na karcie Ogólne. Wycisz "
    L"wszystko przywraca potem tylko widżety, które samo wyciszyło. M na widżecie wykonuje to samo przełączenie globalne. Włączenie alarmu bez wybranego dnia "
    L"otwiera kartę Alarm tego widżetu. Ikona obszaru powiadomień jest automatycznie przywracana po ponownym uruchomieniu Eksploratora Windows.",
    L"\r\n\r\nNASTAVENIA A PONUKY\r\nUložiť použije zmeny a zavrie Nastavenia, Použiť ich vykoná bez zatvorenia a Zrušiť zahodí doteraz nepoužité zmeny vrátane živého náhľadu vzhľadu. Enter "
    L"aktivuje Uložiť a Esc Zrušiť. Na malej pracovnej ploche dostane formulár potrebné posuvníky. Jazyk, písmo, vyhladzovanie, motívy, úložisko, spúšťanie s Windows a prichytávanie sú "
    L"globálne a nastavujú sa na karte Aplikácia. Pri prvom spustení sa jazyk volí podľa jazyka rozhrania Windows, neznámy jazyk sa nahradí angličtinou (USA); jazyk, vyhladzovanie a "
    L"motívy widgetu platia iba preň. Použitá zmena jazyka aktualizuje aj otvorené okno.\r\n\r\nPonuka widgetu obsahuje príslušné voľby viditeľnosti, režimu navrchu, sekúnd, veľkosti a "
    L"kopírovania dátumu a ďalej Zarovnať do mriežky, Nastavenia, Pomoc, O programe a Koniec. Ponuka ikony uvádza očíslované widgety a príkazy Zobraziť všetko, Skryť všetko "
    L"a Stlmiť všetko. Samostatne oddelený príkaz Zarovnať do mriežky nasleduje za nimi. Zobrazenie alebo obnovenie prenesie widgety dopredu bez zmeny Vždy navrchu. Ďalšie "
    L"spustenie aktivuje bežiacu inštanciu a podľa potreby obnoví naposledy skryté widgety. "
    L"Dostupné rozmery ciferníka a sekundová ručička vychádzajú zo systémového ClockWndMain; nedostupné Sekundy sú deaktivované, ale uložená voľba zostane pre podporovanú veľkosť. "
    L"Budík a Signál možno prepínať v ponuke widgetu; Budík ukazuje čas a pri čiastočnom týždni aj aktívne dni. Stlmiť v ponuke widgetu "
    L"zodpovedá voľbe Stlmené na karte Všeobecné. Stlmiť všetko potom obnoví iba widgety, ktoré samo stlmilo. Kláves M na widgete vykoná rovnaké globálne prepnutie. Zapnutie "
    L"budíka bez vybraného dňa otvorí kartu Budík daného widgetu. Ikona v oznamovacej oblasti sa po reštarte Prieskumníka Windows automaticky obnoví.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nSave applies changes and closes Settings, Apply performs them without closing, and Cancel discards changes not yet applied, including the live appearance "
    L"preview. Enter activates Save and Esc activates Cancel. The dialog gains the required scroll bars on a small work area. Application language, font, smoothing, themes, storage, Windows "
    L"startup and edge snapping are global and are configured on the Application tab. On first launch, the application language follows the Windows user-interface language, with US English "
    L"as the fallback; widget language, smoothing and themes affect that widget only. An applied language change also updates the open dialog.\r\n\r\nA widget menu contains the "
    L"applicable visibility, always-on-top, seconds, size and date-copy choices, followed by Arrange in a grid, Settings, Help, About and Exit. The notification-icon menu lists "
    L"numbered widgets and provides Show all, Hide all and Mute all. The separately grouped Arrange in a grid command follows. Showing or restoring widgets brings them forward "
    L"without changing Always on top. Starting CalClock again activates the "
    L"running instance and restores the most recently hidden widgets when needed. Available face sizes and second-hand support come from the system ClockWndMain control; Seconds is "
    L"disabled when unavailable, but its saved choice is retained for a supported size. Alarm and Signal can be toggled directly in a widget "
    L"menu; Alarm shows its time and, for a partial week, its active weekdays. Checked Mute in a widget menu corresponds to Muted on the General tab. Mute all in the "
    L"notification-icon menu mutes every widget and, when toggled again, restores only those it muted. Pressing M on any widget performs the same global toggle. Enabling an "
    L"alarm with no weekday selected opens that widget’s Alarm tab. The notification icon is restored automatically after Windows Explorer restarts.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nSave applies changes and closes Settings, Apply performs them without closing, and Cancel discards changes not yet applied, including the live appearance "
    L"preview. Enter activates Save and Esc activates Cancel. The dialog gains the required scroll bars on a small work area. Application language, font, smoothing, themes, storage, Windows "
    L"startup and edge snapping are global and are configured on the Application tab. On first launch, the application language follows the Windows user-interface language, with US English "
    L"as the fallback; widget language, smoothing and themes affect that widget only. An applied language change also updates the open dialog.\r\n\r\nA widget menu contains the "
    L"applicable visibility, always-on-top, seconds, size and date-copy choices, followed by Arrange in a grid, Settings, Help, About and Exit. The notification-icon menu lists "
    L"numbered widgets and provides Show all, Hide all and Mute all. The separately grouped Arrange in a grid command follows. Showing or restoring widgets brings them forward "
    L"without changing Always on top. Starting CalClock again activates the "
    L"running instance and restores the most recently hidden widgets when needed. Available face sizes and second-hand support come from the system ClockWndMain control; Seconds is "
    L"disabled when unavailable, but its saved choice is retained for a supported size. Alarm and Signal can be toggled directly in a widget "
    L"menu; Alarm shows its time and, for a partial week, its active weekdays. Checked Mute in a widget menu corresponds to Muted on the General tab. Mute all in the "
    L"notification-icon menu mutes every widget and, when toggled again, restores only those it muted. Pressing M on any widget performs the same global toggle. Enabling an "
    L"alarm with no weekday selected opens that widget’s Alarm tab. The notification icon is restored automatically after Windows Explorer restarts.",
    L"\r\n\r\nDEFINIÇÕES E MENUS\r\nGuardar aplica e fecha, Aplicar mantém a janela aberta e Cancelar repõe alterações ainda não aplicadas. Enter ativa Guardar e Esc "
    L"ativa Cancelar. O idioma, tipo de letra, suavização, temas, armazenamento, arranque com o Windows, ajuste às margens e origem da hora são globais; as opções "
    L"da aplicação são configuradas no separador Aplicação. No primeiro arranque, o idioma segue a interface do Windows, com inglês dos EUA como alternativa. "
    L"O idioma e outras opções de widget aplicam-se individualmente. No menu do ícone, Mostrar tudo e Ocultar tudo precedem Silenciar tudo; Dispor numa grelha surge num grupo "
    L"separado. Silenciar no menu do widget corresponde a Silenciado em Geral. Silenciar tudo repõe "
    L"depois apenas os widgets que silenciou. M num widget executa a mesma alternância global. Ativar o alarme sem nenhum dia selecionado abre o "
    L"separador Alarme desse widget. O ícone de notificação é restaurado automaticamente após reiniciar o Explorador do Windows.",
    L"\r\n\r\nINNSTILLINGER OG MENYER\r\nLagre bruker endringene og lukker, Bruk lar vinduet stå åpent, og Avbryt gjenoppretter endringer som ikke er brukt. Enter aktiverer "
    L"Lagre og Esc Avbryt. Programspråk, skrift, utjevning, temaer, lagring, oppstart med Windows, kantfesting og tidskilde er globale; programvalgene angis på fanen Program. "
    L"Ved første start følger språket Windows-grensesnittet, med amerikansk engelsk som reserve. Widgetspråk og andre widgetvalg gjelder enkeltvis. I ikonmenyen kommer Vis alle og "
    L"Skjul alle før Demp alle; Ordne i et rutenett står i en egen gruppe etter dem. Demp i widgetmenyen "
    L"tilsvarer Dempet på fanen Generelt. Demp alle gjenoppretter senere bare widgetene den dempet. M på en widget utfører samme globale veksling. Aktivering av "
    L"alarmen uten valgte ukedager åpner widgetens Alarm-fane. Varslingsikonet gjenopprettes automatisk etter at Windows Utforsker starter på nytt.",
    L"\r\n\r\nINSTÄLLNINGAR OCH MENYER\r\nSpara verkställer och stänger, Verkställ lämnar fönstret öppet och Avbryt återställer ändringar som ännu inte verkställts. Enter aktiverar "
    L"Spara och Esc Avbryt. Programspråk, teckensnitt, utjämning, teman, lagring, start med Windows, kantfästning och tidskälla är globala; programalternativen ställs in på "
    L"fliken Program. Vid första starten följer språket Windows gränssnittsspråk, med amerikansk engelska som reserv. Widgetspråk och andra widgetval gäller separat. I ikonmenyn "
    L"kommer Visa alla och Dölj alla före Tysta alla; Ordna i ett rutnät står i en egen grupp efter dem. Tysta i "
    L"widgetmenyn motsvarar Tyst på fliken Allmänt. Tysta alla återställer därefter bara de widgetar som kommandot tystade. M på en widget gör samma globala växling. Om "
    L"alarmet aktiveras utan valda veckodagar öppnas widgetens Alarm-flik. Meddelandeikonen återställs automatiskt när Utforskaren startas om.",
    L"\r\n\r\nASETUKSET JA VALIKOT\r\nTallenna ottaa muutokset käyttöön ja sulkee, Käytä pitää ikkunan avoinna ja Peruuta palauttaa käyttämättömät muutokset. Enter aktivoi "
    L"Tallenna-painikkeen ja Esc Peruuta-painikkeen. Sovelluksen kieli, fontti, pehmennys, teemat, tallennus, Windowsin mukana käynnistys, reunakiinnitys ja aikalähde ovat "
    L"yleisiä; sovellusasetukset määritetään Sovellus-välilehdellä. Ensimmäisellä käynnistyksellä kieli seuraa Windowsin käyttöliittymäkieltä, varalla on amerikanenglanti. "
    L"Pienoisohjelman kieli ja muut valinnat ovat yksilöllisiä. Kuvakevalikossa Näytä kaikki ja Piilota kaikki ovat ennen Mykistä kaikki -komentoa; Järjestä ruudukkoon on niiden "
    L"jälkeen omana ryhmänään. Pienoisohjelman Mykistä vastaa Yleiset-välilehden Mykistetty-valintaa. Mykistä kaikki palauttaa "
    L"myöhemmin vain itse mykistämänsä pienoisohjelmat. M pienoisohjelmassa tekee saman yleisen vaihdon. Herätyksen ottaminen käyttöön ilman valittuja viikonpäiviä "
    L"avaa pienoisohjelman Herätys-välilehden. Ilmoitusalueen kuvake palautetaan automaattisesti, kun Resurssienhallinta käynnistyy uudelleen.",
    L"\r\n\r\nINDSTILLINGER OG MENUER\r\nGem anvender og lukker, Anvend holder vinduet åbent, og Annuller gendanner ændringer som endnu ikke er anvendt. Enter aktiverer Gem og Esc "
    L"Annuller. Programsprog, skrifttype, udjævning, temaer, lager, start med Windows, kantfastgørelse og tidskilde er globale; programvalgene indstilles på fanen Program. Ved "
    L"første start følger sproget Windows-grænsefladen, med amerikansk engelsk som reserve. Widgetsprog og andre widgetvalg gælder enkeltvis. I ikonmenuen kommer Vis alle og Skjul "
    L"alle før Slå al lyd fra; Arranger i et gitter står i en særskilt gruppe efter dem. Slå lyd fra i widgetmenuen "
    L"svarer til Lyd fra på fanen Generelt. Slå al lyd fra gendanner senere kun de widgets, kommandoen selv dæmpede. M på en widget udfører samme globale skift. "
    L"Aktivering af alarmen uden valgte ugedage åbner widgetens Alarm-fane. Meddelelsesikonet gendannes automatisk, når Windows Stifinder genstartes.",
    L"\r\n\r\nSTILLINGAR OG VALMYNDIR\r\nVista beitir og lokar, Nota heldur glugganum opnum og Hætta við afturkallar breytingar sem ekki hafa verið notaðar. Enter virkjar Vista og Esc "
    L"Hætta við. Tungumál forrits, letur, jöfnun, þemu, geymsla, ræsing með Windows, festing við brúnir og tímagjafi gilda alls staðar; forritsvalkostir eru stilltir á "
    L"Forrit-flipanum. Við fyrstu ræsingu fylgir tungumálið viðmóti Windows, en bandarísk enska er varaval. Tungumál og aðrir valkostir græju gilda fyrir hverja græju. Í "
    L"táknvalmyndinni koma Sýna allt og Fela allt á undan Þagga allt; Raða á hnitanet er í sérstökum flokki á eftir þeim. Þagga í "
    L"valmynd græju samsvarar Þaggað á Almennt-flipanum. Þagga allt endurheimtir síðar aðeins græjurnar sem skipunin þaggaði. M á græju framkvæmir sömu heildarskiptingu. Ef "
    L"vekjari er virkjaður án valinna vikudaga opnast Vekjari-flipi græjunnar. Tilkynningartáknið endurheimtist sjálfkrafa eftir endurræsingu Windows Explorer.",
    L"\r\n\r\nAYARLAR VE MENÜLER\r\nKaydet uygular ve kapatır, Uygula pencereyi açık tutar, İptal ise henüz uygulanmamış değişiklikleri geri alır. Enter Kaydet'i, Esc "
    L"İptal'i etkinleştirir. Uygulama dili, yazı tipi, kenar yumuşatma, temalar, depolama, Windows ile başlatma, kenara yaslama ve zaman kaynağı geneldir; uygulama "
    L"seçenekleri Uygulama sekmesinde ayarlanır. İlk açılışta dil Windows arayüz dilinden alınır; desteklenmiyorsa ABD İngilizcesi kullanılır. Araç dili ve "
    L"diğer araç seçenekleri her araç için ayrıdır. Simge menüsünde Tümünü göster ve Tümünü gizle, Tümünü sessize al seçeneğinden önce gelir; Izgarada düzenle bunların "
    L"ardından ayrı bir gruptadır. Araç menüsündeki Sessize al, Genel sekmesindeki Sessiz ile aynıdır. Tümünü sessize al, daha sonra "
    L"yalnızca kendisinin sessize aldığı araçların sesini geri açar. Bir araçta M tuşu aynı genel geçişi yapar. Hiçbir gün seçili değilken alarmı "
    L"etkinleştirmek aracın Alarm sekmesini açar. Windows Gezgini yeniden başlatıldığında bildirim simgesi otomatik olarak geri yüklenir."
};

const wchar_t* HELP_TIME_SIGNAL_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZVUKOVÉ ČASOVÉ ZNAMENÍ\r\nNa kartě Znamení se pro každý widget samostatně volí žádné znamení nebo interval jedné, pěti, deseti, patnácti, "
    L"dvaceti, třiceti či šedesáti minut. Časová hranice vychází z času daného widgetu včetně UTC, časového pásma, offsetu a případné korekce NTP. Pět krátkých "
    L"tónů zazní v posledních pěti sekundách a dlouhý tón přesně na hranici. Pokud na stejný okamžik připadne znamení více widgetů, přehraje se jediná "
    L"společná sekvence. Po ztlumení může právě znějící tón doznít; další tóny se přeskočí a po zrušení ztlumení zazní až následující naplánovaný tón. "
    L"Samostatný Kalendář nepodporuje budík, časové znamení ani ztlumení; příslušné volby jsou neaktivní a v jeho nabídce nejsou."
    L"\r\n\r\nPři intervalu 20 minut znamení zazní v :00, :20 a :40 podle času widgetu.",
    L"\r\n\r\nAUDIBLE TIME SIGNAL\r\nThe Signal tab selects no signal or an interval of one, five, ten, fifteen, twenty, thirty, or sixty minutes separately "
    L"for each widget. The boundary follows that widget’s time, including UTC, time zone, offset, and any NTP correction. Five short pips sound "
    L"during the final five seconds and a long pip exactly on the boundary. If several widgets signal at the same instant, only one shared sequence "
    L"is played. After muting, a pip already sounding may finish; later pips are skipped and only the next scheduled pip sounds after unmuting. "
    L"A standalone Calendar supports neither alarms, time signals nor muting; the corresponding controls are disabled and its menu omits them."
    L"\r\n\r\nWith a 20-minute interval, signals sound at :00, :20 and :40 in the widget's displayed time.",
    L"\r\n\r\nAKUSTISCHES ZEITZEICHEN\r\nAuf der Registerkarte Zeitzeichen wird für jedes Widget einzeln kein Signal oder ein Intervall von einer, fünf, zehn, fünfzehn, "
    L"zwanzig, dreißig oder sechzig Minuten gewählt. Die Grenze folgt der Zeit dieses Widgets einschließlich UTC, Zeitzone, Offset und einer möglichen NTP-Korrektur. In den letzten "
    L"fünf Sekunden erklingen fünf kurze Töne und genau an der Grenze ein langer Ton. Fallen Signale mehrerer Widgets auf denselben Zeitpunkt, wird nur eine gemeinsame "
    L"Folge wiedergegeben. Beim Stummschalten darf ein bereits klingender Ton enden; weitere Töne werden bis zum nächsten geplanten Ton nach dem Aufheben übersprungen. "
    L"Ein einzelner Kalender unterstützt weder Wecker noch Zeitzeichen oder Stummschaltung; die zugehörigen Optionen sind deaktiviert und fehlen in seinem Menü."
    L"\r\n\r\nBeim 20-Minuten-Intervall ertönt das Zeitzeichen um :00, :20 und :40 gemäß der Widget-Zeit.",
    L"\r\n\r\nSIGNAL HORAIRE SONORE\r\nL’onglet Signal choisit séparément pour chaque widget aucun signal ou un intervalle d’une, cinq, dix, quinze, vingt, trente ou "
    L"soixante minutes. La limite suit l’heure du widget, y compris UTC, le fuseau horaire, le décalage et toute correction NTP. Cinq bips courts retentissent "
    L"pendant les cinq dernières secondes et un bip long exactement à la limite. Si plusieurs widgets signalent au même instant, une seule séquence commune est "
    L"jouée. Lors de la coupure, un bip déjà commencé peut finir ; les suivants sont ignorés et seul le prochain bip planifié retentit après le rétablissement. "
    L"Un Calendrier autonome ne propose ni alarme, ni signal horaire, ni coupure du son ; les options correspondantes sont désactivées et absentes de son menu."
    L"\r\n\r\nAvec un intervalle de 20 minutes, le signal retentit à :00, :20 et :40 selon l’heure du widget.",
    L"\r\n\r\nSEÑAL HORARIA SONORA\r\nLa pestaña Señal permite elegir por separado para cada widget ninguna señal o un intervalo de uno, cinco, diez, quince, "
    L"veinte, treinta o sesenta minutos. El límite sigue la hora del widget, incluidos UTC, zona horaria, offset y cualquier corrección NTP. Cinco pitidos cortos "
    L"suenan durante los últimos cinco segundos y uno largo exactamente en el límite. Si varios widgets coinciden, se reproduce una única secuencia compartida. "
    L"Al silenciar, puede terminar el pitido que ya suena; los siguientes se omiten y, al reactivar el sonido, suena solo el próximo pitido programado. "
    L"Un Calendario independiente no admite alarma, señal horaria ni silencio; las opciones correspondientes están desactivadas y no aparecen en su menú."
    L"\r\n\r\nCon un intervalo de 20 minutos, la señal suena a :00, :20 y :40 según la hora del widget.",
    L"\r\n\r\nSEGNALE ORARIO ACUSTICO\r\nLa scheda Segnale consente di scegliere separatamente per ogni widget nessun segnale oppure un intervallo di uno, "
    L"cinque, dieci, quindici, venti, trenta o sessanta minuti. Il limite segue l’ora del widget, inclusi UTC, fuso orario, offset ed eventuale correzione NTP. Cinque "
    L"segnali brevi suonano negli ultimi cinque secondi e uno lungo esattamente al limite. Se più widget coincidono, viene riprodotta una sola sequenza comune. "
    L"Disattivando l’audio, un segnale già iniziato può terminare; i successivi vengono saltati e, alla riattivazione, suona solo il prossimo segnale programmato. "
    L"Un Calendario autonomo non supporta sveglia, segnale orario o disattivazione audio; le relative opzioni sono disabilitate e assenti dal menu."
    L"\r\n\r\nCon un intervallo di 20 minuti, il segnale suona a :00, :20 e :40 secondo l’ora del widget.",
    L"\r\n\r\nDŹWIĘKOWY SYGNAŁ CZASU\r\nKarta Sygnał pozwala osobno dla każdego widżetu wybrać brak sygnału albo odstęp jednej, pięciu, dziesięciu, piętnastu, "
    L"dwudziestu, trzydziestu lub sześćdziesięciu minut. Granica wynika z czasu widżetu, w tym UTC, strefy czasowej, offsetu i korekty NTP. Pięć krótkich sygnałów "
    L"rozlega się w ostatnich pięciu sekundach, a długi dokładnie na granicy. Gdy sygnały wielu widżetów przypadają jednocześnie, odtwarzana jest jedna wspólna "
    L"sekwencja. Po wyciszeniu rozpoczęty sygnał może wybrzmieć; następne są pomijane, a po włączeniu dźwięku zabrzmi dopiero kolejny zaplanowany sygnał. "
    L"Samodzielny Kalendarz nie obsługuje alarmu, sygnału czasu ani wyciszenia; odpowiednie opcje są wyłączone i nie występują w jego menu."
    L"\r\n\r\nPrzy odstępie 20 minut sygnał rozlega się o :00, :20 i :40 według czasu widżetu.",
    L"\r\n\r\nZVUKOVÉ ČASOVÉ ZNAMENIE\r\nNa karte Znamenie sa pre každý widget samostatne volí žiadne znamenie alebo interval jednej, piatich, desiatich, "
    L"pätnástich, dvadsiatich, tridsiatich či šesťdesiatich minút. Časová hranica vychádza z času daného widgetu vrátane UTC, časového pásma, offsetu a prípadnej korekcie NTP. "
    L"Päť krátkych tónov zaznie v posledných piatich sekundách a dlhý tón presne na hranici. Ak na rovnaký okamih pripadne znamenie viacerých widgetov, prehrá "
    L"sa jediná spoločná sekvencia. Po stlmení môže práve znejúci tón doznieť; ďalšie sa preskočia a po zrušení stlmenia zaznie až nasledujúci naplánovaný tón. "
    L"Samostatný Kalendár nepodporuje budík, časové znamenie ani stlmenie; príslušné voľby sú neaktívne a v jeho ponuke nie sú."
    L"\r\n\r\nPri intervale 20 minút znamenie zaznie v :00, :20 a :40 podľa času widgetu.",
    L"\r\n\r\nAUDIBLE TIME SIGNAL\r\nThe Signal tab selects no signal or an interval of one, five, ten, fifteen, twenty, thirty, or sixty minutes separately "
    L"for each widget. The boundary follows that widget’s time, including UTC, time zone, offset, and any NTP correction. Five short pips sound "
    L"during the final five seconds and a long pip exactly on the boundary. If several widgets signal at the same instant, only one shared sequence "
    L"is played. After muting, a pip already sounding may finish; later pips are skipped and only the next scheduled pip sounds after unmuting. "
    L"A standalone Calendar supports neither alarms, time signals nor muting; the corresponding controls are disabled and its menu omits them."
    L"\r\n\r\nWith a 20-minute interval, signals sound at :00, :20 and :40 in the widget's displayed time.",
    L"\r\n\r\nAUDIBLE TIME SIGNAL\r\nThe Signal tab selects no signal or an interval of one, five, ten, fifteen, twenty, thirty, or sixty minutes separately "
    L"for each widget. The boundary follows that widget’s time, including UTC, time zone, offset, and any NTP correction. Five short pips sound "
    L"during the final five seconds and a long pip exactly on the boundary. If several widgets signal at the same instant, only one shared sequence "
    L"is played. After muting, a pip already sounding may finish; later pips are skipped and only the next scheduled pip sounds after unmuting. "
    L"A standalone Calendar supports neither alarms, time signals nor muting; the corresponding controls are disabled and its menu omits them."
    L"\r\n\r\nWith a 20-minute interval, signals sound at :00, :20 and :40 in the widget's displayed time.",
    L"\r\n\r\nSINAL HORÁRIO SONORO\r\nO separador Sinal escolhe para cada widget nenhum sinal ou intervalos de 1, 5, 10, 15, 20, 30 ou 60 minutos. O limite "
    L"segue a hora do widget, incluindo UTC, fuso, desvio e correção NTP. Soam cinco sinais curtos e um longo; sinais simultâneos de vários widgets "
    L"são unidos. Ao silenciar, o sinal já iniciado pode terminar; os seguintes são ignorados e só o próximo sinal agendado soa depois de repor o áudio. "
    L"Um Calendário autónomo não suporta alarme, sinal horário nem silenciamento; as opções correspondentes ficam desativadas e não aparecem no menu."
    L"\r\n\r\nCom um intervalo de 20 minutos, o sinal soa aos :00, :20 e :40 segundo a hora do widget.",
    L"\r\n\r\nHØRBART TIDSSIGNAL\r\nFanen Signal velger for hver widget ingen signal eller intervaller på 1, 5, 10, 15, 20, 30 eller 60 minutter. Grensen "
    L"følger widgettiden, inkludert UTC, tidssone, forskyvning og NTP-korreksjon. Fem korte og ett langt pip høres; samtidige signaler fra flere widgeter "
    L"slås sammen. Ved demping kan et pip som allerede har startet fullføres; senere pip hoppes over, og bare neste planlagte pip høres etter oppheving. "
    L"En frittstående Kalender støtter ikke alarm, tidssignal eller demping; de tilhørende valgene er deaktivert og finnes ikke i menyen."
    L"\r\n\r\nMed et intervall på 20 minutter lyder signalet ved :00, :20 og :40 etter widgettiden.",
    L"\r\n\r\nHÖRBAR TIDSSIGNAL\r\nFliken Signal väljer för varje widget ingen signal eller intervall på 1, 5, 10, 15, 20, 30 eller 60 minuter. Gränsen "
    L"följer widgetens tid, inklusive UTC, tidszon, förskjutning och NTP-korrigering. Fem korta och ett långt pip hörs; samtidiga signaler från flera "
    L"widgetar slås samman. Vid tystning får ett påbörjat pip avslutas; följande hoppas över och först nästa schemalagda pip hörs efter återaktivering. "
    L"En fristående Kalender stöder inte alarm, tidssignal eller tystning; motsvarande val är inaktiva och saknas i menyn."
    L"\r\n\r\nMed ett intervall på 20 minuter hörs signalen vid :00, :20 och :40 enligt widgetens tid.",
    L"\r\n\r\nÄÄNIMERKKI\r\nAikamerkki-välilehdellä valitaan jokaiselle pienoisohjelmalle ei merkkiä tai 1, 5, 10, 15, 20, 30 tai 60 minuutin väli. Raja "
    L"seuraa pienoisohjelman aikaa, UTC:tä, aikavyöhykettä, poikkeamaa ja NTP-korjausta myöten. Viisi lyhyttä ja yksi pitkä merkki kuuluu; samanaikaiset "
    L"merkit yhdistetään. Mykistettäessä jo alkanut ääni saa päättyä; seuraavat ohitetaan ja mykistyksen jälkeen kuuluu vasta seuraava ajastettu ääni. "
    L"Erillinen Kalenteri ei tue herätystä, aikamerkkiä eikä mykistystä; vastaavat valinnat ovat poissa käytöstä eivätkä näy valikossa."
    L"\r\n\r\nKun väli on 20 minuuttia, aikamerkki kuuluu kohdissa :00, :20 ja :40 pienoisohjelman ajan mukaan.",
    L"\r\n\r\nHØRBART TIDSSIGNAL\r\nFanen Signal vælger for hver widget intet signal eller intervaller på 1, 5, 10, 15, 20, 30 eller 60 minutter. Grænsen "
    L"følger widgettiden, inklusive UTC, tidszone, forskydning og NTP-korrektion. Fem korte og ét langt bip lyder; samtidige signaler fra flere widgets "
    L"flettes sammen. Ved dæmpning må et igangværende bip klinge ud; de følgende springes over, og først det næste planlagte bip lyder efter ophævelse. "
    L"En selvstændig Kalender understøtter ikke alarm, tidssignal eller dæmpning; de tilhørende valg er deaktiverede og findes ikke i menuen."
    L"\r\n\r\nMed et interval på 20 minutter lyder signalet ved :00, :20 og :40 efter widgettiden.",
    L"\r\n\r\nHLJÓÐTÍMAMERKI\r\nTímamerkisflipinn velur fyrir hverja græju ekkert merki eða 1, 5, 10, 15, 20, 30 eða 60 mínútna bil. Mörkin fylgja "
    L"tíma græjunnar, þar með talið UTC, tímabelti, hliðrun og NTP-leiðrétting. Fimm stutt og eitt langt píp hljóma; samtímamerki margra græja "
    L"eru sameinuð. Við þöggun má þegar hafið píp klárast; þeim næstu er sleppt og fyrst næsta áætlaða píp heyrist eftir að þöggun er aflétt. "
    L"Sjálfstætt Dagatal styður hvorki vekjara, tímamerki né þöggun; viðeigandi valkostir eru óvirkir og birtast ekki í valmyndinni."
    L"\r\n\r\nMeð 20 mínútna millibili hljómar tímamerkið á :00, :20 og :40 samkvæmt tíma græjunnar.",
    L"\r\n\r\nSESLİ ZAMAN SİNYALİ\r\nSinyal sekmesi her araç için sinyal yok seçeneğini veya 1, 5, 10, 15, 20, 30 ya da 60 dakikalık aralıkları seçer. Sınır; "
    L"UTC, saat dilimi, ofset ve NTP düzeltmesi dâhil aracın zamanını izler. Beş kısa ve bir uzun ses çalar; birden çok aracın eşzamanlı sinyalleri "
    L"birleştirilir. Sessize alındığında başlamış olan ses bitebilir; sonrakiler atlanır ve ses açıldıktan sonra yalnızca sıradaki planlanmış ses çalar. "
    L"Bağımsız Takvim alarmı, zaman sinyalini veya sessize almayı desteklemez; ilgili seçenekler devre dışıdır ve menüsünde görünmez."
    L"\r\n\r\n20 dakikalık aralıkta sinyal, aracın saatine göre :00, :20 ve :40’ta çalar."
};

const wchar_t* HELP_TIME_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZDROJ ČASU\r\nNa kartě Čas lze pro celou aplikaci, tedy společně pro všechny widgety, vybrat systémový čas Windows nebo čas ze zadaných serverů NTP. NTP koriguje pouze čas "
    L"zobrazovaný v CalClock; systémové hodiny Windows se nikdy nemění. Dokud nebyl získán platný údaj, používá se systémový čas. Po pozdějším výpadku zůstane poslední korekce jen v paměti "
    L"procesu a synchronizace se opakuje. NTP je výchozí. Automatická sada volí podle systémové oblasti české a slovenské servery, PTB pro Evropu nebo celosvětový fond. Více měření se filtruje "
    L"podle síťového zpoždění a odlehlých odpovědí. Synchronizovat nyní spustí nové měření okamžitě. Při změně serverů zůstane dosavadní platná korekce aktivní do získání nové odpovědi.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP servers for the whole application and therefore for all widgets. "
    L"NTP corrects only the time displayed by CalClock; the Windows clock is never changed. System time is used until the first valid reply. After a later "
    L"outage, the last correction remains in process memory and synchronization is retried. NTP is the default. The automatic set chooses Czech and Slovak "
    L"servers, PTB for Europe, or the global pool according to the system region. Multiple measurements are filtered by network delay and outlying replies. "
    L"Synchronize now starts a fresh measurement immediately. When servers change, the current valid correction remains active until a new reply is obtained.",
    L"\r\n\r\nZEITQUELLE\r\nAuf der Registerkarte Zeit wird für die gesamte Anwendung und damit für alle Widgets die Windows-Systemzeit oder die Zeit der eingestellten "
    L"NTP-Server gewählt. NTP korrigiert nur die in CalClock angezeigte Zeit; die Windows-Uhr wird nie geändert. Bis zur ersten gültigen Antwort wird die Systemzeit verwendet. "
    L"Bei einem späteren Ausfall bleibt die letzte Korrektur nur im Prozessspeicher erhalten und die Synchronisierung wird wiederholt. NTP ist voreingestellt. Die automatische "
    L"Gruppe wählt nach der Systemregion die tschechisch-slowakischen Server, PTB für Europa oder den globalen Pool. Mehrere Messungen werden nach Netzverzögerung und "
    L"Ausreißern gefiltert. Jetzt synchronisieren startet sofort eine neue Messung. Beim Serverwechsel bleibt die bisherige gültige Korrektur bis zu einer neuen Antwort aktiv.",
    L"\r\n\r\nSOURCE DE L’HEURE\r\nL’onglet Heure sélectionne l’heure système Windows ou les serveurs NTP configurés pour toute l’application, donc pour tous les widgets. NTP "
    L"corrige uniquement l’heure affichée par CalClock ; l’horloge Windows n’est jamais modifiée. L’heure système est utilisée jusqu’à la première réponse valide. Après une panne "
    L"ultérieure, la dernière correction reste uniquement en mémoire du processus et la synchronisation est retentée. NTP est la valeur par défaut. Le jeu automatique choisit les "
    L"serveurs tchèques et slovaques, PTB pour l’Europe ou le pool mondial selon la région système. Plusieurs mesures sont filtrées selon le délai réseau et les réponses aberrantes. "
    L"Synchroniser maintenant lance immédiatement une nouvelle mesure. Lors d’un changement de serveur, la correction valide actuelle reste active jusqu’à une nouvelle réponse.",
    L"\r\n\r\nORIGEN DE HORA\r\nLa pestaña Hora selecciona la hora del sistema Windows o los servidores NTP configurados para toda la aplicación y, por tanto, para todos los "
    L"widgets. NTP solo corrige la hora mostrada por CalClock; el reloj de Windows nunca se modifica. Se usa la hora del sistema hasta la primera respuesta válida. Tras una "
    L"interrupción posterior, la última corrección permanece solo en la memoria del proceso y se reintenta la sincronización. NTP es el valor predeterminado. El conjunto "
    L"automático elige servidores checos y eslovacos, PTB para Europa o el grupo mundial según la región del sistema. Varias mediciones se filtran por retardo de red y respuestas "
    L"atípicas. Sincronizar ahora inicia una medición nueva de inmediato. Al cambiar servidores, la corrección válida actual sigue activa hasta obtener una respuesta nueva.",
    L"\r\n\r\nORIGINE DELL’ORA\r\nLa scheda Ora seleziona l’ora di sistema Windows o i server NTP configurati per l’intera applicazione e quindi per tutti i widget. NTP "
    L"corregge solo l’ora visualizzata da CalClock; l’orologio di Windows non viene mai modificato. L’ora di sistema viene usata fino alla prima risposta valida. Dopo una "
    L"successiva interruzione, l’ultima correzione rimane solo nella memoria del processo e la sincronizzazione viene ripetuta. NTP è l’impostazione predefinita. Il gruppo "
    L"automatico sceglie i server cechi e slovacchi, PTB per l’Europa o il pool globale in base all’area di sistema. Più misurazioni vengono filtrate in base al ritardo di rete "
    L"e alle risposte anomale. Sincronizza ora avvia subito una nuova misurazione. Cambiando server, la correzione valida corrente resta attiva fino a una nuova risposta.",
    L"\r\n\r\nŹRÓDŁO CZASU\r\nKarta Czas wybiera dla całej aplikacji, a więc dla wszystkich widżetów, czas systemowy Windows albo skonfigurowane serwery NTP. NTP "
    L"koryguje wyłącznie czas wyświetlany przez CalClock; zegar Windows nigdy nie jest zmieniany. Do pierwszej prawidłowej odpowiedzi używany jest czas systemowy. Po "
    L"późniejszej awarii ostatnia korekta pozostaje wyłącznie w pamięci procesu, a synchronizacja jest ponawiana. NTP jest ustawieniem domyślnym. Zestaw automatyczny "
    L"wybiera według regionu systemu serwery czeskie i słowackie, PTB dla Europy albo pulę globalną. Wiele pomiarów jest filtrowanych według opóźnienia sieci i "
    L"wartości odstających. Synchronizuj teraz natychmiast rozpoczyna nowy pomiar. Po zmianie serwerów bieżąca prawidłowa korekta działa do uzyskania nowej odpowiedzi.",
    L"\r\n\r\nZDROJ ČASU\r\nNa karte Čas možno pre celú aplikáciu, teda spoločne pre všetky widgety, vybrať systémový čas Windows alebo čas zo zadaných "
    L"serverov NTP. NTP koriguje iba čas zobrazený v CalClock; systémové hodiny Windows sa nikdy nemenia. Do prvej platnej odpovede sa používa systémový čas. "
    L"Po neskoršom výpadku zostane posledná korekcia iba v pamäti procesu a synchronizácia sa zopakuje. NTP je predvolené. Automatická sada vyberie podľa "
    L"systémovej oblasti české a slovenské servery, PTB pre Európu alebo celosvetový fond. Viaceré merania sa filtrujú podľa sieťového oneskorenia a odľahlých "
    L"odpovedí. Synchronizovať teraz spustí nové meranie ihneď. Pri zmene serverov zostane doterajšia platná korekcia aktívna do získania novej odpovede.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP servers for the whole application and therefore for all widgets. "
    L"NTP corrects only the time displayed by CalClock; the Windows clock is never changed. System time is used until the first valid reply. After a later "
    L"outage, the last correction remains in process memory and synchronization is retried. NTP is the default. The automatic set chooses Czech and Slovak "
    L"servers, PTB for Europe, or the global pool according to the system region. Multiple measurements are filtered by network delay and outlying replies. "
    L"Synchronize now starts a fresh measurement immediately. When servers change, the current valid correction remains active until a new reply is obtained.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP servers for the whole application and therefore for all widgets. "
    L"NTP corrects only the time displayed by CalClock; the Windows clock is never changed. System time is used until the first valid reply. After a later "
    L"outage, the last correction remains in process memory and synchronization is retried. NTP is the default. The automatic set chooses Czech and Slovak "
    L"servers, PTB for Europe, or the global pool according to the system region. Multiple measurements are filtered by network delay and outlying replies. "
    L"Synchronize now starts a fresh measurement immediately. When servers change, the current valid correction remains active until a new reply is obtained.",
    L"\r\n\r\nORIGEM DA HORA\r\nO separador Hora escolhe para toda a aplicação a hora do Windows ou servidores NTP. O NTP corrige apenas o CalClock e nunca altera o Windows. A última "
    L"correção válida permanece na memória durante uma falha. A predefinição é NTP; o conjunto automático escolhe servidores pela região e filtra medições por atraso e valores atípicos.",
    L"\r\n\r\nTIDSKILDE\r\nFanen Tid velger Windows-tid eller NTP-servere for hele programmet. NTP korrigerer bare CalClock og endrer aldri Windows. Siste gyldige "
    L"korreksjon beholdes i minnet under et avbrudd. NTP er standard; det automatiske settet velger servere etter region og filtrerer målinger etter forsinkelse og avvik.",
    L"\r\n\r\nTIDSKÄLLA\r\nFliken Tid väljer Windows-tid eller NTP-servrar för hela programmet. NTP korrigerar bara CalClock och ändrar aldrig Windows. Den senaste giltiga "
    L"korrigeringen sparas i minnet vid ett avbrott. NTP är standard; den automatiska uppsättningen väljer servrar efter region och filtrerar mätningar efter fördröjning och avvikelse.",
    L"\r\n\r\nAIKALÄHDE\r\nAika-välilehdellä valitaan koko sovellukselle Windowsin aika tai NTP-palvelimet. NTP korjaa vain CalClockia eikä muuta Windowsia. Viimeisin kelvollinen "
    L"korjaus säilyy muistissa katkoksen aikana. NTP on oletus; automaattinen joukko valitsee palvelimet alueen mukaan ja suodattaa mittaukset viiveen ja poikkeamien perusteella.",
    L"\r\n\r\nTIDSKILDE\r\nFanen Tid vælger Windows-tid eller NTP-servere for hele programmet. NTP korrigerer kun CalClock og ændrer aldrig Windows. Den seneste gyldige "
    L"korrektion bevares i hukommelsen under en afbrydelse. NTP er standard; det automatiske sæt vælger servere efter område og filtrerer målinger efter forsinkelse og afvigelser.",
    L"\r\n\r\nTÍMAGJAFI\r\nTímaflipinn velur Windows-tíma eða NTP-þjóna fyrir allt forritið. NTP leiðréttir aðeins CalClock og breytir aldrei Windows. Síðasta "
    L"gilda leiðrétting helst í minni meðan sambandsleysi varir. NTP er sjálfgefið; sjálfvirka safnið velur þjóna eftir svæði og síar mælingar eftir töf og frávikum.",
    L"\r\n\r\nZAMAN KAYNAĞI\r\nZaman sekmesi tüm uygulama için Windows zamanını veya NTP sunucularını seçer. NTP yalnızca CalClock'u düzeltir ve Windows'u hiçbir zaman değiştirmez. "
    L"Kesinti sırasında son geçerli düzeltme bellekte tutulur. NTP varsayılandır; otomatik küme bölgeye göre sunucu seçer ve ölçümleri gecikme ile aykırı değerlere göre süzer."
};

const wchar_t* HELP_FULLSCREEN_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nHODINY NA MONITORU\r\nDigitální hodiny mohou vyplnit jeden či více monitorů a volitelně zatemnit ostatní. Ctrl+A vybere v seznamu všechny monitory. "
    L"Velikost písma se udává procentem výšky monitoru; nastavit lze také písmo, vyhlazování, barvy a odsazení. Při času UTC lze na samostatném řádku zobrazit text "
    L"UTC. Výchozí je bílý text na černém pozadí. Je-li otevřeno Nastavení, hodiny se vždy zobrazují jen jako malý přesouvatelný náhled se zachovaným poměrem stran; "
    L"jeho poloha se ukládá. Zarovnání do mřížky tento typ nepřesouvá ani s ním nepočítá. Esc hodiny skryje a zatemnění odstraní i tehdy, když je aktivní Nastavení.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and optionally black out the others. Ctrl+A selects every monitor in the list. "
    L"Font size is a percentage of monitor height; font, smoothing, colours and padding are also configurable. In UTC mode, UTC can be shown on a separate "
    L"line. The default is white text on black. While Settings is open, the clock is always a small draggable preview that keeps the monitor aspect ratio, and its "
    L"position is saved. Grid arrangement ignores and does not move this widget type. Esc hides the clock and removes blackouts even when Settings is active.",
    L"\r\n\r\nMONITORUHR\r\nDie Digitaluhr kann einen oder mehrere Monitore ausfüllen und die übrigen optional abdunkeln. Strg+A wählt alle Monitore der Liste. Die "
    L"Schriftgröße ist ein Prozentsatz der Monitorhöhe; Schrift, Glättung, Farben und Innenabstand sind ebenfalls einstellbar. Im UTC-Modus kann UTC in einer eigenen "
    L"Zeile stehen. Voreingestellt ist Weiß auf Schwarz. Bei geöffneten Einstellungen erscheint die Uhr stets als kleine verschiebbare Vorschau mit dem Seitenverhältnis "
    L"des Monitors; ihre Position wird gespeichert. Die Rasteranordnung ignoriert diesen Widget-Typ. Esc blendet Uhr und Abdunklung auch bei aktiven Einstellungen aus.",
    L"\r\n\r\nHORLOGE SUR MONITEUR\r\nL’horloge numérique peut remplir un ou plusieurs moniteurs et assombrir les autres. Ctrl+A sélectionne tous les moniteurs de la "
    L"liste. La taille de police est un pourcentage de la hauteur ; police, lissage, couleurs et marge sont aussi réglables. En mode UTC, UTC peut apparaître sur une "
    L"ligne distincte. La valeur par défaut est blanc sur noir. Tant que Paramètres est ouvert, l’horloge reste un petit aperçu déplaçable aux proportions du moniteur, "
    L"dont la position est enregistrée. L’alignement en grille ignore ce type de widget. Échap masque l’horloge et retire l’assombrissement même si Paramètres est actif.",
    L"\r\n\r\nRELOJ DE MONITOR\r\nEl reloj digital puede ocupar uno o varios monitores y oscurecer los demás. Ctrl+A selecciona todos los monitores de la lista. El "
    L"tamaño de fuente es un porcentaje de la altura; también se configuran fuente, suavizado, colores y relleno. En modo UTC, UTC puede mostrarse en una línea separada. "
    L"El valor predeterminado es blanco sobre negro. Mientras Configuración está abierta, el reloj siempre es una vista previa pequeña y móvil con la proporción del "
    L"monitor, y se guarda su posición. La alineación en cuadrícula ignora este tipo. Esc oculta el reloj y elimina el oscurecimiento incluso con Configuración activa.",
    L"\r\n\r\nOROLOGIO SU MONITOR\r\nL’orologio digitale può occupare uno o più monitor e oscurare gli altri. Ctrl+A seleziona tutti i monitor nell’elenco. La "
    L"dimensione del carattere è una percentuale dell’altezza; sono configurabili anche carattere, antialiasing, colori e margine. In modalità UTC, UTC può apparire su "
    L"una riga separata. Il valore predefinito è bianco su nero. Con Impostazioni aperto, l’orologio resta sempre una piccola anteprima spostabile con le proporzioni "
    L"del monitor, e la posizione viene salvata. La disposizione in griglia ignora questo tipo. Esc nasconde orologio e oscuramento anche con Impostazioni attivo.",
    L"\r\n\r\nZEGAR NA MONITORZE\r\nZegar cyfrowy może zająć jeden lub kilka monitorów i wygasić pozostałe. Ctrl+A zaznacza wszystkie monitory na liście. "
    L"Rozmiar czcionki jest procentem wysokości monitora; można też ustawić czcionkę, wygładzanie, kolory i odstęp. W trybie UTC napis UTC można wyświetlić "
    L"w osobnym wierszu. Domyślne są białe cyfry na czarnym tle. Gdy Ustawienia są otwarte, zegar zawsze jest małym, przesuwanym podglądem o proporcjach "
    L"monitora, a jego położenie jest zapisywane. Układanie w siatce pomija ten typ. Esc ukrywa zegar i wygaszenie również przy aktywnych Ustawieniach.",
    L"\r\n\r\nHODINY NA MONITORE\r\nDigitálne hodiny môžu vyplniť jeden alebo viac monitorov a stmaviť ostatné. Ctrl+A vyberie všetky monitory v zozname. "
    L"Veľkosť písma je percentom výšky monitora; nastaviť možno aj písmo, vyhladzovanie, farby a odsadenie. V režime UTC možno zobraziť text UTC "
    L"na samostatnom riadku. Predvolené je biele písmo na čiernom pozadí. Pri otvorenom Nastavení sú hodiny vždy iba malým presúvateľným náhľadom s "
    L"pomerom strán monitora a jeho poloha sa ukladá. Zarovnanie do mriežky tento typ ignoruje. Esc skryje hodiny aj stmavenie aj pri aktívnom Nastavení.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and optionally black out the others. Ctrl+A selects every monitor in the list. "
    L"Font size is a percentage of monitor height; font, smoothing, colours and padding are also configurable. In UTC mode, UTC can be shown on a separate "
    L"line. The default is white text on black. While Settings is open, the clock is always a small draggable preview that keeps the monitor aspect ratio, and its "
    L"position is saved. Grid arrangement ignores and does not move this widget type. Esc hides the clock and removes blackouts even when Settings is active.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and optionally black out the others. Ctrl+A selects every monitor in the list. "
    L"Font size is a percentage of monitor height; font, smoothing, colours and padding are also configurable. In UTC mode, UTC can be shown on a separate "
    L"line. The default is white text on black. While Settings is open, the clock is always a small draggable preview that keeps the monitor aspect ratio, and its "
    L"position is saved. Grid arrangement ignores and does not move this widget type. Esc hides the clock and removes blackouts even when Settings is active.",
    L"\r\n\r\nRELÓGIO NO MONITOR\r\nO relógio digital pode preencher um ou vários monitores e escurecer os restantes. A letra é uma percentagem da altura do monitor e também se "
    L"configuram tipo de letra, suavização, cores e margem. Com as Definições abertas é sempre uma pequena pré-visualização arrastável. Esc oculta o relógio e remove o escurecimento.",
    L"\r\n\r\nSKJERMKLOKKE\r\nDen digitale klokken kan fylle én eller flere skjermer og mørklegge resten. Skriftstørrelsen er en prosentandel av skjermhøyden; skrift, "
    L"utjevning, farger og luft kan også angis. Når Innstillinger er åpent, vises alltid en liten, flyttbar forhåndsvisning. Esc skjuler klokken og fjerner mørklegging.",
    L"\r\n\r\nSKÄRMKLOCKA\r\nDen digitala klockan kan fylla en eller flera bildskärmar och släcka de övriga. Teckenstorleken är en procentandel av bildskärmshöjden; teckensnitt, "
    L"utjämning, färger och utfyllnad kan också ställas in. När Inställningar är öppet visas alltid en liten flyttbar förhandsvisning. Esc döljer klockan och tar bort släckningen.",
    L"\r\n\r\nNÄYTTÖKELLO\r\nDigitaalinen kello voi täyttää yhden tai useita näyttöjä ja pimentää muut. Fonttikoko on prosenttiosuus näytön korkeudesta; myös fontti, "
    L"pehmennys, värit ja täyttö voidaan määrittää. Kun Asetukset on avoinna, näytetään aina pieni siirrettävä esikatselu. Esc piilottaa kellon ja poistaa pimennyksen.",
    L"\r\n\r\nSKÆRMUR\r\nDet digitale ur kan fylde en eller flere skærme og mørklægge de øvrige. Skriftstørrelsen er en procentdel af skærmhøjden; skrifttype, "
    L"udjævning, farver og luft kan også indstilles. Når Indstillinger er åbent, vises altid en lille flytbar forhåndsvisning. Esc skjuler uret og fjerner mørklægningen.",
    L"\r\n\r\nSKJÁKUKKA\r\nStafræna klukkan getur fyllt einn eða fleiri skjái og myrkvað hina. Leturstærð er hlutfall af hæð skjásins; einnig má "
    L"stilla letur, jöfnun, liti og bil. Þegar Stillingar eru opnar birtist alltaf lítil færanleg forskoðun. Esc felur klukkuna og fjarlægir myrkvun.",
    L"\r\n\r\nMONİTÖR SAATİ\r\nDijital saat bir veya daha fazla monitörü doldurabilir ve diğerlerini karartabilir. Yazı tipi boyutu monitör yüksekliğinin yüzdesidir; yazı "
    L"tipi, kenar yumuşatma, renkler ve dolgu da ayarlanabilir. Ayarlar açıkken her zaman küçük, sürüklenebilir bir önizleme gösterilir. Esc saati gizler ve karartmayı kaldırır."
};

const wchar_t* ABOUT_TEXT[LANG_COUNT] = {
    L"Hodiny a kalendáře\r\n\r\nNativní Win32 aplikace pro libovolný počet samostatně nastavených plovoucích hodin a kalendářů. Ručičkový ciferník používá systémový ClockWndMain.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for any number of independently configured floating clocks and calendars. The analog face uses the system ClockWndMain.",
    L"Uhren und Kalender\r\n\r\nNative Win32-Anwendung für beliebig viele unabhängig konfigurierte schwebende Uhren und Kalender. Das Zifferblatt verwendet ClockWndMain.",
    L"Horloges et calendriers\r\n\r\nApplication Win32 native pour plusieurs horloges et calendriers flottants configurés séparément. Le cadran utilise ClockWndMain.",
    L"Relojes y calendarios\r\n\r\nAplicación Win32 nativa para varios relojes y calendarios flotantes configurados por separado. La esfera usa ClockWndMain.",
    L"Orologi e calendari\r\n\r\nApplicazione Win32 nativa per più orologi e calendari mobili configurati separatamente. Il quadrante usa ClockWndMain.",
    L"Zegary i kalendarze\r\n\r\nNatywna aplikacja Win32 obsługująca wiele niezależnie skonfigurowanych zegarów i kalendarzy. Tarcza używa ClockWndMain.",
    L"Hodiny a kalendáre\r\n\r\nNatívna aplikácia Win32 pre ľubovoľný počet samostatne nastavených plávajúcich hodín a kalendárov. Ciferník používa ClockWndMain.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for any number of independently configured floating clocks and calendars. The analog face uses the system ClockWndMain.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for any number of independently configured floating clocks and calendars. The analog face uses the system ClockWndMain.",
    L"Relógios e calendários\r\n\r\nAplicação Win32 nativa para qualquer número de relógios e calendários "
    L"flutuantes configurados independentemente. O mostrador analógico utiliza o ClockWndMain do sistema.",
    L"Klokker og kalendere\r\n\r\nEt innebygd Win32-program for et valgfritt antall flytende klokker "
    L"og kalendere med separate innstillinger. Den analoge urskiven bruker systemets ClockWndMain.",
    L"Klockor och kalendrar\r\n\r\nEtt inbyggt Win32-program för valfritt antal flytande klockor "
    L"och kalendrar med separata inställningar. Den analoga urtavlan använder systemets ClockWndMain.",
    L"Kellot ja kalenterit\r\n\r\nNatiivi Win32-sovellus rajattomalle määrälle erikseen määritettäviä "
    L"kelluvia kelloja ja kalentereita. Analoginen kellotaulu käyttää järjestelmän ClockWndMain-ohjainta.",
    L"Ure og kalendere\r\n\r\nEt indbygget Win32-program til et vilkårligt antal flydende ure og kalendere med separate indstillinger. Den analoge urskive bruger systemets ClockWndMain.",
    L"Klukkur og dagatöl\r\n\r\nInnbyggt Win32-forrit fyrir ótakmarkaðan fjölda fljótandi klukkna og dagatala með sjálfstæðum stillingum. Skífuklukkan notar ClockWndMain kerfisins.",
    L"Saatler ve takvimler\r\n\r\nBağımsız olarak yapılandırılan istenen sayıda kayan saat ve takvim için yerel bir Win32 uygulaması. Analog kadran sistem ClockWndMain denetimini kullanır."
};

const wchar_t* ABOUT_VERSION_LABELS[LANG_COUNT] = {
    L"Verze:",
    L"Version:",
    L"Version:",
    L"Version :",
    L"Versión:",
    L"Versione:",
    L"Wersja:",
    L"Verzia:",
    L"Version:",
    L"Version:",
    L"Versão:",
    L"Versjon:",
    L"Version:",
    L"Versio:",
    L"Version:",
    L"Útgáfa:",
    L"Sürüm:"
};

const wchar_t* ABOUT_PLATFORM_LABELS[LANG_COUNT] = {
    L"Cílová platforma:",
    L"Target platform:",
    L"Zielplattform:",
    L"Plateforme cible :",
    L"Plataforma de destino:",
    L"Piattaforma di destinazione:",
    L"Platforma docelowa:",
    L"Cieľová platforma:",
    L"Target platform:",
    L"Target platform:",
    L"Plataforma de destino:",
    L"Målplattform:",
    L"Målplattform:",
    L"Kohdealusta:",
    L"Målplatform:",
    L"Markvettvangur:",
    L"Hedef platform:"
};

const wchar_t* ABOUT_WEBSITE_LABELS[LANG_COUNT] = {
    L"Web:",
    L"Website:",
    L"Website:",
    L"Site web :",
    L"Sitio web:",
    L"Sito web:",
    L"Witryna:",
    L"Web:",
    L"Website:",
    L"Website:",
    L"Site:",
    L"Nettsted:",
    L"Webbplats:",
    L"Verkkosivusto:",
    L"Websted:",
    L"Vefsvæði:",
    L"Web sitesi:"
};

const wchar_t* ABOUT_VISIT_TOOLTIP[LANG_COUNT] = {
    L"Navštívit web",
    L"Visit website",
    L"Website besuchen",
    L"Visiter le site web",
    L"Visitar el sitio web",
    L"Visita il sito web",
    L"Odwiedź witrynę",
    L"Navštíviť web",
    L"Visit website",
    L"Visit website",
    L"Visitar o site",
    L"Besøk nettstedet",
    L"Besök webbplatsen",
    L"Käy verkkosivustolla",
    L"Besøg webstedet",
    L"Heimsækja vefsvæði",
    L"Web sitesini ziyaret et"
};

const wchar_t* OPEN_IN_BROWSER_LABELS[LANG_COUNT] = {
    L"&Otevřít ve výchozím prohlížeči",
    L"&Open in default browser",
    L"Im Standardbrowser &öffnen",
    L"&Ouvrir dans le navigateur par défaut",
    L"&Abrir en el navegador predeterminado",
    L"&Apri nel browser predefinito",
    L"&Otwórz w domyślnej przeglądarce",
    L"&Otvoriť v predvolenom prehliadači",
    L"&Open in default browser",
    L"&Open in default browser",
    L"&Abrir no navegador predefinido",
    L"&Åpne i standardnettleseren",
    L"&Öppna i standardwebbläsaren",
    L"&Avaa oletusselaimessa",
    L"&Åbn i standardbrowseren",
    L"&Opna í sjálfgefnum vafra",
    L"Varsayılan tarayıcıda &aç"
};

const wchar_t* COPY_URL_LABELS[LANG_COUNT] = {
    L"Kopírovat &adresu",
    L"Copy &URL",
    L"&URL kopieren",
    L"Copier l’&URL",
    L"Copiar &URL",
    L"Copia &URL",
    L"Kopiuj &adres URL",
    L"Kopírovať &adresu",
    L"Copy &URL",
    L"Copy &URL",
    L"Copiar &URL",
    L"Kopier &URL",
    L"Kopiera &URL",
    L"Kopioi &URL",
    L"Kopiér &URL",
    L"Afrita &vefslóð",
    L"&URL'yi kopyala"
};

const wchar_t* COPY_INFORMATION_LABELS[LANG_COUNT] = {
    L"Kopírovat &informace",
    L"Copy &information",
    L"&Informationen kopieren",
    L"Copier les &informations",
    L"Copiar &información",
    L"Copia &informazioni",
    L"Kopiuj &informacje",
    L"Kopírovať &informácie",
    L"Copy &information",
    L"Copy &information",
    L"Copiar &informações",
    L"Kopier &informasjon",
    L"Kopiera &information",
    L"Kopioi &tiedot",
    L"Kopiér &oplysninger",
    L"Afrita &upplýsingar",
    L"&Bilgileri kopyala"
};

const wchar_t* APPLICATION_TAB_LABELS[LANG_COUNT] = {
    L"Aplikace",
    L"Application",
    L"Anwendung",
    L"Application",
    L"Aplicación",
    L"Applicazione",
    L"Aplikacja",
    L"Aplikácia",
    L"Application",
    L"Application",
    L"Aplicação",
    L"Program",
    L"Program",
    L"Sovellus",
    L"Program",
    L"Forrit",
    L"Uygulama"
};

const wchar_t* SNAP_TO_WORK_AREA_LABELS[LANG_COUNT] = {
    L"Přichytávat k okrajům plochy",
    L"Snap to work area edges",
    L"An Arbeitsbereichsrändern einrasten",
    L"Aligner sur les bords de la zone de travail",
    L"Ajustar a los bordes del área de trabajo",
    L"Aggancia ai bordi dell'area di lavoro",
    L"Przyciągaj do krawędzi obszaru roboczego",
    L"Prichytávať k okrajom pracovnej plochy",
    L"Snap to work area edges",
    L"Snap to work area edges",
    L"Ajustar às margens da área de trabalho",
    L"Fest til kantene av arbeidsområdet",
    L"Fäst vid arbetsytans kanter",
    L"Kiinnitä työalueen reunoihin",
    L"Fastgør til arbejdsområdets kanter",
    L"Festa við brúnir vinnusvæðis",
    L"Çalışma alanı kenarlarına yasla"
};
