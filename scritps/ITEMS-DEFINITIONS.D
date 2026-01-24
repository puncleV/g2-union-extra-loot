instance itpo_np_stats_traders(c_item) {
    name = "«елье могущества";
    mainflag = item_kat_potions;
    flags = item_multi | item_mission;
    value = 15777;
    visual = "ITPO_MAGIC_02.3ds";
    material = mat_glas;
    on_state = use_itpo_np_stats;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "«елье могущества";
    text[1] = name_bonus_str;
    count[1] = 2;
    text[2] = name_bonus_dex;
    count[2] = 2;
    text[3] = name_bonus_manamax;
    count[3] = 5;
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_np_stats, bit_item_no_hotbar);
};

instance itpo_firedefence_traders(c_item) {
    name = "Ёликсир защиты от огн€";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 7000;
    visual = "ITPO_MAGIE_01_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_firedefence;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "Ёликсир защиты от огн€";
    text[1] = name_prot_fire;
    count[1] = 2;
    text[4] = "";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_firedefence, bit_item_no_hotbar);
};

instance itpo_magdefence_traders(c_item) {
    name = "Ёликсир защиты от магии";
    mainflag = item_kat_potions;
    flags = item_multi | item_mission;
    value = 7000;
    visual = "ITPO_MAGIE_02_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_magdefence;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "Ёликсир защиты от магии";
    text[1] = name_prot_magic;
    count[1] = 2;
    text[4] = "";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_magdefence, bit_item_no_hotbar);
};

instance itpo_amunsu_traders(c_item) {
    name = "«елье јмун-—у";
    mainflag = item_kat_potions;
    flags = item_multi | item_mission;
    value = 6500;
    visual = "ITPO_PERM_DEX_EX.3DS";
    material = mat_glas;
    on_state = useitpo_itpo_amunsu;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "«елье јмун-—у";
    text[1] = name_bonus_manamax;
    count[1] = 8;
    text[4] = "";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_amunsu, bit_item_no_hotbar);
};

instance itpo_intellect_traders(c_item) {
    name = "Ёликсир разума";
    mainflag = item_kat_potions;
    flags = item_multi | item_mission;
    value = 4000;
    visual = "ITPO_PERM_DEX_EX.3DS";
    material = mat_glas;
    on_state = use_itpo_intellect;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "Ёликсир разума";
    text[1] = name_bonus_int;
    count[1] = 2;
    text[4] = "";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_intellect, bit_item_no_hotbar);
};

instance itpo_rarepotion_01_traders(c_item) {
    name = "«елье магии";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 1750;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_01;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "”величивает максимальную ману на 200 ед.";
    text[4] = "¬рем€ действи€: 15 минут.";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_01, bit_item_nowisp);

};
instance itpo_rarepotion_02_traders(c_item) {
    name = "«елье мощи";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 1750;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_02;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "”величивает мощность физических атак на 20%.";
    text[4] = "¬рем€ действи€: 15 минут.";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_02, bit_item_nowisp);
};
instance itpo_rarepotion_03_traders(c_item) {
    name = "«елье защиты";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 2350;
    visual = "ITPO_BLACK_EX_2.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_03;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "—оздает защитную ауру, поглоща€ вход€щий урон на 20%.";
    text[4] = "¬рем€ действи€: 15 минут.";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_03, bit_item_nowisp);

};
instance itpo_rarepotion_04_traders(c_item) {
    name = "«елье неутомимости";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 750;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_04;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "ѕридает выпившему прилив сил, регенераци€ выносливости +15 в сек.";
    text[4] = "¬рем€ действи€: 15 минут.";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_04, bit_item_nowisp);

};
instance itpo_rarepotion_05_traders(c_item) {
    name = "«елье бесконечной маны";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 3350;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_05;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "–егенераци€ маны +50 в секунду.";
    text[4] = "¬рем€ действи€: 15 минут.";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_05, bit_item_nowisp);
};
instance itpo_rarepotion_06_traders(c_item) {
    name = "«елье верткости";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 2350;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_06;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "Ўанс увернутьс€ от любой атаки +50%.";
    text[4] = "¬рем€ действи€: 10 минут.";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_06, bit_item_nowisp);
};
instance itpo_rarepotion_07_traders(c_item) {
    name = "«елье регенерации";
    mainflag = item_kat_potions;
    flags = item_mission | item_multi;
    value = 3350;
    visual = "ITPO_BLACK_EX.3ds";
    material = mat_glas;
    on_state = use_itpo_rarepotion_07;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = name;
    text[3] = "¬осстанавливает 3% жизни в секунду.";
    text[4] = "¬рем€ действи€: 10 минут.";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_rarepotion_07, bit_item_nowisp);
};

instance itpo_megadrink_traders(c_item) {
    name = "Ёмбарла ‘иргасто";
    mainflag = item_kat_potions;
    flags = item_multi | item_mission;
    value = 13500;
    visual = "ITPO_MAGIE_02_EX.3ds";
    material = mat_glas;
    on_state = useitpo_megadrink;
    scemename = "POTIONFAST";
    wear = wear_effect;
    description = "Ёмбарла ‘иргасто";
    text[3] = "ќчень редкое и ценное зелье";
    text[4] = "Ёффект неизвестен...";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
    setitemvartrue(itpo_megadrink, bit_item_no_hotbar);
};

func void use_itpo_rarepotion_01() {
    use_itpo_rarepotion_01_old();
    
    if(self.id == 0) {
        rarepotion_01_numofsec += 300;
    };
};

func void use_itpo_rarepotion_02() {
    use_itpo_rarepotion_02_old();
    
    if(self.id == 0) {
        rarepotion_02_numofsec += 300;
    };
};

func void use_itpo_rarepotion_03() {
    use_itpo_rarepotion_03_old();
    
    if(self.id == 0) {
        rarepotion_03_numofsec += 300;
    };
};

func void use_itpo_rarepotion_04() {
    use_itpo_rarepotion_04_old();
    
    if(self.id == 0) {
        rarepotion_04_numofsec += 300;
    };
};

func void use_itpo_rarepotion_05() {
    use_itpo_rarepotion_05_old();
    
    if(self.id == 0) {
        rarepotion_05_numofsec += 300;
    };
};

func void use_itpo_rarepotion_06() {
    use_itpo_rarepotion_06_old();
    
    if(self.id == 0) {
        rarepotion_06_numofsec += 300;
    };
};

func void use_itpo_rarepotion_07() {
    use_itpo_rarepotion_07_old();
    
    if(self.id == 0) {
        rarepotion_07_numofsec += 300;
    };
};