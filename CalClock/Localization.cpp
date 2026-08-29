#include "Localization.h"

const wchar_t* TEXT[LANG_COUNT][TXT_COUNT] = {
    {
        L"Hodiny a kalendáře",
        L"Nastavení",
        L"Přidat",
        L"Odebrat",
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
        L"Remove",
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
        L"Entfernen",
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
        L"Supprimer",
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
        L"Quitar",
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
        L"Rimuovi",
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
        L"Usuń",
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
        L"Odobrať",
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
    }
};

const wchar_t* LANGUAGE_NAMES[LANG_COUNT] = {
    L"Čeština",
    L"English",
    L"Deutsch",
    L"Français",
    L"Español",
    L"Italiano",
    L"Polski",
    L"Slovenčina"
};

const wchar_t* LANGUAGE_LOCALES[LANG_COUNT] = {
    L"cs-CZ",
    L"en-GB",
    L"de-DE",
    L"fr-FR",
    L"es-ES",
    L"it-IT",
    L"pl-PL",
    L"sk-SK"
};

const wchar_t* WIDGET_LANGUAGE_LABELS[LANG_COUNT] = {
    L"Jazyk widgetu:",
    L"Widget language:",
    L"Widget-Sprache:",
    L"Langue du widget :",
    L"Idioma del widget:",
    L"Lingua del widget:",
    L"Język widżetu:",
    L"Jazyk widgetu:"
};

const wchar_t* APPLICATION_LANGUAGE_LABELS[LANG_COUNT] = {
    L"&Jazyk aplikace:",
    L"Application &language:",
    L"&Anwendungssprache:",
    L"&Langue de l’application :",
    L"&Idioma de la aplicación:",
    L"&Lingua applicazione:",
    L"Język &aplikacji:",
    L"&Jazyk aplikácie:"
};

const wchar_t* APPLICATION_FONT_LABELS[LANG_COUNT] = {
    L"&Písmo aplikace:",
    L"Application &font:",
    L"Anwendungs&schrift:",
    L"&Police de l’application :",
    L"&Fuente de la aplicación:",
    L"&Carattere applicazione:",
    L"&Czcionka aplikacji:",
    L"&Písmo aplikácie:"
};

const wchar_t* SYSTEM_DEFAULT_FONT_LABELS[LANG_COUNT] = {
    L"Výchozí systémové",
    L"System default",
    L"Systemstandard",
    L"Valeur système",
    L"Predeterminada del sistema",
    L"Predefinito di sistema",
    L"Domyślna systemowa",
    L"Predvolené systémové"
};

const wchar_t* DATE_COPY_LABELS[LANG_COUNT] = {
    L"&Formát kopírovaného data",
    L"Copied &date format",
    L"Format des kopierten &Datums",
    L"Format de date &copié",
    L"Formato de fecha &copiada",
    L"Formato data &copiata",
    L"Format &kopiowanej daty",
    L"Formát &kopírovaného dátumu"
};

const wchar_t* DATE_FORMAT_LABELS[LANG_COUNT] = {
    L"Formát &kopírovaného data:",
    L"Copied &date format:",
    L"Format des kopierten &Datums:",
    L"Format de date &copié :",
    L"Formato de fecha &copiada:",
    L"Formato data &copiata:",
    L"Format &kopiowanej daty:",
    L"Formát &kopírovaného dátumu:"
};

const wchar_t* LOCAL_SHORT_LABELS[LANG_COUNT] = {
    L"Krátké datum",
    L"Short date",
    L"Kurzes Datum",
    L"Date courte",
    L"Fecha corta",
    L"Data breve",
    L"Data krótka",
    L"Krátky dátum"
};

const wchar_t* LOCAL_LONG_LABELS[LANG_COUNT] = {
    L"Dlouhé datum",
    L"Long date",
    L"Langes Datum",
    L"Date longue",
    L"Fecha larga",
    L"Data estesa",
    L"Data długa",
    L"Dlhý dátum"
};

const wchar_t* ARRANGE_WIDGET_LABELS[LANG_COUNT] = {
    L"&Zarovnat widgety do mřížky",
    L"&Arrange widgets in a grid",
    L"Widgets im &Raster anordnen",
    L"&Aligner les widgets en grille",
    L"&Alinear widgets en cuadrícula",
    L"&Disponi i widget in griglia",
    L"&Ułóż widżety w siatce",
    L"&Zarovnať widgety do mriežky"
};

const wchar_t* SHOW_WIDGET_LABELS[LANG_COUNT] = {
    L"&Zobrazit",
    L"&Show",
    L"&Anzeigen",
    L"&Afficher",
    L"&Mostrar",
    L"&Mostra",
    L"&Pokaż",
    L"&Zobraziť"
};

const wchar_t* HIDE_WIDGET_LABELS[LANG_COUNT] = {
    L"&Skrýt",
    L"&Hide",
    L"A&usblenden",
    L"&Masquer",
    L"&Ocultar",
    L"&Nascondi",
    L"&Ukryj",
    L"&Skryť"
};

const wchar_t* UTC_TEXT_LABELS[LANG_COUNT] = {
    L"Zobrazit text &UTC",
    L"Show &UTC text",
    L"&UTC-Text anzeigen",
    L"Afficher le texte &UTC",
    L"Mostrar texto &UTC",
    L"Mostra testo &UTC",
    L"Pokaż tekst &UTC",
    L"Zobraziť text &UTC"
};

const wchar_t* SHOW_FRAME_LABELS[LANG_COUNT] = {
    L"Zobrazit &rámeček",
    L"Show &frame",
    L"&Rahmen anzeigen",
    L"Afficher la &bordure",
    L"Mostrar &marco",
    L"Mostra &cornice",
    L"Pokaż &ramkę",
    L"Zobraziť &rámček"
};

const wchar_t* MONITOR_LABELS[LANG_COUNT] = {
    L"&Monitory:",
    L"&Monitors:",
    L"&Monitore:",
    L"&Moniteurs :",
    L"&Monitores:",
    L"&Monitor:",
    L"&Monitory:",
    L"&Monitory:"
};

const wchar_t* BLACKOUT_MONITOR_LABELS[LANG_COUNT] = {
    L"Zatemnit &ostatní monitory",
    L"Black out &other monitors",
    L"&Andere Monitore abdunkeln",
    L"Assombrir les &autres moniteurs",
    L"Oscurecer &otros monitores",
    L"Oscura gli &altri monitor",
    L"Wygasz &pozostałe monitory",
    L"Stmaviť &ostatné monitory"
};

const wchar_t* FONT_BUTTON_LABELS[LANG_COUNT] = {
    L"Vybrat &písmo...",
    L"Choose &font...",
    L"&Schriftart wählen...",
    L"Choisir la &police...",
    L"Elegir &fuente...",
    L"Scegli &carattere...",
    L"Wybierz &czcionkę...",
    L"Vybrať &písmo..."
};

const wchar_t* CALENDAR_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &kalendáře...",
    L"&Calendar font...",
    L"&Kalenderschrift...",
    L"Police du &calendrier...",
    L"Fuente del &calendario...",
    L"Carattere del &calendario...",
    L"Czcionka &kalendarza...",
    L"Písmo &kalendára..."
};

const wchar_t* PANEL_TOP_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &horního řádku...",
    L"&Top row font...",
    L"Schrift der &oberen Zeile...",
    L"Police de la ligne &supérieure...",
    L"Fuente de la línea &superior...",
    L"Carattere riga &superiore...",
    L"Czcionka &górnego wiersza...",
    L"Písmo &horného riadka..."
};

const wchar_t* PANEL_TIME_FONT_LABELS[LANG_COUNT] = {
    L"Písmo č&asu...",
    L"&Time font...",
    L"&Zeitschrift...",
    L"Police de l’&heure...",
    L"Fuente de la &hora...",
    L"Carattere dell’&ora...",
    L"Czcionka &czasu...",
    L"Písmo č&asu..."
};

const wchar_t* PANEL_BOTTOM_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &spodního řádku...",
    L"&Bottom row font...",
    L"Schrift der &unteren Zeile...",
    L"Police de la ligne &inférieure...",
    L"Fuente de la línea &inferior...",
    L"Carattere riga &inferiore...",
    L"Czcionka &dolnego wiersza...",
    L"Písmo &spodného riadka..."
};

const wchar_t* DEFAULT_FONT_LABELS[LANG_COUNT] = {
    L"Vý&chozí",
    L"&Default",
    L"&Standard",
    L"Par &défaut",
    L"&Predeterminada",
    L"&Predefinito",
    L"&Domyślna",
    L"&Predvolené"
};

const wchar_t* ALARM_TEXT_COLOR_LABELS[LANG_COUNT] = {
    L"Barva &textu budíku...",
    L"Alarm &text color...",
    L"&Wecker-Textfarbe...",
    L"Couleur du &texte d’alarme...",
    L"Color del &texto de alarma...",
    L"Colore &testo sveglia...",
    L"Kolor &tekstu alarmu...",
    L"Farba &textu budíka..."
};

const wchar_t* ALARM_BACKGROUND_COLOR_LABELS[LANG_COUNT] = {
    L"Barva &pozadí budíku...",
    L"Alarm &background...",
    L"Wecker-&Hintergrund...",
    L"&Fond de l’alarme...",
    L"&Fondo de alarma...",
    L"&Sfondo sveglia...",
    L"&Tło alarmu...",
    L"Farba &pozadia budíka..."
};

const wchar_t* PADDING_LABELS[LANG_COUNT] = {
    L"&Odsazení:",
    L"&Padding:",
    L"&Innenabstand:",
    L"&Marge interne :",
    L"&Relleno:",
    L"&Margine:",
    L"&Odstęp:",
    L"&Odsadenie:"
};

const wchar_t* BORDER_LABELS[LANG_COUNT] = {
    L"&Styl rámečku:",
    L"&Border style:",
    L"&Rahmenstil:",
    L"Style de &bordure :",
    L"Estilo de &borde:",
    L"Stile &bordo:",
    L"Styl &ramki:",
    L"Štýl &rámčeka:"
};

const wchar_t* BORDER_WIDTH_LABELS[LANG_COUNT] = {
    L"Šíř&ka rám.:",
    L"Border &width:",
    L"Rahmen&breite:",
    L"É&paisseur :",
    L"&Ancho:",
    L"&Spessore:",
    L"&Szerokość:",
    L"Šír&ka rám.:"
};

const wchar_t* TIME_TAB_LABELS[LANG_COUNT] = {
    L"Čas",
    L"Time",
    L"Zeit",
    L"Heure",
    L"Hora",
    L"Ora",
    L"Czas",
    L"Čas"
};

const wchar_t* TIME_SOURCE_LABELS[LANG_COUNT] = {
    L"&Zdroj času:",
    L"Time &source:",
    L"Zeit&quelle:",
    L"&Source de l’heure :",
    L"&Origen de hora:",
    L"&Origine ora:",
    L"Źródło &czasu:",
    L"&Zdroj času:"
};

const wchar_t* SYSTEM_TIME_LABELS[LANG_COUNT] = {
    L"Systémový čas Windows",
    L"Windows system time",
    L"Windows-Systemzeit",
    L"Heure système Windows",
    L"Hora del sistema Windows",
    L"Ora di sistema Windows",
    L"Czas systemowy Windows",
    L"Systémový čas Windows"
};

const wchar_t* NTP_TIME_LABELS[LANG_COUNT] = {
    L"Čas ze serverů NTP",
    L"Time from NTP servers",
    L"Zeit von NTP-Servern",
    L"Heure des serveurs NTP",
    L"Hora de servidores NTP",
    L"Ora dai server NTP",
    L"Czas z serwerów NTP",
    L"Čas zo serverov NTP"
};

const wchar_t* NTP_SERVERS_LABELS[LANG_COUNT] = {
    L"&Servery NTP (oddělené středníkem):",
    L"&NTP servers (semicolon-separated):",
    L"&NTP-Server (durch Semikolon getrennt):",
    L"Serveurs &NTP (séparés par des points-virgules) :",
    L"Servidores &NTP (separados por punto y coma):",
    L"Server &NTP (separati da punto e virgola):",
    L"Serwery &NTP (oddzielone średnikami):",
    L"Servery &NTP (oddelené bodkočiarkou):"
};

const wchar_t* NTP_PRESET_FIELD_LABELS[LANG_COUNT] = {
    L"Výchozí &sada:",
    L"Default &set:",
    L"Standard&gruppe:",
    L"&Jeu par défaut :",
    L"Conjunto &predeterminado:",
    L"Gruppo &predefinito:",
    L"&Zestaw domyślny:",
    L"Predvolená &sada:"
};

const wchar_t* NTP_PRESET_LABELS[LANG_COUNT][NTP_PRESET_COUNT] = {
    {
        L"Automaticky podle oblasti",
        L"Česko a Slovensko – CESNET/NIC.CZ",
        L"PTB – Německo a Evropa",
        L"Celý svět – Ubuntu / NTP Pool",
        L"Vlastní"},
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
    L"&Synchronizovať teraz"
};

const wchar_t* TIME_GLOBAL_NOTE[LANG_COUNT] = {
    L"Zdroj a synchronizace času platí globálně pro všechny widgety.",
    L"The time source and synchronization apply globally to all widgets.",
    L"Zeitquelle und Synchronisierung gelten global für alle Widgets.",
    L"La source et la synchronisation de l’heure s’appliquent globalement à tous les widgets.",
    L"La fuente y la sincronización de hora se aplican globalmente a todos los widgets.",
    L"L’origine e la sincronizzazione dell’ora si applicano globalmente a tutti i widget.",
    L"Źródło i synchronizacja czasu obowiązują globalnie dla wszystkich widżetów.",
    L"Zdroj a synchronizácia času platia globálne pre všetky widgety."
};

const wchar_t* NTP_STATUS_SYSTEM[LANG_COUNT] = {
    L"Používá se systémový čas; Windows se nemění.",
    L"System time is used; Windows is not changed.",
    L"Die Systemzeit wird verwendet; Windows wird nicht geändert.",
    L"L’heure système est utilisée ; Windows n’est pas modifié.",
    L"Se usa la hora del sistema; Windows no se modifica.",
    L"Viene usata l’ora di sistema; Windows non viene modificato.",
    L"Używany jest czas systemowy; system Windows nie jest zmieniany.",
    L"Používa sa systémový čas; Windows sa nemení."
};

const wchar_t* NTP_STATUS_WAITING[LANG_COUNT] = {
    L"Čeká se na synchronizaci NTP…",
    L"Waiting for NTP synchronization…",
    L"NTP-Synchronisierung wird erwartet…",
    L"Synchronisation NTP en attente…",
    L"Esperando la sincronización NTP…",
    L"In attesa della sincronizzazione NTP…",
    L"Oczekiwanie na synchronizację NTP…",
    L"Čaká sa na synchronizáciu NTP…"
};

const wchar_t* NTP_STATUS_FAILED[LANG_COUNT] = {
    L"Servery NTP nejsou dostupné; dočasně se používá systémový čas.",
    L"NTP servers are unavailable; system time is used temporarily.",
    L"NTP-Server sind nicht erreichbar; vorübergehend wird die Systemzeit verwendet.",
    L"Les serveurs NTP sont indisponibles ; l’heure système est utilisée temporairement.",
    L"Los servidores NTP no están disponibles; se usa temporalmente la hora del sistema.",
    L"I server NTP non sono disponibili; viene usata temporaneamente l’ora di sistema.",
    L"Serwery NTP są niedostępne; tymczasowo używany jest czas systemowy.",
    L"Servery NTP nie sú dostupné; dočasne sa používa systémový čas."
};

const wchar_t* NTP_STATUS_RETAINED[LANG_COUNT] = {
    L"Servery NTP nejsou dostupné; používá se poslední korekce v paměti:",
    L"NTP servers are unavailable; the last in-memory correction is used:",
    L"NTP-Server sind nicht erreichbar; die letzte Korrektur im Speicher wird verwendet:",
    L"Les serveurs NTP sont indisponibles ; la dernière correction en mémoire est utilisée :",
    L"Los servidores NTP no están disponibles; se usa la última corrección guardada en memoria:",
    L"I server NTP non sono disponibili; viene usata l’ultima correzione in memoria:",
    L"Serwery NTP są niedostępne; używana jest ostatnia korekta przechowywana w pamięci:",
    L"Servery NTP nie sú dostupné; používa sa posledná korekcia v pamäti:"
};

const wchar_t* NTP_STATUS_SYNCHRONIZED[LANG_COUNT] = {
    L"Synchronizováno se serverem",
    L"Synchronized with",
    L"Synchronisiert mit",
    L"Synchronisé avec",
    L"Sincronizado con",
    L"Sincronizzato con",
    L"Zsynchronizowano z",
    L"Synchronizované so serverom"
};

const wchar_t* ANTIALIASING_LABELS[LANG_COUNT] = {
    L"&Vyhlazování písma:",
    L"Font &antialiasing:",
    L"Schrift&glättung:",
    L"&Lissage des polices :",
    L"&Suavizado de fuente:",
    L"&Antialiasing carattere:",
    L"&Wygładzanie czcionki:",
    L"&Vyhladzovanie písma:"
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
    L"&Predvolený vzhľad"
};

const wchar_t* TEST_COMMAND_LABELS[LANG_COUNT] = {
    L"V&yzkoušet",
    L"&Test",
    L"&Testen",
    L"&Tester",
    L"&Probar",
    L"&Prova",
    L"&Testuj",
    L"V&yskúšať"
};

const wchar_t* STOP_TEST_LABELS[LANG_COUNT] = {
    L"&Zastavit test",
    L"S&top test",
    L"Test &stoppen",
    L"&Arrêter le test",
    L"&Detener prueba",
    L"&Ferma prova",
    L"&Zatrzymaj test",
    L"&Zastaviť test"
};

const wchar_t* REMOTE_SCRIPT_LABELS[LANG_COUNT] = {
    L"Zavolat &vzdálený skript",
    L"Call a &remote script",
    L"&Remote-Skript aufrufen",
    L"Appeler un script &distant",
    L"Llamar a un script &remoto",
    L"Chiama script &remoto",
    L"Wywołaj skrypt &zdalny",
    L"Zavolať &vzdialený skript"
};

const wchar_t* REMOTE_SCRIPT_URL_LABELS[LANG_COUNT] = {
    L"Adresa URL:",
    L"URL:",
    L"URL:",
    L"URL :",
    L"URL:",
    L"URL:",
    L"Adres URL:",
    L"Adresa URL:"
};

const wchar_t* INVALID_REMOTE_SCRIPT_URL[LANG_COUNT] = {
    L"Zadejte platnou adresu vzdáleného skriptu HTTP nebo HTTPS.",
    L"Enter a valid HTTP or HTTPS remote script URL.",
    L"Geben Sie eine gültige HTTP- oder HTTPS-Adresse des Remote-Skripts ein.",
    L"Entrez une adresse HTTP ou HTTPS valide pour le script distant.",
    L"Introduzca una dirección HTTP o HTTPS válida para el script remoto.",
    L"Immettere un indirizzo HTTP o HTTPS valido per lo script remoto.",
    L"Wprowadź prawidłowy adres HTTP lub HTTPS zdalnego skryptu.",
    L"Zadajte platnú adresu HTTP alebo HTTPS vzdialeného skriptu."
};

const wchar_t* IMPORT_SETTINGS_LABELS[LANG_COUNT] = {
    L"Importovat &XML...",
    L"Import &XML...",
    L"&XML importieren...",
    L"Importer &XML...",
    L"Importar &XML...",
    L"Importa &XML...",
    L"Importuj &XML...",
    L"Importovať &XML..."
};

const wchar_t* EXPORT_SETTINGS_LABELS[LANG_COUNT] = {
    L"Exportovat X&ML...",
    L"Export X&ML...",
    L"XML &exportieren...",
    L"Exporter X&ML...",
    L"Exportar X&ML...",
    L"Esporta X&ML...",
    L"Eksportuj X&ML...",
    L"Exportovať X&ML..."
};

const wchar_t* INVALID_SETTINGS_FILE[LANG_COUNT] = {
    L"Soubor neobsahuje platné nastavení CalClock.",
    L"The file does not contain valid CalClock settings.",
    L"Die Datei enthält keine gültigen CalClock-Einstellungen.",
    L"Le fichier ne contient pas de paramètres CalClock valides.",
    L"El archivo no contiene una configuración válida de CalClock.",
    L"Il file non contiene impostazioni CalClock valide.",
    L"Plik nie zawiera prawidłowych ustawień CalClock.",
    L"Súbor neobsahuje platné nastavenia CalClock."
};

const wchar_t* SETTINGS_EXPORT_FAILED[LANG_COUNT] = {
    L"Nastavení se nepodařilo exportovat.",
    L"Settings could not be exported.",
    L"Die Einstellungen konnten nicht exportiert werden.",
    L"Impossible d’exporter les paramètres.",
    L"No se pudo exportar la configuración.",
    L"Impossibile esportare le impostazioni.",
    L"Nie udało się wyeksportować ustawień.",
    L"Nastavenia sa nepodarilo exportovať."
};

const wchar_t* SETTINGS_IMPORT_FAILED[LANG_COUNT] = {
    L"Nastavení se nepodařilo importovat.",
    L"Settings could not be imported.",
    L"Die Einstellungen konnten nicht importiert werden.",
    L"Impossible d’importer les paramètres.",
    L"No se pudo importar la configuración.",
    L"Impossibile importare le impostazioni.",
    L"Nie udało się zaimportować ustawień.",
    L"Nastavenia sa nepodarilo importovať."
};

const wchar_t* XML_STORAGE_LABELS[LANG_COUNT] = {
    L"Ukládat do &XML",
    L"Save to &XML",
    L"In &XML speichern",
    L"Enregistrer en &XML",
    L"Guardar en &XML",
    L"Salva in &XML",
    L"Zapisuj do &XML",
    L"Ukladať do &XML"
};

const wchar_t* HELP_TEXT[LANG_COUNT] = {
    L"OVLÁDÁNÍ\r\nLevým tlačítkem a tažením přesunete hodiny nebo panel. Samostatný kalendář se přesouvá za volnou plochu; kliknutím na den měníte vybrané datum a šipkami, "
    L"záhlavím nebo odkazem Dnes kalendář procházíte. Pravým tlačítkem na widgetu nebo na ikoně v oznamovací oblasti otevřete nabídku. Levé kliknutí na ikonu skryje právě "
    L"viditelné widgety; jsou-li všechny skryté, obnoví pouze naposledy skryté widgety.\r\n\r\nWIDGETY A NASTAVENÍ\r\nV Nastavení lze přidat, odebrat a duplikovat "
    L"libovolný počet ručičkových hodin, digitálních hodin, kalendářů a panelů s "
    L"kalendářem a hodinami i hodin na monitoru. Každý widget má vlastní viditelnost, režim vždy navrchu, jazyk, časové pásmo a offset. Offset zadávejte jako [-]HH:mm:ss.ff. Ručičkové hodiny a "
    L"hodiny v panelu mají čtyři velikosti. U digitálních hodin lze nastavit sekundy, úvodní nulu, písmo, barvy, neprůhlednost a průhledné pozadí. Kalendář podporuje čísla týdnů, "
    L"neděli jako první den a používá zvolený jazyk widgetu.\r\n\r\nBUDÍK\r\nBudík lze nastavit pro hodiny a panel. Zvukový soubor aplikace přehrává sama jednou nebo stále dokola "
    L"podle volby. Ostatní soubor nebo příkaz předá systému Windows. Kliknutím na budící ciferník či displej, příkazem Zastavit budík nebo klávesou Esc zastavíte blikání i zvuk "
    L"přehrávaný aplikací.\r\n\r\nZKRATKY A UKLÁDÁNÍ\r\nDvojklik na hodiny přepne sekundy, F1 otevře nápovědu, B otevře Nastavení a Esc skryje widget, pokud právě nezastavuje "
    L"budík. Polohy widgetů se ukládají po přesunutí, polohy formulářů při zavření a nastavení do zvoleného úložiště. Další spuštění programu aktivuje již běžící instanci a "
    L"zachová widgety u nejbližšího dostupného okraje pracovní plochy.",
    L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a standalone calendar by its free area; click a day to change the selection and use the arrows, header or "
    L"Today link to navigate. Right-click a widget or notification icon for its menu. Left-click the notification icon to hide the currently visible widgets; when all are hidden, it "
    L"restores only the widgets hidden most recently.\r\n\r\nWIDGETS AND "
    L"SETTINGS\r\nSettings can add, remove and duplicate any number of analog clocks, digital clocks, calendars, calendar-and-clock panels and monitor clocks. Each widget has its own visibility, "
    L"always-on-top state, language, time zone and offset. Enter offsets as [-]HH:mm:ss.ff. Analog clocks and panel clocks have four sizes. Digital clocks support seconds, a "
    L"leading zero, font, colours, opacity and a transparent background. Calendars support week numbers and Sunday as the first day and use the widget "
    L"language.\r\n\r\nALARM\r\nClocks and panels can have an alarm. The application plays an audio file itself, once or continuously according to the loop option. Other files or "
    L"commands are passed to Windows. Click the alarming clock face or display, choose Stop alarm, or press Esc to stop both the alarm indication and audio played by the "
    L"application.\r\n\r\nSHORTCUTS AND SAVING\r\nDouble-click a clock to toggle seconds, press F1 for Help, B for Settings, and Esc to hide a widget when no alarm is being "
    L"stopped. Widget positions are saved after dragging, dialog positions when closed, and all settings in the selected storage. Starting the program again activates the running "
    L"instance and keeps widgets at the nearest available point in the work area.",
    L"BEDIENUNG\r\nZiehen Sie eine Uhr oder ein Panel mit der linken Maustaste. Einen einzelnen Kalender ziehen Sie an seiner freien Fläche; ein Klick auf einen Tag ändert die "
    L"Auswahl. Rechtsklick auf Widget oder Infobereichsymbol öffnet das Menü. Linksklick auf das Symbol verbirgt die gerade sichtbaren Widgets; sind alle verborgen, werden nur "
    L"die zuletzt verborgenen Widgets wiederhergestellt.\r\n\r\nWIDGETS UND EINSTELLUNGEN\r\nSie "
    L"können beliebig viele Analoguhren, Digitaluhren, Kalender, Kalender-Uhr-Panels und Monitoruhren hinzufügen, entfernen oder duplizieren. Jedes Widget besitzt eigene Sichtbarkeit, "
    L"Vordergrundlage, Sprache, Zeitzone und einen Versatz im Format [-]HH:mm:ss.ff. Analoguhren haben vier Größen. Digitaluhren bieten Sekunden, führende Null, Schrift, Farben, "
    L"Deckkraft und transparenten Hintergrund. Kalender bieten Wochennummern, Sonntag als ersten Tag und verwenden die Widget-Sprache.\r\n\r\nWECKER\r\nEine Audiodatei wird "
    L"intern einmal oder in Schleife abgespielt; andere Dateien oder Befehle werden an Windows übergeben. Ein Klick auf das alarmierende Zifferblatt bzw. Display, Wecker stoppen "
    L"oder Esc beendet Anzeige und intern abgespielten Ton.\r\n\r\nTASTEN UND SPEICHERN\r\nDoppelklick schaltet Sekunden um, F1 öffnet Hilfe, B die Einstellungen. Positionen und "
    L"sämtliche Einstellungen werden im gewählten Speicher gespeichert. Ein erneuter Programmstart aktiviert die laufende Instanz.",
    L"COMMANDES\r\nFaites glisser une horloge ou un panneau avec le bouton gauche. Déplacez un calendrier autonome par sa zone libre ; cliquez sur un jour pour changer la "
    L"sélection. Un clic droit sur un widget ou l’icône de notification ouvre le menu. Un clic gauche sur l’icône masque les widgets visibles ; s’ils sont tous masqués, il "
    L"rétablit uniquement les widgets masqués le plus récemment.\r\n\r\nWIDGETS ET "
    L"PARAMÈTRES\r\nVous pouvez ajouter, supprimer et dupliquer autant d’horloges analogiques, numériques, calendriers, panneaux combinés et horloges sur moniteur que nécessaire. Chaque widget possède "
    L"sa visibilité, son maintien au premier plan, sa langue, son fuseau et son décalage au format [-]HH:mm:ss.ff. Les horloges analogiques ont quatre tailles. Les horloges "
    L"numériques proposent secondes, zéro initial, police, couleurs, opacité et fond transparent. Le calendrier propose numéros de semaine, dimanche en premier et la langue du "
    L"widget.\r\n\r\nALARME\r\nL’application lit elle-même un fichier audio une fois ou en boucle ; les autres fichiers ou commandes sont confiés à Windows. Cliquez sur le cadran "
    L"ou l’affichage en alarme, choisissez Arrêter l’alarme ou appuyez sur Échap pour arrêter l’indication et le son interne.\r\n\r\nRACCOURCIS ET ENREGISTREMENT\r\nUn "
    L"double-clic bascule les secondes, F1 ouvre l’aide et B les paramètres. Les positions et tous les réglages sont enregistrés dans le stockage sélectionné. Un nouveau lancement active "
    L"l’instance existante.",
    L"CONTROLES\r\nArrastre un reloj o panel con el botón izquierdo. El calendario independiente se arrastra por su zona libre; haga clic en un día para cambiar la selección. El "
    L"botón derecho sobre un widget o el icono de notificación abre el menú. Un clic izquierdo sobre el icono oculta los widgets visibles; si todos están ocultos, restaura solo "
    L"los ocultados más recientemente.\r\n\r\nWIDGETS Y "
    L"CONFIGURACIÓN\r\nPuede añadir, quitar y duplicar cualquier número de relojes analógicos, digitales, calendarios, paneles combinados y relojes de monitor. Cada widget tiene visibilidad, primer "
    L"plano, idioma, zona horaria y desfase propios; use [-]HH:mm:ss.ff. Los relojes analógicos tienen cuatro tamaños. Los digitales permiten segundos, cero inicial, fuente, "
    L"colores, opacidad y fondo transparente. El calendario permite números de semana, domingo primero y usa el idioma del widget.\r\n\r\nALARMA\r\nLa aplicación reproduce "
    L"internamente un archivo de audio una vez o en bucle; los demás archivos o comandos se entregan a Windows. Haga clic en la esfera o pantalla con alarma, elija Detener alarma "
    L"o pulse Esc para detener la indicación y el audio interno.\r\n\r\nATAJOS Y GUARDADO\r\nEl doble clic cambia los segundos, F1 abre la ayuda y B la configuración. Las "
    L"posiciones y todos los ajustes se guardan en el almacenamiento seleccionado. Otra ejecución activa la instancia existente.",
    L"COMANDI\r\nTrascinare un orologio o pannello con il pulsante sinistro. Il calendario autonomo si trascina dall’area libera; fare clic su un giorno per cambiare la "
    L"selezione. Il pulsante destro su widget o icona di notifica apre il menu. Il clic sinistro sull’icona nasconde i widget visibili; se sono tutti nascosti, ripristina soltanto "
    L"quelli nascosti più di recente.\r\n\r\nWIDGET E IMPOSTAZIONI\r\nÈ "
    L"possibile aggiungere, rimuovere e duplicare un numero qualsiasi di orologi analogici, digitali, calendari, pannelli combinati e orologi su monitor. Ogni widget ha visibilità, primo piano, "
    L"lingua, fuso orario e offset propri; usare [-]HH:mm:ss.ff. Gli orologi analogici hanno quattro dimensioni. Quelli digitali offrono secondi, zero iniziale, carattere, "
    L"colori, opacità e sfondo trasparente. Il calendario offre numeri di settimana, domenica per prima e usa la lingua del widget.\r\n\r\nSVEGLIA\r\nL’applicazione riproduce "
    L"internamente un file audio una volta o in ciclo; gli altri file o comandi vengono affidati a Windows. Fare clic sul quadrante o display in allarme, scegliere Ferma sveglia "
    L"o premere Esc per fermare indicazione e audio interno.\r\n\r\nSCORCIATOIE E SALVATAGGIO\r\nIl doppio clic commuta i secondi, F1 apre la guida e B le impostazioni. Posizioni "
    L"e impostazioni vengono salvate nell’archivio selezionato. Un nuovo avvio attiva l’istanza esistente.",
    L"STEROWANIE\r\nPrzeciągnij zegar lub panel lewym przyciskiem. Samodzielny kalendarz przeciąga się za wolne miejsce; kliknięcie dnia zmienia wybór. Prawy przycisk na widżecie "
    L"lub ikonie obszaru powiadomień otwiera menu. Lewy przycisk na ikonie ukrywa widoczne widżety; gdy wszystkie są ukryte, przywraca tylko ostatnio ukryte widżety.\r\n\r\n"
    L"WIDŻETY I USTAWIENIA\r\nMożna dodać, usunąć i powielić "
    L"dowolną liczbę zegarów analogowych, cyfrowych, kalendarzy, paneli łączonych i zegarów na monitorze. Każdy widżet ma własną widoczność, tryb na wierzchu, język, strefę czasową i przesunięcie w "
    L"formacie [-]HH:mm:ss.ff. Zegary analogowe mają cztery rozmiary. Cyfrowe oferują sekundy, zero wiodące, czcionkę, kolory, krycie i przezroczyste tło. Kalendarz oferuje "
    L"numery tygodni, niedzielę jako pierwszy dzień i język widżetu.\r\n\r\nALARM\r\nAplikacja sama odtwarza plik audio raz lub w pętli; inne pliki i polecenia przekazuje "
    L"systemowi Windows. Kliknięcie alarmującej tarczy lub wyświetlacza, polecenie Zatrzymaj alarm albo Esc zatrzymuje wskazanie i dźwięk wewnętrzny.\r\n\r\nSKRÓTY I ZAPIS\r\n"
    L"Dwuklik przełącza sekundy, F1 otwiera pomoc, a B ustawienia. Pozycje i wszystkie ustawienia są zapisywane w wybranym magazynie. Ponowne uruchomienie aktywuje istniejącą instancję.",
    L"OVLÁDANIE\r\nĽavým tlačidlom a ťahaním presuniete hodiny alebo panel. Samostatný kalendár sa presúva za voľnú plochu; kliknutím na deň zmeníte výber. Pravé tlačidlo na "
    L"widgete alebo ikone v oznamovacej oblasti otvorí ponuku. Ľavé kliknutie na ikonu skryje viditeľné widgety; ak sú všetky skryté, obnoví iba naposledy skryté widgety.\r\n\r\n"
    L"WIDGETY A NASTAVENIA\r\nMožno pridať, odobrať a "
    L"duplikovať ľubovoľný počet ručičkových hodín, digitálnych hodín, kalendárov, kombinovaných panelov a hodín na monitore. Každý widget má vlastnú viditeľnosť, režim vždy navrchu, jazyk, časové "
    L"pásmo a offset vo formáte [-]HH:mm:ss.ff. Ručičkové hodiny majú štyri veľkosti. Digitálne hodiny ponúkajú sekundy, úvodnú nulu, písmo, farby, priehľadnosť a priehľadné "
    L"pozadie. Kalendár ponúka čísla týždňov, nedeľu ako prvý deň a používa jazyk widgetu.\r\n\r\nBUDÍK\r\nAplikácia prehrá zvukový súbor sama raz alebo dookola; ostatné súbory a "
    L"príkazy odovzdá systému Windows. Kliknutie na budík, príkaz Zastaviť budík alebo Esc zastaví signalizáciu aj interný zvuk.\r\n\r\nSKRATKY A UKLADANIE\r\nDvojklik prepne "
    L"sekundy, F1 otvorí pomoc a B nastavenia. Polohy a všetky nastavenia sa ukladajú do zvoleného úložiska. Ďalšie spustenie aktivuje existujúcu inštanciu."
};

const wchar_t* HELP_ALARM_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZADÁVÁNÍ ČASU A AKCE BUDÍKU\r\nČas budíku přijímá běžný tvar HH:mm s dvojtečkou, tečkou, mezerou či jiným oddělovačem; oddělovač lze také vynechat. Jedna nebo dvě "
    L"číslice znamenají hodiny, tři nebo čtyři číslice hodiny a minuty, například 7, 12, 730, 0730 nebo 7:30. Po opuštění pole se čas sjednotí na HH:mm. Offset se zadává zprava "
    L"od sekund: 2 znamená 00:00:02.00, 230 i 0230 znamená 00:02:30.00 a 12345 znamená 01:23:45.00. Při odděleném zápisu jsou dvě skupiny minuty a sekundy, tři skupiny hodiny, "
    L"minuty a sekundy a čtvrtá skupina setiny; lze použít znaménko. Tlačítko Vyzkoušet rozbliká aktuální ciferník či rám panelu a zároveň asynchronně vyzkouší soubor, příkaz, "
    L"zvuk a HTTP/HTTPS adresu vzdáleného skriptu. Zastavení testu nebo budíku ukončí i interně přehrávaný zvuk.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, space or another separator; the separator may also be omitted. One or two digits mean "
    L"hours, while three or four digits mean hours and minutes, for example 7, 12, 730, 0730 or 7:30. The value is normalized to HH:mm after leaving the field. Offset entry "
    L"starts from seconds on the right: 2 means 00:00:02.00, 230 and 0230 mean 00:02:30.00, and 12345 means 01:23:45.00. With separators, two groups mean minutes and seconds, "
    L"three mean hours, minutes and seconds, and a fourth group contains hundredths; a sign is accepted. Test flashes the selected clock face or panel frame and asynchronously "
    L"tests the file, command, audio and HTTP/HTTPS remote-script URL. Stopping the test or alarm also stops audio played internally.",
    L"\r\n\r\nZEITEINGABE UND WECKERAKTIONEN\r\nDie Weckzeit akzeptiert HH:mm mit Doppelpunkt, Punkt, Leerzeichen oder einem anderen Trennzeichen; das Trennzeichen kann "
    L"entfallen. Eine oder zwei Ziffern bedeuten Stunden, drei oder vier Ziffern Stunden und Minuten, z. B. 7, 12, 730, 0730 oder 7:30. Beim Verlassen des Feldes wird HH:mm "
    L"verwendet. Der Versatz wird von rechts ab den Sekunden eingegeben: 2 bedeutet 00:00:02.00, 230 und 0230 bedeuten 00:02:30.00 und 12345 bedeutet 01:23:45.00. Mit "
    L"Trennzeichen stehen zwei Gruppen für Minuten und Sekunden, drei für Stunden, Minuten und Sekunden und eine vierte für Hundertstel; ein Vorzeichen ist zulässig. Testen lässt "
    L"Zifferblatt oder Panelrahmen blinken und prüft Datei, Befehl, Audio sowie eine HTTP/HTTPS-Adresse eines Remote-Skripts asynchron. Das Stoppen beendet auch intern "
    L"abgespieltes Audio.",
    L"\r\n\r\nSAISIE DE L’HEURE ET ACTIONS D’ALARME\r\nL’heure accepte HH:mm avec deux-points, point, espace ou un autre séparateur, qui peut aussi être omis. Un ou deux chiffres "
    L"indiquent les heures, trois ou quatre les heures et les minutes, par exemple 7, 12, 730, 0730 ou 7:30. La valeur devient HH:mm à la sortie du champ. Le décalage se saisit "
    L"de droite à partir des secondes : 2 signifie 00:00:02.00, 230 et 0230 signifient 00:02:30.00, et 12345 signifie 01:23:45.00. Avec séparateurs, deux groupes représentent "
    L"minutes et secondes, trois représentent heures, minutes et secondes, et un quatrième les centièmes ; un signe est accepté. Tester fait clignoter le cadran ou le cadre du "
    L"panneau et teste de façon asynchrone fichier, commande, audio et URL HTTP/HTTPS du script distant. L’arrêt coupe aussi le son lu par l’application.",
    L"\r\n\r\nENTRADA DE HORA Y ACCIONES DE ALARMA\r\nLa hora admite HH:mm con dos puntos, punto, espacio u otro separador, que también puede omitirse. Uno o dos dígitos indican "
    L"horas; tres o cuatro, horas y minutos, por ejemplo 7, 12, 730, 0730 o 7:30. Al salir del campo se normaliza a HH:mm. El desfase se introduce desde la derecha empezando por "
    L"los segundos: 2 es 00:00:02.00, 230 y 0230 son 00:02:30.00, y 12345 es 01:23:45.00. Con separadores, dos grupos son minutos y segundos, tres son horas, minutos y segundos, "
    L"y un cuarto contiene centésimas; se admite signo. Probar hace parpadear la esfera o el marco del panel y prueba de forma asíncrona archivo, comando, audio y URL HTTP/HTTPS "
    L"del script remoto. Detener también para el audio interno.",
    L"\r\n\r\nIMMISSIONE DELL’ORA E AZIONI SVEGLIA\r\nL’ora accetta HH:mm con due punti, punto, spazio o un altro separatore, che può anche essere omesso. Una o due cifre "
    L"indicano le ore; tre o quattro indicano ore e minuti, per esempio 7, 12, 730, 0730 o 7:30. Uscendo dal campo il valore diventa HH:mm. L’offset si inserisce da destra "
    L"partendo dai secondi: 2 significa 00:00:02.00, 230 e 0230 significano 00:02:30.00 e 12345 significa 01:23:45.00. Con separatori, due gruppi sono minuti e secondi, tre sono "
    L"ore, minuti e secondi e un quarto contiene i centesimi; è ammesso il segno. Prova fa lampeggiare il quadrante o il bordo del pannello e verifica in modo asincrono file, "
    L"comando, audio e URL HTTP/HTTPS dello script remoto. L’arresto interrompe anche l’audio interno.",
    L"\r\n\r\nWPROWADZANIE CZASU I AKCJE ALARMU\r\nCzas alarmu przyjmuje HH:mm z dwukropkiem, kropką, spacją lub innym separatorem; separator można pominąć. Jedna lub dwie cyfry "
    L"oznaczają godziny, trzy lub cztery godziny i minuty, np. 7, 12, 730, 0730 albo 7:30. Po opuszczeniu pola wartość przyjmuje postać HH:mm. Przesunięcie wpisuje się od prawej, "
    L"zaczynając od sekund: 2 oznacza 00:00:02.00, 230 i 0230 oznaczają 00:02:30.00, a 12345 oznacza 01:23:45.00. Przy separatorach dwie grupy oznaczają minuty i sekundy, trzy "
    L"godziny, minuty i sekundy, a czwarta setne części; znak jest dozwolony. Test miga tarczą lub ramką panelu i asynchronicznie sprawdza plik, polecenie, dźwięk oraz adres "
    L"HTTP/HTTPS zdalnego skryptu. Zatrzymanie wyłącza też dźwięk wewnętrzny.",
    L"\r\n\r\nZADÁVANIE ČASU A AKCIE BUDÍKA\r\nČas budíka prijíma HH:mm s dvojbodkou, bodkou, medzerou alebo iným oddeľovačom; oddeľovač možno aj vynechať. Jedna alebo dve "
    L"číslice znamenajú hodiny, tri alebo štyri hodiny a minúty, napríklad 7, 12, 730, 0730 alebo 7:30. Po opustení poľa sa hodnota upraví na HH:mm. Offset sa zadáva sprava od "
    L"sekúnd: 2 znamená 00:00:02.00, 230 aj 0230 znamená 00:02:30.00 a 12345 znamená 01:23:45.00. Pri oddelenom zápise sú dve skupiny minúty a sekundy, tri skupiny hodiny, minúty "
    L"a sekundy a štvrtá skupina stotiny; možno použiť znamienko. Vyskúšať rozbliká ciferník alebo rám panela a asynchrónne otestuje súbor, príkaz, zvuk aj HTTP/HTTPS adresu "
    L"vzdialeného skriptu. Zastavenie ukončí aj interne prehrávaný zvuk."
};

const wchar_t* HELP_SELECTION_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nVÝBĚR, KLÁVESY A KOPÍROVÁNÍ DATA\r\nV seznamu widgetů označíte více položek pomocí Ctrl, Shift nebo Ctrl+A. Ovládací prvky na kartách Obecné, Vzhled a Budík se potom "
    L"zneaktivní, karta Čas však zůstane dostupná, protože je globální. Nastavení si pamatuje poslední otevřenou kartu a Přidat poslední skutečně přidaný typ. Odebrat nebo Del "
    L"odstraní všechny označené položky až po použití změn. Dvojklik položky krátce zvýrazní "
    L"odpovídající widget. Volba Nastavení… v nabídce konkrétního widgetu jej v seznamu rovnou vybere. Ctrl+A i trojklik označí celý obsah textového pole. Kliknutí na den v "
    L"kalendáři datum vybere a zkopíruje do schránky; všechny masky jsou dostupné v každém jazyce a slovní formáty používají jazyk widgetu. Výchozí Krátké datum se řídí jazykem widgetu.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nUse Ctrl, Shift or Ctrl+A to select several widgets. Controls on the General, Appearance and Alarm tabs are then disabled, while the global "
    L"Time tab remains available. Settings remembers the last open tab, and Add remembers the last type actually added. Remove or Del removes all selected items when the changes "
    L"are applied. Double-click an item to identify its widget briefly. Settings… in a specific "
    L"widget menu selects that widget in the list. Ctrl+A and a triple-click select all text in an edit field. Clicking a calendar day selects it and copies it to the clipboard; each "
    L"calendar has its own format in Settings and its menu. Every pattern is available in every language, while textual formats use the widget language. The default Short date "
    L"follows the widget language.",
    L"\r\n\r\nAUSWAHL, TASTEN UND DATUMSKOPIE\r\nMit Strg, Umschalt oder Strg+A wählen Sie mehrere Widgets. Die Bedienelemente der Registerkarten Allgemein, Darstellung und Wecker "
    L"werden dann deaktiviert; die globale Registerkarte Zeit bleibt verfügbar. Einstellungen merkt sich die zuletzt geöffnete Registerkarte, Hinzufügen den zuletzt wirklich hinzugefügten "
    L"Typ. Entfernen oder Entf löscht beim Anwenden alle ausgewählten Einträge. Doppelklick kennzeichnet ein "
    L"Widget kurz; Einstellungen… im Widget-Menü wählt es in der Liste aus. Strg+A und Dreifachklick markieren den gesamten Text eines Eingabefelds. Ein Klick auf einen "
    L"Kalendertag wählt und kopiert ihn im je Widget eingestellten Format. Alle Muster sind in jeder Sprache verfügbar; Textformate verwenden die Widget-Sprache. Das voreingestellte "
    L"Kurze Datum folgt der Widget-Sprache.",
    L"\r\n\r\nSÉLECTION, TOUCHES ET COPIE DE DATE\r\nCtrl, Maj ou Ctrl+A sélectionne plusieurs widgets. Les commandes des onglets Général, Apparence et Alarme sont alors désactivées, mais "
    L"l’onglet global Heure reste disponible. Paramètres mémorise le dernier onglet ouvert et Ajouter le dernier type réellement ajouté. Supprimer ou Suppr retire toute la sélection "
    L"lors de l’application. Un double-clic identifie brièvement le widget ; Paramètres… dans "
    L"son menu le sélectionne dans la liste. Ctrl+A et un triple-clic sélectionnent tout le texte d’un champ. Cliquer sur un jour le sélectionne et le copie selon le format propre "
    L"au calendrier. Tous les modèles sont disponibles dans chaque langue ; les formats textuels utilisent la langue du widget. La Date courte par défaut suit la langue du widget.",
    L"\r\n\r\nSELECCIÓN, TECLAS Y COPIA DE FECHA\r\nCtrl, Mayús o Ctrl+A selecciona varios widgets. Los controles de General, Apariencia y Alarma se desactivan, pero la pestaña global Hora "
    L"sigue disponible. Configuración recuerda la última pestaña abierta y Añadir el último tipo realmente añadido. Quitar o Supr elimina todos los seleccionados al aplicar los "
    L"cambios. Un doble clic identifica brevemente el widget; Configuración… en su menú lo selecciona "
    L"en la lista. Ctrl+A y un triple clic seleccionan todo el texto de un campo. Pulsar un día lo selecciona y copia según el formato propio del calendario; los formatos de texto "
    L"usan el idioma del widget. Todos los patrones están disponibles en cualquier idioma y la Fecha corta predeterminada sigue el idioma del widget.",
    L"\r\n\r\nSELEZIONE, TASTI E COPIA DELLA DATA\r\nCtrl, Maiusc o Ctrl+A seleziona più widget. I controlli delle schede Generale, Aspetto e Sveglia vengono disattivati, mentre la scheda Ora "
    L"globale resta disponibile. Impostazioni ricorda l’ultima scheda aperta e Aggiungi l’ultimo tipo realmente aggiunto. Rimuovi o Canc elimina tutti gli elementi selezionati "
    L"quando si applicano le modifiche. Un doppio clic identifica il widget; Impostazioni… nel suo "
    L"menu lo seleziona nell’elenco. Ctrl+A e un triplo clic selezionano tutto il testo di un campo. Il clic su un giorno lo seleziona e lo copia nel formato del calendario; i formati "
    L"testuali usano la lingua del widget. Tutti i modelli sono disponibili in ogni lingua e la Data breve predefinita segue la lingua del widget.",
    L"\r\n\r\nZAZNACZANIE, KLAWISZE I KOPIOWANIE DATY\r\nCtrl, Shift lub Ctrl+A zaznacza wiele widżetów. Elementy kart Ogólne, Wygląd i Alarm są wtedy wyłączone, ale globalna karta Czas "
    L"pozostaje dostępna. Ustawienia pamiętają ostatnio otwartą kartę, a Dodaj ostatnio rzeczywiście dodany typ. Usuń lub Del usuwa wszystkie zaznaczone pozycje po zastosowaniu "
    L"zmian. Dwuklik krótko wskazuje widżet; Ustawienia… w jego menu wybierają go na liście. "
    L"Ctrl+A i potrójne kliknięcie zaznaczają cały tekst pola. Kliknięcie dnia wybiera go i kopiuje w formacie danego kalendarza. Wszystkie wzorce są dostępne w każdym języku, "
    L"a formaty słowne używają języka widżetu. Domyślna Data krótka zależy od języka widżetu.",
    L"\r\n\r\nVÝBER, KLÁVESY A KOPÍROVANIE DÁTUMU\r\nPomocou Ctrl, Shift alebo Ctrl+A označíte viac widgetov. Prvky kariet Všeobecné, Vzhľad a Budík sa deaktivujú, globálna karta Čas však "
    L"zostane dostupná. Nastavenie si pamätá poslednú otvorenú kartu a Pridať posledný skutočne pridaný typ. Odobrať alebo Del odstráni po použití zmien všetky označené položky. "
    L"Dvojklik widget krátko zvýrazní; Nastavenia… v jeho ponuke ho vyberú v zozname. "
    L"Ctrl+A aj trojklik označia celý text poľa. Kliknutie na deň ho vyberie a skopíruje vo formáte daného kalendára. Všetky masky sú dostupné v každom jazyku, slovné formáty "
    L"používajú jazyk widgetu a predvolený Krátky dátum sa riadi jazykom widgetu."
};

const wchar_t* HELP_LAYOUT_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nROZLOŽENÍ WIDGETŮ\r\nPříkaz Zarovnat widgety do mřížky zachová přibližné ruční rozmístění, posune středy widgetů na nejbližší body mřížky a odstraní překrytí. V "
    L"nabídce widgetu se upraví jeho monitor, z ikony všechny monitory samostatně. Opakování rozložení nemění. Dvojklik v Nastavení označí widget rychlým světlemodrým blikáním; "
    L"budík bliká pomaleji červeně. Vypnutí Vždy navrchu pošle widget dozadu.",
    L"\r\n\r\nWIDGET LAYOUT\r\nArrange widgets in a grid preserves the approximate manual layout, snaps widget centres to the nearest grid points and removes overlaps. A widget "
    L"menu affects its monitor; the notification icon applies it to every monitor separately. Repeating the command keeps the layout stable. A Settings double-click identifies a "
    L"widget with a fast light-blue flash; an alarm flashes more slowly in red. Turning off Always on top sends the widget to the back.",
    L"\r\n\r\nWIDGET-ANORDNUNG\r\nWidgets im Raster anordnen behält die ungefähre manuelle Anordnung bei, richtet die Mittelpunkte am nächsten Rasterpunkt aus und beseitigt "
    L"Überlappungen. Das Widget-Menü wirkt auf seinen Monitor, das Symbol auf alle Monitore einzeln. Wiederholen ändert die Anordnung nicht. Die Kennzeichnung blinkt schnell "
    L"hellblau, der Alarm langsamer rot. Das Abschalten von Immer im Vordergrund schickt das Widget nach hinten.",
    L"\r\n\r\nDISPOSITION\r\nAligner les widgets en grille conserve leur disposition manuelle approximative, aligne leurs centres sur la grille la plus proche et supprime les "
    L"chevauchements. Le menu du widget agit sur son écran, l’icône sur chaque écran séparément. La commande répétée reste stable. L’identification clignote rapidement en bleu "
    L"clair, l’alarme plus lentement en rouge. Désactiver Toujours visible envoie le widget à l’arrière-plan.",
    L"\r\n\r\nDISTRIBUCIÓN\r\nAlinear widgets en cuadrícula conserva la distribución manual aproximada, ajusta sus centros a la cuadrícula más cercana y elimina superposiciones. "
    L"El menú del widget actúa en su monitor; el icono, en cada monitor por separado. Repetir no cambia la distribución. La identificación parpadea rápido en azul claro y la "
    L"alarma más despacio en rojo. Desactivar Siempre visible envía el widget al fondo.",
    L"\r\n\r\nDISPOSIZIONE\r\nDisponi i widget in griglia conserva la disposizione manuale approssimativa, allinea i centri alla griglia più vicina ed elimina le sovrapposizioni. "
    L"Il menu del widget agisce sul suo monitor, l’icona su ogni monitor separatamente. Ripetere il comando non cambia la disposizione. L’identificazione lampeggia rapidamente in "
    L"azzurro, la sveglia più lentamente in rosso. Disattivando Sempre in primo piano il widget viene mandato dietro.",
    L"\r\n\r\nUKŁAD WIDŻETÓW\r\nUłóż widżety w siatce zachowuje przybliżony układ ręczny, przyciąga środki widżetów do najbliższych punktów siatki i usuwa nakładanie. Menu "
    L"widżetu działa na jego monitorze, a ikona na każdym monitorze osobno. Powtórzenie nie zmienia układu. Identyfikacja miga szybko jasnoniebiesko, alarm wolniej na czerwono. "
    L"Wyłączenie Zawsze na wierzchu wysyła widżet do tyłu.",
    L"\r\n\r\nROZLOŽENIE WIDGETOV\r\nZarovnať widgety do mriežky zachová približné ručné rozmiestnenie, pritiahne stredy widgetov k najbližším bodom mriežky a odstráni "
    L"prekrývanie. Ponuka widgetu upraví jeho monitor, ikona každý monitor samostatne. Opakovanie rozloženie nemení. Identifikácia bliká rýchlo svetlomodro, budík pomalšie "
    L"načerveno. Vypnutie Vždy navrchu pošle widget dozadu."
};

const wchar_t* HELP_STORAGE_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nVZHLED A ÚLOŽIŠTĚ\r\nZměny vzhledu se ukazují ihned v živém náhledu; Zrušit vrátí nepoužitý vzhled a Výchozí vzhled obnoví výchozí hodnoty daného typu. Digitální hodiny "
    L"nabízejí písmo, vyhlazování, barvy, neprůhlednost, odsazení, styl a šířku rámečku a průhledné pozadí, které ponechá jen číslice a rámeček. Panel má samostatná písma horního "
    L"řádku, času a spodního řádku, úvodní nulu a čtyři velikosti ciferníku. Kalendář i panel lze zobrazit s rámečkem nebo bez něj. Motivy a vyhlazování lze nastavit pro aplikaci "
    L"i widget; písmo nativního kalendáře lze měnit jen při zakázaných motivech. Nastavení lze exportovat do XML a importovat přímo do stavu aplikace. Automatické XML je v "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Po úspěšném zápisu XML se odstraní větev HKCU\\SOFTWARE\\FortSoft\\CalClock; při ukládání do registru se automatické XML odstraní.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live preview; Cancel restores unapplied appearance and Default appearance restores the defaults for that widget type. "
    L"Digital clocks provide font, smoothing, colours, opacity, padding, border style and width, and a transparent background that leaves only digits and border. The panel has separate "
    L"fonts for its top row, time and bottom row, a leading zero and four clock-face sizes. Calendars and panels can show or hide their frame. Themes and font smoothing can be set for "
    L"the application and each widget; the native calendar font is selectable only when themes are disabled. Settings can be exported to XML and imported directly into application state. "
    L"Automatic XML is %AppData%\\FortSoft\\CalClock\\settings.xml. After writing XML, HKCU\\SOFTWARE\\FortSoft\\CalClock is removed; registry storage removes the automatic XML.",
    L"\r\n\r\nDARSTELLUNG UND SPEICHERUNG\r\nDarstellungsänderungen erscheinen sofort in der Vorschau; Abbrechen stellt nicht angewandte Werte wieder her, "
    L"Standarddarstellung die Vorgaben des Widget-Typs. "
    L"Digitaluhren bieten Schrift, Glättung, Farben, Deckkraft, Innenabstand, Rahmenart und -breite sowie transparenten Hintergrund. Das Panel besitzt getrennte Schriften für obere Zeile, "
    L"Zeit und untere Zeile, eine führende Null und vier Zifferblattgrößen. Kalender und Panel können ihren Rahmen ein- oder ausblenden. Designs und Schriftglättung gelten wahlweise für "
    L"Anwendung oder Widget; die native Kalenderschrift ist nur bei deaktivierten Designs wählbar. XML-Export und -Import wirken direkt auf den Anwendungszustand. Automatisches XML liegt in "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml; XML-Speicherung entfernt HKCU\\SOFTWARE\\FortSoft\\CalClock, Registrierungsspeicherung entfernt das automatische XML.",
    L"\r\n\r\nAPPARENCE ET STOCKAGE\r\nLes changements d’apparence sont prévisualisés immédiatement ; Annuler restaure les valeurs non appliquées et Apparence par défaut celles "
    L"du type de widget. Les horloges "
    L"numériques proposent police, lissage, couleurs, opacité, marge, style et largeur de bordure, ainsi qu’un fond transparent. Le panneau possède des polices distinctes pour les lignes "
    L"supérieure, horaire et inférieure, un zéro initial et quatre tailles de cadran. Calendrier et panneau peuvent masquer leur cadre. Thèmes et lissage se règlent pour l’application et "
    L"le widget ; la police du calendrier natif n’est sélectionnable que si les thèmes sont désactivés. L’export et l’import XML agissent directement sur l’état. Le XML automatique est "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml ; son écriture retire HKCU\\SOFTWARE\\FortSoft\\CalClock, tandis que le registre retire ce XML.",
    L"\r\n\r\nAPARIENCIA Y ALMACENAMIENTO\r\nLos cambios de apariencia se previsualizan al instante; Cancelar restaura los no aplicados y Apariencia predeterminada los valores del "
    L"tipo de widget. Los relojes digitales "
    L"ofrecen fuente, suavizado, colores, opacidad, relleno, estilo y ancho de borde, además de fondo transparente. El panel tiene fuentes separadas para la línea superior, la hora y la "
    L"inferior, cero inicial y cuatro tamaños de esfera. Calendario y panel pueden ocultar su marco. Temas y suavizado se configuran para la aplicación y para cada widget; la fuente del "
    L"calendario nativo solo se elige con temas desactivados. La exportación e importación XML actúan directamente sobre el estado. El XML automático es "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml; al escribirlo se elimina HKCU\\SOFTWARE\\FortSoft\\CalClock y al usar el registro se elimina el XML automático.",
    L"\r\n\r\nASPETTO E ARCHIVIAZIONE\r\nLe modifiche all’aspetto sono mostrate subito nell’anteprima; Annulla ripristina quelle non applicate e Aspetto predefinito i valori del tipo "
    L"di widget. Gli orologi digitali "
    L"offrono carattere, antialiasing, colori, opacità, margine, stile e larghezza del bordo e sfondo trasparente. Il pannello ha caratteri separati per riga superiore, ora e riga inferiore, "
    L"zero iniziale e quattro dimensioni del quadrante. Calendario e pannello possono nascondere il bordo. Temi e antialiasing si impostano per applicazione e widget; il carattere del "
    L"calendario nativo è selezionabile solo con temi disattivati. Esportazione e importazione XML agiscono direttamente sullo stato. L’XML automatico è "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml; scriverlo rimuove HKCU\\SOFTWARE\\FortSoft\\CalClock, mentre il registro rimuove l’XML automatico.",
    L"\r\n\r\nWYGLĄD I ZAPIS\r\nZmiany wyglądu są od razu widoczne w podglądzie; Anuluj przywraca niezastosowane wartości, a Wygląd domyślny wartości danego typu widżetu. Zegary cyfrowe "
    L"oferują czcionkę, wygładzanie, kolory, krycie, odstęp, styl i szerokość ramki oraz przezroczyste tło. Panel ma osobne czcionki górnego wiersza, czasu i dolnego wiersza, zero "
    L"wiodące oraz cztery rozmiary tarczy. Kalendarz i panel mogą ukrywać ramkę. Motywy i wygładzanie ustawia się dla aplikacji i widżetu; czcionkę natywnego kalendarza można wybrać "
    L"tylko przy wyłączonych motywach. Eksport i import XML działają bezpośrednio na stan. Automatyczny XML to %AppData%\\FortSoft\\CalClock\\settings.xml; zapis XML usuwa "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock, a zapis w rejestrze usuwa automatyczny XML.",
    L"\r\n\r\nVZHĽAD A UKLADANIE\r\nZmeny vzhľadu sa ihneď ukazujú v náhľade; Zrušiť vráti nepoužité hodnoty a Predvolený vzhľad hodnoty daného typu widgetu. Digitálne hodiny ponúkajú písmo, "
    L"vyhladzovanie, farby, nepriehľadnosť, odsadenie, štýl a šírku rámčeka aj priehľadné pozadie. Panel má samostatné písma horného riadka, času a spodného riadka, úvodnú nulu a "
    L"štyri veľkosti ciferníka. Kalendár a panel môžu rámček skryť. Motívy a vyhladzovanie sa nastavujú pre aplikáciu aj widget; písmo natívneho kalendára možno vybrať iba pri "
    L"zakázaných motívoch. Export a import XML pôsobia priamo na stav. Automatické XML je %AppData%\\FortSoft\\CalClock\\settings.xml; zápis XML odstráni "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock a ukladanie do registra odstráni automatické XML."
};

const wchar_t* HELP_TIME_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZDROJ ČASU\r\nNa kartě Čas lze pro celou aplikaci, tedy společně pro všechny widgety, vybrat systémový čas Windows nebo čas ze zadaných serverů NTP. NTP koriguje pouze čas "
    L"zobrazovaný v CalClock; systémové hodiny Windows se nikdy nemění. Dokud nebyl získán platný údaj, používá se systémový čas. Po pozdějším výpadku zůstane poslední korekce jen v "
    L"paměti procesu a synchronizace se opakuje. NTP je výchozí. Automatická sada volí podle systémové oblasti české a slovenské servery, PTB pro Evropu nebo celosvětový fond. Více "
    L"měření se filtruje podle síťového zpoždění a odlehlých odpovědí. Synchronizovat nyní spustí nové měření okamžitě. Při změně serverů zůstane dosavadní platná korekce aktivní "
    L"do získání nové odpovědi.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP servers for the whole application and therefore for all widgets. NTP corrects only the time "
    L"displayed by CalClock; the Windows clock is never changed. System time is used until the first valid reply. After a later outage, the last correction remains in process memory and "
    L"synchronization is retried. NTP is the default. The automatic set chooses Czech and Slovak servers, PTB for Europe, or the global pool according to the system region. Multiple "
    L"measurements are filtered by network delay and outlying replies. Synchronize now starts a fresh measurement immediately. When servers change, the current valid correction "
    L"remains active until a new reply is obtained.",
    L"\r\n\r\nZEITQUELLE\r\nAuf der Registerkarte Zeit wird für die gesamte Anwendung und damit für alle Widgets die Windows-Systemzeit oder die Zeit der eingestellten NTP-Server "
    L"gewählt. NTP korrigiert nur die in CalClock angezeigte Zeit; die Windows-Uhr wird nie geändert. Bis zur ersten gültigen Antwort wird die Systemzeit verwendet. Bei einem späteren "
    L"Ausfall bleibt die letzte Korrektur nur im Prozessspeicher erhalten und die Synchronisierung wird wiederholt. NTP ist voreingestellt. Die automatische Gruppe wählt nach der "
    L"Systemregion die tschechisch-slowakischen Server, PTB für Europa oder den globalen Pool. Mehrere Messungen werden nach Netzverzögerung und Ausreißern gefiltert. Jetzt synchronisieren "
    L"startet sofort eine neue Messung. Beim Serverwechsel bleibt die bisherige gültige Korrektur bis zu einer neuen Antwort aktiv.",
    L"\r\n\r\nSOURCE DE L’HEURE\r\nL’onglet Heure sélectionne l’heure système Windows ou les serveurs NTP configurés pour toute l’application, donc pour tous les widgets. NTP corrige "
    L"uniquement l’heure affichée par CalClock ; l’horloge Windows n’est jamais modifiée. L’heure système est utilisée jusqu’à la première réponse valide. Après une panne ultérieure, la "
    L"dernière correction reste uniquement en mémoire du processus et la synchronisation est retentée. NTP est la valeur par défaut. Le jeu automatique choisit les serveurs tchèques et "
    L"slovaques, PTB pour l’Europe ou le pool mondial selon la région système. Plusieurs mesures sont filtrées selon le délai réseau et les réponses aberrantes. Synchroniser maintenant "
    L"lance immédiatement une nouvelle mesure. Lors d’un changement de serveur, la correction valide actuelle reste active jusqu’à une nouvelle réponse.",
    L"\r\n\r\nORIGEN DE HORA\r\nLa pestaña Hora selecciona la hora del sistema Windows o los servidores NTP configurados para toda la aplicación y, por tanto, para todos los widgets. NTP "
    L"solo corrige la hora mostrada por CalClock; el reloj de Windows nunca se modifica. Se usa la hora del sistema hasta la primera respuesta válida. Tras una interrupción posterior, la "
    L"última corrección permanece solo en la memoria del proceso y se reintenta la sincronización. NTP es el valor predeterminado. El conjunto automático elige servidores checos y "
    L"eslovacos, PTB para Europa o el grupo mundial según la región del sistema. Varias mediciones se filtran por retardo de red y respuestas atípicas. Sincronizar ahora inicia una "
    L"medición nueva de inmediato. Al cambiar servidores, la corrección válida actual sigue activa hasta obtener una respuesta nueva.",
    L"\r\n\r\nORIGINE DELL’ORA\r\nLa scheda Ora seleziona l’ora di sistema Windows o i server NTP configurati per l’intera applicazione e quindi per tutti i widget. NTP corregge solo "
    L"l’ora visualizzata da CalClock; l’orologio di Windows non viene mai modificato. L’ora di sistema viene usata fino alla prima risposta valida. Dopo una successiva interruzione, "
    L"l’ultima correzione rimane solo nella memoria del processo e la sincronizzazione viene ripetuta. NTP è l’impostazione predefinita. Il gruppo automatico sceglie i server cechi e "
    L"slovacchi, PTB per l’Europa o il pool globale in base all’area di sistema. Più misurazioni vengono filtrate in base al ritardo di rete e alle risposte anomale. Sincronizza ora "
    L"avvia subito una nuova misurazione. Cambiando server, la correzione valida corrente resta attiva fino a una nuova risposta.",
    L"\r\n\r\nŹRÓDŁO CZASU\r\nKarta Czas wybiera dla całej aplikacji, a więc dla wszystkich widżetów, czas systemowy Windows albo skonfigurowane serwery NTP. NTP koryguje wyłącznie czas "
    L"wyświetlany przez CalClock; zegar Windows nigdy nie jest zmieniany. Do pierwszej prawidłowej odpowiedzi używany jest czas systemowy. Po późniejszej awarii ostatnia korekta "
    L"pozostaje wyłącznie w pamięci procesu, a synchronizacja jest ponawiana. NTP jest ustawieniem domyślnym. Zestaw automatyczny wybiera według regionu systemu serwery czeskie i "
    L"słowackie, PTB dla Europy albo pulę globalną. Wiele pomiarów jest filtrowanych według opóźnienia sieci i wartości odstających. Synchronizuj teraz natychmiast rozpoczyna nowy "
    L"pomiar. Po zmianie serwerów bieżąca prawidłowa korekta działa do uzyskania nowej odpowiedzi.",
    L"\r\n\r\nZDROJ ČASU\r\nNa karte Čas možno pre celú aplikáciu, teda spoločne pre všetky widgety, vybrať systémový čas Windows alebo čas zo zadaných serverov NTP. NTP koriguje iba čas "
    L"zobrazený v CalClock; systémové hodiny Windows sa nikdy nemenia. Do prvej platnej odpovede sa používa systémový čas. Po neskoršom výpadku zostane posledná korekcia iba v pamäti "
    L"procesu a synchronizácia sa zopakuje. NTP je predvolené. Automatická sada vyberie podľa systémovej oblasti české a slovenské servery, PTB pre Európu alebo celosvetový fond. Viaceré "
    L"merania sa filtrujú podľa sieťového oneskorenia a odľahlých odpovedí. Synchronizovať teraz spustí nové meranie ihneď. Pri zmene serverov zostane doterajšia platná korekcia "
    L"aktívna do získania novej odpovede."
};

const wchar_t* HELP_FULLSCREEN_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nHODINY NA MONITORU\r\nDigitální hodiny mohou vyplnit jeden či více monitorů a volitelně zatemnit ostatní. Ctrl+A vybere v seznamu všechny monitory. Velikost písma "
    L"se udává procentem výšky monitoru; nastavit lze také písmo, vyhlazování, barvy a odsazení. Výchozí je bílý text na černém pozadí. Je-li otevřeno Nastavení, hodiny se vždy "
    L"zobrazují jen jako malý přesouvatelný náhled se zachovaným poměrem stran; jeho poloha se ukládá. Zarovnání do mřížky tento typ nepřesouvá ani s ním nepočítá. Esc hodiny "
    L"skryje a zatemnění odstraní i tehdy, když je aktivní Nastavení.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and optionally black out the others. Ctrl+A selects every monitor in the list. Font size is a percentage "
    L"of monitor height; font, smoothing, colours and padding are also configurable. The default is white text on black. While Settings is open, the clock is always a small draggable "
    L"preview that keeps the monitor aspect ratio, and its position is saved. Grid arrangement ignores and does not move this widget type. Esc hides the clock and removes blackouts even "
    L"when Settings is active.",
    L"\r\n\r\nMONITORUHR\r\nDie Digitaluhr kann einen oder mehrere Monitore ausfüllen und die übrigen optional abdunkeln. Strg+A wählt alle Monitore der Liste. Die Schriftgröße ist ein "
    L"Prozentsatz der Monitorhöhe; Schrift, Glättung, Farben und Innenabstand sind ebenfalls einstellbar. Voreingestellt ist Weiß auf Schwarz. Bei geöffneten Einstellungen erscheint die "
    L"Uhr stets als kleine verschiebbare Vorschau mit dem Seitenverhältnis des Monitors; ihre Position wird gespeichert. Die Rasteranordnung ignoriert diesen Widget-Typ. Esc blendet Uhr "
    L"und Abdunklung auch bei aktiven Einstellungen aus.",
    L"\r\n\r\nHORLOGE SUR MONITEUR\r\nL’horloge numérique peut remplir un ou plusieurs moniteurs et assombrir les autres. Ctrl+A sélectionne tous les moniteurs de la liste. La taille de "
    L"police est un pourcentage de la hauteur ; police, lissage, couleurs et marge sont aussi réglables. La valeur par défaut est blanc sur noir. Tant que Paramètres est ouvert, l’horloge "
    L"reste un petit aperçu déplaçable aux proportions du moniteur, dont la position est enregistrée. L’alignement en grille ignore ce type de widget. Échap masque l’horloge et retire "
    L"l’assombrissement même si Paramètres est actif.",
    L"\r\n\r\nRELOJ DE MONITOR\r\nEl reloj digital puede ocupar uno o varios monitores y oscurecer los demás. Ctrl+A selecciona todos los monitores de la lista. El tamaño de fuente es un "
    L"porcentaje de la altura; también se configuran fuente, suavizado, colores y relleno. El valor predeterminado es blanco sobre negro. Mientras Configuración está abierta, el reloj "
    L"siempre es una vista previa pequeña y móvil con la proporción del monitor, y se guarda su posición. La alineación en cuadrícula ignora este tipo. Esc oculta el reloj y elimina el "
    L"oscurecimiento incluso con Configuración activa.",
    L"\r\n\r\nOROLOGIO SU MONITOR\r\nL’orologio digitale può occupare uno o più monitor e oscurare gli altri. Ctrl+A seleziona tutti i monitor nell’elenco. La dimensione del carattere è una "
    L"percentuale dell’altezza; sono configurabili anche carattere, antialiasing, colori e margine. Il valore predefinito è bianco su nero. Con Impostazioni aperto, l’orologio resta sempre "
    L"una piccola anteprima spostabile con le proporzioni del monitor, e la posizione viene salvata. La disposizione in griglia ignora questo tipo. Esc nasconde orologio e oscuramento "
    L"anche con Impostazioni attivo.",
    L"\r\n\r\nZEGAR NA MONITORZE\r\nZegar cyfrowy może zająć jeden lub kilka monitorów i wygasić pozostałe. Ctrl+A zaznacza wszystkie monitory na liście. Rozmiar czcionki jest procentem "
    L"wysokości monitora; można też ustawić czcionkę, wygładzanie, kolory i odstęp. Domyślne są białe cyfry na czarnym tle. Gdy Ustawienia są otwarte, zegar zawsze jest małym, "
    L"przesuwanym podglądem o proporcjach monitora, a jego położenie jest zapisywane. Układanie w siatce pomija ten typ. Esc ukrywa zegar i wygaszenie również przy aktywnych Ustawieniach.",
    L"\r\n\r\nHODINY NA MONITORE\r\nDigitálne hodiny môžu vyplniť jeden alebo viac monitorov a stmaviť ostatné. Ctrl+A vyberie všetky monitory v zozname. Veľkosť písma je percentom "
    L"výšky monitora; nastaviť možno aj písmo, vyhladzovanie, farby a odsadenie. Predvolené je biele písmo na čiernom pozadí. Pri otvorenom Nastavení sú hodiny vždy iba malým "
    L"presúvateľným náhľadom s pomerom strán monitora a jeho poloha sa ukladá. Zarovnanie do mriežky tento typ ignoruje. Esc skryje hodiny aj stmavenie aj pri aktívnom Nastavení."
};

const wchar_t* ABOUT_TEXT[LANG_COUNT] = {
    L"Hodiny a kalendáře\r\n\r\nNativní Win32 aplikace pro libovolný počet samostatně nastavených plovoucích hodin a kalendářů. Ručičkový ciferník používá systémový ClockWndMain.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for any number of independently configured floating clocks and calendars. The analog face uses the system ClockWndMain.",
    L"Uhren und Kalender\r\n\r\nNative Win32-Anwendung für beliebig viele unabhängig konfigurierte schwebende Uhren und Kalender. Das Zifferblatt verwendet ClockWndMain.",
    L"Horloges et calendriers\r\n\r\nApplication Win32 native pour plusieurs horloges et calendriers flottants configurés séparément. Le cadran utilise ClockWndMain.",
    L"Relojes y calendarios\r\n\r\nAplicación Win32 nativa para varios relojes y calendarios flotantes configurados por separado. La esfera usa ClockWndMain.",
    L"Orologi e calendari\r\n\r\nApplicazione Win32 nativa per più orologi e calendari mobili configurati separatamente. Il quadrante usa ClockWndMain.",
    L"Zegary i kalendarze\r\n\r\nNatywna aplikacja Win32 obsługująca wiele niezależnie skonfigurowanych zegarów i kalendarzy. Tarcza używa ClockWndMain.",
    L"Hodiny a kalendáre\r\n\r\nNatívna aplikácia Win32 pre ľubovoľný počet samostatne nastavených plávajúcich hodín a kalendárov. Ciferník používa ClockWndMain."
};
