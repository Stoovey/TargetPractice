#include "includes.h"

void gameLogic(Cursor &cursor, Target &target, BITMAP* bmp);

BITMAP *background;
SAMPLE *gunShot;
BITMAP *Menubackground;
volatile int mouseClicks = 0;

volatile int ticks = 0; ////"volatile" means that the variable is likely to change/ meant to be changed during the program
void ticker()
{
       ticks++;
}
END_OF_FUNCTION(ticker)

       volatile int game_time = 0;
void game_time_ticker()
{
       game_time++;
}
END_OF_FUNCTION(game_time_ticker)

       const int updates_per_second = 60;

int main()
{
       if (allegro_init() != 0)
       {
              allegro_message("Cannot initalize Allegro.\n"); //If cannot load allegro display message
              return -1;
       }
       
       set_color_depth( 32 );
       if( set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 760, 0, 0) )
       {
              allegro_message("Video Error: %s.\n", allegro_error); // If cannot load into the screen, display nessage + error
              return 1;
       }
       
       if (install_keyboard())
       {
              allegro_message("Cannot initalize keyboard input.\n");
              return 1;
       }

       if (!install_mouse())
       {
              allegro_message("Cannot initalize mouse input.\n");
              return 1;
       }

       
       install_timer();
       install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
       LOCK_VARIABLE(ticks);
       LOCK_FUNCTION(ticker);
       install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));

       LOCK_VARIABLE(game_time);
       LOCK_FUNCTION(game_time_ticker);
       install_int_ex(game_time_ticker, BPS_TO_TIMER(10));
       int fps = 0;
       int frames_done = 0;
       int old_time = 0;

       Cursor myCursor;
       

       int currentTarget = 0;
       Target targetArray[20];

       for (int i = 0; i < 20; i++)
       {
              targetArray[i].ctorTarget();
       }

       set_window_title("Get off my land!");

       BITMAP* bmp = create_bitmap(1024, 768);
       background = load_bitmap("background.bmp", NULL);
       clear_to_color(bmp, makecol(0,128,128));
       gunShot = load_sample("gunShot.wav");
	   Menubackground = load_bitmap ("Menubackground.bmp", NULL);

      /* enum GameState {MENU, INSTRUCTIONS, INGAME, CREDITS, EXIT};
       GameState gameState;
       gameState = MENU;*/
       while(!key[KEY_ESC])
       {
       
       
              while(ticks == 0)
              {
                                  rest(1);
              }

              while(ticks > 0)
              {
                     int old_ticks = ticks;
                     /////////////////////////////////////////////////////////////////////////////
       
                           
/*
                           switch(gameState)
                           {
                                  case MENU:
								
                                                       if(key[KEY_1])
                                                       {
                                                              gameState = INGAME;
                                                       }
													   else if(key[KEY_2])
                                                       {
                                                              gameState = INSTRUCTIONS;
                                                       }
                                                       else if(key[KEY_3])
                                                       {
                                                              gameState = CREDITS;
                                                       }
                                                       else if(key[KEY_4])
                                                       {
                                                              exit(1);
                                                       }
                                                       break;
                                  case INSTRUCTIONS:
                                                       if(key[KEY_1])
                                                       {
                                                              gameState = MENU;
                                                       }
													   else if (key[KEY_2])
                                                       {
                                                              gameState = INGAME;
                                                       }
                                                       else if (key[KEY_3])
                                                       {
                                                              exit(1);
                                                       }
                                                       break;
                                  case INGAME:*/
              
                                                       blit(background, bmp, 0, 0, 0, 0, bmp->w, bmp->h); //Display background to the bmp
                                                       gameLogic(myCursor, targetArray[currentTarget], bmp); //Begin gameLogic 
                                                       if (targetArray[currentTarget].getPosY() > 768 && currentTarget < 19)
                                                       {
                                                              currentTarget++; //Increment for score
                                                              targetArray[currentTarget-1].dtorTarget();//Load new target if target has been shot
                                                              play_sample(gunShot, 255, 0, 1000,0);//OnClick/destroy bird, play sound
                                                       }
                                         /////////////////////////////////////////////////////////////////////////////

                                                       ticks--;
                                                       if(old_ticks <= ticks)
                                                       {
                                                              break; 
                                                       }

                                                       if(game_time - old_time >= 10)
                                                       {
                                                              fps = frames_done;
                                                              frames_done = 0;
                                                              old_time = game_time;
                                                       }

              
                                                       char click[5];
                                                       itoa(mouseClicks,click,10);
                                                       textout_ex(bmp, font, "Mouse Clicks", 20, 40, makecol(0, 0, 255), -1);
                                                       textout_ex(bmp, font, click, 125, 40, makecol(0, 0, 255), -1);

                                                       //Display Score
                                                       char score[5];
                                                       itoa(currentTarget,score,10);
                                                       textout_ex(bmp, font, "Score", 20, 20, makecol(0, 0, 255), -1);
                                                       textout_ex(bmp, font, score, 70, 20, makecol(0, 0, 255), -1);
                                                       blit(bmp, screen, 0,0,0,0, bmp->w,bmp->h);
                                                       frames_done++;
                                                       break;

                          /* case CREDITS:
                                                       if(key[KEY_1])
                                                       {
                                                              gameState = MENU;
                                                       }
                                                       else if (key[KEY_2])
                                                       {
                                                              exit(1);
                                                       }
                                                       break;
              */


                                  //}

              }
       }


       return 0;
}
END_OF_MAIN()

void gameLogic(Cursor &cursor, Target &target, BITMAP* bmp)
{
       if(!target.isPositionSet())
       {
              target.setPosition();
       }
       target.drawTarget(bmp);
       cursor.drawCursor(bmp);

       target.checkHit();
       if (target.hasBeenHit())
       {
              target.fallOff();
       }

}
