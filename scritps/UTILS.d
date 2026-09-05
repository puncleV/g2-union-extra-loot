instance dia_clean_xar_chest(c_info) {
    npc = none_100_xardas;
    nr = 2;
    condition = dia_clean_xar_chest_condition;
    information = dia_clean_xar_chest_info;
    permanent = true;
    important = false;
    description = "Очистить сундук Ксардаса";
};

func int dia_clean_xar_chest_condition() {
    return true;
};

func void dia_clean_xar_chest_info() {
    info_clearchoices(dia_clean_xar_chest);
    info_addchoice(dia_clean_xar_chest, dialog_back, dia_clean_xar_chest_back);
    info_addchoice(dia_clean_xar_chest, "Подтвердить удаление предметов (вернуть вещи будет нельзя)", dia_clean_xar_chest_clean);

};
func void dia_clean_xar_chest_clean() {
    punclev_remove_all_items();
    print("Все вещи были удалены из сундука.");
};

func void dia_clean_xar_chest_back() {
    info_clearchoices(dia_clean_xar_chest);
};

const string punclev_lucky_steal_str = "Удачная кража: ";

func void b_givethiefxp() {
    punclev_loot_steal();
    b_givethiefxp_old();
};

var string pv_steal_item_name;

func void print_stolen_item() {
    print(concatstrings(punclev_lucky_steal_str, pv_steal_item_name));
};

const string punclev_lp_give = "Я стал опытнее: +";
const string punclev_lp_given = "ЛП";
const string punclev_champion_text = "Чемпион";

var string pv_lp_given;

func void print_pv_lp() {
    print(concatstrings(concatstrings(punclev_lp_give, pv_lp_given), punclev_lp_given));
};