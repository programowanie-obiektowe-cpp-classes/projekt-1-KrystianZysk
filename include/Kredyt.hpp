#pragma once
#include <iostream>
#include <stdio.h>
#include <memory>
#include <cmath>

class Kredyt {
private:
    int pozostale_raty;
    double do_splaty;
    double oprocentowanie = 0.05;
public:
    double dlug;
public:
    Kredyt(double kwota, int raty) : dlug(kwota), pozostale_raty(raty) {
        double q = 1 + oprocentowanie;
        do_splaty = dlug * pow(q, raty) * (q - 1) / (pow(q, raty) - 1);
        std::cout<<"Do splaty: "<<do_splaty<<"\n";
    }

    double splac_rate() {
        if (pozostale_raty == 0) {
            return 0.0;
        } else {
            dlug -= do_splaty;
            pozostale_raty--;
            return do_splaty;
        }
    }
};