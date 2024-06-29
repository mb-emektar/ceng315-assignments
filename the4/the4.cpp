#include "the4.h"

// do not add extra libraries here

int divide_land(int X, int Y, bool** possible_plots){

	int** dp = new int*[X+1];
	for(int i = 0; i <= X; i++){
		dp[i] = new int [Y+1];
		for (int j = 0; j <= Y; j++){
			dp[i][j] = X*Y;
		}
 	}
	for(int i=1; i<=X; i++){
		for(int j=1; j<=Y; j++){
			if(possible_plots[i][j]){
			    dp[i][j]=0;
			    continue;
			}

			int min_vertical = i*j+1;
			for (int k=1; k<=j; k++){
				int min_vertical_new = dp[i][k] + dp[i][j-k];
				if(min_vertical_new < min_vertical)
					min_vertical = min_vertical_new;
			}
			
			int min_horizontal = i*j;
			for (int k=1; k<=i; k++){
				int min_horizontal_new = dp[k][j] + dp[i-k][j];
				if(min_horizontal_new < min_horizontal)
					min_horizontal = min_horizontal_new;
			}

			dp[i][j] = std::min(i*j, min_horizontal);
			dp[i][j] = std::min(dp[i][j], min_vertical);
		}
	}
	 return dp[X][Y];
}
