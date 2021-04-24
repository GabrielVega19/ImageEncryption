#include "FibLFSR.h"

#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using std::string;
using std::cout;
using std:: endl;

void transform(sf::Image &image,FibLFSR &lsfr);
void alphaToBinary(string& seed);

int main (int argc, char* argv[]){
    
    //this retrieves the command line arguments 
    if (argc != 4){
        cout << "you did not pass the correct amount of arguments to run the program" << endl;
        return -1;
    }
    string inputFileName = argv[1];
    string outputFileName = argv[2];
    string seed = argv[3];

    //this sets up the lfsr
    alphaToBinary(seed);
    FibLFSR lfsr(seed);

    //this opens the image
    sf::Image image;
    if (!image.loadFromFile(inputFileName)){
        cout << "could not open the image" << inputFileName << endl;
        return -1;
    }
    
    //this sets up the origional sprite
    sf::Texture texture;
    texture.loadFromFile(inputFileName);
    sf::Sprite origionalSprite(texture);

    //sets up the encrypted sprite
    sf::Texture texture2;
    transform(image, lfsr);
    texture2.loadFromImage(image);
    sf::Sprite encryptedSprite(texture2);

    //this creats the two windows
    sf::Vector2u size = image.getSize();
    sf::RenderWindow oWindow(sf::VideoMode(size.x, size.y), "Origional Image");
    sf::RenderWindow eWindow(sf::VideoMode(size.x, size.y), "Encrypted Image");

    //this saves the encrypted image to memory
    if (!image.saveToFile(outputFileName)){
        cout << "could not save encrypted image to file" << endl;
        return -1;
    }

    //this is the main program loop that loops while the window is open 
    while (oWindow.isOpen() && eWindow.isOpen()){
        //this closes a window if a close event is detected
        sf::Event event;
        while(oWindow.pollEvent(event)){
            if (event.type == sf::Event::Closed)
				oWindow.close();
        }
        while(eWindow.pollEvent(event)){
            if (event.type == sf::Event::Closed)
				eWindow.close();
        }

        //this prints out the new frame for the windows
        oWindow.clear();
        oWindow.draw(origionalSprite);
        oWindow.display();
        eWindow.clear();
        eWindow.draw(encryptedSprite);
        eWindow.display();

    }

    return 0;
}


void transform(sf::Image& image,FibLFSR& lsfr){
    sf::Color c;
    sf::Vector2u size = image.getSize();

    for (unsigned int x = 0; x < size.x; x++){
        for (unsigned int y = 0; y < size.y; y++){
            c = image.getPixel(x, y);
            c.r ^= lsfr.generate(8);
            c.g ^= lsfr.generate(8);
            c.b ^= lsfr.generate(8);
            image.setPixel(x, y, c);
        }
    }
}

void alphaToBinary(string& seed){
    string binaryString;

    for (unsigned int i = 0; i < seed.length(); i++){
        int j = static_cast<int>(seed[i]);
        while (j != 0){
            binaryString.push_back(static_cast<char>('0' + (j % 2)));
            j /= 2;
        }
    }

    seed = binaryString;
}