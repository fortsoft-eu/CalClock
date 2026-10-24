# CalClock

[Čeština](README.cs-CZ.md) · [English (US)](../README.md) · [English (UK)](README.en-GB.md) · [English (Australia)](README.en-AU.md) · [Deutsch](README.de-DE.md) · [Français](README.fr-FR.md) · [Español](README.es-ES.md) · [Italiano](README.it-IT.md) · [Português](README.pt-PT.md) · [Polski](README.pl-PL.md) · [Slovenčina](README.sk-SK.md) · [Dansk](README.da-DK.md) · [Suomi](README.fi-FI.md) · [Íslenska](README.is-IS.md) · [Norsk (bokmål)](README.nb-NO.md) · [Svenska](README.sv-SE.md) · **Türkçe** · [Eesti](README.et-EE.md) · [Gaeilge](README.ga-IE.md) · [Lietuvių](README.lt-LT.md) · [Latviešu](README.lv-LV.md) · [Magyar](README.hu-HU.md) · [Malti](README.mt-MT.md) · [Nederlands](README.nl-NL.md) · [Română](README.ro-RO.md) · [Ελληνικά](README.el-GR.md) · [Bosanski](README.bs-Latn-BA.md) · [Hrvatski](README.hr-HR.md) · [Slovenščina](README.sl-SI.md) · [Crnogorski](README.cnr-Latn-ME.md) · [Беларуская](README.be-BY.md) · [Български](README.bg-BG.md) · [Македонски](README.mk-MK.md) · [Српски](README.sr-Cyrl-RS.md) · [Українська](README.uk-UA.md) · [Русский](README.ru-RU.md)

CalClock, Windows Vista ve sonraki sürümler için geliştirilmiş yerel bir Win32/x86 uygulamasıdır. Windows masaüstünde birbirinden bağımsız ayarlanabilen, serbestçe taşınabilen saatler ve takvimler gösterir. Bildirim alanında çalışır ve sürekli açık bir denetim penceresi gerektirmez.

## Özellikler

- Bağımsız ayarlanabilen en fazla 32 araç
- Her araç için ayrı dil, saat dilimi, zaman kaydırması, görünürlük ve her zaman üstte durumu
- Kadran boyutu seçilebilen ve isteğe bağlı saniye ibresi olan analog saatler
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
- 36 dil seçeneği sunan arayüz; uygulama ve her bir araç için bağımsız dil seçimi

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
- Delete seçili araçları kaldırır. `Insert` geçerli öğenin seçimini değiştirir ve liste imlecini bir satır aşağı taşır.
- `Ctrl+C` seçilen araçları kopyalar; `Ctrl+V` kopyaları liste sırasıyla sona ekler. Kopyalar bütün ayarları içerir ve adlarına uygulama dilinde bir ek alır. Çoğalt aynı işlemi doğrudan yapar. En fazla 32 araç kullanılabilir. Tüm kopyalar sığmazsa sığanlar sırayla eklenir ve kalanlar için bildirim gösterilir.

Ayarlar bildirim alanındaki simgeden açıldığında en son seçilen araç yeniden seçilir.

Ayarlar son açık sekmeyi ve son eklenen araç türünü hatırlar. Küçük çalışma alanlarında pencere gerektiğinde yatay veya dikey kaydırma sağlar.

Takvim tarihleri 33 biçimde kopyalanabilir: yerel, sıralanabilir, gün veya ay önce, metin tabanlı ve haftanın gününü içeren biçimler. Her maske bütün arayüz dillerinde kullanılabilir. Varsayılan kısa yerel biçim aracın dilini izler; ay ve gün adları da aynı dili kullanır. Girdiler maskeyi ve güncel örneği gösterir.

Saatli takvim paneli en fazla iki ek saat gösterebilir. Her birini Genel’de etkinleştirip adını ve saat dilimini seçin. Adlandırılmış bölgeler kendi yaz saati kurallarını izler; sabit UTC kaydırmaları değişmez. Ek saatler etkinken her saat kendi yerel haftanın gününü saatin altında gösterir. Görünüm’deki üç boyut listesi sırasıyla ana saati, Saat 1’i ve Saat 2’yi denetler. Ek kadrana sağ tıklayarak boyut seçebilirsiniz. Ek saatler saniyeleri her zaman atlar ve aracın dilini, saat biçimini, yazı tiplerini ve zaman kaydırmasını paylaşır. Saat eklemek, kaldırmak veya boyutlandırmak aracın aynı çalışma alanı kenarlarına bağlılığını korur.

Panelin üst tarihi, takvimi bugüne döndüren bir bağlantıdır; alttaki saat dilimi metni Windows’un klasik Tarih ve Saat ayarlarını açar.

Takvim ve saat panelleri, alt bağlantının üzerinde Windows tarih ve saat bildirimlerini gösterebilir. **Genel** sekmesindeki **Tarih ve saat bildirimleri** seçeneği varsayılan olarak açıktır ve her panel için ayrı kaydedilir. Birden fazla bildirim geçerliyse Windows’taki gibi alt alta gösterilir. Seçenek kapalıysa veya geçerli bir bildirim yoksa panelin özgün boyutu ve düzeni korunur; boş alan ayrılmaz.

`Izgaraya hizala`, görünür masaüstü araçlarını yaklaşık elle yerleştirme düzenini koruyarak sabit ve çakışmayan bir ızgaraya yerleştirir. Komutun kendi menüsünden çağrıldığı araç yerinde kalır; bildirim alanındaki komut her monitörü ayrı düzenler. Monitör saatleri kapsam dışındadır.

## Görünüm

Bağımsız takvimlerde menüdeki veya Görünüm sekmesindeki **Bugün satırı**, alttaki satırın görünürlüğünü denetler. Varsayılan olarak işaretlidir; işareti kaldırmak satırı gizler ve takvimi küçültür. Seçim araç başına saklanır. **Bugüne git** menüde kullanılabilir kalır ve ay görünümüne döner. Aracın zamanına göre tarih değiştiğinde takvim bugünü otomatik seçer ve geçerli görünümünü korur.

Görünüm değişiklikleri seçili araçta hemen önizlenir. `İptal` uygulanmamış değişiklikleri geri alır; `Varsayılan görünüm` o araç türünün varsayılanlarını geri getirir.

Dijital saatler, takvimler ve birleşik paneller dört kenarlık stilini paylaşır. Tek çizgili kenarlığın rengi de ayarlanabilir; genişlik denetimi aracın desteklediği yerlerde kullanılabilir. Saydam dijital saatlerde opak saatlerle aynı stiller bulunur. Uygulama ve takvim yazı tiplerinde boyut yoktur; dijital saatlerde ve panel metinlerinde vardır. Özel takvim yazı tipleri, Windows klasik görünümünde veya uygulama ya da araç için temalar kapatıldığında desteklenir.

Uygulama dili, arayüz yazı tipi, yumuşatma, görsel stiller, saklama, Windows ile başlatma ve kenara yapışma genel ayarlardır ve Uygulama’da yapılır. Zaman kaynağı da geneldir. Araç dili, yumuşatma, stiller, saat dilimi, kaydırma, alarm ve zaman sinyali bağımsız ayarlanır. Yumuşatma **ClearType**, **GDI** ve **Yok** seçeneklerini sunar.

Alarm’daki **Ses düzeyi** kaydırıcısı dahili çalınan dosyaları her araç için ayrı ayarlar ve düzeyi dB cinsinden gösterir. Varsayılan **−18 dB**, dosyanın özgün düzeyini (**100%**) korur. Sağa taşımak sesi yükseltir; en yüksek **0 dB**, özgün genliğin yaklaşık **794%** değeridir. En sol **−∞ dB** (sessizlik) konumudur. Değişiklikler ses testi sırasında etkilidir. Yükseltme, Windows desteklediğinde WAV, MP3, WMA, AAC, M4A ve FLAC dahil çözülmüş sese uygulanır. MIDI gibi çözülemeyen dosyaların eski çalma yöntemi 100% ile sınırlıdır.

Alarmın gün denetimleri seçilen uygulama kültürünün ilk hafta gününü izler. Kaydedilmiş günler dil değişince anlamlarını korur. Hiç gün seçilmeden menüden alarm açmak, çalamayacak bir alarmı etkinleştirmek yerine aracın Alarm sekmesini açar.

**Baştaki sıfır**, **Evet** (varsayılan), **Hayır, yer ayır** ve **Hayır, boşluksuz** seçeneklerini sunar. **Hayır, yer ayır**, sıfırı gizler ama seçili yazı tipindeki gerçek genişliğini korur; diğer rakamlar orantılı yazı tiplerinde bile yerinde kalır. Monitör saatleri varsayılan olarak siyah zemin üzerinde beyaz metin kullanır.

## Saat ve alarmlar

Dijital saatler, saatli takvim panelleri ve monitör saatleri Genel’deki **Saat biçimi** altında **Dile göre**, **12 saat** ve **24 saat** seçeneklerini sunar. Varsayılan **Dile göre** aracın dilini izler: örneğin ABD ve Avustralya İngilizcesi 12, Britanya İngilizcesi 24 saat kullanır. Elle seçilen döngü dil değişince korunur. Ayraçlar ve AM/PM göstergeleri seçili kültürü izler; kendi göstergesi olmayan kültürler 12 saat kipinde **AM/PM** kullanır.

**AM/PM** varsayılan olarak işaretlidir. İşareti kaldırmak göstergeyi gizler, 12 saat döngüsünü değiştirmez. Monitör saatleri göstergeyi UTC gibi saatin altında ayrı satırda gösterir. UTC her zaman 24 saatlik düzeni kullanır. Baştaki sıfır ayarı, sıfırın görünmesini, yer ayrılarak gizlenmesini veya atlanmasını belirlemeyi sürdürür.

Adlandırılmış saat dilimleri seçili yerin resmî yerel saatini gösterir ve o yerin yaz saati kurallarını otomatik izler. Adın yanındaki fark geçerli tarihe aittir ve liste açılırken yenilenir. Bağımsız **UTC** girdileri **UTC−12:00** ile **UTC+14:00** arasında 15 dakikalık adımlarla, yaz saati değişimi olmadan sabit kaydırmalar sunar. Her araç için yerel bölge, başka bir adlandırılmış bölge veya sabit UTC kaydırması bağımsız seçilebilir.

Yeni araçlarda varsayılan seçenek **Geçerli Windows saat dilimi** olur. Bu seçenek Windows’un geçerli saat dilimini ve otomatik yaz saati ayarını izler. Mevcut araçlar seçili saat dilimlerini korur. Bu seçim saat dilimini belirler; ortak Windows veya NTP zaman kaynağı bundan bağımsızdır.

Her araç herhangi bir Windows saat dilimini ve `[-]HH:mm:ss.ff` biçiminde işaretli kaydırmayı kullanabilir. Kısa giriş sağdan, saniyelerden başlayarak yorumlanır.

Kaydırma, örneğin yayın stüdyolarında iletim yolunun gecikmesini telafi etmek için yararlıdır. Stüdyo saatini ölçülen gecikme kadar ileri almak zaman sinyalinin dinleyicilere hedeflenen anda ulaşmasını sağlar.

Aracın zaman kaydırması, saat dilimine dönüştürülmeden önce UTC’ye uygulanır; böylece yaz saati uygulamasına geçiş veya uygulamadan çıkış anını da kaydırır. On saniye ileri ayarlanmış saat on saniye erken, on saniye geri ayarlanmış saat on saniye geç değişir. İbreler, dijital gösterim, takvim tarihleri, alarmlar ve saat sinyalleri sonuçta elde edilen zamanı kullanır.

Zaman sekmesi tüm uygulama için Windows zamanını veya NTP sunucularını seçer. NTP yalnızca CalClock'u düzeltir ve Windows'u hiçbir zaman değiştirmez. NTP varsayılandır; otomatik küme bölgeye göre sunucu seçer ve ölçümleri gecikme ile aykırı değerlere göre süzer.

Eşitlemeden sonra CalClock saati, Windows sistem saatinde daha sonra yapılan değişikliklerden bağımsız olarak ilerler. Bağlantı kesilirse veya sunucular değiştirilirse yeni bir yanıt alınana kadar son geçerli eşitlemeden itibaren ilerlemeye devam eder; bu durum uygulama kapatılana kadar korunur.

Zaman sekmesi, uygulama başlatıldığından beri NTP sunucu sorgularını kaydeder. Her kayıt tarih ve bilgisayarın yerel saatini, sunucuyu ve durumu içerir. OK geçerli bir yanıtı, θ ise bu yanıtın Windows sistem saatinden farkını gösterir. ERR başarısızlığın nedenini ve varsa hata kodunu belirtir. Kullanılabilir ölçümler varsa sorgu grubunun son kaydı hesaplanan zaman farkını Θ olarak da gösterir.

Zaman farkları milisaniye cinsinden dört ondalık basamakla gösterilir. Pozitif değer sunucu saatinin Windows’tan ileride, negatif değer geride olduğunu belirtir. Θ kabul edilen ölçümleri yansıtır ve eşitleme durumunda da gösterilir.

Günlüğü kaydet, zaman farkları ve hata ayrıntıları dahil kayıtları CSV’ye aktarır. Kayıtlar uygulama oturumları arasında korunmaz; saklamak istiyorsanız uygulamadan çıkmadan önce kaydedin.

Saat araçları ayrı seçilen hafta günlerinde alarm sunar; varsayılan olarak yedi gün de etkindir. Alarm gizli aracını gösterir ve her zaman üstte ayarını kalıcı değiştirmeden diğer pencerelerin önüne getirir. WAV, MP3, WMA, MIDI, AAC, M4A ve FLAC tek seferlik veya döngülü dahili çalma için tanınır; gerçek çözme desteği Windows’taki çoklu ortam bileşenlerine bağlıdır. Diğer dosya ve komutlar Windows’a eşzamansız iletilir. Alarm HTTP veya HTTPS adresi de çağırabilir. Bunlardan bağımsız olarak ilk kısa bipin alarm saatinden beş saniye önce başladığı altı bipli zaman sinyalini kullanabilir.

Alarmın ses sinyalleri, saat dilimi dönüşümü ve araç kaydırması uygulandıktan sonraki gerçek alarm anına göre planlanır. Gösterilen saat doğrudan alarm saatine atlasa bile sinyaller bu andan beş gerçek saniye önce başlar. İlkbaharda atlanan bir alarm saati ne alarmı ne de sinyallerini başlatır. Sonbaharda tekrarlanan saatte, aynı tarih ve ayarlı saat için alarm ve sinyalleri yalnızca bir kez çalar.

Test görsel uyarıyı gösterir ve dosya, komut, ses ve uzak betik adresini eşzamansız dener. Alarm zaman sinyali seçilmişse altı biplik dizinin tamamını da çalar; Testi durdur dahili sesi ve sinyal önizlemesini bitirir.

Sinyal sekmesinde Zaman sinyali etkin onay kutusu ve aracın gösterdiği saate göre 1, 5, 10, 15, 20, 30 veya 60 dakikalık aralıklar için seçenek düğmeleri bulunur. Sinyal başlangıçta kapalıdır ve bir saatlik aralık seçilidir. Araç menüsünde Sinyal seçeneğini kapatıp açmak aralığı korur. Menü, alarm saatini ve sinyal aralığını parantez içinde gösterir. 20 dakikalık aralık bu saatin :00, :20 ve :40 dakikalarında çalar. Düzen **Greenwich Time Signal (GTS)** biçimindedir: beş kısa bip son beş saniyeyi, uzun bip tam sınırı işaretler. Saat dilimleri, UTC, kaydırmalar ve geçerli NTP düzeltmesi dikkate alınır. Alarm sinyali ve Sinyal sekmesi ayrı ayarlanır; zamanları aynı ana denk gelirse CalClock tek bir ortak dizi çalar. Kesirli kaydırmalar korunur; üst üste gelen araç, alarm ve test tonları son örtüşme bitene kadar kesintisiz sürer.

Uygulama’daki **Zaman sinyali sesi**, **Yerleşik üreteç** (varsayılan) ve **Sistem bip sesi** seçeneklerini sunar. Seçim alarmlar dahil tüm araç sinyallerine uygulanır ve genel ayarlara kaydedilir. **Yerleşik üreteç** için **Zaman sinyali ses düzeyi** tüm uygulamanın düzeyini dB olarak gösterir. Sağ uç **0 dB**, bozulmamış sinüs dalgasının en yüksek genliğidir; sessizlik **−∞ dB** değeridir. Varsayılan **−18 dB**’dir. Üreteç, test durdurulurken de tonları sıfır geçişinde başlatır ve bitirir. Geçerli bipin bitmesine izin verilir; uzun bipin sona ermesi yarım saniyeye kadar sürebilir. **Zaman sinyali sesi** yanındaki **Test** sürekli önizlemeyi başlatır; **Testi durdur** bitirir. İki yöntem de test edilebilir ve test durumu kaydedilmez. Ses düzeyi kaydırıcısını fareyle tutmak da düğmeden başlatılmış test çalışmıyorsa fare bırakılana kadar önizleme yapar. Çalma sonraki tam saniyede başlar: her saniye kısa, :00, :05, :10 vb. anlarda uzun ton duyulur. Önizleme ile eşzamanlı araç veya alarm sinyalleri tek bir tonu paylaşır. Ses seçimi yalnızca sistem her iki yöntemi destekliyorsa kullanılabilir.

Alarm ve zaman sinyali ses destekleyen araçların bağlam menüsünden de açılabilir. Alarm öğesi saatini ve tüm günler seçili değilse etkin günleri gösterir. Sessiz komutu kendi aracını etkiler ve Genel’deki seçimle eşleşir. Bağımsız Takvim alarmı, zaman sinyalini veya sessize almayı desteklemez. Bildirim alanındaki komut Tümünü sessize al’dır; herhangi bir araç üzerinde `M` aynı genel geçişi yapar. Genel sessizliği kaldırmak yalnızca önceki genel eylemin susturduğu araçları geri getirir. Dahili ses sessizce ilerler ve sessizlik kaldırılınca yeniden duyulur. Başlamış bip bitebilir; sonraki bipler ses açılana kadar atlanır. Ses dışı komutlar ve uzak betikler etkilenmez.

## Ayarlar ve menüler

Her araç menüsü türüne uygun komutları — görünürlük, her zaman üstte, saniyeler, analog boyut veya tarih kopyalama biçimi — ve ardından `Izgaraya hizala`, Ayarlar, Yardım, Hakkında ve Çıkış’ı içerir. Bildirim menüsü tüm araçları sıra numaralarıyla listeler, ardından Tümünü göster, Tümünü gizle ve Tümünü sessize al gelir. Ayrı gruptaki `Izgaraya hizala` uygulama komutlarından önce yer alır.

Araçları göstermek veya geri getirmek her zaman üstte durumunu değiştirmeden onları diğer pencerelerin önüne taşır. CalClock başlangıçta en az bir görünür araç sağlar. İkinci çalıştırma var olan örneği etkinleştirir ve görünür araç yoksa en son gizlenenleri geri getirir. Windows Gezgini yeniden başladığında bildirim simgesi otomatik yeniden kaydedilir.

## Ayarların saklanması

Ayarlar varsayılan olarak şurada saklanır:

```text
HKEY_CURRENT_USER\Software\FortSoft\CalClock
```

XML saklama Ayarlar’dan etkinleştirilebilir ve şunu kullanır:

```text
%AppData%\FortSoft\CalClock\settings.xml
```

XML içe aktarmak ayarları hemen yükler ve saklama türünü değiştirmeden seçili konuma kaydeder. Sessiz durumu her sesli araç için ayrı saklanır.

## Derleme

Gereksinimler:

- MSVC v145 araç takımına sahip Microsoft Visual Studio
- Windows SDK

`CalClock.slnx` dosyasını açın, `Release | x86` seçin ve çözümü derleyin. Çalıştırılabilir dosya şu konumda oluşturulur:

```text
Release\CalClock.exe
```

Yalnızca Win32/x86 yapılandırması desteklenir. Windows saat denetimiyle bütünleşme x86 uyumluluğu gerektirdiğinden proje bilinçli olarak x64 yapılandırması sağlamaz.

## Lisans

CalClock, [MIT Lisansı](../license.txt) altında sunulur.

Copyright © Petr Červinka — FortSoft 2026
