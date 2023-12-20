#include <iostream>     //Layton Miller     4/18/2023     Project 7: Survival Game
#include <sstream>
#include <time.h>

using namespace std;

class Player {
    public:
    Player(int x, int y){
        health = MAX_HEALTH;
        hunger = MAX_HUNGER;
        thirst = MAX_THIRST;
        
        this->x = x;
        this->y = y;
        this->score = 0;
    }
    
    int getScore() const {
        return score;
    }
    
    void takeDamage(int val){
        this->health -= val;
        if(this->health < 0) this->health = 0;
    }
    
    void takeTurn(){
        this->thirst--;
        this->hunger--;
        
        if(this->thirst <= 0){
            this->health--;
            this->thirst = 0;
        }
        
        if(this->hunger <= 0){
            this->health--;
            this->hunger = 0;
        }
        
        this->score++;
    }
    
    string getStats() const {
        stringstream ss;
        ss  << "============\n"
            << "Health: " << this->health << "\n" 
            << "Hunger: " << this->hunger << "\n" 
            << "Thirst: " << this->thirst << "\n"
            << "============\n";
        return ss.str();
    }
    
    bool isAlive() const {
        return this->health > 0;
    }
    
    void increaseThrist(int val){
        this->thirst = this->thirst + val;
        if(this->thirst > MAX_THIRST) this->thirst = MAX_THIRST;
    }
    
    void increaseHunger(int val){
        this->hunger += val;
        if(this->hunger > MAX_HUNGER) this->hunger = MAX_HUNGER;
    }
    
    int x, y;
    private:
    int health, hunger, thirst, score;
    const int MAX_HEALTH = 3;
    const int MAX_HUNGER = 5;
    const int MAX_THIRST = 3;
};

class Land {
    public:
    virtual string getDescription() = 0;
    virtual string visit(Player& player) = 0;
};

class logicSystems : public Land {
    public:
    string getDescription(){
        return "Logic Systems, a land full of tricky true or false questions.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 50){
            player.takeDamage(1);
            return "You incorrectly answered one of Ssas' multiple choice questions,\nyou lose 1 HP for descending mental health.";
        }
        else{
            player.increaseThrist(1);
            return "Despite getting the question wrong about flop-flops,\nProfessor Euhs decides to drop an extra quiz and gives you a Java Monster for thirst!";
        }
    }
};

class networkTheory1 : public Land {
    public:
    string getDescription(){
        return "Network Theory 1, a land full of laziness and very little attendance.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 75){
            player.takeDamage(1);
            return "Professor Nasah caught you doing KVL instead of being lazy,\nyou lose 1 HP after getting hit by a falling eraser.";
        }
        else{
            player.increaseHunger(1);
            return "Your newfound laziness now requires you to intake less calories\nand your hunger to learn was satisfied. Your hunger increases by 1.";
        }
    }
};

class SoVi : public Land {
    public:
    string getDescription(){
        return "SoVi, a land full of unlimited food with limited taste.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 81){
            player.takeDamage(1);
            return "You ate four slices of pizza and discovered you were lactose intolerant.\nYou lose 1 HP.";
        }
        else{
            player.increaseHunger(2);
            player.increaseThrist(1);
            return "You found your way to the main course and had gelato for dessert.\n";
        }
    }
};

class Business : public Land {
    public:
    string getDescription(){
        return "Belk college of Business, a land of temptation through salesmen, partying, and just general temptations.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 70){
            return "You met with your peer advisor for advice, it wasted your time completely.";
        }
        else{
            player.increaseThrist(1);
            return "You found the RedBull truck and it quenches your thirst (and gives you wings but not really).";
        }
    }
};

class CraverRoad : public Land {
    public:
    string getDescription(){
        return "Craver Road, one of the most challenging paths to cross.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 69){
            player.takeDamage(3);
            return "You got hit by the Silver Line bus.";
        }
        else{
            player.increaseHunger(1);
            player.increaseThrist(1);
            return "You safely make it to Wendy's and have a lovely meal.";
        }
    }
};

class UREC : public Land {
    public:
    string getDescription(){
        return "UREC, a land of bountiful gains and sports galore.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 75){
            player.takeDamage(1);
            return "Ouch! You dropped a weight on your toe and lost 1 HP.";
        }
        else{
            player.increaseThrist(1);
            return "You played a fantastic round of badminton and then finished a yellow gatorade.";
        }
    }
};

class FootballGame : public Land {
    public:
    string getDescription(){
        return "A 49ers Football Game, there's no good description with our team for this, but enjoy the football game.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 80){
            player.takeDamage(1);
            return "Yikes! Someone threw a can of Pick n' Roll and it bonked you on the head.";
        }
        else{
            player.increaseHunger(1);
            return "The concessions messed up and gave you a free hot dog! You devour it.";
        }
    }
};

class Atkins : public Land {
    public:
    string getDescription(){
        return "Atkins, a land full of students on the grind or at least pretending to be productive.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 85){
            player.takeDamage(1);
            return "Someone caught you in the study room they reserved and did not take it lightly.\nLose 1 HP.";
        }
        else{
            player.increaseHunger(1);
            player.increaseThrist(1);
            return "You decided to treat yourself today with some Starbies, it was scrumdidlyumptious.";
        }
    }
};

const int MAP_SIZE = 10;
Land* map[MAP_SIZE][MAP_SIZE];

void populateMap(){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            // TODO: Modify this code to add your new land types
            int randomNum = rand() % 8;
            switch(randomNum){
                case 0: 
                    map[i][j] = new logicSystems;
                    break;
                case 1:
                    map[i][j] = new networkTheory1;
                    break;
                case 2:
                    map[i][j] = new SoVi;
                    break;
                case 3: 
                    map[i][j] = new Business;
                    break;
                case 4:
                    map[i][j] = new CraverRoad;
                    break;
                case 5:
                    map[i][j] = new UREC;
                    break;
                case 6: 
                    map[i][j] = new FootballGame;
                    break;
                case 7: 
                    map[i][j] = new Atkins;
                    break;
                default:
                    cout << "Invalid land type selected" << endl;
                    break;
            }
        }
    }
}

int main(){
    srand(time(0));
    
    populateMap();
    
    Player player(MAP_SIZE/2, MAP_SIZE/2);
    
    cout << "Congratulations! You have been accepted to UNC Charlotte,\nan accomplishment only 4 out of 5 people who apply get!" << endl;
    
    // TODO: Handle boundary conditions (e.g., if index out of bounds north, you index the south-most location)
    
    while(player.isAlive()){
        if((player.y-1) < 0){
            cout << "To the north you see " << map[player.x][player.y + 9]->getDescription() << endl;
        }
        else{
            cout << "To the north you see " << map[player.x][player.y - 1]->getDescription() << endl;
        }
        
        if((player.x+1) > 9){
            cout << "To the east you see " << map[player.x - 9][player.y]->getDescription() << endl;
        }
        else{
            cout << "To the east you see " << map[player.x + 1][player.y]->getDescription() << endl;
        }
        
        if((player.y+1) > 9){
            cout << "To the south you see " << map[player.x][player.y - 9]->getDescription() << endl;
        }
        else{
            cout << "To the south you see " << map[player.x][player.y + 1]->getDescription() << endl;
        }
        
        if((player.x - 1) < 0){
            cout << "To the west you see " << map[player.x + 9][player.y]->getDescription() << endl;
        }
        else{
            cout << "To the west you see " << map[player.x - 1][player.y]->getDescription() << endl;
        }
        
        
        cout << "Which way will you go? Enter N, E, S, or W:" << endl;
        bool charInput = false;
        char userInput;
        while(!charInput){
            cin >> userInput;
            if(userInput == 'N' || userInput == 'E' || userInput == 'S' || userInput == 'W'){
                charInput = true;
            }
            else{
                cout << "Please enter N, E, S, or W." << endl;
            }
        }
        
        switch(userInput){
            case 'N':
                if((player.y - 1) < 0){
                    player.y = player.y + 9;
                }
                else{
                    player.y = player.y - 1;
                }
                break;
            case 'E':
                if((player.x + 1) > 9){
                    player.x = player.x - 9;
                }
                else{
                    player.x = player.x + 1;
                }
                break;
            case 'S':
                if((player.y + 1) > 9){
                    player.y = player.y - 9;
                }
                else{
                    player.y = player.y + 1;
                }
                break;
            case 'W':
                if((player.x - 1) < 0){
                    player.x = player.x + 9;
                }
                else{
                    player.x = player.x - 1;
                }
                break;
            default:
                break;
        }
        
        cout << map[player.x][player.y]->visit(player) << endl;
        
        cout << player.getStats() << endl;
        player.takeTurn();
    }
    
    cout << "You died." << endl;
    cout << player.getScore() << endl;
    
    return 0;
}