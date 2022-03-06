#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

int max_fails = 7;

string WORD_LIST[] = {
        "angle", "ant", "apple", "arch", "arm", "army",
        "baby", "bag", "ball", "band", "basin", "basket", "bath", "bed", "bee", "bell", "berry",
        "bird", "blade", "board", "boat", "bone", "book", "boot", "bottle", "box", "boy",
        "brain", "brake", "branch", "brick", "bridge", "brush", "bucket", "bulb", "button",
        "cake", "camera", "card",  "cart", "carriage", "cat", "chain", "cheese", "chest",
        "chin", "church", "circle", "clock", "cloud", "coat", "collar", "comb", "cord",
        "cow", "cup", "curtain", "cushion",
        "dog", "door", "drain", "drawer", "dress", "drop", "ear", "egg", "engine", "eye",
        "face", "farm", "feather", "finger", "fish", "flag", "floor", "fly",
        "foot", "fork", "fowl", "frame", "garden", "girl", "glove", "goat", "gun",
        "hair", "hammer", "hand", "hat", "head", "heart", "hook", "horn", "horse",
        "hospital", "house", "island", "jewel",  "kettle", "key", "knee", "knife", "knot",
        "leaf", "leg", "library", "line", "lip", "lock",
        "map", "match", "monkey", "moon", "mouth", "muscle",
        "nail", "neck", "needle", "nerve", "net", "nose", "nut",
        "office", "orange", "oven", "parcel", "pen", "pencil", "picture", "pig", "pin",
        "pipe", "plane", "plate", "plow", "pocket", "pot", "potato", "prison", "pump",
        "rail", "rat", "receipt", "ring", "rod", "roof", "root",
        "sail", "school", "scissors", "screw", "seed", "sheep", "shelf", "ship", "shirt",
        "shoe", "skin", "skirt", "snake", "sock", "spade", "sponge", "spoon", "spring",
        "square", "stamp", "star", "station", "stem", "stick", "stocking", "stomach",
        "store", "street", "sun", "table", "tail", "thread", "throat", "thumb", "ticket",
        "toe", "tongue", "tooth", "town", "train", "tray", "tree", "trousers", "umbrella",
        "wall", "watch", "wheel", "whip", "whistle", "window", "wire", "wing", "worm",
    };

const string FIGURE[] = {
         "   -------------    \n"
         "   |                \n"
         "   |                \n"
         "   |                \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |                \n"
         "   |                \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |                \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |           |    \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|    \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|\\  \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|\\  \n"
         "   |          /     \n"
         "   |     \n"
         " -----   \n",

         "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|\\  \n"
         "   |          / \\  \n"
         "   |     \n"
         " -----   \n",
};


string get_word(){
    srand(time(NULL));
    int x = rand() % 100 + 1;
    return WORD_LIST[x];
}

void display(string word, string guess, int count_mistake){
    cout << FIGURE[count_mistake];
    cout << guess << endl;
    cout << "you made " << count_mistake << " mistakes" << endl;
}

char get_guess(){
    char a;
    cin >> a;
    return a;
}

void check_character(string word, string &guess, char input, int &count_mistake){
    bool c = false;
    for(int i = 0; i < word.length(); i++){
        if(word[i] == input){
            guess[i] = input;
            c = true;
        }
    }
    if(c == false){
        count_mistake++;
    }
}

bool game_over(string word, string guess, int count_mistake){
    if(word == guess || count_mistake == max_fails){
        return true;
    }
}

void showResult(string word, string guess, int count_mistake){
    if(guess == word){
        cout << FIGURE[count_mistake];
        cout << "congrats" << endl;
    }else{
        cout << "You lost" << endl;
        cout << "The word was " << word << endl;
    }
}

int main(){
    string word = get_word();
    string guess;
    int count_mistake = 0;
    guess = string(word.length(), '-');
    do{
        display(word, guess, count_mistake);
        char input = get_guess();
        check_character(word, guess, input, count_mistake);
    }while(!game_over(word, guess, count_mistake));

    showResult(word, guess, count_mistake);

    return 0;
}
