#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
using namespace std;

class Player {
    public: 
        string name;
        int score;
        int balls;
        int fours;
        int sixes;
        bool isWicket;
    
        Player(string _name = "", int _score=0, int _balls=0 , int _fours=0, int _sixes=0 , bool _isWicket=false): name(_name), score(_score), balls(_balls), fours(_fours), sixes(_sixes), isWicket(_isWicket) {
        }
};

class Scorecard {
    public:
        int playersInTeam1, playersInTeam2;
        int totalOvers;
        map<string, Player> playersTeam1, playersTeam2;
        int totalScoreTeam1, totalScoreTeam2;
        int totalWicketsTeam1, totalWicketsTeam2;
        int totalOversPlayedTeam1, totalOversPlayedTeam2;
        Player* striker;
        Player* non_striker;
        int validBallsFacedTeam1, validBallsFacedTeam2;

    Scorecard(int playersInTeam1 = 0, int playersInTeam2 = 0, int totalOvers = 0) {
        this->playersInTeam1 = playersInTeam1;
        this->playersInTeam2 = playersInTeam2;
        this->totalOvers = totalOvers;
        totalScoreTeam1 = totalScoreTeam2 = 0;
        totalWicketsTeam1 = totalWicketsTeam2 = 0;
        totalOversPlayedTeam1 = totalOversPlayedTeam2 = 0;
        validBallsFacedTeam1 = validBallsFacedTeam2 = 0;
    }

    void showStrikers(){
        cout << striker->name << " " << non_striker->name  << endl;
    }

    void addPlayer(string playerName, string team) {
        Player newPlayer = Player(playerName, 0, 0, 0, 0, false);
        // cout << newPlayer.name << endl;
        if (team == "team1") {
            playersTeam1[playerName] = newPlayer;
        } else {
            playersTeam2[playerName] = newPlayer;
        }
    }

    void recordBall(string team, string ball) {
        if(ball != "W" && ball != "Nb" && ball != "Wd"){
            int score = stoi(ball);
            if (team == "team1") {
                playersTeam1[striker->name].score += score;
                playersTeam1[striker->name].balls++;
                if (score == 1 || score == 3){
                    changeStrike();
                }
                if (score == 4) playersTeam1[striker->name].fours++;
                if (score == 6) playersTeam1[striker->name].sixes++;
                totalScoreTeam1 += score;
            } else {
                playersTeam2[striker->name].score += score;
                playersTeam2[striker->name].balls++;
                if (score == 1 || score == 3){
                    changeStrike();
                }
                if (score == 4) playersTeam2[striker->name].fours++;
                if (score == 6) playersTeam2[striker->name].sixes++;
                totalScoreTeam2 += score;
            }
        }else if (ball=="W"){
            if(team == "team1"){
                totalWicketsTeam1++;
                playersTeam1[striker->name].balls++;
                Player * temp  = striker;
                for(auto &it :playersTeam1){
                    if(it.second.balls == 0 && non_striker != &(it.second)){
                        striker = &(it.second);
                        break;
                    }
                }
            }else{
                totalWicketsTeam2++;
                playersTeam2[striker->name].balls++;
                Player * temp  = striker;
                for(auto &it :playersTeam2){
                    if(it.second.balls == 0 && non_striker != &(it.second)){
                        striker = &(it.second);
                        break;
                    }

                }
            }
        }else if (ball == "Wd" || ball == "Nb"){
            team == "team1" ? totalScoreTeam1++ : totalOversPlayedTeam2;
        }
        
    }

    void markStrikers(string  name1, string name2, string team){
        Player *player1, *player2;
        if(team == "team1"){
            player1 = &playersTeam1[name1];
            player2 = &playersTeam1[name2];
        }else{
            player1 = &playersTeam2[name1];
            player2 = &playersTeam2[name2];
        }
        striker = player1;
        non_striker = player2;
        // cout << striker->name << " " << non_striker->name << " ";

    }

    void changeStrike(){
        swap(striker, non_striker);
    }

    void addWicket(string playerName, string team, int ball) {
        if (team == "team1") {
            playersTeam1[playerName].isWicket = true;
            totalWicketsTeam1++;
        } else {
            playersTeam2[playerName].isWicket = true;
            totalWicketsTeam2++;
        }
    }

    void displayScorecard(string team) {
        cout << "Scorecard for " << team << ":" << endl;
        cout << "Player Name Score 4s 6s Balls" << endl;
        map<string, Player> players = (team == "team1") ? playersTeam1 : playersTeam2;
        for (auto player : players) {
            cout << player.first << " " << player.second.score << " " << player.second.fours << " " << player.second.sixes << " " << player.second.balls << " ";
            // if (player.second.isWicket) {
            //     cout << "*";
            // }
            cout << endl;
        }
        cout << "Total: " << (team == "team1" ? totalScoreTeam1 : totalScoreTeam2) << "/" << (team == "team1" ? totalWicketsTeam1 : totalWicketsTeam2) << endl;
        cout << "Overs: " << (team == "team1" ? totalOversPlayedTeam1 : totalOversPlayedTeam2) << endl;
    }

    void displayResult() {
        int team1Runs = totalScoreTeam1;
        int team2Runs = totalScoreTeam2;

        if(team1Runs > team2Runs){
            cout << "Team 1 won by " << team1Runs - team2Runs << " runs!" << endl;
        } else {
            cout << "Team 2 won by " << playersInTeam1- totalWicketsTeam2 << " Wickets!" << endl;
        }
        string result = to_string(totalScoreTeam1) ;
    }

    void markEndOfOver(string team){
        if(team == "team1"){
            totalOversPlayedTeam1 ++;
        }else{
            totalOversPlayedTeam2 ++;
        }
        changeStrike();
    }
};

int main() {
    
    Scorecard scorecard(5, 5, 2);

    scorecard.addPlayer("P0", "team1");
    scorecard.addPlayer("P1", "team1");
    scorecard.addPlayer("P2", "team1");
    scorecard.addPlayer("P3", "team1");
    scorecard.addPlayer("P4", "team1");
    
    scorecard.markStrikers("P0", "P1", "team1");
    scorecard.recordBall("team1", "1");
    scorecard.recordBall("team1", "1");
    scorecard.recordBall("team1", "1");
    scorecard.recordBall("team1", "1");
    scorecard.recordBall("team1", "1");
    scorecard.recordBall("team1", "2");
    scorecard.markEndOfOver("team1");
    scorecard.displayScorecard("team1");

    scorecard.recordBall("team1", "W");
    scorecard.recordBall("team1", "4");
    scorecard.recordBall("team1", "4");
    scorecard.recordBall("team1", "Wd");
    scorecard.recordBall("team1", "W");
    scorecard.recordBall("team1", "1");
    scorecard.recordBall("team1", "6");
    scorecard.markEndOfOver("team1");
    scorecard.displayScorecard("team1");


    scorecard.addPlayer("P5", "team2");
    scorecard.addPlayer("P6", "team2");
    scorecard.addPlayer("P7", "team2");
    scorecard.addPlayer("P8", "team2");
    scorecard.addPlayer("P9", "team2");
    

    scorecard.markStrikers("P5", "P6", "team2");
    

    scorecard.recordBall("team2", "4");
    scorecard.recordBall("team2", "6");
    scorecard.recordBall("team2", "W");
    scorecard.recordBall("team2", "W");
    scorecard.recordBall("team2", "1");
    scorecard.recordBall("team2", "1");
    scorecard.markEndOfOver("team2");
    scorecard.displayScorecard("team2");

    scorecard.recordBall("team2", "6");
    scorecard.recordBall("team2", "1");
    scorecard.recordBall("team2", "W");
    scorecard.recordBall("team2", "W");
    scorecard.displayScorecard("team2");

    scorecard.displayResult();
    return 0;
}