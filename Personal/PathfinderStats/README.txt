Explanation:
	This application runs a series of simulations to calculate how effective bonuses to attack rolls are in Pathfinder 2nd Edition.
	For those unfamiliar with Pathfinder 2nd Edition, attacks in combat are made in two steps:
		Rolling to Hit:
			Player rolls a 20 sided die and then adds a bonus based on the their stats.
			The result is then compared to the target's "Armor Class" or AC.
				If the result is >= the target's AC, they hit,
				If the result is >= 10 + the target's AC, they critically hit, dealing double damage
				If the result is < the target's AC they miss.
				If the result is < 10 - the target's AC they critically fail. (this usually doesn't have any additional effect)
				
				Furthermore, rolling a 20 on the die increases the degree of success by 1 (from success to crit success, or fail to success, etc.)
				and rolling a 1 on the die decreases the degree of success by 1
				
		if the player hit, they Roll Damage:
			Player rolls a number and type of dice determined by thier weapon and adds a bonus based on their stats.
				Double damage if the attack roll was a critical success.
	
Usage:
	Run "rollstats.exe" to start the application
	
	The program will first ask whether you want file output. 
	
		- If you say yes, all output will be put in the file "io/output.txt" overwriting anything already in that file.
			- This is the best option if you are running the program normally.
		- If you say no, all output will be printed to the console.
			- Console output is only preferrable if directly running from within the console, as most OSs close
			  console windows after program execution finishes. 
	
	
	Once you respond, the program reads the data from "io/input.txt" and runs a series of simulations based on the parameters set there
	and prints the results to the output you specified.
	
Interpreting Output:

	First, the program will show any errors it encountered while parsing the input file.
	
	Next, it will print a header showing the parameters of the simulation series
	
	Then it will print the results of each simulation in the series
		Each simulation shows:
			- The attack bonus of the player character
			- Percentage division of degrees of success for the attacks	
				- this is mostly for convenience as the pure percentages would be easy to calculate
			- Average damage on hit
				- includes damage of normal hits and critical hits
			- Average damage per attempted attack
				- overall average 
				
			- Percent increase from previous 
				- increase in average damage compared to the previous simulation (where toHit was 1 lower)
				- not included in Simulation 0
			- Percent increase in average damage per attempted attack overall
				- increase in average damage compared to Simulation 0
				- not included in Simulation 0


Input file Format: 

	An example of a valid file is included in "io/example.txt", copy the contents into "io/input.txt" to use it.
	
		- The format of the input file is as follows (only need to know if you want to edit it):
			- Each line starts with a header that declares what data it represents, followed by values in {}
			- Currently recognized headers are (replace the x with the desired value): 
				PlayerCharacter: {toHit=x; dieSize=x; numDie=x; damageBonus=x;}
					- Defines the statistics for the player character
						- toHit: defines the starting bonus to the player's attack rolls
						- dieSize: defines the number of sides on the player's damage dice
						- numDie: defines the number of damage dice the player rolls
						- damageBonus: defines a flat bonus to the player's damage, added after all dice are rolled
					- Restrictions
						- dieSize must be 4, 6, 8, 10, or 12
						- numDie must be > 0
				Target: {ac=x;}
					- Defines statistics for the target
						- ac: defines the target's armor class, which represents how difficult they are to hit
				rolls: {x}
					- Defines the number of attacks to roll in each simulation, higher means greater accuracy but longer processing time
					- Restrictions
						must be > 0
				simulations: {x}
					- Defines the number of simulations to run, each simulation increases the player's toHit bonus by one
					- Restrictions
						must be > 0
			- PlayerCharacter and Target are required, if rolls or simulations are not specified, defaults are used.
			- Small details:
				- For Class values, the order of the values within the {} is fixed and must be replicated exactly.
				- Lines are in the format "DataName: {value1; value2;}" for Class values,
				  or "dataName: {value}" for single variable values.
				- All values are limited by the size of an int on the machine they are run on (typically 4 bytes)
				- Order of the lines does not matter.
				- Invalid lines are skipped.
			
		