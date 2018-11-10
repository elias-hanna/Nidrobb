#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include "../GameEnv/Player.hpp"

//Représente une commande
//Command Pattern
class Command
{
protected:
	std::string _name;
	int _target; //0:système , >0 : Player
public:
  virtual ~Command() {}

  //Pourrait être préférable de prendre le jeu en argument
  virtual void execute(Player& p) const = 0; //Execute l'action sur un joueur
  //virtual void execute(Game& g) = 0;

  //Accesseurs
  const std::string& name() const{return _name;}
  int target() const{return _target;}
};

#endif