#include "city/data_private.h"
#include "city/warning.h"
#include "core/random.h"
#include "festival.h"
#include "race_bet.h"

static int get_random_race_result(void)
{
    return (random_from_stdlib() % 4) + 1;
}

int has_bet_in_progress(void)
{
    return city_data.games.bet_value != NO_BET && city_data.games.bet_amount;
}

void race_result_process(void)
{
    if (city_data.games.bet_value != NO_BET) {
        // bet success
        if (get_random_race_result() == city_data.games.bet_value) {
            city_data.emperor.personal_savings += city_data.games.bet_amount * (city_festival_games_active() ? 4 : 2);
            city_warning_show(WARNING_BET_VICTORY);
        } else {
            if (city_data.emperor.personal_savings > city_data.games.bet_amount) {
                city_data.emperor.personal_savings -= city_data.games.bet_amount;
            } else {
                city_data.emperor.personal_savings = 0;
            }
            city_warning_show(WARNING_BET_DEFEAT);
        }

        // reset previous bet
        city_data.games.bet_value = NO_BET;
        city_data.games.bet_amount = 0;
    }
}
