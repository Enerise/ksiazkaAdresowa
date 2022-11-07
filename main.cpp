#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>

using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

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
        cout << "Twoj wybor: ";
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
        cout << "Twoj wybor: ";
    }
    return wchodzacaLiczba;
}

int obliczenieId() {
    fstream plik;
    string linia = "";
    int id = 0;

    plik.open("Adresaci.txt", ios::in);

    if(!plik.good()) {
        return id;
    }

    do {
        getline(plik, linia);
        if(linia == "") {
            break;
        }
        id++;
    } while(linia != "");


    plik.close();
    return id;
}

void zapisDoPlikuUzytkownicy(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if(!plik.good()) {
        cout << "Plik nie istnieje";
        exit(0);
    }

    plik << uzytkownicy[iloscUzytkownikow].id << '|';
    plik << uzytkownicy[iloscUzytkownikow].nazwa << '|';
    plik << uzytkownicy[iloscUzytkownikow].haslo << '|' << endl;

    plik.close();
}

int rejestracja(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    cout << "Rejestracja nowego uzytkownika" << endl << endl;
    Uzytkownik pojedynczyUzytkownik;
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    int i = 0;
    while (i < iloscUzytkownikow) {
        if(uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        } else
            i++;
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    pojedynczyUzytkownik.id = iloscUzytkownikow + 1;
    pojedynczyUzytkownik.nazwa = nazwa;
    pojedynczyUzytkownik.haslo = haslo;
    uzytkownicy.push_back(pojedynczyUzytkownik);
    zapisDoPlikuUzytkownicy(uzytkownicy, iloscUzytkownikow);
    cout << "Konto zalozone" << endl;
    Sleep(1500);
    return iloscUzytkownikow + 1;
}

int logowanie(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    cout << "Logowanie" << endl << endl;
    string nazwa, haslo;
    cout << "Podaj nazwe: ";
    cin >> nazwa;

    int i = 0;
    while (i < iloscUzytkownikow) {
        if(uzytkownicy[i].nazwa == nazwa) {
            for (int proby = 0; proby < 3; proby++) {
                cout << "Podaj haslo. Pozostalo prob " << 3 - proby << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1500);
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne hasla. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

void zapisanieNowychDanychDoPlikuUzytkownicy(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    remove("Uzytkownicy.txt");
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if(!plik.good()) {
        cout << "Plik nie istnieje";
        exit(0);
    }

    for(int i = 0; i < iloscUzytkownikow; i++) {
        plik << uzytkownicy[i].id << '|';
        plik << uzytkownicy[i].nazwa << '|';
        plik << uzytkownicy[i].haslo << '|' << endl;
    }
    plik.close();
}

void zmianahasla(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow, int idZalogowanegoUzytkownika) {
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for (int i = 0; i < iloscUzytkownikow; i++) {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = haslo;
            zapisanieNowychDanychDoPlikuUzytkownicy(uzytkownicy, iloscUzytkownikow);
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }
}

void zapisDoPlikuAdresaci(vector <Adresat> adresaci, int ilosc, int idZalogowanegoUzytkownika) {
    fstream plik;
    plik.open("Adresaci.txt", ios::out | ios::app);
    if(!plik.good()) {
        cout << "Plik nie istnieje";
        exit(0);
    }

    plik << adresaci[ilosc].id << '|';
    plik << idZalogowanegoUzytkownika << '|';
    plik << adresaci[ilosc].imie << '|';
    plik << adresaci[ilosc].nazwisko << '|';
    plik << adresaci[ilosc].nrTelefonu << '|';
    plik << adresaci[ilosc].email << '|';
    plik << adresaci[ilosc].adres << '|' << endl;

    plik.close();
}

void rozdzielDaneZPlikuAdresaci(string linia, vector <Adresat> &adresaci, int ilosc) {
    Adresat pojedynczyAdresat;
    string idSTR, imie, nazwisko, nrTelefonu, email, adres, idZalogowanegoSTR;
    int index = 0, id;

    while(linia[index] != '|') {
        idSTR += linia[index];
        index++;
    }
    index++;
    while(linia[index] != '|') {
        idZalogowanegoSTR += linia[index];
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

void rozdzielDaneZPlikuUzytkownicy(string linia, vector <Uzytkownik> &uzytkownicy, int ilosc) {
    Uzytkownik pojedynczyUzytkownik;
    string idSTR, nazwa, haslo;
    int index = 0, id;

    while(linia[index] != '|') {
        idSTR += linia[index];
        index++;
    }
    index++;
    while(linia[index] != '|') {
        nazwa += linia[index];
        index++;
    }
    index++;
    while(linia[index] != '|') {
        haslo += linia[index];
        index++;
    }

    id = stoi(idSTR);

    pojedynczyUzytkownik.id = id;
    pojedynczyUzytkownik.nazwa = nazwa;
    pojedynczyUzytkownik.haslo = haslo;

    uzytkownicy.push_back(pojedynczyUzytkownik);
}

int odczytZPlikuAdresaci(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    adresaci.erase(adresaci.begin(), adresaci.end());
    fstream plik;
    string linia = "", odczytaneIdSTR = "";
    int id = 0, odczytaneId;

    plik.open("Adresaci.txt", ios::in);

    if(!plik.good()) {
        return id;
    }

    do {
        cin.sync();
        getline(plik, linia);
        if(linia == "") {
            break;
        }
        size_t pozycjaPierwszegoZnaku = linia.find('|');
        size_t pozycjaDrugiegoZnaku = linia.find('|', pozycjaPierwszegoZnaku + 1);
        odczytaneIdSTR = linia.substr(pozycjaPierwszegoZnaku + 1, pozycjaDrugiegoZnaku - pozycjaPierwszegoZnaku - 1);
        odczytaneId = stoi(odczytaneIdSTR);
        if(odczytaneId == idZalogowanegoUzytkownika) {
            rozdzielDaneZPlikuAdresaci(linia, adresaci, id);
            id++;
        }
    } while(linia != "");

    plik.close();
    return id;
}

int odczytZPlikuUzytkownicy(vector <Uzytkownik> &uzytkownicy) {
    fstream plik;
    string linia = "";
    int id = 0;

    plik.open("Uzytkownicy.txt", ios::in);

    if(!plik.good()) {
        return id;
    }

    do {
        getline(plik, linia);
        if(linia == "") {
            break;
        }
        rozdzielDaneZPlikuUzytkownicy(linia, uzytkownicy, id);
        id++;
    } while(linia != "");


    plik.close();
    return id;
}

int dodajAdresata(vector <Adresat> &adresaci, int iloscAdresatow, int idZalogowanegoUzytkownika, int nrId) {
    fstream plik;
    plik.open("Adresaci.txt", ios::app);
    plik.close();

    int rozmiarWektora = adresaci.size();
    Adresat pojedynczyAdresat;

    pojedynczyAdresat.id = nrId + 1;

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

    zapisDoPlikuAdresaci(adresaci, iloscAdresatow, idZalogowanegoUzytkownika);
    cout << endl;
    cout << "Dodano pomyslnie adresata";
    Sleep(1500);

    return rozmiarWektora + 1;
}

void wyszukajAdresataPoImieniu(vector <Adresat> adresaci, int iloscAdresatow) {
    string imie = "";
    int brakImienia = 0;
    cout << "Podaj imie: ";
    imie = wczytajLinie();

    if(iloscAdresatow == 0) {
        cout << "Brak zapisanych adresatow w bazie." << endl;
        Sleep(1500);
    } else {
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

    if(iloscAdresatow == 0) {
        cout << "Brak zapisanych adresatow w bazie." << endl;
        Sleep(1500);
    } else {
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

void zapisanieNowychDanychDoPlikuAdresaciEdycja(vector <Adresat> &adresaci, int wyborID, int pozycja, int idZalogowanegoUzytkownika) {

    fstream plik, plikTymczasowy;
    string linia = "", odczytaneIdSTR = "";
    int odczytaneId;

    plik.open("Adresaci.txt", ios::in);
    if(!plik.good()) {
        cout << "Plik nie istnieje";
        exit(0);
    }

    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out | ios::app);
    if(!plikTymczasowy.good()) {
        cout << "Plik nie istnieje";
        exit(0);
    }

    do {
        getline(plik, linia);
        if(linia == "") {
            break;
        }
        size_t pozycjaPierwszegoZnaku = linia.find('|');
        if(pozycjaPierwszegoZnaku == 1) {
            odczytaneIdSTR = linia.substr(0, 1);
        } else {
            odczytaneIdSTR = linia.substr(0, pozycjaPierwszegoZnaku - 1);
        }

        odczytaneId = stoi(odczytaneIdSTR);
        if(odczytaneId == wyborID) {
            plikTymczasowy << adresaci[pozycja].id << '|';
            plikTymczasowy << idZalogowanegoUzytkownika << '|';
            plikTymczasowy << adresaci[pozycja].imie << '|';
            plikTymczasowy << adresaci[pozycja].nazwisko << '|';
            plikTymczasowy << adresaci[pozycja].nrTelefonu << '|';
            plikTymczasowy << adresaci[pozycja].email << '|';
            plikTymczasowy << adresaci[pozycja].adres << '|' << endl;
        }
        else{
            plikTymczasowy << linia << endl;
        }
    } while(linia != "");

    plik.close();
    plikTymczasowy.close();
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
}

void zapisanieNowychDanychDoPlikuAdresaciUsuniecie(vector <Adresat> &adresaci, int wyborID, int idZalogowanegoUzytkownika) {

    fstream plik, plikTymczasowy;
    string linia = "", odczytaneIdSTR = "";
    int odczytaneId;

    plik.open("Adresaci.txt", ios::in);
    if(!plik.good()) {
        cout << "Plik nie istnieje";
        exit(0);
    }

    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out | ios::app);
    if(!plikTymczasowy.good()) {
        cout << "Plik nie istnieje";
        exit(0);
    }

   do{
        getline(plik, linia);
        if(linia == "") {
            break;
        }
        size_t pozycjaPierwszegoZnaku = linia.find('|');
        if(pozycjaPierwszegoZnaku == 1) {
            odczytaneIdSTR = linia.substr(0, 1);
        } else {
            odczytaneIdSTR = linia.substr(0, pozycjaPierwszegoZnaku - 1);
        }

        odczytaneId = stoi(odczytaneIdSTR);
        if(odczytaneId != wyborID) {
            plikTymczasowy << linia << endl;
        }
    } while(linia != "");

    plik.close();
    plikTymczasowy.close();
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
}

int usunAdresata(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    int wyborID = 0;
    char znakPotwierdzenia;
    bool czyIstniejeAdresat = false;
    cout << "Podaj numer ID adresata, ktorego chcesz usunac: ";
    wyborID = pobierzLiczbe();
    int rozmiarWektora = adresaci.size();

    if(rozmiarWektora == 0) {
        cout << "Brak adresatow w bazie";
        Sleep(1500);
        return rozmiarWektora;
    } else {
        for(int i = 0; i < rozmiarWektora; i++) {
            if(wyborID == adresaci[i].id)
                czyIstniejeAdresat = true;
        }

    if (czyIstniejeAdresat == false) {
            cout << "Nie ma takiego adresata w ksiazce adresowej" << endl;
            Sleep(1500);
    } else {
            cout << "Potwierdz naciskajac klawisz 't': ";
            znakPotwierdzenia = pobierzZnak();

            if(znakPotwierdzenia == 't') {
                auto it = adresaci.begin();
                for(int pozycja = 0; pozycja < rozmiarWektora; pozycja++) {
                    if (adresaci[pozycja].id == wyborID) {
                        zapisanieNowychDanychDoPlikuAdresaciUsuniecie(adresaci, wyborID, idZalogowanegoUzytkownika);
                        adresaci.erase(it);
                        rozmiarWektora = adresaci.size();
                        break;
                    }
                    it++;
                }
            } else
                return rozmiarWektora;
            cout << "Usunieto pomyslnie adresata";
            Sleep(1500);
            return rozmiarWektora;
        }
    }
}

void zmienImie(vector <Adresat> &adresaci, int wyborID, int iloscAdresatow, int idZalogowanegoUzytkownika) {
    for(int pozycja = 0; pozycja < iloscAdresatow; pozycja++) {
        if (adresaci[pozycja].id == wyborID) {
            cout << "Stare imie: " << adresaci[pozycja].imie << endl;
            cout << "Nowe imie: ";
            cin >> adresaci[pozycja].imie;
            zapisanieNowychDanychDoPlikuAdresaciEdycja(adresaci, wyborID, pozycja, idZalogowanegoUzytkownika);
            cout << "Pomyslnie zmieniono imie";
            Sleep(1500);
        }
    }
}

void zmienNazwisko(vector <Adresat> &adresaci, int wyborID, int iloscAdresatow, int idZalogowanegoUzytkownika) {
    for(int pozycja = 0; pozycja < iloscAdresatow; pozycja++) {
        if (adresaci[pozycja].id == wyborID) {
            cout << "Stare nazwisko: " << adresaci[pozycja].nazwisko << endl;
            cout << "Nowe nazwisko: ";
            cin >> adresaci[pozycja].nazwisko;
            zapisanieNowychDanychDoPlikuAdresaciEdycja(adresaci, wyborID, pozycja, idZalogowanegoUzytkownika);
            cout << "Pomyslnie zmieniono nazwisko";
            Sleep(1500);
        }
    }
}

void zmienNumerTelefonu(vector <Adresat> &adresaci, int wyborID, int iloscAdresatow, int idZalogowanegoUzytkownika) {
    for(int pozycja = 0; pozycja < iloscAdresatow; pozycja++) {
        if (adresaci[pozycja].id == wyborID) {
            cout << "Stary numer telefonu: " << adresaci[pozycja].nrTelefonu << endl;
            cout << "Nowy numer telefonu: ";
            cin >> adresaci[pozycja].nrTelefonu;
            zapisanieNowychDanychDoPlikuAdresaciEdycja(adresaci, wyborID, pozycja, idZalogowanegoUzytkownika);
            cout << "Pomyslnie zmieniono numer telefonu";
            Sleep(1500);
        }
    }
}

void zmienEmail(vector <Adresat> &adresaci, int wyborID, int iloscAdresatow, int idZalogowanegoUzytkownika) {
    for(int pozycja = 0; pozycja < iloscAdresatow; pozycja++) {
        if (adresaci[pozycja].id == wyborID) {
            cout << "Stary email: " << adresaci[pozycja].email << endl;
            cout << "Nowy email: ";
            cin >> adresaci[pozycja].email;
            zapisanieNowychDanychDoPlikuAdresaciEdycja(adresaci, wyborID, pozycja, idZalogowanegoUzytkownika);
            cout << "Pomyslnie zmieniono email";
            Sleep(1500);
        }
    }
}

void zmienAdres(vector <Adresat> &adresaci, int wyborID, int iloscAdresatow, int idZalogowanegoUzytkownika) {
    for(int pozycja = 0; pozycja < iloscAdresatow; pozycja++) {
        if (adresaci[pozycja].id == wyborID) {
            cout << "Stary adres: " << adresaci[pozycja].adres << endl;
            cout << "Nowy adres: ";
            cin >> adresaci[pozycja].adres;
            zapisanieNowychDanychDoPlikuAdresaciEdycja(adresaci, wyborID, pozycja, idZalogowanegoUzytkownika);
            cout << "Pomyslnie zmieniono adres";
            Sleep(1500);
        }
    }
}

void edytujAdresata(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    int wyborID = 0, wyborEdycji = 0;
    bool czyIstniejeAdresat = false;
    int rozmiarWektora = adresaci.size();
    cout << "Podaj numer ID adresata, ktorego dane chcesz edytowac" << endl;
    wyborID = pobierzLiczbe();

    if(rozmiarWektora == 0) {
        cout << "Brak adresatow w bazie";
        Sleep(1500);
        return;
    } else {
        for(int i = 0; i < rozmiarWektora; i++) {
            if(wyborID == adresaci[i].id) {
                czyIstniejeAdresat = true;
            }
        }
    }
    if (czyIstniejeAdresat == false) {
        cout << "Nie ma takiego adresata w ksiazce adresowej" << endl;
    } else {
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
            zmienImie(adresaci, wyborID, rozmiarWektora, idZalogowanegoUzytkownika);
            break;
        case 2:
            zmienNazwisko(adresaci, wyborID, rozmiarWektora, idZalogowanegoUzytkownika);
            break;
        case 3:
            zmienNumerTelefonu(adresaci, wyborID, rozmiarWektora, idZalogowanegoUzytkownika);
            break;
        case 4:
            zmienEmail(adresaci, wyborID, rozmiarWektora, idZalogowanegoUzytkownika);
            break;
        case 5:
            zmienAdres(adresaci, wyborID, rozmiarWektora, idZalogowanegoUzytkownika);
            break;
        case 9:
            return;
            break;
        }
    }
}

int main() {
    vector <Adresat> adresaci;
    vector <Uzytkownik> uzytkownicy;

    int wybor = 0;
    int iloscAdresatow = 0;
    int nrId = 0;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;

    iloscUzytkownikow = odczytZPlikuUzytkownicy(uzytkownicy);
    nrId = obliczenieId();

    while(true) {
        if(idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << "Ksiazka adresowa" << endl << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl << endl;
            cout << "Twoj wybor: ";
            wybor = pobierzLiczbe();
            cout << endl;
            switch(wybor) {
            case 1:
                system("cls");
                iloscUzytkownikow = rejestracja(uzytkownicy, iloscUzytkownikow);
                break;
            case 2:
                system("cls");
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
                if(idZalogowanegoUzytkownika != 0){
                    iloscAdresatow = odczytZPlikuAdresaci(adresaci, idZalogowanegoUzytkownika);
                }
                break;
            case 9:
                exit(0);
                break;
            default:
                cout << "Nie ma takiej opcji. Prosze wybierz inny numer" << endl;
                Sleep(1500);
                break;
            }
        } else {
            system("cls");
            cout << "Ksiazka adresowa" << endl << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj adresata po imieniu" << endl;
            cout << "3. Wyszukaj adresata po nazwisku" << endl;
            cout << "4. Wyswietl liste wszystkich zapisanych osob" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edycja danych adresata" << endl << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl << endl;
            cout << "Twoj wybor: ";
            wybor = pobierzLiczbe();
            cout << endl;

            switch(wybor) {
            case 1:
                iloscAdresatow = dodajAdresata(adresaci, iloscAdresatow, idZalogowanegoUzytkownika, nrId);
                nrId++;
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
                iloscAdresatow = usunAdresata(adresaci, idZalogowanegoUzytkownika);
                break;
            case 6:
                system("cls");
                edytujAdresata(adresaci, idZalogowanegoUzytkownika);
                break;
            case 7:
                zmianahasla(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
                break;
            case 8:
                idZalogowanegoUzytkownika = 0;
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
    }
    return 0;
}
