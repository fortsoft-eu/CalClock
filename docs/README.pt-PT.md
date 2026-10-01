# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · **Português** · [Norsk](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · [Türkçe](README.tr-TR.md)

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
- Interfaces em checo, inglês dos EUA, britânico e australiano, alemão, francês, espanhol, italiano, português, polaco, eslovaco, dinamarquês, finlandês, islandês, norueguês, sueco e turco

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
- Um duplo clique num widget das Definições torna-o visível se necessário, seleciona `Visível` e identifica-o brevemente no ambiente de trabalho.
- Abrir as Definições pelo menu de um widget seleciona-o imediatamente.
- Use `Ctrl` ou `Shift` para selecionar vários elementos, `Ctrl+A` para selecionar todos e `Del` para remover os selecionados. `Insert` alterna a seleção do elemento atual e avança o cursor da lista para a linha seguinte, como no Total Commander.
- Todos os atalhos da lista funcionam também com o foco em Remover ou Duplicar. O atalho transfere o foco para a lista e executa a ação. `Ctrl+C` copia os widgets selecionados e `Ctrl+V` acrescenta as cópias pela ordem da lista. As cópias incluem todas as definições e recebem um sufixo no idioma da aplicação. Duplicar executa diretamente a mesma operação. São permitidos até 32 widgets. Se não houver espaço para todas as cópias, são acrescentadas as que cabem, por ordem, e é apresentado um aviso sobre as restantes.
- `Ctrl+A` ou um triplo clique num campo de texto seleciona todo o conteúdo.

Com vários widgets selecionados, os respetivos controlos Geral, Aspeto, Alarme e Sinal ficam desativados; os separadores globais Hora e Aplicação continuam disponíveis. As Definições recordam o último separador aberto e o último tipo de widget adicionado. Numa área de trabalho pequena, a janela permite deslocamento horizontal ou vertical conforme necessário.

As datas podem ser copiadas em 33 formatos locais, ordenáveis, com dia ou mês primeiro, textuais e com dia da semana. Todas as máscaras estão disponíveis em todos os idiomas. O formato curto local predefinido segue o idioma do widget, tal como os nomes de meses e dias. As entradas mostram a máscara e um exemplo atualizado.

Um painel de calendário com relógio pode apresentar até dois relógios adicionais. Ative cada um em Geral e escolha o nome e o fuso. Os fusos com nome seguem as suas próprias regras de hora de verão; os desvios UTC fixos mantêm-se constantes. Com relógios adicionais ativos, cada relógio apresenta o seu dia local sob a hora. As três listas de tamanho em Aspeto controlam, por ordem, o relógio principal, Relógio 1 e Relógio 2. Um clique direito num mostrador adicional permite escolher o tamanho. Estes relógios omitem sempre os segundos e partilham idioma, formato, tipos de letra e desvio do widget. Adicionar, remover ou redimensionar relógios mantém o widget ligado às mesmas margens da área de trabalho.

Neste painel, a data superior é uma ligação que leva o calendário a hoje; o texto inferior do fuso abre as definições clássicas de Data e hora do Windows. Ambas as ligações são acessíveis com `Tab`, mostram um retângulo de foco e podem ser ativadas pelo teclado. O calendário nativo continua totalmente interativo, mas omite a linha Hoje, redundante nesta disposição.

`Alinhar na grelha` coloca os widgets visíveis numa grelha estável sem sobreposições, preservando aproximadamente a disposição manual. O widget cujo menu invocou o comando permanece no lugar; o comando da área de notificação organiza cada monitor separadamente. Os relógios no monitor são excluídos.

## Aspeto

Nos calendários independentes, **Linha Hoje**, no menu ou em Aspeto, controla a linha inferior. Está selecionada por predefinição; desmarcá-la oculta a linha e reduz o calendário. A escolha é guardada por widget. **Ir para hoje** continua disponível no menu e regressa à vista mensal. Quando a data muda segundo a hora do widget, o calendário seleciona hoje automaticamente, mantendo a vista atual.

As alterações de aspeto são imediatamente pré-visualizadas no widget selecionado. `Cancelar` repõe alterações não aplicadas; `Aspeto predefinido` repõe os valores do respetivo tipo de widget.

Relógios digitais, calendários e painéis partilham quatro estilos de contorno. O estilo simples também permite escolher a cor; a largura é configurável quando o widget a suporta. Os relógios digitais transparentes oferecem os mesmos estilos que os opacos. As janelas de tipos de letra mostram apenas opções aplicáveis, omitindo pré-visualização e efeitos não utilizados. Para aplicação e calendário não incluem tamanho; para relógios digitais e texto do painel incluem. Um calendário nativo só aceita um tipo de letra personalizado se os seus estilos visuais, ou os de toda a aplicação, estiverem desativados.

Idioma da aplicação, tipo de letra da interface, suavização, estilos visuais, armazenamento, arranque com Windows e encaixe às margens são globais e configurados em Aplicação. A origem da hora também é global. Idioma do widget, suavização, estilos, fuso, desvio, alarme e sinal horário são independentes. Aplicar outro idioma recria imediatamente a janela Definições aberta nesse idioma. A suavização oferece **ClearType**, **GDI** e **Nenhuma**. Em Aspeto, a suavização e desativação de temas ocupam a mesma posição em todos os tipos, com **Aspeto predefinido** por baixo.

O controlo **Volume do áudio** em Alarme regula os ficheiros reproduzidos internamente por widget e apresenta o nível em dB. A predefinição **−18 dB** mantém o nível original do ficheiro (**100%**). Para a direita amplifica o áudio; o máximo **0 dB** corresponde a cerca de **794%** da amplitude original. O extremo esquerdo é **−∞ dB** (silêncio). As alterações aplicam-se durante o teste. O controlo está desativado para ficheiros abertos externamente. A amplificação aplica-se a áudio descodificado, incluindo WAV, MP3, WMA, AAC, M4A e FLAC quando suportados pelo Windows. A reprodução antiga de ficheiros que não podem ser descodificados, como MIDI, está limitada a 100%.

Os dias do alarme seguem o primeiro dia da semana da cultura escolhida para a aplicação. Os dias guardados conservam o significado ao mudar o idioma. Ativar pelo menu um alarme sem dias selecionados abre o respetivo separador Alarme em vez de ativar um alarme que não pode tocar.

A largura predefinida do contorno digital é zero. **Zero inicial** oferece **Mostrar** (predefinido), **Reservar espaço** e **Sem espaço**. **Reservar espaço** oculta o zero mantendo a sua largura real no tipo de letra escolhido, para que os restantes algarismos não se movam mesmo com tipos proporcionais. Os relógios digitais flutuantes alinham a hora à esquerda e mantêm um tamanho fixo à medida que o tempo avança. Os relógios no monitor centram uma área fixa dimensionada para o tipo de letra e formato, incluindo dois algarismos para a hora. A mudança da hora não recentra nem redimensiona o texto. A linha AM/PM ou UTC fica centrada independentemente. Os relógios no monitor usam texto branco sobre fundo preto por predefinição.

## Hora e alarmes

Relógios digitais, painéis de calendário com relógio e relógios no monitor oferecem **Segundo o idioma**, **12 horas** e **24 horas** em **Formato da hora** de Geral. **Segundo o idioma** é a predefinição: inglês dos EUA e australiano usam, por exemplo, 12 horas, e britânico usa 24. A escolha manual mantém-se ao mudar o idioma do widget. Separadores e indicadores AM/PM seguem a cultura; culturas sem indicadores próprios usam **AM/PM** no modo de 12 horas.

**AM/PM** está selecionado por predefinição. Desmarcá-lo oculta o indicador sem alterar o ciclo de 12 horas. Fica desativado no modo de 24 horas e para widgets sem hora digital. Os relógios no monitor mostram o indicador numa linha separada sob a hora, como UTC. **UTC usa sempre 24 horas**; os controlos de ciclo e AM/PM ficam desativados, conservando os valores para o regresso à hora local. O zero inicial continua visível, oculto com espaço reservado ou omitido conforme a sua definição.

Os fusos com nome apresentam a hora civil do local e seguem automaticamente as suas regras de hora de verão. O desvio junto ao nome corresponde à data atual e é atualizado ao abrir a lista. As entradas **UTC** independentes oferecem desvios fixos de **UTC−12:00** a **UTC+14:00**, em passos de 15 minutos, sem hora de verão. Cada widget pode escolher o fuso local, qualquer outro fuso com nome ou um desvio UTC fixo de forma independente.

Cada widget pode usar qualquer fuso do Windows e um desvio com sinal no formato `[-]HH:mm:ss.ff`. A entrada compacta é interpretada da direita para a esquerda, começando pelos segundos.

O desvio é útil, por exemplo, em estúdios de radiodifusão para compensar o atraso do percurso de transmissão. Adiantar o relógio do estúdio pelo atraso medido permite que o sinal horário chegue aos ouvintes no momento previsto.

O CalClock pode usar a hora do sistema Windows ou uma correção interna obtida de servidores NTP. A escolha é global. A sincronização nunca altera o relógio Windows. Se a ligação NTP se perder após uma sincronização bem-sucedida, a última correção mantém-se ativa na memória do processo. Mudar de servidores também conserva a correção válida até chegar uma nova resposta.

Os widgets de relógio permitem alarmes por dias escolhidos individualmente; os sete dias estão ativos por predefinição. Um alarme torna visível o seu widget oculto e coloca-o à frente de outras janelas sem alterar permanentemente o estado sempre no topo. WAV, MP3, WMA, MIDI, AAC, M4A e FLAC são reconhecidos para reprodução interna única ou repetida; o suporte efetivo depende dos componentes multimédia instalados no Windows. Outros ficheiros e comandos são passados ao Windows de forma assíncrona. Um alarme pode também chamar um URL HTTP ou HTTPS. Independentemente, pode usar o sinal de seis tons cujo primeiro tom curto toca cinco segundos antes da hora definida.

Executar ficheiro ou comando ativa o campo, Procurar, Teste e repetição. Teste e repetição exigem também um campo não vazio; um teste em curso pode sempre ser parado. Teste mostra a indicação visual e testa de forma assíncrona ficheiro, comando, áudio e URL do script remoto. Se o sinal horário do alarme estiver selecionado, reproduz também os seis tons completos; Parar teste termina o áudio interno e a pré-visualização do sinal.

O separador Sinal desativa sinais ou programa-os a cada 1, 5, 10, 15, 20, 30 ou 60 minutos segundo a hora apresentada pelo widget. O intervalo de 20 minutos toca a :00, :20 e :40 dessa hora. O padrão é o **Greenwich Time Signal (GTS)**: cinco tons curtos marcam os últimos cinco segundos e um mais longo o limite exato. São respeitados fusos, UTC, desvios e correção NTP atual. O sinal do alarme e o separador Sinal permanecem independentes; quando coincidem, o CalClock reproduz uma única sequência partilhada. São respeitados desvios fracionários, e os tons sobrepostos de widgets, alarmes e testes continuam sem interrupção até terminar a última sobreposição.

**Som do sinal horário** em Aplicação permite escolher **Gerador interno** (predefinido) ou **Sinal sonoro do sistema**. A escolha aplica-se a todos os sinais, incluindo os dos alarmes, e é guardada globalmente. No **Gerador interno**, **Volume do sinal horário** mostra o nível em dB para toda a aplicação. À direita fica **0 dB**, a amplitude sinusoidal máxima sem distorção; silêncio é **−∞ dB**. O valor predefinido é **−18 dB**. A escala em decibéis tem −18 dB a meio. O gerador inicia e termina tons na passagem por zero, também ao parar um teste. O tom atual termina normalmente; um tom longo pode demorar até meio segundo. **Teste**, junto de **Som do sinal horário**, inicia a pré-visualização contínua; **Parar teste** termina-a. Ambos os modos podem ser testados e o estado do teste não é guardado. Manter premido o controlo de volume também inicia uma pré-visualização até soltar o rato, exceto se o teste pelo botão estiver ativo. A reprodução começa no próximo segundo inteiro, com tons curtos a cada segundo e um longo a :00, :05, :10, etc. A pré-visualização e sinais simultâneos de widgets ou alarmes partilham um único tom. Para o **Sinal sonoro do sistema**, apenas o volume fica desativado. A escolha só está disponível quando o sistema suporta ambos os modos.

Alarmes e sinais também podem ser ativados no menu contextual de cada widget com som. A entrada do alarme mostra a hora e, salvo se todos estiverem selecionados, os dias ativos. Sem som afeta o widget e corresponde à opção em Geral. Um Calendário independente não tem alarme, sinal nem estado sem som; esses comandos são omitidos ou desativados. Na área de notificação existe Silenciar tudo; `M` em qualquer widget executa a mesma alternância global. A reativação global restaura apenas widgets silenciados pela ação global anterior. O áudio interno continua silenciosamente e volta a ouvir-se ao reativar. Um tom já iniciado pode terminar; os seguintes são ignorados até reativar o som. Comandos não sonoros e scripts remotos não são afetados.

## Definições e menus

`Guardar` aplica alterações e fecha as Definições; `Aplicar` aplica-as mantendo a janela aberta; `Cancelar` descarta alterações ainda não aplicadas, incluindo a pré-visualização do aspeto. Enter ativa `Guardar`; Esc ativa `Cancelar`.

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

Após guardar o XML com êxito, o CalClock remove o seu estado do Registo. Regressar ao Registo remove, de modo semelhante, o XML automático e as pastas CalClock vazias. Importar XML carrega e guarda imediatamente as definições no armazenamento escolhido sem alterar o tipo. O estado sem som é guardado por widget sonoro. O arranque com Windows é guardado como valor `CalClock` na chave padrão `Run` do utilizador atual.

## Compilação

Requisitos:

- Microsoft Visual Studio com o conjunto de ferramentas MSVC v145
- Windows SDK

Abra `CalClock.slnx`, selecione `Release | Win32` e compile a solução. O executável é criado em:

```text
Release\CalClock.exe
```

Apenas Win32/x86 é suportado. O projeto não disponibiliza intencionalmente uma configuração x64, pois a integração com o controlo do relógio Windows exige compatibilidade x86.

## Licença

O CalClock está disponível sob a [licença MIT](../license.txt).

Copyright © Petr Červinka — FortSoft 2026
