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
 * Last modified for version 1.6.0.0
 */

#include "Localization.h"
#include <cwchar>

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
        L"Ausgewählte Widgets entfernen?",
        L"Mindestens ein Widget muss erhalten bleiben.",
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
        L"Zéro initial :",
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
        L"Supprimer les widgets sélectionnés ?",
        L"Au moins un widget doit rester.",
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
        L"¿Quitar los widgets seleccionados?",
        L"Debe quedar al menos un widget.",
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
        L"Rimuovere i widget selezionati?",
        L"Deve restare almeno un widget.",
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
        L"Usunąć wybrane widżety?",
        L"Musi pozostać co najmniej jeden widżet.",
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
        L"Odobrať vybrané widgety?",
        L"Musí zostať aspoň jeden widget.",
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
        L"Text colour…",
        L"Background colour…",
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
        L"Text colour…",
        L"Background colour…",
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
    }, {
        L"Kellad ja kalendrid",
        L"Sätted",
        L"Lisa",
        L"Eemalda…",
        L"Dubleeri",
        L"Üldine",
        L"Ilme",
        L"Äratus",
        L"Nimi:",
        L"Tüüp:",
        L"Nähtav",
        L"Alati pealmine",
        L"Sekundid",
        L"UTC aeg",
        L"Ajavöönd:",
        L"Nihe [-]HH:mm:ss.ff:",
        L"Suurus:",
        L"Läbipaistmatus:",
        L"Fondi suurus:",
        L"Algusnull:",
        L"Läbipaistev taust",
        L"Teksti värv…",
        L"Taustavärv…",
        L"Nädalanumbrid",
        L"Pühapäev esimesena",
        L"Äratus lubatud",
        L"Äratuse aeg:",
        L"Käivita fail või käsk",
        L"Korda heli pidevalt",
        L"Sirvi…",
        L"Keel:",
        L"Keela kujundused",
        L"Salvesta",
        L"Rakenda",
        L"Loobu",
        L"Kuva kõik",
        L"Peida kõik",
        L"Peata äratus",
        L"Spikker",
        L"Teave",
        L"Välju",
        L"Analoogkell",
        L"Digitaalkell",
        L"Kalender",
        L"Kalender ja kell",
        L"Sisestage nihe kujul [-]HH:mm:ss.ff.",
        L"Sisestage sobiv aeg vahemikus 0:00–23:59.",
        L"Kas eemaldada valitud vidinad?",
        L"Alles peab jääma vähemalt üks vidin.",
        L"Sule"
    }, {
        L"Cloig agus féilirí",
        L"Socruithe",
        L"Cuir leis",
        L"Bain…",
        L"Dúblaigh",
        L"Ginearálta",
        L"Cuma",
        L"Aláram",
        L"Ainm:",
        L"Cineál:",
        L"Infheicthe",
        L"Ar barr i gcónaí",
        L"Soicindí",
        L"Am UTC",
        L"Crios ama:",
        L"Fritháireamh [-]HH:mm:ss.ff:",
        L"Méid:",
        L"Teimhneacht:",
        L"Clómhéid:",
        L"Nialas tosaigh:",
        L"Cúlra trédhearcach",
        L"Dath an téacs…",
        L"Dath an chúlra…",
        L"Uimhreacha seachtainí",
        L"Dé Domhnaigh ar dtús",
        L"Aláram cumasaithe",
        L"Am an aláraim:",
        L"Rith comhad nó ordú",
        L"Athsheinn an fhuaim go leanúnach",
        L"Brabhsáil…",
        L"Teanga:",
        L"Díchumasaigh téamaí",
        L"Sábháil",
        L"Cuir i bhfeidhm",
        L"Cealaigh",
        L"Taispeáin uile",
        L"Folaigh uile",
        L"Stop an t-aláram",
        L"Cabhair",
        L"Maidir leis",
        L"Scoir",
        L"Clog analógach",
        L"Clog digiteach",
        L"Féilire",
        L"Féilire agus clog",
        L"Iontráil an fritháireamh san fhormáid [-]HH:mm:ss.ff.",
        L"Iontráil am bailí idir 0:00 agus 23:59.",
        L"An bhfuil fonn ort na giuirléidí roghnaithe a bhaint?",
        L"Ní mór giuirléid amháin ar a laghad a fhágáil.",
        L"Dún"
    }, {
        L"Laikrodžiai ir kalendoriai",
        L"Parametrai",
        L"Įtraukti",
        L"Pašalinti…",
        L"Kurti dublikatą",
        L"Bendra",
        L"Išvaizda",
        L"Žadintuvas",
        L"Pavadinimas:",
        L"Tipas:",
        L"Matomas",
        L"Visada viršuje",
        L"Sekundės",
        L"UTC laikas",
        L"Laiko juosta:",
        L"Poslinkis [-]HH:mm:ss.ff:",
        L"Dydis:",
        L"Nepermatomumas:",
        L"Šrifto dydis:",
        L"Pradinis nulis:",
        L"Permatomas fonas",
        L"Teksto spalva…",
        L"Fono spalva…",
        L"Savaičių numeriai",
        L"Sekmadienis pirmas",
        L"Žadintuvas įjungtas",
        L"Žadintuvo laikas:",
        L"Vykdyti failą arba komandą",
        L"Kartoti garsą",
        L"Naršyti…",
        L"Kalba:",
        L"Išjungti temas",
        L"Įrašyti",
        L"Taikyti",
        L"Atšaukti",
        L"Rodyti visus",
        L"Slėpti visus",
        L"Stabdyti žadintuvą",
        L"Žinynas",
        L"Apie",
        L"Išeiti",
        L"Analoginis laikrodis",
        L"Skaitmeninis laikrodis",
        L"Kalendorius",
        L"Kalendorius su laikrodžiu",
        L"Įveskite poslinkį formatu [-]HH:mm:ss.ff.",
        L"Įveskite tinkamą laiką nuo 0:00 iki 23:59.",
        L"Pašalinti pasirinktus valdiklius?",
        L"Turi likti bent vienas valdiklis.",
        L"Uždaryti"
    }, {
        L"Pulksteņi un kalendāri",
        L"Iestatījumi",
        L"Pievienot",
        L"Noņemt…",
        L"Dublēt",
        L"Vispārīgi",
        L"Izskats",
        L"Modinātājs",
        L"Nosaukums:",
        L"Tips:",
        L"Redzams",
        L"Vienmēr virspusē",
        L"Sekundes",
        L"UTC laiks",
        L"Laika josla:",
        L"Nobīde [-]HH:mm:ss.ff:",
        L"Lielums:",
        L"Necaurspīdīgums:",
        L"Fonta lielums:",
        L"Sākuma nulle:",
        L"Caurspīdīgs fons",
        L"Teksta krāsa…",
        L"Fona krāsa…",
        L"Nedēļu numuri",
        L"Svētdiena pirmā",
        L"Modinātājs ieslēgts",
        L"Modinātāja laiks:",
        L"Palaist failu vai komandu",
        L"Nepārtraukti atkārtot skaņu",
        L"Pārlūkot…",
        L"Valoda:",
        L"Atspējot dizainus",
        L"Saglabāt",
        L"Lietot",
        L"Atcelt",
        L"Rādīt visus",
        L"Paslēpt visus",
        L"Apturēt modinātāju",
        L"Palīdzība",
        L"Par programmu",
        L"Iziet",
        L"Analogais pulkstenis",
        L"Digitālais pulkstenis",
        L"Kalendārs",
        L"Kalendārs ar pulksteni",
        L"Ievadiet nobīdi formātā [-]HH:mm:ss.ff.",
        L"Ievadiet derīgu laiku no 0:00 līdz 23:59.",
        L"Vai noņemt atlasītos logrīkus?",
        L"Jāpaliek vismaz vienam logrīkam.",
        L"Aizvērt"
    }, {
        L"Órák és naptárak",
        L"Beállítások",
        L"Hozzáadás",
        L"Eltávolítás…",
        L"Duplikálás",
        L"Általános",
        L"Megjelenés",
        L"Ébresztés",
        L"Név:",
        L"Típus:",
        L"Látható",
        L"Mindig felül",
        L"Másodpercek",
        L"UTC-idő",
        L"Időzóna:",
        L"Eltolás [-]HH:mm:ss.ff:",
        L"Méret:",
        L"Átlátszatlanság:",
        L"Betűméret:",
        L"Vezető nulla:",
        L"Átlátszó háttér",
        L"Szövegszín…",
        L"Háttérszín…",
        L"Hétszámok",
        L"Vasárnap az első nap",
        L"Ébresztés engedélyezve",
        L"Ébresztés ideje:",
        L"Fájl vagy parancs futtatása",
        L"Hang folyamatos ismétlése",
        L"Tallózás…",
        L"Nyelv:",
        L"Témák letiltása",
        L"Mentés",
        L"Alkalmaz",
        L"Mégse",
        L"Összes megjelenítése",
        L"Összes elrejtése",
        L"Ébresztés leállítása",
        L"Súgó",
        L"Névjegy",
        L"Kilépés",
        L"Analóg óra",
        L"Digitális óra",
        L"Naptár",
        L"Naptár órával",
        L"Adja meg az eltolást [-]HH:mm:ss.ff formátumban.",
        L"Adjon meg érvényes időpontot 0:00 és 23:59 között.",
        L"Eltávolítja a kijelölt minialkalmazásokat?",
        L"Legalább egy minialkalmazásnak maradnia kell.",
        L"Bezárás"
    }, {
        L"Arloġġi u kalendarji",
        L"Settings",
        L"Żid",
        L"Neħħi…",
        L"Idduplika",
        L"Ġenerali",
        L"Dehra",
        L"Allarm",
        L"Isem:",
        L"Tip:",
        L"Viżibbli",
        L"Dejjem fuq nett",
        L"Sekondi",
        L"Ħin UTC",
        L"Żona tal-ħin:",
        L"Kumpens [-]HH:mm:ss.ff:",
        L"Daqs:",
        L"Opaċità:",
        L"Daqs tal-font:",
        L"Żero fil-bidu:",
        L"Sfond trasparenti",
        L"Kulur tat-test…",
        L"Kulur tal-isfond…",
        L"Numri tal-ġimgħat",
        L"Il-Ħadd l-ewwel",
        L"Allarm attivat",
        L"Ħin tal-allarm:",
        L"Ħaddem fajl jew kmand",
        L"Irrepeti l-awdjo kontinwament",
        L"Ibbrawżja…",
        L"Lingwa:",
        L"Iddiżattiva t-temi",
        L"Issejvja",
        L"Applika",
        L"Ikkanċella",
        L"Uri kollox",
        L"Aħbi kollox",
        L"Waqqaf l-allarm",
        L"Għajnuna",
        L"Dwar",
        L"Oħroġ",
        L"Arloġġ analogu",
        L"Arloġġ diġitali",
        L"Kalendarju",
        L"Kalendarju bl-arloġġ",
        L"Daħħal il-kumpens fil-format [-]HH:mm:ss.ff.",
        L"Daħħal ħin validu minn 0:00 sa 23:59.",
        L"Trid tneħħi l-widgets magħżula?",
        L"Irid jibqa’ mill-inqas widget wieħed.",
        L"Agħlaq"
    }, {
        L"Klokken en kalenders",
        L"Instellingen",
        L"Toevoegen",
        L"Verwijderen…",
        L"Dupliceren",
        L"Algemeen",
        L"Vormgeving",
        L"Alarm",
        L"Naam:",
        L"Type:",
        L"Zichtbaar",
        L"Altijd op voorgrond",
        L"Seconden",
        L"UTC-tijd",
        L"Tijdzone:",
        L"Verschuiving [-]HH:mm:ss.ff:",
        L"Grootte:",
        L"Dekking:",
        L"Tekengrootte:",
        L"Voorloopnul:",
        L"Transparante achtergrond",
        L"Tekstkleur…",
        L"Achtergrondkleur…",
        L"Weeknummers",
        L"Zondag eerst",
        L"Alarm ingeschakeld",
        L"Alarmtijd:",
        L"Bestand of opdracht uitvoeren",
        L"Geluid blijven herhalen",
        L"Bladeren…",
        L"Taal:",
        L"Thema’s uitschakelen",
        L"Opslaan",
        L"Toepassen",
        L"Annuleren",
        L"Alles weergeven",
        L"Alles verbergen",
        L"Alarm stoppen",
        L"Help",
        L"Info",
        L"Afsluiten",
        L"Analoge klok",
        L"Digitale klok",
        L"Kalender",
        L"Kalender met klok",
        L"Voer de verschuiving in als [-]HH:mm:ss.ff.",
        L"Voer een geldige tijd tussen 0:00 en 23:59 in.",
        L"De geselecteerde widgets verwijderen?",
        L"Er moet minstens één widget overblijven.",
        L"Sluiten"
    }, {
        L"Ceasuri și calendare",
        L"Setări",
        L"Adăugare",
        L"Eliminare…",
        L"Dublare",
        L"General",
        L"Aspect",
        L"Alarmă",
        L"Nume:",
        L"Tip:",
        L"Vizibil",
        L"Întotdeauna deasupra",
        L"Secunde",
        L"Ora UTC",
        L"Fus orar:",
        L"Decalaj [-]HH:mm:ss.ff:",
        L"Dimensiune:",
        L"Opacitate:",
        L"Dimensiune font:",
        L"Zero inițial:",
        L"Fundal transparent",
        L"Culoare text…",
        L"Culoare fundal…",
        L"Numere săptămâni",
        L"Duminica prima zi",
        L"Alarmă activată",
        L"Ora alarmei:",
        L"Executare fișier sau comandă",
        L"Repetare continuă a sunetului",
        L"Răsfoire…",
        L"Limbă:",
        L"Dezactivare teme",
        L"Salvare",
        L"Se aplică",
        L"Anulare",
        L"Afișare totală",
        L"Ascundere totală",
        L"Oprire alarmă",
        L"Ajutor",
        L"Despre",
        L"Ieșire",
        L"Ceas analogic",
        L"Ceas digital",
        L"Calendar",
        L"Calendar cu ceas",
        L"Introduceți decalajul în formatul [-]HH:mm:ss.ff.",
        L"Introduceți o oră validă între 0:00 și 23:59.",
        L"Eliminați widgeturile selectate?",
        L"Trebuie să rămână cel puțin un widget.",
        L"Închidere"
    }, {
        L"Ρολόγια και ημερολόγια",
        L"Ρυθμίσεις",
        L"Προσθήκη",
        L"Κατάργηση…",
        L"Δημιουργία αντιγράφου",
        L"Γενικά",
        L"Εμφάνιση",
        L"Ξυπνητήρι",
        L"Όνομα:",
        L"Τύπος:",
        L"Ορατό",
        L"Πάντα σε πρώτο πλάνο",
        L"Δευτερόλεπτα",
        L"Ώρα UTC",
        L"Ζώνη ώρας:",
        L"Μετατόπιση [-]HH:mm:ss.ff:",
        L"Μέγεθος:",
        L"Αδιαφάνεια:",
        L"Μέγεθος κειμένου:",
        L"Αρχικό μηδενικό:",
        L"Διαφανές φόντο",
        L"Χρώμα κειμένου…",
        L"Χρώμα φόντου…",
        L"Αριθμοί εβδομάδων",
        L"Κυριακή πρώτη ημέρα",
        L"Ξυπνητήρι ενεργό",
        L"Ώρα αφύπνισης:",
        L"Εκτέλεση αρχείου ή εντολής",
        L"Συνεχής επανάληψη ήχου",
        L"Αναζήτηση…",
        L"Γλώσσα:",
        L"Χωρίς θέματα",
        L"Αποθήκευση",
        L"Εφαρμογή",
        L"Άκυρο",
        L"Εμφάνιση όλων",
        L"Απόκρυψη όλων",
        L"Διακοπή αφύπνισης",
        L"Βοήθεια",
        L"Πληροφορίες",
        L"Έξοδος",
        L"Αναλογικό ρολόι",
        L"Ψηφιακό ρολόι",
        L"Ημερολόγιο",
        L"Ημερολόγιο με ρολόι",
        L"Εισαγάγετε τη μετατόπιση στη μορφή [-]HH:mm:ss.ff.",
        L"Εισαγάγετε έγκυρη ώρα από 0:00 έως 23:59.",
        L"Να καταργηθούν τα επιλεγμένα γραφικά στοιχεία;",
        L"Πρέπει να παραμείνει τουλάχιστον ένα γραφικό στοιχείο.",
        L"Κλείσιμο"
    }, {
        L"Satovi i kalendari",
        L"Postavke",
        L"Dodaj",
        L"Ukloni…",
        L"Dupliciraj",
        L"Općenito",
        L"Izgled",
        L"Alarm",
        L"Naziv:",
        L"Vrsta:",
        L"Vidljivo",
        L"Uvijek na vrhu",
        L"Sekunde",
        L"Vrijeme UTC",
        L"Vremenska zona:",
        L"Pomak [-]HH:mm:ss.ff:",
        L"Veličina:",
        L"Neprozirnost:",
        L"Veličina fonta:",
        L"Početna nula:",
        L"Prozirna pozadina",
        L"Boja teksta…",
        L"Boja pozadine…",
        L"Brojevi sedmica",
        L"Nedjelja kao prvi dan",
        L"Alarm uključen",
        L"Vrijeme alarma:",
        L"Pokreni datoteku ili naredbu",
        L"Ponavljaj zvuk",
        L"Pregledaj…",
        L"Jezik:",
        L"Onemogući teme",
        L"Sačuvaj",
        L"Primijeni",
        L"Otkaži",
        L"Prikaži sve",
        L"Sakrij sve",
        L"Zaustavi alarm",
        L"Pomoć",
        L"O programu",
        L"Izlaz",
        L"Analogni sat",
        L"Digitalni sat",
        L"Kalendar",
        L"Kalendar sa satom",
        L"Unesite pomak u obliku [-]HH:mm:ss.ff.",
        L"Unesite valjano vrijeme od 0:00 do 23:59.",
        L"Ukloniti odabrane vidžete?",
        L"Mora ostati barem jedan vidžet.",
        L"Zatvori"
    }, {
        L"Satovi i kalendari",
        L"Postavke",
        L"Dodaj",
        L"Ukloni…",
        L"Dupliciraj",
        L"Općenito",
        L"Izgled",
        L"Alarm",
        L"Naziv:",
        L"Vrsta:",
        L"Vidljivo",
        L"Uvijek na vrhu",
        L"Sekunde",
        L"Vrijeme UTC",
        L"Vremenska zona:",
        L"Pomak [-]HH:mm:ss.ff:",
        L"Veličina:",
        L"Neprozirnost:",
        L"Veličina fonta:",
        L"Početna nula:",
        L"Prozirna pozadina",
        L"Boja teksta…",
        L"Boja pozadine…",
        L"Brojevi tjedana",
        L"Nedjelja kao prvi dan",
        L"Alarm uključen",
        L"Vrijeme alarma:",
        L"Pokreni datoteku ili naredbu",
        L"Ponavljaj zvuk",
        L"Pregledaj…",
        L"Jezik:",
        L"Onemogući teme",
        L"Spremi",
        L"Primijeni",
        L"Odustani",
        L"Prikaži sve",
        L"Sakrij sve",
        L"Zaustavi alarm",
        L"Pomoć",
        L"O programu",
        L"Izlaz",
        L"Analogni sat",
        L"Digitalni sat",
        L"Kalendar",
        L"Kalendar sa satom",
        L"Unesite pomak u obliku [-]HH:mm:ss.ff.",
        L"Unesite valjano vrijeme od 0:00 do 23:59.",
        L"Ukloniti odabrane widgete?",
        L"Mora ostati barem jedan widget.",
        L"Zatvori"
    }, {
        L"Ure in koledarji",
        L"Nastavitve",
        L"Dodaj",
        L"Odstrani…",
        L"Podvoji",
        L"Splošno",
        L"Videz",
        L"Budilka",
        L"Ime:",
        L"Vrsta:",
        L"Vidno",
        L"Vedno na vrhu",
        L"Sekunde",
        L"Čas UTC",
        L"Časovni pas:",
        L"Odmik [-]HH:mm:ss.ff:",
        L"Velikost:",
        L"Neprosojnost:",
        L"Velikost pisave:",
        L"Vodilna ničla:",
        L"Prosojno ozadje",
        L"Barva besedila…",
        L"Barva ozadja…",
        L"Številke tednov",
        L"Nedelja kot prvi dan",
        L"Budilka vključena",
        L"Čas budilke:",
        L"Zaženi datoteko ali ukaz",
        L"Ponavljaj zvok",
        L"Prebrskaj…",
        L"Jezik:",
        L"Onemogoči teme",
        L"Shrani",
        L"Uporabi",
        L"Prekliči",
        L"Pokaži vse",
        L"Skrij vse",
        L"Ustavi budilko",
        L"Pomoč",
        L"O programu",
        L"Izhod",
        L"Analogna ura",
        L"Digitalna ura",
        L"Koledar",
        L"Koledar z uro",
        L"Vnesite odmik v obliki [-]HH:mm:ss.ff.",
        L"Vnesite veljaven čas od 0:00 do 23:59.",
        L"Odstranim izbrane gradnike?",
        L"Ostati mora vsaj en gradnik.",
        L"Zapri"
    }, {
        L"Satovi i kalendari",
        L"Podešavanja",
        L"Dodaj",
        L"Ukloni…",
        L"Dupliraj",
        L"Opšte",
        L"Izgled",
        L"Alarm",
        L"Naziv:",
        L"Vrsta:",
        L"Vidljivo",
        L"Uvijek na vrhu",
        L"Sekunde",
        L"Vrijeme UTC",
        L"Vremenska zona:",
        L"Pomak [-]HH:mm:ss.ff:",
        L"Veličina:",
        L"Neprozirnost:",
        L"Veličina fonta:",
        L"Vodeća nula:",
        L"Providna pozadina",
        L"Boja teksta…",
        L"Boja pozadine…",
        L"Brojevi nedjelja",
        L"Nedjelja kao prvi dan",
        L"Alarm uključen",
        L"Vrijeme alarma:",
        L"Pokreni datoteku ili naredbu",
        L"Ponavljaj zvuk",
        L"Pregledaj…",
        L"Jezik:",
        L"Onemogući teme",
        L"Sačuvaj",
        L"Primijeni",
        L"Otkaži",
        L"Prikaži sve",
        L"Sakrij sve",
        L"Zaustavi alarm",
        L"Pomoć",
        L"O programu",
        L"Izlaz",
        L"Analogni sat",
        L"Digitalni sat",
        L"Kalendar",
        L"Kalendar sa satom",
        L"Unesite pomak u obliku [-]HH:mm:ss.ff.",
        L"Unesite ispravno vrijeme od 0:00 do 23:59.",
        L"Ukloniti izabrane vidžete?",
        L"Mora ostati bar jedan vidžet.",
        L"Zatvori"
    }, {
        L"Гадзіннікі і календары",
        L"Налады",
        L"Дадаць",
        L"Выдаліць…",
        L"Дубляваць",
        L"Агульныя",
        L"Выгляд",
        L"Будзільнік",
        L"Назва:",
        L"Тып:",
        L"Паказваць",
        L"Заўсёды зверху",
        L"Секунды",
        L"Час UTC",
        L"Часавы пояс:",
        L"Зрушэнне [-]HH:mm:ss.ff:",
        L"Памер:",
        L"Непразрыстасць:",
        L"Памер шрыфту:",
        L"Пачатковы нуль:",
        L"Празрысты фон",
        L"Колер тэксту…",
        L"Колер фону…",
        L"Нумары тыдняў",
        L"Нядзеля — першы дзень",
        L"Будзільнік уключаны",
        L"Час будзільніка:",
        L"Запускаць файл або каманду",
        L"Паўтараць гук",
        L"Агляд…",
        L"Мова:",
        L"Адключыць тэмы",
        L"Захаваць",
        L"Ужыць",
        L"Скасаваць",
        L"Паказаць усё",
        L"Схаваць усё",
        L"Спыніць будзільнік",
        L"Даведка",
        L"Пра праграму",
        L"Выйсці",
        L"Аналагавы гадзіннік",
        L"Лічбавы гадзіннік",
        L"Каляндар",
        L"Каляндар з гадзіннікам",
        L"Увядзіце зрушэнне ў фармаце [-]HH:mm:ss.ff.",
        L"Увядзіце карэктны час ад 0:00 да 23:59.",
        L"Выдаліць выбраныя віджэты?",
        L"Павінен застацца прынамсі адзін віджэт.",
        L"Закрыць"
    }, {
        L"Часовници и календари",
        L"Настройки",
        L"Добави",
        L"Премахни…",
        L"Дублирай",
        L"Общи",
        L"Изглед",
        L"Аларма",
        L"Име:",
        L"Тип:",
        L"Видим",
        L"Винаги отгоре",
        L"Секунди",
        L"Час UTC",
        L"Часова зона:",
        L"Отместване [-]HH:mm:ss.ff:",
        L"Размер:",
        L"Непрозрачност:",
        L"Размер на шрифта:",
        L"Водеща нула:",
        L"Прозрачен фон",
        L"Цвят на текста…",
        L"Цвят на фона…",
        L"Номера на седмиците",
        L"Неделя като първи ден",
        L"Алармата е включена",
        L"Час на алармата:",
        L"Изпълни файл или команда",
        L"Повтаряй звука",
        L"Преглед…",
        L"Език:",
        L"Забрани темите",
        L"Запази",
        L"Приложи",
        L"Отказ",
        L"Покажи всички",
        L"Скрий всички",
        L"Спри алармата",
        L"Помощ",
        L"За програмата",
        L"Изход",
        L"Аналогов часовник",
        L"Цифров часовник",
        L"Календар",
        L"Календар с часовник",
        L"Въведете отместване във формат [-]HH:mm:ss.ff.",
        L"Въведете валиден час от 0:00 до 23:59.",
        L"Да се премахнат ли избраните изпълними модули?",
        L"Трябва да остане поне един изпълним модул.",
        L"Затвори"
    }, {
        L"Часовници и календари",
        L"Поставки",
        L"Додај",
        L"Отстрани…",
        L"Дуплирај",
        L"Општо",
        L"Изглед",
        L"Аларм",
        L"Име:",
        L"Вид:",
        L"Видливо",
        L"Секогаш најгоре",
        L"Секунди",
        L"Време UTC",
        L"Временска зона:",
        L"Поместување [-]HH:mm:ss.ff:",
        L"Големина:",
        L"Непроѕирност:",
        L"Големина на фонтот:",
        L"Водечка нула:",
        L"Проѕирна заднина",
        L"Боја на текстот…",
        L"Боја на заднината…",
        L"Броеви на недели",
        L"Недела како прв ден",
        L"Алармот е вклучен",
        L"Време на алармот:",
        L"Изврши датотека или наредба",
        L"Повторувај го звукот",
        L"Прегледај…",
        L"Јазик:",
        L"Оневозможи теми",
        L"Зачувај",
        L"Примени",
        L"Откажи",
        L"Прикажи ги сите",
        L"Скриј ги сите",
        L"Запри го алармот",
        L"Помош",
        L"За програмата",
        L"Излез",
        L"Аналоген часовник",
        L"Дигитален часовник",
        L"Календар",
        L"Календар со часовник",
        L"Внесете поместување во облик [-]HH:mm:ss.ff.",
        L"Внесете важечко време од 0:00 до 23:59.",
        L"Да се отстранат избраните виџети?",
        L"Мора да остане најмалку еден виџет.",
        L"Затвори"
    }, {
        L"Сатови и календари",
        L"Подешавања",
        L"Додај",
        L"Уклони…",
        L"Дуплирај",
        L"Опште",
        L"Изглед",
        L"Аларм",
        L"Назив:",
        L"Врста:",
        L"Видљиво",
        L"Увек на врху",
        L"Секунде",
        L"Време UTC",
        L"Временска зона:",
        L"Помак [-]HH:mm:ss.ff:",
        L"Величина:",
        L"Непрозирност:",
        L"Величина фонта:",
        L"Водећа нула:",
        L"Провидна позадина",
        L"Боја текста…",
        L"Боја позадине…",
        L"Бројеви недеља",
        L"Недеља као први дан",
        L"Аларм укључен",
        L"Време аларма:",
        L"Покрени датотеку или наредбу",
        L"Понављај звук",
        L"Прегледај…",
        L"Језик:",
        L"Онемогући теме",
        L"Сачувај",
        L"Примени",
        L"Откажи",
        L"Прикажи све",
        L"Сакриј све",
        L"Заустави аларм",
        L"Помоћ",
        L"О програму",
        L"Излаз",
        L"Аналогни сат",
        L"Дигитални сат",
        L"Календар",
        L"Календар са сатом",
        L"Унесите помак у облику [-]HH:mm:ss.ff.",
        L"Унесите исправно време од 0:00 до 23:59.",
        L"Уклонити изабране виџете?",
        L"Мора остати бар један виџет.",
        L"Затвори"
    }, {
        L"Годинники та календарі",
        L"Налаштування",
        L"Додати",
        L"Видалити…",
        L"Дублювати",
        L"Загальні",
        L"Вигляд",
        L"Будильник",
        L"Назва:",
        L"Тип:",
        L"Показувати",
        L"Завжди зверху",
        L"Секунди",
        L"Час UTC",
        L"Часовий пояс:",
        L"Зсув [-]HH:mm:ss.ff:",
        L"Розмір:",
        L"Непрозорість:",
        L"Розмір шрифту:",
        L"Початковий нуль:",
        L"Прозоре тло",
        L"Колір тексту…",
        L"Колір тла…",
        L"Номери тижнів",
        L"Неділя — перший день",
        L"Будильник увімкнено",
        L"Час будильника:",
        L"Запускати файл або команду",
        L"Повторювати звук",
        L"Огляд…",
        L"Мова:",
        L"Вимкнути теми",
        L"Зберегти",
        L"Застосувати",
        L"Скасувати",
        L"Показати все",
        L"Приховати все",
        L"Зупинити будильник",
        L"Довідка",
        L"Про програму",
        L"Вийти",
        L"Аналоговий годинник",
        L"Цифровий годинник",
        L"Календар",
        L"Календар із годинником",
        L"Введіть зсув у форматі [-]HH:mm:ss.ff.",
        L"Введіть коректний час від 0:00 до 23:59.",
        L"Видалити вибрані віджети?",
        L"Має залишитися принаймні один віджет.",
        L"Закрити"
    }, {
        L"Часы и календари",
        L"Настройки",
        L"Добавить",
        L"Удалить…",
        L"Дублировать",
        L"Общие",
        L"Внешний вид",
        L"Будильник",
        L"Название:",
        L"Тип:",
        L"Показывать",
        L"Поверх всех окон",
        L"Секунды",
        L"Время UTC",
        L"Часовой пояс:",
        L"Смещение [-]HH:mm:ss.ff:",
        L"Размер:",
        L"Непрозрачность:",
        L"Размер шрифта:",
        L"Ведущий ноль:",
        L"Прозрачный фон",
        L"Цвет текста…",
        L"Цвет фона…",
        L"Номера недель",
        L"Воскресенье — первый день",
        L"Будильник включён",
        L"Время будильника:",
        L"Запускать файл или команду",
        L"Повторять звук",
        L"Обзор…",
        L"Язык:",
        L"Отключить темы",
        L"Сохранить",
        L"Применить",
        L"Отмена",
        L"Показать всё",
        L"Скрыть всё",
        L"Остановить будильник",
        L"Справка",
        L"О программе",
        L"Выход",
        L"Аналоговые часы",
        L"Цифровые часы",
        L"Календарь",
        L"Календарь с часами",
        L"Введите смещение в формате [-]HH:mm:ss.ff.",
        L"Введите корректное время от 0:00 до 23:59.",
        L"Удалить выбранные виджеты?",
        L"Должен остаться хотя бы один виджет.",
        L"Закрыть"
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
    L"Norsk (bokmål)",
    L"Svenska",
    L"Suomi",
    L"Dansk",
    L"Íslenska",
    L"Türkçe",
    L"Eesti",
    L"Gaeilge",
    L"Lietuvių",
    L"Latviešu",
    L"Magyar",
    L"Malti",
    L"Nederlands",
    L"Română",
    L"Ελληνικά",
    L"Bosanski",
    L"Hrvatski",
    L"Slovenščina",
    L"Crnogorski",
    L"Беларуская",
    L"Български",
    L"Македонски",
    L"Српски",
    L"Українська",
    L"Русский"
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
    L"Skjáklukka",
    L"Monitör saati",
    L"Ekraanikell",
    L"Clog scáileáin",
    L"Ekrano laikrodis",
    L"Ekrāna pulkstenis",
    L"Képernyőóra",
    L"Arloġġ tal-iskrin",
    L"Schermklok",
    L"Ceas pe ecran",
    L"Ρολόι οθόνης",
    L"Sat na ekranu",
    L"Sat na zaslonu",
    L"Ura na zaslonu",
    L"Sat na monitoru",
    L"Гадзіннік на маніторы",
    L"Часовник на монитор",
    L"Часовник на монитор",
    L"Сат на монитору",
    L"Годинник на моніторі",
    L"Часы на мониторе"
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
    L"En fazla %d araç kullanılabilir.",
    L"Vidinaid võib olla kuni %d.",
    L"Is é %d an líon uasta giuirléidí.",
    L"Didžiausias valdiklių skaičius – %d.",
    L"Maksimālais logrīku skaits ir %d.",
    L"A minialkalmazások maximális száma: %d.",
    L"L-għadd massimu ta’ widgets huwa %d.",
    L"Het maximumaantal widgets is %d.",
    L"Numărul maxim de widgeturi este %d.",
    L"Ο μέγιστος αριθμός γραφικών στοιχείων είναι %d.",
    L"Najveći broj vidžeta je %d.",
    L"Najveći broj widgeta je %d.",
    L"Največje število gradnikov je %d.",
    L"Najveći broj vidžeta je %d.",
    L"Максімальная колькасць віджэтаў — %d.",
    L"Максималният брой изпълними модули е %d.",
    L"Најголемиот број виџети е %d.",
    L"Највећи број виџета је %d.",
    L"Максимальна кількість віджетів — %d.",
    L"Максимальное количество виджетов — %d."
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
    L" - kopya",
    L" - koopia",
    L" - cóip",
    L" - kopija",
    L" - kopija",
    L" - másolat",
    L" - kopja",
    L" - kopie",
    L" - copie",
    L" - αντίγραφο",
    L" - kopija",
    L" - kopija",
    L" - kopija",
    L" - kopija",
    L" - копія",
    L" - копие",
    L" - копија",
    L" - копија",
    L" - копія",
    L" - копия"
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
    L"Genişletilebilir işaretleme dili (*.xml)",
    L"Laiendatav märgistuskeel (*.xml)",
    L"Teanga Mharcála Inbhreisithe (*.xml)",
    L"Išplečiamoji ženklinimo kalba (*.xml)",
    L"Paplašināmā iezīmēšanas valoda (*.xml)",
    L"Bővíthető jelölőnyelv (*.xml)",
    L"Lingwa tal-markatura estensibbli (*.xml)",
    L"Uitbreidbare opmaaktaal (*.xml)",
    L"Limbaj de marcare extensibil (*.xml)",
    L"Επεκτάσιμη γλώσσα σήμανσης (*.xml)",
    L"Proširivi označni jezik (*.xml)",
    L"Proširivi označni jezik (*.xml)",
    L"Razširljivi označevalni jezik (*.xml)",
    L"Proširivi jezik za označavanje (*.xml)",
    L"Пашыральная мова разметкі (*.xml)",
    L"Разширяем маркиращ език (*.xml)",
    L"Проширлив јазик за означување (*.xml)",
    L"Прошириви језик за означавање (*.xml)",
    L"Розширювана мова розмітки (*.xml)",
    L"Расширяемый язык разметки (*.xml)"
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
    L"Virgülle ayrılmış değerler (*.csv)",
    L"Komaga eraldatud väärtused (*.csv)",
    L"Luachanna scartha le camóga (*.csv)",
    L"Kableliais atskirtos reikšmės (*.csv)",
    L"Ar komatiem atdalītas vērtības (*.csv)",
    L"Vesszővel tagolt értékek (*.csv)",
    L"Valuri separati b’virgoli (*.csv)",
    L"Door komma’s gescheiden waarden (*.csv)",
    L"Valori separate prin virgulă (*.csv)",
    L"Τιμές διαχωρισμένες με κόμματα (*.csv)",
    L"Vrijednosti odvojene zarezima (*.csv)",
    L"Vrijednosti odvojene zarezima (*.csv)",
    L"Vrednosti, ločene z vejicami (*.csv)",
    L"Vrijednosti razdvojene zarezima (*.csv)",
    L"Значэнні, падзеленыя коскамі (*.csv)",
    L"Стойности, разделени със запетаи (*.csv)",
    L"Вредности одделени со запирки (*.csv)",
    L"Вредности раздвојене зарезима (*.csv)",
    L"Значення, розділені комами (*.csv)",
    L"Значения, разделённые запятыми (*.csv)"
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
    L"dosyalar\0*.*\0",
    L"Heli ja programmid\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Kõik "
    L"failid\0*.*\0",
    L"Fuaim agus ríomhchláir\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Gach "
    L"comhad\0*.*\0",
    L"Garsas ir programos\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Visi "
    L"failai\0*.*\0",
    L"Skaņa un programmas\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Visi "
    L"faili\0*.*\0",
    L"Hangfájlok és programok\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Minden "
    L"fájl\0*.*\0",
    L"Awdjo u programmi\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Il-fajls "
    L"kollha\0*.*\0",
    L"Geluid en programma’s\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Alle "
    L"bestanden\0*.*\0",
    L"Sunet și programe\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Toate "
    L"fișierele\0*.*\0",
    L"Ήχος και προγράμματα\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Όλα τα "
    L"αρχεία\0*.*\0",
    L"Zvuk i programi\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Sve "
    L"datoteke\0*.*\0",
    L"Zvuk i programi\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Sve "
    L"datoteke\0*.*\0",
    L"Zvok in programi\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Vse "
    L"datoteke\0*.*\0",
    L"Zvuk i programi\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Sve "
    L"datoteke\0*.*\0",
    L"Гук і праграмы\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Усе файлы\0*.*\0",
    L"Звук и програми\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Всички "
    L"файлове\0*.*\0",
    L"Звук и програми\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Сите "
    L"датотеки\0*.*\0",
    L"Звук и програми\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Све "
    L"датотеке\0*.*\0",
    L"Звук і програми\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Усі файли\0*.*\0",
    L"Звук и программы\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0Все файлы\0*.*\0"
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
    L"tr-TR",
    L"et-EE",
    L"ga-IE",
    L"lt-LT",
    L"lv-LV",
    L"hu-HU",
    L"mt-MT",
    L"nl-NL",
    L"ro-RO",
    L"el-GR",
    L"bs-Latn-BA",
    L"hr-HR",
    L"sl-SI",
    L"sr-Latn-ME",
    L"be-BY",
    L"bg-BG",
    L"mk-MK",
    L"sr-Cyrl-RS",
    L"uk-UA",
    L"ru-RU"
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
    L"Araç dili:",
    L"Vidina keel:",
    L"Teanga na giuirléide:",
    L"Valdiklio kalba:",
    L"Logrīka valoda:",
    L"Minialkalmazás nyelve:",
    L"Lingwa tal-widget:",
    L"Widgettaal:",
    L"Limba widgetului:",
    L"Γλώσσα στοιχείου:",
    L"Jezik vidžeta:",
    L"Jezik widgeta:",
    L"Jezik gradnika:",
    L"Jezik vidžeta:",
    L"Мова віджэта:",
    L"Език на модула:",
    L"Јазик на виџетот:",
    L"Језик виџета:",
    L"Мова віджета:",
    L"Язык виджета:"
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
    L"Uygulama &dili:",
    L"Rakenduse &keel:",
    L"&Teanga an fheidhmchláir:",
    L"Programos &kalba:",
    L"Programmas &valoda:",
    L"Alkalmazás &nyelve:",
    L"&Lingwa tal-applikazzjoni:",
    L"&Taal van toepassing:",
    L"&Limba aplicației:",
    L"&Γλώσσα εφαρμογής:",
    L"&Jezik programa:",
    L"&Jezik programa:",
    L"&Jezik programa:",
    L"&Jezik programa:",
    L"&Мова праграмы:",
    L"&Език на програмата:",
    L"&Јазик на програмата:",
    L"&Језик програма:",
    L"&Мова програми:",
    L"&Язык программы:"
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
    L"Uygulama &yazı tipi:",
    L"Rakenduse &font:",
    L"&Cló an fheidhmchláir:",
    L"Programos &šriftas:",
    L"Programmas &fonts:",
    L"Alkalmazás &betűtípusa:",
    L"&Font tal-applikazzjoni:",
    L"&Lettertype van toepassing:",
    L"&Fontul aplicației:",
    L"Γ&ραμματοσειρά εφαρμογής:",
    L"&Font programa:",
    L"&Font programa:",
    L"&Pisava programa:",
    L"&Font programa:",
    L"&Шрыфт праграмы:",
    L"&Шрифт на програмата:",
    L"&Фонт на програмата:",
    L"&Фонт програма:",
    L"&Шрифт програми:",
    L"&Шрифт программы:"
};

const wchar_t* FONT_STYLE_LABELS[LANG_COUNT][4] = {
    { L"Tučné", L"Kurzíva", L"Podtržené", L"Přeškrtnuté" },
    { L"Bold", L"Italic", L"Underline", L"Strikeout" },
    { L"Fett", L"Kursiv", L"Unterstrichen", L"Durchgestrichen" },
    { L"Gras", L"Italique", L"Souligné", L"Barré" },
    { L"Negrita", L"Cursiva", L"Subrayado", L"Tachado" },
    { L"Grassetto", L"Corsivo", L"Sottolineato", L"Barrato" },
    { L"Pogrubienie", L"Kursywa", L"Podkreślenie", L"Przekreślenie" },
    { L"Tučné", L"Kurzíva", L"Podčiarknuté", L"Prečiarknuté" },
    { L"Bold", L"Italic", L"Underline", L"Strikeout" },
    { L"Bold", L"Italic", L"Underline", L"Strikeout" },
    { L"Negrito", L"Itálico", L"Sublinhado", L"Rasurado" },
    { L"Fet", L"Kursiv", L"Understreket", L"Gjennomstreket" },
    { L"Fet", L"Kursiv", L"Understruken", L"Genomstruken" },
    { L"Lihavoitu", L"Kursivoitu", L"Alleviivattu", L"Yliviivattu" },
    { L"Fed", L"Kursiv", L"Understreget", L"Gennemstreget" },
    { L"Feitletrað", L"Skáletrað", L"Undirstrikað", L"Yfirstrikað" },
    { L"Kalın", L"İtalik", L"Altı çizili", L"Üstü çizili" },
    { L"Paks", L"Kursiiv", L"Allakriipsutus", L"Läbikriipsutus" },
    { L"Trom", L"Iodálach", L"Folíne", L"Líne tríd" },
    { L"Paryškintasis", L"Kursyvas", L"Pabrauktas", L"Perbrauktas" },
    { L"Treknraksts", L"Slīpraksts", L"Pasvītrojums", L"Pārsvītrojums" },
    { L"Félkövér", L"Dőlt", L"Aláhúzott", L"Áthúzott" },
    { L"Grassett", L"Korsiv", L"Sottolinjat", L"Maqtugħ" },
    { L"Vet", L"Cursief", L"Onderstreept", L"Doorgehaald" },
    { L"Aldin", L"Cursiv", L"Subliniat", L"Tăiat cu o linie" },
    { L"Έντονα", L"Πλάγια", L"Υπογράμμιση", L"Διακριτή διαγραφή" },
    { L"Podebljano", L"Kurziv", L"Podcrtano", L"Precrtano" },
    { L"Podebljano", L"Kurziv", L"Podcrtano", L"Precrtano" },
    { L"Krepko", L"Ležeče", L"Podčrtano", L"Prečrtano" },
    { L"Podebljano", L"Kurziv", L"Podvučeno", L"Precrtano" },
    { L"Паўтлусты", L"Курсіў", L"Падкрэслены", L"Закрэслены" },
    { L"Получер", L"Курсив", L"Подчертан", L"Зачертан" },
    { L"Задебелено", L"Курзив", L"Подвлечено", L"Прецртано" },
    { L"Подебљано", L"Курзив", L"Подвучено", L"Прецртано" },
    { L"Напівжирний", L"Курсив", L"Підкреслений", L"Закреслений" },
    { L"Полужирный", L"Курсив", L"Подчёркнутый", L"Зачёркнутый" }
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
    L"Sistem varsayılanı",
    L"Süsteemi vaikefont",
    L"Réamhshocrú an chórais",
    L"Numatytasis sistemos",
    L"Sistēmas noklusējums",
    L"Rendszer alapértelmezése",
    L"Default tas-sistema",
    L"Systeemstandaard",
    L"Implicit pentru sistem",
    L"Προεπιλογή συστήματος",
    L"Podrazumijevani sistemski",
    L"Zadani sustavski",
    L"Sistemsko privzeto",
    L"Podrazumijevani sistemski",
    L"Сістэмны прадвызначаны",
    L"Системен по подразбиране",
    L"Стандарден системски",
    L"Подразумевани системски",
    L"Системний за замовчуванням",
    L"Системный по умолчанию"
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
    L"Kopyalanan &tarih biçimi",
    L"Kopeeritava &kuupäeva vorming",
    L"Formáid an &dáta cóipeáilte",
    L"Kopijuojamos &datos formatas",
    L"Kopētā &datuma formāts",
    L"Másolt &dátum formátuma",
    L"Format tad-&data kkupjata",
    L"Indeling gekopieerde &datum",
    L"Formatul &datei copiate",
    L"Μορφή αντιγραμμένης &ημερομηνίας",
    L"Oblik kopiranog &datuma",
    L"Oblik kopiranog &datuma",
    L"Oblika kopiranega &datuma",
    L"Oblik kopiranog &datuma",
    L"Фармат капіявання &даты",
    L"Формат на копираната &дата",
    L"Облик на копираниот &датум",
    L"Облик копираног &датума",
    L"Формат копіювання &дати",
    L"Формат копирования &даты"
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
    L"Kopyalanan &tarih biçimi:",
    L"Kopeeritava &kuupäeva vorming:",
    L"Formáid an &dáta cóipeáilte:",
    L"Kopijuojamos &datos formatas:",
    L"Kopētā &datuma formāts:",
    L"Másolt &dátum formátuma:",
    L"Format tad-&data kkupjata:",
    L"Indeling gekopieerde &datum:",
    L"Formatul &datei copiate:",
    L"Μορφή αντιγραμμένης &ημερομηνίας:",
    L"Oblik kopiranog &datuma:",
    L"Oblik kopiranog &datuma:",
    L"Oblika kopiranega &datuma:",
    L"Oblik kopiranog &datuma:",
    L"Фармат капіявання &даты:",
    L"Формат на копираната &дата:",
    L"Облик на копираниот &датум:",
    L"Облик копираног &датума:",
    L"Формат копіювання &дати:",
    L"Формат копирования &даты:"
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
    L"Kısa tarih",
    L"Lühike kuupäev",
    L"Dáta gearr",
    L"Trumpoji data",
    L"Īsais datums",
    L"Rövid dátum",
    L"Data qasira",
    L"Korte datum",
    L"Dată scurtă",
    L"Σύντομη ημερομηνία",
    L"Kratki datum",
    L"Kratki datum",
    L"Kratki datum",
    L"Kratak datum",
    L"Кароткая дата",
    L"Кратка дата",
    L"Краток датум",
    L"Кратак датум",
    L"Коротка дата",
    L"Краткая дата"
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
    L"Uzun tarih",
    L"Pikk kuupäev",
    L"Dáta fada",
    L"Ilgoji data",
    L"Garais datums",
    L"Hosszú dátum",
    L"Data twila",
    L"Lange datum",
    L"Dată lungă",
    L"Πλήρης ημερομηνία",
    L"Dugi datum",
    L"Dugi datum",
    L"Dolgi datum",
    L"Dug datum",
    L"Поўная дата",
    L"Дълга дата",
    L"Долг датум",
    L"Дуг датум",
    L"Повна дата",
    L"Полная дата"
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
    L"&Izgarada düzenle",
    L"&Paiguta ruudustikku",
    L"&Eagraigh in eangach",
    L"&Išdėstyti tinkleliu",
    L"&Sakārtot režģī",
    L"&Rácsba rendezés",
    L"&Irranġa fi gradilja",
    L"&Schikken in raster",
    L"&Aranjare în grilă",
    L"&Τακτοποίηση σε πλέγμα",
    L"&Rasporedi u mrežu",
    L"&Rasporedi u mrežu",
    L"&Razporedi v mrežo",
    L"&Rasporedi u mrežu",
    L"&Упарадкаваць па сетцы",
    L"&Подреди в мрежа",
    L"&Распореди во мрежа",
    L"&Распореди у мрежу",
    L"&Упорядкувати за сіткою",
    L"&Упорядочить по сетке"
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
    L"&Göster",
    L"&Kuva",
    L"&Taispeáin",
    L"&Rodyti",
    L"&Rādīt",
    L"&Megjelenítés",
    L"&Uri",
    L"&Weergeven",
    L"&Afișare",
    L"&Εμφάνιση",
    L"&Prikaži",
    L"&Prikaži",
    L"&Pokaži",
    L"&Prikaži",
    L"&Паказаць",
    L"&Покажи",
    L"&Прикажи",
    L"&Прикажи",
    L"&Показати",
    L"&Показать"
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
    L"&Gizle",
    L"&Peida",
    L"&Folaigh",
    L"&Slėpti",
    L"&Paslēpt",
    L"&Elrejtés",
    L"&Aħbi",
    L"&Verbergen",
    L"&Ascundere",
    L"&Απόκρυψη",
    L"&Sakrij",
    L"&Sakrij",
    L"&Skrij",
    L"&Sakrij",
    L"&Схаваць",
    L"&Скрий",
    L"&Скриј",
    L"&Сакриј",
    L"&Приховати",
    L"&Скрыть"
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
    L"&UTC metnini göster",
    L"Kuva &UTC tähis",
    L"Taispeáin téacs &UTC",
    L"Rodyti &UTC žymą",
    L"Rādīt &UTC apzīmējumu",
    L"&UTC-felirat megjelenítése",
    L"Uri t-test &UTC",
    L"&UTC-tekst weergeven",
    L"Afișare text &UTC",
    L"Εμφάνιση ένδειξης &UTC",
    L"Prikaži oznaku &UTC",
    L"Prikaži oznaku &UTC",
    L"Pokaži oznako &UTC",
    L"Prikaži oznaku &UTC",
    L"Паказваць надпіс &UTC",
    L"Показвай надпис &UTC",
    L"Прикажувај ознака &UTC",
    L"Прикажи ознаку &UTC",
    L"Показувати напис &UTC",
    L"Показывать надпись &UTC"
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
    L"&Monitörler:",
    L"&Kuvarid:",
    L"&Monatóirí:",
    L"&Monitoriai:",
    L"&Monitori:",
    L"&Monitorok:",
    L"&Moniters:",
    L"&Beeldschermen:",
    L"&Monitoare:",
    L"&Οθόνες:",
    L"&Ekrani:",
    L"&Zasloni:",
    L"&Zasloni:",
    L"&Monitori:",
    L"&Маніторы:",
    L"&Монитори:",
    L"&Монитори:",
    L"&Монитори:",
    L"&Монітори:",
    L"&Мониторы:"
};

/// Monitor ListView headings, primary-output labels, and explicit bit-depth units.
const wchar_t* MONITOR_COLUMN_LABELS[LANG_COUNT][MONITOR_COLUMN_COUNT] = {
    { L"Monitor", L"Model monitoru", L"Rozlišení", L"Obnovovací frekvence", L"Bitová hloubka", L"Formát barvy", L"Barevný prostor", L"Poloha" },
    { L"Display", L"Monitor model", L"Resolution", L"Refresh rate", L"Bit depth", L"Color format", L"Color space", L"Position" },
    { L"Monitor", L"Monitormodell", L"Auflösung", L"Bildwiederholfrequenz", L"Bittiefe", L"Farbformat", L"Farbraum", L"Position" },
    { L"Moniteur", L"Modèle du moniteur", L"Résolution", L"Fréquence de rafraîchissement", L"Profondeur de bits", L"Format de couleur", L"Espace colorimétrique", L"Position" },
    { L"Monitor", L"Modelo del monitor", L"Resolución", L"Frecuencia de actualización", L"Profundidad de bits", L"Formato de color", L"Espacio de color", L"Posición" },
    { L"Monitor", L"Modello del monitor", L"Risoluzione", L"Frequenza di aggiornamento", L"Profondità di bit", L"Formato colore", L"Spazio colore", L"Posizione" },
    { L"Monitor", L"Model monitora", L"Rozdzielczość", L"Częstotliwość odświeżania", L"Głębia bitowa", L"Format koloru", L"Przestrzeń barw", L"Położenie" },
    { L"Monitor", L"Model monitora", L"Rozlíšenie", L"Obnovovacia frekvencia", L"Bitová hĺbka", L"Formát farby", L"Farebný priestor", L"Poloha" },
    { L"Display", L"Monitor model", L"Resolution", L"Refresh rate", L"Bit depth", L"Colour format", L"Colour space", L"Position" },
    { L"Display", L"Monitor model", L"Resolution", L"Refresh rate", L"Bit depth", L"Colour format", L"Colour space", L"Position" },
    { L"Monitor", L"Modelo do monitor", L"Resolução", L"Taxa de atualização", L"Profundidade de bits", L"Formato de cor", L"Espaço de cor", L"Posição" },
    { L"Skjerm", L"Skjermmodell", L"Oppløsning", L"Oppdateringsfrekvens", L"Bitdybde", L"Fargeformat", L"Fargerom", L"Posisjon" },
    { L"Bildskärm", L"Skärmmodell", L"Upplösning", L"Uppdateringsfrekvens", L"Bitdjup", L"Färgformat", L"Färgrymd", L"Position" },
    { L"Näyttö", L"Näytön malli", L"Tarkkuus", L"Virkistystaajuus", L"Bittisyvyys", L"Värimuoto", L"Väriavaruus", L"Sijainti" },
    { L"Skærm", L"Skærmmodel", L"Opløsning", L"Opdateringsfrekvens", L"Bitdybde", L"Farveformat", L"Farverum", L"Placering" },
    { L"Skjár", L"Gerð skjás", L"Upplausn", L"Endurnýjunartíðni", L"Bitadýpt", L"Litasnið", L"Litarými", L"Staðsetning" },
    { L"Monitör", L"Monitör modeli", L"Çözünürlük", L"Yenileme hızı", L"Bit derinliği", L"Renk biçimi", L"Renk alanı", L"Konum" },
    { L"Kuvar", L"Kuvari mudel", L"Eraldusvõime", L"Värskendussagedus", L"Bitisügavus", L"Värvivorming", L"Värviruum", L"Asukoht" },
    { L"Monatóir", L"Samhail an mhonatóra", L"Taifeach", L"Ráta athnuachana", L"Doimhneacht ghiotán", L"Formáid datha", L"Spás datha", L"Suíomh" },
    { L"Monitorius", L"Monitoriaus modelis", L"Skiriamoji geba", L"Atnaujinimo dažnis", L"Bitų gylis", L"Spalvų formatas", L"Spalvų erdvė", L"Padėtis" },
    { L"Monitors", L"Monitora modelis", L"Izšķirtspēja", L"Atsvaidzināšanas frekvence", L"Bitu dziļums", L"Krāsu formāts", L"Krāstelpa", L"Pozīcija" },
    { L"Monitor", L"Monitor típusa", L"Felbontás", L"Frissítési gyakoriság", L"Bitmélység", L"Színformátum", L"Színtér", L"Pozíció" },
    { L"Moniter", L"Mudell tal-moniter", L"Riżoluzzjoni", L"Rata ta’ aġġornament", L"Fond tal-bits", L"Format tal-kulur", L"Spazju tal-kulur", L"Pożizzjoni" },
    { L"Beeldscherm", L"Beeldschermmodel", L"Resolutie", L"Vernieuwingsfrequentie", L"Bitdiepte", L"Kleurindeling", L"Kleurruimte", L"Positie" },
    { L"Monitor", L"Model monitor", L"Rezoluție", L"Rată de reîmprospătare", L"Adâncime de biți", L"Format de culoare", L"Spațiu de culoare", L"Poziție" },
    { L"Οθόνη", L"Μοντέλο οθόνης", L"Ανάλυση", L"Ρυθμός ανανέωσης", L"Βάθος bit", L"Μορφή χρώματος", L"Χρωματικός χώρος", L"Θέση" },
    { L"Monitor", L"Model monitora", L"Rezolucija", L"Frekvencija osvježavanja", L"Dubina bita", L"Format boje", L"Prostor boja", L"Položaj" },
    { L"Zaslon", L"Model zaslona", L"Razlučivost", L"Frekvencija osvježavanja", L"Dubina bita", L"Oblik boje", L"Prostor boja", L"Položaj" },
    { L"Zaslon", L"Model zaslona", L"Ločljivost", L"Hitrost osveževanja", L"Bitna globina", L"Oblika barv", L"Barvni prostor", L"Položaj" },
    { L"Monitor", L"Model monitora", L"Rezolucija", L"Frekvencija osvježavanja", L"Dubina bita", L"Format boje", L"Prostor boja", L"Položaj" },
    { L"Манітор", L"Мадэль манітора", L"Раздзяляльнасць", L"Частата абнаўлення", L"Бітавая глыбіня", L"Фармат колеру", L"Каляровая прастора", L"Пазіцыя" },
    { L"Монитор", L"Модел на монитора", L"Разделителна способност", L"Честота на опресняване", L"Битова дълбочина", L"Формат на цветовете", L"Цветово пространство", L"Позиция" },
    { L"Монитор", L"Модел на мониторот", L"Резолуција", L"Стапка на освежување", L"Битна длабочина", L"Формат на боја", L"Простор на бои", L"Положба" },
    { L"Монитор", L"Модел монитора", L"Резолуција", L"Учестаност освежавања", L"Дубина бита", L"Формат боје", L"Простор боја", L"Положај" },
    { L"Монітор", L"Модель монітора", L"Роздільна здатність", L"Частота оновлення", L"Бітова глибина", L"Формат кольору", L"Колірний простір", L"Розташування" },
    { L"Монитор", L"Модель монитора", L"Разрешение", L"Частота обновления", L"Глубина цвета", L"Формат цвета", L"Цветовое пространство", L"Расположение" }
};

const wchar_t* MONITOR_PRIMARY_LABELS[LANG_COUNT] = {
    L"hlavní",
    L"primary",
    L"primär",
    L"principal",
    L"principal",
    L"principale",
    L"główny",
    L"hlavný",
    L"primary",
    L"primary",
    L"principal",
    L"primær",
    L"primär",
    L"ensisijainen",
    L"primær",
    L"aðal",
    L"birincil",
    L"peamine",
    L"príomhúil",
    L"pagrindinis",
    L"galvenais",
    L"elsődleges",
    L"primarju",
    L"primair",
    L"principal",
    L"κύρια",
    L"primarni",
    L"primarni",
    L"glavni",
    L"primarni",
    L"асноўны",
    L"основен",
    L"примарен",
    L"примарни",
    L"основний",
    L"основной"
};

const wchar_t* MONITOR_DEPTH_FORMATS[LANG_COUNT][2] = {
    { L"%u bitů/kanál", L"%u bitů/pixel" },
    { L"%u bits/channel", L"%u bits/pixel" },
    { L"%u Bit/Kanal", L"%u Bit/Pixel" },
    { L"%u bits/canal", L"%u bits/pixel" },
    { L"%u bits/canal", L"%u bits/píxel" },
    { L"%u bit/canale", L"%u bit/pixel" },
    { L"%u bitów/kanał", L"%u bitów/piksel" },
    { L"%u bitov/kanál", L"%u bitov/pixel" },
    { L"%u bits/channel", L"%u bits/pixel" },
    { L"%u bits/channel", L"%u bits/pixel" },
    { L"%u bits/canal", L"%u bits/píxel" },
    { L"%u bit/kanal", L"%u bit/piksel" },
    { L"%u bitar/kanal", L"%u bitar/pixel" },
    { L"%u bittiä/kanava", L"%u bittiä/pikseli" },
    { L"%u bit/kanal", L"%u bit/pixel" },
    { L"%u bitar/rás", L"%u bitar/myndpunktur" },
    { L"%u bit/kanal", L"%u bit/piksel" },
    { L"%u bitti/kanal", L"%u bitti/piksel" },
    { L"%u giotán/cainéal", L"%u giotán/picteilín" },
    { L"%u bitų/kanalą", L"%u bitų/pikselį" },
    { L"%u biti/kanālā", L"%u biti/pikselī" },
    { L"%u bit/csatorna", L"%u bit/képpont" },
    { L"%u bits/kanal", L"%u bits/pixel" },
    { L"%u bits/kanaal", L"%u bits/pixel" },
    { L"%u biți/canal", L"%u biți/pixel" },
    { L"%u bit/κανάλι", L"%u bit/pixel" },
    { L"%u bita/kanal", L"%u bita/piksel" },
    { L"%u bita/kanal", L"%u bita/piksel" },
    { L"%u bitov/kanal", L"%u bitov/slikovno piko" },
    { L"%u bita/kanal", L"%u bita/piksel" },
    { L"%u біт/канал", L"%u біт/піксель" },
    { L"%u бита/канал", L"%u бита/пиксел" },
    { L"%u бита/канал", L"%u бита/пиксел" },
    { L"%u бита/канал", L"%u бита/пиксел" },
    { L"%u біт/канал", L"%u біт/піксель" },
    { L"%u бит/канал", L"%u бит/пиксель" }
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
    L"&Diğer monitörleri karart",
    L"Tumenda &muud kuvarid",
    L"Dorchaigh &monatóirí eile",
    L"Užtemdyti &kitus monitorius",
    L"Aptumšot &pārējos monitorus",
    L"&Többi monitor elsötétítése",
    L"Dallam il-&moniters l-oħra",
    L"&Andere beeldschermen verduisteren",
    L"Întunecarea &celorlalte monitoare",
    L"Συσκότιση &άλλων οθονών",
    L"Zatamni &ostale ekrane",
    L"Zatamni &ostale zaslone",
    L"Zatemni &druge zaslone",
    L"Zatamni &ostale monitore",
    L"Зацямняць &іншыя маніторы",
    L"Затъмни &другите монитори",
    L"Затемни ги &другите монитори",
    L"Затамни &остале мониторе",
    L"Затемнювати &інші монітори",
    L"Затемнять &другие мониторы"
};

const wchar_t* FONT_LABELS[LANG_COUNT] = {
    L"&Písmo:",
    L"&Font:",
    L"&Schriftart:",
    L"&Police :",
    L"&Fuente:",
    L"&Carattere:",
    L"&Czcionka:",
    L"&Písmo:",
    L"&Font:",
    L"&Font:",
    L"&Tipo de letra:",
    L"&Skrift:",
    L"&Teckensnitt:",
    L"&Fontti:",
    L"&Skrifttype:",
    L"&Letur:",
    L"&Yazı tipi:",
    L"&Font:",
    L"&Cló:",
    L"&Šriftas:",
    L"&Fonts:",
    L"&Betűtípus:",
    L"&Font:",
    L"&Lettertype:",
    L"&Font:",
    L"&Γραμματοσειρά:",
    L"&Font:",
    L"&Font:",
    L"&Pisava:",
    L"&Font:",
    L"&Шрыфт:",
    L"&Шрифт:",
    L"&Фонт:",
    L"&Фонт:",
    L"&Шрифт:",
    L"&Шрифт:"
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
    L"&Yazı tipi seç…",
    L"Vali &font…",
    L"Roghnaigh &cló…",
    L"Pasirinkti &šriftą…",
    L"Izvēlēties &fontu…",
    L"&Betűtípus…",
    L"Agħżel &font…",
    L"&Lettertype kiezen…",
    L"Alegere &font…",
    L"Επιλογή &γραμματοσειράς…",
    L"Odaberi &font…",
    L"Odaberi &font…",
    L"Izberi &pisavo…",
    L"Izaberi &font…",
    L"Выбраць &шрыфт…",
    L"Избери &шрифт…",
    L"Избери &фонт…",
    L"Изабери &фонт…",
    L"Вибрати &шрифт…",
    L"Выбрать &шрифт…"
};

const wchar_t* CALENDAR_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &kalendáře:",
    L"&Calendar font:",
    L"&Kalenderschrift:",
    L"Police du &calendrier :",
    L"Fuente del &calendario:",
    L"Carattere del &calendario:",
    L"Czcionka &kalendarza:",
    L"Písmo &kalendára:",
    L"&Calendar font:",
    L"&Calendar font:",
    L"Tipo de letra do &calendário:",
    L"&Kalenderskrift:",
    L"&Kalenderteckensnitt:",
    L"&Kalenterin fontti:",
    L"&Kalenderskrifttype:",
    L"Letur &dagatals:",
    L"&Takvim yazı tipi:",
    L"&Kalendri font:",
    L"Cló an &fhéilire:",
    L"&Kalendoriaus šriftas:",
    L"&Kalendāra fonts:",
    L"&Naptár betűtípusa:",
    L"Font tal-&kalendarju:",
    L"&Kalenderlettertype:",
    L"Font &calendar:",
    L"Γραμματοσειρά &ημερολογίου:",
    L"Font &kalendara:",
    L"Font &kalendara:",
    L"Pisava &koledarja:",
    L"Font &kalendara:",
    L"Шрыфт &календара:",
    L"Шрифт на &календара:",
    L"Фонт на &календарот:",
    L"Фонт &календара:",
    L"Шрифт &календаря:",
    L"Шрифт &календаря:"
};

const wchar_t* PANEL_TOP_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &horního řádku:",
    L"&Top row font:",
    L"Schrift der &oberen Zeile:",
    L"Police de la ligne &supérieure :",
    L"Fuente de la línea &superior:",
    L"Carattere riga &superiore:",
    L"Czcionka &górnego wiersza:",
    L"Písmo &horného riadka:",
    L"&Top row font:",
    L"&Top row font:",
    L"Tipo de letra da linha &superior:",
    L"Skrift for &øverste rad:",
    L"Teckensnitt för &översta raden:",
    L"&Ylärivin fontti:",
    L"Skrifttype for &øverste linje:",
    L"Letur &efri línu:",
    L"&Üst satır yazı tipi:",
    L"&Ülemise rea font:",
    L"Cló na sraithe &uachtaraí:",
    L"&Viršutinės eilutės šriftas:",
    L"&Augšējās rindas fonts:",
    L"&Felső sor betűtípusa:",
    L"Font tar-ringiela ta’ &fuq:",
    L"Lettertype &bovenste rij:",
    L"Font rând &superior:",
    L"Γραμματοσειρά &επάνω:",
    L"Font &gornjeg reda:",
    L"Font &gornjeg retka:",
    L"Pisava &zgornje vrstice:",
    L"Font &gornjeg reda:",
    L"Шрыфт &верхняга радка:",
    L"Шрифт на &горния ред:",
    L"Фонт на &горниот ред:",
    L"Фонт &горњег реда:",
    L"Шрифт &верхнього рядка:",
    L"Шрифт &верхней строки:"
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
    L"Bugün satırı",
    L"Tänase kuupäeva rida",
    L"Sraith an lae inniu",
    L"Šiandienos eilutė",
    L"Šodienas rinda",
    L"Mai dátum sora",
    L"Ringiela tal-lum",
    L"Rij Vandaag",
    L"Rândul Azi",
    L"Γραμμή Σήμερα",
    L"Red Danas",
    L"Redak Danas",
    L"Vrstica Danes",
    L"Red Danas",
    L"Радок «Сёння»",
    L"Ред „Днес“",
    L"Ред „Денес“",
    L"Ред Данас",
    L"Рядок «Сьогодні»",
    L"Строка «Сегодня»"
};

const wchar_t* PANEL_TODAY_TOOLTIP[LANG_COUNT] = {
    L"Přejít na dnešek",
    L"Go to Today",
    L"Zu heute wechseln",
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
    L"Bugüne git",
    L"Mine tänasele kuupäevale",
    L"Téigh go dtí an lá inniu",
    L"Pereiti į šiandieną",
    L"Pāriet uz šodienu",
    L"Ugrás a mai napra",
    L"Mur għad-data tal-lum",
    L"Naar vandaag",
    L"Salt la ziua de azi",
    L"Μετάβαση στο σήμερα",
    L"Idi na današnji datum",
    L"Idi na današnji datum",
    L"Pojdi na današnji datum",
    L"Idi na današnji datum",
    L"Перайсці да сённяшняй даты",
    L"Отиди на днешната дата",
    L"Оди на денешниот датум",
    L"Иди на данашњи датум",
    L"Перейти до сьогоднішньої дати",
    L"Перейти к сегодняшней дате"
};

const wchar_t* PANEL_TIME_FONT_LABELS[LANG_COUNT] = {
    L"Písmo č&asu:",
    L"&Time font:",
    L"Schrift der &Uhrzeit:",
    L"Police de l’&heure :",
    L"Fuente de la &hora:",
    L"Carattere dell’&ora:",
    L"Czcionka &czasu:",
    L"Písmo č&asu:",
    L"&Time font:",
    L"&Time font:",
    L"Tipo de letra da &hora:",
    L"Skrift for &klokkeslett:",
    L"&Tidsteckensnitt:",
    L"&Ajan fontti:",
    L"Skrifttype for &tid:",
    L"Letur &tíma:",
    L"&Saat yazı tipi:",
    L"&Kellaaja font:",
    L"Cló an &ama:",
    L"&Laiko šriftas:",
    L"&Laika fonts:",
    L"&Idő betűtípusa:",
    L"Font tal-&ħin:",
    L"Lettertype &tijd:",
    L"Font &oră:",
    L"Γραμματοσειρά &ώρας:",
    L"Font &vremena:",
    L"Font &vremena:",
    L"Pisava &časa:",
    L"Font &vremena:",
    L"Шрыфт &часу:",
    L"Шрифт на &часа:",
    L"Фонт на &времето:",
    L"Фонт &времена:",
    L"Шрифт &часу:",
    L"Шрифт &времени:"
};

const wchar_t* PANEL_BOTTOM_FONT_LABELS[LANG_COUNT] = {
    L"Písmo &spodního řádku:",
    L"&Bottom row font:",
    L"Schrift der &unteren Zeile:",
    L"Police de la ligne &inférieure :",
    L"Fuente de la línea &inferior:",
    L"Carattere riga &inferiore:",
    L"Czcionka &dolnego wiersza:",
    L"Písmo &spodného riadka:",
    L"&Bottom row font:",
    L"&Bottom row font:",
    L"Tipo de letra da linha &inferior:",
    L"Skrift for &nederste rad:",
    L"Teckensnitt för &nedersta raden:",
    L"&Alarivin fontti:",
    L"Skrifttype for &nederste linje:",
    L"Letur &neðri línu:",
    L"&Alt satır yazı tipi:",
    L"&Alumise rea font:",
    L"Cló na sraithe &íochtaraí:",
    L"&Apatinės eilutės šriftas:",
    L"&Apakšējās rindas fonts:",
    L"&Alsó sor betűtípusa:",
    L"Font tar-ringiela ta’ &isfel:",
    L"Lettertype &onderste rij:",
    L"Font rând &inferior:",
    L"Γραμματοσειρά &κάτω:",
    L"Font &donjeg reda:",
    L"Font &donjeg retka:",
    L"Pisava &spodnje vrstice:",
    L"Font &donjeg reda:",
    L"Шрыфт &ніжняга радка:",
    L"Шрифт на &долния ред:",
    L"Фонт на &долниот ред:",
    L"Фонт &доњег реда:",
    L"Шрифт &нижнього рядка:",
    L"Шрифт &нижней строки:"
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
    L"&Varsayılan",
    L"&Vaikesäte",
    L"&Réamhshocrú",
    L"&Numatytasis",
    L"&Noklusējums",
    L"&Alapértelmezett",
    L"&Default",
    L"&Standaard",
    L"&Implicit",
    L"&Προεπιλογή",
    L"&Podrazumijevano",
    L"&Zadano",
    L"&Privzeto",
    L"&Podrazumijevano",
    L"&Прадвызначаны",
    L"По &подразбиране",
    L"&Стандардно",
    L"&Подразумевано",
    L"За &замовчуванням",
    L"По &умолчанию"
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
    L"Alarm &text colour…",
    L"Alarm &text colour…",
    L"Cor do &texto do alarme…",
    L"Alarmens &tekstfarge…",
    L"Alarmets &textfärg…",
    L"Herätyksen &tekstiväri…",
    L"Alarmens &tekstfarve…",
    L"&Textalitur vekjara…",
    L"Alarm &metin rengi…",
    L"Äratuse &teksti värv…",
    L"Dath &téacs an aláraim…",
    L"Žadintuvo &teksto spalva…",
    L"Modinātāja &teksta krāsa…",
    L"Ébresztés &szövegszíne…",
    L"Kulur tat-&test tal-allarm…",
    L"Alarm&tekstkleur…",
    L"Culoare &text alarmă…",
    L"Χρώμα &κειμένου αφύπνισης…",
    L"Boja &teksta alarma…",
    L"Boja &teksta alarma…",
    L"Barva &besedila budilke…",
    L"Boja &teksta alarma…",
    L"Колер &тэксту будзільніка…",
    L"Цвят на &текста при аларма…",
    L"Боја на &текстот при аларм…",
    L"Боја &текста аларма…",
    L"Колір &тексту будильника…",
    L"Цвет &текста будильника…"
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
    L"Alarm &arka planı…",
    L"Äratuse &taustavärv…",
    L"&Cúlra an aláraim…",
    L"Žadintuvo &fono spalva…",
    L"Modinātāja &fona krāsa…",
    L"Ébresztés &háttérszíne…",
    L"&Sfond tal-allarm…",
    L"Alarm&achtergrond…",
    L"&Fundal alarmă…",
    L"&Φόντο αφύπνισης…",
    L"Boja &pozadine alarma…",
    L"Boja &pozadine alarma…",
    L"Barva &ozadja budilke…",
    L"Boja &pozadine alarma…",
    L"Колер &фону будзільніка…",
    L"Цвят на &фона при аларма…",
    L"Боја на &заднината при аларм…",
    L"Боја &позадине аларма…",
    L"Колір &тла будильника…",
    L"Цвет &фона будильника…"
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
    L"&Dolgu:",
    L"&Siseveeris:",
    L"&Spásáil inmheánach:",
    L"&Vidinė paraštė:",
    L"&Iekšējā atkāpe:",
    L"&Belső margó:",
    L"&Spazju intern:",
    L"&Binnenmarge:",
    L"&Spațiere interioară:",
    L"&Εσωτερικό περιθώριο:",
    L"&Unutrašnji razmak:",
    L"&Unutarnji razmak:",
    L"&Notranji odmik:",
    L"&Unutrašnji razmak:",
    L"Унутраны &водступ:",
    L"Вътрешен &отстъп:",
    L"Внатрешна &маргина:",
    L"&Унутрашњи размак:",
    L"Внутрішній &відступ:",
    L"Внутренний &отступ:"
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
    L"&Çerçeve stili:",
    L"&Äärise laad:",
    L"&Stíl na himlíne:",
    L"&Kraštinės stilius:",
    L"&Apmales stils:",
    L"&Szegély stílusa:",
    L"&Stil tal-bordura:",
    L"&Randstijl:",
    L"&Stil bordură:",
    L"&Στυλ περιγράμματος:",
    L"&Stil obruba:",
    L"&Stil obruba:",
    L"&Slog obrobe:",
    L"&Stil okvira:",
    L"Стыль &рамкі:",
    L"Стил на &рамката:",
    L"Стил на &рамката:",
    L"&Стил оквира:",
    L"Стиль &рамки:",
    L"Стиль &рамки:"
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
    L"Çerçeve rengi…",
    L"Äärise värv…",
    L"Dath na himlíne…",
    L"Kraštinės spalva…",
    L"Apmales krāsa…",
    L"Szegély színe…",
    L"Kulur tal-bordura…",
    L"Randkleur…",
    L"Culoare bordură…",
    L"Χρώμα περιγράμματος…",
    L"Boja obruba…",
    L"Boja obruba…",
    L"Barva obrobe…",
    L"Boja okvira…",
    L"Колер рамкі…",
    L"Цвят на рамката…",
    L"Боја на рамката…",
    L"Боја оквира…",
    L"Колір рамки…",
    L"Цвет рамки…"
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
    L"Çerçeve &genişliği:",
    L"Äärise &laius:",
    L"&Leithead na himlíne:",
    L"Kraštinės &plotis:",
    L"Apmales &platums:",
    L"Szegély &vastagsága:",
    L"&Wisa’ tal-bordura:",
    L"Rand&breedte:",
    L"&Grosime bordură:",
    L"&Πλάτος περιγράμματος:",
    L"&Širina obruba:",
    L"&Širina obruba:",
    L"&Širina obrobe:",
    L"&Širina okvira:",
    L"&Таўшчыня рамкі:",
    L"&Дебелина на рамката:",
    L"&Дебелина на рамката:",
    L"&Ширина оквира:",
    L"&Товщина рамки:",
    L"&Толщина рамки:"
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
    L"Saat %d",
    L"Kell %d",
    L"Clog %d",
    L"Laikrodis %d",
    L"Pulkstenis %d",
    L"%d. óra",
    L"Arloġġ %d",
    L"Klok %d",
    L"Ceas %d",
    L"Ρολόι %d",
    L"Sat %d",
    L"Sat %d",
    L"Ura %d",
    L"Sat %d",
    L"Гадзіннік %d",
    L"Часовник %d",
    L"Часовник %d",
    L"Сат %d",
    L"Годинник %d",
    L"Часы %d"
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
    L"Saat %d göster",
    L"Kuva kell %d",
    L"Taispeáin clog %d",
    L"Rodyti laikrodį %d",
    L"Rādīt pulksteni %d",
    L"%d. óra megjelenítése",
    L"Uri l-arloġġ %d",
    L"Klok %d weergeven",
    L"Afișare ceas %d",
    L"Εμφάνιση ρολογιού %d",
    L"Prikaži sat %d",
    L"Prikaži sat %d",
    L"Pokaži uro %d",
    L"Prikaži sat %d",
    L"Паказваць гадзіннік %d",
    L"Показвай часовник %d",
    L"Прикажувај часовник %d",
    L"Прикажи сат %d",
    L"Показувати годинник %d",
    L"Показывать часы %d"
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
    L"Saat biçimi:",
    L"Kellaajavorming:",
    L"Formáid ama:",
    L"Laiko formatas:",
    L"Laika formāts:",
    L"Időformátum:",
    L"Format tal-ħin:",
    L"Tijdnotatie:",
    L"Format oră:",
    L"Μορφή ώρας:",
    L"Oblik vremena:",
    L"Oblik vremena:",
    L"Oblika časa:",
    L"Oblik vremena:",
    L"Фармат часу:",
    L"Формат на часа:",
    L"Облик на времето:",
    L"Облик времена:",
    L"Формат часу:",
    L"Формат времени:"
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
    { L"Dile göre", L"12 saat", L"24 saat" },
    { L"Keele vaikesäte", L"12 tundi", L"24 tundi" },
    { L"De réir na teanga", L"12 uair", L"24 uair" },
    { L"Pagal kalbą", L"12 valandų", L"24 valandos" },
    { L"Atbilstoši valodai", L"12 stundas", L"24 stundas" },
    { L"Nyelv szerinti", L"12 órás", L"24 órás" },
    { L"Skont il-lingwa", L"12-il siegħa", L"24 siegħa" },
    { L"Volgens taal", L"12 uur", L"24 uur" },
    { L"Conform limbii", L"12 ore", L"24 de ore" },
    { L"Σύμφωνα με τη γλώσσα", L"12 ώρες", L"24 ώρες" },
    { L"Prema jeziku", L"12 sati", L"24 sata" },
    { L"Prema jeziku", L"12 sati", L"24 sata" },
    { L"Glede na jezik", L"12 ur", L"24 ur" },
    { L"Prema jeziku", L"12 sati", L"24 sata" },
    { L"Паводле мовы", L"12 гадзін", L"24 гадзіны" },
    { L"Според езика", L"12 часа", L"24 часа" },
    { L"Според јазикот", L"12 часа", L"24 часа" },
    { L"Према језику", L"12 сати", L"24 сата" },
    { L"За мовою", L"12 годин", L"24 години" },
    { L"По языку", L"12 часов", L"24 часа" }
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
    { L"Göster", L"Yer ayır", L"Yer ayırma" },
    { L"Kuva", L"Säilita ruum", L"Ilma ruumita" },
    { L"Taispeáin", L"Coinnigh an spás", L"Gan spás" },
    { L"Rodyti", L"Palikti vietą", L"Be vietos" },
    { L"Rādīt", L"Saglabāt vietu", L"Bez vietas" },
    { L"Megjelenítés", L"Hely megtartása", L"Hely nélkül" },
    { L"Uri", L"Żomm l-ispazju", L"Bla spazju" },
    { L"Weergeven", L"Ruimte behouden", L"Zonder ruimte" },
    { L"Afișare", L"Păstrare spațiu", L"Fără spațiu" },
    { L"Εμφάνιση", L"Διατήρηση χώρου", L"Χωρίς χώρο" },
    { L"Prikaži", L"Zadrži razmak", L"Bez razmaka" },
    { L"Prikaži", L"Zadrži razmak", L"Bez razmaka" },
    { L"Pokaži", L"Ohrani prostor", L"Brez prostora" },
    { L"Prikaži", L"Zadrži razmak", L"Bez razmaka" },
    { L"Паказваць", L"Пакідаць месца", L"Без месца" },
    { L"Показвай", L"Запази мястото", L"Без място" },
    { L"Прикажувај", L"Зачувај место", L"Без место" },
    { L"Прикажи", L"Задржи размак", L"Без размака" },
    { L"Показувати", L"Залишати місце", L"Без місця" },
    { L"Показывать", L"Оставлять место", L"Без места" }
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
    L"Zaman sinyali sesi:",
    L"Ajasignaali heli:",
    L"Fuaim an chomhartha ama:",
    L"Laiko signalo garsas:",
    L"Laika signāla skaņa:",
    L"Időjelzés hangja:",
    L"Ħoss tas-sinjal tal-ħin:",
    L"Geluid tijdsignaal:",
    L"Sunet semnal orar:",
    L"Ήχος σήματος ώρας:",
    L"Zvuk vremenskog signala:",
    L"Zvuk vremenskog signala:",
    L"Zvok časovnega signala:",
    L"Zvuk vremenskog signala:",
    L"Гук сігналу часу:",
    L"Звук на сигнала за време:",
    L"Звук на временскиот сигнал:",
    L"Звук временског сигнала:",
    L"Звук сигналу часу:",
    L"Звук сигнала времени:"
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
    L"Ses düzeyi:",
    L"Helitugevus:",
    L"Airde na fuaime:",
    L"Garsumas:",
    L"Skaļums:",
    L"Hangerő:",
    L"Volum tal-awdjo:",
    L"Geluidsvolume:",
    L"Volum audio:",
    L"Ένταση ήχου:",
    L"Glasnoća zvuka:",
    L"Glasnoća zvuka:",
    L"Glasnost zvoka:",
    L"Jačina zvuka:",
    L"Гучнасць гуку:",
    L"Сила на звука:",
    L"Гласност на звукот:",
    L"Јачина звука:",
    L"Гучність звуку:",
    L"Громкость звука:"
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
    L"Zaman sinyali ses düzeyi:",
    L"Ajasignaali helitugevus:",
    L"Airde an chomhartha ama:",
    L"Laiko signalo garsumas:",
    L"Laika signāla skaļums:",
    L"Időjelzés hangereje:",
    L"Volum tas-sinjal tal-ħin:",
    L"Volume tijdsignaal:",
    L"Volum semnal orar:",
    L"Ένταση σήματος ώρας:",
    L"Glasnoća vremenskog signala:",
    L"Glasnoća vremenskog signala:",
    L"Glasnost časovnega signala:",
    L"Jačina vremenskog signala:",
    L"Гучнасць сігналу часу:",
    L"Сила на сигнала за време:",
    L"Гласност на временскиот сигнал:",
    L"Јачина временског сигнала:",
    L"Гучність сигналу часу:",
    L"Громкость сигнала времени:"
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
    L"Sistem bip sesi",
    L"Süsteemi helisignaal",
    L"Bíp an chórais",
    L"Sistemos pyptelėjimas",
    L"Sistēmas pīkstiens",
    L"Rendszerhang",
    L"Ħoss tas-sistema",
    L"Systeempiep",
    L"Bip de sistem",
    L"Ήχος συστήματος",
    L"Zvuk sistema",
    L"Zvuk sustava",
    L"Sistemski pisk",
    L"Sistemski zvučni signal",
    L"Сістэмны сігнал",
    L"Системен сигнал",
    L"Системски сигнал",
    L"Системски звучни сигнал",
    L"Системний сигнал",
    L"Системный сигнал"
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
    L"Yerleşik üreteç",
    L"Sisseehitatud generaator",
    L"Gineadóir ionsuite",
    L"Įtaisytasis generatorius",
    L"Iebūvēts ģenerators",
    L"Beépített generátor",
    L"Ġeneratur integrat",
    L"Ingebouwde generator",
    L"Generator încorporat",
    L"Ενσωματωμένη γεννήτρια",
    L"Ugrađeni generator",
    L"Ugrađeni generator",
    L"Vgrajeni generator",
    L"Ugrađeni generator",
    L"Убудаваны генератар",
    L"Вграден генератор",
    L"Вграден генератор",
    L"Уграђени генератор",
    L"Вбудований генератор",
    L"Встроенный генератор"
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
    L"Sinyal",
    L"Signaal",
    L"Comhartha",
    L"Signalas",
    L"Signāls",
    L"Időjelzés",
    L"Sinjal",
    L"Signaal",
    L"Semnal",
    L"Σήμα",
    L"Signal",
    L"Signal",
    L"Signal",
    L"Signal",
    L"Сігнал",
    L"Сигнал",
    L"Сигнал",
    L"Сигнал",
    L"Сигнал",
    L"Сигнал"
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
    L"&Sinyal",
    L"&Signaal",
    L"&Comhartha",
    L"&Signalas",
    L"&Signāls",
    L"&Időjelzés",
    L"&Sinjal",
    L"&Signaal",
    L"&Semnal",
    L"&Σήμα",
    L"&Signal",
    L"&Signal",
    L"&Signal",
    L"&Signal",
    L"&Сігнал",
    L"&Сигнал",
    L"&Сигнал",
    L"&Сигнал",
    L"&Сигнал",
    L"&Сигнал"
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
    L"Aikamerkki &käytössä",
    L"Tidssignal &aktivt",
    L"Tímamerki &virkt",
    L"Zaman sinyali &etkin",
    L"Ajasignaal &lubatud",
    L"Comhartha ama &gníomhach",
    L"Laiko signalas &įjungtas",
    L"Laika signāls &ieslēgts",
    L"Időjelzés &engedélyezve",
    L"Sinjal tal-ħin &attivat",
    L"Tijdsignaal &ingeschakeld",
    L"Semnal orar &activat",
    L"Σήμα ώρας &ενεργό",
    L"Vremenski signal &uključen",
    L"Vremenski signal &uključen",
    L"Časovni signal &vključen",
    L"Vremenski signal &uključen",
    L"Сігнал часу &ўключаны",
    L"Сигналът за време е &включен",
    L"Временскиот сигнал е &вклучен",
    L"Временски сигнал &укључен",
    L"Сигнал часу &увімкнено",
    L"Сигнал времени &включён"
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
    }, {
        L"Puudub",
        L"Iga minut",
        L"Iga 5 minuti järel",
        L"Iga 10 minuti järel",
        L"Iga 15 minuti järel",
        L"Iga 20 minuti järel",
        L"Iga 30 minuti järel",
        L"Iga tund"
    }, {
        L"Gan chomhartha",
        L"Gach nóiméad",
        L"Gach 5 nóiméad",
        L"Gach 10 nóiméad",
        L"Gach 15 nóiméad",
        L"Gach 20 nóiméad",
        L"Gach 30 nóiméad",
        L"Gach uair"
    }, {
        L"Nėra",
        L"Kas minutę",
        L"Kas 5 minutes",
        L"Kas 10 minučių",
        L"Kas 15 minučių",
        L"Kas 20 minučių",
        L"Kas 30 minučių",
        L"Kas valandą"
    }, {
        L"Nav",
        L"Katru minūti",
        L"Ik pēc 5 minūtēm",
        L"Ik pēc 10 minūtēm",
        L"Ik pēc 15 minūtēm",
        L"Ik pēc 20 minūtēm",
        L"Ik pēc 30 minūtēm",
        L"Katru stundu"
    }, {
        L"Nincs",
        L"Percenként",
        L"5 percenként",
        L"10 percenként",
        L"15 percenként",
        L"20 percenként",
        L"30 percenként",
        L"Óránként"
    }, {
        L"Xejn",
        L"Kull minuta",
        L"Kull 5 minuti",
        L"Kull 10 minuti",
        L"Kull 15-il minuta",
        L"Kull 20 minuta",
        L"Kull 30 minuta",
        L"Kull siegħa"
    }, {
        L"Geen",
        L"Elke minuut",
        L"Elke 5 minuten",
        L"Elke 10 minuten",
        L"Elk kwartier",
        L"Elke 20 minuten",
        L"Elk halfuur",
        L"Elk uur"
    }, {
        L"Niciunul",
        L"La fiecare minut",
        L"La fiecare 5 minute",
        L"La fiecare 10 minute",
        L"La fiecare 15 minute",
        L"La fiecare 20 de minute",
        L"La fiecare 30 de minute",
        L"La fiecare oră"
    }, {
        L"Κανένα",
        L"Κάθε λεπτό",
        L"Κάθε 5 λεπτά",
        L"Κάθε 10 λεπτά",
        L"Κάθε 15 λεπτά",
        L"Κάθε 20 λεπτά",
        L"Κάθε 30 λεπτά",
        L"Κάθε ώρα"
    }, {
        L"Nema",
        L"Svake minute",
        L"Svakih 5 minuta",
        L"Svakih 10 minuta",
        L"Svakih 15 minuta",
        L"Svakih 20 minuta",
        L"Svakih 30 minuta",
        L"Svakog sata"
    }, {
        L"Nema",
        L"Svake minute",
        L"Svakih 5 minuta",
        L"Svakih 10 minuta",
        L"Svakih 15 minuta",
        L"Svakih 20 minuta",
        L"Svakih 30 minuta",
        L"Svakog sata"
    }, {
        L"Brez",
        L"Vsako minuto",
        L"Vsakih 5 minut",
        L"Vsakih 10 minut",
        L"Vsakih 15 minut",
        L"Vsakih 20 minut",
        L"Vsakih 30 minut",
        L"Vsako uro"
    }, {
        L"Nema",
        L"Svakog minuta",
        L"Svakih 5 minuta",
        L"Svakih 10 minuta",
        L"Svakih 15 minuta",
        L"Svakih 20 minuta",
        L"Svakih 30 minuta",
        L"Svakog sata"
    }, {
        L"Няма",
        L"Кожную хвіліну",
        L"Кожныя 5 хвілін",
        L"Кожныя 10 хвілін",
        L"Кожныя 15 хвілін",
        L"Кожныя 20 хвілін",
        L"Кожныя 30 хвілін",
        L"Кожную гадзіну"
    }, {
        L"Няма",
        L"Всяка минута",
        L"На всеки 5 минути",
        L"На всеки 10 минути",
        L"На всеки 15 минути",
        L"На всеки 20 минути",
        L"На всеки 30 минути",
        L"Всеки час"
    }, {
        L"Нема",
        L"Секоја минута",
        L"На секои 5 минути",
        L"На секои 10 минути",
        L"На секои 15 минути",
        L"На секои 20 минути",
        L"На секои 30 минути",
        L"Секој час"
    }, {
        L"Нема",
        L"Сваког минута",
        L"Сваких 5 минута",
        L"Сваких 10 минута",
        L"Сваких 15 минута",
        L"Сваких 20 минута",
        L"Сваких 30 минута",
        L"Сваког сата"
    }, {
        L"Немає",
        L"Щохвилини",
        L"Кожні 5 хвилин",
        L"Кожні 10 хвилин",
        L"Кожні 15 хвилин",
        L"Кожні 20 хвилин",
        L"Кожні 30 хвилин",
        L"Щогодини"
    }, {
        L"Нет",
        L"Каждую минуту",
        L"Каждые 5 минут",
        L"Каждые 10 минут",
        L"Каждые 15 минут",
        L"Каждые 20 минут",
        L"Каждые 30 минут",
        L"Каждый час"
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
    L"sinyalleri yalnızca bir kez çalınır.",
    L"Greenwichi ajasignaal (GTS): viimasel viiel sekundil kõlab viis lühikest tooni ja valitud ajahetkel pikk"
    L" toon. Mitme vidina samaaegsed signaalid esitatakse vaid üks kord.",
    L"Comhartha Ama Greenwich (GTS): cúig bhíp ghearra sna cúig shoicind dheireanacha agus bíp fhada ag an am "
    L"roghnaithe go beacht. Seinntear comharthaí comhuaineacha ó roinnt giuirléidí uair amháin.",
    L"Grinvičo laiko signalas (GTS): penki trumpi tonai paskutines penkias sekundes ir ilgas tonas tiksliai "
    L"pasirinktu laiku. Vienalaikiai kelių valdiklių signalai leidžiami tik vieną kartą.",
    L"Griničas laika signāls (GTS): pieci īsi toņi pēdējās piecās sekundēs un garš tonis tieši izvēlētajā "
    L"laika robežā. Vairāku logrīku vienlaicīgie signāli tiek atskaņoti tikai vienreiz.",
    L"Greenwichi időjelzés (GTS): az utolsó öt másodpercben öt rövid hang, a kiválasztott időhatáron pedig egy"
    L" hosszú hang szól. Több minialkalmazás egyidejű jelzése csak egyszer hangzik el.",
    L"Is-Sinjal tal-Ħin ta’ Greenwich (GTS): ħames toni qosra fl-aħħar ħames sekondi u ton twil eżatt fil-ħin "
    L"magħżul. Sinjali simultanji minn diversi widgets jindaqqu darba biss.",
    L"Greenwich Time Signal (GTS): vijf korte tonen in de laatste vijf seconden en een lange toon precies op "
    L"het gekozen tijdstip. Gelijktijdige signalen van meerdere widgets worden maar eenmaal afgespeeld.",
    L"Semnalul orar Greenwich (GTS): cinci tonuri scurte în ultimele cinci secunde și un ton lung exact la "
    L"momentul ales. Semnalele simultane ale mai multor widgeturi sunt redate o singură dată.",
    L"Σήμα ώρας Γκρίνουιτς (GTS): πέντε σύντομοι τόνοι στα τελευταία πέντε δευτερόλεπτα και ένας παρατεταμένος"
    L" τόνος ακριβώς στην επιλεγμένη χρονική στιγμή. Ταυτόχρονα σήματα πολλών γραφικών στοιχείων ακούγονται "
    L"μόνο μία φορά.",
    L"Greenwich Time Signal (GTS): pet kratkih tonova tokom posljednjih pet sekundi i jedan dugi ton tačno na "
    L"odabranoj vremenskoj granici. Istovremeni signali više vidžeta reproduciraju se samo jednom.",
    L"Greenwich Time Signal (GTS): pet kratkih tonova tijekom posljednjih pet sekundi i jedan dugi ton točno "
    L"na odabranoj vremenskoj granici. Istodobni signali više widgeta reproduciraju se samo jednom.",
    L"Greenwich Time Signal (GTS): pet kratkih piskov v zadnjih petih sekundah in dolg pisk natanko na izbrani"
    L" časovni meji. Sočasni signali več gradnikov se predvajajo le enkrat.",
    L"Grinički vremenski signal (GTS): pet kratkih tonova tokom posljednjih pet sekundi i dugi ton tačno na "
    L"izabranoj vremenskoj granici. Istovremeni signali više vidžeta puštaju se samo jednom.",
    L"Грынвіцкі сігнал часу (GTS): пяць кароткіх сігналаў у апошнія пяць секунд і доўгі сігнал дакладна на "
    L"выбранай часовай мяжы. Адначасовыя сігналы некалькіх віджэтаў гучаць толькі адзін раз.",
    L"Гринуички сигнал за време (GTS): пет кратки тона през последните пет секунди и дълъг тон точно на "
    L"избраната времева граница. Едновременните сигнали на няколко модула се възпроизвеждат само веднъж.",
    L"Гринички временски сигнал (GTS): пет кратки тона во последните пет секунди и долг тон точно на избраната"
    L" временска граница. Истовремените сигнали од повеќе виџети се пуштаат само еднаш.",
    L"Гринички временски сигнал (GTS): пет кратких тонова током последњих пет секунди и дуги тон тачно на "
    L"изабраној временској граници. Истовремени сигнали више виџета пуштају се само једном.",
    L"Гринвіцький сигнал часу (GTS): п’ять коротких сигналів протягом останніх п’яти секунд і довгий сигнал "
    L"точно на вибраній часовій межі. Одночасні сигнали кількох віджетів відтворюються лише один раз.",
    L"Гринвичский сигнал времени (GTS): пять коротких сигналов в течение последних пяти секунд и длинный сигнал"
    L" точно на выбранной временной границе. Одновременные сигналы нескольких виджетов воспроизводятся только "
    L"один раз."
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
    L"Zaman",
    L"Aeg",
    L"Am",
    L"Laikas",
    L"Laiks",
    L"Idő",
    L"Ħin",
    L"Tijd",
    L"Oră",
    L"Ώρα",
    L"Vrijeme",
    L"Vrijeme",
    L"Čas",
    L"Vrijeme",
    L"Час",
    L"Време",
    L"Време",
    L"Време",
    L"Час",
    L"Время"
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
    L"Zaman &kaynağı:",
    L"Aja &allikas:",
    L"&Foinse ama:",
    L"Laiko &šaltinis:",
    L"Laika &avots:",
    L"Idő&forrás:",
    L"&Sors tal-ħin:",
    L"Tijd&bron:",
    L"&Sursă de timp:",
    L"&Πηγή ώρας:",
    L"&Izvor vremena:",
    L"&Izvor vremena:",
    L"&Vir časa:",
    L"&Izvor vremena:",
    L"Крыніца &часу:",
    L"&Източник на време:",
    L"&Извор на време:",
    L"&Извор времена:",
    L"Джерело &часу:",
    L"Источник &времени:"
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
    L"Windows sistem zamanı",
    L"Windowsi süsteemiaeg",
    L"Am córais Windows",
    L"„Windows“ sistemos laikas",
    L"Windows sistēmas laiks",
    L"Windows rendszerideje",
    L"Ħin tas-sistema Windows",
    L"Windows-systeemtijd",
    L"Ora sistemului Windows",
    L"Ώρα συστήματος Windows",
    L"Sistemsko vrijeme Windowsa",
    L"Sustavsko vrijeme Windowsa",
    L"Sistemski čas Windows",
    L"Sistemsko vrijeme Windows-a",
    L"Сістэмны час Windows",
    L"Системно време на Windows",
    L"Системско време на Windows",
    L"Системско време Windows-а",
    L"Системний час Windows",
    L"Системное время Windows"
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
    L"NTP sunucularından zaman",
    L"Aeg NTP-serveritest",
    L"Am ó fhreastalaithe NTP",
    L"Laikas iš NTP serverių",
    L"Laiks no NTP serveriem",
    L"NTP-kiszolgálók ideje",
    L"Ħin minn servers NTP",
    L"Tijd van NTP-servers",
    L"Ora de la servere NTP",
    L"Ώρα από διακομιστές NTP",
    L"Vrijeme s NTP servera",
    L"Vrijeme s NTP poslužitelja",
    L"Čas iz strežnikov NTP",
    L"Vrijeme sa NTP servera",
    L"Час з сервераў NTP",
    L"Време от NTP сървъри",
    L"Време од сервери NTP",
    L"Време са NTP сервера",
    L"Час із серверів NTP",
    L"Время с серверов NTP"
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
    L"&NTP sunucuları (noktalı virgülle ayrılmış):",
    L"&NTP-serverid (eraldage semikooloniga):",
    L"&Freastalaithe NTP (scartha le leathstadanna):",
    L"&NTP serveriai (atskirti kabliataškiais):",
    L"&NTP serveri (atdalīti ar semikolu):",
    L"&NTP-kiszolgálók (pontosvesszővel elválasztva):",
    L"&Servers NTP (separati b’punt u virgola):",
    L"&NTP-servers (gescheiden door puntkomma’s):",
    L"&Servere NTP (separate prin punct și virgulă):",
    L"&Διακομιστές NTP (διαχωρισμός με ;):",
    L"&NTP serveri (odvojeni tačkom sa zarezom):",
    L"&NTP poslužitelji (odvojeni točkom sa zarezom):",
    L"&Strežniki NTP (ločeni s podpičji):",
    L"&NTP serveri (razdvojeni tačkom i zarezom):",
    L"Серверы &NTP (праз кропку з коскай):",
    L"&NTP сървъри (разделени с точка и запетая):",
    L"&Сервери NTP (одделени со точка-запирка):",
    L"&NTP сервери (раздвојени тачком и зарезом):",
    L"Сервери &NTP (через крапку з комою):",
    L"Серверы &NTP (через точку с запятой):"
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
    L"Varsayılan &küme:",
    L"&Serverirühm:",
    L"&Tacar freastalaithe:",
    L"&Serverių rinkinys:",
    L"&Serveru kopa:",
    L"&Kiszolgálócsoport:",
    L"&Grupp ta’ servers:",
    L"&Servergroep:",
    L"&Grup de servere:",
    L"&Ομάδα διακομιστών:",
    L"&Skup servera:",
    L"&Skup poslužitelja:",
    L"&Nabor strežnikov:",
    L"&Grupa servera:",
    L"&Набор сервераў:",
    L"&Набор сървъри:",
    L"&Група сервери:",
    L"&Група сервера:",
    L"Набір &серверів:",
    L"Набор &серверов:"
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
    }, {
        L"Automaatselt piirkonna järgi",
        L"Tšehhi ja Slovakkia – CESNET/NIC.CZ",
        L"PTB – Saksamaa ja Euroopa",
        L"Ülemaailmne – Ubuntu / NTP Pool",
        L"Kohandatud"
    }, {
        L"Uathoibríoch de réir réigiúin",
        L"An tSeicia agus an tSlóvaic – CESNET/NIC.CZ",
        L"PTB – An Ghearmáin agus an Eoraip",
        L"Ar fud an domhain – Ubuntu / NTP Pool",
        L"Saincheaptha"
    }, {
        L"Automatiškai pagal regioną",
        L"Čekija ir Slovakija – CESNET/NIC.CZ",
        L"PTB – Vokietija ir Europa",
        L"Visas pasaulis – Ubuntu / NTP Pool",
        L"Pasirinktinis"
    }, {
        L"Automātiski pēc reģiona",
        L"Čehija un Slovākija – CESNET/NIC.CZ",
        L"PTB – Vācija un Eiropa",
        L"Visā pasaulē – Ubuntu / NTP Pool",
        L"Pielāgots"
    }, {
        L"Automatikus, régió szerint",
        L"Csehország és Szlovákia – CESNET/NIC.CZ",
        L"PTB – Németország és Európa",
        L"Világszerte – Ubuntu / NTP Pool",
        L"Egyéni"
    }, {
        L"Awtomatiku skont ir-reġjun",
        L"Iċ-Ċekja u s-Slovakkja – CESNET/NIC.CZ",
        L"PTB – Il-Ġermanja u l-Ewropa",
        L"Madwar id-dinja – Ubuntu / NTP Pool",
        L"Personalizzat"
    }, {
        L"Automatisch op basis van regio",
        L"Tsjechië en Slowakije – CESNET/NIC.CZ",
        L"PTB – Duitsland en Europa",
        L"Wereldwijd – Ubuntu / NTP Pool",
        L"Aangepast"
    }, {
        L"Automat, conform regiunii",
        L"Cehia și Slovacia – CESNET/NIC.CZ",
        L"PTB – Germania și Europa",
        L"La nivel mondial – Ubuntu / NTP Pool",
        L"Particularizat"
    }, {
        L"Αυτόματα ανά περιοχή",
        L"Τσεχία και Σλοβακία – CESNET/NIC.CZ",
        L"PTB – Γερμανία και Ευρώπη",
        L"Παγκοσμίως – Ubuntu / NTP Pool",
        L"Προσαρμοσμένη"
    }, {
        L"Automatski prema regiji",
        L"Češka i Slovačka – CESNET/NIC.CZ",
        L"PTB – Njemačka i Europa",
        L"Cijeli svijet – Ubuntu / NTP Pool",
        L"Prilagođeno"
    }, {
        L"Automatski prema regiji",
        L"Češka i Slovačka – CESNET/NIC.CZ",
        L"PTB – Njemačka i Europa",
        L"Cijeli svijet – Ubuntu / NTP Pool",
        L"Prilagođeno"
    }, {
        L"Samodejno glede na regijo",
        L"Češka in Slovaška – CESNET/NIC.CZ",
        L"PTB – Nemčija in Evropa",
        L"Ves svet – Ubuntu / NTP Pool",
        L"Po meri"
    }, {
        L"Automatski prema regionu",
        L"Češka i Slovačka – CESNET/NIC.CZ",
        L"PTB – Njemačka i Evropa",
        L"Cijeli svijet – Ubuntu / NTP Pool",
        L"Prilagođeno"
    }, {
        L"Аўтаматычна паводле рэгіёна",
        L"Чэхія і Славакія – CESNET/NIC.CZ",
        L"PTB – Германія і Еўропа",
        L"Увесь свет – Ubuntu / NTP Pool",
        L"Уласны"
    }, {
        L"Автоматично според региона",
        L"Чехия и Словакия – CESNET/NIC.CZ",
        L"PTB – Германия и Европа",
        L"Цял свят – Ubuntu / NTP Pool",
        L"По избор"
    }, {
        L"Автоматски според регионот",
        L"Чешка и Словачка – CESNET/NIC.CZ",
        L"PTB – Германија и Европа",
        L"Целиот свет – Ubuntu / NTP Pool",
        L"Прилагодено"
    }, {
        L"Аутоматски према региону",
        L"Чешка и Словачка – CESNET/NIC.CZ",
        L"PTB – Немачка и Европа",
        L"Цео свет – Ubuntu / NTP Pool",
        L"Прилагођено"
    }, {
        L"Автоматично за регіоном",
        L"Чехія та Словаччина — CESNET/NIC.CZ",
        L"PTB — Німеччина та Європа",
        L"Увесь світ — Ubuntu / NTP Pool",
        L"Власний"
    }, {
        L"Автоматически по региону",
        L"Чехия и Словакия — CESNET/NIC.CZ",
        L"PTB — Германия и Европа",
        L"Весь мир — Ubuntu / NTP Pool",
        L"Свой"
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
    L"&Synchronise now",
    L"&Synchronise now",
    L"&Sincronizar agora",
    L"&Synkroniser nå",
    L"&Synkronisera nu",
    L"&Synkronoi nyt",
    L"&Synkroniser nu",
    L"&Samstilla núna",
    L"Şimdi &eşitle",
    L"&Sünkrooni kohe",
    L"&Sioncronaigh anois",
    L"&Sinchronizuoti dabar",
    L"&Sinhronizēt tūlīt",
    L"&Szinkronizálás most",
    L"&Issinkronizza issa",
    L"Nu &synchroniseren",
    L"&Sincronizare acum",
    L"&Συγχρονισμός τώρα",
    L"&Sinhroniziraj sada",
    L"&Sinkroniziraj sada",
    L"&Sinhroniziraj zdaj",
    L"&Sinhronizuj sada",
    L"&Сінхранізаваць зараз",
    L"&Синхронизирай сега",
    L"&Синхронизирај сега",
    L"&Синхронизуј сада",
    L"&Синхронізувати зараз",
    L"&Синхронизировать сейчас"
};

const wchar_t* NTP_LOG_COLUMN_LABELS[LANG_COUNT][3] = {
    { L"Datum a čas", L"Server NTP", L"Stav" },
    { L"Date and time", L"NTP server", L"Status" },
    { L"Datum und Uhrzeit", L"NTP-Server", L"Status" },
    { L"Date et heure", L"Serveur NTP", L"État" },
    { L"Fecha y hora", L"Servidor NTP", L"Estado" },
    { L"Data e ora", L"Server NTP", L"Stato" },
    { L"Data i godzina", L"Serwer NTP", L"Stan" },
    { L"Dátum a čas", L"Server NTP", L"Stav" },
    { L"Date and time", L"NTP server", L"Status" },
    { L"Date and time", L"NTP server", L"Status" },
    { L"Data e hora", L"Servidor NTP", L"Estado" },
    { L"Dato og klokkeslett", L"NTP-server", L"Status" },
    { L"Datum och tid", L"NTP-server", L"Status" },
    { L"Päivämäärä ja aika", L"NTP-palvelin", L"Tila" },
    { L"Dato og klokkeslæt", L"NTP-server", L"Status" },
    { L"Dagsetning og tími", L"NTP-þjónn", L"Staða" },
    { L"Tarih ve saat", L"NTP sunucusu", L"Durum" },
    { L"Kuupäev ja kellaaeg", L"NTP-server", L"Olek" },
    { L"Dáta agus am", L"Freastalaí NTP", L"Stádas" },
    { L"Data ir laikas", L"NTP serveris", L"Būsena" },
    { L"Datums un laiks", L"NTP serveris", L"Statuss" },
    { L"Dátum és idő", L"NTP-kiszolgáló", L"Állapot" },
    { L"Data u ħin", L"Server NTP", L"Status" },
    { L"Datum en tijd", L"NTP-server", L"Status" },
    { L"Data și ora", L"Server NTP", L"Stare" },
    { L"Ημερομηνία και ώρα", L"Διακομιστής NTP", L"Κατάσταση" },
    { L"Datum i vrijeme", L"NTP server", L"Stanje" },
    { L"Datum i vrijeme", L"NTP poslužitelj", L"Stanje" },
    { L"Datum in čas", L"Strežnik NTP", L"Stanje" },
    { L"Datum i vrijeme", L"NTP server", L"Stanje" },
    { L"Дата і час", L"Сервер NTP", L"Стан" },
    { L"Дата и час", L"NTP сървър", L"Състояние" },
    { L"Датум и време", L"Сервер NTP", L"Состојба" },
    { L"Датум и време", L"NTP сервер", L"Стање" },
    { L"Дата й час", L"Сервер NTP", L"Стан" },
    { L"Дата и время", L"Сервер NTP", L"Состояние" }
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
    }, {
        L"Vigane NTP-vastus",
        L"Serveri nime lahendamine nurjus",
        L"Võrgutõrge",
        L"Vastuse ooteaeg lõppes"
    }, {
        L"Freagra NTP neamhbhailí",
        L"Theip ar réiteach ainm an fhreastalaí",
        L"Earráid líonra",
        L"Chuaigh an freagra thar am"
    }, {
        L"Netinkamas NTP atsakymas",
        L"Nepavyko nustatyti serverio adreso",
        L"Tinklo klaida",
        L"Baigėsi atsakymo laukimo laikas"
    }, {
        L"Nederīga NTP atbilde",
        L"Neizdevās atrisināt servera nosaukumu",
        L"Tīkla kļūda",
        L"Beidzies atbildes gaidīšanas laiks"
    }, {
        L"Érvénytelen NTP-válasz",
        L"A kiszolgálónév feloldása sikertelen",
        L"Hálózati hiba",
        L"A válasz időkorlátja lejárt"
    }, {
        L"Tweġiba NTP invalida",
        L"Ma setax jiġi riżolt l-isem tas-server",
        L"Żball tan-network",
        L"Skada l-ħin ta’ stennija tat-tweġiba"
    }, {
        L"Ongeldig NTP-antwoord",
        L"Servernaam kan niet worden omgezet",
        L"Netwerkfout",
        L"Time-out bij wachten op antwoord"
    }, {
        L"Răspuns NTP nevalid",
        L"Nu s-a putut rezolva numele serverului",
        L"Eroare de rețea",
        L"Timpul de așteptare a răspunsului a expirat"
    }, {
        L"Μη έγκυρη απάντηση NTP",
        L"Αποτυχία επίλυσης ονόματος διακομιστή",
        L"Σφάλμα δικτύου",
        L"Λήξη χρονικού ορίου απάντησης"
    }, {
        L"Nevaljan NTP odgovor",
        L"Nije moguće razriješiti naziv servera",
        L"Mrežna greška",
        L"Isteklo je vrijeme čekanja odgovora"
    }, {
        L"Nevaljan NTP odgovor",
        L"Nije moguće razriješiti naziv poslužitelja",
        L"Mrežna pogreška",
        L"Isteklo je vrijeme čekanja odgovora"
    }, {
        L"Neveljaven odgovor NTP",
        L"Imena strežnika ni mogoče razrešiti",
        L"Omrežna napaka",
        L"Časovna omejitev odgovora je potekla"
    }, {
        L"Neispravan NTP odgovor",
        L"Nije moguće razriješiti naziv servera",
        L"Mrežna greška",
        L"Isteklo je vrijeme čekanja odgovora"
    }, {
        L"Некарэктны адказ NTP",
        L"Не ўдалося вызначыць адрас сервера",
        L"Памылка сеткі",
        L"Час чакання адказу скончыўся"
    }, {
        L"Невалиден NTP отговор",
        L"Името на сървъра не може да се разреши",
        L"Мрежова грешка",
        L"Времето за изчакване на отговор изтече"
    }, {
        L"Невалиден одговор NTP",
        L"Не може да се одреди адресата на серверот",
        L"Мрежна грешка",
        L"Истече времето за чекање одговор"
    }, {
        L"Неисправан NTP одговор",
        L"Није могуће разрешити назив сервера",
        L"Мрежна грешка",
        L"Истекло је време чекања одговора"
    }, {
        L"Некоректна відповідь NTP",
        L"Не вдалося визначити адресу сервера",
        L"Помилка мережі",
        L"Час очікування відповіді вичерпано"
    }, {
        L"Некорректный ответ NTP",
        L"Не удалось определить адрес сервера",
        L"Ошибка сети",
        L"Время ожидания ответа истекло"
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
    L"Guardar registo",
    L"Lagre logg",
    L"Spara logg",
    L"Tallenna loki",
    L"Gem log",
    L"Vista annál",
    L"Günlüğü kaydet",
    L"Salvesta logi",
    L"Sábháil an logchomhad",
    L"Įrašyti žurnalą",
    L"Saglabāt žurnālu",
    L"Napló mentése",
    L"Issejvja r-reġistru",
    L"Logboek opslaan",
    L"Salvare jurnal",
    L"Αποθήκευση αρχείου καταγραφής",
    L"Sačuvaj zapisnik",
    L"Spremi zapisnik",
    L"Shrani dnevnik",
    L"Sačuvaj dnevnik",
    L"Захаваць журнал",
    L"Запази дневника",
    L"Зачувај дневник",
    L"Сачувај дневник",
    L"Зберегти журнал",
    L"Сохранить журнал"
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
    L"Não foi possível guardar o registo.",
    L"Loggen kunne ikke lagres.",
    L"Loggen kunde inte sparas.",
    L"Lokia ei voitu tallentaa.",
    L"Loggen kunne ikke gemmes.",
    L"Ekki tókst að vista annálinn.",
    L"Günlük kaydedilemedi.",
    L"Logi ei saanud salvestada.",
    L"Níorbh fhéidir an logchomhad a shábháil.",
    L"Nepavyko įrašyti žurnalo.",
    L"Neizdevās saglabāt žurnālu.",
    L"Nem sikerült menteni a naplót.",
    L"Ir-reġistru ma setax jiġi ssejvjat.",
    L"Het logboek kan niet worden opgeslagen.",
    L"Jurnalul nu a putut fi salvat.",
    L"Δεν ήταν δυνατή η αποθήκευση του αρχείου καταγραφής.",
    L"Nije moguće sačuvati zapisnik.",
    L"Nije moguće spremiti zapisnik.",
    L"Dnevnika ni mogoče shraniti.",
    L"Nije moguće sačuvati dnevnik.",
    L"Не ўдалося захаваць журнал.",
    L"Дневникът не може да бъде записан.",
    L"Дневникот не може да се зачува.",
    L"Није могуће сачувати дневник.",
    L"Не вдалося зберегти журнал.",
    L"Не удалось сохранить журнал."
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
    L"The time source and synchronisation apply globally to all widgets.",
    L"The time source and synchronisation apply globally to all widgets.",
    L"A origem e a sincronização da hora aplicam-se globalmente a todos os widgets.",
    L"Tidskilde og synkronisering gjelder globalt for alle widgeter.",
    L"Tidskälla och synkronisering gäller globalt för alla widgetar.",
    L"Aikalähde ja synkronointi koskevat kaikkia pienoisohjelmia.",
    L"Tidskilde og synkronisering gælder globalt for alle widgets.",
    L"Tímagjafi og samstilling gilda fyrir allar græjur.",
    L"Zaman kaynağı ve eşitleme tüm araçlara genel olarak uygulanır.",
    L"Aja allikas ja sünkroonimine kehtivad kõigile vidinatele.",
    L"Baineann an fhoinse ama agus an sioncronú le gach giuirléid.",
    L"Laiko šaltinis ir sinchronizavimas taikomi visiems valdikliams.",
    L"Laika avots un sinhronizācija attiecas uz visiem logrīkiem.",
    L"Az időforrás és a szinkronizálás minden minialkalmazásra érvényes.",
    L"Is-sors tal-ħin u s-sinkronizzazzjoni japplikaw għall-widgets kollha.",
    L"De tijdbron en synchronisatie gelden voor alle widgets.",
    L"Sursa de timp și sincronizarea se aplică tuturor widgeturilor.",
    L"Η πηγή ώρας και ο συγχρονισμός ισχύουν για όλα τα γραφικά στοιχεία.",
    L"Izvor vremena i sinhronizacija vrijede za sve vidžete.",
    L"Izvor vremena i sinkronizacija vrijede za sve widgete.",
    L"Vir časa in sinhronizacija veljata za vse gradnike.",
    L"Izvor vremena i sinhronizacija važe za sve vidžete.",
    L"Крыніца часу і сінхранізацыя дзейнічаюць для ўсіх віджэтаў.",
    L"Източникът на време и синхронизацията важат за всички изпълними модули.",
    L"Изворот на време и синхронизацијата важат за сите виџети.",
    L"Извор времена и синхронизација важе за све виџете.",
    L"Джерело часу та синхронізація застосовуються до всіх віджетів.",
    L"Источник времени и синхронизация применяются ко всем виджетам."
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
    L"Sistem zamanı kullanılıyor; Windows değiştirilmez.",
    L"Kasutatakse süsteemiaega; Windowsi kella ei muudeta.",
    L"Úsáidtear am an chórais; ní athraítear clog Windows.",
    L"Naudojamas sistemos laikas; „Windows“ laikrodis nekeičiamas.",
    L"Tiek izmantots sistēmas laiks; Windows pulkstenis netiek mainīts.",
    L"A rendszeridő van használatban; a Windows órája nem módosul.",
    L"Jintuża l-ħin tas-sistema; l-arloġġ tal-Windows ma jinbidilx.",
    L"De systeemtijd wordt gebruikt; de Windows-klok wordt niet gewijzigd.",
    L"Se utilizează ora sistemului; ceasul Windows nu este modificat.",
    L"Χρησιμοποιείται η ώρα συστήματος· το ρολόι των Windows δεν αλλάζει.",
    L"Koristi se sistemsko vrijeme; sat Windowsa ne mijenja se.",
    L"Koristi se sustavsko vrijeme; sat Windowsa ne mijenja se.",
    L"Uporablja se sistemski čas; ura Windows se ne spreminja.",
    L"Koristi se sistemsko vrijeme; sat Windows-a se ne mijenja.",
    L"Выкарыстоўваецца сістэмны час; гадзіннік Windows не змяняецца.",
    L"Използва се системното време; часовникът на Windows не се променя.",
    L"Се користи системското време; часовникот на Windows не се менува.",
    L"Користи се системско време; сат Windows-а се не мења.",
    L"Використовується системний час; час Windows не змінюється.",
    L"Используется системное время; время Windows не изменяется."
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
    L"Waiting for NTP synchronisation…",
    L"Waiting for NTP synchronisation…",
    L"A aguardar a sincronização NTP…",
    L"Venter på NTP-synkronisering…",
    L"Väntar på NTP-synkronisering…",
    L"Odotetaan NTP-synkronointia…",
    L"Venter på NTP-synkronisering…",
    L"Bíður eftir NTP-samstillingu…",
    L"NTP eşitlemesi bekleniyor…",
    L"NTP-sünkroonimise ootel…",
    L"Ag fanacht le sioncronú NTP…",
    L"Laukiama NTP sinchronizavimo…",
    L"Gaida NTP sinhronizāciju…",
    L"Várakozás az NTP-szinkronizálásra…",
    L"Qed tistenna s-sinkronizzazzjoni NTP…",
    L"Wachten op NTP-synchronisatie…",
    L"Se așteaptă sincronizarea NTP…",
    L"Αναμονή για συγχρονισμό NTP…",
    L"Čekanje NTP sinhronizacije…",
    L"Čekanje NTP sinkronizacije…",
    L"Čakanje na sinhronizacijo NTP…",
    L"Čekanje NTP sinhronizacije…",
    L"Чаканне сінхранізацыі NTP…",
    L"Изчакване на NTP синхронизация…",
    L"Чекање синхронизација NTP…",
    L"Чекање NTP синхронизације…",
    L"Очікування синхронізації NTP…",
    L"Ожидание синхронизации NTP…"
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
    L"NTP sunucuları kullanılamıyor; geçici olarak sistem zamanı kullanılıyor.",
    L"NTP-serverid pole saadaval; ajutiselt kasutatakse süsteemiaega.",
    L"Níl na freastalaithe NTP ar fáil; úsáidtear am an chórais go sealadach.",
    L"NTP serveriai nepasiekiami; laikinai naudojamas sistemos laikas.",
    L"NTP serveri nav pieejami; pagaidām tiek izmantots sistēmas laiks.",
    L"Az NTP-kiszolgálók nem érhetők el; átmenetileg a rendszeridő van használatban.",
    L"Is-servers NTP mhumiex disponibbli; jintuża l-ħin tas-sistema temporanjament.",
    L"NTP-servers zijn niet beschikbaar; tijdelijk wordt de systeemtijd gebruikt.",
    L"Serverele NTP nu sunt disponibile; se utilizează temporar ora sistemului.",
    L"Οι διακομιστές NTP δεν είναι διαθέσιμοι· χρησιμοποιείται προσωρινά η ώρα συστήματος.",
    L"NTP serveri nisu dostupni; privremeno se koristi sistemsko vrijeme.",
    L"NTP poslužitelji nisu dostupni; privremeno se koristi sustavsko vrijeme.",
    L"Strežniki NTP niso dosegljivi; začasno se uporablja sistemski čas.",
    L"NTP serveri nisu dostupni; privremeno se koristi sistemsko vrijeme.",
    L"Серверы NTP недаступныя; часова выкарыстоўваецца сістэмны час.",
    L"NTP сървърите са недостъпни; временно се използва системното време.",
    L"Серверите NTP се недостапни; привремено се користи системското време.",
    L"NTP сервери нису доступни; привремено се користи системско време.",
    L"Сервери NTP недоступні; тимчасово використовується системний час.",
    L"Серверы NTP недоступны; временно используется системное время."
};

const wchar_t* NTP_STATUS_RETAINED[LANG_COUNT] = {
    L"Servery NTP nejsou dostupné; hodiny pokračují od poslední synchronizace:",
    L"NTP servers are unavailable; the clock continues from the last synchronization:",
    L"NTP-Server sind nicht erreichbar; die Uhr läuft ab der letzten Synchronisierung weiter:",
    L"Les serveurs NTP sont indisponibles ; l’horloge continue depuis la dernière synchronisation :",
    L"Los servidores NTP no están disponibles; el reloj continúa desde la última sincronización:",
    L"I server NTP non sono disponibili; l’orologio prosegue dall’ultima sincronizzazione:",
    L"Serwery NTP są niedostępne; zegar kontynuuje odmierzanie od ostatniej synchronizacji:",
    L"Servery NTP nie sú dostupné; hodiny pokračujú od poslednej synchronizácie:",
    L"NTP servers are unavailable; the clock continues from the last synchronisation:",
    L"NTP servers are unavailable; the clock continues from the last synchronisation:",
    L"Os servidores NTP estão indisponíveis; o relógio continua desde a última sincronização:",
    L"NTP-serverne er utilgjengelige; klokken fortsetter fra siste synkronisering:",
    L"NTP-servrarna är inte tillgängliga; klockan fortsätter från den senaste synkroniseringen:",
    L"NTP-palvelimia ei tavoiteta; kello jatkaa viimeisestä synkronoinnista:",
    L"NTP-serverne er ikke tilgængelige; uret fortsætter fra den seneste synkronisering:",
    L"NTP-þjónar eru ekki tiltækir; klukkan heldur áfram frá síðustu samstillingu:",
    L"NTP sunucuları kullanılamıyor; saat son eşitlemeden itibaren ilerlemeye devam ediyor:",
    L"NTP-serverid pole saadaval; kell jätkab viimasest sünkroonimisest:",
    L"Níl na freastalaithe NTP ar fáil; leanann an clog ón sioncronú deireanach:",
    L"NTP serveriai nepasiekiami; laikrodis tęsia nuo paskutinio sinchronizavimo:",
    L"NTP serveri nav pieejami; pulkstenis turpina skaitīt no pēdējās sinhronizācijas:",
    L"Az NTP-kiszolgálók nem érhetők el; az óra az utolsó szinkronizálástól halad tovább:",
    L"Is-servers NTP mhumiex disponibbli; l-arloġġ ikompli mill-aħħar sinkronizzazzjoni:",
    L"NTP-servers zijn niet beschikbaar; de klok loopt door vanaf de laatste synchronisatie:",
    L"Serverele NTP nu sunt disponibile; ceasul continuă de la ultima sincronizare:",
    L"Οι διακομιστές NTP δεν είναι διαθέσιμοι· το ρολόι συνεχίζει από τον τελευταίο συγχρονισμό:",
    L"NTP serveri nisu dostupni; sat nastavlja od posljednje sinhronizacije:",
    L"NTP poslužitelji nisu dostupni; sat nastavlja od posljednje sinkronizacije:",
    L"Strežniki NTP niso dosegljivi; ura teče od zadnje sinhronizacije:",
    L"NTP serveri nisu dostupni; sat nastavlja od posljednje sinhronizacije:",
    L"Серверы NTP недаступныя; гадзіннік працягвае адлік ад апошняй сінхранізацыі:",
    L"NTP сървърите са недостъпни; часовникът продължава от последната синхронизация:",
    L"Серверите NTP се недостапни; часовникот продолжува од последната синхронизација:",
    L"NTP сервери нису доступни; сат наставља од последње синхронизације:",
    L"Сервери NTP недоступні; годинник продовжує відлік від останньої синхронізації:",
    L"Серверы NTP недоступны; часы продолжают отсчёт от последней синхронизации:"
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
    L"Synchronised with",
    L"Synchronised with",
    L"Sincronizado com",
    L"Synkronisert med",
    L"Synkroniserad med",
    L"Synkronoitu palvelimeen",
    L"Synkroniseret med",
    L"Samstillt við",
    L"Şununla eşitlendi",
    L"Sünkroonitud serveriga",
    L"Sioncronaithe le",
    L"Sinchronizuota su",
    L"Sinhronizēts ar",
    L"Szinkronizálva ezzel:",
    L"Issinkronizzat ma’",
    L"Gesynchroniseerd met",
    L"Sincronizat cu",
    L"Συγχρονίστηκε με",
    L"Sinhronizirano s",
    L"Sinkronizirano s",
    L"Sinhronizirano s strežnikom",
    L"Sinhronizovano sa",
    L"Сінхранізавана з",
    L"Синхронизирано с",
    L"Синхронизирано со",
    L"Синхронизовано са",
    L"Синхронізовано з",
    L"Синхронизировано с"
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
    L"Yazı tipi &kenar yumuşatma:",
    L"Fondi &silumine:",
    L"&Frithailiasáil cló:",
    L"Šrifto &glodinimas:",
    L"Fonta &nogludināšana:",
    L"Betűtípus &élsimítása:",
    L"&Anti-aliasing tal-font:",
    L"Lettertype&vereffening:",
    L"&Netezire font:",
    L"Ε&ξομάλυνση γραμματοσειράς:",
    L"&Izglađivanje fonta:",
    L"&Izglađivanje fonta:",
    L"&Glajenje pisave:",
    L"&Umekšavanje fonta:",
    L"&Згладжванне шрыфту:",
    L"&Изглаждане на шрифта:",
    L"&Измазнување на фонтот:",
    L"&Умекшавање фонта:",
    L"&Згладжування шрифту:",
    L"&Сглаживание шрифта:"
};

const wchar_t* ANTIALIASING_NAMES[LANG_COUNT][FONT_ANTIALIAS_COUNT] = {
    { L"GDI", L"ClearType", L"Žádné" },
    { L"GDI", L"ClearType", L"None" },
    { L"GDI", L"ClearType", L"Keine" },
    { L"GDI", L"ClearType", L"Aucun" },
    { L"GDI", L"ClearType", L"Ninguno" },
    { L"GDI", L"ClearType", L"Nessuno" },
    { L"GDI", L"ClearType", L"Brak" },
    { L"GDI", L"ClearType", L"Žiadne" },
    { L"GDI", L"ClearType", L"None" },
    { L"GDI", L"ClearType", L"None" },
    { L"GDI", L"ClearType", L"Nenhuma" },
    { L"GDI", L"ClearType", L"Ingen" },
    { L"GDI", L"ClearType", L"Ingen" },
    { L"GDI", L"ClearType", L"Ei mitään" },
    { L"GDI", L"ClearType", L"Ingen" },
    { L"GDI", L"ClearType", L"Engin" },
    { L"GDI", L"ClearType", L"Yok" },
    { L"GDI", L"ClearType", L"Puudub" },
    { L"GDI", L"ClearType", L"Gan frithailiasál" },
    { L"GDI", L"ClearType", L"Nėra" },
    { L"GDI", L"ClearType", L"Nav" },
    { L"GDI", L"ClearType", L"Nincs" },
    { L"GDI", L"ClearType", L"Xejn" },
    { L"GDI", L"ClearType", L"Geen" },
    { L"GDI", L"ClearType", L"Fără" },
    { L"GDI", L"ClearType", L"Καμία" },
    { L"GDI", L"ClearType", L"Nema" },
    { L"GDI", L"ClearType", L"Nema" },
    { L"GDI", L"ClearType", L"Brez" },
    { L"GDI", L"ClearType", L"Nema" },
    { L"GDI", L"ClearType", L"Няма" },
    { L"GDI", L"ClearType", L"Няма" },
    { L"GDI", L"ClearType", L"Нема" },
    { L"GDI", L"ClearType", L"Нема" },
    { L"GDI", L"ClearType", L"Немає" },
    { L"GDI", L"ClearType", L"Нет" }
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
    L"&Varsayılan görünüm",
    L"&Vaikeilme",
    L"&Cuma réamhshocraithe",
    L"&Numatytoji išvaizda",
    L"&Noklusējuma izskats",
    L"&Alapértelmezett megjelenés",
    L"&Dehra default",
    L"&Standaardvormgeving",
    L"&Aspect implicit",
    L"&Προεπιλεγμένη εμφάνιση",
    L"&Podrazumijevani izgled",
    L"&Zadani izgled",
    L"&Privzeti videz",
    L"&Podrazumijevani izgled",
    L"&Прадвызначаны выгляд",
    L"&Изглед по подразбиране",
    L"&Стандарден изглед",
    L"&Подразумевани изглед",
    L"&Типовий вигляд",
    L"&Вид по умолчанию"
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
    L"&Test et",
    L"&Testi",
    L"&Tástáil",
    L"&Tikrinti",
    L"&Pārbaudīt",
    L"&Tesztelés",
    L"&Ittestja",
    L"&Testen",
    L"&Testare",
    L"&Δοκιμή",
    L"&Testiraj",
    L"&Testiraj",
    L"&Preizkusi",
    L"&Testiraj",
    L"&Праверыць",
    L"&Тествай",
    L"&Тестирај",
    L"&Тестирај",
    L"&Перевірити",
    L"&Проверить"
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
    L"Testi &durdur",
    L"&Peata test",
    L"&Stop an tástáil",
    L"&Stabdyti tikrinimą",
    L"&Apturēt pārbaudi",
    L"&Teszt leállítása",
    L"&Waqqaf it-test",
    L"&Test stoppen",
    L"&Oprire test",
    L"&Διακοπή δοκιμής",
    L"&Zaustavi test",
    L"&Zaustavi test",
    L"&Ustavi preizkus",
    L"&Zaustavi test",
    L"&Спыніць тэст",
    L"&Спри теста",
    L"&Запри го тестот",
    L"&Заустави тест",
    L"&Зупинити перевірку",
    L"&Остановить тест"
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
    L"Zaman &sinyalini çal",
    L"Esita &ajasignaal",
    L"Seinn an comhartha &ama",
    L"Leisti laiko &signalą",
    L"Atskaņot laika &signālu",
    L"Idő&jelzés lejátszása",
    L"Daqq is-&sinjal tal-ħin",
    L"Tijdsi&gnaal afspelen",
    L"Redare &semnal orar",
    L"Αναπαραγωγή σήματος &ώρας",
    L"Reproduciraj vremenski &signal",
    L"Reproduciraj vremenski &signal",
    L"Predvajaj časovni &signal",
    L"Pusti vremenski &signal",
    L"Прайграваць сігнал &часу",
    L"Възпроизвеждай сигнал за &време",
    L"Пушти временски &сигнал",
    L"Пусти временски &сигнал",
    L"Відтворювати сигнал &часу",
    L"Воспроизводить сигнал &времени"
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
    L"&Uzak betiği çağır",
    L"Käivita &kaugskript",
    L"Glaoigh ar &chianscript",
    L"Vykdyti &nuotolinį scenarijų",
    L"Izsaukt &attālu skriptu",
    L"Távoli &parancsfájl hívása",
    L"Sejjaħ &skript remot",
    L"&Extern script aanroepen",
    L"Apelare &script la distanță",
    L"Κλήση &απομακρυσμένου σεναρίου",
    L"Pozovi &udaljenu skriptu",
    L"Pozovi &udaljenu skriptu",
    L"Pokliči &oddaljeni skript",
    L"Pozovi &udaljenu skriptu",
    L"Выклікаць &аддалены скрыпт",
    L"Извикай &отдалечен скрипт",
    L"Повикај &оддалечена скрипта",
    L"Позови &удаљену скрипту",
    L"Викликати &віддалений скрипт",
    L"Вызывать &удалённый скрипт"
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
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
    L"URL:",
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
    L"Geçerli bir HTTP veya HTTPS uzak betik URL'si girin.",
    L"Sisestage sobiv kaugskripti HTTP- või HTTPS-aadress.",
    L"Iontráil URL bailí HTTP nó HTTPS don chianscript.",
    L"Įveskite tinkamą nuotolinio scenarijaus HTTP arba HTTPS adresą.",
    L"Ievadiet derīgu attālā skripta HTTP vai HTTPS adresi.",
    L"Adja meg a távoli parancsfájl érvényes HTTP- vagy HTTPS-címét.",
    L"Daħħal indirizz HTTP jew HTTPS validu tal-iskript remot.",
    L"Voer een geldige HTTP- of HTTPS-URL voor het externe script in.",
    L"Introduceți o adresă HTTP sau HTTPS validă pentru scriptul la distanță.",
    L"Εισαγάγετε έγκυρη διεύθυνση HTTP ή HTTPS για το απομακρυσμένο σενάριο.",
    L"Unesite valjanu HTTP ili HTTPS adresu udaljene skripte.",
    L"Unesite valjanu HTTP ili HTTPS adresu udaljene skripte.",
    L"Vnesite veljaven naslov HTTP ali HTTPS oddaljenega skripta.",
    L"Unesite ispravnu HTTP ili HTTPS adresu udaljene skripte.",
    L"Увядзіце карэктны HTTP- або HTTPS-адрас аддаленага скрыпта.",
    L"Въведете валиден HTTP или HTTPS адрес на отдалечения скрипт.",
    L"Внесете важечка HTTP или HTTPS адреса на оддалечената скрипта.",
    L"Унесите исправну HTTP или HTTPS адресу удаљене скрипте.",
    L"Введіть коректну HTTP- або HTTPS-адресу віддаленого скрипту.",
    L"Введите корректный HTTP- или HTTPS-адрес удалённого скрипта."
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
    L"&XML içe aktar…",
    L"Impordi &XML…",
    L"Iompórtáil &XML…",
    L"Importuoti &XML…",
    L"Importēt &XML…",
    L"&XML importálása…",
    L"Importa &XML…",
    L"&XML importeren…",
    L"Import &XML…",
    L"Εισαγωγή &XML…",
    L"Uvezi &XML…",
    L"Uvezi &XML…",
    L"Uvozi &XML…",
    L"Uvezi &XML…",
    L"Імпартаваць &XML…",
    L"Импортирай &XML…",
    L"Увези &XML…",
    L"Увези &XML…",
    L"Імпортувати &XML…",
    L"Импортировать &XML…"
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
    L"X&ML dışa aktar…",
    L"Ekspordi X&ML…",
    L"Easpórtáil X&ML…",
    L"Eksportuoti X&ML…",
    L"Eksportēt X&ML…",
    L"X&ML exportálása…",
    L"Esporta X&ML…",
    L"X&ML exporteren…",
    L"Export X&ML…",
    L"Εξαγωγή X&ML…",
    L"Izvezi X&ML…",
    L"Izvezi X&ML…",
    L"Izvozi X&ML…",
    L"Izvezi X&ML…",
    L"Экспартаваць X&ML…",
    L"Експортирай X&ML…",
    L"Извези X&ML…",
    L"Извези X&ML…",
    L"Експортувати X&ML…",
    L"Экспортировать X&ML…"
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
    L"Dosya geçerli CalClock ayarları içermiyor.",
    L"Fail ei sisalda sobivaid CalClocki sätteid.",
    L"Níl socruithe bailí CalClock sa chomhad.",
    L"Faile nėra tinkamų „CalClock“ parametrų.",
    L"Fails nesatur derīgus CalClock iestatījumus.",
    L"A fájl nem tartalmaz érvényes CalClock-beállításokat.",
    L"Il-fajl ma fihx settings validi ta’ CalClock.",
    L"Het bestand bevat geen geldige CalClock-instellingen.",
    L"Fișierul nu conține setări CalClock valide.",
    L"Το αρχείο δεν περιέχει έγκυρες ρυθμίσεις CalClock.",
    L"Datoteka ne sadrži valjane postavke programa CalClock.",
    L"Datoteka ne sadrži valjane postavke programa CalClock.",
    L"Datoteka ne vsebuje veljavnih nastavitev CalClock.",
    L"Datoteka ne sadrži ispravna podešavanja za CalClock.",
    L"Файл не змяшчае карэктных налад CalClock.",
    L"Файлът не съдържа валидни настройки на CalClock.",
    L"Датотеката не содржи важечки поставки за CalClock.",
    L"Датотека не садржи исправна подешавања за CalClock.",
    L"Файл не містить коректних налаштувань CalClock.",
    L"Файл не содержит корректных настроек CalClock."
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
    L"Ayarlar dışa aktarılamadı.",
    L"Sätteid ei saanud eksportida.",
    L"Níorbh fhéidir na socruithe a easpórtáil.",
    L"Nepavyko eksportuoti parametrų.",
    L"Neizdevās eksportēt iestatījumus.",
    L"Nem sikerült exportálni a beállításokat.",
    L"Is-settings ma setgħux jiġu esportati.",
    L"De instellingen kunnen niet worden geëxporteerd.",
    L"Setările nu au putut fi exportate.",
    L"Δεν ήταν δυνατή η εξαγωγή των ρυθμίσεων.",
    L"Nije moguće izvesti postavke.",
    L"Nije moguće izvesti postavke.",
    L"Nastavitev ni mogoče izvoziti.",
    L"Nije moguće izvesti podešavanja.",
    L"Не ўдалося экспартаваць налады.",
    L"Настройките не могат да бъдат експортирани.",
    L"Поставките не може да се извезат.",
    L"Није могуће извести подешавања.",
    L"Не вдалося експортувати налаштування.",
    L"Не удалось экспортировать настройки."
};

const wchar_t* XML_STORAGE_LABELS[LANG_COUNT] = {
    L"Nastavení ukládat do &XML",
    L"Save settings to &XML",
    L"Einstellungen in &XML speichern",
    L"Enregistrer les paramètres au format &XML",
    L"Guardar la configuración en &XML",
    L"Salva le impostazioni in &XML",
    L"Zapisuj ustawienia w formacie &XML",
    L"Nastavenia ukladať do &XML",
    L"Save settings to &XML",
    L"Save settings to &XML",
    L"Guardar as definições em &XML",
    L"Lagre innstillinger i &XML",
    L"Spara inställningar i &XML",
    L"Tallenna asetukset &XML-muodossa",
    L"Gem indstillinger i &XML",
    L"Vista stillingar á &XML-sniði",
    L"Ayarları &XML biçiminde kaydet",
    L"Salvesta sätted &XML-vormingus",
    L"Sábháil socruithe in &XML",
    L"Įrašyti parametrus &XML formatu",
    L"Saglabāt iestatījumus &XML formātā",
    L"Beállítások mentése &XML-formátumban",
    L"Issejvja s-settings f’&XML",
    L"Instellingen opslaan in &XML",
    L"Salvează setările în &XML",
    L"Αποθήκευση ρυθμίσεων σε &XML",
    L"Čuvaj postavke u &XML formatu",
    L"Spremaj postavke u &XML formatu",
    L"Shranjuj nastavitve v obliki &XML",
    L"Čuvaj podešavanja u &XML formatu",
    L"Захоўваць налады ў фармаце &XML",
    L"Записвай настройките във формат &XML",
    L"Зачувувај ги поставките во формат &XML",
    L"Чувај подешавања у &XML формату",
    L"Зберігати налаштування у форматі &XML",
    L"Сохранять настройки в формате &XML"
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
    L"&Windows ile başlat",
    L"Käivita koos &Windowsiga",
    L"Tosaigh le &Windows",
    L"Paleisti kartu su &Windows",
    L"Palaist kopā ar &Windows",
    L"Indítás a &Windowszal",
    L"Ibda mal-&Windows",
    L"Starten met &Windows",
    L"Pornire odată cu &Windows",
    L"Εκκίνηση με τα &Windows",
    L"Pokreni uz &Windows",
    L"Pokreni sa sustavom &Windows",
    L"Zaženi s sistemom &Windows",
    L"Pokreni uz &Windows",
    L"Запускаць разам з &Windows",
    L"Стартирай с &Windows",
    L"Стартувај со &Windows",
    L"Покрени уз &Windows",
    L"Запускати разом із &Windows",
    L"Запускать вместе с &Windows"
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
    L"&Sessize al",
    L"&Vaigista",
    L"&Balbhaigh",
    L"&Nutildyti",
    L"&Izslēgt skaņu",
    L"&Némítás",
    L"&Iddiżattiva l-ħoss",
    L"&Dempen",
    L"&Dezactivare sunet",
    L"&Σίγαση",
    L"&Isključi zvuk",
    L"&Isključi zvuk",
    L"&Izklopi zvok",
    L"&Isključi zvuk",
    L"&Выключыць гук",
    L"&Изключи звука",
    L"&Исклучи го звукот",
    L"&Искључи звук",
    L"&Вимкнути звук",
    L"&Выключить звук"
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
    L"&Tümünü sessize al",
    L"Vaigista &kõik",
    L"Balbhaigh &uile",
    L"Nutildyti &visus",
    L"Izslēgt &visu skaņu",
    L"Összes &némítása",
    L"Iddiżattiva l-ħoss &kollu",
    L"&Alles dempen",
    L"Dezactivare &totală sunet",
    L"Σίγαση &όλων",
    L"Isključi &sav zvuk",
    L"Isključi &sav zvuk",
    L"Izklopi &ves zvok",
    L"Isključi &sav zvuk",
    L"Выключыць &увесь гук",
    L"Изключи &целия звук",
    L"Исклучи го &целиот звук",
    L"Искључи &сав звук",
    L"Вимкнути &весь звук",
    L"Выключить &весь звук"
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
    L"Sessi&z",
    L"&Vaigistatud",
    L"&Balbhaithe",
    L"&Nutildyta",
    L"&Skaņa izslēgta",
    L"&Némítva",
    L"&Ħoss diżattivat",
    L"&Gedempt",
    L"&Sunet dezactivat",
    L"Σε &σίγαση",
    L"&Zvuk isključen",
    L"&Zvuk isključen",
    L"&Zvok izklopljen",
    L"&Zvuk isključen",
    L"&Без гуку",
    L"&Без звук",
    L"&Без звук",
    L"&Звук искључен",
    L"&Без звуку",
    L"&Без звука"
};

const wchar_t* HELP_TEXT[LANG_COUNT] = {
    L"OVLÁDÁNÍ\r\nLevým tlačítkem a tažením přesunete hodiny nebo panel. Samostatný kalendář se přesouvá za "
    L"volnou plochu"
    L". Pravým tlačítkem na "
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
    L"area"
    L". Right-click a widget or notification "
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
    L"ziehen Sie an seiner freien Fläche"
    L". Rechtsklick auf Widget oder Infobereichsymbol öffnet das Menü. "
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
    L"autonome par sa zone libre"
    L". Un clic droit sur un widget ou l’icône de notification ouvre le "
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
    L"por su zona libre"
    L". El botón derecho sobre un widget o el icono de notificación abre el "
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
    L"trascina dall’area libera"
    L". Il pulsante destro su widget o icona di notifica apre il menu. Il "
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
    L"wolne miejsce. Prawy przycisk na widżecie lub ikonie obszaru powiadomień "
    L"otwiera menu. Lewy przycisk na ikonie ukrywa widoczne widżety; gdy wszystkie są ukryte, przywraca tylko "
    L"ostatnio ukryte widżety.\r\n\r\nWIDŻETY I USTAWIENIA\r\nMożna dodawać, usuwać i duplikować zegary "
    L"analogowe i cyfrowe, kalendarze, panele z kalendarzem i zegarem oraz zegary na monitorze. Każdy widżet "
    L"ma własną widoczność, tryb na wierzchu, język, strefę czasową i przesunięcie w formacie [-]HH:mm:ss.ff. "
    L"Zegary analogowe mają różne rozmiary. Cyfrowe oferują sekundy, zero wiodące, czcionkę, kolory, krycie i "
    L"przezroczyste tło. Kalendarz oferuje numery tygodni, niedzielę jako pierwszy dzień i język "
    L"widżetu.\r\n\r\nALARM\r\nAplikacja sama odtwarza plik audio raz lub w pętli; inne pliki i polecenia "
    L"przekazuje systemowi Windows. Kliknięcie alarmującej tarczy lub wyświetlacza, polecenie Zatrzymaj alarm "
    L"albo Esc zatrzymuje wskazanie i dźwięk wewnętrzny.\r\n\r\nSKRÓTY I ZAPIS\r\nDwuklik na tarczy lub "
    L"wyświetlaczu cyfrowym przełącza sekundy, F1 otwiera pomoc, a B ustawienia. Pozycje i wszystkie "
    L"ustawienia są zapisywane w wybranym magazynie. Ponowne uruchomienie aktywuje istniejącą instancję.",
    L"OVLÁDANIE\r\nĽavým tlačidlom a ťahaním presuniete hodiny alebo panel. Samostatný kalendár sa presúva za "
    L"voľnú plochu. Pravé tlačidlo na widgete alebo ikone v oznamovacej "
    L"oblasti otvorí ponuku. Ľavé kliknutie na ikonu skryje viditeľné widgety; ak sú všetky skryté, obnoví iba"
    L" naposledy skryté widgety.\r\n\r\nWIDGETY A NASTAVENIA\r\nMožno pridať, odobrať a duplikovať ručičkové "
    L"hodiny, digitálne hodiny, kalendáre, kombinované panely a hodiny na monitore. Každý widget má vlastnú "
    L"viditeľnosť, režim vždy navrchu, jazyk, časové pásmo a offset vo formáte [-]HH:mm:ss.ff. Ručičkové "
    L"hodiny majú voliteľnú veľkosť. Digitálne hodiny ponúkajú sekundy, úvodnú nulu, písmo, farby, "
    L"nepriehľadnosť a priehľadné pozadie. Kalendár ponúka čísla týždňov, nedeľu ako prvý deň a používa jazyk "
    L"widgetu.\r\n\r\nBUDÍK\r\nAplikácia prehrá zvukový súbor sama raz alebo dookola; ostatné súbory a príkazy"
    L" odovzdá systému Windows. Kliknutie na budík, príkaz Zastaviť budík alebo Esc zastaví signalizáciu aj "
    L"interný zvuk.\r\n\r\nSKRATKY A UKLADANIE\r\nDvojklik na ciferník alebo digitálny displej prepne sekundy,"
    L" F1 otvorí pomoc a B nastavenia. Polohy a všetky nastavenia sa ukladajú do zvoleného úložiska. Ďalšie "
    L"spustenie aktivuje existujúcu inštanciu.",
    L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a standalone calendar by its free "
    L"area"
    L". Right-click a widget or notification "
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
    L"area"
    L". Right-click a widget or notification "
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
    L"área livre"
    L". O botão direito abre o menu do widget. Um clique esquerdo no ícone de notificação oculta "
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
    L"ledige området"
    L". Høyreklikk åpner widgetmenyen. Et venstreklikk på systemstatusikonet skjuler synlige "
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
    L"området"
    L". Högerklick öppnar widgetmenyn. Ett vänsterklick på meddelandeikonen döljer synliga widgetar "
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
    L"alueelt"
    L"a. Napsauta hiiren kakkospainikkeella avataksesi pienoisohjelman valikon. Ilmoitusalueen "
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
    L"område"
    L". Højreklik åbner widgetmenuen. Et venstreklik på meddelelsesikonet skjuler synlige widgets eller "
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
    L"STJÓRNUN\r\nDragðu klukku eða spjald með vinstri músarhnappi. Dragðu sjálfstætt dagatal á auðu svæði"
    L". "
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
    L"sürükleyi"
    L"n. Sağ tıklama araç menüsünü açar. Bildirim simgesine sol tıklamak görünür araçları gizler veya "
    L"en son gizlenenleri geri "
    L"getirir.\r\n\r\nARAÇLAR VE AYARLAR\r\nAnalog saatler, dijital saatler, takvimler, birleşik paneller ve "
    L"monitör saatleri ekleyebilir, "
    L"kaldırabilir ve çoğaltabilirsiniz. Her aracın görünürlük, her zaman üstte, dil, saat dilimi ve ofset "
    L"ayarları "
    L"ayrıdır.\r\n\r\nALARM\r\nSaatlerde ve panellerde alarm olabilir. Alarm veren kadrana veya ekrana "
    L"tıklayın, Alarmı durdur'u seçin ya da "
    L"göstergeyi ve dahili sesi durdurmak için Esc tuşuna basın.\r\n\r\nKISAYOLLAR\r\nKadrana veya dijital "
    L"ekrana çift tıklama saniyeleri açıp "
    L"kapatır, F1 Yardım'ı, B Ayarlar'ı açar ve Esc aracı gizler.",
    L"Juhtimine\r\nLohistage kella või paneeli hiire vasaku nupuga. Eraldi kalendrit saab lohistada vabast "
    L"alast. Paremklõps"
    L" vidinal või olekuala ikoonil avab menüü. Vasakklõps ikoonil peidab nähtavad vidinad; kui kõik on "
    L"peidetud, taastab see ainult viimati peidetud vidinad.\r\n\r\nVidinad ja sätted\r\n\r\nSätetes saab "
    L"lisada, eemaldada ja dubleerida analoogkelli, digitaalkelli, kalendreid, kalendri ja kella paneele ning "
    L"ekraanikelli. Igal vidinal on oma nähtavus, suvand Alati pealmine, keel, ajavöönd ja nihe kujul "
    L"[-]HH:mm:ss.ff. Analoogkella ja paneeli kellade suurust saab valida eraldi. Digitaalkellal on sekundite,"
    L" algusnulli, fondi, värvide, läbipaistmatuse ja läbipaistva tausta sätted. Kalender toetab "
    L"nädalanumbreid ja pühapäeva nädala esimese päevana ning kasutab vidina keelt.\r\n\r\nÄratus ja "
    L"kiirklahvid\r\n\r\nKelladel ja paneelidel võib olla äratus. Rakendus esitab helifaili ise ühe korra või "
    L"pidevalt vastavalt kordamise sättele; muud failid ja käsud edastatakse Windowsile. Klõps ärataval "
    L"sihverplaadil või kuval, Peata äratus või Esc peatab nii äratuse tähistuse kui ka rakenduse heli. "
    L"Topeltklõps sihverplaadil või digitaalkuval lülitab sekundeid. F1 avab spikri, B sätted ja Esc peidab "
    L"vidina, kui ei peatata äratust. Vidina asukoht salvestatakse lohistamise järel, dialoogi asukoht "
    L"sulgemisel ja sätted valitud salvestuskohta. Korduskäivitus aktiveerib töötava eksemplari ning vidinad "
    L"jäävad tööala lähimasse saadaolevasse punkti.",
    L"Rialuithe\r\nTarraing clog nó painéal leis an gcnaipe luiche ar chlé. Tarraing féilire neamhspleách ón "
    L"achar saor"
    L". Osclaíonn deaschliceáil ar ghiuirléid nó ar dheilbhín an limistéir "
    L"fógraí an roghchlár. Folaíonn clé-chliceáil ar an deilbhín na giuirléidí infheicthe; má tá siad uile i "
    L"bhfolach, ní athchóirítear ach na cinn is déanaí a folaíodh.\r\n\r\nGiuirléidí agus socruithe\r\n\r\nIs "
    L"féidir cloig analógacha, cloig dhigiteacha, féilirí, painéil féilire agus cloig agus cloig scáileáin a "
    L"chur leis, a bhaint agus a dhúbailt sna Socruithe. Tá infheictheacht, Ar barr i gcónaí, teanga, crios "
    L"ama agus fritháireamh [-]HH:mm:ss.ff ar leith ag gach giuirléid. Roghnaítear méideanna na n-aghaidheanna"
    L" ar leith. Tacaíonn cloig dhigiteacha le soicindí, nialas tosaigh, cló, dathanna, teimhneacht agus cúlra"
    L" trédhearcach. Tacaíonn féilirí le huimhreacha seachtainí agus Dé Domhnaigh mar chéad lá agus úsáideann "
    L"siad teanga na giuirléide.\r\n\r\nAláram agus aicearraí\r\n\r\nIs féidir aláram a shocrú do chloig agus "
    L"do phainéil. Seinneann an feidhmchlár comhad fuaime é féin uair amháin nó go leanúnach de réir na rogha "
    L"athsheinnte; cuirtear comhaid agus orduithe eile ar aghaidh chuig Windows. Stopann cliceáil ar aghaidh "
    L"nó taispeáint an aláraim, Stop an t-aláram nó Esc an comhartha amhairc agus fuaim an fheidhmchláir. "
    L"Athraíonn déchliceáil ar aghaidh nó taispeáint dhigiteach na soicindí. Osclaíonn F1 Cabhair agus B "
    L"Socruithe; folaíonn Esc giuirléid mura bhfuil aláram á stopadh. Sábháiltear suíomhanna giuirléidí tar "
    L"éis tarraingthe, suíomhanna dialóg nuair a dhúntar iad agus na socruithe sa stóras roghnaithe. Má "
    L"sheoltar CalClock arís, gníomhachtaítear an feidhmchlár atá ar siúl cheana agus coinnítear na giuirléidí"
    L" ag an bpointe is gaire atá ar fáil sa limistéar oibre.",
    L"Valdymas\r\nVilkite laikrodį arba skydelį kairiuoju pelės mygtuku. Atskiras kalendorius velkamas už "
    L"laisvos srities"
    L". Dešiniuoju mygtuku spustelėjus valdiklį arba pranešimų srities piktogramą atidaromas meniu. "
    L"Kairysis piktogramos spustelėjimas paslepia matomus valdiklius; jei visi paslėpti, atkuriami tik "
    L"paskutinį kartą paslėpti valdikliai.\r\n\r\nValdikliai ir parametrai\r\n\r\nParametruose galima "
    L"įtraukti, pašalinti ir dubliuoti analoginius bei skaitmeninius laikrodžius, kalendorius, kalendoriaus su"
    L" laikrodžiu skydelius ir ekrano laikrodžius. Kiekvienas turi atskirą matomumą, Visada viršuje, kalbą, "
    L"laiko juostą ir poslinkį [-]HH:mm:ss.ff. Ciferblatų dydžiai pasirenkami atskirai. Skaitmeniniams "
    L"laikrodžiams galima nustatyti sekundes, pradinį nulį, šriftą, spalvas, nepermatomumą ir permatomą foną. "
    L"Kalendorius palaiko savaičių numerius ir sekmadienį kaip pirmąją dieną; pavadinimai rodomi valdiklio "
    L"kalba.\r\n\r\nŽadintuvas ir spartieji klavišai\r\n\r\nLaikrodžiai ir skydeliai palaiko žadintuvą. "
    L"Programa pati leidžia garso failą vieną kartą arba nuolat pagal kartojimo nuostatą; kiti failai ir "
    L"komandos perduodami „Windows“. Spustelėjus skambantį ciferblatą ar ekraną, pasirinkus Stabdyti žadintuvą"
    L" arba paspaudus Esc, sustabdomas vaizdinis signalas ir programos garsas. Dukart spustelėjus ciferblatą "
    L"arba skaitmeninį ekraną perjungiamos sekundės. F1 atidaro žinyną, B – parametrus, Esc paslepia valdiklį,"
    L" jei nestabdomas žadintuvas. Valdiklių padėtys įrašomos nuvilkus, dialogų – juos uždarius, o parametrai "
    L"– pasirinktoje saugykloje. Pakartotinis paleidimas suaktyvina veikiantį egzempliorių; valdikliai "
    L"paliekami artimiausioje pasiekiamoje darbo srities vietoje.",
    L"Vadība\r\nVelciet pulksteni vai paneli ar peles kreiso pogu. Atsevišķu kalendāru velciet aiz brīvās "
    L"zona"
    L"s. Labais klikšķis uz logrīka vai paziņojumu apgabala ikonas atver izvēlni. Kreisais "
    L"klikšķis uz ikonas paslēpj redzamos logrīkus; ja visi ir paslēpti, atjauno tikai pēdējos "
    L"paslēptos.\r\n\r\nLogrīki un iestatījumi\r\n\r\nIestatījumos var pievienot, noņemt un dublēt analogos un"
    L" digitālos pulksteņus, kalendārus, kalendāra un pulksteņa paneļus un ekrāna pulksteņus. Katram logrīkam "
    L"ir sava redzamība, Vienmēr virspusē, valoda, laika josla un nobīde [-]HH:mm:ss.ff. Ciparnīcu lielumi ir "
    L"izvēlami atsevišķi. Digitālajiem pulksteņiem ir sekundes, sākuma nulle, fonts, krāsas, necaurspīdīgums "
    L"un caurspīdīgs fons. Kalendāri atbalsta nedēļu numurus un svētdienu kā pirmo dienu un izmanto logrīka "
    L"valodu.\r\n\r\nModinātājs un īsinājumtaustiņi\r\n\r\nPulksteņi un paneļi atbalsta modinātāju. Programma "
    L"pati atskaņo skaņas failu vienreiz vai nepārtraukti atbilstoši atkārtošanas izvēlei; citus failus un "
    L"komandas nodod Windows. Klikšķis uz aktīvā modinātāja ciparnīcas vai displeja, Apturēt modinātāju vai "
    L"Esc aptur indikāciju un programmas skaņu. Dubultklikšķis uz ciparnīcas vai digitālā displeja pārslēdz "
    L"sekundes. F1 atver palīdzību, B iestatījumus, Esc paslēpj logrīku, ja netiek apturēts modinātājs. "
    L"Logrīka novietojumu saglabā pēc vilkšanas, dialoga novietojumu aizverot, iestatījumus izvēlētajā "
    L"krātuvē. Atkārtota palaišana aktivizē esošo programmas eksemplāru un notur logrīkus tuvākajā pieejamajā "
    L"darba apgabala vietā.",
    L"Kezelés\r\nAz órát vagy panelt a bal egérgombbal húzhatja. Az önálló naptárt a szabad területénél fogva "
    L"mozgathatja"
    L". A minialkalmazásra vagy az értesítési terület ikonjára kattintva a jobb gombbal menüt "
    L"nyithat. Az ikonra kattintva a bal gombbal elrejtheti a látható minialkalmazásokat; ha mind rejtett, "
    L"csak a legutóbb elrejtettek térnek vissza.\r\n\r\nMinialkalmazások és beállítások\r\n\r\nA Beállítások "
    L"között analóg és digitális órákat, naptárakat, naptárat és órát tartalmazó paneleket, valamint "
    L"képernyőórákat adhat hozzá, távolíthat el és másolhat. Minden minialkalmazás külön láthatósággal, Mindig"
    L" felül állapottal, nyelvvel, időzónával és [-]HH:mm:ss.ff eltolással rendelkezik. A számlapméretek külön"
    L" választhatók. A digitális órák másodperceket, vezető nullát, betűtípust, színeket, átlátszatlanságot és"
    L" átlátszó hátteret támogatnak. A naptár megjeleníti a hétszámokat, kezdődhet vasárnappal, és a "
    L"minialkalmazás nyelvét használja.\r\n\r\nÉbresztés és billentyűparancsok\r\n\r\nAz órákhoz és panelekhez"
    L" ébresztés állítható be. A program a hangfájlt maga játssza le egyszer vagy folyamatosan az ismétlés "
    L"szerint; a többi fájlt és parancsot átadja a Windowsnak. Az ébresztő számlapra vagy kijelzőre kattintva,"
    L" az Ébresztés leállítása paranccsal vagy az Esc billentyűvel a jelzés és a program hangja leállítható. A"
    L" számlapra vagy digitális kijelzőre duplán kattintva a másodperceket kapcsolhatja. Az F1 a Súgót, a B a "
    L"Beállításokat nyitja meg; az Esc elrejti a minialkalmazást, ha nem ébresztést állít le. A helyzetet "
    L"húzás után, a párbeszédablak helyét bezáráskor, a beállításokat a kiválasztott tárolóban menti a "
    L"program. Az újabb indítás a futó példányt aktiválja, és a minialkalmazásokat a munkaterület legközelebbi"
    L" elérhető pontján tartja.",
    L"Kontrolli\r\nMexxi arloġġ jew panew billi tkaxkru bil-buttuna tax-xellug tal-maws. Kalendarju separat "
    L"jitmexxa miż-żona vojta tiegħu"
    L". Klikk bil-lemin fuq widget jew l-ikona taż-żona tan-notifiki jiftaħ "
    L"il-menu. Klikk bix-xellug fuq l-ikona jaħbi l-widgets viżibbli; jekk kollha moħbija, jirrestawra biss "
    L"dawk li nħbew l-aħħar.\r\n\r\nWidgets u settings\r\n\r\nFis-Settings tista’ żżid, tneħħi u tidduplika "
    L"arloġġi analogi u diġitali, kalendarji, panewijiet tal-kalendarju bl-arloġġ u arloġġi tal-iskrin. Kull "
    L"widget għandu l-viżibbiltà, Dejjem fuq nett, il-lingwa, iż-żona tal-ħin u l-kumpens [-]HH:mm:ss.ff "
    L"tiegħu. Id-daqsijiet tal-uċuħ jintgħażlu separatament. L-arloġġi diġitali jappoġġjaw sekondi, żero "
    L"fil-bidu, font, kuluri, opaċità u sfond trasparenti. Il-kalendarju jappoġġja numri tal-ġimgħat u l-Ħadd "
    L"bħala l-ewwel jum u juża l-lingwa tal-widget.\r\n\r\nAllarm u shortcuts\r\n\r\nL-arloġġi u l-panewijiet "
    L"jistgħu jkollhom allarm. Il-programm idoqq fajl tal-awdjo huwa stess darba jew kontinwament skont "
    L"ir-ripetizzjoni; fajls u kmandi oħra jintbagħtu lill-Windows. Klikk fuq il-wiċċ jew il-wiri tal-allarm "
    L"attiv, Waqqaf l-allarm jew Esc iwaqqaf l-indikazzjoni u l-awdjo tal-programm. Klikk doppju fuq wiċċ jew "
    L"wiri diġitali jaqleb is-sekondi. F1 jiftaħ l-Għajnuna, B is-Settings, u Esc jaħbi widget jekk mhux qed "
    L"iwaqqaf allarm. Il-pożizzjonijiet tal-widgets jiġu ssejvjati wara t-tkaxkir, dawk tad-djalogi meta "
    L"jingħalqu, u s-settings fil-ħażna magħżula. Tnedija oħra tattiva l-istanza li diġà qed taħdem u żżomm "
    L"il-widgets fl-eqreb punt disponibbli taż-żona tax-xogħol.",
    L"Bediening\r\nSleep een klok of paneel met de linkermuisknop. Sleep een losse kalender via de vrije "
    L"ruimte"
    L". Klik met rechts op een widget of het pictogram in het systeemvak voor het menu. Klik met "
    L"links op het pictogram om zichtbare widgets te verbergen; als alles verborgen is, worden alleen de "
    L"laatst verborgen widgets hersteld.\r\n\r\nWidgets en instellingen\r\n\r\nVia Instellingen kunt u analoge"
    L" en digitale klokken, kalenders, kalenderpanelen met een klok en schermklokken toevoegen, verwijderen en"
    L" dupliceren. Elke widget heeft een eigen zichtbaarheid, Altijd op voorgrond, taal, tijdzone en "
    L"verschuiving [-]HH:mm:ss.ff. Wijzerplaatgroottes zijn afzonderlijk instelbaar. Digitale klokken "
    L"ondersteunen seconden, een voorloopnul, lettertypen, kleuren, dekking en een transparante achtergrond. "
    L"Kalenders ondersteunen weeknummers en zondag als eerste dag en gebruiken de widgettaal.\r\n\r\nAlarm en "
    L"sneltoetsen\r\n\r\nKlokken en panelen kunnen een alarm hebben. De toepassing speelt een geluidsbestand "
    L"zelf eenmaal of voortdurend af volgens de herhaaloptie; andere bestanden en opdrachten worden aan "
    L"Windows doorgegeven. Klik op de alarmerende wijzerplaat of weergave, kies Alarm stoppen of druk op Esc "
    L"om de aanduiding en het geluid van de toepassing te stoppen. Dubbelklikken op een wijzerplaat of "
    L"digitale weergave schakelt seconden om. F1 opent Help, B Instellingen en Esc verbergt een widget wanneer"
    L" er geen alarm wordt gestopt. Widgetposities worden na slepen opgeslagen, dialoogposities bij sluiten en"
    L" instellingen in de gekozen opslag. Opnieuw starten activeert de bestaande toepassing en houdt widgets "
    L"op de dichtstbijzijnde beschikbare plaats in het werkgebied.",
    L"Comenzi\r\nGlisați ceasul sau panoul cu butonul stâng al mouse-ului. Un calendar separat se glisează din"
    L" zona liberă. Un "
    L"clic dreapta pe widget sau pe pictograma din zona de notificare deschide meniul. Un clic stânga pe "
    L"pictogramă ascunde widgeturile vizibile; dacă toate sunt ascunse, le restabilește numai pe cele ascunse "
    L"ultima dată.\r\n\r\nWidgeturi și setări\r\n\r\nÎn Setări puteți adăuga, elimina și dubla ceasuri "
    L"analogice și digitale, calendare, panouri calendar cu ceas și ceasuri pe ecran. Fiecare are propria "
    L"vizibilitate, Întotdeauna deasupra, limbă, fus orar și decalaj [-]HH:mm:ss.ff. Dimensiunile cadranelor "
    L"se aleg separat. Ceasurile digitale oferă secunde, zero inițial, fonturi, culori, opacitate și fundal "
    L"transparent. Calendarele acceptă numere de săptămâni și duminica drept prima zi și folosesc limba "
    L"widgetului.\r\n\r\nAlarmă și comenzi rapide\r\n\r\nCeasurile și panourile pot avea alarmă. Aplicația "
    L"redă singură fișierul audio o dată sau continuu, conform repetării; alte fișiere și comenzi sunt "
    L"transmise către Windows. Un clic pe cadranul sau afișajul alarmei active, Oprire alarmă ori Esc oprește "
    L"indicația și sunetul aplicației. Un dublu clic pe cadran sau afișaj digital comută secundele. F1 "
    L"deschide Ajutor, B Setări, iar Esc ascunde widgetul dacă nu oprește o alarmă. Pozițiile widgeturilor se "
    L"salvează după glisare, cele ale dialogurilor la închidere, iar setările în spațiul de stocare ales. O "
    L"nouă pornire activează instanța existentă și păstrează widgeturile în cel mai apropiat punct disponibil "
    L"al zonei de lucru.",
    L"Χειρισμός\r\nΣύρετε ένα ρολόι ή πλαίσιο με το αριστερό κουμπί του ποντικιού. Σύρετε ένα ανεξάρτητο "
    L"ημερολόγιο από την ελεύθερη περιοχή του"
    L". Το δεξί κλικ σε γραφικό στοιχείο ή στο εικονίδιο της "
    L"περιοχής ειδοποιήσεων ανοίγει το μενού. Το αριστερό κλικ στο εικονίδιο κρύβει τα ορατά στοιχεία· αν όλα "
    L"είναι κρυφά, επαναφέρει μόνο όσα αποκρύφτηκαν τελευταία.\r\n\r\nΓραφικά στοιχεία και "
    L"ρυθμίσεις\r\n\r\nΣτις Ρυθμίσεις προσθέτετε, καταργείτε και αντιγράφετε αναλογικά και ψηφιακά ρολόγια, "
    L"ημερολόγια, πλαίσια ημερολογίου με ρολόι και ρολόγια οθόνης. Κάθε στοιχείο έχει δική του ορατότητα, "
    L"Πάντα σε πρώτο πλάνο, γλώσσα, ζώνη ώρας και μετατόπιση [-]HH:mm:ss.ff. Τα μεγέθη των καντράν επιλέγονται"
    L" χωριστά. Τα ψηφιακά ρολόγια υποστηρίζουν δευτερόλεπτα, αρχικό μηδενικό, γραμματοσειρά, χρώματα, "
    L"αδιαφάνεια και διαφανές φόντο. Τα ημερολόγια υποστηρίζουν αριθμούς εβδομάδων και Κυριακή ως πρώτη ημέρα "
    L"και χρησιμοποιούν τη γλώσσα του στοιχείου.\r\n\r\nΞυπνητήρι και συντομεύσεις\r\n\r\nΤα ρολόγια και τα "
    L"πλαίσια υποστηρίζουν ξυπνητήρι. Η εφαρμογή αναπαράγει το αρχείο ήχου μία φορά ή συνεχώς σύμφωνα με την "
    L"επανάληψη· άλλα αρχεία και εντολές διαβιβάζονται στα Windows. Κλικ στο ενεργό καντράν ή στην ένδειξη, "
    L"Διακοπή αφύπνισης ή Esc σταματά την οπτική ένδειξη και τον ήχο της εφαρμογής. Το διπλό κλικ στο καντράν "
    L"ή στην ψηφιακή ένδειξη αλλάζει την εμφάνιση δευτερολέπτων. Το F1 ανοίγει τη Βοήθεια, το B τις Ρυθμίσεις,"
    L" το Esc κρύβει το στοιχείο όταν δεν σταματά ξυπνητήρι. Οι θέσεις των στοιχείων αποθηκεύονται μετά τη "
    L"μεταφορά, των παραθύρων διαλόγου κατά το κλείσιμο και οι ρυθμίσεις στον επιλεγμένο χώρο αποθήκευσης. Νέα"
    L" εκκίνηση ενεργοποιεί την υπάρχουσα παρουσία και διατηρεί τα στοιχεία στο πλησιέστερο διαθέσιμο σημείο "
    L"της περιοχής εργασίας.",
    L"Upravljanje\r\nPovucite sat ili ploču lijevom tipkom miša. Samostalni kalendar povlači se za slobodno "
    L"područje"
    L". Desnom tipkom kliknite vidžet ili ikonu u području obavijesti za otvaranje menija. Lijevi klik na"
    L" ikonu skriva vidljive vidžete; ako su svi skriveni, vraća samo posljednje skrivene "
    L"vidžete.\r\n\r\nVidžeti i postavke\r\n\r\nU Postavkama možete dodavati, uklanjati i duplicirati analogne"
    L" i digitalne satove, kalendare, ploče kalendara sa satom i satove na ekranu. Svaki vidžet ima vlastitu "
    L"vidljivost, način Uvijek na vrhu, jezik, vremensku zonu i vremenski pomak. Pomak unesite kao "
    L"[-]HH:mm:ss.ff. Veličina analognih satova i satova na ploči može se odabrati. Digitalni satovi "
    L"podržavaju sekunde, početnu nulu, font, boje, neprozirnost i prozirnu pozadinu. Kalendar podržava "
    L"brojeve sedmica i nedjelju kao prvi dan te koristi jezik vidžeta.\r\n\r\nAlarm\r\n\r\nSatovi i ploče "
    L"mogu imati alarm. Program sam reproducira zvučnu datoteku jednom ili neprekidno, zavisno o postavci "
    L"ponavljanja. Ostale datoteke i naredbe predaju se Windowsu. Kliknite brojčanik ili ekran aktivnog "
    L"alarma, odaberite Zaustavi alarm ili pritisnite Esc za zaustavljanje signalizacije i zvuka koji "
    L"reproducira program.\r\n\r\nPrečaci i čuvanje\r\n\r\nDvostruki klik na brojčanik ili digitalni ekran "
    L"uključuje ili isključuje sekunde. F1 otvara pomoć, B otvara Postavke, a Esc skriva vidžet ako ne "
    L"zaustavlja alarm. Položaji vidžeta čuvaju se nakon povlačenja, položaji dijaloških prozora pri "
    L"zatvaranju, a postavke u odabrano spremište. Ponovno pokretanje aktivira već pokrenutu instancu i "
    L"zadržava vidžete na najbližem dostupnom mjestu radnog područja.",
    L"Upravljanje\r\nPovucite sat ili ploču lijevom tipkom miša. Samostalni kalendar povlači se za slobodno "
    L"područje"
    L". Desnom tipkom kliknite widget ili ikonu u području obavijesti za otvaranje izbornika. Lijevi klik"
    L" na ikonu skriva vidljive widgete; ako su svi skriveni, vraća samo posljednje skrivene "
    L"widgete.\r\n\r\nWidgeti i postavke\r\n\r\nU Postavkama možete dodavati, uklanjati i duplicirati analogne"
    L" i digitalne satove, kalendare, ploče kalendara sa satom i satove na zaslonu. Svaki widget ima vlastitu "
    L"vidljivost, način Uvijek na vrhu, jezik, vremensku zonu i vremenski pomak. Pomak unesite kao "
    L"[-]HH:mm:ss.ff. Veličina analognih satova i satova na ploči može se odabrati. Digitalni satovi "
    L"podržavaju sekunde, početnu nulu, font, boje, neprozirnost i prozirnu pozadinu. Kalendar podržava "
    L"brojeve tjedana i nedjelju kao prvi dan te koristi jezik widgeta.\r\n\r\nAlarm\r\n\r\nSatovi i ploče "
    L"mogu imati alarm. Program sam reproducira zvučnu datoteku jednom ili neprekidno, ovisno o postavci "
    L"ponavljanja. Ostale datoteke i naredbe predaju se Windowsu. Kliknite brojčanik ili zaslon aktivnog "
    L"alarma, odaberite Zaustavi alarm ili pritisnite Esc za zaustavljanje signalizacije i zvuka koji "
    L"reproducira program.\r\n\r\nPrečaci i spremanje\r\n\r\nDvostruki klik na brojčanik ili digitalni zaslon "
    L"uključuje ili isključuje sekunde. F1 otvara pomoć, B otvara Postavke, a Esc skriva widget ako ne "
    L"zaustavlja alarm. Položaji widgeta spremaju se nakon povlačenja, položaji dijaloških prozora pri "
    L"zatvaranju, a postavke u odabrano spremište. Ponovno pokretanje aktivira već pokrenutu instancu i "
    L"zadržava widgete na najbližem dostupnom mjestu radnog područja.",
    L"Upravljanje\r\nUro ali ploščo povlecite z levim miškinim gumbom. Samostojni koledar premikate za prosti "
    L"del. Desni klik na "
    L"gradnik ali ikono v območju za obvestila odpre meni. Levi klik na ikono skrije vidne gradnike; če so vsi"
    L" skriti, obnovi samo nazadnje skrite.\r\n\r\nGradniki in nastavitve\r\n\r\nV Nastavitvah lahko dodajate,"
    L" odstranjujete in podvajate analogne in digitalne ure, koledarje, plošče koledarja z uro ter ure na "
    L"zaslonu. Vsak gradnik ima lastno vidnost, možnost Vedno na vrhu, jezik, časovni pas in odmik v obliki "
    L"[-]HH:mm:ss.ff. Velikost analognih ur in ur na plošči je nastavljiva. Digitalne ure podpirajo sekunde, "
    L"vodilno ničlo, pisavo, barve, neprosojnost in prosojno ozadje. Koledar podpira številke tednov in "
    L"nedeljo kot prvi dan ter uporablja jezik gradnika.\r\n\r\nBudilka in bližnjice\r\n\r\nUre in plošče "
    L"podpirajo budilko. Program sam predvaja zvočno datoteko enkrat ali neprekinjeno glede na ponavljanje; "
    L"druge datoteke in ukaze preda sistemu Windows. Klik na številčnico ali prikaz aktivne budilke, Ustavi "
    L"budilko ali Esc ustavi opozarjanje in zvok programa. Dvoklik na številčnico ali digitalni prikaz "
    L"preklopi sekunde. F1 odpre pomoč, B Nastavitve, Esc pa skrije gradnik, kadar ne ustavlja budilke. "
    L"Položaji gradnikov se shranijo po premikanju, položaji pogovornih oken ob zaprtju, nastavitve pa v "
    L"izbrano shrambo. Ponovni zagon aktivira obstoječi primerek in ohrani gradnike na najbližjem dosegljivem "
    L"mestu delovnega območja.",
    L"Upravljanje\r\nPovucite sat ili panel lijevim tasterom miša. Samostalni kalendar se pomjera preko "
    L"slobodne površine. Desni "
    L"klik na vidžet ili ikonu u oblasti za obavještenja otvara meni. Lijevi klik na ikonu skriva vidljive "
    L"vidžete; ako su svi skriveni, vraća samo posljednje skrivene.\r\n\r\nVidžeti i podešavanja\r\n\r\nU "
    L"Podešavanjima možete dodavati, uklanjati i duplirati analogne i digitalne satove, kalendare, panele "
    L"kalendara sa satom i satove na monitoru. Svaki vidžet ima sopstvenu vidljivost, režim Uvijek na vrhu, "
    L"jezik, vremensku zonu i pomak u obliku [-]HH:mm:ss.ff. Veličine analognih satova i satova na panelu "
    L"biraju se posebno. Digitalni satovi podržavaju sekunde, vodeću nulu, font, boje, neprozirnost i providnu"
    L" pozadinu. Kalendar podržava brojeve nedjelja i nedjelju kao prvi dan i koristi jezik "
    L"vidžeta.\r\n\r\nAlarm i prečice\r\n\r\nSatovi i paneli podržavaju alarm. Program sam pušta zvučnu "
    L"datoteku jednom ili neprekidno, u zavisnosti od ponavljanja. Ostale datoteke i naredbe predaje "
    L"Windows-u. Klik na brojčanik ili prikaz aktivnog alarma, Zaustavi alarm ili Esc zaustavljaju indikaciju "
    L"i zvuk programa. Dvoklik na brojčanik ili digitalni prikaz prebacuje sekunde. F1 otvara pomoć, B "
    L"Podešavanja, a Esc skriva vidžet ako ne zaustavlja alarm. Položaji vidžeta čuvaju se poslije pomjeranja,"
    L" položaji dijaloga pri zatvaranju, a podešavanja u izabranom skladištu. Ponovno pokretanje aktivira "
    L"postojeću instancu i zadržava vidžete na najbližem dostupnom mjestu radne površine.",
    L"Кіраванне\r\nПерацягвайце гадзіннік або панэль левай кнопкай мышы. Асобны каляндар перацягваецца за "
    L"вольную вобласць"
    L". Правая кнопка на віджэце або значку ў вобласці апавяшчэнняў адкрывае меню. Левая "
    L"кнопка на значку хавае бачныя віджэты; калі ўсе схаваныя, аднаўляе толькі апошнія "
    L"схаваныя.\r\n\r\nВіджэты і налады\r\n\r\nУ акне «Налады» можна дадаваць, выдаляць і дубляваць аналагавыя"
    L" і лічбавыя гадзіннікі, календары, панэлі календара з гадзіннікам і гадзіннікі на маніторы. Кожны віджэт"
    L" мае ўласныя бачнасць, рэжым «Заўсёды зверху», мову, часавы пояс і зрушэнне ў фармаце [-]HH:mm:ss.ff. "
    L"Памер аналагавых гадзіннікаў і гадзіннікаў на панэлі выбіраецца асобна. Лічбавыя гадзіннікі "
    L"падтрымліваюць секунды, пачатковы нуль, шрыфт, колеры, непразрыстасць і празрысты фон. Каляндар "
    L"падтрымлівае нумары тыдняў і нядзелю як першы дзень ды выкарыстоўвае мову віджэта.\r\n\r\nБудзільнік і "
    L"спалучэнні клавіш\r\n\r\nГадзіннікі і панэлі падтрымліваюць будзільнік. Праграма прайгравае гукавы файл "
    L"адзін раз або бесперапынна паводле налады паўтарэння. Іншыя файлы і каманды перадаюцца Windows. Пстрычка"
    L" на цыферблаце ці дысплеі актыўнага будзільніка, «Спыніць будзільнік» або Esc спыняюць сігналізацыю і "
    L"гук праграмы. Падвойная пстрычка на цыферблаце ці лічбавым дысплеі пераключае секунды. F1 адкрывае "
    L"даведку, B — налады, а Esc хавае віджэт, калі не спыняе будзільнік. Пазіцыі віджэтаў захоўваюцца пасля "
    L"перацягвання, дыялогавых вокнаў — пры закрыцці, а налады — у выбраным сховішчы. Паўторны запуск актывуе "
    L"ўжо запушчаны асобнік і пакідае віджэты ў найбліжэйшым даступным месцы рабочай вобласці.",
    L"Управление\r\nПреместете часовник или панел с плъзгане с левия бутон на мишката. Самостоятелният "
    L"календар се премества чрез свободната му област"
    L". Десният бутон върху модул или иконата в областта"
    L" за уведомяване отваря меню. Левият бутон върху иконата скрива видимите модули; ако всички са скрити, "
    L"възстановява само последно скритите.\r\n\r\nИзпълними модули и настройки\r\n\r\nВ „Настройки“ можете да "
    L"добавяте, премахвате и дублирате аналогови и цифрови часовници, календари, панели с календар и часовник "
    L"и часовници на монитор. Всеки модул има собствена видимост, режим „Винаги отгоре“, език, часова зона и "
    L"отместване във формат [-]HH:mm:ss.ff. Размерите на аналоговите часовници и часовниците в панела се "
    L"избират отделно. Цифровите часовници поддържат секунди, водеща нула, шрифт, цветове, непрозрачност и "
    L"прозрачен фон. Календарът поддържа номера на седмиците и неделя като първи ден и използва езика на "
    L"модула.\r\n\r\nАларма и клавишни комбинации\r\n\r\nЧасовниците и панелите поддържат аларма. Програмата "
    L"възпроизвежда звуков файл веднъж или непрекъснато според настройката за повторение. Другите файлове и "
    L"команди се предават на Windows. Щракнете върху циферблата или дисплея на активната аларма, изберете "
    L"„Спри алармата“ или натиснете Esc, за да спрете индикацията и звука на програмата. Двойното щракване "
    L"върху циферблата или цифровия дисплей превключва секундите. F1 отваря помощта, B — настройките, а Esc "
    L"скрива модула, ако не спира аларма. Позициите на модулите се записват след преместване, на диалоговите "
    L"прозорци — при затваряне, а настройките — в избраното хранилище. Повторното стартиране активира "
    L"работещия екземпляр и оставя модулите на най-близкото достъпно място в работната област.",
    L"Управување\r\nПовлечете часовник или панел со левото копче на глувчето. Самостојниот календар се "
    L"поместува преку слободната површина"
    L". Десен клик на виџет или иконата во областа за известување го отвора менито. Лев клик"
    L" на иконата ги крие видливите виџети; ако сите се скриени, ги враќа само последно "
    L"скриените.\r\n\r\nВиџети и поставки\r\n\r\nВо „Поставки“ можете да додавате, отстранувате и дуплирате "
    L"аналогни и дигитални часовници, календари, панели со календар и часовник и часовници на монитор. Секој "
    L"виџет има своја видливост, режим „Секогаш најгоре“, јазик, временска зона и поместување во облик "
    L"[-]HH:mm:ss.ff. Големината на аналогните часовници и часовниците во панелот се избира одделно. "
    L"Дигиталните часовници поддржуваат секунди, водечка нула, фонт, бои, непроѕирност и проѕирна заднина. "
    L"Календарот поддржува броеви на недели и недела како прв ден и го користи јазикот на "
    L"виџетот.\r\n\r\nАларм и кратенки\r\n\r\nЧасовниците и панелите поддржуваат аларм. Програмата самата "
    L"пушта звучна датотека еднаш или непрекинато според повторувањето. Другите датотеки и наредби се "
    L"предаваат на Windows. Клик на бројчаникот или приказот на активниот аларм, „Запри го алармот“ или Esc ги"
    L" запира сигнализацијата и звукот на програмата. Двоен клик на бројчаникот или дигиталниот приказ ги "
    L"вклучува или исклучува секундите. F1 ја отвора помошта, B — поставките, а Esc го крие виџетот ако не "
    L"запира аларм. Положбите на виџетите се зачувуваат по поместување, на дијалозите при затворање, а "
    L"поставките во избраното складиште. Повторното стартување го активира постојниот примерок и ги задржува "
    L"виџетите на најблиското достапно место на работната површина.",
    L"Управљање\r\nПовуците сат или панел левим тастером миша. Самостални календар се помера преко слободне "
    L"површине. Десни клик на "
    L"виџет или икону у области за обавештења отвара мени. Леви клик на икону скрива видљиве виџете; ако су "
    L"сви скривени, враћа само последње скривене.\r\n\r\nВиџети и подешавања\r\n\r\nУ Подешавањима можете "
    L"додавати, уклањати и дуплирати аналогне и дигиталне сатове, календаре, панеле календара са сатом и "
    L"сатове на монитору. Сваки виџет има сопствену видљивост, режим Увек на врху, језик, временску зону и "
    L"помак у облику [-]HH:mm:ss.ff. Величине аналогних сатова и сатова на панелу бирају се посебно. Дигитални"
    L" сатови подржавају секунде, водећу нулу, фонт, боје, непрозирност и провидну позадину. Календар подржава"
    L" бројеве недеља и недељу као први дан и користи језик виџета.\r\n\r\nАларм и пречице\r\n\r\nСатови и "
    L"панели подржавају аларм. Програм сам пушта звучну датотеку једном или непрекидно, у зависности од "
    L"понављања. Остале датотеке и наредбе предаје Windows-у. Клик на бројчаник или приказ активног аларма, "
    L"Заустави аларм или Esc заустављају индикацију и звук програма. Двоклик на бројчаник или дигитални приказ"
    L" пребацује секунде. F1 отвара помоћ, B Подешавања, а Esc скрива виџет ако не зауставља аларм. Положаји "
    L"виџета чувају се после померања, дијалога при затварању, а подешавања у изабраном складишту. Поновно "
    L"покретање активира постојећу инстанцу и задржава виџете на најближем доступном месту радне површине.",
    L"КЕРУВАННЯ\r\nПеретягуйте годинник або панель лівою кнопкою миші. Окремий календар перетягується за вільну"
    L" область"
    L". Клацніть віджет або піктограму в області сповіщень правою кнопкою миші, щоб "
    L"відкрити меню. Ліве клацання піктограми приховує видимі віджети; якщо всі віджети приховано, "
    L"відновлюються лише ті, що були приховані останніми.\r\n\r\nВІДЖЕТИ ТА НАЛАШТУВАННЯ\r\nУ вікні "
    L"«Налаштування» можна додавати, видаляти й дублювати аналогові та цифрові годинники, календарі, панелі "
    L"календаря з годинником і годинники на моніторі. Для кожного віджета окремо задаються видимість, режим "
    L"«Завжди зверху», мова, часовий пояс і зсув часу. Зсув вводиться у форматі [-]HH:mm:ss.ff. Розмір "
    L"аналогового годинника та годинників на панелі можна змінювати. Цифрові годинники підтримують показ "
    L"секунд, початкового нуля, вибір шрифту, кольорів, непрозорості та прозорого тла. У календарі можна "
    L"показувати номери тижнів і починати тиждень із неділі; назви відображаються мовою "
    L"віджета.\r\n\r\nБУДИЛЬНИК\r\nДля годинників і панелей можна ввімкнути будильник. Програма сама відтворює "
    L"звуковий файл один раз або безперервно, залежно від параметра повторення. Інші файли та команди "
    L"передаються Windows. Щоб зупинити індикацію будильника та звук, який відтворює програма, клацніть його "
    L"циферблат або дисплей, виберіть «Зупинити будильник» або натисніть Esc.\r\n\r\nСПОЛУЧЕННЯ КЛАВІШ І "
    L"ЗБЕРЕЖЕННЯ\r\nПодвійне клацання циферблата або цифрового дисплея перемикає показ секунд. F1 відкриває "
    L"довідку, B — налаштування, а Esc приховує віджет, якщо не потрібно зупиняти будильник. Розташування "
    L"віджетів зберігається після перетягування, розташування діалогових вікон — під час закриття, а "
    L"налаштування — у вибраному сховищі. Повторний запуск активує вже запущений примірник програми й залишає "
    L"віджети в найближчому доступному місці робочої області.",
    L"УПРАВЛЕНИЕ\r\nПеретаскивайте часы или панель левой кнопкой мыши. Отдельный календарь перетаскивается за "
    L"свободную область"
    L". Щёлкните виджет или значок в области уведомлений правой кнопкой мыши, чтобы открыть "
    L"меню. Щелчок значка левой кнопкой скрывает видимые виджеты; если все виджеты скрыты, восстанавливаются "
    L"только те, которые были скрыты последними.\r\n\r\nВИДЖЕТЫ И НАСТРОЙКИ\r\nВ окне «Настройки» можно "
    L"добавлять, удалять и дублировать аналоговые и цифровые часы, календари, панели календаря с часами и часы "
    L"на мониторе. Для каждого виджета отдельно задаются видимость, режим «Поверх всех окон», язык, часовой "
    L"пояс и смещение времени. Смещение вводится в формате [-]HH:mm:ss.ff. Размер аналоговых часов и часов на "
    L"панели можно менять. Цифровые часы поддерживают показ секунд, ведущего нуля, выбор шрифта, цветов, "
    L"непрозрачности и прозрачного фона. В календаре можно показывать номера недель и начинать неделю с "
    L"воскресенья; названия отображаются на языке виджета.\r\n\r\nБУДИЛЬНИК\r\nДля часов и панелей можно "
    L"включить будильник. Программа сама воспроизводит звуковой файл один раз или непрерывно, в зависимости от "
    L"параметра повтора. Другие файлы и команды передаются Windows. Чтобы остановить индикацию будильника и "
    L"звук, который воспроизводит программа, щёлкните его циферблат или дисплей, выберите «Остановить "
    L"будильник» или нажмите Esc.\r\n\r\nСОЧЕТАНИЯ КЛАВИШ И СОХРАНЕНИЕ\r\nДвойной щелчок циферблата или "
    L"цифрового дисплея переключает показ секунд. F1 открывает справку, B — настройки, а Esc скрывает виджет, "
    L"если не требуется остановить будильник. Расположение виджетов сохраняется после перетаскивания, "
    L"расположение диалоговых окон — при закрытии, а настройки — в выбранном хранилище. Повторный запуск "
    L"активирует уже запущенный экземпляр программы и оставляет виджеты в ближайшем доступном месте рабочей "
    L"области."
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
    L"Hodnota −∞ dB znamená úplné ztišení. Změny uslyšíte i během testu. "
    L"Soubory MIDI a soubory, které nelze dekódovat a přehrávají se náhradním přehrávačem, "
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
    L"approximately 794%. The −∞ dB position is silence. Changes can also be heard during a test. "
    L"MIDI files and files played by a fallback player because "
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
    L"%. −∞ dB bedeutet Stille. Änderungen sind auch während eines Tests hörbar. "
    L"MIDI-Dateien und Dateien, die nicht decodiert werden können und mit "
    L"einem Ersatzplayer abgespielt werden, sind auf 100 % begrenzt.",
    L"\r\n\r\nSAISIE DE L’HEURE ET ACTIONS D’ALARME\r\nL’heure accepte HH:mm avec deux-points, point, espace "
    L"ou un autre séparateur, qui peut aussi être omis. Un ou deux chiffres indiquent les heures, trois ou "
    L"quatre les heures et les minutes, par exemple 7, 12, 730, 0730 ou 7:30. La valeur devient HH:mm à la "
    L"sortie du champ. Le décalage se saisit de droite à partir des secondes : 2 signifie 00:00:02.00, 230 et "
    L"0230 signifient 00:02:30.00, et 12345 signifie 01:23:45.00. Avec séparateurs, deux groupes représentent "
    L"minutes et secondes, trois représentent heures, minutes et secondes, et un quatrième les centièmes ; un "
    L"signe est accepté. Les jours sous Alarme active déterminent les jours où l’alarme fonctionne ; tous sont"
    L" sélectionnés par défaut. Leur ordre suit la culture de l’application ; changer de langue ne modifie pas"
    L" les jours enregistrés. Lors du déclenchement, l’alarme affiche un widget masqué et le ramène devant "
    L"sans modifier durablement Toujours visible. Émettre le signal horaire lance le premier bip court"
    L" cinq secondes avant l’alarme. Ce choix est indépendant de l’onglet Signal, mais les séquences "
    L"simultanées sont fusionnées. Tester fait clignoter le cadran ou le cadre du panneau et teste de façon le"
    L" fichier, la commande, l’audio, l’URL HTTP/HTTPS du script distant et, si l’option est activée, la "
    L"séquence complète du signal horaire. Arrêter le test coupe son audio interne et son aperçu du signal ; "
    L"arrêter l’alarme coupe son audio interne. Couper le son n’arrête pas la lecture interne : elle continue "
    L"silencieusement et redevient audible après rétablissement. Les commandes et scripts distants ne sont pas"
    L" affectés. Lancer un fichier ou une commande active le champ, Parcourir, Tester et la boucle ; Tester et"
    L" la boucle exigent aussi une valeur non vide, mais un test en cours peut toujours être arrêté.\r\n\r\nLe"
    L" curseur Volume audio de l’onglet Alarme règle le volume des fichiers audio lus en interne pour ce "
    L"widget. La valeur par défaut −18 dB correspond au niveau original du fichier (100 %). Déplacer le "
    L"curseur vers la droite amplifie le son ; le maximum de 0 dB correspond à environ 794 %. −∞ dB correspond"
    L" au silence. Les changements sont audibles pendant le test. Le"
    L"s fichiers MIDI et ceux lus par un lecteur de secours faute de décodage sont limités à 100 "
    L"%.",
    L"\r\n\r\nENTRADA DE HORA Y ACCIONES DE ALARMA\r\nLa hora admite HH:mm con dos puntos, punto, espacio u "
    L"otro separador, que también puede omitirse. Uno o dos dígitos indican horas; tres o cuatro, horas y "
    L"minutos, por ejemplo 7, 12, 730, 0730 o 7:30. Al salir del campo se normaliza a HH:mm. El desfase se "
    L"introduce desde la derecha empezando por los segundos: 2 es 00:00:02.00, 230 y 0230 son 00:02:30.00, y "
    L"12345 es 01:23:45.00. Con separadores, dos grupos son minutos y segundos, tres son horas, minutos y "
    L"segundos, y un cuarto contiene centésimas; se admite signo. Los días bajo Alarma activa determinan los "
    L"días de la semana en que funciona; todos están seleccionados de forma predeterminada. Su orden sigue la "
    L"cultura de la aplicación; cambiar el idioma no modifica los días guardados. Al activarse, la alarma "
    L"muestra un widget oculto y lo lleva al frente sin cambiar permanentemente Siempre visible. "
    L"Emitir la señal horaria inicia el primer pitido corto cinco segundos antes de la alarma. Es "
    L"independiente de la pestaña Señal, aunque las secuencias coincidentes se combinan. Probar hace parpadear"
    L" la esfera o el marco del panel y prueba de forma asíncrona el archivo, el comando, el audio, la URL "
    L"HTTP/HTTPS del script remoto y, si está activada, la secuencia completa de la señal horaria. Detener la "
    L"prueba también detiene su audio interno y la vista previa de la señal; detener la alarma detiene su "
    L"audio interno. Silenciar no detiene la reproducción interna: continúa en silencio y vuelve a oírse al "
    L"reactivar el sonido. No afecta a comandos ni scripts remotos. Ejecutar archivo o comando activa el "
    L"campo, Examinar, Probar y la repetición; Probar y repetir también requieren un valor no vacío, pero una "
    L"prueba en curso siempre puede detenerse.\r\n\r\nEl control Volumen de audio de la pestaña Alarma ajusta "
    L"los archivos de audio reproducidos internamente para ese widget. El valor predeterminado de −18 dB "
    L"conserva el nivel original del archivo (100 %). Hacia la derecha se amplifica el sonido; el máximo de 0 "
    L"dB equivale aproximadamente al 794 %. −∞ dB es silencio. Los cambios se oyen durante la prueba. "
    L"Los archivos MIDI y los reproducidos por un reproductor "
    L"alternativo al no poder decodificarse están limitados al 100 %.",
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
    L"indica il silenzio. Le modifiche si sentono durante la prova. I"
    L" file MIDI e quelli riprodotti da un lettore alternativo perché non decodificabili "
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
    L"również podczas testu. Pliki MIDI i pliki odtwarzane "
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
    L"počuť aj počas testu. Súbory MIDI a súbory, ktoré nemožno "
    L"dekódovať a prehrávajú sa náhradným prehrávačom, možno nastaviť najviac na 100 %.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, space or another "
    L"separator; the separator may also be omitted. One or two digits mean hours, while three or four digits "
    L"mean hours and minutes, for example 7, 12, 730, 0730 or 7:30. The value is normalised to HH:mm after "
    L"leaving the field. Offset entry starts from seconds on the right: 2 means 00:00:02.00, 230 and 0230 mean"
    L" 00:02:30.00, and 12345 means 01:23:45.00. With separators, two groups mean minutes and seconds, three "
    L"mean hours, minutes and seconds, and a fourth group contains hundredths; a sign is accepted. The days "
    L"below Alarm enabled select the weekdays on which the alarm runs; all days are selected by default. Their"
    L" order follows the application culture, and changing the language does not change the stored weekdays. "
    L"When triggered, the alarm shows a hidden widget and brings it in front without permanently changing "
    L"Always on top. Sound the time signal starts its first short pip five seconds before the alarm. It is "
    L"independent of the Signal tab, although coincident sequences are merged. Test flashes the selected clock"
    L" face or panel frame and tests the file, command, audio, HTTP/HTTPS remote-script URL and, when "
    L"selected, the complete time-signal sequence. Stopping the test stops its internal audio and signal "
    L"preview; stopping the alarm stops its internal audio. Muting does not stop internal playback: it "
    L"continues silently and becomes audible again after unmuting. Commands and remote scripts are "
    L"unaffected.\r\n\r\nThe Audio volume slider on the Alarm tab sets the volume of internally played audio "
    L"files for that widget. The default −18 dB preserves the original file level (100%). Moving the slider to"
    L" the right amplifies the audio; the 0 dB maximum is approximately 794%. The −∞ dB position is silence. "
    L"Changes can also be heard during a test. MIDI files and files "
    L"played by a fallback player because they cannot be decoded are limited to 100%.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, space or another "
    L"separator; the separator may also be omitted. One or two digits mean hours, while three or four digits "
    L"mean hours and minutes, for example 7, 12, 730, 0730 or 7:30. The value is normalised to HH:mm after "
    L"leaving the field. Offset entry starts from seconds on the right: 2 means 00:00:02.00, 230 and 0230 mean"
    L" 00:02:30.00, and 12345 means 01:23:45.00. With separators, two groups mean minutes and seconds, three "
    L"mean hours, minutes and seconds, and a fourth group contains hundredths; a sign is accepted. The days "
    L"below Alarm enabled select the weekdays on which the alarm runs; all days are selected by default. Their"
    L" order follows the application culture, and changing the language does not change the stored weekdays. "
    L"When triggered, the alarm shows a hidden widget and brings it in front without permanently changing "
    L"Always on top. Sound the time signal starts its first short pip five seconds before the alarm. It is "
    L"independent of the Signal tab, although coincident sequences are merged. Test flashes the selected clock"
    L" face or panel frame and tests the file, command, audio, HTTP/HTTPS remote-script URL and, when "
    L"selected, the complete time-signal sequence. Stopping the test stops its internal audio and signal "
    L"preview; stopping the alarm stops its internal audio. Muting does not stop internal playback: it "
    L"continues silently and becomes audible again after unmuting. Commands and remote scripts are "
    L"unaffected.\r\n\r\nThe Audio volume slider on the Alarm tab sets the volume of internally played audio "
    L"files for that widget. The default −18 dB preserves the original file level (100%). Moving the slider to"
    L" the right amplifies the audio; the 0 dB maximum is approximately 794%. The −∞ dB position is silence. "
    L"Changes can also be heard during a test. MIDI files and files "
    L"played by a fallback player because they cannot be decoded are limited to 100%.",
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
    L"durante o teste. Os ficheiros MIDI e os "
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
    L"stillhet. Endringer høres også under testen. "
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
    L"dB är tystnad. Ändringar hörs även under testet. "
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
    L"794 %:a. −∞ dB tarkoittaa hiljaisuutta. Muutokset kuuluvat myös testin aikana. M"
    L"IDI-tiedostojen ja varasoittimella toistettavien "
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
    L"−∞ dB er stilhed. Ændringer høres også under testen. "
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
    L"um 794%. −∞ dB er þögn. Breytingar heyrast einnig meðan á prófun stendur. "
    L"MIDI-skrár og skrár sem aukaspilari spilar vegna þess að ekki er hægt að "
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
    L"Değişiklikler test sırasında da duyulur. MIDI "
    L"dosyaları ve çözülemediği için yedek oynatıcıyla çalınan dosyalar %100 ile sınırlıdır.",
    L"\r\n\r\nAja sisestamine ja äratuse toimingud\r\nÄratuse aeg lubab vormingut HH:mm kooloni, punkti, "
    L"tühiku või muu eraldajaga või eraldajata. Üks või kaks numbrit tähendavad tunde, kolm või neli tunde ja "
    L"minuteid: 7, 12, 730, 0730 või 7:30. Väljalt lahkumisel teisendatakse väärtus vormingusse HH:mm. Nihet "
    L"loetakse paremalt alates sekunditest: 2 tähendab 00:00:02.00, 230 ja 0230 tähendavad 00:02:30.00 ning "
    L"12345 tähendab 01:23:45.00. Eraldajatega tähendavad kaks rühma minuteid ja sekundeid, kolm tunde, "
    L"minuteid ja sekundeid ning neljas sajandiksekundeid; märk on lubatud. Päevad suvandi Äratus lubatud all "
    L"määravad äratuspäevad; vaikimisi on valitud kõik. Järjestus järgib rakenduse keelt, kuid keele muutmine "
    L"ei muuda salvestatud päevi.\r\n\r\nÄratus kuvab peidetud vidina ja toob selle ette, muutmata püsivalt "
    L"suvandit Alati pealmine. Esita ajasignaal alustab esimest lühikest tooni viis sekundit enne äratust. See"
    L" on vahekaardist Signaal sõltumatu; samaaegsed jadad ühendatakse. Testi paneb sihverplaadi või raami "
    L"vilkuma ja kontrollib faili, käsku, heli, kaugskripti HTTP/HTTPS-aadressi ning valitud ajasignaali kogu "
    L"jada. Testi peatamine lõpetab selle sisemise heli ja proovisignaali; äratuse peatamine lõpetab selle "
    L"sisemise heli. Vaigistamisel esitus jätkub hääletult ja muutub vaigistuse eemaldamisel taas kuuldavaks. "
    L"Käske ja kaugskripte see ei peata.\r\n\r\nVahekaardi Äratus liugur Helitugevus määrab selle vidina "
    L"sisemise heliesituse tugevuse. Vaikimisi −18 dB säilitab faili algtaseme (100%). Paremale liikumine "
    L"võimendab heli; maksimaalne 0 dB vastab ligikaudu 794%-le. −∞ dB tähendab vaikust. Muutus kostab ka "
    L"testi ajal. MIDI ja failid, mida ei saa dekodeerida ning "
    L"esitatakse varumängijaga, on piiratud 100%-ga.",
    L"\r\n\r\nAm a iontráil agus gníomhartha aláraim\r\nGlacann am an aláraim le HH:mm, le hidirstad, lánstad,"
    L" spás nó deighilteoir eile, nó gan deighilteoir. Ciallaíonn digit nó dhó uaireanta, agus trí nó ceithre "
    L"huaireanta agus nóiméid: 7, 12, 730, 0730 nó 7:30. Déantar HH:mm den luach nuair a fhágtar an réimse. "
    L"Léitear an fritháireamh ón taobh deas, ag tosú le soicindí: is ionann 2 agus 00:00:02.00, 230 agus 0230 "
    L"agus 00:02:30.00, agus 12345 agus 01:23:45.00. Le deighilteoirí, ciallaíonn dhá ghrúpa nóiméid agus "
    L"soicindí, trí ghrúpa uaireanta, nóiméid agus soicindí, agus ceathrú grúpa céaduithe soicind; ceadaítear "
    L"comhartha. Roghnaíonn na laethanta faoi Aláram cumasaithe na laethanta gníomhacha; tá siad uile "
    L"roghnaithe ar dtús. Leanann an t-ord teanga an fheidhmchláir; ní athraíonn teanga nua na laethanta "
    L"sábháilte.\r\n\r\nTaispeánann aláram giuirléid fholaithe agus tugann sé chun tosaigh í gan Ar barr i "
    L"gcónaí a athrú go buan. Tosaíonn Seinn an comhartha ama an chéad bhíp ghearr cúig shoicind roimh an "
    L"aláram. Tá sé neamhspleách ar an gcluaisín Comhartha, ach cumaisctear seichimh chomhuaineacha. Cuireann "
    L"Tástáil aghaidh an chloig nó fráma an phainéil ag caochadh agus seiceálann sé an comhad, an t-ordú, an "
    L"fhuaim, URL HTTP/HTTPS an chianscript agus, má roghnaítear é, an comhartha ama iomlán. Stopann Stop an "
    L"tástáil an fhuaim inmheánach agus an comhartha trialach; stopann Stop an t-aláram fuaim inmheánach an "
    L"aláraim. Leanann athsheinm ar aghaidh go ciúin nuair a bhalbhaítear é agus éiríonn sé inchloiste arís "
    L"nuair a bhaintear an balbhú. Ní stoptar orduithe ná cianscripteanna.\r\n\r\nSocraíonn Airde na fuaime ar"
    L" an gcluaisín Aláram leibhéal na gcomhad a sheinntear go hinmheánach don ghiuirléid sin. Coinníonn an "
    L"réamhshocrú −18 dB leibhéal bunaidh an chomhaid (100%). Méadaíonn bogadh ar dheis an fhuaim; is ionann "
    L"an t-uasmhéid 0 dB agus thart ar 794%. Is tost é −∞ dB. Cloistear athruithe le linn tástála freisin. Tá "
    L"MIDI agus comhaid a sheinntear le seinnteoir cúltaca "
    L"toisc nach féidir iad a dhíchódú teoranta do 100%.",
    L"\r\n\r\nLaiko įvedimas ir žadintuvo veiksmai\r\nŽadintuvo laikas priima HH:mm su dvitaškiu, tašku, tarpu"
    L" ar kitu skirtuku arba be skirtuko. Vienas ar du skaitmenys reiškia valandas, trys ar keturi – valandas "
    L"ir minutes: 7, 12, 730, 0730 arba 7:30. Išėjus iš lauko nustatomas HH:mm formatas. Poslinkis skaitomas "
    L"iš dešinės nuo sekundžių: 2 reiškia 00:00:02.00, 230 ir 0230 – 00:02:30.00, 12345 – 01:23:45.00. Su "
    L"skirtukais dvi grupės reiškia minutes ir sekundes, trys – valandas, minutes ir sekundes, ketvirta – "
    L"šimtąsias sekundės dalis; leidžiamas ženklas. Dienos po Žadintuvas įjungtas nustato suveikimo dienas; iš"
    L" pradžių pasirinktos visos. Jų tvarka priklauso nuo programos kalbos, tačiau pakeitus kalbą įrašytos "
    L"dienos nesikeičia.\r\n\r\nŽadintuvas parodo paslėptą valdiklį ir iškelia jį į priekį nekeisdamas Visada "
    L"viršuje visam laikui. Leisti laiko signalą pradeda pirmą trumpą toną likus penkioms sekundėms iki "
    L"žadintuvo. Ši nuostata nepriklauso nuo skirtuko Signalas; vienalaikės sekos sujungiamos. Tikrinti "
    L"įjungia ciferblato arba rėmelio mirksėjimą ir tikrina failą, komandą, garsą, nuotolinio scenarijaus "
    L"HTTP/HTTPS adresą ir, jei pasirinkta, visą laiko signalą. Sustabdžius tikrinimą nutraukiamas jo vidinis "
    L"garsas ir bandomasis signalas; sustabdžius žadintuvą – jo vidinis garsas. Nutildžius atkūrimas tęsiasi "
    L"tyliai ir vėl girdimas įjungus garsą. Komandos ir nuotoliniai scenarijai nestabdomi.\r\n\r\nSlankiklis "
    L"Garsumas skirtuke Žadintuvas valdo šio valdiklio vidinį atkūrimą. Numatytieji −18 dB išlaiko pradinį "
    L"failo lygį (100%). Slenkant dešinėn garsas stiprinamas; didžiausi 0 dB atitinka maždaug 794%. −∞ dB "
    L"reiškia tylą. Pakeitimai girdimi ir tikrinant. MIDI ir failams, "
    L"kurių negalima dekoduoti ir kurie atkuriami atsarginiu būdu, taikoma 100% riba.",
    L"\r\n\r\nLaika ievade un modinātāja darbības\r\nModinātāja laiks pieņem HH:mm ar kolu, punktu, atstarpi, "
    L"citu atdalītāju vai bez tā. Viens vai divi cipari ir stundas, trīs vai četri – stundas un minūtes: 7, "
    L"12, 730, 0730 vai 7:30. Atstājot lauku, vērtība kļūst par HH:mm. Nobīdi lasa no labās puses, sākot ar "
    L"sekundēm: 2 ir 00:00:02.00, 230 un 0230 ir 00:02:30.00, 12345 ir 01:23:45.00. Ar atdalītājiem divas "
    L"grupas nozīmē minūtes un sekundes, trīs – stundas, minūtes un sekundes, ceturtā – sekundes simtdaļas; "
    L"atļauta zīme. Dienas zem Modinātājs ieslēgts nosaka darbības dienas; sākumā atlasītas visas. Secība "
    L"atbilst programmas valodai, bet valodas maiņa nemaina saglabātās dienas.\r\n\r\nModinātājs parāda "
    L"paslēpto logrīku un izvirza to priekšplānā bez pastāvīgas Vienmēr virspusē maiņas. Atskaņot laika "
    L"signālu sāk pirmo īso toni piecas sekundes pirms modinātāja. Šī izvēle ir neatkarīga no cilnes Signāls; "
    L"vienlaicīgās virknes tiek apvienotas. Pārbaudīt ieslēdz ciparnīcas vai rāmja mirgošanu un pārbauda "
    L"failu, komandu, skaņu, attālā skripta HTTP/HTTPS adresi un izvēlēto pilno laika signālu. Pārbaudes "
    L"apturēšana pārtrauc tās iekšējo skaņu un izmēģinājuma signālu; modinātāja apturēšana pārtrauc tā iekšējo"
    L" skaņu. Izslēdzot skaņu, atskaņošana turpinās nedzirdami un kļūst dzirdama pēc ieslēgšanas. Komandas un "
    L"attālie skripti netiek apturēti.\r\n\r\nSlīdnis Skaļums cilnē Modinātājs regulē šī logrīka iekšējo "
    L"atskaņošanu. Noklusējuma −18 dB saglabā faila sākotnējo līmeni (100%). Pa labi skaņa tiek pastiprināta; "
    L"lielākie 0 dB atbilst apmēram 794%. −∞ dB ir klusums. Izmaiņas dzirdamas arī pārbaudē. "
    L"MIDI un faili, kurus nevar dekodēt un atskaņo rezerves atskaņotājs, ir ierobežoti "
    L"līdz 100%.",
    L"\r\n\r\nIdőbevitel és ébresztési műveletek\r\nAz ébresztési idő HH:mm formátumú lehet kettősponttal, "
    L"ponttal, szóközzel, más elválasztóval vagy anélkül. Egy vagy két számjegy órát, három vagy négy órát és "
    L"percet jelent: 7, 12, 730, 0730 vagy 7:30. A mező elhagyásakor HH:mm alakra vált. Az eltolást jobbról, a"
    L" másodpercektől olvassa: 2 jelentése 00:00:02.00, 230 és 0230 jelentése 00:02:30.00, 12345 jelentése "
    L"01:23:45.00. Elválasztóval két csoport percet és másodpercet, három órát, percet és másodpercet, a "
    L"negyedik századmásodpercet jelent; előjel megadható. Az Ébresztés engedélyezve alatti napok adják a "
    L"működés napjait; alapból mind kijelölt. Sorrendjük a program nyelvét követi, de a nyelvváltás nem "
    L"módosítja a mentett napokat.\r\n\r\nAz ébresztés megjeleníti a rejtett minialkalmazást, és előtérbe "
    L"hozza a Mindig felül tartós módosítása nélkül. Az Időjelzés lejátszása az első rövid hangot öt "
    L"másodperccel az ébresztés előtt indítja. Ez független az Időjelzés fültől; az egyidejű sorozatok "
    L"egyesülnek. A Tesztelés villogtatja a számlapot vagy keretet, és ellenőrzi a fájlt, parancsot, hangot, "
    L"távoli parancsfájl HTTP/HTTPS-címét és a kiválasztott teljes időjelzést. A teszt leállítása annak belső "
    L"hangját és próbajelzését, az ébresztés leállítása annak belső hangját állítja le. Némításkor a lejátszás"
    L" hangtalanul folytatódik, feloldáskor ismét hallható. A parancsok és távoli parancsfájlok nem állnak "
    L"le.\r\n\r\nAz Ébresztés fül Hangerő csúszkája az adott minialkalmazás belső lejátszását szabályozza. Az "
    L"alapértelmezett −18 dB megőrzi a fájl eredeti szintjét (100%). Jobbra erősíti a hangot; a legnagyobb 0 "
    L"dB körülbelül 794%. A −∞ dB csendet jelent. A változtatás teszt közben is hallható. "
    L"A MIDI és a nem dekódolható, tartalék lejátszóval kezelt fájlok legfeljebb 100%-osak.",
    L"\r\n\r\nDħul tal-ħin u azzjonijiet tal-allarm\r\nIl-ħin tal-allarm jaċċetta HH:mm b’żewġ punti, punt, "
    L"spazju jew separatur ieħor, jew mingħajr separatur. Ċifra waħda jew tnejn ifissru sigħat; tlieta jew "
    L"erbgħa sigħat u minuti: 7, 12, 730, 0730 jew 7:30. Meta titlaq mill-qasam, il-valur isir HH:mm. "
    L"Il-kumpens jinqara mil-lemin mis-sekondi: 2 ifisser 00:00:02.00, 230 u 0230 ifissru 00:02:30.00, u 12345"
    L" ifisser 01:23:45.00. B’separaturi, żewġ gruppi jfissru minuti u sekondi, tlieta sigħat, minuti u "
    L"sekondi, u r-raba’ ċentesimi ta’ sekonda; sinjal huwa permess. Il-jiem taħt Allarm attivat jagħżlu "
    L"l-jiem tal-allarm; kollha magħżula inizjalment. L-ordni jsegwi l-lingwa tal-programm, iżda bidla "
    L"fil-lingwa ma tbiddilx il-jiem issejvjati.\r\n\r\nL-allarm juri widget moħbi u jġibu fuq quddiem "
    L"mingħajr ma jibdel Dejjem fuq nett permanentement. Daqq is-sinjal tal-ħin jibda l-ewwel ton qasir ħames "
    L"sekondi qabel l-allarm. Dan huwa indipendenti mit-tab Sinjal; sekwenzi simultanji jingħaqdu. Ittestja "
    L"jteptep il-wiċċ jew il-qafas u jittestja l-fajl, il-kmand, l-awdjo, l-indirizz HTTP/HTTPS tal-iskript "
    L"remot u, jekk magħżul, is-sinjal tal-ħin sħiħ. Il-waqfien tat-test iwaqqaf l-awdjo intern tiegħu u "
    L"s-sinjal ta’ prova; il-waqfien tal-allarm iwaqqaf l-awdjo intern tiegħu. Meta ssikket, id-daqq ikompli "
    L"fis-skiet u jerġa’ jinstema’ meta tneħħi s-sikket. Il-kmandi u l-iskripts remoti jibqgħu "
    L"attivi.\r\n\r\nIs-slajder Volum tal-awdjo fit-tab Allarm jikkontrolla d-daqq intern ta’ dak il-widget. "
    L"Id-default −18 dB iżomm il-livell oriġinali tal-fajl (100%). Lejn il-lemin il-ħoss jiġi amplifikat; "
    L"il-massimu 0 dB huwa madwar 794%. −∞ dB huwa skiet. Il-bidliet jinstemgħu waqt it-test ukoll. "
    L"MIDI u fajls li ma jistgħux jiġu dekodifikati u jindaqqu b’metodu ta’ "
    L"riżerva huma limitati għal 100%.",
    L"\r\n\r\nTijd invoeren en alarmacties\r\nDe alarmtijd accepteert HH:mm met een dubbele punt, punt, spatie"
    L" of ander scheidingsteken, of zonder scheidingsteken. Een of twee cijfers zijn uren, drie of vier uren "
    L"en minuten: 7, 12, 730, 0730 of 7:30. Na het verlaten van het veld wordt de waarde HH:mm. Verschuivingen"
    L" worden vanaf rechts als seconden gelezen: 2 is 00:00:02.00, 230 en 0230 zijn 00:02:30.00, 12345 is "
    L"01:23:45.00. Met scheidingstekens zijn twee groepen minuten en seconden, drie uren, minuten en seconden "
    L"en een vierde honderdsten; een teken is toegestaan. De dagen onder Alarm ingeschakeld bepalen de actieve"
    L" weekdagen; standaard zijn alle dagen gekozen. Hun volgorde volgt de toepassingstaal; taalwijziging "
    L"verandert de opgeslagen dagen niet.\r\n\r\nEen alarm toont een verborgen widget en brengt deze naar "
    L"voren zonder Altijd op voorgrond blijvend te wijzigen. Tijdsignaal afspelen begint de eerste korte toon "
    L"vijf seconden vóór het alarm. Dit staat los van het tabblad Signaal; gelijktijdige reeksen worden "
    L"samengevoegd. Testen laat de wijzerplaat of rand knipperen en test het bestand, de opdracht, het geluid,"
    L" de HTTP/HTTPS-URL van het externe script en, indien gekozen, het volledige tijdsignaal. Test stoppen "
    L"beëindigt de interne audio en het proefsignaal van de test; het alarm stoppen beëindigt de interne "
    L"alarmaudio. Bij dempen loopt interne audio stil door en wordt na opheffen weer hoorbaar. Opdrachten en "
    L"externe scripts blijven actief.\r\n\r\nGeluidsvolume op het tabblad Alarm regelt de interne weergave "
    L"voor die widget. De standaard −18 dB behoudt het oorspronkelijke bestandsniveau (100%). Naar rechts "
    L"versterkt het geluid; het maximum van 0 dB is ongeveer 794%. −∞ dB betekent stilte. Wijzigingen zijn ook"
    L" tijdens een test hoorbaar. MIDI en bestanden "
    L"die niet gedecodeerd kunnen worden en via een alternatieve speler worden afgespeeld, zijn beperkt tot "
    L"100%.",
    L"\r\n\r\nIntroducerea orei și acțiunile alarmei\r\nOra alarmei acceptă HH:mm cu două puncte, punct, "
    L"spațiu, alt separator sau fără separator. Una ori două cifre înseamnă ore, trei sau patru ore și minute:"
    L" 7, 12, 730, 0730 sau 7:30. La ieșirea din câmp, valoarea devine HH:mm. Decalajul se citește de la "
    L"dreapta, începând cu secundele: 2 înseamnă 00:00:02.00, 230 și 0230 înseamnă 00:02:30.00, iar 12345 "
    L"înseamnă 01:23:45.00. Cu separatori, două grupuri înseamnă minute și secunde, trei ore, minute și "
    L"secunde, al patrulea sutimi; se acceptă semn. Zilele de sub Alarmă activată stabilesc zilele de "
    L"declanșare; implicit sunt selectate toate. Ordinea urmează limba aplicației, dar schimbarea limbii nu "
    L"modifică zilele salvate.\r\n\r\nAlarma afișează widgetul ascuns și îl aduce în față fără a modifica "
    L"permanent Întotdeauna deasupra. Redare semnal orar pornește primul ton scurt cu cinci secunde înaintea "
    L"alarmei. Este independent de fila Semnal; secvențele simultane sunt îmbinate. Testare face să clipească "
    L"cadranul sau rama și verifică fișierul, comanda, sunetul, adresa HTTP/HTTPS a scriptului la distanță și,"
    L" dacă este selectat, întregul semnal orar. Oprirea testului oprește sunetul intern și semnalul de probă "
    L"ale acestuia; oprirea alarmei oprește sunetul ei intern. Dezactivarea sunetului nu oprește redarea: "
    L"aceasta continuă în liniște și se aude din nou după reactivare. Comenzile și scripturile la distanță nu "
    L"sunt oprite.\r\n\r\nGlisorul Volum audio din fila Alarmă controlează redarea internă a widgetului. "
    L"Valoarea implicită −18 dB păstrează nivelul inițial al fișierului (100%). Spre dreapta se amplifică "
    L"sunetul; maximul de 0 dB corespunde la aproximativ 794%. −∞ dB înseamnă liniște. Modificările se aud și "
    L"în timpul testului. MIDI și fișierele care nu pot fi "
    L"decodificate și sunt redate prin metoda de rezervă sunt limitate la 100%.",
    L"\r\n\r\nΕισαγωγή ώρας και ενέργειες αφύπνισης\r\nΗ ώρα αφύπνισης δέχεται HH:mm με άνω και κάτω τελεία, "
    L"τελεία, κενό, άλλο διαχωριστικό ή χωρίς διαχωριστικό. Ένα ή δύο ψηφία είναι ώρες, τρία ή τέσσερα ώρες "
    L"και λεπτά: 7, 12, 730, 0730 ή 7:30. Με την έξοδο από το πεδίο γίνεται HH:mm. Η μετατόπιση διαβάζεται από"
    L" δεξιά, αρχίζοντας από δευτερόλεπτα: 2 σημαίνει 00:00:02.00, 230 και 0230 σημαίνουν 00:02:30.00, 12345 "
    L"σημαίνει 01:23:45.00. Με διαχωριστικά, δύο ομάδες είναι λεπτά και δευτερόλεπτα, τρεις ώρες, λεπτά και "
    L"δευτερόλεπτα, η τέταρτη εκατοστά δευτερολέπτου· επιτρέπεται πρόσημο. Οι ημέρες κάτω από Ξυπνητήρι ενεργό"
    L" ορίζουν πότε λειτουργεί· αρχικά είναι όλες επιλεγμένες. Η σειρά ακολουθεί τη γλώσσα της εφαρμογής, αλλά"
    L" η αλλαγή γλώσσας δεν αλλάζει τις αποθηκευμένες ημέρες.\r\n\r\nΤο ξυπνητήρι εμφανίζει κρυφό στοιχείο και"
    L" το φέρνει μπροστά χωρίς μόνιμη αλλαγή του Πάντα σε πρώτο πλάνο. Η Αναπαραγωγή σήματος ώρας αρχίζει τον "
    L"πρώτο σύντομο τόνο πέντε δευτερόλεπτα πριν από την αφύπνιση. Είναι ανεξάρτητη από την καρτέλα Σήμα· οι "
    L"ταυτόχρονες ακολουθίες ενώνονται. Η Δοκιμή αναβοσβήνει το καντράν ή το περίγραμμα και ελέγχει αρχείο, "
    L"εντολή, ήχο, διεύθυνση HTTP/HTTPS απομακρυσμένου σεναρίου και, αν επιλεγεί, ολόκληρο το σήμα ώρας. Η "
    L"διακοπή δοκιμής σταματά τον εσωτερικό ήχο και το δοκιμαστικό σήμα της· η διακοπή αφύπνισης τον εσωτερικό"
    L" ήχο της αφύπνισης. Στη σίγαση η αναπαραγωγή συνεχίζεται αθόρυβα και ακούγεται ξανά μετά την κατάργησή "
    L"της. Οι εντολές και τα απομακρυσμένα σενάρια δεν σταματούν.\r\n\r\nΗ Ένταση ήχου στην καρτέλα Ξυπνητήρι "
    L"ελέγχει την εσωτερική αναπαραγωγή αυτού του στοιχείου. Τα προεπιλεγμένα −18 dB διατηρούν το αρχικό "
    L"επίπεδο του αρχείου (100%). Προς τα δεξιά ο ήχος ενισχύεται· τα μέγιστα 0 dB αντιστοιχούν περίπου σε "
    L"794%. Το −∞ dB είναι σιωπή. Οι αλλαγές ακούγονται και στη δοκιμή. "
    L"MIDI και αρχεία που δεν αποκωδικοποιούνται και αναπαράγονται με εφεδρική μέθοδο "
    L"περιορίζονται στο 100%.",
    L"\r\n\r\nUnos vremena i radnje alarma\r\nVrijeme alarma prihvata HH:mm s dvotačkom, tačkom, razmakom ili "
    L"drugim razdjelnikom; razdjelnik se može izostaviti. Jedna ili dvije znamenke označavaju sate, a tri ili "
    L"četiri sate i minute, primjerice 7, 12, 730, 0730 ili 7:30. Nakon napuštanja polja vrijednost se "
    L"pretvara u HH:mm. Pomak se čita zdesna, počevši od sekundi: 2 znači 00:00:02.00, 230 i 0230 znače "
    L"00:02:30.00, a 12345 znači 01:23:45.00. Uz razdjelnike dvije skupine znače minute i sekunde, tri sate, "
    L"minute i sekunde, a četvrta sadrži stotinke; dopušten je predznak. Dani ispod opcije Alarm uključen "
    L"određuju dane u sedmici kada se alarm pokreće; podrazumijevano su odabrani svi dani. Redoslijed prati "
    L"jezik programa, a promjena jezika ne mijenja sačuvane dane. Aktivirani alarm prikazuje skriveni vidžet i"
    L" dovodi ga ispred drugih prozora bez trajne promjene postavke Uvijek na vrhu. Reproduciraj vremenski "
    L"signal pokreće prvi kratki ton pet sekundi prije vremena alarma. Ta je opcija nezavisna o kartici "
    L"Signal, ali istovremeni se nizovi spajaju. Testiraj uključuje treperenje odabranog brojčanika ili okvira"
    L" ploče i provjerava datoteku, naredbu, zvuk, HTTP/HTTPS adresu udaljene skripte te, ako je odabrano, "
    L"cijeli niz vremenskog signala. Zaustavljanje testa prekida njegov unutrašnji zvuk i probni signal; "
    L"zaustavljanje alarma prekida njegov unutrašnji zvuk. Isključivanje zvuka ne zaustavlja reprodukciju: ona"
    L" se nastavlja nečujno i ponovno se čuje nakon uključivanja zvuka. Naredbe i udaljene skripte ostaju "
    L"aktivne.\r\n\r\nKlizač Glasnoća zvuka na kartici Alarm podešava glasnoću zvučnih datoteka koje program "
    L"reproducira za taj vidžet. Podrazumijevanih −18 dB čuva izvornu razinu datoteke (100%). Pomicanje udesno"
    L" pojačava zvuk; najvećih 0 dB odgovara približno 794%. Položaj −∞ dB znači tišinu. Promjene se čuju i "
    L"tokom testa. MIDI i datoteke koje se ne mogu dekodirati pa se "
    L"reproduciraju zamjenskim načinom ograničene su na 100%.",
    L"\r\n\r\nUnos vremena i radnje alarma\r\nVrijeme alarma prihvaća HH:mm s dvotočkom, točkom, razmakom ili "
    L"drugim razdjelnikom; razdjelnik se može izostaviti. Jedna ili dvije znamenke označavaju sate, a tri ili "
    L"četiri sate i minute, primjerice 7, 12, 730, 0730 ili 7:30. Nakon napuštanja polja vrijednost se "
    L"pretvara u HH:mm. Pomak se čita zdesna, počevši od sekundi: 2 znači 00:00:02.00, 230 i 0230 znače "
    L"00:02:30.00, a 12345 znači 01:23:45.00. Uz razdjelnike dvije skupine znače minute i sekunde, tri sate, "
    L"minute i sekunde, a četvrta sadrži stotinke; dopušten je predznak. Dani ispod opcije Alarm uključen "
    L"određuju dane u tjednu kada se alarm pokreće; zadano su odabrani svi dani. Redoslijed prati jezik "
    L"programa, a promjena jezika ne mijenja spremljene dane. Aktivirani alarm prikazuje skriveni widget i "
    L"dovodi ga ispred drugih prozora bez trajne promjene postavke Uvijek na vrhu. Reproduciraj vremenski "
    L"signal pokreće prvi kratki ton pet sekundi prije vremena alarma. Ta je opcija neovisna o kartici Signal,"
    L" ali istodobni se nizovi spajaju. Testiraj uključuje treperenje odabranog brojčanika ili okvira ploče i "
    L"provjerava datoteku, naredbu, zvuk, HTTP/HTTPS adresu udaljene skripte te, ako je odabrano, cijeli niz "
    L"vremenskog signala. Zaustavljanje testa prekida njegov unutarnji zvuk i probni signal; zaustavljanje "
    L"alarma prekida njegov unutarnji zvuk. Isključivanje zvuka ne zaustavlja reprodukciju: ona se nastavlja "
    L"nečujno i ponovno se čuje nakon uključivanja zvuka. Naredbe i udaljene skripte ostaju "
    L"aktivne.\r\n\r\nKlizač Glasnoća zvuka na kartici Alarm podešava glasnoću zvučnih datoteka koje program "
    L"reproducira za taj widget. Zadanih −18 dB čuva izvornu razinu datoteke (100%). Pomicanje udesno pojačava"
    L" zvuk; najvećih 0 dB odgovara približno 794%. Položaj −∞ dB znači tišinu. Promjene se čuju i tijekom "
    L"testa. MIDI i datoteke koje se ne mogu dekodirati pa se "
    L"reproduciraju zamjenskim načinom ograničene su na 100%.",
    L"\r\n\r\nVnos časa in dejanja budilke\r\nČas budilke sprejema HH:mm z dvopičjem, piko, presledkom ali "
    L"drugim ločilom, lahko tudi brez ločila. Ena ali dve števki pomenita ure, tri ali štiri pa ure in minute:"
    L" 7, 12, 730, 0730 ali 7:30. Po odhodu iz polja se vrednost poenoti v HH:mm. Odmik se bere z desne, od "
    L"sekund: 2 pomeni 00:00:02.00, 230 in 0230 pomenita 00:02:30.00, 12345 pa 01:23:45.00. Z ločili dve "
    L"skupini pomenita minute in sekunde, tri ure, minute in sekunde, četrta pa stotinke; dovoljen je "
    L"predznak. Dnevi pod Budilka vključena določajo dneve sprožitve; privzeto so izbrani vsi. Vrstni red "
    L"sledi jeziku programa, sprememba jezika pa ne spremeni shranjenih dni. Budilka pokaže skriti gradnik in "
    L"ga postavi v ospredje brez trajne spremembe Vedno na vrhu. Predvajaj časovni signal začne prvi kratek "
    L"pisk pet sekund pred budilko. Nastavitev je neodvisna od zavihka Signal; sočasna zaporedja se združijo. "
    L"Preizkusi sproži utripanje številčnice ali okvira ter preveri datoteko, ukaz, zvok, naslov HTTP/HTTPS "
    L"oddaljenega skripta in po potrebi celoten časovni signal. Ustavitev preizkusa ustavi njegov notranji "
    L"zvok in poskusni signal; ustavitev budilke ustavi njen notranji zvok. Izklop zvoka ne ustavi "
    L"predvajanja: nadaljuje se neslišno in po vklopu spet postane slišno. Ukazi in oddaljeni skripti niso "
    L"prizadeti.\r\n\r\nDrsnik Glasnost zvoka na zavihku Budilka uravnava notranje predvajanje za posamezni "
    L"gradnik. Privzetih −18 dB ohrani izvirno raven datoteke (100%). Pomik v desno ojača zvok; največjih 0 dB"
    L" pomeni približno 794%. −∞ dB pomeni tišino. Spremembe se slišijo tudi med preizkusom. "
    L"MIDI in datoteke, ki jih ni mogoče dekodirati in se predvajajo z nadomestnim "
    L"načinom, so omejene na 100%.",
    L"\r\n\r\nUnos vremena i radnje alarma\r\nVrijeme alarma prihvata HH:mm sa dvotačkom, tačkom, razmakom ili"
    L" drugim razdvajačem, a može i bez njega. Jedna ili dvije cifre znače sate, tri ili četiri sate i minute:"
    L" 7, 12, 730, 0730 ili 7:30. Po napuštanju polja vrijednost se pretvara u HH:mm. Pomak se čita zdesna, "
    L"počev od sekundi: 2 znači 00:00:02.00, 230 i 0230 znače 00:02:30.00, a 12345 znači 01:23:45.00. Sa "
    L"razdvajačima dvije grupe su minuti i sekunde, tri sati, minuti i sekunde, a četvrta sadrži stotinke; "
    L"dozvoljen je predznak. Dani ispod Alarm uključen određuju dane pokretanja; podrazumijevano su izabrani "
    L"svi. Redoslijed prati jezik programa, a promjena jezika ne mijenja sačuvane dane. Alarm prikazuje "
    L"skriveni vidžet i dovodi ga ispred drugih prozora bez trajne promjene Uvijek na vrhu. Pusti vremenski "
    L"signal počinje prvi kratak ton pet sekundi prije alarma. Postavka je nezavisna od kartice Signal; "
    L"istovremene sekvence se spajaju. Testiraj uključuje treperenje brojčanika ili okvira i provjerava "
    L"datoteku, naredbu, zvuk, HTTP/HTTPS adresu udaljene skripte i, ako je izabrano, cijeli vremenski signal."
    L" Zaustavljanje testa zaustavlja njegov unutrašnji zvuk i probni signal; zaustavljanje alarma zaustavlja "
    L"njegov unutrašnji zvuk. Isključivanje zvuka ne prekida reprodukciju: ona se nastavlja nečujno i ponovo "
    L"se čuje nakon uključivanja. Naredbe i udaljene skripte ostaju aktivne.\r\n\r\nKlizač Jačina zvuka na "
    L"kartici Alarm podešava unutrašnju reprodukciju za taj vidžet. Podrazumijevanih −18 dB čuva izvorni nivo "
    L"datoteke (100%). Pomjeranje udesno pojačava zvuk; najvećih 0 dB odgovara približno 794%. −∞ dB je "
    L"tišina. Promjene se čuju i tokom testa. MIDI i datoteke koje ne"
    L" mogu da se dekodiraju i puštaju se rezervnim načinom ograničeni su na 100%.",
    L"\r\n\r\nУвод часу і дзеянні будзільніка\r\nЧас будзільніка прымае HH:mm з двукроп’ем, кропкай, прабелам "
    L"ці іншым раздзяляльнікам або без яго. Адна ці дзве лічбы азначаюць гадзіны, тры ці чатыры — гадзіны і "
    L"хвіліны: 7, 12, 730, 0730 або 7:30. Пасля выхаду з поля значэнне прыводзіцца да HH:mm. Зрушэнне "
    L"разбіраецца справа, пачынаючы з секунд: 2 азначае 00:00:02.00, 230 і 0230 — 00:02:30.00, а 12345 — "
    L"01:23:45.00. З раздзяляльнікамі дзве групы азначаюць хвіліны і секунды, тры — гадзіны, хвіліны і "
    L"секунды, чацвёртая — сотыя долі секунды; дазволены знак. Дні пад сцяжком «Будзільнік уключаны» "
    L"вызначаюць дні спрацоўвання; спачатку выбраныя ўсе. Парадак адпавядае мове праграмы, але змена мовы не "
    L"змяняе захаваныя дні. Будзільнік паказвае схаваны віджэт і выводзіць яго наперад без пастаяннай змены "
    L"«Заўсёды зверху». «Прайграваць сігнал часу» пачынае першы кароткі сігнал за пяць секунд да будзільніка. "
    L"Гэта не залежыць ад укладкі «Сігнал»; адначасовыя паслядоўнасці аб’ядноўваюцца. «Праверыць» уключае "
    L"мігценне цыферблата або рамкі ды правярае файл, каманду, гук, HTTP/HTTPS-адрас аддаленага скрыпта і, "
    L"калі выбрана, поўны сігнал часу. Спыненне тэсту спыняе яго ўнутраны гук і пробны сігнал; спыненне "
    L"будзільніка спыняе яго ўнутраны гук. Пры выключэнні гуку прайграванне працягваецца бязгучна і зноў "
    L"становіцца чутным пасля ўключэння. Каманды і аддаленыя скрыпты не закранаюцца.\r\n\r\nПаўзунок «Гучнасць"
    L" гуку» на ўкладцы «Будзільнік» задае гучнасць унутранага прайгравання для віджэта. Прадвызначаныя −18 дБ"
    L" захоўваюць зыходны ўзровень файла (100%). Рух управа ўзмацняе гук; максімум 0 дБ адпавядае прыблізна "
    L"794%. −∞ дБ азначае цішыню. Змены чутныя і падчас тэсту. MIDI і "
    L"файлы, якія не ўдалося дэкадаваць і якія прайграюцца запасным спосабам, абмежаваныя 100%.",
    L"\r\n\r\nВъвеждане на час и действия на алармата\r\nЧасът на алармата приема HH:mm с двоеточие, точка, "
    L"интервал или друг разделител, както и без разделител. Една или две цифри означават часове, три или "
    L"четири — часове и минути: 7, 12, 730, 0730 или 7:30. При напускане на полето стойността се преобразува в"
    L" HH:mm. Отместването се чете отдясно, започвайки от секундите: 2 означава 00:00:02.00, 230 и 0230 — "
    L"00:02:30.00, а 12345 — 01:23:45.00. С разделители две групи са минути и секунди, три — часове, минути и "
    L"секунди, а четвъртата — стотни; допуска се знак. Дните под „Алармата е включена“ определят кога се "
    L"задейства; първоначално са избрани всички дни. Редът следва езика на програмата, но смяната на езика не "
    L"променя записаните дни. Алармата показва скрития модул и го извежда отпред без постоянна промяна на "
    L"„Винаги отгоре“. „Възпроизвеждай сигнал за време“ започва първия кратък тон пет секунди преди часа на "
    L"алармата. Настройката е независима от раздела „Сигнал“; едновременните поредици се обединяват. „Тествай“"
    L" включва мигането на циферблата или рамката и проверява файла, командата, звука, HTTP/HTTPS адреса на "
    L"отдалечения скрипт и при избор — пълната поредица на сигнала за време. Спирането на теста прекратява "
    L"неговия вътрешен звук и пробен сигнал; спирането на алармата прекратява нейния вътрешен звук. При "
    L"изключен звук възпроизвеждането продължава беззвучно и се чува отново след включване. Командите и "
    L"отдалечените скриптове не се засягат.\r\n\r\nПлъзгачът „Сила на звука“ в раздела „Аларма“ управлява "
    L"вътрешното възпроизвеждане за този модул. Стойността по подразбиране −18 dB запазва първоначалното ниво "
    L"на файла (100%). Преместването надясно усилва звука; максимумът 0 dB съответства на около 794%. −∞ dB "
    L"означава тишина. Промените се чуват и при тест. MIDI и "
    L"файловете, които не могат да бъдат декодирани и се възпроизвеждат по резервния начин, са ограничени до "
    L"100%.",
    L"\r\n\r\nВнесување време и дејства на алармот\r\nВремето на алармот прифаќа HH:mm со две точки, точка, "
    L"празно место или друг разделувач, како и без разделувач. Една или две цифри значат часови, три или "
    L"четири — часови и минути: 7, 12, 730, 0730 или 7:30. По напуштање на полето вредноста се претвора во "
    L"HH:mm. Поместувањето се чита оддесно, почнувајќи од секундите: 2 значи 00:00:02.00, 230 и 0230 — "
    L"00:02:30.00, а 12345 — 01:23:45.00. Со разделувачи две групи се минути и секунди, три се часови, минути "
    L"и секунди, а четвртата содржи стотинки; дозволен е предзнак. Деновите под „Алармот е вклучен“ ги "
    L"одредуваат деновите на активирање; стандардно се избрани сите. Редоследот го следи јазикот на "
    L"програмата, но промената на јазикот не ги менува зачуваните денови. Алармот го покажува скриениот виџет "
    L"и го носи пред другите прозорци без трајно менување на „Секогаш најгоре“. „Пушти временски сигнал“ го "
    L"почнува првиот краток тон пет секунди пред алармот. Ова е независно од картичката „Сигнал“; "
    L"истовремените низи се спојуваат. „Тестирај“ го вклучува трепкањето на бројчаникот или рамката и ги "
    L"проверува датотеката, наредбата, звукот, HTTP/HTTPS-адресата на оддалечената скрипта и, ако е избрано, "
    L"целиот временски сигнал. Запирањето на тестот ги запира неговиот внатрешен звук и пробниот сигнал; "
    L"запирањето на алармот го запира неговиот внатрешен звук. Исклучувањето на звукот не ја запира "
    L"репродукцијата: таа продолжува нечујно и повторно се слуша по вклучување. Наредбите и оддалечените "
    L"скрипти не се засегнати.\r\n\r\nЛизгачот „Гласност на звукот“ на картичката „Аларм“ го поставува "
    L"внатрешното пуштање звук за тој виџет. Стандардните −18 dB го зачувуваат изворното ниво на датотеката "
    L"(100%). Поместувањето надесно го засилува звукот; најголемите 0 dB одговараат на приближно 794%. −∞ dB е"
    L" тишина. Промените се слушаат и за време на тест. MIDI и "
    L"датотеките што не може да се декодираат и се пуштаат со резервниот начин се ограничени на 100%.",
    L"\r\n\r\nУнос времена и радње аларма\r\nВреме аларма прихвата HH:mm са двотачком, тачком, размаком или "
    L"другим раздвајачем, а може и без њега. Једна или две цифре значе сате, три или четири сате и минуте: 7, "
    L"12, 730, 0730 или 7:30. По напуштању поља вредност се претвара у HH:mm. Помак се чита здесна, почев од "
    L"секунди: 2 значи 00:00:02.00, 230 и 0230 значе 00:02:30.00, а 12345 значи 01:23:45.00. Са раздвајачима "
    L"две групе су минути и секунде, три сати, минути и секунде, а четврта садржи стотинке; дозвољен је "
    L"предзнак. Дани испод Аларм укључен одређују дане покретања; подразумевано су изабрани сви. Редослед "
    L"прати језик програма, а промена језика не мења сачуване дане. Аларм приказује скривени виџет и доводи га"
    L" испред других прозора без трајне промене Увек на врху. Пусти временски сигнал почиње први кратак тон "
    L"пет секунди пре аларма. Поставка је независна од картице Сигнал; истовремене секвенце се спајају. "
    L"Тестирај укључује треперење бројчаника или оквира и проверава датотеку, наредбу, звук, HTTP/HTTPS адресу"
    L" удаљене скрипте и, ако је изабрано, цео временски сигнал. Заустављање теста зауставља његов унутрашњи "
    L"звук и пробни сигнал; заустављање аларма зауставља његов унутрашњи звук. Искључивање звука не прекида "
    L"репродукцију: она се наставља нечујно и поново се чује након укључивања. Наредбе и удаљене скрипте "
    L"остају активне.\r\n\r\nКлизач Јачина звука на картици Аларм подешава унутрашњу репродукцију за тај "
    L"виџет. Подразумеваних −18 dB чува изворни ниво датотеке (100%). Померање удесно појачава звук; највећих "
    L"0 dB одговара приближно 794%. −∞ dB је тишина. Промене се чују и током теста. "
    L"MIDI и датотеке које не могу да се декодирају и пуштају се резервним начином ограничени "
    L"су на 100%.",
    L"\r\n\r\nВВЕДЕННЯ ЧАСУ ТА ДІЇ БУДИЛЬНИКА\r\nЧас будильника можна вводити у форматі HH:mm із двокрапкою, "
    L"крапкою, пробілом чи іншим роздільником або без роздільника. Одна чи дві цифри означають години, три чи "
    L"чотири — години та хвилини, наприклад 7, 12, 730, 0730 або 7:30. Після виходу з поля значення приводиться"
    L" до формату HH:mm. Зсув розбирається справа наліво, починаючи із секунд: 2 означає 00:00:02.00, 230 і "
    L"0230 — 00:02:30.00, а 12345 — 01:23:45.00. Якщо є роздільники, дві групи означають хвилини й секунди, три"
    L" — години, хвилини й секунди, а четверта містить соті частки секунди; дозволено вказувати знак. Дні під "
    L"прапорцем «Будильник увімкнено» визначають дні тижня, у які він спрацьовує; спочатку вибрано всі дні. "
    L"Їхній порядок залежить від мови програми, але зміна мови не змінює збережених днів. Під час спрацювання "
    L"прихований віджет стає видимим і виходить на передній план без постійної зміни режиму «Завжди зверху». "
    L"Параметр «Відтворювати сигнал часу» запускає перший короткий сигнал за п’ять секунд до часу будильника. "
    L"Він незалежний від вкладки «Сигнал», але одночасні послідовності об’єднуються. Кнопка «Перевірити» вмикає"
    L" блимання вибраного циферблата або рамки панелі й перевіряє файл, команду, звук, HTTP/HTTPS-адресу "
    L"віддаленого скрипту та, якщо вибрано, повну послідовність сигналу точного часу. Зупинення перевірки "
    L"припиняє вбудоване відтворення звуку та попередній перегляд сигналу; зупинення будильника припиняє його "
    L"вбудоване відтворення. У режимі «Без звуку» відтворення триває беззвучно й знову стає чутним після "
    L"ввімкнення звуку. На команди та віддалені скрипти цей режим не впливає.\r\n\r\nПовзунок «Гучність звуку» "
    L"на вкладці «Будильник» задає гучність звукових файлів, які програма відтворює для цього віджета. Типове "
    L"значення −18 дБ зберігає початковий рівень файлу (100%). Переміщення праворуч підсилює звук; максимум 0 "
    L"дБ відповідає приблизно 794%. Положення −∞ дБ вимикає звук. Зміни чути й під час перевірки. Для "
    L"MIDI та файлів, які не вдалося декодувати й які відтворюються резервним "
    L"програвачем, рівень обмежено 100%.",
    L"\r\n\r\nВВОД ВРЕМЕНИ И ДЕЙСТВИЯ БУДИЛЬНИКА\r\nВремя будильника можно вводить в формате HH:mm с "
    L"двоеточием, точкой, пробелом или другим разделителем либо без разделителя. Одна или две цифры означают "
    L"часы, три или четыре — часы и минуты, например 7, 12, 730, 0730 или 7:30. После выхода из поля значение "
    L"приводится к формату HH:mm. Смещение разбирается справа налево, начиная с секунд: 2 означает 00:00:02.00,"
    L" 230 и 0230 — 00:02:30.00, а 12345 — 01:23:45.00. При наличии разделителей две группы означают минуты и "
    L"секунды, три — часы, минуты и секунды, а четвёртая содержит сотые доли секунды; допускается знак. Дни под"
    L" флажком «Будильник включён» определяют дни недели, в которые он срабатывает; изначально выбраны все дни."
    L" Их порядок зависит от языка программы, но смена языка не меняет сохранённые дни. При срабатывании "
    L"скрытый виджет становится видимым и выходит на передний план без постоянного изменения режима «Поверх "
    L"всех окон». Параметр «Воспроизводить сигнал времени» запускает первый короткий сигнал за пять секунд до "
    L"времени будильника. Он независим от вкладки «Сигнал», но одновременные последовательности объединяются. "
    L"Кнопка «Проверить» включает мигание выбранного циферблата или рамки панели и проверяет файл, команду, "
    L"звук, HTTP/HTTPS-адрес удалённого скрипта и, если выбрано, полную последовательность сигнала точного "
    L"времени. Остановка проверки прекращает встроенное воспроизведение звука и предварительное прослушивание "
    L"сигнала; остановка будильника прекращает его встроенное воспроизведение. В режиме «Без звука» "
    L"воспроизведение продолжается беззвучно и снова становится слышимым после включения звука. На команды и "
    L"удалённые скрипты этот режим не влияет.\r\n\r\nПолзунок «Громкость звука» на вкладке «Будильник» задаёт "
    L"громкость звуковых файлов, которые программа воспроизводит для этого виджета. Значение по умолчанию −18 "
    L"дБ сохраняет исходный уровень файла (100%). Перемещение вправо усиливает звук; максимум 0 дБ "
    L"соответствует примерно 794%. Положение −∞ дБ отключает звук. Изменения слышны и во время проверки. Для "
    L"MIDI и файлов, которые не удалось декодировать и которые "
    L"воспроизводятся резервным проигрывателем, уровень ограничен 100%."
};

const wchar_t* HELP_SELECTION_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nVÝBĚR, KLÁVESY A KOPÍROVÁNÍ DATA\r\nPři otevření Nastavení z ikony v oznamovací oblasti se vybere naposledy zvolený widget"
    L". Nastavení si pamatuje poslední otevřenou kartu a Přidat poslední skutečně přidaný typ. "
    L"Odebrat nebo Del odstraní všechny označené položky až po použití změn. Dvojklik položky zobrazí případně"
    L" skrytý widget, nastaví Zobrazeno a krátce jej zvýrazní. Volba Nastavení v nabídce konkrétního widgetu "
    L"jej v seznamu rovnou vybere. Kliknutí na den v kalendáři datum vybere a zkopíruje do schránky; všechny "
    L"masky jsou dostupné v každém jazyce a slovní formáty používají jazyk widgetu. Výchozí Krátké datum se "
    L"řídí jazykem widgetu. Insert přepne označení aktuální položky a posune kurzor seznamu o řádek dolů. "
    L"Ctrl+C zkopíruje označené widgety. Ctrl+V přidá kopie na konec v pořadí seznamu s příponou názvu podle "
    L"jazyka aplikace. Maximální počet widgetů je 32. Při duplikování nebo vložení se přidají v pořadí pouze "
    L"kopie, které se vejdou do limitu; na zbývající se zobrazí upozornění. Na widgetech Ručičkové hodiny a "
    L"Kalendář s hodinami zvolíte pomocí Alt+0, Alt+1, Alt+2 nebo Alt+3 velikost hlavního ciferníku od "
    L"nejmenší po největší.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nOpening Settings from the notification-area icon returns to the last selected widget. "
    L"Settings remembers the last open tab, and Add remembers the last type actually added. Remove or Del "
    L"removes all selected items when the changes are applied. Double-clicking an item makes a hidden widget "
    L"visible, selects Visible and identifies the widget briefly. Settings in a specific widget menu selects "
    L"that widget in the list. Clicking a calendar day selects it and copies it to the clipboard; each "
    L"calendar has its own format in Settings and its menu. Every pattern is available in every language, "
    L"while textual formats use the widget language. The default Short date follows the widget language. "
    L"Insert toggles the current item and moves the list cursor down one row. Ctrl+C copies selected widgets. "
    L"Ctrl+V appends copies in list order with a name suffix in the application language. Up to 32 widgets are"
    L" allowed. When duplicating or pasting, copies are added in order until the limit is reached; a "
    L"notification appears for the remaining copies. Press Alt+0, Alt+1, Alt+2, or Alt+3 on an Analog clock or"
    L" Calendar with clock widget to select the main clock face size, from smallest to largest.",
    L"\r\n\r\nAUSWAHL, TASTEN UND DATUMSKOPIE\r\nBeim Öffnen der Einstellungen über das Infobereichsymbol werden die Einstellungen des zuletzt ausgewählten Widgets angezeigt. "
    L"Einstellungen merkt sich die zuletzt geöffnete Registerkarte, Hinzufügen den zuletzt hinzugefügten Typ. "
    L"Entfernen oder Entf löscht beim Anwenden alle ausgewählten Einträge. Ein Doppelklick macht ein "
    L"verborgenes Widget sichtbar, aktiviert Sichtbar und kennzeichnet das Widget kurz; Einstellungen im "
    L"Widget-Menü wählt es in der Liste aus. Ein Klick auf einen Kalendertag wählt und kopiert ihn im je "
    L"Widget eingestellten Format. Alle Muster sind in jeder Sprache verfügbar; Textformate verwenden die "
    L"Widget-Sprache. Das voreingestellte Kurze Datum folgt der Widget-Sprache. Einfg schaltet die Markierung "
    L"des aktuellen Eintrags um und bewegt den Listencursor eine Zeile nach unten. Strg+C kopiert ausgewählte "
    L"Widgets. Strg+V fügt Kopien in Listenreihenfolge am Ende hinzu, mit einem Namenszusatz in der "
    L"Anwendungssprache. Maximal 32 Widgets sind möglich. Beim Duplizieren oder Einfügen werden Kopien der "
    L"Reihe nach bis zum Limit hinzugefügt; für die übrigen erscheint ein Hinweis. Mit Alt+0, Alt+1, Alt+2 "
    L"oder Alt+3 wählen Sie bei Analoguhr und Kalender mit Uhr die Größe des Hauptzifferblatts von der "
    L"kleinsten bis zur größten.",
    L"\r\n\r\nSÉLECTION, TOUCHES ET COPIE DE DATE\r\nL’ouverture des paramètres depuis l’icône de notification affiche les paramètres du dernier widget sélectionné. "
    L"Paramètres mémorise le dernier onglet ouvert et Ajouter le dernier type réellement ajouté. Supprimer ou "
    L"Suppr retire toute la sélection lors de l’application. Un double-clic rend visible un widget masqué, "
    L"coche Visible et l’identifie brièvement ; Paramètres dans son menu le sélectionne dans la liste. Cliquer"
    L" sur un jour le sélectionne et le copie selon le format propre au calendrier. Tous les modèles sont "
    L"disponibles dans chaque langue ; les formats textuels utilisent la langue du widget. La Date courte par "
    L"défaut suit la langue du widget. Inser bascule la sélection de l’élément courant et descend le curseur "
    L"de liste d’une ligne. Ctrl+C copie les widgets sélectionnés. Ctrl+V ajoute les copies à la fin dans "
    L"l’ordre de la liste, avec un suffixe dans la langue de l’application. Le nombre de widgets est limité à "
    L"32. Lors de la duplication ou du collage, les copies sont ajoutées dans l’ordre jusqu’à la limite ; un "
    L"message signale les copies restantes. Appuyez sur Alt+0, Alt+1, Alt+2 ou Alt+3 dans les widgets Horloge "
    L"analogique et Calendrier avec horloge pour choisir la taille du cadran principal, de la plus petite à la"
    L" plus grande.",
    L"\r\n\r\nSELECCIÓN, TECLAS Y COPIA DE FECHA\r\nAl abrir Configuración desde el icono del área de notificación, se selecciona el último widget elegido. "
    L"Configuración recuerda la última pestaña abierta y Añadir el último tipo realmente añadido. Quitar o "
    L"Supr elimina todos los seleccionados al aplicar los cambios. Un doble clic muestra un widget oculto, "
    L"activa Visible y lo identifica brevemente; Configuración en su menú lo selecciona en la lista. Pulsar un"
    L" día lo selecciona y copia según el formato propio del calendario; los formatos de texto usan el idioma "
    L"del widget. Todos los patrones están disponibles en cualquier idioma y la Fecha corta predeterminada "
    L"sigue el idioma del widget. Insert alterna la selección del elemento actual y baja el cursor de la lista"
    L" una fila. Ctrl+C copia los widgets seleccionados. Ctrl+V añade las copias al final en el orden de la "
    L"lista, con un sufijo en el idioma de la aplicación. Se permiten hasta 32 widgets. Al duplicar o pegar, "
    L"las copias se añaden en orden hasta alcanzar el límite; se muestra un aviso para las restantes. Pulse "
    L"Alt+0, Alt+1, Alt+2 o Alt+3 en Reloj analógico o Calendario con reloj para elegir el tamaño de la esfera"
    L" principal, del menor al mayor.",
    L"\r\n\r\nSELEZIONE, TASTI E COPIA DELLA DATA\r\nAprendo le impostazioni dall’icona nell’area di notifica, viene selezionato l’ultimo widget scelto. Impostazioni "
    L"ricorda l’ultima scheda aperta e Aggiungi l’ultimo tipo realmente aggiunto. Rimuovi o Canc elimina tutti"
    L" gli elementi selezionati quando si applicano le modifiche. Un doppio clic rende visibile un widget "
    L"nascosto, seleziona Visibile e lo identifica brevemente; Impostazioni nel suo menu lo seleziona "
    L"nell’elenco. Il clic su un giorno lo seleziona e lo copia nel formato del calendario; i formati testuali"
    L" usano la lingua del widget. Tutti i modelli sono disponibili in ogni lingua e la Data breve predefinita"
    L" segue la lingua del widget. Ins commuta la selezione dell’elemento corrente e sposta il cursore "
    L"dell’elenco una riga in basso. Ctrl+C copia i widget selezionati. Ctrl+V aggiunge le copie in fondo "
    L"nell’ordine dell’elenco, con un suffisso nella lingua dell’applicazione. Sono consentiti fino a 32 "
    L"widget. Quando si duplica o incolla, le copie vengono aggiunte in ordine fino al limite; un avviso "
    L"segnala quelle rimanenti. Premere Alt+0, Alt+1, Alt+2 o Alt+3 nei widget Orologio analogico e Calendario"
    L" con orologio per scegliere la dimensione del quadrante principale, dalla più piccola alla più grande.",
    L"\r\n\r\nZAZNACZANIE, KLAWISZE I KOPIOWANIE DATY\r\nOtwarcie ustawień z ikony w obszarze powiadomień przywraca ostatnio wybrany widżet. "
    L"Ustawienia pamiętają ostatnio otwartą kartę, a Dodaj ostatnio rzeczywiście dodany typ. Usuń lub Del "
    L"usuwa wszystkie zaznaczone pozycje po zastosowaniu zmian. Dwuklik pokazuje ukryty widżet, zaznacza "
    L"Widoczny i krótko go wskazuje; Ustawienia w jego menu wybierają go na liście. Kliknięcie dnia wybiera go"
    L" i kopiuje w formacie danego kalendarza. Wszystkie wzorce są dostępne w każdym języku, a formaty słowne "
    L"używają języka widżetu. Domyślna Data krótka zależy od języka widżetu. Insert przełącza zaznaczenie "
    L"bieżącej pozycji i przesuwa kursor listy o jeden wiersz w dół. Ctrl+C kopiuje zaznaczone widżety. Ctrl+V"
    L" dodaje kopie na końcu w kolejności listy, z przyrostkiem w języku aplikacji. Dozwolone są maksymalnie "
    L"32 widżety. Podczas powielania lub wklejania kopie są dodawane w kolejności do osiągnięcia limitu; dla "
    L"pozostałych pojawia się powiadomienie. W widżetach Zegar analogowy i Kalendarz z zegarem klawisze Alt+0,"
    L" Alt+1, Alt+2 i Alt+3 wybierają rozmiar głównej tarczy od najmniejszego do największego.",
    L"\r\n\r\nVÝBER, KLÁVESY A KOPÍROVANIE DÁTUMU\r\nNastavenia otvorené z ikony v oblasti oznámení obnovia naposledy vybraný widget. "
    L"Nastavenie si pamätá poslednú otvorenú kartu a Pridať posledný skutočne pridaný typ. Odobrať alebo Del "
    L"odstráni po použití zmien všetky označené položky. Dvojklik zobrazí skrytý widget, začiarkne Zobrazené a"
    L" krátko ho zvýrazní; Nastavenia v jeho ponuke ho vyberú v zozname. Kliknutie na deň ho vyberie a "
    L"skopíruje vo formáte daného kalendára. Všetky masky sú dostupné v každom jazyku, slovné formáty "
    L"používajú jazyk widgetu a predvolený Krátky dátum sa riadi jazykom widgetu. Insert prepne označenie "
    L"aktuálnej položky a posunie kurzor zoznamu o riadok nižšie. Ctrl+C skopíruje označené widgety. Ctrl+V "
    L"pridá kópie na koniec v poradí zoznamu s príponou podľa jazyka aplikácie. Maximálny počet widgetov je "
    L"32. Pri duplikovaní alebo vložení sa pridajú v poradí iba kópie, ktoré sa zmestia do limitu; na "
    L"zostávajúce sa zobrazí upozornenie. Na widgetoch Ručičkové hodiny a Kalendár s hodinami zvolíte pomocou "
    L"Alt+0, Alt+1, Alt+2 alebo Alt+3 veľkosť hlavného ciferníka od najmenšej po najväčšiu.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nOpening Settings from the notification-area icon returns to the last selected widget. "
    L"Settings remembers the last open tab, and Add remembers the last type actually added. Remove or Del "
    L"removes all selected items when the changes are applied. Double-clicking an item makes a hidden widget "
    L"visible, selects Visible and identifies the widget briefly. Settings in a specific widget menu selects "
    L"that widget in the list. Clicking a calendar day selects it and copies it to the clipboard; each "
    L"calendar has its own format in Settings and its menu. Every pattern is available in every language, "
    L"while textual formats use the widget language. The default Short date follows the widget language. "
    L"Insert toggles the current item and moves the list cursor down one row. Ctrl+C copies selected widgets. "
    L"Ctrl+V appends copies in list order with a name suffix in the application language. Up to 32 widgets are"
    L" allowed. When duplicating or pasting, copies are added in order until the limit is reached; a "
    L"notification appears for the remaining copies. Press Alt+0, Alt+1, Alt+2, or Alt+3 on an Analog clock or"
    L" Calendar with clock widget to select the main clock face size, from smallest to largest.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nOpening Settings from the notification-area icon returns to the last selected widget. "
    L"Settings remembers the last open tab, and Add remembers the last type actually added. Remove or Del "
    L"removes all selected items when the changes are applied. Double-clicking an item makes a hidden widget "
    L"visible, selects Visible and identifies the widget briefly. Settings in a specific widget menu selects "
    L"that widget in the list. Clicking a calendar day selects it and copies it to the clipboard; each "
    L"calendar has its own format in Settings and its menu. Every pattern is available in every language, "
    L"while textual formats use the widget language. The default Short date follows the widget language. "
    L"Insert toggles the current item and moves the list cursor down one row. Ctrl+C copies selected widgets. "
    L"Ctrl+V appends copies in list order with a name suffix in the application language. Up to 32 widgets are"
    L" allowed. When duplicating or pasting, copies are added in order until the limit is reached; a "
    L"notification appears for the remaining copies. Press Alt+0, Alt+1, Alt+2, or Alt+3 on an Analog clock or"
    L" Calendar with clock widget to select the main clock face size, from smallest to largest.",
    L"\r\n\r\nSELEÇÃO E DATA\r\nAo abrir as definições pelo ícone da área de notificação, é selecionado o último widget escolhido. Um clique direito e Definições seleciona o widget correspondente."
    L" Delete remove os widgets selecionados. Um duplo clique numa "
    L"entrada torna o widget visível e realça-o brevemente. Num calendário, clicar num dia seleciona-o e "
    L"copia-o no formato escolhido; todos os formatos estão disponíveis em todos os idioma"
    L"s. Insert alterna a seleção do item atual e desloca o cursor da lista uma"
    L" linha para baixo. Ctrl+C copia os widgets selecionados. Ctrl+V acrescenta cópias no fim pela ordem da "
    L"lista, com um sufixo no idioma da aplicação. São permitidos até 32 widgets. Ao duplicar ou colar, as "
    L"cópias são acrescentadas pela ordem até ao limite; é apresentado um aviso sobre as restantes. Prima "
    L"Alt+0, Alt+1, Alt+2 ou Alt+3 nos widgets Relógio analógico e Calendário com relógio para escolher o "
    L"tamanho do mostrador principal, do menor ao maior.",
    L"\r\n\r\nVALG OG DATO\r\nNår innstillingene åpnes fra ikonet i systemstatusfeltet, velges den sist valgte widgeten igjen. Høyreklikk og Innstillinger velger den aktuelle widgeten."
    L" Delete fjerner valgte widgeter. Dobbeltklikk på en oppføring gjør widgeten "
    L"synlig og fremhever den kort. Klikk på en dag i kalenderen for å velge og kopiere den i valgt format; "
    L"alle formater er tilgjengelige på alle språk"
    L". Insert veksler markeringen av gjeldende "
    L"oppføring og flytter listepekeren én rad ned. Ctrl+C kopierer valgte widgeter. Ctrl+V legger kopier "
    L"nederst i listens rekkefølge med et navnetillegg på programspråket. Opptil 32 widgeter er tillatt. Ved "
    L"duplisering eller innliming legges kopier til i rekkefølge til grensen er nådd; et varsel vises for "
    L"resten. Trykk Alt+0, Alt+1, Alt+2 eller Alt+3 på Analog klokke eller Kalender med klokke for å velge "
    L"størrelsen på hovedurskiven, fra minst til størst.",
    L"\r\n\r\nMARKERING OCH DATUM\r\nNär inställningarna öppnas från ikonen i meddelandefältet visas inställningarna för den senast valda widgeten. Högerklick och Inställningar markerar den aktuella widgeten."
    L" Delete tar bort markerade widgetar. Dubbelklick på en post "
    L"visar widgeten och markerar den kort. Klicka på en dag i kalendern för att välja och kopiera den i valt "
    L"format; alla format finns på alla språk"
    L". Insert växlar markeringen av den aktuella"
    L" posten och flyttar listmarkören en rad ned. Ctrl+C kopierar markerade widgetar. Ctrl+V lägger kopior "
    L"sist i listordning med ett namntillägg på programspråket. Upp till 32 widgetar tillåts. Vid duplicering "
    L"eller inklistring läggs kopior till i ordning tills gränsen nås; ett meddelande visas för de "
    L"återstående. Tryck Alt+0, Alt+1, Alt+2 eller Alt+3 på Analog klocka eller Kalender med klocka för att "
    L"välja huvudurtavlans storlek, från minst till störst.",
    L"\r\n\r\nVALINTA JA PÄIVÄMÄÄRÄ\r\nKun asetukset avataan ilmoitusalueen kuvakkeesta, viimeksi valittu pienoisohjelma valitaan uudelleen. Napsauta hiiren kakkospainikkeella ja valitse Asetukset valitaksesi "
    L"kyseisen pienoisohjelman. Delete poistaa valitut "
    L"pienoisohjelmat. Luettelon kaksoisnapsautus näyttää pienoisohjelman ja korostaa sen hetkeksi. "
    L"Kalenteripäivän napsautus valitsee ja kopioi sen valitussa muodossa; kaikki muodot ovat käytettävissä "
    L"kaikilla kielill"
    L"ä. Insert vaihtaa nykyisen kohteen valinnan ja "
    L"siirtää luettelokohdistinta yhden rivin alaspäin. Ctrl+C kopioi valitut pienoisohjelmat. Ctrl+V lisää "
    L"kopiot loppuun luettelon järjestyksessä ja liittää nimeen sovelluksen kielisen päätteen. Pienoisohjelmia"
    L" voi olla enintään 32. Monistettaessa tai liitettäessä kopiot lisätään järjestyksessä rajaan asti; "
    L"jäljelle jäävistä näytetään ilmoitus. Valitse pääkellotaulun koko pienimmästä suurimpaan näppäimillä "
    L"Alt+0, Alt+1, Alt+2 tai Alt+3 Analoginen kello- tai Kalenteri ja kello -pienoisohjelmassa.",
    L"\r\n\r\nMARKERING OG DATO\r\nNår indstillingerne åbnes fra ikonet i meddelelsesområdet, vælges den sidst valgte widget igen. Højreklik og Indstillinger markerer den pågældende widget."
    L" Delete fjerner markerede widgets. Dobbeltklik på en post viser widgeten og "
    L"fremhæver den kort. Klik på en kalenderdag for at vælge og kopiere den i det valgte format; alle "
    L"formater findes på alle sprog"
    L". Insert skifter markeringen af det aktuelle element og "
    L"flytter listemarkøren én række ned. Ctrl+C kopierer markerede widgets. Ctrl+V tilføjer kopier nederst i "
    L"listens rækkefølge med et navnetillæg på programmets sprog. Der kan være op til 32 widgets. Ved "
    L"duplikering eller indsættelse tilføjes kopier i rækkefølge indtil grænsen; en meddelelse vises for "
    L"resten. Tryk Alt+0, Alt+1, Alt+2 eller Alt+3 på Analogt ur eller Kalender med ur for at vælge "
    L"hovedurskivens størrelse, fra mindst til størst.",
    L"\r\n\r\nVAL OG DAGSETNING\r\nÞegar stillingar eru opnaðar frá tákninu á tilkynningasvæðinu er síðast valda græjan valin aftur. Hægrismellur og Stillingar velja viðkomandi græju."
    L" Delete fjarlægir valdar græjur. Tvísmellur á færslu sýnir græjuna og auðkennir hana "
    L"stuttlega. Smelltu á dag í dagatali til að velja og afrita hann á völdu sniði; öll snið eru tiltæk á "
    L"öllum tungumálum"
    L". Insert víxlar vali núverandi færslu og færir listabendilinn eina línu "
    L"niður. Ctrl+C afritar valdar græjur. Ctrl+V bætir afritum aftast í röð listans með viðskeyti á tungumáli"
    L" forritsins. Að hámarki eru 32 græjur leyfðar. Við afritun eða límingu er afritum bætt við í röð þar til"
    L" hámarkinu er náð; tilkynning birtist um þau sem eftir eru. Ýttu á Alt+0, Alt+1, Alt+2 eða Alt+3 á "
    L"græjunum Vísaklukka og Dagatal með klukku til að velja stærð aðalskífunnar, frá minnstu til stærstu.",
    L"\r\n\r\nSEÇİM VE TARİH\r\nAyarlar bildirim alanındaki simgeden açıldığında en son seçilen araç yeniden seçilir. Sağ tıklayıp Ayarlar'ı seçmek ilgili aracı seçer. Delete seçili araçları kaldırır. Listedeki bir öğeye çift tıklamak aracı görünür "
    L"yapar ve kısa süre vurgular. Takvimde bir güne tıklamak günü seçili biçimde panoya kopyalar; tüm "
    L"biçimler tüm dillerde"
    L" kullanılabilir. Insert geçerli öğenin seçimini değiştirir"
    L" ve liste imlecini bir satır aşağı taşır. Ctrl+C seçili araçları kopyalar. Ctrl+V kopyaları liste "
    L"sırasıyla sona ekler ve adlarına uygulama dilinde bir ek getirir. En fazla 32 araç kullanılabilir. "
    L"Çoğaltırken veya yapıştırırken kopyalar sınıra kadar sırayla eklenir; kalan kopyalar için bir bildirim "
    L"gösterilir. Analog saat veya Saatli takvim aracında ana kadranın boyutunu küçükten büyüğe seçmek için "
    L"Alt+0, Alt+1, Alt+2 veya Alt+3 tuşlarına basın.",
    L"\r\n\r\nValimine, klahvid ja kuupäeva kopeerimine\r\nOlekuala ikoonilt seadete avamisel taastatakse viimati valitud vidin"
    L". Sätted jätavad meelde viimase vahekaardi ja Lisa viimati lisatud tüübi. Eemalda või Del eemaldab"
    L" kõik valitud üksused muudatuste rakendamisel. Topeltklõps üksusel kuvab peidetud vidina, märgib Nähtav "
    L"ja tõstab vidina korraks esile. Vidina menüü Sätted valib loendis selle vidina. Kalendripäeval "
    L"klõpsamine valib kuupäeva ja kopeerib selle lõikelauale. Igal kalendril on oma kopeerimisvorming sätetes"
    L" ja menüüs. Kõik 33 vormingut on saadaval igas keeles; tekstilised nimetused ja vaikevalik Lühike "
    L"kuupäev järgivad vidina keelt.\r\n\r\nInsert muudab praeguse üksuse valikut ja viib loendikursori ühe "
    L"rea alla. Ctrl+C kopeerib valitud vidinad, Ctrl+V lisab koopiad loendi järjekorras ning nimelaiendi "
    L"rakenduse keeles. Lubatud on kuni 32 vidinat. Koopiad lisatakse järjekorras piirini ja ülejäänute kohta "
    L"kuvatakse teade. Alt+0, Alt+1, Alt+2 ja Alt+3 valivad analoogkella või kalendri ja kella paneeli peamise"
    L" sihverplaadi suuruse väikseimast suurimani.",
    L"\r\n\r\nRoghnú, eochracha agus cóipeáil dátaí\r\nNuair a osclaítear na socruithe ó dheilbhín an limistéir fógraí, roghnaítear an ghiuirléid dheireanach a roghnaíodh. "
    L"Cuimhníonn Socruithe ar an gcluaisín deireanach agus Cuir leis ar an gcineál deireanach a cuireadh leis."
    L" Baineann Bain nó Del gach mír roghnaithe nuair a chuirtear na hathruithe i bhfeidhm. Taispeánann "
    L"déchliceáil ar mhír giuirléid fholaithe, roghnaíonn sé Infheicthe agus aibhsíonn sé í go gairid. "
    L"Roghnaíonn Socruithe i roghchlár giuirléide an ghiuirléid sin sa liosta. Roghnaíonn cliceáil ar lá dáta "
    L"agus cóipeálann sé chuig an ngearrthaisce é. Tá formáid ar leith ag gach féilire sna Socruithe agus ina "
    L"roghchlár. Tá gach ceann de na 33 formáid ar fáil i ngach teanga; leanann ainmneacha téacsúla agus Dáta "
    L"gearr teanga na giuirléide.\r\n\r\nAthraíonn Insert roghnú na míre reatha agus bogann sé cúrsóir an "
    L"liosta síos sraith amháin. Cóipeálann Ctrl+C giuirléidí roghnaithe agus cuireann Ctrl+V cóipeanna leis "
    L"in ord an liosta, le hiarmhír ainm i dteanga an fheidhmchláir. Ceadaítear suas le 32 giuirléid. Cuirtear"
    L" cóipeanna leis in ord go dtí an teorainn agus taispeántar fógra maidir leis an gcuid eile. Roghnaíonn "
    L"Alt+0, Alt+1, Alt+2 agus Alt+3 méid phríomhaghaidh an chloig analógaigh nó an phainéil ón gceann is lú "
    L"go dtí an ceann is mó.",
    L"\r\n\r\nPasirinkimas, klavišai ir datos kopijavimas\r\nAtidarius nuostatas iš pranešimų srities piktogramos, vėl atveriamos paskutinio pasirinkto "
    L"valdiklio nuostatos. Parametrai įsimena paskutinį skirtuką, Įtraukti – paskutinį įtrauktą tipą. Pašalinti arba "
    L"Del pašalina visus pasirinktus elementus pritaikius pakeitimus. Dukart spustelėjus elementą parodomas "
    L"paslėptas valdiklis, pažymimas Matomas ir valdiklis trumpai paryškinamas. Valdiklio meniu Parametrai "
    L"pasirenka jį sąraše. Spustelėjus kalendoriaus dieną pasirenkama data ir nukopijuojama į mainų sritį. "
    L"Kiekvienas kalendorius turi atskirą formatą parametruose ir meniu. Visi 33 formatai prieinami visomis "
    L"kalbomis; tekstiniai pavadinimai ir numatytoji Trumpoji data priklauso nuo valdiklio "
    L"kalbos.\r\n\r\nInsert perjungia dabartinio elemento pasirinkimą ir perkelia sąrašo žymeklį eilute žemyn."
    L" Ctrl+C kopijuoja valdiklius, Ctrl+V įtraukia kopijas sąrašo tvarka su pavadinimo priesaga programos "
    L"kalba. Leidžiama iki 32 valdiklių. Kopijos įtraukiamos iš eilės iki ribos; dėl likusių parodomas "
    L"pranešimas. Alt+0, Alt+1, Alt+2 ir Alt+3 pasirenka analoginio laikrodžio arba kalendoriaus su laikrodžiu"
    L" pagrindinio ciferblato dydį nuo mažiausio iki didžiausio.",
    L"\r\n\r\nAtlase, taustiņi un datuma kopēšana\r\nAtverot iestatījumus no paziņojumu apgabala ikonas, tiek atlasīts pēdējais izvēlētais logrīks. "
    L"Iestatījumi atceras pēdējo cilni, Pievienot – pēdējo pievienoto tipu. Noņemt vai Del noņem visas "
    L"atlasītās vienības pēc izmaiņu lietošanas. Dubultklikšķis uz vienības parāda paslēptu logrīku, atlasa "
    L"Redzams un īslaicīgi izceļ logrīku. Iestatījumi logrīka izvēlnē atlasa to sarakstā. Klikšķis uz "
    L"kalendāra dienas atlasa datumu un kopē to starpliktuvē. Katram kalendāram ir savs formāts iestatījumos "
    L"un izvēlnē. Visi 33 formāti ir pieejami jebkurā valodā; teksta nosaukumi un noklusējuma Īsais datums "
    L"atbilst logrīka valodai.\r\n\r\nInsert pārslēdz pašreizējās vienības atlasi un pārvieto saraksta kursoru"
    L" rindu uz leju. Ctrl+C kopē logrīkus, Ctrl+V pievieno kopijas saraksta secībā ar nosaukuma sufiksu "
    L"programmas valodā. Atļauti līdz 32 logrīkiem. Kopijas pievieno secīgi līdz robežai; par atlikušajām "
    L"parāda paziņojumu. Alt+0, Alt+1, Alt+2 un Alt+3 analogajā pulkstenī vai kalendārā ar pulksteni izvēlas "
    L"galvenās ciparnīcas lielumu no mazākā līdz lielākajam.",
    L"\r\n\r\nKijelölés, billentyűk és dátummásolás\r\nAz értesítési terület ikonjáról megnyitott beállításokban a legutóbb kiválasztott minialkalmazás beállításai jelennek "
    L"meg. A Beállítások az utolsó fület, a Hozzáadás az utoljára hozzáadott típust jegyzi meg. Az Eltávolítás "
    L"vagy Del a módosítások alkalmazásakor minden kijelölt elemet eltávolít. Dupla kattintás megjeleníti a "
    L"rejtett minialkalmazást, bejelöli a Látható értéket, és röviden kiemeli azt. A minialkalmazás menüjének "
    L"Beállítások parancsa kiválasztja azt a listában. A naptár napjára kattintva a dátum kijelölődik és a "
    L"vágólapra másolódik. Minden naptárnak külön formátuma van a beállításokban és menüjében. Mind a 33 "
    L"formátum minden nyelven elérhető; a szöveges nevek és az alapértelmezett Rövid dátum a minialkalmazás "
    L"nyelvét követik.\r\n\r\nAz Insert átváltja az aktuális elem kijelölését, és egy sorral lejjebb lépteti a"
    L" listakurzort. A Ctrl+C másol, a Ctrl+V a lista sorrendjében illeszti hozzá a másolatokat a program "
    L"nyelvén adott névutótaggal. Legfeljebb 32 minialkalmazás lehet. A másolatok sorrendben kerülnek be a "
    L"határig, a többiről értesítés jelenik meg. Az Alt+0, Alt+1, Alt+2 és Alt+3 analóg órán vagy naptár "
    L"órával típuson a fő számlap méretét választja ki a legkisebbtől a legnagyobbig.",
    L"\r\n\r\nGħażla, tastiera u kkupjar tad-data\r\nMeta tiftaħ is-settings mill-ikona taż-żona tan-notifiki, jerġa’ jintgħażel l-aħħar widget magħżul. "
    L"Is-Settings jiftakru l-aħħar tab miftuħ, Żid l-aħħar tip miżjud. Neħħi jew Del ineħħi l-oġġetti magħżula"
    L" meta jiġu applikati l-bidliet. Klikk doppju fuq oġġett juri widget moħbi, jagħżel Viżibbli u "
    L"jenfasizzah għal ftit. Settings fil-menu ta’ widget jagħżel dak il-widget fil-lista. Klikk fuq jum "
    L"jagħżel id-data u jikkopjaha fil-klibbord. Kull kalendarju għandu l-format tiegħu fis-settings u "
    L"fil-menu. It-33 format kollha huma disponibbli f’kull lingwa; ismijiet testwali u Data qasira default "
    L"isegwu l-lingwa tal-widget.\r\n\r\nInsert jaqleb l-għażla tal-oġġett kurrenti u jmexxi l-kursur "
    L"tal-lista ringiela ’l isfel. Ctrl+C jikkopja l-widgets magħżula, Ctrl+V iżid kopji fl-ordni tal-lista "
    L"b’suffiss tal-isem fil-lingwa tal-programm. Il-limitu huwa 32 widget. Il-kopji jiżdiedu fl-ordni "
    L"sal-limitu u tintwera notifika għall-bqija. Alt+0, Alt+1, Alt+2 u Alt+3 fuq arloġġ analogu jew "
    L"kalendarju bl-arloġġ jagħżlu d-daqs tal-wiċċ prinċipali mill-iżgħar sal-akbar.",
    L"\r\n\r\nSelecteren, toetsen en datums kopiëren\r\nWanneer u de instellingen opent via het systeemvakpictogram, wordt de laatst geselecteerde widget opnieuw geselecteerd. "
    L"Instellingen onthoudt het laatste tabblad en Toevoegen het laatst toegevoegde type. Verwijderen of Del "
    L"verwijdert alle geselecteerde items zodra wijzigingen worden toegepast. Dubbelklikken op een item toont "
    L"een verborgen widget, selecteert Zichtbaar en markeert deze kort. Instellingen in het menu van een "
    L"widget selecteert die widget in de lijst. Klikken op een kalenderdag kiest de datum en kopieert deze "
    L"naar het klembord. Elke kalender heeft een eigen indeling in Instellingen en zijn menu. Alle 33 "
    L"indelingen zijn in elke taal beschikbaar; tekstnamen en de standaard Korte datum volgen de "
    L"widgettaal.\r\n\r\nInsert schakelt de selectie van het huidige item om en verplaatst de lijstcursor één "
    L"rij omlaag. Ctrl+C kopieert widgets, Ctrl+V voegt kopieën in lijstvolgorde toe met een naamachtervoegsel"
    L" in de toepassingstaal. Er zijn maximaal 32 widgets toegestaan. Kopieën worden op volgorde toegevoegd "
    L"tot de limiet; voor de rest verschijnt een melding. Alt+0, Alt+1, Alt+2 en Alt+3 kiezen op een analoge "
    L"klok of kalender met klok de grootte van de hoofdwijzerplaat, van klein naar groot.",
    L"\r\n\r\nSelecție, taste și copierea datei\r\nLa deschiderea setărilor din pictograma din zona de notificare, este selectat din nou ultimul widget ales. "
    L"Setări reține ultima filă, iar Adăugare ultimul tip adăugat. Eliminare sau Del elimină toate elementele "
    L"selectate când se aplică modificările. Un dublu clic pe un element afișează widgetul ascuns, bifează "
    L"Vizibil și îl evidențiază scurt. Setări din meniul unui widget îl selectează în listă. Un clic pe o zi "
    L"selectează data și o copiază în clipboard. Fiecare calendar are propriul format în setări și meniu. "
    L"Toate cele 33 de formate sunt disponibile în orice limbă; numele textuale și formatul implicit Dată "
    L"scurtă urmează limba widgetului.\r\n\r\nInsert comută selecția elementului curent și deplasează cursorul"
    L" listei un rând în jos. Ctrl+C copiază widgeturile, Ctrl+V adaugă copii în ordinea listei, cu un sufix "
    L"al numelui în limba aplicației. Sunt permise până la 32 de widgeturi. Copiile se adaugă în ordine până "
    L"la limită; pentru restul apare o notificare. Alt+0, Alt+1, Alt+2 și Alt+3 pe un ceas analogic sau "
    L"calendar cu ceas aleg dimensiunea cadranului principal de la cea mai mică la cea mai mare.",
    L"\r\n\r\nΕπιλογή, πλήκτρα και αντιγραφή ημερομηνίας\r\nΤο άνοιγμα των ρυθμίσεων από το εικονίδιο της περιοχής ειδοποιήσεων επαναφέρει το τελευταίο επιλεγμένο γραφικό στοιχείο. Οι "
    L"Ρυθμίσεις θυμούνται την τελευταία καρτέλα και η Προσθήκη τον τελευταίο τύπο που προστέθηκε. Κατάργηση ή "
    L"Del καταργεί όλα τα επιλεγμένα στοιχεία όταν εφαρμοστούν οι αλλαγές. Το διπλό κλικ σε καταχώρηση "
    L"εμφανίζει το κρυφό στοιχείο, επιλέγει Ορατό και το επισημαίνει για λίγο. Οι Ρυθμίσεις από μενού "
    L"στοιχείου το επιλέγουν στη λίστα. Το κλικ σε ημέρα επιλέγει την ημερομηνία και την αντιγράφει στο "
    L"πρόχειρο. Κάθε ημερολόγιο έχει δική του μορφή στις ρυθμίσεις και στο μενού. Και οι 33 μορφές διατίθενται"
    L" σε κάθε γλώσσα· τα ονόματα και η προεπιλεγμένη Σύντομη ημερομηνία ακολουθούν τη γλώσσα του "
    L"στοιχείου.\r\n\r\nΤο Insert αλλάζει την επιλογή της τρέχουσας καταχώρησης και μετακινεί τον δρομέα μία "
    L"γραμμή κάτω. Το Ctrl+C αντιγράφει στοιχεία, το Ctrl+V προσθέτει αντίγραφα με τη σειρά της λίστας και "
    L"επίθημα ονόματος στη γλώσσα της εφαρμογής. Επιτρέπονται έως 32 στοιχεία. Τα αντίγραφα προστίθενται με τη"
    L" σειρά μέχρι το όριο, με ειδοποίηση για τα υπόλοιπα. Alt+0, Alt+1, Alt+2 και Alt+3 σε αναλογικό ρολόι ή "
    L"ημερολόγιο με ρολόι επιλέγουν το μέγεθος του κύριου καντράν από το μικρότερο στο μεγαλύτερο.",
    L"\r\n\r\nOdabir, tipke i kopiranje datuma\r\nOtvaranje postavki preko ikone u području obavijesti ponovo bira posljednji odabrani vidžet. "
    L"Postavke pamte posljednju otvorenu karticu, a Dodaj posljednju dodanu vrstu. Ukloni ili Del uklanja sve "
    L"odabrane stavke nakon primjene promjena. Dvostruki klik na stavku prikazuje skriveni vidžet, označava "
    L"Vidljivo i nakratko ističe vidžet. Postavke u meniju vidžeta odabiru taj vidžet na popisu. Klik na dan u"
    L" kalendaru odabire datum i kopira ga u međuspremnik; svaki kalendar ima vlastiti oblik u Postavkama i "
    L"meniju. Dostupna su sva 33 oblika, nezavisno o jeziku; tekstualni nazivi koriste jezik vidžeta. "
    L"Podrazumijevani Kratki datum prati jezik vidžeta. Insert mijenja odabir trenutne stavke i pomiče "
    L"pokazivač popisa jedan red niže. Ctrl+C kopira odabrane vidžete. Ctrl+V dodaje kopije redoslijedom "
    L"popisa, s nastavkom naziva na jeziku programa. Dopuštena su najviše 32 vidžeta. Pri dupliciranju ili "
    L"lijepljenju kopije se dodaju redom do dosezanja ograničenja, a za preostale se prikazuje obavijest. "
    L"Alt+0, Alt+1, Alt+2 ili Alt+3 na analognom satu ili kalendaru sa satom odabire veličinu glavnog "
    L"brojčanika od najmanje do najveće.",
    L"\r\n\r\nOdabir, tipke i kopiranje datuma\r\nOtvaranje postavki preko ikone u području obavijesti ponovno odabire posljednji odabrani widget. "
    L"Postavke pamte posljednju otvorenu karticu, a Dodaj posljednju dodanu vrstu. Ukloni ili Del uklanja sve "
    L"odabrane stavke nakon primjene promjena. Dvostruki klik na stavku prikazuje skriveni widget, označava "
    L"Vidljivo i nakratko ističe widget. Postavke u izborniku widgeta odabiru taj widget na popisu. Klik na "
    L"dan u kalendaru odabire datum i kopira ga u međuspremnik; svaki kalendar ima vlastiti oblik u Postavkama"
    L" i izborniku. Dostupna su sva 33 oblika, neovisno o jeziku; tekstualni nazivi koriste jezik widgeta. "
    L"Zadani Kratki datum prati jezik widgeta. Insert mijenja odabir trenutačne stavke i pomiče pokazivač "
    L"popisa jedan redak niže. Ctrl+C kopira odabrane widgete. Ctrl+V dodaje kopije redoslijedom popisa, s "
    L"nastavkom naziva na jeziku programa. Dopuštena su najviše 32 widgeta. Pri dupliciranju ili lijepljenju "
    L"kopije se dodaju redom do dosezanja ograničenja, a za preostale se prikazuje obavijest. Alt+0, Alt+1, "
    L"Alt+2 ili Alt+3 na analognom satu ili kalendaru sa satom odabire veličinu glavnog brojčanika od najmanje"
    L" do najveće.",
    L"\r\n\r\nIzbiranje, tipke in kopiranje datuma\r\nOb odpiranju nastavitev prek ikone v območju za obvestila je znova izbran nazadnje izbrani gradnik. "
    L"Nastavitve pomnijo zadnji odprti zavihek, Dodaj pa zadnjo dodano vrsto. Odstrani ali Del odstrani vse "
    L"izbrane elemente ob uporabi sprememb. Dvoklik elementa pokaže skriti gradnik, označi Vidno in ga na "
    L"kratko osvetli. Nastavitve v meniju gradnika izberejo ta gradnik na seznamu. Klik dneva v koledarju "
    L"izbere datum in ga kopira v odložišče. Vsak koledar ima lastno obliko v Nastavitvah in meniju. Vseh 33 "
    L"oblik je na voljo v vseh jezikih; besedilna imena in privzeti Kratki datum sledijo jeziku gradnika. "
    L"Insert preklopi izbor trenutnega elementa in premakne kazalec seznama vrstico navzdol. Ctrl+C kopira "
    L"izbrane gradnike, Ctrl+V pa doda kopije po vrstnem redu seznama s pripono imena v jeziku programa. "
    L"Dovoljenih je do 32 gradnikov. Kopije se dodajajo po vrsti do omejitve; za preostale se prikaže "
    L"obvestilo. Alt+0, Alt+1, Alt+2 in Alt+3 na analogni uri ali koledarju z uro izberejo velikost glavne "
    L"številčnice od najmanjše do največje.",
    L"\r\n\r\nIzbor, tasteri i kopiranje datuma\r\nOtvaranje podešavanja preko ikone u oblasti za obavještenja ponovo bira posljednji izabrani vidžet. Podešavanja "
    L"pamte posljednju otvorenu karticu, a Dodaj posljednju dodatu vrstu. Ukloni ili Del uklanja sve izabrane "
    L"stavke po primjeni promjena. Dvoklik stavke prikazuje skriveni vidžet, označava Vidljivo i nakratko "
    L"osvjetljava vidžet. Podešavanja iz menija vidžeta biraju taj vidžet u spisku. Klik na dan kalendara bira"
    L" datum i kopira ga u ostavu; svaki kalendar ima sopstveni oblik u Podešavanjima i meniju. Sva 33 oblika "
    L"su dostupna u svakom jeziku; tekstualni nazivi i podrazumijevani Kratak datum prate jezik vidžeta. "
    L"Insert prebacuje izbor trenutne stavke i pomjera pokazivač spiska red niže. Ctrl+C kopira izabrane "
    L"vidžete, Ctrl+V dodaje kopije redom spiska sa nastavkom naziva na jeziku programa. Dozvoljena su najviše"
    L" 32 vidžeta. Kopije se dodaju redom do ograničenja, a za preostale se prikazuje obavještenje. Alt+0, "
    L"Alt+1, Alt+2 i Alt+3 na analognom satu ili kalendaru sa satom biraju veličinu glavnog brojčanika od "
    L"najmanje do najveće.",
    L"\r\n\r\nВыбар, клавішы і капіяванне даты\r\nПры адкрыцці налад праз значок у вобласці апавяшчэнняў зноў выбіраецца апошні выбраны віджэт. «Налады»"
    L" памятаюць апошнюю ўкладку, а «Дадаць» — апошні дададзены тып. «Выдаліць» або Del выдаляе ўсе выбраныя "
    L"элементы пасля ўжывання змен. Падвойная пстрычка элемента паказвае схаваны віджэт, усталёўвае "
    L"«Паказваць» і ненадоўга падсвечвае віджэт. «Налады» ў меню віджэта выбіраюць яго ў спісе. Пстрычка дня "
    L"выбірае дату і капіюе яе ў буфер абмену; фармат задаецца асобна для календара ў наладах ці меню. Усе 33 "
    L"фарматы даступныя на ўсіх мовах; тэкставыя назвы і прадвызначаная «Кароткая дата» адпавядаюць мове "
    L"віджэта. Insert пераключае выбар бягучага элемента і перамяшчае курсор спіса на радок уніз. Ctrl+C "
    L"капіюе выбраныя віджэты, Ctrl+V дадае копіі ў парадку спіса з суфіксам назвы на мове праграмы. Дазволена"
    L" да 32 віджэтаў. Копіі дадаюцца па парадку да мяжы, пра астатнія паказваецца апавяшчэнне. Alt+0, Alt+1, "
    L"Alt+2 і Alt+3 на аналагавым гадзінніку або календары з гадзіннікам выбіраюць памер галоўнага цыферблата "
    L"ад найменшага да найбольшага.",
    L"\r\n\r\nИзбор, клавиши и копиране на дата\r\nПри отваряне на настройките от иконата в областта за уведомяване отново се избира последният избран модул. „Настройки“ "
    L"помни последния отворен раздел, а „Добави“ — последния добавен тип. „Премахни“ или Del премахва всички "
    L"избрани елементи при прилагане на промените. Двойното щракване върху елемент показва скрития модул, "
    L"избира „Видим“ и го осветява за кратко. „Настройки“ в менюто на модул го избира в списъка. Щракването "
    L"върху ден избира датата и я копира в клипборда; всеки календар има собствен формат в настройките и "
    L"менюто. Всичките 33 формата са достъпни на всички езици; текстовите имена и „Кратка дата“ следват езика "
    L"на модула. Insert превключва избора на текущия елемент и премества курсора на списъка един ред надолу. "
    L"Ctrl+C копира избраните модули, а Ctrl+V добавя копия по реда на списъка с наставка на името на езика на"
    L" програмата. Допускат се до 32 модула. Копията се добавят по ред до ограничението; за останалите се "
    L"показва уведомление. Alt+0, Alt+1, Alt+2 и Alt+3 върху аналогов часовник или календар с часовник избират"
    L" размера на главния циферблат от най-малкия до най-големия.",
    L"\r\n\r\nИзбирање, копчиња и копирање датум\r\nПри отворање на поставките преку иконата во областа за известување повторно се избира последниот избран виџет. „Поставки“ "
    L"ја памети последната картичка, а „Додај“ последниот додаден вид. „Отстрани“ или Del ги отстранува сите "
    L"избрани ставки по применување на промените. Двоен клик на ставка го покажува скриениот виџет, избира "
    L"„Видливо“ и накратко го истакнува виџетот. „Поставки“ од менито на виџетот го избира тој виџет во "
    L"списокот. Клик на ден во календар избира датум и го копира во меморијата за копирање; секој календар има"
    L" свој облик во поставките и менито. Сите 33 облици се достапни на секој јазик; текстуалните имиња и "
    L"стандардниот „Краток датум“ го следат јазикот на виџетот. Insert го менува изборот на тековната ставка и"
    L" го поместува покажувачот на списокот ред надолу. Ctrl+C ги копира избраните виџети, а Ctrl+V додава "
    L"копии по редот на списокот со наставка на името на јазикот на програмата. Дозволени се до 32 виџети. "
    L"Копиите се додаваат по ред до границата, а за останатите се прикажува известување. Alt+0, Alt+1, Alt+2 и"
    L" Alt+3 на аналоген часовник или календар со часовник ја избираат големината на главниот бројчаник од "
    L"најмала до најголема.",
    L"\r\n\r\nИзбор, тастери и копирање датума\r\nОтварање подешавања преко иконе у области за обавештења поново бира последњи изабрани виџет. Подешавања памте "
    L"последњу отворену картицу, а Додај последњу додату врсту. Уклони или Del уклања све изабране ставке по "
    L"примени промена. Двоклик ставке приказује скривени виџет, означава Видљиво и накратко осветљава виџет. "
    L"Подешавања из менија виџета бирају тај виџет у списку. Клик на дан календара бира датум и копира га у "
    L"оставу; сваки календар има сопствени облик у Подешавањима и менију. Сва 33 облика су доступна у сваком "
    L"језику; текстуални називи и подразумевани Кратак датум прате језик виџета. Insert пребацује избор "
    L"тренутне ставке и помера показивач списка ред ниже. Ctrl+C копира изабране виџете, Ctrl+V додаје копије "
    L"редом списка са наставком назива на језику програма. Дозвољена су највише 32 виџета. Копије се додају "
    L"редом до ограничења, а за преостале се приказује обавештење. Alt+0, Alt+1, Alt+2 и Alt+3 на аналогном "
    L"сату или календару са сатом бирају величину главног бројчаника од најмање до највеће.",
    L"\r\n\r\nВИБІР, КЛАВІШІ ТА КОПІЮВАННЯ ДАТИ\r\nПід час відкриття налаштувань із піктограми в області сповіщень знову вибирається останній вибраний віджет"
    L". Вікно «Налаштування» запам’ятовує останню відкриту вкладку, а команда «Додати» — останній "
    L"доданий тип. «Видалити» або Del видаляє всі вибрані елементи після застосування змін. Подвійне клацання "
    L"елемента показує прихований віджет, установлює прапорець «Показувати» та коротко підсвічує віджет. "
    L"Команда «Налаштування» в меню віджета вибирає його у списку. Клацання дня календаря вибирає дату й "
    L"копіює її до буфера обміну; формат задається окремо для кожного календаря в налаштуваннях або меню. Усі "
    L"шаблони доступні всіма мовами, а текстові назви подаються мовою віджета. Типова «Коротка дата» "
    L"відповідає мові віджета. Insert перемикає вибір поточного елемента й переміщує курсор списку на рядок "
    L"униз. Ctrl+C копіює вибрані віджети. Ctrl+V додає копії в порядку списку із суфіксом назви мовою "
    L"програми. Дозволено до 32 віджетів. Під час дублювання або вставлення копії додаються за порядком до "
    L"досягнення межі; про решту з’являється повідомлення. Alt+0, Alt+1, Alt+2 або Alt+3 на аналоговому "
    L"годиннику чи календарі з годинником вибирає розмір головного циферблата від найменшого до найбільшого.",
    L"\r\n\r\nВЫБОР, КЛАВИШИ И КОПИРОВАНИЕ ДАТЫ\r\nПри открытии настроек через значок в области уведомлений снова выбирается последний выбранный виджет"
    L". Окно «Настройки» запоминает последнюю открытую вкладку, а команда «Добавить» — последний "
    L"добавленный тип. «Удалить» или Del удаляет все выбранные элементы после применения изменений. Двойной "
    L"щелчок элемента показывает скрытый виджет, устанавливает флажок «Показывать» и ненадолго подсвечивает "
    L"виджет. Команда «Настройки» в меню виджета выбирает его в списке. Щелчок дня календаря выбирает дату и "
    L"копирует её в буфер обмена; формат задаётся отдельно для каждого календаря в настройках или меню. Все "
    L"шаблоны доступны на всех языках, а текстовые названия выводятся на языке виджета. «Краткая дата», "
    L"выбранная по умолчанию, соответствует языку виджета. Insert переключает выбор текущего элемента и "
    L"перемещает курсор списка на строку вниз. Ctrl+C копирует выбранные виджеты. Ctrl+V добавляет копии в "
    L"порядке списка с суффиксом названия на языке программы. Допускается до 32 виджетов. При дублировании или"
    L" вставке копии добавляются по порядку до достижения предела; об остальных появляется уведомление. Alt+0,"
    L" Alt+1, Alt+2 или Alt+3 на аналоговых часах либо календаре с часами выбирает размер главного циферблата "
    L"от наименьшего до наибольшего."
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
    L"\r\n\r\nWIDGET-ANORDNUNG\r\nIm Raster anordnen behält die ungefähre manuelle Anordnung bei, richtet die "
    L"Mittelpunkte am nächsten Rasterpunkt aus und beseitigt Überlappungen. Das Widget-Menü wirkt auf seinen "
    L"Monitor, das Symbol auf alle Monitore einzeln. Wiederholen ändert die Anordnung nicht. Die Kennzeichnung"
    L" blinkt schnell hellblau, der Alarm langsamer rot. Das Abschalten von Immer im Vordergrund schickt das "
    L"Widget nach hinten. Im Kalender-Uhr-Panel ist das obere Datum ein Link zum heutigen Tag, der untere Link"
    L" öffnet die klassischen Windows-Einstellungen für Datum und Uhrzeit. Wenn das Einrasten aktiviert ist, "
    L"rastet ein Widget beim Ziehen innerhalb von fünf Pixeln am Rand der Arbeitsfläche ein. Beim Ändern der "
    L"Größe bleibt es am selben Rand oder an demselben Randpaar angeheftet.\r\n\r\nBei einem einzelnen "
    L"Kalender lässt sich die Heute-Zeile unter Darstellung oder im Widget-Menü ein- und ausblenden. Zu heute "
    L"wechseln wählt den heutigen Tag und die Monatsansicht. Beim Datumswechsel gemäß der Widget-Zeit wird "
    L"heute automatisch ausgewählt; die aktuelle Kalenderansicht bleibt erhalten.",
    L"\r\n\r\nDISPOSITION\r\nAligner sur une grille conserve leur disposition manuelle approximative, aligne "
    L"leurs centres sur la grille la plus proche et supprime les chevauchements. Le menu du widget agit sur "
    L"son écran, l’icône sur chaque écran séparément. La commande répétée reste stable. L’identification "
    L"clignote rapidement en bleu clair, l’alarme plus lentement en rouge. Désactiver Toujours visible"
    L" envoie le widget à l’arrière-plan. Dans le panneau calendrier-horloge, la date supérieure est un lien "
    L"vers aujourd’hui et le lien inférieur ouvre les paramètres classiques Date et heure de Windows. Lorsque "
    L"l’accrochage est activé, le widget déplacé s’accroche au bord de la zone de travail à moins de cinq "
    L"pixels. Lors du redimensionnement, il reste accroché au même bord ou à la même paire de "
    L"bords.\r\n\r\nPour un calendrier autonome, affichez ou masquez la ligne Aujourd’hui dans Apparence ou "
    L"dans le menu du widget. Aller à aujourd’hui sélectionne la date du jour et revient à la vue mensuelle. "
    L"Au changement de date selon l’heure du widget, le jour courant est sélectionné automatiquement sans "
    L"changer le type de vue.",
    L"\r\n\r\nDISTRIBUCIÓN\r\nAlinear en cuadrícula conserva la distribución manual aproximada, ajusta sus "
    L"centros a la cuadrícula más cercana y elimina superposiciones. El menú del widget actúa en su monitor; "
    L"el icono, en cada monitor por separado. Repetir no cambia la distribución. La identificación parpadea "
    L"rápido en azul claro y la alarma más despacio en rojo. Desactivar Siempre visible envía el "
    L"widget al fondo. En el panel de calendario y reloj, la fecha superior es un enlace a hoy y el enlace "
    L"inferior abre la configuración clásica de Fecha y hora de Windows. Con el ajuste activado, el widget se "
    L"acopla al borde del área de trabajo al arrastrarlo a menos de cinco píxeles. Al cambiar de tamaño, "
    L"permanece acoplado al mismo borde o al mismo par de bordes.\r\n\r\nEn un calendario independiente, "
    L"muestre u oculte la fila Hoy en Apariencia o en el menú del widget. Ir a hoy selecciona la fecha actual "
    L"y vuelve a la vista mensual. Al cambiar la fecha según la hora del widget, se selecciona automáticamente"
    L" el día actual sin cambiar el tipo de vista.",
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
    L"içinde yapışır ve boyut değişirken yapışık kalır. Izgarada düzenle, başvuru aracını yerinde tutarak "
    L"diğer araçları çakışmayan yakın konumlara taşır. Monitör saatleri hesaba katılmaz. Saatli takvim "
    L"panelinde üst bağlantı bugüne döner, alt bağlantı Windows'un klasik Tarih ve Saat ayarlarını açar; ikisi"
    L" de fare ve klavyeyle çalışır.\r\n\r\nBağımsız takvimde Bugün satırını Görünüm sekmesinden veya araç "
    L"menüsünden gösterip gizleyebilirsiniz. Bugüne git, bugünün tarihini seçer ve ay görünümüne döner. Aracın"
    L" saatine göre tarih değiştiğinde görünüm türü korunarak bugünün tarihi otomatik seçilir.",
    L"\r\n\r\nVidinate paigutus\r\nPaiguta ruudustikku säilitab ligikaudse käsitsi paigutuse, tõmbab "
    L"keskpunktid lähimatele ruudustikupunktidele ja kõrvaldab kattumised. Käsu käivitanud vidin jääb paigale."
    L" Vidina menüü mõjutab selle kuvarit, olekuala ikoon iga kuvarit eraldi. Kordamine säilitab stabiilse "
    L"paigutuse. Sätete topeltklõps tõstab vidina esile kiire helesinise vilkumisega; äratus vilgub "
    L"aeglasemalt punaselt. Alati pealmine väljalülitamine saadab vidina teiste akende taha. Paneeli ülemine "
    L"link toob kalendri tänasele kuupäevale ja alumine avab Windowsi klassikalised kuupäeva ja kellaaja "
    L"sätted. Servatõmme haarab lohistatava vidina tööala serva külge kuni viie piksli kauguselt. Suuruse "
    L"muutmisel säilib kinnitus sama serva või servapaari külge.\r\n\r\nEraldi kalendris kuvab või peidab "
    L"Tänase kuupäeva rida vahekaardil Ilme või menüüs alumise rea. Mine tänasele kuupäevale valib tänase "
    L"päeva ja taastab kuuvaate. Kui vidina aja järgi kuupäev muutub, valitakse tänane kuupäev automaatselt "
    L"praegust kalendrivaadet säilitades.",
    L"\r\n\r\nLeagan amach\r\nCoinníonn Eagraigh in eangach an leagan amach láimhe gar dá bhunleagan, léimeann"
    L" lárphointí chuig na pointí eangaí is gaire agus baintear forluí. Fanann an ghiuirléid óna roghchlár a "
    L"seoladh an t-ordú ina háit. Baineann roghchlár giuirléide lena monatóir; baineann an deilbhín fógraí le "
    L"gach monatóir ar leith. Coinníonn athdhéanamh an leagan amach seasmhach. Aithníonn déchliceáil sna "
    L"Socruithe giuirléid le caochadh tapa gorm éadrom; bíonn aláram dearg agus níos moille. Cuireann múchadh "
    L"Ar barr i gcónaí an ghiuirléid taobh thiar de na fuinneoga eile. Filleann nasc uachtarach an phainéil ar"
    L" an lá inniu agus osclaíonn an nasc íochtarach socruithe clasaiceacha dáta agus ama Windows. Léimeann "
    L"giuirléid atá á tarraingt chuig imeall an limistéir oibre laistigh de chúig phicteilín má tá an rogha "
    L"cumasaithe. Coinníonn athrú méide an ceangal leis an imeall céanna nó leis an bpéire imill "
    L"céanna.\r\n\r\nI bhféilire neamhspleách, taispeánann nó folaíonn Sraith an lae inniu ar an gcluaisín "
    L"Cuma nó sa roghchlár an tsraith íochtarach. Roghnaíonn Téigh go dtí an lá inniu an dáta reatha agus "
    L"filleann sé ar amharc na míosa. Nuair a athraíonn an dáta de réir am na giuirléide, roghnaítear an lá "
    L"inniu go huathoibríoch agus coinnítear an t-amharc reatha.",
    L"\r\n\r\nValdiklių išdėstymas\r\nIšdėstyti tinkleliu išlaiko apytikslį rankinį išdėstymą, prikabina "
    L"centrus prie artimiausių tinklo taškų ir pašalina persidengimą. Komandą iškvietęs valdiklis lieka "
    L"vietoje. Valdiklio meniu veikia jo monitorių; pranešimų srities piktograma – kiekvieną monitorių "
    L"atskirai. Pakartojimas išlaiko išdėstymą stabilų. Dukart spustelėjus parametruose valdiklis greitai "
    L"mirksi šviesiai mėlynai; žadintuvas mirksi lėčiau raudonai. Išjungus Visada viršuje valdiklis "
    L"nusiunčiamas už kitų langų. Viršutinis skydelio saitas grąžina kalendorių į šiandieną, apatinis atidaro "
    L"klasikinius „Windows“ datos ir laiko parametrus. Įjungtas prikabinimas pritraukia velkamą valdiklį prie "
    L"darbo srities krašto iki penkių pikselių atstumu. Keičiant dydį ryšys su tuo pačiu kraštu arba kraštų "
    L"pora išlieka.\r\n\r\nAtskiro kalendoriaus Šiandienos eilutė skirtuke Išvaizda arba meniu rodo ar slepia "
    L"apatinę eilutę. Pereiti į šiandieną pasirenka šiandienos datą ir atkuria mėnesio rodinį. Pasikeitus "
    L"datai pagal valdiklio laiką šiandiena pasirenkama automatiškai išlaikant dabartinį rodinį.",
    L"\r\n\r\nLogrīku izkārtojums\r\nSakārtot režģī saglabā aptuveno manuālo izkārtojumu, pievelk centrus "
    L"tuvākajiem režģa punktiem un novērš pārklāšanos. Logrīks, kura izvēlnē izsaukta komanda, paliek vietā. "
    L"Logrīka izvēlne ietekmē tā monitoru, paziņojumu ikona katru monitoru atsevišķi. Atkārtojot izkārtojums "
    L"paliek stabils. Dubultklikšķis iestatījumos izceļ logrīku ar ātru gaišzilu mirgošanu; modinātājs mirgo "
    L"lēnāk sarkani. Izslēdzot Vienmēr virspusē, logrīks tiek novietots aiz pārējiem logiem. Paneļa augšējā "
    L"saite atgriež kalendāru šodienā, apakšējā atver Windows klasiskos datuma un laika iestatījumus. Ieslēgta"
    L" pievilkšana pievelk vilktu logrīku darba apgabala malai līdz piecu pikseļu attālumā. Lieluma maiņa "
    L"saglabā piesaisti tai pašai malai vai malu pārim.\r\n\r\nAtsevišķā kalendārā Šodienas rinda cilnē "
    L"Izskats vai izvēlnē rāda vai slēpj apakšējo rindu. Pāriet uz šodienu atlasa šodienas datumu un atjauno "
    L"mēneša skatu. Mainoties datumam pēc logrīka laika, šodiena tiek atlasīta automātiski, saglabājot "
    L"pašreizējo skatu.",
    L"\r\n\r\nElrendezés\r\nA Rácsba rendezés megőrzi a hozzávetőleges kézi elrendezést, a középpontokat a "
    L"legközelebbi rácspontokhoz illeszti és megszünteti az átfedéseket. A parancsot indító minialkalmazás "
    L"helyben marad. A saját menü a saját monitorra, az értesítési ikon minden monitorra külön hat. Ismételve "
    L"az elrendezés stabil marad. A beállításokbeli dupla kattintás gyors világoskék villogással jelöl; az "
    L"ébresztés lassabban, pirosan villog. A Mindig felül kikapcsolása a többi ablak mögé küldi a "
    L"minialkalmazást. A panel felső hivatkozása a mai napra tér vissza, az alsó a Windows klasszikus dátum- "
    L"és időbeállításait nyitja meg. Az engedélyezett szélhez illesztés öt képponton belül a munkaterület "
    L"széléhez húzza a mozgatott minialkalmazást. Átméretezéskor ugyanahhoz a szélhez vagy sarokhoz "
    L"csatlakozik.\r\n\r\nÖnálló naptárban a Mai dátum sora a Megjelenés fülön vagy menüben az alsó sort "
    L"kapcsolja. Az Ugrás a mai napra kiválasztja a mai dátumot és visszaállítja a havi nézetet. A "
    L"minialkalmazás szerinti dátumváltáskor a mai nap automatikusan kijelölődik az aktuális nézet "
    L"megtartásával.",
    L"\r\n\r\nTqassim tal-widgets\r\nIrranġa fi gradilja iżomm bejn wieħed u ieħor it-tqassim manwali, iwaħħal"
    L" iċ-ċentri mal-eqreb punti tal-gradilja u jneħħi s-sovrapożizzjonijiet. Il-widget li minnu ġie msejjaħ "
    L"il-kmand jibqa’ f’postu. Il-menu tal-widget jaġixxi fuq il-moniter tiegħu; l-ikona tan-notifiki fuq kull"
    L" moniter separatament. Ir-ripetizzjoni żżomm tqassim stabbli. Klikk doppju fis-settings jidentifika "
    L"widget b’teptip blu ċar mgħaġġel; allarm iteptep aħmar aktar bil-mod. It-tifi ta’ Dejjem fuq nett "
    L"jibgħat il-widget wara t-twieqi l-oħra. Il-link ta’ fuq fil-panew jirritorna għal-lum; t’isfel jiftaħ "
    L"is-settings klassiċi tad-data u l-ħin tal-Windows. Meta t-twaħħil ikun attivat, widget mkaxkar sa ħames "
    L"pixels mit-tarf jeħel mat-tarf taż-żona tax-xogħol. Il-bidla fid-daqs iżżomm ir-rabta mal-istess tarf "
    L"jew par truf.\r\n\r\nF’kalendarju separat, Ringiela tal-lum fit-tab Dehra jew fil-menu turi jew taħbi "
    L"r-ringiela t’isfel. Mur għad-data tal-lum jagħżel illum u jirritorna għall-vista tax-xahar. Meta d-data "
    L"tinbidel skont il-ħin tal-widget, illum jintgħażel awtomatikament waqt li tinżamm il-vista kurrenti.",
    L"\r\n\r\nWidgets schikken\r\nSchikken in raster behoudt de globale handmatige indeling, lijnt "
    L"middelpunten uit op de dichtstbijzijnde rasterpunten en verwijdert overlap. De widget waarvan het menu "
    L"is gebruikt blijft staan. Een widgetmenu beïnvloedt zijn beeldscherm; het systeemvakpictogram behandelt "
    L"elk scherm afzonderlijk. Herhalen houdt de indeling stabiel. Dubbelklikken in Instellingen markeert een "
    L"widget met snel lichtblauw knipperen; een alarm knippert langzamer rood. Altijd op voorgrond "
    L"uitschakelen plaatst de widget achter andere vensters. De bovenste paneelkoppeling gaat naar vandaag, de"
    L" onderste opent de klassieke Windows-instellingen voor datum en tijd. Als uitlijnen op randen is "
    L"ingeschakeld, klikt een versleepte widget binnen vijf pixels vast aan de rand van het werkgebied. Bij "
    L"vergroten of verkleinen blijft dezelfde rand of hetzelfde paar randen behouden.\r\n\r\nBij een losse "
    L"kalender toont of verbergt Rij Vandaag op Vormgeving of in het menu de onderste rij. Naar vandaag kiest "
    L"vandaag en herstelt de maandweergave. Bij een datumwisseling volgens de widgettijd wordt vandaag "
    L"automatisch gekozen zonder de huidige kalenderweergave te veranderen.",
    L"\r\n\r\nAranjarea widgeturilor\r\nAranjare în grilă păstrează aproximativ pozițiile manuale, aliniază "
    L"centrele la cele mai apropiate puncte ale grilei și elimină suprapunerile. Widgetul din al cărui meniu "
    L"s-a lansat comanda rămâne pe loc. Meniul widgetului afectează monitorul său; pictograma de notificare "
    L"tratează fiecare monitor separat. Repetarea păstrează aranjarea stabilă. Dublul clic din Setări "
    L"identifică widgetul prin clipire rapidă albastru-deschis; alarma clipește mai lent în roșu. Dezactivarea"
    L" Întotdeauna deasupra trimite widgetul în spatele ferestrelor. Legătura superioară a panoului revine la "
    L"azi, cea inferioară deschide setările clasice Windows pentru dată și oră. Alinierea la margini atrage "
    L"widgetul glisat la marginea zonei de lucru de la cel mult cinci pixeli. Redimensionarea păstrează "
    L"atașarea la aceeași margine sau pereche de margini.\r\n\r\nPentru un calendar separat, Rândul Azi din "
    L"Aspect sau meniu afișează ori ascunde rândul inferior. Salt la ziua de azi selectează azi și "
    L"restabilește vizualizarea lunară. Când data se schimbă după ora widgetului, ziua de azi se selectează "
    L"automat, păstrând vizualizarea curentă.",
    L"\r\n\r\nΔιάταξη στοιχείων\r\nΗ Τακτοποίηση σε πλέγμα διατηρεί την κατά προσέγγιση χειροκίνητη διάταξη, "
    L"ευθυγραμμίζει κέντρα στα πλησιέστερα σημεία του πλέγματος και αφαιρεί επικαλύψεις. Το στοιχείο από το "
    L"μενού του οποίου κλήθηκε η εντολή παραμένει στη θέση του. Το μενού στοιχείου επηρεάζει την οθόνη του· το"
    L" εικονίδιο ειδοποιήσεων κάθε οθόνη χωριστά. Η επανάληψη κρατά τη διάταξη σταθερή. Το διπλό κλικ στις "
    L"Ρυθμίσεις επισημαίνει στοιχείο με γρήγορο γαλάζιο αναβόσβημα· το ξυπνητήρι αναβοσβήνει πιο αργά κόκκινο."
    L" Η απενεργοποίηση του Πάντα σε πρώτο πλάνο στέλνει το στοιχείο πίσω από άλλα παράθυρα. Ο επάνω σύνδεσμος"
    L" του πλαισίου επιστρέφει στο σήμερα, ο κάτω ανοίγει τις κλασικές ρυθμίσεις ημερομηνίας και ώρας των "
    L"Windows. Η ενεργή προσκόλληση τραβά συρόμενο στοιχείο στο άκρο της περιοχής εργασίας από απόσταση έως "
    L"πέντε pixel. Η αλλαγή μεγέθους διατηρεί την προσκόλληση στο ίδιο άκρο ή ζεύγος άκρων.\r\n\r\nΣε "
    L"ανεξάρτητο ημερολόγιο, η Γραμμή Σήμερα στην Εμφάνιση ή στο μενού δείχνει ή κρύβει την κάτω γραμμή. Η "
    L"Μετάβαση στο σήμερα επιλέγει σήμερα και επαναφέρει τη μηνιαία προβολή. Όταν αλλάξει η ημερομηνία κατά "
    L"την ώρα του στοιχείου, το σήμερα επιλέγεται αυτόματα χωρίς αλλαγή της τρέχουσας προβολής.",
    L"\r\n\r\nRaspored vidžeta\r\nRasporedi u mrežu čuva približan ručni raspored, priljubljuje središta "
    L"vidžeta uz najbliže tačke mreže i uklanja preklapanja. Meni vidžeta djeluje na njegov ekran, a ikona u "
    L"području obavijesti na svaki ekran zasebno. Ponavljanje naredbe čuva raspored. Dvostruki klik u "
    L"Postavkama označava vidžet brzim svijetloplavim treperenjem; alarm treperi sporije i crveno. "
    L"Isključivanje opcije Uvijek na vrhu šalje vidžet iza ostalih prozora. Na ploči kalendara sa satom gornja"
    L" poveznica vraća kalendar na današnji datum, a donja otvara klasične postavke datuma i vremena Windowsa."
    L" Ako je priljubljivanje uključeno, vidžet se tokom povlačenja priljubljuje uz ivicu radnog područja na "
    L"udaljenosti do pet piksela. Promjena veličine čuva vezu s istom ivicom ili parom ivica.\r\n\r\nZa "
    L"samostalni kalendar prikažite ili sakrijte Red Danas na kartici Izgled ili u meniju vidžeta. Idi na "
    L"današnji datum odabire danas i vraća mjesečni prikaz. Kada se datum promijeni prema vremenu vidžeta, "
    L"današnji se datum odabire automatski uz očuvanje trenutnog prikaza kalendara.",
    L"\r\n\r\nRaspored widgeta\r\nRasporedi u mrežu čuva približan ručni raspored, priljubljuje središta "
    L"widgeta uz najbliže točke mreže i uklanja preklapanja. Izbornik widgeta djeluje na njegov zaslon, a "
    L"ikona u području obavijesti na svaki zaslon zasebno. Ponavljanje naredbe čuva raspored. Dvostruki klik u"
    L" Postavkama označava widget brzim svijetloplavim treperenjem; alarm treperi sporije i crveno. "
    L"Isključivanje opcije Uvijek na vrhu šalje widget iza ostalih prozora. Na ploči kalendara sa satom gornja"
    L" poveznica vraća kalendar na današnji datum, a donja otvara klasične postavke datuma i vremena Windowsa."
    L" Ako je priljubljivanje uključeno, widget se tijekom povlačenja priljubljuje uz rub radnog područja na "
    L"udaljenosti do pet piksela. Promjena veličine čuva vezu s istim rubom ili parom rubova.\r\n\r\nZa "
    L"samostalni kalendar prikažite ili sakrijte Redak Danas na kartici Izgled ili u izborniku widgeta. Idi na"
    L" današnji datum odabire danas i vraća mjesečni prikaz. Kada se datum promijeni prema vremenu widgeta, "
    L"današnji se datum odabire automatski uz očuvanje trenutačnog prikaza kalendara.",
    L"\r\n\r\nRazporeditev gradnikov\r\nRazporedi v mrežo ohrani približno ročno razporeditev, pripne središča"
    L" na najbližje mrežne točke in odpravi prekrivanje. Meni gradnika deluje na njegovem zaslonu, ikona za "
    L"obvestila pa na vsakem zaslonu posebej. Ponovitev ohrani razporeditev. Dvoklik v Nastavitvah označi "
    L"gradnik s hitrim svetlomodrim utripanjem; budilka utripa počasneje in rdeče. Izklop Vedno na vrhu pošlje"
    L" gradnik v ozadje. Na plošči koledarja z uro zgornja povezava vrne koledar na danes, spodnja pa odpre "
    L"klasične nastavitve datuma in časa Windows. Vključeno pripenjanje pritegne vlečeni gradnik do roba "
    L"delovnega območja na razdalji petih slikovnih pik. Spreminjanje velikosti ohrani pripetost na isti rob "
    L"ali par robov.\r\n\r\nV samostojnem koledarju možnost Vrstica Danes na zavihku Videz ali v meniju pokaže"
    L" ali skrije spodnjo vrstico. Pojdi na današnji datum izbere danes in vrne mesečni pogled. Ob spremembi "
    L"datuma po času gradnika se današnji datum izbere samodejno, trenutni pogled koledarja pa se ohrani.",
    L"\r\n\r\nRaspored vidžeta\r\nRasporedi u mrežu čuva približan ručni raspored, priljepljuje središta uz "
    L"najbliže tačke mreže i uklanja preklapanja. Meni vidžeta djeluje na njegov monitor, ikona za "
    L"obavještenja na svaki monitor posebno. Ponavljanje čuva raspored. Dvoklik u Podešavanjima označava "
    L"vidžet brzim svijetloplavim treperenjem; alarm treperi sporije i crveno. Isključivanje Uvijek na vrhu "
    L"šalje vidžet iza ostalih prozora. Gornja veza na panelu vraća kalendar na danas, donja otvara klasična "
    L"podešavanja datuma i vremena Windows-a. Uključeno priljepljivanje privlači pomjerani vidžet uz ivicu "
    L"radne površine sa razdaljine do pet piksela. Promjena veličine čuva vezu sa istom ivicom ili parom "
    L"ivica.\r\n\r\nU samostalnom kalendaru Red Danas na kartici Izgled ili u meniju prikazuje ili skriva "
    L"donji red. Idi na današnji datum bira danas i vraća mjesečni prikaz. Pri promjeni datuma po vremenu "
    L"vidžeta današnji datum se bira automatski uz očuvanje trenutnog prikaza kalendara.",
    L"\r\n\r\nРазмяшчэнне віджэтаў\r\n«Упарадкаваць па сетцы» захоўвае прыблізнае ручное размяшчэнне, "
    L"прывязвае цэнтры да найбліжэйшых вузлоў сеткі і прыбірае перакрыцці. Меню віджэта дзейнічае на яго "
    L"маніторы, а значок у вобласці апавяшчэнняў — на кожным маніторы асобна. Паўтор каманды захоўвае "
    L"размяшчэнне. Падвойная пстрычка ў наладах пазначае віджэт хуткім светла-блакітным мігценнем; будзільнік "
    L"мігціць павольней і чырвоным. Выключэнне «Заўсёды зверху» перамяшчае віджэт назад. На панэлі календара з"
    L" гадзіннікам верхняя спасылка вяртае каляндар да сёння, а ніжняя адкрывае класічныя налады даты і часу "
    L"Windows. Пры ўключанай прывязцы перацягнуты віджэт прывязваецца да краю рабочай вобласці на адлегласці "
    L"да пяці пікселяў. Змена памеру захоўвае прывязку да таго ж краю або пары краёў.\r\n\r\nУ асобным "
    L"календары Радок «Сёння» на ўкладцы «Выгляд» ці ў меню паказвае або хавае ніжні радок. «Перайсці да "
    L"сённяшняй даты» выбірае сёння і вяртае месячны выгляд. Калі дата паводле часу віджэта змяняецца, "
    L"сённяшняя дата выбіраецца аўтаматычна з захаваннем бягучага выгляду календара.",
    L"\r\n\r\nРазполагане на модулите\r\n„Подреди в мрежа“ запазва приблизителното ръчно разположение, "
    L"прилепва центровете към най-близките възли и премахва застъпванията. Менюто на модул действа върху "
    L"неговия монитор, а иконата за уведомяване — върху всеки монитор поотделно. Повторението запазва "
    L"разположението. Двойното щракване в настройките обозначава модул с бързо светлосиньо мигане; алармата "
    L"мига по-бавно в червено. Изключването на „Винаги отгоре“ изпраща модула отзад. Горната връзка в панела "
    L"връща календара към днес, а долната отваря класическите настройки за дата и час на Windows. При включено"
    L" прилепване влаченият модул се прилепва към край на работната област от разстояние до пет пиксела. "
    L"Промяната на размера запазва прилепването към същия край или двойка краища.\r\n\r\nЗа самостоятелен "
    L"календар Ред „Днес“ в раздела „Изглед“ или менюто показва или скрива долния ред. „Отиди на днешната "
    L"дата“ избира днес и връща месечния изглед. При смяна на датата по времето на модула днешната дата се "
    L"избира автоматично, като текущият изглед се запазва.",
    L"\r\n\r\nРаспоред на виџетите\r\n„Распореди во мрежа“ го зачувува приближниот рачен распоред, ги "
    L"прилепува средиштата до најблиските точки на мрежата и ги отстранува преклопувањата. Менито на виџетот "
    L"дејствува на неговиот монитор, а иконата за известување на секој монитор одделно. Повторувањето го "
    L"зачувува распоредот. Двоен клик во поставките го означува виџетот со брзо светлосино трепкање; алармот "
    L"трепка побавно и црвено. Исклучувањето на „Секогаш најгоре“ го испраќа виџетот назад. Горната врска во "
    L"панелот го враќа календарот на денес, а долната ги отвора класичните поставки за датум и време на "
    L"Windows. При вклучено прилепување, повлечениот виџет се прилепува кон раб на работната површина од "
    L"растојание до пет пиксели. Промената на големината ја зачувува врската со истиот раб или пар "
    L"рабови.\r\n\r\nЗа самостоен календар редот „Денес“ се покажува или крие на картичката „Изглед“ или во "
    L"менито. „Оди на денешниот датум“ избира денес и го враќа месечниот приказ. При промена на датумот според"
    L" времето на виџетот, денешниот датум се избира автоматски, а тековниот приказ останува зачуван.",
    L"\r\n\r\nРаспоред виџета\r\nРаспореди у мрежу чува приближан ручни распоред, прилепљује средишта уз "
    L"најближе тачке мреже и уклања преклапања. Мени виџета делује на његов монитор, икона за обавештења на "
    L"сваки монитор посебно. Понављање чува распоред. Двоклик у Подешавањима означава виџет брзим светлоплавим"
    L" треперењем; аларм трепери спорије и црвено. Искључивање Увек на врху шаље виџет иза осталих прозора. "
    L"Горња веза на панелу враћа календар на данас, доња отвара класична подешавања датума и времена "
    L"Windows-а. Укључено прилепљивање привлачи померани виџет уз ивицу радне површине са раздаљине до пет "
    L"пиксела. Промена величине чува везу са истом ивицом или паром ивица.\r\n\r\nУ самосталном календару Ред "
    L"Данас на картици Изглед или у менију приказује или скрива доњи ред. Иди на данашњи датум бира данас и "
    L"враћа месечни приказ. При промени датума по времену виџета данашњи датум се бира аутоматски уз очување "
    L"тренутног приказа календара.",
    L"\r\n\r\nРОЗТАШУВАННЯ ВІДЖЕТІВ\r\nКоманда «Упорядкувати за сіткою» зберігає приблизне ручне розташування, "
    L"прив’язує центри віджетів до найближчих вузлів сітки та усуває перекриття. Команда з меню віджета діє на "
    L"його моніторі, а з меню піктограми в області сповіщень — окремо на кожному моніторі. Повторне виконання "
    L"зберігає розташування. Подвійне клацання у списку налаштувань позначає віджет швидким світло-блакитним "
    L"блиманням; будильник блимає повільніше й червоним. Вимкнення «Завжди зверху» переміщує віджет на задній "
    L"план. У панелі календаря з годинником верхнє посилання повертає календар до сьогоднішньої дати, а нижнє "
    L"відкриває класичні параметри дати й часу Windows. Якщо прив’язку до країв увімкнено, віджет під час "
    L"перетягування прив’язується до краю робочої області на відстані до п’яти пікселів. Після зміни розміру "
    L"він залишається прив’язаним до того самого краю або пари країв.\r\n\r\nДля окремого календаря рядок "
    L"«Сьогодні» можна показати або приховати на вкладці «Вигляд» чи в меню віджета. «Перейти до сьогоднішньої "
    L"дати» вибирає сьогоднішню дату й повертає перегляд місяця. Коли дата за часом віджета змінюється, "
    L"сьогоднішня дата вибирається автоматично зі збереженням поточного режиму перегляду календаря.",
    L"\r\n\r\nРАСПОЛОЖЕНИЕ ВИДЖЕТОВ\r\nКоманда «Упорядочить по сетке» сохраняет приблизительное ручное "
    L"расположение, привязывает центры виджетов к ближайшим узлам сетки и устраняет перекрытия. Команда из меню"
    L" виджета действует на его мониторе, а из меню значка в области уведомлений — отдельно на каждом мониторе."
    L" Повторное выполнение сохраняет расположение. Двойной щелчок в списке настроек обозначает виджет быстрым "
    L"светло-голубым миганием; будильник мигает медленнее и красным. Отключение «Поверх всех окон» перемещает "
    L"виджет на задний план. В панели календаря с часами верхняя ссылка возвращает календарь к сегодняшней "
    L"дате, а нижняя открывает классические параметры даты и времени Windows. Если привязка к краям включена, "
    L"перетаскиваемый виджет привязывается к краю рабочей области на расстоянии до пяти пикселей. После "
    L"изменения размера он остаётся привязанным к тому же краю или паре краёв.\r\n\r\nДля отдельного календаря "
    L"строку «Сегодня» можно показать или скрыть на вкладке «Внешний вид» либо в меню виджета. «Перейти к "
    L"сегодняшней дате» выбирает сегодняшнюю дату и возвращает просмотр месяца. Когда дата по времени виджета "
    L"меняется, сегодняшняя дата выбирается автоматически с сохранением текущего режима просмотра календаря."
};

const wchar_t* HELP_STORAGE_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nVZHLED A ÚLOŽIŠTĚ\r\nZměny vzhledu se ukazují ihned v živém náhledu; Zrušit zruší nepoužité "
    L"změny vzhledu a Výchozí vzhled obnoví výchozí hodnoty daného typu. Digitální hodiny nabízejí písmo, "
    L"vyhlazování, barvy, neprůhlednost, odsazení, šířku rámečku a průhledné pozadí. Digitální hodiny, "
    L"kalendář a panel mají stejné čtyři styly rámečku; u jednoduchého rámečku lze zvolit jeho barvu. Panel má"
    L" samostatná písma horního řádku, času a spodního řádku, úvodní nulu a volitelnou velikost ciferníku. "
    L"Vlastní písmo kalendáře se používá při "
    L"klasickém vzhledu Windows nebo při vypnutých motivech aplikace či widgetu. Nastavení lze exportovat do XML. Import XML okamžitě načte a uloží nastavení do "
    L"právě zvoleného úložiště; typ úložiště nezmění. Automatické XML je v "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Po úspěšném zápisu XML se odstraní větev "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; při ukládání do registru se automatické XML "
    L"odstraní.\r\n\r\nVyhlazování písma nabízí ClearType, GDI a Žádné.\r\n\r\nÚvodní nula nabízí Zobrazit "
    L"(výchozí), S místem a Bez místa. Volba S místem skryje nulu a rezervuje její šířku ve zvoleném písmu; "
    L"ostatní číslice zůstanou na stejných místech i u proporcionálního písma. Hodiny na monitoru zůstávají "
    L"zarovnané na střed včetně rezervovaného místa. Řádek UTC si zachovává vlastní zarovnání na střed.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live preview; Cancel "
    L"discards unapplied appearance changes and Default appearance restores the defaults for that widget type."
    L" Digital clocks provide font, smoothing, colors, opacity, padding, border width and a transparent "
    L"background. Digital clocks, calendars and panels share four border styles; the single-line border has a "
    L"selectable color. The panel has separate fonts for its top row, time and bottom row, a leading zero and "
    L"selectable clock-face sizes. Custom calendar fonts are supported with the Windows classic appearance or with visual styles turned off for the application or widget"
    L". Settings can be exported to XML. "
    L"Importing XML immediately loads and saves the settings to the currently selected storage without "
    L"changing the storage type. Automatic XML is %AppData%\\FortSoft\\CalClock\\settings.xml. After writing "
    L"XML, HKCU\\SOFTWARE\\FortSoft\\CalClock is removed; registry storage removes the automatic "
    L"XML.\r\n\r\nFont antialiasing offers ClearType, GDI, and None.\r\n\r\nLeading zero offers Show "
    L"(default), Keep space, and No space. Keep space hides the zero while reserving its width in the selected"
    L" font; the other digits keep their positions even with proportional fonts. Monitor clocks remain "
    L"centered, including the reserved space. The UTC row keeps its own center alignment.",
    L"\r\n\r\nDARSTELLUNG UND SPEICHERUNG\r\nDarstellungsänderungen erscheinen sofort in der Vorschau; "
    L"Abbrechen verwirft noch nicht übernommene Änderungen, Standarddarstellung die Vorgaben des Widget-Typs. "
    L"Digitaluhren bieten Schrift, Glättung, Farben, Deckkraft, Innenabstand, Rahmenbreite und transparenten "
    L"Hintergrund. Digitaluhren, Kalender und Panel verwenden dieselben vier Rahmenarten; für den einfachen "
    L"Rahmen ist die Farbe wählbar. Das Panel besitzt getrennte Schriften für obere Zeile, Zeit und untere "
    L"Zeile, eine führende Null und wählbare Zifferblattgrößen. Eigen"
    L"e Kalenderschriftarten werden beim klassischen Windows-Erscheinungsbild oder bei deaktivierten Designs für die Anwendung oder das Widget unterstützt. "
    L"Einstellungen können als XML exportiert werden. Ein XML-Import lädt und speichert die Einstellungen "
    L"sofort im aktuell gewählten Speicher, ohne die Speicherart zu ändern. Automatisches XML liegt in "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml; XML-Speicherung entfernt "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock, Registrierungsspeicherung entfernt das automatische XML.\r\n\r\nFür "
    L"die Schriftglättung stehen ClearType, GDI und Keine zur Auswahl.\r\n\r\nFührende Null bietet Anzeigen "
    L"(Standard), Platz freihalten und Ohne Platz. Platz freihalten blendet die Null aus und reserviert ihre "
    L"Breite in der gewählten Schrift; andere Ziffern bleiben auch bei proportionalen Schriften an derselben "
    L"Position. Monitoruhren bleiben mit dem reservierten Platz zentriert, die UTC-Zeile bleibt separat "
    L"zentriert.",
    L"\r\n\r\nAPPARENCE ET STOCKAGE\r\nLes changements d’apparence sont prévisualisés immédiatement ; Annuler "
    L"abandonne les modifications non appliquées et Apparence par défaut celles du type de widget. Les "
    L"horloges numériques proposent police, lissage, couleurs, opacité, marge, largeur de bordure et fond "
    L"transparent. Horloges numériques, calendriers et panneaux partagent quatre styles de bordure ; la "
    L"couleur de la bordure simple est sélectionnable. Le panneau possède des polices distinctes pour les "
    L"lignes supérieure, horaire et inférieure, un zéro initial et des tailles de cadran au choix. Les"
    L" polices de calendrier personnalisées sont prises en charge "
    L"avec l’apparence classique de Windows ou lorsque les thèmes sont désactivés pour l’application ou le widget. Les paramètres peuvent être exportés en XML. L’import XML charge et "
    L"enregistre immédiatement les paramètres dans le stockage sélectionné, sans changer son type. Le XML "
    L"automatique est %AppData%\\FortSoft\\CalClock\\settings.xml ; son écriture retire "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock, tandis que le registre retire ce XML.\r\n\r\nLe lissage des polices "
    L"propose ClearType, GDI et Aucun.\r\n\r\nLe zéro initial propose Afficher (par défaut), Garder la place "
    L"et Sans espace. Garder la place masque le zéro en réservant sa largeur dans la police choisie ; les "
    L"autres chiffres gardent leur position, même avec une police proportionnelle. Les horloges de moniteur "
    L"restent centrées, espace réservé compris. La ligne UTC reste centrée séparément.",
    L"\r\n\r\nAPARIENCIA Y ALMACENAMIENTO\r\nLos cambios de apariencia se previsualizan al instante; Cancelar "
    L"descarta los cambios de apariencia no aplicados y Aspecto predeterminado restaura los valores "
    L"predeterminados de ese tipo de widget. Los relojes digitales ofrecen fuente, suavizado, colores, "
    L"opacidad, relleno, ancho de borde y fondo transparente. Los relojes digitales, calendarios y paneles "
    L"comparten cuatro estilos de borde; el color del borde simple es seleccionable. El panel tiene fuentes "
    L"separadas para la línea superior, la hora y la inferior, cero inicial y tamaños de esfera "
    L"seleccionables. Las fuentes personalizadas del calendario se admiten con la apariencia clásica de Windows o con los temas desactivados para la aplicación o el widget"
    L". Los ajustes se pueden exportar a XML. La "
    L"importación XML carga y guarda inmediatamente los ajustes en el almacenamiento seleccionado sin cambiar "
    L"su tipo. El XML automático es %AppData%\\FortSoft\\CalClock\\settings.xml; al escribirlo se elimina "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock y al usar el registro se elimina el XML automático.\r\n\r\nEl "
    L"suavizado de fuente ofrece ClearType, GDI y Ninguno.\r\n\r\nEl cero inicial ofrece Mostrar "
    L"(predeterminado), Reservar espacio y Sin espacio. Reservar espacio oculta el cero y conserva su anchura "
    L"en la fuente elegida; los demás dígitos mantienen su posición incluso con fuentes proporcionales. Los "
    L"relojes de monitor permanecen centrados, incluido el espacio reservado. La línea UTC mantiene su propio "
    L"centrado.",
    L"\r\n\r\nASPETTO E ARCHIVIAZIONE\r\nLe modifiche all’aspetto sono mostrate subito nell’anteprima; Annulla"
    L" elimina le modifiche non applicate e Aspetto predefinito i valori del tipo di widget. Gli orologi "
    L"digitali offrono carattere, antialiasing, colori, opacità, margine, larghezza del bordo e sfondo "
    L"trasparente. Orologi digitali, calendari e pannelli condividono quattro stili di bordo; il colore del "
    L"bordo semplice è selezionabile. Il pannello ha caratteri separati per riga superiore, ora e riga "
    L"inferiore, zero iniziale e dimensioni selezionabili del quadrante. I"
    L" caratteri personalizzati del calendario sono supportati con l’aspetto classico di Windows o con i temi disattivati per l’applicazione o il widget. Le "
    L"impostazioni possono essere esportate in XML. L’importazione XML carica e salva subito le impostazioni "
    L"nell’archivio selezionato, senza cambiarne il tipo. L’XML automatico è "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml; scriverlo rimuove HKCU\\SOFTWARE\\FortSoft\\CalClock, "
    L"mentre il registro rimuove l’XML automatico.\r\n\r\nL’antialiasing del carattere offre ClearType, GDI e "
    L"Nessuno.\r\n\r\nLo zero iniziale offre Mostra (predefinito), Riserva spazio e Senza spazio. Riserva "
    L"spazio nasconde lo zero riservandone la larghezza nel carattere scelto; le altre cifre mantengono la "
    L"posizione anche con caratteri proporzionali. Gli orologi sul monitor restano centrati, incluso lo spazio"
    L" riservato. La riga UTC mantiene il proprio allineamento centrale.",
    L"\r\n\r\nWYGLĄD I ZAPIS\r\nZmiany wyglądu są od razu widoczne w podglądzie; Anuluj odrzuca niezastosowane"
    L" zmiany, a Wygląd domyślny wartości danego typu widżetu. Zegary cyfrowe oferują czcionkę, wygładzanie, "
    L"kolory, krycie, odstęp, szerokość ramki i przezroczyste tło. Zegary cyfrowe, kalendarze i panele mają te"
    L" same cztery style ramki; kolor prostej ramki można wybrać. Panel ma osobne czcionki górnego wiersza, "
    L"czasu i dolnego wiersza, zero wiodące oraz różne rozmiary tarczy. Własne czcionki kalendarza są obsługiwane przy klasycznym wyglądzie systemu Windows lub po wyłączeniu motywów dla "
    L"aplikacji bądź widżetu. "
    L"Ustawienia można eksportować do XML. Import XML natychmiast wczytuje i zapisuje ustawienia w wybranym "
    L"magazynie, nie zmieniając jego rodzaju. Automatyczny XML to %AppData%\\FortSoft\\CalClock\\settings.xml;"
    L" zapis XML usuwa HKCU\\SOFTWARE\\FortSoft\\CalClock, a zapis w rejestrze usuwa automatyczny "
    L"XML.\r\n\r\nWygładzanie czcionki oferuje ClearType, GDI i Brak.\r\n\r\nZero wiodące oferuje Pokaż "
    L"(domyślnie), Zachowaj miejsce i Bez miejsca. Zachowaj miejsce ukrywa zero, rezerwując jego szerokość w "
    L"wybranej czcionce; pozostałe cyfry zachowują położenie także w czcionkach proporcjonalnych. Zegary na "
    L"monitorze pozostają wyśrodkowane wraz z zarezerwowanym miejscem. Wiersz UTC pozostaje osobno "
    L"wyśrodkowany.",
    L"\r\n\r\nVZHĽAD A UKLADANIE\r\nZmeny vzhľadu sa ihneď ukazujú v náhľade; Zrušiť zruší nepoužité zmeny "
    L"vzhľadu a Predvolený vzhľad hodnoty daného typu widgetu. Digitálne hodiny ponúkajú písmo, vyhladzovanie,"
    L" farby, nepriehľadnosť, odsadenie, šírku rámčeka aj priehľadné pozadie. Digitálne hodiny, kalendár a "
    L"panel majú rovnaké štyri štýly rámčeka; pri jednoduchom rámčeku možno zvoliť farbu. Panel má samostatné "
    L"písma horného riadka, času a spodného riadka, úvodnú nulu a voliteľnú veľkosť ciferníka. V"
    L"lastné písmo kalendára sa používa pri "
    L"klasickom vzhľade Windows alebo pri vypnutých motívoch aplikácie či widgetu. Nastavenia možno exportovať do XML. Import XML okamžite načíta a uloží nastavenia "
    L"do práve zvoleného úložiska; typ úložiska nezmení. Automatické XML je "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml; zápis XML odstráni HKCU\\SOFTWARE\\FortSoft\\CalClock a "
    L"ukladanie do registra odstráni automatické XML.\r\n\r\nVyhladzovanie písma ponúka ClearType, GDI a "
    L"Žiadne.\r\n\r\nÚvodná nula ponúka Zobraziť (predvolené), S miestom a Bez miesta. Voľba S miestom skryje "
    L"nulu a rezervuje jej šírku vo zvolenom písme; ostatné číslice zostanú na rovnakých miestach aj pri "
    L"proporcionálnom písme. Hodiny na monitore zostávajú zarovnané na stred vrátane rezervovaného miesta. "
    L"Riadok UTC si zachováva vlastné zarovnanie na stred.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live preview; Cancel "
    L"discards unapplied appearance changes and Default appearance restores the defaults for that widget type."
    L" Digital clocks provide font, smoothing, colours, opacity, padding, border width and a transparent "
    L"background. Digital clocks, calendars and panels share four border styles; the single-line border has a "
    L"selectable colour. The panel has separate fonts for its top row, time and bottom row, a leading zero and"
    L" selectable clock-face sizes. Custom calendar fonts are supported with the Windows classic appearance or with visual styles turned off for the application or widget"
    L". Settings can be exported to XML. "
    L"Importing XML immediately loads and saves the settings to the currently selected storage without "
    L"changing the storage type. Automatic XML is %AppData%\\FortSoft\\CalClock\\settings.xml. After writing "
    L"XML, HKCU\\SOFTWARE\\FortSoft\\CalClock is removed; registry storage removes the automatic "
    L"XML.\r\n\r\nFont antialiasing offers ClearType, GDI, and None.\r\n\r\nLeading zero offers Show "
    L"(default), Keep space, and No space. Keep space hides the zero while reserving its width in the selected"
    L" font; the other digits keep their positions even with proportional fonts. Monitor clocks remain "
    L"centred, including the reserved space. The UTC row keeps its own centre alignment.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live preview; Cancel "
    L"discards unapplied appearance changes and Default appearance restores the defaults for that widget type."
    L" Digital clocks provide font, smoothing, colours, opacity, padding, border width and a transparent "
    L"background. Digital clocks, calendars and panels share four border styles; the single-line border has a "
    L"selectable colour. The panel has separate fonts for its top row, time and bottom row, a leading zero and"
    L" selectable clock-face sizes. Custom calendar fonts are supported with the Windows classic appearance or with visual styles turned off for the application or widget"
    L". Settings can be exported to XML. "
    L"Importing XML immediately loads and saves the settings to the currently selected storage without "
    L"changing the storage type. Automatic XML is %AppData%\\FortSoft\\CalClock\\settings.xml. After writing "
    L"XML, HKCU\\SOFTWARE\\FortSoft\\CalClock is removed; registry storage removes the automatic "
    L"XML.\r\n\r\nFont antialiasing offers ClearType, GDI, and None.\r\n\r\nLeading zero offers Show "
    L"(default), Keep space, and No space. Keep space hides the zero while reserving its width in the selected"
    L" font; the other digits keep their positions even with proportional fonts. Monitor clocks remain "
    L"centred, including the reserved space. The UTC row keeps its own centre alignment.",
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
    L"centrados, incluindo o espaço reservado. A linha UTC mantém o seu próprio alinhamento ao centro.\r\n\r\nOs tipos de letra personalizados do calendário são suportados com o aspeto clássico do Windows ou com os temas desativados para a aplicação ou o widget.",
    L"\r\n\r\nLAGRING\r\nInnstillinger lagres i registeret under HKCU\\SOFTWARE\\FortSoft\\CalClock eller "
    L"som "
    L"XML i %AppData%\\FortSoft\\CalClock\\settings.xml. Digitale klokker, kalendere og paneler har fire "
    L"felles kantstiler; fargen på den enkle kanten kan velges. Bytte av lagring fjerner bare "
    L"tidligere CalClock-data. Innstillinger kan eksporteres til XML. XML-import laster inn og lagrer "
    L"innstillingene umiddelbart i valgt lagring uten å endre lagringstypen.\r\n\r\nSkriftutjevning "
    L"tilbyr ClearType, GDI og Ingen.\r\n\r\nInnledende null tilbyr Vis (standard), Behold plass og Uten "
    L"plass. Behold plass skjuler nullen og reserverer bredden i valgt skrift; andre sifre beholder "
    L"plasseringen også med proporsjonale skrifter. Monitorklokker forblir sentrert, inkludert "
    L"reservert plass. UTC-linjen beholder sin egen sentrering.\r\n\r\nEgendefinerte kalenderskrifter støttes med klassisk Windows-utseende eller når temaer er deaktivert for programmet eller widgeten.",
    L"\r\n\r\nLAGRING\r\nInställningar sparas i registret under HKCU\\SOFTWARE\\FortSoft\\CalClock eller som "
    L"XML i %AppData%\\FortSoft\\CalClock\\settings.xml. Digitala klockor, kalendrar och paneler har "
    L"fyra gemensamma kantstilar; färgen på den enkla kanten kan väljas. Byte av lagring tar bara "
    L"bort tidigare CalClock-data. Inställningar kan exporteras till XML. XML-import läser in och "
    L"sparar inställningarna direkt i vald lagring utan att ändra "
    L"lagringstypen.\r\n\r\nTeckensnittsutjämning erbjuder ClearType, GDI och Ingen.\r\n\r\nInledande nolla "
    L"erbjuder Visa (standard), Behåll utrymme och Utan utrymme. Behåll utrymme döljer nollan och "
    L"reserverar dess bredd i valt teckensnitt; övriga siffror behåller sina positioner även med "
    L"proportionella teckensnitt. Bildskärmsklockor förblir centrerade, inklusive reserverat utrymme. "
    L"UTC-raden behåller sin egen centrering.\r\n\r\nEgna kalenderteckensnitt stöds med Windows klassiska utseende eller när teman är avstängda för programmet eller widgeten.",
    L"\r\n\r\nTALLENNUS\r\nAsetukset tallennetaan rekisteriin kohtaan HKCU\\SOFTWARE\\FortSoft\\CalClock tai "
    L"XML-tiedostoon kansiossa %AppData%\\FortSoft\\CalClock\\settings.xml. Digitaalikelloilla, "
    L"kalentereilla ja paneeleilla on neljä yhteistä reunatyyliä; yksinkertaisen reunan väri voidaan "
    L"valita. Tallennustavan vaihto poistaa vain aiemmat CalClock-tiedot. Asetukset voi viedä "
    L"XML-tiedostoon. XML-tuonti lataa ja tallentaa asetukset heti valittuun tallennuspaikkaan "
    L"muuttamatta tallennustapaa.\r\n\r\nFontin pehmennyksen vaihtoehdot ovat ClearType, GDI ja Ei "
    L"mitään.\r\n\r\nEtunolla tarjoaa Näytä (oletus), Varaa tila ja Ilman tilaa. Varaa tila piilottaa "
    L"nollan mutta varaa sen leveyden valitussa fontissa; muut numerot säilyttävät paikkansa myös "
    L"suhteellisilla fonteilla. Näyttökellot pysyvät keskitettyinä varattu tila mukaan lukien. "
    L"UTC-rivi säilyttää oman keskityksensä.\r\n\r\nKalenterin mukautettuja fontteja voi käyttää Windowsin perinteisessä ulkoasussa tai kun sovelluksen tai pienoisohjelman teemat on poistettu käytöstä.",
    L"\r\n\r\nLAGRING\r\nIndstillinger gemmes i registreringsdatabasen under "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock eller som XML i %AppData%\\FortSoft\\CalClock\\settings.xml. "
    L"Digitale ure, kalendere og paneler har fire fælles kanttyper; farven på den enkle kant kan "
    L"vælges. Skift af lager fjerner kun tidligere CalClock-data. Indstillinger kan eksporteres til "
    L"XML. XML-import indlæser og gemmer straks indstillingerne i det valgte lager uden at ændre "
    L"lagertypen.\r\n\r\nSkriftudjævning tilbyder ClearType, GDI og Ingen.\r\n\r\nForanstillet nul tilbyder "
    L"Vis (standard), Bevar plads og Uden plads. Bevar plads skjuler nullet og reserverer dets bredde "
    L"i den valgte skrifttype; øvrige cifre beholder deres placering også med proportionale "
    L"skrifttyper. Skærmure forbliver centrerede inklusive reserveret plads. UTC-linjen bevarer sin "
    L"egen centrering.\r\n\r\nBrugerdefinerede kalenderskrifttyper understøttes med Windows' klassiske udseende, eller når temaer er slået fra for programmet eller widgeten.",
    L"\r\n\r\nGEYMSLA\r\nStillingar eru vistaðar í skrásetningu undir HKCU\\SOFTWARE\\FortSoft\\CalClock eða "
    L"sem XML í %AppData%\\FortSoft\\CalClock\\settings.xml. Stafrænar klukkur, dagatöl og spjöld hafa "
    L"fjórar sameiginlegar rammagerðir; velja má lit einfalda rammans. Skipti um geymslu fjarlægja "
    L"aðeins eldri CalClock-gögn. Hægt er að flytja stillingar út sem XML. Innflutningur XML hleður "
    L"og vistar stillingarnar strax í valinni geymslu án þess að breyta gerð hennar.\r\n\r\nLeturjöfnun "
    L"býður upp á ClearType, GDI og Engin.\r\n\r\nNúll fremst býður upp á Sýna (sjálfgefið), Halda plássi "
    L"og Án pláss. Halda plássi felur núllið en tekur frá breidd þess í völdu letri; aðrir tölustafir "
    L"halda stöðu sinni jafnvel með misbreiðu letri. Skjáklukkur haldast miðjaðar með fráteknu "
    L"plássi. UTC-línan heldur eigin miðjun.\r\n\r\nNota má sérsniðið letur í dagatali með hefðbundnu útliti Windows eða þegar slökkt er á þemum fyrir forritið eða græjuna.",
    L"\r\n\r\nDEPOLAMA\r\nAyarlar HKCU\\SOFTWARE\\FortSoft\\CalClock altındaki kayıt defterinde veya "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml içindeki XML dosyasında saklanır. Dijital saatler, "
    L"takvimler ve paneller aynı dört kenarlık stilini kullanır; basit kenarlığın rengi seçilebilir. "
    L"Depolamayı değiştirmek yalnızca önceki CalClock verilerini kaldırır. Ayarlar XML olarak dışa "
    L"aktarılabilir. XML içe aktarma, depolama türünü değiştirmeden ayarları hemen yükler ve seçili "
    L"depolamaya kaydeder.\r\n\r\nYazı tipi kenar yumuşatma seçenekleri ClearType, GDI ve Yok "
    L"şeklindedir.\r\n\r\nBaştaki sıfır için Göster (varsayılan), Yer ayır ve Yer ayırma seçenekleri "
    L"vardır. Yer ayır, sıfırı gizleyip seçilen yazı tipindeki genişliğini korur; diğer rakamlar "
    L"orantılı yazı tiplerinde bile konumlarını korur. Monitör saatleri ayrılan alan dâhil ortalanır. "
    L"UTC satırı kendi orta hizalamasını korur.\r\n\r\nÖzel takvim yazı tipleri, Windows klasik görünümünde veya uygulama ya da araç için temalar kapatıldığında desteklenir.",
    L"\r\n\r\nIlme ja salvestamine\r\nIlme muutused on kohe eelvaates näha. Loobu hülgab rakendamata "
    L"muudatused ja Vaikeilme taastab vidinatüübi vaikesätted. Digitaalkell toetab fonti, silumist, värve, "
    L"läbipaistmatust, siseveerist, äärise laiust ja läbipaistvat tausta. Kellad, kalendrid ja paneelid "
    L"jagavad nelja ääriselaadi; ühekordse äärise värvi saab valida. Paneelil on eraldi fondid ülemisele "
    L"reale, kellaajale ja alumisele reale, algusnull ning valitavad sihverplaadisuurused. Kujundused ja "
    L"silumine määratakse rakendusele ja igale vidinale eraldi. Kohandatud kalendrifonte saab kasutada Windowsi klassikalise ilmega või siis, kui rakenduse või vidin"
    L"a kujundused on välja lülitatud.\r\n\r\nSätteid saab eksportida XML-i. Import laadib ja salvestab sätted kohe "
    L"praegusesse salvestuskohta selle tüüpi muutmata. Automaatne XML asub failis "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. XML-i kirjutamine eemaldab võtme "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; registrisse salvestamine eemaldab automaatse XML-i.\r\n\r\nFondi "
    L"silumine pakub ClearType, GDI ja Puudub. Algusnull pakub Kuva (vaikimisi), Säilita ruum ja Ilma ruumita."
    L" Säilita ruum peidab nulli, kuid reserveerib selle laiuse valitud fondis; ülejäänud numbrid säilitavad "
    L"asukoha ka proportsionaalse fondiga. Ekraanikella keskjoondus arvestab reserveeritud ruumi. UTC-real on "
    L"oma keskjoondus.",
    L"\r\n\r\nCuma agus stóras\r\nFeictear athruithe cuma sa réamhamharc láithreach. Caitheann Cealaigh "
    L"athruithe nach bhfuil curtha i bhfeidhm i leataobh; athchóiríonn Cuma réamhshocraithe réamhshocruithe an"
    L" chineáil. Tá cló, frithailiasáil, dathanna, teimhneacht, spásáil inmheánach, leithead imlíne agus cúlra"
    L" trédhearcach ar fáil do chloig dhigiteacha. Tá ceithre stíl imlíne ag cloig, féilirí agus painéil; is "
    L"féidir dath na himlíne aonlíne a roghnú. Tá clónna ar leith ag an bpainéal don tsraith uachtarach, don "
    L"am agus don tsraith íochtarach, chomh maith le nialas tosaigh agus méideanna aghaidhe. Socraítear téamaí"
    L" agus frithailiasáil don fheidhmchlár agus do gach giuirléid. Tacaítear le clónna saincheaptha féilire le cuma chlasaice"
    L"ach Windows nó nuair atá téamaí múchta don fheidhmchlár nó don ghiuirléid.\r\n\r\nIs féidir socruithe a easpórtáil mar XML. Lódálann agus"
    L" sábhálann iompórtáil XML na socruithe láithreach sa stóras roghnaithe gan a chineál a athrú. Is é "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml an XML uathoibríoch. Tar éis XML a scríobh, baintear "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; baineann stóráil sa chlárlann an XML uathoibríoch.\r\n\r\nTugann "
    L"Frithailiasáil cló ClearType, GDI agus Gan frithailiasáil. Tugann Nialas tosaigh Taispeáin "
    L"(réamhshocrú), Coinnigh an spás agus Gan spás. Folaíonn Coinnigh an spás an nialas ach coimeádann sé a "
    L"leithead sa chló roghnaithe; fanann digití eile ina n-áit le clónna comhréireacha freisin. Fanann cloig "
    L"scáileáin lárnaithe agus an spás sin san áireamh. Tá lárnú ar leith ag sraith UTC.",
    L"\r\n\r\nIšvaizda ir saugojimas\r\nIšvaizdos pakeitimai iškart matomi peržiūroje. Atšaukti atmeta "
    L"nepritaikytus pakeitimus, Numatytoji išvaizda atkuria šio tipo valdiklio numatytąsias reikšmes. "
    L"Skaitmeniniai laikrodžiai siūlo šriftą, glodinimą, spalvas, nepermatomumą, vidinę paraštę, kraštinės "
    L"plotį ir permatomą foną. Laikrodžiai, kalendoriai ir skydeliai turi keturis bendrus kraštinių stilius; "
    L"viengubai kraštinei galima pasirinkti spalvą. Skydelis turi atskirus viršutinės eilutės, laiko ir "
    L"apatinės eilutės šriftus, pradinį nulį ir ciferblatų dydžius. Temos ir glodinimas nustatomi programai ir"
    L" kiekvienam valdikliui. Pasirinktinius kalendoriaus šriftus galima naudoti su klasikine „Windows“ išvaizda arba išjungus programos ar valdiklio "
    L"temas.\r\n\r\nParametrus galima eksportuoti į XML. Importas iškart įkelia ir įrašo parametrus į "
    L"pasirinktą saugyklą nekeisdamas jos tipo. Automatinis XML yra "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Įrašius XML pašalinamas HKCU\\SOFTWARE\\FortSoft\\CalClock "
    L"raktas; įrašymas į registrą pašalina automatinį XML.\r\n\r\nŠrifto glodinimas siūlo ClearType, GDI ir "
    L"Nėra. Pradinis nulis siūlo Rodyti (numatyta), Palikti vietą ir Be vietos. Palikti vietą slepia nulį, bet"
    L" rezervuoja jo plotį pasirinktame šrifte; kiti skaitmenys nepajuda ir naudojant proporcinį šriftą. "
    L"Ekrano laikrodžių centravimas įskaito rezervuotą vietą. UTC eilutė centruojama atskirai.",
    L"\r\n\r\nIzskats un glabāšana\r\nIzskata izmaiņas uzreiz redzamas priekšskatījumā. Atcelt atmet "
    L"nelietotās izmaiņas, Noklusējuma izskats atjauno logrīka tipa noklusējumus. Digitālie pulksteņi piedāvā "
    L"fontu, nogludināšanu, krāsas, necaurspīdīgumu, iekšējo atkāpi, apmales platumu un caurspīdīgu fonu. "
    L"Pulksteņiem, kalendāriem un paneļiem ir četri kopīgi apmales stili; vienas līnijas apmalei var "
    L"izvēlēties krāsu. Panelim ir atsevišķi augšējās rindas, laika un apakšējās rindas fonti, sākuma nulle un"
    L" ciparnīcu lielumi. Dizainus un nogludināšanu iestata programmai un katram logrīkam. Pielāgotus kalendāra "
    L"fontus var izmantot ar Windows klasisko izskatu vai tad, ja lietotnei vai logrīkam ir izslēgti dizaini.\r\n\r\nIestatījumus var eksportēt XML. Imports tos "
    L"uzreiz ielādē un saglabā izvēlētajā krātuvē, nemainot tās tipu. Automātiskais XML ir "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. XML ierakstīšana noņem HKCU\\SOFTWARE\\FortSoft\\CalClock "
    L"atslēgu; saglabāšana reģistrā noņem automātisko XML.\r\n\r\nFonta nogludināšana piedāvā ClearType, GDI "
    L"un Nav. Sākuma nulle piedāvā Rādīt (noklusējums), Saglabāt vietu un Bez vietas. Saglabāt vietu slēpj "
    L"nulli, rezervējot tās platumu izvēlētajā fontā; pārējie cipari paliek vietā arī proporcionālā fontā. "
    L"Ekrāna pulksteņi tiek centrēti, ieskaitot rezervēto vietu. UTC rindai ir atsevišķa centrēšana.",
    L"\r\n\r\nMegjelenés és tárolás\r\nA megjelenés változásai azonnal láthatók az előnézetben. A Mégse elveti"
    L" az alkalmazatlan változtatásokat, az Alapértelmezett megjelenés visszaállítja a típus alapértékeit. A "
    L"digitális órához betűtípus, élsimítás, színek, átlátszatlanság, belső margó, szegélyvastagság és "
    L"átlátszó háttér választható. Az órák, naptárak és panelek négy közös szegélystílust használnak; az "
    L"egysoros szegély színezhető. A panel felső sorának, idejének és alsó sorának külön betűtípusa van, "
    L"vezető nullával és számlapméretekkel. A témák és élsimítás a programhoz és minden minialkalmazáshoz "
    L"külön adhatók meg. Egyéni naptárbetűtípusok a Windows klasszikus megjelenésével, illetve az alkalmazás vagy a minialkalmazás témáinak kikapcsolásával használhatók.\r\n\r\nA "
    L"beállítások XML-be exportálhatók. Az importálás azonnal betölti és a kijelölt tárolóba menti őket, a "
    L"tárolótípus megváltoztatása nélkül. Az automatikus XML helye "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Az XML írása törli a HKCU\\SOFTWARE\\FortSoft\\CalClock "
    L"kulcsot; a beállításjegyzékbe mentés törli az automatikus XML-t.\r\n\r\nA Betűtípus élsimítása lehet "
    L"ClearType, GDI vagy Nincs. A Vezető nulla választásai: Megjelenítés (alapértelmezett), Hely megtartása "
    L"és Hely nélkül. A Hely megtartása elrejti a nullát, de fenntartja a szélességét; a többi számjegy "
    L"arányos betűtípusnál sem mozdul el. A képernyőórák középre igazítása ezt a helyet is figyelembe veszi. "
    L"Az UTC-sor külön igazodik középre.",
    L"\r\n\r\nDehra u ħażna\r\nIl-bidliet fid-dehra jidhru minnufih fil-previżjoni. Ikkanċella jarmi l-bidliet"
    L" mhux applikati, Dehra default jerġa’ jġib il-valuri default tat-tip. L-arloġġi diġitali joffru font, "
    L"anti-aliasing, kuluri, opaċità, spazju intern, wisa’ tal-bordura u sfond trasparenti. L-arloġġi, "
    L"il-kalendarji u l-panewijiet għandhom erba’ stili tal-bordura komuni; il-bordura b’linja waħda għandha "
    L"kulur magħżul. Il-panew għandu fonts separati għar-ringiela ta’ fuq, il-ħin u r-ringiela t’isfel, żero "
    L"fil-bidu u daqsijiet tal-uċuħ. It-temi u l-anti-aliasing jiġu ssettjati għall-programm u għal kull "
    L"widget. Il-fonts personalizzati tal-kalendarju huma appoġġjati bid-dehra klassika ta’ Windows jew meta t-temi jkunu mitfija għall-applikazzjoni jew il-widget.\r\n\r\nIs-settings "
    L"jistgħu jiġu esportati f’XML. L-importazzjoni tgħabbi u tissejvja s-settings minnufih fil-ħażna magħżula"
    L" mingħajr ma tbiddel it-tip tagħha. L-XML awtomatiku huwa %AppData%\\FortSoft\\CalClock\\settings.xml. "
    L"Il-kitba tal-XML tneħħi ċ-ċavetta HKCU\\SOFTWARE\\FortSoft\\CalClock; il-ħażna fir-reġistru tneħħi l-XML"
    L" awtomatiku.\r\n\r\nAnti-aliasing tal-font joffri ClearType, GDI u Xejn. Żero fil-bidu joffri Uri "
    L"(default), Żomm l-ispazju u Bla spazju. Żomm l-ispazju jaħbi ż-żero iżda jirriżerva l-wisa’ tiegħu "
    L"fil-font magħżul; iċ-ċifri l-oħra jibqgħu f’posthom anki b’fonts proporzjonali. L-arloġġi tal-iskrin "
    L"jibqgħu ċċentrati inkluż l-ispazju riżervat. Ir-ringiela UTC tiġi ċċentrata separatament.",
    L"\r\n\r\nVormgeving en opslag\r\nWijzigingen in de vormgeving verschijnen direct in het voorbeeld. "
    L"Annuleren verwerpt niet-toegepaste wijzigingen; Standaardvormgeving herstelt de standaardwaarden voor "
    L"dat type. Digitale klokken bieden lettertypen, vereffening, kleuren, dekking, binnenmarge, randbreedte "
    L"en een transparante achtergrond. Klokken, kalenders en panelen delen vier randstijlen; een enkele rand "
    L"heeft een instelbare kleur. Een paneel heeft aparte lettertypen voor de bovenste rij, tijd en onderste "
    L"rij, een voorloopnul en wijzerplaatgroottes. Thema’s en lettertypevereffening worden voor de toepassing "
    L"en elke widget ingesteld. Aangepaste kalenderlettertypen worden ondersteund bij de klassieke Windows-weergave of als thema’s voor de toepassing of widget zijn "
    L"uitgeschakeld.\r\n\r\nInstellingen kunnen naar XML worden geëxporteerd. Importeren laadt en bewaart de "
    L"instellingen direct in de gekozen opslag zonder het opslagtype te veranderen. Automatische XML staat in "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Na XML-opslag wordt HKCU\\SOFTWARE\\FortSoft\\CalClock "
    L"verwijderd; opslag in het register verwijdert de automatische XML.\r\n\r\nLettertypevereffening biedt "
    L"ClearType, GDI en Geen. Voorloopnul biedt Weergeven (standaard), Ruimte behouden en Zonder ruimte. "
    L"Ruimte behouden verbergt de nul maar reserveert de breedte in het gekozen lettertype; andere cijfers "
    L"behouden hun positie, ook bij proportionele lettertypen. Schermklokken blijven gecentreerd inclusief die"
    L" ruimte. De UTC-rij heeft een eigen centrering.",
    L"\r\n\r\nAspect și stocare\r\nModificările de aspect se văd imediat în previzualizare. Anulare respinge "
    L"modificările neaplicate, Aspect implicit restabilește valorile implicite ale tipului. Ceasurile digitale"
    L" oferă font, netezire, culori, opacitate, spațiere interioară, grosime a bordurii și fundal transparent."
    L" Ceasurile, calendarele și panourile au patru stiluri comune de bordură; bordura simplă are culoare "
    L"configurabilă. Panoul are fonturi separate pentru rândul superior, oră și rândul inferior, zero inițial "
    L"și dimensiuni ale cadranelor. Temele și netezirea sunt configurate pentru aplicație și fiecare widget. "
    L"Fonturile personalizate ale calendarului sunt acceptate cu aspectul clasic Windows sau când temele sunt dezactivate pentru aplicație ori widget.\r\n\r\nSetările pot fi "
    L"exportate în XML. Importul încarcă și salvează imediat setările în stocarea aleasă fără a-i schimba "
    L"tipul. XML-ul automat este %AppData%\\FortSoft\\CalClock\\settings.xml. Scrierea XML elimină cheia "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; stocarea în registry elimină XML-ul automat.\r\n\r\nNetezire font "
    L"oferă ClearType, GDI și Fără. Zero inițial oferă Afișare (implicit), Păstrare spațiu și Fără spațiu. "
    L"Păstrare spațiu ascunde zero, rezervând lățimea lui în fontul ales; celelalte cifre rămân pe poziție și "
    L"cu fonturi proporționale. Ceasurile pe ecran rămân centrate incluzând spațiul rezervat. Rândul UTC are "
    L"centrare separată.",
    L"\r\n\r\nΕμφάνιση και αποθήκευση\r\nΟι αλλαγές εμφάνισης φαίνονται αμέσως στην προεπισκόπηση. Το Άκυρο "
    L"απορρίπτει μη εφαρμοσμένες αλλαγές· η Προεπιλεγμένη εμφάνιση επαναφέρει τις προεπιλογές του τύπου. Τα "
    L"ψηφιακά ρολόγια προσφέρουν γραμματοσειρά, εξομάλυνση, χρώματα, αδιαφάνεια, εσωτερικό περιθώριο, πλάτος "
    L"περιγράμματος και διαφανές φόντο. Ρολόγια, ημερολόγια και πλαίσια έχουν τέσσερα κοινά στυλ "
    L"περιγράμματος· η μονή γραμμή έχει επιλέξιμο χρώμα. Το πλαίσιο έχει χωριστές γραμματοσειρές επάνω "
    L"γραμμής, ώρας και κάτω γραμμής, αρχικό μηδενικό και μεγέθη καντράν. Θέματα και εξομάλυνση ορίζονται για "
    L"την εφαρμογή και κάθε στοιχείο. Οι προσαρμοσμένες γραμματοσειρές ημερολογίου υποστηρίζονται με την κλασική εμφάνιση των Windows ή όταν τα θέματα είναι "
    L"απενεργοποιημένα για την εφαρμογή ή το γραφικό στοιχείο.\r\n\r\nΟι ρυθμίσεις εξάγονται σε XML. Η εισαγωγή τις φορτώνει και τις "
    L"αποθηκεύει αμέσως στον επιλεγμένο χώρο χωρίς αλλαγή τύπου αποθήκευσης. Το αυτόματο XML είναι "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Η εγγραφή XML αφαιρεί το κλειδί "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock· η αποθήκευση στο μητρώο αφαιρεί το αυτόματο XML.\r\n\r\nΗ Εξομάλυνση"
    L" γραμματοσειράς προσφέρει ClearType, GDI και Καμία. Το Αρχικό μηδενικό προσφέρει Εμφάνιση (προεπιλογή), "
    L"Διατήρηση χώρου και Χωρίς χώρο. Η Διατήρηση χώρου κρύβει το μηδενικό αλλά δεσμεύει το πλάτος του στην "
    L"επιλεγμένη γραμματοσειρά· τα άλλα ψηφία μένουν στη θέση τους και με αναλογικές γραμματοσειρές. Το "
    L"κεντράρισμα των ρολογιών οθόνης περιλαμβάνει τον δεσμευμένο χώρο. Η γραμμή UTC κεντράρεται χωριστά.",
    L"\r\n\r\nIzgled i čuvanje postavki\r\nPromjene izgleda odmah se prikazuju u pregledu. Otkaži odbacuje "
    L"neprimijenjene promjene, a Podrazumijevani izgled vraća podrazumijevane vrijednosti za tu vrstu vidžeta."
    L" Digitalni satovi nude font, izglađivanje, boje, neprozirnost, unutrašnji razmak, širinu obruba i "
    L"prozirnu pozadinu. Digitalni satovi, kalendari i ploče dijele četiri stila obruba; boja jednostrukog "
    L"obruba može se odabrati. Ploča ima odvojene fontove gornjeg reda, vremena i donjeg reda, početnu nulu i "
    L"odabir veličine brojčanika. Prilagođeni fontovi kalendara podržani su uz klasični izgled Windowsa ili kada su teme isključene za program ili vidžet"
    L". Postavke se mogu izvesti u XML. "
    L"Uvoz XML-a odmah učitava i čuva postavke u odabrano spremište bez promjene njegove vrste. Automatska XML"
    L" datoteka je %AppData%\\FortSoft\\CalClock\\settings.xml. Nakon zapisivanja XML-a uklanja se ključ "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; čuvanje u registar uklanja automatsku XML "
    L"datoteku.\r\n\r\nIzglađivanje fonta nudi ClearType, GDI i Nema. Početna nula nudi Prikaži "
    L"(podrazumijevano), Zadrži razmak i Bez razmaka. Zadrži razmak skriva nulu, ali rezervira njezinu širinu "
    L"u odabranom fontu, pa ostale znamenke zadržavaju položaj i kod proporcionalnih fontova. Satovi na ekranu"
    L" ostaju centrirani, uključujući rezervirani razmak. Red UTC ima vlastito centriranje.",
    L"\r\n\r\nIzgled i spremanje postavki\r\nPromjene izgleda odmah se prikazuju u pretpregledu. Odustani "
    L"odbacuje neprimijenjene promjene, a Zadani izgled vraća zadane vrijednosti za tu vrstu widgeta. "
    L"Digitalni satovi nude font, izglađivanje, boje, neprozirnost, unutarnji razmak, širinu obruba i prozirnu"
    L" pozadinu. Digitalni satovi, kalendari i ploče dijele četiri stila obruba; boja jednostrukog obruba može"
    L" se odabrati. Ploča ima odvojene fontove gornjeg retka, vremena i donjeg retka, početnu nulu i odabir "
    L"veličine brojčanika. Prilagođeni fontovi kalendara podržani su uz klasični izgled Windowsa ili kada su teme isključene za program ili widget"
    L". Postavke se mogu izvesti u XML. Uvoz XML-a "
    L"odmah učitava i sprema postavke u odabrano spremište bez promjene njegove vrste. Automatska XML datoteka"
    L" je %AppData%\\FortSoft\\CalClock\\settings.xml. Nakon zapisivanja XML-a uklanja se ključ "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; spremanje u registar uklanja automatsku XML "
    L"datoteku.\r\n\r\nIzglađivanje fonta nudi ClearType, GDI i Nema. Početna nula nudi Prikaži (zadano), "
    L"Zadrži razmak i Bez razmaka. Zadrži razmak skriva nulu, ali rezervira njezinu širinu u odabranom fontu, "
    L"pa ostale znamenke zadržavaju položaj i kod proporcionalnih fontova. Satovi na zaslonu ostaju "
    L"centrirani, uključujući rezervirani razmak. Redak UTC ima vlastito centriranje.",
    L"\r\n\r\nVidez in shranjevanje\r\nSpremembe videza so vidne takoj v predogledu. Prekliči zavrže "
    L"neuporabljene spremembe, Privzeti videz pa obnovi privzete vrednosti vrste gradnika. Digitalne ure "
    L"ponujajo pisavo, glajenje, barve, neprosojnost, notranji odmik, širino obrobe in prosojno ozadje. "
    L"Digitalne ure, koledarji in plošče imajo štiri skupne sloge obrob; enojni obrobi lahko določite barvo. "
    L"Plošča ima ločene pisave zgornje vrstice, časa in spodnje vrstice, vodilno ničlo in izbiro velikosti "
    L"številčnic. Teme in glajenje se določijo za program in vsak gradnik. Pisavo koledarja po meri lahko "
    L"uporabljate pri klasičnem videzu sistema Windows ali ko so teme izključene za program ali gradnik. Nastavitve je mogoče izvoziti v XML. Uvoz XML takoj naloži in "
    L"shrani nastavitve v izbrano shrambo, ne da bi spremenil njeno vrsto. Samodejni XML je "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Zapis XML odstrani ključ "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; shranjevanje v register odstrani samodejni XML.\r\n\r\nGlajenje "
    L"pisave ponuja ClearType, GDI in Brez. Vodilna ničla ponuja Pokaži (privzeto), Ohrani prostor in Brez "
    L"prostora. Ohrani prostor skrije ničlo in rezervira njeno širino v izbrani pisavi; druge števke ostanejo "
    L"na mestu tudi pri proporcionalnih pisavah. Ure na zaslonu ostanejo sredinsko poravnane z upoštevanjem "
    L"rezerviranega prostora. Vrstica UTC ima lastno sredinsko poravnavo.",
    L"\r\n\r\nIzgled i čuvanje\r\nPromjene izgleda odmah se vide u pregledu. Otkaži odbacuje neprimijenjene "
    L"promjene, a Podrazumijevani izgled vraća podrazumijevane vrijednosti za vrstu vidžeta. Digitalni satovi "
    L"nude font, umekšavanje, boje, neprozirnost, unutrašnji razmak, širinu okvira i providnu pozadinu. "
    L"Digitalni satovi, kalendari i paneli dijele četiri stila okvira; jednostrukom okviru može se birati "
    L"boja. Panel ima zasebne fontove za gornji red, vrijeme i donji red, vodeću nulu i izbor veličine "
    L"brojčanika. Teme i umekšavanje zadaju se za program i svaki vidžet. Prilagođeni fontovi kalendara podrža"
    L"ni su uz klasični izgled Windows-a ili kada su teme isključene za program ili vidžet. Podešavanja se mogu izvesti u XML. Uvoz XML-a odmah učitava i "
    L"čuva podešavanja u izabranom skladištu bez promjene njegove vrste. Automatski XML je "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Po zapisivanju XML-a uklanja se ključ "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; čuvanje u registru uklanja automatski XML.\r\n\r\nUmekšavanje fonta "
    L"nudi ClearType, GDI i Nema. Vodeća nula nudi Prikaži (podrazumijevano), Zadrži razmak i Bez razmaka. "
    L"Zadrži razmak skriva nulu, ali čuva njenu širinu u izabranom fontu; ostale cifre zadržavaju položaje i "
    L"kod proporcionalnih fontova. Satovi na monitoru ostaju centrirani sa uračunatim razmakom. Red UTC ima "
    L"sopstveno centriranje.",
    L"\r\n\r\nВыгляд і захоўванне\r\nЗмены выгляду адразу бачныя ў папярэднім праглядзе. «Скасаваць» адхіляе "
    L"неўжытыя змены, а «Прадвызначаны выгляд» вяртае прадвызначаныя значэнні тыпу віджэта. Лічбавыя "
    L"гадзіннікі прапануюць шрыфт, згладжванне, колеры, непразрыстасць, унутраны водступ, таўшчыню рамкі і "
    L"празрысты фон. Гадзіннікі, календары і панэлі маюць чатыры агульныя стылі рамкі; для адзінарнай рамкі "
    L"выбіраецца колер. Панэль мае асобныя шрыфты верхняга радка, часу і ніжняга радка, пачатковы нуль і выбар"
    L" памераў цыферблатаў. Тэмы і згладжванне задаюцца для праграмы і кожнага віджэта. Уласныя шрыфты "
    L"календара падтрымліваюцца пры класічным выглядзе Windows або калі тэмы адключаныя для праграмы ці віджэта. Налады можна экспартаваць у XML. Імпарт XML адразу "
    L"загружае і захоўвае налады ў бягучым сховішчы, не змяняючы яго тып. Аўтаматычны файл XML — "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Пасля запісу XML ключ HKCU\\SOFTWARE\\FortSoft\\CalClock "
    L"выдаляецца; захоўванне ў рэестры выдаляе аўтаматычны XML.\r\n\r\nЗгладжванне шрыфту прапануе ClearType, "
    L"GDI і «Няма». «Пачатковы нуль» мае варыянты «Паказваць» (прадвызначаны), «Пакідаць месца» і «Без месца»."
    L" «Пакідаць месца» хавае нуль, але рэзервуе яго шырыню ў выбраным шрыфце; астатнія лічбы захоўваюць "
    L"пазіцыі і ў прапарцыянальных шрыфтах. Гадзіннікі на маніторы застаюцца па цэнтры з улікам "
    L"зарэзерваванага месца. Радок UTC мае асобнае цэнтраванне.",
    L"\r\n\r\nИзглед и съхраняване\r\nПромените на изгледа се показват веднага в предварителния преглед. "
    L"„Отказ“ отхвърля неприложените промени, а „Изглед по подразбиране“ връща стандартните стойности за вида "
    L"модул. Цифровите часовници предлагат шрифт, изглаждане, цветове, непрозрачност, вътрешен отстъп, "
    L"дебелина на рамката и прозрачен фон. Часовниците, календарите и панелите имат четири общи стила на "
    L"рамката; за единичната рамка се избира цвят. Панелът има отделни шрифтове за горния ред, часа и долния "
    L"ред, водеща нула и избор на размери на циферблатите. Темите и изглаждането се задават за програмата и "
    L"всеки модул. Персонализираните шрифтове на календара се поддържат при класически облик на Windows или когато темите са изключени за приложението или модула. Настройките могат "
    L"да се експортират в XML. Импортирането веднага зарежда и записва настройките в текущото хранилище, без "
    L"да сменя типа му. Автоматичният XML е %AppData%\\FortSoft\\CalClock\\settings.xml. След запис на XML "
    L"ключът HKCU\\SOFTWARE\\FortSoft\\CalClock се премахва; записът в регистъра премахва автоматичния "
    L"XML.\r\n\r\nИзглаждането предлага ClearType, GDI и „Няма“. „Водеща нула“ предлага „Показвай“ (по "
    L"подразбиране), „Запази мястото“ и „Без място“. „Запази мястото“ скрива нулата, но запазва ширината ѝ в "
    L"избрания шрифт; другите цифри остават на място дори при пропорционални шрифтове. Часовниците на монитор "
    L"остават центрирани с включено запазено място. Редът UTC има отделно центриране.",
    L"\r\n\r\nИзглед и зачувување\r\nПромените на изгледот се гледаат веднаш во прегледот. „Откажи“ ги отфрла "
    L"неприменетите промени, а „Стандарден изглед“ ги враќа стандардните вредности за видот на виџетот. "
    L"Дигиталните часовници нудат фонт, измазнување, бои, непроѕирност, внатрешна маргина, дебелина на рамката"
    L" и проѕирна заднина. Часовниците, календарите и панелите имаат четири заеднички стила на рамка; за "
    L"еднолиниската рамка се избира боја. Панелот има посебни фонтови за горниот ред, времето и долниот ред, "
    L"водечка нула и избор на големини на бројчаниците. Темите и измазнувањето се поставуваат за програмата и "
    L"секој виџет. Приспособените фонтови на календарот се поддржани со класичниот изглед на Windows или кога темите се исклучени за апликацијата или виџетот. Поставките може"
    L" да се извезат во XML. Увозот XML веднаш ги вчитува и зачувува во тековното складиште без да го менува "
    L"неговиот вид. Автоматскиот XML е %AppData%\\FortSoft\\CalClock\\settings.xml. По запишување XML се "
    L"отстранува клучот HKCU\\SOFTWARE\\FortSoft\\CalClock; чувањето во регистарот го отстранува автоматскиот "
    L"XML.\r\n\r\nИзмазнувањето на фонтот нуди ClearType, GDI и „Нема“. „Водечка нула“ нуди „Прикажувај“ "
    L"(стандардно), „Зачувај место“ и „Без место“. „Зачувај место“ ја крие нулата, но ја задржува нејзината "
    L"ширина во избраниот фонт; другите цифри остануваат на место и кај пропорционални фонтови. Часовниците на"
    L" монитор остануваат центрирани со вклучено резервирано место. Редот UTC има свое центрирање.",
    L"\r\n\r\nИзглед и чување\r\nПромене изгледа одмах се виде у прегледу. Откажи одбацује непримењене "
    L"промене, а Подразумевани изглед враћа подразумеване вредности за врсту виџета. Дигитални сатови нуде "
    L"фонт, умекшавање, боје, непрозирност, унутрашњи размак, ширину оквира и провидну позадину. Дигитални "
    L"сатови, календари и панели деле четири стила оквира; једноструком оквиру може се бирати боја. Панел има "
    L"засебне фонтове за горњи ред, време и доњи ред, водећу нулу и избор величине бројчаника. Теме и "
    L"умекшавање задају се за програм и сваки виџет. Прилагођени фонтови календара подржани су уз класични изглед Windows-а или када су теме "
    L"искључене за програм или виџет. Подешавања се могу извести у XML. Увоз XML-а одмах учитава и чува подешавања у изабраном "
    L"складишту без промене његове врсте. Аутоматски XML је %AppData%\\FortSoft\\CalClock\\settings.xml. По "
    L"записивању XML-а уклања се кључ HKCU\\SOFTWARE\\FortSoft\\CalClock; чување у регистру уклања аутоматски "
    L"XML.\r\n\r\nУмекшавање фонта нуди ClearType, GDI и Нема. Водећа нула нуди Прикажи (подразумевано), "
    L"Задржи размак и Без размака. Задржи размак скрива нулу, али чува њену ширину у изабраном фонту; остале "
    L"цифре задржавају положаје и код пропорционалних фонтова. Сатови на монитору остају центрирани са "
    L"урачунатим размаком. Ред UTC има сопствено центрирање.",
    L"\r\n\r\nВИГЛЯД І ЗБЕРІГАННЯ НАЛАШТУВАНЬ\r\nЗміни вигляду одразу відображаються в попередньому перегляді."
    L" «Скасувати» скасовує незастосовані зміни вигляду, а «Типовий вигляд» повертає типові параметри для "
    L"цього виду віджета. У цифрових годинниках можна налаштувати шрифт, згладжування, кольори, непрозорість, "
    L"внутрішній відступ, товщину рамки й прозоре тло. Цифрові годинники, календарі та панелі мають чотири "
    L"спільні стилі рамки; для однолінійної рамки можна вибрати колір. Панель має окремі шрифти верхнього "
    L"рядка, часу й нижнього рядка, показ початкового нуля та вибір розмірів циферблатів. Власні"
    L" шрифти календаря підтримуються за класичного вигляду Windows або коли теми вимкнено для програми чи віджета"
    L". Налаштування можна експортувати до XML. Імпорт XML одразу завантажує й зберігає "
    L"налаштування в поточному сховищі, не змінюючи його типу. Автоматичне сховище XML — "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Після запису XML розділ HKCU\\SOFTWARE\\FortSoft\\CalClock "
    L"видаляється; вибір зберігання в реєстрі видаляє автоматичний файл XML.\r\n\r\nДля згладжування шрифту "
    L"доступні ClearType, GDI та «Немає».\r\n\r\nПараметр «Початковий нуль» має значення «Показувати» "
    L"(типове), «Залишати місце» та «Без місця». «Залишати місце» приховує нуль, але резервує його ширину у "
    L"вибраному шрифті; решта цифр залишається на місці навіть у пропорційних шрифтах. Годинники на моніторі "
    L"зберігають центрування з урахуванням зарезервованого місця. Рядок UTC має власне центрування.",
    L"\r\n\r\nВНЕШНИЙ ВИД И ХРАНЕНИЕ НАСТРОЕК\r\nИзменения внешнего вида сразу отображаются в предварительном "
    L"просмотре. «Отмена» отменяет неприменённые изменения внешнего вида, а «Вид по умолчанию» возвращает "
    L"исходные параметры этого типа виджета. В цифровых часах можно настроить шрифт, сглаживание, цвета, "
    L"непрозрачность, внутренний отступ, толщину рамки и прозрачный фон. Цифровые часы, календари и панели "
    L"имеют четыре общих стиля рамки; для однолинейной рамки можно выбрать цвет. У панели отдельные шрифты "
    L"верхней строки, времени и нижней строки, показ ведущего нуля и выбор размеров циферблатов. По"
    L"льзовательские шрифты календаря поддерживаются при классическом оформлении Windows или когда темы отключены для программы либо виджета"
    L". Настройки можно экспортировать в XML. Импорт XML сразу загружает и "
    L"сохраняет настройки в текущем хранилище, не меняя его типа. Автоматическое хранилище XML — "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. После записи XML раздел HKCU\\SOFTWARE\\FortSoft\\CalClock "
    L"удаляется; выбор хранения в реестре удаляет автоматический файл XML.\r\n\r\nДля сглаживания шрифта "
    L"доступны ClearType, GDI и «Нет».\r\n\r\nПараметр «Ведущий ноль» имеет значения «Показывать» (по "
    L"умолчанию), «Оставлять место» и «Без места». «Оставлять место» скрывает ноль, но резервирует его ширину "
    L"в выбранном шрифте; остальные цифры остаются на месте даже в пропорциональных шрифтах. Часы на мониторе "
    L"сохраняют центрирование с учётом зарезервированного места. Строка UTC имеет собственное центрирование."
};

const wchar_t* HELP_SETTINGS_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nNASTAVENÍ A NABÍDKY\r\nJazyk, písmo, vyhlazování, motivy, úložiště, spouštění s Windows a "
    L"přichytávání jsou globální a nastavují se na kartě Aplikace. Při prvním spuštění se jazyk volí "
    L"podle uživatelského jazyka Windows, neznámý jazyk se nahradí angličtinou (USA); jazyk, "
    L"vyhlazování a motivy widgetu platí jen pro něj. "
    L"\r\n\r\nNabídka widgetu obsahuje příslušné volby viditelnosti, režimu navrchu, "
    L"sekund, velikosti a kopírování data a dále Zarovnat do mřížky, Nastavení, Nápovědu, O programu "
    L"a Konec. Nabídka ikony uvádí widgety s pořadovými čísly a příkazy Zobrazit vše, Skrýt vše a "
    L"Ztlumit vše. Samostatně oddělený příkaz Zarovnat do mřížky následuje za nimi. Zobrazení či "
    L"obnovení přenese widgety dopředu bez změny Vždy navrchu. Další spuštění aktivuje běžící "
    L"instanci a v případě potřeby obnoví naposledy skryté widgety. Dostupné rozměry ciferníku a "
    L"možnost sekundové ručičky vycházejí z možností používané verze Windows"
    L". Budík a signál lze zapnout "
    L"přímo v nabídce widgetu; položka Budík ukazuje čas a při částečném týdnu také aktivní dny. "
    L"Zaškrtnutí Ztlumit v nabídce widgetu odpovídá volbě Ztlumeno na kartě Obecné. Ztlumit vše v "
    L"nabídce ikony ztlumí všechny widgety a při dalším přepnutí obnoví jen ty, které samo ztlumilo. "
    L"Totéž globální přepnutí provede klávesa M na kterémkoli widgetu. Zapnutí budíku bez vybraného "
    L"dne otevře kartu Budík daného widgetu.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nApplication language, font, smoothing, themes, storage, Windows startup "
    L"and edge snapping are global and are configured on the Application tab. On first launch, the "
    L"application language follows the Windows user-interface language, with US English as the "
    L"fallback; widget language, smoothing and themes affect that widget only. "
    L"\r\n\r\nA widget menu contains the applicable visibility, "
    L"always-on-top, seconds, size and date-copy choices, followed by Arrange in a grid, Settings, "
    L"Help, About and Exit. The notification-icon menu lists numbered widgets and provides Show all, "
    L"Hide all and Mute all. The separately grouped Arrange in a grid command follows. Showing or "
    L"restoring widgets brings them forward without changing Always on top. Starting CalClock again "
    L"activates the running instance and restores the most recently hidden widgets when needed. "
    L"Available face sizes and second-hand support come from the installed Windows version"
    L". Alarm and "
    L"Signal can be toggled directly in a widget menu; Alarm shows its time and, for a partial week, "
    L"its active weekdays. Checked Mute in a widget menu corresponds to Muted on the General tab. "
    L"Mute all in the notification-icon menu mutes every widget and, when toggled again, restores "
    L"only those it muted. Pressing M on any widget performs the same global toggle. Enabling an "
    L"alarm with no weekday selected opens that widget’s Alarm tab.",
    L"\r\n\r\nEINSTELLUNGEN UND MENÜS\r\nAnwendungssprache, Schrift, Glättung, Designs, Speicher, "
    L"Windows-Start und Randeinrasten sind global und werden auf der Registerkarte Anwendung "
    L"eingestellt. Beim ersten Start folgt die Sprache der Windows-Anzeigesprache; sonst wird "
    L"US-Englisch verwendet. Widget-Sprache, Glättung und Designs gelten nur für dieses Widget. "
    L"\r\n\r\nDas Widget-Menü enthält die "
    L"zutreffenden Optionen für Sichtbarkeit, Vordergrund, Sekunden, Größe und Datumskopie sowie Im "
    L"Raster anordnen, Einstellungen, Hilfe, Info und Beenden. Das Infobereichsmenü listet "
    L"nummerierte Widgets und bietet Alle anzeigen, Alle ausblenden und Alles stummschalten. Im "
    L"Raster anordnen folgt als getrennte Gruppe. Anzeigen oder Wiederherstellen bringt Widgets nach "
    L"vorn, ohne Immer im Vordergrund zu ändern. Ein erneuter Start aktiviert die laufende Instanz "
    L"und stellt bei Bedarf die zuletzt verborgenen Widgets wieder her. Verfügbare Zifferblattgrößen "
    L"und Sekundenzeiger hängen von der installierten Windows-Version ab"
    L". "
    L"Wecker und Zeitzeichen lassen sich direkt im Widget-Menü schalten; Wecker zeigt Zeit und bei "
    L"einer Teilwoche die aktiven Tage. Stummschalten im Widget-Menü entspricht Stummgeschaltet unter "
    L"Allgemein. Alles stummschalten im Infobereich stellt beim nächsten Umschalten nur die von ihm "
    L"stummgeschalteten Widgets wieder her. M auf einem Widget schaltet denselben Gesamtzustand um. "
    L"Wird ein Wecker ohne ausgewählten Wochentag aktiviert, öffnet sich die Registerkarte Wecker "
    L"dieses Widgets.",
    L"\r\n\r\nPARAMÈTRES ET MENUS\r\nLangue, police, lissage, thèmes, stockage, démarrage avec Windows et "
    L"accrochage sont globaux et se règlent dans l’onglet Application. Au premier lancement, la langue suit "
    L"celle de l’interface Windows, avec l’anglais américain par défaut ; langue, lissage et thèmes du widget "
    L"ne concernent que lui. \r\n\r\nLe "
    L"menu d’un widget contient les choix applicables de visibilité, premier plan, secondes, taille et copie "
    L"de date, puis Aligner sur une grille, Paramètres, Aide, À propos et Quitter. Le menu de notification "
    L"liste les widgets numérotés et propose Tout afficher, Tout masquer et Couper tous les sons. Aligner sur "
    L"une grille suit dans un groupe séparé. Afficher ou restaurer les widgets les ramène devant sans modifier"
    L" Toujours visible. Un nouveau lancement active l’instance existante et restaure au besoin les "
    L"derniers widgets masqués. Les tailles de cadran et la trotteuse disponibles viennent de la version de "
    L"Windows installée"
    L". Alarme et Signal se commutent dans le menu du widget ; Alarme affiche l’heure et, pour une "
    L"semaine partielle, les jours actifs. Couper le son dans le menu du widget correspond à Son coupé dans "
    L"Général. Tout couper rétablit ensuite uniquement les widgets qu’il a coupés. M sur un widget effectue la"
    L" même bascule globale. Activer l’alarme sans jour sélectionné ouvre l’onglet Alarme de ce widget.",
    L"\r\n\r\nCONFIGURACIÓN Y MENÚS\r\nIdioma, fuente, suavizado, temas, almacenamiento, inicio con Windows y "
    L"acoplamiento son globales y se configuran en la pestaña Aplicación. En el primer inicio, el idioma sigue"
    L" al de la interfaz de Windows y usa inglés de EE. UU. como alternativa; idioma, suavizado y temas del "
    L"widget solo afectan a este. \r\n\r\nEl"
    L" menú del widget contiene las opciones aplicables de visibilidad, primer plano, segundos, tamaño y copia"
    L" de fecha, además de Alinear en cuadrícula, Configuración, Ayuda, Acerca de y Salir. El menú del icono "
    L"muestra widgets numerados y ofrece Mostrar todo, Ocultar todo y Silenciar todo. Alinear en cuadrícula "
    L"aparece después como grupo separado. Mostrar o restaurar lleva los widgets al frente sin cambiar Siempre"
    L" visible. Otra ejecución activa la instancia existente y restaura cuando haga falta los últimos widgets "
    L"ocultos. Los tamaños de esfera y la disponibilidad del segundero proceden de la versión de Windows "
    L"instalada"
    L". Alarma y Señal se conmutan en el menú del widget; Alarma muestra la hora y, "
    L"para una semana parcial, los días activos. Silenciar en el menú del widget corresponde a Silenciado en "
    L"General. Silenciar todo restaura después solo los widgets que silenció. M sobre un widget realiza la "
    L"misma conmutación global. Activar la alarma sin ningún día seleccionado abre la pestaña Alarma de ese "
    L"widget.",
    L"\r\n\r\nIMPOSTAZIONI E MENU\r\nLingua, carattere, antialiasing, temi, archivio, avvio con Windows e "
    L"aggancio sono globali e si configurano nella scheda Applicazione. Al primo avvio la lingua segue quella "
    L"dell’interfaccia di Windows, con inglese USA come ripiego; lingua, antialiasing e temi del widget "
    L"valgono solo per esso. \r\n\r\nIl "
    L"menu del widget contiene le scelte pertinenti per visibilità, primo piano, secondi, dimensione e copia "
    L"della data, oltre a Disponi in griglia, Impostazioni, Guida, Informazioni ed Esci. Il menu dell’icona "
    L"elenca i widget numerati e offre Mostra tutto, Nascondi tutto e Disattiva tutto l'audio. Disponi in "
    L"griglia segue come gruppo separato. Mostrare o ripristinare porta i widget davanti senza cambiare Sempre"
    L" in primo piano. Un nuovo avvio attiva l’istanza esistente e, se necessario, ripristina gli ultimi "
    L"widget nascosti. Dimensioni del quadrante e lancetta dei secondi disponibili dipendono dalla versione di"
    L" Windows installata"
    L". Sveglia e Segnale si attivano dal menu del widget; Sveglia mostra l’ora e, per "
    L"una settimana parziale, i giorni attivi. Disattiva audio nel menu del widget corrisponde ad Audio "
    L"disattivato in Generali. Disattiva tutto ripristina poi solo i widget che aveva disattivato. M su un "
    L"widget esegue lo stesso comando globale. Attivare la sveglia senza giorni selezionati apre la scheda "
    L"Sveglia del widget.",
    L"\r\n\r\nUSTAWIENIA I MENU\r\nJęzyk, czcionka, wygładzanie, motywy, magazyn ustawień, uruchamianie z "
    L"Windows i przyciąganie są globalne i ustawia się je na karcie Aplikacja. Przy pierwszym "
    L"uruchomieniu język wynika z języka interfejsu Windows, a nieznany zastępuje angielski (USA); "
    L"język, wygładzanie i motywy widżetu dotyczą tylko jego. "
    L"\r\n\r\nMenu widżetu zawiera odpowiednie opcje widoczności, położenia na "
    L"wierzchu, sekund, rozmiaru i kopiowania daty oraz Ułóż w siatce, Ustawienia, Pomoc, O programie "
    L"i Zakończ. Menu ikony wyświetla numerowane widżety oraz Pokaż wszystkie, Ukryj wszystkie i "
    L"Wycisz wszystko. Ułóż w siatce znajduje się dalej w oddzielnej grupie. Pokazanie lub "
    L"przywrócenie przenosi widżety do przodu bez zmiany Zawsze na wierzchu. Ponowne uruchomienie "
    L"aktywuje istniejącą instancję i w razie potrzeby przywraca ostatnio ukryte widżety. Dostępne "
    L"rozmiary tarczy i sekundnik zależą od zainstalowanej wersji Windows"
    L". Alarm i Sygnał można "
    L"przełączać w menu widżetu; Alarm pokazuje czas i, dla części tygodnia, aktywne dni. Wycisz w "
    L"menu widżetu odpowiada opcji Wyciszony na karcie Ogólne. Wycisz wszystko przywraca potem tylko "
    L"widżety, które samo wyciszyło. M na widżecie wykonuje to samo przełączenie globalne. Włączenie "
    L"alarmu bez wybranego dnia otwiera kartę Alarm tego widżetu.",
    L"\r\n\r\nNASTAVENIA A PONUKY\r\nJazyk, písmo, vyhladzovanie, motívy, úložisko, spúšťanie s Windows a "
    L"prichytávanie sú globálne a nastavujú sa na karte Aplikácia. Pri prvom spustení sa jazyk volí "
    L"podľa jazyka rozhrania Windows, neznámy jazyk sa nahradí angličtinou (USA); jazyk, "
    L"vyhladzovanie a motívy widgetu platia iba preň. "
    L"\r\n\r\nPonuka widgetu obsahuje príslušné voľby viditeľnosti, režimu navrchu, sekúnd, veľkosti "
    L"a kopírovania dátumu a ďalej Zarovnať do mriežky, Nastavenia, Pomoc, O programe a Koniec. "
    L"Ponuka ikony uvádza očíslované widgety a príkazy Zobraziť všetko, Skryť všetko a Stlmiť všetko. "
    L"Samostatne oddelený príkaz Zarovnať do mriežky nasleduje za nimi. Zobrazenie alebo obnovenie "
    L"prenesie widgety dopredu bez zmeny Vždy navrchu. Ďalšie spustenie aktivuje bežiacu inštanciu a "
    L"podľa potreby obnoví naposledy skryté widgety. Dostupné rozmery ciferníka a sekundová ručička "
    L"vychádzajú z možností používanej verzie Windows"
    L". Budík a Signál možno prepínať v ponuke widgetu; "
    L"Budík ukazuje čas a pri čiastočnom týždni aj aktívne dni. Stlmiť v ponuke widgetu zodpovedá "
    L"voľbe Stlmené na karte Všeobecné. Stlmiť všetko potom obnoví iba widgety, ktoré samo stlmilo. "
    L"Kláves M na widgete vykoná rovnaké globálne prepnutie. Zapnutie budíka bez vybraného dňa otvorí "
    L"kartu Budík daného widgetu.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nApplication language, font, smoothing, themes, storage, Windows startup "
    L"and edge snapping are global and are configured on the Application tab. On first launch, the "
    L"application language follows the Windows user-interface language, with US English as the "
    L"fallback; widget language, smoothing and themes affect that widget only. "
    L"\r\n\r\nA widget menu contains the applicable visibility, "
    L"always-on-top, seconds, size and date-copy choices, followed by Arrange in a grid, Settings, "
    L"Help, About and Exit. The notification-icon menu lists numbered widgets and provides Show all, "
    L"Hide all and Mute all. The separately grouped Arrange in a grid command follows. Showing or "
    L"restoring widgets brings them forward without changing Always on top. Starting CalClock again "
    L"activates the running instance and restores the most recently hidden widgets when needed. "
    L"Available face sizes and second-hand support come from the installed Windows version"
    L". Alarm and "
    L"Signal can be toggled directly in a widget menu; Alarm shows its time and, for a partial week, "
    L"its active weekdays. Checked Mute in a widget menu corresponds to Muted on the General tab. "
    L"Mute all in the notification-icon menu mutes every widget and, when toggled again, restores "
    L"only those it muted. Pressing M on any widget performs the same global toggle. Enabling an "
    L"alarm with no weekday selected opens that widget’s Alarm tab.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nApplication language, font, smoothing, themes, storage, Windows startup "
    L"and edge snapping are global and are configured on the Application tab. On first launch, the "
    L"application language follows the Windows user-interface language, with US English as the "
    L"fallback; widget language, smoothing and themes affect that widget only. "
    L"\r\n\r\nA widget menu contains the applicable visibility, "
    L"always-on-top, seconds, size and date-copy choices, followed by Arrange in a grid, Settings, "
    L"Help, About and Exit. The notification-icon menu lists numbered widgets and provides Show all, "
    L"Hide all and Mute all. The separately grouped Arrange in a grid command follows. Showing or "
    L"restoring widgets brings them forward without changing Always on top. Starting CalClock again "
    L"activates the running instance and restores the most recently hidden widgets when needed. "
    L"Available face sizes and second-hand support come from the installed Windows version"
    L". Alarm and "
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
    L"etkinleştirmek aracın Alarm sekmesini açar.",
    L"\r\n\r\nSätted ja menüüd\r\nRakenduse keel, font, silumine, kujundused, salvestuskoht, Windowsiga "
    L"käivitamine ja servatõmme on ühised sätted vahekaardil Rakendus. Esmakäivitamisel kasutatakse Windowsi "
    L"kasutajaliidese keelt või selle puudumisel USA inglise keelt. Vidina keel, silumine ja kujundused "
    L"mõjutavad vaid seda vidinat. \r\n\r\nVidina "
    L"menüüs on selle tüübile sobivad nähtavuse, esiplaanil hoidmise, sekundite, suuruse ja kuupäeva "
    L"kopeerimise valikud, seejärel Paiguta ruudustikku, Sätted, Spikker, Teave ja Välju. Olekuala menüü "
    L"loetleb nummerdatud vidinad, Kuva kõik, Peida kõik ja Vaigista kõik ning eraldi ruudustikukäsu. Kuvamine"
    L" või taastamine toob vidina ette suvandit Alati pealmine muutmata. Korduskäivitus taastab vajaduse "
    L"korral viimati peidetud vidinad. Sihverplaadisuurused ja sekundiosuti tugi sõltuvad Windowsist"
    L". Äratus ja Signaal on lülitatavad ka menüüs, kus kuvatakse"
    L" aeg, intervall ning osalise nädala korral aktiivsed päevad. Vaigista vastab vahekaardi Üldine valikule "
    L"Vaigistatud. Vaigista kõik ja klahv M vaigistavad kõik vidinad ning järgmisel korral taastavad heli "
    L"ainult neil, mille nad ise vaigistasid. Päevadeta äratuse lubamine avab vahekaardi Äratus.",
    L"\r\n\r\nSocruithe agus roghchláir\r\nIs socruithe comhroinnte ar an gcluaisín Feidhmchlár iad an teanga,"
    L" cló, frithailiasáil, téamaí, stóras, tosú le Windows agus léim chuig imill. Ar an gcéad tosú, "
    L"roghnaítear teanga chomhéadan Windows nó Béarla SAM mura dtacaítear léi. Ní bhaineann teanga, "
    L"frithailiasáil agus téamaí giuirléide ach léi féin. "
    L"\r\n\r\nTaispeánann roghchlár giuirléide na roghanna infheictheachta, Ar barr i"
    L" gcónaí, soicindí, méid agus cóipeáil dáta a bhaineann léi, agus ansin Eagraigh in eangach, Socruithe, "
    L"Cabhair, Maidir leis agus Scoir. Liostaíonn an roghchlár fógraí giuirléidí uimhrithe agus Taispeáin "
    L"uile, Folaigh uile agus Balbhaigh uile, agus an t-ordú eangaí i ngrúpa ar leith. Tugann taispeáint nó "
    L"athchóiriú giuirléid chun tosaigh gan Ar barr i gcónaí a athrú. Má sheoltar CalClock arís, "
    L"gníomhachtaítear an feidhmchlár atá ar siúl cheana agus athchóirítear na giuirléidí is déanaí a folaíodh"
    L" más gá. Braitheann méideanna aghaidhe agus tacaíocht don lámh soicindí ar Windows"
    L". Is féidir Aláram agus Comhartha a athrú sa roghchlár, a "
    L"thaispeánann am, eatramh agus na laethanta gníomhacha nuair nach bhfuil an tseachtain iomlán roghnaithe."
    L" Freagraíonn Balbhaigh do Balbhaithe ar Ginearálta. Balbhaíonn Balbhaigh uile agus M gach giuirléid; "
    L"arís, ní athchóiríonn siad ach an fhuaim a bhalbhaigh siad féin. Osclaítear Aláram má chumasaítear "
    L"aláram gan lá roghnaithe.",
    L"\r\n\r\nParametrai ir meniu\r\nProgramos kalba, šriftas, glodinimas, temos, saugykla, paleidimas su "
    L"„Windows“ ir prikabinimas yra bendri skirtuko Programa parametrai. Pirmą kartą parenkama „Windows“ "
    L"sąsajos kalba arba JAV anglų kalba, jei ji nepalaikoma. Valdiklio kalba, glodinimas ir temos taikomi tik"
    L" jam. \r\n\r\nValdiklio meniu turi jam "
    L"tinkamus matomumo, Visada viršuje, sekundžių, dydžio ir datos kopijavimo pasirinkimus, po jų – Išdėstyti"
    L" tinkleliu, Parametrai, Žinynas, Apie ir Išeiti. Piktogramos meniu pateikia numeruotus valdiklius, "
    L"Rodyti visus, Slėpti visus ir Nutildyti visus, tada atskirą tinklelio komandą. Rodant ar atkuriant "
    L"valdiklis iškeliamas į priekį nekeičiant Visada viršuje. Pakartotinis paleidimas prireikus atkuria "
    L"paskutinį kartą paslėptus valdiklius. Ciferblatų dydžiai ir sekundžių rodyklė priklauso nuo „Windows“"
    L". Žadintuvas ir Signalas perjungiami ir "
    L"meniu, kuris rodo laiką, intervalą bei pasirinktas dienas, jei pažymėta ne visa savaitė. Nutildyti "
    L"atitinka Nutildyta skirtuke Bendra. Nutildyti visus ir M nutildo visus valdiklius; pakartojus grąžinamas"
    L" garsas tik tiems, kuriuos ši komanda nutildė. Įjungus žadintuvą be pasirinktos dienos atidaromas "
    L"skirtukas Žadintuvas.",
    L"\r\n\r\nIestatījumi un izvēlnes\r\nProgrammas valoda, fonts, nogludināšana, dizaini, krātuve, palaišana "
    L"kopā ar Windows un pievilkšana ir kopīgi iestatījumi cilnē Programma. Pirmajā palaišanā izmanto Windows "
    L"saskarnes valodu vai ASV angļu valodu, ja tā netiek atbalstīta. Logrīka valoda, nogludināšana un dizaini"
    L" ietekmē tikai to. \r\n\r\nLogrīka izvēlnē ir tam "
    L"piemērotās redzamības, Vienmēr virspusē, sekunžu, lieluma un datuma kopēšanas izvēles, tad Sakārtot "
    L"režģī, Iestatījumi, Palīdzība, Par programmu un Iziet. Ikonas izvēlnē ir numurēti logrīki, Rādīt visus, "
    L"Paslēpt visus un Izslēgt visu skaņu, pēc tam atsevišķa režģa komanda. Parādīšana vai atjaunošana izvirza"
    L" logrīku priekšplānā bez Vienmēr virspusē maiņas. Atkārtota palaišana vajadzības gadījumā atjauno "
    L"pēdējos paslēptos logrīkus. Ciparnīcas un sekunžu rādītāja atbalsts atkarīgs no Windows"
    L". Modinātāju un Signālu var pārslēgt izvēlnē, kur "
    L"redzams laiks, intervāls un atlasītās dienas, ja nav atlasīta visa nedēļa. Izslēgt skaņu atbilst Skaņa "
    L"izslēgta cilnē Vispārīgi. Izslēgt visu skaņu un M izslēdz visu logrīku skaņu; atkārtoti ieslēdz tikai "
    L"to, ko šī komanda izslēgusi. Modinātāja ieslēgšana bez atlasītas dienas atver tā cilni.",
    L"\r\n\r\nBeállítások és menük\r\nA nyelv, betűtípus, élsimítás, témák, tároló, Windowszal indítás és "
    L"szélhez illesztés közös beállítás az Alkalmazás fülön. Első indításkor a Windows felületének nyelve, nem"
    L" támogatott nyelvnél az amerikai angol lesz aktív. A minialkalmazás nyelve, élsimítása és témái csak "
    L"arra érvényesek. \r\n\r\nA "
    L"minialkalmazás menüje az alkalmazható láthatóság-, Mindig felül-, másodperc-, méret- és dátummásolási "
    L"választásokat, majd a Rácsba rendezés, Beállítások, Súgó, Névjegy és Kilépés parancsokat tartalmazza. Az"
    L" ikon menüje számozott minialkalmazásokat, Összes megjelenítése, Összes elrejtése és Összes némítása "
    L"parancsot, majd külön rácsparancsot ad. A megjelenítés vagy visszaállítás előtérbe hoz a Mindig felül "
    L"módosítása nélkül. Az újabb indítás szükség esetén visszahozza a legutóbb elrejtetteket. A számlapméret "
    L"és másodpercmutató a Windowstól függ. Az "
    L"Ébresztés és Időjelzés a menüből is kapcsolható; az idő, intervallum és részleges hétnél a kijelölt "
    L"napok is látszanak. A Némítás a Némítva állapotnak felel meg az Általános fülön. Az Összes némítása és "
    L"az M mindent némít, ismételve csak az általa némított hangokat állítja vissza. Nap nélküli ébresztés "
    L"engedélyezése megnyitja az Ébresztés fület.",
    L"\r\n\r\nSettings u menus\r\nIl-lingwa, il-font, l-anti-aliasing, it-temi, il-ħażna, il-bidu mal-Windows "
    L"u t-twaħħil mat-truf huma settings komuni fit-tab Applikazzjoni. Mal-ewwel tnedija tintgħażel il-lingwa "
    L"tal-interfaċċa tal-Windows jew l-Ingliż Amerikan jekk mhijiex appoġġjata. Il-lingwa, l-anti-aliasing u "
    L"t-temi tal-widget jaffettwaw biss lilu. "
    L"\r\n\r\nIl-menu tal-widget fih l-għażliet xierqa għall-viżibbiltà, Dejjem fuq nett, sekondi, daqs"
    L" u kkupjar tad-data, imbagħad Irranġa fi gradilja, Settings, Għajnuna, Dwar u Oħroġ. Il-menu tal-ikona "
    L"jelenka widgets innumerati, Uri kollox, Aħbi kollox u Iddiżattiva l-ħoss kollu, imbagħad il-kmand "
    L"tal-gradilja separat. Il-wiri jew ir-restawr iġib il-widget quddiem mingħajr ma jibdel Dejjem fuq nett. "
    L"Tnedija oħra tirrestawra l-aħħar widgets moħbija jekk meħtieġ. Id-daqsijiet u l-appoġġ għall-id "
    L"tas-sekondi jiddependu fuq Windows"
    L". Allarm u Sinjal jistgħu jinqalbu fil-menu, li juri l-ħin, l-intervall u l-jiem magħżula jekk "
    L"mhijiex magħżula l-ġimgħa kollha. Iddiżattiva l-ħoss jikkorrispondi għal Ħoss diżattivat fit-tab "
    L"Ġenerali. Iddiżattiva l-ħoss kollu u M isikktu l-widgets kollha; ir-ripetizzjoni tirrestawra biss dawk "
    L"imsikkta minn dak il-kmand. L-attivazzjoni ta’ allarm mingħajr jum magħżul tiftaħ it-tab Allarm.",
    L"\r\n\r\nInstellingen en menu’s\r\nTaal, lettertype, vereffening, thema’s, opslag, starten met Windows en"
    L" uitlijnen op randen zijn algemene instellingen op Toepassing. Bij de eerste start wordt de "
    L"Windows-weergavetaal gekozen, of Amerikaans Engels als deze niet ondersteund wordt. Widgettaal, "
    L"vereffening en thema’s gelden alleen voor die widget. "
    L"\r\n\r\nEen widgetmenu bevat toepasselijke keuzes voor zichtbaarheid, Altijd"
    L" op voorgrond, seconden, grootte en datumkopie, gevolgd door Schikken in raster, Instellingen, Help, "
    L"Info en Afsluiten. Het pictogrammenu bevat genummerde widgets, Alles weergeven, Alles verbergen en Alles"
    L" dempen, gevolgd door een afzonderlijke rasteropdracht. Tonen of herstellen brengt een widget naar voren"
    L" zonder Altijd op voorgrond te wijzigen. Opnieuw starten herstelt zo nodig de laatst verborgen widgets. "
    L"Wijzerplaatgroottes en de secondewijzer hangen van Windows af"
    L". Alarm en Signaal zijn ook in het menu te "
    L"schakelen; daar staan de tijd, het interval en bij een gedeeltelijke week de actieve dagen. Dempen komt "
    L"overeen met Gedempt op Algemeen. Alles dempen en M dempen elke widget; opnieuw schakelen herstelt alleen"
    L" wat deze opdracht zelf dempte. Een alarm inschakelen zonder gekozen dag opent het tabblad Alarm.",
    L"\r\n\r\nSetări și meniuri\r\nLimba aplicației, fontul, netezirea, temele, stocarea, pornirea cu Windows "
    L"și alinierea la margini sunt comune în fila Aplicație. La prima pornire se alege limba interfeței "
    L"Windows sau engleza americană dacă nu este acceptată. Limba, netezirea și temele widgetului afectează "
    L"numai acel widget. \r\n\r\nMeniul "
    L"widgetului conține alegerile aplicabile de vizibilitate, Întotdeauna deasupra, secunde, dimensiune și "
    L"copiere a datei, apoi Aranjare în grilă, Setări, Ajutor, Despre și Ieșire. Meniul pictogramei enumeră "
    L"widgeturile numerotate, Afișare totală, Ascundere totală și Dezactivare totală sunet, apoi comanda de "
    L"grilă separată. Afișarea sau restabilirea aduce widgetul în față fără schimbarea Întotdeauna deasupra. O"
    L" nouă pornire restabilește la nevoie ultimele widgeturi ascunse. Dimensiunile și secundarul depind de "
    L"Windows. Alarmă și Semnal se pot "
    L"comuta din meniu, care arată ora, intervalul și zilele active când nu este selectată întreaga săptămână."
    L" Dezactivare sunet corespunde cu Sunet dezactivat din General. Dezactivare totală sunet și M "
    L"dezactivează sunetul tuturor widgeturilor; repetarea îl restabilește numai celor afectate de acea "
    L"comandă. Activarea unei alarme fără zi selectată deschide fila Alarmă.",
    L"\r\n\r\nΡυθμίσεις και μενού\r\nΗ γλώσσα, η γραμματοσειρά, η εξομάλυνση, τα θέματα, η αποθήκευση, η "
    L"εκκίνηση με Windows και η προσκόλληση είναι κοινές ρυθμίσεις στην καρτέλα Εφαρμογή. Στην πρώτη εκκίνηση "
    L"επιλέγεται η γλώσσα των Windows ή τα Αγγλικά ΗΠΑ αν δεν υποστηρίζεται. Η γλώσσα, η εξομάλυνση και τα "
    L"θέματα ενός στοιχείου επηρεάζουν μόνο αυτό. "
    L"\r\n\r\nΤο μενού στοιχείου έχει τις κατάλληλες επιλογές ορατότητας, Πάντα σε πρώτο "
    L"πλάνο, δευτερολέπτων, μεγέθους και αντιγραφής ημερομηνίας και μετά Τακτοποίηση σε πλέγμα, Ρυθμίσεις, "
    L"Βοήθεια, Πληροφορίες και Έξοδος. Το μενού εικονιδίου έχει αριθμημένα στοιχεία, Εμφάνιση όλων, Απόκρυψη "
    L"όλων και Σίγαση όλων και χωριστά την εντολή πλέγματος. Η εμφάνιση ή επαναφορά φέρνει το στοιχείο μπροστά"
    L" χωρίς αλλαγή του Πάντα σε πρώτο πλάνο. Η νέα εκκίνηση επαναφέρει όσα αποκρύφτηκαν τελευταία, αν "
    L"χρειάζεται. Μεγέθη καντράν και δείκτης δευτερολέπτων εξαρτώνται από Windows"
    L". Ξυπνητήρι και Σήμα αλλάζουν και από το μενού, που δείχνει ώρα, "
    L"διάστημα και ενεργές ημέρες όταν δεν επιλέγεται ολόκληρη η εβδομάδα. Η Σίγαση αντιστοιχεί στο Σε σίγαση "
    L"στα Γενικά. Η Σίγαση όλων και το M σιγούν όλα τα στοιχεία· η επανάληψη επαναφέρει μόνο όσα σίγησε η ίδια"
    L" εντολή. Η ενεργοποίηση ξυπνητηριού χωρίς ημέρα ανοίγει την καρτέλα του.",
    L"\r\n\r\nPostavke i meniji\r\nJezik programa, font, izglađivanje, teme, spremište, pokretanje s Windowsom"
    L" i priljubljivanje uz ivice vrijede globalno i postavljaju se na kartici Program. Pri prvom pokretanju "
    L"jezik se bira prema jeziku interfejsa Windowsa; ako nije podržan, koristi se američki engleski. Jezik, "
    L"izglađivanje i teme vidžeta utječu samo na taj vidžet. "
    L"\r\n\r\nMeni vidžeta sadrži primjenjive postavke vidljivosti, načina Uvijek na vrhu, "
    L"sekundi, veličine i oblika kopiranja datuma, a zatim Rasporedi u mrežu, Postavke, Pomoć, O programu i "
    L"Izlaz. Meni ikone u području obavijesti navodi numerisane vidžete i naredbe Prikaži sve, Sakrij sve i "
    L"Isključi sav zvuk. Slijedi zasebno grupirana naredba Rasporedi u mrežu. Prikazivanje ili vraćanje "
    L"vidžeta dovodi ga naprijed bez promjene postavke Uvijek na vrhu. Ponovno pokretanje CalClocka aktivira "
    L"postojeću instancu i po potrebi vraća posljednje skrivene vidžete. Dostupne veličine brojčanika i "
    L"podrška sekundnoj kazaljci zavise od verzije Windowsa"
    L". Alarm i Signal mogu se uključiti u meniju vidžeta; Alarm "
    L"pokazuje vrijeme i, ako nisu odabrani svi dani, aktivne dane u sedmici. Označeni Isključi zvuk odgovara "
    L"opciji Zvuk isključen na kartici Općenito. Isključi sav zvuk isključuje zvuk svih vidžeta, a ponovnim "
    L"izvođenjem vraća zvuk samo onima koje je prethodno utišao. M na bilo kojem vidžetu radi isto. "
    L"Uključivanje alarma bez odabranih dana otvara njegovu karticu Alarm.",
    L"\r\n\r\nPostavke i izbornici\r\nJezik programa, font, izglađivanje, teme, spremište, pokretanje s "
    L"Windowsom i priljubljivanje uz rubove vrijede globalno i postavljaju se na kartici Program. Pri prvom "
    L"pokretanju jezik se bira prema jeziku sučelja Windowsa; ako nije podržan, koristi se američki engleski. "
    L"Jezik, izglađivanje i teme widgeta utječu samo na taj widget. "
    L"\r\n\r\nIzbornik widgeta sadrži primjenjive postavke vidljivosti, načina "
    L"Uvijek na vrhu, sekundi, veličine i oblika kopiranja datuma, a zatim Rasporedi u mrežu, Postavke, Pomoć,"
    L" O programu i Izlaz. Izbornik ikone u području obavijesti navodi numerirane widgete i naredbe Prikaži "
    L"sve, Sakrij sve i Isključi sav zvuk. Slijedi zasebno grupirana naredba Rasporedi u mrežu. Prikazivanje "
    L"ili vraćanje widgeta dovodi ga naprijed bez promjene postavke Uvijek na vrhu. Ponovno pokretanje "
    L"CalClocka aktivira postojeću instancu i po potrebi vraća posljednje skrivene widgete. Dostupne veličine "
    L"brojčanika i podrška sekundnoj kazaljci ovise o verziji Windowsa. "
    L"Alarm i Signal mogu se uključiti u "
    L"izborniku widgeta; Alarm pokazuje vrijeme i, ako nisu odabrani svi dani, aktivne dane u tjednu. Označeni"
    L" Isključi zvuk odgovara opciji Zvuk isključen na kartici Općenito. Isključi sav zvuk isključuje zvuk "
    L"svih widgeta, a ponovnim izvođenjem vraća zvuk samo onima koje je prethodno utišao. M na bilo kojem "
    L"widgetu radi isto. Uključivanje alarma bez odabranih dana otvara njegovu karticu Alarm.",
    L"\r\n\r\nNastavitve in meniji\r\nJezik, pisava, glajenje, teme, shramba, zagon z Windows in pripenjanje "
    L"so skupne nastavitve na zavihku Program. Ob prvem zagonu se jezik izbere po jeziku vmesnika Windows; če "
    L"ni podprt, se uporabi ameriška angleščina. Jezik, glajenje in teme gradnika vplivajo samo nanj. "
    L"\r\n\r\nMeni gradnika vsebuje ustrezne izbire "
    L"vidnosti, Vedno na vrhu, sekund, velikosti in kopiranja datuma, nato Razporedi v mrežo, Nastavitve, "
    L"Pomoč, O programu in Izhod. Meni ikone vsebuje oštevilčene gradnike ter Pokaži vse, Skrij vse in Izklopi"
    L" ves zvok; sledi ločeni ukaz Razporedi v mrežo. Prikaz ali obnova postavi gradnik v ospredje brez "
    L"spremembe Vedno na vrhu. Ponovni zagon aktivira obstoječi primerek in po potrebi obnovi nazadnje skrite "
    L"gradnike. Velikosti številčnic in podpora sekundnemu kazalcu so odvisne od Windows. "
    L"Budilko in Signal lahko preklopite v "
    L"meniju; budilka kaže čas in pri delnem tednu izbrane dneve. Označeni Izklopi zvok ustreza možnosti Zvok "
    L"izklopljen na zavihku Splošno. Izklopi ves zvok utiša vse gradnike, ob ponovitvi pa obnovi zvok samo "
    L"tistim, ki jih je sam utišal. Tipka M na katerem koli gradniku naredi isto. Vklop budilke brez izbranega"
    L" dneva odpre njen zavihek Budilka.",
    L"\r\n\r\nPodešavanja i meniji\r\nJezik programa, font, umekšavanje, teme, skladište, pokretanje uz "
    L"Windows i priljepljivanje su zajedničke postavke na kartici Program. Pri prvom pokretanju bira se jezik "
    L"interfejsa Windows-a; ako nije podržan, koristi se američki engleski. Jezik, umekšavanje i teme vidžeta "
    L"utiču samo na njega. \r\n\r\nMeni vidžeta sadrži "
    L"primjenjive postavke vidljivosti, Uvijek na vrhu, sekundi, veličine i kopiranja datuma, zatim Rasporedi "
    L"u mrežu, Podešavanja, Pomoć, O programu i Izlaz. Meni ikone navodi numerisane vidžete, Prikaži sve, "
    L"Sakrij sve i Isključi sav zvuk, pa odvojeno Rasporedi u mrežu. Prikaz ili vraćanje dovodi vidžet "
    L"naprijed bez promjene Uvijek na vrhu. Ponovni start aktivira postojeću instancu i po potrebi vraća "
    L"posljednje skrivene vidžete. Veličine brojčanika i sekundna kazaljka zavise od Windows-a. "
    L"Alarm i Signal prebacuju"
    L" se i iz menija; Alarm pokazuje vrijeme i aktivne dane kada nije izabrana cijela nedjelja. Označeno "
    L"Isključi zvuk odgovara opciji Zvuk isključen na kartici Opšte. Isključi sav zvuk isključuje zvuk svih "
    L"vidžeta, a ponovljena radnja vraća zvuk samo onima koje je sama isključila. M na svakom vidžetu radi "
    L"isto. Uključivanje alarma bez izabranih dana otvara njegovu karticu Alarm.",
    L"\r\n\r\nНалады і меню\r\nМова праграмы, шрыфт, згладжванне, тэмы, сховішча, запуск з Windows і прывязка "
    L"да краёў задаюцца для ўсёй праграмы на ўкладцы «Праграма». Пры першым запуску выбіраецца мова інтэрфейсу"
    L" Windows; калі яна не падтрымліваецца, выкарыстоўваецца амерыканская англійская. Мова, згладжванне і "
    L"тэмы віджэта ўплываюць толькі на яго. "
    L"\r\n\r\nМеню віджэта мае даступныя яму налады бачнасці, «Заўсёды зверху», секунд, памеру і "
    L"капіявання даты, далей — «Упарадкаваць па сетцы», «Налады», «Даведка», «Пра праграму» і «Выйсці». Меню "
    L"значка змяшчае нумараваныя віджэты ды «Паказаць усё», «Схаваць усё» і «Выключыць увесь гук», затым "
    L"асобна — «Упарадкаваць па сетцы». Паказ ці аднаўленне выводзіць віджэт наперад без змены «Заўсёды "
    L"зверху». Паўторны запуск актывуе існы асобнік і пры патрэбе аднаўляе апошнія схаваныя віджэты. Памеры "
    L"цыферблата і секундная стрэлка залежаць ад версіі Windows. "
    L"Будзільнік і сігнал пераключаюцца і ў меню; будзільнік "
    L"паказвае час і выбраныя дні, калі выбраны не ўвесь тыдзень. Пазначанае «Выключыць гук» адпавядае «Без "
    L"гуку» на ўкладцы «Агульныя». «Выключыць увесь гук» выключае гук усіх віджэтаў, а паўтор аднаўляе яго "
    L"толькі ў тых, якія гэтая каманда адключыла. M на любым віджэце робіць тое самае. Уключэнне будзільніка "
    L"без выбраных дзён адкрывае яго ўкладку «Будзільнік».",
    L"\r\n\r\nНастройки и менюта\r\nЕзикът, шрифтът, изглаждането, темите, хранилището, стартирането с Windows"
    L" и прилепването са общи настройки в раздела „Програма“. При първо стартиране се избира езикът на "
    L"интерфейса на Windows; ако не се поддържа, се използва американски английски. Езикът, изглаждането и "
    L"темите на модула влияят само на него. "
    L"\r\n\r\nМенюто на модул съдържа приложимите настройки за видимост, „Винаги отгоре“, секунди, "
    L"размер и копиране на дата, следвани от „Подреди в мрежа“, „Настройки“, „Помощ“, „За програмата“ и "
    L"„Изход“. Менюто на иконата изброява номерирани модули и „Покажи всички“, „Скрий всички“, „Изключи целия "
    L"звук“, след което отделно е „Подреди в мрежа“. Показването или възстановяването извежда модула отпред "
    L"без промяна на „Винаги отгоре“. Повторният старт активира работещия екземпляр и при нужда възстановява "
    L"последно скритите модули. Размерите на циферблата и секундната стрелка зависят от Windows. А"
    L"лармата и "
    L"сигналът се превключват и от менюто; алармата показва часа и избраните дни, ако не е избрана цялата "
    L"седмица. Отметнатото „Изключи звука“ съответства на „Без звук“ в раздела „Общи“. „Изключи целия звук“ "
    L"изключва звука на всички модули, а повторението възстановява само тези, които тази команда е изключила. "
    L"M върху всеки модул прави същото. Включването на аларма без избрани дни отваря нейния раздел „Аларма“.",
    L"\r\n\r\nПоставки и менија\r\nЈазикот, фонтот, измазнувањето, темите, складиштето, стартувањето со "
    L"Windows и прилепувањето се општи поставки на картичката „Програма“. При првото стартување се избира "
    L"јазикот на интерфејсот на Windows; ако не е поддржан, се користи американски англиски. Јазикот, "
    L"измазнувањето и темите на виџетот влијаат само на него. "
    L"\r\n\r\nМенито на виџетот содржи достапни поставки за видливост, „Секогаш најгоре“, "
    L"секунди, големина и копирање датум, потоа „Распореди во мрежа“, „Поставки“, „Помош“, „За програмата“ и "
    L"„Излез“. Менито на иконата ги наведува нумерираните виџети, „Прикажи ги сите“, „Скриј ги сите“ и "
    L"„Исклучи го целиот звук“, па одделно „Распореди во мрежа“. Покажувањето или враќањето го носи виџетот "
    L"напред без промена на „Секогаш најгоре“. Повторниот старт го активира постојниот примерок и по потреба "
    L"ги враќа последно скриените виџети. Големините на бројчаникот и секундната стрелка зависат од Windows. "
    L"А"
    L"лармот и сигналот се менуваат и од менито; алармот ги покажува времето и избраните денови кога не е "
    L"избрана целата недела. Означеното „Исклучи го звукот“ одговара на „Без звук“ во „Општо“. „Исклучи го "
    L"целиот звук“ го исклучува звукот на сите виџети, а повторувањето го враќа само кај оние што ги исклучила"
    L" оваа команда. M на кој било виџет го прави истото. Вклучувањето аларм без избрани денови ја отвора "
    L"неговата картичка „Аларм“.",
    L"\r\n\r\nПодешавања и менији\r\nЈезик програма, фонт, умекшавање, теме, складиште, покретање уз Windows и"
    L" прилепљивање су заједничке поставке на картици Програм. При првом покретању бира се језик интерфејса "
    L"Windows-а; ако није подржан, користи се амерички енглески. Језик, умекшавање и теме виџета утичу само на"
    L" њега. \r\n\r\nМени виџета садржи примењиве поставке "
    L"видљивости, Увек на врху, секунди, величине и копирања датума, затим Распореди у мрежу, Подешавања, "
    L"Помоћ, О програму и Излаз. Мени иконе наводи нумерисане виџете, Прикажи све, Сакриј све и Искључи сав "
    L"звук, па одвојено Распореди у мрежу. Приказ или враћање доводи виџет напред без промене Увек на врху. "
    L"Поновни старт активира постојећу инстанцу и по потреби враћа последње скривене виџете. Величине "
    L"бројчаника и секундна казаљка зависе од Windows-а. "
    L"Аларм и Сигнал пребацују се и из менија; Аларм показује време и "
    L"активне дане када није изабрана цела недеља. Означено Искључи звук одговара опцији Звук искључен на "
    L"картици Опште. Искључи сав звук искључује звук свих виџета, а поновљена радња враћа звук само онима које"
    L" је сама искључила. M на сваком виџету ради исто. Укључивање аларма без изабраних дана отвара његову "
    L"картицу Аларм.",
    L"\r\n\r\nНАЛАШТУВАННЯ ТА МЕНЮ\r\nМова програми, шрифт, згладжування, теми, сховище, запуск разом із "
    L"Windows і прив’язка до країв задаються для всієї програми на вкладці «Програма». Під час першого запуску "
    L"мова вибирається за мовою інтерфейсу Windows; якщо вона не підтримується, використовується англійська "
    L"(США). Мова, згладжування та теми віджета впливають лише на нього. "
    L"\r\n\r\nМеню віджета містить доступні для нього команди видимості, режиму "
    L"«Завжди зверху», секунд, розміру та формату копіювання дати, а далі — «Упорядкувати за сіткою», "
    L"«Налаштування», «Довідка», «Про програму» та «Вийти». Меню піктограми в області сповіщень містить "
    L"нумерований список віджетів і команди «Показати все», «Приховати все» та «Вимкнути весь звук». Далі "
    L"окремо розташовано команду «Упорядкувати за сіткою». Показ або відновлення віджета виводить його на "
    L"передній план без зміни режиму «Завжди зверху». Повторний запуск CalClock активує вже запущений примірник"
    L" і за потреби відновлює останні приховані віджети. Доступні розміри циферблата та підтримка секундної "
    L"стрілки залежать від установленої версії Windows. "
    L"Будильник і сигнал можна "
    L"перемикати безпосередньо в меню віджета; пункт будильника показує час і, якщо вибрано не весь тиждень, "
    L"активні дні. Позначена команда «Вимкнути звук» відповідає прапорцю «Без звуку» на вкладці «Загальні». "
    L"«Вимкнути весь звук» вимикає звук усіх віджетів, а повторне виконання відновлює звук лише тих, які ця "
    L"команда вимкнула. Клавіша M на будь-якому віджеті виконує те саме перемикання. Якщо ввімкнути будильник "
    L"без вибраних днів тижня, відкривається його вкладка «Будильник».",
    L"\r\n\r\nНАСТРОЙКИ И МЕНЮ\r\nЯзык программы, шрифт, сглаживание, темы, хранилище, запуск вместе с Windows "
    L"и привязка к краям задаются для всей программы на вкладке «Программа». При первом запуске язык выбирается"
    L" по языку интерфейса Windows; если он не поддерживается, используется английский (США). Язык, сглаживание"
    L" и темы виджета влияют только на него. "
    L"\r\n\r\nМеню виджета содержит доступные для него команды видимости, режима «Поверх всех окон», "
    L"секунд, размера и формата копирования даты, а затем — «Упорядочить по сетке», «Настройки», «Справка», «О "
    L"программе» и «Выход». Меню значка в области уведомлений содержит нумерованный список виджетов и команды "
    L"«Показать всё», «Скрыть всё» и «Выключить весь звук». Далее отдельно расположена команда «Упорядочить по "
    L"сетке». Показ или восстановление виджета выводит его на передний план без изменения режима «Поверх всех "
    L"окон». Повторный запуск CalClock активирует уже запущенный экземпляр и при необходимости восстанавливает "
    L"последние скрытые виджеты. Доступные размеры циферблата и поддержка секундной стрелки зависят от "
    L"установленной версии Windows. "
    L"Будильник и сигнал можно переключать "
    L"непосредственно в меню виджета; пункт будильника показывает время и, если выбрана не вся неделя, активные"
    L" дни. Отмеченная команда «Выключить звук» соответствует флажку «Без звука» на вкладке «Общие». «Выключить"
    L" весь звук» отключает звук всех виджетов, а повторное выполнение восстанавливает звук только тех, у "
    L"которых эта команда его отключила. Клавиша M на любом виджете выполняет то же переключение. Если включить"
    L" будильник без выбранных дней недели, открывается его вкладка «Будильник»."
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
    L"budík, časové znamení ani ztlumení"
    L".\r\n\r\nPři intervalu 20 minut znamení zazní v :00, :20 a :40 podle času widgetu.\r\n\r\nNa "
    L"kartě Aplikace lze ve volbě Zvuk časového znamení vybrat Vlastní generátor nebo Systémové "
    L"pípání. Volba platí pro časová znamení všech widgetů včetně znamení budíku. Výchozí je Vlastní "
    L"generátor.\r\n\r\nJezdec Hlasitost časového znamení na kartě Aplikace zobrazuje úroveň vlastního "
    L"generátoru v dB. Pravý doraz je 0 dB, tedy maximální nezkreslená amplituda sinusovky; úplné "
    L"ztišení je −∞ dB. Výchozí hlasitost je −18 dB. Tlačítko Vyzkoušet vedle volby Zvuk časového "
    L"znamení zapne stálou ukázku, Zastavit test ji ukončí. Otestovat lze oba druhy zvuku; test se "
    L"neukládá. Ukázka zní také po dobu držení jezdce myší; po uvolnění skončí, pokud neběží test "
    L"zapnutý tlačítkem. Začne až na následující celé sekundě, krátce každou sekundu a dlouze v :00, "
    L":05, :10 atd. Souběžná ukázka a časová znamení widgetů či budíků zaznějí jako jediný tón. P"
    L"ři zastavení testu právě rozehraný píp "
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
    L"standalone Calendar supports neither alarms, time signals nor muting"
    L".\r\n\r\nWith a 20-minute interval, signals sound at "
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
    L"tone. Stopping the test lets the current "
    L"pip finish; a long pip can take up to half a second to end. Widget offsets also apply in "
    L"hundredths of a second. Overlapping widget, alarm, and test tones play as one continuous tone "
    L"until the last overlap ends.",
    L"\r\n\r\nAKUSTISCHES ZEITZEICHEN\r\nDas Signal entspricht dem Greenwich Time Signal (GTS). Auf der "
    L"Registerkarte Zeitzeichen gibt es das Kontrollkästchen Zeitzeichen aktiv und Optionsfelder für "
    L"Intervalle von 1, 5, 10, 15, 20, 30 oder 60 Minuten gemäß der angezeigten Widget-Zeit. Anfangs ist das "
    L"Signal ausgeschaltet und das Stundenintervall ausgewählt. Aus- und Einschalten über Zeitzeichen im "
    L"Widget-Menü behält das Intervall bei. Das Menü zeigt die Weckzeit und das Signalintervall in Klammern. "
    L"Die Grenze folgt der Zeit dieses Widgets einschließlich UTC, Zeitzone, Offset und einer möglichen "
    L"NTP-Korrektur. In den letzten fünf Sekunden erklingen fünf kurze Töne und genau an der Grenze ein langer"
    L" Ton. Fallen Signale mehrerer Widgets auf denselben Zeitpunkt, wird nur eine gemeinsame Folge "
    L"wiedergegeben. Beim Stummschalten darf ein bereits klingender Ton enden; weitere Töne werden bis zum "
    L"nächsten geplanten Ton nach dem Aufheben übersprungen. Ein einzelner Kalender unterstützt weder Wecker "
    L"noch Zeitzeichen oder Stummschaltung"
    L".\r\n\r\nBeim 20-Minuten-Intervall ertönt das Zeitzeichen um :00, :20 und :40 gemäß der "
    L"Widget-Zeit.\r\n\r\nAuf der Registerkarte Anwendung können Sie unter Klang des Zeitzeichens zwischen "
    L"Interner Generator und Systemsignalton wählen. Die Auswahl gilt für die Zeitzeichen aller Widgets "
    L"einschließlich der Zeitzeichen des Weckers. Standardmäßig ist Interner Generator ausgewählt.\r\n\r\nDer "
    L"Lautstärkeregler für das Zeitzeichen auf der Registerkarte Anwendung zeigt den Pegel des eingebauten "
    L"Generators in dB. Der rechte Anschlag entspricht 0 dB, der maximalen unverzerrten Sinusamplitude; Stille"
    L" entspricht −∞ dB. Die Standardlautstärke beträgt −18 dB. Mit Testen neben Klang des Zeitzeichens "
    L"starten Sie eine fortlaufende Vorschau, mit Test stoppen beenden Sie sie. Beide Klangarten lassen sich "
    L"testen; der Test wird nicht gespeichert. Auch das Festhalten des Lautstärkereglers startet eine Vorschau"
    L" bis zum Loslassen, sofern der Tastentest nicht läuft. Die Wiedergabe beginnt zur nächsten vollen "
    L"Sekunde: kurze Töne jede Sekunde und ein langer bei :00, :05, :10 usw. Gleichzeitige Signale von "
    L"Vorschau, Widgets und Alarmen werden zu einem Ton zusammengefasst. Beim S"
    L"toppen des Tests klingt der aktuelle Ton aus; ein langer Ton kann "
    L"noch bis zu einer halben Sekunde dauern. Widget-Versätze gelten auch in Hundertstelsekunden. "
    L"Überlappende Töne von Widgets, Weckern und Tests erklingen als ein durchgehender Ton bis zum Ende der "
    L"letzten Überlappung.",
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
    L"Calendrier autonome ne propose ni alarme, ni signal horaire, ni coupure du son"
    L".\r\n\r\nAvec un intervalle de 20 minutes, "
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
    L"de l’aperçu, des widgets et des alarmes produisent un seul son. "
    L"À l’arrêt du test, le son en cours se termine ; un son long peut "
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
    L"independiente no admite alarma, señal horaria ni silencio"
    L".\r\n\r\nCon un intervalo de 20 minutos, la señal suena a :00, "
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
    L"alarmas se combinan en un solo tono. "
    L"Al detener la prueba, el tono actual termina; un tono largo puede tardar hasta medio "
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
    L"supporta sveglia, segnale orario o disattivazione audio"
    L".\r\n\r\nCon un intervallo di 20 minuti, il segnale suona a :00, :20 e :40 "
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
    L":10 ecc. I segnali simultanei di prova, widget e sveglie vengono uniti in un solo tono. "
    L"Quando si interrompe la "
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
    L"sygnał. Samodzielny Kalendarz nie obsługuje alarmu, sygnału czasu ani wyciszenia"
    L".\r\n\r\nPrzy odstępie 20 minut sygnał rozlega się o "
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
    L"są łączone w jeden dźwięk. Po "
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
    L"naplánovaný tón. Samostatný Kalendár nepodporuje budík, časové znamenie ani stlmenie"
    L".\r\n\r\nPri intervale 20 minút znamenie zaznie v :00, :20 "
    L"a :40 podľa času widgetu.\r\n\r\nNa karte Aplikácia možno vo voľbe Zvuk časového znamenia vybrať "
    L"Vlastný generátor alebo Systémové pípanie. Voľba platí pre časové znamenia všetkých widgetov "
    L"vrátane znamení budíka. Predvolený je Vlastný generátor.\r\n\r\nJazdec Hlasitosť časového znamenia "
    L"na karte Aplikácia zobrazuje úroveň vlastného generátora v dB. Pravý doraz je 0 dB, teda "
    L"maximálna neskreslená amplitúda sínusovky; úplné stíšenie je −∞ dB. Predvolená hlasitosť je −18 "
    L"dB. Tlačidlo Vyskúšať vedľa voľby Zvuk časového znamenia zapne stálu ukážku, Zastaviť test ju "
    L"ukončí. Otestovať možno oba druhy zvuku; test sa neukladá. Ukážka znie aj počas držania jazdca "
    L"myšou; po uvoľnení skončí, ak nebeží test zapnutý tlačidlom. Začne až na nasledujúcej celej "
    L"sekunde, krátko každú sekundu a dlho v :00, :05, :10 atď. Súbežná ukážka a časové znamenia "
    L"widgetov či budíkov zaznejú ako jediný tón. Pr"
    L"i zastavení testu práve rozohraný tón doznie; pri dlhom tóne to môže trvať až pol "
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
    L"standalone Calendar supports neither alarms, time signals nor muting"
    L".\r\n\r\nWith a 20-minute interval, signals sound at "
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
    L"share a single tone. Stopping the test lets "
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
    L"standalone Calendar supports neither alarms, time signals nor muting"
    L".\r\n\r\nWith a 20-minute interval, signals sound at "
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
    L"share a single tone. Stopping the test lets "
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
    L"áudio. Um Calendário autónomo não suporta alarme, sinal horário nem silenciamento"
    L".\r\n\r\nCom um intervalo de 20 minutos, o "
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
    L"sinais simultâneos da pré-visualização, dos widgets e dos alarmes produzem um único som. "
    L"O gerador integrado inicia e "
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
    L"Kalender støtter ikke alarm, tidssignal eller demping"
    L".\r\n\r\nMed et intervall på 20 minutter lyder signalet ved :00, :20 og :40 "
    L"etter widgettiden.\r\n\r\nPå fanen Program kan du under Lyd for tidssignal velge mellom Innebygd "
    L"generator og Systempip. Valget gjelder tidssignaler fra alle widgeter, inkludert tidssignaler "
    L"for alarmer. Innebygd generator er standardvalget.\r\n\r\nVolumglidebryteren for tidssignalet på "
    L"fanen Program viser nivået til den innebygde generatoren i dB. Høyre endepunkt er 0 dB, "
    L"maksimal uforvrengt sinusamplitude; stillhet er −∞ dB. Standardvolumet er −18 dB. Klikk Test "
    L"ved lyden for tidssignalet for å starte kontinuerlig forhåndslytting, og Stopp test for å "
    L"avslutte. Begge lydene kan testes; testen lagres ikke. Å holde volumglidebryteren starter også "
    L"forhåndslytting til musen slippes, med mindre knapptesten kjører. Avspillingen begynner på "
    L"neste hele sekund: korte toner hvert sekund og en lang ved :00, :05, :10 osv. Samtidige "
    L"signaler fra forhåndslytting, widgeter og alarmer slås sammen til én tone. "
    L"Når testen stoppes, spilles den pågående tonen "
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
    L"stöder inte alarm, tidssignal eller tystning"
    L".\r\n\r\nMed ett intervall på 20 minuter hörs signalen vid :00, :20 och :40 enligt widgetens "
    L"tid.\r\n\r\nPå fliken Program kan du under Ljud för tidssignal välja mellan Inbyggd generator och "
    L"Systempip. Valet gäller tidssignaler från alla widgetar, inklusive tidssignaler för alarm. "
    L"Inbyggd generator är standardvalet.\r\n\r\nVolymreglaget för tidssignalen på fliken Program visar "
    L"den inbyggda generatorns nivå i dB. Höger ändläge är 0 dB, maximal sinusamplitud utan "
    L"distorsion; tystnad är −∞ dB. Standardvolymen är −18 dB. Klicka på Testa vid tidssignalens ljud "
    L"för att starta kontinuerlig förhandslyssning och på Stoppa test för att avsluta. Båda ljuden "
    L"kan testas; testet sparas inte. Att hålla volymreglaget startar också förhandslyssning tills "
    L"musen släpps, om inte knapptestet körs. Uppspelningen börjar vid nästa hela sekund: korta toner "
    L"varje sekund och en lång vid :00, :05, :10 osv. Samtidiga signaler från förhandslyssning, "
    L"widgetar och alarm slås samman till en ton. När "
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
    L"aikamerkkiä eikä mykistystä"
    L".\r\n\r\nKun väli on 20 minuuttia, aikamerkki kuuluu kohdissa :00, :20 ja :40 "
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
    L"understøtter ikke alarm, tidssignal eller dæmpning"
    L".\r\n\r\nMed et interval på 20 minutter lyder signalet ved :00, :20 og :40 "
    L"efter widgettiden.\r\n\r\nPå fanen Program kan du under Lyd for tidssignal vælge mellem Indbygget "
    L"generator og Systembip. Valget gælder tidssignaler fra alle widgets, inklusive tidssignaler for "
    L"alarmer. Indbygget generator er standardvalget.\r\n\r\nLydstyrkeskyderen for tidssignalet på fanen "
    L"Program viser den indbyggede generators niveau i dB. Højre endepunkt er 0 dB, maksimal "
    L"uforvrænget sinusamplitude; stilhed er −∞ dB. Standardlydstyrken er −18 dB. Klik på Test ved "
    L"tidssignalets lyd for at starte vedvarende prøveafspilning og på Stop test for at afslutte. "
    L"Begge lyde kan testes; testen gemmes ikke. At holde lydstyrkeskyderen starter også "
    L"prøveafspilning, indtil musen slippes, medmindre knaptesten kører. Afspilningen begynder på "
    L"næste hele sekund: korte toner hvert sekund og en lang ved :00, :05, :10 osv. Samtidige "
    L"signaler fra prøven, widgets og alarmer samles i én tone. "
    L"Når testen stoppes, afspilles den igangværende tone færdig; en lang tone kan "
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
    L"þöggun.\r\n\r\nMeð 20 mínútna "
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
    L"sameinast í einn tón. Þegar "
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
    L"zaman sinyalini veya sessize almayı destekle"
    L"mez.\r\n\r\n20 dakikalık aralıkta sinyal, aracın saatine göre :00, :20 ve :40’ta "
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
    L"eşzamanlı sinyalleri tek bir seste birleştirilir. "
    L"Test durdurulduğunda çalmakta olan ses tamamlanır; uzun sesin "
    L"bitmesi yarım saniyeye kadar sürebilir. Araç ofsetleri saniyenin yüzde biri düzeyinde de "
    L"uygulanır. Araçların, alarmların ve testlerin örtüşen tonları son örtüşme bitene kadar tek ve "
    L"kesintisiz bir ton olarak çalar.",
    L"\r\n\r\nKuuldav ajasignaal\r\nSignaal järgib Greenwichi ajasignaali (GTS): viis lühikest tooni viimase "
    L"viie sekundi jooksul ja pikk toon täpsel ajahetkel. Vahekaardil Signaal on Ajasignaal lubatud ja "
    L"intervallid 1, 5, 10, 15, 20, 30 või 60 minutit vidina kuvatava aja järgi. Vaikimisi on signaal väljas "
    L"ja valitud tunnine intervall. Menüü lülitus säilitab intervalli. Ajapiir arvestab UTC-d, ajavööndit, "
    L"nihet ja NTP-d. 20-minutilise intervalliga kõlab signaal :00, :20 ja :40. Samaaegsed vidina- ja "
    L"äratussignaalid ühendatakse. Vaigistamisel võib praegune toon lõppeda; järgmised jäetakse vahele ja heli"
    L" taastamisel kõlab alles järgmine kavandatud toon. Eraldi Kalender ei toeta äratust, ajasignaali ega "
    L"vaigistamist.\r\n\r\nVahekaardi Rakendus "
    L"Ajasignaali heli pakub Sisseehitatud generaatorit (vaikimisi) ja Süsteemi helisignaali. Valik kehtib "
    L"kõigile vidinatele ja äratustele. Ajasignaali helitugevus näitab generaatori taset dB-des: parempoolne 0"
    L" dB on suurim moonutuseta siinusamplituud, −∞ dB vaikus ja vaikesäte −18 dB. Testi käivitab pideva "
    L"prooviesituse ning Peata test lõpetab selle. Testida saab mõlemat heli; testi ei salvestata. Liuguri "
    L"hoidmine esitab samuti heli kuni hiire vabastamiseni, kui nuputest pole käimas. Esitus algab järgmisel "
    L"täissekundil: lühike toon igal sekundil ja pikk toon :00, :05, :10 jne. Kõik samaaegsed proovi-, vidina-"
    L" ja äratussignaalid jagavad ühte tooni. "
    L"Peatamine lubab praegusel toonil lõppeda; pikk toon võib kesta veel pool sekundit. Arvestatakse "
    L"ka nihke sajandikke ning kattuvad toonid kõlavad katkestuseta viimase kattumise lõpuni.",
    L"\r\n\r\nComhartha ama inchloiste\r\nLeanann an comhartha patrún Greenwich Time Signal (GTS): cúig bhíp "
    L"ghearra sna cúig shoicind dheireanacha agus bíp fhada ag an teorainn ama go beacht. Tugann Comhartha an "
    L"rogha Comhartha ama gníomhach agus eatraimh 1, 5, 10, 15, 20, 30 nó 60 nóiméad de réir am na giuirléide."
    L" Tá sé múchta ar dtús agus eatramh uair an chloig roghnaithe. Coinníonn an roghchlár an t-eatramh. "
    L"Cuirtear UTC, crios ama, fritháireamh agus NTP san áireamh; le 20 nóiméad, seinntear ag :00, :20 agus "
    L":40. Cumaisctear comharthaí comhuaineacha. Tar éis balbhaithe, féadfaidh an ton reatha críochnú; "
    L"scipeáiltear na chéad toin eile go dtí an chéad ton sceidealaithe tar éis díbhalbhaithe. Ní thacaíonn "
    L"Féilire neamhspleách le haláram, comhartha ama ná balbhú"
    L".\r\n\r\nAr Feidhmchlár, tugann Fuaim an chomhartha ama Gineadóir ionsuite (réamhshocrú) "
    L"agus Bíp an chórais do gach giuirléid agus aláram. Taispeánann Airde an chomhartha ama leibhéal an "
    L"ghineadóra in dB: is é 0 dB ar dheis an aimplitiúid síneasóideach is mó gan saobhadh, −∞ dB tost agus "
    L"−18 dB an réamhshocrú. Tosaíonn Tástáil réamhamharc leanúnach agus stopann Stop an tástáil é. Is féidir "
    L"an dá chineál fuaime a thástáil; ní shábháiltear an tástáil. Seinneann coinneáil an tsleamhnáin fuaim go"
    L" dtí go scaoiltear an luch, mura bhfuil tástáil an chnaipe ar siúl. Tosaíonn sí ar an gcéad soicind "
    L"iomlán eile: ton gearr gach soicind agus ton fada ag :00, :05, :10 agus mar sin de. Roinneann comharthaí"
    L" trialach, giuirléidí agus aláraim ton amháin. Ní dhíchumasaítear ach an sleamhnán airde do Bhíp an "
    L"chórais. Ligtear don ton reatha críochnú nuair a stoptar an tástáil; d’fhéadfadh ton fada maireachtáil "
    L"leathshoicind eile. Cuirtear céaduithe fritháirimh san áireamh agus seinntear toin fhorluiteacha go "
    L"leanúnach go deireadh an fhorluí dheireanaigh.",
    L"\r\n\r\nGarsinis laiko signalas\r\nSignalas atitinka Grinvičo laiko signalą (GTS): penki trumpi tonai "
    L"paskutines penkias sekundes ir ilgas tonas tiksliai nustatytu metu. Skirtuke Signalas yra Laiko signalas"
    L" įjungtas ir 1, 5, 10, 15, 20, 30 arba 60 minučių intervalai pagal valdiklio laiką. Iš pradžių išjungta,"
    L" pasirinktas valandos intervalas. Perjungimas meniu išlaiko intervalą. Atsižvelgiama į UTC, juostą, "
    L"poslinkį ir NTP. 20 minučių intervalas skamba :00, :20 ir :40. Vienalaikiai valdiklių ir žadintuvų "
    L"signalai sujungiami. Nutildžius dabartinis tonas gali baigtis, kiti praleidžiami, o įjungus garsą "
    L"girdimas tik kitas suplanuotas tonas. Atskiras Kalendorius neturi žadintuvo, laiko signalo ar nutildymo"
    L".\r\n\r\nSkirtuko Programa Laiko signalo garsas siūlo "
    L"Įtaisytasis generatorius (numatyta) ir Sistemos pyptelėjimas visiems valdikliams ir žadintuvams. Laiko "
    L"signalo garsumas rodo generatoriaus lygį dB: dešinėje 0 dB – didžiausia neiškraipyta sinusoidės "
    L"amplitudė, −∞ dB – tyla, numatyta −18 dB. Tikrinti pradeda nepertraukiamą peržiūrą, Stabdyti tikrinimą "
    L"ją baigia. Tikrinami abu garsai; tikrinimas neįrašomas. Laikant slankiklį garsas taip pat leidžiamas iki"
    L" pelės atleidimo, jei nevyksta mygtuko tikrinimas. Pradedama kitą pilną sekundę: trumpas tonas kas "
    L"sekundę ir ilgas :00, :05, :10 ir toliau. Vienalaikiai bandomieji, valdiklių ir žadintuvų signalai "
    L"naudoja vieną toną. Sustabdymas leidžia "
    L"dabartiniam tonui baigtis; ilgas gali tęstis dar pusę sekundės. Įskaitomos poslinkių šimtosios dalys; "
    L"persidengiantys tonai skamba nenutrūkstamai iki paskutinio persidengimo pabaigos.",
    L"\r\n\r\nSkaņas laika signāls\r\nSignāls atbilst Griničas laika signālam (GTS): pieci īsi toņi pēdējās "
    L"piecās sekundēs un garš tonis precīzi noteiktajā brīdī. Cilnē Signāls ir Laika signāls ieslēgts un 1, 5,"
    L" 10, 15, 20, 30 vai 60 minūšu intervāli pēc logrīka laika. Sākumā izslēgts, atlasīts stundas intervāls. "
    L"Pārslēgšana izvēlnē saglabā intervālu. Ņem vērā UTC, joslu, nobīdi un NTP; 20 minūšu intervālā skan :00,"
    L" :20 un :40. Vienlaicīgie logrīku un modinātāju signāli apvienojas. Izslēdzot skaņu, pašreizējais tonis "
    L"var beigties; nākamie tiek izlaisti līdz nākamajam plānotajam tonim pēc skaņas ieslēgšanas. Atsevišķam "
    L"Kalendāram nav modinātāja, laika signāla vai skaņas izslēgšanas"
    L".\r\n\r\nCilnē Programma Laika signāla skaņa piedāvā Iebūvēts ģenerators (noklusējums) "
    L"un Sistēmas pīkstiens visiem logrīkiem un modinātājiem. Laika signāla skaļums rāda ģeneratora līmeni dB:"
    L" labajā galā 0 dB ir maksimālā neizkropļotā sinusoīdas amplitūda, −∞ dB klusums, noklusējums −18 dB. "
    L"Pārbaudīt sāk nepārtrauktu priekšskatījumu, Apturēt pārbaudi to beidz. Pārbaudāmas abas skaņas; pārbaude"
    L" netiek saglabāta. Turot slīdni, skaņa skan līdz peles atlaišanai, ja nenotiek pogas pārbaude. "
    L"Atskaņošana sākas nākamajā veselajā sekundē: īss tonis katru sekundi un garš :00, :05, :10 utt. "
    L"Vienlaicīgie pārbaudes, logrīku un modinātāju signāli izmanto vienu toni. "
    L"Apturot pašreizējais tonis drīkst beigties; garais var turpināties vēl "
    L"pussekundi. Ņem vērā nobīdes simtdaļas; pārklājušies toņi skan nepārtraukti līdz pēdējā pārklājuma "
    L"beigām.",
    L"\r\n\r\nHallható időjelzés\r\nA jelzés a Greenwich Time Signal (GTS) mintáját követi: öt rövid hang az "
    L"utolsó öt másodpercben, majd hosszú hang a pontos időhatáron. Az Időjelzés fülön az Időjelzés "
    L"engedélyezve és 1, 5, 10, 15, 20, 30 vagy 60 perces intervallum választható a minialkalmazás ideje "
    L"szerint. Kezdetben kikapcsolt, órás intervallummal. A menübeli kapcsolás megőrzi az intervallumot. "
    L"Figyelembe veszi az UTC-t, időzónát, eltolást és NTP-t; 20 percnél :00, :20 és :40 időpontban szól. Az "
    L"egyidejű óra- és ébresztési jelzések egyesülnek. Némítás után az aktuális hang befejeződhet; a "
    L"következők kimaradnak, és feloldáskor csak a következő ütemezett hang szól. Az önálló Naptárnak nincs "
    L"ébresztése, időjelzése vagy némítása"
    L".\r\n\r\nAz Alkalmazás fül Időjelzés hangja beállítása Beépített generátor (alapértelmezett) vagy"
    L" Rendszerhang lehet minden órához és ébresztéshez. Az Időjelzés hangereje dB-ben mutatja a generátor "
    L"szintjét: a jobb szélső 0 dB a legnagyobb torzítatlan szinuszamplitúdó, −∞ dB a csend, −18 dB az "
    L"alapérték. A Tesztelés folyamatos próbát indít, a Teszt leállítása befejezi. Mindkét hang tesztelhető; a"
    L" teszt nem mentődik. A csúszka nyomva tartása is szól az egér felengedéséig, ha nincs gombbal indított "
    L"teszt. A lejátszás a következő egész másodpercnél indul: rövid hang másodpercenként és hosszú :00, :05, "
    L":10 stb. időpontban. Az egyidejű teszt-, óra- és ébresztési hangok egyetlen hangot használnak. A "
    L"rendszerhangnál csak a hangerőcsúszka tiltott. Leállításkor az aktuális hang befejeződik; a hosszú még "
    L"fél másodpercig tarthat. A századmásodperces eltolás is számít; az átfedő hangok az utolsó átfedés "
    L"végéig megszakítás nélkül szólnak.",
    L"\r\n\r\nSinjal tal-ħin li jinstema’\r\nIs-sinjal isegwi s-Sinjal tal-Ħin ta’ Greenwich (GTS): ħames toni"
    L" qosra fl-aħħar ħames sekondi u ton twil eżatt fil-ħin stabbilit. It-tab Sinjal għandu Sinjal tal-ħin "
    L"attivat u intervalli ta’ 1, 5, 10, 15, 20, 30 jew 60 minuta skont il-ħin tal-widget. Għall-ewwel huwa "
    L"mitfi b’intervall ta’ siegħa magħżul. Il-bidla fil-menu żżomm l-intervall. Jitqiesu UTC, iż-żona, "
    L"il-kumpens u NTP; b’20 minuta jindaqq f’:00, :20 u :40. Sinjali simultanji ta’ widgets u allarmi "
    L"jingħaqdu. Wara s-sikket, it-ton kurrenti jista’ jispiċċa, dawk li jmiss jinqabżu u wara li jerġa’ "
    L"jinxtegħel il-ħoss jinstema’ biss it-ton skedat li jmiss. Kalendarju separat m’għandux allarm, sinjal "
    L"tal-ħin jew sikket.\r\n\r\nĦoss tas-sinjal "
    L"tal-ħin fit-tab Applikazzjoni joffri Ġeneratur integrat (default) u Ħoss tas-sistema għall-widgets u "
    L"l-allarmi kollha. Volum tas-sinjal tal-ħin juri l-livell tal-ġeneratur f’dB: 0 dB fuq il-lemin huwa "
    L"l-massimu ta’ amplitudni sinusojdali mingħajr distorsjoni, −∞ dB huwa skiet, u d-default −18 dB. "
    L"Ittestja jibda previżjoni kontinwa, Waqqaf it-test itemmha. Iż-żewġ ħsejjes jistgħu jiġu ttestjati; "
    L"it-test ma jiġix issejvjat. Iż-żamma tas-slajder iddoqq ukoll sal-ħelsien tal-maws, sakemm mhux għaddej "
    L"test mill-buttuna. Id-daqq jibda fis-sekonda sħiħa li jmiss: ton qasir kull sekonda u twil f’:00, :05, "
    L":10 u hekk ikompli. Sinjali simultanji ta’ prova, widgets u allarmi jaqsmu ton wieħed. "
    L"Il-waqfien iħalli t-ton kurrenti jispiċċa; wieħed"
    L" twil jista’ jdum nofs sekonda oħra. Jitqiesu ċ-ċentesimi tal-kumpens; toni li jikkoinċidu jindaqqu "
    L"kontinwament sa tmiem l-aħħar sovrapożizzjoni.",
    L"\r\n\r\nHoorbaar tijdsignaal\r\nHet signaal volgt Greenwich Time Signal (GTS): vijf korte tonen tijdens "
    L"de laatste vijf seconden en een lange toon precies op de tijdgrens. Signaal biedt Tijdsignaal "
    L"ingeschakeld en intervallen van 1, 5, 10, 15, 20, 30 of 60 minuten volgens de widgettijd. Aanvankelijk "
    L"staat het uit met een uurinterval geselecteerd. Schakelen via het menu behoudt het interval. UTC, "
    L"tijdzone, verschuiving en NTP tellen mee; bij 20 minuten klinkt het op :00, :20 en :40. Gelijktijdige "
    L"widget- en alarmsignalen worden samengevoegd. Na dempen mag de huidige toon eindigen; volgende tonen "
    L"worden overgeslagen tot de eerstvolgende geplande toon na opheffen. Een losse Kalender heeft geen alarm,"
    L" tijdsignaal of demping"
    L".\r\n\r\nGeluid tijdsignaal op Toepassing biedt Ingebouwde generator (standaard) en Systeempiep voor"
    L" alle widgets en alarmen. Volume tijdsignaal toont het generatorniveau in dB: rechts is 0 dB de maximale"
    L" onvervormde sinusamplitude, −∞ dB is stilte en −18 dB de standaard. Testen start een voortdurend "
    L"voorbeeld, Test stoppen beëindigt dit. Beide geluiden zijn te testen; de test wordt niet opgeslagen. De "
    L"schuifregelaar vasthouden geeft ook een voorbeeld tot de muis wordt losgelaten, tenzij de knoptest "
    L"loopt. Het afspelen begint op de volgende hele seconde: een korte toon elke seconde en een lange op :00,"
    L" :05, :10 enzovoort. Gelijktijdige test-, widget- en alarmsignalen delen één toon. "
    L"Stoppen laat de huidige toon eindigen; een lange kan "
    L"nog een halve seconde duren. Honderdsten in de verschuiving tellen mee; overlappende tonen klinken "
    L"onafgebroken tot de laatste overlap eindigt.",
    L"\r\n\r\nSemnal orar sonor\r\nSemnalul urmează Greenwich Time Signal (GTS): cinci tonuri scurte în "
    L"ultimele cinci secunde și un ton lung exact la momentul stabilit. Semnal oferă Semnal orar activat și "
    L"intervale de 1, 5, 10, 15, 20, 30 sau 60 de minute după ora widgetului. Inițial este dezactivat, cu "
    L"interval orar selectat. Comutarea din meniu păstrează intervalul. Sunt respectate UTC, fusul, decalajul "
    L"și NTP; la 20 de minute sună la :00, :20 și :40. Semnalele simultane ale widgeturilor și alarmelor se "
    L"îmbină. După dezactivarea sunetului, tonul curent se poate încheia; următoarele sunt omise până la "
    L"următorul ton programat după reactivare. Un Calendar separat nu are alarmă, semnal orar sau dezactivare "
    L"de sunet.\r\n\r\nSunet semnal orar din "
    L"Aplicație oferă Generator încorporat (implicit) și Bip de sistem pentru toate widgeturile și alarmele. "
    L"Volum semnal orar arată nivelul generatorului în dB: 0 dB la dreapta este amplitudinea sinusoidală "
    L"maximă nedistorsionată, −∞ dB liniște, iar −18 dB valoarea implicită. Testare începe o previzualizare "
    L"continuă, Oprire test o încheie. Se pot testa ambele sunete; testul nu se salvează. Menținerea "
    L"glisorului redă și ea sunet până la eliberarea mouse-ului, dacă nu rulează testul din buton. Redarea "
    L"începe la următoarea secundă întreagă: ton scurt în fiecare secundă și lung la :00, :05, :10 etc. "
    L"Semnalele simultane de test, widget și alarmă folosesc un singur ton. "
    L"Oprirea lasă tonul curent să se încheie; unul lung poate dura încă o"
    L" jumătate de secundă. Sunt luate în calcul sutimile decalajului; tonurile suprapuse sună continuu până "
    L"la sfârșitul ultimei suprapuneri.",
    L"\r\n\r\nΗχητικό σήμα ώρας\r\nΤο σήμα ακολουθεί το Greenwich Time Signal (GTS): πέντε σύντομοι τόνοι στα "
    L"τελευταία πέντε δευτερόλεπτα και παρατεταμένος τόνος στην ακριβή χρονική στιγμή. Η καρτέλα Σήμα έχει "
    L"Σήμα ώρας ενεργό και διαστήματα 1, 5, 10, 15, 20, 30 ή 60 λεπτών κατά την ώρα του στοιχείου. Αρχικά "
    L"είναι ανενεργό με επιλεγμένο ωριαίο διάστημα. Το μενού διατηρεί το διάστημα. Λαμβάνονται υπόψη UTC, "
    L"ζώνη, μετατόπιση και NTP· στα 20 λεπτά ακούγεται στις :00, :20 και :40. Ταυτόχρονα σήματα στοιχείων και "
    L"ξυπνητηριών ενώνονται. Μετά τη σίγαση ο τρέχων τόνος μπορεί να ολοκληρωθεί· οι επόμενοι παραλείπονται "
    L"μέχρι τον επόμενο προγραμματισμένο τόνο μετά την άρση της. Ανεξάρτητο Ημερολόγιο δεν έχει ξυπνητήρι, "
    L"σήμα ή σίγαση· τα αντίστοιχα χειριστήρια είναι ανενεργά και λείπουν από το μενού.\r\n\r\nΟ Ήχος σήματος "
    L"ώρας στην Εφαρμογή προσφέρει Ενσωματωμένη γεννήτρια (προεπιλογή) και Ήχος συστήματος για όλα τα στοιχεία"
    L" και ξυπνητήρια. Η Ένταση σήματος ώρας δείχνει επίπεδο γεννήτριας σε dB: δεξιά 0 dB είναι η μέγιστη "
    L"ημιτονοειδής ένταση χωρίς παραμόρφωση, −∞ dB σιωπή και −18 dB η προεπιλογή. Η Δοκιμή αρχίζει συνεχή "
    L"προεπισκόπηση, η Διακοπή δοκιμής τη σταματά. Δοκιμάζονται και οι δύο ήχοι· η δοκιμή δεν αποθηκεύεται. "
    L"Κρατώντας το ρυθμιστικό ακούγεται επίσης προεπισκόπηση μέχρι την απελευθέρωση του ποντικιού, εκτός αν "
    L"εκτελείται δοκιμή κουμπιού. Αρχίζει στο επόμενο ακέραιο δευτερόλεπτο: σύντομος τόνος κάθε δευτερόλεπτο "
    L"και μακρύς στις :00, :05, :10 κ.ο.κ. Ταυτόχρονα δοκιμαστικά σήματα, στοιχεία και ξυπνητήρια μοιράζονται "
    L"έναν τόνο. Η διακοπή αφήνει τον "
    L"τρέχοντα τόνο να τελειώσει· ο μακρύς μπορεί να διαρκέσει άλλο μισό δευτερόλεπτο. Υπολογίζονται και "
    L"εκατοστά μετατόπισης· επικαλυπτόμενοι τόνοι ακούγονται συνεχώς μέχρι το τέλος της τελευταίας επικάλυψης.",
    L"\r\n\r\nZvučni vremenski signal\r\nSignal slijedi obrazac Greenwich Time Signal (GTS). Kartica Signal "
    L"sadrži opciju Vremenski signal uključen i odabir intervala od 1, 5, 10, 15, 20, 30 ili 60 minuta prema "
    L"prikazanom vremenu vidžeta. Signal je u početku isključen, a odabran je interval od jednog sata. "
    L"Isključivanje i uključivanje u meniju čuva interval. Meni prikazuje vrijeme alarma i interval signala u "
    L"zagradama. Granica prati vrijeme vidžeta, uključujući UTC, vremensku zonu, pomak i NTP sinhronizaciju. "
    L"Pet kratkih tonova označava posljednjih pet sekundi, a dugi ton tačnu granicu. Istovremeni signali više "
    L"vidžeta spajaju se u jedan niz. Nakon isključivanja zvuka trenutni ton može završiti; sljedeći se "
    L"preskaču, a nakon uključivanja zvuka čuje se tek sljedeći planirani ton. Samostalni Kalendar nema alarm,"
    L" vremenski signal ni isključivanje zvuk"
    L"a.\r\n\r\nPri intervalu od 20 minuta signal se čuje na :00, :20 i :40 prema vremenu "
    L"vidžeta.\r\n\r\nNa kartici Program opcija Zvuk vremenskog signala nudi Ugrađeni generator i Zvuk "
    L"sistema. Izbor vrijedi za sve vidžete, uključujući signale alarma. Podrazumijevani je Ugrađeni "
    L"generator.\r\n\r\nKlizač Glasnoća vremenskog signala na kartici Program prikazuje razinu generatora u "
    L"dB. Krajnji desni položaj je 0 dB, najveća neizobličena amplituda sinusoide; tišina je −∞ dB. "
    L"Podrazumijevana je glasnoća −18 dB. Testiraj uz izbor zvuka pokreće neprekidni pregled, a Zaustavi test "
    L"ga završava. Oba se zvuka mogu testirati; test se ne čuva. Držanje klizača glasnoće također pokreće "
    L"pregled do otpuštanja miša, osim ako traje test pokrenut dugmetom. Reprodukcija počinje na sljedećoj "
    L"punoj sekundi: kratki ton svake sekunde i dugi na :00, :05, :10 i tako dalje. Istovremeni probni signali"
    L" i signali vidžeta ili alarma dijele jedan ton. Za"
    L"ustavljanje testa dopušta završetak trenutnog tona; dugi ton može trajati još do pola sekunde. Pomaci "
    L"vidžeta poštuju se i u stotinkama sekunde. Tonovi vidžeta, alarma i testova koji se preklapaju zvuče kao"
    L" jedan neprekidan ton do kraja posljednjeg preklapanja.",
    L"\r\n\r\nZvučni vremenski signal\r\nSignal slijedi obrazac Greenwich Time Signal (GTS). Kartica Signal "
    L"sadrži opciju Vremenski signal uključen i odabir intervala od 1, 5, 10, 15, 20, 30 ili 60 minuta prema "
    L"prikazanom vremenu widgeta. Signal je u početku isključen, a odabran je interval od jednog sata. "
    L"Isključivanje i uključivanje u izborniku čuva interval. Izbornik prikazuje vrijeme alarma i interval "
    L"signala u zagradama. Granica prati vrijeme widgeta, uključujući UTC, vremensku zonu, pomak i NTP "
    L"sinkronizaciju. Pet kratkih tonova označava posljednjih pet sekundi, a dugi ton točnu granicu. Istodobni"
    L" signali više widgeta spajaju se u jedan niz. Nakon isključivanja zvuka trenutačni ton može završiti; "
    L"sljedeći se preskaču, a nakon uključivanja zvuka čuje se tek sljedeći planirani ton. Samostalni Kalendar"
    L" nema alarm, vremenski signal ni isključivanje zvu"
    L"ka.\r\n\r\nPri intervalu od 20 minuta signal se čuje na :00, :20 i :40 "
    L"prema vremenu widgeta.\r\n\r\nNa kartici Program opcija Zvuk vremenskog signala nudi Ugrađeni generator "
    L"i Zvuk sustava. Izbor vrijedi za sve widgete, uključujući signale alarma. Zadani je Ugrađeni "
    L"generator.\r\n\r\nKlizač Glasnoća vremenskog signala na kartici Program prikazuje razinu generatora u "
    L"dB. Krajnji desni položaj je 0 dB, najveća neizobličena amplituda sinusoide; tišina je −∞ dB. Zadana je "
    L"glasnoća −18 dB. Testiraj uz izbor zvuka pokreće neprekidni pretpregled, a Zaustavi test ga završava. "
    L"Oba se zvuka mogu testirati; test se ne sprema. Držanje klizača glasnoće također pokreće pretpregled do "
    L"otpuštanja miša, osim ako traje test pokrenut gumbom. Reprodukcija počinje na sljedećoj punoj sekundi: "
    L"kratki ton svake sekunde i dugi na :00, :05, :10 i tako dalje. Istodobni probni signali i signali "
    L"widgeta ili alarma dijele jedan ton. Zaustavljanje "
    L"testa dopušta završetak trenutačnog tona; dugi ton može trajati još do pola sekunde. Pomaci widgeta "
    L"poštuju se i u stotinkama sekunde. Tonovi widgeta, alarma i testova koji se preklapaju zvuče kao jedan "
    L"neprekidan ton do kraja posljednjeg preklapanja.",
    L"\r\n\r\nZvočni časovni signal\r\nSignal sledi vzorcu Greenwich Time Signal (GTS). Zavihek Signal ponuja "
    L"Časovni signal vključen in intervale 1, 5, 10, 15, 20, 30 ali 60 minut po prikazanem času gradnika. "
    L"Signal je sprva izključen, izbran pa je enourni interval. Preklop v meniju ohrani interval; čas budilke "
    L"in interval sta prikazana v oklepajih. Časovna meja upošteva UTC, časovni pas, odmik in NTP. V zadnjih "
    L"petih sekundah se oglasi pet kratkih piskov, natanko na meji pa dolg. Sočasni signali se združijo v eno "
    L"zaporedje. Ob izklopu zvoka se trenutni pisk lahko konča, nadaljnji se izpustijo, po vklopu pa se "
    L"zasliši šele naslednji načrtovani pisk. Samostojni Koledar nima budilke, časovnega signala ali utišanja"
    L".\r\n\r\nPri intervalu 20 minut se signal oglasi "
    L"ob :00, :20 in :40 po času gradnika. Na zavihku Program Zvok časovnega signala ponuja Vgrajeni generator"
    L" (privzeto) in Sistemski pisk. Izbira velja za vse gradnike, tudi za signale budilk.\r\n\r\nGlasnost "
    L"časovnega signala kaže raven generatorja v dB. Desni konec je 0 dB, največja nepopačena amplituda "
    L"sinusoide; tišina je −∞ dB. Privzeto je −18 dB. Preizkusi ob izbiri zvoka začne neprekinjeni predogled, "
    L"Ustavi preizkus pa ga konča. Preizkusiti je mogoče obe možnosti; preizkus se ne shrani. Držanje drsnika "
    L"prav tako predvaja predogled do izpusta miške, razen če teče preizkus z gumbom. Predvajanje se začne ob "
    L"naslednji polni sekundi: kratko vsako sekundo in dolgo ob :00, :05, :10 in tako naprej. Sočasni "
    L"poskusni, gradniški in budilkini signali imajo skupen ton. "
    L"Ob ustavitvi se trenutni pisk konča; dolg lahko traja še pol sekunde. Upoštevane so tudi "
    L"stotinke odmikov. Prekrivajoči se toni trajajo neprekinjeno do konca zadnjega prekrivanja.",
    L"\r\n\r\nZvučni vremenski signal\r\nSignal prati obrazac Greenwich Time Signal (GTS). Kartica Signal ima "
    L"Vremenski signal uključen i intervale 1, 5, 10, 15, 20, 30 ili 60 minuta prema vremenu vidžeta. Signal "
    L"je prvobitno isključen, a izabran je jednočasovni interval. Prebacivanje u meniju čuva interval; vrijeme"
    L" alarma i interval prikazani su u zagradama. Granica prati UTC, vremensku zonu, pomak i NTP. Pet kratkih"
    L" tonova obilježava posljednjih pet sekundi, dugi tačnu granicu. Istovremeni signali spajaju se u jednu "
    L"sekvencu. Poslije isključivanja zvuka trenutni ton može da završi; sljedeći se preskaču, a nakon "
    L"uključivanja čuje se tek sljedeći planirani ton. Samostalni Kalendar nema alarm, vremenski signal ni "
    L"isključivanje zvuka.\r\n\r\nPri intervalu"
    L" 20 minuta signal se čuje na :00, :20 i :40 po vremenu vidžeta. Na kartici Program Zvuk vremenskog "
    L"signala nudi Ugrađeni generator (podrazumijevano) i Sistemski zvučni signal. Izbor važi za sve vidžete, "
    L"uključujući signale alarma.\r\n\r\nJačina vremenskog signala pokazuje nivo generatora u dB. Desni kraj "
    L"je 0 dB, najveća neizobličena amplituda sinusoide; tišina je −∞ dB. Podrazumijevano je −18 dB. Testiraj "
    L"pored izbora zvuka pokreće neprekidan probni zvuk, Zaustavi test ga završava. Obje vrste zvuka mogu se "
    L"testirati; test se ne čuva. Držanje klizača takođe pušta probni zvuk do otpuštanja miša, osim ako traje "
    L"test dugmetom. Reprodukcija počinje na sljedećoj cijeloj sekundi: kratak ton svake sekunde i dugi na "
    L":00, :05, :10 i tako dalje. Istovremeni probni signali i signali vidžeta ili alarma dijele jedan ton. Za"
    L"ustavljanje dopušta da trenutni ton završi; dugi "
    L"može trajati još pola sekunde. Uračunavaju se i stotinke pomaka. Tonovi koji se preklapaju zvuče "
    L"neprekidno do kraja posljednjeg preklapanja.",
    L"\r\n\r\nГукавы сігнал дакладнага часу\r\nСігнал адпавядае грынвіцкаму сігналу часу (GTS). Укладка "
    L"«Сігнал» мае «Сігнал часу ўключаны» і інтэрвалы 1, 5, 10, 15, 20, 30 або 60 хвілін паводле часу віджэта."
    L" Спачатку сігнал выключаны, а інтэрвал — адна гадзіна. Пераключэнне ў меню захоўвае інтэрвал. Час "
    L"будзільніка і інтэрвал паказваюцца ў дужках. Часавая мяжа ўлічвае UTC, пояс, зрушэнне і NTP. Пяць "
    L"кароткіх тонаў гучаць у апошнія пяць секунд, доўгі — дакладна на мяжы. Адначасовыя сігналы "
    L"аб’ядноўваюцца ў адну паслядоўнасць. Пасля выключэння гуку бягучы тон можа скончыцца; наступныя "
    L"прапускаюцца, а пасля ўключэння гучыць толькі наступны запланаваны тон. Асобны каляндар не мае "
    L"будзільніка, сігналу часу і выключэння гуку"
    L".\r\n\r\nПры інтэрвале 20 хвілін сігналы гучаць на :00, :20 і :40 паводле часу віджэта. На ўкладцы "
    L"«Праграма» «Гук сігналу часу» прапануе «Убудаваны генератар» (прадвызначаны) і «Сістэмны сігнал». Выбар "
    L"дзейнічае для ўсіх віджэтаў, у тым ліку сігналаў будзільніка.\r\n\r\n«Гучнасць сігналу часу» паказвае "
    L"ўзровень генератара ў дБ. Край справа — 0 дБ, найбольшая амплітуда сінусоіды без скажэнняў; цішыня — −∞ "
    L"дБ. Прадвызначаная гучнасць — −18 дБ. «Праверыць» побач з выбарам гуку запускае бесперапынны прагляд, а "
    L"«Спыніць тэст» заканчвае яго. Абодва гукі можна праверыць; тэст не захоўваецца. Утрымліванне паўзунка "
    L"таксама прайграе гук да адпускання мышы, калі не ідзе тэст кнопкай. Прайграванне пачынаецца з наступнай "
    L"поўнай секунды: кароткі тон кожную секунду і доўгі на :00, :05, :10 і далей. Адначасовыя пробныя сігналы"
    L" і сігналы віджэтаў ці будзільнікаў маюць адзін тон. "
    L"Пры спыненні бягучы тон дагучвае; доўгі можа гучаць яшчэ да паловы секунды. Улічваюцца і сотыя"
    L" долі зрушэнняў. Тоны, якія перакрываюцца, гучаць непарыўна да канца апошняга перакрыцця.",
    L"\r\n\r\nЗвуков сигнал за точно време\r\nСигналът следва гринуичкия сигнал за време (GTS). Разделът "
    L"„Сигнал“ има „Сигналът за време е включен“ и интервали 1, 5, 10, 15, 20, 30 или 60 минути според "
    L"показваното време. Първоначално сигналът е изключен и е избран едночасов интервал. Превключването в "
    L"менюто запазва интервала; часът на алармата и интервалът се показват в скоби. Времевата граница отчита "
    L"UTC, зоната, отместването и NTP. Пет кратки тона звучат в последните пет секунди, дълъг — точно на "
    L"границата. Едновременните сигнали се обединяват в една поредица. След изключване на звука текущият тон "
    L"може да завърши, следващите се пропускат, а след включване се чува следващият планиран тон. "
    L"Самостоятелният календар няма аларма, сигнал за време или изключване на звука"
    L".\r\n\r\nПри интервал 20 минути сигналите звучат на :00, :20 и :40 според "
    L"времето на модула. В раздела „Програма“ „Звук на сигнала за време“ предлага „Вграден генератор“ (по "
    L"подразбиране) и „Системен сигнал“. Изборът важи за всички модули, включително сигналите на "
    L"алармите.\r\n\r\n„Сила на сигнала за време“ показва нивото на генератора в dB. Крайното дясно положение "
    L"е 0 dB, максимална синусоидална амплитуда без изкривяване; тишината е −∞ dB. По подразбиране е −18 dB. "
    L"„Тествай“ до избора на звук стартира непрекъснато прослушване, а „Спри теста“ го прекратява. И двата "
    L"звука могат да се тестват; тестът не се записва. Задържането на плъзгача също пуска прослушване до "
    L"отпускане на мишката, освен ако тече тест от бутона. Възпроизвеждането започва от следващата цяла "
    L"секунда: кратък тон всяка секунда и дълъг на :00, :05, :10 и нататък. Едновременните пробни сигнали и "
    L"сигналите на модулите или алармите споделят един тон. "
    L"При спиране текущият тон завършва; дългият може да продължи още половин секунда. "
    L"Отместванията се отчитат и в стотни от секундата. Застъпващите се тонове звучат непрекъснато до края на "
    L"последното застъпване.",
    L"\r\n\r\nЗвучен временски сигнал\r\nСигналот го следи гриничкиот временски сигнал (GTS). Картичката "
    L"„Сигнал“ има „Временскиот сигнал е вклучен“ и интервали 1, 5, 10, 15, 20, 30 или 60 минути според "
    L"времето на виџетот. Сигналот почнува исклучен со избран едночасовен интервал. Менувањето во менито го "
    L"зачувува интервалот; времето на алармот и интервалот се прикажуваат во загради. Временската граница ги "
    L"зема предвид UTC, зоната, поместувањето и NTP. Пет кратки тона ги означуваат последните пет секунди, а "
    L"долг тон точната граница. Истовремените сигнали се спојуваат во една низа. По исклучување на звукот "
    L"тековниот тон може да заврши; следните се прескокнуваат, а по вклучување се слуша следниот планиран тон."
    L" Самостојниот календар нема аларм, временски сигнал или исклучување звук"
    L".\r\n\r\nПри интервал 20 минути сигналите се слушаат на :00, :20 и :40 "
    L"според времето на виџетот. Во „Програма“, „Звук на временскиот сигнал“ нуди „Вграден генератор“ "
    L"(стандардно) и „Системски сигнал“. Изборот важи за сите виџети, вклучувајќи ги сигналите на "
    L"алармите.\r\n\r\n„Гласност на временскиот сигнал“ го покажува нивото на генераторот во dB. Десниот крај "
    L"е 0 dB, најголемата неизобличена синусоидална амплитуда; тишината е −∞ dB. Стандардно е −18 dB. "
    L"„Тестирај“ до изборот на звук почнува непрекинато пробно слушање, а „Запри го тестот“ го завршува. Може "
    L"да се тестираат двата звука; тестот не се зачувува. Држењето на лизгачот пушта пробен звук до отпуштање "
    L"на глувчето, освен ако тече тест од копчето. Пуштањето почнува на следната цела секунда: краток тон "
    L"секоја секунда и долг на :00, :05, :10 и понатаму. Истовремените пробни сигнали и сигналите на виџетите "
    L"или алармите делат еден тон. Запирањето го"
    L" остава тековниот тон да заврши; долгиот може да трае уште половина секунда. Се земаат предвид и "
    L"стотинките на поместувањата. Преклопените тонови звучат непрекинато до крајот на последното "
    L"преклопување.",
    L"\r\n\r\nЗвучни временски сигнал\r\nСигнал прати образац Greenwich Time Signal (GTS). Картица Сигнал има "
    L"Временски сигнал укључен и интервале 1, 5, 10, 15, 20, 30 или 60 минута према времену виџета. Сигнал је "
    L"првобитно искључен, а изабран је једночасовни интервал. Пребацивање у менију чува интервал; време аларма"
    L" и интервал приказани су у заградама. Граница прати UTC, временску зону, помак и NTP. Пет кратких тонова"
    L" обележава последњих пет секунди, дуги тачну границу. Истовремени сигнали спајају се у једну секвенцу. "
    L"После искључивања звука тренутни тон може да заврши; следећи се прескачу, а након укључивања чује се тек"
    L" следећи планирани тон. Самостални Календар нема аларм, временски сигнал ни искључивање звук"
    L"а.\r\n\r\nПри интервалу 20 минута сигнал се "
    L"чује на :00, :20 и :40 по времену виџета. На картици Програм Звук временског сигнала нуди Уграђени "
    L"генератор (подразумевано) и Системски звучни сигнал. Избор важи за све виџете, укључујући сигнале "
    L"аларма.\r\n\r\nЈачина временског сигнала показује ниво генератора у dB. Десни крај је 0 dB, највећа "
    L"неизобличена амплитуда синусоиде; тишина је −∞ dB. Подразумевано је −18 dB. Тестирај поред избора звука "
    L"покреће непрекидан пробни звук, Заустави тест га завршава. Обе врсте звука могу се тестирати; тест се не"
    L" чува. Држање клизача такође пушта пробни звук до отпуштања миша, осим ако траје тест дугметом. "
    L"Репродукција почиње на следећој целој секунди: кратак тон сваке секунде и дуги на :00, :05, :10 и тако "
    L"даље. Истовремени пробни сигнали и сигнали виџета или аларма деле један тон. За"
    L"устављање допушта да тренутни тон заврши; дуги може трајати још пола"
    L" секунде. Урачунавају се и стотинке помака. Тонови који се преклапају звуче непрекидно до краја "
    L"последњег преклапања.",
    L"\r\n\r\nЗВУКОВИЙ СИГНАЛ ТОЧНОГО ЧАСУ\r\nСигнал відповідає схемі гринвіцького сигналу часу (GTS). На "
    L"вкладці «Сигнал» є прапорець «Сигнал часу увімкнено» та перемикачі інтервалів 1, 5, 10, 15, 20, 30 і 60 "
    L"хвилин за часом віджета. Спочатку сигнал вимкнено, а інтервал установлено на одну годину. Перемикання "
    L"сигналу в меню віджета зберігає вибраний інтервал. Час будильника й інтервал сигналу показуються в меню в"
    L" дужках. Часова межа визначається часом віджета з урахуванням UTC, часового поясу, зсуву та синхронізації"
    L" NTP. Протягом останніх п’яти секунд звучать п’ять коротких сигналів, а точно на межі — довгий. Якщо "
    L"кілька віджетів подають сигнал одночасно, відтворюється одна спільна послідовність. Після вимкнення звуку"
    L" поточний сигнал може завершитися; наступні пропускаються, а після ввімкнення звуку відтворюється лише "
    L"наступний запланований сигнал. Окремий календар не підтримує будильники, сигнали часу та вимкнення звуку"
    L".\r\n\r\nЗа інтервалу 20 хвилин сигнали звучать на "
    L":00, :20 і :40 за часом віджета.\r\n\r\nНа вкладці «Програма» параметр «Звук сигналу часу» дає змогу "
    L"вибрати «Вбудований генератор» або «Системний сигнал». Вибір діє для всіх віджетів, зокрема сигналів "
    L"будильника. Типово використовується вбудований генератор.\r\n\r\nПовзунок «Гучність сигналу часу» на "
    L"вкладці «Програма» показує рівень вбудованого генератора в дБ. Крайнє праве положення — 0 дБ, найбільша "
    L"амплітуда синусоїди без спотворень; тиша — −∞ дБ. Типова гучність — −18 дБ. Кнопка «Перевірити» поряд із "
    L"параметром звуку запускає безперервне прослуховування, а «Зупинити перевірку» завершує його. Можна "
    L"перевірити обидва варіанти звуку; перевірка не зберігається. Утримування повзунка гучності також вмикає "
    L"прослуховування до відпускання кнопки миші, якщо перевірку кнопкою не запущено. Відтворення починається з"
    L" наступної цілої секунди: короткий сигнал щосекунди та довгий на :00, :05, :10 тощо. Одночасні сигнали "
    L"прослуховування, віджетів і будильників об’єднуються. "
    L"Зупинення перевірки дає поточному сигналу завершитися; довгий сигнал може тривати ще до "
    L"половини секунди. Зсуви віджетів враховуються й у сотих частках секунди. Сигнали, що перекриваються, "
    L"звучать як один безперервний звук до завершення останнього перекриття.",
    L"\r\n\r\nЗВУКОВОЙ СИГНАЛ ТОЧНОГО ВРЕМЕНИ\r\nСигнал соответствует схеме гринвичского сигнала времени (GTS)."
    L" На вкладке «Сигнал» есть флажок «Сигнал времени включён» и переключатели интервалов 1, 5, 10, 15, 20, 30"
    L" и 60 минут по времени виджета. Изначально сигнал отключён, а интервал установлен на один час. "
    L"Переключение сигнала в меню виджета сохраняет выбранный интервал. Время будильника и интервал сигнала "
    L"показываются в меню в скобках. Временная граница определяется временем виджета с учётом UTC, часового "
    L"пояса, смещения и синхронизации NTP. В течение последних пяти секунд звучат пять коротких сигналов, а "
    L"точно на границе — длинный. Если несколько виджетов подают сигнал одновременно, воспроизводится одна "
    L"общая последовательность. После отключения звука текущий сигнал может завершиться; следующие "
    L"пропускаются, а после включения звука воспроизводится только следующий запланированный сигнал. Отдельный "
    L"календарь не поддерживает будильники, сигналы времени и отключение звука"
    L".\r\n\r\nПри интервале 20 минут сигналы звучат на :00, :20 и :40 по "
    L"времени виджета.\r\n\r\nНа вкладке «Программа» параметр «Звук сигнала времени» позволяет выбрать "
    L"«Встроенный генератор» или «Системный сигнал». Выбор действует для всех виджетов, включая сигналы "
    L"будильника. По умолчанию используется встроенный генератор.\r\n\r\nПолзунок «Громкость сигнала времени» "
    L"на вкладке «Программа» показывает уровень встроенного генератора в дБ. Крайнее правое положение — 0 дБ, "
    L"наибольшая амплитуда синусоиды без искажений; тишина — −∞ дБ. Громкость по умолчанию — −18 дБ. Кнопка "
    L"«Проверить» рядом с параметром звука запускает непрерывное прослушивание, а «Остановить тест» завершает "
    L"его. Можно проверить оба варианта звука; проверка не сохраняется. Удерживание ползунка громкости также "
    L"включает прослушивание до отпускания кнопки мыши, если проверка кнопкой не запущена. Воспроизведение "
    L"начинается со следующей целой секунды: короткий сигнал каждую секунду и длинный на :00, :05, :10 и так "
    L"далее. Одновременные сигналы прослушивания, виджетов и будильников объединяются. "
    L"Остановка проверки позволяет текущему сигналу завершиться; длинный "
    L"сигнал может продолжаться ещё до половины секунды. Смещения виджетов учитываются и в сотых долях секунды."
    L" Перекрывающиеся сигналы звучат как один непрерывный звук до завершения последнего перекрытия."
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
    L"\r\n\r\nAdditional clocks: On the General tab, a Calendar with clock widget can show up to two "
    L"additional clocks with their own names and time zones. Each clock then also shows its local day of the "
    L"week. Choose each clock face size separately on the Appearance tab or from its right-click menu. "
    L"Additional clocks have no second hand. Adding, removing, or resizing clocks preserves the widget's "
    L"attachment to work-area edges.\r\n\r\nOnly a double-click directly on the main clock face toggles its "
    L"second hand. Additional clock menus contain only size choices. Additional clocks share the widget’s "
    L"language, time format, fonts, and offset; their digital time omits seconds.",
    L"\r\n\r\nZusätzliche Uhren: Auf der Registerkarte Allgemein kann das Widget Kalender mit Uhr bis zu zwei "
    L"weitere Uhren mit eigenen Namen und Zeitzonen anzeigen. Jede Uhr zeigt dann auch ihren lokalen "
    L"Wochentag. Die Größe jedes Zifferblatts lässt sich unter Darstellung oder in seinem Kontextmenü wählen. "
    L"Zusätzliche Uhren haben keinen Sekundenzeiger. Beim Hinzufügen, Entfernen oder Ändern der Größe bleibt "
    L"das Widget an denselben Arbeitsbereichsrändern ausgerichtet.\r\n\r\nNur ein Doppelklick direkt auf das "
    L"Hauptzifferblatt schaltet dessen Sekundenzeiger um. Die Menüs zusätzlicher Uhren enthalten nur Größen. "
    L"Zusätzliche Uhren übernehmen Sprache, Zeitformat, Schriften und Versatz des Widgets; ihre digitale Zeit "
    L"zeigt keine Sekunden.",
    L"\r\n\r\nHorloges supplémentaires : Dans l’onglet Général, le widget Calendrier avec horloge peut "
    L"afficher deux horloges supplémentaires avec leurs propres noms et fuseaux horaires. Chaque horloge "
    L"affiche alors aussi son jour de la semaine local. Choisissez la taille de chaque cadran dans Apparence "
    L"ou dans son menu contextuel. Les horloges supplémentaires n’ont pas de trotteuse. L’ajout, le retrait et"
    L" le redimensionnement préservent l’alignement du widget sur les bords de la zone de travail.\r\n\r\nSeul"
    L" un double-clic directement sur le cadran principal active ou désactive sa trotteuse. Les menus des "
    L"cadrans supplémentaires ne proposent que les tailles. Ces horloges partagent la langue, le format, les "
    L"polices et le décalage du widget ; leur heure numérique omet les secondes.",
    L"\r\n\r\nRelojes adicionales: En la pestaña General, Calendario con reloj permite mostrar hasta dos "
    L"relojes adicionales con nombres y zonas horarias propios. Cada reloj muestra también su día de la semana"
    L" local. El tamaño de cada esfera se elige en Apariencia o en su menú contextual. Los relojes adicionales"
    L" no tienen segundero. Al añadir, quitar o cambiar el tamaño de los relojes se conserva la posición del "
    L"widget junto a los bordes del área de trabajo.\r\n\r\nSolo un doble clic directamente sobre la esfera "
    L"principal activa o desactiva su segundero. Los menús de los relojes adicionales solo contienen tamaños. "
    L"Comparten el idioma, formato, fuentes y desfase del widget; su hora digital no muestra segundos.",
    L"\r\n\r\nOrologi aggiuntivi: Nella scheda Generali, Calendario con orologio può mostrare fino a due "
    L"orologi aggiuntivi con nomi e fusi orari propri. Ogni orologio mostra anche il giorno della settimana "
    L"locale. La dimensione di ogni quadrante si sceglie in Aspetto o nel suo menu contestuale. Gli orologi "
    L"aggiuntivi non hanno la lancetta dei secondi. Aggiungere, rimuovere o ridimensionare gli orologi "
    L"mantiene il widget agganciato agli stessi bordi dell’area di lavoro.\r\n\r\nSolo un doppio clic "
    L"direttamente sul quadrante principale attiva o disattiva la lancetta dei secondi. I menu dei quadranti "
    L"aggiuntivi contengono solo le dimensioni. Condividono lingua, formato, caratteri e offset del widget; "
    L"l’ora digitale non mostra i secondi.",
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
    L"\r\n\r\nAdditional clocks: On the General tab, a Calendar with clock widget can show up to two "
    L"additional clocks with their own names and time zones. Each clock then also shows its local day of the "
    L"week. Choose each clock face size separately on the Appearance tab or from its right-click menu. "
    L"Additional clocks have no second hand. Adding, removing, or resizing clocks preserves the widget's "
    L"attachment to work-area edges.\r\n\r\nOnly a double-click directly on the main clock face toggles its "
    L"second hand. Additional clock menus contain only size choices. Additional clocks share the widget’s "
    L"language, time format, fonts, and offset; their digital time omits seconds.",
    L"\r\n\r\nAdditional clocks: On the General tab, a Calendar with clock widget can show up to two "
    L"additional clocks with their own names and time zones. Each clock then also shows its local day of the "
    L"week. Choose each clock face size separately on the Appearance tab or from its right-click menu. "
    L"Additional clocks have no second hand. Adding, removing, or resizing clocks preserves the widget's "
    L"attachment to work-area edges.\r\n\r\nOnly a double-click directly on the main clock face toggles its "
    L"second hand. Additional clock menus contain only size choices. Additional clocks share the widget’s "
    L"language, time format, fonts, and offset; their digital time omits seconds.",
    L"\r\n\r\nRelógios adicionais: No separador Geral, Calendário com relógio pode apresentar até dois "
    L"relógios adicionais com nomes e fusos horários próprios. Cada relógio apresenta também o dia da semana "
    L"local. Escolha o tamanho de cada mostrador em Aspeto ou no respetivo menu de contexto. Os relógios "
    L"adicionais não têm ponteiro dos segundos. Adicionar, remover ou redimensionar relógios mantém o widget "
    L"junto às mesmas margens da área de trabalho.\r\n\r\nSó um duplo clique diretamente no mostrador "
    L"principal alterna o ponteiro dos segundos. Os menus dos mostradores adicionais contêm apenas tamanhos. "
    L"Estes relógios partilham o idioma, formato, tipos de letra e desvio do widget; a hora digital não mostra"
    L" segundos.",
    L"\r\n\r\nEkstra klokker: På fanen Generelt kan Kalender med klokke vise opptil to ekstra klokker med egne"
    L" navn og tidssoner. Hver klokke viser også sin lokale ukedag. Velg størrelsen på hver urskive under "
    L"Utseende eller i dens høyreklikkmeny. Ekstra klokker har ingen sekundviser. Når klokker legges til, "
    L"fjernes eller endrer størrelse, forblir widgeten festet til de samme kantene av "
    L"arbeidsområdet.\r\n\r\nBare et dobbeltklikk direkte på hovedurskiven veksler sekundviseren. Menyene for "
    L"ekstra urskiver inneholder bare størrelser. Ekstra klokker deler widgetens språk, tidsformat, skrifter "
    L"og forskyvning; den digitale tiden viser ikke sekunder.",
    L"\r\n\r\nExtra klockor: På fliken Allmänt kan Kalender med klocka visa upp till två extra klockor med "
    L"egna namn och tidszoner. Varje klocka visar även sin lokala veckodag. Välj storlek för varje urtavla "
    L"under Utseende eller i dess högerklicksmeny. Extra klockor saknar sekundvisare. När klockor läggs till, "
    L"tas bort eller ändrar storlek ligger widgeten kvar vid samma kanter av arbetsområdet.\r\n\r\nEndast ett "
    L"dubbelklick direkt på huvudurtavlan växlar sekundvisaren. Menyerna för extra urtavlor innehåller bara "
    L"storlekar. Extra klockor delar widgetens språk, tidsformat, teckensnitt och förskjutning; den digitala "
    L"tiden visar inte sekunder.",
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
    L"\r\n\r\nEkstra ure: På fanen Generelt kan Kalender med ur vise op til to ekstra ure med egne navne og "
    L"tidszoner. Hvert ur viser også sin lokale ugedag. Vælg størrelsen på hver urskive under Udseende eller i"
    L" dens højrekliksmenu. Ekstra ure har ingen sekundviser. Når ure tilføjes, fjernes eller ændrer "
    L"størrelse, forbliver widgetten fastgjort til de samme kanter af arbejdsområdet.\r\n\r\nKun et "
    L"dobbeltklik direkte på hovedurskiven skifter sekundviseren. Menuerne for ekstra urskiver indeholder kun "
    L"størrelser. Ekstra ure deler widgetens sprog, tidsformat, skrifttyper og forskydning; den digitale tid "
    L"viser ikke sekunder.",
    L"\r\n\r\nViðbótarklukkur: Á flipanum Almennt getur Dagatal með klukku sýnt allt að tvær viðbótarklukkur "
    L"með eigin nöfnum og tímabeltum. Hver klukka sýnir einnig vikudaginn á sínum stað. Veldu stærð hverrar "
    L"klukkuskífu í Útliti eða í hægrismellivalmynd hennar. Viðbótarklukkur hafa engan sekúnduvísi. Þegar "
    L"klukkum er bætt við, þær fjarlægðar eða stærð þeirra breytt helst græjan við sömu brúnir "
    L"vinnusvæðisins.\r\n\r\nAðeins tvísmellur beint á aðalskífuna skiptir um sýnileika sekúnduvísisins. "
    L"Valmyndir aukaskífa innihalda aðeins stærðir. Aukaklukkur nota tungumál, tímasnið, letur og hliðrun "
    L"græjunnar; stafræni tíminn sýnir ekki sekúndur.",
    L"\r\n\r\nEk saatler: Genel sekmesinde Saatli takvim bileşeni, kendi adları ve saat dilimleri olan iki ek "
    L"saat gösterebilir. Her saat kendi yerel haftanın gününü de gösterir. Her kadranın boyutunu Görünüm "
    L"sekmesinden veya kendi sağ tıklama menüsünden seçin. Ek saatlerde saniye ibresi yoktur. Saat eklerken, "
    L"kaldırırken veya boyutunu değiştirirken bileşen çalışma alanının aynı kenarlarına bağlı "
    L"kalır.\r\n\r\nYalnızca ana kadrana doğrudan çift tıklamak saniye ibresini açıp kapatır. Ek kadranların "
    L"menülerinde yalnızca boyutlar bulunur. Ek saatler aracın dilini, zaman biçimini, yazı tiplerini ve "
    L"ofsetini paylaşır; dijital saatlerinde saniye gösterilmez.",
    L"\r\n\r\nLisakellad\r\nKalender ja kell võib vahekaardil Üldine kuvada kuni kahte lisakella oma nime ja "
    L"ajavööndiga. Iga kell kuvab siis ka kohaliku nädalapäeva. Sihverplaadi suurus valitakse eraldi "
    L"vahekaardil Ilme või selle paremklõpsumenüüs. Lisakelladel pole sekundiosutit. Lisamine, eemaldamine ja "
    L"suuruse muutmine säilitavad kinnituse tööala servade külge.\r\n\r\nAinult otse peamisel sihverplaadil "
    L"tehtud topeltklõps lülitab selle sekundiosutit. Lisakella menüüs on ainult suurused. Lisakellad jagavad "
    L"vidina keelt, ajavormingut, fonte ja nihet; nende digitaalkuva ei näita sekundeid.",
    L"\r\n\r\nCloig bhreise\r\nIs féidir le Féilire agus clog suas le dhá chlog bhreise a thaispeáint ar "
    L"Ginearálta, lena n-ainmneacha agus a gcriosanna ama féin. Taispeánann gach clog lá áitiúil na seachtaine"
    L" ansin freisin. Roghnaítear méid gach aghaidhe ar Cuma nó ina roghchlár deaschliceála. Níl lámh soicindí"
    L" ag cloig bhreise. Coinníonn cur leis, baint agus athrú méide an ceangal le himill an limistéir "
    L"oibre.\r\n\r\nNí athraíonn ach déchliceáil díreach ar an bpríomhaghaidh a lámh soicindí. Níl ach "
    L"méideanna i roghchláir na gclog breise. Roinneann siad teanga, formáid ama, clónna agus fritháireamh na "
    L"giuirléide; níl soicindí ina dtaispeáint dhigiteach.",
    L"\r\n\r\nPapildomi laikrodžiai\r\nKalendorius su laikrodžiu skirtuke Bendra gali rodyti iki dviejų "
    L"papildomų laikrodžių su savais pavadinimais ir laiko juostomis. Kiekvienas tada rodo ir vietinę savaitės"
    L" dieną. Dydis pasirenkamas atskirai skirtuke Išvaizda arba ciferblato kontekstiniame meniu. Papildomi "
    L"laikrodžiai neturi sekundžių rodyklės. Įtraukimas, pašalinimas ir dydžio keitimas išlaiko prikabinimą "
    L"prie darbo srities kraštų.\r\n\r\nTik dukart spustelėjus tiesiai pagrindinį ciferblatą perjungiama jo "
    L"sekundžių rodyklė. Papildomų laikrodžių meniu yra tik dydžiai. Jie naudoja valdiklio kalbą, laiko "
    L"formatą, šriftus ir poslinkį; skaitmeninis laikas rodomas be sekundžių.",
    L"\r\n\r\nPapildu pulksteņi\r\nKalendārs ar pulksteni cilnē Vispārīgi var rādīt līdz diviem papildu "
    L"pulksteņiem ar saviem nosaukumiem un laika joslām. Tad katrs rāda arī vietējo nedēļas dienu. Lielumu "
    L"izvēlas atsevišķi cilnē Izskats vai ciparnīcas kontekstizvēlnē. Papildu pulksteņiem nav sekunžu "
    L"rādītāja. Pievienošana, noņemšana un lieluma maiņa saglabā piesaisti darba apgabala malām.\r\n\r\nTikai "
    L"dubultklikšķis tieši uz galvenās ciparnīcas pārslēdz tās sekunžu rādītāju. Papildu pulksteņu izvēlnēs ir"
    L" tikai lielumi. Tie izmanto logrīka valodu, laika formātu, fontus un nobīdi; digitālajā laikā nav "
    L"sekunžu.",
    L"\r\n\r\nTovábbi órák\r\nA Naptár órával az Általános fülön legfeljebb két további órát mutathat saját "
    L"névvel és időzónával. Ekkor mindegyik a hét helyi napját is jelzi. A méret külön választható a "
    L"Megjelenés fülön vagy a számlap helyi menüjében. A további óráknak nincs másodpercmutatójuk. Hozzáadás, "
    L"eltávolítás és átméretezés megtartja a munkaterület széleihez csatlakozást.\r\n\r\nCsak a fő számlapra "
    L"közvetlenül történő dupla kattintás kapcsolja a másodpercmutatóját. A további órák menüje csak méretet "
    L"tartalmaz. Közös a minialkalmazás nyelve, időformátuma, betűtípusai és eltolása; digitális idejük "
    L"másodpercek nélküli.",
    L"\r\n\r\nArloġġi addizzjonali\r\nKalendarju bl-arloġġ jista’ juri sa żewġ arloġġi addizzjonali fit-tab "
    L"Ġenerali, bl-ismijiet u ż-żoni tal-ħin tagħhom. Kull wieħed imbagħad juri wkoll il-jum lokali "
    L"tal-ġimgħa. Id-daqs jintgħażel separatament fit-tab Dehra jew mill-menu tal-wiċċ. L-arloġġi addizzjonali"
    L" m’għandhomx id tas-sekondi. Iż-żieda, it-tneħħija u l-bidla fid-daqs iżommu t-twaħħil mat-truf taż-żona"
    L" tax-xogħol.\r\n\r\nKlikk doppju direttament fuq il-wiċċ prinċipali biss jaqleb l-id tas-sekondi tiegħu."
    L" Il-menus tal-arloġġi addizzjonali fihom daqsijiet biss. Dawn jaqsmu l-lingwa, il-format tal-ħin, "
    L"il-fonts u l-kumpens tal-widget; il-wiri diġitali tagħhom ma jurix sekondi.",
    L"\r\n\r\nExtra klokken\r\nKalender met klok kan op Algemeen maximaal twee extra klokken met eigen namen "
    L"en tijdzones tonen. Elke klok toont dan ook zijn lokale weekdag. Kies elke wijzerplaatgrootte "
    L"afzonderlijk op Vormgeving of in het contextmenu. Extra klokken hebben geen secondewijzer. Toevoegen, "
    L"verwijderen en vergroten of verkleinen behoudt de verbinding met de randen van het "
    L"werkgebied.\r\n\r\nAlleen dubbelklikken rechtstreeks op de hoofdwijzerplaat schakelt de secondewijzer "
    L"daarvan. Menu’s van extra klokken bevatten alleen groottes. Zij delen taal, tijdnotatie, lettertypen en "
    L"verschuiving van de widget; hun digitale tijd toont geen seconden.",
    L"\r\n\r\nCeasuri suplimentare\r\nCalendar cu ceas poate afișa în General până la două ceasuri "
    L"suplimentare cu nume și fusuri orare proprii. Fiecare arată atunci și ziua locală a săptămânii. "
    L"Dimensiunea se alege separat în Aspect sau meniul contextual al cadranului. Ceasurile suplimentare nu au"
    L" secundar. Adăugarea, eliminarea și redimensionarea păstrează atașarea la marginile zonei de "
    L"lucru.\r\n\r\nNumai dublul clic direct pe cadranul principal comută secundarul acestuia. Meniurile "
    L"ceasurilor suplimentare conțin doar dimensiuni. Ele folosesc limba, formatul orei, fonturile și "
    L"decalajul widgetului; afișajul digital nu are secunde.",
    L"\r\n\r\nΠρόσθετα ρολόγια\r\nΤο Ημερολόγιο με ρολόι μπορεί στα Γενικά να δείξει έως δύο πρόσθετα ρολόγια "
    L"με δικά τους ονόματα και ζώνες ώρας. Κάθε ρολόι τότε δείχνει και την τοπική ημέρα εβδομάδας. Το μέγεθος "
    L"επιλέγεται χωριστά στην Εμφάνιση ή στο μενού του καντράν. Τα πρόσθετα ρολόγια δεν έχουν δείκτη "
    L"δευτερολέπτων. Προσθήκη, κατάργηση και αλλαγή μεγέθους διατηρούν την προσκόλληση στα άκρα της περιοχής "
    L"εργασίας.\r\n\r\nΜόνο το διπλό κλικ απευθείας στο κύριο καντράν αλλάζει τον δείκτη δευτερολέπτων του. Τα"
    L" πρόσθετα μενού έχουν μόνο μεγέθη. Τα πρόσθετα ρολόγια μοιράζονται γλώσσα, μορφή ώρας, γραμματοσειρές "
    L"και μετατόπιση του στοιχείου· η ψηφιακή ώρα τους δεν έχει δευτερόλεπτα.",
    L"\r\n\r\nDodatni satovi\r\nNa kartici Općenito kalendar sa satom može prikazivati do dva dodatna sata s "
    L"vlastitim nazivima i vremenskim zonama. Tada svaki sat prikazuje i lokalni dan u sedmici. Veličina "
    L"svakog brojčanika bira se zasebno na kartici Izgled ili u njegovu kontekstnom meniju. Dodatni satovi "
    L"nemaju sekundnu kazaljku. Dodavanje, uklanjanje ili promjena veličine čuva priljubljivanje vidžeta uz "
    L"ivice radnog područja.\r\n\r\nSamo dvostruki klik direktno na glavni brojčanik mijenja prikaz njegove "
    L"sekundne kazaljke. Meniji dodatnih satova sadrže samo veličine. Dodatni satovi dijele jezik, oblik "
    L"vremena, fontove i pomak vidžeta; njihov digitalni prikaz nema sekunde.",
    L"\r\n\r\nDodatni satovi\r\nNa kartici Općenito kalendar sa satom može prikazivati do dva dodatna sata s "
    L"vlastitim nazivima i vremenskim zonama. Tada svaki sat prikazuje i lokalni dan u tjednu. Veličina svakog"
    L" brojčanika bira se zasebno na kartici Izgled ili u njegovu kontekstnom izborniku. Dodatni satovi nemaju"
    L" sekundnu kazaljku. Dodavanje, uklanjanje ili promjena veličine čuva priljubljivanje widgeta uz rubove "
    L"radnog područja.\r\n\r\nSamo dvostruki klik izravno na glavni brojčanik mijenja prikaz njegove sekundne "
    L"kazaljke. Izbornici dodatnih satova sadrže samo veličine. Dodatni satovi dijele jezik, oblik vremena, "
    L"fontove i pomak widgeta; njihov digitalni prikaz nema sekunde.",
    L"\r\n\r\nDodatne ure\r\nKoledar z uro lahko na zavihku Splošno prikaže do dve dodatni uri z lastnima "
    L"imenoma in časovnima pasovoma. Vsaka nato kaže tudi svoj krajevni dan v tednu. Velikost številčnice "
    L"izberete posebej na zavihku Videz ali v njenem kontekstnem meniju. Dodatne ure nimajo sekundnega "
    L"kazalca. Dodajanje, odstranjevanje in spreminjanje velikosti ohrani pripetost gradnika na robove "
    L"delovnega območja.\r\n\r\nSekundni kazalec preklopi le dvoklik neposredno na glavno številčnico. Meniji "
    L"dodatnih ur vsebujejo le velikosti. Dodatne ure uporabljajo jezik, obliko časa, pisave in odmik "
    L"gradnika; njihov digitalni čas ne kaže sekund.",
    L"\r\n\r\nDodatni satovi\r\nKalendar sa satom na kartici Opšte može prikazati do dva dodatna sata sa "
    L"sopstvenim nazivima i vremenskim zonama. Svaki tada pokazuje i lokalni dan nedjelje. Veličina brojčanika"
    L" bira se posebno na kartici Izgled ili u njegovom kontekstnom meniju. Dodatni satovi nemaju sekundnu "
    L"kazaljku. Dodavanje, uklanjanje i promjena veličine čuvaju priljepljivanje uz ivice radne "
    L"površine.\r\n\r\nSamo dvoklik neposredno na glavni brojčanik prebacuje njegovu sekundnu kazaljku. Meniji"
    L" dodatnih satova sadrže samo veličine. Oni dijele jezik, oblik vremena, fontove i pomak vidžeta; njihov "
    L"digitalni prikaz nema sekunde.",
    L"\r\n\r\nДадатковыя гадзіннікі\r\nКаляндар з гадзіннікам на ўкладцы «Агульныя» можа мець да двух "
    L"дадатковых гадзіннікаў з уласнымі назвамі і часавымі паясамі. Тады кожны паказвае і свой мясцовы дзень "
    L"тыдня. Памер цыферблата выбіраецца асобна на ўкладцы «Выгляд» або ў яго кантэкстным меню. Дадатковыя "
    L"гадзіннікі не маюць секунднай стрэлкі. Дадаванне, выдаленне і змена памеру захоўваюць прывязку да краёў "
    L"рабочай вобласці.\r\n\r\nСекундная стрэлка пераключаецца толькі падвойнай пстрычкай непасрэдна на "
    L"галоўным цыферблаце. Меню дадатковых гадзіннікаў мае толькі памеры. Яны выкарыстоўваюць мову, фармат "
    L"часу, шрыфты і зрушэнне віджэта; іх лічбавы час не мае секунд.",
    L"\r\n\r\nДопълнителни часовници\r\nКалендарът с часовник може да показва до два допълнителни часовника "
    L"със собствени имена и часови зони чрез раздела „Общи“. Тогава всеки показва и своя местен ден от "
    L"седмицата. Размерът се избира отделно в „Изглед“ или контекстното меню на циферблата. Допълнителните "
    L"часовници нямат секундна стрелка. Добавянето, премахването и промяната на размера запазват прилепването "
    L"към краищата на работната област.\r\n\r\nСамо двойно щракване направо върху главния циферблат превключва"
    L" неговата секундна стрелка. Менютата на допълнителните часовници съдържат само размери. Те споделят "
    L"езика, формата на часа, шрифтовете и отместването на модула; цифровото им време няма секунди.",
    L"\r\n\r\nДополнителни часовници\r\nКалендарот со часовник може да прикаже до два дополнителни часовника "
    L"со свои имиња и временски зони на картичката „Општо“. Тогаш секој го покажува и својот локален ден во "
    L"неделата. Големината на бројчаникот се избира посебно во „Изглед“ или неговото контекстно мени. "
    L"Дополнителните часовници немаат секундна стрелка. Додавањето, отстранувањето и менувањето на големината "
    L"го зачувуваат прилепувањето кон рабовите на работната површина.\r\n\r\nСамо двоен клик непосредно на "
    L"главниот бројчаник ја менува неговата секундна стрелка. Менијата на дополнителните часовници содржат "
    L"само големини. Тие ги делат јазикот, обликот на времето, фонтовите и поместувањето на виџетот; нивното "
    L"дигитално време нема секунди.",
    L"\r\n\r\nДодатни сатови\r\nКалендар са сатом на картици Опште може приказати до два додатна сата са "
    L"сопственим називима и временским зонама. Сваки тада показује и локални дан недеље. Величина бројчаника "
    L"бира се посебно на картици Изглед или у његовом контекстном менију. Додатни сатови немају секундну "
    L"казаљку. Додавање, уклањање и промена величине чувају прилепљивање уз ивице радне површине.\r\n\r\nСамо "
    L"двоклик непосредно на главни бројчаник пребацује његову секундну казаљку. Менији додатних сатова садрже "
    L"само величине. Они деле језик, облик времена, фонтове и помак виџета; њихов дигитални приказ нема "
    L"секунде.",
    L"\r\n\r\nДодаткові годинники: на вкладці «Загальні» для календаря з годинником можна ввімкнути до двох "
    L"додаткових годинників із власними назвами та часовими поясами. Тоді кожен годинник також показує "
    L"місцевий день тижня. Розмір кожного циферблата вибирається окремо на вкладці «Вигляд» або в його "
    L"контекстному меню. Додаткові годинники не мають секундної стрілки. Додавання, видалення або зміна "
    L"розміру годинників зберігає прив’язку віджета до країв робочої області.\r\n\r\nСекундна стрілка "
    L"перемикається лише подвійним клацанням безпосередньо на головному циферблаті. Меню додаткових годинників"
    L" містять лише розміри. Додаткові годинники використовують мову, формат часу, шрифти та зсув віджета; "
    L"їхній цифровий час не містить секунд.",
    L"\r\n\r\nДополнительные часы: на вкладке «Общие» для календаря с часами можно включить до двух "
    L"дополнительных часов с собственными названиями и часовыми поясами. Тогда каждые часы также показывают "
    L"местный день недели. Размер каждого циферблата выбирается отдельно на вкладке «Внешний вид» или в его "
    L"контекстном меню. У дополнительных часов нет секундной стрелки. Добавление, удаление или изменение "
    L"размера часов сохраняет привязку виджета к краям рабочей области.\r\n\r\nСекундная стрелка переключается"
    L" только двойным щелчком непосредственно по главному циферблату. Меню дополнительных часов содержат "
    L"только размеры. Дополнительные часы используют язык, формат времени, шрифты и смещение виджета; их "
    L"цифровое время не содержит секунд."
};

const wchar_t* HELP_TIME_FORMAT_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nFORMÁT ČASU A PÁSMA\r\nFormát času na kartě Obecné nabízí Podle jazyka (výchozí), 12 hodin a 24 "
    L"hodin. Podle jazyka převezme cyklus dané země; ruční volba zůstane zachována při změně jazyka. "
    L"Oddělovače a označení části dne odpovídají jazyku widgetu. Zatržítko AM/PM je ve výchozím stavu zapnuto "
    L"a ve 12hodinovém režimu ovládá pouze označení části dne; není-li v dané kultuře definováno, použije se "
    L"AM/PM. Na celomonitorových hodinách je označení na samostatném spodním řádku. UTC vždy používá 24hodinový "
    L"formát. Pojmenovaná pásma používají občanský čas daného místa včetně "
    L"jeho letního času; offset u názvu odpovídá aktuálnímu datu. Samostatné položky UTC jsou pevné offsety od"
    L" −12:00 do +14:00 po 15 minutách a letní čas nepoužívají.",
    L"\r\n\r\nTIME FORMAT AND TIME ZONES\r\nTime format on the General tab offers Language default (the "
    L"default), 12 hours, and 24 hours. Language default follows the selected culture; a manual "
    L"choice is retained when the widget language changes. Separators and time markers follow the "
    L"widget language. AM/PM is checked by default and controls only the marker in 12-hour mode; "
    L"AM/PM is used when the culture defines no marker. Monitor clocks show the marker on a separate "
    L"line below the time. UTC always uses 24-hour time. "
    L"Named time zones follow local civil time, including local daylight saving time; the offset next "
    L"to the name reflects the current date. Standalone UTC entries are fixed offsets from -12:00 to "
    L"+14:00 in 15-minute steps and do not observe daylight saving time.",
    L"\r\n\r\nZEITFORMAT UND ZEITZONEN\r\nZeitformat auf Allgemein bietet Nach Sprache (Standard), 12 "
    L"Stunden und 24 Stunden. Nach Sprache folgt der gewählten Kultur; eine manuelle Auswahl bleibt "
    L"bei Sprachänderungen erhalten. Trennzeichen und Tageszeitangaben folgen der Widget-Sprache. "
    L"AM/PM ist standardmäßig aktiviert und schaltet im 12-Stunden-Format nur die Tageszeitangabe um; "
    L"ohne kultureigene Angabe wird AM/PM verwendet. Bildschirmuhren zeigen sie in einer eigenen "
    L"Zeile unter der Uhrzeit. UTC verwendet immer das 24-Stunden-Forma"
    L"t. Benannte Zeitzonen folgen der jeweiligen Ortszeit einschließlich Sommerzeit; der "
    L"Versatz neben dem Namen gilt für das aktuelle Datum. Einzelne UTC-Einträge sind feste Versätze "
    L"von −12:00 bis +14:00 in 15-Minuten-Schritten ohne Sommerzeit.",
    L"\r\n\r\nFORMAT DE L’HEURE ET FUSEAUX\r\nFormat de l’heure dans Général propose Selon la langue (par "
    L"défaut), 12 heures et 24 heures. Le choix manuel est conservé lors d’un changement de langue. "
    L"Les séparateurs et indications suivent la langue du widget. AM/PM est coché par défaut et "
    L"commande uniquement l’indication en mode 12 heures ; AM/PM est utilisé si la culture n’en "
    L"définit aucune. Les horloges plein écran placent cette indication sur une ligne sous l’heure. "
    L"UTC utilise toujours le format 24 heures. Les fuseaux nommés "
    L"suivent l’heure civile locale, y compris l’heure d’été ; le décalage indiqué correspond à la "
    L"date actuelle. Les entrées UTC seules sont des décalages fixes de −12:00 à +14:00 par pas de 15 "
    L"minutes, sans heure d’été.",
    L"\r\n\r\nFORMATO DE HORA Y ZONAS HORARIAS\r\nFormato de hora en General ofrece Según el idioma "
    L"(predeterminado), 12 horas y 24 horas. La elección manual se conserva al cambiar el idioma. Los "
    L"separadores e indicadores siguen el idioma del widget. AM/PM está marcado de forma "
    L"predeterminada y controla solo el indicador en modo de 12 horas; se usa AM/PM si la cultura no "
    L"define ninguno. Los relojes de monitor muestran el indicador en una línea debajo de la hora. "
    L"UTC siempre usa el formato de 24 horas. Las zonas con nombre "
    L"siguen la hora civil local, incluido el horario de verano; el desfase indicado corresponde a la "
    L"fecha actual. Las entradas UTC independientes son desfases fijos de −12:00 a +14:00 en pasos de "
    L"15 minutos, sin horario de verano.",
    L"\r\n\r\nFORMATO DELL’ORA E FUSI ORARI\r\nFormato ora in Generali offre Secondo la lingua (predefinito), "
    L"12 ore e 24 ore. La scelta manuale viene mantenuta quando cambia la lingua. Separatori e indicatori "
    L"seguono la lingua del widget. AM/PM è selezionato per impostazione predefinita e controlla solo "
    L"l’indicatore nel formato a 12 ore; si usa AM/PM se la cultura non ne definisce uno. Gli orologi a "
    L"schermo intero mostrano l’indicatore su una riga sotto l’ora. UTC usa sempre il formato a 24 ore"
    L". I fusi con nome seguono l’ora civile locale, inclusa l’ora legale; lo "
    L"scostamento indicato corrisponde alla data attuale. Le voci UTC separate sono scostamenti fissi da "
    L"−12:00 a +14:00 a intervalli di 15 minuti, senza ora legale.",
    L"\r\n\r\nFORMAT CZASU I STREFY\r\nFormat czasu na karcie Ogólne oferuje Według języka (domyślnie), 12 "
    L"godzin i 24 godziny. Ręczny wybór pozostaje zachowany przy zmianie języka. Separatory i "
    L"oznaczenia odpowiadają językowi widżetu. AM/PM jest domyślnie zaznaczone i steruje tylko "
    L"oznaczeniem w trybie 12-godzinnym; gdy kultura nie określa oznaczenia, używane jest AM/PM. "
    L"Zegary pełnoekranowe pokazują je w osobnym wierszu pod czasem. UTC zawsze używa formatu 24-godzinneg"
    L"o. Nazwane strefy stosują lokalny czas urzędowy, w tym czas letni; "
    L"przesunięcie obok nazwy odpowiada bieżącej dacie. Osobne wpisy UTC to stałe przesunięcia od "
    L"−12:00 do +14:00 co 15 minut, bez czasu letniego.",
    L"\r\n\r\nFORMÁT ČASU A PÁSMA\r\nFormát času na karte Všeobecné ponúka Podľa jazyka (predvolené), 12 "
    L"hodín a 24 hodín. Ručná voľba zostane zachovaná pri zmene jazyka. Oddeľovače a označenia časti "
    L"dňa zodpovedajú jazyku widgetu. AM/PM je predvolene začiarknuté a v 12-hodinovom režime ovláda "
    L"iba označenie časti dňa; ak ho kultúra nedefinuje, použije sa AM/PM. Celomonitorové hodiny ho "
    L"zobrazujú na samostatnom riadku pod časom. UTC vždy používa 24-hodinový formá"
    L"t. Pomenované pásma používajú občiansky čas daného miesta vrátane jeho letného času; "
    L"posun pri názve zodpovedá aktuálnemu dátumu. Samostatné položky UTC sú pevné posuny od −12:00 "
    L"do +14:00 po 15 minútach bez letného času.",
    L"\r\n\r\nTIME FORMAT AND TIME ZONES\r\nTime format on the General tab offers Language default (the "
    L"default), 12 hours, and 24 hours. Language default follows the selected culture; a manual "
    L"choice is retained when the widget language changes. Separators and time markers follow the "
    L"widget language. AM/PM is checked by default and controls only the marker in 12-hour mode; "
    L"AM/PM is used when the culture defines no marker. Monitor clocks show the marker on a separate "
    L"line below the time. UTC always uses 24-hour time. "
    L"Named time zones follow local civil time, including local daylight saving time; the offset next "
    L"to the name reflects the current date. Standalone UTC entries are fixed offsets from -12:00 to "
    L"+14:00 in 15-minute steps and do not observe daylight saving time.",
    L"\r\n\r\nTIME FORMAT AND TIME ZONES\r\nTime format on the General tab offers Language default (the "
    L"default), 12 hours, and 24 hours. Language default follows the selected culture; a manual "
    L"choice is retained when the widget language changes. Separators and time markers follow the "
    L"widget language. AM/PM is checked by default and controls only the marker in 12-hour mode; "
    L"AM/PM is used when the culture defines no marker. Monitor clocks show the marker on a separate "
    L"line below the time. UTC always uses 24-hour time. "
    L"Named time zones follow local civil time, including local daylight saving time; the offset next "
    L"to the name reflects the current date. Standalone UTC entries are fixed offsets from -12:00 to "
    L"+14:00 in 15-minute steps and do not observe daylight saving time.",
    L"\r\n\r\nFORMATO DA HORA E FUSOS HORÁRIOS\r\nFormato da hora em Geral oferece Conforme o idioma "
    L"(predefinição), 12 horas e 24 horas. A escolha manual é mantida quando o idioma muda. Os "
    L"separadores e indicadores seguem o idioma do widget. AM/PM está selecionado por predefinição e "
    L"controla apenas o indicador no modo de 12 horas; usa-se AM/PM se a cultura não definir nenhum. "
    L"Os relógios de monitor mostram o indicador numa linha abaixo da hora. UTC usa sempre o formato de 24 horas"
    L". Os fusos com nome seguem a hora civil local, incluindo a "
    L"hora de verão; o desvio junto ao nome corresponde à data atual. As entradas UTC isoladas são "
    L"desvios fixos de −12:00 a +14:00 em intervalos de 15 minutos, sem hora de verão.",
    L"\r\n\r\nTIDSFORMAT OG TIDSSONER\r\nTidsformat på Generelt tilbyr Etter språk (standard), 12 timer og "
    L"24 timer. Et manuelt valg beholdes når språket endres. Skilletegn og tidsmarkører følger "
    L"widgetens språk. AM/PM er på som standard og styrer bare markøren i 12-timersformat; AM/PM "
    L"brukes hvis kulturen ikke har en egen markør. Skjermklokker viser markøren på en egen linje "
    L"under tiden. UTC bruker alltid 24-timersformat. Navngitte "
    L"tidssoner følger lokal tid, inkludert sommertid; forskyvningen ved navnet gjelder dagens dato. "
    L"Egne UTC-oppføringer er faste forskyvninger fra −12:00 til +14:00 i trinn på 15 minutter, uten "
    L"sommertid.",
    L"\r\n\r\nTIDSFORMAT OCH TIDSZONER\r\nTidsformat på Allmänt erbjuder Enligt språk (standard), 12 timmar "
    L"och 24 timmar. Ett manuellt val behålls när språket ändras. Avgränsare och tidsbeteckningar "
    L"följer widgetens språk. AM/PM är på som standard och styr bara beteckningen i 12-timmarsformat; "
    L"AM/PM används om kulturen saknar en egen beteckning. Bildskärmsklockor visar den på en egen rad "
    L"under tiden. UTC använder alltid 24-timmarsformat. "
    L"Namngivna tidszoner följer lokal tid, inklusive sommartid; förskjutningen vid namnet gäller "
    L"dagens datum. Separata UTC-poster är fasta förskjutningar från −12:00 till +14:00 i steg om 15 "
    L"minuter, utan sommartid.",
    L"\r\n\r\nAIKAMUOTO JA AIKAVYÖHYKKEET\r\nYleiset-välilehden Aikamuoto tarjoaa Kielen mukaan (oletus), "
    L"12 tuntia ja 24 tuntia. Käsin tehty valinta säilyy kielen vaihtuessa. Erottimet ja merkinnät "
    L"noudattavat pienoisohjelman kieltä. AM/PM on oletusarvoisesti valittu ja ohjaa vain merkintää "
    L"12 tunnin muodossa; AM/PM-merkintää käytetään, jos kulttuurilla ei ole omaa. Koko näytön kellot "
    L"näyttävät merkinnän ajan alla omalla rivillään. UTC käyttää aina 24 tunnin muotoa"
    L". Nimetyt aikavyöhykkeet noudattavat paikallista aikaa "
    L"kesäaikoineen; nimen vieressä oleva siirtymä vastaa nykyistä päivämäärää. Erilliset "
    L"UTC-valinnat ovat kiinteitä siirtymiä −12:00:sta +14:00:aan 15 minuutin välein ilman kesäaikaa.",
    L"\r\n\r\nTIDSFORMAT OG TIDSZONER\r\nTidsformat på Generelt tilbyder Efter sprog (standard), 12 timer "
    L"og 24 timer. Et manuelt valg bevares, når sproget ændres. Separatorer og tidsmarkører følger "
    L"widgetens sprog. AM/PM er slået til som standard og styrer kun markøren i 12-timersformat; "
    L"AM/PM bruges, hvis kulturen ikke har en egen markør. Skærmure viser markøren på en separat "
    L"linje under tiden. UTC bruger altid 24-timersformat. "
    L"Navngivne tidszoner følger lokal tid inklusive sommertid; forskydningen ved navnet gælder den "
    L"aktuelle dato. Separate UTC-poster er faste forskydninger fra −12:00 til +14:00 i trin på 15 "
    L"minutter uden sommertid.",
    L"\r\n\r\nTÍMASNIÐ OG TÍMABELTI\r\nTímasnið á Almennt býður Samkvæmt tungumáli (sjálfgefið), 12 "
    L"klukkustundir og 24 klukkustundir. Handvirkt val helst við breytingu á tungumáli. "
    L"Aðgreiningarmerki og tímamerkingar fylgja tungumáli græjunnar. AM/PM er sjálfgefið virkt og "
    L"stjórnar aðeins merkingunni í 12 klukkustunda sniði; AM/PM er notað ef menningarsvæðið "
    L"skilgreinir enga merkingu. Skjáklukkur sýna hana á sér línu undir tímanum. UTC notar alltaf 24 "
    L"klukkustunda snið. Nafngreind tímabelti fylgja staðartíma með "
    L"sumartíma; hliðrunin við nafnið gildir fyrir daginn í dag. Sérstakar UTC-færslur eru fastar "
    L"hliðranir frá −12:00 til +14:00 í 15 mínútna skrefum án sumartíma.",
    L"\r\n\r\nSAAT BİÇİMİ VE SAAT DİLİMLERİ\r\nGenel sekmesindeki Saat biçimi, Dile göre (varsayılan), 12 "
    L"saat ve 24 saat seçeneklerini sunar. Dil değiştiğinde elle seçilen düzen korunur. Ayırıcılar ve "
    L"göstergeler araç diline uyar. AM/PM varsayılan olarak işaretlidir ve 12 saatlik düzende "
    L"yalnızca göstergeyi denetler; kültür bir gösterge tanımlamıyorsa AM/PM kullanılır. Tam ekran "
    L"saatler göstergeyi saatin altında ayrı bir satırda gösterir. UTC her zaman 24 saatlik düzeni "
    L"kullanır. Adlandırılmış saat dilimleri, "
    L"yaz saati dahil yerel resmi saati izler; adın yanındaki fark güncel tarihe aittir. Ayrı UTC "
    L"girdileri −12:00 ile +14:00 arasında 15 dakikalık adımlarla sabit farklardır ve yaz saati "
    L"uygulamaz.",
    L"\r\n\r\nKellaajavorming ja ajavööndid\r\nKellaajavorming vahekaardil Üldine pakub Keele vaikesätet, 12 "
    L"tundi ja 24 tundi. Esimene järgib vidina keelt; käsivalik säilib keele vahetamisel. Eraldajad ja "
    L"ajatähised järgivad keelt. AM/PM on vaikimisi sees ja juhib ainult 12-tunnise kuva tähist; keele oma "
    L"tähise puudumisel kasutatakse AM/PM-i. Ekraanikell kuvab tähise eraldi real kellaaja all. UTC kasutab "
    L"alati 24-tunnist vormingut"
    L". Nimega ajavööndid arvestavad kohalikku ja suveaega; nime kõrval olev nihe kehtib praegusele "
    L"kuupäevale. Eraldi UTC-valikud on püsinihked −12:00 kuni +14:00 15-minutilise sammuga, ilma suveajata.",
    L"\r\n\r\nFormáid ama agus criosanna ama\r\nTugann Formáid ama ar Ginearálta De réir na teanga "
    L"(réamhshocrú), 12 uair agus 24 uair. Fanann rogha láimhe tar éis athrú teanga. Leanann deighilteoirí "
    L"agus marcóirí ama an teanga. Tá AM/PM cumasaithe ar dtús agus ní rialaíonn sé ach an marcóir i mód 12 "
    L"uair; mura bhfuil marcóirí ag an teanga, úsáidtear AM/PM. Taispeánann cloig scáileáin é ar shraith ar "
    L"leith faoin am. Úsáideann UTC formáid 24 uair i gcónaí"
    L". Leanann criosanna ainmnithe a rialacha áitiúla agus "
    L"ama samhraidh; baineann an fritháireamh leis an dáta reatha. Is fritháirimh sheasta ó −12:00 go +14:00 i"
    L" gcéimeanna 15 nóiméad iad na míreanna UTC ar leith, gan am samhraidh.",
    L"\r\n\r\nLaiko formatas ir laiko juostos\r\nLaiko formatas skirtuke Bendra siūlo Pagal kalbą (numatyta), "
    L"12 valandų ir 24 valandos. Rankinis pasirinkimas išlieka pakeitus kalbą. Skyrikliai ir laiko žymos "
    L"priklauso nuo valdiklio kalbos. AM/PM iš pradžių įjungta ir valdo tik 12 valandų formato žymą; jei kalba"
    L" neturi savų žymų, naudojama AM/PM. Ekrano laikrodžiai žymą rodo atskiroje eilutėje po laiku. UTC visada"
    L" naudoja 24 valandų formatą"
    L". Vardinės juostos laikosi vietinio ir vasaros laiko taisyklių; poslinkis atitinka dabartinę datą."
    L" Atskiros UTC parinktys yra pastovūs poslinkiai nuo −12:00 iki +14:00 kas 15 minučių be vasaros laiko.",
    L"\r\n\r\nLaika formāts un laika joslas\r\nLaika formāts cilnē Vispārīgi piedāvā Atbilstoši valodai "
    L"(noklusējums), 12 stundas un 24 stundas. Manuālā izvēle paliek pēc valodas maiņas. Atdalītāji un laika "
    L"apzīmējumi atbilst logrīka valodai. AM/PM sākumā ieslēgts un ietekmē tikai apzīmējumu 12 stundu režīmā; "
    L"ja valodai nav savu apzīmējumu, lieto AM/PM. Ekrāna pulksteņi to rāda atsevišķā rindā zem laika. UTC "
    L"vienmēr izmanto 24 stundu formātu. Nosauktās "
    L"joslas ievēro vietējo un vasaras laiku; nobīde atbilst pašreizējam datumam. Atsevišķās UTC izvēles ir "
    L"nemainīgas nobīdes no −12:00 līdz +14:00 ar 15 minūšu soli bez vasaras laika.",
    L"\r\n\r\nIdőformátum és időzónák\r\nAz Általános fül Időformátum beállítása Nyelv szerinti "
    L"(alapértelmezett), 12 órás vagy 24 órás. A kézi választás nyelvváltáskor is megmarad. Az elválasztók és "
    L"időjelölések a minialkalmazás nyelvét követik. Az AM/PM alapból bekapcsolt, csak a 12 órás jelölést "
    L"szabályozza; saját nyelvi jelölés hiányában AM/PM használatos. A képernyőórák külön sorban, az idő alatt"
    L" jelzik. Az UTC mindig 24 órás formátumot használ"
    L". A név szerinti zónák követik a helyi és nyári időszámítást; az eltolás az aktuális dátumra "
    L"érvényes. A külön UTC-elemek állandó eltolások −12:00 és +14:00 között 15 perces lépéssel, nyári "
    L"időszámítás nélkül.",
    L"\r\n\r\nFormat tal-ħin u żoni tal-ħin\r\nFormat tal-ħin fit-tab Ġenerali joffri Skont il-lingwa "
    L"(default), 12-il siegħa u 24 siegħa. Għażla manwali tibqa’ wara bidla fil-lingwa. Is-separaturi u "
    L"l-markaturi tal-ħin isegwu l-lingwa tal-widget. AM/PM huwa attivat inizjalment u jikkontrolla biss "
    L"il-markatur fil-format ta’ 12-il siegħa; jekk il-lingwa m’għandhiex markaturi tagħha, jintuża AM/PM. "
    L"L-arloġġi tal-iskrin juruh f’ringiela separata taħt il-ħin. UTC dejjem juża l-format ta’ 24 siegħa"
    L". Żoni msemmija jsegwu r-regoli lokali u "
    L"tal-ħin tas-sajf; il-kumpens japplika għad-data kurrenti. L-għażliet UTC separati huma kumpensi fissi "
    L"minn −12:00 sa +14:00 f’passi ta’ 15-il minuta, mingħajr ħin tas-sajf.",
    L"\r\n\r\nTijdnotatie en tijdzones\r\nTijdnotatie op Algemeen biedt Volgens taal (standaard), 12 uur en 24"
    L" uur. Een handmatige keuze blijft na een taalwijziging behouden. Scheidingstekens en tijdsaanduidingen "
    L"volgen de widgettaal. AM/PM is aanvankelijk ingeschakeld en regelt alleen de aanduiding bij 12 uur; "
    L"zonder eigen taalaanduidingen wordt AM/PM gebruikt. Schermklokken tonen deze in een aparte rij onder de "
    L"tijd. UTC gebruikt altijd de 24-uursnota"
    L"tie. Benoemde zones volgen lokale tijd en zomertijd; de verschuiving geldt voor de huidige "
    L"datum. Aparte UTC-items zijn vaste verschuivingen van −12:00 tot +14:00 in stappen van 15 minuten, "
    L"zonder zomertijd.",
    L"\r\n\r\nFormatul orei și fusuri orare\r\nFormat oră din General oferă Conform limbii (implicit), 12 ore "
    L"și 24 de ore. Alegerea manuală rămâne după schimbarea limbii. Separatorii și marcajele urmează limba "
    L"widgetului. AM/PM este inițial activat și controlează numai marcajul în modul de 12 ore; dacă limba nu "
    L"are marcaje proprii, se utilizează AM/PM. Ceasurile pe ecran îl arată pe un rând separat sub oră. UTC "
    L"folosește întotdeauna formatul de 24 de ore"
    L". Fusurile denumite urmează ora locală și ora de vară; decalajul este pentru data curentă. "
    L"Opțiunile UTC separate sunt decalaje fixe de la −12:00 la +14:00 în pași de 15 minute fără oră de vară.",
    L"\r\n\r\nΜορφή ώρας και ζώνες ώρας\r\nΗ Μορφή ώρας στα Γενικά προσφέρει Σύμφωνα με τη γλώσσα "
    L"(προεπιλογή), 12 ώρες και 24 ώρες. Η χειροκίνητη επιλογή διατηρείται μετά από αλλαγή γλώσσας. "
    L"Διαχωριστικά και ενδείξεις ακολουθούν τη γλώσσα του στοιχείου. Το AM/PM είναι αρχικά ενεργό και ελέγχει "
    L"μόνο την ένδειξη στη 12ωρη μορφή· χωρίς ενδείξεις της γλώσσας χρησιμοποιείται AM/PM. Τα ρολόγια οθόνης "
    L"τη δείχνουν σε χωριστή γραμμή κάτω από την ώρα. Το UTC χρησιμοποιεί πάντα 24ωρη μορφή"
    L". Οι ονομαστικές ζώνες ακολουθούν"
    L" τοπική και θερινή ώρα· η μετατόπιση ισχύει για την τρέχουσα ημερομηνία. Οι χωριστές επιλογές UTC είναι "
    L"σταθερές μετατοπίσεις από −12:00 έως +14:00 ανά 15 λεπτά χωρίς θερινή ώρα.",
    L"\r\n\r\nOblik vremena i vremenske zone\r\nOblik vremena na kartici Općenito nudi Prema jeziku "
    L"(podrazumijevano), 12 sati i 24 sata. Prema jeziku slijedi odabranu kulturu; ručni se izbor čuva nakon "
    L"promjene jezika vidžeta. Razdjelnici i oznake vremena prate jezik vidžeta. AM/PM je podrazumijevano "
    L"označen i upravlja samo oznakom u 12-satnom prikazu; ako kultura nema vlastite oznake, koristi se AM/PM."
    L" Satovi na ekranu prikazuju oznaku u zasebnom redu ispod vremena. UTC uvijek koristi 24-satni oblik"
    L". "
    L"Imenovane vremenske zone prate lokalno vrijeme i ljetno računanje vremena; pomak uz naziv odgovara "
    L"trenutnom datumu. Zasebne stavke UTC predstavljaju stalne pomake od -12:00 do +14:00 u koracima od 15 "
    L"minuta, bez ljetnog računanja vremena.",
    L"\r\n\r\nOblik vremena i vremenske zone\r\nOblik vremena na kartici Općenito nudi Prema jeziku (zadano), "
    L"12 sati i 24 sata. Prema jeziku slijedi odabranu kulturu; ručni se izbor čuva nakon promjene jezika "
    L"widgeta. Razdjelnici i oznake vremena prate jezik widgeta. AM/PM je zadano označen i upravlja samo "
    L"oznakom u 12-satnom prikazu; ako kultura nema vlastite oznake, koristi se AM/PM. Satovi na zaslonu "
    L"prikazuju oznaku u zasebnom retku ispod vremena. UTC uvijek koristi 24-satni oblik"
    L". Imenovane vremenske "
    L"zone prate lokalno vrijeme i ljetno računanje vremena; pomak uz naziv odgovara trenutačnom datumu. "
    L"Zasebne stavke UTC predstavljaju stalne pomake od -12:00 do +14:00 u koracima od 15 minuta, bez ljetnog "
    L"računanja vremena.",
    L"\r\n\r\nOblika časa in časovni pasovi\r\nOblika časa na zavihku Splošno ponuja Glede na jezik "
    L"(privzeto), 12 ur in 24 ur. Privzeta možnost sledi jeziku gradnika, ročna izbira pa ostane tudi po "
    L"spremembi jezika. Ločila in časovne oznake sledijo jeziku. AM/PM je privzeto označen in določa le prikaz"
    L" oznake v 12-urnem načinu. Če jezik nima svoje oznake, se uporabi AM/PM. Ure na zaslonu jo kažejo v "
    L"ločeni vrstici pod časom. UTC vedno uporablja 24-urni prikaz"
    L". Imenovani pasovi sledijo krajevnemu času in poletnemu času; odmik "
    L"ob imenu velja za trenutni datum. Samostojne izbire UTC so stalni odmiki od -12:00 do +14:00 v korakih "
    L"po 15 minut brez poletnega časa.",
    L"\r\n\r\nOblik vremena i vremenske zone\r\nOblik vremena na kartici Opšte nudi Prema jeziku "
    L"(podrazumijevano), 12 sati i 24 sata. Prva opcija prati jezik, a ručni izbor ostaje nakon njegove "
    L"promjene. Razdvajači i oznake vremena prate jezik vidžeta. AM/PM je prvobitno uključen i upravlja samo "
    L"oznakom u 12-časovnom režimu; ako jezik nema sopstvene oznake, koristi se AM/PM. Satovi na monitoru "
    L"prikazuju oznaku u zasebnom redu ispod vremena. UTC uvijek koristi 24-časovni prikaz"
    L". Imenovane zone prate lokalno i "
    L"ljetnje računanje vremena; pomak uz naziv važi za trenutni datum. Zasebne stavke UTC su stalni pomaci od"
    L" -12:00 do +14:00 u koracima od 15 minuta bez ljetnjeg računanja vremena.",
    L"\r\n\r\nФармат часу і часавыя паясы\r\n«Фармат часу» на ўкладцы «Агульныя» прапануе «Паводле мовы» "
    L"(прадвызначаны), «12 гадзін» і «24 гадзіны». Першы варыянт адпавядае мове, ручны выбар захоўваецца пасля"
    L" яе змены. Раздзяляльнікі і пазначэнні часу адпавядаюць мове віджэта. AM/PM спачатку ўключаны і кіруе "
    L"толькі пазначэннем у 12-гадзінным рэжыме; калі мова не мае ўласнага пазначэння, ужываецца AM/PM. "
    L"Гадзіннікі на маніторы паказваюць яго асобным радком пад часам. UTC заўсёды выкарыстоўвае 24-гадзінны "
    L"фармат. Іменаваныя "
    L"паясы ўлічваюць мясцовы і летні час; зрушэнне каля назвы адпавядае бягучай даце. Асобныя пункты UTC "
    L"задаюць пастаянныя зрушэнні ад -12:00 да +14:00 з крокам 15 хвілін без летняга часу.",
    L"\r\n\r\nФормат на часа и часови зони\r\n„Формат на часа“ в раздела „Общи“ предлага „Според езика“ (по "
    L"подразбиране), „12 часа“ и „24 часа“. Първата опция следва езика; ръчният избор се запазва след смяната "
    L"му. Разделителите и означенията следват езика на модула. AM/PM е включено по подразбиране и управлява "
    L"само означението в 12-часов режим; ако езикът няма свое означение, се използва AM/PM. Часовниците на "
    L"монитор го показват на отделен ред под часа. UTC винаги използва 24-часов формат"
    L". Именуваните зони следват местното време и "
    L"лятното часово време; отместването до името е за текущата дата. Отделните записи UTC са постоянни "
    L"отмествания от -12:00 до +14:00 на стъпки от 15 минути без лятно часово време.",
    L"\r\n\r\nОблик на времето и временски зони\r\n„Облик на времето“ во „Општо“ нуди „Според јазикот“ "
    L"(стандардно), „12 часа“ и „24 часа“. Првата опција го следи јазикот, а рачниот избор останува по "
    L"неговата промена. Разделувачите и ознаките го следат јазикот на виџетот. AM/PM е стандардно вклучено и "
    L"ја менува само ознаката во 12-часовен режим; ако јазикот нема свои ознаки, се користи AM/PM. Часовниците"
    L" на монитор ја покажуваат во одделен ред под времето. UTC секогаш користи 24-часовен облик"
    L". Именуваните зони"
    L" го следат локалното и летното сметање на времето; поместувањето до името важи за тековниот датум. "
    L"Одделните ставки UTC се постојани поместувања од -12:00 до +14:00 во чекори од 15 минути без летно "
    L"сметање на времето.",
    L"\r\n\r\nОблик времена и временске зоне\r\nОблик времена на картици Опште нуди Према језику "
    L"(подразумевано), 12 сати и 24 сата. Прва опција прати језик, а ручни избор остаје након његове промене. "
    L"Раздвајачи и ознаке времена прате језик виџета. AM/PM је првобитно укључен и управља само ознаком у "
    L"12-часовном режиму; ако језик нема сопствене ознаке, користи се AM/PM. Сатови на монитору приказују "
    L"ознаку у засебном реду испод времена. UTC увек користи 24-часовни приказ"
    L". Именоване зоне прате локално и летње "
    L"рачунање времена; помак уз назив важи за тренутни датум. Засебне ставке UTC су стални помаци од -12:00 "
    L"до +14:00 у корацима од 15 минута без летњег рачунања времена.",
    L"\r\n\r\nФОРМАТ ЧАСУ ТА ЧАСОВІ ПОЯСИ\r\nПараметр «Формат часу» на вкладці «Загальні» пропонує «За мовою» "
    L"(типове значення), «12 годин» і «24 години». Перший варіант відповідає вибраній мові; ручний вибір "
    L"зберігається після зміни мови віджета. Роздільники та позначення часу відповідають мові віджета. "
    L"Прапорець AM/PM спочатку встановлено; він керує лише позначенням у 12-годинному режимі. Якщо мова не має "
    L"власного позначення, використовується AM/PM. Годинники на моніторі показують його окремим рядком під "
    L"часом. UTC завжди використовує 24-годинний формат. Іменовані часові "
    L"пояси враховують місцевий час і перехід на літній час; зсув поряд із назвою відповідає поточній даті. "
    L"Окремі пункти UTC задають фіксовані зсуви від -12:00 до +14:00 із кроком 15 хвилин без переходу на літній"
    L" час.",
    L"\r\n\r\nФОРМАТ ВРЕМЕНИ И ЧАСОВЫЕ ПОЯСА\r\nПараметр «Формат времени» на вкладке «Общие» предлагает «По "
    L"языку» (по умолчанию), «12 часов» и «24 часа». Первый вариант соответствует выбранному языку; ручной "
    L"выбор сохраняется после смены языка виджета. Разделители и обозначения времени соответствуют языку "
    L"виджета. Флажок AM/PM изначально установлен; он управляет только обозначением в 12-часовом режиме. Если у"
    L" языка нет собственного обозначения, используется AM/PM. Часы на мониторе показывают его отдельной "
    L"строкой под временем. UTC всегда использует 24-часовой формат. "
    L"Именованные часовые пояса учитывают местное время и переход на летнее время; смещение рядом с названием "
    L"соответствует текущей дате. Отдельные пункты UTC задают фиксированные смещения от -12:00 до +14:00 с "
    L"шагом 15 минут без перехода на летнее время."
};

const wchar_t* HELP_TIME_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZDROJ ČASU\r\nNa kartě Čas lze pro celou aplikaci, tedy společně pro všechny widgety, vybrat "
    L"systémový čas Windows nebo čas ze zadaných serverů NTP. NTP koriguje pouze čas zobrazovaný v CalClock; "
    L"systémové hodiny Windows se nikdy nemění. Dokud nebyl získán platný údaj, používá se systémový čas. NTP "
    L"je výchozí. Automatická sada volí podle systémové oblasti české a slovenské servery, PTB pro Evropu nebo"
    L" celosvětový fond. Více měření se filtruje podle síťového zpoždění a odlehlých odpovědí. Synchronizovat "
    L"nyní spustí nové měření okamžitě.\r\n\r\nPo synchronizaci hodiny CalClock pokračují nezávisle na "
    L"pozdějších změnách systémového času Windows. Při výpadku spojení nebo změně serverů pokračují od "
    L"poslední platné synchronizace až do získání nové odpovědi; stav se uchovává do ukončení "
    L"aplikace.\r\n\r\nZÁZNAM SYNCHRONIZACE NTP\r\nNa kartě Čas je záznam dotazů na servery NTP od spuštění "
    L"aplikace. Každý záznam obsahuje datum a místní čas počítače, server a stav. OK označuje platnou odpověď "
    L"a θ její odchylku vůči systémovému času Windows. ERR uvádí důvod neúspěchu a případný chybový kód. "
    L"Poslední záznam skupiny obsahuje také výslednou odchylku Θ, pokud se podařilo získat použitelná "
    L"měření.\r\n\r\nOdchylky se zobrazují v milisekundách se čtyřmi desetinnými místy. Kladná hodnota "
    L"znamená, že čas serveru je vůči Windows napřed; záporná, že je pozadu. Výsledná odchylka Θ zohledňuje "
    L"přijatá měření a je uvedena také ve stavu synchronizace.\r\n\r\nUložit log uloží záznamy do CSV včetně "
    L"odchylek a důvodů chyb. Záznamy se mezi spuštěními neuchovávají; chcete-li je zachovat, uložte je před "
    L"ukončením aplikace.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP servers for the "
    L"whole application and therefore for all widgets. NTP corrects only the time displayed by CalClock; the "
    L"Windows clock is never changed. System time is used until the first valid reply. NTP is the default. The"
    L" automatic set chooses Czech and Slovak servers, PTB for Europe, or the global pool according to the "
    L"system region. Multiple measurements are filtered by network delay and outlying replies. Synchronize now"
    L" starts a fresh measurement immediately.\r\n\r\nAfter synchronization, CalClock keeps time independently"
    L" of later changes to Windows system time. If the connection fails or servers change, it continues from "
    L"the last valid synchronization until a new reply arrives; this state is retained until the application "
    L"closes.\r\n\r\nNTP SYNCHRONIZATION LOG\r\nThe Time tab records NTP server queries since the application "
    L"started. Each entry contains the date and local computer time, server, and status. OK identifies a valid"
    L" reply, with θ showing its offset from Windows system time. ERR gives the failure reason and any error "
    L"code. The final entry in a query group also shows the combined offset Θ when usable measurements are "
    L"available.\r\n\r\nOffsets are displayed in milliseconds with four decimal places. A positive value means"
    L" the server clock is ahead of Windows; a negative value means it is behind. The combined offset Θ "
    L"reflects the accepted measurements and is also shown in the synchronization status.\r\n\r\nSave log "
    L"exports the records to CSV, including offsets and failure details. Records are not retained between "
    L"application sessions; save them before exiting if you want to keep them.",
    L"\r\n\r\nZEITQUELLE\r\nAuf der Registerkarte Zeit wird für die gesamte Anwendung und damit für alle "
    L"Widgets die Windows-Systemzeit oder die Zeit der eingestellten NTP-Server gewählt. NTP korrigiert nur "
    L"die in CalClock angezeigte Zeit; die Windows-Uhr wird nie geändert. Bis zur ersten gültigen Antwort wird"
    L" die Systemzeit verwendet. NTP ist voreingestellt. Die automatische Gruppe wählt nach der Systemregion "
    L"die tschechisch-slowakischen Server, PTB für Europa oder den globalen Pool. Mehrere Messungen werden "
    L"nach Netzverzögerung und Ausreißern gefiltert. Jetzt synchronisieren startet sofort eine neue "
    L"Messung.\r\n\r\nNach der Synchronisierung läuft die CalClock-Uhr unabhängig von späteren Änderungen der "
    L"Windows-Systemzeit weiter. Bei einem Verbindungsausfall oder Serverwechsel läuft sie ab der letzten "
    L"gültigen Synchronisierung weiter, bis eine neue Antwort vorliegt; dieser Zustand bleibt bis zum Beenden "
    L"der Anwendung erhalten.\r\n\r\nNTP-SYNCHRONISIERUNGSPROTOKOLL\r\nDie Registerkarte Zeit protokolliert "
    L"NTP-Serverabfragen seit dem Programmstart. Jeder Eintrag enthält Datum und lokale Computerzeit, Server "
    L"und Status. OK bezeichnet eine gültige Antwort; θ zeigt deren Abweichung von der Windows-Systemzeit. ERR"
    L" nennt den Fehlergrund und gegebenenfalls einen Fehlercode. Der letzte Eintrag einer Abfragegruppe "
    L"enthält auch die berechnete Abweichung Θ, sofern verwertbare Messungen vorliegen.\r\n\r\nAbweichungen "
    L"werden in Millisekunden mit vier Nachkommastellen angezeigt. Ein positiver Wert bedeutet, dass die "
    L"Serveruhr Windows voraus ist; ein negativer Wert bedeutet, dass sie nachgeht. Θ berücksichtigt die "
    L"angenommenen Messungen und wird auch im Synchronisierungsstatus angezeigt.\r\n\r\nProtokoll speichern "
    L"exportiert die Einträge einschließlich Abweichungen und Fehlerdetails als CSV. Einträge werden nicht "
    L"über Programmstarts hinweg aufbewahrt; speichern Sie sie vor dem Beenden, wenn Sie sie behalten möchten.",
    L"\r\n\r\nSOURCE DE L’HEURE\r\nL’onglet Heure sélectionne l’heure système Windows ou les serveurs NTP "
    L"configurés pour toute l’application, donc pour tous les widgets. NTP corrige uniquement l’heure affichée"
    L" par CalClock ; l’horloge Windows n’est jamais modifiée. L’heure système est utilisée jusqu’à la "
    L"première réponse valide. NTP est la valeur par défaut. Le jeu automatique choisit les serveurs tchèques "
    L"et slovaques, PTB pour l’Europe ou le pool mondial selon la région système. Plusieurs mesures sont "
    L"filtrées selon le délai réseau et les réponses aberrantes. Synchroniser maintenant lance immédiatement "
    L"une nouvelle mesure.\r\n\r\nAprès la synchronisation, l’horloge de CalClock continue de fonctionner "
    L"indépendamment des modifications ultérieures de l’heure système Windows. Si la connexion est perdue ou "
    L"si les serveurs changent, elle continue à partir de la dernière synchronisation valide jusqu’à une "
    L"nouvelle réponse ; cet état est conservé jusqu’à la fermeture de l’application.\r\n\r\nJOURNAL DE "
    L"SYNCHRONISATION NTP\r\nL’onglet Heure conserve les requêtes aux serveurs NTP depuis le lancement de "
    L"l’application. Chaque entrée indique la date et l’heure locale de l’ordinateur, le serveur et l’état. OK"
    L" signale une réponse valide et θ son décalage par rapport à l’heure système Windows. ERR indique la "
    L"cause de l’échec et, le cas échéant, un code d’erreur. La dernière entrée d’un groupe de requêtes "
    L"indique aussi le décalage calculé Θ lorsque des mesures exploitables sont disponibles.\r\n\r\nLes "
    L"décalages sont exprimés en millisecondes avec quatre décimales. Une valeur positive signifie que "
    L"l’horloge du serveur est en avance sur Windows ; une valeur négative signifie qu’elle est en retard. Θ "
    L"tient compte des mesures acceptées et apparaît aussi dans l’état de synchronisation.\r\n\r\nEnregistrer "
    L"le journal exporte les entrées en CSV, avec les décalages et les détails des erreurs. Les entrées ne "
    L"sont pas conservées entre les sessions ; enregistrez-les avant de quitter pour les garder.",
    L"\r\n\r\nORIGEN DE HORA\r\nLa pestaña Hora selecciona la hora del sistema Windows o los servidores NTP "
    L"configurados para toda la aplicación y, por tanto, para todos los widgets. NTP solo corrige la hora "
    L"mostrada por CalClock; el reloj de Windows nunca se modifica. Se usa la hora del sistema hasta la "
    L"primera respuesta válida. NTP es el valor predeterminado. El conjunto automático elige servidores checos"
    L" y eslovacos, PTB para Europa o el grupo mundial según la región del sistema. Varias mediciones se "
    L"filtran por retardo de red y respuestas atípicas. Sincronizar ahora inicia una medición nueva de "
    L"inmediato.\r\n\r\nTras la sincronización, el reloj de CalClock sigue funcionando independientemente de "
    L"los cambios posteriores en la hora del sistema Windows. Si falla la conexión o se cambian los "
    L"servidores, continúa desde la última sincronización válida hasta recibir una nueva respuesta; este "
    L"estado se conserva hasta que se cierra la aplicación.\r\n\r\nREGISTRO DE SINCRONIZACIÓN NTP\r\nLa "
    L"pestaña Hora registra las consultas a servidores NTP desde el inicio de la aplicación. Cada entrada "
    L"contiene la fecha y hora local del equipo, el servidor y el estado. OK identifica una respuesta válida y"
    L" θ su desfase respecto a la hora del sistema Windows. ERR indica el motivo del fallo y, si existe, su "
    L"código. La última entrada de cada grupo de consultas también muestra el desfase calculado Θ cuando hay "
    L"mediciones utilizables.\r\n\r\nLos desfases se muestran en milisegundos con cuatro decimales. Un valor "
    L"positivo indica que el reloj del servidor está adelantado respecto a Windows; uno negativo indica que "
    L"está atrasado. Θ refleja las mediciones aceptadas y también aparece en el estado de "
    L"sincronización.\r\n\r\nGuardar registro exporta las entradas a CSV, incluidos los desfases y los "
    L"detalles de los errores. Las entradas no se conservan entre sesiones; guárdelas antes de salir si desea "
    L"conservarlas.",
    L"\r\n\r\nORIGINE DELL’ORA\r\nLa scheda Ora seleziona l’ora di sistema Windows o i server NTP configurati "
    L"per l’intera applicazione e quindi per tutti i widget. NTP corregge solo l’ora visualizzata da CalClock;"
    L" l’orologio di Windows non viene mai modificato. L’ora di sistema viene usata fino alla prima risposta "
    L"valida. NTP è l’impostazione predefinita. Il gruppo automatico sceglie i server cechi e slovacchi, PTB "
    L"per l’Europa o il pool globale in base all’area di sistema. Più misurazioni vengono filtrate in base al "
    L"ritardo di rete e alle risposte anomale. Sincronizza ora avvia subito una nuova misurazione.\r\n\r\nDopo"
    L" la sincronizzazione, l’orologio di CalClock continua a funzionare indipendentemente dalle successive "
    L"modifiche all’ora di sistema Windows. Se la connessione si interrompe o si cambiano i server, continua "
    L"dall’ultima sincronizzazione valida fino a una nuova risposta; questo stato viene mantenuto fino alla "
    L"chiusura dell’applicazione.\r\n\r\nREGISTRO DI SINCRONIZZAZIONE NTP\r\nLa scheda Ora registra le "
    L"richieste ai server NTP dall’avvio dell’applicazione. Ogni voce contiene data e ora locale del computer,"
    L" server e stato. OK indica una risposta valida e θ il suo scostamento dall’ora di sistema Windows. ERR "
    L"indica il motivo dell’errore e l’eventuale codice. L’ultima voce di un gruppo di richieste mostra anche "
    L"lo scostamento calcolato Θ quando sono disponibili misurazioni utilizzabili.\r\n\r\nGli scostamenti sono"
    L" espressi in millisecondi con quattro cifre decimali. Un valore positivo indica che l’orologio del "
    L"server è avanti rispetto a Windows; un valore negativo indica che è indietro. Θ tiene conto delle "
    L"misurazioni accettate ed è mostrato anche nello stato di sincronizzazione.\r\n\r\nSalva registro esporta"
    L" le voci in CSV, compresi scostamenti e dettagli degli errori. Le voci non vengono conservate tra le "
    L"sessioni; salvarle prima di uscire se si desidera mantenerle.",
    L"\r\n\r\nŹRÓDŁO CZASU\r\nKarta Czas wybiera dla całej aplikacji, a więc dla wszystkich widżetów, czas "
    L"systemowy Windows albo skonfigurowane serwery NTP. NTP koryguje wyłącznie czas wyświetlany przez "
    L"CalClock; zegar Windows nigdy nie jest zmieniany. Do pierwszej prawidłowej odpowiedzi używany jest czas "
    L"systemowy. NTP jest ustawieniem domyślnym. Zestaw automatyczny wybiera według regionu systemu serwery "
    L"czeskie i słowackie, PTB dla Europy albo pulę globalną. Wiele pomiarów jest filtrowanych według "
    L"opóźnienia sieci i wartości odstających. Synchronizuj teraz natychmiast rozpoczyna nowy "
    L"pomiar.\r\n\r\nPo synchronizacji zegar CalClock odmierza czas niezależnie od późniejszych zmian czasu "
    L"systemowego Windows. Po utracie połączenia lub zmianie serwerów kontynuuje odmierzanie od ostatniej "
    L"prawidłowej synchronizacji do uzyskania nowej odpowiedzi; stan ten jest zachowywany do zamknięcia "
    L"aplikacji.\r\n\r\nDZIENNIK SYNCHRONIZACJI NTP\r\nKarta Czas rejestruje zapytania do serwerów NTP od "
    L"uruchomienia aplikacji. Każdy wpis zawiera datę i lokalny czas komputera, serwer oraz stan. OK oznacza "
    L"prawidłową odpowiedź, a θ jej odchylenie od czasu systemowego Windows. ERR podaje przyczynę "
    L"niepowodzenia i ewentualny kod błędu. Ostatni wpis grupy zapytań zawiera również obliczone odchylenie Θ,"
    L" jeśli dostępne są użyteczne pomiary.\r\n\r\nOdchylenia są wyświetlane w milisekundach z czterema "
    L"miejscami po przecinku. Wartość dodatnia oznacza, że zegar serwera wyprzedza Windows; ujemna oznacza, że"
    L" jest opóźniony. Θ uwzględnia zaakceptowane pomiary i jest również widoczne w stanie "
    L"synchronizacji.\r\n\r\nZapisz dziennik eksportuje wpisy do CSV wraz z odchyleniami i szczegółami błędów."
    L" Wpisy nie są zachowywane między uruchomieniami; zapisz je przed zamknięciem aplikacji, jeśli chcesz je "
    L"zachować.",
    L"\r\n\r\nZDROJ ČASU\r\nNa karte Čas možno pre celú aplikáciu, teda spoločne pre všetky widgety, vybrať "
    L"systémový čas Windows alebo čas zo zadaných serverov NTP. NTP koriguje iba čas zobrazený v CalClock; "
    L"systémové hodiny Windows sa nikdy nemenia. Do prvej platnej odpovede sa používa systémový čas. NTP je "
    L"predvolené. Automatická sada vyberie podľa systémovej oblasti české a slovenské servery, PTB pre Európu "
    L"alebo celosvetový fond. Viaceré merania sa filtrujú podľa sieťového oneskorenia a odľahlých odpovedí. "
    L"Synchronizovať teraz spustí nové meranie ihneď.\r\n\r\nPo synchronizácii hodiny CalClock pokračujú "
    L"nezávisle od neskorších zmien systémového času Windows. Pri výpadku spojenia alebo zmene serverov "
    L"pokračujú od poslednej platnej synchronizácie až do získania novej odpovede; stav sa uchováva do "
    L"ukončenia aplikácie.\r\n\r\nZÁZNAM SYNCHRONIZÁCIE NTP\r\nNa karte Čas je záznam dotazov na servery NTP "
    L"od spustenia aplikácie. Každý záznam obsahuje dátum a miestny čas počítača, server a stav. OK označuje "
    L"platnú odpoveď a θ jej odchýlku voči systémovému času Windows. ERR uvádza dôvod neúspechu a prípadný "
    L"chybový kód. Posledný záznam skupiny obsahuje aj výslednú odchýlku Θ, ak sa podarilo získať použiteľné "
    L"merania.\r\n\r\nOdchýlky sa zobrazujú v milisekundách so štyrmi desatinnými miestami. Kladná hodnota "
    L"znamená, že čas servera je voči Windows vpred; záporná, že zaostáva. Výsledná odchýlka Θ zohľadňuje "
    L"prijaté merania a je uvedená aj v stave synchronizácie.\r\n\r\nUložiť log uloží záznamy do CSV vrátane "
    L"odchýlok a dôvodov chýb. Záznamy sa medzi spusteniami neuchovávajú; ak ich chcete zachovať, uložte ich "
    L"pred ukončením aplikácie.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP servers for the "
    L"whole application and therefore for all widgets. NTP corrects only the time displayed by CalClock; the "
    L"Windows clock is never changed. System time is used until the first valid reply. NTP is the default. The"
    L" automatic set chooses Czech and Slovak servers, PTB for Europe, or the global pool according to the "
    L"system region. Multiple measurements are filtered by network delay and outlying replies. Synchronise now"
    L" starts a fresh measurement immediately.\r\n\r\nAfter synchronisation, CalClock keeps time independently"
    L" of later changes to Windows system time. If the connection fails or servers change, it continues from "
    L"the last valid synchronisation until a new reply arrives; this state is retained until the application "
    L"closes.\r\n\r\nNTP SYNCHRONIZATION LOG\r\nThe Time tab records NTP server queries since the application "
    L"started. Each entry contains the date and local computer time, server, and status. OK identifies a valid"
    L" reply, with θ showing its offset from Windows system time. ERR gives the failure reason and any error "
    L"code. The final entry in a query group also shows the combined offset Θ when usable measurements are "
    L"available.\r\n\r\nOffsets are displayed in milliseconds with four decimal places. A positive value means"
    L" the server clock is ahead of Windows; a negative value means it is behind. The combined offset Θ "
    L"reflects the accepted measurements and is also shown in the synchronisation status.\r\n\r\nSave log "
    L"exports the records to CSV, including offsets and failure details. Records are not retained between "
    L"application sessions; save them before exiting if you want to keep them.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP servers for the "
    L"whole application and therefore for all widgets. NTP corrects only the time displayed by CalClock; the "
    L"Windows clock is never changed. System time is used until the first valid reply. NTP is the default. The"
    L" automatic set chooses Czech and Slovak servers, PTB for Europe, or the global pool according to the "
    L"system region. Multiple measurements are filtered by network delay and outlying replies. Synchronise now"
    L" starts a fresh measurement immediately.\r\n\r\nAfter synchronisation, CalClock keeps time independently"
    L" of later changes to Windows system time. If the connection fails or servers change, it continues from "
    L"the last valid synchronisation until a new reply arrives; this state is retained until the application "
    L"closes.\r\n\r\nNTP SYNCHRONIZATION LOG\r\nThe Time tab records NTP server queries since the application "
    L"started. Each entry contains the date and local computer time, server, and status. OK identifies a valid"
    L" reply, with θ showing its offset from Windows system time. ERR gives the failure reason and any error "
    L"code. The final entry in a query group also shows the combined offset Θ when usable measurements are "
    L"available.\r\n\r\nOffsets are displayed in milliseconds with four decimal places. A positive value means"
    L" the server clock is ahead of Windows; a negative value means it is behind. The combined offset Θ "
    L"reflects the accepted measurements and is also shown in the synchronisation status.\r\n\r\nSave log "
    L"exports the records to CSV, including offsets and failure details. Records are not retained between "
    L"application sessions; save them before exiting if you want to keep them.",
    L"\r\n\r\nORIGEM DA HORA\r\nO separador Hora escolhe para toda a aplicação a hora do Windows ou servidores"
    L" NTP. O NTP corrige apenas o CalClock e nunca altera o Windows. A predefinição é NTP; o conjunto "
    L"automático escolhe servidores pela região e filtra medições por atraso e valores atípicos.\r\n\r\nApós a"
    L" sincronização, o relógio do CalClock continua a funcionar independentemente de alterações posteriores à"
    L" hora do sistema Windows. Se a ligação falhar ou os servidores forem alterados, continua a partir da "
    L"última sincronização válida até receber uma nova resposta; este estado mantém-se até fechar a "
    L"aplicação.\r\n\r\nREGISTO DE SINCRONIZAÇÃO NTP\r\nO separador Hora regista as consultas a servidores NTP"
    L" desde o início da aplicação. Cada entrada contém a data e hora local do computador, o servidor e o "
    L"estado. OK identifica uma resposta válida e θ o seu desvio em relação à hora do Windows. ERR indica a "
    L"causa da falha e o eventual código de erro. A última entrada de um grupo de consultas mostra também o "
    L"desvio calculado Θ quando existem medições utilizáveis.\r\n\r\nOs desvios são apresentados em "
    L"milissegundos com quatro casas decimais. Um valor positivo significa que o relógio do servidor está "
    L"adiantado em relação ao Windows; um valor negativo significa que está atrasado. Θ reflete as medições "
    L"aceites e também aparece no estado da sincronização.\r\n\r\nGuardar registo exporta as entradas para "
    L"CSV, incluindo desvios e detalhes das falhas. As entradas não são conservadas entre sessões; guarde-as "
    L"antes de sair se quiser mantê-las.",
    L"\r\n\r\nTIDSKILDE\r\nFanen Tid velger Windows-tid eller NTP-servere for hele programmet. NTP korrigerer "
    L"bare CalClock og endrer aldri Windows. NTP er standard; det automatiske settet velger servere etter "
    L"region og filtrerer målinger etter forsinkelse og avvik.\r\n\r\nEtter synkronisering går "
    L"CalClock-klokken videre uavhengig av senere endringer i systemtiden i Windows. Hvis forbindelsen brytes "
    L"eller serverne endres, fortsetter klokken fra siste gyldige synkronisering til et nytt svar mottas; "
    L"denne tilstanden beholdes til programmet avsluttes.\r\n\r\nNTP-SYNKRONISERINGSLOGG\r\nFanen Tid "
    L"registrerer NTP-serverforespørsler siden programmet startet. Hver oppføring inneholder dato og lokal "
    L"datamaskintid, server og status. OK angir et gyldig svar, og θ viser tidsavviket fra "
    L"Windows-systemtiden. ERR angir årsaken til feilen og en eventuell feilkode. Den siste oppføringen i en "
    L"forespørselsgruppe viser også det beregnede tidsavviket Θ når brukbare målinger er "
    L"tilgjengelige.\r\n\r\nTidsavvik vises i millisekunder med fire desimaler. En positiv verdi betyr at "
    L"serverklokken går foran Windows; en negativ verdi betyr at den går etter. Θ tar hensyn til de godkjente "
    L"målingene og vises også i synkroniseringsstatusen.\r\n\r\nLagre logg eksporterer oppføringene til CSV, "
    L"inkludert tidsavvik og feildetaljer. Oppføringer beholdes ikke mellom programøkter; lagre dem før du "
    L"avslutter hvis du vil beholde dem.",
    L"\r\n\r\nTIDSKÄLLA\r\nFliken Tid väljer Windows-tid eller NTP-servrar för hela programmet. NTP korrigerar"
    L" bara CalClock och ändrar aldrig Windows. NTP är standard; den automatiska uppsättningen väljer servrar "
    L"efter region och filtrerar mätningar efter fördröjning och avvikelse.\r\n\r\nEfter synkronisering går "
    L"CalClock-klockan vidare oberoende av senare ändringar av systemtiden i Windows. Om anslutningen bryts "
    L"eller servrarna ändras fortsätter klockan från den senaste giltiga synkroniseringen tills ett nytt svar "
    L"kommer; detta tillstånd behålls tills programmet stängs.\r\n\r\nNTP-SYNKRONISERINGSLOGG\r\nFliken Tid "
    L"registrerar NTP-serverförfrågningar sedan programmet startades. Varje post innehåller datum och datorns "
    L"lokala tid, server och status. OK anger ett giltigt svar och θ dess tidsavvikelse från "
    L"Windows-systemtiden. ERR anger felorsaken och en eventuell felkod. Den sista posten i en grupp "
    L"förfrågningar visar även den beräknade tidsavvikelsen Θ när användbara mätningar "
    L"finns.\r\n\r\nTidsavvikelser visas i millisekunder med fyra decimaler. Ett positivt värde betyder att "
    L"serverklockan går före Windows; ett negativt värde betyder att den går efter. Θ tar hänsyn till de "
    L"godkända mätningarna och visas även i synkroniseringsstatusen.\r\n\r\nSpara logg exporterar posterna "
    L"till CSV, inklusive tidsavvikelser och feldetaljer. Poster sparas inte mellan programstarter; spara dem "
    L"innan du avslutar om du vill behålla dem.",
    L"\r\n\r\nAIKALÄHDE\r\nAika-välilehdellä valitaan koko sovellukselle Windowsin aika tai NTP-palvelimet. "
    L"NTP korjaa vain CalClockia eikä muuta Windowsia. NTP on oletus; automaattinen joukko valitsee palvelimet"
    L" alueen mukaan ja suodattaa mittaukset viiveen ja poikkeamien perusteella.\r\n\r\nSynkronoinnin jälkeen "
    L"CalClockin kello käy riippumatta myöhemmistä Windowsin järjestelmäajan muutoksista. Jos yhteys katkeaa "
    L"tai palvelimia vaihdetaan, kello jatkaa viimeisestä kelvollisesta synkronoinnista uuteen vastaukseen "
    L"asti; tämä tila säilyy sovelluksen sulkemiseen saakka.\r\n\r\nNTP-SYNKRONOINTILOKI\r\nAika-välilehti "
    L"tallentaa NTP-palvelinkyselyt sovelluksen käynnistämisestä alkaen. Jokainen merkintä sisältää "
    L"päivämäärän ja tietokoneen paikallisen ajan, palvelimen sekä tilan. OK tarkoittaa kelvollista vastausta,"
    L" ja θ ilmaisee sen aikaeron Windowsin järjestelmäaikaan. ERR kertoo epäonnistumisen syyn ja mahdollisen "
    L"virhekoodin. Kyselyryhmän viimeinen merkintä näyttää myös lasketun aikaeron Θ, jos käytettävissä on "
    L"käyttökelpoisia mittauksia.\r\n\r\nAikaerot näytetään millisekunteina neljällä desimaalilla. "
    L"Positiivinen arvo tarkoittaa, että palvelimen kello on Windowsia edellä; negatiivinen arvo tarkoittaa, "
    L"että se on jäljessä. Θ perustuu hyväksyttyihin mittauksiin ja näkyy myös synkronoinnin "
    L"tilassa.\r\n\r\nTallenna loki vie merkinnät CSV-tiedostoon, mukaan lukien aikaerot ja virhetiedot. "
    L"Merkintöjä ei säilytetä käynnistyskertojen välillä; tallenna ne ennen sulkemista, jos haluat säilyttää "
    L"ne.",
    L"\r\n\r\nTIDSKILDE\r\nFanen Tid vælger Windows-tid eller NTP-servere for hele programmet. NTP korrigerer "
    L"kun CalClock og ændrer aldrig Windows. NTP er standard; det automatiske sæt vælger servere efter område "
    L"og filtrerer målinger efter forsinkelse og afvigelser.\r\n\r\nEfter synkronisering går CalClock-uret "
    L"videre uafhængigt af senere ændringer af systemtiden i Windows. Hvis forbindelsen afbrydes, eller "
    L"serverne ændres, fortsætter uret fra den seneste gyldige synkronisering, indtil et nyt svar modtages; "
    L"denne tilstand bevares, indtil programmet lukkes.\r\n\r\nNTP-SYNKRONISERINGSLOG\r\nFanen Tid registrerer"
    L" NTP-serverforespørgsler siden programmets start. Hver post indeholder dato og computerens lokale tid, "
    L"server og status. OK angiver et gyldigt svar, og θ viser tidsafvigelsen fra Windows-systemtiden. ERR "
    L"angiver fejlårsagen og en eventuel fejlkode. Den sidste post i en forespørgselsgruppe viser også den "
    L"beregnede tidsafvigelse Θ, når brugbare målinger er tilgængelige.\r\n\r\nTidsafvigelser vises i "
    L"millisekunder med fire decimaler. En positiv værdi betyder, at serveruret går foran Windows; en negativ "
    L"værdi betyder, at det går bagefter. Θ tager hensyn til de godkendte målinger og vises også i "
    L"synkroniseringsstatussen.\r\n\r\nGem log eksporterer posterne til CSV, inklusive tidsafvigelser og "
    L"fejloplysninger. Poster beholdes ikke mellem programstarter; gem dem før afslutning, hvis du vil beholde"
    L" dem.",
    L"\r\n\r\nTÍMAGJAFI\r\nTímaflipinn velur Windows-tíma eða NTP-þjóna fyrir allt forritið. NTP leiðréttir "
    L"aðeins CalClock og breytir aldrei Windows. NTP er sjálfgefið; sjálfvirka safnið velur þjóna eftir svæði "
    L"og síar mælingar eftir töf og frávikum.\r\n\r\nEftir samstillingu gengur klukka CalClock áfram óháð "
    L"síðari breytingum á kerfistíma Windows. Ef samband rofnar eða skipt er um þjóna heldur klukkan áfram frá"
    L" síðustu gildu samstillingu þar til nýtt svar berst; þetta ástand helst þar til forritinu er "
    L"lokað.\r\n\r\nNTP-SAMSTILLINGARSKRÁ\r\nTímaflipinn skráir fyrirspurnir til NTP-þjóna frá ræsingu "
    L"forritsins. Hver færsla inniheldur dagsetningu og staðartíma tölvunnar, þjón og stöðu. OK merkir gilt "
    L"svar og θ tímamun þess frá kerfistíma Windows. ERR sýnir ástæðu bilunar og villukóða ef við á. Síðasta "
    L"færsla í hópi fyrirspurna sýnir einnig reiknaðan tímamun Θ þegar nothæfar mælingar liggja "
    L"fyrir.\r\n\r\nTímamunur er sýndur í millisekúndum með fjórum aukastöfum. Jákvætt gildi merkir að klukka "
    L"þjónsins er á undan Windows; neikvætt gildi merkir að hún er á eftir. Θ tekur mið af samþykktum mælingum"
    L" og birtist einnig í samstillingarstöðu.\r\n\r\nVista annál flytur færslur út sem CSV, með tímamun og "
    L"villuupplýsingum. Færslur varðveitast ekki milli keyrslna; vistaðu þær áður en þú lokar forritinu ef þú "
    L"vilt geyma þær.",
    L"\r\n\r\nZAMAN KAYNAĞI\r\nZaman sekmesi tüm uygulama için Windows zamanını veya NTP sunucularını seçer. "
    L"NTP yalnızca CalClock'u düzeltir ve Windows'u hiçbir zaman değiştirmez. NTP varsayılandır; otomatik küme"
    L" bölgeye göre sunucu seçer ve ölçümleri gecikme ile aykırı değerlere göre süzer.\r\n\r\nEşitlemeden "
    L"sonra CalClock saati, Windows sistem saatinde daha sonra yapılan değişikliklerden bağımsız olarak "
    L"ilerler. Bağlantı kesilirse veya sunucular değiştirilirse yeni bir yanıt alınana kadar son geçerli "
    L"eşitlemeden itibaren ilerlemeye devam eder; bu durum uygulama kapatılana kadar korunur.\r\n\r\nNTP "
    L"EŞİTLEME GÜNLÜĞÜ\r\nZaman sekmesi, uygulama başlatıldığından beri NTP sunucu sorgularını kaydeder. Her "
    L"kayıt tarih ve bilgisayarın yerel saatini, sunucuyu ve durumu içerir. OK geçerli bir yanıtı, θ ise bu "
    L"yanıtın Windows sistem saatinden farkını gösterir. ERR başarısızlığın nedenini ve varsa hata kodunu "
    L"belirtir. Kullanılabilir ölçümler varsa sorgu grubunun son kaydı hesaplanan zaman farkını Θ olarak da "
    L"gösterir.\r\n\r\nZaman farkları milisaniye cinsinden dört ondalık basamakla gösterilir. Pozitif değer "
    L"sunucu saatinin Windows’tan ileride, negatif değer geride olduğunu belirtir. Θ kabul edilen ölçümleri "
    L"yansıtır ve eşitleme durumunda da gösterilir.\r\n\r\nGünlüğü kaydet, zaman farkları ve hata ayrıntıları "
    L"dahil kayıtları CSV’ye aktarır. Kayıtlar uygulama oturumları arasında korunmaz; saklamak istiyorsanız "
    L"uygulamadan çıkmadan önce kaydedin.",
    L"\r\n\r\nAja allikas ja NTP-logi\r\nVahekaart Aeg valib Windowsi süsteemiaja või NTP-serverid kogu "
    L"rakendusele. NTP muudab ainult CalClocki aega; Windowsi kella ei muudeta. Esimese sobiva vastuseni "
    L"kasutatakse süsteemiaega. NTP on vaikevalik. Automaatrühm valib süsteemi piirkonna järgi Tšehhi ja "
    L"Slovakkia serverid, Euroopa jaoks PTB või ülemaailmse rühma. Mõõtmisi filtreeritakse võrgulatentsuse ja "
    L"teistest vastustest kõrvalekallete järgi. Sünkrooni kohe alustab uut mõõtmist.\r\n\r\nPärast "
    L"sünkroonimist käib CalClocki kell sõltumata Windowsi süsteemiaja hilisematest muutustest. Ühenduse "
    L"kadumisel või serverite vahetamisel jätkab kell viimasest sobivast sünkroonimisest uue vastuseni; olek "
    L"säilib rakenduse sulgemiseni.\r\n\r\nVahekaart Aeg logib NTP-päringud käivitamisest alates. Kirje "
    L"sisaldab kuupäeva, arvuti kohalikku aega, serverit ja olekut. OK näitab sobivat vastust ja θ selle nihet"
    L" Windowsi süsteemiajast. ERR annab põhjuse ja võimaliku veakoodi. Päringurühma viimane kirje näitab ka "
    L"ühendatud nihet Θ, kui on kasutatavaid mõõtmisi. Nihked on millisekundites nelja kümnendkohaga: "
    L"positiivne tähendab serveri edestamist ja negatiivne mahajäämist. Θ põhineb vastu võetud mõõtmistel ja "
    L"ilmub ka sünkroonimisolekus. Salvesta logi ekspordib CSV koos nihete ja veateabega. Logi ei säili "
    L"käivituste vahel; vajaduse korral salvestage see enne väljumist.",
    L"\r\n\r\nFoinse ama agus logchomhad NTP\r\nAr an gcluaisín Am, roghnaítear am córais Windows nó "
    L"freastalaithe NTP don fheidhmchlár iomlán. Ní athraíonn NTP ach am CalClock; ní athraítear clog Windows."
    L" Úsáidtear am an chórais go dtí an chéad fhreagra bailí. Is é NTP an réamhshocrú. Roghnaíonn an tacar "
    L"uathoibríoch freastalaithe Seiceacha agus Slóvacacha, PTB don Eoraip nó tacar domhanda de réir réigiún "
    L"an chórais. Scagtar tomhais de réir moille líonra agus diall ó fhreagraí eile. Tosaíonn Sioncronaigh "
    L"anois tomhas nua láithreach.\r\n\r\nTar éis sioncronaithe, coinníonn CalClock an t-am go neamhspleách ar"
    L" athruithe níos déanaí ar am córais Windows. Má chailltear an nasc nó má athraítear freastalaithe, "
    L"leanann sé ón sioncronú bailí deireanach go dtí freagra nua; coinnítear an staid go dtí go ndúntar an "
    L"feidhmchlár.\r\n\r\nLogálann Am iarratais NTP ó thús an fheidhmchláir. Tá dáta, am áitiúil an ríomhaire,"
    L" freastalaí agus stádas sa taifead. Ciallaíonn OK freagra bailí agus θ a fhritháireamh ó am Windows; "
    L"tugann ERR an chúis agus aon chód earráide. Taispeánann taifead deiridh grúpa an fritháireamh "
    L"comhcheangailte Θ nuair atá tomhais inúsáidte ann. Tá na fritháirimh i milleasoicindí le ceithre ionad "
    L"dheachúlacha: dearfach má tá an freastalaí chun tosaigh, diúltach má tá sé ar gcúl. Bunaítear Θ ar na "
    L"tomhais ghlactha agus taispeántar sa stádas sioncronaithe é. Easpórtálann Sábháil an logchomhad CSV le "
    L"fritháirimh agus sonraí earráide. Ní choinnítear taifid idir seisiúin; sábháil roimh imeacht más gá.",
    L"\r\n\r\nLaiko šaltinis ir NTP žurnalas\r\nSkirtukas Laikas parenka „Windows“ sistemos laiką arba NTP "
    L"serverius visai programai. NTP keičia tik „CalClock“ laiką; „Windows“ laikrodis nekeičiamas. Iki pirmo "
    L"tinkamo atsakymo naudojamas sistemos laikas. NTP yra numatytasis pasirinkimas. Automatinis rinkinys "
    L"pagal sistemos regioną parenka Čekijos ir Slovakijos serverius, PTB Europai arba pasaulinį rinkinį. "
    L"Matavimai filtruojami pagal tinklo delsą ir nuokrypį nuo kitų atsakymų. Sinchronizuoti dabar iškart "
    L"pradeda naują matavimą.\r\n\r\nPo sinchronizavimo „CalClock“ laikrodis veikia nepriklausomai nuo "
    L"vėlesnių „Windows“ sistemos laiko pakeitimų. Praradus ryšį ar pakeitus serverius tęsiama nuo paskutinio "
    L"tinkamo sinchronizavimo iki naujo atsakymo; būsena išlaikoma iki programos uždarymo.\r\n\r\nLaikas "
    L"registruoja NTP užklausas nuo programos paleidimo. Įraše yra data, kompiuterio vietinis laikas, serveris"
    L" ir būsena. OK žymi tinkamą atsakymą, θ – jo poslinkį nuo „Windows“ sistemos laiko. ERR pateikia "
    L"priežastį ir galimą klaidos kodą. Paskutinis užklausų grupės įrašas rodo bendrą poslinkį Θ, jei yra "
    L"tinkamų matavimų. Poslinkiai pateikiami milisekundėmis su keturiais skaitmenimis po kablelio: teigiamas "
    L"reiškia, kad serveris skuba, neigiamas – atsilieka. Θ pagrįstas priimtais matavimais ir rodomas "
    L"sinchronizavimo būsenoje. Įrašyti žurnalą eksportuoja CSV su poslinkiais ir klaidų informacija. Įrašai "
    L"tarp paleidimų neišlieka; prireikus įrašykite prieš išeidami.",
    L"\r\n\r\nLaika avots un NTP žurnāls\r\nCilne Laiks izvēlas Windows sistēmas laiku vai NTP serverus visai "
    L"programmai. NTP maina tikai CalClock laiku; Windows pulkstenis netiek mainīts. Līdz pirmajai derīgajai "
    L"atbildei izmanto sistēmas laiku. NTP ir noklusējums. Automātiskā kopa pēc sistēmas reģiona izvēlas "
    L"Čehijas un Slovākijas serverus, PTB Eiropai vai pasaules kopu. Mērījumus filtrē pēc tīkla aizkaves un "
    L"novirzēm no citām atbildēm. Sinhronizēt tūlīt nekavējoties sāk jaunu mērījumu.\r\n\r\nPēc "
    L"sinhronizācijas CalClock pulkstenis darbojas neatkarīgi no turpmākām Windows sistēmas laika izmaiņām. "
    L"Zūdot savienojumam vai mainot serverus, tas turpina no pēdējās derīgās sinhronizācijas līdz jaunai "
    L"atbildei; stāvoklis paliek līdz programmas aizvēršanai.\r\n\r\nLaiks reģistrē NTP vaicājumus kopš "
    L"palaišanas. Ierakstā ir datums, datora vietējais laiks, serveris un statuss. OK nozīmē derīgu atbildi, θ"
    L" – tās nobīdi no Windows laika. ERR sniedz iemeslu un iespējamo kļūdas kodu. Grupas pēdējais ieraksts "
    L"rāda arī apvienoto nobīdi Θ, ja ir derīgi mērījumi. Nobīdes ir milisekundēs ar četrām zīmēm aiz komata: "
    L"pozitīva vērtība nozīmē, ka serveris ir priekšā, negatīva – atpaliek. Θ balstās uz pieņemtajiem "
    L"mērījumiem un redzama arī sinhronizācijas statusā. Saglabāt žurnālu eksportē CSV ar nobīdēm un kļūdu "
    L"informāciju. Ieraksti starp palaišanām nepaliek; saglabājiet pirms iziešanas, ja vajadzīgs.",
    L"\r\n\r\nIdőforrás és NTP-napló\r\nAz Idő fül a Windows rendszeridejét vagy NTP-kiszolgálókat választ az "
    L"egész programhoz. Az NTP csak a CalClock idejét módosítja, a Windows óráját soha. Az első érvényes "
    L"válaszig a rendszeridő használatos. Az NTP az alapértelmezett. Az automatikus csoport a rendszer régiója"
    L" szerint cseh és szlovák kiszolgálókat, Európához PTB-t vagy világméretű csoportot választ. A méréseket "
    L"a hálózati késés és a többi választól való eltérés szerint szűri. A Szinkronizálás most azonnal új "
    L"mérést indít.\r\n\r\nSzinkronizálás után a CalClock órája a Windows rendszeridejének későbbi "
    L"változásaitól függetlenül jár. Kapcsolatvesztés vagy kiszolgálóváltás esetén az utolsó érvényes "
    L"szinkronizálástól folytatja az új válaszig; az állapot a program bezárásáig marad meg.\r\n\r\nAz Idő fül"
    L" indítás óta naplózza az NTP-lekérdezéseket. A bejegyzés dátumot, helyi gépidőt, kiszolgálót és "
    L"állapotot tartalmaz. Az OK érvényes válasz, θ az eltérés a Windows idejétől. Az ERR az okot és az "
    L"esetleges hibakódot adja. A csoport utolsó bejegyzése az összevont Θ eltolást is mutatja, ha vannak "
    L"használható mérések. Az eltolás milliszekundumban, négy tizedesjeggyel jelenik meg: pozitívnál a "
    L"kiszolgáló előrébb jár, negatívnál késik. A Θ az elfogadott mérésekre épül, és a szinkronizálási "
    L"állapotban is látható. A Napló mentése CSV-be exportálja a bejegyzéseket eltolásokkal és "
    L"hibarészletekkel. A napló nem marad meg két indítás között; kilépés előtt mentse, ha szükséges.",
    L"\r\n\r\nSors tal-ħin u reġistru NTP\r\nIt-tab Ħin jagħżel il-ħin tas-sistema Windows jew servers NTP "
    L"għall-programm kollu. NTP jibdel biss il-ħin ta’ CalClock; l-arloġġ tal-Windows ma jinbidilx. Jintuża "
    L"l-ħin tas-sistema sal-ewwel tweġiba valida. NTP huwa d-default. Il-grupp awtomatiku jagħżel servers Ċeki"
    L" u Slovakki, PTB għall-Ewropa jew grupp dinji skont ir-reġjun tas-sistema. Il-kejl jiġi ffiltrat skont "
    L"id-dewmien tan-network u d-differenza minn tweġibiet oħra. Issinkronizza issa jibda kejl ġdid "
    L"minnufih.\r\n\r\nWara s-sinkronizzazzjoni, l-arloġġ ta’ CalClock ikompli jaħdem indipendentement minn "
    L"bidliet sussegwenti fil-ħin tas-sistema Windows. Jekk tintilef il-konnessjoni jew jinbidlu s-servers, "
    L"ikompli mill-aħħar sinkronizzazzjoni valida sa tweġiba ġdida; l-istat jibqa’ sal-għeluq "
    L"tal-programm.\r\n\r\nĦin jirreġistra mistoqsijiet NTP mit-tnedija. Ir-rekord fih id-data, il-ħin lokali "
    L"tal-kompjuter, is-server u l-istatus. OK ifisser tweġiba valida; θ il-kumpens tagħha mill-ħin "
    L"tal-Windows. ERR jagħti r-raġuni u kwalunkwe kodiċi tal-iżball. L-aħħar rekord ta’ grupp juri wkoll "
    L"il-kumpens magħqud Θ jekk ikun hemm kejl li jista’ jintuża. Il-kumpensi huma f’millisekondi b’erba’ "
    L"postijiet deċimali: pożittiv ifisser li s-server huwa ’l quddiem, negattiv li qiegħed lura. Θ huwa "
    L"bbażat fuq il-kejl aċċettat u jidher ukoll fl-istatus tas-sinkronizzazzjoni. Issejvja r-reġistru "
    L"jesporta CSV bil-kumpensi u d-dettalji tal-iżbalji. Ir-rekords ma jinżammux bejn tnedijiet; issejvjahom "
    L"qabel toħroġ jekk meħtieġ.",
    L"\r\n\r\nTijdbron en NTP-logboek\r\nTijd kiest Windows-systeemtijd of NTP-servers voor de hele "
    L"toepassing. NTP verandert alleen de CalClock-tijd; de Windows-klok wordt nooit aangepast. Tot het eerste"
    L" geldige antwoord wordt de systeemtijd gebruikt. NTP is de standaard. De automatische groep kiest "
    L"volgens de systeemregio Tsjechische en Slowaakse servers, PTB voor Europa of een wereldwijde groep. "
    L"Metingen worden gefilterd op netwerkvertraging en afwijkingen van andere antwoorden. Nu synchroniseren "
    L"start direct een nieuwe meting.\r\n\r\nNa synchronisatie loopt de CalClock-klok door, onafhankelijk van "
    L"latere wijzigingen van de Windows-systeemtijd. Bij verbindingsverlies of andere servers loopt deze door "
    L"vanaf de laatste geldige synchronisatie tot een nieuw antwoord; de toestand blijft behouden tot de "
    L"toepassing sluit.\r\n\r\nTijd registreert NTP-aanvragen sinds de start. Een record bevat de datum, "
    L"lokale computertijd, server en status. OK is een geldig antwoord, θ de afwijking van "
    L"Windows-systeemtijd. ERR geeft de oorzaak en eventuele foutcode. Het laatste record van een groep toont "
    L"de gecombineerde afwijking Θ als bruikbare metingen bestaan. Afwijkingen zijn in milliseconden met vier "
    L"decimalen: positief betekent dat de server voorloopt, negatief dat deze achterloopt. Θ is gebaseerd op "
    L"geaccepteerde metingen en staat ook in de synchronisatiestatus. Logboek opslaan exporteert CSV met "
    L"afwijkingen en foutdetails. Records worden niet tussen sessies bewaard; sla ze zo nodig vóór afsluiten "
    L"op.",
    L"\r\n\r\nSursa de timp și jurnalul NTP\r\nOră alege ora sistemului Windows sau servere NTP pentru "
    L"întreaga aplicație. NTP modifică numai ora CalClock; ceasul Windows nu se schimbă. Până la primul "
    L"răspuns valid se folosește ora sistemului. NTP este implicit. Grupul automat alege după regiunea "
    L"sistemului servere cehe și slovace, PTB pentru Europa sau un grup mondial. Măsurătorile sunt filtrate "
    L"după întârzierea rețelei și abaterile față de alte răspunsuri. Sincronizare acum începe imediat o "
    L"măsurătoare nouă.\r\n\r\nDupă sincronizare, ceasul CalClock funcționează independent de modificările "
    L"ulterioare ale orei sistemului Windows. La pierderea conexiunii sau schimbarea serverelor continuă de la"
    L" ultima sincronizare validă până la un nou răspuns; starea se păstrează până la închiderea "
    L"aplicației.\r\n\r\nOră înregistrează cererile NTP de la pornire. Intrarea conține data, ora locală a "
    L"calculatorului, serverul și starea. OK indică un răspuns valid; θ abaterea față de ora Windows. ERR "
    L"oferă cauza și eventualul cod de eroare. Ultima intrare a grupului arată și abaterea combinată Θ dacă "
    L"există măsurători utilizabile. Abaterile sunt în milisecunde cu patru zecimale: pozitiv înseamnă că "
    L"serverul este înainte, negativ că rămâne în urmă. Θ se bazează pe măsurătorile acceptate și apare în "
    L"starea sincronizării. Salvare jurnal exportă CSV cu abateri și detalii de eroare. Înregistrările nu "
    L"rămân între sesiuni; salvați înainte de ieșire dacă sunt necesare.",
    L"\r\n\r\nΠηγή ώρας και καταγραφή NTP\r\nΗ Ώρα επιλέγει ώρα συστήματος Windows ή διακομιστές NTP για όλη "
    L"την εφαρμογή. Το NTP αλλάζει μόνο την ώρα του CalClock· το ρολόι των Windows δεν αλλάζει. Μέχρι την "
    L"πρώτη έγκυρη απάντηση χρησιμοποιείται η ώρα συστήματος. Το NTP είναι η προεπιλογή. Η αυτόματη ομάδα "
    L"επιλέγει βάσει περιοχής συστήματος τσεχικούς και σλοβακικούς διακομιστές, PTB για την Ευρώπη ή παγκόσμια"
    L" ομάδα. Οι μετρήσεις φιλτράρονται βάσει καθυστέρησης δικτύου και απόκλισης από άλλες απαντήσεις. Ο "
    L"Συγχρονισμός τώρα αρχίζει αμέσως νέα μέτρηση.\r\n\r\nΜετά τον συγχρονισμό το ρολόι του CalClock "
    L"λειτουργεί ανεξάρτητα από μεταγενέστερες αλλαγές της ώρας συστήματος των Windows. Σε απώλεια σύνδεσης ή "
    L"αλλαγή διακομιστών συνεχίζει από τον τελευταίο έγκυρο συγχρονισμό μέχρι νέα απάντηση· η κατάσταση "
    L"διατηρείται μέχρι το κλείσιμο.\r\n\r\nΗ Ώρα καταγράφει ερωτήματα NTP από την εκκίνηση. Κάθε εγγραφή έχει"
    L" ημερομηνία, τοπική ώρα υπολογιστή, διακομιστή και κατάσταση. OK σημαίνει έγκυρη απάντηση, θ τη "
    L"μετατόπισή της από τα Windows. ERR δίνει αιτία και τυχόν κωδικό σφάλματος. Η τελευταία εγγραφή ομάδας "
    L"δείχνει και τη συνδυασμένη απόκλιση Θ αν υπάρχουν χρήσιμες μετρήσεις. Οι αποκλίσεις είναι σε χιλιοστά "
    L"δευτερολέπτου με τέσσερα δεκαδικά: θετική σημαίνει ότι ο διακομιστής προηγείται, αρνητική ότι "
    L"καθυστερεί. Το Θ βασίζεται σε αποδεκτές μετρήσεις και φαίνεται στην κατάσταση συγχρονισμού. Η Αποθήκευση"
    L" αρχείου καταγραφής εξάγει CSV με αποκλίσεις και λεπτομέρειες σφαλμάτων. Οι εγγραφές δεν διατηρούνται "
    L"μεταξύ εκκινήσεων· αποθηκεύστε τις πριν από την έξοδο αν χρειάζονται.",
    L"\r\n\r\nIzvor vremena\r\nKartica Vrijeme bira sistemsko vrijeme Windowsa ili podešene NTP servere za "
    L"cijeli program i sve vidžete. NTP mijenja samo vrijeme prikazano u CalClocku; sat Windowsa nikad se ne "
    L"mijenja. Do prvog valjanog odgovora koristi se sistemsko vrijeme. NTP je podrazumijevani izbor. "
    L"Automatski skup prema regiji sistema bira češke i slovačke servere, PTB za Europu ili globalni skup. "
    L"Mjerenja se filtriraju prema mrežnom kašnjenju i odstupanjima od ostalih odgovora. Sinhroniziraj sada "
    L"odmah pokreće novo mjerenje.\r\n\r\nNakon sinhronizacije sat CalClocka nastavlja raditi nezavisno od "
    L"naknadnih promjena sistemskog vremena Windowsa. Pri prekidu veze ili promjeni servera nastavlja od "
    L"posljednje valjane sinhronizacije do novog odgovora; stanje se čuva do zatvaranja "
    L"programa.\r\n\r\nZapisnik NTP sinhronizacije\r\n\r\nKartica Vrijeme bilježi upite NTP serverima od "
    L"pokretanja programa. Svaki zapis sadrži datum i lokalno vrijeme računara, server i stanje. OK označava "
    L"valjan odgovor; θ prikazuje odstupanje od sistemskog vremena Windowsa. ERR navodi uzrok i eventualnu "
    L"šifru greške. Posljednji zapis skupine upita prikazuje i objedinjeno odstupanje Θ ako postoje "
    L"upotrebljiva mjerenja.\r\n\r\nOdstupanja su u milisekundama s četiri decimalna mjesta. Pozitivna "
    L"vrijednost znači da je sat servera ispred Windowsa, a negativna da kasni. Objedinjeno Θ temelji se na "
    L"prihvaćenim mjerenjima i prikazuje se i u stanju sinhronizacije.\r\n\r\nSačuvaj zapisnik izvozi zapise u"
    L" CSV, uključujući odstupanja i pojedinosti grešaka. Zapisi se ne čuvaju između pokretanja; sačuvajte ih "
    L"prije izlaska ako ih želite zadržati.",
    L"\r\n\r\nIzvor vremena\r\nKartica Vrijeme bira sustavsko vrijeme Windowsa ili zadane NTP poslužitelje za "
    L"cijeli program i sve widgete. NTP mijenja samo vrijeme prikazano u CalClocku; sat Windowsa nikad se ne "
    L"mijenja. Do prvog valjanog odgovora koristi se sustavsko vrijeme. NTP je zadani izbor. Automatski skup "
    L"prema regiji sustava bira češke i slovačke poslužitelje, PTB za Europu ili globalni skup. Mjerenja se "
    L"filtriraju prema mrežnom kašnjenju i odstupanjima od ostalih odgovora. Sinkroniziraj sada odmah pokreće "
    L"novo mjerenje.\r\n\r\nNakon sinkronizacije sat CalClocka nastavlja raditi neovisno o naknadnim "
    L"promjenama sustavskog vremena Windowsa. Pri prekidu veze ili promjeni poslužitelja nastavlja od "
    L"posljednje valjane sinkronizacije do novog odgovora; stanje se čuva do zatvaranja "
    L"programa.\r\n\r\nZapisnik NTP sinkronizacije\r\n\r\nKartica Vrijeme bilježi upite NTP poslužiteljima od "
    L"pokretanja programa. Svaki zapis sadrži datum i lokalno vrijeme računala, poslužitelj i stanje. OK "
    L"označava valjan odgovor; θ prikazuje odstupanje od sustavskog vremena Windowsa. ERR navodi uzrok i "
    L"eventualnu šifru pogreške. Posljednji zapis skupine upita prikazuje i objedinjeno odstupanje Θ ako "
    L"postoje upotrebljiva mjerenja.\r\n\r\nOdstupanja su u milisekundama s četiri decimalna mjesta. Pozitivna"
    L" vrijednost znači da je sat poslužitelja ispred Windowsa, a negativna da kasni. Objedinjeno Θ temelji se"
    L" na prihvaćenim mjerenjima i prikazuje se i u stanju sinkronizacije.\r\n\r\nSpremi zapisnik izvozi "
    L"zapise u CSV, uključujući odstupanja i pojedinosti pogrešaka. Zapisi se ne čuvaju između pokretanja; "
    L"spremite ih prije izlaska ako ih želite zadržati.",
    L"\r\n\r\nVir časa\r\nZavihek Čas izbere sistemski čas Windows ali strežnike NTP za celoten program. NTP "
    L"spremeni le čas CalClocka, ure Windows nikoli. Do prvega veljavnega odgovora se uporablja sistemski čas."
    L" NTP je privzet. Samodejni nabor glede na regijo izbere češke in slovaške strežnike, PTB za Evropo ali "
    L"svetovni nabor. Meritve se filtrirajo po omrežni zakasnitvi in odstopanjih. Sinhroniziraj zdaj takoj "
    L"sproži novo meritev.\r\n\r\nPo sinhronizaciji ura CalClock teče neodvisno od poznejših sprememb "
    L"sistemske ure Windows. Ob izgubi povezave ali menjavi strežnikov teče od zadnje veljavne sinhronizacije "
    L"do novega odgovora; stanje se ohrani do zaprtja programa.\r\n\r\nDnevnik sinhronizacije "
    L"NTP\r\n\r\nZavihek Čas beleži poizvedbe strežnikom NTP od zagona programa. Zapis vsebuje datum in "
    L"krajevni čas računalnika, strežnik in stanje. OK označuje veljaven odgovor s θ kot odmikom od ure "
    L"Windows. ERR navede razlog in morebitno kodo napake. Zadnji zapis skupine poizvedb vsebuje tudi skupni "
    L"odmik Θ, če so na voljo uporabne meritve.\r\n\r\nOdmiki so v milisekundah s štirimi decimalnimi mesti. "
    L"Pozitivna vrednost pomeni, da je strežnik pred uro Windows, negativna pa za njo. Θ upošteva sprejete "
    L"meritve in je prikazan tudi v stanju sinhronizacije. Shrani dnevnik izvozi zapise v CSV z odmiki in "
    L"podrobnostmi napak. Zapisi se ne ohranijo med zagoni; pred izhodom jih shranite, če jih želite obdržati.",
    L"\r\n\r\nIzvor vremena\r\nKartica Vrijeme bira sistemsko vrijeme Windows-a ili NTP servere za cijeli "
    L"program. NTP mijenja samo prikaz CalClock-a; sat Windows-a se nikada ne mijenja. Do prvog ispravnog "
    L"odgovora koristi se sistemsko vrijeme. NTP je podrazumijevan. Automatska grupa prema regionu sistema "
    L"bira češke i slovačke servere, PTB za Evropu ili globalni skup. Mjerenja se filtriraju prema mrežnom "
    L"kašnjenju i odstupanjima od ostalih odgovora. Sinhronizuj sada odmah počinje novo "
    L"mjerenje.\r\n\r\nPoslije sinhronizacije sat CalClock-a nastavlja nezavisno od kasnijih promjena "
    L"sistemskog vremena Windows-a. Pri gubitku veze ili promjeni servera nastavlja od posljednje ispravne "
    L"sinhronizacije do novog odgovora; stanje se čuva do zatvaranja programa.\r\n\r\nDnevnik NTP "
    L"sinhronizacije\r\n\r\nKartica Vrijeme bilježi upite NTP serverima od pokretanja programa. Zapis sadrži "
    L"datum i lokalno vrijeme računara, server i stanje. OK označava ispravan odgovor; θ njegovo odstupanje od"
    L" sistemskog vremena Windows-a. ERR navodi uzrok i eventualnu šifru greške. Posljednji zapis grupe upita "
    L"pokazuje i objedinjeno odstupanje Θ kada postoje upotrebljiva mjerenja.\r\n\r\nOdstupanja su u "
    L"milisekundama sa četiri decimale. Pozitivna vrijednost znači da je server ispred Windows-a, negativna da"
    L" kasni. Θ se zasniva na prihvaćenim mjerenjima i vidi se i u stanju sinhronizacije. Sačuvaj dnevnik "
    L"izvozi zapise u CSV sa odstupanjima i detaljima grešaka. Zapisi se ne čuvaju između pokretanja; "
    L"sačuvajte ih prije izlaska ako želite da ostanu.",
    L"\r\n\r\nКрыніца часу\r\nУкладка «Час» выбірае сістэмны час Windows або серверы NTP для ўсёй праграмы. "
    L"NTP змяняе толькі час CalClock, а не гадзіннік Windows. Да першага карэктнага адказу выкарыстоўваецца "
    L"сістэмны час. NTP выбраны першапачаткова. Аўтаматычны набор паводле сістэмнага рэгіёна выбірае чэшскія і"
    L" славацкія серверы, PTB для Еўропы або глабальны пул. Вымярэнні фільтруюцца паводле сеткавай затрымкі і "
    L"адхілення ад іншых адказаў. «Сінхранізаваць зараз» адразу пачынае новае вымярэнне.\r\n\r\nПасля "
    L"сінхранізацыі гадзіннік CalClock працягвае адлік незалежна ад наступных змен сістэмнага часу Windows. "
    L"Пры страце сувязі ці змене сервераў ён працягвае адлік ад апошняй карэктнай сінхранізацыі да новага "
    L"адказу; стан захоўваецца да закрыцця праграмы.\r\n\r\nЖурнал сінхранізацыі NTP\r\n\r\nУкладка «Час» "
    L"запісвае запыты да сервераў NTP ад запуску праграмы. Запіс мае дату і мясцовы час камп’ютара, сервер і "
    L"стан. OK пазначае карэктны адказ, θ — адхіленне ад сістэмнага часу Windows. ERR паказвае прычыну і "
    L"магчымы код памылкі. Апошні запіс групы запытаў мае таксама аб’яднанае адхіленне Θ, калі ёсць прыдатныя "
    L"вымярэнні.\r\n\r\nАдхіленні паказваюцца ў мілісекундах з чатырма дзесятковымі знакамі. Дадатнае значэнне"
    L" азначае, што сервер апярэджвае Windows, адмоўнае — што адстае. Θ улічвае прынятыя вымярэнні і "
    L"паказваецца ў стане сінхранізацыі. «Захаваць журнал» экспартуе запісы ў CSV з адхіленнямі і звесткамі "
    L"пра памылкі. Запісы не захоўваюцца паміж запускамі; перад выхадам захавайце іх, калі хочаце пакінуць.",
    L"\r\n\r\nИзточник на време\r\nРазделът „Време“ избира системното време на Windows или NTP сървъри за "
    L"цялата програма. NTP променя само времето на CalClock; часовникът на Windows не се променя. До първия "
    L"валиден отговор се използва системното време. NTP е избрано по подразбиране. Автоматичният набор според "
    L"системния регион избира чешки и словашки сървъри, PTB за Европа или глобален пул. Измерванията се "
    L"филтрират по мрежовото закъснение и отклоненията от другите отговори. „Синхронизирай сега“ започва ново "
    L"измерване веднага.\r\n\r\nСлед синхронизация часовникът на CalClock работи независимо от последващи "
    L"промени на системното време на Windows. При загуба на връзка или смяна на сървъри продължава от "
    L"последната валидна синхронизация до нов отговор; състоянието се пази до затваряне на "
    L"програмата.\r\n\r\nДневник на NTP синхронизацията\r\n\r\nРазделът „Време“ записва запитванията към NTP "
    L"сървърите от стартирането на програмата. Всеки запис има дата и местно време на компютъра, сървър и "
    L"състояние. OK означава валиден отговор, θ — отклонението от системното време на Windows. ERR дава "
    L"причината и евентуален код за грешка. Последният запис на група запитвания включва и общото отклонение Θ"
    L" при налични използваеми измервания.\r\n\r\nОтклоненията са в милисекунди с четири знака след десетичния"
    L" разделител. Положителна стойност означава, че сървърът е пред Windows, отрицателна — че изостава. Θ "
    L"отчита приетите измервания и се вижда в състоянието на синхронизацията. „Запази дневника“ експортира "
    L"записите в CSV с отклоненията и подробностите за грешките. Записите не се пазят между стартиранията; "
    L"запишете ги преди изход, ако искате да ги запазите.",
    L"\r\n\r\nИзвор на време\r\nКартичката „Време“ избира системско време на Windows или сервери NTP за целата"
    L" програма. NTP го менува само времето на CalClock, никогаш часовникот на Windows. До првиот важечки "
    L"одговор се користи системско време. NTP е стандардниот избор. Автоматската група според регионот избира "
    L"чешки и словачки сервери, PTB за Европа или глобалната група. Мерењата се филтрираат според мрежното "
    L"доцнење и отстапувањата од другите одговори. „Синхронизирај сега“ почнува ново мерење веднаш.\r\n\r\nПо "
    L"синхронизацијата часовникот на CalClock работи независно од подоцнежните промени на системското време на"
    L" Windows. При губење врска или промена на сервери продолжува од последната важечка синхронизација до нов"
    L" одговор; состојбата се чува до затворање на програмата.\r\n\r\nДневник на синхронизацијата "
    L"NTP\r\n\r\nКартичката „Време“ ги бележи барањата до серверите NTP од стартувањето на програмата. Записот"
    L" содржи датум и локално време на компјутерот, сервер и состојба. OK значи важечки одговор, θ — "
    L"отстапување од системското време на Windows. ERR ги дава причината и можниот код за грешка. Последниот "
    L"запис на група барања го покажува и заедничкото отстапување Θ ако постојат употребливи "
    L"мерења.\r\n\r\nОтстапувањата се во милисекунди со четири децимални места. Позитивно значи дека серверот "
    L"е пред Windows, негативно дека доцни. Θ ги зема предвид прифатените мерења и се покажува и во состојбата"
    L" на синхронизацијата. „Зачувај дневник“ ги извезува записите во CSV со отстапувањата и деталите за "
    L"грешките. Записите не се чуваат меѓу стартувањата; зачувајте ги пред излез ако сакате да останат.",
    L"\r\n\r\nИзвор времена\r\nКартица Време бира системско време Windows-а или NTP сервере за цео програм. "
    L"NTP мења само приказ CalClock-а; сат Windows-а се никада не мења. До првог исправног одговора користи се"
    L" системско време. NTP је подразумеван. Аутоматска група према региону система бира чешке и словачке "
    L"сервере, PTB за Европу или глобални скуп. Мерења се филтрирају према мрежном кашњењу и одступањима од "
    L"осталих одговора. Синхронизуј сада одмах почиње ново мерење.\r\n\r\nПосле синхронизације сат CalClock-а "
    L"наставља независно од каснијих промена системског времена Windows-а. При губитку везе или промени "
    L"сервера наставља од последње исправне синхронизације до новог одговора; стање се чува до затварања "
    L"програма.\r\n\r\nДневник NTP синхронизације\r\n\r\nКартица Време бележи упите NTP серверима од покретања"
    L" програма. Запис садржи датум и локално време рачунара, сервер и стање. OK означава исправан одговор; θ "
    L"његово одступање од системског времена Windows-а. ERR наводи узрок и евентуалну шифру грешке. Последњи "
    L"запис групе упита показује и обједињено одступање Θ када постоје употребљива мерења.\r\n\r\nОдступања су"
    L" у милисекундама са четири децимале. Позитивна вредност значи да је сервер испред Windows-а, негативна "
    L"да касни. Θ се заснива на прихваћеним мерењима и види се и у стању синхронизације. Сачувај дневник "
    L"извози записе у CSV са одступањима и детаљима грешака. Записи се не чувају између покретања; сачувајте "
    L"их пре изласка ако желите да остану.",
    L"\r\n\r\nДЖЕРЕЛО ЧАСУ\r\nНа вкладці «Час» вибирається системний час Windows або налаштовані сервери NTP "
    L"для всієї програми та всіх віджетів. NTP коригує лише час CalClock, не змінюючи годинник Windows. До "
    L"першої коректної відповіді використовується системний час. NTP вибрано за замовчуванням. Автоматичний "
    L"набір вибирає чеські та словацькі сервери, PTB для Європи або глобальний пул відповідно до системного "
    L"регіону. Кілька вимірювань фільтруються за мережевою затримкою та відхиленням від інших відповідей. "
    L"«Синхронізувати зараз» негайно запускає нове вимірювання.\r\n\r\nПісля синхронізації годинник CalClock "
    L"продовжує відлік незалежно від подальших змін системного часу Windows. У разі втрати зв’язку або зміни "
    L"серверів він продовжує відлік від останньої коректної синхронізації до отримання нової відповіді; цей "
    L"стан зберігається до закриття програми.\r\n\r\nЖУРНАЛ СИНХРОНІЗАЦІЇ NTP\r\nВкладка «Час» містить журнал "
    L"запитів до серверів NTP від початку роботи програми. Кожен запис містить дату й місцевий час комп’ютера,"
    L" сервер і стан. OK позначає коректну відповідь; θ показує відхилення від системного часу Windows. ERR "
    L"містить причину збою та, за наявності, код помилки. Останній запис групи запитів також показує об’єднане"
    L" відхилення Θ, якщо отримано придатні вимірювання.\r\n\r\nВідхилення показуються в мілісекундах із "
    L"чотирма десятковими знаками. Додатне значення означає, що час сервера випереджає Windows, від’ємне — що "
    L"він відстає. Об’єднане відхилення Θ розраховується за прийнятими вимірюваннями й також показується у "
    L"стані синхронізації.\r\n\r\nКоманда «Зберегти журнал» експортує записи до CSV разом із відхиленнями та "
    L"відомостями про помилки. Між запусками програми журнал не зберігається; за потреби збережіть його перед "
    L"виходом.",
    L"\r\n\r\nИСТОЧНИК ВРЕМЕНИ\r\nНа вкладке «Время» выбирается системное время Windows или настроенные "
    L"серверы NTP для всей программы и всех виджетов. NTP корректирует только время CalClock, не меняя часы "
    L"Windows. До первого корректного ответа используется системное время. NTP выбран по умолчанию. "
    L"Автоматический набор выбирает чешские и словацкие серверы, PTB для Европы или глобальный пул в "
    L"соответствии с системным регионом. Несколько измерений фильтруются по сетевой задержке и отклонению от "
    L"других ответов. «Синхронизировать сейчас» немедленно запускает новое измерение.\r\n\r\nПосле "
    L"синхронизации часы CalClock продолжают отсчёт независимо от последующих изменений системного времени "
    L"Windows. При потере связи или смене серверов они продолжают отсчёт от последней корректной синхронизации"
    L" до получения нового ответа; это состояние сохраняется до закрытия программы.\r\n\r\nЖУРНАЛ "
    L"СИНХРОНИЗАЦИИ NTP\r\nВкладка «Время» содержит журнал запросов к серверам NTP с начала работы программы. "
    L"Каждая запись содержит дату и местное время компьютера, сервер и состояние. OK обозначает корректный "
    L"ответ; θ показывает отклонение от системного времени Windows. ERR содержит причину сбоя и, при наличии, "
    L"код ошибки. Последняя запись группы запросов также показывает объединённое отклонение Θ, если получены "
    L"пригодные измерения.\r\n\r\nОтклонения показываются в миллисекундах с четырьмя десятичными знаками. "
    L"Положительное значение означает, что время сервера опережает Windows, отрицательное — что оно отстаёт. "
    L"Объединённое отклонение Θ рассчитывается по принятым измерениям и также показывается в состоянии "
    L"синхронизации.\r\n\r\nКоманда «Сохранить журнал» экспортирует записи в CSV вместе с отклонениями и "
    L"сведениями об ошибках. Между запусками программы журнал не сохраняется; при необходимости сохраните его "
    L"перед выходом."
};

const wchar_t* HELP_FULLSCREEN_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nHODINY NA MONITORU\r\nDigitální hodiny mohou vyplnit jeden či více monitorů a volitelně "
    L"zatemnit ostatní. Velikost písma se udává procentem výšky monitoru; nastavit lze také písmo, "
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
    L"others. Font size is a percentage of monitor height; font, smoothing, colors and padding are also "
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
    L"optional abdunkeln. Die Schriftgröße ist ein Prozentsatz der Monitorhöhe; Schrift, Glättung, Farben "
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
    L"assombrir les autres. La taille de police est un pourcentage de la hauteur ; police, lissage, "
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
    L"demás. El tamaño de fuente es un porcentaje de la altura; también se configuran "
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
    L"altri. La dimensione del carattere è una percentuale dell’altezza; sono configurabili anche "
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
    L"\r\n\r\nZEGAR NA MONITORZE\r\nZegar cyfrowy może zająć jeden lub kilka monitorów i wygasić pozostał"
    L"e. Rozmiar czcionki jest procentem wysokości monitora; można też ustawić czcionkę, wygładzanie, "
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
    L"ostatné. Veľkosť písma je percentom výšky monitora; nastaviť možno aj písmo, vyhladzovanie, farby a "
    L"odsadenie. V režime UTC možno zobraziť "
    L"text UTC na samostatnom riadku. Predvolené je biele písmo na čiernom pozadí. Pri otvorenom Nastavení "
    L"sú hodiny vždy iba malým presúvateľným "
    L"náhľadom s pomerom strán monitora a jeho poloha sa ukladá. Zarovnanie do mriežky tento typ ignoruje. "
    L"Esc skryje hodiny aj stmavenie aj pri "
    L"aktívnom Nastavení.\r\n\r\nNad celomonitorovými hodinami aj zatemnenými monitormi sa kurzor po chvíli "
    L"nečinnosti skryje a pri pohybe myši "
    L"sa znovu objaví. Nad zmenšeným náhľadom v režime Nastavenia zostáva viditeľný.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and optionally black out the "
    L"others. Font size is a percentage of monitor height; font, smoothing, colours and padding are "
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
    L"others. Font size is a percentage of monitor height; font, smoothing, colours and padding are "
    L"also configurable. In UTC mode, UTC can "
    L"be shown on a separate line. The default is white text on black. While Settings is open, the clock is "
    L"always a small draggable preview that "
    L"keeps the monitor aspect ratio, and its position is saved. Grid arrangement ignores and does not move "
    L"this widget type. Esc hides the clock "
    L"and removes blackouts even when Settings is active.\r\n\r\nThe pointer hides after a short period of "
    L"inactivity over monitor clocks and "
    L"blacked-out monitors, and reappears when the mouse moves. It stays visible over the small preview "
    L"while Settings is open.",
    L"\r\n\r\nRELÓGIO NO MONITOR\r\nO relógio digital pode preencher um ou vários monitores e escurecer os restantes. A letra é uma percentagem "
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
    L"\r\n\r\nMONİTÖR SAATİ\r\nDijital saat bir veya daha fazla monitörü doldurabilir ve diğerlerini karartabilir. Yazı tipi boyutu monitör "
    L"yüksekliğinin yüzdesidir; yazı tipi, kenar yumuşatma, renkler ve dolgu da ayarlanabilir. Ayarlar "
    L"açıkken her zaman küçük, sürüklenebilir "
    L"bir önizleme gösterilir. Esc saati gizler ve karartmayı kaldırır.\r\n\r\nİşaretçi, monitör saatleri ve "
    L"karartılmış monitörler üzerinde kısa "
    L"bir hareketsizlikten sonra gizlenir ve fare hareket edince yeniden görünür. Ayarlar açıkken küçük "
    L"önizleme üzerinde görünür kalır.",
    L"\r\n\r\nEkraanikell\r\nDigitaalkell võib täita ühe või mitu kuvarit ja tumendada ülejäänud. Fondisuurus on protsent kuvari kõrgusest; valida saab ka fondi, silumise, värvid "
    L"ja siseveerise. UTC võib olla eraldi real. Vaikimisi on tekst valge ja taust must. Avatud sätetega "
    L"esitatakse kella väikese liigutatava eelvaatena, mis säilitab kuvari kuvasuhte ja mille asukoht "
    L"salvestatakse. Ruudustikupaigutus seda tüüpi ei liiguta. Esc peidab kella ja eemaldab tumenduse ka "
    L"avatud sätetega.\r\n\r\nHiirekursor peitub ekraanikella või tumendatud kuvarite kohal pärast lühikest "
    L"tegevusetust ning ilmub hiire liigutamisel. Väikese eelvaate kohal jääb see nähtavaks.",
    L"\r\n\r\nClog scáileáin\r\nIs féidir le clog digiteach monatóir amháin nó níos mó a líonadh agus na cinn "
    L"eile a dhorchú. Is céatadán d’airde an mhonatóra an clómhéid;"
    L" tá cló, frithailiasáil, dathanna agus spásáil inmheánach ar fáil freisin. Is féidir UTC a chur ar "
    L"shraith ar leith. Téacs bán ar chúlra dubh atá ann ar dtús. Nuair atá Socruithe oscailte, is réamhamharc"
    L" beag inaistrithe é le cóimheas treoíochta an mhonatóra agus suíomh sábháilte. Ní bhogann an eangach an "
    L"cineál seo. Folaíonn Esc an clog agus baintear dorchú fiú nuair atá Socruithe oscailte.\r\n\r\nFolaítear"
    L" an pointeoir tar éis tréimhse ghairid gan ghníomhaíocht os cionn an chloig nó monatóirí dorchaithe agus"
    L" tagann sé ar ais le gluaiseacht luiche. Fanann sé infheicthe os cionn an réamhamhairc bhig.",
    L"\r\n\r\nEkrano laikrodis\r\nSkaitmeninis laikrodis gali užpildyti vieną ar kelis monitorius ir užtemdyti"
    L" kitus. Šrifto dydis yra monitoriaus aukščio procentas; "
    L"pasirenkamas šriftas, glodinimas, spalvos ir vidinė paraštė. UTC gali būti atskiroje eilutėje. "
    L"Numatytasis vaizdas – baltas tekstas juodame fone. Kol atidaryti parametrai, rodomas mažas perkeliamas "
    L"peržiūros langas, išlaikantis monitoriaus proporcijas ir įrašomą padėtį. Tinklelis šio tipo neperkelia. "
    L"Esc paslepia laikrodį ir pašalina užtemdymą net atidarius parametrus.\r\n\r\nPelės žymeklis virš ekrano "
    L"laikrodžio ir užtemdytų monitorių pasislepia po trumpos neveiklos ir vėl pasirodo pajudinus pelę. Virš "
    L"mažos peržiūros jis lieka matomas.",
    L"\r\n\r\nEkrāna pulkstenis\r\nDigitālais pulkstenis var aizpildīt vienu vai vairākus monitorus un "
    L"aptumšot pārējos. Fonta lielums ir procenti no monitora "
    L"augstuma; izvēlami fonts, nogludināšana, krāsas un iekšējā atkāpe. UTC var būt atsevišķā rindā. "
    L"Noklusējums ir balts teksts uz melna fona. Kamēr atvērti iestatījumi, redzams mazs pārvietojams "
    L"priekšskatījums ar monitora malu attiecību un saglabājamu novietojumu. Režģis šo tipu nepārvieto. Esc "
    L"paslēpj pulksteni un noņem aptumšojumu arī tad, ja iestatījumi ir atvērti.\r\n\r\nPeles rādītājs virs "
    L"ekrāna pulksteņa un aptumšotajiem monitoriem pēc īsas neaktivitātes pazūd un atgriežas, pakustinot peli."
    L" Virs mazā priekšskatījuma tas paliek redzams.",
    L"\r\n\r\nKépernyőóra\r\nA digitális óra egy vagy több monitort kitölthet, a többit elsötétítheti. A betűméret a monitor magasságának százaléka; betűtípus, "
    L"élsimítás, színek és belső margó is választható. Az UTC külön sorban lehet. Alapból fehér szöveg jelenik"
    L" meg fekete háttéren. Nyitott Beállítások mellett az óra kicsi, mozgatható előnézet a monitor "
    L"képarányával, mentett helyzettel. A rács ezt a típust nem mozgatja. Az Esc nyitott Beállítások mellett "
    L"is elrejti az órát és megszünteti az elsötétítést.\r\n\r\nAz egérmutató rövid tétlenség után eltűnik a "
    L"képernyőóra és az elsötétített monitorok fölött, és egérmozgáskor visszatér. A kis előnézet fölött "
    L"látható marad.",
    L"\r\n\r\nArloġġ tal-iskrin\r\nArloġġ diġitali jista’ jimla moniter wieħed jew aktar u jdallam l-oħrajn"
    L". Id-daqs tal-font huwa perċentwal tal-għoli tal-moniter; "
    L"jintgħażlu wkoll font, anti-aliasing, kuluri u spazju intern. UTC jista’ jkun f’ringiela separata. "
    L"Id-default huwa test abjad fuq sfond iswed. Bis-Settings miftuħa, l-arloġġ huwa previżjoni żgħira li "
    L"tista’ titmexxa bil-proporzjonijiet tal-moniter u pożizzjoni ssejvjata. Il-gradilja ma tmexxix dan "
    L"it-tip. Esc jaħbi l-arloġġ u jneħħi d-dlam anki bis-Settings miftuħa.\r\n\r\nIl-pointer tal-maws jinħeba"
    L" wara ftit inattività fuq l-arloġġ jew il-moniters mudlama u jerġa’ jidher meta jiċċaqlaq il-maws. Fuq "
    L"il-previżjoni żgħira jibqa’ viżibbli.",
    L"\r\n\r\nSchermklok\r\nEen digitale klok kan een of meer beeldschermen vullen en de andere verduisteren"
    L". De tekengrootte is een percentage van de schermhoogte; "
    L"lettertype, vereffening, kleuren en binnenmarge zijn instelbaar. UTC kan op een aparte rij staan. "
    L"Standaard is de tekst wit op zwart. Met Instellingen geopend is de klok een klein verplaatsbaar "
    L"voorbeeld met de beeldverhouding van het scherm en een opgeslagen positie. Het raster verplaatst dit "
    L"type niet. Esc verbergt de klok en verwijdert verduistering, ook met Instellingen geopend.\r\n\r\nDe "
    L"muisaanwijzer verdwijnt na korte inactiviteit boven de schermklok en verduisterde schermen en verschijnt"
    L" bij bewegen. Boven het kleine voorbeeld blijft deze zichtbaar.",
    L"\r\n\r\nCeas pe ecran\r\nUn ceas digital poate umple unul sau mai multe monitoare și le poate întuneca "
    L"pe celelalte. Dimensiunea fontului este procent din înălțimea "
    L"monitorului; se pot alege fontul, netezirea, culorile și spațierea interioară. UTC poate fi pe un rând "
    L"separat. Implicit, textul este alb pe fundal negru. Cu Setări deschis, ceasul este o previzualizare "
    L"mică, mobilă, cu proporțiile monitorului și poziție salvată. Grila nu mută acest tip. Esc ascunde ceasul"
    L" și elimină întunecarea chiar cu Setări deschis.\r\n\r\nIndicatorul mouse-ului se ascunde după o scurtă "
    L"inactivitate deasupra ceasului și monitoarelor întunecate și reapare la mișcare. Deasupra "
    L"previzualizării mici rămâne vizibil.",
    L"\r\n\r\nΡολόι οθόνης\r\nΨηφιακό ρολόι μπορεί να γεμίσει μία ή περισσότερες οθόνες και να συσκοτίσει τις "
    L"υπόλοιπες. Το μέγεθος γραμματοσειράς είναι ποσοστό του "
    L"ύψους οθόνης· επιλέγονται γραμματοσειρά, εξομάλυνση, χρώματα και εσωτερικό περιθώριο. Το UTC μπορεί να "
    L"έχει χωριστή γραμμή. Προεπιλογή είναι λευκό κείμενο σε μαύρο φόντο. Με ανοιχτές Ρυθμίσεις το ρολόι είναι"
    L" μικρή μετακινούμενη προεπισκόπηση με αναλογία οθόνης και αποθηκευμένη θέση. Το πλέγμα δεν μετακινεί "
    L"αυτόν τον τύπο. Το Esc κρύβει το ρολόι και αφαιρεί τη συσκότιση ακόμη και με ανοιχτές "
    L"Ρυθμίσεις.\r\n\r\nΟ δείκτης ποντικιού κρύβεται μετά από λίγη αδράνεια πάνω από το ρολόι και τις "
    L"συσκοτισμένες οθόνες και επιστρέφει με κίνηση. Πάνω από τη μικρή προεπισκόπηση παραμένει ορατός.",
    L"\r\n\r\nSat na ekranu\r\nDigitalni sat može ispuniti jedan ili više ekrana i po potrebi zatamniti "
    L"ostale. Veličina fonta zadaje se kao postotak visine ekrana; mogu "
    L"se podesiti i font, izglađivanje, boje i unutrašnji razmak. U načinu UTC oznaka UTC može biti u zasebnom"
    L" redu. Podrazumijevani je izgled bijeli tekst na crnoj pozadini. Dok su Postavke otvorene, sat je mali "
    L"pomični pregled koji čuva omjer stranica ekrana; njegov se položaj čuva. Raspoređivanje u mrežu "
    L"izostavlja tu vrstu vidžeta. Esc skriva sat i uklanja zatamnjenje i kada su Postavke "
    L"otvorene.\r\n\r\nPokazivač miša skriva se nakon kratke neaktivnosti iznad sata na ekranu i zatamnjenih "
    L"ekrana te se ponovno prikazuje nakon pomicanja miša. Iznad malog pregleda u Postavkama ostaje vidljiv.",
    L"\r\n\r\nSat na zaslonu\r\nDigitalni sat može ispuniti jedan ili više zaslona i po potrebi zatamniti "
    L"ostale. Veličina fonta zadaje se kao postotak visine zaslona; mogu"
    L" se podesiti i font, izglađivanje, boje i unutarnji razmak. U načinu UTC oznaka UTC može biti u zasebnom"
    L" retku. Zadani je izgled bijeli tekst na crnoj pozadini. Dok su Postavke otvorene, sat je mali pomični "
    L"pretpregled koji čuva omjer stranica zaslona; njegov se položaj sprema. Raspoređivanje u mrežu "
    L"izostavlja tu vrstu widgeta. Esc skriva sat i uklanja zatamnjenje i kada su Postavke "
    L"otvorene.\r\n\r\nPokazivač miša skriva se nakon kratke neaktivnosti iznad sata na zaslonu i zatamnjenih "
    L"zaslona te se ponovno prikazuje nakon pomicanja miša. Iznad malog pretpregleda u Postavkama ostaje "
    L"vidljiv.",
    L"\r\n\r\nUra na zaslonu\r\nDigitalna ura lahko zapolni enega ali več zaslonov in po potrebi zatemni "
    L"druge. Velikost pisave je odstotek višine zaslona; nastavljivi so "
    L"tudi pisava, glajenje, barve in notranji odmik. UTC je lahko v ločeni vrstici. Privzet je bel napis na "
    L"črni podlagi. Med odprtimi Nastavitvami je ura majhen premakljiv predogled z razmerjem stranic izbranega"
    L" zaslona; njegov položaj se shrani. Razporeditev v mrežo tega gradnika ne premika. Esc skrije uro in "
    L"odstrani zatemnitev tudi med odprtimi Nastavitvami.\r\n\r\nKazalec se po kratki nedejavnosti nad uro na "
    L"zaslonu ali zatemnjenimi zasloni skrije in ob premiku miške spet pokaže. Nad majhnim predogledom ostane "
    L"viden.",
    L"\r\n\r\nSat na monitoru\r\nDigitalni sat može popuniti jedan ili više monitora i zatamniti ostale"
    L". Veličina fonta zadaje se kao procenat visine monitora; podešavaju se "
    L"i font, umekšavanje, boje i unutrašnji razmak. UTC može biti u zasebnom redu. Podrazumijevan je bijeli "
    L"tekst na crnoj pozadini. Dok su Podešavanja otvorena, sat je mali pokretni pregled sa odnosom stranica "
    L"monitora; njegov položaj se čuva. Rasporedi u mrežu ne premješta tu vrstu vidžeta. Esc skriva sat i "
    L"uklanja zatamnjenje i kada su Podešavanja otvorena.\r\n\r\nPokazivač miša skriva se poslije kratke "
    L"neaktivnosti iznad sata na monitoru i zatamnjenih monitora, a pojavljuje pri pomjeranju miša. Iznad "
    L"malog pregleda ostaje vidljiv.",
    L"\r\n\r\nГадзіннік на маніторы\r\nЛічбавы гадзіннік можа займаць адзін ці некалькі манітораў і зацямняць "
    L"астатнія. Памер шрыфту — працэнт вышыні манітора; таксама задаюцца "
    L"шрыфт, згладжванне, колеры і ўнутраны водступ. UTC можа паказвацца асобным радком. Прадвызначаны выгляд "
    L"— белы тэкст на чорным фоне. Пры адкрытых наладах гадзіннік паказваецца маленькім рухомым праглядам з "
    L"прапорцыямі манітора; яго пазіцыя захоўваецца. Упарадкаванне па сетцы гэты віджэт не перамяшчае. Esc "
    L"хавае гадзіннік і прыбірае зацямненне нават з адкрытымі наладамі.\r\n\r\nПаказальнік мышы хаваецца пасля"
    L" кароткай бяздзейнасці над гадзіннікам на маніторы ці зацемненымі маніторамі і з’яўляецца пры руху мышы."
    L" Над маленькім праглядам ён застаецца бачным.",
    L"\r\n\r\nЧасовник на монитор\r\nЦифровият часовник може да запълни един или няколко монитора и да затъмни"
    L" останалите. Размерът на шрифта е процент от височината на "
    L"монитора; задават се и шрифт, изглаждане, цветове и вътрешен отстъп. UTC може да е на отделен ред. По "
    L"подразбиране текстът е бял върху черен фон. При отворени настройки часовникът е малък подвижен преглед "
    L"със съотношението на страните на монитора; позицията му се пази. Подреждането в мрежа не го премества. "
    L"Esc скрива часовника и премахва затъмнението дори при отворени настройки.\r\n\r\nПоказалецът се скрива "
    L"след кратко бездействие над часовника или затъмнените монитори и се показва отново при движение на "
    L"мишката. Над малкия преглед остава видим.",
    L"\r\n\r\nЧасовник на монитор\r\nДигиталниот часовник може да пополни еден или повеќе монитори и да ги "
    L"затемни другите. Големината на фонтот е процент од "
    L"височината на мониторот; се поставуваат и фонтот, измазнувањето, боите и внатрешната маргина. UTC може "
    L"да биде во одделен ред. Стандардно има бел текст на црна заднина. Додека се отворени поставките, "
    L"часовникот е мал подвижен преглед со односот на страните на мониторот; положбата му се зачувува. "
    L"Распоредувањето во мрежа не го поместува овој виџет. Esc го крие часовникот и го отстранува "
    L"затемнувањето и при отворени поставки.\r\n\r\nПокажувачот на глувчето се крие по кратка неактивност над "
    L"часовникот или затемнетите монитори и се појавува при движење. Над малиот преглед останува видлив.",
    L"\r\n\r\nСат на монитору\r\nДигитални сат може попунити један или више монитора и затамнити остале"
    L". Величина фонта задаје се као проценат висине монитора; подешавају се "
    L"и фонт, умекшавање, боје и унутрашњи размак. UTC може бити у засебном реду. Подразумеван је бели текст "
    L"на црној позадини. Док су Подешавања отворена, сат је мали покретни преглед са односом страница "
    L"монитора; његов положај се чува. Распореди у мрежу не премешта ту врсту виџета. Esc скрива сат и уклања "
    L"затамњење и када су Подешавања отворена.\r\n\r\nПоказивач миша скрива се после кратке неактивности изнад"
    L" сата на монитору и затамњених монитора, а појављује при померању миша. Изнад малог прегледа остаје "
    L"видљив.",
    L"\r\n\r\nГОДИННИК НА МОНІТОРІ\r\nЦифровий годинник може займати один або кілька моніторів і за потреби "
    L"затемнювати решту. Розмір шрифту задається у відсотках висоти "
    L"монітора; також можна налаштувати шрифт, згладжування, кольори та внутрішні відступи. У режимі UTC напис "
    L"UTC можна показувати окремим рядком. Типовий вигляд — білий текст на чорному тлі. Поки відкрито "
    L"налаштування, годинник показується як невелике рухоме вікно попереднього перегляду зі збереженням "
    L"пропорцій монітора; його положення зберігається. Упорядкування за сіткою не переміщує цей тип віджета. "
    L"Esc приховує годинник і прибирає затемнення навіть із відкритим вікном налаштувань.\r\n\r\nВказівник миші"
    L" приховується після короткої бездіяльності над годинником на моніторі та затемненими моніторами й "
    L"з’являється знову під час руху миші. Над малим вікном попереднього перегляду він залишається видимим.",
    L"\r\n\r\nЧАСЫ НА МОНИТОРЕ\r\nЦифровые часы могут занимать один или несколько мониторов и при необходимости"
    L" затемнять остальные. Размер шрифта задаётся в процентах высоты "
    L"монитора; также можно настроить шрифт, сглаживание, цвета и внутренние отступы. В режиме UTC надпись UTC "
    L"можно показывать отдельной строкой. Вид по умолчанию — белый текст на чёрном фоне. Пока открыты "
    L"настройки, часы показываются в небольшом перемещаемом окне предварительного просмотра с сохранением "
    L"пропорций монитора; его положение сохраняется. Упорядочение по сетке не перемещает этот тип виджета. Esc "
    L"скрывает часы и убирает затемнение даже при открытом окне настроек.\r\n\r\nУказатель мыши скрывается "
    L"после короткого бездействия над часами на мониторе и затемнёнными мониторами и появляется снова при "
    L"движении мыши. Над небольшим окном предварительного просмотра он остаётся видимым."
};

const wchar_t* ABOUT_TEXT[LANG_COUNT] = {
    L"Hodiny a kalendáře\r\n\r\nNativní Win32 aplikace pro až 32 samostatně nastavených plovoucích hodin a "
    L"kalendářů.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for up to 32 independently configured floating "
    L"clocks and calendars.",
    L"Uhren und Kalender\r\n\r\nNative Win32-Anwendung für bis zu 32 unabhängig konfigurierte schwebende Uhren"
    L" und Kalender.",
    L"Horloges et calendriers\r\n\r\nApplication Win32 native pour plusieurs horloges et calendriers flottants"
    L" configurés séparément.",
    L"Relojes y calendarios\r\n\r\nAplicación Win32 nativa para varios relojes y calendarios flotantes "
    L"configurados por separado.",
    L"Orologi e calendari\r\n\r\nApplicazione Win32 nativa per più orologi e calendari mobili configurati "
    L"separatamente.",
    L"Zegary i kalendarze\r\n\r\nNatywna aplikacja Win32 obsługująca wiele niezależnie skonfigurowanych "
    L"zegarów i kalendarzy.",
    L"Hodiny a kalendáre\r\n\r\nNatívna aplikácia Win32 pre najviac 32 samostatne nastavených plávajúcich "
    L"hodín a kalendárov.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for up to 32 independently configured floating "
    L"clocks and calendars.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for up to 32 independently configured floating "
    L"clocks and calendars.",
    L"Relógios e calendários\r\n\r\nAplicação Win32 nativa para até 32 relógios e calendários flutuantes "
    L"configurados independentemente.",
    L"Klokker og kalendere\r\n\r\nEt Win32-program for opptil 32 flytende klokker og kalendere med separate "
    L"innstillinger.",
    L"Klockor och kalendrar\r\n\r\nEtt Win32-program för upp till 32 flytande klockor och kalendrar med "
    L"separata inställningar.",
    L"Kellot ja kalenterit\r\n\r\nNatiivi Win32-sovellus enintään 32 erikseen määritettävälle kelluvalle "
    L"kellolle ja kalenterille.",
    L"Ure og kalendere\r\n\r\nEt Win32-program til op til 32 flydende ure og kalendere med separate "
    L"indstillinger.",
    L"Klukkur og dagatöl\r\n\r\nWin32-forrit fyrir allt að 32 fljótandi klukkur og dagatöl með sjálfstæðum "
    L"stillingum.",
    L"Saatler ve takvimler\r\n\r\nBağımsız olarak yapılandırılan en fazla 32 kayan saat ve takvim için yerel "
    L"bir Win32 uygulaması.",
    L"Kellad ja kalendrid\r\n\r\nWin32-rakendus kuni 32 eraldi seadistatava hõljuva kella ja kalendri jaoks.",
    L"Cloig agus féilirí\r\n\r\nFeidhmchlár dúchasach Win32 le haghaidh suas le 32 clog agus féilire ar snámh "
    L"ar féidir iad a chumrú go neamhspleách.",
    L"Laikrodžiai ir kalendoriai\r\n\r\nWin32 programa, rodanti iki 32 atskirai nustatomų slankiųjų laikrodžių"
    L" ir kalendorių.",
    L"Pulksteņi un kalendāri\r\n\r\nWin32 programma līdz 32 neatkarīgi iestatāmiem peldošiem pulksteņiem un "
    L"kalendāriem.",
    L"Órák és naptárak\r\n\r\nNatív Win32-alkalmazás legfeljebb 32, egymástól függetlenül beállítható lebegő "
    L"órával és naptárral.",
    L"Arloġġi u kalendarji\r\n\r\nApplikazzjoni nattiva Win32 għal sa 32 arloġġ u kalendarju li jżommu fuq "
    L"id-desktop u jistgħu jiġu kkonfigurati separatament.",
    L"Klokken en kalenders\r\n\r\nEen native Win32-toepassing voor maximaal 32 afzonderlijk instelbare "
    L"zwevende klokken en kalenders.",
    L"Ceasuri și calendare\r\n\r\nAplicație nativă Win32 pentru până la 32 de ceasuri și calendare flotante, "
    L"configurabile independent.",
    L"Ρολόγια και ημερολόγια\r\n\r\nΕγγενής εφαρμογή Win32 για έως 32 ανεξάρτητα ρυθμιζόμενα αιωρούμενα "
    L"ρολόγια και ημερολόγια.",
    L"Satovi i kalendari\r\n\r\nIzvorni Win32 program za do 32 nezavisno podesiva plutajuća sata i kalendara.",
    L"Satovi i kalendari\r\n\r\nIzvorni Win32 program za do 32 neovisno podesiva plutajuća sata i kalendara.",
    L"Ure in koledarji\r\n\r\nIzvorni program Win32 za do 32 neodvisno nastavljenih plavajočih ur in "
    L"koledarjev.",
    L"Satovi i kalendari\r\n\r\nIzvorna Win32 aplikacija za do 32 nezavisno podešena plutajuća sata i "
    L"kalendara.",
    L"Гадзіннікі і календары\r\n\r\nПраграма Win32 для паказу да 32 незалежна наладжаных рухомых гадзіннікаў і"
    L" календароў.",
    L"Часовници и календари\r\n\r\nПриложение Win32 за до 32 независимо настроени плаващи часовника и "
    L"календара.",
    L"Часовници и календари\r\n\r\nПрограма Win32 за до 32 независно поставени лебдечки часовници и календари.",
    L"Сатови и календари\r\n\r\nИзворна Win32 апликација за до 32 независно подешена плутајућа сата и "
    L"календара.",
    L"Годинники та календарі\r\n\r\nПрограма Win32 для показу до 32 незалежно налаштованих рухомих годинників "
    L"і календарів.",
    L"Часы и календари\r\n\r\nПрограмма Win32 для показа до 32 независимо настроенных перемещаемых часов и "
    L"календарей."
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
    L"Sürüm:",
    L"Versioon:",
    L"Leagan:",
    L"Versija:",
    L"Versija:",
    L"Verzió:",
    L"Verżjoni:",
    L"Versie:",
    L"Versiune:",
    L"Έκδοση:",
    L"Verzija:",
    L"Verzija:",
    L"Različica:",
    L"Verzija:",
    L"Версія:",
    L"Версия:",
    L"Верзија:",
    L"Верзија:",
    L"Версія:",
    L"Версия:"
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
    L"Hedef platform:",
    L"Sihtplatvorm:",
    L"Sprioc-ardán:",
    L"Tikslinė platforma:",
    L"Mērķa platforma:",
    L"Célplatform:",
    L"Pjattaforma fil-mira:",
    L"Doelplatform:",
    L"Platformă țintă:",
    L"Πλατφόρμα προορισμού:",
    L"Ciljna platforma:",
    L"Ciljna platforma:",
    L"Ciljna platforma:",
    L"Ciljna platforma:",
    L"Мэтавая платформа:",
    L"Целева платформа:",
    L"Целна платформа:",
    L"Циљна платформа:",
    L"Цільова платформа:",
    L"Целевая платформа:"
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
    L"Web sitesi:",
    L"Veebisait:",
    L"Suíomh gréasáin:",
    L"Svetainė:",
    L"Tīmekļa vietne:",
    L"Webhely:",
    L"Sit web:",
    L"Website:",
    L"Site web:",
    L"Τοποθεσία web:",
    L"Web-mjesto:",
    L"Web-mjesto:",
    L"Spletno mesto:",
    L"Veb-sajt:",
    L"Вэб-сайт:",
    L"Уебсайт:",
    L"Веб-страница:",
    L"Веб-сајт:",
    L"Вебсайт:",
    L"Веб-сайт:"
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
    L"Web sitesini ziyaret et",
    L"Ava veebisait",
    L"Oscail an suíomh gréasáin",
    L"Atidaryti svetainę",
    L"Atvērt tīmekļa vietni",
    L"Webhely megnyitása",
    L"Iftaħ is-sit web",
    L"Website openen",
    L"Deschidere site web",
    L"Άνοιγμα τοποθεσίας web",
    L"Posjeti web-mjesto",
    L"Posjeti web-mjesto",
    L"Obišči spletno mesto",
    L"Otvori veb-sajt",
    L"Адкрыць вэб-сайт",
    L"Отвори уебсайта",
    L"Отвори ја веб-страницата",
    L"Отвори веб-сајт",
    L"Відкрити вебсайт",
    L"Открыть веб-сайт"
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
    L"Varsayılan tarayıcıda &aç",
    L"&Ava vaikebrauseris",
    L"&Oscail sa bhrabhsálaí réamhshocraithe",
    L"&Atidaryti numatytojoje naršyklėje",
    L"&Atvērt noklusējuma pārlūkprogrammā",
    L"&Megnyitás az alapértelmezett böngészőben",
    L"&Iftaħ fil-brawżer default",
    L"&Openen in standaardbrowser",
    L"&Deschidere în browserul implicit",
    L"&Άνοιγμα στο προεπιλεγμένο πρόγραμμα περιήγησης",
    L"&Otvori u podrazumijevanom pregledniku",
    L"&Otvori u zadanom pregledniku",
    L"&Odpri v privzetem brskalniku",
    L"&Otvori u podrazumijevanom pregledaču",
    L"&Адкрыць у прадвызначаным браўзеры",
    L"&Отвори в браузъра по подразбиране",
    L"&Отвори во стандардниот прелистувач",
    L"&Отвори у подразумеваном прегледачу",
    L"&Відкрити в типовому браузері",
    L"&Открыть в браузере по умолчанию"
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
    L"&URL'yi kopyala",
    L"Kopeeri &aadress",
    L"Cóipeáil an &seoladh",
    L"Kopijuoti &adresą",
    L"Kopēt &adresi",
    L"&Cím másolása",
    L"Ikkopja l-&indirizz",
    L"&Adres kopiëren",
    L"Copiere &adresă",
    L"Αντιγραφή &διεύθυνσης",
    L"Kopiraj &adresu",
    L"Kopiraj &adresu",
    L"Kopiraj &naslov",
    L"Kopiraj &adresu",
    L"Капіяваць &адрас",
    L"Копирай &адреса",
    L"Копирај ја &адресата",
    L"Копирај &адресу",
    L"Копіювати &адресу",
    L"Копировать &адрес"
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
    L"&Bilgileri kopyala",
    L"Kopeeri &teave",
    L"Cóipeáil an &fhaisnéis",
    L"Kopijuoti &informaciją",
    L"Kopēt &informāciju",
    L"&Információ másolása",
    L"Ikkopja l-&informazzjoni",
    L"&Informatie kopiëren",
    L"Copiere &informații",
    L"Αντιγραφή &πληροφοριών",
    L"Kopiraj &informacije",
    L"Kopiraj &informacije",
    L"Kopiraj &podatke",
    L"Kopiraj &podatke",
    L"Капіяваць &звесткі",
    L"Копирай &информацията",
    L"Копирај ги &информациите",
    L"Копирај &податке",
    L"Копіювати &відомості",
    L"Копировать &сведения"
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
    L"Uygulama",
    L"Rakendus",
    L"Feidhmchlár",
    L"Programa",
    L"Programma",
    L"Alkalmazás",
    L"Applikazzjoni",
    L"Toepassing",
    L"Aplicație",
    L"Εφαρμογή",
    L"Program",
    L"Program",
    L"Program",
    L"Program",
    L"Праграма",
    L"Програма",
    L"Програма",
    L"Програм",
    L"Програма",
    L"Программа"
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
    L"Çalışma alanı kenarlarına yasla",
    L"Tõmba tööala servade külge",
    L"Léim go himill an limistéir oibre",
    L"Prikabinti prie darbo srities kraštų",
    L"Pievilkt pie darba apgabala malām",
    L"Illesztés a munkaterület széleihez",
    L"Waħħal mat-truf taż-żona tax-xogħol",
    L"Uitlijnen op randen van werkgebied",
    L"Aliniere la marginile zonei de lucru",
    L"Προσκόλληση στα άκρα της περιοχής εργασίας",
    L"Priljubi uz ivice radnog područja",
    L"Priljubi uz rubove radnog područja",
    L"Pripni na robove delovnega območja",
    L"Prilijepi uz ivice radne površine",
    L"Прывязваць да краёў рабочай вобласці",
    L"Прилепвай към краищата на работната област",
    L"Прилепувај кон рабовите на работната површина",
    L"Прилепи уз ивице радне површине",
    L"Прив’язувати до країв робочої області",
    L"Привязывать к краям рабочей области"
};

const wchar_t* WARN_UNSAVED_CHANGES_LABELS[LANG_COUNT] = {
    L"Upozornit na neuložené změny",
    L"Warn about unsaved changes",
    L"Vor ungespeicherten Änderungen warnen",
    L"Avertir en cas de modifications non enregistrées",
    L"Advertir de cambios sin guardar",
    L"Avvisa in caso di modifiche non salvate",
    L"Ostrzegaj o niezapisanych zmianach",
    L"Upozorniť na neuložené zmeny",
    L"Warn about unsaved changes",
    L"Warn about unsaved changes",
    L"Avisar sobre alterações não guardadas",
    L"Advar om ulagrede endringer",
    L"Varna för osparade ändringar",
    L"Varoita tallentamattomista muutoksista",
    L"Advar om ændringer, der ikke er gemt",
    L"Vara við óvistuðum breytingum",
    L"Kaydedilmemiş değişiklikler için uyar",
    L"Hoiata salvestamata muudatuste eest",
    L"Tabhair rabhadh faoi athruithe gan sábháil",
    L"Įspėti apie neįrašytus pakeitimus",
    L"Brīdināt par nesaglabātām izmaiņām",
    L"Figyelmeztetés a nem mentett módosításokra",
    L"Avża dwar bidliet mhux issejvjati",
    L"Waarschuwen voor niet-opgeslagen wijzigingen",
    L"Avertizează despre modificările nesalvate",
    L"Προειδοποίηση για μη αποθηκευμένες αλλαγές",
    L"Upozori na nesačuvane promjene",
    L"Upozori na nespremljene promjene",
    L"Opozori na neshranjene spremembe",
    L"Upozori na nesačuvane izmjene",
    L"Папярэджваць пра незахаваныя змены",
    L"Предупреждавай за незаписани промени",
    L"Предупреди за незачувани промени",
    L"Упозори на несачуване измене",
    L"Попереджати про незбережені зміни",
    L"Предупреждать о несохранённых изменениях"
};

const wchar_t* UNSAVED_SETTINGS_PROMPTS[LANG_COUNT] = {
    L"Chcete před zavřením uložit změny nastavení?\r\n\r\nPokud je neuložíte, všechny neuložené změny budou ztraceny.",
    L"Do you want to save changes to the settings before closing?\r\n\r\nIf you do not save them, all unsaved changes will be lost.",
    L"Möchten Sie die Änderungen an den Einstellungen vor dem Schließen speichern?\r\n\r\nWenn Sie sie nicht speichern, gehen alle ungespeicherten Änderungen verloren.",
    L"Voulez-vous enregistrer les modifications des paramètres avant de fermer ?\r\n\r\nSinon, toutes les modifications non enregistrées seront perdues.",
    L"¿Desea guardar los cambios en la configuración antes de cerrar?\r\n\r\nSi no los guarda, se perderán todos los cambios sin guardar.",
    L"Salvare le modifiche alle impostazioni prima di chiudere?\r\n\r\nSe non vengono salvate, tutte le modifiche non salvate andranno perse.",
    L"Czy zapisać zmiany w ustawieniach przed zamknięciem?\r\n\r\nJeśli ich nie zapiszesz, wszystkie niezapisane zmiany zostaną utracone.",
    L"Chcete pred zatvorením uložiť zmeny nastavení?\r\n\r\nAk ich neuložíte, všetky neuložené zmeny sa stratia.",
    L"Do you want to save changes to the settings before closing?\r\n\r\nIf you do not save them, all unsaved changes will be lost.",
    L"Do you want to save changes to the settings before closing?\r\n\r\nIf you do not save them, all unsaved changes will be lost.",
    L"Pretende guardar as alterações às definições antes de fechar?\r\n\r\nSe não as guardar, todas as alterações não guardadas serão perdidas.",
    L"Vil du lagre endringene i innstillingene før du lukker?\r\n\r\nHvis du ikke lagrer dem, går alle ulagrede endringer tapt.",
    L"Vill du spara ändringarna i inställningarna innan du stänger?\r\n\r\nOm du inte sparar dem går alla osparade ändringar förlorade.",
    L"Haluatko tallentaa asetuksiin tehdyt muutokset ennen sulkemista?\r\n\r\nJos et tallenna niitä, kaikki tallentamattomat muutokset menetetään.",
    L"Vil du gemme ændringerne i indstillingerne, før du lukker?\r\n\r\nHvis du ikke gemmer dem, går alle ændringer, der ikke er gemt, tabt.",
    L"Viltu vista breytingar á stillingum áður en þú lokar?\r\n\r\nEf þú vistar þær ekki glatast allar óvistaðar breytingar.",
    L"Kapatmadan önce ayarlardaki değişiklikleri kaydetmek istiyor musunuz?\r\n\r\nKaydetmezseniz kaydedilmemiş tüm değişiklikler kaybolacak.",
    L"Kas soovite enne sulgemist sätete muudatused salvestada?\r\n\r\nKui te neid ei salvesta, lähevad kõik salvestamata muudatused kaotsi.",
    L"Ar mhaith leat na hathruithe ar na socruithe a shábháil roimh dhúnadh?\r\n\r\nMura sábhálann tú iad, caillfear gach athrú gan sábháil.",
    L"Ar norite prieš uždarydami įrašyti parametrų pakeitimus?\r\n\r\nJei jų neįrašysite, visi neįrašyti pakeitimai bus prarasti.",
    L"Vai pirms aizvēršanas saglabāt iestatījumu izmaiņas?\r\n\r\nJa tās nesaglabāsiet, visas nesaglabātās izmaiņas tiks zaudētas.",
    L"Szeretné menteni a beállítások módosításait bezárás előtt?\r\n\r\nHa nem menti őket, minden nem mentett módosítás elvész.",
    L"Trid tissejvja l-bidliet fis-settings qabel tagħlaq?\r\n\r\nJekk ma tissejvjahomx, jintilfu l-bidliet kollha mhux issejvjati.",
    L"Wilt u de wijzigingen in de instellingen opslaan voordat u sluit?\r\n\r\nAls u ze niet opslaat, gaan alle niet-opgeslagen wijzigingen verloren.",
    L"Doriți să salvați modificările setărilor înainte de închidere?\r\n\r\nDacă nu le salvați, toate modificările nesalvate se vor pierde.",
    L"Θέλετε να αποθηκεύσετε τις αλλαγές στις ρυθμίσεις πριν από το κλείσιμο;\r\n\r\nΑν δεν τις αποθηκεύσετε, όλες οι μη αποθηκευμένες αλλαγές θα χαθούν.",
    L"Želite li sačuvati promjene postavki prije zatvaranja?\r\n\r\nAko ih ne sačuvate, sve nesačuvane promjene bit će izgubljene.",
    L"Želite li spremiti promjene postavki prije zatvaranja?\r\n\r\nAko ih ne spremite, sve nespremljene promjene bit će izgubljene.",
    L"Ali želite pred zapiranjem shraniti spremembe nastavitev?\r\n\r\nČe jih ne shranite, bodo vse neshranjene spremembe izgubljene.",
    L"Želite li sačuvati izmjene podešavanja prije zatvaranja?\r\n\r\nAko ih ne sačuvate, sve nesačuvane izmjene biće izgubljene.",
    L"Захаваць змены налад перад закрыццём?\r\n\r\nКалі іх не захаваць, усе незахаваныя змены будуць страчаны.",
    L"Искате ли да запишете промените в настройките преди затваряне?\r\n\r\nАко не ги запишете, всички незаписани промени ще бъдат загубени.",
    L"Дали сакате да ги зачувате промените на поставките пред затворање?\r\n\r\nАко не ги зачувате, сите незачувани промени ќе бидат изгубени.",
    L"Желите ли да сачувате измене подешавања пре затварања?\r\n\r\nАко их не сачувате, све несачуване измене биће изгубљене.",
    L"Зберегти зміни налаштувань перед закриттям?\r\n\r\nЯкщо їх не зберегти, усі незбережені зміни буде втрачено.",
    L"Сохранить изменения настроек перед закрытием?\r\n\r\nЕсли их не сохранить, все несохранённые изменения будут потеряны."
};

/// Formats an initial additional-clock name; callers preserve stored empty names instead of replacing them.
std::wstring DefaultAdditionalClockName(AppLanguage language, int index) {
    wchar_t text[128] = {};
    swprintf_s(text, ADDITIONAL_CLOCK_NAME_FORMATS[language], index + 1);
    return text;
}

void InitializeLanguageLocales() {
    if (!IsValidLocaleName(LANGUAGE_LOCALES[LANG_SR])) {
        LANGUAGE_LOCALES[LANG_SR] = L"sr-Cyrl-CS";
    }
    if (!IsValidLocaleName(LANGUAGE_LOCALES[LANG_CNR])) {
        LANGUAGE_LOCALES[LANG_CNR] = IsValidLocaleName(L"sr-Latn-RS") ? L"sr-Latn-RS" : L"sr-Latn-CS";
    }
}
