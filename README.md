# OPTICS
Bu program, kullanıcıdan nokta sayısını, noktaların koordinatlarını, epsilon (ε) değerini ve minPts değerini alır. Daha sonra OPTICS algoritmasını kullanarak her noktayı bir kümeye atar ve sonuçları ekrana yazdırır.  
Başlangıçta, gerekli kütüphaneler (stdio.h, stdlib.h, math.h) dahil edilir ve bazı sabitler tanımlanır.

struct Nokta yapısı tanımlanır, bu yapı x ve y koordinatlarını tutar.

noktalar adında bir dizi tanımlanır ve bu dizi, struct Nokta türünden noktaların koordinatlarını saklar. Dizi, en fazla MAX_POINTS kadar nokta içerebilir.

noktaSayisi değişkeni tanımlanır ve kullanıcıdan alınacak nokta sayısını tutar.

kullanicidanNoktaAl() fonksiyonu, kullanıcıdan bir nokta alır ve bu noktanın x ve y koordinatlarını döndürür.

uzaklikHesapla() fonksiyonu, iki nokta arasındaki öklidyen uzaklığını hesaplar ve sonucu döndürür.

genislemeSirasi() fonksiyonu, genişleme sırasını gerçekleştirir. Bu fonksiyon, belirli bir noktadan başlayarak, epsilon (ε) değeri ve minPts parametresine göre komşuluk ilişkisini kontrol ederek noktaları kümelere atar.

optics() fonksiyonu, OPTICS algoritmasının gerçekleştirildiği ana fonksiyondur. Bu fonksiyon, her bir noktayı tek tek dolaşarak, henüz kümeye atılmamış noktalar için genişleme sırasını çağırır ve kümeleri oluşturur.

main() fonksiyonu, programın giriş noktasıdır. İlk olarak, nokta sayısını kullanıcıdan alır. Ardından, noktaların koordinatlarını kullanıcıdan alır ve noktalar dizisine kaydeder. Epsilon (ε) ve minPts değerlerini kullanıcıdan alır.

kumeIDs ve ulasilabilirlikUzakliklari dizileri tanımlanır. kumeIDs dizisi, her noktanın hangi kümede olduğunu tutar. ulasilabilirlikUzakliklari dizisi, her noktanın ulasilabilirlik uzaklığını saklar.

optics() fonksiyonu çağrılır ve OPTICS algoritması çalıştırılır.

Son olarak, noktaların hangi kümeye ait olduğu ekrana yazdırılır.

Bu şekilde program, kullanıcının girdiği noktaları OPTICS algoritmasına tabi tutar ve her noktayı bir kümeye atar.
