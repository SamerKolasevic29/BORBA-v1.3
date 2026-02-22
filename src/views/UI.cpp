#include "../../include/views/UI.h"
#include "../../include/utils/Tools.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm> 

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::endl;
using std::flush;
using std::setw;
using std::left;
using std::right;
using std::setfill;
using std::string;
using std::to_string; 
using std::unique_ptr;

namespace UI {
    // Using helper
    using namespace Animation;

    // ---[ CMD FORMATING FUNCS ]---

    void clearScreen() {
        cout << "\033[2J\033[H" << std::flush;
    }

    void clearLines(int count) {
        for (int i = 0; i < count; i++) {
            cout << "\033[F"; // Move up
            cout << "\033[2K"; // Erase line
        }
        cout << flush;
    }

    void moveDown(int count) {
        if (count < 1) return;
        cout << "\033[" << count << "B";
    }

    void hideCursor(){
        cout << "\033[?25l" << flush;
    }

    void showCursor(){
        cout << "\033[?25h" << flush;
    }

    void errorMessage(){
        clearLines(1);
        blinking("ERROR [Wrong Input!]", RED, 200, 3);
        clearLines(1);
    }

    // ---[ LOADING COMPONENTS ]---

    void loadingCSV(bool loaded){
        clearScreen();
        writeLine("Loading fighters...   ", CYAN, 50);
        bar(8, BRIGHT_CYAN, 100);
        
        if(loaded) {
            clearScreen();
            writeLine("LOAD SUCCESSFUL!", BRIGHT_CYAN, 30);
            wait(1);
            clearScreen();
        }
        else {
            clearScreen();
            writeLine("LOAD UNSUCCESSFUL!", BRIGHT_RED, 30);
            wait(1);
            return;
        }
    }

    void loadingBattle(const string& f1, const string& f2){
        writeLine("\n\t  **| BATTLE BETWEEN ", BRIGHT_BLACK, 30); 
        writeLine(f1, BRIGHT_WHITE, 30);
        writeLine(" AND ", BRIGHT_BLACK, 30);
        writeLine(f2, BRIGHT_WHITE, 30);
        writeLine(" |**  \n\n\t    ", BRIGHT_BLACK, 30);
        writeLine("LOADING BATTLE ", BRIGHT_CYAN, 30);
        bar(10, BRIGHT_CYAN, 200);
    }

    void fighterThinking(const string& f){
        hideCursor();
        thinking("\t " + f + " is thinking ", BRIGHT_BLACK, 2, 300);
        clearLines(1);
        showCursor();
    } 

    // ---[ LOGOS ]---  (printLogo() func is for opening scene)

    inline void appearLogo(){
	cout << "\033[?25l       ____   ___   ____  ____    _        \n"
	     << getAnsiCode(BRIGHT_YELLOW) << "      | __ ) / _ \\ |  _ \\| __ )  / \\       \n"
	     << getAnsiCode(YELLOW) << "      |  _ \\| | | || |_) |  _ \\ / _ \\      \n"
	     << getAnsiCode(BRIGHT_RED) << "      | |_) | |_| ||  _ <| |_) / ___ \\     \n"
	     << getAnsiCode(RED) << "      |____/ \\___/ |_| \\_\\____/_/   \\_\\   \033[0m\n"
	     << getAnsiCode(WHITE) << "\033[5m             \\_[Version: 1.3]_/                      \033[0m\n\n\n";
    }

    inline void printLogo() {
	 writeLine("\033[?25l       ____   ___   ____  ____    _        \n", WHITE, 15);
    writeLine("      | __ ) / _ \\ |  _ \\| __ )  / \\       \n", BRIGHT_YELLOW, 15);
    writeLine("      |  _ \\| | | || |_) |  _ \\ / _ \\      \n", YELLOW, 15);
    writeLine("      | |_) | |_| ||  _ <| |_) / ___ \\     \n", BRIGHT_RED, 15);
    writeLine("      |____/ \\___/ |_| \\_\\____/_/   \\_\\   \033[0m\n ", RED, 15);
    writeLine("\033[5m             \\_[Version: 1.3]_/                      \033[0m\n\n\n", BRIGHT_WHITE, 6);
    }

    // ---[ MENUS ]---

    void mainMenu(){
	appearLogo();
	writeLine("               -/ MAIN MENU \\-\n\n", WHITE, 1);
    writeLine("                   VS Comp", BRIGHT_BLACK, 5);
	writeLine("    ---    ",WHITE,5); writeLine("[", BRIGHT_RED, 5);writeLine("1", BRIGHT_WHITE, 5); writeLine("]\n", BRIGHT_RED, 5);
	writeLine("                    PvP", BRIGHT_BLACK, 5);
	writeLine("    ---       ",WHITE,5); writeLine("[", BRIGHT_RED, 5);writeLine("2", BRIGHT_WHITE, 5); writeLine("]\n", BRIGHT_RED, 5);
	writeLine("               Fighters Info", BRIGHT_BLACK, 5);
	writeLine("   ---   ",WHITE,5); writeLine("[", BRIGHT_RED, 5);writeLine("3", BRIGHT_WHITE, 5); writeLine("]\n", BRIGHT_RED, 5);
	writeLine("              Create Fighters", BRIGHT_BLACK, 5);
	writeLine("   ---  " ,WHITE,5); writeLine("[", BRIGHT_RED, 5); writeLine("4", BRIGHT_WHITE, 5); writeLine("]\n", BRIGHT_RED, 5);
	writeLine("                 About Us", BRIGHT_BLACK, 5);
	writeLine("    ---     ",WHITE,5); writeLine("[", BRIGHT_RED, 5); writeLine("5", BRIGHT_WHITE, 5); writeLine("]\n", BRIGHT_RED, 5);
	writeLine("                   Exit", BRIGHT_BLACK, 5);
	writeLine("    -----     ",WHITE,5); writeLine("[", BRIGHT_RED, 5); writeLine("0", BRIGHT_WHITE, 5); writeLine("]\n", BRIGHT_RED, 5);
    }

    void firstMenu() {
	cout << "\033[H";
    printLogo();
    writeLine("               -/ MAIN MENU \\-\n\n", WHITE, 1);
    writeLine("                   VS Comp", BRIGHT_BLACK, 20);
	writeLine("    ---    ",WHITE,10); writeLine("[", BRIGHT_RED, 20);writeLine("1", BRIGHT_WHITE, 20); writeLine("]\n", BRIGHT_RED, 20);
	writeLine("                    PvP", BRIGHT_BLACK, 20);
	writeLine("    ---       ",WHITE,5); writeLine("[", BRIGHT_RED, 20);writeLine("2", BRIGHT_WHITE, 20); writeLine("]\n", BRIGHT_RED, 20);
	writeLine("               Fighters Info", BRIGHT_BLACK, 20);
	writeLine("   ---   ",WHITE,5); writeLine("[", BRIGHT_RED, 20);writeLine("3", BRIGHT_WHITE, 20); writeLine("]\n", BRIGHT_RED, 20);
	writeLine("              Create Fighters", BRIGHT_BLACK, 20);
	writeLine("   ---  " ,WHITE,5); writeLine("[", BRIGHT_RED, 20); writeLine("4", BRIGHT_WHITE, 20); writeLine("]\n", BRIGHT_RED, 20);
	writeLine("                 About Us", BRIGHT_BLACK, 20);
	writeLine("    ---     ",WHITE,5); writeLine("[", BRIGHT_RED, 20); writeLine("5", BRIGHT_WHITE, 20); writeLine("]\n", BRIGHT_RED, 20);
	writeLine("                   Exit", BRIGHT_BLACK, 20);
	writeLine("    -----     ",WHITE,5); writeLine("[", BRIGHT_RED, 20); writeLine("0", BRIGHT_WHITE, 20); writeLine("]\n", BRIGHT_RED, 20);

   }

   // ---[ ABOUT US ]---

   void aboutUs() {
 	writeLine("\n\n\t\t\t\t-/ ABOUT US \\-\n\n", WHITE, 1);
 	
 	writeLine("  Welcome to ", BRIGHT_BLACK, 50); 
	writeLine("BORBA v1.3", BRIGHT_RED, 50);
    writeLine(", a turn-based fighting game created by ", BRIGHT_BLACK, 50); 
	writeLine("Samer Kolasevic.", BRIGHT_RED, 50);  
	writeLine("This\ngame \033[4mwas developed entirely in C++\033[0m", BRIGHT_BLACK, 50);
	writeLine(" using modular design principles to manage\ncharacters, menus, and combat logic efficiently.\n\n  ", BRIGHT_BLACK,50);
    writeLine("The goal of BORBA has always been to deliver a simple yet strategic combat\nexperience, with clear mechanics and a retro-inspired pixel aesthetic. Its modular \nstructure ensures that the game is ready for future enhancements, such as audio \nsupport, GUI improvements, and even potential ports to other platforms.\n\n  ", BRIGHT_BLACK, 50);
    writeLine("Speaking of audio, we are excited to collaborate with ",BRIGHT_BLACK,50);
	writeLine("Dino Matkovic, aka Vert",BRIGHT_RED, 50);  
	writeLine(",\nwho is helping to bring immersive sound effects and music to the game in upcoming updates.\n\n  Thank you for playing, and enjoy every battle!\n\n", BRIGHT_BLACK, 50);
   }

   // ---[INPUT & CREATE ]---

   string inputName(){
        string n;
        do {
            writeLine("Enter fighter's name (max 15 chars): ", BRIGHT_WHITE, 30);
            
            std::getline(cin >> std::ws, n); // ws 'eats' whitespace on front
            
            if(n.length() >= 16){
                clearLines(1);
                blinking("ERROR [name too long!]", RED, 200, 3);
            }
        } while(n.length() >= 16);
        return n;
    }

    int inputPositiveInt(const string& msg, Color c) {
        int x;
        while (true) {
            writeLine(msg, c, 30);
            cin >> x;

            if (cin.fail() || x <= 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                clearLines(1);
                blinking("ERROR [invalid number!]", RED, 200, 3);
            }
            else {
                return x;
            }
        }
    }

    uint8_t inputCritChance() {
        int c;
        while (true) {
            writeLine("Enter critical chance percentage (0-100): ", BRIGHT_YELLOW, 30);
            cin >> c;

            if (cin.fail() || c < 0 || c > 100) {
                cin.clear();
                cin.ignore(10000, '\n');
                clearLines(1);
                blinking("ERROR [must be 0-100!]", RED, 200, 3);
            }
            else {
                return static_cast<uint8_t>(c);
            }
        }
    }

    Fighter createFighterUI() {
        writeLine("\n\n\t\t\t\t-/ CREATE YOUR FIGHTER \\-\n\n", WHITE, 1);
        string n = inputName();
        int h = inputPositiveInt("Enter fighter's Max Health: ", BRIGHT_GREEN);
        int l = inputPositiveInt("Enter Light Attack amount: ", BRIGHT_RED);
        int s = inputPositiveInt("Enter Special Attack amount: ", RED);
        int c = inputCritChance();
        
        Fighter f(n,h,l,s,c);
        moveDown(1); 
        blinking("                           ---[ FIGHTER CREATION SUCCESSFUL ]---", BRIGHT_YELLOW, 200, 3);
        return f;
    }

    // ---[ LIST & CHOOSE]---

    void fightersInfo(const vector<unique_ptr<Fighter>>& list){
        writeLine("\n\n\t\t\t\t-/ FIGHTERS INFO \\-\n\n", WHITE, 1);
        writeLine("  |      Name      |",BRIGHT_BLACK, 5); writeLine("    Health    ", BRIGHT_BLACK, 5); cout << "|"; 
        writeLine("  Light Attack  ", BRIGHT_BLACK, 5); cout << "|"; writeLine(" Special Attack ", BRIGHT_BLACK, 5); cout << "|";
        writeLine(" Crit Chance(%) ", BRIGHT_BLACK, 5); cout << "|\n=======================================================================================\n"; 
        
        for(size_t i = 0; i < list.size(); i++){
            cout << setw(2) << right << i + 1 << ". ";
            writeLine(list[i]->Name(), WHITE, 20);
            cout <<  setw(16 - list[i]->Name().length()) << setfill(' ') << "|";
            writeLine(list[i]->HealthStr(), BRIGHT_GREEN, 20);
            cout <<  setw(15 - list[i]->HealthStr().length()) << setfill(' ') << "|";
            writeLine(list[i]->LightAttackStr(), BRIGHT_RED, 20);
            cout <<  setw(17 - list[i]->LightAttackStr().length()) << setfill(' ') << "|";
            writeLine(list[i]->SpecialAttackStr(), RED, 20);
            cout <<  setw(17 - list[i]->SpecialAttackStr().length()) << setfill(' ') << "|";
            writeLine(list[i]->CriticalStr(), BRIGHT_YELLOW, 20);
            cout <<  setw(19 - list[i]->CriticalStr().length()) << setfill(' ') << "|\n\n";
        }
    }

    void chooseFighter(const vector<unique_ptr<Fighter>>& f, int fightersPerRow, int option){
        
        writeLine("\n\n\t\t\t\t-/ CHOOSE YOUR FIGHTER \\-\n\n", WHITE, 1);
        cout << "\t"; sq(BRIGHT_GREEN); writeLine(" -- HEALTH\t", BRIGHT_WHITE, 10);
        sq(BRIGHT_RED); writeLine(" -- LIGHT ATTACK\t", BRIGHT_WHITE, 10);
        sq(RED); writeLine(" -- SPECIAL ATTCK\t", BRIGHT_WHITE, 10);
        sq(BRIGHT_YELLOW); writeLine(" -- CRIT. CHANCE\n", BRIGHT_WHITE, 10);
        
        const int columnWidth = 21;
        const int totalFighters = f.size();
        cout << "\n\t" << getAnsiCode(BRIGHT_WHITE); repeatChar('_', columnWidth * fightersPerRow); cout << "\n\n";
        
        for(int idx = 0; idx < totalFighters; idx += fightersPerRow){
            int fightersInThisRow = std::min(fightersPerRow, totalFighters - idx);
            cout << "\t ";
            
            // Names
            for(int i = 0; i < fightersInThisRow; i++){
                string id = to_string(idx + i + 1) + ". ";
                writeColumnText(id + f[idx + i]->Name(), columnWidth, BRIGHT_WHITE, 10);
            }
            cout << "\n\t    ";
            
            // Health
            for(int i = 0; i < fightersInThisRow; i++){
                if(option == idx + i + 1) cout << getAnsiCode(BRIGHT_BLACK);
                else cout << getAnsiCode(BRIGHT_GREEN);
                cout << setw(columnWidth) << left << f[idx + i]->HealthStr();
            }
            cout << "\n\t    ";
            
            // Light Attack
            for(int i = 0; i < fightersInThisRow; i++){
                if(option == idx + i + 1) cout << getAnsiCode(BRIGHT_BLACK);
                else cout << getAnsiCode(BRIGHT_RED);
                cout << setw(columnWidth) << left << f[idx + i]->LightAttackStr();
            }
            cout << "\n\t    ";
            
            // Special Attack
            for(int i = 0; i < fightersInThisRow; i++){
                if(option == idx + i + 1) cout << getAnsiCode(BRIGHT_BLACK);
                else cout << getAnsiCode(RED);
                cout << setw(columnWidth) << left << f[idx + i]->SpecialAttackStr();
            }
            cout << "\n\t    ";
            
            // Crit
            for(int i = 0; i < fightersInThisRow; i++){
                if(option == idx + i + 1) cout << getAnsiCode(BRIGHT_BLACK);
                else cout << getAnsiCode(BRIGHT_YELLOW);
                cout << setw(columnWidth) << left << f[idx + i]->CriticalStr();
            }
            cout << "\n\t" << getAnsiCode(BRIGHT_WHITE); repeatChar('_', columnWidth * fightersPerRow); cout << "\n\n";
        }
        reset();
    }

    // ---[BATTLE HUD]---

    void fightInfoBar(const Fighter& f1, const Fighter& f2){
    	cout << getAnsiCode(BRIGHT_BLACK) << "\n\n\t============================================================\n\t|"
    	<< getAnsiCode(BRIGHT_YELLOW) <<            "        [PLAYER I]                     [PLAYER II]        " << getAnsiCode(BRIGHT_BLACK) << "|\n\t|" 
    	<< getAnsiCode(BRIGHT_WHITE)  <<            "        " << f1.Name() << setw(35-f1.Name().length()) << setfill(' ') << f2.Name() <<  setw(24-f2.Name().length()) 
	    << getAnsiCode(BRIGHT_BLACK)  << "|\n\t|"<< "        "<< getAnsiCode(BRIGHT_GREEN) << f1.HealthStr() << setw(37-f1.HealthStr().length()) << setfill(' ') << f2.HealthStr() <<  setw(24-f2.HealthStr().length()) 
	    << getAnsiCode(BRIGHT_BLACK)  << "|\n\t============================================================\n\n" << getAnsiCode(WHITE);
	}
	
    string nameLabel(const string& name) {
        char last = tolower(name.back());
        if (last == 's')
            return "[" + name + "' TURN]";
        return "[" + name + "'s TURN]";
    }
    
    void fightTurnBar(const Fighter& f){
    	writeLine("\t" + nameLabel(f.Name()) + "\n", BRIGHT_YELLOW, 30);
	}
	
    void fightOptionBar(const Fighter& f){
 	    writeLine("\tChoose Your Attack: \n\t", BRIGHT_WHITE, 20);
        writeLine("[", BRIGHT_BLACK, 20); writeLine("1", BRIGHT_RED, 20); writeLine("]--- Light Attack(",BRIGHT_BLACK, 20);	
        writeLine(f.LightAttackStr(), BRIGHT_RED, 20); writeLine(")           [", BRIGHT_BLACK, 20);
        writeLine("2", RED, 20); writeLine("]--- Special Attack(",BRIGHT_BLACK, 20);

        if(!f.FlagSpecial()) writeLine(f.SpecialAttackStr(), RED, 20);
         else writeLine("USED", BRIGHT_WHITE, 20); writeLine(")", BRIGHT_BLACK, 20);

	    cout << "\n\t-------------------------------------------------------------------\n";
    }

    void fightAttackBar(const Fighter& f1, const Fighter& f2, AttackType a){
        switch(a){
            case AttackType::LIGHT:
                writeLine(f1.Name(), BRIGHT_WHITE, 20); 
                writeLine(" hits ", BRIGHT_BLACK, 20);
                writeLine(f2.Name(), BRIGHT_WHITE, 20); 
                writeLine(" with a light strike!  (", BRIGHT_BLACK, 20);
                writeLine(f1.LightAttackStr(), BRIGHT_RED, 20);
                writeLine(")", BRIGHT_BLACK, 20);
                break;
                
            case AttackType::SPECIAL:
                writeLine(f1.Name(), BRIGHT_WHITE, 20); 
                writeLine(" unleashed a devastating special strike on ", BRIGHT_BLACK, 20);
                writeLine(f2.Name(), BRIGHT_WHITE, 20); 
                writeLine("  (", BRIGHT_BLACK, 20);
                writeLine(f1.SpecialAttackStr(), RED, 20);
                writeLine(")", BRIGHT_BLACK, 20);
                break;
            
            case AttackType::CRITICAL:
                writeLine("\033[5mCRITICAL DAMAGE! \033[0m", BRIGHT_YELLOW, 20);
                writeLine(f1.Name(), BRIGHT_WHITE, 20);
                writeLine("  strikes ", BRIGHT_BLACK, 20);
                writeLine(f2.Name(), BRIGHT_WHITE, 20);
                writeLine(" at their weak point!  (", BRIGHT_BLACK, 20);
                writeLine(to_string(f1.LightAttack() * 2) + "ATK", BRIGHT_YELLOW, 20);
                writeLine(")", BRIGHT_BLACK, 20);    
                break; 
        }
        wait(2);
    }

    void fightWinnerBar(const Fighter& winner){
        blinking("\t***[ WINNER IS \033[97m" + winner.Name() +"\033[36m ]***", CYAN, 300, 6);
    }

    // ---[ OPTION BOX]---

    uint8_t optionBox(FormContext m, int limit){
        int choice; 
        do {
            writeLine("\033[4mOPTION\033[0m: ", YELLOW, 0);
            cin >> choice;
            
            if(cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                errorMessage();
                choice = 255;
                continue;
            }
            
            // Validation logic
            int valid = 255;
            switch(m){
                case FormContext::MAIN_MENU:
                    if(choice >= 0 && choice <= 5) valid = choice;
                    break;
                
                case FormContext::ONLY_BACK:
                    if(choice == 0) valid = choice;
                    break;
                
                case FormContext::PICK_FIGHTER:
                    // Limit is number of fighters
                    if(choice >= 0 && choice <= limit) valid = choice;
                    break;
                
                case FormContext::BATTLE:
                    if(choice == 1 || choice == 2) valid = choice;
                    break;
            }
            
            if(valid == 255) {
                errorMessage();
                choice = 255;
            }

        } while(choice == 255);
        
        return static_cast<uint8_t>(choice);
    }

} // namespace UI