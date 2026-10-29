# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · **Português** · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Türkçe](README.tr-TR.md) · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

O CalClock é uma aplicação nativa Win32/x86 para Windows Vista e versões posteriores que apresenta relógios e calendários flutuantes configuráveis individualmente no ambiente de trabalho. Funciona na área de notificação e não exige uma janela de controlo permanente.

## Funcionalidades

- Até 32 widgets configuráveis individualmente
- Idioma, fuso horário, desvio de hora, visibilidade e estado sempre no topo por widget
- Relógios analógicos baseados no controlo Windows `ClockWndMain`, com deteção dos tamanhos disponíveis e suporte para o ponteiro dos segundos
- Relógios digitais com tipos de letra, cores, opacidade, margens interiores, contornos, zero inicial opcional e fundo transparente opcional
- Calendários nativos do Windows com seleção de datas, quatro estilos de contorno, cor configurável, números de semana, escolha do primeiro dia e 33 formatos de cópia
- Painéis de calendário e relógio com até dois relógios adicionais com nome e fusos independentes, tamanhos separados de mostrador, quatro estilos de contorno, cor configurável, texto UTC, zero inicial e tipo de letra próprio para cada linha de texto
- Alarmes com seleção de dias, indicação visual, reprodução interna de áudio, repetição, comandos locais e chamadas a scripts HTTP/HTTPS
- Sinais horários por relógio a cada 1, 5, 10, 15, 20, 30 ou 60 minutos; sinais coincidentes são unidos numa sequência
- Comando Sem som por relógio e comando selecionável Silenciar tudo na área de notificação
- Arranque automático com o Windows opcional
- Encaixe opcional nas margens da área de trabalho ao arrastar, dentro de cinco píxeis e ativo por predefinição; a ligação à margem mantém-se ao redimensionar
- Sincronização NTP sem alterar o relógio do sistema Windows
- Predefinições NTP para a Chéquia e Eslováquia, PTB, Ubuntu/NTP Pool ou servidores personalizados
- Definições no Registo ou em XML, com importação e exportação XML
- Controlos na área de notificação que restauram os widgets ocultados mais recentemente
- Identificação dos widgets e alinhamento estável numa grelha sem sobreposições
- Pré-visualização imediata do aspeto com cancelamento e reposição dos valores predefinidos por widget
- Tipos de letra da aplicação e dos widgets, estilos visuais e suavização ClearType, GDI ou nenhuma
- Interface em 36 variantes de idioma, com seleção independente para a aplicação e cada widget

## Tipos de widget

| Widget | Descrição |
| --- | --- |
| Relógio analógico | Mostrador flutuante do Windows com os tamanhos e ponteiro dos segundos opcional fornecidos pela versão atual do Windows |
| Relógio digital | Visor digital flutuante configurável com texto UTC, zero inicial, contornos e fundo transparente opcionais |
| Calendário | Calendário mensal nativo móvel com seleção de datas, contornos configuráveis e formatos de cópia |
| Calendário com relógio | Painel combinado com calendário nativo, relógio analógico, linhas de texto configuráveis, UTC e contornos |
| Relógio no monitor | Relógio digital que ocupa um ou mais monitores selecionados, com escurecimento opcional e UTC numa linha separada |

No primeiro arranque, o CalClock escolhe o idioma da interface do Windows e usa inglês dos EUA se não for suportado. Cria um relógio analógico visível por predefinição. Cada widget conserva a posição e as definições entre execuções. Enquanto as Definições estão abertas, um relógio no monitor é representado por uma pré-visualização móvel com as proporções do monitor selecionado. `Esc` oculta esse relógio e elimina o escurecimento, mesmo com as Definições ativas. O ponteiro desaparece após uma breve inatividade sobre os relógios no monitor e monitores escurecidos, reaparecendo quando o rato se move. Permanece visível sobre a pequena pré-visualização das Definições.

## Controlos

- Arraste um relógio ou painel com o botão esquerdo do rato.
- Arraste um calendário independente pela sua área livre.
- Clique com o botão direito num widget ou no ícone de notificação para abrir o menu de contexto.
- Um clique esquerdo no ícone de notificação oculta os widgets visíveis. Se todos estiverem ocultos, outro clique restaura apenas os ocultados mais recentemente.
- Faça duplo clique num mostrador para alternar os segundos. Num painel de calendário com relógio, só o duplo clique diretamente no mostrador principal alterna o ponteiro dos segundos. Os relógios adicionais não têm esse ponteiro.
- `F1` abre a Ajuda, `B` as Definições, `M` alterna Silenciar tudo e `Esc` oculta um widget ou para um alarme ativo.
- Prima `Alt+0`, `Alt+1`, `Alt+2` ou `Alt+3` nos widgets Relógio analógico e Calendário com relógio para escolher o tamanho do mostrador principal, do menor ao maior.
- Um duplo clique num widget das Definições torna-o visível se necessário, seleciona `Visível` e identifica-o brevemente no ambiente de trabalho.
- Abrir as Definições pelo menu de um widget seleciona-o imediatamente.
- Delete remove os widgets selecionados. `Insert` alterna a seleção do item atual e desloca o cursor da lista uma linha para baixo.
- `Ctrl+C` copia os widgets selecionados e `Ctrl+V` acrescenta as cópias pela ordem da lista. As cópias incluem todas as definições e recebem um sufixo no idioma da aplicação. Duplicar executa diretamente a mesma operação. São permitidos até 32 widgets. Se não houver espaço para todas as cópias, são acrescentadas as que cabem, por ordem, e é apresentado um aviso sobre as restantes.

Ao abrir as definições pelo ícone da área de notificação, é selecionado o último widget escolhido.

As Definições recordam o último separador aberto e o último tipo de widget adicionado.

As datas podem ser copiadas em 33 formatos locais, ordenáveis, com dia ou mês primeiro, textuais e com dia da semana. Todas as máscaras estão disponíveis em todos os idiomas. O formato curto local predefinido segue o idioma do widget, tal como os nomes de meses e dias. As entradas mostram a máscara e um exemplo atualizado.

Um painel de calendário com relógio pode apresentar até dois relógios adicionais. Ative cada um em Geral e escolha o nome e o fuso. Os fusos com nome seguem as suas próprias regras de hora de verão; os desvios UTC fixos mantêm-se constantes. Com relógios adicionais ativos, cada relógio apresenta o seu dia local sob a hora. As três listas de tamanho em Aspeto controlam, por ordem, o relógio principal, Relógio 1 e Relógio 2. Um clique direito num mostrador adicional permite escolher o tamanho. Estes relógios omitem sempre os segundos e partilham idioma, formato, tipos de letra e desvio do widget. Adicionar, remover ou redimensionar relógios mantém o widget ligado às mesmas margens da área de trabalho.

Neste painel, a data superior é uma ligação que leva o calendário a hoje; o texto inferior do fuso abre as definições clássicas de Data e hora do Windows.

Os painéis de calendário e relógio podem apresentar os avisos de data e hora do Windows acima da ligação inferior. A opção **Avisos de data e hora** no separador **Geral** está ativada por predefinição e é guardada separadamente para cada painel. Quando se aplicam vários avisos, estes aparecem uns por baixo dos outros, como no Windows. Se a opção estiver desativada ou não houver avisos aplicáveis, o painel mantém o tamanho e a disposição originais, sem reservar espaço vazio.

`Alinhar na grelha` coloca os widgets visíveis numa grelha estável sem sobreposições, preservando aproximadamente a disposição manual. O widget cujo menu invocou o comando permanece no lugar; o comando da área de notificação organiza cada monitor separadamente. Os relógios no monitor são excluídos.

## Aspeto

Nos calendários independentes, **Linha Hoje**, no menu ou em Aspeto, controla a linha inferior. Está selecionada por predefinição; desmarcá-la oculta a linha e reduz o calendário. A escolha é guardada por widget. **Ir para hoje** continua disponível no menu e regressa à vista mensal. Quando a data muda segundo a hora do widget, o calendário seleciona hoje automaticamente, mantendo a vista atual.

As alterações de aspeto são imediatamente pré-visualizadas no widget selecionado. `Aspeto predefinido` repõe os valores predefinidos desse tipo de widget. Ao fechar as definições com alterações não aplicadas, é perguntado se pretende guardá-las. Este aviso está ativado por predefinição e pode ser desativado no separador Aplicação.

Relógios digitais, calendários e painéis partilham quatro estilos de contorno. O estilo simples também permite escolher a cor; a largura é configurável quando o widget a suporta. Os relógios digitais transparentes oferecem os mesmos estilos que os opacos. Para aplicação e calendário não incluem tamanho; para relógios digitais e texto do painel incluem. Os tipos de letra personalizados do calendário são suportados com o aspeto clássico do Windows ou com os temas desativados para a aplicação ou o widget.

Idioma da aplicação, tipo de letra da interface, suavização, estilos visuais, armazenamento, arranque com Windows e encaixe às margens são globais e configurados em Aplicação. A origem da hora também é global. Idioma do widget, suavização, estilos, fuso, desvio, alarme e sinal horário são independentes. A suavização oferece **ClearType**, **GDI** e **Nenhuma**.

O controlo **Volume do áudio** em Alarme regula os ficheiros reproduzidos internamente por widget e apresenta o nível em dB. A predefinição **−18 dB** mantém o nível original do ficheiro (**100%**). Para a direita amplifica o áudio; o máximo **0 dB** corresponde a cerca de **794%** da amplitude original. O extremo esquerdo é **−∞ dB** (silêncio). As alterações aplicam-se durante o teste. A amplificação aplica-se a áudio descodificado, incluindo WAV, MP3, WMA, AAC, M4A e FLAC quando suportados pelo Windows. A reprodução antiga de ficheiros que não podem ser descodificados, como MIDI, está limitada a 100%.

Os dias do alarme seguem o primeiro dia da semana da cultura escolhida para a aplicação. Os dias guardados conservam o significado ao mudar o idioma. Ativar pelo menu um alarme sem dias selecionados abre o respetivo separador Alarme em vez de ativar um alarme que não pode tocar.

**Zero à esquerda** oferece **Sim** (predefinido), **Não, reservar espaço** e **Não, sem espaço**. **Não, reservar espaço** oculta o zero mantendo a sua largura real no tipo de letra escolhido, para que os restantes algarismos não se movam mesmo com tipos proporcionais. Os relógios no monitor usam texto branco sobre fundo preto por predefinição.

## Hora e alarmes

Relógios digitais, painéis de calendário com relógio e relógios no monitor oferecem **Conforme o idioma**, **12 horas** e **24 horas** em **Formato da hora** de Geral. **Conforme o idioma** é a predefinição: inglês dos EUA e australiano usam, por exemplo, 12 horas, e britânico usa 24. A escolha manual mantém-se ao mudar o idioma do widget. Separadores e indicadores AM/PM seguem a cultura; culturas sem indicadores próprios usam **AM/PM** no modo de 12 horas.

**AM/PM** está selecionado por predefinição. Desmarcá-lo oculta o indicador sem alterar o ciclo de 12 horas. Os relógios no monitor mostram o indicador numa linha separada sob a hora, como UTC. UTC usa sempre o formato de 24 horas. O zero inicial continua visível, oculto com espaço reservado ou omitido conforme a sua definição.

Os fusos com nome apresentam a hora civil do local e seguem automaticamente as suas regras de hora de verão. O desvio junto ao nome corresponde à data atual e é atualizado ao abrir a lista. As entradas **UTC** independentes oferecem desvios fixos de **UTC−12:00** a **UTC+14:00**, em passos de 15 minutos, sem hora de verão. Cada widget pode escolher o fuso local, qualquer outro fuso com nome ou um desvio UTC fixo de forma independente.

Os novos widgets usam por predefinição **Fuso horário atual do Windows**, que acompanha o fuso horário atual do Windows e a definição automática da hora de verão. Os widgets existentes mantêm o fuso escolhido. Esta opção determina o fuso horário; a fonte de tempo partilhada, Windows ou NTP, permanece independente.

Cada widget pode usar qualquer fuso do Windows e um desvio com sinal no formato `[-]HH:mm:ss.ff`. A entrada compacta é interpretada da direita para a esquerda, começando pelos segundos.

O desvio é útil, por exemplo, em estúdios de radiodifusão para compensar o atraso do percurso de transmissão. Adiantar o relógio do estúdio pelo atraso medido permite que o sinal horário chegue aos ouvintes no momento previsto.

O desvio do widget é aplicado a UTC antes da conversão para o seu fuso horário, pelo que também desloca o instante da mudança de hora. Um relógio adiantado dez segundos muda dez segundos mais cedo; um relógio atrasado dez segundos muda dez segundos mais tarde. Os ponteiros, a indicação digital, as datas do calendário, os alarmes e os sinais horários usam a hora resultante.

O separador Hora escolhe para toda a aplicação a hora do Windows ou servidores NTP. O NTP corrige apenas o CalClock e nunca altera o Windows. A predefinição é NTP; o conjunto automático escolhe servidores pela região e filtra medições por atraso e valores atípicos.

Após a sincronização, o relógio do CalClock continua a funcionar independentemente de alterações posteriores à hora do sistema Windows. Se a ligação falhar ou os servidores forem alterados, continua a partir da última sincronização válida até receber uma nova resposta; este estado mantém-se até fechar a aplicação.

O separador Hora regista as consultas a servidores NTP desde o início da aplicação. Cada entrada contém a data e hora local do computador, o servidor e o estado. OK identifica uma resposta válida e θ o seu desvio em relação à hora do Windows. ERR indica a causa da falha e o eventual código de erro. A última entrada de um grupo de consultas mostra também o desvio calculado Θ quando existem medições utilizáveis.

Os desvios são apresentados em milissegundos com quatro casas decimais. Um valor positivo significa que o relógio do servidor está adiantado em relação ao Windows; um valor negativo significa que está atrasado. Θ reflete as medições aceites e também aparece no estado da sincronização.

Guardar registo exporta as entradas para CSV, incluindo desvios e detalhes das falhas. As entradas não são conservadas entre sessões; guarde-as antes de sair se quiser mantê-las.

Os widgets de relógio permitem alarmes por dias escolhidos individualmente; os sete dias estão ativos por predefinição. Um alarme torna visível o seu widget oculto e coloca-o à frente de outras janelas sem alterar permanentemente o estado sempre no topo. WAV, MP3, WMA, MIDI, AAC, M4A e FLAC são reconhecidos para reprodução interna única ou repetida; o suporte efetivo depende dos componentes multimédia instalados no Windows. Outros ficheiros e comandos são passados ao Windows de forma assíncrona. Um alarme pode também chamar um URL HTTP ou HTTPS. Independentemente, pode usar o sinal de seis tons cujo primeiro tom curto toca cinco segundos antes da hora definida.

Os sinais sonoros do alarme são agendados a partir do instante real do próximo alarme, após a conversão do fuso e a aplicação do desvio do widget. Começam cinco segundos reais antes desse instante, mesmo quando o relógio apresentado salta diretamente para a hora do alarme. Uma hora de alarme omitida na primavera não ativa o alarme nem os sinais. Durante a hora repetida no outono, o alarme e os seus sinais ocorrem apenas uma vez para a mesma data e hora configurada.

Teste mostra a indicação visual e testa de forma assíncrona ficheiro, comando, áudio e URL do script remoto. Se o sinal horário do alarme estiver selecionado, reproduz também os seis tons completos; Parar teste termina o áudio interno e a pré-visualização do sinal.

O separador Sinal contém a caixa Sinal horário ativo e botões de opção para intervalos de 1, 5, 10, 15, 20, 30 ou 60 minutos segundo a hora apresentada pelo widget. Inicialmente, o sinal está desativado e está selecionado o intervalo de uma hora. Desativar e ativar Sinal no menu do widget mantém o intervalo. O menu mostra a hora do alarme e o intervalo do sinal entre parênteses. O intervalo de 20 minutos toca a :00, :20 e :40 dessa hora. O padrão é o **Greenwich Time Signal (GTS)**: cinco tons curtos marcam os últimos cinco segundos e um mais longo o limite exato. São respeitados fusos, UTC, desvios e correção NTP atual. O sinal do alarme e o separador Sinal permanecem independentes. São respeitados desvios fracionários, e os tons sobrepostos de widgets, alarmes e testes continuam sem interrupção até terminar a última sobreposição na mesma saída de áudio.

**Som do sinal horário** em Aplicação permite escolher **Gerador integrado** (predefinido) ou **Sinal sonoro do sistema**. A escolha aplica-se a todos os sinais, incluindo os dos alarmes, e é guardada globalmente. No **Gerador integrado**, **Volume do sinal horário** mostra o nível em dB para toda a aplicação. À direita fica **0 dB**, a amplitude sinusoidal máxima sem distorção; silêncio é **−∞ dB**. O valor predefinido é **−18 dB**. A escala em decibéis tem −18 dB a meio. O gerador inicia e termina tons na passagem por zero, também ao parar um teste. O tom atual termina normalmente; um tom longo pode demorar até meio segundo. **Testar**, junto de **Som do sinal horário**, inicia a pré-visualização contínua; **Parar teste** termina-a. Ambos os modos podem ser testados e o estado do teste não é guardado. Manter premido o controlo de volume também inicia uma pré-visualização até soltar o rato, exceto se o teste pelo botão estiver ativo. A reprodução começa no próximo segundo inteiro, com tons curtos a cada segundo e um longo a :00, :05, :10, etc. A escolha só está disponível quando o sistema suporta ambos os modos.

**Saída de áudio**

**Saída de áudio** no separador **Sinal** seleciona o dispositivo para os sinais horários regulares de cada widget com
som. O fuso horário, o desvio e o intervalo do widget não são alterados. A escolha do gerador e o volume continuam a
ser globais no separador **Aplicação**. Com **Sinal sonoro do sistema**, o seletor permanece visível mas desativado e
conserva o dispositivo escolhido; **Gerador integrado** volta a ativá-lo. O Windows Vista utiliza automaticamente o
gerador.

**Dispositivo predefinido do Windows** acompanha a saída predefinida atual do Windows. Um dispositivo escolhido
explicitamente mantém-se selecionado após ser desligado e aparece como **Dispositivo indisponível**; os seus sinais
ficam em silêncio até estar disponível ou ser escolhida outra saída. A lista de dispositivos é atualizada ao abrir. A
seleção é guardada separadamente para cada widget no Registo ou nas definições XML.

Os sinais são combinados automaticamente por saída. Um dispositivo escolhido explicitamente e **Dispositivo
predefinido do Windows** que indique esse mesmo dispositivo partilham uma saída. Dispositivos diferentes funcionam de
forma independente; mantêm-se a onda sinusoidal, a continuidade de fase e o início e fim dos tons em zero. Os alarmes,
incluindo os ficheiros reproduzidos internamente e os sinais que os antecedem, e todos os testes continuam a utilizar
a saída predefinida do Windows. Só se combinam com sinais regulares numa saída comum.

Alarmes e sinais também podem ser ativados no menu contextual de cada widget com som. A entrada do alarme mostra a hora e, salvo se todos estiverem selecionados, os dias ativos. Sem som afeta o widget e corresponde à opção em Geral. Um Calendário autónomo não suporta alarme, sinal horário nem silenciamento. Na área de notificação existe Silenciar tudo; `M` em qualquer widget executa a mesma alternância global. A reativação global restaura apenas widgets silenciados pela ação global anterior. O áudio interno continua silenciosamente e volta a ouvir-se ao reativar. Um tom já iniciado pode terminar; os seguintes são ignorados até reativar o som. Comandos não sonoros e scripts remotos não são afetados.

## Definições e menus

Cada menu contém os comandos pertinentes ao tipo — visibilidade, sempre no topo, segundos, tamanho analógico ou formato da data copiada — seguidos de `Alinhar na grelha`, Definições, Ajuda, Acerca de e Sair. O menu de notificação enumera todos os widgets com o seu número e oferece Mostrar tudo, Ocultar tudo e Silenciar tudo. `Alinhar na grelha` surge num grupo separado antes dos comandos da aplicação.

Mostrar ou restaurar widgets coloca-os à frente das outras janelas sem alterar o estado sempre no topo. O CalClock garante pelo menos um widget visível ao iniciar. Um segundo arranque ativa a instância existente e restaura os widgets ocultados mais recentemente se nenhum estiver visível. O ícone de notificação é registado novamente de forma automática após o reinício do Explorador do Windows. Se `ClockWndMain` não suportar ponteiro dos segundos no tamanho selecionado, Segundos fica desativado, mas a escolha é conservada para outro tamanho compatível.

## Armazenamento das definições

Por predefinição, as definições são guardadas em:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

O armazenamento XML pode ser ativado nas Definições e usa:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

Importar XML carrega e guarda imediatamente as definições no armazenamento escolhido sem alterar o tipo. O estado sem som é guardado por widget sonoro.

## Compilação

Requisitos:

- Microsoft Visual Studio com o conjunto de ferramentas MSVC v145
- Windows SDK

Abra `CalClock.slnx`, selecione `Release | x86` e compile a solução. O executável é criado em:

```text
Release\CalClock.exe
```

Apenas Win32/x86 é suportado. O projeto não disponibiliza intencionalmente uma configuração x64, pois a integração com o controlo do relógio Windows exige compatibilidade x86.

Após a compilação, execute `.\PackageRelease.ps1` para criar `CalClock-<version>-win32.zip` com o programa e a
respetiva licença.

Os parâmetros de assinatura também obtêm valores predefinidos das variáveis de ambiente do utilizador do Windows:
`BUILD_SIGNER_NAME`, `BUILD_CERTIFICATE_THUMBPRINT`, `BUILD_SIGNTOOL_PATH`, `BUILD_TIMESTAMP_SERVER`. Os argumentos
explícitos da linha de comandos têm prioridade.

## Licença

O CalClock está disponível sob a [licença MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
