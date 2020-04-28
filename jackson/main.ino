/*
IEP II Project OL3
Name: main
Purpose: Operating code for Arduino interactige Back the he Future display

By Jackson Miller
04/26/2020
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "util.h"

/*  PIN DEFINITIONS
    Using preprocessor macros for pin constants instead of variables to save on memory
*/
#define redPin 9
#define greenPin 10
#define bluePin 11

#define button1 4
#define button2 3

#define knob A0
#define buzzer 2

/* GLOBALS */
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
    // Music
    pinMode(buzzer, OUTPUT);
    // Buttons to navigate menu
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);

    // Setup and initialize lcd object, defines custom character bitmaps
    begin_lcd();
}

void loop()
{
    lcd.clear();
    rgb_color(OFF);

    // Welcome text and initial story introduction is displayed on the lcd screen
    lcd.setCursor(3, 0);
    scroll_text("WELCOME TO   ", 0);
    delay(1500);
    lcd.clear();

    scroll_text("<<BACK TO THE FUTURE>>", 1);
    delay(1500);
    lcd.clear();

    scroll_text("You arrive in 2015 ...", 0);
    delay(800);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("and Biff is");
    lcd.setCursor(0, 1);
    lcd.print("chasing you!");

    delay(1400);

    // Returns true if choice 'a' is picked, false if choice 'b' is picked
    bool choice = get_choice("Speed Up", "Get Out");

    lcd.clear();
    lcd.setCursor(0, 0);

    delay(150);

    /*  PATH 1 (true): Marty chooses to run away on foot (possible loss)
        PATH 2 (false): Marty accelerates the DeLorean to 88 mph and escapes into time (guaranteed)
    */
    if (choice)
    {
        // PATH 1
        rgb_color(RED);
        lcd.write(DOWN_ARROW);
        lcd.print(" Press to run ");
        lcd.write(DOWN_ARROW);

        // Get result of running minigame
        bool win = run_away();

        // clear the top row of the lcd, and execute appropriate outcome
        clear_row(0);
        lcd.setCursor(0, 0);

        if (win)
        {
            // If the user wins, the BTTF theme plays and the display ends
            lcd.print("You get away");
            rgb_color(BLUE);
            play_theme(buzzer);
            delay(2400);
        }
        else
        {
            // If the user loses, the display ends and can optionally be reset
            lcd.print("HE CATCHES YOU!");
            flash_rgb(RED);
            delay(1000);
        }
    }
    else
    {
        // PATH 2
        speed_up();
        lcd.print("You get away");
        lcd.setCursor(0, 1);
        lcd.print("into the past!");
        play_theme(buzzer);
        delay(2400);
    }

    // Clean everything up and prepare to be reset
    lcd.clear();
    rgb_color(OFF);
    lcd.setCursor(0, 0);
    lcd.print("RESET");
    lcd.setCursor(2, 1);
    lcd.write(DOWN_ARROW);

    // Idle until reset button is pressed
    while (true)
    {
        if (!digitalRead(button1))
        {
            break;
        }
    }
}

/*  A function that will display two choices on the lcd and return which one the user picked
    The strings to be displayed are passed as parameters
    Also flashes the rgb led different colors
*/
bool get_choice(const char *a, const char *b)
{
    // Display 2 choices
    lcd.clear();

    lcd.print(a);
    lcd.write(DOUBLE_ARROW);
    lcd.print(b);

    lcd.setCursor(0, 1);
    lcd.write(DOWN_ARROW);
    lcd.setCursor(15, 1);
    lcd.write(DOWN_ARROW);

    bool is_red = true;
    long t0 = millis();

    while (true)
    {
        bool b1 = !digitalRead(button1);
        bool b2 = !digitalRead(button2);

        // When either of the buttons is pressed, return a bool value representing which button was pressed
        if (b1 || b2)
        {
            rgb_color(OFF);
            return b1;
        }

        // Blink without using delay() so as to still detect button presses
        long t1 = millis();
        if (t1 - t0 > 200) // If > 200 ms have elapsed
        {
            // Set LED to red or blue
            if (is_red)
            {
                rgb_color(BLUE);
            }
            else
            {
                rgb_color(WHITE);
            }
            // Flip flag
            is_red = !is_red;

            // set old time to new time
            t0 = t1;
        }
    }
}

/*  This function implements the timetravel minigame
    Use the potentiometer knob to accelerate and see the speed increase on the lcd
    exits when time travel speed (80mph) is reached
    (I know it is technically 88mph, but 80 worked better for the integer division and weird flickering issues)
*/
void speed_up()
{
    lcd.clear();
    int mph;
    int prev = 0;
    int max_speed = 80;

    // Determine initial direction to turn, depending on current state of potentiometer
    bool clockwise = true;
    int val = analogRead(knob);
    int brightness;

    if (val > 900)
    {
        clockwise = false;
    }

    do // Loop until mph reaches maxspeed
    {
        // small delay to smooth things out and reduce exccesive flashing
        delay(50);

        val = analogRead(knob);
        // Map analog knob values to miles per hour, direction depends on the initial state
        // Brightness controls the led brightness. 2 bit shifts to the right is faster than dividing by 4
        // 2^10 mapped to 2^8
        if (clockwise)
        {
            mph = map(val, 0, 1023, 0, max_speed);
            brightness = val >> 2;
        }
        else
        {
            mph = map(val, 1023, 0, 0, max_speed);
            brightness = 255 - (val >> 2);
        }

        // Format the display nicely for single digits and print the numeric speed
        if (mph < 10)
        {
            lcd.setCursor(5, 0);
            lcd.print("0");
            lcd.setCursor(6, 0);
        }
        else
        {
            lcd.setCursor(5, 0);
        }
        lcd.print(mph);
        lcd.print(" mph");

        // Format and display speed bar, decreases or increases based on speed
        lcd.setCursor(mph / 5, 1);
        if (mph > prev)
        {
            lcd.write(SOLID);
        }
        else if (mph < prev)
        {
            lcd.print(" ");
        }
        prev = mph;

        // LED gets more cyan as knob is turned
        rgb_color(RGB{0, brightness, brightness});

    } while (mph < max_speed);

    lcd.clear();

    // Exit when max speed reached
}

/*  This function implements the running minigame.
    Alternate pressing the buttons before Biff catches up.
    Returns true if the player succesfully escaped.
    Custom characters are displayed on screen.
*/
bool run_away()
{
    // Character starting positions
    int runnerpos = 3;
    int chaserpos = 0;

    bool b1last = false;

    long t0 = millis();

    // Draw initial positions once
    lcd.setCursor(chaserpos, 1);
    lcd.write(RUN_MAN);
    lcd.setCursor(runnerpos, 1);
    lcd.write(RUN_MAN);

    // Game loop, breaks on end conditions
    while (true)
    {
        // Increment the chaser's position once every .333 seconds
        long t1 = millis();
        if (t1 - t0 > 333)
        {
            // Erase the previous character before moving one segment to the right
            lcd.setCursor(chaserpos, 1);
            lcd.print(" ");

            chaserpos++;

            lcd.setCursor(chaserpos, 1);
            lcd.write(RUN_MAN);

            t0 = t1;
        }

        bool b1 = !digitalRead(button1);
        bool b2 = !digitalRead(button2);

        // Check for either button pressed, but not both (xor)
        if (b1 != b2)
        {
            // The user must alternate between the buttons, starting with b1 (right side)
            // Character position is updated on screen when the correct button is pressed
            // (updating once at the end of the loop resulted in flickering)
            if (b1last && b2)
            {
                rgb_color(GREEN);
                lcd.setCursor(runnerpos, 1);
                lcd.print(" ");

                runnerpos++;

                lcd.setCursor(runnerpos, 1);
                lcd.write(RUN_MAN);

                b1last = false;
            }

            if (!b1last && b1)
            {
                rgb_color(BLUE);
                lcd.setCursor(runnerpos, 1);
                lcd.print(" ");

                runnerpos++;

                lcd.setCursor(runnerpos, 1);
                lcd.write(RUN_MAN);

                b1last = true;
            }
        }

        if (chaserpos == runnerpos) // Biff caught up, you lost
        {
            return false;
        }
        else if (runnerpos > 15) // You get away if you reach the end of the screen
        {
            return true;
        }
    }
}

// A helper function that sets up the lcd and loads custom characters defined in "util.h"
void begin_lcd()
{
    // Initialize the lcd
    lcd.init();
    lcd.backlight();

    // Load custom characters
    lcd.createChar(SOLID, solid);
    lcd.createChar(DOWN_ARROW, down);
    lcd.createChar(LEFT_ARROW, left);
    lcd.createChar(RIGHT_ARROW, right);
    lcd.createChar(DOUBLE_ARROW, bi);
    lcd.createChar(RUN_MAN, run);

    lcd.setCursor(0, 0);
}

// CLears a single row of the lcd
void clear_row(int row)
{
    lcd.setCursor(0, row);
    lcd.print("                ");
}

// Scrolls a message in from the right
void scroll_text(const char *message, int startrow)
{
    lcd.setCursor(15, startrow);
    // Prints each character one at a time, scrolling to the left
    for (int letter = 0; letter < strlen(message); letter++)
    {
        lcd.print(message[letter]);
        lcd.scrollDisplayLeft();
        delay(300);
    }
}

// Sets the rgb led to a color, using the RGB struct defined in "util.h"
void rgb_color(RGB color)
{
    analogWrite(redPin, 255 - color.r);
    analogWrite(greenPin, 255 - color.g);
    analogWrite(bluePin, 255 - color.b);
}

// Flashes the led one color a few times
void flash_rgb(RGB color)
{
    for (int i = 0; i < 12; i++)
    {
        rgb_color(color);
        delay(150);
        rgb_color(OFF);
        delay(150);
    }
}

/*  Plays the notes encoded in the Back To The Future theme in "util.h"
    This code and melody taken from forum post by user '111windmills'
    https://forum.arduino.cc/index.php?topic=338236.0
*/
void play_theme(uint8_t pin)
{
    // Iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < sizeof(bttf) / sizeof(int) / 2; thisNote++)
    {
        // To calculate the note duration, take one second
        // divided by the note type.
        // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / bttf[1][thisNote];
        tone(pin, bttf[0][thisNote], noteDuration);

        // To distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // Stop the tone playing:
        noTone(pin);
    }
}