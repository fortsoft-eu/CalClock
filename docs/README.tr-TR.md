# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Português](README.pt-PT.md) · [Norsk](README.nb-NO.md) · [Svenska](README.sv-SE.md) · [Suomi](README.fi-FI.md) · [Dansk](README.da-DK.md) · [Íslenska](README.is-IS.md) · **Türkçe**

CalClock, Windows Vista ve sonraki sürümler için geliştirilmiş yerel bir Win32/x86 uygulamasıdır. Windows masaüstünde birbirinden bağımsız ayarlanabilen, serbestçe taşınabilen saatler ve takvimler gösterir. Bildirim alanında çalışır ve sürekli açık bir denetim penceresi gerektirmez.

## Özellikler

- Bağımsız ayarlanabilen en fazla 32 araç
- Her araç için ayrı dil, saat dilimi, zaman kaydırması, görünürlük ve her zaman üstte durumu
- Windows `ClockWndMain` denetimine dayanan, kullanılabilir boyutları otomatik algılayan ve saniye ibresini destekleyen analog saatler
- Yazı tipi, renk, opaklık, iç boşluk, kenarlık, isteğe bağlı baştaki sıfır ve saydam arka plan ayarları bulunan dijital saatler
- Tarih seçimi, dört kenarlık stili, ayarlanabilir kenarlık rengi, hafta numarası, ilk gün seçimi ve 33 kopyalama biçimi sunan yerel Windows takvimleri
- Ayrı saat dilimlerinde en fazla iki ek adlandırılmış saat, bağımsız kadran boyutları, dört kenarlık stili, ayarlanabilir renk, UTC metni, baştaki sıfır ve her metin satırı için ayrı yazı tipi sunan takvim ve saat panelleri
- Gün seçimi, görsel uyarı, dahili ses çalma, yineleme, yerel komutlar ve HTTP/HTTPS betik çağrıları bulunan alarmlar
- Her saat için 1, 5, 10, 15, 20, 30 veya 60 dakikalık zaman sinyalleri; eşzamanlı sinyaller tek bir dizi halinde birleştirilir
- Her saat için Sessiz komutu ve bildirim alanında işaretlenebilir Tümünü sessize al komutu
- İsteğe bağlı Windows ile otomatik başlatma
- Sürükleme sırasında çalışma alanı kenarlarına beş piksel içinde isteğe bağlı yapışma; varsayılan olarak açıktır ve boyut değiştiğinde kenara bağlılık korunur
- Windows sistem saatini değiştirmeden NTP eşitlemesi
- Çekya ve Slovakya, PTB, Ubuntu/NTP Pool veya özel sunucular için NTP ön ayarları
- XML içe ve dışa aktarma dahil Kayıt Defteri veya XML üzerinde ayar saklama
- En son gizlenen araçları geri getiren bildirim alanı denetimleri
- Araçları tanımlama ve çakışmayan, sabit bir ızgarada hizalama
- İptal etme ve araç başına varsayılan görünüm seçenekleriyle anlık görünüm önizlemesi
- Uygulama ve araç yazı tipleri, görsel stiller ve ClearType, GDI veya yumuşatma olmadan yazı görüntüleme
- Çekçe, ABD, Britanya ve Avustralya İngilizcesi, Almanca, Fransızca, İspanyolca, İtalyanca, Portekizce, Lehçe, Slovakça, Danca, Fince, İzlandaca, Norveççe, İsveççe ve Türkçe arayüzler

## Araç türleri

| Araç | Açıklama |
| --- | --- |
| Analog saat | Geçerli Windows sürümünün sunduğu boyutlara ve isteğe bağlı saniye ibresine sahip, taşınabilir Windows kadranı |
| Dijital saat | İsteğe bağlı UTC metni, baştaki sıfır, kenarlık ve saydam arka plan sunan ayarlanabilir dijital gösterim |
| Takvim | Tarih seçimi, ayarlanabilir kenarlıklar ve kopyalama biçimleri bulunan taşınabilir yerel aylık takvim |
| Saatli takvim | Yerel takvim, analog saat, ayarlanabilir metin satırları, UTC gösterimi ve kenarlıkları birleştiren panel |
| Monitör saati | Seçilen bir veya daha fazla monitörü dolduran, isteğe bağlı karartma ve ayrı satırda UTC sunan dijital saat |

CalClock ilk başlatmada Windows arayüz dilini seçer; dil desteklenmiyorsa ABD İngilizcesini kullanır. Varsayılan olarak görünür bir analog saat oluşturur. Her araç, konumunu ve ayarlarını çalıştırmalar arasında korur. Ayarlar açıkken monitör saati, seçili monitörün en boy oranına sahip taşınabilir bir önizlemeyle temsil edilir. `Esc`, Ayarlar etkin olsa bile monitör saatini gizler ve karartmasını kaldırır. İşaretçi, monitör saatleri ve karartılmış monitörler üzerinde kısa süre hareketsiz kalınca gizlenir, fare hareket edince yeniden görünür. Ayarlar içindeki küçük önizleme üzerinde görünür kalır.

## Kullanım

- Saati veya paneli sol fare düğmesiyle sürükleyin.
- Bağımsız takvimi boş alanından sürükleyin.
- Bağlam menüsü için araca veya bildirim alanı simgesine sağ tıklayın.
- Bildirim simgesine sol tıklamak görünür araçları gizler. Hepsi gizliyse sonraki tıklama yalnızca en son gizlenenleri geri getirir.
- Saniye gösterimini değiştirmek için kadrana çift tıklayın. Saatli takvimde saniye ibresini yalnızca doğrudan ana kadrana çift tıklamak değiştirir. Ek saatlerde saniye ibresi yoktur.
- `F1` Yardım’ı, `B` Ayarlar’ı açar; `M` genel sessiz durumunu değiştirir; `Esc` aracı gizler veya etkin alarmı durdurur.
- Analog saat veya Saatli takvim aracında ana kadranın boyutunu küçükten büyüğe seçmek için `Alt+0`, `Alt+1`, `Alt+2` veya `Alt+3` tuşlarına basın.
- Ayarlar listesindeki araca çift tıklamak gerekirse onu görünür yapar, `Görünür` seçeneğini işaretler ve masaüstünde kısa süre tanımlar.
- Ayarlar’ı aracın bağlam menüsünden açmak o aracı hemen seçer.
- Çoklu seçim için `Ctrl` veya `Shift`, tümünü seçmek için `Ctrl+A`, seçilenleri kaldırmak için `Del` kullanın. `Insert`, geçerli öğenin seçimini değiştirir ve liste imlecini Total Commander’daki gibi sonraki satıra taşır.
- Liste kısayollarının tümü odak Kaldır veya Çoğalt düğmesindeyken de çalışır. Kısayol odağı listeye taşır ve işlemi yapar. `Ctrl+C` seçilen araçları kopyalar; `Ctrl+V` kopyaları liste sırasıyla sona ekler. Kopyalar bütün ayarları içerir ve adlarına uygulama dilinde bir ek alır. Çoğalt aynı işlemi doğrudan yapar. En fazla 32 araç kullanılabilir. Tüm kopyalar sığmazsa sığanlar sırayla eklenir ve kalanlar için bildirim gösterilir.
- Bir metin alanında `Ctrl+A` veya üç kez tıklama tüm metni seçer.

Birden fazla araç seçildiğinde Genel, Görünüm, Alarm ve Sinyal üzerindeki araç denetimleri devre dışı kalır; genel Saat ve Uygulama sekmeleri kullanılabilir. Ayarlar son açık sekmeyi ve son eklenen araç türünü hatırlar. Küçük çalışma alanlarında pencere gerektiğinde yatay veya dikey kaydırma sağlar.

Takvim tarihleri 33 biçimde kopyalanabilir: yerel, sıralanabilir, gün veya ay önce, metin tabanlı ve haftanın gününü içeren biçimler. Her maske bütün arayüz dillerinde kullanılabilir. Varsayılan kısa yerel biçim aracın dilini izler; ay ve gün adları da aynı dili kullanır. Girdiler maskeyi ve güncel örneği gösterir.

Saatli takvim paneli en fazla iki ek saat gösterebilir. Her birini Genel’de etkinleştirip adını ve saat dilimini seçin. Adlandırılmış bölgeler kendi yaz saati kurallarını izler; sabit UTC kaydırmaları değişmez. Ek saatler etkinken her saat kendi yerel haftanın gününü saatin altında gösterir. Görünüm’deki üç boyut listesi sırasıyla ana saati, Saat 1’i ve Saat 2’yi denetler. Ek kadrana sağ tıklayarak boyut seçebilirsiniz. Ek saatler saniyeleri her zaman atlar ve aracın dilini, saat biçimini, yazı tiplerini ve zaman kaydırmasını paylaşır. Saat eklemek, kaldırmak veya boyutlandırmak aracın aynı çalışma alanı kenarlarına bağlılığını korur.

Panelin üst tarihi, takvimi bugüne döndüren bir bağlantıdır; alttaki saat dilimi metni Windows’un klasik Tarih ve Saat ayarlarını açar. İki bağlantıya da `Tab` ile ulaşılabilir, odak dikdörtgeni gösterilir ve klavyeyle etkinleştirilebilir. Yerel takvim tamamen etkileşimli kalır ancak birleşik düzende gereksiz olan Bugün satırını göstermez.

`Izgaraya hizala`, görünür masaüstü araçlarını yaklaşık elle yerleştirme düzenini koruyarak sabit ve çakışmayan bir ızgaraya yerleştirir. Komutun kendi menüsünden çağrıldığı araç yerinde kalır; bildirim alanındaki komut her monitörü ayrı düzenler. Monitör saatleri kapsam dışındadır.

## Görünüm

Bağımsız takvimlerde menüdeki veya Görünüm sekmesindeki **Bugün satırı**, alttaki satırın görünürlüğünü denetler. Varsayılan olarak işaretlidir; işareti kaldırmak satırı gizler ve takvimi küçültür. Seçim araç başına saklanır. **Bugüne git** menüde kullanılabilir kalır ve ay görünümüne döner. Aracın zamanına göre tarih değiştiğinde takvim bugünü otomatik seçer ve geçerli görünümünü korur.

Görünüm değişiklikleri seçili araçta hemen önizlenir. `İptal` uygulanmamış değişiklikleri geri alır; `Varsayılan görünüm` o araç türünün varsayılanlarını geri getirir.

Dijital saatler, takvimler ve birleşik paneller dört kenarlık stilini paylaşır. Tek çizgili kenarlığın rengi de ayarlanabilir; genişlik denetimi aracın desteklediği yerlerde kullanılabilir. Saydam dijital saatlerde opak saatlerle aynı stiller bulunur. Yazı tipi iletişim kutuları yalnızca ilgili seçenekleri gösterir, kullanılmayan önizleme ve efektleri atlar. Uygulama ve takvim yazı tiplerinde boyut yoktur; dijital saatlerde ve panel metinlerinde vardır. Yerel takvim özel yazı tipini yalnızca kendisinin veya uygulamanın görsel stilleri kapatılmışsa kabul eder.

Uygulama dili, arayüz yazı tipi, yumuşatma, görsel stiller, saklama, Windows ile başlatma ve kenara yapışma genel ayarlardır ve Uygulama’da yapılır. Zaman kaynağı da geneldir. Araç dili, yumuşatma, stiller, saat dilimi, kaydırma, alarm ve zaman sinyali bağımsız ayarlanır. Yeni uygulama dili uygulanınca açık Ayarlar penceresi hemen o dilde yeniden oluşturulur. Yumuşatma **ClearType**, **GDI** ve **Yok** seçeneklerini sunar. Görünüm’de yumuşatma ile temaları kapatma bütün türlerde aynı yerdedir; **Varsayılan görünüm** altlarındadır.

Alarm’daki **Ses düzeyi** kaydırıcısı dahili çalınan dosyaları her araç için ayrı ayarlar ve düzeyi dB cinsinden gösterir. Varsayılan **−18 dB**, dosyanın özgün düzeyini (**100%**) korur. Sağa taşımak sesi yükseltir; en yüksek **0 dB**, özgün genliğin yaklaşık **794%** değeridir. En sol **−∞ dB** (sessizlik) konumudur. Değişiklikler ses testi sırasında etkilidir. Harici uygulamada açılan dosyalarda kaydırıcı devre dışıdır. Yükseltme, Windows desteklediğinde WAV, MP3, WMA, AAC, M4A ve FLAC dahil çözülmüş sese uygulanır. MIDI gibi çözülemeyen dosyaların eski çalma yöntemi 100% ile sınırlıdır.

Alarmın gün denetimleri seçilen uygulama kültürünün ilk hafta gününü izler. Kaydedilmiş günler dil değişince anlamlarını korur. Hiç gün seçilmeden menüden alarm açmak, çalamayacak bir alarmı etkinleştirmek yerine aracın Alarm sekmesini açar.

Dijital saatin varsayılan kenarlık genişliği sıfırdır. **Baştaki sıfır**, **Göster** (varsayılan), **Yer ayır** ve **Yer ayırma** seçeneklerini sunar. **Yer ayır**, sıfırı gizler ama seçili yazı tipindeki gerçek genişliğini korur; diğer rakamlar orantılı yazı tiplerinde bile yerinde kalır. Serbestçe yerleştirilen dijital saatler zamanı sola hizalar ve zaman ilerlerken sabit boyutu korur. Monitör saatleri, yazı tipi ve biçime göre boyutlandırılmış, iki saat rakamına yer ayıran sabit bir zaman alanını ortalar. Zamanın değişmesi metni yeniden ortalamaz veya boyutlandırmaz. AM/PM veya UTC satırı bağımsız ortalanır. Monitör saatleri varsayılan olarak siyah zemin üzerinde beyaz metin kullanır.

## Saat ve alarmlar

Dijital saatler, saatli takvim panelleri ve monitör saatleri Genel’deki **Saat biçimi** altında **Dile göre**, **12 saat** ve **24 saat** seçeneklerini sunar. Varsayılan **Dile göre** aracın dilini izler: örneğin ABD ve Avustralya İngilizcesi 12, Britanya İngilizcesi 24 saat kullanır. Elle seçilen döngü dil değişince korunur. Ayraçlar ve AM/PM göstergeleri seçili kültürü izler; kendi göstergesi olmayan kültürler 12 saat kipinde **AM/PM** kullanır.

**AM/PM** varsayılan olarak işaretlidir. İşareti kaldırmak göstergeyi gizler, 12 saat döngüsünü değiştirmez. 24 saat kipinde ve dijital saat göstermeyen araçlarda devre dışıdır. Monitör saatleri göstergeyi UTC gibi saatin altında ayrı satırda gösterir. **UTC her zaman 24 saat kullanır**; UTC seçiliyken döngü ve AM/PM denetimleri devre dışıdır, değerleri yerel saate dönmek için saklanır. Baştaki sıfır ayarı, sıfırın görünmesini, yer ayrılarak gizlenmesini veya atlanmasını belirlemeyi sürdürür.

Adlandırılmış saat dilimleri seçili yerin resmî yerel saatini gösterir ve o yerin yaz saati kurallarını otomatik izler. Adın yanındaki fark geçerli tarihe aittir ve liste açılırken yenilenir. Bağımsız **UTC** girdileri **UTC−12:00** ile **UTC+14:00** arasında 15 dakikalık adımlarla, yaz saati değişimi olmadan sabit kaydırmalar sunar. Her araç için yerel bölge, başka bir adlandırılmış bölge veya sabit UTC kaydırması bağımsız seçilebilir.

Her araç herhangi bir Windows saat dilimini ve `[-]HH:mm:ss.ff` biçiminde işaretli kaydırmayı kullanabilir. Kısa giriş sağdan, saniyelerden başlayarak yorumlanır.

Kaydırma, örneğin yayın stüdyolarında iletim yolunun gecikmesini telafi etmek için yararlıdır. Stüdyo saatini ölçülen gecikme kadar ileri almak zaman sinyalinin dinleyicilere hedeflenen anda ulaşmasını sağlar.

CalClock Windows sistem saatini veya NTP sunucularından alınan uygulamaya özgü düzeltmeyi kullanabilir. Seçim tüm araçlar için geneldir. Eşitleme Windows saatini asla değiştirmez. Başarılı eşitlemeden sonra NTP bağlantısı kaybolursa son düzeltme işlem belleğinde etkin kalır. Sunucu değiştirmek de yeni yanıt alınana kadar geçerli düzeltmeyi korur.

Saat araçları ayrı seçilen hafta günlerinde alarm sunar; varsayılan olarak yedi gün de etkindir. Alarm gizli aracını gösterir ve her zaman üstte ayarını kalıcı değiştirmeden diğer pencerelerin önüne getirir. WAV, MP3, WMA, MIDI, AAC, M4A ve FLAC tek seferlik veya döngülü dahili çalma için tanınır; gerçek çözme desteği Windows’taki çoklu ortam bileşenlerine bağlıdır. Diğer dosya ve komutlar Windows’a eşzamansız iletilir. Alarm HTTP veya HTTPS adresi de çağırabilir. Bunlardan bağımsız olarak ilk kısa bipin alarm saatinden beş saniye önce başladığı altı bipli zaman sinyalini kullanabilir.

Dosya veya komut çalıştır seçeneği alanı, Gözat ve Test düğmelerini ve yinelemeyi etkinleştirir. Test ve yineleme ayrıca boş olmayan bir alan gerektirir; çalışan test her zaman durdurulabilir. Test görsel uyarıyı gösterir ve dosya, komut, ses ve uzak betik adresini eşzamansız dener. Alarm zaman sinyali seçilmişse altı biplik dizinin tamamını da çalar; Testi durdur dahili sesi ve sinyal önizlemesini bitirir.

Sinyal sekmesinde Zaman sinyali etkin onay kutusu ve aracın gösterdiği saate göre 1, 5, 10, 15, 20, 30 veya 60 dakikalık aralıklar için seçenek düğmeleri bulunur. Sinyal başlangıçta kapalıdır ve bir saatlik aralık seçilidir. Araç menüsünde Sinyal seçeneğini kapatıp açmak aralığı korur. Menü, alarm saatini ve sinyal aralığını parantez içinde gösterir. 20 dakikalık aralık bu saatin :00, :20 ve :40 dakikalarında çalar. Düzen **Greenwich Time Signal (GTS)** biçimindedir: beş kısa bip son beş saniyeyi, uzun bip tam sınırı işaretler. Saat dilimleri, UTC, kaydırmalar ve geçerli NTP düzeltmesi dikkate alınır. Alarm sinyali ve Sinyal sekmesi ayrı ayarlanır; zamanları aynı ana denk gelirse CalClock tek bir ortak dizi çalar. Kesirli kaydırmalar korunur; üst üste gelen araç, alarm ve test tonları son örtüşme bitene kadar kesintisiz sürer.

Uygulama’daki **Zaman sinyali sesi**, **Dahili üreteç** (varsayılan) ve **Sistem bip sesi** seçeneklerini sunar. Seçim alarmlar dahil tüm araç sinyallerine uygulanır ve genel ayarlara kaydedilir. **Dahili üreteç** için **Zaman sinyali ses düzeyi** tüm uygulamanın düzeyini dB olarak gösterir. Sağ uç **0 dB**, bozulmamış sinüs dalgasının en yüksek genliğidir; sessizlik **−∞ dB** değeridir. Varsayılan **−18 dB**’dir. Desibel ölçeğinin orta noktasında −18 dB bulunur. Üreteç, test durdurulurken de tonları sıfır geçişinde başlatır ve bitirir. Geçerli bipin bitmesine izin verilir; uzun bipin sona ermesi yarım saniyeye kadar sürebilir. **Zaman sinyali sesi** yanındaki **Test** sürekli önizlemeyi başlatır; **Testi durdur** bitirir. İki yöntem de test edilebilir ve test durumu kaydedilmez. Ses düzeyi kaydırıcısını fareyle tutmak da düğmeden başlatılmış test çalışmıyorsa fare bırakılana kadar önizleme yapar. Çalma sonraki tam saniyede başlar: her saniye kısa, :00, :05, :10 vb. anlarda uzun ton duyulur. Önizleme ile eşzamanlı araç veya alarm sinyalleri tek bir tonu paylaşır. **Sistem bip sesi** için yalnızca ses düzeyi kaydırıcısı devre dışıdır. Ses seçimi yalnızca sistem her iki yöntemi destekliyorsa kullanılabilir.

Alarm ve zaman sinyali ses destekleyen araçların bağlam menüsünden de açılabilir. Alarm öğesi saatini ve tüm günler seçili değilse etkin günleri gösterir. Sessiz komutu kendi aracını etkiler ve Genel’deki seçimle eşleşir. Bağımsız Takvim’de alarm, sinyal veya sessiz durumu yoktur; ilgili komutlar gösterilmez ya da devre dışıdır. Bildirim alanındaki komut Tümünü sessize al’dır; herhangi bir araç üzerinde `M` aynı genel geçişi yapar. Genel sessizliği kaldırmak yalnızca önceki genel eylemin susturduğu araçları geri getirir. Dahili ses sessizce ilerler ve sessizlik kaldırılınca yeniden duyulur. Başlamış bip bitebilir; sonraki bipler ses açılana kadar atlanır. Ses dışı komutlar ve uzak betikler etkilenmez.

## Ayarlar ve menüler

`Kaydet` değişiklikleri uygular ve Ayarlar’ı kapatır; `Uygula` kapatmadan uygular; `İptal` görünüm önizlemesi dahil uygulanmamış değişiklikleri atar. Enter `Kaydet`i, Esc `İptal`i etkinleştirir.

Her araç menüsü türüne uygun komutları — görünürlük, her zaman üstte, saniyeler, analog boyut veya tarih kopyalama biçimi — ve ardından `Izgaraya hizala`, Ayarlar, Yardım, Hakkında ve Çıkış’ı içerir. Bildirim menüsü tüm araçları sıra numaralarıyla listeler, ardından Tümünü göster, Tümünü gizle ve Tümünü sessize al gelir. Ayrı gruptaki `Izgaraya hizala` uygulama komutlarından önce yer alır.

Araçları göstermek veya geri getirmek her zaman üstte durumunu değiştirmeden onları diğer pencerelerin önüne taşır. CalClock başlangıçta en az bir görünür araç sağlar. İkinci çalıştırma var olan örneği etkinleştirir ve görünür araç yoksa en son gizlenenleri geri getirir. Windows Gezgini yeniden başladığında bildirim simgesi otomatik yeniden kaydedilir. `ClockWndMain` seçili boyutta saniye ibresini desteklemiyorsa Saniyeler komutu devre dışı kalır, ancak tercih başka bir desteklenen boyut için saklanır.

## Ayarların saklanması

Ayarlar varsayılan olarak şurada saklanır:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

XML saklama Ayarlar’dan etkinleştirilebilir ve şunu kullanır:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

XML başarıyla yazıldıktan sonra CalClock uygulama durumunu Kayıt Defteri’nden kaldırır. Kayıt Defteri’ne geri dönmek benzer şekilde otomatik XML dosyasını ve boş CalClock klasörlerini kaldırır. XML içe aktarmak ayarları hemen yükler ve saklama türünü değiştirmeden seçili konuma kaydeder. Sessiz durumu her sesli araç için ayrı saklanır. Windows ile başlatma, geçerli kullanıcının standart Windows `Run` anahtarında `CalClock` değeri olarak saklanır.

## Derleme

Gereksinimler:

- MSVC v145 araç takımına sahip Microsoft Visual Studio
- Windows SDK

`CalClock.slnx` dosyasını açın, `Release | Win32` seçin ve çözümü derleyin. Çalıştırılabilir dosya şu konumda oluşturulur:

```text
Release\CalClock.exe
```

Yalnızca Win32/x86 yapılandırması desteklenir. Windows saat denetimiyle bütünleşme x86 uyumluluğu gerektirdiğinden proje bilinçli olarak x64 yapılandırması sağlamaz.

## Lisans

CalClock, [MIT Lisansı](../license.txt) altında sunulur.

Copyright © Petr Červinka — FortSoft 2026
