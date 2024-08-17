#include <iostream>
#include <vector>
#include <conio.h>   // Untuk getch()
#include <ctime>     // Untuk fungsi waktu
#include <cstdlib>   // Untuk fungsi rand()
#include <csignal>   // Untuk menangani Ctrl+C

using namespace std;

bool stop = false;  // Flag untuk menghentikan program dengan Ctrl+C

// Fungsi untuk menangani sinyal Ctrl+C
void signalHandler(int signum) {
    cout << "\nProgram dihentikan oleh pengguna." << endl;
    stop = true;
}

int main() {
    // Registrasi signal handler untuk Ctrl+C
    signal(SIGINT, signalHandler);

    while (!stop) {
        int correctAnswers = 0;
        int wrongAnswers = 0;

        vector<int> results;  // Menyimpan hasil penjumlahan

        // Masukkan batas waktu dari pengguna
        int timeLimit;
        cout << "Masukkan batas waktu tes (dalam detik): ";
        cin >> timeLimit;

        // Waktu mulai
        time_t startTime = time(0);

        // Seed untuk angka acak
        srand(time(0));

        while (!stop) {
            // Cek waktu apakah sudah melebihi batas waktu
            time_t currentTime = time(0);
            if (difftime(currentTime, startTime) >= timeLimit) {
                cout << "\nWaktu tes telah habis!" << endl;
                break;
            }

            // Generate dua angka acak dari 0 sampai 9
            int num1 = rand() % 10;
            int num2 = rand() % 10;

            int sum = num1 + num2;
            cout << "Jumlah dari " << num1 << " + " << num2 << " = ";

            char input = _getch();  // Tangkap input tanpa enter
            cout << input << endl;

            // Konversi char ke integer
            int result = input - '0';

            // Validasi input
            if (result == (sum % 10)) {
                results.push_back(result);
                correctAnswers++;  // Tambahkan jawaban benar
            }
            else {
                cout << "Jawaban salah. Hasil yang benar adalah " << (sum % 10) << endl;
                results.push_back(sum % 10);  // Masukkan hasil yang benar
                wrongAnswers++;  // Tambahkan jawaban salah
            }

            // Cek waktu setelah setiap input
            currentTime = time(0);
            if (difftime(currentTime, startTime) >= timeLimit) {
                cout << "\nWaktu tes telah habis!" << endl;
                break;
            }
        }

        // Tampilkan hasil
        cout << "\nHasil Tes Kreplin Anda:" << endl;
        cout << "Benar: " << correctAnswers << endl;
        cout << "Salah: " << wrongAnswers << endl;

        // Tanya pengguna apakah ingin melanjutkan
        char choice;
        cout << "\nIngin lanjut? (Y/N): ";
        cin >> choice;

        if (choice == 'N' || choice == 'n') {
            cout << "Terima kasih telah mengikuti Tes Kreplin!" << endl;
            break;
        }

        // Reset waktu mulai untuk tes berikutnya
        startTime = time(0);
    }

    return 0;
}
