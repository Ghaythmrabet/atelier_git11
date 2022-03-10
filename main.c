#include "header.h"


#define MENU 1
#define OPTIONS 2
#define PLAY 3

int main( int argc, char **argv)
{
	SDL_Init( SDL_INIT_VIDEO);
	SDL_Surface *screen;
	
	int valVolume[6]={0,25,50,75,100,125}; //niveaux volumes
	int nivVolume=5;
	int etat = MENU;
	int mouseX,mouseY,mouseClic=0;
	image backg;
	SDL_Event eventP;
	int continuerP=1;
	bouton newgame,settings,exit,fullscreen,check,plus,min,back;
	SDL_Surface *volumes[6];
	int position=1,continuer=1;
	SDL_Event event;
	SDL_Surface *texte=NULL;
	TTF_Init();
        
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
{	printf("failed to load music \n");}	
	screen = SDL_SetVideoMode(1920, 1080, 32,SDL_HWSURFACE | SDL_SRCALPHA);
	if( !screen)
{
	printf("unable to set 1500*800: %s\n",SDL_GetError());
	return 1; 
}
	SDL_Surface *nomJeu;
	SDL_Color white={ 0, 0, 0};
	TTF_Font *font=NULL;
	TTF_Font *font2=NULL;
	font= TTF_OpenFont("Mighty Brush Demo.ttf",50);
	font2= TTF_OpenFont("Bite Hard.ttf",100);
	SDL_Rect pos_text;
	SDL_Rect pos_nomJeu;
	pos_text.x=100;
       pos_text.y=900;
	pos_nomJeu.x=680;
	pos_nomJeu.y=150;
	nomJeu= TTF_RenderText_Blended(font2,"J O U R N E Y",white);

	SDL_Surface *text;
	
	int selection=0;
	Mix_Chunk *son;
    son = Mix_LoadWAV("btnsnd.wav");
    Mix_AllocateChannels(20);
	Mix_Music *musique=Mix_LoadMUS("akatsuki.mp3");
	initbackground( &backg);
	
	initbutton( &back , "back.png","back.png",10,10,"firstbuttons/clic.wav");
	initbutton( &fullscreen, "fullscreen_image.png","fullscreen_image.png", 100,300,"firstbuttons/clic.wav");
	initbutton( &check, "fs_unchecked.png","fs_checked.png", 400,320,"firstbuttons/clic.wav");
	initbutton( &plus, "soundplus.png","soundplus.png", 400,210,"firstbuttons/clic.wav");
	initbutton( &min, "soundminus.png","soundminus.png", 100,210,"firstbuttons/clic.wav");

	volumes[0] = IMG_Load("vol_0.png");
	volumes[1] = IMG_Load("vol_1.png");
	volumes[2] = IMG_Load("vol_2.png");
	volumes[3] = IMG_Load("vol_3.png");
	volumes[4] = IMG_Load("vol_4.png");
	volumes[5] = IMG_Load("vol_5.png");

	SDL_Rect posVolume;
	posVolume.x = 200;
	posVolume.y = 200;

	initbutton( &newgame, "firstbuttons/play.png","firstbuttons/play1.png", 1500,640,"firstbuttons/btnsnd.wav");
	initbutton( &settings, "firstbuttons/settings.png","firstbuttons/settings1.png", 1500,720,"firstbuttons/btnsnd.wav");
	initbutton( &exit, "firstbuttons/exit.png","firstbuttons/exit1.png", 1500,810,"firstbuttons/btnsnd.wav");
	Mix_PlayMusic(musique,-1);
while(continuer)
{
	
	afficher(backg,screen);
	backg.currentImg++;
	if (backg.currentImg>138)
	{
		backg.currentImg=1;
	}
	if (etat == MENU)
	{
	SDL_BlitSurface(text, NULL, screen, &pos_text);
	SDL_BlitSurface(nomJeu,NULL,screen,&pos_nomJeu);
	afficherBt(newgame,screen);
	afficherBt(settings,screen);
	afficherBt(exit,screen);
	}
	if (etat == OPTIONS)
	{
	afficherBt(back,screen);
	afficherBt(check,screen);
	afficherBt(plus,screen);
	afficherBt(min,screen);
	afficherBt(fullscreen,screen);
	SDL_BlitSurface(volumes[nivVolume],NULL,screen,&posVolume);
	}
	
	

    SDL_Flip(screen);


	///partie input
        while(SDL_PollEvent(&event))
        {
			switch(event.type)
        {
			case SDL_QUIT:    
        continuer=0;
        break;

	 	case SDL_MOUSEMOTION:
	 	mouseX = event.motion.x;
		 mouseY = event.motion.y;
	 break;  
	 	case SDL_MOUSEBUTTONUP:
		mouseClic=0;
	break;  

	 	case SDL_MOUSEBUTTONDOWN:
		mouseClic=1;
		 break;

		case SDL_KEYUP:
			mouseClic=0;

		break; 

		

		 case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_RETURN:
				mouseClic=1;
				break;
				
			case SDLK_UP:
				selection--;
				if (selection==0)
				{
					selection=3;
				}
				
				break;
			case SDLK_DOWN:
				selection++;
				if (selection==4)
				{
					selection=1;
				}
				
			break;

				
			
			default:
				break;
			}
		 break;   
	}
}
//partie mise a jour
if (etat == MENU)
{
	
if(event.motion.x>= newgame.pos.x && event.motion.x<= newgame.pos.x+newgame.img1->w && event.motion.y>= newgame.pos.y && event.motion.y<= newgame.pos.y+newgame.img1->h)
            {
				selection=1;
				
            }

if(event.motion.x>= settings.pos.x && event.motion.x<= settings.pos.x+settings.img2->w && event.motion.y>= settings.pos.y && event.motion.y<= settings.pos.y+settings.img1->h)
            {
				selection=2;
				
				
            }
            

if(event.motion.x>= exit.pos.x && event.motion.x<= exit.pos.x+exit.img1->w && event.motion.y>= exit.pos.y && event.motion.y<= exit.pos.y+exit.img1->h)
            {
                selection=3;
				
            }

switch (selection)
	{
					
	case 1:
		newgame.actif=1;
		settings.actif=0;
		exit.actif=0;
		
		text= TTF_RenderText_Blended(font,"Start a new game",white);
		
		break;
		
	case 2:
		newgame.actif=0;
		settings.actif=1;
		exit.actif=0;
		
		text= TTF_RenderText_Blended(font,"Modify game settings",white);
	break;	
	case 3:
		newgame.actif=0;
		settings.actif=0;
		exit.actif=1;
		
		text= TTF_RenderText_Blended(font,"Exit the game",white);
	break;
	
	default:
		break;
		
	}



if (mouseClic)//appuie sur la boutton de souris
{
	Mix_PlayChannel(-1,son,0);
	if (newgame.actif)
	{
		etat = PLAY;
		continuerP=1;
		mouseClic=0;
	}
	if (settings.actif)
	{
		//ouvrir settings
		etat = OPTIONS;
		continuerP=1;
		mouseClic=0;
		
	}
	if (exit.actif)
	{
		SDL_Delay(10);
		continuer=0;;
	}
	
	
}
}
if (etat == OPTIONS)
{


	if (mouseClic)
	{
		Mix_PlayChannel(-1,son,0);
		if(mouseX>= back.pos.x && mouseX<= back.pos.x+229 && mouseY>= back.pos.y && mouseY<= back.pos.y+69)
            {
                etat = MENU;
                continuerP=1;
		mouseClic=0;
            }
            
		if(mouseX>= check.pos.x && mouseX<= check.pos.x+50 && mouseY>= check.pos.y && mouseY<= check.pos.y+50)
            {
                if (check.actif)
				{
					check.actif=0;
					screen = SDL_SetVideoMode(1920, 1080, 32,SDL_HWSURFACE | SDL_SRCALPHA);
				}else if (check.actif==0)
				{
					check.actif=1;
					screen = SDL_SetVideoMode(1920, 1080, 32,SDL_HWSURFACE | SDL_SRCALPHA | SDL_FULLSCREEN);
				}
				
            }
		if(mouseX>= plus.pos.x && mouseX<= plus.pos.x+50 && mouseY>= plus.pos.y && mouseY<= plus.pos.y+50)
            {
            	continuerP=1;
		mouseClic=0;
                if (nivVolume<5) 
                	nivVolume++;
                	
            }
		if(mouseX>= min.pos.x && mouseX<= min.pos.x+50 && mouseY>= min.pos.y && mouseY<= min.pos.y+50)
            {
            	continuerP=1;
		mouseClic=0;
                if (nivVolume>0) 
                	nivVolume--;
            }	

	}
	
	Mix_VolumeMusic(valVolume[nivVolume]);
	
}
if (etat == PLAY)
{

	while (continuerP)
            {
                afficher(backg,screen);
				backg.currentImg++;
	if (backg.currentImg>138)
	{
		backg.currentImg=1;
	}
                SDL_Flip(screen);
				SDL_Delay(40);
                while (SDL_PollEvent(&eventP))
				{
                if (eventP.type == SDL_QUIT)
                {
                   continuer=0;
                   continuerP=0;
                }else if (eventP.type == SDL_KEYDOWN)
                {
                    continuerP=0;
                    etat= MENU;
                }
				}
                
            }
}


SDL_Delay(15);
}
	
 SDL_FreeSurface(screen);
liberer(backg);
libererBt(newgame);
libererBt(settings);
libererBt(exit);
Mix_FreeMusic(musique);
Mix_CloseAudio();
Mix_FreeChunk(son);
return 0;
}
