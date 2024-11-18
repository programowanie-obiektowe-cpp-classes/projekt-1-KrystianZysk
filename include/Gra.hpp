#pragma once
#include "Firma.hpp"
#include <utility>
class Gra {
public:
    Firma firma;
    Gra(){
        firma.zatrudnij(std::move(std::make_unique<Inz>()));
        firma.zatrudnij(std::move(std::make_unique<Mkt>()));
        firma.zatrudnij(std::move(std::make_unique<Mag>()));
        firma.zatrudnij(std::move(std::make_unique<Rob>()));
        while (firma.get_stan_konta() > 0){
            akcja_gracza();
        }
    };

    void tick(){
        firma.zaplac_wynagrodzenie();
        firma.splac_raty();
        firma.oblicz_przychod();
        std::cout<<"Stan konta: "<<firma.get_stan_konta()<<"\n"; 
    }
    void akcja_gracza(){
        std::string akcja;
        std::cout<<"Podaj akcje do wykonania:";
        std::cin>>akcja;
        if (akcja == "zinz"){
            firma.zatrudnij(std::move(std::make_unique<Inz>()));
            std::cout<<"Udalo sie zatrudnic Inzyniera.\n";
        }
        else if (akcja == "zmkt"){
            firma.zatrudnij(std::move(std::make_unique<Mkt>()));
            std::cout<<"Udalo sie zatrudnic Marketera.\n";
        }
        else if (akcja == "zmag"){
            firma.zatrudnij(std::move(std::make_unique<Mag>()));
            std::cout<<"Udalo sie zatrudnic Magazyniera.\n";
        }
        else if (akcja == "zrob"){
            firma.zatrudnij(std::move(std::make_unique<Rob>()));
            std::cout<<"Udalo sie zatrudnic Robotnika.\n";
        }
        else if (akcja == "lp"){
            std::cout<<"Lista pracownikow:\n";
            firma.drukuj_pracownikow();
        }
        else if (akcja == "kred"){
            double kwota_kredytu;
            double czas_splaty_kredytu;
            std::cout<<"Podaj kwote kredytu:";
            std::cin>>kwota_kredytu;
            std::cout<<"Podaj ilosc rat:";
            std::cin>>czas_splaty_kredytu;
            if (kwota_kredytu>firma.wartosc_firmy()){
                std::cout<< "Wartosc kredytu jest wieksza niz wartosc firmy\n";
                std::cout<< "Wartosc kredytu:" << kwota_kredytu <<"\n";
                std::cout<< "Wartosc firmy:" << firma.wartosc_firmy() <<"\n";
            }
            else {
                firma.wez_kredyt(kwota_kredytu, czas_splaty_kredytu);
                std::cout<<"Udalo sie wziac kredyt.\n";
            }
        }
        else if (akcja == "kt"){
            tick();
        }
    }     
};