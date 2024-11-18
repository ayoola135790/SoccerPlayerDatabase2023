// Author: E.Ogunleye
// Goal: Create a soccer player's database using the data
// ----------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Player
{
	string playername;
	string team;
	int goals, assists, minutes;
};

//Prototypes
void makeDatabase(string fileName, vector<Player>& playerDatabase);
void showPlayer(Player p);
void showDatabase(vector<Player> playerDatabase);
Player findMostEffectivePlayer(vector<Player> playerDatabase);
double performanceIndex(Player p);
//------------------------------------------------------------------

int main()
{
	vector<Player> playerDatabase;
	string fileName("c:/temp/soccer2023.txt");
	
	makeDatabase(fileName, playerDatabase);
	showDatabase(playerDatabase);

	Player mostEffectivePlayer = findMostEffectivePlayer(playerDatabase);
	cout << "\nMost Effective Player (AMAZING!)" << endl; 
	showPlayer(mostEffectivePlayer);

}
void makeDatabase(string fileName, vector<Player>& playerDatabase)
{
	string strplayername, strteam, strgoals, strassists, strminutes;
	ifstream infile(fileName);
	if (!infile)
	{
		cout << "Error - file not found";
		exit(1);
	}
	while (getline(infile, strplayername))
	{
		getline(infile, strteam);
		getline(infile, strgoals);
		getline(infile, strassists);
		getline(infile, strminutes);
		Player p{ strplayername, strteam,
		stoi(strgoals),
		stoi(strassists),
		stoi(strminutes) };
		playerDatabase.push_back(p);
	}
}
void showPlayer(Player p)
{
	cout << fixed << setprecision(2) << showpoint; 
	cout << setw(20) << left << p.playername 
		<< setw(20) << left << p.team 
		<< setw(10) << left << p.goals 
		<< setw(10) << left << p.assists 
		<< setw(10) << left << p.minutes 
		<< setw(10) << right << performanceIndex(p) 
		<< endl;
}
void showDatabase(vector<Player> playerDatabase)
{
	cout << "Player Name:\t    ";
	cout << "Team\t        ";
	cout << "Goals\t  ";
	cout << "Assists   ";
	cout << "Minutes\t   ";
	cout << "Perf. Index " << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	
	for (int i = 0; i < playerDatabase.size(); i++) {
		showPlayer(playerDatabase[i]);
	}
}

Player findMostEffectivePlayer(vector<Player> playerDatabase)
{
	int pos = 0;
	double maxPI = performanceIndex(playerDatabase[0]);

	for (double i = 1; i < playerDatabase.size(); i++)
	{
		double currentPI = performanceIndex(playerDatabase[i]);
			if (currentPI > maxPI) { 
				pos = i; 
				maxPI = currentPI; 
			}
	}
	return playerDatabase[pos];
}
double performanceIndex(Player p)
{
	double PI = 1000.0 * (p.goals + p.assists / 2.0) / p.minutes;
	return PI;
}