# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · **Français** · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md)

CalClock est une application native Win32/x86 pour Windows Vista et versions ultérieures qui affiche sur le bureau Windows des horloges et calendriers flottants configurables indépendamment. Elle fonctionne dans la zone de notification et ne nécessite pas de fenêtre de commande permanente.

## Fonctionnalités

- Jusqu’à 32 widgets configurables indépendamment
- Langue, fuseau horaire, décalage, visibilité et maintien au premier plan propres à chaque widget
- Horloges analogiques fondées sur le contrôle Windows `ClockWndMain`, avec détection des tailles disponibles et prise en charge de la trotteuse
- Horloges numériques avec polices, couleurs, opacité, marges intérieures, bordures, zéro initial facultatif et arrière-plan transparent facultatif
- Calendriers Windows natifs avec sélection de dates, quatre styles de bordure, couleur de bordure configurable, numéros de semaine, choix du premier jour et 33 formats de copie
- Panneaux calendrier et horloge avec jusqu’à deux horloges supplémentaires nommées dans des fuseaux indépendants, tailles de cadran distinctes, quatre styles de bordure, couleur configurable, texte UTC, zéro initial et police distincte pour chaque ligne de texte
- Alarmes avec choix des jours, indication visuelle, lecture audio interne, répétition, commandes locales et appels de scripts HTTP/HTTPS
- Signaux horaires propres à chaque horloge, toutes les 1, 5, 10, 15, 20, 30 ou 60 minutes, les signaux simultanés étant réunis en une seule séquence
- Commande Muet par horloge et commande à cocher Tout mettre en sourdine dans la zone de notification
- Démarrage automatique avec Windows facultatif
- Accrochage facultatif aux bords de la zone de travail dans un rayon de cinq pixels pendant le déplacement, activé par défaut ; l’attachement reste conservé lors du redimensionnement
- Synchronisation NTP sans modification de l’horloge système Windows
- Plusieurs préréglages NTP pour la Tchéquie et la Slovaquie, PTB, Ubuntu/NTP Pool ou des serveurs personnalisés
- Stockage des paramètres dans le Registre ou en XML, avec importation et exportation XML
- Commandes dans la zone de notification avec restauration des widgets masqués en dernier
- Identification des widgets et alignement stable sur une grille sans chevauchement
- Aperçu immédiat de l’apparence, annulation et restauration de l’apparence par défaut de chaque widget
- Polices de l’application et des widgets, styles visuels et lissage ClearType, GDI ou désactivé
- Interfaces en tchèque, anglais américain, britannique et australien, allemand, français, espagnol, italien, portugais, polonais, slovaque, danois, finnois, islandais, norvégien, suédois et turc

## Types de widgets

| Widget | Description |
| --- | --- |
| Horloge analogique | Cadran Windows flottant avec les tailles et la trotteuse facultative fournies par la version actuelle de Windows |
| Horloge numérique | Affichage numérique flottant configurable avec texte UTC, zéro initial, bordures et transparence facultatifs |
| Calendrier | Calendrier mensuel natif déplaçable avec sélection de date, bordures configurables et formats de copie |
| Calendrier et horloge | Panneau combinant calendrier natif, horloge analogique, lignes de texte configurables, affichage UTC et bordures |
| Horloge sur moniteur | Horloge numérique occupant un ou plusieurs moniteurs sélectionnés, avec obscurcissement facultatif et UTC sur une ligne distincte |

Au premier démarrage, CalClock choisit la langue selon celle de l’interface Windows et utilise l’anglais américain si elle n’est pas prise en charge. Une horloge analogique visible est créée par défaut. Chaque widget conserve sa position et ses paramètres entre les exécutions. Lorsque les Paramètres sont ouverts, une horloge sur moniteur est toujours représentée par un aperçu déplaçable aux proportions du moniteur sélectionné. `Esc` masque cette horloge et supprime son obscurcissement même lorsque les Paramètres sont actifs. Le pointeur disparaît après une courte inactivité au-dessus des horloges sur moniteur et des moniteurs obscurcis, puis réapparaît au mouvement de la souris. Il reste visible sur le petit aperçu des Paramètres.

## Commandes

- Déplacez une horloge ou un panneau avec le bouton gauche de la souris.
- Déplacez un calendrier indépendant en le saisissant dans une zone libre.
- Faites un clic droit sur un widget ou l’icône de notification pour ouvrir son menu contextuel.
- Un clic gauche sur l’icône de notification masque les widgets visibles. S’ils sont tous masqués, le clic suivant restaure uniquement ceux masqués en dernier.
- Un double-clic sur un cadran active ou désactive les secondes. Dans un panneau calendrier et horloge, seul un double-clic directement sur le cadran principal bascule la trotteuse. Les horloges supplémentaires n’en ont pas.
- `F1` ouvre l’Aide, `B` les Paramètres, `M` bascule la sourdine globale et `Esc` masque un widget ou arrête une alarme active.
- Appuyez sur `Alt+0`, `Alt+1`, `Alt+2` ou `Alt+3` dans les widgets Horloge analogique et Calendrier avec horloge pour choisir la taille du cadran principal, de la plus petite à la plus grande.
- Un double-clic sur un widget dans les Paramètres le rend visible si nécessaire, coche `Visible` et le repère brièvement sur le bureau.
- Ouvrir les Paramètres depuis le menu contextuel d’un widget sélectionne immédiatement celui-ci.
- Utilisez `Ctrl` ou `Shift` pour une sélection multiple, `Ctrl+A` pour tout sélectionner et `Del` pour retirer la sélection. `Insert` bascule l’état de sélection de l’élément courant et avance le curseur de liste d’une ligne, comme dans Total Commander.
- Tous les raccourcis de la liste fonctionnent aussi lorsque le bouton Retirer ou Dupliquer a le focus. Le raccourci transfère le focus à la liste et exécute l’action. `Ctrl+C` copie les widgets sélectionnés ; `Ctrl+V` ajoute leurs copies à la fin dans l’ordre de la liste. Les copies reprennent tous les paramètres et reçoivent un suffixe de nom dans la langue de l’application. Dupliquer effectue directement la même opération. La limite est de 32 widgets. Si toutes les copies ne tiennent pas, celles qui tiennent sont ajoutées dans l’ordre et un message signale les autres.
- `Ctrl+A` ou un triple-clic dans un champ de texte sélectionne tout son contenu.

Si plusieurs widgets sont sélectionnés, leurs contrôles Général, Apparence, Alarme et Signal sont désactivés ; les onglets globaux Heure et Application restent disponibles. Les Paramètres mémorisent le dernier onglet ouvert et le dernier type de widget ajouté. Sur une petite zone de travail, la fenêtre propose un défilement horizontal ou vertical selon les besoins.

Les dates du calendrier se copient dans 33 formats : locaux, triables, jour ou mois en premier, textuels et avec jour de la semaine. Chaque masque est disponible dans chaque langue d’interface. Le format court local par défaut suit la langue du widget ; les noms de mois et de jours aussi. Les entrées présentent le masque et un exemple actualisé.

Un panneau calendrier et horloge peut afficher jusqu’à deux horloges supplémentaires. Activez chacune dans Général et choisissez son nom et son fuseau. Les fuseaux nommés suivent leurs propres règles d’heure d’été ; les décalages UTC fixes restent constants. Quand les horloges supplémentaires sont activées, chaque horloge affiche son jour local sous l’heure. Les trois listes de taille d’Apparence commandent, dans l’ordre, l’horloge principale, Horloge 1 et Horloge 2. Un clic droit sur un cadran supplémentaire permet d’en choisir la taille. Ces horloges n’affichent jamais les secondes et partagent langue, format horaire, polices et décalage du widget. Ajouter, retirer ou redimensionner les horloges conserve l’attachement aux mêmes bords de la zone de travail.

Dans ce panneau, la date supérieure est un lien ramenant le calendrier à aujourd’hui ; le texte de fuseau inférieur ouvre les paramètres classiques Date et heure de Windows. Les deux liens sont accessibles avec `Tab`, affichent un rectangle de focus et s’activent au clavier. Le calendrier natif reste entièrement interactif, mais omet sa ligne Aujourd’hui devenue redondante dans cette disposition.

`Aligner sur la grille` place les widgets de bureau visibles sur une grille stable sans chevauchement en préservant approximativement leur disposition manuelle. Le widget ayant lancé la commande depuis son menu reste en place ; la commande de la zone de notification traite chaque moniteur indépendamment. Les horloges sur moniteur sont exclues.

## Apparence

Pour les calendriers indépendants, **Ligne Aujourd’hui**, dans le menu du widget ou l’onglet Apparence, contrôle la ligne du bas. Elle est cochée par défaut ; la décocher masque la ligne et réduit le calendrier. Le choix est enregistré par widget. **Aller à aujourd’hui** reste disponible dans le menu et revient à la vue mensuelle. Au changement de date selon l’heure propre au widget, le calendrier sélectionne automatiquement aujourd’hui tout en conservant la vue actuelle.

Les modifications d’apparence sont immédiatement prévisualisées sur le widget sélectionné. `Annuler` restaure les changements non appliqués ; `Apparence par défaut` rétablit les valeurs par défaut du type de widget.

Horloges numériques, calendriers et panneaux combinés partagent quatre styles de bordure. Le style simple possède une couleur configurable ; la largeur est réglable lorsque le widget la prend en charge. Les horloges numériques transparentes proposent les mêmes styles que les opaques. Les dialogues de police n’affichent que les choix utiles et omettent aperçu et effets inutilisés ; les polices de l’application et du calendrier excluent la taille, celles des horloges numériques et textes du panneau l’incluent. Un calendrier natif n’accepte une police personnalisée que si ses styles visuels, ou ceux de l’application, sont désactivés.

La langue de l’application, la police d’interface, le lissage, les styles visuels, le stockage, le démarrage Windows et l’accrochage aux bords sont globaux et se règlent dans Application. La source horaire est également globale. Langue du widget, lissage, styles, fuseau, décalage, alarme et signal horaire se règlent indépendamment. Appliquer une nouvelle langue recrée immédiatement la fenêtre Paramètres ouverte dans cette langue. Le lissage propose **ClearType**, **GDI** et **Aucun**. Dans Apparence, le lissage et la désactivation des thèmes occupent la même position pour tous les types de widget, avec **Apparence par défaut** au-dessous.

Le curseur **Volume audio** de l’onglet Alarme règle les fichiers lus en interne séparément pour chaque widget et indique le niveau en dB. La valeur par défaut **−18 dB** conserve le niveau d’origine du fichier (**100%**). Vers la droite, le son est amplifié ; le maximum **0 dB** correspond à environ **794%** de l’amplitude initiale. Tout à gauche, **−∞ dB** signifie silence. Les modifications s’appliquent pendant le test audio. Le curseur est désactivé pour les fichiers ouverts dans une application externe. L’amplification concerne l’audio décodé, dont WAV, MP3, WMA, AAC, M4A et FLAC si Windows les prend en charge. L’ancienne lecture de fichiers non décodables, comme MIDI, est limitée à 100%.

Les jours d’alarme suivent le premier jour de semaine de la culture sélectionnée pour l’application. Les jours enregistrés gardent leur signification après un changement de langue. Activer une alarme par le menu sans aucun jour sélectionné ouvre l’onglet Alarme correspondant au lieu d’activer une alarme incapable de se déclencher.

La largeur de bordure par défaut des horloges numériques est nulle. **Zéro initial** propose **Afficher** (par défaut), **Réserver l’espace** et **Sans espace**. **Réserver l’espace** masque le zéro en conservant sa largeur réelle dans la police choisie ; les autres chiffres gardent ainsi leur position même en police proportionnelle. Les horloges numériques flottantes alignent l’heure à gauche et gardent une taille fixe pendant l’écoulement du temps. Les horloges sur moniteur centrent une zone horaire fixe dimensionnée pour la police et le format choisis, avec deux chiffres pour l’heure. Les changements d’heure ne recentrent ni ne redimensionnent le texte. La ligne AM/PM ou UTC reste centrée indépendamment. Les horloges sur moniteur affichent par défaut du texte blanc sur fond noir.

## Heure et alarmes

Les horloges numériques, panneaux calendrier et horloge et horloges sur moniteur proposent **Selon la langue**, **12 heures** et **24 heures** sous **Format horaire** dans Général. **Selon la langue** est la valeur par défaut : l’anglais américain et australien utilisent par exemple 12 heures, le britannique 24 heures. Un choix manuel reste conservé lors du changement de langue du widget. Séparateurs et indicateurs AM/PM suivent la culture choisie ; les cultures sans indicateurs propres utilisent **AM/PM** en mode 12 heures.

La case **AM/PM** est cochée par défaut. La décocher masque l’indicateur sans modifier le cycle de 12 heures. Elle est désactivée en mode 24 heures et pour les widgets sans heure numérique. Les horloges sur moniteur affichent l’indicateur sur une ligne séparée sous l’heure, comme UTC. **UTC utilise toujours 24 heures** ; les contrôles du cycle et d’AM/PM sont désactivés en UTC et leurs valeurs sont conservées pour le retour à l’heure locale. Le réglage du zéro initial continue de déterminer s’il est visible, masqué avec espace réservé ou omis.

Les fuseaux nommés affichent l’heure civile du lieu sélectionné et suivent automatiquement ses règles d’heure d’été. Le décalage auprès de chaque nom correspond à la date actuelle et est actualisé à l’ouverture de la liste. Les entrées **UTC** indépendantes offrent des décalages fixes de **UTC−12:00** à **UTC+14:00** par pas de 15 minutes, sans heure d’été. Choisissez indépendamment pour chaque widget votre fuseau local, tout autre fuseau nommé ou un décalage UTC fixe.

Chaque widget peut utiliser n’importe quel fuseau Windows et un décalage signé au format `[-]HH:mm:ss.ff`. Une saisie compacte est interprétée depuis la droite, en commençant par les secondes.

Le décalage est utile notamment dans un studio de diffusion pour compenser le retard de la chaîne de transmission. Avancer l’horloge du studio du retard mesuré permet à son signal horaire d’atteindre les auditeurs au moment voulu.

CalClock utilise soit l’heure système Windows, soit une correction locale à l’application obtenue auprès de serveurs NTP. Ce choix est global. La synchronisation ne change jamais l’horloge Windows. Si la connexion NTP est perdue après une synchronisation réussie, la dernière correction reste active en mémoire du processus. Changer de serveurs conserve aussi la correction valide jusqu’à réception d’une nouvelle réponse.

Les widgets d’horloge prennent en charge les alarmes par jour de semaine ; les sept jours sont activés par défaut. Une alarme rend son widget masqué visible et le place devant les autres fenêtres sans modifier durablement son maintien au premier plan. WAV, MP3, WMA, MIDI, AAC, M4A et FLAC sont reconnus pour la lecture interne unique ou en boucle ; le décodage réel dépend des composants multimédias installés dans Windows. Les autres fichiers et commandes sont transmis à Windows de manière asynchrone. Une alarme peut aussi appeler une URL HTTP ou HTTPS. Indépendamment de ces actions, elle peut utiliser le signal à six bips dont le premier bip court sonne cinq secondes avant l’heure programmée.

Exécuter un fichier ou une commande active son champ, Parcourir, Test et la répétition. Test et répétition nécessitent aussi un champ non vide ; un test en cours peut toujours être arrêté. Test prévisualise l’indication visuelle et teste de façon asynchrone le fichier, la commande, l’audio et l’URL du script distant. Si le signal horaire d’alarme est sélectionné, Test joue aussi sa séquence complète de six bips ; Arrêter le test termine l’audio interne et l’aperçu du signal.

L’onglet Signal propose la case Signal horaire actif et des boutons radio pour les intervalles de 1, 5, 10, 15, 20, 30 ou 60 minutes selon l’heure affichée par le widget. Le signal est initialement désactivé, avec un intervalle d’une heure sélectionné. Désactiver puis réactiver Signal dans le menu du widget conserve l’intervalle. Le menu affiche l’heure de l’alarme et l’intervalle du signal entre parenthèses. L’intervalle de 20 minutes sonne à :00, :20 et :40 de cette heure. Le motif est celui du **Greenwich Time Signal (GTS)** : cinq bips courts marquent les cinq dernières secondes et un bip plus long la limite exacte. Fuseaux, UTC, décalages et correction NTP sont respectés. Le signal d’alarme et l’onglet Signal restent indépendants ; si des échéances coïncident, CalClock ne joue qu’une séquence commune. Les fractions de seconde des décalages sont prises en compte. Les tons de widgets, alarmes et tests qui se chevauchent sont continus jusqu’à la fin du dernier chevauchement.

**Son du signal horaire** dans Application propose **Générateur intégré** (par défaut) et **Bip système**. Le choix concerne tous les signaux de widgets, y compris les alarmes, et s’enregistre globalement. Pour le **Générateur intégré**, **Volume du signal horaire** indique le niveau en dB pour toute l’application. L’extrémité droite est **0 dB**, amplitude sinusoïdale maximale sans distorsion ; le silence est **−∞ dB**. La valeur par défaut est **−18 dB**. L’échelle en décibels place −18 dB au milieu. Le générateur commence et termine les tons au passage par zéro, y compris lors de l’arrêt d’un test. Le bip en cours se termine normalement ; un bip long peut prendre jusqu’à une demi-seconde. **Test**, à côté de **Son du signal horaire**, lance l’aperçu continu ; **Arrêter le test** l’arrête. Les deux modes sont testables et l’état du test n’est pas enregistré. Maintenir le curseur de volume lance aussi un aperçu jusqu’au relâchement de la souris, sauf si le test par bouton est actif. La lecture commence à la prochaine seconde entière, avec un ton court chaque seconde et un long à :00, :05, :10, etc. L’aperçu et les signaux simultanés des widgets ou alarmes partagent un seul ton. Seul le volume est désactivé pour le **Bip système**. Le choix du son n’est disponible que si le système prend en charge les deux modes.

L’alarme et le signal horaire peuvent aussi être activés dans le menu contextuel de tout widget sonore. L’entrée d’alarme montre son heure et, sauf si tous sont sélectionnés, ses jours actifs. Muet agit sur son widget et correspond à la case de Général. Un Calendrier indépendant ne possède ni alarme, ni signal, ni état muet : les commandes correspondantes sont omises ou désactivées. La commande de notification Tout mettre en sourdine est également accessible avec `M` sur un widget. La réactivation globale ne restaure que les widgets mis en sourdine par l’action globale précédente. L’audio interne continue silencieusement et redevient audible ensuite. Un bip déjà commencé peut se terminer ; les suivants sont ignorés jusqu’à réactivation du son. Les commandes non audio et scripts distants ne sont pas affectés.

## Paramètres et menus

`Enregistrer` applique les modifications et ferme les Paramètres ; `Appliquer` les applique en gardant la fenêtre ouverte ; `Annuler` abandonne les modifications non appliquées, y compris l’aperçu de l’apparence. Entrée active `Enregistrer` et Échap `Annuler`.

Chaque menu de widget contient les commandes adaptées au type — visibilité, premier plan, secondes, taille analogique ou format de copie de date — puis `Aligner sur la grille`, Paramètres, Aide, À propos et Quitter. Le menu de notification énumère les widgets avec leur numéro, puis Tout afficher, Tout masquer et Tout mettre en sourdine. La commande `Aligner sur la grille`, séparée des autres groupes, précède les commandes de l’application.

Afficher ou restaurer des widgets les place devant les autres fenêtres sans modifier leur maintien au premier plan. CalClock garantit au moins un widget visible au démarrage. Un second lancement active l’instance existante et restaure les widgets masqués en dernier si aucun n’est visible. L’icône de notification est réenregistrée automatiquement après un redémarrage de l’Explorateur Windows. Si `ClockWndMain` ne prend pas en charge la trotteuse à la taille choisie, Secondes est désactivé, mais le choix reste mémorisé pour une autre taille compatible.

## Stockage des paramètres

Par défaut, les paramètres sont enregistrés sous :

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

Le stockage XML s’active dans les Paramètres et utilise :

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Après l’écriture réussie du XML, CalClock supprime son état du Registre. Revenir au Registre supprime de même le fichier XML automatique et les dossiers CalClock vides. Importer un XML charge et enregistre immédiatement ses paramètres dans le stockage actuellement choisi sans en changer le type. L’état muet est enregistré par widget sonore. Le démarrage avec Windows est enregistré comme valeur `CalClock` dans la clé Windows standard `Run` de l’utilisateur actuel.

## Compilation

Prérequis :

- Microsoft Visual Studio avec les outils MSVC v145
- Windows SDK

Ouvrez `CalClock.slnx`, sélectionnez `Release | Win32` et compilez la solution. L’exécutable est créé sous :

```text
Release\CalClock.exe
```

Seule la configuration Win32/x86 est prise en charge. Le projet ne fournit volontairement pas de configuration x64, car l’intégration du contrôle d’horloge Windows exige la compatibilité x86.

## Licence

CalClock est disponible sous [licence MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
