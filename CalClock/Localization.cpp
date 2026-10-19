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
 * Last modified for version 1.6.0.1
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
    L"Zvuk a programy\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Všechny soubory\0*.*\0",
    L"Audio and programs\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"All files\0*.*\0",
    L"Audio und Programme\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Alle Dateien\0*.*\0",
    L"Audio et programmes\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Tous les fichiers\0*.*\0",
    L"Audio y programas\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Todos los archivos\0*.*\0",
    L"Audio e programmi\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Tutti i file\0*.*\0",
    L"Dźwięk i programy\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Wszystkie pliki\0*.*\0",
    L"Zvuk a programy\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Všetky súbory\0*.*\0",
    L"Audio and programs\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"All files\0*.*\0",
    L"Audio and programs\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"All files\0*.*\0",
    L"Áudio e programas\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Todos os ficheiros\0*.*\0",
    L"Lyd og programmer\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Alle filer\0*.*\0",
    L"Ljud och program\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Alla filer\0*.*\0",
    L"Ääni ja ohjelmat\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Kaikki tiedostot\0*.*\0",
    L"Lyd og programmer\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Alle filer\0*.*\0",
    L"Hljóð og forrit\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Allar skrár\0*.*\0",
    L"Ses ve programlar\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Tüm dosyalar\0*.*\0",
    L"Heli ja programmid\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Kõik failid\0*.*\0",
    L"Fuaim agus ríomhchláir\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Gach comhad\0*.*\0",
    L"Garsas ir programos\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Visi failai\0*.*\0",
    L"Skaņa un programmas\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Visi faili\0*.*\0",
    L"Hangfájlok és programok\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Minden fájl\0*.*\0",
    L"Awdjo u programmi\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Il-fajls kollha\0*.*\0",
    L"Geluid en programma’s\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Alle bestanden\0*.*\0",
    L"Sunet și programe\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Toate fișierele\0*.*\0",
    L"Ήχος και προγράμματα\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Όλα τα αρχεία\0*.*\0",
    L"Zvuk i programi\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Sve datoteke\0*.*\0",
    L"Zvuk i programi\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Sve datoteke\0*.*\0",
    L"Zvok in programi\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Vse datoteke\0*.*\0",
    L"Zvuk i programi\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Sve datoteke\0*.*\0",
    L"Гук і праграмы\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Усе файлы\0*.*\0",
    L"Звук и програми\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Всички файлове\0*.*\0",
    L"Звук и програми\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Сите датотеки\0*.*\0",
    L"Звук и програми\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Све датотеке\0*.*\0",
    L"Звук і програми\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Усі файли\0*.*\0",
    L"Звук и программы\0"
    L"*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.flac;*.exe;*.bat;*.cmd\0"
    L"Все файлы\0*.*\0"
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
    {
        L"Monitor",
        L"Model monitoru",
        L"Rozlišení",
        L"Obnovovací frekvence",
        L"Bitová hloubka",
        L"Formát barvy",
        L"Barevný prostor",
        L"Poloha"
    }, {
        L"Display",
        L"Monitor model",
        L"Resolution",
        L"Refresh rate",
        L"Bit depth",
        L"Color format",
        L"Color space",
        L"Position"
    }, {
        L"Monitor",
        L"Monitormodell",
        L"Auflösung",
        L"Bildwiederholfrequenz",
        L"Bittiefe",
        L"Farbformat",
        L"Farbraum",
        L"Position"
    }, {
        L"Moniteur",
        L"Modèle du moniteur",
        L"Résolution",
        L"Fréquence de rafraîchissement",
        L"Profondeur de bits",
        L"Format de couleur",
        L"Espace colorimétrique",
        L"Position"
    }, {
        L"Monitor",
        L"Modelo del monitor",
        L"Resolución",
        L"Frecuencia de actualización",
        L"Profundidad de bits",
        L"Formato de color",
        L"Espacio de color",
        L"Posición"
    }, {
        L"Monitor",
        L"Modello del monitor",
        L"Risoluzione",
        L"Frequenza di aggiornamento",
        L"Profondità di bit",
        L"Formato colore",
        L"Spazio colore",
        L"Posizione"
    }, {
        L"Monitor",
        L"Model monitora",
        L"Rozdzielczość",
        L"Częstotliwość odświeżania",
        L"Głębia bitowa",
        L"Format koloru",
        L"Przestrzeń barw",
        L"Położenie"
    }, {
        L"Monitor",
        L"Model monitora",
        L"Rozlíšenie",
        L"Obnovovacia frekvencia",
        L"Bitová hĺbka",
        L"Formát farby",
        L"Farebný priestor",
        L"Poloha"
    }, {
        L"Display",
        L"Monitor model",
        L"Resolution",
        L"Refresh rate",
        L"Bit depth",
        L"Colour format",
        L"Colour space",
        L"Position"
    }, {
        L"Display",
        L"Monitor model",
        L"Resolution",
        L"Refresh rate",
        L"Bit depth",
        L"Colour format",
        L"Colour space",
        L"Position"
    }, {
        L"Monitor",
        L"Modelo do monitor",
        L"Resolução",
        L"Taxa de atualização",
        L"Profundidade de bits",
        L"Formato de cor",
        L"Espaço de cor",
        L"Posição"
    }, {
        L"Skjerm",
        L"Skjermmodell",
        L"Oppløsning",
        L"Oppdateringsfrekvens",
        L"Bitdybde",
        L"Fargeformat",
        L"Fargerom",
        L"Posisjon"
    }, {
        L"Bildskärm",
        L"Skärmmodell",
        L"Upplösning",
        L"Uppdateringsfrekvens",
        L"Bitdjup",
        L"Färgformat",
        L"Färgrymd",
        L"Position"
    }, {
        L"Näyttö",
        L"Näytön malli",
        L"Tarkkuus",
        L"Virkistystaajuus",
        L"Bittisyvyys",
        L"Värimuoto",
        L"Väriavaruus",
        L"Sijainti"
    }, {
        L"Skærm",
        L"Skærmmodel",
        L"Opløsning",
        L"Opdateringsfrekvens",
        L"Bitdybde",
        L"Farveformat",
        L"Farverum",
        L"Placering"
    }, {
        L"Skjár",
        L"Gerð skjás",
        L"Upplausn",
        L"Endurnýjunartíðni",
        L"Bitadýpt",
        L"Litasnið",
        L"Litarými",
        L"Staðsetning"
    }, {
        L"Monitör",
        L"Monitör modeli",
        L"Çözünürlük",
        L"Yenileme hızı",
        L"Bit derinliği",
        L"Renk biçimi",
        L"Renk alanı",
        L"Konum"
    }, {
        L"Kuvar",
        L"Kuvari mudel",
        L"Eraldusvõime",
        L"Värskendussagedus",
        L"Bitisügavus",
        L"Värvivorming",
        L"Värviruum",
        L"Asukoht"
    }, {
        L"Monatóir",
        L"Samhail an mhonatóra",
        L"Taifeach",
        L"Ráta athnuachana",
        L"Doimhneacht ghiotán",
        L"Formáid datha",
        L"Spás datha",
        L"Suíomh"
    }, {
        L"Monitorius",
        L"Monitoriaus modelis",
        L"Skiriamoji geba",
        L"Atnaujinimo dažnis",
        L"Bitų gylis",
        L"Spalvų formatas",
        L"Spalvų erdvė",
        L"Padėtis"
    }, {
        L"Monitors",
        L"Monitora modelis",
        L"Izšķirtspēja",
        L"Atsvaidzināšanas frekvence",
        L"Bitu dziļums",
        L"Krāsu formāts",
        L"Krāstelpa",
        L"Pozīcija"
    }, {
        L"Monitor",
        L"Monitor típusa",
        L"Felbontás",
        L"Frissítési gyakoriság",
        L"Bitmélység",
        L"Színformátum",
        L"Színtér",
        L"Pozíció"
    }, {
        L"Moniter",
        L"Mudell tal-moniter",
        L"Riżoluzzjoni",
        L"Rata ta’ aġġornament",
        L"Fond tal-bits",
        L"Format tal-kulur",
        L"Spazju tal-kulur",
        L"Pożizzjoni"
    }, {
        L"Beeldscherm",
        L"Beeldschermmodel",
        L"Resolutie",
        L"Vernieuwingsfrequentie",
        L"Bitdiepte",
        L"Kleurindeling",
        L"Kleurruimte",
        L"Positie"
    }, {
        L"Monitor",
        L"Model monitor",
        L"Rezoluție",
        L"Rată de reîmprospătare",
        L"Adâncime de biți",
        L"Format de culoare",
        L"Spațiu de culoare",
        L"Poziție"
    }, {
        L"Οθόνη",
        L"Μοντέλο οθόνης",
        L"Ανάλυση",
        L"Ρυθμός ανανέωσης",
        L"Βάθος bit",
        L"Μορφή χρώματος",
        L"Χρωματικός χώρος",
        L"Θέση"
    }, {
        L"Monitor",
        L"Model monitora",
        L"Rezolucija",
        L"Frekvencija osvježavanja",
        L"Dubina bita",
        L"Format boje",
        L"Prostor boja",
        L"Položaj"
    }, {
        L"Zaslon",
        L"Model zaslona",
        L"Razlučivost",
        L"Frekvencija osvježavanja",
        L"Dubina bita",
        L"Oblik boje",
        L"Prostor boja",
        L"Položaj"
    }, {
        L"Zaslon",
        L"Model zaslona",
        L"Ločljivost",
        L"Hitrost osveževanja",
        L"Bitna globina",
        L"Oblika barv",
        L"Barvni prostor",
        L"Položaj"
    }, {
        L"Monitor",
        L"Model monitora",
        L"Rezolucija",
        L"Frekvencija osvježavanja",
        L"Dubina bita",
        L"Format boje",
        L"Prostor boja",
        L"Položaj"
    }, {
        L"Манітор",
        L"Мадэль манітора",
        L"Раздзяляльнасць",
        L"Частата абнаўлення",
        L"Бітавая глыбіня",
        L"Фармат колеру",
        L"Каляровая прастора",
        L"Пазіцыя"
    }, {
        L"Монитор",
        L"Модел на монитора",
        L"Разделителна способност",
        L"Честота на опресняване",
        L"Битова дълбочина",
        L"Формат на цветовете",
        L"Цветово пространство",
        L"Позиция"
    }, {
        L"Монитор",
        L"Модел на мониторот",
        L"Резолуција",
        L"Стапка на освежување",
        L"Битна длабочина",
        L"Формат на боја",
        L"Простор на бои",
        L"Положба"
    }, {
        L"Монитор",
        L"Модел монитора",
        L"Резолуција",
        L"Учестаност освежавања",
        L"Дубина бита",
        L"Формат боје",
        L"Простор боја",
        L"Положај"
    }, {
        L"Монітор",
        L"Модель монітора",
        L"Роздільна здатність",
        L"Частота оновлення",
        L"Бітова глибина",
        L"Формат кольору",
        L"Колірний простір",
        L"Розташування"
    }, {
        L"Монитор",
        L"Модель монитора",
        L"Разрешение",
        L"Частота обновления",
        L"Глубина цвета",
        L"Формат цвета",
        L"Цветовое пространство",
        L"Расположение"
    }
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
    { L"Ano", L"Ne, ponechat místo", L"Ne, bez místa" },
    { L"Yes", L"No, keep space", L"No, without space" },
    { L"Ja", L"Nein, Platz freihalten", L"Nein, ohne Platz" },
    { L"Oui", L"Non, garder l’espace", L"Non, sans espace" },
    { L"Sí", L"No, reservar espacio", L"No, sin espacio" },
    { L"Sì", L"No, riserva spazio", L"No, senza spazio" },
    { L"Tak", L"Nie, zachowaj miejsce", L"Nie, bez miejsca" },
    { L"Áno", L"Nie, ponechať miesto", L"Nie, bez miesta" },
    { L"Yes", L"No, keep space", L"No, without space" },
    { L"Yes", L"No, keep space", L"No, without space" },
    { L"Sim", L"Não, reservar espaço", L"Não, sem espaço" },
    { L"Ja", L"Nei, behold plass", L"Nei, uten plass" },
    { L"Ja", L"Nej, behåll utrymme", L"Nej, utan utrymme" },
    { L"Kyllä", L"Ei, varaa tila", L"Ei, ilman tilaa" },
    { L"Ja", L"Nej, bevar plads", L"Nej, uden plads" },
    { L"Já", L"Nei, halda plássi", L"Nei, án pláss" },
    { L"Evet", L"Hayır, yer ayır", L"Hayır, boşluksuz" },
    { L"Jah", L"Ei, säilita ruum", L"Ei, ilma ruumita" },
    { L"Tá", L"Níl, coinnigh an spás", L"Níl, gan spás" },
    { L"Taip", L"Ne, palikti vietą", L"Ne, be vietos" },
    { L"Jā", L"Nē, saglabāt vietu", L"Nē, bez vietas" },
    { L"Igen", L"Nem, hely megtartása", L"Nem, hely nélkül" },
    { L"Iva", L"Le, żomm l-ispazju", L"Le, bla spazju" },
    { L"Ja", L"Nee, ruimte behouden", L"Nee, zonder ruimte" },
    { L"Da", L"Nu, păstrează spațiul", L"Nu, fără spațiu" },
    { L"Ναι", L"Όχι, διατήρηση χώρου", L"Όχι, χωρίς χώρο" },
    { L"Da", L"Ne, zadrži razmak", L"Ne, bez razmaka" },
    { L"Da", L"Ne, zadrži razmak", L"Ne, bez razmaka" },
    { L"Da", L"Ne, ohrani prostor", L"Ne, brez prostora" },
    { L"Da", L"Ne, zadrži razmak", L"Ne, bez razmaka" },
    { L"Так", L"Не, пакідаць месца", L"Не, без месца" },
    { L"Да", L"Не, запази мястото", L"Не, без място" },
    { L"Да", L"Не, зачувај место", L"Не, без место" },
    { L"Да", L"Не, задржи размак", L"Не, без размака" },
    { L"Так", L"Ні, залишати місце", L"Ні, без місця" },
    { L"Да", L"Нет, оставить место", L"Нет, без места" }
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
    L"Greenwich Time Signal (GTS): pět krátkých tónů zazní v posledních pěti sekundách a dlouhý "
    L"tón přesně na zvolené časové hranici. Souběžná znamení více widgetů se přehrají pouze "
    L"jednou.",
    L"Greenwich Time Signal (GTS): five short pips sound during the final five seconds and a long "
    L"pip exactly at the selected time boundary. Coincident signals from multiple widgets play "
    L"only once.",
    L"Greenwich Time Signal (GTS): fünf kurze Töne erklingen in den letzten fünf Sekunden und ein "
    L"langer Ton genau an der gewählten Zeitgrenze. Gleichzeitige Signale mehrerer Widgets werden "
    L"nur einmal wiedergegeben.",
    L"Greenwich Time Signal (GTS): cinq bips courts retentissent pendant les cinq dernières "
    L"secondes et un bip long exactement à la limite choisie. Les signaux simultanés de plusieurs "
    L"widgets ne sont joués qu’une fois.",
    L"Greenwich Time Signal (GTS): cinco pitidos cortos suenan durante los últimos cinco segundos "
    L"y uno largo exactamente en el límite elegido. Las señales simultáneas de varios widgets se "
    L"reproducen una sola vez.",
    L"Greenwich Time Signal (GTS): cinque segnali brevi suonano negli ultimi cinque secondi e uno "
    L"lungo esattamente al limite scelto. I segnali simultanei di più widget vengono riprodotti "
    L"una sola volta.",
    L"Greenwich Time Signal (GTS): pięć krótkich sygnałów rozlega się w ostatnich pięciu "
    L"sekundach, a długi dokładnie na wybranej granicy czasu. Zbieżne sygnały wielu widżetów są "
    L"odtwarzane tylko raz.",
    L"Greenwich Time Signal (GTS): päť krátkych tónov zaznie v posledných piatich sekundách a "
    L"dlhý tón presne na zvolenej časovej hranici. Súbežné znamenia viacerých widgetov sa "
    L"prehrajú iba raz.",
    L"Greenwich Time Signal (GTS): five short pips sound during the final five seconds and a long "
    L"pip exactly at the selected time boundary. Coincident signals from multiple widgets play "
    L"only once.",
    L"Greenwich Time Signal (GTS): five short pips sound during the final five seconds and a long "
    L"pip exactly at the selected time boundary. Coincident signals from multiple widgets play "
    L"only once.",
    L"Greenwich Time Signal (GTS): cinco sinais curtos soam nos últimos cinco segundos e um sinal "
    L"longo exatamente no limite escolhido. Sinais coincidentes de vários widgets são "
    L"reproduzidos apenas uma vez.",
    L"Greenwich Time Signal (GTS): fem korte pip høres i de siste fem sekundene og et langt pip "
    L"nøyaktig på den valgte tidsgrensen. Samtidige signaler fra flere widgeter spilles bare én "
    L"gang.",
    L"Greenwich Time Signal (GTS): fem korta pip hörs under de sista fem sekunderna och ett långt "
    L"pip exakt vid den valda tidsgränsen. Samtidiga signaler från flera widgetar spelas bara en "
    L"gång.",
    L"Greenwich Time Signal (GTS): viisi lyhyttä äänimerkkiä kuuluu viimeisten viiden sekunnin "
    L"aikana ja pitkä merkki täsmälleen valitulla aikarajalla. Samanaikaiset merkit toistetaan "
    L"vain kerran.",
    L"Greenwich Time Signal (GTS): fem korte bip lyder i de sidste fem sekunder og et langt bip "
    L"præcis ved den valgte tidsgrænse. Samtidige signaler fra flere widgets afspilles kun én "
    L"gang.",
    L"Greenwich Time Signal (GTS): fimm stutt píp hljóma síðustu fimm sekúndurnar og langt píp "
    L"nákvæmlega á völdum tímamörkum. Samtímamerki frá mörgum græjum eru aðeins spiluð einu sinni.",
    L"Greenwich Time Signal (GTS): son beş saniyede beş kısa ses ve seçili zaman sınırında tam "
    L"olarak bir uzun ses çalar. Birden çok aracın çakışan sinyalleri yalnızca bir kez çalınır.",
    L"Greenwichi ajasignaal (GTS): viimasel viiel sekundil kõlab viis lühikest tooni ja valitud "
    L"ajahetkel pikk toon. Mitme vidina samaaegsed signaalid esitatakse vaid üks kord.",
    L"Comhartha Ama Greenwich (GTS): cúig bhíp ghearra sna cúig shoicind dheireanacha agus bíp "
    L"fhada ag an am roghnaithe go beacht. Seinntear comharthaí comhuaineacha ó roinnt giuirléidí "
    L"uair amháin.",
    L"Grinvičo laiko signalas (GTS): penki trumpi tonai paskutines penkias sekundes ir ilgas "
    L"tonas tiksliai pasirinktu laiku. Vienalaikiai kelių valdiklių signalai leidžiami tik vieną "
    L"kartą.",
    L"Griničas laika signāls (GTS): pieci īsi toņi pēdējās piecās sekundēs un garš tonis tieši "
    L"izvēlētajā laika robežā. Vairāku logrīku vienlaicīgie signāli tiek atskaņoti tikai vienreiz.",
    L"Greenwichi időjelzés (GTS): az utolsó öt másodpercben öt rövid hang, a kiválasztott "
    L"időhatáron pedig egy hosszú hang szól. Több minialkalmazás egyidejű jelzése csak egyszer "
    L"hangzik el.",
    L"Is-Sinjal tal-Ħin ta’ Greenwich (GTS): ħames toni qosra fl-aħħar ħames sekondi u ton twil "
    L"eżatt fil-ħin magħżul. Sinjali simultanji minn diversi widgets jindaqqu darba biss.",
    L"Greenwich Time Signal (GTS): vijf korte tonen in de laatste vijf seconden en een lange toon "
    L"precies op het gekozen tijdstip. Gelijktijdige signalen van meerdere widgets worden maar "
    L"eenmaal afgespeeld.",
    L"Semnalul orar Greenwich (GTS): cinci tonuri scurte în ultimele cinci secunde și un ton lung "
    L"exact la momentul ales. Semnalele simultane ale mai multor widgeturi sunt redate o singură "
    L"dată.",
    L"Σήμα ώρας Γκρίνουιτς (GTS): πέντε σύντομοι τόνοι στα τελευταία πέντε δευτερόλεπτα και ένας "
    L"παρατεταμένος τόνος ακριβώς στην επιλεγμένη χρονική στιγμή. Ταυτόχρονα σήματα πολλών "
    L"γραφικών στοιχείων ακούγονται μόνο μία φορά.",
    L"Greenwich Time Signal (GTS): pet kratkih tonova tokom posljednjih pet sekundi i jedan dugi "
    L"ton tačno na odabranoj vremenskoj granici. Istovremeni signali više vidžeta reproduciraju "
    L"se samo jednom.",
    L"Greenwich Time Signal (GTS): pet kratkih tonova tijekom posljednjih pet sekundi i jedan "
    L"dugi ton točno na odabranoj vremenskoj granici. Istodobni signali više widgeta "
    L"reproduciraju se samo jednom.",
    L"Greenwich Time Signal (GTS): pet kratkih piskov v zadnjih petih sekundah in dolg pisk "
    L"natanko na izbrani časovni meji. Sočasni signali več gradnikov se predvajajo le enkrat.",
    L"Grinički vremenski signal (GTS): pet kratkih tonova tokom posljednjih pet sekundi i dugi "
    L"ton tačno na izabranoj vremenskoj granici. Istovremeni signali više vidžeta puštaju se samo "
    L"jednom.",
    L"Грынвіцкі сігнал часу (GTS): пяць кароткіх сігналаў у апошнія пяць секунд і доўгі сігнал "
    L"дакладна на выбранай часовай мяжы. Адначасовыя сігналы некалькіх віджэтаў гучаць толькі "
    L"адзін раз.",
    L"Гринуички сигнал за време (GTS): пет кратки тона през последните пет секунди и дълъг тон "
    L"точно на избраната времева граница. Едновременните сигнали на няколко модула се "
    L"възпроизвеждат само веднъж.",
    L"Гринички временски сигнал (GTS): пет кратки тона во последните пет секунди и долг тон точно "
    L"на избраната временска граница. Истовремените сигнали од повеќе виџети се пуштаат само "
    L"еднаш.",
    L"Гринички временски сигнал (GTS): пет кратких тонова током последњих пет секунди и дуги тон "
    L"тачно на изабраној временској граници. Истовремени сигнали више виџета пуштају се само "
    L"једном.",
    L"Гринвіцький сигнал часу (GTS): п’ять коротких сигналів протягом останніх п’яти секунд і "
    L"довгий сигнал точно на вибраній часовій межі. Одночасні сигнали кількох віджетів "
    L"відтворюються лише один раз.",
    L"Гринвичский сигнал времени (GTS): пять коротких сигналов в течение последних пяти секунд и "
    L"длинный сигнал точно на выбранной временной границе. Одновременные сигналы нескольких "
    L"виджетов воспроизводятся только один раз."
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
    L"Les serveurs NTP sont indisponibles ; l’horloge continue depuis la dernière synchronisation "
    L":",
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
    L"OVLÁDÁNÍ\r\nLevým tlačítkem a tažením přesunete hodiny nebo panel. Samostatný kalendář se "
    L"přesouvá za volnou plochu. Pravým tlačítkem na widgetu nebo na ikoně v oznamovací oblasti "
    L"otevřete nabídku. Levé kliknutí na ikonu skryje právě viditelné widgety; jsou-li všechny "
    L"skryté, obnoví pouze naposledy skryté widgety.\r\n\r\nWIDGETY A NASTAVENÍ\r\nV Nastavení "
    L"lze přidat, odebrat a duplikovat ručičkové hodiny, digitální hodiny, kalendáře a panely s "
    L"kalendářem a hodinami i hodiny na monitoru. Každý widget má vlastní viditelnost, režim vždy "
    L"navrchu, jazyk, časové pásmo a offset. Offset zadávejte jako [-]HH:mm:ss.ff. Ručičkové "
    L"hodiny a hodiny v panelu mají volitelnou velikost. U digitálních hodin lze nastavit "
    L"sekundy, úvodní nulu, písmo, barvy, neprůhlednost a průhledné pozadí. Kalendář podporuje "
    L"čísla týdnů, neděli jako první den a používá zvolený jazyk widgetu.\r\n\r\nBUDÍK\r\nBudík "
    L"lze nastavit pro hodiny a panel. Zvukový soubor aplikace přehrává sama jednou nebo stále "
    L"dokola podle volby. Ostatní soubor nebo příkaz předá systému Windows. Kliknutím na budící "
    L"ciferník či displej, příkazem Zastavit budík nebo klávesou Esc zastavíte blikání i zvuk "
    L"přehrávaný aplikací.\r\n\r\nZKRATKY A UKLÁDÁNÍ\r\nDvojklik na ciferník nebo digitální "
    L"displej přepne sekundy, F1 otevře nápovědu, B otevře Nastavení a Esc skryje widget, pokud "
    L"právě nezastavuje budík. Polohy widgetů se ukládají po přesunutí, polohy formulářů při "
    L"zavření a nastavení do zvoleného úložiště. Další spuštění programu aktivuje již běžící "
    L"instanci a zachová widgety u nejbližšího dostupného okraje pracovní plochy.",
    L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a standalone calendar by "
    L"its free area. Right-click a widget or notification icon for its menu. Left-click the "
    L"notification icon to hide the currently visible widgets; when all are hidden, it restores "
    L"only the widgets hidden most recently.\r\n\r\nWIDGETS AND SETTINGS\r\nSettings can add, "
    L"remove and duplicate analog clocks, digital clocks, calendars, calendar-and-clock panels "
    L"and monitor clocks. Each widget has its own visibility, always-on-top state, language, time "
    L"zone and offset. Enter offsets as [-]HH:mm:ss.ff. Analog clocks and panel clocks have "
    L"selectable sizes. Digital clocks support seconds, a leading zero, font, colors, opacity and "
    L"a transparent background. Calendars support week numbers and Sunday as the first day and "
    L"use the widget language.\r\n\r\nALARM\r\nClocks and panels can have an alarm. The "
    L"application plays an audio file itself, once or continuously according to the loop option. "
    L"Other files or commands are passed to Windows. Click the alarming clock face or display, "
    L"choose Stop alarm, or press Esc to stop both the alarm indication and audio played by the "
    L"application.\r\n\r\nSHORTCUTS AND SAVING\r\nDouble-click a clock face or digital display to "
    L"toggle seconds, press F1 for Help, B for Settings, and Esc to hide a widget when no alarm "
    L"is being stopped. Widget positions are saved after dragging, dialog positions when closed, "
    L"and all settings in the selected storage. Starting the program again activates the running "
    L"instance and keeps widgets at the nearest available point in the work area.",
    L"BEDIENUNG\r\nZiehen Sie eine Uhr oder ein Panel mit der linken Maustaste. Einen einzelnen "
    L"Kalender ziehen Sie an seiner freien Fläche. Rechtsklick auf Widget oder Infobereichsymbol "
    L"öffnet das Menü. Linksklick auf das Symbol verbirgt die gerade sichtbaren Widgets; sind "
    L"alle verborgen, werden nur die zuletzt verborgenen Widgets "
    L"wiederhergestellt.\r\n\r\nWIDGETS UND EINSTELLUNGEN\r\nSie können Analoguhren, "
    L"Digitaluhren, Kalender, Kalender-Uhr-Panels und Monitoruhren hinzufügen, entfernen oder "
    L"duplizieren. Jedes Widget besitzt eigene Sichtbarkeit, Vordergrundlage, Sprache, Zeitzone "
    L"und einen Versatz im Format [-]HH:mm:ss.ff. Analoguhren haben wählbare Größen. Digitaluhren "
    L"bieten Sekunden, führende Null, Schrift, Farben, Deckkraft und transparenten Hintergrund. "
    L"Kalender bieten Wochennummern, Sonntag als ersten Tag und verwenden die "
    L"Widget-Sprache.\r\n\r\nWECKER\r\nEine Audiodatei wird intern einmal oder in Schleife "
    L"abgespielt; andere Dateien oder Befehle werden an Windows übergeben. Ein Klick auf das "
    L"alarmierende Zifferblatt bzw. Display, Wecker stoppen oder Esc beendet Anzeige und intern "
    L"abgespielten Ton.\r\n\r\nTASTEN UND SPEICHERN\r\nDoppelklick auf Zifferblatt oder "
    L"Digitalanzeige schaltet Sekunden um, F1 öffnet Hilfe, B die Einstellungen. Positionen und "
    L"sämtliche Einstellungen werden im gewählten Speicher gespeichert. Ein erneuter "
    L"Programmstart aktiviert die laufende Instanz.",
    L"COMMANDES\r\nFaites glisser une horloge ou un panneau avec le bouton gauche. Déplacez un "
    L"calendrier autonome par sa zone libre. Un clic droit sur un widget ou l’icône de "
    L"notification ouvre le menu. Un clic gauche sur l’icône masque les widgets visibles ; s’ils "
    L"sont tous masqués, il rétablit uniquement les widgets masqués le plus "
    L"récemment.\r\n\r\nWIDGETS ET PARAMÈTRES\r\nVous pouvez ajouter, supprimer et dupliquer des "
    L"horloges analogiques, numériques, des calendriers, des panneaux combinés et des horloges "
    L"sur moniteur. Chaque widget possède sa visibilité, son maintien au premier plan, sa langue, "
    L"son fuseau et son décalage au format [-]HH:mm:ss.ff. Les horloges analogiques ont des "
    L"tailles au choix. Les horloges numériques proposent secondes, zéro initial, police, "
    L"couleurs, opacité et fond transparent. Le calendrier propose numéros de semaine, dimanche "
    L"en premier et la langue du widget.\r\n\r\nALARME\r\nL’application lit elle-même un fichier "
    L"audio une fois ou en boucle ; les autres fichiers ou commandes sont confiés à Windows. "
    L"Cliquez sur le cadran ou l’affichage en alarme, choisissez Arrêter l’alarme ou appuyez sur "
    L"Échap pour arrêter l’indication et le son interne.\r\n\r\nRACCOURCIS ET "
    L"ENREGISTREMENT\r\nUn double-clic sur le cadran ou l’affichage numérique bascule les "
    L"secondes, F1 ouvre l’aide et B les paramètres. Les positions et tous les réglages sont "
    L"enregistrés dans le stockage sélectionné. Un nouveau lancement active l’instance existante.",
    L"CONTROLES\r\nArrastre un reloj o panel con el botón izquierdo. El calendario independiente "
    L"se arrastra por su zona libre. El botón derecho sobre un widget o el icono de notificación "
    L"abre el menú. Un clic izquierdo sobre el icono oculta los widgets visibles; si todos están "
    L"ocultos, restaura solo los ocultados más recientemente.\r\n\r\nWIDGETS Y "
    L"CONFIGURACIÓN\r\nPuede añadir, quitar y duplicar relojes analógicos, digitales, "
    L"calendarios, paneles combinados y relojes de monitor. Cada widget tiene visibilidad, primer "
    L"plano, idioma, zona horaria y desfase propios; use [-]HH:mm:ss.ff. Los relojes analógicos "
    L"tienen tamaños seleccionables. Los digitales permiten segundos, cero inicial, fuente, "
    L"colores, opacidad y fondo transparente. El calendario permite números de semana, domingo "
    L"primero y usa el idioma del widget.\r\n\r\nALARMA\r\nLa aplicación reproduce internamente "
    L"un archivo de audio una vez o en bucle; los demás archivos o comandos se entregan a "
    L"Windows. Haga clic en la esfera o pantalla con alarma, elija Detener alarma o pulse Esc "
    L"para detener la indicación y el audio interno.\r\n\r\nATAJOS Y GUARDADO\r\nEl doble clic en "
    L"la esfera o la pantalla digital cambia los segundos, F1 abre la ayuda y B la configuración. "
    L"Las posiciones y todos los ajustes se guardan en el almacenamiento seleccionado. Otra "
    L"ejecución activa la instancia existente.",
    L"COMANDI\r\nTrascinare un orologio o pannello con il pulsante sinistro. Il calendario "
    L"autonomo si trascina dall’area libera. Il pulsante destro su widget o icona di notifica "
    L"apre il menu. Il clic sinistro sull’icona nasconde i widget visibili; se sono tutti "
    L"nascosti, ripristina soltanto quelli nascosti più di recente.\r\n\r\nWIDGET E "
    L"IMPOSTAZIONI\r\nÈ possibile aggiungere, rimuovere e duplicare orologi analogici, digitali, "
    L"calendari, pannelli combinati e orologi su monitor. Ogni widget ha visibilità, primo piano, "
    L"lingua, fuso orario e offset propri; usare [-]HH:mm:ss.ff. Gli orologi analogici hanno "
    L"dimensioni selezionabili. Quelli digitali offrono secondi, zero iniziale, carattere, "
    L"colori, opacità e sfondo trasparente. Il calendario offre numeri di settimana, domenica per "
    L"prima e usa la lingua del widget.\r\n\r\nSVEGLIA\r\nL’applicazione riproduce internamente "
    L"un file audio una volta o in ciclo; gli altri file o comandi vengono affidati a Windows. "
    L"Fare clic sul quadrante o display in allarme, scegliere Ferma sveglia o premere Esc per "
    L"fermare indicazione e audio interno.\r\n\r\nSCORCIATOIE E SALVATAGGIO\r\nIl doppio clic sul "
    L"quadrante o sul display digitale commuta i secondi, F1 apre la guida e B le impostazioni. "
    L"Posizioni e impostazioni vengono salvate nell’archivio selezionato. Un nuovo avvio attiva "
    L"l’istanza esistente.",
    L"STEROWANIE\r\nPrzeciągnij zegar lub panel lewym przyciskiem. Samodzielny kalendarz "
    L"przeciąga się za wolne miejsce. Prawy przycisk na widżecie lub ikonie obszaru powiadomień "
    L"otwiera menu. Lewy przycisk na ikonie ukrywa widoczne widżety; gdy wszystkie są ukryte, "
    L"przywraca tylko ostatnio ukryte widżety.\r\n\r\nWIDŻETY I USTAWIENIA\r\nMożna dodawać, "
    L"usuwać i duplikować zegary analogowe i cyfrowe, kalendarze, panele z kalendarzem i zegarem "
    L"oraz zegary na monitorze. Każdy widżet ma własną widoczność, tryb na wierzchu, język, "
    L"strefę czasową i przesunięcie w formacie [-]HH:mm:ss.ff. Zegary analogowe mają różne "
    L"rozmiary. Cyfrowe oferują sekundy, zero wiodące, czcionkę, kolory, krycie i przezroczyste "
    L"tło. Kalendarz oferuje numery tygodni, niedzielę jako pierwszy dzień i język "
    L"widżetu.\r\n\r\nALARM\r\nAplikacja sama odtwarza plik audio raz lub w pętli; inne pliki i "
    L"polecenia przekazuje systemowi Windows. Kliknięcie alarmującej tarczy lub wyświetlacza, "
    L"polecenie Zatrzymaj alarm albo Esc zatrzymuje wskazanie i dźwięk wewnętrzny.\r\n\r\nSKRÓTY "
    L"I ZAPIS\r\nDwuklik na tarczy lub wyświetlaczu cyfrowym przełącza sekundy, F1 otwiera pomoc, "
    L"a B ustawienia. Pozycje i wszystkie ustawienia są zapisywane w wybranym magazynie. Ponowne "
    L"uruchomienie aktywuje istniejącą instancję.",
    L"OVLÁDANIE\r\nĽavým tlačidlom a ťahaním presuniete hodiny alebo panel. Samostatný kalendár "
    L"sa presúva za voľnú plochu. Pravé tlačidlo na widgete alebo ikone v oznamovacej oblasti "
    L"otvorí ponuku. Ľavé kliknutie na ikonu skryje viditeľné widgety; ak sú všetky skryté, "
    L"obnoví iba naposledy skryté widgety.\r\n\r\nWIDGETY A NASTAVENIA\r\nMožno pridať, odobrať a "
    L"duplikovať ručičkové hodiny, digitálne hodiny, kalendáre, kombinované panely a hodiny na "
    L"monitore. Každý widget má vlastnú viditeľnosť, režim vždy navrchu, jazyk, časové pásmo a "
    L"offset vo formáte [-]HH:mm:ss.ff. Ručičkové hodiny majú voliteľnú veľkosť. Digitálne hodiny "
    L"ponúkajú sekundy, úvodnú nulu, písmo, farby, nepriehľadnosť a priehľadné pozadie. Kalendár "
    L"ponúka čísla týždňov, nedeľu ako prvý deň a používa jazyk "
    L"widgetu.\r\n\r\nBUDÍK\r\nAplikácia prehrá zvukový súbor sama raz alebo dookola; ostatné "
    L"súbory a príkazy odovzdá systému Windows. Kliknutie na budík, príkaz Zastaviť budík alebo "
    L"Esc zastaví signalizáciu aj interný zvuk.\r\n\r\nSKRATKY A UKLADANIE\r\nDvojklik na "
    L"ciferník alebo digitálny displej prepne sekundy, F1 otvorí pomoc a B nastavenia. Polohy a "
    L"všetky nastavenia sa ukladajú do zvoleného úložiska. Ďalšie spustenie aktivuje existujúcu "
    L"inštanciu.",
    L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a standalone calendar by "
    L"its free area. Right-click a widget or notification icon for its menu. Left-click the "
    L"notification icon to hide the currently visible widgets; when all are hidden, it restores "
    L"only the widgets hidden most recently.\r\n\r\nWIDGETS AND SETTINGS\r\nSettings can add, "
    L"remove and duplicate analog clocks, digital clocks, calendars, calendar-and-clock panels "
    L"and monitor clocks. Each widget has its own visibility, always-on-top state, language, time "
    L"zone and offset. Enter offsets as [-]HH:mm:ss.ff. Analog clocks and panel clocks have "
    L"selectable sizes. Digital clocks support seconds, a leading zero, font, colours, opacity "
    L"and a transparent background. Calendars support week numbers and Sunday as the first day "
    L"and use the widget language.\r\n\r\nALARM\r\nClocks and panels can have an alarm. The "
    L"application plays an audio file itself, once or continuously according to the loop option. "
    L"Other files or commands are passed to Windows. Click the alarming clock face or display, "
    L"choose Stop alarm, or press Esc to stop both the alarm indication and audio played by the "
    L"application.\r\n\r\nSHORTCUTS AND SAVING\r\nDouble-click a clock face or digital display to "
    L"toggle seconds, press F1 for Help, B for Settings, and Esc to hide a widget when no alarm "
    L"is being stopped. Widget positions are saved after dragging, dialog positions when closed, "
    L"and all settings in the selected storage. Starting the program again activates the running "
    L"instance and keeps widgets at the nearest available point in the work area.",
    L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a standalone calendar by "
    L"its free area. Right-click a widget or notification icon for its menu. Left-click the "
    L"notification icon to hide the currently visible widgets; when all are hidden, it restores "
    L"only the widgets hidden most recently.\r\n\r\nWIDGETS AND SETTINGS\r\nSettings can add, "
    L"remove and duplicate analog clocks, digital clocks, calendars, calendar-and-clock panels "
    L"and monitor clocks. Each widget has its own visibility, always-on-top state, language, time "
    L"zone and offset. Enter offsets as [-]HH:mm:ss.ff. Analog clocks and panel clocks have "
    L"selectable sizes. Digital clocks support seconds, a leading zero, font, colours, opacity "
    L"and a transparent background. Calendars support week numbers and Sunday as the first day "
    L"and use the widget language.\r\n\r\nALARM\r\nClocks and panels can have an alarm. The "
    L"application plays an audio file itself, once or continuously according to the loop option. "
    L"Other files or commands are passed to Windows. Click the alarming clock face or display, "
    L"choose Stop alarm, or press Esc to stop both the alarm indication and audio played by the "
    L"application.\r\n\r\nSHORTCUTS AND SAVING\r\nDouble-click a clock face or digital display to "
    L"toggle seconds, press F1 for Help, B for Settings, and Esc to hide a widget when no alarm "
    L"is being stopped. Widget positions are saved after dragging, dialog positions when closed, "
    L"and all settings in the selected storage. Starting the program again activates the running "
    L"instance and keeps widgets at the nearest available point in the work area.",
    L"CONTROLOS\r\nArraste um relógio ou painel com o botão esquerdo. Arraste um calendário "
    L"autónomo pela área livre. O botão direito abre o menu do widget. Um clique esquerdo no "
    L"ícone de notificação oculta os widgets visíveis ou repõe os ocultados mais "
    L"recentemente.\r\n\r\nWIDGETS E DEFINIÇÕES\r\nPode adicionar, remover e duplicar relógios "
    L"analógicos, digitais, calendários, painéis combinados e relógios de monitor. Cada widget "
    L"tem visibilidade, posição no topo, idioma, fuso horário e desvio "
    L"próprios.\r\n\r\nALARME\r\nRelógios e painéis podem ter um alarme. Clique no mostrador ou "
    L"visor em alarme, escolha Parar alarme ou prima Esc para parar a indicação e o áudio "
    L"interno.\r\n\r\nATALHOS\r\nUm duplo clique no mostrador ou visor digital alterna os "
    L"segundos, F1 abre a Ajuda, B abre as Definições e Esc oculta o widget.",
    L"KONTROLLER\r\nDra en klokke eller et panel med venstre museknapp. Dra en frittstående "
    L"kalender i det ledige området. Høyreklikk åpner widgetmenyen. Et venstreklikk på "
    L"systemstatusikonet skjuler synlige widgeter eller gjenoppretter de sist "
    L"skjulte.\r\n\r\nWIDGETER OG INNSTILLINGER\r\nDu kan legge til, fjerne og duplisere analoge "
    L"klokker, digitale klokker, kalendere, kombinerte paneler og skjermklokker. Hver widget har "
    L"egne innstillinger for synlighet, alltid øverst, språk, tidssone og "
    L"forskyvning.\r\n\r\nALARM\r\nKlokker og paneler kan ha en alarm. Klikk urskiven eller "
    L"skjermen som alarmerer, velg Stopp alarm eller trykk Esc for å stoppe indikasjonen og "
    L"intern lyd.\r\n\r\nSNARVEIER\r\nDobbeltklikk på urskiven eller den digitale visningen "
    L"veksler sekunder, F1 åpner Hjelp, B åpner Innstillinger og Esc skjuler widgeten.",
    L"KONTROLLER\r\nDra en klocka eller panel med vänster musknapp. Dra en fristående kalender i "
    L"det fria området. Högerklick öppnar widgetmenyn. Ett vänsterklick på meddelandeikonen "
    L"döljer synliga widgetar eller återställer de senast dolda.\r\n\r\nWIDGETAR OCH "
    L"INSTÄLLNINGAR\r\nDu kan lägga till, ta bort och duplicera analoga klockor, digitala "
    L"klockor, kalendrar, kombinerade paneler och skärmklockor. Varje widget har egna "
    L"inställningar för synlighet, alltid överst, språk, tidszon och "
    L"förskjutning.\r\n\r\nALARM\r\nKlockor och paneler kan ha ett alarm. Klicka på urtavlan "
    L"eller displayen som larmar, välj Stoppa alarm eller tryck Esc för att stoppa indikeringen "
    L"och internt ljud.\r\n\r\nGENVÄGAR\r\nDubbelklick på urtavlan eller den digitala displayen "
    L"växlar sekunder, F1 öppnar Hjälp, B öppnar Inställningar och Esc döljer widgeten.",
    L"OHJAUS\r\nVedä kelloa tai paneelia hiiren vasemmalla painikkeella. Vedä erillistä "
    L"kalenteria vapaalta alueelta. Napsauta hiiren kakkospainikkeella avataksesi pienoisohjelman "
    L"valikon. Ilmoitusalueen kuvakkeen napsautus piilottaa näkyvät pienoisohjelmat tai palauttaa "
    L"viimeksi piilotetut.\r\n\r\nPIENOISOHJELMAT JA ASETUKSET\r\nVoit lisätä, poistaa ja "
    L"monistaa analogisia ja digitaalisia kelloja, kalentereita, yhdistelmäpaneeleita ja "
    L"näyttökelloja. Jokaisella on omat näkyvyys-, päällimmäisyys-, kieli-, aikavyöhyke- ja "
    L"poikkeama-asetukset.\r\n\r\nHERÄTYS\r\nKelloissa ja paneeleissa voi olla herätys. Pysäytä "
    L"ilmaisin ja sisäinen ääni napsauttamalla hälyttävää näyttöä, valitsemalla Pysäytä herätys "
    L"tai painamalla Esc.\r\n\r\nPIKANÄPPÄIMET\r\nKellotaulun tai digitaalisen näytön "
    L"kaksoisnapsautus vaihtaa sekuntien näkyvyyttä, F1 avaa ohjeen, B asetukset ja Esc piilottaa "
    L"pienoisohjelman.",
    L"BETJENING\r\nTræk et ur eller panel med venstre museknap. Træk en selvstændig kalender i "
    L"det frie område. Højreklik åbner widgetmenuen. Et venstreklik på meddelelsesikonet skjuler "
    L"synlige widgets eller gendanner de senest skjulte.\r\n\r\nWIDGETS OG INDSTILLINGER\r\nDu "
    L"kan tilføje, fjerne og duplikere analoge ure, digitale ure, kalendere, kombinerede paneler "
    L"og skærmure. Hver widget har egne indstillinger for synlighed, altid øverst, sprog, "
    L"tidszone og forskydning.\r\n\r\nALARM\r\nUre og paneler kan have en alarm. Klik på den "
    L"alarmerende urskive eller visning, vælg Stop alarm eller tryk Esc for at stoppe "
    L"indikationen og intern lyd.\r\n\r\nGENVEJE\r\nDobbeltklik på urskiven eller den digitale "
    L"visning skifter sekunder, F1 åbner Hjælp, B åbner Indstillinger og Esc skjuler widgeten.",
    L"STJÓRNUN\r\nDragðu klukku eða spjald með vinstri músarhnappi. Dragðu sjálfstætt dagatal á "
    L"auðu svæði. Hægrismellur opnar valmynd græju. Vinstrismellur á tilkynningatáknið felur "
    L"sýnilegar græjur eða endurheimtir þær sem síðast voru faldar.\r\n\r\nGRÆJUR OG "
    L"STILLINGAR\r\nHægt er að bæta við, fjarlægja og afrita skífuklukkur, stafrænar klukkur, "
    L"dagatöl, samsett spjöld og skjáklukkur. Hver græja hefur eigið sýnileika-, efst-, "
    L"tungumála-, tímabeltis- og hliðrunargildi.\r\n\r\nVEKJARI\r\nKlukkur og spjöld geta haft "
    L"vekjara. Smelltu á skífuna eða skjáinn, veldu Stöðva vekjara eða ýttu á Esc til að stöðva "
    L"merkingu og innra hljóð.\r\n\r\nFLÝTILEIÐIR\r\nTvísmellur á skífu eða stafrænan skjá "
    L"skiptir um sýnileika sekúndna, F1 opnar Hjálp, B opnar Stillingar og Esc felur græjuna.",
    L"DENETİMLER\r\nBir saati veya paneli sol fare düğmesiyle sürükleyin. Bağımsız takvimi boş "
    L"alanından sürükleyin. Sağ tıklama araç menüsünü açar. Bildirim simgesine sol tıklamak "
    L"görünür araçları gizler veya en son gizlenenleri geri getirir.\r\n\r\nARAÇLAR VE "
    L"AYARLAR\r\nAnalog saatler, dijital saatler, takvimler, birleşik paneller ve monitör "
    L"saatleri ekleyebilir, kaldırabilir ve çoğaltabilirsiniz. Her aracın görünürlük, her zaman "
    L"üstte, dil, saat dilimi ve ofset ayarları ayrıdır.\r\n\r\nALARM\r\nSaatlerde ve panellerde "
    L"alarm olabilir. Alarm veren kadrana veya ekrana tıklayın, Alarmı durdur'u seçin ya da "
    L"göstergeyi ve dahili sesi durdurmak için Esc tuşuna basın.\r\n\r\nKISAYOLLAR\r\nKadrana "
    L"veya dijital ekrana çift tıklama saniyeleri açıp kapatır, F1 Yardım'ı, B Ayarlar'ı açar ve "
    L"Esc aracı gizler.",
    L"Juhtimine\r\nLohistage kella või paneeli hiire vasaku nupuga. Eraldi kalendrit saab "
    L"lohistada vabast alast. Paremklõps vidinal või olekuala ikoonil avab menüü. Vasakklõps "
    L"ikoonil peidab nähtavad vidinad; kui kõik on peidetud, taastab see ainult viimati peidetud "
    L"vidinad.\r\n\r\nVidinad ja sätted\r\n\r\nSätetes saab lisada, eemaldada ja dubleerida "
    L"analoogkelli, digitaalkelli, kalendreid, kalendri ja kella paneele ning ekraanikelli. Igal "
    L"vidinal on oma nähtavus, suvand Alati pealmine, keel, ajavöönd ja nihe kujul "
    L"[-]HH:mm:ss.ff. Analoogkella ja paneeli kellade suurust saab valida eraldi. Digitaalkellal "
    L"on sekundite, algusnulli, fondi, värvide, läbipaistmatuse ja läbipaistva tausta sätted. "
    L"Kalender toetab nädalanumbreid ja pühapäeva nädala esimese päevana ning kasutab vidina "
    L"keelt.\r\n\r\nÄratus ja kiirklahvid\r\n\r\nKelladel ja paneelidel võib olla äratus. "
    L"Rakendus esitab helifaili ise ühe korra või pidevalt vastavalt kordamise sättele; muud "
    L"failid ja käsud edastatakse Windowsile. Klõps ärataval sihverplaadil või kuval, Peata "
    L"äratus või Esc peatab nii äratuse tähistuse kui ka rakenduse heli. Topeltklõps "
    L"sihverplaadil või digitaalkuval lülitab sekundeid. F1 avab spikri, B sätted ja Esc peidab "
    L"vidina, kui ei peatata äratust. Vidina asukoht salvestatakse lohistamise järel, dialoogi "
    L"asukoht sulgemisel ja sätted valitud salvestuskohta. Korduskäivitus aktiveerib töötava "
    L"eksemplari ning vidinad jäävad tööala lähimasse saadaolevasse punkti.",
    L"Rialuithe\r\nTarraing clog nó painéal leis an gcnaipe luiche ar chlé. Tarraing féilire "
    L"neamhspleách ón achar saor. Osclaíonn deaschliceáil ar ghiuirléid nó ar dheilbhín an "
    L"limistéir fógraí an roghchlár. Folaíonn clé-chliceáil ar an deilbhín na giuirléidí "
    L"infheicthe; má tá siad uile i bhfolach, ní athchóirítear ach na cinn is déanaí a "
    L"folaíodh.\r\n\r\nGiuirléidí agus socruithe\r\n\r\nIs féidir cloig analógacha, cloig "
    L"dhigiteacha, féilirí, painéil féilire agus cloig agus cloig scáileáin a chur leis, a bhaint "
    L"agus a dhúbailt sna Socruithe. Tá infheictheacht, Ar barr i gcónaí, teanga, crios ama agus "
    L"fritháireamh [-]HH:mm:ss.ff ar leith ag gach giuirléid. Roghnaítear méideanna na "
    L"n-aghaidheanna ar leith. Tacaíonn cloig dhigiteacha le soicindí, nialas tosaigh, cló, "
    L"dathanna, teimhneacht agus cúlra trédhearcach. Tacaíonn féilirí le huimhreacha seachtainí "
    L"agus Dé Domhnaigh mar chéad lá agus úsáideann siad teanga na giuirléide.\r\n\r\nAláram agus "
    L"aicearraí\r\n\r\nIs féidir aláram a shocrú do chloig agus do phainéil. Seinneann an "
    L"feidhmchlár comhad fuaime é féin uair amháin nó go leanúnach de réir na rogha athsheinnte; "
    L"cuirtear comhaid agus orduithe eile ar aghaidh chuig Windows. Stopann cliceáil ar aghaidh "
    L"nó taispeáint an aláraim, Stop an t-aláram nó Esc an comhartha amhairc agus fuaim an "
    L"fheidhmchláir. Athraíonn déchliceáil ar aghaidh nó taispeáint dhigiteach na soicindí. "
    L"Osclaíonn F1 Cabhair agus B Socruithe; folaíonn Esc giuirléid mura bhfuil aláram á stopadh. "
    L"Sábháiltear suíomhanna giuirléidí tar éis tarraingthe, suíomhanna dialóg nuair a dhúntar "
    L"iad agus na socruithe sa stóras roghnaithe. Má sheoltar CalClock arís, gníomhachtaítear an "
    L"feidhmchlár atá ar siúl cheana agus coinnítear na giuirléidí ag an bpointe is gaire atá ar "
    L"fáil sa limistéar oibre.",
    L"Valdymas\r\nVilkite laikrodį arba skydelį kairiuoju pelės mygtuku. Atskiras kalendorius "
    L"velkamas už laisvos srities. Dešiniuoju mygtuku spustelėjus valdiklį arba pranešimų srities "
    L"piktogramą atidaromas meniu. Kairysis piktogramos spustelėjimas paslepia matomus "
    L"valdiklius; jei visi paslėpti, atkuriami tik paskutinį kartą paslėpti "
    L"valdikliai.\r\n\r\nValdikliai ir parametrai\r\n\r\nParametruose galima įtraukti, pašalinti "
    L"ir dubliuoti analoginius bei skaitmeninius laikrodžius, kalendorius, kalendoriaus su "
    L"laikrodžiu skydelius ir ekrano laikrodžius. Kiekvienas turi atskirą matomumą, Visada "
    L"viršuje, kalbą, laiko juostą ir poslinkį [-]HH:mm:ss.ff. Ciferblatų dydžiai pasirenkami "
    L"atskirai. Skaitmeniniams laikrodžiams galima nustatyti sekundes, pradinį nulį, šriftą, "
    L"spalvas, nepermatomumą ir permatomą foną. Kalendorius palaiko savaičių numerius ir "
    L"sekmadienį kaip pirmąją dieną; pavadinimai rodomi valdiklio kalba.\r\n\r\nŽadintuvas ir "
    L"spartieji klavišai\r\n\r\nLaikrodžiai ir skydeliai palaiko žadintuvą. Programa pati leidžia "
    L"garso failą vieną kartą arba nuolat pagal kartojimo nuostatą; kiti failai ir komandos "
    L"perduodami „Windows“. Spustelėjus skambantį ciferblatą ar ekraną, pasirinkus Stabdyti "
    L"žadintuvą arba paspaudus Esc, sustabdomas vaizdinis signalas ir programos garsas. Dukart "
    L"spustelėjus ciferblatą arba skaitmeninį ekraną perjungiamos sekundės. F1 atidaro žinyną, B "
    L"– parametrus, Esc paslepia valdiklį, jei nestabdomas žadintuvas. Valdiklių padėtys įrašomos "
    L"nuvilkus, dialogų – juos uždarius, o parametrai – pasirinktoje saugykloje. Pakartotinis "
    L"paleidimas suaktyvina veikiantį egzempliorių; valdikliai paliekami artimiausioje "
    L"pasiekiamoje darbo srities vietoje.",
    L"Vadība\r\nVelciet pulksteni vai paneli ar peles kreiso pogu. Atsevišķu kalendāru velciet "
    L"aiz brīvās zonas. Labais klikšķis uz logrīka vai paziņojumu apgabala ikonas atver izvēlni. "
    L"Kreisais klikšķis uz ikonas paslēpj redzamos logrīkus; ja visi ir paslēpti, atjauno tikai "
    L"pēdējos paslēptos.\r\n\r\nLogrīki un iestatījumi\r\n\r\nIestatījumos var pievienot, noņemt "
    L"un dublēt analogos un digitālos pulksteņus, kalendārus, kalendāra un pulksteņa paneļus un "
    L"ekrāna pulksteņus. Katram logrīkam ir sava redzamība, Vienmēr virspusē, valoda, laika josla "
    L"un nobīde [-]HH:mm:ss.ff. Ciparnīcu lielumi ir izvēlami atsevišķi. Digitālajiem pulksteņiem "
    L"ir sekundes, sākuma nulle, fonts, krāsas, necaurspīdīgums un caurspīdīgs fons. Kalendāri "
    L"atbalsta nedēļu numurus un svētdienu kā pirmo dienu un izmanto logrīka "
    L"valodu.\r\n\r\nModinātājs un īsinājumtaustiņi\r\n\r\nPulksteņi un paneļi atbalsta "
    L"modinātāju. Programma pati atskaņo skaņas failu vienreiz vai nepārtraukti atbilstoši "
    L"atkārtošanas izvēlei; citus failus un komandas nodod Windows. Klikšķis uz aktīvā modinātāja "
    L"ciparnīcas vai displeja, Apturēt modinātāju vai Esc aptur indikāciju un programmas skaņu. "
    L"Dubultklikšķis uz ciparnīcas vai digitālā displeja pārslēdz sekundes. F1 atver palīdzību, B "
    L"iestatījumus, Esc paslēpj logrīku, ja netiek apturēts modinātājs. Logrīka novietojumu "
    L"saglabā pēc vilkšanas, dialoga novietojumu aizverot, iestatījumus izvēlētajā krātuvē. "
    L"Atkārtota palaišana aktivizē esošo programmas eksemplāru un notur logrīkus tuvākajā "
    L"pieejamajā darba apgabala vietā.",
    L"Kezelés\r\nAz órát vagy panelt a bal egérgombbal húzhatja. Az önálló naptárt a szabad "
    L"területénél fogva mozgathatja. A minialkalmazásra vagy az értesítési terület ikonjára "
    L"kattintva a jobb gombbal menüt nyithat. Az ikonra kattintva a bal gombbal elrejtheti a "
    L"látható minialkalmazásokat; ha mind rejtett, csak a legutóbb elrejtettek térnek "
    L"vissza.\r\n\r\nMinialkalmazások és beállítások\r\n\r\nA Beállítások között analóg és "
    L"digitális órákat, naptárakat, naptárat és órát tartalmazó paneleket, valamint "
    L"képernyőórákat adhat hozzá, távolíthat el és másolhat. Minden minialkalmazás külön "
    L"láthatósággal, Mindig felül állapottal, nyelvvel, időzónával és [-]HH:mm:ss.ff eltolással "
    L"rendelkezik. A számlapméretek külön választhatók. A digitális órák másodperceket, vezető "
    L"nullát, betűtípust, színeket, átlátszatlanságot és átlátszó hátteret támogatnak. A naptár "
    L"megjeleníti a hétszámokat, kezdődhet vasárnappal, és a minialkalmazás nyelvét "
    L"használja.\r\n\r\nÉbresztés és billentyűparancsok\r\n\r\nAz órákhoz és panelekhez ébresztés "
    L"állítható be. A program a hangfájlt maga játssza le egyszer vagy folyamatosan az ismétlés "
    L"szerint; a többi fájlt és parancsot átadja a Windowsnak. Az ébresztő számlapra vagy "
    L"kijelzőre kattintva, az Ébresztés leállítása paranccsal vagy az Esc billentyűvel a jelzés "
    L"és a program hangja leállítható. A számlapra vagy digitális kijelzőre duplán kattintva a "
    L"másodperceket kapcsolhatja. Az F1 a Súgót, a B a Beállításokat nyitja meg; az Esc elrejti a "
    L"minialkalmazást, ha nem ébresztést állít le. A helyzetet húzás után, a párbeszédablak "
    L"helyét bezáráskor, a beállításokat a kiválasztott tárolóban menti a program. Az újabb "
    L"indítás a futó példányt aktiválja, és a minialkalmazásokat a munkaterület legközelebbi "
    L"elérhető pontján tartja.",
    L"Kontrolli\r\nMexxi arloġġ jew panew billi tkaxkru bil-buttuna tax-xellug tal-maws. "
    L"Kalendarju separat jitmexxa miż-żona vojta tiegħu. Klikk bil-lemin fuq widget jew l-ikona "
    L"taż-żona tan-notifiki jiftaħ il-menu. Klikk bix-xellug fuq l-ikona jaħbi l-widgets "
    L"viżibbli; jekk kollha moħbija, jirrestawra biss dawk li nħbew l-aħħar.\r\n\r\nWidgets u "
    L"settings\r\n\r\nFis-Settings tista’ żżid, tneħħi u tidduplika arloġġi analogi u diġitali, "
    L"kalendarji, panewijiet tal-kalendarju bl-arloġġ u arloġġi tal-iskrin. Kull widget għandu "
    L"l-viżibbiltà, Dejjem fuq nett, il-lingwa, iż-żona tal-ħin u l-kumpens [-]HH:mm:ss.ff "
    L"tiegħu. Id-daqsijiet tal-uċuħ jintgħażlu separatament. L-arloġġi diġitali jappoġġjaw "
    L"sekondi, żero fil-bidu, font, kuluri, opaċità u sfond trasparenti. Il-kalendarju jappoġġja "
    L"numri tal-ġimgħat u l-Ħadd bħala l-ewwel jum u juża l-lingwa tal-widget.\r\n\r\nAllarm u "
    L"shortcuts\r\n\r\nL-arloġġi u l-panewijiet jistgħu jkollhom allarm. Il-programm idoqq fajl "
    L"tal-awdjo huwa stess darba jew kontinwament skont ir-ripetizzjoni; fajls u kmandi oħra "
    L"jintbagħtu lill-Windows. Klikk fuq il-wiċċ jew il-wiri tal-allarm attiv, Waqqaf l-allarm "
    L"jew Esc iwaqqaf l-indikazzjoni u l-awdjo tal-programm. Klikk doppju fuq wiċċ jew wiri "
    L"diġitali jaqleb is-sekondi. F1 jiftaħ l-Għajnuna, B is-Settings, u Esc jaħbi widget jekk "
    L"mhux qed iwaqqaf allarm. Il-pożizzjonijiet tal-widgets jiġu ssejvjati wara t-tkaxkir, dawk "
    L"tad-djalogi meta jingħalqu, u s-settings fil-ħażna magħżula. Tnedija oħra tattiva l-istanza "
    L"li diġà qed taħdem u żżomm il-widgets fl-eqreb punt disponibbli taż-żona tax-xogħol.",
    L"Bediening\r\nSleep een klok of paneel met de linkermuisknop. Sleep een losse kalender via "
    L"de vrije ruimte. Klik met rechts op een widget of het pictogram in het systeemvak voor het "
    L"menu. Klik met links op het pictogram om zichtbare widgets te verbergen; als alles "
    L"verborgen is, worden alleen de laatst verborgen widgets hersteld.\r\n\r\nWidgets en "
    L"instellingen\r\n\r\nVia Instellingen kunt u analoge en digitale klokken, kalenders, "
    L"kalenderpanelen met een klok en schermklokken toevoegen, verwijderen en dupliceren. Elke "
    L"widget heeft een eigen zichtbaarheid, Altijd op voorgrond, taal, tijdzone en verschuiving "
    L"[-]HH:mm:ss.ff. Wijzerplaatgroottes zijn afzonderlijk instelbaar. Digitale klokken "
    L"ondersteunen seconden, een voorloopnul, lettertypen, kleuren, dekking en een transparante "
    L"achtergrond. Kalenders ondersteunen weeknummers en zondag als eerste dag en gebruiken de "
    L"widgettaal.\r\n\r\nAlarm en sneltoetsen\r\n\r\nKlokken en panelen kunnen een alarm hebben. "
    L"De toepassing speelt een geluidsbestand zelf eenmaal of voortdurend af volgens de "
    L"herhaaloptie; andere bestanden en opdrachten worden aan Windows doorgegeven. Klik op de "
    L"alarmerende wijzerplaat of weergave, kies Alarm stoppen of druk op Esc om de aanduiding en "
    L"het geluid van de toepassing te stoppen. Dubbelklikken op een wijzerplaat of digitale "
    L"weergave schakelt seconden om. F1 opent Help, B Instellingen en Esc verbergt een widget "
    L"wanneer er geen alarm wordt gestopt. Widgetposities worden na slepen opgeslagen, "
    L"dialoogposities bij sluiten en instellingen in de gekozen opslag. Opnieuw starten activeert "
    L"de bestaande toepassing en houdt widgets op de dichtstbijzijnde beschikbare plaats in het "
    L"werkgebied.",
    L"Comenzi\r\nGlisați ceasul sau panoul cu butonul stâng al mouse-ului. Un calendar separat se "
    L"glisează din zona liberă. Un clic dreapta pe widget sau pe pictograma din zona de "
    L"notificare deschide meniul. Un clic stânga pe pictogramă ascunde widgeturile vizibile; dacă "
    L"toate sunt ascunse, le restabilește numai pe cele ascunse ultima dată.\r\n\r\nWidgeturi și "
    L"setări\r\n\r\nÎn Setări puteți adăuga, elimina și dubla ceasuri analogice și digitale, "
    L"calendare, panouri calendar cu ceas și ceasuri pe ecran. Fiecare are propria vizibilitate, "
    L"Întotdeauna deasupra, limbă, fus orar și decalaj [-]HH:mm:ss.ff. Dimensiunile cadranelor se "
    L"aleg separat. Ceasurile digitale oferă secunde, zero inițial, fonturi, culori, opacitate și "
    L"fundal transparent. Calendarele acceptă numere de săptămâni și duminica drept prima zi și "
    L"folosesc limba widgetului.\r\n\r\nAlarmă și comenzi rapide\r\n\r\nCeasurile și panourile "
    L"pot avea alarmă. Aplicația redă singură fișierul audio o dată sau continuu, conform "
    L"repetării; alte fișiere și comenzi sunt transmise către Windows. Un clic pe cadranul sau "
    L"afișajul alarmei active, Oprire alarmă ori Esc oprește indicația și sunetul aplicației. Un "
    L"dublu clic pe cadran sau afișaj digital comută secundele. F1 deschide Ajutor, B Setări, iar "
    L"Esc ascunde widgetul dacă nu oprește o alarmă. Pozițiile widgeturilor se salvează după "
    L"glisare, cele ale dialogurilor la închidere, iar setările în spațiul de stocare ales. O "
    L"nouă pornire activează instanța existentă și păstrează widgeturile în cel mai apropiat "
    L"punct disponibil al zonei de lucru.",
    L"Χειρισμός\r\nΣύρετε ένα ρολόι ή πλαίσιο με το αριστερό κουμπί του ποντικιού. Σύρετε ένα "
    L"ανεξάρτητο ημερολόγιο από την ελεύθερη περιοχή του. Το δεξί κλικ σε γραφικό στοιχείο ή στο "
    L"εικονίδιο της περιοχής ειδοποιήσεων ανοίγει το μενού. Το αριστερό κλικ στο εικονίδιο κρύβει "
    L"τα ορατά στοιχεία· αν όλα είναι κρυφά, επαναφέρει μόνο όσα αποκρύφτηκαν "
    L"τελευταία.\r\n\r\nΓραφικά στοιχεία και ρυθμίσεις\r\n\r\nΣτις Ρυθμίσεις προσθέτετε, "
    L"καταργείτε και αντιγράφετε αναλογικά και ψηφιακά ρολόγια, ημερολόγια, πλαίσια ημερολογίου "
    L"με ρολόι και ρολόγια οθόνης. Κάθε στοιχείο έχει δική του ορατότητα, Πάντα σε πρώτο πλάνο, "
    L"γλώσσα, ζώνη ώρας και μετατόπιση [-]HH:mm:ss.ff. Τα μεγέθη των καντράν επιλέγονται χωριστά. "
    L"Τα ψηφιακά ρολόγια υποστηρίζουν δευτερόλεπτα, αρχικό μηδενικό, γραμματοσειρά, χρώματα, "
    L"αδιαφάνεια και διαφανές φόντο. Τα ημερολόγια υποστηρίζουν αριθμούς εβδομάδων και Κυριακή ως "
    L"πρώτη ημέρα και χρησιμοποιούν τη γλώσσα του στοιχείου.\r\n\r\nΞυπνητήρι και "
    L"συντομεύσεις\r\n\r\nΤα ρολόγια και τα πλαίσια υποστηρίζουν ξυπνητήρι. Η εφαρμογή αναπαράγει "
    L"το αρχείο ήχου μία φορά ή συνεχώς σύμφωνα με την επανάληψη· άλλα αρχεία και εντολές "
    L"διαβιβάζονται στα Windows. Κλικ στο ενεργό καντράν ή στην ένδειξη, Διακοπή αφύπνισης ή Esc "
    L"σταματά την οπτική ένδειξη και τον ήχο της εφαρμογής. Το διπλό κλικ στο καντράν ή στην "
    L"ψηφιακή ένδειξη αλλάζει την εμφάνιση δευτερολέπτων. Το F1 ανοίγει τη Βοήθεια, το B τις "
    L"Ρυθμίσεις, το Esc κρύβει το στοιχείο όταν δεν σταματά ξυπνητήρι. Οι θέσεις των στοιχείων "
    L"αποθηκεύονται μετά τη μεταφορά, των παραθύρων διαλόγου κατά το κλείσιμο και οι ρυθμίσεις "
    L"στον επιλεγμένο χώρο αποθήκευσης. Νέα εκκίνηση ενεργοποιεί την υπάρχουσα παρουσία και "
    L"διατηρεί τα στοιχεία στο πλησιέστερο διαθέσιμο σημείο της περιοχής εργασίας.",
    L"Upravljanje\r\nPovucite sat ili ploču lijevom tipkom miša. Samostalni kalendar povlači se "
    L"za slobodno područje. Desnom tipkom kliknite vidžet ili ikonu u području obavijesti za "
    L"otvaranje menija. Lijevi klik na ikonu skriva vidljive vidžete; ako su svi skriveni, vraća "
    L"samo posljednje skrivene vidžete.\r\n\r\nVidžeti i postavke\r\n\r\nU Postavkama možete "
    L"dodavati, uklanjati i duplicirati analogne i digitalne satove, kalendare, ploče kalendara "
    L"sa satom i satove na ekranu. Svaki vidžet ima vlastitu vidljivost, način Uvijek na vrhu, "
    L"jezik, vremensku zonu i vremenski pomak. Pomak unesite kao [-]HH:mm:ss.ff. Veličina "
    L"analognih satova i satova na ploči može se odabrati. Digitalni satovi podržavaju sekunde, "
    L"početnu nulu, font, boje, neprozirnost i prozirnu pozadinu. Kalendar podržava brojeve "
    L"sedmica i nedjelju kao prvi dan te koristi jezik vidžeta.\r\n\r\nAlarm\r\n\r\nSatovi i "
    L"ploče mogu imati alarm. Program sam reproducira zvučnu datoteku jednom ili neprekidno, "
    L"zavisno o postavci ponavljanja. Ostale datoteke i naredbe predaju se Windowsu. Kliknite "
    L"brojčanik ili ekran aktivnog alarma, odaberite Zaustavi alarm ili pritisnite Esc za "
    L"zaustavljanje signalizacije i zvuka koji reproducira program.\r\n\r\nPrečaci i "
    L"čuvanje\r\n\r\nDvostruki klik na brojčanik ili digitalni ekran uključuje ili isključuje "
    L"sekunde. F1 otvara pomoć, B otvara Postavke, a Esc skriva vidžet ako ne zaustavlja alarm. "
    L"Položaji vidžeta čuvaju se nakon povlačenja, položaji dijaloških prozora pri zatvaranju, a "
    L"postavke u odabrano spremište. Ponovno pokretanje aktivira već pokrenutu instancu i "
    L"zadržava vidžete na najbližem dostupnom mjestu radnog područja.",
    L"Upravljanje\r\nPovucite sat ili ploču lijevom tipkom miša. Samostalni kalendar povlači se "
    L"za slobodno područje. Desnom tipkom kliknite widget ili ikonu u području obavijesti za "
    L"otvaranje izbornika. Lijevi klik na ikonu skriva vidljive widgete; ako su svi skriveni, "
    L"vraća samo posljednje skrivene widgete.\r\n\r\nWidgeti i postavke\r\n\r\nU Postavkama "
    L"možete dodavati, uklanjati i duplicirati analogne i digitalne satove, kalendare, ploče "
    L"kalendara sa satom i satove na zaslonu. Svaki widget ima vlastitu vidljivost, način Uvijek "
    L"na vrhu, jezik, vremensku zonu i vremenski pomak. Pomak unesite kao [-]HH:mm:ss.ff. "
    L"Veličina analognih satova i satova na ploči može se odabrati. Digitalni satovi podržavaju "
    L"sekunde, početnu nulu, font, boje, neprozirnost i prozirnu pozadinu. Kalendar podržava "
    L"brojeve tjedana i nedjelju kao prvi dan te koristi jezik "
    L"widgeta.\r\n\r\nAlarm\r\n\r\nSatovi i ploče mogu imati alarm. Program sam reproducira "
    L"zvučnu datoteku jednom ili neprekidno, ovisno o postavci ponavljanja. Ostale datoteke i "
    L"naredbe predaju se Windowsu. Kliknite brojčanik ili zaslon aktivnog alarma, odaberite "
    L"Zaustavi alarm ili pritisnite Esc za zaustavljanje signalizacije i zvuka koji reproducira "
    L"program.\r\n\r\nPrečaci i spremanje\r\n\r\nDvostruki klik na brojčanik ili digitalni zaslon "
    L"uključuje ili isključuje sekunde. F1 otvara pomoć, B otvara Postavke, a Esc skriva widget "
    L"ako ne zaustavlja alarm. Položaji widgeta spremaju se nakon povlačenja, položaji dijaloških "
    L"prozora pri zatvaranju, a postavke u odabrano spremište. Ponovno pokretanje aktivira već "
    L"pokrenutu instancu i zadržava widgete na najbližem dostupnom mjestu radnog područja.",
    L"Upravljanje\r\nUro ali ploščo povlecite z levim miškinim gumbom. Samostojni koledar "
    L"premikate za prosti del. Desni klik na gradnik ali ikono v območju za obvestila odpre meni. "
    L"Levi klik na ikono skrije vidne gradnike; če so vsi skriti, obnovi samo nazadnje "
    L"skrite.\r\n\r\nGradniki in nastavitve\r\n\r\nV Nastavitvah lahko dodajate, odstranjujete in "
    L"podvajate analogne in digitalne ure, koledarje, plošče koledarja z uro ter ure na zaslonu. "
    L"Vsak gradnik ima lastno vidnost, možnost Vedno na vrhu, jezik, časovni pas in odmik v "
    L"obliki [-]HH:mm:ss.ff. Velikost analognih ur in ur na plošči je nastavljiva. Digitalne ure "
    L"podpirajo sekunde, vodilno ničlo, pisavo, barve, neprosojnost in prosojno ozadje. Koledar "
    L"podpira številke tednov in nedeljo kot prvi dan ter uporablja jezik "
    L"gradnika.\r\n\r\nBudilka in bližnjice\r\n\r\nUre in plošče podpirajo budilko. Program sam "
    L"predvaja zvočno datoteko enkrat ali neprekinjeno glede na ponavljanje; druge datoteke in "
    L"ukaze preda sistemu Windows. Klik na številčnico ali prikaz aktivne budilke, Ustavi budilko "
    L"ali Esc ustavi opozarjanje in zvok programa. Dvoklik na številčnico ali digitalni prikaz "
    L"preklopi sekunde. F1 odpre pomoč, B Nastavitve, Esc pa skrije gradnik, kadar ne ustavlja "
    L"budilke. Položaji gradnikov se shranijo po premikanju, položaji pogovornih oken ob zaprtju, "
    L"nastavitve pa v izbrano shrambo. Ponovni zagon aktivira obstoječi primerek in ohrani "
    L"gradnike na najbližjem dosegljivem mestu delovnega območja.",
    L"Upravljanje\r\nPovucite sat ili panel lijevim tasterom miša. Samostalni kalendar se pomjera "
    L"preko slobodne površine. Desni klik na vidžet ili ikonu u oblasti za obavještenja otvara "
    L"meni. Lijevi klik na ikonu skriva vidljive vidžete; ako su svi skriveni, vraća samo "
    L"posljednje skrivene.\r\n\r\nVidžeti i podešavanja\r\n\r\nU Podešavanjima možete dodavati, "
    L"uklanjati i duplirati analogne i digitalne satove, kalendare, panele kalendara sa satom i "
    L"satove na monitoru. Svaki vidžet ima sopstvenu vidljivost, režim Uvijek na vrhu, jezik, "
    L"vremensku zonu i pomak u obliku [-]HH:mm:ss.ff. Veličine analognih satova i satova na "
    L"panelu biraju se posebno. Digitalni satovi podržavaju sekunde, vodeću nulu, font, boje, "
    L"neprozirnost i providnu pozadinu. Kalendar podržava brojeve nedjelja i nedjelju kao prvi "
    L"dan i koristi jezik vidžeta.\r\n\r\nAlarm i prečice\r\n\r\nSatovi i paneli podržavaju "
    L"alarm. Program sam pušta zvučnu datoteku jednom ili neprekidno, u zavisnosti od "
    L"ponavljanja. Ostale datoteke i naredbe predaje Windows-u. Klik na brojčanik ili prikaz "
    L"aktivnog alarma, Zaustavi alarm ili Esc zaustavljaju indikaciju i zvuk programa. Dvoklik na "
    L"brojčanik ili digitalni prikaz prebacuje sekunde. F1 otvara pomoć, B Podešavanja, a Esc "
    L"skriva vidžet ako ne zaustavlja alarm. Položaji vidžeta čuvaju se poslije pomjeranja, "
    L"položaji dijaloga pri zatvaranju, a podešavanja u izabranom skladištu. Ponovno pokretanje "
    L"aktivira postojeću instancu i zadržava vidžete na najbližem dostupnom mjestu radne površine.",
    L"Кіраванне\r\nПерацягвайце гадзіннік або панэль левай кнопкай мышы. Асобны каляндар "
    L"перацягваецца за вольную вобласць. Правая кнопка на віджэце або значку ў вобласці "
    L"апавяшчэнняў адкрывае меню. Левая кнопка на значку хавае бачныя віджэты; калі ўсе схаваныя, "
    L"аднаўляе толькі апошнія схаваныя.\r\n\r\nВіджэты і налады\r\n\r\nУ акне «Налады» можна "
    L"дадаваць, выдаляць і дубляваць аналагавыя і лічбавыя гадзіннікі, календары, панэлі "
    L"календара з гадзіннікам і гадзіннікі на маніторы. Кожны віджэт мае ўласныя бачнасць, рэжым "
    L"«Заўсёды зверху», мову, часавы пояс і зрушэнне ў фармаце [-]HH:mm:ss.ff. Памер аналагавых "
    L"гадзіннікаў і гадзіннікаў на панэлі выбіраецца асобна. Лічбавыя гадзіннікі падтрымліваюць "
    L"секунды, пачатковы нуль, шрыфт, колеры, непразрыстасць і празрысты фон. Каляндар "
    L"падтрымлівае нумары тыдняў і нядзелю як першы дзень ды выкарыстоўвае мову "
    L"віджэта.\r\n\r\nБудзільнік і спалучэнні клавіш\r\n\r\nГадзіннікі і панэлі падтрымліваюць "
    L"будзільнік. Праграма прайгравае гукавы файл адзін раз або бесперапынна паводле налады "
    L"паўтарэння. Іншыя файлы і каманды перадаюцца Windows. Пстрычка на цыферблаце ці дысплеі "
    L"актыўнага будзільніка, «Спыніць будзільнік» або Esc спыняюць сігналізацыю і гук праграмы. "
    L"Падвойная пстрычка на цыферблаце ці лічбавым дысплеі пераключае секунды. F1 адкрывае "
    L"даведку, B — налады, а Esc хавае віджэт, калі не спыняе будзільнік. Пазіцыі віджэтаў "
    L"захоўваюцца пасля перацягвання, дыялогавых вокнаў — пры закрыцці, а налады — у выбраным "
    L"сховішчы. Паўторны запуск актывуе ўжо запушчаны асобнік і пакідае віджэты ў найбліжэйшым "
    L"даступным месцы рабочай вобласці.",
    L"Управление\r\nПреместете часовник или панел с плъзгане с левия бутон на мишката. "
    L"Самостоятелният календар се премества чрез свободната му област. Десният бутон върху модул "
    L"или иконата в областта за уведомяване отваря меню. Левият бутон върху иконата скрива "
    L"видимите модули; ако всички са скрити, възстановява само последно "
    L"скритите.\r\n\r\nИзпълними модули и настройки\r\n\r\nВ „Настройки“ можете да добавяте, "
    L"премахвате и дублирате аналогови и цифрови часовници, календари, панели с календар и "
    L"часовник и часовници на монитор. Всеки модул има собствена видимост, режим „Винаги отгоре“, "
    L"език, часова зона и отместване във формат [-]HH:mm:ss.ff. Размерите на аналоговите "
    L"часовници и часовниците в панела се избират отделно. Цифровите часовници поддържат секунди, "
    L"водеща нула, шрифт, цветове, непрозрачност и прозрачен фон. Календарът поддържа номера на "
    L"седмиците и неделя като първи ден и използва езика на модула.\r\n\r\nАларма и клавишни "
    L"комбинации\r\n\r\nЧасовниците и панелите поддържат аларма. Програмата възпроизвежда звуков "
    L"файл веднъж или непрекъснато според настройката за повторение. Другите файлове и команди се "
    L"предават на Windows. Щракнете върху циферблата или дисплея на активната аларма, изберете "
    L"„Спри алармата“ или натиснете Esc, за да спрете индикацията и звука на програмата. Двойното "
    L"щракване върху циферблата или цифровия дисплей превключва секундите. F1 отваря помощта, B — "
    L"настройките, а Esc скрива модула, ако не спира аларма. Позициите на модулите се записват "
    L"след преместване, на диалоговите прозорци — при затваряне, а настройките — в избраното "
    L"хранилище. Повторното стартиране активира работещия екземпляр и оставя модулите на "
    L"най-близкото достъпно място в работната област.",
    L"Управување\r\nПовлечете часовник или панел со левото копче на глувчето. Самостојниот "
    L"календар се поместува преку слободната површина. Десен клик на виџет или иконата во областа "
    L"за известување го отвора менито. Лев клик на иконата ги крие видливите виџети; ако сите се "
    L"скриени, ги враќа само последно скриените.\r\n\r\nВиџети и поставки\r\n\r\nВо „Поставки“ "
    L"можете да додавате, отстранувате и дуплирате аналогни и дигитални часовници, календари, "
    L"панели со календар и часовник и часовници на монитор. Секој виџет има своја видливост, "
    L"режим „Секогаш најгоре“, јазик, временска зона и поместување во облик [-]HH:mm:ss.ff. "
    L"Големината на аналогните часовници и часовниците во панелот се избира одделно. Дигиталните "
    L"часовници поддржуваат секунди, водечка нула, фонт, бои, непроѕирност и проѕирна заднина. "
    L"Календарот поддржува броеви на недели и недела како прв ден и го користи јазикот на "
    L"виџетот.\r\n\r\nАларм и кратенки\r\n\r\nЧасовниците и панелите поддржуваат аларм. "
    L"Програмата самата пушта звучна датотека еднаш или непрекинато според повторувањето. Другите "
    L"датотеки и наредби се предаваат на Windows. Клик на бројчаникот или приказот на активниот "
    L"аларм, „Запри го алармот“ или Esc ги запира сигнализацијата и звукот на програмата. Двоен "
    L"клик на бројчаникот или дигиталниот приказ ги вклучува или исклучува секундите. F1 ја "
    L"отвора помошта, B — поставките, а Esc го крие виџетот ако не запира аларм. Положбите на "
    L"виџетите се зачувуваат по поместување, на дијалозите при затворање, а поставките во "
    L"избраното складиште. Повторното стартување го активира постојниот примерок и ги задржува "
    L"виџетите на најблиското достапно место на работната површина.",
    L"Управљање\r\nПовуците сат или панел левим тастером миша. Самостални календар се помера "
    L"преко слободне површине. Десни клик на виџет или икону у области за обавештења отвара мени. "
    L"Леви клик на икону скрива видљиве виџете; ако су сви скривени, враћа само последње "
    L"скривене.\r\n\r\nВиџети и подешавања\r\n\r\nУ Подешавањима можете додавати, уклањати и "
    L"дуплирати аналогне и дигиталне сатове, календаре, панеле календара са сатом и сатове на "
    L"монитору. Сваки виџет има сопствену видљивост, режим Увек на врху, језик, временску зону и "
    L"помак у облику [-]HH:mm:ss.ff. Величине аналогних сатова и сатова на панелу бирају се "
    L"посебно. Дигитални сатови подржавају секунде, водећу нулу, фонт, боје, непрозирност и "
    L"провидну позадину. Календар подржава бројеве недеља и недељу као први дан и користи језик "
    L"виџета.\r\n\r\nАларм и пречице\r\n\r\nСатови и панели подржавају аларм. Програм сам пушта "
    L"звучну датотеку једном или непрекидно, у зависности од понављања. Остале датотеке и наредбе "
    L"предаје Windows-у. Клик на бројчаник или приказ активног аларма, Заустави аларм или Esc "
    L"заустављају индикацију и звук програма. Двоклик на бројчаник или дигитални приказ пребацује "
    L"секунде. F1 отвара помоћ, B Подешавања, а Esc скрива виџет ако не зауставља аларм. Положаји "
    L"виџета чувају се после померања, дијалога при затварању, а подешавања у изабраном "
    L"складишту. Поновно покретање активира постојећу инстанцу и задржава виџете на најближем "
    L"доступном месту радне површине.",
    L"КЕРУВАННЯ\r\nПеретягуйте годинник або панель лівою кнопкою миші. Окремий календар "
    L"перетягується за вільну область. Клацніть віджет або піктограму в області сповіщень правою "
    L"кнопкою миші, щоб відкрити меню. Ліве клацання піктограми приховує видимі віджети; якщо всі "
    L"віджети приховано, відновлюються лише ті, що були приховані останніми.\r\n\r\nВІДЖЕТИ ТА "
    L"НАЛАШТУВАННЯ\r\nУ вікні «Налаштування» можна додавати, видаляти й дублювати аналогові та "
    L"цифрові годинники, календарі, панелі календаря з годинником і годинники на моніторі. Для "
    L"кожного віджета окремо задаються видимість, режим «Завжди зверху», мова, часовий пояс і "
    L"зсув часу. Зсув вводиться у форматі [-]HH:mm:ss.ff. Розмір аналогового годинника та "
    L"годинників на панелі можна змінювати. Цифрові годинники підтримують показ секунд, "
    L"початкового нуля, вибір шрифту, кольорів, непрозорості та прозорого тла. У календарі можна "
    L"показувати номери тижнів і починати тиждень із неділі; назви відображаються мовою "
    L"віджета.\r\n\r\nБУДИЛЬНИК\r\nДля годинників і панелей можна ввімкнути будильник. Програма "
    L"сама відтворює звуковий файл один раз або безперервно, залежно від параметра повторення. "
    L"Інші файли та команди передаються Windows. Щоб зупинити індикацію будильника та звук, який "
    L"відтворює програма, клацніть його циферблат або дисплей, виберіть «Зупинити будильник» або "
    L"натисніть Esc.\r\n\r\nСПОЛУЧЕННЯ КЛАВІШ І ЗБЕРЕЖЕННЯ\r\nПодвійне клацання циферблата або "
    L"цифрового дисплея перемикає показ секунд. F1 відкриває довідку, B — налаштування, а Esc "
    L"приховує віджет, якщо не потрібно зупиняти будильник. Розташування віджетів зберігається "
    L"після перетягування, розташування діалогових вікон — під час закриття, а налаштування — у "
    L"вибраному сховищі. Повторний запуск активує вже запущений примірник програми й залишає "
    L"віджети в найближчому доступному місці робочої області.",
    L"УПРАВЛЕНИЕ\r\nПеретаскивайте часы или панель левой кнопкой мыши. Отдельный календарь "
    L"перетаскивается за свободную область. Щёлкните виджет или значок в области уведомлений "
    L"правой кнопкой мыши, чтобы открыть меню. Щелчок значка левой кнопкой скрывает видимые "
    L"виджеты; если все виджеты скрыты, восстанавливаются только те, которые были скрыты "
    L"последними.\r\n\r\nВИДЖЕТЫ И НАСТРОЙКИ\r\nВ окне «Настройки» можно добавлять, удалять и "
    L"дублировать аналоговые и цифровые часы, календари, панели календаря с часами и часы на "
    L"мониторе. Для каждого виджета отдельно задаются видимость, режим «Поверх всех окон», язык, "
    L"часовой пояс и смещение времени. Смещение вводится в формате [-]HH:mm:ss.ff. Размер "
    L"аналоговых часов и часов на панели можно менять. Цифровые часы поддерживают показ секунд, "
    L"ведущего нуля, выбор шрифта, цветов, непрозрачности и прозрачного фона. В календаре можно "
    L"показывать номера недель и начинать неделю с воскресенья; названия отображаются на языке "
    L"виджета.\r\n\r\nБУДИЛЬНИК\r\nДля часов и панелей можно включить будильник. Программа сама "
    L"воспроизводит звуковой файл один раз или непрерывно, в зависимости от параметра повтора. "
    L"Другие файлы и команды передаются Windows. Чтобы остановить индикацию будильника и звук, "
    L"который воспроизводит программа, щёлкните его циферблат или дисплей, выберите «Остановить "
    L"будильник» или нажмите Esc.\r\n\r\nСОЧЕТАНИЯ КЛАВИШ И СОХРАНЕНИЕ\r\nДвойной щелчок "
    L"циферблата или цифрового дисплея переключает показ секунд. F1 открывает справку, B — "
    L"настройки, а Esc скрывает виджет, если не требуется остановить будильник. Расположение "
    L"виджетов сохраняется после перетаскивания, расположение диалоговых окон — при закрытии, а "
    L"настройки — в выбранном хранилище. Повторный запуск активирует уже запущенный экземпляр "
    L"программы и оставляет виджеты в ближайшем доступном месте рабочей области."
};

const wchar_t* HELP_ALARM_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZADÁVÁNÍ ČASU A AKCE BUDÍKU\r\nČas budíku přijímá běžný tvar HH:mm s dvojtečkou, "
    L"tečkou, mezerou či jiným oddělovačem; oddělovač lze také vynechat. Jedna nebo dvě číslice "
    L"znamenají hodiny, tři nebo čtyři číslice hodiny a minuty, například 7, 12, 730, 0730 nebo "
    L"7:30. Po opuštění pole se čas sjednotí na HH:mm. Offset se zadává zprava od sekund: 2 "
    L"znamená 00:00:02.00, 230 i 0230 znamená 00:02:30.00 a 12345 znamená 01:23:45.00. Při "
    L"odděleném zápisu jsou dvě skupiny minuty a sekundy, tři skupiny hodiny, minuty a sekundy a "
    L"čtvrtá skupina setiny; lze použít znaménko. Dny pod volbou Budík aktivní určují, ve které "
    L"dny se budík spustí; výchozí jsou všechny dny. Jejich pořadí se řídí kulturou aplikace a "
    L"změna jazyka nemění uložené dny. Při spuštění budík zobrazí skrytý widget a přenese jej "
    L"před ostatní okna, aniž trvale změní Vždy navrchu. Volba Pípat časové znamení spustí první "
    L"krátký tón pět sekund před časem budíku. Je nezávislá na kartě Znamení; souběžné sekvence "
    L"se však sloučí. Tlačítko Vyzkoušet rozbliká aktuální ciferník či rám panelu a vyzkouší "
    L"soubor, příkaz, zvuk, HTTP/HTTPS adresu vzdáleného skriptu a při zapnuté volbě i celé "
    L"časové znamení. Zastavení testu ukončí jeho interní zvuk a náhled znamení; zastavení budíku "
    L"ukončí jeho interní zvuk. Ztlumení interní přehrávání nezastaví: pokračuje potichu a po "
    L"zrušení ztlumení je znovu slyšet. Příkazy a vzdálené skripty ztlumení "
    L"neovlivňuje.\r\n\r\nJezdec Hlasitost zvuku na kartě Budík nastavuje hlasitost interně "
    L"přehrávaného zvukového souboru pro daný widget. Výchozích −18 dB odpovídá 100 % původní "
    L"úrovně souboru. Posun doprava zvuk zesiluje; maximum 0 dB odpovídá přibližně 794 %. Hodnota "
    L"−∞ dB znamená úplné ztišení. Změny uslyšíte i během testu. Soubory MIDI a soubory, které "
    L"nelze dekódovat a přehrávají se náhradním přehrávačem, lze nastavit nejvýše na 100 %.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, "
    L"space or another separator; the separator may also be omitted. One or two digits mean "
    L"hours, while three or four digits mean hours and minutes, for example 7, 12, 730, 0730 or "
    L"7:30. The value is normalized to HH:mm after leaving the field. Offset entry starts from "
    L"seconds on the right: 2 means 00:00:02.00, 230 and 0230 mean 00:02:30.00, and 12345 means "
    L"01:23:45.00. With separators, two groups mean minutes and seconds, three mean hours, "
    L"minutes and seconds, and a fourth group contains hundredths; a sign is accepted. The days "
    L"below Alarm enabled select the weekdays on which the alarm runs; all days are selected by "
    L"default. Their order follows the application culture, and changing the language does not "
    L"change the stored weekdays. When triggered, the alarm shows a hidden widget and brings it "
    L"in front without permanently changing Always on top. Sound the time signal starts its first "
    L"short pip five seconds before the alarm. It is independent of the Signal tab, although "
    L"coincident sequences are merged. Test flashes the selected clock face or panel frame and "
    L"tests the file, command, audio, HTTP/HTTPS remote-script URL and, when selected, the "
    L"complete time-signal sequence. Stopping the test stops its internal audio and signal "
    L"preview; stopping the alarm stops its internal audio. Muting does not stop internal "
    L"playback: it continues silently and becomes audible again after unmuting. Commands and "
    L"remote scripts are unaffected.\r\n\r\nThe Audio volume slider on the Alarm tab sets the "
    L"volume of internally played audio files for that widget. The default −18 dB preserves the "
    L"original file level (100%). Moving the slider to the right amplifies the audio; the 0 dB "
    L"maximum is approximately 794%. The −∞ dB position is silence. Changes can also be heard "
    L"during a test. MIDI files and files played by a fallback player because they cannot be "
    L"decoded are limited to 100%.",
    L"\r\n\r\nZEITEINGABE UND WECKERAKTIONEN\r\nDie Weckzeit akzeptiert HH:mm mit Doppelpunkt, "
    L"Punkt, Leerzeichen oder einem anderen Trennzeichen; das Trennzeichen kann entfallen. Eine "
    L"oder zwei Ziffern bedeuten Stunden, drei oder vier Ziffern Stunden und Minuten, z. B. 7, "
    L"12, 730, 0730 oder 7:30. Beim Verlassen des Feldes wird HH:mm verwendet. Der Versatz wird "
    L"von rechts ab den Sekunden eingegeben: 2 bedeutet 00:00:02.00, 230 und 0230 bedeuten "
    L"00:02:30.00 und 12345 bedeutet 01:23:45.00. Mit Trennzeichen stehen zwei Gruppen für "
    L"Minuten und Sekunden, drei für Stunden, Minuten und Sekunden und eine vierte für "
    L"Hundertstel; ein Vorzeichen ist zulässig. Die Tage unter Wecker aktiv bestimmen, an welchen "
    L"Wochentagen der Wecker läuft; standardmäßig sind alle gewählt. Ihre Reihenfolge folgt der "
    L"Anwendungskultur; ein Sprachwechsel ändert die gespeicherten Wochentage nicht. Beim "
    L"Auslösen zeigt der Wecker ein verborgenes Widget und bringt es nach vorn, ohne Immer im "
    L"Vordergrund dauerhaft zu ändern. Akustisches Zeitzeichen startet den ersten kurzen Ton fünf "
    L"Sekunden vor dem Wecker. Diese Wahl ist von der Registerkarte Zeitzeichen unabhängig; "
    L"gleichzeitige Folgen werden jedoch zusammengeführt. Testen lässt Zifferblatt oder "
    L"Panelrahmen blinken und prüft Datei, Befehl, Audio, eine HTTP/HTTPS-Adresse eines "
    L"Remote-Skripts sowie bei aktivierter Option die vollständige Zeitzeichenfolge asynchron. "
    L"Das Stoppen des Tests beendet dessen internes Audio und die Signalvorschau; das Stoppen des "
    L"Weckers beendet sein internes Audio. Stummschalten beendet die interne Wiedergabe nicht: "
    L"Sie läuft lautlos weiter und wird nach dem Aufheben wieder hörbar. Befehle und "
    L"Remote-Skripte bleiben unberührt. Datei oder Befehl starten aktiviert Feld, Durchsuchen, "
    L"Test und Wiederholung; Test und Wiederholung erfordern zusätzlich einen nicht leeren Wert, "
    L"ein laufender Test kann jedoch immer gestoppt werden.\r\n\r\nDer Regler Audiolautstärke auf "
    L"der Registerkarte Alarm stellt die Lautstärke intern abgespielter Audiodateien für dieses "
    L"Widget ein. Der Standardwert −18 dB entspricht dem ursprünglichen Pegel der Datei (100 %). "
    L"Nach rechts wird der Ton verstärkt; das Maximum von 0 dB entspricht etwa 794 %. −∞ dB "
    L"bedeutet Stille. Änderungen sind auch während eines Tests hörbar. MIDI-Dateien und Dateien, "
    L"die nicht decodiert werden können und mit einem Ersatzplayer abgespielt werden, sind auf "
    L"100 % begrenzt.",
    L"\r\n\r\nSAISIE DE L’HEURE ET ACTIONS D’ALARME\r\nL’heure accepte HH:mm avec deux-points, "
    L"point, espace ou un autre séparateur, qui peut aussi être omis. Un ou deux chiffres "
    L"indiquent les heures, trois ou quatre les heures et les minutes, par exemple 7, 12, 730, "
    L"0730 ou 7:30. La valeur devient HH:mm à la sortie du champ. Le décalage se saisit de droite "
    L"à partir des secondes : 2 signifie 00:00:02.00, 230 et 0230 signifient 00:02:30.00, et "
    L"12345 signifie 01:23:45.00. Avec séparateurs, deux groupes représentent minutes et "
    L"secondes, trois représentent heures, minutes et secondes, et un quatrième les centièmes ; "
    L"un signe est accepté. Les jours sous Alarme active déterminent les jours où l’alarme "
    L"fonctionne ; tous sont sélectionnés par défaut. Leur ordre suit la culture de l’application "
    L"; changer de langue ne modifie pas les jours enregistrés. Lors du déclenchement, l’alarme "
    L"affiche un widget masqué et le ramène devant sans modifier durablement Toujours visible. "
    L"Émettre le signal horaire lance le premier bip court cinq secondes avant l’alarme. Ce choix "
    L"est indépendant de l’onglet Signal, mais les séquences simultanées sont fusionnées. Tester "
    L"fait clignoter le cadran ou le cadre du panneau et teste de façon le fichier, la commande, "
    L"l’audio, l’URL HTTP/HTTPS du script distant et, si l’option est activée, la séquence "
    L"complète du signal horaire. Arrêter le test coupe son audio interne et son aperçu du signal "
    L"; arrêter l’alarme coupe son audio interne. Couper le son n’arrête pas la lecture interne : "
    L"elle continue silencieusement et redevient audible après rétablissement. Les commandes et "
    L"scripts distants ne sont pas affectés. Lancer un fichier ou une commande active le champ, "
    L"Parcourir, Tester et la boucle ; Tester et la boucle exigent aussi une valeur non vide, "
    L"mais un test en cours peut toujours être arrêté.\r\n\r\nLe curseur Volume audio de l’onglet "
    L"Alarme règle le volume des fichiers audio lus en interne pour ce widget. La valeur par "
    L"défaut −18 dB correspond au niveau original du fichier (100 %). Déplacer le curseur vers la "
    L"droite amplifie le son ; le maximum de 0 dB correspond à environ 794 %. −∞ dB correspond au "
    L"silence. Les changements sont audibles pendant le test. Les fichiers MIDI et ceux lus par "
    L"un lecteur de secours faute de décodage sont limités à 100 %.",
    L"\r\n\r\nENTRADA DE HORA Y ACCIONES DE ALARMA\r\nLa hora admite HH:mm con dos puntos, punto, "
    L"espacio u otro separador, que también puede omitirse. Uno o dos dígitos indican horas; tres "
    L"o cuatro, horas y minutos, por ejemplo 7, 12, 730, 0730 o 7:30. Al salir del campo se "
    L"normaliza a HH:mm. El desfase se introduce desde la derecha empezando por los segundos: 2 "
    L"es 00:00:02.00, 230 y 0230 son 00:02:30.00, y 12345 es 01:23:45.00. Con separadores, dos "
    L"grupos son minutos y segundos, tres son horas, minutos y segundos, y un cuarto contiene "
    L"centésimas; se admite signo. Los días bajo Alarma activa determinan los días de la semana "
    L"en que funciona; todos están seleccionados de forma predeterminada. Su orden sigue la "
    L"cultura de la aplicación; cambiar el idioma no modifica los días guardados. Al activarse, "
    L"la alarma muestra un widget oculto y lo lleva al frente sin cambiar permanentemente Siempre "
    L"visible. Emitir la señal horaria inicia el primer pitido corto cinco segundos antes de la "
    L"alarma. Es independiente de la pestaña Señal, aunque las secuencias coincidentes se "
    L"combinan. Probar hace parpadear la esfera o el marco del panel y prueba de forma asíncrona "
    L"el archivo, el comando, el audio, la URL HTTP/HTTPS del script remoto y, si está activada, "
    L"la secuencia completa de la señal horaria. Detener la prueba también detiene su audio "
    L"interno y la vista previa de la señal; detener la alarma detiene su audio interno. "
    L"Silenciar no detiene la reproducción interna: continúa en silencio y vuelve a oírse al "
    L"reactivar el sonido. No afecta a comandos ni scripts remotos. Ejecutar archivo o comando "
    L"activa el campo, Examinar, Probar y la repetición; Probar y repetir también requieren un "
    L"valor no vacío, pero una prueba en curso siempre puede detenerse.\r\n\r\nEl control Volumen "
    L"de audio de la pestaña Alarma ajusta los archivos de audio reproducidos internamente para "
    L"ese widget. El valor predeterminado de −18 dB conserva el nivel original del archivo (100 "
    L"%). Hacia la derecha se amplifica el sonido; el máximo de 0 dB equivale aproximadamente al "
    L"794 %. −∞ dB es silencio. Los cambios se oyen durante la prueba. Los archivos MIDI y los "
    L"reproducidos por un reproductor alternativo al no poder decodificarse están limitados al "
    L"100 %.",
    L"\r\n\r\nIMMISSIONE DELL’ORA E AZIONI SVEGLIA\r\nL’ora accetta HH:mm con due punti, punto, "
    L"spazio o un altro separatore, che può anche essere omesso. Una o due cifre indicano le ore; "
    L"tre o quattro indicano ore e minuti, per esempio 7, 12, 730, 0730 o 7:30. Uscendo dal campo "
    L"il valore diventa HH:mm. L’offset si inserisce da destra partendo dai secondi: 2 significa "
    L"00:00:02.00, 230 e 0230 significano 00:02:30.00 e 12345 significa 01:23:45.00. Con "
    L"separatori, due gruppi sono minuti e secondi, tre sono ore, minuti e secondi e un quarto "
    L"contiene i centesimi; è ammesso il segno. I giorni sotto Sveglia attiva stabiliscono in "
    L"quali giorni suona; per impostazione predefinita sono selezionati tutti. L’ordine segue la "
    L"cultura dell’applicazione; cambiare lingua non modifica i giorni memorizzati. "
    L"All’attivazione, la sveglia mostra un widget nascosto e lo porta davanti senza cambiare in "
    L"modo permanente Sempre in primo piano. Emetti il segnale orario avvia il primo segnale "
    L"breve cinque secondi prima della sveglia. È indipendente dalla scheda Segnale, ma le "
    L"sequenze coincidenti vengono unite. Prova fa lampeggiare il quadrante o il bordo del "
    L"pannello e verifica in modo asincrono file, comando, audio, URL HTTP/HTTPS dello script "
    L"remoto e, se selezionata, l’intera sequenza del segnale orario. L’arresto della prova "
    L"interrompe il suo audio interno e l’anteprima del segnale; l’arresto della sveglia "
    L"interrompe il suo audio interno. Disattivare l’audio non ferma la riproduzione interna: "
    L"continua silenziosa e torna udibile alla riattivazione. Comandi e script remoti non sono "
    L"interessati. Esegui file o comando abilita il campo, Sfoglia, Prova e la ripetizione; Prova "
    L"e ripetizione richiedono anche un valore non vuoto, ma una prova in corso può sempre essere "
    L"interrotta.\r\n\r\nIl cursore Volume audio nella scheda Sveglia regola i file audio "
    L"riprodotti internamente per il widget. Il valore predefinito −18 dB mantiene il livello "
    L"originale del file (100%). Spostando il cursore a destra si amplifica il suono; il massimo "
    L"di 0 dB equivale a circa il 794%. −∞ dB indica il silenzio. Le modifiche si sentono durante "
    L"la prova. I file MIDI e quelli riprodotti da un lettore alternativo perché non "
    L"decodificabili sono limitati al 100%.",
    L"\r\n\r\nWPROWADZANIE CZASU I AKCJE ALARMU\r\nCzas alarmu przyjmuje HH:mm z dwukropkiem, "
    L"kropką, spacją lub innym separatorem; separator można pominąć. Jedna lub dwie cyfry "
    L"oznaczają godziny, trzy lub cztery godziny i minuty, np. 7, 12, 730, 0730 albo 7:30. Po "
    L"opuszczeniu pola wartość przyjmuje postać HH:mm. Przesunięcie wpisuje się od prawej, "
    L"zaczynając od sekund: 2 oznacza 00:00:02.00, 230 i 0230 oznaczają 00:02:30.00, a 12345 "
    L"oznacza 01:23:45.00. Przy separatorach dwie grupy oznaczają minuty i sekundy, trzy godziny, "
    L"minuty i sekundy, a czwarta setne części; znak jest dozwolony. Dni pod opcją Alarm aktywny "
    L"określają dni tygodnia działania alarmu; domyślnie zaznaczone są wszystkie. Ich kolejność "
    L"zależy od kultury aplikacji; zmiana języka nie zmienia zapisanych dni. Po uruchomieniu "
    L"alarm pokazuje ukryty widżet i przenosi go do przodu bez trwałej zmiany Zawsze na wierzchu. "
    L"Odtwarzaj sygnał czasu uruchamia pierwszy krótki sygnał pięć sekund przed alarmem. Opcja "
    L"jest niezależna od karty Sygnał, lecz zbieżne sekwencje są łączone. Test miga tarczą lub "
    L"ramką panelu i sprawdza plik, polecenie, dźwięk, adres HTTP/HTTPS zdalnego skryptu oraz, "
    L"jeśli wybrano tę opcję, pełną sekwencję sygnału czasu. Zatrzymanie testu wyłącza jego "
    L"dźwięk wewnętrzny i podgląd sygnału; zatrzymanie alarmu wyłącza jego dźwięk wewnętrzny. "
    L"Wyciszenie nie zatrzymuje odtwarzania wewnętrznego: trwa ono bezgłośnie i po włączeniu "
    L"dźwięku znów jest słyszalne. Polecenia i zdalne skrypty pozostają bez zmian.\r\n\r\nSuwak "
    L"Głośność dźwięku na karcie Alarm ustawia głośność plików audio odtwarzanych wewnętrznie dla "
    L"danego widżetu. Domyślne −18 dB odpowiada oryginalnemu poziomowi pliku (100%). Przesunięcie "
    L"w prawo wzmacnia dźwięk; maksimum 0 dB odpowiada około 794%. −∞ dB oznacza ciszę. Zmiany "
    L"słychać również podczas testu. Pliki MIDI i pliki odtwarzane przez odtwarzacz zastępczy z "
    L"powodu braku możliwości dekodowania są ograniczone do 100%.",
    L"\r\n\r\nZADÁVANIE ČASU A AKCIE BUDÍKA\r\nČas budíka prijíma HH:mm s dvojbodkou, bodkou, "
    L"medzerou alebo iným oddeľovačom; oddeľovač možno aj vynechať. Jedna alebo dve číslice "
    L"znamenajú hodiny, tri alebo štyri hodiny a minúty, napríklad 7, 12, 730, 0730 alebo 7:30. "
    L"Po opustení poľa sa hodnota upraví na HH:mm. Offset sa zadáva sprava od sekúnd: 2 znamená "
    L"00:00:02.00, 230 aj 0230 znamená 00:02:30.00 a 12345 znamená 01:23:45.00. Pri oddelenom "
    L"zápise sú dve skupiny minúty a sekundy, tri skupiny hodiny, minúty a sekundy a štvrtá "
    L"skupina stotiny; možno použiť znamienko. Dni pod voľbou Budík aktívny určujú, v ktoré dni "
    L"sa budík spustí; predvolene sú vybrané všetky. Ich poradie sa riadi kultúrou aplikácie a "
    L"zmena jazyka nemení uložené dni. Po spustení budík zobrazí skrytý widget a prenesie ho pred "
    L"ostatné okná bez trvalej zmeny Vždy navrchu. Voľba Pípať časové znamenie spustí prvý krátky "
    L"tón päť sekúnd pred časom budíka. Je nezávislá od karty Znamenie; súbežné sekvencie sa však "
    L"zlúčia. Vyskúšať rozbliká ciferník alebo rám panela a otestuje súbor, príkaz, zvuk, "
    L"HTTP/HTTPS adresu vzdialeného skriptu a pri zapnutej voľbe aj celé časové znamenie. "
    L"Zastavenie testu ukončí jeho interný zvuk a náhľad znamenia; zastavenie budíka ukončí "
    L"interný zvuk. Stlmenie interné prehrávanie nezastaví: pokračuje potichu a po zrušení "
    L"stlmenia je znovu počuť. Príkazy a vzdialené skripty stlmenie neovplyvňuje.\r\n\r\nJazdec "
    L"Hlasitosť zvuku na karte Budík nastavuje hlasitosť interne prehrávaného zvukového súboru "
    L"pre daný widget. Predvolených −18 dB zodpovedá 100 % pôvodnej úrovne súboru. Posun doprava "
    L"zvuk zosilňuje; maximum 0 dB zodpovedá približne 794 %. Hodnota −∞ dB znamená úplné "
    L"stíšenie. Zmeny počuť aj počas testu. Súbory MIDI a súbory, ktoré nemožno dekódovať a "
    L"prehrávajú sa náhradným prehrávačom, možno nastaviť najviac na 100 %.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, "
    L"space or another separator; the separator may also be omitted. One or two digits mean "
    L"hours, while three or four digits mean hours and minutes, for example 7, 12, 730, 0730 or "
    L"7:30. The value is normalised to HH:mm after leaving the field. Offset entry starts from "
    L"seconds on the right: 2 means 00:00:02.00, 230 and 0230 mean 00:02:30.00, and 12345 means "
    L"01:23:45.00. With separators, two groups mean minutes and seconds, three mean hours, "
    L"minutes and seconds, and a fourth group contains hundredths; a sign is accepted. The days "
    L"below Alarm enabled select the weekdays on which the alarm runs; all days are selected by "
    L"default. Their order follows the application culture, and changing the language does not "
    L"change the stored weekdays. When triggered, the alarm shows a hidden widget and brings it "
    L"in front without permanently changing Always on top. Sound the time signal starts its first "
    L"short pip five seconds before the alarm. It is independent of the Signal tab, although "
    L"coincident sequences are merged. Test flashes the selected clock face or panel frame and "
    L"tests the file, command, audio, HTTP/HTTPS remote-script URL and, when selected, the "
    L"complete time-signal sequence. Stopping the test stops its internal audio and signal "
    L"preview; stopping the alarm stops its internal audio. Muting does not stop internal "
    L"playback: it continues silently and becomes audible again after unmuting. Commands and "
    L"remote scripts are unaffected.\r\n\r\nThe Audio volume slider on the Alarm tab sets the "
    L"volume of internally played audio files for that widget. The default −18 dB preserves the "
    L"original file level (100%). Moving the slider to the right amplifies the audio; the 0 dB "
    L"maximum is approximately 794%. The −∞ dB position is silence. Changes can also be heard "
    L"during a test. MIDI files and files played by a fallback player because they cannot be "
    L"decoded are limited to 100%.",
    L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, period, "
    L"space or another separator; the separator may also be omitted. One or two digits mean "
    L"hours, while three or four digits mean hours and minutes, for example 7, 12, 730, 0730 or "
    L"7:30. The value is normalised to HH:mm after leaving the field. Offset entry starts from "
    L"seconds on the right: 2 means 00:00:02.00, 230 and 0230 mean 00:02:30.00, and 12345 means "
    L"01:23:45.00. With separators, two groups mean minutes and seconds, three mean hours, "
    L"minutes and seconds, and a fourth group contains hundredths; a sign is accepted. The days "
    L"below Alarm enabled select the weekdays on which the alarm runs; all days are selected by "
    L"default. Their order follows the application culture, and changing the language does not "
    L"change the stored weekdays. When triggered, the alarm shows a hidden widget and brings it "
    L"in front without permanently changing Always on top. Sound the time signal starts its first "
    L"short pip five seconds before the alarm. It is independent of the Signal tab, although "
    L"coincident sequences are merged. Test flashes the selected clock face or panel frame and "
    L"tests the file, command, audio, HTTP/HTTPS remote-script URL and, when selected, the "
    L"complete time-signal sequence. Stopping the test stops its internal audio and signal "
    L"preview; stopping the alarm stops its internal audio. Muting does not stop internal "
    L"playback: it continues silently and becomes audible again after unmuting. Commands and "
    L"remote scripts are unaffected.\r\n\r\nThe Audio volume slider on the Alarm tab sets the "
    L"volume of internally played audio files for that widget. The default −18 dB preserves the "
    L"original file level (100%). Moving the slider to the right amplifies the audio; the 0 dB "
    L"maximum is approximately 794%. The −∞ dB position is silence. Changes can also be heard "
    L"during a test. MIDI files and files played by a fallback player because they cannot be "
    L"decoded are limited to 100%.",
    L"\r\n\r\nHORA E AÇÕES DO ALARME\r\nA hora aceita HH:mm com ou sem separador: 7, 12, 730, "
    L"0730 ou 7:30. O desvio é lido da direita a partir dos segundos: 2 é 00:00:02.00, 230 é "
    L"00:02:30.00 e 12345 é 01:23:45.00. Os dias definem quando o alarme funciona e todos vêm "
    L"selecionados. A ordem segue a cultura da aplicação; mudar o idioma não altera os dias "
    L"guardados. Ao disparar, mostra um widget oculto e leva-o à frente sem alterar "
    L"permanentemente Sempre no topo. O sinal começa cinco segundos antes. Testar verifica de "
    L"forma assíncrona a indicação, o áudio, o comando e o script remoto. Silenciar não para a "
    L"reprodução interna; continua sem som e volta a ouvir-se depois. Comandos e scripts remotos "
    L"não são afetados. Executar um ficheiro ou comando ativa o campo, Procurar, Testar e a "
    L"repetição; Testar e repetir exigem também um valor não vazio, mas um teste em curso pode "
    L"sempre ser parado.\r\n\r\nO controlo Volume do áudio no separador Alarme ajusta os "
    L"ficheiros de áudio reproduzidos internamente para esse widget. O valor predefinido −18 dB "
    L"mantém o nível original do ficheiro (100%). Deslocar o controlo para a direita amplifica o "
    L"som; o máximo de 0 dB corresponde a cerca de 794%. −∞ dB é silêncio. As alterações ouvem-se "
    L"durante o teste. Os ficheiros MIDI e os reproduzidos por um leitor alternativo por não ser "
    L"possível descodificá-los estão limitados a 100%.",
    L"\r\n\r\nTIDSANGIVELSE OG ALARMHANDLINGER\r\nAlarmtid godtar HH:mm med eller uten "
    L"skilletegn: 7, 12, 730, 0730 eller 7:30. Forskyvningen leses fra høyre fra sekundene: 2 er "
    L"00:00:02.00, 230 er 00:02:30.00 og 12345 er 01:23:45.00. Dagene angir når alarmen kjører, "
    L"og alle er valgt som standard. Rekkefølgen følger programkulturen; språkbytte endrer ikke "
    L"de lagrede ukedagene. Når alarmen utløses, vises en skjult widget og bringes frem uten å "
    L"endre Alltid øverst permanent. Tidssignalet starter fem sekunder før. Test kontrollerer "
    L"indikasjon, lyd, kommando og eksternt skript asynkront. Demping stopper ikke intern "
    L"avspilling; den fortsetter lydløst og blir hørbar igjen etterpå. Kommandoer og eksterne "
    L"skript påvirkes ikke. Kjør en fil eller kommando aktiverer feltet, Bla gjennom, Test og "
    L"gjentakelse; Test og gjentakelse krever også en verdi som ikke er tom, men en pågående test "
    L"kan alltid stoppes.\r\n\r\nLydvolum på Alarm-fanen justerer internt avspilte lydfiler for "
    L"widgeten. Standardverdien −18 dB beholder filens opprinnelige nivå (100 %). Mot høyre "
    L"forsterkes lyden; maksimum 0 dB tilsvarer omtrent 794 %. −∞ dB er stillhet. Endringer høres "
    L"også under testen. MIDI-filer og filer som spilles av med en alternativ spiller fordi de "
    L"ikke kan dekodes, er begrenset til 100 %.",
    L"\r\n\r\nTIDSINMATNING OCH ALARMÅTGÄRDER\r\nAlarmtiden godtar HH:mm med eller utan "
    L"avgränsare: 7, 12, 730, 0730 eller 7:30. Förskjutningen läses från höger med sekunder "
    L"först: 2 är 00:00:02.00, 230 är 00:02:30.00 och 12345 är 01:23:45.00. Dagarna anger när "
    L"alarmet körs och alla är valda från början. Ordningen följer programkulturen; ett språkbyte "
    L"ändrar inte de sparade veckodagarna. När alarmet utlöses visas en dold widget och förs fram "
    L"utan att Alltid överst ändras permanent. Tidssignalen börjar fem sekunder före. Test provar "
    L"indikering, ljud, kommando och fjärrskript asynkront. Tystning stoppar inte intern "
    L"uppspelning; den fortsätter tyst och hörs igen efter återaktivering. Kommandon och "
    L"fjärrskript påverkas inte. Kör en fil eller ett kommando aktiverar fältet, Bläddra, Testa "
    L"och upprepning; Testa och upprepning kräver också ett värde som inte är tomt, men ett "
    L"pågående test kan alltid stoppas.\r\n\r\nLjudvolym på fliken Alarm justerar ljudfiler som "
    L"spelas internt för widgeten. Standardvärdet −18 dB behåller filens ursprungliga nivå (100 "
    L"%). Åt höger förstärks ljudet; maximum 0 dB motsvarar ungefär 794 %. −∞ dB är tystnad. "
    L"Ändringar hörs även under testet. MIDI-filer och filer som spelas upp med en reservspelare "
    L"eftersom de inte kan avkodas begränsas till 100 %.",
    L"\r\n\r\nAJAN SYÖTTÖ JA HERÄTYKSEN TOIMINNOT\r\nHerätysaika hyväksyy HH:mm-muodon "
    L"erottimella tai ilman: 7, 12, 730, 0730 tai 7:30. Poikkeama luetaan oikealta sekunneista "
    L"alkaen: 2 on 00:00:02.00, 230 on 00:02:30.00 ja 12345 on 01:23:45.00. Päivät määräävät "
    L"milloin herätys toimii; kaikki ovat oletuksena valittuina. Järjestys seuraa sovelluksen "
    L"kulttuuria, eikä kielen vaihto muuta tallennettuja viikonpäiviä. Hälytys näyttää piilotetun "
    L"pienoisohjelman ja tuo sen eteen muuttamatta pysyvästi Aina päällimmäisenä -tilaa. "
    L"Aikamerkki alkaa viisi sekuntia ennen. Testi tarkistaa ilmaisimen, äänen, komennon ja "
    L"etäkomentosarjan asynkronisesti. Mykistys ei pysäytä sisäistä toistoa; se jatkuu "
    L"äänettömänä ja kuuluu taas mykistyksen jälkeen. Komennot ja etäkomentosarjat eivät muutu. "
    L"Suorita tiedosto tai komento ottaa käyttöön kentän, Selaa-, Testaa- ja toistovalinnat; "
    L"Testaa ja toisto vaativat muun kuin tyhjän arvon, mutta käynnissä olevan testin voi aina "
    L"pysäyttää.\r\n\r\nHerätys-välilehden Äänenvoimakkuus säätää pienoisohjelman sisäisesti "
    L"toistettavien äänitiedostojen voimakkuutta. Oletusarvo −18 dB säilyttää tiedoston "
    L"alkuperäisen tason (100 %). Oikealle siirtäminen vahvistaa ääntä; enimmäisarvo 0 dB vastaa "
    L"noin 794 %:a. −∞ dB tarkoittaa hiljaisuutta. Muutokset kuuluvat myös testin aikana. "
    L"MIDI-tiedostojen ja varasoittimella toistettavien tiedostojen, joita ei voi purkaa, "
    L"enimmäistaso on 100 %.",
    L"\r\n\r\nTIDSINDTASTNING OG ALARMHANDLINGER\r\nAlarmtid accepterer HH:mm med eller uden "
    L"skilletegn: 7, 12, 730, 0730 eller 7:30. Forskydningen læses fra højre fra sekunderne: 2 er "
    L"00:00:02.00, 230 er 00:02:30.00 og 12345 er 01:23:45.00. Dagene bestemmer hvornår alarmen "
    L"kører, og alle er valgt som standard. Rækkefølgen følger programkulturen; et sprogskift "
    L"ændrer ikke de gemte ugedage. Når alarmen udløses, vises en skjult widget og føres frem "
    L"uden permanent at ændre Altid øverst. Tidssignalet starter fem sekunder før. Test afprøver "
    L"indikationen, lyd, kommando og fjernscript asynkront. Dæmpning stopper ikke intern "
    L"afspilning; den fortsætter lydløst og kan høres igen efter ophævelse. Kommandoer og "
    L"fjernscripts påvirkes ikke. Kør en fil eller kommando aktiverer feltet, Gennemse, Test og "
    L"gentagelse; Test og gentagelse kræver også en værdi, der ikke er tom, men en igangværende "
    L"test kan altid stoppes.\r\n\r\nLydstyrke på fanen Alarm justerer internt afspillede "
    L"lydfiler for widgetten. Standardværdien −18 dB bevarer filens oprindelige niveau (100 %). "
    L"Mod højre forstærkes lyden; maksimum 0 dB svarer til cirka 794 %. −∞ dB er stilhed. "
    L"Ændringer høres også under testen. MIDI-filer og filer, der afspilles med en alternativ "
    L"afspiller, fordi de ikke kan afkodes, er begrænset til 100 %.",
    L"\r\n\r\nINNSLÁTTUR TÍMA OG AÐGERÐIR VEKJARA\r\nVekjaratími tekur við HH:mm með eða án "
    L"skilmerkis: 7, 12, 730, 0730 eða 7:30. Hliðrun er lesin frá hægri frá sekúndum: 2 er "
    L"00:00:02.00, 230 er 00:02:30.00 og 12345 er 01:23:45.00. Dagarnir ákvarða hvenær vekjarinn "
    L"virkar og allir eru sjálfgefið valdir. Röðin fylgir menningu forritsins; tungumálaskipti "
    L"breyta ekki vistuðum vikudögum. Þegar vekjari fer af stað sýnir hann falda græju og færir "
    L"hana fremst án þess að breyta varanlega Alltaf efst. Tímamerkið hefst fimm sekúndum fyrr. "
    L"Prófun kannar merkingu, hljóð, skipun og fjarskriftu ósamstillt. Þöggun stöðvar ekki innri "
    L"spilun; hún heldur hljóðlaus áfram og heyrist aftur þegar þöggun er aflétt. Skipanir og "
    L"fjarskriftur breytast ekki. Keyra skrá eða skipun virkjar reitinn, Velja, Prófa og "
    L"endurtekningu; Prófa og endurtekning krefjast einnig gildis sem er ekki autt, en alltaf má "
    L"stöðva prófun sem er í gangi.\r\n\r\nHljóðstyrkur á vekjaraflipanum stillir hljóðskrár sem "
    L"forritið spilar fyrir græjuna. Sjálfgefið gildi −18 dB heldur upprunalegum styrk skrárinnar "
    L"(100%). Til hægri magnast hljóðið; hámarkið 0 dB samsvarar um 794%. −∞ dB er þögn. "
    L"Breytingar heyrast einnig meðan á prófun stendur. MIDI-skrár og skrár sem aukaspilari "
    L"spilar vegna þess að ekki er hægt að afkóða þær takmarkast við 100%.",
    L"\r\n\r\nZAMAN GİRİŞİ VE ALARM EYLEMLERİ\r\nAlarm zamanı ayırıcıyla veya ayırıcı olmadan "
    L"HH:mm kabul eder: 7, 12, 730, 0730 ya da 7:30. Ofset sağdan saniyelerden başlayarak okunur: "
    L"2 değeri 00:00:02.00, 230 değeri 00:02:30.00 ve 12345 değeri 01:23:45.00 olur. Günler "
    L"alarmın ne zaman çalışacağını belirler ve varsayılan olarak tümü seçilidir. Sıralama "
    L"uygulama kültürünü izler; dil değişikliği kayıtlı günleri değiştirmez. Alarm "
    L"tetiklendiğinde gizli aracı gösterir ve kalıcı üstte durumunu değiştirmeden öne getirir. "
    L"Zaman sinyali beş saniye önce başlar. Test; göstergeyi, sesi, komutu ve uzak betiği sınar. "
    L"Sessize alma dahili oynatmayı durdurmaz; sessizce sürer ve ses açılınca yeniden duyulur. "
    L"Komutlar ve uzak betikler etkilenmez. Dosya veya komut çalıştır; alanı, Gözat, Test ve "
    L"yinelemeyi etkinleştirir. Test ve yineleme ayrıca boş olmayan bir değer gerektirir, ancak "
    L"çalışan test her zaman durdurulabilir.\r\n\r\nAlarm sekmesindeki Ses düzeyi kaydırıcısı, "
    L"araç için dahili olarak çalınan ses dosyalarının düzeyini ayarlar. Varsayılan −18 dB, "
    L"dosyanın özgün düzeyini (%100) korur. Sağa kaydırmak sesi yükseltir; en yüksek değer olan 0 "
    L"dB yaklaşık %794 düzeyindedir. −∞ dB sessizliktir. Değişiklikler test sırasında da duyulur. "
    L"MIDI dosyaları ve çözülemediği için yedek oynatıcıyla çalınan dosyalar %100 ile sınırlıdır.",
    L"\r\n\r\nAja sisestamine ja äratuse toimingud\r\nÄratuse aeg lubab vormingut HH:mm kooloni, "
    L"punkti, tühiku või muu eraldajaga või eraldajata. Üks või kaks numbrit tähendavad tunde, "
    L"kolm või neli tunde ja minuteid: 7, 12, 730, 0730 või 7:30. Väljalt lahkumisel "
    L"teisendatakse väärtus vormingusse HH:mm. Nihet loetakse paremalt alates sekunditest: 2 "
    L"tähendab 00:00:02.00, 230 ja 0230 tähendavad 00:02:30.00 ning 12345 tähendab 01:23:45.00. "
    L"Eraldajatega tähendavad kaks rühma minuteid ja sekundeid, kolm tunde, minuteid ja sekundeid "
    L"ning neljas sajandiksekundeid; märk on lubatud. Päevad suvandi Äratus lubatud all määravad "
    L"äratuspäevad; vaikimisi on valitud kõik. Järjestus järgib rakenduse keelt, kuid keele "
    L"muutmine ei muuda salvestatud päevi.\r\n\r\nÄratus kuvab peidetud vidina ja toob selle "
    L"ette, muutmata püsivalt suvandit Alati pealmine. Esita ajasignaal alustab esimest lühikest "
    L"tooni viis sekundit enne äratust. See on vahekaardist Signaal sõltumatu; samaaegsed jadad "
    L"ühendatakse. Testi paneb sihverplaadi või raami vilkuma ja kontrollib faili, käsku, heli, "
    L"kaugskripti HTTP/HTTPS-aadressi ning valitud ajasignaali kogu jada. Testi peatamine lõpetab "
    L"selle sisemise heli ja proovisignaali; äratuse peatamine lõpetab selle sisemise heli. "
    L"Vaigistamisel esitus jätkub hääletult ja muutub vaigistuse eemaldamisel taas kuuldavaks. "
    L"Käske ja kaugskripte see ei peata.\r\n\r\nVahekaardi Äratus liugur Helitugevus määrab selle "
    L"vidina sisemise heliesituse tugevuse. Vaikimisi −18 dB säilitab faili algtaseme (100%). "
    L"Paremale liikumine võimendab heli; maksimaalne 0 dB vastab ligikaudu 794%-le. −∞ dB "
    L"tähendab vaikust. Muutus kostab ka testi ajal. MIDI ja failid, mida ei saa dekodeerida ning "
    L"esitatakse varumängijaga, on piiratud 100%-ga.",
    L"\r\n\r\nAm a iontráil agus gníomhartha aláraim\r\nGlacann am an aláraim le HH:mm, le "
    L"hidirstad, lánstad, spás nó deighilteoir eile, nó gan deighilteoir. Ciallaíonn digit nó dhó "
    L"uaireanta, agus trí nó ceithre huaireanta agus nóiméid: 7, 12, 730, 0730 nó 7:30. Déantar "
    L"HH:mm den luach nuair a fhágtar an réimse. Léitear an fritháireamh ón taobh deas, ag tosú "
    L"le soicindí: is ionann 2 agus 00:00:02.00, 230 agus 0230 agus 00:02:30.00, agus 12345 agus "
    L"01:23:45.00. Le deighilteoirí, ciallaíonn dhá ghrúpa nóiméid agus soicindí, trí ghrúpa "
    L"uaireanta, nóiméid agus soicindí, agus ceathrú grúpa céaduithe soicind; ceadaítear "
    L"comhartha. Roghnaíonn na laethanta faoi Aláram cumasaithe na laethanta gníomhacha; tá siad "
    L"uile roghnaithe ar dtús. Leanann an t-ord teanga an fheidhmchláir; ní athraíonn teanga nua "
    L"na laethanta sábháilte.\r\n\r\nTaispeánann aláram giuirléid fholaithe agus tugann sé chun "
    L"tosaigh í gan Ar barr i gcónaí a athrú go buan. Tosaíonn Seinn an comhartha ama an chéad "
    L"bhíp ghearr cúig shoicind roimh an aláram. Tá sé neamhspleách ar an gcluaisín Comhartha, "
    L"ach cumaisctear seichimh chomhuaineacha. Cuireann Tástáil aghaidh an chloig nó fráma an "
    L"phainéil ag caochadh agus seiceálann sé an comhad, an t-ordú, an fhuaim, URL HTTP/HTTPS an "
    L"chianscript agus, má roghnaítear é, an comhartha ama iomlán. Stopann Stop an tástáil an "
    L"fhuaim inmheánach agus an comhartha trialach; stopann Stop an t-aláram fuaim inmheánach an "
    L"aláraim. Leanann athsheinm ar aghaidh go ciúin nuair a bhalbhaítear é agus éiríonn sé "
    L"inchloiste arís nuair a bhaintear an balbhú. Ní stoptar orduithe ná "
    L"cianscripteanna.\r\n\r\nSocraíonn Airde na fuaime ar an gcluaisín Aláram leibhéal na "
    L"gcomhad a sheinntear go hinmheánach don ghiuirléid sin. Coinníonn an réamhshocrú −18 dB "
    L"leibhéal bunaidh an chomhaid (100%). Méadaíonn bogadh ar dheis an fhuaim; is ionann an "
    L"t-uasmhéid 0 dB agus thart ar 794%. Is tost é −∞ dB. Cloistear athruithe le linn tástála "
    L"freisin. Tá MIDI agus comhaid a sheinntear le seinnteoir cúltaca toisc nach féidir iad a "
    L"dhíchódú teoranta do 100%.",
    L"\r\n\r\nLaiko įvedimas ir žadintuvo veiksmai\r\nŽadintuvo laikas priima HH:mm su dvitaškiu, "
    L"tašku, tarpu ar kitu skirtuku arba be skirtuko. Vienas ar du skaitmenys reiškia valandas, "
    L"trys ar keturi – valandas ir minutes: 7, 12, 730, 0730 arba 7:30. Išėjus iš lauko "
    L"nustatomas HH:mm formatas. Poslinkis skaitomas iš dešinės nuo sekundžių: 2 reiškia "
    L"00:00:02.00, 230 ir 0230 – 00:02:30.00, 12345 – 01:23:45.00. Su skirtukais dvi grupės "
    L"reiškia minutes ir sekundes, trys – valandas, minutes ir sekundes, ketvirta – šimtąsias "
    L"sekundės dalis; leidžiamas ženklas. Dienos po Žadintuvas įjungtas nustato suveikimo dienas; "
    L"iš pradžių pasirinktos visos. Jų tvarka priklauso nuo programos kalbos, tačiau pakeitus "
    L"kalbą įrašytos dienos nesikeičia.\r\n\r\nŽadintuvas parodo paslėptą valdiklį ir iškelia jį "
    L"į priekį nekeisdamas Visada viršuje visam laikui. Leisti laiko signalą pradeda pirmą trumpą "
    L"toną likus penkioms sekundėms iki žadintuvo. Ši nuostata nepriklauso nuo skirtuko Signalas; "
    L"vienalaikės sekos sujungiamos. Tikrinti įjungia ciferblato arba rėmelio mirksėjimą ir "
    L"tikrina failą, komandą, garsą, nuotolinio scenarijaus HTTP/HTTPS adresą ir, jei pasirinkta, "
    L"visą laiko signalą. Sustabdžius tikrinimą nutraukiamas jo vidinis garsas ir bandomasis "
    L"signalas; sustabdžius žadintuvą – jo vidinis garsas. Nutildžius atkūrimas tęsiasi tyliai ir "
    L"vėl girdimas įjungus garsą. Komandos ir nuotoliniai scenarijai "
    L"nestabdomi.\r\n\r\nSlankiklis Garsumas skirtuke Žadintuvas valdo šio valdiklio vidinį "
    L"atkūrimą. Numatytieji −18 dB išlaiko pradinį failo lygį (100%). Slenkant dešinėn garsas "
    L"stiprinamas; didžiausi 0 dB atitinka maždaug 794%. −∞ dB reiškia tylą. Pakeitimai girdimi "
    L"ir tikrinant. MIDI ir failams, kurių negalima dekoduoti ir kurie atkuriami atsarginiu būdu, "
    L"taikoma 100% riba.",
    L"\r\n\r\nLaika ievade un modinātāja darbības\r\nModinātāja laiks pieņem HH:mm ar kolu, "
    L"punktu, atstarpi, citu atdalītāju vai bez tā. Viens vai divi cipari ir stundas, trīs vai "
    L"četri – stundas un minūtes: 7, 12, 730, 0730 vai 7:30. Atstājot lauku, vērtība kļūst par "
    L"HH:mm. Nobīdi lasa no labās puses, sākot ar sekundēm: 2 ir 00:00:02.00, 230 un 0230 ir "
    L"00:02:30.00, 12345 ir 01:23:45.00. Ar atdalītājiem divas grupas nozīmē minūtes un sekundes, "
    L"trīs – stundas, minūtes un sekundes, ceturtā – sekundes simtdaļas; atļauta zīme. Dienas zem "
    L"Modinātājs ieslēgts nosaka darbības dienas; sākumā atlasītas visas. Secība atbilst "
    L"programmas valodai, bet valodas maiņa nemaina saglabātās dienas.\r\n\r\nModinātājs parāda "
    L"paslēpto logrīku un izvirza to priekšplānā bez pastāvīgas Vienmēr virspusē maiņas. Atskaņot "
    L"laika signālu sāk pirmo īso toni piecas sekundes pirms modinātāja. Šī izvēle ir neatkarīga "
    L"no cilnes Signāls; vienlaicīgās virknes tiek apvienotas. Pārbaudīt ieslēdz ciparnīcas vai "
    L"rāmja mirgošanu un pārbauda failu, komandu, skaņu, attālā skripta HTTP/HTTPS adresi un "
    L"izvēlēto pilno laika signālu. Pārbaudes apturēšana pārtrauc tās iekšējo skaņu un "
    L"izmēģinājuma signālu; modinātāja apturēšana pārtrauc tā iekšējo skaņu. Izslēdzot skaņu, "
    L"atskaņošana turpinās nedzirdami un kļūst dzirdama pēc ieslēgšanas. Komandas un attālie "
    L"skripti netiek apturēti.\r\n\r\nSlīdnis Skaļums cilnē Modinātājs regulē šī logrīka iekšējo "
    L"atskaņošanu. Noklusējuma −18 dB saglabā faila sākotnējo līmeni (100%). Pa labi skaņa tiek "
    L"pastiprināta; lielākie 0 dB atbilst apmēram 794%. −∞ dB ir klusums. Izmaiņas dzirdamas arī "
    L"pārbaudē. MIDI un faili, kurus nevar dekodēt un atskaņo rezerves atskaņotājs, ir ierobežoti "
    L"līdz 100%.",
    L"\r\n\r\nIdőbevitel és ébresztési műveletek\r\nAz ébresztési idő HH:mm formátumú lehet "
    L"kettősponttal, ponttal, szóközzel, más elválasztóval vagy anélkül. Egy vagy két számjegy "
    L"órát, három vagy négy órát és percet jelent: 7, 12, 730, 0730 vagy 7:30. A mező "
    L"elhagyásakor HH:mm alakra vált. Az eltolást jobbról, a másodpercektől olvassa: 2 jelentése "
    L"00:00:02.00, 230 és 0230 jelentése 00:02:30.00, 12345 jelentése 01:23:45.00. Elválasztóval "
    L"két csoport percet és másodpercet, három órát, percet és másodpercet, a negyedik "
    L"századmásodpercet jelent; előjel megadható. Az Ébresztés engedélyezve alatti napok adják a "
    L"működés napjait; alapból mind kijelölt. Sorrendjük a program nyelvét követi, de a "
    L"nyelvváltás nem módosítja a mentett napokat.\r\n\r\nAz ébresztés megjeleníti a rejtett "
    L"minialkalmazást, és előtérbe hozza a Mindig felül tartós módosítása nélkül. Az Időjelzés "
    L"lejátszása az első rövid hangot öt másodperccel az ébresztés előtt indítja. Ez független az "
    L"Időjelzés fültől; az egyidejű sorozatok egyesülnek. A Tesztelés villogtatja a számlapot "
    L"vagy keretet, és ellenőrzi a fájlt, parancsot, hangot, távoli parancsfájl HTTP/HTTPS-címét "
    L"és a kiválasztott teljes időjelzést. A teszt leállítása annak belső hangját és "
    L"próbajelzését, az ébresztés leállítása annak belső hangját állítja le. Némításkor a "
    L"lejátszás hangtalanul folytatódik, feloldáskor ismét hallható. A parancsok és távoli "
    L"parancsfájlok nem állnak le.\r\n\r\nAz Ébresztés fül Hangerő csúszkája az adott "
    L"minialkalmazás belső lejátszását szabályozza. Az alapértelmezett −18 dB megőrzi a fájl "
    L"eredeti szintjét (100%). Jobbra erősíti a hangot; a legnagyobb 0 dB körülbelül 794%. A −∞ "
    L"dB csendet jelent. A változtatás teszt közben is hallható. A MIDI és a nem dekódolható, "
    L"tartalék lejátszóval kezelt fájlok legfeljebb 100%-osak.",
    L"\r\n\r\nDħul tal-ħin u azzjonijiet tal-allarm\r\nIl-ħin tal-allarm jaċċetta HH:mm b’żewġ "
    L"punti, punt, spazju jew separatur ieħor, jew mingħajr separatur. Ċifra waħda jew tnejn "
    L"ifissru sigħat; tlieta jew erbgħa sigħat u minuti: 7, 12, 730, 0730 jew 7:30. Meta titlaq "
    L"mill-qasam, il-valur isir HH:mm. Il-kumpens jinqara mil-lemin mis-sekondi: 2 ifisser "
    L"00:00:02.00, 230 u 0230 ifissru 00:02:30.00, u 12345 ifisser 01:23:45.00. B’separaturi, "
    L"żewġ gruppi jfissru minuti u sekondi, tlieta sigħat, minuti u sekondi, u r-raba’ ċentesimi "
    L"ta’ sekonda; sinjal huwa permess. Il-jiem taħt Allarm attivat jagħżlu l-jiem tal-allarm; "
    L"kollha magħżula inizjalment. L-ordni jsegwi l-lingwa tal-programm, iżda bidla fil-lingwa ma "
    L"tbiddilx il-jiem issejvjati.\r\n\r\nL-allarm juri widget moħbi u jġibu fuq quddiem mingħajr "
    L"ma jibdel Dejjem fuq nett permanentement. Daqq is-sinjal tal-ħin jibda l-ewwel ton qasir "
    L"ħames sekondi qabel l-allarm. Dan huwa indipendenti mit-tab Sinjal; sekwenzi simultanji "
    L"jingħaqdu. Ittestja jteptep il-wiċċ jew il-qafas u jittestja l-fajl, il-kmand, l-awdjo, "
    L"l-indirizz HTTP/HTTPS tal-iskript remot u, jekk magħżul, is-sinjal tal-ħin sħiħ. Il-waqfien "
    L"tat-test iwaqqaf l-awdjo intern tiegħu u s-sinjal ta’ prova; il-waqfien tal-allarm iwaqqaf "
    L"l-awdjo intern tiegħu. Meta ssikket, id-daqq ikompli fis-skiet u jerġa’ jinstema’ meta "
    L"tneħħi s-sikket. Il-kmandi u l-iskripts remoti jibqgħu attivi.\r\n\r\nIs-slajder Volum "
    L"tal-awdjo fit-tab Allarm jikkontrolla d-daqq intern ta’ dak il-widget. Id-default −18 dB "
    L"iżomm il-livell oriġinali tal-fajl (100%). Lejn il-lemin il-ħoss jiġi amplifikat; "
    L"il-massimu 0 dB huwa madwar 794%. −∞ dB huwa skiet. Il-bidliet jinstemgħu waqt it-test "
    L"ukoll. MIDI u fajls li ma jistgħux jiġu dekodifikati u jindaqqu b’metodu ta’ riżerva huma "
    L"limitati għal 100%.",
    L"\r\n\r\nTijd invoeren en alarmacties\r\nDe alarmtijd accepteert HH:mm met een dubbele punt, "
    L"punt, spatie of ander scheidingsteken, of zonder scheidingsteken. Een of twee cijfers zijn "
    L"uren, drie of vier uren en minuten: 7, 12, 730, 0730 of 7:30. Na het verlaten van het veld "
    L"wordt de waarde HH:mm. Verschuivingen worden vanaf rechts als seconden gelezen: 2 is "
    L"00:00:02.00, 230 en 0230 zijn 00:02:30.00, 12345 is 01:23:45.00. Met scheidingstekens zijn "
    L"twee groepen minuten en seconden, drie uren, minuten en seconden en een vierde honderdsten; "
    L"een teken is toegestaan. De dagen onder Alarm ingeschakeld bepalen de actieve weekdagen; "
    L"standaard zijn alle dagen gekozen. Hun volgorde volgt de toepassingstaal; taalwijziging "
    L"verandert de opgeslagen dagen niet.\r\n\r\nEen alarm toont een verborgen widget en brengt "
    L"deze naar voren zonder Altijd op voorgrond blijvend te wijzigen. Tijdsignaal afspelen "
    L"begint de eerste korte toon vijf seconden vóór het alarm. Dit staat los van het tabblad "
    L"Signaal; gelijktijdige reeksen worden samengevoegd. Testen laat de wijzerplaat of rand "
    L"knipperen en test het bestand, de opdracht, het geluid, de HTTP/HTTPS-URL van het externe "
    L"script en, indien gekozen, het volledige tijdsignaal. Test stoppen beëindigt de interne "
    L"audio en het proefsignaal van de test; het alarm stoppen beëindigt de interne alarmaudio. "
    L"Bij dempen loopt interne audio stil door en wordt na opheffen weer hoorbaar. Opdrachten en "
    L"externe scripts blijven actief.\r\n\r\nGeluidsvolume op het tabblad Alarm regelt de interne "
    L"weergave voor die widget. De standaard −18 dB behoudt het oorspronkelijke bestandsniveau "
    L"(100%). Naar rechts versterkt het geluid; het maximum van 0 dB is ongeveer 794%. −∞ dB "
    L"betekent stilte. Wijzigingen zijn ook tijdens een test hoorbaar. MIDI en bestanden die niet "
    L"gedecodeerd kunnen worden en via een alternatieve speler worden afgespeeld, zijn beperkt "
    L"tot 100%.",
    L"\r\n\r\nIntroducerea orei și acțiunile alarmei\r\nOra alarmei acceptă HH:mm cu două puncte, "
    L"punct, spațiu, alt separator sau fără separator. Una ori două cifre înseamnă ore, trei sau "
    L"patru ore și minute: 7, 12, 730, 0730 sau 7:30. La ieșirea din câmp, valoarea devine HH:mm. "
    L"Decalajul se citește de la dreapta, începând cu secundele: 2 înseamnă 00:00:02.00, 230 și "
    L"0230 înseamnă 00:02:30.00, iar 12345 înseamnă 01:23:45.00. Cu separatori, două grupuri "
    L"înseamnă minute și secunde, trei ore, minute și secunde, al patrulea sutimi; se acceptă "
    L"semn. Zilele de sub Alarmă activată stabilesc zilele de declanșare; implicit sunt selectate "
    L"toate. Ordinea urmează limba aplicației, dar schimbarea limbii nu modifică zilele "
    L"salvate.\r\n\r\nAlarma afișează widgetul ascuns și îl aduce în față fără a modifica "
    L"permanent Întotdeauna deasupra. Redare semnal orar pornește primul ton scurt cu cinci "
    L"secunde înaintea alarmei. Este independent de fila Semnal; secvențele simultane sunt "
    L"îmbinate. Testare face să clipească cadranul sau rama și verifică fișierul, comanda, "
    L"sunetul, adresa HTTP/HTTPS a scriptului la distanță și, dacă este selectat, întregul semnal "
    L"orar. Oprirea testului oprește sunetul intern și semnalul de probă ale acestuia; oprirea "
    L"alarmei oprește sunetul ei intern. Dezactivarea sunetului nu oprește redarea: aceasta "
    L"continuă în liniște și se aude din nou după reactivare. Comenzile și scripturile la "
    L"distanță nu sunt oprite.\r\n\r\nGlisorul Volum audio din fila Alarmă controlează redarea "
    L"internă a widgetului. Valoarea implicită −18 dB păstrează nivelul inițial al fișierului "
    L"(100%). Spre dreapta se amplifică sunetul; maximul de 0 dB corespunde la aproximativ 794%. "
    L"−∞ dB înseamnă liniște. Modificările se aud și în timpul testului. MIDI și fișierele care "
    L"nu pot fi decodificate și sunt redate prin metoda de rezervă sunt limitate la 100%.",
    L"\r\n\r\nΕισαγωγή ώρας και ενέργειες αφύπνισης\r\nΗ ώρα αφύπνισης δέχεται HH:mm με άνω και "
    L"κάτω τελεία, τελεία, κενό, άλλο διαχωριστικό ή χωρίς διαχωριστικό. Ένα ή δύο ψηφία είναι "
    L"ώρες, τρία ή τέσσερα ώρες και λεπτά: 7, 12, 730, 0730 ή 7:30. Με την έξοδο από το πεδίο "
    L"γίνεται HH:mm. Η μετατόπιση διαβάζεται από δεξιά, αρχίζοντας από δευτερόλεπτα: 2 σημαίνει "
    L"00:00:02.00, 230 και 0230 σημαίνουν 00:02:30.00, 12345 σημαίνει 01:23:45.00. Με "
    L"διαχωριστικά, δύο ομάδες είναι λεπτά και δευτερόλεπτα, τρεις ώρες, λεπτά και δευτερόλεπτα, "
    L"η τέταρτη εκατοστά δευτερολέπτου· επιτρέπεται πρόσημο. Οι ημέρες κάτω από Ξυπνητήρι ενεργό "
    L"ορίζουν πότε λειτουργεί· αρχικά είναι όλες επιλεγμένες. Η σειρά ακολουθεί τη γλώσσα της "
    L"εφαρμογής, αλλά η αλλαγή γλώσσας δεν αλλάζει τις αποθηκευμένες ημέρες.\r\n\r\nΤο ξυπνητήρι "
    L"εμφανίζει κρυφό στοιχείο και το φέρνει μπροστά χωρίς μόνιμη αλλαγή του Πάντα σε πρώτο "
    L"πλάνο. Η Αναπαραγωγή σήματος ώρας αρχίζει τον πρώτο σύντομο τόνο πέντε δευτερόλεπτα πριν "
    L"από την αφύπνιση. Είναι ανεξάρτητη από την καρτέλα Σήμα· οι ταυτόχρονες ακολουθίες "
    L"ενώνονται. Η Δοκιμή αναβοσβήνει το καντράν ή το περίγραμμα και ελέγχει αρχείο, εντολή, ήχο, "
    L"διεύθυνση HTTP/HTTPS απομακρυσμένου σεναρίου και, αν επιλεγεί, ολόκληρο το σήμα ώρας. Η "
    L"διακοπή δοκιμής σταματά τον εσωτερικό ήχο και το δοκιμαστικό σήμα της· η διακοπή αφύπνισης "
    L"τον εσωτερικό ήχο της αφύπνισης. Στη σίγαση η αναπαραγωγή συνεχίζεται αθόρυβα και ακούγεται "
    L"ξανά μετά την κατάργησή της. Οι εντολές και τα απομακρυσμένα σενάρια δεν "
    L"σταματούν.\r\n\r\nΗ Ένταση ήχου στην καρτέλα Ξυπνητήρι ελέγχει την εσωτερική αναπαραγωγή "
    L"αυτού του στοιχείου. Τα προεπιλεγμένα −18 dB διατηρούν το αρχικό επίπεδο του αρχείου "
    L"(100%). Προς τα δεξιά ο ήχος ενισχύεται· τα μέγιστα 0 dB αντιστοιχούν περίπου σε 794%. Το "
    L"−∞ dB είναι σιωπή. Οι αλλαγές ακούγονται και στη δοκιμή. MIDI και αρχεία που δεν "
    L"αποκωδικοποιούνται και αναπαράγονται με εφεδρική μέθοδο περιορίζονται στο 100%.",
    L"\r\n\r\nUnos vremena i radnje alarma\r\nVrijeme alarma prihvata HH:mm s dvotačkom, tačkom, "
    L"razmakom ili drugim razdjelnikom; razdjelnik se može izostaviti. Jedna ili dvije znamenke "
    L"označavaju sate, a tri ili četiri sate i minute, primjerice 7, 12, 730, 0730 ili 7:30. "
    L"Nakon napuštanja polja vrijednost se pretvara u HH:mm. Pomak se čita zdesna, počevši od "
    L"sekundi: 2 znači 00:00:02.00, 230 i 0230 znače 00:02:30.00, a 12345 znači 01:23:45.00. Uz "
    L"razdjelnike dvije skupine znače minute i sekunde, tri sate, minute i sekunde, a četvrta "
    L"sadrži stotinke; dopušten je predznak. Dani ispod opcije Alarm uključen određuju dane u "
    L"sedmici kada se alarm pokreće; podrazumijevano su odabrani svi dani. Redoslijed prati jezik "
    L"programa, a promjena jezika ne mijenja sačuvane dane. Aktivirani alarm prikazuje skriveni "
    L"vidžet i dovodi ga ispred drugih prozora bez trajne promjene postavke Uvijek na vrhu. "
    L"Reproduciraj vremenski signal pokreće prvi kratki ton pet sekundi prije vremena alarma. Ta "
    L"je opcija nezavisna o kartici Signal, ali istovremeni se nizovi spajaju. Testiraj uključuje "
    L"treperenje odabranog brojčanika ili okvira ploče i provjerava datoteku, naredbu, zvuk, "
    L"HTTP/HTTPS adresu udaljene skripte te, ako je odabrano, cijeli niz vremenskog signala. "
    L"Zaustavljanje testa prekida njegov unutrašnji zvuk i probni signal; zaustavljanje alarma "
    L"prekida njegov unutrašnji zvuk. Isključivanje zvuka ne zaustavlja reprodukciju: ona se "
    L"nastavlja nečujno i ponovno se čuje nakon uključivanja zvuka. Naredbe i udaljene skripte "
    L"ostaju aktivne.\r\n\r\nKlizač Glasnoća zvuka na kartici Alarm podešava glasnoću zvučnih "
    L"datoteka koje program reproducira za taj vidžet. Podrazumijevanih −18 dB čuva izvornu "
    L"razinu datoteke (100%). Pomicanje udesno pojačava zvuk; najvećih 0 dB odgovara približno "
    L"794%. Položaj −∞ dB znači tišinu. Promjene se čuju i tokom testa. MIDI i datoteke koje se "
    L"ne mogu dekodirati pa se reproduciraju zamjenskim načinom ograničene su na 100%.",
    L"\r\n\r\nUnos vremena i radnje alarma\r\nVrijeme alarma prihvaća HH:mm s dvotočkom, točkom, "
    L"razmakom ili drugim razdjelnikom; razdjelnik se može izostaviti. Jedna ili dvije znamenke "
    L"označavaju sate, a tri ili četiri sate i minute, primjerice 7, 12, 730, 0730 ili 7:30. "
    L"Nakon napuštanja polja vrijednost se pretvara u HH:mm. Pomak se čita zdesna, počevši od "
    L"sekundi: 2 znači 00:00:02.00, 230 i 0230 znače 00:02:30.00, a 12345 znači 01:23:45.00. Uz "
    L"razdjelnike dvije skupine znače minute i sekunde, tri sate, minute i sekunde, a četvrta "
    L"sadrži stotinke; dopušten je predznak. Dani ispod opcije Alarm uključen određuju dane u "
    L"tjednu kada se alarm pokreće; zadano su odabrani svi dani. Redoslijed prati jezik programa, "
    L"a promjena jezika ne mijenja spremljene dane. Aktivirani alarm prikazuje skriveni widget i "
    L"dovodi ga ispred drugih prozora bez trajne promjene postavke Uvijek na vrhu. Reproduciraj "
    L"vremenski signal pokreće prvi kratki ton pet sekundi prije vremena alarma. Ta je opcija "
    L"neovisna o kartici Signal, ali istodobni se nizovi spajaju. Testiraj uključuje treperenje "
    L"odabranog brojčanika ili okvira ploče i provjerava datoteku, naredbu, zvuk, HTTP/HTTPS "
    L"adresu udaljene skripte te, ako je odabrano, cijeli niz vremenskog signala. Zaustavljanje "
    L"testa prekida njegov unutarnji zvuk i probni signal; zaustavljanje alarma prekida njegov "
    L"unutarnji zvuk. Isključivanje zvuka ne zaustavlja reprodukciju: ona se nastavlja nečujno i "
    L"ponovno se čuje nakon uključivanja zvuka. Naredbe i udaljene skripte ostaju "
    L"aktivne.\r\n\r\nKlizač Glasnoća zvuka na kartici Alarm podešava glasnoću zvučnih datoteka "
    L"koje program reproducira za taj widget. Zadanih −18 dB čuva izvornu razinu datoteke (100%). "
    L"Pomicanje udesno pojačava zvuk; najvećih 0 dB odgovara približno 794%. Položaj −∞ dB znači "
    L"tišinu. Promjene se čuju i tijekom testa. MIDI i datoteke koje se ne mogu dekodirati pa se "
    L"reproduciraju zamjenskim načinom ograničene su na 100%.",
    L"\r\n\r\nVnos časa in dejanja budilke\r\nČas budilke sprejema HH:mm z dvopičjem, piko, "
    L"presledkom ali drugim ločilom, lahko tudi brez ločila. Ena ali dve števki pomenita ure, tri "
    L"ali štiri pa ure in minute: 7, 12, 730, 0730 ali 7:30. Po odhodu iz polja se vrednost "
    L"poenoti v HH:mm. Odmik se bere z desne, od sekund: 2 pomeni 00:00:02.00, 230 in 0230 "
    L"pomenita 00:02:30.00, 12345 pa 01:23:45.00. Z ločili dve skupini pomenita minute in "
    L"sekunde, tri ure, minute in sekunde, četrta pa stotinke; dovoljen je predznak. Dnevi pod "
    L"Budilka vključena določajo dneve sprožitve; privzeto so izbrani vsi. Vrstni red sledi "
    L"jeziku programa, sprememba jezika pa ne spremeni shranjenih dni. Budilka pokaže skriti "
    L"gradnik in ga postavi v ospredje brez trajne spremembe Vedno na vrhu. Predvajaj časovni "
    L"signal začne prvi kratek pisk pet sekund pred budilko. Nastavitev je neodvisna od zavihka "
    L"Signal; sočasna zaporedja se združijo. Preizkusi sproži utripanje številčnice ali okvira "
    L"ter preveri datoteko, ukaz, zvok, naslov HTTP/HTTPS oddaljenega skripta in po potrebi "
    L"celoten časovni signal. Ustavitev preizkusa ustavi njegov notranji zvok in poskusni signal; "
    L"ustavitev budilke ustavi njen notranji zvok. Izklop zvoka ne ustavi predvajanja: nadaljuje "
    L"se neslišno in po vklopu spet postane slišno. Ukazi in oddaljeni skripti niso "
    L"prizadeti.\r\n\r\nDrsnik Glasnost zvoka na zavihku Budilka uravnava notranje predvajanje za "
    L"posamezni gradnik. Privzetih −18 dB ohrani izvirno raven datoteke (100%). Pomik v desno "
    L"ojača zvok; največjih 0 dB pomeni približno 794%. −∞ dB pomeni tišino. Spremembe se slišijo "
    L"tudi med preizkusom. MIDI in datoteke, ki jih ni mogoče dekodirati in se predvajajo z "
    L"nadomestnim načinom, so omejene na 100%.",
    L"\r\n\r\nUnos vremena i radnje alarma\r\nVrijeme alarma prihvata HH:mm sa dvotačkom, tačkom, "
    L"razmakom ili drugim razdvajačem, a može i bez njega. Jedna ili dvije cifre znače sate, tri "
    L"ili četiri sate i minute: 7, 12, 730, 0730 ili 7:30. Po napuštanju polja vrijednost se "
    L"pretvara u HH:mm. Pomak se čita zdesna, počev od sekundi: 2 znači 00:00:02.00, 230 i 0230 "
    L"znače 00:02:30.00, a 12345 znači 01:23:45.00. Sa razdvajačima dvije grupe su minuti i "
    L"sekunde, tri sati, minuti i sekunde, a četvrta sadrži stotinke; dozvoljen je predznak. Dani "
    L"ispod Alarm uključen određuju dane pokretanja; podrazumijevano su izabrani svi. Redoslijed "
    L"prati jezik programa, a promjena jezika ne mijenja sačuvane dane. Alarm prikazuje skriveni "
    L"vidžet i dovodi ga ispred drugih prozora bez trajne promjene Uvijek na vrhu. Pusti "
    L"vremenski signal počinje prvi kratak ton pet sekundi prije alarma. Postavka je nezavisna od "
    L"kartice Signal; istovremene sekvence se spajaju. Testiraj uključuje treperenje brojčanika "
    L"ili okvira i provjerava datoteku, naredbu, zvuk, HTTP/HTTPS adresu udaljene skripte i, ako "
    L"je izabrano, cijeli vremenski signal. Zaustavljanje testa zaustavlja njegov unutrašnji zvuk "
    L"i probni signal; zaustavljanje alarma zaustavlja njegov unutrašnji zvuk. Isključivanje "
    L"zvuka ne prekida reprodukciju: ona se nastavlja nečujno i ponovo se čuje nakon "
    L"uključivanja. Naredbe i udaljene skripte ostaju aktivne.\r\n\r\nKlizač Jačina zvuka na "
    L"kartici Alarm podešava unutrašnju reprodukciju za taj vidžet. Podrazumijevanih −18 dB čuva "
    L"izvorni nivo datoteke (100%). Pomjeranje udesno pojačava zvuk; najvećih 0 dB odgovara "
    L"približno 794%. −∞ dB je tišina. Promjene se čuju i tokom testa. MIDI i datoteke koje ne "
    L"mogu da se dekodiraju i puštaju se rezervnim načinom ograničeni su na 100%.",
    L"\r\n\r\nУвод часу і дзеянні будзільніка\r\nЧас будзільніка прымае HH:mm з двукроп’ем, "
    L"кропкай, прабелам ці іншым раздзяляльнікам або без яго. Адна ці дзве лічбы азначаюць "
    L"гадзіны, тры ці чатыры — гадзіны і хвіліны: 7, 12, 730, 0730 або 7:30. Пасля выхаду з поля "
    L"значэнне прыводзіцца да HH:mm. Зрушэнне разбіраецца справа, пачынаючы з секунд: 2 азначае "
    L"00:00:02.00, 230 і 0230 — 00:02:30.00, а 12345 — 01:23:45.00. З раздзяляльнікамі дзве групы "
    L"азначаюць хвіліны і секунды, тры — гадзіны, хвіліны і секунды, чацвёртая — сотыя долі "
    L"секунды; дазволены знак. Дні пад сцяжком «Будзільнік уключаны» вызначаюць дні спрацоўвання; "
    L"спачатку выбраныя ўсе. Парадак адпавядае мове праграмы, але змена мовы не змяняе захаваныя "
    L"дні. Будзільнік паказвае схаваны віджэт і выводзіць яго наперад без пастаяннай змены "
    L"«Заўсёды зверху». «Прайграваць сігнал часу» пачынае першы кароткі сігнал за пяць секунд да "
    L"будзільніка. Гэта не залежыць ад укладкі «Сігнал»; адначасовыя паслядоўнасці "
    L"аб’ядноўваюцца. «Праверыць» уключае мігценне цыферблата або рамкі ды правярае файл, "
    L"каманду, гук, HTTP/HTTPS-адрас аддаленага скрыпта і, калі выбрана, поўны сігнал часу. "
    L"Спыненне тэсту спыняе яго ўнутраны гук і пробны сігнал; спыненне будзільніка спыняе яго "
    L"ўнутраны гук. Пры выключэнні гуку прайграванне працягваецца бязгучна і зноў становіцца "
    L"чутным пасля ўключэння. Каманды і аддаленыя скрыпты не закранаюцца.\r\n\r\nПаўзунок "
    L"«Гучнасць гуку» на ўкладцы «Будзільнік» задае гучнасць унутранага прайгравання для віджэта. "
    L"Прадвызначаныя −18 дБ захоўваюць зыходны ўзровень файла (100%). Рух управа ўзмацняе гук; "
    L"максімум 0 дБ адпавядае прыблізна 794%. −∞ дБ азначае цішыню. Змены чутныя і падчас тэсту. "
    L"MIDI і файлы, якія не ўдалося дэкадаваць і якія прайграюцца запасным спосабам, абмежаваныя "
    L"100%.",
    L"\r\n\r\nВъвеждане на час и действия на алармата\r\nЧасът на алармата приема HH:mm с "
    L"двоеточие, точка, интервал или друг разделител, както и без разделител. Една или две цифри "
    L"означават часове, три или четири — часове и минути: 7, 12, 730, 0730 или 7:30. При "
    L"напускане на полето стойността се преобразува в HH:mm. Отместването се чете отдясно, "
    L"започвайки от секундите: 2 означава 00:00:02.00, 230 и 0230 — 00:02:30.00, а 12345 — "
    L"01:23:45.00. С разделители две групи са минути и секунди, три — часове, минути и секунди, а "
    L"четвъртата — стотни; допуска се знак. Дните под „Алармата е включена“ определят кога се "
    L"задейства; първоначално са избрани всички дни. Редът следва езика на програмата, но смяната "
    L"на езика не променя записаните дни. Алармата показва скрития модул и го извежда отпред без "
    L"постоянна промяна на „Винаги отгоре“. „Възпроизвеждай сигнал за време“ започва първия "
    L"кратък тон пет секунди преди часа на алармата. Настройката е независима от раздела "
    L"„Сигнал“; едновременните поредици се обединяват. „Тествай“ включва мигането на циферблата "
    L"или рамката и проверява файла, командата, звука, HTTP/HTTPS адреса на отдалечения скрипт и "
    L"при избор — пълната поредица на сигнала за време. Спирането на теста прекратява неговия "
    L"вътрешен звук и пробен сигнал; спирането на алармата прекратява нейния вътрешен звук. При "
    L"изключен звук възпроизвеждането продължава беззвучно и се чува отново след включване. "
    L"Командите и отдалечените скриптове не се засягат.\r\n\r\nПлъзгачът „Сила на звука“ в "
    L"раздела „Аларма“ управлява вътрешното възпроизвеждане за този модул. Стойността по "
    L"подразбиране −18 dB запазва първоначалното ниво на файла (100%). Преместването надясно "
    L"усилва звука; максимумът 0 dB съответства на около 794%. −∞ dB означава тишина. Промените "
    L"се чуват и при тест. MIDI и файловете, които не могат да бъдат декодирани и се "
    L"възпроизвеждат по резервния начин, са ограничени до 100%.",
    L"\r\n\r\nВнесување време и дејства на алармот\r\nВремето на алармот прифаќа HH:mm со две "
    L"точки, точка, празно место или друг разделувач, како и без разделувач. Една или две цифри "
    L"значат часови, три или четири — часови и минути: 7, 12, 730, 0730 или 7:30. По напуштање на "
    L"полето вредноста се претвора во HH:mm. Поместувањето се чита оддесно, почнувајќи од "
    L"секундите: 2 значи 00:00:02.00, 230 и 0230 — 00:02:30.00, а 12345 — 01:23:45.00. Со "
    L"разделувачи две групи се минути и секунди, три се часови, минути и секунди, а четвртата "
    L"содржи стотинки; дозволен е предзнак. Деновите под „Алармот е вклучен“ ги одредуваат "
    L"деновите на активирање; стандардно се избрани сите. Редоследот го следи јазикот на "
    L"програмата, но промената на јазикот не ги менува зачуваните денови. Алармот го покажува "
    L"скриениот виџет и го носи пред другите прозорци без трајно менување на „Секогаш најгоре“. "
    L"„Пушти временски сигнал“ го почнува првиот краток тон пет секунди пред алармот. Ова е "
    L"независно од картичката „Сигнал“; истовремените низи се спојуваат. „Тестирај“ го вклучува "
    L"трепкањето на бројчаникот или рамката и ги проверува датотеката, наредбата, звукот, "
    L"HTTP/HTTPS-адресата на оддалечената скрипта и, ако е избрано, целиот временски сигнал. "
    L"Запирањето на тестот ги запира неговиот внатрешен звук и пробниот сигнал; запирањето на "
    L"алармот го запира неговиот внатрешен звук. Исклучувањето на звукот не ја запира "
    L"репродукцијата: таа продолжува нечујно и повторно се слуша по вклучување. Наредбите и "
    L"оддалечените скрипти не се засегнати.\r\n\r\nЛизгачот „Гласност на звукот“ на картичката "
    L"„Аларм“ го поставува внатрешното пуштање звук за тој виџет. Стандардните −18 dB го "
    L"зачувуваат изворното ниво на датотеката (100%). Поместувањето надесно го засилува звукот; "
    L"најголемите 0 dB одговараат на приближно 794%. −∞ dB е тишина. Промените се слушаат и за "
    L"време на тест. MIDI и датотеките што не може да се декодираат и се пуштаат со резервниот "
    L"начин се ограничени на 100%.",
    L"\r\n\r\nУнос времена и радње аларма\r\nВреме аларма прихвата HH:mm са двотачком, тачком, "
    L"размаком или другим раздвајачем, а може и без њега. Једна или две цифре значе сате, три или "
    L"четири сате и минуте: 7, 12, 730, 0730 или 7:30. По напуштању поља вредност се претвара у "
    L"HH:mm. Помак се чита здесна, почев од секунди: 2 значи 00:00:02.00, 230 и 0230 значе "
    L"00:02:30.00, а 12345 значи 01:23:45.00. Са раздвајачима две групе су минути и секунде, три "
    L"сати, минути и секунде, а четврта садржи стотинке; дозвољен је предзнак. Дани испод Аларм "
    L"укључен одређују дане покретања; подразумевано су изабрани сви. Редослед прати језик "
    L"програма, а промена језика не мења сачуване дане. Аларм приказује скривени виџет и доводи "
    L"га испред других прозора без трајне промене Увек на врху. Пусти временски сигнал почиње "
    L"први кратак тон пет секунди пре аларма. Поставка је независна од картице Сигнал; "
    L"истовремене секвенце се спајају. Тестирај укључује треперење бројчаника или оквира и "
    L"проверава датотеку, наредбу, звук, HTTP/HTTPS адресу удаљене скрипте и, ако је изабрано, "
    L"цео временски сигнал. Заустављање теста зауставља његов унутрашњи звук и пробни сигнал; "
    L"заустављање аларма зауставља његов унутрашњи звук. Искључивање звука не прекида "
    L"репродукцију: она се наставља нечујно и поново се чује након укључивања. Наредбе и удаљене "
    L"скрипте остају активне.\r\n\r\nКлизач Јачина звука на картици Аларм подешава унутрашњу "
    L"репродукцију за тај виџет. Подразумеваних −18 dB чува изворни ниво датотеке (100%). "
    L"Померање удесно појачава звук; највећих 0 dB одговара приближно 794%. −∞ dB је тишина. "
    L"Промене се чују и током теста. MIDI и датотеке које не могу да се декодирају и пуштају се "
    L"резервним начином ограничени су на 100%.",
    L"\r\n\r\nВВЕДЕННЯ ЧАСУ ТА ДІЇ БУДИЛЬНИКА\r\nЧас будильника можна вводити у форматі HH:mm із "
    L"двокрапкою, крапкою, пробілом чи іншим роздільником або без роздільника. Одна чи дві цифри "
    L"означають години, три чи чотири — години та хвилини, наприклад 7, 12, 730, 0730 або 7:30. "
    L"Після виходу з поля значення приводиться до формату HH:mm. Зсув розбирається справа наліво, "
    L"починаючи із секунд: 2 означає 00:00:02.00, 230 і 0230 — 00:02:30.00, а 12345 — "
    L"01:23:45.00. Якщо є роздільники, дві групи означають хвилини й секунди, три — години, "
    L"хвилини й секунди, а четверта містить соті частки секунди; дозволено вказувати знак. Дні "
    L"під прапорцем «Будильник увімкнено» визначають дні тижня, у які він спрацьовує; спочатку "
    L"вибрано всі дні. Їхній порядок залежить від мови програми, але зміна мови не змінює "
    L"збережених днів. Під час спрацювання прихований віджет стає видимим і виходить на передній "
    L"план без постійної зміни режиму «Завжди зверху». Параметр «Відтворювати сигнал часу» "
    L"запускає перший короткий сигнал за п’ять секунд до часу будильника. Він незалежний від "
    L"вкладки «Сигнал», але одночасні послідовності об’єднуються. Кнопка «Перевірити» вмикає "
    L"блимання вибраного циферблата або рамки панелі й перевіряє файл, команду, звук, "
    L"HTTP/HTTPS-адресу віддаленого скрипту та, якщо вибрано, повну послідовність сигналу точного "
    L"часу. Зупинення перевірки припиняє вбудоване відтворення звуку та попередній перегляд "
    L"сигналу; зупинення будильника припиняє його вбудоване відтворення. У режимі «Без звуку» "
    L"відтворення триває беззвучно й знову стає чутним після ввімкнення звуку. На команди та "
    L"віддалені скрипти цей режим не впливає.\r\n\r\nПовзунок «Гучність звуку» на вкладці "
    L"«Будильник» задає гучність звукових файлів, які програма відтворює для цього віджета. "
    L"Типове значення −18 дБ зберігає початковий рівень файлу (100%). Переміщення праворуч "
    L"підсилює звук; максимум 0 дБ відповідає приблизно 794%. Положення −∞ дБ вимикає звук. Зміни "
    L"чути й під час перевірки. Для MIDI та файлів, які не вдалося декодувати й які відтворюються "
    L"резервним програвачем, рівень обмежено 100%.",
    L"\r\n\r\nВВОД ВРЕМЕНИ И ДЕЙСТВИЯ БУДИЛЬНИКА\r\nВремя будильника можно вводить в формате HH:mm "
    L"с двоеточием, точкой, пробелом или другим разделителем либо без разделителя. Одна или две "
    L"цифры означают часы, три или четыре — часы и минуты, например 7, 12, 730, 0730 или 7:30. "
    L"После выхода из поля значение приводится к формату HH:mm. Смещение разбирается справа "
    L"налево, начиная с секунд: 2 означает 00:00:02.00, 230 и 0230 — 00:02:30.00, а 12345 — "
    L"01:23:45.00. При наличии разделителей две группы означают минуты и секунды, три — часы, "
    L"минуты и секунды, а четвёртая содержит сотые доли секунды; допускается знак. Дни под флажком "
    L"«Будильник включён» определяют дни недели, в которые он срабатывает; изначально выбраны все "
    L"дни. Их порядок зависит от языка программы, но смена языка не меняет сохранённые дни. При "
    L"срабатывании скрытый виджет становится видимым и выходит на передний план без постоянного "
    L"изменения режима «Поверх всех окон». Параметр «Воспроизводить сигнал времени» запускает "
    L"первый короткий сигнал за пять секунд до времени будильника. Он независим от вкладки "
    L"«Сигнал», но одновременные последовательности объединяются. Кнопка «Проверить» включает "
    L"мигание выбранного циферблата или рамки панели и проверяет файл, команду, звук, "
    L"HTTP/HTTPS-адрес удалённого скрипта и, если выбрано, полную последовательность сигнала "
    L"точного времени. Остановка проверки прекращает встроенное воспроизведение звука и "
    L"предварительное прослушивание сигнала; остановка будильника прекращает его встроенное "
    L"воспроизведение. В режиме «Без звука» воспроизведение продолжается беззвучно и снова "
    L"становится слышимым после включения звука. На команды и удалённые скрипты этот режим не "
    L"влияет.\r\n\r\nПолзунок «Громкость звука» на вкладке «Будильник» задаёт громкость звуковых "
    L"файлов, которые программа воспроизводит для этого виджета. Значение по умолчанию −18 дБ "
    L"сохраняет исходный уровень файла (100%). Перемещение вправо усиливает звук; максимум 0 дБ "
    L"соответствует примерно 794%. Положение −∞ дБ отключает звук. Изменения слышны и во время "
    L"проверки. Для MIDI и файлов, которые не удалось декодировать и которые воспроизводятся "
    L"резервным проигрывателем, уровень ограничен 100%."
};

const wchar_t* HELP_SELECTION_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nVÝBĚR, KLÁVESY A KOPÍROVÁNÍ DATA\r\nPři otevření Nastavení z ikony v oznamovací "
    L"oblasti se vybere naposledy zvolený widget. Nastavení si pamatuje poslední otevřenou kartu "
    L"a Přidat poslední skutečně přidaný typ. Odebrat nebo Del odstraní všechny označené položky "
    L"až po použití změn. Dvojklik položky zobrazí případně skrytý widget, nastaví Zobrazeno a "
    L"krátce jej zvýrazní. Volba Nastavení v nabídce konkrétního widgetu jej v seznamu rovnou "
    L"vybere. Kliknutí na den v kalendáři datum vybere a zkopíruje do schránky; všechny masky "
    L"jsou dostupné v každém jazyce a slovní formáty používají jazyk widgetu. Výchozí Krátké "
    L"datum se řídí jazykem widgetu. Insert přepne označení aktuální položky a posune kurzor "
    L"seznamu o řádek dolů. Ctrl+C zkopíruje označené widgety. Ctrl+V přidá kopie na konec v "
    L"pořadí seznamu s příponou názvu podle jazyka aplikace. Maximální počet widgetů je 32. Při "
    L"duplikování nebo vložení se přidají v pořadí pouze kopie, které se vejdou do limitu; na "
    L"zbývající se zobrazí upozornění. Na widgetech Ručičkové hodiny a Kalendář s hodinami "
    L"zvolíte pomocí Alt+0, Alt+1, Alt+2 nebo Alt+3 velikost hlavního ciferníku od nejmenší po "
    L"největší.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nOpening Settings from the notification-area "
    L"icon returns to the last selected widget. Settings remembers the last open tab, and Add "
    L"remembers the last type actually added. Remove or Del removes all selected items when the "
    L"changes are applied. Double-clicking an item makes a hidden widget visible, selects Visible "
    L"and identifies the widget briefly. Settings in a specific widget menu selects that widget "
    L"in the list. Clicking a calendar day selects it and copies it to the clipboard; each "
    L"calendar has its own format in Settings and its menu. Every pattern is available in every "
    L"language, while textual formats use the widget language. The default Short date follows the "
    L"widget language. Insert toggles the current item and moves the list cursor down one row. "
    L"Ctrl+C copies selected widgets. Ctrl+V appends copies in list order with a name suffix in "
    L"the application language. Up to 32 widgets are allowed. When duplicating or pasting, copies "
    L"are added in order until the limit is reached; a notification appears for the remaining "
    L"copies. Press Alt+0, Alt+1, Alt+2, or Alt+3 on an Analog clock or Calendar with clock "
    L"widget to select the main clock face size, from smallest to largest.",
    L"\r\n\r\nAUSWAHL, TASTEN UND DATUMSKOPIE\r\nBeim Öffnen der Einstellungen über das "
    L"Infobereichsymbol werden die Einstellungen des zuletzt ausgewählten Widgets angezeigt. "
    L"Einstellungen merkt sich die zuletzt geöffnete Registerkarte, Hinzufügen den zuletzt "
    L"hinzugefügten Typ. Entfernen oder Entf löscht beim Anwenden alle ausgewählten Einträge. Ein "
    L"Doppelklick macht ein verborgenes Widget sichtbar, aktiviert Sichtbar und kennzeichnet das "
    L"Widget kurz; Einstellungen im Widget-Menü wählt es in der Liste aus. Ein Klick auf einen "
    L"Kalendertag wählt und kopiert ihn im je Widget eingestellten Format. Alle Muster sind in "
    L"jeder Sprache verfügbar; Textformate verwenden die Widget-Sprache. Das voreingestellte "
    L"Kurze Datum folgt der Widget-Sprache. Einfg schaltet die Markierung des aktuellen Eintrags "
    L"um und bewegt den Listencursor eine Zeile nach unten. Strg+C kopiert ausgewählte Widgets. "
    L"Strg+V fügt Kopien in Listenreihenfolge am Ende hinzu, mit einem Namenszusatz in der "
    L"Anwendungssprache. Maximal 32 Widgets sind möglich. Beim Duplizieren oder Einfügen werden "
    L"Kopien der Reihe nach bis zum Limit hinzugefügt; für die übrigen erscheint ein Hinweis. Mit "
    L"Alt+0, Alt+1, Alt+2 oder Alt+3 wählen Sie bei Analoguhr und Kalender mit Uhr die Größe des "
    L"Hauptzifferblatts von der kleinsten bis zur größten.",
    L"\r\n\r\nSÉLECTION, TOUCHES ET COPIE DE DATE\r\nL’ouverture des paramètres depuis l’icône de "
    L"notification affiche les paramètres du dernier widget sélectionné. Paramètres mémorise le "
    L"dernier onglet ouvert et Ajouter le dernier type réellement ajouté. Supprimer ou Suppr "
    L"retire toute la sélection lors de l’application. Un double-clic rend visible un widget "
    L"masqué, coche Visible et l’identifie brièvement ; Paramètres dans son menu le sélectionne "
    L"dans la liste. Cliquer sur un jour le sélectionne et le copie selon le format propre au "
    L"calendrier. Tous les modèles sont disponibles dans chaque langue ; les formats textuels "
    L"utilisent la langue du widget. La Date courte par défaut suit la langue du widget. Inser "
    L"bascule la sélection de l’élément courant et descend le curseur de liste d’une ligne. "
    L"Ctrl+C copie les widgets sélectionnés. Ctrl+V ajoute les copies à la fin dans l’ordre de la "
    L"liste, avec un suffixe dans la langue de l’application. Le nombre de widgets est limité à "
    L"32. Lors de la duplication ou du collage, les copies sont ajoutées dans l’ordre jusqu’à la "
    L"limite ; un message signale les copies restantes. Appuyez sur Alt+0, Alt+1, Alt+2 ou Alt+3 "
    L"dans les widgets Horloge analogique et Calendrier avec horloge pour choisir la taille du "
    L"cadran principal, de la plus petite à la plus grande.",
    L"\r\n\r\nSELECCIÓN, TECLAS Y COPIA DE FECHA\r\nAl abrir Configuración desde el icono del "
    L"área de notificación, se selecciona el último widget elegido. Configuración recuerda la "
    L"última pestaña abierta y Añadir el último tipo realmente añadido. Quitar o Supr elimina "
    L"todos los seleccionados al aplicar los cambios. Un doble clic muestra un widget oculto, "
    L"activa Visible y lo identifica brevemente; Configuración en su menú lo selecciona en la "
    L"lista. Pulsar un día lo selecciona y copia según el formato propio del calendario; los "
    L"formatos de texto usan el idioma del widget. Todos los patrones están disponibles en "
    L"cualquier idioma y la Fecha corta predeterminada sigue el idioma del widget. Insert alterna "
    L"la selección del elemento actual y baja el cursor de la lista una fila. Ctrl+C copia los "
    L"widgets seleccionados. Ctrl+V añade las copias al final en el orden de la lista, con un "
    L"sufijo en el idioma de la aplicación. Se permiten hasta 32 widgets. Al duplicar o pegar, "
    L"las copias se añaden en orden hasta alcanzar el límite; se muestra un aviso para las "
    L"restantes. Pulse Alt+0, Alt+1, Alt+2 o Alt+3 en Reloj analógico o Calendario con reloj para "
    L"elegir el tamaño de la esfera principal, del menor al mayor.",
    L"\r\n\r\nSELEZIONE, TASTI E COPIA DELLA DATA\r\nAprendo le impostazioni dall’icona nell’area "
    L"di notifica, viene selezionato l’ultimo widget scelto. Impostazioni ricorda l’ultima scheda "
    L"aperta e Aggiungi l’ultimo tipo realmente aggiunto. Rimuovi o Canc elimina tutti gli "
    L"elementi selezionati quando si applicano le modifiche. Un doppio clic rende visibile un "
    L"widget nascosto, seleziona Visibile e lo identifica brevemente; Impostazioni nel suo menu "
    L"lo seleziona nell’elenco. Il clic su un giorno lo seleziona e lo copia nel formato del "
    L"calendario; i formati testuali usano la lingua del widget. Tutti i modelli sono disponibili "
    L"in ogni lingua e la Data breve predefinita segue la lingua del widget. Ins commuta la "
    L"selezione dell’elemento corrente e sposta il cursore dell’elenco una riga in basso. Ctrl+C "
    L"copia i widget selezionati. Ctrl+V aggiunge le copie in fondo nell’ordine dell’elenco, con "
    L"un suffisso nella lingua dell’applicazione. Sono consentiti fino a 32 widget. Quando si "
    L"duplica o incolla, le copie vengono aggiunte in ordine fino al limite; un avviso segnala "
    L"quelle rimanenti. Premere Alt+0, Alt+1, Alt+2 o Alt+3 nei widget Orologio analogico e "
    L"Calendario con orologio per scegliere la dimensione del quadrante principale, dalla più "
    L"piccola alla più grande.",
    L"\r\n\r\nZAZNACZANIE, KLAWISZE I KOPIOWANIE DATY\r\nOtwarcie ustawień z ikony w obszarze "
    L"powiadomień przywraca ostatnio wybrany widżet. Ustawienia pamiętają ostatnio otwartą kartę, "
    L"a Dodaj ostatnio rzeczywiście dodany typ. Usuń lub Del usuwa wszystkie zaznaczone pozycje "
    L"po zastosowaniu zmian. Dwuklik pokazuje ukryty widżet, zaznacza Widoczny i krótko go "
    L"wskazuje; Ustawienia w jego menu wybierają go na liście. Kliknięcie dnia wybiera go i "
    L"kopiuje w formacie danego kalendarza. Wszystkie wzorce są dostępne w każdym języku, a "
    L"formaty słowne używają języka widżetu. Domyślna Data krótka zależy od języka widżetu. "
    L"Insert przełącza zaznaczenie bieżącej pozycji i przesuwa kursor listy o jeden wiersz w dół. "
    L"Ctrl+C kopiuje zaznaczone widżety. Ctrl+V dodaje kopie na końcu w kolejności listy, z "
    L"przyrostkiem w języku aplikacji. Dozwolone są maksymalnie 32 widżety. Podczas powielania "
    L"lub wklejania kopie są dodawane w kolejności do osiągnięcia limitu; dla pozostałych pojawia "
    L"się powiadomienie. W widżetach Zegar analogowy i Kalendarz z zegarem klawisze Alt+0, Alt+1, "
    L"Alt+2 i Alt+3 wybierają rozmiar głównej tarczy od najmniejszego do największego.",
    L"\r\n\r\nVÝBER, KLÁVESY A KOPÍROVANIE DÁTUMU\r\nNastavenia otvorené z ikony v oblasti "
    L"oznámení obnovia naposledy vybraný widget. Nastavenie si pamätá poslednú otvorenú kartu a "
    L"Pridať posledný skutočne pridaný typ. Odobrať alebo Del odstráni po použití zmien všetky "
    L"označené položky. Dvojklik zobrazí skrytý widget, začiarkne Zobrazené a krátko ho zvýrazní; "
    L"Nastavenia v jeho ponuke ho vyberú v zozname. Kliknutie na deň ho vyberie a skopíruje vo "
    L"formáte daného kalendára. Všetky masky sú dostupné v každom jazyku, slovné formáty "
    L"používajú jazyk widgetu a predvolený Krátky dátum sa riadi jazykom widgetu. Insert prepne "
    L"označenie aktuálnej položky a posunie kurzor zoznamu o riadok nižšie. Ctrl+C skopíruje "
    L"označené widgety. Ctrl+V pridá kópie na koniec v poradí zoznamu s príponou podľa jazyka "
    L"aplikácie. Maximálny počet widgetov je 32. Pri duplikovaní alebo vložení sa pridajú v "
    L"poradí iba kópie, ktoré sa zmestia do limitu; na zostávajúce sa zobrazí upozornenie. Na "
    L"widgetoch Ručičkové hodiny a Kalendár s hodinami zvolíte pomocou Alt+0, Alt+1, Alt+2 alebo "
    L"Alt+3 veľkosť hlavného ciferníka od najmenšej po najväčšiu.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nOpening Settings from the notification-area "
    L"icon returns to the last selected widget. Settings remembers the last open tab, and Add "
    L"remembers the last type actually added. Remove or Del removes all selected items when the "
    L"changes are applied. Double-clicking an item makes a hidden widget visible, selects Visible "
    L"and identifies the widget briefly. Settings in a specific widget menu selects that widget "
    L"in the list. Clicking a calendar day selects it and copies it to the clipboard; each "
    L"calendar has its own format in Settings and its menu. Every pattern is available in every "
    L"language, while textual formats use the widget language. The default Short date follows the "
    L"widget language. Insert toggles the current item and moves the list cursor down one row. "
    L"Ctrl+C copies selected widgets. Ctrl+V appends copies in list order with a name suffix in "
    L"the application language. Up to 32 widgets are allowed. When duplicating or pasting, copies "
    L"are added in order until the limit is reached; a notification appears for the remaining "
    L"copies. Press Alt+0, Alt+1, Alt+2, or Alt+3 on an Analog clock or Calendar with clock "
    L"widget to select the main clock face size, from smallest to largest.",
    L"\r\n\r\nSELECTION, KEYS AND DATE COPYING\r\nOpening Settings from the notification-area "
    L"icon returns to the last selected widget. Settings remembers the last open tab, and Add "
    L"remembers the last type actually added. Remove or Del removes all selected items when the "
    L"changes are applied. Double-clicking an item makes a hidden widget visible, selects Visible "
    L"and identifies the widget briefly. Settings in a specific widget menu selects that widget "
    L"in the list. Clicking a calendar day selects it and copies it to the clipboard; each "
    L"calendar has its own format in Settings and its menu. Every pattern is available in every "
    L"language, while textual formats use the widget language. The default Short date follows the "
    L"widget language. Insert toggles the current item and moves the list cursor down one row. "
    L"Ctrl+C copies selected widgets. Ctrl+V appends copies in list order with a name suffix in "
    L"the application language. Up to 32 widgets are allowed. When duplicating or pasting, copies "
    L"are added in order until the limit is reached; a notification appears for the remaining "
    L"copies. Press Alt+0, Alt+1, Alt+2, or Alt+3 on an Analog clock or Calendar with clock "
    L"widget to select the main clock face size, from smallest to largest.",
    L"\r\n\r\nSELEÇÃO E DATA\r\nAo abrir as definições pelo ícone da área de notificação, é "
    L"selecionado o último widget escolhido. Um clique direito e Definições seleciona o widget "
    L"correspondente. Delete remove os widgets selecionados. Um duplo clique numa entrada torna o "
    L"widget visível e realça-o brevemente. Num calendário, clicar num dia seleciona-o e copia-o "
    L"no formato escolhido; todos os formatos estão disponíveis em todos os idiomas. Insert "
    L"alterna a seleção do item atual e desloca o cursor da lista uma linha para baixo. Ctrl+C "
    L"copia os widgets selecionados. Ctrl+V acrescenta cópias no fim pela ordem da lista, com um "
    L"sufixo no idioma da aplicação. São permitidos até 32 widgets. Ao duplicar ou colar, as "
    L"cópias são acrescentadas pela ordem até ao limite; é apresentado um aviso sobre as "
    L"restantes. Prima Alt+0, Alt+1, Alt+2 ou Alt+3 nos widgets Relógio analógico e Calendário "
    L"com relógio para escolher o tamanho do mostrador principal, do menor ao maior.",
    L"\r\n\r\nVALG OG DATO\r\nNår innstillingene åpnes fra ikonet i systemstatusfeltet, velges "
    L"den sist valgte widgeten igjen. Høyreklikk og Innstillinger velger den aktuelle widgeten. "
    L"Delete fjerner valgte widgeter. Dobbeltklikk på en oppføring gjør widgeten synlig og "
    L"fremhever den kort. Klikk på en dag i kalenderen for å velge og kopiere den i valgt format; "
    L"alle formater er tilgjengelige på alle språk. Insert veksler markeringen av gjeldende "
    L"oppføring og flytter listepekeren én rad ned. Ctrl+C kopierer valgte widgeter. Ctrl+V "
    L"legger kopier nederst i listens rekkefølge med et navnetillegg på programspråket. Opptil 32 "
    L"widgeter er tillatt. Ved duplisering eller innliming legges kopier til i rekkefølge til "
    L"grensen er nådd; et varsel vises for resten. Trykk Alt+0, Alt+1, Alt+2 eller Alt+3 på "
    L"Analog klokke eller Kalender med klokke for å velge størrelsen på hovedurskiven, fra minst "
    L"til størst.",
    L"\r\n\r\nMARKERING OCH DATUM\r\nNär inställningarna öppnas från ikonen i meddelandefältet "
    L"visas inställningarna för den senast valda widgeten. Högerklick och Inställningar markerar "
    L"den aktuella widgeten. Delete tar bort markerade widgetar. Dubbelklick på en post visar "
    L"widgeten och markerar den kort. Klicka på en dag i kalendern för att välja och kopiera den "
    L"i valt format; alla format finns på alla språk. Insert växlar markeringen av den aktuella "
    L"posten och flyttar listmarkören en rad ned. Ctrl+C kopierar markerade widgetar. Ctrl+V "
    L"lägger kopior sist i listordning med ett namntillägg på programspråket. Upp till 32 "
    L"widgetar tillåts. Vid duplicering eller inklistring läggs kopior till i ordning tills "
    L"gränsen nås; ett meddelande visas för de återstående. Tryck Alt+0, Alt+1, Alt+2 eller Alt+3 "
    L"på Analog klocka eller Kalender med klocka för att välja huvudurtavlans storlek, från minst "
    L"till störst.",
    L"\r\n\r\nVALINTA JA PÄIVÄMÄÄRÄ\r\nKun asetukset avataan ilmoitusalueen kuvakkeesta, viimeksi "
    L"valittu pienoisohjelma valitaan uudelleen. Napsauta hiiren kakkospainikkeella ja valitse "
    L"Asetukset valitaksesi kyseisen pienoisohjelman. Delete poistaa valitut pienoisohjelmat. "
    L"Luettelon kaksoisnapsautus näyttää pienoisohjelman ja korostaa sen hetkeksi. "
    L"Kalenteripäivän napsautus valitsee ja kopioi sen valitussa muodossa; kaikki muodot ovat "
    L"käytettävissä kaikilla kielillä. Insert vaihtaa nykyisen kohteen valinnan ja siirtää "
    L"luettelokohdistinta yhden rivin alaspäin. Ctrl+C kopioi valitut pienoisohjelmat. Ctrl+V "
    L"lisää kopiot loppuun luettelon järjestyksessä ja liittää nimeen sovelluksen kielisen "
    L"päätteen. Pienoisohjelmia voi olla enintään 32. Monistettaessa tai liitettäessä kopiot "
    L"lisätään järjestyksessä rajaan asti; jäljelle jäävistä näytetään ilmoitus. Valitse "
    L"pääkellotaulun koko pienimmästä suurimpaan näppäimillä Alt+0, Alt+1, Alt+2 tai Alt+3 "
    L"Analoginen kello- tai Kalenteri ja kello -pienoisohjelmassa.",
    L"\r\n\r\nMARKERING OG DATO\r\nNår indstillingerne åbnes fra ikonet i meddelelsesområdet, "
    L"vælges den sidst valgte widget igen. Højreklik og Indstillinger markerer den pågældende "
    L"widget. Delete fjerner markerede widgets. Dobbeltklik på en post viser widgeten og "
    L"fremhæver den kort. Klik på en kalenderdag for at vælge og kopiere den i det valgte format; "
    L"alle formater findes på alle sprog. Insert skifter markeringen af det aktuelle element og "
    L"flytter listemarkøren én række ned. Ctrl+C kopierer markerede widgets. Ctrl+V tilføjer "
    L"kopier nederst i listens rækkefølge med et navnetillæg på programmets sprog. Der kan være "
    L"op til 32 widgets. Ved duplikering eller indsættelse tilføjes kopier i rækkefølge indtil "
    L"grænsen; en meddelelse vises for resten. Tryk Alt+0, Alt+1, Alt+2 eller Alt+3 på Analogt ur "
    L"eller Kalender med ur for at vælge hovedurskivens størrelse, fra mindst til størst.",
    L"\r\n\r\nVAL OG DAGSETNING\r\nÞegar stillingar eru opnaðar frá tákninu á tilkynningasvæðinu "
    L"er síðast valda græjan valin aftur. Hægrismellur og Stillingar velja viðkomandi græju. "
    L"Delete fjarlægir valdar græjur. Tvísmellur á færslu sýnir græjuna og auðkennir hana "
    L"stuttlega. Smelltu á dag í dagatali til að velja og afrita hann á völdu sniði; öll snið eru "
    L"tiltæk á öllum tungumálum. Insert víxlar vali núverandi færslu og færir listabendilinn eina "
    L"línu niður. Ctrl+C afritar valdar græjur. Ctrl+V bætir afritum aftast í röð listans með "
    L"viðskeyti á tungumáli forritsins. Að hámarki eru 32 græjur leyfðar. Við afritun eða límingu "
    L"er afritum bætt við í röð þar til hámarkinu er náð; tilkynning birtist um þau sem eftir "
    L"eru. Ýttu á Alt+0, Alt+1, Alt+2 eða Alt+3 á græjunum Vísaklukka og Dagatal með klukku til "
    L"að velja stærð aðalskífunnar, frá minnstu til stærstu.",
    L"\r\n\r\nSEÇİM VE TARİH\r\nAyarlar bildirim alanındaki simgeden açıldığında en son seçilen "
    L"araç yeniden seçilir. Sağ tıklayıp Ayarlar'ı seçmek ilgili aracı seçer. Delete seçili "
    L"araçları kaldırır. Listedeki bir öğeye çift tıklamak aracı görünür yapar ve kısa süre "
    L"vurgular. Takvimde bir güne tıklamak günü seçili biçimde panoya kopyalar; tüm biçimler tüm "
    L"dillerde kullanılabilir. Insert geçerli öğenin seçimini değiştirir ve liste imlecini bir "
    L"satır aşağı taşır. Ctrl+C seçili araçları kopyalar. Ctrl+V kopyaları liste sırasıyla sona "
    L"ekler ve adlarına uygulama dilinde bir ek getirir. En fazla 32 araç kullanılabilir. "
    L"Çoğaltırken veya yapıştırırken kopyalar sınıra kadar sırayla eklenir; kalan kopyalar için "
    L"bir bildirim gösterilir. Analog saat veya Saatli takvim aracında ana kadranın boyutunu "
    L"küçükten büyüğe seçmek için Alt+0, Alt+1, Alt+2 veya Alt+3 tuşlarına basın.",
    L"\r\n\r\nValimine, klahvid ja kuupäeva kopeerimine\r\nOlekuala ikoonilt seadete avamisel "
    L"taastatakse viimati valitud vidin. Sätted jätavad meelde viimase vahekaardi ja Lisa viimati "
    L"lisatud tüübi. Eemalda või Del eemaldab kõik valitud üksused muudatuste rakendamisel. "
    L"Topeltklõps üksusel kuvab peidetud vidina, märgib Nähtav ja tõstab vidina korraks esile. "
    L"Vidina menüü Sätted valib loendis selle vidina. Kalendripäeval klõpsamine valib kuupäeva ja "
    L"kopeerib selle lõikelauale. Igal kalendril on oma kopeerimisvorming sätetes ja menüüs. Kõik "
    L"33 vormingut on saadaval igas keeles; tekstilised nimetused ja vaikevalik Lühike kuupäev "
    L"järgivad vidina keelt.\r\n\r\nInsert muudab praeguse üksuse valikut ja viib loendikursori "
    L"ühe rea alla. Ctrl+C kopeerib valitud vidinad, Ctrl+V lisab koopiad loendi järjekorras ning "
    L"nimelaiendi rakenduse keeles. Lubatud on kuni 32 vidinat. Koopiad lisatakse järjekorras "
    L"piirini ja ülejäänute kohta kuvatakse teade. Alt+0, Alt+1, Alt+2 ja Alt+3 valivad "
    L"analoogkella või kalendri ja kella paneeli peamise sihverplaadi suuruse väikseimast "
    L"suurimani.",
    L"\r\n\r\nRoghnú, eochracha agus cóipeáil dátaí\r\nNuair a osclaítear na socruithe ó "
    L"dheilbhín an limistéir fógraí, roghnaítear an ghiuirléid dheireanach a roghnaíodh. "
    L"Cuimhníonn Socruithe ar an gcluaisín deireanach agus Cuir leis ar an gcineál deireanach a "
    L"cuireadh leis. Baineann Bain nó Del gach mír roghnaithe nuair a chuirtear na hathruithe i "
    L"bhfeidhm. Taispeánann déchliceáil ar mhír giuirléid fholaithe, roghnaíonn sé Infheicthe "
    L"agus aibhsíonn sé í go gairid. Roghnaíonn Socruithe i roghchlár giuirléide an ghiuirléid "
    L"sin sa liosta. Roghnaíonn cliceáil ar lá dáta agus cóipeálann sé chuig an ngearrthaisce é. "
    L"Tá formáid ar leith ag gach féilire sna Socruithe agus ina roghchlár. Tá gach ceann de na "
    L"33 formáid ar fáil i ngach teanga; leanann ainmneacha téacsúla agus Dáta gearr teanga na "
    L"giuirléide.\r\n\r\nAthraíonn Insert roghnú na míre reatha agus bogann sé cúrsóir an liosta "
    L"síos sraith amháin. Cóipeálann Ctrl+C giuirléidí roghnaithe agus cuireann Ctrl+V cóipeanna "
    L"leis in ord an liosta, le hiarmhír ainm i dteanga an fheidhmchláir. Ceadaítear suas le 32 "
    L"giuirléid. Cuirtear cóipeanna leis in ord go dtí an teorainn agus taispeántar fógra maidir "
    L"leis an gcuid eile. Roghnaíonn Alt+0, Alt+1, Alt+2 agus Alt+3 méid phríomhaghaidh an chloig "
    L"analógaigh nó an phainéil ón gceann is lú go dtí an ceann is mó.",
    L"\r\n\r\nPasirinkimas, klavišai ir datos kopijavimas\r\nAtidarius nuostatas iš pranešimų "
    L"srities piktogramos, vėl atveriamos paskutinio pasirinkto valdiklio nuostatos. Parametrai "
    L"įsimena paskutinį skirtuką, Įtraukti – paskutinį įtrauktą tipą. Pašalinti arba Del pašalina "
    L"visus pasirinktus elementus pritaikius pakeitimus. Dukart spustelėjus elementą parodomas "
    L"paslėptas valdiklis, pažymimas Matomas ir valdiklis trumpai paryškinamas. Valdiklio meniu "
    L"Parametrai pasirenka jį sąraše. Spustelėjus kalendoriaus dieną pasirenkama data ir "
    L"nukopijuojama į mainų sritį. Kiekvienas kalendorius turi atskirą formatą parametruose ir "
    L"meniu. Visi 33 formatai prieinami visomis kalbomis; tekstiniai pavadinimai ir numatytoji "
    L"Trumpoji data priklauso nuo valdiklio kalbos.\r\n\r\nInsert perjungia dabartinio elemento "
    L"pasirinkimą ir perkelia sąrašo žymeklį eilute žemyn. Ctrl+C kopijuoja valdiklius, Ctrl+V "
    L"įtraukia kopijas sąrašo tvarka su pavadinimo priesaga programos kalba. Leidžiama iki 32 "
    L"valdiklių. Kopijos įtraukiamos iš eilės iki ribos; dėl likusių parodomas pranešimas. Alt+0, "
    L"Alt+1, Alt+2 ir Alt+3 pasirenka analoginio laikrodžio arba kalendoriaus su laikrodžiu "
    L"pagrindinio ciferblato dydį nuo mažiausio iki didžiausio.",
    L"\r\n\r\nAtlase, taustiņi un datuma kopēšana\r\nAtverot iestatījumus no paziņojumu apgabala "
    L"ikonas, tiek atlasīts pēdējais izvēlētais logrīks. Iestatījumi atceras pēdējo cilni, "
    L"Pievienot – pēdējo pievienoto tipu. Noņemt vai Del noņem visas atlasītās vienības pēc "
    L"izmaiņu lietošanas. Dubultklikšķis uz vienības parāda paslēptu logrīku, atlasa Redzams un "
    L"īslaicīgi izceļ logrīku. Iestatījumi logrīka izvēlnē atlasa to sarakstā. Klikšķis uz "
    L"kalendāra dienas atlasa datumu un kopē to starpliktuvē. Katram kalendāram ir savs formāts "
    L"iestatījumos un izvēlnē. Visi 33 formāti ir pieejami jebkurā valodā; teksta nosaukumi un "
    L"noklusējuma Īsais datums atbilst logrīka valodai.\r\n\r\nInsert pārslēdz pašreizējās "
    L"vienības atlasi un pārvieto saraksta kursoru rindu uz leju. Ctrl+C kopē logrīkus, Ctrl+V "
    L"pievieno kopijas saraksta secībā ar nosaukuma sufiksu programmas valodā. Atļauti līdz 32 "
    L"logrīkiem. Kopijas pievieno secīgi līdz robežai; par atlikušajām parāda paziņojumu. Alt+0, "
    L"Alt+1, Alt+2 un Alt+3 analogajā pulkstenī vai kalendārā ar pulksteni izvēlas galvenās "
    L"ciparnīcas lielumu no mazākā līdz lielākajam.",
    L"\r\n\r\nKijelölés, billentyűk és dátummásolás\r\nAz értesítési terület ikonjáról megnyitott "
    L"beállításokban a legutóbb kiválasztott minialkalmazás beállításai jelennek meg. A "
    L"Beállítások az utolsó fület, a Hozzáadás az utoljára hozzáadott típust jegyzi meg. Az "
    L"Eltávolítás vagy Del a módosítások alkalmazásakor minden kijelölt elemet eltávolít. Dupla "
    L"kattintás megjeleníti a rejtett minialkalmazást, bejelöli a Látható értéket, és röviden "
    L"kiemeli azt. A minialkalmazás menüjének Beállítások parancsa kiválasztja azt a listában. A "
    L"naptár napjára kattintva a dátum kijelölődik és a vágólapra másolódik. Minden naptárnak "
    L"külön formátuma van a beállításokban és menüjében. Mind a 33 formátum minden nyelven "
    L"elérhető; a szöveges nevek és az alapértelmezett Rövid dátum a minialkalmazás nyelvét "
    L"követik.\r\n\r\nAz Insert átváltja az aktuális elem kijelölését, és egy sorral lejjebb "
    L"lépteti a listakurzort. A Ctrl+C másol, a Ctrl+V a lista sorrendjében illeszti hozzá a "
    L"másolatokat a program nyelvén adott névutótaggal. Legfeljebb 32 minialkalmazás lehet. A "
    L"másolatok sorrendben kerülnek be a határig, a többiről értesítés jelenik meg. Az Alt+0, "
    L"Alt+1, Alt+2 és Alt+3 analóg órán vagy naptár órával típuson a fő számlap méretét választja "
    L"ki a legkisebbtől a legnagyobbig.",
    L"\r\n\r\nGħażla, tastiera u kkupjar tad-data\r\nMeta tiftaħ is-settings mill-ikona taż-żona "
    L"tan-notifiki, jerġa’ jintgħażel l-aħħar widget magħżul. Is-Settings jiftakru l-aħħar tab "
    L"miftuħ, Żid l-aħħar tip miżjud. Neħħi jew Del ineħħi l-oġġetti magħżula meta jiġu applikati "
    L"l-bidliet. Klikk doppju fuq oġġett juri widget moħbi, jagħżel Viżibbli u jenfasizzah għal "
    L"ftit. Settings fil-menu ta’ widget jagħżel dak il-widget fil-lista. Klikk fuq jum jagħżel "
    L"id-data u jikkopjaha fil-klibbord. Kull kalendarju għandu l-format tiegħu fis-settings u "
    L"fil-menu. It-33 format kollha huma disponibbli f’kull lingwa; ismijiet testwali u Data "
    L"qasira default isegwu l-lingwa tal-widget.\r\n\r\nInsert jaqleb l-għażla tal-oġġett "
    L"kurrenti u jmexxi l-kursur tal-lista ringiela ’l isfel. Ctrl+C jikkopja l-widgets magħżula, "
    L"Ctrl+V iżid kopji fl-ordni tal-lista b’suffiss tal-isem fil-lingwa tal-programm. Il-limitu "
    L"huwa 32 widget. Il-kopji jiżdiedu fl-ordni sal-limitu u tintwera notifika għall-bqija. "
    L"Alt+0, Alt+1, Alt+2 u Alt+3 fuq arloġġ analogu jew kalendarju bl-arloġġ jagħżlu d-daqs "
    L"tal-wiċċ prinċipali mill-iżgħar sal-akbar.",
    L"\r\n\r\nSelecteren, toetsen en datums kopiëren\r\nWanneer u de instellingen opent via het "
    L"systeemvakpictogram, wordt de laatst geselecteerde widget opnieuw geselecteerd. "
    L"Instellingen onthoudt het laatste tabblad en Toevoegen het laatst toegevoegde type. "
    L"Verwijderen of Del verwijdert alle geselecteerde items zodra wijzigingen worden toegepast. "
    L"Dubbelklikken op een item toont een verborgen widget, selecteert Zichtbaar en markeert deze "
    L"kort. Instellingen in het menu van een widget selecteert die widget in de lijst. Klikken op "
    L"een kalenderdag kiest de datum en kopieert deze naar het klembord. Elke kalender heeft een "
    L"eigen indeling in Instellingen en zijn menu. Alle 33 indelingen zijn in elke taal "
    L"beschikbaar; tekstnamen en de standaard Korte datum volgen de widgettaal.\r\n\r\nInsert "
    L"schakelt de selectie van het huidige item om en verplaatst de lijstcursor één rij omlaag. "
    L"Ctrl+C kopieert widgets, Ctrl+V voegt kopieën in lijstvolgorde toe met een "
    L"naamachtervoegsel in de toepassingstaal. Er zijn maximaal 32 widgets toegestaan. Kopieën "
    L"worden op volgorde toegevoegd tot de limiet; voor de rest verschijnt een melding. Alt+0, "
    L"Alt+1, Alt+2 en Alt+3 kiezen op een analoge klok of kalender met klok de grootte van de "
    L"hoofdwijzerplaat, van klein naar groot.",
    L"\r\n\r\nSelecție, taste și copierea datei\r\nLa deschiderea setărilor din pictograma din "
    L"zona de notificare, este selectat din nou ultimul widget ales. Setări reține ultima filă, "
    L"iar Adăugare ultimul tip adăugat. Eliminare sau Del elimină toate elementele selectate când "
    L"se aplică modificările. Un dublu clic pe un element afișează widgetul ascuns, bifează "
    L"Vizibil și îl evidențiază scurt. Setări din meniul unui widget îl selectează în listă. Un "
    L"clic pe o zi selectează data și o copiază în clipboard. Fiecare calendar are propriul "
    L"format în setări și meniu. Toate cele 33 de formate sunt disponibile în orice limbă; numele "
    L"textuale și formatul implicit Dată scurtă urmează limba widgetului.\r\n\r\nInsert comută "
    L"selecția elementului curent și deplasează cursorul listei un rând în jos. Ctrl+C copiază "
    L"widgeturile, Ctrl+V adaugă copii în ordinea listei, cu un sufix al numelui în limba "
    L"aplicației. Sunt permise până la 32 de widgeturi. Copiile se adaugă în ordine până la "
    L"limită; pentru restul apare o notificare. Alt+0, Alt+1, Alt+2 și Alt+3 pe un ceas analogic "
    L"sau calendar cu ceas aleg dimensiunea cadranului principal de la cea mai mică la cea mai "
    L"mare.",
    L"\r\n\r\nΕπιλογή, πλήκτρα και αντιγραφή ημερομηνίας\r\nΤο άνοιγμα των ρυθμίσεων από το "
    L"εικονίδιο της περιοχής ειδοποιήσεων επαναφέρει το τελευταίο επιλεγμένο γραφικό στοιχείο. Οι "
    L"Ρυθμίσεις θυμούνται την τελευταία καρτέλα και η Προσθήκη τον τελευταίο τύπο που προστέθηκε. "
    L"Κατάργηση ή Del καταργεί όλα τα επιλεγμένα στοιχεία όταν εφαρμοστούν οι αλλαγές. Το διπλό "
    L"κλικ σε καταχώρηση εμφανίζει το κρυφό στοιχείο, επιλέγει Ορατό και το επισημαίνει για λίγο. "
    L"Οι Ρυθμίσεις από μενού στοιχείου το επιλέγουν στη λίστα. Το κλικ σε ημέρα επιλέγει την "
    L"ημερομηνία και την αντιγράφει στο πρόχειρο. Κάθε ημερολόγιο έχει δική του μορφή στις "
    L"ρυθμίσεις και στο μενού. Και οι 33 μορφές διατίθενται σε κάθε γλώσσα· τα ονόματα και η "
    L"προεπιλεγμένη Σύντομη ημερομηνία ακολουθούν τη γλώσσα του στοιχείου.\r\n\r\nΤο Insert "
    L"αλλάζει την επιλογή της τρέχουσας καταχώρησης και μετακινεί τον δρομέα μία γραμμή κάτω. Το "
    L"Ctrl+C αντιγράφει στοιχεία, το Ctrl+V προσθέτει αντίγραφα με τη σειρά της λίστας και "
    L"επίθημα ονόματος στη γλώσσα της εφαρμογής. Επιτρέπονται έως 32 στοιχεία. Τα αντίγραφα "
    L"προστίθενται με τη σειρά μέχρι το όριο, με ειδοποίηση για τα υπόλοιπα. Alt+0, Alt+1, Alt+2 "
    L"και Alt+3 σε αναλογικό ρολόι ή ημερολόγιο με ρολόι επιλέγουν το μέγεθος του κύριου καντράν "
    L"από το μικρότερο στο μεγαλύτερο.",
    L"\r\n\r\nOdabir, tipke i kopiranje datuma\r\nOtvaranje postavki preko ikone u području "
    L"obavijesti ponovo bira posljednji odabrani vidžet. Postavke pamte posljednju otvorenu "
    L"karticu, a Dodaj posljednju dodanu vrstu. Ukloni ili Del uklanja sve odabrane stavke nakon "
    L"primjene promjena. Dvostruki klik na stavku prikazuje skriveni vidžet, označava Vidljivo i "
    L"nakratko ističe vidžet. Postavke u meniju vidžeta odabiru taj vidžet na popisu. Klik na dan "
    L"u kalendaru odabire datum i kopira ga u međuspremnik; svaki kalendar ima vlastiti oblik u "
    L"Postavkama i meniju. Dostupna su sva 33 oblika, nezavisno o jeziku; tekstualni nazivi "
    L"koriste jezik vidžeta. Podrazumijevani Kratki datum prati jezik vidžeta. Insert mijenja "
    L"odabir trenutne stavke i pomiče pokazivač popisa jedan red niže. Ctrl+C kopira odabrane "
    L"vidžete. Ctrl+V dodaje kopije redoslijedom popisa, s nastavkom naziva na jeziku programa. "
    L"Dopuštena su najviše 32 vidžeta. Pri dupliciranju ili lijepljenju kopije se dodaju redom do "
    L"dosezanja ograničenja, a za preostale se prikazuje obavijest. Alt+0, Alt+1, Alt+2 ili Alt+3 "
    L"na analognom satu ili kalendaru sa satom odabire veličinu glavnog brojčanika od najmanje do "
    L"najveće.",
    L"\r\n\r\nOdabir, tipke i kopiranje datuma\r\nOtvaranje postavki preko ikone u području "
    L"obavijesti ponovno odabire posljednji odabrani widget. Postavke pamte posljednju otvorenu "
    L"karticu, a Dodaj posljednju dodanu vrstu. Ukloni ili Del uklanja sve odabrane stavke nakon "
    L"primjene promjena. Dvostruki klik na stavku prikazuje skriveni widget, označava Vidljivo i "
    L"nakratko ističe widget. Postavke u izborniku widgeta odabiru taj widget na popisu. Klik na "
    L"dan u kalendaru odabire datum i kopira ga u međuspremnik; svaki kalendar ima vlastiti oblik "
    L"u Postavkama i izborniku. Dostupna su sva 33 oblika, neovisno o jeziku; tekstualni nazivi "
    L"koriste jezik widgeta. Zadani Kratki datum prati jezik widgeta. Insert mijenja odabir "
    L"trenutačne stavke i pomiče pokazivač popisa jedan redak niže. Ctrl+C kopira odabrane "
    L"widgete. Ctrl+V dodaje kopije redoslijedom popisa, s nastavkom naziva na jeziku programa. "
    L"Dopuštena su najviše 32 widgeta. Pri dupliciranju ili lijepljenju kopije se dodaju redom do "
    L"dosezanja ograničenja, a za preostale se prikazuje obavijest. Alt+0, Alt+1, Alt+2 ili Alt+3 "
    L"na analognom satu ili kalendaru sa satom odabire veličinu glavnog brojčanika od najmanje do "
    L"najveće.",
    L"\r\n\r\nIzbiranje, tipke in kopiranje datuma\r\nOb odpiranju nastavitev prek ikone v "
    L"območju za obvestila je znova izbran nazadnje izbrani gradnik. Nastavitve pomnijo zadnji "
    L"odprti zavihek, Dodaj pa zadnjo dodano vrsto. Odstrani ali Del odstrani vse izbrane "
    L"elemente ob uporabi sprememb. Dvoklik elementa pokaže skriti gradnik, označi Vidno in ga na "
    L"kratko osvetli. Nastavitve v meniju gradnika izberejo ta gradnik na seznamu. Klik dneva v "
    L"koledarju izbere datum in ga kopira v odložišče. Vsak koledar ima lastno obliko v "
    L"Nastavitvah in meniju. Vseh 33 oblik je na voljo v vseh jezikih; besedilna imena in "
    L"privzeti Kratki datum sledijo jeziku gradnika. Insert preklopi izbor trenutnega elementa in "
    L"premakne kazalec seznama vrstico navzdol. Ctrl+C kopira izbrane gradnike, Ctrl+V pa doda "
    L"kopije po vrstnem redu seznama s pripono imena v jeziku programa. Dovoljenih je do 32 "
    L"gradnikov. Kopije se dodajajo po vrsti do omejitve; za preostale se prikaže obvestilo. "
    L"Alt+0, Alt+1, Alt+2 in Alt+3 na analogni uri ali koledarju z uro izberejo velikost glavne "
    L"številčnice od najmanjše do največje.",
    L"\r\n\r\nIzbor, tasteri i kopiranje datuma\r\nOtvaranje podešavanja preko ikone u oblasti za "
    L"obavještenja ponovo bira posljednji izabrani vidžet. Podešavanja pamte posljednju otvorenu "
    L"karticu, a Dodaj posljednju dodatu vrstu. Ukloni ili Del uklanja sve izabrane stavke po "
    L"primjeni promjena. Dvoklik stavke prikazuje skriveni vidžet, označava Vidljivo i nakratko "
    L"osvjetljava vidžet. Podešavanja iz menija vidžeta biraju taj vidžet u spisku. Klik na dan "
    L"kalendara bira datum i kopira ga u ostavu; svaki kalendar ima sopstveni oblik u "
    L"Podešavanjima i meniju. Sva 33 oblika su dostupna u svakom jeziku; tekstualni nazivi i "
    L"podrazumijevani Kratak datum prate jezik vidžeta. Insert prebacuje izbor trenutne stavke i "
    L"pomjera pokazivač spiska red niže. Ctrl+C kopira izabrane vidžete, Ctrl+V dodaje kopije "
    L"redom spiska sa nastavkom naziva na jeziku programa. Dozvoljena su najviše 32 vidžeta. "
    L"Kopije se dodaju redom do ograničenja, a za preostale se prikazuje obavještenje. Alt+0, "
    L"Alt+1, Alt+2 i Alt+3 na analognom satu ili kalendaru sa satom biraju veličinu glavnog "
    L"brojčanika od najmanje do najveće.",
    L"\r\n\r\nВыбар, клавішы і капіяванне даты\r\nПры адкрыцці налад праз значок у вобласці "
    L"апавяшчэнняў зноў выбіраецца апошні выбраны віджэт. «Налады» памятаюць апошнюю ўкладку, а "
    L"«Дадаць» — апошні дададзены тып. «Выдаліць» або Del выдаляе ўсе выбраныя элементы пасля "
    L"ўжывання змен. Падвойная пстрычка элемента паказвае схаваны віджэт, усталёўвае «Паказваць» "
    L"і ненадоўга падсвечвае віджэт. «Налады» ў меню віджэта выбіраюць яго ў спісе. Пстрычка дня "
    L"выбірае дату і капіюе яе ў буфер абмену; фармат задаецца асобна для календара ў наладах ці "
    L"меню. Усе 33 фарматы даступныя на ўсіх мовах; тэкставыя назвы і прадвызначаная «Кароткая "
    L"дата» адпавядаюць мове віджэта. Insert пераключае выбар бягучага элемента і перамяшчае "
    L"курсор спіса на радок уніз. Ctrl+C капіюе выбраныя віджэты, Ctrl+V дадае копіі ў парадку "
    L"спіса з суфіксам назвы на мове праграмы. Дазволена да 32 віджэтаў. Копіі дадаюцца па "
    L"парадку да мяжы, пра астатнія паказваецца апавяшчэнне. Alt+0, Alt+1, Alt+2 і Alt+3 на "
    L"аналагавым гадзінніку або календары з гадзіннікам выбіраюць памер галоўнага цыферблата ад "
    L"найменшага да найбольшага.",
    L"\r\n\r\nИзбор, клавиши и копиране на дата\r\nПри отваряне на настройките от иконата в "
    L"областта за уведомяване отново се избира последният избран модул. „Настройки“ помни "
    L"последния отворен раздел, а „Добави“ — последния добавен тип. „Премахни“ или Del премахва "
    L"всички избрани елементи при прилагане на промените. Двойното щракване върху елемент показва "
    L"скрития модул, избира „Видим“ и го осветява за кратко. „Настройки“ в менюто на модул го "
    L"избира в списъка. Щракването върху ден избира датата и я копира в клипборда; всеки календар "
    L"има собствен формат в настройките и менюто. Всичките 33 формата са достъпни на всички "
    L"езици; текстовите имена и „Кратка дата“ следват езика на модула. Insert превключва избора "
    L"на текущия елемент и премества курсора на списъка един ред надолу. Ctrl+C копира избраните "
    L"модули, а Ctrl+V добавя копия по реда на списъка с наставка на името на езика на "
    L"програмата. Допускат се до 32 модула. Копията се добавят по ред до ограничението; за "
    L"останалите се показва уведомление. Alt+0, Alt+1, Alt+2 и Alt+3 върху аналогов часовник или "
    L"календар с часовник избират размера на главния циферблат от най-малкия до най-големия.",
    L"\r\n\r\nИзбирање, копчиња и копирање датум\r\nПри отворање на поставките преку иконата во "
    L"областа за известување повторно се избира последниот избран виџет. „Поставки“ ја памети "
    L"последната картичка, а „Додај“ последниот додаден вид. „Отстрани“ или Del ги отстранува "
    L"сите избрани ставки по применување на промените. Двоен клик на ставка го покажува скриениот "
    L"виџет, избира „Видливо“ и накратко го истакнува виџетот. „Поставки“ од менито на виџетот го "
    L"избира тој виџет во списокот. Клик на ден во календар избира датум и го копира во "
    L"меморијата за копирање; секој календар има свој облик во поставките и менито. Сите 33 "
    L"облици се достапни на секој јазик; текстуалните имиња и стандардниот „Краток датум“ го "
    L"следат јазикот на виџетот. Insert го менува изборот на тековната ставка и го поместува "
    L"покажувачот на списокот ред надолу. Ctrl+C ги копира избраните виџети, а Ctrl+V додава "
    L"копии по редот на списокот со наставка на името на јазикот на програмата. Дозволени се до "
    L"32 виџети. Копиите се додаваат по ред до границата, а за останатите се прикажува "
    L"известување. Alt+0, Alt+1, Alt+2 и Alt+3 на аналоген часовник или календар со часовник ја "
    L"избираат големината на главниот бројчаник од најмала до најголема.",
    L"\r\n\r\nИзбор, тастери и копирање датума\r\nОтварање подешавања преко иконе у области за "
    L"обавештења поново бира последњи изабрани виџет. Подешавања памте последњу отворену картицу, "
    L"а Додај последњу додату врсту. Уклони или Del уклања све изабране ставке по примени "
    L"промена. Двоклик ставке приказује скривени виџет, означава Видљиво и накратко осветљава "
    L"виџет. Подешавања из менија виџета бирају тај виџет у списку. Клик на дан календара бира "
    L"датум и копира га у оставу; сваки календар има сопствени облик у Подешавањима и менију. Сва "
    L"33 облика су доступна у сваком језику; текстуални називи и подразумевани Кратак датум прате "
    L"језик виџета. Insert пребацује избор тренутне ставке и помера показивач списка ред ниже. "
    L"Ctrl+C копира изабране виџете, Ctrl+V додаје копије редом списка са наставком назива на "
    L"језику програма. Дозвољена су највише 32 виџета. Копије се додају редом до ограничења, а за "
    L"преостале се приказује обавештење. Alt+0, Alt+1, Alt+2 и Alt+3 на аналогном сату или "
    L"календару са сатом бирају величину главног бројчаника од најмање до највеће.",
    L"\r\n\r\nВИБІР, КЛАВІШІ ТА КОПІЮВАННЯ ДАТИ\r\nПід час відкриття налаштувань із піктограми в "
    L"області сповіщень знову вибирається останній вибраний віджет. Вікно «Налаштування» "
    L"запам’ятовує останню відкриту вкладку, а команда «Додати» — останній доданий тип. "
    L"«Видалити» або Del видаляє всі вибрані елементи після застосування змін. Подвійне клацання "
    L"елемента показує прихований віджет, установлює прапорець «Показувати» та коротко підсвічує "
    L"віджет. Команда «Налаштування» в меню віджета вибирає його у списку. Клацання дня календаря "
    L"вибирає дату й копіює її до буфера обміну; формат задається окремо для кожного календаря в "
    L"налаштуваннях або меню. Усі шаблони доступні всіма мовами, а текстові назви подаються мовою "
    L"віджета. Типова «Коротка дата» відповідає мові віджета. Insert перемикає вибір поточного "
    L"елемента й переміщує курсор списку на рядок униз. Ctrl+C копіює вибрані віджети. Ctrl+V "
    L"додає копії в порядку списку із суфіксом назви мовою програми. Дозволено до 32 віджетів. "
    L"Під час дублювання або вставлення копії додаються за порядком до досягнення межі; про решту "
    L"з’являється повідомлення. Alt+0, Alt+1, Alt+2 або Alt+3 на аналоговому годиннику чи "
    L"календарі з годинником вибирає розмір головного циферблата від найменшого до найбільшого.",
    L"\r\n\r\nВЫБОР, КЛАВИШИ И КОПИРОВАНИЕ ДАТЫ\r\nПри открытии настроек через значок в области "
    L"уведомлений снова выбирается последний выбранный виджет. Окно «Настройки» запоминает "
    L"последнюю открытую вкладку, а команда «Добавить» — последний добавленный тип. «Удалить» или "
    L"Del удаляет все выбранные элементы после применения изменений. Двойной щелчок элемента "
    L"показывает скрытый виджет, устанавливает флажок «Показывать» и ненадолго подсвечивает "
    L"виджет. Команда «Настройки» в меню виджета выбирает его в списке. Щелчок дня календаря "
    L"выбирает дату и копирует её в буфер обмена; формат задаётся отдельно для каждого календаря в "
    L"настройках или меню. Все шаблоны доступны на всех языках, а текстовые названия выводятся на "
    L"языке виджета. «Краткая дата», выбранная по умолчанию, соответствует языку виджета. Insert "
    L"переключает выбор текущего элемента и перемещает курсор списка на строку вниз. Ctrl+C "
    L"копирует выбранные виджеты. Ctrl+V добавляет копии в порядке списка с суффиксом названия на "
    L"языке программы. Допускается до 32 виджетов. При дублировании или вставке копии добавляются "
    L"по порядку до достижения предела; об остальных появляется уведомление. Alt+0, Alt+1, Alt+2 "
    L"или Alt+3 на аналоговых часах либо календаре с часами выбирает размер главного циферблата от "
    L"наименьшего до наибольшего."
};

const wchar_t* HELP_LAYOUT_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nROZLOŽENÍ WIDGETŮ\r\nPříkaz Zarovnat do mřížky zachová přibližné ruční rozmístění, "
    L"posune středy widgetů na nejbližší body mřížky a odstraní překrytí. V nabídce widgetu se "
    L"upraví jeho monitor, z ikony všechny monitory samostatně. Opakování rozložení nemění. "
    L"Dvojklik v Nastavení označí widget rychlým světlemodrým blikáním; budík bliká pomaleji "
    L"červeně. Vypnutí Vždy navrchu pošle widget dozadu. V panelu s kalendářem a hodinami je "
    L"horní datum odkaz na dnešek; spodní odkaz otevře klasické nastavení data a času Windows. "
    L"Je-li přichytávání zapnuté, při tažení se widget do vzdálenosti pěti pixelů přichytí k "
    L"hraně pracovní plochy. Při změně velikosti zůstane přichycený ke stejnému okraji nebo ke "
    L"stejným dvěma okrajům.\r\n\r\nV samostatném kalendáři lze řádek Dnes zapnout nebo vypnout "
    L"na kartě Vzhled i v nabídce widgetu. Přejít na dnešek vybere dnešní datum a vrátí měsíční "
    L"zobrazení. Při změně dne podle času widgetu se dnešek vybere automaticky, ale aktuální druh "
    L"zobrazení kalendáře se zachová.",
    L"\r\n\r\nWIDGET LAYOUT\r\nArrange in a grid preserves the approximate manual layout, snaps "
    L"widget centers to the nearest grid points and removes overlaps. A widget menu affects its "
    L"monitor; the notification icon applies it to every monitor separately. Repeating the "
    L"command keeps the layout stable. A Settings double-click identifies a widget with a fast "
    L"light-blue flash; an alarm flashes more slowly in red. Turning off Always on top sends the "
    L"widget to the back. In a calendar-and-clock panel, the upper link returns the calendar to "
    L"today and the lower link opens the classic Windows Date and Time settings. When edge "
    L"snapping is enabled, a dragged widget within five pixels snaps to a work-area edge. When "
    L"resized, it remains attached to the same edge or pair of edges.\r\n\r\nFor a standalone "
    L"calendar, show or hide the Today row on the Appearance tab or in the widget menu. Go to "
    L"Today selects today and returns to the month view. When the date changes according to the "
    L"widget’s time, today is selected automatically while the current calendar view is preserved.",
    L"\r\n\r\nWIDGET-ANORDNUNG\r\nIm Raster anordnen behält die ungefähre manuelle Anordnung bei, "
    L"richtet die Mittelpunkte am nächsten Rasterpunkt aus und beseitigt Überlappungen. Das "
    L"Widget-Menü wirkt auf seinen Monitor, das Symbol auf alle Monitore einzeln. Wiederholen "
    L"ändert die Anordnung nicht. Die Kennzeichnung blinkt schnell hellblau, der Alarm langsamer "
    L"rot. Das Abschalten von Immer im Vordergrund schickt das Widget nach hinten. Im "
    L"Kalender-Uhr-Panel ist das obere Datum ein Link zum heutigen Tag, der untere Link öffnet "
    L"die klassischen Windows-Einstellungen für Datum und Uhrzeit. Wenn das Einrasten aktiviert "
    L"ist, rastet ein Widget beim Ziehen innerhalb von fünf Pixeln am Rand der Arbeitsfläche ein. "
    L"Beim Ändern der Größe bleibt es am selben Rand oder an demselben Randpaar "
    L"angeheftet.\r\n\r\nBei einem einzelnen Kalender lässt sich die Heute-Zeile unter "
    L"Darstellung oder im Widget-Menü ein- und ausblenden. Zu heute wechseln wählt den heutigen "
    L"Tag und die Monatsansicht. Beim Datumswechsel gemäß der Widget-Zeit wird heute automatisch "
    L"ausgewählt; die aktuelle Kalenderansicht bleibt erhalten.",
    L"\r\n\r\nDISPOSITION\r\nAligner sur une grille conserve leur disposition manuelle "
    L"approximative, aligne leurs centres sur la grille la plus proche et supprime les "
    L"chevauchements. Le menu du widget agit sur son écran, l’icône sur chaque écran séparément. "
    L"La commande répétée reste stable. L’identification clignote rapidement en bleu clair, "
    L"l’alarme plus lentement en rouge. Désactiver Toujours visible envoie le widget à "
    L"l’arrière-plan. Dans le panneau calendrier-horloge, la date supérieure est un lien vers "
    L"aujourd’hui et le lien inférieur ouvre les paramètres classiques Date et heure de Windows. "
    L"Lorsque l’accrochage est activé, le widget déplacé s’accroche au bord de la zone de travail "
    L"à moins de cinq pixels. Lors du redimensionnement, il reste accroché au même bord ou à la "
    L"même paire de bords.\r\n\r\nPour un calendrier autonome, affichez ou masquez la ligne "
    L"Aujourd’hui dans Apparence ou dans le menu du widget. Aller à aujourd’hui sélectionne la "
    L"date du jour et revient à la vue mensuelle. Au changement de date selon l’heure du widget, "
    L"le jour courant est sélectionné automatiquement sans changer le type de vue.",
    L"\r\n\r\nDISTRIBUCIÓN\r\nAlinear en cuadrícula conserva la distribución manual aproximada, "
    L"ajusta sus centros a la cuadrícula más cercana y elimina superposiciones. El menú del "
    L"widget actúa en su monitor; el icono, en cada monitor por separado. Repetir no cambia la "
    L"distribución. La identificación parpadea rápido en azul claro y la alarma más despacio en "
    L"rojo. Desactivar Siempre visible envía el widget al fondo. En el panel de calendario y "
    L"reloj, la fecha superior es un enlace a hoy y el enlace inferior abre la configuración "
    L"clásica de Fecha y hora de Windows. Con el ajuste activado, el widget se acopla al borde "
    L"del área de trabajo al arrastrarlo a menos de cinco píxeles. Al cambiar de tamaño, "
    L"permanece acoplado al mismo borde o al mismo par de bordes.\r\n\r\nEn un calendario "
    L"independiente, muestre u oculte la fila Hoy en Apariencia o en el menú del widget. Ir a hoy "
    L"selecciona la fecha actual y vuelve a la vista mensual. Al cambiar la fecha según la hora "
    L"del widget, se selecciona automáticamente el día actual sin cambiar el tipo de vista.",
    L"\r\n\r\nDISPOSIZIONE\r\nDisponi in griglia conserva la disposizione manuale approssimativa, "
    L"allinea i centri alla griglia più vicina ed elimina le sovrapposizioni. Il menu del widget "
    L"agisce sul suo monitor, l’icona su ogni monitor separatamente. Ripetere il comando non "
    L"cambia la disposizione. L’identificazione lampeggia rapidamente in azzurro, la sveglia più "
    L"lentamente in rosso. Disattivando Sempre in primo piano il widget viene mandato dietro. Nel "
    L"pannello calendario-orologio, la data superiore è un collegamento a oggi e quello inferiore "
    L"apre le impostazioni classiche Data e ora di Windows. Se l’aggancio è attivo, durante il "
    L"trascinamento il widget si aggancia al bordo dell’area di lavoro entro cinque pixel. Quando "
    L"viene ridimensionato, resta agganciato allo stesso bordo o alla stessa coppia di "
    L"bordi.\r\n\r\nIn un calendario autonomo, mostrare o nascondere la riga Oggi in Aspetto o "
    L"nel menu del widget. Vai a oggi seleziona la data corrente e torna alla vista mensile. "
    L"Quando cambia la data secondo l’ora del widget, viene selezionato automaticamente il giorno "
    L"corrente mantenendo il tipo di vista.",
    L"\r\n\r\nUKŁAD WIDŻETÓW\r\nUłóż w siatce zachowuje przybliżony układ ręczny, przyciąga "
    L"środki widżetów do najbliższych punktów siatki i usuwa nakładanie. Menu widżetu działa na "
    L"jego monitorze, a ikona na każdym monitorze osobno. Powtórzenie nie zmienia układu. "
    L"Identyfikacja miga szybko jasnoniebiesko, alarm wolniej na czerwono. Wyłączenie Zawsze na "
    L"wierzchu wysyła widżet do tyłu. W panelu kalendarza z zegarem górna data jest odsyłaczem do "
    L"dzisiejszego dnia, a dolny odsyłacz otwiera klasyczne ustawienia daty i godziny systemu "
    L"Windows. Po włączeniu przyciągania widżet przeciągnięty na odległość najwyżej pięciu "
    L"pikseli przyciąga się do krawędzi obszaru roboczego. Po zmianie rozmiaru pozostaje "
    L"przyciągnięty do tej samej krawędzi lub pary krawędzi.\r\n\r\nW samodzielnym kalendarzu "
    L"wiersz Dzisiaj można pokazać lub ukryć na karcie Wygląd albo w menu widżetu. Przejdź do "
    L"dnia dzisiejszego wybiera bieżącą datę i widok miesiąca. Przy zmianie daty według czasu "
    L"widżetu bieżący dzień jest wybierany automatycznie, ale rodzaj widoku pozostaje bez zmian.",
    L"\r\n\r\nROZLOŽENIE WIDGETOV\r\nZarovnať do mriežky zachová približné ručné rozmiestnenie, "
    L"pritiahne stredy widgetov k najbližším bodom mriežky a odstráni prekrývanie. Ponuka widgetu "
    L"upraví jeho monitor, ikona každý monitor samostatne. Opakovanie rozloženie nemení. "
    L"Identifikácia bliká rýchlo svetlomodro, budík pomalšie načerveno. Vypnutie Vždy navrchu "
    L"pošle widget dozadu. V paneli s kalendárom a hodinami je horný dátum odkazom na dnešok; "
    L"spodný odkaz otvorí klasické nastavenie dátumu a času Windows. Ak je prichytávanie zapnuté, "
    L"pri ťahaní sa widget vo vzdialenosti najviac piatich pixelov prichytí k okraju pracovnej "
    L"plochy. Pri zmene veľkosti zostane prichytený k rovnakému okraju alebo k rovnakej dvojici "
    L"okrajov.\r\n\r\nV samostatnom kalendári možno riadok Dnes zapnúť alebo vypnúť na karte "
    L"Vzhľad aj v ponuke widgetu. Prejsť na dnešný deň vyberie dnešný dátum a obnoví mesačné "
    L"zobrazenie. Pri zmene dňa podľa času widgetu sa dnešok vyberie automaticky, ale aktuálny "
    L"druh zobrazenia sa zachová.",
    L"\r\n\r\nWIDGET LAYOUT\r\nArrange in a grid preserves the approximate manual layout, snaps "
    L"widget centres to the nearest grid points and removes overlaps. A widget menu affects its "
    L"monitor; the notification icon applies it to every monitor separately. Repeating the "
    L"command keeps the layout stable. A Settings double-click identifies a widget with a fast "
    L"light-blue flash; an alarm flashes more slowly in red. Turning off Always on top sends the "
    L"widget to the back. In a calendar-and-clock panel, the upper link returns the calendar to "
    L"today and the lower link opens the classic Windows Date and Time settings. When edge "
    L"snapping is enabled, a dragged widget within five pixels snaps to a work-area edge. When "
    L"resized, it remains attached to the same edge or pair of edges.\r\n\r\nFor a standalone "
    L"calendar, show or hide the Today row on the Appearance tab or in the widget menu. Go to "
    L"Today selects today and returns to the month view. When the date changes according to the "
    L"widget’s time, today is selected automatically while the current calendar view is preserved.",
    L"\r\n\r\nWIDGET LAYOUT\r\nArrange in a grid preserves the approximate manual layout, snaps "
    L"widget centres to the nearest grid points and removes overlaps. A widget menu affects its "
    L"monitor; the notification icon applies it to every monitor separately. Repeating the "
    L"command keeps the layout stable. A Settings double-click identifies a widget with a fast "
    L"light-blue flash; an alarm flashes more slowly in red. Turning off Always on top sends the "
    L"widget to the back. In a calendar-and-clock panel, the upper link returns the calendar to "
    L"today and the lower link opens the classic Windows Date and Time settings. When edge "
    L"snapping is enabled, a dragged widget within five pixels snaps to a work-area edge. When "
    L"resized, it remains attached to the same edge or pair of edges.\r\n\r\nFor a standalone "
    L"calendar, show or hide the Today row on the Appearance tab or in the widget menu. Go to "
    L"Today selects today and returns to the month view. When the date changes according to the "
    L"widget’s time, today is selected automatically while the current calendar view is preserved.",
    L"\r\n\r\nDISPOSIÇÃO\r\nQuando o ajuste está ativado, os widgets prendem-se às margens da "
    L"área de trabalho a cinco píxeis e permanecem presos ao redimensionar. Dispor numa grelha "
    L"move os outros widgets para posições próximas sem sobreposição, mantendo o widget de "
    L"referência no lugar. Os relógios de monitor são ignorados. No painel com calendário e "
    L"relógio, a ligação superior volta a hoje e a inferior abre as definições clássicas de Data "
    L"e Hora do Windows; ambas funcionam com rato e teclado.\r\n\r\nNum calendário autónomo, "
    L"mostre ou oculte a linha Hoje em Aspeto ou no menu do widget. Ir para hoje seleciona a data "
    L"atual e regressa à vista mensal. Quando a data muda segundo a hora do widget, o dia atual é "
    L"selecionado automaticamente, mantendo o tipo de vista.",
    L"\r\n\r\nPLASSERING\r\nNår kantfesting er aktivert, festes widgeter til kanten av "
    L"arbeidsområdet innen fem piksler og forblir festet ved størrelsesendring. Ordne i et "
    L"rutenett flytter de andre widgetene til nærliggende plasser uten overlapping, mens "
    L"referansewidgeten blir stående. Skjermklokker ignoreres. I kalender- og klokke-panelet går "
    L"den øvre lenken til i dag, og den nedre åpner de klassiske innstillingene for dato og "
    L"klokkeslett i Windows; begge virker med mus og tastatur.\r\n\r\nI en frittstående kalender "
    L"kan I dag-raden vises eller skjules på fanen Utseende eller i widgetmenyen. Gå til i dag "
    L"velger dagens dato og månedsvisningen. Når datoen endres etter widgetens tid, velges i dag "
    L"automatisk uten å endre visningstypen.",
    L"\r\n\r\nPLACERING\r\nNär kantfästning är aktiverad fäster widgetar vid arbetsytans kanter "
    L"inom fem bildpunkter och förblir fästa när storleken ändras. Ordna i rutnät flyttar de "
    L"andra widgetarna till närliggande platser utan överlappning medan referenswidgeten står "
    L"kvar. Skärmklockor ignoreras. I kalender- och klockpanelen går den övre länken till i dag "
    L"och den nedre öppnar Windows klassiska inställningar för datum och tid; båda fungerar med "
    L"mus och tangentbord.\r\n\r\nI en fristående kalender kan raden I dag visas eller döljas på "
    L"fliken Utseende eller i widgetmenyn. Gå till i dag väljer dagens datum och månadsvyn. När "
    L"datumet ändras enligt widgetens tid väljs dagens datum automatiskt utan att ändra vytypen.",
    L"\r\n\r\nASETTELU\r\nKun reunakiinnitys on käytössä, pienoisohjelmat tarttuvat työalueen "
    L"reunoihin viiden kuvapisteen etäisyydellä ja pysyvät kiinni koon muuttuessa. Järjestä "
    L"ruudukkoon siirtää muut pienoisohjelmat läheisiin, päällekkäisyyksiä välttäviin paikkoihin "
    L"ja pitää viiteohjelman paikallaan. Näyttökellot ohitetaan. Kalenteri- ja kellopaneelin "
    L"ylälinkki palauttaa tämän päivän ja alalinkki avaa Windowsin perinteiset päivämäärä- ja "
    L"aika-asetukset; molempia voi käyttää hiirellä ja näppäimistöllä.\r\n\r\nErillisen "
    L"kalenterin Tänään-rivin voi näyttää tai piilottaa Ulkoasu-välilehdellä tai pienoisohjelman "
    L"valikossa. Siirry tähän päivään valitsee nykyisen päivän ja kuukausinäkymän. Päivämäärän "
    L"vaihtuessa pienoisohjelman ajan mukaan nykyinen päivä valitaan automaattisesti "
    L"näkymätyyppiä muuttamatta.",
    L"\r\n\r\nPLACERING\r\nNår kantfastgørelse er slået til, fastgøres widgets til "
    L"arbejdsområdets kanter inden for fem pixel og forbliver fastgjort ved størrelsesændring. "
    L"Arranger i gitter flytter de øvrige widgets til nærliggende pladser uden overlapning og "
    L"lader referencewidgeten blive stående. Skærmure ignoreres. I kalender- og urpanelet går det "
    L"øverste link til i dag, og det nederste åbner Windows' klassiske indstillinger for dato og "
    L"klokkeslæt; begge virker med mus og tastatur.\r\n\r\nI en selvstændig kalender kan rækken I "
    L"dag vises eller skjules på fanen Udseende eller i widgetmenuen. Gå til i dag vælger dags "
    L"dato og månedsvisningen. Når datoen ændres efter widgetens tid, vælges dagens dato "
    L"automatisk uden at ændre visningstypen.",
    L"\r\n\r\nUPPRÖÐUN\r\nÞegar festing við brúnir er virk festast græjur við brúnir "
    L"vinnusvæðisins innan fimm mynddíla og haldast fastar þegar stærð breytist. Raða á hnitanet "
    L"færir aðrar græjur á nálæga staði án skörunar en heldur viðmiðunargræjunni kyrrri. "
    L"Skjáklukkur eru hunsaðar. Í dagatals- og klukkuspjaldinu fer efri tengillinn á daginn í dag "
    L"og sá neðri opnar hefðbundnar dagsetningar- og tímastillingar Windows; báðir virka með mús "
    L"og lyklaborði.\r\n\r\nÍ sjálfstæðu dagatali má sýna eða fela Í dag-línuna á Útlit-flipanum "
    L"eða í valmynd græjunnar. Fara á daginn í dag velur daginn í dag og mánaðarsýn. Þegar "
    L"dagsetning breytist samkvæmt tíma græjunnar er dagurinn í dag valinn sjálfkrafa án þess að "
    L"breyta gerð dagatalssýnar.",
    L"\r\n\r\nDÜZEN\r\nKenar yapışması etkinleştirildiğinde araçlar çalışma alanının kenarlarına "
    L"beş piksel içinde yapışır ve boyut değişirken yapışık kalır. Izgarada düzenle, başvuru "
    L"aracını yerinde tutarak diğer araçları çakışmayan yakın konumlara taşır. Monitör saatleri "
    L"hesaba katılmaz. Saatli takvim panelinde üst bağlantı bugüne döner, alt bağlantı Windows'un "
    L"klasik Tarih ve Saat ayarlarını açar; ikisi de fare ve klavyeyle çalışır.\r\n\r\nBağımsız "
    L"takvimde Bugün satırını Görünüm sekmesinden veya araç menüsünden gösterip "
    L"gizleyebilirsiniz. Bugüne git, bugünün tarihini seçer ve ay görünümüne döner. Aracın "
    L"saatine göre tarih değiştiğinde görünüm türü korunarak bugünün tarihi otomatik seçilir.",
    L"\r\n\r\nVidinate paigutus\r\nPaiguta ruudustikku säilitab ligikaudse käsitsi paigutuse, "
    L"tõmbab keskpunktid lähimatele ruudustikupunktidele ja kõrvaldab kattumised. Käsu käivitanud "
    L"vidin jääb paigale. Vidina menüü mõjutab selle kuvarit, olekuala ikoon iga kuvarit eraldi. "
    L"Kordamine säilitab stabiilse paigutuse. Sätete topeltklõps tõstab vidina esile kiire "
    L"helesinise vilkumisega; äratus vilgub aeglasemalt punaselt. Alati pealmine väljalülitamine "
    L"saadab vidina teiste akende taha. Paneeli ülemine link toob kalendri tänasele kuupäevale ja "
    L"alumine avab Windowsi klassikalised kuupäeva ja kellaaja sätted. Servatõmme haarab "
    L"lohistatava vidina tööala serva külge kuni viie piksli kauguselt. Suuruse muutmisel säilib "
    L"kinnitus sama serva või servapaari külge.\r\n\r\nEraldi kalendris kuvab või peidab Tänase "
    L"kuupäeva rida vahekaardil Ilme või menüüs alumise rea. Mine tänasele kuupäevale valib "
    L"tänase päeva ja taastab kuuvaate. Kui vidina aja järgi kuupäev muutub, valitakse tänane "
    L"kuupäev automaatselt praegust kalendrivaadet säilitades.",
    L"\r\n\r\nLeagan amach\r\nCoinníonn Eagraigh in eangach an leagan amach láimhe gar dá "
    L"bhunleagan, léimeann lárphointí chuig na pointí eangaí is gaire agus baintear forluí. "
    L"Fanann an ghiuirléid óna roghchlár a seoladh an t-ordú ina háit. Baineann roghchlár "
    L"giuirléide lena monatóir; baineann an deilbhín fógraí le gach monatóir ar leith. Coinníonn "
    L"athdhéanamh an leagan amach seasmhach. Aithníonn déchliceáil sna Socruithe giuirléid le "
    L"caochadh tapa gorm éadrom; bíonn aláram dearg agus níos moille. Cuireann múchadh Ar barr i "
    L"gcónaí an ghiuirléid taobh thiar de na fuinneoga eile. Filleann nasc uachtarach an phainéil "
    L"ar an lá inniu agus osclaíonn an nasc íochtarach socruithe clasaiceacha dáta agus ama "
    L"Windows. Léimeann giuirléid atá á tarraingt chuig imeall an limistéir oibre laistigh de "
    L"chúig phicteilín má tá an rogha cumasaithe. Coinníonn athrú méide an ceangal leis an imeall "
    L"céanna nó leis an bpéire imill céanna.\r\n\r\nI bhféilire neamhspleách, taispeánann nó "
    L"folaíonn Sraith an lae inniu ar an gcluaisín Cuma nó sa roghchlár an tsraith íochtarach. "
    L"Roghnaíonn Téigh go dtí an lá inniu an dáta reatha agus filleann sé ar amharc na míosa. "
    L"Nuair a athraíonn an dáta de réir am na giuirléide, roghnaítear an lá inniu go "
    L"huathoibríoch agus coinnítear an t-amharc reatha.",
    L"\r\n\r\nValdiklių išdėstymas\r\nIšdėstyti tinkleliu išlaiko apytikslį rankinį išdėstymą, "
    L"prikabina centrus prie artimiausių tinklo taškų ir pašalina persidengimą. Komandą iškvietęs "
    L"valdiklis lieka vietoje. Valdiklio meniu veikia jo monitorių; pranešimų srities piktograma "
    L"– kiekvieną monitorių atskirai. Pakartojimas išlaiko išdėstymą stabilų. Dukart spustelėjus "
    L"parametruose valdiklis greitai mirksi šviesiai mėlynai; žadintuvas mirksi lėčiau raudonai. "
    L"Išjungus Visada viršuje valdiklis nusiunčiamas už kitų langų. Viršutinis skydelio saitas "
    L"grąžina kalendorių į šiandieną, apatinis atidaro klasikinius „Windows“ datos ir laiko "
    L"parametrus. Įjungtas prikabinimas pritraukia velkamą valdiklį prie darbo srities krašto iki "
    L"penkių pikselių atstumu. Keičiant dydį ryšys su tuo pačiu kraštu arba kraštų pora "
    L"išlieka.\r\n\r\nAtskiro kalendoriaus Šiandienos eilutė skirtuke Išvaizda arba meniu rodo ar "
    L"slepia apatinę eilutę. Pereiti į šiandieną pasirenka šiandienos datą ir atkuria mėnesio "
    L"rodinį. Pasikeitus datai pagal valdiklio laiką šiandiena pasirenkama automatiškai išlaikant "
    L"dabartinį rodinį.",
    L"\r\n\r\nLogrīku izkārtojums\r\nSakārtot režģī saglabā aptuveno manuālo izkārtojumu, pievelk "
    L"centrus tuvākajiem režģa punktiem un novērš pārklāšanos. Logrīks, kura izvēlnē izsaukta "
    L"komanda, paliek vietā. Logrīka izvēlne ietekmē tā monitoru, paziņojumu ikona katru monitoru "
    L"atsevišķi. Atkārtojot izkārtojums paliek stabils. Dubultklikšķis iestatījumos izceļ logrīku "
    L"ar ātru gaišzilu mirgošanu; modinātājs mirgo lēnāk sarkani. Izslēdzot Vienmēr virspusē, "
    L"logrīks tiek novietots aiz pārējiem logiem. Paneļa augšējā saite atgriež kalendāru šodienā, "
    L"apakšējā atver Windows klasiskos datuma un laika iestatījumus. Ieslēgta pievilkšana pievelk "
    L"vilktu logrīku darba apgabala malai līdz piecu pikseļu attālumā. Lieluma maiņa saglabā "
    L"piesaisti tai pašai malai vai malu pārim.\r\n\r\nAtsevišķā kalendārā Šodienas rinda cilnē "
    L"Izskats vai izvēlnē rāda vai slēpj apakšējo rindu. Pāriet uz šodienu atlasa šodienas datumu "
    L"un atjauno mēneša skatu. Mainoties datumam pēc logrīka laika, šodiena tiek atlasīta "
    L"automātiski, saglabājot pašreizējo skatu.",
    L"\r\n\r\nElrendezés\r\nA Rácsba rendezés megőrzi a hozzávetőleges kézi elrendezést, a "
    L"középpontokat a legközelebbi rácspontokhoz illeszti és megszünteti az átfedéseket. A "
    L"parancsot indító minialkalmazás helyben marad. A saját menü a saját monitorra, az "
    L"értesítési ikon minden monitorra külön hat. Ismételve az elrendezés stabil marad. A "
    L"beállításokbeli dupla kattintás gyors világoskék villogással jelöl; az ébresztés lassabban, "
    L"pirosan villog. A Mindig felül kikapcsolása a többi ablak mögé küldi a minialkalmazást. A "
    L"panel felső hivatkozása a mai napra tér vissza, az alsó a Windows klasszikus dátum- és "
    L"időbeállításait nyitja meg. Az engedélyezett szélhez illesztés öt képponton belül a "
    L"munkaterület széléhez húzza a mozgatott minialkalmazást. Átméretezéskor ugyanahhoz a "
    L"szélhez vagy sarokhoz csatlakozik.\r\n\r\nÖnálló naptárban a Mai dátum sora a Megjelenés "
    L"fülön vagy menüben az alsó sort kapcsolja. Az Ugrás a mai napra kiválasztja a mai dátumot "
    L"és visszaállítja a havi nézetet. A minialkalmazás szerinti dátumváltáskor a mai nap "
    L"automatikusan kijelölődik az aktuális nézet megtartásával.",
    L"\r\n\r\nTqassim tal-widgets\r\nIrranġa fi gradilja iżomm bejn wieħed u ieħor it-tqassim "
    L"manwali, iwaħħal iċ-ċentri mal-eqreb punti tal-gradilja u jneħħi s-sovrapożizzjonijiet. "
    L"Il-widget li minnu ġie msejjaħ il-kmand jibqa’ f’postu. Il-menu tal-widget jaġixxi fuq "
    L"il-moniter tiegħu; l-ikona tan-notifiki fuq kull moniter separatament. Ir-ripetizzjoni "
    L"żżomm tqassim stabbli. Klikk doppju fis-settings jidentifika widget b’teptip blu ċar "
    L"mgħaġġel; allarm iteptep aħmar aktar bil-mod. It-tifi ta’ Dejjem fuq nett jibgħat il-widget "
    L"wara t-twieqi l-oħra. Il-link ta’ fuq fil-panew jirritorna għal-lum; t’isfel jiftaħ "
    L"is-settings klassiċi tad-data u l-ħin tal-Windows. Meta t-twaħħil ikun attivat, widget "
    L"mkaxkar sa ħames pixels mit-tarf jeħel mat-tarf taż-żona tax-xogħol. Il-bidla fid-daqs "
    L"iżżomm ir-rabta mal-istess tarf jew par truf.\r\n\r\nF’kalendarju separat, Ringiela tal-lum "
    L"fit-tab Dehra jew fil-menu turi jew taħbi r-ringiela t’isfel. Mur għad-data tal-lum jagħżel "
    L"illum u jirritorna għall-vista tax-xahar. Meta d-data tinbidel skont il-ħin tal-widget, "
    L"illum jintgħażel awtomatikament waqt li tinżamm il-vista kurrenti.",
    L"\r\n\r\nWidgets schikken\r\nSchikken in raster behoudt de globale handmatige indeling, "
    L"lijnt middelpunten uit op de dichtstbijzijnde rasterpunten en verwijdert overlap. De widget "
    L"waarvan het menu is gebruikt blijft staan. Een widgetmenu beïnvloedt zijn beeldscherm; het "
    L"systeemvakpictogram behandelt elk scherm afzonderlijk. Herhalen houdt de indeling stabiel. "
    L"Dubbelklikken in Instellingen markeert een widget met snel lichtblauw knipperen; een alarm "
    L"knippert langzamer rood. Altijd op voorgrond uitschakelen plaatst de widget achter andere "
    L"vensters. De bovenste paneelkoppeling gaat naar vandaag, de onderste opent de klassieke "
    L"Windows-instellingen voor datum en tijd. Als uitlijnen op randen is ingeschakeld, klikt een "
    L"versleepte widget binnen vijf pixels vast aan de rand van het werkgebied. Bij vergroten of "
    L"verkleinen blijft dezelfde rand of hetzelfde paar randen behouden.\r\n\r\nBij een losse "
    L"kalender toont of verbergt Rij Vandaag op Vormgeving of in het menu de onderste rij. Naar "
    L"vandaag kiest vandaag en herstelt de maandweergave. Bij een datumwisseling volgens de "
    L"widgettijd wordt vandaag automatisch gekozen zonder de huidige kalenderweergave te "
    L"veranderen.",
    L"\r\n\r\nAranjarea widgeturilor\r\nAranjare în grilă păstrează aproximativ pozițiile "
    L"manuale, aliniază centrele la cele mai apropiate puncte ale grilei și elimină "
    L"suprapunerile. Widgetul din al cărui meniu s-a lansat comanda rămâne pe loc. Meniul "
    L"widgetului afectează monitorul său; pictograma de notificare tratează fiecare monitor "
    L"separat. Repetarea păstrează aranjarea stabilă. Dublul clic din Setări identifică widgetul "
    L"prin clipire rapidă albastru-deschis; alarma clipește mai lent în roșu. Dezactivarea "
    L"Întotdeauna deasupra trimite widgetul în spatele ferestrelor. Legătura superioară a "
    L"panoului revine la azi, cea inferioară deschide setările clasice Windows pentru dată și "
    L"oră. Alinierea la margini atrage widgetul glisat la marginea zonei de lucru de la cel mult "
    L"cinci pixeli. Redimensionarea păstrează atașarea la aceeași margine sau pereche de "
    L"margini.\r\n\r\nPentru un calendar separat, Rândul Azi din Aspect sau meniu afișează ori "
    L"ascunde rândul inferior. Salt la ziua de azi selectează azi și restabilește vizualizarea "
    L"lunară. Când data se schimbă după ora widgetului, ziua de azi se selectează automat, "
    L"păstrând vizualizarea curentă.",
    L"\r\n\r\nΔιάταξη στοιχείων\r\nΗ Τακτοποίηση σε πλέγμα διατηρεί την κατά προσέγγιση "
    L"χειροκίνητη διάταξη, ευθυγραμμίζει κέντρα στα πλησιέστερα σημεία του πλέγματος και αφαιρεί "
    L"επικαλύψεις. Το στοιχείο από το μενού του οποίου κλήθηκε η εντολή παραμένει στη θέση του. "
    L"Το μενού στοιχείου επηρεάζει την οθόνη του· το εικονίδιο ειδοποιήσεων κάθε οθόνη χωριστά. Η "
    L"επανάληψη κρατά τη διάταξη σταθερή. Το διπλό κλικ στις Ρυθμίσεις επισημαίνει στοιχείο με "
    L"γρήγορο γαλάζιο αναβόσβημα· το ξυπνητήρι αναβοσβήνει πιο αργά κόκκινο. Η απενεργοποίηση του "
    L"Πάντα σε πρώτο πλάνο στέλνει το στοιχείο πίσω από άλλα παράθυρα. Ο επάνω σύνδεσμος του "
    L"πλαισίου επιστρέφει στο σήμερα, ο κάτω ανοίγει τις κλασικές ρυθμίσεις ημερομηνίας και ώρας "
    L"των Windows. Η ενεργή προσκόλληση τραβά συρόμενο στοιχείο στο άκρο της περιοχής εργασίας "
    L"από απόσταση έως πέντε pixel. Η αλλαγή μεγέθους διατηρεί την προσκόλληση στο ίδιο άκρο ή "
    L"ζεύγος άκρων.\r\n\r\nΣε ανεξάρτητο ημερολόγιο, η Γραμμή Σήμερα στην Εμφάνιση ή στο μενού "
    L"δείχνει ή κρύβει την κάτω γραμμή. Η Μετάβαση στο σήμερα επιλέγει σήμερα και επαναφέρει τη "
    L"μηνιαία προβολή. Όταν αλλάξει η ημερομηνία κατά την ώρα του στοιχείου, το σήμερα επιλέγεται "
    L"αυτόματα χωρίς αλλαγή της τρέχουσας προβολής.",
    L"\r\n\r\nRaspored vidžeta\r\nRasporedi u mrežu čuva približan ručni raspored, priljubljuje "
    L"središta vidžeta uz najbliže tačke mreže i uklanja preklapanja. Meni vidžeta djeluje na "
    L"njegov ekran, a ikona u području obavijesti na svaki ekran zasebno. Ponavljanje naredbe "
    L"čuva raspored. Dvostruki klik u Postavkama označava vidžet brzim svijetloplavim "
    L"treperenjem; alarm treperi sporije i crveno. Isključivanje opcije Uvijek na vrhu šalje "
    L"vidžet iza ostalih prozora. Na ploči kalendara sa satom gornja poveznica vraća kalendar na "
    L"današnji datum, a donja otvara klasične postavke datuma i vremena Windowsa. Ako je "
    L"priljubljivanje uključeno, vidžet se tokom povlačenja priljubljuje uz ivicu radnog područja "
    L"na udaljenosti do pet piksela. Promjena veličine čuva vezu s istom ivicom ili parom "
    L"ivica.\r\n\r\nZa samostalni kalendar prikažite ili sakrijte Red Danas na kartici Izgled ili "
    L"u meniju vidžeta. Idi na današnji datum odabire danas i vraća mjesečni prikaz. Kada se "
    L"datum promijeni prema vremenu vidžeta, današnji se datum odabire automatski uz očuvanje "
    L"trenutnog prikaza kalendara.",
    L"\r\n\r\nRaspored widgeta\r\nRasporedi u mrežu čuva približan ručni raspored, priljubljuje "
    L"središta widgeta uz najbliže točke mreže i uklanja preklapanja. Izbornik widgeta djeluje na "
    L"njegov zaslon, a ikona u području obavijesti na svaki zaslon zasebno. Ponavljanje naredbe "
    L"čuva raspored. Dvostruki klik u Postavkama označava widget brzim svijetloplavim "
    L"treperenjem; alarm treperi sporije i crveno. Isključivanje opcije Uvijek na vrhu šalje "
    L"widget iza ostalih prozora. Na ploči kalendara sa satom gornja poveznica vraća kalendar na "
    L"današnji datum, a donja otvara klasične postavke datuma i vremena Windowsa. Ako je "
    L"priljubljivanje uključeno, widget se tijekom povlačenja priljubljuje uz rub radnog područja "
    L"na udaljenosti do pet piksela. Promjena veličine čuva vezu s istim rubom ili parom "
    L"rubova.\r\n\r\nZa samostalni kalendar prikažite ili sakrijte Redak Danas na kartici Izgled "
    L"ili u izborniku widgeta. Idi na današnji datum odabire danas i vraća mjesečni prikaz. Kada "
    L"se datum promijeni prema vremenu widgeta, današnji se datum odabire automatski uz očuvanje "
    L"trenutačnog prikaza kalendara.",
    L"\r\n\r\nRazporeditev gradnikov\r\nRazporedi v mrežo ohrani približno ročno razporeditev, "
    L"pripne središča na najbližje mrežne točke in odpravi prekrivanje. Meni gradnika deluje na "
    L"njegovem zaslonu, ikona za obvestila pa na vsakem zaslonu posebej. Ponovitev ohrani "
    L"razporeditev. Dvoklik v Nastavitvah označi gradnik s hitrim svetlomodrim utripanjem; "
    L"budilka utripa počasneje in rdeče. Izklop Vedno na vrhu pošlje gradnik v ozadje. Na plošči "
    L"koledarja z uro zgornja povezava vrne koledar na danes, spodnja pa odpre klasične "
    L"nastavitve datuma in časa Windows. Vključeno pripenjanje pritegne vlečeni gradnik do roba "
    L"delovnega območja na razdalji petih slikovnih pik. Spreminjanje velikosti ohrani pripetost "
    L"na isti rob ali par robov.\r\n\r\nV samostojnem koledarju možnost Vrstica Danes na zavihku "
    L"Videz ali v meniju pokaže ali skrije spodnjo vrstico. Pojdi na današnji datum izbere danes "
    L"in vrne mesečni pogled. Ob spremembi datuma po času gradnika se današnji datum izbere "
    L"samodejno, trenutni pogled koledarja pa se ohrani.",
    L"\r\n\r\nRaspored vidžeta\r\nRasporedi u mrežu čuva približan ručni raspored, priljepljuje "
    L"središta uz najbliže tačke mreže i uklanja preklapanja. Meni vidžeta djeluje na njegov "
    L"monitor, ikona za obavještenja na svaki monitor posebno. Ponavljanje čuva raspored. Dvoklik "
    L"u Podešavanjima označava vidžet brzim svijetloplavim treperenjem; alarm treperi sporije i "
    L"crveno. Isključivanje Uvijek na vrhu šalje vidžet iza ostalih prozora. Gornja veza na "
    L"panelu vraća kalendar na danas, donja otvara klasična podešavanja datuma i vremena "
    L"Windows-a. Uključeno priljepljivanje privlači pomjerani vidžet uz ivicu radne površine sa "
    L"razdaljine do pet piksela. Promjena veličine čuva vezu sa istom ivicom ili parom "
    L"ivica.\r\n\r\nU samostalnom kalendaru Red Danas na kartici Izgled ili u meniju prikazuje "
    L"ili skriva donji red. Idi na današnji datum bira danas i vraća mjesečni prikaz. Pri "
    L"promjeni datuma po vremenu vidžeta današnji datum se bira automatski uz očuvanje trenutnog "
    L"prikaza kalendara.",
    L"\r\n\r\nРазмяшчэнне віджэтаў\r\n«Упарадкаваць па сетцы» захоўвае прыблізнае ручное "
    L"размяшчэнне, прывязвае цэнтры да найбліжэйшых вузлоў сеткі і прыбірае перакрыцці. Меню "
    L"віджэта дзейнічае на яго маніторы, а значок у вобласці апавяшчэнняў — на кожным маніторы "
    L"асобна. Паўтор каманды захоўвае размяшчэнне. Падвойная пстрычка ў наладах пазначае віджэт "
    L"хуткім светла-блакітным мігценнем; будзільнік мігціць павольней і чырвоным. Выключэнне "
    L"«Заўсёды зверху» перамяшчае віджэт назад. На панэлі календара з гадзіннікам верхняя "
    L"спасылка вяртае каляндар да сёння, а ніжняя адкрывае класічныя налады даты і часу Windows. "
    L"Пры ўключанай прывязцы перацягнуты віджэт прывязваецца да краю рабочай вобласці на "
    L"адлегласці да пяці пікселяў. Змена памеру захоўвае прывязку да таго ж краю або пары "
    L"краёў.\r\n\r\nУ асобным календары Радок «Сёння» на ўкладцы «Выгляд» ці ў меню паказвае або "
    L"хавае ніжні радок. «Перайсці да сённяшняй даты» выбірае сёння і вяртае месячны выгляд. Калі "
    L"дата паводле часу віджэта змяняецца, сённяшняя дата выбіраецца аўтаматычна з захаваннем "
    L"бягучага выгляду календара.",
    L"\r\n\r\nРазполагане на модулите\r\n„Подреди в мрежа“ запазва приблизителното ръчно "
    L"разположение, прилепва центровете към най-близките възли и премахва застъпванията. Менюто "
    L"на модул действа върху неговия монитор, а иконата за уведомяване — върху всеки монитор "
    L"поотделно. Повторението запазва разположението. Двойното щракване в настройките обозначава "
    L"модул с бързо светлосиньо мигане; алармата мига по-бавно в червено. Изключването на „Винаги "
    L"отгоре“ изпраща модула отзад. Горната връзка в панела връща календара към днес, а долната "
    L"отваря класическите настройки за дата и час на Windows. При включено прилепване влаченият "
    L"модул се прилепва към край на работната област от разстояние до пет пиксела. Промяната на "
    L"размера запазва прилепването към същия край или двойка краища.\r\n\r\nЗа самостоятелен "
    L"календар Ред „Днес“ в раздела „Изглед“ или менюто показва или скрива долния ред. „Отиди на "
    L"днешната дата“ избира днес и връща месечния изглед. При смяна на датата по времето на "
    L"модула днешната дата се избира автоматично, като текущият изглед се запазва.",
    L"\r\n\r\nРаспоред на виџетите\r\n„Распореди во мрежа“ го зачувува приближниот рачен "
    L"распоред, ги прилепува средиштата до најблиските точки на мрежата и ги отстранува "
    L"преклопувањата. Менито на виџетот дејствува на неговиот монитор, а иконата за известување "
    L"на секој монитор одделно. Повторувањето го зачувува распоредот. Двоен клик во поставките го "
    L"означува виџетот со брзо светлосино трепкање; алармот трепка побавно и црвено. "
    L"Исклучувањето на „Секогаш најгоре“ го испраќа виџетот назад. Горната врска во панелот го "
    L"враќа календарот на денес, а долната ги отвора класичните поставки за датум и време на "
    L"Windows. При вклучено прилепување, повлечениот виџет се прилепува кон раб на работната "
    L"површина од растојание до пет пиксели. Промената на големината ја зачувува врската со "
    L"истиот раб или пар рабови.\r\n\r\nЗа самостоен календар редот „Денес“ се покажува или крие "
    L"на картичката „Изглед“ или во менито. „Оди на денешниот датум“ избира денес и го враќа "
    L"месечниот приказ. При промена на датумот според времето на виџетот, денешниот датум се "
    L"избира автоматски, а тековниот приказ останува зачуван.",
    L"\r\n\r\nРаспоред виџета\r\nРаспореди у мрежу чува приближан ручни распоред, прилепљује "
    L"средишта уз најближе тачке мреже и уклања преклапања. Мени виџета делује на његов монитор, "
    L"икона за обавештења на сваки монитор посебно. Понављање чува распоред. Двоклик у "
    L"Подешавањима означава виџет брзим светлоплавим треперењем; аларм трепери спорије и црвено. "
    L"Искључивање Увек на врху шаље виџет иза осталих прозора. Горња веза на панелу враћа "
    L"календар на данас, доња отвара класична подешавања датума и времена Windows-а. Укључено "
    L"прилепљивање привлачи померани виџет уз ивицу радне површине са раздаљине до пет пиксела. "
    L"Промена величине чува везу са истом ивицом или паром ивица.\r\n\r\nУ самосталном календару "
    L"Ред Данас на картици Изглед или у менију приказује или скрива доњи ред. Иди на данашњи "
    L"датум бира данас и враћа месечни приказ. При промени датума по времену виџета данашњи датум "
    L"се бира аутоматски уз очување тренутног приказа календара.",
    L"\r\n\r\nРОЗТАШУВАННЯ ВІДЖЕТІВ\r\nКоманда «Упорядкувати за сіткою» зберігає приблизне ручне "
    L"розташування, прив’язує центри віджетів до найближчих вузлів сітки та усуває перекриття. "
    L"Команда з меню віджета діє на його моніторі, а з меню піктограми в області сповіщень — "
    L"окремо на кожному моніторі. Повторне виконання зберігає розташування. Подвійне клацання у "
    L"списку налаштувань позначає віджет швидким світло-блакитним блиманням; будильник блимає "
    L"повільніше й червоним. Вимкнення «Завжди зверху» переміщує віджет на задній план. У панелі "
    L"календаря з годинником верхнє посилання повертає календар до сьогоднішньої дати, а нижнє "
    L"відкриває класичні параметри дати й часу Windows. Якщо прив’язку до країв увімкнено, віджет "
    L"під час перетягування прив’язується до краю робочої області на відстані до п’яти пікселів. "
    L"Після зміни розміру він залишається прив’язаним до того самого краю або пари "
    L"країв.\r\n\r\nДля окремого календаря рядок «Сьогодні» можна показати або приховати на "
    L"вкладці «Вигляд» чи в меню віджета. «Перейти до сьогоднішньої дати» вибирає сьогоднішню "
    L"дату й повертає перегляд місяця. Коли дата за часом віджета змінюється, сьогоднішня дата "
    L"вибирається автоматично зі збереженням поточного режиму перегляду календаря.",
    L"\r\n\r\nРАСПОЛОЖЕНИЕ ВИДЖЕТОВ\r\nКоманда «Упорядочить по сетке» сохраняет приблизительное "
    L"ручное расположение, привязывает центры виджетов к ближайшим узлам сетки и устраняет "
    L"перекрытия. Команда из меню виджета действует на его мониторе, а из меню значка в области "
    L"уведомлений — отдельно на каждом мониторе. Повторное выполнение сохраняет расположение. "
    L"Двойной щелчок в списке настроек обозначает виджет быстрым светло-голубым миганием; "
    L"будильник мигает медленнее и красным. Отключение «Поверх всех окон» перемещает виджет на "
    L"задний план. В панели календаря с часами верхняя ссылка возвращает календарь к сегодняшней "
    L"дате, а нижняя открывает классические параметры даты и времени Windows. Если привязка к "
    L"краям включена, перетаскиваемый виджет привязывается к краю рабочей области на расстоянии до "
    L"пяти пикселей. После изменения размера он остаётся привязанным к тому же краю или паре "
    L"краёв.\r\n\r\nДля отдельного календаря строку «Сегодня» можно показать или скрыть на вкладке "
    L"«Внешний вид» либо в меню виджета. «Перейти к сегодняшней дате» выбирает сегодняшнюю дату и "
    L"возвращает просмотр месяца. Когда дата по времени виджета меняется, сегодняшняя дата "
    L"выбирается автоматически с сохранением текущего режима просмотра календаря."
};

const wchar_t* HELP_STORAGE_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nVZHLED A ÚLOŽIŠTĚ\r\nZměny vzhledu se ukazují ihned v živém náhledu; Zrušit zruší "
    L"nepoužité změny vzhledu a Výchozí vzhled obnoví výchozí hodnoty daného typu. Digitální "
    L"hodiny nabízejí písmo, vyhlazování, barvy, neprůhlednost, odsazení, šířku rámečku a "
    L"průhledné pozadí. Digitální hodiny, kalendář a panel mají stejné čtyři styly rámečku; u "
    L"jednoduchého rámečku lze zvolit jeho barvu. Panel má samostatná písma horního řádku, času a "
    L"spodního řádku, úvodní nulu a volitelnou velikost ciferníku. Vlastní písmo kalendáře se "
    L"používá při klasickém vzhledu Windows nebo při vypnutých motivech aplikace či widgetu. "
    L"Nastavení lze exportovat do XML. Import XML okamžitě načte a uloží nastavení do právě "
    L"zvoleného úložiště; typ úložiště nezmění. Automatické XML je v "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Po úspěšném zápisu XML se odstraní větev "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; při ukládání do registru se automatické XML "
    L"odstraní.\r\n\r\nVyhlazování písma nabízí ClearType, GDI a Žádné.\r\n\r\nÚvodní nula nabízí "
    L"„Ano“ (výchozí), „Ne, ponechat místo“ a „Ne, bez místa“. Volba „Ne, ponechat místo“ skryje "
    L"nulu a rezervuje její šířku "
    L"ve zvoleném písmu; ostatní číslice zůstanou na stejných místech i u proporcionálního písma. "
    L"Hodiny na monitoru zůstávají zarovnané na střed včetně rezervovaného místa. Řádek UTC si "
    L"zachovává vlastní zarovnání na střed.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live "
    L"preview; Cancel discards unapplied appearance changes and Default appearance restores the "
    L"defaults for that widget type. Digital clocks provide font, smoothing, colors, opacity, "
    L"padding, border width and a transparent background. Digital clocks, calendars and panels "
    L"share four border styles; the single-line border has a selectable color. The panel has "
    L"separate fonts for its top row, time and bottom row, a leading zero and selectable "
    L"clock-face sizes. Custom calendar fonts are supported with the Windows classic appearance "
    L"or with visual styles turned off for the application or widget. Settings can be exported to "
    L"XML. Importing XML immediately loads and saves the settings to the currently selected "
    L"storage without changing the storage type. Automatic XML is "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. After writing XML, "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock is removed; registry storage removes the automatic "
    L"XML.\r\n\r\nFont antialiasing offers ClearType, GDI, and None.\r\n\r\nLeading zero offers "
    L"“Yes” (default), “No, keep space”, and “No, without space”. “No, keep space” hides the zero "
    L"while reserving its "
    L"width in the selected font; the other digits keep their positions even with proportional "
    L"fonts. Monitor clocks remain centered, including the reserved space. The UTC row keeps its "
    L"own center alignment.",
    L"\r\n\r\nDARSTELLUNG UND SPEICHERUNG\r\nDarstellungsänderungen erscheinen sofort in der "
    L"Vorschau; Abbrechen verwirft noch nicht übernommene Änderungen, Standarddarstellung die "
    L"Vorgaben des Widget-Typs. Digitaluhren bieten Schrift, Glättung, Farben, Deckkraft, "
    L"Innenabstand, Rahmenbreite und transparenten Hintergrund. Digitaluhren, Kalender und Panel "
    L"verwenden dieselben vier Rahmenarten; für den einfachen Rahmen ist die Farbe wählbar. Das "
    L"Panel besitzt getrennte Schriften für obere Zeile, Zeit und untere Zeile, eine führende "
    L"Null und wählbare Zifferblattgrößen. Eigene Kalenderschriftarten werden beim klassischen "
    L"Windows-Erscheinungsbild oder bei deaktivierten Designs für die Anwendung oder das Widget "
    L"unterstützt. Einstellungen können als XML exportiert werden. Ein XML-Import lädt und "
    L"speichert die Einstellungen sofort im aktuell gewählten Speicher, ohne die Speicherart zu "
    L"ändern. Automatisches XML liegt in %AppData%\\FortSoft\\CalClock\\settings.xml; "
    L"XML-Speicherung entfernt HKCU\\SOFTWARE\\FortSoft\\CalClock, Registrierungsspeicherung "
    L"entfernt das automatische XML.\r\n\r\nFür die Schriftglättung stehen ClearType, GDI und "
    L"Keine zur Auswahl.\r\n\r\nFührende Null bietet „Ja“ (Standard), „Nein, Platz freihalten“ und "
    L"„Nein, ohne Platz“. „Nein, Platz freihalten“ blendet die Null aus und reserviert ihre Breite "
    L"in der "
    L"gewählten Schrift; andere Ziffern bleiben auch bei proportionalen Schriften an derselben "
    L"Position. Monitoruhren bleiben mit dem reservierten Platz zentriert, die UTC-Zeile bleibt "
    L"separat zentriert.",
    L"\r\n\r\nAPPARENCE ET STOCKAGE\r\nLes changements d’apparence sont prévisualisés "
    L"immédiatement ; Annuler abandonne les modifications non appliquées et Apparence par défaut "
    L"celles du type de widget. Les horloges numériques proposent police, lissage, couleurs, "
    L"opacité, marge, largeur de bordure et fond transparent. Horloges numériques, calendriers et "
    L"panneaux partagent quatre styles de bordure ; la couleur de la bordure simple est "
    L"sélectionnable. Le panneau possède des polices distinctes pour les lignes supérieure, "
    L"horaire et inférieure, un zéro initial et des tailles de cadran au choix. Les polices de "
    L"calendrier personnalisées sont prises en charge avec l’apparence classique de Windows ou "
    L"lorsque les thèmes sont désactivés pour l’application ou le widget. Les paramètres peuvent "
    L"être exportés en XML. L’import XML charge et enregistre immédiatement les paramètres dans "
    L"le stockage sélectionné, sans changer son type. Le XML automatique est "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml ; son écriture retire "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock, tandis que le registre retire ce XML.\r\n\r\nLe lissage "
    L"des polices propose ClearType, GDI et Aucun.\r\n\r\nLe zéro initial propose « Oui » (par "
    L"défaut), « Non, garder l’espace » et « Non, sans espace ». « Non, garder l’espace » masque le"
    L" zéro en réservant sa "
    L"largeur dans la police choisie ; les autres chiffres gardent leur position, même avec une "
    L"police proportionnelle. Les horloges de moniteur restent centrées, espace réservé compris. "
    L"La ligne UTC reste centrée séparément.",
    L"\r\n\r\nAPARIENCIA Y ALMACENAMIENTO\r\nLos cambios de apariencia se previsualizan al "
    L"instante; Cancelar descarta los cambios de apariencia no aplicados y Aspecto predeterminado "
    L"restaura los valores predeterminados de ese tipo de widget. Los relojes digitales ofrecen "
    L"fuente, suavizado, colores, opacidad, relleno, ancho de borde y fondo transparente. Los "
    L"relojes digitales, calendarios y paneles comparten cuatro estilos de borde; el color del "
    L"borde simple es seleccionable. El panel tiene fuentes separadas para la línea superior, la "
    L"hora y la inferior, cero inicial y tamaños de esfera seleccionables. Las fuentes "
    L"personalizadas del calendario se admiten con la apariencia clásica de Windows o con los "
    L"temas desactivados para la aplicación o el widget. Los ajustes se pueden exportar a XML. La "
    L"importación XML carga y guarda inmediatamente los ajustes en el almacenamiento seleccionado "
    L"sin cambiar su tipo. El XML automático es %AppData%\\FortSoft\\CalClock\\settings.xml; al "
    L"escribirlo se elimina HKCU\\SOFTWARE\\FortSoft\\CalClock y al usar el registro se elimina "
    L"el XML automático.\r\n\r\nEl suavizado de fuente ofrece ClearType, GDI y Ninguno.\r\n\r\nEl "
    L"cero inicial ofrece «Sí» (predeterminado), «No, reservar espacio» y «No, sin espacio». «No, "
    L"reservar espacio» oculta el cero y conserva su anchura en la fuente elegida; los demás "
    L"dígitos "
    L"mantienen su posición incluso con fuentes proporcionales. Los relojes de monitor permanecen "
    L"centrados, incluido el espacio reservado. La línea UTC mantiene su propio centrado.",
    L"\r\n\r\nASPETTO E ARCHIVIAZIONE\r\nLe modifiche all’aspetto sono mostrate subito "
    L"nell’anteprima; Annulla elimina le modifiche non applicate e Aspetto predefinito i valori "
    L"del tipo di widget. Gli orologi digitali offrono carattere, antialiasing, colori, opacità, "
    L"margine, larghezza del bordo e sfondo trasparente. Orologi digitali, calendari e pannelli "
    L"condividono quattro stili di bordo; il colore del bordo semplice è selezionabile. Il "
    L"pannello ha caratteri separati per riga superiore, ora e riga inferiore, zero iniziale e "
    L"dimensioni selezionabili del quadrante. I caratteri personalizzati del calendario sono "
    L"supportati con l’aspetto classico di Windows o con i temi disattivati per l’applicazione o "
    L"il widget. Le impostazioni possono essere esportate in XML. L’importazione XML carica e "
    L"salva subito le impostazioni nell’archivio selezionato, senza cambiarne il tipo. L’XML "
    L"automatico è %AppData%\\FortSoft\\CalClock\\settings.xml; scriverlo rimuove "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock, mentre il registro rimuove l’XML "
    L"automatico.\r\n\r\nL’antialiasing del carattere offre ClearType, GDI e Nessuno.\r\n\r\nLo "
    L"zero iniziale offre «Sì» (predefinito), «No, riserva spazio» e «No, senza spazio». «No, "
    L"riserva spazio» "
    L"nasconde lo zero riservandone la larghezza nel carattere scelto; le altre cifre mantengono "
    L"la posizione anche con caratteri proporzionali. Gli orologi sul monitor restano centrati, "
    L"incluso lo spazio riservato. La riga UTC mantiene il proprio allineamento centrale.",
    L"\r\n\r\nWYGLĄD I ZAPIS\r\nZmiany wyglądu są od razu widoczne w podglądzie; Anuluj odrzuca "
    L"niezastosowane zmiany, a Wygląd domyślny wartości danego typu widżetu. Zegary cyfrowe "
    L"oferują czcionkę, wygładzanie, kolory, krycie, odstęp, szerokość ramki i przezroczyste tło. "
    L"Zegary cyfrowe, kalendarze i panele mają te same cztery style ramki; kolor prostej ramki "
    L"można wybrać. Panel ma osobne czcionki górnego wiersza, czasu i dolnego wiersza, zero "
    L"wiodące oraz różne rozmiary tarczy. Własne czcionki kalendarza są obsługiwane przy "
    L"klasycznym wyglądzie systemu Windows lub po wyłączeniu motywów dla aplikacji bądź widżetu. "
    L"Ustawienia można eksportować do XML. Import XML natychmiast wczytuje i zapisuje ustawienia "
    L"w wybranym magazynie, nie zmieniając jego rodzaju. Automatyczny XML to "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml; zapis XML usuwa "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock, a zapis w rejestrze usuwa automatyczny "
    L"XML.\r\n\r\nWygładzanie czcionki oferuje ClearType, GDI i Brak.\r\n\r\nZero wiodące oferuje "
    L"„Tak” (domyślnie), „Nie, zachowaj miejsce” i „Nie, bez miejsca”. „Nie, zachowaj miejsce” "
    L"ukrywa zero, rezerwując "
    L"jego szerokość w wybranej czcionce; pozostałe cyfry zachowują położenie także w czcionkach "
    L"proporcjonalnych. Zegary na monitorze pozostają wyśrodkowane wraz z zarezerwowanym "
    L"miejscem. Wiersz UTC pozostaje osobno wyśrodkowany.",
    L"\r\n\r\nVZHĽAD A UKLADANIE\r\nZmeny vzhľadu sa ihneď ukazujú v náhľade; Zrušiť zruší "
    L"nepoužité zmeny vzhľadu a Predvolený vzhľad hodnoty daného typu widgetu. Digitálne hodiny "
    L"ponúkajú písmo, vyhladzovanie, farby, nepriehľadnosť, odsadenie, šírku rámčeka aj "
    L"priehľadné pozadie. Digitálne hodiny, kalendár a panel majú rovnaké štyri štýly rámčeka; "
    L"pri jednoduchom rámčeku možno zvoliť farbu. Panel má samostatné písma horného riadka, času "
    L"a spodného riadka, úvodnú nulu a voliteľnú veľkosť ciferníka. Vlastné písmo kalendára sa "
    L"používa pri klasickom vzhľade Windows alebo pri vypnutých motívoch aplikácie či widgetu. "
    L"Nastavenia možno exportovať do XML. Import XML okamžite načíta a uloží nastavenia do práve "
    L"zvoleného úložiska; typ úložiska nezmení. Automatické XML je "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml; zápis XML odstráni "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock a ukladanie do registra odstráni automatické "
    L"XML.\r\n\r\nVyhladzovanie písma ponúka ClearType, GDI a Žiadne.\r\n\r\nÚvodná nula ponúka "
    L"„Áno“ (predvolené), „Nie, ponechať miesto“ a „Nie, bez miesta“. Voľba „Nie, ponechať miesto“ "
    L"skryje nulu a rezervuje jej "
    L"šírku vo zvolenom písme; ostatné číslice zostanú na rovnakých miestach aj pri "
    L"proporcionálnom písme. Hodiny na monitore zostávajú zarovnané na stred vrátane "
    L"rezervovaného miesta. Riadok UTC si zachováva vlastné zarovnanie na stred.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live "
    L"preview; Cancel discards unapplied appearance changes and Default appearance restores the "
    L"defaults for that widget type. Digital clocks provide font, smoothing, colours, opacity, "
    L"padding, border width and a transparent background. Digital clocks, calendars and panels "
    L"share four border styles; the single-line border has a selectable colour. The panel has "
    L"separate fonts for its top row, time and bottom row, a leading zero and selectable "
    L"clock-face sizes. Custom calendar fonts are supported with the Windows classic appearance "
    L"or with visual styles turned off for the application or widget. Settings can be exported to "
    L"XML. Importing XML immediately loads and saves the settings to the currently selected "
    L"storage without changing the storage type. Automatic XML is "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. After writing XML, "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock is removed; registry storage removes the automatic "
    L"XML.\r\n\r\nFont antialiasing offers ClearType, GDI, and None.\r\n\r\nLeading zero offers "
    L"“Yes” (default), “No, keep space”, and “No, without space”. “No, keep space” hides the zero "
    L"while reserving its "
    L"width in the selected font; the other digits keep their positions even with proportional "
    L"fonts. Monitor clocks remain centred, including the reserved space. The UTC row keeps its "
    L"own centre alignment.",
    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nAppearance changes are shown immediately in a live "
    L"preview; Cancel discards unapplied appearance changes and Default appearance restores the "
    L"defaults for that widget type. Digital clocks provide font, smoothing, colours, opacity, "
    L"padding, border width and a transparent background. Digital clocks, calendars and panels "
    L"share four border styles; the single-line border has a selectable colour. The panel has "
    L"separate fonts for its top row, time and bottom row, a leading zero and selectable "
    L"clock-face sizes. Custom calendar fonts are supported with the Windows classic appearance "
    L"or with visual styles turned off for the application or widget. Settings can be exported to "
    L"XML. Importing XML immediately loads and saves the settings to the currently selected "
    L"storage without changing the storage type. Automatic XML is "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. After writing XML, "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock is removed; registry storage removes the automatic "
    L"XML.\r\n\r\nFont antialiasing offers ClearType, GDI, and None.\r\n\r\nLeading zero offers "
    L"“Yes” (default), “No, keep space”, and “No, without space”. “No, keep space” hides the zero "
    L"while reserving its "
    L"width in the selected font; the other digits keep their positions even with proportional "
    L"fonts. Monitor clocks remain centred, including the reserved space. The UTC row keeps its "
    L"own centre alignment.",
    L"\r\n\r\nARMAZENAMENTO\r\nAs definições são guardadas no registo em "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock ou num XML em "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Relógios digitais, calendários e painéis "
    L"partilham quatro estilos de moldura; a cor da moldura simples pode ser escolhida. A mudança "
    L"de armazenamento remove apenas os dados CalClock anteriores. As definições podem ser "
    L"exportadas para XML. A importação XML carrega e guarda imediatamente as definições no "
    L"armazenamento selecionado, sem alterar o seu tipo.\r\n\r\nA suavização do tipo de letra "
    L"oferece ClearType, GDI e Nenhuma.\r\n\r\nO zero inicial oferece «Sim» (predefinido), «Não, "
    L"reservar espaço» e «Não, sem espaço». «Não, reservar espaço» oculta o zero e reserva a sua "
    L"largura no tipo "
    L"de letra escolhido; os outros algarismos mantêm a posição mesmo com letras proporcionais. "
    L"Os relógios no monitor permanecem centrados, incluindo o espaço reservado. A linha UTC "
    L"mantém o seu próprio alinhamento ao centro.\r\n\r\nOs tipos de letra personalizados do "
    L"calendário são suportados com o aspeto clássico do Windows ou com os temas desativados para "
    L"a aplicação ou o widget.",
    L"\r\n\r\nLAGRING\r\nInnstillinger lagres i registeret under "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock eller som XML i "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Digitale klokker, kalendere og paneler har "
    L"fire felles kantstiler; fargen på den enkle kanten kan velges. Bytte av lagring fjerner "
    L"bare tidligere CalClock-data. Innstillinger kan eksporteres til XML. XML-import laster inn "
    L"og lagrer innstillingene umiddelbart i valgt lagring uten å endre "
    L"lagringstypen.\r\n\r\nSkriftutjevning tilbyr ClearType, GDI og Ingen.\r\n\r\nInnledende "
    L"null tilbyr «Ja» (standard), «Nei, behold plass» og «Nei, uten plass». «Nei, behold plass» "
    L"skjuler nullen og "
    L"reserverer bredden i valgt skrift; andre sifre beholder plasseringen også med proporsjonale "
    L"skrifter. Monitorklokker forblir sentrert, inkludert reservert plass. UTC-linjen beholder "
    L"sin egen sentrering.\r\n\r\nEgendefinerte kalenderskrifter støttes med klassisk "
    L"Windows-utseende eller når temaer er deaktivert for programmet eller widgeten.",
    L"\r\n\r\nLAGRING\r\nInställningar sparas i registret under "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock eller som XML i "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Digitala klockor, kalendrar och paneler har "
    L"fyra gemensamma kantstilar; färgen på den enkla kanten kan väljas. Byte av lagring tar bara "
    L"bort tidigare CalClock-data. Inställningar kan exporteras till XML. XML-import läser in och "
    L"sparar inställningarna direkt i vald lagring utan att ändra "
    L"lagringstypen.\r\n\r\nTeckensnittsutjämning erbjuder ClearType, GDI och "
    L"Ingen.\r\n\r\nInledande nolla erbjuder ”Ja” (standard), ”Nej, behåll utrymme” och ”Nej, utan "
    L"utrymme”. ”Nej, behåll utrymme” döljer nollan och reserverar dess bredd i valt teckensnitt; "
    L"övriga siffror "
    L"behåller sina positioner även med proportionella teckensnitt. Bildskärmsklockor förblir "
    L"centrerade, inklusive reserverat utrymme. UTC-raden behåller sin egen "
    L"centrering.\r\n\r\nEgna kalenderteckensnitt stöds med Windows klassiska utseende eller när "
    L"teman är avstängda för programmet eller widgeten.",
    L"\r\n\r\nTALLENNUS\r\nAsetukset tallennetaan rekisteriin kohtaan "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock tai XML-tiedostoon kansiossa "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Digitaalikelloilla, kalentereilla ja "
    L"paneeleilla on neljä yhteistä reunatyyliä; yksinkertaisen reunan väri voidaan valita. "
    L"Tallennustavan vaihto poistaa vain aiemmat CalClock-tiedot. Asetukset voi viedä "
    L"XML-tiedostoon. XML-tuonti lataa ja tallentaa asetukset heti valittuun tallennuspaikkaan "
    L"muuttamatta tallennustapaa.\r\n\r\nFontin pehmennyksen vaihtoehdot ovat ClearType, GDI ja "
    L"Ei mitään.\r\n\r\nEtunolla tarjoaa ”Kyllä” (oletus), ”Ei, varaa tila” ja ”Ei, ilman tilaa”. "
    L"”Ei, varaa tila” "
    L"piilottaa nollan mutta varaa sen leveyden valitussa fontissa; muut numerot säilyttävät "
    L"paikkansa myös suhteellisilla fonteilla. Näyttökellot pysyvät keskitettyinä varattu tila "
    L"mukaan lukien. UTC-rivi säilyttää oman keskityksensä.\r\n\r\nKalenterin mukautettuja "
    L"fontteja voi käyttää Windowsin perinteisessä ulkoasussa tai kun sovelluksen tai "
    L"pienoisohjelman teemat on poistettu käytöstä.",
    L"\r\n\r\nLAGRING\r\nIndstillinger gemmes i registreringsdatabasen under "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock eller som XML i "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Digitale ure, kalendere og paneler har fire "
    L"fælles kanttyper; farven på den enkle kant kan vælges. Skift af lager fjerner kun tidligere "
    L"CalClock-data. Indstillinger kan eksporteres til XML. XML-import indlæser og gemmer straks "
    L"indstillingerne i det valgte lager uden at ændre lagertypen.\r\n\r\nSkriftudjævning "
    L"tilbyder ClearType, GDI og Ingen.\r\n\r\nForanstillet nul tilbyder »Ja« (standard), »Nej, "
    L"bevar plads« og »Nej, uden plads«. »Nej, bevar plads« skjuler nullet og reserverer dets "
    L"bredde i den valgte "
    L"skrifttype; øvrige cifre beholder deres placering også med proportionale skrifttyper. "
    L"Skærmure forbliver centrerede inklusive reserveret plads. UTC-linjen bevarer sin egen "
    L"centrering.\r\n\r\nBrugerdefinerede kalenderskrifttyper understøttes med Windows' klassiske "
    L"udseende, eller når temaer er slået fra for programmet eller widgeten.",
    L"\r\n\r\nGEYMSLA\r\nStillingar eru vistaðar í skrásetningu undir "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock eða sem XML í "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Stafrænar klukkur, dagatöl og spjöld hafa "
    L"fjórar sameiginlegar rammagerðir; velja má lit einfalda rammans. Skipti um geymslu "
    L"fjarlægja aðeins eldri CalClock-gögn. Hægt er að flytja stillingar út sem XML. "
    L"Innflutningur XML hleður og vistar stillingarnar strax í valinni geymslu án þess að breyta "
    L"gerð hennar.\r\n\r\nLeturjöfnun býður upp á ClearType, GDI og Engin.\r\n\r\nNúll fremst "
    L"býður upp á „Já“ (sjálfgefið), „Nei, halda plássi“ og „Nei, án pláss“. „Nei, halda plássi“ "
    L"felur núllið en tekur "
    L"frá breidd þess í völdu letri; aðrir tölustafir halda stöðu sinni jafnvel með misbreiðu "
    L"letri. Skjáklukkur haldast miðjaðar með fráteknu plássi. UTC-línan heldur eigin "
    L"miðjun.\r\n\r\nNota má sérsniðið letur í dagatali með hefðbundnu útliti Windows eða þegar "
    L"slökkt er á þemum fyrir forritið eða græjuna.",
    L"\r\n\r\nDEPOLAMA\r\nAyarlar HKCU\\SOFTWARE\\FortSoft\\CalClock altındaki kayıt defterinde "
    L"veya %AppData%\\FortSoft\\CalClock\\settings.xml içindeki XML dosyasında saklanır. Dijital "
    L"saatler, takvimler ve paneller aynı dört kenarlık stilini kullanır; basit kenarlığın rengi "
    L"seçilebilir. Depolamayı değiştirmek yalnızca önceki CalClock verilerini kaldırır. Ayarlar "
    L"XML olarak dışa aktarılabilir. XML içe aktarma, depolama türünü değiştirmeden ayarları "
    L"hemen yükler ve seçili depolamaya kaydeder.\r\n\r\nYazı tipi kenar yumuşatma seçenekleri "
    L"ClearType, GDI ve Yok şeklindedir.\r\n\r\nBaştaki sıfır için “Evet” (varsayılan), “Hayır, yer"
    L" ayır” ve “Hayır, boşluksuz” seçenekleri vardır. “Hayır, yer ayır”, sıfırı gizleyip seçilen "
    L"yazı tipindeki "
    L"genişliğini korur; diğer rakamlar orantılı yazı tiplerinde bile konumlarını korur. Monitör "
    L"saatleri ayrılan alan dâhil ortalanır. UTC satırı kendi orta hizalamasını "
    L"korur.\r\n\r\nÖzel takvim yazı tipleri, Windows klasik görünümünde veya uygulama ya da araç "
    L"için temalar kapatıldığında desteklenir.",
    L"\r\n\r\nIlme ja salvestamine\r\nIlme muutused on kohe eelvaates näha. Loobu hülgab "
    L"rakendamata muudatused ja Vaikeilme taastab vidinatüübi vaikesätted. Digitaalkell toetab "
    L"fonti, silumist, värve, läbipaistmatust, siseveerist, äärise laiust ja läbipaistvat tausta. "
    L"Kellad, kalendrid ja paneelid jagavad nelja ääriselaadi; ühekordse äärise värvi saab "
    L"valida. Paneelil on eraldi fondid ülemisele reale, kellaajale ja alumisele reale, algusnull "
    L"ning valitavad sihverplaadisuurused. Kujundused ja silumine määratakse rakendusele ja igale "
    L"vidinale eraldi. Kohandatud kalendrifonte saab kasutada Windowsi klassikalise ilmega või "
    L"siis, kui rakenduse või vidina kujundused on välja lülitatud.\r\n\r\nSätteid saab "
    L"eksportida XML-i. Import laadib ja salvestab sätted kohe praegusesse salvestuskohta selle "
    L"tüüpi muutmata. Automaatne XML asub failis %AppData%\\FortSoft\\CalClock\\settings.xml. "
    L"XML-i kirjutamine eemaldab võtme HKCU\\SOFTWARE\\FortSoft\\CalClock; registrisse "
    L"salvestamine eemaldab automaatse XML-i.\r\n\r\nFondi silumine pakub ClearType, GDI ja "
    L"Puudub. Algusnull pakub „Jah“ (vaikimisi), „Ei, säilita ruum“ ja „Ei, ilma ruumita“. „Ei, "
    L"säilita ruum“ peidab "
    L"nulli, kuid reserveerib selle laiuse valitud fondis; ülejäänud numbrid säilitavad asukoha "
    L"ka proportsionaalse fondiga. Ekraanikella keskjoondus arvestab reserveeritud ruumi. "
    L"UTC-real on oma keskjoondus.",
    L"\r\n\r\nCuma agus stóras\r\nFeictear athruithe cuma sa réamhamharc láithreach. Caitheann "
    L"Cealaigh athruithe nach bhfuil curtha i bhfeidhm i leataobh; athchóiríonn Cuma "
    L"réamhshocraithe réamhshocruithe an chineáil. Tá cló, frithailiasáil, dathanna, teimhneacht, "
    L"spásáil inmheánach, leithead imlíne agus cúlra trédhearcach ar fáil do chloig dhigiteacha. "
    L"Tá ceithre stíl imlíne ag cloig, féilirí agus painéil; is féidir dath na himlíne aonlíne a "
    L"roghnú. Tá clónna ar leith ag an bpainéal don tsraith uachtarach, don am agus don tsraith "
    L"íochtarach, chomh maith le nialas tosaigh agus méideanna aghaidhe. Socraítear téamaí agus "
    L"frithailiasáil don fheidhmchlár agus do gach giuirléid. Tacaítear le clónna saincheaptha "
    L"féilire le cuma chlasaiceach Windows nó nuair atá téamaí múchta don fheidhmchlár nó don "
    L"ghiuirléid.\r\n\r\nIs féidir socruithe a easpórtáil mar XML. Lódálann agus sábhálann "
    L"iompórtáil XML na socruithe láithreach sa stóras roghnaithe gan a chineál a athrú. Is é "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml an XML uathoibríoch. Tar éis XML a scríobh, "
    L"baintear HKCU\\SOFTWARE\\FortSoft\\CalClock; baineann stóráil sa chlárlann an XML "
    L"uathoibríoch.\r\n\r\nTugann Frithailiasáil cló ClearType, GDI agus Gan frithailiasáil. "
    L"Tugann Nialas tosaigh “Tá” (réamhshocrú), “Níl, coinnigh an spás” agus “Níl, gan spás”. "
    L"Folaíonn “Níl, coinnigh an spás” an nialas ach coimeádann sé a leithead sa chló roghnaithe; "
    L"fanann digití "
    L"eile ina n-áit le clónna comhréireacha freisin. Fanann cloig scáileáin lárnaithe agus an "
    L"spás sin san áireamh. Tá lárnú ar leith ag sraith UTC.",
    L"\r\n\r\nIšvaizda ir saugojimas\r\nIšvaizdos pakeitimai iškart matomi peržiūroje. Atšaukti "
    L"atmeta nepritaikytus pakeitimus, Numatytoji išvaizda atkuria šio tipo valdiklio "
    L"numatytąsias reikšmes. Skaitmeniniai laikrodžiai siūlo šriftą, glodinimą, spalvas, "
    L"nepermatomumą, vidinę paraštę, kraštinės plotį ir permatomą foną. Laikrodžiai, kalendoriai "
    L"ir skydeliai turi keturis bendrus kraštinių stilius; viengubai kraštinei galima pasirinkti "
    L"spalvą. Skydelis turi atskirus viršutinės eilutės, laiko ir apatinės eilutės šriftus, "
    L"pradinį nulį ir ciferblatų dydžius. Temos ir glodinimas nustatomi programai ir kiekvienam "
    L"valdikliui. Pasirinktinius kalendoriaus šriftus galima naudoti su klasikine „Windows“ "
    L"išvaizda arba išjungus programos ar valdiklio temas.\r\n\r\nParametrus galima eksportuoti į "
    L"XML. Importas iškart įkelia ir įrašo parametrus į pasirinktą saugyklą nekeisdamas jos tipo. "
    L"Automatinis XML yra %AppData%\\FortSoft\\CalClock\\settings.xml. Įrašius XML pašalinamas "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock raktas; įrašymas į registrą pašalina automatinį "
    L"XML.\r\n\r\nŠrifto glodinimas siūlo ClearType, GDI ir Nėra. Pradinis nulis siūlo „Taip“ "
    L"(numatyta), „Ne, palikti vietą“ ir „Ne, be vietos“. „Ne, palikti vietą“ slepia nulį, bet "
    L"rezervuoja jo plotį "
    L"pasirinktame šrifte; kiti skaitmenys nepajuda ir naudojant proporcinį šriftą. Ekrano "
    L"laikrodžių centravimas įskaito rezervuotą vietą. UTC eilutė centruojama atskirai.",
    L"\r\n\r\nIzskats un glabāšana\r\nIzskata izmaiņas uzreiz redzamas priekšskatījumā. Atcelt "
    L"atmet nelietotās izmaiņas, Noklusējuma izskats atjauno logrīka tipa noklusējumus. Digitālie "
    L"pulksteņi piedāvā fontu, nogludināšanu, krāsas, necaurspīdīgumu, iekšējo atkāpi, apmales "
    L"platumu un caurspīdīgu fonu. Pulksteņiem, kalendāriem un paneļiem ir četri kopīgi apmales "
    L"stili; vienas līnijas apmalei var izvēlēties krāsu. Panelim ir atsevišķi augšējās rindas, "
    L"laika un apakšējās rindas fonti, sākuma nulle un ciparnīcu lielumi. Dizainus un "
    L"nogludināšanu iestata programmai un katram logrīkam. Pielāgotus kalendāra fontus var "
    L"izmantot ar Windows klasisko izskatu vai tad, ja lietotnei vai logrīkam ir izslēgti "
    L"dizaini.\r\n\r\nIestatījumus var eksportēt XML. Imports tos uzreiz ielādē un saglabā "
    L"izvēlētajā krātuvē, nemainot tās tipu. Automātiskais XML ir "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. XML ierakstīšana noņem "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock atslēgu; saglabāšana reģistrā noņem automātisko "
    L"XML.\r\n\r\nFonta nogludināšana piedāvā ClearType, GDI un Nav. Sākuma nulle piedāvā “Jā” "
    L"(noklusējums), “Nē, saglabāt vietu” un “Nē, bez vietas”. “Nē, saglabāt vietu” slēpj nulli, "
    L"rezervējot tās "
    L"platumu izvēlētajā fontā; pārējie cipari paliek vietā arī proporcionālā fontā. Ekrāna "
    L"pulksteņi tiek centrēti, ieskaitot rezervēto vietu. UTC rindai ir atsevišķa centrēšana.",
    L"\r\n\r\nMegjelenés és tárolás\r\nA megjelenés változásai azonnal láthatók az előnézetben. A "
    L"Mégse elveti az alkalmazatlan változtatásokat, az Alapértelmezett megjelenés visszaállítja "
    L"a típus alapértékeit. A digitális órához betűtípus, élsimítás, színek, átlátszatlanság, "
    L"belső margó, szegélyvastagság és átlátszó háttér választható. Az órák, naptárak és panelek "
    L"négy közös szegélystílust használnak; az egysoros szegély színezhető. A panel felső "
    L"sorának, idejének és alsó sorának külön betűtípusa van, vezető nullával és "
    L"számlapméretekkel. A témák és élsimítás a programhoz és minden minialkalmazáshoz külön "
    L"adhatók meg. Egyéni naptárbetűtípusok a Windows klasszikus megjelenésével, illetve az "
    L"alkalmazás vagy a minialkalmazás témáinak kikapcsolásával használhatók.\r\n\r\nA "
    L"beállítások XML-be exportálhatók. Az importálás azonnal betölti és a kijelölt tárolóba "
    L"menti őket, a tárolótípus megváltoztatása nélkül. Az automatikus XML helye "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Az XML írása törli a "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock kulcsot; a beállításjegyzékbe mentés törli az "
    L"automatikus XML-t.\r\n\r\nA Betűtípus élsimítása lehet ClearType, GDI vagy Nincs. A Vezető "
    L"nulla választásai: „Igen” (alapértelmezett), „Nem, hely megtartása” és „Nem, hely nélkül”. A "
    L"„Nem, hely megtartása” elrejti a nullát, de fenntartja a szélességét; a többi számjegy "
    L"arányos "
    L"betűtípusnál sem mozdul el. A képernyőórák középre igazítása ezt a helyet is figyelembe "
    L"veszi. Az UTC-sor külön igazodik középre.",
    L"\r\n\r\nDehra u ħażna\r\nIl-bidliet fid-dehra jidhru minnufih fil-previżjoni. Ikkanċella "
    L"jarmi l-bidliet mhux applikati, Dehra default jerġa’ jġib il-valuri default tat-tip. "
    L"L-arloġġi diġitali joffru font, anti-aliasing, kuluri, opaċità, spazju intern, wisa’ "
    L"tal-bordura u sfond trasparenti. L-arloġġi, il-kalendarji u l-panewijiet għandhom erba’ "
    L"stili tal-bordura komuni; il-bordura b’linja waħda għandha kulur magħżul. Il-panew għandu "
    L"fonts separati għar-ringiela ta’ fuq, il-ħin u r-ringiela t’isfel, żero fil-bidu u "
    L"daqsijiet tal-uċuħ. It-temi u l-anti-aliasing jiġu ssettjati għall-programm u għal kull "
    L"widget. Il-fonts personalizzati tal-kalendarju huma appoġġjati bid-dehra klassika ta’ "
    L"Windows jew meta t-temi jkunu mitfija għall-applikazzjoni jew il-widget.\r\n\r\nIs-settings "
    L"jistgħu jiġu esportati f’XML. L-importazzjoni tgħabbi u tissejvja s-settings minnufih "
    L"fil-ħażna magħżula mingħajr ma tbiddel it-tip tagħha. L-XML awtomatiku huwa "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Il-kitba tal-XML tneħħi ċ-ċavetta "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; il-ħażna fir-reġistru tneħħi l-XML "
    L"awtomatiku.\r\n\r\nAnti-aliasing tal-font joffri ClearType, GDI u Xejn. Żero fil-bidu "
    L"joffri “Iva” (default), “Le, żomm l-ispazju” u “Le, bla spazju”. “Le, żomm l-ispazju” jaħbi "
    L"ż-żero iżda "
    L"jirriżerva l-wisa’ tiegħu fil-font magħżul; iċ-ċifri l-oħra jibqgħu f’posthom anki b’fonts "
    L"proporzjonali. L-arloġġi tal-iskrin jibqgħu ċċentrati inkluż l-ispazju riżervat. "
    L"Ir-ringiela UTC tiġi ċċentrata separatament.",
    L"\r\n\r\nVormgeving en opslag\r\nWijzigingen in de vormgeving verschijnen direct in het "
    L"voorbeeld. Annuleren verwerpt niet-toegepaste wijzigingen; Standaardvormgeving herstelt de "
    L"standaardwaarden voor dat type. Digitale klokken bieden lettertypen, vereffening, kleuren, "
    L"dekking, binnenmarge, randbreedte en een transparante achtergrond. Klokken, kalenders en "
    L"panelen delen vier randstijlen; een enkele rand heeft een instelbare kleur. Een paneel "
    L"heeft aparte lettertypen voor de bovenste rij, tijd en onderste rij, een voorloopnul en "
    L"wijzerplaatgroottes. Thema’s en lettertypevereffening worden voor de toepassing en elke "
    L"widget ingesteld. Aangepaste kalenderlettertypen worden ondersteund bij de klassieke "
    L"Windows-weergave of als thema’s voor de toepassing of widget zijn "
    L"uitgeschakeld.\r\n\r\nInstellingen kunnen naar XML worden geëxporteerd. Importeren laadt en "
    L"bewaart de instellingen direct in de gekozen opslag zonder het opslagtype te veranderen. "
    L"Automatische XML staat in %AppData%\\FortSoft\\CalClock\\settings.xml. Na XML-opslag wordt "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock verwijderd; opslag in het register verwijdert de "
    L"automatische XML.\r\n\r\nLettertypevereffening biedt ClearType, GDI en Geen. Voorloopnul "
    L"biedt “Ja” (standaard), “Nee, ruimte behouden” en “Nee, zonder ruimte”. “Nee, ruimte "
    L"behouden” verbergt de "
    L"nul maar reserveert de breedte in het gekozen lettertype; andere cijfers behouden hun "
    L"positie, ook bij proportionele lettertypen. Schermklokken blijven gecentreerd inclusief die "
    L"ruimte. De UTC-rij heeft een eigen centrering.",
    L"\r\n\r\nAspect și stocare\r\nModificările de aspect se văd imediat în previzualizare. "
    L"Anulare respinge modificările neaplicate, Aspect implicit restabilește valorile implicite "
    L"ale tipului. Ceasurile digitale oferă font, netezire, culori, opacitate, spațiere "
    L"interioară, grosime a bordurii și fundal transparent. Ceasurile, calendarele și panourile "
    L"au patru stiluri comune de bordură; bordura simplă are culoare configurabilă. Panoul are "
    L"fonturi separate pentru rândul superior, oră și rândul inferior, zero inițial și dimensiuni "
    L"ale cadranelor. Temele și netezirea sunt configurate pentru aplicație și fiecare widget. "
    L"Fonturile personalizate ale calendarului sunt acceptate cu aspectul clasic Windows sau când "
    L"temele sunt dezactivate pentru aplicație ori widget.\r\n\r\nSetările pot fi exportate în "
    L"XML. Importul încarcă și salvează imediat setările în stocarea aleasă fără a-i schimba "
    L"tipul. XML-ul automat este %AppData%\\FortSoft\\CalClock\\settings.xml. Scrierea XML "
    L"elimină cheia HKCU\\SOFTWARE\\FortSoft\\CalClock; stocarea în registry elimină XML-ul "
    L"automat.\r\n\r\nNetezire font oferă ClearType, GDI și Fără. Zero inițial oferă „Da” "
    L"(implicit), „Nu, păstrează spațiul” și „Nu, fără spațiu”. „Nu, păstrează spațiul” ascunde "
    L"zero, rezervând lățimea "
    L"lui în fontul ales; celelalte cifre rămân pe poziție și cu fonturi proporționale. Ceasurile "
    L"pe ecran rămân centrate incluzând spațiul rezervat. Rândul UTC are centrare separată.",
    L"\r\n\r\nΕμφάνιση και αποθήκευση\r\nΟι αλλαγές εμφάνισης φαίνονται αμέσως στην "
    L"προεπισκόπηση. Το Άκυρο απορρίπτει μη εφαρμοσμένες αλλαγές· η Προεπιλεγμένη εμφάνιση "
    L"επαναφέρει τις προεπιλογές του τύπου. Τα ψηφιακά ρολόγια προσφέρουν γραμματοσειρά, "
    L"εξομάλυνση, χρώματα, αδιαφάνεια, εσωτερικό περιθώριο, πλάτος περιγράμματος και διαφανές "
    L"φόντο. Ρολόγια, ημερολόγια και πλαίσια έχουν τέσσερα κοινά στυλ περιγράμματος· η μονή "
    L"γραμμή έχει επιλέξιμο χρώμα. Το πλαίσιο έχει χωριστές γραμματοσειρές επάνω γραμμής, ώρας "
    L"και κάτω γραμμής, αρχικό μηδενικό και μεγέθη καντράν. Θέματα και εξομάλυνση ορίζονται για "
    L"την εφαρμογή και κάθε στοιχείο. Οι προσαρμοσμένες γραμματοσειρές ημερολογίου υποστηρίζονται "
    L"με την κλασική εμφάνιση των Windows ή όταν τα θέματα είναι απενεργοποιημένα για την "
    L"εφαρμογή ή το γραφικό στοιχείο.\r\n\r\nΟι ρυθμίσεις εξάγονται σε XML. Η εισαγωγή τις "
    L"φορτώνει και τις αποθηκεύει αμέσως στον επιλεγμένο χώρο χωρίς αλλαγή τύπου αποθήκευσης. Το "
    L"αυτόματο XML είναι %AppData%\\FortSoft\\CalClock\\settings.xml. Η εγγραφή XML αφαιρεί το "
    L"κλειδί HKCU\\SOFTWARE\\FortSoft\\CalClock· η αποθήκευση στο μητρώο αφαιρεί το αυτόματο "
    L"XML.\r\n\r\nΗ Εξομάλυνση γραμματοσειράς προσφέρει ClearType, GDI και Καμία. Το Αρχικό "
    L"μηδενικό προσφέρει «Ναι» (προεπιλογή), «Όχι, διατήρηση χώρου» και «Όχι, χωρίς χώρο». Η "
    L"επιλογή «Όχι, διατήρηση χώρου» "
    L"κρύβει το μηδενικό αλλά δεσμεύει το πλάτος του στην επιλεγμένη γραμματοσειρά· τα άλλα ψηφία "
    L"μένουν στη θέση τους και με αναλογικές γραμματοσειρές. Το κεντράρισμα των ρολογιών οθόνης "
    L"περιλαμβάνει τον δεσμευμένο χώρο. Η γραμμή UTC κεντράρεται χωριστά.",
    L"\r\n\r\nIzgled i čuvanje postavki\r\nPromjene izgleda odmah se prikazuju u pregledu. Otkaži "
    L"odbacuje neprimijenjene promjene, a Podrazumijevani izgled vraća podrazumijevane "
    L"vrijednosti za tu vrstu vidžeta. Digitalni satovi nude font, izglađivanje, boje, "
    L"neprozirnost, unutrašnji razmak, širinu obruba i prozirnu pozadinu. Digitalni satovi, "
    L"kalendari i ploče dijele četiri stila obruba; boja jednostrukog obruba može se odabrati. "
    L"Ploča ima odvojene fontove gornjeg reda, vremena i donjeg reda, početnu nulu i odabir "
    L"veličine brojčanika. Prilagođeni fontovi kalendara podržani su uz klasični izgled Windowsa "
    L"ili kada su teme isključene za program ili vidžet. Postavke se mogu izvesti u XML. Uvoz "
    L"XML-a odmah učitava i čuva postavke u odabrano spremište bez promjene njegove vrste. "
    L"Automatska XML datoteka je %AppData%\\FortSoft\\CalClock\\settings.xml. Nakon zapisivanja "
    L"XML-a uklanja se ključ HKCU\\SOFTWARE\\FortSoft\\CalClock; čuvanje u registar uklanja "
    L"automatsku XML datoteku.\r\n\r\nIzglađivanje fonta nudi ClearType, GDI i Nema. Početna nula "
    L"nudi „Da“ (podrazumijevano), „Ne, zadrži razmak“ i „Ne, bez razmaka“. „Ne, zadrži razmak“ "
    L"skriva nulu, ali "
    L"rezervira njezinu širinu u odabranom fontu, pa ostale znamenke zadržavaju položaj i kod "
    L"proporcionalnih fontova. Satovi na ekranu ostaju centrirani, uključujući rezervirani "
    L"razmak. Red UTC ima vlastito centriranje.",
    L"\r\n\r\nIzgled i spremanje postavki\r\nPromjene izgleda odmah se prikazuju u pretpregledu. "
    L"Odustani odbacuje neprimijenjene promjene, a Zadani izgled vraća zadane vrijednosti za tu "
    L"vrstu widgeta. Digitalni satovi nude font, izglađivanje, boje, neprozirnost, unutarnji "
    L"razmak, širinu obruba i prozirnu pozadinu. Digitalni satovi, kalendari i ploče dijele "
    L"četiri stila obruba; boja jednostrukog obruba može se odabrati. Ploča ima odvojene fontove "
    L"gornjeg retka, vremena i donjeg retka, početnu nulu i odabir veličine brojčanika. "
    L"Prilagođeni fontovi kalendara podržani su uz klasični izgled Windowsa ili kada su teme "
    L"isključene za program ili widget. Postavke se mogu izvesti u XML. Uvoz XML-a odmah učitava "
    L"i sprema postavke u odabrano spremište bez promjene njegove vrste. Automatska XML datoteka "
    L"je %AppData%\\FortSoft\\CalClock\\settings.xml. Nakon zapisivanja XML-a uklanja se ključ "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; spremanje u registar uklanja automatsku XML "
    L"datoteku.\r\n\r\nIzglađivanje fonta nudi ClearType, GDI i Nema. Početna nula nudi „Da” "
    L"(zadano), „Ne, zadrži razmak” i „Ne, bez razmaka”. „Ne, zadrži razmak” skriva nulu, ali "
    L"rezervira njezinu "
    L"širinu u odabranom fontu, pa ostale znamenke zadržavaju položaj i kod proporcionalnih "
    L"fontova. Satovi na zaslonu ostaju centrirani, uključujući rezervirani razmak. Redak UTC ima "
    L"vlastito centriranje.",
    L"\r\n\r\nVidez in shranjevanje\r\nSpremembe videza so vidne takoj v predogledu. Prekliči "
    L"zavrže neuporabljene spremembe, Privzeti videz pa obnovi privzete vrednosti vrste gradnika. "
    L"Digitalne ure ponujajo pisavo, glajenje, barve, neprosojnost, notranji odmik, širino obrobe "
    L"in prosojno ozadje. Digitalne ure, koledarji in plošče imajo štiri skupne sloge obrob; "
    L"enojni obrobi lahko določite barvo. Plošča ima ločene pisave zgornje vrstice, časa in "
    L"spodnje vrstice, vodilno ničlo in izbiro velikosti številčnic. Teme in glajenje se določijo "
    L"za program in vsak gradnik. Pisavo koledarja po meri lahko uporabljate pri klasičnem videzu "
    L"sistema Windows ali ko so teme izključene za program ali gradnik. Nastavitve je mogoče "
    L"izvoziti v XML. Uvoz XML takoj naloži in shrani nastavitve v izbrano shrambo, ne da bi "
    L"spremenil njeno vrsto. Samodejni XML je %AppData%\\FortSoft\\CalClock\\settings.xml. Zapis "
    L"XML odstrani ključ HKCU\\SOFTWARE\\FortSoft\\CalClock; shranjevanje v register odstrani "
    L"samodejni XML.\r\n\r\nGlajenje pisave ponuja ClearType, GDI in Brez. Vodilna ničla ponuja "
    L"»Da« (privzeto), »Ne, ohrani prostor« in »Ne, brez prostora«. »Ne, ohrani prostor« skrije "
    L"ničlo in "
    L"rezervira njeno širino v izbrani pisavi; druge števke ostanejo na mestu tudi pri "
    L"proporcionalnih pisavah. Ure na zaslonu ostanejo sredinsko poravnane z upoštevanjem "
    L"rezerviranega prostora. Vrstica UTC ima lastno sredinsko poravnavo.",
    L"\r\n\r\nIzgled i čuvanje\r\nPromjene izgleda odmah se vide u pregledu. Otkaži odbacuje "
    L"neprimijenjene promjene, a Podrazumijevani izgled vraća podrazumijevane vrijednosti za "
    L"vrstu vidžeta. Digitalni satovi nude font, umekšavanje, boje, neprozirnost, unutrašnji "
    L"razmak, širinu okvira i providnu pozadinu. Digitalni satovi, kalendari i paneli dijele "
    L"četiri stila okvira; jednostrukom okviru može se birati boja. Panel ima zasebne fontove za "
    L"gornji red, vrijeme i donji red, vodeću nulu i izbor veličine brojčanika. Teme i "
    L"umekšavanje zadaju se za program i svaki vidžet. Prilagođeni fontovi kalendara podržani su "
    L"uz klasični izgled Windows-a ili kada su teme isključene za program ili vidžet. Podešavanja "
    L"se mogu izvesti u XML. Uvoz XML-a odmah učitava i čuva podešavanja u izabranom skladištu "
    L"bez promjene njegove vrste. Automatski XML je %AppData%\\FortSoft\\CalClock\\settings.xml. "
    L"Po zapisivanju XML-a uklanja se ključ HKCU\\SOFTWARE\\FortSoft\\CalClock; čuvanje u "
    L"registru uklanja automatski XML.\r\n\r\nUmekšavanje fonta nudi ClearType, GDI i Nema. "
    L"Vodeća nula nudi „Da” (podrazumijevano), „Ne, zadrži razmak” i „Ne, bez razmaka”. „Ne, zadrži"
    L" razmak” "
    L"skriva nulu, ali čuva njenu širinu u izabranom fontu; ostale cifre zadržavaju položaje i "
    L"kod proporcionalnih fontova. Satovi na monitoru ostaju centrirani sa uračunatim razmakom. "
    L"Red UTC ima sopstveno centriranje.",
    L"\r\n\r\nВыгляд і захоўванне\r\nЗмены выгляду адразу бачныя ў папярэднім праглядзе. "
    L"«Скасаваць» адхіляе неўжытыя змены, а «Прадвызначаны выгляд» вяртае прадвызначаныя значэнні "
    L"тыпу віджэта. Лічбавыя гадзіннікі прапануюць шрыфт, згладжванне, колеры, непразрыстасць, "
    L"унутраны водступ, таўшчыню рамкі і празрысты фон. Гадзіннікі, календары і панэлі маюць "
    L"чатыры агульныя стылі рамкі; для адзінарнай рамкі выбіраецца колер. Панэль мае асобныя "
    L"шрыфты верхняга радка, часу і ніжняга радка, пачатковы нуль і выбар памераў цыферблатаў. "
    L"Тэмы і згладжванне задаюцца для праграмы і кожнага віджэта. Уласныя шрыфты календара "
    L"падтрымліваюцца пры класічным выглядзе Windows або калі тэмы адключаныя для праграмы ці "
    L"віджэта. Налады можна экспартаваць у XML. Імпарт XML адразу загружае і захоўвае налады ў "
    L"бягучым сховішчы, не змяняючы яго тып. Аўтаматычны файл XML — "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Пасля запісу XML ключ "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock выдаляецца; захоўванне ў рэестры выдаляе аўтаматычны "
    L"XML.\r\n\r\nЗгладжванне шрыфту прапануе ClearType, GDI і «Няма». «Пачатковы нуль» мае "
    L"варыянты «Так» (прадвызначаны), «Не, пакідаць месца» і «Не, без месца». «Не, пакідаць месца» "
    L"хавае нуль, але рэзервуе яго шырыню ў выбраным шрыфце; астатнія лічбы захоўваюць пазіцыі і "
    L"ў прапарцыянальных шрыфтах. Гадзіннікі на маніторы застаюцца па цэнтры з улікам "
    L"зарэзерваванага месца. Радок UTC мае асобнае цэнтраванне.",
    L"\r\n\r\nИзглед и съхраняване\r\nПромените на изгледа се показват веднага в предварителния "
    L"преглед. „Отказ“ отхвърля неприложените промени, а „Изглед по подразбиране“ връща "
    L"стандартните стойности за вида модул. Цифровите часовници предлагат шрифт, изглаждане, "
    L"цветове, непрозрачност, вътрешен отстъп, дебелина на рамката и прозрачен фон. Часовниците, "
    L"календарите и панелите имат четири общи стила на рамката; за единичната рамка се избира "
    L"цвят. Панелът има отделни шрифтове за горния ред, часа и долния ред, водеща нула и избор на "
    L"размери на циферблатите. Темите и изглаждането се задават за програмата и всеки модул. "
    L"Персонализираните шрифтове на календара се поддържат при класически облик на Windows или "
    L"когато темите са изключени за приложението или модула. Настройките могат да се експортират "
    L"в XML. Импортирането веднага зарежда и записва настройките в текущото хранилище, без да "
    L"сменя типа му. Автоматичният XML е %AppData%\\FortSoft\\CalClock\\settings.xml. След запис "
    L"на XML ключът HKCU\\SOFTWARE\\FortSoft\\CalClock се премахва; записът в регистъра премахва "
    L"автоматичния XML.\r\n\r\nИзглаждането предлага ClearType, GDI и „Няма“. „Водеща нула“ "
    L"предлага „Да“ (по подразбиране), „Не, запази мястото“ и „Не, без място“. „Не, запази мястото“"
    L" "
    L"скрива нулата, но запазва ширината ѝ в избрания шрифт; другите цифри остават на място дори "
    L"при пропорционални шрифтове. Часовниците на монитор остават центрирани с включено запазено "
    L"място. Редът UTC има отделно центриране.",
    L"\r\n\r\nИзглед и зачувување\r\nПромените на изгледот се гледаат веднаш во прегледот. "
    L"„Откажи“ ги отфрла неприменетите промени, а „Стандарден изглед“ ги враќа стандардните "
    L"вредности за видот на виџетот. Дигиталните часовници нудат фонт, измазнување, бои, "
    L"непроѕирност, внатрешна маргина, дебелина на рамката и проѕирна заднина. Часовниците, "
    L"календарите и панелите имаат четири заеднички стила на рамка; за еднолиниската рамка се "
    L"избира боја. Панелот има посебни фонтови за горниот ред, времето и долниот ред, водечка "
    L"нула и избор на големини на бројчаниците. Темите и измазнувањето се поставуваат за "
    L"програмата и секој виџет. Приспособените фонтови на календарот се поддржани со класичниот "
    L"изглед на Windows или кога темите се исклучени за апликацијата или виџетот. Поставките може "
    L"да се извезат во XML. Увозот XML веднаш ги вчитува и зачувува во тековното складиште без да "
    L"го менува неговиот вид. Автоматскиот XML е %AppData%\\FortSoft\\CalClock\\settings.xml. По "
    L"запишување XML се отстранува клучот HKCU\\SOFTWARE\\FortSoft\\CalClock; чувањето во "
    L"регистарот го отстранува автоматскиот XML.\r\n\r\nИзмазнувањето на фонтот нуди ClearType, "
    L"GDI и „Нема“. „Водечка нула“ нуди „Да“ (стандардно), „Не, зачувај место“ и „Не, без место“. "
    L"„Не, зачувај место“ ја крие нулата, но ја задржува нејзината ширина во избраниот фонт; "
    L"другите "
    L"цифри остануваат на место и кај пропорционални фонтови. Часовниците на монитор остануваат "
    L"центрирани со вклучено резервирано место. Редот UTC има свое центрирање.",
    L"\r\n\r\nИзглед и чување\r\nПромене изгледа одмах се виде у прегледу. Откажи одбацује "
    L"непримењене промене, а Подразумевани изглед враћа подразумеване вредности за врсту виџета. "
    L"Дигитални сатови нуде фонт, умекшавање, боје, непрозирност, унутрашњи размак, ширину оквира "
    L"и провидну позадину. Дигитални сатови, календари и панели деле четири стила оквира; "
    L"једноструком оквиру може се бирати боја. Панел има засебне фонтове за горњи ред, време и "
    L"доњи ред, водећу нулу и избор величине бројчаника. Теме и умекшавање задају се за програм и "
    L"сваки виџет. Прилагођени фонтови календара подржани су уз класични изглед Windows-а или "
    L"када су теме искључене за програм или виџет. Подешавања се могу извести у XML. Увоз XML-а "
    L"одмах учитава и чува подешавања у изабраном складишту без промене његове врсте. Аутоматски "
    L"XML је %AppData%\\FortSoft\\CalClock\\settings.xml. По записивању XML-а уклања се кључ "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock; чување у регистру уклања аутоматски "
    L"XML.\r\n\r\nУмекшавање фонта нуди ClearType, GDI и Нема. Водећа нула нуди „Да“ "
    L"(подразумевано), „Не, задржи размак“ и „Не, без размака“. „Не, задржи размак“ скрива нулу, "
    L"али чува њену "
    L"ширину у изабраном фонту; остале цифре задржавају положаје и код пропорционалних фонтова. "
    L"Сатови на монитору остају центрирани са урачунатим размаком. Ред UTC има сопствено "
    L"центрирање.",
    L"\r\n\r\nВИГЛЯД І ЗБЕРІГАННЯ НАЛАШТУВАНЬ\r\nЗміни вигляду одразу відображаються в "
    L"попередньому перегляді. «Скасувати» скасовує незастосовані зміни вигляду, а «Типовий "
    L"вигляд» повертає типові параметри для цього виду віджета. У цифрових годинниках можна "
    L"налаштувати шрифт, згладжування, кольори, непрозорість, внутрішній відступ, товщину рамки й "
    L"прозоре тло. Цифрові годинники, календарі та панелі мають чотири спільні стилі рамки; для "
    L"однолінійної рамки можна вибрати колір. Панель має окремі шрифти верхнього рядка, часу й "
    L"нижнього рядка, показ початкового нуля та вибір розмірів циферблатів. Власні шрифти "
    L"календаря підтримуються за класичного вигляду Windows або коли теми вимкнено для програми "
    L"чи віджета. Налаштування можна експортувати до XML. Імпорт XML одразу завантажує й зберігає "
    L"налаштування в поточному сховищі, не змінюючи його типу. Автоматичне сховище XML — "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. Після запису XML розділ "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock видаляється; вибір зберігання в реєстрі видаляє "
    L"автоматичний файл XML.\r\n\r\nДля згладжування шрифту доступні ClearType, GDI та "
    L"«Немає».\r\n\r\nПараметр «Початковий нуль» має значення «Так» (типове), «Ні, залишати місце» "
    L"та «Ні, без місця». «Ні, залишати місце» приховує нуль, але резервує його ширину у вибраному "
    L"шрифті; решта цифр залишається на місці навіть у пропорційних шрифтах. Годинники на "
    L"моніторі зберігають центрування з урахуванням зарезервованого місця. Рядок UTC має власне "
    L"центрування.",
    L"\r\n\r\nВНЕШНИЙ ВИД И ХРАНЕНИЕ НАСТРОЕК\r\nИзменения внешнего вида сразу отображаются в "
    L"предварительном просмотре. «Отмена» отменяет неприменённые изменения внешнего вида, а «Вид "
    L"по умолчанию» возвращает исходные параметры этого типа виджета. В цифровых часах можно "
    L"настроить шрифт, сглаживание, цвета, непрозрачность, внутренний отступ, толщину рамки и "
    L"прозрачный фон. Цифровые часы, календари и панели имеют четыре общих стиля рамки; для "
    L"однолинейной рамки можно выбрать цвет. У панели отдельные шрифты верхней строки, времени и "
    L"нижней строки, показ ведущего нуля и выбор размеров циферблатов. Пользовательские шрифты "
    L"календаря поддерживаются при классическом оформлении Windows или когда темы отключены для "
    L"программы либо виджета. Настройки можно экспортировать в XML. Импорт XML сразу загружает и "
    L"сохраняет настройки в текущем хранилище, не меняя его типа. Автоматическое хранилище XML — "
    L"%AppData%\\FortSoft\\CalClock\\settings.xml. После записи XML раздел "
    L"HKCU\\SOFTWARE\\FortSoft\\CalClock удаляется; выбор хранения в реестре удаляет "
    L"автоматический файл XML.\r\n\r\nДля сглаживания шрифта доступны ClearType, GDI и "
    L"«Нет».\r\n\r\nПараметр «Ведущий ноль» имеет значения «Да» (по умолчанию), «Нет, оставить "
    L"место» и «Нет, без места». «Нет, оставить место» скрывает ноль, но резервирует его ширину в "
    L"выбранном "
    L"шрифте; остальные цифры остаются на месте даже в пропорциональных шрифтах. Часы на мониторе "
    L"сохраняют центрирование с учётом зарезервированного места. Строка UTC имеет собственное "
    L"центрирование."
};

const wchar_t* HELP_SETTINGS_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nNASTAVENÍ A NABÍDKY\r\nJazyk, písmo, vyhlazování, motivy, úložiště, spouštění s "
    L"Windows a přichytávání jsou globální a nastavují se na kartě Aplikace. Při prvním spuštění "
    L"se jazyk volí podle uživatelského jazyka Windows, neznámý jazyk se nahradí angličtinou "
    L"(USA); jazyk, vyhlazování a motivy widgetu platí jen pro něj. \r\n\r\nNabídka widgetu "
    L"obsahuje příslušné volby viditelnosti, režimu navrchu, sekund, velikosti a kopírování data "
    L"a dále Zarovnat do mřížky, Nastavení, Nápovědu, O programu a Konec. Nabídka ikony uvádí "
    L"widgety s pořadovými čísly a příkazy Zobrazit vše, Skrýt vše a Ztlumit vše. Samostatně "
    L"oddělený příkaz Zarovnat do mřížky následuje za nimi. Zobrazení či obnovení přenese widgety "
    L"dopředu bez změny Vždy navrchu. Další spuštění aktivuje běžící instanci a v případě potřeby "
    L"obnoví naposledy skryté widgety. Dostupné rozměry ciferníku a možnost sekundové ručičky "
    L"vycházejí z možností používané verze Windows. Budík a signál lze zapnout přímo v nabídce "
    L"widgetu; položka Budík ukazuje čas a při částečném týdnu také aktivní dny. Zaškrtnutí "
    L"Ztlumit v nabídce widgetu odpovídá volbě Ztlumeno na kartě Obecné. Ztlumit vše v nabídce "
    L"ikony ztlumí všechny widgety a při dalším přepnutí obnoví jen ty, které samo ztlumilo. "
    L"Totéž globální přepnutí provede klávesa M na kterémkoli widgetu. Zapnutí budíku bez "
    L"vybraného dne otevře kartu Budík daného widgetu.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nApplication language, font, smoothing, themes, storage, "
    L"Windows startup and edge snapping are global and are configured on the Application tab. On "
    L"first launch, the application language follows the Windows user-interface language, with US "
    L"English as the fallback; widget language, smoothing and themes affect that widget only. "
    L"\r\n\r\nA widget menu contains the applicable visibility, always-on-top, seconds, size and "
    L"date-copy choices, followed by Arrange in a grid, Settings, Help, About and Exit. The "
    L"notification-icon menu lists numbered widgets and provides Show all, Hide all and Mute all. "
    L"The separately grouped Arrange in a grid command follows. Showing or restoring widgets "
    L"brings them forward without changing Always on top. Starting CalClock again activates the "
    L"running instance and restores the most recently hidden widgets when needed. Available face "
    L"sizes and second-hand support come from the installed Windows version. Alarm and Signal can "
    L"be toggled directly in a widget menu; Alarm shows its time and, for a partial week, its "
    L"active weekdays. Checked Mute in a widget menu corresponds to Muted on the General tab. "
    L"Mute all in the notification-icon menu mutes every widget and, when toggled again, restores "
    L"only those it muted. Pressing M on any widget performs the same global toggle. Enabling an "
    L"alarm with no weekday selected opens that widget’s Alarm tab.",
    L"\r\n\r\nEINSTELLUNGEN UND MENÜS\r\nAnwendungssprache, Schrift, Glättung, Designs, Speicher, "
    L"Windows-Start und Randeinrasten sind global und werden auf der Registerkarte Anwendung "
    L"eingestellt. Beim ersten Start folgt die Sprache der Windows-Anzeigesprache; sonst wird "
    L"US-Englisch verwendet. Widget-Sprache, Glättung und Designs gelten nur für dieses Widget. "
    L"\r\n\r\nDas Widget-Menü enthält die zutreffenden Optionen für Sichtbarkeit, Vordergrund, "
    L"Sekunden, Größe und Datumskopie sowie Im Raster anordnen, Einstellungen, Hilfe, Info und "
    L"Beenden. Das Infobereichsmenü listet nummerierte Widgets und bietet Alle anzeigen, Alle "
    L"ausblenden und Alles stummschalten. Im Raster anordnen folgt als getrennte Gruppe. Anzeigen "
    L"oder Wiederherstellen bringt Widgets nach vorn, ohne Immer im Vordergrund zu ändern. Ein "
    L"erneuter Start aktiviert die laufende Instanz und stellt bei Bedarf die zuletzt verborgenen "
    L"Widgets wieder her. Verfügbare Zifferblattgrößen und Sekundenzeiger hängen von der "
    L"installierten Windows-Version ab. Wecker und Zeitzeichen lassen sich direkt im Widget-Menü "
    L"schalten; Wecker zeigt Zeit und bei einer Teilwoche die aktiven Tage. Stummschalten im "
    L"Widget-Menü entspricht Stummgeschaltet unter Allgemein. Alles stummschalten im Infobereich "
    L"stellt beim nächsten Umschalten nur die von ihm stummgeschalteten Widgets wieder her. M auf "
    L"einem Widget schaltet denselben Gesamtzustand um. Wird ein Wecker ohne ausgewählten "
    L"Wochentag aktiviert, öffnet sich die Registerkarte Wecker dieses Widgets.",
    L"\r\n\r\nPARAMÈTRES ET MENUS\r\nLangue, police, lissage, thèmes, stockage, démarrage avec "
    L"Windows et accrochage sont globaux et se règlent dans l’onglet Application. Au premier "
    L"lancement, la langue suit celle de l’interface Windows, avec l’anglais américain par défaut "
    L"; langue, lissage et thèmes du widget ne concernent que lui. \r\n\r\nLe menu d’un widget "
    L"contient les choix applicables de visibilité, premier plan, secondes, taille et copie de "
    L"date, puis Aligner sur une grille, Paramètres, Aide, À propos et Quitter. Le menu de "
    L"notification liste les widgets numérotés et propose Tout afficher, Tout masquer et Couper "
    L"tous les sons. Aligner sur une grille suit dans un groupe séparé. Afficher ou restaurer les "
    L"widgets les ramène devant sans modifier Toujours visible. Un nouveau lancement active "
    L"l’instance existante et restaure au besoin les derniers widgets masqués. Les tailles de "
    L"cadran et la trotteuse disponibles viennent de la version de Windows installée. Alarme et "
    L"Signal se commutent dans le menu du widget ; Alarme affiche l’heure et, pour une semaine "
    L"partielle, les jours actifs. Couper le son dans le menu du widget correspond à Son coupé "
    L"dans Général. Tout couper rétablit ensuite uniquement les widgets qu’il a coupés. M sur un "
    L"widget effectue la même bascule globale. Activer l’alarme sans jour sélectionné ouvre "
    L"l’onglet Alarme de ce widget.",
    L"\r\n\r\nCONFIGURACIÓN Y MENÚS\r\nIdioma, fuente, suavizado, temas, almacenamiento, inicio "
    L"con Windows y acoplamiento son globales y se configuran en la pestaña Aplicación. En el "
    L"primer inicio, el idioma sigue al de la interfaz de Windows y usa inglés de EE. UU. como "
    L"alternativa; idioma, suavizado y temas del widget solo afectan a este. \r\n\r\nEl menú del "
    L"widget contiene las opciones aplicables de visibilidad, primer plano, segundos, tamaño y "
    L"copia de fecha, además de Alinear en cuadrícula, Configuración, Ayuda, Acerca de y Salir. "
    L"El menú del icono muestra widgets numerados y ofrece Mostrar todo, Ocultar todo y Silenciar "
    L"todo. Alinear en cuadrícula aparece después como grupo separado. Mostrar o restaurar lleva "
    L"los widgets al frente sin cambiar Siempre visible. Otra ejecución activa la instancia "
    L"existente y restaura cuando haga falta los últimos widgets ocultos. Los tamaños de esfera y "
    L"la disponibilidad del segundero proceden de la versión de Windows instalada. Alarma y Señal "
    L"se conmutan en el menú del widget; Alarma muestra la hora y, para una semana parcial, los "
    L"días activos. Silenciar en el menú del widget corresponde a Silenciado en General. "
    L"Silenciar todo restaura después solo los widgets que silenció. M sobre un widget realiza la "
    L"misma conmutación global. Activar la alarma sin ningún día seleccionado abre la pestaña "
    L"Alarma de ese widget.",
    L"\r\n\r\nIMPOSTAZIONI E MENU\r\nLingua, carattere, antialiasing, temi, archivio, avvio con "
    L"Windows e aggancio sono globali e si configurano nella scheda Applicazione. Al primo avvio "
    L"la lingua segue quella dell’interfaccia di Windows, con inglese USA come ripiego; lingua, "
    L"antialiasing e temi del widget valgono solo per esso. \r\n\r\nIl menu del widget contiene "
    L"le scelte pertinenti per visibilità, primo piano, secondi, dimensione e copia della data, "
    L"oltre a Disponi in griglia, Impostazioni, Guida, Informazioni ed Esci. Il menu dell’icona "
    L"elenca i widget numerati e offre Mostra tutto, Nascondi tutto e Disattiva tutto l'audio. "
    L"Disponi in griglia segue come gruppo separato. Mostrare o ripristinare porta i widget "
    L"davanti senza cambiare Sempre in primo piano. Un nuovo avvio attiva l’istanza esistente e, "
    L"se necessario, ripristina gli ultimi widget nascosti. Dimensioni del quadrante e lancetta "
    L"dei secondi disponibili dipendono dalla versione di Windows installata. Sveglia e Segnale "
    L"si attivano dal menu del widget; Sveglia mostra l’ora e, per una settimana parziale, i "
    L"giorni attivi. Disattiva audio nel menu del widget corrisponde ad Audio disattivato in "
    L"Generali. Disattiva tutto ripristina poi solo i widget che aveva disattivato. M su un "
    L"widget esegue lo stesso comando globale. Attivare la sveglia senza giorni selezionati apre "
    L"la scheda Sveglia del widget.",
    L"\r\n\r\nUSTAWIENIA I MENU\r\nJęzyk, czcionka, wygładzanie, motywy, magazyn ustawień, "
    L"uruchamianie z Windows i przyciąganie są globalne i ustawia się je na karcie Aplikacja. "
    L"Przy pierwszym uruchomieniu język wynika z języka interfejsu Windows, a nieznany zastępuje "
    L"angielski (USA); język, wygładzanie i motywy widżetu dotyczą tylko jego. \r\n\r\nMenu "
    L"widżetu zawiera odpowiednie opcje widoczności, położenia na wierzchu, sekund, rozmiaru i "
    L"kopiowania daty oraz Ułóż w siatce, Ustawienia, Pomoc, O programie i Zakończ. Menu ikony "
    L"wyświetla numerowane widżety oraz Pokaż wszystkie, Ukryj wszystkie i Wycisz wszystko. Ułóż "
    L"w siatce znajduje się dalej w oddzielnej grupie. Pokazanie lub przywrócenie przenosi "
    L"widżety do przodu bez zmiany Zawsze na wierzchu. Ponowne uruchomienie aktywuje istniejącą "
    L"instancję i w razie potrzeby przywraca ostatnio ukryte widżety. Dostępne rozmiary tarczy i "
    L"sekundnik zależą od zainstalowanej wersji Windows. Alarm i Sygnał można przełączać w menu "
    L"widżetu; Alarm pokazuje czas i, dla części tygodnia, aktywne dni. Wycisz w menu widżetu "
    L"odpowiada opcji Wyciszony na karcie Ogólne. Wycisz wszystko przywraca potem tylko widżety, "
    L"które samo wyciszyło. M na widżecie wykonuje to samo przełączenie globalne. Włączenie "
    L"alarmu bez wybranego dnia otwiera kartę Alarm tego widżetu.",
    L"\r\n\r\nNASTAVENIA A PONUKY\r\nJazyk, písmo, vyhladzovanie, motívy, úložisko, spúšťanie s "
    L"Windows a prichytávanie sú globálne a nastavujú sa na karte Aplikácia. Pri prvom spustení "
    L"sa jazyk volí podľa jazyka rozhrania Windows, neznámy jazyk sa nahradí angličtinou (USA); "
    L"jazyk, vyhladzovanie a motívy widgetu platia iba preň. \r\n\r\nPonuka widgetu obsahuje "
    L"príslušné voľby viditeľnosti, režimu navrchu, sekúnd, veľkosti a kopírovania dátumu a ďalej "
    L"Zarovnať do mriežky, Nastavenia, Pomoc, O programe a Koniec. Ponuka ikony uvádza očíslované "
    L"widgety a príkazy Zobraziť všetko, Skryť všetko a Stlmiť všetko. Samostatne oddelený príkaz "
    L"Zarovnať do mriežky nasleduje za nimi. Zobrazenie alebo obnovenie prenesie widgety dopredu "
    L"bez zmeny Vždy navrchu. Ďalšie spustenie aktivuje bežiacu inštanciu a podľa potreby obnoví "
    L"naposledy skryté widgety. Dostupné rozmery ciferníka a sekundová ručička vychádzajú z "
    L"možností používanej verzie Windows. Budík a Signál možno prepínať v ponuke widgetu; Budík "
    L"ukazuje čas a pri čiastočnom týždni aj aktívne dni. Stlmiť v ponuke widgetu zodpovedá voľbe "
    L"Stlmené na karte Všeobecné. Stlmiť všetko potom obnoví iba widgety, ktoré samo stlmilo. "
    L"Kláves M na widgete vykoná rovnaké globálne prepnutie. Zapnutie budíka bez vybraného dňa "
    L"otvorí kartu Budík daného widgetu.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nApplication language, font, smoothing, themes, storage, "
    L"Windows startup and edge snapping are global and are configured on the Application tab. On "
    L"first launch, the application language follows the Windows user-interface language, with US "
    L"English as the fallback; widget language, smoothing and themes affect that widget only. "
    L"\r\n\r\nA widget menu contains the applicable visibility, always-on-top, seconds, size and "
    L"date-copy choices, followed by Arrange in a grid, Settings, Help, About and Exit. The "
    L"notification-icon menu lists numbered widgets and provides Show all, Hide all and Mute all. "
    L"The separately grouped Arrange in a grid command follows. Showing or restoring widgets "
    L"brings them forward without changing Always on top. Starting CalClock again activates the "
    L"running instance and restores the most recently hidden widgets when needed. Available face "
    L"sizes and second-hand support come from the installed Windows version. Alarm and Signal can "
    L"be toggled directly in a widget menu; Alarm shows its time and, for a partial week, its "
    L"active weekdays. Checked Mute in a widget menu corresponds to Muted on the General tab. "
    L"Mute all in the notification-icon menu mutes every widget and, when toggled again, restores "
    L"only those it muted. Pressing M on any widget performs the same global toggle. Enabling an "
    L"alarm with no weekday selected opens that widget’s Alarm tab.",
    L"\r\n\r\nSETTINGS AND MENUS\r\nApplication language, font, smoothing, themes, storage, "
    L"Windows startup and edge snapping are global and are configured on the Application tab. On "
    L"first launch, the application language follows the Windows user-interface language, with US "
    L"English as the fallback; widget language, smoothing and themes affect that widget only. "
    L"\r\n\r\nA widget menu contains the applicable visibility, always-on-top, seconds, size and "
    L"date-copy choices, followed by Arrange in a grid, Settings, Help, About and Exit. The "
    L"notification-icon menu lists numbered widgets and provides Show all, Hide all and Mute all. "
    L"The separately grouped Arrange in a grid command follows. Showing or restoring widgets "
    L"brings them forward without changing Always on top. Starting CalClock again activates the "
    L"running instance and restores the most recently hidden widgets when needed. Available face "
    L"sizes and second-hand support come from the installed Windows version. Alarm and Signal can "
    L"be toggled directly in a widget menu; Alarm shows its time and, for a partial week, its "
    L"active weekdays. Checked Mute in a widget menu corresponds to Muted on the General tab. "
    L"Mute all in the notification-icon menu mutes every widget and, when toggled again, restores "
    L"only those it muted. Pressing M on any widget performs the same global toggle. Enabling an "
    L"alarm with no weekday selected opens that widget’s Alarm tab.",
    L"\r\n\r\nDEFINIÇÕES E MENUS\r\nO idioma, tipo de letra, suavização, temas, armazenamento, "
    L"arranque com o Windows, ajuste às margens e origem da hora são globais; as opções da "
    L"aplicação são configuradas no separador Aplicação. No primeiro arranque, o idioma segue a "
    L"interface do Windows, com inglês dos EUA como alternativa. O idioma e outras opções de "
    L"widget aplicam-se individualmente. No menu do ícone, Mostrar tudo e Ocultar tudo precedem "
    L"Silenciar tudo; Dispor numa grelha surge num grupo separado. Silenciar no menu do widget "
    L"corresponde a Silenciado em Geral. Silenciar tudo repõe depois apenas os widgets que "
    L"silenciou. M num widget executa a mesma alternância global. Ativar o alarme sem nenhum dia "
    L"selecionado abre o separador Alarme desse widget.",
    L"\r\n\r\nINNSTILLINGER OG MENYER\r\nProgramspråk, skrift, utjevning, temaer, lagring, "
    L"oppstart med Windows, kantfesting og tidskilde er globale; programvalgene angis på fanen "
    L"Program. Ved første start følger språket Windows-grensesnittet, med amerikansk engelsk som "
    L"reserve. Widgetspråk og andre widgetvalg gjelder enkeltvis. I ikonmenyen kommer Vis alle og "
    L"Skjul alle før Demp alle; Ordne i et rutenett står i en egen gruppe etter dem. Demp i "
    L"widgetmenyen tilsvarer Dempet på fanen Generelt. Demp alle gjenoppretter senere bare "
    L"widgetene den dempet. M på en widget utfører samme globale veksling. Aktivering av alarmen "
    L"uten valgte ukedager åpner widgetens Alarm-fane.",
    L"\r\n\r\nINSTÄLLNINGAR OCH MENYER\r\nProgramspråk, teckensnitt, utjämning, teman, lagring, "
    L"start med Windows, kantfästning och tidskälla är globala; programalternativen ställs in på "
    L"fliken Program. Vid första starten följer språket Windows gränssnittsspråk, med amerikansk "
    L"engelska som reserv. Widgetspråk och andra widgetval gäller separat. I ikonmenyn kommer "
    L"Visa alla och Dölj alla före Tysta alla; Ordna i ett rutnät står i en egen grupp efter dem. "
    L"Tysta i widgetmenyn motsvarar Tyst på fliken Allmänt. Tysta alla återställer därefter bara "
    L"de widgetar som kommandot tystade. M på en widget gör samma globala växling. Om alarmet "
    L"aktiveras utan valda veckodagar öppnas widgetens Alarm-flik.",
    L"\r\n\r\nASETUKSET JA VALIKOT\r\nSovelluksen kieli, fontti, pehmennys, teemat, tallennus, "
    L"Windowsin mukana käynnistys, reunakiinnitys ja aikalähde ovat yleisiä; sovellusasetukset "
    L"määritetään Sovellus-välilehdellä. Ensimmäisellä käynnistyksellä kieli seuraa Windowsin "
    L"käyttöliittymäkieltä, varalla on amerikanenglanti. Pienoisohjelman kieli ja muut valinnat "
    L"ovat yksilöllisiä. Kuvakevalikossa Näytä kaikki ja Piilota kaikki ovat ennen Mykistä kaikki "
    L"-komentoa; Järjestä ruudukkoon on niiden jälkeen omana ryhmänään. Pienoisohjelman Mykistä "
    L"vastaa Yleiset-välilehden Mykistetty-valintaa. Mykistä kaikki palauttaa myöhemmin vain itse "
    L"mykistämänsä pienoisohjelmat. M pienoisohjelmassa tekee saman yleisen vaihdon. Herätyksen "
    L"ottaminen käyttöön ilman valittuja viikonpäiviä avaa pienoisohjelman Herätys-välilehden.",
    L"\r\n\r\nINDSTILLINGER OG MENUER\r\nProgramsprog, skrifttype, udjævning, temaer, lager, "
    L"start med Windows, kantfastgørelse og tidskilde er globale; programvalgene indstilles på "
    L"fanen Program. Ved første start følger sproget Windows-grænsefladen, med amerikansk engelsk "
    L"som reserve. Widgetsprog og andre widgetvalg gælder enkeltvis. I ikonmenuen kommer Vis alle "
    L"og Skjul alle før Slå al lyd fra; Arranger i et gitter står i en særskilt gruppe efter dem. "
    L"Slå lyd fra i widgetmenuen svarer til Lyd fra på fanen Generelt. Slå al lyd fra gendanner "
    L"senere kun de widgets, kommandoen selv dæmpede. M på en widget udfører samme globale skift. "
    L"Aktivering af alarmen uden valgte ugedage åbner widgetens Alarm-fane.",
    L"\r\n\r\nSTILLINGAR OG VALMYNDIR\r\nTungumál forrits, letur, jöfnun, þemu, geymsla, ræsing "
    L"með Windows, festing við brúnir og tímagjafi gilda alls staðar; forritsvalkostir eru "
    L"stilltir á Forrit-flipanum. Við fyrstu ræsingu fylgir tungumálið viðmóti Windows, en "
    L"bandarísk enska er varaval. Tungumál og aðrir valkostir græju gilda fyrir hverja græju. Í "
    L"táknvalmyndinni koma Sýna allt og Fela allt á undan Þagga allt; Raða á hnitanet er í "
    L"sérstökum flokki á eftir þeim. Þagga í valmynd græju samsvarar Þaggað á Almennt-flipanum. "
    L"Þagga allt endurheimtir síðar aðeins græjurnar sem skipunin þaggaði. M á græju framkvæmir "
    L"sömu heildarskiptingu. Ef vekjari er virkjaður án valinna vikudaga opnast Vekjari-flipi "
    L"græjunnar.",
    L"\r\n\r\nAYARLAR VE MENÜLER\r\nUygulama dili, yazı tipi, kenar yumuşatma, temalar, depolama, "
    L"Windows ile başlatma, kenara yaslama ve zaman kaynağı geneldir; uygulama seçenekleri "
    L"Uygulama sekmesinde ayarlanır. İlk açılışta dil Windows arayüz dilinden alınır; "
    L"desteklenmiyorsa ABD İngilizcesi kullanılır. Araç dili ve diğer araç seçenekleri her araç "
    L"için ayrıdır. Simge menüsünde Tümünü göster ve Tümünü gizle, Tümünü sessize al seçeneğinden "
    L"önce gelir; Izgarada düzenle bunların ardından ayrı bir gruptadır. Araç menüsündeki Sessize "
    L"al, Genel sekmesindeki Sessiz ile aynıdır. Tümünü sessize al, daha sonra yalnızca "
    L"kendisinin sessize aldığı araçların sesini geri açar. Bir araçta M tuşu aynı genel geçişi "
    L"yapar. Hiçbir gün seçili değilken alarmı etkinleştirmek aracın Alarm sekmesini açar.",
    L"\r\n\r\nSätted ja menüüd\r\nRakenduse keel, font, silumine, kujundused, salvestuskoht, "
    L"Windowsiga käivitamine ja servatõmme on ühised sätted vahekaardil Rakendus. "
    L"Esmakäivitamisel kasutatakse Windowsi kasutajaliidese keelt või selle puudumisel USA "
    L"inglise keelt. Vidina keel, silumine ja kujundused mõjutavad vaid seda vidinat. "
    L"\r\n\r\nVidina menüüs on selle tüübile sobivad nähtavuse, esiplaanil hoidmise, sekundite, "
    L"suuruse ja kuupäeva kopeerimise valikud, seejärel Paiguta ruudustikku, Sätted, Spikker, "
    L"Teave ja Välju. Olekuala menüü loetleb nummerdatud vidinad, Kuva kõik, Peida kõik ja "
    L"Vaigista kõik ning eraldi ruudustikukäsu. Kuvamine või taastamine toob vidina ette suvandit "
    L"Alati pealmine muutmata. Korduskäivitus taastab vajaduse korral viimati peidetud vidinad. "
    L"Sihverplaadisuurused ja sekundiosuti tugi sõltuvad Windowsist. Äratus ja Signaal on "
    L"lülitatavad ka menüüs, kus kuvatakse aeg, intervall ning osalise nädala korral aktiivsed "
    L"päevad. Vaigista vastab vahekaardi Üldine valikule Vaigistatud. Vaigista kõik ja klahv M "
    L"vaigistavad kõik vidinad ning järgmisel korral taastavad heli ainult neil, mille nad ise "
    L"vaigistasid. Päevadeta äratuse lubamine avab vahekaardi Äratus.",
    L"\r\n\r\nSocruithe agus roghchláir\r\nIs socruithe comhroinnte ar an gcluaisín Feidhmchlár "
    L"iad an teanga, cló, frithailiasáil, téamaí, stóras, tosú le Windows agus léim chuig imill. "
    L"Ar an gcéad tosú, roghnaítear teanga chomhéadan Windows nó Béarla SAM mura dtacaítear léi. "
    L"Ní bhaineann teanga, frithailiasáil agus téamaí giuirléide ach léi féin. "
    L"\r\n\r\nTaispeánann roghchlár giuirléide na roghanna infheictheachta, Ar barr i gcónaí, "
    L"soicindí, méid agus cóipeáil dáta a bhaineann léi, agus ansin Eagraigh in eangach, "
    L"Socruithe, Cabhair, Maidir leis agus Scoir. Liostaíonn an roghchlár fógraí giuirléidí "
    L"uimhrithe agus Taispeáin uile, Folaigh uile agus Balbhaigh uile, agus an t-ordú eangaí i "
    L"ngrúpa ar leith. Tugann taispeáint nó athchóiriú giuirléid chun tosaigh gan Ar barr i "
    L"gcónaí a athrú. Má sheoltar CalClock arís, gníomhachtaítear an feidhmchlár atá ar siúl "
    L"cheana agus athchóirítear na giuirléidí is déanaí a folaíodh más gá. Braitheann méideanna "
    L"aghaidhe agus tacaíocht don lámh soicindí ar Windows. Is féidir Aláram agus Comhartha a "
    L"athrú sa roghchlár, a thaispeánann am, eatramh agus na laethanta gníomhacha nuair nach "
    L"bhfuil an tseachtain iomlán roghnaithe. Freagraíonn Balbhaigh do Balbhaithe ar Ginearálta. "
    L"Balbhaíonn Balbhaigh uile agus M gach giuirléid; arís, ní athchóiríonn siad ach an fhuaim a "
    L"bhalbhaigh siad féin. Osclaítear Aláram má chumasaítear aláram gan lá roghnaithe.",
    L"\r\n\r\nParametrai ir meniu\r\nProgramos kalba, šriftas, glodinimas, temos, saugykla, "
    L"paleidimas su „Windows“ ir prikabinimas yra bendri skirtuko Programa parametrai. Pirmą "
    L"kartą parenkama „Windows“ sąsajos kalba arba JAV anglų kalba, jei ji nepalaikoma. Valdiklio "
    L"kalba, glodinimas ir temos taikomi tik jam. \r\n\r\nValdiklio meniu turi jam tinkamus "
    L"matomumo, Visada viršuje, sekundžių, dydžio ir datos kopijavimo pasirinkimus, po jų – "
    L"Išdėstyti tinkleliu, Parametrai, Žinynas, Apie ir Išeiti. Piktogramos meniu pateikia "
    L"numeruotus valdiklius, Rodyti visus, Slėpti visus ir Nutildyti visus, tada atskirą "
    L"tinklelio komandą. Rodant ar atkuriant valdiklis iškeliamas į priekį nekeičiant Visada "
    L"viršuje. Pakartotinis paleidimas prireikus atkuria paskutinį kartą paslėptus valdiklius. "
    L"Ciferblatų dydžiai ir sekundžių rodyklė priklauso nuo „Windows“. Žadintuvas ir Signalas "
    L"perjungiami ir meniu, kuris rodo laiką, intervalą bei pasirinktas dienas, jei pažymėta ne "
    L"visa savaitė. Nutildyti atitinka Nutildyta skirtuke Bendra. Nutildyti visus ir M nutildo "
    L"visus valdiklius; pakartojus grąžinamas garsas tik tiems, kuriuos ši komanda nutildė. "
    L"Įjungus žadintuvą be pasirinktos dienos atidaromas skirtukas Žadintuvas.",
    L"\r\n\r\nIestatījumi un izvēlnes\r\nProgrammas valoda, fonts, nogludināšana, dizaini, "
    L"krātuve, palaišana kopā ar Windows un pievilkšana ir kopīgi iestatījumi cilnē Programma. "
    L"Pirmajā palaišanā izmanto Windows saskarnes valodu vai ASV angļu valodu, ja tā netiek "
    L"atbalstīta. Logrīka valoda, nogludināšana un dizaini ietekmē tikai to. \r\n\r\nLogrīka "
    L"izvēlnē ir tam piemērotās redzamības, Vienmēr virspusē, sekunžu, lieluma un datuma "
    L"kopēšanas izvēles, tad Sakārtot režģī, Iestatījumi, Palīdzība, Par programmu un Iziet. "
    L"Ikonas izvēlnē ir numurēti logrīki, Rādīt visus, Paslēpt visus un Izslēgt visu skaņu, pēc "
    L"tam atsevišķa režģa komanda. Parādīšana vai atjaunošana izvirza logrīku priekšplānā bez "
    L"Vienmēr virspusē maiņas. Atkārtota palaišana vajadzības gadījumā atjauno pēdējos paslēptos "
    L"logrīkus. Ciparnīcas un sekunžu rādītāja atbalsts atkarīgs no Windows. Modinātāju un "
    L"Signālu var pārslēgt izvēlnē, kur redzams laiks, intervāls un atlasītās dienas, ja nav "
    L"atlasīta visa nedēļa. Izslēgt skaņu atbilst Skaņa izslēgta cilnē Vispārīgi. Izslēgt visu "
    L"skaņu un M izslēdz visu logrīku skaņu; atkārtoti ieslēdz tikai to, ko šī komanda izslēgusi. "
    L"Modinātāja ieslēgšana bez atlasītas dienas atver tā cilni.",
    L"\r\n\r\nBeállítások és menük\r\nA nyelv, betűtípus, élsimítás, témák, tároló, Windowszal "
    L"indítás és szélhez illesztés közös beállítás az Alkalmazás fülön. Első indításkor a Windows "
    L"felületének nyelve, nem támogatott nyelvnél az amerikai angol lesz aktív. A minialkalmazás "
    L"nyelve, élsimítása és témái csak arra érvényesek. \r\n\r\nA minialkalmazás menüje az "
    L"alkalmazható láthatóság-, Mindig felül-, másodperc-, méret- és dátummásolási választásokat, "
    L"majd a Rácsba rendezés, Beállítások, Súgó, Névjegy és Kilépés parancsokat tartalmazza. Az "
    L"ikon menüje számozott minialkalmazásokat, Összes megjelenítése, Összes elrejtése és Összes "
    L"némítása parancsot, majd külön rácsparancsot ad. A megjelenítés vagy visszaállítás előtérbe "
    L"hoz a Mindig felül módosítása nélkül. Az újabb indítás szükség esetén visszahozza a "
    L"legutóbb elrejtetteket. A számlapméret és másodpercmutató a Windowstól függ. Az Ébresztés "
    L"és Időjelzés a menüből is kapcsolható; az idő, intervallum és részleges hétnél a kijelölt "
    L"napok is látszanak. A Némítás a Némítva állapotnak felel meg az Általános fülön. Az Összes "
    L"némítása és az M mindent némít, ismételve csak az általa némított hangokat állítja vissza. "
    L"Nap nélküli ébresztés engedélyezése megnyitja az Ébresztés fület.",
    L"\r\n\r\nSettings u menus\r\nIl-lingwa, il-font, l-anti-aliasing, it-temi, il-ħażna, il-bidu "
    L"mal-Windows u t-twaħħil mat-truf huma settings komuni fit-tab Applikazzjoni. Mal-ewwel "
    L"tnedija tintgħażel il-lingwa tal-interfaċċa tal-Windows jew l-Ingliż Amerikan jekk mhijiex "
    L"appoġġjata. Il-lingwa, l-anti-aliasing u t-temi tal-widget jaffettwaw biss lilu. "
    L"\r\n\r\nIl-menu tal-widget fih l-għażliet xierqa għall-viżibbiltà, Dejjem fuq nett, "
    L"sekondi, daqs u kkupjar tad-data, imbagħad Irranġa fi gradilja, Settings, Għajnuna, Dwar u "
    L"Oħroġ. Il-menu tal-ikona jelenka widgets innumerati, Uri kollox, Aħbi kollox u Iddiżattiva "
    L"l-ħoss kollu, imbagħad il-kmand tal-gradilja separat. Il-wiri jew ir-restawr iġib il-widget "
    L"quddiem mingħajr ma jibdel Dejjem fuq nett. Tnedija oħra tirrestawra l-aħħar widgets "
    L"moħbija jekk meħtieġ. Id-daqsijiet u l-appoġġ għall-id tas-sekondi jiddependu fuq Windows. "
    L"Allarm u Sinjal jistgħu jinqalbu fil-menu, li juri l-ħin, l-intervall u l-jiem magħżula "
    L"jekk mhijiex magħżula l-ġimgħa kollha. Iddiżattiva l-ħoss jikkorrispondi għal Ħoss "
    L"diżattivat fit-tab Ġenerali. Iddiżattiva l-ħoss kollu u M isikktu l-widgets kollha; "
    L"ir-ripetizzjoni tirrestawra biss dawk imsikkta minn dak il-kmand. L-attivazzjoni ta’ allarm "
    L"mingħajr jum magħżul tiftaħ it-tab Allarm.",
    L"\r\n\r\nInstellingen en menu’s\r\nTaal, lettertype, vereffening, thema’s, opslag, starten "
    L"met Windows en uitlijnen op randen zijn algemene instellingen op Toepassing. Bij de eerste "
    L"start wordt de Windows-weergavetaal gekozen, of Amerikaans Engels als deze niet ondersteund "
    L"wordt. Widgettaal, vereffening en thema’s gelden alleen voor die widget. \r\n\r\nEen "
    L"widgetmenu bevat toepasselijke keuzes voor zichtbaarheid, Altijd op voorgrond, seconden, "
    L"grootte en datumkopie, gevolgd door Schikken in raster, Instellingen, Help, Info en "
    L"Afsluiten. Het pictogrammenu bevat genummerde widgets, Alles weergeven, Alles verbergen en "
    L"Alles dempen, gevolgd door een afzonderlijke rasteropdracht. Tonen of herstellen brengt een "
    L"widget naar voren zonder Altijd op voorgrond te wijzigen. Opnieuw starten herstelt zo nodig "
    L"de laatst verborgen widgets. Wijzerplaatgroottes en de secondewijzer hangen van Windows af. "
    L"Alarm en Signaal zijn ook in het menu te schakelen; daar staan de tijd, het interval en bij "
    L"een gedeeltelijke week de actieve dagen. Dempen komt overeen met Gedempt op Algemeen. Alles "
    L"dempen en M dempen elke widget; opnieuw schakelen herstelt alleen wat deze opdracht zelf "
    L"dempte. Een alarm inschakelen zonder gekozen dag opent het tabblad Alarm.",
    L"\r\n\r\nSetări și meniuri\r\nLimba aplicației, fontul, netezirea, temele, stocarea, "
    L"pornirea cu Windows și alinierea la margini sunt comune în fila Aplicație. La prima pornire "
    L"se alege limba interfeței Windows sau engleza americană dacă nu este acceptată. Limba, "
    L"netezirea și temele widgetului afectează numai acel widget. \r\n\r\nMeniul widgetului "
    L"conține alegerile aplicabile de vizibilitate, Întotdeauna deasupra, secunde, dimensiune și "
    L"copiere a datei, apoi Aranjare în grilă, Setări, Ajutor, Despre și Ieșire. Meniul "
    L"pictogramei enumeră widgeturile numerotate, Afișare totală, Ascundere totală și Dezactivare "
    L"totală sunet, apoi comanda de grilă separată. Afișarea sau restabilirea aduce widgetul în "
    L"față fără schimbarea Întotdeauna deasupra. O nouă pornire restabilește la nevoie ultimele "
    L"widgeturi ascunse. Dimensiunile și secundarul depind de Windows. Alarmă și Semnal se pot "
    L"comuta din meniu, care arată ora, intervalul și zilele active când nu este selectată "
    L"întreaga săptămână. Dezactivare sunet corespunde cu Sunet dezactivat din General. "
    L"Dezactivare totală sunet și M dezactivează sunetul tuturor widgeturilor; repetarea îl "
    L"restabilește numai celor afectate de acea comandă. Activarea unei alarme fără zi selectată "
    L"deschide fila Alarmă.",
    L"\r\n\r\nΡυθμίσεις και μενού\r\nΗ γλώσσα, η γραμματοσειρά, η εξομάλυνση, τα θέματα, η "
    L"αποθήκευση, η εκκίνηση με Windows και η προσκόλληση είναι κοινές ρυθμίσεις στην καρτέλα "
    L"Εφαρμογή. Στην πρώτη εκκίνηση επιλέγεται η γλώσσα των Windows ή τα Αγγλικά ΗΠΑ αν δεν "
    L"υποστηρίζεται. Η γλώσσα, η εξομάλυνση και τα θέματα ενός στοιχείου επηρεάζουν μόνο αυτό. "
    L"\r\n\r\nΤο μενού στοιχείου έχει τις κατάλληλες επιλογές ορατότητας, Πάντα σε πρώτο πλάνο, "
    L"δευτερολέπτων, μεγέθους και αντιγραφής ημερομηνίας και μετά Τακτοποίηση σε πλέγμα, "
    L"Ρυθμίσεις, Βοήθεια, Πληροφορίες και Έξοδος. Το μενού εικονιδίου έχει αριθμημένα στοιχεία, "
    L"Εμφάνιση όλων, Απόκρυψη όλων και Σίγαση όλων και χωριστά την εντολή πλέγματος. Η εμφάνιση ή "
    L"επαναφορά φέρνει το στοιχείο μπροστά χωρίς αλλαγή του Πάντα σε πρώτο πλάνο. Η νέα εκκίνηση "
    L"επαναφέρει όσα αποκρύφτηκαν τελευταία, αν χρειάζεται. Μεγέθη καντράν και δείκτης "
    L"δευτερολέπτων εξαρτώνται από Windows. Ξυπνητήρι και Σήμα αλλάζουν και από το μενού, που "
    L"δείχνει ώρα, διάστημα και ενεργές ημέρες όταν δεν επιλέγεται ολόκληρη η εβδομάδα. Η Σίγαση "
    L"αντιστοιχεί στο Σε σίγαση στα Γενικά. Η Σίγαση όλων και το M σιγούν όλα τα στοιχεία· η "
    L"επανάληψη επαναφέρει μόνο όσα σίγησε η ίδια εντολή. Η ενεργοποίηση ξυπνητηριού χωρίς ημέρα "
    L"ανοίγει την καρτέλα του.",
    L"\r\n\r\nPostavke i meniji\r\nJezik programa, font, izglađivanje, teme, spremište, "
    L"pokretanje s Windowsom i priljubljivanje uz ivice vrijede globalno i postavljaju se na "
    L"kartici Program. Pri prvom pokretanju jezik se bira prema jeziku interfejsa Windowsa; ako "
    L"nije podržan, koristi se američki engleski. Jezik, izglađivanje i teme vidžeta utječu samo "
    L"na taj vidžet. \r\n\r\nMeni vidžeta sadrži primjenjive postavke vidljivosti, načina Uvijek "
    L"na vrhu, sekundi, veličine i oblika kopiranja datuma, a zatim Rasporedi u mrežu, Postavke, "
    L"Pomoć, O programu i Izlaz. Meni ikone u području obavijesti navodi numerisane vidžete i "
    L"naredbe Prikaži sve, Sakrij sve i Isključi sav zvuk. Slijedi zasebno grupirana naredba "
    L"Rasporedi u mrežu. Prikazivanje ili vraćanje vidžeta dovodi ga naprijed bez promjene "
    L"postavke Uvijek na vrhu. Ponovno pokretanje CalClocka aktivira postojeću instancu i po "
    L"potrebi vraća posljednje skrivene vidžete. Dostupne veličine brojčanika i podrška sekundnoj "
    L"kazaljci zavise od verzije Windowsa. Alarm i Signal mogu se uključiti u meniju vidžeta; "
    L"Alarm pokazuje vrijeme i, ako nisu odabrani svi dani, aktivne dane u sedmici. Označeni "
    L"Isključi zvuk odgovara opciji Zvuk isključen na kartici Općenito. Isključi sav zvuk "
    L"isključuje zvuk svih vidžeta, a ponovnim izvođenjem vraća zvuk samo onima koje je prethodno "
    L"utišao. M na bilo kojem vidžetu radi isto. Uključivanje alarma bez odabranih dana otvara "
    L"njegovu karticu Alarm.",
    L"\r\n\r\nPostavke i izbornici\r\nJezik programa, font, izglađivanje, teme, spremište, "
    L"pokretanje s Windowsom i priljubljivanje uz rubove vrijede globalno i postavljaju se na "
    L"kartici Program. Pri prvom pokretanju jezik se bira prema jeziku sučelja Windowsa; ako nije "
    L"podržan, koristi se američki engleski. Jezik, izglađivanje i teme widgeta utječu samo na "
    L"taj widget. \r\n\r\nIzbornik widgeta sadrži primjenjive postavke vidljivosti, načina Uvijek "
    L"na vrhu, sekundi, veličine i oblika kopiranja datuma, a zatim Rasporedi u mrežu, Postavke, "
    L"Pomoć, O programu i Izlaz. Izbornik ikone u području obavijesti navodi numerirane widgete i "
    L"naredbe Prikaži sve, Sakrij sve i Isključi sav zvuk. Slijedi zasebno grupirana naredba "
    L"Rasporedi u mrežu. Prikazivanje ili vraćanje widgeta dovodi ga naprijed bez promjene "
    L"postavke Uvijek na vrhu. Ponovno pokretanje CalClocka aktivira postojeću instancu i po "
    L"potrebi vraća posljednje skrivene widgete. Dostupne veličine brojčanika i podrška sekundnoj "
    L"kazaljci ovise o verziji Windowsa. Alarm i Signal mogu se uključiti u izborniku widgeta; "
    L"Alarm pokazuje vrijeme i, ako nisu odabrani svi dani, aktivne dane u tjednu. Označeni "
    L"Isključi zvuk odgovara opciji Zvuk isključen na kartici Općenito. Isključi sav zvuk "
    L"isključuje zvuk svih widgeta, a ponovnim izvođenjem vraća zvuk samo onima koje je prethodno "
    L"utišao. M na bilo kojem widgetu radi isto. Uključivanje alarma bez odabranih dana otvara "
    L"njegovu karticu Alarm.",
    L"\r\n\r\nNastavitve in meniji\r\nJezik, pisava, glajenje, teme, shramba, zagon z Windows in "
    L"pripenjanje so skupne nastavitve na zavihku Program. Ob prvem zagonu se jezik izbere po "
    L"jeziku vmesnika Windows; če ni podprt, se uporabi ameriška angleščina. Jezik, glajenje in "
    L"teme gradnika vplivajo samo nanj. \r\n\r\nMeni gradnika vsebuje ustrezne izbire vidnosti, "
    L"Vedno na vrhu, sekund, velikosti in kopiranja datuma, nato Razporedi v mrežo, Nastavitve, "
    L"Pomoč, O programu in Izhod. Meni ikone vsebuje oštevilčene gradnike ter Pokaži vse, Skrij "
    L"vse in Izklopi ves zvok; sledi ločeni ukaz Razporedi v mrežo. Prikaz ali obnova postavi "
    L"gradnik v ospredje brez spremembe Vedno na vrhu. Ponovni zagon aktivira obstoječi primerek "
    L"in po potrebi obnovi nazadnje skrite gradnike. Velikosti številčnic in podpora sekundnemu "
    L"kazalcu so odvisne od Windows. Budilko in Signal lahko preklopite v meniju; budilka kaže "
    L"čas in pri delnem tednu izbrane dneve. Označeni Izklopi zvok ustreza možnosti Zvok "
    L"izklopljen na zavihku Splošno. Izklopi ves zvok utiša vse gradnike, ob ponovitvi pa obnovi "
    L"zvok samo tistim, ki jih je sam utišal. Tipka M na katerem koli gradniku naredi isto. Vklop "
    L"budilke brez izbranega dneva odpre njen zavihek Budilka.",
    L"\r\n\r\nPodešavanja i meniji\r\nJezik programa, font, umekšavanje, teme, skladište, "
    L"pokretanje uz Windows i priljepljivanje su zajedničke postavke na kartici Program. Pri "
    L"prvom pokretanju bira se jezik interfejsa Windows-a; ako nije podržan, koristi se američki "
    L"engleski. Jezik, umekšavanje i teme vidžeta utiču samo na njega. \r\n\r\nMeni vidžeta "
    L"sadrži primjenjive postavke vidljivosti, Uvijek na vrhu, sekundi, veličine i kopiranja "
    L"datuma, zatim Rasporedi u mrežu, Podešavanja, Pomoć, O programu i Izlaz. Meni ikone navodi "
    L"numerisane vidžete, Prikaži sve, Sakrij sve i Isključi sav zvuk, pa odvojeno Rasporedi u "
    L"mrežu. Prikaz ili vraćanje dovodi vidžet naprijed bez promjene Uvijek na vrhu. Ponovni "
    L"start aktivira postojeću instancu i po potrebi vraća posljednje skrivene vidžete. Veličine "
    L"brojčanika i sekundna kazaljka zavise od Windows-a. Alarm i Signal prebacuju se i iz "
    L"menija; Alarm pokazuje vrijeme i aktivne dane kada nije izabrana cijela nedjelja. Označeno "
    L"Isključi zvuk odgovara opciji Zvuk isključen na kartici Opšte. Isključi sav zvuk isključuje "
    L"zvuk svih vidžeta, a ponovljena radnja vraća zvuk samo onima koje je sama isključila. M na "
    L"svakom vidžetu radi isto. Uključivanje alarma bez izabranih dana otvara njegovu karticu "
    L"Alarm.",
    L"\r\n\r\nНалады і меню\r\nМова праграмы, шрыфт, згладжванне, тэмы, сховішча, запуск з "
    L"Windows і прывязка да краёў задаюцца для ўсёй праграмы на ўкладцы «Праграма». Пры першым "
    L"запуску выбіраецца мова інтэрфейсу Windows; калі яна не падтрымліваецца, выкарыстоўваецца "
    L"амерыканская англійская. Мова, згладжванне і тэмы віджэта ўплываюць толькі на яго. "
    L"\r\n\r\nМеню віджэта мае даступныя яму налады бачнасці, «Заўсёды зверху», секунд, памеру і "
    L"капіявання даты, далей — «Упарадкаваць па сетцы», «Налады», «Даведка», «Пра праграму» і "
    L"«Выйсці». Меню значка змяшчае нумараваныя віджэты ды «Паказаць усё», «Схаваць усё» і "
    L"«Выключыць увесь гук», затым асобна — «Упарадкаваць па сетцы». Паказ ці аднаўленне "
    L"выводзіць віджэт наперад без змены «Заўсёды зверху». Паўторны запуск актывуе існы асобнік і "
    L"пры патрэбе аднаўляе апошнія схаваныя віджэты. Памеры цыферблата і секундная стрэлка "
    L"залежаць ад версіі Windows. Будзільнік і сігнал пераключаюцца і ў меню; будзільнік паказвае "
    L"час і выбраныя дні, калі выбраны не ўвесь тыдзень. Пазначанае «Выключыць гук» адпавядае "
    L"«Без гуку» на ўкладцы «Агульныя». «Выключыць увесь гук» выключае гук усіх віджэтаў, а "
    L"паўтор аднаўляе яго толькі ў тых, якія гэтая каманда адключыла. M на любым віджэце робіць "
    L"тое самае. Уключэнне будзільніка без выбраных дзён адкрывае яго ўкладку «Будзільнік».",
    L"\r\n\r\nНастройки и менюта\r\nЕзикът, шрифтът, изглаждането, темите, хранилището, "
    L"стартирането с Windows и прилепването са общи настройки в раздела „Програма“. При първо "
    L"стартиране се избира езикът на интерфейса на Windows; ако не се поддържа, се използва "
    L"американски английски. Езикът, изглаждането и темите на модула влияят само на него. "
    L"\r\n\r\nМенюто на модул съдържа приложимите настройки за видимост, „Винаги отгоре“, "
    L"секунди, размер и копиране на дата, следвани от „Подреди в мрежа“, „Настройки“, „Помощ“, "
    L"„За програмата“ и „Изход“. Менюто на иконата изброява номерирани модули и „Покажи всички“, "
    L"„Скрий всички“, „Изключи целия звук“, след което отделно е „Подреди в мрежа“. Показването "
    L"или възстановяването извежда модула отпред без промяна на „Винаги отгоре“. Повторният старт "
    L"активира работещия екземпляр и при нужда възстановява последно скритите модули. Размерите "
    L"на циферблата и секундната стрелка зависят от Windows. Алармата и сигналът се превключват и "
    L"от менюто; алармата показва часа и избраните дни, ако не е избрана цялата седмица. "
    L"Отметнатото „Изключи звука“ съответства на „Без звук“ в раздела „Общи“. „Изключи целия "
    L"звук“ изключва звука на всички модули, а повторението възстановява само тези, които тази "
    L"команда е изключила. M върху всеки модул прави същото. Включването на аларма без избрани "
    L"дни отваря нейния раздел „Аларма“.",
    L"\r\n\r\nПоставки и менија\r\nЈазикот, фонтот, измазнувањето, темите, складиштето, "
    L"стартувањето со Windows и прилепувањето се општи поставки на картичката „Програма“. При "
    L"првото стартување се избира јазикот на интерфејсот на Windows; ако не е поддржан, се "
    L"користи американски англиски. Јазикот, измазнувањето и темите на виџетот влијаат само на "
    L"него. \r\n\r\nМенито на виџетот содржи достапни поставки за видливост, „Секогаш најгоре“, "
    L"секунди, големина и копирање датум, потоа „Распореди во мрежа“, „Поставки“, „Помош“, „За "
    L"програмата“ и „Излез“. Менито на иконата ги наведува нумерираните виџети, „Прикажи ги "
    L"сите“, „Скриј ги сите“ и „Исклучи го целиот звук“, па одделно „Распореди во мрежа“. "
    L"Покажувањето или враќањето го носи виџетот напред без промена на „Секогаш најгоре“. "
    L"Повторниот старт го активира постојниот примерок и по потреба ги враќа последно скриените "
    L"виџети. Големините на бројчаникот и секундната стрелка зависат од Windows. Алармот и "
    L"сигналот се менуваат и од менито; алармот ги покажува времето и избраните денови кога не е "
    L"избрана целата недела. Означеното „Исклучи го звукот“ одговара на „Без звук“ во „Општо“. "
    L"„Исклучи го целиот звук“ го исклучува звукот на сите виџети, а повторувањето го враќа само "
    L"кај оние што ги исклучила оваа команда. M на кој било виџет го прави истото. Вклучувањето "
    L"аларм без избрани денови ја отвора неговата картичка „Аларм“.",
    L"\r\n\r\nПодешавања и менији\r\nЈезик програма, фонт, умекшавање, теме, складиште, покретање "
    L"уз Windows и прилепљивање су заједничке поставке на картици Програм. При првом покретању "
    L"бира се језик интерфејса Windows-а; ако није подржан, користи се амерички енглески. Језик, "
    L"умекшавање и теме виџета утичу само на њега. \r\n\r\nМени виџета садржи примењиве поставке "
    L"видљивости, Увек на врху, секунди, величине и копирања датума, затим Распореди у мрежу, "
    L"Подешавања, Помоћ, О програму и Излаз. Мени иконе наводи нумерисане виџете, Прикажи све, "
    L"Сакриј све и Искључи сав звук, па одвојено Распореди у мрежу. Приказ или враћање доводи "
    L"виџет напред без промене Увек на врху. Поновни старт активира постојећу инстанцу и по "
    L"потреби враћа последње скривене виџете. Величине бројчаника и секундна казаљка зависе од "
    L"Windows-а. Аларм и Сигнал пребацују се и из менија; Аларм показује време и активне дане "
    L"када није изабрана цела недеља. Означено Искључи звук одговара опцији Звук искључен на "
    L"картици Опште. Искључи сав звук искључује звук свих виџета, а поновљена радња враћа звук "
    L"само онима које је сама искључила. M на сваком виџету ради исто. Укључивање аларма без "
    L"изабраних дана отвара његову картицу Аларм.",
    L"\r\n\r\nНАЛАШТУВАННЯ ТА МЕНЮ\r\nМова програми, шрифт, згладжування, теми, сховище, запуск "
    L"разом із Windows і прив’язка до країв задаються для всієї програми на вкладці «Програма». "
    L"Під час першого запуску мова вибирається за мовою інтерфейсу Windows; якщо вона не "
    L"підтримується, використовується англійська (США). Мова, згладжування та теми віджета "
    L"впливають лише на нього. \r\n\r\nМеню віджета містить доступні для нього команди видимості, "
    L"режиму «Завжди зверху», секунд, розміру та формату копіювання дати, а далі — «Упорядкувати "
    L"за сіткою», «Налаштування», «Довідка», «Про програму» та «Вийти». Меню піктограми в області "
    L"сповіщень містить нумерований список віджетів і команди «Показати все», «Приховати все» та "
    L"«Вимкнути весь звук». Далі окремо розташовано команду «Упорядкувати за сіткою». Показ або "
    L"відновлення віджета виводить його на передній план без зміни режиму «Завжди зверху». "
    L"Повторний запуск CalClock активує вже запущений примірник і за потреби відновлює останні "
    L"приховані віджети. Доступні розміри циферблата та підтримка секундної стрілки залежать від "
    L"установленої версії Windows. Будильник і сигнал можна перемикати безпосередньо в меню "
    L"віджета; пункт будильника показує час і, якщо вибрано не весь тиждень, активні дні. "
    L"Позначена команда «Вимкнути звук» відповідає прапорцю «Без звуку» на вкладці «Загальні». "
    L"«Вимкнути весь звук» вимикає звук усіх віджетів, а повторне виконання відновлює звук лише "
    L"тих, які ця команда вимкнула. Клавіша M на будь-якому віджеті виконує те саме перемикання. "
    L"Якщо ввімкнути будильник без вибраних днів тижня, відкривається його вкладка «Будильник».",
    L"\r\n\r\nНАСТРОЙКИ И МЕНЮ\r\nЯзык программы, шрифт, сглаживание, темы, хранилище, запуск "
    L"вместе с Windows и привязка к краям задаются для всей программы на вкладке «Программа». При "
    L"первом запуске язык выбирается по языку интерфейса Windows; если он не поддерживается, "
    L"используется английский (США). Язык, сглаживание и темы виджета влияют только на него. "
    L"\r\n\r\nМеню виджета содержит доступные для него команды видимости, режима «Поверх всех "
    L"окон», секунд, размера и формата копирования даты, а затем — «Упорядочить по сетке», "
    L"«Настройки», «Справка», «О программе» и «Выход». Меню значка в области уведомлений содержит "
    L"нумерованный список виджетов и команды «Показать всё», «Скрыть всё» и «Выключить весь звук». "
    L"Далее отдельно расположена команда «Упорядочить по сетке». Показ или восстановление виджета "
    L"выводит его на передний план без изменения режима «Поверх всех окон». Повторный запуск "
    L"CalClock активирует уже запущенный экземпляр и при необходимости восстанавливает последние "
    L"скрытые виджеты. Доступные размеры циферблата и поддержка секундной стрелки зависят от "
    L"установленной версии Windows. Будильник и сигнал можно переключать непосредственно в меню "
    L"виджета; пункт будильника показывает время и, если выбрана не вся неделя, активные дни. "
    L"Отмеченная команда «Выключить звук» соответствует флажку «Без звука» на вкладке «Общие». "
    L"«Выключить весь звук» отключает звук всех виджетов, а повторное выполнение восстанавливает "
    L"звук только тех, у которых эта команда его отключила. Клавиша M на любом виджете выполняет "
    L"то же переключение. Если включить будильник без выбранных дней недели, открывается его "
    L"вкладка «Будильник»."
};

const wchar_t* HELP_TIME_SIGNAL_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZVUKOVÉ ČASOVÉ ZNAMENÍ\r\nZnamení odpovídá Greenwich Time Signal (GTS). Na kartě "
    L"Znamení je zatržítko Časové znamení aktivní a přepínače intervalů 1, 5, 10, 15, 20, 30 nebo "
    L"60 minut podle času zobrazovaného widgetem. Znamení je zpočátku vypnuté a je zvolen "
    L"hodinový interval. Vypnutí a zapnutí příkazem Signál v menu widgetu interval zachovává. "
    L"Menu zobrazuje čas budíku a interval znamení v závorkách. Časová hranice vychází z času "
    L"daného widgetu včetně UTC, časového pásma, offsetu a případné korekce NTP. Pět krátkých "
    L"tónů zazní v posledních pěti sekundách a dlouhý tón přesně na hranici. Pokud na stejný "
    L"okamžik připadne znamení více widgetů, přehraje se jediná společná sekvence. Po ztlumení "
    L"může právě znějící tón doznít; další tóny se přeskočí a po zrušení ztlumení zazní až "
    L"následující naplánovaný tón. Samostatný Kalendář nepodporuje budík, časové znamení ani "
    L"ztlumení.\r\n\r\nPři intervalu 20 minut znamení zazní v :00, :20 a :40 podle času "
    L"widgetu.\r\n\r\nNa kartě Aplikace lze ve volbě Zvuk časového znamení vybrat Vlastní "
    L"generátor nebo Systémové pípání. Volba platí pro časová znamení všech widgetů včetně "
    L"znamení budíku. Výchozí je Vlastní generátor.\r\n\r\nJezdec Hlasitost časového znamení na "
    L"kartě Aplikace zobrazuje úroveň vlastního generátoru v dB. Pravý doraz je 0 dB, tedy "
    L"maximální nezkreslená amplituda sinusovky; úplné ztišení je −∞ dB. Výchozí hlasitost je −18 "
    L"dB. Tlačítko Vyzkoušet vedle volby Zvuk časového znamení zapne stálou ukázku, Zastavit test "
    L"ji ukončí. Otestovat lze oba druhy zvuku; test se neukládá. Ukázka zní také po dobu držení "
    L"jezdce myší; po uvolnění skončí, pokud neběží test zapnutý tlačítkem. Začne až na "
    L"následující celé sekundě, krátce každou sekundu a dlouze v :00, :05, :10 atd. Souběžná "
    L"ukázka a časová znamení widgetů či budíků zaznějí jako jediný tón. Při zastavení testu "
    L"právě rozehraný píp dozní; u dlouhého pípu to může trvat až půl sekundy. Offsety widgetů se "
    L"uplatní i v setinách sekundy. Překrývající se tóny widgetů, budíků a testu znějí jako "
    L"jediný souvislý tón až do konce posledního překryvu.",
    L"\r\n\r\nAUDIBLE TIME SIGNAL\r\nThe signal follows the Greenwich Time Signal (GTS) pattern. "
    L"The Signal tab has a Time signal active checkbox and radio buttons for intervals of 1, 5, "
    L"10, 15, 20, 30, or 60 minutes according to the widget's displayed time. Signals are "
    L"initially off, with an hourly interval selected. Turning Signal off and on in the widget "
    L"menu retains the interval. The menu shows the alarm time and signal interval in "
    L"parentheses. The boundary follows that widget’s time, including UTC, time zone, offset, and "
    L"any NTP correction. Five short pips sound during the final five seconds and a long pip "
    L"exactly on the boundary. If several widgets signal at the same instant, only one shared "
    L"sequence is played. After muting, a pip already sounding may finish; later pips are skipped "
    L"and only the next scheduled pip sounds after unmuting. A standalone Calendar supports "
    L"neither alarms, time signals nor muting.\r\n\r\nWith a 20-minute interval, signals sound at "
    L":00, :20 and :40 in the widget's displayed time.\r\n\r\nOn the Application tab, Time signal "
    L"sound lets you choose between Built-in generator and System beep. The choice applies to "
    L"time signals from all widgets, including alarm time signals. Built-in generator is the "
    L"default.\r\n\r\nThe Time signal volume slider on the Application tab shows the built-in "
    L"generator’s level in dB. The rightmost position is 0 dB, the maximum undistorted sine-wave "
    L"amplitude; silence is −∞ dB. The default volume is −18 dB. Click Test next to Time signal "
    L"sound to start a continuous preview, or Stop test to end it. Both sound options can be "
    L"tested; the test is not saved. Holding the volume slider also plays a preview until the "
    L"mouse is released, unless the button test is running. Playback starts on the next whole "
    L"second: short tones every second and a long tone at :00, :05, :10, and so on. Simultaneous "
    L"preview, widget, and alarm time signals share a single tone. Stopping the test lets the "
    L"current pip finish; a long pip can take up to half a second to end. Widget offsets also "
    L"apply in hundredths of a second. Overlapping widget, alarm, and test tones play as one "
    L"continuous tone until the last overlap ends.",
    L"\r\n\r\nAKUSTISCHES ZEITZEICHEN\r\nDas Signal entspricht dem Greenwich Time Signal (GTS). "
    L"Auf der Registerkarte Zeitzeichen gibt es das Kontrollkästchen Zeitzeichen aktiv und "
    L"Optionsfelder für Intervalle von 1, 5, 10, 15, 20, 30 oder 60 Minuten gemäß der angezeigten "
    L"Widget-Zeit. Anfangs ist das Signal ausgeschaltet und das Stundenintervall ausgewählt. Aus- "
    L"und Einschalten über Zeitzeichen im Widget-Menü behält das Intervall bei. Das Menü zeigt "
    L"die Weckzeit und das Signalintervall in Klammern. Die Grenze folgt der Zeit dieses Widgets "
    L"einschließlich UTC, Zeitzone, Offset und einer möglichen NTP-Korrektur. In den letzten fünf "
    L"Sekunden erklingen fünf kurze Töne und genau an der Grenze ein langer Ton. Fallen Signale "
    L"mehrerer Widgets auf denselben Zeitpunkt, wird nur eine gemeinsame Folge wiedergegeben. "
    L"Beim Stummschalten darf ein bereits klingender Ton enden; weitere Töne werden bis zum "
    L"nächsten geplanten Ton nach dem Aufheben übersprungen. Ein einzelner Kalender unterstützt "
    L"weder Wecker noch Zeitzeichen oder Stummschaltung.\r\n\r\nBeim 20-Minuten-Intervall ertönt "
    L"das Zeitzeichen um :00, :20 und :40 gemäß der Widget-Zeit.\r\n\r\nAuf der Registerkarte "
    L"Anwendung können Sie unter Klang des Zeitzeichens zwischen Interner Generator und "
    L"Systemsignalton wählen. Die Auswahl gilt für die Zeitzeichen aller Widgets einschließlich "
    L"der Zeitzeichen des Weckers. Standardmäßig ist Interner Generator ausgewählt.\r\n\r\nDer "
    L"Lautstärkeregler für das Zeitzeichen auf der Registerkarte Anwendung zeigt den Pegel des "
    L"eingebauten Generators in dB. Der rechte Anschlag entspricht 0 dB, der maximalen "
    L"unverzerrten Sinusamplitude; Stille entspricht −∞ dB. Die Standardlautstärke beträgt −18 "
    L"dB. Mit Testen neben Klang des Zeitzeichens starten Sie eine fortlaufende Vorschau, mit "
    L"Test stoppen beenden Sie sie. Beide Klangarten lassen sich testen; der Test wird nicht "
    L"gespeichert. Auch das Festhalten des Lautstärkereglers startet eine Vorschau bis zum "
    L"Loslassen, sofern der Tastentest nicht läuft. Die Wiedergabe beginnt zur nächsten vollen "
    L"Sekunde: kurze Töne jede Sekunde und ein langer bei :00, :05, :10 usw. Gleichzeitige "
    L"Signale von Vorschau, Widgets und Alarmen werden zu einem Ton zusammengefasst. Beim Stoppen "
    L"des Tests klingt der aktuelle Ton aus; ein langer Ton kann noch bis zu einer halben Sekunde "
    L"dauern. Widget-Versätze gelten auch in Hundertstelsekunden. Überlappende Töne von Widgets, "
    L"Weckern und Tests erklingen als ein durchgehender Ton bis zum Ende der letzten Überlappung.",
    L"\r\n\r\nSIGNAL HORAIRE SONORE\r\nLe signal reprend le Greenwich Time Signal (GTS). L’onglet "
    L"Signal propose la case Signal horaire actif et des boutons radio pour les intervalles de 1, "
    L"5, 10, 15, 20, 30 ou 60 minutes selon l’heure affichée par le widget. Le signal est "
    L"initialement désactivé, avec un intervalle d’une heure sélectionné. Désactiver puis "
    L"réactiver Signal dans le menu du widget conserve l’intervalle. Le menu affiche l’heure de "
    L"l’alarme et l’intervalle du signal entre parenthèses. La limite suit l’heure du widget, y "
    L"compris UTC, le fuseau horaire, le décalage et toute correction NTP. Cinq bips courts "
    L"retentissent pendant les cinq dernières secondes et un bip long exactement à la limite. Si "
    L"plusieurs widgets signalent au même instant, une seule séquence commune est jouée. Lors de "
    L"la coupure, un bip déjà commencé peut finir ; les suivants sont ignorés et seul le prochain "
    L"bip planifié retentit après le rétablissement. Un Calendrier autonome ne propose ni alarme, "
    L"ni signal horaire, ni coupure du son.\r\n\r\nAvec un intervalle de 20 minutes, le signal "
    L"retentit à :00, :20 et :40 selon l’heure du widget.\r\n\r\nDans l’onglet Application, Son "
    L"du signal horaire permet de choisir entre Générateur intégré et Bip système. Ce choix "
    L"s’applique aux signaux horaires de tous les widgets, y compris ceux des alarmes. Le "
    L"Générateur intégré est sélectionné par défaut.\r\n\r\nLe curseur du volume du signal "
    L"horaire dans l’onglet Application affiche le niveau du générateur intégré en dB. La "
    L"position maximale est 0 dB, soit l’amplitude sinusoïdale maximale sans distorsion ; le "
    L"silence est −∞ dB. Le volume par défaut est de −18 dB. Cliquez sur Tester à côté du son du "
    L"signal horaire pour démarrer un aperçu continu, puis sur Arrêter le test pour le terminer. "
    L"Les deux sons peuvent être testés ; le test n’est pas enregistré. Maintenir le curseur de "
    L"volume lance aussi un aperçu jusqu’au relâchement, sauf si le test par bouton est actif. La "
    L"lecture commence à la seconde entière suivante : sons courts chaque seconde et son long à "
    L":00, :05, :10, etc. Les signaux simultanés de l’aperçu, des widgets et des alarmes "
    L"produisent un seul son. À l’arrêt du test, le son en cours se termine ; un son long peut "
    L"encore durer jusqu’à une demi-seconde. Le curseur suit une échelle en décibels ; −18 dB se "
    L"trouve au milieu.\r\n\r\nLe choix du son est disponible uniquement si le système prend en "
    L"charge les deux options. Les décalages des widgets s’appliquent aussi aux centièmes de "
    L"seconde. Les sons des widgets, alarmes et tests qui se chevauchent forment un seul son "
    L"continu jusqu’à la fin du dernier chevauchement.",
    L"\r\n\r\nSEÑAL HORARIA SONORA\r\nLa señal sigue el patrón del Greenwich Time Signal (GTS). "
    L"La pestaña Señal incluye la casilla Señal horaria activa y botones de opción para "
    L"intervalos de 1, 5, 10, 15, 20, 30 o 60 minutos según la hora mostrada por el widget. La "
    L"señal está inicialmente desactivada y el intervalo seleccionado es de una hora. Desactivar "
    L"y activar Señal en el menú del widget conserva el intervalo. El menú muestra la hora de la "
    L"alarma y el intervalo de la señal entre paréntesis. El límite sigue la hora del widget, "
    L"incluidos UTC, zona horaria, offset y cualquier corrección NTP. Cinco pitidos cortos suenan "
    L"durante los últimos cinco segundos y uno largo exactamente en el límite. Si varios widgets "
    L"coinciden, se reproduce una única secuencia compartida. Al silenciar, puede terminar el "
    L"pitido que ya suena; los siguientes se omiten y, al reactivar el sonido, suena solo el "
    L"próximo pitido programado. Un Calendario independiente no admite alarma, señal horaria ni "
    L"silencio.\r\n\r\nCon un intervalo de 20 minutos, la señal suena a :00, :20 y :40 según la "
    L"hora del widget.\r\n\r\nEn la pestaña Aplicación, Sonido de la señal horaria permite elegir "
    L"entre Generador integrado y Pitido del sistema. La elección se aplica a las señales "
    L"horarias de todos los widgets, incluidas las de las alarmas. Generador integrado es la "
    L"opción predeterminada.\r\n\r\nEl control de volumen de la señal horaria en la pestaña "
    L"Aplicación muestra el nivel del generador integrado en dB. El extremo derecho es 0 dB, la "
    L"amplitud sinusoidal máxima sin distorsión; el silencio es −∞ dB. El volumen predeterminado "
    L"es −18 dB. Pulse Probar junto al sonido de la señal horaria para iniciar una prueba "
    L"continua y Detener prueba para finalizarla. Se pueden probar ambos sonidos; la prueba no se "
    L"guarda. Mantener pulsado el control de volumen también reproduce una prueba hasta soltarlo, "
    L"salvo que siga activa la prueba del botón. Empieza en el siguiente segundo entero: tonos "
    L"cortos cada segundo y uno largo en :00, :05, :10, etc. Las señales simultáneas de la "
    L"prueba, los widgets y las alarmas se combinan en un solo tono. Al detener la prueba, el "
    L"tono actual termina; un tono largo puede tardar hasta medio segundo. Los desfases de los "
    L"widgets también se aplican en centésimas de segundo. Los tonos superpuestos de widgets, "
    L"alarmas y pruebas suenan como un único tono continuo hasta que termina la última "
    L"superposición.",
    L"\r\n\r\nSEGNALE ORARIO ACUSTICO\r\nIl segnale segue lo schema del Greenwich Time Signal "
    L"(GTS). La scheda Segnale contiene la casella Segnale orario attivo e pulsanti di opzione "
    L"per intervalli di 1, 5, 10, 15, 20, 30 o 60 minuti secondo l’ora visualizzata dal widget. "
    L"Inizialmente il segnale è disattivato e l’intervallo selezionato è di un’ora. Disattivare e "
    L"riattivare Segnale nel menu del widget mantiene l’intervallo. Il menu mostra tra parentesi "
    L"l’ora della sveglia e l’intervallo del segnale. Il limite segue l’ora del widget, inclusi "
    L"UTC, fuso orario, offset ed eventuale correzione NTP. Cinque segnali brevi suonano negli "
    L"ultimi cinque secondi e uno lungo esattamente al limite. Se più widget coincidono, viene "
    L"riprodotta una sola sequenza comune. Disattivando l’audio, un segnale già iniziato può "
    L"terminare; i successivi vengono saltati e, alla riattivazione, suona solo il prossimo "
    L"segnale programmato. Un Calendario autonomo non supporta sveglia, segnale orario o "
    L"disattivazione audio.\r\n\r\nCon un intervallo di 20 minuti, il segnale suona a :00, :20 e "
    L":40 secondo l’ora del widget.\r\n\r\nNella scheda Applicazione, Suono del segnale orario "
    L"consente di scegliere tra Generatore integrato e Segnale acustico di sistema. La scelta si "
    L"applica ai segnali orari di tutti i widget, inclusi quelli delle sveglie. Generatore "
    L"integrato è l’opzione predefinita.\r\n\r\nIl cursore del volume del segnale orario nella "
    L"scheda Applicazione mostra il livello del generatore integrato in dB. L’estremità destra è "
    L"0 dB, l’ampiezza sinusoidale massima senza distorsione; il silenzio è −∞ dB. Il volume "
    L"predefinito è −18 dB. Premere Prova accanto al suono del segnale orario per avviare una "
    L"prova continua e Ferma prova per terminarla. Entrambi i suoni possono essere provati; la "
    L"prova non viene salvata. Tenere premuto il cursore del volume avvia una prova fino al "
    L"rilascio, a meno che sia attiva la prova con il pulsante. Inizia al secondo intero "
    L"successivo: toni brevi ogni secondo e uno lungo a :00, :05, :10 ecc. I segnali simultanei "
    L"di prova, widget e sveglie vengono uniti in un solo tono. Quando si interrompe la prova, il "
    L"tono in corso termina; un tono lungo può richiedere fino a mezzo secondo. Gli offset dei "
    L"widget si applicano anche ai centesimi di secondo. I toni sovrapposti di widget, sveglie e "
    L"test formano un unico tono continuo fino alla fine dell’ultima sovrapposizione.",
    L"\r\n\r\nDŹWIĘKOWY SYGNAŁ CZASU\r\nSygnał odpowiada Greenwich Time Signal (GTS). Karta "
    L"Sygnał zawiera pole Sygnał czasu aktywny oraz przyciski opcji dla odstępów 1, 5, 10, 15, "
    L"20, 30 lub 60 minut według czasu wyświetlanego przez widżet. Początkowo sygnał jest "
    L"wyłączony i wybrany jest odstęp jednej godziny. Wyłączenie i włączenie opcji Sygnał w menu "
    L"widżetu zachowuje odstęp. Menu pokazuje godzinę alarmu i odstęp sygnału w nawiasach. "
    L"Granica wynika z czasu widżetu, w tym UTC, strefy czasowej, offsetu i korekty NTP. Pięć "
    L"krótkich sygnałów rozlega się w ostatnich pięciu sekundach, a długi dokładnie na granicy. "
    L"Gdy sygnały wielu widżetów przypadają jednocześnie, odtwarzana jest jedna wspólna "
    L"sekwencja. Po wyciszeniu rozpoczęty sygnał może wybrzmieć; następne są pomijane, a po "
    L"włączeniu dźwięku zabrzmi dopiero kolejny zaplanowany sygnał. Samodzielny Kalendarz nie "
    L"obsługuje alarmu, sygnału czasu ani wyciszenia.\r\n\r\nPrzy odstępie 20 minut sygnał "
    L"rozlega się o :00, :20 i :40 według czasu widżetu.\r\n\r\nNa karcie Aplikacja opcja Dźwięk "
    L"sygnału czasu pozwala wybrać Wbudowany generator lub Sygnał systemowy. Wybór dotyczy "
    L"sygnałów czasu wszystkich widżetów, w tym sygnałów alarmu. Domyślnie wybrany jest Wbudowany "
    L"generator.\r\n\r\nSuwak głośności sygnału czasu na karcie Aplikacja pokazuje poziom "
    L"wbudowanego generatora w dB. Prawe skrajne położenie to 0 dB, czyli maksymalna "
    L"niezniekształcona amplituda sinusoidy; cisza to −∞ dB. Domyślna głośność wynosi −18 dB. "
    L"Kliknij Testuj obok dźwięku sygnału czasu, aby rozpocząć ciągły odsłuch, lub Zatrzymaj "
    L"test, aby go zakończyć. Można testować oba dźwięki; test nie jest zapisywany. Przytrzymanie "
    L"suwaka głośności również uruchamia odsłuch do puszczenia myszy, chyba że trwa test włączony "
    L"przyciskiem. Odsłuch zaczyna się od następnej pełnej sekundy: krótkie dźwięki co sekundę, "
    L"długi o :00, :05, :10 itd. Jednoczesne sygnały odsłuchu, widżetów i alarmów są łączone w "
    L"jeden dźwięk. Po zatrzymaniu testu bieżący dźwięk wybrzmi do końca; długi dźwięk może trwać "
    L"jeszcze do pół sekundy. Suwak ma skalę decybelową; −18 dB znajduje się w połowie "
    L"zakresu.\r\n\r\nWybór dźwięku jest dostępny tylko wtedy, gdy system obsługuje obie opcje. "
    L"Przesunięcia widżetów uwzględniają także setne części sekundy. Nakładające się tony "
    L"widżetów, alarmów i testów tworzą jeden ciągły ton do końca ostatniego nakładania.",
    L"\r\n\r\nZVUKOVÉ ČASOVÉ ZNAMENIE\r\nZnamenie zodpovedá Greenwich Time Signal (GTS). Na karte "
    L"Znamenie je začiarkavacie políčko Časové znamenie aktívne a prepínače intervalov 1, 5, 10, "
    L"15, 20, 30 alebo 60 minút podľa času zobrazovaného widgetom. Znamenie je spočiatku vypnuté "
    L"a je zvolený hodinový interval. Vypnutie a zapnutie príkazom Signál v menu widgetu "
    L"zachováva interval. Menu zobrazuje čas budíka a interval znamenia v zátvorkách. Časová "
    L"hranica vychádza z času daného widgetu vrátane UTC, časového pásma, offsetu a prípadnej "
    L"korekcie NTP. Päť krátkych tónov zaznie v posledných piatich sekundách a dlhý tón presne na "
    L"hranici. Ak na rovnaký okamih pripadne znamenie viacerých widgetov, prehrá sa jediná "
    L"spoločná sekvencia. Po stlmení môže práve znejúci tón doznieť; ďalšie sa preskočia a po "
    L"zrušení stlmenia zaznie až nasledujúci naplánovaný tón. Samostatný Kalendár nepodporuje "
    L"budík, časové znamenie ani stlmenie.\r\n\r\nPri intervale 20 minút znamenie zaznie v :00, "
    L":20 a :40 podľa času widgetu.\r\n\r\nNa karte Aplikácia možno vo voľbe Zvuk časového "
    L"znamenia vybrať Vlastný generátor alebo Systémové pípanie. Voľba platí pre časové znamenia "
    L"všetkých widgetov vrátane znamení budíka. Predvolený je Vlastný generátor.\r\n\r\nJazdec "
    L"Hlasitosť časového znamenia na karte Aplikácia zobrazuje úroveň vlastného generátora v dB. "
    L"Pravý doraz je 0 dB, teda maximálna neskreslená amplitúda sínusovky; úplné stíšenie je −∞ "
    L"dB. Predvolená hlasitosť je −18 dB. Tlačidlo Vyskúšať vedľa voľby Zvuk časového znamenia "
    L"zapne stálu ukážku, Zastaviť test ju ukončí. Otestovať možno oba druhy zvuku; test sa "
    L"neukladá. Ukážka znie aj počas držania jazdca myšou; po uvoľnení skončí, ak nebeží test "
    L"zapnutý tlačidlom. Začne až na nasledujúcej celej sekunde, krátko každú sekundu a dlho v "
    L":00, :05, :10 atď. Súbežná ukážka a časové znamenia widgetov či budíkov zaznejú ako jediný "
    L"tón. Pri zastavení testu práve rozohraný tón doznie; pri dlhom tóne to môže trvať až pol "
    L"sekundy. Offsety widgetov sa uplatnia aj v stotinách sekundy. Prekrývajúce sa tóny "
    L"widgetov, budíkov a testu znejú ako jediný súvislý tón až do konca posledného prekrytia.",
    L"\r\n\r\nAUDIBLE TIME SIGNAL\r\nThe signal follows the Greenwich Time Signal (GTS) pattern. "
    L"The Signal tab has a Time signal active checkbox and radio buttons for intervals of 1, 5, "
    L"10, 15, 20, 30, or 60 minutes according to the widget's displayed time. Signals are "
    L"initially off, with an hourly interval selected. Turning Signal off and on in the widget "
    L"menu retains the interval. The menu shows the alarm time and signal interval in "
    L"parentheses. The boundary follows that widget’s time, including UTC, time zone, offset, and "
    L"any NTP correction. Five short pips sound during the final five seconds and a long pip "
    L"exactly on the boundary. If several widgets signal at the same instant, only one shared "
    L"sequence is played. After muting, a pip already sounding may finish; later pips are skipped "
    L"and only the next scheduled pip sounds after unmuting. A standalone Calendar supports "
    L"neither alarms, time signals nor muting.\r\n\r\nWith a 20-minute interval, signals sound at "
    L":00, :20 and :40 in the widget's displayed time.\r\n\r\nOn the Application tab, Time signal "
    L"sound lets you choose between Built-in generator and System beep. The choice applies to "
    L"time signals from all widgets, including alarm time signals. Built-in generator is selected "
    L"by default.\r\n\r\nThe Time signal volume slider on the Application tab shows the built-in "
    L"generator’s level in dB. The rightmost position is 0 dB, the maximum undistorted sine-wave "
    L"amplitude; silence is −∞ dB. The default volume is −18 dB. Click Test next to Time signal "
    L"sound to start a continuous preview, or Stop test to end it. Both sound options can be "
    L"tested; the test is not saved. Holding the volume slider also plays a preview until the "
    L"mouse is released, unless the button test is running. Playback starts on the next whole "
    L"second: short tones every second and a long tone at :00, :05, :10, and so on. Simultaneous "
    L"preview, widget, and alarm time signals share a single tone. Stopping the test lets the "
    L"current pip finish; a long pip can take up to half a second to end. Widget offsets also "
    L"apply in hundredths of a second. Overlapping widget, alarm, and test tones play as one "
    L"continuous tone until the last overlap ends.",
    L"\r\n\r\nAUDIBLE TIME SIGNAL\r\nThe signal follows the Greenwich Time Signal (GTS) pattern. "
    L"The Signal tab has a Time signal active checkbox and radio buttons for intervals of 1, 5, "
    L"10, 15, 20, 30, or 60 minutes according to the widget's displayed time. Signals are "
    L"initially off, with an hourly interval selected. Turning Signal off and on in the widget "
    L"menu retains the interval. The menu shows the alarm time and signal interval in "
    L"parentheses. The boundary follows that widget’s time, including UTC, time zone, offset, and "
    L"any NTP correction. Five short pips sound during the final five seconds and a long pip "
    L"exactly on the boundary. If several widgets signal at the same instant, only one shared "
    L"sequence is played. After muting, a pip already sounding may finish; later pips are skipped "
    L"and only the next scheduled pip sounds after unmuting. A standalone Calendar supports "
    L"neither alarms, time signals nor muting.\r\n\r\nWith a 20-minute interval, signals sound at "
    L":00, :20 and :40 in the widget's displayed time.\r\n\r\nOn the Application tab, Time signal "
    L"sound lets you choose between Built-in generator and System beep. The choice applies to "
    L"time signals from all widgets, including alarm time signals. Built-in generator is selected "
    L"by default.\r\n\r\nThe Time signal volume slider on the Application tab shows the built-in "
    L"generator’s level in dB. The rightmost position is 0 dB, the maximum undistorted sine-wave "
    L"amplitude; silence is −∞ dB. The default volume is −18 dB. Click Test next to Time signal "
    L"sound to start a continuous preview, or Stop test to end it. Both sound options can be "
    L"tested; the test is not saved. Holding the volume slider also plays a preview until the "
    L"mouse is released, unless the button test is running. Playback starts on the next whole "
    L"second: short tones every second and a long tone at :00, :05, :10, and so on. Simultaneous "
    L"preview, widget, and alarm time signals share a single tone. Stopping the test lets the "
    L"current pip finish; a long pip can take up to half a second to end. Widget offsets also "
    L"apply in hundredths of a second. Overlapping widget, alarm, and test tones play as one "
    L"continuous tone until the last overlap ends.",
    L"\r\n\r\nSINAL HORÁRIO SONORO\r\nO sinal segue o padrão do Greenwich Time Signal (GTS). O "
    L"separador Sinal contém a caixa Sinal horário ativo e botões de opção para intervalos de 1, "
    L"5, 10, 15, 20, 30 ou 60 minutos segundo a hora apresentada pelo widget. Inicialmente, o "
    L"sinal está desativado e está selecionado o intervalo de uma hora. Desativar e ativar Sinal "
    L"no menu do widget mantém o intervalo. O menu mostra a hora do alarme e o intervalo do sinal "
    L"entre parênteses. O limite segue a hora do widget, incluindo UTC, fuso, desvio e correção "
    L"NTP. Soam cinco sinais curtos e um longo; sinais simultâneos de vários widgets são unidos. "
    L"Ao silenciar, o sinal já iniciado pode terminar; os seguintes são ignorados e só o próximo "
    L"sinal agendado soa depois de repor o áudio. Um Calendário autónomo não suporta alarme, "
    L"sinal horário nem silenciamento.\r\n\r\nCom um intervalo de 20 minutos, o sinal soa aos "
    L":00, :20 e :40 segundo a hora do widget.\r\n\r\nNo separador Aplicação, Som do sinal "
    L"horário permite escolher entre Gerador integrado e Sinal sonoro do sistema. A escolha "
    L"aplica-se aos sinais horários de todos os widgets, incluindo os dos alarmes. Gerador "
    L"integrado é a opção predefinida.\r\n\r\nO controlo de volume do sinal horário no separador "
    L"Aplicação mostra o nível do gerador integrado em dB. O extremo direito é 0 dB, a amplitude "
    L"sinusoidal máxima sem distorção; o silêncio é −∞ dB. O volume predefinido é −18 dB. Clique "
    L"em Testar junto ao som do sinal horário para iniciar uma pré-visualização contínua e em "
    L"Parar teste para a terminar. Ambos os sons podem ser testados; o teste não é guardado. "
    L"Manter o controlo de volume premido também reproduz uma pré-visualização até o soltar, "
    L"exceto se o teste pelo botão estiver ativo. Começa no segundo inteiro seguinte: sons curtos "
    L"a cada segundo e um longo aos :00, :05, :10, etc. Os sinais simultâneos da "
    L"pré-visualização, dos widgets e dos alarmes produzem um único som. O gerador integrado "
    L"inicia e termina os sons numa passagem por zero, mesmo ao parar um teste. Ao parar o teste, "
    L"o som atual termina; um som longo pode demorar até meio segundo. Os desvios dos widgets "
    L"também se aplicam em centésimos de segundo. Os sons sobrepostos de widgets, alarmes e "
    L"testes formam um único som contínuo até ao fim da última sobreposição.",
    L"\r\n\r\nHØRBART TIDSSIGNAL\r\nSignalet følger mønsteret til Greenwich Time Signal (GTS). "
    L"Signal-fanen har avkrysningsboksen Tidssignal aktivt og alternativknapper for intervaller "
    L"på 1, 5, 10, 15, 20, 30 eller 60 minutter etter widgetens viste tid. Signalet er først "
    L"slått av, med et intervall på én time valgt. Å slå Signal av og på i widgetmenyen beholder "
    L"intervallet. Menyen viser alarmtid og signalintervall i parentes. Grensen følger "
    L"widgettiden, inkludert UTC, tidssone, forskyvning og NTP-korreksjon. Fem korte og ett langt "
    L"pip høres; samtidige signaler fra flere widgeter slås sammen. Ved demping kan et pip som "
    L"allerede har startet fullføres; senere pip hoppes over, og bare neste planlagte pip høres "
    L"etter oppheving. En frittstående Kalender støtter ikke alarm, tidssignal eller "
    L"demping.\r\n\r\nMed et intervall på 20 minutter lyder signalet ved :00, :20 og :40 etter "
    L"widgettiden.\r\n\r\nPå fanen Program kan du under Lyd for tidssignal velge mellom Innebygd "
    L"generator og Systempip. Valget gjelder tidssignaler fra alle widgeter, inkludert "
    L"tidssignaler for alarmer. Innebygd generator er standardvalget.\r\n\r\nVolumglidebryteren "
    L"for tidssignalet på fanen Program viser nivået til den innebygde generatoren i dB. Høyre "
    L"endepunkt er 0 dB, maksimal uforvrengt sinusamplitude; stillhet er −∞ dB. Standardvolumet "
    L"er −18 dB. Klikk Test ved lyden for tidssignalet for å starte kontinuerlig forhåndslytting, "
    L"og Stopp test for å avslutte. Begge lydene kan testes; testen lagres ikke. Å holde "
    L"volumglidebryteren starter også forhåndslytting til musen slippes, med mindre knapptesten "
    L"kjører. Avspillingen begynner på neste hele sekund: korte toner hvert sekund og en lang ved "
    L":00, :05, :10 osv. Samtidige signaler fra forhåndslytting, widgeter og alarmer slås sammen "
    L"til én tone. Når testen stoppes, spilles den pågående tonen ferdig; en lang tone kan vare i "
    L"opptil et halvt sekund. Glidebryteren følger en desibelskala; −18 dB ligger i "
    L"midten.\r\n\r\nLydvalget er bare tilgjengelig når systemet støtter begge alternativene. "
    L"Widgetforskyvninger gjelder også i hundredeler av et sekund. Overlappende toner fra "
    L"widgeter, alarmer og tester spilles som én sammenhengende tone til den siste overlappingen "
    L"er slutt.",
    L"\r\n\r\nHÖRBAR TIDSSIGNAL\r\nSignalen följer mönstret för Greenwich Time Signal (GTS). "
    L"Signal-fliken har kryssrutan Tidssignal aktiv och alternativknappar för intervall på 1, 5, "
    L"10, 15, 20, 30 eller 60 minuter enligt widgetens visade tid. Signalen är från början "
    L"avstängd med en timmes intervall valt. Att stänga av och slå på Signal i widgetens meny "
    L"behåller intervallet. Menyn visar alarmtiden och signalintervallet inom parentes. Gränsen "
    L"följer widgetens tid, inklusive UTC, tidszon, förskjutning och NTP-korrigering. Fem korta "
    L"och ett långt pip hörs; samtidiga signaler från flera widgetar slås samman. Vid tystning "
    L"får ett påbörjat pip avslutas; följande hoppas över och först nästa schemalagda pip hörs "
    L"efter återaktivering. En fristående Kalender stöder inte alarm, tidssignal eller "
    L"tystning.\r\n\r\nMed ett intervall på 20 minuter hörs signalen vid :00, :20 och :40 enligt "
    L"widgetens tid.\r\n\r\nPå fliken Program kan du under Ljud för tidssignal välja mellan "
    L"Inbyggd generator och Systempip. Valet gäller tidssignaler från alla widgetar, inklusive "
    L"tidssignaler för alarm. Inbyggd generator är standardvalet.\r\n\r\nVolymreglaget för "
    L"tidssignalen på fliken Program visar den inbyggda generatorns nivå i dB. Höger ändläge är 0 "
    L"dB, maximal sinusamplitud utan distorsion; tystnad är −∞ dB. Standardvolymen är −18 dB. "
    L"Klicka på Testa vid tidssignalens ljud för att starta kontinuerlig förhandslyssning och på "
    L"Stoppa test för att avsluta. Båda ljuden kan testas; testet sparas inte. Att hålla "
    L"volymreglaget startar också förhandslyssning tills musen släpps, om inte knapptestet körs. "
    L"Uppspelningen börjar vid nästa hela sekund: korta toner varje sekund och en lång vid :00, "
    L":05, :10 osv. Samtidiga signaler från förhandslyssning, widgetar och alarm slås samman till "
    L"en ton. När testet stoppas spelas den pågående tonen klart; en lång ton kan ta upp till en "
    L"halv sekund. Widgetförskjutningar gäller även i hundradels sekunder. Överlappande toner "
    L"från widgetar, alarm och tester spelas som en sammanhängande ton tills den sista "
    L"överlappningen är slut.",
    L"\r\n\r\nÄÄNIMERKKI\r\nAikamerkki noudattaa Greenwich Time Signal (GTS) -mallia. "
    L"Aikamerkki-välilehdellä on Äänimerkki käytössä -valintaruutu ja valintanapit 1, 5, 10, 15, "
    L"20, 30 tai 60 minuutin väleille pienoisohjelman näyttämän ajan mukaan. Äänimerkki on aluksi "
    L"pois käytöstä, ja valittuna on tunnin väli. Aikamerkin poistaminen käytöstä ja ottaminen "
    L"uudelleen käyttöön pienoisohjelman valikosta säilyttää aikavälin. Valikko näyttää "
    L"herätysajan ja aikamerkin välin sulkeissa. Raja seuraa pienoisohjelman aikaa, UTC:tä, "
    L"aikavyöhykettä, poikkeamaa ja NTP-korjausta myöten. Viisi lyhyttä ja yksi pitkä merkki "
    L"kuuluu; samanaikaiset merkit yhdistetään. Mykistettäessä jo alkanut ääni saa päättyä; "
    L"seuraavat ohitetaan ja mykistyksen jälkeen kuuluu vasta seuraava ajastettu ääni. Erillinen "
    L"Kalenteri ei tue herätystä, aikamerkkiä eikä mykistystä.\r\n\r\nKun väli on 20 minuuttia, "
    L"aikamerkki kuuluu kohdissa :00, :20 ja :40 pienoisohjelman ajan "
    L"mukaan.\r\n\r\nSovellus-välilehden aikamerkin ääniasetuksessa voit valita vaihtoehdon "
    L"Sisäinen generaattori tai Järjestelmän äänimerkki. Valinta koskee kaikkien pienoisohjelmien "
    L"aikamerkkejä, myös herätysten aikamerkkejä. Sisäinen generaattori on "
    L"oletusvalinta.\r\n\r\nSovellus-välilehden aikamerkin äänenvoimakkuuden liukusäädin näyttää "
    L"sisäisen generaattorin tason desibeleinä. Oikea ääriasento on 0 dB eli suurin särötön "
    L"siniaallon amplitudi; hiljaisuus on −∞ dB. Oletusäänenvoimakkuus on −18 dB. Napsauta "
    L"aikamerkin ääniasetuksen vieressä Testaa aloittaaksesi jatkuvan esikuuntelun ja Pysäytä "
    L"testi lopettaaksesi sen. Molempia ääniä voi testata; testiä ei tallenneta. Liukusäätimen "
    L"pitäminen painettuna käynnistää myös esikuuntelun hiiren vapauttamiseen asti, ellei "
    L"painikkeella käynnistetty testi ole käynnissä. Toisto alkaa seuraavalla tasasekunnilla: "
    L"lyhyt ääni joka sekunti ja pitkä kohdissa :00, :05, :10 jne. Samanaikaiset esikuuntelun, "
    L"pienoisohjelmien ja herätysten aikamerkit yhdistetään yhdeksi ääneksi. Vain "
    L"äänenvoimakkuuden liukusäädin on pois käytöstä järjestelmän äänimerkin kanssa. Kun testi "
    L"pysäytetään, nykyinen ääni soi loppuun; pitkä ääni voi kestää vielä puoli sekuntia. "
    L"Pienoisohjelmien aikapoikkeamat huomioidaan myös sekunnin sadasosina. Pienoisohjelmien, "
    L"herätysten ja testien päällekkäiset äänet soivat yhtenä jatkuvana äänenä viimeisen "
    L"päällekkäisyyden loppuun asti.",
    L"\r\n\r\nHØRBART TIDSSIGNAL\r\nSignalet følger mønstret for Greenwich Time Signal (GTS). "
    L"Signal-fanen har afkrydsningsfeltet Tidssignal aktivt og alternativknapper til intervaller "
    L"på 1, 5, 10, 15, 20, 30 eller 60 minutter efter widgetens viste tid. Signalet er som "
    L"udgangspunkt slået fra med et interval på én time valgt. Når Signal slås fra og til i "
    L"widgetmenuen, bevares intervallet. Menuen viser alarmtid og signalinterval i parentes. "
    L"Grænsen følger widgettiden, inklusive UTC, tidszone, forskydning og NTP-korrektion. Fem "
    L"korte og ét langt bip lyder; samtidige signaler fra flere widgets flettes sammen. Ved "
    L"dæmpning må et igangværende bip klinge ud; de følgende springes over, og først det næste "
    L"planlagte bip lyder efter ophævelse. En selvstændig Kalender understøtter ikke alarm, "
    L"tidssignal eller dæmpning.\r\n\r\nMed et interval på 20 minutter lyder signalet ved :00, "
    L":20 og :40 efter widgettiden.\r\n\r\nPå fanen Program kan du under Lyd for tidssignal vælge "
    L"mellem Indbygget generator og Systembip. Valget gælder tidssignaler fra alle widgets, "
    L"inklusive tidssignaler for alarmer. Indbygget generator er "
    L"standardvalget.\r\n\r\nLydstyrkeskyderen for tidssignalet på fanen Program viser den "
    L"indbyggede generators niveau i dB. Højre endepunkt er 0 dB, maksimal uforvrænget "
    L"sinusamplitude; stilhed er −∞ dB. Standardlydstyrken er −18 dB. Klik på Test ved "
    L"tidssignalets lyd for at starte vedvarende prøveafspilning og på Stop test for at afslutte. "
    L"Begge lyde kan testes; testen gemmes ikke. At holde lydstyrkeskyderen starter også "
    L"prøveafspilning, indtil musen slippes, medmindre knaptesten kører. Afspilningen begynder på "
    L"næste hele sekund: korte toner hvert sekund og en lang ved :00, :05, :10 osv. Samtidige "
    L"signaler fra prøven, widgets og alarmer samles i én tone. Når testen stoppes, afspilles den "
    L"igangværende tone færdig; en lang tone kan vare op til et halvt sekund. Skyderen følger en "
    L"decibelskala; −18 dB ligger i midten.\r\n\r\nLydvalget er kun tilgængeligt, når systemet "
    L"understøtter begge muligheder. Widgetforskydninger gælder også i hundrededele af et sekund. "
    L"Overlappende toner fra widgets, alarmer og test afspilles som én sammenhængende tone indtil "
    L"den sidste overlapning slutter.",
    L"\r\n\r\nHLJÓÐTÍMAMERKI\r\nMerkið fylgir mynstri Greenwich Time Signal (GTS). "
    L"Tímamerkisflipinn hefur gátreitinn Tímamerki virkt og valhnappa fyrir 1, 5, 10, 15, 20, 30 "
    L"eða 60 mínútna bil samkvæmt sýndum tíma græjunnar. Í upphafi er slökkt á merkinu og "
    L"klukkustundarbil valið. Þegar slökkt og kveikt er á Tímamerki í valmynd græjunnar helst "
    L"bilið óbreytt. Valmyndin sýnir vekjaratímann og tímamerkjabilið innan sviga. Mörkin fylgja "
    L"tíma græjunnar, þar með talið UTC, tímabelti, hliðrun og NTP-leiðrétting. Fimm stutt og "
    L"eitt langt píp hljóma; samtímamerki margra græja eru sameinuð. Við þöggun má þegar hafið "
    L"píp klárast; þeim næstu er sleppt og fyrst næsta áætlaða píp heyrist eftir að þöggun er "
    L"aflétt. Sjálfstætt Dagatal styður hvorki vekjara, tímamerki né þöggun.\r\n\r\nMeð 20 "
    L"mínútna millibili hljómar tímamerkið á :00, :20 og :40 samkvæmt tíma græjunnar.\r\n\r\nÁ "
    L"flipanum Forrit geturðu valið Innbyggður hljóðgjafi eða Kerfishljóð fyrir hljóð "
    L"tímamerkisins. Valið gildir fyrir tímamerki allra græja, þar á meðal tímamerki vekjara. "
    L"Innbyggður hljóðgjafi er sjálfgefinn.\r\n\r\nHljóðstyrkssleði tímamerkisins á flipanum "
    L"Forrit sýnir styrk innbyggða hljóðgjafans í dB. Hægri endastöð er 0 dB, hámarksútslag "
    L"óbjagaðrar sínusbylgju; þögn er −∞ dB. Sjálfgefinn hljóðstyrkur er −18 dB. Smelltu á Prófa "
    L"við hljóð tímamerkisins til að hefja samfellda prufu og á Stöðva prófun til að ljúka henni. "
    L"Hægt er að prófa báðar hljóðgerðir; prufan er ekki vistuð. Að halda hljóðstyrkssleðanum "
    L"niðri byrjar einnig prufu þar til músinni er sleppt, nema prufan með hnappnum sé í gangi. "
    L"Hún hefst á næstu heilu sekúndu: stutt hljóð á hverri sekúndu og langt á :00, :05, :10 "
    L"o.s.frv. Samtímamerki frá prufunni, græjum og vekjurum sameinast í einn tón. Þegar prófun "
    L"er stöðvuð klárast tónninn sem er í gangi; langur tónn getur tekið allt að hálfa sekúndu. "
    L"Hliðrun græja tekur einnig mið af hundraðshlutum úr sekúndu. Tónar frá græjum, vekjurum og "
    L"prófunum sem skarast hljóma sem einn samfelldur tónn þar til síðustu skörun lýkur.",
    L"\r\n\r\nSESLİ ZAMAN SİNYALİ\r\nSinyal, Greenwich Time Signal (GTS) düzenini izler. Sinyal "
    L"sekmesinde Zaman sinyali etkin onay kutusu ve aracın gösterdiği saate göre 1, 5, 10, 15, "
    L"20, 30 veya 60 dakikalık aralıklar için seçenek düğmeleri bulunur. Sinyal başlangıçta "
    L"kapalıdır ve bir saatlik aralık seçilidir. Araç menüsünde Sinyal seçeneğini kapatıp açmak "
    L"aralığı korur. Menü, alarm saatini ve sinyal aralığını parantez içinde gösterir. Sınır; "
    L"UTC, saat dilimi, ofset ve NTP düzeltmesi dâhil aracın zamanını izler. Beş kısa ve bir uzun "
    L"ses çalar; birden çok aracın eşzamanlı sinyalleri birleştirilir. Sessize alındığında "
    L"başlamış olan ses bitebilir; sonrakiler atlanır ve ses açıldıktan sonra yalnızca sıradaki "
    L"planlanmış ses çalar. Bağımsız Takvim alarmı, zaman sinyalini veya sessize almayı "
    L"desteklemez.\r\n\r\n20 dakikalık aralıkta sinyal, aracın saatine göre :00, :20 ve :40’ta "
    L"çalar.\r\n\r\nUygulama sekmesindeki Zaman sinyali sesi seçeneğiyle Yerleşik üreteç veya "
    L"Sistem bip sesi seçilebilir. Bu seçim, alarm zaman sinyalleri de dâhil olmak üzere tüm "
    L"araçların zaman sinyalleri için geçerlidir. Varsayılan seçenek Yerleşik "
    L"üreteçtir.\r\n\r\nUygulama sekmesindeki zaman sinyali ses düzeyi kaydırıcısı, yerleşik "
    L"üretecin düzeyini dB olarak gösterir. En sağ konum 0 dB, yani bozulmamış sinüs dalgasının "
    L"en yüksek genliğidir; sessizlik −∞ dB’dir. Varsayılan ses düzeyi −18 dB’dir. Sürekli "
    L"önizlemeyi başlatmak için zaman sinyali sesinin yanındaki Test et düğmesine, bitirmek için "
    L"Testi durdur düğmesine basın. Her iki ses de test edilebilir; test kaydedilmez. Ses "
    L"kaydırıcısını basılı tutmak da fare bırakılana kadar önizleme yapar; düğmeyle başlatılan "
    L"test sürüyorsa önizleme devam eder. Sonraki tam saniyede başlar: her saniye kısa, :00, :05, "
    L":10 vb. saniyelerde uzun ses çalar. Önizleme, araçlar ve alarmların eşzamanlı sinyalleri "
    L"tek bir seste birleştirilir. Test durdurulduğunda çalmakta olan ses tamamlanır; uzun sesin "
    L"bitmesi yarım saniyeye kadar sürebilir. Araç ofsetleri saniyenin yüzde biri düzeyinde de "
    L"uygulanır. Araçların, alarmların ve testlerin örtüşen tonları son örtüşme bitene kadar tek "
    L"ve kesintisiz bir ton olarak çalar.",
    L"\r\n\r\nKuuldav ajasignaal\r\nSignaal järgib Greenwichi ajasignaali (GTS): viis lühikest "
    L"tooni viimase viie sekundi jooksul ja pikk toon täpsel ajahetkel. Vahekaardil Signaal on "
    L"Ajasignaal lubatud ja intervallid 1, 5, 10, 15, 20, 30 või 60 minutit vidina kuvatava aja "
    L"järgi. Vaikimisi on signaal väljas ja valitud tunnine intervall. Menüü lülitus säilitab "
    L"intervalli. Ajapiir arvestab UTC-d, ajavööndit, nihet ja NTP-d. 20-minutilise intervalliga "
    L"kõlab signaal :00, :20 ja :40. Samaaegsed vidina- ja äratussignaalid ühendatakse. "
    L"Vaigistamisel võib praegune toon lõppeda; järgmised jäetakse vahele ja heli taastamisel "
    L"kõlab alles järgmine kavandatud toon. Eraldi Kalender ei toeta äratust, ajasignaali ega "
    L"vaigistamist.\r\n\r\nVahekaardi Rakendus Ajasignaali heli pakub Sisseehitatud generaatorit "
    L"(vaikimisi) ja Süsteemi helisignaali. Valik kehtib kõigile vidinatele ja äratustele. "
    L"Ajasignaali helitugevus näitab generaatori taset dB-des: parempoolne 0 dB on suurim "
    L"moonutuseta siinusamplituud, −∞ dB vaikus ja vaikesäte −18 dB. Testi käivitab pideva "
    L"prooviesituse ning Peata test lõpetab selle. Testida saab mõlemat heli; testi ei "
    L"salvestata. Liuguri hoidmine esitab samuti heli kuni hiire vabastamiseni, kui nuputest pole "
    L"käimas. Esitus algab järgmisel täissekundil: lühike toon igal sekundil ja pikk toon :00, "
    L":05, :10 jne. Kõik samaaegsed proovi-, vidina- ja äratussignaalid jagavad ühte tooni. "
    L"Peatamine lubab praegusel toonil lõppeda; pikk toon võib kesta veel pool sekundit. "
    L"Arvestatakse ka nihke sajandikke ning kattuvad toonid kõlavad katkestuseta viimase "
    L"kattumise lõpuni.",
    L"\r\n\r\nComhartha ama inchloiste\r\nLeanann an comhartha patrún Greenwich Time Signal "
    L"(GTS): cúig bhíp ghearra sna cúig shoicind dheireanacha agus bíp fhada ag an teorainn ama "
    L"go beacht. Tugann Comhartha an rogha Comhartha ama gníomhach agus eatraimh 1, 5, 10, 15, "
    L"20, 30 nó 60 nóiméad de réir am na giuirléide. Tá sé múchta ar dtús agus eatramh uair an "
    L"chloig roghnaithe. Coinníonn an roghchlár an t-eatramh. Cuirtear UTC, crios ama, "
    L"fritháireamh agus NTP san áireamh; le 20 nóiméad, seinntear ag :00, :20 agus :40. "
    L"Cumaisctear comharthaí comhuaineacha. Tar éis balbhaithe, féadfaidh an ton reatha críochnú; "
    L"scipeáiltear na chéad toin eile go dtí an chéad ton sceidealaithe tar éis díbhalbhaithe. Ní "
    L"thacaíonn Féilire neamhspleách le haláram, comhartha ama ná balbhú.\r\n\r\nAr Feidhmchlár, "
    L"tugann Fuaim an chomhartha ama Gineadóir ionsuite (réamhshocrú) agus Bíp an chórais do gach "
    L"giuirléid agus aláram. Taispeánann Airde an chomhartha ama leibhéal an ghineadóra in dB: is "
    L"é 0 dB ar dheis an aimplitiúid síneasóideach is mó gan saobhadh, −∞ dB tost agus −18 dB an "
    L"réamhshocrú. Tosaíonn Tástáil réamhamharc leanúnach agus stopann Stop an tástáil é. Is "
    L"féidir an dá chineál fuaime a thástáil; ní shábháiltear an tástáil. Seinneann coinneáil an "
    L"tsleamhnáin fuaim go dtí go scaoiltear an luch, mura bhfuil tástáil an chnaipe ar siúl. "
    L"Tosaíonn sí ar an gcéad soicind iomlán eile: ton gearr gach soicind agus ton fada ag :00, "
    L":05, :10 agus mar sin de. Roinneann comharthaí trialach, giuirléidí agus aláraim ton "
    L"amháin. Ní dhíchumasaítear ach an sleamhnán airde do Bhíp an chórais. Ligtear don ton "
    L"reatha críochnú nuair a stoptar an tástáil; d’fhéadfadh ton fada maireachtáil leathshoicind "
    L"eile. Cuirtear céaduithe fritháirimh san áireamh agus seinntear toin fhorluiteacha go "
    L"leanúnach go deireadh an fhorluí dheireanaigh.",
    L"\r\n\r\nGarsinis laiko signalas\r\nSignalas atitinka Grinvičo laiko signalą (GTS): penki "
    L"trumpi tonai paskutines penkias sekundes ir ilgas tonas tiksliai nustatytu metu. Skirtuke "
    L"Signalas yra Laiko signalas įjungtas ir 1, 5, 10, 15, 20, 30 arba 60 minučių intervalai "
    L"pagal valdiklio laiką. Iš pradžių išjungta, pasirinktas valandos intervalas. Perjungimas "
    L"meniu išlaiko intervalą. Atsižvelgiama į UTC, juostą, poslinkį ir NTP. 20 minučių "
    L"intervalas skamba :00, :20 ir :40. Vienalaikiai valdiklių ir žadintuvų signalai sujungiami. "
    L"Nutildžius dabartinis tonas gali baigtis, kiti praleidžiami, o įjungus garsą girdimas tik "
    L"kitas suplanuotas tonas. Atskiras Kalendorius neturi žadintuvo, laiko signalo ar "
    L"nutildymo.\r\n\r\nSkirtuko Programa Laiko signalo garsas siūlo Įtaisytasis generatorius "
    L"(numatyta) ir Sistemos pyptelėjimas visiems valdikliams ir žadintuvams. Laiko signalo "
    L"garsumas rodo generatoriaus lygį dB: dešinėje 0 dB – didžiausia neiškraipyta sinusoidės "
    L"amplitudė, −∞ dB – tyla, numatyta −18 dB. Tikrinti pradeda nepertraukiamą peržiūrą, "
    L"Stabdyti tikrinimą ją baigia. Tikrinami abu garsai; tikrinimas neįrašomas. Laikant "
    L"slankiklį garsas taip pat leidžiamas iki pelės atleidimo, jei nevyksta mygtuko tikrinimas. "
    L"Pradedama kitą pilną sekundę: trumpas tonas kas sekundę ir ilgas :00, :05, :10 ir toliau. "
    L"Vienalaikiai bandomieji, valdiklių ir žadintuvų signalai naudoja vieną toną. Sustabdymas "
    L"leidžia dabartiniam tonui baigtis; ilgas gali tęstis dar pusę sekundės. Įskaitomos "
    L"poslinkių šimtosios dalys; persidengiantys tonai skamba nenutrūkstamai iki paskutinio "
    L"persidengimo pabaigos.",
    L"\r\n\r\nSkaņas laika signāls\r\nSignāls atbilst Griničas laika signālam (GTS): pieci īsi "
    L"toņi pēdējās piecās sekundēs un garš tonis precīzi noteiktajā brīdī. Cilnē Signāls ir Laika "
    L"signāls ieslēgts un 1, 5, 10, 15, 20, 30 vai 60 minūšu intervāli pēc logrīka laika. Sākumā "
    L"izslēgts, atlasīts stundas intervāls. Pārslēgšana izvēlnē saglabā intervālu. Ņem vērā UTC, "
    L"joslu, nobīdi un NTP; 20 minūšu intervālā skan :00, :20 un :40. Vienlaicīgie logrīku un "
    L"modinātāju signāli apvienojas. Izslēdzot skaņu, pašreizējais tonis var beigties; nākamie "
    L"tiek izlaisti līdz nākamajam plānotajam tonim pēc skaņas ieslēgšanas. Atsevišķam Kalendāram "
    L"nav modinātāja, laika signāla vai skaņas izslēgšanas.\r\n\r\nCilnē Programma Laika signāla "
    L"skaņa piedāvā Iebūvēts ģenerators (noklusējums) un Sistēmas pīkstiens visiem logrīkiem un "
    L"modinātājiem. Laika signāla skaļums rāda ģeneratora līmeni dB: labajā galā 0 dB ir "
    L"maksimālā neizkropļotā sinusoīdas amplitūda, −∞ dB klusums, noklusējums −18 dB. Pārbaudīt "
    L"sāk nepārtrauktu priekšskatījumu, Apturēt pārbaudi to beidz. Pārbaudāmas abas skaņas; "
    L"pārbaude netiek saglabāta. Turot slīdni, skaņa skan līdz peles atlaišanai, ja nenotiek "
    L"pogas pārbaude. Atskaņošana sākas nākamajā veselajā sekundē: īss tonis katru sekundi un "
    L"garš :00, :05, :10 utt. Vienlaicīgie pārbaudes, logrīku un modinātāju signāli izmanto vienu "
    L"toni. Apturot pašreizējais tonis drīkst beigties; garais var turpināties vēl pussekundi. "
    L"Ņem vērā nobīdes simtdaļas; pārklājušies toņi skan nepārtraukti līdz pēdējā pārklājuma "
    L"beigām.",
    L"\r\n\r\nHallható időjelzés\r\nA jelzés a Greenwich Time Signal (GTS) mintáját követi: öt "
    L"rövid hang az utolsó öt másodpercben, majd hosszú hang a pontos időhatáron. Az Időjelzés "
    L"fülön az Időjelzés engedélyezve és 1, 5, 10, 15, 20, 30 vagy 60 perces intervallum "
    L"választható a minialkalmazás ideje szerint. Kezdetben kikapcsolt, órás intervallummal. A "
    L"menübeli kapcsolás megőrzi az intervallumot. Figyelembe veszi az UTC-t, időzónát, eltolást "
    L"és NTP-t; 20 percnél :00, :20 és :40 időpontban szól. Az egyidejű óra- és ébresztési "
    L"jelzések egyesülnek. Némítás után az aktuális hang befejeződhet; a következők kimaradnak, "
    L"és feloldáskor csak a következő ütemezett hang szól. Az önálló Naptárnak nincs ébresztése, "
    L"időjelzése vagy némítása.\r\n\r\nAz Alkalmazás fül Időjelzés hangja beállítása Beépített "
    L"generátor (alapértelmezett) vagy Rendszerhang lehet minden órához és ébresztéshez. Az "
    L"Időjelzés hangereje dB-ben mutatja a generátor szintjét: a jobb szélső 0 dB a legnagyobb "
    L"torzítatlan szinuszamplitúdó, −∞ dB a csend, −18 dB az alapérték. A Tesztelés folyamatos "
    L"próbát indít, a Teszt leállítása befejezi. Mindkét hang tesztelhető; a teszt nem mentődik. "
    L"A csúszka nyomva tartása is szól az egér felengedéséig, ha nincs gombbal indított teszt. A "
    L"lejátszás a következő egész másodpercnél indul: rövid hang másodpercenként és hosszú :00, "
    L":05, :10 stb. időpontban. Az egyidejű teszt-, óra- és ébresztési hangok egyetlen hangot "
    L"használnak. A rendszerhangnál csak a hangerőcsúszka tiltott. Leállításkor az aktuális hang "
    L"befejeződik; a hosszú még fél másodpercig tarthat. A századmásodperces eltolás is számít; "
    L"az átfedő hangok az utolsó átfedés végéig megszakítás nélkül szólnak.",
    L"\r\n\r\nSinjal tal-ħin li jinstema’\r\nIs-sinjal isegwi s-Sinjal tal-Ħin ta’ Greenwich "
    L"(GTS): ħames toni qosra fl-aħħar ħames sekondi u ton twil eżatt fil-ħin stabbilit. It-tab "
    L"Sinjal għandu Sinjal tal-ħin attivat u intervalli ta’ 1, 5, 10, 15, 20, 30 jew 60 minuta "
    L"skont il-ħin tal-widget. Għall-ewwel huwa mitfi b’intervall ta’ siegħa magħżul. Il-bidla "
    L"fil-menu żżomm l-intervall. Jitqiesu UTC, iż-żona, il-kumpens u NTP; b’20 minuta jindaqq "
    L"f’:00, :20 u :40. Sinjali simultanji ta’ widgets u allarmi jingħaqdu. Wara s-sikket, it-ton "
    L"kurrenti jista’ jispiċċa, dawk li jmiss jinqabżu u wara li jerġa’ jinxtegħel il-ħoss "
    L"jinstema’ biss it-ton skedat li jmiss. Kalendarju separat m’għandux allarm, sinjal tal-ħin "
    L"jew sikket.\r\n\r\nĦoss tas-sinjal tal-ħin fit-tab Applikazzjoni joffri Ġeneratur integrat "
    L"(default) u Ħoss tas-sistema għall-widgets u l-allarmi kollha. Volum tas-sinjal tal-ħin "
    L"juri l-livell tal-ġeneratur f’dB: 0 dB fuq il-lemin huwa l-massimu ta’ amplitudni "
    L"sinusojdali mingħajr distorsjoni, −∞ dB huwa skiet, u d-default −18 dB. Ittestja jibda "
    L"previżjoni kontinwa, Waqqaf it-test itemmha. Iż-żewġ ħsejjes jistgħu jiġu ttestjati; "
    L"it-test ma jiġix issejvjat. Iż-żamma tas-slajder iddoqq ukoll sal-ħelsien tal-maws, sakemm "
    L"mhux għaddej test mill-buttuna. Id-daqq jibda fis-sekonda sħiħa li jmiss: ton qasir kull "
    L"sekonda u twil f’:00, :05, :10 u hekk ikompli. Sinjali simultanji ta’ prova, widgets u "
    L"allarmi jaqsmu ton wieħed. Il-waqfien iħalli t-ton kurrenti jispiċċa; wieħed twil jista’ "
    L"jdum nofs sekonda oħra. Jitqiesu ċ-ċentesimi tal-kumpens; toni li jikkoinċidu jindaqqu "
    L"kontinwament sa tmiem l-aħħar sovrapożizzjoni.",
    L"\r\n\r\nHoorbaar tijdsignaal\r\nHet signaal volgt Greenwich Time Signal (GTS): vijf korte "
    L"tonen tijdens de laatste vijf seconden en een lange toon precies op de tijdgrens. Signaal "
    L"biedt Tijdsignaal ingeschakeld en intervallen van 1, 5, 10, 15, 20, 30 of 60 minuten "
    L"volgens de widgettijd. Aanvankelijk staat het uit met een uurinterval geselecteerd. "
    L"Schakelen via het menu behoudt het interval. UTC, tijdzone, verschuiving en NTP tellen mee; "
    L"bij 20 minuten klinkt het op :00, :20 en :40. Gelijktijdige widget- en alarmsignalen worden "
    L"samengevoegd. Na dempen mag de huidige toon eindigen; volgende tonen worden overgeslagen "
    L"tot de eerstvolgende geplande toon na opheffen. Een losse Kalender heeft geen alarm, "
    L"tijdsignaal of demping.\r\n\r\nGeluid tijdsignaal op Toepassing biedt Ingebouwde generator "
    L"(standaard) en Systeempiep voor alle widgets en alarmen. Volume tijdsignaal toont het "
    L"generatorniveau in dB: rechts is 0 dB de maximale onvervormde sinusamplitude, −∞ dB is "
    L"stilte en −18 dB de standaard. Testen start een voortdurend voorbeeld, Test stoppen "
    L"beëindigt dit. Beide geluiden zijn te testen; de test wordt niet opgeslagen. De "
    L"schuifregelaar vasthouden geeft ook een voorbeeld tot de muis wordt losgelaten, tenzij de "
    L"knoptest loopt. Het afspelen begint op de volgende hele seconde: een korte toon elke "
    L"seconde en een lange op :00, :05, :10 enzovoort. Gelijktijdige test-, widget- en "
    L"alarmsignalen delen één toon. Stoppen laat de huidige toon eindigen; een lange kan nog een "
    L"halve seconde duren. Honderdsten in de verschuiving tellen mee; overlappende tonen klinken "
    L"onafgebroken tot de laatste overlap eindigt.",
    L"\r\n\r\nSemnal orar sonor\r\nSemnalul urmează Greenwich Time Signal (GTS): cinci tonuri "
    L"scurte în ultimele cinci secunde și un ton lung exact la momentul stabilit. Semnal oferă "
    L"Semnal orar activat și intervale de 1, 5, 10, 15, 20, 30 sau 60 de minute după ora "
    L"widgetului. Inițial este dezactivat, cu interval orar selectat. Comutarea din meniu "
    L"păstrează intervalul. Sunt respectate UTC, fusul, decalajul și NTP; la 20 de minute sună la "
    L":00, :20 și :40. Semnalele simultane ale widgeturilor și alarmelor se îmbină. După "
    L"dezactivarea sunetului, tonul curent se poate încheia; următoarele sunt omise până la "
    L"următorul ton programat după reactivare. Un Calendar separat nu are alarmă, semnal orar sau "
    L"dezactivare de sunet.\r\n\r\nSunet semnal orar din Aplicație oferă Generator încorporat "
    L"(implicit) și Bip de sistem pentru toate widgeturile și alarmele. Volum semnal orar arată "
    L"nivelul generatorului în dB: 0 dB la dreapta este amplitudinea sinusoidală maximă "
    L"nedistorsionată, −∞ dB liniște, iar −18 dB valoarea implicită. Testare începe o "
    L"previzualizare continuă, Oprire test o încheie. Se pot testa ambele sunete; testul nu se "
    L"salvează. Menținerea glisorului redă și ea sunet până la eliberarea mouse-ului, dacă nu "
    L"rulează testul din buton. Redarea începe la următoarea secundă întreagă: ton scurt în "
    L"fiecare secundă și lung la :00, :05, :10 etc. Semnalele simultane de test, widget și alarmă "
    L"folosesc un singur ton. Oprirea lasă tonul curent să se încheie; unul lung poate dura încă "
    L"o jumătate de secundă. Sunt luate în calcul sutimile decalajului; tonurile suprapuse sună "
    L"continuu până la sfârșitul ultimei suprapuneri.",
    L"\r\n\r\nΗχητικό σήμα ώρας\r\nΤο σήμα ακολουθεί το Greenwich Time Signal (GTS): πέντε "
    L"σύντομοι τόνοι στα τελευταία πέντε δευτερόλεπτα και παρατεταμένος τόνος στην ακριβή χρονική "
    L"στιγμή. Η καρτέλα Σήμα έχει Σήμα ώρας ενεργό και διαστήματα 1, 5, 10, 15, 20, 30 ή 60 "
    L"λεπτών κατά την ώρα του στοιχείου. Αρχικά είναι ανενεργό με επιλεγμένο ωριαίο διάστημα. Το "
    L"μενού διατηρεί το διάστημα. Λαμβάνονται υπόψη UTC, ζώνη, μετατόπιση και NTP· στα 20 λεπτά "
    L"ακούγεται στις :00, :20 και :40. Ταυτόχρονα σήματα στοιχείων και ξυπνητηριών ενώνονται. "
    L"Μετά τη σίγαση ο τρέχων τόνος μπορεί να ολοκληρωθεί· οι επόμενοι παραλείπονται μέχρι τον "
    L"επόμενο προγραμματισμένο τόνο μετά την άρση της. Ανεξάρτητο Ημερολόγιο δεν έχει ξυπνητήρι, "
    L"σήμα ή σίγαση· τα αντίστοιχα χειριστήρια είναι ανενεργά και λείπουν από το μενού.\r\n\r\nΟ "
    L"Ήχος σήματος ώρας στην Εφαρμογή προσφέρει Ενσωματωμένη γεννήτρια (προεπιλογή) και Ήχος "
    L"συστήματος για όλα τα στοιχεία και ξυπνητήρια. Η Ένταση σήματος ώρας δείχνει επίπεδο "
    L"γεννήτριας σε dB: δεξιά 0 dB είναι η μέγιστη ημιτονοειδής ένταση χωρίς παραμόρφωση, −∞ dB "
    L"σιωπή και −18 dB η προεπιλογή. Η Δοκιμή αρχίζει συνεχή προεπισκόπηση, η Διακοπή δοκιμής τη "
    L"σταματά. Δοκιμάζονται και οι δύο ήχοι· η δοκιμή δεν αποθηκεύεται. Κρατώντας το ρυθμιστικό "
    L"ακούγεται επίσης προεπισκόπηση μέχρι την απελευθέρωση του ποντικιού, εκτός αν εκτελείται "
    L"δοκιμή κουμπιού. Αρχίζει στο επόμενο ακέραιο δευτερόλεπτο: σύντομος τόνος κάθε δευτερόλεπτο "
    L"και μακρύς στις :00, :05, :10 κ.ο.κ. Ταυτόχρονα δοκιμαστικά σήματα, στοιχεία και ξυπνητήρια "
    L"μοιράζονται έναν τόνο. Η διακοπή αφήνει τον τρέχοντα τόνο να τελειώσει· ο μακρύς μπορεί να "
    L"διαρκέσει άλλο μισό δευτερόλεπτο. Υπολογίζονται και εκατοστά μετατόπισης· επικαλυπτόμενοι "
    L"τόνοι ακούγονται συνεχώς μέχρι το τέλος της τελευταίας επικάλυψης.",
    L"\r\n\r\nZvučni vremenski signal\r\nSignal slijedi obrazac Greenwich Time Signal (GTS). "
    L"Kartica Signal sadrži opciju Vremenski signal uključen i odabir intervala od 1, 5, 10, 15, "
    L"20, 30 ili 60 minuta prema prikazanom vremenu vidžeta. Signal je u početku isključen, a "
    L"odabran je interval od jednog sata. Isključivanje i uključivanje u meniju čuva interval. "
    L"Meni prikazuje vrijeme alarma i interval signala u zagradama. Granica prati vrijeme "
    L"vidžeta, uključujući UTC, vremensku zonu, pomak i NTP sinhronizaciju. Pet kratkih tonova "
    L"označava posljednjih pet sekundi, a dugi ton tačnu granicu. Istovremeni signali više "
    L"vidžeta spajaju se u jedan niz. Nakon isključivanja zvuka trenutni ton može završiti; "
    L"sljedeći se preskaču, a nakon uključivanja zvuka čuje se tek sljedeći planirani ton. "
    L"Samostalni Kalendar nema alarm, vremenski signal ni isključivanje zvuka.\r\n\r\nPri "
    L"intervalu od 20 minuta signal se čuje na :00, :20 i :40 prema vremenu vidžeta.\r\n\r\nNa "
    L"kartici Program opcija Zvuk vremenskog signala nudi Ugrađeni generator i Zvuk sistema. "
    L"Izbor vrijedi za sve vidžete, uključujući signale alarma. Podrazumijevani je Ugrađeni "
    L"generator.\r\n\r\nKlizač Glasnoća vremenskog signala na kartici Program prikazuje razinu "
    L"generatora u dB. Krajnji desni položaj je 0 dB, najveća neizobličena amplituda sinusoide; "
    L"tišina je −∞ dB. Podrazumijevana je glasnoća −18 dB. Testiraj uz izbor zvuka pokreće "
    L"neprekidni pregled, a Zaustavi test ga završava. Oba se zvuka mogu testirati; test se ne "
    L"čuva. Držanje klizača glasnoće također pokreće pregled do otpuštanja miša, osim ako traje "
    L"test pokrenut dugmetom. Reprodukcija počinje na sljedećoj punoj sekundi: kratki ton svake "
    L"sekunde i dugi na :00, :05, :10 i tako dalje. Istovremeni probni signali i signali vidžeta "
    L"ili alarma dijele jedan ton. Zaustavljanje testa dopušta završetak trenutnog tona; dugi ton "
    L"može trajati još do pola sekunde. Pomaci vidžeta poštuju se i u stotinkama sekunde. Tonovi "
    L"vidžeta, alarma i testova koji se preklapaju zvuče kao jedan neprekidan ton do kraja "
    L"posljednjeg preklapanja.",
    L"\r\n\r\nZvučni vremenski signal\r\nSignal slijedi obrazac Greenwich Time Signal (GTS). "
    L"Kartica Signal sadrži opciju Vremenski signal uključen i odabir intervala od 1, 5, 10, 15, "
    L"20, 30 ili 60 minuta prema prikazanom vremenu widgeta. Signal je u početku isključen, a "
    L"odabran je interval od jednog sata. Isključivanje i uključivanje u izborniku čuva interval. "
    L"Izbornik prikazuje vrijeme alarma i interval signala u zagradama. Granica prati vrijeme "
    L"widgeta, uključujući UTC, vremensku zonu, pomak i NTP sinkronizaciju. Pet kratkih tonova "
    L"označava posljednjih pet sekundi, a dugi ton točnu granicu. Istodobni signali više widgeta "
    L"spajaju se u jedan niz. Nakon isključivanja zvuka trenutačni ton može završiti; sljedeći se "
    L"preskaču, a nakon uključivanja zvuka čuje se tek sljedeći planirani ton. Samostalni "
    L"Kalendar nema alarm, vremenski signal ni isključivanje zvuka.\r\n\r\nPri intervalu od 20 "
    L"minuta signal se čuje na :00, :20 i :40 prema vremenu widgeta.\r\n\r\nNa kartici Program "
    L"opcija Zvuk vremenskog signala nudi Ugrađeni generator i Zvuk sustava. Izbor vrijedi za sve "
    L"widgete, uključujući signale alarma. Zadani je Ugrađeni generator.\r\n\r\nKlizač Glasnoća "
    L"vremenskog signala na kartici Program prikazuje razinu generatora u dB. Krajnji desni "
    L"položaj je 0 dB, najveća neizobličena amplituda sinusoide; tišina je −∞ dB. Zadana je "
    L"glasnoća −18 dB. Testiraj uz izbor zvuka pokreće neprekidni pretpregled, a Zaustavi test ga "
    L"završava. Oba se zvuka mogu testirati; test se ne sprema. Držanje klizača glasnoće također "
    L"pokreće pretpregled do otpuštanja miša, osim ako traje test pokrenut gumbom. Reprodukcija "
    L"počinje na sljedećoj punoj sekundi: kratki ton svake sekunde i dugi na :00, :05, :10 i tako "
    L"dalje. Istodobni probni signali i signali widgeta ili alarma dijele jedan ton. "
    L"Zaustavljanje testa dopušta završetak trenutačnog tona; dugi ton može trajati još do pola "
    L"sekunde. Pomaci widgeta poštuju se i u stotinkama sekunde. Tonovi widgeta, alarma i testova "
    L"koji se preklapaju zvuče kao jedan neprekidan ton do kraja posljednjeg preklapanja.",
    L"\r\n\r\nZvočni časovni signal\r\nSignal sledi vzorcu Greenwich Time Signal (GTS). Zavihek "
    L"Signal ponuja Časovni signal vključen in intervale 1, 5, 10, 15, 20, 30 ali 60 minut po "
    L"prikazanem času gradnika. Signal je sprva izključen, izbran pa je enourni interval. Preklop "
    L"v meniju ohrani interval; čas budilke in interval sta prikazana v oklepajih. Časovna meja "
    L"upošteva UTC, časovni pas, odmik in NTP. V zadnjih petih sekundah se oglasi pet kratkih "
    L"piskov, natanko na meji pa dolg. Sočasni signali se združijo v eno zaporedje. Ob izklopu "
    L"zvoka se trenutni pisk lahko konča, nadaljnji se izpustijo, po vklopu pa se zasliši šele "
    L"naslednji načrtovani pisk. Samostojni Koledar nima budilke, časovnega signala ali "
    L"utišanja.\r\n\r\nPri intervalu 20 minut se signal oglasi ob :00, :20 in :40 po času "
    L"gradnika. Na zavihku Program Zvok časovnega signala ponuja Vgrajeni generator (privzeto) in "
    L"Sistemski pisk. Izbira velja za vse gradnike, tudi za signale budilk.\r\n\r\nGlasnost "
    L"časovnega signala kaže raven generatorja v dB. Desni konec je 0 dB, največja nepopačena "
    L"amplituda sinusoide; tišina je −∞ dB. Privzeto je −18 dB. Preizkusi ob izbiri zvoka začne "
    L"neprekinjeni predogled, Ustavi preizkus pa ga konča. Preizkusiti je mogoče obe možnosti; "
    L"preizkus se ne shrani. Držanje drsnika prav tako predvaja predogled do izpusta miške, razen "
    L"če teče preizkus z gumbom. Predvajanje se začne ob naslednji polni sekundi: kratko vsako "
    L"sekundo in dolgo ob :00, :05, :10 in tako naprej. Sočasni poskusni, gradniški in budilkini "
    L"signali imajo skupen ton. Ob ustavitvi se trenutni pisk konča; dolg lahko traja še pol "
    L"sekunde. Upoštevane so tudi stotinke odmikov. Prekrivajoči se toni trajajo neprekinjeno do "
    L"konca zadnjega prekrivanja.",
    L"\r\n\r\nZvučni vremenski signal\r\nSignal prati obrazac Greenwich Time Signal (GTS). "
    L"Kartica Signal ima Vremenski signal uključen i intervale 1, 5, 10, 15, 20, 30 ili 60 minuta "
    L"prema vremenu vidžeta. Signal je prvobitno isključen, a izabran je jednočasovni interval. "
    L"Prebacivanje u meniju čuva interval; vrijeme alarma i interval prikazani su u zagradama. "
    L"Granica prati UTC, vremensku zonu, pomak i NTP. Pet kratkih tonova obilježava posljednjih "
    L"pet sekundi, dugi tačnu granicu. Istovremeni signali spajaju se u jednu sekvencu. Poslije "
    L"isključivanja zvuka trenutni ton može da završi; sljedeći se preskaču, a nakon uključivanja "
    L"čuje se tek sljedeći planirani ton. Samostalni Kalendar nema alarm, vremenski signal ni "
    L"isključivanje zvuka.\r\n\r\nPri intervalu 20 minuta signal se čuje na :00, :20 i :40 po "
    L"vremenu vidžeta. Na kartici Program Zvuk vremenskog signala nudi Ugrađeni generator "
    L"(podrazumijevano) i Sistemski zvučni signal. Izbor važi za sve vidžete, uključujući signale "
    L"alarma.\r\n\r\nJačina vremenskog signala pokazuje nivo generatora u dB. Desni kraj je 0 dB, "
    L"najveća neizobličena amplituda sinusoide; tišina je −∞ dB. Podrazumijevano je −18 dB. "
    L"Testiraj pored izbora zvuka pokreće neprekidan probni zvuk, Zaustavi test ga završava. Obje "
    L"vrste zvuka mogu se testirati; test se ne čuva. Držanje klizača takođe pušta probni zvuk do "
    L"otpuštanja miša, osim ako traje test dugmetom. Reprodukcija počinje na sljedećoj cijeloj "
    L"sekundi: kratak ton svake sekunde i dugi na :00, :05, :10 i tako dalje. Istovremeni probni "
    L"signali i signali vidžeta ili alarma dijele jedan ton. Zaustavljanje dopušta da trenutni "
    L"ton završi; dugi može trajati još pola sekunde. Uračunavaju se i stotinke pomaka. Tonovi "
    L"koji se preklapaju zvuče neprekidno do kraja posljednjeg preklapanja.",
    L"\r\n\r\nГукавы сігнал дакладнага часу\r\nСігнал адпавядае грынвіцкаму сігналу часу (GTS). "
    L"Укладка «Сігнал» мае «Сігнал часу ўключаны» і інтэрвалы 1, 5, 10, 15, 20, 30 або 60 хвілін "
    L"паводле часу віджэта. Спачатку сігнал выключаны, а інтэрвал — адна гадзіна. Пераключэнне ў "
    L"меню захоўвае інтэрвал. Час будзільніка і інтэрвал паказваюцца ў дужках. Часавая мяжа "
    L"ўлічвае UTC, пояс, зрушэнне і NTP. Пяць кароткіх тонаў гучаць у апошнія пяць секунд, доўгі "
    L"— дакладна на мяжы. Адначасовыя сігналы аб’ядноўваюцца ў адну паслядоўнасць. Пасля "
    L"выключэння гуку бягучы тон можа скончыцца; наступныя прапускаюцца, а пасля ўключэння гучыць "
    L"толькі наступны запланаваны тон. Асобны каляндар не мае будзільніка, сігналу часу і "
    L"выключэння гуку.\r\n\r\nПры інтэрвале 20 хвілін сігналы гучаць на :00, :20 і :40 паводле "
    L"часу віджэта. На ўкладцы «Праграма» «Гук сігналу часу» прапануе «Убудаваны генератар» "
    L"(прадвызначаны) і «Сістэмны сігнал». Выбар дзейнічае для ўсіх віджэтаў, у тым ліку сігналаў "
    L"будзільніка.\r\n\r\n«Гучнасць сігналу часу» паказвае ўзровень генератара ў дБ. Край справа "
    L"— 0 дБ, найбольшая амплітуда сінусоіды без скажэнняў; цішыня — −∞ дБ. Прадвызначаная "
    L"гучнасць — −18 дБ. «Праверыць» побач з выбарам гуку запускае бесперапынны прагляд, а "
    L"«Спыніць тэст» заканчвае яго. Абодва гукі можна праверыць; тэст не захоўваецца. "
    L"Утрымліванне паўзунка таксама прайграе гук да адпускання мышы, калі не ідзе тэст кнопкай. "
    L"Прайграванне пачынаецца з наступнай поўнай секунды: кароткі тон кожную секунду і доўгі на "
    L":00, :05, :10 і далей. Адначасовыя пробныя сігналы і сігналы віджэтаў ці будзільнікаў маюць "
    L"адзін тон. Пры спыненні бягучы тон дагучвае; доўгі можа гучаць яшчэ да паловы секунды. "
    L"Улічваюцца і сотыя долі зрушэнняў. Тоны, якія перакрываюцца, гучаць непарыўна да канца "
    L"апошняга перакрыцця.",
    L"\r\n\r\nЗвуков сигнал за точно време\r\nСигналът следва гринуичкия сигнал за време (GTS). "
    L"Разделът „Сигнал“ има „Сигналът за време е включен“ и интервали 1, 5, 10, 15, 20, 30 или 60 "
    L"минути според показваното време. Първоначално сигналът е изключен и е избран едночасов "
    L"интервал. Превключването в менюто запазва интервала; часът на алармата и интервалът се "
    L"показват в скоби. Времевата граница отчита UTC, зоната, отместването и NTP. Пет кратки тона "
    L"звучат в последните пет секунди, дълъг — точно на границата. Едновременните сигнали се "
    L"обединяват в една поредица. След изключване на звука текущият тон може да завърши, "
    L"следващите се пропускат, а след включване се чува следващият планиран тон. Самостоятелният "
    L"календар няма аларма, сигнал за време или изключване на звука.\r\n\r\nПри интервал 20 "
    L"минути сигналите звучат на :00, :20 и :40 според времето на модула. В раздела „Програма“ "
    L"„Звук на сигнала за време“ предлага „Вграден генератор“ (по подразбиране) и „Системен "
    L"сигнал“. Изборът важи за всички модули, включително сигналите на алармите.\r\n\r\n„Сила на "
    L"сигнала за време“ показва нивото на генератора в dB. Крайното дясно положение е 0 dB, "
    L"максимална синусоидална амплитуда без изкривяване; тишината е −∞ dB. По подразбиране е −18 "
    L"dB. „Тествай“ до избора на звук стартира непрекъснато прослушване, а „Спри теста“ го "
    L"прекратява. И двата звука могат да се тестват; тестът не се записва. Задържането на "
    L"плъзгача също пуска прослушване до отпускане на мишката, освен ако тече тест от бутона. "
    L"Възпроизвеждането започва от следващата цяла секунда: кратък тон всяка секунда и дълъг на "
    L":00, :05, :10 и нататък. Едновременните пробни сигнали и сигналите на модулите или алармите "
    L"споделят един тон. При спиране текущият тон завършва; дългият може да продължи още половин "
    L"секунда. Отместванията се отчитат и в стотни от секундата. Застъпващите се тонове звучат "
    L"непрекъснато до края на последното застъпване.",
    L"\r\n\r\nЗвучен временски сигнал\r\nСигналот го следи гриничкиот временски сигнал (GTS). "
    L"Картичката „Сигнал“ има „Временскиот сигнал е вклучен“ и интервали 1, 5, 10, 15, 20, 30 или "
    L"60 минути според времето на виџетот. Сигналот почнува исклучен со избран едночасовен "
    L"интервал. Менувањето во менито го зачувува интервалот; времето на алармот и интервалот се "
    L"прикажуваат во загради. Временската граница ги зема предвид UTC, зоната, поместувањето и "
    L"NTP. Пет кратки тона ги означуваат последните пет секунди, а долг тон точната граница. "
    L"Истовремените сигнали се спојуваат во една низа. По исклучување на звукот тековниот тон "
    L"може да заврши; следните се прескокнуваат, а по вклучување се слуша следниот планиран тон. "
    L"Самостојниот календар нема аларм, временски сигнал или исклучување звук.\r\n\r\nПри "
    L"интервал 20 минути сигналите се слушаат на :00, :20 и :40 според времето на виџетот. Во "
    L"„Програма“, „Звук на временскиот сигнал“ нуди „Вграден генератор“ (стандардно) и „Системски "
    L"сигнал“. Изборот важи за сите виџети, вклучувајќи ги сигналите на "
    L"алармите.\r\n\r\n„Гласност на временскиот сигнал“ го покажува нивото на генераторот во dB. "
    L"Десниот крај е 0 dB, најголемата неизобличена синусоидална амплитуда; тишината е −∞ dB. "
    L"Стандардно е −18 dB. „Тестирај“ до изборот на звук почнува непрекинато пробно слушање, а "
    L"„Запри го тестот“ го завршува. Може да се тестираат двата звука; тестот не се зачувува. "
    L"Држењето на лизгачот пушта пробен звук до отпуштање на глувчето, освен ако тече тест од "
    L"копчето. Пуштањето почнува на следната цела секунда: краток тон секоја секунда и долг на "
    L":00, :05, :10 и понатаму. Истовремените пробни сигнали и сигналите на виџетите или алармите "
    L"делат еден тон. Запирањето го остава тековниот тон да заврши; долгиот може да трае уште "
    L"половина секунда. Се земаат предвид и стотинките на поместувањата. Преклопените тонови "
    L"звучат непрекинато до крајот на последното преклопување.",
    L"\r\n\r\nЗвучни временски сигнал\r\nСигнал прати образац Greenwich Time Signal (GTS). "
    L"Картица Сигнал има Временски сигнал укључен и интервале 1, 5, 10, 15, 20, 30 или 60 минута "
    L"према времену виџета. Сигнал је првобитно искључен, а изабран је једночасовни интервал. "
    L"Пребацивање у менију чува интервал; време аларма и интервал приказани су у заградама. "
    L"Граница прати UTC, временску зону, помак и NTP. Пет кратких тонова обележава последњих пет "
    L"секунди, дуги тачну границу. Истовремени сигнали спајају се у једну секвенцу. После "
    L"искључивања звука тренутни тон може да заврши; следећи се прескачу, а након укључивања чује "
    L"се тек следећи планирани тон. Самостални Календар нема аларм, временски сигнал ни "
    L"искључивање звука.\r\n\r\nПри интервалу 20 минута сигнал се чује на :00, :20 и :40 по "
    L"времену виџета. На картици Програм Звук временског сигнала нуди Уграђени генератор "
    L"(подразумевано) и Системски звучни сигнал. Избор важи за све виџете, укључујући сигнале "
    L"аларма.\r\n\r\nЈачина временског сигнала показује ниво генератора у dB. Десни крај је 0 dB, "
    L"највећа неизобличена амплитуда синусоиде; тишина је −∞ dB. Подразумевано је −18 dB. "
    L"Тестирај поред избора звука покреће непрекидан пробни звук, Заустави тест га завршава. Обе "
    L"врсте звука могу се тестирати; тест се не чува. Држање клизача такође пушта пробни звук до "
    L"отпуштања миша, осим ако траје тест дугметом. Репродукција почиње на следећој целој "
    L"секунди: кратак тон сваке секунде и дуги на :00, :05, :10 и тако даље. Истовремени пробни "
    L"сигнали и сигнали виџета или аларма деле један тон. Заустављање допушта да тренутни тон "
    L"заврши; дуги може трајати још пола секунде. Урачунавају се и стотинке помака. Тонови који "
    L"се преклапају звуче непрекидно до краја последњег преклапања.",
    L"\r\n\r\nЗВУКОВИЙ СИГНАЛ ТОЧНОГО ЧАСУ\r\nСигнал відповідає схемі гринвіцького сигналу часу "
    L"(GTS). На вкладці «Сигнал» є прапорець «Сигнал часу увімкнено» та перемикачі інтервалів 1, "
    L"5, 10, 15, 20, 30 і 60 хвилин за часом віджета. Спочатку сигнал вимкнено, а інтервал "
    L"установлено на одну годину. Перемикання сигналу в меню віджета зберігає вибраний інтервал. "
    L"Час будильника й інтервал сигналу показуються в меню в дужках. Часова межа визначається "
    L"часом віджета з урахуванням UTC, часового поясу, зсуву та синхронізації NTP. Протягом "
    L"останніх п’яти секунд звучать п’ять коротких сигналів, а точно на межі — довгий. Якщо "
    L"кілька віджетів подають сигнал одночасно, відтворюється одна спільна послідовність. Після "
    L"вимкнення звуку поточний сигнал може завершитися; наступні пропускаються, а після "
    L"ввімкнення звуку відтворюється лише наступний запланований сигнал. Окремий календар не "
    L"підтримує будильники, сигнали часу та вимкнення звуку.\r\n\r\nЗа інтервалу 20 хвилин "
    L"сигнали звучать на :00, :20 і :40 за часом віджета.\r\n\r\nНа вкладці «Програма» параметр "
    L"«Звук сигналу часу» дає змогу вибрати «Вбудований генератор» або «Системний сигнал». Вибір "
    L"діє для всіх віджетів, зокрема сигналів будильника. Типово використовується вбудований "
    L"генератор.\r\n\r\nПовзунок «Гучність сигналу часу» на вкладці «Програма» показує рівень "
    L"вбудованого генератора в дБ. Крайнє праве положення — 0 дБ, найбільша амплітуда синусоїди "
    L"без спотворень; тиша — −∞ дБ. Типова гучність — −18 дБ. Кнопка «Перевірити» поряд із "
    L"параметром звуку запускає безперервне прослуховування, а «Зупинити перевірку» завершує "
    L"його. Можна перевірити обидва варіанти звуку; перевірка не зберігається. Утримування "
    L"повзунка гучності також вмикає прослуховування до відпускання кнопки миші, якщо перевірку "
    L"кнопкою не запущено. Відтворення починається з наступної цілої секунди: короткий сигнал "
    L"щосекунди та довгий на :00, :05, :10 тощо. Одночасні сигнали прослуховування, віджетів і "
    L"будильників об’єднуються. Зупинення перевірки дає поточному сигналу завершитися; довгий "
    L"сигнал може тривати ще до половини секунди. Зсуви віджетів враховуються й у сотих частках "
    L"секунди. Сигнали, що перекриваються, звучать як один безперервний звук до завершення "
    L"останнього перекриття.",
    L"\r\n\r\nЗВУКОВОЙ СИГНАЛ ТОЧНОГО ВРЕМЕНИ\r\nСигнал соответствует схеме гринвичского сигнала "
    L"времени (GTS). На вкладке «Сигнал» есть флажок «Сигнал времени включён» и переключатели "
    L"интервалов 1, 5, 10, 15, 20, 30 и 60 минут по времени виджета. Изначально сигнал отключён, а "
    L"интервал установлен на один час. Переключение сигнала в меню виджета сохраняет выбранный "
    L"интервал. Время будильника и интервал сигнала показываются в меню в скобках. Временная "
    L"граница определяется временем виджета с учётом UTC, часового пояса, смещения и синхронизации "
    L"NTP. В течение последних пяти секунд звучат пять коротких сигналов, а точно на границе — "
    L"длинный. Если несколько виджетов подают сигнал одновременно, воспроизводится одна общая "
    L"последовательность. После отключения звука текущий сигнал может завершиться; следующие "
    L"пропускаются, а после включения звука воспроизводится только следующий запланированный "
    L"сигнал. Отдельный календарь не поддерживает будильники, сигналы времени и отключение "
    L"звука.\r\n\r\nПри интервале 20 минут сигналы звучат на :00, :20 и :40 по времени "
    L"виджета.\r\n\r\nНа вкладке «Программа» параметр «Звук сигнала времени» позволяет выбрать "
    L"«Встроенный генератор» или «Системный сигнал». Выбор действует для всех виджетов, включая "
    L"сигналы будильника. По умолчанию используется встроенный генератор.\r\n\r\nПолзунок "
    L"«Громкость сигнала времени» на вкладке «Программа» показывает уровень встроенного генератора "
    L"в дБ. Крайнее правое положение — 0 дБ, наибольшая амплитуда синусоиды без искажений; тишина "
    L"— −∞ дБ. Громкость по умолчанию — −18 дБ. Кнопка «Проверить» рядом с параметром звука "
    L"запускает непрерывное прослушивание, а «Остановить тест» завершает его. Можно проверить оба "
    L"варианта звука; проверка не сохраняется. Удерживание ползунка громкости также включает "
    L"прослушивание до отпускания кнопки мыши, если проверка кнопкой не запущена. Воспроизведение "
    L"начинается со следующей целой секунды: короткий сигнал каждую секунду и длинный на :00, :05, "
    L":10 и так далее. Одновременные сигналы прослушивания, виджетов и будильников объединяются. "
    L"Остановка проверки позволяет текущему сигналу завершиться; длинный сигнал может продолжаться "
    L"ещё до половины секунды. Смещения виджетов учитываются и в сотых долях секунды. "
    L"Перекрывающиеся сигналы звучат как один непрерывный звук до завершения последнего перекрытия."
};

const wchar_t* HELP_ADDITIONAL_CLOCK_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nDalší hodiny: Ve widgetu Kalendář s hodinami lze na kartě Obecné zapnout až dvoje "
    L"další hodiny a zadat jejich názvy a časová pásma. U každých hodin se pak zobrazí i "
    L"příslušný den týdne. Velikost každého ciferníku se volí samostatně na kartě Vzhled nebo v "
    L"jeho nabídce pravého tlačítka. Další hodiny nemají sekundovou ručičku. Při přidávání, "
    L"odebírání a změně velikosti zůstane widget přichycený ke stejným hranám pracovní "
    L"plochy.\r\n\r\nDvojklik přepíná sekundovou ručičku pouze přímo na hlavním ciferníku. "
    L"Nabídky dalších ciferníků obsahují pouze velikosti. Další hodiny sdílejí jazyk, formát "
    L"času, písma a offset widgetu; jejich digitální čas se zobrazuje bez sekund.",
    L"\r\n\r\nAdditional clocks: On the General tab, a Calendar with clock widget can show up to "
    L"two additional clocks with their own names and time zones. Each clock then also shows its "
    L"local day of the week. Choose each clock face size separately on the Appearance tab or from "
    L"its right-click menu. Additional clocks have no second hand. Adding, removing, or resizing "
    L"clocks preserves the widget's attachment to work-area edges.\r\n\r\nOnly a double-click "
    L"directly on the main clock face toggles its second hand. Additional clock menus contain "
    L"only size choices. Additional clocks share the widget’s language, time format, fonts, and "
    L"offset; their digital time omits seconds.",
    L"\r\n\r\nZusätzliche Uhren: Auf der Registerkarte Allgemein kann das Widget Kalender mit Uhr "
    L"bis zu zwei weitere Uhren mit eigenen Namen und Zeitzonen anzeigen. Jede Uhr zeigt dann "
    L"auch ihren lokalen Wochentag. Die Größe jedes Zifferblatts lässt sich unter Darstellung "
    L"oder in seinem Kontextmenü wählen. Zusätzliche Uhren haben keinen Sekundenzeiger. Beim "
    L"Hinzufügen, Entfernen oder Ändern der Größe bleibt das Widget an denselben "
    L"Arbeitsbereichsrändern ausgerichtet.\r\n\r\nNur ein Doppelklick direkt auf das "
    L"Hauptzifferblatt schaltet dessen Sekundenzeiger um. Die Menüs zusätzlicher Uhren enthalten "
    L"nur Größen. Zusätzliche Uhren übernehmen Sprache, Zeitformat, Schriften und Versatz des "
    L"Widgets; ihre digitale Zeit zeigt keine Sekunden.",
    L"\r\n\r\nHorloges supplémentaires : Dans l’onglet Général, le widget Calendrier avec horloge "
    L"peut afficher deux horloges supplémentaires avec leurs propres noms et fuseaux horaires. "
    L"Chaque horloge affiche alors aussi son jour de la semaine local. Choisissez la taille de "
    L"chaque cadran dans Apparence ou dans son menu contextuel. Les horloges supplémentaires "
    L"n’ont pas de trotteuse. L’ajout, le retrait et le redimensionnement préservent l’alignement "
    L"du widget sur les bords de la zone de travail.\r\n\r\nSeul un double-clic directement sur "
    L"le cadran principal active ou désactive sa trotteuse. Les menus des cadrans supplémentaires "
    L"ne proposent que les tailles. Ces horloges partagent la langue, le format, les polices et "
    L"le décalage du widget ; leur heure numérique omet les secondes.",
    L"\r\n\r\nRelojes adicionales: En la pestaña General, Calendario con reloj permite mostrar "
    L"hasta dos relojes adicionales con nombres y zonas horarias propios. Cada reloj muestra "
    L"también su día de la semana local. El tamaño de cada esfera se elige en Apariencia o en su "
    L"menú contextual. Los relojes adicionales no tienen segundero. Al añadir, quitar o cambiar "
    L"el tamaño de los relojes se conserva la posición del widget junto a los bordes del área de "
    L"trabajo.\r\n\r\nSolo un doble clic directamente sobre la esfera principal activa o "
    L"desactiva su segundero. Los menús de los relojes adicionales solo contienen tamaños. "
    L"Comparten el idioma, formato, fuentes y desfase del widget; su hora digital no muestra "
    L"segundos.",
    L"\r\n\r\nOrologi aggiuntivi: Nella scheda Generali, Calendario con orologio può mostrare "
    L"fino a due orologi aggiuntivi con nomi e fusi orari propri. Ogni orologio mostra anche il "
    L"giorno della settimana locale. La dimensione di ogni quadrante si sceglie in Aspetto o nel "
    L"suo menu contestuale. Gli orologi aggiuntivi non hanno la lancetta dei secondi. Aggiungere, "
    L"rimuovere o ridimensionare gli orologi mantiene il widget agganciato agli stessi bordi "
    L"dell’area di lavoro.\r\n\r\nSolo un doppio clic direttamente sul quadrante principale "
    L"attiva o disattiva la lancetta dei secondi. I menu dei quadranti aggiuntivi contengono solo "
    L"le dimensioni. Condividono lingua, formato, caratteri e offset del widget; l’ora digitale "
    L"non mostra i secondi.",
    L"\r\n\r\nDodatkowe zegary: Na karcie Ogólne widżet Kalendarz z zegarem może wyświetlać dwa "
    L"dodatkowe zegary z własnymi nazwami i strefami czasowymi. Każdy zegar pokazuje wtedy także "
    L"lokalny dzień tygodnia. Rozmiar każdej tarczy można wybrać na karcie Wygląd lub w jej menu "
    L"kontekstowym. Dodatkowe zegary nie mają sekundnika. Dodawanie, usuwanie i zmiana rozmiaru "
    L"zegarów zachowują przyciągnięcie widżetu do tych samych krawędzi obszaru "
    L"roboczego.\r\n\r\nTylko dwuklik bezpośrednio na głównej tarczy przełącza jej sekundnik. "
    L"Menu dodatkowych tarcz zawierają wyłącznie rozmiary. Dodatkowe zegary współdzielą język, "
    L"format czasu, czcionki i przesunięcie widżetu; ich czas cyfrowy nie zawiera sekund.",
    L"\r\n\r\nĎalšie hodiny: Vo widgete Kalendár s hodinami možno na karte Všeobecné zapnúť až "
    L"dvoje ďalšie hodiny s vlastnými názvami a časovými pásmami. Pri každých hodinách sa potom "
    L"zobrazí aj príslušný deň týždňa. Veľkosť každého ciferníka sa volí samostatne na karte "
    L"Vzhľad alebo v jeho kontextovej ponuke. Ďalšie hodiny nemajú sekundovú ručičku. Pri "
    L"pridávaní, odoberaní a zmene veľkosti zostane widget prichytený k rovnakým hranám pracovnej "
    L"plochy.\r\n\r\nDvojklik prepína sekundovú ručičku iba priamo na hlavnom ciferníku. Ponuky "
    L"ďalších ciferníkov obsahujú iba veľkosti. Ďalšie hodiny zdieľajú jazyk, formát času, písma "
    L"a offset widgetu; ich digitálny čas sa zobrazuje bez sekúnd.",
    L"\r\n\r\nAdditional clocks: On the General tab, a Calendar with clock widget can show up to "
    L"two additional clocks with their own names and time zones. Each clock then also shows its "
    L"local day of the week. Choose each clock face size separately on the Appearance tab or from "
    L"its right-click menu. Additional clocks have no second hand. Adding, removing, or resizing "
    L"clocks preserves the widget's attachment to work-area edges.\r\n\r\nOnly a double-click "
    L"directly on the main clock face toggles its second hand. Additional clock menus contain "
    L"only size choices. Additional clocks share the widget’s language, time format, fonts, and "
    L"offset; their digital time omits seconds.",
    L"\r\n\r\nAdditional clocks: On the General tab, a Calendar with clock widget can show up to "
    L"two additional clocks with their own names and time zones. Each clock then also shows its "
    L"local day of the week. Choose each clock face size separately on the Appearance tab or from "
    L"its right-click menu. Additional clocks have no second hand. Adding, removing, or resizing "
    L"clocks preserves the widget's attachment to work-area edges.\r\n\r\nOnly a double-click "
    L"directly on the main clock face toggles its second hand. Additional clock menus contain "
    L"only size choices. Additional clocks share the widget’s language, time format, fonts, and "
    L"offset; their digital time omits seconds.",
    L"\r\n\r\nRelógios adicionais: No separador Geral, Calendário com relógio pode apresentar até "
    L"dois relógios adicionais com nomes e fusos horários próprios. Cada relógio apresenta também "
    L"o dia da semana local. Escolha o tamanho de cada mostrador em Aspeto ou no respetivo menu "
    L"de contexto. Os relógios adicionais não têm ponteiro dos segundos. Adicionar, remover ou "
    L"redimensionar relógios mantém o widget junto às mesmas margens da área de "
    L"trabalho.\r\n\r\nSó um duplo clique diretamente no mostrador principal alterna o ponteiro "
    L"dos segundos. Os menus dos mostradores adicionais contêm apenas tamanhos. Estes relógios "
    L"partilham o idioma, formato, tipos de letra e desvio do widget; a hora digital não mostra "
    L"segundos.",
    L"\r\n\r\nEkstra klokker: På fanen Generelt kan Kalender med klokke vise opptil to ekstra "
    L"klokker med egne navn og tidssoner. Hver klokke viser også sin lokale ukedag. Velg "
    L"størrelsen på hver urskive under Utseende eller i dens høyreklikkmeny. Ekstra klokker har "
    L"ingen sekundviser. Når klokker legges til, fjernes eller endrer størrelse, forblir widgeten "
    L"festet til de samme kantene av arbeidsområdet.\r\n\r\nBare et dobbeltklikk direkte på "
    L"hovedurskiven veksler sekundviseren. Menyene for ekstra urskiver inneholder bare "
    L"størrelser. Ekstra klokker deler widgetens språk, tidsformat, skrifter og forskyvning; den "
    L"digitale tiden viser ikke sekunder.",
    L"\r\n\r\nExtra klockor: På fliken Allmänt kan Kalender med klocka visa upp till två extra "
    L"klockor med egna namn och tidszoner. Varje klocka visar även sin lokala veckodag. Välj "
    L"storlek för varje urtavla under Utseende eller i dess högerklicksmeny. Extra klockor saknar "
    L"sekundvisare. När klockor läggs till, tas bort eller ändrar storlek ligger widgeten kvar "
    L"vid samma kanter av arbetsområdet.\r\n\r\nEndast ett dubbelklick direkt på huvudurtavlan "
    L"växlar sekundvisaren. Menyerna för extra urtavlor innehåller bara storlekar. Extra klockor "
    L"delar widgetens språk, tidsformat, teckensnitt och förskjutning; den digitala tiden visar "
    L"inte sekunder.",
    L"\r\n\r\nLisäkellot: Yleiset-välilehdellä Kalenteri ja kello voi näyttää kaksi lisäkelloa, "
    L"joilla on omat nimet ja aikavyöhykkeet. Jokainen kello näyttää myös paikallisen "
    L"viikonpäivän. Valitse kunkin kellotaulun koko Ulkoasu-välilehdellä tai sen pikavalikosta. "
    L"Lisäkelloissa ei ole sekuntiviisaria. Kellojen lisääminen, poistaminen tai koon muuttaminen "
    L"säilyttää widgetin kiinnityksen työalueen samoihin reunoihin.\r\n\r\nVain pääkellotaulun "
    L"suora kaksoisnapsautus vaihtaa sen sekuntiviisarin näkyvyyttä. Lisäkellojen valikoissa on "
    L"vain kokovaihtoehdot. Lisäkellot käyttävät pienoisohjelman kieltä, aikamuotoa, fontteja ja "
    L"poikkeamaa; niiden digitaalinen aika ei sisällä sekunteja.",
    L"\r\n\r\nEkstra ure: På fanen Generelt kan Kalender med ur vise op til to ekstra ure med "
    L"egne navne og tidszoner. Hvert ur viser også sin lokale ugedag. Vælg størrelsen på hver "
    L"urskive under Udseende eller i dens højrekliksmenu. Ekstra ure har ingen sekundviser. Når "
    L"ure tilføjes, fjernes eller ændrer størrelse, forbliver widgetten fastgjort til de samme "
    L"kanter af arbejdsområdet.\r\n\r\nKun et dobbeltklik direkte på hovedurskiven skifter "
    L"sekundviseren. Menuerne for ekstra urskiver indeholder kun størrelser. Ekstra ure deler "
    L"widgetens sprog, tidsformat, skrifttyper og forskydning; den digitale tid viser ikke "
    L"sekunder.",
    L"\r\n\r\nViðbótarklukkur: Á flipanum Almennt getur Dagatal með klukku sýnt allt að tvær "
    L"viðbótarklukkur með eigin nöfnum og tímabeltum. Hver klukka sýnir einnig vikudaginn á sínum "
    L"stað. Veldu stærð hverrar klukkuskífu í Útliti eða í hægrismellivalmynd hennar. "
    L"Viðbótarklukkur hafa engan sekúnduvísi. Þegar klukkum er bætt við, þær fjarlægðar eða stærð "
    L"þeirra breytt helst græjan við sömu brúnir vinnusvæðisins.\r\n\r\nAðeins tvísmellur beint á "
    L"aðalskífuna skiptir um sýnileika sekúnduvísisins. Valmyndir aukaskífa innihalda aðeins "
    L"stærðir. Aukaklukkur nota tungumál, tímasnið, letur og hliðrun græjunnar; stafræni tíminn "
    L"sýnir ekki sekúndur.",
    L"\r\n\r\nEk saatler: Genel sekmesinde Saatli takvim bileşeni, kendi adları ve saat dilimleri "
    L"olan iki ek saat gösterebilir. Her saat kendi yerel haftanın gününü de gösterir. Her "
    L"kadranın boyutunu Görünüm sekmesinden veya kendi sağ tıklama menüsünden seçin. Ek saatlerde "
    L"saniye ibresi yoktur. Saat eklerken, kaldırırken veya boyutunu değiştirirken bileşen "
    L"çalışma alanının aynı kenarlarına bağlı kalır.\r\n\r\nYalnızca ana kadrana doğrudan çift "
    L"tıklamak saniye ibresini açıp kapatır. Ek kadranların menülerinde yalnızca boyutlar "
    L"bulunur. Ek saatler aracın dilini, zaman biçimini, yazı tiplerini ve ofsetini paylaşır; "
    L"dijital saatlerinde saniye gösterilmez.",
    L"\r\n\r\nLisakellad\r\nKalender ja kell võib vahekaardil Üldine kuvada kuni kahte lisakella "
    L"oma nime ja ajavööndiga. Iga kell kuvab siis ka kohaliku nädalapäeva. Sihverplaadi suurus "
    L"valitakse eraldi vahekaardil Ilme või selle paremklõpsumenüüs. Lisakelladel pole "
    L"sekundiosutit. Lisamine, eemaldamine ja suuruse muutmine säilitavad kinnituse tööala "
    L"servade külge.\r\n\r\nAinult otse peamisel sihverplaadil tehtud topeltklõps lülitab selle "
    L"sekundiosutit. Lisakella menüüs on ainult suurused. Lisakellad jagavad vidina keelt, "
    L"ajavormingut, fonte ja nihet; nende digitaalkuva ei näita sekundeid.",
    L"\r\n\r\nCloig bhreise\r\nIs féidir le Féilire agus clog suas le dhá chlog bhreise a "
    L"thaispeáint ar Ginearálta, lena n-ainmneacha agus a gcriosanna ama féin. Taispeánann gach "
    L"clog lá áitiúil na seachtaine ansin freisin. Roghnaítear méid gach aghaidhe ar Cuma nó ina "
    L"roghchlár deaschliceála. Níl lámh soicindí ag cloig bhreise. Coinníonn cur leis, baint agus "
    L"athrú méide an ceangal le himill an limistéir oibre.\r\n\r\nNí athraíonn ach déchliceáil "
    L"díreach ar an bpríomhaghaidh a lámh soicindí. Níl ach méideanna i roghchláir na gclog "
    L"breise. Roinneann siad teanga, formáid ama, clónna agus fritháireamh na giuirléide; níl "
    L"soicindí ina dtaispeáint dhigiteach.",
    L"\r\n\r\nPapildomi laikrodžiai\r\nKalendorius su laikrodžiu skirtuke Bendra gali rodyti iki "
    L"dviejų papildomų laikrodžių su savais pavadinimais ir laiko juostomis. Kiekvienas tada rodo "
    L"ir vietinę savaitės dieną. Dydis pasirenkamas atskirai skirtuke Išvaizda arba ciferblato "
    L"kontekstiniame meniu. Papildomi laikrodžiai neturi sekundžių rodyklės. Įtraukimas, "
    L"pašalinimas ir dydžio keitimas išlaiko prikabinimą prie darbo srities kraštų.\r\n\r\nTik "
    L"dukart spustelėjus tiesiai pagrindinį ciferblatą perjungiama jo sekundžių rodyklė. "
    L"Papildomų laikrodžių meniu yra tik dydžiai. Jie naudoja valdiklio kalbą, laiko formatą, "
    L"šriftus ir poslinkį; skaitmeninis laikas rodomas be sekundžių.",
    L"\r\n\r\nPapildu pulksteņi\r\nKalendārs ar pulksteni cilnē Vispārīgi var rādīt līdz diviem "
    L"papildu pulksteņiem ar saviem nosaukumiem un laika joslām. Tad katrs rāda arī vietējo "
    L"nedēļas dienu. Lielumu izvēlas atsevišķi cilnē Izskats vai ciparnīcas kontekstizvēlnē. "
    L"Papildu pulksteņiem nav sekunžu rādītāja. Pievienošana, noņemšana un lieluma maiņa saglabā "
    L"piesaisti darba apgabala malām.\r\n\r\nTikai dubultklikšķis tieši uz galvenās ciparnīcas "
    L"pārslēdz tās sekunžu rādītāju. Papildu pulksteņu izvēlnēs ir tikai lielumi. Tie izmanto "
    L"logrīka valodu, laika formātu, fontus un nobīdi; digitālajā laikā nav sekunžu.",
    L"\r\n\r\nTovábbi órák\r\nA Naptár órával az Általános fülön legfeljebb két további órát "
    L"mutathat saját névvel és időzónával. Ekkor mindegyik a hét helyi napját is jelzi. A méret "
    L"külön választható a Megjelenés fülön vagy a számlap helyi menüjében. A további óráknak "
    L"nincs másodpercmutatójuk. Hozzáadás, eltávolítás és átméretezés megtartja a munkaterület "
    L"széleihez csatlakozást.\r\n\r\nCsak a fő számlapra közvetlenül történő dupla kattintás "
    L"kapcsolja a másodpercmutatóját. A további órák menüje csak méretet tartalmaz. Közös a "
    L"minialkalmazás nyelve, időformátuma, betűtípusai és eltolása; digitális idejük másodpercek "
    L"nélküli.",
    L"\r\n\r\nArloġġi addizzjonali\r\nKalendarju bl-arloġġ jista’ juri sa żewġ arloġġi "
    L"addizzjonali fit-tab Ġenerali, bl-ismijiet u ż-żoni tal-ħin tagħhom. Kull wieħed imbagħad "
    L"juri wkoll il-jum lokali tal-ġimgħa. Id-daqs jintgħażel separatament fit-tab Dehra jew "
    L"mill-menu tal-wiċċ. L-arloġġi addizzjonali m’għandhomx id tas-sekondi. Iż-żieda, "
    L"it-tneħħija u l-bidla fid-daqs iżommu t-twaħħil mat-truf taż-żona tax-xogħol.\r\n\r\nKlikk "
    L"doppju direttament fuq il-wiċċ prinċipali biss jaqleb l-id tas-sekondi tiegħu. Il-menus "
    L"tal-arloġġi addizzjonali fihom daqsijiet biss. Dawn jaqsmu l-lingwa, il-format tal-ħin, "
    L"il-fonts u l-kumpens tal-widget; il-wiri diġitali tagħhom ma jurix sekondi.",
    L"\r\n\r\nExtra klokken\r\nKalender met klok kan op Algemeen maximaal twee extra klokken met "
    L"eigen namen en tijdzones tonen. Elke klok toont dan ook zijn lokale weekdag. Kies elke "
    L"wijzerplaatgrootte afzonderlijk op Vormgeving of in het contextmenu. Extra klokken hebben "
    L"geen secondewijzer. Toevoegen, verwijderen en vergroten of verkleinen behoudt de verbinding "
    L"met de randen van het werkgebied.\r\n\r\nAlleen dubbelklikken rechtstreeks op de "
    L"hoofdwijzerplaat schakelt de secondewijzer daarvan. Menu’s van extra klokken bevatten "
    L"alleen groottes. Zij delen taal, tijdnotatie, lettertypen en verschuiving van de widget; "
    L"hun digitale tijd toont geen seconden.",
    L"\r\n\r\nCeasuri suplimentare\r\nCalendar cu ceas poate afișa în General până la două "
    L"ceasuri suplimentare cu nume și fusuri orare proprii. Fiecare arată atunci și ziua locală a "
    L"săptămânii. Dimensiunea se alege separat în Aspect sau meniul contextual al cadranului. "
    L"Ceasurile suplimentare nu au secundar. Adăugarea, eliminarea și redimensionarea păstrează "
    L"atașarea la marginile zonei de lucru.\r\n\r\nNumai dublul clic direct pe cadranul principal "
    L"comută secundarul acestuia. Meniurile ceasurilor suplimentare conțin doar dimensiuni. Ele "
    L"folosesc limba, formatul orei, fonturile și decalajul widgetului; afișajul digital nu are "
    L"secunde.",
    L"\r\n\r\nΠρόσθετα ρολόγια\r\nΤο Ημερολόγιο με ρολόι μπορεί στα Γενικά να δείξει έως δύο "
    L"πρόσθετα ρολόγια με δικά τους ονόματα και ζώνες ώρας. Κάθε ρολόι τότε δείχνει και την "
    L"τοπική ημέρα εβδομάδας. Το μέγεθος επιλέγεται χωριστά στην Εμφάνιση ή στο μενού του "
    L"καντράν. Τα πρόσθετα ρολόγια δεν έχουν δείκτη δευτερολέπτων. Προσθήκη, κατάργηση και αλλαγή "
    L"μεγέθους διατηρούν την προσκόλληση στα άκρα της περιοχής εργασίας.\r\n\r\nΜόνο το διπλό "
    L"κλικ απευθείας στο κύριο καντράν αλλάζει τον δείκτη δευτερολέπτων του. Τα πρόσθετα μενού "
    L"έχουν μόνο μεγέθη. Τα πρόσθετα ρολόγια μοιράζονται γλώσσα, μορφή ώρας, γραμματοσειρές και "
    L"μετατόπιση του στοιχείου· η ψηφιακή ώρα τους δεν έχει δευτερόλεπτα.",
    L"\r\n\r\nDodatni satovi\r\nNa kartici Općenito kalendar sa satom može prikazivati do dva "
    L"dodatna sata s vlastitim nazivima i vremenskim zonama. Tada svaki sat prikazuje i lokalni "
    L"dan u sedmici. Veličina svakog brojčanika bira se zasebno na kartici Izgled ili u njegovu "
    L"kontekstnom meniju. Dodatni satovi nemaju sekundnu kazaljku. Dodavanje, uklanjanje ili "
    L"promjena veličine čuva priljubljivanje vidžeta uz ivice radnog područja.\r\n\r\nSamo "
    L"dvostruki klik direktno na glavni brojčanik mijenja prikaz njegove sekundne kazaljke. "
    L"Meniji dodatnih satova sadrže samo veličine. Dodatni satovi dijele jezik, oblik vremena, "
    L"fontove i pomak vidžeta; njihov digitalni prikaz nema sekunde.",
    L"\r\n\r\nDodatni satovi\r\nNa kartici Općenito kalendar sa satom može prikazivati do dva "
    L"dodatna sata s vlastitim nazivima i vremenskim zonama. Tada svaki sat prikazuje i lokalni "
    L"dan u tjednu. Veličina svakog brojčanika bira se zasebno na kartici Izgled ili u njegovu "
    L"kontekstnom izborniku. Dodatni satovi nemaju sekundnu kazaljku. Dodavanje, uklanjanje ili "
    L"promjena veličine čuva priljubljivanje widgeta uz rubove radnog područja.\r\n\r\nSamo "
    L"dvostruki klik izravno na glavni brojčanik mijenja prikaz njegove sekundne kazaljke. "
    L"Izbornici dodatnih satova sadrže samo veličine. Dodatni satovi dijele jezik, oblik vremena, "
    L"fontove i pomak widgeta; njihov digitalni prikaz nema sekunde.",
    L"\r\n\r\nDodatne ure\r\nKoledar z uro lahko na zavihku Splošno prikaže do dve dodatni uri z "
    L"lastnima imenoma in časovnima pasovoma. Vsaka nato kaže tudi svoj krajevni dan v tednu. "
    L"Velikost številčnice izberete posebej na zavihku Videz ali v njenem kontekstnem meniju. "
    L"Dodatne ure nimajo sekundnega kazalca. Dodajanje, odstranjevanje in spreminjanje velikosti "
    L"ohrani pripetost gradnika na robove delovnega območja.\r\n\r\nSekundni kazalec preklopi le "
    L"dvoklik neposredno na glavno številčnico. Meniji dodatnih ur vsebujejo le velikosti. "
    L"Dodatne ure uporabljajo jezik, obliko časa, pisave in odmik gradnika; njihov digitalni čas "
    L"ne kaže sekund.",
    L"\r\n\r\nDodatni satovi\r\nKalendar sa satom na kartici Opšte može prikazati do dva dodatna "
    L"sata sa sopstvenim nazivima i vremenskim zonama. Svaki tada pokazuje i lokalni dan "
    L"nedjelje. Veličina brojčanika bira se posebno na kartici Izgled ili u njegovom kontekstnom "
    L"meniju. Dodatni satovi nemaju sekundnu kazaljku. Dodavanje, uklanjanje i promjena veličine "
    L"čuvaju priljepljivanje uz ivice radne površine.\r\n\r\nSamo dvoklik neposredno na glavni "
    L"brojčanik prebacuje njegovu sekundnu kazaljku. Meniji dodatnih satova sadrže samo veličine. "
    L"Oni dijele jezik, oblik vremena, fontove i pomak vidžeta; njihov digitalni prikaz nema "
    L"sekunde.",
    L"\r\n\r\nДадатковыя гадзіннікі\r\nКаляндар з гадзіннікам на ўкладцы «Агульныя» можа мець да "
    L"двух дадатковых гадзіннікаў з уласнымі назвамі і часавымі паясамі. Тады кожны паказвае і "
    L"свой мясцовы дзень тыдня. Памер цыферблата выбіраецца асобна на ўкладцы «Выгляд» або ў яго "
    L"кантэкстным меню. Дадатковыя гадзіннікі не маюць секунднай стрэлкі. Дадаванне, выдаленне і "
    L"змена памеру захоўваюць прывязку да краёў рабочай вобласці.\r\n\r\nСекундная стрэлка "
    L"пераключаецца толькі падвойнай пстрычкай непасрэдна на галоўным цыферблаце. Меню дадатковых "
    L"гадзіннікаў мае толькі памеры. Яны выкарыстоўваюць мову, фармат часу, шрыфты і зрушэнне "
    L"віджэта; іх лічбавы час не мае секунд.",
    L"\r\n\r\nДопълнителни часовници\r\nКалендарът с часовник може да показва до два допълнителни "
    L"часовника със собствени имена и часови зони чрез раздела „Общи“. Тогава всеки показва и "
    L"своя местен ден от седмицата. Размерът се избира отделно в „Изглед“ или контекстното меню "
    L"на циферблата. Допълнителните часовници нямат секундна стрелка. Добавянето, премахването и "
    L"промяната на размера запазват прилепването към краищата на работната област.\r\n\r\nСамо "
    L"двойно щракване направо върху главния циферблат превключва неговата секундна стрелка. "
    L"Менютата на допълнителните часовници съдържат само размери. Те споделят езика, формата на "
    L"часа, шрифтовете и отместването на модула; цифровото им време няма секунди.",
    L"\r\n\r\nДополнителни часовници\r\nКалендарот со часовник може да прикаже до два "
    L"дополнителни часовника со свои имиња и временски зони на картичката „Општо“. Тогаш секој го "
    L"покажува и својот локален ден во неделата. Големината на бројчаникот се избира посебно во "
    L"„Изглед“ или неговото контекстно мени. Дополнителните часовници немаат секундна стрелка. "
    L"Додавањето, отстранувањето и менувањето на големината го зачувуваат прилепувањето кон "
    L"рабовите на работната површина.\r\n\r\nСамо двоен клик непосредно на главниот бројчаник ја "
    L"менува неговата секундна стрелка. Менијата на дополнителните часовници содржат само "
    L"големини. Тие ги делат јазикот, обликот на времето, фонтовите и поместувањето на виџетот; "
    L"нивното дигитално време нема секунди.",
    L"\r\n\r\nДодатни сатови\r\nКалендар са сатом на картици Опште може приказати до два додатна "
    L"сата са сопственим називима и временским зонама. Сваки тада показује и локални дан недеље. "
    L"Величина бројчаника бира се посебно на картици Изглед или у његовом контекстном менију. "
    L"Додатни сатови немају секундну казаљку. Додавање, уклањање и промена величине чувају "
    L"прилепљивање уз ивице радне површине.\r\n\r\nСамо двоклик непосредно на главни бројчаник "
    L"пребацује његову секундну казаљку. Менији додатних сатова садрже само величине. Они деле "
    L"језик, облик времена, фонтове и помак виџета; њихов дигитални приказ нема секунде.",
    L"\r\n\r\nДодаткові годинники: на вкладці «Загальні» для календаря з годинником можна "
    L"ввімкнути до двох додаткових годинників із власними назвами та часовими поясами. Тоді кожен "
    L"годинник також показує місцевий день тижня. Розмір кожного циферблата вибирається окремо на "
    L"вкладці «Вигляд» або в його контекстному меню. Додаткові годинники не мають секундної "
    L"стрілки. Додавання, видалення або зміна розміру годинників зберігає прив’язку віджета до "
    L"країв робочої області.\r\n\r\nСекундна стрілка перемикається лише подвійним клацанням "
    L"безпосередньо на головному циферблаті. Меню додаткових годинників містять лише розміри. "
    L"Додаткові годинники використовують мову, формат часу, шрифти та зсув віджета; їхній "
    L"цифровий час не містить секунд.",
    L"\r\n\r\nДополнительные часы: на вкладке «Общие» для календаря с часами можно включить до "
    L"двух дополнительных часов с собственными названиями и часовыми поясами. Тогда каждые часы "
    L"также показывают местный день недели. Размер каждого циферблата выбирается отдельно на "
    L"вкладке «Внешний вид» или в его контекстном меню. У дополнительных часов нет секундной "
    L"стрелки. Добавление, удаление или изменение размера часов сохраняет привязку виджета к краям "
    L"рабочей области.\r\n\r\nСекундная стрелка переключается только двойным щелчком "
    L"непосредственно по главному циферблату. Меню дополнительных часов содержат только размеры. "
    L"Дополнительные часы используют язык, формат времени, шрифты и смещение виджета; их цифровое "
    L"время не содержит секунд."
};

const wchar_t* HELP_TIME_FORMAT_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nFORMÁT ČASU A PÁSMA\r\nFormát času na kartě Obecné nabízí Podle jazyka (výchozí), "
    L"12 hodin a 24 hodin. Podle jazyka převezme cyklus dané země; ruční volba zůstane zachována "
    L"při změně jazyka. Oddělovače a označení části dne odpovídají jazyku widgetu. Zatržítko "
    L"AM/PM je ve výchozím stavu zapnuto a ve 12hodinovém režimu ovládá pouze označení části dne; "
    L"není-li v dané kultuře definováno, použije se AM/PM. Na celomonitorových hodinách je "
    L"označení na samostatném spodním řádku. UTC vždy používá 24hodinový formát. Pojmenovaná "
    L"pásma používají občanský čas daného místa včetně jeho letního času; offset u názvu odpovídá "
    L"aktuálnímu datu. Samostatné položky UTC jsou pevné offsety od −12:00 do +14:00 po 15 "
    L"minutách a letní čas nepoužívají.",
    L"\r\n\r\nTIME FORMAT AND TIME ZONES\r\nTime format on the General tab offers Language "
    L"default (the default), 12 hours, and 24 hours. Language default follows the selected "
    L"culture; a manual choice is retained when the widget language changes. Separators and time "
    L"markers follow the widget language. AM/PM is checked by default and controls only the "
    L"marker in 12-hour mode; AM/PM is used when the culture defines no marker. Monitor clocks "
    L"show the marker on a separate line below the time. UTC always uses 24-hour time. Named time "
    L"zones follow local civil time, including local daylight saving time; the offset next to the "
    L"name reflects the current date. Standalone UTC entries are fixed offsets from -12:00 to "
    L"+14:00 in 15-minute steps and do not observe daylight saving time.",
    L"\r\n\r\nZEITFORMAT UND ZEITZONEN\r\nZeitformat auf Allgemein bietet Nach Sprache "
    L"(Standard), 12 Stunden und 24 Stunden. Nach Sprache folgt der gewählten Kultur; eine "
    L"manuelle Auswahl bleibt bei Sprachänderungen erhalten. Trennzeichen und Tageszeitangaben "
    L"folgen der Widget-Sprache. AM/PM ist standardmäßig aktiviert und schaltet im "
    L"12-Stunden-Format nur die Tageszeitangabe um; ohne kultureigene Angabe wird AM/PM "
    L"verwendet. Bildschirmuhren zeigen sie in einer eigenen Zeile unter der Uhrzeit. UTC "
    L"verwendet immer das 24-Stunden-Format. Benannte Zeitzonen folgen der jeweiligen Ortszeit "
    L"einschließlich Sommerzeit; der Versatz neben dem Namen gilt für das aktuelle Datum. "
    L"Einzelne UTC-Einträge sind feste Versätze von −12:00 bis +14:00 in 15-Minuten-Schritten "
    L"ohne Sommerzeit.",
    L"\r\n\r\nFORMAT DE L’HEURE ET FUSEAUX\r\nFormat de l’heure dans Général propose Selon la "
    L"langue (par défaut), 12 heures et 24 heures. Le choix manuel est conservé lors d’un "
    L"changement de langue. Les séparateurs et indications suivent la langue du widget. AM/PM est "
    L"coché par défaut et commande uniquement l’indication en mode 12 heures ; AM/PM est utilisé "
    L"si la culture n’en définit aucune. Les horloges plein écran placent cette indication sur "
    L"une ligne sous l’heure. UTC utilise toujours le format 24 heures. Les fuseaux nommés "
    L"suivent l’heure civile locale, y compris l’heure d’été ; le décalage indiqué correspond à "
    L"la date actuelle. Les entrées UTC seules sont des décalages fixes de −12:00 à +14:00 par "
    L"pas de 15 minutes, sans heure d’été.",
    L"\r\n\r\nFORMATO DE HORA Y ZONAS HORARIAS\r\nFormato de hora en General ofrece Según el "
    L"idioma (predeterminado), 12 horas y 24 horas. La elección manual se conserva al cambiar el "
    L"idioma. Los separadores e indicadores siguen el idioma del widget. AM/PM está marcado de "
    L"forma predeterminada y controla solo el indicador en modo de 12 horas; se usa AM/PM si la "
    L"cultura no define ninguno. Los relojes de monitor muestran el indicador en una línea debajo "
    L"de la hora. UTC siempre usa el formato de 24 horas. Las zonas con nombre siguen la hora "
    L"civil local, incluido el horario de verano; el desfase indicado corresponde a la fecha "
    L"actual. Las entradas UTC independientes son desfases fijos de −12:00 a +14:00 en pasos de "
    L"15 minutos, sin horario de verano.",
    L"\r\n\r\nFORMATO DELL’ORA E FUSI ORARI\r\nFormato ora in Generali offre Secondo la lingua "
    L"(predefinito), 12 ore e 24 ore. La scelta manuale viene mantenuta quando cambia la lingua. "
    L"Separatori e indicatori seguono la lingua del widget. AM/PM è selezionato per impostazione "
    L"predefinita e controlla solo l’indicatore nel formato a 12 ore; si usa AM/PM se la cultura "
    L"non ne definisce uno. Gli orologi a schermo intero mostrano l’indicatore su una riga sotto "
    L"l’ora. UTC usa sempre il formato a 24 ore. I fusi con nome seguono l’ora civile locale, "
    L"inclusa l’ora legale; lo scostamento indicato corrisponde alla data attuale. Le voci UTC "
    L"separate sono scostamenti fissi da −12:00 a +14:00 a intervalli di 15 minuti, senza ora "
    L"legale.",
    L"\r\n\r\nFORMAT CZASU I STREFY\r\nFormat czasu na karcie Ogólne oferuje Według języka "
    L"(domyślnie), 12 godzin i 24 godziny. Ręczny wybór pozostaje zachowany przy zmianie języka. "
    L"Separatory i oznaczenia odpowiadają językowi widżetu. AM/PM jest domyślnie zaznaczone i "
    L"steruje tylko oznaczeniem w trybie 12-godzinnym; gdy kultura nie określa oznaczenia, "
    L"używane jest AM/PM. Zegary pełnoekranowe pokazują je w osobnym wierszu pod czasem. UTC "
    L"zawsze używa formatu 24-godzinnego. Nazwane strefy stosują lokalny czas urzędowy, w tym "
    L"czas letni; przesunięcie obok nazwy odpowiada bieżącej dacie. Osobne wpisy UTC to stałe "
    L"przesunięcia od −12:00 do +14:00 co 15 minut, bez czasu letniego.",
    L"\r\n\r\nFORMÁT ČASU A PÁSMA\r\nFormát času na karte Všeobecné ponúka Podľa jazyka "
    L"(predvolené), 12 hodín a 24 hodín. Ručná voľba zostane zachovaná pri zmene jazyka. "
    L"Oddeľovače a označenia časti dňa zodpovedajú jazyku widgetu. AM/PM je predvolene "
    L"začiarknuté a v 12-hodinovom režime ovláda iba označenie časti dňa; ak ho kultúra "
    L"nedefinuje, použije sa AM/PM. Celomonitorové hodiny ho zobrazujú na samostatnom riadku pod "
    L"časom. UTC vždy používa 24-hodinový formát. Pomenované pásma používajú občiansky čas daného "
    L"miesta vrátane jeho letného času; posun pri názve zodpovedá aktuálnemu dátumu. Samostatné "
    L"položky UTC sú pevné posuny od −12:00 do +14:00 po 15 minútach bez letného času.",
    L"\r\n\r\nTIME FORMAT AND TIME ZONES\r\nTime format on the General tab offers Language "
    L"default (the default), 12 hours, and 24 hours. Language default follows the selected "
    L"culture; a manual choice is retained when the widget language changes. Separators and time "
    L"markers follow the widget language. AM/PM is checked by default and controls only the "
    L"marker in 12-hour mode; AM/PM is used when the culture defines no marker. Monitor clocks "
    L"show the marker on a separate line below the time. UTC always uses 24-hour time. Named time "
    L"zones follow local civil time, including local daylight saving time; the offset next to the "
    L"name reflects the current date. Standalone UTC entries are fixed offsets from -12:00 to "
    L"+14:00 in 15-minute steps and do not observe daylight saving time.",
    L"\r\n\r\nTIME FORMAT AND TIME ZONES\r\nTime format on the General tab offers Language "
    L"default (the default), 12 hours, and 24 hours. Language default follows the selected "
    L"culture; a manual choice is retained when the widget language changes. Separators and time "
    L"markers follow the widget language. AM/PM is checked by default and controls only the "
    L"marker in 12-hour mode; AM/PM is used when the culture defines no marker. Monitor clocks "
    L"show the marker on a separate line below the time. UTC always uses 24-hour time. Named time "
    L"zones follow local civil time, including local daylight saving time; the offset next to the "
    L"name reflects the current date. Standalone UTC entries are fixed offsets from -12:00 to "
    L"+14:00 in 15-minute steps and do not observe daylight saving time.",
    L"\r\n\r\nFORMATO DA HORA E FUSOS HORÁRIOS\r\nFormato da hora em Geral oferece Conforme o "
    L"idioma (predefinição), 12 horas e 24 horas. A escolha manual é mantida quando o idioma "
    L"muda. Os separadores e indicadores seguem o idioma do widget. AM/PM está selecionado por "
    L"predefinição e controla apenas o indicador no modo de 12 horas; usa-se AM/PM se a cultura "
    L"não definir nenhum. Os relógios de monitor mostram o indicador numa linha abaixo da hora. "
    L"UTC usa sempre o formato de 24 horas. Os fusos com nome seguem a hora civil local, "
    L"incluindo a hora de verão; o desvio junto ao nome corresponde à data atual. As entradas UTC "
    L"isoladas são desvios fixos de −12:00 a +14:00 em intervalos de 15 minutos, sem hora de "
    L"verão.",
    L"\r\n\r\nTIDSFORMAT OG TIDSSONER\r\nTidsformat på Generelt tilbyr Etter språk (standard), 12 "
    L"timer og 24 timer. Et manuelt valg beholdes når språket endres. Skilletegn og tidsmarkører "
    L"følger widgetens språk. AM/PM er på som standard og styrer bare markøren i 12-timersformat; "
    L"AM/PM brukes hvis kulturen ikke har en egen markør. Skjermklokker viser markøren på en egen "
    L"linje under tiden. UTC bruker alltid 24-timersformat. Navngitte tidssoner følger lokal tid, "
    L"inkludert sommertid; forskyvningen ved navnet gjelder dagens dato. Egne UTC-oppføringer er "
    L"faste forskyvninger fra −12:00 til +14:00 i trinn på 15 minutter, uten sommertid.",
    L"\r\n\r\nTIDSFORMAT OCH TIDSZONER\r\nTidsformat på Allmänt erbjuder Enligt språk (standard), "
    L"12 timmar och 24 timmar. Ett manuellt val behålls när språket ändras. Avgränsare och "
    L"tidsbeteckningar följer widgetens språk. AM/PM är på som standard och styr bara "
    L"beteckningen i 12-timmarsformat; AM/PM används om kulturen saknar en egen beteckning. "
    L"Bildskärmsklockor visar den på en egen rad under tiden. UTC använder alltid "
    L"24-timmarsformat. Namngivna tidszoner följer lokal tid, inklusive sommartid; förskjutningen "
    L"vid namnet gäller dagens datum. Separata UTC-poster är fasta förskjutningar från −12:00 "
    L"till +14:00 i steg om 15 minuter, utan sommartid.",
    L"\r\n\r\nAIKAMUOTO JA AIKAVYÖHYKKEET\r\nYleiset-välilehden Aikamuoto tarjoaa Kielen mukaan "
    L"(oletus), 12 tuntia ja 24 tuntia. Käsin tehty valinta säilyy kielen vaihtuessa. Erottimet "
    L"ja merkinnät noudattavat pienoisohjelman kieltä. AM/PM on oletusarvoisesti valittu ja ohjaa "
    L"vain merkintää 12 tunnin muodossa; AM/PM-merkintää käytetään, jos kulttuurilla ei ole omaa. "
    L"Koko näytön kellot näyttävät merkinnän ajan alla omalla rivillään. UTC käyttää aina 24 "
    L"tunnin muotoa. Nimetyt aikavyöhykkeet noudattavat paikallista aikaa kesäaikoineen; nimen "
    L"vieressä oleva siirtymä vastaa nykyistä päivämäärää. Erilliset UTC-valinnat ovat kiinteitä "
    L"siirtymiä −12:00:sta +14:00:aan 15 minuutin välein ilman kesäaikaa.",
    L"\r\n\r\nTIDSFORMAT OG TIDSZONER\r\nTidsformat på Generelt tilbyder Efter sprog (standard), "
    L"12 timer og 24 timer. Et manuelt valg bevares, når sproget ændres. Separatorer og "
    L"tidsmarkører følger widgetens sprog. AM/PM er slået til som standard og styrer kun markøren "
    L"i 12-timersformat; AM/PM bruges, hvis kulturen ikke har en egen markør. Skærmure viser "
    L"markøren på en separat linje under tiden. UTC bruger altid 24-timersformat. Navngivne "
    L"tidszoner følger lokal tid inklusive sommertid; forskydningen ved navnet gælder den "
    L"aktuelle dato. Separate UTC-poster er faste forskydninger fra −12:00 til +14:00 i trin på "
    L"15 minutter uden sommertid.",
    L"\r\n\r\nTÍMASNIÐ OG TÍMABELTI\r\nTímasnið á Almennt býður Samkvæmt tungumáli (sjálfgefið), "
    L"12 klukkustundir og 24 klukkustundir. Handvirkt val helst við breytingu á tungumáli. "
    L"Aðgreiningarmerki og tímamerkingar fylgja tungumáli græjunnar. AM/PM er sjálfgefið virkt og "
    L"stjórnar aðeins merkingunni í 12 klukkustunda sniði; AM/PM er notað ef menningarsvæðið "
    L"skilgreinir enga merkingu. Skjáklukkur sýna hana á sér línu undir tímanum. UTC notar alltaf "
    L"24 klukkustunda snið. Nafngreind tímabelti fylgja staðartíma með sumartíma; hliðrunin við "
    L"nafnið gildir fyrir daginn í dag. Sérstakar UTC-færslur eru fastar hliðranir frá −12:00 til "
    L"+14:00 í 15 mínútna skrefum án sumartíma.",
    L"\r\n\r\nSAAT BİÇİMİ VE SAAT DİLİMLERİ\r\nGenel sekmesindeki Saat biçimi, Dile göre "
    L"(varsayılan), 12 saat ve 24 saat seçeneklerini sunar. Dil değiştiğinde elle seçilen düzen "
    L"korunur. Ayırıcılar ve göstergeler araç diline uyar. AM/PM varsayılan olarak işaretlidir ve "
    L"12 saatlik düzende yalnızca göstergeyi denetler; kültür bir gösterge tanımlamıyorsa AM/PM "
    L"kullanılır. Tam ekran saatler göstergeyi saatin altında ayrı bir satırda gösterir. UTC her "
    L"zaman 24 saatlik düzeni kullanır. Adlandırılmış saat dilimleri, yaz saati dahil yerel resmi "
    L"saati izler; adın yanındaki fark güncel tarihe aittir. Ayrı UTC girdileri −12:00 ile +14:00 "
    L"arasında 15 dakikalık adımlarla sabit farklardır ve yaz saati uygulamaz.",
    L"\r\n\r\nKellaajavorming ja ajavööndid\r\nKellaajavorming vahekaardil Üldine pakub Keele "
    L"vaikesätet, 12 tundi ja 24 tundi. Esimene järgib vidina keelt; käsivalik säilib keele "
    L"vahetamisel. Eraldajad ja ajatähised järgivad keelt. AM/PM on vaikimisi sees ja juhib "
    L"ainult 12-tunnise kuva tähist; keele oma tähise puudumisel kasutatakse AM/PM-i. Ekraanikell "
    L"kuvab tähise eraldi real kellaaja all. UTC kasutab alati 24-tunnist vormingut. Nimega "
    L"ajavööndid arvestavad kohalikku ja suveaega; nime kõrval olev nihe kehtib praegusele "
    L"kuupäevale. Eraldi UTC-valikud on püsinihked −12:00 kuni +14:00 15-minutilise sammuga, ilma "
    L"suveajata.",
    L"\r\n\r\nFormáid ama agus criosanna ama\r\nTugann Formáid ama ar Ginearálta De réir na "
    L"teanga (réamhshocrú), 12 uair agus 24 uair. Fanann rogha láimhe tar éis athrú teanga. "
    L"Leanann deighilteoirí agus marcóirí ama an teanga. Tá AM/PM cumasaithe ar dtús agus ní "
    L"rialaíonn sé ach an marcóir i mód 12 uair; mura bhfuil marcóirí ag an teanga, úsáidtear "
    L"AM/PM. Taispeánann cloig scáileáin é ar shraith ar leith faoin am. Úsáideann UTC formáid 24 "
    L"uair i gcónaí. Leanann criosanna ainmnithe a rialacha áitiúla agus ama samhraidh; baineann "
    L"an fritháireamh leis an dáta reatha. Is fritháirimh sheasta ó −12:00 go +14:00 i gcéimeanna "
    L"15 nóiméad iad na míreanna UTC ar leith, gan am samhraidh.",
    L"\r\n\r\nLaiko formatas ir laiko juostos\r\nLaiko formatas skirtuke Bendra siūlo Pagal kalbą "
    L"(numatyta), 12 valandų ir 24 valandos. Rankinis pasirinkimas išlieka pakeitus kalbą. "
    L"Skyrikliai ir laiko žymos priklauso nuo valdiklio kalbos. AM/PM iš pradžių įjungta ir valdo "
    L"tik 12 valandų formato žymą; jei kalba neturi savų žymų, naudojama AM/PM. Ekrano "
    L"laikrodžiai žymą rodo atskiroje eilutėje po laiku. UTC visada naudoja 24 valandų formatą. "
    L"Vardinės juostos laikosi vietinio ir vasaros laiko taisyklių; poslinkis atitinka dabartinę "
    L"datą. Atskiros UTC parinktys yra pastovūs poslinkiai nuo −12:00 iki +14:00 kas 15 minučių "
    L"be vasaros laiko.",
    L"\r\n\r\nLaika formāts un laika joslas\r\nLaika formāts cilnē Vispārīgi piedāvā Atbilstoši "
    L"valodai (noklusējums), 12 stundas un 24 stundas. Manuālā izvēle paliek pēc valodas maiņas. "
    L"Atdalītāji un laika apzīmējumi atbilst logrīka valodai. AM/PM sākumā ieslēgts un ietekmē "
    L"tikai apzīmējumu 12 stundu režīmā; ja valodai nav savu apzīmējumu, lieto AM/PM. Ekrāna "
    L"pulksteņi to rāda atsevišķā rindā zem laika. UTC vienmēr izmanto 24 stundu formātu. "
    L"Nosauktās joslas ievēro vietējo un vasaras laiku; nobīde atbilst pašreizējam datumam. "
    L"Atsevišķās UTC izvēles ir nemainīgas nobīdes no −12:00 līdz +14:00 ar 15 minūšu soli bez "
    L"vasaras laika.",
    L"\r\n\r\nIdőformátum és időzónák\r\nAz Általános fül Időformátum beállítása Nyelv szerinti "
    L"(alapértelmezett), 12 órás vagy 24 órás. A kézi választás nyelvváltáskor is megmarad. Az "
    L"elválasztók és időjelölések a minialkalmazás nyelvét követik. Az AM/PM alapból bekapcsolt, "
    L"csak a 12 órás jelölést szabályozza; saját nyelvi jelölés hiányában AM/PM használatos. A "
    L"képernyőórák külön sorban, az idő alatt jelzik. Az UTC mindig 24 órás formátumot használ. A "
    L"név szerinti zónák követik a helyi és nyári időszámítást; az eltolás az aktuális dátumra "
    L"érvényes. A külön UTC-elemek állandó eltolások −12:00 és +14:00 között 15 perces lépéssel, "
    L"nyári időszámítás nélkül.",
    L"\r\n\r\nFormat tal-ħin u żoni tal-ħin\r\nFormat tal-ħin fit-tab Ġenerali joffri Skont "
    L"il-lingwa (default), 12-il siegħa u 24 siegħa. Għażla manwali tibqa’ wara bidla fil-lingwa. "
    L"Is-separaturi u l-markaturi tal-ħin isegwu l-lingwa tal-widget. AM/PM huwa attivat "
    L"inizjalment u jikkontrolla biss il-markatur fil-format ta’ 12-il siegħa; jekk il-lingwa "
    L"m’għandhiex markaturi tagħha, jintuża AM/PM. L-arloġġi tal-iskrin juruh f’ringiela separata "
    L"taħt il-ħin. UTC dejjem juża l-format ta’ 24 siegħa. Żoni msemmija jsegwu r-regoli lokali u "
    L"tal-ħin tas-sajf; il-kumpens japplika għad-data kurrenti. L-għażliet UTC separati huma "
    L"kumpensi fissi minn −12:00 sa +14:00 f’passi ta’ 15-il minuta, mingħajr ħin tas-sajf.",
    L"\r\n\r\nTijdnotatie en tijdzones\r\nTijdnotatie op Algemeen biedt Volgens taal (standaard), "
    L"12 uur en 24 uur. Een handmatige keuze blijft na een taalwijziging behouden. "
    L"Scheidingstekens en tijdsaanduidingen volgen de widgettaal. AM/PM is aanvankelijk "
    L"ingeschakeld en regelt alleen de aanduiding bij 12 uur; zonder eigen taalaanduidingen wordt "
    L"AM/PM gebruikt. Schermklokken tonen deze in een aparte rij onder de tijd. UTC gebruikt "
    L"altijd de 24-uursnotatie. Benoemde zones volgen lokale tijd en zomertijd; de verschuiving "
    L"geldt voor de huidige datum. Aparte UTC-items zijn vaste verschuivingen van −12:00 tot "
    L"+14:00 in stappen van 15 minuten, zonder zomertijd.",
    L"\r\n\r\nFormatul orei și fusuri orare\r\nFormat oră din General oferă Conform limbii "
    L"(implicit), 12 ore și 24 de ore. Alegerea manuală rămâne după schimbarea limbii. "
    L"Separatorii și marcajele urmează limba widgetului. AM/PM este inițial activat și "
    L"controlează numai marcajul în modul de 12 ore; dacă limba nu are marcaje proprii, se "
    L"utilizează AM/PM. Ceasurile pe ecran îl arată pe un rând separat sub oră. UTC folosește "
    L"întotdeauna formatul de 24 de ore. Fusurile denumite urmează ora locală și ora de vară; "
    L"decalajul este pentru data curentă. Opțiunile UTC separate sunt decalaje fixe de la −12:00 "
    L"la +14:00 în pași de 15 minute fără oră de vară.",
    L"\r\n\r\nΜορφή ώρας και ζώνες ώρας\r\nΗ Μορφή ώρας στα Γενικά προσφέρει Σύμφωνα με τη γλώσσα "
    L"(προεπιλογή), 12 ώρες και 24 ώρες. Η χειροκίνητη επιλογή διατηρείται μετά από αλλαγή "
    L"γλώσσας. Διαχωριστικά και ενδείξεις ακολουθούν τη γλώσσα του στοιχείου. Το AM/PM είναι "
    L"αρχικά ενεργό και ελέγχει μόνο την ένδειξη στη 12ωρη μορφή· χωρίς ενδείξεις της γλώσσας "
    L"χρησιμοποιείται AM/PM. Τα ρολόγια οθόνης τη δείχνουν σε χωριστή γραμμή κάτω από την ώρα. Το "
    L"UTC χρησιμοποιεί πάντα 24ωρη μορφή. Οι ονομαστικές ζώνες ακολουθούν τοπική και θερινή ώρα· "
    L"η μετατόπιση ισχύει για την τρέχουσα ημερομηνία. Οι χωριστές επιλογές UTC είναι σταθερές "
    L"μετατοπίσεις από −12:00 έως +14:00 ανά 15 λεπτά χωρίς θερινή ώρα.",
    L"\r\n\r\nOblik vremena i vremenske zone\r\nOblik vremena na kartici Općenito nudi Prema "
    L"jeziku (podrazumijevano), 12 sati i 24 sata. Prema jeziku slijedi odabranu kulturu; ručni "
    L"se izbor čuva nakon promjene jezika vidžeta. Razdjelnici i oznake vremena prate jezik "
    L"vidžeta. AM/PM je podrazumijevano označen i upravlja samo oznakom u 12-satnom prikazu; ako "
    L"kultura nema vlastite oznake, koristi se AM/PM. Satovi na ekranu prikazuju oznaku u "
    L"zasebnom redu ispod vremena. UTC uvijek koristi 24-satni oblik. Imenovane vremenske zone "
    L"prate lokalno vrijeme i ljetno računanje vremena; pomak uz naziv odgovara trenutnom datumu. "
    L"Zasebne stavke UTC predstavljaju stalne pomake od -12:00 do +14:00 u koracima od 15 minuta, "
    L"bez ljetnog računanja vremena.",
    L"\r\n\r\nOblik vremena i vremenske zone\r\nOblik vremena na kartici Općenito nudi Prema "
    L"jeziku (zadano), 12 sati i 24 sata. Prema jeziku slijedi odabranu kulturu; ručni se izbor "
    L"čuva nakon promjene jezika widgeta. Razdjelnici i oznake vremena prate jezik widgeta. AM/PM "
    L"je zadano označen i upravlja samo oznakom u 12-satnom prikazu; ako kultura nema vlastite "
    L"oznake, koristi se AM/PM. Satovi na zaslonu prikazuju oznaku u zasebnom retku ispod "
    L"vremena. UTC uvijek koristi 24-satni oblik. Imenovane vremenske zone prate lokalno vrijeme "
    L"i ljetno računanje vremena; pomak uz naziv odgovara trenutačnom datumu. Zasebne stavke UTC "
    L"predstavljaju stalne pomake od -12:00 do +14:00 u koracima od 15 minuta, bez ljetnog "
    L"računanja vremena.",
    L"\r\n\r\nOblika časa in časovni pasovi\r\nOblika časa na zavihku Splošno ponuja Glede na "
    L"jezik (privzeto), 12 ur in 24 ur. Privzeta možnost sledi jeziku gradnika, ročna izbira pa "
    L"ostane tudi po spremembi jezika. Ločila in časovne oznake sledijo jeziku. AM/PM je privzeto "
    L"označen in določa le prikaz oznake v 12-urnem načinu. Če jezik nima svoje oznake, se "
    L"uporabi AM/PM. Ure na zaslonu jo kažejo v ločeni vrstici pod časom. UTC vedno uporablja "
    L"24-urni prikaz. Imenovani pasovi sledijo krajevnemu času in poletnemu času; odmik ob imenu "
    L"velja za trenutni datum. Samostojne izbire UTC so stalni odmiki od -12:00 do +14:00 v "
    L"korakih po 15 minut brez poletnega časa.",
    L"\r\n\r\nOblik vremena i vremenske zone\r\nOblik vremena na kartici Opšte nudi Prema jeziku "
    L"(podrazumijevano), 12 sati i 24 sata. Prva opcija prati jezik, a ručni izbor ostaje nakon "
    L"njegove promjene. Razdvajači i oznake vremena prate jezik vidžeta. AM/PM je prvobitno "
    L"uključen i upravlja samo oznakom u 12-časovnom režimu; ako jezik nema sopstvene oznake, "
    L"koristi se AM/PM. Satovi na monitoru prikazuju oznaku u zasebnom redu ispod vremena. UTC "
    L"uvijek koristi 24-časovni prikaz. Imenovane zone prate lokalno i ljetnje računanje vremena; "
    L"pomak uz naziv važi za trenutni datum. Zasebne stavke UTC su stalni pomaci od -12:00 do "
    L"+14:00 u koracima od 15 minuta bez ljetnjeg računanja vremena.",
    L"\r\n\r\nФармат часу і часавыя паясы\r\n«Фармат часу» на ўкладцы «Агульныя» прапануе "
    L"«Паводле мовы» (прадвызначаны), «12 гадзін» і «24 гадзіны». Першы варыянт адпавядае мове, "
    L"ручны выбар захоўваецца пасля яе змены. Раздзяляльнікі і пазначэнні часу адпавядаюць мове "
    L"віджэта. AM/PM спачатку ўключаны і кіруе толькі пазначэннем у 12-гадзінным рэжыме; калі "
    L"мова не мае ўласнага пазначэння, ужываецца AM/PM. Гадзіннікі на маніторы паказваюць яго "
    L"асобным радком пад часам. UTC заўсёды выкарыстоўвае 24-гадзінны фармат. Іменаваныя паясы "
    L"ўлічваюць мясцовы і летні час; зрушэнне каля назвы адпавядае бягучай даце. Асобныя пункты "
    L"UTC задаюць пастаянныя зрушэнні ад -12:00 да +14:00 з крокам 15 хвілін без летняга часу.",
    L"\r\n\r\nФормат на часа и часови зони\r\n„Формат на часа“ в раздела „Общи“ предлага „Според "
    L"езика“ (по подразбиране), „12 часа“ и „24 часа“. Първата опция следва езика; ръчният избор "
    L"се запазва след смяната му. Разделителите и означенията следват езика на модула. AM/PM е "
    L"включено по подразбиране и управлява само означението в 12-часов режим; ако езикът няма "
    L"свое означение, се използва AM/PM. Часовниците на монитор го показват на отделен ред под "
    L"часа. UTC винаги използва 24-часов формат. Именуваните зони следват местното време и "
    L"лятното часово време; отместването до името е за текущата дата. Отделните записи UTC са "
    L"постоянни отмествания от -12:00 до +14:00 на стъпки от 15 минути без лятно часово време.",
    L"\r\n\r\nОблик на времето и временски зони\r\n„Облик на времето“ во „Општо“ нуди „Според "
    L"јазикот“ (стандардно), „12 часа“ и „24 часа“. Првата опција го следи јазикот, а рачниот "
    L"избор останува по неговата промена. Разделувачите и ознаките го следат јазикот на виџетот. "
    L"AM/PM е стандардно вклучено и ја менува само ознаката во 12-часовен режим; ако јазикот нема "
    L"свои ознаки, се користи AM/PM. Часовниците на монитор ја покажуваат во одделен ред под "
    L"времето. UTC секогаш користи 24-часовен облик. Именуваните зони го следат локалното и "
    L"летното сметање на времето; поместувањето до името важи за тековниот датум. Одделните "
    L"ставки UTC се постојани поместувања од -12:00 до +14:00 во чекори од 15 минути без летно "
    L"сметање на времето.",
    L"\r\n\r\nОблик времена и временске зоне\r\nОблик времена на картици Опште нуди Према језику "
    L"(подразумевано), 12 сати и 24 сата. Прва опција прати језик, а ручни избор остаје након "
    L"његове промене. Раздвајачи и ознаке времена прате језик виџета. AM/PM је првобитно укључен "
    L"и управља само ознаком у 12-часовном режиму; ако језик нема сопствене ознаке, користи се "
    L"AM/PM. Сатови на монитору приказују ознаку у засебном реду испод времена. UTC увек користи "
    L"24-часовни приказ. Именоване зоне прате локално и летње рачунање времена; помак уз назив "
    L"важи за тренутни датум. Засебне ставке UTC су стални помаци од -12:00 до +14:00 у корацима "
    L"од 15 минута без летњег рачунања времена.",
    L"\r\n\r\nФОРМАТ ЧАСУ ТА ЧАСОВІ ПОЯСИ\r\nПараметр «Формат часу» на вкладці «Загальні» "
    L"пропонує «За мовою» (типове значення), «12 годин» і «24 години». Перший варіант відповідає "
    L"вибраній мові; ручний вибір зберігається після зміни мови віджета. Роздільники та "
    L"позначення часу відповідають мові віджета. Прапорець AM/PM спочатку встановлено; він керує "
    L"лише позначенням у 12-годинному режимі. Якщо мова не має власного позначення, "
    L"використовується AM/PM. Годинники на моніторі показують його окремим рядком під часом. UTC "
    L"завжди використовує 24-годинний формат. Іменовані часові пояси враховують місцевий час і "
    L"перехід на літній час; зсув поряд із назвою відповідає поточній даті. Окремі пункти UTC "
    L"задають фіксовані зсуви від -12:00 до +14:00 із кроком 15 хвилин без переходу на літній час.",
    L"\r\n\r\nФОРМАТ ВРЕМЕНИ И ЧАСОВЫЕ ПОЯСА\r\nПараметр «Формат времени» на вкладке «Общие» "
    L"предлагает «По языку» (по умолчанию), «12 часов» и «24 часа». Первый вариант соответствует "
    L"выбранному языку; ручной выбор сохраняется после смены языка виджета. Разделители и "
    L"обозначения времени соответствуют языку виджета. Флажок AM/PM изначально установлен; он "
    L"управляет только обозначением в 12-часовом режиме. Если у языка нет собственного "
    L"обозначения, используется AM/PM. Часы на мониторе показывают его отдельной строкой под "
    L"временем. UTC всегда использует 24-часовой формат. Именованные часовые пояса учитывают "
    L"местное время и переход на летнее время; смещение рядом с названием соответствует текущей "
    L"дате. Отдельные пункты UTC задают фиксированные смещения от -12:00 до +14:00 с шагом 15 "
    L"минут без перехода на летнее время."
};

const wchar_t* HELP_TIME_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nZDROJ ČASU\r\nNa kartě Čas lze pro celou aplikaci, tedy společně pro všechny "
    L"widgety, vybrat systémový čas Windows nebo čas ze zadaných serverů NTP. NTP koriguje pouze "
    L"čas zobrazovaný v CalClock; systémové hodiny Windows se nikdy nemění. Dokud nebyl získán "
    L"platný údaj, používá se systémový čas. NTP je výchozí. Automatická sada volí podle "
    L"systémové oblasti české a slovenské servery, PTB pro Evropu nebo celosvětový fond. Více "
    L"měření se filtruje podle síťového zpoždění a odlehlých odpovědí. Synchronizovat nyní spustí "
    L"nové měření okamžitě.\r\n\r\nPo synchronizaci hodiny CalClock pokračují nezávisle na "
    L"pozdějších změnách systémového času Windows. Při výpadku spojení nebo změně serverů "
    L"pokračují od poslední platné synchronizace až do získání nové odpovědi; stav se uchovává do "
    L"ukončení aplikace.\r\n\r\nZÁZNAM SYNCHRONIZACE NTP\r\nNa kartě Čas je záznam dotazů na "
    L"servery NTP od spuštění aplikace. Každý záznam obsahuje datum a místní čas počítače, server "
    L"a stav. OK označuje platnou odpověď a θ její odchylku vůči systémovému času Windows. ERR "
    L"uvádí důvod neúspěchu a případný chybový kód. Poslední záznam skupiny obsahuje také "
    L"výslednou odchylku Θ, pokud se podařilo získat použitelná měření.\r\n\r\nOdchylky se "
    L"zobrazují v milisekundách se čtyřmi desetinnými místy. Kladná hodnota znamená, že čas "
    L"serveru je vůči Windows napřed; záporná, že je pozadu. Výsledná odchylka Θ zohledňuje "
    L"přijatá měření a je uvedena také ve stavu synchronizace.\r\n\r\nUložit log uloží záznamy do "
    L"CSV včetně odchylek a důvodů chyb. Záznamy se mezi spuštěními neuchovávají; chcete-li je "
    L"zachovat, uložte je před ukončením aplikace.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP "
    L"servers for the whole application and therefore for all widgets. NTP corrects only the time "
    L"displayed by CalClock; the Windows clock is never changed. System time is used until the "
    L"first valid reply. NTP is the default. The automatic set chooses Czech and Slovak servers, "
    L"PTB for Europe, or the global pool according to the system region. Multiple measurements "
    L"are filtered by network delay and outlying replies. Synchronize now starts a fresh "
    L"measurement immediately.\r\n\r\nAfter synchronization, CalClock keeps time independently of "
    L"later changes to Windows system time. If the connection fails or servers change, it "
    L"continues from the last valid synchronization until a new reply arrives; this state is "
    L"retained until the application closes.\r\n\r\nNTP SYNCHRONIZATION LOG\r\nThe Time tab "
    L"records NTP server queries since the application started. Each entry contains the date and "
    L"local computer time, server, and status. OK identifies a valid reply, with θ showing its "
    L"offset from Windows system time. ERR gives the failure reason and any error code. The final "
    L"entry in a query group also shows the combined offset Θ when usable measurements are "
    L"available.\r\n\r\nOffsets are displayed in milliseconds with four decimal places. A "
    L"positive value means the server clock is ahead of Windows; a negative value means it is "
    L"behind. The combined offset Θ reflects the accepted measurements and is also shown in the "
    L"synchronization status.\r\n\r\nSave log exports the records to CSV, including offsets and "
    L"failure details. Records are not retained between application sessions; save them before "
    L"exiting if you want to keep them.",
    L"\r\n\r\nZEITQUELLE\r\nAuf der Registerkarte Zeit wird für die gesamte Anwendung und damit "
    L"für alle Widgets die Windows-Systemzeit oder die Zeit der eingestellten NTP-Server gewählt. "
    L"NTP korrigiert nur die in CalClock angezeigte Zeit; die Windows-Uhr wird nie geändert. Bis "
    L"zur ersten gültigen Antwort wird die Systemzeit verwendet. NTP ist voreingestellt. Die "
    L"automatische Gruppe wählt nach der Systemregion die tschechisch-slowakischen Server, PTB "
    L"für Europa oder den globalen Pool. Mehrere Messungen werden nach Netzverzögerung und "
    L"Ausreißern gefiltert. Jetzt synchronisieren startet sofort eine neue Messung.\r\n\r\nNach "
    L"der Synchronisierung läuft die CalClock-Uhr unabhängig von späteren Änderungen der "
    L"Windows-Systemzeit weiter. Bei einem Verbindungsausfall oder Serverwechsel läuft sie ab der "
    L"letzten gültigen Synchronisierung weiter, bis eine neue Antwort vorliegt; dieser Zustand "
    L"bleibt bis zum Beenden der Anwendung erhalten.\r\n\r\nNTP-SYNCHRONISIERUNGSPROTOKOLL\r\nDie "
    L"Registerkarte Zeit protokolliert NTP-Serverabfragen seit dem Programmstart. Jeder Eintrag "
    L"enthält Datum und lokale Computerzeit, Server und Status. OK bezeichnet eine gültige "
    L"Antwort; θ zeigt deren Abweichung von der Windows-Systemzeit. ERR nennt den Fehlergrund und "
    L"gegebenenfalls einen Fehlercode. Der letzte Eintrag einer Abfragegruppe enthält auch die "
    L"berechnete Abweichung Θ, sofern verwertbare Messungen vorliegen.\r\n\r\nAbweichungen werden "
    L"in Millisekunden mit vier Nachkommastellen angezeigt. Ein positiver Wert bedeutet, dass die "
    L"Serveruhr Windows voraus ist; ein negativer Wert bedeutet, dass sie nachgeht. Θ "
    L"berücksichtigt die angenommenen Messungen und wird auch im Synchronisierungsstatus "
    L"angezeigt.\r\n\r\nProtokoll speichern exportiert die Einträge einschließlich Abweichungen "
    L"und Fehlerdetails als CSV. Einträge werden nicht über Programmstarts hinweg aufbewahrt; "
    L"speichern Sie sie vor dem Beenden, wenn Sie sie behalten möchten.",
    L"\r\n\r\nSOURCE DE L’HEURE\r\nL’onglet Heure sélectionne l’heure système Windows ou les "
    L"serveurs NTP configurés pour toute l’application, donc pour tous les widgets. NTP corrige "
    L"uniquement l’heure affichée par CalClock ; l’horloge Windows n’est jamais modifiée. L’heure "
    L"système est utilisée jusqu’à la première réponse valide. NTP est la valeur par défaut. Le "
    L"jeu automatique choisit les serveurs tchèques et slovaques, PTB pour l’Europe ou le pool "
    L"mondial selon la région système. Plusieurs mesures sont filtrées selon le délai réseau et "
    L"les réponses aberrantes. Synchroniser maintenant lance immédiatement une nouvelle "
    L"mesure.\r\n\r\nAprès la synchronisation, l’horloge de CalClock continue de fonctionner "
    L"indépendamment des modifications ultérieures de l’heure système Windows. Si la connexion "
    L"est perdue ou si les serveurs changent, elle continue à partir de la dernière "
    L"synchronisation valide jusqu’à une nouvelle réponse ; cet état est conservé jusqu’à la "
    L"fermeture de l’application.\r\n\r\nJOURNAL DE SYNCHRONISATION NTP\r\nL’onglet Heure "
    L"conserve les requêtes aux serveurs NTP depuis le lancement de l’application. Chaque entrée "
    L"indique la date et l’heure locale de l’ordinateur, le serveur et l’état. OK signale une "
    L"réponse valide et θ son décalage par rapport à l’heure système Windows. ERR indique la "
    L"cause de l’échec et, le cas échéant, un code d’erreur. La dernière entrée d’un groupe de "
    L"requêtes indique aussi le décalage calculé Θ lorsque des mesures exploitables sont "
    L"disponibles.\r\n\r\nLes décalages sont exprimés en millisecondes avec quatre décimales. Une "
    L"valeur positive signifie que l’horloge du serveur est en avance sur Windows ; une valeur "
    L"négative signifie qu’elle est en retard. Θ tient compte des mesures acceptées et apparaît "
    L"aussi dans l’état de synchronisation.\r\n\r\nEnregistrer le journal exporte les entrées en "
    L"CSV, avec les décalages et les détails des erreurs. Les entrées ne sont pas conservées "
    L"entre les sessions ; enregistrez-les avant de quitter pour les garder.",
    L"\r\n\r\nORIGEN DE HORA\r\nLa pestaña Hora selecciona la hora del sistema Windows o los "
    L"servidores NTP configurados para toda la aplicación y, por tanto, para todos los widgets. "
    L"NTP solo corrige la hora mostrada por CalClock; el reloj de Windows nunca se modifica. Se "
    L"usa la hora del sistema hasta la primera respuesta válida. NTP es el valor predeterminado. "
    L"El conjunto automático elige servidores checos y eslovacos, PTB para Europa o el grupo "
    L"mundial según la región del sistema. Varias mediciones se filtran por retardo de red y "
    L"respuestas atípicas. Sincronizar ahora inicia una medición nueva de inmediato.\r\n\r\nTras "
    L"la sincronización, el reloj de CalClock sigue funcionando independientemente de los cambios "
    L"posteriores en la hora del sistema Windows. Si falla la conexión o se cambian los "
    L"servidores, continúa desde la última sincronización válida hasta recibir una nueva "
    L"respuesta; este estado se conserva hasta que se cierra la aplicación.\r\n\r\nREGISTRO DE "
    L"SINCRONIZACIÓN NTP\r\nLa pestaña Hora registra las consultas a servidores NTP desde el "
    L"inicio de la aplicación. Cada entrada contiene la fecha y hora local del equipo, el "
    L"servidor y el estado. OK identifica una respuesta válida y θ su desfase respecto a la hora "
    L"del sistema Windows. ERR indica el motivo del fallo y, si existe, su código. La última "
    L"entrada de cada grupo de consultas también muestra el desfase calculado Θ cuando hay "
    L"mediciones utilizables.\r\n\r\nLos desfases se muestran en milisegundos con cuatro "
    L"decimales. Un valor positivo indica que el reloj del servidor está adelantado respecto a "
    L"Windows; uno negativo indica que está atrasado. Θ refleja las mediciones aceptadas y "
    L"también aparece en el estado de sincronización.\r\n\r\nGuardar registro exporta las "
    L"entradas a CSV, incluidos los desfases y los detalles de los errores. Las entradas no se "
    L"conservan entre sesiones; guárdelas antes de salir si desea conservarlas.",
    L"\r\n\r\nORIGINE DELL’ORA\r\nLa scheda Ora seleziona l’ora di sistema Windows o i server NTP "
    L"configurati per l’intera applicazione e quindi per tutti i widget. NTP corregge solo l’ora "
    L"visualizzata da CalClock; l’orologio di Windows non viene mai modificato. L’ora di sistema "
    L"viene usata fino alla prima risposta valida. NTP è l’impostazione predefinita. Il gruppo "
    L"automatico sceglie i server cechi e slovacchi, PTB per l’Europa o il pool globale in base "
    L"all’area di sistema. Più misurazioni vengono filtrate in base al ritardo di rete e alle "
    L"risposte anomale. Sincronizza ora avvia subito una nuova misurazione.\r\n\r\nDopo la "
    L"sincronizzazione, l’orologio di CalClock continua a funzionare indipendentemente dalle "
    L"successive modifiche all’ora di sistema Windows. Se la connessione si interrompe o si "
    L"cambiano i server, continua dall’ultima sincronizzazione valida fino a una nuova risposta; "
    L"questo stato viene mantenuto fino alla chiusura dell’applicazione.\r\n\r\nREGISTRO DI "
    L"SINCRONIZZAZIONE NTP\r\nLa scheda Ora registra le richieste ai server NTP dall’avvio "
    L"dell’applicazione. Ogni voce contiene data e ora locale del computer, server e stato. OK "
    L"indica una risposta valida e θ il suo scostamento dall’ora di sistema Windows. ERR indica "
    L"il motivo dell’errore e l’eventuale codice. L’ultima voce di un gruppo di richieste mostra "
    L"anche lo scostamento calcolato Θ quando sono disponibili misurazioni "
    L"utilizzabili.\r\n\r\nGli scostamenti sono espressi in millisecondi con quattro cifre "
    L"decimali. Un valore positivo indica che l’orologio del server è avanti rispetto a Windows; "
    L"un valore negativo indica che è indietro. Θ tiene conto delle misurazioni accettate ed è "
    L"mostrato anche nello stato di sincronizzazione.\r\n\r\nSalva registro esporta le voci in "
    L"CSV, compresi scostamenti e dettagli degli errori. Le voci non vengono conservate tra le "
    L"sessioni; salvarle prima di uscire se si desidera mantenerle.",
    L"\r\n\r\nŹRÓDŁO CZASU\r\nKarta Czas wybiera dla całej aplikacji, a więc dla wszystkich "
    L"widżetów, czas systemowy Windows albo skonfigurowane serwery NTP. NTP koryguje wyłącznie "
    L"czas wyświetlany przez CalClock; zegar Windows nigdy nie jest zmieniany. Do pierwszej "
    L"prawidłowej odpowiedzi używany jest czas systemowy. NTP jest ustawieniem domyślnym. Zestaw "
    L"automatyczny wybiera według regionu systemu serwery czeskie i słowackie, PTB dla Europy "
    L"albo pulę globalną. Wiele pomiarów jest filtrowanych według opóźnienia sieci i wartości "
    L"odstających. Synchronizuj teraz natychmiast rozpoczyna nowy pomiar.\r\n\r\nPo "
    L"synchronizacji zegar CalClock odmierza czas niezależnie od późniejszych zmian czasu "
    L"systemowego Windows. Po utracie połączenia lub zmianie serwerów kontynuuje odmierzanie od "
    L"ostatniej prawidłowej synchronizacji do uzyskania nowej odpowiedzi; stan ten jest "
    L"zachowywany do zamknięcia aplikacji.\r\n\r\nDZIENNIK SYNCHRONIZACJI NTP\r\nKarta Czas "
    L"rejestruje zapytania do serwerów NTP od uruchomienia aplikacji. Każdy wpis zawiera datę i "
    L"lokalny czas komputera, serwer oraz stan. OK oznacza prawidłową odpowiedź, a θ jej "
    L"odchylenie od czasu systemowego Windows. ERR podaje przyczynę niepowodzenia i ewentualny "
    L"kod błędu. Ostatni wpis grupy zapytań zawiera również obliczone odchylenie Θ, jeśli "
    L"dostępne są użyteczne pomiary.\r\n\r\nOdchylenia są wyświetlane w milisekundach z czterema "
    L"miejscami po przecinku. Wartość dodatnia oznacza, że zegar serwera wyprzedza Windows; "
    L"ujemna oznacza, że jest opóźniony. Θ uwzględnia zaakceptowane pomiary i jest również "
    L"widoczne w stanie synchronizacji.\r\n\r\nZapisz dziennik eksportuje wpisy do CSV wraz z "
    L"odchyleniami i szczegółami błędów. Wpisy nie są zachowywane między uruchomieniami; zapisz "
    L"je przed zamknięciem aplikacji, jeśli chcesz je zachować.",
    L"\r\n\r\nZDROJ ČASU\r\nNa karte Čas možno pre celú aplikáciu, teda spoločne pre všetky "
    L"widgety, vybrať systémový čas Windows alebo čas zo zadaných serverov NTP. NTP koriguje iba "
    L"čas zobrazený v CalClock; systémové hodiny Windows sa nikdy nemenia. Do prvej platnej "
    L"odpovede sa používa systémový čas. NTP je predvolené. Automatická sada vyberie podľa "
    L"systémovej oblasti české a slovenské servery, PTB pre Európu alebo celosvetový fond. "
    L"Viaceré merania sa filtrujú podľa sieťového oneskorenia a odľahlých odpovedí. "
    L"Synchronizovať teraz spustí nové meranie ihneď.\r\n\r\nPo synchronizácii hodiny CalClock "
    L"pokračujú nezávisle od neskorších zmien systémového času Windows. Pri výpadku spojenia "
    L"alebo zmene serverov pokračujú od poslednej platnej synchronizácie až do získania novej "
    L"odpovede; stav sa uchováva do ukončenia aplikácie.\r\n\r\nZÁZNAM SYNCHRONIZÁCIE NTP\r\nNa "
    L"karte Čas je záznam dotazov na servery NTP od spustenia aplikácie. Každý záznam obsahuje "
    L"dátum a miestny čas počítača, server a stav. OK označuje platnú odpoveď a θ jej odchýlku "
    L"voči systémovému času Windows. ERR uvádza dôvod neúspechu a prípadný chybový kód. Posledný "
    L"záznam skupiny obsahuje aj výslednú odchýlku Θ, ak sa podarilo získať použiteľné "
    L"merania.\r\n\r\nOdchýlky sa zobrazujú v milisekundách so štyrmi desatinnými miestami. "
    L"Kladná hodnota znamená, že čas servera je voči Windows vpred; záporná, že zaostáva. "
    L"Výsledná odchýlka Θ zohľadňuje prijaté merania a je uvedená aj v stave "
    L"synchronizácie.\r\n\r\nUložiť log uloží záznamy do CSV vrátane odchýlok a dôvodov chýb. "
    L"Záznamy sa medzi spusteniami neuchovávajú; ak ich chcete zachovať, uložte ich pred "
    L"ukončením aplikácie.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP "
    L"servers for the whole application and therefore for all widgets. NTP corrects only the time "
    L"displayed by CalClock; the Windows clock is never changed. System time is used until the "
    L"first valid reply. NTP is the default. The automatic set chooses Czech and Slovak servers, "
    L"PTB for Europe, or the global pool according to the system region. Multiple measurements "
    L"are filtered by network delay and outlying replies. Synchronise now starts a fresh "
    L"measurement immediately.\r\n\r\nAfter synchronisation, CalClock keeps time independently of "
    L"later changes to Windows system time. If the connection fails or servers change, it "
    L"continues from the last valid synchronisation until a new reply arrives; this state is "
    L"retained until the application closes.\r\n\r\nNTP SYNCHRONIZATION LOG\r\nThe Time tab "
    L"records NTP server queries since the application started. Each entry contains the date and "
    L"local computer time, server, and status. OK identifies a valid reply, with θ showing its "
    L"offset from Windows system time. ERR gives the failure reason and any error code. The final "
    L"entry in a query group also shows the combined offset Θ when usable measurements are "
    L"available.\r\n\r\nOffsets are displayed in milliseconds with four decimal places. A "
    L"positive value means the server clock is ahead of Windows; a negative value means it is "
    L"behind. The combined offset Θ reflects the accepted measurements and is also shown in the "
    L"synchronisation status.\r\n\r\nSave log exports the records to CSV, including offsets and "
    L"failure details. Records are not retained between application sessions; save them before "
    L"exiting if you want to keep them.",
    L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the configured NTP "
    L"servers for the whole application and therefore for all widgets. NTP corrects only the time "
    L"displayed by CalClock; the Windows clock is never changed. System time is used until the "
    L"first valid reply. NTP is the default. The automatic set chooses Czech and Slovak servers, "
    L"PTB for Europe, or the global pool according to the system region. Multiple measurements "
    L"are filtered by network delay and outlying replies. Synchronise now starts a fresh "
    L"measurement immediately.\r\n\r\nAfter synchronisation, CalClock keeps time independently of "
    L"later changes to Windows system time. If the connection fails or servers change, it "
    L"continues from the last valid synchronisation until a new reply arrives; this state is "
    L"retained until the application closes.\r\n\r\nNTP SYNCHRONIZATION LOG\r\nThe Time tab "
    L"records NTP server queries since the application started. Each entry contains the date and "
    L"local computer time, server, and status. OK identifies a valid reply, with θ showing its "
    L"offset from Windows system time. ERR gives the failure reason and any error code. The final "
    L"entry in a query group also shows the combined offset Θ when usable measurements are "
    L"available.\r\n\r\nOffsets are displayed in milliseconds with four decimal places. A "
    L"positive value means the server clock is ahead of Windows; a negative value means it is "
    L"behind. The combined offset Θ reflects the accepted measurements and is also shown in the "
    L"synchronisation status.\r\n\r\nSave log exports the records to CSV, including offsets and "
    L"failure details. Records are not retained between application sessions; save them before "
    L"exiting if you want to keep them.",
    L"\r\n\r\nORIGEM DA HORA\r\nO separador Hora escolhe para toda a aplicação a hora do Windows "
    L"ou servidores NTP. O NTP corrige apenas o CalClock e nunca altera o Windows. A predefinição "
    L"é NTP; o conjunto automático escolhe servidores pela região e filtra medições por atraso e "
    L"valores atípicos.\r\n\r\nApós a sincronização, o relógio do CalClock continua a funcionar "
    L"independentemente de alterações posteriores à hora do sistema Windows. Se a ligação falhar "
    L"ou os servidores forem alterados, continua a partir da última sincronização válida até "
    L"receber uma nova resposta; este estado mantém-se até fechar a aplicação.\r\n\r\nREGISTO DE "
    L"SINCRONIZAÇÃO NTP\r\nO separador Hora regista as consultas a servidores NTP desde o início "
    L"da aplicação. Cada entrada contém a data e hora local do computador, o servidor e o estado. "
    L"OK identifica uma resposta válida e θ o seu desvio em relação à hora do Windows. ERR indica "
    L"a causa da falha e o eventual código de erro. A última entrada de um grupo de consultas "
    L"mostra também o desvio calculado Θ quando existem medições utilizáveis.\r\n\r\nOs desvios "
    L"são apresentados em milissegundos com quatro casas decimais. Um valor positivo significa "
    L"que o relógio do servidor está adiantado em relação ao Windows; um valor negativo significa "
    L"que está atrasado. Θ reflete as medições aceites e também aparece no estado da "
    L"sincronização.\r\n\r\nGuardar registo exporta as entradas para CSV, incluindo desvios e "
    L"detalhes das falhas. As entradas não são conservadas entre sessões; guarde-as antes de sair "
    L"se quiser mantê-las.",
    L"\r\n\r\nTIDSKILDE\r\nFanen Tid velger Windows-tid eller NTP-servere for hele programmet. "
    L"NTP korrigerer bare CalClock og endrer aldri Windows. NTP er standard; det automatiske "
    L"settet velger servere etter region og filtrerer målinger etter forsinkelse og "
    L"avvik.\r\n\r\nEtter synkronisering går CalClock-klokken videre uavhengig av senere "
    L"endringer i systemtiden i Windows. Hvis forbindelsen brytes eller serverne endres, "
    L"fortsetter klokken fra siste gyldige synkronisering til et nytt svar mottas; denne "
    L"tilstanden beholdes til programmet avsluttes.\r\n\r\nNTP-SYNKRONISERINGSLOGG\r\nFanen Tid "
    L"registrerer NTP-serverforespørsler siden programmet startet. Hver oppføring inneholder dato "
    L"og lokal datamaskintid, server og status. OK angir et gyldig svar, og θ viser tidsavviket "
    L"fra Windows-systemtiden. ERR angir årsaken til feilen og en eventuell feilkode. Den siste "
    L"oppføringen i en forespørselsgruppe viser også det beregnede tidsavviket Θ når brukbare "
    L"målinger er tilgjengelige.\r\n\r\nTidsavvik vises i millisekunder med fire desimaler. En "
    L"positiv verdi betyr at serverklokken går foran Windows; en negativ verdi betyr at den går "
    L"etter. Θ tar hensyn til de godkjente målingene og vises også i "
    L"synkroniseringsstatusen.\r\n\r\nLagre logg eksporterer oppføringene til CSV, inkludert "
    L"tidsavvik og feildetaljer. Oppføringer beholdes ikke mellom programøkter; lagre dem før du "
    L"avslutter hvis du vil beholde dem.",
    L"\r\n\r\nTIDSKÄLLA\r\nFliken Tid väljer Windows-tid eller NTP-servrar för hela programmet. "
    L"NTP korrigerar bara CalClock och ändrar aldrig Windows. NTP är standard; den automatiska "
    L"uppsättningen väljer servrar efter region och filtrerar mätningar efter fördröjning och "
    L"avvikelse.\r\n\r\nEfter synkronisering går CalClock-klockan vidare oberoende av senare "
    L"ändringar av systemtiden i Windows. Om anslutningen bryts eller servrarna ändras fortsätter "
    L"klockan från den senaste giltiga synkroniseringen tills ett nytt svar kommer; detta "
    L"tillstånd behålls tills programmet stängs.\r\n\r\nNTP-SYNKRONISERINGSLOGG\r\nFliken Tid "
    L"registrerar NTP-serverförfrågningar sedan programmet startades. Varje post innehåller datum "
    L"och datorns lokala tid, server och status. OK anger ett giltigt svar och θ dess "
    L"tidsavvikelse från Windows-systemtiden. ERR anger felorsaken och en eventuell felkod. Den "
    L"sista posten i en grupp förfrågningar visar även den beräknade tidsavvikelsen Θ när "
    L"användbara mätningar finns.\r\n\r\nTidsavvikelser visas i millisekunder med fyra decimaler. "
    L"Ett positivt värde betyder att serverklockan går före Windows; ett negativt värde betyder "
    L"att den går efter. Θ tar hänsyn till de godkända mätningarna och visas även i "
    L"synkroniseringsstatusen.\r\n\r\nSpara logg exporterar posterna till CSV, inklusive "
    L"tidsavvikelser och feldetaljer. Poster sparas inte mellan programstarter; spara dem innan "
    L"du avslutar om du vill behålla dem.",
    L"\r\n\r\nAIKALÄHDE\r\nAika-välilehdellä valitaan koko sovellukselle Windowsin aika tai "
    L"NTP-palvelimet. NTP korjaa vain CalClockia eikä muuta Windowsia. NTP on oletus; "
    L"automaattinen joukko valitsee palvelimet alueen mukaan ja suodattaa mittaukset viiveen ja "
    L"poikkeamien perusteella.\r\n\r\nSynkronoinnin jälkeen CalClockin kello käy riippumatta "
    L"myöhemmistä Windowsin järjestelmäajan muutoksista. Jos yhteys katkeaa tai palvelimia "
    L"vaihdetaan, kello jatkaa viimeisestä kelvollisesta synkronoinnista uuteen vastaukseen asti; "
    L"tämä tila säilyy sovelluksen sulkemiseen "
    L"saakka.\r\n\r\nNTP-SYNKRONOINTILOKI\r\nAika-välilehti tallentaa NTP-palvelinkyselyt "
    L"sovelluksen käynnistämisestä alkaen. Jokainen merkintä sisältää päivämäärän ja tietokoneen "
    L"paikallisen ajan, palvelimen sekä tilan. OK tarkoittaa kelvollista vastausta, ja θ ilmaisee "
    L"sen aikaeron Windowsin järjestelmäaikaan. ERR kertoo epäonnistumisen syyn ja mahdollisen "
    L"virhekoodin. Kyselyryhmän viimeinen merkintä näyttää myös lasketun aikaeron Θ, jos "
    L"käytettävissä on käyttökelpoisia mittauksia.\r\n\r\nAikaerot näytetään millisekunteina "
    L"neljällä desimaalilla. Positiivinen arvo tarkoittaa, että palvelimen kello on Windowsia "
    L"edellä; negatiivinen arvo tarkoittaa, että se on jäljessä. Θ perustuu hyväksyttyihin "
    L"mittauksiin ja näkyy myös synkronoinnin tilassa.\r\n\r\nTallenna loki vie merkinnät "
    L"CSV-tiedostoon, mukaan lukien aikaerot ja virhetiedot. Merkintöjä ei säilytetä "
    L"käynnistyskertojen välillä; tallenna ne ennen sulkemista, jos haluat säilyttää ne.",
    L"\r\n\r\nTIDSKILDE\r\nFanen Tid vælger Windows-tid eller NTP-servere for hele programmet. "
    L"NTP korrigerer kun CalClock og ændrer aldrig Windows. NTP er standard; det automatiske sæt "
    L"vælger servere efter område og filtrerer målinger efter forsinkelse og "
    L"afvigelser.\r\n\r\nEfter synkronisering går CalClock-uret videre uafhængigt af senere "
    L"ændringer af systemtiden i Windows. Hvis forbindelsen afbrydes, eller serverne ændres, "
    L"fortsætter uret fra den seneste gyldige synkronisering, indtil et nyt svar modtages; denne "
    L"tilstand bevares, indtil programmet lukkes.\r\n\r\nNTP-SYNKRONISERINGSLOG\r\nFanen Tid "
    L"registrerer NTP-serverforespørgsler siden programmets start. Hver post indeholder dato og "
    L"computerens lokale tid, server og status. OK angiver et gyldigt svar, og θ viser "
    L"tidsafvigelsen fra Windows-systemtiden. ERR angiver fejlårsagen og en eventuel fejlkode. "
    L"Den sidste post i en forespørgselsgruppe viser også den beregnede tidsafvigelse Θ, når "
    L"brugbare målinger er tilgængelige.\r\n\r\nTidsafvigelser vises i millisekunder med fire "
    L"decimaler. En positiv værdi betyder, at serveruret går foran Windows; en negativ værdi "
    L"betyder, at det går bagefter. Θ tager hensyn til de godkendte målinger og vises også i "
    L"synkroniseringsstatussen.\r\n\r\nGem log eksporterer posterne til CSV, inklusive "
    L"tidsafvigelser og fejloplysninger. Poster beholdes ikke mellem programstarter; gem dem før "
    L"afslutning, hvis du vil beholde dem.",
    L"\r\n\r\nTÍMAGJAFI\r\nTímaflipinn velur Windows-tíma eða NTP-þjóna fyrir allt forritið. NTP "
    L"leiðréttir aðeins CalClock og breytir aldrei Windows. NTP er sjálfgefið; sjálfvirka safnið "
    L"velur þjóna eftir svæði og síar mælingar eftir töf og frávikum.\r\n\r\nEftir samstillingu "
    L"gengur klukka CalClock áfram óháð síðari breytingum á kerfistíma Windows. Ef samband rofnar "
    L"eða skipt er um þjóna heldur klukkan áfram frá síðustu gildu samstillingu þar til nýtt svar "
    L"berst; þetta ástand helst þar til forritinu er "
    L"lokað.\r\n\r\nNTP-SAMSTILLINGARSKRÁ\r\nTímaflipinn skráir fyrirspurnir til NTP-þjóna frá "
    L"ræsingu forritsins. Hver færsla inniheldur dagsetningu og staðartíma tölvunnar, þjón og "
    L"stöðu. OK merkir gilt svar og θ tímamun þess frá kerfistíma Windows. ERR sýnir ástæðu "
    L"bilunar og villukóða ef við á. Síðasta færsla í hópi fyrirspurna sýnir einnig reiknaðan "
    L"tímamun Θ þegar nothæfar mælingar liggja fyrir.\r\n\r\nTímamunur er sýndur í millisekúndum "
    L"með fjórum aukastöfum. Jákvætt gildi merkir að klukka þjónsins er á undan Windows; neikvætt "
    L"gildi merkir að hún er á eftir. Θ tekur mið af samþykktum mælingum og birtist einnig í "
    L"samstillingarstöðu.\r\n\r\nVista annál flytur færslur út sem CSV, með tímamun og "
    L"villuupplýsingum. Færslur varðveitast ekki milli keyrslna; vistaðu þær áður en þú lokar "
    L"forritinu ef þú vilt geyma þær.",
    L"\r\n\r\nZAMAN KAYNAĞI\r\nZaman sekmesi tüm uygulama için Windows zamanını veya NTP "
    L"sunucularını seçer. NTP yalnızca CalClock'u düzeltir ve Windows'u hiçbir zaman değiştirmez. "
    L"NTP varsayılandır; otomatik küme bölgeye göre sunucu seçer ve ölçümleri gecikme ile aykırı "
    L"değerlere göre süzer.\r\n\r\nEşitlemeden sonra CalClock saati, Windows sistem saatinde daha "
    L"sonra yapılan değişikliklerden bağımsız olarak ilerler. Bağlantı kesilirse veya sunucular "
    L"değiştirilirse yeni bir yanıt alınana kadar son geçerli eşitlemeden itibaren ilerlemeye "
    L"devam eder; bu durum uygulama kapatılana kadar korunur.\r\n\r\nNTP EŞİTLEME "
    L"GÜNLÜĞÜ\r\nZaman sekmesi, uygulama başlatıldığından beri NTP sunucu sorgularını kaydeder. "
    L"Her kayıt tarih ve bilgisayarın yerel saatini, sunucuyu ve durumu içerir. OK geçerli bir "
    L"yanıtı, θ ise bu yanıtın Windows sistem saatinden farkını gösterir. ERR başarısızlığın "
    L"nedenini ve varsa hata kodunu belirtir. Kullanılabilir ölçümler varsa sorgu grubunun son "
    L"kaydı hesaplanan zaman farkını Θ olarak da gösterir.\r\n\r\nZaman farkları milisaniye "
    L"cinsinden dört ondalık basamakla gösterilir. Pozitif değer sunucu saatinin Windows’tan "
    L"ileride, negatif değer geride olduğunu belirtir. Θ kabul edilen ölçümleri yansıtır ve "
    L"eşitleme durumunda da gösterilir.\r\n\r\nGünlüğü kaydet, zaman farkları ve hata ayrıntıları "
    L"dahil kayıtları CSV’ye aktarır. Kayıtlar uygulama oturumları arasında korunmaz; saklamak "
    L"istiyorsanız uygulamadan çıkmadan önce kaydedin.",
    L"\r\n\r\nAja allikas ja NTP-logi\r\nVahekaart Aeg valib Windowsi süsteemiaja või "
    L"NTP-serverid kogu rakendusele. NTP muudab ainult CalClocki aega; Windowsi kella ei muudeta. "
    L"Esimese sobiva vastuseni kasutatakse süsteemiaega. NTP on vaikevalik. Automaatrühm valib "
    L"süsteemi piirkonna järgi Tšehhi ja Slovakkia serverid, Euroopa jaoks PTB või ülemaailmse "
    L"rühma. Mõõtmisi filtreeritakse võrgulatentsuse ja teistest vastustest kõrvalekallete järgi. "
    L"Sünkrooni kohe alustab uut mõõtmist.\r\n\r\nPärast sünkroonimist käib CalClocki kell "
    L"sõltumata Windowsi süsteemiaja hilisematest muutustest. Ühenduse kadumisel või serverite "
    L"vahetamisel jätkab kell viimasest sobivast sünkroonimisest uue vastuseni; olek säilib "
    L"rakenduse sulgemiseni.\r\n\r\nVahekaart Aeg logib NTP-päringud käivitamisest alates. Kirje "
    L"sisaldab kuupäeva, arvuti kohalikku aega, serverit ja olekut. OK näitab sobivat vastust ja "
    L"θ selle nihet Windowsi süsteemiajast. ERR annab põhjuse ja võimaliku veakoodi. Päringurühma "
    L"viimane kirje näitab ka ühendatud nihet Θ, kui on kasutatavaid mõõtmisi. Nihked on "
    L"millisekundites nelja kümnendkohaga: positiivne tähendab serveri edestamist ja negatiivne "
    L"mahajäämist. Θ põhineb vastu võetud mõõtmistel ja ilmub ka sünkroonimisolekus. Salvesta "
    L"logi ekspordib CSV koos nihete ja veateabega. Logi ei säili käivituste vahel; vajaduse "
    L"korral salvestage see enne väljumist.",
    L"\r\n\r\nFoinse ama agus logchomhad NTP\r\nAr an gcluaisín Am, roghnaítear am córais Windows "
    L"nó freastalaithe NTP don fheidhmchlár iomlán. Ní athraíonn NTP ach am CalClock; ní "
    L"athraítear clog Windows. Úsáidtear am an chórais go dtí an chéad fhreagra bailí. Is é NTP "
    L"an réamhshocrú. Roghnaíonn an tacar uathoibríoch freastalaithe Seiceacha agus Slóvacacha, "
    L"PTB don Eoraip nó tacar domhanda de réir réigiún an chórais. Scagtar tomhais de réir moille "
    L"líonra agus diall ó fhreagraí eile. Tosaíonn Sioncronaigh anois tomhas nua "
    L"láithreach.\r\n\r\nTar éis sioncronaithe, coinníonn CalClock an t-am go neamhspleách ar "
    L"athruithe níos déanaí ar am córais Windows. Má chailltear an nasc nó má athraítear "
    L"freastalaithe, leanann sé ón sioncronú bailí deireanach go dtí freagra nua; coinnítear an "
    L"staid go dtí go ndúntar an feidhmchlár.\r\n\r\nLogálann Am iarratais NTP ó thús an "
    L"fheidhmchláir. Tá dáta, am áitiúil an ríomhaire, freastalaí agus stádas sa taifead. "
    L"Ciallaíonn OK freagra bailí agus θ a fhritháireamh ó am Windows; tugann ERR an chúis agus "
    L"aon chód earráide. Taispeánann taifead deiridh grúpa an fritháireamh comhcheangailte Θ "
    L"nuair atá tomhais inúsáidte ann. Tá na fritháirimh i milleasoicindí le ceithre ionad "
    L"dheachúlacha: dearfach má tá an freastalaí chun tosaigh, diúltach má tá sé ar gcúl. "
    L"Bunaítear Θ ar na tomhais ghlactha agus taispeántar sa stádas sioncronaithe é. Easpórtálann "
    L"Sábháil an logchomhad CSV le fritháirimh agus sonraí earráide. Ní choinnítear taifid idir "
    L"seisiúin; sábháil roimh imeacht más gá.",
    L"\r\n\r\nLaiko šaltinis ir NTP žurnalas\r\nSkirtukas Laikas parenka „Windows“ sistemos laiką "
    L"arba NTP serverius visai programai. NTP keičia tik „CalClock“ laiką; „Windows“ laikrodis "
    L"nekeičiamas. Iki pirmo tinkamo atsakymo naudojamas sistemos laikas. NTP yra numatytasis "
    L"pasirinkimas. Automatinis rinkinys pagal sistemos regioną parenka Čekijos ir Slovakijos "
    L"serverius, PTB Europai arba pasaulinį rinkinį. Matavimai filtruojami pagal tinklo delsą ir "
    L"nuokrypį nuo kitų atsakymų. Sinchronizuoti dabar iškart pradeda naują matavimą.\r\n\r\nPo "
    L"sinchronizavimo „CalClock“ laikrodis veikia nepriklausomai nuo vėlesnių „Windows“ sistemos "
    L"laiko pakeitimų. Praradus ryšį ar pakeitus serverius tęsiama nuo paskutinio tinkamo "
    L"sinchronizavimo iki naujo atsakymo; būsena išlaikoma iki programos uždarymo.\r\n\r\nLaikas "
    L"registruoja NTP užklausas nuo programos paleidimo. Įraše yra data, kompiuterio vietinis "
    L"laikas, serveris ir būsena. OK žymi tinkamą atsakymą, θ – jo poslinkį nuo „Windows“ "
    L"sistemos laiko. ERR pateikia priežastį ir galimą klaidos kodą. Paskutinis užklausų grupės "
    L"įrašas rodo bendrą poslinkį Θ, jei yra tinkamų matavimų. Poslinkiai pateikiami "
    L"milisekundėmis su keturiais skaitmenimis po kablelio: teigiamas reiškia, kad serveris "
    L"skuba, neigiamas – atsilieka. Θ pagrįstas priimtais matavimais ir rodomas sinchronizavimo "
    L"būsenoje. Įrašyti žurnalą eksportuoja CSV su poslinkiais ir klaidų informacija. Įrašai tarp "
    L"paleidimų neišlieka; prireikus įrašykite prieš išeidami.",
    L"\r\n\r\nLaika avots un NTP žurnāls\r\nCilne Laiks izvēlas Windows sistēmas laiku vai NTP "
    L"serverus visai programmai. NTP maina tikai CalClock laiku; Windows pulkstenis netiek "
    L"mainīts. Līdz pirmajai derīgajai atbildei izmanto sistēmas laiku. NTP ir noklusējums. "
    L"Automātiskā kopa pēc sistēmas reģiona izvēlas Čehijas un Slovākijas serverus, PTB Eiropai "
    L"vai pasaules kopu. Mērījumus filtrē pēc tīkla aizkaves un novirzēm no citām atbildēm. "
    L"Sinhronizēt tūlīt nekavējoties sāk jaunu mērījumu.\r\n\r\nPēc sinhronizācijas CalClock "
    L"pulkstenis darbojas neatkarīgi no turpmākām Windows sistēmas laika izmaiņām. Zūdot "
    L"savienojumam vai mainot serverus, tas turpina no pēdējās derīgās sinhronizācijas līdz "
    L"jaunai atbildei; stāvoklis paliek līdz programmas aizvēršanai.\r\n\r\nLaiks reģistrē NTP "
    L"vaicājumus kopš palaišanas. Ierakstā ir datums, datora vietējais laiks, serveris un "
    L"statuss. OK nozīmē derīgu atbildi, θ – tās nobīdi no Windows laika. ERR sniedz iemeslu un "
    L"iespējamo kļūdas kodu. Grupas pēdējais ieraksts rāda arī apvienoto nobīdi Θ, ja ir derīgi "
    L"mērījumi. Nobīdes ir milisekundēs ar četrām zīmēm aiz komata: pozitīva vērtība nozīmē, ka "
    L"serveris ir priekšā, negatīva – atpaliek. Θ balstās uz pieņemtajiem mērījumiem un redzama "
    L"arī sinhronizācijas statusā. Saglabāt žurnālu eksportē CSV ar nobīdēm un kļūdu informāciju. "
    L"Ieraksti starp palaišanām nepaliek; saglabājiet pirms iziešanas, ja vajadzīgs.",
    L"\r\n\r\nIdőforrás és NTP-napló\r\nAz Idő fül a Windows rendszeridejét vagy "
    L"NTP-kiszolgálókat választ az egész programhoz. Az NTP csak a CalClock idejét módosítja, a "
    L"Windows óráját soha. Az első érvényes válaszig a rendszeridő használatos. Az NTP az "
    L"alapértelmezett. Az automatikus csoport a rendszer régiója szerint cseh és szlovák "
    L"kiszolgálókat, Európához PTB-t vagy világméretű csoportot választ. A méréseket a hálózati "
    L"késés és a többi választól való eltérés szerint szűri. A Szinkronizálás most azonnal új "
    L"mérést indít.\r\n\r\nSzinkronizálás után a CalClock órája a Windows rendszeridejének "
    L"későbbi változásaitól függetlenül jár. Kapcsolatvesztés vagy kiszolgálóváltás esetén az "
    L"utolsó érvényes szinkronizálástól folytatja az új válaszig; az állapot a program bezárásáig "
    L"marad meg.\r\n\r\nAz Idő fül indítás óta naplózza az NTP-lekérdezéseket. A bejegyzés "
    L"dátumot, helyi gépidőt, kiszolgálót és állapotot tartalmaz. Az OK érvényes válasz, θ az "
    L"eltérés a Windows idejétől. Az ERR az okot és az esetleges hibakódot adja. A csoport utolsó "
    L"bejegyzése az összevont Θ eltolást is mutatja, ha vannak használható mérések. Az eltolás "
    L"milliszekundumban, négy tizedesjeggyel jelenik meg: pozitívnál a kiszolgáló előrébb jár, "
    L"negatívnál késik. A Θ az elfogadott mérésekre épül, és a szinkronizálási állapotban is "
    L"látható. A Napló mentése CSV-be exportálja a bejegyzéseket eltolásokkal és "
    L"hibarészletekkel. A napló nem marad meg két indítás között; kilépés előtt mentse, ha "
    L"szükséges.",
    L"\r\n\r\nSors tal-ħin u reġistru NTP\r\nIt-tab Ħin jagħżel il-ħin tas-sistema Windows jew "
    L"servers NTP għall-programm kollu. NTP jibdel biss il-ħin ta’ CalClock; l-arloġġ tal-Windows "
    L"ma jinbidilx. Jintuża l-ħin tas-sistema sal-ewwel tweġiba valida. NTP huwa d-default. "
    L"Il-grupp awtomatiku jagħżel servers Ċeki u Slovakki, PTB għall-Ewropa jew grupp dinji skont "
    L"ir-reġjun tas-sistema. Il-kejl jiġi ffiltrat skont id-dewmien tan-network u d-differenza "
    L"minn tweġibiet oħra. Issinkronizza issa jibda kejl ġdid minnufih.\r\n\r\nWara "
    L"s-sinkronizzazzjoni, l-arloġġ ta’ CalClock ikompli jaħdem indipendentement minn bidliet "
    L"sussegwenti fil-ħin tas-sistema Windows. Jekk tintilef il-konnessjoni jew jinbidlu "
    L"s-servers, ikompli mill-aħħar sinkronizzazzjoni valida sa tweġiba ġdida; l-istat jibqa’ "
    L"sal-għeluq tal-programm.\r\n\r\nĦin jirreġistra mistoqsijiet NTP mit-tnedija. Ir-rekord fih "
    L"id-data, il-ħin lokali tal-kompjuter, is-server u l-istatus. OK ifisser tweġiba valida; θ "
    L"il-kumpens tagħha mill-ħin tal-Windows. ERR jagħti r-raġuni u kwalunkwe kodiċi tal-iżball. "
    L"L-aħħar rekord ta’ grupp juri wkoll il-kumpens magħqud Θ jekk ikun hemm kejl li jista’ "
    L"jintuża. Il-kumpensi huma f’millisekondi b’erba’ postijiet deċimali: pożittiv ifisser li "
    L"s-server huwa ’l quddiem, negattiv li qiegħed lura. Θ huwa bbażat fuq il-kejl aċċettat u "
    L"jidher ukoll fl-istatus tas-sinkronizzazzjoni. Issejvja r-reġistru jesporta CSV "
    L"bil-kumpensi u d-dettalji tal-iżbalji. Ir-rekords ma jinżammux bejn tnedijiet; issejvjahom "
    L"qabel toħroġ jekk meħtieġ.",
    L"\r\n\r\nTijdbron en NTP-logboek\r\nTijd kiest Windows-systeemtijd of NTP-servers voor de "
    L"hele toepassing. NTP verandert alleen de CalClock-tijd; de Windows-klok wordt nooit "
    L"aangepast. Tot het eerste geldige antwoord wordt de systeemtijd gebruikt. NTP is de "
    L"standaard. De automatische groep kiest volgens de systeemregio Tsjechische en Slowaakse "
    L"servers, PTB voor Europa of een wereldwijde groep. Metingen worden gefilterd op "
    L"netwerkvertraging en afwijkingen van andere antwoorden. Nu synchroniseren start direct een "
    L"nieuwe meting.\r\n\r\nNa synchronisatie loopt de CalClock-klok door, onafhankelijk van "
    L"latere wijzigingen van de Windows-systeemtijd. Bij verbindingsverlies of andere servers "
    L"loopt deze door vanaf de laatste geldige synchronisatie tot een nieuw antwoord; de toestand "
    L"blijft behouden tot de toepassing sluit.\r\n\r\nTijd registreert NTP-aanvragen sinds de "
    L"start. Een record bevat de datum, lokale computertijd, server en status. OK is een geldig "
    L"antwoord, θ de afwijking van Windows-systeemtijd. ERR geeft de oorzaak en eventuele "
    L"foutcode. Het laatste record van een groep toont de gecombineerde afwijking Θ als bruikbare "
    L"metingen bestaan. Afwijkingen zijn in milliseconden met vier decimalen: positief betekent "
    L"dat de server voorloopt, negatief dat deze achterloopt. Θ is gebaseerd op geaccepteerde "
    L"metingen en staat ook in de synchronisatiestatus. Logboek opslaan exporteert CSV met "
    L"afwijkingen en foutdetails. Records worden niet tussen sessies bewaard; sla ze zo nodig "
    L"vóór afsluiten op.",
    L"\r\n\r\nSursa de timp și jurnalul NTP\r\nOră alege ora sistemului Windows sau servere NTP "
    L"pentru întreaga aplicație. NTP modifică numai ora CalClock; ceasul Windows nu se schimbă. "
    L"Până la primul răspuns valid se folosește ora sistemului. NTP este implicit. Grupul automat "
    L"alege după regiunea sistemului servere cehe și slovace, PTB pentru Europa sau un grup "
    L"mondial. Măsurătorile sunt filtrate după întârzierea rețelei și abaterile față de alte "
    L"răspunsuri. Sincronizare acum începe imediat o măsurătoare nouă.\r\n\r\nDupă sincronizare, "
    L"ceasul CalClock funcționează independent de modificările ulterioare ale orei sistemului "
    L"Windows. La pierderea conexiunii sau schimbarea serverelor continuă de la ultima "
    L"sincronizare validă până la un nou răspuns; starea se păstrează până la închiderea "
    L"aplicației.\r\n\r\nOră înregistrează cererile NTP de la pornire. Intrarea conține data, ora "
    L"locală a calculatorului, serverul și starea. OK indică un răspuns valid; θ abaterea față de "
    L"ora Windows. ERR oferă cauza și eventualul cod de eroare. Ultima intrare a grupului arată "
    L"și abaterea combinată Θ dacă există măsurători utilizabile. Abaterile sunt în milisecunde "
    L"cu patru zecimale: pozitiv înseamnă că serverul este înainte, negativ că rămâne în urmă. Θ "
    L"se bazează pe măsurătorile acceptate și apare în starea sincronizării. Salvare jurnal "
    L"exportă CSV cu abateri și detalii de eroare. Înregistrările nu rămân între sesiuni; salvați "
    L"înainte de ieșire dacă sunt necesare.",
    L"\r\n\r\nΠηγή ώρας και καταγραφή NTP\r\nΗ Ώρα επιλέγει ώρα συστήματος Windows ή διακομιστές "
    L"NTP για όλη την εφαρμογή. Το NTP αλλάζει μόνο την ώρα του CalClock· το ρολόι των Windows "
    L"δεν αλλάζει. Μέχρι την πρώτη έγκυρη απάντηση χρησιμοποιείται η ώρα συστήματος. Το NTP είναι "
    L"η προεπιλογή. Η αυτόματη ομάδα επιλέγει βάσει περιοχής συστήματος τσεχικούς και σλοβακικούς "
    L"διακομιστές, PTB για την Ευρώπη ή παγκόσμια ομάδα. Οι μετρήσεις φιλτράρονται βάσει "
    L"καθυστέρησης δικτύου και απόκλισης από άλλες απαντήσεις. Ο Συγχρονισμός τώρα αρχίζει αμέσως "
    L"νέα μέτρηση.\r\n\r\nΜετά τον συγχρονισμό το ρολόι του CalClock λειτουργεί ανεξάρτητα από "
    L"μεταγενέστερες αλλαγές της ώρας συστήματος των Windows. Σε απώλεια σύνδεσης ή αλλαγή "
    L"διακομιστών συνεχίζει από τον τελευταίο έγκυρο συγχρονισμό μέχρι νέα απάντηση· η κατάσταση "
    L"διατηρείται μέχρι το κλείσιμο.\r\n\r\nΗ Ώρα καταγράφει ερωτήματα NTP από την εκκίνηση. Κάθε "
    L"εγγραφή έχει ημερομηνία, τοπική ώρα υπολογιστή, διακομιστή και κατάσταση. OK σημαίνει "
    L"έγκυρη απάντηση, θ τη μετατόπισή της από τα Windows. ERR δίνει αιτία και τυχόν κωδικό "
    L"σφάλματος. Η τελευταία εγγραφή ομάδας δείχνει και τη συνδυασμένη απόκλιση Θ αν υπάρχουν "
    L"χρήσιμες μετρήσεις. Οι αποκλίσεις είναι σε χιλιοστά δευτερολέπτου με τέσσερα δεκαδικά: "
    L"θετική σημαίνει ότι ο διακομιστής προηγείται, αρνητική ότι καθυστερεί. Το Θ βασίζεται σε "
    L"αποδεκτές μετρήσεις και φαίνεται στην κατάσταση συγχρονισμού. Η Αποθήκευση αρχείου "
    L"καταγραφής εξάγει CSV με αποκλίσεις και λεπτομέρειες σφαλμάτων. Οι εγγραφές δεν "
    L"διατηρούνται μεταξύ εκκινήσεων· αποθηκεύστε τις πριν από την έξοδο αν χρειάζονται.",
    L"\r\n\r\nIzvor vremena\r\nKartica Vrijeme bira sistemsko vrijeme Windowsa ili podešene NTP "
    L"servere za cijeli program i sve vidžete. NTP mijenja samo vrijeme prikazano u CalClocku; "
    L"sat Windowsa nikad se ne mijenja. Do prvog valjanog odgovora koristi se sistemsko vrijeme. "
    L"NTP je podrazumijevani izbor. Automatski skup prema regiji sistema bira češke i slovačke "
    L"servere, PTB za Europu ili globalni skup. Mjerenja se filtriraju prema mrežnom kašnjenju i "
    L"odstupanjima od ostalih odgovora. Sinhroniziraj sada odmah pokreće novo "
    L"mjerenje.\r\n\r\nNakon sinhronizacije sat CalClocka nastavlja raditi nezavisno od naknadnih "
    L"promjena sistemskog vremena Windowsa. Pri prekidu veze ili promjeni servera nastavlja od "
    L"posljednje valjane sinhronizacije do novog odgovora; stanje se čuva do zatvaranja "
    L"programa.\r\n\r\nZapisnik NTP sinhronizacije\r\n\r\nKartica Vrijeme bilježi upite NTP "
    L"serverima od pokretanja programa. Svaki zapis sadrži datum i lokalno vrijeme računara, "
    L"server i stanje. OK označava valjan odgovor; θ prikazuje odstupanje od sistemskog vremena "
    L"Windowsa. ERR navodi uzrok i eventualnu šifru greške. Posljednji zapis skupine upita "
    L"prikazuje i objedinjeno odstupanje Θ ako postoje upotrebljiva mjerenja.\r\n\r\nOdstupanja "
    L"su u milisekundama s četiri decimalna mjesta. Pozitivna vrijednost znači da je sat servera "
    L"ispred Windowsa, a negativna da kasni. Objedinjeno Θ temelji se na prihvaćenim mjerenjima i "
    L"prikazuje se i u stanju sinhronizacije.\r\n\r\nSačuvaj zapisnik izvozi zapise u CSV, "
    L"uključujući odstupanja i pojedinosti grešaka. Zapisi se ne čuvaju između pokretanja; "
    L"sačuvajte ih prije izlaska ako ih želite zadržati.",
    L"\r\n\r\nIzvor vremena\r\nKartica Vrijeme bira sustavsko vrijeme Windowsa ili zadane NTP "
    L"poslužitelje za cijeli program i sve widgete. NTP mijenja samo vrijeme prikazano u "
    L"CalClocku; sat Windowsa nikad se ne mijenja. Do prvog valjanog odgovora koristi se "
    L"sustavsko vrijeme. NTP je zadani izbor. Automatski skup prema regiji sustava bira češke i "
    L"slovačke poslužitelje, PTB za Europu ili globalni skup. Mjerenja se filtriraju prema "
    L"mrežnom kašnjenju i odstupanjima od ostalih odgovora. Sinkroniziraj sada odmah pokreće novo "
    L"mjerenje.\r\n\r\nNakon sinkronizacije sat CalClocka nastavlja raditi neovisno o naknadnim "
    L"promjenama sustavskog vremena Windowsa. Pri prekidu veze ili promjeni poslužitelja "
    L"nastavlja od posljednje valjane sinkronizacije do novog odgovora; stanje se čuva do "
    L"zatvaranja programa.\r\n\r\nZapisnik NTP sinkronizacije\r\n\r\nKartica Vrijeme bilježi "
    L"upite NTP poslužiteljima od pokretanja programa. Svaki zapis sadrži datum i lokalno vrijeme "
    L"računala, poslužitelj i stanje. OK označava valjan odgovor; θ prikazuje odstupanje od "
    L"sustavskog vremena Windowsa. ERR navodi uzrok i eventualnu šifru pogreške. Posljednji zapis "
    L"skupine upita prikazuje i objedinjeno odstupanje Θ ako postoje upotrebljiva "
    L"mjerenja.\r\n\r\nOdstupanja su u milisekundama s četiri decimalna mjesta. Pozitivna "
    L"vrijednost znači da je sat poslužitelja ispred Windowsa, a negativna da kasni. Objedinjeno "
    L"Θ temelji se na prihvaćenim mjerenjima i prikazuje se i u stanju "
    L"sinkronizacije.\r\n\r\nSpremi zapisnik izvozi zapise u CSV, uključujući odstupanja i "
    L"pojedinosti pogrešaka. Zapisi se ne čuvaju između pokretanja; spremite ih prije izlaska ako "
    L"ih želite zadržati.",
    L"\r\n\r\nVir časa\r\nZavihek Čas izbere sistemski čas Windows ali strežnike NTP za celoten "
    L"program. NTP spremeni le čas CalClocka, ure Windows nikoli. Do prvega veljavnega odgovora "
    L"se uporablja sistemski čas. NTP je privzet. Samodejni nabor glede na regijo izbere češke in "
    L"slovaške strežnike, PTB za Evropo ali svetovni nabor. Meritve se filtrirajo po omrežni "
    L"zakasnitvi in odstopanjih. Sinhroniziraj zdaj takoj sproži novo meritev.\r\n\r\nPo "
    L"sinhronizaciji ura CalClock teče neodvisno od poznejših sprememb sistemske ure Windows. Ob "
    L"izgubi povezave ali menjavi strežnikov teče od zadnje veljavne sinhronizacije do novega "
    L"odgovora; stanje se ohrani do zaprtja programa.\r\n\r\nDnevnik sinhronizacije "
    L"NTP\r\n\r\nZavihek Čas beleži poizvedbe strežnikom NTP od zagona programa. Zapis vsebuje "
    L"datum in krajevni čas računalnika, strežnik in stanje. OK označuje veljaven odgovor s θ kot "
    L"odmikom od ure Windows. ERR navede razlog in morebitno kodo napake. Zadnji zapis skupine "
    L"poizvedb vsebuje tudi skupni odmik Θ, če so na voljo uporabne meritve.\r\n\r\nOdmiki so v "
    L"milisekundah s štirimi decimalnimi mesti. Pozitivna vrednost pomeni, da je strežnik pred "
    L"uro Windows, negativna pa za njo. Θ upošteva sprejete meritve in je prikazan tudi v stanju "
    L"sinhronizacije. Shrani dnevnik izvozi zapise v CSV z odmiki in podrobnostmi napak. Zapisi "
    L"se ne ohranijo med zagoni; pred izhodom jih shranite, če jih želite obdržati.",
    L"\r\n\r\nIzvor vremena\r\nKartica Vrijeme bira sistemsko vrijeme Windows-a ili NTP servere "
    L"za cijeli program. NTP mijenja samo prikaz CalClock-a; sat Windows-a se nikada ne mijenja. "
    L"Do prvog ispravnog odgovora koristi se sistemsko vrijeme. NTP je podrazumijevan. Automatska "
    L"grupa prema regionu sistema bira češke i slovačke servere, PTB za Evropu ili globalni skup. "
    L"Mjerenja se filtriraju prema mrežnom kašnjenju i odstupanjima od ostalih odgovora. "
    L"Sinhronizuj sada odmah počinje novo mjerenje.\r\n\r\nPoslije sinhronizacije sat CalClock-a "
    L"nastavlja nezavisno od kasnijih promjena sistemskog vremena Windows-a. Pri gubitku veze ili "
    L"promjeni servera nastavlja od posljednje ispravne sinhronizacije do novog odgovora; stanje "
    L"se čuva do zatvaranja programa.\r\n\r\nDnevnik NTP sinhronizacije\r\n\r\nKartica Vrijeme "
    L"bilježi upite NTP serverima od pokretanja programa. Zapis sadrži datum i lokalno vrijeme "
    L"računara, server i stanje. OK označava ispravan odgovor; θ njegovo odstupanje od sistemskog "
    L"vremena Windows-a. ERR navodi uzrok i eventualnu šifru greške. Posljednji zapis grupe upita "
    L"pokazuje i objedinjeno odstupanje Θ kada postoje upotrebljiva mjerenja.\r\n\r\nOdstupanja "
    L"su u milisekundama sa četiri decimale. Pozitivna vrijednost znači da je server ispred "
    L"Windows-a, negativna da kasni. Θ se zasniva na prihvaćenim mjerenjima i vidi se i u stanju "
    L"sinhronizacije. Sačuvaj dnevnik izvozi zapise u CSV sa odstupanjima i detaljima grešaka. "
    L"Zapisi se ne čuvaju između pokretanja; sačuvajte ih prije izlaska ako želite da ostanu.",
    L"\r\n\r\nКрыніца часу\r\nУкладка «Час» выбірае сістэмны час Windows або серверы NTP для ўсёй "
    L"праграмы. NTP змяняе толькі час CalClock, а не гадзіннік Windows. Да першага карэктнага "
    L"адказу выкарыстоўваецца сістэмны час. NTP выбраны першапачаткова. Аўтаматычны набор паводле "
    L"сістэмнага рэгіёна выбірае чэшскія і славацкія серверы, PTB для Еўропы або глабальны пул. "
    L"Вымярэнні фільтруюцца паводле сеткавай затрымкі і адхілення ад іншых адказаў. "
    L"«Сінхранізаваць зараз» адразу пачынае новае вымярэнне.\r\n\r\nПасля сінхранізацыі гадзіннік "
    L"CalClock працягвае адлік незалежна ад наступных змен сістэмнага часу Windows. Пры страце "
    L"сувязі ці змене сервераў ён працягвае адлік ад апошняй карэктнай сінхранізацыі да новага "
    L"адказу; стан захоўваецца да закрыцця праграмы.\r\n\r\nЖурнал сінхранізацыі "
    L"NTP\r\n\r\nУкладка «Час» запісвае запыты да сервераў NTP ад запуску праграмы. Запіс мае "
    L"дату і мясцовы час камп’ютара, сервер і стан. OK пазначае карэктны адказ, θ — адхіленне ад "
    L"сістэмнага часу Windows. ERR паказвае прычыну і магчымы код памылкі. Апошні запіс групы "
    L"запытаў мае таксама аб’яднанае адхіленне Θ, калі ёсць прыдатныя вымярэнні.\r\n\r\nАдхіленні "
    L"паказваюцца ў мілісекундах з чатырма дзесятковымі знакамі. Дадатнае значэнне азначае, што "
    L"сервер апярэджвае Windows, адмоўнае — што адстае. Θ улічвае прынятыя вымярэнні і "
    L"паказваецца ў стане сінхранізацыі. «Захаваць журнал» экспартуе запісы ў CSV з адхіленнямі і "
    L"звесткамі пра памылкі. Запісы не захоўваюцца паміж запускамі; перад выхадам захавайце іх, "
    L"калі хочаце пакінуць.",
    L"\r\n\r\nИзточник на време\r\nРазделът „Време“ избира системното време на Windows или NTP "
    L"сървъри за цялата програма. NTP променя само времето на CalClock; часовникът на Windows не "
    L"се променя. До първия валиден отговор се използва системното време. NTP е избрано по "
    L"подразбиране. Автоматичният набор според системния регион избира чешки и словашки сървъри, "
    L"PTB за Европа или глобален пул. Измерванията се филтрират по мрежовото закъснение и "
    L"отклоненията от другите отговори. „Синхронизирай сега“ започва ново измерване "
    L"веднага.\r\n\r\nСлед синхронизация часовникът на CalClock работи независимо от последващи "
    L"промени на системното време на Windows. При загуба на връзка или смяна на сървъри "
    L"продължава от последната валидна синхронизация до нов отговор; състоянието се пази до "
    L"затваряне на програмата.\r\n\r\nДневник на NTP синхронизацията\r\n\r\nРазделът „Време“ "
    L"записва запитванията към NTP сървърите от стартирането на програмата. Всеки запис има дата "
    L"и местно време на компютъра, сървър и състояние. OK означава валиден отговор, θ — "
    L"отклонението от системното време на Windows. ERR дава причината и евентуален код за грешка. "
    L"Последният запис на група запитвания включва и общото отклонение Θ при налични използваеми "
    L"измервания.\r\n\r\nОтклоненията са в милисекунди с четири знака след десетичния разделител. "
    L"Положителна стойност означава, че сървърът е пред Windows, отрицателна — че изостава. Θ "
    L"отчита приетите измервания и се вижда в състоянието на синхронизацията. „Запази дневника“ "
    L"експортира записите в CSV с отклоненията и подробностите за грешките. Записите не се пазят "
    L"между стартиранията; запишете ги преди изход, ако искате да ги запазите.",
    L"\r\n\r\nИзвор на време\r\nКартичката „Време“ избира системско време на Windows или сервери "
    L"NTP за целата програма. NTP го менува само времето на CalClock, никогаш часовникот на "
    L"Windows. До првиот важечки одговор се користи системско време. NTP е стандардниот избор. "
    L"Автоматската група според регионот избира чешки и словачки сервери, PTB за Европа или "
    L"глобалната група. Мерењата се филтрираат според мрежното доцнење и отстапувањата од другите "
    L"одговори. „Синхронизирај сега“ почнува ново мерење веднаш.\r\n\r\nПо синхронизацијата "
    L"часовникот на CalClock работи независно од подоцнежните промени на системското време на "
    L"Windows. При губење врска или промена на сервери продолжува од последната важечка "
    L"синхронизација до нов одговор; состојбата се чува до затворање на "
    L"програмата.\r\n\r\nДневник на синхронизацијата NTP\r\n\r\nКартичката „Време“ ги бележи "
    L"барањата до серверите NTP од стартувањето на програмата. Записот содржи датум и локално "
    L"време на компјутерот, сервер и состојба. OK значи важечки одговор, θ — отстапување од "
    L"системското време на Windows. ERR ги дава причината и можниот код за грешка. Последниот "
    L"запис на група барања го покажува и заедничкото отстапување Θ ако постојат употребливи "
    L"мерења.\r\n\r\nОтстапувањата се во милисекунди со четири децимални места. Позитивно значи "
    L"дека серверот е пред Windows, негативно дека доцни. Θ ги зема предвид прифатените мерења и "
    L"се покажува и во состојбата на синхронизацијата. „Зачувај дневник“ ги извезува записите во "
    L"CSV со отстапувањата и деталите за грешките. Записите не се чуваат меѓу стартувањата; "
    L"зачувајте ги пред излез ако сакате да останат.",
    L"\r\n\r\nИзвор времена\r\nКартица Време бира системско време Windows-а или NTP сервере за "
    L"цео програм. NTP мења само приказ CalClock-а; сат Windows-а се никада не мења. До првог "
    L"исправног одговора користи се системско време. NTP је подразумеван. Аутоматска група према "
    L"региону система бира чешке и словачке сервере, PTB за Европу или глобални скуп. Мерења се "
    L"филтрирају према мрежном кашњењу и одступањима од осталих одговора. Синхронизуј сада одмах "
    L"почиње ново мерење.\r\n\r\nПосле синхронизације сат CalClock-а наставља независно од "
    L"каснијих промена системског времена Windows-а. При губитку везе или промени сервера "
    L"наставља од последње исправне синхронизације до новог одговора; стање се чува до затварања "
    L"програма.\r\n\r\nДневник NTP синхронизације\r\n\r\nКартица Време бележи упите NTP серверима "
    L"од покретања програма. Запис садржи датум и локално време рачунара, сервер и стање. OK "
    L"означава исправан одговор; θ његово одступање од системског времена Windows-а. ERR наводи "
    L"узрок и евентуалну шифру грешке. Последњи запис групе упита показује и обједињено одступање "
    L"Θ када постоје употребљива мерења.\r\n\r\nОдступања су у милисекундама са четири децимале. "
    L"Позитивна вредност значи да је сервер испред Windows-а, негативна да касни. Θ се заснива на "
    L"прихваћеним мерењима и види се и у стању синхронизације. Сачувај дневник извози записе у "
    L"CSV са одступањима и детаљима грешака. Записи се не чувају између покретања; сачувајте их "
    L"пре изласка ако желите да остану.",
    L"\r\n\r\nДЖЕРЕЛО ЧАСУ\r\nНа вкладці «Час» вибирається системний час Windows або налаштовані "
    L"сервери NTP для всієї програми та всіх віджетів. NTP коригує лише час CalClock, не змінюючи "
    L"годинник Windows. До першої коректної відповіді використовується системний час. NTP вибрано "
    L"за замовчуванням. Автоматичний набір вибирає чеські та словацькі сервери, PTB для Європи "
    L"або глобальний пул відповідно до системного регіону. Кілька вимірювань фільтруються за "
    L"мережевою затримкою та відхиленням від інших відповідей. «Синхронізувати зараз» негайно "
    L"запускає нове вимірювання.\r\n\r\nПісля синхронізації годинник CalClock продовжує відлік "
    L"незалежно від подальших змін системного часу Windows. У разі втрати зв’язку або зміни "
    L"серверів він продовжує відлік від останньої коректної синхронізації до отримання нової "
    L"відповіді; цей стан зберігається до закриття програми.\r\n\r\nЖУРНАЛ СИНХРОНІЗАЦІЇ "
    L"NTP\r\nВкладка «Час» містить журнал запитів до серверів NTP від початку роботи програми. "
    L"Кожен запис містить дату й місцевий час комп’ютера, сервер і стан. OK позначає коректну "
    L"відповідь; θ показує відхилення від системного часу Windows. ERR містить причину збою та, "
    L"за наявності, код помилки. Останній запис групи запитів також показує об’єднане відхилення "
    L"Θ, якщо отримано придатні вимірювання.\r\n\r\nВідхилення показуються в мілісекундах із "
    L"чотирма десятковими знаками. Додатне значення означає, що час сервера випереджає Windows, "
    L"від’ємне — що він відстає. Об’єднане відхилення Θ розраховується за прийнятими "
    L"вимірюваннями й також показується у стані синхронізації.\r\n\r\nКоманда «Зберегти журнал» "
    L"експортує записи до CSV разом із відхиленнями та відомостями про помилки. Між запусками "
    L"програми журнал не зберігається; за потреби збережіть його перед виходом.",
    L"\r\n\r\nИСТОЧНИК ВРЕМЕНИ\r\nНа вкладке «Время» выбирается системное время Windows или "
    L"настроенные серверы NTP для всей программы и всех виджетов. NTP корректирует только время "
    L"CalClock, не меняя часы Windows. До первого корректного ответа используется системное время. "
    L"NTP выбран по умолчанию. Автоматический набор выбирает чешские и словацкие серверы, PTB для "
    L"Европы или глобальный пул в соответствии с системным регионом. Несколько измерений "
    L"фильтруются по сетевой задержке и отклонению от других ответов. «Синхронизировать сейчас» "
    L"немедленно запускает новое измерение.\r\n\r\nПосле синхронизации часы CalClock продолжают "
    L"отсчёт независимо от последующих изменений системного времени Windows. При потере связи или "
    L"смене серверов они продолжают отсчёт от последней корректной синхронизации до получения "
    L"нового ответа; это состояние сохраняется до закрытия программы.\r\n\r\nЖУРНАЛ СИНХРОНИЗАЦИИ "
    L"NTP\r\nВкладка «Время» содержит журнал запросов к серверам NTP с начала работы программы. "
    L"Каждая запись содержит дату и местное время компьютера, сервер и состояние. OK обозначает "
    L"корректный ответ; θ показывает отклонение от системного времени Windows. ERR содержит "
    L"причину сбоя и, при наличии, код ошибки. Последняя запись группы запросов также показывает "
    L"объединённое отклонение Θ, если получены пригодные измерения.\r\n\r\nОтклонения показываются "
    L"в миллисекундах с четырьмя десятичными знаками. Положительное значение означает, что время "
    L"сервера опережает Windows, отрицательное — что оно отстаёт. Объединённое отклонение Θ "
    L"рассчитывается по принятым измерениям и также показывается в состоянии "
    L"синхронизации.\r\n\r\nКоманда «Сохранить журнал» экспортирует записи в CSV вместе с "
    L"отклонениями и сведениями об ошибках. Между запусками программы журнал не сохраняется; при "
    L"необходимости сохраните его перед выходом."
};

const wchar_t* HELP_FULLSCREEN_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nHODINY NA MONITORU\r\nDigitální hodiny mohou vyplnit jeden či více monitorů a "
    L"volitelně zatemnit ostatní. Velikost písma se udává procentem výšky monitoru; nastavit lze "
    L"také písmo, vyhlazování, barvy a odsazení. Při času UTC lze na samostatném řádku zobrazit "
    L"text UTC. Výchozí je bílý text na černém pozadí. Je-li otevřeno Nastavení, hodiny se vždy "
    L"zobrazují jen jako malý přesouvatelný náhled se zachovaným poměrem stran; jeho poloha se "
    L"ukládá. Zarovnání do mřížky tento typ nepřesouvá ani s ním nepočítá. Esc hodiny skryje a "
    L"zatemnění odstraní i tehdy, když je aktivní Nastavení.\r\n\r\nNad celomonitorovými hodinami "
    L"i zatemněnými monitory se kurzor po chvíli nečinnosti skryje a při pohybu myši znovu "
    L"objeví. Nad zmenšeným náhledem v režimu Nastavení zůstává viditelný.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and optionally "
    L"black out the others. Font size is a percentage of monitor height; font, smoothing, colors "
    L"and padding are also configurable. In UTC mode, UTC can be shown on a separate line. The "
    L"default is white text on black. While Settings is open, the clock is always a small "
    L"draggable preview that keeps the monitor aspect ratio, and its position is saved. Grid "
    L"arrangement ignores and does not move this widget type. Esc hides the clock and removes "
    L"blackouts even when Settings is active.\r\n\r\nThe pointer hides after a short period of "
    L"inactivity over monitor clocks and blacked-out monitors, and reappears when the mouse "
    L"moves. It stays visible over the small preview while Settings is open.",
    L"\r\n\r\nMONITORUHR\r\nDie Digitaluhr kann einen oder mehrere Monitore ausfüllen und die "
    L"übrigen optional abdunkeln. Die Schriftgröße ist ein Prozentsatz der Monitorhöhe; Schrift, "
    L"Glättung, Farben und Innenabstand sind ebenfalls einstellbar. Im UTC-Modus kann UTC in "
    L"einer eigenen Zeile stehen. Voreingestellt ist Weiß auf Schwarz. Bei geöffneten "
    L"Einstellungen erscheint die Uhr stets als kleine verschiebbare Vorschau mit dem "
    L"Seitenverhältnis des Monitors; ihre Position wird gespeichert. Die Rasteranordnung "
    L"ignoriert diesen Widget-Typ. Esc blendet Uhr und Abdunklung auch bei aktiven Einstellungen "
    L"aus.\r\n\r\nDer Mauszeiger wird über Monitoruhren und abgedunkelten Monitoren nach kurzer "
    L"Inaktivität ausgeblendet und bei Bewegung wieder angezeigt. Über der kleinen Vorschau bei "
    L"geöffneten Einstellungen bleibt er sichtbar.",
    L"\r\n\r\nHORLOGE SUR MONITEUR\r\nL’horloge numérique peut remplir un ou plusieurs moniteurs "
    L"et assombrir les autres. La taille de police est un pourcentage de la hauteur ; police, "
    L"lissage, couleurs et marge sont aussi réglables. En mode UTC, UTC peut apparaître sur une "
    L"ligne distincte. La valeur par défaut est blanc sur noir. Tant que Paramètres est ouvert, "
    L"l’horloge reste un petit aperçu déplaçable aux proportions du moniteur, dont la position "
    L"est enregistrée. L’alignement en grille ignore ce type de widget. Échap masque l’horloge et "
    L"retire l’assombrissement même si Paramètres est actif.\r\n\r\nLe pointeur se masque après "
    L"une courte inactivité sur les horloges plein écran et les moniteurs assombris, puis "
    L"réapparaît au mouvement de la souris. Il reste visible sur le petit aperçu lorsque "
    L"Paramètres est ouvert.",
    L"\r\n\r\nRELOJ DE MONITOR\r\nEl reloj digital puede ocupar uno o varios monitores y "
    L"oscurecer los demás. El tamaño de fuente es un porcentaje de la altura; también se "
    L"configuran fuente, suavizado, colores y relleno. En modo UTC, UTC puede mostrarse en una "
    L"línea separada. El valor predeterminado es blanco sobre negro. Mientras Configuración está "
    L"abierta, el reloj siempre es una vista previa pequeña y móvil con la proporción del "
    L"monitor, y se guarda su posición. La alineación en cuadrícula ignora este tipo. Esc oculta "
    L"el reloj y elimina el oscurecimiento incluso con Configuración activa.\r\n\r\nEl puntero se "
    L"oculta tras un breve período de inactividad sobre los relojes de monitor y los monitores "
    L"oscurecidos, y reaparece al mover el ratón. Permanece visible sobre la vista previa pequeña "
    L"mientras Configuración está abierta.",
    L"\r\n\r\nOROLOGIO SU MONITOR\r\nL’orologio digitale può occupare uno o più monitor e "
    L"oscurare gli altri. La dimensione del carattere è una percentuale dell’altezza; sono "
    L"configurabili anche carattere, antialiasing, colori e margine. In modalità UTC, UTC può "
    L"apparire su una riga separata. Il valore predefinito è bianco su nero. Con Impostazioni "
    L"aperto, l’orologio resta sempre una piccola anteprima spostabile con le proporzioni del "
    L"monitor, e la posizione viene salvata. La disposizione in griglia ignora questo tipo. Esc "
    L"nasconde orologio e oscuramento anche con Impostazioni attivo.\r\n\r\nIl puntatore si "
    L"nasconde dopo una breve inattività sugli orologi a schermo intero e sui monitor oscurati, e "
    L"riappare muovendo il mouse. Rimane visibile sulla piccola anteprima quando Impostazioni è "
    L"aperto.",
    L"\r\n\r\nZEGAR NA MONITORZE\r\nZegar cyfrowy może zająć jeden lub kilka monitorów i wygasić "
    L"pozostałe. Rozmiar czcionki jest procentem wysokości monitora; można też ustawić czcionkę, "
    L"wygładzanie, kolory i odstęp. W trybie UTC napis UTC można wyświetlić w osobnym wierszu. "
    L"Domyślne są białe cyfry na czarnym tle. Gdy Ustawienia są otwarte, zegar zawsze jest małym, "
    L"przesuwanym podglądem o proporcjach monitora, a jego położenie jest zapisywane. Układanie w "
    L"siatce pomija ten typ. Esc ukrywa zegar i wygaszenie również przy aktywnych "
    L"Ustawieniach.\r\n\r\nWskaźnik znika po krótkiej bezczynności nad zegarami pełnoekranowymi i "
    L"zaciemnionymi monitorami, a pojawia się po poruszeniu myszą. Nad małym podglądem przy "
    L"otwartych Ustawieniach pozostaje widoczny.",
    L"\r\n\r\nHODINY NA MONITORE\r\nDigitálne hodiny môžu vyplniť jeden alebo viac monitorov a "
    L"stmaviť ostatné. Veľkosť písma je percentom výšky monitora; nastaviť možno aj písmo, "
    L"vyhladzovanie, farby a odsadenie. V režime UTC možno zobraziť text UTC na samostatnom "
    L"riadku. Predvolené je biele písmo na čiernom pozadí. Pri otvorenom Nastavení sú hodiny vždy "
    L"iba malým presúvateľným náhľadom s pomerom strán monitora a jeho poloha sa ukladá. "
    L"Zarovnanie do mriežky tento typ ignoruje. Esc skryje hodiny aj stmavenie aj pri aktívnom "
    L"Nastavení.\r\n\r\nNad celomonitorovými hodinami aj zatemnenými monitormi sa kurzor po "
    L"chvíli nečinnosti skryje a pri pohybe myši sa znovu objaví. Nad zmenšeným náhľadom v režime "
    L"Nastavenia zostáva viditeľný.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and optionally "
    L"black out the others. Font size is a percentage of monitor height; font, smoothing, colours "
    L"and padding are also configurable. In UTC mode, UTC can be shown on a separate line. The "
    L"default is white text on black. While Settings is open, the clock is always a small "
    L"draggable preview that keeps the monitor aspect ratio, and its position is saved. Grid "
    L"arrangement ignores and does not move this widget type. Esc hides the clock and removes "
    L"blackouts even when Settings is active.\r\n\r\nThe pointer hides after a short period of "
    L"inactivity over monitor clocks and blacked-out monitors, and reappears when the mouse "
    L"moves. It stays visible over the small preview while Settings is open.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and optionally "
    L"black out the others. Font size is a percentage of monitor height; font, smoothing, colours "
    L"and padding are also configurable. In UTC mode, UTC can be shown on a separate line. The "
    L"default is white text on black. While Settings is open, the clock is always a small "
    L"draggable preview that keeps the monitor aspect ratio, and its position is saved. Grid "
    L"arrangement ignores and does not move this widget type. Esc hides the clock and removes "
    L"blackouts even when Settings is active.\r\n\r\nThe pointer hides after a short period of "
    L"inactivity over monitor clocks and blacked-out monitors, and reappears when the mouse "
    L"moves. It stays visible over the small preview while Settings is open.",
    L"\r\n\r\nRELÓGIO NO MONITOR\r\nO relógio digital pode preencher um ou vários monitores e "
    L"escurecer os restantes. A letra é uma percentagem da altura do monitor e também se "
    L"configuram tipo de letra, suavização, cores e margem. Com as Definições abertas é sempre "
    L"uma pequena pré-visualização arrastável. Esc oculta o relógio e remove o "
    L"escurecimento.\r\n\r\nO ponteiro oculta-se após um curto período de inatividade sobre "
    L"relógios de monitor e monitores escurecidos, e reaparece ao mover o rato. Permanece visível "
    L"sobre a pequena pré-visualização com as Definições abertas.",
    L"\r\n\r\nSKJERMKLOKKE\r\nDen digitale klokken kan fylle én eller flere skjermer og mørklegge "
    L"resten. Skriftstørrelsen er en prosentandel av skjermhøyden; skrift, utjevning, farger og "
    L"luft kan også angis. Når Innstillinger er åpent, vises alltid en liten, flyttbar "
    L"forhåndsvisning. Esc skjuler klokken og fjerner mørklegging.\r\n\r\nPekeren skjules etter "
    L"kort inaktivitet over skjermklokker og mørklagte skjermer, og vises igjen når musen "
    L"beveges. Den forblir synlig over den lille forhåndsvisningen når Innstillinger er åpent.",
    L"\r\n\r\nSKÄRMKLOCKA\r\nDen digitala klockan kan fylla en eller flera bildskärmar och släcka "
    L"de övriga. Teckenstorleken är en procentandel av bildskärmshöjden; teckensnitt, utjämning, "
    L"färger och utfyllnad kan också ställas in. När Inställningar är öppet visas alltid en liten "
    L"flyttbar förhandsvisning. Esc döljer klockan och tar bort släckningen.\r\n\r\nPekaren döljs "
    L"efter en kort stunds inaktivitet över skärmklockor och mörklagda skärmar och visas igen när "
    L"musen rör sig. Den förblir synlig över den lilla förhandsvisningen när Inställningar är "
    L"öppet.",
    L"\r\n\r\nNÄYTTÖKELLO\r\nDigitaalinen kello voi täyttää yhden tai useita näyttöjä ja pimentää "
    L"muut. Fonttikoko on prosenttiosuus näytön korkeudesta; myös fontti, pehmennys, värit ja "
    L"täyttö voidaan määrittää. Kun Asetukset on avoinna, näytetään aina pieni siirrettävä "
    L"esikatselu. Esc piilottaa kellon ja poistaa pimennyksen.\r\n\r\nOsoitin piilotetaan lyhyen "
    L"käyttämättömyyden jälkeen näyttökellojen ja pimennettyjen näyttöjen päällä. Se palaa "
    L"näkyviin hiirtä liikuttamalla. Pienen esikatselun päällä osoitin pysyy näkyvissä Asetusten "
    L"ollessa auki.",
    L"\r\n\r\nSKÆRMUR\r\nDet digitale ur kan fylde en eller flere skærme og mørklægge de øvrige. "
    L"Skriftstørrelsen er en procentdel af skærmhøjden; skrifttype, udjævning, farver og luft kan "
    L"også indstilles. Når Indstillinger er åbent, vises altid en lille flytbar forhåndsvisning. "
    L"Esc skjuler uret og fjerner mørklægningen.\r\n\r\nMarkøren skjules efter kort inaktivitet "
    L"over skærmure og mørklagte skærme og vises igen, når musen bevæges. Den forbliver synlig "
    L"over den lille forhåndsvisning, når Indstillinger er åbent.",
    L"\r\n\r\nSKJÁKUKKA\r\nStafræna klukkan getur fyllt einn eða fleiri skjái og myrkvað hina. "
    L"Leturstærð er hlutfall af hæð skjásins; einnig má stilla letur, jöfnun, liti og bil. Þegar "
    L"Stillingar eru opnar birtist alltaf lítil færanleg forskoðun. Esc felur klukkuna og "
    L"fjarlægir myrkvun.\r\n\r\nBendillinn felst eftir stutt aðgerðaleysi yfir skjáklukkum og "
    L"myrkvuðum skjám og birtist aftur þegar músin hreyfist. Hann er sýnilegur yfir litlu "
    L"forskoðuninni meðan Stillingar eru opnar.",
    L"\r\n\r\nMONİTÖR SAATİ\r\nDijital saat bir veya daha fazla monitörü doldurabilir ve "
    L"diğerlerini karartabilir. Yazı tipi boyutu monitör yüksekliğinin yüzdesidir; yazı tipi, "
    L"kenar yumuşatma, renkler ve dolgu da ayarlanabilir. Ayarlar açıkken her zaman küçük, "
    L"sürüklenebilir bir önizleme gösterilir. Esc saati gizler ve karartmayı "
    L"kaldırır.\r\n\r\nİşaretçi, monitör saatleri ve karartılmış monitörler üzerinde kısa bir "
    L"hareketsizlikten sonra gizlenir ve fare hareket edince yeniden görünür. Ayarlar açıkken "
    L"küçük önizleme üzerinde görünür kalır.",
    L"\r\n\r\nEkraanikell\r\nDigitaalkell võib täita ühe või mitu kuvarit ja tumendada ülejäänud. "
    L"Fondisuurus on protsent kuvari kõrgusest; valida saab ka fondi, silumise, värvid ja "
    L"siseveerise. UTC võib olla eraldi real. Vaikimisi on tekst valge ja taust must. Avatud "
    L"sätetega esitatakse kella väikese liigutatava eelvaatena, mis säilitab kuvari kuvasuhte ja "
    L"mille asukoht salvestatakse. Ruudustikupaigutus seda tüüpi ei liiguta. Esc peidab kella ja "
    L"eemaldab tumenduse ka avatud sätetega.\r\n\r\nHiirekursor peitub ekraanikella või "
    L"tumendatud kuvarite kohal pärast lühikest tegevusetust ning ilmub hiire liigutamisel. "
    L"Väikese eelvaate kohal jääb see nähtavaks.",
    L"\r\n\r\nClog scáileáin\r\nIs féidir le clog digiteach monatóir amháin nó níos mó a líonadh "
    L"agus na cinn eile a dhorchú. Is céatadán d’airde an mhonatóra an clómhéid; tá cló, "
    L"frithailiasáil, dathanna agus spásáil inmheánach ar fáil freisin. Is féidir UTC a chur ar "
    L"shraith ar leith. Téacs bán ar chúlra dubh atá ann ar dtús. Nuair atá Socruithe oscailte, "
    L"is réamhamharc beag inaistrithe é le cóimheas treoíochta an mhonatóra agus suíomh "
    L"sábháilte. Ní bhogann an eangach an cineál seo. Folaíonn Esc an clog agus baintear dorchú "
    L"fiú nuair atá Socruithe oscailte.\r\n\r\nFolaítear an pointeoir tar éis tréimhse ghairid "
    L"gan ghníomhaíocht os cionn an chloig nó monatóirí dorchaithe agus tagann sé ar ais le "
    L"gluaiseacht luiche. Fanann sé infheicthe os cionn an réamhamhairc bhig.",
    L"\r\n\r\nEkrano laikrodis\r\nSkaitmeninis laikrodis gali užpildyti vieną ar kelis monitorius "
    L"ir užtemdyti kitus. Šrifto dydis yra monitoriaus aukščio procentas; pasirenkamas šriftas, "
    L"glodinimas, spalvos ir vidinė paraštė. UTC gali būti atskiroje eilutėje. Numatytasis "
    L"vaizdas – baltas tekstas juodame fone. Kol atidaryti parametrai, rodomas mažas perkeliamas "
    L"peržiūros langas, išlaikantis monitoriaus proporcijas ir įrašomą padėtį. Tinklelis šio tipo "
    L"neperkelia. Esc paslepia laikrodį ir pašalina užtemdymą net atidarius "
    L"parametrus.\r\n\r\nPelės žymeklis virš ekrano laikrodžio ir užtemdytų monitorių pasislepia "
    L"po trumpos neveiklos ir vėl pasirodo pajudinus pelę. Virš mažos peržiūros jis lieka matomas.",
    L"\r\n\r\nEkrāna pulkstenis\r\nDigitālais pulkstenis var aizpildīt vienu vai vairākus "
    L"monitorus un aptumšot pārējos. Fonta lielums ir procenti no monitora augstuma; izvēlami "
    L"fonts, nogludināšana, krāsas un iekšējā atkāpe. UTC var būt atsevišķā rindā. Noklusējums ir "
    L"balts teksts uz melna fona. Kamēr atvērti iestatījumi, redzams mazs pārvietojams "
    L"priekšskatījums ar monitora malu attiecību un saglabājamu novietojumu. Režģis šo tipu "
    L"nepārvieto. Esc paslēpj pulksteni un noņem aptumšojumu arī tad, ja iestatījumi ir "
    L"atvērti.\r\n\r\nPeles rādītājs virs ekrāna pulksteņa un aptumšotajiem monitoriem pēc īsas "
    L"neaktivitātes pazūd un atgriežas, pakustinot peli. Virs mazā priekšskatījuma tas paliek "
    L"redzams.",
    L"\r\n\r\nKépernyőóra\r\nA digitális óra egy vagy több monitort kitölthet, a többit "
    L"elsötétítheti. A betűméret a monitor magasságának százaléka; betűtípus, élsimítás, színek "
    L"és belső margó is választható. Az UTC külön sorban lehet. Alapból fehér szöveg jelenik meg "
    L"fekete háttéren. Nyitott Beállítások mellett az óra kicsi, mozgatható előnézet a monitor "
    L"képarányával, mentett helyzettel. A rács ezt a típust nem mozgatja. Az Esc nyitott "
    L"Beállítások mellett is elrejti az órát és megszünteti az elsötétítést.\r\n\r\nAz egérmutató "
    L"rövid tétlenség után eltűnik a képernyőóra és az elsötétített monitorok fölött, és "
    L"egérmozgáskor visszatér. A kis előnézet fölött látható marad.",
    L"\r\n\r\nArloġġ tal-iskrin\r\nArloġġ diġitali jista’ jimla moniter wieħed jew aktar u "
    L"jdallam l-oħrajn. Id-daqs tal-font huwa perċentwal tal-għoli tal-moniter; jintgħażlu wkoll "
    L"font, anti-aliasing, kuluri u spazju intern. UTC jista’ jkun f’ringiela separata. "
    L"Id-default huwa test abjad fuq sfond iswed. Bis-Settings miftuħa, l-arloġġ huwa previżjoni "
    L"żgħira li tista’ titmexxa bil-proporzjonijiet tal-moniter u pożizzjoni ssejvjata. "
    L"Il-gradilja ma tmexxix dan it-tip. Esc jaħbi l-arloġġ u jneħħi d-dlam anki bis-Settings "
    L"miftuħa.\r\n\r\nIl-pointer tal-maws jinħeba wara ftit inattività fuq l-arloġġ jew "
    L"il-moniters mudlama u jerġa’ jidher meta jiċċaqlaq il-maws. Fuq il-previżjoni żgħira jibqa’ "
    L"viżibbli.",
    L"\r\n\r\nSchermklok\r\nEen digitale klok kan een of meer beeldschermen vullen en de andere "
    L"verduisteren. De tekengrootte is een percentage van de schermhoogte; lettertype, "
    L"vereffening, kleuren en binnenmarge zijn instelbaar. UTC kan op een aparte rij staan. "
    L"Standaard is de tekst wit op zwart. Met Instellingen geopend is de klok een klein "
    L"verplaatsbaar voorbeeld met de beeldverhouding van het scherm en een opgeslagen positie. "
    L"Het raster verplaatst dit type niet. Esc verbergt de klok en verwijdert verduistering, ook "
    L"met Instellingen geopend.\r\n\r\nDe muisaanwijzer verdwijnt na korte inactiviteit boven de "
    L"schermklok en verduisterde schermen en verschijnt bij bewegen. Boven het kleine voorbeeld "
    L"blijft deze zichtbaar.",
    L"\r\n\r\nCeas pe ecran\r\nUn ceas digital poate umple unul sau mai multe monitoare și le "
    L"poate întuneca pe celelalte. Dimensiunea fontului este procent din înălțimea monitorului; "
    L"se pot alege fontul, netezirea, culorile și spațierea interioară. UTC poate fi pe un rând "
    L"separat. Implicit, textul este alb pe fundal negru. Cu Setări deschis, ceasul este o "
    L"previzualizare mică, mobilă, cu proporțiile monitorului și poziție salvată. Grila nu mută "
    L"acest tip. Esc ascunde ceasul și elimină întunecarea chiar cu Setări "
    L"deschis.\r\n\r\nIndicatorul mouse-ului se ascunde după o scurtă inactivitate deasupra "
    L"ceasului și monitoarelor întunecate și reapare la mișcare. Deasupra previzualizării mici "
    L"rămâne vizibil.",
    L"\r\n\r\nΡολόι οθόνης\r\nΨηφιακό ρολόι μπορεί να γεμίσει μία ή περισσότερες οθόνες και να "
    L"συσκοτίσει τις υπόλοιπες. Το μέγεθος γραμματοσειράς είναι ποσοστό του ύψους οθόνης· "
    L"επιλέγονται γραμματοσειρά, εξομάλυνση, χρώματα και εσωτερικό περιθώριο. Το UTC μπορεί να "
    L"έχει χωριστή γραμμή. Προεπιλογή είναι λευκό κείμενο σε μαύρο φόντο. Με ανοιχτές Ρυθμίσεις "
    L"το ρολόι είναι μικρή μετακινούμενη προεπισκόπηση με αναλογία οθόνης και αποθηκευμένη θέση. "
    L"Το πλέγμα δεν μετακινεί αυτόν τον τύπο. Το Esc κρύβει το ρολόι και αφαιρεί τη συσκότιση "
    L"ακόμη και με ανοιχτές Ρυθμίσεις.\r\n\r\nΟ δείκτης ποντικιού κρύβεται μετά από λίγη αδράνεια "
    L"πάνω από το ρολόι και τις συσκοτισμένες οθόνες και επιστρέφει με κίνηση. Πάνω από τη μικρή "
    L"προεπισκόπηση παραμένει ορατός.",
    L"\r\n\r\nSat na ekranu\r\nDigitalni sat može ispuniti jedan ili više ekrana i po potrebi "
    L"zatamniti ostale. Veličina fonta zadaje se kao postotak visine ekrana; mogu se podesiti i "
    L"font, izglađivanje, boje i unutrašnji razmak. U načinu UTC oznaka UTC može biti u zasebnom "
    L"redu. Podrazumijevani je izgled bijeli tekst na crnoj pozadini. Dok su Postavke otvorene, "
    L"sat je mali pomični pregled koji čuva omjer stranica ekrana; njegov se položaj čuva. "
    L"Raspoređivanje u mrežu izostavlja tu vrstu vidžeta. Esc skriva sat i uklanja zatamnjenje i "
    L"kada su Postavke otvorene.\r\n\r\nPokazivač miša skriva se nakon kratke neaktivnosti iznad "
    L"sata na ekranu i zatamnjenih ekrana te se ponovno prikazuje nakon pomicanja miša. Iznad "
    L"malog pregleda u Postavkama ostaje vidljiv.",
    L"\r\n\r\nSat na zaslonu\r\nDigitalni sat može ispuniti jedan ili više zaslona i po potrebi "
    L"zatamniti ostale. Veličina fonta zadaje se kao postotak visine zaslona; mogu se podesiti i "
    L"font, izglađivanje, boje i unutarnji razmak. U načinu UTC oznaka UTC može biti u zasebnom "
    L"retku. Zadani je izgled bijeli tekst na crnoj pozadini. Dok su Postavke otvorene, sat je "
    L"mali pomični pretpregled koji čuva omjer stranica zaslona; njegov se položaj sprema. "
    L"Raspoređivanje u mrežu izostavlja tu vrstu widgeta. Esc skriva sat i uklanja zatamnjenje i "
    L"kada su Postavke otvorene.\r\n\r\nPokazivač miša skriva se nakon kratke neaktivnosti iznad "
    L"sata na zaslonu i zatamnjenih zaslona te se ponovno prikazuje nakon pomicanja miša. Iznad "
    L"malog pretpregleda u Postavkama ostaje vidljiv.",
    L"\r\n\r\nUra na zaslonu\r\nDigitalna ura lahko zapolni enega ali več zaslonov in po potrebi "
    L"zatemni druge. Velikost pisave je odstotek višine zaslona; nastavljivi so tudi pisava, "
    L"glajenje, barve in notranji odmik. UTC je lahko v ločeni vrstici. Privzet je bel napis na "
    L"črni podlagi. Med odprtimi Nastavitvami je ura majhen premakljiv predogled z razmerjem "
    L"stranic izbranega zaslona; njegov položaj se shrani. Razporeditev v mrežo tega gradnika ne "
    L"premika. Esc skrije uro in odstrani zatemnitev tudi med odprtimi "
    L"Nastavitvami.\r\n\r\nKazalec se po kratki nedejavnosti nad uro na zaslonu ali zatemnjenimi "
    L"zasloni skrije in ob premiku miške spet pokaže. Nad majhnim predogledom ostane viden.",
    L"\r\n\r\nSat na monitoru\r\nDigitalni sat može popuniti jedan ili više monitora i zatamniti "
    L"ostale. Veličina fonta zadaje se kao procenat visine monitora; podešavaju se i font, "
    L"umekšavanje, boje i unutrašnji razmak. UTC može biti u zasebnom redu. Podrazumijevan je "
    L"bijeli tekst na crnoj pozadini. Dok su Podešavanja otvorena, sat je mali pokretni pregled "
    L"sa odnosom stranica monitora; njegov položaj se čuva. Rasporedi u mrežu ne premješta tu "
    L"vrstu vidžeta. Esc skriva sat i uklanja zatamnjenje i kada su Podešavanja "
    L"otvorena.\r\n\r\nPokazivač miša skriva se poslije kratke neaktivnosti iznad sata na "
    L"monitoru i zatamnjenih monitora, a pojavljuje pri pomjeranju miša. Iznad malog pregleda "
    L"ostaje vidljiv.",
    L"\r\n\r\nГадзіннік на маніторы\r\nЛічбавы гадзіннік можа займаць адзін ці некалькі манітораў "
    L"і зацямняць астатнія. Памер шрыфту — працэнт вышыні манітора; таксама задаюцца шрыфт, "
    L"згладжванне, колеры і ўнутраны водступ. UTC можа паказвацца асобным радком. Прадвызначаны "
    L"выгляд — белы тэкст на чорным фоне. Пры адкрытых наладах гадзіннік паказваецца маленькім "
    L"рухомым праглядам з прапорцыямі манітора; яго пазіцыя захоўваецца. Упарадкаванне па сетцы "
    L"гэты віджэт не перамяшчае. Esc хавае гадзіннік і прыбірае зацямненне нават з адкрытымі "
    L"наладамі.\r\n\r\nПаказальнік мышы хаваецца пасля кароткай бяздзейнасці над гадзіннікам на "
    L"маніторы ці зацемненымі маніторамі і з’яўляецца пры руху мышы. Над маленькім праглядам ён "
    L"застаецца бачным.",
    L"\r\n\r\nЧасовник на монитор\r\nЦифровият часовник може да запълни един или няколко монитора "
    L"и да затъмни останалите. Размерът на шрифта е процент от височината на монитора; задават се "
    L"и шрифт, изглаждане, цветове и вътрешен отстъп. UTC може да е на отделен ред. По "
    L"подразбиране текстът е бял върху черен фон. При отворени настройки часовникът е малък "
    L"подвижен преглед със съотношението на страните на монитора; позицията му се пази. "
    L"Подреждането в мрежа не го премества. Esc скрива часовника и премахва затъмнението дори при "
    L"отворени настройки.\r\n\r\nПоказалецът се скрива след кратко бездействие над часовника или "
    L"затъмнените монитори и се показва отново при движение на мишката. Над малкия преглед остава "
    L"видим.",
    L"\r\n\r\nЧасовник на монитор\r\nДигиталниот часовник може да пополни еден или повеќе "
    L"монитори и да ги затемни другите. Големината на фонтот е процент од височината на "
    L"мониторот; се поставуваат и фонтот, измазнувањето, боите и внатрешната маргина. UTC може да "
    L"биде во одделен ред. Стандардно има бел текст на црна заднина. Додека се отворени "
    L"поставките, часовникот е мал подвижен преглед со односот на страните на мониторот; "
    L"положбата му се зачувува. Распоредувањето во мрежа не го поместува овој виџет. Esc го крие "
    L"часовникот и го отстранува затемнувањето и при отворени поставки.\r\n\r\nПокажувачот на "
    L"глувчето се крие по кратка неактивност над часовникот или затемнетите монитори и се "
    L"појавува при движење. Над малиот преглед останува видлив.",
    L"\r\n\r\nСат на монитору\r\nДигитални сат може попунити један или више монитора и затамнити "
    L"остале. Величина фонта задаје се као проценат висине монитора; подешавају се и фонт, "
    L"умекшавање, боје и унутрашњи размак. UTC може бити у засебном реду. Подразумеван је бели "
    L"текст на црној позадини. Док су Подешавања отворена, сат је мали покретни преглед са "
    L"односом страница монитора; његов положај се чува. Распореди у мрежу не премешта ту врсту "
    L"виџета. Esc скрива сат и уклања затамњење и када су Подешавања отворена.\r\n\r\nПоказивач "
    L"миша скрива се после кратке неактивности изнад сата на монитору и затамњених монитора, а "
    L"појављује при померању миша. Изнад малог прегледа остаје видљив.",
    L"\r\n\r\nГОДИННИК НА МОНІТОРІ\r\nЦифровий годинник може займати один або кілька моніторів і "
    L"за потреби затемнювати решту. Розмір шрифту задається у відсотках висоти монітора; також "
    L"можна налаштувати шрифт, згладжування, кольори та внутрішні відступи. У режимі UTC напис "
    L"UTC можна показувати окремим рядком. Типовий вигляд — білий текст на чорному тлі. Поки "
    L"відкрито налаштування, годинник показується як невелике рухоме вікно попереднього перегляду "
    L"зі збереженням пропорцій монітора; його положення зберігається. Упорядкування за сіткою не "
    L"переміщує цей тип віджета. Esc приховує годинник і прибирає затемнення навіть із відкритим "
    L"вікном налаштувань.\r\n\r\nВказівник миші приховується після короткої бездіяльності над "
    L"годинником на моніторі та затемненими моніторами й з’являється знову під час руху миші. Над "
    L"малим вікном попереднього перегляду він залишається видимим.",
    L"\r\n\r\nЧАСЫ НА МОНИТОРЕ\r\nЦифровые часы могут занимать один или несколько мониторов и при "
    L"необходимости затемнять остальные. Размер шрифта задаётся в процентах высоты монитора; также "
    L"можно настроить шрифт, сглаживание, цвета и внутренние отступы. В режиме UTC надпись UTC "
    L"можно показывать отдельной строкой. Вид по умолчанию — белый текст на чёрном фоне. Пока "
    L"открыты настройки, часы показываются в небольшом перемещаемом окне предварительного "
    L"просмотра с сохранением пропорций монитора; его положение сохраняется. Упорядочение по сетке "
    L"не перемещает этот тип виджета. Esc скрывает часы и убирает затемнение даже при открытом "
    L"окне настроек.\r\n\r\nУказатель мыши скрывается после короткого бездействия над часами на "
    L"мониторе и затемнёнными мониторами и появляется снова при движении мыши. Над небольшим окном "
    L"предварительного просмотра он остаётся видимым."
};

const wchar_t* ABOUT_TEXT[LANG_COUNT] = {
    L"Hodiny a kalendáře\r\n\r\nNativní Win32 aplikace pro až 32 samostatně nastavených "
    L"plovoucích hodin a kalendářů.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for up to 32 independently "
    L"configured floating clocks and calendars.",
    L"Uhren und Kalender\r\n\r\nNative Win32-Anwendung für bis zu 32 unabhängig konfigurierte "
    L"schwebende Uhren und Kalender.",
    L"Horloges et calendriers\r\n\r\nApplication Win32 native pour plusieurs horloges et "
    L"calendriers flottants configurés séparément.",
    L"Relojes y calendarios\r\n\r\nAplicación Win32 nativa para varios relojes y calendarios "
    L"flotantes configurados por separado.",
    L"Orologi e calendari\r\n\r\nApplicazione Win32 nativa per più orologi e calendari mobili "
    L"configurati separatamente.",
    L"Zegary i kalendarze\r\n\r\nNatywna aplikacja Win32 obsługująca wiele niezależnie "
    L"skonfigurowanych zegarów i kalendarzy.",
    L"Hodiny a kalendáre\r\n\r\nNatívna aplikácia Win32 pre najviac 32 samostatne nastavených "
    L"plávajúcich hodín a kalendárov.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for up to 32 independently "
    L"configured floating clocks and calendars.",
    L"Clocks and calendars\r\n\r\nA native Win32 application for up to 32 independently "
    L"configured floating clocks and calendars.",
    L"Relógios e calendários\r\n\r\nAplicação Win32 nativa para até 32 relógios e calendários "
    L"flutuantes configurados independentemente.",
    L"Klokker og kalendere\r\n\r\nEt Win32-program for opptil 32 flytende klokker og kalendere "
    L"med separate innstillinger.",
    L"Klockor och kalendrar\r\n\r\nEtt Win32-program för upp till 32 flytande klockor och "
    L"kalendrar med separata inställningar.",
    L"Kellot ja kalenterit\r\n\r\nNatiivi Win32-sovellus enintään 32 erikseen määritettävälle "
    L"kelluvalle kellolle ja kalenterille.",
    L"Ure og kalendere\r\n\r\nEt Win32-program til op til 32 flydende ure og kalendere med "
    L"separate indstillinger.",
    L"Klukkur og dagatöl\r\n\r\nWin32-forrit fyrir allt að 32 fljótandi klukkur og dagatöl með "
    L"sjálfstæðum stillingum.",
    L"Saatler ve takvimler\r\n\r\nBağımsız olarak yapılandırılan en fazla 32 kayan saat ve takvim "
    L"için yerel bir Win32 uygulaması.",
    L"Kellad ja kalendrid\r\n\r\nWin32-rakendus kuni 32 eraldi seadistatava hõljuva kella ja "
    L"kalendri jaoks.",
    L"Cloig agus féilirí\r\n\r\nFeidhmchlár dúchasach Win32 le haghaidh suas le 32 clog agus "
    L"féilire ar snámh ar féidir iad a chumrú go neamhspleách.",
    L"Laikrodžiai ir kalendoriai\r\n\r\nWin32 programa, rodanti iki 32 atskirai nustatomų "
    L"slankiųjų laikrodžių ir kalendorių.",
    L"Pulksteņi un kalendāri\r\n\r\nWin32 programma līdz 32 neatkarīgi iestatāmiem peldošiem "
    L"pulksteņiem un kalendāriem.",
    L"Órák és naptárak\r\n\r\nNatív Win32-alkalmazás legfeljebb 32, egymástól függetlenül "
    L"beállítható lebegő órával és naptárral.",
    L"Arloġġi u kalendarji\r\n\r\nApplikazzjoni nattiva Win32 għal sa 32 arloġġ u kalendarju li "
    L"jżommu fuq id-desktop u jistgħu jiġu kkonfigurati separatament.",
    L"Klokken en kalenders\r\n\r\nEen native Win32-toepassing voor maximaal 32 afzonderlijk "
    L"instelbare zwevende klokken en kalenders.",
    L"Ceasuri și calendare\r\n\r\nAplicație nativă Win32 pentru până la 32 de ceasuri și "
    L"calendare flotante, configurabile independent.",
    L"Ρολόγια και ημερολόγια\r\n\r\nΕγγενής εφαρμογή Win32 για έως 32 ανεξάρτητα ρυθμιζόμενα "
    L"αιωρούμενα ρολόγια και ημερολόγια.",
    L"Satovi i kalendari\r\n\r\nIzvorni Win32 program za do 32 nezavisno podesiva plutajuća sata "
    L"i kalendara.",
    L"Satovi i kalendari\r\n\r\nIzvorni Win32 program za do 32 neovisno podesiva plutajuća sata i "
    L"kalendara.",
    L"Ure in koledarji\r\n\r\nIzvorni program Win32 za do 32 neodvisno nastavljenih plavajočih ur "
    L"in koledarjev.",
    L"Satovi i kalendari\r\n\r\nIzvorna Win32 aplikacija za do 32 nezavisno podešena plutajuća "
    L"sata i kalendara.",
    L"Гадзіннікі і календары\r\n\r\nПраграма Win32 для паказу да 32 незалежна наладжаных рухомых "
    L"гадзіннікаў і календароў.",
    L"Часовници и календари\r\n\r\nПриложение Win32 за до 32 независимо настроени плаващи "
    L"часовника и календара.",
    L"Часовници и календари\r\n\r\nПрограма Win32 за до 32 независно поставени лебдечки часовници "
    L"и календари.",
    L"Сатови и календари\r\n\r\nИзворна Win32 апликација за до 32 независно подешена плутајућа "
    L"сата и календара.",
    L"Годинники та календарі\r\n\r\nПрограма Win32 для показу до 32 незалежно налаштованих "
    L"рухомих годинників і календарів.",
    L"Часы и календари\r\n\r\nПрограмма Win32 для показа до 32 независимо настроенных перемещаемых "
    L"часов и календарей."
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
    L"Chcete před zavřením uložit změny nastavení?\r\n\r\nPokud je neuložíte, všechny neuložené "
    L"změny budou ztraceny.",
    L"Do you want to save changes to the settings before closing?\r\n\r\nIf you do not save them, "
    L"all unsaved changes will be lost.",
    L"Möchten Sie die Änderungen an den Einstellungen vor dem Schließen speichern?\r\n\r\nWenn "
    L"Sie sie nicht speichern, gehen alle ungespeicherten Änderungen verloren.",
    L"Voulez-vous enregistrer les modifications des paramètres avant de fermer ?\r\n\r\nSinon, "
    L"toutes les modifications non enregistrées seront perdues.",
    L"¿Desea guardar los cambios en la configuración antes de cerrar?\r\n\r\nSi no los guarda, se "
    L"perderán todos los cambios sin guardar.",
    L"Salvare le modifiche alle impostazioni prima di chiudere?\r\n\r\nSe non vengono salvate, "
    L"tutte le modifiche non salvate andranno perse.",
    L"Czy zapisać zmiany w ustawieniach przed zamknięciem?\r\n\r\nJeśli ich nie zapiszesz, "
    L"wszystkie niezapisane zmiany zostaną utracone.",
    L"Chcete pred zatvorením uložiť zmeny nastavení?\r\n\r\nAk ich neuložíte, všetky neuložené "
    L"zmeny sa stratia.",
    L"Do you want to save changes to the settings before closing?\r\n\r\nIf you do not save them, "
    L"all unsaved changes will be lost.",
    L"Do you want to save changes to the settings before closing?\r\n\r\nIf you do not save them, "
    L"all unsaved changes will be lost.",
    L"Pretende guardar as alterações às definições antes de fechar?\r\n\r\nSe não as guardar, "
    L"todas as alterações não guardadas serão perdidas.",
    L"Vil du lagre endringene i innstillingene før du lukker?\r\n\r\nHvis du ikke lagrer dem, går "
    L"alle ulagrede endringer tapt.",
    L"Vill du spara ändringarna i inställningarna innan du stänger?\r\n\r\nOm du inte sparar dem "
    L"går alla osparade ändringar förlorade.",
    L"Haluatko tallentaa asetuksiin tehdyt muutokset ennen sulkemista?\r\n\r\nJos et tallenna "
    L"niitä, kaikki tallentamattomat muutokset menetetään.",
    L"Vil du gemme ændringerne i indstillingerne, før du lukker?\r\n\r\nHvis du ikke gemmer dem, "
    L"går alle ændringer, der ikke er gemt, tabt.",
    L"Viltu vista breytingar á stillingum áður en þú lokar?\r\n\r\nEf þú vistar þær ekki glatast "
    L"allar óvistaðar breytingar.",
    L"Kapatmadan önce ayarlardaki değişiklikleri kaydetmek istiyor musunuz?\r\n\r\nKaydetmezseniz "
    L"kaydedilmemiş tüm değişiklikler kaybolacak.",
    L"Kas soovite enne sulgemist sätete muudatused salvestada?\r\n\r\nKui te neid ei salvesta, "
    L"lähevad kõik salvestamata muudatused kaotsi.",
    L"Ar mhaith leat na hathruithe ar na socruithe a shábháil roimh dhúnadh?\r\n\r\nMura "
    L"sábhálann tú iad, caillfear gach athrú gan sábháil.",
    L"Ar norite prieš uždarydami įrašyti parametrų pakeitimus?\r\n\r\nJei jų neįrašysite, visi "
    L"neįrašyti pakeitimai bus prarasti.",
    L"Vai pirms aizvēršanas saglabāt iestatījumu izmaiņas?\r\n\r\nJa tās nesaglabāsiet, visas "
    L"nesaglabātās izmaiņas tiks zaudētas.",
    L"Szeretné menteni a beállítások módosításait bezárás előtt?\r\n\r\nHa nem menti őket, minden "
    L"nem mentett módosítás elvész.",
    L"Trid tissejvja l-bidliet fis-settings qabel tagħlaq?\r\n\r\nJekk ma tissejvjahomx, jintilfu "
    L"l-bidliet kollha mhux issejvjati.",
    L"Wilt u de wijzigingen in de instellingen opslaan voordat u sluit?\r\n\r\nAls u ze niet "
    L"opslaat, gaan alle niet-opgeslagen wijzigingen verloren.",
    L"Doriți să salvați modificările setărilor înainte de închidere?\r\n\r\nDacă nu le salvați, "
    L"toate modificările nesalvate se vor pierde.",
    L"Θέλετε να αποθηκεύσετε τις αλλαγές στις ρυθμίσεις πριν από το κλείσιμο;\r\n\r\nΑν δεν τις "
    L"αποθηκεύσετε, όλες οι μη αποθηκευμένες αλλαγές θα χαθούν.",
    L"Želite li sačuvati promjene postavki prije zatvaranja?\r\n\r\nAko ih ne sačuvate, sve "
    L"nesačuvane promjene bit će izgubljene.",
    L"Želite li spremiti promjene postavki prije zatvaranja?\r\n\r\nAko ih ne spremite, sve "
    L"nespremljene promjene bit će izgubljene.",
    L"Ali želite pred zapiranjem shraniti spremembe nastavitev?\r\n\r\nČe jih ne shranite, bodo "
    L"vse neshranjene spremembe izgubljene.",
    L"Želite li sačuvati izmjene podešavanja prije zatvaranja?\r\n\r\nAko ih ne sačuvate, sve "
    L"nesačuvane izmjene biće izgubljene.",
    L"Захаваць змены налад перад закрыццём?\r\n\r\nКалі іх не захаваць, усе незахаваныя змены "
    L"будуць страчаны.",
    L"Искате ли да запишете промените в настройките преди затваряне?\r\n\r\nАко не ги запишете, "
    L"всички незаписани промени ще бъдат загубени.",
    L"Дали сакате да ги зачувате промените на поставките пред затворање?\r\n\r\nАко не ги "
    L"зачувате, сите незачувани промени ќе бидат изгубени.",
    L"Желите ли да сачувате измене подешавања пре затварања?\r\n\r\nАко их не сачувате, све "
    L"несачуване измене биће изгубљене.",
    L"Зберегти зміни налаштувань перед закриттям?\r\n\r\nЯкщо їх не зберегти, усі незбережені "
    L"зміни буде втрачено.",
    L"Сохранить изменения настроек перед закрытием?\r\n\r\nЕсли их не сохранить, все несохранённые "
    L"изменения будут потеряны."
};

/// Returns localized monitor-detail column captions and bit-depth formats.
MonitorColumnText MonitorColumnsText(AppLanguage language) {
    const wchar_t* const* headings = MONITOR_COLUMN_LABELS[language];
    const wchar_t* const* formats = MONITOR_DEPTH_FORMATS[language];
    return MonitorColumnText{
        headings[1],
        headings[3],
        headings[4],
        headings[5],
        headings[6],
        formats[0],
        formats[1]
    };
}

/// Formats an initial additional-clock name; callers preserve stored empty names
/// instead of replacing them.
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
        LANGUAGE_LOCALES[LANG_CNR] =
            IsValidLocaleName(L"sr-Latn-RS") ? L"sr-Latn-RS" : L"sr-Latn-CS";
    }
}
