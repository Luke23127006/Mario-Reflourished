#include "Resources.h"
#include <iostream>

std::map<std::string, sf::Texture> Resources::textures;
std::map<std::string, sf::Font> Resources::fonts;
std::map<std::string, sf::SoundBuffer> Resources::sounds;

void Resources::initTextures()
{
                                            /*MAIN*/
    //Mario
    textures["MARIO_IDLE"].loadFromFile("./Resources/Character/Main/Mario/Mario/Mario.png");
    textures["MARIO_CLIMB"].loadFromFile("./Resources/Character/Main/Mario/Mario/MarioClimb.png");
    textures["MARIO_JUMP"].loadFromFile("./Resources/Character/Main/Mario/Mario/MarioJump.png");
    textures["MARIO_SKID"].loadFromFile("./Resources/Character/Main/Mario/Mario/MarioSkid.png");
    textures["MARIO_SWIM"].loadFromFile("./Resources/Character/Main/Mario/Mario/MarioSwim.png");
    textures["MARIO_DEATH"].loadFromFile("./Resources/Character/Main/Mario/Mario/MarioDead.png");
    textures["MARIO_WALK"].loadFromFile("./Resources/Character/Main/Mario/Mario/MarioWalk.png");

    //Super mario
    textures["SUPER_MARIO_IDLE"].loadFromFile("./Resources/Character/Main/Mario/Super Mario/SuperMario.png");
    textures["SUPER_MARIO_CLIMB"].loadFromFile("./Resources/Character/Main/Mario/Super Mario/SuperMarioClimb.png");
    textures["SUPER_MARIO_DUCK"].loadFromFile("./Resources/Character/Main/Mario/Super Mario/SuperMarioDuck.png");
    textures["SUPER_MARIO_JUMP"].loadFromFile("./Resources/Character/Main/Mario/Super Mario/SuperMarioJump.png");
    textures["SUPER_MARIO_SKID"].loadFromFile("./Resources/Character/Main/Mario/Super Mario/SuperMarioSkid.png");
    textures["SUPER_MARIO_SWIM"].loadFromFile("./Resources/Character/Main/Mario/Super Mario/SuperMarioSwim.png");
    textures["SUPER_MARIO_WALK"].loadFromFile("./Resources/Character/Main/Mario/Super Mario/SuperMarioWalk.png");
    
    //luigi
    textures["LUIGI_IDLE"].loadFromFile("./Resources/Character/Main/Luigi/Luigi/Luigi.png");
    textures["LUIGI_CLIMB"].loadFromFile("./Resources/Character/Main/Luigi/Luigi/LuigiClimb.png");
    textures["LUIGI_JUMP"].loadFromFile("./Resources/Character/Main/Luigi/Luigi/LuigiJump.png");
    textures["LUIGI_SKID"].loadFromFile("./Resources/Character/Main/Luigi/Luigi/LuigiSkid.png");
    textures["LUIGI_SWIM"].loadFromFile("./Resources/Character/Main/Luigi/Luigi/LuigiSwim.png");
    textures["LUIGI_DEATH"].loadFromFile("./Resources/Character/Main/Luigi/Luigi/LuigiDead.png");
    textures["LUIGI_WALK"].loadFromFile("./Resources/Character/Main/Luigi/Luigi/LuigiWalk.png");

    //Super Luigi
    textures["SUPER_LUIGI_IDLE"].loadFromFile("./Resources/Character/Main/Luigi/Super Luigi/SuperLuigi.png");
    textures["SUPER_LUIGI_CLIMB"].loadFromFile("./Resources/Character/Main/Luigi/Super Luigi/SuperLuigiClimb.png");
    textures["SUPER_LUIGI_DUCK"].loadFromFile("./Resources/Character/Main/Luigi/Super Luigi/SuperLuigiDuck.png");
    textures["SUPER_LUIGI_JUMP"].loadFromFile("./Resources/Character/Main/Luigi/Super Luigi/SuperLuigiJump.png");
    textures["SUPER_LUIGI_SKID"].loadFromFile("./Resources/Character/Main/Luigi/Super Luigi/SuperLuigiSkid.png");
    textures["SUPER_LUIGI_SWIM"].loadFromFile("./Resources/Character/Main/Luigi/Super Luigi/SuperLuigiSwim.png");
    textures["SUPER_LUIGI_WALK"].loadFromFile("./Resources/Character/Main/Luigi/Super Luigi/SuperLuigiWalk.png");

    //Fire Mario/Luigi
    textures["FIRE_MARIO_IDLE"].loadFromFile("./Resources/Character/Main/Mario/Fire Mario/FieryMario.png");
    textures["FIRE_MARIO_CLIMB"].loadFromFile("./Resources/Character/Main/Mario/Fire Mario/FieryMarioClimb.png");
    textures["FIRE_MARIO_DUCK"].loadFromFile("./Resources/Character/Main/Mario/Fire Mario/FieryMarioDuck.png");
    textures["FIRE_MARIO_FIREBALL"].loadFromFile("./Resources/Character/Main/Mario/Fire Mario/FieryMarioFireball.png");
    textures["FIRE_MARIO_JUMP"].loadFromFile("./Resources/Character/Main/Mario/Fire Mario/FieryMarioJump.png");
    textures["FIRE_MARIO_SKID"].loadFromFile("./Resources/Character/Main/Mario/Fire Mario/FieryMarioSkid.png");
    textures["FIRE_MARIO_SWIM"].loadFromFile("./Resources/Character/Main/Mario/Fire Mario/FieryMarioSwim.png");
    textures["FIRE_MARIO_WALK"].loadFromFile("./Resources/Character/Main/Mario/Fire Mario/FieryMarioWalk.png");

    //New Mario
    textures["NEW_MARIO_IDLE"].loadFromFile("./Resources/Character/Main/New mario/Mario/Mario.png");
    textures["NEW_MARIO_CLIMB"].loadFromFile("./Resources/Character/Main/New mario/Mario/MarioClimb.png");
    textures["NEW_MARIO_JUMP"].loadFromFile("./Resources/Character/Main/New mario/Mario/MarioJump.png");
    textures["NEW_MARIO_SKID"].loadFromFile("./Resources/Character/Main/New mario/Mario/MarioSkid.png");
    textures["NEW_MARIO_SWIM"].loadFromFile("./Resources/Character/Main/New mario/Mario/MarioSwim.png");
    textures["NEW_MARIO_DEATH"].loadFromFile("./Resources/Character/Main/New mario/Mario/MarioDead.png");
    textures["NEW_MARIO_WALK"].loadFromFile("./Resources/Character/Main/New mario/Mario/MarioWalk.png");

    //New Super Mario
    textures["NEW_SUPER_MARIO_IDLE"].loadFromFile("./Resources/Character/Main/New mario/Super Mario/SuperMario.png");
    textures["NEW_SUPER_MARIO_CLIMB"].loadFromFile("./Resources/Character/Main/New mario/Super Mario/SuperMarioClimb.png");
    textures["NEW_SUPER_MARIO_DUCK"].loadFromFile("./Resources/Character/Main/New mario/Super Mario/SuperMarioDuck.png");
    textures["NEW_SUPER_MARIO_JUMP"].loadFromFile("./Resources/Character/Main/New mario/Super Mario/SuperMarioJump.png");
    textures["NEW_SUPER_MARIO_SKID"].loadFromFile("./Resources/Character/Main/New mario/Super Mario/SuperMarioSkid.png");
    textures["NEW_SUPER_MARIO_SWIM"].loadFromFile("./Resources/Character/Main/New mario/Super Mario/SuperMarioSwim.png");
    textures["NEW_SUPER_MARIO_WALK"].loadFromFile("./Resources/Character/Main/New mario/Super Mario/SuperMarioWalk.png");

    //New Luigi
    textures["NEW_LUIGI_IDLE"].loadFromFile("./Resources/Character/Main/New luigi/Luigi/Luigi.png");
    textures["NEW_LUIGI_CLIMB"].loadFromFile("./Resources/Character/Main/New luigi/Luigi/LuigiClimb.png");
    textures["NEW_LUIGI_JUMP"].loadFromFile("./Resources/Character/Main/New luigi/Luigi/LuigiJump.png");
    textures["NEW_LUIGI_SKID"].loadFromFile("./Resources/Character/Main/New luigi/Luigi/LuigiSkid.png");
    textures["NEW_LUIGI_SWIM"].loadFromFile("./Resources/Character/Main/New luigi/Luigi/LuigiSwim.png");
    textures["NEW_LUIGI_DEATH"].loadFromFile("./Resources/Character/Main/New luigi/Luigi/LuigiDead.png");
    textures["NEW_LUIGI_WALK"].loadFromFile("./Resources/Character/Main/New luigi/Luigi/LuigiWalk.png");

    //New Super Luigi
    textures["NEW_SUPER_LUIGI_IDLE"].loadFromFile("./Resources/Character/Main/New luigi/Super Luigi/SuperLuigi.png");
    textures["NEW_SUPER_LUIGI_CLIMB"].loadFromFile("./Resources/Character/Main/New luigi/Super Luigi/SuperLuigiClimb.png");
    textures["NEW_SUPER_LUIGI_DUCK"].loadFromFile("./Resources/Character/Main/New luigi/Super Luigi/SuperLuigiDuck.png");
    textures["NEW_SUPER_LUIGI_JUMP"].loadFromFile("./Resources/Character/Main/New luigi/Super Luigi/SuperLuigiJump.png");
    textures["NEW_SUPER_LUIGI_SKID"].loadFromFile("./Resources/Character/Main/New luigi/Super Luigi/SuperLuigiSkid.png");
    textures["NEW_SUPER_LUIGI_SWIM"].loadFromFile("./Resources/Character/Main/New luigi/Super Luigi/SuperLuigiSwim.png");
    textures["NEW_SUPER_LUIGI_WALK"].loadFromFile("./Resources/Character/Main/New luigi/Super Luigi/SuperLuigiWalk.png");


    //New Fire Mario/Luigi
    textures["NEW_FIRE_MARIO_IDLE"].loadFromFile("./Resources/Character/Main/New mario/Fire Mario/FireMario.png");
    textures["NEW_FIRE_MARIO_CLIMB"].loadFromFile("./Resources/Character/Main/New mario/Fire Mario/FireMarioClimb.png");
    textures["NEW_FIRE_MARIO_DUCK"].loadFromFile("./Resources/Character/Main/New mario/Fire Mario/FireMarioDuck.png");
    textures["NEW_FIRE_MARIO_FIREBALL"].loadFromFile("./Resources/Character/Main/New mario/Fire Mario/FireMarioFireBall.png");
    textures["NEW_FIRE_MARIO_JUMP"].loadFromFile("./Resources/Character/Main/New mario/Fire Mario/FireMarioJump.png");
    textures["NEW_FIRE_MARIO_SKID"].loadFromFile("./Resources/Character/Main/New mario/Fire Mario/FireMarioSkid.png");
    textures["NEW_FIRE_MARIO_SWIM"].loadFromFile("./Resources/Character/Main/New mario/Fire Mario/FireMarioSwim.png");
    textures["NEW_FIRE_MARIO_WALK"].loadFromFile("./Resources/Character/Main/New mario/Fire Mario/FireMarioWalk.png");

                                                /*ENEMY*/
    //Goomba
    textures["GOOMBA_WALK"].loadFromFile("./Resources/Character/Enemy/Goomba/Goomba.png");

    //Koopa
    textures["KOOPA_WALK"].loadFromFile("./Resources/Character/Enemy/Koopa Troopa/KoopaWalk.png");

    //Shell
    textures["SHELL"].loadFromFile("./Resources/Character/Enemy/Koopa Troopa/GreenShell.png");

    //Piranha Plant
    textures["PIRANHA_PLANT_GREEN"].loadFromFile("./Resources/Character/Enemy/Piranha Plant/PiranhaPlantGreen.png");
    textures["PIRANHA_PLANT_RED"].loadFromFile("./Resources/Character/Enemy/Piranha Plant/PiranhaPlantRed.png");

    //Cheep Cheep
    textures["CHEEP_CHEEP"].loadFromFile("./Resources/Character/Enemy/Cheep Cheep/CheepCheep.png");

    //Brower(Boss)
    textures["BROWSER"].loadFromFile("./Resources/Character/Enemy/Brower/Brower.png");
    textures["FIRE_BROWSER"].loadFromFile("./Resources/Character/Enemy/Brower/Fireball.png");

                                                /*NPCs*/
    //Princess Peach
    textures["PRINCESS_PEACH"].loadFromFile("./Resources/Character/NPCs/PrincessToadstool.png");      

    //Toad
    textures["TOAD"].loadFromFile("./Resources/Character/NPCs/Toad.png");                                     
                                

}

void Resources::initMusics()
{
    musics["OVERWORLD"].openFromFile("./Resources/Sound/Music/Overworld.wav");
    musics["UNDERWORLD"].openFromFile("./Resources/Sound/Music/Underworld.wav");
    musics["UNDERWATER"].openFromFile("./Resources/Sound/Music/Underwater.wav");
}

void Resources::initSounds()
{
    sounds["1UP"].loadFromFile("./Resources/Sound/Sound effect/smb_1-up.wav");
    sounds["BOWSERFIRE"].loadFromFile("./Resources/Sound/Sound effect/smb_bowserfire.wav");
    sounds["COIN"].loadFromFile("./Resources/Sound/Sound effect/smb_coin.wav");
    sounds["FIREBALL"].loadFromFile("./Resources/Sound/Sound effect/smb_fireball.wav");
    sounds["GAMEOVER"].loadFromFile("./Resources/Sound/Sound effect/smb_gameover.wav");
    sounds["JUMP_SMALL"].loadFromFile("./Resources/Sound/Sound effect/smb_jump-small.wav");
    sounds["JUMP_SUPER"].loadFromFile("./Resources/Sound/Sound effect/smb_jump-super.wav");
    sounds["KICK"].loadFromFile("./Resources/Sound/Sound effect/smb_kick.wav");
    sounds["DEATH"].loadFromFile("./Resources/Sound/Sound effect/smb_mariodie.wav");
    sounds["PAUSE"].loadFromFile("./Resources/Sound/Sound effect/smb_pause.wav");
    sounds["PIPE"].loadFromFile("./Resources/Sound/Sound effect/smb_pipe.wav");
    sounds["POWERUP"].loadFromFile("./Resources/Sound/Sound effect/smb_powerup.wav");
    sounds["STAGECLEAR"].loadFromFile("./Resources/Sound/Sound effect/smb_stage_clear.wav");
    sounds["STOMP"].loadFromFile("./Resources/Sound/Sound effect/smb_stomp.wav");
}

void Resources::initFonts()
{
    fonts["EMULOGIC"].loadFromFile("./Resources/Font/emulogic.ttf");
    fonts["FOO"].loadFromFile("./Resources/Font/FOO.ttf");
    fonts["SNES_ITALIC"].loadFromFile("./Resources/Font/SNES Italic.ttf");
    fonts["SUPER_MARIO_BROS"].loadFromFile("./Resources/Font/Super Mario Bros.ttf");
}

Resources::Resources()
{
    this->initTextures();
    this->initFonts();
    this->initSounds();
}

Resources::~Resources()
{
}