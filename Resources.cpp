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
    

}

void Resources::initFonts()
{
}

void Resources::initSounds()
{
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