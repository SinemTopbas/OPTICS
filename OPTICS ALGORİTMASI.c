#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 100
#define UNDEFINED -1
#define UNVISITED -2

// Nokta yapýsý x ve y koordinatlarýný içerir.
struct Nokta {
    double x, y;
};

// Nokta dizisi ve nokta sayýsýný tutan deðiþkenler tanýmlanýr.
struct Nokta noktalar[MAX_POINTS];
int noktaSayisi;

// Kullanýcýdan nokta bilgilerini alan fonksiyon
struct Nokta kullanicidanNoktaAl() {
    struct Nokta n;
    printf("x koordinatini girin: ");
    scanf("%lf", &n.x);
    printf("y koordinatini girin: ");
    scanf("%lf", &n.y);
    return n;
}

// Ýki nokta arasýndaki Euclidean uzaklýðýný hesaplayan fonksiyon
double uzaklikHesapla(struct Nokta n1, struct Nokta n2) {
    return sqrt(pow(n1.x - n2.x, 2) + pow(n1.y - n2.y, 2));
}

// Geniþleme sýrasýný uygulayan yardýmcý fonksiyon
void genislemeSirasi(int index, int kumeID, double epsilon, int minPts, int kumeIDs[], double ulasilabilirlikUzakliklari[]) {
    int i;
    for (i = 0; i < noktaSayisi; i++) {
        if (ulasilabilirlikUzakliklari[i] <= epsilon && kumeIDs[i] == UNDEFINED) {
            kumeIDs[i] = kumeID;
            if (i != index)
                genislemeSirasi(i, kumeID, epsilon, minPts, kumeIDs, ulasilabilirlikUzakliklari);
        }
    }
}

// OPTICS algoritmasýný uygulayan ana fonksiyon
void optics(double epsilon, int minPts, int kumeIDs[], double ulasilabilirlikUzakliklari[]) {
    int i, j;
    int kumeID = 0;

    for (i = 0; i < noktaSayisi; i++) {
        if (kumeIDs[i] == UNDEFINED) {
            kumeIDs[i] = kumeID;

            // Her noktanýn komþu uzaklýklarýný hesaplamak için bellek ayrýlýr
            double* komsuUzakliklar = malloc(noktaSayisi * sizeof(double));
            for (j = 0; j < noktaSayisi; j++) {
                if (i != j)
                    komsuUzakliklar[j] = uzaklikHesapla(noktalar[i], noktalar[j]);
                else
                    komsuUzakliklar[j] = INFINITY;
            }

            int cekirdekUzaklikIndeksi = -1;
            double cekirdekUzaklik = INFINITY;

            // Çekirdek uzaklýðý ve indeksi belirleme
            for (j = 0; j < noktaSayisi; j++) {
                if (komsuUzakliklar[j] <= epsilon) {
                    int komsuSayisi = 0;
                    int k;

                    // Belirlenen epsilon içindeki komþu noktalarýn sayýsýný hesapla
                    for (k = 0; k < noktaSayisi; k++) {
                        if (komsuUzakliklar[k] <= epsilon)
                            komsuSayisi++;
                    }

                    // MinPts koþulunu saðlayan ve en yakýn noktayý belirleme
                    if (komsuSayisi >= minPts && komsuUzakliklar[j] < cekirdekUzaklik) {
                        cekirdekUzaklik = komsuUzakliklar[j];
                        cekirdekUzaklikIndeksi = j;
                    }
                }
            }

            // Çekirdek nokta varsa geniþleme sýrasýný uygulama
            if (cekirdekUzaklikIndeksi != -1) {
                genislemeSirasi(i, kumeID, epsilon, minPts, kumeIDs, ulasilabilirlikUzakliklari);
                for (j = 0; j < noktaSayisi; j++) {
                    if (kumeIDs[j] == kumeID && komsuUzakliklar[j] > cekirdekUzaklik)
                        ulasilabilirlikUzakliklari[j] = fmax(cekirdekUzaklik, komsuUzakliklar[j]);
                }
                kumeID++;
            }

            // Bellek temizleme
            free(komsuUzakliklar);
        }
    }
}

int main() {
    int i;

    printf("Nokta sayisini girin: ");
    scanf("%d", &noktaSayisi);

    printf("Noktalarin koordinatlarini girin:\n");
    for (i = 0; i < noktaSayisi; i++) {
        printf("Nokta %d:\n", i + 1);
        noktalar[i] = kullanicidanNoktaAl();
    }

    double epsilon;
    int minPts;
    int kumeIDs[MAX_POINTS];
    double ulasilabilirlikUzakliklari[MAX_POINTS];

    printf("Epsilon degerini girin: ");
    scanf("%lf", &epsilon);
    printf("minPts degerini girin: ");
    scanf("%d", &minPts);

    // Küme ID'leri ve ulaþýlabilirlik uzaklýklarýný baþlangýç deðerleriyle ayarla
    for (i = 0; i < noktaSayisi; i++) {
        kumeIDs[i] = UNDEFINED;
        ulasilabilirlikUzakliklari[i] = INFINITY;
    }

    // OPTICS algoritmasýný uygula
    optics(epsilon, minPts, kumeIDs, ulasilabilirlikUzakliklari);

    // Küme atamalarýný ekrana yazdýr
    printf("Kume Atamalari:\n");
    for (i = 0; i < noktaSayisi; i++) {
        printf("Nokta %d -> Kume %d\n", i + 1, kumeIDs[i]);
    }

    return 0;
}
