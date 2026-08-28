#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "resource.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <windowsx.h>
#include <algorithm>
#include <atomic>
#include <climits>
#include <cmath>
#include <commctrl.h>
#include <commdlg.h>
#include <cstring>
#include <cwctype>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <memory>
#include <mmsystem.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <string>
#include <utility>
#include <uxtheme.h>
#include <vector>
#include <winhttp.h>
#include <xmllite.h>

#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "D2d1.lib")
#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Winhttp.lib")
#pragma comment(lib, "UxTheme.lib")
#pragma comment(lib, "XmlLite.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

enum WidgetType {
    WIDGET_ANALOG,
    WIDGET_DIGITAL,
    WIDGET_CALENDAR,
    WIDGET_PANEL,
    WIDGET_FULLSCREEN,
    WIDGET_TYPE_COUNT
};
enum DigitalBorderStyle {
    DIGITAL_BORDER_NONE,
    DIGITAL_BORDER_TOOL_WINDOW,
    DIGITAL_BORDER_SINGLE,
    DIGITAL_BORDER_3D,
    DIGITAL_BORDER_STYLE_COUNT
};
enum FontAntialiasing {
    FONT_ANTIALIAS_GDI,
    FONT_ANTIALIAS_CLEARTYPE,
    FONT_ANTIALIAS_COUNT
};

const int DIGITAL_BORDER_WIDTH_MAX = 10;
enum AppLanguage {
    LANG_CZ,
    LANG_EN,
    LANG_DE,
    LANG_FR,
    LANG_ES,
    LANG_IT,
    LANG_PL,
    LANG_SK,
    LANG_COUNT
};
enum NtpPreset {
    NTP_PRESET_AUTO,
    NTP_PRESET_CESNET,
    NTP_PRESET_PTB,
    NTP_PRESET_GLOBAL,
    NTP_PRESET_CUSTOM,
    NTP_PRESET_COUNT
};
enum DateCopyFormat {
    DATE_YYMMDD,
    DATE_YYYYMMDD,
    DATE_YY_MM_DD,
    DATE_ISO,
    DATE_LOCAL_SHORT,
    DATE_DD_MM_YYYY,
    DATE_DAY_SHORT_MONTH,
    DATE_DAY_MONTH,
    DATE_WEEKDAY,
    DATE_LOCAL_LONG,
    DATE_RFC,
    DATE_SLASH,
    DATE_FORMAT_COUNT
};
enum TextId {
    TXT_APP,
    TXT_SETTINGS,
    TXT_ADD,
    TXT_REMOVE,
    TXT_DUPLICATE,
    TXT_GENERAL,
    TXT_APPEARANCE,
    TXT_ALARM,
    TXT_NAME,
    TXT_TYPE,
    TXT_VISIBLE,
    TXT_TOPMOST,
    TXT_SECONDS,
    TXT_UTC,
    TXT_TIMEZONE,
    TXT_OFFSET,
    TXT_SIZE,
    TXT_OPACITY,
    TXT_FONT_SIZE,
    TXT_LEADING_ZERO,
    TXT_TRANSPARENT_BG,
    TXT_TEXT_COLOR,
    TXT_BACKGROUND_COLOR,
    TXT_WEEK_NUMBERS,
    TXT_SUNDAY_FIRST,
    TXT_ALARM_ACTIVE,
    TXT_ALARM_TIME,
    TXT_RUN_FILE,
    TXT_LOOP_AUDIO,
    TXT_BROWSE,
    TXT_LANGUAGE,
    TXT_VISUAL_STYLES,
    TXT_SAVE,
    TXT_APPLY,
    TXT_CANCEL,
    TXT_SHOW_ALL,
    TXT_HIDE_ALL,
    TXT_STOP_ALARM,
    TXT_HELP,
    TXT_ABOUT,
    TXT_EXIT,
    TXT_ANALOG,
    TXT_DIGITAL,
    TXT_CALENDAR,
    TXT_PANEL,
    TXT_INVALID_OFFSET,
    TXT_INVALID_TIME,
    TXT_DELETE_CONFIRM,
    TXT_AT_LEAST_ONE,
    TXT_CLOSE,
    TXT_COUNT
};

const wchar_t* TEXT[LANG_COUNT][TXT_COUNT] = { {L"Hodiny a kalendáře",
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
                                               L"Zavřít"},
                                              {L"Clocks and calendars",
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
                                               L"Close"},
                                              {L"Uhren und Kalender",
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
                                               L"Schließen"},
                                              {L"Horloges et calendriers",
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
                                               L"Fermer"},
                                              {L"Relojes y calendarios",
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
                                               L"Cerrar"},
                                              {L"Orologi e calendari",
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
                                               L"Chiudi"},
                                              {L"Zegary i kalendarze",
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
                                               L"Zamknij"},
                                              {L"Hodiny a kalendáre",
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
                                               L"Zavrieť"} };

struct FontSelection {
    std::wstring face = L"Segoe UI";
    int dialogSize = 90;
    int weight = FW_NORMAL;
    bool italic = false;
    bool underline = false;
    bool strikeOut = false;
    BYTE charSet = DEFAULT_CHARSET;
};

struct WidgetConfig {
    int id = 0;
    WidgetType type = WIDGET_ANALOG;
    std::wstring name;
    bool visible = false;
    bool topMost = false;
    bool showSeconds = false;
    bool showUtc = false;
    bool showUtcText = false;
    AppLanguage language = LANG_CZ;
    std::wstring timeZoneKey;
    std::wstring monitorDevices;
    bool blackoutOtherMonitors = true;
    LONGLONG offsetMilliseconds = 0;
    int x = 0;
    int y = 0;
    int previewX = CW_USEDEFAULT;
    int previewY = CW_USEDEFAULT;
    int size = 0;
    int opacity = 0;
    int fontSize = 0;
    int fontDialogSize = 90;
    int fontAntialiasing = FONT_ANTIALIAS_CLEARTYPE;
    bool leadingZero = false;
    bool transparentBackground = false;
    bool disableThemes = false;
    std::wstring fontFace = L"Segoe UI";
    int fontWeight = FW_NORMAL;
    bool fontItalic = false;
    bool fontUnderline = false;
    bool fontStrikeOut = false;
    BYTE fontCharSet = DEFAULT_CHARSET;
    FontSelection panelTopFont;
    FontSelection panelTimeFont;
    FontSelection panelBottomFont;
    int padding = 8;
    int borderStyle = DIGITAL_BORDER_SINGLE;
    int borderWidth = 1;
    COLORREF textColor = 0;
    COLORREF backgroundColor = 0;
    COLORREF alarmTextColor = RGB(220, 0, 0);
    COLORREF alarmBackgroundColor = RGB(255, 255, 128);
    bool weekNumbers = false;
    bool sundayFirst = false;
    int dateCopyFormat = DATE_YYMMDD;
    bool alarmEnabled = false;
    int alarmHour = 0;
    int alarmMinute = 0;
    bool runCommand = false;
    bool loopAudio = false;
    std::wstring command;
    bool callRemoteScript = false;
    std::wstring remoteScriptUrl;
};

struct SettingsSnapshot {
    AppLanguage language = LANG_EN;
    bool themesDisabled = false;
    int fontAntialiasing = FONT_ANTIALIAS_CLEARTYPE;
    std::wstring fontFace;
    int fontDialogSize = 90;
    int fontWeight = FW_NORMAL;
    bool fontItalic = false;
    bool useNtpTime = true;
    int ntpPreset = NTP_PRESET_AUTO;
    std::wstring ntpServers;
    int settingsX = CW_USEDEFAULT;
    int settingsY = CW_USEDEFAULT;
    int helpX = CW_USEDEFAULT;
    int helpY = CW_USEDEFAULT;
    int aboutX = CW_USEDEFAULT;
    int aboutY = CW_USEDEFAULT;
    std::vector<WidgetConfig> widgets;
};

struct NtpThreadResult {
    bool success = false;
    LONGLONG offset100Nanoseconds = 0;
    std::wstring server;
    ULONG generation = 0;
};

struct NtpThreadParameters {
    std::wstring serverList;
    ULONG generation = 0;
};

struct NtpSample {
    LONGLONG offset100Nanoseconds = 0;
    LONGLONG delay100Nanoseconds = 0;
    std::wstring server;
};

struct AudioThreadParameters {
    std::wstring path;
    bool loop = false;
    HANDLE stopEvent = nullptr;
    HWND notifyWindow = nullptr;
    UINT notifyMessage = 0;
    int widgetId = -1;
    ULONG generation = 0;
};

struct LocalCommandThreadParameters {
    std::wstring command;
};

struct RemoteScriptThreadParameters {
    std::wstring url;
};

struct Widget {
    WidgetConfig config;
    HWND window = nullptr;
    HWND analogChild = nullptr;
    WNDPROC analogProc = nullptr;
    HWND calendarChild = nullptr;
    WNDPROC calendarProc = nullptr;
    HFONT calendarFont = nullptr;
    std::vector<HWND> fullscreenWindows;
    bool fullscreenPreview = false;
    bool dragging = false;
    POINT dragOffset = {};
    bool rendered = false;
    bool alarmActive = false;
    bool flashPhase = false;
    int lastAlarmDate = -1;
    int lastAlarmMinute = -1;
    int lastRenderKey = -1;
    int lastPanelDateKey = -1;
    COLORREF analogBackground = CLR_INVALID;
    HANDLE audioStopEvent = nullptr;
    ULONG audioGeneration = 0;
    ULONGLONG alarmStoppedTick = 0;
    bool identifyActive = false;
    bool identifyPhase = false;
    bool identifyRestoreHidden = false;
    bool identifyRestoreNotTopmost = false;
    ULONGLONG identifyEndTick = 0;
    HWND copyTooltip = nullptr;
    std::wstring copyTooltipText;
    ULONGLONG copyTooltipEndTick = 0;
    ULONGLONG lastAnalogClickTick = 0;
    POINT lastAnalogClickPoint = {};
};

struct DisplayMonitor {
    HMONITOR handle = nullptr;
    RECT rect = {};
    std::wstring device;
    bool primary = false;
};

HINSTANCE hInstance = nullptr;
HMODULE hTimeDate = nullptr;
HANDLE hSingleInstanceMutex = nullptr;
HWND hController = nullptr;
HWND hSettings = nullptr;
HWND hHelp = nullptr;
HWND hAbout = nullptr;
NOTIFYICONDATAW trayIcon = {};
HFONT hUiFont = nullptr;
HFONT hAboutFont = nullptr;
UINT taskbarCreatedMessage = 0;
thread_local LCID activeCalendarLocale = 0;
typedef LCID(WINAPI* GetUserDefaultLcidProc)();
typedef int(WINAPI* GetLocaleInfoWProc)(LCID locale, LCTYPE type, LPWSTR data, int characters);
typedef int(WINAPI* GetCalendarInfoWProc)(LCID locale, CALID calendar, CALTYPE type, LPWSTR data, int characters, LPDWORD value);
typedef int(WINAPI* GetCalendarInfoExProc)(LPCWSTR localeName, CALID calendar, LPCWSTR reserved, CALTYPE type, LPWSTR data, int characters, LPDWORD value);
typedef int(WINAPI* GetCalendarDateFormatProc)(CALID calendar, DWORD flags, const void* calendarDate, LPCWSTR format, LPWSTR data, int characters);
typedef BOOL(WINAPI* ConvertCalDateTimeToSystemTimeProc)(const void* calendarDate, SYSTEMTIME* systemTime);
GetUserDefaultLcidProc originalGetUserDefaultLcid = nullptr;
GetLocaleInfoWProc originalGetLocaleInfoW = nullptr;
GetCalendarInfoWProc originalGetCalendarInfoW = nullptr;
GetCalendarInfoExProc originalGetCalendarInfoEx = nullptr;
GetCalendarDateFormatProc originalGetCalendarDateFormat = nullptr;
ConvertCalDateTimeToSystemTimeProc convertCalDateTimeToSystemTime = nullptr;
AppLanguage appLanguage = LANG_EN;
bool themesDisabled = false;
int appFontAntialiasing = FONT_ANTIALIAS_CLEARTYPE;
std::wstring appFontFace;
int appFontDialogSize = 90;
int appFontWeight = FW_NORMAL;
bool appFontItalic = false;
std::wstring settingsAppFontFace;
int settingsAppFontDialogSize = 90;
int settingsAppFontWeight = FW_NORMAL;
bool settingsAppFontItalic = false;
ID2D1Factory* d2dFactory = nullptr;
IDWriteFactory* dwriteFactory = nullptr;
bool storageUsesXml = false;
bool useNtpTime = true;
bool winsockReady = false;
int ntpPreset = NTP_PRESET_AUTO;
std::wstring ntpServers;
std::wstring ntpActiveServer;
bool ntpLastQueryFailed = false;
std::atomic<LONGLONG> ntpOffset100Nanoseconds = 0;
std::atomic<bool> ntpTimeValid = false;
std::atomic<bool> ntpQueryRunning = false;
std::atomic<bool> ntpStopRequested = false;
std::atomic<ULONG> ntpGeneration = 0;
ULONGLONG lastNtpAttemptTick = 0;
HANDLE hNtpThread = nullptr;
int settingsX = CW_USEDEFAULT;
int settingsY = CW_USEDEFAULT;
int helpX = CW_USEDEFAULT;
int helpY = CW_USEDEFAULT;
int aboutX = CW_USEDEFAULT;
int aboutY = CW_USEDEFAULT;
int nextWidgetId = 1;
int selectedDraftIndex = 0;
ULONGLONG lastTrayToggleTick = 0;
std::vector<std::unique_ptr<Widget>> widgets;
std::vector<DisplayMonitor> displayMonitors;
std::vector<HWND> blackoutWindows;
std::vector<WidgetConfig> settingsDraft;
std::vector<WidgetConfig> settingsAppearanceOriginals;
std::vector<int> settingsAppearancePreviewIds;
bool settingsAppearancePreviewActive = false;
bool settingsApplicationFontPreviewActive = false;
std::vector<DYNAMIC_TIME_ZONE_INFORMATION> timeZones;

const wchar_t CLASS_NAME[] = L"CalClockMultiWidgetWindow";
const wchar_t BLACKOUT_CLASS_NAME[] = L"CalClockBlackoutWindow";
const wchar_t CONTROLLER_TITLE[] = L"CalClockMessageController";
const wchar_t REGISTRY_PATH[] = L"Software\\FortSoft\\CalClock";
const wchar_t VENDOR_REGISTRY_PATH[] = L"Software\\FortSoft";
const UINT WM_TRAYICON = WM_APP + 1;
const UINT WM_SHOW_EXISTING = WM_APP + 2;
const UINT WM_ANALOG_SETTIME = WM_USER + 1;
const UINT WM_NTP_RESULT = WM_APP + 3;
const UINT WM_AUDIO_FINISHED = WM_APP + 4;
const UINT WM_SETTINGS_AUDIO_FINISHED = WM_APP + 5;
const UINT WM_REFRESH_DISPLAYS = WM_APP + 6;
const UINT_PTR TIMER_REFRESH = 1;
const COLORREF IDENTIFY_COLOR = RGB(80, 190, 255);

const int ID_MENU_SETTINGS = 1001;
const int ID_MENU_VISIBLE = 1002;
const int ID_MENU_TOPMOST = 1003;
const int ID_MENU_SECONDS = 1004;
const int ID_MENU_STOP_ALARM = 1005;
const int ID_MENU_SIZE_104 = 1010;
const int ID_MENU_SIZE_130 = 1011;
const int ID_MENU_SIZE_166 = 1012;
const int ID_MENU_SIZE_198 = 1013;
const int ID_MENU_DATE_FORMAT_BASE = 1060;
const int ID_MENU_ARRANGE_WIDGETS = 1080;
const int ID_MENU_SHOW_ALL = 1020;
const int ID_MENU_HIDE_ALL = 1021;
const int ID_MENU_HELP = 1022;
const int ID_MENU_ABOUT = 1023;
const int ID_MENU_EXIT = 1024;
const int ID_MENU_WIDGET_BASE = 2000;

const int ID_LIST_WIDGETS = 3001;
const int ID_ADD_TYPE = 3002;
const int ID_ADD = 3003;
const int ID_REMOVE = 3004;
const int ID_DUPLICATE = 3005;
const int ID_TABS = 3006;
const int ID_NAME = 3010;
const int ID_TYPE = 3011;
const int ID_VISIBLE = 3012;
const int ID_TOPMOST = 3013;
const int ID_SECONDS = 3014;
const int ID_UTC = 3015;
const int ID_TIMEZONE = 3016;
const int ID_OFFSET = 3017;
const int ID_WIDGET_LANGUAGE = 3018;
const int ID_UTC_TEXT = 3019;
const int ID_BLACKOUT_MONITORS = 3070;
const int ID_MONITOR_LIST = 3071;
const int ID_SIZE = 3020;
const int ID_OPACITY = 3021;
const int ID_FONT_SIZE = 3022;
const int ID_LEADING_ZERO = 3023;
const int ID_TRANSPARENT_BG = 3024;
const int ID_TEXT_COLOR = 3025;
const int ID_BACKGROUND_COLOR = 3026;
const int ID_WEEK_NUMBERS = 3027;
const int ID_SUNDAY_FIRST = 3028;
const int ID_DATE_FORMAT = 3029;
const int ID_FONT = 3052;
const int ID_ALARM_TEXT_COLOR = 3053;
const int ID_ALARM_BACKGROUND_COLOR = 3054;
const int ID_PADDING = 3055;
const int ID_BORDER = 3056;
const int ID_WIDGET_DISABLE_THEMES = 3057;
const int ID_DEFAULT_APPEARANCE = 3058;
const int ID_BORDER_WIDTH = 3059;
const int ID_WIDGET_ANTIALIAS = 3072;
const int ID_PANEL_TOP_FONT = 3073;
const int ID_PANEL_TIME_FONT = 3074;
const int ID_PANEL_BOTTOM_FONT = 3075;
const int ID_ALARM_ENABLED = 3030;
const int ID_ALARM_TIME = 3031;
const int ID_RUN_COMMAND = 3032;
const int ID_COMMAND = 3033;
const int ID_BROWSE = 3034;
const int ID_LOOP_AUDIO = 3035;
const int ID_TEST_COMMAND = 3036;
const int ID_REMOTE_SCRIPT = 3037;
const int ID_REMOTE_SCRIPT_URL = 3038;
const int ID_LANGUAGE = 3040;
const int ID_VISUAL_STYLES = 3041;
const int ID_SAVE = 3042;
const int ID_APPLY = 3043;
const int ID_CANCEL = 3044;
const int ID_IMPORT_SETTINGS = 3045;
const int ID_EXPORT_SETTINGS = 3046;
const int ID_USE_XML_SETTINGS = 3047;
const int ID_APP_ANTIALIAS = 3048;
const int ID_APP_FONT = 3049;
const int ID_APP_FONT_DEFAULT = 3076;
const int ID_TIME_SOURCE = 3060;
const int ID_NTP_SERVERS = 3061;
const int ID_NTP_SYNC = 3062;
const int ID_NTP_PRESET = 3063;
const int ID_INFO_CLOSE = 3050;
const int ID_INFO_TEXT = 3051;

HWND hWidgetList = nullptr;
HWND hAddType = nullptr;
HWND hTabs = nullptr;
HWND hGeneralPage = nullptr;
HWND hAppearancePage = nullptr;
HWND hAlarmPage = nullptr;
HWND hTimePage = nullptr;
HWND hNameEdit = nullptr;
HWND hTypeCombo = nullptr;
HWND hVisibleCheck = nullptr;
HWND hTopmostCheck = nullptr;
HWND hSecondsCheck = nullptr;
HWND hUtcCheck = nullptr;
HWND hUtcTextCheck = nullptr;
HWND hTimeZoneCombo = nullptr;
HWND hMonitorLabel = nullptr;
HWND hMonitorList = nullptr;
HWND hBlackoutMonitorsCheck = nullptr;
HWND hOffsetEdit = nullptr;
HWND hWidgetLanguageCombo = nullptr;
HWND hSizeCombo = nullptr;
HWND hOpacityTrackBar = nullptr;
HWND hOpacityValue = nullptr;
HWND hFontSizeTrackBar = nullptr;
HWND hFontSizeValue = nullptr;
HWND hWidgetAntialiasLabel = nullptr;
HWND hWidgetAntialiasCombo = nullptr;
HWND hLeadingZeroCheck = nullptr;
HWND hTransparentBackgroundCheck = nullptr;
HWND hTextColorButton = nullptr;
HWND hBackgroundColorButton = nullptr;
HWND hWeekNumbersCheck = nullptr;
HWND hSundayFirstCheck = nullptr;
HWND hDateFormatLabel = nullptr;
HWND hDateFormatCombo = nullptr;
HWND hAlarmEnabledCheck = nullptr;
HWND hAlarmTimeEdit = nullptr;
HWND hRunCommandCheck = nullptr;
HWND hCommandEdit = nullptr;
HWND hBrowseButton = nullptr;
HWND hLoopAudioCheck = nullptr;
HWND hRemoteScriptCheck = nullptr;
HWND hRemoteScriptEdit = nullptr;
HWND hLanguageCombo = nullptr;
HWND hDisableThemesCheck = nullptr;
HWND hUseXmlSettingsCheck = nullptr;
HWND hAppAntialiasCombo = nullptr;
HWND hAppFontButton = nullptr;
HWND hAppFontDefaultButton = nullptr;
HWND hTimeSourceCombo = nullptr;
HWND hNtpPresetCombo = nullptr;
HWND hNtpServersEdit = nullptr;
HWND hNtpStatus = nullptr;
HWND hNtpSyncButton = nullptr;
HWND hSizeLabel = nullptr;
HWND hOpacityLabel = nullptr;
HWND hFontSizeLabel = nullptr;
HWND hFontButton = nullptr;
HWND hPanelTopFontButton = nullptr;
HWND hPanelTimeFontButton = nullptr;
HWND hPanelBottomFontButton = nullptr;
HWND hFontDescription = nullptr;
HWND hAlarmTextColorButton = nullptr;
HWND hAlarmBackgroundColorButton = nullptr;
HWND hPaddingLabel = nullptr;
HWND hPaddingTrackBar = nullptr;
HWND hPaddingValue = nullptr;
HWND hBorderLabel = nullptr;
HWND hBorderTrackBar = nullptr;
HWND hBorderWidthLabel = nullptr;
HWND hBorderWidthTrackBar = nullptr;
HWND hBorderWidthValue = nullptr;
bool updatingNtpPresetControls = false;
bool displayRefreshPending = false;
HWND hWidgetDisableThemesCheck = nullptr;
HWND hDefaultAppearanceButton = nullptr;
HWND hTestCommandButton = nullptr;
HANDLE settingsPreviewStopEvent = nullptr;
ULONG settingsPreviewGeneration = 0;
int settingsVisualPreviewWidgetId = -1;
bool settingsVisualPreviewActive = false;
static HWND lastClickedEdit = nullptr;
static DWORD lastEditClickTick = 0;
static POINT lastEditClickPoint = {};
static int editClickCount = 0;
std::vector<HWND> generalControls;
std::vector<HWND> appearanceControls;
std::vector<HWND> alarmControls;
std::vector<HWND> timeControls;

typedef UINT(__fastcall* RegisterClockClassProc)(HINSTANCE);
typedef void(__fastcall* RenderClockProc)(void* state, void* unused, HDC targetDC);
RegisterClockClassProc registerClockClass = nullptr;
RenderClockProc renderClock = nullptr;
DWORD* analogProfile198 = nullptr;
DWORD* activeAnalogProfile = nullptr;

static LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK AnalogChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK CalendarChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK EditSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR referenceData);
static LRESULT CALLBACK WidgetListSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR referenceData);
static void RenderWidget(Widget* widget);
static void SaveAllSettings();
static void ShowSettingsWindow(int widgetId = -1);
static void SynchronizeOpenSettings(const Widget* widget);
static void RefreshInformationWindows();
static HFONT CreateWidgetDrawingFont(const WidgetConfig& config);
static void StopSettingsPreview();
static void UpdateFontDescription(const WidgetConfig& config);
static void ApplyUiStyle(HWND window);
static void PreviewSelectedWidgetAppearance(bool structuralChange);
static void RestoreSettingsAppearancePreview();
static void RefreshFullscreenPresentation();
static Widget* FindWidgetById(int id);
static HFONT CreateCalendarUiFont(const WidgetConfig& config);

static const wchar_t* T(TextId id) {
    return TEXT[appLanguage][id];
}
static const wchar_t* TypeName(WidgetType type) {
    static const wchar_t* fullscreenNames[LANG_COUNT] = { L"Hodiny na monitoru", L"Monitor clock",       L"Monitoruhr",         L"Horloge sur moniteur",
                                                         L"Reloj de monitor",   L"Orologio su monitor", L"Zegar na monitorze", L"Hodiny na monitore" };
    if (type == WIDGET_FULLSCREEN) {
        return fullscreenNames[appLanguage];
    }
    return T(static_cast<TextId>(TXT_ANALOG + static_cast<int>(type)));
}
const wchar_t* LANGUAGE_NAMES[LANG_COUNT] = { L"Čeština", L"English", L"Deutsch", L"Français", L"Español", L"Italiano", L"Polski", L"Slovenčina" };
const wchar_t* LANGUAGE_LOCALES[LANG_COUNT] = { L"cs-CZ", L"en-GB", L"de-DE", L"fr-FR", L"es-ES", L"it-IT", L"pl-PL", L"sk-SK" };
const wchar_t* WIDGET_LANGUAGE_LABELS[LANG_COUNT] = { L"Jazyk widgetu:",     L"Widget language:",   L"Widget-Sprache:", L"Langue du widget :",
                                                     L"Idioma del widget:", L"Lingua del widget:", L"Język widżetu:",  L"Jazyk widgetu:" };
const wchar_t* APPLICATION_LANGUAGE_LABELS[LANG_COUNT] = { L"&Jazyk aplikace:",     L"Application &language:", L"&Anwendungssprache:", L"&Langue de l’application :",
                                                           L"&Idioma de la aplicación:", L"&Lingua applicazione:", L"Język &aplikacji:",   L"&Jazyk aplikácie:" };
const wchar_t* APPLICATION_FONT_LABELS[LANG_COUNT] = { L"&Písmo aplikace:",       L"Application &font:",   L"Anwendungs&schrift:", L"&Police de l’application :",
                                                       L"&Fuente de la aplicación:", L"&Carattere applicazione:", L"&Czcionka aplikacji:", L"&Písmo aplikácie:" };
const wchar_t* SYSTEM_DEFAULT_FONT_LABELS[LANG_COUNT] = { L"Výchozí systémové", L"System default", L"Systemstandard", L"Valeur système",
                                                          L"Predeterminada del sistema", L"Predefinito di sistema", L"Domyślna systemowa", L"Predvolené systémové" };
const wchar_t* DATE_COPY_LABELS[LANG_COUNT] = { L"&Formát kopírovaného data", L"Copied &date format",   L"Format des kopierten &Datums", L"Format de date &copié",
                                               L"Formato de fecha &copiada", L"Formato data &copiata", L"Format &kopiowanej daty",      L"Formát &kopírovaného dátumu" };
const wchar_t* DATE_FORMAT_LABELS[LANG_COUNT] = { L"Formát &kopírovaného data:", L"Copied &date format:",   L"Format des kopierten &Datums:", L"Format de date &copié :",
                                                 L"Formato de fecha &copiada:", L"Formato data &copiata:", L"Format &kopiowanej daty:",      L"Formát &kopírovaného dátumu:" };
const wchar_t* LOCAL_SHORT_LABELS[LANG_COUNT] = { L"Krátké datum", L"Short date", L"Kurzes Datum", L"Date courte", L"Fecha corta", L"Data breve", L"Data krótka", L"Krátky dátum" };
const wchar_t* LOCAL_LONG_LABELS[LANG_COUNT] = { L"Dlouhé datum", L"Long date", L"Langes Datum", L"Date longue", L"Fecha larga", L"Data estesa", L"Data długa", L"Dlhý dátum" };
const wchar_t* ARRANGE_WIDGET_LABELS[LANG_COUNT] = { L"&Zarovnat widgety do mřížky",    L"&Arrange widgets in a grid",     L"Widgets im &Raster anordnen",
                                                    L"&Aligner les widgets en grille", L"&Alinear widgets en cuadrícula", L"&Disponi i widget in griglia",
                                                    L"&Ułóż widżety w siatce",         L"&Zarovnať widgety do mriežky" };
const wchar_t* SHOW_WIDGET_LABELS[LANG_COUNT] = { L"&Zobrazit", L"&Show", L"&Anzeigen", L"&Afficher", L"&Mostrar", L"&Mostra", L"&Pokaż", L"&Zobraziť" };
const wchar_t* HIDE_WIDGET_LABELS[LANG_COUNT] = { L"&Skrýt", L"&Hide", L"A&usblenden", L"&Masquer", L"&Ocultar", L"&Nascondi", L"&Ukryj", L"&Skryť" };
const wchar_t* UTC_TEXT_LABELS[LANG_COUNT] = { L"Zobrazit text &UTC", L"Show &UTC text",    L"&UTC-Text anzeigen", L"Afficher le texte &UTC",
                                              L"Mostrar texto &UTC", L"Mostra testo &UTC", L"Pokaż tekst &UTC",   L"Zobraziť text &UTC" };
const wchar_t* MONITOR_LABELS[LANG_COUNT] = { L"&Monitory:", L"&Monitors:", L"&Monitore:", L"&Moniteurs :", L"&Monitores:", L"&Monitor:", L"&Monitory:", L"&Monitory:" };
const wchar_t* BLACKOUT_MONITOR_LABELS[LANG_COUNT] = { L"Zatemnit &ostatní monitory",      L"Black out &other monitors",  L"&Andere Monitore abdunkeln",
                                                      L"Assombrir les &autres moniteurs", L"Oscurecer &otros monitores", L"Oscura gli &altri monitor",
                                                      L"Wygasz &pozostałe monitory",      L"Stmaviť &ostatné monitory" };
const wchar_t* FONT_BUTTON_LABELS[LANG_COUNT] = { L"Vybrat &písmo...",  L"Choose &font...",      L"&Schriftart wählen...", L"Choisir la &police...",
                                                 L"Elegir &fuente...", L"Scegli &carattere...", L"Wybierz &czcionkę...",  L"Vybrať &písmo..." };
const wchar_t* CALENDAR_FONT_LABELS[LANG_COUNT] = { L"Písmo &kalendáře...", L"&Calendar font...", L"&Kalenderschrift...", L"Police du &calendrier...",
                                                   L"Fuente del &calendario...", L"Carattere del &calendario...", L"Czcionka &kalendarza...", L"Písmo &kalendára..." };
const wchar_t* PANEL_TOP_FONT_LABELS[LANG_COUNT] = { L"Písmo &horního řádku...", L"&Top row font...", L"Schrift der &oberen Zeile...", L"Police de la ligne &supérieure...",
                                                    L"Fuente de la línea &superior...", L"Carattere riga &superiore...", L"Czcionka &górnego wiersza...", L"Písmo &horného riadka..." };
const wchar_t* PANEL_TIME_FONT_LABELS[LANG_COUNT] = { L"Písmo č&asu...", L"&Time font...", L"&Zeitschrift...", L"Police de l’&heure...", L"Fuente de la &hora...",
                                                     L"Carattere dell’&ora...", L"Czcionka &czasu...", L"Písmo č&asu..." };
const wchar_t* PANEL_BOTTOM_FONT_LABELS[LANG_COUNT] = { L"Písmo &spodního řádku...", L"&Bottom row font...", L"Schrift der &unteren Zeile...", L"Police de la ligne &inférieure...",
                                                       L"Fuente de la línea &inferior...", L"Carattere riga &inferiore...", L"Czcionka &dolnego wiersza...", L"Písmo &spodného riadka..." };
const wchar_t* DEFAULT_FONT_LABELS[LANG_COUNT] = { L"Vý&chozí", L"&Default", L"&Standard", L"Par &défaut", L"&Predeterminada", L"&Predefinito", L"&Domyślna", L"&Predvolené" };
const wchar_t* ALARM_TEXT_COLOR_LABELS[LANG_COUNT] = { L"Barva &textu budíku...",        L"Alarm &text color...",     L"&Wecker-Textfarbe...",    L"Couleur du &texte d’alarme...",
                                                      L"Color del &texto de alarma...", L"Colore &testo sveglia...", L"Kolor &tekstu alarmu...", L"Farba &textu budíka..." };
const wchar_t* ALARM_BACKGROUND_COLOR_LABELS[LANG_COUNT] = { L"Barva &pozadí budíku...", L"Alarm &background...", L"Wecker-&Hintergrund...", L"&Fond de l’alarme...",
                                                            L"&Fondo de alarma...",     L"&Sfondo sveglia...",   L"&Tło alarmu...",         L"Farba &pozadia budíka..." };
const wchar_t* PADDING_LABELS[LANG_COUNT] = { L"&Odsazení:", L"&Padding:", L"&Innenabstand:", L"&Marge interne :", L"&Relleno:", L"&Margine:", L"&Odstęp:", L"&Odsadenie:" };
const wchar_t* BORDER_LABELS[LANG_COUNT] = { L"&Styl rámečku:",    L"&Border style:", L"&Rahmenstil:", L"Style de &bordure :",
                                            L"Estilo de &borde:", L"Stile &bordo:",  L"Styl &ramki:", L"Štýl &rámčeka:" };
const wchar_t* BORDER_WIDTH_LABELS[LANG_COUNT] = { L"Šíř&ka rám.:", L"Border &width:", L"Rahmen&breite:", L"É&paisseur :",
                                                  L"&Ancho:",      L"&Spessore:",     L"&Szerokość:",    L"Šír&ka rám.:" };
const wchar_t* TIME_TAB_LABELS[LANG_COUNT] = { L"Čas", L"Time", L"Zeit", L"Heure", L"Hora", L"Ora", L"Czas", L"Čas" };
const wchar_t* TIME_SOURCE_LABELS[LANG_COUNT] = { L"&Zdroj času:",     L"Time &source:", L"Zeit&quelle:",   L"&Source de l’heure :",
                                                 L"&Origen de hora:", L"&Origine ora:", L"Źródło &czasu:", L"&Zdroj času:" };
const wchar_t* SYSTEM_TIME_LABELS[LANG_COUNT] = { L"Systémový čas Windows",    L"Windows system time",    L"Windows-Systemzeit",     L"Heure système Windows",
                                                 L"Hora del sistema Windows", L"Ora di sistema Windows", L"Czas systemowy Windows", L"Systémový čas Windows" };
const wchar_t* NTP_TIME_LABELS[LANG_COUNT] = { L"Čas ze serverů NTP",     L"Time from NTP servers", L"Zeit von NTP-Servern", L"Heure des serveurs NTP",
                                              L"Hora de servidores NTP", L"Ora dai server NTP",    L"Czas z serwerów NTP",  L"Čas zo serverov NTP" };
const wchar_t* NTP_SERVERS_LABELS[LANG_COUNT] = { L"&Servery NTP (oddělené středníkem):",           L"&NTP servers (semicolon-separated):",
                                                 L"&NTP-Server (durch Semikolon getrennt):",       L"Serveurs &NTP (séparés par des points-virgules) :",
                                                 L"Servidores &NTP (separados por punto y coma):", L"Server &NTP (separati da punto e virgola):",
                                                 L"Serwery &NTP (oddzielone średnikami):",         L"Servery &NTP (oddelené bodkočiarkou):" };
const wchar_t* NTP_PRESET_FIELD_LABELS[LANG_COUNT] = { L"Výchozí &sada:",       L"Default &set:",     L"Standard&gruppe:", L"&Jeu par défaut :", L"Conjunto &predeterminado:",
                                                      L"Gruppo &predefinito:", L"&Zestaw domyślny:", L"Predvolená &sada:" };
const wchar_t* NTP_PRESET_LABELS[LANG_COUNT][NTP_PRESET_COUNT] = {
    {L"Automaticky podle oblasti", L"Česko a Slovensko – CESNET/NIC.CZ", L"PTB – Německo a Evropa", L"Celý svět – Ubuntu / NTP Pool", L"Vlastní"},
    {L"Automatic by region", L"Czechia and Slovakia – CESNET/NIC.CZ", L"PTB – Germany and Europe", L"Worldwide – Ubuntu / NTP Pool", L"Custom"},
    {L"Automatisch nach Region", L"Tschechien und Slowakei – CESNET/NIC.CZ", L"PTB – Deutschland und Europa", L"Weltweit – Ubuntu / NTP Pool", L"Benutzerdefiniert"},
    {L"Automatique selon la région", L"Tchéquie et Slovaquie – CESNET/NIC.CZ", L"PTB – Allemagne et Europe", L"Monde entier – Ubuntu / NTP Pool", L"Personnalisé"},
    {L"Automático según la región", L"Chequia y Eslovaquia – CESNET/NIC.CZ", L"PTB – Alemania y Europa", L"Todo el mundo – Ubuntu / NTP Pool", L"Personalizado"},
    {L"Automatico in base all’area", L"Cechia e Slovacchia – CESNET/NIC.CZ", L"PTB – Germania ed Europa", L"Tutto il mondo – Ubuntu / NTP Pool", L"Personalizzato"},
    {L"Automatycznie według regionu", L"Czechy i Słowacja – CESNET/NIC.CZ", L"PTB – Niemcy i Europa", L"Cały świat – Ubuntu / NTP Pool", L"Własny"},
    {L"Automaticky podľa oblasti", L"Česko a Slovensko – CESNET/NIC.CZ", L"PTB – Nemecko a Európa", L"Celý svet – Ubuntu / NTP Pool", L"Vlastné"} };
const wchar_t* NTP_SYNC_LABELS[LANG_COUNT] = { L"&Synchronizovat nyní", L"&Synchronize now", L"Jetzt &synchronisieren", L"&Synchroniser maintenant",
                                              L"&Sincronizar ahora",   L"&Sincronizza ora", L"&Synchronizuj teraz",    L"&Synchronizovať teraz" };
const wchar_t* NTP_STATUS_SYSTEM[LANG_COUNT] = { L"Používá se systémový čas; Windows se nemění.",
                                                L"System time is used; Windows is not changed.",
                                                L"Die Systemzeit wird verwendet; Windows wird nicht geändert.",
                                                L"L’heure système est utilisée ; Windows n’est pas modifié.",
                                                L"Se usa la hora del sistema; Windows no se modifica.",
                                                L"Viene usata l’ora di sistema; Windows non viene modificato.",
                                                L"Używany jest czas systemowy; system Windows nie jest zmieniany.",
                                                L"Používa sa systémový čas; Windows sa nemení." };
const wchar_t* NTP_STATUS_WAITING[LANG_COUNT] = { L"Čeká se na synchronizaci NTP…",      L"Waiting for NTP synchronization…", L"NTP-Synchronisierung wird erwartet…",
                                                 L"Synchronisation NTP en attente…",    L"Esperando la sincronización NTP…", L"In attesa della sincronizzazione NTP…",
                                                 L"Oczekiwanie na synchronizację NTP…", L"Čaká sa na synchronizáciu NTP…" };
const wchar_t* NTP_STATUS_FAILED[LANG_COUNT] = { L"Servery NTP nejsou dostupné; dočasně se používá systémový čas.",
                                                L"NTP servers are unavailable; system time is used temporarily.",
                                                L"NTP-Server sind nicht erreichbar; vorübergehend wird die Systemzeit "
                                                L"verwendet.",
                                                L"Les serveurs NTP sont indisponibles ; l’heure système est utilisée "
                                                L"temporairement.",
                                                L"Los servidores NTP no están disponibles; se usa temporalmente la hora "
                                                L"del sistema.",
                                                L"I server NTP non sono disponibili; viene usata temporaneamente l’ora di "
                                                L"sistema.",
                                                L"Serwery NTP są niedostępne; tymczasowo używany jest czas systemowy.",
                                                L"Servery NTP nie sú dostupné; dočasne sa používa systémový čas." };
const wchar_t* NTP_STATUS_RETAINED[LANG_COUNT] = { L"Servery NTP nejsou dostupné; používá se poslední korekce v paměti:",
                                                  L"NTP servers are unavailable; the last in-memory correction is used:",
                                                  L"NTP-Server sind nicht erreichbar; die letzte Korrektur im Speicher wird "
                                                  L"verwendet:",
                                                  L"Les serveurs NTP sont indisponibles ; la dernière correction en mémoire "
                                                  L"est utilisée :",
                                                  L"Los servidores NTP no están disponibles; se usa la última corrección "
                                                  L"guardada en memoria:",
                                                  L"I server NTP non sono disponibili; viene usata l’ultima correzione in "
                                                  L"memoria:",
                                                  L"Serwery NTP są niedostępne; używana jest ostatnia korekta przechowywana "
                                                  L"w pamięci:",
                                                  L"Servery NTP nie sú dostupné; používa sa posledná korekcia v pamäti:" };
const wchar_t* NTP_STATUS_SYNCHRONIZED[LANG_COUNT] = {
    L"Synchronizováno se serverem", L"Synchronized with",  L"Synchronisiert mit",         L"Synchronisé avec", L"Sincronizado con",
    L"Sincronizzato con",           L"Zsynchronizowano z", L"Synchronizované so serverom" };
const wchar_t* ANTIALIASING_LABELS[LANG_COUNT] = { L"&Vyhlazování písma:", L"Font &antialiasing:", L"Schrift&glättung:", L"&Lissage des polices :",
                                                  L"&Suavizado de fuente:", L"&Antialiasing carattere:", L"&Wygładzanie czcionki:", L"&Vyhladzovanie písma:" };
const wchar_t* ANTIALIASING_NAMES[FONT_ANTIALIAS_COUNT] = { L"GDI", L"ClearType" };
const wchar_t* DEFAULT_APPEARANCE_LABELS[LANG_COUNT] = { L"&Výchozí vzhled",         L"&Default appearance",  L"&Standarddarstellung", L"Apparence par &défaut",
                                                        L"Aspecto &predeterminado", L"Aspetto &predefinito", L"Wygląd &domyślny",     L"&Predvolený vzhľad" };
const wchar_t* TEST_COMMAND_LABELS[LANG_COUNT] = { L"V&yzkoušet", L"&Test", L"&Testen", L"&Tester", L"&Probar", L"&Prova", L"&Testuj", L"V&yskúšať" };
const wchar_t* STOP_TEST_LABELS[LANG_COUNT] = { L"&Zastavit test",  L"S&top test",   L"Test &stoppen",   L"&Arrêter le test",
                                               L"&Detener prueba", L"&Ferma prova", L"&Zatrzymaj test", L"&Zastaviť test" };
const wchar_t* REMOTE_SCRIPT_LABELS[LANG_COUNT] = { L"Zavolat &vzdálený skript",   L"Call a &remote script", L"&Remote-Skript aufrufen", L"Appeler un script &distant",
                                                   L"Llamar a un script &remoto", L"Chiama script &remoto", L"Wywołaj skrypt &zdalny",  L"Zavolať &vzdialený skript" };
const wchar_t* REMOTE_SCRIPT_URL_LABELS[LANG_COUNT] = { L"Adresa URL:", L"URL:", L"URL:", L"URL :", L"URL:", L"URL:", L"Adres URL:", L"Adresa URL:" };
const wchar_t* INVALID_REMOTE_SCRIPT_URL[LANG_COUNT] = { L"Zadejte platnou adresu vzdáleného skriptu HTTP nebo HTTPS.",
                                                        L"Enter a valid HTTP or HTTPS remote script URL.",
                                                        L"Geben Sie eine gültige HTTP- oder HTTPS-Adresse des Remote-Skripts ein.",
                                                        L"Entrez une adresse HTTP ou HTTPS valide pour le script distant.",
                                                        L"Introduzca una dirección HTTP o HTTPS válida para el script remoto.",
                                                        L"Immettere un indirizzo HTTP o HTTPS valido per lo script remoto.",
                                                        L"Wprowadź prawidłowy adres HTTP lub HTTPS zdalnego skryptu.",
                                                        L"Zadajte platnú adresu HTTP alebo HTTPS vzdialeného skriptu." };
const wchar_t* IMPORT_SETTINGS_LABELS[LANG_COUNT] = { L"Importovat &XML...", L"Import &XML...",  L"&XML importieren...", L"Importer &XML...",
                                                     L"Importar &XML...",   L"Importa &XML...", L"Importuj &XML...",    L"Importovať &XML..." };
const wchar_t* EXPORT_SETTINGS_LABELS[LANG_COUNT] = { L"Exportovat X&ML...", L"Export X&ML...",  L"XML &exportieren...", L"Exporter X&ML...",
                                                     L"Exportar X&ML...",   L"Esporta X&ML...", L"Eksportuj X&ML...",   L"Exportovať X&ML..." };
const wchar_t* INVALID_SETTINGS_FILE[LANG_COUNT] = { L"Soubor neobsahuje platné nastavení CalClock.",
                                                    L"The file does not contain valid CalClock settings.",
                                                    L"Die Datei enthält keine gültigen CalClock-Einstellungen.",
                                                    L"Le fichier ne contient pas de paramètres CalClock valides.",
                                                    L"El archivo no contiene una configuración válida de CalClock.",
                                                    L"Il file non contiene impostazioni CalClock valide.",
                                                    L"Plik nie zawiera prawidłowych ustawień CalClock.",
                                                    L"Súbor neobsahuje platné nastavenia CalClock." };
const wchar_t* SETTINGS_EXPORT_FAILED[LANG_COUNT] = {
    L"Nastavení se nepodařilo exportovat.",   L"Settings could not be exported.",       L"Die Einstellungen konnten nicht exportiert werden.",
    L"Impossible d’exporter les paramètres.", L"No se pudo exportar la configuración.", L"Impossibile esportare le impostazioni.",
    L"Nie udało się wyeksportować ustawień.", L"Nastavenia sa nepodarilo exportovať." };
const wchar_t* SETTINGS_IMPORT_FAILED[LANG_COUNT] = {
    L"Nastavení se nepodařilo importovat.",   L"Settings could not be imported.",       L"Die Einstellungen konnten nicht importiert werden.",
    L"Impossible d’importer les paramètres.", L"No se pudo importar la configuración.", L"Impossibile importare le impostazioni.",
    L"Nie udało się zaimportować ustawień.",  L"Nastavenia sa nepodarilo importovať." };
const wchar_t* XML_STORAGE_LABELS[LANG_COUNT] = { L"Ukládat do &XML", L"Save to &XML",  L"In &XML speichern", L"Enregistrer en &XML",
                                                 L"Guardar en &XML", L"Salva in &XML", L"Zapisuj do &XML",   L"Ukladať do &XML" };

static int AutomaticNtpPreset() {
    wchar_t localeName[LOCALE_NAME_MAX_LENGTH] = {};
    wchar_t country[4] = {};
    if (GetUserDefaultLocaleName(localeName, ARRAYSIZE(localeName)) == 0 || GetLocaleInfoEx(localeName, LOCALE_SISO3166CTRYNAME, country, ARRAYSIZE(country)) == 0) {
        return NTP_PRESET_GLOBAL;
    }
    if (_wcsicmp(country, L"CZ") == 0 || _wcsicmp(country, L"SK") == 0) {
        return NTP_PRESET_CESNET;
    }
    const wchar_t* europeanCountries[] = { L"AL", L"AD", L"AT", L"BY", L"BE", L"BA", L"BG", L"HR", L"CY", L"DK", L"EE", L"FI", L"FR", L"DE", L"GR",
                                          L"HU", L"IS", L"IE", L"IT", L"XK", L"LV", L"LI", L"LT", L"LU", L"MT", L"MD", L"MC", L"ME", L"NL", L"MK",
                                          L"NO", L"PL", L"PT", L"RO", L"RU", L"SM", L"RS", L"SI", L"ES", L"SE", L"CH", L"TR", L"UA", L"GB", L"VA" };
    for (const wchar_t* europeanCountry : europeanCountries) {
        if (_wcsicmp(country, europeanCountry) == 0) {
            return NTP_PRESET_PTB;
        }
    }
    return NTP_PRESET_GLOBAL;
}

static std::wstring NtpServersForPreset(int preset) {
    int selected = std::clamp(preset, 0, NTP_PRESET_COUNT - 1);
    if (selected == NTP_PRESET_AUTO) {
        selected = AutomaticNtpPreset();
    }
    if (selected == NTP_PRESET_CESNET) {
        return L"tik.cesnet.cz; tak.cesnet.cz; ntp.nic.cz";
    }
    if (selected == NTP_PRESET_PTB) {
        return L"ptbtime1.ptb.de; ptbtime2.ptb.de; ptbtime3.ptb.de; "
            L"ptbtime4.ptb.de";
    }
    if (selected == NTP_PRESET_GLOBAL) {
        return L"1.ntp.ubuntu.com; 2.ntp.ubuntu.com; 3.ntp.ubuntu.com; 4.ntp.ubuntu.com; "
            L"0.pool.ntp.org; 1.pool.ntp.org; 2.pool.ntp.org; 3.pool.ntp.org";
    }
    return std::wstring();
}

static const wchar_t* WT(const Widget* widget, TextId id) {
    AppLanguage language = widget == nullptr ? appLanguage : widget->config.language;
    return TEXT[language][id];
}

static wchar_t MnemonicKey(wchar_t character) {
    CharUpperBuffW(&character, 1);
    return character;
}

static std::wstring UniqueMnemonic(const wchar_t* text, std::vector<wchar_t>* usedMnemonics) {
    std::wstring plainText;
    size_t preferredPosition = std::wstring::npos;
    for (size_t index = 0; text[index] != L'\0'; index++) {
        if (text[index] == L'&' && text[index + 1] != L'\0') {
            if (text[index + 1] == L'&') {
                plainText += L'&';
                index++;
            } else if (preferredPosition == std::wstring::npos) {
                preferredPosition = plainText.size();
            }
            continue;
        }
        plainText += text[index];
    }

    size_t mnemonicPosition = std::wstring::npos;
    if (preferredPosition < plainText.size()) {
        wchar_t key = MnemonicKey(plainText[preferredPosition]);
        if (std::iswalnum(plainText[preferredPosition]) && std::find(usedMnemonics->begin(), usedMnemonics->end(), key) == usedMnemonics->end()) {
            mnemonicPosition = preferredPosition;
        }
    }
    if (mnemonicPosition == std::wstring::npos) {
        for (size_t index = 0; index < plainText.size(); index++) {
            wchar_t key = MnemonicKey(plainText[index]);
            if (std::iswalnum(plainText[index]) && std::find(usedMnemonics->begin(), usedMnemonics->end(), key) == usedMnemonics->end()) {
                mnemonicPosition = index;
                break;
            }
        }
    }

    std::wstring result;
    for (size_t index = 0; index < plainText.size(); index++) {
        if (index == mnemonicPosition) {
            result += L'&';
        }
        if (plainText[index] == L'&') {
            result += L'&';
        }
        result += plainText[index];
    }
    if (mnemonicPosition != std::wstring::npos) {
        usedMnemonics->push_back(MnemonicKey(plainText[mnemonicPosition]));
    }
    return result;
}

static void AppendMenuCommand(HMENU menu, UINT flags, UINT_PTR command, const wchar_t* text, std::vector<wchar_t>* usedMnemonics, bool opensWindow = false) {
    std::wstring caption = text;
    if (opensWindow) {
        caption += L"...";
    }
    std::wstring label = UniqueMnemonic(caption.c_str(), usedMnemonics);
    AppendMenuW(menu, flags, command, label.c_str());
}

static LCID WINAPI CalendarGetUserDefaultLCID() {
    if (activeCalendarLocale != 0) {
        return activeCalendarLocale;
    }
    return originalGetUserDefaultLcid == nullptr ? LOCALE_USER_DEFAULT : originalGetUserDefaultLcid();
}

static int WINAPI CalendarGetLocaleInfoW(LCID locale, LCTYPE type, LPWSTR data, int characters) {
    LCID selectedLocale = activeCalendarLocale == 0 ? locale : activeCalendarLocale;
    return originalGetLocaleInfoW == nullptr ? 0 : originalGetLocaleInfoW(selectedLocale, type, data, characters);
}

static int WINAPI CalendarGetCalendarInfoW(LCID locale, CALID calendar, CALTYPE type, LPWSTR data, int characters, LPDWORD value) {
    LCID selectedLocale = activeCalendarLocale == 0 ? locale : activeCalendarLocale;
    return originalGetCalendarInfoW == nullptr ? 0 : originalGetCalendarInfoW(selectedLocale, calendar, type, data, characters, value);
}

static int WINAPI CalendarGetCalendarInfoEx(LPCWSTR localeName, CALID calendar, LPCWSTR reserved, CALTYPE type, LPWSTR data, int characters, LPDWORD value) {
    wchar_t selectedName[LOCALE_NAME_MAX_LENGTH] = {};
    LPCWSTR selectedLocaleName = localeName;
    if (activeCalendarLocale != 0 && LCIDToLocaleName(activeCalendarLocale, selectedName, ARRAYSIZE(selectedName), 0) != 0) {
        selectedLocaleName = selectedName;
    }
    return originalGetCalendarInfoEx == nullptr ? 0 : originalGetCalendarInfoEx(selectedLocaleName, calendar, reserved, type, data, characters, value);
}

static int WINAPI CalendarGetCalendarDateFormat(CALID calendar, DWORD flags, const void* calendarDate, LPCWSTR format, LPWSTR data, int characters) {
    if (activeCalendarLocale != 0 && calendarDate != nullptr && data != nullptr && characters > 0) {
        if (convertCalDateTimeToSystemTime == nullptr) {
            HMODULE kernel = GetModuleHandleW(L"kernel32.dll");
            if (kernel != nullptr) {
                convertCalDateTimeToSystemTime = reinterpret_cast<ConvertCalDateTimeToSystemTimeProc>(GetProcAddress(kernel, "ConvertCalDateTimeToSystemTime"));
            }
        }
        SYSTEMTIME systemTime = {};
        wchar_t localeName[LOCALE_NAME_MAX_LENGTH] = {};
        if (convertCalDateTimeToSystemTime != nullptr && convertCalDateTimeToSystemTime(calendarDate, &systemTime) &&
            LCIDToLocaleName(activeCalendarLocale, localeName, ARRAYSIZE(localeName), 0) != 0) {
            int result = GetDateFormatEx(localeName, flags, &systemTime, format, data, characters, nullptr);
            if (result != 0) {
                return result;
            }
        }
    }
    return originalGetCalendarDateFormat == nullptr ? 0 : originalGetCalendarDateFormat(calendar, flags, calendarDate, format, data, characters);
}

class CalendarLocaleScope {
public:
    explicit CalendarLocaleScope(AppLanguage language) {
        previousOverride = activeCalendarLocale;
        previousLocale = GetThreadLocale();
        previousUiLanguage = GetThreadUILanguage();
        activeCalendarLocale = LocaleNameToLCID(LANGUAGE_LOCALES[language], 0);
        if (activeCalendarLocale != 0) {
            SetThreadLocale(activeCalendarLocale);
            SetThreadUILanguage(LANGIDFROMLCID(activeCalendarLocale));
        }
    }

    ~CalendarLocaleScope() {
        SetThreadUILanguage(previousUiLanguage);
        SetThreadLocale(previousLocale);
        activeCalendarLocale = previousOverride;
    }

private:
    LCID previousOverride;
    LCID previousLocale;
    LANGID previousUiLanguage;
};

static bool PatchCommonControlsImport(const char* functionName, ULONG_PTR replacement, ULONG_PTR* original) {
    HMODULE commonControls = GetModuleHandleW(L"comctl32.dll");
    if (commonControls == nullptr) {
        return false;
    }
    BYTE* base = reinterpret_cast<BYTE*>(commonControls);
    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        return false;
    }
    IMAGE_NT_HEADERS* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
        return false;
    }
    IMAGE_DATA_DIRECTORY imports = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (imports.VirtualAddress == 0) {
        return false;
    }
    IMAGE_IMPORT_DESCRIPTOR* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + imports.VirtualAddress);
    for (; descriptor->Name != 0; descriptor++) {
        if (descriptor->OriginalFirstThunk == 0 || descriptor->FirstThunk == 0) {
            continue;
        }
        IMAGE_THUNK_DATA* names = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->OriginalFirstThunk);
        IMAGE_THUNK_DATA* addresses = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->FirstThunk);
        for (; names->u1.AddressOfData != 0; names++, addresses++) {
            if (IMAGE_SNAP_BY_ORDINAL(names->u1.Ordinal)) {
                continue;
            }
            IMAGE_IMPORT_BY_NAME* importName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + names->u1.AddressOfData);
            if (strcmp(reinterpret_cast<const char*>(importName->Name), functionName) != 0) {
                continue;
            }
            DWORD oldProtect = 0;
            if (!VirtualProtect(&addresses->u1.Function, sizeof(addresses->u1.Function), PAGE_READWRITE, &oldProtect)) {
                return false;
            }
            *original = addresses->u1.Function;
            addresses->u1.Function = replacement;
            DWORD ignored = 0;
            VirtualProtect(&addresses->u1.Function, sizeof(addresses->u1.Function), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), &addresses->u1.Function, sizeof(addresses->u1.Function));
            return true;
        }
    }
    return false;
}

static bool InstallCalendarLocaleHook() {
    if (originalGetUserDefaultLcid != nullptr) {
        return true;
    }
    ULONG_PTR original = 0;
    bool defaultHook = PatchCommonControlsImport("GetUserDefaultLCID", reinterpret_cast<ULONG_PTR>(&CalendarGetUserDefaultLCID), &original);
    originalGetUserDefaultLcid = reinterpret_cast<GetUserDefaultLcidProc>(original);
    original = 0;
    bool localeHook = PatchCommonControlsImport("GetLocaleInfoW", reinterpret_cast<ULONG_PTR>(&CalendarGetLocaleInfoW), &original);
    originalGetLocaleInfoW = reinterpret_cast<GetLocaleInfoWProc>(original);
    original = 0;
    bool calendarHook = PatchCommonControlsImport("GetCalendarInfoW", reinterpret_cast<ULONG_PTR>(&CalendarGetCalendarInfoW), &original);
    originalGetCalendarInfoW = reinterpret_cast<GetCalendarInfoWProc>(original);
    original = 0;
    PatchCommonControlsImport("GetCalendarInfoEx", reinterpret_cast<ULONG_PTR>(&CalendarGetCalendarInfoEx), &original);
    originalGetCalendarInfoEx = reinterpret_cast<GetCalendarInfoExProc>(original);
    original = 0;
    bool dateHook = PatchCommonControlsImport("GetCalendarDateFormat", reinterpret_cast<ULONG_PTR>(&CalendarGetCalendarDateFormat), &original);
    originalGetCalendarDateFormat = reinterpret_cast<GetCalendarDateFormatProc>(original);
    return defaultHook && localeHook && calendarHook && dateHook;
}

static BOOL CALLBACK CollectDisplayMonitor(HMONITOR monitor, HDC, LPRECT, LPARAM data) {
    std::vector<DisplayMonitor>* monitors = reinterpret_cast<std::vector<DisplayMonitor> *>(data);
    MONITORINFOEXW information = {};
    information.cbSize = sizeof(information);
    if (monitors != nullptr && GetMonitorInfoW(monitor, &information)) {
        DisplayMonitor item = {};
        item.handle = monitor;
        item.rect = information.rcMonitor;
        item.device = information.szDevice;
        item.primary = (information.dwFlags & MONITORINFOF_PRIMARY) != 0;
        monitors->push_back(item);
    }
    return TRUE;
}

static void RefreshDisplayMonitors() {
    displayMonitors.clear();
    EnumDisplayMonitors(nullptr, nullptr, CollectDisplayMonitor, reinterpret_cast<LPARAM>(&displayMonitors));
    std::stable_sort(displayMonitors.begin(), displayMonitors.end(), [](const DisplayMonitor& left, const DisplayMonitor& right) {
        if (left.primary != right.primary) {
            return left.primary;
        }
        if (left.rect.top != right.rect.top) {
            return left.rect.top < right.rect.top;
        }
        return left.rect.left < right.rect.left;
    });
}

static bool ContainsMonitorDevice(const std::wstring& devices, const std::wstring& device) {
    size_t start = 0;
    while (start <= devices.size()) {
        size_t end = devices.find(L';', start);
        std::wstring current = devices.substr(start, end == std::wstring::npos ? std::wstring::npos : end - start);
        if (_wcsicmp(current.c_str(), device.c_str()) == 0) {
            return true;
        }
        if (end == std::wstring::npos) {
            break;
        }
        start = end + 1;
    }
    return false;
}

static std::vector<const DisplayMonitor*> SelectedDisplayMonitors(const WidgetConfig& config) {
    if (displayMonitors.empty()) {
        RefreshDisplayMonitors();
    }
    std::vector<const DisplayMonitor*> selected;
    for (size_t index = 0; index < displayMonitors.size(); index++) {
        if (ContainsMonitorDevice(config.monitorDevices, displayMonitors[index].device)) {
            selected.push_back(&displayMonitors[index]);
        }
    }
    if (selected.empty() && !displayMonitors.empty()) {
        selected.push_back(&displayMonitors[0]);
    }
    return selected;
}

static bool GetPrimarySelectedMonitorRect(const WidgetConfig& config, RECT* rect) {
    std::vector<const DisplayMonitor*> selected = SelectedDisplayMonitors(config);
    if (selected.empty() || rect == nullptr) {
        return false;
    }
    *rect = selected[0]->rect;
    return true;
}

static void SetDefaultWidgetAppearance(WidgetConfig* config, WidgetType type) {
    if (config == nullptr) {
        return;
    }
    config->size = 130;
    config->opacity = 100;
    config->fontSize = 44;
    config->fontDialogSize = type == WIDGET_DIGITAL ? config->fontSize * 10 : 90;
    int selectedAppFontAntialiasing = hAppAntialiasCombo == nullptr ? appFontAntialiasing : static_cast<int>(SendMessageW(hAppAntialiasCombo, CB_GETCURSEL, 0, 0));
    config->fontAntialiasing = std::clamp(selectedAppFontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
    config->leadingZero = true;
    config->transparentBackground = false;
    config->disableThemes = false;
    config->fontFace = type == WIDGET_DIGITAL ? L"Arial" : (type == WIDGET_FULLSCREEN ? L"Arial Narrow" : L"Segoe UI");
    config->fontWeight = FW_NORMAL;
    config->fontItalic = false;
    config->fontUnderline = false;
    config->fontStrikeOut = false;
    config->fontCharSet = DEFAULT_CHARSET;
    config->padding = 8;
    config->borderStyle = DIGITAL_BORDER_SINGLE;
    config->borderWidth = 1;
    config->textColor = RGB(16, 16, 16);
    config->backgroundColor = RGB(255, 255, 255);
    config->alarmTextColor = RGB(220, 0, 0);
    config->alarmBackgroundColor = RGB(255, 255, 128);
    config->weekNumbers = false;
    config->sundayFirst = false;
    config->dateCopyFormat = DATE_YYMMDD;
    config->panelTopFont = FontSelection();
    config->panelTimeFont = FontSelection();
    config->panelBottomFont = FontSelection();
}

static WidgetConfig DefaultConfig(WidgetType type, int index) {
    WidgetConfig config = {};
    config.id = nextWidgetId++;
    config.type = type;
    config.name = TypeName(type);
    config.visible = true;
    config.topMost = true;
    config.showSeconds = true;
    config.showUtc = false;
    config.showUtcText = false;
    config.language = appLanguage;
    DYNAMIC_TIME_ZONE_INFORMATION systemZone = {};
    GetDynamicTimeZoneInformation(&systemZone);
    config.timeZoneKey = systemZone.TimeZoneKeyName;
    if (type == WIDGET_FULLSCREEN) {
        RefreshDisplayMonitors();
        if (!displayMonitors.empty()) {
            config.monitorDevices = displayMonitors[0].device;
        }
    }
    config.offsetMilliseconds = 0;
    config.x = 100 + index * 28;
    config.y = 100 + index * 28;
    SetDefaultWidgetAppearance(&config, type);
    config.alarmEnabled = false;
    config.alarmHour = 6;
    config.alarmMinute = 0;
    config.runCommand = false;
    config.loopAudio = false;
    config.callRemoteScript = false;
    return config;
}

static void SelectSystemLanguage() {
    switch (PRIMARYLANGID(GetUserDefaultUILanguage())) {
        case LANG_CZECH:
            appLanguage = LANG_CZ;
            break;
        case LANG_GERMAN:
            appLanguage = LANG_DE;
            break;
        case LANG_FRENCH:
            appLanguage = LANG_FR;
            break;
        case LANG_SPANISH:
            appLanguage = LANG_ES;
            break;
        case LANG_ITALIAN:
            appLanguage = LANG_IT;
            break;
        case LANG_POLISH:
            appLanguage = LANG_PL;
            break;
        case LANG_SLOVAK:
            appLanguage = LANG_SK;
            break;
        default:
            appLanguage = LANG_EN;
            break;
    }
}

static bool ReadDword(HKEY key, const wchar_t* name, DWORD* value) {
    DWORD type = 0;
    DWORD size = sizeof(*value);
    return RegQueryValueExW(key, name, nullptr, &type, reinterpret_cast<BYTE*>(value), &size) == ERROR_SUCCESS && type == REG_DWORD;
}

static bool ReadQword(HKEY key, const wchar_t* name, LONGLONG* value) {
    DWORD type = 0;
    DWORD size = sizeof(*value);
    return RegQueryValueExW(key, name, nullptr, &type, reinterpret_cast<BYTE*>(value), &size) == ERROR_SUCCESS && type == REG_QWORD;
}

static bool ReadString(HKEY key, const wchar_t* name, std::wstring* value) {
    DWORD type = 0;
    DWORD size = 0;
    if (RegQueryValueExW(key, name, nullptr, &type, nullptr, &size) != ERROR_SUCCESS || (type != REG_SZ && type != REG_EXPAND_SZ) || size < sizeof(wchar_t)) {
        return false;
    }
    std::vector<wchar_t> buffer(size / sizeof(wchar_t) + 1, 0);
    if (RegQueryValueExW(key, name, nullptr, &type, reinterpret_cast<BYTE*>(buffer.data()), &size) != ERROR_SUCCESS) {
        return false;
    }
    *value = buffer.data();
    return true;
}

static void WriteDword(HKEY key, const wchar_t* name, DWORD value) {
    RegSetValueExW(key, name, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));
}
static void WriteQword(HKEY key, const wchar_t* name, LONGLONG value) {
    RegSetValueExW(key, name, 0, REG_QWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));
}
static void WriteString(HKEY key, const wchar_t* name, const std::wstring& value) {
    RegSetValueExW(key, name, 0, REG_SZ, reinterpret_cast<const BYTE*>(value.c_str()), static_cast<DWORD>((value.size() + 1) * sizeof(wchar_t)));
}

static std::wstring AutomaticXmlSettingsPath(bool createDirectory) {
    wchar_t appData[MAX_PATH] = {};
    if (SHGetFolderPathW(nullptr, CSIDL_APPDATA | (createDirectory ? CSIDL_FLAG_CREATE : 0), nullptr, SHGFP_TYPE_CURRENT, appData) != S_OK) {
        return L"";
    }
    std::wstring vendorDirectory = std::wstring(appData) + L"\\FortSoft";
    if (createDirectory && !CreateDirectoryW(vendorDirectory.c_str(), nullptr) && GetLastError() != ERROR_ALREADY_EXISTS) {
        return L"";
    }
    std::wstring directory = vendorDirectory + L"\\CalClock";
    if (createDirectory && !CreateDirectoryW(directory.c_str(), nullptr) && GetLastError() != ERROR_ALREADY_EXISTS) {
        return L"";
    }
    return directory + L"\\settings.xml";
}

static void RemoveAutomaticXmlSettings() {
    std::wstring path = AutomaticXmlSettingsPath(false);
    if (path.empty()) {
        return;
    }
    DeleteFileW(path.c_str());
    size_t separator = path.find_last_of(L"\\/");
    if (separator == std::wstring::npos) {
        return;
    }
    std::wstring applicationDirectory = path.substr(0, separator);
    RemoveDirectoryW(applicationDirectory.c_str());
    separator = applicationDirectory.find_last_of(L"\\/");
    if (separator == std::wstring::npos) {
        return;
    }
    std::wstring vendorDirectory = applicationDirectory.substr(0, separator);
    RemoveDirectoryW(vendorDirectory.c_str());
}

static SettingsSnapshot CaptureSettingsSnapshot() {
    SettingsSnapshot snapshot = {};
    snapshot.language = appLanguage;
    snapshot.themesDisabled = themesDisabled;
    snapshot.fontAntialiasing = appFontAntialiasing;
    snapshot.fontFace = appFontFace;
    snapshot.fontDialogSize = appFontDialogSize;
    snapshot.fontWeight = appFontWeight;
    snapshot.fontItalic = appFontItalic;
    snapshot.useNtpTime = useNtpTime;
    snapshot.ntpPreset = ntpPreset;
    snapshot.ntpServers = ntpServers;
    snapshot.settingsX = settingsX;
    snapshot.settingsY = settingsY;
    snapshot.helpX = helpX;
    snapshot.helpY = helpY;
    snapshot.aboutX = aboutX;
    snapshot.aboutY = aboutY;
    for (size_t index = 0; index < widgets.size(); index++) {
        snapshot.widgets.push_back(widgets[index]->config);
    }
    return snapshot;
}

static HRESULT WriteXmlTextAttribute(IXmlWriter* writer, const wchar_t* name, const std::wstring& value) {
    return writer->WriteAttributeString(nullptr, name, nullptr, value.c_str());
}

static HRESULT WriteXmlNumberAttribute(IXmlWriter* writer, const wchar_t* name, LONGLONG value) {
    wchar_t text[32] = {};
    _i64tow_s(value, text, ARRAYSIZE(text), 10);
    return writer->WriteAttributeString(nullptr, name, nullptr, text);
}

static FontSelection GetWidgetFontSelection(const WidgetConfig& config) {
    FontSelection selection = {};
    selection.face = config.fontFace;
    selection.dialogSize = config.fontDialogSize;
    selection.weight = config.fontWeight;
    selection.italic = config.fontItalic;
    selection.underline = config.fontUnderline;
    selection.strikeOut = config.fontStrikeOut;
    selection.charSet = config.fontCharSet;
    return selection;
}

static bool WriteSettingsXml(const std::wstring& path, const SettingsSnapshot& snapshot) {
    if (path.empty() || snapshot.widgets.empty()) {
        return false;
    }
    IStream* stream = nullptr;
    if (FAILED(SHCreateStreamOnFileEx(path.c_str(), STGM_CREATE | STGM_WRITE | STGM_SHARE_DENY_WRITE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, &stream))) {
        return false;
    }
    IXmlWriter* writer = nullptr;
    HRESULT result = CreateXmlWriter(__uuidof(IXmlWriter), reinterpret_cast<void**>(&writer), nullptr);
    if (SUCCEEDED(result)) {
        result = writer->SetOutput(stream);
    }
    if (SUCCEEDED(result)) {
        result = writer->SetProperty(XmlWriterProperty_Indent, TRUE);
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteStartDocument(XmlStandalone_Omit);
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteStartElement(nullptr, L"CalClockSettings", nullptr);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"version", 1);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"language", snapshot.language);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"disableThemes", snapshot.themesDisabled);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"fontAntialiasing", snapshot.fontAntialiasing);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlTextAttribute(writer, L"fontFace", snapshot.fontFace);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"fontDialogSize", snapshot.fontDialogSize);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"fontWeight", snapshot.fontWeight);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"fontItalic", snapshot.fontItalic);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"useNtpTime", snapshot.useNtpTime);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"ntpPreset", snapshot.ntpPreset);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlTextAttribute(writer, L"ntpServers", snapshot.ntpServers);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"settingsX", snapshot.settingsX);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"settingsY", snapshot.settingsY);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"helpX", snapshot.helpX);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"helpY", snapshot.helpY);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"aboutX", snapshot.aboutX);
    }
    if (SUCCEEDED(result)) {
        result = WriteXmlNumberAttribute(writer, L"aboutY", snapshot.aboutY);
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteStartElement(nullptr, L"Widgets", nullptr);
    }
    for (size_t index = 0; index < snapshot.widgets.size() && SUCCEEDED(result); index++) {
        const WidgetConfig& config = snapshot.widgets[index];
        result = writer->WriteStartElement(nullptr, L"Widget", nullptr);
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"id", config.id);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"type", config.type);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"name", config.name);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"visible", config.visible);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"topMost", config.topMost);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"showSeconds", config.showSeconds);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"showUtc", config.showUtc);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"showUtcText", config.showUtcText);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"language", config.language);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"timeZoneKey", config.timeZoneKey);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"monitorDevices", config.monitorDevices);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"blackoutOtherMonitors", config.blackoutOtherMonitors);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"offsetMilliseconds", config.offsetMilliseconds);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"x", config.x);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"y", config.y);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"previewX", config.previewX);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"previewY", config.previewY);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"size", config.size);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"opacity", config.opacity);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontSize", config.fontSize);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontDialogSize", config.fontDialogSize);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontAntialiasing", config.fontAntialiasing);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"leadingZero", config.leadingZero);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"transparentBackground", config.transparentBackground);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"disableThemes", config.disableThemes);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"fontFace", config.fontFace);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontWeight", config.fontWeight);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontItalic", config.fontItalic);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontUnderline", config.fontUnderline);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontStrikeOut", config.fontStrikeOut);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"fontCharSet", config.fontCharSet);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"panelTopFontFace", config.panelTopFont.face);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontSize", config.panelTopFont.dialogSize);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontWeight", config.panelTopFont.weight);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontItalic", config.panelTopFont.italic);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontUnderline", config.panelTopFont.underline);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontStrikeOut", config.panelTopFont.strikeOut);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTopFontCharSet", config.panelTopFont.charSet);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"panelTimeFontFace", config.panelTimeFont.face);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontSize", config.panelTimeFont.dialogSize);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontWeight", config.panelTimeFont.weight);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontItalic", config.panelTimeFont.italic);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontUnderline", config.panelTimeFont.underline);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontStrikeOut", config.panelTimeFont.strikeOut);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelTimeFontCharSet", config.panelTimeFont.charSet);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"panelBottomFontFace", config.panelBottomFont.face);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontSize", config.panelBottomFont.dialogSize);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontWeight", config.panelBottomFont.weight);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontItalic", config.panelBottomFont.italic);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontUnderline", config.panelBottomFont.underline);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontStrikeOut", config.panelBottomFont.strikeOut);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"panelBottomFontCharSet", config.panelBottomFont.charSet);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"padding", config.padding);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"borderStyle", config.borderStyle);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"borderWidth", config.borderWidth);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"textColor", static_cast<DWORD>(config.textColor));
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"backgroundColor", static_cast<DWORD>(config.backgroundColor));
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmTextColor", static_cast<DWORD>(config.alarmTextColor));
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmBackgroundColor", static_cast<DWORD>(config.alarmBackgroundColor));
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"weekNumbers", config.weekNumbers);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"sundayFirst", config.sundayFirst);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"dateCopyFormat", config.dateCopyFormat);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmEnabled", config.alarmEnabled);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmHour", config.alarmHour);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"alarmMinute", config.alarmMinute);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"runCommand", config.runCommand);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"loopAudio", config.loopAudio);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"command", config.command);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlNumberAttribute(writer, L"callRemoteScript", config.callRemoteScript);
        }
        if (SUCCEEDED(result)) {
            result = WriteXmlTextAttribute(writer, L"remoteScriptUrl", config.remoteScriptUrl);
        }
        if (SUCCEEDED(result)) {
            result = writer->WriteEndElement();
        }
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteEndElement();
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteEndElement();
    }
    if (SUCCEEDED(result)) {
        result = writer->WriteEndDocument();
    }
    if (SUCCEEDED(result)) {
        result = writer->Flush();
    }
    if (writer != nullptr) {
        writer->Release();
    }
    stream->Release();
    return SUCCEEDED(result);
}

static bool ReadXmlAttribute(IXmlReader* reader, const wchar_t* name, std::wstring* value) {
    if (reader->MoveToAttributeByName(name, nullptr) != S_OK) {
        return false;
    }
    const wchar_t* text = nullptr;
    UINT length = 0;
    HRESULT result = reader->GetValue(&text, &length);
    reader->MoveToElement();
    if (FAILED(result) || text == nullptr) {
        return false;
    }
    value->assign(text, length);
    return true;
}

static bool ParseXmlNumber(const std::wstring& text, LONGLONG* value) {
    if (text.empty()) {
        return false;
    }
    wchar_t* end = nullptr;
    LONGLONG parsed = _wcstoi64(text.c_str(), &end, 10);
    if (end == text.c_str() || *end != L'\0') {
        return false;
    }
    *value = parsed;
    return true;
}

static bool ReadXmlNumberAttribute(IXmlReader* reader, const wchar_t* name, LONGLONG* value) {
    std::wstring text;
    return ReadXmlAttribute(reader, name, &text) && ParseXmlNumber(text, value);
}

static void ReadWidgetXml(IXmlReader* reader, int index, int defaultFontAntialiasing, WidgetConfig* config) {
    LONGLONG number = 0;
    int type = WIDGET_ANALOG;
    if (ReadXmlNumberAttribute(reader, L"type", &number) && number >= 0 && number < WIDGET_TYPE_COUNT) {
        type = static_cast<int>(number);
    }
    int savedNextWidgetId = nextWidgetId;
    *config = DefaultConfig(static_cast<WidgetType>(type), index);
    nextWidgetId = savedNextWidgetId;
    config->fontAntialiasing = std::clamp(defaultFontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
    std::wstring text;
    if (ReadXmlNumberAttribute(reader, L"id", &number) && number > 0 && number <= INT_MAX) {
        config->id = static_cast<int>(number);
    }
    config->type = static_cast<WidgetType>(type);
    if (ReadXmlAttribute(reader, L"name", &text)) {
        config->name = text;
    }
    if (ReadXmlNumberAttribute(reader, L"visible", &number)) {
        config->visible = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"topMost", &number)) {
        config->topMost = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"showSeconds", &number)) {
        config->showSeconds = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"showUtc", &number)) {
        config->showUtc = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"showUtcText", &number)) {
        config->showUtcText = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"language", &number) && number >= 0 && number < LANG_COUNT) {
        config->language = static_cast<AppLanguage>(number);
    }
    if (ReadXmlAttribute(reader, L"timeZoneKey", &text)) {
        config->timeZoneKey = text;
    }
    if (ReadXmlAttribute(reader, L"monitorDevices", &text)) {
        config->monitorDevices = text;
    }
    if (ReadXmlNumberAttribute(reader, L"blackoutOtherMonitors", &number)) {
        config->blackoutOtherMonitors = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"offsetMilliseconds", &number)) {
        config->offsetMilliseconds = number;
    }
    if (ReadXmlNumberAttribute(reader, L"x", &number) && number >= INT_MIN && number <= INT_MAX) {
        config->x = static_cast<int>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"y", &number) && number >= INT_MIN && number <= INT_MAX) {
        config->y = static_cast<int>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"previewX", &number) && number >= INT_MIN && number <= INT_MAX) {
        config->previewX = static_cast<int>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"previewY", &number) && number >= INT_MIN && number <= INT_MAX) {
        config->previewY = static_cast<int>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"size", &number)) {
        config->size = std::clamp(static_cast<int>(number), 104, 198);
    }
    if (ReadXmlNumberAttribute(reader, L"opacity", &number)) {
        config->opacity = std::clamp(static_cast<int>(number), 5, 100);
    }
    if (ReadXmlNumberAttribute(reader, L"fontSize", &number)) {
        config->fontSize = std::clamp(static_cast<int>(number), config->type == WIDGET_FULLSCREEN ? 5 : 10, config->type == WIDGET_FULLSCREEN ? 85 : 140);
    }
    if (config->type == WIDGET_DIGITAL) {
        config->fontDialogSize = config->fontSize * 10;
    }
    if (ReadXmlNumberAttribute(reader, L"fontDialogSize", &number)) {
        int savedSize = static_cast<int>(number);
        config->fontDialogSize = std::clamp(savedSize < 10 ? savedSize * 10 : savedSize, 10, 9990);
    }
    if (ReadXmlNumberAttribute(reader, L"fontAntialiasing", &number) && number >= 0 && number < FONT_ANTIALIAS_COUNT) {
        config->fontAntialiasing = static_cast<int>(number);
    }
    if (ReadXmlNumberAttribute(reader, L"leadingZero", &number)) {
        config->leadingZero = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"transparentBackground", &number)) {
        config->transparentBackground = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"disableThemes", &number)) {
        config->disableThemes = number != 0;
    }
    if (ReadXmlAttribute(reader, L"fontFace", &text) && text.size() < LF_FACESIZE) {
        config->fontFace = text;
    }
    if (ReadXmlNumberAttribute(reader, L"fontWeight", &number)) {
        config->fontWeight = std::clamp(static_cast<int>(number), 0, 1000);
    }
    if (ReadXmlNumberAttribute(reader, L"fontItalic", &number)) {
        config->fontItalic = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"fontUnderline", &number)) {
        config->fontUnderline = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"fontStrikeOut", &number)) {
        config->fontStrikeOut = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"fontCharSet", &number)) {
        config->fontCharSet = static_cast<BYTE>(std::clamp<LONGLONG>(number, 0, 255));
    }
    config->panelTopFont = GetWidgetFontSelection(*config);
    config->panelTimeFont = config->panelTopFont;
    config->panelBottomFont = config->panelTopFont;
    if (ReadXmlAttribute(reader, L"panelTopFontFace", &text) && text.size() < LF_FACESIZE) {
        config->panelTopFont.face = text;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontSize", &number)) {
        config->panelTopFont.dialogSize = std::clamp(static_cast<int>(number), 10, 9990);
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontWeight", &number)) {
        config->panelTopFont.weight = std::clamp(static_cast<int>(number), 0, 1000);
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontItalic", &number)) {
        config->panelTopFont.italic = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontUnderline", &number)) {
        config->panelTopFont.underline = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontStrikeOut", &number)) {
        config->panelTopFont.strikeOut = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTopFontCharSet", &number)) {
        config->panelTopFont.charSet = static_cast<BYTE>(std::clamp<LONGLONG>(number, 0, 255));
    }
    if (ReadXmlAttribute(reader, L"panelTimeFontFace", &text) && text.size() < LF_FACESIZE) {
        config->panelTimeFont.face = text;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontSize", &number)) {
        config->panelTimeFont.dialogSize = std::clamp(static_cast<int>(number), 10, 9990);
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontWeight", &number)) {
        config->panelTimeFont.weight = std::clamp(static_cast<int>(number), 0, 1000);
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontItalic", &number)) {
        config->panelTimeFont.italic = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontUnderline", &number)) {
        config->panelTimeFont.underline = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontStrikeOut", &number)) {
        config->panelTimeFont.strikeOut = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelTimeFontCharSet", &number)) {
        config->panelTimeFont.charSet = static_cast<BYTE>(std::clamp<LONGLONG>(number, 0, 255));
    }
    if (ReadXmlAttribute(reader, L"panelBottomFontFace", &text) && text.size() < LF_FACESIZE) {
        config->panelBottomFont.face = text;
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontSize", &number)) {
        config->panelBottomFont.dialogSize = std::clamp(static_cast<int>(number), 10, 9990);
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontWeight", &number)) {
        config->panelBottomFont.weight = std::clamp(static_cast<int>(number), 0, 1000);
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontItalic", &number)) {
        config->panelBottomFont.italic = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontUnderline", &number)) {
        config->panelBottomFont.underline = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontStrikeOut", &number)) {
        config->panelBottomFont.strikeOut = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"panelBottomFontCharSet", &number)) {
        config->panelBottomFont.charSet = static_cast<BYTE>(std::clamp<LONGLONG>(number, 0, 255));
    }
    if (ReadXmlNumberAttribute(reader, L"padding", &number)) {
        config->padding = std::clamp(static_cast<int>(number), 0, 70);
    }
    if (ReadXmlNumberAttribute(reader, L"borderStyle", &number)) {
        config->borderStyle = std::clamp(static_cast<int>(number), 0, DIGITAL_BORDER_STYLE_COUNT - 1);
    }
    if (ReadXmlNumberAttribute(reader, L"borderWidth", &number)) {
        config->borderWidth = std::clamp(static_cast<int>(number), 0, DIGITAL_BORDER_WIDTH_MAX);
    }
    if (ReadXmlNumberAttribute(reader, L"textColor", &number)) {
        config->textColor = static_cast<COLORREF>(number & 0xFFFFFF);
    }
    if (ReadXmlNumberAttribute(reader, L"backgroundColor", &number)) {
        config->backgroundColor = static_cast<COLORREF>(number & 0xFFFFFF);
    }
    if (ReadXmlNumberAttribute(reader, L"alarmTextColor", &number)) {
        config->alarmTextColor = static_cast<COLORREF>(number & 0xFFFFFF);
    }
    if (ReadXmlNumberAttribute(reader, L"alarmBackgroundColor", &number)) {
        config->alarmBackgroundColor = static_cast<COLORREF>(number & 0xFFFFFF);
    }
    if (ReadXmlNumberAttribute(reader, L"weekNumbers", &number)) {
        config->weekNumbers = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"sundayFirst", &number)) {
        config->sundayFirst = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"dateCopyFormat", &number)) {
        config->dateCopyFormat = std::clamp(static_cast<int>(number), 0, DATE_FORMAT_COUNT - 1);
    }
    if (ReadXmlNumberAttribute(reader, L"alarmEnabled", &number)) {
        config->alarmEnabled = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"alarmHour", &number)) {
        config->alarmHour = std::clamp(static_cast<int>(number), 0, 23);
    }
    if (ReadXmlNumberAttribute(reader, L"alarmMinute", &number)) {
        config->alarmMinute = std::clamp(static_cast<int>(number), 0, 59);
    }
    if (ReadXmlNumberAttribute(reader, L"runCommand", &number)) {
        config->runCommand = number != 0;
    }
    if (ReadXmlNumberAttribute(reader, L"loopAudio", &number)) {
        config->loopAudio = number != 0;
    }
    if (ReadXmlAttribute(reader, L"command", &text)) {
        config->command = text;
    }
    if (ReadXmlNumberAttribute(reader, L"callRemoteScript", &number)) {
        config->callRemoteScript = number != 0;
    }
    if (ReadXmlAttribute(reader, L"remoteScriptUrl", &text)) {
        config->remoteScriptUrl = text;
    }
}

static bool ReadSettingsXml(const std::wstring& path, SettingsSnapshot* snapshot) {
    if (path.empty() || snapshot == nullptr) {
        return false;
    }
    WIN32_FILE_ATTRIBUTE_DATA fileData = {};
    if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &fileData) || fileData.nFileSizeHigh != 0 || fileData.nFileSizeLow > 4 * 1024 * 1024) {
        return false;
    }
    IStream* stream = nullptr;
    if (FAILED(SHCreateStreamOnFileEx(path.c_str(), STGM_READ | STGM_SHARE_DENY_WRITE, FILE_ATTRIBUTE_NORMAL, FALSE, nullptr, &stream))) {
        return false;
    }
    IXmlReader* reader = nullptr;
    HRESULT result = CreateXmlReader(__uuidof(IXmlReader), reinterpret_cast<void**>(&reader), nullptr);
    if (SUCCEEDED(result)) {
        result = reader->SetInput(stream);
    }
    SettingsSnapshot loaded = {};
    loaded.language = appLanguage;
    bool rootFound = false;
    XmlNodeType nodeType = XmlNodeType_None;
    while (SUCCEEDED(result) && (result = reader->Read(&nodeType)) == S_OK) {
        if (nodeType != XmlNodeType_Element) {
            continue;
        }
        const wchar_t* localName = nullptr;
        UINT nameLength = 0;
        if (FAILED(reader->GetLocalName(&localName, &nameLength)) || localName == nullptr) {
            result = E_FAIL;
            break;
        }
        std::wstring element(localName, nameLength);
        if (element == L"CalClockSettings") {
            if (rootFound) {
                result = E_FAIL;
                break;
            }
            LONGLONG number = 0;
            if (!ReadXmlNumberAttribute(reader, L"version", &number) || number != 1) {
                result = E_FAIL;
                break;
            }
            rootFound = true;
            if (ReadXmlNumberAttribute(reader, L"language", &number) && number >= 0 && number < LANG_COUNT) {
                loaded.language = static_cast<AppLanguage>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"disableThemes", &number)) {
                loaded.themesDisabled = number != 0;
            }
            if (ReadXmlNumberAttribute(reader, L"fontAntialiasing", &number) && number >= 0 && number < FONT_ANTIALIAS_COUNT) {
                loaded.fontAntialiasing = static_cast<int>(number);
            }
            std::wstring applicationFontFace;
            if (ReadXmlAttribute(reader, L"fontFace", &applicationFontFace) && applicationFontFace.size() < LF_FACESIZE) {
                loaded.fontFace = applicationFontFace;
            }
            if (ReadXmlNumberAttribute(reader, L"fontDialogSize", &number)) {
                int savedSize = static_cast<int>(number);
                loaded.fontDialogSize = std::clamp(savedSize < 10 ? savedSize * 10 : savedSize, 10, 9990);
            }
            if (ReadXmlNumberAttribute(reader, L"fontWeight", &number)) {
                loaded.fontWeight = std::clamp(static_cast<int>(number), 0, 1000);
            }
            if (ReadXmlNumberAttribute(reader, L"fontItalic", &number)) {
                loaded.fontItalic = number != 0;
            }
            if (ReadXmlNumberAttribute(reader, L"useNtpTime", &number)) {
                loaded.useNtpTime = number != 0;
            }
            if (ReadXmlNumberAttribute(reader, L"ntpPreset", &number) && number >= 0 && number < NTP_PRESET_COUNT) {
                loaded.ntpPreset = static_cast<int>(number);
            }
            std::wstring text;
            if (ReadXmlAttribute(reader, L"ntpServers", &text) && text.size() <= 1024) {
                loaded.ntpServers = text;
            }
            if (ReadXmlNumberAttribute(reader, L"settingsX", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.settingsX = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"settingsY", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.settingsY = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"helpX", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.helpX = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"helpY", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.helpY = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"aboutX", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.aboutX = static_cast<int>(number);
            }
            if (ReadXmlNumberAttribute(reader, L"aboutY", &number) && number >= INT_MIN && number <= INT_MAX) {
                loaded.aboutY = static_cast<int>(number);
            }
        } else if (element == L"Widget" && rootFound) {
            if (loaded.widgets.size() >= 32) {
                result = E_FAIL;
                break;
            }
            WidgetConfig config = {};
            ReadWidgetXml(reader, static_cast<int>(loaded.widgets.size()), loaded.fontAntialiasing, &config);
            loaded.widgets.push_back(config);
        }
    }
    bool valid = SUCCEEDED(result) && rootFound && !loaded.widgets.empty();
    if (valid) {
        std::vector<int> ids;
        for (size_t index = 0; index < loaded.widgets.size(); index++) {
            int id = loaded.widgets[index].id;
            if (id <= 0 || std::find(ids.begin(), ids.end(), id) != ids.end()) {
                valid = false;
                break;
            }
            ids.push_back(id);
        }
    }
    if (reader != nullptr) {
        reader->Release();
    }
    stream->Release();
    if (valid) {
        *snapshot = std::move(loaded);
    }
    return valid;
}

static void ApplySettingsSnapshot(const SettingsSnapshot& snapshot) {
    appLanguage = snapshot.language;
    themesDisabled = snapshot.themesDisabled;
    appFontAntialiasing = std::clamp(snapshot.fontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
    appFontFace = snapshot.fontFace.size() < LF_FACESIZE ? snapshot.fontFace : L"";
    appFontDialogSize = std::clamp(snapshot.fontDialogSize, 10, 9990);
    appFontWeight = std::clamp(snapshot.fontWeight, 0, 1000);
    appFontItalic = snapshot.fontItalic;
    useNtpTime = snapshot.useNtpTime;
    ntpPreset = std::clamp(snapshot.ntpPreset, 0, NTP_PRESET_COUNT - 1);
    ntpServers = ntpPreset == NTP_PRESET_CUSTOM ? snapshot.ntpServers : NtpServersForPreset(ntpPreset);
    if (ntpServers.empty()) {
        ntpPreset = NTP_PRESET_GLOBAL;
        ntpServers = NtpServersForPreset(ntpPreset);
    }
    ntpGeneration++;
    ntpTimeValid = false;
    ntpActiveServer.clear();
    ntpLastQueryFailed = false;
    lastNtpAttemptTick = 0;
    settingsX = snapshot.settingsX;
    settingsY = snapshot.settingsY;
    helpX = snapshot.helpX;
    helpY = snapshot.helpY;
    aboutX = snapshot.aboutX;
    aboutY = snapshot.aboutY;
    widgets.clear();
    nextWidgetId = 1;
    for (size_t index = 0; index < snapshot.widgets.size(); index++) {
        std::unique_ptr<Widget> widget(new Widget());
        widget->config = snapshot.widgets[index];
        nextWidgetId = std::max(nextWidgetId, widget->config.id + 1);
        widgets.push_back(std::move(widget));
    }
}

static void LoadTimeZones() {
    timeZones.clear();
    DWORD index = 0;
    DYNAMIC_TIME_ZONE_INFORMATION zone = {};
    while (EnumDynamicTimeZoneInformation(index, &zone) == ERROR_SUCCESS) {
        timeZones.push_back(zone);
        index++;
    }
    std::sort(timeZones.begin(), timeZones.end(),
              [](const DYNAMIC_TIME_ZONE_INFORMATION& left, const DYNAMIC_TIME_ZONE_INFORMATION& right) { return _wcsicmp(left.StandardName, right.StandardName) < 0; });
}

static void ReadWidgetConfig(HKEY key, WidgetConfig* config) {
    DWORD value = 0;
    if (ReadDword(key, L"Id", &value)) {
        config->id = static_cast<int>(value);
    }
    if (ReadDword(key, L"Type", &value) && value < WIDGET_TYPE_COUNT) {
        config->type = static_cast<WidgetType>(value);
    }
    ReadString(key, L"Name", &config->name);
    if (ReadDword(key, L"Visible", &value)) {
        config->visible = value != 0;
    }
    if (ReadDword(key, L"TopMost", &value)) {
        config->topMost = value != 0;
    }
    if (ReadDword(key, L"ShowSeconds", &value)) {
        config->showSeconds = value != 0;
    }
    if (ReadDword(key, L"ShowUtc", &value)) {
        config->showUtc = value != 0;
    }
    if (ReadDword(key, L"ShowUtcText", &value)) {
        config->showUtcText = value != 0;
    }
    if (ReadDword(key, L"WidgetLanguage", &value) && value < LANG_COUNT) {
        config->language = static_cast<AppLanguage>(value);
    }
    ReadString(key, L"TimeZoneKey", &config->timeZoneKey);
    ReadString(key, L"MonitorDevices", &config->monitorDevices);
    if (ReadDword(key, L"BlackoutOtherMonitors", &value)) {
        config->blackoutOtherMonitors = value != 0;
    }
    ReadQword(key, L"OffsetMilliseconds", &config->offsetMilliseconds);
    if (ReadDword(key, L"X", &value)) {
        config->x = static_cast<int>(value);
    }
    if (ReadDword(key, L"Y", &value)) {
        config->y = static_cast<int>(value);
    }
    if (ReadDword(key, L"PreviewX", &value)) {
        config->previewX = static_cast<int>(value);
    }
    if (ReadDword(key, L"PreviewY", &value)) {
        config->previewY = static_cast<int>(value);
    }
    if (ReadDword(key, L"Size", &value)) {
        config->size = static_cast<int>(value);
    }
    if (ReadDword(key, L"Opacity", &value)) {
        config->opacity = std::clamp(static_cast<int>(value), 5, 100);
    }
    if (ReadDword(key, L"FontSize", &value)) {
        config->fontSize = std::clamp(static_cast<int>(value), config->type == WIDGET_FULLSCREEN ? 5 : 10, config->type == WIDGET_FULLSCREEN ? 85 : 140);
    }
    if (config->type == WIDGET_DIGITAL) {
        config->fontDialogSize = config->fontSize * 10;
    }
    if (ReadDword(key, L"FontDialogSize", &value)) {
        int savedSize = static_cast<int>(value);
        config->fontDialogSize = std::clamp(savedSize < 10 ? savedSize * 10 : savedSize, 10, 9990);
    }
    if (ReadDword(key, L"FontAntialiasing", &value) && value < FONT_ANTIALIAS_COUNT) {
        config->fontAntialiasing = static_cast<int>(value);
    }
    if (ReadDword(key, L"LeadingZero", &value)) {
        config->leadingZero = value != 0;
    }
    if (ReadDword(key, L"TransparentBackground", &value)) {
        config->transparentBackground = value != 0;
    }
    if (ReadDword(key, L"DisableThemes", &value)) {
        config->disableThemes = value != 0;
    }
    ReadString(key, L"FontFace", &config->fontFace);
    if (config->fontFace.empty()) {
        config->fontFace = L"Segoe UI";
    }
    if (ReadDword(key, L"FontWeight", &value)) {
        config->fontWeight = std::clamp(static_cast<int>(value), 0, 1000);
    }
    if (ReadDword(key, L"FontItalic", &value)) {
        config->fontItalic = value != 0;
    }
    if (ReadDword(key, L"FontUnderline", &value)) {
        config->fontUnderline = value != 0;
    }
    if (ReadDword(key, L"FontStrikeOut", &value)) {
        config->fontStrikeOut = value != 0;
    }
    if (ReadDword(key, L"FontCharSet", &value)) {
        config->fontCharSet = static_cast<BYTE>(value);
    }
    config->panelTopFont = GetWidgetFontSelection(*config);
    config->panelTimeFont = config->panelTopFont;
    config->panelBottomFont = config->panelTopFont;
    ReadString(key, L"PanelTopFontFace", &config->panelTopFont.face);
    if (ReadDword(key, L"PanelTopFontSize", &value)) {
        config->panelTopFont.dialogSize = std::clamp(static_cast<int>(value), 10, 9990);
    }
    if (ReadDword(key, L"PanelTopFontWeight", &value)) {
        config->panelTopFont.weight = std::clamp(static_cast<int>(value), 0, 1000);
    }
    if (ReadDword(key, L"PanelTopFontItalic", &value)) {
        config->panelTopFont.italic = value != 0;
    }
    if (ReadDword(key, L"PanelTopFontUnderline", &value)) {
        config->panelTopFont.underline = value != 0;
    }
    if (ReadDword(key, L"PanelTopFontStrikeOut", &value)) {
        config->panelTopFont.strikeOut = value != 0;
    }
    if (ReadDword(key, L"PanelTopFontCharSet", &value)) {
        config->panelTopFont.charSet = static_cast<BYTE>(value);
    }
    ReadString(key, L"PanelTimeFontFace", &config->panelTimeFont.face);
    if (ReadDword(key, L"PanelTimeFontSize", &value)) {
        config->panelTimeFont.dialogSize = std::clamp(static_cast<int>(value), 10, 9990);
    }
    if (ReadDword(key, L"PanelTimeFontWeight", &value)) {
        config->panelTimeFont.weight = std::clamp(static_cast<int>(value), 0, 1000);
    }
    if (ReadDword(key, L"PanelTimeFontItalic", &value)) {
        config->panelTimeFont.italic = value != 0;
    }
    if (ReadDword(key, L"PanelTimeFontUnderline", &value)) {
        config->panelTimeFont.underline = value != 0;
    }
    if (ReadDword(key, L"PanelTimeFontStrikeOut", &value)) {
        config->panelTimeFont.strikeOut = value != 0;
    }
    if (ReadDword(key, L"PanelTimeFontCharSet", &value)) {
        config->panelTimeFont.charSet = static_cast<BYTE>(value);
    }
    ReadString(key, L"PanelBottomFontFace", &config->panelBottomFont.face);
    if (ReadDword(key, L"PanelBottomFontSize", &value)) {
        config->panelBottomFont.dialogSize = std::clamp(static_cast<int>(value), 10, 9990);
    }
    if (ReadDword(key, L"PanelBottomFontWeight", &value)) {
        config->panelBottomFont.weight = std::clamp(static_cast<int>(value), 0, 1000);
    }
    if (ReadDword(key, L"PanelBottomFontItalic", &value)) {
        config->panelBottomFont.italic = value != 0;
    }
    if (ReadDword(key, L"PanelBottomFontUnderline", &value)) {
        config->panelBottomFont.underline = value != 0;
    }
    if (ReadDword(key, L"PanelBottomFontStrikeOut", &value)) {
        config->panelBottomFont.strikeOut = value != 0;
    }
    if (ReadDword(key, L"PanelBottomFontCharSet", &value)) {
        config->panelBottomFont.charSet = static_cast<BYTE>(value);
    }
    if (ReadDword(key, L"Padding", &value)) {
        config->padding = std::clamp(static_cast<int>(value), 0, 70);
    }
    if (ReadDword(key, L"BorderStyle", &value)) {
        config->borderStyle = std::clamp(static_cast<int>(value), 0, DIGITAL_BORDER_STYLE_COUNT - 1);
    }
    if (ReadDword(key, L"BorderWidth", &value)) {
        config->borderWidth = std::clamp(static_cast<int>(value), 0, DIGITAL_BORDER_WIDTH_MAX);
    }
    if (ReadDword(key, L"TextColor", &value)) {
        config->textColor = static_cast<COLORREF>(value);
    }
    if (ReadDword(key, L"BackgroundColor", &value)) {
        config->backgroundColor = static_cast<COLORREF>(value);
    }
    if (ReadDword(key, L"AlarmTextColor", &value)) {
        config->alarmTextColor = static_cast<COLORREF>(value);
    }
    if (ReadDword(key, L"AlarmBackgroundColor", &value)) {
        config->alarmBackgroundColor = static_cast<COLORREF>(value);
    }
    if (ReadDword(key, L"WeekNumbers", &value)) {
        config->weekNumbers = value != 0;
    }
    if (ReadDword(key, L"SundayFirst", &value)) {
        config->sundayFirst = value != 0;
    }
    if (ReadDword(key, L"DateCopyFormat", &value) && value < DATE_FORMAT_COUNT) {
        config->dateCopyFormat = static_cast<int>(value);
    }
    if (ReadDword(key, L"AlarmEnabled", &value)) {
        config->alarmEnabled = value != 0;
    }
    if (ReadDword(key, L"AlarmHour", &value) && value < 24) {
        config->alarmHour = static_cast<int>(value);
    }
    if (ReadDword(key, L"AlarmMinute", &value) && value < 60) {
        config->alarmMinute = static_cast<int>(value);
    }
    if (ReadDword(key, L"RunCommand", &value)) {
        config->runCommand = value != 0;
    }
    if (ReadDword(key, L"LoopAudio", &value)) {
        config->loopAudio = value != 0;
    }
    ReadString(key, L"Command", &config->command);
    if (ReadDword(key, L"CallRemoteScript", &value)) {
        config->callRemoteScript = value != 0;
    }
    ReadString(key, L"RemoteScriptUrl", &config->remoteScriptUrl);
    nextWidgetId = std::max(nextWidgetId, config->id + 1);
}

static void LoadAllSettings() {
    SelectSystemLanguage();
    ntpPreset = NTP_PRESET_AUTO;
    ntpServers = NtpServersForPreset(ntpPreset);
    LoadTimeZones();
    std::wstring xmlPath = AutomaticXmlSettingsPath(false);
    storageUsesXml = !xmlPath.empty() && GetFileAttributesW(xmlPath.c_str()) != INVALID_FILE_ATTRIBUTES;
    if (storageUsesXml) {
        SettingsSnapshot snapshot = {};
        if (ReadSettingsXml(xmlPath, &snapshot)) {
            ApplySettingsSnapshot(snapshot);
            return;
        }
    }
    HKEY root = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_PATH, 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS, &root) != ERROR_SUCCESS) {
        std::unique_ptr<Widget> widget(new Widget());
        widget->config = DefaultConfig(WIDGET_ANALOG, 0);
        widgets.push_back(std::move(widget));
        return;
    }
    DWORD value = 0;
    if (ReadDword(root, L"Language", &value) && value < LANG_COUNT) {
        appLanguage = static_cast<AppLanguage>(value);
    }
    if (ReadDword(root, L"DisableThemes", &value)) {
        themesDisabled = value != 0;
    } else if (ReadDword(root, L"VisualStyles", &value)) {
        themesDisabled = value == 0;
    }
    if (ReadDword(root, L"FontAntialiasing", &value) && value < FONT_ANTIALIAS_COUNT) {
        appFontAntialiasing = static_cast<int>(value);
    }
    ReadString(root, L"FontFace", &appFontFace);
    if (appFontFace.size() >= LF_FACESIZE) {
        appFontFace.clear();
    }
    if (ReadDword(root, L"FontDialogSize", &value)) {
        int savedSize = static_cast<int>(value);
        appFontDialogSize = std::clamp(savedSize < 10 ? savedSize * 10 : savedSize, 10, 9990);
    }
    if (ReadDword(root, L"FontWeight", &value)) {
        appFontWeight = std::clamp(static_cast<int>(value), 0, 1000);
    }
    if (ReadDword(root, L"FontItalic", &value)) {
        appFontItalic = value != 0;
    }
    if (ReadDword(root, L"UseNtpTime", &value)) {
        useNtpTime = value != 0;
    }
    if (ReadDword(root, L"NtpPreset", &value) && value < NTP_PRESET_COUNT) {
        ntpPreset = static_cast<int>(value);
    }
    ReadString(root, L"NtpServers", &ntpServers);
    if (ntpPreset != NTP_PRESET_CUSTOM) {
        ntpServers = NtpServersForPreset(ntpPreset);
    } else if (ntpServers.empty() || ntpServers.size() > 1024) {
        ntpPreset = NTP_PRESET_GLOBAL;
        ntpServers = NtpServersForPreset(ntpPreset);
    }
    if (ReadDword(root, L"SettingsX", &value)) {
        settingsX = static_cast<int>(value);
    }
    if (ReadDword(root, L"SettingsY", &value)) {
        settingsY = static_cast<int>(value);
    }
    if (ReadDword(root, L"HelpX", &value)) {
        helpX = static_cast<int>(value);
    }
    if (ReadDword(root, L"HelpY", &value)) {
        helpY = static_cast<int>(value);
    }
    if (ReadDword(root, L"AboutX", &value)) {
        aboutX = static_cast<int>(value);
    }
    if (ReadDword(root, L"AboutY", &value)) {
        aboutY = static_cast<int>(value);
    }
    HKEY collection = nullptr;
    DWORD count = 0;
    if (RegOpenKeyExW(root, L"Widgets", 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS, &collection) == ERROR_SUCCESS && ReadDword(collection, L"Count", &count)) {
        count = std::min<DWORD>(count, 32);
        for (DWORD index = 0; index < count; index++) {
            wchar_t subkey[24] = {};
            swprintf_s(subkey, L"%u", index);
            HKEY item = nullptr;
            if (RegOpenKeyExW(collection, subkey, 0, KEY_QUERY_VALUE, &item) == ERROR_SUCCESS) {
                std::unique_ptr<Widget> widget(new Widget());
                widget->config = DefaultConfig(WIDGET_ANALOG, static_cast<int>(index));
                ReadWidgetConfig(item, &widget->config);
                widgets.push_back(std::move(widget));
                RegCloseKey(item);
            }
        }
        RegCloseKey(collection);
    }
    if (widgets.empty()) {
        std::unique_ptr<Widget> widget(new Widget());
        widget->config = DefaultConfig(WIDGET_ANALOG, 0);
        if (ReadDword(root, L"ClockSize", &value)) {
            widget->config.size = static_cast<int>(value);
        }
        if (ReadDword(root, L"ShowSeconds", &value)) {
            widget->config.showSeconds = value != 0;
        }
        if (ReadDword(root, L"ShowUtc", &value)) {
            widget->config.showUtc = value != 0;
        }
        if (ReadDword(root, L"AlwaysOnTop", &value)) {
            widget->config.topMost = value != 0;
        }
        if (ReadDword(root, L"ClockVisible", &value)) {
            widget->config.visible = value != 0;
        }
        if (ReadDword(root, L"PopupX", &value)) {
            widget->config.x = static_cast<int>(value);
        }
        if (ReadDword(root, L"PopupY", &value)) {
            widget->config.y = static_cast<int>(value);
        }
        if (ReadDword(root, L"AlarmEnabled", &value)) {
            widget->config.alarmEnabled = value != 0;
        }
        if (ReadDword(root, L"AlarmHour", &value)) {
            widget->config.alarmHour = static_cast<int>(value);
        }
        if (ReadDword(root, L"AlarmMinute", &value)) {
            widget->config.alarmMinute = static_cast<int>(value);
        }
        if (ReadDword(root, L"AlarmRunCommand", &value)) {
            widget->config.runCommand = value != 0;
        }
        if (ReadDword(root, L"AlarmLoopAudio", &value)) {
            widget->config.loopAudio = value != 0;
        }
        ReadQword(root, L"ClockOffsetMilliseconds", &widget->config.offsetMilliseconds);
        ReadString(root, L"TimeZoneKey", &widget->config.timeZoneKey);
        ReadString(root, L"AlarmCommand", &widget->config.command);
        widgets.push_back(std::move(widget));
    }
    RegCloseKey(root);
}

static void WriteWidgetConfig(HKEY key, const WidgetConfig& config) {
    WriteDword(key, L"Id", config.id);
    WriteDword(key, L"Type", config.type);
    WriteString(key, L"Name", config.name);
    WriteDword(key, L"Visible", config.visible);
    WriteDword(key, L"TopMost", config.topMost);
    WriteDword(key, L"ShowSeconds", config.showSeconds);
    WriteDword(key, L"ShowUtc", config.showUtc);
    WriteDword(key, L"ShowUtcText", config.showUtcText);
    WriteDword(key, L"WidgetLanguage", config.language);
    WriteString(key, L"TimeZoneKey", config.timeZoneKey);
    WriteString(key, L"MonitorDevices", config.monitorDevices);
    WriteDword(key, L"BlackoutOtherMonitors", config.blackoutOtherMonitors);
    WriteQword(key, L"OffsetMilliseconds", config.offsetMilliseconds);
    WriteDword(key, L"X", config.x);
    WriteDword(key, L"Y", config.y);
    WriteDword(key, L"PreviewX", config.previewX);
    WriteDword(key, L"PreviewY", config.previewY);
    WriteDword(key, L"Size", config.size);
    WriteDword(key, L"Opacity", config.opacity);
    WriteDword(key, L"FontSize", config.fontSize);
    WriteDword(key, L"FontDialogSize", config.fontDialogSize);
    WriteDword(key, L"FontAntialiasing", config.fontAntialiasing);
    WriteDword(key, L"LeadingZero", config.leadingZero);
    WriteDword(key, L"TransparentBackground", config.transparentBackground);
    WriteDword(key, L"DisableThemes", config.disableThemes);
    WriteString(key, L"FontFace", config.fontFace);
    WriteDword(key, L"FontWeight", config.fontWeight);
    WriteDword(key, L"FontItalic", config.fontItalic);
    WriteDword(key, L"FontUnderline", config.fontUnderline);
    WriteDword(key, L"FontStrikeOut", config.fontStrikeOut);
    WriteDword(key, L"FontCharSet", config.fontCharSet);
    WriteString(key, L"PanelTopFontFace", config.panelTopFont.face);
    WriteDword(key, L"PanelTopFontSize", config.panelTopFont.dialogSize);
    WriteDword(key, L"PanelTopFontWeight", config.panelTopFont.weight);
    WriteDword(key, L"PanelTopFontItalic", config.panelTopFont.italic);
    WriteDword(key, L"PanelTopFontUnderline", config.panelTopFont.underline);
    WriteDword(key, L"PanelTopFontStrikeOut", config.panelTopFont.strikeOut);
    WriteDword(key, L"PanelTopFontCharSet", config.panelTopFont.charSet);
    WriteString(key, L"PanelTimeFontFace", config.panelTimeFont.face);
    WriteDword(key, L"PanelTimeFontSize", config.panelTimeFont.dialogSize);
    WriteDword(key, L"PanelTimeFontWeight", config.panelTimeFont.weight);
    WriteDword(key, L"PanelTimeFontItalic", config.panelTimeFont.italic);
    WriteDword(key, L"PanelTimeFontUnderline", config.panelTimeFont.underline);
    WriteDword(key, L"PanelTimeFontStrikeOut", config.panelTimeFont.strikeOut);
    WriteDword(key, L"PanelTimeFontCharSet", config.panelTimeFont.charSet);
    WriteString(key, L"PanelBottomFontFace", config.panelBottomFont.face);
    WriteDword(key, L"PanelBottomFontSize", config.panelBottomFont.dialogSize);
    WriteDword(key, L"PanelBottomFontWeight", config.panelBottomFont.weight);
    WriteDword(key, L"PanelBottomFontItalic", config.panelBottomFont.italic);
    WriteDword(key, L"PanelBottomFontUnderline", config.panelBottomFont.underline);
    WriteDword(key, L"PanelBottomFontStrikeOut", config.panelBottomFont.strikeOut);
    WriteDword(key, L"PanelBottomFontCharSet", config.panelBottomFont.charSet);
    WriteDword(key, L"Padding", config.padding);
    WriteDword(key, L"BorderStyle", config.borderStyle);
    WriteDword(key, L"BorderWidth", config.borderWidth);
    WriteDword(key, L"TextColor", config.textColor);
    WriteDword(key, L"BackgroundColor", config.backgroundColor);
    WriteDword(key, L"AlarmTextColor", config.alarmTextColor);
    WriteDword(key, L"AlarmBackgroundColor", config.alarmBackgroundColor);
    WriteDword(key, L"WeekNumbers", config.weekNumbers);
    WriteDword(key, L"SundayFirst", config.sundayFirst);
    WriteDword(key, L"DateCopyFormat", config.dateCopyFormat);
    WriteDword(key, L"AlarmEnabled", config.alarmEnabled);
    WriteDword(key, L"AlarmHour", config.alarmHour);
    WriteDword(key, L"AlarmMinute", config.alarmMinute);
    WriteDword(key, L"RunCommand", config.runCommand);
    WriteDword(key, L"LoopAudio", config.loopAudio);
    WriteString(key, L"Command", config.command);
    WriteDword(key, L"CallRemoteScript", config.callRemoteScript);
    WriteString(key, L"RemoteScriptUrl", config.remoteScriptUrl);
}

static bool IsObsoleteWidgetRegistryKey(const wchar_t* name, size_t widgetCount) {
    if (name == nullptr || name[0] == L'\0') {
        return false;
    }
    size_t index = 0;
    for (const wchar_t* character = name; *character != L'\0'; character++) {
        if (!iswdigit(*character)) {
            return false;
        }
        size_t digit = static_cast<size_t>(*character - L'0');
        if (index > (SIZE_MAX - digit) / 10) {
            return true;
        }
        index = index * 10 + digit;
    }
    return index >= widgetCount;
}

static void RemoveObsoleteWidgetRegistryKeys(HKEY collection, size_t widgetCount) {
    std::vector<std::wstring> obsoleteKeys;
    for (DWORD keyIndex = 0;; keyIndex++) {
        wchar_t name[256] = {};
        DWORD nameLength = ARRAYSIZE(name);
        LSTATUS result = RegEnumKeyExW(collection, keyIndex, name, &nameLength, nullptr, nullptr, nullptr, nullptr);
        if (result == ERROR_NO_MORE_ITEMS) {
            break;
        }
        if (result != ERROR_SUCCESS) {
            break;
        }
        if (IsObsoleteWidgetRegistryKey(name, widgetCount)) {
            obsoleteKeys.push_back(name);
        }
    }
    for (size_t index = 0; index < obsoleteKeys.size(); index++) {
        RegDeleteTreeW(collection, obsoleteKeys[index].c_str());
    }
}

static void SaveAllSettings() {
    if (storageUsesXml) {
        std::wstring path = AutomaticXmlSettingsPath(true);
        if (WriteSettingsXml(path, CaptureSettingsSnapshot())) {
            RegDeleteTreeW(HKEY_CURRENT_USER, REGISTRY_PATH);
            RegDeleteKeyW(HKEY_CURRENT_USER, VENDOR_REGISTRY_PATH);
        }
        return;
    }
    HKEY root = nullptr;
    DWORD disposition = 0;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, REGISTRY_PATH, 0, nullptr, 0, KEY_SET_VALUE | KEY_CREATE_SUB_KEY, nullptr, &root, &disposition) != ERROR_SUCCESS) {
        return;
    }
    WriteDword(root, L"SchemaVersion", 11);
    WriteDword(root, L"Language", appLanguage);
    WriteDword(root, L"DisableThemes", themesDisabled);
    WriteDword(root, L"VisualStyles", !themesDisabled);
    WriteDword(root, L"FontAntialiasing", appFontAntialiasing);
    WriteString(root, L"FontFace", appFontFace);
    WriteDword(root, L"FontDialogSize", appFontDialogSize);
    WriteDword(root, L"FontWeight", appFontWeight);
    WriteDword(root, L"FontItalic", appFontItalic);
    WriteDword(root, L"UseNtpTime", useNtpTime);
    WriteDword(root, L"NtpPreset", ntpPreset);
    WriteString(root, L"NtpServers", ntpServers);
    WriteDword(root, L"SettingsX", settingsX);
    WriteDword(root, L"SettingsY", settingsY);
    WriteDword(root, L"HelpX", helpX);
    WriteDword(root, L"HelpY", helpY);
    WriteDword(root, L"AboutX", aboutX);
    WriteDword(root, L"AboutY", aboutY);
    HKEY collection = nullptr;
    REGSAM collectionAccess = KEY_SET_VALUE | KEY_QUERY_VALUE | KEY_CREATE_SUB_KEY | KEY_ENUMERATE_SUB_KEYS | DELETE;
    if (RegCreateKeyExW(root, L"Widgets", 0, nullptr, 0, collectionAccess, nullptr, &collection, &disposition) == ERROR_SUCCESS) {
        WriteDword(collection, L"Count", static_cast<DWORD>(widgets.size()));
        for (size_t index = 0; index < widgets.size(); index++) {
            wchar_t subkey[24] = {};
            swprintf_s(subkey, L"%zu", index);
            HKEY item = nullptr;
            if (RegCreateKeyExW(collection, subkey, 0, nullptr, 0, KEY_SET_VALUE, nullptr, &item, &disposition) == ERROR_SUCCESS) {
                WriteWidgetConfig(item, widgets[index]->config);
                RegCloseKey(item);
            }
        }
        RemoveObsoleteWidgetRegistryKeys(collection, widgets.size());
        RegCloseKey(collection);
    }
    RegCloseKey(root);
    RemoveAutomaticXmlSettings();
}

static bool SplitNumericInput(const wchar_t* text, bool allowSign, bool* negative, std::vector<std::wstring>* groups) {
    if (text == nullptr || groups == nullptr) {
        return false;
    }
    groups->clear();
    const wchar_t* position = text;
    while (iswspace(*position)) {
        position++;
    }
    bool parsedNegative = false;
    if (*position == L'-' || *position == L'+') {
        if (!allowSign) {
            return false;
        }
        parsedNegative = *position == L'-';
        position++;
    }
    while (*position != 0) {
        if (iswdigit(*position)) {
            const wchar_t* start = position;
            while (iswdigit(*position)) {
                position++;
            }
            groups->emplace_back(start, position);
            continue;
        }
        if (iswalpha(*position) || *position == L'_') {
            return false;
        }
        position++;
    }
    if (negative != nullptr) {
        *negative = parsedNegative;
    }
    return !groups->empty();
}

static bool ParseUnsignedGroup(const std::wstring& text, ULONGLONG* value) {
    if (text.empty() || value == nullptr) {
        return false;
    }
    ULONGLONG parsed = 0;
    for (wchar_t character : text) {
        unsigned int digit = static_cast<unsigned int>(character - L'0');
        if (parsed > (ULLONG_MAX - digit) / 10) {
            return false;
        }
        parsed = parsed * 10 + digit;
    }
    *value = parsed;
    return true;
}

static bool ParseOffset(const wchar_t* text, LONGLONG* result) {
    if (result == nullptr) {
        return false;
    }
    bool negative = false;
    std::vector<std::wstring> groups;
    if (!SplitNumericInput(text, true, &negative, &groups) || groups.size() > 4) {
        return false;
    }
    ULONGLONG hours = 0;
    ULONGLONG minutes = 0;
    ULONGLONG seconds = 0;
    ULONGLONG hundredths = 0;
    if (groups.size() == 1) {
        const std::wstring& compact = groups[0];
        size_t secondsStart = compact.size() > 2 ? compact.size() - 2 : 0;
        size_t minutesStart = secondsStart > 2 ? secondsStart - 2 : 0;
        if (!ParseUnsignedGroup(compact.substr(secondsStart), &seconds)) {
            return false;
        }
        if (secondsStart > 0 && !ParseUnsignedGroup(compact.substr(minutesStart, secondsStart - minutesStart), &minutes)) {
            return false;
        }
        if (minutesStart > 0 && !ParseUnsignedGroup(compact.substr(0, minutesStart), &hours)) {
            return false;
        }
    } else {
        ULONGLONG values[4] = {};
        for (size_t index = 0; index < groups.size(); index++) {
            if (!ParseUnsignedGroup(groups[index], &values[index])) {
                return false;
            }
        }
        if (groups.size() == 2) {
            minutes = values[0];
            seconds = values[1];
        } else if (groups.size() == 3) {
            hours = values[0];
            minutes = values[1];
            seconds = values[2];
        } else if (groups.size() == 4) {
            hours = values[0];
            minutes = values[1];
            seconds = values[2];
            hundredths = values[3];
        } else {
            return false;
        }
    }
    if (minutes > 59 || seconds > 59 || hundredths > 99 || hours > static_cast<ULONGLONG>(LLONG_MAX) / 3600000ULL) {
        return false;
    }
    ULONGLONG milliseconds = ((hours * 60ULL + minutes) * 60ULL + seconds) * 1000ULL + hundredths * 10ULL;
    if (milliseconds > static_cast<ULONGLONG>(LLONG_MAX)) {
        return false;
    }
    *result = negative ? -static_cast<LONGLONG>(milliseconds) : static_cast<LONGLONG>(milliseconds);
    return true;
}

static std::wstring FormatOffset(LONGLONG milliseconds) {
    bool negative = milliseconds < 0;
    ULONGLONG value = negative ? static_cast<ULONGLONG>(-(milliseconds + 1)) + 1ULL : static_cast<ULONGLONG>(milliseconds);
    ULONGLONG hours = value / 3600000;
    int minutes = static_cast<int>((value / 60000) % 60);
    int seconds = static_cast<int>((value / 1000) % 60);
    int hundredths = static_cast<int>((value / 10) % 100);
    wchar_t text[64] = {};
    swprintf_s(text, L"%s%02llu:%02d:%02d.%02d", negative ? L"-" : L"", hours, minutes, seconds, hundredths);
    return text;
}

static bool ParseAlarmTime(const wchar_t* text, int* hour, int* minute) {
    if (hour == nullptr || minute == nullptr) {
        return false;
    }
    std::vector<std::wstring> groups;
    if (!SplitNumericInput(text, false, nullptr, &groups) || groups.size() > 2) {
        return false;
    }
    if (groups.size() == 1) {
        if (groups[0].size() < 1 || groups[0].size() > 4) {
            return false;
        }
        if (groups[0].size() == 3 || groups[0].size() == 4) {
            size_t hourDigits = groups[0].size() - 2;
            std::wstring compact = groups[0];
            groups.clear();
            groups.push_back(compact.substr(0, hourDigits));
            groups.push_back(compact.substr(hourDigits));
        }
    }
    ULONGLONG parsedHour = 0;
    ULONGLONG parsedMinute = 0;
    if (!ParseUnsignedGroup(groups[0], &parsedHour) || (groups.size() == 2 && !ParseUnsignedGroup(groups[1], &parsedMinute)) || parsedHour > 23 || parsedMinute > 59) {
        return false;
    }
    *hour = static_cast<int>(parsedHour);
    *minute = static_cast<int>(parsedMinute);
    return true;
}

static ULONGLONG CurrentFileTimeValue() {
    FILETIME fileTime = {};
    typedef VOID(WINAPI* GetPreciseTimeProc)(LPFILETIME fileTime);
    static GetPreciseTimeProc getPreciseTime = []() {
        HMODULE kernel = GetModuleHandleW(L"kernel32.dll");
        return kernel == nullptr ? static_cast<GetPreciseTimeProc>(nullptr) : reinterpret_cast<GetPreciseTimeProc>(GetProcAddress(kernel, "GetSystemTimePreciseAsFileTime"));
        }();
    if (getPreciseTime != nullptr) {
        getPreciseTime(&fileTime);
    } else {
        GetSystemTimeAsFileTime(&fileTime);
    }
    ULARGE_INTEGER value = {};
    value.LowPart = fileTime.dwLowDateTime;
    value.HighPart = fileTime.dwHighDateTime;
    return value.QuadPart;
}

static void WriteNtpTimestamp(BYTE* destination, ULONGLONG fileTimeValue) {
    const ULONGLONG ntpEpochInFileTime = 94354848000000000ULL;
    ULONGLONG ntpValue = fileTimeValue - ntpEpochInFileTime;
    DWORD seconds = static_cast<DWORD>(ntpValue / 10000000ULL);
    DWORD fraction = static_cast<DWORD>(((ntpValue % 10000000ULL) << 32) / 10000000ULL);
    seconds = htonl(seconds);
    fraction = htonl(fraction);
    CopyMemory(destination, &seconds, sizeof(seconds));
    CopyMemory(destination + sizeof(seconds), &fraction, sizeof(fraction));
}

static ULONGLONG ReadNtpTimestamp(const BYTE* source, ULONGLONG referenceFileTime) {
    const ULONGLONG ntpEpochInFileTime = 94354848000000000ULL;
    DWORD secondsNetwork = 0;
    DWORD fractionNetwork = 0;
    CopyMemory(&secondsNetwork, source, sizeof(secondsNetwork));
    CopyMemory(&fractionNetwork, source + sizeof(secondsNetwork), sizeof(fractionNetwork));
    ULONGLONG seconds = ntohl(secondsNetwork);
    ULONGLONG fraction = ntohl(fractionNetwork);
    ULONGLONG referenceSeconds = (referenceFileTime - ntpEpochInFileTime) / 10000000ULL;
    ULONGLONG candidate = (referenceSeconds & 0xFFFFFFFF00000000ULL) | seconds;
    if (candidate + 0x80000000ULL < referenceSeconds) {
        candidate += 0x100000000ULL;
    } else if (candidate > referenceSeconds + 0x80000000ULL && candidate >= 0x100000000ULL) {
        candidate -= 0x100000000ULL;
    }
    return ntpEpochInFileTime + candidate * 10000000ULL + ((fraction * 10000000ULL) >> 32);
}

static std::vector<std::wstring> ParseNtpServerList(const std::wstring& serverList) {
    std::vector<std::wstring> servers;
    size_t start = 0;
    while (start < serverList.size()) {
        while (start < serverList.size() && (serverList[start] == L';' || serverList[start] == L',' || iswspace(serverList[start]))) {
            start++;
        }
        size_t end = start;
        while (end < serverList.size() && serverList[end] != L';' && serverList[end] != L',' && !iswspace(serverList[end])) {
            end++;
        }
        if (end > start) {
            std::wstring server = serverList.substr(start, end - start);
            if (server.size() <= 253 && servers.size() < 8 && std::find(servers.begin(), servers.end(), server) == servers.end()) {
                servers.push_back(server);
            }
        }
        start = end;
    }
    return servers;
}

static bool QueryNtpServer(const std::wstring& server, NtpSample* bestSample) {
    ADDRINFOW hints = {};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    PADDRINFOW addresses = nullptr;
    if (GetAddrInfoW(server.c_str(), L"123", &hints, &addresses) != 0) {
        return false;
    }
    bool success = false;
    for (int attempt = 0; attempt < 4 && !ntpStopRequested; attempt++) {
        for (PADDRINFOW address = addresses; address != nullptr && !ntpStopRequested; address = address->ai_next) {
            SOCKET socketHandle = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
            if (socketHandle == INVALID_SOCKET) {
                continue;
            }
            DWORD timeout = 1200;
            setsockopt(socketHandle, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));
            setsockopt(socketHandle, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));
            bool connected = connect(socketHandle, address->ai_addr, static_cast<int>(address->ai_addrlen)) != SOCKET_ERROR;
            BYTE request[48] = {};
            request[0] = 0x23;
            ULONGLONG t1 = CurrentFileTimeValue();
            WriteNtpTimestamp(request + 40, t1);
            int sent = connected ? send(socketHandle, reinterpret_cast<const char*>(request), sizeof(request), 0) : SOCKET_ERROR;
            BYTE response[48] = {};
            int received = sent == sizeof(request) ? recv(socketHandle, reinterpret_cast<char*>(response), sizeof(response), 0) : SOCKET_ERROR;
            ULONGLONG t4 = CurrentFileTimeValue();
            closesocket(socketHandle);
            BYTE leap = response[0] >> 6;
            BYTE version = (response[0] >> 3) & 7;
            BYTE mode = response[0] & 7;
            BYTE stratum = response[1];
            BYTE zeroTimestamp[8] = {};
            if (received < static_cast<int>(sizeof(response)) || leap == 3 || version < 3 || version > 4 || mode != 4 || stratum == 0 || stratum >= 16 || memcmp(response + 24, request + 40, 8) != 0 || memcmp(response + 40, zeroTimestamp, sizeof(zeroTimestamp)) == 0) {
                continue;
            }
            ULONGLONG t2 = ReadNtpTimestamp(response + 32, t4);
            ULONGLONG t3 = ReadNtpTimestamp(response + 40, t4);
            if (t3 < t2) {
                continue;
            }
            LONGLONG firstLeg = static_cast<LONGLONG>(t2) - static_cast<LONGLONG>(t1);
            LONGLONG secondLeg = static_cast<LONGLONG>(t3) - static_cast<LONGLONG>(t4);
            LONGLONG networkDelay = static_cast<LONGLONG>(t4 - t1) - static_cast<LONGLONG>(t3 - t2);
            if (networkDelay < 0 || networkDelay > 10LL * 10000000LL) {
                continue;
            }
            NtpSample sample = {};
            sample.offset100Nanoseconds = (firstLeg + secondLeg) / 2;
            sample.delay100Nanoseconds = networkDelay;
            sample.server = server;
            if (!success || sample.delay100Nanoseconds < bestSample->delay100Nanoseconds) {
                *bestSample = sample;
            }
            success = true;
            break;
        }
        if (attempt < 3 && !ntpStopRequested) {
            Sleep(40);
        }
    }
    FreeAddrInfoW(addresses);
    return success;
}

static DWORD WINAPI NtpThreadProc(void* parameter) {
    std::unique_ptr<NtpThreadParameters> parameters(static_cast<NtpThreadParameters*>(parameter));
    std::unique_ptr<NtpThreadResult> result(new NtpThreadResult());
    result->generation = parameters->generation;
    std::vector<std::wstring> servers = ParseNtpServerList(parameters->serverList);
    std::vector<NtpSample> samples;
    for (size_t index = 0; index < servers.size() && !ntpStopRequested; index++) {
        NtpSample sample = {};
        if (QueryNtpServer(servers[index], &sample)) {
            samples.push_back(sample);
        }
    }
    if (!samples.empty()) {
        std::vector<LONGLONG> sortedOffsets;
        for (size_t index = 0; index < samples.size(); index++) {
            sortedOffsets.push_back(samples[index].offset100Nanoseconds);
        }
        std::sort(sortedOffsets.begin(), sortedOffsets.end());
        size_t middle = sortedOffsets.size() / 2;
        LONGLONG medianOffset = sortedOffsets.size() % 2 == 0 ? sortedOffsets[middle - 1] / 2 + sortedOffsets[middle] / 2 : sortedOffsets[middle];
        LONGLONG minimumDelay = samples[0].delay100Nanoseconds;
        for (size_t index = 1; index < samples.size(); index++) {
            minimumDelay = std::min(minimumDelay, samples[index].delay100Nanoseconds);
        }
        long double rejectionLimit = static_cast<long double>(std::max(1000000LL, minimumDelay * 4));
        long double weightedOffset = 0.0L;
        long double totalWeight = 0.0L;
        size_t bestIndex = 0;
        bool acceptedAny = false;
        for (size_t index = 0; index < samples.size(); index++) {
            long double difference = std::fabs(static_cast<long double>(samples[index].offset100Nanoseconds) - static_cast<long double>(medianOffset));
            if (difference > rejectionLimit) {
                continue;
            }
            LONGLONG weightedDelay = std::max(10000LL, samples[index].delay100Nanoseconds);
            long double weight = 1.0L / static_cast<long double>(weightedDelay);
            weightedOffset += static_cast<long double>(samples[index].offset100Nanoseconds) * weight;
            totalWeight += weight;
            if (!acceptedAny || samples[index].delay100Nanoseconds < samples[bestIndex].delay100Nanoseconds) {
                bestIndex = index;
            }
            acceptedAny = true;
        }
        if (!acceptedAny) {
            for (size_t index = 1; index < samples.size(); index++) {
                if (samples[index].delay100Nanoseconds < samples[bestIndex].delay100Nanoseconds) {
                    bestIndex = index;
                }
            }
            result->offset100Nanoseconds = samples[bestIndex].offset100Nanoseconds;
        } else {
            result->offset100Nanoseconds = static_cast<LONGLONG>(std::llround(weightedOffset / totalWeight));
        }
        result->server = samples[bestIndex].server;
        result->success = true;
    }
    if (ntpStopRequested) {
        ntpQueryRunning = false;
        return 0;
    }
    if (hController != nullptr && PostMessageW(hController, WM_NTP_RESULT, 0, reinterpret_cast<LPARAM>(result.get()))) {
        result.release();
    } else {
        ntpQueryRunning = false;
    }
    return 0;
}

static void StartNtpSynchronization(bool force) {
    if (!useNtpTime || !winsockReady) {
        return;
    }
    ULONGLONG now = GetTickCount64();
    ULONGLONG interval = ntpTimeValid && !ntpLastQueryFailed ? 5ULL * 60ULL * 1000ULL : 60ULL * 1000ULL;
    if (!force && lastNtpAttemptTick != 0 && now - lastNtpAttemptTick < interval) {
        return;
    }
    bool expected = false;
    if (!ntpQueryRunning.compare_exchange_strong(expected, true)) {
        return;
    }
    if (hNtpThread != nullptr) {
        CloseHandle(hNtpThread);
        hNtpThread = nullptr;
    }
    std::unique_ptr<NtpThreadParameters> parameters(new NtpThreadParameters());
    parameters->serverList = ntpServers;
    parameters->generation = ntpGeneration.load();
    ntpStopRequested = false;
    lastNtpAttemptTick = now;
    hNtpThread = CreateThread(nullptr, 0, NtpThreadProc, parameters.get(), 0, nullptr);
    if (hNtpThread == nullptr) {
        ntpQueryRunning = false;
        return;
    }
    parameters.release();
}

static bool StopNtpSynchronization() {
    ntpStopRequested = true;
    bool threadFinished = true;
    if (hNtpThread != nullptr) {
        DWORD waitResult = WaitForSingleObject(hNtpThread, 3000);
        threadFinished = waitResult == WAIT_OBJECT_0;
        CloseHandle(hNtpThread);
        hNtpThread = nullptr;
    }
    MSG pending = {};
    while (PeekMessageW(&pending, nullptr, WM_NTP_RESULT, WM_NTP_RESULT, PM_REMOVE)) {
        delete reinterpret_cast<NtpThreadResult*>(pending.lParam);
        ntpQueryRunning = false;
    }
    if (threadFinished) {
        ntpQueryRunning = false;
    }
    return threadFinished;
}

static void GetApplicationUtcTime(SYSTEMTIME* utc) {
    ULONGLONG value = CurrentFileTimeValue();
    if (useNtpTime && ntpTimeValid) {
        value = static_cast<ULONGLONG>(static_cast<LONGLONG>(value) + ntpOffset100Nanoseconds.load());
    }
    FILETIME fileTime = {};
    ULARGE_INTEGER parts = {};
    parts.QuadPart = value;
    fileTime.dwLowDateTime = parts.LowPart;
    fileTime.dwHighDateTime = parts.HighPart;
    FileTimeToSystemTime(&fileTime, utc);
}

static void GetDisplayedTime(const WidgetConfig& config, SYSTEMTIME* displayed) {
    SYSTEMTIME utc = {};
    GetApplicationUtcTime(&utc);
    if (config.showUtc) {
        *displayed = utc;
    } else {
        const DYNAMIC_TIME_ZONE_INFORMATION* selected = nullptr;
        for (size_t index = 0; index < timeZones.size(); index++) {
            if (_wcsicmp(timeZones[index].TimeZoneKeyName, config.timeZoneKey.c_str()) == 0) {
                selected = &timeZones[index];
                break;
            }
        }
        if (selected != nullptr) {
            SystemTimeToTzSpecificLocalTimeEx(selected, &utc, displayed);
        } else {
            SystemTimeToTzSpecificLocalTime(nullptr, &utc, displayed);
        }
    }
    FILETIME fileTime = {};
    SystemTimeToFileTime(displayed, &fileTime);
    ULARGE_INTEGER value = {};
    value.LowPart = fileTime.dwLowDateTime;
    value.HighPart = fileTime.dwHighDateTime;
    LONGLONG adjusted = static_cast<LONGLONG>(value.QuadPart) + config.offsetMilliseconds * 10000;
    value.QuadPart = static_cast<ULONGLONG>(adjusted);
    fileTime.dwLowDateTime = value.LowPart;
    fileTime.dwHighDateTime = value.HighPart;
    FileTimeToSystemTime(&fileTime, displayed);
}

static std::wstring FormatWidgetDate(const WidgetConfig& config, const SYSTEMTIME& date, int formatIndex) {
    static const wchar_t* patterns[DATE_FORMAT_COUNT] = { L"yyMMdd", L"yyyyMMdd", L"yy-MM-dd", L"yyyy-MM-dd", nullptr, L"dd.MM.yyyy", L"d MMM yyyy", L"d MMMM yyyy", L"dddd d MMMM yyyy", nullptr, L"ddd, dd MMM yyyy", L"yyyy/MM/dd" };
    int selected = std::clamp(formatIndex, 0, DATE_FORMAT_COUNT - 1);
    DWORD flags = selected == DATE_LOCAL_SHORT ? DATE_SHORTDATE : (selected == DATE_LOCAL_LONG ? DATE_LONGDATE : 0);
    const wchar_t* pattern = patterns[selected];
    wchar_t text[160] = {};
    int length = GetDateFormatEx(LANGUAGE_LOCALES[config.language], flags, &date, pattern, text, ARRAYSIZE(text), nullptr);
    if (length == 0) {
        swprintf_s(text, L"%04d-%02d-%02d", date.wYear, date.wMonth, date.wDay);
    }
    return text;
}

static std::wstring DateFormatCaption(const WidgetConfig& config, const SYSTEMTIME& date, int formatIndex) {
    static const wchar_t* patternNames[DATE_FORMAT_COUNT] = { L"yyMMdd", L"yyyyMMdd", L"yy-MM-dd", L"yyyy-MM-dd", nullptr, L"dd.MM.yyyy", L"d MMM yyyy", L"d MMMM yyyy", L"dddd d MMMM yyyy", nullptr, L"ddd, dd MMM yyyy", L"yyyy/MM/dd" };
    int selected = std::clamp(formatIndex, 0, DATE_FORMAT_COUNT - 1);
    const wchar_t* name =
        selected == DATE_LOCAL_SHORT ? LOCAL_SHORT_LABELS[config.language] : (selected == DATE_LOCAL_LONG ? LOCAL_LONG_LABELS[config.language] : patternNames[selected]);
    return std::wstring(name) + L"  —  " + FormatWidgetDate(config, date, selected);
}

static void ShowCopiedDateTooltip(Widget* widget, const std::wstring& text) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    if (widget->copyTooltip != nullptr && IsWindow(widget->copyTooltip)) {
        DestroyWindow(widget->copyTooltip);
    }
    widget->copyTooltipText = text;
    widget->copyTooltip = CreateWindowExW(WS_EX_TOPMOST, TOOLTIPS_CLASSW, nullptr, WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                          CW_USEDEFAULT, widget->window, nullptr, hInstance, nullptr);
    if (widget->copyTooltip == nullptr) {
        return;
    }
    TOOLINFOW information = {};
    information.cbSize = sizeof(information);
    information.uFlags = TTF_TRACK | TTF_ABSOLUTE;
    information.hwnd = widget->window;
    information.uId = 1;
    information.lpszText = const_cast<wchar_t*>(widget->copyTooltipText.c_str());
    SendMessageW(widget->copyTooltip, TTM_ADDTOOLW, 0, reinterpret_cast<LPARAM>(&information));
    POINT cursor = {};
    GetCursorPos(&cursor);
    SendMessageW(widget->copyTooltip, TTM_TRACKPOSITION, 0, MAKELPARAM(cursor.x + 12, cursor.y + 20));
    SendMessageW(widget->copyTooltip, TTM_TRACKACTIVATE, TRUE, reinterpret_cast<LPARAM>(&information));
    widget->copyTooltipEndTick = GetTickCount64() + 1400;
}

static void CopyWidgetDate(Widget* widget, const SYSTEMTIME& date) {
    if (widget == nullptr) {
        return;
    }
    std::wstring text = FormatWidgetDate(widget->config, date, widget->config.dateCopyFormat);
    SIZE_T bytes = (text.size() + 1) * sizeof(wchar_t);
    HGLOBAL memory = GlobalAlloc(GMEM_MOVEABLE, bytes);
    if (memory == nullptr) {
        return;
    }
    void* target = GlobalLock(memory);
    if (target == nullptr) {
        GlobalFree(memory);
        return;
    }
    CopyMemory(target, text.c_str(), bytes);
    GlobalUnlock(memory);
    if (!OpenClipboard(widget->window)) {
        GlobalFree(memory);
        return;
    }
    EmptyClipboard();
    if (SetClipboardData(CF_UNICODETEXT, memory) == nullptr) {
        GlobalFree(memory);
    } else {
        ShowCopiedDateTooltip(widget, text);
    }
    CloseClipboard();
}

static SIZE GetCalendarSize(const WidgetConfig& config, bool borderless) {
    struct CalendarSizeEntry {
        AppLanguage language;
        bool weekNumbers;
        bool borderless;
        bool themesDisabled;
        int fontAntialiasing;
        int fontWeight;
        bool fontItalic;
        BYTE fontCharSet;
        std::wstring fontFace;
        SIZE size;
    };
    static std::vector<CalendarSizeEntry> cache;
    bool disabledThemes = themesDisabled || config.disableThemes;
    for (size_t index = 0; index < cache.size(); index++) {
        const CalendarSizeEntry& entry = cache[index];
        if (entry.language == config.language && entry.weekNumbers == config.weekNumbers && entry.borderless == borderless && entry.themesDisabled == disabledThemes &&
            entry.fontAntialiasing == config.fontAntialiasing && entry.fontWeight == config.fontWeight && entry.fontItalic == config.fontItalic &&
            entry.fontCharSet == config.fontCharSet && entry.fontFace == config.fontFace) {
            return entry.size;
        }
    }
    SIZE size = { config.weekNumbers ? 250 : 227, 160 };
    DWORD style = WS_POPUP | (config.weekNumbers ? MCS_WEEKNUMBERS : 0);
    CalendarLocaleScope localeScope(config.language);
    HWND calendar = CreateWindowExW(0, MONTHCAL_CLASSW, L"", style, 0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);
    if (calendar != nullptr) {
        SetWindowTheme(calendar, disabledThemes ? L"" : nullptr, disabledThemes ? L"" : nullptr);
        if (borderless) {
            MonthCal_SetCalendarBorder(calendar, TRUE, 0);
        }
        HFONT font = CreateCalendarUiFont(config);
        if (font != nullptr) {
            SendMessageW(calendar, WM_SETFONT, reinterpret_cast<WPARAM>(font), FALSE);
        }
        RECT minimum = {};
        if (MonthCal_GetMinReqRect(calendar, &minimum)) {
            size.cx = minimum.right - minimum.left;
            size.cy = minimum.bottom - minimum.top;
        }
        DestroyWindow(calendar);
        if (font != nullptr) {
            DeleteObject(font);
        }
    }
    cache.push_back({ config.language, config.weekNumbers, borderless, disabledThemes, config.fontAntialiasing, config.fontWeight, config.fontItalic, config.fontCharSet,
                      config.fontFace, size });
    return size;
}

static int GetDigitalBorderInset(int borderStyle) {
    if (borderStyle == DIGITAL_BORDER_NONE) {
        return 0;
    }
    if (borderStyle == DIGITAL_BORDER_3D) {
        return 3;
    }
    return 2;
}

static void ApplyDigitalNativeBorderStyle(int borderStyle, DWORD* style, DWORD* extendedStyle) {
    if (borderStyle == DIGITAL_BORDER_NONE) {
        return;
    }
    *style |= WS_BORDER;
    if (borderStyle == DIGITAL_BORDER_SINGLE) {
        *extendedStyle |= WS_EX_DLGMODALFRAME;
    } else if (borderStyle == DIGITAL_BORDER_3D) {
        *extendedStyle |= WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE;
    }
}

static void GetWidgetDimensions(const WidgetConfig& config, int* width, int* height) {
    if (config.type == WIDGET_FULLSCREEN) {
        RECT monitorRect = {};
        if (GetPrimarySelectedMonitorRect(config, &monitorRect)) {
            *width = monitorRect.right - monitorRect.left;
            *height = monitorRect.bottom - monitorRect.top;
        } else {
            *width = GetSystemMetrics(SM_CXSCREEN);
            *height = GetSystemMetrics(SM_CYSCREEN);
        }
        return;
    }
    SIZE calendarSize = GetCalendarSize(config, config.type == WIDGET_PANEL);
    if (config.type == WIDGET_ANALOG) {
        *width = config.size;
        *height = config.size;
    } else if (config.type == WIDGET_DIGITAL) {
        std::wstring sample;
        SYSTEMTIME displayed = {};
        GetDisplayedTime(config, &displayed);
        const wchar_t* hourSample = config.leadingZero || displayed.wHour >= 10 ? L"88" : L"8";
        if (config.showSeconds) {
            sample = std::wstring(hourSample) + L":88:88";
        } else {
            sample = std::wstring(hourSample) + L":88";
        }
        if (config.showUtc && config.showUtcText) {
            sample += L" UTC";
        }
        SIZE extent = {};
        TEXTMETRICW metrics = {};
        HDC screen = GetDC(nullptr);
        HFONT font = CreateWidgetDrawingFont(config);
        if (screen != nullptr && font != nullptr) {
            HGDIOBJ oldFont = SelectObject(screen, font);
            GetTextExtentPoint32W(screen, sample.c_str(), static_cast<int>(sample.size()), &extent);
            GetTextMetricsW(screen, &metrics);
            SelectObject(screen, oldFont);
        }
        if (font != nullptr) {
            DeleteObject(font);
        }
        if (screen != nullptr) {
            ReleaseDC(nullptr, screen);
        }
        int borderInset = config.transparentBackground ? GetDigitalBorderInset(config.borderStyle) : 0;
        int inset = config.padding + borderInset + config.borderWidth;
        *width = std::max(1, static_cast<int>(extent.cx) + inset * 2 + 4);
        *height = std::max(38, std::max(static_cast<int>(extent.cy), static_cast<int>(metrics.tmHeight)) + inset * 2 + 4);
        if (!config.transparentBackground) {
            DWORD style = WS_POPUP;
            DWORD extendedStyle = WS_EX_TOOLWINDOW;
            ApplyDigitalNativeBorderStyle(config.borderStyle, &style, &extendedStyle);
            RECT rect = { 0, 0, *width, *height };
            if (AdjustWindowRectEx(&rect, style, FALSE, extendedStyle)) {
                *width = rect.right - rect.left;
                *height = rect.bottom - rect.top;
            }
        }
    } else if (config.type == WIDGET_CALENDAR) {
        *width = calendarSize.cx;
        *height = calendarSize.cy;
    } else {
        const int clockGroupHeight = config.size + 27;
        const int contentHeight = std::max(static_cast<int>(calendarSize.cy), clockGroupHeight);
        const int zoneTop = 35 + contentHeight + 4;
        *width = 8 + calendarSize.cx + 12 + config.size + 8;
        *height = zoneTop + 28 + 7;
    }
}

static void GetPanelLayout(const WidgetConfig& config, RECT* calendarRect, POINT* clockPosition, RECT* timeRect) {
    SIZE calendarSize = GetCalendarSize(config, true);
    const int contentTop = 35;
    const int clockGroupHeight = config.size + 27;
    const int contentHeight = std::max(static_cast<int>(calendarSize.cy), clockGroupHeight);
    const int calendarTop = contentTop + (contentHeight - calendarSize.cy) / 2;
    const int clockLeft = 8 + calendarSize.cx + 12;
    const int clockTop = contentTop + (contentHeight - clockGroupHeight) / 2;
    if (calendarRect != nullptr) {
        *calendarRect = { 8, calendarTop, 8 + calendarSize.cx, calendarTop + calendarSize.cy };
    }
    if (clockPosition != nullptr) {
        *clockPosition = { clockLeft, clockTop };
    }
    if (timeRect != nullptr) {
        *timeRect = { clockLeft, clockTop + config.size + 2, clockLeft + config.size, clockTop + config.size + 27 };
    }
}

static void ClampWidgetPosition(WidgetConfig* config) {
    int width = 0;
    int height = 0;
    GetWidgetDimensions(*config, &width, &height);
    RECT desired = { config->x, config->y, config->x + width, config->y + height };
    HMONITOR monitor = MonitorFromRect(&desired, MONITOR_DEFAULTTONEAREST);
    MONITORINFO information = {};
    information.cbSize = sizeof(information);
    if (monitor == nullptr || !GetMonitorInfoW(monitor, &information)) {
        return;
    }
    int workLeft = static_cast<int>(information.rcWork.left);
    int workTop = static_cast<int>(information.rcWork.top);
    int workRight = static_cast<int>(information.rcWork.right);
    int workBottom = static_cast<int>(information.rcWork.bottom);
    config->x = width >= workRight - workLeft ? workLeft : std::clamp(config->x, workLeft, workRight - width);
    config->y = height >= workBottom - workTop ? workTop : std::clamp(config->y, workTop, workBottom - height);
}

static void ClampFormPosition(int* x, int* y, int width, int height) {
    if (*x == CW_USEDEFAULT || *y == CW_USEDEFAULT) {
        return;
    }
    RECT desired = { *x, *y, *x + width, *y + height };
    HMONITOR monitor = MonitorFromRect(&desired, MONITOR_DEFAULTTONEAREST);
    MONITORINFO information = {};
    information.cbSize = sizeof(information);
    if (monitor == nullptr || !GetMonitorInfoW(monitor, &information)) {
        return;
    }
    int workLeft = static_cast<int>(information.rcWork.left);
    int workTop = static_cast<int>(information.rcWork.top);
    int workRight = static_cast<int>(information.rcWork.right);
    int workBottom = static_cast<int>(information.rcWork.bottom);
    *x = std::clamp(*x, workLeft, std::max(workLeft, workRight - width));
    *y = std::clamp(*y, workTop, std::max(workTop, workBottom - height));
}

static void SaveFormPosition(HWND window, int* x, int* y) {
    RECT rect = {};
    if (window != nullptr && GetWindowRect(window, &rect)) {
        *x = rect.left;
        *y = rect.top;
    }
}

static BYTE FontQuality(int fontAntialiasing) {
    return fontAntialiasing == FONT_ANTIALIAS_CLEARTYPE ? CLEARTYPE_QUALITY : ANTIALIASED_QUALITY;
}

static HFONT CreateCalendarUiFont(const WidgetConfig& config) {
    NONCLIENTMETRICSW metrics = {};
    metrics.cbSize = sizeof(metrics);
    if (!SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
        return nullptr;
    }
    metrics.lfMessageFont.lfWeight = config.fontWeight;
    metrics.lfMessageFont.lfItalic = config.fontItalic;
    metrics.lfMessageFont.lfQuality = FontQuality(config.fontAntialiasing);
    if (!config.fontFace.empty()) {
        wcsncpy_s(metrics.lfMessageFont.lfFaceName, config.fontFace.c_str(), _TRUNCATE);
        metrics.lfMessageFont.lfCharSet = config.fontCharSet;
    }
    return CreateFontIndirectW(&metrics.lfMessageFont);
}

static void UpdateApplicationFontButtons() {
    if (hAppFontButton != nullptr) {
        const wchar_t* caption = settingsAppFontFace.empty() ? SYSTEM_DEFAULT_FONT_LABELS[appLanguage] : settingsAppFontFace.c_str();
        SetWindowTextW(hAppFontButton, caption);
    }
    if (hAppFontDefaultButton != nullptr) {
        EnableWindow(hAppFontDefaultButton, !settingsAppFontFace.empty() || settingsAppFontWeight != FW_NORMAL || settingsAppFontItalic || settingsAppFontDialogSize != 90);
    }
}

static void ResetUiFont() {
    if (hUiFont != nullptr) {
        DeleteObject(hUiFont);
        hUiFont = nullptr;
    }
}

static int CALLBACK FindFontCallback(const LOGFONTW*, const TEXTMETRICW*, DWORD, LPARAM parameter) {
    *reinterpret_cast<bool*>(parameter) = true;
    return 0;
}

static bool IsFontAvailable(const wchar_t* face) {
    HDC screen = GetDC(nullptr);
    if (screen == nullptr) {
        return false;
    }
    LOGFONTW font = {};
    font.lfCharSet = DEFAULT_CHARSET;
    wcsncpy_s(font.lfFaceName, face, _TRUNCATE);
    bool found = false;
    EnumFontFamiliesExW(screen, &font, FindFontCallback, reinterpret_cast<LPARAM>(&found), 0);
    ReleaseDC(nullptr, screen);
    return found;
}

static HFONT CreateAboutFont() {
    NONCLIENTMETRICSW metrics = {};
    metrics.cbSize = sizeof(metrics);
    LOGFONTW font = {};
    if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
        font = metrics.lfMessageFont;
    } else {
        font.lfHeight = -12;
        font.lfCharSet = DEFAULT_CHARSET;
    }
    font.lfWeight = FW_NORMAL;
    font.lfItalic = FALSE;
    font.lfUnderline = FALSE;
    font.lfStrikeOut = FALSE;
    font.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
    const wchar_t* face = IsFontAvailable(L"Consolas") ? L"Consolas" : L"Courier New";
    wcsncpy_s(font.lfFaceName, face, _TRUNCATE);
    HFONT result = CreateFontIndirectW(&font);
    if (result == nullptr && wcscmp(face, L"Courier New") != 0) {
        wcsncpy_s(font.lfFaceName, L"Courier New", _TRUNCATE);
        result = CreateFontIndirectW(&font);
    }
    return result;
}

static void ApplyApplicationFontPreview() {
    std::wstring savedFace = appFontFace;
    int savedWeight = appFontWeight;
    bool savedItalic = appFontItalic;
    HFONT previousFont = hUiFont;
    appFontFace = settingsAppFontFace;
    appFontWeight = settingsAppFontWeight;
    appFontItalic = settingsAppFontItalic;
    hUiFont = nullptr;
    if (hSettings != nullptr) {
        ApplyUiStyle(hSettings);
    }
    if (hHelp != nullptr) {
        ApplyUiStyle(hHelp);
    }
    if (hAbout != nullptr) {
        ApplyUiStyle(hAbout);
    }
    appFontFace = savedFace;
    appFontWeight = savedWeight;
    appFontItalic = savedItalic;
    if (hUiFont != nullptr && previousFont != nullptr) {
        DeleteObject(previousFont);
    } else if (hUiFont == nullptr) {
        hUiFont = previousFont;
    }
    settingsApplicationFontPreviewActive = true;
}

static void RestoreApplicationFontPreview() {
    if (!settingsApplicationFontPreviewActive) {
        return;
    }
    HFONT previewFont = hUiFont;
    hUiFont = nullptr;
    if (hSettings != nullptr) {
        ApplyUiStyle(hSettings);
    }
    if (hHelp != nullptr) {
        ApplyUiStyle(hHelp);
    }
    if (hAbout != nullptr) {
        ApplyUiStyle(hAbout);
    }
    if (hUiFont != nullptr && previewFont != nullptr) {
        DeleteObject(previewFont);
    } else if (hUiFont == nullptr) {
        hUiFont = previewFont;
    }
    settingsApplicationFontPreviewActive = false;
}

static BOOL CALLBACK ApplyFontAndTheme(HWND child, LPARAM) {
    HFONT font = GetParent(child) == hAbout && GetDlgCtrlID(child) == ID_INFO_TEXT && hAboutFont != nullptr ? hAboutFont : hUiFont;
    if (font != nullptr) {
        SendMessageW(child, WM_SETFONT, reinterpret_cast<WPARAM>(font), TRUE);
    }
    SetWindowTheme(child, themesDisabled ? L"" : nullptr, themesDisabled ? L"" : nullptr);
    return TRUE;
}

static void ApplyUiStyle(HWND window) {
    if (hUiFont == nullptr) {
        NONCLIENTMETRICSW metrics = {};
        metrics.cbSize = sizeof(metrics);
        if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
            metrics.lfMessageFont.lfWeight = appFontWeight;
            metrics.lfMessageFont.lfItalic = appFontItalic;
            metrics.lfMessageFont.lfQuality = FontQuality(appFontAntialiasing);
            if (!appFontFace.empty()) {
                wcsncpy_s(metrics.lfMessageFont.lfFaceName, appFontFace.c_str(), _TRUNCATE);
                metrics.lfMessageFont.lfCharSet = DEFAULT_CHARSET;
            }
            hUiFont = CreateFontIndirectW(&metrics.lfMessageFont);
        }
    }
    SetWindowTheme(window, themesDisabled ? L"" : nullptr, themesDisabled ? L"" : nullptr);
    EnumChildWindows(window, ApplyFontAndTheme, 0);
    RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
}

static void ApplyWidgetTheme(HWND window, const WidgetConfig& config) {
    if (window == nullptr) {
        return;
    }
    bool disabled = themesDisabled || config.disableThemes;
    SetWindowTheme(window, disabled ? L"" : nullptr, disabled ? L"" : nullptr);
    RedrawWindow(window, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
}

static void ApplyCalendarFont(Widget* widget) {
    if (widget == nullptr || widget->calendarChild == nullptr) {
        return;
    }
    HFONT replacement = CreateCalendarUiFont(widget->config);
    if (replacement == nullptr) {
        return;
    }
    SendMessageW(widget->calendarChild, WM_SETFONT, reinterpret_cast<WPARAM>(replacement), TRUE);
    if (widget->calendarFont != nullptr) {
        DeleteObject(widget->calendarFont);
    }
    widget->calendarFont = replacement;
    RECT minimum = {};
    if (MonthCal_GetMinReqRect(widget->calendarChild, &minimum)) {
        SetWindowPos(widget->calendarChild, nullptr, 0, 0, minimum.right - minimum.left, minimum.bottom - minimum.top,
                     SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    RedrawWindow(widget->calendarChild, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW);
}

static bool SetForegroundWindowEx(HWND window) {
    if (window == nullptr || !IsWindow(window)) {
        return false;
    }
    DWORD currentThread = GetCurrentThreadId();
    DWORD foregroundThread = GetWindowThreadProcessId(GetForegroundWindow(), nullptr);
    if (foregroundThread != 0 && foregroundThread != currentThread) {
        AttachThreadInput(currentThread, foregroundThread, TRUE);
    }
    ShowWindow(window, SW_SHOWNORMAL);
    BringWindowToTop(window);
    bool result = SetForegroundWindow(window) != FALSE;
    if (foregroundThread != 0 && foregroundThread != currentThread) {
        AttachThreadInput(currentThread, foregroundThread, FALSE);
    }
    return result;
}

const DWORD PROFILE_104[14] = { 104, 5002, 5003, 51, 51, 27, 2, 0, 37, 2, 0, 50, 1, 13 };
const DWORD PROFILE_130[14] = { 130, 5000, 5001, 63, 63, 35, 2, 0, 46, 2, 0, 64, 1, 18 };
const DWORD PROFILE_166[14] = { 166, 5008, 5009, 81, 81, 43, 2, 0, 60, 2, 0, 80, 1, 20 };
const DWORD PROFILE_198[14] = { 198, 5004, 5005, 97, 97, 53, 3, 0, 71, 3, 0, 95, 1, 24 };

static BYTE* FindModulePattern(BYTE* begin, size_t length, const BYTE* pattern, size_t patternLength) {
    if (begin == nullptr || pattern == nullptr || patternLength == 0 || length < patternLength) {
        return nullptr;
    }
    for (size_t offset = 0; offset <= length - patternLength; offset++) {
        if (memcmp(begin + offset, pattern, patternLength) == 0) {
            return begin + offset;
        }
    }
    return nullptr;
}

static bool ResolveAnalogClockInternals() {
    if (hTimeDate == nullptr) {
        return false;
    }
    BYTE* module = reinterpret_cast<BYTE*>(hTimeDate);
    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(module);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE || dosHeader->e_lfanew <= 0) {
        return false;
    }
    IMAGE_NT_HEADERS32* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS32*>(module + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE || ntHeaders->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC || ntHeaders->OptionalHeader.SizeOfImage == 0) {
        return false;
    }
    size_t imageSize = ntHeaders->OptionalHeader.SizeOfImage;
    BYTE* profile = FindModulePattern(module, imageSize, reinterpret_cast<const BYTE*>(PROFILE_198), sizeof(PROFILE_198));
    if (profile == nullptr || profile + sizeof(PROFILE_198) + sizeof(PROFILE_166) + sizeof(PROFILE_130) > module + imageSize ||
        memcmp(profile + sizeof(PROFILE_198), PROFILE_166, sizeof(PROFILE_166)) != 0 ||
        memcmp(profile + sizeof(PROFILE_198) + sizeof(PROFILE_166), PROFILE_130, sizeof(PROFILE_130)) != 0) {
        return false;
    }
    const BYTE registerPattern[] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x2C, 0x56, 0x33, 0xC0, 0xC7, 0x45, 0xE4, 0x04, 0x00, 0x00, 0x00,                                    0x68, 0x00, 0x7F, 0x00, 0x00, 0x50, 0x8B, 0xF1, 0x89, 0x45, 0xE0, 0x89, 0x45, 0xEC, 0x89, 0x45, 0xF8 };
    BYTE* registerAddress = nullptr;
    BYTE* search = module;
    size_t remaining = imageSize;
    DWORD expectedDescriptorAddress = static_cast<DWORD>(reinterpret_cast<ULONG_PTR>(profile - 0x200));
    while (remaining >= sizeof(registerPattern)) {
        BYTE* candidate = FindModulePattern(search, remaining, registerPattern, sizeof(registerPattern));
        if (candidate == nullptr) {
            break;
        }
        size_t candidateOffset = static_cast<size_t>(candidate - module);
        if (candidateOffset + 62 <= imageSize && candidate[55] == 0xC7 && candidate[56] == 0x45 && candidate[57] == 0xFC) {
            DWORD descriptorAddress = 0;
            CopyMemory(&descriptorAddress, candidate + 58, sizeof(descriptorAddress));
            if (descriptorAddress == expectedDescriptorAddress) {
                registerAddress = candidate;
                break;
            }
        }
        search = candidate + 1;
        remaining = imageSize - static_cast<size_t>(search - module);
    }
    const BYTE renderPattern[] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x40, 0x53, 0x56, 0x8B, 0xF1, 0x33, 0xC0, 0x57, 0x89, 0x75, 0xDC, 0x39, 0x46, 0x34 };
    BYTE* renderAddress = FindModulePattern(module, imageSize, renderPattern, sizeof(renderPattern));
    if (registerAddress == nullptr || renderAddress == nullptr) {
        return false;
    }
    BYTE* secondRenderAddress = FindModulePattern(renderAddress + 1, imageSize - static_cast<size_t>(renderAddress + 1 - module), renderPattern, sizeof(renderPattern));
    if (secondRenderAddress != nullptr) {
        return false;
    }
    registerClockClass = reinterpret_cast<RegisterClockClassProc>(registerAddress);
    renderClock = reinterpret_cast<RenderClockProc>(renderAddress);
    analogProfile198 = reinterpret_cast<DWORD*>(profile);
    activeAnalogProfile = nullptr;
    return true;
}

static bool IsAnalogClockClassRegistered() {
    if (hTimeDate == nullptr) {
        return false;
    }
    WNDCLASSW clockClass = {};
    return GetClassInfoW(reinterpret_cast<HINSTANCE>(hTimeDate), L"ClockWndMain", &clockClass) != FALSE;
}

static bool LoadAnalogClockClass() {
    if (sizeof(void*) != 4) {
        return false;
    }
    if (hTimeDate == nullptr) {
        wchar_t systemDirectory[MAX_PATH] = {};
        UINT length = GetSystemWow64DirectoryW(systemDirectory, ARRAYSIZE(systemDirectory));
        if (length == 0 || length >= ARRAYSIZE(systemDirectory)) {
            length = GetSystemDirectoryW(systemDirectory, ARRAYSIZE(systemDirectory));
        }
        if (length == 0 || length >= ARRAYSIZE(systemDirectory)) {
            return false;
        }
        wchar_t path[MAX_PATH] = {};
        swprintf_s(path, L"%s\\timedate.cpl", systemDirectory);
        hTimeDate = LoadLibraryW(path);
        if (hTimeDate == nullptr) {
            return false;
        }
        if (!ResolveAnalogClockInternals()) {
            FreeLibrary(hTimeDate);
            hTimeDate = nullptr;
            return false;
        }
    }
    if (IsAnalogClockClassRegistered()) {
        return true;
    }
    if (registerClockClass == nullptr && !ResolveAnalogClockInternals()) {
        return false;
    }
    if (registerClockClass == nullptr) {
        return false;
    }
    registerClockClass(reinterpret_cast<HINSTANCE>(hTimeDate));
    return IsAnalogClockClassRegistered();
}

static const DWORD* ProfileForSize(int size) {
    if (size == 104) {
        return PROFILE_104;
    }
    if (size == 166) {
        return PROFILE_166;
    }
    if (size == 198) {
        return PROFILE_198;
    }
    return PROFILE_130;
}

static bool ApplyAnalogProfile(const WidgetConfig& config) {
    if (!LoadAnalogClockClass()) {
        return false;
    }
    DWORD profile[14] = {};
    CopyMemory(profile, ProfileForSize(config.size), sizeof(profile));
    if (!config.showSeconds) {
        profile[11] = profile[12] = profile[13] = 0;
    }
    if (activeAnalogProfile == nullptr) {
        HDC screen = GetDC(nullptr);
        int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSX);
        if (screen != nullptr) {
            ReleaseDC(nullptr, screen);
        }
        activeAnalogProfile = analogProfile198 + (dpi <= 120 ? 28 : (dpi <= 144 ? 14 : 0));
    }
    DWORD oldProtect = 0;
    if (!VirtualProtect(activeAnalogProfile, sizeof(profile), PAGE_READWRITE, &oldProtect)) {
        return false;
    }
    CopyMemory(activeAnalogProfile, profile, sizeof(profile));
    DWORD ignored = 0;
    VirtualProtect(activeAnalogProfile, sizeof(profile), oldProtect, &ignored);
    return true;
}

static void UpdateAnalogTime(Widget* widget) {
    if (widget == nullptr || widget->analogChild == nullptr) {
        return;
    }
    SYSTEMTIME time = {};
    GetDisplayedTime(widget->config, &time);
    SendMessageW(widget->analogChild, WM_ANALOG_SETTIME, 0, reinterpret_cast<LPARAM>(&time));
}

static COLORREF ReadAnalogBackground(const Widget* widget) {
    if (widget == nullptr || widget->analogChild == nullptr) {
        return GetSysColor(COLOR_WINDOW);
    }
    LONG_PTR stateValue = GetWindowLongPtrW(widget->analogChild, GWLP_USERDATA);
    if (stateValue == 0) {
        return GetSysColor(COLOR_WINDOW);
    }
    BYTE* state = reinterpret_cast<BYTE*>(stateValue);
    DWORD** backgroundAddress = reinterpret_cast<DWORD**>(state + 0x20);
    if (backgroundAddress != nullptr && *backgroundAddress != nullptr) {
        return static_cast<COLORREF>(**backgroundAddress & 0x00FFFFFF);
    }
    return GetSysColor(COLOR_WINDOW);
}

static void CaptureAnalogBackground(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    COLORREF color = ReadAnalogBackground(widget);
    if (widget->analogBackground != color) {
        widget->analogBackground = color;
        InvalidateRect(widget->window, nullptr, FALSE);
    }
}

static COLORREF PanelBackgroundColor(const Widget* widget) {
    return widget != nullptr && widget->analogBackground != CLR_INVALID ? widget->analogBackground : ReadAnalogBackground(widget);
}

static bool CreateDib(HDC reference, int width, int height, HBITMAP* bitmap, DWORD** pixels) {
    BITMAPINFO information = {};
    information.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    information.bmiHeader.biWidth = width;
    information.bmiHeader.biHeight = -height;
    information.bmiHeader.biPlanes = 1;
    information.bmiHeader.biBitCount = 32;
    information.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    *bitmap = CreateDIBSection(reference, &information, DIB_RGB_COLORS, &bits, nullptr, 0);
    *pixels = static_cast<DWORD*>(bits);
    return *bitmap != nullptr && bits != nullptr;
}

static void PresentLayeredBitmap(Widget* widget, HDC sourceDC, HDC screenDC, int width, int height, BYTE opacity) {
    RECT current = {};
    GetWindowRect(widget->window, &current);
    POINT destination = { widget->rendered ? current.left : widget->config.x, widget->rendered ? current.top : widget->config.y };
    POINT source = { 0, 0 };
    SIZE size = { width, height };
    BLENDFUNCTION blend = { AC_SRC_OVER, 0, opacity, AC_SRC_ALPHA };
    if (UpdateLayeredWindow(widget->window, screenDC, &destination, &size, sourceDC, &source, 0, &blend, ULW_ALPHA)) {
        widget->rendered = true;
    }
}

static bool RenderAnalogBackground(Widget* widget, HDC reference, DWORD background, HBITMAP* bitmap, DWORD** pixels) {
    if (renderClock == nullptr) {
        return false;
    }
    LONG_PTR stateValue = GetWindowLongPtrW(widget->analogChild, GWLP_USERDATA);
    if (stateValue == 0 || !CreateDib(reference, widget->config.size, widget->config.size, bitmap, pixels)) {
        return false;
    }
    BYTE* state = reinterpret_cast<BYTE*>(stateValue);
    DWORD** backgroundAddress = reinterpret_cast<DWORD**>(state + 0x20);
    if (*backgroundAddress == nullptr) {
        DeleteObject(*bitmap);
        *bitmap = nullptr;
        return false;
    }
    DWORD oldBackground = **backgroundAddress;
    HDC memory = CreateCompatibleDC(reference);
    HGDIOBJ oldBitmap = SelectObject(memory, *bitmap);
    **backgroundAddress = background;
    UpdateAnalogTime(widget);
    renderClock(state, nullptr, memory);
    **backgroundAddress = oldBackground;
    SelectObject(memory, oldBitmap);
    DeleteDC(memory);
    return true;
}

static void RenderAnalogWidget(Widget* widget) {
    int size = widget->config.size;
    HDC screen = GetDC(nullptr);
    if (screen == nullptr) {
        return;
    }
    HBITMAP whiteBitmap = nullptr;
    HBITMAP blackBitmap = nullptr;
    DWORD* whitePixels = nullptr;
    DWORD* blackPixels = nullptr;
    if (!RenderAnalogBackground(widget, screen, 0xFFFFFFFF, &whiteBitmap, &whitePixels) || !RenderAnalogBackground(widget, screen, 0xFF000000, &blackBitmap, &blackPixels)) {
        if (whiteBitmap != nullptr) {
            DeleteObject(whiteBitmap);
        }
        if (blackBitmap != nullptr) {
            DeleteObject(blackBitmap);
        }
        ReleaseDC(nullptr, screen);
        return;
    }
    HBITMAP outputBitmap = nullptr;
    DWORD* output = nullptr;
    HDC outputDC = CreateCompatibleDC(screen);
    if (!CreateDib(screen, size, size, &outputBitmap, &output)) {
        DeleteObject(whiteBitmap);
        DeleteObject(blackBitmap);
        DeleteDC(outputDC);
        ReleaseDC(nullptr, screen);
        return;
    }
    for (int index = 0; index < size * size; index++) {
        DWORD white = whitePixels[index];
        DWORD black = blackPixels[index];
        int wb = static_cast<BYTE>(white);
        int wg = static_cast<BYTE>(white >> 8);
        int wr = static_cast<BYTE>(white >> 16);
        int bb = static_cast<BYTE>(black);
        int bg = static_cast<BYTE>(black >> 8);
        int br = static_cast<BYTE>(black >> 16);
        int alpha = 255 - std::clamp(((wr - br) + (wg - bg) + (wb - bb)) / 3, 0, 255);
        if (alpha < 2) {
            output[index] = 0;
            continue;
        }
        if (alpha > 253) {
            alpha = 255;
        }
        int red = std::min(br, alpha);
        int green = std::min(bg, alpha);
        int blue = std::min(bb, alpha);
        if (widget->identifyActive && widget->identifyPhase) {
            const int tintStrength = 150;
            int tintRed = 80 * alpha / 255;
            int tintGreen = 190 * alpha / 255;
            int tintBlue = alpha;
            red = (red * (255 - tintStrength) + tintRed * tintStrength) / 255;
            green = (green * (255 - tintStrength) + tintGreen * tintStrength) / 255;
            blue = (blue * (255 - tintStrength) + tintBlue * tintStrength) / 255;
        } else if (widget->alarmActive && widget->flashPhase) {
            red = alpha;
            green /= 3;
            blue /= 3;
        }
        output[index] = (static_cast<DWORD>(alpha) << 24) | (red << 16) | (green << 8) | blue;
    }
    HGDIOBJ oldOutput = SelectObject(outputDC, outputBitmap);
    PresentLayeredBitmap(widget, outputDC, screen, size, size, static_cast<BYTE>(widget->config.opacity * 255 / 100));
    SelectObject(outputDC, oldOutput);
    DeleteObject(outputBitmap);
    DeleteDC(outputDC);
    DeleteObject(whiteBitmap);
    DeleteObject(blackBitmap);
    ReleaseDC(nullptr, screen);
}

static HFONT CreateDrawingFont(int points, int weight, int fontAntialiasing, const wchar_t* fontFace = L"Arial", bool italic = false) {
    HDC screen = GetDC(nullptr);
    int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSY);
    if (screen != nullptr) {
        ReleaseDC(nullptr, screen);
    }
    return CreateFontW(-MulDiv(points, dpi, 72), 0, 0, 0, weight, italic, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                       FontQuality(fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, fontFace);
}

static HFONT CreatePanelFont(const FontSelection& selection, int fontAntialiasing) {
    HDC screen = GetDC(nullptr);
    int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSY);
    if (screen != nullptr) {
        ReleaseDC(nullptr, screen);
    }
    int height = -MulDiv(std::clamp(selection.dialogSize, 10, 9990), dpi, 720);
    return CreateFontW(height, 0, 0, 0, selection.weight, selection.italic, selection.underline, selection.strikeOut, selection.charSet, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                       FontQuality(fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, selection.face.c_str());
}

static HFONT CreateWidgetDrawingFont(const WidgetConfig& config) {
    HDC screen = GetDC(nullptr);
    int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSY);
    if (screen != nullptr) {
        ReleaseDC(nullptr, screen);
    }
    return CreateFontW(-MulDiv(config.fontSize, dpi, 72), 0, 0, 0, config.fontWeight, config.fontItalic, config.fontUnderline, config.fontStrikeOut, config.fontCharSet,
                       OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, FontQuality(config.fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, config.fontFace.c_str());
}

static HFONT CreateFullscreenDrawingFont(const WidgetConfig& config, const RECT& client, HDC dc, const wchar_t* text) {
    int width = client.right - client.left;
    int height = client.bottom - client.top;
    int pixelHeight = std::max(24, height * std::clamp(config.fontSize, 5, 85) / 100);
    HFONT font = CreateFontW(-pixelHeight, 0, 0, 0, config.fontWeight, config.fontItalic, config.fontUnderline, config.fontStrikeOut, config.fontCharSet, OUT_DEFAULT_PRECIS,
                             CLIP_DEFAULT_PRECIS, FontQuality(config.fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, config.fontFace.c_str());
    if (font == nullptr || dc == nullptr || text == nullptr || text[0] == L'\0') {
        return font;
    }
    HGDIOBJ oldFont = SelectObject(dc, font);
    SIZE textSize = {};
    BOOL measured = GetTextExtentPoint32W(dc, text, static_cast<int>(wcslen(text)), &textSize);
    SelectObject(dc, oldFont);
    if (measured && textSize.cx > width && textSize.cx > 0) {
        int fittedHeight = std::max(1, MulDiv(pixelHeight, width, textSize.cx));
        DeleteObject(font);
        font = CreateFontW(-fittedHeight, 0, 0, 0, config.fontWeight, config.fontItalic, config.fontUnderline, config.fontStrikeOut, config.fontCharSet, OUT_DEFAULT_PRECIS,
                           CLIP_DEFAULT_PRECIS, FontQuality(config.fontAntialiasing), DEFAULT_PITCH | FF_DONTCARE, config.fontFace.c_str());
    }
    return font;
}

static void DrawCenteredText(HDC dc, const std::wstring& text, RECT rect, HFONT font, COLORREF color, UINT format = DT_CENTER | DT_VCENTER | DT_SINGLELINE,
                             COLORREF backgroundColor = CLR_INVALID) {
    HGDIOBJ oldFont = SelectObject(dc, font);
    SetTextColor(dc, color);
    if (backgroundColor == CLR_INVALID) {
        SetBkMode(dc, TRANSPARENT);
    } else {
        SetBkColor(dc, backgroundColor);
        SetBkMode(dc, OPAQUE);
    }
    DrawTextW(dc, text.c_str(), -1, &rect, format);
    SelectObject(dc, oldFont);
}

static bool DrawFullscreenText(HDC dc, const wchar_t* text, const RECT& rect, const WidgetConfig& config, COLORREF color, COLORREF backgroundColor) {
    if (d2dFactory == nullptr || dwriteFactory == nullptr || dc == nullptr || text == nullptr || text[0] == L'\0') {
        return false;
    }
    int width = std::max(1L, rect.right - rect.left);
    int height = std::max(1L, rect.bottom - rect.top);
    D2D1_RENDER_TARGET_PROPERTIES properties = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), 96.0f, 96.0f, D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE);
    ID2D1DCRenderTarget* target = nullptr;
    HRESULT result = d2dFactory->CreateDCRenderTarget(&properties, &target);
    if (FAILED(result) || target == nullptr) {
        return false;
    }
    result = target->BindDC(dc, &rect);
    if (FAILED(result)) {
        target->Release();
        return false;
    }
    float fontSize = std::max(24.0f, static_cast<float>(height) * static_cast<float>(std::clamp(config.fontSize, 5, 85)) / 100.0f);
    DWRITE_FONT_WEIGHT weight = static_cast<DWRITE_FONT_WEIGHT>(std::clamp(config.fontWeight, 1, 999));
    DWRITE_FONT_STYLE style = config.fontItalic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL;
    IDWriteTextFormat* format = nullptr;
    result = dwriteFactory->CreateTextFormat(config.fontFace.empty() ? L"Arial" : config.fontFace.c_str(), nullptr, weight, style, DWRITE_FONT_STRETCH_NORMAL, fontSize,
                                             LANGUAGE_LOCALES[config.language], &format);
    if (FAILED(result) || format == nullptr) {
        target->Release();
        return false;
    }
    format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    UINT32 length = static_cast<UINT32>(wcslen(text));
    IDWriteTextLayout* layout = nullptr;
    result = dwriteFactory->CreateTextLayout(text, length, format, static_cast<float>(width), static_cast<float>(height), &layout);
    if (FAILED(result) || layout == nullptr) {
        format->Release();
        target->Release();
        return false;
    }
    DWRITE_TEXT_METRICS metrics = {};
    if (SUCCEEDED(layout->GetMetrics(&metrics)) && metrics.widthIncludingTrailingWhitespace > static_cast<float>(width) && metrics.widthIncludingTrailingWhitespace > 0.0f) {
        fontSize = std::max(1.0f, fontSize * static_cast<float>(width) / metrics.widthIncludingTrailingWhitespace);
        layout->Release();
        format->Release();
        layout = nullptr;
        format = nullptr;
        result = dwriteFactory->CreateTextFormat(config.fontFace.empty() ? L"Arial" : config.fontFace.c_str(), nullptr, weight, style, DWRITE_FONT_STRETCH_NORMAL, fontSize,
                                                 LANGUAGE_LOCALES[config.language], &format);
        if (SUCCEEDED(result) && format != nullptr) {
            format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
            format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
            format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
            result = dwriteFactory->CreateTextLayout(text, length, format, static_cast<float>(width), static_cast<float>(height), &layout);
        }
    }
    if (FAILED(result) || format == nullptr || layout == nullptr) {
        if (layout != nullptr) {
            layout->Release();
        }
        if (format != nullptr) {
            format->Release();
        }
        target->Release();
        return false;
    }
    DWRITE_TEXT_RANGE range = { 0, length };
    layout->SetUnderline(config.fontUnderline, range);
    layout->SetStrikethrough(config.fontStrikeOut, range);
    ID2D1SolidColorBrush* brush = nullptr;
    result = target->CreateSolidColorBrush(D2D1::ColorF(GetRValue(color) / 255.0f, GetGValue(color) / 255.0f, GetBValue(color) / 255.0f), &brush);
    if (SUCCEEDED(result) && brush != nullptr) {
        target->SetTextAntialiasMode(config.fontAntialiasing == FONT_ANTIALIAS_CLEARTYPE ? D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE : D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        target->BeginDraw();
        target->Clear(D2D1::ColorF(GetRValue(backgroundColor) / 255.0f, GetGValue(backgroundColor) / 255.0f, GetBValue(backgroundColor) / 255.0f));
        target->DrawTextLayout(D2D1::Point2F(0.0f, 0.0f), layout, brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
        result = target->EndDraw();
    }
    if (brush != nullptr) {
        brush->Release();
    }
    layout->Release();
    format->Release();
    target->Release();
    return SUCCEEDED(result);
}

static void DrawDigitalBorder(HDC dc, int width, int height, int borderStyle, COLORREF color) {
    RECT borderRect = { 0, 0, width, height };
    if (borderStyle == DIGITAL_BORDER_TOOL_WINDOW) {
        DrawEdge(dc, &borderRect, EDGE_RAISED, BF_RECT);
    } else if (borderStyle == DIGITAL_BORDER_SINGLE) {
        HPEN pen = CreatePen(PS_SOLID, 1, color);
        HGDIOBJ oldPen = SelectObject(dc, pen);
        HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
        Rectangle(dc, 0, 0, width, height);
        SelectObject(dc, oldBrush);
        SelectObject(dc, oldPen);
        DeleteObject(pen);
    } else if (borderStyle == DIGITAL_BORDER_3D) {
        DrawEdge(dc, &borderRect, EDGE_SUNKEN, BF_RECT);
    }
}

static void DrawDigitalWidthBorder(HDC dc, int width, int height, int inset, int borderWidth, COLORREF color) {
    if (borderWidth <= 0) {
        return;
    }
    HPEN pen = CreatePen(PS_SOLID, 1, color);
    HGDIOBJ oldPen = SelectObject(dc, pen);
    HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
    for (int border = 0; border < borderWidth; border++) {
        int edge = inset + border;
        Rectangle(dc, edge, edge, width - edge, height - edge);
    }
    SelectObject(dc, oldBrush);
    SelectObject(dc, oldPen);
    DeleteObject(pen);
}

static void GetDigitalTimeText(const WidgetConfig& config, wchar_t* text, size_t textCount) {
    SYSTEMTIME time = {};
    GetDisplayedTime(config, &time);
    if (config.showSeconds) {
        swprintf_s(text, textCount, config.leadingZero ? L"%02d:%02d:%02d" : L"%d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
    } else {
        swprintf_s(text, textCount, config.leadingZero ? L"%02d:%02d" : L"%d:%02d", time.wHour, time.wMinute);
    }
    if (config.showUtc && config.showUtcText) {
        wcscat_s(text, textCount, L" UTC");
    }
}

static int GetDigitalTextInset(const Widget* widget, const RECT& client) {
    if (widget->config.type != WIDGET_FULLSCREEN) {
        return widget->config.padding + widget->config.borderWidth;
    }
    int clientWidth = static_cast<int>(client.right - client.left);
    int clientHeight = static_cast<int>(client.bottom - client.top);
    int inset = widget->config.padding;
    if (widget->fullscreenPreview) {
        RECT monitorRect = {};
        if (GetPrimarySelectedMonitorRect(widget->config, &monitorRect)) {
            int monitorWidth = static_cast<int>(monitorRect.right - monitorRect.left);
            int monitorHeight = static_cast<int>(monitorRect.bottom - monitorRect.top);
            int clientSize = std::max(1, std::min(clientWidth, clientHeight));
            int monitorSize = std::max(1, std::min(monitorWidth, monitorHeight));
            inset = MulDiv(inset, clientSize, monitorSize);
        }
    }
    int maximumInset = std::max(0, (std::min(clientWidth, clientHeight) - 2) / 2);
    return std::clamp(inset, 0, maximumInset);
}

static void PaintOpaqueDigitalWidget(Widget* widget, HWND window, HDC dc) {
    RECT client = {};
    GetClientRect(window, &client);
    bool alarmFlash = widget->alarmActive && widget->flashPhase;
    COLORREF textColor = alarmFlash ? widget->config.alarmTextColor : widget->config.textColor;
    COLORREF backgroundColor = alarmFlash ? widget->config.alarmBackgroundColor : widget->config.backgroundColor;
    HBRUSH background = CreateSolidBrush(backgroundColor);
    FillRect(dc, &client, background);
    DeleteObject(background);
    wchar_t text[32] = {};
    GetDigitalTimeText(widget->config, text, _countof(text));
    RECT textRect = client;
    int textInset = GetDigitalTextInset(widget, client);
    InflateRect(&textRect, -textInset, -textInset);
    bool fullscreenDrawn = widget->config.type == WIDGET_FULLSCREEN && DrawFullscreenText(dc, text, textRect, widget->config, textColor, backgroundColor);
    if (!fullscreenDrawn) {
        HFONT font = widget->config.type == WIDGET_FULLSCREEN ? CreateFullscreenDrawingFont(widget->config, textRect, dc, text) : CreateWidgetDrawingFont(widget->config);
        DrawCenteredText(dc, text, textRect, font, textColor, DT_CENTER | DT_VCENTER | DT_SINGLELINE, backgroundColor);
        DeleteObject(font);
    }
    if (widget->config.type != WIDGET_FULLSCREEN) {
        DrawDigitalWidthBorder(dc, client.right, client.bottom, 0, widget->config.borderWidth, textColor);
    }
    if (widget->identifyActive && widget->identifyPhase) {
        HPEN pen = CreatePen(PS_SOLID, 3, IDENTIFY_COLOR);
        HGDIOBJ oldPen = SelectObject(dc, pen);
        HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
        Rectangle(dc, 1, 1, client.right - 1, client.bottom - 1);
        SelectObject(dc, oldBrush);
        SelectObject(dc, oldPen);
        DeleteObject(pen);
    }
}

static void RenderCustomWidget(Widget* widget) {
    int width = 0;
    int height = 0;
    GetWidgetDimensions(widget->config, &width, &height);
    HDC screen = GetDC(nullptr);
    if (screen == nullptr) {
        return;
    }
    HBITMAP bitmap = nullptr;
    DWORD* pixels = nullptr;
    HDC dc = CreateCompatibleDC(screen);
    if (!CreateDib(screen, width, height, &bitmap, &pixels) || dc == nullptr) {
        if (bitmap) {
            DeleteObject(bitmap);
        }
        if (dc) {
            DeleteDC(dc);
        }
        ReleaseDC(nullptr, screen);
        return;
    }
    HGDIOBJ oldBitmap = SelectObject(dc, bitmap);
    bool transparentDigital = widget->config.type == WIDGET_DIGITAL && widget->config.transparentBackground;
    bool alarmFlash = widget->alarmActive && widget->flashPhase;
    COLORREF textColor = alarmFlash ? widget->config.alarmTextColor : widget->config.textColor;
    COLORREF backgroundColor = alarmFlash ? widget->config.alarmBackgroundColor : widget->config.backgroundColor;
    HBRUSH background = CreateSolidBrush(transparentDigital ? RGB(255, 255, 255) : backgroundColor);
    RECT full = { 0, 0, width, height };
    FillRect(dc, &full, background);
    DeleteObject(background);
    wchar_t text[32] = {};
    GetDigitalTimeText(widget->config, text, _countof(text));
    int borderStyleInset = GetDigitalBorderInset(widget->config.borderStyle);
    int inset = widget->config.padding + borderStyleInset + widget->config.borderWidth;
    RECT textRect = { inset, inset, width - inset, height - inset };
    HFONT font = CreateWidgetDrawingFont(widget->config);
    DrawCenteredText(dc, text, textRect, font, transparentDigital ? RGB(0, 0, 0) : textColor);
    DeleteObject(font);
    DrawDigitalBorder(dc, width, height, widget->config.borderStyle, transparentDigital ? RGB(0, 0, 0) : textColor);
    DrawDigitalWidthBorder(dc, width, height, borderStyleInset, widget->config.borderWidth, transparentDigital ? RGB(0, 0, 0) : textColor);
    if (widget->identifyActive && widget->identifyPhase) {
        HPEN pen = CreatePen(PS_SOLID, 3, IDENTIFY_COLOR);
        HGDIOBJ oldPen = SelectObject(dc, pen);
        HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
        Rectangle(dc, 1, 1, width - 1, height - 1);
        SelectObject(dc, oldBrush);
        SelectObject(dc, oldPen);
        DeleteObject(pen);
    }
    SelectObject(dc, oldBitmap);
    BYTE opacity = static_cast<BYTE>(widget->config.opacity * 255 / 100);
    if (transparentDigital) {
        COLORREF color = widget->identifyActive && widget->identifyPhase ? IDENTIFY_COLOR : textColor;
        int minimumHitTestAlpha = (255 + opacity - 1) / std::max(1, static_cast<int>(opacity));
        for (int index = 0; index < width * height; index++) {
            DWORD pixel = pixels[index];
            int coverage = 255 - (static_cast<BYTE>(pixel) + static_cast<BYTE>(pixel >> 8) + static_cast<BYTE>(pixel >> 16)) / 3;
            int alpha = std::max(minimumHitTestAlpha, coverage);
            int red = GetRValue(color) * alpha / 255;
            int green = GetGValue(color) * alpha / 255;
            int blue = GetBValue(color) * alpha / 255;
            pixels[index] = (static_cast<DWORD>(alpha) << 24) | (red << 16) | (green << 8) | blue;
        }
    } else {
        for (int index = 0; index < width * height; index++) {
            pixels[index] |= 0xFF000000;
        }
    }
    oldBitmap = SelectObject(dc, bitmap);
    PresentLayeredBitmap(widget, dc, screen, width, height, opacity);
    SelectObject(dc, oldBitmap);
    DeleteObject(bitmap);
    DeleteDC(dc);
    ReleaseDC(nullptr, screen);
}

static void PaintPanelWidget(Widget* widget, HDC dc) {
    if (widget == nullptr) {
        return;
    }
    int width = 0;
    int height = 0;
    GetWidgetDimensions(widget->config, &width, &height);
    RECT full = { 0, 0, width, height };
    HBRUSH background = CreateSolidBrush(PanelBackgroundColor(widget));
    FillRect(dc, &full, background);
    DeleteObject(background);
    SYSTEMTIME time = {};
    GetDisplayedTime(widget->config, &time);
    HFONT topFont = CreatePanelFont(widget->config.panelTopFont, widget->config.fontAntialiasing);
    HFONT timeFont = CreatePanelFont(widget->config.panelTimeFont, widget->config.fontAntialiasing);
    HFONT bottomFont = CreatePanelFont(widget->config.panelBottomFont, widget->config.fontAntialiasing);
    wchar_t dateText[128] = {};
    GetDateFormatEx(LANGUAGE_LOCALES[widget->config.language], DATE_LONGDATE, &time, nullptr, dateText, ARRAYSIZE(dateText), nullptr);
    RECT dateRect = { 8, 7, width - 8, 34 };
    DrawCenteredText(dc, dateText, dateRect, topFont, RGB(0, 83, 184));
    RECT calendarRect = {};
    RECT timeRect = {};
    GetPanelLayout(widget->config, &calendarRect, nullptr, &timeRect);
    wchar_t clockText[32] = {};
    if (widget->config.showSeconds) {
        swprintf_s(clockText, L"%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
    } else {
        swprintf_s(clockText, L"%02d:%02d", time.wHour, time.wMinute);
    }
    DrawCenteredText(dc, clockText, timeRect, timeFont, RGB(0, 0, 0));
    std::wstring zoneName = widget->config.showUtc ? L"UTC" : widget->config.timeZoneKey;
    for (size_t index = 0; index < timeZones.size(); index++) {
        if (_wcsicmp(timeZones[index].TimeZoneKeyName, widget->config.timeZoneKey.c_str()) == 0) {
            zoneName = timeZones[index].StandardName;
            break;
        }
    }
    std::wstring zoneText = WT(widget, TXT_TIMEZONE);
    zoneText += L" ";
    zoneText += zoneName;
    if (widget->config.offsetMilliseconds != 0) {
        zoneText += L"  (" + FormatOffset(widget->config.offsetMilliseconds) + L")";
    }
    int zoneTop = std::max(calendarRect.bottom, timeRect.bottom) + 4;
    RECT zoneRect = { 8, zoneTop, width - 8, zoneTop + 28 };
    DrawCenteredText(dc, zoneText, zoneRect, bottomFont, RGB(0, 83, 184), DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
    DeleteObject(topFont);
    DeleteObject(timeFont);
    DeleteObject(bottomFont);
    bool identifyFrame = widget->identifyActive && widget->identifyPhase;
    bool alarmFrame = widget->alarmActive && widget->flashPhase;
    if (identifyFrame || alarmFrame) {
        HPEN pen = CreatePen(PS_SOLID, 3, identifyFrame ? IDENTIFY_COLOR : RGB(220, 0, 0));
        HGDIOBJ oldPen = SelectObject(dc, pen);
        HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
        Rectangle(dc, 1, 1, width - 1, height - 1);
        SelectObject(dc, oldBrush);
        SelectObject(dc, oldPen);
        DeleteObject(pen);
    }
}

static void PaintWidgetBuffered(Widget* widget, HWND window, HDC target, bool panel) {
    if (widget == nullptr || target == nullptr) {
        return;
    }
    RECT client = {};
    GetClientRect(window, &client);
    int width = client.right - client.left;
    int height = client.bottom - client.top;
    if (width <= 0 || height <= 0) {
        return;
    }
    HDC buffer = CreateCompatibleDC(target);
    HBITMAP bitmap = CreateCompatibleBitmap(target, width, height);
    if (buffer == nullptr || bitmap == nullptr) {
        if (bitmap != nullptr) {
            DeleteObject(bitmap);
        }
        if (buffer != nullptr) {
            DeleteDC(buffer);
        }
        if (panel) {
            PaintPanelWidget(widget, target);
        } else {
            PaintOpaqueDigitalWidget(widget, window, target);
        }
        return;
    }
    HGDIOBJ oldBitmap = SelectObject(buffer, bitmap);
    if (panel) {
        PaintPanelWidget(widget, buffer);
    } else {
        PaintOpaqueDigitalWidget(widget, window, buffer);
    }
    BitBlt(target, 0, 0, width, height, buffer, 0, 0, SRCCOPY);
    SelectObject(buffer, oldBitmap);
    DeleteObject(bitmap);
    DeleteDC(buffer);
}

static void RenderWidget(Widget* widget) {
    if (widget == nullptr || !widget->config.visible || widget->window == nullptr) {
        return;
    }
    if (widget->config.type == WIDGET_ANALOG) {
        if (widget->analogChild != nullptr) {
            RenderAnalogWidget(widget);
        }
        return;
    }
    if (widget->config.type == WIDGET_PANEL) {
        UpdateAnalogTime(widget);
        SYSTEMTIME displayed = {};
        GetDisplayedTime(widget->config, &displayed);
        int dateKey = displayed.wYear * 10000 + displayed.wMonth * 100 + displayed.wDay;
        if (!widget->rendered || widget->lastPanelDateKey != dateKey || widget->alarmActive) {
            widget->lastPanelDateKey = dateKey;
            InvalidateRect(widget->window, nullptr, FALSE);
        } else {
            RECT timeRect = {};
            GetPanelLayout(widget->config, nullptr, nullptr, &timeRect);
            InvalidateRect(widget->window, &timeRect, FALSE);
        }
        widget->rendered = true;
        return;
    }
    if (widget->config.type == WIDGET_CALENDAR) {
        widget->rendered = true;
        return;
    }
    if (widget->config.type == WIDGET_FULLSCREEN) {
        InvalidateRect(widget->window, nullptr, FALSE);
        UpdateWindow(widget->window);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            InvalidateRect(widget->fullscreenWindows[index], nullptr, FALSE);
            UpdateWindow(widget->fullscreenWindows[index]);
        }
        widget->rendered = true;
        return;
    }
    if (widget->config.transparentBackground) {
        RenderCustomWidget(widget);
    } else {
        int desiredWidth = 0;
        int desiredHeight = 0;
        GetWidgetDimensions(widget->config, &desiredWidth, &desiredHeight);
        RECT current = {};
        if (GetWindowRect(widget->window, &current) && (current.right - current.left != desiredWidth || current.bottom - current.top != desiredHeight)) {
            SetWindowPos(widget->window, nullptr, 0, 0, desiredWidth, desiredHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
        InvalidateRect(widget->window, nullptr, FALSE);
        UpdateWindow(widget->window);
        widget->rendered = true;
    }
}

static void RenderWidgetIdentification(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    if (widget->config.type == WIDGET_ANALOG) {
        RenderAnalogWidget(widget);
    } else if (widget->config.type == WIDGET_DIGITAL) {
        RenderCustomWidget(widget);
    } else if (widget->config.type == WIDGET_FULLSCREEN) {
        InvalidateRect(widget->window, nullptr, FALSE);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            InvalidateRect(widget->fullscreenWindows[index], nullptr, FALSE);
        }
    } else if (widget->config.type == WIDGET_PANEL) {
        InvalidateRect(widget->window, nullptr, FALSE);
    } else if (widget->config.type == WIDGET_CALENDAR && widget->calendarChild != nullptr) {
        InvalidateRect(widget->calendarChild, nullptr, TRUE);
    }
}

static void ApplyWidgetZOrder(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    bool topMost = widget->config.topMost || widget->config.type == WIDGET_FULLSCREEN;
    if (topMost) {
        SetWindowPos(widget->window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    } else {
        SetWindowPos(widget->window, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        SetWindowPos(widget->window, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        SetWindowPos(widget->fullscreenWindows[index], topMost ? HWND_TOPMOST : HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

static void BringWidgetForward(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    HWND insertAfter = widget->config.topMost || widget->config.type == WIDGET_FULLSCREEN ? HWND_TOPMOST : HWND_TOP;
    SetWindowPos(widget->window, insertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        SetWindowPos(widget->fullscreenWindows[index], insertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

static void IdentifyWidget(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    if (!widget->identifyActive) {
        widget->identifyRestoreHidden = !widget->config.visible;
        widget->identifyRestoreNotTopmost = !widget->config.topMost;
        if (widget->identifyRestoreHidden) {
            widget->config.visible = true;
            ShowWindow(widget->window, SW_SHOWNOACTIVATE);
            for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
                ShowWindow(widget->fullscreenWindows[index], SW_SHOWNOACTIVATE);
            }
        }
    }
    widget->identifyActive = true;
    widget->identifyPhase = true;
    widget->identifyEndTick = GetTickCount64() + 1600;
    SetWindowPos(widget->window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
        SetWindowPos(widget->fullscreenWindows[index], HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    RenderWidgetIdentification(widget);
}

static void FinishWidgetIdentification(Widget* widget) {
    if (widget == nullptr || !widget->identifyActive) {
        return;
    }
    widget->identifyActive = false;
    widget->identifyPhase = false;
    RenderWidgetIdentification(widget);
    if (widget->identifyRestoreHidden) {
        widget->config.visible = false;
        ShowWindow(widget->window, SW_HIDE);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            ShowWindow(widget->fullscreenWindows[index], SW_HIDE);
        }
    }
    if (widget->identifyRestoreNotTopmost) {
        ApplyWidgetZOrder(widget);
    }
    widget->identifyRestoreHidden = false;
    widget->identifyRestoreNotTopmost = false;
}

static void CloseWidgetAudio(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    widget->audioGeneration++;
    if (widget->audioStopEvent != nullptr) {
        SetEvent(widget->audioStopEvent);
        CloseHandle(widget->audioStopEvent);
        widget->audioStopEvent = nullptr;
    }
}

static void StopWidgetAlarm(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    CloseWidgetAudio(widget);
    widget->alarmActive = false;
    widget->flashPhase = false;
    RenderWidget(widget);
    if (widget->config.type == WIDGET_PANEL && widget->window != nullptr) {
        InvalidateRect(widget->window, nullptr, FALSE);
    }
}

static void StopAllAlarms() {
    for (size_t index = 0; index < widgets.size(); index++) {
        StopWidgetAlarm(widgets[index].get());
    }
}

static bool LooksLikeAudio(const std::wstring& path) {
    size_t dot = path.find_last_of(L'.');
    if (dot == std::wstring::npos) {
        return false;
    }
    std::wstring extension = path.substr(dot);
    std::transform(extension.begin(), extension.end(), extension.begin(), towlower);
    return extension == L".wav" || extension == L".mp3" || extension == L".wma" || extension == L".mid" || extension == L".midi" || extension == L".aac" || extension == L".m4a";
}

static bool IsRemoteScriptUrlValid(const std::wstring& url) {
    if (url.empty()) {
        return false;
    }
    URL_COMPONENTSW components = {};
    components.dwStructSize = sizeof(components);
    components.dwHostNameLength = static_cast<DWORD>(-1);
    components.dwUrlPathLength = static_cast<DWORD>(-1);
    components.dwExtraInfoLength = static_cast<DWORD>(-1);
    if (!WinHttpCrackUrl(url.c_str(), 0, 0, &components)) {
        return false;
    }
    return (components.nScheme == INTERNET_SCHEME_HTTP || components.nScheme == INTERNET_SCHEME_HTTPS) && components.lpszHostName != nullptr && components.dwHostNameLength != 0;
}

static DWORD WINAPI AudioThreadProc(void* parameter) {
    std::unique_ptr<AudioThreadParameters> parameters(static_cast<AudioThreadParameters*>(parameter));
    std::wstring alias = L"calClockAudio" + std::to_wstring(GetCurrentThreadId()) + L"_" + std::to_wstring(parameters->generation);
    std::wstring command = L"open \"" + parameters->path + L"\" alias " + alias;
    bool opened = mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
    if (opened && WaitForSingleObject(parameters->stopEvent, 0) != WAIT_OBJECT_0) {
        command = L"play " + alias + (parameters->loop ? L" repeat" : L"");
        if (mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0) {
            while (WaitForSingleObject(parameters->stopEvent, 100) == WAIT_TIMEOUT) {
                if (!parameters->loop) {
                    wchar_t mode[32] = {};
                    command = L"status " + alias + L" mode";
                    if (mciSendStringW(command.c_str(), mode, ARRAYSIZE(mode), nullptr) != 0 || (_wcsicmp(mode, L"playing") != 0 && _wcsicmp(mode, L"seeking") != 0)) {
                        break;
                    }
                }
            }
        }
        command = L"stop " + alias;
        mciSendStringW(command.c_str(), nullptr, 0, nullptr);
    }
    if (opened) {
        command = L"close " + alias;
        mciSendStringW(command.c_str(), nullptr, 0, nullptr);
    }
    CloseHandle(parameters->stopEvent);
    PostMessageW(parameters->notifyWindow, parameters->notifyMessage, static_cast<WPARAM>(parameters->widgetId), static_cast<LPARAM>(parameters->generation));
    return 0;
}

static bool StartAudioPlaybackAsync(const std::wstring& path, bool loop, HWND notifyWindow, UINT notifyMessage, int widgetId, ULONG generation, HANDLE* stopEvent) {
    if (stopEvent == nullptr) {
        return false;
    }
    HANDLE ownerEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (ownerEvent == nullptr) {
        return false;
    }
    HANDLE workerEvent = nullptr;
    if (!DuplicateHandle(GetCurrentProcess(), ownerEvent, GetCurrentProcess(), &workerEvent, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
        CloseHandle(ownerEvent);
        return false;
    }
    std::unique_ptr<AudioThreadParameters> parameters(new AudioThreadParameters());
    parameters->path = path;
    parameters->loop = loop;
    parameters->stopEvent = workerEvent;
    parameters->notifyWindow = notifyWindow;
    parameters->notifyMessage = notifyMessage;
    parameters->widgetId = widgetId;
    parameters->generation = generation;
    HANDLE thread = CreateThread(nullptr, 0, AudioThreadProc, parameters.get(), 0, nullptr);
    if (thread == nullptr) {
        CloseHandle(workerEvent);
        CloseHandle(ownerEvent);
        return false;
    }
    parameters.release();
    CloseHandle(thread);
    *stopEvent = ownerEvent;
    return true;
}

static DWORD WINAPI LocalCommandThreadProc(void* parameter) {
    std::unique_ptr<LocalCommandThreadParameters> parameters(static_cast<LocalCommandThreadParameters*>(parameter));
    ShellExecuteW(nullptr, L"open", parameters->command.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    return 0;
}

static void StartLocalCommandAsync(const std::wstring& command) {
    std::unique_ptr<LocalCommandThreadParameters> parameters(new LocalCommandThreadParameters());
    parameters->command = command;
    HANDLE thread = CreateThread(nullptr, 0, LocalCommandThreadProc, parameters.get(), 0, nullptr);
    if (thread != nullptr) {
        parameters.release();
        CloseHandle(thread);
    }
}

static DWORD WINAPI RemoteScriptThreadProc(void* parameter) {
    std::unique_ptr<RemoteScriptThreadParameters> parameters(static_cast<RemoteScriptThreadParameters*>(parameter));
    URL_COMPONENTSW components = {};
    components.dwStructSize = sizeof(components);
    components.dwHostNameLength = static_cast<DWORD>(-1);
    components.dwUrlPathLength = static_cast<DWORD>(-1);
    components.dwExtraInfoLength = static_cast<DWORD>(-1);
    if (!WinHttpCrackUrl(parameters->url.c_str(), 0, 0, &components)) {
        return 0;
    }
    if (components.lpszHostName == nullptr || components.dwHostNameLength == 0) {
        return 0;
    }
    std::wstring host(components.lpszHostName, components.dwHostNameLength);
    std::wstring path;
    if (components.lpszUrlPath != nullptr && components.dwUrlPathLength != 0) {
        path.assign(components.lpszUrlPath, components.dwUrlPathLength);
    }
    if (components.lpszExtraInfo != nullptr && components.dwExtraInfoLength != 0) {
        path.append(components.lpszExtraInfo, components.dwExtraInfoLength);
    }
    if (path.empty()) {
        path = L"/";
    }
    HINTERNET session = WinHttpOpen(L"CalClock/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (session == nullptr) {
        return 0;
    }
    WinHttpSetTimeouts(session, 5000, 5000, 5000, 5000);
    HINTERNET connection = WinHttpConnect(session, host.c_str(), components.nPort, 0);
    DWORD flags = components.nScheme == INTERNET_SCHEME_HTTPS ? WINHTTP_FLAG_SECURE : 0;
    HINTERNET request = connection == nullptr ? nullptr : WinHttpOpenRequest(connection, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, flags);
    if (request != nullptr && WinHttpSendRequest(request, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
        WinHttpReceiveResponse(request, nullptr);
    }
    if (request != nullptr) {
        WinHttpCloseHandle(request);
    }
    if (connection != nullptr) {
        WinHttpCloseHandle(connection);
    }
    WinHttpCloseHandle(session);
    return 0;
}

static void StartRemoteScriptAsync(const std::wstring& url) {
    if (!IsRemoteScriptUrlValid(url)) {
        return;
    }
    std::unique_ptr<RemoteScriptThreadParameters> parameters(new RemoteScriptThreadParameters());
    parameters->url = url;
    HANDLE thread = CreateThread(nullptr, 0, RemoteScriptThreadProc, parameters.get(), 0, nullptr);
    if (thread != nullptr) {
        parameters.release();
        CloseHandle(thread);
    }
}

static void StartWidgetAlarm(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    CloseWidgetAudio(widget);
    widget->alarmActive = true;
    widget->flashPhase = true;
    if (widget->config.runCommand && !widget->config.command.empty()) {
        if (LooksLikeAudio(widget->config.command)) {
            StartAudioPlaybackAsync(widget->config.command, widget->config.loopAudio, hController, WM_AUDIO_FINISHED, widget->config.id, widget->audioGeneration,
                                    &widget->audioStopEvent);
        } else {
            StartLocalCommandAsync(widget->config.command);
        }
    }
    if (widget->config.callRemoteScript) {
        StartRemoteScriptAsync(widget->config.remoteScriptUrl);
    }
    RenderWidget(widget);
}

static void CheckWidgetAlarm(Widget* widget) {
    if (widget == nullptr || !widget->config.alarmEnabled || widget->config.type == WIDGET_CALENDAR) {
        return;
    }
    SYSTEMTIME time = {};
    GetDisplayedTime(widget->config, &time);
    int date = time.wYear * 10000 + time.wMonth * 100 + time.wDay;
    int minute = time.wHour * 60 + time.wMinute;
    if (time.wHour == widget->config.alarmHour && time.wMinute == widget->config.alarmMinute && (widget->lastAlarmDate != date || widget->lastAlarmMinute != minute)) {
        widget->lastAlarmDate = date;
        widget->lastAlarmMinute = minute;
        StartWidgetAlarm(widget);
    }
}

static void SaveWidgetPosition(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr || widget->config.type == WIDGET_FULLSCREEN) {
        return;
    }
    RECT rect = {};
    if (GetWindowRect(widget->window, &rect)) {
        widget->config.x = rect.left;
        widget->config.y = rect.top;
        SynchronizeOpenSettings(widget);
        SaveAllSettings();
    }
}

static void SaveSettingsWithoutAppearancePreviews() {
    std::vector<std::pair<Widget*, WidgetConfig>> previewConfigurations;
    for (size_t idIndex = 0; idIndex < settingsAppearancePreviewIds.size(); idIndex++) {
        Widget* previewWidget = FindWidgetById(settingsAppearancePreviewIds[idIndex]);
        if (previewWidget == nullptr) {
            continue;
        }
        for (size_t originalIndex = 0; originalIndex < settingsAppearanceOriginals.size(); originalIndex++) {
            if (settingsAppearanceOriginals[originalIndex].id == previewWidget->config.id) {
                previewConfigurations.push_back(std::make_pair(previewWidget, previewWidget->config));
                previewWidget->config = settingsAppearanceOriginals[originalIndex];
                break;
            }
        }
    }
    SaveAllSettings();
    for (size_t index = 0; index < previewConfigurations.size(); index++) {
        previewConfigurations[index].first->config = previewConfigurations[index].second;
    }
}

static void SaveFullscreenPreviewPosition(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr || !widget->fullscreenPreview) {
        return;
    }
    RECT rect = {};
    if (!GetWindowRect(widget->window, &rect)) {
        return;
    }
    widget->config.previewX = rect.left;
    widget->config.previewY = rect.top;
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        if (settingsDraft[index].id == widget->config.id) {
            settingsDraft[index].previewX = rect.left;
            settingsDraft[index].previewY = rect.top;
            break;
        }
    }
    for (size_t index = 0; index < settingsAppearanceOriginals.size(); index++) {
        if (settingsAppearanceOriginals[index].id == widget->config.id) {
            settingsAppearanceOriginals[index].previewX = rect.left;
            settingsAppearanceOriginals[index].previewY = rect.top;
            break;
        }
    }
    SaveSettingsWithoutAppearancePreviews();
}

static void CreateAnalogChild(Widget* widget) {
    if (widget == nullptr || !ApplyAnalogProfile(widget->config)) {
        return;
    }
    int childX = -widget->config.size - 2;
    int childY = 0;
    if (widget->config.type == WIDGET_PANEL) {
        POINT clockPosition = {};
        GetPanelLayout(widget->config, nullptr, &clockPosition, nullptr);
        childX = clockPosition.x;
        childY = clockPosition.y;
    }
    widget->analogChild = CreateWindowExW(0, L"ClockWndMain", L"", WS_CHILD | WS_VISIBLE | 0x10, childX, childY, widget->config.size, widget->config.size, widget->window, reinterpret_cast<HMENU>(113), reinterpret_cast<HINSTANCE>(hTimeDate), nullptr);
    if (widget->analogChild != nullptr) {
        ApplyWidgetTheme(widget->analogChild, widget->config);
        widget->analogProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(widget->analogChild, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(AnalogChildProc)));
        UpdateAnalogTime(widget);
        if (widget->config.type == WIDGET_PANEL) {
            CaptureAnalogBackground(widget);
        }
    }
}

static bool ReplaceAnalogChild(Widget* widget) {
    if (widget == nullptr || widget->window == nullptr || widget->analogChild == nullptr || !ApplyAnalogProfile(widget->config)) {
        return false;
    }
    int childX = -widget->config.size - 2;
    int childY = 0;
    if (widget->config.type == WIDGET_PANEL) {
        POINT clockPosition = {};
        GetPanelLayout(widget->config, nullptr, &clockPosition, nullptr);
        childX = clockPosition.x;
        childY = clockPosition.y;
    }
    HWND replacement = CreateWindowExW(0, L"ClockWndMain", L"", WS_CHILD | 0x10, childX, childY, widget->config.size, widget->config.size, widget->window,
                                       reinterpret_cast<HMENU>(113), reinterpret_cast<HINSTANCE>(hTimeDate), nullptr);
    if (replacement == nullptr) {
        return false;
    }
    ApplyWidgetTheme(replacement, widget->config);
    WNDPROC replacementProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(replacement, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(AnalogChildProc)));
    if (replacementProc == nullptr) {
        DestroyWindow(replacement);
        return false;
    }
    HWND previousChild = widget->analogChild;
    WNDPROC previousProc = widget->analogProc;
    widget->analogChild = replacement;
    widget->analogProc = replacementProc;
    widget->analogBackground = CLR_INVALID;
    UpdateAnalogTime(widget);
    if (widget->config.type == WIDGET_PANEL) {
        CaptureAnalogBackground(widget);
    }
    SetWindowPos(replacement, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    RedrawWindow(replacement, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
    if (previousProc != nullptr) {
        SetWindowLongPtrW(previousChild, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(previousProc));
    }
    DestroyWindow(previousChild);
    if (widget->config.type == WIDGET_ANALOG) {
        RenderAnalogWidget(widget);
    }
    return true;
}

static void CreateCalendarChild(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    bool borderless = widget->config.type == WIDGET_PANEL;
    SIZE calendarSize = GetCalendarSize(widget->config, borderless);
    int childX = 0;
    int childY = 0;
    if (widget->config.type == WIDGET_PANEL) {
        RECT calendarRect = {};
        GetPanelLayout(widget->config, &calendarRect, nullptr, nullptr);
        childX = calendarRect.left;
        childY = calendarRect.top;
    }
    DWORD style = WS_CHILD | (widget->config.weekNumbers ? MCS_WEEKNUMBERS : 0);
    CalendarLocaleScope localeScope(widget->config.language);
    widget->calendarChild = CreateWindowExW(0, MONTHCAL_CLASSW, L"", style, 0, 0, 0, 0, widget->window, reinterpret_cast<HMENU>(114), hInstance, nullptr);
    if (widget->calendarChild != nullptr) {
        ApplyWidgetTheme(widget->calendarChild, widget->config);
    }
    if (widget->calendarChild != nullptr) {
        ApplyCalendarFont(widget);
        if (borderless) {
            MonthCal_SetCalendarBorder(widget->calendarChild, TRUE, 0);
        }
        SYSTEMTIME displayed = {};
        GetDisplayedTime(widget->config, &displayed);
        MonthCal_SetCurSel(widget->calendarChild, &displayed);
        MonthCal_SetFirstDayOfWeek(widget->calendarChild, widget->config.sundayFirst ? 6 : 0);
        RECT minimum = {};
        if (MonthCal_GetMinReqRect(widget->calendarChild, &minimum)) {
            calendarSize.cx = minimum.right - minimum.left;
            calendarSize.cy = minimum.bottom - minimum.top;
        }
        SetWindowPos(widget->calendarChild, nullptr, childX, childY, calendarSize.cx, calendarSize.cy, SWP_NOZORDER | SWP_NOACTIVATE);
        widget->calendarProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(widget->calendarChild, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(CalendarChildProc)));
        ShowWindow(widget->calendarChild, SW_SHOWNOACTIVATE);
        RedrawWindow(widget->calendarChild, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW);
    }
}

static void CreateWidgetWindow(Widget* widget) {
    if (widget == nullptr) {
        return;
    }
    bool fullscreen = widget->config.type == WIDGET_FULLSCREEN;
    std::vector<const DisplayMonitor*> selectedMonitors;
    if (fullscreen) {
        selectedMonitors = SelectedDisplayMonitors(widget->config);
        if (!selectedMonitors.empty()) {
            widget->config.x = selectedMonitors[0]->rect.left;
            widget->config.y = selectedMonitors[0]->rect.top;
        }
    } else {
        ClampWidgetPosition(&widget->config);
    }
    int width = 0;
    int height = 0;
    GetWidgetDimensions(widget->config, &width, &height);
    DWORD extended = WS_EX_TOOLWINDOW | ((widget->config.topMost || fullscreen) ? WS_EX_TOPMOST : 0);
    bool parentedControl = widget->config.type == WIDGET_PANEL || widget->config.type == WIDGET_CALENDAR;
    if (!fullscreen && (!parentedControl || widget->config.opacity < 100)) {
        extended |= WS_EX_LAYERED;
    }
    DWORD style = WS_POPUP | (parentedControl ? WS_CLIPCHILDREN : 0);
    if (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground) {
        ApplyDigitalNativeBorderStyle(widget->config.borderStyle, &style, &extended);
    }
    widget->window = CreateWindowExW(extended, CLASS_NAME, widget->config.name.c_str(), style, widget->config.x, widget->config.y, width, height, nullptr, nullptr, hInstance, widget);
    ApplyWidgetTheme(widget->window, widget->config);
    widget->fullscreenWindows.clear();
    widget->fullscreenPreview = false;
    if (fullscreen) {
        for (size_t index = 1; index < selectedMonitors.size(); index++) {
            const RECT& rect = selectedMonitors[index]->rect;
            HWND additional = CreateWindowExW(extended, CLASS_NAME, widget->config.name.c_str(), WS_POPUP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, widget);
            if (additional != nullptr) {
                ApplyWidgetTheme(additional, widget->config);
                widget->fullscreenWindows.push_back(additional);
            }
        }
    }
    widget->analogChild = nullptr;
    widget->analogProc = nullptr;
    widget->calendarChild = nullptr;
    widget->calendarProc = nullptr;
    widget->calendarFont = nullptr;
    widget->dragging = false;
    widget->rendered = false;
    widget->alarmActive = false;
    widget->flashPhase = false;
    widget->lastAlarmDate = -1;
    widget->lastAlarmMinute = -1;
    widget->lastRenderKey = -1;
    widget->lastPanelDateKey = -1;
    widget->analogBackground = CLR_INVALID;
    widget->alarmStoppedTick = 0;
    widget->identifyActive = false;
    widget->identifyPhase = false;
    widget->identifyRestoreHidden = false;
    widget->identifyRestoreNotTopmost = false;
    widget->identifyEndTick = 0;
    widget->copyTooltip = nullptr;
    widget->copyTooltipEndTick = 0;
    widget->lastAnalogClickTick = 0;
    widget->lastAnalogClickPoint = {};
    if (widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL) {
        CreateAnalogChild(widget);
    }
    if (widget->config.type == WIDGET_CALENDAR || widget->config.type == WIDGET_PANEL) {
        CreateCalendarChild(widget);
    }
    if (parentedControl && widget->config.opacity < 100) {
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100), LWA_ALPHA);
    } else if (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground) {
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100), LWA_ALPHA);
    }
    if (widget->config.visible) {
        RenderWidget(widget);
        ShowWindow(widget->window, SW_SHOWNOACTIVATE);
        RedrawWindow(widget->window, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            ShowWindow(widget->fullscreenWindows[index], SW_SHOWNOACTIVATE);
            RedrawWindow(widget->fullscreenWindows[index], nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
        }
        ApplyWidgetZOrder(widget);
    }
}

static void DestroyWidgetWindows() {
    for (size_t index = 0; index < blackoutWindows.size(); index++) {
        if (IsWindow(blackoutWindows[index])) {
            DestroyWindow(blackoutWindows[index]);
        }
    }
    blackoutWindows.clear();
    StopAllAlarms();
    for (size_t index = 0; index < widgets.size(); index++) {
        if (widgets[index]->copyTooltip != nullptr && IsWindow(widgets[index]->copyTooltip)) {
            DestroyWindow(widgets[index]->copyTooltip);
        }
        widgets[index]->copyTooltip = nullptr;
        if (widgets[index]->window != nullptr && IsWindow(widgets[index]->window)) {
            DestroyWindow(widgets[index]->window);
        }
        if (widgets[index]->calendarFont != nullptr) {
            DeleteObject(widgets[index]->calendarFont);
            widgets[index]->calendarFont = nullptr;
        }
        for (size_t windowIndex = 0; windowIndex < widgets[index]->fullscreenWindows.size(); windowIndex++) {
            if (IsWindow(widgets[index]->fullscreenWindows[windowIndex])) {
                DestroyWindow(widgets[index]->fullscreenWindows[windowIndex]);
            }
        }
        widgets[index]->fullscreenWindows.clear();
        widgets[index]->window = nullptr;
        widgets[index]->analogChild = nullptr;
        widgets[index]->analogProc = nullptr;
        widgets[index]->calendarChild = nullptr;
        widgets[index]->calendarProc = nullptr;
    }
}

static LRESULT CALLBACK BlackoutWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_ERASEBKGND) {
        RECT rect = {};
        GetClientRect(window, &rect);
        FillRect(reinterpret_cast<HDC>(wParam), &rect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
        return 1;
    }
    if (message == WM_PAINT) {
        PAINTSTRUCT paint = {};
        HDC dc = BeginPaint(window, &paint);
        FillRect(dc, &paint.rcPaint, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
        EndPaint(window, &paint);
        return 0;
    }
    if (message == WM_SETCURSOR) {
        SetCursor(nullptr);
        return TRUE;
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

static void RefreshFullscreenPresentation() {
    for (size_t index = 0; index < blackoutWindows.size(); index++) {
        if (IsWindow(blackoutWindows[index])) {
            DestroyWindow(blackoutWindows[index]);
        }
    }
    blackoutWindows.clear();
    RefreshDisplayMonitors();
    bool blackoutRequested = false;
    HWND escapeTarget = nullptr;
    std::vector<std::wstring> occupiedDevices;
    for (size_t widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++) {
        Widget* widget = widgets[widgetIndex].get();
        if (widget->config.type != WIDGET_FULLSCREEN || !widget->config.visible || widget->fullscreenPreview || widget->window == nullptr) {
            continue;
        }
        for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
            ShowWindow(widget->fullscreenWindows[windowIndex], SW_HIDE);
        }
        blackoutRequested = blackoutRequested || widget->config.blackoutOtherMonitors;
        if (escapeTarget == nullptr) {
            escapeTarget = widget->window;
        }
        std::vector<const DisplayMonitor*> selected = SelectedDisplayMonitors(widget->config);
        for (size_t monitorIndex = 0; monitorIndex < selected.size(); monitorIndex++) {
            occupiedDevices.push_back(selected[monitorIndex]->device);
            HWND target = monitorIndex == 0 ? widget->window : (monitorIndex - 1 < widget->fullscreenWindows.size() ? widget->fullscreenWindows[monitorIndex - 1] : nullptr);
            if (target != nullptr) {
                const RECT& rect = selected[monitorIndex]->rect;
                SetWindowPos(target, HWND_TOPMOST, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOACTIVATE | SWP_SHOWWINDOW);
            }
        }
    }
    if (blackoutRequested) {
        for (size_t monitorIndex = 0; monitorIndex < displayMonitors.size(); monitorIndex++) {
            bool occupied = std::any_of(occupiedDevices.begin(), occupiedDevices.end(), [&](const std::wstring& device) { return _wcsicmp(device.c_str(), displayMonitors[monitorIndex].device.c_str()) == 0; });
            if (occupied) {
                continue;
            }
            const RECT& rect = displayMonitors[monitorIndex].rect;
            HWND blackout = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE, BLACKOUT_CLASS_NAME, L"", WS_POPUP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);
            if (blackout != nullptr) {
                ShowWindow(blackout, SW_SHOWNOACTIVATE);
                SetWindowPos(blackout, HWND_TOPMOST, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOACTIVATE | SWP_SHOWWINDOW);
                blackoutWindows.push_back(blackout);
            }
        }
    }
    for (size_t widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++) {
        Widget* widget = widgets[widgetIndex].get();
        if (widget->config.type == WIDGET_FULLSCREEN && widget->config.visible && !widget->fullscreenPreview) {
            BringWidgetForward(widget);
        }
    }
    if (hSettings != nullptr && IsWindow(hSettings)) {
        SetWindowPos(hSettings, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    } else if (escapeTarget != nullptr) {
        SetForegroundWindowEx(escapeTarget);
        SetFocus(escapeTarget);
    }
}

static void RecreateAllWidgetWindows() {
    DestroyWidgetWindows();
    for (size_t index = 0; index < widgets.size(); index++) {
        CreateWidgetWindow(widgets[index].get());
    }
    RefreshFullscreenPresentation();
}

static Widget* FindWidgetById(int id) {
    for (size_t index = 0; index < widgets.size(); index++) {
        if (widgets[index]->config.id == id) {
            return widgets[index].get();
        }
    }
    return nullptr;
}

static void SetWidgetVisible(Widget* widget, bool visible) {
    if (widget == nullptr) {
        return;
    }
    widget->config.visible = visible;
    if (visible) {
        ShowWindow(widget->window, SW_SHOWNOACTIVATE);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            ShowWindow(widget->fullscreenWindows[index], SW_SHOWNOACTIVATE);
        }
        RenderWidget(widget);
        ApplyWidgetZOrder(widget);
    } else {
        SaveWidgetPosition(widget);
        ShowWindow(widget->window, SW_HIDE);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            ShowWindow(widget->fullscreenWindows[index], SW_HIDE);
        }
    }
    RefreshFullscreenPresentation();
    SynchronizeOpenSettings(widget);
    SaveAllSettings();
}

static void SetAllVisible(bool visible) {
    for (size_t index = 0; index < widgets.size(); index++) {
        widgets[index]->config.visible = visible;
        if (visible) {
            ShowWindow(widgets[index]->window, SW_SHOWNOACTIVATE);
            for (size_t windowIndex = 0; windowIndex < widgets[index]->fullscreenWindows.size(); windowIndex++) {
                ShowWindow(widgets[index]->fullscreenWindows[windowIndex], SW_SHOWNOACTIVATE);
            }
            RenderWidget(widgets[index].get());
            BringWidgetForward(widgets[index].get());
        } else {
            SaveWidgetPosition(widgets[index].get());
            ShowWindow(widgets[index]->window, SW_HIDE);
            for (size_t windowIndex = 0; windowIndex < widgets[index]->fullscreenWindows.size(); windowIndex++) {
                ShowWindow(widgets[index]->fullscreenWindows[windowIndex], SW_HIDE);
            }
        }
        SynchronizeOpenSettings(widgets[index].get());
    }
    RefreshFullscreenPresentation();
    SaveAllSettings();
}

static void ArrangeVisibleWidgets(Widget* anchor) {
    if (anchor != nullptr && (anchor->window == nullptr || !anchor->config.visible || anchor->config.type == WIDGET_FULLSCREEN)) {
        return;
    }
    struct MonitorGroup {
        HMONITOR monitor;
        std::vector<Widget*> items;
    };
    std::vector<MonitorGroup> groups;
    HMONITOR anchorMonitor = anchor == nullptr ? nullptr : MonitorFromWindow(anchor->window, MONITOR_DEFAULTTONEAREST);
    for (size_t index = 0; index < widgets.size(); index++) {
        Widget* current = widgets[index].get();
        if (!current->config.visible || current->window == nullptr || current->config.type == WIDGET_FULLSCREEN) {
            continue;
        }
        HMONITOR monitor = MonitorFromWindow(current->window, MONITOR_DEFAULTTONEAREST);
        if (anchorMonitor != nullptr && monitor != anchorMonitor) {
            continue;
        }
        size_t groupIndex = 0;
        while (groupIndex < groups.size() && groups[groupIndex].monitor != monitor) {
            groupIndex++;
        }
        if (groupIndex == groups.size()) {
            groups.push_back({ monitor, {} });
        }
        groups[groupIndex].items.push_back(current);
    }
    if (groups.empty()) {
        return;
    }
    struct PendingPlacement {
        Widget* widget;
        RECT rect;
    };
    std::vector<PendingPlacement> pending;
    const int gridStep = 16;
    const int preferredGap = 10;
    bool failed = false;
    for (size_t groupIndex = 0; groupIndex < groups.size() && !failed; groupIndex++) {
        MONITORINFO monitorInformation = {};
        monitorInformation.cbSize = sizeof(monitorInformation);
        if (!GetMonitorInfoW(groups[groupIndex].monitor, &monitorInformation)) {
            failed = true;
            break;
        }
        RECT work = monitorInformation.rcWork;
        std::sort(groups[groupIndex].items.begin(), groups[groupIndex].items.end(), [](Widget* left, Widget* right) { return left->config.id < right->config.id; });
        std::vector<RECT> placedOnMonitor;
        for (size_t itemIndex = 0; itemIndex < groups[groupIndex].items.size(); itemIndex++) {
            Widget* current = groups[groupIndex].items[itemIndex];
            RECT original = {};
            GetWindowRect(current->window, &original);
            int width = original.right - original.left;
            int height = original.bottom - original.top;
            int originalCenterX = (original.left + original.right) / 2;
            int originalCenterY = (original.top + original.bottom) / 2;
            int minimumCenterX = static_cast<int>(work.left) + width / 2;
            int maximumCenterX = static_cast<int>(work.right) - width + width / 2;
            int minimumCenterY = static_cast<int>(work.top) + height / 2;
            int maximumCenterY = static_cast<int>(work.bottom) - height + height / 2;
            auto alignUp = [gridStep](int value, int origin) {
                int delta = value - origin;
                if (delta <= 0) {
                    return origin;
                }
                return origin + ((delta + gridStep - 1) / gridStep) * gridStep;
                };
            int firstCenterX = alignUp(minimumCenterX, static_cast<int>(work.left));
            int firstCenterY = alignUp(minimumCenterY, static_cast<int>(work.top));
            RECT bestRect = {};
            LONGLONG bestDistance = LLONG_MAX;
            bool found = false;
            for (int pass = 0; pass < 2 && !found; pass++) {
                int gap = pass == 0 ? preferredGap : 0;
                for (int centerY = firstCenterY; centerY <= maximumCenterY; centerY += gridStep) {
                    for (int centerX = firstCenterX; centerX <= maximumCenterX; centerX += gridStep) {
                        RECT candidate = { centerX - width / 2, centerY - height / 2, centerX - width / 2 + width, centerY - height / 2 + height };
                        bool overlaps = false;
                        for (size_t placedIndex = 0; placedIndex < placedOnMonitor.size(); placedIndex++) {
                            const RECT& placed = placedOnMonitor[placedIndex];
                            bool separated = candidate.right + gap <= placed.left || candidate.left >= placed.right + gap || candidate.bottom + gap <= placed.top ||
                                candidate.top >= placed.bottom + gap;
                            if (!separated) {
                                overlaps = true;
                                break;
                            }
                        }
                        if (overlaps) {
                            continue;
                        }
                        LONGLONG deltaX = static_cast<LONGLONG>(centerX) - originalCenterX;
                        LONGLONG deltaY = static_cast<LONGLONG>(centerY) - originalCenterY;
                        LONGLONG distance = deltaX * deltaX + deltaY * deltaY;
                        if (!found || distance < bestDistance ||
                            (distance == bestDistance && (candidate.top < bestRect.top || (candidate.top == bestRect.top && candidate.left < bestRect.left)))) {
                            bestRect = candidate;
                            bestDistance = distance;
                            found = true;
                        }
                    }
                }
            }
            if (!found) {
                failed = true;
                break;
            }
            placedOnMonitor.push_back(bestRect);
            pending.push_back({ current, bestRect });
        }
    }
    if (failed) {
        return;
    }
    for (size_t index = 0; index < pending.size(); index++) {
        Widget* current = pending[index].widget;
        current->config.x = pending[index].rect.left;
        current->config.y = pending[index].rect.top;
        SetWindowPos(current->window, nullptr, current->config.x, current->config.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    SaveAllSettings();
}

static void ToggleAllFromTray() {
    ULONGLONG tick = GetTickCount64();
    if (lastTrayToggleTick != 0 && tick - lastTrayToggleTick < 500) {
        return;
    }
    lastTrayToggleTick = tick;
    bool anyVisible = false;
    for (size_t index = 0; index < widgets.size(); index++) {
        anyVisible = anyVisible || widgets[index]->config.visible;
    }
    SetAllVisible(!anyVisible);
}

static void AddTrayIcon() {
    trayIcon = {};
    trayIcon.cbSize = sizeof(trayIcon);
    trayIcon.hWnd = hController;
    trayIcon.uID = 1;
    trayIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    trayIcon.uCallbackMessage = WM_TRAYICON;
    trayIcon.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_CLOCK));
    wcscpy_s(trayIcon.szTip, T(TXT_APP));
    Shell_NotifyIconW(NIM_ADD, &trayIcon);
    trayIcon.uVersion = NOTIFYICON_VERSION;
    Shell_NotifyIconW(NIM_SETVERSION, &trayIcon);
}

static void RemoveTrayIcon() {
    if (trayIcon.cbSize != 0) {
        Shell_NotifyIconW(NIM_DELETE, &trayIcon);
    }
    trayIcon = {};
}

static void UpdateTrayIcon() {
    if (trayIcon.cbSize == 0) {
        return;
    }
    trayIcon.uFlags = NIF_TIP;
    wcscpy_s(trayIcon.szTip, T(TXT_APP));
    Shell_NotifyIconW(NIM_MODIFY, &trayIcon);
}

static void HandleWidgetMenuCommand(Widget* widget, int command) {
    if (widget == nullptr) {
        return;
    }
    bool recreate = false;
    if (command == ID_MENU_VISIBLE) {
        SetWidgetVisible(widget, !widget->config.visible);
    } else if (command == ID_MENU_TOPMOST) {
        widget->config.topMost = !widget->config.topMost;
        ApplyWidgetZOrder(widget);
        SynchronizeOpenSettings(widget);
        SaveAllSettings();
    } else if (command == ID_MENU_SECONDS) {
        bool previousShowSeconds = widget->config.showSeconds;
        widget->config.showSeconds = !widget->config.showSeconds;
        if ((widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL) && !ReplaceAnalogChild(widget)) {
            widget->config.showSeconds = previousShowSeconds;
            return;
        }
        if (widget->config.type == WIDGET_DIGITAL) {
            int width = 0;
            int height = 0;
            GetWidgetDimensions(widget->config, &width, &height);
            SetWindowPos(widget->window, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    } else if (command == ID_MENU_STOP_ALARM) {
        StopWidgetAlarm(widget);
    } else if (command >= ID_MENU_SIZE_104 && command <= ID_MENU_SIZE_198) {
        const int sizes[] = { 104, 130, 166, 198 };
        const int fonts[] = { 28, 44, 58, 72 };
        int sizeIndex = command - ID_MENU_SIZE_104;
        widget->config.size = sizes[sizeIndex];
        if (widget->config.type == WIDGET_DIGITAL) {
            widget->config.fontSize = fonts[sizeIndex];
        }
        recreate = true;
    } else if (command >= ID_MENU_DATE_FORMAT_BASE && command < ID_MENU_DATE_FORMAT_BASE + DATE_FORMAT_COUNT) {
        widget->config.dateCopyFormat = command - ID_MENU_DATE_FORMAT_BASE;
        SynchronizeOpenSettings(widget);
        SaveAllSettings();
    } else if (command == ID_MENU_ARRANGE_WIDGETS) {
        ArrangeVisibleWidgets(widget);
    } else if (command == ID_MENU_SETTINGS) {
        ShowSettingsWindow(widget->config.id);
    }
    if (recreate) {
        if (widget->alarmActive || widget->audioStopEvent != nullptr) {
            StopWidgetAlarm(widget);
        }
        if (widget->window != nullptr) {
            DestroyWindow(widget->window);
        }
        for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
            DestroyWindow(widget->fullscreenWindows[windowIndex]);
        }
        widget->fullscreenWindows.clear();
        widget->window = nullptr;
        widget->analogChild = nullptr;
        CreateWidgetWindow(widget);
        RefreshFullscreenPresentation();
        SynchronizeOpenSettings(widget);
        SaveAllSettings();
    } else if (command == ID_MENU_SECONDS) {
        RenderWidget(widget);
        SynchronizeOpenSettings(widget);
        SaveAllSettings();
    }
}

static void ShowWidgetContextMenu(Widget* widget, HWND owner) {
    HMENU menu = CreatePopupMenu();
    std::vector<wchar_t> menuMnemonics;
    AppendMenuCommand(menu, MF_STRING, ID_MENU_VISIBLE, widget->config.visible ? HIDE_WIDGET_LABELS[widget->config.language] : SHOW_WIDGET_LABELS[widget->config.language],
                      &menuMnemonics);
    if (widget->config.type != WIDGET_FULLSCREEN) {
        AppendMenuCommand(menu, MF_STRING | (widget->config.topMost ? MF_CHECKED : 0), ID_MENU_TOPMOST, WT(widget, TXT_TOPMOST), &menuMnemonics);
    }
    if (widget->config.type != WIDGET_CALENDAR) {
        AppendMenuCommand(menu, MF_STRING | (widget->config.showSeconds ? MF_CHECKED : 0), ID_MENU_SECONDS, WT(widget, TXT_SECONDS), &menuMnemonics);
    }
    if (widget->config.type == WIDGET_ANALOG || widget->config.type == WIDGET_PANEL) {
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        const int sizes[] = { 104, 130, 166, 198 };
        for (int index = 0; index < 4; index++) {
            std::wstring label = WT(widget, TXT_SIZE);
            label += L" ";
            label += std::to_wstring(sizes[index]);
            AppendMenuCommand(menu, MF_STRING | (widget->config.size == sizes[index] ? MF_CHECKED : 0), ID_MENU_SIZE_104 + index, label.c_str(), &menuMnemonics);
        }
    }
    if (widget->config.type == WIDGET_CALENDAR || widget->config.type == WIDGET_PANEL) {
        HMENU dateMenu = CreatePopupMenu();
        std::vector<wchar_t> dateMenuMnemonics;
        SYSTEMTIME selectedDate = {};
        if (widget->calendarChild == nullptr || !MonthCal_GetCurSel(widget->calendarChild, &selectedDate)) {
            GetDisplayedTime(widget->config, &selectedDate);
        }
        for (int index = 0; index < DATE_FORMAT_COUNT; index++) {
            std::wstring label = DateFormatCaption(widget->config, selectedDate, index);
            AppendMenuCommand(dateMenu, MF_STRING | (widget->config.dateCopyFormat == index ? MF_CHECKED : 0), ID_MENU_DATE_FORMAT_BASE + index, label.c_str(),
                              &dateMenuMnemonics);
        }
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuCommand(menu, MF_POPUP, reinterpret_cast<UINT_PTR>(dateMenu), DATE_COPY_LABELS[widget->config.language], &menuMnemonics);
    }
    if (widget->alarmActive) {
        AppendMenuCommand(menu, MF_STRING, ID_MENU_STOP_ALARM, WT(widget, TXT_STOP_ALARM), &menuMnemonics);
    }
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_ARRANGE_WIDGETS, ARRANGE_WIDGET_LABELS[widget->config.language], &menuMnemonics);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_SETTINGS, WT(widget, TXT_SETTINGS), &menuMnemonics, true);
    POINT point = {};
    GetCursorPos(&point);
    SetForegroundWindow(owner);
    int command = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, owner, nullptr);
    DestroyMenu(menu);
    if (command != 0) {
        HandleWidgetMenuCommand(widget, command);
    }
}

static void ShowTrayContextMenu() {
    HMENU menu = CreatePopupMenu();
    std::vector<wchar_t> menuMnemonics;
    for (size_t index = 0; index < widgets.size(); index++) {
        std::wstring label = std::to_wstring(index + 1) + L". " + widgets[index]->config.name;
        AppendMenuW(menu, MF_STRING | (widgets[index]->config.visible ? MF_CHECKED : 0), ID_MENU_WIDGET_BASE + static_cast<UINT>(index), label.c_str());
    }
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_SHOW_ALL, T(TXT_SHOW_ALL), &menuMnemonics);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_HIDE_ALL, T(TXT_HIDE_ALL), &menuMnemonics);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_ARRANGE_WIDGETS, ARRANGE_WIDGET_LABELS[appLanguage], &menuMnemonics);
    bool activeAlarm = false;
    for (size_t index = 0; index < widgets.size(); index++) {
        activeAlarm = activeAlarm || widgets[index]->alarmActive;
    }
    if (activeAlarm) {
        AppendMenuCommand(menu, MF_STRING, ID_MENU_STOP_ALARM, T(TXT_STOP_ALARM), &menuMnemonics);
    }
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_SETTINGS, T(TXT_SETTINGS), &menuMnemonics, true);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_HELP, T(TXT_HELP), &menuMnemonics, true);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_ABOUT, T(TXT_ABOUT), &menuMnemonics, true);
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuCommand(menu, MF_STRING, ID_MENU_EXIT, T(TXT_EXIT), &menuMnemonics);
    POINT point = {};
    GetCursorPos(&point);
    SetForegroundWindow(hController);
    int command = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, hController, nullptr);
    DestroyMenu(menu);
    if (command >= ID_MENU_WIDGET_BASE && command < ID_MENU_WIDGET_BASE + static_cast<int>(widgets.size())) {
        SetWidgetVisible(widgets[command - ID_MENU_WIDGET_BASE].get(), !widgets[command - ID_MENU_WIDGET_BASE]->config.visible);
    } else {
        SendMessageW(hController, WM_COMMAND, command, 0);
    }
}

static std::wstring Mnemonic(TextId id) {
    return std::wstring(L"&") + T(id);
}

static HWND AddStatic(HWND parent, TextId id, int x, int y, int width, int height, std::vector<HWND>* group = nullptr) {
    std::wstring text = Mnemonic(id);
    HWND control = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", text.c_str(), WS_CHILD | WS_VISIBLE, x, y, width, height, parent, nullptr, hInstance, nullptr);
    if (group != nullptr) {
        group->push_back(control);
    }
    return control;
}

static HWND AddControl(DWORD extended, const wchar_t* className, const wchar_t* text, DWORD style, int x, int y, int width, int height, HWND parent, int id, std::vector<HWND>* group = nullptr) {
    HWND control = CreateWindowExW(extended, className, text, WS_CHILD | WS_VISIBLE | style, x, y, width, height, parent, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), hInstance, nullptr);
    if (control != nullptr && _wcsicmp(className, L"EDIT") == 0) {
        SetWindowSubclass(control, EditSubclassProc, static_cast<UINT_PTR>(id), 0);
    } else if (control != nullptr && id == ID_LIST_WIDGETS) {
        SetWindowSubclass(control, WidgetListSubclassProc, static_cast<UINT_PTR>(id), 0);
    }
    if (group != nullptr) {
        group->push_back(control);
    }
    return control;
}

static LRESULT CALLBACK EditSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (message == WM_LBUTTONDOWN || message == WM_LBUTTONDBLCLK) {
        DWORD clickTick = static_cast<DWORD>(GetMessageTime());
        POINT clickPoint = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        bool consecutiveClick = lastClickedEdit == window && clickTick - lastEditClickTick <= GetDoubleClickTime() &&
            abs(clickPoint.x - lastEditClickPoint.x) <= GetSystemMetrics(SM_CXDOUBLECLK) &&
            abs(clickPoint.y - lastEditClickPoint.y) <= GetSystemMetrics(SM_CYDOUBLECLK);
        editClickCount = consecutiveClick ? editClickCount + 1 : 1;
        lastClickedEdit = window;
        lastEditClickTick = clickTick;
        lastEditClickPoint = clickPoint;
        LRESULT result = DefSubclassProc(window, message, wParam, lParam);
        if (editClickCount >= 3) {
            SendMessageW(window, EM_SETSEL, 0, -1);
            lastClickedEdit = nullptr;
            lastEditClickTick = 0;
            editClickCount = 0;
            return 0;
        }
        return result;
    }
    if (message == WM_KEYDOWN && wParam == L'A' && (GetKeyState(VK_CONTROL) & 0x8000) != 0) {
        SendMessageW(window, EM_SETSEL, 0, -1);
        return 0;
    }
    if (message == WM_NCDESTROY) {
        if (lastClickedEdit == window) {
            lastClickedEdit = nullptr;
            lastEditClickTick = 0;
            editClickCount = 0;
        }
        RemoveWindowSubclass(window, EditSubclassProc, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

static LRESULT CALLBACK WidgetListSubclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR referenceData) {
    UNREFERENCED_PARAMETER(referenceData);
    if (message == WM_KEYDOWN && wParam == L'A' && (GetKeyState(VK_CONTROL) & 0x8000) != 0) {
        SendMessageW(window, LB_SETSEL, TRUE, -1);
        SendMessageW(GetParent(window), WM_COMMAND, MAKEWPARAM(ID_LIST_WIDGETS, LBN_SELCHANGE), reinterpret_cast<LPARAM>(window));
        return 0;
    }
    if (message == WM_NCDESTROY) {
        RemoveWindowSubclass(window, WidgetListSubclassProc, subclassId);
    }
    return DefSubclassProc(window, message, wParam, lParam);
}

static void SetCheck(HWND control, bool checked) {
    SendMessageW(control, BM_SETCHECK, checked ? BST_CHECKED : BST_UNCHECKED, 0);
}
static bool GetCheck(HWND control) {
    return SendMessageW(control, BM_GETCHECK, 0, 0) == BST_CHECKED;
}

static bool HideFullscreenWidgetsFromEscape() {
    bool hidden = false;
    for (size_t widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++) {
        Widget* widget = widgets[widgetIndex].get();
        if (widget->config.type != WIDGET_FULLSCREEN || !widget->config.visible) {
            continue;
        }
        if (widget->alarmActive || widget->audioStopEvent != nullptr) {
            StopWidgetAlarm(widget);
        }
        widget->config.visible = false;
        ShowWindow(widget->window, SW_HIDE);
        for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
            ShowWindow(widget->fullscreenWindows[windowIndex], SW_HIDE);
        }
        for (size_t draftIndex = 0; draftIndex < settingsDraft.size(); draftIndex++) {
            if (settingsDraft[draftIndex].id == widget->config.id) {
                settingsDraft[draftIndex].visible = false;
                if (static_cast<int>(draftIndex) == selectedDraftIndex && hVisibleCheck != nullptr) {
                    SetCheck(hVisibleCheck, false);
                }
                break;
            }
        }
        for (size_t originalIndex = 0; originalIndex < settingsAppearanceOriginals.size(); originalIndex++) {
            if (settingsAppearanceOriginals[originalIndex].id == widget->config.id) {
                settingsAppearanceOriginals[originalIndex].visible = false;
                break;
            }
        }
        hidden = true;
    }
    if (hidden) {
        RefreshFullscreenPresentation();
        UpdateTrayIcon();
        SaveSettingsWithoutAppearancePreviews();
    }
    return hidden;
}

static std::wstring GetControlText(HWND control) {
    int length = GetWindowTextLengthW(control);
    std::vector<wchar_t> text(length + 1, 0);
    GetWindowTextW(control, text.data(), static_cast<int>(text.size()));
    return text.data();
}

static void AssignSettingsMnemonicsToChildren(HWND parent, std::vector<wchar_t>* usedMnemonics) {
    for (HWND control = GetWindow(parent, GW_CHILD); control != nullptr; control = GetWindow(control, GW_HWNDNEXT)) {
        if (!IsWindowVisible(control)) {
            continue;
        }
        wchar_t className[32] = {};
        GetClassNameW(control, className, ARRAYSIZE(className));
        LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
        std::wstring text = GetControlText(control);
        bool button = _wcsicmp(className, L"Button") == 0 && (style & WS_TABSTOP) != 0;
        bool label = _wcsicmp(className, L"Static") == 0 && control != hNtpStatus && text.find(L':') != std::wstring::npos;
        if (!button && !label) {
            continue;
        }
        std::wstring caption = UniqueMnemonic(text.c_str(), usedMnemonics);
        if (caption != text) {
            SetWindowTextW(control, caption.c_str());
        }
    }
}

static void AssignSettingsMnemonics() {
    if (hSettings == nullptr || !IsWindow(hSettings)) {
        return;
    }
    int tab = hTabs == nullptr ? 0 : TabCtrl_GetCurSel(hTabs);
    HWND activePage = tab == 0 ? hGeneralPage : (tab == 1 ? hAppearancePage : (tab == 2 ? hAlarmPage : hTimePage));
    std::vector<wchar_t> usedMnemonics;
    if (activePage != nullptr && IsWindowVisible(activePage)) {
        AssignSettingsMnemonicsToChildren(activePage, &usedMnemonics);
    }
    AssignSettingsMnemonicsToChildren(hSettings, &usedMnemonics);
}

static void ApplySelectedNtpPresetToEdit() {
    if (hNtpPresetCombo == nullptr || hNtpServersEdit == nullptr) {
        return;
    }
    int preset = static_cast<int>(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0));
    if (preset < 0 || preset >= NTP_PRESET_CUSTOM) {
        return;
    }
    std::wstring servers = NtpServersForPreset(preset);
    updatingNtpPresetControls = true;
    SetWindowTextW(hNtpServersEdit, servers.c_str());
    updatingNtpPresetControls = false;
}

static void UpdateNtpSettingsControls() {
    if (hTimeSourceCombo == nullptr || hNtpPresetCombo == nullptr || hNtpServersEdit == nullptr) {
        return;
    }
    int source = static_cast<int>(SendMessageW(hTimeSourceCombo, CB_GETCURSEL, 0, 0));
    bool ntpSelected = source == 1;
    int selectedPreset = static_cast<int>(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0));
    bool settingsApplied = ntpSelected == useNtpTime && selectedPreset == ntpPreset && GetControlText(hNtpServersEdit) == ntpServers;
    EnableWindow(hNtpPresetCombo, ntpSelected);
    EnableWindow(hNtpServersEdit, ntpSelected);
    EnableWindow(hNtpSyncButton, ntpSelected && winsockReady && settingsApplied);
    std::wstring status;
    if (!ntpSelected) {
        status = NTP_STATUS_SYSTEM[appLanguage];
    } else if (!winsockReady) {
        status = NTP_STATUS_FAILED[appLanguage];
    } else if (ntpQueryRunning) {
        status = NTP_STATUS_WAITING[appLanguage];
    } else if (ntpTimeValid && ntpLastQueryFailed) {
        LONGLONG offsetMilliseconds = ntpOffset100Nanoseconds.load() / 10000;
        status = NTP_STATUS_RETAINED[appLanguage];
        status += L" " + ntpActiveServer + L" (" + FormatOffset(offsetMilliseconds) + L")";
    } else if (ntpTimeValid) {
        LONGLONG offsetMilliseconds = ntpOffset100Nanoseconds.load() / 10000;
        status = NTP_STATUS_SYNCHRONIZED[appLanguage];
        status += L" " + ntpActiveServer + L" (" + FormatOffset(offsetMilliseconds) + L")";
    } else if (lastNtpAttemptTick != 0) {
        status = NTP_STATUS_FAILED[appLanguage];
    } else {
        status = NTP_STATUS_WAITING[appLanguage];
    }
    SetWindowTextW(hNtpStatus, status.c_str());
}

static void ShowSettingsTab(int tab) {
    if (hGeneralPage != nullptr) {
        ShowWindow(hGeneralPage, tab == 0 ? SW_SHOW : SW_HIDE);
    }
    if (hAppearancePage != nullptr) {
        ShowWindow(hAppearancePage, tab == 1 ? SW_SHOW : SW_HIDE);
    }
    if (hAlarmPage != nullptr) {
        ShowWindow(hAlarmPage, tab == 2 ? SW_SHOW : SW_HIDE);
    }
    if (hTimePage != nullptr) {
        ShowWindow(hTimePage, tab == 3 ? SW_SHOW : SW_HIDE);
    }
    HWND activePage = tab == 0 ? hGeneralPage : (tab == 1 ? hAppearancePage : (tab == 2 ? hAlarmPage : hTimePage));
    if (activePage != nullptr) {
        SetWindowPos(activePage, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        RedrawWindow(activePage, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW);
    }
    if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        bool calendar = settingsDraft[selectedDraftIndex].type == WIDGET_CALENDAR;
        if (tab == 2) {
            for (size_t index = 0; index < alarmControls.size(); index++) {
                EnableWindow(alarmControls[index], !calendar);
            }
        }
    }
    AssignSettingsMnemonics();
}

static std::vector<int> GetSelectedWidgetIndices() {
    std::vector<int> selected;
    if (hWidgetList == nullptr || !IsWindow(hWidgetList)) {
        return selected;
    }
    int count = static_cast<int>(SendMessageW(hWidgetList, LB_GETSELCOUNT, 0, 0));
    if (count <= 0) {
        return selected;
    }
    selected.resize(count);
    int copied = static_cast<int>(SendMessageW(hWidgetList, LB_GETSELITEMS, count, reinterpret_cast<LPARAM>(selected.data())));
    if (copied < 0) {
        selected.clear();
    } else {
        selected.resize(copied);
    }
    return selected;
}

static void UpdateSettingsSelectionState() {
    bool singleSelection = GetSelectedWidgetIndices().size() == 1;
    if (hTabs != nullptr) {
        EnableWindow(hTabs, singleSelection);
    }
    if (hGeneralPage != nullptr) {
        EnableWindow(hGeneralPage, singleSelection);
    }
    if (hAppearancePage != nullptr) {
        EnableWindow(hAppearancePage, singleSelection);
    }
    if (hAlarmPage != nullptr) {
        EnableWindow(hAlarmPage, singleSelection);
    }
}

static void SelectOnlyWidgetIndex(int index) {
    if (hWidgetList == nullptr || !IsWindow(hWidgetList)) {
        return;
    }
    SendMessageW(hWidgetList, LB_SETSEL, FALSE, -1);
    if (index >= 0 && index < static_cast<int>(settingsDraft.size())) {
        SendMessageW(hWidgetList, LB_SETSEL, TRUE, index);
        SendMessageW(hWidgetList, LB_SETCARETINDEX, index, FALSE);
    }
    UpdateSettingsSelectionState();
}

static void RefreshWidgetList(bool preserveSelection = true) {
    std::vector<int> selectedIds;
    if (preserveSelection) {
        std::vector<int> selectedIndices = GetSelectedWidgetIndices();
        for (size_t index = 0; index < selectedIndices.size(); index++) {
            LRESULT id = SendMessageW(hWidgetList, LB_GETITEMDATA, selectedIndices[index], 0);
            if (id != LB_ERR) {
                selectedIds.push_back(static_cast<int>(id));
            }
        }
    }
    SendMessageW(hWidgetList, LB_RESETCONTENT, 0, 0);
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        std::wstring label = std::to_wstring(index + 1) + L". " + settingsDraft[index].name;
        int item = static_cast<int>(SendMessageW(hWidgetList, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label.c_str())));
        SendMessageW(hWidgetList, LB_SETITEMDATA, item, settingsDraft[index].id);
    }
    if (!settingsDraft.empty()) {
        selectedDraftIndex = std::clamp(selectedDraftIndex, 0, static_cast<int>(settingsDraft.size()) - 1);
        bool restored = false;
        for (size_t index = 0; index < settingsDraft.size(); index++) {
            if (std::find(selectedIds.begin(), selectedIds.end(), settingsDraft[index].id) != selectedIds.end()) {
                SendMessageW(hWidgetList, LB_SETSEL, TRUE, index);
                restored = true;
            }
        }
        if (!restored || SendMessageW(hWidgetList, LB_GETSEL, selectedDraftIndex, 0) == 0) {
            SendMessageW(hWidgetList, LB_SETSEL, TRUE, selectedDraftIndex);
        }
        SendMessageW(hWidgetList, LB_SETCARETINDEX, selectedDraftIndex, FALSE);
    }
    UpdateSettingsSelectionState();
}

static void SelectTimeZoneInCombo(const std::wstring& key) {
    int selected = 0;
    int count = static_cast<int>(SendMessageW(hTimeZoneCombo, CB_GETCOUNT, 0, 0));
    for (int index = 0; index < count; index++) {
        size_t zoneIndex = static_cast<size_t>(SendMessageW(hTimeZoneCombo, CB_GETITEMDATA, index, 0));
        if (zoneIndex < timeZones.size() && _wcsicmp(timeZones[zoneIndex].TimeZoneKeyName, key.c_str()) == 0) {
            selected = index;
            break;
        }
    }
    SendMessageW(hTimeZoneCombo, CB_SETCURSEL, selected, 0);
}

static void LoadMonitorSelection(const WidgetConfig& config) {
    if (hMonitorList == nullptr) {
        return;
    }
    RefreshDisplayMonitors();
    SendMessageW(hMonitorList, LB_RESETCONTENT, 0, 0);
    bool anySelected = false;
    for (size_t index = 0; index < displayMonitors.size(); index++) {
        int width = displayMonitors[index].rect.right - displayMonitors[index].rect.left;
        int height = displayMonitors[index].rect.bottom - displayMonitors[index].rect.top;
        std::wstring label = std::to_wstring(index + 1) + L"  (" + std::to_wstring(width) + L" × " + std::to_wstring(height) + L")";
        int item = static_cast<int>(SendMessageW(hMonitorList, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label.c_str())));
        SendMessageW(hMonitorList, LB_SETITEMDATA, item, index);
        if (ContainsMonitorDevice(config.monitorDevices, displayMonitors[index].device)) {
            SendMessageW(hMonitorList, LB_SETSEL, TRUE, item);
            anySelected = true;
        }
    }
    if (!anySelected && !displayMonitors.empty()) {
        SendMessageW(hMonitorList, LB_SETSEL, TRUE, 0);
    }
}

static std::wstring GetSelectedMonitorDevices() {
    std::wstring devices;
    if (hMonitorList == nullptr) {
        return devices;
    }
    int count = static_cast<int>(SendMessageW(hMonitorList, LB_GETCOUNT, 0, 0));
    for (int item = 0; item < count; item++) {
        if (SendMessageW(hMonitorList, LB_GETSEL, item, 0) <= 0) {
            continue;
        }
        size_t monitorIndex = static_cast<size_t>(SendMessageW(hMonitorList, LB_GETITEMDATA, item, 0));
        if (monitorIndex >= displayMonitors.size()) {
            continue;
        }
        if (!devices.empty()) {
            devices += L';';
        }
        devices += displayMonitors[monitorIndex].device;
    }
    if (devices.empty() && !displayMonitors.empty()) {
        devices = displayMonitors[0].device;
    }
    return devices;
}

static void SetSliderValueText(HWND label, int value, const wchar_t* suffix) {
    if (label == nullptr) {
        return;
    }
    wchar_t text[32] = {};
    swprintf_s(text, L"%d%s", value, suffix);
    if (GetControlText(label) == text) {
        return;
    }
    SetWindowTextW(label, text);
    RedrawWindow(label, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}

static void UpdateAppearanceSliderLabels(HWND changedTrackBar = nullptr) {
    if (hOpacityTrackBar == nullptr) {
        return;
    }
    int opacity = static_cast<int>(SendMessageW(hOpacityTrackBar, TBM_GETPOS, 0, 0));
    int fontSize = static_cast<int>(SendMessageW(hFontSizeTrackBar, TBM_GETPOS, 0, 0));
    int padding = static_cast<int>(SendMessageW(hPaddingTrackBar, TBM_GETPOS, 0, 0));
    int borderWidth = static_cast<int>(SendMessageW(hBorderWidthTrackBar, TBM_GETPOS, 0, 0));
    if (changedTrackBar == nullptr || changedTrackBar == hOpacityTrackBar) {
        SetSliderValueText(hOpacityValue, opacity, L" %");
    }
    if (changedTrackBar == nullptr || changedTrackBar == hFontSizeTrackBar) {
        bool fullscreen = selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size()) && settingsDraft[selectedDraftIndex].type == WIDGET_FULLSCREEN;
        SetSliderValueText(hFontSizeValue, fontSize, fullscreen ? L" %" : L" pt");
    }
    if (changedTrackBar == nullptr || changedTrackBar == hPaddingTrackBar) {
        SetSliderValueText(hPaddingValue, padding, L" px");
    }
    if (changedTrackBar == nullptr || changedTrackBar == hBorderWidthTrackBar) {
        SetSliderValueText(hBorderWidthValue, borderWidth, L" px");
    }
    if (changedTrackBar == hFontSizeTrackBar && selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        WidgetConfig preview = settingsDraft[selectedDraftIndex];
        preview.fontSize = fontSize;
        UpdateFontDescription(preview);
    }
}

static bool SaveAppearanceControlsToDraft() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return false;
    }
    WidgetConfig& config = settingsDraft[selectedDraftIndex];
    const int sizes[] = { 104, 130, 166, 198 };
    int sizeIndex = static_cast<int>(SendMessageW(hSizeCombo, CB_GETCURSEL, 0, 0));
    if (sizeIndex >= 0 && sizeIndex < 4) {
        config.size = sizes[sizeIndex];
    }
    config.opacity = std::clamp(static_cast<int>(SendMessageW(hOpacityTrackBar, TBM_GETPOS, 0, 0)), 5, 100);
    int minimumFontSize = config.type == WIDGET_FULLSCREEN ? 5 : 10;
    int maximumFontSize = config.type == WIDGET_FULLSCREEN ? 85 : 140;
    config.fontSize = std::clamp(static_cast<int>(SendMessageW(hFontSizeTrackBar, TBM_GETPOS, 0, 0)), minimumFontSize, maximumFontSize);
    if (config.type == WIDGET_DIGITAL) {
        config.fontDialogSize = config.fontSize * 10;
    }
    config.fontAntialiasing = std::clamp(static_cast<int>(SendMessageW(hWidgetAntialiasCombo, CB_GETCURSEL, 0, 0)), 0, FONT_ANTIALIAS_COUNT - 1);
    config.padding = std::clamp(static_cast<int>(SendMessageW(hPaddingTrackBar, TBM_GETPOS, 0, 0)), 0, 70);
    config.borderStyle = std::clamp(static_cast<int>(SendMessageW(hBorderTrackBar, TBM_GETPOS, 0, 0)), 0, DIGITAL_BORDER_STYLE_COUNT - 1);
    config.borderWidth = std::clamp(static_cast<int>(SendMessageW(hBorderWidthTrackBar, TBM_GETPOS, 0, 0)), 0, DIGITAL_BORDER_WIDTH_MAX);
    config.leadingZero = GetCheck(hLeadingZeroCheck);
    config.transparentBackground = GetCheck(hTransparentBackgroundCheck);
    config.disableThemes = GetCheck(hWidgetDisableThemesCheck);
    config.textColor = static_cast<COLORREF>(GetWindowLongPtrW(hTextColorButton, GWLP_USERDATA));
    config.backgroundColor = static_cast<COLORREF>(GetWindowLongPtrW(hBackgroundColorButton, GWLP_USERDATA));
    config.alarmTextColor = static_cast<COLORREF>(GetWindowLongPtrW(hAlarmTextColorButton, GWLP_USERDATA));
    config.alarmBackgroundColor = static_cast<COLORREF>(GetWindowLongPtrW(hAlarmBackgroundColorButton, GWLP_USERDATA));
    config.weekNumbers = GetCheck(hWeekNumbersCheck);
    config.sundayFirst = GetCheck(hSundayFirstCheck);
    int dateFormat = static_cast<int>(SendMessageW(hDateFormatCombo, CB_GETCURSEL, 0, 0));
    if (dateFormat >= 0 && dateFormat < DATE_FORMAT_COUNT) {
        config.dateCopyFormat = dateFormat;
    }
    return true;
}

static void UpdateSettingControlAvailability() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    WidgetType type = settingsDraft[selectedDraftIndex].type;
    bool fullscreen = type == WIDGET_FULLSCREEN;
    bool digital = type == WIDGET_DIGITAL || fullscreen;
    bool calendar = type == WIDGET_CALENDAR || type == WIDGET_PANEL;
    bool panel = type == WIDGET_PANEL;
    bool hasSize = type == WIDGET_ANALOG || type == WIDGET_PANEL;
    bool hasTextFont = digital || calendar;
    bool globalThemesDisabled = hDisableThemesCheck == nullptr ? themesDisabled : GetCheck(hDisableThemesCheck);
    bool widgetThemesDisabled = hWidgetDisableThemesCheck == nullptr ? settingsDraft[selectedDraftIndex].disableThemes : GetCheck(hWidgetDisableThemesCheck);
    bool calendarFontEnabled = globalThemesDisabled || widgetThemesDisabled;
    if (hAppearancePage != nullptr) {
        SendMessageW(hAppearancePage, WM_SETREDRAW, FALSE, 0);
    }
    EnableWindow(hSecondsCheck, type != WIDGET_CALENDAR);
    EnableWindow(hUtcTextCheck, digital && GetCheck(hUtcCheck));
    ShowWindow(hMonitorLabel, fullscreen ? SW_SHOW : SW_HIDE);
    ShowWindow(hMonitorList, fullscreen ? SW_SHOW : SW_HIDE);
    ShowWindow(hBlackoutMonitorsCheck, fullscreen ? SW_SHOW : SW_HIDE);
    if (fullscreen) {
        SetCheck(hTopmostCheck, true);
    }
    EnableWindow(hTopmostCheck, !fullscreen);
    SendMessageW(hFontSizeTrackBar, TBM_SETRANGE, TRUE, fullscreen ? MAKELPARAM(5, 85) : MAKELPARAM(10, 140));
    int currentFontSize = static_cast<int>(SendMessageW(hFontSizeTrackBar, TBM_GETPOS, 0, 0));
    SendMessageW(hFontSizeTrackBar, TBM_SETPOS, TRUE, std::clamp(currentFontSize, fullscreen ? 5 : 10, fullscreen ? 85 : 140));
    UpdateAppearanceSliderLabels();
    ShowWindow(hSizeLabel, hasSize ? SW_SHOW : SW_HIDE);
    ShowWindow(hSizeCombo, hasSize ? SW_SHOW : SW_HIDE);
    int opacityTop = hasSize ? 38 : 4;
    SetWindowPos(hOpacityLabel, nullptr, 8, opacityTop + 7, 102, 22, SWP_NOZORDER | SWP_NOACTIVATE);
    SetWindowPos(hOpacityTrackBar, nullptr, 114, opacityTop, 212, 32, SWP_NOZORDER | SWP_NOACTIVATE);
    SetWindowPos(hOpacityValue, nullptr, 328, opacityTop + 7, 48, 22, SWP_NOZORDER | SWP_NOACTIVATE);
    for (HWND control : {hFontSizeLabel, hFontSizeTrackBar, hFontSizeValue, hFontDescription, hLeadingZeroCheck, hTransparentBackgroundCheck, hTextColorButton,
                         hAlarmTextColorButton, hAlarmBackgroundColorButton, hPaddingLabel, hPaddingTrackBar, hPaddingValue, hBorderLabel, hBorderTrackBar, hBorderWidthLabel,
                         hBorderWidthTrackBar, hBorderWidthValue}) {
        if (control != nullptr) {
            ShowWindow(control, digital ? SW_SHOW : SW_HIDE);
        }
    }
    if (hasTextFont) {
        int fontX = panel ? 194 : 8;
        int fontY = digital ? 70 : (panel ? 106 : 76);
        SetWindowPos(hFontButton, nullptr, fontX, fontY, 178, 27, SWP_NOZORDER | SWP_NOACTIVATE);
        ShowWindow(hFontButton, SW_SHOW);
    } else {
        ShowWindow(hFontButton, SW_HIDE);
    }
    EnableWindow(hFontButton, digital || calendarFontEnabled);
    if (panel) {
        SetWindowPos(hPanelTopFontButton, nullptr, 8, 76, 178, 27, SWP_NOZORDER | SWP_NOACTIVATE);
        SetWindowPos(hPanelTimeFontButton, nullptr, 194, 76, 178, 27, SWP_NOZORDER | SWP_NOACTIVATE);
        SetWindowPos(hPanelBottomFontButton, nullptr, 8, 106, 178, 27, SWP_NOZORDER | SWP_NOACTIVATE);
    }
    for (HWND control : { hPanelTopFontButton, hPanelTimeFontButton, hPanelBottomFontButton }) {
        ShowWindow(control, panel ? SW_SHOW : SW_HIDE);
    }
    int defaultAppearanceX = 194;
    int defaultAppearanceY = digital ? 70 : (panel ? 240 : (calendar ? 76 : 110));
    SetWindowPos(hDefaultAppearanceButton, nullptr, defaultAppearanceX, defaultAppearanceY, 178, 27, SWP_NOZORDER | SWP_NOACTIVATE);
    ShowWindow(hDefaultAppearanceButton, SW_SHOW);
    if (fullscreen) {
        for (HWND control : {hTransparentBackgroundCheck, hBorderLabel, hBorderTrackBar, hBorderWidthLabel, hBorderWidthTrackBar, hBorderWidthValue}) {
            ShowWindow(control, SW_HIDE);
        }
    }
    bool showBackground = digital;
    ShowWindow(hBackgroundColorButton, showBackground ? SW_SHOW : SW_HIDE);
    if (showBackground) {
        SetWindowPos(hBackgroundColorButton, nullptr, 194, digital ? 100 : 76, 178, 27, SWP_NOZORDER | SWP_NOACTIVATE);
    }
    if (calendar) {
        int calendarTop = panel ? 140 : 110;
        SetWindowPos(hWeekNumbersCheck, nullptr, 8, calendarTop, 150, 24, SWP_NOZORDER | SWP_NOACTIVATE);
        SetWindowPos(hSundayFirstCheck, nullptr, 165, calendarTop, 205, 24, SWP_NOZORDER | SWP_NOACTIVATE);
        SetWindowPos(hDateFormatLabel, nullptr, 8, calendarTop + 34, 179, 22, SWP_NOZORDER | SWP_NOACTIVATE);
        SetWindowPos(hDateFormatCombo, nullptr, 191, calendarTop + 30, 181, 240, SWP_NOZORDER | SWP_NOACTIVATE);
    }
    for (HWND control : {hWeekNumbersCheck, hSundayFirstCheck, hDateFormatLabel, hDateFormatCombo}) {
        if (control != nullptr) {
            ShowWindow(control, calendar ? SW_SHOW : SW_HIDE);
        }
    }
    if (hWidgetDisableThemesCheck != nullptr && hWidgetAntialiasLabel != nullptr && hWidgetAntialiasCombo != nullptr) {
        int optionsTop = digital ? 258 : (panel ? 208 : (calendar ? 178 : 76));
        SetWindowPos(hWidgetAntialiasLabel, nullptr, 8, optionsTop + 4, 138, 22, SWP_NOZORDER | SWP_NOACTIVATE);
        SetWindowPos(hWidgetAntialiasCombo, nullptr, 148, optionsTop, 86, 100, SWP_NOZORDER | SWP_NOACTIVATE);
        SetWindowPos(hWidgetDisableThemesCheck, nullptr, 242, optionsTop, 130, 24, SWP_NOZORDER | SWP_NOACTIVATE);
    }
    EnableWindow(hOpacityTrackBar, !fullscreen);
    EnableWindow(hTransparentBackgroundCheck, !fullscreen);
    EnableWindow(hPaddingTrackBar, digital);
    EnableWindow(hBorderTrackBar, !fullscreen);
    EnableWindow(hBorderWidthTrackBar, !fullscreen);
    EnableWindow(hAlarmEnabledCheck, type != WIDGET_CALENDAR);
    EnableWindow(hAlarmTimeEdit, type != WIDGET_CALENDAR);
    EnableWindow(hRunCommandCheck, type != WIDGET_CALENDAR);
    EnableWindow(hCommandEdit, type != WIDGET_CALENDAR);
    EnableWindow(hBrowseButton, type != WIDGET_CALENDAR);
    EnableWindow(hLoopAudioCheck, type != WIDGET_CALENDAR);
    EnableWindow(hTestCommandButton, type != WIDGET_CALENDAR);
    EnableWindow(hRemoteScriptCheck, type != WIDGET_CALENDAR);
    EnableWindow(hRemoteScriptEdit, type != WIDGET_CALENDAR && GetCheck(hRemoteScriptCheck));
    if (hAppearancePage != nullptr) {
        SendMessageW(hAppearancePage, WM_SETREDRAW, TRUE, 0);
        RedrawWindow(hAppearancePage, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW);
    }
    AssignSettingsMnemonics();
}

static void FillDateFormatCombo(const WidgetConfig& config) {
    if (hDateFormatCombo == nullptr) {
        return;
    }
    SendMessageW(hDateFormatCombo, CB_RESETCONTENT, 0, 0);
    SendMessageW(hDateFormatCombo, CB_SETDROPPEDWIDTH, 360, 0);
    SYSTEMTIME date = {};
    GetDisplayedTime(config, &date);
    for (int index = 0; index < DATE_FORMAT_COUNT; index++) {
        std::wstring label = DateFormatCaption(config, date, index);
        SendMessageW(hDateFormatCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(label.c_str()));
    }
    SendMessageW(hDateFormatCombo, CB_SETCURSEL, std::clamp(config.dateCopyFormat, 0, DATE_FORMAT_COUNT - 1), 0);
}

static void LoadDraftIntoControls() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    const WidgetConfig& config = settingsDraft[selectedDraftIndex];
    SetWindowTextW(hNameEdit, config.name.c_str());
    SendMessageW(hTypeCombo, CB_SETCURSEL, config.type, 0);
    SetCheck(hVisibleCheck, config.visible);
    SetCheck(hTopmostCheck, config.topMost);
    SetCheck(hSecondsCheck, config.showSeconds);
    SetCheck(hUtcCheck, config.showUtc);
    SetCheck(hUtcTextCheck, config.showUtcText);
    SendMessageW(hWidgetLanguageCombo, CB_SETCURSEL, config.language, 0);
    SelectTimeZoneInCombo(config.timeZoneKey);
    LoadMonitorSelection(config);
    SetCheck(hBlackoutMonitorsCheck, config.blackoutOtherMonitors);
    SetWindowTextW(hOffsetEdit, FormatOffset(config.offsetMilliseconds).c_str());
    const int sizes[] = { 104, 130, 166, 198 };
    int sizeIndex = 1;
    for (int index = 0; index < 4; index++) {
        if (sizes[index] == config.size) {
            sizeIndex = index;
        }
    }
    SendMessageW(hSizeCombo, CB_SETCURSEL, sizeIndex, 0);
    SendMessageW(hOpacityTrackBar, TBM_SETPOS, TRUE, config.opacity);
    SendMessageW(hFontSizeTrackBar, TBM_SETPOS, TRUE, config.fontSize);
    SendMessageW(hWidgetAntialiasCombo, CB_SETCURSEL, config.fontAntialiasing, 0);
    SendMessageW(hPaddingTrackBar, TBM_SETPOS, TRUE, config.padding);
    SendMessageW(hBorderTrackBar, TBM_SETPOS, TRUE, config.borderStyle);
    SendMessageW(hBorderWidthTrackBar, TBM_SETPOS, TRUE, config.borderWidth);
    UpdateAppearanceSliderLabels();
    UpdateFontDescription(config);
    SetCheck(hLeadingZeroCheck, config.leadingZero);
    SetCheck(hTransparentBackgroundCheck, config.transparentBackground);
    SetCheck(hWidgetDisableThemesCheck, config.disableThemes);
    SetWindowLongPtrW(hTextColorButton, GWLP_USERDATA, config.textColor);
    SetWindowLongPtrW(hBackgroundColorButton, GWLP_USERDATA, config.backgroundColor);
    SetWindowLongPtrW(hAlarmTextColorButton, GWLP_USERDATA, config.alarmTextColor);
    SetWindowLongPtrW(hAlarmBackgroundColorButton, GWLP_USERDATA, config.alarmBackgroundColor);
    InvalidateRect(hTextColorButton, nullptr, TRUE);
    InvalidateRect(hBackgroundColorButton, nullptr, TRUE);
    InvalidateRect(hAlarmTextColorButton, nullptr, TRUE);
    InvalidateRect(hAlarmBackgroundColorButton, nullptr, TRUE);
    SetCheck(hWeekNumbersCheck, config.weekNumbers);
    SetCheck(hSundayFirstCheck, config.sundayFirst);
    FillDateFormatCombo(config);
    SetCheck(hAlarmEnabledCheck, config.alarmEnabled);
    wchar_t alarm[16] = {};
    swprintf_s(alarm, L"%02d:%02d", config.alarmHour, config.alarmMinute);
    SetWindowTextW(hAlarmTimeEdit, alarm);
    SetCheck(hRunCommandCheck, config.runCommand);
    SetWindowTextW(hCommandEdit, config.command.c_str());
    SetCheck(hLoopAudioCheck, config.loopAudio);
    SetCheck(hRemoteScriptCheck, config.callRemoteScript);
    SetWindowTextW(hRemoteScriptEdit, config.remoteScriptUrl.c_str());
    UpdateSettingControlAvailability();
}

static bool SaveControlsToDraft(bool showErrors) {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return true;
    }
    WidgetConfig& config = settingsDraft[selectedDraftIndex];
    LONGLONG offset = 0;
    std::wstring offsetText = GetControlText(hOffsetEdit);
    if (!ParseOffset(offsetText.c_str(), &offset)) {
        if (showErrors) {
            MessageBoxW(hSettings, T(TXT_INVALID_OFFSET), T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
            SetFocus(hOffsetEdit);
        }
        return false;
    }
    int hour = config.alarmHour;
    int minute = config.alarmMinute;
    std::wstring alarmText = GetControlText(hAlarmTimeEdit);
    if (!ParseAlarmTime(alarmText.c_str(), &hour, &minute)) {
        if (showErrors) {
            MessageBoxW(hSettings, T(TXT_INVALID_TIME), T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
            SetFocus(hAlarmTimeEdit);
        }
        return false;
    }
    int selectedType = static_cast<int>(SendMessageW(hTypeCombo, CB_GETCURSEL, 0, 0));
    bool remoteScriptEnabled = GetCheck(hRemoteScriptCheck);
    std::wstring remoteScriptUrl = GetControlText(hRemoteScriptEdit);
    if (selectedType != WIDGET_CALENDAR && remoteScriptEnabled && !IsRemoteScriptUrlValid(remoteScriptUrl)) {
        if (showErrors) {
            MessageBoxW(hSettings, INVALID_REMOTE_SCRIPT_URL[appLanguage], T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
            SetFocus(hRemoteScriptEdit);
            SendMessageW(hRemoteScriptEdit, EM_SETSEL, 0, -1);
        }
        return false;
    }
    config.name = GetControlText(hNameEdit);
    if (config.name.empty()) {
        config.name = TypeName(config.type);
    }
    if (selectedType >= 0 && selectedType < WIDGET_TYPE_COUNT) {
        config.type = static_cast<WidgetType>(selectedType);
    }
    config.visible = GetCheck(hVisibleCheck);
    config.topMost = GetCheck(hTopmostCheck);
    config.showSeconds = GetCheck(hSecondsCheck);
    config.showUtc = GetCheck(hUtcCheck);
    config.showUtcText = GetCheck(hUtcTextCheck);
    int widgetLanguage = static_cast<int>(SendMessageW(hWidgetLanguageCombo, CB_GETCURSEL, 0, 0));
    if (widgetLanguage >= 0 && widgetLanguage < LANG_COUNT) {
        config.language = static_cast<AppLanguage>(widgetLanguage);
    }
    int zoneSelection = static_cast<int>(SendMessageW(hTimeZoneCombo, CB_GETCURSEL, 0, 0));
    if (zoneSelection != CB_ERR) {
        size_t zoneIndex = static_cast<size_t>(SendMessageW(hTimeZoneCombo, CB_GETITEMDATA, zoneSelection, 0));
        if (zoneIndex < timeZones.size()) {
            config.timeZoneKey = timeZones[zoneIndex].TimeZoneKeyName;
        }
    }
    if (config.type == WIDGET_FULLSCREEN) {
        config.monitorDevices = GetSelectedMonitorDevices();
        config.blackoutOtherMonitors = GetCheck(hBlackoutMonitorsCheck);
    }
    config.offsetMilliseconds = offset;
    SaveAppearanceControlsToDraft();
    config.alarmEnabled = GetCheck(hAlarmEnabledCheck);
    config.alarmHour = hour;
    config.alarmMinute = minute;
    config.runCommand = GetCheck(hRunCommandCheck);
    config.command = GetControlText(hCommandEdit);
    config.loopAudio = GetCheck(hLoopAudioCheck);
    config.callRemoteScript = remoteScriptEnabled;
    config.remoteScriptUrl = remoteScriptUrl;
    return true;
}

static void CopyWidgetAppearance(WidgetConfig* target, const WidgetConfig& source) {
    if (target == nullptr) {
        return;
    }
    target->size = source.size;
    target->opacity = source.opacity;
    target->fontSize = source.fontSize;
    target->fontDialogSize = source.fontDialogSize;
    target->fontAntialiasing = source.fontAntialiasing;
    target->leadingZero = source.leadingZero;
    target->transparentBackground = source.transparentBackground;
    target->disableThemes = source.disableThemes;
    target->fontFace = source.fontFace;
    target->fontWeight = source.fontWeight;
    target->fontItalic = source.fontItalic;
    target->fontUnderline = source.fontUnderline;
    target->fontStrikeOut = source.fontStrikeOut;
    target->fontCharSet = source.fontCharSet;
    target->panelTopFont = source.panelTopFont;
    target->panelTimeFont = source.panelTimeFont;
    target->panelBottomFont = source.panelBottomFont;
    target->padding = source.padding;
    target->borderStyle = source.borderStyle;
    target->borderWidth = source.borderWidth;
    target->textColor = source.textColor;
    target->backgroundColor = source.backgroundColor;
    target->alarmTextColor = source.alarmTextColor;
    target->alarmBackgroundColor = source.alarmBackgroundColor;
    target->weekNumbers = source.weekNumbers;
    target->sundayFirst = source.sundayFirst;
    target->dateCopyFormat = source.dateCopyFormat;
}

static bool FontSelectionsEqual(const FontSelection& left, const FontSelection& right) {
    return left.face == right.face && left.dialogSize == right.dialogSize && left.weight == right.weight && left.italic == right.italic && left.underline == right.underline &&
        left.strikeOut == right.strikeOut && left.charSet == right.charSet;
}

static bool WidgetConfigurationsEqual(const WidgetConfig& left, const WidgetConfig& right) {
    return left.id == right.id && left.type == right.type && left.name == right.name && left.visible == right.visible && left.topMost == right.topMost &&
        left.showSeconds == right.showSeconds && left.showUtc == right.showUtc && left.showUtcText == right.showUtcText && left.language == right.language &&
        left.timeZoneKey == right.timeZoneKey && left.monitorDevices == right.monitorDevices && left.blackoutOtherMonitors == right.blackoutOtherMonitors &&
        left.offsetMilliseconds == right.offsetMilliseconds && left.x == right.x && left.y == right.y && left.previewX == right.previewX && left.previewY == right.previewY &&
        left.size == right.size && left.opacity == right.opacity &&
        left.fontSize == right.fontSize && left.fontDialogSize == right.fontDialogSize && left.fontAntialiasing == right.fontAntialiasing && left.leadingZero == right.leadingZero &&
        left.transparentBackground == right.transparentBackground &&
        left.disableThemes == right.disableThemes && left.fontFace == right.fontFace && left.fontWeight == right.fontWeight && left.fontItalic == right.fontItalic &&
        left.fontUnderline == right.fontUnderline && left.fontStrikeOut == right.fontStrikeOut && left.fontCharSet == right.fontCharSet &&
        FontSelectionsEqual(left.panelTopFont, right.panelTopFont) && FontSelectionsEqual(left.panelTimeFont, right.panelTimeFont) &&
        FontSelectionsEqual(left.panelBottomFont, right.panelBottomFont) && left.padding == right.padding &&
        left.borderStyle == right.borderStyle && left.borderWidth == right.borderWidth && left.textColor == right.textColor && left.backgroundColor == right.backgroundColor &&
        left.alarmTextColor == right.alarmTextColor && left.alarmBackgroundColor == right.alarmBackgroundColor && left.weekNumbers == right.weekNumbers &&
        left.sundayFirst == right.sundayFirst && left.dateCopyFormat == right.dateCopyFormat && left.alarmEnabled == right.alarmEnabled && left.alarmHour == right.alarmHour &&
        left.alarmMinute == right.alarmMinute && left.runCommand == right.runCommand && left.loopAudio == right.loopAudio && left.command == right.command &&
        left.callRemoteScript == right.callRemoteScript && left.remoteScriptUrl == right.remoteScriptUrl;
}

static bool WidgetConfigurationsDifferOnlyInSeconds(const WidgetConfig& left, const WidgetConfig& right) {
    WidgetConfig normalized = left;
    normalized.showSeconds = right.showSeconds;
    return WidgetConfigurationsEqual(normalized, right);
}

static void RecreateWidgetForConfiguration(Widget* widget, const WidgetConfig& configuration) {
    if (widget == nullptr || widget->window == nullptr) {
        return;
    }
    RECT rect = {};
    bool hasPosition = GetWindowRect(widget->window, &rect) != FALSE;
    int targetX = rect.left;
    int targetY = rect.top;
    if (hasPosition && widget->config.type == WIDGET_PANEL && configuration.type == WIDGET_PANEL) {
        POINT previousClockPosition = {};
        POINT newClockPosition = {};
        GetPanelLayout(widget->config, nullptr, &previousClockPosition, nullptr);
        GetPanelLayout(configuration, nullptr, &newClockPosition, nullptr);
        targetX = rect.left + previousClockPosition.x - newClockPosition.x;
    }
    bool alarmActive = widget->alarmActive;
    bool flashPhase = widget->flashPhase;
    int lastAlarmDate = widget->lastAlarmDate;
    int lastAlarmMinute = widget->lastAlarmMinute;
    ULONGLONG alarmStoppedTick = widget->alarmStoppedTick;
    bool identifyActive = widget->identifyActive;
    bool identifyPhase = widget->identifyPhase;
    bool identifyRestoreHidden = widget->identifyRestoreHidden;
    bool identifyRestoreNotTopmost = widget->identifyRestoreNotTopmost;
    ULONGLONG identifyEndTick = widget->identifyEndTick;
    if (configuration.type == WIDGET_CALENDAR && (widget->alarmActive || widget->audioStopEvent != nullptr)) {
        StopWidgetAlarm(widget);
        alarmActive = false;
        flashPhase = false;
    }
    if (widget->copyTooltip != nullptr && IsWindow(widget->copyTooltip)) {
        DestroyWindow(widget->copyTooltip);
    }
    widget->copyTooltip = nullptr;
    DestroyWindow(widget->window);
    if (widget->calendarFont != nullptr) {
        DeleteObject(widget->calendarFont);
        widget->calendarFont = nullptr;
    }
    for (size_t windowIndex = 0; windowIndex < widget->fullscreenWindows.size(); windowIndex++) {
        DestroyWindow(widget->fullscreenWindows[windowIndex]);
    }
    widget->fullscreenWindows.clear();
    widget->window = nullptr;
    widget->analogChild = nullptr;
    widget->analogProc = nullptr;
    widget->calendarChild = nullptr;
    widget->calendarProc = nullptr;
    widget->config = configuration;
    if (hasPosition) {
        widget->config.x = targetX;
        widget->config.y = targetY;
    }
    CreateWidgetWindow(widget);
    RefreshFullscreenPresentation();
    widget->alarmActive = alarmActive;
    widget->flashPhase = flashPhase;
    widget->lastAlarmDate = lastAlarmDate;
    widget->lastAlarmMinute = lastAlarmMinute;
    widget->alarmStoppedTick = alarmStoppedTick;
    widget->identifyActive = identifyActive;
    widget->identifyPhase = identifyPhase;
    widget->identifyRestoreHidden = identifyRestoreHidden;
    widget->identifyRestoreNotTopmost = identifyRestoreNotTopmost;
    widget->identifyEndTick = identifyEndTick;
    RenderWidget(widget);
}

static void RecreateWidgetForAppearance(Widget* widget, const WidgetConfig& appearance) {
    if (widget == nullptr || widget->window == nullptr || widget->config.type != appearance.type) {
        return;
    }
    WidgetConfig configuration = widget->config;
    CopyWidgetAppearance(&configuration, appearance);
    RecreateWidgetForConfiguration(widget, configuration);
}

static void ApplyWidgetAppearancePreview(Widget* widget, const WidgetConfig& appearance, bool structuralChange) {
    if (widget == nullptr || widget->window == nullptr || widget->config.type != appearance.type) {
        return;
    }
    if (widget->config.type == WIDGET_FULLSCREEN) {
        RECT previousPreviewRect = {};
        bool preservePreviewPosition = widget->fullscreenPreview && GetWindowRect(widget->window, &previousPreviewRect);
        CopyWidgetAppearance(&widget->config, appearance);
        RECT monitorRect = {};
        if (!GetPrimarySelectedMonitorRect(widget->config, &monitorRect)) {
            return;
        }
        int monitorWidth = monitorRect.right - monitorRect.left;
        int monitorHeight = monitorRect.bottom - monitorRect.top;
        int previewWidth = std::min(480, std::max(240, monitorWidth / 4));
        int previewHeight = std::max(120, MulDiv(previewWidth, monitorHeight, std::max(1, monitorWidth)));
        if (previewHeight > 300) {
            previewHeight = 300;
            previewWidth = std::max(160, MulDiv(previewHeight, monitorWidth, std::max(1, monitorHeight)));
        }
        int previewX = widget->config.previewX == CW_USEDEFAULT ? monitorRect.left + (monitorWidth - previewWidth) / 2 : widget->config.previewX;
        int previewY = widget->config.previewY == CW_USEDEFAULT ? monitorRect.top + (monitorHeight - previewHeight) / 2 : widget->config.previewY;
        if (preservePreviewPosition) {
            previewX = previousPreviewRect.left;
            previewY = previousPreviewRect.top;
        }
        ClampFormPosition(&previewX, &previewY, previewWidth, previewHeight);
        widget->fullscreenPreview = true;
        SetWindowPos(widget->window, HWND_TOPMOST, previewX, previewY, previewWidth, previewHeight, SWP_NOACTIVATE | SWP_SHOWWINDOW);
        for (size_t index = 0; index < widget->fullscreenWindows.size(); index++) {
            ShowWindow(widget->fullscreenWindows[index], SW_HIDE);
        }
        RefreshFullscreenPresentation();
        widget->rendered = false;
        RenderWidget(widget);
        return;
    }
    bool digital = widget->config.type == WIDGET_DIGITAL;
    bool calendarWidget = widget->config.type == WIDGET_CALENDAR || widget->config.type == WIDGET_PANEL;
    bool themeChanged = widget->config.disableThemes != appearance.disableThemes;
    bool fontAntialiasingChanged = widget->config.fontAntialiasing != appearance.fontAntialiasing;
    bool fontSelectionChanged = widget->config.fontFace != appearance.fontFace || widget->config.fontWeight != appearance.fontWeight ||
        widget->config.fontItalic != appearance.fontItalic || widget->config.fontCharSet != appearance.fontCharSet;
    bool panelFontChanged = !FontSelectionsEqual(widget->config.panelTopFont, appearance.panelTopFont) ||
        !FontSelectionsEqual(widget->config.panelTimeFont, appearance.panelTimeFont) || !FontSelectionsEqual(widget->config.panelBottomFont, appearance.panelBottomFont);
    bool digitalFrameChanged = digital && widget->config.borderStyle != appearance.borderStyle;
    bool digitalDimensionsChanged = digital && (digitalFrameChanged || widget->config.borderWidth != appearance.borderWidth || widget->config.padding != appearance.padding ||
                                                widget->config.leadingZero != appearance.leadingZero || widget->config.fontSize != appearance.fontSize ||
                                                widget->config.fontFace != appearance.fontFace || widget->config.fontWeight != appearance.fontWeight ||
                                                widget->config.fontItalic != appearance.fontItalic || widget->config.fontUnderline != appearance.fontUnderline ||
                                                widget->config.fontStrikeOut != appearance.fontStrikeOut || widget->config.fontCharSet != appearance.fontCharSet);
    bool requiresRecreation = widget->config.transparentBackground != appearance.transparentBackground ||
        (!digital && (structuralChange || widget->config.size != appearance.size || widget->config.weekNumbers != appearance.weekNumbers ||
            widget->config.sundayFirst != appearance.sundayFirst)) || (calendarWidget && (fontSelectionChanged || themeChanged));
    if (requiresRecreation) {
        RecreateWidgetForAppearance(widget, appearance);
        return;
    }
    if (digitalFrameChanged && !appearance.transparentBackground) {
        DWORD style = static_cast<DWORD>(GetWindowLongPtrW(widget->window, GWL_STYLE));
        DWORD extendedStyle = static_cast<DWORD>(GetWindowLongPtrW(widget->window, GWL_EXSTYLE));
        style &= ~WS_BORDER;
        extendedStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE);
        ApplyDigitalNativeBorderStyle(appearance.borderStyle, &style, &extendedStyle);
        SetWindowLongPtrW(widget->window, GWL_STYLE, static_cast<LONG_PTR>(style));
        SetWindowLongPtrW(widget->window, GWL_EXSTYLE, static_cast<LONG_PTR>(extendedStyle));
    }
    CopyWidgetAppearance(&widget->config, appearance);
    if (panelFontChanged && widget->config.type == WIDGET_PANEL) {
        widget->rendered = false;
    }
    if ((fontAntialiasingChanged || fontSelectionChanged) && widget->calendarChild != nullptr) {
        ApplyCalendarFont(widget);
    }
    if (digitalDimensionsChanged && !widget->config.transparentBackground) {
        int width = 0;
        int height = 0;
        GetWidgetDimensions(widget->config, &width, &height);
        UINT flags = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOREDRAW;
        if (digitalFrameChanged) {
            flags |= SWP_FRAMECHANGED;
        }
        SetWindowPos(widget->window, nullptr, 0, 0, width, height, flags);
        widget->rendered = false;
    }
    if (themeChanged) {
        ApplyWidgetTheme(widget->window, widget->config);
        if (widget->analogChild != nullptr) {
            ApplyWidgetTheme(widget->analogChild, widget->config);
        }
        if (widget->calendarChild != nullptr) {
            ApplyWidgetTheme(widget->calendarChild, widget->config);
        }
    }
    if (widget->config.type == WIDGET_PANEL || widget->config.type == WIDGET_CALENDAR) {
        LONG_PTR extendedStyle = GetWindowLongPtrW(widget->window, GWL_EXSTYLE);
        if ((extendedStyle & WS_EX_LAYERED) == 0) {
            SetWindowLongPtrW(widget->window, GWL_EXSTYLE, extendedStyle | WS_EX_LAYERED);
        }
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100), LWA_ALPHA);
    } else if (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground) {
        SetLayeredWindowAttributes(widget->window, 0, static_cast<BYTE>(widget->config.opacity * 255 / 100), LWA_ALPHA);
    }
    RenderWidget(widget);
}

static void PreviewSelectedWidgetAppearance(bool structuralChange) {
    if (!SaveAppearanceControlsToDraft()) {
        return;
    }
    WidgetConfig& appearance = settingsDraft[selectedDraftIndex];
    Widget* widget = FindWidgetById(appearance.id);
    if (widget == nullptr || widget->config.type != appearance.type) {
        return;
    }
    if (std::find(settingsAppearancePreviewIds.begin(), settingsAppearancePreviewIds.end(), appearance.id) == settingsAppearancePreviewIds.end()) {
        settingsAppearancePreviewIds.push_back(appearance.id);
    }
    settingsAppearancePreviewActive = true;
    ApplyWidgetAppearancePreview(widget, appearance, structuralChange);
}

static void RestoreSettingsAppearancePreview() {
    if (!settingsAppearancePreviewActive) {
        return;
    }
    for (size_t idIndex = 0; idIndex < settingsAppearancePreviewIds.size(); idIndex++) {
        int id = settingsAppearancePreviewIds[idIndex];
        Widget* widget = FindWidgetById(id);
        if (widget == nullptr) {
            continue;
        }
        for (size_t originalIndex = 0; originalIndex < settingsAppearanceOriginals.size(); originalIndex++) {
            if (settingsAppearanceOriginals[originalIndex].id == id) {
                RecreateWidgetForConfiguration(widget, settingsAppearanceOriginals[originalIndex]);
                break;
            }
        }
    }
    settingsAppearancePreviewActive = false;
    settingsAppearancePreviewIds.clear();
}

static bool SelectDraftWidgetById(int widgetId) {
    if (widgetId < 0) {
        return true;
    }
    int targetIndex = -1;
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        if (settingsDraft[index].id == widgetId) {
            targetIndex = static_cast<int>(index);
            break;
        }
    }
    if (targetIndex < 0) {
        return false;
    }
    if (targetIndex != selectedDraftIndex && !SaveControlsToDraft(true)) {
        SelectOnlyWidgetIndex(selectedDraftIndex);
        return false;
    }
    selectedDraftIndex = targetIndex;
    SelectOnlyWidgetIndex(selectedDraftIndex);
    LoadDraftIntoControls();
    return true;
}

static void ApplySettingsDraft() {
    StopSettingsPreview();
    for (size_t draftIndex = 0; draftIndex < settingsDraft.size(); draftIndex++) {
        Widget* current = FindWidgetById(settingsDraft[draftIndex].id);
        if (current != nullptr && current->window != nullptr) {
            RECT rect = {};
            if (GetWindowRect(current->window, &rect)) {
                if (current->fullscreenPreview) {
                    settingsDraft[draftIndex].previewX = rect.left;
                    settingsDraft[draftIndex].previewY = rect.top;
                } else {
                    int targetX = rect.left;
                    if (current->config.type == WIDGET_PANEL && settingsDraft[draftIndex].type == WIDGET_PANEL) {
                        POINT currentClockPosition = {};
                        POINT draftClockPosition = {};
                        GetPanelLayout(current->config, nullptr, &currentClockPosition, nullptr);
                        GetPanelLayout(settingsDraft[draftIndex], nullptr, &draftClockPosition, nullptr);
                        targetX = rect.left + currentClockPosition.x - draftClockPosition.x;
                    }
                    settingsDraft[draftIndex].x = targetX;
                    settingsDraft[draftIndex].y = rect.top;
                }
            }
        }
    }
    AppLanguage previousLanguage = appLanguage;
    appLanguage = static_cast<AppLanguage>(std::clamp(static_cast<int>(SendMessageW(hLanguageCombo, CB_GETCURSEL, 0, 0)), 0, LANG_COUNT - 1));
    RefreshInformationWindows();
    bool previousThemesDisabled = themesDisabled;
    themesDisabled = GetCheck(hDisableThemesCheck);
    int previousAppFontAntialiasing = appFontAntialiasing;
    appFontAntialiasing = std::clamp(static_cast<int>(SendMessageW(hAppAntialiasCombo, CB_GETCURSEL, 0, 0)), 0, FONT_ANTIALIAS_COUNT - 1);
    std::wstring previousAppFontFace = appFontFace;
    int previousAppFontWeight = appFontWeight;
    bool previousAppFontItalic = appFontItalic;
    appFontFace = settingsAppFontFace;
    appFontDialogSize = std::clamp(settingsAppFontDialogSize, 10, 9990);
    appFontWeight = std::clamp(settingsAppFontWeight, 0, 1000);
    appFontItalic = settingsAppFontItalic;
    storageUsesXml = GetCheck(hUseXmlSettingsCheck);
    bool newUseNtpTime = SendMessageW(hTimeSourceCombo, CB_GETCURSEL, 0, 0) == 1;
    int newNtpPreset = std::clamp(static_cast<int>(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0)), 0, NTP_PRESET_COUNT - 1);
    std::wstring newNtpServers = newNtpPreset == NTP_PRESET_CUSTOM ? GetControlText(hNtpServersEdit) : NtpServersForPreset(newNtpPreset);
    if (ParseNtpServerList(newNtpServers).empty()) {
        newNtpPreset = NTP_PRESET_GLOBAL;
        newNtpServers = NtpServersForPreset(newNtpPreset);
    }
    bool ntpSettingsChanged = useNtpTime != newUseNtpTime || ntpPreset != newNtpPreset || ntpServers != newNtpServers;
    useNtpTime = newUseNtpTime;
    ntpPreset = newNtpPreset;
    ntpServers = newNtpServers;
    if (ntpSettingsChanged) {
        ntpGeneration++;
        ntpTimeValid = false;
        ntpActiveServer.clear();
        ntpLastQueryFailed = false;
        lastNtpAttemptTick = 0;
    }
    SetThemeAppProperties(themesDisabled ? 0 : STAP_ALLOW_NONCLIENT | STAP_ALLOW_CONTROLS | STAP_ALLOW_WEBCONTENT);
    bool secondsOnlyOrUnchanged = previousLanguage == appLanguage && previousThemesDisabled == themesDisabled &&
        previousAppFontAntialiasing == appFontAntialiasing && previousAppFontFace == appFontFace && previousAppFontWeight == appFontWeight &&
        previousAppFontItalic == appFontItalic && settingsDraft.size() == widgets.size();
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        Widget* current = FindWidgetById(settingsDraft[index].id);
        if (current != nullptr) {
            current->config.fontDialogSize = settingsDraft[index].fontDialogSize;
        }
    }
    if (secondsOnlyOrUnchanged) {
        for (size_t index = 0; index < settingsDraft.size(); index++) {
            Widget* current = FindWidgetById(settingsDraft[index].id);
            if (current == nullptr || current->fullscreenPreview ||
                (!WidgetConfigurationsEqual(current->config, settingsDraft[index]) && !WidgetConfigurationsDifferOnlyInSeconds(current->config, settingsDraft[index]))) {
                secondsOnlyOrUnchanged = false;
                break;
            }
        }
    }
    if (secondsOnlyOrUnchanged) {
        for (size_t index = 0; index < settingsDraft.size(); index++) {
            Widget* current = FindWidgetById(settingsDraft[index].id);
            if (current == nullptr || current->config.showSeconds == settingsDraft[index].showSeconds) {
                continue;
            }
            current->config.showSeconds = settingsDraft[index].showSeconds;
            if (current->config.type == WIDGET_ANALOG || current->config.type == WIDGET_PANEL) {
                if (!ReplaceAnalogChild(current)) {
                    RecreateWidgetForConfiguration(current, settingsDraft[index]);
                }
            } else if (current->config.type == WIDGET_DIGITAL) {
                int width = 0;
                int height = 0;
                GetWidgetDimensions(current->config, &width, &height);
                SetWindowPos(current->window, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
            }
            current->lastRenderKey = -1;
            RenderWidget(current);
        }
    } else {
        DestroyWidgetWindows();
        widgets.clear();
        for (size_t index = 0; index < settingsDraft.size(); index++) {
            std::unique_ptr<Widget> widget(new Widget());
            widget->config = settingsDraft[index];
            widgets.push_back(std::move(widget));
        }
        for (size_t index = 0; index < widgets.size(); index++) {
            CreateWidgetWindow(widgets[index].get());
        }
        RefreshFullscreenPresentation();
    }
    for (size_t index = 0; index < widgets.size(); index++) {
        if (widgets[index]->calendarChild != nullptr) {
            ApplyCalendarFont(widgets[index].get());
        }
    }
    settingsAppearancePreviewActive = false;
    settingsAppearancePreviewIds.clear();
    settingsAppearanceOriginals.clear();
    if (previousAppFontAntialiasing != appFontAntialiasing || previousAppFontFace != appFontFace || previousAppFontWeight != appFontWeight ||
        previousAppFontItalic != appFontItalic) {
        ResetUiFont();
    }
    if (previousThemesDisabled != themesDisabled || previousAppFontAntialiasing != appFontAntialiasing || previousAppFontFace != appFontFace ||
        previousAppFontWeight != appFontWeight || previousAppFontItalic != appFontItalic) {
        ApplyUiStyle(hSettings);
        if (hHelp != nullptr) {
            ApplyUiStyle(hHelp);
        }
        if (hAbout != nullptr) {
            ApplyUiStyle(hAbout);
        }
    }
    settingsApplicationFontPreviewActive = false;
    UpdateTrayIcon();
    SaveAllSettings();
    if (useNtpTime) {
        StartNtpSynchronization(true);
    }
}

static void SynchronizeOpenSettings(const Widget* widget) {
    if (hSettings == nullptr || !IsWindow(hSettings) || widget == nullptr) {
        return;
    }
    for (size_t index = 0; index < settingsDraft.size(); index++) {
        if (settingsDraft[index].id == widget->config.id) {
            settingsDraft[index] = widget->config;
            if (static_cast<int>(index) == selectedDraftIndex) {
                LoadDraftIntoControls();
            }
            RefreshWidgetList();
            break;
        }
    }
}

static bool ChooseButtonColor(HWND button) {
    static COLORREF customColors[16] = {};
    CHOOSECOLORW choice = {};
    choice.lStructSize = sizeof(choice);
    choice.hwndOwner = hSettings;
    choice.rgbResult = static_cast<COLORREF>(GetWindowLongPtrW(button, GWLP_USERDATA));
    choice.lpCustColors = customColors;
    choice.Flags = CC_FULLOPEN | CC_RGBINIT;
    if (!ChooseColorW(&choice)) {
        return false;
    }
    SetWindowLongPtrW(button, GWLP_USERDATA, choice.rgbResult);
    InvalidateRect(button, nullptr, TRUE);
    return true;
}

static void UpdateFontDescription(const WidgetConfig& config) {
    if (hFontButton != nullptr) {
        SetWindowTextW(hFontButton, config.type == WIDGET_CALENDAR || config.type == WIDGET_PANEL ? CALENDAR_FONT_LABELS[appLanguage] : config.fontFace.c_str());
    }
    if (hPanelTopFontButton != nullptr) {
        SetWindowTextW(hPanelTopFontButton, PANEL_TOP_FONT_LABELS[appLanguage]);
    }
    if (hPanelTimeFontButton != nullptr) {
        SetWindowTextW(hPanelTimeFontButton, PANEL_TIME_FONT_LABELS[appLanguage]);
    }
    if (hPanelBottomFontButton != nullptr) {
        SetWindowTextW(hPanelBottomFontButton, PANEL_BOTTOM_FONT_LABELS[appLanguage]);
    }
    if (hFontDescription == nullptr) {
        return;
    }
    std::wstring description = config.fontFace + L", " + std::to_wstring(config.fontDialogSize / 10) + L" pt";
    if (config.fontWeight >= FW_BOLD) {
        description += L", Bold";
    }
    if (config.fontItalic) {
        description += L", Italic";
    }
    if (config.fontUnderline) {
        description += L", Underline";
    }
    if (config.fontStrikeOut) {
        description += L", Strikeout";
    }
    SetWindowTextW(hFontDescription, description.c_str());
}

static bool ChooseFontAttributes(HWND owner, std::wstring* face, int* sizeTenths, int* weight, bool* italic, BYTE* charSet, bool* underline = nullptr,
                                 bool* strikeOut = nullptr) {
    if (face == nullptr || sizeTenths == nullptr || weight == nullptr || italic == nullptr || charSet == nullptr) {
        return false;
    }
    HDC screen = GetDC(owner);
    int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSY);
    if (screen != nullptr) {
        ReleaseDC(owner, screen);
    }
    LOGFONTW font = {};
    font.lfHeight = -MulDiv(std::clamp(*sizeTenths, 10, 9990), dpi, 720);
    font.lfWeight = std::clamp(*weight, 0, 1000);
    font.lfItalic = *italic;
    font.lfUnderline = underline != nullptr && *underline;
    font.lfStrikeOut = strikeOut != nullptr && *strikeOut;
    font.lfCharSet = *charSet;
    font.lfOutPrecision = OUT_DEFAULT_PRECIS;
    font.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    font.lfQuality = DEFAULT_QUALITY;
    font.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    wcsncpy_s(font.lfFaceName, face->c_str(), _TRUNCATE);
    CHOOSEFONTW choice = {};
    choice.lStructSize = sizeof(choice);
    choice.hwndOwner = owner;
    choice.lpLogFont = &font;
    choice.iPointSize = std::clamp(*sizeTenths, 10, 9990);
    choice.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT | CF_FORCEFONTEXIST;
    if (!ChooseFontW(&choice) || font.lfFaceName[0] == L'\0') {
        return false;
    }
    *face = font.lfFaceName;
    *sizeTenths = std::clamp(choice.iPointSize, 10, 9990);
    *weight = std::clamp(static_cast<int>(font.lfWeight), 0, 1000);
    *italic = font.lfItalic != FALSE;
    if (underline != nullptr) {
        *underline = font.lfUnderline != FALSE;
    }
    if (strikeOut != nullptr) {
        *strikeOut = font.lfStrikeOut != FALSE;
    }
    *charSet = font.lfCharSet;
    return true;
}

static void ChooseWidgetFont() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    WidgetConfig& config = settingsDraft[selectedDraftIndex];
    if (!ChooseFontAttributes(hSettings, &config.fontFace, &config.fontDialogSize, &config.fontWeight, &config.fontItalic, &config.fontCharSet, &config.fontUnderline,
        &config.fontStrikeOut)) {
        return;
    }
    if (config.type == WIDGET_DIGITAL) {
        config.fontSize = std::clamp((config.fontDialogSize + 5) / 10, 10, 140);
        SendMessageW(hFontSizeTrackBar, TBM_SETPOS, TRUE, config.fontSize);
        UpdateAppearanceSliderLabels();
    }
    UpdateFontDescription(config);
    PreviewSelectedWidgetAppearance(false);
}

static void ChoosePanelFont(FontSelection* selection) {
    if (selection == nullptr) {
        return;
    }
    if (!ChooseFontAttributes(hSettings, &selection->face, &selection->dialogSize, &selection->weight, &selection->italic, &selection->charSet, &selection->underline,
        &selection->strikeOut)) {
        return;
    }
    PreviewSelectedWidgetAppearance(false);
}

static void ChooseApplicationFont() {
    std::wstring selectedFace = settingsAppFontFace;
    BYTE charSet = DEFAULT_CHARSET;
    if (selectedFace.empty()) {
        NONCLIENTMETRICSW metrics = {};
        metrics.cbSize = sizeof(metrics);
        if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) {
            selectedFace = metrics.lfMessageFont.lfFaceName;
            charSet = metrics.lfMessageFont.lfCharSet;
        }
    }
    if (ChooseFontAttributes(hSettings, &selectedFace, &settingsAppFontDialogSize, &settingsAppFontWeight, &settingsAppFontItalic, &charSet)) {
        settingsAppFontFace = selectedFace;
        UpdateApplicationFontButtons();
        ApplyApplicationFontPreview();
    }
}

static void ResetWidgetAppearance() {
    if (selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
        return;
    }
    WidgetConfig& config = settingsDraft[selectedDraftIndex];
    WidgetConfig defaults = {};
    SetDefaultWidgetAppearance(&defaults, config.type);
    CopyWidgetAppearance(&config, defaults);
    LoadDraftIntoControls();
    PreviewSelectedWidgetAppearance(false);
}

static void StopSettingsPreview() {
    settingsPreviewGeneration++;
    if (settingsPreviewStopEvent != nullptr) {
        SetEvent(settingsPreviewStopEvent);
        CloseHandle(settingsPreviewStopEvent);
        settingsPreviewStopEvent = nullptr;
    }
    if (settingsVisualPreviewActive) {
        Widget* widget = FindWidgetById(settingsVisualPreviewWidgetId);
        if (widget != nullptr) {
            widget->alarmActive = false;
            widget->flashPhase = false;
            RenderWidget(widget);
            if (widget->config.type == WIDGET_PANEL && widget->window != nullptr) {
                InvalidateRect(widget->window, nullptr, FALSE);
            }
        }
    }
    settingsVisualPreviewWidgetId = -1;
    settingsVisualPreviewActive = false;
    if (hTestCommandButton != nullptr) {
        SetWindowTextW(hTestCommandButton, TEST_COMMAND_LABELS[appLanguage]);
    }
}

static void TestSettingsCommand() {
    if (settingsPreviewStopEvent != nullptr || settingsVisualPreviewActive) {
        StopSettingsPreview();
        return;
    }
    bool remoteScriptEnabled = GetCheck(hRemoteScriptCheck);
    std::wstring remoteScriptUrl = GetControlText(hRemoteScriptEdit);
    if (remoteScriptEnabled && !IsRemoteScriptUrlValid(remoteScriptUrl)) {
        MessageBoxW(hSettings, INVALID_REMOTE_SCRIPT_URL[appLanguage], T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
        SetFocus(hRemoteScriptEdit);
        SendMessageW(hRemoteScriptEdit, EM_SETSEL, 0, -1);
        return;
    }
    SaveAppearanceControlsToDraft();
    PreviewSelectedWidgetAppearance(false);
    if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        Widget* widget = FindWidgetById(settingsDraft[selectedDraftIndex].id);
        if (widget != nullptr && widget->config.type != WIDGET_CALENDAR && !widget->alarmActive) {
            settingsVisualPreviewWidgetId = widget->config.id;
            settingsVisualPreviewActive = true;
            widget->alarmActive = true;
            widget->flashPhase = true;
            RenderWidget(widget);
            if (widget->config.type == WIDGET_PANEL && widget->window != nullptr) {
                InvalidateRect(widget->window, nullptr, FALSE);
            }
        }
    }
    std::wstring path = GetControlText(hCommandEdit);
    if (!path.empty()) {
        SetCheck(hRunCommandCheck, true);
        if (LooksLikeAudio(path)) {
            StartAudioPlaybackAsync(path, GetCheck(hLoopAudioCheck), hController, WM_SETTINGS_AUDIO_FINISHED, -1, settingsPreviewGeneration, &settingsPreviewStopEvent);
        } else {
            StartLocalCommandAsync(path);
        }
    }
    if (remoteScriptEnabled) {
        StartRemoteScriptAsync(remoteScriptUrl);
    }
    if (settingsPreviewStopEvent == nullptr && !settingsVisualPreviewActive) {
        StopSettingsPreview();
        return;
    }
    SetWindowTextW(hTestCommandButton, STOP_TEST_LABELS[appLanguage]);
}

static void BrowseForCommand() {
    wchar_t fileName[MAX_PATH] = {};
    OPENFILENAMEW dialog = {};
    dialog.lStructSize = sizeof(dialog);
    dialog.hwndOwner = hSettings;
    dialog.lpstrFile = fileName;
    dialog.nMaxFile = ARRAYSIZE(fileName);
    dialog.lpstrFilter = L"Zvuk a programy\0*.wav;*.mp3;*.wma;*.mid;*.midi;*.aac;*.m4a;*.exe;*.bat;*.cmd\0Všechny soubory\0*.*\0";
    dialog.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    if (GetOpenFileNameW(&dialog)) {
        SetWindowTextW(hCommandEdit, fileName);
        SetCheck(hRunCommandCheck, true);
        if (LooksLikeAudio(fileName)) {
            SetCheck(hLoopAudioCheck, true);
        }
    }
}

static void CreateSettingsControls() {
    generalControls.clear();
    appearanceControls.clear();
    alarmControls.clear();
    timeControls.clear();
    AddStatic(hSettings, TXT_TYPE, 10, 10, 52, 22);
    hAddType = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 62, 7, 160, 220, hSettings, ID_ADD_TYPE);
    for (int type = 0; type < WIDGET_TYPE_COUNT; type++) {
        SendMessageW(hAddType, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(TypeName(static_cast<WidgetType>(type))));
    }
    SendMessageW(hAddType, CB_SETCURSEL, WIDGET_ANALOG, 0);
    AddControl(0, L"BUTTON", Mnemonic(TXT_ADD).c_str(), WS_TABSTOP, 228, 5, 84, 27, hSettings, ID_ADD);
    hWidgetList = AddControl(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_TABSTOP | LBS_NOTIFY | LBS_EXTENDEDSEL | WS_VSCROLL, 10, 39, 302, 278, hSettings, ID_LIST_WIDGETS);
    AddControl(0, L"BUTTON", Mnemonic(TXT_REMOVE).c_str(), WS_TABSTOP, 10, 323, 148, 27, hSettings, ID_REMOVE);
    AddControl(0, L"BUTTON", Mnemonic(TXT_DUPLICATE).c_str(), WS_TABSTOP, 164, 323, 148, 27, hSettings, ID_DUPLICATE);
    hTabs = AddControl(0, WC_TABCONTROLW, L"", WS_TABSTOP, 322, 7, 430, 345, hSettings, ID_TABS);
    if (hTabs == nullptr) {
        return;
    }
    TCITEMW tab = {};
    tab.mask = TCIF_TEXT;
    tab.pszText = const_cast<wchar_t*>(T(TXT_GENERAL));
    TabCtrl_InsertItem(hTabs, 0, &tab);
    tab.pszText = const_cast<wchar_t*>(T(TXT_APPEARANCE));
    TabCtrl_InsertItem(hTabs, 1, &tab);
    tab.pszText = const_cast<wchar_t*>(T(TXT_ALARM));
    TabCtrl_InsertItem(hTabs, 2, &tab);
    tab.pszText = const_cast<wchar_t*>(TIME_TAB_LABELS[appLanguage]);
    TabCtrl_InsertItem(hTabs, 3, &tab);
    RECT pageRect = { 0, 0, 430, 345 };
    TabCtrl_AdjustRect(hTabs, FALSE, &pageRect);
    int pageX = 322 + pageRect.left;
    int pageY = 7 + pageRect.top;
    int pageWidth = pageRect.right - pageRect.left;
    int pageHeight = pageRect.bottom - pageRect.top;
    hGeneralPage = CreateWindowExW(0, CLASS_NAME, L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hAppearancePage = CreateWindowExW(0, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS, pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hAlarmPage = CreateWindowExW(0, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS, pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    hTimePage = CreateWindowExW(0, CLASS_NAME, L"", WS_CHILD | WS_CLIPSIBLINGS, pageX, pageY, pageWidth, pageHeight, hSettings, nullptr, hInstance, nullptr);
    int left = 8;
    int label = 162;
    int field = 244;
    int fieldLeft = left + label + 4;
    AddStatic(hGeneralPage, TXT_NAME, left, 11, label, 22, &generalControls);
    hNameEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL, fieldLeft, 8, field, 24, hGeneralPage, ID_NAME, &generalControls);
    AddStatic(hGeneralPage, TXT_TYPE, left, 42, label, 22, &generalControls);
    hTypeCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, fieldLeft, 38, field, 220, hGeneralPage, ID_TYPE, &generalControls);
    for (int type = 0; type < WIDGET_TYPE_COUNT; type++) {
        SendMessageW(hTypeCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(TypeName(static_cast<WidgetType>(type))));
    }
    hVisibleCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_VISIBLE).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left, 72, 105, 24, hGeneralPage, ID_VISIBLE, &generalControls);
    hTopmostCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_TOPMOST).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left + 112, 72, 145, 24, hGeneralPage, ID_TOPMOST, &generalControls);
    hSecondsCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_SECONDS).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left + 262, 72, 100, 24, hGeneralPage, ID_SECONDS, &generalControls);
    hUtcCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_UTC).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left, 100, 120, 24, hGeneralPage, ID_UTC, &generalControls);
    hUtcTextCheck = AddControl(0, L"BUTTON", UTC_TEXT_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX, left + 130, 100, 220, 24, hGeneralPage, ID_UTC_TEXT, &generalControls);
    AddStatic(hGeneralPage, TXT_TIMEZONE, left, 130, label, 22, &generalControls);
    hTimeZoneCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST | WS_VSCROLL, fieldLeft, 126, field, 260, hGeneralPage, ID_TIMEZONE, &generalControls);
    for (size_t index = 0; index < timeZones.size(); index++) {
        int item = static_cast<int>(SendMessageW(hTimeZoneCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(timeZones[index].StandardName)));
        SendMessageW(hTimeZoneCombo, CB_SETITEMDATA, item, index);
    }
    AddStatic(hGeneralPage, TXT_OFFSET, left, 161, label, 22, &generalControls);
    hOffsetEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL, fieldLeft, 158, 136, 24, hGeneralPage, ID_OFFSET, &generalControls);
    HWND widgetLanguageLabel = CreateWindowW(L"STATIC", WIDGET_LANGUAGE_LABELS[appLanguage], WS_CHILD | WS_VISIBLE | SS_LEFT, left, 194, label, 22, hGeneralPage, nullptr, hInstance, nullptr);
    generalControls.push_back(widgetLanguageLabel);
    hWidgetLanguageCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, fieldLeft, 190, field, 220, hGeneralPage, ID_WIDGET_LANGUAGE, &generalControls);
    for (int index = 0; index < LANG_COUNT; index++) {
        SendMessageW(hWidgetLanguageCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(LANGUAGE_NAMES[index]));
    }
    hMonitorLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", MONITOR_LABELS[appLanguage], WS_CHILD | SS_LEFT, left, 224, label, 22, hGeneralPage, nullptr, hInstance, nullptr);
    generalControls.push_back(hMonitorLabel);
    hMonitorList = AddControl(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_TABSTOP | LBS_EXTENDEDSEL | LBS_NOINTEGRALHEIGHT | WS_VSCROLL, fieldLeft, 220, field, 64, hGeneralPage, ID_MONITOR_LIST, &generalControls);
    hBlackoutMonitorsCheck = AddControl(0, L"BUTTON", BLACKOUT_MONITOR_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX, left, 288, 350, 24, hGeneralPage, ID_BLACKOUT_MONITORS, &generalControls);
    hSizeLabel = AddStatic(hAppearancePage, TXT_SIZE, 8, 12, 90, 22, &appearanceControls);
    hSizeCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 100, 8, 90, 180, hAppearancePage, ID_SIZE, &appearanceControls);
    for (const wchar_t* size : { L"104 px", L"130 px", L"166 px", L"198 px" }) {
        SendMessageW(hSizeCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(size));
    }
    hOpacityLabel = AddStatic(hAppearancePage, TXT_OPACITY, 8, 11, 102, 22, &appearanceControls);
    hOpacityTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS, 114, 4, 212, 32, hAppearancePage, ID_OPACITY, &appearanceControls);
    SendMessageW(hOpacityTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(5, 100));
    SendMessageW(hOpacityTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hOpacityTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hOpacityTrackBar, TBM_SETPAGESIZE, 0, 5);
    hOpacityValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT, 328, 11, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hOpacityValue);
    hFontSizeLabel = AddStatic(hAppearancePage, TXT_FONT_SIZE, 8, 45, 109, 22, &appearanceControls);
    hFontSizeTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS, 121, 38, 205, 32, hAppearancePage, ID_FONT_SIZE, &appearanceControls);
    SendMessageW(hFontSizeTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(10, 140));
    SendMessageW(hFontSizeTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hFontSizeTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hFontSizeTrackBar, TBM_SETPAGESIZE, 0, 5);
    hFontSizeValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT, 328, 45, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hFontSizeValue);
    hFontButton = AddControl(0, L"BUTTON", FONT_BUTTON_LABELS[appLanguage], WS_TABSTOP, 8, 70, 178, 27, hAppearancePage, ID_FONT, &appearanceControls);
    hPanelTopFontButton = AddControl(0, L"BUTTON", PANEL_TOP_FONT_LABELS[appLanguage], WS_TABSTOP, 8, 76, 178, 27, hAppearancePage, ID_PANEL_TOP_FONT, &appearanceControls);
    hPanelTimeFontButton = AddControl(0, L"BUTTON", PANEL_TIME_FONT_LABELS[appLanguage], WS_TABSTOP, 194, 76, 178, 27, hAppearancePage, ID_PANEL_TIME_FONT, &appearanceControls);
    hPanelBottomFontButton = AddControl(0, L"BUTTON", PANEL_BOTTOM_FONT_LABELS[appLanguage], WS_TABSTOP, 8, 106, 178, 27, hAppearancePage, ID_PANEL_BOTTOM_FONT,
                                        &appearanceControls);
    hDefaultAppearanceButton = AddControl(0, L"BUTTON", DEFAULT_APPEARANCE_LABELS[appLanguage], WS_TABSTOP, 194, 70, 178, 27, hAppearancePage, ID_DEFAULT_APPEARANCE, &appearanceControls);
    hTextColorButton = AddControl(0, L"BUTTON", Mnemonic(TXT_TEXT_COLOR).c_str(), WS_TABSTOP, 8, 100, 178, 27, hAppearancePage, ID_TEXT_COLOR, &appearanceControls);
    hBackgroundColorButton = AddControl(0, L"BUTTON", Mnemonic(TXT_BACKGROUND_COLOR).c_str(), WS_TABSTOP, 194, 100, 178, 27, hAppearancePage, ID_BACKGROUND_COLOR, &appearanceControls);
    hAlarmTextColorButton = AddControl(0, L"BUTTON", ALARM_TEXT_COLOR_LABELS[appLanguage], WS_TABSTOP, 8, 130, 178, 27, hAppearancePage, ID_ALARM_TEXT_COLOR, &appearanceControls);
    hAlarmBackgroundColorButton = AddControl(0, L"BUTTON", ALARM_BACKGROUND_COLOR_LABELS[appLanguage], WS_TABSTOP, 194, 130, 178, 27, hAppearancePage, ID_ALARM_BACKGROUND_COLOR, &appearanceControls);
    hPaddingLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", PADDING_LABELS[appLanguage], WS_CHILD | WS_VISIBLE, 8, 169, 100, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hPaddingLabel);
    hPaddingTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS, 110, 162, 216, 32, hAppearancePage, ID_PADDING, &appearanceControls);
    SendMessageW(hPaddingTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, 70));
    SendMessageW(hPaddingTrackBar, TBM_SETTICFREQ, 5, 0);
    SendMessageW(hPaddingTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hPaddingTrackBar, TBM_SETPAGESIZE, 0, 5);
    hPaddingValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT, 328, 169, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hPaddingValue);
    hBorderWidthLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", BORDER_WIDTH_LABELS[appLanguage], WS_CHILD | WS_VISIBLE, 8, 201, 100, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hBorderWidthLabel);
    hBorderWidthTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS, 110, 194, 216, 32, hAppearancePage, ID_BORDER_WIDTH, &appearanceControls);
    SendMessageW(hBorderWidthTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, DIGITAL_BORDER_WIDTH_MAX));
    SendMessageW(hBorderWidthTrackBar, TBM_SETTICFREQ, 1, 0);
    SendMessageW(hBorderWidthTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hBorderWidthTrackBar, TBM_SETPAGESIZE, 0, 1);
    hBorderWidthValue = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_RIGHT, 328, 201, 48, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hBorderWidthValue);
    hBorderLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", BORDER_LABELS[appLanguage], WS_CHILD | WS_VISIBLE, 8, 233, 100, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hBorderLabel);
    hBorderTrackBar = AddControl(0, TRACKBAR_CLASSW, L"", WS_TABSTOP | TBS_HORZ | TBS_AUTOTICKS, 110, 226, 216, 32, hAppearancePage, ID_BORDER, &appearanceControls);
    SendMessageW(hBorderTrackBar, TBM_SETRANGE, TRUE, MAKELPARAM(0, 3));
    SendMessageW(hBorderTrackBar, TBM_SETTICFREQ, 1, 0);
    SendMessageW(hBorderTrackBar, TBM_SETLINESIZE, 0, 1);
    SendMessageW(hBorderTrackBar, TBM_SETPAGESIZE, 0, 1);
    hWidgetAntialiasLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", ANTIALIASING_LABELS[appLanguage], WS_CHILD | WS_VISIBLE, 8, 262, 138, 22, hAppearancePage,
                                             nullptr, hInstance, nullptr);
    appearanceControls.push_back(hWidgetAntialiasLabel);
    hWidgetAntialiasCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 148, 258, 86, 100, hAppearancePage, ID_WIDGET_ANTIALIAS, &appearanceControls);
    for (int antialiasing = 0; antialiasing < FONT_ANTIALIAS_COUNT; antialiasing++) {
        SendMessageW(hWidgetAntialiasCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(ANTIALIASING_NAMES[antialiasing]));
    }
    hWidgetDisableThemesCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_VISUAL_STYLES).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 242, 258, 130, 24, hAppearancePage,
                                            ID_WIDGET_DISABLE_THEMES, &appearanceControls);
    hLeadingZeroCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_LEADING_ZERO).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 8, 286, 130, 24, hAppearancePage, ID_LEADING_ZERO, &appearanceControls);
    hTransparentBackgroundCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_TRANSPARENT_BG).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 145, 286, 220, 24, hAppearancePage, ID_TRANSPARENT_BG, &appearanceControls);
    hWeekNumbersCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_WEEK_NUMBERS).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 8, 76, 150, 24, hAppearancePage, ID_WEEK_NUMBERS, &appearanceControls);
    hSundayFirstCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_SUNDAY_FIRST).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 165, 76, 205, 24, hAppearancePage, ID_SUNDAY_FIRST, &appearanceControls);
    hDateFormatLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", DATE_FORMAT_LABELS[appLanguage], WS_CHILD | WS_VISIBLE | SS_LEFT, 8, 110, 179, 22, hAppearancePage, nullptr, hInstance, nullptr);
    appearanceControls.push_back(hDateFormatLabel);
    hDateFormatCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST | WS_VSCROLL, 191, 106, 181, 240, hAppearancePage, ID_DATE_FORMAT, &appearanceControls);
    int y = 12;
    hAlarmEnabledCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_ALARM_ACTIVE).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left, y, 175, 24, hAlarmPage, ID_ALARM_ENABLED, &alarmControls);
    y += 32;
    std::wstring alarmTimeLabel = Mnemonic(TXT_ALARM_TIME);
    HWND alarmTimeStatic = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", alarmTimeLabel.c_str(), WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, left, y - 1, 150, 22, hAlarmPage, nullptr, hInstance, nullptr);
    alarmControls.push_back(alarmTimeStatic);
    hAlarmTimeEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL, left + 154, y - 4, 100, 24, hAlarmPage, ID_ALARM_TIME, &alarmControls);
    y += 36;
    hRunCommandCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_RUN_FILE).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left, y, 290, 24, hAlarmPage, ID_RUN_COMMAND, &alarmControls);
    y += 30;
    hCommandEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL, left, y, 275, 24, hAlarmPage, ID_COMMAND, &alarmControls);
    hBrowseButton = AddControl(0, L"BUTTON", Mnemonic(TXT_BROWSE).c_str(), WS_TABSTOP, left + 282, y - 3, 88, 27, hAlarmPage, ID_BROWSE, &alarmControls);
    y += 32;
    hTestCommandButton = AddControl(0, L"BUTTON", TEST_COMMAND_LABELS[appLanguage], WS_TABSTOP, left, y - 2, 102, 27, hAlarmPage, ID_TEST_COMMAND, &alarmControls);
    hLoopAudioCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_LOOP_AUDIO).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, left + 110, y, 260, 24, hAlarmPage, ID_LOOP_AUDIO, &alarmControls);
    y += 34;
    hRemoteScriptCheck = AddControl(0, L"BUTTON", REMOTE_SCRIPT_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX, left, y, 300, 24, hAlarmPage, ID_REMOTE_SCRIPT, &alarmControls);
    y += 30;
    HWND remoteUrlLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", REMOTE_SCRIPT_URL_LABELS[appLanguage], WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, left, y + 3, 92, 22,
                                          hAlarmPage, nullptr, hInstance, nullptr);
    alarmControls.push_back(remoteUrlLabel);
    hRemoteScriptEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | ES_AUTOHSCROLL, left + 96, y, 274, 24, hAlarmPage, ID_REMOTE_SCRIPT_URL, &alarmControls);
    HWND timeSourceLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", TIME_SOURCE_LABELS[appLanguage], WS_CHILD | WS_VISIBLE, 8, 16, 122, 22, hTimePage, nullptr, hInstance, nullptr);
    timeControls.push_back(timeSourceLabel);
    hTimeSourceCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 132, 12, 240, 180, hTimePage, ID_TIME_SOURCE, &timeControls);
    SendMessageW(hTimeSourceCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(SYSTEM_TIME_LABELS[appLanguage]));
    SendMessageW(hTimeSourceCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(NTP_TIME_LABELS[appLanguage]));
    SendMessageW(hTimeSourceCombo, CB_SETCURSEL, useNtpTime ? 1 : 0, 0);
    HWND ntpPresetLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", NTP_PRESET_FIELD_LABELS[appLanguage], WS_CHILD | WS_VISIBLE, 8, 50, 122, 22, hTimePage, nullptr, hInstance, nullptr);
    timeControls.push_back(ntpPresetLabel);
    hNtpPresetCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 132, 46, 240, 220, hTimePage, ID_NTP_PRESET, &timeControls);
    for (int preset = 0; preset < NTP_PRESET_COUNT; preset++) {
        SendMessageW(hNtpPresetCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(NTP_PRESET_LABELS[appLanguage][preset]));
    }
    SendMessageW(hNtpPresetCombo, CB_SETDROPPEDWIDTH, 360, 0);
    SendMessageW(hNtpPresetCombo, CB_SETCURSEL, ntpPreset, 0);
    HWND ntpServersLabel = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", NTP_SERVERS_LABELS[appLanguage], WS_CHILD | WS_VISIBLE, 8, 82, 364, 22, hTimePage, nullptr, hInstance, nullptr);
    timeControls.push_back(ntpServersLabel);
    hNtpServersEdit = AddControl(WS_EX_CLIENTEDGE, L"EDIT", ntpServers.c_str(), WS_TABSTOP | ES_AUTOHSCROLL, 8, 106, 364, 24, hTimePage, ID_NTP_SERVERS, &timeControls);
    hNtpSyncButton = AddControl(0, L"BUTTON", NTP_SYNC_LABELS[appLanguage], WS_TABSTOP, 8, 140, 180, 27, hTimePage, ID_NTP_SYNC, &timeControls);
    hNtpStatus = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 8, 178, 364, 66, hTimePage, nullptr, hInstance, nullptr);
    timeControls.push_back(hNtpStatus);
    UpdateNtpSettingsControls();
    CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", APPLICATION_LANGUAGE_LABELS[appLanguage], WS_CHILD | WS_VISIBLE, 10, 364, 138, 22, hSettings, nullptr, hInstance, nullptr);
    hLanguageCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 150, 360, 220, 220, hSettings, ID_LANGUAGE);
    for (int index = 0; index < LANG_COUNT; index++) {
        SendMessageW(hLanguageCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(LANGUAGE_NAMES[index]));
    }
    SendMessageW(hLanguageCombo, CB_SETCURSEL, appLanguage, 0);
    CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", APPLICATION_FONT_LABELS[appLanguage], WS_CHILD | WS_VISIBLE, 390, 364, 130, 22, hSettings, nullptr, hInstance, nullptr);
    hAppFontButton = AddControl(0, L"BUTTON", L"", WS_TABSTOP, 522, 358, 142, 27, hSettings, ID_APP_FONT);
    hAppFontDefaultButton = AddControl(0, L"BUTTON", DEFAULT_FONT_LABELS[appLanguage], WS_TABSTOP, 670, 358, 72, 27, hSettings, ID_APP_FONT_DEFAULT);
    UpdateApplicationFontButtons();
    CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", ANTIALIASING_LABELS[appLanguage], WS_CHILD | WS_VISIBLE, 10, 393, 138, 22, hSettings, nullptr, hInstance, nullptr);
    hAppAntialiasCombo = AddControl(0, WC_COMBOBOXW, L"", WS_TABSTOP | CBS_DROPDOWNLIST, 150, 389, 220, 100, hSettings, ID_APP_ANTIALIAS);
    for (int antialiasing = 0; antialiasing < FONT_ANTIALIAS_COUNT; antialiasing++) {
        SendMessageW(hAppAntialiasCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(ANTIALIASING_NAMES[antialiasing]));
    }
    SendMessageW(hAppAntialiasCombo, CB_SETCURSEL, appFontAntialiasing, 0);
    hDisableThemesCheck = AddControl(0, L"BUTTON", Mnemonic(TXT_VISUAL_STYLES).c_str(), WS_TABSTOP | BS_AUTOCHECKBOX, 390, 389, 150, 24, hSettings, ID_VISUAL_STYLES);
    SetCheck(hDisableThemesCheck, themesDisabled);
    hUseXmlSettingsCheck = AddControl(0, L"BUTTON", XML_STORAGE_LABELS[appLanguage], WS_TABSTOP | BS_AUTOCHECKBOX, 548, 389, 194, 24, hSettings, ID_USE_XML_SETTINGS);
    SetCheck(hUseXmlSettingsCheck, storageUsesXml);
    AddControl(0, L"BUTTON", IMPORT_SETTINGS_LABELS[appLanguage], WS_TABSTOP, 10, 420, 148, 27, hSettings, ID_IMPORT_SETTINGS);
    AddControl(0, L"BUTTON", EXPORT_SETTINGS_LABELS[appLanguage], WS_TABSTOP, 164, 420, 148, 27, hSettings, ID_EXPORT_SETTINGS);
    AddControl(0, L"BUTTON", Mnemonic(TXT_SAVE).c_str(), WS_TABSTOP | BS_DEFPUSHBUTTON, 524, 420, 70, 27, hSettings, ID_SAVE);
    AddControl(0, L"BUTTON", Mnemonic(TXT_APPLY).c_str(), WS_TABSTOP, 598, 420, 70, 27, hSettings, ID_APPLY);
    AddControl(0, L"BUTTON", Mnemonic(TXT_CANCEL).c_str(), WS_TABSTOP, 672, 420, 70, 27, hSettings, ID_CANCEL);
    ApplyUiStyle(hSettings);
    ShowSettingsTab(0);
}

static void RebuildSettingsControls() {
    if (hSettings == nullptr || !IsWindow(hSettings)) {
        return;
    }
    StopSettingsPreview();
    int selectedTab = hTabs == nullptr ? 0 : TabCtrl_GetCurSel(hTabs);
    HWND child = GetWindow(hSettings, GW_CHILD);
    while (child != nullptr) {
        HWND next = GetWindow(child, GW_HWNDNEXT);
        DestroyWindow(child);
        child = next;
    }
    hWidgetList = nullptr;
    hTabs = nullptr;
    hGeneralPage = nullptr;
    hAppearancePage = nullptr;
    hAlarmPage = nullptr;
    hTimePage = nullptr;
    hUtcTextCheck = nullptr;
    hMonitorLabel = nullptr;
    hMonitorList = nullptr;
    hBlackoutMonitorsCheck = nullptr;
    hWidgetAntialiasLabel = nullptr;
    hWidgetAntialiasCombo = nullptr;
    hAppAntialiasCombo = nullptr;
    hAppFontButton = nullptr;
    hAppFontDefaultButton = nullptr;
    hRemoteScriptCheck = nullptr;
    hRemoteScriptEdit = nullptr;
    SetWindowTextW(hSettings, T(TXT_SETTINGS));
    CreateSettingsControls();
    RefreshWidgetList();
    LoadDraftIntoControls();
    if (hTabs == nullptr) {
        return;
    }
    TabCtrl_SetCurSel(hTabs, std::clamp(selectedTab, 0, 3));
    ShowSettingsTab(TabCtrl_GetCurSel(hTabs));
}

static void CloseSettingsWindow() {
    RestoreSettingsAppearancePreview();
    RestoreApplicationFontPreview();
    StopSettingsPreview();
    if (hSettings != nullptr && IsWindow(hSettings)) {
        SaveFormPosition(hSettings, &settingsX, &settingsY);
        DestroyWindow(hSettings);
        SaveAllSettings();
    }
    hSettings = nullptr;
    hWidgetList = nullptr;
    hTabs = nullptr;
    hGeneralPage = nullptr;
    hAppearancePage = nullptr;
    hAlarmPage = nullptr;
    hTimePage = nullptr;
    hWidgetAntialiasLabel = nullptr;
    hWidgetAntialiasCombo = nullptr;
    hAppAntialiasCombo = nullptr;
    hAppFontButton = nullptr;
    hAppFontDefaultButton = nullptr;
    hRemoteScriptCheck = nullptr;
    hRemoteScriptEdit = nullptr;
    hTimeSourceCombo = nullptr;
    hNtpPresetCombo = nullptr;
    hNtpServersEdit = nullptr;
    hNtpStatus = nullptr;
    hNtpSyncButton = nullptr;
    settingsDraft.clear();
    settingsAppearanceOriginals.clear();
    settingsAppearancePreviewIds.clear();
    settingsAppearancePreviewActive = false;
    settingsApplicationFontPreviewActive = false;
    RefreshFullscreenPresentation();
}

static bool ChooseSettingsXmlFile(bool save, std::wstring* path) {
    if (path == nullptr) {
        return false;
    }
    wchar_t file[MAX_PATH] = L"CalClock-settings.xml";
    const wchar_t filter[] = L"CalClock XML (*.xml)\0*.xml\0XML (*.xml)\0*.xml\0\0";
    OPENFILENAMEW dialog = {};
    dialog.lStructSize = sizeof(dialog);
    dialog.hwndOwner = hSettings;
    dialog.lpstrFilter = filter;
    dialog.lpstrFile = file;
    dialog.nMaxFile = ARRAYSIZE(file);
    dialog.lpstrDefExt = L"xml";
    dialog.Flags = OFN_EXPLORER | OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | (save ? OFN_OVERWRITEPROMPT : OFN_FILEMUSTEXIST);
    BOOL selected = save ? GetSaveFileNameW(&dialog) : GetOpenFileNameW(&dialog);
    if (!selected) {
        return false;
    }
    *path = file;
    return true;
}

static void ExportSettings() {
    std::wstring path;
    if (!ChooseSettingsXmlFile(true, &path)) {
        return;
    }
    if (!SaveControlsToDraft(true)) {
        return;
    }
    ApplySettingsDraft();
    if (!WriteSettingsXml(path, CaptureSettingsSnapshot())) {
        MessageBoxW(hSettings, SETTINGS_EXPORT_FAILED[appLanguage], T(TXT_SETTINGS), MB_OK | MB_ICONERROR);
    }
}

static void ImportSettings() {
    std::wstring path;
    if (!ChooseSettingsXmlFile(false, &path)) {
        return;
    }
    SettingsSnapshot snapshot = {};
    if (!ReadSettingsXml(path, &snapshot)) {
        MessageBoxW(hSettings, INVALID_SETTINGS_FILE[appLanguage], T(TXT_SETTINGS), MB_OK | MB_ICONWARNING);
        return;
    }
    bool useXmlStorage = GetCheck(hUseXmlSettingsCheck);
    CloseSettingsWindow();
    DestroyWidgetWindows();
    ApplySettingsSnapshot(snapshot);
    ResetUiFont();
    storageUsesXml = useXmlStorage;
    SetThemeAppProperties(themesDisabled ? 0 : STAP_ALLOW_NONCLIENT | STAP_ALLOW_CONTROLS | STAP_ALLOW_WEBCONTENT);
    for (size_t index = 0; index < widgets.size(); index++) {
        CreateWidgetWindow(widgets[index].get());
    }
    RefreshFullscreenPresentation();
    RefreshInformationWindows();
    if (hHelp != nullptr) {
        ApplyUiStyle(hHelp);
    }
    if (hAbout != nullptr) {
        ApplyUiStyle(hAbout);
    }
    UpdateTrayIcon();
    SaveAllSettings();
    if (useNtpTime) {
        StartNtpSynchronization(true);
    }
    ShowSettingsWindow();
}

static void ShowSettingsWindow(int widgetId) {
    if (hSettings != nullptr && IsWindow(hSettings)) {
        SelectDraftWidgetById(widgetId);
        SetForegroundWindowEx(hSettings);
        return;
    }
    settingsDraft.clear();
    for (size_t index = 0; index < widgets.size(); index++) {
        settingsDraft.push_back(widgets[index]->config);
    }
    settingsAppearanceOriginals = settingsDraft;
    settingsAppearancePreviewIds.clear();
    settingsAppearancePreviewActive = false;
    settingsAppFontFace = appFontFace;
    settingsAppFontDialogSize = appFontDialogSize;
    settingsAppFontWeight = appFontWeight;
    settingsAppFontItalic = appFontItalic;
    selectedDraftIndex = 0;
    if (widgetId >= 0) {
        for (size_t index = 0; index < settingsDraft.size(); index++) {
            if (settingsDraft[index].id == widgetId) {
                selectedDraftIndex = static_cast<int>(index);
                break;
            }
        }
    }
    ClampFormPosition(&settingsX, &settingsY, 778, 491);
    hSettings = CreateWindowExW((std::any_of(widgets.begin(), widgets.end(), [](const std::unique_ptr<Widget>& w) { return w->config.topMost; }) ? WS_EX_TOPMOST : 0), CLASS_NAME, T(TXT_SETTINGS), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, settingsX, settingsY, 778, 491, nullptr, nullptr, hInstance, nullptr);
    CreateSettingsControls();
    RefreshWidgetList();
    LoadDraftIntoControls();
    ShowWindow(hSettings, SW_SHOW);
    SetForegroundWindowEx(hSettings);
}

const wchar_t* HELP_TEXT[LANG_COUNT] = { L"OVLÁDÁNÍ\r\nLevým tlačítkem a tažením přesunete hodiny nebo panel. "
                                        L"Samostatný kalendář se přesouvá za volnou plochu; kliknutím na den "
                                        L"měníte vybrané datum a šipkami, "
                                        L"záhlavím nebo odkazem Dnes kalendář procházíte. Pravým tlačítkem na "
                                        L"widgetu nebo na ikoně v oznamovací oblasti otevřete nabídku. Levé "
                                        L"kliknutí na ikonu zobrazí nebo skryje "
                                        L"všechny widgety.\r\n\r\nWIDGETY A NASTAVENÍ\r\nV Nastavení lze přidat, "
                                        L"odebrat a duplikovat libovolný počet ručičkových hodin, digitálních "
                                        L"hodin, kalendářů a panelů s "
                                        L"kalendářem a hodinami. Každý widget má vlastní viditelnost, režim vždy "
                                        L"navrchu, jazyk, časové pásmo a offset. Offset zadávejte jako "
                                        L"[-]HH:mm:ss.ff. Ručičkové hodiny a "
                                        L"hodiny v panelu mají čtyři velikosti. U digitálních hodin lze nastavit "
                                        L"sekundy, úvodní nulu, písmo, barvy, neprůhlednost a průhledné pozadí. "
                                        L"Kalendář podporuje čísla týdnů, "
                                        L"neděli jako první den a používá zvolený jazyk "
                                        L"widgetu.\r\n\r\nBUDÍK\r\nBudík lze nastavit pro hodiny a panel. Zvukový "
                                        L"soubor aplikace přehrává sama jednou nebo stále dokola "
                                        L"podle volby. Ostatní soubor nebo příkaz předá systému Windows. Kliknutím "
                                        L"na budící ciferník či displej, příkazem Zastavit budík nebo klávesou Esc "
                                        L"zastavíte blikání i zvuk "
                                        L"přehrávaný aplikací.\r\n\r\nZKRATKY A UKLÁDÁNÍ\r\nDvojklik na hodiny "
                                        L"přepne sekundy, F1 otevře nápovědu, B otevře Nastavení a Esc skryje "
                                        L"widget, pokud právě nezastavuje "
                                        L"budík. Polohy widgetů se ukládají po přesunutí, polohy formulářů při "
                                        L"zavření a nastavení do zvoleného úložiště. Další spuštění programu "
                                        L"aktivuje již běžící instanci a "
                                        L"zachová widgety u nejbližšího dostupného okraje pracovní plochy.",
                                        L"CONTROLS\r\nDrag a clock or panel with the left mouse button. Drag a "
                                        L"standalone calendar by its free area; click a day to change the "
                                        L"selection and use the arrows, header or "
                                        L"Today link to navigate. Right-click a widget or notification icon for "
                                        L"its menu. Left-click the notification icon to show or hide all "
                                        L"widgets.\r\n\r\nWIDGETS AND "
                                        L"SETTINGS\r\nSettings can add, remove and duplicate any number of analog "
                                        L"clocks, digital clocks, calendars and calendar-and-clock panels. Each "
                                        L"widget has its own visibility, "
                                        L"always-on-top state, language, time zone and offset. Enter offsets as "
                                        L"[-]HH:mm:ss.ff. Analog clocks and panel clocks have four sizes. Digital "
                                        L"clocks support seconds, a "
                                        L"leading zero, font, colours, opacity and a transparent background. "
                                        L"Calendars support week numbers and Sunday as the first day and use the "
                                        L"widget "
                                        L"language.\r\n\r\nALARM\r\nClocks and panels can have an alarm. The "
                                        L"application plays an audio file itself, once or continuously according "
                                        L"to the loop option. Other files or "
                                        L"commands are passed to Windows. Click the alarming clock face or "
                                        L"display, choose Stop alarm, or press Esc to stop both the alarm "
                                        L"indication and audio played by the "
                                        L"application.\r\n\r\nSHORTCUTS AND SAVING\r\nDouble-click a clock to "
                                        L"toggle seconds, press F1 for Help, B for Settings, and Esc to hide a "
                                        L"widget when no alarm is being "
                                        L"stopped. Widget positions are saved after dragging, dialog positions "
                                        L"when closed, and all settings in the registry. Starting the program "
                                        L"again activates the running "
                                        L"instance and keeps widgets at the nearest available point in the work "
                                        L"area.",
                                        L"BEDIENUNG\r\nZiehen Sie eine Uhr oder ein Panel mit der linken "
                                        L"Maustaste. Einen einzelnen Kalender ziehen Sie an seiner freien Fläche; "
                                        L"ein Klick auf einen Tag ändert die "
                                        L"Auswahl. Rechtsklick auf Widget oder Infobereichsymbol öffnet das Menü. "
                                        L"Linksklick auf das Symbol zeigt oder verbirgt alle "
                                        L"Widgets.\r\n\r\nWIDGETS UND EINSTELLUNGEN\r\nSie "
                                        L"können beliebig viele Analoguhren, Digitaluhren, Kalender und "
                                        L"Kalender-Uhr-Panels hinzufügen, entfernen oder duplizieren. Jedes Widget "
                                        L"besitzt eigene Sichtbarkeit, "
                                        L"Vordergrundlage, Sprache, Zeitzone und einen Versatz im Format "
                                        L"[-]HH:mm:ss.ff. Analoguhren haben vier Größen. Digitaluhren bieten "
                                        L"Sekunden, führende Null, Schrift, Farben, "
                                        L"Deckkraft und transparenten Hintergrund. Kalender bieten Wochennummern, "
                                        L"Sonntag als ersten Tag und verwenden die "
                                        L"Widget-Sprache.\r\n\r\nWECKER\r\nEine Audiodatei wird "
                                        L"intern einmal oder in Schleife abgespielt; andere Dateien oder Befehle "
                                        L"werden an Windows übergeben. Ein Klick auf das alarmierende Zifferblatt "
                                        L"bzw. Display, Wecker stoppen "
                                        L"oder Esc beendet Anzeige und intern abgespielten Ton.\r\n\r\nTASTEN UND "
                                        L"SPEICHERN\r\nDoppelklick schaltet Sekunden um, F1 öffnet Hilfe, B die "
                                        L"Einstellungen. Positionen und "
                                        L"sämtliche Einstellungen werden in der Registrierung gespeichert. Ein "
                                        L"erneuter Programmstart aktiviert die laufende Instanz.",
                                        L"COMMANDES\r\nFaites glisser une horloge ou un panneau avec le bouton "
                                        L"gauche. Déplacez un calendrier autonome par sa zone libre ; cliquez sur "
                                        L"un jour pour changer la "
                                        L"sélection. Un clic droit sur un widget ou l’icône de notification ouvre "
                                        L"le menu. Un clic gauche sur l’icône affiche ou masque tous les "
                                        L"widgets.\r\n\r\nWIDGETS ET "
                                        L"PARAMÈTRES\r\nVous pouvez ajouter, supprimer et dupliquer autant "
                                        L"d’horloges analogiques, numériques, calendriers et panneaux combinés que "
                                        L"nécessaire. Chaque widget possède "
                                        L"sa visibilité, son maintien au premier plan, sa langue, son fuseau et "
                                        L"son décalage au format [-]HH:mm:ss.ff. Les horloges analogiques ont "
                                        L"quatre tailles. Les horloges "
                                        L"numériques proposent secondes, zéro initial, police, couleurs, opacité "
                                        L"et fond transparent. Le calendrier propose numéros de semaine, dimanche "
                                        L"en premier et la langue du "
                                        L"widget.\r\n\r\nALARME\r\nL’application lit elle-même un fichier audio "
                                        L"une fois ou en boucle ; les autres fichiers ou commandes sont confiés à "
                                        L"Windows. Cliquez sur le cadran "
                                        L"ou l’affichage en alarme, choisissez Arrêter l’alarme ou appuyez sur "
                                        L"Échap pour arrêter l’indication et le son interne.\r\n\r\nRACCOURCIS ET "
                                        L"ENREGISTREMENT\r\nUn "
                                        L"double-clic bascule les secondes, F1 ouvre l’aide et B les paramètres. "
                                        L"Les positions et tous les réglages sont enregistrés dans le registre. Un "
                                        L"nouveau lancement active "
                                        L"l’instance existante.",
                                        L"CONTROLES\r\nArrastre un reloj o panel con el botón izquierdo. El "
                                        L"calendario independiente se arrastra por su zona libre; haga clic en un "
                                        L"día para cambiar la selección. El "
                                        L"botón derecho sobre un widget o el icono de notificación abre el menú. "
                                        L"El botón izquierdo sobre el icono muestra u oculta todos los "
                                        L"widgets.\r\n\r\nWIDGETS Y "
                                        L"CONFIGURACIÓN\r\nPuede añadir, quitar y duplicar cualquier número de "
                                        L"relojes analógicos, digitales, calendarios y paneles combinados. Cada "
                                        L"widget tiene visibilidad, primer "
                                        L"plano, idioma, zona horaria y desfase propios; use [-]HH:mm:ss.ff. Los "
                                        L"relojes analógicos tienen cuatro tamaños. Los digitales permiten "
                                        L"segundos, cero inicial, fuente, "
                                        L"colores, opacidad y fondo transparente. El calendario permite números de "
                                        L"semana, domingo primero y usa el idioma del widget.\r\n\r\nALARMA\r\nLa "
                                        L"aplicación reproduce "
                                        L"internamente un archivo de audio una vez o en bucle; los demás archivos "
                                        L"o comandos se entregan a Windows. Haga clic en la esfera o pantalla con "
                                        L"alarma, elija Detener alarma "
                                        L"o pulse Esc para detener la indicación y el audio interno.\r\n\r\nATAJOS "
                                        L"Y GUARDADO\r\nEl doble clic cambia los segundos, F1 abre la ayuda y B la "
                                        L"configuración. Las "
                                        L"posiciones y todos los ajustes se guardan en el registro. Otra ejecución "
                                        L"activa la instancia existente.",
                                        L"COMANDI\r\nTrascinare un orologio o pannello con il pulsante sinistro. "
                                        L"Il calendario autonomo si trascina dall’area libera; fare clic su un "
                                        L"giorno per cambiare la "
                                        L"selezione. Il pulsante destro su widget o icona di notifica apre il "
                                        L"menu. Il clic sinistro sull’icona mostra o nasconde tutti i "
                                        L"widget.\r\n\r\nWIDGET E IMPOSTAZIONI\r\nÈ "
                                        L"possibile aggiungere, rimuovere e duplicare un numero qualsiasi di "
                                        L"orologi analogici, digitali, calendari e pannelli combinati. Ogni widget "
                                        L"ha visibilità, primo piano, "
                                        L"lingua, fuso orario e offset propri; usare [-]HH:mm:ss.ff. Gli orologi "
                                        L"analogici hanno quattro dimensioni. Quelli digitali offrono secondi, "
                                        L"zero iniziale, carattere, "
                                        L"colori, opacità e sfondo trasparente. Il calendario offre numeri di "
                                        L"settimana, domenica per prima e usa la lingua del "
                                        L"widget.\r\n\r\nSVEGLIA\r\nL’applicazione riproduce "
                                        L"internamente un file audio una volta o in ciclo; gli altri file o "
                                        L"comandi vengono affidati a Windows. Fare clic sul quadrante o display in "
                                        L"allarme, scegliere Ferma sveglia "
                                        L"o premere Esc per fermare indicazione e audio "
                                        L"interno.\r\n\r\nSCORCIATOIE E SALVATAGGIO\r\nIl doppio clic commuta i "
                                        L"secondi, F1 apre la guida e B le impostazioni. Posizioni "
                                        L"e impostazioni vengono salvate nel registro. Un nuovo avvio attiva "
                                        L"l’istanza esistente.",
                                        L"STEROWANIE\r\nPrzeciągnij zegar lub panel lewym przyciskiem. Samodzielny "
                                        L"kalendarz przeciąga się za wolne miejsce; kliknięcie dnia zmienia wybór. "
                                        L"Prawy przycisk na widżecie "
                                        L"lub ikonie obszaru powiadomień otwiera menu. Lewy przycisk na ikonie "
                                        L"pokazuje albo ukrywa wszystkie widżety.\r\n\r\nWIDŻETY I "
                                        L"USTAWIENIA\r\nMożna dodać, usunąć i powielić "
                                        L"dowolną liczbę zegarów analogowych, cyfrowych, kalendarzy i paneli "
                                        L"łączonych. Każdy widżet ma własną widoczność, tryb na wierzchu, język, "
                                        L"strefę czasową i przesunięcie w "
                                        L"formacie [-]HH:mm:ss.ff. Zegary analogowe mają cztery rozmiary. Cyfrowe "
                                        L"oferują sekundy, zero wiodące, czcionkę, kolory, krycie i przezroczyste "
                                        L"tło. Kalendarz oferuje "
                                        L"numery tygodni, niedzielę jako pierwszy dzień i język "
                                        L"widżetu.\r\n\r\nALARM\r\nAplikacja sama odtwarza plik audio raz lub w "
                                        L"pętli; inne pliki i polecenia przekazuje "
                                        L"systemowi Windows. Kliknięcie alarmującej tarczy lub wyświetlacza, "
                                        L"polecenie Zatrzymaj alarm albo Esc zatrzymuje wskazanie i dźwięk "
                                        L"wewnętrzny.\r\n\r\nSKRÓTY I "
                                        L"ZAPIS\r\nDwuklik przełącza sekundy, F1 otwiera pomoc, a B ustawienia. "
                                        L"Pozycje i wszystkie ustawienia są zapisywane w rejestrze. Ponowne "
                                        L"uruchomienie aktywuje istniejącą "
                                        L"instancję.",
                                        L"OVLÁDANIE\r\nĽavým tlačidlom a ťahaním presuniete hodiny alebo panel. "
                                        L"Samostatný kalendár sa presúva za voľnú plochu; kliknutím na deň zmeníte "
                                        L"výber. Pravé tlačidlo na "
                                        L"widgete alebo ikone v oznamovacej oblasti otvorí ponuku. Ľavé kliknutie "
                                        L"na ikonu zobrazí alebo skryje všetky widgety.\r\n\r\nWIDGETY A "
                                        L"NASTAVENIA\r\nMožno pridať, odobrať a "
                                        L"duplikovať ľubovoľný počet ručičkových hodín, digitálnych hodín, "
                                        L"kalendárov a kombinovaných panelov. Každý widget má vlastnú viditeľnosť, "
                                        L"režim vždy navrchu, jazyk, časové "
                                        L"pásmo a offset vo formáte [-]HH:mm:ss.ff. Ručičkové hodiny majú štyri "
                                        L"veľkosti. Digitálne hodiny ponúkajú sekundy, úvodnú nulu, písmo, farby, "
                                        L"priehľadnosť a priehľadné "
                                        L"pozadie. Kalendár ponúka čísla týždňov, nedeľu ako prvý deň a používa "
                                        L"jazyk widgetu.\r\n\r\nBUDÍK\r\nAplikácia prehrá zvukový súbor sama raz "
                                        L"alebo dookola; ostatné súbory a "
                                        L"príkazy odovzdá systému Windows. Kliknutie na budík, príkaz Zastaviť "
                                        L"budík alebo Esc zastaví signalizáciu aj interný zvuk.\r\n\r\nSKRATKY A "
                                        L"UKLADANIE\r\nDvojklik prepne "
                                        L"sekundy, F1 otvorí pomoc a B nastavenia. Polohy a všetky nastavenia sa "
                                        L"ukladajú do registra. Ďalšie spustenie aktivuje existujúcu inštanciu." };

const wchar_t* HELP_ALARM_APPENDIX[LANG_COUNT] = { L"\r\n\r\nZADÁVÁNÍ ČASU A AKCE BUDÍKU\r\nČas budíku přijímá běžný tvar "
                                                  L"HH:mm s dvojtečkou, tečkou, mezerou či jiným oddělovačem; oddělovač lze "
                                                  L"také vynechat. Jedna nebo dvě číslice znamenají hodiny, tři nebo čtyři "
                                                  L"číslice hodiny a minuty, například 7, 12, 730, 0730 nebo 7:30. Po "
                                                  L"opuštění pole se čas sjednotí na HH:mm. Offset se zadává zprava od sekund: "
                                                  L"2 znamená 00:00:02.00, 230 i 0230 znamená 00:02:30.00 a 12345 znamená "
                                                  L"01:23:45.00. Při odděleném zápisu jsou dvě skupiny minuty a sekundy, tři "
                                                  L"skupiny hodiny, minuty a sekundy a čtvrtá skupina setiny; lze použít "
                                                  L"znaménko. Tlačítko Vyzkoušet rozbliká aktuální ciferník či rám panelu a "
                                                  L"zároveň asynchronně vyzkouší "
                                                  L"soubor, příkaz, zvuk a HTTP/HTTPS adresu vzdáleného skriptu. Zastavení "
                                                  L"testu nebo budíku ukončí i interně přehrávaný zvuk.",
                                                  L"\r\n\r\nTIME ENTRY AND ALARM ACTIONS\r\nAlarm time accepts HH:mm with a colon, "
                                                  L"period, space or another separator; the separator may also be omitted. One "
                                                  L"or two digits mean hours, while three or four digits mean hours and minutes, "
                                                  L"for example 7, 12, 730, 0730 or 7:30. The value is normalized to HH:mm after "
                                                  L"leaving the field. Offset entry starts from seconds on the right: 2 means "
                                                  L"00:00:02.00, 230 and 0230 mean 00:02:30.00, and 12345 means 01:23:45.00. "
                                                  L"With separators, two groups mean minutes and seconds, three mean hours, "
                                                  L"minutes and seconds, and a fourth group contains hundredths; a sign is "
                                                  L"accepted. Test flashes the selected clock face or panel frame and "
                                                  L"asynchronously tests the file, "
                                                  L"command, audio and HTTP/HTTPS remote-script URL. Stopping the test or "
                                                  L"alarm also stops audio played internally.",
                                                  L"\r\n\r\nZEITEINGABE UND WECKERAKTIONEN\r\nDie Weckzeit akzeptiert HH:mm mit "
                                                  L"Doppelpunkt, Punkt, Leerzeichen oder einem anderen Trennzeichen; das "
                                                  L"Trennzeichen kann entfallen. Eine oder zwei Ziffern bedeuten Stunden, drei "
                                                  L"oder vier Ziffern Stunden und Minuten, z. B. 7, 12, 730, 0730 oder 7:30. "
                                                  L"Beim Verlassen des Feldes wird HH:mm verwendet. Der Versatz wird von rechts "
                                                  L"ab den Sekunden eingegeben: 2 bedeutet 00:00:02.00, 230 und 0230 bedeuten "
                                                  L"00:02:30.00 und 12345 bedeutet 01:23:45.00. Mit Trennzeichen stehen zwei "
                                                  L"Gruppen für Minuten und Sekunden, drei für Stunden, Minuten und Sekunden "
                                                  L"und eine vierte für Hundertstel; ein Vorzeichen ist zulässig. Testen lässt "
                                                  L"Zifferblatt oder Panelrahmen "
                                                  L"blinken und prüft Datei, Befehl, "
                                                  L"Audio sowie eine HTTP/HTTPS-Adresse eines Remote-Skripts asynchron. Das "
                                                  L"Stoppen beendet auch intern abgespieltes Audio.",
                                                  L"\r\n\r\nSAISIE DE L’HEURE ET ACTIONS D’ALARME\r\nL’heure accepte HH:mm avec "
                                                  L"deux-points, point, espace ou un autre séparateur, qui peut aussi être omis. "
                                                  L"Un ou deux chiffres indiquent les heures, trois ou quatre les heures et les "
                                                  L"minutes, par exemple 7, 12, 730, 0730 ou 7:30. La valeur devient HH:mm à la "
                                                  L"sortie du champ. Le décalage se saisit de droite à partir des secondes : 2 "
                                                  L"signifie 00:00:02.00, 230 et 0230 signifient 00:02:30.00, et 12345 signifie "
                                                  L"01:23:45.00. Avec séparateurs, deux groupes représentent minutes et "
                                                  L"secondes, trois représentent heures, minutes et secondes, et un quatrième "
                                                  L"les centièmes ; un signe est accepté. Tester fait "
                                                  L"clignoter le cadran ou le cadre du panneau et teste de façon asynchrone "
                                                  L"fichier, commande, audio et "
                                                  L"URL HTTP/HTTPS du script distant. L’arrêt coupe aussi le son lu par "
                                                  L"l’application.",
                                                  L"\r\n\r\nENTRADA DE HORA Y ACCIONES DE ALARMA\r\nLa hora admite HH:mm con "
                                                  L"dos puntos, punto, espacio u otro separador, que también puede omitirse. Uno "
                                                  L"o dos dígitos indican horas; tres o cuatro, horas y minutos, por ejemplo 7, "
                                                  L"12, 730, 0730 o 7:30. Al salir del campo se normaliza a HH:mm. El desfase se "
                                                  L"introduce desde la derecha empezando por los segundos: 2 es 00:00:02.00, "
                                                  L"230 y 0230 son 00:02:30.00, y 12345 es 01:23:45.00. Con separadores, dos "
                                                  L"grupos son minutos y segundos, tres son horas, minutos y segundos, y un "
                                                  L"cuarto contiene centésimas; se admite signo. Probar hace parpadear "
                                                  L"la esfera o el marco del panel y prueba de forma asíncrona archivo, "
                                                  L"comando, audio y URL HTTP/HTTPS "
                                                  L"del script remoto. Detener también para el audio interno.",
                                                  L"\r\n\r\nIMMISSIONE DELL’ORA E AZIONI SVEGLIA\r\nL’ora accetta HH:mm con "
                                                  L"due punti, punto, spazio o un altro separatore, che può anche essere omesso. "
                                                  L"Una o due cifre indicano le ore; tre o quattro indicano ore e minuti, per "
                                                  L"esempio 7, 12, 730, 0730 o 7:30. Uscendo dal campo il valore diventa HH:mm. "
                                                  L"L’offset si inserisce da destra partendo dai secondi: 2 significa "
                                                  L"00:00:02.00, 230 e 0230 significano 00:02:30.00 e 12345 significa "
                                                  L"01:23:45.00. Con separatori, due gruppi sono minuti e secondi, tre sono ore, "
                                                  L"minuti e secondi e un quarto contiene i centesimi; è ammesso il segno. Prova "
                                                  L"fa lampeggiare il "
                                                  L"quadrante o il bordo del pannello e verifica in modo asincrono file, "
                                                  L"comando, audio e URL HTTP/HTTPS "
                                                  L"dello script remoto. L’arresto interrompe anche l’audio interno.",
                                                  L"\r\n\r\nWPROWADZANIE CZASU I AKCJE ALARMU\r\nCzas alarmu przyjmuje HH:mm z "
                                                  L"dwukropkiem, kropką, spacją lub innym separatorem; separator można pominąć. "
                                                  L"Jedna lub dwie cyfry oznaczają godziny, trzy lub cztery godziny i minuty, "
                                                  L"np. 7, 12, 730, 0730 albo 7:30. Po opuszczeniu pola wartość przyjmuje postać "
                                                  L"HH:mm. Przesunięcie wpisuje się od prawej, zaczynając od sekund: 2 oznacza "
                                                  L"00:00:02.00, 230 i 0230 oznaczają 00:02:30.00, a 12345 oznacza "
                                                  L"01:23:45.00. Przy separatorach dwie grupy oznaczają minuty i sekundy, trzy "
                                                  L"godziny, minuty i sekundy, a czwarta setne części; znak jest dozwolony. Test "
                                                  L"miga tarczą lub ramką panelu i asynchronicznie sprawdza plik, polecenie, "
                                                  L"dźwięk oraz adres "
                                                  L"HTTP/HTTPS "
                                                  L"zdalnego skryptu. Zatrzymanie wyłącza też dźwięk wewnętrzny.",
                                                  L"\r\n\r\nZADÁVANIE ČASU A AKCIE BUDÍKA\r\nČas budíka prijíma HH:mm s "
                                                  L"dvojbodkou, bodkou, medzerou alebo iným oddeľovačom; oddeľovač možno aj "
                                                  L"vynechať. Jedna alebo dve číslice znamenajú hodiny, tri alebo štyri hodiny "
                                                  L"a minúty, napríklad 7, 12, 730, 0730 alebo 7:30. Po opustení poľa sa "
                                                  L"hodnota upraví na HH:mm. Offset sa zadáva sprava od sekúnd: 2 znamená "
                                                  L"00:00:02.00, 230 aj 0230 znamená 00:02:30.00 a 12345 znamená 01:23:45.00. "
                                                  L"Pri oddelenom zápise sú dve skupiny minúty a sekundy, tri skupiny hodiny, "
                                                  L"minúty a sekundy a štvrtá skupina stotiny; možno použiť znamienko. Vyskúšať "
                                                  L"rozbliká ciferník alebo "
                                                  L"rám panela a asynchrónne otestuje súbor, príkaz, zvuk aj HTTP/HTTPS "
                                                  L"adresu vzdialeného skriptu. "
                                                  L"Zastavenie ukončí aj interne prehrávaný zvuk." };

const wchar_t* HELP_SELECTION_APPENDIX[LANG_COUNT] = { L"\r\n\r\nVÝBĚR A KOPÍROVÁNÍ DATA\r\nV seznamu widgetů označíte více "
                                                      L"položek pomocí Ctrl nebo Shift; pravá část je potom neaktivní a Odebrat "
                                                      L"pracuje se všemi označenými "
                                                      L"položkami. Dvojklik na položku krátce zvýrazní odpovídající widget na "
                                                      L"ploše. Kliknutí na den v kalendáři datum vybere a zároveň zkopíruje do "
                                                      L"schránky. Formát se volí "
                                                      L"samostatně pro každý kalendář v Nastavení nebo v jeho kontextové "
                                                      L"nabídce; slovní formáty používají jazyk widgetu.",
                                                      L"\r\n\r\nSELECTION AND DATE COPYING\r\nUse Ctrl or Shift to select "
                                                      L"several widgets; the right-hand editor is then disabled and Remove "
                                                      L"affects every selected item. "
                                                      L"Double-click an item to identify its widget briefly on the desktop. "
                                                      L"Clicking a calendar day selects it and copies it to the clipboard. Each "
                                                      L"calendar has its own format in "
                                                      L"Settings and its context menu; textual formats use the widget language.",
                                                      L"\r\n\r\nAUSWAHL UND DATUMSKOPIE\r\nMit Strg oder Umschalt wählen Sie "
                                                      L"mehrere Widgets; der rechte Editor wird deaktiviert und Entfernen gilt "
                                                      L"für alle ausgewählten Einträge. "
                                                      L"Doppelklick hebt das Widget kurz hervor. Ein Klick auf einen Kalendertag "
                                                      L"kopiert ihn in die Zwischenablage. Format und Sprache werden je Widget "
                                                      L"verwendet.",
                                                      L"\r\n\r\nSÉLECTION ET COPIE DE DATE\r\nCtrl ou Maj permet de sélectionner "
                                                      L"plusieurs widgets ; l’éditeur droit est alors désactivé et Supprimer "
                                                      L"agit sur toute la sélection. "
                                                      L"Un double-clic identifie brièvement le widget. Cliquer sur un jour le "
                                                      L"copie dans le presse-papiers selon le format et la langue du widget.",
                                                      L"\r\n\r\nSELECCIÓN Y COPIA DE FECHA\r\nUse Ctrl o Mayús para seleccionar "
                                                      L"varios widgets; el editor derecho se desactiva y Quitar afecta a toda la "
                                                      L"selección. Un doble clic "
                                                      L"identifica brevemente el widget. Al pulsar un día se copia al "
                                                      L"portapapeles con el formato y el idioma del widget.",
                                                      L"\r\n\r\nSELEZIONE E COPIA DELLA DATA\r\nCtrl o Maiusc seleziona più "
                                                      L"widget; l’editor destro viene disattivato e Rimuovi agisce su tutti gli "
                                                      L"elementi selezionati. Un doppio "
                                                      L"clic identifica brevemente il widget. Il clic su un giorno lo copia "
                                                      L"negli appunti con formato e lingua del widget.",
                                                      L"\r\n\r\nZAZNACZANIE I KOPIOWANIE DATY\r\nCtrl lub Shift zaznacza wiele "
                                                      L"widżetów; prawy edytor jest wtedy nieaktywny, a Usuń obejmuje wszystkie "
                                                      L"zaznaczone pozycje. Dwuklik "
                                                      L"krótko wskazuje widżet. Kliknięcie dnia kopiuje go do schowka w formacie "
                                                      L"i języku widżetu.",
                                                      L"\r\n\r\nVÝBER A KOPÍROVANIE DÁTUMU\r\nPomocou Ctrl alebo Shift označíte "
                                                      L"viac widgetov; pravá časť sa deaktivuje a Odobrať platí pre všetky "
                                                      L"označené položky. Dvojklik krátko "
                                                      L"zvýrazní widget. Kliknutie na deň ho skopíruje do schránky vo formáte a "
                                                      L"jazyku widgetu." };

const wchar_t* HELP_LAYOUT_APPENDIX[LANG_COUNT] = { L"\r\n\r\nROZLOŽENÍ WIDGETŮ\r\nPříkaz Zarovnat widgety do mřížky zachová "
                                                   L"přibližné ruční rozmístění, posune středy widgetů na nejbližší body "
                                                   L"mřížky a odstraní překrytí. V "
                                                   L"nabídce widgetu se upraví jeho monitor, z ikony všechny monitory "
                                                   L"samostatně. Opakování rozložení nemění. Dvojklik v Nastavení označí "
                                                   L"widget rychlým světlemodrým blikáním; "
                                                   L"budík bliká pomaleji červeně. Vypnutí Vždy navrchu pošle widget dozadu.",
                                                   L"\r\n\r\nWIDGET LAYOUT\r\nArrange widgets in a grid preserves the "
                                                   L"approximate manual layout, snaps widget centres to the nearest grid "
                                                   L"points and removes overlaps. A widget "
                                                   L"menu affects its monitor; the notification icon applies it to every "
                                                   L"monitor separately. Repeating the command keeps the layout stable. A "
                                                   L"Settings double-click identifies a "
                                                   L"widget with a fast light-blue flash; an alarm flashes more slowly in "
                                                   L"red. Turning off Always on top sends the widget to the back.",
                                                   L"\r\n\r\nWIDGET-ANORDNUNG\r\nWidgets im Raster anordnen behält die "
                                                   L"ungefähre manuelle Anordnung bei, richtet die Mittelpunkte am nächsten "
                                                   L"Rasterpunkt aus und beseitigt "
                                                   L"Überlappungen. Das Widget-Menü wirkt auf seinen Monitor, das Symbol auf "
                                                   L"alle Monitore einzeln. Wiederholen ändert die Anordnung nicht. Die "
                                                   L"Kennzeichnung blinkt schnell "
                                                   L"hellblau, der Alarm langsamer rot. Das Abschalten von Immer im "
                                                   L"Vordergrund schickt das Widget nach hinten.",
                                                   L"\r\n\r\nDISPOSITION\r\nAligner les widgets en grille conserve leur "
                                                   L"disposition manuelle approximative, aligne leurs centres sur la grille "
                                                   L"la plus proche et supprime les "
                                                   L"chevauchements. Le menu du widget agit sur son écran, l’icône sur chaque "
                                                   L"écran séparément. La commande répétée reste stable. L’identification "
                                                   L"clignote rapidement en bleu "
                                                   L"clair, l’alarme plus lentement en rouge. Désactiver Toujours visible "
                                                   L"envoie le widget à l’arrière-plan.",
                                                   L"\r\n\r\nDISTRIBUCIÓN\r\nAlinear widgets en cuadrícula conserva la "
                                                   L"distribución manual aproximada, ajusta sus centros a la cuadrícula más "
                                                   L"cercana y elimina superposiciones. "
                                                   L"El menú del widget actúa en su monitor; el icono, en cada monitor por "
                                                   L"separado. Repetir no cambia la distribución. La identificación parpadea "
                                                   L"rápido en azul claro y la "
                                                   L"alarma más despacio en rojo. Desactivar Siempre visible envía el widget "
                                                   L"al fondo.",
                                                   L"\r\n\r\nDISPOSIZIONE\r\nDisponi i widget in griglia conserva la "
                                                   L"disposizione manuale approssimativa, allinea i centri alla griglia più "
                                                   L"vicina ed elimina le sovrapposizioni. "
                                                   L"Il menu del widget agisce sul suo monitor, l’icona su ogni monitor "
                                                   L"separatamente. Ripetere il comando non cambia la disposizione. "
                                                   L"L’identificazione lampeggia rapidamente in "
                                                   L"azzurro, la sveglia più lentamente in rosso. Disattivando Sempre in "
                                                   L"primo piano il widget viene mandato dietro.",
                                                   L"\r\n\r\nUKŁAD WIDŻETÓW\r\nUłóż widżety w siatce zachowuje przybliżony "
                                                   L"układ ręczny, przyciąga środki widżetów do najbliższych punktów siatki i "
                                                   L"usuwa nakładanie. Menu "
                                                   L"widżetu działa na jego monitorze, a ikona na każdym monitorze osobno. "
                                                   L"Powtórzenie nie zmienia układu. Identyfikacja miga szybko "
                                                   L"jasnoniebiesko, alarm wolniej na czerwono. "
                                                   L"Wyłączenie Zawsze na wierzchu wysyła widżet do tyłu.",
                                                   L"\r\n\r\nROZLOŽENIE WIDGETOV\r\nZarovnať widgety do mriežky zachová "
                                                   L"približné ručné rozmiestnenie, pritiahne stredy widgetov k najbližším "
                                                   L"bodom mriežky a odstráni "
                                                   L"prekrývanie. Ponuka widgetu upraví jeho monitor, ikona každý monitor "
                                                   L"samostatne. Opakovanie rozloženie nemení. Identifikácia bliká rýchlo "
                                                   L"svetlomodro, budík pomalšie "
                                                   L"načerveno. Vypnutie Vždy navrchu pošle widget dozadu." };

const wchar_t* HELP_STORAGE_APPENDIX[LANG_COUNT] = { L"\r\n\r\nVZHLED A ÚLOŽIŠTĚ\r\nVelikost písma, odsazení, styl a šířka "
                                                    L"rámečku a neprůhlednost se nastavují posuvníky. Průhledné pozadí "
                                                    L"digitálních hodin ponechá viditelné jen "
                                                    L"číslice a rámeček. Nastavení lze exportovat do XML a importovat z XML "
                                                    L"přímo do stavu "
                                                    L"aplikace. Volba Ukládat do XML používá soubor "
                                                    L"%AppData%\\FortSoft\\CalClock\\settings.xml; po jeho úspěšném zápisu se "
                                                    L"celá větev nastavení aplikace odstraní z registru. Při "
                                                    L"spuštění se XML použije, pokud tento soubor existuje.",
                                                    L"\r\n\r\nAPPEARANCE AND STORAGE\r\nFont size, padding, border style and "
                                                    L"width, and opacity use sliders. A transparent digital-clock background "
                                                    L"leaves only the digits and "
                                                    L"border visible. Settings can be exported to XML and imported from XML "
                                                    L"directly into the application "
                                                    L"state. Save to XML uses %AppData%\\FortSoft\\CalClock\\settings.xml; "
                                                    L"after a successful write, the complete application settings branch is "
                                                    L"removed from the registry. XML is "
                                                    L"used at startup whenever this file exists.",
                                                    L"\r\n\r\nDARSTELLUNG UND SPEICHERUNG\r\nSchriftgröße, Innenabstand, "
                                                    L"Rahmen und Deckkraft werden mit Schiebereglern eingestellt. "
                                                    L"Einstellungen lassen sich als XML exportieren "
                                                    L"und direkt in den Anwendungszustand importieren. XML wird unter "
                                                    L"%AppData%\\FortSoft\\CalClock\\settings.xml gespeichert; nach "
                                                    L"erfolgreichem Schreiben wird der "
                                                    L"Anwendungszustand aus der Registrierung entfernt.",
                                                    L"\r\n\r\nAPPARENCE ET STOCKAGE\r\nLa taille de police, la marge, la "
                                                    L"bordure et l’opacité utilisent des curseurs. Les paramètres peuvent être "
                                                    L"exportés en XML et importés "
                                                    L"directement dans l’état de l’application. Le stockage XML utilise "
                                                    L"%AppData%\\FortSoft\\CalClock\\settings.xml et retire ensuite l’état de "
                                                    L"l’application du registre.",
                                                    L"\r\n\r\nAPARIENCIA Y ALMACENAMIENTO\r\nEl tamaño de fuente, relleno, "
                                                    L"borde y opacidad se ajustan con deslizadores. La configuración se "
                                                    L"exporta a XML y se importa "
                                                    L"directamente al estado de la aplicación. El almacenamiento XML usa "
                                                    L"%AppData%\\FortSoft\\CalClock\\settings.xml y después elimina del "
                                                    L"registro el estado de la aplicación.",
                                                    L"\r\n\r\nASPETTO E ARCHIVIAZIONE\r\nDimensione carattere, margine, bordo "
                                                    L"e opacità usano cursori. Le impostazioni possono essere esportate in XML "
                                                    L"e importate direttamente "
                                                    L"nello stato dell’applicazione. Il salvataggio XML usa "
                                                    L"%AppData%\\FortSoft\\CalClock\\settings.xml e poi rimuove lo stato "
                                                    L"dell’applicazione dal registro.",
                                                    L"\r\n\r\nWYGLĄD I ZAPIS\r\nRozmiar czcionki, odstęp, ramka i krycie są "
                                                    L"ustawiane suwakami. Ustawienia można eksportować do XML i importować "
                                                    L"bezpośrednio do stanu aplikacji. "
                                                    L"Zapis XML używa %AppData%\\FortSoft\\CalClock\\settings.xml, po czym "
                                                    L"usuwa stan aplikacji z rejestru.",
                                                    L"\r\n\r\nVZHĽAD A UKLADANIE\r\nVeľkosť písma, odsadenie, rámček a "
                                                    L"nepriehľadnosť sa nastavujú posuvníkmi. Nastavenia možno exportovať do "
                                                    L"XML a importovať priamo do stavu "
                                                    L"aplikácie. XML sa ukladá do %AppData%\\FortSoft\\CalClock\\settings.xml; "
                                                    L"po úspešnom zápise sa stav aplikácie odstráni z registra." };

const wchar_t* HELP_TIME_APPENDIX[LANG_COUNT] = { L"\r\n\r\nZDROJ ČASU\r\nNa kartě Čas lze pro celou aplikaci vybrat "
                                                 L"systémový čas Windows nebo čas ze zadaných serverů NTP. NTP koriguje "
                                                 L"pouze čas zobrazovaný v CalClock; "
                                                 L"systémové hodiny Windows se nikdy nemění. Dokud nebyl získán platný "
                                                 L"údaj, používá se systémový čas. Po pozdějším výpadku zůstane poslední "
                                                 L"korekce jen v paměti procesu a "
                                                 L"synchronizace se opakuje. NTP je výchozí. Automatická sada volí podle "
                                                 L"systémové oblasti české a slovenské servery, PTB pro Evropu nebo "
                                                 L"celosvětový fond. Více měření se "
                                                 L"filtruje podle síťového zpoždění a odlehlých odpovědí.",
                                                 L"\r\n\r\nTIME SOURCE\r\nThe Time tab selects Windows system time or the "
                                                 L"configured NTP servers for the whole application. NTP corrects only the "
                                                 L"time displayed by CalClock; "
                                                 L"the Windows clock is never changed. System time is used until the first "
                                                 L"valid reply. After a later outage, the last correction remains in "
                                                 L"process memory and synchronization "
                                                 L"is retried. NTP is the default. The automatic set chooses Czech and "
                                                 L"Slovak servers, PTB for Europe, or the global pool according to the "
                                                 L"system region. Multiple measurements "
                                                 L"are filtered by network delay and outlying replies.",
                                                 L"\r\n\r\nZEITQUELLE\r\nAuf der Registerkarte Zeit wird für die gesamte "
                                                 L"Anwendung die Windows-Systemzeit oder die Zeit der eingestellten "
                                                 L"NTP-Server gewählt. NTP korrigiert "
                                                 L"nur die in CalClock angezeigte Zeit; die Windows-Uhr wird nie geändert. "
                                                 L"Bis zur ersten gültigen Antwort wird die Systemzeit verwendet. Bei einem "
                                                 L"späteren Ausfall bleibt die "
                                                 L"letzte Korrektur nur im Prozessspeicher erhalten und die "
                                                 L"Synchronisierung wird wiederholt. NTP ist voreingestellt. Die "
                                                 L"automatische Gruppe wählt nach der Systemregion die "
                                                 L"tschechisch-slowakischen Server, PTB für Europa oder den globalen Pool. "
                                                 L"Mehrere Messungen werden nach Netzverzögerung und Ausreißern gefiltert.",
                                                 L"\r\n\r\nSOURCE DE L’HEURE\r\nL’onglet Heure sélectionne l’heure système "
                                                 L"Windows ou les serveurs NTP configurés pour toute l’application. NTP "
                                                 L"corrige uniquement l’heure "
                                                 L"affichée par CalClock ; l’horloge Windows n’est jamais modifiée. L’heure "
                                                 L"système est utilisée jusqu’à la première réponse valide. Après une panne "
                                                 L"ultérieure, la dernière "
                                                 L"correction reste uniquement en mémoire du processus et la "
                                                 L"synchronisation est retentée. NTP est la valeur par défaut. Le jeu "
                                                 L"automatique choisit les serveurs tchèques et "
                                                 L"slovaques, PTB pour l’Europe ou le pool mondial selon la région système. "
                                                 L"Plusieurs mesures sont filtrées selon le délai réseau et les réponses "
                                                 L"aberrantes.",
                                                 L"\r\n\r\nORIGEN DE HORA\r\nLa pestaña Hora selecciona la hora del sistema "
                                                 L"Windows o los servidores NTP configurados para toda la aplicación. NTP "
                                                 L"solo corrige la hora "
                                                 L"mostrada por CalClock; el reloj de Windows nunca se modifica. Se usa la "
                                                 L"hora del sistema hasta la primera respuesta válida. Tras una "
                                                 L"interrupción posterior, la última "
                                                 L"corrección permanece solo en la memoria del proceso y se reintenta la "
                                                 L"sincronización. NTP es el valor predeterminado. El conjunto automático "
                                                 L"elige servidores checos y "
                                                 L"eslovacos, PTB para Europa o el grupo mundial según la región del "
                                                 L"sistema. Varias mediciones se filtran por retardo de red y respuestas "
                                                 L"atípicas.",
                                                 L"\r\n\r\nORIGINE DELL’ORA\r\nLa scheda Ora seleziona l’ora di sistema "
                                                 L"Windows o i server NTP configurati per l’intera applicazione. NTP "
                                                 L"corregge solo l’ora visualizzata da "
                                                 L"CalClock; l’orologio di Windows non viene mai modificato. L’ora di "
                                                 L"sistema viene usata fino alla prima risposta valida. Dopo una successiva "
                                                 L"interruzione, l’ultima "
                                                 L"correzione rimane solo nella memoria del processo e la sincronizzazione "
                                                 L"viene ripetuta. NTP è l’impostazione predefinita. Il gruppo automatico "
                                                 L"sceglie i server cechi e "
                                                 L"slovacchi, PTB per l’Europa o il pool globale in base all’area di "
                                                 L"sistema. Più misurazioni vengono filtrate in base al ritardo di rete e "
                                                 L"alle risposte anomale.",
                                                 L"\r\n\r\nŹRÓDŁO CZASU\r\nKarta Czas wybiera dla całej aplikacji czas "
                                                 L"systemowy Windows albo skonfigurowane serwery NTP. NTP koryguje "
                                                 L"wyłącznie czas wyświetlany przez "
                                                 L"CalClock; zegar Windows nigdy nie jest zmieniany. Do pierwszej "
                                                 L"prawidłowej odpowiedzi używany jest czas systemowy. Po późniejszej "
                                                 L"awarii ostatnia korekta pozostaje "
                                                 L"wyłącznie w pamięci procesu, a synchronizacja jest ponawiana. NTP jest "
                                                 L"ustawieniem domyślnym. Zestaw automatyczny wybiera według regionu "
                                                 L"systemu serwery czeskie i "
                                                 L"słowackie, PTB dla Europy albo pulę globalną. Wiele pomiarów jest "
                                                 L"filtrowanych według opóźnienia sieci i wartości odstających.",
                                                 L"\r\n\r\nZDROJ ČASU\r\nNa karte Čas možno pre celú aplikáciu vybrať "
                                                 L"systémový čas Windows alebo čas zo zadaných serverov NTP. NTP koriguje "
                                                 L"iba čas zobrazený v CalClock; "
                                                 L"systémové hodiny Windows sa nikdy nemenia. Do prvej platnej odpovede sa "
                                                 L"používa systémový čas. Po neskoršom výpadku zostane posledná korekcia "
                                                 L"iba v pamäti procesu a "
                                                 L"synchronizácia sa zopakuje. NTP je predvolené. Automatická sada vyberie "
                                                 L"podľa systémovej oblasti české a slovenské servery, PTB pre Európu alebo "
                                                 L"celosvetový fond. Viaceré "
                                                 L"merania sa filtrujú podľa sieťového oneskorenia a odľahlých odpovedí." };

const wchar_t* HELP_FULLSCREEN_APPENDIX[LANG_COUNT] = {
    L"\r\n\r\nHODINY NA MONITORU\r\nDigitální hodiny mohou vyplnit jeden či více monitorů. Volitelně zatemní ostatní monitory. Velikost písma se udává procentem výšky "
    L"monitoru a malý náhled zachovává jeho poměr stran. Náhled lze přetáhnout myší a jeho poloha se uloží. Klávesa Esc hodiny ihned skryje a zatemnění odstraní.",
    L"\r\n\r\nMONITOR CLOCK\r\nThe digital clock can fill one or more monitors and can optionally black out the others. Font size is a percentage of monitor height, and "
    L"the small preview keeps its aspect ratio. The preview can be dragged and its position is saved. Esc immediately hides the clock and removes blackouts.",
    L"\r\n\r\nMONITORUHR\r\nDie Digitaluhr kann einen oder mehrere Monitore ausfüllen und die übrigen optional abdunkeln. Die Schriftgröße wird als Prozentsatz der "
    L"Monitorhöhe angegeben; die kleine Vorschau behält sein Seitenverhältnis. Sie kann verschoben werden; ihre Position wird gespeichert. Esc blendet Uhr und Abdunklung sofort aus.",
    L"\r\n\r\nHORLOGE SUR MONITEUR\r\nL’horloge numérique peut remplir un ou plusieurs moniteurs et assombrir les autres en option. La taille de police est un pourcentage de "
    L"la hauteur du moniteur et l’aperçu conserve ses proportions. Il peut être déplacé et sa position est enregistrée. Échap masque immédiatement l’horloge et l’assombrissement.",
    L"\r\n\r\nRELOJ DE MONITOR\r\nEl reloj digital puede ocupar uno o varios monitores y oscurecer opcionalmente los demás. El tamaño de fuente es un porcentaje de la altura "
    L"del monitor y la vista previa mantiene su proporción. La vista previa se puede mover y su posición se guarda. Esc oculta inmediatamente el reloj y el oscurecimiento.",
    L"\r\n\r\nOROLOGIO SU MONITOR\r\nL’orologio digitale può occupare uno o più monitor e oscurare facoltativamente gli altri. La dimensione del carattere è una percentuale "
    L"dell’altezza del monitor e l’anteprima mantiene le proporzioni. L’anteprima può essere spostata e la posizione viene salvata. Esc nasconde subito l’orologio e l’oscuramento.",
    L"\r\n\r\nZEGAR NA MONITORZE\r\nZegar cyfrowy może zająć jeden lub kilka monitorów i opcjonalnie wygasić pozostałe. Rozmiar czcionki jest procentem wysokości monitora, a "
    L"mały podgląd zachowuje jego proporcje. Podgląd można przeciągać, a jego położenie jest zapisywane. Esc natychmiast ukrywa zegar i usuwa wygaszenie.",
    L"\r\n\r\nHODINY NA MONITORE\r\nDigitálne hodiny môžu vyplniť jeden alebo viac monitorov a voliteľne stmaviť ostatné. Veľkosť písma je percentom výšky monitora a malý "
    L"náhľad zachováva jeho pomer strán. Náhľad možno presúvať myšou a jeho poloha sa uloží. Esc hodiny ihneď skryje a stmavenie odstráni." };

const wchar_t* ABOUT_TEXT[LANG_COUNT] = { L"Hodiny a kalendáře\r\n\r\nNativní Win32 aplikace pro libovolný počet "
                                         L"samostatně nastavených plovoucích hodin a kalendářů. Ručičkový ciferník "
                                         L"používá systémový ClockWndMain.",
                                         L"Clocks and calendars\r\n\r\nA native Win32 application for any number of "
                                         L"independently configured floating clocks and calendars. The analog face "
                                         L"uses the system "
                                         L"ClockWndMain.",
                                         L"Uhren und Kalender\r\n\r\nNative Win32-Anwendung für beliebig viele "
                                         L"unabhängig konfigurierte schwebende Uhren und Kalender. Das Zifferblatt "
                                         L"verwendet ClockWndMain.",
                                         L"Horloges et calendriers\r\n\r\nApplication Win32 native pour plusieurs "
                                         L"horloges et calendriers flottants configurés séparément. Le cadran "
                                         L"utilise ClockWndMain.",
                                         L"Relojes y calendarios\r\n\r\nAplicación Win32 nativa para varios relojes "
                                         L"y calendarios flotantes configurados por separado. La esfera usa "
                                         L"ClockWndMain.",
                                         L"Orologi e calendari\r\n\r\nApplicazione Win32 nativa per più orologi e "
                                         L"calendari mobili configurati separatamente. Il quadrante usa "
                                         L"ClockWndMain.",
                                         L"Zegary i kalendarze\r\n\r\nNatywna aplikacja Win32 obsługująca wiele "
                                         L"niezależnie skonfigurowanych zegarów i kalendarzy. Tarcza używa "
                                         L"ClockWndMain.",
                                         L"Hodiny a kalendáre\r\n\r\nNatívna aplikácia Win32 pre ľubovoľný počet "
                                         L"samostatne nastavených plávajúcich hodín a kalendárov. Ciferník používa "
                                         L"ClockWndMain." };

static std::wstring LoadLicenseText() {
    HRSRC resource = FindResourceW(hInstance, MAKEINTRESOURCEW(IDR_LICENSE), RT_RCDATA);
    if (resource == nullptr) {
        return std::wstring();
    }
    HGLOBAL loadedResource = LoadResource(hInstance, resource);
    if (loadedResource == nullptr) {
        return std::wstring();
    }
    DWORD byteCount = SizeofResource(hInstance, resource);
    const char* bytes = static_cast<const char*>(LockResource(loadedResource));
    if (bytes == nullptr || byteCount == 0 || byteCount > static_cast<DWORD>(INT_MAX)) {
        return std::wstring();
    }
    int characterCount = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, bytes, static_cast<int>(byteCount), nullptr, 0);
    if (characterCount <= 0) {
        return std::wstring();
    }
    std::wstring decoded(characterCount, L'\0');
    if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, bytes, static_cast<int>(byteCount), decoded.data(), characterCount) != characterCount) {
        return std::wstring();
    }
    std::wstring result;
    result.reserve(decoded.size() + 32);
    for (size_t index = 0; index < decoded.size(); index++) {
        if (decoded[index] == L'\n' && (index == 0 || decoded[index - 1] != L'\r')) {
            result += L'\r';
        }
        result += decoded[index];
    }
    return result;
}

static std::wstring BuildAboutText() {
    std::wstring result = ABOUT_TEXT[appLanguage];
    std::wstring license = LoadLicenseText();
    if (!license.empty()) {
        result += L"\r\n\r\n";
        result += license;
    }
    return result;
}

static void RefreshInformationWindows() {
    if (hHelp != nullptr && IsWindow(hHelp)) {
        SetWindowTextW(hHelp, T(TXT_HELP));
        std::wstring helpText = std::wstring(HELP_TEXT[appLanguage]) + HELP_ALARM_APPENDIX[appLanguage] + HELP_SELECTION_APPENDIX[appLanguage] + HELP_LAYOUT_APPENDIX[appLanguage] + HELP_STORAGE_APPENDIX[appLanguage] + HELP_TIME_APPENDIX[appLanguage] + HELP_FULLSCREEN_APPENDIX[appLanguage];
        SetDlgItemTextW(hHelp, ID_INFO_TEXT, helpText.c_str());
        SetDlgItemTextW(hHelp, ID_INFO_CLOSE, Mnemonic(TXT_CLOSE).c_str());
    }
    if (hAbout != nullptr && IsWindow(hAbout)) {
        SetWindowTextW(hAbout, T(TXT_ABOUT));
        std::wstring aboutText = BuildAboutText();
        SetDlgItemTextW(hAbout, ID_INFO_TEXT, aboutText.c_str());
        SetDlgItemTextW(hAbout, ID_INFO_CLOSE, Mnemonic(TXT_CLOSE).c_str());
    }
}

static void ShowInformationWindow(bool help) {
    HWND* target = help ? &hHelp : &hAbout;
    if (*target != nullptr && IsWindow(*target)) {
        SetForegroundWindowEx(*target);
        return;
    }
    int* x = help ? &helpX : &aboutX;
    int* y = help ? &helpY : &aboutY;
    ClampFormPosition(x, y, 660, 500);
    *target = CreateWindowExW(WS_EX_TOPMOST, CLASS_NAME, help ? T(TXT_HELP) : T(TXT_ABOUT), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, *x, *y, 660, 500, nullptr,
                              nullptr, hInstance, nullptr);
    std::wstring body = help ? std::wstring(HELP_TEXT[appLanguage]) + HELP_ALARM_APPENDIX[appLanguage] + HELP_SELECTION_APPENDIX[appLanguage] + HELP_LAYOUT_APPENDIX[appLanguage] + HELP_STORAGE_APPENDIX[appLanguage] + HELP_TIME_APPENDIX[appLanguage] + HELP_FULLSCREEN_APPENDIX[appLanguage] : BuildAboutText();
    DWORD textStyle = WS_TABSTOP | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL;
    HWND text = AddControl(WS_EX_CLIENTEDGE, L"EDIT", body.c_str(), textStyle, 18, 18, 610, 385, *target, ID_INFO_TEXT);
    if (!help && hAboutFont == nullptr) {
        hAboutFont = CreateAboutFont();
    }
    SendMessageW(text, EM_SETSEL, 0, 0);
    AddControl(0, L"BUTTON", Mnemonic(TXT_CLOSE).c_str(), WS_TABSTOP | BS_DEFPUSHBUTTON, 528, 420, 100, 28, *target, ID_INFO_CLOSE);
    ApplyUiStyle(*target);
    ShowWindow(*target, SW_SHOW);
    SetForegroundWindowEx(*target);
}

static void HandleSettingsCommand(int id, int notification) {
    if (id == ID_LIST_WIDGETS && notification == LBN_SELCHANGE) {
        if (!SaveControlsToDraft(true)) {
            SelectOnlyWidgetIndex(selectedDraftIndex);
            return;
        }
        if (settingsPreviewStopEvent != nullptr || settingsVisualPreviewActive) {
            StopSettingsPreview();
        }
        int caretIndex = static_cast<int>(SendMessageW(hWidgetList, LB_GETCARETINDEX, 0, 0));
        if (caretIndex >= 0 && caretIndex < static_cast<int>(settingsDraft.size())) {
            selectedDraftIndex = caretIndex;
        }
        LoadDraftIntoControls();
        UpdateSettingsSelectionState();
    } else if (id == ID_LIST_WIDGETS && notification == LBN_DBLCLK) {
        if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
            IdentifyWidget(FindWidgetById(settingsDraft[selectedDraftIndex].id));
        }
    } else if (id == ID_TYPE && notification == CBN_SELCHANGE) {
        if (settingsPreviewStopEvent != nullptr || settingsVisualPreviewActive) {
            StopSettingsPreview();
        }
        int type = static_cast<int>(SendMessageW(hTypeCombo, CB_GETCURSEL, 0, 0));
        if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size()) && type >= 0 && type < WIDGET_TYPE_COUNT) {
            WidgetConfig& config = settingsDraft[selectedDraftIndex];
            WidgetType previousType = config.type;
            std::wstring editedName = GetControlText(hNameEdit);
            bool defaultName = editedName.empty() || editedName == TypeName(previousType);
            if (!SaveControlsToDraft(true)) {
                SendMessageW(hTypeCombo, CB_SETCURSEL, previousType, 0);
                return;
            }
            WidgetType selectedType = static_cast<WidgetType>(type);
            config.type = selectedType;
            if (selectedType != previousType) {
                if (defaultName) {
                    config.name = TypeName(selectedType);
                }
                Widget* widget = FindWidgetById(config.id);
                if (widget != nullptr) {
                    WidgetConfig preview = widget->config;
                    preview.type = selectedType;
                    preview.name = config.name;
                    preview.showSeconds = config.showSeconds;
                    preview.showUtc = config.showUtc;
                    preview.showUtcText = config.showUtcText;
                    preview.language = config.language;
                    preview.timeZoneKey = config.timeZoneKey;
                    preview.monitorDevices = config.monitorDevices;
                    preview.blackoutOtherMonitors = config.blackoutOtherMonitors;
                    preview.offsetMilliseconds = config.offsetMilliseconds;
                    CopyWidgetAppearance(&preview, config);
                    if (std::find(settingsAppearancePreviewIds.begin(), settingsAppearancePreviewIds.end(), config.id) == settingsAppearancePreviewIds.end()) {
                        settingsAppearancePreviewIds.push_back(config.id);
                    }
                    settingsAppearancePreviewActive = true;
                    RecreateWidgetForConfiguration(widget, preview);
                }
                RefreshWidgetList();
                LoadDraftIntoControls();
                UpdateSettingsSelectionState();
                return;
            }
        }
        UpdateSettingControlAvailability();
    } else if (id == ID_UTC && notification == BN_CLICKED) {
        bool digital = selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size()) &&
            (settingsDraft[selectedDraftIndex].type == WIDGET_DIGITAL || settingsDraft[selectedDraftIndex].type == WIDGET_FULLSCREEN);
        EnableWindow(hUtcTextCheck, digital && GetCheck(hUtcCheck));
    } else if (id == ID_ALARM_TIME && notification == EN_CHANGE && GetFocus() == hAlarmTimeEdit) {
        SetCheck(hAlarmEnabledCheck, true);
    } else if (id == ID_ALARM_TIME && notification == EN_KILLFOCUS) {
        int hour = 0;
        int minute = 0;
        std::wstring text = GetControlText(hAlarmTimeEdit);
        if (ParseAlarmTime(text.c_str(), &hour, &minute)) {
            wchar_t formatted[16] = {};
            swprintf_s(formatted, L"%02d:%02d", hour, minute);
            SetWindowTextW(hAlarmTimeEdit, formatted);
        }
    } else if (id == ID_OFFSET && notification == EN_KILLFOCUS) {
        LONGLONG offset = 0;
        std::wstring text = GetControlText(hOffsetEdit);
        if (ParseOffset(text.c_str(), &offset)) {
            SetWindowTextW(hOffsetEdit, FormatOffset(offset).c_str());
        }
    } else if (id == ID_REMOTE_SCRIPT && notification == BN_CLICKED) {
        EnableWindow(hRemoteScriptEdit, GetCheck(hRemoteScriptCheck));
        if (GetCheck(hRemoteScriptCheck)) {
            SetFocus(hRemoteScriptEdit);
        }
    } else if (id == ID_SIZE && notification == CBN_SELCHANGE) {
        PreviewSelectedWidgetAppearance(true);
    } else if (id == ID_WIDGET_ANTIALIAS && notification == CBN_SELCHANGE) {
        PreviewSelectedWidgetAppearance(false);
    } else if (id == ID_WIDGET_LANGUAGE && notification == CBN_SELCHANGE) {
        int language = static_cast<int>(SendMessageW(hWidgetLanguageCombo, CB_GETCURSEL, 0, 0));
        if (selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size()) && language >= 0 && language < LANG_COUNT) {
            WidgetConfig& config = settingsDraft[selectedDraftIndex];
            int dateFormat = static_cast<int>(SendMessageW(hDateFormatCombo, CB_GETCURSEL, 0, 0));
            if (dateFormat >= 0 && dateFormat < DATE_FORMAT_COUNT) {
                config.dateCopyFormat = dateFormat;
            }
            config.language = static_cast<AppLanguage>(language);
            FillDateFormatCombo(config);
        }
    } else if (id == ID_TIME_SOURCE && notification == CBN_SELCHANGE) {
        UpdateNtpSettingsControls();
    } else if (id == ID_NTP_PRESET && notification == CBN_SELCHANGE) {
        ApplySelectedNtpPresetToEdit();
        UpdateNtpSettingsControls();
    } else if (id == ID_NTP_SERVERS && notification == EN_CHANGE) {
        if (!updatingNtpPresetControls && hNtpPresetCombo != nullptr) {
            int selectedPreset = static_cast<int>(SendMessageW(hNtpPresetCombo, CB_GETCURSEL, 0, 0));
            if (selectedPreset >= 0 && selectedPreset < NTP_PRESET_CUSTOM) {
                std::wstring expected = NtpServersForPreset(selectedPreset);
                if (GetControlText(hNtpServersEdit) != expected) {
                    SendMessageW(hNtpPresetCombo, CB_SETCURSEL, NTP_PRESET_CUSTOM, 0);
                }
            }
        }
        UpdateNtpSettingsControls();
    } else if (id == ID_NTP_SYNC && notification == BN_CLICKED) {
        StartNtpSynchronization(true);
        UpdateNtpSettingsControls();
    } else if (id == ID_ADD) {
        if (!SaveControlsToDraft(true)) {
            return;
        }
        int type = static_cast<int>(SendMessageW(hAddType, CB_GETCURSEL, 0, 0));
        if (type < 0 || type >= WIDGET_TYPE_COUNT) {
            type = WIDGET_ANALOG;
        }
        WidgetConfig config = DefaultConfig(static_cast<WidgetType>(type), static_cast<int>(settingsDraft.size()));
        int selectedAppFontAntialiasing = static_cast<int>(SendMessageW(hAppAntialiasCombo, CB_GETCURSEL, 0, 0));
        config.fontAntialiasing = std::clamp(selectedAppFontAntialiasing, 0, FONT_ANTIALIAS_COUNT - 1);
        settingsDraft.push_back(config);
        selectedDraftIndex = static_cast<int>(settingsDraft.size()) - 1;
        RefreshWidgetList(false);
        LoadDraftIntoControls();
    } else if (id == ID_DUPLICATE) {
        if (!SaveControlsToDraft(true) || selectedDraftIndex < 0 || selectedDraftIndex >= static_cast<int>(settingsDraft.size())) {
            return;
        }
        WidgetConfig copy = settingsDraft[selectedDraftIndex];
        copy.id = nextWidgetId++;
        copy.x += 28;
        copy.y += 28;
        settingsDraft.insert(settingsDraft.begin() + selectedDraftIndex + 1, copy);
        selectedDraftIndex++;
        RefreshWidgetList(false);
        LoadDraftIntoControls();
    } else if (id == ID_REMOVE) {
        if (!SaveControlsToDraft(true)) {
            return;
        }
        std::vector<int> selected = GetSelectedWidgetIndices();
        if (selected.empty() && selectedDraftIndex >= 0) {
            selected.push_back(selectedDraftIndex);
        }
        if (selected.empty()) {
            return;
        }
        if (selected.size() >= settingsDraft.size()) {
            MessageBoxW(hSettings, T(TXT_AT_LEAST_ONE), T(TXT_SETTINGS), MB_OK | MB_ICONINFORMATION);
            return;
        }
        if (MessageBoxW(hSettings, T(TXT_DELETE_CONFIRM), T(TXT_SETTINGS), MB_YESNO | MB_ICONQUESTION) != IDYES) {
            return;
        }
        std::sort(selected.begin(), selected.end());
        int firstRemoved = selected.front();
        for (std::vector<int>::reverse_iterator index = selected.rbegin(); index != selected.rend(); ++index) {
            if (*index >= 0 && *index < static_cast<int>(settingsDraft.size())) {
                settingsDraft.erase(settingsDraft.begin() + *index);
            }
        }
        selectedDraftIndex = std::min(firstRemoved, static_cast<int>(settingsDraft.size()) - 1);
        RefreshWidgetList(false);
        LoadDraftIntoControls();
    } else if (id == ID_TEXT_COLOR) {
        if (ChooseButtonColor(hTextColorButton)) {
            PreviewSelectedWidgetAppearance(false);
        }
    } else if (id == ID_BACKGROUND_COLOR) {
        if (ChooseButtonColor(hBackgroundColorButton)) {
            PreviewSelectedWidgetAppearance(false);
        }
    } else if (id == ID_ALARM_TEXT_COLOR) {
        if (ChooseButtonColor(hAlarmTextColorButton)) {
            PreviewSelectedWidgetAppearance(false);
        }
    } else if (id == ID_ALARM_BACKGROUND_COLOR) {
        if (ChooseButtonColor(hAlarmBackgroundColorButton)) {
            PreviewSelectedWidgetAppearance(false);
        }
    } else if (id == ID_FONT) {
        ChooseWidgetFont();
    } else if (id == ID_PANEL_TOP_FONT && selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        ChoosePanelFont(&settingsDraft[selectedDraftIndex].panelTopFont);
    } else if (id == ID_PANEL_TIME_FONT && selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        ChoosePanelFont(&settingsDraft[selectedDraftIndex].panelTimeFont);
    } else if (id == ID_PANEL_BOTTOM_FONT && selectedDraftIndex >= 0 && selectedDraftIndex < static_cast<int>(settingsDraft.size())) {
        ChoosePanelFont(&settingsDraft[selectedDraftIndex].panelBottomFont);
    } else if (id == ID_APP_FONT) {
        ChooseApplicationFont();
    } else if (id == ID_APP_FONT_DEFAULT) {
        settingsAppFontFace.clear();
        settingsAppFontDialogSize = 90;
        settingsAppFontWeight = FW_NORMAL;
        settingsAppFontItalic = false;
        UpdateApplicationFontButtons();
        ApplyApplicationFontPreview();
    } else if (id == ID_VISUAL_STYLES && notification == BN_CLICKED) {
        UpdateSettingControlAvailability();
    } else if (id == ID_DEFAULT_APPEARANCE) {
        ResetWidgetAppearance();
    } else if ((id == ID_LEADING_ZERO || id == ID_TRANSPARENT_BG || id == ID_WIDGET_DISABLE_THEMES) && notification == BN_CLICKED) {
        if (id == ID_WIDGET_DISABLE_THEMES) {
            UpdateSettingControlAvailability();
        }
        PreviewSelectedWidgetAppearance(false);
    } else if ((id == ID_WEEK_NUMBERS || id == ID_SUNDAY_FIRST) && notification == BN_CLICKED) {
        PreviewSelectedWidgetAppearance(true);
    } else if (id == ID_BROWSE) {
        BrowseForCommand();
    } else if (id == ID_TEST_COMMAND) {
        TestSettingsCommand();
    } else if (id == ID_IMPORT_SETTINGS) {
        ImportSettings();
    } else if (id == ID_EXPORT_SETTINGS) {
        ExportSettings();
    } else if (id == ID_SAVE || id == ID_APPLY) {
        if (!SaveControlsToDraft(true)) {
            return;
        }
        bool widgetListChanged = settingsDraft.size() != widgets.size();
        if (!widgetListChanged) {
            for (size_t index = 0; index < settingsDraft.size(); index++) {
                if (settingsDraft[index].id != widgets[index]->config.id || settingsDraft[index].name != widgets[index]->config.name) {
                    widgetListChanged = true;
                    break;
                }
            }
        }
        AppLanguage previousLanguage = appLanguage;
        ApplySettingsDraft();
        if (id == ID_SAVE) {
            CloseSettingsWindow();
        } else {
            settingsDraft.clear();
            for (size_t index = 0; index < widgets.size(); index++) {
                settingsDraft.push_back(widgets[index]->config);
            }
            settingsAppearanceOriginals = settingsDraft;
            settingsAppearancePreviewIds.clear();
            settingsAppearancePreviewActive = false;
            if (previousLanguage != appLanguage) {
                RebuildSettingsControls();
            } else if (widgetListChanged) {
                RefreshWidgetList();
            }
        }
    } else if (id == ID_CANCEL) {
        CloseSettingsWindow();
    }
}

static void DrawIdentificationOutline(HWND window, bool ellipse) {
    HDC dc = GetDC(window);
    if (dc == nullptr) {
        return;
    }
    RECT rect = {};
    GetClientRect(window, &rect);
    HPEN pen = CreatePen(PS_SOLID, 3, IDENTIFY_COLOR);
    HGDIOBJ oldPen = SelectObject(dc, pen);
    HGDIOBJ oldBrush = SelectObject(dc, GetStockObject(HOLLOW_BRUSH));
    if (ellipse) {
        Ellipse(dc, 2, 2, rect.right - 2, rect.bottom - 2);
    } else {
        Rectangle(dc, 1, 1, rect.right - 1, rect.bottom - 1);
    }
    SelectObject(dc, oldBrush);
    SelectObject(dc, oldPen);
    DeleteObject(pen);
    ReleaseDC(window, dc);
}

static bool IsPanelAnalogDoubleClick(Widget* widget, LPARAM lParam) {
    if (widget == nullptr || widget->config.type != WIDGET_PANEL) {
        return false;
    }
    ULONGLONG tick = GetTickCount64();
    POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
    bool doubleClick = widget->lastAnalogClickTick != 0 && tick - widget->lastAnalogClickTick <= GetDoubleClickTime() &&
        std::abs(point.x - widget->lastAnalogClickPoint.x) <= GetSystemMetrics(SM_CXDOUBLECLK) / 2 &&
        std::abs(point.y - widget->lastAnalogClickPoint.y) <= GetSystemMetrics(SM_CYDOUBLECLK) / 2;
    if (doubleClick) {
        widget->lastAnalogClickTick = 0;
    } else {
        widget->lastAnalogClickTick = tick;
        widget->lastAnalogClickPoint = point;
    }
    return doubleClick;
}

static LRESULT CALLBACK AnalogChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    HWND parent = GetParent(window);
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(parent, GWLP_USERDATA));
    if (widget != nullptr) {
        if (message == WM_LBUTTONDOWN && IsPanelAnalogDoubleClick(widget, lParam)) {
            return SendMessageW(parent, WM_LBUTTONDBLCLK, wParam, lParam);
        }
        if (message == WM_LBUTTONDBLCLK) {
            widget->lastAnalogClickTick = 0;
        }
        if (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP || message == WM_MOUSEMOVE || message == WM_LBUTTONDBLCLK || message == WM_RBUTTONUP ||
            message == WM_CONTEXTMENU) {
            return SendMessageW(parent, message, wParam, lParam);
        }
        if (widget->analogProc != nullptr) {
            LRESULT result = CallWindowProcW(widget->analogProc, window, message, wParam, lParam);
            return result;
        }
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

static LRESULT CALLBACK CalendarChildProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    HWND parent = GetParent(window);
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(parent, GWLP_USERDATA));
    if (widget != nullptr) {
        if (message == WM_RBUTTONUP || message == WM_CONTEXTMENU) {
            return SendMessageW(parent, message, wParam, lParam);
        }
        if (message == WM_LBUTTONDOWN && widget->config.type == WIDGET_CALENDAR) {
            MCHITTESTINFO hit = {};
            hit.cbSize = sizeof(hit);
            hit.pt.x = GET_X_LPARAM(lParam);
            hit.pt.y = GET_Y_LPARAM(lParam);
            MonthCal_HitTest(window, &hit);
            bool draggableArea = hit.uHit == MCHT_NOWHERE || hit.uHit == MCHT_TITLEBK || hit.uHit == MCHT_CALENDARBK;
            if (draggableArea) {
                return SendMessageW(parent, message, wParam, lParam);
            }
        }
        if (widget->calendarProc != nullptr) {
            CalendarLocaleScope localeScope(widget->config.language);
            LRESULT result = CallWindowProcW(widget->calendarProc, window, message, wParam, lParam);
            if ((message == WM_THEMECHANGED || message == WM_SETTINGCHANGE) && widget->calendarFont != nullptr) {
                SendMessageW(window, WM_SETFONT, reinterpret_cast<WPARAM>(widget->calendarFont), TRUE);
            }
            if (message == WM_PAINT && widget->config.type == WIDGET_CALENDAR && widget->identifyActive && widget->identifyPhase) {
                DrawIdentificationOutline(window, false);
            }
            return result;
        }
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

static LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    Widget* widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(window, GWLP_USERDATA));
    if (message == WM_NCCREATE) {
        CREATESTRUCTW* create = reinterpret_cast<CREATESTRUCTW*>(lParam);
        if (create->lpCreateParams != nullptr) {
            widget = static_cast<Widget*>(create->lpCreateParams);
            SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(widget));
        }
    }
    if (message == taskbarCreatedMessage && window == hController) {
        AddTrayIcon();
        return 0;
    }
    switch (message) {
        case WM_DISPLAYCHANGE:
            if (window == hController) {
                displayRefreshPending = false;
                RecreateAllWidgetWindows();
                return 0;
            }
            if (!displayRefreshPending) {
                displayRefreshPending = true;
                PostMessageW(hController, WM_REFRESH_DISPLAYS, 0, 0);
            }
            break;
        case WM_REFRESH_DISPLAYS:
            if (window == hController) {
                displayRefreshPending = false;
                RecreateAllWidgetWindows();
                return 0;
            }
            break;
        case WM_AUDIO_FINISHED:
            if (window == hController) {
                Widget* finishedWidget = FindWidgetById(static_cast<int>(wParam));
                ULONG generation = static_cast<ULONG>(lParam);
                if (finishedWidget != nullptr && finishedWidget->audioGeneration == generation && finishedWidget->audioStopEvent != nullptr) {
                    CloseHandle(finishedWidget->audioStopEvent);
                    finishedWidget->audioStopEvent = nullptr;
                }
                return 0;
            }
            break;
        case WM_SETTINGS_AUDIO_FINISHED:
            if (window == hController) {
                ULONG generation = static_cast<ULONG>(lParam);
                if (settingsPreviewGeneration == generation && settingsPreviewStopEvent != nullptr) {
                    CloseHandle(settingsPreviewStopEvent);
                    settingsPreviewStopEvent = nullptr;
                }
                return 0;
            }
            break;
        case WM_NTP_RESULT:
            if (window == hController) {
                std::unique_ptr<NtpThreadResult> result(reinterpret_cast<NtpThreadResult*>(lParam));
                ntpQueryRunning = false;
                if (hNtpThread != nullptr) {
                    CloseHandle(hNtpThread);
                    hNtpThread = nullptr;
                }
                if (result != nullptr && result->generation != ntpGeneration.load()) {
                    StartNtpSynchronization(true);
                    UpdateNtpSettingsControls();
                    return 0;
                }
                if (result != nullptr && result->success) {
                    ntpOffset100Nanoseconds = result->offset100Nanoseconds;
                    ntpActiveServer = result->server;
                    ntpTimeValid = true;
                    ntpLastQueryFailed = false;
                    for (size_t index = 0; index < widgets.size(); index++) {
                        widgets[index]->lastRenderKey = -1;
                        widgets[index]->rendered = false;
                        if (widgets[index]->config.visible) {
                            RenderWidget(widgets[index].get());
                        }
                    }
                } else {
                    ntpLastQueryFailed = true;
                    if (!ntpTimeValid) {
                        ntpActiveServer.clear();
                    }
                }
                UpdateNtpSettingsControls();
                return 0;
            }
            break;
        case WM_CTLCOLORSTATIC:
        {
            HDC dc = reinterpret_cast<HDC>(wParam);
            if (window == hGeneralPage || window == hAppearancePage || window == hAlarmPage || window == hTimePage) {
                int colorIndex = themesDisabled ? COLOR_BTNFACE : COLOR_WINDOW;
                SetTextColor(dc, GetSysColor(COLOR_WINDOWTEXT));
                SetBkColor(dc, GetSysColor(colorIndex));
                SetBkMode(dc, OPAQUE);
                return reinterpret_cast<LRESULT>(GetSysColorBrush(colorIndex));
            }
            break;
        }
        case WM_CTLCOLORBTN:
        {
            HWND control = reinterpret_cast<HWND>(lParam);
            bool tabControlChild = std::find(generalControls.begin(), generalControls.end(), control) != generalControls.end() ||
                std::find(appearanceControls.begin(), appearanceControls.end(), control) != appearanceControls.end() ||
                std::find(alarmControls.begin(), alarmControls.end(), control) != alarmControls.end() ||
                std::find(timeControls.begin(), timeControls.end(), control) != timeControls.end();
            LONG_PTR style = GetWindowLongPtrW(control, GWL_STYLE);
            UINT buttonType = static_cast<UINT>(style & BS_TYPEMASK);
            if (tabControlChild && (buttonType == BS_CHECKBOX || buttonType == BS_AUTOCHECKBOX || buttonType == BS_3STATE || buttonType == BS_AUTO3STATE)) {
                int colorIndex = themesDisabled ? COLOR_BTNFACE : COLOR_WINDOW;
                SetBkColor(reinterpret_cast<HDC>(wParam), GetSysColor(colorIndex));
                SetBkMode(reinterpret_cast<HDC>(wParam), OPAQUE);
                return reinterpret_cast<LRESULT>(GetSysColorBrush(colorIndex));
            }
            break;
        }
        case WM_ERASEBKGND:
            if (window == hGeneralPage || window == hAppearancePage || window == hAlarmPage || window == hTimePage) {
                RECT rect = {};
                GetClientRect(window, &rect);
                int colorIndex = themesDisabled ? COLOR_BTNFACE : COLOR_WINDOW;
                FillRect(reinterpret_cast<HDC>(wParam), &rect, GetSysColorBrush(colorIndex));
                return 1;
            }
            if (widget != nullptr && (widget->config.type == WIDGET_PANEL || widget->config.type == WIDGET_CALENDAR || widget->config.type == WIDGET_FULLSCREEN ||
                (widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground))) {
                return 1;
            }
            break;
        case WM_PRINTCLIENT:
            if (window == hGeneralPage || window == hAppearancePage || window == hAlarmPage || window == hTimePage) {
                RECT rect = {};
                GetClientRect(window, &rect);
                int colorIndex = themesDisabled ? COLOR_BTNFACE : COLOR_WINDOW;
                FillRect(reinterpret_cast<HDC>(wParam), &rect, GetSysColorBrush(colorIndex));
                return 0;
            }
            break;
        case WM_PAINT:
            if (widget != nullptr && ((widget->config.type == WIDGET_DIGITAL && !widget->config.transparentBackground) || widget->config.type == WIDGET_FULLSCREEN)) {
                PAINTSTRUCT paint = {};
                HDC dc = BeginPaint(window, &paint);
                PaintWidgetBuffered(widget, window, dc, false);
                EndPaint(window, &paint);
                return 0;
            }
            if (widget != nullptr && widget->config.type == WIDGET_PANEL) {
                PAINTSTRUCT paint = {};
                HDC dc = BeginPaint(window, &paint);
                PaintWidgetBuffered(widget, window, dc, true);
                EndPaint(window, &paint);
                return 0;
            }
            break;
        case WM_HSCROLL:
            if (window == hAppearancePage) {
                return SendMessageW(hSettings, WM_HSCROLL, wParam, lParam);
            }
            if (window == hSettings) {
                HWND trackBar = reinterpret_cast<HWND>(lParam);
                if (trackBar == hOpacityTrackBar || trackBar == hFontSizeTrackBar || trackBar == hPaddingTrackBar || trackBar == hBorderTrackBar || trackBar == hBorderWidthTrackBar) {
                    UpdateAppearanceSliderLabels(trackBar);
                    PreviewSelectedWidgetAppearance(false);
                    return 0;
                }
            }
            break;
        case WM_COMMAND:
        {
            int id = LOWORD(wParam);
            int notification = HIWORD(wParam);
            if (window == hGeneralPage || window == hAppearancePage || window == hAlarmPage || window == hTimePage) {
                return SendMessageW(hSettings, WM_COMMAND, wParam, lParam);
            }
            if (window == hSettings) {
                HandleSettingsCommand(id, notification);
                return 0;
            }
            if (window == hHelp || window == hAbout) {
                if (id == ID_INFO_CLOSE) {
                    SendMessageW(window, WM_CLOSE, 0, 0);
                }
                return 0;
            }
            if (window == hController) {
                if (id == ID_MENU_SETTINGS) {
                    ShowSettingsWindow();
                } else if (id == ID_MENU_SHOW_ALL) {
                    SetAllVisible(true);
                } else if (id == ID_MENU_HIDE_ALL) {
                    SetAllVisible(false);
                } else if (id == ID_MENU_ARRANGE_WIDGETS) {
                    ArrangeVisibleWidgets(nullptr);
                } else if (id == ID_MENU_STOP_ALARM) {
                    StopAllAlarms();
                } else if (id == ID_MENU_HELP) {
                    ShowInformationWindow(true);
                } else if (id == ID_MENU_ABOUT) {
                    ShowInformationWindow(false);
                } else if (id == ID_MENU_EXIT) {
                    DestroyWindow(hController);
                }
                return 0;
            }
            break;
        }
        case WM_NOTIFY:
            if (widget != nullptr && widget->calendarChild != nullptr && reinterpret_cast<NMHDR*>(lParam)->hwndFrom == widget->calendarChild &&
                reinterpret_cast<NMHDR*>(lParam)->code == MCN_SELECT) {
                NMSELCHANGE* selection = reinterpret_cast<NMSELCHANGE*>(lParam);
                CopyWidgetDate(widget, selection->stSelStart);
                return 0;
            }
            if (window == hSettings && hTabs != nullptr && reinterpret_cast<NMHDR*>(lParam)->idFrom == ID_TABS && reinterpret_cast<NMHDR*>(lParam)->code == TCN_SELCHANGE) {
                ShowSettingsTab(TabCtrl_GetCurSel(hTabs));
                return 0;
            }
            break;
        case WM_TRAYICON:
            if (window == hController) {
                UINT event = LOWORD(lParam);
                if (event == WM_CONTEXTMENU || event == WM_RBUTTONUP) {
                    ShowTrayContextMenu();
                } else if (event == NIN_SELECT || event == NIN_KEYSELECT || event == WM_LBUTTONUP || event == WM_LBUTTONDOWN || event == WM_LBUTTONDBLCLK) {
                    ToggleAllFromTray();
                }
                return 0;
            }
            break;
        case WM_SHOW_EXISTING:
            if (window == hController) {
                bool anyVisible = false;
                for (size_t index = 0; index < widgets.size(); index++) {
                    if (widgets[index]->config.visible) {
                        anyVisible = true;
                        SetWindowPos(widgets[index]->window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        for (size_t windowIndex = 0; windowIndex < widgets[index]->fullscreenWindows.size(); windowIndex++) {
                            SetWindowPos(widgets[index]->fullscreenWindows[windowIndex], HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        }
                        if (!widgets[index]->config.topMost && widgets[index]->config.type != WIDGET_FULLSCREEN) {
                            SetWindowPos(widgets[index]->window, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        }
                    }
                }
                if (!anyVisible) {
                    SetAllVisible(true);
                } else {
                    RefreshFullscreenPresentation();
                }
                if (hSettings != nullptr) {
                    SetForegroundWindowEx(hSettings);
                } else {
                    for (size_t index = 0; index < widgets.size(); index++) {
                        if (widgets[index]->config.visible) {
                            SetForegroundWindowEx(widgets[index]->window);
                            break;
                        }
                    }
                }
                return 0;
            }
            break;
        case WM_TIMER:
            if (window == hController && wParam == TIMER_REFRESH) {
                static ULONGLONG previousSecond = static_cast<ULONGLONG>(-1);
                static ULONGLONG previousHalfSecond = static_cast<ULONGLONG>(-1);
                static ULONGLONG previousIdentifyFrame = static_cast<ULONGLONG>(-1);
                ULONGLONG tick = GetTickCount64();
                StartNtpSynchronization(false);
                ULONGLONG second = tick / 1000;
                ULONGLONG halfSecond = tick / 500;
                ULONGLONG identifyFrame = tick / 200;
                for (size_t index = 0; index < widgets.size(); index++) {
                    Widget* current = widgets[index].get();
                    if (current->copyTooltip != nullptr && tick >= current->copyTooltipEndTick) {
                        if (IsWindow(current->copyTooltip)) {
                            DestroyWindow(current->copyTooltip);
                        }
                        current->copyTooltip = nullptr;
                    }
                }
                bool flashChanged = halfSecond != previousHalfSecond;
                if (flashChanged) {
                    previousHalfSecond = halfSecond;
                    for (size_t index = 0; index < widgets.size(); index++) {
                        Widget* current = widgets[index].get();
                        if (current->alarmActive) {
                            current->flashPhase = !current->flashPhase;
                        }
                    }
                }
                if (identifyFrame != previousIdentifyFrame) {
                    previousIdentifyFrame = identifyFrame;
                    for (size_t index = 0; index < widgets.size(); index++) {
                        Widget* current = widgets[index].get();
                        if (!current->identifyActive) {
                            continue;
                        }
                        if (tick >= current->identifyEndTick) {
                            FinishWidgetIdentification(current);
                        } else {
                            current->identifyPhase = !current->identifyPhase;
                            RenderWidgetIdentification(current);
                        }
                    }
                }
                if (second != previousSecond || flashChanged) {
                    bool secondChanged = second != previousSecond;
                    if (secondChanged) {
                        previousSecond = second;
                        for (size_t index = 0; index < widgets.size(); index++) {
                            CheckWidgetAlarm(widgets[index].get());
                        }
                    }
                    for (size_t index = 0; index < widgets.size(); index++) {
                        Widget* current = widgets[index].get();
                        if (!current->config.visible) {
                            continue;
                        }
                        SYSTEMTIME displayed = {};
                        GetDisplayedTime(current->config, &displayed);
                        int renderKey = current->config.showSeconds ? displayed.wHour * 3600 + displayed.wMinute * 60 + displayed.wSecond : displayed.wHour * 60 + displayed.wMinute;
                        bool alarmFrameChanged = current->alarmActive && flashChanged;
                        if (current->lastRenderKey != renderKey || alarmFrameChanged || !current->rendered) {
                            current->lastRenderKey = renderKey;
                            RenderWidget(current);
                        }
                    }
                }
                return 0;
            }
            break;
        case WM_LBUTTONDOWN:
            if (widget != nullptr) {
                ULONGLONG tick = GetTickCount64();
                if (widget->alarmActive || widget->audioStopEvent != nullptr) {
                    StopWidgetAlarm(widget);
                    widget->alarmStoppedTick = tick;
                    return 0;
                }
                if (widget->alarmStoppedTick != 0 && tick - widget->alarmStoppedTick <= GetDoubleClickTime()) {
                    return 0;
                }
                widget->alarmStoppedTick = 0;
                if (widget->config.type == WIDGET_FULLSCREEN && !widget->fullscreenPreview) {
                    SetForegroundWindow(window);
                    SetFocus(window);
                    return 0;
                }
                POINT cursor = {};
                GetCursorPos(&cursor);
                RECT rect = {};
                GetWindowRect(window, &rect);
                widget->dragOffset.x = cursor.x - rect.left;
                widget->dragOffset.y = cursor.y - rect.top;
                widget->dragging = true;
                SetCapture(window);
                return 0;
            }
            break;
        case WM_MOUSEMOVE:
            if (widget != nullptr && widget->dragging && (wParam & MK_LBUTTON)) {
                widget->lastAnalogClickTick = 0;
                POINT cursor = {};
                GetCursorPos(&cursor);
                SetWindowPos(window, nullptr, cursor.x - widget->dragOffset.x, cursor.y - widget->dragOffset.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                return 0;
            }
            break;
        case WM_LBUTTONUP:
            if (widget != nullptr && widget->dragging) {
                widget->dragging = false;
                ReleaseCapture();
                if (widget->fullscreenPreview) {
                    SaveFullscreenPreviewPosition(widget);
                } else {
                    SaveWidgetPosition(widget);
                }
                return 0;
            }
            break;
        case WM_CAPTURECHANGED:
            if (widget != nullptr && widget->dragging) {
                widget->dragging = false;
                if (widget->fullscreenPreview) {
                    SaveFullscreenPreviewPosition(widget);
                } else {
                    SaveWidgetPosition(widget);
                }
                return 0;
            }
            break;
        case WM_LBUTTONDBLCLK:
            if (widget != nullptr && widget->alarmStoppedTick != 0 && GetTickCount64() - widget->alarmStoppedTick <= GetDoubleClickTime()) {
                return 0;
            }
            if (widget != nullptr && widget->config.type != WIDGET_CALENDAR) {
                HandleWidgetMenuCommand(widget, ID_MENU_SECONDS);
                return 0;
            }
            break;
        case WM_RBUTTONUP:
        case WM_CONTEXTMENU:
            if (widget != nullptr) {
                ShowWidgetContextMenu(widget, window);
                return 0;
            }
            break;
        case WM_KEYDOWN:
            if (widget != nullptr) {
                if (wParam == VK_ESCAPE) {
                    if (widget->alarmActive) {
                        StopWidgetAlarm(widget);
                    } else {
                        SetWidgetVisible(widget, false);
                    }
                } else if (wParam == VK_F1) {
                    ShowInformationWindow(true);
                } else if (wParam == L'B') {
                    ShowSettingsWindow();
                }
                return 0;
            }
            break;
        case WM_CLOSE:
            if (window == hSettings) {
                CloseSettingsWindow();
                return 0;
            }
            if (window == hHelp) {
                SaveFormPosition(hHelp, &helpX, &helpY);
                DestroyWindow(hHelp);
                hHelp = nullptr;
                SaveAllSettings();
                return 0;
            }
            if (window == hAbout) {
                SaveFormPosition(hAbout, &aboutX, &aboutY);
                DestroyWindow(hAbout);
                hAbout = nullptr;
                SaveAllSettings();
                return 0;
            }
            if (widget != nullptr) {
                SetWidgetVisible(widget, false);
                return 0;
            }
            break;
        case WM_DESTROY:
            if (window == hController) {
                RestoreSettingsAppearancePreview();
                StopSettingsPreview();
                KillTimer(hController, TIMER_REFRESH);
                RemoveTrayIcon();
                DestroyWidgetWindows();
                SaveAllSettings();
                PostQuitMessage(0);
                return 0;
            }
            break;
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

int APIENTRY wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previousInstance, _In_ LPWSTR commandLine, _In_ int showCommand) {
    UNREFERENCED_PARAMETER(previousInstance);
    UNREFERENCED_PARAMETER(commandLine);
    UNREFERENCED_PARAMETER(showCommand);
    hInstance = instance;
    hSingleInstanceMutex = CreateMutexW(nullptr, FALSE, L"CalClock.MultiWidget.Instance");
    if (hSingleInstanceMutex != nullptr && GetLastError() == ERROR_ALREADY_EXISTS) {
        HWND existing = FindWindowExW(HWND_MESSAGE, nullptr, CLASS_NAME, CONTROLLER_TITLE);
        if (existing != nullptr) {
            SendMessageW(existing, WM_SHOW_EXISTING, 0, 0);
        }
        CloseHandle(hSingleInstanceMutex);
        return 0;
    }
    INITCOMMONCONTROLSEX controls = { sizeof(controls), ICC_WIN95_CLASSES | ICC_TAB_CLASSES | ICC_DATE_CLASSES };
    InitCommonControlsEx(&controls);
    WSADATA winsockData = {};
    winsockReady = WSAStartup(MAKEWORD(2, 2), &winsockData) == 0;
    InstallCalendarLocaleHook();
    LoadAllSettings();
    SetThemeAppProperties(themesDisabled ? 0 : STAP_ALLOW_NONCLIENT | STAP_ALLOW_CONTROLS | STAP_ALLOW_WEBCONTENT);
    WNDCLASSEXW blackoutClass = {};
    blackoutClass.cbSize = sizeof(blackoutClass);
    blackoutClass.lpfnWndProc = BlackoutWindowProc;
    blackoutClass.hInstance = instance;
    blackoutClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    blackoutClass.lpszClassName = BLACKOUT_CLASS_NAME;
    if (!RegisterClassExW(&blackoutClass)) {
        if (winsockReady) {
            WSACleanup();
        }
        return 1;
    }
    WNDCLASSEXW windowClass = {};
    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_DBLCLKS;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = instance;
    windowClass.hIcon = LoadIconW(instance, MAKEINTRESOURCEW(IDI_CLOCK));
    windowClass.hIconSm = windowClass.hIcon;
    windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
    windowClass.lpszClassName = CLASS_NAME;
    if (!RegisterClassExW(&windowClass)) {
        if (winsockReady) {
            WSACleanup();
        }
        return 1;
    }
    taskbarCreatedMessage = RegisterWindowMessageW(L"TaskbarCreated");
    hController = CreateWindowExW(0, CLASS_NAME, CONTROLLER_TITLE, 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, instance, nullptr);
    if (hController == nullptr) {
        if (winsockReady) {
            WSACleanup();
        }
        return 2;
    }
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&dwriteFactory));
    for (size_t index = 0; index < widgets.size(); index++) {
        CreateWidgetWindow(widgets[index].get());
    }
    RefreshFullscreenPresentation();
    AddTrayIcon();
    SetTimer(hController, TIMER_REFRESH, 100, nullptr);
    SaveAllSettings();
    StartNtpSynchronization(true);
    MSG message = {};
    while (GetMessageW(&message, nullptr, 0, 0) > 0) {
        if ((message.message == WM_KEYDOWN || message.message == WM_SYSKEYDOWN) && message.wParam == VK_ESCAPE && HideFullscreenWidgetsFromEscape()) {
            continue;
        }
        if (hSettings != nullptr && IsDialogMessageW(hSettings, &message)) {
            continue;
        }
        if (hHelp != nullptr && IsDialogMessageW(hHelp, &message)) {
            continue;
        }
        if (hAbout != nullptr && IsDialogMessageW(hAbout, &message)) {
            continue;
        }
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
    if (hTimeDate != nullptr) {
        FreeLibrary(hTimeDate);
    }
    if (hUiFont != nullptr) {
        DeleteObject(hUiFont);
    }
    if (hAboutFont != nullptr) {
        DeleteObject(hAboutFont);
    }
    if (dwriteFactory != nullptr) {
        dwriteFactory->Release();
        dwriteFactory = nullptr;
    }
    if (d2dFactory != nullptr) {
        d2dFactory->Release();
        d2dFactory = nullptr;
    }
    if (hSingleInstanceMutex != nullptr) {
        CloseHandle(hSingleInstanceMutex);
    }
    bool ntpThreadFinished = StopNtpSynchronization();
    if (winsockReady && ntpThreadFinished) {
        WSACleanup();
    }
    return static_cast<int>(message.wParam);
}
