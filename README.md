
# iw_rpg
  
# About
Directory to store related scripts to the Ironwood RPG game: https://ironwoodrpg.com

## Scripts:  
`iw_rpg_battle_sim`:  Simulation that mimics the player combat within Ironwood RPG

## Todo:  
`iw_rpg_battle_sim`:  
Add other utility runes that effect kills per hour (kps)  
Implement Mob damaging  
Implement Food consumption in relation to Mob Damage  
Implement death (Following death timers)  
Implement Potion consumption that affects loot and player health  
Implement Loop drops and log them for metrics (Gold, Items, Legendary)  
Add more Metrics (Hourly Food Consumption, Total Loot Drop)  

# Usage
Clone the repo into the designated folder of your choice using `git clone https://github.com/ryaaahs/iw_rpg.git`

`iw_rpg_battle_sim`:  
Using `gcc` in this example.  
Make any edits to the player data located at the top of the file  
```
Modify the following fields with a *
const float ZONE_BONUS = 0.10; // Percent (* If you're in zone with a bonus)
const float DAMAGE_RANGE_AVG = 0.875; (* Damage range, which depends on the weapon)
const float DAMAGE_RANGE_LOW = 0.75; (* Damage range, which depends on the weapon)
const short DAMAGE = 250; (*)
const float DAMAGE_AVG = (float)(DAMAGE * (DAMAGE_RANGE_AVG + ZONE_BONUS));
const float DAMAGE_LOW = (float)(DAMAGE * (DAMAGE_RANGE_LOW + ZONE_BONUS));
const float PLAYER_ACCURACY = 0.9; // Percent (*)
const float PLAYER_ATTACK_SPEED = 2.5; // Seconds (*)
const float PLAYER_CRITICAL_CHANCE = 0.06; // Percent (*)
const float PLAYER_CRITICAL_HIT_MULTIPLIER = 1.5; // Percent (*)
const float PLAYER_STAT_EFFICIENCY = 0.3475; // Percent (* You get the stat efficiency within the combat action)

const short MONSTER_HEALTH = 1125; (* Mob health that you are fighting)

const float GAME_TICK_SECONDS = 0.50; // Seconds
const short GAME_TICK = 1;

const short HOUR_IN_SECONDS = 3600;
const long SIMULATIONS = 10000000; (* How many mob simulations you want to run (1000 - 10,000,000 is goood)
```
Then compile the script using gcc
`gcc iw_rpg_battle_sim.c`
This will create an output file `a.out` that you can run
```
./a.out
Sim Iterations: 10000000
Elapsed: 434.049000ms
Avg Ticks Per Kill: 10.78
Avg Kills Per Hour: 823.89
``` 
