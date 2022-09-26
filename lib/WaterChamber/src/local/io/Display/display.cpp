#include "display.hpp"

Display::Display() : LiquidCrystal_I2C(0x27, 16, 2), // set the LCD address to 0x27 for a 16 chars and 2 line display
                     bell{0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4},
                     note{0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0},
                     clock{0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0},
                     heart{0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0},
                     duck{0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0},
                     check{0x0, 0x1, 0x3, 0x16, 0x1c, 0x8, 0x0},
                     cross{0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0},
                     retarrow{0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4}
{
    init();
}

Display::~Display() {}

void Display::init()
{
    init();
    backlight();

    createChar(0, bell);
    createChar(1, note);
    createChar(2, clock);
    createChar(3, heart);
    createChar(4, duck);
    createChar(5, check);
    createChar(6, cross);
    createChar(7, retarrow);
    home();

    print("Hello world...");
    setCursor(0, 1);
    print(" i ");
    printByte(3);
    print(" arduinos!");
    delay(5000);
    displayKeyCodes();
}

void Display::printStr(std::string text)
{
    print(text.c_str());
}

// display all keycodes
void Display::displayKeyCodes(void)
{
    uint8_t i = 0;
    while (1)
    {
        clear();
        print("Codes 0x");
        print(i, HEX);
        print("-0x");
        print(i + 15, HEX);
        setCursor(0, 1);
        for (int j = 0; j < 16; j++)
        {
            printByte(i + j);
        }
        i += 16;
        delay(4000);
    }
}
