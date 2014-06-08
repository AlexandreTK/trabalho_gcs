#include "interfaceMenu.h"

InterfaceMenu InterfaceMenu::InterfaceControl;

InterfaceMenu::InterfaceMenu(){
    spriteSheet = NULL;
}

void InterfaceMenu::render()
{
    renderBar();
    renderEnergy();
    renderQuest();
}

void InterfaceMenu::renderBar()
{
    int hpmax = Player::PlayerControl.getHPMax();
    int hp =    Player::PlayerControl.getHP();
    int HP_w = 0;
    float hpPercent = -1;

    //Dessa forma, 1 pixel = 1 HP
    int HPMax_w = hpmax;
    if(HPMax_w < 26) HPMax_w = 26; //tamanho minimo da barra.

    hpPercent = ((float)(hp)/(float)hpmax); //A % de HP que o jogador possui
    HP_w = (int)  (hpPercent*HPMax_w);

    int posX = (int)TILE_SIZE/3;
    int posY = (int)TILE_SIZE/2;

    //Se não tiver carregado um spritesheet, prototipo de quadrados
    if(spriteSheet == NULL)
    {
        SDL_Rect hpFull;
        SDL_Rect hpReal;

        hpFull.x = hpReal.x = posX;
        hpFull.y = hpReal.y = posY;
        hpFull.h = hpReal.h = (int)(TILE_SIZE/10);
        hpFull.w = hpReal.w = TILE_SIZE*3;
        //Nota: *100 do percent e /100 do real são cortados

        hpReal.w = HP_w; //A quantidad real de pixels
        //Faz o HP full ficar maior que o HP real por 1 pixel, tornando-o como uma borda
        hpReal.x++; hpReal.y++; hpFull.w+=2; hpFull.h+=2;

        SDL_FillRect( SDLBase::getScreen(), &hpFull, SDL_MapRGB( SDLBase::getScreen()->format, 255, 10, 10) );
        SDL_FillRect( SDLBase::getScreen(), &hpReal, SDL_MapRGB( SDLBase::getScreen()->format, 40, 255, 10) );
    }
    else
    {
        int hp_fill = 0;
        int endPosX = posX;
        int size = 16; // tamanho da divisão da imagem
        SDL_Rect clip;

        SDL_Rect start; start.x = 0; start.y = 0;
        SDL_Rect borda; borda.x = 1*size; borda.y = 0;
        SDL_Rect end; end.x = 2*size; end.y = 0;
        SDL_Rect off; off.x = 0; off.y = 1*size;
        SDL_Rect on; on.x = 0; on.y = 2*size;
        start.w = start.h = end.w = end.h = off.w = off.h = on.w = on.h = borda.w = borda.h = size;//tamanho do corte.

        clip = start;
        spriteSheet->render(posX, posY,&clip);
        hp_fill+= 13;
        endPosX+= size;

        //Nota: o 13 eh devido a quantidade de pixels no fim da barra
        while(hp_fill < (hpmax-13) )
        {
            int restante = hpmax-hp_fill-13;//restante que pode utilizar
            int step = restante;

            if(step > size) //step é o tamanho do sprite que deve renderizar
                step = size;

            borda.w = step;
            clip = borda;
            spriteSheet->render(endPosX, posY, &clip);

            hp_fill += step;
            endPosX += step;
        }

        clip = end;
        spriteSheet->render(endPosX, posY,&clip);
        /// FIM da barra, começando a imprimir o HP
        hp_fill = 0;
        endPosX = posX + 3;
        bool isFirst = true;
        //enche agora a barra de vida
        while(hp_fill < (hpmax) )
        {
            int step = hpmax-hp_fill;
            int stepHP = HP_w - hp_fill; //Quanto do HP tem q imprimir

            if(step > size) //step é o tamanho do sprite que deve renderizar
                step = size;

            if(stepHP < 0) stepHP = 0; //Caso já tenha preenchido todo o HP, step é 0
            if(stepHP > size) stepHP = size;


            //Arruma a parte de traz da barra
            off.w = step;
            if(isFirst) off.x = 0;
                else off.x = 1*size;
            clip = off;
            spriteSheet->render(endPosX, posY,&clip);

            on.w = stepHP;
            clip = on;
            spriteSheet->render(endPosX, posY,&clip);

            hp_fill += step;
            endPosX += step;
            isFirst = !isFirst;//Alterna sprites 0 e 1 em x do off
        }
        //Se pelo menos 1 pixel de HP tirado, imprime a parte final da barra
        if(HP_w != HPMax_w) {
            on.x = 1*size;
            clip = on;
            spriteSheet->render(posX+3+HPMax_w+1, posY,&clip);
        }
    }
}
void InterfaceMenu::renderEnergy()
{
    int size = 16;
    int posX = (int)TILE_SIZE/3;
    int posY = (int)TILE_SIZE/2;

    int r,g,b;
    r = 255;
    g = 255;
    b = 255;

    SDLBase::txt.applyText(posX, posY-6, 12,r,g,b,150,150,150, "%d/%d", Player::PlayerControl.getHP(), Player::PlayerControl.getHPMax() );

    posY+= 16;
    SDL_Rect clip;
    clip.x = 0; clip.y = 3*size; clip.h = clip.w = size;
    spriteSheet->render(posX, posY, &clip);
    posX+= 20;
    SDLBase::txt.applyText(posX, posY+2, 12,r,g,b,150,150,150, "%d", Player::PlayerControl.getFogo() );
    posX+=25;

    clip.x += size;
    spriteSheet->render(posX, posY, &clip);
    posX+= 20;
    SDLBase::txt.applyText(posX, posY+2, 12,r,g,b,150,150,150, "%d", Player::PlayerControl.getTerra() );
    posX+=25;

    clip.x += size;
    spriteSheet->render(posX, posY, &clip);
    posX+= 20;
    SDLBase::txt.applyText(posX, posY+2, 12,r,g,b,150,150,150, "%d", Player::PlayerControl.getAgua() );
    posX+=25;

    clip.x += size;
    spriteSheet->render(posX, posY, &clip);
    posX+= 20;
    SDLBase::txt.applyText(posX, posY+2, 12,r,g,b,150,150,150, "%d", Player::PlayerControl.getAr() );
}

void InterfaceMenu::renderQuest()
{
    int n = 0;
    int completa = 0;
    int n_quests = 0;
    for(unsigned int i = 0; i < Quest::QuestList.size();i++){
        if(Quest::QuestList[i]->isActive()){
            n+=Quest::QuestList[i]->render(10+10*n);
        }
        if(Quest::QuestList[i]->isCompleted())
            completa ++;
        n_quests++;
    }
    if(n>0){
        SDLBase::txt.applyText(530, 10-10, 12, 150,0,150,
                               200,200,200,"Quests:");}
}
