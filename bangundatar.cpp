#include <iostream>
#include <cmath>
#include <string>
#include <functional>
#include <iomanip>

using namespace std;

// STRUCT — mendefinisikan entitas/objek Bangun Datar
struct BangunDatar {
    string nama;
    double luas;
    double keliling;
};


// NAMESPACE — membungkus fungsi logika utama program
namespace GeometriCalc {

    const double PI = 3.14159265358979323846;

    // INLINE FUNCTION — fungsi pendek untuk format garis pemisah
    inline void cetakGaris() {
        cout << string(50, '=') << endl;
    }

    // INLINE FUNCTION — fungsi pendek untuk cetak judul section
    inline void cetakJudul(const string& judul) {
        cout << "  [ " << judul << " ]" << endl;
    }

    // REFERENCES (&) — parameter dilewatkan via referensi
    //  Persegi 
    void hitungPersegi(double sisi, BangunDatar& hasil) {
        hasil.nama     = "Persegi";
        hasil.luas     = sisi * sisi;
        hasil.keliling = 4 * sisi;
    }

    // Persegi Panjang 
    void hitungPersegiPanjang(double panjang, double lebar, BangunDatar& hasil) {
        hasil.nama     = "Persegi Panjang";
        hasil.luas     = panjang * lebar;
        hasil.keliling = 2 * (panjang + lebar);
    }

    // Segitiga 
    void hitungSegitiga(double alas, double tinggi,
                        double sisi_a, double sisi_b, double sisi_c,
                        BangunDatar& hasil) {
        hasil.nama     = "Segitiga";
        hasil.luas     = 0.5 * alas * tinggi;
        hasil.keliling = sisi_a + sisi_b + sisi_c;
    }

    // Lingkaran 
    void hitungLingkaran(double jariJari, BangunDatar& hasil) {
        hasil.nama     = "Lingkaran";
        hasil.luas     = PI * jariJari * jariJari;
        hasil.keliling = 2 * PI * jariJari;  // Keliling = Keliling
    }

    // Trapesium 
    void hitungTrapesium(double sisiAtas, double sisiBawah,
                         double tinggi, double kaki_a, double kaki_b,
                         BangunDatar& hasil) {
        hasil.nama     = "Trapesium";
        hasil.luas     = 0.5 * (sisiAtas + sisiBawah) * tinggi;
        hasil.keliling = sisiAtas + sisiBawah + kaki_a + kaki_b;
    }

    // POINTER — fungsi mencetak hasil melalui pointer
    void cetakHasil(const BangunDatar* bd) {
        cetakGaris();
        cetakJudul("HASIL PERHITUNGAN");
        cetakGaris();
        cout << fixed << setprecision(4);
        cout << "  Bangun Datar : " << bd->nama     << endl;
        cout << "  Luas         : " << bd->luas     << " satuan persegi" << endl;
        cout << "  Keliling     : " << bd->keliling << " satuan" << endl;
        cetakGaris();
    }

    // CALLBACK FUNCTION — fungsi pemrosesan menerima fungsi lain
    // sebagai parameter (tipe std::function)
    
    void prosesHasil(BangunDatar& bd, function<void(const BangunDatar*)> callbackCetak) {
        // Setelah dihitung, delegasikan tampilan ke callback
        callbackCetak(&bd);
    }

    // FUNCTION OVERLOADING — fungsi 'tampilInfo' dengan parameter berbeda
    // Overload 1: hanya nama bangun
    void tampilInfo(const string& nama) {
        cout << "\n  >> Menghitung " << nama << "..." << endl;
    }

    // Overload 2: nama + jumlah dimensi yang diinput
    void tampilInfo(const string& nama, int jumlahDimensi) {
        cout << "\n  >> Menghitung " << nama
             << " (input " << jumlahDimensi << " dimensi)..." << endl;
    }

    // Overload 3: nama + luas + keliling (untuk ringkasan singkat)
    void tampilInfo(const string& nama, double luas, double keliling) {
        cout << "  Ringkasan: " << nama
             << " | L=" << luas << " | K=" << keliling << endl;
    }

    // DEFAULT ARGUMENT — fungsi dengan nilai default satuan
    void tampilSatuan(const string& jenisLuas = "cm2",
                      const string& jenisKeliling = "cm") {
        cout << "  Satuan yang digunakan: Luas = " << jenisLuas
             << ", Keliling = " << jenisKeliling << endl;
    }

} // end namespace 

// FUNCTION TEMPLATE — fungsi validasi input
template <typename T>
bool isPositif(T nilai) {
    return nilai > 0;
}

// FUNGSI MENU
void tampilMenu() {
    GeometriCalc::cetakGaris();
    cout << "   KALKULATOR LUAS & KELILING BANGUN DATAR" << endl;
    GeometriCalc::cetakGaris();
    cout << "  1. Persegi" << endl;
    cout << "  2. Persegi Panjang" << endl;
    cout << "  3. Segitiga" << endl;
    cout << "  4. Lingkaran" << endl;
    cout << "  5. Trapesium" << endl;
    cout << "  0. Keluar" << endl;
    GeometriCalc::cetakGaris();
    cout << "  Pilih menu: ";
}

// MAIN
int main() {
    int pilihan;
    char ulang;

    do {
        tampilMenu();
        cin >> pilihan;

        // Alokasi struct via pointer (demonstrasi pointer + new)
        BangunDatar* hasil = new BangunDatar();

        // Callback: menunjuk ke fungsi cetakHasil di namespace
        function<void(const BangunDatar*)> callback = GeometriCalc::cetakHasil;

        switch (pilihan) {
            case 1: { // Persegi
                double sisi;
                GeometriCalc::tampilInfo("Persegi");          // Overload 1
                GeometriCalc::tampilSatuan();                  // Default argument
                cout << "  Masukkan sisi: ";
                cin >> sisi;
                if (!isPositif(sisi)) { cout << "  Input harus positif!\n"; break; }
                GeometriCalc::hitungPersegi(sisi, *hasil);
                GeometriCalc::prosesHasil(*hasil, callback);  // Callback
                GeometriCalc::tampilInfo(hasil->nama, hasil->luas, hasil->keliling); // Overload 3
                break;
            }
            case 2: { // Persegi Panjang
                double p, l;
                GeometriCalc::tampilInfo("Persegi Panjang", 2); // Overload 2
                GeometriCalc::tampilSatuan("m2", "m");           // Default override
                cout << "  Masukkan panjang: "; cin >> p;
                cout << "  Masukkan lebar  : "; cin >> l;
                if (!isPositif(p) || !isPositif(l)) { cout << "  Input harus positif!\n"; break; }
                GeometriCalc::hitungPersegiPanjang(p, l, *hasil);
                GeometriCalc::prosesHasil(*hasil, callback);
                GeometriCalc::tampilInfo(hasil->nama, hasil->luas, hasil->keliling);
                break;
            }
            case 3: { // Segitiga
                double alas, tinggi, sa, sb, sc;
                GeometriCalc::tampilInfo("Segitiga", 5); // Overload 2
                GeometriCalc::tampilSatuan();
                cout << "  Masukkan alas         : "; cin >> alas;
                cout << "  Masukkan tinggi       : "; cin >> tinggi;
                cout << "  Masukkan sisi a (alas): "; cin >> sa;
                cout << "  Masukkan sisi b       : "; cin >> sb;
                cout << "  Masukkan sisi c       : "; cin >> sc;
                if (!isPositif(alas)||!isPositif(tinggi)) { cout << "  Input harus positif!\n"; break; }
                GeometriCalc::hitungSegitiga(alas, tinggi, sa, sb, sc, *hasil);
                GeometriCalc::prosesHasil(*hasil, callback);
                GeometriCalc::tampilInfo(hasil->nama, hasil->luas, hasil->keliling);
                break;
            }
            case 4: { // Lingkaran
                double r;
                GeometriCalc::tampilInfo("Lingkaran"); // Overload 1
                GeometriCalc::tampilSatuan();
                cout << "  Masukkan jari-jari: "; cin >> r;
                if (!isPositif(r)) { cout << "  Input harus positif!\n"; break; }
                GeometriCalc::hitungLingkaran(r, *hasil);
                GeometriCalc::prosesHasil(*hasil, callback);
                GeometriCalc::tampilInfo(hasil->nama, hasil->luas, hasil->keliling);
                break;
            }
            case 5: { // Trapesium
                double sa, sb, t, ka, kb;
                GeometriCalc::tampilInfo("Trapesium", 5); // Overload 2
                GeometriCalc::tampilSatuan();
                cout << "  Masukkan sisi atas  : "; cin >> sa;
                cout << "  Masukkan sisi bawah : "; cin >> sb;
                cout << "  Masukkan tinggi     : "; cin >> t;
                cout << "  Masukkan kaki kiri  : "; cin >> ka;
                cout << "  Masukkan kaki kanan : "; cin >> kb;
                if (!isPositif(sa)||!isPositif(sb)||!isPositif(t)) { cout << "  Input harus positif!\n"; break; }
                GeometriCalc::hitungTrapesium(sa, sb, t, ka, kb, *hasil);
                GeometriCalc::prosesHasil(*hasil, callback);
                GeometriCalc::tampilInfo(hasil->nama, hasil->luas, hasil->keliling);
                break;
            }
            case 0:
                cout << "\n  Terima kasih telah menggunakan program ini!\n";
                delete hasil;
                return 0;
            default:
                cout << "\n  Pilihan tidak valid!\n";
        }

        // Dealokasi memori pointer
        delete hasil;

        cout << "\n  Hitung lagi? (y/n): ";
        cin >> ulang;
        cout << endl;

    } while (ulang == 'y' || ulang == 'Y');

    cout << "\n  Terima kasih!\n";
    return 0;
}