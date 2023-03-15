#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <bits/stdc++.h> 
#include "../game/gameState.hpp" 
#include "commandException.hpp"

#include "../ability/double.hpp"
#include "../ability/abillityless.hpp"
#include "../ability/half.hpp"
#include "../ability/next.hpp"
#include "../ability/quadruple.hpp"
#include "../ability/quarter.hpp"
#include "../ability/reRoll.hpp"
#include "../ability/reverse_direction.hpp"
#include "../ability/swap_card.hpp"
#include "../ability/switch.hpp"


using namespace std;

map<string, int> commands = {{"NEXT", 0}, {"DOUBLE", 1}, {"HALF", 2}, {"RE-ROLL", 3}, {"QUADRUPLE", 4}, {"QUARTER", 5}, {"REVERSE", 6}, {"SWAP",7}, {"SWITCH", 8}, {"ABILITYLESS", 9}};

class Command {
    private:
        GameState gameState;
        string command;
    public: 
        Command(GameState gameState){
            this->gameState = gameState;
        }

        void commandValidation(){
            cout<<"silahkan input command : ";
            cin >> command;
            cout << endl;
            auto In = commands.find(command);
            if(In == commands.end()){
                commandException err(command, " ", gameState.players.at(gameState.turn).getIsAbilityLess());
                throw err;
            }
        }
        void inputCommand(){
            bool valid = false;
            while(!valid){
                try{
                    commandValidation();
                    abillityValidation();
                    valid = true;
                }
                catch(commandException err){
                    err.errorMessage();
                }
            }
        }
        GameState getGamestate(){
            return gameState;
        }
        void setGameState(GameState gameState){
            this->gameState = gameState;
        }
        void abillityValidation(){
            switch (commands[this->command])
            {
            case 0:
            {
                Next next(this->gameState);
                next.DoAction();
                this->gameState = next.GetGameState();
                break;
            }
            case 1:
            {
                Double dble(this->gameState);
                dble.DoAction();
                this->gameState = dble.GetGameState();
                break;
            }
            case 2:
            {
                Half half(this->gameState);
                half.DoAction();
                this->gameState = half.GetGameState();
                break;
            }
            case 3:
            {
                if(gameState.players.at(gameState.turn).getAbility() == "RE-ROLL"){
                    ReRoll reRoll(this->gameState);
                    reRoll.DoAction();
                    this->gameState = reRoll.GetGameState();
                }
                else{
                    commandException err(" ", "RE-ROLL", gameState.players.at(gameState.turn).getIsAbilityLess());
                    throw err;
                }
                break;
            }
            case 4:
            {
                if(gameState.players.at(gameState.turn).getAbility() == "QUADRUPLE"){
                    Quadruple quadruple(this->gameState);
                    quadruple.DoAction();
                    this->gameState = quadruple.GetGameState();
                }
                else{
                    commandException err(" ", "QUADRUPLE", gameState.players.at(gameState.turn).getIsAbilityLess());
                    throw err;
                }
                break;
            }
            case 5:
            {
                if(gameState.players.at(gameState.turn).getAbility() == "QUARTER"){
                    Quarter quarter(this->gameState);
                    quarter.DoAction();
                    this->gameState = quarter.GetGameState();
                }
                else{
                    commandException err(" ", "QUARTER", gameState.players.at(gameState.turn).getIsAbilityLess());
                    throw err;
                }
                break;
            }
            case 6:
            {
                if(gameState.players.at(gameState.turn).getAbility() == "REVERSE"){
                    ReverseDirection reverseDirection(this->gameState);
                    reverseDirection.DoAction();
                    this->gameState = reverseDirection.GetGameState();
                }
                else{
                    commandException err(" ", "reverseDirection", gameState.players.at(gameState.turn).getIsAbilityLess());
                    throw err;
                }
                break;
            }
            case 7:
            {
                if(gameState.players.at(gameState.turn).getAbility() == "SWAP"){
                    vector<Player> listTarget;
                    for(size_t i = 0; i<gameState.players.size(); i++){
                        if(i != gameState.turn){
                            listTarget.push_back(gameState.players[i]);
                        }
                    }
                    for(size_t i = 0; i<listTarget.size(); i++){
                        cout << i+1<< listTarget[i].getName()<<endl;
                    }
                    cout << gameState.players.at(gameState.turn).getName() << " akan melakukan swap"<< endl;
                    int noPlayer1, noPlayer2, noKartu1, noKartu2;
                    cout << "Masukkan nomor urut pemain pertama yang ingin ditukar" << endl;
                    cin >> noPlayer1;
                    while(noPlayer1 < 1 || noPlayer1 >6){
                        cout << "input tidak valid!! ulangi "<<endl;
                        cin >> noPlayer1;
                    }
                    auto iter1 = find(gameState.players.begin(), gameState.players.end(), listTarget[noPlayer1-1]);
                    noPlayer1 = distance(gameState.players.begin(), iter1);
                    listTarget.erase(listTarget.begin() + noPlayer1-1);
                    for(size_t i = 0; i<listTarget.size(); i++){
                        cout << i+1<< listTarget[i].getName()<<endl;
                    }
                    cout << "Masukkan nomor urut pemain kedua yang ingin ditukar" << endl;
                    cin >> noPlayer2;
                    while(noPlayer2 < 1 || noPlayer2 >6){
                        cout << "input tidak valid!! ulangi "<<endl;
                        cin >> noPlayer2;
                    }
                    auto iter2 = find(gameState.players.begin(), gameState.players.end(), listTarget[noPlayer2-1]);
                    noPlayer2 = distance(gameState.players.begin(), iter2);
                    cout << "Pilih kiri atau kanan dari pemain pertama" << endl;
                    cout << "1. Kanan"<<endl;
                    cout << "2. Kiri"<< endl;
                    cin >> noKartu1;
                    while(noKartu1 <1 && noKartu1 > 2){
                        cout << "input tidak valid!! ulangi "<<endl;
                        cin >> noKartu1;
                    }
                    cout << "Pilih kiri atau kanan dari pemain kedua" << endl;
                    cout << "1. Kanan"<<endl;
                    cout << "2. Kiri"<< endl;
                    cin >> noKartu2;
                    while(noKartu2 <1 && noKartu2 > 2){
                        cout << "input tidak valid!! ulangi "<<endl;
                        cin >> noKartu2;
                    }
                    SwapCard swapCard(this->gameState, noPlayer1, noPlayer2, noKartu1-1, noKartu2-1);
                    swapCard.DoAction();
                    this->gameState = swapCard.GetGameState();
                }
                else{
                    commandException err(" ", "swap-card", gameState.players.at(gameState.turn).getIsAbilityLess());
                    throw err;
                }
                break;
            }
            case 8:
            {
                if(gameState.players.at(gameState.turn).getAbility() == "SWITCH"){
                    int noPlayer;
                    vector<Player> listTarget;
                    cout << gameState.players.at(gameState.turn).getName() << " akan melakukan switch"<< endl;
                    cout << "Kartu sekarang adalah : "<< endl;
                    cout << gameState.players.at(gameState.turn).getPlayerCard().getCard()[0].getNumber() << " " <<gameState.players.at(gameState.turn).getPlayerCard().getCard()[0].getColor() << endl;
                    cout << gameState.players.at(gameState.turn).getPlayerCard().getCard()[1].getNumber() << " " <<gameState.players.at(gameState.turn).getPlayerCard().getCard()[1].getColor() << endl;
                    cout << "Masukkan no pemain yang akan ditukar dengan Anda" << endl;
                    for(size_t i = 0; i<gameState.players.size(); i++){
                        if(i != gameState.turn){
                            listTarget.push_back(gameState.players[i]);
                        }
                    }
                    for(size_t i = 0; i<listTarget.size(); i++){
                        cout << i+1<< listTarget[i].getName()<<endl;
                    }
                    cin >> noPlayer;
                    while(noPlayer < 1 || noPlayer >6){
                        cout << "input tidak valid!! ulangi "<<endl;
                        cin >> noPlayer;
                    }
                    auto iter = find(gameState.players.begin(), gameState.players.end(), listTarget[noPlayer-1]);
                    noPlayer = distance(gameState.players.begin(), iter);
                    Switch swit = Switch(this->gameState, noPlayer);
                    swit.DoAction();
                    this->gameState = swit.GetGameState();
                }
                else{
                    commandException err(" ", "switch", gameState.players.at(gameState.turn).getIsAbilityLess());
                    throw err;
                }
                break;
            }
            case 9:
            {
                if(gameState.players.at(gameState.turn).getAbility() == "ABILITYLESS"){
                    vector<Player> listTarget;
                    cout << gameState.players.at(gameState.turn).getName() << " akan mematikan kartu ablity lawan!"<< endl;
                    cout << "silahkan pilih nomor pemain yang ingin dimatikan!"<< endl;
                    for(size_t i = 0; i<gameState.players.size(); i++){
                        if(i != gameState.turn){
                            listTarget.push_back(gameState.players[i]);
                        }
                    }
                    for(size_t i = 0; i<listTarget.size(); i++){
                        cout << i+1<< listTarget[i].getName()<<endl;
                    }
                    int nomorTarget;
                    cin >> nomorTarget;
                    while(nomorTarget < 1 || nomorTarget >6){
                        cout << "input tidak valid!! ulangi "<<endl;
                        cin >> nomorTarget;
                    }
                    auto iter = find(gameState.players.begin(), gameState.players.end(), listTarget[nomorTarget-1]);
                    nomorTarget = distance(gameState.players.begin(), iter);

                    AbilityLess abilityLess = AbilityLess(this->gameState, nomorTarget);
                    abilityLess.DoAction(); 
                    this->gameState = abilityLess.GetGameState();
                }
                else{
                    commandException err(" ", "abillityLess", gameState.players.at(gameState.turn).getIsAbilityLess());
                    throw err;
                }
                break;
            }

            default:
                break;
            }
        }
        
};

#endif