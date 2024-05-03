# Lojistik Regresyon ile Yangın Alarm Sistemi Oluşturulması
<h2> 1.	PROJE KONUSU, ÖNEMİ VE HEDEFİ </h2>

Proje, Arduino UNO [1] kartı ile geliştirilmiş bir gömülü sistem çalışmasıdır. Projenin konusu makine öğrenmesi yöntemlerinden biri olan Lojistik regresyon [2] ile yangın tespitinin gerçekleştirilmesidir. Günümüzde teknolojik aletlerin kullanımın artması ile elektronik sistemler daha sık kullanılmaya başlanmıştır. Teknolojik ve elektronik aletlerin kullanımı sırasında yaşanan bazı teknik aksaklıklar yangınlara sebep olabilmektedir. Bunlara ek olarak; mutfaklar, sanayiler, okullar ve hastaneler gibi insanların sıklıkla bulunduğu alanlarda da çeşitli sebeplerden dolayı yangınlar çıkabilmektedir.
Geleneksel yangın tespit sistemleri genellikle sadece duman sensörlerine dayanırken, bu çalışma daha kapsamlı bir yaklaşım sunmaktadır. Hava basıncı, sıcaklık, nem, havadaki alkol ve H2 miktarı gibi çeşitli veri noktaları kullanılmıştır. Gelişen teknoloji ve makine öğrenimi tekniklerinin entegrasyonuyla sistem yangın tespitine daha hassas ve güvenilir bir şekilde oluşturulmuştur. Oluşturulan yangın tespit sisteminin Arduino üzerindeki sensör bağlantıları Şekil 1’de görülmektedir.
Bu yaklaşımın, yangın riskini daha doğru bir şekilde belirlemesi ve yanlış alarm riskini azaltması hedeflenmektedir. Birden fazla verinin değerlendirilmesi ile yangın tespit sisteminin performansının artacağı düşünülmektedir.
<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/c8fed516-54b9-4b3f-81d6-c438f9cc30cf" alt="image">
</div>
<div align="center">
Şekil 1. Oluşturulan yangın tespit sisteminin Arduino bağlantısı
</div>
<br>

<h2> 2.	MATERYAL VE METOD </h2>

<h3> 2.1.	  PROJEDE KULLANILAN DONANIMLAR VE TEKNİK ÖZELLİKLERİ </h3>

<h4> 2.1.1.  ARDUINO UNO </h4>
<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/643b28e2-af8f-4ae0-b56d-58fb26e47b28" alt="image">
</div>
Arduino kartları arasında sıklıkla kullanılan kartlardan biridir. Bir sisteme entegre edilmesi kolay olduğu için pek çok kullanım alanları vardır. Akıllı ev sistemleri, robot sistemleri gibi gelişmiş sistemlerde kullanılabilmektedir. Onun haricinde okul projelerinde bireysel küçük çaplı projelerde de kullanım kolaylığı açısından tercih edilmektedir. Elektronik devrelerin kontrol edilmesini ve çalıştırılmasını sağlamaktadır [3] .
• Dijital çıkış pini sayısı : 14
• PWM çıkışı sayısı : 5
• Analog giriş sayısı : 6
• Çalışma gerilimi : 5 V
• Mikrodenetleyici : Atmega328
• EEPROM : 1 KB
• SRAM : 2 KB
• Saat hızı : 16 MHz
• I/O için akım : 40 mA
• 3.3 V çıkış için akım : 50 mA

<h4> 2.1.2.  MQ-3 SENSÖRÜ </h4>
<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/ff2ad49f-b450-445c-a291-4b9f75b6fa11" alt="image">
</div>
MQ serisi gaz sensörleri içerisinde gazı algılamaya duyarlı bir tel, ısıtıcı eleman ve bir yük direnci bulunmaktadır. Çalışma prensipleri genel olarak aynıdır. MQ-3 sensörü özellikle etanol ölçümünde kullanılmaktadır. Alkollü buharı algılayabilmektedir. Analog direnç değerini, 0 ile 5V aralığına eş bir değere çevirmek için bir yük direnci kullanılmaktadır.

Yük direnci pini, Arduino’nun analog giriş pinlerinden birine bağlanarak Arduino’ya bilgi aktarımı sağlanmaktadır. 
• Ölçme konsantrasyonu: 300 – 10000ppm 
• Besleme voltajı : < 24V 
• Istıcı voltajı: 5.0V ± 0.2V 
• Yük direnci: Ayarlanabilir 
• Isıtıcı güç sarfiyatı : < 900mW

<h4> 2.1.3.  MQ-8 SENSÖRÜ </h4>
<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/e1937708-85fc-4304-9e92-cca76123a037" alt="image">
</div>

MQ serisi gaz sensörleri içerisinde gazı algılamaya duyarlı bir tel, ısıtıcı eleman ve bir yük direnci bulunmaktadır. Çalışma prensipleri genel olarak aynıdır. MQ-8 sensörü metan (CH4) gazı ölçümünde kullanılmaktadır. Çalışmada metan gazı ile benzerlikleri olduğu için hidrojen di oksit (H2) gazı ölçmek amacıyla kullanılmıştır. Analog direnç değerini, 0 ile 5V aralığına eş bir değere çevirmek için bir yük direnci kullanılmaktadır. Yük direnci pini, Arduino’nun analog giriş pinlerinden birine bağlanarak Arduino’ya bilgi aktarımı sağlanmaktadır. 
• Ölçme konsantrasyonu: 100 - 10,000ppm 
• Besleme voltajı : < 24V 
• Istıcı voltajı: 5.0V ± 0.2V
• Yük direnci: Ayarlanabilir 
• Isıtıcı güç sarfiyatı : < 750mW

<h4> 2.1.4.  BME280 SENSÖRÜ </h4>
<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/d4b22154-b354-40f6-b794-885850b064c5" alt="image">
</div>

BME280 sensörü, sıcaklık, nem ve basınç ölçümü yapabilen bir çevresel sensördür. İşlevselliği ve hassasiyeti nedeniyle hava kalitesi izleme, hava tahmini, iç mekan iklimlendirme ve diğer meteorolojik uygulamalarda yaygın olarak kullanılmaktadır.
• Sıcaklık Ölçümü: -40°C ila +85°C arasındaki sıcaklıkları ölçmektedir.
• Nem Ölçümü: %0 ila %100 arasında nem değerlerini ölçmektedir.
• Basınç Ölçümü: Atmosferik basıncı hPa (hektopaskal), Pa (paskal), mmHg (milimetre cıva) veya inHg (inç cıva) birimleriyle ölçmektedir.
• İletişim Arabirimi: I2C (Inter-Integrated Circuit) ve SPI (Serial Peripheral Interface) olmak üzere iki farklı iletişim protokolünü desteklemektedir.

<h4> 2.1.5.  BUZZER </h4>
<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/4a48dfb5-1b9c-47dd-ad9b-5f7ee9479e81" alt="image">
</div>

Geniş alanlara ses sinyalleri yaymaktadır. Projeye göre istenilen şartlar sağlandığında ses sinyalleri ile uyarı vermektedir. Alarm işlevi görmektedir.
• Maksimum akım: 30 mA
• 10 cm’deki minimum ses çıkışı: 85 dB
• Titreşim frekansı: 2300 +/- 300 Hz
• Çalışma voltajı: 4-8V

<h4> 2.1.6.  LED </h4>
<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/3d59d8d9-66fb-4f44-9c51-9705efa026d3" alt="image">
</div>

Elektrik enerjisini ışığa dönüştüren yarı iletken bir devre elemanıdır. Belirli miktarda voltaj verildiğinde etrafa ışık yaymaktadır. Projede yeşil ve kırmızı renkte ledler kullanılmıştır.
• Boyut: 5 mm
• Çalışma voltajı: 1.5 - 3 V
• Önerilen kullanım akımı: 16 - 18 mA
• Maksimum akım: 20 mA

<h4> 2.1.7.  JUMPER KABLO </h4>
<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/ae449991-ee75-43fb-bfa7-0cb03131677e" alt="image">
</div>
Arduino ve breadboard arasında bağlantı yapılmasını sağlamaktadır. Örnek olarak projede kullanım alanlarından biri; arduino üzerinden gelen 5V, jumper kablolar ile breadboard üzerine aktarılmıştır ve 5V pini bu şekilde çoğaltılmıştır.

<h4> 2.1.8.  BREADBOARD </h4>
<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/4c7c6d54-650a-4483-9653-d4ed0e8bdaef" alt="image">
</div>

Teknik terim olarak devre tahtası olarak isimlendirilmektedir. Üzerine sensör bağlanarak arduino kartı ile sensörün bağlantısının sağlanmasında kullanılmaktadır.
• Gerilim: 300 V
• Akım: 3A ~ 5A
• Boyut: 17cm x 5.5cm

<h3> 2.2.	PROJEDE KULLANILAN YAZILIMLAR </h3>
Projede kullanılan arduino kodları Arduino IDE [4] ortamında yazılmıştır. Arduino IDE, Arduino için entegre geliştirme ortamıdır. C ve C++ programlama dilleri ile yazılmış bir platformlar arası uygulamadır. Arduino uyumlu kartlara program yazmak ve yüklemek için kullanılmaktadır. Lojistik regresyon algoritmasının eğitilmesi, veri setinin elde edilmesi ve ön işleme adımlarından geçirilmesi için C programlama dili kullanılmıştır.

<h3> 2.2.	PROJENİN GELİŞTİRİLME AŞAMALARI </h3>

Projenin geliştirilme aşamaları Şekil 2’de bulunan akış şemasında görülmektedir.

<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/8e7c6b71-33f0-4caf-bb9b-8b46ff4ec4ea" alt="image">
</div>

<div align="center">
Şekil 2. Projenin geliştirilme aşamaları - Akış şeması
</div>

Projede öncelikle veri seti araştırılması yapılmıştır. Arduino UNO kartı ile uyumlu sensörlerden okunabilecek veriler ile birlikte kullanılabilecek uygun veri setleri araştırılmıştır. Araştırmalar sonucunda Kaggle sitesi üzerinden yangın alarmı için oluşturulmuş yaklaşık 63 bin adet veriden oluşan ‘Smoke Detection’ [5] adlı veri setinin kullanılmasına karar verilmiştir. Veri seti etiket sütunu hariç 14 farklı özellikten oluşmaktadır. Sensörler yardımı ile hangi verilerin elde edilebileceğine karar verilmiştir ve kullanılmayacak olan özellik sütunları veri setinden çıkarılmıştır. Veri seti etiketleri “1” ve “0” olmak üzere iki sınıftan oluşmaktadır. “1” sınıfına ait veri sayısı 44.760, “0” sınıfına ait veri sayısı ise 17.871’dir. Algoritma eğitiminde veri setinde dengesizlik olmaması için veri seti karıştırılarak her iki sınıftan da 17.871 adet veri kullanılmıştır. Toplamda 35.742 adet veri kullanılmıştır. Bu verilerin %80’i eğitim verisi, %20’si test verisi olarak kullanılmak üzere ayrılmıştır. Eğitim ve test verileri dosyalara kayıt edilmiştir.

Veri setinin ön işleme adımları tamamlandıktan sonra Lojistik regresyon algoritması C programlama dilli kullanılarak kodlanmıştır. Lojistik regresyon, bir sınıflandırma algoritmasıdır. İstatistik ve makine öğrenimi alanlarında sıkça kullanılan bir yöntemdir. Genellikle ikili sınıflandırma problemlerinde kullanılmaktadır. Lojistik regresyon, bağımsız değişkenlerin bir kombinasyonunu kullanarak bir bağımlı değişkenin olasılığını tahmin etmek için kullanılmaktadır. Lojistik regresyon, yüksek doğruluk ve yorumlanabilirlik sağlamaktadır, bu nedenle özellikle tıp, ekonomi, pazarlama ve diğer birçok alanda kullanılmaktadır. Lojistik regresyon sınıflandırma problemlerinde aktivasyon fonksiyonu olarak “sigmoid” kullanmaktadır. Aktivasyon fonksiyonu, bir yapay sinir ağı veya derin öğrenme modelinde bir nöronun çıktısını belirlemek için kullanılan bir matematiksel işlemdir. Sigmoid aktivasyon fonksiyonu verileri 0 ve 1 arasında sıkıştırmaktadır. Sigmoid fonksiyonundan elde edilen çıktı belirlenen eşit değerine göre “0” ve “1” sınıfına atanmaktadır. Sigmoid aktivasyon fonksiyonunun hesaplanma formülü Denklem 1’de görülmektedir. 
<br>
<div align="center">
𝑆(𝑥)= 11+ 𝑒−𝑥       (1)
</div>
<br>
Lojistik regresyonda, veri setindeki girdiler başlangıçta rastgele olarak tanımlanan ağırlık değerleri ile çarpılmaktadır. Her bir girdi ağırlık değerleri ile çarpılarak toplanmaktadır. Elde edilen bu toplam sigmoid fonksiyonuna gönderilmektedir. Sigmoid fonksiyonundan gelen sonuca göre sınıflandırma işlemi gerçekleşmektedir. Sonrasında elde edilen tahmin sonucu ve gerçek etiket değeri ile bir kayıp değeri hesaplanmaktadır. Hesaplanan kayıp değeri öğrenme oranı ve veri ile çarpılarak ağırlık değerleri güncellenmektedir. Öğrenme oranı, bir makine öğrenimi algoritmasında kullanılan bir hiper parametredir ve modelin ne kadar hızlı veya yavaş öğrenmesi gerektiğini belirlemektedir. Öğrenme oranı, her bir iterasyonda model parametrelerini güncelleme miktarını kontrol eder. Güncellenen ağırlık değerleri ile Lojistik regresyon algoritması tekrar eğitim, tahmin ve kayıp değeri hesaplama aşamalarından geçmektedir. Her bir iterasyonda kayıp değeri ve doğruluk değeri hesaplanmıştır. Belirlenen iterasyon sayısı kadar bu işlemler devam etmektedir. Her iterasyonda hesaplanan doğruluk değerleri karşılaştırılarak en yüksek doğruluk değerinin elde edildiği ağırlık değerleri “TrainResults.txt” dosyasına kayıt edilmiştir. En başarılı sonucu veren ağırlık değerleri test için ayrılan veriler üzerinde test edilmiştir. Test sonucunda karışıklık matrisi (confusion matrix), doğruluk, kesinlik (precision), hassasiyet (recall) ve F1-skor performans metrikleri hesaplanmıştır. Hesaplanan değerler “TestResults.txt” dosyasına kayıt edilmiştir.

Karışıklık matrisi, sınıflandırma algoritmalarının performansını değerlendirmek için kullanılan bir metriktir. Bu matris, tahmin edilen sınıfların gerçek sınıflarla karşılaştırılmasını sağlar. Karışıklık matrisi True Positive (TP), True Negative (TN), False Positive (FP) ve False Negative (FN) değerlerinden oluşmaktadır.
• TP: Gerçek değerin 1 ve tahmin edilen değerin de 1 olduğu örneklerdir.
• TN: Gerçek değerin 0 ve tahmin edilen değerin de 0 olduğu örneklerdir.
• FP: Gerçek değerin 0 ancak tahmin edilen değerin 1 olduğu örneklerdir.
• FN: Gerçek değerin 1 ancak tahmin edilen değerin 0 olduğu örneklerdir.

Doğruluk değeri, doğru tahminlerin yüzdesel oranını belirtmektedir. Doğruluk değerinin hesaplanma formülü Denklem 2’de görülmektedir.
<br> 
<div align="center">
𝐷𝑜ğ𝑟𝑢𝑙𝑢𝑘= 𝑇𝑃+𝑇𝑁𝑇𝑃+𝑇𝑁+𝐹𝑃+𝐹𝑁∗100      (2)
</div>
<br>
Kesinlik, pozitif olarak tahmin edilen değerlerin gerçekten kaç tanesinin pozitif olduğunu göstermektedir. Kesinlik değerinin hesaplanma formülü Denklem 3’te görülmektedir. 
<br>
<br>
<div align="center">
𝐾𝑒𝑠𝑖𝑛𝑙𝑖𝑘= 𝑇𝑃𝑇𝑃+𝐹𝑃       (3)
</div>
<br>
Hassasiyet ise pozitif olarak tahmin edilmesi gereken işlemlerin ne kadarının pozitif olarak tahmin edildiğini gösteren bir metriktir. Hassasiyet değerinin hesaplanma formülü Denklem 4’te görülmektedir. 
<br>
<br>
<div align="center">
𝐻𝑎𝑠𝑠𝑎𝑠𝑖𝑦𝑒𝑡= 𝑇𝑃𝑇𝑃+𝐹𝑁     (4)
</div>
<br>
F1-skor değerinin kullanılmasının en temel sebebi eşit dağılmayan veri kümelerinde hatalı bir seçim yapmamaktır. Ayrıca sadece yanlış negatif ya da yanlış pozitif değil tüm hata maliyetlerini de içerecek bir ölçme metriğine ihtiyaç duyulduğu için F1-skor çok önemlidir. F1-skor değeri doğru pozitif, yanlış pozitif ve yanlış negatif değerleri ile hesaplanmaktadır. F1-skor değerinin hesaplanma formülü Denklem 5’te görülmektedir. 
<br>
<br>
<div align="center">
𝐹1−𝑠𝑘𝑜𝑟=2∗ 𝑘𝑒𝑠𝑖𝑛𝑙𝑖𝑘∗ℎ𝑎𝑠𝑠𝑎𝑠𝑖𝑦𝑒𝑡𝑘𝑒𝑠𝑖𝑛𝑙𝑖𝑘+ℎ𝑎𝑠𝑠𝑎𝑠𝑖𝑦𝑒𝑡       (5)
</div>
<br>
Lojistik regresyon algoritmasının çalıştırılması tamamlandıktan ve sonuçlar elde edildikten sonra Arduino kartı ile sensör bağlantıları gerçekleştirilmiştir. Arduino kartı ve sensör bağlantılarının detaylı gösterimi Şekil 3’te görülmektedir.

<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/6a64a7a7-a7bc-42e2-986e-b48d4994f593" alt="image">
</div>

<div align="center">
Şekil 3. Arduino kartı ve sensör bağlantıları
</div>

En başarılı sonucun elde edildiği ağırlık değerleri Arduino koduna bir dizi olarak tanımlanmıştır. Arduino kodu içerisinde sigmoid aktivasyon fonksiyonu ve Lojistik regresyon kodlamaları yapılmıştır. Sonrasında kullanılan sensörlerden veriler okunarak, tanımlanan ağırlık değerleri ile tahmin işlemi gerçekleştirilmiştir. Tahmin işleminin sürekli olmaması için Arduino koduna Timer kesmesi eklenmiştir. 5 dakika aralıklar ile sensörden gelen verilerden tahmin işlemi gerçekleştirilmektedir. Gerçekleştirilen tahmin işlemine göre “1” sınıfı yangın riskini temsil etmektedir bu sebeple kırmızı led ve buzzer çalışmaktadır. “0” sınıfı tahmin edildiğinde ise risk yok anlamında yeşil led çalışmaktadır. Sistemin çalışması Şekil 4’te görülmektedir.
<div align="center">
<table>
    <tr>
        <td>
            <img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/496f267a-4629-4b46-9533-59c4dcca4e3a">
        </td>
        <td>
            <img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/595ab5fb-6254-43d2-ae77-c8e9bae0c9fa">
        </td>
    </tr>
</table>
</div>

<h2> 3.	DENEYSEL SONUÇLAR </h2>

Lojistik regresyon algoritması 1000 iterasyon ve 0.05 öğrenme oranı ile çalıştırılmıştır. Gerçekleştirilen sınıflandırma eğitiminde, eğitim sürecinde elde edilen maksimum doğruluk değeri %85.30 ve kayıp değeri (mean squared error – mse) 0.146989’dur. En başarılı sonuç 878’inci iterasyonda elde edilmiştir. En başarılı sonucu veren ağırlık değerleri test verilerinin tahmininde kullanılmıştır. Test verilerinden elde edilen performans metrikleri Tablo 1’de görülmektedir.
<div align="center">
<table>
    <tr>
        <td>
            <b>Doğruluk (%)</b>
        </td>
        <td>
            <b>Kayıp**</b>
        </td>
                <td>
            <b>Kesinlik (%)**</b>
        </td>
        <td>
            <b>Hassasiyet (%)</b>
        </td>
                <td>
            <b>F1-skor (%)</b>
        </td>
    </tr>
            <td>
            85.73
        </td>
        <td>
            0.142677
        </td>
                <td>
            82
        </td>
        <td>
            94 
        </td>
                <td>
            87 
        </td>
    <tr>
    </tr>
</table>
</div>

Test verileri kullanılarak hesaplanan karışıklık matrisi verileri görselleştirilmiştir. Oluşturulan karışıklık matrisi Şekil 5’te görülmektedir.

<div align="center">
<img src="https://github.com/hediyeorhan/LogisticRegressionWithArduino/assets/59260491/ae030fa7-946a-4357-9cba-e0f455ad6615" alt="image">
</div>

<div align="center">
Şekil 5. Karışıklık matrisi
</div>

<h2> 4.	SONUÇ </h2>

Yangın tespiti için geliştirilen sistem, Arduino UNO kartı ve entegre sensörlerin kullanımıyla birlikte başarılı bir şekilde gerçekleştirilmiştir. Çeşitli veri noktalarının (hava basıncı, sıcaklık, nem, havadaki alkol ve H2 miktarı) entegrasyonuyla, sistem yangın tespitinde başarılı bir performans sergilemiştir. Geliştirilen yaklaşımın, geleneksel yangın tespit sistemlerine kıyasla daha doğru yangın riski belirleme ve yanlış alarm riskini azaltma potansiyeli olduğu gözlemlenmiştir. Çalışmanın sonuçları, birden fazla verinin değerlendirilmesiyle yangın tespit sisteminin performansının artabileceğini ortaya koymaktadır. Gelecekteki çalışmalarda, veri setinin boyutunun artırılması, farklı makine öğrenme yöntemlerinin test edilmesi, farklı sensörler ile daha fazla kullanılabilecek veri okunması ve elde edilen başarı oranının artırılması düşünülmektedir.

<h2> KAYNAKLAR </h2>

[1] A. Datasheet. Available: https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf
<br>
[2] J. M. Hilbe, "Logistic regression," International encyclopedia of statistical science, vol. 1, pp. 15-32, 2011.
<br>
[3] M. Banzi and M. Shiloh, Getting started with Arduino: Maker Media, Inc., 2022.
<br>
[4] Arduino ide. Available: https://www.arduino.cc/en/software
<br>
[5] Smoke Detection. Available: https://www.kaggle.com/datasets/deepcontractor/smoke-detection-dataset