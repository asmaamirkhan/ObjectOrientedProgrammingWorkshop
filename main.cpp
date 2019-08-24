#include <iostream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>

using namespace std;

class Matris{
private:
    int satir, sutun;
    int ** elemanlar;
public:
    Matris();
    Matris(int);
    Matris(int, int);
    Matris(int, int, int);
    Matris(Matris &);
    void rastgeleDoldur(int);
    Matris operator + (Matris&);
    Matris& operator = (const Matris&);
    bool operator == (Matris &);
    int operator ()(int, int);
    friend ostream& operator<<(ostream&, const Matris&);
    Matris transpoze();
    int ** getElemanlar();
    int getSatir();
    int getSutun();
    void print();
};

int ** Matris::getElemanlar(){
    return elemanlar;
}

int Matris::getSatir(){
    return satir;
}
int Matris::getSutun(){
    return sutun;
}

class KareMatris:public Matris{
public:
    KareMatris(int boyut):Matris(boyut){};
    KareMatris(int boyut, int sayi):Matris(boyut, boyut, sayi){};
    bool simetrik_mi();
    bool ustUcgen_mi();
};

bool KareMatris::ustUcgen_mi(){
    int i,j;
    for(i=1; i<getSatir(); i++){
        for(j=1; j<i; j++){
            if(getElemanlar()[i][j]!=0)
                return false;
        }
    }
    return true;
}

KareMatris eye(int boyut){
    KareMatris sonuc(boyut, 0);
    int i;
    for(i=0; i<boyut; i++)
        sonuc.getElemanlar()[i][i]=1;
    return sonuc;
}

Matris::Matris(){
    satir=0;
    sutun=0;
    elemanlar=NULL;
}

Matris::Matris(int m){
    satir=m;
    sutun=m;
    elemanlar = new int* [m];
    int i;
    for(i=0; i<m; i++){
        elemanlar[i] = new int [m];
    }
}

Matris::Matris(int satir, int sutun){
    this->satir = satir;
    this->sutun = sutun;
    elemanlar = new int*[satir];
    int i;
    for(i=0; i<satir; i++){
        elemanlar[i] = new int[sutun];
    }
}

Matris::Matris(int satir, int sutun, int sayi){
    this->satir = satir;
    this->sutun = sutun;
    elemanlar = new int*[satir];
    int i,j;
    for(i=0; i<satir; i++){
        elemanlar[i] = new int[sutun];
    }
    for(i=0; i<satir; i++)
        for(j=0; j<sutun; j++)
            elemanlar[i][j]=sayi;
}

Matris::Matris(Matris &mat){
    int i,j;
    this->satir = mat.satir;
    this->sutun = mat.sutun;
    this->elemanlar = new int*[mat.satir];
    for(i=0; i<satir; i++){
        elemanlar[i]=new int[sutun];
    }
    for(i=0; i<satir; i++){
        for(j=0; j<sutun; j++){
            this->elemanlar[i][j] = mat.elemanlar[i][j];
        }
    }

}

void Matris::rastgeleDoldur(int max_val){
    int i,j;
    srand(time(NULL));
    for(i=0; i<satir; i++){
        for(j=0; j<sutun; j++){
            elemanlar[i][j] = rand() % (max_val+1);
        }
    }
}

void Matris::print(){
    int i,j;
    for(i=0; i<satir; i++){
        for(j=0; j<sutun; j++){
            cout<<elemanlar[i][j]<<"  ";
        }
        cout<<endl;
    }
}

Matris Matris::operator+(Matris &sag){
    if(satir == sag.satir && sutun == sag.sutun){
    Matris sonuc(sag.satir, sag.sutun);
    int i,j,k=0;
    for(i=0; i<sag.satir; i++){
        for(j=0; j<sag.sutun; j++){
            sonuc.elemanlar[i][j]=this->elemanlar[i][j] + sag.elemanlar[i][j];
            k++;
        }
    }
    return sonuc;
    }else{
        throw "Matris boyutlari uyusmuyor!";
    }

}

Matris& Matris::operator=(const Matris &sag){
    cout<<"\natama\n";
    int i,j;
    this->satir = sag.satir;
    this->sutun = sag.sutun;
    this->elemanlar = new int*[sag.satir];
    for(i=0; i<satir; i++){
        elemanlar[i]=new int[sutun];
    }
    for(i=0; i<satir; i++){
        for(j=0; j<sutun; j++){
            this->elemanlar[i][j] = sag.elemanlar[i][j];
        }
    }
    return *this;
}

bool Matris::operator==(Matris & sag){
    if(satir==sag.satir && sutun == sag.sutun){
    int i,j;
    for(i=0; i<satir; i++){
        for(j=0; j<sutun; j++){
            if(this->elemanlar[i][j]!=sag.elemanlar[i][j])
                return false;
        }
    }
    return true;
    }else{
        throw "Matris boyutlari uyusmuyor";
    }
}

int Matris::operator()(int satir, int sutun){
    if(satir>=0 && satir<this->satir && sutun>0 && sutun<this->sutun)
        return this->elemanlar[satir][sutun];
    else
        throw "Matris boyutunu astiniz";
}

ostream& operator<<(ostream& ost, const Matris& sag){
    int i,j;
    for(i=0; i<sag.satir; i++){
        for(j=0; j<sag.sutun; j++){
            ost<<sag.elemanlar[i][j]<<"  ";
        }
        ost<<endl;
    }
    return ost;
}

Matris Matris::transpoze(){
    Matris sonuc(sutun, satir);
    int i, j;
    for(i=0; i<satir; i++){
        for(j=0; j<sutun; j++){
            sonuc.elemanlar[j][i] = elemanlar[i][j];
        }
    }
    return sonuc;
}

bool KareMatris::simetrik_mi(){
    int i,j;
    for(i=0; i<getSatir(); i++){
        for(j=i; j<getSutun(); j++){
            if(getElemanlar()[i][j]!=getElemanlar()[j][i])
                return false;
        }
    }
    return true;
}

int main()
{
    KareMatris k1(5);
    k1.rastgeleDoldur(30);
    cout<<k1;
    cout<<endl;
    cout<<k1.transpoze();
    cout <<endl<< typeid(k1).name() << endl;
    /*cout<<endl<<&(m1.satir);
    cout<<endl<<&(m2.satir);
    cout<<endl<<(m1.elemanlar);
    cout<<endl<<(m2.elemanlar);*/

}
