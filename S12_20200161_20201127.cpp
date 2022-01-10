//Hussien Mostafa - 20200161 || Amr Riyad - 20201127 || S11-S12
#include <iostream>
#include <windows.h>

using namespace std;

void SetColor(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
//The required class.
class ColoredBox{
private:
    //The box itself 2D dynamic array, its character, and its dimensions as well as color.
    char **box;
    char c;
    int length, width, color = 15;
    static int maxArea;
public:
    //Paramterized constructor that takes the length and width of the box and builds the box.
    ColoredBox(int l, int w): length(l), width(w){

        box = new char*[length];
        for(int i = 0; i < length; i++) box[i] = new char[width];

        for(int i = 0; i < length; i++)
            for(int j = 0; j < width; j++)
                box[i][j] = '#';

        if(length * width > maxArea) maxArea = length * width;
    }

    //a constructor that takes all the characteristics of the box and builds it.
    ColoredBox(int l, int w, int col, char boxChar): length(l), width(w), color(col), c(boxChar){

        box = new char *[length];
        for(int i = 0; i < length; i++) box[i] = new char[width];

        for(int i = 0; i < length; i++)
            for (int j = 0; j < width; j++)
                box[i][j] = c;

        if(length * width > maxArea) maxArea = length * width;
    }

    //the following are mutators and accessors for each attribute of the box. 
    void setColor(int col){
        color = col;
    }
    int getColor() const {
        return color;
    }
    int getArea(){
        return length * width;
    }
    static int getMaxArea(){
        return maxArea;
    }
    char getCharacter() const{
        return c;
    }
    void setCharacter(char ch){
        c = ch;
        for(int i = 0; i < length; i++)
            for(int j = 0; j < width; j++)
                box[i][j] = ch;
    }

    //a member function that displays the box.
    void display(){
        SetColor(color);
        for(int i = 0; i < length; i++) {
            for(int j = 0; j < width; j++) {
                cout << box[i][j];
            }
            cout << "\n";
        }
        SetColor(15);
    }

    //a member function that displays the box but transposed.
    void displayTransposed(){
        SetColor(color);
        for(int i = 0; i < width; i++){
            for(int j = 0; j < length; j++){
                cout << box[j][i];
            }
            cout << "\n";
        }
        SetColor(15);
    }

    //a member function that displays the box wider by adding a space after each print.
    void displayWider(){
        SetColor(color);
        for (int i = 0; i < length; i++){
            for (int j = 0; j < width; j++){
                cout << box[i][j] << " ";
            }
            cout << "\n";
        }
        SetColor(15);
    }

    //a member function that displays the box like a chess board.
    void displayChess(int boxColor){
        for (int i = 0; i < length; i++){
            for (int j = 0; j < width; j++){
                if ((i + j) % 2 == 0) {
                    SetColor(color);
                    cout << box[i][j];
                } else {
                    SetColor(boxColor);
                    cout << box[i][j];
                }
            }
            cout << "\n";
        }
        SetColor(15);
    }

    //the requried destructor to free the allocated memory. 
    ~ColoredBox(){
        for (int i = 0; i < length; i++)
            delete[] box[i];
        delete[] box;
    }
};

//initializing the static member max area which stores the area of the largest box. 
int ColoredBox::maxArea = 0;

int main()
{
    int len,wid,col,col2;
    char boxChar;
    cout<<"Enter length and width of the box separated by a space: ";
    cin>>len>>wid;
    ColoredBox* cb1;
    cb1 = new ColoredBox(len,wid);
    cb1->display();
    cout<<"Set the box to another color: ";
    cin>>col;
    cb1->setColor(col);
    cout<<"Displaying Transposed: "<<endl;
    cb1->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb1->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb1->displayChess(col2);
    cout<<endl<<"Area="<<cb1->getArea();
    cout<<endl<<"Max Area="<<cb1->getMaxArea();
    delete cb1;

    cout<<"Enter length,width,color,character of the box separated by spaces: ";
    cin>>len>>wid>>col>>boxChar;
    ColoredBox* cb2;
    cb2 = new ColoredBox(len,wid,col,boxChar);
    cb2->display();
    cout<<"Displaying Transposed: "<<endl;
    cb2->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb2->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb2->displayChess(col2);
    cout<<"Displaying original again:"<<endl;
    cb2->display();
    cout<<endl<<"Area="<<cb2->getArea();
    cout<<endl<<"Max Area="<<cb2->getMaxArea();
    delete cb2;
    return 0;
}