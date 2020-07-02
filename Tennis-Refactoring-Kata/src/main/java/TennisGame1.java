
public class TennisGame1 implements TennisGame {

    private static final String LOVE = "Love";
    private static final String FIFTEEN = "Fifteen";
    private static final String THIRTY = "Thirty";
    private static final String FORTY = "Forty";
    private static final String DEUCE = "Deuce";
    
    private int player1Score = 0;
    private int player2Score = 0;
    private String player1Name;
    private String player2Name;

    public TennisGame1(String player1Name, String player2Name) {
        this.player1Name = player1Name;
        this.player2Name = player2Name;
    }

    public void wonPoint(String playerName) {
        if (playerName == this.player1Name)
            this.player1Score += 1;
        else
            this.player2Score += 1;
    }

    // public String newGetScore() {
    public String getScore() {
        String score;

        int maxScore = Integer.max(this.player1Score, this.player2Score);
        int diffScore = Math.abs(this.player1Score - this.player2Score);

        if (this.player1Score == this.player2Score) {

            // The score are equal. The score should either be "<score>-All" or
            // "Deuce" if the current score is above or equals 3.
            if (this.player1Score >= 3) {
                score = DEUCE;
            } else {
                score = this.scoreToString(this.player1Score) + "-All";
            }

        } else if (maxScore >= 4) {

            // Since the person with the highest score have reached a score
            // above or equals 4, the person will either have the "advantage"
            // if the score is less that two, otherwise it will have won.
            String leader = (this.player1Score > this.player2Score) ? "player1" : "player2" ;            
            if (diffScore >= 2) {
                score = "Win for " + leader;
            } else {
                score = "Advantage " + leader;
            }

        } else {

            // Both players have a score less that 4 and doesn't have the same
            // score. The score just just be printed out "as is".
            score = this.scoreToString(this.player1Score) + "-" + this.scoreToString(this.player2Score);

        }

        return score;
    }

    public String oldGetScore() {
    //public String getScore() {
        String score = "";
        int tempScore=0;
        if (player1Score==player2Score)
        {
            switch (player1Score)
            {
                case 0:
                        score = "Love-All";
                    break;
                case 1:
                        score = "Fifteen-All";
                    break;
                case 2:
                        score = "Thirty-All";
                    break;
                default:
                        score = "Deuce";
                    break;
                
            }
        }
        else if (player1Score>=4 || player2Score>=4)
        {
            int minusResult = player1Score-player2Score;
            if (minusResult==1) score ="Advantage player1";
            else if (minusResult ==-1) score ="Advantage player2";
            else if (minusResult>=2) score = "Win for player1";
            else score ="Win for player2";
        }
        else
        {
            for (int i=1; i<3; i++)
            {
                if (i==1) tempScore = player1Score;
                else { score+="-"; tempScore = player2Score;}
                switch(tempScore)
                {
                    case 0:
                        score+="Love";
                        break;
                    case 1:
                        score+="Fifteen";
                        break;
                    case 2:
                        score+="Thirty";
                        break;
                    case 3:
                        score+="Forty";
                        break;
                }
            }
        }
        return score;
    }

    private String scoreToString(int score) {
        switch (score) {
            case 0:  return LOVE;
            case 1:  return FIFTEEN;
            case 2:  return THIRTY;
            case 3:  return FORTY;
            default: return null;
        }
    }
}
