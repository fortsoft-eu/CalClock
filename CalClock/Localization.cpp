/**
 * This is open-source software licensed under the terms of the MIT License.
 *
 * Copyright (c) 2026 Petr Červinka - FortSoft <cervinka@fortsoft.eu>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **
 * Last modified for version 1.5.5.0
 */

#include "Localization.h"

const wchar_t* TEXT[LANG_COUNT][TXT_COUNT] = {
    {
        L"Hodiny a kalendáře",
        L"Nastavení",
        L"Přidat",
        L"Odebrat…",
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
        L"Úvodní nula:",
        L"Průhledné pozadí",
        L"Barva textu…",
        L"Barva pozadí…",
        L"Čísla týdnů",
        L"Neděle jako první den",
        L"Budík aktivní",
        L"Čas budíku:",
        L"Spustit soubor nebo příkaz",
        L"Zvuk přehrávat stále dokola",
        L"Vybrat…",
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
    }, {
        L"Clocks and calendars",
        L"Settings",
        L"Add",
        L"Remove…",
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
        L"Leading zero:",
        L"Transparent background",
        L"Text color…",
        L"Background color…",
        L"Week numbers",
        L"Sunday first",
        L"Alarm enabled",
        L"Alarm time:",
        L"Run a file or command",
        L"Loop audio continuously",
        L"Browse…",
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
    }, {
        L"Uhren und Kalender",
        L"Einstellungen",
        L"Hinzufügen",
        L"Entfernen…",
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
        L"Führende Null:",
        L"Transparenter Hintergrund",
        L"Textfarbe…",
        L"Hintergrundfarbe…",
        L"Wochennummern",
        L"Sonntag zuerst",
        L"Wecker aktiv",
        L"Weckzeit:",
        L"Datei oder Befehl starten",
        L"Audio endlos wiederholen",
        L"Durchsuchen…",
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
    }, {
        L"Horloges et calendriers",
        L"Paramètres",
        L"Ajouter",
        L"Supprimer…",
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
        L"Zéro initial:",
        L"Fond transparent",
        L"Couleur du texte…",
        L"Couleur du fond…",
        L"Numéros de semaine",
        L"Dimanche en premier",
        L"Alarme active",
        L"Heure de l’alarme :",
        L"Lancer un fichier ou une commande",
        L"Lire le son en boucle",
        L"Parcourir…",
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
    }, {
        L"Relojes y calendarios",
        L"Configuración",
        L"Añadir",
        L"Quitar…",
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
        L"Cero inicial:",
        L"Fondo transparente",
        L"Color de texto…",
        L"Color de fondo…",
        L"Números de semana",
        L"Domingo primero",
        L"Alarma activa",
        L"Hora de alarma:",
        L"Ejecutar archivo o comando",
        L"Repetir audio continuamente",
        L"Examinar…",
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
    }, {
        L"Orologi e calendari",
        L"Impostazioni",
        L"Aggiungi",
        L"Rimuovi…",
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
        L"Zero iniziale:",
        L"Sfondo trasparente",
        L"Colore testo…",
        L"Colore sfondo…",
        L"Numeri settimana",
        L"Domenica per prima",
        L"Sveglia attiva",
        L"Ora sveglia:",
        L"Esegui file o comando",
        L"Ripeti audio continuamente",
        L"Sfoglia…",
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
    }, {
        L"Zegary i kalendarze",
        L"Ustawienia",
        L"Dodaj",
        L"Usuń…",
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
        L"Zero wiodące:",
        L"Przezroczyste tło",
        L"Kolor tekstu…",
        L"Kolor tła…",
        L"Numery tygodni",
        L"Niedziela pierwsza",
        L"Alarm aktywny",
        L"Czas alarmu:",
        L"Uruchom plik lub polecenie",
        L"Powtarzaj dźwięk",
        L"Wybierz…",
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
    }, {
        L"Hodiny a kalendáre",
        L"Nastavenia",
        L"Pridať",
        L"Odobrať…",
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
        L"Úvodná nula:",
        L"Priehľadné pozadie",
        L"Farba textu…",
        L"Farba pozadia…",
        L"Čísla týždňov",
        L"Nedeľa ako prvý deň",
        L"Budík aktívny",
        L"Čas budíka:",
        L"Spustiť súbor alebo príkaz",
        L"Zvuk prehrávať dookola",
        L"Vybrať…",
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
    }, {
        L"Clocks and calendars",
        L"Settings",
        L"Add",
        L"Remove…",
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
        L"Leading zero:",
        L"Transparent background",
        L"Text color…",
        L"Background color…",
        L"Week numbers",
        L"Sunday first",
        L"Alarm enabled",
        L"Alarm time:",
        L"Run a file or command",
        L"Loop audio continuously",
        L"Browse…",
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
    }, {
        L"Clocks and calendars",
        L"Settings",
        L"Add",
        L"Remove…",
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
        L"Leading zero:",
        L"Transparent background",
        L"Text color…",
        L"Background color…",
        L"Week numbers",
        L"Sunday first",
        L"Alarm enabled",
        L"Alarm time:",
        L"Run a file or command",
        L"Loop audio continuously",
        L"Browse…",
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
    }, {
        L"Relógios e calendários",
        L"Definições",
        L"Adicionar",
        L"Remover…",
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
        L"Zero à esquerda:",
        L"Fundo transparente",
        L"Cor do texto…",
        L"Cor de fundo…",
        L"Números das semanas",
        L"Domingo primeiro",
        L"Alarme ativo",
        L"Hora do alarme:",
        L"Executar um ficheiro ou comando",
        L"Repetir áudio continuamente",
        L"Procurar…",
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
    }, {
        L"Klokker og kalendere",
        L"Innstillinger",
        L"Legg til",
        L"Fjern…",
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
        L"Innledende null:",
        L"Gjennomsiktig bakgrunn",
        L"Tekstfarge…",
        L"Bakgrunnsfarge…",
        L"Ukenumre",
        L"Søndag først",
        L"Alarm aktiv",
        L"Alarmtid:",
        L"Kjør en fil eller kommando",
        L"Gjenta lyd kontinuerlig",
        L"Bla gjennom…",
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
    }, {
        L"Klockor och kalendrar",
        L"Inställningar",
        L"Lägg till",
        L"Ta bort…",
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
        L"Inledande nolla:",
        L"Genomskinlig bakgrund",
        L"Textfärg…",
        L"Bakgrundsfärg…",
        L"Veckonummer",
        L"Söndag först",
        L"Alarm aktivt",
        L"Alarmtid:",
        L"Kör en fil eller ett kommando",
        L"Upprepa ljud kontinuerligt",
        L"Bläddra…",
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
    }, {
        L"Kellot ja kalenterit",
        L"Asetukset",
        L"Lisää",
        L"Poista…",
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
        L"Etunolla:",
        L"Läpinäkyvä tausta",
        L"Tekstin väri…",
        L"Taustaväri…",
        L"Viikkonumerot",
        L"Sunnuntai ensin",
        L"Herätys käytössä",
        L"Herätysaika:",
        L"Suorita tiedosto tai komento",
        L"Toista ääntä jatkuvasti",
        L"Selaa…",
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
    }, {
        L"Ure og kalendere",
        L"Indstillinger",
        L"Tilføj",
        L"Fjern…",
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
        L"Foranstillet nul:",
        L"Gennemsigtig baggrund",
        L"Tekstfarve…",
        L"Baggrundsfarve…",
        L"Ugenumre",
        L"Søndag først",
        L"Alarm aktiv",
        L"Alarmtid:",
        L"Kør en fil eller kommando",
        L"Gentag lyd kontinuerligt",
        L"Gennemse…",
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
    }, {
        L"Klukkur og dagatöl",
        L"Stillingar",
        L"Bæta við",
        L"Fjarlægja…",
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
        L"Núll fremst:",
        L"Gegnsær bakgrunnur",
        L"Textalitur…",
        L"Bakgrunnslitur…",
        L"Vikunúmer",
        L"Sunnudagur fyrst",
        L"Vekjari virkur",
        L"Tími vekjara:",
        L"Keyra skrá eða skipun",
        L"Endurtaka hljóð stöðugt",
        L"Velja…",
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
    }, {
        L"Saatler ve takvimler",
        L"Ayarlar",
        L"Ekle",
        L"Kaldır…",
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
        L"Baştaki sıfır:",
        L"Saydam arka plan",
        L"Metin rengi…",
        L"Arka plan rengi…",
        L"Hafta numaraları",
        L"Pazar ilk gün",
        L"Alarm etkin",
        L"Alarm saati:",
        L"Dosya veya komut çalıştır",
        L"Sesi sürekli yinele",
        L"Gözat…",
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

const wchar_t* WIDGET_LIMIT_MESSAGES[LANG_COUNT] = {
    L"Maximální počet widgetů je %d.",
    L"The maximum number of widgets is %d.",
    L"Die maximale Anzahl an Widgets beträgt %d.",
    L"Le nombre maximal de widgets est de %d.",
    L"El número máximo de widgets es %d.",
    L"Il numero massimo di widget è %d.",
    L"Maksymalna liczba widżetów wynosi %d.",
    L"Maximálny počet widgetov je %d.",
    L"The maximum number of widgets is %d.",
    L"The maximum number of widgets is %d.",
    L"O número máximo de widgets é %d.",
    L"Maksimalt antall widgeter er %d.",
    L"Det maximala antalet widgetar är %d.",
    L"Pienoisohjelmien enimmäismäärä on %d.",
    L"Det maksimale antal widgets er %d.",
    L"Hámarksfjöldi græja er %d.",
    L"En fazla %d araç kullanılabilir."
};

const wchar_t* WIDGET_COPY_SUFFIXES[LANG_COUNT] = {
    L" - kopie",
    L" - copy",
    L" - Kopie",
    L" - copie",
    L" - copia",
    L" - copia",
    L" - kopia",
    L" - kópia",
    L" - copy",
    L" - copy",
    L" - cópia",
    L" - kopi",
    L" - kopia",
    L" - kopio",
    L" - kopi",
    L" - afrit",
    L" - kopya"
};

const wchar_t* XML_FILE_TYPE_LABELS[LANG_COUNT] = {
    L"Rozšiřitelný značkovací jazyk (*.xml)",
    L"Extensible Markup Language (*.xml)",
    L"Erweiterbare Auszeichnungssprache (*.xml)",
    L"Langage de balisage extensible (*.xml)",
    L"Lenguaje de marcado extensible (*.xml)",
    L"Linguaggio di marcatura estensibile (*.xml)",
    L"Rozszerzalny język znaczników (*.xml)",
    L"Rozšíriteľný značkovací jazyk (*.xml)",
    L"Extensible Markup Language (*.xml)",
    L"Extensible Markup Language (*.xml)",
    L"Linguagem de marcação extensível (*.xml)",
    L"Utvidbart markeringsspråk (*.xml)",
    L"Utökningsbart märkspråk (*.xml)",
    L"Laajennettava merkintäkieli (*.xml)",
    L"Udvideligt opmærkningssprog (*.xml)",
    L"Útvíkkanlegt ívafsmál (*.xml)",
    L"Genişletilebilir işaretleme dili (*.xml)"
};

const wchar_t* CSV_FILE_TYPE_LABELS[LANG_COUNT] = {
    L"Čárkami oddělené hodnoty (*.csv)",
    L"Comma Separated Values (*.csv)",
    L"Durch Kommas getrennte Werte (*.csv)",
    L"Valeurs séparées par des virgules (*.csv)",
    L"Valores separados por comas (*.csv)",
    L"Valori separati da virgole (*.csv)",
    L"Wartości rozdzielane przecinkami (*.csv)",
    L"Hodnoty oddelené čiarkami (*.csv)",
    L"Comma Separated Values (*.csv)",
    L"Comma Separated Values (*.csv)",
    L"Valores separados por vírgulas (*.csv)",
    L"Kommaseparerte verdier (*.csv)",
    L"Kommaseparerade värden (*.csv)",
    L"Pilkuilla erotetut arvot (*.csv)",
    L"Kommaseparerede værdier (*.csv)",
    L"Gildi aðskilin með kommum (*.csv)",
    L"Virgülle ayrılmış değerler (*.csv)"
};

const wchar_t* COMMAND_FILE_FILTERS[LANG_COUNT] = {
    L"Zvuk a programy\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Všechny "
    L"soubory\0*.*\0",
    L"Audio and programs\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0All "
    L"files\0*.*\0",
    L"Audio und Programme\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Alle "
    L"Dateien\0*.*\0",
    L"Audio et programmes\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Tous les "
    L"fichiers\0*.*\0",
    L"Audio y programas\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Todos los "
    L"archivos\0*.*\0",
    L"Audio e programmi\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Tutti i "
    L"file\0*.*\0",
    L"Dźwięk i programy\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Wszystkie "
    L"pliki\0*.*\0",
    L"Zvuk a programy\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Všetky "
    L"súbory\0*.*\0",
    L"Audio and programs\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0All "
    L"files\0*.*\0",
    L"Audio and programs\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0All "
    L"files\0*.*\0",
    L"Áudio e programas\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Todos os "
    L"ficheiros\0*.*\0",
    L"Lyd og programmer\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Alle "
    L"filer\0*.*\0",
    L"Ljud och program\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Alla "
    L"filer\0*.*\0",
    L"Ääni ja ohjelmat\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Kaikki "
    L"tiedostot\0*.*\0",
    L"Lyd og programmer\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Alle "
    L"filer\0*.*\0",
    L"Hljóð og forrit\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Allar "
    L"skrár\0*.*\0",
    L"Ses ve programlar\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Tüm "
    L"dosyalar\0*.*\0"
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
    L"Vybrat &písmo…",
    L"Choose &font…",
    L"&Schriftart wählen…",
    L"Choisir la &police…",
    L"Elegir &fuente…",
    L"Scegli &carattere…",
    L"Wybierz &czcionkę…",
    L"Vybrať &písmo…",
    L"Choose &font…",
    L"Choose &font…",
    L"Escolher &tipo de letra…",
    L"Velg &skrift…",
    L"Välj &teckensnitt…",
    L"Valitse &fontti…",
    L"Vælg &skrifttype…",
    L"Velja &letur…",
    L"&Yazı tipi seç…"
};

const wchar_t* CALENDAR_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &kalendáře…",
    L"&Calendar font…",
    L"&Kalenderschrift…",
    L"Police du &calendrier…",
    L"Fuente del &calendario…",
    L"Carattere del &calendario…",
    L"Czcionka &kalendarza…",
    L"Písmo &kalendára…",
    L"&Calendar font…",
    L"&Calendar font…",
    L"Tipo de letra do &calendário…",
    L"&Kalenderskrift…",
    L"&Kalenderteckensnitt…",
    L"&Kalenterin fontti…",
    L"&Kalenderskrifttype…",
    L"Letur &dagatals…",
    L"&Takvim yazı tipi…"
};

const wchar_t* PANEL_TOP_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &horního řádku…",
    L"&Top row font…",
    L"Schrift der &oberen Zeile…",
    L"Police de la ligne &supérieure…",
    L"Fuente de la línea &superior…",
    L"Carattere riga &superiore…",
    L"Czcionka &górnego wiersza…",
    L"Písmo &horného riadka…",
    L"&Top row font…",
    L"&Top row font…",
    L"Tipo de letra da linha &superior…",
    L"Skrift for &øverste rad…",
    L"Teckensnitt för &översta raden…",
    L"&Ylärivin fontti…",
    L"Skrifttype for &øverste linje…",
    L"Letur &efri línu…",
    L"&Üst satır yazı tipi…"
};

const wchar_t* SHOW_TODAY_LABELS[LANG_COUNT] = {
    L"Řádek Dnes",
    L"Today row",
    L"Heute-Zeile",
    L"Ligne Aujourd’hui",
    L"Fila Hoy",
    L"Riga Oggi",
    L"Wiersz Dzisiaj",
    L"Riadok Dnes",
    L"Today row",
    L"Today row",
    L"Linha Hoje",
    L"I dag-raden",
    L"Raden I dag",
    L"Tänään-rivi",
    L"Rækken I dag",
    L"Línan Í dag",
    L"Bugün satırı"
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
    L"Písmo č&asu…",
    L"&Time font…",
    L"&Zeitschrift…",
    L"Police de l’&heure…",
    L"Fuente de la &hora…",
    L"Carattere dell’&ora…",
    L"Czcionka &czasu…",
    L"Písmo č&asu…",
    L"&Time font…",
    L"&Time font…",
    L"Tipo de letra da &hora…",
    L"&Tidsskrift…",
    L"&Tidsteckensnitt…",
    L"&Ajan fontti…",
    L"Skrifttype for &tid…",
    L"Letur &tíma…",
    L"&Saat yazı tipi…"
};

const wchar_t* PANEL_BOTTOM_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &spodního řádku…",
    L"&Bottom row font…",
    L"Schrift der &unteren Zeile…",
    L"Police de la ligne &inférieure…",
    L"Fuente de la línea &inferior…",
    L"Carattere riga &inferiore…",
    L"Czcionka &dolnego wiersza…",
    L"Písmo &spodného riadka…",
    L"&Bottom row font…",
    L"&Bottom row font…",
    L"Tipo de letra da linha &inferior…",
    L"Skrift for &nederste rad…",
    L"Teckensnitt för &nedersta raden…",
    L"&Alarivin fontti…",
    L"Skrifttype for &nederste linje…",
    L"Letur &neðri línu…",
    L"&Alt satır yazı tipi…"
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
    L"Barva &textu budíku…",
    L"Alarm &text color…",
    L"&Wecker-Textfarbe…",
    L"Couleur du &texte d’alarme…",
    L"Color del &texto de alarma…",
    L"Colore &testo sveglia…",
    L"Kolor &tekstu alarmu…",
    L"Farba &textu budíka…",
    L"Alarm &text color…",
    L"Alarm &text color…",
    L"Cor do &texto do alarme…",
    L"Alarmens &tekstfarge…",
    L"Alarmets &textfärg…",
    L"Herätyksen &tekstiväri…",
    L"Alarmens &tekstfarve…",
    L"&Textalitur vekjara…",
    L"Alarm &metin rengi…"
};

const wchar_t* ALARM_BACKGROUND_COLOR_LABELS[LANG_COUNT] = {
    L"Barva &pozadí budíku…",
    L"Alarm &background…",
    L"Wecker-&Hintergrund…",
    L"&Fond de l’alarme…",
    L"&Fondo de alarma…",
    L"&Sfondo sveglia…",
    L"&Tło alarmu…",
    L"Farba &pozadia budíka…",
    L"Alarm &background…",
    L"Alarm &background…",
    L"Cor de &fundo do alarme…",
    L"Alarmens &bakgrunn…",
    L"Alarmets &bakgrund…",
    L"Herätyksen &tausta…",
    L"Alarmens &baggrund…",
    L"&Bakgrunnslitur vekjara…",
    L"Alarm &arka planı…"
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
    L"Barva rámečku…",
    L"Border color…",
    L"Rahmenfarbe…",
    L"Couleur de bordure…",
    L"Color del borde…",
    L"Colore bordo…",
    L"Kolor ramki…",
    L"Farba rámčeka…",
    L"Border colour…",
    L"Border colour…",
    L"Cor da moldura…",
    L"Rammefarge…",
    L"Ramfärg…",
    L"Reunuksen väri…",
    L"Rammefarve…",
    L"Litur ramma…",
    L"Çerçeve rengi…"
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

const wchar_t* ADDITIONAL_CLOCK_NAME_FORMATS[LANG_COUNT] = {
    L"Hodiny %d",
    L"Clock %d",
    L"Uhr %d",
    L"Horloge %d",
    L"Reloj %d",
    L"Orologio %d",
    L"Zegar %d",
    L"Hodiny %d",
    L"Clock %d",
    L"Clock %d",
    L"Relógio %d",
    L"Klokke %d",
    L"Klocka %d",
    L"Kello %d",
    L"Ur %d",
    L"Klukka %d",
    L"Saat %d"
};

const wchar_t* ADDITIONAL_CLOCK_SHOW_FORMATS[LANG_COUNT] = {
    L"Zobrazit hodiny %d",
    L"Show clock %d",
    L"Uhr %d anzeigen",
    L"Afficher l’horloge %d",
    L"Mostrar reloj %d",
    L"Mostra orologio %d",
    L"Pokaż zegar %d",
    L"Zobraziť hodiny %d",
    L"Show clock %d",
    L"Show clock %d",
    L"Mostrar relógio %d",
    L"Vis klokke %d",
    L"Visa klocka %d",
    L"Näytä kello %d",
    L"Vis ur %d",
    L"Sýna klukku %d",
    L"Saat %d göster"
};

const wchar_t* TIME_FORMAT_LABELS[LANG_COUNT] = {
    L"Formát času:",
    L"Time format:",
    L"Zeitformat:",
    L"Format de l’heure :",
    L"Formato de hora:",
    L"Formato ora:",
    L"Format czasu:",
    L"Formát času:",
    L"Time format:",
    L"Time format:",
    L"Formato da hora:",
    L"Tidsformat:",
    L"Tidsformat:",
    L"Aikamuoto:",
    L"Tidsformat:",
    L"Tímasnið:",
    L"Saat biçimi:"
};

const wchar_t* TIME_FORMAT_MODE_LABELS[LANG_COUNT][TIME_FORMAT_COUNT] = {
    { L"Podle jazyka", L"12 hodin", L"24 hodin" },
    { L"Language default", L"12 hours", L"24 hours" },
    { L"Nach Sprache", L"12 Stunden", L"24 Stunden" },
    { L"Selon la langue", L"12 heures", L"24 heures" },
    { L"Según el idioma", L"12 horas", L"24 horas" },
    { L"Secondo la lingua", L"12 ore", L"24 ore" },
    { L"Według języka", L"12 godzin", L"24 godziny" },
    { L"Podľa jazyka", L"12 hodín", L"24 hodín" },
    { L"Language default", L"12 hours", L"24 hours" },
    { L"Language default", L"12 hours", L"24 hours" },
    { L"Conforme o idioma", L"12 horas", L"24 horas" },
    { L"Etter språk", L"12 timer", L"24 timer" },
    { L"Enligt språk", L"12 timmar", L"24 timmar" },
    { L"Kielen mukaan", L"12 tuntia", L"24 tuntia" },
    { L"Efter sprog", L"12 timer", L"24 timer" },
    { L"Samkvæmt tungumáli", L"12 klukkustundir", L"24 klukkustundir" },
    { L"Dile göre", L"12 saat", L"24 saat" }
};

const wchar_t* LEADING_ZERO_MODE_LABELS[LANG_COUNT][LEADING_ZERO_MODE_COUNT] = {
    { L"Zobrazit", L"S místem", L"Bez místa" },
    { L"Show", L"Keep space", L"No space" },
    { L"Anzeigen", L"Platz freihalten", L"Ohne Platz" },
    { L"Afficher", L"Garder la place", L"Sans espace" },
    { L"Mostrar", L"Reservar espacio", L"Sin espacio" },
    { L"Mostra", L"Riserva spazio", L"Senza spazio" },
    { L"Pokaż", L"Zachowaj miejsce", L"Bez miejsca" },
    { L"Zobraziť", L"S miestom", L"Bez miesta" },
    { L"Show", L"Keep space", L"No space" },
    { L"Show", L"Keep space", L"No space" },
    { L"Mostrar", L"Reservar espaço", L"Sem espaço" },
    { L"Vis", L"Behold plass", L"Uten plass" },
    { L"Visa", L"Behåll utrymme", L"Utan utrymme" },
    { L"Näytä", L"Varaa tila", L"Ilman tilaa" },
    { L"Vis", L"Bevar plads", L"Uden plads" },
    { L"Sýna", L"Halda plássi", L"Án pláss" },
    { L"Göster", L"Yer ayır", L"Yer ayırma" }
};

const wchar_t* TIME_SIGNAL_SOUND_LABELS[LANG_COUNT] = {
    L"Zvuk časového znamení:",
    L"Time signal sound:",
    L"Klang des Zeitzeichens:",
    L"Son du signal horaire :",
    L"Sonido de la señal horaria:",
    L"Suono del segnale orario:",
    L"Dźwięk sygnału czasu:",
    L"Zvuk časového znamenia:",
    L"Time signal sound:",
    L"Time signal sound:",
    L"Som do sinal horário:",
    L"Lyd for tidssignal:",
    L"Ljud för tidssignal:",
    L"Aikamerkin ääni:",
    L"Lyd for tidssignal:",
    L"Hljóð tímamerkis:",
    L"Zaman sinyali sesi:"
};


const wchar_t* ALARM_VOLUME_LABELS[LANG_COUNT] = {
    L"Hlasitost zvuku:",
    L"Audio volume:",
    L"Audiolautstärke:",
    L"Volume audio :",
    L"Volumen de audio:",
    L"Volume audio:",
    L"Głośność dźwięku:",
    L"Hlasitosť zvuku:",
    L"Audio volume:",
    L"Audio volume:",
    L"Volume do áudio:",
    L"Lydvolum:",
    L"Ljudvolym:",
    L"Äänenvoimakkuus:",
    L"Lydstyrke:",
    L"Hljóðstyrkur:",
    L"Ses düzeyi:"
};

const wchar_t* TIME_SIGNAL_VOLUME_LABELS[LANG_COUNT] = {
    L"Hlasitost časového znamení:",
    L"Time signal volume:",
    L"Lautstärke des Zeitzeichens:",
    L"Volume du signal horaire :",
    L"Volumen de la señal horaria:",
    L"Volume del segnale orario:",
    L"Głośność sygnału czasu:",
    L"Hlasitosť časového znamenia:",
    L"Time signal volume:",
    L"Time signal volume:",
    L"Volume do sinal horário:",
    L"Volum for tidssignal:",
    L"Volym för tidssignal:",
    L"Aikamerkin äänenvoimakkuus:",
    L"Lydstyrke for tidssignal:",
    L"Hljóðstyrkur tímamerkis:",
    L"Zaman sinyali ses düzeyi:"
};

const wchar_t* TIME_SIGNAL_SYSTEM_SOUND_LABELS[LANG_COUNT] = {
    L"Systémové pípání",
    L"System beep",
    L"Systemsignalton",
    L"Bip système",
    L"Pitido del sistema",
    L"Segnale acustico di sistema",
    L"Sygnał systemowy",
    L"Systémové pípanie",
    L"System beep",
    L"System beep",
    L"Sinal sonoro do sistema",
    L"Systempip",
    L"Systempip",
    L"Järjestelmän äänimerkki",
    L"Systembip",
    L"Kerfishljóð",
    L"Sistem bip sesi"
};

const wchar_t* TIME_SIGNAL_GENERATED_SOUND_LABELS[LANG_COUNT] = {
    L"Vlastní generátor",
    L"Built-in generator",
    L"Interner Generator",
    L"Générateur intégré",
    L"Generador integrado",
    L"Generatore integrato",
    L"Wbudowany generator",
    L"Vlastný generátor",
    L"Built-in generator",
    L"Built-in generator",
    L"Gerador integrado",
    L"Innebygd generator",
    L"Inbyggd generator",
    L"Sisäinen generaattori",
    L"Indbygget generator",
    L"Innbyggður hljóðgjafi",
    L"Yerleşik üreteç"
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

const wchar_t* TIME_SIGNAL_ENABLED_LABELS[LANG_COUNT] = {
    L"Časové znamení &aktivní",
    L"Time signal &active",
    L"Zeitzeichen &aktiv",
    L"Signal horaire &actif",
    L"Señal horaria &activa",
    L"Segnale orario &attivo",
    L"Sygnał czasu &aktywny",
    L"Časové znamenie &aktívne",
    L"Time signal &active",
    L"Time signal &active",
    L"Sinal horário &ativo",
    L"Tidssignal &aktivt",
    L"Tidssignal &aktiv",
    L"Äänimerkki &käytössä",
    L"Tidssignal &aktivt",
    L"Tímamerki &virkt",
    L"Zaman sinyali &etkin"
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
    }, {
        L"None",
        L"Every minute",
        L"Every 5 minutes",
        L"Every 10 minutes",
        L"Every quarter hour",
        L"Every 20 minutes",
        L"Every half hour",
        L"Every hour"
    }, {
        L"Kein",
        L"Jede Minute",
        L"Alle 5 Minuten",
        L"Alle 10 Minuten",
        L"Jede Viertelstunde",
        L"Alle 20 Minuten",
        L"Jede halbe Stunde",
        L"Jede Stunde"
    }, {
        L"Aucun",
        L"Chaque minute",
        L"Toutes les 5 minutes",
        L"Toutes les 10 minutes",
        L"Chaque quart d’heure",
        L"Toutes les 20 minutes",
        L"Chaque demi-heure",
        L"Chaque heure"
    }, {
        L"Ninguno",
        L"Cada minuto",
        L"Cada 5 minutos",
        L"Cada 10 minutos",
        L"Cada cuarto de hora",
        L"Cada 20 minutos",
        L"Cada media hora",
        L"Cada hora"
    }, {
        L"Nessuno",
        L"Ogni minuto",
        L"Ogni 5 minuti",
        L"Ogni 10 minuti",
        L"Ogni quarto d’ora",
        L"Ogni 20 minuti",
        L"Ogni mezz’ora",
        L"Ogni ora"
    }, {
        L"Brak",
        L"Co minutę",
        L"Co 5 minut",
        L"Co 10 minut",
        L"Co kwadrans",
        L"Co 20 minut",
        L"Co pół godziny",
        L"Co godzinę"
    }, {
        L"Žiadne",
        L"Každú minútu",
        L"Každých 5 minút",
        L"Každých 10 minút",
        L"Každú štvrťhodinu",
        L"Každých 20 minút",
        L"Každú polhodinu",
        L"Každú hodinu"
    }, {
        L"None",
        L"Every minute",
        L"Every 5 minutes",
        L"Every 10 minutes",
        L"Every quarter hour",
        L"Every 20 minutes",
        L"Every half hour",
        L"Every hour"
    }, {
        L"None",
        L"Every minute",
        L"Every 5 minutes",
        L"Every 10 minutes",
        L"Every quarter hour",
        L"Every 20 minutes",
        L"Every half hour",
        L"Every hour"
    }, {
        L"Nenhum",
        L"A cada minuto",
        L"A cada 5 minutos",
        L"A cada 10 minutos",
        L"A cada quarto de hora",
        L"A cada 20 minutos",
        L"A cada meia hora",
        L"A cada hora"
    }, {
        L"Ingen",
        L"Hvert minutt",
        L"Hvert 5. minutt",
        L"Hvert 10. minutt",
        L"Hvert kvarter",
        L"Hvert 20. minutt",
        L"Hver halvtime",
        L"Hver time"
    }, {
        L"Ingen",
        L"Varje minut",
        L"Var 5:e minut",
        L"Var 10:e minut",
        L"Varje kvart",
        L"Var 20:e minut",
        L"Varje halvtimme",
        L"Varje timme"
    }, {
        L"Ei mitään",
        L"Minuutin välein",
        L"5 minuutin välein",
        L"10 minuutin välein",
        L"15 minuutin välein",
        L"20 minuutin välein",
        L"30 minuutin välein",
        L"Tunnin välein"
    }, {
        L"Intet",
        L"Hvert minut",
        L"Hvert 5. minut",
        L"Hvert 10. minut",
        L"Hvert kvarter",
        L"Hvert 20. minut",
        L"Hver halve time",
        L"Hver time"
    }, {
        L"Ekkert",
        L"Á hverri mínútu",
        L"Á 5 mínútna fresti",
        L"Á 10 mínútna fresti",
        L"Á stundarfjórðungs fresti",
        L"Á 20 mínútna fresti",
        L"Á hálftíma fresti",
        L"Á klukkustundar fresti"
    }, {
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
    L"Greenwich Time Signal (GTS): pět krátkých tónů zazní v posledních pěti sekundách a dlouhý tón přesně "
    L"na zvolené časové hranici. Souběžná "
    L"znamení více widgetů se přehrají pouze jednou.",
    L"Greenwich Time Signal (GTS): five short pips sound during the final five seconds and a long pip "
    L"exactly at the selected time boundary. "
    L"Coincident signals from multiple widgets play only once.",
    L"Greenwich Time Signal (GTS): fünf kurze Töne erklingen in den letzten fünf Sekunden und ein langer Ton "
    L"genau an der gewählten Zeitgrenze. "
    L"Gleichzeitige Signale mehrerer Widgets werden nur einmal wiedergegeben.",
    L"Greenwich Time Signal (GTS): cinq bips courts retentissent pendant les cinq dernières secondes et un "
    L"bip long exactement à la limite choisie. "
    L"Les signaux simultanés de plusieurs widgets ne sont joués qu’une fois.",
    L"Greenwich Time Signal (GTS): cinco pitidos cortos suenan durante los últimos cinco segundos y uno "
    L"largo exactamente en el límite elegido. Las "
    L"señales simultáneas de varios widgets se reproducen una sola vez.",
    L"Greenwich Time Signal (GTS): cinque segnali brevi suonano negli ultimi cinque secondi e uno lungo "
    L"esattamente al limite scelto. I segnali "
    L"simultanei di più widget vengono riprodotti una sola volta.",
    L"Greenwich Time Signal (GTS): pięć krótkich sygnałów rozlega się w ostatnich pięciu sekundach, a długi "
    L"dokładnie na wybranej granicy czasu. "
    L"Zbieżne sygnały wielu widżetów są odtwarzane tylko raz.",
    L"Greenwich Time Signal (GTS): päť krátkych tónov zaznie v posledných piatich sekundách a dlhý tón "
    L"presne na zvolenej časovej hranici. Súbežné "
    L"znamenia viacerých widgetov sa prehrajú iba raz.",
    L"Greenwich Time Signal (GTS): five short pips sound during the final five seconds and a long pip "
    L"exactly at the selected time boundary. "
    L"Coincident signals from multiple widgets play only once.",
    L"Greenwich Time Signal (GTS): five short pips sound during the final five seconds and a long pip "
    L"exactly at the selected time boundary. "
    L"Coincident signals from multiple widgets play only once.",
    L"Greenwich Time Signal (GTS): cinco sinais curtos soam nos últimos cinco segundos e um sinal longo "
    L"exatamente no limite escolhido. Sinais "
    L"coincidentes de vários widgets são reproduzidos apenas uma vez.",
    L"Greenwich Time Signal (GTS): fem korte pip høres i de siste fem sekundene og et langt pip nøyaktig på "
    L"den valgte tidsgrensen. Samtidige "
    L"signaler fra flere widgeter spilles bare én gang.",
    L"Greenwich Time Signal (GTS): fem korta pip hörs under de sista fem sekunderna och ett långt pip exakt "
    L"vid den valda tidsgränsen. Samtidiga "
    L"signaler från flera widgetar spelas bara en gång.",
    L"Greenwich Time Signal (GTS): viisi lyhyttä äänimerkkiä kuuluu viimeisten viiden sekunnin aikana ja "
    L"pitkä merkki täsmälleen valitulla "
    L"aikarajalla. Samanaikaiset merkit toistetaan vain kerran.",
    L"Greenwich Time Signal (GTS): fem korte bip lyder i de sidste fem sekunder og et langt bip præcis ved "
    L"den valgte tidsgrænse. Samtidige "
    L"signaler fra flere widgets afspilles kun én gang.",
    L"Greenwich Time Signal (GTS): fimm stutt píp hljóma síðustu fimm sekúndurnar og langt píp nákvæmlega á "
    L"völdum tímamörkum. Samtímamerki frá "
    L"mörgum græjum eru aðeins spiluð einu sinni.",
    L"Greenwich Time Signal (GTS): son beş saniyede beş kısa ses ve seçili zaman sınırında tam olarak bir "
    L"uzun ses çalar. Birden çok aracın çakışan "
    L"sinyalleri yalnızca bir kez çalınır."
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
    }, {
        L"Automatic by region",
        L"Czechia and Slovakia – CESNET/NIC.CZ",
        L"PTB – Germany and Europe",
        L"Worldwide – Ubuntu / NTP Pool",
        L"Custom"
    }, {
        L"Automatisch nach Region",
        L"Tschechien und Slowakei – CESNET/NIC.CZ",
        L"PTB – Deutschland und Europa",
        L"Weltweit – Ubuntu / NTP Pool",
        L"Benutzerdefiniert"
    }, {
        L"Automatique selon la région",
        L"Tchéquie et Slovaquie – CESNET/NIC.CZ",
        L"PTB – Allemagne et Europe",
        L"Monde entier – Ubuntu / NTP Pool",
        L"Personnalisé"
    }, {
        L"Automático según la región",
        L"Chequia y Eslovaquia – CESNET/NIC.CZ",
        L"PTB – Alemania y Europa",
        L"Todo el mundo – Ubuntu / NTP Pool",
        L"Personalizado"
    }, {
        L"Automatico in base all’area",
        L"Cechia e Slovacchia – CESNET/NIC.CZ",
        L"PTB – Germania ed Europa",
        L"Tutto il mondo – Ubuntu / NTP Pool",
        L"Personalizzato"
    }, {
        L"Automatycznie według regionu",
        L"Czechy i Słowacja – CESNET/NIC.CZ",
        L"PTB – Niemcy i Europa",
        L"Cały świat – Ubuntu / NTP Pool",
        L"Własny"
    }, {
        L"Automaticky podľa oblasti",
        L"Česko a Slovensko – CESNET/NIC.CZ",
        L"PTB – Nemecko a Európa",
        L"Celý svet – Ubuntu / NTP Pool",
        L"Vlastné"
    }, {
        L"Automatic by region",
        L"Czechia and Slovakia – CESNET/NIC.CZ",
        L"PTB – Germany and Europe",
        L"Worldwide – Ubuntu / NTP Pool",
        L"Custom"
    }, {
        L"Automatic by region",
        L"Czechia and Slovakia – CESNET/NIC.CZ",
        L"PTB – Germany and Europe",
        L"Worldwide – Ubuntu / NTP Pool",
        L"Custom"
    }, {
        L"Automático por região",
        L"Chéquia e Eslováquia – CESNET/NIC.CZ",
        L"PTB – Alemanha e Europa",
        L"Mundial – Ubuntu / NTP Pool",
        L"Personalizado"
    }, {
        L"Automatisk etter region",
        L"Tsjekkia og Slovakia – CESNET/NIC.CZ",
        L"PTB – Tyskland og Europa",
        L"Hele verden – Ubuntu / NTP Pool",
        L"Egendefinert"
    }, {
        L"Automatiskt efter region",
        L"Tjeckien och Slovakien – CESNET/NIC.CZ",
        L"PTB – Tyskland och Europa",
        L"Hela världen – Ubuntu / NTP Pool",
        L"Anpassad"
    }, {
        L"Automaattinen alueen mukaan",
        L"Tšekki ja Slovakia – CESNET/NIC.CZ",
        L"PTB – Saksa ja Eurooppa",
        L"Maailmanlaajuinen – Ubuntu / NTP Pool",
        L"Mukautettu"
    }, {
        L"Automatisk efter område",
        L"Tjekkiet og Slovakiet – CESNET/NIC.CZ",
        L"PTB – Tyskland og Europa",
        L"Hele verden – Ubuntu / NTP Pool",
        L"Brugerdefineret"
    }, {
        L"Sjálfvirkt eftir svæði",
        L"Tékkland og Slóvakía – CESNET/NIC.CZ",
        L"PTB – Þýskaland og Evrópa",
        L"Allur heimurinn – Ubuntu / NTP Pool",
        L"Sérsniðið"
    }, {
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

const wchar_t* NTP_LOG_COLUMN_LABELS[LANG_COUNT][3] = {
    {
        L"Datum a čas",
        L"Server NTP",
        L"Stav"
    }, {
        L"Date and time",
        L"NTP server",
        L"Status"
    }, {
        L"Datum und Uhrzeit",
        L"NTP-Server",
        L"Status"
    }, {
        L"Date et heure",
        L"Serveur NTP",
        L"État"
    }, {
        L"Fecha y hora",
        L"Servidor NTP",
        L"Estado"
    }, {
        L"Data e ora",
        L"Server NTP",
        L"Stato"
    }, {
        L"Data i godzina",
        L"Serwer NTP",
        L"Stan"
    }, {
        L"Dátum a čas",
        L"Server NTP",
        L"Stav"
    }, {
        L"Date and time",
        L"NTP server",
        L"Status"
    }, {
        L"Date and time",
        L"NTP server",
        L"Status"
    }, {
        L"Data e hora",
        L"Servidor NTP",
        L"Estado"
    }, {
        L"Dato og klokkeslett",
        L"NTP-server",
        L"Status"
    }, {
        L"Datum och tid",
        L"NTP-server",
        L"Status"
    }, {
        L"Päivämäärä ja aika",
        L"NTP-palvelin",
        L"Tila"
    }, {
        L"Dato og klokkeslæt",
        L"NTP-server",
        L"Status"
    }, {
        L"Dagsetning og tími",
        L"NTP-þjónn",
        L"Staða"
    }, {
        L"Tarih ve saat",
        L"NTP sunucusu",
        L"Durum"
    }
};

const wchar_t* NTP_LOG_ERROR_LABELS[LANG_COUNT][4] = {
    {
        L"Neplatná odpověď NTP",
        L"Nepodařilo se přeložit název serveru",
        L"Chyba sítě",
        L"Vypršel časový limit odpovědi"
    }, {
        L"Invalid NTP reply",
        L"Server name resolution failed",
        L"Network error",
        L"Response timed out"
    }, {
        L"Ungültige NTP-Antwort",
        L"Servername konnte nicht aufgelöst werden",
        L"Netzwerkfehler",
        L"Zeitüberschreitung beim Warten auf die Antwort"
    }, {
        L"Réponse NTP non valide",
        L"Échec de la résolution du nom du serveur",
        L"Erreur réseau",
        L"Délai d’attente de la réponse dépassé"
    }, {
        L"Respuesta NTP no válida",
        L"Error al resolver el nombre del servidor",
        L"Error de red",
        L"Tiempo de espera de la respuesta agotado"
    }, {
        L"Risposta NTP non valida",
        L"Risoluzione del nome del server non riuscita",
        L"Errore di rete",
        L"Tempo di attesa della risposta scaduto"
    }, {
        L"Nieprawidłowa odpowiedź NTP",
        L"Nie udało się rozpoznać nazwy serwera",
        L"Błąd sieci",
        L"Przekroczono czas oczekiwania na odpowiedź"
    }, {
        L"Neplatná odpoveď NTP",
        L"Nepodarilo sa preložiť názov servera",
        L"Chyba siete",
        L"Vypršal časový limit odpovede"
    }, {
        L"Invalid NTP reply",
        L"Server name resolution failed",
        L"Network error",
        L"Response timed out"
    }, {
        L"Invalid NTP reply",
        L"Server name resolution failed",
        L"Network error",
        L"Response timed out"
    }, {
        L"Resposta NTP inválida",
        L"Falha na resolução do nome do servidor",
        L"Erro de rede",
        L"Tempo de espera da resposta esgotado"
    }, {
        L"Ugyldig NTP-svar",
        L"Kunne ikke slå opp servernavnet",
        L"Nettverksfeil",
        L"Tidsavbrudd ved venting på svar"
    }, {
        L"Ogiltigt NTP-svar",
        L"Kunde inte slå upp servernamnet",
        L"Nätverksfel",
        L"Tidsgränsen för svar överskreds"
    }, {
        L"Virheellinen NTP-vastaus",
        L"Palvelimen nimen selvitys epäonnistui",
        L"Verkkovirhe",
        L"Vastauksen aikakatkaisu"
    }, {
        L"Ugyldigt NTP-svar",
        L"Servernavnet kunne ikke slås op",
        L"Netværksfejl",
        L"Tidsgrænsen for svar blev overskredet"
    }, {
        L"Ógilt NTP-svar",
        L"Ekki tókst að leysa nafn þjóns",
        L"Netvilla",
        L"Bið eftir svari rann út"
    }, {
        L"Geçersiz NTP yanıtı",
        L"Sunucu adı çözümlenemedi",
        L"Ağ hatası",
        L"Yanıt zaman aşımına uğradı"
    }
};

const wchar_t* NTP_SAVE_LOG_LABELS[LANG_COUNT] = {
    L"Uložit log",
    L"Save log",
    L"Protokoll speichern",
    L"Enregistrer le journal",
    L"Guardar registro",
    L"Salva registro",
    L"Zapisz dziennik",
    L"Uložiť log",
    L"Save log",
    L"Save log",
    L"Salvar registro",
    L"Lagre logg",
    L"Spara logg",
    L"Tallenna loki",
    L"Gem log",
    L"Vista annál",
    L"Günlüğü kaydet"
};

const wchar_t* NTP_LOG_EXPORT_FAILED[LANG_COUNT] = {
    L"Log se nepodařilo uložit.",
    L"The log could not be saved.",
    L"Das Protokoll konnte nicht gespeichert werden.",
    L"Impossible d’enregistrer le journal.",
    L"No se pudo guardar el registro.",
    L"Impossibile salvare il registro.",
    L"Nie można zapisać dziennika.",
    L"Log sa nepodarilo uložiť.",
    L"The log could not be saved.",
    L"The log could not be saved.",
    L"Não foi possível salvar o registro.",
    L"Loggen kunne ikke lagres.",
    L"Loggen kunde inte sparas.",
    L"Lokia ei voitu tallentaa.",
    L"Loggen kunne ikke gemmes.",
    L"Ekki tókst að vista annálinn.",
    L"Günlük kaydedilemedi."
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

const wchar_t* ANTIALIASING_NAMES[LANG_COUNT][FONT_ANTIALIAS_COUNT] = {
    {
        L"GDI",
        L"ClearType",
        L"Žádné"
    }, {
        L"GDI",
        L"ClearType",
        L"None"
    }, {
        L"GDI",
        L"ClearType",
        L"Keine"
    }, {
        L"GDI",
        L"ClearType",
        L"Aucun"
    }, {
        L"GDI",
        L"ClearType",
        L"Ninguno"
    }, {
        L"GDI",
        L"ClearType",
        L"Nessuno"
    }, {
        L"GDI",
        L"ClearType",
        L"Brak"
    }, {
        L"GDI",
        L"ClearType",
        L"Žiadne"
    }, {
        L"GDI",
        L"ClearType",
        L"None"
    }, {
        L"GDI",
        L"ClearType",
        L"None"
    }, {
        L"GDI",
        L"ClearType",
        L"Nenhuma"
    }, {
        L"GDI",
        L"ClearType",
        L"Ingen"
    }, {
        L"GDI",
        L"ClearType",
        L"Ingen"
    }, {
        L"GDI",
        L"ClearType",
        L"Ei mitään"
    }, {
        L"GDI",
        L"ClearType",
        L"Ingen"
    }, {
        L"GDI",
        L"ClearType",
        L"Engin"
    }, {
        L"GDI",
        L"ClearType",
        L"Yok"
    }
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
    L"Importovat &XML…",
    L"Import &XML…",
    L"&XML importieren…",
    L"Importer &XML…",
    L"Importar &XML…",
    L"Importa &XML…",
    L"Importuj &XML…",
    L"Importovať &XML…",
    L"Import &XML…",
    L"Import &XML…",
    L"Importar &XML…",
    L"Importer &XML…",
    L"Importera &XML…",
    L"Tuo &XML…",
    L"Importer &XML…",
    L"Flytja inn &XML…",
    L"&XML içe aktar…"
};

const wchar_t* EXPORT_SETTINGS_LABELS[LANG_COUNT] = {
    L"Exportovat X&ML…",
    L"Export X&ML…",
    L"XML &exportieren…",
    L"Exporter X&ML…",
    L"Exportar X&ML…",
    L"Esporta X&ML…",
    L"Eksportuj X&ML…",
    L"Exportovať X&ML…",
    L"Export X&ML…",
    L"Export X&ML…",
    L"Exportar X&ML…",
    L"Eksporter X&ML…",
    L"Exportera X&ML…",
    L"Vie X&ML…",
    L"Eksporter X&ML…",
    L"Flytja út X&ML…",
    L"X&ML dışa aktar…"
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
    L"OVLÁDÁNÍ\r\nLevým tlačítkem a tažením přesunete hodiny nebo panel. Samostatný kalendář se přesouvá za "
    L"volnou plochu; kliknutím na den "
    L"měníte vybrané datum a šipkami, záhlavím nebo odkazem Dnes kalendář procházíte. Pravým tlačítkem na "
    L"widgetu nebo na ikoně v oznamovací "
    L"oblasti otevřete nabídku. Levé kliknutí na ikonu skryje právě viditelné widgety; jsou-li všechny "
    L"skryté, obnoví pouze naposledy skryté "
    L"widgety.\r\n\r\nWIDGETY A NASTAVENÍ\r\nV Nastavení lze přidat, odebrat a duplikovat ručičkové hodiny, "
    L"digitální hodiny, kalendáře a panely "
    L"s kalendářem a hodinami i hodiny na monitoru. Každý widget má vlastní viditelnost, režim vždy navrchu, "
    L"jazyk, časové pásmo a offset. Offset "
    L"zadávejte jako [-]HH:mm:ss.ff. Ručičkové hodiny a hodiny v panelu mají volitelnou velikost. U "
    L"digitálních hodin lze nastavit sekundy, "
    L"úvodní nulu, písmo, barvy, neprůhlednost a průhledné pozadí. Kalendář podporuje čísla týdnů, neděli "
    L"jako první den a používá zvolený jazyk "
    L"widgetu.\r\n\r\nBUDÍK\r\nBudík lze nastavit pro hodiny a panel. Zvukový soubor aplikace přehrává sama "
    L"jednou nebo stále dokola podle volby. "
    L"Ostatní soubor nebo příkaz předá systému Windows. Kliknutím na budící ciferník či displej, příkazem "
    L"Zastavit budík nebo klávesou Esc "
    L"zastavíte blikání i zvuk přehrávaný aplikací.\r\n\r\nZKRATKY A UKLÁDÁNÍ\r\nDvojklik na ciferník nebo "
    L"digitální displej přepne sekundy, F1 "
    L"otevře nápovědu, B otevře Nastavení a Esc skryje widget, pokud právě nezastavuje budík. Polohy widgetů "
    L"se ukládají po přesunutí, polohy "
    L"formulářů při zavření a nastavení do zvoleného úložiště. Další spuštění programu aktivuje již běžící "
    L"instanci a zachová widgety u "
    L"nejbližšího dostupného okraje pracovní plochy.",
    L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a standalone calendar by its free "
    L"area; click a day to change the "
    L"selection and use the arrows, header or Today link to navigate. Right-click a widget or notification "
    L"icon for its menu. Left-click the "
    L"notification icon to hide the currently visible widgets; when all are hidden, it restores only the "
    L"widgets hidden most "
    L"recently.\r\n\r\nWIDGETS AND SETTINGS\r\nSettings can add, remove and duplicate analog clocks, digital "
    L"clocks, calendars, "
    L"calendar-and-clock panels and monitor clocks. Each widget has its own visibility, always-on-top state, "
    L"language, time zone and offset. "
    L"Enter offsets as [-]HH:mm:ss.ff. Analog clocks and panel clocks have selectable sizes. Digital clocks "
    L"support seconds, a leading zero, "
    L"font, colors, opacity and a transparent background. Calendars support week numbers and Sunday as the "
    L"first day and use the widget "
    L"language.\r\n\r\nALARM\r\nClocks and panels can have an alarm. The application plays an audio file "
    L"itself, once or continuously according "
    L"to the loop option. Other files or commands are passed to Windows. Click the alarming clock face or "
    L"display, choose Stop alarm, or press "
    L"Esc to stop both the alarm indication and audio played by the application.\r\n\r\nSHORTCUTS AND "
    L"SAVING\r\nDouble-click a clock face or "
    L"digital display to toggle seconds, press F1 for Help, B for Settings, and Esc to hide a widget when no "
    L"alarm is being stopped. Widget "
    L"positions are saved after dragging, dialog positions when closed, and all settings in the selected "
    L"storage. Starting the program again "
    L"activates the running instance and keeps widgets at the nearest available point in the work area.",
    L"BEDIENUNG\r\nZiehen Sie eine Uhr oder ein Panel mit der linken Maustaste. Einen einzelnen Kalender "
    L"ziehen Sie an seiner freien Fläche; ein "
    L"Klick auf einen Tag ändert die Auswahl. Rechtsklick auf Widget oder Infobereichsymbol öffnet das Menü. "
    L"Linksklick auf das Symbol verbirgt "
    L"die gerade sichtbaren Widgets; sind alle verborgen, werden nur die zuletzt verborgenen Widgets "
    L"wiederhergestellt.\r\n\r\nWIDGETS UND "
    L"EINSTELLUNGEN\r\nSie können Analoguhren, Digitaluhren, Kalender, Kalender-Uhr-Panels und Monitoruhren "
    L"hinzufügen, entfernen oder "
    L"duplizieren. Jedes Widget besitzt eigene Sichtbarkeit, Vordergrundlage, Sprache, Zeitzone und einen "
    L"Versatz im Format [-]HH:mm:ss.ff. "
    L"Analoguhren haben wählbare Größen. Digitaluhren bieten Sekunden, führende Null, Schrift, Farben, "
    L"Deckkraft und transparenten Hintergrund. "
    L"Kalender bieten Wochennummern, Sonntag als ersten Tag und verwenden die "
    L"Widget-Sprache.\r\n\r\nWECKER\r\nEine Audiodatei wird intern einmal "
    L"oder in Schleife abgespielt; andere Dateien oder Befehle werden an Windows übergeben. Ein Klick auf "
    L"das alarmierende Zifferblatt bzw. "
    L"Display, Wecker stoppen oder Esc beendet Anzeige und intern abgespielten Ton.\r\n\r\nTASTEN UND "
    L"SPEICHERN\r\nDoppelklick auf Zifferblatt "
    L"oder Digitalanzeige schaltet Sekunden um, F1 öffnet Hilfe, B die Einstellungen. Positionen und "
    L"sämtliche Einstellungen werden im gewählten "
    L"Speicher gespeichert. Ein erneuter Programmstart aktiviert die laufende Instanz.",
    L"COMMANDES\r\nFaites glisser une horloge ou un panneau avec le bouton gauche. Déplacez un calendrier "
    L"autonome par sa zone libre ; cliquez "
    L"sur un jour pour changer la sélection. Un clic droit sur un widget ou l’icône de notification ouvre le "
    L"menu. Un clic gauche sur l’icône "
    L"masque les widgets visibles ; s’ils sont tous masqués, il rétablit uniquement les widgets masqués le "
    L"plus récemment.\r\n\r\nWIDGETS ET "
    L"PARAMÈTRES\r\nVous pouvez ajouter, supprimer et dupliquer des horloges analogiques, numériques, des "
    L"calendriers, des panneaux combinés et "
    L"des horloges sur moniteur. Chaque widget possède sa visibilité, son maintien au premier plan, sa "
    L"langue, son fuseau et son décalage au "
    L"format [-]HH:mm:ss.ff. Les horloges analogiques ont des tailles au choix. Les horloges numériques "
    L"proposent secondes, zéro initial, police, "
    L"couleurs, opacité et fond transparent. Le calendrier propose numéros de semaine, dimanche en premier "
    L"et la langue du "
    L"widget.\r\n\r\nALARME\r\nL’application lit elle-même un fichier audio une fois ou en boucle ; les "
    L"autres fichiers ou commandes sont confiés "
    L"à Windows. Cliquez sur le cadran ou l’affichage en alarme, choisissez Arrêter l’alarme ou appuyez sur "
    L"Échap pour arrêter l’indication et le "
    L"son interne.\r\n\r\nRACCOURCIS ET ENREGISTREMENT\r\nUn double-clic sur le cadran ou l’affichage "
    L"numérique bascule les secondes, F1 ouvre "
    L"l’aide et B les paramètres. Les positions et tous les réglages sont enregistrés dans le stockage "
    L"sélectionné. Un nouveau lancement active "
    L"l’instance existante.",
    L"CONTROLES\r\nArrastre un reloj o panel con el botón izquierdo. El calendario independiente se arrastra "
    L"por su zona libre; haga clic en un "
    L"día para cambiar la selección. El botón derecho sobre un widget o el icono de notificación abre el "
    L"menú. Un clic izquierdo sobre el icono "
    L"oculta los widgets visibles; si todos están ocultos, restaura solo los ocultados más "
    L"recientemente.\r\n\r\nWIDGETS Y CONFIGURACIÓN\r\nPuede "
    L"añadir, quitar y duplicar relojes analógicos, digitales, calendarios, paneles combinados y relojes de "
    L"monitor. Cada widget tiene "
    L"visibilidad, primer plano, idioma, zona horaria y desfase propios; use [-]HH:mm:ss.ff. Los relojes "
    L"analógicos tienen tamaños "
    L"seleccionables. Los digitales permiten segundos, cero inicial, fuente, colores, opacidad y fondo "
    L"transparente. El calendario permite "
    L"números de semana, domingo primero y usa el idioma del widget.\r\n\r\nALARMA\r\nLa aplicación "
    L"reproduce internamente un archivo de audio "
    L"una vez o en bucle; los demás archivos o comandos se entregan a Windows. Haga clic en la esfera o "
    L"pantalla con alarma, elija Detener alarma "
    L"o pulse Esc para detener la indicación y el audio interno.\r\n\r\nATAJOS Y GUARDADO\r\nEl doble clic "
    L"en la esfera o la pantalla digital "
    L"cambia los segundos, F1 abre la ayuda y B la configuración. Las posiciones y todos los ajustes se "
    L"guardan en el almacenamiento "
    L"seleccionado. Otra ejecución activa la instancia existente.",
    L"COMANDI\r\nTrascinare un orologio o pannello con il pulsante sinistro. Il calendario autonomo si "
    L"trascina dall’area libera; fare clic su un "
    L"giorno per cambiare la selezione. Il pulsante destro su widget o icona di notifica apre il menu. Il "
    L"clic sinistro sull’icona nasconde i "
    L"widget visibili; se sono tutti nascosti, ripristina soltanto quelli nascosti più di "
    L"recente.\r\n\r\nWIDGET E IMPOSTAZIONI\r\nÈ possibile "
    L"aggiungere, rimuovere e duplicare orologi analogici, digitali, calendari, pannelli combinati e orologi "
    L"su monitor. Ogni widget ha "
    L"visibilità, primo piano, lingua, fuso orario e offset propri; usare [-]HH:mm:ss.ff. Gli orologi "
    L"analogici hanno dimensioni selezionabili. "
    L"Quelli digitali offrono secondi, zero iniziale, carattere, colori, opacità e sfondo trasparente. Il "
    L"calendario offre numeri di settimana, "
    L"domenica per prima e usa la lingua del widget.\r\n\r\nSVEGLIA\r\nL’applicazione riproduce internamente "
    L"un file audio una volta o in ciclo; "
    L"gli altri file o comandi vengono affidati a Windows. Fare clic sul quadrante o display in allarme, "
    L"scegliere Ferma sveglia o premere Esc "
    L"per fermare indicazione e audio interno.\r\n\r\nSCORCIATOIE E SALVATAGGIO\r\nIl doppio clic sul "
    L"quadrante o sul display digitale commuta i "
    L"secondi, F1 apre la guida e B le impostazioni. Posizioni e impostazioni vengono salvate nell’archivio "
    L"selezionato. Un nuovo avvio attiva "
    L"l’istanza esistente.",
    L"STEROWANIE\r\nPrzeciągnij zegar lub panel lewym przyciskiem. Samodzielny kalendarz przeciąga się za "
    L"wolne miejsce; kliknięcie dnia zmienia "
    L"wybór. Prawy przycisk na widżecie lub ikonie obszaru powiadomień otwiera menu. Lewy przycisk na ikonie "
    L"ukrywa widoczne widżety; gdy "
    L"wszystkie są ukryte, przywraca tylko ostatnio ukryte widżety.\r\n\r\nWIDŻETY I USTAWIENIA\r\nMożna "
    L"dodać, usunąć i powielić zegary "
    L"analogowych, cyfrowych, kalendarzy, paneli łączonych i zegarów na monitorze. Każdy widżet ma własną "
    L"widoczność, tryb na wierzchu, język, "
    L"strefę czasową i przesunięcie w formacie [-]HH:mm:ss.ff. Zegary analogowe mają różne rozmiary. Cyfrowe "
    L"oferują sekundy, zero wiodące, "
    L"czcionkę, kolory, krycie i przezroczyste tło. Kalendarz oferuje numery tygodni, niedzielę jako "
    L"pierwszy dzień i język "
    L"widżetu.\r\n\r\nALARM\r\nAplikacja sama odtwarza plik audio raz lub w pętli; inne pliki i polecenia "
    L"przekazuje systemowi Windows. "
    L"Kliknięcie alarmującej tarczy lub wyświetlacza, polecenie Zatrzymaj alarm albo Esc zatrzymuje "
    L"wskazanie i dźwięk wewnętrzny.\r\n\r\nSKRÓTY "
    L"I ZAPIS\r\nDwuklik na tarczy lub wyświetlaczu cyfrowym przełącza sekundy, F1 otwiera pomoc, a B "
    L"ustawienia. Pozycje i wszystkie ustawienia "
    L"są zapisywane w wybranym magazynie. Ponowne uruchomienie aktywuje istniejącą instancję.",
    L"OVLÁDANIE\r\nĽavým tlačidlom a ťahaním presuniete hodiny alebo panel. Samostatný kalendár sa presúva "
    L"za voľnú plochu; kliknutím na deň "
    L"zmeníte výber. Pravé tlačidlo na widgete alebo ikone v oznamovacej oblasti otvorí ponuku. Ľavé "
    L"kliknutie na ikonu skryje viditeľné widgety; "
    L"ak sú všetky skryté, obnoví iba naposledy skryté widgety.\r\n\r\nWIDGETY A NASTAVENIA\r\nMožno pridať, "
    L"odobrať a duplikovať ručičkové "
    L"hodiny, digitálne hodiny, kalendáre, kombinované panely a hodiny na monitore. Každý widget má vlastnú "
    L"viditeľnosť, režim vždy navrchu, "
    L"jazyk, časové pásmo a offset vo formáte [-]HH:mm:ss.ff. Ručičkové hodiny majú voliteľnú veľkosť. "
    L"Digitálne hodiny ponúkajú sekundy, úvodnú "
    L"nulu, písmo, farby, priehľadnosť a priehľadné pozadie. Kalendár ponúka čísla týždňov, nedeľu ako prvý "
    L"deň a používa jazyk "
    L"widgetu.\r\n\r\nBUDÍK\r\nAplikácia prehrá zvukový súbor sama raz alebo dookola; ostatné súbory a "
    L"príkazy odovzdá systému Windows. Kliknutie "
    L"na budík, príkaz Zastaviť budík alebo Esc zastaví signalizáciu aj interný zvuk.\r\n\r\nSKRATKY A "
    L"UKLADANIE\r\nDvojklik na ciferník alebo "
    L"digitálny displej prepne sekundy, F1 otvorí pomoc a B nastavenia. Polohy a všetky nastavenia sa "
    L"ukladajú do zvoleného úložiska. Ďalšie "
    L"spustenie aktivuje existujúcu inštanciu.",
    L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a standalone calendar by its free "
    L"area; click a day to change the "
    L"selection and use the arrows, header or Today link to navigate. Right-click a widget or notification "
    L"icon for its menu. Left-click the "
    L"notification icon to hide the currently visible widgets; when all are hidden, it restores only the "
    L"widgets hidden most "
    L"recently.\r\n\r\nWIDGETS AND SETTINGS\r\nSettings can add, remove and duplicate analog clocks, digital "
    L"clocks, calendars, "
    L"calendar-and-clock panels and monitor clocks. Each widget has its own visibility, always-on-top state, "
    L"language, time zone and offset. "
    L"Enter offsets as [-]HH:mm:ss.ff. Analog clocks and panel clocks have selectable sizes. Digital clocks "
    L"support seconds, a leading zero, "
    L"font, colours, opacity and a transparent background. Calendars support week numbers and Sunday as the "
    L"first day and use the widget "
    L"language.\r\n\r\nALARM\r\nClocks and panels can have an alarm. The application plays an audio file "
    L"itself, once or continuously according "
    L"to the loop option. Other files or commands are passed to Windows. Click the alarming clock face or "
    L"display, choose Stop alarm, or press "
    L"Esc to stop both the alarm indication and audio played by the application.\r\n\r\nSHORTCUTS AND "
    L"SAVING\r\nDouble-click a clock face or "
    L"digital display to toggle seconds, press F1 for Help, B for Settings, and Esc to hide a widget when no "
    L"alarm is being stopped. Widget "
    L"positions are saved after dragging, dialog positions when closed, and all settings in the selected "
    L"storage. Starting the program again "
    L"activates the running instance and keeps widgets at the nearest available point in the work area.",
    L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a standalone calendar by its free "
    L"area; click a day to change the "
    L"selection and use the arrows, header or Today link to navigate. Right-click a widget or notification "
    L"icon for its menu. Left-click the "
    L"notification icon to hide the currently visible widgets; when all are hidden, it restores only the "
    L"widgets hidden most "
    L"recently.\r\n\r\nWIDGETS AND SETTINGS\r\nSettings can add, remove and duplicate analog clocks, digital "
    L"clocks, calendars, "
    L"calendar-and-clock panels and monitor clocks. Each widget has its own visibility, always-on-top state, "
    L"language, time zone and offset. "
    L"Enter offsets as [-]HH:mm:ss.ff. Analog clocks and panel clocks have selectable sizes. Digital clocks "
    L"support seconds, a leading zero, "
    L"font, colours, opacity and a transparent background. Calendars support week numbers and Sunday as the "
    L"first day and use the widget "
    L"language.\r\n\r\nALARM\r\nClocks and panels can have an alarm. The application plays an audio file "
    L"itself, once or continuously according "
    L"to the loop option. Other files or commands are passed to Windows. Click the alarming clock face or "
    L"display, choose Stop alarm, or press "
    L"Esc to stop both the alarm indication and audio played by the application.\r\n\r\nSHORTCUTS AND "
    L"SAVING\r\nDouble-click a clock face or "
    L"digital display to toggle seconds, press F1 for Help, B for Settings, and Esc to hide a widget when no "
    L"alarm is being stopped. Widget "
    L"positions are saved after dragging, dialog positions when closed, and all settings in the selected "
    L"storage. Starting the program again "
    L"activates the running instance and keeps widgets at the nearest available point in the work area.",
    L"CONTROLOS\r\nArraste um relógio ou painel com o botão esquerdo. Arraste um calendário autónomo pela "
    L"área livre e clique num dia para o "
    L"selecionar. O botão direito abre o menu do widget. Um clique esquerdo no ícone de notificação oculta "
    L"os widgets visíveis ou repõe os "
    L"ocultados mais recentemente.\r\n\r\nWIDGETS E DEFINIÇÕES\r\nPode adicionar, remover e duplicar "
    L"relógios analógicos, digitais, calendários, "
    L"painéis combinados e relógios de monitor. Cada widget tem visibilidade, posição no topo, idioma, fuso "
    L"horário e desvio "
    L"próprios.\r\n\r\nALARME\r\nRelógios e painéis podem ter um alarme. Clique no mostrador ou visor em "
    L"alarme, escolha Parar alarme ou prima "
    L"Esc para parar a indicação e o áudio interno.\r\n\r\nATALHOS\r\nUm duplo clique no mostrador ou visor "
    L"digital alterna os segundos, F1 abre "
    L"a Ajuda, B abre as Definições e Esc oculta o widget.",
    L"KONTROLLER\r\nDra en klokke eller et panel med venstre museknapp. Dra en frittstående kalender i det "
    L"ledige området og klikk en dag for å "
    L"velge den. Høyreklikk åpner widgetmenyen. Et venstreklikk på systemstatusikonet skjuler synlige "
    L"widgeter eller gjenoppretter de sist "
    L"skjulte.\r\n\r\nWIDGETER OG INNSTILLINGER\r\nDu kan legge til, fjerne og duplisere analoge klokker, "
    L"digitale klokker, kalendere, kombinerte "
    L"paneler og skjermklokker. Hver widget har egne innstillinger for synlighet, alltid øverst, språk, "
    L"tidssone og "
    L"forskyvning.\r\n\r\nALARM\r\nKlokker og paneler kan ha en alarm. Klikk urskiven eller skjermen som "
    L"alarmerer, velg Stopp alarm eller trykk "
    L"Esc for å stoppe indikasjonen og intern lyd.\r\n\r\nSNARVEIER\r\nDobbeltklikk på urskiven eller den "
    L"digitale visningen veksler sekunder, F1 "
    L"åpner Hjelp, B åpner Innstillinger og Esc skjuler widgeten.",
    L"KONTROLLER\r\nDra en klocka eller panel med vänster musknapp. Dra en fristående kalender i det fria "
    L"området och klicka på en dag för att "
    L"välja den. Högerklick öppnar widgetmenyn. Ett vänsterklick på meddelandeikonen döljer synliga widgetar "
    L"eller återställer de senast "
    L"dolda.\r\n\r\nWIDGETAR OCH INSTÄLLNINGAR\r\nDu kan lägga till, ta bort och duplicera analoga klockor, "
    L"digitala klockor, kalendrar, "
    L"kombinerade paneler och skärmklockor. Varje widget har egna inställningar för synlighet, alltid "
    L"överst, språk, tidszon och "
    L"förskjutning.\r\n\r\nALARM\r\nKlockor och paneler kan ha ett alarm. Klicka på urtavlan eller displayen "
    L"som larmar, välj Stoppa alarm eller "
    L"tryck Esc för att stoppa indikeringen och internt ljud.\r\n\r\nGENVÄGAR\r\nDubbelklick på urtavlan "
    L"eller den digitala displayen växlar "
    L"sekunder, F1 öppnar Hjälp, B öppnar Inställningar och Esc döljer widgeten.",
    L"OHJAUS\r\nVedä kelloa tai paneelia hiiren vasemmalla painikkeella. Vedä erillistä kalenteria vapaalta "
    L"alueelta ja valitse päivä "
    L"napsauttamalla. Napsauta hiiren kakkospainikkeella avataksesi pienoisohjelman valikon. Ilmoitusalueen "
    L"kuvakkeen napsautus piilottaa näkyvät "
    L"pienoisohjelmat tai palauttaa viimeksi piilotetut.\r\n\r\nPIENOISOHJELMAT JA ASETUKSET\r\nVoit lisätä, "
    L"poistaa ja monistaa analogisia ja "
    L"digitaalisia kelloja, kalentereita, yhdistelmäpaneeleita ja näyttökelloja. Jokaisella on omat "
    L"näkyvyys-, päällimmäisyys-, kieli-, "
    L"aikavyöhyke- ja poikkeama-asetukset.\r\n\r\nHERÄTYS\r\nKelloissa ja paneeleissa voi olla herätys. "
    L"Pysäytä ilmaisin ja sisäinen ääni "
    L"napsauttamalla hälyttävää näyttöä, valitsemalla Pysäytä herätys tai painamalla "
    L"Esc.\r\n\r\nPIKANÄPPÄIMET\r\nKellotaulun tai digitaalisen "
    L"näytön kaksoisnapsautus vaihtaa sekuntien näkyvyyttä, F1 avaa ohjeen, B asetukset ja Esc piilottaa "
    L"pienoisohjelman.",
    L"BETJENING\r\nTræk et ur eller panel med venstre museknap. Træk en selvstændig kalender i det frie "
    L"område og klik på en dag for at vælge "
    L"den. Højreklik åbner widgetmenuen. Et venstreklik på meddelelsesikonet skjuler synlige widgets eller "
    L"gendanner de senest "
    L"skjulte.\r\n\r\nWIDGETS OG INDSTILLINGER\r\nDu kan tilføje, fjerne og duplikere analoge ure, digitale "
    L"ure, kalendere, kombinerede paneler "
    L"og skærmure. Hver widget har egne indstillinger for synlighed, altid øverst, sprog, tidszone og "
    L"forskydning.\r\n\r\nALARM\r\nUre og paneler "
    L"kan have en alarm. Klik på den alarmerende urskive eller visning, vælg Stop alarm eller tryk Esc for "
    L"at stoppe indikationen og intern "
    L"lyd.\r\n\r\nGENVEJE\r\nDobbeltklik på urskiven eller den digitale visning skifter sekunder, F1 åbner "
    L"Hjælp, B åbner Indstillinger og Esc "
    L"skjuler widgeten.",
    L"STJÓRNUN\r\nDragðu klukku eða spjald með vinstri músarhnappi. Dragðu sjálfstætt dagatal á auðu svæði "
    L"og smelltu á dag til að velja hann. "
    L"Hægrismellur opnar valmynd græju. Vinstrismellur á tilkynningatáknið felur sýnilegar græjur eða "
    L"endurheimtir þær sem síðast voru "
    L"faldar.\r\n\r\nGRÆJUR OG STILLINGAR\r\nHægt er að bæta við, fjarlægja og afrita skífuklukkur, "
    L"stafrænar klukkur, dagatöl, samsett spjöld og "
    L"skjáklukkur. Hver græja hefur eigið sýnileika-, efst-, tungumála-, tímabeltis- og "
    L"hliðrunargildi.\r\n\r\nVEKJARI\r\nKlukkur og spjöld geta "
    L"haft vekjara. Smelltu á skífuna eða skjáinn, veldu Stöðva vekjara eða ýttu á Esc til að stöðva "
    L"merkingu og innra "
    L"hljóð.\r\n\r\nFLÝTILEIÐIR\r\nTvísmellur á skífu eða stafrænan skjá skiptir um sýnileika sekúndna, F1 "
    L"opnar Hjálp, B opnar Stillingar og Esc "
    L"felur græjuna.",
    L"DENETİMLER\r\nBir saati veya paneli sol fare düğmesiyle sürükleyin. Bağımsız takvimi boş alanından "
    L"sürükleyin ve seçmek için bir güne "
    L"tıklayın. Sağ tıklama araç menüsünü açar. Bildirim simgesine sol tıklamak görünür araçları gizler veya "
    L"en son gizlenenleri geri "
    L"getirir.\r\n\r\nARAÇLAR VE AYARLAR\r\nAnalog saatler, dijital saatler, takvimler, birleşik paneller ve "
    L"monitör saatleri ekleyebilir, "
    L"kaldırabilir ve çoğaltabilirsiniz. Her aracın görünürlük, her zaman üstte, dil, saat dilimi ve ofset "
    L"ayarları "
    L"ayrıdır.\r\n\r\nALARM\r\nSaatlerde ve panellerde alarm olabilir. Alarm veren kadrana veya ekrana "
    L"tıklayın, Alarmı durdur'u seçin ya da "
    L"göstergeyi ve dahili sesi durdurmak için Esc tuşuna basın.\r\n\r\nKISAYOLLAR\r\nKadrana veya dijital "
    L"ekrana çift tıklama saniyeleri açıp "
    L"kapatır, F1 Yardım'ı, B Ayarlar'ı açar ve Esc aracı gizler."
};

const wchar_t* HELP_ALARM_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZADÁVÁNÍ ČASU A AKCE BUDÍKU\r\nČas budíku přijímá běžný tvar HH:mm s dvojtečkou, tečkou, "
    L"mezerou či jiným oddělovačem; oddělovač lze také vynechat. Jedna nebo dvě číslice znamenají "
    L"hodiny, tři nebo čtyři číslice hodiny a minuty, například 7, 12, 730, 0730 nebo 7:30. Po "
    L"opuštění pole se čas sjednotí na HH:mm. Offset se zadává zprava od sekund: 2 znamená "
    L"00:00:02.00, 230 i 0230 znamená 00:02:30.00 a 12345 znamená 01:23:45.00. Při odděleném zápisu "
    L"jsou dvě skupiny minuty a sekundy, tři skupiny hodiny, minuty a sekundy a čtvrtá skupina "
    L"setiny; lze použít znaménko. Dny pod volbou Budík aktivní určují, ve které dny se budík spustí; "
    L"výchozí jsou všechny dny. Jejich pořadí se řídí kulturou aplikace a změna jazyka nemění uložené "
    L"dny. Při spuštění budík zobrazí skrytý widget a přenese jej před ostatní okna, aniž trvale "
    L"změní Vždy navrchu. Volba Pípat časové znamení spustí první krátký tón pět sekund před časem "
    L"budíku. Je nezávislá na kartě Znamení; souběžné sekvence se však sloučí. Tlačítko Vyzkoušet "
    L"rozbliká aktuální ciferník či rám panelu a vyzkouší soubor, příkaz, zvuk, HTTP/HTTPS adresu "
    L"vzdáleného skriptu a při zapnuté volbě i celé časové znamení. Zastavení testu ukončí jeho "
    L"interní zvuk a náhled znamení; zastavení budíku ukončí jeho interní zvuk. Ztlumení interní "
    L"přehrávání nezastaví: pokračuje potichu a po zrušení ztlumení je znovu slyšet. Příkazy a "
    L"vzdálené skripty ztlumení neovlivňuje.\r\n\r\nJezdec Hlasitost zvuku na kartě Budík nastavuje "
    L"hlasitost interně přehrávaného zvukového souboru pro daný widget. Výchozích −18 dB odpovídá 100 "
    L"% původní úrovně souboru. Posun doprava zvuk zesiluje; maximum 0 dB odpovídá přibližně 794 %. "
    L"Hodnota −∞ dB znamená úplné ztišení. Změny uslyšíte i během testu. Pro jiné soubory je jezdec "
    L"neaktivní. Soubory MIDI a soubory, které nelze dekódovat a přehrávají se náhradním přehrávačem, "
    L"lze nastavit nejvýše na 100 %.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, space or "
    L"another separator; the separator may also be omitted. One or two digits mean hours, while three "
    L"or four digits mean hours and minutes, for example 7, 12, 730, 0730 or 7:30. The value is "
    L"normalized to HH:mm after leaving the field. Offset entry starts from seconds on the right: 2 "
    L"means 00:00:02.00, 230 and 0230 mean 00:02:30.00, and 12345 means 01:23:45.00. With separators, "
    L"two groups mean minutes and seconds, three mean hours, minutes and seconds, and a fourth group "
    L"contains hundredths; a sign is accepted. The days below Alarm enabled select the weekdays on "
    L"which the alarm runs; all days are selected by default. Their order follows the application "
    L"culture, and changing the language does not change the stored weekdays. When triggered, the "
    L"alarm shows a hidden widget and brings it in front without permanently changing Always on top. "
    L"Sound the time signal starts its first short pip five seconds before the alarm. It is "
    L"independent of the Signal tab, although coincident sequences are merged. Test flashes the "
    L"selected clock face or panel frame and tests the file, command, audio, HTTP/HTTPS remote-script "
    L"URL and, when selected, the complete time-signal sequence. Stopping the test stops its internal "
    L"audio and signal preview; stopping the alarm stops its internal audio. Muting does not stop "
    L"internal playback: it continues silently and becomes audible again after unmuting. Commands and "
    L"remote scripts are unaffected.\r\n\r\nThe Audio volume slider on the Alarm tab sets the volume of "
    L"internally played audio files for that widget. The default −18 dB preserves the original file "
    L"level (100%). Moving the slider to the right amplifies the audio; the 0 dB maximum is "
    L"approximately 794%. The −∞ dB position is silence. Changes can also be heard during a test. The "
    L"slider is disabled for other files. MIDI files and files played by a fallback player because "
    L"they cannot be decoded are limited to 100%.",
    L"\r\n\r\nZEITEINGABE UND WECKERAKTIONEN\r\nDie Weckzeit akzeptiert HH:mm mit Doppelpunkt, Punkt, "
    L"Leerzeichen oder einem anderen Trennzeichen; das Trennzeichen kann entfallen. Eine oder zwei "
    L"Ziffern bedeuten Stunden, drei oder vier Ziffern Stunden und Minuten, z. B. 7, 12, 730, 0730 "
    L"oder 7:30. Beim Verlassen des Feldes wird HH:mm verwendet. Der Versatz wird von rechts ab den "
    L"Sekunden eingegeben: 2 bedeutet 00:00:02.00, 230 und 0230 bedeuten 00:02:30.00 und 12345 "
    L"bedeutet 01:23:45.00. Mit Trennzeichen stehen zwei Gruppen für Minuten und Sekunden, drei für "
    L"Stunden, Minuten und Sekunden und eine vierte für Hundertstel; ein Vorzeichen ist zulässig. Die "
    L"Tage unter Wecker aktiv bestimmen, an welchen Wochentagen der Wecker läuft; standardmäßig sind "
    L"alle gewählt. Ihre Reihenfolge folgt der Anwendungskultur; ein Sprachwechsel ändert die "
    L"gespeicherten Wochentage nicht. Beim Auslösen zeigt der Wecker ein verborgenes Widget und "
    L"bringt es nach vorn, ohne Immer im Vordergrund dauerhaft zu ändern. Akustisches Zeitzeichen "
    L"startet den ersten kurzen Ton fünf Sekunden vor dem Wecker. Diese Wahl ist von der "
    L"Registerkarte Zeitzeichen unabhängig; gleichzeitige Folgen werden jedoch zusammengeführt. "
    L"Testen lässt Zifferblatt oder Panelrahmen blinken und prüft Datei, Befehl, Audio, eine "
    L"HTTP/HTTPS-Adresse eines Remote-Skripts sowie bei aktivierter Option die vollständige "
    L"Zeitzeichenfolge asynchron. Das Stoppen des Tests beendet dessen internes Audio und die "
    L"Signalvorschau; das Stoppen des Weckers beendet sein internes Audio. Stummschalten beendet die "
    L"interne Wiedergabe nicht: Sie läuft lautlos weiter und wird nach dem Aufheben wieder hörbar. "
    L"Befehle und Remote-Skripte bleiben unberührt. Datei oder Befehl starten aktiviert Feld, "
    L"Durchsuchen, Test und Wiederholung; Test und Wiederholung erfordern zusätzlich einen nicht "
    L"leeren Wert, ein laufender Test kann jedoch immer gestoppt werden.\r\n\r\nDer Regler "
    L"Audiolautstärke auf der Registerkarte Alarm stellt die Lautstärke intern abgespielter "
    L"Audiodateien für dieses Widget ein. Der Standardwert −18 dB entspricht dem ursprünglichen Pegel "
    L"der Datei (100 %). Nach rechts wird der Ton verstärkt; das Maximum von 0 dB entspricht etwa 794 "
    L"%. −∞ dB bedeutet Stille. Änderungen sind auch während eines Tests hörbar. Für andere Dateien "
    L"ist der Regler deaktiviert. MIDI-Dateien und Dateien, die nicht decodiert werden können und mit "
    L"einem Ersatzplayer abgespielt werden, sind auf 100 % begrenzt.",
    L"\r\n\r\nSAISIE DE L’HEURE ET ACTIONS D’ALARME\r\nL’heure accepte HH:mm avec deux-points, point, "
    L"espace ou un autre séparateur, qui peut aussi être omis. Un ou deux chiffres indiquent les "
    L"heures, trois ou quatre les heures et les minutes, par exemple 7, 12, 730, 0730 ou 7:30. La "
    L"valeur devient HH:mm à la sortie du champ. Le décalage se saisit de droite à partir des "
    L"secondes : 2 signifie 00:00:02.00, 230 et 0230 signifient 00:02:30.00, et 12345 signifie "
    L"01:23:45.00. Avec séparateurs, deux groupes représentent minutes et secondes, trois "
    L"représentent heures, minutes et secondes, et un quatrième les centièmes ; un signe est accepté. "
    L"Les jours sous Alarme active déterminent les jours où l’alarme fonctionne ; tous sont "
    L"sélectionnés par défaut. Leur ordre suit la culture de l’application ; changer de langue ne "
    L"modifie pas les jours enregistrés. Lors du déclenchement, l’alarme affiche un widget masqué et "
    L"le ramène devant sans modifier durablement Toujours visible. Émettre le signal horaire lance le "
    L"premier bip court cinq secondes avant l’alarme. Ce choix est indépendant de l’onglet Signal, "
    L"mais les séquences simultanées sont fusionnées. Tester fait clignoter le cadran ou le cadre du "
    L"panneau et teste de façon le fichier, la commande, l’audio, l’URL HTTP/HTTPS du script distant "
    L"et, si l’option est activée, la séquence complète du signal horaire. Arrêter le test coupe son "
    L"audio interne et son aperçu du signal ; arrêter l’alarme coupe son audio interne. Couper le son "
    L"n’arrête pas la lecture interne : elle continue silencieusement et redevient audible après "
    L"rétablissement. Les commandes et scripts distants ne sont pas affectés. Lancer un fichier ou "
    L"une commande active le champ, Parcourir, Tester et la boucle ; Tester et la boucle exigent "
    L"aussi une valeur non vide, mais un test en cours peut toujours être arrêté.\r\n\r\nLe curseur "
    L"Volume audio de l’onglet Alarme règle le volume des fichiers audio lus en interne pour ce "
    L"widget. La valeur par défaut −18 dB correspond au niveau original du fichier (100 %). Déplacer "
    L"le curseur vers la droite amplifie le son ; le maximum de 0 dB correspond à environ 794 %. −∞ "
    L"dB correspond au silence. Les changements sont audibles pendant le test. Le curseur est "
    L"désactivé pour les autres fichiers. Les fichiers MIDI et ceux lus par un lecteur de secours "
    L"faute de décodage sont limités à 100 %.",
    L"\r\n\r\nENTRADA DE HORA Y ACCIONES DE ALARMA\r\nLa hora admite HH:mm con dos puntos, punto, espacio u "
    L"otro separador, que también puede omitirse. Uno o dos dígitos indican horas; tres o cuatro, "
    L"horas y minutos, por ejemplo 7, 12, 730, 0730 o 7:30. Al salir del campo se normaliza a HH:mm. "
    L"El desfase se introduce desde la derecha empezando por los segundos: 2 es 00:00:02.00, 230 y "
    L"0230 son 00:02:30.00, y 12345 es 01:23:45.00. Con separadores, dos grupos son minutos y "
    L"segundos, tres son horas, minutos y segundos, y un cuarto contiene centésimas; se admite signo. "
    L"Los días bajo Alarma activa determinan los días de la semana en que funciona; todos están "
    L"seleccionados de forma predeterminada. Su orden sigue la cultura de la aplicación; cambiar el "
    L"idioma no modifica los días guardados. Al activarse, la alarma muestra un widget oculto y lo "
    L"lleva al frente sin cambiar permanentemente Siempre visible. Emitir la señal horaria inicia el "
    L"primer pitido corto cinco segundos antes de la alarma. Es independiente de la pestaña Señal, "
    L"aunque las secuencias coincidentes se combinan. Probar hace parpadear la esfera o el marco del "
    L"panel y prueba de forma asíncrona el archivo, el comando, el audio, la URL HTTP/HTTPS del "
    L"script remoto y, si está activada, la secuencia completa de la señal horaria. Detener la prueba "
    L"también detiene su audio interno y la vista previa de la señal; detener la alarma detiene su "
    L"audio interno. Silenciar no detiene la reproducción interna: continúa en silencio y vuelve a "
    L"oírse al reactivar el sonido. No afecta a comandos ni scripts remotos. Ejecutar archivo o "
    L"comando activa el campo, Examinar, Probar y la repetición; Probar y repetir también requieren "
    L"un valor no vacío, pero una prueba en curso siempre puede detenerse.\r\n\r\nEl control Volumen de "
    L"audio de la pestaña Alarma ajusta los archivos de audio reproducidos internamente para ese "
    L"widget. El valor predeterminado de −18 dB conserva el nivel original del archivo (100 %). Hacia "
    L"la derecha se amplifica el sonido; el máximo de 0 dB equivale aproximadamente al 794 %. −∞ dB "
    L"es silencio. Los cambios se oyen durante la prueba. El control se desactiva para otros "
    L"archivos. Los archivos MIDI y los reproducidos por un reproductor alternativo al no poder "
    L"decodificarse están limitados al 100 %.",
    L"\r\n\r\nIMMISSIONE DELL’ORA E AZIONI SVEGLIA\r\nL’ora accetta HH:mm con due punti, punto, spazio o un "
    L"altro separatore, che può anche essere omesso. Una o due cifre indicano le ore; tre o quattro "
    L"indicano ore e minuti, per esempio 7, 12, 730, 0730 o 7:30. Uscendo dal campo il valore diventa "
    L"HH:mm. L’offset si inserisce da destra partendo dai secondi: 2 significa 00:00:02.00, 230 e "
    L"0230 significano 00:02:30.00 e 12345 significa 01:23:45.00. Con separatori, due gruppi sono "
    L"minuti e secondi, tre sono ore, minuti e secondi e un quarto contiene i centesimi; è ammesso il "
    L"segno. I giorni sotto Sveglia attiva stabiliscono in quali giorni suona; per impostazione "
    L"predefinita sono selezionati tutti. L’ordine segue la cultura dell’applicazione; cambiare "
    L"lingua non modifica i giorni memorizzati. All’attivazione, la sveglia mostra un widget nascosto "
    L"e lo porta davanti senza cambiare in modo permanente Sempre in primo piano. Emetti il segnale "
    L"orario avvia il primo segnale breve cinque secondi prima della sveglia. È indipendente dalla "
    L"scheda Segnale, ma le sequenze coincidenti vengono unite. Prova fa lampeggiare il quadrante o "
    L"il bordo del pannello e verifica in modo asincrono file, comando, audio, URL HTTP/HTTPS dello "
    L"script remoto e, se selezionata, l’intera sequenza del segnale orario. L’arresto della prova "
    L"interrompe il suo audio interno e l’anteprima del segnale; l’arresto della sveglia interrompe "
    L"il suo audio interno. Disattivare l’audio non ferma la riproduzione interna: continua "
    L"silenziosa e torna udibile alla riattivazione. Comandi e script remoti non sono interessati. "
    L"Esegui file o comando abilita il campo, Sfoglia, Prova e la ripetizione; Prova e ripetizione "
    L"richiedono anche un valore non vuoto, ma una prova in corso può sempre essere interrotta.\r\n\r\nIl "
    L"cursore Volume audio nella scheda Sveglia regola i file audio riprodotti internamente per il "
    L"widget. Il valore predefinito −18 dB mantiene il livello originale del file (100%). Spostando "
    L"il cursore a destra si amplifica il suono; il massimo di 0 dB equivale a circa il 794%. −∞ dB "
    L"indica il silenzio. Le modifiche si sentono durante la prova. Il cursore è disattivato per gli "
    L"altri file. I file MIDI e quelli riprodotti da un lettore alternativo perché non decodificabili "
    L"sono limitati al 100%.",
    L"\r\n\r\nWPROWADZANIE CZASU I AKCJE ALARMU\r\nCzas alarmu przyjmuje HH:mm z dwukropkiem, kropką, "
    L"spacją lub innym separatorem; separator można pominąć. Jedna lub dwie cyfry oznaczają godziny, "
    L"trzy lub cztery godziny i minuty, np. 7, 12, 730, 0730 albo 7:30. Po opuszczeniu pola wartość "
    L"przyjmuje postać HH:mm. Przesunięcie wpisuje się od prawej, zaczynając od sekund: 2 oznacza "
    L"00:00:02.00, 230 i 0230 oznaczają 00:02:30.00, a 12345 oznacza 01:23:45.00. Przy separatorach "
    L"dwie grupy oznaczają minuty i sekundy, trzy godziny, minuty i sekundy, a czwarta setne części; "
    L"znak jest dozwolony. Dni pod opcją Alarm aktywny określają dni tygodnia działania alarmu; "
    L"domyślnie zaznaczone są wszystkie. Ich kolejność zależy od kultury aplikacji; zmiana języka nie "
    L"zmienia zapisanych dni. Po uruchomieniu alarm pokazuje ukryty widżet i przenosi go do przodu "
    L"bez trwałej zmiany Zawsze na wierzchu. Odtwarzaj sygnał czasu uruchamia pierwszy krótki sygnał "
    L"pięć sekund przed alarmem. Opcja jest niezależna od karty Sygnał, lecz zbieżne sekwencje są "
    L"łączone. Test miga tarczą lub ramką panelu i sprawdza plik, polecenie, dźwięk, adres HTTP/HTTPS "
    L"zdalnego skryptu oraz, jeśli wybrano tę opcję, pełną sekwencję sygnału czasu. Zatrzymanie testu "
    L"wyłącza jego dźwięk wewnętrzny i podgląd sygnału; zatrzymanie alarmu wyłącza jego dźwięk "
    L"wewnętrzny. Wyciszenie nie zatrzymuje odtwarzania wewnętrznego: trwa ono bezgłośnie i po "
    L"włączeniu dźwięku znów jest słyszalne. Polecenia i zdalne skrypty pozostają bez zmian.\r\n\r\nSuwak "
    L"Głośność dźwięku na karcie Alarm ustawia głośność plików audio odtwarzanych wewnętrznie dla "
    L"danego widżetu. Domyślne −18 dB odpowiada oryginalnemu poziomowi pliku (100%). Przesunięcie w "
    L"prawo wzmacnia dźwięk; maksimum 0 dB odpowiada około 794%. −∞ dB oznacza ciszę. Zmiany słychać "
    L"również podczas testu. Dla innych plików suwak jest nieaktywny. Pliki MIDI i pliki odtwarzane "
    L"przez odtwarzacz zastępczy z powodu braku możliwości dekodowania są ograniczone do 100%.",
    L"\r\n\r\nZADÁVANIE ČASU A AKCIE BUDÍKA\r\nČas budíka prijíma HH:mm s dvojbodkou, bodkou, medzerou "
    L"alebo iným oddeľovačom; oddeľovač možno aj vynechať. Jedna alebo dve číslice znamenajú hodiny, "
    L"tri alebo štyri hodiny a minúty, napríklad 7, 12, 730, 0730 alebo 7:30. Po opustení poľa sa "
    L"hodnota upraví na HH:mm. Offset sa zadáva sprava od sekúnd: 2 znamená 00:00:02.00, 230 aj 0230 "
    L"znamená 00:02:30.00 a 12345 znamená 01:23:45.00. Pri oddelenom zápise sú dve skupiny minúty a "
    L"sekundy, tri skupiny hodiny, minúty a sekundy a štvrtá skupina stotiny; možno použiť znamienko. "
    L"Dni pod voľbou Budík aktívny určujú, v ktoré dni sa budík spustí; predvolene sú vybrané všetky. "
    L"Ich poradie sa riadi kultúrou aplikácie a zmena jazyka nemení uložené dni. Po spustení budík "
    L"zobrazí skrytý widget a prenesie ho pred ostatné okná bez trvalej zmeny Vždy navrchu. Voľba "
    L"Pípať časové znamenie spustí prvý krátky tón päť sekúnd pred časom budíka. Je nezávislá od "
    L"karty Znamenie; súbežné sekvencie sa však zlúčia. Vyskúšať rozbliká ciferník alebo rám panela a "
    L"otestuje súbor, príkaz, zvuk, HTTP/HTTPS adresu vzdialeného skriptu a pri zapnutej voľbe aj "
    L"celé časové znamenie. Zastavenie testu ukončí jeho interný zvuk a náhľad znamenia; zastavenie "
    L"budíka ukončí interný zvuk. Stlmenie interné prehrávanie nezastaví: pokračuje potichu a po "
    L"zrušení stlmenia je znovu počuť. Príkazy a vzdialené skripty stlmenie neovplyvňuje.\r\n\r\nJazdec "
    L"Hlasitosť zvuku na karte Budík nastavuje hlasitosť interne prehrávaného zvukového súboru pre "
    L"daný widget. Predvolených −18 dB zodpovedá 100 % pôvodnej úrovne súboru. Posun doprava zvuk "
    L"zosilňuje; maximum 0 dB zodpovedá približne 794 %. Hodnota −∞ dB znamená úplné stíšenie. Zmeny "
    L"počuť aj počas testu. Pre iné súbory je jazdec neaktívny. Súbory MIDI a súbory, ktoré nemožno "
    L"dekódovať a prehrávajú sa náhradným prehrávačom, možno nastaviť najviac na 100 %.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, space or "
    L"another separator; the separator may also be omitted. One or two digits mean hours, while three "
    L"or four digits mean hours and minutes, for example 7, 12, 730, 0730 or 7:30. The value is "
    L"normalized to HH:mm after leaving the field. Offset entry starts from seconds on the right: 2 "
    L"means 00:00:02.00, 230 and 0230 mean 00:02:30.00, and 12345 means 01:23:45.00. With separators, "
    L"two groups mean minutes and seconds, three mean hours, minutes and seconds, and a fourth group "
    L"contains hundredths; a sign is accepted. The days below Alarm enabled select the weekdays on "
    L"which the alarm runs; all days are selected by default. Their order follows the application "
    L"culture, and changing the language does not change the stored weekdays. When triggered, the "
    L"alarm shows a hidden widget and brings it in front without permanently changing Always on top. "
    L"Sound the time signal starts its first short pip five seconds before the alarm. It is "
    L"independent of the Signal tab, although coincident sequences are merged. Test flashes the "
    L"selected clock face or panel frame and tests the file, command, audio, HTTP/HTTPS remote-script "
    L"URL and, when selected, the complete time-signal sequence. Stopping the test stops its internal "
    L"audio and signal preview; stopping the alarm stops its internal audio. Muting does not stop "
    L"internal playback: it continues silently and becomes audible again after unmuting. Commands and "
    L"remote scripts are unaffected.\r\n\r\nThe Audio volume slider on the Alarm tab sets the volume of "
    L"internally played audio files for that widget. The default −18 dB preserves the original file "
    L"level (100%). Moving the slider to the right amplifies the audio; the 0 dB maximum is "
    L"approximately 794%. The −∞ dB position is silence. Changes can also be heard during a test. The "
    L"slider is disabled for other files. MIDI files and files played by a fallback player because "
    L"they cannot be decoded are limited to 100%.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, space or "
    L"another separator; the separator may also be omitted. One or two digits mean hours, while three "
    L"or four digits mean hours and minutes, for example 7, 12, 730, 0730 or 7:30. The value is "
    L"normalized to HH:mm after leaving the field. Offset entry starts from seconds on the right: 2 "
    L"means 00:00:02.00, 230 and 0230 mean 00:02:30.00, and 12345 means 01:23:45.00. With separators, "
    L"two groups mean minutes and seconds, three mean hours, minutes and seconds, and a fourth group "
    L"contains hundredths; a sign is accepted. The days below Alarm enabled select the weekdays on "
    L"which the alarm runs; all days are selected by default. Their order follows the application "
    L"culture, and changing the language does not change the stored weekdays. When triggered, the "
    L"alarm shows a hidden widget and brings it in front without permanently changing Always on top. "
    L"Sound the time signal starts its first short pip five seconds before the alarm. It is "
    L"independent of the Signal tab, although coincident sequences are merged. Test flashes the "
    L"selected clock face or panel frame and tests the file, command, audio, HTTP/HTTPS remote-script "
    L"URL and, when selected, the complete time-signal sequence. Stopping the test stops its internal "
    L"audio and signal preview; stopping the alarm stops its internal audio. Muting does not stop "
    L"internal playback: it continues silently and becomes audible again after unmuting. Commands and "
    L"remote scripts are unaffected.\r\n\r\nThe Audio volume slider on the Alarm tab sets the volume of "
    L"internally played audio files for that widget. The default −18 dB preserves the original file "
    L"level (100%). Moving the slider to the right amplifies the audio; the 0 dB maximum is "
    L"approximately 794%. The −∞ dB position is silence. Changes can also be heard during a test. The "
    L"slider is disabled for other files. MIDI files and files played by a fallback player because "
    L"they cannot be decoded are limited to 100%.",
    L"\r\n\r\nHORA E AÇÕES DO ALARME\r\nA hora aceita HH:mm com ou sem separador: 7, 12, 730, 0730 ou 7:30. "
    L"O desvio é lido da direita a partir dos segundos: 2 é 00:00:02.00, 230 é 00:02:30.00 e 12345 é "
    L"01:23:45.00. Os dias definem quando o alarme funciona e todos vêm selecionados. A ordem segue a "
    L"cultura da aplicação; mudar o idioma não altera os dias guardados. Ao disparar, mostra um "
    L"widget oculto e leva-o à frente sem alterar permanentemente Sempre no topo. O sinal começa "
    L"cinco segundos antes. Testar verifica de forma assíncrona a indicação, o áudio, o comando e o "
    L"script remoto. Silenciar não para a reprodução interna; continua sem som e volta a ouvir-se "
    L"depois. Comandos e scripts remotos não são afetados. Executar um ficheiro ou comando ativa o "
    L"campo, Procurar, Testar e a repetição; Testar e repetir exigem também um valor não vazio, mas "
    L"um teste em curso pode sempre ser parado.\r\n\r\nO controlo Volume do áudio no separador Alarme "
    L"ajusta os ficheiros de áudio reproduzidos internamente para esse widget. O valor predefinido "
    L"−18 dB mantém o nível original do ficheiro (100%). Deslocar o controlo para a direita amplifica "
    L"o som; o máximo de 0 dB corresponde a cerca de 794%. −∞ dB é silêncio. As alterações ouvem-se "
    L"durante o teste. O controlo fica desativado para outros ficheiros. Os ficheiros MIDI e os "
    L"reproduzidos por um leitor alternativo por não ser possível descodificá-los estão limitados a "
    L"100%.",
    L"\r\n\r\nTIDSANGIVELSE OG ALARMHANDLINGER\r\nAlarmtid godtar HH:mm med eller uten skilletegn: 7, 12, "
    L"730, 0730 eller 7:30. Forskyvningen leses fra høyre fra sekundene: 2 er 00:00:02.00, 230 er "
    L"00:02:30.00 og 12345 er 01:23:45.00. Dagene angir når alarmen kjører, og alle er valgt som "
    L"standard. Rekkefølgen følger programkulturen; språkbytte endrer ikke de lagrede ukedagene. Når "
    L"alarmen utløses, vises en skjult widget og bringes frem uten å endre Alltid øverst permanent. "
    L"Tidssignalet starter fem sekunder før. Test kontrollerer indikasjon, lyd, kommando og eksternt "
    L"skript asynkront. Demping stopper ikke intern avspilling; den fortsetter lydløst og blir hørbar "
    L"igjen etterpå. Kommandoer og eksterne skript påvirkes ikke. Kjør en fil eller kommando "
    L"aktiverer feltet, Bla gjennom, Test og gjentakelse; Test og gjentakelse krever også en verdi "
    L"som ikke er tom, men en pågående test kan alltid stoppes.\r\n\r\nLydvolum på Alarm-fanen justerer "
    L"internt avspilte lydfiler for widgeten. Standardverdien −18 dB beholder filens opprinnelige "
    L"nivå (100 %). Mot høyre forsterkes lyden; maksimum 0 dB tilsvarer omtrent 794 %. −∞ dB er "
    L"stillhet. Endringer høres også under testen. Glidebryteren er deaktivert for andre filer. "
    L"MIDI-filer og filer som spilles av med en alternativ spiller fordi de ikke kan dekodes, er "
    L"begrenset til 100 %.",
    L"\r\n\r\nTIDSINMATNING OCH ALARMÅTGÄRDER\r\nAlarmtiden godtar HH:mm med eller utan avgränsare: 7, 12, "
    L"730, 0730 eller 7:30. Förskjutningen läses från höger med sekunder först: 2 är 00:00:02.00, 230 "
    L"är 00:02:30.00 och 12345 är 01:23:45.00. Dagarna anger när alarmet körs och alla är valda från "
    L"början. Ordningen följer programkulturen; ett språkbyte ändrar inte de sparade veckodagarna. "
    L"När alarmet utlöses visas en dold widget och förs fram utan att Alltid överst ändras permanent. "
    L"Tidssignalen börjar fem sekunder före. Test provar indikering, ljud, kommando och fjärrskript "
    L"asynkront. Tystning stoppar inte intern uppspelning; den fortsätter tyst och hörs igen efter "
    L"återaktivering. Kommandon och fjärrskript påverkas inte. Kör en fil eller ett kommando "
    L"aktiverar fältet, Bläddra, Testa och upprepning; Testa och upprepning kräver också ett värde "
    L"som inte är tomt, men ett pågående test kan alltid stoppas.\r\n\r\nLjudvolym på fliken Alarm "
    L"justerar ljudfiler som spelas internt för widgeten. Standardvärdet −18 dB behåller filens "
    L"ursprungliga nivå (100 %). Åt höger förstärks ljudet; maximum 0 dB motsvarar ungefär 794 %. −∞ "
    L"dB är tystnad. Ändringar hörs även under testet. Reglaget är inaktivt för andra filer. "
    L"MIDI-filer och filer som spelas upp med en reservspelare eftersom de inte kan avkodas begränsas "
    L"till 100 %.",
    L"\r\n\r\nAJAN SYÖTTÖ JA HERÄTYKSEN TOIMINNOT\r\nHerätysaika hyväksyy HH:mm-muodon erottimella tai "
    L"ilman: 7, 12, 730, 0730 tai 7:30. Poikkeama luetaan oikealta sekunneista alkaen: 2 on "
    L"00:00:02.00, 230 on 00:02:30.00 ja 12345 on 01:23:45.00. Päivät määräävät milloin herätys "
    L"toimii; kaikki ovat oletuksena valittuina. Järjestys seuraa sovelluksen kulttuuria, eikä kielen "
    L"vaihto muuta tallennettuja viikonpäiviä. Hälytys näyttää piilotetun pienoisohjelman ja tuo sen "
    L"eteen muuttamatta pysyvästi Aina päällimmäisenä -tilaa. Aikamerkki alkaa viisi sekuntia ennen. "
    L"Testi tarkistaa ilmaisimen, äänen, komennon ja etäkomentosarjan asynkronisesti. Mykistys ei "
    L"pysäytä sisäistä toistoa; se jatkuu äänettömänä ja kuuluu taas mykistyksen jälkeen. Komennot ja "
    L"etäkomentosarjat eivät muutu. Suorita tiedosto tai komento ottaa käyttöön kentän, Selaa-, "
    L"Testaa- ja toistovalinnat; Testaa ja toisto vaativat muun kuin tyhjän arvon, mutta käynnissä "
    L"olevan testin voi aina pysäyttää.\r\n\r\nHerätys-välilehden Äänenvoimakkuus säätää pienoisohjelman "
    L"sisäisesti toistettavien äänitiedostojen voimakkuutta. Oletusarvo −18 dB säilyttää tiedoston "
    L"alkuperäisen tason (100 %). Oikealle siirtäminen vahvistaa ääntä; enimmäisarvo 0 dB vastaa noin "
    L"794 %:a. −∞ dB tarkoittaa hiljaisuutta. Muutokset kuuluvat myös testin aikana. Muille "
    L"tiedostoille liukusäädin ei ole käytössä. MIDI-tiedostojen ja varasoittimella toistettavien "
    L"tiedostojen, joita ei voi purkaa, enimmäistaso on 100 %.",
    L"\r\n\r\nTIDSINDTASTNING OG ALARMHANDLINGER\r\nAlarmtid accepterer HH:mm med eller uden skilletegn: 7, "
    L"12, 730, 0730 eller 7:30. Forskydningen læses fra højre fra sekunderne: 2 er 00:00:02.00, 230 "
    L"er 00:02:30.00 og 12345 er 01:23:45.00. Dagene bestemmer hvornår alarmen kører, og alle er "
    L"valgt som standard. Rækkefølgen følger programkulturen; et sprogskift ændrer ikke de gemte "
    L"ugedage. Når alarmen udløses, vises en skjult widget og føres frem uden permanent at ændre "
    L"Altid øverst. Tidssignalet starter fem sekunder før. Test afprøver indikationen, lyd, kommando "
    L"og fjernscript asynkront. Dæmpning stopper ikke intern afspilning; den fortsætter lydløst og "
    L"kan høres igen efter ophævelse. Kommandoer og fjernscripts påvirkes ikke. Kør en fil eller "
    L"kommando aktiverer feltet, Gennemse, Test og gentagelse; Test og gentagelse kræver også en "
    L"værdi, der ikke er tom, men en igangværende test kan altid stoppes.\r\n\r\nLydstyrke på fanen Alarm "
    L"justerer internt afspillede lydfiler for widgetten. Standardværdien −18 dB bevarer filens "
    L"oprindelige niveau (100 %). Mod højre forstærkes lyden; maksimum 0 dB svarer til cirka 794 %. "
    L"−∞ dB er stilhed. Ændringer høres også under testen. Skyderen er deaktiveret for andre filer. "
    L"MIDI-filer og filer, der afspilles med en alternativ afspiller, fordi de ikke kan afkodes, er "
    L"begrænset til 100 %.",
    L"\r\n\r\nINNSLÁTTUR TÍMA OG AÐGERÐIR VEKJARA\r\nVekjaratími tekur við HH:mm með eða án skilmerkis: 7, "
    L"12, 730, 0730 eða 7:30. Hliðrun er lesin frá hægri frá sekúndum: 2 er 00:00:02.00, 230 er "
    L"00:02:30.00 og 12345 er 01:23:45.00. Dagarnir ákvarða hvenær vekjarinn virkar og allir eru "
    L"sjálfgefið valdir. Röðin fylgir menningu forritsins; tungumálaskipti breyta ekki vistuðum "
    L"vikudögum. Þegar vekjari fer af stað sýnir hann falda græju og færir hana fremst án þess að "
    L"breyta varanlega Alltaf efst. Tímamerkið hefst fimm sekúndum fyrr. Prófun kannar merkingu, "
    L"hljóð, skipun og fjarskriftu ósamstillt. Þöggun stöðvar ekki innri spilun; hún heldur hljóðlaus "
    L"áfram og heyrist aftur þegar þöggun er aflétt. Skipanir og fjarskriftur breytast ekki. Keyra "
    L"skrá eða skipun virkjar reitinn, Velja, Prófa og endurtekningu; Prófa og endurtekning krefjast "
    L"einnig gildis sem er ekki autt, en alltaf má stöðva prófun sem er í gangi.\r\n\r\nHljóðstyrkur á "
    L"vekjaraflipanum stillir hljóðskrár sem forritið spilar fyrir græjuna. Sjálfgefið gildi −18 dB "
    L"heldur upprunalegum styrk skrárinnar (100%). Til hægri magnast hljóðið; hámarkið 0 dB samsvarar "
    L"um 794%. −∞ dB er þögn. Breytingar heyrast einnig meðan á prófun stendur. Sleðinn er óvirkur "
    L"fyrir aðrar skrár. MIDI-skrár og skrár sem aukaspilari spilar vegna þess að ekki er hægt að "
    L"afkóða þær takmarkast við 100%.",
    L"\r\n\r\nZAMAN GİRİŞİ VE ALARM EYLEMLERİ\r\nAlarm zamanı ayırıcıyla veya ayırıcı olmadan HH:mm kabul "
    L"eder: 7, 12, 730, 0730 ya da 7:30. Ofset sağdan saniyelerden başlayarak okunur: 2 değeri "
    L"00:00:02.00, 230 değeri 00:02:30.00 ve 12345 değeri 01:23:45.00 olur. Günler alarmın ne zaman "
    L"çalışacağını belirler ve varsayılan olarak tümü seçilidir. Sıralama uygulama kültürünü izler; "
    L"dil değişikliği kayıtlı günleri değiştirmez. Alarm tetiklendiğinde gizli aracı gösterir ve "
    L"kalıcı üstte durumunu değiştirmeden öne getirir. Zaman sinyali beş saniye önce başlar. Test; "
    L"göstergeyi, sesi, komutu ve uzak betiği sınar. Sessize alma dahili oynatmayı durdurmaz; "
    L"sessizce sürer ve ses açılınca yeniden duyulur. Komutlar ve uzak betikler etkilenmez. Dosya "
    L"veya komut çalıştır; alanı, Gözat, Test ve yinelemeyi etkinleştirir. Test ve yineleme ayrıca "
    L"boş olmayan bir değer gerektirir, ancak çalışan test her zaman durdurulabilir.\r\n\r\nAlarm "
    L"sekmesindeki Ses düzeyi kaydırıcısı, araç için dahili olarak çalınan ses dosyalarının düzeyini "
    L"ayarlar. Varsayılan −18 dB, dosyanın özgün düzeyini (%100) korur. Sağa kaydırmak sesi "
    L"yükseltir; en yüksek değer olan 0 dB yaklaşık %794 düzeyindedir. −∞ dB sessizliktir. "
    L"Değişiklikler test sırasında da duyulur. Diğer dosyalar için kaydırıcı devre dışıdır. MIDI "
    L"dosyaları ve çözülemediği için yedek oynatıcıyla çalınan dosyalar %100 ile sınırlıdır."
};

const wchar_t* HELP_SELECTION_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nVÝBĚR, KLÁVESY A KOPÍROVÁNÍ DATA\r\nV seznamu widgetů označíte více položek pomocí Ctrl, "
    L"Shift nebo Ctrl+A. Nastavení si pamatuje poslední otevřenou kartu a Přidat poslední skutečně "
    L"přidaný typ. Odebrat nebo Del odstraní všechny označené položky až po použití změn. Dvojklik "
    L"položky zobrazí případně skrytý widget, nastaví Zobrazeno a krátce jej zvýrazní. Volba "
    L"Nastavení v nabídce konkrétního widgetu jej v seznamu rovnou vybere. Kliknutí na den v "
    L"kalendáři datum vybere a zkopíruje do schránky; všechny masky jsou dostupné v každém jazyce a "
    L"slovní formáty používají jazyk widgetu. Výchozí Krátké datum se řídí jazykem widgetu. Insert "
    L"přepne označení aktuální položky a posune kurzor seznamu o řádek dolů. Ctrl+C zkopíruje "
    L"označené widgety. Ctrl+V přidá kopie na konec v pořadí seznamu s příponou názvu podle jazyka "
    L"aplikace. Ctrl+A, Ctrl+C, Ctrl+V, Delete a Insert fungují i na tlačítkách Odebrat a Duplikovat; "
    L"před provedením akce přesunou fokus do seznamu widgetů. Maximální počet widgetů je 32. Při "
    L"duplikování nebo vložení se přidají v pořadí pouze kopie, které se vejdou do limitu; na "
    L"zbývající se zobrazí upozornění. Na widgetech Ručičkové hodiny a Kalendář s hodinami zvolíte "
    L"pomocí Alt+0, Alt+1, Alt+2 nebo Alt+3 velikost hlavního ciferníku od nejmenší po největší.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nUse Ctrl, Shift or Ctrl+A to select several widgets. "
    L"Settings remembers the last open tab, and Add remembers the last type actually added. Remove or "
    L"Del removes all selected items when the changes are applied. Double-clicking an item makes a "
    L"hidden widget visible, selects Visible and identifies the widget briefly. Settings in a "
    L"specific widget menu selects that widget in the list. Clicking a calendar day selects it and "
    L"copies it to the clipboard; each calendar has its own format in Settings and its menu. Every "
    L"pattern is available in every language, while textual formats use the widget language. The "
    L"default Short date follows the widget language. Insert toggles the current item and moves the "
    L"list cursor down one row. Ctrl+C copies selected widgets. Ctrl+V appends copies in list order "
    L"with a name suffix in the application language. Ctrl+A, Ctrl+C, Ctrl+V, Delete and Insert also "
    L"work from the Remove and Duplicate buttons, moving focus to the widget list before performing "
    L"the action. Up to 32 widgets are allowed. When duplicating or pasting, copies are added in "
    L"order until the limit is reached; a notification appears for the remaining copies. Press Alt+0, "
    L"Alt+1, Alt+2, or Alt+3 on an Analog clock or Calendar with clock widget to select the main "
    L"clock face size, from smallest to largest.",
    L"\r\n\r\nAUSWAHL, TASTEN UND DATUMSKOPIE\r\nMit Strg, Umschalt oder Strg+A wählen Sie mehrere Widgets. "
    L"Einstellungen merkt sich die zuletzt geöffnete Registerkarte, Hinzufügen den zuletzt "
    L"hinzugefügten Typ. Entfernen oder Entf löscht beim Anwenden alle ausgewählten Einträge. Ein "
    L"Doppelklick macht ein verborgenes Widget sichtbar, aktiviert Sichtbar und kennzeichnet das "
    L"Widget kurz; Einstellungen im Widget-Menü wählt es in der Liste aus. Ein Klick auf einen "
    L"Kalendertag wählt und kopiert ihn im je Widget eingestellten Format. Alle Muster sind in jeder "
    L"Sprache verfügbar; Textformate verwenden die Widget-Sprache. Das voreingestellte Kurze Datum "
    L"folgt der Widget-Sprache. Einfg schaltet die Markierung des aktuellen Eintrags um und bewegt "
    L"den Listencursor eine Zeile nach unten. Strg+C kopiert ausgewählte Widgets. Strg+V fügt Kopien "
    L"in Listenreihenfolge am Ende hinzu, mit einem Namenszusatz in der Anwendungssprache. Strg+A, "
    L"Strg+C, Strg+V, Entf und Einfg funktionieren auch auf Entfernen und Duplizieren und setzen vor "
    L"der Aktion den Fokus auf die Widget-Liste. Maximal 32 Widgets sind möglich. Beim Duplizieren "
    L"oder Einfügen werden Kopien der Reihe nach bis zum Limit hinzugefügt; für die übrigen erscheint "
    L"ein Hinweis. Mit Alt+0, Alt+1, Alt+2 oder Alt+3 wählen Sie bei Analoguhr und Kalender mit Uhr "
    L"die Größe des Hauptzifferblatts von der kleinsten bis zur größten.",
    L"\r\n\r\nSÉLECTION, TOUCHES ET COPIE DE DATE\r\nCtrl, Maj ou Ctrl+A sélectionne plusieurs widgets. "
    L"Paramètres mémorise le dernier onglet ouvert et Ajouter le dernier type réellement ajouté. "
    L"Supprimer ou Suppr retire toute la sélection lors de l’application. Un double-clic rend visible "
    L"un widget masqué, coche Visible et l’identifie brièvement ; Paramètres dans son menu le "
    L"sélectionne dans la liste. Cliquer sur un jour le sélectionne et le copie selon le format "
    L"propre au calendrier. Tous les modèles sont disponibles dans chaque langue ; les formats "
    L"textuels utilisent la langue du widget. La Date courte par défaut suit la langue du widget. "
    L"Inser bascule la sélection de l’élément courant et descend le curseur de liste d’une ligne. "
    L"Ctrl+C copie les widgets sélectionnés. Ctrl+V ajoute les copies à la fin dans l’ordre de la "
    L"liste, avec un suffixe dans la langue de l’application. Ctrl+A, Ctrl+C, Ctrl+V, Suppr et Inser "
    L"fonctionnent aussi sur Supprimer et Dupliquer et déplacent le focus vers la liste avant "
    L"l’action. Le nombre de widgets est limité à 32. Lors de la duplication ou du collage, les "
    L"copies sont ajoutées dans l’ordre jusqu’à la limite ; un message signale les copies restantes. "
    L"Appuyez sur Alt+0, Alt+1, Alt+2 ou Alt+3 dans les widgets Horloge analogique et Calendrier avec "
    L"horloge pour choisir la taille du cadran principal, de la plus petite à la plus grande.",
    L"\r\n\r\nSELECCIÓN, TECLAS Y COPIA DE FECHA\r\nCtrl, Mayús o Ctrl+A selecciona varios widgets. "
    L"Configuración recuerda la última pestaña abierta y Añadir el último tipo realmente añadido. "
    L"Quitar o Supr elimina todos los seleccionados al aplicar los cambios. Un doble clic muestra un "
    L"widget oculto, activa Visible y lo identifica brevemente; Configuración en su menú lo "
    L"selecciona en la lista. Pulsar un día lo selecciona y copia según el formato propio del "
    L"calendario; los formatos de texto usan el idioma del widget. Todos los patrones están "
    L"disponibles en cualquier idioma y la Fecha corta predeterminada sigue el idioma del widget. "
    L"Insert alterna la selección del elemento actual y baja el cursor de la lista una fila. Ctrl+C "
    L"copia los widgets seleccionados. Ctrl+V añade las copias al final en el orden de la lista, con "
    L"un sufijo en el idioma de la aplicación. Ctrl+A, Ctrl+C, Ctrl+V, Supr e Insert también "
    L"funcionan desde Quitar y Duplicar y pasan el foco a la lista antes de actuar. Se permiten hasta "
    L"32 widgets. Al duplicar o pegar, las copias se añaden en orden hasta alcanzar el límite; se "
    L"muestra un aviso para las restantes. Pulse Alt+0, Alt+1, Alt+2 o Alt+3 en Reloj analógico o "
    L"Calendario con reloj para elegir el tamaño de la esfera principal, del menor al mayor.",
    L"\r\n\r\nSELEZIONE, TASTI E COPIA DELLA DATA\r\nCtrl, Maiusc o Ctrl+A seleziona più widget. "
    L"Impostazioni ricorda l’ultima scheda aperta e Aggiungi l’ultimo tipo realmente aggiunto. "
    L"Rimuovi o Canc elimina tutti gli elementi selezionati quando si applicano le modifiche. Un "
    L"doppio clic rende visibile un widget nascosto, seleziona Visibile e lo identifica brevemente; "
    L"Impostazioni nel suo menu lo seleziona nell’elenco. Il clic su un giorno lo seleziona e lo "
    L"copia nel formato del calendario; i formati testuali usano la lingua del widget. Tutti i "
    L"modelli sono disponibili in ogni lingua e la Data breve predefinita segue la lingua del widget. "
    L"Ins commuta la selezione dell’elemento corrente e sposta il cursore dell’elenco una riga in "
    L"basso. Ctrl+C copia i widget selezionati. Ctrl+V aggiunge le copie in fondo nell’ordine "
    L"dell’elenco, con un suffisso nella lingua dell’applicazione. Ctrl+A, Ctrl+C, Ctrl+V, Canc e Ins "
    L"funzionano anche da Rimuovi e Duplica e spostano il focus nell’elenco prima dell’azione. Sono "
    L"consentiti fino a 32 widget. Quando si duplica o incolla, le copie vengono aggiunte in ordine "
    L"fino al limite; un avviso segnala quelle rimanenti. Premere Alt+0, Alt+1, Alt+2 o Alt+3 nei "
    L"widget Orologio analogico e Calendario con orologio per scegliere la dimensione del quadrante "
    L"principale, dalla più piccola alla più grande.",
    L"\r\n\r\nZAZNACZANIE, KLAWISZE I KOPIOWANIE DATY\r\nCtrl, Shift lub Ctrl+A zaznacza wiele widżetów. "
    L"Ustawienia pamiętają ostatnio otwartą kartę, a Dodaj ostatnio rzeczywiście dodany typ. Usuń lub "
    L"Del usuwa wszystkie zaznaczone pozycje po zastosowaniu zmian. Dwuklik pokazuje ukryty widżet, "
    L"zaznacza Widoczny i krótko go wskazuje; Ustawienia w jego menu wybierają go na liście. "
    L"Kliknięcie dnia wybiera go i kopiuje w formacie danego kalendarza. Wszystkie wzorce są dostępne "
    L"w każdym języku, a formaty słowne używają języka widżetu. Domyślna Data krótka zależy od języka "
    L"widżetu. Insert przełącza zaznaczenie bieżącej pozycji i przesuwa kursor listy o jeden wiersz w "
    L"dół. Ctrl+C kopiuje zaznaczone widżety. Ctrl+V dodaje kopie na końcu w kolejności listy, z "
    L"przyrostkiem w języku aplikacji. Ctrl+A, Ctrl+C, Ctrl+V, Delete i Insert działają też na "
    L"przyciskach Usuń i Duplikuj i przed wykonaniem akcji przenoszą fokus na listę. Dozwolone są "
    L"maksymalnie 32 widżety. Podczas powielania lub wklejania kopie są dodawane w kolejności do "
    L"osiągnięcia limitu; dla pozostałych pojawia się powiadomienie. W widżetach Zegar analogowy i "
    L"Kalendarz z zegarem klawisze Alt+0, Alt+1, Alt+2 i Alt+3 wybierają rozmiar głównej tarczy od "
    L"najmniejszego do największego.",
    L"\r\n\r\nVÝBER, KLÁVESY A KOPÍROVANIE DÁTUMU\r\nPomocou Ctrl, Shift alebo Ctrl+A označíte viac "
    L"widgetov. Nastavenie si pamätá poslednú otvorenú kartu a Pridať posledný skutočne pridaný typ. "
    L"Odobrať alebo Del odstráni po použití zmien všetky označené položky. Dvojklik zobrazí skrytý "
    L"widget, začiarkne Zobrazené a krátko ho zvýrazní; Nastavenia v jeho ponuke ho vyberú v zozname. "
    L"Kliknutie na deň ho vyberie a skopíruje vo formáte daného kalendára. Všetky masky sú dostupné v "
    L"každom jazyku, slovné formáty používajú jazyk widgetu a predvolený Krátky dátum sa riadi "
    L"jazykom widgetu. Insert prepne označenie aktuálnej položky a posunie kurzor zoznamu o riadok "
    L"nižšie. Ctrl+C skopíruje označené widgety. Ctrl+V pridá kópie na koniec v poradí zoznamu s "
    L"príponou podľa jazyka aplikácie. Ctrl+A, Ctrl+C, Ctrl+V, Delete a Insert fungujú aj na "
    L"tlačidlách Odobrať a Duplikovať; pred vykonaním akcie presunú fokus do zoznamu. Maximálny počet "
    L"widgetov je 32. Pri duplikovaní alebo vložení sa pridajú v poradí iba kópie, ktoré sa zmestia "
    L"do limitu; na zostávajúce sa zobrazí upozornenie. Na widgetoch Ručičkové hodiny a Kalendár s "
    L"hodinami zvolíte pomocou Alt+0, Alt+1, Alt+2 alebo Alt+3 veľkosť hlavného ciferníka od "
    L"najmenšej po najväčšiu.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nUse Ctrl, Shift or Ctrl+A to select several widgets. "
    L"Settings remembers the last open tab, and Add remembers the last type actually added. Remove or "
    L"Del removes all selected items when the changes are applied. Double-clicking an item makes a "
    L"hidden widget visible, selects Visible and identifies the widget briefly. Settings in a "
    L"specific widget menu selects that widget in the list. Clicking a calendar day selects it and "
    L"copies it to the clipboard; each calendar has its own format in Settings and its menu. Every "
    L"pattern is available in every language, while textual formats use the widget language. The "
    L"default Short date follows the widget language. Insert toggles the current item and moves the "
    L"list cursor down one row. Ctrl+C copies selected widgets. Ctrl+V appends copies in list order "
    L"with a name suffix in the application language. Ctrl+A, Ctrl+C, Ctrl+V, Delete and Insert also "
    L"work from the Remove and Duplicate buttons, moving focus to the widget list before performing "
    L"the action. Up to 32 widgets are allowed. When duplicating or pasting, copies are added in "
    L"order until the limit is reached; a notification appears for the remaining copies. Press Alt+0, "
    L"Alt+1, Alt+2, or Alt+3 on an Analog clock or Calendar with clock widget to select the main "
    L"clock face size, from smallest to largest.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nUse Ctrl, Shift or Ctrl+A to select several widgets. "
    L"Settings remembers the last open tab, and Add remembers the last type actually added. Remove or "
    L"Del removes all selected items when the changes are applied. Double-clicking an item makes a "
    L"hidden widget visible, selects Visible and identifies the widget briefly. Settings in a "
    L"specific widget menu selects that widget in the list. Clicking a calendar day selects it and "
    L"copies it to the clipboard; each calendar has its own format in Settings and its menu. Every "
    L"pattern is available in every language, while textual formats use the widget language. The "
    L"default Short date follows the widget language. Insert toggles the current item and moves the "
    L"list cursor down one row. Ctrl+C copies selected widgets. Ctrl+V appends copies in list order "
    L"with a name suffix in the application language. Ctrl+A, Ctrl+C, Ctrl+V, Delete and Insert also "
    L"work from the Remove and Duplicate buttons, moving focus to the widget list before performing "
    L"the action. Up to 32 widgets are allowed. When duplicating or pasting, copies are added in "
    L"order until the limit is reached; a notification appears for the remaining copies. Press Alt+0, "
    L"Alt+1, Alt+2, or Alt+3 on an Analog clock or Calendar with clock widget to select the main "
    L"clock face size, from smallest to largest.",
    L"\r\n\r\nSELEÇÃO E DATA\r\nUm clique direito e Definições seleciona o widget correspondente. Ctrl+A "
    L"seleciona todos os widgets ou monitores; Delete remove os widgets selecionados. Um duplo clique "
    L"numa entrada torna o widget visível e realça-o brevemente. Num calendário, clicar num dia "
    L"seleciona-o e copia-o no formato escolhido; todos os formatos estão disponíveis em todos os "
    L"idiomas. Se forem selecionados vários widgets, as opções específicas ficam desativadas, mas os "
    L"separadores globais Hora e Aplicação permanecem disponíveis. Insert alterna a seleção do item "
    L"atual e desloca o cursor da lista uma linha para baixo. Ctrl+C copia os widgets selecionados. "
    L"Ctrl+V acrescenta cópias no fim pela ordem da lista, com um sufixo no idioma da aplicação. "
    L"Ctrl+A, Ctrl+C, Ctrl+V, Delete e Insert também funcionam nos botões Remover e Duplicar e passam "
    L"o foco para a lista antes da ação. São permitidos até 32 widgets. Ao duplicar ou colar, as "
    L"cópias são acrescentadas pela ordem até ao limite; é apresentado um aviso sobre as restantes. "
    L"Prima Alt+0, Alt+1, Alt+2 ou Alt+3 nos widgets Relógio analógico e Calendário com relógio para "
    L"escolher o tamanho do mostrador principal, do menor ao maior.",
    L"\r\n\r\nVALG OG DATO\r\nHøyreklikk og Innstillinger velger den aktuelle widgeten. Ctrl+A velger alle "
    L"widgeter eller skjermer; Delete fjerner valgte widgeter. Dobbeltklikk på en oppføring gjør "
    L"widgeten synlig og fremhever den kort. Klikk på en dag i kalenderen for å velge og kopiere den "
    L"i valgt format; alle formater er tilgjengelige på alle språk. Når flere widgeter er valgt, "
    L"deaktiveres widgetvalgene, men de globale fanene Tid og Program forblir tilgjengelige. Insert "
    L"veksler markeringen av gjeldende oppføring og flytter listepekeren én rad ned. Ctrl+C kopierer "
    L"valgte widgeter. Ctrl+V legger kopier nederst i listens rekkefølge med et navnetillegg på "
    L"programspråket. Ctrl+A, Ctrl+C, Ctrl+V, Delete og Insert virker også fra Fjern og Dupliser og "
    L"flytter fokus til listen før handlingen. Opptil 32 widgeter er tillatt. Ved duplisering eller "
    L"innliming legges kopier til i rekkefølge til grensen er nådd; et varsel vises for resten. Trykk "
    L"Alt+0, Alt+1, Alt+2 eller Alt+3 på Analog klokke eller Kalender med klokke for å velge "
    L"størrelsen på hovedurskiven, fra minst til størst.",
    L"\r\n\r\nMARKERING OCH DATUM\r\nHögerklick och Inställningar markerar den aktuella widgeten. Ctrl+A "
    L"markerar alla widgetar eller bildskärmar; Delete tar bort markerade widgetar. Dubbelklick på en "
    L"post visar widgeten och markerar den kort. Klicka på en dag i kalendern för att välja och "
    L"kopiera den i valt format; alla format finns på alla språk. När flera widgetar är markerade "
    L"inaktiveras widgetalternativen, men de globala flikarna Tid och Program förblir tillgängliga. "
    L"Insert växlar markeringen av den aktuella posten och flyttar listmarkören en rad ned. Ctrl+C "
    L"kopierar markerade widgetar. Ctrl+V lägger kopior sist i listordning med ett namntillägg på "
    L"programspråket. Ctrl+A, Ctrl+C, Ctrl+V, Delete och Insert fungerar också från Ta bort och "
    L"Duplicera och flyttar fokus till listan före åtgärden. Upp till 32 widgetar tillåts. Vid "
    L"duplicering eller inklistring läggs kopior till i ordning tills gränsen nås; ett meddelande "
    L"visas för de återstående. Tryck Alt+0, Alt+1, Alt+2 eller Alt+3 på Analog klocka eller Kalender "
    L"med klocka för att välja huvudurtavlans storlek, från minst till störst.",
    L"\r\n\r\nVALINTA JA PÄIVÄMÄÄRÄ\r\nNapsauta hiiren kakkospainikkeella ja valitse Asetukset valitaksesi "
    L"kyseisen pienoisohjelman. Ctrl+A valitsee kaikki pienoisohjelmat tai näytöt; Delete poistaa "
    L"valitut pienoisohjelmat. Luettelon kaksoisnapsautus näyttää pienoisohjelman ja korostaa sen "
    L"hetkeksi. Kalenteripäivän napsautus valitsee ja kopioi sen valitussa muodossa; kaikki muodot "
    L"ovat käytettävissä kaikilla kielillä. Kun useita pienoisohjelmia on valittu, niiden asetukset "
    L"poistetaan käytöstä, mutta yleiset Aika- ja Sovellus-välilehdet pysyvät käytettävissä. Insert "
    L"vaihtaa nykyisen kohteen valinnan ja siirtää luettelokohdistinta yhden rivin alaspäin. Ctrl+C "
    L"kopioi valitut pienoisohjelmat. Ctrl+V lisää kopiot loppuun luettelon järjestyksessä ja liittää "
    L"nimeen sovelluksen kielisen päätteen. Ctrl+A, Ctrl+C, Ctrl+V, Delete ja Insert toimivat myös "
    L"Poista- ja Monista-painikkeista ja siirtävät kohdistuksen luetteloon ennen toimintoa. "
    L"Pienoisohjelmia voi olla enintään 32. Monistettaessa tai liitettäessä kopiot lisätään "
    L"järjestyksessä rajaan asti; jäljelle jäävistä näytetään ilmoitus. Valitse pääkellotaulun koko "
    L"pienimmästä suurimpaan näppäimillä Alt+0, Alt+1, Alt+2 tai Alt+3 Analoginen kello- tai "
    L"Kalenteri ja kello -pienoisohjelmassa.",
    L"\r\n\r\nMARKERING OG DATO\r\nHøjreklik og Indstillinger markerer den pågældende widget. Ctrl+A "
    L"markerer alle widgets eller skærme; Delete fjerner markerede widgets. Dobbeltklik på en post "
    L"viser widgeten og fremhæver den kort. Klik på en kalenderdag for at vælge og kopiere den i det "
    L"valgte format; alle formater findes på alle sprog. Når flere widgets er markeret, deaktiveres "
    L"widgetvalgene, men de globale faner Tid og Program forbliver tilgængelige. Insert skifter "
    L"markeringen af det aktuelle element og flytter listemarkøren én række ned. Ctrl+C kopierer "
    L"markerede widgets. Ctrl+V tilføjer kopier nederst i listens rækkefølge med et navnetillæg på "
    L"programmets sprog. Ctrl+A, Ctrl+C, Ctrl+V, Delete og Insert virker også fra Fjern og Dupliker "
    L"og flytter fokus til listen før handlingen. Der kan være op til 32 widgets. Ved duplikering "
    L"eller indsættelse tilføjes kopier i rækkefølge indtil grænsen; en meddelelse vises for resten. "
    L"Tryk Alt+0, Alt+1, Alt+2 eller Alt+3 på Analogt ur eller Kalender med ur for at vælge "
    L"hovedurskivens størrelse, fra mindst til størst.",
    L"\r\n\r\nVAL OG DAGSETNING\r\nHægrismellur og Stillingar velja viðkomandi græju. Ctrl+A velur allar "
    L"græjur eða skjái; Delete fjarlægir valdar græjur. Tvísmellur á færslu sýnir græjuna og "
    L"auðkennir hana stuttlega. Smelltu á dag í dagatali til að velja og afrita hann á völdu sniði; "
    L"öll snið eru tiltæk á öllum tungumálum. Þegar margar græjur eru valdar óvirkjast "
    L"græjustillingarnar, en almennu fliparnir Tími og Forrit eru áfram tiltækir. Insert víxlar vali "
    L"núverandi færslu og færir listabendilinn eina línu niður. Ctrl+C afritar valdar græjur. Ctrl+V "
    L"bætir afritum aftast í röð listans með viðskeyti á tungumáli forritsins. Ctrl+A, Ctrl+C, "
    L"Ctrl+V, Delete og Insert virka líka á Fjarlægja og Afrita og færa fókus í listann áður en "
    L"aðgerðin er framkvæmd. Að hámarki eru 32 græjur leyfðar. Við afritun eða límingu er afritum "
    L"bætt við í röð þar til hámarkinu er náð; tilkynning birtist um þau sem eftir eru. Ýttu á Alt+0, "
    L"Alt+1, Alt+2 eða Alt+3 á græjunum Vísaklukka og Dagatal með klukku til að velja stærð "
    L"aðalskífunnar, frá minnstu til stærstu.",
    L"\r\n\r\nSEÇİM VE TARİH\r\nSağ tıklayıp Ayarlar'ı seçmek ilgili aracı seçer. Ctrl+A tüm araçları veya "
    L"monitörleri seçer; Delete seçili araçları kaldırır. Listedeki bir öğeye çift tıklamak aracı "
    L"görünür yapar ve kısa süre vurgular. Takvimde bir güne tıklamak günü seçili biçimde panoya "
    L"kopyalar; tüm biçimler tüm dillerde kullanılabilir. Birden çok araç seçildiğinde araca özgü "
    L"seçenekler devre dışı kalır, ancak genel Zaman ve Uygulama sekmeleri kullanılabilir. Insert "
    L"geçerli öğenin seçimini değiştirir ve liste imlecini bir satır aşağı taşır. Ctrl+C seçili "
    L"araçları kopyalar. Ctrl+V kopyaları liste sırasıyla sona ekler ve adlarına uygulama dilinde bir "
    L"ek getirir. Ctrl+A, Ctrl+C, Ctrl+V, Delete ve Insert, Kaldır ve Çoğalt düğmelerinde de çalışır "
    L"ve işlemden önce odağı listeye taşır. En fazla 32 araç kullanılabilir. Çoğaltırken veya "
    L"yapıştırırken kopyalar sınıra kadar sırayla eklenir; kalan kopyalar için bir bildirim "
    L"gösterilir. Analog saat veya Saatli takvim aracında ana kadranın boyutunu küçükten büyüğe "
    L"seçmek için Alt+0, Alt+1, Alt+2 veya Alt+3 tuşlarına basın."
};

const wchar_t* HELP_LAYOUT_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nROZLOŽENÍ WIDGETŮ\r\nPříkaz Zarovnat do mřížky zachová přibližné ruční rozmístění, posune "
    L"středy widgetů na nejbližší body mřížky a odstraní překrytí. V nabídce widgetu se upraví jeho "
    L"monitor, z ikony všechny monitory samostatně. Opakování rozložení nemění. Dvojklik v Nastavení "
    L"označí widget rychlým světlemodrým blikáním; budík bliká pomaleji červeně. Vypnutí Vždy navrchu "
    L"pošle widget dozadu. V panelu s kalendářem a hodinami je horní datum odkaz na dnešek; spodní "
    L"odkaz otevře klasické nastavení data a času Windows. Je-li přichytávání zapnuté, při tažení se "
    L"widget do vzdálenosti pěti pixelů přichytí k hraně pracovní plochy. Při změně velikosti zůstane "
    L"přichycený ke stejnému okraji nebo ke stejným dvěma okrajům.\r\n\r\nV samostatném kalendáři lze "
    L"řádek Dnes zapnout nebo vypnout na kartě Vzhled i v nabídce widgetu. Přejít na dnešek vybere "
    L"dnešní datum a vrátí měsíční zobrazení. Při změně dne podle času widgetu se dnešek vybere "
    L"automaticky, ale aktuální druh zobrazení kalendáře se zachová.",
    L"\r\n\r\nWIDGET LAYOUT\r\nArrange in a grid preserves the approximate manual layout, snaps widget "
    L"centers to the nearest grid points and removes overlaps. A widget menu affects its monitor; the "
    L"notification icon applies it to every monitor separately. Repeating the command keeps the "
    L"layout stable. A Settings double-click identifies a widget with a fast light-blue flash; an "
    L"alarm flashes more slowly in red. Turning off Always on top sends the widget to the back. In a "
    L"calendar-and-clock panel, the upper link returns the calendar to today and the lower link opens "
    L"the classic Windows Date and Time settings. When edge snapping is enabled, a dragged widget "
    L"within five pixels snaps to a work-area edge. When resized, it remains attached to the same "
    L"edge or pair of edges.\r\n\r\nFor a standalone calendar, show or hide the Today row on the "
    L"Appearance tab or in the widget menu. Go to Today selects today and returns to the month view. "
    L"When the date changes according to the widget’s time, today is selected automatically while the "
    L"current calendar view is preserved.",
    L"\r\n\r\nWIDGET-ANORDNUNG\r\nIm Raster anordnen behält die ungefähre manuelle Anordnung bei, richtet "
    L"die Mittelpunkte am nächsten Rasterpunkt aus und beseitigt Überlappungen. Das Widget-Menü wirkt "
    L"auf seinen Monitor, das Symbol auf alle Monitore einzeln. Wiederholen ändert die Anordnung "
    L"nicht. Die Kennzeichnung blinkt schnell hellblau, der Alarm langsamer rot. Das Abschalten von "
    L"Immer im Vordergrund schickt das Widget nach hinten. Im Kalender-Uhr-Panel ist das obere Datum "
    L"ein Link zum heutigen Tag, der untere Link öffnet die klassischen Windows-Einstellungen für "
    L"Datum und Uhrzeit. Wenn das Einrasten aktiviert ist, rastet ein Widget beim Ziehen innerhalb "
    L"von fünf Pixeln am Rand der Arbeitsfläche ein. Beim Ändern der Größe bleibt es am selben Rand "
    L"oder an demselben Randpaar angeheftet.\r\n\r\nBei einem einzelnen Kalender lässt sich die "
    L"Heute-Zeile unter Darstellung oder im Widget-Menü ein- und ausblenden. Gehe zu Heute wählt den "
    L"heutigen Tag und die Monatsansicht. Beim Datumswechsel gemäß der Widget-Zeit wird heute "
    L"automatisch ausgewählt; die aktuelle Kalenderansicht bleibt erhalten.",
    L"\r\n\r\nDISPOSITION\r\nAligner sur une grille conserve leur disposition manuelle approximative, "
    L"aligne leurs centres sur la grille la plus proche et supprime les chevauchements. Le menu du "
    L"widget agit sur son écran, l’icône sur chaque écran séparément. La commande répétée reste "
    L"stable. L’identification clignote rapidement en bleu clair, l’alarme plus lentement en rouge. "
    L"Désactiver Toujours visible envoie le widget à l’arrière-plan. Dans le panneau "
    L"calendrier-horloge, la date supérieure est un lien vers aujourd’hui et le lien inférieur ouvre "
    L"les paramètres classiques Date et heure de Windows. Lorsque l’accrochage est activé, le widget "
    L"déplacé s’accroche au bord de la zone de travail à moins de cinq pixels. Lors du "
    L"redimensionnement, il reste accroché au même bord ou à la même paire de bords.\r\n\r\nPour un "
    L"calendrier autonome, affichez ou masquez la ligne Aujourd’hui dans Apparence ou dans le menu du "
    L"widget. Aller à aujourd’hui sélectionne la date du jour et revient à la vue mensuelle. Au "
    L"changement de date selon l’heure du widget, le jour courant est sélectionné automatiquement "
    L"sans changer le type de vue.",
    L"\r\n\r\nDISTRIBUCIÓN\r\nAlinear en cuadrícula conserva la distribución manual aproximada, ajusta sus "
    L"centros a la cuadrícula más cercana y elimina superposiciones. El menú del widget actúa en su "
    L"monitor; el icono, en cada monitor por separado. Repetir no cambia la distribución. La "
    L"identificación parpadea rápido en azul claro y la alarma más despacio en rojo. Desactivar "
    L"Siempre visible envía el widget al fondo. En el panel de calendario y reloj, la fecha superior "
    L"es un enlace a hoy y el enlace inferior abre la configuración clásica de Fecha y hora de "
    L"Windows. Con el ajuste activado, el widget se acopla al borde del área de trabajo al "
    L"arrastrarlo a menos de cinco píxeles. Al cambiar de tamaño, permanece acoplado al mismo borde o "
    L"al mismo par de bordes.\r\n\r\nEn un calendario independiente, muestre u oculte la fila Hoy en "
    L"Apariencia o en el menú del widget. Ir a hoy selecciona la fecha actual y vuelve a la vista "
    L"mensual. Al cambiar la fecha según la hora del widget, se selecciona automáticamente el día "
    L"actual sin cambiar el tipo de vista.",
    L"\r\n\r\nDISPOSIZIONE\r\nDisponi in griglia conserva la disposizione manuale approssimativa, allinea i "
    L"centri alla griglia più vicina ed elimina le sovrapposizioni. Il menu del widget agisce sul suo "
    L"monitor, l’icona su ogni monitor separatamente. Ripetere il comando non cambia la disposizione. "
    L"L’identificazione lampeggia rapidamente in azzurro, la sveglia più lentamente in rosso. "
    L"Disattivando Sempre in primo piano il widget viene mandato dietro. Nel pannello "
    L"calendario-orologio, la data superiore è un collegamento a oggi e quello inferiore apre le "
    L"impostazioni classiche Data e ora di Windows. Se l’aggancio è attivo, durante il trascinamento "
    L"il widget si aggancia al bordo dell’area di lavoro entro cinque pixel. Quando viene "
    L"ridimensionato, resta agganciato allo stesso bordo o alla stessa coppia di bordi.\r\n\r\nIn un "
    L"calendario autonomo, mostrare o nascondere la riga Oggi in Aspetto o nel menu del widget. Vai a "
    L"oggi seleziona la data corrente e torna alla vista mensile. Quando cambia la data secondo l’ora "
    L"del widget, viene selezionato automaticamente il giorno corrente mantenendo il tipo di vista.",
    L"\r\n\r\nUKŁAD WIDŻETÓW\r\nUłóż w siatce zachowuje przybliżony układ ręczny, przyciąga środki widżetów "
    L"do najbliższych punktów siatki i usuwa nakładanie. Menu widżetu działa na jego monitorze, a "
    L"ikona na każdym monitorze osobno. Powtórzenie nie zmienia układu. Identyfikacja miga szybko "
    L"jasnoniebiesko, alarm wolniej na czerwono. Wyłączenie Zawsze na wierzchu wysyła widżet do tyłu. "
    L"W panelu kalendarza z zegarem górna data jest odsyłaczem do dzisiejszego dnia, a dolny odsyłacz "
    L"otwiera klasyczne ustawienia daty i godziny systemu Windows. Po włączeniu przyciągania widżet "
    L"przeciągnięty na odległość najwyżej pięciu pikseli przyciąga się do krawędzi obszaru roboczego. "
    L"Po zmianie rozmiaru pozostaje przyciągnięty do tej samej krawędzi lub pary krawędzi.\r\n\r\nW "
    L"samodzielnym kalendarzu wiersz Dzisiaj można pokazać lub ukryć na karcie Wygląd albo w menu "
    L"widżetu. Przejdź do dnia dzisiejszego wybiera bieżącą datę i widok miesiąca. Przy zmianie daty "
    L"według czasu widżetu bieżący dzień jest wybierany automatycznie, ale rodzaj widoku pozostaje "
    L"bez zmian.",
    L"\r\n\r\nROZLOŽENIE WIDGETOV\r\nZarovnať do mriežky zachová približné ručné rozmiestnenie, pritiahne "
    L"stredy widgetov k najbližším bodom mriežky a odstráni prekrývanie. Ponuka widgetu upraví jeho "
    L"monitor, ikona každý monitor samostatne. Opakovanie rozloženie nemení. Identifikácia bliká "
    L"rýchlo svetlomodro, budík pomalšie načerveno. Vypnutie Vždy navrchu pošle widget dozadu. V "
    L"paneli s kalendárom a hodinami je horný dátum odkazom na dnešok; spodný odkaz otvorí klasické "
    L"nastavenie dátumu a času Windows. Ak je prichytávanie zapnuté, pri ťahaní sa widget vo "
    L"vzdialenosti najviac piatich pixelov prichytí k okraju pracovnej plochy. Pri zmene veľkosti "
    L"zostane prichytený k rovnakému okraju alebo k rovnakej dvojici okrajov.\r\n\r\nV samostatnom "
    L"kalendári možno riadok Dnes zapnúť alebo vypnúť na karte Vzhľad aj v ponuke widgetu. Prejsť na "
    L"dnešný deň vyberie dnešný dátum a obnoví mesačné zobrazenie. Pri zmene dňa podľa času widgetu "
    L"sa dnešok vyberie automaticky, ale aktuálny druh zobrazenia sa zachová.",
    L"\r\n\r\nWIDGET LAYOUT\r\nArrange in a grid preserves the approximate manual layout, snaps widget "
    L"centres to the nearest grid points and removes overlaps. A widget menu affects its monitor; the "
    L"notification icon applies it to every monitor separately. Repeating the command keeps the "
    L"layout stable. A Settings double-click identifies a widget with a fast light-blue flash; an "
    L"alarm flashes more slowly in red. Turning off Always on top sends the widget to the back. In a "
    L"calendar-and-clock panel, the upper link returns the calendar to today and the lower link opens "
    L"the classic Windows Date and Time settings. When edge snapping is enabled, a dragged widget "
    L"within five pixels snaps to a work-area edge. When resized, it remains attached to the same "
    L"edge or pair of edges.\r\n\r\nFor a standalone calendar, show or hide the Today row on the "
    L"Appearance tab or in the widget menu. Go to Today selects today and returns to the month view. "
    L"When the date changes according to the widget’s time, today is selected automatically while the "
    L"current calendar view is preserved.",
    L"\r\n\r\nWIDGET LAYOUT\r\nArrange in a grid preserves the approximate manual layout, snaps widget "
    L"centres to the nearest grid points and removes overlaps. A widget menu affects its monitor; the "
    L"notification icon applies it to every monitor separately. Repeating the command keeps the "
    L"layout stable. A Settings double-click identifies a widget with a fast light-blue flash; an "
    L"alarm flashes more slowly in red. Turning off Always on top sends the widget to the back. In a "
    L"calendar-and-clock panel, the upper link returns the calendar to today and the lower link opens "
    L"the classic Windows Date and Time settings. When edge snapping is enabled, a dragged widget "
    L"within five pixels snaps to a work-area edge. When resized, it remains attached to the same "
    L"edge or pair of edges.\r\n\r\nFor a standalone calendar, show or hide the Today row on the "
    L"Appearance tab or in the widget menu. Go to Today selects today and returns to the month view. "
    L"When the date changes according to the widget’s time, today is selected automatically while the "
    L"current calendar view is preserved.",
    L"\r\n\r\nDISPOSIÇÃO\r\nQuando o ajuste está ativado, os widgets prendem-se às margens da área de "
    L"trabalho a cinco píxeis e permanecem presos ao redimensionar. Dispor numa grelha move os outros "
    L"widgets para posições próximas sem sobreposição, mantendo o widget de referência no lugar. Os "
    L"relógios de monitor são ignorados. No painel com calendário e relógio, a ligação superior volta "
    L"a hoje e a inferior abre as definições clássicas de Data e Hora do Windows; ambas funcionam com "
    L"rato e teclado.\r\n\r\nNum calendário autónomo, mostre ou oculte a linha Hoje em Aspeto ou no menu "
    L"do widget. Ir para hoje seleciona a data atual e regressa à vista mensal. Quando a data muda "
    L"segundo a hora do widget, o dia atual é selecionado automaticamente, mantendo o tipo de vista.",
    L"\r\n\r\nPLASSERING\r\nNår kantfesting er aktivert, festes widgeter til kanten av arbeidsområdet innen "
    L"fem piksler og forblir festet ved størrelsesendring. Ordne i et rutenett flytter de andre "
    L"widgetene til nærliggende plasser uten overlapping, mens referansewidgeten blir stående. "
    L"Skjermklokker ignoreres. I kalender- og klokke-panelet går den øvre lenken til i dag, og den "
    L"nedre åpner de klassiske innstillingene for dato og klokkeslett i Windows; begge virker med mus "
    L"og tastatur.\r\n\r\nI en frittstående kalender kan I dag-raden vises eller skjules på fanen "
    L"Utseende eller i widgetmenyen. Gå til i dag velger dagens dato og månedsvisningen. Når datoen "
    L"endres etter widgetens tid, velges i dag automatisk uten å endre visningstypen.",
    L"\r\n\r\nPLACERING\r\nNär kantfästning är aktiverad fäster widgetar vid arbetsytans kanter inom fem "
    L"bildpunkter och förblir fästa när storleken ändras. Ordna i rutnät flyttar de andra widgetarna "
    L"till närliggande platser utan överlappning medan referenswidgeten står kvar. Skärmklockor "
    L"ignoreras. I kalender- och klockpanelen går den övre länken till i dag och den nedre öppnar "
    L"Windows klassiska inställningar för datum och tid; båda fungerar med mus och tangentbord.\r\n\r\nI "
    L"en fristående kalender kan raden I dag visas eller döljas på fliken Utseende eller i "
    L"widgetmenyn. Gå till i dag väljer dagens datum och månadsvyn. När datumet ändras enligt "
    L"widgetens tid väljs dagens datum automatiskt utan att ändra vytypen.",
    L"\r\n\r\nASETTELU\r\nKun reunakiinnitys on käytössä, pienoisohjelmat tarttuvat työalueen reunoihin "
    L"viiden kuvapisteen etäisyydellä ja pysyvät kiinni koon muuttuessa. Järjestä ruudukkoon siirtää "
    L"muut pienoisohjelmat läheisiin, päällekkäisyyksiä välttäviin paikkoihin ja pitää viiteohjelman "
    L"paikallaan. Näyttökellot ohitetaan. Kalenteri- ja kellopaneelin ylälinkki palauttaa tämän "
    L"päivän ja alalinkki avaa Windowsin perinteiset päivämäärä- ja aika-asetukset; molempia voi "
    L"käyttää hiirellä ja näppäimistöllä.\r\n\r\nErillisen kalenterin Tänään-rivin voi näyttää tai "
    L"piilottaa Ulkoasu-välilehdellä tai pienoisohjelman valikossa. Siirry tähän päivään valitsee "
    L"nykyisen päivän ja kuukausinäkymän. Päivämäärän vaihtuessa pienoisohjelman ajan mukaan nykyinen "
    L"päivä valitaan automaattisesti näkymätyyppiä muuttamatta.",
    L"\r\n\r\nPLACERING\r\nNår kantfastgørelse er slået til, fastgøres widgets til arbejdsområdets kanter "
    L"inden for fem pixel og forbliver fastgjort ved størrelsesændring. Arranger i gitter flytter de "
    L"øvrige widgets til nærliggende pladser uden overlapning og lader referencewidgeten blive "
    L"stående. Skærmure ignoreres. I kalender- og urpanelet går det øverste link til i dag, og det "
    L"nederste åbner Windows' klassiske indstillinger for dato og klokkeslæt; begge virker med mus og "
    L"tastatur.\r\n\r\nI en selvstændig kalender kan rækken I dag vises eller skjules på fanen Udseende "
    L"eller i widgetmenuen. Gå til i dag vælger dags dato og månedsvisningen. Når datoen ændres efter "
    L"widgetens tid, vælges dagens dato automatisk uden at ændre visningstypen.",
    L"\r\n\r\nUPPRÖÐUN\r\nÞegar festing við brúnir er virk festast græjur við brúnir vinnusvæðisins innan "
    L"fimm mynddíla og haldast fastar þegar stærð breytist. Raða á hnitanet færir aðrar græjur á "
    L"nálæga staði án skörunar en heldur viðmiðunargræjunni kyrrri. Skjáklukkur eru hunsaðar. Í "
    L"dagatals- og klukkuspjaldinu fer efri tengillinn á daginn í dag og sá neðri opnar hefðbundnar "
    L"dagsetningar- og tímastillingar Windows; báðir virka með mús og lyklaborði.\r\n\r\nÍ sjálfstæðu "
    L"dagatali má sýna eða fela Í dag-línuna á Útlit-flipanum eða í valmynd græjunnar. Fara á daginn "
    L"í dag velur daginn í dag og mánaðarsýn. Þegar dagsetning breytist samkvæmt tíma græjunnar er "
    L"dagurinn í dag valinn sjálfkrafa án þess að breyta gerð dagatalssýnar.",
    L"\r\n\r\nDÜZEN\r\nKenar yapışması etkinleştirildiğinde araçlar çalışma alanının kenarlarına beş piksel "
    L"içinde yapışır ve boyut değişirken yapışık kalır. Izgarada düzenle, başvuru aracını yerinde "
    L"tutarak diğer araçları çakışmayan yakın konumlara taşır. Monitör saatleri hesaba katılmaz. "
    L"Takvim ve saat panelinde üst bağlantı bugüne döner, alt bağlantı Windows'un klasik Tarih ve "
    L"Saat ayarlarını açar; ikisi de fare ve klavyeyle çalışır.\r\n\r\nBağımsız takvimde Bugün satırını "
    L"Görünüm sekmesinden veya araç menüsünden gösterip gizleyebilirsiniz. Bugüne git, bugünün "
    L"tarihini seçer ve ay görünümüne döner. Aracın saatine göre tarih değiştiğinde görünüm türü "
    L"korunarak bugünün tarihi otomatik seçilir."
};

const wchar_t* HELP_STORAGE_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nVZHLED A ÚLOŽIŠTĚ\r\nZměny vzhledu se ukazují ihned v živém náhledu; Zrušit vrátí nepoužitý "
    L"vzhled a Výchozí vzhled obnoví výchozí hodnoty daného typu. Digitální hodiny nabízejí písmo, "
    L"vyhlazování, barvy, neprůhlednost, odsazení, šířku rámečku a průhledné pozadí. Digitální "
    L"hodiny, kalendář a panel mají stejné čtyři styly rámečku; u jednoduchého rámečku lze zvolit "
    L"jeho barvu. Panel má samostatná písma horního řádku, času a spodního řádku, úvodní nulu a "
    L"volitelnou velikost ciferníku. Motivy a vyhlazování lze nastavit pro aplikaci i widget; písmo "
    L"nativního kalendáře lze měnit jen při zakázaných motivech. Nastavení lze exportovat do XML. "
    L"Import XML okamžitě načte a uloží nastavení do právě zvoleného úložiště; typ úložiště nezmění. "
    L"Automatické XML je v %AppData%\\FortSoft\\CalClock\\settings.xml. Po úspěšném zápisu XML se "
    L"odstraní větev HKCU\\SOFTWARE\\FortSoft\\CalClock; při ukládání do registru se automatické XML "
    L"odstraní.\r\n\r\nVyhlazování písma nabízí ClearType, GDI a Žádné.\r\n\r\nÚvodní nula nabízí Zobrazit "
    L"(výchozí), S místem a Bez místa. Volba S místem skryje nulu a rezervuje její šířku ve zvoleném "
    L"písmu; ostatní číslice zůstanou na stejných místech i u proporcionálního písma. Hodiny na "
    L"monitoru zůstávají zarovnané na střed včetně rezervovaného místa. Řádek UTC si zachovává "
    L"vlastní zarovnání na střed.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live preview; Cancel "
    L"restores unapplied appearance and Default appearance restores the defaults for that widget "
    L"type. Digital clocks provide font, smoothing, colors, opacity, padding, border width and a "
    L"transparent background. Digital clocks, calendars and panels share four border styles; the "
    L"single-line border has a selectable color. The panel has separate fonts for its top row, time "
    L"and bottom row, a leading zero and selectable clock-face sizes. Themes and font smoothing can "
    L"be set for the application and each widget; the native calendar font is selectable only when "
    L"themes are disabled. Settings can be exported to XML. Importing XML immediately loads and saves "
    L"the settings to the currently selected storage without changing the storage type. Automatic XML "
    L"is %AppData%\\FortSoft\\CalClock\\settings.xml. After writing XML, HKCU\\SOFTWARE\\FortSoft\\CalClock "
    L"is removed; registry storage removes the automatic XML.\r\n\r\nFont antialiasing offers ClearType, "
    L"GDI, and None.\r\n\r\nLeading zero offers Show (default), Keep space, and No space. Keep space "
    L"hides the zero while reserving its width in the selected font; the other digits keep their "
    L"positions even with proportional fonts. Monitor clocks remain centered, including the reserved "
    L"space. The UTC row keeps its own center alignment.",
    L"\r\n\r\nDARSTELLUNG UND SPEICHERUNG\r\nDarstellungsänderungen erscheinen sofort in der Vorschau; "
    L"Abbrechen stellt nicht angewandte Werte wieder her, Standarddarstellung die Vorgaben des "
    L"Widget-Typs. Digitaluhren bieten Schrift, Glättung, Farben, Deckkraft, Innenabstand, "
    L"Rahmenbreite und transparenten Hintergrund. Digitaluhren, Kalender und Panel verwenden "
    L"dieselben vier Rahmenarten; für den einfachen Rahmen ist die Farbe wählbar. Das Panel besitzt "
    L"getrennte Schriften für obere Zeile, Zeit und untere Zeile, eine führende Null und wählbare "
    L"Zifferblattgrößen. Designs und Schriftglättung gelten wahlweise für Anwendung oder Widget; die "
    L"native Kalenderschrift ist nur bei deaktivierten Designs wählbar. Einstellungen können als XML "
    L"exportiert werden. Ein XML-Import lädt und speichert die Einstellungen sofort im aktuell "
    L"gewählten Speicher, ohne die Speicherart zu ändern. Automatisches XML liegt in "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml; XML-Speicherung entfernt "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock, Registrierungsspeicherung entfernt das automatische "
    L"XML.\r\n\r\nFür die Schriftglättung stehen ClearType, GDI und Keine zur Auswahl.\r\n\r\nFührende Null "
    L"bietet Anzeigen (Standard), Platz freihalten und Ohne Platz. Platz freihalten blendet die Null "
    L"aus und reserviert ihre Breite in der gewählten Schrift; andere Ziffern bleiben auch bei "
    L"proportionalen Schriften an derselben Position. Monitoruhren bleiben mit dem reservierten Platz "
    L"zentriert, die UTC-Zeile bleibt separat zentriert.",
    L"\r\n\r\nAPPARENCE ET STOCKAGE\r\nLes changements d’apparence sont prévisualisés immédiatement ; "
    L"Annuler restaure les valeurs non appliquées et Apparence par défaut celles du type de widget. "
    L"Les horloges numériques proposent police, lissage, couleurs, opacité, marge, largeur de bordure "
    L"et fond transparent. Horloges numériques, calendriers et panneaux partagent quatre styles de "
    L"bordure ; la couleur de la bordure simple est sélectionnable. Le panneau possède des polices "
    L"distinctes pour les lignes supérieure, horaire et inférieure, un zéro initial et des tailles de "
    L"cadran au choix. Thèmes et lissage se règlent pour l’application et le widget ; la police du "
    L"calendrier natif n’est sélectionnable que si les thèmes sont désactivés. Les paramètres peuvent "
    L"être exportés en XML. L’import XML charge et enregistre immédiatement les paramètres dans le "
    L"stockage sélectionné, sans changer son type. Le XML automatique est "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml ; son écriture retire HKCU\\SOFTWARE\\FortSoft\\CalClock, "
    L"tandis que le registre retire ce XML.\r\n\r\nLe lissage des polices propose ClearType, GDI et "
    L"Aucun.\r\n\r\nLe zéro initial propose Afficher (par défaut), Garder la place et Sans espace. Garder "
    L"la place masque le zéro en réservant sa largeur dans la police choisie ; les autres chiffres "
    L"gardent leur position, même avec une police proportionnelle. Les horloges de moniteur restent "
    L"centrées, espace réservé compris. La ligne UTC reste centrée séparément.",
    L"\r\n\r\nAPARIENCIA Y ALMACENAMIENTO\r\nLos cambios de apariencia se previsualizan al instante; "
    L"Cancelar restaura los no aplicados y Apariencia predeterminada los valores del tipo de widget. "
    L"Los relojes digitales ofrecen fuente, suavizado, colores, opacidad, relleno, ancho de borde y "
    L"fondo transparente. Los relojes digitales, calendarios y paneles comparten cuatro estilos de "
    L"borde; el color del borde simple es seleccionable. El panel tiene fuentes separadas para la "
    L"línea superior, la hora y la inferior, cero inicial y tamaños de esfera seleccionables. Temas y "
    L"suavizado se configuran para la aplicación y para cada widget; la fuente del calendario nativo "
    L"solo se elige con temas desactivados. Los ajustes se pueden exportar a XML. La importación XML "
    L"carga y guarda inmediatamente los ajustes en el almacenamiento seleccionado sin cambiar su "
    L"tipo. El XML automático es %AppData%\\FortSoft\\CalClock\\settings.xml; al escribirlo se elimina "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock y al usar el registro se elimina el XML automático.\r\n\r\nEl "
    L"suavizado de fuente ofrece ClearType, GDI y Ninguno.\r\n\r\nEl cero inicial ofrece Mostrar "
    L"(predeterminado), Reservar espacio y Sin espacio. Reservar espacio oculta el cero y conserva su "
    L"anchura en la fuente elegida; los demás dígitos mantienen su posición incluso con fuentes "
    L"proporcionales. Los relojes de monitor permanecen centrados, incluido el espacio reservado. La "
    L"línea UTC mantiene su propio centrado.",
    L"\r\n\r\nASPETTO E ARCHIVIAZIONE\r\nLe modifiche all’aspetto sono mostrate subito nell’anteprima; "
    L"Annulla ripristina quelle non applicate e Aspetto predefinito i valori del tipo di widget. Gli "
    L"orologi digitali offrono carattere, antialiasing, colori, opacità, margine, larghezza del bordo "
    L"e sfondo trasparente. Orologi digitali, calendari e pannelli condividono quattro stili di "
    L"bordo; il colore del bordo semplice è selezionabile. Il pannello ha caratteri separati per riga "
    L"superiore, ora e riga inferiore, zero iniziale e dimensioni selezionabili del quadrante. Temi e "
    L"antialiasing si impostano per applicazione e widget; il carattere del calendario nativo è "
    L"selezionabile solo con temi disattivati. Le impostazioni possono essere esportate in XML. "
    L"L’importazione XML carica e salva subito le impostazioni nell’archivio selezionato, senza "
    L"cambiarne il tipo. L’XML automatico è %AppData%\\FortSoft\\CalClock\\settings.xml; scriverlo "
    L"rimuove HKCU\\SOFTWARE\\FortSoft\\CalClock, mentre il registro rimuove l’XML "
    L"automatico.\r\n\r\nL’antialiasing del carattere offre ClearType, GDI e Nessuno.\r\n\r\nLo zero "
    L"iniziale "
    L"offre Mostra (predefinito), Riserva spazio e Senza spazio. Riserva spazio nasconde lo zero "
    L"riservandone la larghezza nel carattere scelto; le altre cifre mantengono la posizione anche "
    L"con caratteri proporzionali. Gli orologi sul monitor restano centrati, incluso lo spazio "
    L"riservato. La riga UTC mantiene il proprio allineamento centrale.",
    L"\r\n\r\nWYGLĄD I ZAPIS\r\nZmiany wyglądu są od razu widoczne w podglądzie; Anuluj przywraca "
    L"niezastosowane wartości, a Wygląd domyślny wartości danego typu widżetu. Zegary cyfrowe oferują "
    L"czcionkę, wygładzanie, kolory, krycie, odstęp, szerokość ramki i przezroczyste tło. Zegary "
    L"cyfrowe, kalendarze i panele mają te same cztery style ramki; kolor prostej ramki można wybrać. "
    L"Panel ma osobne czcionki górnego wiersza, czasu i dolnego wiersza, zero wiodące oraz różne "
    L"rozmiary tarczy. Motywy i wygładzanie ustawia się dla aplikacji i widżetu; czcionkę natywnego "
    L"kalendarza można wybrać tylko przy wyłączonych motywach. Ustawienia można eksportować do XML. "
    L"Import XML natychmiast wczytuje i zapisuje ustawienia w wybranym magazynie, nie zmieniając jego "
    L"rodzaju. Automatyczny XML to %AppData%\\FortSoft\\CalClock\\settings.xml; zapis XML usuwa "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock, a zapis w rejestrze usuwa automatyczny XML.\r\n\r\nWygładzanie "
    L"czcionki oferuje ClearType, GDI i Brak.\r\n\r\nZero wiodące oferuje Pokaż (domyślnie), Zachowaj "
    L"miejsce i Bez miejsca. Zachowaj miejsce ukrywa zero, rezerwując jego szerokość w wybranej "
    L"czcionce; pozostałe cyfry zachowują położenie także w czcionkach proporcjonalnych. Zegary na "
    L"monitorze pozostają wyśrodkowane wraz z zarezerwowanym miejscem. Wiersz UTC pozostaje osobno "
    L"wyśrodkowany.",
    L"\r\n\r\nVZHĽAD A UKLADANIE\r\nZmeny vzhľadu sa ihneď ukazujú v náhľade; Zrušiť vráti nepoužité "
    L"hodnoty a Predvolený vzhľad hodnoty daného typu widgetu. Digitálne hodiny ponúkajú písmo, "
    L"vyhladzovanie, farby, nepriehľadnosť, odsadenie, šírku rámčeka aj priehľadné pozadie. Digitálne "
    L"hodiny, kalendár a panel majú rovnaké štyri štýly rámčeka; pri jednoduchom rámčeku možno zvoliť "
    L"farbu. Panel má samostatné písma horného riadka, času a spodného riadka, úvodnú nulu a "
    L"voliteľnú veľkosť ciferníka. Motívy a vyhladzovanie sa nastavujú pre aplikáciu aj widget; písmo "
    L"natívneho kalendára možno vybrať iba pri zakázaných motívoch. Nastavenia možno exportovať do "
    L"XML. Import XML okamžite načíta a uloží nastavenia do práve zvoleného úložiska; typ úložiska "
    L"nezmení. Automatické XML je %AppData%\\FortSoft\\CalClock\\settings.xml; zápis XML odstráni "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock a ukladanie do registra odstráni automatické "
    L"XML.\r\n\r\nVyhladzovanie písma ponúka ClearType, GDI a Žiadne.\r\n\r\nÚvodná nula ponúka Zobraziť "
    L"(predvolené), S miestom a Bez miesta. Voľba S miestom skryje nulu a rezervuje jej šírku vo "
    L"zvolenom písme; ostatné číslice zostanú na rovnakých miestach aj pri proporcionálnom písme. "
    L"Hodiny na monitore zostávajú zarovnané na stred vrátane rezervovaného miesta. Riadok UTC si "
    L"zachováva vlastné zarovnanie na stred.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live preview; Cancel "
    L"restores unapplied appearance and Default appearance restores the defaults for that widget "
    L"type. Digital clocks provide font, smoothing, colours, opacity, padding, border width and a "
    L"transparent background. Digital clocks, calendars and panels share four border styles; the "
    L"single-line border has a selectable colour. The panel has separate fonts for its top row, time "
    L"and bottom row, a leading zero and selectable clock-face sizes. Themes and font smoothing can "
    L"be set for the application and each widget; the native calendar font is selectable only when "
    L"themes are disabled. Settings can be exported to XML. Importing XML immediately loads and saves "
    L"the settings to the currently selected storage without changing the storage type. Automatic XML "
    L"is %AppData%\\FortSoft\\CalClock\\settings.xml. After writing XML, HKCU\\SOFTWARE\\FortSoft\\CalClock "
    L"is removed; registry storage removes the automatic XML.\r\n\r\nFont antialiasing offers ClearType, "
    L"GDI, and None.\r\n\r\nLeading zero offers Show (default), Keep space, and No space. Keep space "
    L"hides the zero while reserving its width in the selected font; the other digits keep their "
    L"positions even with proportional fonts. Monitor clocks remain centered, including the reserved "
    L"space. The UTC row keeps its own center alignment.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live preview; Cancel "
    L"restores unapplied appearance and Default appearance restores the defaults for that widget "
    L"type. Digital clocks provide font, smoothing, colours, opacity, padding, border width and a "
    L"transparent background. Digital clocks, calendars and panels share four border styles; the "
    L"single-line border has a selectable colour. The panel has separate fonts for its top row, time "
    L"and bottom row, a leading zero and selectable clock-face sizes. Themes and font smoothing can "
    L"be set for the application and each widget; the native calendar font is selectable only when "
    L"themes are disabled. Settings can be exported to XML. Importing XML immediately loads and saves "
    L"the settings to the currently selected storage without changing the storage type. Automatic XML "
    L"is %AppData%\\FortSoft\\CalClock\\settings.xml. After writing XML, HKCU\\SOFTWARE\\FortSoft\\CalClock "
    L"is removed; registry storage removes the automatic XML.\r\n\r\nFont antialiasing offers ClearType, "
    L"GDI, and None.\r\n\r\nLeading zero offers Show (default), Keep space, and No space. Keep space "
    L"hides the zero while reserving its width in the selected font; the other digits keep their "
    L"positions even with proportional fonts. Monitor clocks remain centered, including the reserved "
    L"space. The UTC row keeps its own center alignment.",
    L"\r\n\r\nARMAZENAMENTO\r\nAs definições são guardadas no registo em HKCU\\SOFTWARE\\FortSoft\\CalClock "
    L"ou "
    L"num XML em %AppData%\\FortSoft\\CalClock\\settings.xml. Relógios digitais, calendários e painéis "
    L"partilham quatro estilos de moldura; a cor da moldura simples pode ser escolhida. A mudança de "
    L"armazenamento remove apenas os dados CalClock anteriores. As definições podem ser exportadas "
    L"para XML. A importação XML carrega e guarda imediatamente as definições no armazenamento "
    L"selecionado, sem alterar o seu tipo.\r\n\r\nA suavização do tipo de letra oferece ClearType, GDI e "
    L"Nenhuma.\r\n\r\nO zero inicial oferece Mostrar (predefinido), Reservar espaço e Sem espaço. "
    L"Reservar espaço oculta o zero e reserva a sua largura no tipo de letra escolhido; os outros "
    L"algarismos mantêm a posição mesmo com letras proporcionais. Os relógios no monitor permanecem "
    L"centrados, incluindo o espaço reservado. A linha UTC mantém o seu próprio alinhamento ao centro.",
    L"\r\n\r\nLAGRING\r\nInnstillinger lagres i registeret under HKCU\\SOFTWARE\\FortSoft\\CalClock eller "
    L"som "
    L"XML i %AppData%\\FortSoft\\CalClock\\settings.xml. Digitale klokker, kalendere og paneler har fire "
    L"felles kantstiler; fargen på den enkle kanten kan velges. Bytte av lagring fjerner bare "
    L"tidligere CalClock-data. Innstillinger kan eksporteres til XML. XML-import laster inn og lagrer "
    L"innstillingene umiddelbart i valgt lagring uten å endre lagringstypen.\r\n\r\nSkriftutjevning "
    L"tilbyr ClearType, GDI og Ingen.\r\n\r\nInnledende null tilbyr Vis (standard), Behold plass og Uten "
    L"plass. Behold plass skjuler nullen og reserverer bredden i valgt skrift; andre sifre beholder "
    L"plasseringen også med proporsjonale skrifter. Monitorklokker forblir sentrert, inkludert "
    L"reservert plass. UTC-linjen beholder sin egen sentrering.",
    L"\r\n\r\nLAGRING\r\nInställningar sparas i registret under HKCU\\SOFTWARE\\FortSoft\\CalClock eller som "
    L"XML i %AppData%\\FortSoft\\CalClock\\settings.xml. Digitala klockor, kalendrar och paneler har "
    L"fyra gemensamma kantstilar; färgen på den enkla kanten kan väljas. Byte av lagring tar bara "
    L"bort tidigare CalClock-data. Inställningar kan exporteras till XML. XML-import läser in och "
    L"sparar inställningarna direkt i vald lagring utan att ändra "
    L"lagringstypen.\r\n\r\nTeckensnittsutjämning erbjuder ClearType, GDI och Ingen.\r\n\r\nInledande nolla "
    L"erbjuder Visa (standard), Behåll utrymme och Utan utrymme. Behåll utrymme döljer nollan och "
    L"reserverar dess bredd i valt teckensnitt; övriga siffror behåller sina positioner även med "
    L"proportionella teckensnitt. Bildskärmsklockor förblir centrerade, inklusive reserverat utrymme. "
    L"UTC-raden behåller sin egen centrering.",
    L"\r\n\r\nTALLENNUS\r\nAsetukset tallennetaan rekisteriin kohtaan HKCU\\SOFTWARE\\FortSoft\\CalClock tai "
    L"XML-tiedostoon kansiossa %AppData%\\FortSoft\\CalClock\\settings.xml. Digitaalikelloilla, "
    L"kalentereilla ja paneeleilla on neljä yhteistä reunatyyliä; yksinkertaisen reunan väri voidaan "
    L"valita. Tallennustavan vaihto poistaa vain aiemmat CalClock-tiedot. Asetukset voi viedä "
    L"XML-tiedostoon. XML-tuonti lataa ja tallentaa asetukset heti valittuun tallennuspaikkaan "
    L"muuttamatta tallennustapaa.\r\n\r\nFontin pehmennyksen vaihtoehdot ovat ClearType, GDI ja Ei "
    L"mitään.\r\n\r\nEtunolla tarjoaa Näytä (oletus), Varaa tila ja Ilman tilaa. Varaa tila piilottaa "
    L"nollan mutta varaa sen leveyden valitussa fontissa; muut numerot säilyttävät paikkansa myös "
    L"suhteellisilla fonteilla. Näyttökellot pysyvät keskitettyinä varattu tila mukaan lukien. "
    L"UTC-rivi säilyttää oman keskityksensä.",
    L"\r\n\r\nLAGRING\r\nIndstillinger gemmes i registreringsdatabasen under "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock eller som XML i %AppData%\\FortSoft\\CalClock\\settings.xml. "
    L"Digitale ure, kalendere og paneler har fire fælles kanttyper; farven på den enkle kant kan "
    L"vælges. Skift af lager fjerner kun tidligere CalClock-data. Indstillinger kan eksporteres til "
    L"XML. XML-import indlæser og gemmer straks indstillingerne i det valgte lager uden at ændre "
    L"lagertypen.\r\n\r\nSkriftudjævning tilbyder ClearType, GDI og Ingen.\r\n\r\nForanstillet nul tilbyder "
    L"Vis (standard), Bevar plads og Uden plads. Bevar plads skjuler nullet og reserverer dets bredde "
    L"i den valgte skrifttype; øvrige cifre beholder deres placering også med proportionale "
    L"skrifttyper. Skærmure forbliver centrerede inklusive reserveret plads. UTC-linjen bevarer sin "
    L"egen centrering.",
    L"\r\n\r\nGEYMSLA\r\nStillingar eru vistaðar í skrásetningu undir HKCU\\SOFTWARE\\FortSoft\\CalClock eða "
    L"sem XML í %AppData%\\FortSoft\\CalClock\\settings.xml. Stafrænar klukkur, dagatöl og spjöld hafa "
    L"fjórar sameiginlegar rammagerðir; velja má lit einfalda rammans. Skipti um geymslu fjarlægja "
    L"aðeins eldri CalClock-gögn. Hægt er að flytja stillingar út sem XML. Innflutningur XML hleður "
    L"og vistar stillingarnar strax í valinni geymslu án þess að breyta gerð hennar.\r\n\r\nLeturjöfnun "
    L"býður upp á ClearType, GDI og Engin.\r\n\r\nNúll fremst býður upp á Sýna (sjálfgefið), Halda plássi "
    L"og Án pláss. Halda plássi felur núllið en tekur frá breidd þess í völdu letri; aðrir tölustafir "
    L"halda stöðu sinni jafnvel með misbreiðu letri. Skjáklukkur haldast miðjaðar með fráteknu "
    L"plássi. UTC-línan heldur eigin miðjun.",
    L"\r\n\r\nDEPOLAMA\r\nAyarlar HKCU\\SOFTWARE\\FortSoft\\CalClock altındaki kayıt defterinde veya "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml içindeki XML dosyasında saklanır. Dijital saatler, "
    L"takvimler ve paneller aynı dört kenarlık stilini kullanır; basit kenarlığın rengi seçilebilir. "
    L"Depolamayı değiştirmek yalnızca önceki CalClock verilerini kaldırır. Ayarlar XML olarak dışa "
    L"aktarılabilir. XML içe aktarma, depolama türünü değiştirmeden ayarları hemen yükler ve seçili "
    L"depolamaya kaydeder.\r\n\r\nYazı tipi kenar yumuşatma seçenekleri ClearType, GDI ve Yok "
    L"şeklindedir.\r\n\r\nBaştaki sıfır için Göster (varsayılan), Yer ayır ve Yer ayırma seçenekleri "
    L"vardır. Yer ayır, sıfırı gizleyip seçilen yazı tipindeki genişliğini korur; diğer rakamlar "
    L"orantılı yazı tiplerinde bile konumlarını korur. Monitör saatleri ayrılan alan dâhil ortalanır. "
    L"UTC satırı kendi orta hizalamasını korur."
};

const wchar_t* HELP_SETTINGS_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nNASTAVENÍ A NABÍDKY\r\nJazyk, písmo, vyhlazování, motivy, úložiště, spouštění s Windows a "
    L"přichytávání jsou globální a nastavují se na kartě Aplikace. Při prvním spuštění se jazyk volí "
    L"podle uživatelského jazyka Windows, neznámý jazyk se nahradí angličtinou (USA); jazyk, "
    L"vyhlazování a motivy widgetu platí jen pro něj. Změna jazyka se po použití promítne i do "
    L"otevřeného formuláře.\r\n\r\nNabídka widgetu obsahuje příslušné volby viditelnosti, režimu navrchu, "
    L"sekund, velikosti a kopírování data a dále Zarovnat do mřížky, Nastavení, Nápovědu, O programu "
    L"a Konec. Nabídka ikony uvádí widgety s pořadovými čísly a příkazy Zobrazit vše, Skrýt vše a "
    L"Ztlumit vše. Samostatně oddělený příkaz Zarovnat do mřížky následuje za nimi. Zobrazení či "
    L"obnovení přenese widgety dopředu bez změny Vždy navrchu. Další spuštění aktivuje běžící "
    L"instanci a v případě potřeby obnoví naposledy skryté widgety. Dostupné rozměry ciferníku a "
    L"možnost sekundové ručičky vycházejí z možností používané verze Windows; nedostupné Sekundy jsou "
    L"šedivé, ale uložená volba se zachová pro podporovanou velikost. Budík a signál lze zapnout "
    L"přímo v nabídce widgetu; položka Budík ukazuje čas a při částečném týdnu také aktivní dny. "
    L"Zaškrtnutí Ztlumit v nabídce widgetu odpovídá volbě Ztlumeno na kartě Obecné. Ztlumit vše v "
    L"nabídce ikony ztlumí všechny widgety a při dalším přepnutí obnoví jen ty, které samo ztlumilo. "
    L"Totéž globální přepnutí provede klávesa M na kterémkoli widgetu. Zapnutí budíku bez vybraného "
    L"dne otevře kartu Budík daného widgetu.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nApplication language, font, smoothing, themes, storage, Windows startup "
    L"and edge snapping are global and are configured on the Application tab. On first launch, the "
    L"application language follows the Windows user-interface language, with US English as the "
    L"fallback; widget language, smoothing and themes affect that widget only. An applied language "
    L"change also updates the open dialog.\r\n\r\nA widget menu contains the applicable visibility, "
    L"always-on-top, seconds, size and date-copy choices, followed by Arrange in a grid, Settings, "
    L"Help, About and Exit. The notification-icon menu lists numbered widgets and provides Show all, "
    L"Hide all and Mute all. The separately grouped Arrange in a grid command follows. Showing or "
    L"restoring widgets brings them forward without changing Always on top. Starting CalClock again "
    L"activates the running instance and restores the most recently hidden widgets when needed. "
    L"Available face sizes and second-hand support come from the installed Windows version; Seconds "
    L"is disabled when unavailable, but its saved choice is retained for a supported size. Alarm and "
    L"Signal can be toggled directly in a widget menu; Alarm shows its time and, for a partial week, "
    L"its active weekdays. Checked Mute in a widget menu corresponds to Muted on the General tab. "
    L"Mute all in the notification-icon menu mutes every widget and, when toggled again, restores "
    L"only those it muted. Pressing M on any widget performs the same global toggle. Enabling an "
    L"alarm with no weekday selected opens that widget’s Alarm tab.",
    L"\r\n\r\nEINSTELLUNGEN UND MENÜS\r\nAnwendungssprache, Schrift, Glättung, Designs, Speicher, "
    L"Windows-Start und Randeinrasten sind global und werden auf der Registerkarte Anwendung "
    L"eingestellt. Beim ersten Start folgt die Sprache der Windows-Anzeigesprache; sonst wird "
    L"US-Englisch verwendet. Widget-Sprache, Glättung und Designs gelten nur für dieses Widget. Eine "
    L"angewandte Sprachänderung aktualisiert auch den offenen Dialog.\r\n\r\nDas Widget-Menü enthält die "
    L"zutreffenden Optionen für Sichtbarkeit, Vordergrund, Sekunden, Größe und Datumskopie sowie Im "
    L"Raster anordnen, Einstellungen, Hilfe, Info und Beenden. Das Infobereichsmenü listet "
    L"nummerierte Widgets und bietet Alle anzeigen, Alle ausblenden und Alles stummschalten. Im "
    L"Raster anordnen folgt als getrennte Gruppe. Anzeigen oder Wiederherstellen bringt Widgets nach "
    L"vorn, ohne Immer im Vordergrund zu ändern. Ein erneuter Start aktiviert die laufende Instanz "
    L"und stellt bei Bedarf die zuletzt verborgenen Widgets wieder her. Verfügbare Zifferblattgrößen "
    L"und Sekundenzeiger hängen von der installierten Windows-Version ab; nicht verfügbare Sekunden "
    L"sind deaktiviert, die gespeicherte Wahl bleibt jedoch für eine unterstützte Größe erhalten. "
    L"Wecker und Zeitzeichen lassen sich direkt im Widget-Menü schalten; Wecker zeigt Zeit und bei "
    L"einer Teilwoche die aktiven Tage. Stummschalten im Widget-Menü entspricht Stummgeschaltet unter "
    L"Allgemein. Alles stummschalten im Infobereich stellt beim nächsten Umschalten nur die von ihm "
    L"stummgeschalteten Widgets wieder her. M auf einem Widget schaltet denselben Gesamtzustand um. "
    L"Wird ein Wecker ohne ausgewählten Wochentag aktiviert, öffnet sich die Registerkarte Wecker "
    L"dieses Widgets.",
    L"\r\n\r\nPARAMÈTRES ET MENUS\r\nLangue, police, lissage, thèmes, stockage, démarrage avec Windows et "
    L"accrochage sont globaux et se règlent dans l’onglet Application. Au premier lancement, la "
    L"langue suit celle de l’interface Windows, avec l’anglais américain par défaut ; langue, lissage "
    L"et thèmes du widget ne concernent que lui. Un changement de langue appliqué actualise aussi la "
    L"fenêtre ouverte.\r\n\r\nLe menu d’un widget contient les choix applicables de visibilité, premier "
    L"plan, secondes, taille et copie de date, puis Aligner sur une grille, Paramètres, Aide, À "
    L"propos et Quitter. Le menu de notification liste les widgets numérotés et propose Tout "
    L"afficher, Tout masquer et Couper tous les sons. Aligner sur une grille suit dans un groupe "
    L"séparé. Afficher ou restaurer les widgets les ramène devant sans modifier Toujours visible. Un "
    L"nouveau lancement active l’instance existante et restaure au besoin les derniers widgets "
    L"masqués. Les tailles de cadran et la trotteuse disponibles viennent de la version de Windows "
    L"installée ; Secondes est désactivé si indisponible, mais le choix est conservé pour une taille "
    L"compatible. Alarme et Signal se commutent dans le menu du widget ; Alarme affiche l’heure et, "
    L"pour une semaine partielle, les jours actifs. Couper le son dans le menu du widget correspond à "
    L"Son coupé dans Général. Tout couper rétablit ensuite uniquement les widgets qu’il a coupés. M "
    L"sur un widget effectue la même bascule globale. Activer l’alarme sans jour sélectionné ouvre "
    L"l’onglet Alarme de ce widget.",
    L"\r\n\r\nCONFIGURACIÓN Y MENÚS\r\nIdioma, fuente, suavizado, temas, almacenamiento, inicio con Windows "
    L"y acoplamiento son globales y se configuran en la pestaña Aplicación. En el primer inicio, el "
    L"idioma sigue al de la interfaz de Windows y usa inglés de EE. UU. como alternativa; idioma, "
    L"suavizado y temas del widget solo afectan a este. Un cambio de idioma aplicado también "
    L"actualiza la ventana abierta.\r\n\r\nEl menú del widget contiene las opciones aplicables de "
    L"visibilidad, primer plano, segundos, tamaño y copia de fecha, además de Alinear en cuadrícula, "
    L"Configuración, Ayuda, Acerca de y Salir. El menú del icono muestra widgets numerados y ofrece "
    L"Mostrar todo, Ocultar todo y Silenciar todo. Alinear en cuadrícula aparece después como grupo "
    L"separado. Mostrar o restaurar lleva los widgets al frente sin cambiar Siempre visible. Otra "
    L"ejecución activa la instancia existente y restaura cuando haga falta los últimos widgets "
    L"ocultos. Los tamaños de esfera y la disponibilidad del segundero proceden de la versión de "
    L"Windows instalada; Segundos aparece desactivado cuando no está disponible, pero la elección "
    L"guardada se conserva para un tamaño compatible. Alarma y Señal se conmutan en el menú del "
    L"widget; Alarma muestra la hora y, para una semana parcial, los días activos. Silenciar en el "
    L"menú del widget corresponde a Silenciado en General. Silenciar todo restaura después solo los "
    L"widgets que silenció. M sobre un widget realiza la misma conmutación global. Activar la alarma "
    L"sin ningún día seleccionado abre la pestaña Alarma de ese widget.",
    L"\r\n\r\nIMPOSTAZIONI E MENU\r\nLingua, carattere, antialiasing, temi, archivio, avvio con Windows e "
    L"aggancio sono globali e si configurano nella scheda Applicazione. Al primo avvio la lingua "
    L"segue quella dell’interfaccia di Windows, con inglese USA come ripiego; lingua, antialiasing e "
    L"temi del widget valgono solo per esso. Una modifica della lingua applicata aggiorna anche la "
    L"finestra aperta.\r\n\r\nIl menu del widget contiene le scelte pertinenti per visibilità, primo "
    L"piano, secondi, dimensione e copia della data, oltre a Disponi in griglia, Impostazioni, Guida, "
    L"Informazioni ed Esci. Il menu dell’icona elenca i widget numerati e offre Mostra tutto, "
    L"Nascondi tutto e Disattiva tutto l'audio. Disponi in griglia segue come gruppo separato. "
    L"Mostrare o ripristinare porta i widget davanti senza cambiare Sempre in primo piano. Un nuovo "
    L"avvio attiva l’istanza esistente e, se necessario, ripristina gli ultimi widget nascosti. "
    L"Dimensioni del quadrante e lancetta dei secondi disponibili dipendono dalla versione di Windows "
    L"installata; Secondi è disabilitato se non disponibile, ma la scelta viene conservata per una "
    L"dimensione supportata. Sveglia e Segnale si attivano dal menu del widget; Sveglia mostra l’ora "
    L"e, per una settimana parziale, i giorni attivi. Disattiva audio nel menu del widget corrisponde "
    L"ad Audio disattivato in Generale. Disattiva tutto ripristina poi solo i widget che aveva "
    L"disattivato. M su un widget esegue lo stesso comando globale. Attivare la sveglia senza giorni "
    L"selezionati apre la scheda Sveglia del widget.",
    L"\r\n\r\nUSTAWIENIA I MENU\r\nJęzyk, czcionka, wygładzanie, motywy, magazyn ustawień, uruchamianie z "
    L"Windows i przyciąganie są globalne i ustawia się je na karcie Aplikacja. Przy pierwszym "
    L"uruchomieniu język wynika z języka interfejsu Windows, a nieznany zastępuje angielski (USA); "
    L"język, wygładzanie i motywy widżetu dotyczą tylko jego. Zastosowana zmiana języka aktualizuje "
    L"również otwarte okno.\r\n\r\nMenu widżetu zawiera odpowiednie opcje widoczności, położenia na "
    L"wierzchu, sekund, rozmiaru i kopiowania daty oraz Ułóż w siatce, Ustawienia, Pomoc, O programie "
    L"i Zakończ. Menu ikony wyświetla numerowane widżety oraz Pokaż wszystkie, Ukryj wszystkie i "
    L"Wycisz wszystko. Ułóż w siatce znajduje się dalej w oddzielnej grupie. Pokazanie lub "
    L"przywrócenie przenosi widżety do przodu bez zmiany Zawsze na wierzchu. Ponowne uruchomienie "
    L"aktywuje istniejącą instancję i w razie potrzeby przywraca ostatnio ukryte widżety. Dostępne "
    L"rozmiary tarczy i sekundnik zależą od zainstalowanej wersji Windows; niedostępna opcja Sekundy "
    L"jest wyłączona, lecz zapisany wybór pozostaje dla obsługiwanego rozmiaru. Alarm i Sygnał można "
    L"przełączać w menu widżetu; Alarm pokazuje czas i, dla części tygodnia, aktywne dni. Wycisz w "
    L"menu widżetu odpowiada opcji Wyciszony na karcie Ogólne. Wycisz wszystko przywraca potem tylko "
    L"widżety, które samo wyciszyło. M na widżecie wykonuje to samo przełączenie globalne. Włączenie "
    L"alarmu bez wybranego dnia otwiera kartę Alarm tego widżetu.",
    L"\r\n\r\nNASTAVENIA A PONUKY\r\nJazyk, písmo, vyhladzovanie, motívy, úložisko, spúšťanie s Windows a "
    L"prichytávanie sú globálne a nastavujú sa na karte Aplikácia. Pri prvom spustení sa jazyk volí "
    L"podľa jazyka rozhrania Windows, neznámy jazyk sa nahradí angličtinou (USA); jazyk, "
    L"vyhladzovanie a motívy widgetu platia iba preň. Použitá zmena jazyka aktualizuje aj otvorené "
    L"okno.\r\n\r\nPonuka widgetu obsahuje príslušné voľby viditeľnosti, režimu navrchu, sekúnd, veľkosti "
    L"a kopírovania dátumu a ďalej Zarovnať do mriežky, Nastavenia, Pomoc, O programe a Koniec. "
    L"Ponuka ikony uvádza očíslované widgety a príkazy Zobraziť všetko, Skryť všetko a Stlmiť všetko. "
    L"Samostatne oddelený príkaz Zarovnať do mriežky nasleduje za nimi. Zobrazenie alebo obnovenie "
    L"prenesie widgety dopredu bez zmeny Vždy navrchu. Ďalšie spustenie aktivuje bežiacu inštanciu a "
    L"podľa potreby obnoví naposledy skryté widgety. Dostupné rozmery ciferníka a sekundová ručička "
    L"vychádzajú z možností používanej verzie Windows; nedostupné Sekundy sú deaktivované, ale "
    L"uložená voľba zostane pre podporovanú veľkosť. Budík a Signál možno prepínať v ponuke widgetu; "
    L"Budík ukazuje čas a pri čiastočnom týždni aj aktívne dni. Stlmiť v ponuke widgetu zodpovedá "
    L"voľbe Stlmené na karte Všeobecné. Stlmiť všetko potom obnoví iba widgety, ktoré samo stlmilo. "
    L"Kláves M na widgete vykoná rovnaké globálne prepnutie. Zapnutie budíka bez vybraného dňa otvorí "
    L"kartu Budík daného widgetu.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nApplication language, font, smoothing, themes, storage, Windows startup "
    L"and edge snapping are global and are configured on the Application tab. On first launch, the "
    L"application language follows the Windows user-interface language, with US English as the "
    L"fallback; widget language, smoothing and themes affect that widget only. An applied language "
    L"change also updates the open dialog.\r\n\r\nA widget menu contains the applicable visibility, "
    L"always-on-top, seconds, size and date-copy choices, followed by Arrange in a grid, Settings, "
    L"Help, About and Exit. The notification-icon menu lists numbered widgets and provides Show all, "
    L"Hide all and Mute all. The separately grouped Arrange in a grid command follows. Showing or "
    L"restoring widgets brings them forward without changing Always on top. Starting CalClock again "
    L"activates the running instance and restores the most recently hidden widgets when needed. "
    L"Available face sizes and second-hand support come from the installed Windows version; Seconds "
    L"is disabled when unavailable, but its saved choice is retained for a supported size. Alarm and "
    L"Signal can be toggled directly in a widget menu; Alarm shows its time and, for a partial week, "
    L"its active weekdays. Checked Mute in a widget menu corresponds to Muted on the General tab. "
    L"Mute all in the notification-icon menu mutes every widget and, when toggled again, restores "
    L"only those it muted. Pressing M on any widget performs the same global toggle. Enabling an "
    L"alarm with no weekday selected opens that widget’s Alarm tab.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nApplication language, font, smoothing, themes, storage, Windows startup "
    L"and edge snapping are global and are configured on the Application tab. On first launch, the "
    L"application language follows the Windows user-interface language, with US English as the "
    L"fallback; widget language, smoothing and themes affect that widget only. An applied language "
    L"change also updates the open dialog.\r\n\r\nA widget menu contains the applicable visibility, "
    L"always-on-top, seconds, size and date-copy choices, followed by Arrange in a grid, Settings, "
    L"Help, About and Exit. The notification-icon menu lists numbered widgets and provides Show all, "
    L"Hide all and Mute all. The separately grouped Arrange in a grid command follows. Showing or "
    L"restoring widgets brings them forward without changing Always on top. Starting CalClock again "
    L"activates the running instance and restores the most recently hidden widgets when needed. "
    L"Available face sizes and second-hand support come from the installed Windows version; Seconds "
    L"is disabled when unavailable, but its saved choice is retained for a supported size. Alarm and "
    L"Signal can be toggled directly in a widget menu; Alarm shows its time and, for a partial week, "
    L"its active weekdays. Checked Mute in a widget menu corresponds to Muted on the General tab. "
    L"Mute all in the notification-icon menu mutes every widget and, when toggled again, restores "
    L"only those it muted. Pressing M on any widget performs the same global toggle. Enabling an "
    L"alarm with no weekday selected opens that widget’s Alarm tab.",
    L"\r\n\r\nDEFINIÇÕES E MENUS\r\nO idioma, tipo de letra, suavização, temas, armazenamento, arranque com "
    L"o Windows, ajuste às margens e origem da hora são globais; as opções da aplicação são "
    L"configuradas no separador Aplicação. No primeiro arranque, o idioma segue a interface do "
    L"Windows, com inglês dos EUA como alternativa. O idioma e outras opções de widget aplicam-se "
    L"individualmente. No menu do ícone, Mostrar tudo e Ocultar tudo precedem Silenciar tudo; Dispor "
    L"numa grelha surge num grupo separado. Silenciar no menu do widget corresponde a Silenciado em "
    L"Geral. Silenciar tudo repõe depois apenas os widgets que silenciou. M num widget executa a "
    L"mesma alternância global. Ativar o alarme sem nenhum dia selecionado abre o separador Alarme "
    L"desse widget.",
    L"\r\n\r\nINNSTILLINGER OG MENYER\r\nProgramspråk, skrift, utjevning, temaer, lagring, oppstart med "
    L"Windows, kantfesting og tidskilde er globale; programvalgene angis på fanen Program. Ved første "
    L"start følger språket Windows-grensesnittet, med amerikansk engelsk som reserve. Widgetspråk og "
    L"andre widgetvalg gjelder enkeltvis. I ikonmenyen kommer Vis alle og Skjul alle før Demp alle; "
    L"Ordne i et rutenett står i en egen gruppe etter dem. Demp i widgetmenyen tilsvarer Dempet på "
    L"fanen Generelt. Demp alle gjenoppretter senere bare widgetene den dempet. M på en widget "
    L"utfører samme globale veksling. Aktivering av alarmen uten valgte ukedager åpner widgetens "
    L"Alarm-fane.",
    L"\r\n\r\nINSTÄLLNINGAR OCH MENYER\r\nProgramspråk, teckensnitt, utjämning, teman, lagring, start med "
    L"Windows, kantfästning och tidskälla är globala; programalternativen ställs in på fliken "
    L"Program. Vid första starten följer språket Windows gränssnittsspråk, med amerikansk engelska "
    L"som reserv. Widgetspråk och andra widgetval gäller separat. I ikonmenyn kommer Visa alla och "
    L"Dölj alla före Tysta alla; Ordna i ett rutnät står i en egen grupp efter dem. Tysta i "
    L"widgetmenyn motsvarar Tyst på fliken Allmänt. Tysta alla återställer därefter bara de widgetar "
    L"som kommandot tystade. M på en widget gör samma globala växling. Om alarmet aktiveras utan "
    L"valda veckodagar öppnas widgetens Alarm-flik.",
    L"\r\n\r\nASETUKSET JA VALIKOT\r\nSovelluksen kieli, fontti, pehmennys, teemat, tallennus, Windowsin "
    L"mukana käynnistys, reunakiinnitys ja aikalähde ovat yleisiä; sovellusasetukset määritetään "
    L"Sovellus-välilehdellä. Ensimmäisellä käynnistyksellä kieli seuraa Windowsin "
    L"käyttöliittymäkieltä, varalla on amerikanenglanti. Pienoisohjelman kieli ja muut valinnat ovat "
    L"yksilöllisiä. Kuvakevalikossa Näytä kaikki ja Piilota kaikki ovat ennen Mykistä kaikki "
    L"-komentoa; Järjestä ruudukkoon on niiden jälkeen omana ryhmänään. Pienoisohjelman Mykistä "
    L"vastaa Yleiset-välilehden Mykistetty-valintaa. Mykistä kaikki palauttaa myöhemmin vain itse "
    L"mykistämänsä pienoisohjelmat. M pienoisohjelmassa tekee saman yleisen vaihdon. Herätyksen "
    L"ottaminen käyttöön ilman valittuja viikonpäiviä avaa pienoisohjelman Herätys-välilehden.",
    L"\r\n\r\nINDSTILLINGER OG MENUER\r\nProgramsprog, skrifttype, udjævning, temaer, lager, start med "
    L"Windows, kantfastgørelse og tidskilde er globale; programvalgene indstilles på fanen Program. "
    L"Ved første start følger sproget Windows-grænsefladen, med amerikansk engelsk som reserve. "
    L"Widgetsprog og andre widgetvalg gælder enkeltvis. I ikonmenuen kommer Vis alle og Skjul alle "
    L"før Slå al lyd fra; Arranger i et gitter står i en særskilt gruppe efter dem. Slå lyd fra i "
    L"widgetmenuen svarer til Lyd fra på fanen Generelt. Slå al lyd fra gendanner senere kun de "
    L"widgets, kommandoen selv dæmpede. M på en widget udfører samme globale skift. Aktivering af "
    L"alarmen uden valgte ugedage åbner widgetens Alarm-fane.",
    L"\r\n\r\nSTILLINGAR OG VALMYNDIR\r\nTungumál forrits, letur, jöfnun, þemu, geymsla, ræsing með "
    L"Windows, festing við brúnir og tímagjafi gilda alls staðar; forritsvalkostir eru stilltir á "
    L"Forrit-flipanum. Við fyrstu ræsingu fylgir tungumálið viðmóti Windows, en bandarísk enska er "
    L"varaval. Tungumál og aðrir valkostir græju gilda fyrir hverja græju. Í táknvalmyndinni koma "
    L"Sýna allt og Fela allt á undan Þagga allt; Raða á hnitanet er í sérstökum flokki á eftir þeim. "
    L"Þagga í valmynd græju samsvarar Þaggað á Almennt-flipanum. Þagga allt endurheimtir síðar aðeins "
    L"græjurnar sem skipunin þaggaði. M á græju framkvæmir sömu heildarskiptingu. Ef vekjari er "
    L"virkjaður án valinna vikudaga opnast Vekjari-flipi græjunnar.",
    L"\r\n\r\nAYARLAR VE MENÜLER\r\nUygulama dili, yazı tipi, kenar yumuşatma, temalar, depolama, Windows "
    L"ile başlatma, kenara yaslama ve zaman kaynağı geneldir; uygulama seçenekleri Uygulama "
    L"sekmesinde ayarlanır. İlk açılışta dil Windows arayüz dilinden alınır; desteklenmiyorsa ABD "
    L"İngilizcesi kullanılır. Araç dili ve diğer araç seçenekleri her araç için ayrıdır. Simge "
    L"menüsünde Tümünü göster ve Tümünü gizle, Tümünü sessize al seçeneğinden önce gelir; Izgarada "
    L"düzenle bunların ardından ayrı bir gruptadır. Araç menüsündeki Sessize al, Genel sekmesindeki "
    L"Sessiz ile aynıdır. Tümünü sessize al, daha sonra yalnızca kendisinin sessize aldığı araçların "
    L"sesini geri açar. Bir araçta M tuşu aynı genel geçişi yapar. Hiçbir gün seçili değilken alarmı "
    L"etkinleştirmek aracın Alarm sekmesini açar."
};

const wchar_t* HELP_TIME_SIGNAL_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZVUKOVÉ ČASOVÉ ZNAMENÍ\r\nZnamení odpovídá Greenwich Time Signal (GTS). Na kartě Znamení je "
    L"zatržítko Časové znamení aktivní a přepínače intervalů 1, 5, 10, 15, 20, 30 nebo 60 minut podle "
    L"času zobrazovaného widgetem. Znamení je zpočátku vypnuté a je zvolen hodinový interval. Vypnutí "
    L"a zapnutí příkazem Signál v menu widgetu interval zachovává. Menu zobrazuje čas budíku a "
    L"interval znamení v závorkách. Časová hranice vychází z času daného widgetu včetně UTC, časového "
    L"pásma, offsetu a případné korekce NTP. Pět krátkých tónů zazní v posledních pěti sekundách a "
    L"dlouhý tón přesně na hranici. Pokud na stejný okamžik připadne znamení více widgetů, přehraje "
    L"se jediná společná sekvence. Po ztlumení může právě znějící tón doznít; další tóny se přeskočí "
    L"a po zrušení ztlumení zazní až následující naplánovaný tón. Samostatný Kalendář nepodporuje "
    L"budík, časové znamení ani ztlumení; příslušné volby jsou neaktivní a v jeho nabídce "
    L"nejsou.\r\n\r\nPři intervalu 20 minut znamení zazní v :00, :20 a :40 podle času widgetu.\r\n\r\nNa "
    L"kartě Aplikace lze ve volbě Zvuk časového znamení vybrat Vlastní generátor nebo Systémové "
    L"pípání. Volba platí pro časová znamení všech widgetů včetně znamení budíku. Výchozí je Vlastní "
    L"generátor.\r\n\r\nJezdec Hlasitost časového znamení na kartě Aplikace zobrazuje úroveň vlastního "
    L"generátoru v dB. Pravý doraz je 0 dB, tedy maximální nezkreslená amplituda sinusovky; úplné "
    L"ztišení je −∞ dB. Výchozí hlasitost je −18 dB. Tlačítko Vyzkoušet vedle volby Zvuk časového "
    L"znamení zapne stálou ukázku, Zastavit test ji ukončí. Otestovat lze oba druhy zvuku; test se "
    L"neukládá. Ukázka zní také po dobu držení jezdce myší; po uvolnění skončí, pokud neběží test "
    L"zapnutý tlačítkem. Začne až na následující celé sekundě, krátce každou sekundu a dlouze v :00, "
    L":05, :10 atd. Souběžná ukázka a časová znamení widgetů či budíků zaznějí jako jediný tón. Pro "
    L"systémové pípání je neaktivní pouze jezdec hlasitosti. Při zastavení testu právě rozehraný píp "
    L"dozní; u dlouhého pípu to může trvat až půl sekundy. Offsety widgetů se uplatní i v setinách "
    L"sekundy. Překrývající se tóny widgetů, budíků a testu znějí jako jediný souvislý tón až do "
    L"konce posledního překryvu.",
    L"\r\n\r\nAUDIBLE TIME SIGNAL\r\nThe signal follows the Greenwich Time Signal (GTS) pattern. The Signal "
    L"tab has a Time signal active checkbox and radio buttons for intervals of 1, 5, 10, 15, 20, 30, "
    L"or 60 minutes according to the widget's displayed time. Signals are initially off, with an "
    L"hourly interval selected. Turning Signal off and on in the widget menu retains the interval. "
    L"The menu shows the alarm time and signal interval in parentheses. The boundary follows that "
    L"widget’s time, including UTC, time zone, offset, and any NTP correction. Five short pips sound "
    L"during the final five seconds and a long pip exactly on the boundary. If several widgets signal "
    L"at the same instant, only one shared sequence is played. After muting, a pip already sounding "
    L"may finish; later pips are skipped and only the next scheduled pip sounds after unmuting. A "
    L"standalone Calendar supports neither alarms, time signals nor muting; the corresponding "
    L"controls are disabled and its menu omits them.\r\n\r\nWith a 20-minute interval, signals sound at "
    L":00, :20 and :40 in the widget's displayed time.\r\n\r\nOn the Application tab, Time signal sound "
    L"lets you choose between Built-in generator and System beep. The choice applies to time signals "
    L"from all widgets, including alarm time signals. Built-in generator is the default.\r\n\r\nThe Time "
    L"signal volume slider on the Application tab shows the built-in generator’s level in dB. The "
    L"rightmost position is 0 dB, the maximum undistorted sine-wave amplitude; silence is −∞ dB. The "
    L"default volume is −18 dB. Click Test next to Time signal sound to start a continuous preview, "
    L"or Stop test to end it. Both sound options can be tested; the test is not saved. Holding the "
    L"volume slider also plays a preview until the mouse is released, unless the button test is "
    L"running. Playback starts on the next whole second: short tones every second and a long tone at "
    L":00, :05, :10, and so on. Simultaneous preview, widget, and alarm time signals share a single "
    L"tone. Only the volume slider is disabled for System beep. Stopping the test lets the current "
    L"pip finish; a long pip can take up to half a second to end. Widget offsets also apply in "
    L"hundredths of a second. Overlapping widget, alarm, and test tones play as one continuous tone "
    L"until the last overlap ends.",
    L"\r\n\r\nAKUSTISCHES ZEITZEICHEN\r\nDas Signal entspricht dem Greenwich Time Signal (GTS). Auf der "
    L"Registerkarte Zeitzeichen gibt es das Kontrollkästchen Zeitzeichen aktiv und Optionsfelder für "
    L"Intervalle von 1, 5, 10, 15, 20, 30 oder 60 Minuten gemäß der angezeigten Widget-Zeit. Anfangs "
    L"ist das Signal ausgeschaltet und das Stundenintervall ausgewählt. Aus- und Einschalten über "
    L"Zeitzeichen im Widget-Menü behält das Intervall bei. Das Menü zeigt die Weckzeit und das "
    L"Signalintervall in Klammern. Die Grenze folgt der Zeit dieses Widgets einschließlich UTC, "
    L"Zeitzone, Offset und einer möglichen NTP-Korrektur. In den letzten fünf Sekunden erklingen fünf "
    L"kurze Töne und genau an der Grenze ein langer Ton. Fallen Signale mehrerer Widgets auf "
    L"denselben Zeitpunkt, wird nur eine gemeinsame Folge wiedergegeben. Beim Stummschalten darf ein "
    L"bereits klingender Ton enden; weitere Töne werden bis zum nächsten geplanten Ton nach dem "
    L"Aufheben übersprungen. Ein einzelner Kalender unterstützt weder Wecker noch Zeitzeichen oder "
    L"Stummschaltung; die zugehörigen Optionen sind deaktiviert und fehlen in seinem Menü.\r\n\r\nBeim "
    L"20-Minuten-Intervall ertönt das Zeitzeichen um :00, :20 und :40 gemäß der Widget-Zeit.\r\n\r\nAuf "
    L"der Registerkarte Anwendung können Sie unter Klang des Zeitzeichens zwischen Interner Generator "
    L"und Systemsignalton wählen. Die Auswahl gilt für die Zeitzeichen aller Widgets einschließlich "
    L"der Zeitzeichen des Weckers. Standardmäßig ist Interner Generator ausgewählt.\r\n\r\nDer "
    L"Lautstärkeregler für das Zeitsignal auf der Registerkarte Anwendung zeigt den Pegel des "
    L"eingebauten Generators in dB. Der rechte Anschlag entspricht 0 dB, der maximalen unverzerrten "
    L"Sinusamplitude; Stille entspricht −∞ dB. Die Standardlautstärke beträgt −18 dB. Mit Testen "
    L"neben Klang des Zeitsignals starten Sie eine fortlaufende Vorschau, mit Test stoppen beenden "
    L"Sie sie. Beide Klangarten lassen sich testen; der Test wird nicht gespeichert. Auch das "
    L"Festhalten des Lautstärkereglers startet eine Vorschau bis zum Loslassen, sofern der Tastentest "
    L"nicht läuft. Die Wiedergabe beginnt zur nächsten vollen Sekunde: kurze Töne jede Sekunde und "
    L"ein langer bei :00, :05, :10 usw. Gleichzeitige Signale von Vorschau, Widgets und Alarmen "
    L"werden zu einem Ton zusammengefasst. Beim Systemton ist nur der Lautstärkeregler deaktiviert. "
    L"Beim Stoppen des Tests klingt der aktuelle Ton aus; ein langer Ton kann noch bis zu einer "
    L"halben Sekunde dauern. Widget-Versätze gelten auch in Hundertstelsekunden. Überlappende Töne "
    L"von Widgets, Weckern und Tests erklingen als ein durchgehender Ton bis zum Ende der letzten "
    L"Überlappung.",
    L"\r\n\r\nSIGNAL HORAIRE SONORE\r\nLe signal reprend le Greenwich Time Signal (GTS). L’onglet Signal "
    L"propose la case Signal horaire actif et des boutons radio pour les intervalles de 1, 5, 10, 15, "
    L"20, 30 ou 60 minutes selon l’heure affichée par le widget. Le signal est initialement "
    L"désactivé, avec un intervalle d’une heure sélectionné. Désactiver puis réactiver Signal dans le "
    L"menu du widget conserve l’intervalle. Le menu affiche l’heure de l’alarme et l’intervalle du "
    L"signal entre parenthèses. La limite suit l’heure du widget, y compris UTC, le fuseau horaire, "
    L"le décalage et toute correction NTP. Cinq bips courts retentissent pendant les cinq dernières "
    L"secondes et un bip long exactement à la limite. Si plusieurs widgets signalent au même instant, "
    L"une seule séquence commune est jouée. Lors de la coupure, un bip déjà commencé peut finir ; les "
    L"suivants sont ignorés et seul le prochain bip planifié retentit après le rétablissement. Un "
    L"Calendrier autonome ne propose ni alarme, ni signal horaire, ni coupure du son ; les options "
    L"correspondantes sont désactivées et absentes de son menu.\r\n\r\nAvec un intervalle de 20 minutes, "
    L"le signal retentit à :00, :20 et :40 selon l’heure du widget.\r\n\r\nDans l’onglet Application, Son "
    L"du signal horaire permet de choisir entre Générateur intégré et Bip système. Ce choix "
    L"s’applique aux signaux horaires de tous les widgets, y compris ceux des alarmes. Le Générateur "
    L"intégré est sélectionné par défaut.\r\n\r\nLe curseur du volume du signal horaire dans l’onglet "
    L"Application affiche le niveau du générateur intégré en dB. La position maximale est 0 dB, soit "
    L"l’amplitude sinusoïdale maximale sans distorsion ; le silence est −∞ dB. Le volume par défaut "
    L"est de −18 dB. Cliquez sur Tester à côté du son du signal horaire pour démarrer un aperçu "
    L"continu, puis sur Arrêter le test pour le terminer. Les deux sons peuvent être testés ; le test "
    L"n’est pas enregistré. Maintenir le curseur de volume lance aussi un aperçu jusqu’au "
    L"relâchement, sauf si le test par bouton est actif. La lecture commence à la seconde entière "
    L"suivante : sons courts chaque seconde et son long à :00, :05, :10, etc. Les signaux simultanés "
    L"de l’aperçu, des widgets et des alarmes produisent un seul son. Seul le curseur de volume est "
    L"désactivé pour le bip système. À l’arrêt du test, le son en cours se termine ; un son long peut "
    L"encore durer jusqu’à une demi-seconde. Le curseur suit une échelle en décibels ; −18 dB se "
    L"trouve au milieu.\r\n\r\nLe choix du son est disponible uniquement si le système prend en charge "
    L"les deux options. Les décalages des widgets s’appliquent aussi aux centièmes de seconde. Les "
    L"sons des widgets, alarmes et tests qui se chevauchent forment un seul son continu jusqu’à la "
    L"fin du dernier chevauchement.",
    L"\r\n\r\nSEÑAL HORARIA SONORA\r\nLa señal sigue el patrón del Greenwich Time Signal (GTS). La pestaña "
    L"Señal incluye la casilla Señal horaria activa y botones de opción para intervalos de 1, 5, 10, "
    L"15, 20, 30 o 60 minutos según la hora mostrada por el widget. La señal está inicialmente "
    L"desactivada y el intervalo seleccionado es de una hora. Desactivar y activar Señal en el menú "
    L"del widget conserva el intervalo. El menú muestra la hora de la alarma y el intervalo de la "
    L"señal entre paréntesis. El límite sigue la hora del widget, incluidos UTC, zona horaria, offset "
    L"y cualquier corrección NTP. Cinco pitidos cortos suenan durante los últimos cinco segundos y "
    L"uno largo exactamente en el límite. Si varios widgets coinciden, se reproduce una única "
    L"secuencia compartida. Al silenciar, puede terminar el pitido que ya suena; los siguientes se "
    L"omiten y, al reactivar el sonido, suena solo el próximo pitido programado. Un Calendario "
    L"independiente no admite alarma, señal horaria ni silencio; las opciones correspondientes están "
    L"desactivadas y no aparecen en su menú.\r\n\r\nCon un intervalo de 20 minutos, la señal suena a :00, "
    L":20 y :40 según la hora del widget.\r\n\r\nEn la pestaña Aplicación, Sonido de la señal horaria "
    L"permite elegir entre Generador integrado y Pitido del sistema. La elección se aplica a las "
    L"señales horarias de todos los widgets, incluidas las de las alarmas. Generador integrado es la "
    L"opción predeterminada.\r\n\r\nEl control de volumen de la señal horaria en la pestaña Aplicación "
    L"muestra el nivel del generador integrado en dB. El extremo derecho es 0 dB, la amplitud "
    L"sinusoidal máxima sin distorsión; el silencio es −∞ dB. El volumen predeterminado es −18 dB. "
    L"Pulse Probar junto al sonido de la señal horaria para iniciar una prueba continua y Detener "
    L"prueba para finalizarla. Se pueden probar ambos sonidos; la prueba no se guarda. Mantener "
    L"pulsado el control de volumen también reproduce una prueba hasta soltarlo, salvo que siga "
    L"activa la prueba del botón. Empieza en el siguiente segundo entero: tonos cortos cada segundo y "
    L"uno largo en :00, :05, :10, etc. Las señales simultáneas de la prueba, los widgets y las "
    L"alarmas se combinan en un solo tono. Solo el control de volumen se desactiva para el pitido del "
    L"sistema. Al detener la prueba, el tono actual termina; un tono largo puede tardar hasta medio "
    L"segundo. Los desfases de los widgets también se aplican en centésimas de segundo. Los tonos "
    L"superpuestos de widgets, alarmas y pruebas suenan como un único tono continuo hasta que termina "
    L"la última superposición.",
    L"\r\n\r\nSEGNALE ORARIO ACUSTICO\r\nIl segnale segue lo schema del Greenwich Time Signal (GTS). La "
    L"scheda Segnale contiene la casella Segnale orario attivo e pulsanti di opzione per intervalli "
    L"di 1, 5, 10, 15, 20, 30 o 60 minuti secondo l’ora visualizzata dal widget. Inizialmente il "
    L"segnale è disattivato e l’intervallo selezionato è di un’ora. Disattivare e riattivare Segnale "
    L"nel menu del widget mantiene l’intervallo. Il menu mostra tra parentesi l’ora della sveglia e "
    L"l’intervallo del segnale. Il limite segue l’ora del widget, inclusi UTC, fuso orario, offset ed "
    L"eventuale correzione NTP. Cinque segnali brevi suonano negli ultimi cinque secondi e uno lungo "
    L"esattamente al limite. Se più widget coincidono, viene riprodotta una sola sequenza comune. "
    L"Disattivando l’audio, un segnale già iniziato può terminare; i successivi vengono saltati e, "
    L"alla riattivazione, suona solo il prossimo segnale programmato. Un Calendario autonomo non "
    L"supporta sveglia, segnale orario o disattivazione audio; le relative opzioni sono disabilitate "
    L"e assenti dal menu.\r\n\r\nCon un intervallo di 20 minuti, il segnale suona a :00, :20 e :40 "
    L"secondo l’ora del widget.\r\n\r\nNella scheda Applicazione, Suono del segnale orario consente di "
    L"scegliere tra Generatore integrato e Segnale acustico di sistema. La scelta si applica ai "
    L"segnali orari di tutti i widget, inclusi quelli delle sveglie. Generatore integrato è l’opzione "
    L"predefinita.\r\n\r\nIl cursore del volume del segnale orario nella scheda Applicazione mostra il "
    L"livello del generatore integrato in dB. L’estremità destra è 0 dB, l’ampiezza sinusoidale "
    L"massima senza distorsione; il silenzio è −∞ dB. Il volume predefinito è −18 dB. Premere Prova "
    L"accanto al suono del segnale orario per avviare una prova continua e Ferma prova per "
    L"terminarla. Entrambi i suoni possono essere provati; la prova non viene salvata. Tenere premuto "
    L"il cursore del volume avvia una prova fino al rilascio, a meno che sia attiva la prova con il "
    L"pulsante. Inizia al secondo intero successivo: toni brevi ogni secondo e uno lungo a :00, :05, "
    L":10 ecc. I segnali simultanei di prova, widget e sveglie vengono uniti in un solo tono. Solo il "
    L"cursore del volume è disattivato per il segnale acustico di sistema. Quando si interrompe la "
    L"prova, il tono in corso termina; un tono lungo può richiedere fino a mezzo secondo. Gli offset "
    L"dei widget si applicano anche ai centesimi di secondo. I toni sovrapposti di widget, sveglie e "
    L"test formano un unico tono continuo fino alla fine dell’ultima sovrapposizione.",
    L"\r\n\r\nDŹWIĘKOWY SYGNAŁ CZASU\r\nSygnał odpowiada Greenwich Time Signal (GTS). Karta Sygnał zawiera "
    L"pole Sygnał czasu aktywny oraz przyciski opcji dla odstępów 1, 5, 10, 15, 20, 30 lub 60 minut "
    L"według czasu wyświetlanego przez widżet. Początkowo sygnał jest wyłączony i wybrany jest odstęp "
    L"jednej godziny. Wyłączenie i włączenie opcji Sygnał w menu widżetu zachowuje odstęp. Menu "
    L"pokazuje godzinę alarmu i odstęp sygnału w nawiasach. Granica wynika z czasu widżetu, w tym "
    L"UTC, strefy czasowej, offsetu i korekty NTP. Pięć krótkich sygnałów rozlega się w ostatnich "
    L"pięciu sekundach, a długi dokładnie na granicy. Gdy sygnały wielu widżetów przypadają "
    L"jednocześnie, odtwarzana jest jedna wspólna sekwencja. Po wyciszeniu rozpoczęty sygnał może "
    L"wybrzmieć; następne są pomijane, a po włączeniu dźwięku zabrzmi dopiero kolejny zaplanowany "
    L"sygnał. Samodzielny Kalendarz nie obsługuje alarmu, sygnału czasu ani wyciszenia; odpowiednie "
    L"opcje są wyłączone i nie występują w jego menu.\r\n\r\nPrzy odstępie 20 minut sygnał rozlega się o "
    L":00, :20 i :40 według czasu widżetu.\r\n\r\nNa karcie Aplikacja opcja Dźwięk sygnału czasu pozwala "
    L"wybrać Wbudowany generator lub Sygnał systemowy. Wybór dotyczy sygnałów czasu wszystkich "
    L"widżetów, w tym sygnałów alarmu. Domyślnie wybrany jest Wbudowany generator.\r\n\r\nSuwak głośności "
    L"sygnału czasu na karcie Aplikacja pokazuje poziom wbudowanego generatora w dB. Prawe skrajne "
    L"położenie to 0 dB, czyli maksymalna niezniekształcona amplituda sinusoidy; cisza to −∞ dB. "
    L"Domyślna głośność wynosi −18 dB. Kliknij Testuj obok dźwięku sygnału czasu, aby rozpocząć "
    L"ciągły odsłuch, lub Zatrzymaj test, aby go zakończyć. Można testować oba dźwięki; test nie jest "
    L"zapisywany. Przytrzymanie suwaka głośności również uruchamia odsłuch do puszczenia myszy, chyba "
    L"że trwa test włączony przyciskiem. Odsłuch zaczyna się od następnej pełnej sekundy: krótkie "
    L"dźwięki co sekundę, długi o :00, :05, :10 itd. Jednoczesne sygnały odsłuchu, widżetów i alarmów "
    L"są łączone w jeden dźwięk. Dla sygnału systemowego nieaktywny jest tylko suwak głośności. Po "
    L"zatrzymaniu testu bieżący dźwięk wybrzmi do końca; długi dźwięk może trwać jeszcze do pół "
    L"sekundy. Suwak ma skalę decybelową; −18 dB znajduje się w połowie zakresu.\r\n\r\nWybór dźwięku "
    L"jest dostępny tylko wtedy, gdy system obsługuje obie opcje. Przesunięcia widżetów uwzględniają "
    L"także setne części sekundy. Nakładające się tony widżetów, alarmów i testów tworzą jeden ciągły "
    L"ton do końca ostatniego nakładania.",
    L"\r\n\r\nZVUKOVÉ ČASOVÉ ZNAMENIE\r\nZnamenie zodpovedá Greenwich Time Signal (GTS). Na karte Znamenie "
    L"je začiarkavacie políčko Časové znamenie aktívne a prepínače intervalov 1, 5, 10, 15, 20, 30 "
    L"alebo 60 minút podľa času zobrazovaného widgetom. Znamenie je spočiatku vypnuté a je zvolený "
    L"hodinový interval. Vypnutie a zapnutie príkazom Signál v menu widgetu zachováva interval. Menu "
    L"zobrazuje čas budíka a interval znamenia v zátvorkách. Časová hranica vychádza z času daného "
    L"widgetu vrátane UTC, časového pásma, offsetu a prípadnej korekcie NTP. Päť krátkych tónov "
    L"zaznie v posledných piatich sekundách a dlhý tón presne na hranici. Ak na rovnaký okamih "
    L"pripadne znamenie viacerých widgetov, prehrá sa jediná spoločná sekvencia. Po stlmení môže "
    L"práve znejúci tón doznieť; ďalšie sa preskočia a po zrušení stlmenia zaznie až nasledujúci "
    L"naplánovaný tón. Samostatný Kalendár nepodporuje budík, časové znamenie ani stlmenie; príslušné "
    L"voľby sú neaktívne a v jeho ponuke nie sú.\r\n\r\nPri intervale 20 minút znamenie zaznie v :00, :20 "
    L"a :40 podľa času widgetu.\r\n\r\nNa karte Aplikácia možno vo voľbe Zvuk časového znamenia vybrať "
    L"Vlastný generátor alebo Systémové pípanie. Voľba platí pre časové znamenia všetkých widgetov "
    L"vrátane znamení budíka. Predvolený je Vlastný generátor.\r\n\r\nJazdec Hlasitosť časového znamenia "
    L"na karte Aplikácia zobrazuje úroveň vlastného generátora v dB. Pravý doraz je 0 dB, teda "
    L"maximálna neskreslená amplitúda sínusovky; úplné stíšenie je −∞ dB. Predvolená hlasitosť je −18 "
    L"dB. Tlačidlo Vyskúšať vedľa voľby Zvuk časového znamenia zapne stálu ukážku, Zastaviť test ju "
    L"ukončí. Otestovať možno oba druhy zvuku; test sa neukladá. Ukážka znie aj počas držania jazdca "
    L"myšou; po uvoľnení skončí, ak nebeží test zapnutý tlačidlom. Začne až na nasledujúcej celej "
    L"sekunde, krátko každú sekundu a dlho v :00, :05, :10 atď. Súbežná ukážka a časové znamenia "
    L"widgetov či budíkov zaznejú ako jediný tón. Pre systémové pípanie je neaktívny iba jazdec "
    L"hlasitosti. Pri zastavení testu práve rozohraný tón doznie; pri dlhom tóne to môže trvať až pol "
    L"sekundy. Offsety widgetov sa uplatnia aj v stotinách sekundy. Prekrývajúce sa tóny widgetov, "
    L"budíkov a testu znejú ako jediný súvislý tón až do konca posledného prekrytia.",
    L"\r\n\r\nAUDIBLE TIME SIGNAL\r\nThe signal follows the Greenwich Time Signal (GTS) pattern. The Signal "
    L"tab has a Time signal active checkbox and radio buttons for intervals of 1, 5, 10, 15, 20, 30, "
    L"or 60 minutes according to the widget's displayed time. Signals are initially off, with an "
    L"hourly interval selected. Turning Signal off and on in the widget menu retains the interval. "
    L"The menu shows the alarm time and signal interval in parentheses. The boundary follows that "
    L"widget’s time, including UTC, time zone, offset, and any NTP correction. Five short pips sound "
    L"during the final five seconds and a long pip exactly on the boundary. If several widgets signal "
    L"at the same instant, only one shared sequence is played. After muting, a pip already sounding "
    L"may finish; later pips are skipped and only the next scheduled pip sounds after unmuting. A "
    L"standalone Calendar supports neither alarms, time signals nor muting; the corresponding "
    L"controls are disabled and its menu omits them.\r\n\r\nWith a 20-minute interval, signals sound at "
    L":00, :20 and :40 in the widget's displayed time.\r\n\r\nOn the Application tab, Time signal sound "
    L"lets you choose between Built-in generator and System beep. The choice applies to time signals "
    L"from all widgets, including alarm time signals. Built-in generator is selected by "
    L"default.\r\n\r\nThe Time signal volume slider on the Application tab shows the built-in generator’s "
    L"level in dB. The rightmost position is 0 dB, the maximum undistorted sine-wave amplitude; "
    L"silence is −∞ dB. The default volume is −18 dB. Click Test next to Time signal sound to start a "
    L"continuous preview, or Stop test to end it. Both sound options can be tested; the test is not "
    L"saved. Holding the volume slider also plays a preview until the mouse is released, unless the "
    L"button test is running. Playback starts on the next whole second: short tones every second and "
    L"a long tone at :00, :05, :10, and so on. Simultaneous preview, widget, and alarm time signals "
    L"share a single tone. Only the volume slider is disabled for System beep. Stopping the test lets "
    L"the current pip finish; a long pip can take up to half a second to end. Widget offsets also "
    L"apply in hundredths of a second. Overlapping widget, alarm, and test tones play as one "
    L"continuous tone until the last overlap ends.",
    L"\r\n\r\nAUDIBLE TIME SIGNAL\r\nThe signal follows the Greenwich Time Signal (GTS) pattern. The Signal "
    L"tab has a Time signal active checkbox and radio buttons for intervals of 1, 5, 10, 15, 20, 30, "
    L"or 60 minutes according to the widget's displayed time. Signals are initially off, with an "
    L"hourly interval selected. Turning Signal off and on in the widget menu retains the interval. "
    L"The menu shows the alarm time and signal interval in parentheses. The boundary follows that "
    L"widget’s time, including UTC, time zone, offset, and any NTP correction. Five short pips sound "
    L"during the final five seconds and a long pip exactly on the boundary. If several widgets signal "
    L"at the same instant, only one shared sequence is played. After muting, a pip already sounding "
    L"may finish; later pips are skipped and only the next scheduled pip sounds after unmuting. A "
    L"standalone Calendar supports neither alarms, time signals nor muting; the corresponding "
    L"controls are disabled and its menu omits them.\r\n\r\nWith a 20-minute interval, signals sound at "
    L":00, :20 and :40 in the widget's displayed time.\r\n\r\nOn the Application tab, Time signal sound "
    L"lets you choose between Built-in generator and System beep. The choice applies to time signals "
    L"from all widgets, including alarm time signals. Built-in generator is selected by "
    L"default.\r\n\r\nThe Time signal volume slider on the Application tab shows the built-in generator’s "
    L"level in dB. The rightmost position is 0 dB, the maximum undistorted sine-wave amplitude; "
    L"silence is −∞ dB. The default volume is −18 dB. Click Test next to Time signal sound to start a "
    L"continuous preview, or Stop test to end it. Both sound options can be tested; the test is not "
    L"saved. Holding the volume slider also plays a preview until the mouse is released, unless the "
    L"button test is running. Playback starts on the next whole second: short tones every second and "
    L"a long tone at :00, :05, :10, and so on. Simultaneous preview, widget, and alarm time signals "
    L"share a single tone. Only the volume slider is disabled for System beep. Stopping the test lets "
    L"the current pip finish; a long pip can take up to half a second to end. Widget offsets also "
    L"apply in hundredths of a second. Overlapping widget, alarm, and test tones play as one "
    L"continuous tone until the last overlap ends.",
    L"\r\n\r\nSINAL HORÁRIO SONORO\r\nO sinal segue o padrão do Greenwich Time Signal (GTS). O separador "
    L"Sinal contém a caixa Sinal horário ativo e botões de opção para intervalos de 1, 5, 10, 15, 20, "
    L"30 ou 60 minutos segundo a hora apresentada pelo widget. Inicialmente, o sinal está desativado "
    L"e está selecionado o intervalo de uma hora. Desativar e ativar Sinal no menu do widget mantém o "
    L"intervalo. O menu mostra a hora do alarme e o intervalo do sinal entre parênteses. O limite "
    L"segue a hora do widget, incluindo UTC, fuso, desvio e correção NTP. Soam cinco sinais curtos e "
    L"um longo; sinais simultâneos de vários widgets são unidos. Ao silenciar, o sinal já iniciado "
    L"pode terminar; os seguintes são ignorados e só o próximo sinal agendado soa depois de repor o "
    L"áudio. Um Calendário autónomo não suporta alarme, sinal horário nem silenciamento; as opções "
    L"correspondentes ficam desativadas e não aparecem no menu.\r\n\r\nCom um intervalo de 20 minutos, o "
    L"sinal soa aos :00, :20 e :40 segundo a hora do widget.\r\n\r\nNo separador Aplicação, Som do sinal "
    L"horário permite escolher entre Gerador integrado e Sinal sonoro do sistema. A escolha aplica-se "
    L"aos sinais horários de todos os widgets, incluindo os dos alarmes. Gerador integrado é a opção "
    L"predefinida.\r\n\r\nO controlo de volume do sinal horário no separador Aplicação mostra o nível do "
    L"gerador integrado em dB. O extremo direito é 0 dB, a amplitude sinusoidal máxima sem distorção; "
    L"o silêncio é −∞ dB. O volume predefinido é −18 dB. Clique em Testar junto ao som do sinal "
    L"horário para iniciar uma pré-visualização contínua e em Parar teste para a terminar. Ambos os "
    L"sons podem ser testados; o teste não é guardado. Manter o controlo de volume premido também "
    L"reproduz uma pré-visualização até o soltar, exceto se o teste pelo botão estiver ativo. Começa "
    L"no segundo inteiro seguinte: sons curtos a cada segundo e um longo aos :00, :05, :10, etc. Os "
    L"sinais simultâneos da pré-visualização, dos widgets e dos alarmes produzem um único som. Só o "
    L"controlo de volume fica desativado para o sinal sonoro do sistema. O gerador integrado inicia e "
    L"termina os sons numa passagem por zero, mesmo ao parar um teste. Ao parar o teste, o som atual "
    L"termina; um som longo pode demorar até meio segundo. Os desvios dos widgets também se aplicam "
    L"em centésimos de segundo. Os sons sobrepostos de widgets, alarmes e testes formam um único som "
    L"contínuo até ao fim da última sobreposição.",
    L"\r\n\r\nHØRBART TIDSSIGNAL\r\nSignalet følger mønsteret til Greenwich Time Signal (GTS). Signal-fanen "
    L"har avkrysningsboksen Tidssignal aktivt og alternativknapper for intervaller på 1, 5, 10, 15, "
    L"20, 30 eller 60 minutter etter widgetens viste tid. Signalet er først slått av, med et "
    L"intervall på én time valgt. Å slå Signal av og på i widgetmenyen beholder intervallet. Menyen "
    L"viser alarmtid og signalintervall i parentes. Grensen følger widgettiden, inkludert UTC, "
    L"tidssone, forskyvning og NTP-korreksjon. Fem korte og ett langt pip høres; samtidige signaler "
    L"fra flere widgeter slås sammen. Ved demping kan et pip som allerede har startet fullføres; "
    L"senere pip hoppes over, og bare neste planlagte pip høres etter oppheving. En frittstående "
    L"Kalender støtter ikke alarm, tidssignal eller demping; de tilhørende valgene er deaktivert og "
    L"finnes ikke i menyen.\r\n\r\nMed et intervall på 20 minutter lyder signalet ved :00, :20 og :40 "
    L"etter widgettiden.\r\n\r\nPå fanen Program kan du under Lyd for tidssignal velge mellom Innebygd "
    L"generator og Systempip. Valget gjelder tidssignaler fra alle widgeter, inkludert tidssignaler "
    L"for alarmer. Innebygd generator er standardvalget.\r\n\r\nVolumglidebryteren for tidssignalet på "
    L"fanen Program viser nivået til den innebygde generatoren i dB. Høyre endepunkt er 0 dB, "
    L"maksimal uforvrengt sinusamplitude; stillhet er −∞ dB. Standardvolumet er −18 dB. Klikk Test "
    L"ved lyden for tidssignalet for å starte kontinuerlig forhåndslytting, og Stopp test for å "
    L"avslutte. Begge lydene kan testes; testen lagres ikke. Å holde volumglidebryteren starter også "
    L"forhåndslytting til musen slippes, med mindre knapptesten kjører. Avspillingen begynner på "
    L"neste hele sekund: korte toner hvert sekund og en lang ved :00, :05, :10 osv. Samtidige "
    L"signaler fra forhåndslytting, widgeter og alarmer slås sammen til én tone. Bare "
    L"volumglidebryteren er deaktivert for Systempip. Når testen stoppes, spilles den pågående tonen "
    L"ferdig; en lang tone kan vare i opptil et halvt sekund. Glidebryteren følger en desibelskala; "
    L"−18 dB ligger i midten.\r\n\r\nLydvalget er bare tilgjengelig når systemet støtter begge "
    L"alternativene. Widgetforskyvninger gjelder også i hundredeler av et sekund. Overlappende toner "
    L"fra widgeter, alarmer og tester spilles som én sammenhengende tone til den siste overlappingen "
    L"er slutt.",
    L"\r\n\r\nHÖRBAR TIDSSIGNAL\r\nSignalen följer mönstret för Greenwich Time Signal (GTS). Signal-fliken "
    L"har kryssrutan Tidssignal aktiv och alternativknappar för intervall på 1, 5, 10, 15, 20, 30 "
    L"eller 60 minuter enligt widgetens visade tid. Signalen är från början avstängd med en timmes "
    L"intervall valt. Att stänga av och slå på Signal i widgetens meny behåller intervallet. Menyn "
    L"visar alarmtiden och signalintervallet inom parentes. Gränsen följer widgetens tid, inklusive "
    L"UTC, tidszon, förskjutning och NTP-korrigering. Fem korta och ett långt pip hörs; samtidiga "
    L"signaler från flera widgetar slås samman. Vid tystning får ett påbörjat pip avslutas; följande "
    L"hoppas över och först nästa schemalagda pip hörs efter återaktivering. En fristående Kalender "
    L"stöder inte alarm, tidssignal eller tystning; motsvarande val är inaktiva och saknas i "
    L"menyn.\r\n\r\nMed ett intervall på 20 minuter hörs signalen vid :00, :20 och :40 enligt widgetens "
    L"tid.\r\n\r\nPå fliken Program kan du under Ljud för tidssignal välja mellan Inbyggd generator och "
    L"Systempip. Valet gäller tidssignaler från alla widgetar, inklusive tidssignaler för alarm. "
    L"Inbyggd generator är standardvalet.\r\n\r\nVolymreglaget för tidssignalen på fliken Program visar "
    L"den inbyggda generatorns nivå i dB. Höger ändläge är 0 dB, maximal sinusamplitud utan "
    L"distorsion; tystnad är −∞ dB. Standardvolymen är −18 dB. Klicka på Testa vid tidssignalens ljud "
    L"för att starta kontinuerlig förhandslyssning och på Stoppa test för att avsluta. Båda ljuden "
    L"kan testas; testet sparas inte. Att hålla volymreglaget startar också förhandslyssning tills "
    L"musen släpps, om inte knapptestet körs. Uppspelningen börjar vid nästa hela sekund: korta toner "
    L"varje sekund och en lång vid :00, :05, :10 osv. Samtidiga signaler från förhandslyssning, "
    L"widgetar och alarm slås samman till en ton. Bara volymreglaget är inaktivt för Systempip. När "
    L"testet stoppas spelas den pågående tonen klart; en lång ton kan ta upp till en halv sekund. "
    L"Widgetförskjutningar gäller även i hundradels sekunder. Överlappande toner från widgetar, alarm "
    L"och tester spelas som en sammanhängande ton tills den sista överlappningen är slut.",
    L"\r\n\r\nÄÄNIMERKKI\r\nAikamerkki noudattaa Greenwich Time Signal (GTS) -mallia. "
    L"Aikamerkki-välilehdellä on Äänimerkki käytössä -valintaruutu ja valintanapit 1, 5, 10, 15, 20, "
    L"30 tai 60 minuutin väleille pienoisohjelman näyttämän ajan mukaan. Äänimerkki on aluksi pois "
    L"käytöstä, ja valittuna on tunnin väli. Aikamerkin poistaminen käytöstä ja ottaminen uudelleen "
    L"käyttöön pienoisohjelman valikosta säilyttää aikavälin. Valikko näyttää herätysajan ja "
    L"aikamerkin välin sulkeissa. Raja seuraa pienoisohjelman aikaa, UTC:tä, aikavyöhykettä, "
    L"poikkeamaa ja NTP-korjausta myöten. Viisi lyhyttä ja yksi pitkä merkki kuuluu; samanaikaiset "
    L"merkit yhdistetään. Mykistettäessä jo alkanut ääni saa päättyä; seuraavat ohitetaan ja "
    L"mykistyksen jälkeen kuuluu vasta seuraava ajastettu ääni. Erillinen Kalenteri ei tue herätystä, "
    L"aikamerkkiä eikä mykistystä; vastaavat valinnat ovat poissa käytöstä eivätkä näy "
    L"valikossa.\r\n\r\nKun väli on 20 minuuttia, aikamerkki kuuluu kohdissa :00, :20 ja :40 "
    L"pienoisohjelman ajan mukaan.\r\n\r\nSovellus-välilehden aikamerkin ääniasetuksessa voit valita "
    L"vaihtoehdon Sisäinen generaattori tai Järjestelmän äänimerkki. Valinta koskee kaikkien "
    L"pienoisohjelmien aikamerkkejä, myös herätysten aikamerkkejä. Sisäinen generaattori on "
    L"oletusvalinta.\r\n\r\nSovellus-välilehden aikamerkin äänenvoimakkuuden liukusäädin näyttää sisäisen "
    L"generaattorin tason desibeleinä. Oikea ääriasento on 0 dB eli suurin särötön siniaallon "
    L"amplitudi; hiljaisuus on −∞ dB. Oletusäänenvoimakkuus on −18 dB. Napsauta aikamerkin "
    L"ääniasetuksen vieressä Testaa aloittaaksesi jatkuvan esikuuntelun ja Pysäytä testi "
    L"lopettaaksesi sen. Molempia ääniä voi testata; testiä ei tallenneta. Liukusäätimen pitäminen "
    L"painettuna käynnistää myös esikuuntelun hiiren vapauttamiseen asti, ellei painikkeella "
    L"käynnistetty testi ole käynnissä. Toisto alkaa seuraavalla tasasekunnilla: lyhyt ääni joka "
    L"sekunti ja pitkä kohdissa :00, :05, :10 jne. Samanaikaiset esikuuntelun, pienoisohjelmien ja "
    L"herätysten aikamerkit yhdistetään yhdeksi ääneksi. Vain äänenvoimakkuuden liukusäädin on pois "
    L"käytöstä järjestelmän äänimerkin kanssa. Kun testi pysäytetään, nykyinen ääni soi loppuun; "
    L"pitkä ääni voi kestää vielä puoli sekuntia. Pienoisohjelmien aikapoikkeamat huomioidaan myös "
    L"sekunnin sadasosina. Pienoisohjelmien, herätysten ja testien päällekkäiset äänet soivat yhtenä "
    L"jatkuvana äänenä viimeisen päällekkäisyyden loppuun asti.",
    L"\r\n\r\nHØRBART TIDSSIGNAL\r\nSignalet følger mønstret for Greenwich Time Signal (GTS). Signal-fanen "
    L"har afkrydsningsfeltet Tidssignal aktivt og alternativknapper til intervaller på 1, 5, 10, 15, "
    L"20, 30 eller 60 minutter efter widgetens viste tid. Signalet er som udgangspunkt slået fra med "
    L"et interval på én time valgt. Når Signal slås fra og til i widgetmenuen, bevares intervallet. "
    L"Menuen viser alarmtid og signalinterval i parentes. Grænsen følger widgettiden, inklusive UTC, "
    L"tidszone, forskydning og NTP-korrektion. Fem korte og ét langt bip lyder; samtidige signaler "
    L"fra flere widgets flettes sammen. Ved dæmpning må et igangværende bip klinge ud; de følgende "
    L"springes over, og først det næste planlagte bip lyder efter ophævelse. En selvstændig Kalender "
    L"understøtter ikke alarm, tidssignal eller dæmpning; de tilhørende valg er deaktiverede og "
    L"findes ikke i menuen.\r\n\r\nMed et interval på 20 minutter lyder signalet ved :00, :20 og :40 "
    L"efter widgettiden.\r\n\r\nPå fanen Program kan du under Lyd for tidssignal vælge mellem Indbygget "
    L"generator og Systembip. Valget gælder tidssignaler fra alle widgets, inklusive tidssignaler for "
    L"alarmer. Indbygget generator er standardvalget.\r\n\r\nLydstyrkeskyderen for tidssignalet på fanen "
    L"Program viser den indbyggede generators niveau i dB. Højre endepunkt er 0 dB, maksimal "
    L"uforvrænget sinusamplitude; stilhed er −∞ dB. Standardlydstyrken er −18 dB. Klik på Test ved "
    L"tidssignalets lyd for at starte vedvarende prøveafspilning og på Stop test for at afslutte. "
    L"Begge lyde kan testes; testen gemmes ikke. At holde lydstyrkeskyderen starter også "
    L"prøveafspilning, indtil musen slippes, medmindre knaptesten kører. Afspilningen begynder på "
    L"næste hele sekund: korte toner hvert sekund og en lang ved :00, :05, :10 osv. Samtidige "
    L"signaler fra prøven, widgets og alarmer samles i én tone. Kun lydstyrkeskyderen er deaktiveret "
    L"for Systembip. Når testen stoppes, afspilles den igangværende tone færdig; en lang tone kan "
    L"vare op til et halvt sekund. Skyderen følger en decibelskala; −18 dB ligger i "
    L"midten.\r\n\r\nLydvalget er kun tilgængeligt, når systemet understøtter begge muligheder. "
    L"Widgetforskydninger gælder også i hundrededele af et sekund. Overlappende toner fra widgets, "
    L"alarmer og test afspilles som én sammenhængende tone indtil den sidste overlapning slutter.",
    L"\r\n\r\nHLJÓÐTÍMAMERKI\r\nMerkið fylgir mynstri Greenwich Time Signal (GTS). Tímamerkisflipinn hefur "
    L"gátreitinn Tímamerki virkt og valhnappa fyrir 1, 5, 10, 15, 20, 30 eða 60 mínútna bil samkvæmt "
    L"sýndum tíma græjunnar. Í upphafi er slökkt á merkinu og klukkustundarbil valið. Þegar slökkt og "
    L"kveikt er á Tímamerki í valmynd græjunnar helst bilið óbreytt. Valmyndin sýnir vekjaratímann og "
    L"tímamerkjabilið innan sviga. Mörkin fylgja tíma græjunnar, þar með talið UTC, tímabelti, "
    L"hliðrun og NTP-leiðrétting. Fimm stutt og eitt langt píp hljóma; samtímamerki margra græja eru "
    L"sameinuð. Við þöggun má þegar hafið píp klárast; þeim næstu er sleppt og fyrst næsta áætlaða "
    L"píp heyrist eftir að þöggun er aflétt. Sjálfstætt Dagatal styður hvorki vekjara, tímamerki né "
    L"þöggun; viðeigandi valkostir eru óvirkir og birtast ekki í valmyndinni.\r\n\r\nMeð 20 mínútna "
    L"millibili hljómar tímamerkið á :00, :20 og :40 samkvæmt tíma græjunnar.\r\n\r\nÁ flipanum Forrit "
    L"geturðu valið Innbyggður hljóðgjafi eða Kerfishljóð fyrir hljóð tímamerkisins. Valið gildir "
    L"fyrir tímamerki allra græja, þar á meðal tímamerki vekjara. Innbyggður hljóðgjafi er "
    L"sjálfgefinn.\r\n\r\nHljóðstyrkssleði tímamerkisins á flipanum Forrit sýnir styrk innbyggða "
    L"hljóðgjafans í dB. Hægri endastöð er 0 dB, hámarksútslag óbjagaðrar sínusbylgju; þögn er −∞ dB. "
    L"Sjálfgefinn hljóðstyrkur er −18 dB. Smelltu á Prófa við hljóð tímamerkisins til að hefja "
    L"samfellda prufu og á Stöðva prófun til að ljúka henni. Hægt er að prófa báðar hljóðgerðir; "
    L"prufan er ekki vistuð. Að halda hljóðstyrkssleðanum niðri byrjar einnig prufu þar til músinni "
    L"er sleppt, nema prufan með hnappnum sé í gangi. Hún hefst á næstu heilu sekúndu: stutt hljóð á "
    L"hverri sekúndu og langt á :00, :05, :10 o.s.frv. Samtímamerki frá prufunni, græjum og vekjurum "
    L"sameinast í einn tón. Aðeins hljóðstyrkssleðinn er óvirkur þegar Kerfishljóð er valið. Þegar "
    L"prófun er stöðvuð klárast tónninn sem er í gangi; langur tónn getur tekið allt að hálfa "
    L"sekúndu. Hliðrun græja tekur einnig mið af hundraðshlutum úr sekúndu. Tónar frá græjum, "
    L"vekjurum og prófunum sem skarast hljóma sem einn samfelldur tónn þar til síðustu skörun lýkur.",
    L"\r\n\r\nSESLİ ZAMAN SİNYALİ\r\nSinyal, Greenwich Time Signal (GTS) düzenini izler. Sinyal sekmesinde "
    L"Zaman sinyali etkin onay kutusu ve aracın gösterdiği saate göre 1, 5, 10, 15, 20, 30 veya 60 "
    L"dakikalık aralıklar için seçenek düğmeleri bulunur. Sinyal başlangıçta kapalıdır ve bir saatlik "
    L"aralık seçilidir. Araç menüsünde Sinyal seçeneğini kapatıp açmak aralığı korur. Menü, alarm "
    L"saatini ve sinyal aralığını parantez içinde gösterir. Sınır; UTC, saat dilimi, ofset ve NTP "
    L"düzeltmesi dâhil aracın zamanını izler. Beş kısa ve bir uzun ses çalar; birden çok aracın "
    L"eşzamanlı sinyalleri birleştirilir. Sessize alındığında başlamış olan ses bitebilir; sonrakiler "
    L"atlanır ve ses açıldıktan sonra yalnızca sıradaki planlanmış ses çalar. Bağımsız Takvim alarmı, "
    L"zaman sinyalini veya sessize almayı desteklemez; ilgili seçenekler devre dışıdır ve menüsünde "
    L"görünmez.\r\n\r\n20 dakikalık aralıkta sinyal, aracın saatine göre :00, :20 ve :40’ta "
    L"çalar.\r\n\r\nUygulama sekmesindeki Zaman sinyali sesi seçeneğiyle Yerleşik üreteç veya Sistem bip "
    L"sesi seçilebilir. Bu seçim, alarm zaman sinyalleri de dâhil olmak üzere tüm araçların zaman "
    L"sinyalleri için geçerlidir. Varsayılan seçenek Yerleşik üreteçtir.\r\n\r\nUygulama sekmesindeki "
    L"zaman sinyali ses düzeyi kaydırıcısı, yerleşik üretecin düzeyini dB olarak gösterir. En sağ "
    L"konum 0 dB, yani bozulmamış sinüs dalgasının en yüksek genliğidir; sessizlik −∞ dB’dir. "
    L"Varsayılan ses düzeyi −18 dB’dir. Sürekli önizlemeyi başlatmak için zaman sinyali sesinin "
    L"yanındaki Test et düğmesine, bitirmek için Testi durdur düğmesine basın. Her iki ses de test "
    L"edilebilir; test kaydedilmez. Ses kaydırıcısını basılı tutmak da fare bırakılana kadar önizleme "
    L"yapar; düğmeyle başlatılan test sürüyorsa önizleme devam eder. Sonraki tam saniyede başlar: her "
    L"saniye kısa, :00, :05, :10 vb. saniyelerde uzun ses çalar. Önizleme, araçlar ve alarmların "
    L"eşzamanlı sinyalleri tek bir seste birleştirilir. Sistem bip sesi seçiliyken yalnızca ses "
    L"kaydırıcısı devre dışıdır. Test durdurulduğunda çalmakta olan ses tamamlanır; uzun sesin "
    L"bitmesi yarım saniyeye kadar sürebilir. Araç ofsetleri saniyenin yüzde biri düzeyinde de "
    L"uygulanır. Araçların, alarmların ve testlerin örtüşen tonları son örtüşme bitene kadar tek ve "
    L"kesintisiz bir ton olarak çalar."
};

const wchar_t* HELP_ADDITIONAL_CLOCK_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nDalší hodiny: Ve widgetu Kalendář s hodinami lze na kartě Obecné zapnout až dvoje další hodiny "
    L"a zadat jejich názvy a časová pásma. "
    L"U každých hodin se pak zobrazí i příslušný den týdne. Velikost každého ciferníku se volí samostatně na "
    L"kartě Vzhled nebo v jeho nabídce "
    L"pravého tlačítka. Další hodiny nemají sekundovou ručičku. Při přidávání, odebírání a změně velikosti "
    L"zůstane widget přichycený ke stejným "
    L"hranám pracovní plochy.\r\n\r\nDvojklik přepíná sekundovou ručičku pouze přímo na hlavním ciferníku. "
    L"Nabídky dalších ciferníků obsahují "
    L"pouze velikosti. Další hodiny sdílejí jazyk, formát času, písma a offset widgetu; jejich digitální "
    L"čas se zobrazuje bez sekund.",
    L"\r\n\r\nAdditional clocks: On the General tab, a Calendar and clock widget can show up to two "
    L"additional clocks with their own names and "
    L"time zones. Each clock then also shows its local day of the week. Choose each clock face size "
    L"separately on the Appearance tab or from its "
    L"right-click menu. Additional clocks have no second hand. Adding, removing, or resizing clocks "
    L"preserves the widget's attachment to "
    L"work-area edges.\r\n\r\nOnly a double-click directly on the main clock face toggles its second hand. "
    L"Additional clock menus contain only "
    L"size choices. Additional clocks share the widget’s language, time format, fonts, and offset; their "
    L"digital time omits seconds.",
    L"\r\n\r\nZusätzliche Uhren: Auf der Registerkarte Allgemein kann das Widget Kalender und Uhr bis zu "
    L"zwei weitere Uhren mit eigenen Namen und "
    L"Zeitzonen anzeigen. Jede Uhr zeigt dann auch ihren lokalen Wochentag. Die Größe jedes Zifferblatts "
    L"lässt sich unter Darstellung oder in "
    L"seinem Kontextmenü wählen. Zusätzliche Uhren haben keinen Sekundenzeiger. Beim Hinzufügen, Entfernen "
    L"oder Ändern der Größe bleibt das "
    L"Widget an denselben Arbeitsbereichsrändern ausgerichtet.\r\n\r\nNur ein Doppelklick direkt auf das "
    L"Hauptzifferblatt schaltet dessen "
    L"Sekundenzeiger um. Die Menüs zusätzlicher Uhren enthalten nur Größen. Zusätzliche Uhren übernehmen "
    L"Sprache, Zeitformat, Schriften und "
    L"Versatz des Widgets; ihre digitale Zeit zeigt keine Sekunden.",
    L"\r\n\r\nHorloges supplémentaires : Dans l’onglet Général, le widget Calendrier et horloge peut "
    L"afficher deux horloges supplémentaires avec "
    L"leurs propres noms et fuseaux horaires. Chaque horloge affiche alors aussi son jour de la semaine "
    L"local. Choisissez la taille de chaque "
    L"cadran dans Apparence ou dans son menu contextuel. Les horloges supplémentaires n’ont pas de "
    L"trotteuse. L’ajout, le retrait et le "
    L"redimensionnement préservent l’alignement du widget sur les bords de la zone de travail.\r\n\r\nSeul "
    L"un double-clic directement sur le "
    L"cadran principal active ou désactive sa trotteuse. Les menus des cadrans supplémentaires ne proposent "
    L"que les tailles. Ces horloges "
    L"partagent la langue, le format, les polices et le décalage du widget ; leur heure numérique omet les "
    L"secondes.",
    L"\r\n\r\nRelojes adicionales: En la pestaña General, Calendario y reloj permite mostrar hasta dos "
    L"relojes adicionales con nombres y zonas "
    L"horarias propios. Cada reloj muestra también su día de la semana local. El tamaño de cada esfera se "
    L"elige en Apariencia o en su menú "
    L"contextual. Los relojes adicionales no tienen segundero. Al añadir, quitar o cambiar el tamaño de los "
    L"relojes se conserva la posición del "
    L"widget junto a los bordes del área de trabajo.\r\n\r\nSolo un doble clic directamente sobre la esfera "
    L"principal activa o desactiva su "
    L"segundero. Los menús de los relojes adicionales solo contienen tamaños. Comparten el idioma, formato, "
    L"fuentes y desfase del widget; su hora "
    L"digital no muestra segundos.",
    L"\r\n\r\nOrologi aggiuntivi: Nella scheda Generale, Calendario e orologio può mostrare fino a due "
    L"orologi aggiuntivi con nomi e fusi orari "
    L"propri. Ogni orologio mostra anche il giorno della settimana locale. La dimensione di ogni quadrante "
    L"si sceglie in Aspetto o nel suo menu "
    L"contestuale. Gli orologi aggiuntivi non hanno la lancetta dei secondi. Aggiungere, rimuovere o "
    L"ridimensionare gli orologi mantiene il "
    L"widget agganciato agli stessi bordi dell’area di lavoro.\r\n\r\nSolo un doppio clic direttamente sul "
    L"quadrante principale attiva o "
    L"disattiva la lancetta dei secondi. I menu dei quadranti aggiuntivi contengono solo le dimensioni. "
    L"Condividono lingua, formato, caratteri e "
    L"offset del widget; l’ora digitale non mostra i secondi.",
    L"\r\n\r\nDodatkowe zegary: Na karcie Ogólne widżet Kalendarz z zegarem może wyświetlać dwa dodatkowe "
    L"zegary z własnymi nazwami i strefami "
    L"czasowymi. Każdy zegar pokazuje wtedy także lokalny dzień tygodnia. Rozmiar każdej tarczy można wybrać "
    L"na karcie Wygląd lub w jej menu "
    L"kontekstowym. Dodatkowe zegary nie mają sekundnika. Dodawanie, usuwanie i zmiana rozmiaru zegarów "
    L"zachowują przyciągnięcie widżetu do tych "
    L"samych krawędzi obszaru roboczego.\r\n\r\nTylko dwuklik bezpośrednio na głównej tarczy przełącza jej "
    L"sekundnik. Menu dodatkowych tarcz "
    L"zawierają wyłącznie rozmiary. Dodatkowe zegary współdzielą język, format czasu, czcionki i "
    L"przesunięcie widżetu; ich czas cyfrowy nie "
    L"zawiera sekund.",
    L"\r\n\r\nĎalšie hodiny: Vo widgete Kalendár s hodinami možno na karte Všeobecné zapnúť až dvoje ďalšie "
    L"hodiny s vlastnými názvami a časovými "
    L"pásmami. Pri každých hodinách sa potom zobrazí aj príslušný deň týždňa. Veľkosť každého ciferníka sa "
    L"volí samostatne na karte Vzhľad alebo "
    L"v jeho kontextovej ponuke. Ďalšie hodiny nemajú sekundovú ručičku. Pri pridávaní, odoberaní a zmene "
    L"veľkosti zostane widget prichytený k "
    L"rovnakým hranám pracovnej plochy.\r\n\r\nDvojklik prepína sekundovú ručičku iba priamo na hlavnom "
    L"ciferníku. Ponuky ďalších ciferníkov "
    L"obsahujú iba veľkosti. Ďalšie hodiny zdieľajú jazyk, formát času, písma a offset widgetu; ich "
    L"digitálny čas sa zobrazuje bez sekúnd.",
    L"\r\n\r\nAdditional clocks: On the General tab, a Calendar and clock widget can show up to two "
    L"additional clocks with their own names and "
    L"time zones. Each clock then also shows its local day of the week. Choose each clock face size "
    L"separately on the Appearance tab or from its "
    L"right-click menu. Additional clocks have no second hand. Adding, removing, or resizing clocks "
    L"preserves the widget's attachment to "
    L"work-area edges.\r\n\r\nOnly a double-click directly on the main clock face toggles its second hand. "
    L"Additional clock menus contain only "
    L"size choices. Additional clocks share the widget’s language, time format, fonts, and offset; their "
    L"digital time omits seconds.",
    L"\r\n\r\nAdditional clocks: On the General tab, a Calendar and clock widget can show up to two "
    L"additional clocks with their own names and "
    L"time zones. Each clock then also shows its local day of the week. Choose each clock face size "
    L"separately on the Appearance tab or from its "
    L"right-click menu. Additional clocks have no second hand. Adding, removing, or resizing clocks "
    L"preserves the widget's attachment to "
    L"work-area edges.\r\n\r\nOnly a double-click directly on the main clock face toggles its second hand. "
    L"Additional clock menus contain only "
    L"size choices. Additional clocks share the widget’s language, time format, fonts, and offset; their "
    L"digital time omits seconds.",
    L"\r\n\r\nRelógios adicionais: No separador Geral, Calendário e relógio pode apresentar até dois "
    L"relógios adicionais com nomes e fusos "
    L"horários próprios. Cada relógio apresenta também o dia da semana local. Escolha o tamanho de cada "
    L"mostrador em Aspeto ou no respetivo menu "
    L"de contexto. Os relógios adicionais não têm ponteiro dos segundos. Adicionar, remover ou redimensionar "
    L"relógios mantém o widget junto às "
    L"mesmas margens da área de trabalho.\r\n\r\nSó um duplo clique diretamente no mostrador principal "
    L"alterna o ponteiro dos segundos. Os menus "
    L"dos mostradores adicionais contêm apenas tamanhos. Estes relógios partilham o idioma, formato, tipos "
    L"de letra e desvio do widget; a hora "
    L"digital não mostra segundos.",
    L"\r\n\r\nEkstra klokker: På fanen Generelt kan Kalender og klokke vise opptil to ekstra klokker med "
    L"egne navn og tidssoner. Hver klokke "
    L"viser også sin lokale ukedag. Velg størrelsen på hver urskive under Utseende eller i dens "
    L"høyreklikkmeny. Ekstra klokker har ingen "
    L"sekundviser. Når klokker legges til, fjernes eller endrer størrelse, forblir widgeten festet til de "
    L"samme kantene av "
    L"arbeidsområdet.\r\n\r\nBare et dobbeltklikk direkte på hovedurskiven veksler sekundviseren. Menyene "
    L"for ekstra urskiver inneholder bare "
    L"størrelser. Ekstra klokker deler widgetens språk, tidsformat, skrifter og forskyvning; den digitale "
    L"tiden viser ikke sekunder.",
    L"\r\n\r\nExtra klockor: På fliken Allmänt kan Kalender och klocka visa upp till två extra klockor med "
    L"egna namn och tidszoner. Varje klocka "
    L"visar även sin lokala veckodag. Välj storlek för varje urtavla under Utseende eller i dess "
    L"högerklicksmeny. Extra klockor saknar "
    L"sekundvisare. När klockor läggs till, tas bort eller ändrar storlek ligger widgeten kvar vid samma "
    L"kanter av arbetsområdet.\r\n\r\nEndast "
    L"ett dubbelklick direkt på huvudurtavlan växlar sekundvisaren. Menyerna för extra urtavlor innehåller "
    L"bara storlekar. Extra klockor delar "
    L"widgetens språk, tidsformat, teckensnitt och förskjutning; den digitala tiden visar inte sekunder.",
    L"\r\n\r\nLisäkellot: Yleiset-välilehdellä Kalenteri ja kello voi näyttää kaksi lisäkelloa, joilla on "
    L"omat nimet ja aikavyöhykkeet. Jokainen "
    L"kello näyttää myös paikallisen viikonpäivän. Valitse kunkin kellotaulun koko Ulkoasu-välilehdellä tai "
    L"sen pikavalikosta. Lisäkelloissa ei "
    L"ole sekuntiviisaria. Kellojen lisääminen, poistaminen tai koon muuttaminen säilyttää widgetin "
    L"kiinnityksen työalueen samoihin "
    L"reunoihin.\r\n\r\nVain pääkellotaulun suora kaksoisnapsautus vaihtaa sen sekuntiviisarin näkyvyyttä. "
    L"Lisäkellojen valikoissa on vain "
    L"kokovaihtoehdot. Lisäkellot käyttävät pienoisohjelman kieltä, aikamuotoa, fontteja ja poikkeamaa; "
    L"niiden digitaalinen aika ei sisällä "
    L"sekunteja.",
    L"\r\n\r\nEkstra ure: På fanen Generelt kan Kalender og ur vise op til to ekstra ure med egne navne og "
    L"tidszoner. Hvert ur viser også sin "
    L"lokale ugedag. Vælg størrelsen på hver urskive under Udseende eller i dens højrekliksmenu. Ekstra ure "
    L"har ingen sekundviser. Når ure "
    L"tilføjes, fjernes eller ændrer størrelse, forbliver widgetten fastgjort til de samme kanter af "
    L"arbejdsområdet.\r\n\r\nKun et dobbeltklik "
    L"direkte på hovedurskiven skifter sekundviseren. Menuerne for ekstra urskiver indeholder kun "
    L"størrelser. Ekstra ure deler widgetens sprog, "
    L"tidsformat, skrifttyper og forskydning; den digitale tid viser ikke sekunder.",
    L"\r\n\r\nViðbótarklukkur: Á flipanum Almennt getur Dagatal og klukka sýnt allt að tvær viðbótarklukkur "
    L"með eigin nöfnum og tímabeltum. Hver "
    L"klukka sýnir einnig vikudaginn á sínum stað. Veldu stærð hverrar klukkuskífu í Útliti eða í "
    L"hægrismellivalmynd hennar. Viðbótarklukkur hafa "
    L"engan sekúnduvísi. Þegar klukkum er bætt við, þær fjarlægðar eða stærð þeirra breytt helst græjan við "
    L"sömu brúnir "
    L"vinnusvæðisins.\r\n\r\nAðeins tvísmellur beint á aðalskífuna skiptir um sýnileika sekúnduvísisins. "
    L"Valmyndir aukaskífa innihalda aðeins "
    L"stærðir. Aukaklukkur nota tungumál, tímasnið, letur og hliðrun græjunnar; stafræni tíminn sýnir ekki "
    L"sekúndur.",
    L"\r\n\r\nEk saatler: Genel sekmesinde Takvim ve saat bileşeni, kendi adları ve saat dilimleri olan iki "
    L"ek saat gösterebilir. Her saat kendi "
    L"yerel haftanın gününü de gösterir. Her kadranın boyutunu Görünüm sekmesinden veya kendi sağ tıklama "
    L"menüsünden seçin. Ek saatlerde saniye "
    L"ibresi yoktur. Saat eklerken, kaldırırken veya boyutunu değiştirirken bileşen çalışma alanının aynı "
    L"kenarlarına bağlı "
    L"kalır.\r\n\r\nYalnızca ana kadrana doğrudan çift tıklamak saniye ibresini açıp kapatır. Ek kadranların "
    L"menülerinde yalnızca boyutlar "
    L"bulunur. Ek saatler aracın dilini, zaman biçimini, yazı tiplerini ve ofsetini paylaşır; dijital "
    L"saatlerinde saniye gösterilmez.",
};

const wchar_t* HELP_TIME_FORMAT_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nFORMÁT ČASU A PÁSMA\r\nFormát času na kartě Obecné nabízí Podle jazyka (výchozí), 12 hodin a "
    L"24 hodin. Podle jazyka převezme cyklus dané země; ruční volba zůstane zachována při změně "
    L"jazyka. Oddělovače a označení části dne odpovídají jazyku widgetu. Zatržítko AM/PM je výchozí "
    L"zapnuto a ve 12hodinovém režimu ovládá pouze označení části dne; není-li v dané kultuře "
    L"definováno, použije se AM/PM. Na celomonitorových hodinách je označení na samostatném spodním "
    L"řádku. UTC je vždy 24hodinové; volba cyklu a AM/PM jsou v něm neaktivní. Pojmenovaná pásma "
    L"používají občanský čas daného místa včetně jeho letního času; offset u názvu odpovídá "
    L"aktuálnímu datu. Samostatné položky UTC jsou pevné offsety od −12:00 do +14:00 po 15 minutách a "
    L"letní čas nepoužívají.",
    L"\r\n\r\nTIME FORMAT AND TIME ZONES\r\nTime format on the General tab offers Language default (the "
    L"default), 12 hours, and 24 hours. Language default follows the selected culture; a manual "
    L"choice is retained when the widget language changes. Separators and time markers follow the "
    L"widget language. AM/PM is checked by default and controls only the marker in 12-hour mode; "
    L"AM/PM is used when the culture defines no marker. Monitor clocks show the marker on a separate "
    L"line below the time. UTC always uses 24-hour time and disables the cycle and AM/PM controls. "
    L"Named time zones follow local civil time, including local daylight saving time; the offset next "
    L"to the name reflects the current date. Standalone UTC entries are fixed offsets from -12:00 to "
    L"+14:00 in 15-minute steps and do not observe daylight saving time.",
    L"\r\n\r\nZEITFORMAT UND ZEITZONEN\r\nZeitformat auf Allgemein bietet Nach Sprache (Standard), 12 "
    L"Stunden und 24 Stunden. Nach Sprache folgt der gewählten Kultur; eine manuelle Auswahl bleibt "
    L"bei Sprachänderungen erhalten. Trennzeichen und Tageszeitangaben folgen der Widget-Sprache. "
    L"AM/PM ist standardmäßig aktiviert und schaltet im 12-Stunden-Format nur die Tageszeitangabe um; "
    L"ohne kultureigene Angabe wird AM/PM verwendet. Bildschirmuhren zeigen sie in einer eigenen "
    L"Zeile unter der Uhrzeit. UTC verwendet immer 24 Stunden; Formatwahl und AM/PM sind dabei "
    L"deaktiviert. Benannte Zeitzonen folgen der jeweiligen Ortszeit einschließlich Sommerzeit; der "
    L"Versatz neben dem Namen gilt für das aktuelle Datum. Einzelne UTC-Einträge sind feste Versätze "
    L"von −12:00 bis +14:00 in 15-Minuten-Schritten ohne Sommerzeit.",
    L"\r\n\r\nFORMAT DE L’HEURE ET FUSEAUX\r\nFormat de l’heure dans Général propose Selon la langue (par "
    L"défaut), 12 heures et 24 heures. Le choix manuel est conservé lors d’un changement de langue. "
    L"Les séparateurs et indications suivent la langue du widget. AM/PM est coché par défaut et "
    L"commande uniquement l’indication en mode 12 heures ; AM/PM est utilisé si la culture n’en "
    L"définit aucune. Les horloges plein écran placent cette indication sur une ligne sous l’heure. "
    L"UTC utilise toujours 24 heures et désactive le choix du cycle et AM/PM. Les fuseaux nommés "
    L"suivent l’heure civile locale, y compris l’heure d’été ; le décalage indiqué correspond à la "
    L"date actuelle. Les entrées UTC seules sont des décalages fixes de −12:00 à +14:00 par pas de 15 "
    L"minutes, sans heure d’été.",
    L"\r\n\r\nFORMATO DE HORA Y ZONAS HORARIAS\r\nFormato de hora en General ofrece Según el idioma "
    L"(predeterminado), 12 horas y 24 horas. La elección manual se conserva al cambiar el idioma. Los "
    L"separadores e indicadores siguen el idioma del widget. AM/PM está marcado de forma "
    L"predeterminada y controla solo el indicador en modo de 12 horas; se usa AM/PM si la cultura no "
    L"define ninguno. Los relojes de monitor muestran el indicador en una línea debajo de la hora. "
    L"UTC siempre usa 24 horas y deshabilita la selección del ciclo y AM/PM. Las zonas con nombre "
    L"siguen la hora civil local, incluido el horario de verano; el desfase indicado corresponde a la "
    L"fecha actual. Las entradas UTC independientes son desfases fijos de −12:00 a +14:00 en pasos de "
    L"15 minutos, sin horario de verano.",
    L"\r\n\r\nFORMATO DELL’ORA E FUSI ORARI\r\nFormato ora in Generale offre Secondo la lingua "
    L"(predefinito), 12 ore e 24 ore. La scelta manuale viene mantenuta quando cambia la lingua. "
    L"Separatori e indicatori seguono la lingua del widget. AM/PM è selezionato per impostazione "
    L"predefinita e controlla solo l’indicatore nel formato a 12 ore; si usa AM/PM se la cultura non "
    L"ne definisce uno. Gli orologi a schermo intero mostrano l’indicatore su una riga sotto l’ora. "
    L"UTC usa sempre 24 ore e disabilita la scelta del ciclo e AM/PM. I fusi con nome seguono l’ora "
    L"civile locale, inclusa l’ora legale; lo scostamento indicato corrisponde alla data attuale. Le "
    L"voci UTC separate sono scostamenti fissi da −12:00 a +14:00 a intervalli di 15 minuti, senza "
    L"ora legale.",
    L"\r\n\r\nFORMAT CZASU I STREFY\r\nFormat czasu na karcie Ogólne oferuje Według języka (domyślnie), 12 "
    L"godzin i 24 godziny. Ręczny wybór pozostaje zachowany przy zmianie języka. Separatory i "
    L"oznaczenia odpowiadają językowi widżetu. AM/PM jest domyślnie zaznaczone i steruje tylko "
    L"oznaczeniem w trybie 12-godzinnym; gdy kultura nie określa oznaczenia, używane jest AM/PM. "
    L"Zegary pełnoekranowe pokazują je w osobnym wierszu pod czasem. UTC zawsze używa 24 godzin i "
    L"wyłącza wybór cyklu oraz AM/PM. Nazwane strefy stosują lokalny czas urzędowy, w tym czas letni; "
    L"przesunięcie obok nazwy odpowiada bieżącej dacie. Osobne wpisy UTC to stałe przesunięcia od "
    L"−12:00 do +14:00 co 15 minut, bez czasu letniego.",
    L"\r\n\r\nFORMÁT ČASU A PÁSMA\r\nFormát času na karte Všeobecné ponúka Podľa jazyka (predvolené), 12 "
    L"hodín a 24 hodín. Ručná voľba zostane zachovaná pri zmene jazyka. Oddeľovače a označenia časti "
    L"dňa zodpovedajú jazyku widgetu. AM/PM je predvolene začiarknuté a v 12-hodinovom režime ovláda "
    L"iba označenie časti dňa; ak ho kultúra nedefinuje, použije sa AM/PM. Celomonitorové hodiny ho "
    L"zobrazujú na samostatnom riadku pod časom. UTC je vždy 24-hodinové a voľby cyklu a AM/PM sú "
    L"neaktívne. Pomenované pásma používajú občiansky čas daného miesta vrátane jeho letného času; "
    L"posun pri názve zodpovedá aktuálnemu dátumu. Samostatné položky UTC sú pevné posuny od −12:00 "
    L"do +14:00 po 15 minútach bez letného času.",
    L"\r\n\r\nTIME FORMAT AND TIME ZONES\r\nTime format on the General tab offers Language default (the "
    L"default), 12 hours, and 24 hours. Language default follows the selected culture; a manual "
    L"choice is retained when the widget language changes. Separators and time markers follow the "
    L"widget language. AM/PM is checked by default and controls only the marker in 12-hour mode; "
    L"AM/PM is used when the culture defines no marker. Monitor clocks show the marker on a separate "
    L"line below the time. UTC always uses 24-hour time and disables the cycle and AM/PM controls. "
    L"Named time zones follow local civil time, including local daylight saving time; the offset next "
    L"to the name reflects the current date. Standalone UTC entries are fixed offsets from -12:00 to "
    L"+14:00 in 15-minute steps and do not observe daylight saving time.",
    L"\r\n\r\nTIME FORMAT AND TIME ZONES\r\nTime format on the General tab offers Language default (the "
    L"default), 12 hours, and 24 hours. Language default follows the selected culture; a manual "
    L"choice is retained when the widget language changes. Separators and time markers follow the "
    L"widget language. AM/PM is checked by default and controls only the marker in 12-hour mode; "
    L"AM/PM is used when the culture defines no marker. Monitor clocks show the marker on a separate "
    L"line below the time. UTC always uses 24-hour time and disables the cycle and AM/PM controls. "
    L"Named time zones follow local civil time, including local daylight saving time; the offset next "
    L"to the name reflects the current date. Standalone UTC entries are fixed offsets from -12:00 to "
    L"+14:00 in 15-minute steps and do not observe daylight saving time.",
    L"\r\n\r\nFORMATO DA HORA E FUSOS HORÁRIOS\r\nFormato da hora em Geral oferece Conforme o idioma "
    L"(predefinição), 12 horas e 24 horas. A escolha manual é mantida quando o idioma muda. Os "
    L"separadores e indicadores seguem o idioma do widget. AM/PM está selecionado por predefinição e "
    L"controla apenas o indicador no modo de 12 horas; usa-se AM/PM se a cultura não definir nenhum. "
    L"Os relógios de monitor mostram o indicador numa linha abaixo da hora. UTC usa sempre 24 horas e "
    L"desativa a escolha do ciclo e AM/PM. Os fusos com nome seguem a hora civil local, incluindo a "
    L"hora de verão; o desvio junto ao nome corresponde à data atual. As entradas UTC isoladas são "
    L"desvios fixos de −12:00 a +14:00 em intervalos de 15 minutos, sem hora de verão.",
    L"\r\n\r\nTIDSFORMAT OG TIDSSONER\r\nTidsformat på Generelt tilbyr Etter språk (standard), 12 timer og "
    L"24 timer. Et manuelt valg beholdes når språket endres. Skilletegn og tidsmarkører følger "
    L"widgetens språk. AM/PM er på som standard og styrer bare markøren i 12-timersformat; AM/PM "
    L"brukes hvis kulturen ikke har en egen markør. Skjermklokker viser markøren på en egen linje "
    L"under tiden. UTC bruker alltid 24-timersformat og deaktiverer formatvalget og AM/PM. Navngitte "
    L"tidssoner følger lokal tid, inkludert sommertid; forskyvningen ved navnet gjelder dagens dato. "
    L"Egne UTC-oppføringer er faste forskyvninger fra −12:00 til +14:00 i trinn på 15 minutter, uten "
    L"sommertid.",
    L"\r\n\r\nTIDSFORMAT OCH TIDSZONER\r\nTidsformat på Allmänt erbjuder Enligt språk (standard), 12 timmar "
    L"och 24 timmar. Ett manuellt val behålls när språket ändras. Avgränsare och tidsbeteckningar "
    L"följer widgetens språk. AM/PM är på som standard och styr bara beteckningen i 12-timmarsformat; "
    L"AM/PM används om kulturen saknar en egen beteckning. Bildskärmsklockor visar den på en egen rad "
    L"under tiden. UTC använder alltid 24-timmarsformat och inaktiverar formatvalet och AM/PM. "
    L"Namngivna tidszoner följer lokal tid, inklusive sommartid; förskjutningen vid namnet gäller "
    L"dagens datum. Separata UTC-poster är fasta förskjutningar från −12:00 till +14:00 i steg om 15 "
    L"minuter, utan sommartid.",
    L"\r\n\r\nAIKAMUOTO JA AIKAVYÖHYKKEET\r\nYleiset-välilehden Aikamuoto tarjoaa Kielen mukaan (oletus), "
    L"12 tuntia ja 24 tuntia. Käsin tehty valinta säilyy kielen vaihtuessa. Erottimet ja merkinnät "
    L"noudattavat pienoisohjelman kieltä. AM/PM on oletusarvoisesti valittu ja ohjaa vain merkintää "
    L"12 tunnin muodossa; AM/PM-merkintää käytetään, jos kulttuurilla ei ole omaa. Koko näytön kellot "
    L"näyttävät merkinnän ajan alla omalla rivillään. UTC käyttää aina 24 tunnin muotoa ja poistaa "
    L"aikamuodon sekä AM/PM-valinnan käytöstä. Nimetyt aikavyöhykkeet noudattavat paikallista aikaa "
    L"kesäaikoineen; nimen vieressä oleva siirtymä vastaa nykyistä päivämäärää. Erilliset "
    L"UTC-valinnat ovat kiinteitä siirtymiä −12:00:sta +14:00:aan 15 minuutin välein ilman kesäaikaa.",
    L"\r\n\r\nTIDSFORMAT OG TIDSZONER\r\nTidsformat på Generelt tilbyder Efter sprog (standard), 12 timer "
    L"og 24 timer. Et manuelt valg bevares, når sproget ændres. Separatorer og tidsmarkører følger "
    L"widgetens sprog. AM/PM er slået til som standard og styrer kun markøren i 12-timersformat; "
    L"AM/PM bruges, hvis kulturen ikke har en egen markør. Skærmure viser markøren på en separat "
    L"linje under tiden. UTC bruger altid 24-timersformat og deaktiverer formatvalget og AM/PM. "
    L"Navngivne tidszoner følger lokal tid inklusive sommertid; forskydningen ved navnet gælder den "
    L"aktuelle dato. Separate UTC-poster er faste forskydninger fra −12:00 til +14:00 i trin på 15 "
    L"minutter uden sommertid.",
    L"\r\n\r\nTÍMASNIÐ OG TÍMABELTI\r\nTímasnið á Almennt býður Samkvæmt tungumáli (sjálfgefið), 12 "
    L"klukkustundir og 24 klukkustundir. Handvirkt val helst við breytingu á tungumáli. "
    L"Aðgreiningarmerki og tímamerkingar fylgja tungumáli græjunnar. AM/PM er sjálfgefið virkt og "
    L"stjórnar aðeins merkingunni í 12 klukkustunda sniði; AM/PM er notað ef menningarsvæðið "
    L"skilgreinir enga merkingu. Skjáklukkur sýna hana á sér línu undir tímanum. UTC notar alltaf 24 "
    L"klukkustunda snið og gerir sniðsval og AM/PM óvirkt. Nafngreind tímabelti fylgja staðartíma með "
    L"sumartíma; hliðrunin við nafnið gildir fyrir daginn í dag. Sérstakar UTC-færslur eru fastar "
    L"hliðranir frá −12:00 til +14:00 í 15 mínútna skrefum án sumartíma.",
    L"\r\n\r\nSAAT BİÇİMİ VE SAAT DİLİMLERİ\r\nGenel sekmesindeki Saat biçimi, Dile göre (varsayılan), 12 "
    L"saat ve 24 saat seçeneklerini sunar. Dil değiştiğinde elle seçilen düzen korunur. Ayırıcılar ve "
    L"göstergeler araç diline uyar. AM/PM varsayılan olarak işaretlidir ve 12 saatlik düzende "
    L"yalnızca göstergeyi denetler; kültür bir gösterge tanımlamıyorsa AM/PM kullanılır. Tam ekran "
    L"saatler göstergeyi saatin altında ayrı bir satırda gösterir. UTC her zaman 24 saatlik düzeni "
    L"kullanır ve düzen seçimi ile AM/PM seçeneğini devre dışı bırakır. Adlandırılmış saat dilimleri, "
    L"yaz saati dahil yerel resmi saati izler; adın yanındaki fark güncel tarihe aittir. Ayrı UTC "
    L"girdileri −12:00 ile +14:00 arasında 15 dakikalık adımlarla sabit farklardır ve yaz saati "
    L"uygulamaz."
};

const wchar_t* HELP_TIME_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZDROJ ČASU\r\nNa kartě Čas lze pro celou aplikaci, tedy společně pro všechny widgety, vybrat "
    L"systémový čas Windows nebo čas ze zadaných serverů NTP. NTP koriguje pouze čas zobrazovaný v "
    L"CalClock; systémové hodiny Windows se nikdy nemění. Dokud nebyl získán platný údaj, používá se "
    L"systémový čas. Po pozdějším výpadku zůstane poslední korekce až do ukončení aplikace a "
    L"synchronizace se opakuje. NTP je výchozí. Automatická sada volí podle systémové oblasti české a "
    L"slovenské servery, PTB pro Evropu nebo celosvětový fond. Více měření se filtruje podle síťového "
    L"zpoždění a odlehlých odpovědí. Synchronizovat nyní spustí nové měření okamžitě. Při změně "
    L"serverů zůstane dosavadní platná korekce aktivní do získání nové odpovědi.\r\n\r\nZÁZNAM "
    L"SYNCHRONIZACE NTP\r\nNa kartě Čas je záznam dotazů na servery NTP od spuštění aplikace. Každý "
    L"záznam obsahuje datum a místní čas počítače, server a stav. OK označuje platnou odpověď a θ "
    L"její odchylku vůči systémovému času Windows. ERR uvádí důvod neúspěchu a případný chybový kód. "
    L"Poslední záznam skupiny obsahuje také výslednou odchylku Θ, pokud se podařilo získat použitelná "
    L"měření.\r\n\r\nOdchylky se zobrazují v milisekundách se čtyřmi desetinnými místy. Kladná hodnota "
    L"znamená, že čas serveru je vůči Windows napřed; záporná, že je pozadu. Výsledná odchylka Θ "
    L"zohledňuje přijatá měření a je uvedena také ve stavu synchronizace.\r\n\r\nUložit log uloží záznamy "
    L"do CSV včetně odchylek a důvodů chyb. Záznamy se mezi spuštěními neuchovávají; chcete-li je "
    L"zachovat, uložte je před ukončením aplikace.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP servers for the "
    L"whole application and therefore for all widgets. NTP corrects only the time displayed by "
    L"CalClock; the Windows clock is never changed. System time is used until the first valid reply. "
    L"After a later outage, the last correction remains until the application closes and "
    L"synchronization is retried. NTP is the default. The automatic set chooses Czech and Slovak "
    L"servers, PTB for Europe, or the global pool according to the system region. Multiple "
    L"measurements are filtered by network delay and outlying replies. Synchronize now starts a fresh "
    L"measurement immediately. When servers change, the current valid correction remains active until "
    L"a new reply is obtained.\r\n\r\nNTP SYNCHRONIZATION LOG\r\nThe Time tab records NTP server queries "
    L"since the application started. Each entry contains the date and local computer time, server, "
    L"and status. OK identifies a valid reply, with θ showing its offset from Windows system time. "
    L"ERR gives the failure reason and any error code. The final entry in a query group also shows "
    L"the combined offset Θ when usable measurements are available.\r\n\r\nOffsets are displayed in "
    L"milliseconds with four decimal places. A positive value means the server clock is ahead of "
    L"Windows; a negative value means it is behind. The combined offset Θ reflects the accepted "
    L"measurements and is also shown in the synchronization status.\r\n\r\nSave log exports the records "
    L"to CSV, including offsets and failure details. Records are not retained between application "
    L"sessions; save them before exiting if you want to keep them.",
    L"\r\n\r\nZEITQUELLE\r\nAuf der Registerkarte Zeit wird für die gesamte Anwendung und damit für alle "
    L"Widgets die Windows-Systemzeit oder die Zeit der eingestellten NTP-Server gewählt. NTP "
    L"korrigiert nur die in CalClock angezeigte Zeit; die Windows-Uhr wird nie geändert. Bis zur "
    L"ersten gültigen Antwort wird die Systemzeit verwendet. Bei einem späteren Ausfall bleibt die "
    L"letzte Korrektur bis zum Beenden der Anwendung erhalten und die Synchronisierung wird "
    L"wiederholt. NTP ist voreingestellt. Die automatische Gruppe wählt nach der Systemregion die "
    L"tschechisch-slowakischen Server, PTB für Europa oder den globalen Pool. Mehrere Messungen "
    L"werden nach Netzverzögerung und Ausreißern gefiltert. Jetzt synchronisieren startet sofort eine "
    L"neue Messung. Beim Serverwechsel bleibt die bisherige gültige Korrektur bis zu einer neuen "
    L"Antwort aktiv.\r\n\r\nNTP-SYNCHRONISIERUNGSPROTOKOLL\r\nDie Registerkarte Zeit protokolliert "
    L"NTP-Serverabfragen seit dem Programmstart. Jeder Eintrag enthält Datum und lokale Computerzeit, "
    L"Server und Status. OK bezeichnet eine gültige Antwort; θ zeigt deren Abweichung von der "
    L"Windows-Systemzeit. ERR nennt den Fehlergrund und gegebenenfalls einen Fehlercode. Der letzte "
    L"Eintrag einer Abfragegruppe enthält auch die berechnete Abweichung Θ, sofern verwertbare "
    L"Messungen vorliegen.\r\n\r\nAbweichungen werden in Millisekunden mit vier Nachkommastellen "
    L"angezeigt. Ein positiver Wert bedeutet, dass die Serveruhr Windows voraus ist; ein negativer "
    L"Wert bedeutet, dass sie nachgeht. Θ berücksichtigt die angenommenen Messungen und wird auch im "
    L"Synchronisierungsstatus angezeigt.\r\n\r\nProtokoll speichern exportiert die Einträge "
    L"einschließlich Abweichungen und Fehlerdetails als CSV. Einträge werden nicht über "
    L"Programmstarts hinweg aufbewahrt; speichern Sie sie vor dem Beenden, wenn Sie sie behalten "
    L"möchten.",
    L"\r\n\r\nSOURCE DE L’HEURE\r\nL’onglet Heure sélectionne l’heure système Windows ou les serveurs NTP "
    L"configurés pour toute l’application, donc pour tous les widgets. NTP corrige uniquement l’heure "
    L"affichée par CalClock ; l’horloge Windows n’est jamais modifiée. L’heure système est utilisée "
    L"jusqu’à la première réponse valide. Après une panne ultérieure, la dernière correction reste "
    L"jusqu’à la fermeture de l’application et la synchronisation est retentée. NTP est la valeur par "
    L"défaut. Le jeu automatique choisit les serveurs tchèques et slovaques, PTB pour l’Europe ou le "
    L"pool mondial selon la région système. Plusieurs mesures sont filtrées selon le délai réseau et "
    L"les réponses aberrantes. Synchroniser maintenant lance immédiatement une nouvelle mesure. Lors "
    L"d’un changement de serveur, la correction valide actuelle reste active jusqu’à une nouvelle "
    L"réponse.\r\n\r\nJOURNAL DE SYNCHRONISATION NTP\r\nL’onglet Heure conserve les requêtes aux serveurs "
    L"NTP depuis le lancement de l’application. Chaque entrée indique la date et l’heure locale de "
    L"l’ordinateur, le serveur et l’état. OK signale une réponse valide et θ son décalage par rapport "
    L"à l’heure système Windows. ERR indique la cause de l’échec et, le cas échéant, un code "
    L"d’erreur. La dernière entrée d’un groupe de requêtes indique aussi le décalage calculé Θ "
    L"lorsque des mesures exploitables sont disponibles.\r\n\r\nLes décalages sont exprimés en "
    L"millisecondes avec quatre décimales. Une valeur positive signifie que l’horloge du serveur est "
    L"en avance sur Windows ; une valeur négative signifie qu’elle est en retard. Θ tient compte des "
    L"mesures acceptées et apparaît aussi dans l’état de synchronisation.\r\n\r\nEnregistrer le journal "
    L"exporte les entrées en CSV, avec les décalages et les détails des erreurs. Les entrées ne sont "
    L"pas conservées entre les sessions ; enregistrez-les avant de quitter pour les garder.",
    L"\r\n\r\nORIGEN DE HORA\r\nLa pestaña Hora selecciona la hora del sistema Windows o los servidores NTP "
    L"configurados para toda la aplicación y, por tanto, para todos los widgets. NTP solo corrige la "
    L"hora mostrada por CalClock; el reloj de Windows nunca se modifica. Se usa la hora del sistema "
    L"hasta la primera respuesta válida. Tras una interrupción posterior, la última corrección "
    L"permanece hasta que se cierre la aplicación y se reintenta la sincronización. NTP es el valor "
    L"predeterminado. El conjunto automático elige servidores checos y eslovacos, PTB para Europa o "
    L"el grupo mundial según la región del sistema. Varias mediciones se filtran por retardo de red y "
    L"respuestas atípicas. Sincronizar ahora inicia una medición nueva de inmediato. Al cambiar "
    L"servidores, la corrección válida actual sigue activa hasta obtener una respuesta "
    L"nueva.\r\n\r\nREGISTRO DE SINCRONIZACIÓN NTP\r\nLa pestaña Hora registra las consultas a servidores "
    L"NTP desde el inicio de la aplicación. Cada entrada contiene la fecha y hora local del equipo, "
    L"el servidor y el estado. OK identifica una respuesta válida y θ su desfase respecto a la hora "
    L"del sistema Windows. ERR indica el motivo del fallo y, si existe, su código. La última entrada "
    L"de cada grupo de consultas también muestra el desfase calculado Θ cuando hay mediciones "
    L"utilizables.\r\n\r\nLos desfases se muestran en milisegundos con cuatro decimales. Un valor "
    L"positivo indica que el reloj del servidor está adelantado respecto a Windows; uno negativo "
    L"indica que está atrasado. Θ refleja las mediciones aceptadas y también aparece en el estado de "
    L"sincronización.\r\n\r\nGuardar registro exporta las entradas a CSV, incluidos los desfases y los "
    L"detalles de los errores. Las entradas no se conservan entre sesiones; guárdelas antes de salir "
    L"si desea conservarlas.",
    L"\r\n\r\nORIGINE DELL’ORA\r\nLa scheda Ora seleziona l’ora di sistema Windows o i server NTP "
    L"configurati per l’intera applicazione e quindi per tutti i widget. NTP corregge solo l’ora "
    L"visualizzata da CalClock; l’orologio di Windows non viene mai modificato. L’ora di sistema "
    L"viene usata fino alla prima risposta valida. Dopo una successiva interruzione, l’ultima "
    L"correzione rimane fino alla chiusura dell’applicazione e la sincronizzazione viene ripetuta. "
    L"NTP è l’impostazione predefinita. Il gruppo automatico sceglie i server cechi e slovacchi, PTB "
    L"per l’Europa o il pool globale in base all’area di sistema. Più misurazioni vengono filtrate in "
    L"base al ritardo di rete e alle risposte anomale. Sincronizza ora avvia subito una nuova "
    L"misurazione. Cambiando server, la correzione valida corrente resta attiva fino a una nuova "
    L"risposta.\r\n\r\nREGISTRO DI SINCRONIZZAZIONE NTP\r\nLa scheda Ora registra le richieste ai server "
    L"NTP dall’avvio dell’applicazione. Ogni voce contiene data e ora locale del computer, server e "
    L"stato. OK indica una risposta valida e θ il suo scostamento dall’ora di sistema Windows. ERR "
    L"indica il motivo dell’errore e l’eventuale codice. L’ultima voce di un gruppo di richieste "
    L"mostra anche lo scostamento calcolato Θ quando sono disponibili misurazioni "
    L"utilizzabili.\r\n\r\nGli scostamenti sono espressi in millisecondi con quattro cifre decimali. Un "
    L"valore positivo indica che l’orologio del server è avanti rispetto a Windows; un valore "
    L"negativo indica che è indietro. Θ tiene conto delle misurazioni accettate ed è mostrato anche "
    L"nello stato di sincronizzazione.\r\n\r\nSalva registro esporta le voci in CSV, compresi scostamenti "
    L"e dettagli degli errori. Le voci non vengono conservate tra le sessioni; salvarle prima di "
    L"uscire se si desidera mantenerle.",
    L"\r\n\r\nŹRÓDŁO CZASU\r\nKarta Czas wybiera dla całej aplikacji, a więc dla wszystkich widżetów, czas "
    L"systemowy Windows albo skonfigurowane serwery NTP. NTP koryguje wyłącznie czas wyświetlany "
    L"przez CalClock; zegar Windows nigdy nie jest zmieniany. Do pierwszej prawidłowej odpowiedzi "
    L"używany jest czas systemowy. Po późniejszej awarii ostatnia korekta pozostaje do zamknięcia "
    L"aplikacji, a synchronizacja jest ponawiana. NTP jest ustawieniem domyślnym. Zestaw automatyczny "
    L"wybiera według regionu systemu serwery czeskie i słowackie, PTB dla Europy albo pulę globalną. "
    L"Wiele pomiarów jest filtrowanych według opóźnienia sieci i wartości odstających. Synchronizuj "
    L"teraz natychmiast rozpoczyna nowy pomiar. Po zmianie serwerów bieżąca prawidłowa korekta działa "
    L"do uzyskania nowej odpowiedzi.\r\n\r\nDZIENNIK SYNCHRONIZACJI NTP\r\nKarta Czas rejestruje zapytania "
    L"do serwerów NTP od uruchomienia aplikacji. Każdy wpis zawiera datę i lokalny czas komputera, "
    L"serwer oraz stan. OK oznacza prawidłową odpowiedź, a θ jej odchylenie od czasu systemowego "
    L"Windows. ERR podaje przyczynę niepowodzenia i ewentualny kod błędu. Ostatni wpis grupy zapytań "
    L"zawiera również obliczone odchylenie Θ, jeśli dostępne są użyteczne pomiary.\r\n\r\nOdchylenia są "
    L"wyświetlane w milisekundach z czterema miejscami po przecinku. Wartość dodatnia oznacza, że "
    L"zegar serwera wyprzedza Windows; ujemna oznacza, że jest opóźniony. Θ uwzględnia zaakceptowane "
    L"pomiary i jest również widoczne w stanie synchronizacji.\r\n\r\nZapisz dziennik eksportuje wpisy do "
    L"CSV wraz z odchyleniami i szczegółami błędów. Wpisy nie są zachowywane między uruchomieniami; "
    L"zapisz je przed zamknięciem aplikacji, jeśli chcesz je zachować.",
    L"\r\n\r\nZDROJ ČASU\r\nNa karte Čas možno pre celú aplikáciu, teda spoločne pre všetky widgety, vybrať "
    L"systémový čas Windows alebo čas zo zadaných serverov NTP. NTP koriguje iba čas zobrazený v "
    L"CalClock; systémové hodiny Windows sa nikdy nemenia. Do prvej platnej odpovede sa používa "
    L"systémový čas. Po neskoršom výpadku zostane posledná korekcia až do ukončenia aplikácie a "
    L"synchronizácia sa zopakuje. NTP je predvolené. Automatická sada vyberie podľa systémovej "
    L"oblasti české a slovenské servery, PTB pre Európu alebo celosvetový fond. Viaceré merania sa "
    L"filtrujú podľa sieťového oneskorenia a odľahlých odpovedí. Synchronizovať teraz spustí nové "
    L"meranie ihneď. Pri zmene serverov zostane doterajšia platná korekcia aktívna do získania novej "
    L"odpovede.\r\n\r\nZÁZNAM SYNCHRONIZÁCIE NTP\r\nNa karte Čas je záznam dotazov na servery NTP od "
    L"spustenia aplikácie. Každý záznam obsahuje dátum a miestny čas počítača, server a stav. OK "
    L"označuje platnú odpoveď a θ jej odchýlku voči systémovému času Windows. ERR uvádza dôvod "
    L"neúspechu a prípadný chybový kód. Posledný záznam skupiny obsahuje aj výslednú odchýlku Θ, ak "
    L"sa podarilo získať použiteľné merania.\r\n\r\nOdchýlky sa zobrazujú v milisekundách so štyrmi "
    L"desatinnými miestami. Kladná hodnota znamená, že čas servera je voči Windows vpred; záporná, že "
    L"zaostáva. Výsledná odchýlka Θ zohľadňuje prijaté merania a je uvedená aj v stave "
    L"synchronizácie.\r\n\r\nUložiť log uloží záznamy do CSV vrátane odchýlok a dôvodov chýb. Záznamy sa "
    L"medzi spusteniami neuchovávajú; ak ich chcete zachovať, uložte ich pred ukončením aplikácie.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP servers for the "
    L"whole application and therefore for all widgets. NTP corrects only the time displayed by "
    L"CalClock; the Windows clock is never changed. System time is used until the first valid reply. "
    L"After a later outage, the last correction remains until the application closes and "
    L"synchronization is retried. NTP is the default. The automatic set chooses Czech and Slovak "
    L"servers, PTB for Europe, or the global pool according to the system region. Multiple "
    L"measurements are filtered by network delay and outlying replies. Synchronize now starts a fresh "
    L"measurement immediately. When servers change, the current valid correction remains active until "
    L"a new reply is obtained.\r\n\r\nNTP SYNCHRONIZATION LOG\r\nThe Time tab records NTP server queries "
    L"since the application started. Each entry contains the date and local computer time, server, "
    L"and status. OK identifies a valid reply, with θ showing its offset from Windows system time. "
    L"ERR gives the failure reason and any error code. The final entry in a query group also shows "
    L"the combined offset Θ when usable measurements are available.\r\n\r\nOffsets are displayed in "
    L"milliseconds with four decimal places. A positive value means the server clock is ahead of "
    L"Windows; a negative value means it is behind. The combined offset Θ reflects the accepted "
    L"measurements and is also shown in the synchronization status.\r\n\r\nSave log exports the records "
    L"to CSV, including offsets and failure details. Records are not retained between application "
    L"sessions; save them before exiting if you want to keep them.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP servers for the "
    L"whole application and therefore for all widgets. NTP corrects only the time displayed by "
    L"CalClock; the Windows clock is never changed. System time is used until the first valid reply. "
    L"After a later outage, the last correction remains until the application closes and "
    L"synchronization is retried. NTP is the default. The automatic set chooses Czech and Slovak "
    L"servers, PTB for Europe, or the global pool according to the system region. Multiple "
    L"measurements are filtered by network delay and outlying replies. Synchronize now starts a fresh "
    L"measurement immediately. When servers change, the current valid correction remains active until "
    L"a new reply is obtained.\r\n\r\nNTP SYNCHRONIZATION LOG\r\nThe Time tab records NTP server queries "
    L"since the application started. Each entry contains the date and local computer time, server, "
    L"and status. OK identifies a valid reply, with θ showing its offset from Windows system time. "
    L"ERR gives the failure reason and any error code. The final entry in a query group also shows "
    L"the combined offset Θ when usable measurements are available.\r\n\r\nOffsets are displayed in "
    L"milliseconds with four decimal places. A positive value means the server clock is ahead of "
    L"Windows; a negative value means it is behind. The combined offset Θ reflects the accepted "
    L"measurements and is also shown in the synchronization status.\r\n\r\nSave log exports the records "
    L"to CSV, including offsets and failure details. Records are not retained between application "
    L"sessions; save them before exiting if you want to keep them.",
    L"\r\n\r\nORIGEM DA HORA\r\nO separador Hora escolhe para toda a aplicação a hora do Windows ou "
    L"servidores NTP. O NTP corrige apenas o CalClock e nunca altera o Windows. A última correção "
    L"válida permanece na memória durante uma falha. A predefinição é NTP; o conjunto automático "
    L"escolhe servidores pela região e filtra medições por atraso e valores atípicos.\r\n\r\nREGISTO DE "
    L"SINCRONIZAÇÃO NTP\r\nO separador Hora regista as consultas a servidores NTP desde o início da "
    L"aplicação. Cada entrada contém a data e hora local do computador, o servidor e o estado. OK "
    L"identifica uma resposta válida e θ o seu desvio em relação à hora do Windows. ERR indica a "
    L"causa da falha e o eventual código de erro. A última entrada de um grupo de consultas mostra "
    L"também o desvio calculado Θ quando existem medições utilizáveis.\r\n\r\nOs desvios são apresentados "
    L"em milissegundos com quatro casas decimais. Um valor positivo significa que o relógio do "
    L"servidor está adiantado em relação ao Windows; um valor negativo significa que está atrasado. Θ "
    L"reflete as medições aceites e também aparece no estado da sincronização.\r\n\r\nSalvar registro "
    L"exporta as entradas para CSV, incluindo desvios e detalhes das falhas. As entradas não são "
    L"conservadas entre sessões; guarde-as antes de sair se quiser mantê-las.",
    L"\r\n\r\nTIDSKILDE\r\nFanen Tid velger Windows-tid eller NTP-servere for hele programmet. NTP "
    L"korrigerer bare CalClock og endrer aldri Windows. Siste gyldige korreksjon beholdes i minnet "
    L"under et avbrudd. NTP er standard; det automatiske settet velger servere etter region og "
    L"filtrerer målinger etter forsinkelse og avvik.\r\n\r\nNTP-SYNKRONISERINGSLOGG\r\nFanen Tid "
    L"registrerer NTP-serverforespørsler siden programmet startet. Hver oppføring inneholder dato og "
    L"lokal datamaskintid, server og status. OK angir et gyldig svar, og θ viser tidsavviket fra "
    L"Windows-systemtiden. ERR angir årsaken til feilen og en eventuell feilkode. Den siste "
    L"oppføringen i en forespørselsgruppe viser også det beregnede tidsavviket Θ når brukbare "
    L"målinger er tilgjengelige.\r\n\r\nTidsavvik vises i millisekunder med fire desimaler. En positiv "
    L"verdi betyr at serverklokken går foran Windows; en negativ verdi betyr at den går etter. Θ tar "
    L"hensyn til de godkjente målingene og vises også i synkroniseringsstatusen.\r\n\r\nLagre logg "
    L"eksporterer oppføringene til CSV, inkludert tidsavvik og feildetaljer. Oppføringer beholdes "
    L"ikke mellom programøkter; lagre dem før du avslutter hvis du vil beholde dem.",
    L"\r\n\r\nTIDSKÄLLA\r\nFliken Tid väljer Windows-tid eller NTP-servrar för hela programmet. NTP "
    L"korrigerar bara CalClock och ändrar aldrig Windows. Den senaste giltiga korrigeringen sparas i "
    L"minnet vid ett avbrott. NTP är standard; den automatiska uppsättningen väljer servrar efter "
    L"region och filtrerar mätningar efter fördröjning och "
    L"avvikelse.\r\n\r\nNTP-SYNKRONISERINGSLOGG\r\nFliken Tid registrerar NTP-serverförfrågningar sedan "
    L"programmet startades. Varje post innehåller datum och datorns lokala tid, server och status. OK "
    L"anger ett giltigt svar och θ dess tidsavvikelse från Windows-systemtiden. ERR anger felorsaken "
    L"och en eventuell felkod. Den sista posten i en grupp förfrågningar visar även den beräknade "
    L"tidsavvikelsen Θ när användbara mätningar finns.\r\n\r\nTidsavvikelser visas i millisekunder med "
    L"fyra decimaler. Ett positivt värde betyder att serverklockan går före Windows; ett negativt "
    L"värde betyder att den går efter. Θ tar hänsyn till de godkända mätningarna och visas även i "
    L"synkroniseringsstatusen.\r\n\r\nSpara logg exporterar posterna till CSV, inklusive tidsavvikelser "
    L"och feldetaljer. Poster sparas inte mellan programstarter; spara dem innan du avslutar om du "
    L"vill behålla dem.",
    L"\r\n\r\nAIKALÄHDE\r\nAika-välilehdellä valitaan koko sovellukselle Windowsin aika tai NTP-palvelimet. "
    L"NTP korjaa vain CalClockia eikä muuta Windowsia. Viimeisin kelvollinen korjaus säilyy muistissa "
    L"katkoksen aikana. NTP on oletus; automaattinen joukko valitsee palvelimet alueen mukaan ja "
    L"suodattaa mittaukset viiveen ja poikkeamien "
    L"perusteella.\r\n\r\nNTP-SYNKRONOINTILOKI\r\nAika-välilehti tallentaa NTP-palvelinkyselyt sovelluksen "
    L"käynnistämisestä alkaen. Jokainen merkintä sisältää päivämäärän ja tietokoneen paikallisen "
    L"ajan, palvelimen sekä tilan. OK tarkoittaa kelvollista vastausta, ja θ ilmaisee sen aikaeron "
    L"Windowsin järjestelmäaikaan. ERR kertoo epäonnistumisen syyn ja mahdollisen virhekoodin. "
    L"Kyselyryhmän viimeinen merkintä näyttää myös lasketun aikaeron Θ, jos käytettävissä on "
    L"käyttökelpoisia mittauksia.\r\n\r\nAikaerot näytetään millisekunteina neljällä desimaalilla. "
    L"Positiivinen arvo tarkoittaa, että palvelimen kello on Windowsia edellä; negatiivinen arvo "
    L"tarkoittaa, että se on jäljessä. Θ perustuu hyväksyttyihin mittauksiin ja näkyy myös "
    L"synkronoinnin tilassa.\r\n\r\nTallenna loki vie merkinnät CSV-tiedostoon, mukaan lukien aikaerot ja "
    L"virhetiedot. Merkintöjä ei säilytetä käynnistyskertojen välillä; tallenna ne ennen sulkemista, "
    L"jos haluat säilyttää ne.",
    L"\r\n\r\nTIDSKILDE\r\nFanen Tid vælger Windows-tid eller NTP-servere for hele programmet. NTP "
    L"korrigerer kun CalClock og ændrer aldrig Windows. Den seneste gyldige korrektion bevares i "
    L"hukommelsen under en afbrydelse. NTP er standard; det automatiske sæt vælger servere efter "
    L"område og filtrerer målinger efter forsinkelse og afvigelser.\r\n\r\nNTP-SYNKRONISERINGSLOG\r\nFanen "
    L"Tid registrerer NTP-serverforespørgsler siden programmets start. Hver post indeholder dato og "
    L"computerens lokale tid, server og status. OK angiver et gyldigt svar, og θ viser tidsafvigelsen "
    L"fra Windows-systemtiden. ERR angiver fejlårsagen og en eventuel fejlkode. Den sidste post i en "
    L"forespørgselsgruppe viser også den beregnede tidsafvigelse Θ, når brugbare målinger er "
    L"tilgængelige.\r\n\r\nTidsafvigelser vises i millisekunder med fire decimaler. En positiv værdi "
    L"betyder, at serveruret går foran Windows; en negativ værdi betyder, at det går bagefter. Θ "
    L"tager hensyn til de godkendte målinger og vises også i synkroniseringsstatussen.\r\n\r\nGem log "
    L"eksporterer posterne til CSV, inklusive tidsafvigelser og fejloplysninger. Poster beholdes ikke "
    L"mellem programstarter; gem dem før afslutning, hvis du vil beholde dem.",
    L"\r\n\r\nTÍMAGJAFI\r\nTímaflipinn velur Windows-tíma eða NTP-þjóna fyrir allt forritið. NTP leiðréttir "
    L"aðeins CalClock og breytir aldrei Windows. Síðasta gilda leiðrétting helst í minni meðan "
    L"sambandsleysi varir. NTP er sjálfgefið; sjálfvirka safnið velur þjóna eftir svæði og síar "
    L"mælingar eftir töf og frávikum.\r\n\r\nNTP-SAMSTILLINGARSKRÁ\r\nTímaflipinn skráir fyrirspurnir til "
    L"NTP-þjóna frá ræsingu forritsins. Hver færsla inniheldur dagsetningu og staðartíma tölvunnar, "
    L"þjón og stöðu. OK merkir gilt svar og θ tímamun þess frá kerfistíma Windows. ERR sýnir ástæðu "
    L"bilunar og villukóða ef við á. Síðasta færsla í hópi fyrirspurna sýnir einnig reiknaðan tímamun "
    L"Θ þegar nothæfar mælingar liggja fyrir.\r\n\r\nTímamunur er sýndur í millisekúndum með fjórum "
    L"aukastöfum. Jákvætt gildi merkir að klukka þjónsins er á undan Windows; neikvætt gildi merkir "
    L"að hún er á eftir. Θ tekur mið af samþykktum mælingum og birtist einnig í "
    L"samstillingarstöðu.\r\n\r\nVista annál flytur færslur út sem CSV, með tímamun og villuupplýsingum. "
    L"Færslur varðveitast ekki milli keyrslna; vistaðu þær áður en þú lokar forritinu ef þú vilt "
    L"geyma þær.",
    L"\r\n\r\nZAMAN KAYNAĞI\r\nZaman sekmesi tüm uygulama için Windows zamanını veya NTP sunucularını "
    L"seçer. NTP yalnızca CalClock'u düzeltir ve Windows'u hiçbir zaman değiştirmez. Kesinti "
    L"sırasında son geçerli düzeltme bellekte tutulur. NTP varsayılandır; otomatik küme bölgeye göre "
    L"sunucu seçer ve ölçümleri gecikme ile aykırı değerlere göre süzer.\r\n\r\nNTP EŞİTLEME "
    L"GÜNLÜĞÜ\r\nZaman sekmesi, uygulama başlatıldığından beri NTP sunucu sorgularını kaydeder. Her "
    L"kayıt tarih ve bilgisayarın yerel saatini, sunucuyu ve durumu içerir. OK geçerli bir yanıtı, θ "
    L"ise bu yanıtın Windows sistem saatinden farkını gösterir. ERR başarısızlığın nedenini ve varsa "
    L"hata kodunu belirtir. Kullanılabilir ölçümler varsa sorgu grubunun son kaydı hesaplanan zaman "
    L"farkını Θ olarak da gösterir.\r\n\r\nZaman farkları milisaniye cinsinden dört ondalık basamakla "
    L"gösterilir. Pozitif değer sunucu saatinin Windows’tan ileride, negatif değer geride olduğunu "
    L"belirtir. Θ kabul edilen ölçümleri yansıtır ve eşitleme durumunda da gösterilir.\r\n\r\nGünlüğü "
    L"kaydet, zaman farkları ve hata ayrıntıları dahil kayıtları CSV’ye aktarır. Kayıtlar uygulama "
    L"oturumları arasında korunmaz; saklamak istiyorsanız uygulamadan çıkmadan önce kaydedin."
};

const wchar_t* HELP_FULLSCREEN_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nHODINY NA MONITORU\r\nDigitální hodiny mohou vyplnit jeden či více monitorů a volitelně "
    L"zatemnit ostatní. Ctrl+A vybere v seznamu "
    L"všechny monitory. Velikost písma se udává procentem výšky monitoru; nastavit lze také písmo, "
    L"vyhlazování, barvy a odsazení. Při času UTC "
    L"lze na samostatném řádku zobrazit text UTC. Výchozí je bílý text na černém pozadí. Je-li otevřeno "
    L"Nastavení, hodiny se vždy zobrazují jen "
    L"jako malý přesouvatelný náhled se zachovaným poměrem stran; jeho poloha se ukládá. Zarovnání do mřížky "
    L"tento typ nepřesouvá ani s ním "
    L"nepočítá. Esc hodiny skryje a zatemnění odstraní i tehdy, když je aktivní Nastavení.\r\n\r\nNad "
    L"celomonitorovými hodinami i zatemněnými "
    L"monitory se kurzor po chvíli nečinnosti skryje a při pohybu myši znovu objeví. Nad zmenšeným náhledem "
    L"v režimu Nastavení zůstává viditelný.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and optionally black out the "
    L"others. Ctrl+A selects every monitor "
    L"in the list. Font size is a percentage of monitor height; font, smoothing, colors and padding are also "
    L"configurable. In UTC mode, UTC can "
    L"be shown on a separate line. The default is white text on black. While Settings is open, the clock is "
    L"always a small draggable preview that "
    L"keeps the monitor aspect ratio, and its position is saved. Grid arrangement ignores and does not move "
    L"this widget type. Esc hides the clock "
    L"and removes blackouts even when Settings is active.\r\n\r\nThe pointer hides after a short period of "
    L"inactivity over monitor clocks and "
    L"blacked-out monitors, and reappears when the mouse moves. It stays visible over the small preview "
    L"while Settings is open.",
    L"\r\n\r\nMONITORUHR\r\nDie Digitaluhr kann einen oder mehrere Monitore ausfüllen und die übrigen "
    L"optional abdunkeln. Strg+A wählt alle "
    L"Monitore der Liste. Die Schriftgröße ist ein Prozentsatz der Monitorhöhe; Schrift, Glättung, Farben "
    L"und Innenabstand sind ebenfalls "
    L"einstellbar. Im UTC-Modus kann UTC in einer eigenen Zeile stehen. Voreingestellt ist Weiß auf Schwarz. "
    L"Bei geöffneten Einstellungen "
    L"erscheint die Uhr stets als kleine verschiebbare Vorschau mit dem Seitenverhältnis des Monitors; ihre "
    L"Position wird gespeichert. Die "
    L"Rasteranordnung ignoriert diesen Widget-Typ. Esc blendet Uhr und Abdunklung auch bei aktiven "
    L"Einstellungen aus.\r\n\r\nDer Mauszeiger wird "
    L"über Monitoruhren und abgedunkelten Monitoren nach kurzer Inaktivität ausgeblendet und bei Bewegung "
    L"wieder angezeigt. Über der kleinen "
    L"Vorschau bei geöffneten Einstellungen bleibt er sichtbar.",
    L"\r\n\r\nHORLOGE SUR MONITEUR\r\nL’horloge numérique peut remplir un ou plusieurs moniteurs et "
    L"assombrir les autres. Ctrl+A sélectionne tous "
    L"les moniteurs de la liste. La taille de police est un pourcentage de la hauteur ; police, lissage, "
    L"couleurs et marge sont aussi réglables. "
    L"En mode UTC, UTC peut apparaître sur une ligne distincte. La valeur par défaut est blanc sur noir. "
    L"Tant que Paramètres est ouvert, "
    L"l’horloge reste un petit aperçu déplaçable aux proportions du moniteur, dont la position est "
    L"enregistrée. L’alignement en grille ignore ce "
    L"type de widget. Échap masque l’horloge et retire l’assombrissement même si Paramètres est "
    L"actif.\r\n\r\nLe pointeur se masque après une "
    L"courte inactivité sur les horloges plein écran et les moniteurs assombris, puis réapparaît au "
    L"mouvement de la souris. Il reste visible sur "
    L"le petit aperçu lorsque Paramètres est ouvert.",
    L"\r\n\r\nRELOJ DE MONITOR\r\nEl reloj digital puede ocupar uno o varios monitores y oscurecer los "
    L"demás. Ctrl+A selecciona todos los "
    L"monitores de la lista. El tamaño de fuente es un porcentaje de la altura; también se configuran "
    L"fuente, suavizado, colores y relleno. En "
    L"modo UTC, UTC puede mostrarse en una línea separada. El valor predeterminado es blanco sobre negro. "
    L"Mientras Configuración está abierta, el "
    L"reloj siempre es una vista previa pequeña y móvil con la proporción del monitor, y se guarda su "
    L"posición. La alineación en cuadrícula "
    L"ignora este tipo. Esc oculta el reloj y elimina el oscurecimiento incluso con Configuración "
    L"activa.\r\n\r\nEl puntero se oculta tras un "
    L"breve período de inactividad sobre los relojes de monitor y los monitores oscurecidos, y reaparece al "
    L"mover el ratón. Permanece visible "
    L"sobre la vista previa pequeña mientras Configuración está abierta.",
    L"\r\n\r\nOROLOGIO SU MONITOR\r\nL’orologio digitale può occupare uno o più monitor e oscurare gli "
    L"altri. Ctrl+A seleziona tutti i monitor "
    L"nell’elenco. La dimensione del carattere è una percentuale dell’altezza; sono configurabili anche "
    L"carattere, antialiasing, colori e "
    L"margine. In modalità UTC, UTC può apparire su una riga separata. Il valore predefinito è bianco su "
    L"nero. Con Impostazioni aperto, "
    L"l’orologio resta sempre una piccola anteprima spostabile con le proporzioni del monitor, e la "
    L"posizione viene salvata. La disposizione in "
    L"griglia ignora questo tipo. Esc nasconde orologio e oscuramento anche con Impostazioni "
    L"attivo.\r\n\r\nIl puntatore si nasconde dopo una "
    L"breve inattività sugli orologi a schermo intero e sui monitor oscurati, e riappare muovendo il mouse. "
    L"Rimane visibile sulla piccola "
    L"anteprima quando Impostazioni è aperto.",
    L"\r\n\r\nZEGAR NA MONITORZE\r\nZegar cyfrowy może zająć jeden lub kilka monitorów i wygasić pozostałe. "
    L"Ctrl+A zaznacza wszystkie monitory na "
    L"liście. Rozmiar czcionki jest procentem wysokości monitora; można też ustawić czcionkę, wygładzanie, "
    L"kolory i odstęp. W trybie UTC napis "
    L"UTC można wyświetlić w osobnym wierszu. Domyślne są białe cyfry na czarnym tle. Gdy Ustawienia są "
    L"otwarte, zegar zawsze jest małym, "
    L"przesuwanym podglądem o proporcjach monitora, a jego położenie jest zapisywane. Układanie w siatce "
    L"pomija ten typ. Esc ukrywa zegar i "
    L"wygaszenie również przy aktywnych Ustawieniach.\r\n\r\nWskaźnik znika po krótkiej bezczynności nad "
    L"zegarami pełnoekranowymi i zaciemnionymi "
    L"monitorami, a pojawia się po poruszeniu myszą. Nad małym podglądem przy otwartych Ustawieniach "
    L"pozostaje widoczny.",
    L"\r\n\r\nHODINY NA MONITORE\r\nDigitálne hodiny môžu vyplniť jeden alebo viac monitorov a stmaviť "
    L"ostatné. Ctrl+A vyberie všetky monitory v "
    L"zozname. Veľkosť písma je percentom výšky monitora; nastaviť možno aj písmo, vyhladzovanie, farby a "
    L"odsadenie. V režime UTC možno zobraziť "
    L"text UTC na samostatnom riadku. Predvolené je biele písmo na čiernom pozadí. Pri otvorenom Nastavení "
    L"sú hodiny vždy iba malým presúvateľným "
    L"náhľadom s pomerom strán monitora a jeho poloha sa ukladá. Zarovnanie do mriežky tento typ ignoruje. "
    L"Esc skryje hodiny aj stmavenie aj pri "
    L"aktívnom Nastavení.\r\n\r\nNad celomonitorovými hodinami aj zatemnenými monitormi sa kurzor po chvíli "
    L"nečinnosti skryje a pri pohybe myši "
    L"sa znovu objaví. Nad zmenšeným náhľadom v režime Nastavenia zostáva viditeľný.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and optionally black out the "
    L"others. Ctrl+A selects every monitor "
    L"in the list. Font size is a percentage of monitor height; font, smoothing, colours and padding are "
    L"also configurable. In UTC mode, UTC can "
    L"be shown on a separate line. The default is white text on black. While Settings is open, the clock is "
    L"always a small draggable preview that "
    L"keeps the monitor aspect ratio, and its position is saved. Grid arrangement ignores and does not move "
    L"this widget type. Esc hides the clock "
    L"and removes blackouts even when Settings is active.\r\n\r\nThe pointer hides after a short period of "
    L"inactivity over monitor clocks and "
    L"blacked-out monitors, and reappears when the mouse moves. It stays visible over the small preview "
    L"while Settings is open.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and optionally black out the "
    L"others. Ctrl+A selects every monitor "
    L"in the list. Font size is a percentage of monitor height; font, smoothing, colours and padding are "
    L"also configurable. In UTC mode, UTC can "
    L"be shown on a separate line. The default is white text on black. While Settings is open, the clock is "
    L"always a small draggable preview that "
    L"keeps the monitor aspect ratio, and its position is saved. Grid arrangement ignores and does not move "
    L"this widget type. Esc hides the clock "
    L"and removes blackouts even when Settings is active.\r\n\r\nThe pointer hides after a short period of "
    L"inactivity over monitor clocks and "
    L"blacked-out monitors, and reappears when the mouse moves. It stays visible over the small preview "
    L"while Settings is open.",
    L"\r\n\r\nRELÓGIO NO MONITOR\r\nO relógio digital pode preencher um ou vários monitores e escurecer os "
    L"restantes. A letra é uma percentagem "
    L"da altura do monitor e também se configuram tipo de letra, suavização, cores e margem. Com as "
    L"Definições abertas é sempre uma pequena "
    L"pré-visualização arrastável. Esc oculta o relógio e remove o escurecimento.\r\n\r\nO ponteiro "
    L"oculta-se após um curto período de "
    L"inatividade sobre relógios de monitor e monitores escurecidos, e reaparece ao mover o rato. Permanece "
    L"visível sobre a pequena "
    L"pré-visualização com as Definições abertas.",
    L"\r\n\r\nSKJERMKLOKKE\r\nDen digitale klokken kan fylle én eller flere skjermer og mørklegge resten. "
    L"Skriftstørrelsen er en prosentandel av "
    L"skjermhøyden; skrift, utjevning, farger og luft kan også angis. Når Innstillinger er åpent, vises "
    L"alltid en liten, flyttbar "
    L"forhåndsvisning. Esc skjuler klokken og fjerner mørklegging.\r\n\r\nPekeren skjules etter kort "
    L"inaktivitet over skjermklokker og mørklagte "
    L"skjermer, og vises igjen når musen beveges. Den forblir synlig over den lille forhåndsvisningen når "
    L"Innstillinger er åpent.",
    L"\r\n\r\nSKÄRMKLOCKA\r\nDen digitala klockan kan fylla en eller flera bildskärmar och släcka de övriga. "
    L"Teckenstorleken är en procentandel "
    L"av bildskärmshöjden; teckensnitt, utjämning, färger och utfyllnad kan också ställas in. När "
    L"Inställningar är öppet visas alltid en liten "
    L"flyttbar förhandsvisning. Esc döljer klockan och tar bort släckningen.\r\n\r\nPekaren döljs efter en "
    L"kort stunds inaktivitet över "
    L"skärmklockor och mörklagda skärmar och visas igen när musen rör sig. Den förblir synlig över den lilla "
    L"förhandsvisningen när Inställningar "
    L"är öppet.",
    L"\r\n\r\nNÄYTTÖKELLO\r\nDigitaalinen kello voi täyttää yhden tai useita näyttöjä ja pimentää muut. "
    L"Fonttikoko on prosenttiosuus näytön "
    L"korkeudesta; myös fontti, pehmennys, värit ja täyttö voidaan määrittää. Kun Asetukset on avoinna, "
    L"näytetään aina pieni siirrettävä "
    L"esikatselu. Esc piilottaa kellon ja poistaa pimennyksen.\r\n\r\nOsoitin piilotetaan lyhyen "
    L"käyttämättömyyden jälkeen näyttökellojen ja "
    L"pimennettyjen näyttöjen päällä. Se palaa näkyviin hiirtä liikuttamalla. Pienen esikatselun päällä "
    L"osoitin pysyy näkyvissä Asetusten ollessa "
    L"auki.",
    L"\r\n\r\nSKÆRMUR\r\nDet digitale ur kan fylde en eller flere skærme og mørklægge de øvrige. "
    L"Skriftstørrelsen er en procentdel af "
    L"skærmhøjden; skrifttype, udjævning, farver og luft kan også indstilles. Når Indstillinger er åbent, "
    L"vises altid en lille flytbar "
    L"forhåndsvisning. Esc skjuler uret og fjerner mørklægningen.\r\n\r\nMarkøren skjules efter kort "
    L"inaktivitet over skærmure og mørklagte "
    L"skærme og vises igen, når musen bevæges. Den forbliver synlig over den lille forhåndsvisning, når "
    L"Indstillinger er åbent.",
    L"\r\n\r\nSKJÁKUKKA\r\nStafræna klukkan getur fyllt einn eða fleiri skjái og myrkvað hina. Leturstærð er "
    L"hlutfall af hæð skjásins; einnig má "
    L"stilla letur, jöfnun, liti og bil. Þegar Stillingar eru opnar birtist alltaf lítil færanleg forskoðun. "
    L"Esc felur klukkuna og fjarlægir "
    L"myrkvun.\r\n\r\nBendillinn felst eftir stutt aðgerðaleysi yfir skjáklukkum og myrkvuðum skjám og "
    L"birtist aftur þegar músin hreyfist. Hann "
    L"er sýnilegur yfir litlu forskoðuninni meðan Stillingar eru opnar.",
    L"\r\n\r\nMONİTÖR SAATİ\r\nDijital saat bir veya daha fazla monitörü doldurabilir ve diğerlerini "
    L"karartabilir. Yazı tipi boyutu monitör "
    L"yüksekliğinin yüzdesidir; yazı tipi, kenar yumuşatma, renkler ve dolgu da ayarlanabilir. Ayarlar "
    L"açıkken her zaman küçük, sürüklenebilir "
    L"bir önizleme gösterilir. Esc saati gizler ve karartmayı kaldırır.\r\n\r\nİşaretçi, monitör saatleri ve "
    L"karartılmış monitörler üzerinde kısa "
    L"bir hareketsizlikten sonra gizlenir ve fare hareket edince yeniden görünür. Ayarlar açıkken küçük "
    L"önizleme üzerinde görünür kalır."
};

const wchar_t* ABOUT_TEXT[LANG_COUNT] = {
    L"Hodiny a kalendáře\r\n\r\nNativní Win32 aplikace pro až 32 samostatně nastavených plovoucích hodin a "
    L"kalendářů. Ručičkový ciferník používá "
    L"systémový ClockWndMain.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for up to 32 independently configured floating "
    L"clocks and calendars. The analog face "
    L"uses the system ClockWndMain.",
    L"Uhren und Kalender\r\n\r\nNative Win32-Anwendung für bis zu 32 unabhängig konfigurierte schwebende "
    L"Uhren und Kalender. Das Zifferblatt "
    L"verwendet ClockWndMain.",
    L"Horloges et calendriers\r\n\r\nApplication Win32 native pour plusieurs horloges et calendriers "
    L"flottants configurés séparément. Le cadran "
    L"utilise ClockWndMain.",
    L"Relojes y calendarios\r\n\r\nAplicación Win32 nativa para varios relojes y calendarios flotantes "
    L"configurados por separado. La esfera usa "
    L"ClockWndMain.",
    L"Orologi e calendari\r\n\r\nApplicazione Win32 nativa per più orologi e calendari mobili configurati "
    L"separatamente. Il quadrante usa "
    L"ClockWndMain.",
    L"Zegary i kalendarze\r\n\r\nNatywna aplikacja Win32 obsługująca wiele niezależnie skonfigurowanych "
    L"zegarów i kalendarzy. Tarcza używa "
    L"ClockWndMain.",
    L"Hodiny a kalendáre\r\n\r\nNatívna aplikácia Win32 pre najviac 32 samostatne nastavených plávajúcich "
    L"hodín a kalendárov. Ciferník používa "
    L"ClockWndMain.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for up to 32 independently configured floating "
    L"clocks and calendars. The analog face "
    L"uses the system ClockWndMain.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for up to 32 independently configured floating "
    L"clocks and calendars. The analog face "
    L"uses the system ClockWndMain.",
    L"Relógios e calendários\r\n\r\nAplicação Win32 nativa para até 32 relógios e calendários "
    L"flutuantes configurados independentemente. O mostrador analógico utiliza o ClockWndMain do sistema.",
    L"Klokker og kalendere\r\n\r\nEt innebygd Win32-program for opptil 32 flytende klokker "
    L"og kalendere med separate innstillinger. Den analoge urskiven bruker systemets ClockWndMain.",
    L"Klockor och kalendrar\r\n\r\nEtt inbyggt Win32-program för upp till 32 flytande klockor "
    L"och kalendrar med separata inställningar. Den analoga urtavlan använder systemets ClockWndMain.",
    L"Kellot ja kalenterit\r\n\r\nNatiivi Win32-sovellus enintään 32 erikseen määritettävälle "
    L"kelluvalle kellolle ja kalenterille. Analoginen kellotaulu käyttää järjestelmän ClockWndMain-ohjainta.",
    L"Ure og kalendere\r\n\r\nEt indbygget Win32-program til op til 32 flydende ure og kalendere med "
    L"separate indstillinger. Den analoge urskive "
    L"bruger systemets ClockWndMain.",
    L"Klukkur og dagatöl\r\n\r\nInnbyggt Win32-forrit fyrir allt að 32 fljótandi klukkna og dagatala með "
    L"sjálfstæðum stillingum. Skífuklukkan notar "
    L"ClockWndMain kerfisins.",
    L"Saatler ve takvimler\r\n\r\nBağımsız olarak yapılandırılan en fazla 32 kayan saat ve takvim için yerel "
    L"bir Win32 uygulaması. Analog kadran "
    L"sistem ClockWndMain denetimini kullanır."
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
