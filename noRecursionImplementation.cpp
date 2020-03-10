double GetProfit() {

		double totalProfit = 0;

		for (int i = 0; i < SIZE; i++) {

			totalProfit += profit[i].amount * profit[i].weeks * (1 - U_percentage/100.0);

		}

		double avgPerWeek = totalProfit / totalWeeks;

		

		return Z * avgPerWeek;

	}


