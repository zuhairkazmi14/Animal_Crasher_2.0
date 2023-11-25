#include <iostream>
#include <String>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace sf;
using namespace std;

#pragma warning(disable : 4996)
/*
Group Members 
///////////////////////////////////////////////////////////////////////////
1. Zuhair Kazmi/////////////////////Defining overAll concept and  Structure of the game
2. Abdul Rehman//////////////////// Woking with Game Event part
3. Katrina Bodani//////////////////Similarity Funtcions
4. Ishtiaq Hussain/////////////////Screen Update Function
///////////////////////////////////////////////////////////////////////////
*/






//Global Variables....

int tile_size = 54;
Vector2i offset(70, 70), position;

bool is_swaped = false, moving = false;
int x_0, y_0, x, y, clk_count = 0, score_points = 0;
int points = 0,Level=1;
///Event Variable

///Rendering Window();
RenderWindow app(VideoMode(740, 480), "Animal Crasher");

/// Defining a structure....for image representation
struct animal {
    int  x, y, col, row, species, same, tra_fade;
    animal()
    {
        same = 0;
        tra_fade = 255;
    }
}grid[7][7];
///Functions Header
void Menu(Sprite Main_menu);
void swaping(animal a1, animal a2);
void positioning();
void GameEvent();
void GameDraw(Sprite background, Sprite wild);
void animations();
void Similar();
void animation_delete();
void Update();
void Score();
void bg_music(Music &bg_Music);
void timer(int seconds);
int main()
{
    srand(time(0));
    /// Redering window.....
    app.setFramerateLimit(60);
    //.... Setting Framesrates

    //... Defining textures for screen objects
    Texture t1, t2, menu;
    t1.loadFromFile("sprites/level_bg.png");
    t2.loadFromFile("sprites/animal.png");
    menu.loadFromFile("sprites/menu.png");

    ///Constructing the sprite from a source texture
    Sprite background(t1), wild(t2), main_menu(menu);
    
    
    
    Music bgMusic;
    
    if(!bgMusic.openFromFile("Audio/backgroun_Music.ogg"))cout<<"File not found";
    bg_music(bgMusic);
    /*bgMusic.setVolume(20);
    bgMusic.play();
    bgMusic.setLoop(true);*/
    /// Definig the layout and position of the sprites
    positioning();
    
    while (app.isOpen())
    {
        //
        
       
        
      
        
        //Menu( main_menu);
       
       GameEvent();
      // 
       

        ///////////

        Similar();
        ///////////////
        ////// Animation for motion of tiles
        animations();
        ///////////////////////////
        animation_delete();
        /////////////
        Score();

        
        /////////

        Update();

        //////TO Draw/////
        

      

        
       GameDraw(background, wild);

    }
    return 0;
}
//Main Menu
void Menu(Sprite Main_menu)
{
    /*while (app.pollEvent(e))
    {
    if
    
    
    
    
    }*/
    Vector2f size_b(190, 50);
    app.draw(Main_menu);
    RectangleShape button1;
    button1.setFillColor(Color(0, 0, 0, 0));
    button1.setPosition(280,240);
    button1.setSize(size_b);
    app.draw(button1);

    Font font;
    if (!font.loadFromFile("Fonts/KGW.ttf")) { cout << "Font not found"; }
    Text NewGame,Options,Exit;
    
    NewGame.setString("NEW GAME");
    NewGame.setFont(font);
    NewGame.setPosition(300,250);
    NewGame.setColor(Color::Cyan);
    NewGame.setCharacterSize(25);
    app.draw(NewGame);
    Options.setString("Options");
    Options.setFont(font);
    Options.setPosition(310, 330);
    Options.setCharacterSize(25);
    Options.setColor(Color::Cyan);
    app.draw(Options);
    Exit.setString("Exit");
    Exit.setFont(font);
    Exit.setPosition(330, 405);
    Exit.setCharacterSize(25);
    Exit.setColor(Color::Cyan);
    app.draw(Exit);
    app.display();
    



}
/// Swaping function
void swaping(animal a1, animal a2)
{
    //swap(a1.col, a2.col);
    //swap(a1.row, a2.row);
    int temp;
    temp = a1.row;
    a1.row = a2.row;//swaped value for row
    a2.row = temp;//swaped value for row
    temp = 0;
    temp = a1.col;
    a1.col = a2.col;//swaped value for column
    a2.col = temp;//swaped value for column

    grid[a1.row][a1.col] = a1;
    grid[a2.row][a2.col] = a2;

}
//Positoning of objects;
void positioning()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            grid[i][j].species = rand() % 6;
            grid[i][j].col = j;
            grid[i][j].row = i;
            grid[i][j].x = (j)*tile_size;
            grid[i][j].y = (i+1) * tile_size;
        }
    }

}
//Background Music
void bg_music(Music &bgMusic) 
{
    
    
    bgMusic.setVolume(20);
    bgMusic.play();
    bgMusic.setLoop(true);


}
///Events of the Game
void GameEvent()
{
    Event e;

  
    //String playerInput;
    //Text playerText;

   

        
    while (app.pollEvent(e))
    {
        if (e.type == Event::Closed) app.close();
        /* if (e.type == sf::Event::TextEntered)
         {
             playerInput += e.text.unicode;
             playerText.setString(playerInput);
         }
         app.draw(playerText);
         */
        
            if (e.type == Event::MouseButtonPressed)
            {

                if (e.key.code == Mouse::Left)
                {
                    if (!is_swaped && !moving)
                    {
                        clk_count++;
                    }
                    position = Mouse::getPosition(app) - offset;
                }
            }
    
    }
        if (clk_count == 1)
        {
            x_0 = position.x / tile_size + 1;
            y_0 = position.y / tile_size + 1;
        }
        if (clk_count == 2)
        {
            x = position.x / tile_size + 1;
            y = position.y / tile_size + 1;
            if (abs(x - x_0) + abs(y - y_0) == 1)
            {
                swaping(grid[y_0][x_0], grid[y][x]);
                is_swaped = true;
                clk_count = 0;
            }
            else
            {
                clk_count = 1;
            }
        }

    


}
///Function that draws objects on the Screen
void GameDraw(Sprite background, Sprite wild)
{
    app.draw(background);
    Font font;
    if (!font.loadFromFile("Fonts/KGW.ttf")) { cout << "Font not found"; }
    Text Level_no, Scores,timeValue,txt_Score,txt_timeValue;
    if (Level == 1)
        Level_no.setString("LEVEL 1");
    if (Level == 2)
        Level_no.setString("LEVEL 2");

    Level_no.setFont(font);
    Level_no.setPosition(570, 125);
    Level_no.setColor(Color::Cyan);
    Level_no.setCharacterSize(32);
    app.draw(Level_no);
    ///Score Count
    string Points = to_string(points);
    Scores.setString(Points);
    Scores.setFont(font);
    Scores.setPosition(545, 380);
    Scores.setColor(Color::Cyan);
    Scores.setCharacterSize(21);
    app.draw(Scores);
    //Score Text
    txt_Score.setString("Score");
    txt_Score.setFont(font);
    txt_Score.setPosition(530, 432);
    txt_Score.setColor(Color::Cyan);
    txt_Score.setCharacterSize(25);
    app.draw(txt_Score);
    ///Timer for Level 2:
    Clock clock;
    Time timer;
    timer = clock.restart();
    int v_time = int(timer.asSeconds()*100+1)*120;
    String stime=to_string(v_time);
    txt_timeValue.setString(stime);
    txt_timeValue.setFont(font);
    txt_timeValue.setPosition(655, 375);
    txt_timeValue.setColor(Color::Cyan);
    txt_timeValue.setCharacterSize(23);
    app.draw(txt_timeValue);
    //timer Text
    Scores.setString("Timer");
    Scores.setFont(font);
    Scores.setPosition(635, 430);
    Scores.setColor(Color::Cyan);
    Scores.setCharacterSize(25);
    app.draw(Scores);
   /* if (Level == 2) 
    {
        for (int i = 0; i < 120; i++)
        {
            time = time - i;
            
        }
    
    }*/

    for (int i = 0; i <= 6; i++)
    {
        for (int j = 0; j <= 6; j++)
        {

            
            animal a = grid[i][j];
            wild.setTextureRect(IntRect(a.species * 49, 0, 49, 49));
            wild.setColor(Color(255, 255, 255, a.tra_fade));
            wild.setPosition(a.x, a.y);
            wild.move(offset.x - tile_size, offset.y - tile_size);
            app.draw(wild);
        }
        

    }
    app.display();

}
//Timer Function
void timer(int seconds) 
{
    for (;;) 
    {
        
        seconds--;
        //Sleep(1000);
        if (seconds == 0)
        {
            break;
        }
        
    }



}


///Animations Funtion
void animations()
{
    moving = false;
    for (int i = 0; i <= 6; i++)
    {
        for (int j = 0; j <= 6; j++)
        {
            animal &a = grid[i][j];
            int dir_x, dir_y;
            for (int s = 0; s < 5; s++)
            {
                dir_x = a.x - a.col * tile_size;
                dir_y = a.y - a.row * tile_size;

                if (dir_x)
                    a.x -= dir_x / abs(dir_x);
                if (dir_y)
                    a.y -= dir_y / abs(dir_y);
                
            }
            if (dir_x || dir_y)
            {
                moving = true;
            }
        }
        

    }
   

}
///Finding similar Tiles....
void Similar()
{
    for (int i = 0; i <= 6; i++)
    {
        for (int j = 0; j <= 6; j++)
        {
            if (grid[i][j].species == grid[i + 1][j].species)
            {
                if (grid[i][j].species == grid[i - 1][j].species)
                {
                    for (int k = -1; k <= 1; k++)
                    {
                        grid[i + k][j].same++;
                        

                    }
                }
            }
            ///For column Match.....
            if (grid[i][j].species == grid[i][j + 1].species)
            {
                if (grid[i][j].species == grid[i][j - 1].species)
                {
                    for (int k = -1; k <= 1; k++)
                    {
                        grid[i][j + k].same++;
                        
                    }
                }
            }
        }

    }




}
///deleting the matched species
void animation_delete()
{
    if (!moving)
    {
        for (int i = 0; i <= 6; i++)
        {
            for (int j = 0; j <= 6; j++)
            {
                if (grid[i][j].same)
                {
                    if (grid[i][j].tra_fade > 10)
                    {
                        grid[i][j].tra_fade -= 10;
                        moving = true;
                    }
                }
            }
        }
    }





}
///Score count
void Score()
{
    
    score_points = 0;
    for (int i = 0; i <= 6; i++)
    {
        for (int j = 0; j <= 6; j++)
        {
            score_points += grid[i][j].same;
            cout<< grid[i][j].species<<endl<<score_points;
            if (grid[i][j].same > 0) {
                if (grid[i][j].species == 0)
                {

                    points += 30;
                }
                if (grid[i][j].species == 1)
                {

                    points +=60;
                }
                if (grid[i][j].species == 2)
                {

                    points +=  70;
                }
                if (grid[i][j].species == 3)
                {

                    points +=  20;
                }
                if (grid[i][j].species == 4)
                {

                    points +=  50;
                }
                if (grid[i][j].species == 5)
                {

                    points += 90;
                }
                if (grid[i][j].species == 6)
                {

                    points +=  100;
                }
            }
    
        }

       
    }

    ///Swaping when match is not found
    if (is_swaped && !moving)
    {
        if (!score_points)
        {
            swaping(grid[y_0][x_0], grid[y][x]);
            is_swaped = false;
        }
    }
    if (Level == 1 && points > 70000) 
    {
        Level = 2;
        points = 0;
        app.clear();
    
    }


}
///updating screen....
void Update()
{
    if (!moving) {
        for (int i = 6; i >= 0; i--)
        {
            for (int j = 0; j <= 6; j++)
            {
                if (grid[i][j].same)
                {
                    for (int l = i; l > 0; l--)
                    {
                        if (!grid[l][j].same)
                        {
                            swaping(grid[l][j], grid[i][j]);
                            break;
                        }
                    }
                }
            }
        }


        for (int j = 0; j <= 6; j++)
        {
            for (int i = 6, r = 0; i >=0 ; i--)
            {
                if (grid[i][j].same)
                {
                    grid[i][j].species = rand() % 7;
                    grid[i][j].y = -tile_size * r++;
                    grid[i][j].same = 0;
                    grid[i][j].tra_fade = 255;
                }
            }
        }

    }
}


