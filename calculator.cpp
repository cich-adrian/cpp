#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

class Kalkulator {
public:
    Kalkulator() {
        // Konstruktor, można umieścić dodatkowe inicjalizacje, jeśli są potrzebne
    }

    // Funkcje dla podstawowych operacji matematycznych

    double dodawanie(double a, double b) {
        return a + b;
    }

    double odejmowanie(double a, double b) {
        return a - b;
    }

    double mnozenie(double a, double b) {
        return a * b;
    }

    double dzielenie(double a, double b) {
        if (b != 0) {
            return a / b;
        }
        else {
            std::cerr << "Blad: Nie mozna dzielic przez zero." << std::endl;
            return 0.0;
        }
    }

    // Funkcja pierwiastkowania

    double pierwiastkowanie(double wartosc) {
        if (wartosc >= 0) {
            return std::sqrt(wartosc);
        }
        else {
            std::cerr << "Blad: Nie mozna obliczyc pierwiastka z liczby ujemnej." << std::endl;
            return 0.0;
        }
    }
};

class Menu {
public:
    // Funkcja wyświetlająca menu i pobierająca wybór użytkownika

    char wyswietlMenuIPobierzWybor() {
        char wybor;
        std::cout << "Wybierz operacje (+, -, *, /, s [pierwiastek]) lub 'q' aby zakonczyc: ";
        std::cin >> wybor;

        // Sprawdzenie poprawności wyboru

        while (!czyPoprawnyWybor(wybor)) {
            std::cerr << "Blad: Nieprawidlowa operacja. Prosze podac poprawny wybor." << std::endl;
            std::cout << "Wybierz operacje (+, -, *, /, s) lub 'q' aby zakonczyc: ";
            std::cin >> wybor;
        }

        return wybor;
    }

    // Funkcja pobierająca liczbę od użytkownika

    double pobierzLiczbe() {
        double liczba;
        std::cin >> liczba;

        // Sprawdzenie poprawności wprowadzonej liczby

        while (std::cin.fail()) {
            std::cin.clear();  // Wyczyszczenie błędów strumienia wejściowego
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignorowanie błędnych danych
            std::cerr << "Blad: Wprowadzona wartosc nie jest liczba. Sprobuj ponownie: ";
            std::cin >> liczba;
        }

        return liczba;
    }

    // Funkcja pytająca użytkownika, czy chce kontynuować działanie programu

    bool kontynuowac() {
        char wybor;
        std::cout << "Czy chcesz kontynuowac? (T/N): ";
        std::cin >> wybor;
        return (wybor == 'T' || wybor == 't');
    }

private:
    // Funkcja sprawdzająca poprawność wyboru

    bool czyPoprawnyWybor(char wybor) {
        return (wybor == '+' || wybor == '-' || wybor == '*' || wybor == '/' || wybor == 's' || wybor == 'q');
    }
};

int main() {
    Kalkulator mojKalkulator;
    Menu menu;
    double num1, num2{};
    char operacja;
    std::vector<double> wyniki; // Kontener STL - wektor do przechowywania wyników

    // Pętla do wykonywania operacji

    do {
        std::cout << "Podaj pierwsza liczbe: ";
        num1 = menu.pobierzLiczbe();

        operacja = menu.wyswietlMenuIPobierzWybor();

        // Jeśli operacja nie jest pierwiastkowaniem, zakończeniem, pobierz drugą liczbę

        if (operacja != 's' && operacja != 'q') {
            std::cout << "Podaj druga liczbe: ";
            num2 = menu.pobierzLiczbe();
        }

        double wynik = 0.0;

        switch (operacja) {
        case '+':
            wynik = mojKalkulator.dodawanie(num1, num2);
            break;
        case '-':
            wynik = mojKalkulator.odejmowanie(num1, num2);
            break;
        case '*':
            wynik = mojKalkulator.mnozenie(num1, num2);
            break;
        case '/':
            wynik = mojKalkulator.dzielenie(num1, num2);
            break;
        case 's':
            wynik = mojKalkulator.pierwiastkowanie(num1);
            break;
        case 'q':
            std::cout << "Zamykanie programu." << std::endl;
            break;
        default:
            std::cerr << "Blad: Nieprawidlowa operacja." << std::endl;
            break;
        }

        // Wyświetlenie wyniku

        if (operacja != 'q') {
            std::cout << "Wynik: " << wynik << std::endl;
            wyniki.push_back(wynik); // Dodanie wyniku do wektora
        }

    } while (operacja != 'q' && menu.kontynuowac());

    // Wyświetlenie wszystkich wyników na koniec programu

    std::cout << "Wyniki operacji: ";
    for (const double& wynik : wyniki) {
        std::cout << wynik << " ";
    }
    std::cout << std::endl;

    return 0;
}
