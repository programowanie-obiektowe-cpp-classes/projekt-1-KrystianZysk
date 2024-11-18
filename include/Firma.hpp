#pragma once
#include <iostream>
#include "Pracownik.hpp"
#include "Kredyt.hpp"
#include <stdio.h>
#include <variant>
#include <memory>

class Firma{
private:
    double c_stan_konta;
    int c_n_kredytow;
    int c_n_prac;
    int c_n_miesiecy;
    double c_pojemnosc;
    double c_produkty;
    double c_popyt;
    std::unique_ptr<std::unique_ptr<Pracownik>[]> c_pracownicy = std::make_unique<std::unique_ptr<Pracownik>[]>(50);
    std::unique_ptr<std::unique_ptr<Kredyt>[]> c_kredyty = std::make_unique<std::unique_ptr<Kredyt>[]>(10);
    std::unique_ptr<double[]> c_historia_przychodow = std::make_unique<double[]>(10000);
public:
    Firma() : c_stan_konta(100000), c_n_kredytow(0), c_n_prac(0), c_pojemnosc(0), c_produkty(0), c_popyt(0), c_n_miesiecy(0) {
    }
    void wez_kredyt(double kwota_, int czas_splaty_) {
        if (c_n_kredytow < 10) {
            c_kredyty[c_n_kredytow] = std::make_unique<Kredyt>(kwota_, czas_splaty_);
            c_n_kredytow++;
        } else {
            std::cout << "Za duzo kredytow." << std::endl;
        }
    }
    void splac_raty() {
        double wszystkie_raty_ = 0.0;
        for (int i = 0; i < c_n_kredytow; ++i) {
            wszystkie_raty_ += c_kredyty[i]->splac_rate();
        }
    c_stan_konta -= wszystkie_raty_;
    std::cout << "Kwota wszystkich rat wynosi: " << wszystkie_raty_ <<"\n";
    }
    void zatrudnij(std::unique_ptr<Pracownik> pracownik_) {
        if (c_n_prac < 50) {
            c_pracownicy[c_n_prac] = std::move(pracownik_);
            c_n_prac++;
        } else {
            std::cout << "Za duzo pracownikow.";
        }
    }
    void drukuj_pracownikow() const {
        for (size_t i = 0; i < c_n_prac; ++i) {
            if (c_pracownicy[i]) {
                c_pracownicy[i]->print();
            }
        }
    }
    void zaplac_wynagrodzenie(){
        double wynagordzenie_ = 0.0;
        for (size_t i = 0; i < c_n_prac; ++i) {
            if (c_pracownicy[i]) {
                wynagordzenie_ += c_pracownicy[i]->getWynagrodzenie();
            }
        }
        c_stan_konta -= wynagordzenie_;
        std::cout << "Wynagordzenie pracownikow wynosi: " << wynagordzenie_ <<"\n";
    }
    double get_stan_konta() const {
        return c_stan_konta;
    }
    void zmien_magazyn() {
    double magazyn_new_ = 0;
    for (size_t i = 0; i < c_n_prac; ++i) {
        if (c_pracownicy[i]) {
            Mag* magPtr = dynamic_cast<Mag*>(c_pracownicy[i].get());
            if (magPtr) {
                magazyn_new_ += Mag::CMag;
            }
        }
    }
    if (magazyn_new_ > c_pojemnosc){
        c_pojemnosc = magazyn_new_;
    }
    }

    void dodaj_c_produkty() {
    for (size_t i = 0; i < c_n_prac; ++i) {
        if (c_pracownicy[i]) {
            Rob* magPtr_ = dynamic_cast<Rob*>(c_pracownicy[i].get());
            if (magPtr_) {
                c_produkty += Rob::CR;
            }
        }
    }
    if (c_produkty > c_pojemnosc){
        c_produkty = c_pojemnosc;
    }
    }
    void oblicz_c_popyt() {
    c_popyt = 0;
    for (size_t i = 0; i < c_n_prac; ++i) {
        if (c_pracownicy[i]) {
            Mkt* magPtr = dynamic_cast<Mkt*>(c_pracownicy[i].get());
            if (magPtr) {
                c_popyt += Mkt::CMkt;
            }
        }
    }
    }
    void przychod()
    {
        double sprzedane_;
        double n_inz_ = 0;
        if(c_produkty >= c_popyt){
            sprzedane_ = c_popyt;
        }
        else if (c_popyt > c_produkty)
        {
            sprzedane_ = c_produkty;
        }
        for (size_t i = 0; i < c_n_prac; ++i) {
            if (c_pracownicy[i]) {
                Inz* magPtr = dynamic_cast<Inz*>(c_pracownicy[i].get());
                if (magPtr) {
                    n_inz_ += 1;
                }
            }
        }
        c_historia_przychodow[c_n_miesiecy] = sprzedane_ * n_inz_ * Inz::CI;
        c_n_miesiecy++;
        c_stan_konta += sprzedane_ * n_inz_ * Inz::CI;
        std::cout << "Przychod w tym miesiacu wyniosl: " << sprzedane_ * n_inz_ * Inz::CI <<"\n";
    }
    void zaaktualizuj_stan_magazyn() {
        c_produkty -= c_popyt;
        if(c_produkty < 0){
            c_produkty = 0;
        }
    }
    double wartosc_firmy(){
        double wartosc_ = 0.0;
        for (int i = c_n_miesiecy; i > c_n_miesiecy-4; --i) {
            wartosc_ += c_historia_przychodow[i];
        }
    return wartosc_ /= 3;
    }
    void oblicz_przychod(){
        zmien_magazyn();
        dodaj_c_produkty();
        oblicz_c_popyt();
        przychod();
        zaaktualizuj_stan_magazyn();
    }
};