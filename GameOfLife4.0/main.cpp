#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>	
#include <time.h>
#include <windows.h>
#include <string.h>
#include <cstdlib>
#include <cstring>


const int width = 1440; //1280 sf::VideoMode::getDesktopMode().height;
const int height = 900; //960 Musze zrobic tablice dynamicznie
const int rozmiarX = 12;
const int rozmiarY = 12;

using namespace std;

int losuj(int poczatek, int koniec)
{
    return rand() % koniec + poczatek;
}

class Bakteria
{
    protected:
    int _x;
    int _y;
    bool _czyMartwa;
    int _znak;

    public:
    Bakteria();
    Bakteria(int x, int y);

    //METODY
    int podajX();
    int podajY();
    bool czyZyje();
    int podajZnak();

};

Bakteria::Bakteria() : _x(losuj(1,width / rozmiarX -1)), _y(losuj(1,height / rozmiarY -1)), _czyMartwa(false), _znak(1){}

Bakteria::Bakteria(int x, int y) : _x(x), _y(y), _czyMartwa(false), _znak(1){}

//METODY

int Bakteria::podajX()
{
    return _x;
}

int Bakteria::podajY()
{
    return _y;
}

bool Bakteria::czyZyje()
{
    return !_czyMartwa;
}

int Bakteria::podajZnak()
{
    return _znak;
}

int mapa[width / rozmiarX][height / rozmiarY];
int mapaTemp[width / rozmiarX][height / rozmiarY];

void rysujMape()
{
    for(int i = 1; i < 40; i++)
    {
        for(int k = 1; k < 40; k++)
        {
            cout << mapa[i][k];
        }
        cout << endl;
    }
}

void initMap()
{
    for(int i = 0; i < width / rozmiarX; i++)
    {
        for(int k = 0; k < height / rozmiarY; k++)
        {
            mapa[i][k] = 0;
        }
    }
}


void copy(int array1[width / rozmiarX][height / rozmiarY], int array2[width / rozmiarX][height / rozmiarY])
{
  for(int j = 0; j < width / rozmiarX; j++)
  {
		for(int i = 0; i < height / rozmiarY; i++)
			array2[j][i] = array1[j][i];
	}
}


int main()
{




    int randomize;
    string LiveGenerator;
    string DeadGenerator;
    cout << "GAME OF LIFE" << endl;
    cout << "HOW MANY RANDOMIZE?" << endl;
    cin >> randomize;
    cout << "Set the generator for Living: ";
    cin >> LiveGenerator;
    cout << "Set the generator for Dying: ";
    cin >> DeadGenerator;

    int *LiveTab = new int [LiveGenerator.length()];
    for(int i = 0; i < LiveGenerator.length(); i++)
    {
        char x = LiveGenerator[i];
        LiveTab[i] = atoi(&x);
        cout << LiveTab[i] << " ";
    }
    cout << endl;
    int *DeadTab = new int [DeadGenerator.length()];
    for(int i = 0; i < DeadGenerator.length(); i++)
    {

        char y = DeadGenerator[i];
        DeadTab[i] = y - '0';
        cout << DeadTab[i] << " ";
    }


    srand (time(NULL));
    initMap();
    for(int i = 0; i < randomize; i++)
    {
        Bakteria *temp = new Bakteria;
        mapa[temp->podajX()][temp->podajY()] = temp->podajZnak();
    }





    // Create the main window
    sf::RenderWindow app(sf::VideoMode::getDesktopMode(), "GameOfLife", sf::Style::Fullscreen);

    sf::Image blueImg;
    blueImg.loadFromFile("blue.png");
    sf::Texture blueTex;
    blueTex.loadFromImage(blueImg);


    app.display();
    // Load a sprite to display

	
	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                app.close();
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(app);
                sf::Vector2f worldPos = app.mapPixelToCoords(pixelPos);
                if(event.mouseWheel.delta == 1)
                {
                sf::View view = app.getDefaultView();
                view.zoom(0.5f);
                view.setCenter(0, 0);
                view.move(worldPos.x, worldPos.y);
                app.setView(view);
                }
                else
                {
                sf::View view = app.getDefaultView();
                view.zoom(1.0f);
                app.setView(view);
                }
            }

        }

        //MAGIA

        //system("cls");
        Sleep(20);
        for(int i = 1; i < width / rozmiarX - 1; i++)
        {
            for(int k = 1; k < height / rozmiarY - 1; k++)
            {
                    int licznik = 0;
                    licznik = mapa[i-1][k] +
					mapa[i-1][k-1] +
					mapa[i][k-1] +
					mapa[i+1][k-1] +
					mapa[i+1][k] +
					mapa[i+1][k+1] +
					mapa[i][k+1] +
					mapa[i-1][k+1];
                    if(mapa[i][k] == 1)
                    {
                        bool isDone = false;
                        for(int z = 0; z < LiveGenerator.length(); z++)
                        {
                            if(licznik == LiveTab[z])
                            {
                                mapaTemp[i][k] = 1;
                                isDone = true;
                                break;
                            }
                        }

                       if(!isDone)
                       {
                            mapaTemp[i][k] = 0;
                       }

                    }
                    else if(mapa[i][k] == 0)
                    {
                        bool isDone = false;
                        for(int z = 0; z < DeadGenerator.length(); z++)
                        {
                            if(licznik == DeadTab[z])
                            {
                                mapaTemp[i][k] = 1;
                                isDone = true;
                                break;
                            }

                        }
                        if(!isDone)
                        {
                            mapaTemp[i][k] =  0;
                        }

                    }
            }

        }
        copy(mapaTemp, mapa);


        // rysujMape();




        // Clear screen
        app.clear(sf::Color(56,43,20));


        for(int p = 1; p < width / rozmiarX - 1; p++)
        {
            for(int o = 1; o < height / rozmiarY - 1; o++)
            {
                if(mapa[p][o] == 1)
                {

                    sf::RectangleShape rectangle;
                    rectangle.setSize(sf::Vector2f(rozmiarX, rozmiarY));
                    rectangle.setOutlineColor(sf::Color(174,18,21)); // Color
                    rectangle.setFillColor(sf::Color(240,210,11)); // Color 151,204,238
                    rectangle.setOutlineThickness(0);
                    rectangle.setPosition(p * rozmiarX, o * rozmiarY);
                    app.draw(rectangle);


                    /*
                    sf::Sprite blueSprt;
                    blueSprt.setTexture(blueTex);
                    blueSprt.setPosition(p * rozmiarX, o * rozmiarY);
                    app.draw(blueSprt);
                    */

                    /*
                    sf::CircleShape circle;
                    circle.setFillColor(sf::Color::Blue);
                    circle.setRadius(rozmiarX/2);
                    circle.setPosition(p * rozmiarX, o * rozmiarY);
                    app.draw(circle); */

                }
            }
        }


        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
