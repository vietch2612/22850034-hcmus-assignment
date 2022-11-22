#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#define Max 50
int a[Max][Max];
int maucam[Max][Max];
int tong_bac_dinh[Max];
int dinh[Max];
int mau_dinh[Max];
int dinh_sap_xep[Max];
int n;
int somau1 = 1;
void khoitao(); //luc dau cac dinh chua duoc to
int kiemtra_maucam(int v, int mau);
void tongbac();
int dinh_bac_max();// tra ket quat ve vi tri cua dinh co bac cao nhat
int chonmau(int v, int mau);
void sap_xep_dinh();
void tomau();

void Docfiledothi()
{

	string line; //khoi tao chuoi doc file xuat ra
	ifstream fi("input.txt");   // mo file de doc
	fi >> n;         //luu n     
	//cout << n;         // Xuat n
	for (int i = 0; i < n + 1; i++)
	{

		getline(fi, line);    //Doc tung dong trong file
		//cout << line << endl; //Xuat ra man hinh
		for (int j = 2; j < line.length(); j++)
		{
			if (line[j] != ' ')
			{
				int length = line[j] - '0';
				a[i - 1][length] = 1;
			}
		}

	}
	fi.close(); // dong file
}

// khoi tao gia tri ban dau cho mang mau_dinh,  gia tri bang -1 la chua duoc to
void khoitao()
{
	int i;
	for (i = 0; i < n; i++)
		mau_dinh[i] = -1;
}

// ham "tongbac()" tinh so bacn cua moi dinh , roi dua vao mang tong_bac_dinh[]
void tongbac()
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		tong_bac_dinh[i] = 0;
		for (j = 0; j < n; j++)
			tong_bac_dinh[i] = tong_bac_dinh[i] + a[i][j];
	}
}

int lay_so_mau() {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (mau_dinh[i] > max)
            max = mau_dinh[i];
    }
    return max;
}

void sap_xep_dinh() { 
    for (int i = 0; i < n; i++) {
        dinh_sap_xep[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tong_bac_dinh[dinh_sap_xep[i]] >= tong_bac_dinh[dinh_sap_xep[j]]) {
                if (tong_bac_dinh[dinh_sap_xep[i]] == tong_bac_dinh[dinh_sap_xep[j]] && i > j) {
                    continue;
                }
                int tmp = dinh_sap_xep[i];
                dinh_sap_xep[i] = dinh_sap_xep[j];
                dinh_sap_xep[j] = tmp;
            }
        }
    }
}
// ham tra ve dinh co bac lon nhat
int dinh_bac_max()
{

	int max, vitri;
	int i;
	max = tong_bac_dinh[1];
	vitri = 1;
	for (i = 0; i < n; i++)
		if (tong_bac_dinh[i] > max)
		{

			max = tong_bac_dinh[i];
			vitri = i;
		}

	return vitri;
}
// ham kiemra xem nhung mau nao se cam va khong to cho dinh dang xet
int kiemtra_maucam(int v, int mau)
{
	int i;
	for (i = 0; i < n; i++)
		if (maucam[v][i] == mau) //
			return 1;
	return 0;
}
// ham se chon ra mau thich hop de to cho dinh dang xet
int chonmau(int v)
{
	int mau = 1; 
	do
	{
		if (kiemtra_maucam(v, mau) == 0) // mau to cho dinh v phai khong trung voi mau cam
		{
			return mau;
			break;
		}
		else
		{
			mau++;
		}
		
	} while (1);
	
}
// thuc hien to mau cho cac dinh trong do thi
void tomau()
{

	int i, j;
	int dem = 1;
	int dinh_max;
	int daxet[Max];
	for (i = 0; i < n; i++)
	{
		daxet[i] = -1; //xet xem dinh nao da duoc to mau hay chua to mau
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			maucam[i][j] = -1;// khoi tao mang hai chieu "maucam"va khoi tao gia tri bang dau=-1 tuc khong co dinh nao bi cam
	do {
		dinh_max = dinh_bac_max();
		mau_dinh[dinh_max] = chonmau(dinh_max);
		daxet[dinh_max] = 1;
		dem++;
		for (i = 0; i < n; i++)
		{
			if ((a[dinh_max][i] == 1) && (daxet[i] != 1))
			{
				maucam[i][dinh_max] = mau_dinh[dinh_max]; //mau da to cho dinh_max se bi cam to cho cac dinh ke voi no
				tong_bac_dinh[i]--; //ha bac cac dinh xuong
			}
			if (tong_bac_dinh[i] == 0 && daxet[i] != 1)// luc nay xet xem sau khi ha bac neu dinh nao =0 va chua xet thi to luon
			{
				mau_dinh[i] = chonmau(i);
				daxet[i] = 1;
				dem++;
				
			}
		}
		tong_bac_dinh[dinh_max] = 0; // bac dinh da to duoc gan bang 0;
		somau1++;
	} while (dem <= n);
	
	cout << "So mau su dung :" << lay_so_mau() << endl;
	cout << "Dinh (mau):";
	for (i = 0; i < n; i++)
	{
		if (mau_dinh[dinh_sap_xep[i]] == 1)
			cout << "(" << dinh_sap_xep[i] << "," << "R" << ")" <<" ";
		if (mau_dinh[dinh_sap_xep[i]] == 2)
			cout << "(" << dinh_sap_xep[i] << "," << "G" << ")" << " ";
		if (mau_dinh[dinh_sap_xep[i]] == 3)
			cout << "(" << dinh_sap_xep[i] << "," << "B" << ")"<< " ";
		if (mau_dinh[dinh_sap_xep[i]] == 4)
			cout << "(" << dinh_sap_xep[i] << "," << "Y" << ")" << " ";
	}
	cout << endl;
}

int main()
{
	khoitao();
	Docfiledothi();
	tongbac();
    sap_xep_dinh();
	tomau();

    return 0;
}