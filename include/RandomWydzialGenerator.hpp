#pragma once
#ifndef P1_CPP_LAB_RANDOMWYDZIALGENERATOR_HPP
#define P1_CPP_LAB_RANDOMWYDZIALGENERATOR_HPP

#include <array>
#include <format>
#include <random>

inline constexpr std::array wydzial{
    "Planowania Logistyki",
    "Transportu Krajowego",
    "Transportu Miedzynarodowego",
    "Zarzadzania Magazynem",
    "Spedycji",
    "Obslugi Klienta",
    "Zarzadzania Flota",
    "Zaopatrzenia",
    "Optymalizacji Procesow Logistycznych",
    "IT i Automatyzacji Logistyki",
    "BHP i Audytu Transportowego",
    "Logistyki Morskiej",
    "Logistyki Lotniczej",
    "Ekspresowych Dostaw",
    "Dystrybucji Lokalnej",
    "Reklamacji i Zwrotow",
    "Zarzadzania Przesylkami Specjalnymi",
    "Prognozowania Popytu",
    "Zarzadzania Relacjami z Dostawcami",
    "Kontroli Jakosci Dostaw"
};

inline auto getRandomWydzial() -> std::string {
    static auto prng = std::mt19937{std::random_device{}()};
    auto fnd = std::uniform_int_distribution<std::size_t>{0, wydzial.size() - 1};
    const auto first_name = wydzial[fnd(prng)];
    return std::format("{}", first_name);
}

#endif //P1_CPP_LAB_RANDOMWYDZIALGENERATOR_HPP