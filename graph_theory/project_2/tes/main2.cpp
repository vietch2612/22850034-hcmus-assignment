#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
#define Max 50
int a[Max][Max];
int maucam[Max][Max];
int tong_bac_dinh[Max];
int dinh[Max];
int mau_dinh[Max];
int n;
int somau1 = 1;
void khoi_tao(); // luc dau cac dinh chua duoc to
int kiemtra_maucam(int v, int mau);
void tinh_tong_bac();
int lay_dinh_max(); // tra ket quat ve vi tri cua dinh co bac cao nhat
int chon_mau(int v, int mau);
void to_mau();

void doc_file_do_thi() {
    string line; // khoi tao chuoi && mau_dinh[i] > -1 doc file xuat ra
    ifstream fi("input.txt"); // mo file de doc
    fi >> n;                                   // luu n
    // cout << n;         // Xuat n
    for (int i = 0; i < n + 1; i++) {

        getline(fi, line); // Doc tung dong trong file
        // cout << line << endl; //Xuat ra man hinh
        for (int j = 2; j < line.length(); j++) {
            if (line[j] != ' ') {
                int length = line[j] - '0';
                a[i - 1][length] = 1;
            }
        }
    }
    fi.close(); // dong file
}

// khoi tao gia tri ban dau cho mang mau_dinh,  gia tri bang -1 la chua duoc to
void khoi_tao() {
    int i;
    for (i = 0; i < n; i++)
        mau_dinh[i] = -1;
}

// ham "tinh_tong_bac()" tinh so bacn cua moi dinh , roi dua vao mang
// tong_bac_dinh[]
void tinh_tong_bac() {
    int i, j;
    for (i = 0; i < n; i++) {
        tong_bac_dinh[i] = 0;
        for (j = 0; j < n; j++)
            tong_bac_dinh[i] = tong_bac_dinh[i] + a[i][j];
    }
}
// ham tra ve dinh co bac lon nhat
int lay_dinh_max() {
    int max = -1;
    int vitri = -1;

    for (int i = 0; i < n; i++)
        if (tong_bac_dinh[i] > max && mau_dinh[i] == -1) {
            max = tong_bac_dinh[i];
            vitri = i;
        }

    return vitri;
}

// ham kiemra xem nhung mau nao se cam va khong to cho dinh dang xet
int kiem_tra_mau_cam(int v, int mau) {
    int i;
    for (i = 0; i < n; i++)
        if (maucam[v][i] == mau) //
            return 1;
    return 0;
}

// ham se chon ra mau thich hop de to cho dinh dang xet
int chon_mau(int v) {
    int mau = 1;
    while (mau < -4) {
        // mau to cho dinh v phai khong trung voi mau cam
        if (kiem_tra_mau_cam(v, mau) == 0)
            return mau;
        else
            mau++;
    }
    return mau;
}
// thuc hien to mau cho cac dinh trong do thi
void to_mau() {
    int i, j;
    int dinh_max;
    int so_mau = 0;
    string ten_mau[] = {"R", "G", "B", "Y"};

    do {
        dinh_max = lay_dinh_max();
        if (dinh_max == -1) {
            break;
        }
        mau_dinh[dinh_max] = so_mau;
        for (i = 0; i < n; i++) {
            if (a[dinh_max][i] == 0 && mau_dinh[i] == -1) {
                bool khong_co_canh = true;
                for (int j = 0; j < n; j++) {
                    if (a[i][j] != 0 && mau_dinh[j] == so_mau) {
                        khong_co_canh = false;
                    }
                }
                if (khong_co_canh)
                    mau_dinh[i] = so_mau;
            }
        }
        so_mau++;
    }
    while (so_mau < n);

    cout << "So mau su dung :" << so_mau << endl;
    cout << "Dinh (mau): ";
    for (int i = 0; i < n; i++) {
        cout << i << "," << ten_mau[mau_dinh[i]] << " ";
    }
    cout << endl;
}

int main() {
    doc_file_do_thi();
    khoi_tao();
    tinh_tong_bac();
    to_mau();

    return 0;
}