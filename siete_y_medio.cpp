#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "cards.h"
using namespace std;

// Global constants (if any)


// Non member functions declarations (if any)
void print_money_get_bet(Player* player);
bool print_value_get_continue(Player* player);
void print_dealer_card_total(Hand* dealer);
/**
   return 0 if no one overflows and player continue to draw
   return 1 if no one overflows and player do not continue to draw
   return 2 if dealer overflows but player do not
   return 3 if player overflows but dealer do not
   return 4 if both player and dealer overflow
 */
int run_one_round(Player* player, Hand* dealer);
void run_one_bet(Player* player);
void player_win(Player* player);
void player_lose(Player* player);
void tie(Player* player);

// Non member functions implementations (if any)
void print_money_get_bet(Player* player) {
  int bet;
  cout << "You have $" << player->get_money() << ". Enter bet: ";
  cin >> bet;

  if(bet <= player->get_money()) {
    player->adjust_bet(bet);
  }
  else {
    cout << "\nYou don't have that much money!\n";
    print_money_get_bet(player);
  }
  return;
}

bool print_value_get_continue(Player* player) {
  char in = '\0';
  while(in != 'y' && in != 'n') {
    cout << "Your total is " << player->get_value()
	 << ". Do you want another card (y/n)? ";
    cin >> in;
  }
  return (in == 'y')? true : false;
}

void print_dealer_card_total(Hand* dealer) {
  cout << "Dealer's cards:\n";
  dealer->print_all_cards();
  cout << "The dealer's total is " << dealer->get_value() << ".\n";
  return;
}


void player_win(Player* player) {
  cout << "You have won " << player->get_bet() << " dollars.\n";
  player->reset(player->get_bet());
  return;
}

void player_lose(Player* player) {
  cout << "You have lost " << player->get_bet() << " dollars.\n";
  player->reset(0 - player->get_bet());
  return;
}

void tie(Player* player, bool overflow) {
  if(overflow) {
    cout << "Both the dealer and you overflow!\n";
  } else {
    cout << "Both the dealer and you have the same value!\n";
  }
  cout << "No one wins.\n";
  player->reset(0);
  return;
}

int run_one_round(Player* player, Hand* dealer, bool draw) {
  bool player_overflow = false, dealer_overflow = false;

  // player draws
  if(draw) {
    Card player_card;
    cout << "New card:\n";
    player_card.print_card();
    player->add_card(player_card);
    if(player->get_value() > 7.5) {
      player_overflow = true;
    }
  }
  else {
    cout << "You did not draw in this round.\n";
  }

  // dealer draws
  if(dealer->get_value() < 5.5) {
    Card dealer_card;
    dealer->add_card(dealer_card);
    print_dealer_card_total(dealer);
    cout << "\n";
    if(dealer->get_value() > 7.5) {
      dealer_overflow = true;
    }
  }
  else {
    cout << "The dealer did not draw in this round.\n";
  }

  return (player_overflow && dealer_overflow) ? 4
    : (player_overflow) ? 3
    : (dealer_overflow) ? 2
    : (print_value_get_continue(player)) ? 0
    : 1;
}

void run_one_bet(Player* player) {
  print_money_get_bet(player);
  Hand* dealer = new Hand();
  bool player_draw = true, dealer_draw = true, no_overflow = true;

  do {
    dealer_draw = (dealer->get_value() < 5.5);
    switch( run_one_round(player, dealer, player_draw) ) {
    case 0:
      player_draw = true;
      break;
    case 1:
      player_draw = false;
      break;
    case 2:
      player_win(player);
      no_overflow = false;
      break;
    case 3:
      player_lose(player);
      no_overflow = false;
      break;
    case 4:
      tie(player, true);
      no_overflow = false;
      break;
    }
  } while((player_draw || dealer_draw) && no_overflow);

  if(no_overflow) {
    double diff = player->get_value() - dealer->get_value();
    (diff > 0) ? player_win(player)
      : (diff < 0) ? player_lose(player)
      : tie(player, false);
  }

  delete dealer;
}

// Stub for main
int main(){
   /* --STATEMENTS-- */
  Player* player = new Player(100);
  while (player->get_money() > 0 && player->get_money() < 1000) {
	  run_one_bet(player);
  }
  if (player->get_money() <= 0) {
	  cout << "You have lost all your money!\n"
		  << "Game over!\n";
  }
  else {
	  cout << "The dealer has lost all money!\n"
		  << "You win!\n";
  }

  delete player;
  return 0;

