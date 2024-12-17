#include <stdio.h> // Standart giriş çıkış fonksiyonlarını kullanmak için stdio.h kütüphanesini kodumuza ekliyoruz.
#include <string.h> // strcmp fonksiyonunu kullanmak için string.h kütüphanesini kodumuza ekliyoruz.

#define MAX_URUN_SAYISI 11 // Sipariş edilebiliecek ürün sayısının 11 olduğunu beliritiyoruz.
#define MAX_SATIR_UZUNLUGU 15 // En uzun ürün adının 13 karakter oluştuğunu belirtiyoruz. (Dizilerin sonundaki \0 ve fgets fonksiyonun sonundaki \n ile 15 oluyor).

// Ürünlerin kalori bilgilerini tutan yapı
typedef struct {
    char urun_adi[MAX_SATIR_UZUNLUGU];
    int kalori;
} Urun; // Daha sonra Urun isimli bir nesne oluşturacağımızı belirtiyoruz.

// Sipariş edilen ürünleri tutan yapı
typedef struct {
    char urun_adi[MAX_SATIR_UZUNLUGU];
    float porsiyon;  // Kesirli porsiyonlar için porsiyon değişkenini float yapıyoruz.
} Siparis; // Daha sonra Siparis isimli bir nesne oluşturacağımızı belirtiyoruz.


int main() {
    FILE *kaloriDosyasi, *siparisDosyasi; // Burada kalori ve siparis dosyalarına erişebilmek için pointerları kullanıyoruz.

    Urun urunler[MAX_URUN_SAYISI]; /* Burada kalori dosyasındaki ürünlerin adı ve kalori sayısını tutmak için oluşturduğumuz "Urun" yapısını
    birden fazla ürün tutmak için "urunler" dizisini tanımlıyoruz. */

    Siparis siparisler[MAX_URUN_SAYISI]; /* Burada siparis dosyasındaki ürünlerin adı ve kalori sayısını tutmak için oluşturduğumuz "Siparis" yapısını
    birden fazla ürün tutmak için "siparis" dizisini tanımlıyoruz. */

    int urunSayisi = 0, siparisSayisi = 0; // Ürün sayısını ve Sipariş sayısını tutacak değişkenlerimizi ekliyoruz.
    char satir[MAX_SATIR_UZUNLUGU];
    float toplamKalori = 0.0;

    // Kalori dosyasını okuma modunda açıyoruz
    kaloriDosyasi = fopen("C:/Users/user/Desktop/kalori.txt", "r");
    if (kaloriDosyasi == NULL) // Eğer kalori dosyasını okumada hata oluşursa veya dosya boşsa uyarı vererek programı sonlandırır.
        {
        perror("Kalori dosyası açılamadı"); // Hata mesajını vermek için perror fonksiyonunu kullanıyoruz.
        return 1;
    }

    // Kalori dosyasını okuma
    while (fgets(satir, sizeof(satir), kaloriDosyasi)) // Kalori dosyasından bir satır okunup okunan satır line dizisine yazılır
        // Okumanın hatalı olmasına veya dosyanın bitişine kadar döngü devam eder. Yiyecekler bittiğinde fgets "NULL" değeri döndürür.
        {
        sscanf(satir, "%s %d", urunler[urunSayisi].urun_adi, &urunler[urunSayisi].kalori);
        // sscanf ile string okuma formatıyla kalori dosyasını okur | line komutu ile kalori dosyasındaki yiyeceği ve kalorisini tek tek alır.
        // %s ile yiyeceğin ismini string formatında, %d ile kalorisini tam sayı olarak alır.
        urunSayisi++;
        // Kalori dosyasındaki yiyecek sayısını sayan sayaç.
    }
    fclose(kaloriDosyasi); // Döngü bittikten sonra kalori dosyasını kapatır.

    // Sipariş dosyasını açıyoruz
    siparisDosyasi = fopen("C:/Users/user/Desktop/siparis.txt", "r");
    if (siparisDosyasi == NULL) {
        perror("Sipariş dosyası açılamadı");
        return 1;
    }

    // Sipariş dosyasını okuma
    while (fgets(satir, sizeof(satir), siparisDosyasi)) {
        // Siparişi ürün adı ve porsiyon sayısına ayırır.
        sscanf(satir, "%s %f", siparisler[siparisSayisi].urun_adi, &siparisler[siparisSayisi].porsiyon);
        siparisSayisi++;
    }
    fclose(siparisDosyasi);

    // Siparişlerin toplam kalorisini hesaplama
    for (int i = 0; i < siparisSayisi; i++) {
        for (int j = 0; j < urunSayisi; j++) {
            if (strcmp(siparisler[i].urun_adi, urunler[j].urun_adi) == 0)
                // Burada siparişimizin içindeki yiyecek adının kalori dosyasında olup olmadığı kontrol ediliyor.
                {
                toplamKalori += urunler[j].kalori * siparisler[i].porsiyon; // Eğer varsa kalori değerini alıp porsiyon sayısıyla çarpıp toplam kalori değişkenine ekliyoruz.
                break; // Yiyeceğin kalori miktarını hesapladıktan sonra diğer ürüne geçmek için
            }
        }
    }

    // Toplam kaloriyi ekrana yazdırma
    printf("Toplam Kalori: \n %.2f\n", toplamKalori);

    return 0;
}