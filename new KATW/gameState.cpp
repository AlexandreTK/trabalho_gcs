#include "gameState.h"

void StateGame::load(int stack)
{
    ///QUESTS
    Quest* q1 = new Quest("2. Mate 5 Slimes!",5);
    //q1->setActive(true);
    //q1->setComplete(true);
    q1->setActive(false);
    q1->setComplete(false);

    q1->addLists();

    Quest* q2 = new Quest("3. Mate 5 Boomers", 5);
    //q2->setActive(true);
    //q2->setComplete(true);
    q2->setActive(false);
    q2->setComplete(false);
    q2->addLists();

    Quest* q3 = new Quest("1. Pegue 1 energias.",1);
    //q3->setActive(true);
    //q3->setComplete(true);
    q3->setActive(false);
    q3->setComplete(false);
    q3->addLists();

    Quest* q4 = new Quest("4. Mate o mid-boss(grande slime).",1);
    //q4->setActive(true);
    //q4->setComplete(true);
    q4->setActive(false);
    q4->setComplete(false);
    q4->addLists();

    Quest* q5 = new Quest("5. Mate o final-boss(slime cybord).",1);
    //q4->setActive(true);
    //q4->setComplete(true);
    q5->setActive(false);
    q5->setComplete(false);
    q5->addLists();



/// FIM TESTES

    //SpriteManager::SpriteControl.loadSprite("data/enemy/player_32.png",SPRITE_PLAYER);
    SpriteManager::SpriteControl.loadSprite("data/enemy/KaysTeste.png",SPRITE_PLAYER);
    SpriteManager::SpriteControl.loadSprite("data/enemy/bommer_enemy.png",SPRITE_BOOMER);
    //SpriteManager::SpriteControl.loadSprite("data/tileset/basic_tileset_32.png",SPRITE_TILESET);
    SpriteManager::SpriteControl.loadSprite("data/tileset/tile_Kays.png",SPRITE_TILESET);
    SpriteManager::SpriteControl.loadSprite("data/enemy/slime_enemy_simple.png",SPRITE_SLIME_SIMPLE);
    SpriteManager::SpriteControl.loadSprite("data/enemy/slime_boss.png", SPRITE_SLIME_GOD);

    SpriteManager::SpriteControl.loadSprite("data/enemy/npc1.png", SPRITE_NPC1);
    SpriteManager::SpriteControl.loadSprite("data/enemy/npc2.png", SPRITE_NPC2);
    SpriteManager::SpriteControl.loadSprite("data/enemy/npc3.png", SPRITE_NPC3);
    SpriteManager::SpriteControl.loadSprite("data/enemy/npc4.png", SPRITE_NPC4);

    SpriteManager::SpriteControl.loadSprite("data/enemy/boss_64.png", SPRITE_CYBORG_SLIME);

    if (!Map::MapControl.loadSprite(SpriteManager::SpriteControl.getSprite(SPRITE_TILESET))){
        printf("Nao carregou imagem de tileset\n");
    }

    if(!Map::MapControl.loadBackground(sp_bg = new Sprite("data/bg/bg1.png"))){
        printf("Nao carregou background\n");
    }

    sp_player = SpriteManager::SpriteControl.getSprite(SPRITE_PLAYER);
    SpriteManager::SpriteControl.loadSprite("data/tiro/shot3.png", SPRITE_TIRO);
    SpriteManager::SpriteControl.loadSprite("data/tiro/animTerra.png", SPRITE_TERRA);
    SpriteManager::SpriteControl.loadSprite("data/tiro/ar.png", SPRITE_AR);
    SpriteManager::SpriteControl.loadSprite("data/tiro/fogo.png", SPRITE_FOGO);
    SpriteManager::SpriteControl.loadSprite("data/tiro/ball_32.png", SPRITE_BALL);

    sp_item = new Sprite("data/item/itens.png");
    sp_bar = new Sprite("data/interface/life_bar2.png");

    InterfaceMenu::InterfaceControl.spriteSheet = sp_bar;

    Player::PlayerControl.resetPlayer();
    Player::PlayerControl.setPos(10*TILE_SIZE,10*TILE_SIZE);//32, 256);boss
    Player::PlayerControl.setSprite(sp_player,64,64);
    Player::PlayerControl.spr_tiroComum = SpriteManager::SpriteControl.getSprite(SPRITE_TIRO);
    Player::PlayerControl.spr_tiroTerra = SpriteManager::SpriteControl.getSprite(SPRITE_TERRA);
    Player::PlayerControl.spr_tiroAr =  SpriteManager::SpriteControl.getSprite(SPRITE_AR);
    Player::PlayerControl.spr_tiroFogo =  SpriteManager::SpriteControl.getSprite(SPRITE_FOGO);

    Player::PlayerControl.setAnimation(100,8);
    //Player::PlayerControl.setCollisionBox(12,14,8,18);
    Player::PlayerControl.setCollisionBox(0,0,40,64);
    Player::PlayerControl.addToEntidadeList();

    ItemObject::spr_itens = sp_item;


    if(stack == 1) {//faz load
        if (!Map::MapControl.loadMap("data/map/inicial.map") )
            printf("Arquivo .map nao encontrado: data/map/Casa.map\n");
        Save::loadGame();
        Player::PlayerControl.setPos(20*TILE_SIZE, 15*TILE_SIZE);
    } else { // novo jogo
        if (!Map::MapControl.loadMap("data/map/output_map.map") )
            printf("Arquivo .map nao encontrado: data/map/inicial.map\n");

        Vetor p9(8,200);
        ItemObject* item = new ItemObject(p9,ITEM_TYPE_HP,22);
        item->addLists();
    }
    Camera::CameraControl.setTarget(&Player::PlayerControl.pos.x, &Player::PlayerControl.pos.y);
    Camera::CameraControl.targetMode = TARGET_MODE_CENTER;


}

void StateGame::destroyObjetos() {

    //===== Arruma erro de ponteiro de linux =======/
    Player::PlayerControl.removeLifeBarLists();

//Entidades
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
            if(Entidade::EntidadeList[i] != &Player::PlayerControl ) //Player não é deletado
                delete Entidade::EntidadeList[i];
    for(unsigned int i = 0; i < Tiro::TiroList.size(); i++)
        delete Tiro::TiroList[i];
//Deleta instancias das Listas das interfaces
    for(unsigned int i = 0; i < LoopList.size(); i++)
        delete LoopList[i];
    for(unsigned int i = 0; i < DrawListBefore.size(); i++)
        delete DrawListBefore[i];
    for(unsigned int i = 0; i < DrawListAfter.size(); i++)
        delete DrawListAfter[i];

//Limpa listas
    LoopList.clear();
    DrawListBefore.clear();
    DrawListAfter.clear();
    Entidade::EntidadeList.clear();
    Tiro::TiroList.clear();

    //===== Arruma erro de ponteiro de linux =======/
    Player::PlayerControl.addLifeBarLists();
}
int StateGame::unload()
{
    destroyObjetos();
    //Deleta sprites
    delete sp_bg;
    delete sp_item;
    SpriteManager::SpriteControl.deleteSprite(SPRITE_BOOMER);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_TILESET);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_PLAYER);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_SLIME_SIMPLE);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_TIRO);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_TERRA);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_AR);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_FOGO);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_SLIME_GOD);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_NPC1);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_NPC2);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_NPC3);
    //Deleta quests somente quando sair do jogo ou estado.
    for(unsigned int i = 0; i < Quest::QuestList.size(); i++)
        delete Quest::QuestList[i];
    Quest::QuestList.clear();
    SDLBase::sfx.stopMusic();
    return stack;
}

eStateType StateGame::update(unsigned int dt)
{
    static bool pause = false;

    if(pause) dt = 0;

    if(InputManager::getInstance()->isKeyDown(SDLK_p)) pause = !pause;

    for(unsigned int i = 0; i < LoopList.size(); i++)
        LoopList[i]->update(dt);
///CALCULA POSIÇÃO
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
        Entidade::EntidadeList[i]->update(dt);
    for(unsigned int i = 0; i < Tiro::TiroList.size(); i++)
        Tiro::TiroList[i]->update(dt);
///EXECUTA COLISÕES
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
        Entidade::EntidadeList[i]->executaColisao();
    for(unsigned int i = 0; i < Tiro::TiroList.size(); i++)
        Tiro::TiroList[i]->executaColisao();

    Player::PlayerControl.handle_events();

    //Teleporta proximo mapa.... apaga entidades existentes
    if(Map::MapControl.isNextMap())
    {
        destroyObjetos();
        Player::PlayerControl.addToEntidadeList();
        Map::MapControl.loadNextMap();
    }

///VERIFICA DERROTA
    if(Player::PlayerControl.dead == true){
        stack = -1;
        return GST_WINLOSE;
    }
///VERIFICA VITORIA
    unsigned int n = 0;
    for(unsigned int i = 0; i < Quest::QuestList.size();i++){
        //Se não ativa e completada... fez a quest e entregou.... vence!
        if(Quest::QuestList[i]->isActive() == false && Quest::QuestList[i]->isCompleted() == true){
            n++;
        }
    }
    if (n >= Quest::QuestList.size()){
        stack = 1;
        return GST_WINLOSE;
    }
//FIM

    for(unsigned int i = 0; i < EventList.size(); i++) {
      //  if(EventList[i]->isActive()) {

        //}
    }

    return GST_NONE;
}
void StateGame::render()
{
    Map::MapControl.render(0,0);

    for(unsigned int i = 0; i < DrawListBefore.size(); i++)
        DrawListBefore[i]->render();

    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
        if(Entidade::EntidadeList[i] != &Player::PlayerControl ) //Garante que player é o ultimo a ser desenhado.
            Entidade::EntidadeList[i]->render();
    for(unsigned int i = 0; i < Tiro::TiroList.size(); i++)
            Tiro::TiroList[i]->render();

    Player::PlayerControl.render();

    for(unsigned int i = 0; i < DrawListAfter.size(); i++)
        DrawListAfter[i]->render();

    //somente para testar se a posição está correta.
    for(unsigned int i = 0; i < Teleporte::TeleporteList.size(); i++)
        Teleporte::TeleporteList[i]->render();

    Map::MapControl.renderLastLayer(0,0);

    InterfaceMenu::InterfaceControl.render();

    //menu.render();
}

