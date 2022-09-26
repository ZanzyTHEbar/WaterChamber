#include <RTClib.h>

#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 8

DHT dht(DHTPIN, DHT22);
RTC_DS1307 rtc;
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);

boolean pumping = false;

const int PUMP = 10;
const int PUMP_ACTIVE = 10;
const int PUMP_WAIT = 60 * 60;

int ledStatus = LOW;
int ledTimer = 5000;
int timer = 0;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PUMP, OUTPUT);

    dht.begin();

    rtc.begin();
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    lcd.begin(16, 2);
}

String displayCountdown()
{
    if (timer < 1 && pumping == true)
    {
        digitalWrite(PUMP, HIGH);
        timer = PUMP_WAIT;
        pumping = false;
        lcd.begin(16, 2);
    }
    else if (timer < 1 && pumping == false)
    {
        digitalWrite(PUMP, LOW);
        timer = PUMP_ACTIVE;
        pumping = true;
        lcd.begin(16, 2);
    }
    else
    {
        timer -= 1;
    }

    String timerDisplay = "";
    if (timer < 60)
    {
        timerDisplay = String(timer) + " sec";
    }
    else
    {
        int displayMinute = timer / 60;
        timerDisplay = String(displayMinute) + " min";
    }
    return String(padFront(timerDisplay, 10));
}

String formatTemp(int humidity, float temperature)
{

    int hic = dht.computeHeatIndex(temperature, humidity, false);
    if (isnan(humidity) || isnan(temperature) || isnan(hic))
    {
        return "Temp read error";
    }

    return padBack("Hum: " + String(humidity) + ", " + String(hic) + "C", 3);
}

String formatTime(DateTime now)
{
    String timeString = "";

    int hour = now.hour();
    if (hour < 10)
    {
        timeString += "0";
    }
    timeString += String(hour) + ":";

    int minute = now.minute();
    if (minute < 10)
    {
        timeString += "0";
    }
    timeString += String(minute) + " ";

    return timeString;
}

String padBack(String input, int padding)
{
    String output = input;
    for (int i = 0; i < padding; i++)
    {
        output += " ";
    }
    return output;
}

String padFront(String input, int length)
{
    String output = input;
    for (int i = 0; i < length - input.length(); i++)
    {
        output = " " + output;
    }
    return output;
}

void loop()
{
    int h = dht.readHumidity();
    float t = dht.readTemperature();

    DateTime now = rtc.now();

    lcd.setCursor(0, 0);
    lcd.print(formatTime(now));
    lcd.setCursor(6, 0);
    lcd.print(displayCountdown());
    lcd.setCursor(1, 1);
    lcd.print(formatTemp(h, t));

    delay(1000);
}