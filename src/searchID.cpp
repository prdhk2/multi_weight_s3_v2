#include "config.h"

void searchID(int new_id) {
    Serial.println("\nMencari data...");

    Serial.print("ID User yang dikirim: ");
    Serial.println(new_id);

    username = getusername(new_id); // Ambil nama berdasarkan ID

    if (!username.isEmpty()) {  // Cek apakah username ditemukan
        id_user = new_id;  // Simpan ID user yang valid
        Serial.print("ID User tersimpan: ");
        Serial.println(id_user);

        float berat = readWeight();  // Ambil berat sebelum ditampilkan
        displayWeight();  // Kirim berat ke tampilan
    } else {
        Serial.println("User tidak ditemukan!");
        notFoundError();
        readUserID();
    }
}
