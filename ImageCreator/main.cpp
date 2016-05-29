#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include <iostream>
using namespace std;

int Mapa[801][601];

void drawCloud(sf::Image &img)
{
    int positionX = rand() % 400 + 200;
    int positionY = rand() % 200 + 400;
    int startX = positionX;
    int startY = positionY;

    img.setPixel(positionX, positionY, sf::Color::White);
    Mapa[positionX][positionY] = 1;
    int cloudSize = rand() % 400 + 300;
    for(int i = 0; i< 150000; i++)
    {
        bool is = true;
        int direction = rand() % 4;

        if(direction == 0)
        {
            if(startY + 50 > positionY + 1)
            {
                positionY++;
            }
            else
            {
                is = false;
            }
        }
        else if(direction == 1)
        {
            if(startY - 50 < positionY + 1)
            {
                positionY--;
            }
            else
            {
                is = false;
            }
        }
        else if(direction == 2)
        {
            if(startX + 100 > positionX + 1)
            {
                positionX++;
            }
            else
            {
                is = false;
            }
        }
        else if(direction == 3)
        {
            if(startX - 100 < positionX + 1)
            {
                positionX--;
            }
            else
            {
                is = false;
            }
        }
        if(is == true)
        {
        Mapa[positionX][positionY] = 1;
        img.setPixel(positionX, positionY, sf::Color::White);

        img.setPixel(positionX - 1, positionY, sf::Color::White);
        img.setPixel(positionX + 1, positionY, sf::Color::White);
        img.setPixel(positionX, positionY - 1, sf::Color::White);
        img.setPixel(positionX, positionY + 1, sf::Color::White);

        Mapa[positionX - 1][positionY] = 1;
        Mapa[positionX + 1][positionY] = 1;
        Mapa[positionX][positionY - 1] = 1;
        Mapa[positionX][positionY + 1] = 1;
        }
    }
}


int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");
    srand(time(NULL));
    sf::Image img;
    img.create(800, 600, sf::Color::Black);



    for(int i = 0; i < 800; i++)
    {
        for(int j = 0; j < 600; j++)
        {
            Mapa[i][j] = 0;
        }
    }

    int punktX = rand() % 801;
    int punktY = rand() % 601;

    cout << "Poczatkowe ustalenia: " << endl;
    cout << "x = " << punktX << endl << "y = " << punktY << endl;
    Mapa[punktX][punktY] = 1;
    int iloscPixeli = rand() & 501 + 100;
    cout << "Ilosc pixeli: " << iloscPixeli << endl;

    int tempx, tempy;
    tempx = punktX;
    tempy = punktY;
    img.setPixel(tempx,tempy,sf::Color(125,125,125));//255 255 224
    int r = 125;
    int g = 125;
    int b = 125;
    int liczbaPokolorowanych = 1;




/*
    for(int i = 0; i < 100000; i++)
    {
        int newX = rand() % 3;
        int newY = rand() % 3;
        int newColorR = rand() % 3;
        int newColorG = rand() % 3;
        int newColorB = rand() % 3;
        if(((tempx - 1 + newX) >= 0) && ((tempx - 1 + newX) <= 799) && ((tempy - 1 + newY) >= 0) && ((tempy - 1 + newY) <= 599))
        {

            tempx = tempx - 1 + newX;
            tempy = tempy - 1 + newY;

            Mapa[tempx][tempy] = 1;
            r = r - 1 + newColorR;
            g = g - 1 + newColorG;
            b = b - 1 + newColorB;
            if(r > 255) r = 255;
            if(r < 0) r = 0;
            if(g > 255) g = 255;
            if(g < 0) g = 0;
            if(b > 255) b = 255;
            if(b < 0) b = 0;
            //cout << r << " "<< g << " " << b << " ";

            img.setPixel(tempx, tempy, sf::Color(r, g, b));


        }

    }
*/

    drawCloud(img);
    cout << "Done, new image is created." << endl;

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
        }

        // Clear screen
        app.clear();

        // Update the window
        app.display();
    }
    img.saveToFile("new.png");


    return EXIT_SUCCESS;
}
