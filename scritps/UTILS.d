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
    mob_removeallitems("XAR_CHEST");
    ai_printiteminfo("!!!", "Все вещи были удалены из сундука.", 2, 1);
};

func void dia_clean_xar_chest_back() {
    info_clearchoices(dia_clean_xar_chest);
};

const string punclev_lucky_steal_str = "Удачная кража: ";

func int rx_getthiefexp(var c_npc target) {
    punclev_loot_steal();
    return rx_getthiefexp_old(target);
};

instance npcVarInst(C_Npc)
{
};

func void SetNpcVar(var int aivrx, var int value) {
    RX_SetNpcVar(npcVarInst, aivrx, value);
};

func int GetNpcVar(var int aivrx) {
    return RX_GetNpcVar(npcVarInst, aivrx);
};

var string pv_steal_item_name;

func void print_stolen_item() {
    ai_printbonus(concatstrings(punclev_lucky_steal_str, pv_steal_item_name));
};