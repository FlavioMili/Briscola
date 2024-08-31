#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <stdexcept>

using namespace std; 

enum class Seme { BASTONI, DENARI, COPPE, SPADE };
enum class Num { DUE, QUATTRO, CINQUE, SEI, SETTE, OTTO, NOVE, DIECI, TRE, ASSO };

typedef struct Card{
    Seme seme;
    Num num;
} Card;

int CardValue(const Card &card) {
    switch (card.num) {
        case Num::ASSO: return 11;
        case Num::TRE: return 10;
        case Num::DIECI: return 4;
        case Num::NOVE: return 3;
        case Num::OTTO: return 2;
        default: return 0;
    }
}

const char* SemeToString(Seme seme) {
    switch (seme) {
        case Seme::BASTONI: return "Bastoni";
        case Seme::DENARI: return "Denari";
        case Seme::COPPE: return "Coppe";
        case Seme::SPADE: return "Spade";
    }
}

const char* NumToString(Num num) {
    switch (num) {
        case Num::DUE: return "Due";
        case Num::QUATTRO: return "Quattro";
        case Num::CINQUE: return "Cinque";
        case Num::SEI: return "Sei";
        case Num::SETTE: return "Sette";
        case Num::OTTO: return "Otto";
        case Num::NOVE: return "Nove";
        case Num::DIECI: return "Dieci";
        case Num::TRE: return "Tre";
        case Num::ASSO: return "Asso";
    }
}

vector<Card> InitializeDeck() {
    vector<Card> deck;
    deck.reserve(40);
    for (int i = 0; i < 4; ++i) { 
        for (int j = 0; j < 10; ++j) {
            deck.push_back({ static_cast<Seme>(i), static_cast<Num>(j)});
        }
    }
    return deck;
}

void shuffleDeck(vector<Card>& deck) {
    static random_device rd;
    static mt19937 gen(rd());
    shuffle(deck.begin(), deck.end(), gen);
}

bool chooseWhoStarts() {
    static mt19937 gen{random_device{}()};
    return uniform_int_distribution<>(0, 1)(gen) == 0;
}

void PrintPlayerHand(const vector<Card>& cards) {
    for (size_t i = 0; i < cards.size(); ++i) {
        const Card& card = cards[i];
        cout << "Carta " << i + 1 << ": " << NumToString(card.num) << " di " << SemeToString(card.seme) << endl;
    }
}

void Draw(vector<Card> &player, vector<Card> &deck){
    while(size(player)<3 && !deck.empty()){
        player.push_back(deck.back());
        deck.pop_back();
    }
}

void UpdatePointsAndWinner(Card player, Card cpu, int &Ppoints, int &Cpoints, Seme briscola, bool &turn) {
    int playerValue = CardValue(player);
    int cpuValue = CardValue(cpu);

    if (player.seme == briscola && cpu.seme != briscola) {
        Ppoints += playerValue + cpuValue;
        cout << "Hai preso" << endl;
        turn = true;
    } 
    else if (player.seme != briscola && cpu.seme == briscola) {
        Cpoints += playerValue + cpuValue;
        cout << "Il computer ha preso" << endl;
        turn = false;
    } 
    else if (player.seme == briscola && cpu.seme == briscola) {
        if (player.num > cpu.num) {
            Ppoints += playerValue + cpuValue;
            cout << "Hai preso" << endl;
            turn = true;
        } else {
            Cpoints += playerValue + cpuValue;
            cout << "Il computer ha preso" << endl;
            turn = false;
        }
    } 
    else if (player.seme == cpu.seme) {
        if (player.num > cpu.num) {
            Ppoints += playerValue + cpuValue;
            cout << "Hai preso" << endl;
            turn = true;
        } else {
            Cpoints += playerValue + cpuValue;
            cout << "Il computer ha preso" << endl;
            turn = false;
        }
    } 
    else { 
        if (turn) {
            Ppoints += playerValue + cpuValue;
            cout << "Hai preso" << endl;
            turn = true;
        } else {
            Cpoints += playerValue + cpuValue;
            cout << "Il computer ha preso" << endl;
            turn = false;
        }
    }
}

Card PlayerTurn(vector<Card> &player){
    int input;
    while(true){
    cout << "Scegli una carta da 1 a " << size(player) << ": ";
    cin >> input;
        if (input >= 1 && input <= static_cast<int>(size(player))) {
                    break; 
        } else {
            cout << "Scelta non valida, scrivi un numero da 1 a " << size(player) << ": " << endl;
        }
    }
    Card chosenCard = player[input - 1];
    cout << "   Hai giocato " << NumToString(chosenCard.num) << " di " << SemeToString(chosenCard.seme) << endl <<endl;
    player.erase(player.begin() + input - 1);
    return chosenCard;
}

Card CPUWhenFirstToPlay(vector<Card> &cpu, Seme briscola) {
    vector<Card> briscolaCards;
    vector<Card> nonBriscolaCards;
    for (const auto& card : cpu) {
        if (card.seme == briscola) {
            briscolaCards.push_back(card);
        } else {
            nonBriscolaCards.push_back(card);
        }
    }
    Card chosenCard;
    if (!nonBriscolaCards.empty()) {
        // Play the lowest value non briscola card
        Card temp = nonBriscolaCards[0];
        for(int i = 0; i < size(nonBriscolaCards); i++){
            if(temp.num > nonBriscolaCards[i].num){
                temp = nonBriscolaCards[i];
            }
        }
        chosenCard = temp;
    } else if (!briscolaCards.empty()) {
        // Play the lowest value briscola card
        Card temp = briscolaCards[0];
        for(int i = 0; i < size(briscolaCards); i++){
            if(temp.num > briscolaCards[i].num){
                temp = briscolaCards[i];
            }
        }
        chosenCard = temp;
    }
    for (auto i = cpu.begin(); i != cpu.end(); ++i) {
        if (i->seme == chosenCard.seme && i->num == chosenCard.num) {
            cpu.erase(i);
            break; 
        }
    }
    cout << "   Il computer ha giocato " << NumToString(chosenCard.num) << " di " << SemeToString(chosenCard.seme) << endl;
    return chosenCard;
}

Card CPUWhenSecondToPlay(vector<Card> &cpu, Card playerCard, Seme briscola) {
    vector<Card> briscolaCards;
    vector<Card> nonBriscolaCards;
    vector<Card> sameSemeCards;

    // Separate cards into briscola and non-briscola and same seme in order to better decide which card to play
    for (const auto& card : cpu) {
        if (card.seme == briscola) {
            briscolaCards.push_back(card);
        } else {
            nonBriscolaCards.push_back(card);
            if (card.seme == playerCard.seme) {
                sameSemeCards.push_back(card);
            }
        }
    }

    Card chosenCard;

    if (playerCard.seme == briscola) {
        if(!nonBriscolaCards.empty()){
            Card temp = nonBriscolaCards[0];
            for(int i = 0; i < size(nonBriscolaCards); i++){
                if(temp.num > nonBriscolaCards[i].num){
                    temp = nonBriscolaCards[i];
                }
            }
            chosenCard = temp;
        }
        else if(!briscolaCards.empty()){
            Card temp = briscolaCards[0];
            for(int i = 0; i < size(briscolaCards); i++){
                if(temp.num > briscolaCards[i].num){
                    temp= briscolaCards[i];
                }
            }
            chosenCard = temp;
        }
    } else {
        if(!sameSemeCards.empty()){
            Card temp = sameSemeCards[0];
            for(int i = 0; i < size(sameSemeCards); i++){
                if(temp.num < sameSemeCards[i].num){
                    temp = sameSemeCards[i];
                }
            }
            chosenCard = temp;
        }
        else if(CardValue(playerCard) > 0 && !briscolaCards.empty()){ // take the least valuable briscola to win
            Card temp = briscolaCards[0];
            for(int i = 0; i < size(briscolaCards); i++){
                if(temp.num > briscolaCards[i].num){
                    temp = briscolaCards[i];
                }
            }
            chosenCard = temp;
        }
        else if(!nonBriscolaCards.empty()){
            Card temp = nonBriscolaCards[0];
            for(int i = 0; i < size(nonBriscolaCards); i++){
                if(temp.num > nonBriscolaCards[i].num){
                    temp = nonBriscolaCards[i];
                }
            }
            chosenCard = temp;
        }
        else{
            chosenCard = cpu[0];
        }
    }

    for (auto i = cpu.begin(); i != cpu.end(); ++i) {
        if (i->seme == chosenCard.seme && i->num == chosenCard.num) {
            cpu.erase(i);
            break; 
        }
    }    
    cout << "   Il computer ha giocato " << NumToString(chosenCard.num) << " di " << SemeToString(chosenCard.seme) << endl;
    return chosenCard;
}

void Turn(bool &turn, vector<Card> &player, vector<Card> &cpu, vector<Card> &deck, int &Ppoints, int &Cpoints, Seme briscola){
    Card PlayerCard, CPUCard;
    if(turn == true){ // player starts
        Draw(player, deck);
        Draw(cpu, deck);
        PrintPlayerHand(player);
        PlayerCard = PlayerTurn(player);
        CPUCard = CPUWhenSecondToPlay(cpu, PlayerCard, briscola);
    } else { // CPU starts
        Draw(cpu, deck);
        Draw(player, deck);
        CPUCard = CPUWhenFirstToPlay(cpu, briscola);
        PrintPlayerHand(player);
        PlayerCard = PlayerTurn(player);
    }
    UpdatePointsAndWinner(PlayerCard, CPUCard, Ppoints, Cpoints, briscola, turn);
}

int main(){
    auto deck = InitializeDeck();
    shuffleDeck(deck);
    bool turn = chooseWhoStarts(); // 1 for player, 0 for CPU

    Card LastCard = deck.front();
    Seme briscola = LastCard.seme;
    cout << "L'ultima carta nel mazzo è: " << NumToString(LastCard.num) << " di " << SemeToString(LastCard.seme) << endl << endl; 
    int PlayerPoints = 0;
    int CPUPoints = 0;

    vector<Card> PlayerCards;
    vector<Card> CPUCards;

    while(!deck.empty() || !PlayerCards.empty() || !CPUCards.empty()){
        cout << endl <<deck.size() << " carte rimanenti nel deck " << endl;
        cout << (turn ? "Turno tuo" : "Turno del computer") << endl << endl;
        Turn(turn, PlayerCards, CPUCards, deck, PlayerPoints, CPUPoints, briscola);
    }
    cout << endl << "Il tuo punteggio: " << PlayerPoints << endl;
    cout << "Punteggio del computer: " << CPUPoints << endl;
    if (PlayerPoints > CPUPoints) {
        cout << endl << "Hai vinto!!!" << endl;
    } else if (CPUPoints > PlayerPoints) {
        cout << endl << "Il computer ha vinto!" << endl;
    } else {
        cout << endl << "Pareggio!" << endl;
    }
}