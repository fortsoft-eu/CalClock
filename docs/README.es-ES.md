# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · **Español** · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock es una aplicación nativa Win32/x86 para Windows Vista y versiones posteriores que muestra relojes y calendarios flotantes configurables por separado en el escritorio de Windows. Se ejecuta en el área de notificación y no necesita una ventana de control permanente.

## Funciones

- Hasta 32 widgets configurables de forma independiente
- Idioma, zona horaria, desfase, visibilidad y opción de mantener siempre encima por widget
- Relojes analógicos con tamaño de esfera seleccionable y segundero opcional
- Relojes digitales con fuentes, colores, opacidad, márgenes interiores, bordes, cero inicial opcional y fondo transparente opcional
- Calendarios nativos de Windows con selección de fechas, cuatro estilos de borde, color de borde configurable, números de semana, elección del primer día y 33 formatos de copia
- Paneles de calendario y reloj con hasta dos relojes adicionales con nombre y zonas independientes, tamaños de esfera separados, cuatro estilos de borde, color configurable, texto UTC, cero inicial y una fuente distinta por línea de texto
- Alarmas con selección de días, indicación visual, reproducción interna de audio, repetición, comandos locales y llamadas a scripts HTTP/HTTPS
- Señales horarias por reloj cada 1, 5, 10, 15, 20, 30 o 60 minutos; las señales coincidentes se combinan en una secuencia
- Comando Silenciado por reloj y comando marcable Silenciar todo en el área de notificación
- Inicio automático con Windows opcional
- Ajuste opcional a los bordes del área de trabajo al arrastrar, dentro de cinco píxeles y activado de forma predeterminada; la fijación se conserva al cambiar el tamaño
- Sincronización NTP sin modificar el reloj del sistema Windows
- Varios ajustes NTP para Chequia y Eslovaquia, PTB, Ubuntu/NTP Pool o servidores personalizados
- Almacenamiento en el Registro o XML, con importación y exportación XML
- Controles del área de notificación que restauran los widgets ocultados más recientemente
- Identificación de widgets y alineación estable en una cuadrícula sin solapamientos
- Vista previa inmediata de la apariencia con cancelación y valores predeterminados por widget
- Fuentes de la aplicación y los widgets, estilos visuales y suavizado ClearType, GDI o ninguno
- Interfaz en 36 variantes de idioma, con selección independiente para la aplicación y cada widget

## Tipos de widget

| Widget | Descripción |
| --- | --- |
| Reloj analógico | Esfera flotante de Windows con los tamaños y el segundero opcional disponibles en la versión actual de Windows |
| Reloj digital | Pantalla digital flotante configurable con texto UTC, cero inicial, bordes y fondo transparente opcionales |
| Calendario | Calendario mensual nativo desplazable con selección de fechas, bordes configurables y formatos de copia |
| Calendario con reloj | Panel combinado con calendario nativo, reloj analógico, líneas de texto configurables, UTC y bordes configurables |
| Reloj de monitor | Reloj digital que ocupa uno o varios monitores seleccionados, con oscurecimiento opcional y UTC en otra línea |

Al iniciarse por primera vez, CalClock elige el idioma de la interfaz de Windows y usa inglés estadounidense si no es compatible. Crea de forma predeterminada un reloj analógico visible. Cada widget conserva su posición y configuración entre ejecuciones. Mientras Configuración está abierta, un reloj de monitor se representa mediante una vista previa desplazable con la proporción del monitor seleccionado. `Esc` oculta el reloj de monitor y elimina su oscurecimiento incluso con Configuración activa. El puntero se oculta tras un breve periodo de inactividad sobre los relojes de monitor y monitores oscurecidos, y reaparece al mover el ratón. Permanece visible sobre la vista previa pequeña de Configuración.

## Controles

- Arrastre un reloj o panel con el botón izquierdo.
- Arrastre un calendario independiente desde una zona libre.
- Pulse con el botón derecho un widget o el icono de notificación para abrir su menú contextual.
- Un clic izquierdo en el icono de notificación oculta los widgets visibles. Si todos están ocultos, otro clic restaura solo los ocultados más recientemente.
- Haga doble clic en una esfera para alternar los segundos. En el panel de calendario con reloj, solo el doble clic directamente en la esfera principal alterna el segundero. Los relojes adicionales no tienen segundero.
- `F1` abre Ayuda, `B` Configuración, `M` alterna Silenciar todo y `Esc` oculta un widget o detiene una alarma activa.
- Pulse `Alt+0`, `Alt+1`, `Alt+2` o `Alt+3` en Reloj analógico o Calendario con reloj para elegir el tamaño de la esfera principal, del menor al mayor.
- Hacer doble clic en un widget de Configuración lo hace visible si es necesario, marca `Visible` y lo identifica brevemente en el escritorio.
- Abrir Configuración desde el menú de un widget lo selecciona inmediatamente.
- Quitar o Supr elimina todos los seleccionados al aplicar los cambios. `Insert` alterna la selección del elemento actual y baja el cursor de la lista una fila.
- `Ctrl+C` copia los widgets seleccionados y `Ctrl+V` añade sus copias al final en el orden de la lista. Las copias conservan todos los ajustes y reciben un sufijo en el idioma de la aplicación. Duplicar realiza directamente la misma operación. Se permiten hasta 32 widgets. Si no caben todas las copias, se añaden las que caben en orden y se muestra un aviso sobre las restantes.

Al abrir Configuración desde el icono del área de notificación, se selecciona el último widget elegido.

Configuración recuerda la última pestaña abierta y el último tipo de widget añadido.

Las fechas del calendario se pueden copiar en 33 formatos locales, ordenables, con día o mes primero, textuales y con día de la semana. Todas las máscaras están disponibles en cualquier idioma de interfaz. El formato corto local predeterminado sigue el idioma del widget, al igual que los nombres de meses y días. Las entradas muestran la máscara y un ejemplo actualizado.

Un panel de calendario con reloj puede mostrar hasta dos relojes adicionales. Active cada uno en General y elija su nombre y zona horaria. Las zonas con nombre siguen sus propias reglas de horario de verano; los desfases UTC fijos permanecen constantes. Cuando están activos, cada reloj muestra su día local debajo de la hora. Las tres listas de tamaño de Apariencia controlan, en orden, el reloj principal, Reloj 1 y Reloj 2. Un clic derecho en una esfera adicional permite elegir su tamaño. Los relojes adicionales siempre omiten los segundos y comparten idioma, formato horario, fuentes y desfase con el widget. Añadir, quitar o redimensionar relojes mantiene el widget fijado a los mismos bordes del área de trabajo.

En este panel, la fecha superior es un enlace que devuelve el calendario a hoy; el texto inferior de zona horaria abre la configuración clásica de Fecha y hora de Windows.

`Alinear en cuadrícula` ajusta los widgets de escritorio visibles a una cuadrícula estable sin solapamientos, conservando aproximadamente su disposición manual. El widget desde cuyo menú se invoca permanece en su sitio; el comando del área de notificación organiza cada monitor de forma independiente. Se excluyen los relojes de monitor.

## Apariencia

Para calendarios independientes, **Fila Hoy** en el menú o en Apariencia controla la fila inferior. Está marcada de forma predeterminada; al desmarcarla se oculta la fila y se reduce el calendario. La elección se guarda por widget. **Ir a hoy** sigue disponible y vuelve a la vista mensual. Al cambiar la fecha según la hora del widget, el calendario selecciona hoy automáticamente y conserva la vista actual.

Los cambios de apariencia se previsualizan inmediatamente en el widget seleccionado. `Cancelar` descarta los cambios no aplicados; `Aspecto predeterminado` recupera los valores de ese tipo de widget.

Relojes digitales, calendarios y paneles comparten cuatro estilos de borde. El borde simple permite configurar el color; el ancho se puede ajustar cuando el widget lo admite. Los relojes digitales transparentes ofrecen los mismos estilos que los opacos. Las fuentes de aplicación y calendario no incluyen tamaño; las digitales y de texto del panel sí. Las fuentes personalizadas del calendario se admiten con la apariencia clásica de Windows o con los temas desactivados para la aplicación o el widget.

El idioma de la aplicación, fuente de interfaz, suavizado, estilos visuales, almacenamiento, inicio con Windows y ajuste a bordes son globales y se configuran en Aplicación. La fuente de tiempo también es global. Idioma del widget, suavizado, estilos, zona, desfase, alarma y señal horaria se configuran por separado. El suavizado ofrece **ClearType**, **GDI** y **Ninguno**.

El control **Volumen de audio** de Alarma regula los archivos reproducidos internamente por widget y muestra el nivel en dB. El valor predeterminado **−18 dB** conserva el nivel original (**100%**). Moverlo a la derecha amplifica el audio; el máximo **0 dB** equivale aproximadamente al **794%** de la amplitud original. El extremo izquierdo es **−∞ dB** (silencio). Los cambios actúan durante la prueba de audio. La amplificación se aplica al audio decodificado, incluidos WAV, MP3, WMA, AAC, M4A y FLAC cuando Windows los admite. La reproducción heredada de archivos no decodificables, como MIDI, está limitada al 100%.

Los controles de días de alarma respetan el primer día de semana de la cultura elegida para la aplicación. Los días guardados conservan su significado al cambiar el idioma. Activar desde el menú una alarma sin días seleccionados abre la pestaña Alarma del widget en lugar de activar una alarma que no puede sonar.

**Cero inicial** ofrece **Sí** (predeterminado), **No, reservar espacio** y **No, sin espacio**. **No, reservar espacio** oculta el cero y reserva su ancho real en la fuente elegida, manteniendo los demás dígitos en posición incluso con fuentes proporcionales. Los relojes de monitor usan por defecto texto blanco sobre fondo negro.

## Hora y alarmas

Los relojes digitales, paneles de calendario con reloj y relojes de monitor ofrecen **Según el idioma**, **12 horas** y **24 horas** en **Formato de hora** de General. **Según el idioma** es el valor predeterminado: por ejemplo, inglés estadounidense y australiano usan 12 horas; británico usa 24. La selección manual se conserva al cambiar el idioma del widget. Separadores e indicadores AM/PM siguen la cultura; las culturas sin indicadores propios usan **AM/PM** en modo de 12 horas.

**AM/PM** está marcado por defecto. Desmarcarlo oculta el indicador sin cambiar el ciclo de 12 horas. Los relojes de monitor muestran el indicador en una línea bajo la hora, igual que UTC. UTC siempre usa el formato de 24 horas. El ajuste del cero inicial sigue determinando si se muestra, se oculta reservando espacio o se omite.

Las zonas con nombre muestran la hora civil del lugar y aplican automáticamente sus reglas de horario de verano. El desfase junto a cada nombre corresponde a la fecha actual y se actualiza al abrir la lista. Las entradas **UTC** independientes ofrecen desfases fijos desde **UTC−12:00** hasta **UTC+14:00**, en pasos de 15 minutos y sin cambios de verano. Elija de forma independiente para cada widget su zona local, cualquier otra zona con nombre o un desfase UTC fijo.

Los widgets nuevos usan por defecto **Zona horaria actual de Windows**, que sigue la zona horaria actual de Windows y su ajuste automático del horario de verano. Los widgets existentes conservan la zona elegida. Esta opción determina la zona horaria; la fuente de tiempo compartida, Windows o NTP, sigue siendo independiente.

Cada widget puede usar cualquier zona de Windows y un desfase con signo de la forma `[-]HH:mm:ss.ff`. La entrada compacta se interpreta desde la derecha, empezando por los segundos.

El desfase resulta útil, por ejemplo, en estudios de radiodifusión para compensar el retardo de la ruta de transmisión. Adelantar el reloj del estudio según el retardo medido permite que la señal llegue a los oyentes en el instante previsto.

El desfase del widget se aplica a UTC antes de convertir la hora a su zona, por lo que también desplaza el instante del cambio de horario. Un reloj adelantado diez segundos cambia diez segundos antes; uno atrasado diez segundos cambia diez segundos después. Las agujas, la indicación digital, las fechas del calendario, las alarmas y las señales horarias usan la hora resultante.

La pestaña Hora selecciona la hora del sistema Windows o los servidores NTP configurados para toda la aplicación y, por tanto, para todos los widgets. NTP solo corrige la hora mostrada por CalClock; el reloj de Windows nunca se modifica. Se usa la hora del sistema hasta la primera respuesta válida. NTP es el valor predeterminado. El conjunto automático elige servidores checos y eslovacos, PTB para Europa o el grupo mundial según la región del sistema. Varias mediciones se filtran por retardo de red y respuestas atípicas. Sincronizar ahora inicia una medición nueva de inmediato.

Tras la sincronización, el reloj de CalClock sigue funcionando independientemente de los cambios posteriores en la hora del sistema Windows. Si falla la conexión o se cambian los servidores, continúa desde la última sincronización válida hasta recibir una nueva respuesta; este estado se conserva hasta que se cierra la aplicación.

La pestaña Hora registra las consultas a servidores NTP desde el inicio de la aplicación. Cada entrada contiene la fecha y hora local del equipo, el servidor y el estado. OK identifica una respuesta válida y θ su desfase respecto a la hora del sistema Windows. ERR indica el motivo del fallo y, si existe, su código. La última entrada de cada grupo de consultas también muestra el desfase calculado Θ cuando hay mediciones utilizables.

Los desfases se muestran en milisegundos con cuatro decimales. Un valor positivo indica que el reloj del servidor está adelantado respecto a Windows; uno negativo indica que está atrasado. Θ refleja las mediciones aceptadas y también aparece en el estado de sincronización.

Guardar registro exporta las entradas a CSV, incluidos los desfases y los detalles de los errores. Las entradas no se conservan entre sesiones; guárdelas antes de salir si desea conservarlas.

Los widgets de reloj admiten alarmas en días seleccionados individualmente; los siete días están activos por defecto. Una alarma hace visible su widget oculto y lo coloca delante de otras ventanas sin modificar permanentemente su opción de estar siempre encima. WAV, MP3, WMA, MIDI, AAC, M4A y FLAC se reconocen para reproducción interna única o repetida; la compatibilidad real depende de los componentes multimedia instalados en Windows. Los demás archivos y comandos se pasan a Windows de forma asíncrona. Una alarma también puede llamar a una URL HTTP o HTTPS. Independientemente de estas acciones, puede usar la señal de seis pitidos, cuyo primer pitido corto suena cinco segundos antes de la hora configurada.

Los pitidos de la alarma se programan según el instante real de la próxima alarma, tras convertir la zona horaria y aplicar el desfase del widget. Comienzan cinco segundos reales antes, incluso si el reloj mostrado salta directamente a la hora de la alarma. Una hora de alarma omitida en primavera no produce ni alarma ni pitidos. Durante la hora repetida en otoño, la alarma y sus pitidos suenan una sola vez para la misma fecha y hora configurada.

Prueba muestra la indicación visual y prueba asíncronamente el archivo, comando, audio y URL del script remoto. Si está seleccionada la señal horaria de alarma, reproduce también la secuencia completa de seis pitidos; Detener prueba termina el audio interno y la vista previa de señal.

La pestaña Señal incluye la casilla Señal horaria activa y botones de opción para intervalos de 1, 5, 10, 15, 20, 30 o 60 minutos según la hora mostrada por el widget. La señal está inicialmente desactivada y el intervalo seleccionado es de una hora. Desactivar y activar Señal en el menú del widget conserva el intervalo. El menú muestra la hora de la alarma y el intervalo de la señal entre paréntesis. El intervalo de 20 minutos señala :00, :20 y :40 de esa hora. El patrón es el **Greenwich Time Signal (GTS)**: cinco pitidos cortos marcan los últimos cinco segundos y uno más largo el límite exacto. Se respetan zona, UTC, desfases y corrección NTP actual. La señal de alarma y la pestaña Señal se configuran por separado; si sus horarios coinciden, CalClock reproduce una única secuencia compartida. Se respetan desfases fraccionarios, y los tonos superpuestos de widgets, alarmas y pruebas suenan continuamente hasta el fin del último solapamiento.

**Sonido de la señal horaria** en Aplicación permite elegir **Generador integrado** (predeterminado) o **Pitido del sistema**. Se aplica a todas las señales, incluidas las de alarma, y se guarda globalmente. Para el **Generador integrado**, **Volumen de la señal horaria** indica el nivel en dB para toda la aplicación. El extremo derecho es **0 dB**, la máxima amplitud sinusoidal sin distorsión; el silencio es **−∞ dB**. El valor predeterminado es **−18 dB**. El pitido actual termina normalmente; uno largo puede tardar hasta medio segundo. **Prueba**, junto a **Sonido de la señal horaria**, inicia una prueba continua; **Detener prueba** la finaliza. Ambos modos se pueden probar y el estado de la prueba no se guarda. Mantener pulsado el control de volumen también inicia una prueba hasta soltar el ratón, salvo si ya está activa la prueba por botón. La reproducción empieza en el siguiente segundo entero, con tonos cortos cada segundo y uno largo en :00, :05, :10, etc. La prueba y las señales simultáneas comparten un único tono. La elección de sonido está disponible únicamente si el sistema admite ambos modos.

La alarma y señal también se activan desde el menú contextual de cada widget con sonido. La entrada de alarma muestra su hora y, si no están seleccionados todos, sus días activos. Silenciado afecta al widget y coincide con la opción de General. Un Calendario independiente no admite alarma, señal horaria ni silencio. El comando del área de notificación es Silenciar todo; `M` sobre cualquier widget hace lo mismo. Desactivar la sordina global solo restaura los widgets silenciados por la acción global anterior. El audio interno continúa en silencio y vuelve a oírse al reactivarlo. Un pitido iniciado puede terminar; los siguientes se omiten hasta habilitar el sonido. Los comandos no sonoros y los scripts remotos no se ven afectados.

## Configuración y menús

Cada menú contiene los comandos pertinentes al tipo —visibilidad, siempre encima, segundos, tamaño analógico o formato de fecha copiada— y luego `Alinear en cuadrícula`, Configuración, Ayuda, Acerca de y Salir. El menú de notificación enumera los widgets con su número y ofrece Mostrar todo, Ocultar todo y Silenciar todo. `Alinear en cuadrícula` aparece en un grupo separado antes de los comandos de la aplicación.

Mostrar o restaurar widgets los sitúa delante de otras ventanas sin cambiar su opción de estar siempre encima. CalClock garantiza al menos un widget visible al inicio. Un segundo lanzamiento activa la instancia existente y restaura los widgets ocultados más recientemente si ninguno está visible. El icono de notificación se registra de nuevo automáticamente al reiniciar el Explorador Windows.

## Almacenamiento de ajustes

Los ajustes se guardan de forma predeterminada en:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

El almacenamiento XML se activa en Configuración y utiliza:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Importar un XML carga y guarda inmediatamente sus ajustes en el almacenamiento elegido sin cambiar el tipo. El silencio se guarda por cada widget con sonido.

## Compilación

Requisitos:

- Microsoft Visual Studio con el conjunto de herramientas MSVC v145
- Windows SDK

Abra `CalClock.slnx`, seleccione `Release | x86` y compile la solución. El ejecutable se crea como:

```text
Release\CalClock.exe
```

Solo se admite Win32/x86. El proyecto no proporciona deliberadamente una configuración x64, porque la integración con el control de reloj Windows requiere compatibilidad x86.

## Licencia

CalClock está disponible bajo la [licencia MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
