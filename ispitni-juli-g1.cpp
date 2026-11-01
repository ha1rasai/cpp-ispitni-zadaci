#include <iostream>
#include<string>
#include<vector>
#include<thread>
#include<regex>
#include<mutex>
#include<sstream>
using namespace std;
string crt = "\n-------------------------------------------------------------------------------- - \n";
string PORUKA_TELEFON = crt +
"TELEFONE ISKLJUCITE I ODLOZITE U TORBU, DZEP ILI DRUGU LOKACIJU VAN DOHVATA.\n"
"CESTO SE NA TELEFONIMA (PRO)NALAZE PROGRAMSKI KODOVI KOJI MOGU BITI ISKORISTENI ZA\n"
"RJESAVANJE ISPITNOG ZADATKA, STO CE, U SLUCAJU PRONALASKA, BITI SANKCIONISANO.\n\n"
"SVI KOD KOJIH BUDE PRONADJEN TELEFON ILI NEKI DRUGI UREDJAJ KOJI MOZE SADRZAVATI\n"
"MATERIJAL ILI RJESENJA ISPITNIH ZADATAKA CE BITI UDALJENI SA ISPITA I BIT CE POKRENUT\n"
"POSTUPAK PROTIV NJIH" + crt;
string PORUKA_ISPIT = crt +
"0. PROVJERITE DA LI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE SA DINAMICKOM ALOKACIJOM MORAJU IMATI ISPRAVAN DESTRUKTOR\n"
"2. IZOSTAVLJANJE DESTRUKTORA ILI NJEGOVIH DIJELOVA BIT CE OZNACENO KAO TM\n"
"3. ATRIBUTI, METODE I PARAMETRI MORAJU BITI IDENTICNI ONIMA U TESTNOJ MAIN FUNKCIJI, \n"
" OSIM AKO POSTOJI JASNO OPISAN RAZLOG ZA MODIFIKACIJU\n"
"4. IZUZETKE BACAJTE SAMO TAMO GDJE JE IZRICITO NAGLASENO\n"
"5. SVE METODE KOJE SE POZIVAJU U MAIN-U MORAJU POSTOJATI.\n"
" AKO NEMATE ZELJENU IMPLEMENTACIJU, OSTAVITE PRAZNO TIJELO ILI VRATITE DEFAULT VRIJEDNOST\n"
"6. U MAIN FUNKCIJI MOZETE DODAVATI TESTNE PODATKE I POZIVE PO VLASTITOM IZBORU\n"
"7. TESTIRAJTE PROGRAM U OBA MODA (F5 i Ctrl+F5)" + crt;
char* AlocirajTekst(const char* tekst) {
	if (tekst == nullptr) return nullptr;
	size_t velicina = strlen(tekst) + 1;
	char* noviTekst = new char[velicina];
	strcpy_s(noviTekst, velicina, tekst);
	return noviTekst;
}
enum VrstaDostave { STANDARDNA, BRZA, MEDJUNARODNA };
const char* VrstaDostaveOznake[] = { "ST", "BR", "MD" };
const char* VrstaDostaveNazivi[] = { "STANDARDNA", "BRZA",
"MEDJUNARODNA" };
enum StatusPosiljke {
	KREIRANA, PREUZETA, U_TRANZITU, ISPORUCENA,
	OTKAZANA
};

ostream& operator<<(ostream& COUT, VrstaDostave& obj) {
	COUT << VrstaDostaveNazivi[obj];
	return COUT;
}

const char* StatusPosiljkeNazivi[] = { "KREIRANA", "PREUZETA", "UTRANZITU", "ISPORUCENA", "OTKAZANA" };

string GenerisiOznaku(const char* imeprezime, int broj, VrstaDostave status) {
	int brojac = 0;
	string imeiprezime = imeprezime;
	int lokacija = 0;
	for (size_t i = 0; i < imeiprezime.size(); i++)
	{
		if (imeiprezime[i] == ' ') {
			brojac++;
			lokacija = i;

		}
	}
	 if (status < 0 || status>2) {
		return "BH-XX0000-XX";
	}

	else if (broj < 1 || broj>9999 || brojac < 1 ) {
		return "BH-XX-0000-XX";
		
		
	}
	
	string vrsta = VrstaDostaveOznake[status];
	string oznaka;
	oznaka += "BH-";

	oznaka += vrsta;
	if ( vrsta != "ST") {
		oznaka += "-";
	}
	if (broj >= 0 && broj < 10) oznaka += "000";
	else if (broj >= 10 && broj < 100) oznaka += "00";
	else if (broj >= 100 && broj < 1000) oznaka += "0";
	oznaka += to_string(broj);
	oznaka += "-";

	
	oznaka += toupper(imeiprezime[0]);
    oznaka += toupper(imeiprezime[lokacija + 1]);
	
	
	return oznaka;
}

bool ValidirajOznaku(string oznaka) {
	regex r1("^BH[-](BR|MD)[-][0]{3}[1-9][-][A-Z]{2}$");
	regex r2("^BH[-](BR|MD)[-][0]{2}[1-9]{2}[-][A-Z]{2}$");
	regex r3("^BH[-](BR|MD)[-][0]{1}[1-9]{3}[-][A-Z]{2}$");
	regex r7("^BH[-](BR|MD)[-][1-9][0-9]{3}[-][A-Z]{2}$");
	regex r4("^BH[-][ST][0]{3}[0-9][-][A-Z]{2}$");
	regex r5("^BH[-][ST][0]{2}[0-9]{2}[-][A-Z]{2}$");
	regex r6("^BH[-][ST][0]{1}[1-9]{3}[-][A-Z]{2}$");
	regex r8("^BH[-][ST][1-9][0-9]{3}[-][A-Z]{2}$");

	return  regex_match(oznaka, r1) || regex_match(oznaka, r2) || regex_match(oznaka, r3) || regex_match(oznaka, r4) || regex_match(oznaka, r5) || regex_match(oznaka, r6) || regex_match(oznaka, r7) || regex_match(oznaka, r8);
}

template<class T1, class T2, int max>
class Kolekcija {
 T1* _elementi1[max];
 T2* _elementi2[max];
 int _trenutno;
public:
	Kolekcija() : _trenutno(0) {
		for (int i = 0; i < max; i++) {
			_elementi1[i] = nullptr;
			_elementi2[i] = nullptr;
		}
	}
 Kolekcija(const Kolekcija& obj) {
	 for (int i = 0; i < max; i++) {
		 _elementi1[i] = nullptr;
		 _elementi2[i] = nullptr;
	 }
	 _trenutno = obj._trenutno;
	 for (size_t i = 0; i < _trenutno; i++)
	 {
		 _elementi1[i] = new T1(*obj._elementi1[i]);
		 _elementi2[i] = new T2(*obj._elementi2[i]);
	 }
 
 }
 void Dodaj(T1 prvi, T2 drugi) {
	 _elementi1[_trenutno] = new T1(prvi);
	 _elementi2[_trenutno] = new T2(drugi);
	 _trenutno++;

 }

 Kolekcija DodajNaPoziciju(int lokacija, T1 prvi, T2 drugi) {
	 if (lokacija<0 || lokacija>_trenutno || _trenutno > max)
		 throw exception("Neodgovarajuca pozicija");

	 Kolekcija nova;
	 for (size_t i = 0; i < _trenutno; i++)
	 {
		 if (i == lokacija) {
			 nova.Dodaj(prvi, drugi);
		 }
		 nova.Dodaj(*_elementi1[i], *_elementi2[i]);

	 }
	 
	 return nova;
 }

 pair<T1, T2> UkloniSaPozicije(int lokacija) {
	 if (lokacija > _trenutno)
		 throw exception("Ne postoji ta pozicija.");

	 Kolekcija stara;
	 pair<T1, T2> nova= make_pair(*_elementi1[lokacija], *_elementi2[lokacija]);
	 
	
	 for (size_t i = 0; i < _trenutno; i++)
	 {
		 if (i != lokacija) {
			 stara.Dodaj(*_elementi1[i], *_elementi2[i]);
		 }
		
	 }
	
	 *this = stara;
	 return nova;
 }
 Kolekcija& operator=(const Kolekcija& obj) {
	 if (this != &obj) {
		 for (size_t i = 0; i < _trenutno; i++)
		 {
			 delete _elementi1[i];
			 delete _elementi2[i];
			 _elementi1[i] = nullptr;
			 _elementi2[i] = nullptr;
		 }
		 _trenutno = obj._trenutno;
		 for (size_t i = 0; i < _trenutno; i++)
		 {
			 _elementi1[i] = new T1(*obj._elementi1[i]);
			 _elementi2[i] = new T2(*obj._elementi2[i]);
		 }
	 }
	 return *this;
 }
 int GetTrenutno() const { return _trenutno; }
 T1& GetElement1(int indeks) { return *_elementi1[indeks]; }
 T2& GetElement2(int indeks) { return *_elementi2[indeks]; }
 const T1& GetElement1(int indeks) const {
 return
*_elementi1[indeks];
 }
const T2& GetElement2(int indeks) const {
return
*_elementi2[indeks];
 }
T1& operator[](int indeks) { return *_elementi1[indeks]; }

friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {

for (int i = 0; i < obj.GetTrenutno(); i++)
COUT << obj.GetElement1(i) << " " << obj.GetElement2(i) <<endl;
 return COUT;
 }


 ~Kolekcija() {
 for (int i = 0; i < _trenutno; i++) {
 delete _elementi1[i];
 delete _elementi2[i];
 _elementi1[i] = nullptr;
 _elementi2[i] = nullptr;
 }
 _trenutno = 0;
 }
};
class DatumVrijeme {
 int* _dan,* _mjesec,* _godina,* _sati,* _minute;
public:
 DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000,
 int sati = 0, int minute = 0) {
 _dan = new int(dan);
 _mjesec = new int(mjesec);
 _godina = new int(godina);
 _sati = new int(sati);
 _minute = new int(minute);
 }

 DatumVrijeme(const DatumVrijeme& obj) {
	 _dan = new int(*obj._dan);
	 _mjesec = new int(*obj._mjesec);
	 _godina = new int(*obj._godina);
	 _sati = new int(*obj._sati);
	 _minute = new int(*obj._minute);
 }
 
 DatumVrijeme& operator=(const  DatumVrijeme& obj) {
	 if (this != &obj) {

		 delete _dan;
		 delete _mjesec;
		 delete _godina;
		 delete _sati;
		 delete _minute;
		 _dan = _mjesec = _godina = _sati = _minute = nullptr;

		 _dan = new int(*obj._dan);
		 _mjesec = new int(*obj._mjesec);
		 _godina = new int(*obj._godina);
		 _sati = new int(*obj._sati);
		 _minute = new int(*obj._minute);

	 }
	 return *this;
 }
 bool operator==(const DatumVrijeme& obj)const {
	 return *_godina == *obj._godina && *_mjesec == *obj._mjesec && *_dan == *obj._dan && *_sati == *obj._sati && *_minute == *obj._minute;
 }
 bool operator>(const DatumVrijeme& obj)const {

	 if (*_godina > *obj._godina) return true;
	 else if (*_godina < *obj._godina) return false;
	 else if (*_godina == *obj._godina) {
		 if (*_mjesec > *obj._mjesec) return true;
		 else if (*_mjesec < *obj._mjesec) return false;
		 else if (*_mjesec == *obj._mjesec) {
			 if (*_dan > *obj._dan) return true;
			 else if (*_dan < *obj._dan) return false;
			 else if (*_dan == *obj._dan) {
				 if (*_sati * 60 + *_minute > *obj._sati * 60 + *_minute) return true;
				 else return false;
			 }
		 }
	 }
	 
 }
 string ToString()const {
	 stringstream s;
	 if (*this->_dan < 10) s << "0";
	 s << *this->_dan << ".";
	 if (*this->_mjesec < 10) s << "0";
	 s << *this->_mjesec << ".";
	 s << *this->_godina << " "; 
	 if (*this->_sati < 10) s << "0";
	 s << *this->_sati << ":";
	 if (*this->_minute < 10) s << "0";
	 s<< *this->_minute;
	 return s.str();
 }
 friend ostream& operator<<(ostream& COUT, const DatumVrijeme& obj)
{
	 //ToString vraca datum i vrijeme u formatu DD.MM.GGGG HH:MM,
	 COUT << obj.ToString();
	 return COUT;
	 }
	 ~DatumVrijeme() {
		 delete _dan;
		 delete _mjesec;
		 delete _godina;
		 delete _sati;
		 delete _minute;
		 _dan = _mjesec = _godina = _sati = _minute = nullptr;
	 }
};
class Posiljka {
	char* _oznaka;
	char* _sadrzaj;
	char* _imePrezimePrimaoca;
	char* _emailPrimaoca;
	VrstaDostave _vrstaDostave;
	int _redniBroj;
	Kolekcija<StatusPosiljke, DatumVrijeme, 10> _statusi;

	void Dealociraj() {
		delete[] _oznaka;
		delete[] _sadrzaj;
		delete[] _imePrezimePrimaoca;
		delete[] _emailPrimaoca;
		_oznaka = _sadrzaj = _imePrezimePrimaoca = _emailPrimaoca =
			nullptr;
	}

	
public:

	Posiljka(const char* sadrzaj = "", const char* imeprezime = "", const char* email = "", VrstaDostave dostava = STANDARDNA, int rednibroj = 0, DatumVrijeme datum = DatumVrijeme())
	{
		_sadrzaj = AlocirajTekst(sadrzaj);
		_imePrezimePrimaoca = AlocirajTekst(imeprezime);
		_emailPrimaoca = AlocirajTekst(email);
		_oznaka = AlocirajTekst(GenerisiOznaku(imeprezime, rednibroj, dostava).c_str());
		_redniBroj = rednibroj;
		_vrstaDostave = dostava;
		_statusi.Dodaj(KREIRANA, datum);
	}
	Posiljka(const Posiljka& obj) {
		_sadrzaj = AlocirajTekst(obj.GetSadrzaj());
		_imePrezimePrimaoca = AlocirajTekst(obj.GetImePrezimePrimaoca());
		_emailPrimaoca = AlocirajTekst(obj.GetEmailPrimaoca());
		_oznaka = AlocirajTekst(obj.GetOznaka());
		_redniBroj = obj.GetRedniBroj();
		_vrstaDostave = obj.GetVrstaDostave();
		_statusi = obj._statusi;
	}

	Posiljka& operator=(const Posiljka& obj) {
		if (this != &obj) {
			_sadrzaj = AlocirajTekst(obj.GetSadrzaj());
			_imePrezimePrimaoca = AlocirajTekst(obj.GetImePrezimePrimaoca());
			_emailPrimaoca = AlocirajTekst(obj.GetEmailPrimaoca());
			_oznaka = AlocirajTekst(obj.GetOznaka());
			_redniBroj = obj.GetRedniBroj();
			_vrstaDostave = obj.GetVrstaDostave();
			_statusi = obj._statusi;
		}
		return *this;
	}
	
	string ToString()const {
		stringstream s;
		s << this->GetOznaka() << " | " <<this->GetImePrezimePrimaoca() << " | " << VrstaDostaveNazivi[GetVrstaDostave()] << " | " << this->GetSadrzaj() << " | " << StatusPosiljkeNazivi[GetTrenutniStatus()];
		return s.str();
	}

	

	bool DodajStatus(StatusPosiljke status, DatumVrijeme datum) {
		int duzina = GetStatusi().GetTrenutno() - 1;
		DatumVrijeme datumprije=GetStatusi().GetElement2(duzina);
		if (datumprije > datum || datumprije==datum) return false;


		if (GetStatusi().GetElement1(duzina) == 3 || GetStatusi().GetElement1(duzina) == 4) return false;
		if (status == 4) {
			GetStatusi().Dodaj(status, datum); return true;
		}
		if (status-1 == GetStatusi().GetElement1(duzina)) { GetStatusi().Dodaj(status, datum); return true; }
		return false;
	}
	const char* GetOznaka() const { return _oznaka; }
	const char* GetSadrzaj() const { return _sadrzaj; }
	const char* GetImePrezimePrimaoca() const {
		return
			_imePrezimePrimaoca;
	}
	const char* GetEmailPrimaoca() const { return _emailPrimaoca; }
	VrstaDostave GetVrstaDostave() const { return _vrstaDostave; }
	int GetRedniBroj() const { return _redniBroj; }
	Kolekcija<StatusPosiljke, DatumVrijeme, 10>& GetStatusi() {
		return
			_statusi;
	}
	StatusPosiljke GetTrenutniStatus()const {
		return _statusi.GetElement1(_statusi.GetTrenutno() - 1);
	}


	friend ostream& operator<<(ostream& COUT, const Posiljka& obj) {
		// ToString vraca podatke u formatu:
		// oznaka | ime i prezime | vrsta dostave | sadrzaj | trenutni status
			// BH-BR-0042-AB | Amina Buric | BRZA | Dokumenti | KREIRANA
			COUT << obj.ToString();
		return COUT;
	}
	~Posiljka() {
		Dealociraj();
	}
};
mutex m;
class DostavnaSluzba {
	char* _naziv;
	vector<Posiljka> _posiljke;
public:
	DostavnaSluzba(const char* naziv = "") {
		_naziv = AlocirajTekst(naziv);
	}
	DostavnaSluzba(const DostavnaSluzba& obj) {
		_naziv = AlocirajTekst(obj._naziv);
		_posiljke = obj._posiljke;
	}
	DostavnaSluzba& operator=(const DostavnaSluzba& obj) {
		if (this != &obj) {
			delete[] _naziv;
			_naziv = AlocirajTekst(obj._naziv);
			_posiljke = obj._posiljke;
		}
		return *this;
	}
	
	void DodajPosiljku(Posiljka posiljka) {
		for (size_t i = 0; i < _posiljke.size(); i++)
		{
			if (posiljka.GetRedniBroj() == _posiljke[i].GetRedniBroj() || strcmp(posiljka.GetOznaka(), _posiljke[i].GetOznaka()) == 0)
				throw exception("Posiljka je vec dodata.");
		}
		_posiljke.push_back(posiljka);
	}

	Posiljka* PronadjiPosiljku(string oznaka) {
		Posiljka* nova = nullptr;
		for (size_t i = 0; i < _posiljke.size(); i++)
		{
			if (strcmp(oznaka.c_str(), _posiljke[i].GetOznaka()) == 0)
				nova = &_posiljke[i];
		}
		return nova;
	}

	void Saljimeil(Posiljka posiljka) {
		int duzina = posiljka.GetStatusi().GetTrenutno();
		m.lock();
		cout << "To: " << posiljka.GetEmailPrimaoca() << endl;
		cout << "From: info@brzaposta.ba" << endl;
		cout << "Subject: Promjena statusa posiljke." << endl;
		cout << "Postovani " << posiljka.GetImePrezimePrimaoca() << ", " << endl;
		cout << "Posiljka " << posiljka.GetOznaka() << " je promijenila status u " << StatusPosiljkeNazivi[posiljka.GetTrenutniStatus()] << "." << endl;
		cout << "Vrijeme evidentiranja: " << posiljka.GetStatusi().GetElement2(duzina - 1) << endl;
		cout << "Hvala sto koristite nase usluge." << endl;
		cout << "BrzaPosta Tim" << endl;
		m.unlock();
	}
	bool EvidentirajStatus(string oznaka, StatusPosiljke status, DatumVrijeme datum) {
		for (size_t i = 0; i < _posiljke.size(); i++)
		{
			if (strcmp(oznaka.c_str(), _posiljke[i].GetOznaka()) == 0)
			{
				
				if (_posiljke[i].DodajStatus(status, datum)) {
					thread t1(&DostavnaSluzba::Saljimeil, this, _posiljke[i]);
					t1.join();
					return true;
				}
				return false;
			}
		}
		return false;
	}
	const char* GetNaziv() const { return _naziv; }
	vector<Posiljka>& GetPosiljke() { return _posiljke; }
	~DostavnaSluzba() {
		delete[] _naziv;
		_naziv = nullptr;
	}
};
const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite da li se svako nasljedjivanje moze posmatrati kao polimorfizam i obrnuto ? Navedite konkretne primjere.\n";
		return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasnite razloge kojima bi se implementator klase mogao voditi pri donosenju odluke da sve metode u klasi (ne)proglasi virtualnim ? \n";
		return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
int main() {
	cout << PORUKA_TELEFON; cin.get();
	cout << PORUKA_TELEFON; cin.get();
	cout << PORUKA_ISPIT;
	cin.get();
	system("cls");
	cout << GetOdgovorNaPrvoPitanje() << crt;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << crt;
	cin.get();
	/*
	Funkcija GenerisiOznaku generise oznaku posiljke u formatu: BH-VDBBBB-IN
	Potpis funkcije treba biti:
	string GenerisiOznaku(const char* imePrezime, int redniBroj,
   VrstaDostave vrstaDostave)
	BH -> fiksna oznaka drzave,
	VD -> vrsta dostave: ST (standardna), BR (brza), MD
   (medjunarodna),
	BBBB -> redni broj posiljke popunjen nulama na slobodnim mjestima,
	IN -> inicijali imena i prezimena primaoca.
	Kod imena koje sadrzi vise rijeci koriste se inicijal prve i
   posljednje
	rijeci. Redni broj mora biti u rasponu 1-9999.
	Za neispravne podatke funkcija vraca "BH-XX-0000-XX".
	*/
	GenerisiOznaku("Amina Buric", 42, BRZA);
	if (GenerisiOznaku("Amina Buric", 42, BRZA) == "BH-BR-0042-AB")
		cout << "Oznaka OK" << crt;
	if (GenerisiOznaku("Goran Skondric", 7, STANDARDNA) == "BH-ST0007-GS")
		cout << "Oznaka OK" << crt;
	if (GenerisiOznaku("Ana Marija Kovac", 156, MEDJUNARODNA) ==
		"BH-MD-0156-AK")
		cout << "Oznaka OK" << crt;
	if (GenerisiOznaku("Amina", 42, BRZA) == "BH-XX-0000-XX" &&
		GenerisiOznaku("Amina Buric", 0, BRZA) == "BH-XX-0000-XX" &&
		GenerisiOznaku("Amina Buric", 10000, BRZA) == "BH-XX-0000-XX"
		&&
		GenerisiOznaku("Amina Buric", 42, (VrstaDostave)99) == "BH-XX0000-XX")
		cout << "Neispravni podaci za oznaku OK" << crt;
//	/*
//	Koristeci regex, funkcija ValidirajOznaku provjerava da li je
//   oznaka
//	zapisana u prethodno definisanom formatu. Dozvoljene su iskljucivo
//   oznake
//	vrsta ST, BR i MD, redni broj mora imati cetiri cifre i ne moze
//   biti 0000,
//	a inicijali moraju biti zapisani velikim slovima.
//	Potpis funkcije treba biti:
//	bool ValidirajOznaku(const string& oznaka)
//	*/
	if (ValidirajOznaku("BH-BR-0042-AB"))
		cout << "OZNAKA VALIDNA" << crt;
	if (!ValidirajOznaku("BH-EX-0042-AB") &&
		!ValidirajOznaku("BH-BR-042-AB") &&
		!ValidirajOznaku("BH-BR-0042-Ab") &&
		!ValidirajOznaku("BH-BR-0000-AB") &&
		!ValidirajOznaku("bh-BR-0042-AB"))
		cout << "OZNAKA NIJE VALIDNA" << crt;
	if (ValidirajOznaku(GenerisiOznaku("Maid Ramic", 284, BRZA)))
		cout << "GENERISANA OZNAKA VALIDNA" << crt;
	Kolekcija<int, string, 5> brojevi;
	brojevi.Dodaj(10, "Deset");
	brojevi.Dodaj(20, "Dvadeset");
	brojevi.Dodaj(30, "Trideset");
	cout << brojevi << crt;
	/*
//	DodajNaPoziciju dodaje novi par na lokaciju/indeks definisanu
//   prvim parametrom,
//	pomjera postojece pokazivace udesno i vraca trenutno stanje
//   kolekcije (izmijenjeni tj. prosireni objekat).
//	U slucaju popunjene kolekcije ili neispravne lokacije potrebno je
//   baciti izuzetak.
//	*/
	Kolekcija<int, string, 5> prosireniBrojevi =
		brojevi.DodajNaPoziciju(1, 15, "Petnaest");
	cout << prosireniBrojevi << crt;
//	
//	//UkloniSaPozicije uklanja par sa proslijedjene pozicije/indeksa,
// //  preostale elemente
//	//pomjera ulijevo i vraca uklonjeni par u obliku pair<T1, T2>.
//	//Za poziciju izvan opsega baca se izuzetak. 
//	
	pair<int, string> uklonjeni =
prosireniBrojevi.UkloniSaPozicije(2);
 cout << "Uklonjeno: " << uklonjeni.first << " " <<
uklonjeni.second << crt;
 cout << "Preostali elementi:" << crt << prosireniBrojevi;
 try {
 prosireniBrojevi.UkloniSaPozicije(10);
 }
 catch (exception& e) {
 cout << "Exception: " << e.what() << crt;
 }
 try {
	 brojevi.DodajNaPoziciju(15, 13, "Trinaest");
 }
 catch (exception& e) {
 cout << "Exception: " << e.what() << crt;
 }
 Kolekcija<int, string, 5> kopijaBrojeva = brojevi;
 kopijaBrojeva[0] = 100;
 Kolekcija<int, string, 5> dodijeljeniBrojevi;
 dodijeljeniBrojevi = brojevi;
 dodijeljeniBrojevi[1] = 200;
 cout << "Original:" << crt << brojevi;
 cout << "Kopija:" << crt << kopijaBrojeva;
 cout << "Dodijeljeni objekat:" << crt << dodijeljeniBrojevi;
 DatumVrijeme kreirana(1, 7, 2026, 8, 0);
 DatumVrijeme preuzeta(1, 7, 2026, 9, 0);
 DatumVrijeme tranzit(1, 7, 2026, 10, 0);
 DatumVrijeme isporucena(1, 7, 2026, 11, 0);

// /*
// ToString vraca datum i vrijeme u formatu DD.MM.GGGG HH:MM,
//ukljucujuci
// pocetne nule.
// */
	cout << kreirana.ToString() << crt; //01.07.2026 08:00
	if (preuzeta > kreirana)
		cout << "Vrijeme preuzimanja je nakon vremena kreiranja" <<
		crt;
	DatumVrijeme kopijaPreuzeta(preuzeta);
	if (kopijaPreuzeta == preuzeta && !(kreirana == preuzeta))
		cout << "Provjera vremena, OK." << crt;
	/*
//	Konstruktor Posiljke generise oznaku i evidentira pocetni status
//   KREIRANA
//	sa proslijedjenim vremenom kreiranja.
//	*/
	Posiljka dokumenti("Dokumenti", "Amina Buric", "amina@fit.ba",
		BRZA, 42, kreirana);
	Posiljka knjige("Knjige", "Goran Skondric", "goran@fit.ba",
		STANDARDNA, 7, kreirana);
	Posiljka oprema("Oprema", "Ana Marija Kovac", "ana@fit.ba",
		MEDJUNARODNA, 156, kreirana);
//	/*
//	ToString vraca podatke u formatu:
//	oznaka | ime i prezime | vrsta dostave | sadrzaj | trenutni status
//	BH-BR-0042-AB | Amina Buric | BRZA | Dokumenti | KREIRANA
//	*/
	cout << dokumenti.ToString() << crt;
	if (dokumenti.ToString() ==
		"BH-BR-0042-AB | Amina Buric | BRZA | Dokumenti | KREIRANA")
		cout << "Posiljka ToString OK" << crt;
//	/*
//	DodajStatus dodaje status samo ako je vrijeme vece od vremena
//	posljednjeg statusa i ako je promjena statusa dozvoljena.
//	Dozvoljen slijed statusa je: KREIRANA -> PREUZETA -> U_TRANZITU ->
//   ISPORUCENA
//	OTKAZANA se moze evidentirati iz bilo kojeg statusa koji nije
//   zavrsni.
//	Nakon statusa ISPORUCENA ili OTKAZANA nisu dozvoljene nove
//   promjene.
//	Preskakanje, ponavljanje statusa i hronoloski neispravno vrijeme
//   vracaju
//	false, bez izmjene kolekcije statusa.
//	*/
	if (dokumenti.DodajStatus(PREUZETA, preuzeta))
		cout << "Status PREUZETA dodan" << crt;
	if (dokumenti.DodajStatus(U_TRANZITU, tranzit))
		cout << "Status U TRANZITU dodan" << crt;
	if (dokumenti.DodajStatus(ISPORUCENA, isporucena))
		cout << "Status ISPORUCENA dodan" << crt;
	if (!dokumenti.DodajStatus(OTKAZANA, isporucena))
		cout << "Promjena zavrsnog statusa nije dozvoljena" << crt;
	if (!knjige.DodajStatus(U_TRANZITU, preuzeta))
		cout << "Preskakanje statusa nije dozvoljeno" << crt;
	if (oprema.DodajStatus(OTKAZANA, preuzeta))
		cout << "Posiljka otkazana" << crt;
	Posiljka kopijaDokumenata = dokumenti;
	cout << kopijaDokumenata << crt;
	DostavnaSluzba brzaPosta("Brza posta");
	/*
//	DodajPosiljku dodaje posiljku u dostavnu sluzbu. Nije dozvoljeno
//   dodati
//	dvije posiljke sa istim rednim brojem ili istom oznakom. U slucaju
//	duplikata metoda baca izuzetak.
//	*/
	brzaPosta.DodajPosiljku(knjige);
	brzaPosta.DodajPosiljku(oprema);
	try {
		brzaPosta.DodajPosiljku(knjige);
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}

//	/*
//	PronadjiPosiljku vraca pokazivac na posiljku sa proslijedjenom
//   oznakom.
//	Ako posiljka nije pronadjena, metoda vraca nullptr.
//	*/
	string oznakaKnjige = knjige.GetOznaka();
	Posiljka* pronadjena =
		brzaPosta.PronadjiPosiljku(oznakaKnjige);
	if (pronadjena != nullptr)
		cout << "Pronadjena posiljka: " << pronadjena->GetOznaka() <<
		crt;
	if (brzaPosta.PronadjiPosiljku("BH-ST-9999-XX") == nullptr)
		cout << "Nepostojeca posiljka nije pronadjena" << crt;
//	/*
//	EvidentirajStatus pronalazi posiljku na osnovu oznake i pokusava
//   dodati
//	novi status koristeci pravila metode DodajStatus.
//	Nakon svakog uspjesno evidentiranog statusa potrebno je u zasebnom
//   threadu
//	poslati obavijest primaocu. Obavijest se ne salje ako posiljka ne
//	postoji ili status nije dodan, te u tim slucajevima metoda vraca
//   false.
//	Primjer sadrzaja obavijesti:
//	------------------------------------------------------------------
//   ---------------
//	To: goran@fit.ba
//	From: info@brzaposta.ba
//	Subject: Promjena statusa posiljke
//	Postovani Goran Skondric,
//	Posiljka BH-ST-0007-GS je promijenila status u PREUZETA.
//	Vrijeme evidentiranja: 01.07.2026 09:00
//	Hvala sto koristite nase usluge.
//	BrzaPosta Tim
//	------------------------------------------------------------------
//   ---------------
//	*/
	if (brzaPosta.EvidentirajStatus(oznakaKnjige, PREUZETA, preuzeta))
		cout << "Status evidentiran i obavijest poslana" << crt;
	if (!brzaPosta.EvidentirajStatus(oznakaKnjige, ISPORUCENA, isporucena))
		cout << "Obavijest nije poslana za neispravnu promjenu statusa" << crt;
		if (!brzaPosta.EvidentirajStatus("NEPOSTOJECA", PREUZETA, preuzeta))
			cout << "Obavijest nije poslana za nepostojecu posiljku" <<
			crt;
//	/*
//	PosiljkePoStatusu vraca vector pokazivaca na sve posiljke ciji
//   trenutni
//	status odgovara proslijedjenom statusu.
//	*/
	/*vector<Posiljka*> preuzetePosiljke =brzaPosta.PosiljkePoStatusu(PREUZETA);
	for (auto posiljka : preuzetePosiljke)
		cout << posiljka->GetOznaka() << " -> "
		<< StatusPosiljkeNazivi[(int)posiljka->GetTrenutniStatus()] <<
		crt;*/
//	/*
//	StatistikaPoStatusu vraca kolekciju koja za svaki status,
//   redoslijedom
//	definisanim enumom StatusPosiljke, sadrzi status i broj posiljki
//   koje se
//	trenutno nalaze u tom statusu. U rezultat se dodaje svih pet
//   statusa,
//	ukljucujuci i one za koje je broj posiljki jednak nuli.
//	*/
//	Kolekcija<StatusPosiljke, int, 5> statistika =
//		brzaPosta.StatistikaPoStatusu();
//	for (int i = 0; i < statistika.GetTrenutno(); i++)
//		cout << StatusPosiljkeNazivi[(int)statistika.GetElement1(i)]
//		<< " -> " << statistika.GetElement2(i) << crt;
//	DostavnaSluzba kopijaSluzbe = brzaPosta;
//	cout << kopijaSluzbe.GetNaziv() << " ima "
//		<< kopijaSluzbe.GetPosiljke().size() << " posiljki" << crt;
	cin.get();
	return 0;
}