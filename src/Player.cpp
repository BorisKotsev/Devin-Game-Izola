#include "../headers/Player.h"
#include "../headers/World.h"

extern World world;

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::init(string configFile)
{
    srand(time(NULL));

    configFile = "config\\" + configFile;
    fstream stream;

    string tmp;
    string playerImg;
    string borderImg;

    stream.open(configFile.c_str());

    stream >> tmp >> playerImg;
    stream >> tmp >> borderImg;

    stream.close();

    m_playerTexture = LoadTexture(playerImg, world.m_main_renderer);
    m_borderTexture = LoadTexture(borderImg, world.m_main_renderer);
}

void Player::draw()
{

}

void Player::update()
{

}