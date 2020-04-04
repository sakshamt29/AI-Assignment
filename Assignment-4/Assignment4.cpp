#include <bits/stdc++.h>
using namespace std;
#define lli long long int
int i = 0;
int choice = 0;
bool user = true;
bool cpu = false;
int n = 0; // number of starting sticks
int pickup = 0;
int maxpick = 3;
string nmm;
int three = 0, two = 0, one = 0;
void AIlogic();
void AIlogic2();
void winner();
void win();
void mini()
{

  while (n > 1)
  {
    if (user)
    {
      cout << "AI 2 picks ";
      AIlogic2();
    }
    else
    {
      cout << "AI 1 picks ";
      AIlogic2();
    }
    if (pickup < 4 && pickup > 0)
    {
      n = n - pickup;
      cout << "Number of sticks left = " << n << "\n";
      user = !user;
    }
    else
    {
      cout << "You can only pick up between 1,2 or 3 sticks\n";
    }
  }
  win();
}
void win()
{
  if (user)
    cout << "AI 1 Wins!";
  else
    cout << "AI 2 Wins!";
}
void minimax()
{
  while (n > 1) //loop will run till last stick left
  {
    if (user)
    {
      cout << nmm << " enter the number of sticks to be removed\n";
      cin >> pickup;
    }
    else
    {
      AIlogic();
    }

    if (pickup < 4 && pickup > 0)
    {
      n = n - pickup;
      cout << "Number of sticks left = " << n << "\n";
      user = !user;
    }
    else
    {
      cout << "You can only pick up between 1,2 or 3 sticks\n";
    }
  }
  winner();
}
void winner()
{
  if (user)
    cout << "AI Wins!";
  else
    cout << nmm << " Wins!";
}
int getNoSticksToPickUp() //returning the best amount of sticks to pick up
{
  if (one > two && one > three)
  {
    return 1;
  }

  if (two > one && two > three)
  {
    return 2;
  }

  if (three > two && three > one)
  {
    return 3;
  }

  return 0;
}
void runMinimax(int sticksLeft, bool playerAI, int noSticksToPickUp, int &rootPickup) //minimax algo to find best option of sticks to pickup
{
  int maxPickup = 3;
  sticksLeft -= noSticksToPickUp;

  if (sticksLeft == 0)
  {
    playerAI = !playerAI;
  }
  if (sticksLeft <= 1)
  {

    if (playerAI)
    {
      if (rootPickup == 1)
        one--;
      if (rootPickup == 2)
        two--;
      if (rootPickup == 3)
        three--;
    }
    else
    {
      if (rootPickup == 1)
        one++;
      if (rootPickup == 2)
        two++;
      if (rootPickup == 3)
        three++;
    }

    return;
  }

  if (sticksLeft < maxPickup)
  {
    maxPickup = sticksLeft;
  }

  for (int j = 1; j <= maxPickup; j++) //recursion which runs through all the posible moves at this current level
  {
    runMinimax(sticksLeft, !playerAI, j, rootPickup);
  }

  return;
}
void resetCount()
{
  three = 0;
  two = 0;
  one = 0;
}
void AIlogic()
{
  int mp = 3;
  if (n < mp)
  {
    mp = n;
  }

  for (int i = 1; i <= mp; i++) // runs through all the posible moves at the root level
  {
    runMinimax(n, user, i, i);
  }
  pickup = getNoSticksToPickUp(); // sticks to be picked up
  if (pickup == 0)
  {
    pickup = rand() % 4;
  }
  cout << "AI picks " << pickup << " sticks.\n";

  resetCount();
}
void AIlogic2()
{
  int mp = 3;
  if (n < mp)
  {
    mp = n;
  }

  for (int i = 1; i <= mp; i++)
  {
    runMinimax(n, cpu, i, i);
  }
  pickup = getNoSticksToPickUp();
  if (pickup == 0)
  {
    pickup = rand() % 4;
  }
  cout << pickup << " sticks.\n";

  resetCount();
}

int main()
{
  cout << "Enter 1 for AI VS AI\n";
  cout << "Enter 2 for human VS AI\n";
  cin >> choice;

  cout << "Enter 14,21 or 53 as n.\n";
  cin >> n;
  srand(time(NULL));

  if (choice == 1)
  {
    cout << "Name of 1st AI is AI 1\n";
    cout << "Name of 2nd AI is AI 2\n";
    i = rand() % 2;
    cout << "Winner of the toss is :";
    if (i == 0)
    {
      cout << "AI 1\n";
      user = false;
    }
    else
    {
      cout << "AI 2\n";
    }
  }
  else
  {
    cout << "Enter your Name\n";
    cin >> nmm;

    i = rand() % 2;
    cout << "Winner of the toss is :";
    if (i == 0)
    {
      cout << "AI\n";
      user = false;
    }
    else
    {
      cout << nmm << "\n";
    }
  }
  if (choice == 2)
    minimax();
  else
  {
    mini();
  }

  return 0;
}