#pragma once
#include <iostream>
#include "RandomNameGenerator.hpp"
#include "RandomWydzialGenerator.hpp"

class Pracownik {
protected:
    std::string name;
    double wynagrodzenie;
public:
    Pracownik() : name(getRandomName()) {}
    
    virtual void print(){
        std::cout<<name<<"\n";
    }
    double getWynagrodzenie(){
        return wynagrodzenie;
    }

};

class Inz : public Pracownik
{
    private:
        std::string wydzial = getRandomWydzial();
    public:
        static constexpr double CI = 333;
        Inz() {
            wynagrodzenie = 6000;
        }
        void print() override {
            std::cout<<name<<" Wydzial: "<<wydzial<<" Wynagrodzenie: "<<wynagrodzenie<<" PLN \n";
        }
};

class Mkt : public Pracownik
{
    private:
        int follows = rand() % 100001;
    public:
        static constexpr double CMkt = 222;
        Mkt() {
            wynagrodzenie = 3500;
        }
        void print() override {
            std::cout<<name<<" Liczba obserwujacych: "<<follows<<" Wynagrodzenie: "<<wynagrodzenie<<" PLN \n";
        }
};

class Mag : public Pracownik
{
    private:
        bool obsl_widl = rand() % 2;
    public:
        static constexpr double CMag = 111;
        Mag() {
            wynagrodzenie = 4500;
        }
        void print() override {
            std::cout<<name<<" Obsluga wozka widlowego: "<<obsl_widl<<" Wynagrodzenie: "<<wynagrodzenie<<" PLN \n";//true, false -> tak, nie
        }
};

class Rob : public Pracownik
{
    private:
        double but = (1.0 / 3) * (rand() % 21) + 36;
    public:
        static constexpr double CR = 55;
        Rob() {
            wynagrodzenie = 4500;
        }
        void print() override {
            std::cout<<name<<" Rozmiar buta: "<<but<<" Wynagrodzenie: "<<wynagrodzenie<<" PLN \n";
        }
};