#include <iostream> // Bu kutuphane olmazsa olmazimizdir.
#include <fstream> // Bu kutuphaneyi dosyalarimiz icin kullaniriz. Örneğin(Dosyadan veri okuyabilir. Dosyaya veri yazabilir)
#include <string> // Bu kutuphaneyi metinlerimiz icin kullaniriz. Metinsel islemlerde isimize yarar.
#include <limits> // Kullanici uygun olmayan karakter girdiginde yazmamiz gereken fonksiyonlari yazdigimizde gerekli olsun diye bu kutuphaneyi cagirdik
using namespace std; // Her kodda std:: yazmamizi onlemek icin kullandik

const int Max_Kitap = 100; //Maksimum kitap sayisini 100 olarak belirledigimiz icin yazdik.

struct Kitap { //Kitap bilgilerimizi tutmaya yarayan veri tipidir
    string kitap_baslik; //String olarak Kitap Basligini belirledik
    string kitap_yazari; //String olarak Kitap Yazarini belirledik
    int kitap_yili; //Integer olarak Kitap Yilini belirledik
    string kitap_isbn; //String olarak Kitap ISBN belirledik
};

Kitap Kitap_Verileri[Max_Kitap]; //Kitaplarimizi saklamak icin bir dizi olusturduk
int Kitap_Sayisi = 0; //Kitap sayimizi 0 olarak belirledik


void Kitap_Ekle() { //Kitap_Ekle diye fonksiyon actik. Kitaplarimizi bu fonksiyon uzerinden ekleyecegiz.
    ifstream dosya("Kitap_Verileri.txt"); //Kitap_Verileri adında dosya açar ve bu dosyayı okumamizi saglar.
    if (!dosya) { //Eğer dosya yok ise
        cout << "Verileri Kaydedilecek Dosya Acilamadi veya Bulunamadi" << endl; //Bu mesajı yazdir
        cout << "Sizin Icin Hemen Yeni Dosya Olusturuluyor...\n" << endl; //Bu mesajı yazdir
        return; //Ve bu if blogunu sonlandir
    }

    Kitap_Sayisi = 0; //Kitap Sayisini 0 yaptik cunku daha iyi dogru okumayi saglar
    while (dosya && Kitap_Sayisi < Max_Kitap) { //Bir dongu baslattik. ilk olarak dosyasinin var olmasi lazim VE Kitap_Sayisi < Max_Kitap olsun dedik.
        getline(dosya, Kitap_Verileri[Kitap_Sayisi].kitap_baslik); //Getline sayesinde dosyanin okunmasini sagladik. Bu satiri kitap_baslik olarak sakladik.
        getline(dosya, Kitap_Verileri[Kitap_Sayisi].kitap_yazari); //Getline sayesinde dosyanin okunmasini sagladik. Bu satiri kitap_yazari olarak sakladik.
        dosya >> Kitap_Verileri[Kitap_Sayisi].kitap_yili; //Dosyadan veri okumak icin bu kodu yazdik. Amacimiz sadece tamsayi okumak
        dosya.ignore(numeric_limits<streamsize>::max(), '\n');  //Dosya akisini saglamak icin bir alt satira indik.
        getline(dosya, Kitap_Verileri[Kitap_Sayisi].kitap_isbn); //Getline sayesinde dosyanin okunmasini sagladik. Bu satiri kitap_isbn olarak sakladik.

        if (!dosya.fail()) { //Yukaridaki islemlerde bir hata olusmadi ise
            Kitap_Sayisi++; //Kitap sayisini 1 arttir
        }
    }
    dosya.close(); //Dosyayi kapat
} //Fonksiyonu bitirdik

void Kitap_Kaydet() { //Kitap Bilgilerini dosyaya kaydetmek icin kullaniriz.
    ofstream dosya("Kitap_Verileri.txt"); //Bir cikis dosyasi olusturur. Eger dosya varsa uzerine yazar. Yoksa dosya olusturur
    if (!dosya) { //Eger dosyanin aciliminda hata varsa
        cout << "Dosya Yazilamadi. Lutfen Daha Sonra Tekrar Deneyiniz"; //Bu mesaji output yaptik
        return; //Dosya acilmadigi icin fonksiyonu sonlandirdik
    }

    for (int i = 0; i < Kitap_Sayisi; i++) {
        dosya << "Kitap Basligi: " << Kitap_Verileri[i].kitap_baslik << endl //Dosyaya Kitap Basligin yazar ve alt satira iner
              << "Kitap Yazari: " << Kitap_Verileri[i].kitap_yazari << endl //Dosyaya Kitap Yazarini yazar ve alt satira iner
              << "Kitap Uretim Yili: " << Kitap_Verileri[i].kitap_yili << endl //Dosyaya Kitap Yilini yazar ve alt satira iner
              << "Kitap ISBN Degeri: " << Kitap_Verileri[i].kitap_isbn << endl << endl << endl; //Dosyaya Kitap ISBN degerini yazar ve alt satira iner
    }
    dosya.close(); //Dosyayi kapatir
} //Fonksiyonu bitirdik

void Kitap_Ekleme() { //Kitap Eklemek icin fonksiyon olusturduk
    if (Kitap_Sayisi >= Max_Kitap) { //Eger kitap sayimiz Max Degerimiz (100)'den fazla ise
        cout << "Maksimim Kitap Sayisina Ulastiniz !!!" << endl;
        cout << "Mevcut Kitap Sayiniz: " << Kitap_Sayisi << endl;
        cout << "Maximum Kitap Sayisi: \n\n" << Max_Kitap << endl; //Bunu yaz
        return; //Fonksiyonu durdur. Asagidakileri okuma
    } //Fonksiyonu bitirdik

    Kitap Yeni_Kitap; //Kitap veri yapisinda degisken olusturduk
    cout << "Lutfen Kitap Adini Giriniz: "; //Kullaniciya bu mesaji gosterir
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Onceki girislerden kalan verileri temizler
    getline(cin, Yeni_Kitap.kitap_baslik); //Kullanicidan metin alir ve yanindaki degiskene atar.

    cout << "Lutfen Kitap Yazarini Giriniz: "; //Kullaniciya bu mesaji gosterir
    getline(cin, Yeni_Kitap.kitap_yazari); //Kullanicidan metin alir ve yanindaki degiskene atar.
    cout << "Lutfen Kitap Yayin Yilini Giriniz: "; //Kullanicidan metin alir ve yanindaki degiskene atar.
    while (!(cin >> Yeni_Kitap.kitap_yili) || Yeni_Kitap.kitap_yili < 0) { //Kullanicidan tam sayi alir. Eger kullanici gecerli sayi veya 0'dan kucuk deger girerse bu kosulu calistir
        cout << "Lutfen Gecerli Bir Yil Giriniz: "; //Ekrana bu mesaji yazdirir
        cin.clear(); //Giris akisindaki hatayi temizlememize yardim eder
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Hatali verileri temizler
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Kalan verileri temizle
    cout << "Lutfen Kitap \"ISBN Numarasi\" Giriniz: "; //ISBN Ekrana yazdir
    getline(cin, Yeni_Kitap.kitap_isbn); //Kullanicidan metin alir ve yanindaki degiskene atar.

    Kitap_Verileri[Kitap_Sayisi] = Yeni_Kitap; //Kullanicidan aldigimiz kitap bilgilerini kaydeder
    Kitap_Sayisi++; //Yeni kitap ekledigimiz icin 1 arttirdik.
    cout << "\n\nKitap Basariyla Eklendi !\n\n\n" << endl; //Ekrana yaz
    Kitap_Kaydet(); //Ekledigimiz kitabi dosyaya kalici olarak ekledik.
} //Fonksiyonu bitirdik

void Kitap_Listesi() { //Kitaplarimizi listelemek istedigimiz icin bu fonksiyonu olusturduk
    if (Kitap_Sayisi == 0) { //Eger kitap sayimiz = 0 ise
        cout << "\nElimizde Herhangi Bir Kitap Yoktur." << endl; //Ekrana bunu yazdir
        cout << "Kitap Eklemeniz Gerekmektedir. Lutfen Kitap Ekleyiniz.\n\n\n" << endl; //Kullanicidan kitap girmesini istedigimiz icin ekrana bu komutu yazdirdik
        return; //Fonksiyonu sonlandirdik. Cunku kitabimiz yok
    }

    for (int i = 0; i < Kitap_Sayisi; i++) { //Sistemdeki kitaplara bakmak için dongu olusturduk
        cout << '\n' << i + 1 <<". Kitap Hakkinda Bilgiler:" << endl << endl; //Kacinci Kitap Oldugunu Yazdirdik
        cout << "Ad: " << Kitap_Verileri[i].kitap_baslik << endl; //Kitabin adinin ne oldugunu yazdirdik
        cout << "Yazar: " << Kitap_Verileri[i].kitap_yazari << endl; //Kitabin yazarinin kim oldugunu yazdirdik
        cout << "Yil: " << Kitap_Verileri[i].kitap_yili << endl; //Kitabin uretim tarihinin ne zaman oldugunu yazdirdik
        cout << "ISBN: " << Kitap_Verileri[i].kitap_isbn << endl << endl << endl;//Kitabin isbn numarasini yazdirdik
    }
} //Fonksiyonu bitirdik

void Kitap_Arama() { //Kitap aramasini gerceklestirmek icin bu fonksiyonu olusturduk
    cout  << '\n' << "Arama Kritlerini Giriniz (Kitap Basligi veya ISBN): "; //Ekrana bu mesaji yazdirdik
    string kullanici_giris; //Kullanicin girdigi karakterleri sakladik ve degiskene atadik
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Eski verileri temizler
    getline(cin, kullanici_giris); //Arama kismina girdigi karakterleri degiskene kaydeder

    bool KitapBul = false; //Arama sonucunda bulduk ya da bulamadik diyecegimiz icin bool yazdik. Bellek'te daha cok byte harcamamak icin
    for (int i = 0; i < Kitap_Sayisi; i++) { //Sistemdeki tum kitaplari sirayla kontrol etmek icin dongu olusturduk
        if (Kitap_Verileri[i].kitap_baslik.find(kullanici_giris) != string::npos || Kitap_Verileri[i].kitap_yazari.find(kullanici_giris) != string::npos) { //Kullanicinin girdigi karakterin, kitabin adinda veya yazarinda olup olmadigina baktik
            cout << '\n' << "Ad: " << Kitap_Verileri[i].kitap_baslik << endl; //Kosul saglandigi icin Adini yazdirdik
            cout << "Yazar: " << Kitap_Verileri[i].kitap_yazari << endl; //Yazarini yazdirdik
            cout << "Yil: " << Kitap_Verileri[i].kitap_yili << endl;  // Yilini yazdirdik
            cout << "ISBN: " << Kitap_Verileri[i].kitap_isbn<< endl << endl << endl; //ISBN numarasini yazdirdik
            KitapBul = true; //Eslesme bulundugu icin true yaptik
        }
    }

    if (!KitapBul) { //Kitaplar arasinda eslesme bulunmadiysa
        cout << "Kitap Bulunamadi. Lutfen Daha Sonra Tekrar Deneyiniz." << endl << endl << endl; //Ekrana bunu yazdir
    }
}

void Kitap_Silme() { //Kitaplari silmek icin kullanacagimiz fonksiyonu olusturduk
    cout << "Kitap Silmek Icin Lutfen \"Kitap Basligini\" veya \"ISBN\" degerini giriniz: "; //Ekrana bu mesaji yazdirdik
    string kullanici_giris; //Kullanicin girdigi bilgileri degiskene atadik
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Eski verileri temizler
    getline(cin, kullanici_giris); //Kullanicinin girdigi bilgileri degiskene kaydeder

    bool Kitap_Sil = false; //Silme islemini false ile baslattik cunku silme basariyla olup olmadigina bakmamiz icin
    for (int i = 0; i < Kitap_Sayisi; i++) { //Sistemdeki tum kitaplari kontrol etmek icin dongu baslattik
        if (Kitap_Verileri[i].kitap_baslik == kullanici_giris || Kitap_Verileri[i].kitap_isbn == kullanici_giris) { //Eger girilen bilgi, kitabin basligina veya kitabin isbn numarasina esit ise
            for (int j = i; j < Kitap_Sayisi - 1; j++) { //Silinecek kitabin altindakileri
                Kitap_Verileri[j] = Kitap_Verileri[j + 1]; // silinen kitabin uzerine yazdik ki dosya da cok karisiklik olmasin
            }
            Kitap_Sayisi--; //Kitap sayisini 1 azaltir. Bu kitap artik sistemde olmadigini belirtir
            Kitap_Sil = true; //Silme islemi basaril oldugunu belirttik
            break; //Islemler tamamlandigi icin donguden ciktik
        }
    }

    if (Kitap_Sil) { //Eger silme islemi true ise
        cout << "\nKitabi Basariyla Sildiniz !!!" << endl << endl << endl;  //Bunu yaz
        Kitap_Kaydet(); //ve silindigini dosyaya kaydet
    } else { //eger silme islemi false ise
        cout << "\nMaalesef Boyle Bir Kitap Bulunamadi. Lutfen Daha Sonra Tekrar Deneyiniz." << endl << endl << endl;  //Bunu yaz
    }
} //Fonksiyonu bitir

void Kitap_Guncelleme() { //Kitap bilgilerini guncellemek icin bu fonksiyonu olusturduk
    cout << "Guncellemek istediginiz \"Kitap Adi\" veya \"ISBN Numarasi\" Giriniz: "; //Ekrana yazdirdik
    string kullanici_giris; // Kullanicidan aldigimiz bilgileri yandaki degiskene atadik
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Eski verileri temizledik
    getline(cin, kullanici_giris); //Kullanicinin girdigi bilgiler yandaki degiskene kayit edilir.

    for (int i = 0; i < Kitap_Sayisi; i++) { //Sistemdeki tum kitaplari kontrol eder
        if (Kitap_Verileri[i].kitap_baslik == kullanici_giris || Kitap_Verileri[i].kitap_isbn == kullanici_giris) { //Eger kullanicinin girdigi bilgiler Kitap basligi veya ISBN Numarasina esit ise
            cout << "Mevcut Kitap Adi: " << Kitap_Verileri[i].kitap_baslik << "   " << "Yeni Kitap Adi: " ; //Kullaniciya kitabin eski adini gosterdik. Ve yeni kitap basligin yazmasini istedigimiz icin ekrana bu mesaji yazdirdik
            getline(cin, Kitap_Verileri[i].kitap_baslik); //Kullanicidan kitap basligi icin input istedik
            cout << "Mevcut Kitap Yazari: " << Kitap_Verileri[i].kitap_yazari << "   " << "Yeni Kitap Yazari: " ; //Kullaniciya kitabin eski yazarini gosterdik. Ve yeni kitap yazarini yazmasini istedigimiz icin ekrana bu mesaji yazdirdik
            getline(cin, Kitap_Verileri[i].kitap_yazari); //Kullanicidan kitap yazari icin input istedik
            cout << "Mevcut Kitap Yili: " << Kitap_Verileri[i].kitap_yili << "   " << "Yeni Kitap Yili: " ; //Kullaniciya kitabin eski yilini gosterdik. Ve yeni kitapin yeni yilini yazmamizi istedigimiz icin ekrana bu mesaji yazdirdik
            while (!(cin >> Kitap_Verileri[i].kitap_yili) || Kitap_Verileri[i].kitap_yili < 0) { //Eger kullanici uygun olmayan degerler yazar ise
                cout << "Lutfen Gecerli Bir Yil Giriniz: "; //Ekrana bunu yazdir
                cin.clear(); //input degerini temizler
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Eski verileri temizler
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Yil girisini tamamladigimiz icin yeni verilerle satir atladik
            cout << "Mevcut Kitap ISBN Numarasi: " << Kitap_Verileri[i].kitap_isbn << "   " << "Yeni ISBN Numarasi: " ; //Kullaniciya kitabin eski isbn numarasini gosterdik. Ve yeni kitapin yeni isbn yazmamizi istedigimiz icin ekrana bu mesaji yazdirdik
            getline(cin, Kitap_Verileri[i].kitap_isbn); //Kullanicidan kitap isbn degeri icin input istedik

            cout << '\n' << "Kitabi Basariyla Guncellendin. Tebrikler\n\n\n"; //Kitap basariyla guncellendigi icin ekrana yazdirdik
            Kitap_Kaydet(); //Kitabi dosyaya kaydettik
            return; //Fonksiyonu sonlandirdik
        }
    }

    cout << '\n' << "Maalesef Boyle Bir Kitap Bulunamadi." << endl << endl << endl; //Eger dongu basariyla sonlanmaz ise bunu yazdir
}

int main() { //Arayuz sisteminin baslangici
    Kitap_Ekle(); //Kitap ekleme icin veri alir ve kitabi veri tabanina kaydeder

    do { //Do-while kullandik cunku kullanici cikis istemedigi surece kosulu uygular
        cout << "Ince Memed Halk Kutuphanesi || Ismail Yaltirik\n\n"; //Kutuphane Basligi icin ekrana yazdirdik
        cout << "1. Kitap Eklemek Icin Tuslayiniz" << endl; //Kitap Eklemek icin ekrana yazdirdik
        cout << "2. Kitap Listelemek Icin Tuslayiniz" << endl; //Kitap Listelemek icin ekrana yazdirdik
        cout << "3. Kitap Aramak Icin Tuslayiniz" << endl; //Kitap Aramak icin ekrana yazdirdik
        cout << "4. Kitap Silmek Icin Tuslayiniz" << endl; //Kitap Silmek icin ekrana yazdirdik
        cout << "5. Kitap Guncellemek Icin Tuslayiniz" << endl;; //Kitap Guncellemek icin ekrana yazdirdik
        cout << "6. Cikmak Icin Tuslayiniz\n\n" << endl; // Cikmak icin ekrana yazdirdik
        cout << "Lutfen Sayi Seciniz: "; //Secimimizi gostermek icin ekrana yazdirdik

        string giris; //String cinsinden bir giris tamamladik
        cin >> giris; //Kullanicidan bilgi aldik
        int Secme_islemi; // Aldigimiz degeri tam sayiya dondurduk


        /**Hocam benim kendi ekledigim kod.
        Kodu defalarca calistirdiktan sonra sans eseri yanlis bir sey girdigimde
        sonsuza dogru gidiyordu. ben bu durumdan rahatsiz oldum ve bunu dusundum*/

        try { //Tekrar yazmasini istiyoruz
            Secme_islemi = stoi(giris); //Kullanicidan aldigimiz girisi degiskene atadik
        } catch (...) {  //Kullanici gecersiz bir sey girer ise
            cout << '\n' << "Gecersiz Secim! Lutfen bir Sayi girin.\n\n\n\n"; //Ekrana yazdir
            continue; //Donguyu yeniden baslatir tekrar secim yapmasini isteriz
        }


        if (Secme_islemi == 1) { //Eger kullanici 1.'yi secerse
            Kitap_Ekleme(); //Kitap ekleme fonksiyonunu cagir
        } else if (Secme_islemi == 2) { //Eger kullanici 2.'yi secerse
            Kitap_Listesi(); //Kitap listeleme fonksiyonunu cagir
        } else if (Secme_islemi == 3) { //Eger kullanici 3.'yi secerse
            Kitap_Arama(); //Kitap arama fonksiyonunu cagir
        } else if (Secme_islemi == 4) { //Eger kullanici 4.'yi secerse
            Kitap_Silme(); //Kitap silme fonksiyonunu cagir
        } else if (Secme_islemi == 5) { //Eger kullanici 5.'yi secerse
            Kitap_Guncelleme(); //Kitap guncelleme fonksiyonunu cagir
        } else if (Secme_islemi == 6) { //Eger kullanici 6.'yi secerse
            cout << endl << "Kutuphane Sisteminden Cikiliyor..." << endl <<endl; //Cikis yap komutu yaz
            break; //Programi sonlandir
        } else { //Degil ise
            cout << '\n' << "Seciminiz Gecersiz. Lutfen Tekrar Deneyiniz" << endl << endl << endl; //Bunu yaz
        }
    } while (true); //Eger dongu true ise

    return 0; //Donguyu durdur
}
