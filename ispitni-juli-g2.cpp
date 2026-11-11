#include <iostream>
#include<cstring>
#include<sstream>
#include<vector>
#include<thread>
#include<mutex>
#include<regex>
#include<exception>

using namespace std;
string crt = "\n-------------------------------------------------------------------------------- - \n";
string PORUKA_TELEFON = crt + "TELEFONE ISKLJUCITE I ODLOZITE U TORBU, DZEP ILI DRUGU LOKACIJU VAN DOHVATA.\n"
"CESTO SE NA TELEFONIMA (PRO)NALAZE PROGRAMSKI KODOVI KOJI MOGU BITI ISKORISTENI ZA\n" "RJESAVANJE ISPITNOG ZADATKA, STO CE, U SLUCAJU PRONALASKA, BITI SANKCIONISANO.\n\n"
"SVI KOD KOJIH BUDE PRONADJEN TELEFON ILI NEKI DRUGI UREDJAJ KOJI MOZE SADRZAVATI\n"
"MATERIJAL ILI RJESENJA ISPITNIH ZADATAKA CE BITI UDALJENI SA ISPITA I BIT CE POKRENUT\n" "POSTUPAK PROTIV NJIH" + crt;
string PORUKA_ISPIT = crt + "0. PROVJERITE DA LI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n""1. SVE KLASE SA DINAMICKOM ALOKACIJOM MORAJU IMATI ISPRAVAN DESTRUKTOR\n"
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
enum StatusZahtjeva { ZAPRIMLJEN, DIJAGNOSTIKA, POPRAVKA, ZAVRSEN };
const char* StatusZahtjevaNazivi[] = {
 "ZAPRIMLJEN", "DIJAGNOSTIKA", "POPRAVKA", "ZAVRSEN"
};
ostream& operator<<(ostream& COUT, const StatusZahtjeva& obj) {
	COUT << StatusZahtjevaNazivi[obj];
	return COUT;
}

string GenerisiOznaku(const char* imeprezime, int broj, int godina) {
	if (broj < 1 || broj>999 || godina < 2000 || godina>2099)
	{
		return AlocirajTekst("SRV-000/XX-0000");
		}
	string sifra;
	string imePrezime = AlocirajTekst(imeprezime);
	sifra += "SRV-";
	if (broj < 10) sifra += "00";
	else if (broj > 9 && broj < 100) sifra += "0";
	sifra += to_string(broj);
	sifra += "/";
	string inicijali;
	inicijali += toupper(imePrezime[0]);

	int brojac = 0;
	for (size_t i = 0; i < imePrezime.length(); i++)
	{
		if (imePrezime[i] == ' ')
		{
			brojac++;
		}
	}
	if (brojac == 1) {
		inicijali += toupper(imePrezime[imePrezime.find(' ') + 1]);
		sifra += inicijali;
	}
	else
	{
		int dvaimena = imePrezime.find(' ')+1;
		for (size_t i = dvaimena; i < imePrezime.length(); i++)
		{
			if (imePrezime[i] == ' ')
			{
				inicijali += toupper(imePrezime[i+1]);
				sifra += inicijali;
			}
		}
	}
	sifra += "-";
	sifra += to_string(godina);

	return sifra;

}

bool ValidirajOznaku(string oznaka) {
	return regex_match(oznaka, regex("^[A-Z]{3}[-][0-9]{2}[1-9]{1}[/][A-Z]{2}[-][0-9]{4}$"));
}
template<class T1, class T2, int max>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	Kolekcija() : _trenutno(0) {
		_elementi1 = new T1[max];
		_elementi2 = new T2[max];
	}
	Kolekcija(const Kolekcija& obj) {
		_trenutno = obj._trenutno;

			_elementi1 = new T1[obj._trenutno];
			_elementi2 = new T2[obj._trenutno];
			for (size_t i = 0; i < _trenutno; i++)
			{
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];
			}

	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if (this != &obj) {
			delete[] _elementi1;
			delete[] _elementi2;
			_elementi1 = nullptr;
			_elementi2 = nullptr;
			_trenutno = 0;

			_trenutno = obj._trenutno;
			_elementi1 = new T1[obj._trenutno];
			_elementi2 = new T2[obj._trenutno];
			for (size_t i = 0; i < _trenutno; i++)
			{
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];
			}
		}
		return *this;
	}

	Kolekcija UkloniDuplikate() {
		Kolekcija novaKolekcija;
		for (size_t i = 0; i < _trenutno; i++) {
			bool pronadjenDuplikat = false;
			for (size_t j = 0; j < novaKolekcija.GetTrenutno(); j++) {
				if (novaKolekcija.GetElement1(j) == _elementi1[i] &&
					novaKolekcija.GetElement2(j) == _elementi2[i]) {
					pronadjenDuplikat = true;
					break;
				}
			}

			if (!pronadjenDuplikat) {
				novaKolekcija.Dodaj(_elementi1[i], _elementi2[i]);
			}
		}

		return novaKolekcija;

	}

	void Dodaj(T1 prvi, T2 drugi) {
		if (_trenutno >= max) {
			throw exception("Kolekcija je puna");
		}
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		temp1[_trenutno] = prvi;
		temp2[_trenutno] = drugi;
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = temp1;
		_elementi2 = temp2;
		_trenutno++;
	}
	int GetTrenutno() const { return _trenutno; }
	const T1& GetElement1(int indeks) const {
		return
			_elementi1[indeks];
	}
	const T2& GetElement2(int indeks) const {
		return
			_elementi2[indeks];
	}
	T2& GetElement2(int index) {
		return _elementi2[index];
	}
	T1& operator[](int index) {
		return _elementi1[index];
	}
	bool operator==(const Kolekcija& obj) {
		if (_trenutno != obj._trenutno) return false;
		for (size_t i = 0; i < _trenutno; i++)
		{
			if (_elementi1[i] != obj._elementi1[i] || _elementi2[i] != obj._elementi2[i])
				return false;
		}
		return true;
	}

	friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
		for (int i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetElement1(i) << " " << obj.GetElement2(i) <<
			endl;
		return COUT;
	}
	~Kolekcija() {
		delete[] _elementi1;
		delete[] _elementi2;
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
};
class DatumVrijeme {
	int* _dan, * _mjesec, * _godina, * _sati, * _minute;
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
	DatumVrijeme& operator=(const DatumVrijeme& obj) {
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

	bool operator>(const DatumVrijeme& obj)const {
		if (*_godina > *obj._godina) return true;
		else if (*_godina < *obj._godina) return false;

		else if (*_godina == *obj._godina) {
			if (*_mjesec > *obj._mjesec)	return true;
			else if (*_mjesec < *obj._mjesec)	return false;

			else if (*_mjesec == *obj._mjesec)
			{
				if (*_dan > *obj._dan) return true;
				else if (*_dan < *obj._dan) return false;

				else if (*_dan == *obj._dan) {
					if (*_sati > *obj._sati) return true;
					else if (*_sati < *obj._sati) return false;

					else if (*_sati == *obj._sati) {
						if (*_minute > *obj._minute) return true;
						else if (*_minute < *obj._minute || *_minute == *obj._minute) return false;
					}
				}
			}
		}
		return false;
	}
	bool operator==(const DatumVrijeme& obj)const {
		return (*_dan == *obj._dan && *_mjesec == *obj._mjesec && *_godina == *obj._godina && *_sati == *obj._sati && *_minute == *obj._minute);
	}
	string ToString() const {
		stringstream s;
		if (*_dan < 10) s << "0";
		s << *_dan << ".";
		if (*_mjesec < 10) s << "0";
		s << *_mjesec<<".";
		s << *_godina << ". ";
		if (*_sati < 10) s << "0";
		s << *_sati << ":";
		if (*_minute < 10) s << "0";
		s << *_minute << endl;
		return s.str();
	}
	int GetGodina() const { return *_godina; }
	friend ostream& operator<<(ostream& COUT, const DatumVrijeme& obj)
	{
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
class Intervencija {
	string _opis;
	string _tehnicar;
	double _cijena;
	int _trajanjeMinuta;
public:
	Intervencija(string opis="", string tehnicar="", double cijena=0, int trajanjeminuta=0) {
		_opis = opis;
		_tehnicar = tehnicar;
		_cijena = cijena;
		_trajanjeMinuta = trajanjeminuta;
	}
	Intervencija(const Intervencija& obj) {
		_opis = obj._opis;
		_tehnicar = obj._tehnicar;
		_cijena = obj._cijena;
		_trajanjeMinuta = obj._trajanjeMinuta;
	}
	Intervencija& operator=(const Intervencija& obj) {
		if (this != &obj) {
			_opis = obj._opis;
			_tehnicar = obj._tehnicar;
			_cijena = obj._cijena;
			_trajanjeMinuta = obj._trajanjeMinuta;
		}
		return *this;
	}
	string ToString() const {
		stringstream s;
		s << _opis << " | " << _tehnicar << " | " << _cijena << " KM | " << _trajanjeMinuta << " min " << endl;
		return s.str();
	}
	const string& GetOpis() const { return _opis; }
	const string& GetTehnicar() const { return _tehnicar; }
	double GetCijena() const { return _cijena; }
	int GetTrajanjeMinuta() const { return _trajanjeMinuta; }
	friend ostream& operator<<(ostream& COUT, const Intervencija& obj)
	{
		COUT << obj.ToString();
		return COUT;
	}
};
class Klijent {
	string _imePrezime;
	string _email;
	string _telefon;
public:
	Klijent(string imeprezime = "", string email = "", string telefon = "") {
		_imePrezime = imeprezime;
		_email = email;
		_telefon = telefon;
	}
	Klijent(const Klijent& obj) {
		_imePrezime = obj._imePrezime;
		_email = obj._email;
		_telefon = obj._telefon;
	}
	Klijent& operator=(const Klijent& obj) {
		if (this != &obj) {
			_imePrezime = obj._imePrezime;
			_email = obj._email;
			_telefon = obj._telefon;
		}
		return *this;
	}
	const string& GetImePrezime() const { return _imePrezime; }
	const string& GetEmail() const { return _email; }
	const string& GetTelefon() const { return _telefon; }
	friend ostream& operator<<(ostream& COUT, const Klijent& obj) {
		COUT << obj.GetImePrezime() << " | " << obj.GetEmail()
			<< " | " << obj.GetTelefon();
		return COUT;
	}
};
class ServisniZahtjev {
	char* _oznaka;
	char* _uredjaj;
	char* _opisKvara;
	int _redniBroj;
	Klijent _klijent;
	Kolekcija<StatusZahtjeva, DatumVrijeme, 10> _statusi;
	vector<Intervencija> _intervencije;
public:
	ServisniZahtjev(const char* uredjaj = "", const char* opiskvara = "", Klijent klijent=Klijent(), int rednibroj = 0, DatumVrijeme datum=DatumVrijeme(), StatusZahtjeva=ZAPRIMLJEN) {
		_oznaka = AlocirajTekst((GenerisiOznaku(klijent.GetImePrezime().c_str(), rednibroj, datum.GetGodina())).c_str());
		_uredjaj = AlocirajTekst(uredjaj);
		_opisKvara = AlocirajTekst(opiskvara);
		_statusi.Dodaj(ZAPRIMLJEN, datum);
		_klijent = klijent;
		_redniBroj = rednibroj;
	}
	ServisniZahtjev(const ServisniZahtjev& obj) {
		_oznaka = AlocirajTekst(obj.GetOznaka());
		_uredjaj = AlocirajTekst(obj.GetUredjaj());
		_opisKvara = AlocirajTekst(obj.GetOpisKvara());
		_statusi = obj.GetStatusi();
		_intervencije = obj.GetIntervencije();
		_klijent = obj.GetKlijent();
		_redniBroj = obj.GetRedniBroj();
	}
	ServisniZahtjev& operator=(const ServisniZahtjev& obj) {
		if (this != &obj) {
			delete[]_oznaka;
			delete[]_uredjaj;
			delete[]_opisKvara;

			_redniBroj = obj.GetRedniBroj();
			_klijent = obj.GetKlijent();
			_oznaka = AlocirajTekst(obj.GetOznaka());
			_uredjaj = AlocirajTekst(obj.GetUredjaj());
			_opisKvara = AlocirajTekst(obj.GetOpisKvara());
			_statusi = obj.GetStatusi();
			_intervencije = obj.GetIntervencije();
		}
		return *this;
	}
	const char* GetOznaka() const { return _oznaka; }
	const char* GetUredjaj() const { return _uredjaj; }
	const char* GetOpisKvara() const { return _opisKvara; }
	int GetRedniBroj() const { return _redniBroj; }
	Klijent& GetKlijent() { return _klijent; }
	const Klijent& GetKlijent() const { return _klijent; }
	Kolekcija<StatusZahtjeva, DatumVrijeme, 10>& GetStatusi() {
		return _statusi;
	}
	const Kolekcija<StatusZahtjeva, DatumVrijeme, 10>& GetStatusi()
		const {
		return _statusi;
	}
	vector<Intervencija>& GetIntervencije() { return _intervencije; }
	const vector<Intervencija>& GetIntervencije() const {
		return
			_intervencije;
	}
	StatusZahtjeva GetTrenutniStatus() const {
		return
			_statusi.GetElement1(_statusi.GetTrenutno() - 1);
	}

	string ToString() const{
		stringstream s;
		s << _oznaka << " | " << _klijent.GetImePrezime() << " | " << _uredjaj << " | " << GetTrenutniStatus();
		return s.str();
	}
	friend ostream& operator<<(ostream& COUT, const ServisniZahtjev&
		obj) {
		COUT << obj.ToString();
		return COUT;
	}

	double UkupnaCijena() {
		double ukupnacijena=0;
		for (size_t i = 0; i < this->GetIntervencije().size(); i++)
		{
			ukupnacijena += this->GetIntervencije()[i].GetCijena();
		}
		return ukupnacijena;
	}
	int UkupnoTrajanje() {
		int ukupnotrajanje = 0;
		for (size_t i = 0; i < this->GetIntervencije().size(); i++)
		{
			ukupnotrajanje += this->GetIntervencije()[i].GetTrajanjeMinuta();
		}
		return ukupnotrajanje;
	}
	bool DodajIntervenciju(Intervencija intervencija){
		if ((this->GetTrenutniStatus() == DIJAGNOSTIKA || this->GetTrenutniStatus() == POPRAVKA) && intervencija.GetCijena()>0 && intervencija.GetTrajanjeMinuta()>0) {
			this->GetIntervencije().push_back(intervencija);

			return true;
		}
		return false;
	}

	bool DodajStatus(StatusZahtjeva status, DatumVrijeme datum) {
		if (datum > _statusi.GetElement2(_statusi.GetTrenutno() - 1))
		{
			if (status-1== _statusi.GetElement1(_statusi.GetTrenutno()-1))
			{
				if (_statusi.GetElement1(_statusi.GetTrenutno()) == ZAVRSEN)
					return false;
				else {
					_statusi.Dodaj(status, datum);
					return true;
				}
			}
			else
			return false;
		}
		return false;
	}

	~ServisniZahtjev() {
		delete[] _oznaka;
		delete[] _uredjaj;
		delete[] _opisKvara;
		_oznaka = _uredjaj = _opisKvara = nullptr;
	}
};
mutex m;
class Servis {
	char* _naziv;
	vector<ServisniZahtjev> _zahtjevi;
public:

	Servis(const char* naziv = "") {
		_naziv = AlocirajTekst(naziv);
	}
	Servis(const Servis& obj) {
		_naziv = AlocirajTekst(obj._naziv);
		_zahtjevi = obj._zahtjevi;
	}
	ServisniZahtjev* PronadjiZahtjev(const char* oznaka) {
		ServisniZahtjev* temp = new ServisniZahtjev;
		for (size_t i = 0; i < _zahtjevi.size(); i++)
		{
			if (strcmp(_zahtjevi[i].GetOznaka(), oznaka) == 0)
			{
				temp = &_zahtjevi[i];
				return temp;
			}
		}
		return nullptr;

	}
	void DodajZahtjev(ServisniZahtjev zahtjev) {

		for (size_t i = 0; i < _zahtjevi.size(); i++)
		{
			if (strcmp(_zahtjevi[i].GetOznaka(), zahtjev.GetOznaka())==0 && _zahtjevi[i].GetRedniBroj() == zahtjev.GetRedniBroj())
				throw exception("Zahtjev je vec dodat.");
		}
		_zahtjevi.push_back(zahtjev);
	}
	Servis& operator=(const Servis& obj) {
		if (this != &obj) {
			delete[] _naziv;
			_naziv= AlocirajTekst(obj._naziv);
			_zahtjevi = obj._zahtjevi;
		}
		return *this;
	}
	void saljiracun(ServisniZahtjev zahtjev) {
		m.lock();
		cout << "To: " << zahtjev.GetKlijent().GetEmail() << endl;
		cout << "From: racuni@servis.ba" << endl;
		cout << "Subject: Servisni zahtjev zavrsen - racun" << endl;
		cout << "Postovani " << zahtjev.GetKlijent().GetImePrezime() << ", " << endl;
		cout << "Servisni zahtjev " << zahtjev.GetOznaka() << " za uredjaj " << zahtjev.GetUredjaj() << " je zavrsen." << endl;
		cout << "Ukupan iznos: " << zahtjev.UkupnaCijena() << " KM" << endl;
		cout << "Hvala na povjerenju." << endl;
		m.unlock();
	}
	bool EvidentirajStatus(const char* oznaka, StatusZahtjeva status, DatumVrijeme datum) {
		for (size_t i = 0; i < _zahtjevi.size(); i++)
		{
			if (strcmp(_zahtjevi[i].GetOznaka(), oznaka) == 0)
			{

				if (_zahtjevi[i].DodajStatus(status, datum) && status == ZAVRSEN)
				{
					thread t1(&Servis::saljiracun, this, _zahtjevi[i]);
					t1.join();
					return true;
				}
				else
					return false;
			}
		}
		return false;
	}
	vector<ServisniZahtjev*> IzdvojiNezavrsene() {
		vector<ServisniZahtjev*> temp;
		for (size_t i = 0; i < _zahtjevi.size(); i++)
		{
			if (_zahtjevi[i].GetTrenutniStatus() != ZAVRSEN)
				temp.push_back(new ServisniZahtjev(_zahtjevi[i]));
		}
		return temp;
	}
	double IzracunajPrihod() {
		double prihod = 0;
		for (size_t i = 0; i < _zahtjevi.size(); i++)
		{
			if (_zahtjevi[i].GetTrenutniStatus() == ZAVRSEN)
			{
				prihod+=_zahtjevi[i].UkupnaCijena();
			}
		}
		return prihod;
	}
	const char* GetNaziv() const { return _naziv; }
	vector<ServisniZahtjev>& GetZahtjevi() { return _zahtjevi; }
	const vector<ServisniZahtjev>& GetZahtjevi() const {
		return
			_zahtjevi;
	}
	~Servis() {
		delete[] _naziv; _naziv = nullptr;
	}
};
int main() {

		if (GenerisiOznaku("Amina Buric", 42, 2026) == "SRV-042/AB-2026")
			cout << "Oznaka OK" << crt;
	if (GenerisiOznaku("Goran Skondric", 7, 2026) == "SRV-007/GS2026")
		cout << "Oznaka OK" << crt;
	if (GenerisiOznaku("Ana Marija Kovac", 156, 2027) ==
		"SRV-156/AK-2027")
		cout << "Oznaka OK" << crt;
	if (GenerisiOznaku("Amina", 42, 2026) == "SRV-000/XX-0000" &&
		GenerisiOznaku("Amina Buric", 0, 2026) == "SRV-000/XX-0000" &&
		GenerisiOznaku("Amina Buric", 1000, 2026) == "SRV-000/XX-0000"
		&&
		GenerisiOznaku("Amina Buric", 42, 1999) == "SRV-000/XX-0000")
		cout << "Neispravni podaci za oznaku OK" << crt;
	if (ValidirajOznaku("SRV-042/AB-2026"))
		cout << "OZNAKA VALIDNA" << crt;
	if (!ValidirajOznaku("SRV/042-AB-2026") &&
		!ValidirajOznaku("SRV-42/AB-2026") &&
		!ValidirajOznaku("SRV-042/Ab-2026") &&
		!ValidirajOznaku("SRV-000/AB-2026") &&
		!ValidirajOznaku("2026-SRV-042/AB"))
		cout << "OZNAKA NIJE VALIDNA" << crt;
	Kolekcija<int, string, 6> brojevi;
	brojevi.Dodaj(10, "Deset");
	brojevi.Dodaj(20, "Dvadeset");
	brojevi.Dodaj(10, "Deset");
	brojevi.Dodaj(30, "Trideset");
	brojevi.Dodaj(20, "Dvadeset");
	cout << brojevi << crt;
	Kolekcija<int, string, 6> bezDuplikata =
		brojevi.UkloniDuplikate();
	cout << "Bez duplikata:" << crt << bezDuplikata;
	cout << "Original:" << crt << brojevi;
	try {
		Kolekcija<int, string, 2> puna;
		puna.Dodaj(1, "Jedan");
		puna.Dodaj(2, "Dva");
		puna.Dodaj(3, "Tri");
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}
	Kolekcija<int, string, 6> kopijaBrojeva = brojevi;
	kopijaBrojeva[0] = 100;
	Kolekcija<int, string, 6> dodijeljeniBrojevi;
	dodijeljeniBrojevi = brojevi;
	dodijeljeniBrojevi.GetElement2(0) = "Izmijenjeno";
	cout << "Original:" << crt << brojevi;
	cout << "Kopija:" << crt << kopijaBrojeva;
	cout << "Dodijeljeni objekat:" << crt << dodijeljeniBrojevi;
	DatumVrijeme zaprimljen(9, 7, 2026, 8, 0);
	DatumVrijeme dijagnostika(9, 7, 2026, 9, 0);
	DatumVrijeme popravka(9, 7, 2026, 10, 0);
	DatumVrijeme zavrsen(9, 7, 2026, 11, 0);
	cout << zaprimljen.ToString() << crt; // 09.07.2026 08:00
	if (dijagnostika > zaprimljen)
		cout << "Vrijeme dijagnostike je nakon zaprimanja" << crt;
	DatumVrijeme kopijaDatuma(dijagnostika);
	if (kopijaDatuma == dijagnostika && !(zaprimljen == dijagnostika))
		cout << "Provjera vremena, OK." << crt;
	Klijent amina("Amina Buric", "amina@fit.ba", "061-111-222");
	Klijent goran("Goran Skondric", "goran@fit.ba", "062-222-333");
	Klijent kopijaKlijenta = amina;
	cout << kopijaKlijenta << crt;
	Intervencija pregled("Dijagnostika uredjaja", "Haris Hadzic", 20,
		30);
	Intervencija zamjenaDiska("Zamjena diska", "Haris Hadzic", 85.5,
		45);
	Intervencija instalacija("Instalacija sistema", "Maja Majic", 35,
		60);
	cout << zamjenaDiska.ToString() << crt;
	ServisniZahtjev laptop("Laptop", "Ne pokrece se", amina, 42,
		zaprimljen);
	ServisniZahtjev telefon("Telefon", "Razbijen ekran", goran, 7,
		zaprimljen);
	cout << laptop.ToString() << crt;
	if (laptop.ToString() == "SRV-042/AB-2026 | Amina Buric | Laptop | ZAPRIMLJEN")
		cout << "ServisniZahtjev ToString OK" << crt;
	if (!laptop.DodajStatus(POPRAVKA, dijagnostika))
		cout << "Preskakanje statusa nije dozvoljeno" << crt;
	if (laptop.DodajStatus(DIJAGNOSTIKA, dijagnostika))
		cout << "Status DIJAGNOSTIKA dodan" << crt;
	if (!laptop.DodajStatus(DIJAGNOSTIKA, popravka))
		cout << "Ponavljanje statusa nije dozvoljeno" << crt;

	if (laptop.DodajIntervenciju(pregled))
		cout << "Intervencija dodana" << crt;
	if (laptop.DodajStatus(POPRAVKA, popravka))
		cout << "Status POPRAVKA dodan" << crt;
	laptop.DodajIntervenciju(zamjenaDiska);
	laptop.DodajIntervenciju(instalacija);
	cout << "Ukupna cijena: " << laptop.UkupnaCijena() << " KM" <<
		crt;
	cout << "Ukupno trajanje: " << laptop.UkupnoTrajanje() << " min"
		<< crt;
	cout << laptop << crt;
	ServisniZahtjev kopijaLaptopa = laptop;
	cout << kopijaLaptopa << crt;
	Servis fitServis("FIT Servis");
	fitServis.DodajZahtjev(laptop);
	fitServis.DodajZahtjev(telefon);
	try {
		fitServis.DodajZahtjev(telefon);
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}
	string oznakaLaptopa = laptop.GetOznaka();
	ServisniZahtjev* pronadjen =
		fitServis.PronadjiZahtjev(oznakaLaptopa.c_str());
	if (pronadjen != nullptr)
		cout << "Pronadjen zahtjev: " << pronadjen->GetOznaka() <<
		crt;
	if (fitServis.PronadjiZahtjev("SRV-999/XX-2026") == nullptr)
		cout << "Zahtjev nije pronadjen" << crt;
	if (fitServis.EvidentirajStatus(oznakaLaptopa.c_str(), ZAVRSEN, zavrsen))
		cout << "Zahtjev zavrsen i racun poslan" << crt;
	if (!fitServis.EvidentirajStatus(
		oznakaLaptopa.c_str(), ZAVRSEN, DatumVrijeme(9, 7, 2026, 12, 0)))
		cout << "Ponavljanje zavrsnog statusa nije dozvoljeno" << crt;
	if (!fitServis.EvidentirajStatus(
		"NEPOSTOJECI", DIJAGNOSTIKA, dijagnostika))
		cout << "Status nije evidentiran za nepostojeci zahtjev" <<
		crt;

	vector<ServisniZahtjev*> nezavrseni =
		fitServis.IzdvojiNezavrsene();
	for (auto zahtjev : nezavrseni)
		cout << zahtjev->GetOznaka() << " -> "
		<< StatusZahtjevaNazivi[(int)zahtjev->GetTrenutniStatus()] <<
		crt;
	cout << "Ostvareni prihod: " << fitServis.IzracunajPrihod()<< " KM" << crt;
	Servis kopijaServisa = fitServis;
	cout << kopijaServisa.GetNaziv() << " ima "
		<< kopijaServisa.GetZahtjevi().size() << " zahtjeva" << crt;

	cin.get();
	return 0;
}
