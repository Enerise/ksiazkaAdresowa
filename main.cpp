#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Adresat {
    int id;
    string imie, nazwisko, nrTelefonu, email, adres;
};

string wczytajLinie() {
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

char pobierzZnak() {
    string wchodzacyString = "";
    char wchodzacyZnak = (0);

    while(true) {
        cin.sync();
        getline(cin, wchodzacyString);

        if(wchodzacyString.length() == 1) {
            wchodzacyZnak = wchodzacyString[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Sprobuj ponowanie." << endl;
    }
    return wchodzacyZnak;
}

int pobierzLiczbe() {
    string wchodzacyString = "";
    int wchodzacaLiczba = 0;

    while(true) {
        cin.sync();
        getline(cin, wchodzacyString);
        stringstream myStream(wchodzacyString);
        if(myStream >> wchodzacaLiczba) break;
        cout << "To nie jest liczba. Sprobuj ponownie" << endl;
    }
    return wchodzacaLiczba;
}

void zapisDoPliku(vector <Adresat> adresaci, int ilosc) {
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app);
    if(!plik.good()) {
        cout << "Plik nie istnieje";
        exit(0);
    }

    plik << adresaci[ilosc].id << '|';
    plik << adresaci[ilosc].imie << '|';
    plik << adresaci[ilosc].nazwisko << '|';
    plik << adresaci[ilosc].nrTelefonu << '|';
    plik << adresaci[ilosc].email << '|';
    plik << adresaci[ilosc].adres << '|' << endl;

    plik.close();
}

void rozdzielDane(string linia, vector <Adresat> &adresaci, int ilosc) {
    Adresat pojedynczyAdresat;
    string idSTR, imie, nazwisko, nrTelefonu, email, adres;
    int index = 0, id;

    while(linia[index] != '|') {
        idSTR += linia[index];
        index++;
    }
    index++;
    while(linia[index] != '|') {
        imie += linia[index];
        index++;
    }
    index++;
    while(linia[index] != '|') {
        nazwisko += linia[index];
        index++;
    }
    index++;
    while(linia[index] != '|') {
        nrTelefonu += linia[index];
        index++;
    }
    index++;
    while(linia[index] != '|') {
        email += linia[index];
        index++;
    }
    index++;
    while(linia[index] != '|') {
        adres += linia[index];
        index++;
    }

    id = stoi(idSTR);

    pojedynczyAdresat.id = id;
    pojedynczyAdresat.imie = imie;
    pojedynczyAdresat.nazwisko = nazwisko;
    pojedynczyAdresat.nrTelefonu = nrTelefonu;
    pojedynczyAdresat.email = email;
    pojedynczyAdresat.adres = adres;

    adresaci.push_back(pojedynczyAdresat);
}

int odczytZPliku(vector <Adresat> &adresaci) {
    fstream plik;
    string linia = "";
    int id = 0;

    plik.open("ksiazka_adresowa.txt", ios::in);

    if(!plik.good()) {
        return id;
    }

    do {
        getline(plik, linia);
        if(linia == "") {
            break;
        }
        rozdzielDane(linia, adresaci, id);
        id++;
    } while(linia != "");


    plik.close();
    return id;
}

int dodajAdresata(vector <Adresat> &adresaci, int iloscAdresatow) {
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::app);
    plik.close();

    int rozmiarWektora = adresaci.size();
    int id = 1;
    Adresat pojedynczyAdresat;
    if(rozmiarWektora != 0) {
        id = (adresaci[rozmiarWektora-1].id + 1);
    }

    pojedynczyAdresat.id = id;

    cout << "Podaj imie: ";
    pojedynczyAdresat.imie = wczytajLinie();

    cout << "Podaj nazwisko: ";
    pojedynczyAdresat.nazwisko = wczytajLinie();

    cout << "Podaj numer telefonu: ";
    pojedynczyAdresat.nrTelefonu = wczytajLinie();

    cout << "Podaj email: ";
    pojedynczyAdresat.email = wczytajLinie();

    cout << "Podaj adres: ";
    pojedynczyAdresat.adres = wczytajLinie();

    adresaci.push_back(pojedynczyAdresat);

    zapisDoPliku(adresaci, iloscAdresatow);
    cout << endl;
    cout << "Dodano pomyslnie adresata";
    Sleep(1500);

    return id;
}

void wyszukajAdresataPoImieniu(vector <Adresat> adresaci, int iloscAdresatow) {
    string imie = "";
    int brakImienia = 0;
    cout << "Podaj imie: ";
    imie = wczytajLinie();

    for (int i = 0; i < iloscAdresatow; i++) {
        if(imie == adresaci[i].imie) {
            cout << "ID:              " << adresaci[i].id << endl;
            cout << "Imie:            " << adresaci[i].imie << endl;
            cout << "Nazwisko:        " << adresaci[i].nazwisko << endl;
            cout << "Numer telefonu:  " << adresaci[i].nrTelefonu << endl;
            cout << "Email:           " << adresaci[i].email << endl;
            cout << "Adres:           " << adresaci[i].adres << endl << endl;
        } else {
            brakImienia++;
        }
    }
    if(brakImienia == iloscAdresatow) {
        cout << "Brak podanego imienia w bazie. " << endl;
        cout << "Nacisnij dowolny klawisz aby przejsc do menu glownego. ";
        system("pause");
    } else {
        cout << "Nacisnij dowolny klawisz aby przejsc do menu glownego" << endl;
        system("pause");
    }
}

void wyszukajAdresataPoNazwisku(vector <Adresat> adresaci, int iloscAdresatow) {
    string nazwisko = "";
    int brakNazwiska = 0;
    cout << "Podaj nazwisko: ";
    nazwisko = wczytajLinie();

    for (int i = 0; i < iloscAdresatow; i++) {
        if(nazwisko == adresaci[i].nazwisko) {
            cout << "ID:              " << adresaci[i].id << endl;
            cout << "Imie:            " << adresaci[i].imie << endl;
            cout << "Nazwisko:        " << adresaci[i].nazwisko << endl;
            cout << "Numer telefonu:  " << adresaci[i].nrTelefonu << endl;
            cout << "Email:           " << adresaci[i].email << endl;
            cout << "Adres:           " << adresaci[i].adres << endl << endl;
        } else {
            brakNazwiska++;
        }
    }
    if(brakNazwiska == iloscAdresatow) {
        cout << "Brak podanego nazwiska w bazie. " << endl;
        cout << "Nacisnij dowolny klawisz aby przejsc do menu glownego. " << endl;
        system("pause");
    } else {
        cout << "Nacisnij dowolny klawisz aby przejsc do menu glownego" << endl;
        system("pause");
    }
}

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci, int iloscAdresatow) {
    if(iloscAdresatow == 0) {
        cout << "Brak zapisanych adresatow w bazie." << endl;
        Sleep(1500);
    } else {
        for (int i = 0; i < iloscAdresatow; i++) {
            cout << "ID:              " << adresaci[i].id << endl;
            cout << "Imie:            " << adresaci[i].imie << endl;
            cout << "Nazwisko:        " << adresaci[i].nazwisko << endl;
            cout << "Numer telefonu:  " << adresaci[i].nrTelefonu << endl;
            cout << "Email:           " << adresaci[i].email << endl;
            cout << "Adres:           " << adresaci[i].adres << endl;
            cout << endl;
        }
        cout << "Nacisnij dowolny klawisz aby przejsc do menu glownego" << endl;
        system("pause");
    }
}

void zapisanieNowychDanychDoPliku(vector <Adresat> &adresaci, int iloscAdresatow) {
    remove("ksiazka_adresowa.txt");
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app);
    if(plik.good() == false) {
        cout << "Plik nie istnieje";
        exit(0);
    }

    for(int i = 0; i < iloscAdresatow; i++) {
        plik << adresaci[i].id << '|';
        plik << adresaci[i].imie << '|';
        plik << adresaci[i].nazwisko << '|';
        plik << adresaci[i].nrTelefonu << '|';
        plik << adresaci[i].email << '|';
        plik << adresaci[i].adres << '|' << endl;
    }
    plik.close();
}

int usunAdresata(vector <Adresat> &adresaci) {
    int wyborID = 0;
    char znakPotwierdzenia;
    cout << "Podaj numer ID adresata, ktorego chcesz usunac: ";
    wyborID = pobierzLiczbe();
    int rozmiarWektora = adresaci.size();

    if(rozmiarWektora == 0) {
        cout << "Brak adresatow w bazie";
        Sleep(1500);
        return rozmiarWektora;
    } else {
        for(int i = 0; i < rozmiarWektora; i++) {
            if((wyborID != adresaci[i].id) && ((adresaci[i].id >= wyborID) || (wyborID > rozmiarWektora))) {
                cout << "Nie ma adresata o podanym numerze ID" << endl;
                Sleep(1500);
                return rozmiarWektora;
            } else if(wyborID == adresaci[i].id)
                break;
        }

        cout << "Potwierdz naciskajac klawisz 't': ";
        znakPotwierdzenia = pobierzZnak();

        if(znakPotwierdzenia == 't') {
            auto it = adresaci.begin();
            for(int i = 0; i < rozmiarWektora; i++) {
                if (adresaci[i].id == wyborID) {
                    adresaci.erase(it);
                    rozmiarWektora = adresaci.size();
                    break;
                }
                it++;
            }
        } else
            return rozmiarWektora;

        zapisanieNowychDanychDoPliku(adresaci, rozmiarWektora);
        cout << "Usunieto pomyslnie adresata";
        Sleep(1500);
        return rozmiarWektora;
    }
}

void zmienImie(vector <Adresat> &adresaci, int wyborID, int iloscAdresatow) {
    for(int i = 0; i < iloscAdresatow; i++) {
        if (adresaci[i].id == wyborID) {
            cout << "Stare imie: " << adresaci[wyborID-1].imie << endl;
            cout << "Nowe imie: ";
            cin >> adresaci[i].imie;
            zapisanieNowychDanychDoPliku(adresaci, iloscAdresatow);
            cout << "Pomyslnie zmieniono imie";
            Sleep(1500);
        }
    }
}

void zmienNazwisko(vector <Adresat> &adresaci, int wyborID, int iloscAdresatow) {
    for(int i = 0; i < iloscAdresatow; i++) {
        if (adresaci[i].id == wyborID) {
            cout << "Stare nazwisko: " << adresaci[wyborID-1].nazwisko << endl;
            cout << "Nowe nazwisko: ";
            cin >> adresaci[i].nazwisko;
            zapisanieNowychDanychDoPliku(adresaci, iloscAdresatow);
            cout << "Pomyslnie zmieniono nazwisko";
            Sleep(1500);
        }
    }
}

void zmienNumerTelefonu(vector <Adresat> &adresaci, int wyborID, int iloscAdresatow) {
    for(int i = 0; i < iloscAdresatow; i++) {
        if (adresaci[i].id == wyborID) {
            cout << "Stary numer telefonu: " << adresaci[wyborID-1].nrTelefonu << endl;
            cout << "Nowy numer telefonu: ";
            cin >> adresaci[i].nrTelefonu;
            zapisanieNowychDanychDoPliku(adresaci, iloscAdresatow);
            cout << "Pomyslnie zmieniono numer telefonu";
            Sleep(1500);
        }
    }
}

void zmienEmail(vector <Adresat> &adresaci, int wyborID, int iloscAdresatow) {
    for(int i = 0; i < iloscAdresatow; i++) {
        if (adresaci[i].id == wyborID) {
            cout << "Stary email: " << adresaci[wyborID-1].email << endl;
            cout << "Nowy email: ";
            cin >> adresaci[i].email;
            zapisanieNowychDanychDoPliku(adresaci, iloscAdresatow);
            cout << "Pomyslnie zmieniono email";
            Sleep(1500);
        }
    }
}

void zmienAdres(vector <Adresat> &adresaci, int wyborID, int iloscAdresatow) {
    for(int i = 0; i < iloscAdresatow; i++) {
        if (adresaci[i].id == wyborID) {
            cout << "Stary adres: " << adresaci[wyborID-1].adres << endl;
            cout << "Nowy adres: ";
            cin >> adresaci[i].adres;
            zapisanieNowychDanychDoPliku(adresaci, iloscAdresatow);
            cout << "Pomyslnie zmieniono adres";
            Sleep(1500);
        }
    }
}

void edytujAdresata(vector <Adresat> &adresaci) {

    int wyborID = 0, wyborEdycji = 0;
    int rozmiarWektora = adresaci.size();
    cout << "Podaj numer ID adresata, ktorego dane chcesz edytowac" << endl;
    wyborID = pobierzLiczbe();

    if(rozmiarWektora == 0) {
        cout << "Brak adresatow w bazie";
        Sleep(1500);
        return;
    } else {
        for(int i = 0; i < rozmiarWektora; i++) {
            if((wyborID != adresaci[i].id) && ((adresaci[i].id >= wyborID) || (wyborID > rozmiarWektora))) {
                cout << "Nie ma adresata o podanym numerze ID" << endl;
                Sleep(1500);
                return;
            } else if(wyborID == adresaci[i].id)
                break;
        }
        system("cls");
        cout << "Wybierz numer odpowiadajacy danej, ktora chcesz edytowac" << endl;
        cout << "1 - imie" << endl;
        cout << "2 - nazwisko" << endl;
        cout << "3 - numer telefonu" << endl;
        cout << "4 - email" << endl;
        cout << "5 - adres" << endl;
        cout << "9 - powrot do menu" << endl;

        cout << "Twoj wybor: ";
        wyborEdycji = pobierzLiczbe();

        switch(wyborEdycji) {
        case 1:
            zmienImie(adresaci, wyborID, rozmiarWektora);
            break;
        case 2:
            zmienNazwisko(adresaci, wyborID, rozmiarWektora);
            break;
        case 3:
            zmienNumerTelefonu(adresaci, wyborID, rozmiarWektora);
            break;
        case 4:
            zmienEmail(adresaci, wyborID, rozmiarWektora);
            break;
        case 5:
            zmienAdres(adresaci, wyborID, rozmiarWektora);
            break;
        case 9:
            return;
            break;
        }
    }
}

int main() {
    vector <Adresat> adresaci;

    int wybor = 0;
    int iloscAdresatow = 0;

    iloscAdresatow = odczytZPliku(adresaci);

    while(true) {
        system("cls");
        cout << "Ksiazka adresowa" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj adresata po imieniu" << endl;
        cout << "3. Wyszukaj adresata po nazwisku" << endl;
        cout << "4. Wyswietl liste wszystkich zapisanych osob" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edycja danych adresata" << endl;
        cout << "9. Zakoncz program" << endl << endl;
        cout << "Twoj wybor: ";
        wybor = pobierzLiczbe();
        cout << endl;

        switch(wybor) {
        case 1:
            iloscAdresatow = dodajAdresata(adresaci, iloscAdresatow);
            break;
        case 2:
            wyszukajAdresataPoImieniu(adresaci, iloscAdresatow);
            break;
        case 3:
            wyszukajAdresataPoNazwisku(adresaci, iloscAdresatow);
            break;
        case 4:
            wyswietlWszystkichAdresatow(adresaci, iloscAdresatow);
            break;
        case 5:
            system("cls");
            iloscAdresatow = usunAdresata(adresaci);
            break;
        case 6:
            system("cls");
            edytujAdresata(adresaci);
            break;
        case 9:
            exit(0);
            break;
        default:
            cout << "Nie ma takiej opcji. Prosze wybierz inny numer" << endl;
            Sleep(1500);
            break;
        }
    }
    return 0;
}
