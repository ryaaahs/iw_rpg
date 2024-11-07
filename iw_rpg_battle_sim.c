#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Allows us to generate a random value between x-y
// https://stackoverflow.com/a/65499678 

// return a random double in [0.0, 1.0]
double rand_bound(void) {
    return (rand() / (double)RAND_MAX); // Adjusted to ensure the upper limit is < 1.0
}

// return random double in [x,y]
double rand_between(double x, double y) {
    return rand_bound() * (y - x) + x;
}

int main(void) {
    // Get the system time.
    unsigned seed = time(0);
    srand(seed);

    // Stats
    const float ZONE_BONUS = 0.10; // Percent
    const float DAMAGE_RANGE_AVG = 0.875;
    const float DAMAGE_RANGE_LOW = 0.75;
    const short DAMAGE = 250;
    const float DAMAGE_AVG = (float)(DAMAGE * (DAMAGE_RANGE_AVG + ZONE_BONUS));
    const float DAMAGE_LOW = (float)(DAMAGE * (DAMAGE_RANGE_LOW + ZONE_BONUS));
    const float PLAYER_ACCURACY = 0.9; // Percent
    const float PLAYER_ATTACK_SPEED = 2.5; // Seconds
    const float PLAYER_CRITICAL_CHANCE = 0.06; // Percent
    const float PLAYER_CRITICAL_HIT_MULTIPLIER = 1.5; // Percent
    const float PLAYER_STAT_EFFICIENCY = 0.3475; // Percent

    const short MONSTER_HEALTH = 1125;

    const float GAME_TICK_SECONDS = 0.50; // Seconds
    const short GAME_TICK = 1;

    const short HOUR_IN_SECONDS = 3600;
    const long SIMULATIONS = 10000000;

    long total_ticks = 0;

    clock_t start = clock();

    for (long i = 0; i < SIMULATIONS; i++) {
        short simulated_health = MONSTER_HEALTH;
        short ticks = 0;

        while (simulated_health > 0) {
            ticks += GAME_TICK;

            if (ticks % (int)(GAME_TICK * (PLAYER_ATTACK_SPEED / GAME_TICK_SECONDS)) == 0) {
                if (rand_bound() < PLAYER_ACCURACY) {
                    if (rand_bound() < PLAYER_CRITICAL_CHANCE) {
                        simulated_health -= rand_between(
                            (DAMAGE_LOW * PLAYER_CRITICAL_HIT_MULTIPLIER), 
                            (DAMAGE * PLAYER_CRITICAL_HIT_MULTIPLIER)
                        );
                    } else {
                        simulated_health -= rand_between(DAMAGE_LOW, DAMAGE);
                    }
                }
            }
        }

        total_ticks += ticks;
    }

    clock_t end = clock();

    float ticks_per_kill = (float) total_ticks / SIMULATIONS;
    float kills_per_hour = (float) (HOUR_IN_SECONDS * (GAME_TICK / GAME_TICK_SECONDS)) / (ticks_per_kill + GAME_TICK);

    // Print results
    printf("Sim Iterations: %ld\n", SIMULATIONS);
    printf("Elapsed: %fms\n", (double)(end - start) * 1000.0  / CLOCKS_PER_SEC);
    printf("Avg Ticks Per Kill: %.2f\n", ticks_per_kill);
    printf("Avg Kills Per Hour: %.2f\n", kills_per_hour * (1 + PLAYER_STAT_EFFICIENCY));

    fflush(stdout);
    return 0;
}