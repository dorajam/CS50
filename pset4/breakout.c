/*
 breakout.c

 Computer Science 50
 Problem Set 4
 
 Author: Dora Jambor, dorajambor@gmail.com
 October, 2014
 
 This is the implementation of the breakout game.
 
*/

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// width and height of brick and paddle; declare space.
float brick_width = 34.50;
int brick_height = 20;
int paddle_width = WIDTH / 2 - 35;
int paddle_height = 550;
int space = 5;

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
GLabel initGameOver(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);
    
    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    
    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    
    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;
    
    // number of points initially
    int points = 0;
    
    //velocity of the moving ball
    double velocity_alongX = drand48() * 2;
    double velocity_alongY = drand48() * 2;
    
    // wait for click before exiting
    waitForClick();
 
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {  
        // move paddle with cursor
        GEvent movePaddle = getNextEvent (MOUSE_EVENT);
         
        if (movePaddle != NULL)
        {
            if (getEventType(movePaddle) == MOUSE_MOVED)
            {
                double x = getX(movePaddle) - paddle_width / 2;
                double y = 550;
                setLocation(paddle, x, y);
            }
        }
            
        // move the ball
        move(ball, velocity_alongX, velocity_alongY);
        
        double x = getX(ball);
        double y = getY(ball);
           
        if (x + getWidth(ball) >= WIDTH || x <= 0)
        {
            velocity_alongX = -velocity_alongX;
        }
        else if (y <= 0)
        {
            velocity_alongY = -velocity_alongY;
        }
               
        // check for collision using detectCollision
        GObject object = detectCollision(window, ball);

        if (object != NULL)
        {
            // bounce the ball from paddle and bricks
            if (strcmp(getType(object), "GRect") == 0 && object != label)
            {
                velocity_alongY = -velocity_alongY;
            }
            
            if (object != paddle && object != label && strcmp(getType(object), "GRect") == 0)
            {   
                //remove brick
                removeGWindow(window, object);
                bricks--;
                    
                //increase points
                points++;
                    
                //update scoreboard
                updateScoreboard(window, label, points);
            }
        }
        
        // if no bounce from paddle, then lose life and set ball to middle
        if (y + getHeight(ball) >= HEIGHT)
        {
            setLocation(ball, WIDTH / 2 - 10, HEIGHT / 2 - 10);
            lives--;
            
            // wait for click to start over
            if(lives != 0)
            {
                waitForClick();
            }
        }
        
        pause(5);
    }

    // tell player the game is over
    GLabel gameover = initGameOver(window);
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    string color[] = {"RED", "MAGENTA", "PINK", "CYAN", "GREEN"};
    
    for (float i = space; i < 400 - space; i = i + brick_width + space)
    {
        int k = 0;
    
        for (int j = 50; j <= 50 + brick_height * 5 + 4 * space; j = j + brick_height + space)
        {
            GRect brick = newGRect(i, j, brick_width, brick_height);
            setFilled (brick, true);
            setColor(brick, color[k]);
            add(window, brick);
            k++;
        }
    }
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{   
    GRect paddle = newGRect(paddle_width, paddle_height, 70, 10);
    setFilled (paddle, true);
    setColor (paddle, "BLACK");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - 10, HEIGHT / 2 - 10, 20, 20);
    setFilled (ball, true);
    setColor (ball, "BLACK");
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setColor(label, "PINK");
    setFont(label, "SansSerif-50");
    setLocation(label, WIDTH / 2 - getWidth(label) / 2, HEIGHT / 2 - getHeight(label) / 2);
    add(window, label);
    
    return label;
}

/**
 * 
 Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

/**
 * Instantiates, configures, and returns label for gameover.
 */
GLabel initGameOver(GWindow window)
{   
    GLabel gameover = newGLabel("GAME OVER");
    setColor(gameover, "BLACK");
    setFont(gameover, "Arial-Italic-55");
    setLocation(gameover, WIDTH / 2 - getWidth(gameover) / 2, 450);
    add(window, gameover);
    
    return gameover;
}
