#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <unistd.h>//sleep

using namespace std;
//------------------SAVES-----------------//
int created_game_saves;
int active_game_save;
//------------------PLAYER-----------------//
string player_name;
char player;
char bullet;
char enemy_look;
int total_kills;
int difficulty_level;
int actual_hp;
int hp;//200
int money;//0
int damage;//100
//-------------------SHOP--------------------//
int shop_array[7];
int kaina1 = 1000;
int kaina2 = 5000;
int kaina3 = 500;
int kaina4 = 2000;
int kaina5 = 3000;
int kaina6 = 4000;
//-------------------ACHIEVEMENTS--------------------//
bool ax[16];
//-------------------WHILEPLAYING--------------------//
bool game_end_win;
bool game_running;
int kills_on_map;
bool wave;
int wave_count;
//-------------------ENEMYSPECS--------------------//
const int difficulty_lv1_damage = 20;
const int difficulty_lv2_damage = 50;
const int difficulty_lv3_damage = 80;
const int difficulty_lv1_hp = 100;//100
const int difficulty_lv2_hp = 200;//200
const int difficulty_lv3_hp = 300;//300
//-------------------TANK--------------------//
int x;
int y;
string look;
string shot_look;
int shot_x;
int shot_y;
bool shot;
//-------------------ENEMIES--------------------//
bool enemy1_left_alive;
bool enemy1_shot;
int enemy1_shot_x;
int enemy1_x;
int enemy1_y;
int enemy1_hp;
//--------------------------//
bool enemy2_up_alive;
bool enemy2_shot;
int enemy2_shot_y;
int enemy2_x;
int enemy2_y;
int enemy2_hp;
//--------------------------//
bool enemy3_down_alive;
bool enemy3_shot;
int enemy3_shot_y;
int enemy3_x;
int enemy3_y;
int enemy3_hp;
//--------------------------//
bool enemy4_right_alive;
bool enemy4_shot;
int enemy4_shot_x;
int enemy4_x;
int enemy4_y;
int enemy4_hp;
//-----------------------MAP-------------------//
const int map_y = 30;//30
const int map_x = 60;//60
string map_chosen;

char map[map_y][map_x];

void check_for_achievement();
void main_menu_text();
void loading_data();
void rewrite_saves();
void choose_game_save_text();
void choose_game_save();
void pard_text();
void parduotuve();
void inventory_text();
void inventory();
void save_echievements();
void pasiekimai();
void pradeti_zaidima();
void create_new_game_save();
void export_to_file();
void import_from_file();
void top_players_text();
void shell_sort(string a[], int b[], int c[], string d);
void top_players();
void main_menu(bool &program_running);
void clear_shots_onfield();
void spawn_enemy(int yy, int xx, string lok);
void print();
void payment();
void first_setup();
void player_spawn();

//----------------------MENU-----------------------//
void the_actual_game_fc();
void main_menu_text()
{
    cout << "--------------------------" << endl;
    cout << "|           WW3          |" << endl;
    cout << "--------------------------" << endl;
    cout << "\n1. Pradeti zaidima" << endl;
    cout << "2. Sukurti nauja zaidimo lygi" << endl;
    cout << "3. Pasirinkti norima zaidimo lygi" << endl;
    cout << "4. Inventorius" << endl;
    cout << "5. Parduotuve" << endl;
    cout << "6. Pasiekimai" << endl;
    cout << "7. Importuoti zaidimo turini" << endl;
    cout << "8. Eksportuoti zaidimo turini" << endl;
    cout << "9. Geriausi zaidejai" << endl;
    cout << "0. Iseiti" << endl;
    cout << "\n--------------------------" << endl;
}
void loading_data()
{
    ifstream file;
    file.open("saves.csv");
    ifstream file1;
    file1.open("shop.csv");
    ifstream file3;
    file3.open("achievements.csv");
    file >> created_game_saves;
    if(created_game_saves != 0)
    {
        file >> active_game_save;
        int check;
        string jump;
        bool temp;
        for(int i = 0; i < created_game_saves; i++)
        {
            file >> check;
            if(check == active_game_save)
            {
                file >> player_name;
                file >> difficulty_level;
                file >> total_kills;
                file >> hp;
                actual_hp = hp;
                file >> money;
                file >> damage;
                file >> player;
                file >> bullet;
                file >> enemy_look;
            }
            else
            {
                for(int j = 0; j < 9; j++)//i < nei, vieno seivo reiksmiu saves.csv faile neiskaitant pirmos reiksmes
                {
                    file >> jump;
                }
            }
        }
        //-------------------------------SHOP----------------------------------//
        for(int i = 1; i <= created_game_saves; i++)
        {
            if(i == active_game_save)
            {
                for(int j = 1; j <= 6; j++)
                {
                    file1 >> shop_array[j];
                }
            }
            else
            {
                for(int j = 1; j <= 6; j++)
                {
                    file1 >> check;
                }
            }
        }
        //-------------------------------ACHIEVEMENTS----------------------------------//
        for(int i = 1; i <= created_game_saves; i++)
        {
            if(i == active_game_save)
            {
                for(int j = 1; j <= 15; j++)
                {
                    file3 >> ax[j];
                }
            }
            else
            {
                for(int j = 1; j <= 15; j++)
                {
                    file3 >> temp;
                }
            }
        }
    }
    else
    {
        active_game_save = 0;
    }
    file.close();
    file1.close();
    file3.close();
}
void rewrite_saves()
{
    ofstream vrite;
    vrite.open("saves_temp.csv");
    ifstream take;
    take.open("saves.csv");
    ofstream vrite1;
    vrite1.open("shop_temp.csv");
    ifstream take1;
    take1.open("shop.csv");
    take >> created_game_saves;
    take >> active_game_save;
    vrite << created_game_saves << " " << active_game_save << endl;
    int a, b, c, d, e, f;
    string a1, b1, c1;
    for(int i = 1; i <= created_game_saves; i++)
    {
        if(i == active_game_save)
        {
            take >> a >> player_name >> b >> c >> d >> e >> f >> a1 >> b1 >> c1;
            vrite << active_game_save << " " << player_name << " " << b << " " << total_kills << " " << actual_hp << " " << money << " " << damage << " " << player << " " << bullet << " " << enemy_look << endl;
            take1 >> a >> b >> c >> d >> e >> f;
            vrite1 << shop_array[1] << " " << shop_array[2] << " " << shop_array[3] << " " << shop_array[4] << " " << shop_array[5] << " " << shop_array[6] << endl;
        }
        else
        {
            take >> a >> player_name >> b >> c >> d >> e >> f >> a1 >> b1 >> c1;
            vrite << a << " " << player_name << " " << b << " " << c << " " << d << " " << e << " " << f << " " << a1 << " " << b1 << " " << c1 << endl;
            take1 >> a >> b >> c >> d >> e >> f;
            vrite1 << a << " " << b << " " << c << " " << d << " " << e << " " << f << endl;
        }
    }
    vrite.close();
    take.close();
    vrite1.close();
    take1.close();
    remove("saves.csv");
    rename("saves_temp.csv","saves.csv");
    remove("shop.csv");
    rename("shop_temp.csv","shop.csv");
    loading_data();
}
void choose_game_save_text()
{
    cout << "--------------------------" << endl;
    cout << "|        GAME SAVES       |" << endl;
    cout << "--------------------------" << endl;
    cout << endl;
}
void choose_game_save()
{
    system("cls");
    choose_game_save_text();
    ifstream file;
    file.open("saves.csv");
    int pass;
    file >> pass >> pass;
    string data;
    char pass1;
    for(int i = 0; i < created_game_saves; i++)
    {
        file >> pass;
        file >> data;
        cout << i + 1 << ". Name: " << data << "| Difficulty: ";
        file >> pass;
        cout << pass;
        file >> pass;
        cout << "| Total kills: " << pass;
        file >> pass;
        cout << "| HP:  " << pass;
        file >> pass;
        cout << "| Money: " << pass;
        file >> pass;
        cout << "| Damage: " << pass << " ";
        if(active_game_save == i + 1)
        {
            cout << "(ACTIVE GAME SAVE)" << endl;
        }
        else
        {
            cout << endl;
        }
        file >> pass1 >> pass1 >> pass1;
    }
    file.close();
    cout << endl;
    int choice;
    cout << "Pasirinkite norima zaidimo lygi (1-" << created_game_saves << "): ";
    cin >> choice;
    ofstream vrite;
    vrite.open("saves_temp.csv");
    ifstream take;
    take.open("saves.csv");
    vrite << created_game_saves << " " << choice << endl;
    take >> pass >> pass;
    int a, b, c, d, e, f;
    string a1, b1, c1;
    for(int i = 1; i <= created_game_saves; i++)
    {
            take >> a >> player_name >> b >> c >> d >> e >> f >> a1 >> b1 >> c1;
            vrite << a << " " << player_name << " " << b << " " << c << " " << d << " " << e << " " << f << " " << a1 << " " << b1 << " " << c1 << endl;
    }
    vrite.close();
    take.close();
    remove("saves.csv");
    rename("saves_temp.csv","saves.csv");
    loading_data();
    system("cls");
    main_menu_text();
}
void pard_text()
{
    system("cls");
    cout << "--------------------------" << endl;
    cout << "|        PARDUOTUVE       |" << endl;
    cout << "--------------------------" << endl;
    cout << "Zaidejo isvaizda: " << endl;
    cout << "1. ( = ) - Kaina: " << kaina1 << "  ";
    if(shop_array[1] == 0){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "2. ( $ ) - Kaina: " << kaina2 << "  ";
    if(shop_array[2] == 0){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "Kulkos isvaizda:" << endl;
    cout << "3. ( * ) - Kaina: " << kaina3 << "  ";
    if(shop_array[3] == 0){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "4. ( ~ ) - Kaina: " << kaina4 << "  ";
    if(shop_array[4] == 0){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "Prieso isvaizda: " << endl;
    cout << "5. ( @ ) - Kaina: " << kaina5 << "  ";
    if(shop_array[5] == 0){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "6. ( % ) - Kaina: " << kaina6 << "  ";
    if(shop_array[6] == 0){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "7. Iseiti" << endl;
}
void parduotuve()
{
    bool pard = true;
    while(pard == true)
    {
        pard_text();
        int choice;
        cout << "Jusu pasirinkimas: ";
        cin >> choice;
        if(choice == 1)
        {
            if(shop_array[1] == 0)
            {
                if(money >= kaina1)
                {
                    shop_array[1] = 1;
                    money -= kaina1;
                    cout << "Daiktas patalpintas i inventoriu!" << endl;
                    system("pause");
                }
                else
                {
                    cout << "Jums truksta pinigu!" << endl;
                    system("pause");
                }
            }
            else
            {
                cout << "Sis daiktas jau isigytas!" << endl;
                system("pause");
            }
        }
        else if(choice == 2)
        {
            if(shop_array[2] == 0)
            {
                if(money >= kaina2)
                {
                    shop_array[2] = 1;
                    money -= kaina2;
                    cout << "Daiktas patalpintas i inventoriu!" << endl;
                    system("pause");
                }
                else
                {
                    cout << "Jums truksta pinigu!" << endl;
                    system("pause");
                }
            }
            else
            {
                cout << "Sis daiktas jau isigytas!" << endl;
                system("pause");
            }
        }
        else if(choice == 3)
        {
            if(shop_array[3] == 0)
            {
                if(money >= kaina3)
                {
                    shop_array[3] = 1;
                    money -= kaina3;
                    cout << "Daiktas patalpintas i inventoriu!" << endl;
                    system("pause");
                }
                else
                {
                    cout << "Jums truksta pinigu!" << endl;
                    system("pause");
                }
            }
            else
            {
                cout << "Sis daiktas jau isigytas!" << endl;
                system("pause");
            }
        }
        else if(choice == 4)
        {
            if(shop_array[4] == 0)
            {
                if(money >= kaina4)
                {
                    shop_array[4] = 1;
                    money -= kaina4;
                    cout << "Daiktas patalpintas i inventoriu!" << endl;
                    system("pause");
                }
                else
                {
                    cout << "Jums truksta pinigu!" << endl;
                    system("pause");
                }
            }
            else
            {
                cout << "Sis daiktas jau isigytas!" << endl;
                system("pause");
            }
        }
        else if(choice == 5)
        {
            if(shop_array[5] == 0)
            {
                if(money >= kaina5)
                {
                    shop_array[5] = 1;
                    money -= kaina5;
                    cout << "Daiktas patalpintas i inventoriu!" << endl;
                    system("pause");
                }
                else
                {
                    cout << "Jums truksta pinigu!" << endl;
                    system("pause");
                }
            }
            else
            {
                cout << "Sis daiktas jau isigytas!" << endl;
                system("pause");
            }
        }
        else if(choice == 6)
        {
            if(shop_array[6] == 0)
            {
                if(money >= kaina6)
                {
                    shop_array[6] = 1;
                    money -= kaina6;
                    cout << "Daiktas patalpintas i inventoriu!" << endl;
                    system("pause");
                }
                else
                {
                    cout << "Jums truksta pinigu!" << endl;
                    system("pause");
                }
            }
            else
            {
                cout << "Sis daiktas jau isigytas!" << endl;
                system("pause");
            }
        }
        else if(choice == 7)
        {
            pard = false;
            rewrite_saves();
            check_for_achievement();
            system("cls");
            main_menu_text();
        }
        else
        {
            cout << "Tokio pasirinkimo nera!" << endl;
            system("pause");
        }
    }
}
void inventory_text()
{
        cout << "--------------------------" << endl;
        cout << "|       INVENTORIUS       |" << endl;
        cout << "--------------------------" << endl;
        cout << "Zaidejo isvaizda: " << endl;
        //zaidejas------------------------------//

        cout << "( + ) ";
        if(player == '+'){cout << "(AKTYVUS)" << endl;}
        else{cout << endl;}
        if(shop_array[1] == 1)
        {
            cout << "( = ) " ;
            if(player == '='){cout << "(AKTYVUS)" << endl;}
            else{cout << endl;}
        }
        if(shop_array[2] == 1)
        {
            cout << "( $ ) " ;
            if(player == '$'){cout << "(AKTYVUS)" << endl;}
            else{cout << endl;}
        }
        //bulletas------------------------------//
        cout << "Kulkos isvaizda: " << endl;
        cout << "( - ) ";
        if(bullet == '-'){cout << "(AKTYVUS)" << endl;}
        else{cout << endl;}
        if(shop_array[3] == 1)
        {
            cout << "( * ) " ;
            if(bullet == '*'){cout << "(AKTYVUS)" << endl;}
            else{cout << endl;}
        }
        if(shop_array[4] == 1)
        {
            cout << "( ~ ) " ;
            if(bullet == '~'){cout << "(AKTYVUS)" << endl;}
            else{cout << endl;}
        }
        //enemy------------------------------//
        cout << "Prieso isvaizda: " << endl;
        cout << "( x ) ";
        if(enemy_look == 'x'){cout << "(AKTYVUS)" << endl;}
        else{cout << endl;}
        if(shop_array[5] == 1)
        {
            cout << "( @ ) " ;
            if(enemy_look == '@'){cout << "(AKTYVUS)" << endl;}
            else{cout << endl;}
        }
        if(shop_array[6] == 1)
        {
            cout << "( % ) " ;
            if(enemy_look == '%'){cout << "(AKTYVUS)" << endl;}
            else{cout << endl;}
        }
        cout << "--------------------------" << endl;
        cout << "1. Iseiti" << endl;
}
void inventory()
{
    system("cls");
    bool inventorius = true;
    while(inventorius == true)
    {
        inventory_text();
        string choice;
        cout << "Jusu pasirinkimas: ";
        cin >> choice;
        if(choice == "+")
        {
            if(player == '+')
            {
                cout << "Sis daiktas jau aktyvuotas!" << endl;
                system("pause");
                system("cls");
            }
            else
            {
                player = '+';
                cout << "Daiktas aktyvuotas!" << endl;
                system("pause");
                system("cls");
            }
        }
        else if(choice == "-")
        {
            if(bullet == '-')
            {
                cout << "Sis daiktas jau aktyvuotas!" << endl;
                system("pause");
                system("cls");
            }
            else
            {
                bullet = '-';
                cout << "Daiktas aktyvuotas!" << endl;
                system("pause");
                system("cls");
            }
        }
        else if(choice == "x")
        {
            if(enemy_look == 'x')
            {
                cout << "Sis daiktas jau aktyvuotas!" << endl;
                system("pause");
                system("cls");
            }
            else
            {
                enemy_look = 'x';
                cout << "Daiktas aktyvuotas!" << endl;
                system("pause");
                system("cls");
            }
        }
        else if(choice == "=")
        {
            if(shop_array[1] == 0)
            {
                cout << "Tokio pasirinkimo nera!" << endl;
                system("pause");
                system("cls");
            }
            else
            {
                if(player == '=')
                {
                    cout << "Sis daiktas jau aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
                else
                {
                    player = '=';
                    cout << "Daiktas aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
            }
        }
        else if(choice == "$")
        {
            if(shop_array[2] == 0)
            {
                cout << "Tokio pasirinkimo nera!" << endl;
                system("pause");
                system("cls");
            }
            else
            {
                if(player == '$')
                {
                    cout << "Sis daiktas jau aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
                else
                {
                    player = '$';
                    cout << "Daiktas aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
            }
        }
        else if(choice == "*")
        {
            if(shop_array[3] == 0)
            {
                cout << "Tokio pasirinkimo nera!" << endl;
                system("pause");
                system("cls");
            }
            else
            {
                if(bullet == '*')
                {
                    cout << "Sis daiktas jau aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
                else
                {
                    bullet = '*';
                    cout << "Daiktas aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
            }
        }
        else if(choice == "~")
        {
            if(shop_array[4] == 0)
            {
                cout << "Tokio pasirinkimo nera!" << endl;
                system("pause");
                system("cls");
            }
            else
            {
                if(bullet == '~')
                {
                    cout << "Sis daiktas jau aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
                else
                {
                    bullet = '~';
                    cout << "Daiktas aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
            }
        }
        else if(choice == "@")
        {
            if(shop_array[5] == 0)
            {
                cout << "Tokio pasirinkimo nera!" << endl;
                system("pause");
                system("cls");
            }
            else
            {
                if(enemy_look == '@')
                {
                    cout << "Sis daiktas jau aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
                else
                {
                    enemy_look = '@';
                    cout << "Daiktas aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
            }
        }
        else if(choice == "%")
        {
            if(shop_array[6] == 0)
            {
                cout << "Tokio pasirinkimo nera!" << endl;
                system("pause");
                system("cls");
            }
            else
            {
                if(enemy_look == '%')
                {
                    cout << "Sis daiktas jau aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
                else
                {
                    enemy_look = '%';
                    cout << "Daiktas aktyvuotas!" << endl;
                    system("pause");
                    system("cls");
                }
            }
        }
        else if(choice == "1")
        {
            inventorius = false;
            rewrite_saves();
            check_for_achievement();
            system("cls");
            main_menu_text();
        }
        else
        {
            cout << "Tokio pasirinkimo nera!" << endl;
            system("pause");
            system("cls");
        }
    }
}
void save_echievements()
{
    ofstream vrite;
    vrite.open("achievements_temp.csv");
    ifstream take;
    take.open("achievements.csv");
    string temp;
    for(int i = 1; i <= created_game_saves; i++)
    {
        if(i == active_game_save)
        {
            for(int j = 1; j <= 15; j++)
            {
                take >> temp;
                vrite << ax[j] << " ";
            }
            vrite << endl;
        }
        else
        {
            for(int j = 1; j <= 15; j++)
            {
                take >> temp;
                vrite << temp << " ";
            }
            vrite << endl;
        }
    }
    take.close();
    vrite.close();
    remove("achievements.csv");
    rename("achievements_temp.csv","achievements.csv");
}
void check_for_achievement()
{
    if(game_running == true && difficulty_level == 1 && ax[1] == false)
    {
        ax[1] = true;
    }
    if(game_running == true && difficulty_level == 2 && ax[2] == false)
    {
        ax[2] = true;
    }
    if(game_running == true && difficulty_level == 3 && ax[3] == false)
    {
        ax[3] = true;
    }
    if(total_kills >= 1 && ax[4] == false)
    {
        ax[4] = true;
    }
    if(wave_count == 2 && ax[5] == false)
    {
        ax[5] = true;
    }
    if(wave_count == 3 && ax[6] == false)
    {
        ax[6] = true;
    }
    if(wave_count == 4 && ax[7] == false)//-----------------------------77777777777777//
    {
        ax[7] = true;
    }
    if((shop_array[1] == 1 || shop_array[2] == 1) && ax[8] == false)
    {
        ax[8] = true;
    }
    if((shop_array[3] == 1 || shop_array[4] == 1) && ax[9] == false)
    {
        ax[9] = true;
    }
    if((shop_array[5] == 1 || shop_array[6] == 1) && ax[10] == false)
    {
        ax[10] = true;
    }
    if(wave_count == 4 && ax[11] == false)
    {
        ax[11] = true;
    }
    if(player != '+' && ax[12] == false)
    {
        ax[12] = true;
    }
    if(bullet != '-' && ax[13] == false)
    {
        ax[13] = true;
    }
    if(enemy_look != 'x' && ax[14] == false)
    {
        ax[14] = true;
    }
    if(money >= 1000 && ax[15] == false)
    {
        ax[15] = true;
    }
    save_echievements();
}
void pasiekimai()
{
    system("cls");
    cout << "--------------------------" << endl;
    cout << "|        PASIEKIMAI       |" << endl;
    cout << "--------------------------" << endl;
    cout << "1 Suzaiskite lengvo sunkumo lygi(1)  ";
    if(ax[1] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "2 Suzaiskite vidutinio sunkumo lygi(2)  ";
    if(ax[2] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "3 Suzaiskite sunkaus sunkumo lygi(3)  ";
    if(ax[3] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "4 Sunaikinkite nors viena priesa ";
    if(ax[4] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "5 Sekmingai iveiktie WAVE 1  ";
    if(ax[5] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "6 Sekmingai iveiktie WAVE 2  ";
    if(ax[6] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "7 Sekmingai iveiktie WAVE 3  ";
    if(ax[7] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "8 Parduotuveje nusipirkite zaidejo isvaizdos tipo pirkini  ";
    if(ax[8] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "9 Parduotuveje nusipirkite kulkos isvaizdos tipo pirkini  ";
    if(ax[9] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "10 Parduotuveje nusipirkite Prieso isvaizdos tipo pirkini  ";
    if(ax[10] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "11 Laimekite zaidima ant betkurio zemelapio  ";
    if(ax[11] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "12 Inventoriuje uzsidekite zaidejo isvaizdos tipo pirkini  ";
    if(ax[12] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "13 Inventoriuje uzsidekite kulkos isvaizdos tipo pirkini  ";
    if(ax[13] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "14 Inventoriuje uzsidekite prieso isvaizdos tipo pirkini  ";
    if(ax[14] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "15 Surinkti 1000 pinigu  ";
    if(ax[15] == false){cout << "-" << endl;}
    else{cout << "+" << endl;}
    cout << "--------------------------" << endl;
    system("pause");
    system("cls");
    main_menu_text();
}
void pradeti_zaidima()
{
    if(created_game_saves != 0)
    {
        /*cout << "created_game_saves=" <<  created_game_saves << endl;
        cout << "active_game_save="  << active_game_save << endl;
        cout << "name:" << player_name << endl;
        cout << "difficulty: " << difficulty_level << endl;
        cout << "total kills: " << total_kills << endl;
        cout << "hp: " << hp << endl;
        cout << "money: " << money << endl;
        cout << "gamage: "<< damage << endl;
        cout << "player_look: " << player << endl;
        cout << "bullet_look: " << bullet << endl;
        cout << "enemy_look: " << enemy_look << endl;
        system("pause");*/
        bool loop = true;
        while(loop == true)
        {
            cout << "Pasirinkite zemelapi(1-2)(2 nerealizuotas): ";
            cin >> map_chosen;
            if(map_chosen == "1")
            {
                ifstream take;
                take.open("map1.txt");
                char temp;
                for(int i = 0; i < map_y; i++)
                {
                     for(int j = 0; j < map_x; j++)
                     {
                         take >> temp;
                         if(temp != '0')
                         {
                            map[i][j] = temp;
                         }
                         else
                         {
                             map[i][j] = ' ';
                         }
                     }
                     map[i][map_x - 1] = '\0';
                }
                take.close();
                system("cls");
                the_actual_game_fc();
                check_for_achievement();
                rewrite_saves();
                loop = false;
            }
            else if(map_chosen == "2")
            {
                system("cls");
                main_menu_text();
                cout << "Atsiprasome bet zemelapis siuo metu nera pasiekiamas!" << endl;
            }
            else
            {
                system("cls");
                main_menu_text();
                cout << "Toks zemelapis neegzistuoja!" << endl;
            }
        }
        system("cls");
        main_menu_text();
    }
    else
    {
        system("cls");
        main_menu_text();
        cout << "Nera sukurtu zaidimo lygiu!" << endl;
    }
}
void create_new_game_save()
{
    if(created_game_saves == 0)
    {
        ofstream file;
        file.open("saves.csv");
        file << 1 << " " << 1 << endl;
        file << 1 << " ";
        cout << "Iveskite naudotojo varda: ";
        cin >> player_name;
        file << player_name << " ";
        //---------------------//
        bool loop = true;
        while(loop == true)
        {
            system("cls");
            main_menu_text();
            string difficulty;
            cout << "Zaidimo sunkumo lygis(1-3): ";
            cin >> difficulty;
            if(difficulty == "1")
            {
                difficulty_level = 1;
                loop = false;
            }
            else if(difficulty == "2")
            {
                difficulty_level = 2;
                loop = false;
            }
            else if(difficulty == "3")
            {
                difficulty_level = 3;
                loop = false;
            }
        }
        file << difficulty_level << " " << 0 << " " << 200 << " " << 0 << " " << 100 << " " << "+ " << "- " << "x " << endl;
        file.close();
        //---------------------//
        ofstream file1;
        file1.open("shop.csv");
        file1 << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << endl;
        file1.close();
        //---------------------//
        ofstream file2;
        file2.open("achievements.csv");
        file2 << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << endl;
        file2.close();
        //---------------------//
        loading_data();
        cout << "Naujas lygis sukurtas!" << endl;
    }
    else
    {
        ofstream vrite;
        vrite.open("saves_temp.csv");
        ifstream take;
        take.open("saves.csv");
        take >> created_game_saves;
        take >> active_game_save;
        vrite << created_game_saves + 1 << " " << created_game_saves + 1 << endl;
        int a, b, c, d, e, f;
        string a1, b1, c1;
        for(int i = 0; i < created_game_saves; i++)
        {
            take >> a >> player_name >> b >> c >> d >> e >> f >> a1 >> b1 >> c1;
            vrite << a << " " << player_name << " " << b << " " << c << " " << d << " " << e << " " << f << " " << a1 << " " << b1 << " " << c1 << endl;
        }
        cout << "Iveskite naudotojo varda: ";
        cin >> player_name;
        bool loop = true;
        while(loop == true)
        {
            system("cls");
            main_menu_text();
            string difficulty;
            cout << "Zaidimo sunkumo lygis(1-3): ";
            cin >> difficulty;
            if(difficulty == "1")
            {
                difficulty_level = 1;
                loop = false;
            }
            else if(difficulty == "2")
            {
                difficulty_level = 2;
                loop = false;
            }
            else if(difficulty == "3")
            {
                difficulty_level = 3;
                loop = false;
            }
        }
        vrite << created_game_saves + 1 << " " << player_name << " " << difficulty_level << " 0 " << "200 " << "0 " << "100 " << "+ " << "- " << "x " << endl;
        vrite.close();
        take.close();
        remove("saves.csv");
        rename("saves_temp.csv","saves.csv");
        //-----------------------------//
        ofstream file1;
        file1.open("shop.csv", ios_base::app);
        file1 << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << endl;
        file1.close();
        //----------------------------//
        ofstream file2;
        file2.open("achievements.csv", ios_base::app);
        file2 << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << endl;
        file2.close();
        //----------------------------//
        cout << "Naujas lygis sukurtas!" << endl;
        loading_data();
    }
}
void export_to_file()
{
    ofstream vrite;
    vrite.open("export.csv");
    ifstream take;
    take.open("saves.csv");
    string temp;
    take >> temp;
    vrite << temp << " ";
    take >> temp;
    vrite << temp << endl;
    for(int i = 0; i < created_game_saves; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            take >> temp;
            vrite << temp << " ";
        }
        vrite << endl;
    }
    take.close();
    take.open("achievements.csv");
    for(int i = 0; i < created_game_saves; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            take >> temp;
            vrite << temp << " ";
        }
        vrite << endl;
    }
    take.close();
    take.open("shop.csv");
    for(int i = 0; i < created_game_saves; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            take >> temp;
            vrite << temp << " ";
        }
        vrite << endl;
    }
    take.close();
    vrite.close();
    cout << "Eksportuota i export.csv!" << endl;
    system("pause");
    system("cls");
    main_menu_text();
}
void import_from_file()
{
    ofstream vrite;
    vrite.open("saves.csv");
    ifstream take;
    take.open("export.csv");
    take >> created_game_saves >> active_game_save;
    vrite << created_game_saves<< " " << active_game_save << endl;
    string temp;
    for(int i = 0; i < created_game_saves; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            take >> temp;
            vrite << temp << " ";
        }
        vrite << endl;
    }
    vrite.close();
    vrite.open("achievements.csv");
    for(int i = 0; i < created_game_saves; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            take >> temp;
            vrite << temp << " ";
        }
        vrite << endl;
    }
    vrite.close();
    vrite.open("shop.csv");
    for(int i = 0; i < created_game_saves; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            take >> temp;
            vrite << temp << " ";
        }
        vrite << endl;
    }
    vrite.close();
    take.close();
    cout << "Importuota is export.csv!" << endl;
    system("pause");
    system("cls");
    loading_data();
    main_menu_text();
}
void top_players_text()
{
    system("cls");
    cout << "--------------------------" << endl;
    cout << "|    GERIAUSI ZAIDEJAI    |" << endl;
    cout << "--------------------------" << endl;
    cout << "1. Surusiuoti pagal MONEY" << endl;
    cout << "2. Surusiuoti pagal TOTAL KILLS" << endl;
    cout << "3. Iseiti" << endl;
    cout << "--------------------------" << endl;
}
void shell_sort(string a[], int b[], int c[], string d)
{
    if(d == "KILLS")
    {
        for(int gap = 100 / 2; gap > 0; gap /= 2)
        {
            for(int i = gap; i < 100; i++)
            {
                int temp = b[i];
                string temp1 = a[i];
                int temp2 = c[i];
                int j;
                for(j = i; j >= gap && b[j - gap] < temp; j -= gap)
                {
                    b[j] = b[j - gap];
                    c[j] = c[j - gap];
                    a[j] = a[j - gap];
                }
                b[j] = temp;
                c[j] = temp2;
                a[j] = temp1;
            }
        }
    }
    else if(d == "MONEY")
    {
        for(int gap = 100 / 2; gap > 0; gap /= 2)
        {
            for(int i = gap; i < 100; i++)
            {
                int temp = b[i];
                string temp1 = a[i];
                int temp2 = c[i];
                int j;
                for(j = i; j >= gap && c[j - gap] < temp2; j -= gap)
                {
                    b[j] = b[j - gap];
                    c[j] = c[j - gap];
                    a[j] = a[j - gap];
                }
                b[j] = temp;
                c[j] = temp2;
                a[j] = temp1;
            }
        }
    }
}
void top_players()
{
    ofstream vrite("Output.html");
    vrite << "<!DOCTYPE html>" << endl;
    vrite << "<html>" << endl;
    vrite << "<head>" << endl;
    vrite << "<title>TOP PLAYERS</title>" << endl;
    vrite << "<style>" << endl;
    vrite << "table {" << endl;
    vrite << "border-spacing: 0;" << endl;
    vrite << "width: 100%;" << endl;
    vrite << "border: 1px solix #ddd;" << endl;
    vrite << "}" << endl;
    vrite << endl;
    vrite << "th, td {" << endl;
    vrite << "text-align: center;" << endl;
    vrite << "padding: 20px;" << endl;
    vrite << "}" << endl;
    vrite << endl;
    vrite << endl;
    vrite << ".header {" << endl;
    vrite << "padding: 80px;" << endl;
    vrite << "text-align: center;" << endl;
    vrite << "background: #ADFF2F;" << endl;
    vrite << "color: blue;" << endl;
    vrite << "font-size: 20px;" << endl;
    vrite << "}" << endl;
    vrite << "</style>" << endl;
    vrite << "</head>" << endl;
    vrite << "<body>" << endl;
    vrite << endl;
    vrite << "<div class=\"header\">" << endl;
    vrite << "<h1>TOP ZAIDEJAI</h1>" << endl;
    vrite << "</div>" << endl;
    vrite << endl;
    vrite << "<table id=\"myTable\"" <<endl;
    vrite << "<table style=\"border:1px solid black;margin-left:auto;margin-right:auto;\">"<<endl;
    vrite << "<tr>" << endl;
    vrite << "<th>NAME</th>" << endl;
    vrite << "<th>MONEY</th>" << endl;
    vrite << "<th>TOTAL KILLS</th>" << endl;
    string arr_names[100];
    int arr_money[100];
    int arr_kills[100];
    for(int i = 0; i < 100; i++)
    {
        arr_names[i] = "-";
        arr_kills[i] = 0;
        arr_money[i] = 0;
    }
    ifstream take;
    take.open("saves.csv");
    string temp;
    take >> temp >> temp;
    for(int i = 0; i < created_game_saves; i++)
    {
        take >> temp;
        take >> arr_names[i];
        take >> temp;
        take >> arr_kills[i];
        take >> temp;
        take >> arr_money[i];
        take >> temp;
        take >> temp;
        take >> temp;
        take >> temp;
    }
    top_players_text();
    string choice;
    bool check = true;
    while(check == true)
    {
        cout << "Jusu parisinkimas: ";
        cin >> choice;
        if(choice == "1")
        {
            shell_sort(arr_names, arr_kills, arr_money, "KILLS");
            check = false;
        }
        else if(choice == "2")
        {
            shell_sort(arr_names, arr_kills, arr_money, "MONEY");
            check = false;
        }
        else if(choice == "3")
        {
            system("cls");
            main_menu_text();
            check = false;
        }
        else
        {
            cout << "Tokio pasirinkimo nera!" << endl;
            system("pause");
            system("cls");
            top_players_text();
        }
    }
    for(int i = 0; i < 100; i++)
    {
        if(arr_names[i] != "-")
        {
            vrite << "<tr>" << endl;
            vrite << "<td>" << arr_names[i] << "</th>" << endl;
            vrite << "<td>" << arr_kills[i] << "</th>" << endl;
            vrite << "<td>" << arr_money[i] << "</th>" << endl;
            vrite << "</tr>" << endl;
        }
        else
        {
            vrite << "<tr>" << endl;
            vrite << "<td>" << "-" << "</th>" << endl;
            vrite << "<td>" << "-" << "</th>" << endl;
            vrite << "<td>" << "-" << "</th>" << endl;
            vrite << "</tr>" << endl;
        }
    }
    vrite << "</table>" << endl;
    vrite << "</body>" << endl;
    vrite << "</html>" << endl;
    vrite.close();
    system("start Output.html");
    system("cls");
    main_menu_text();
}
void main_menu(bool &program_running)
{
    string choice = "0";
    cout << "Jusu pasirinkimas: ";
    cin >> choice;
    if(choice == "1")
    {
        pradeti_zaidima();
    }
    else if(choice == "2")
    {
        create_new_game_save();
    }
    else if(choice == "3")
    {
        choose_game_save();
    }
    else if(choice == "4")
    {
        inventory();
    }
    else if(choice == "5")
    {
        parduotuve();
    }
    else if(choice == "6")
    {
        pasiekimai();
    }
    else if(choice == "7")
    {
        import_from_file();
    }
    else if(choice == "8")
    {
        export_to_file();
    }
    else if(choice == "9")
    {
        top_players();
    }
    else if(choice == "0")
    {
        cout << "Zaidimo pabaiga." << endl;
        program_running = false;
    }
    else
    {
        system("cls");
        main_menu_text();
        cout << "Tokio meniu punkto nera!" << endl;
    }
}

//-----------------------GAME----------------------//
void clear_shots_onfield()
{
    for(int x = 0; x < map_y; x++)
    {
        for(int y = 0; y < map_x; y++)
        {
            if(map[x][y] == bullet)
            {
                map[x][y] = ' ';
            }
        }
    }
}
void spawn_enemy(int yy, int xx, string lok)
{
    if(lok == "LEFT")
    {
        map[yy][xx] = enemy_look;
        map[yy][xx - 1] = enemy_look;
        map[yy - 1][xx] = enemy_look;
        map[yy - 1][xx + 1] = enemy_look;
        map[yy + 1][xx] = enemy_look;
        map[yy + 1][xx + 1] = enemy_look;
    }
    if(lok == "UP")
    {
        map[yy][xx] = enemy_look;
        map[yy - 1][xx] = enemy_look;
        map[yy][xx - 1] = enemy_look;
        map[yy + 1][xx - 1] = enemy_look;
        map[yy][xx + 1] = enemy_look;
        map[yy + 1][xx + 1] = enemy_look;
    }
    if(lok == "DOWN")
    {
        map[yy][xx] = enemy_look;
        map[yy + 1][xx] = enemy_look;
        map[yy][xx - 1] = enemy_look;
        map[yy - 1][xx - 1] = enemy_look;
        map[yy][xx + 1] = enemy_look;
        map[yy - 1][xx + 1] = enemy_look;
    }
    if(lok == "RIGHT")
    {
        map[yy][xx] = enemy_look;
        map[yy][xx + 1] = enemy_look;
        map[yy + 1][xx] = enemy_look;
        map[yy + 1][xx - 1] = enemy_look;
        map[yy - 1][xx] = enemy_look;
        map[yy - 1][xx - 1] = enemy_look;
    }
}
void print()
{
    system("cls");
    //----------------------------------------------------------------------//Printing
        for(int display = 0; display < 1; display++)
        {
            cout << map[display] << endl;
        }
        cout << "#HP:";
        if(hp < 0)
        {
            printf("%3d", 0);
        }
        else
        {
            printf("%3d", hp);
        }
        cout << " # MONEY:";
        printf("%5d", money);
        cout << "                          ";
        cout << "   WAVE: ";
        if(wave_count < 4)
        {
            cout << wave_count;
        }
        else
        {
            cout << wave_count - 1;
        }
        cout << " #" << endl;
        for(int display = 0; display < 1; display++)
        {
            cout << map[display] << endl;
        }
        for(int display = 1; display < map_y - 1; display++)
        {
            cout << map[display] << endl;
        }
        for(int display = 0; display < 1; display++)
        {
            cout << map[display] << endl;
        }
        cout << "#[x:";
        printf("%2d", x);
        cout << ",y:";
        printf("%2d", y);
        cout << "]";
        cout << "                              ";
        cout << "TOTAL KILLS: " << total_kills << " #" << endl;
        for(int display = map_y - 1; display < map_y; display++)
        {
            cout << map[display] << endl;
        }
        //if(shot == false){system("pause");}
}
void payment()
{
    if(difficulty_level == 1)
    {
        money += 25;
    }
    if(difficulty_level == 2)
        {
        money += 50;
    }
    if(difficulty_level == 3)
    {
        money += 75;
    }
    check_for_achievement();
}
void first_setup()
{
    enemy1_left_alive = false;//false
    enemy2_up_alive = false;//false
    enemy3_down_alive = false;//false
    enemy4_right_alive = false;//false
    wave_count = 1;//must be 1
    kills_on_map = 0;//must be 0
    game_end_win = false;//false
    shot = false;//false
    wave = true;//true
    x = 2;
    y = 2;
    look = "RIGHT";
    enemy1_x = 55;
    enemy1_y = 2;
    enemy2_x = 3;
    enemy2_y = 27;
    enemy3_x = 51;
    enemy3_y = 8;
    enemy4_x = 15;
    enemy4_y = 26;
    if(difficulty_level == 1)
    {
        enemy1_hp = difficulty_lv1_hp;
        enemy2_hp = difficulty_lv1_hp;
        enemy3_hp = difficulty_lv1_hp;
        enemy4_hp = difficulty_lv1_hp;
    }
    else if(difficulty_level == 2)
    {
        enemy1_hp = difficulty_lv2_hp;
        enemy2_hp = difficulty_lv2_hp;
        enemy3_hp = difficulty_lv2_hp;
        enemy4_hp = difficulty_lv2_hp;
    }
    else
    {
        enemy1_hp = difficulty_lv3_hp;
        enemy2_hp = difficulty_lv3_hp;
        enemy3_hp = difficulty_lv3_hp;
        enemy4_hp = difficulty_lv3_hp;
    }
}
void player_spawn()
{
    if(look == "RIGHT")
    {
        map[y][x] = player;
        map[y][x + 1] = player;
        map[y][x + 2] = player;
        map[y + 1][x] = player;
        map[y + 1][x - 1] = player;
        map[y - 1][x] = player;
        map[y - 1][x - 1] = player;
    }
}
//-----------------------------------------------------/
void the_actual_game_fc()
{
    first_setup();
    game_running = true;
    while(game_running == true)
    {
        print();
        //-----------------------------enemy spawn-------------------------------------//
        if(wave == true)
        {
            player_spawn();
            spawn_enemy(enemy1_y, enemy1_x, "LEFT");
            enemy1_left_alive = true;
            spawn_enemy(enemy2_y, enemy2_x, "UP");
            enemy2_up_alive = true;
            spawn_enemy(enemy3_y, enemy3_x, "DOWN");
            enemy3_down_alive = true;
            spawn_enemy(enemy4_y, enemy4_x, "RIGHT");
            enemy4_right_alive = true;
            wave = false;
        }
        //----------------------------MOVEMENT---------------------------------------//
        if(look == "RIGHT")
        {
            if(GetAsyncKeyState(VK_SPACE))
            {
                if(shot == false)
                {
                    shot_look = look;
                    shot_x = x + 3;
                    shot_y = y;
                    shot = true;
                }
            }
            else if(GetAsyncKeyState(VK_DOWN))
            {
                if(map[y][x - 1] == ' ' && map[y - 1][x + 1] == ' ' && map[y + 2][x] == ' ')
                {
                    map[y + 1][x - 1] = ' ';
                    map[y - 1][x] = ' ';
                    map[y][x + 2] = ' ';
                    map[y][x - 1] = player;
                    map[y - 1][x + 1] = player;
                    map[y + 2][x] = player;
                    look = "DOWN";
                }
            }
            if(GetAsyncKeyState(VK_UP))
            {
                if(map[y - 2][x] == ' ' && map[y][x - 1] == ' ' && map[y + 1][x + 1] == ' ')
                {
                    map[y + 1][x] = ' ';
                    map[y][x + 2] = ' ';
                    map[y - 1][x - 1] = ' ';
                    map[y + 1][x + 1] = player;
                    map[y][x - 1] = player;
                    map[y - 2][x] = player;
                    look = "UP";
                }
            }
            if(GetAsyncKeyState(VK_LEFT))
            {
                if(map[y][x - 1] == ' ' && map[y][x - 2] == ' ' && map[y - 1][x + 1] == ' ' && map[y + 1][x + 1] == ' ')
                {
                    map[y][x + 1] = ' ';
                    map[y][x + 2] = ' ';
                    map[y - 1][x - 1] = ' ';
                    map[y + 1][x - 1] = ' ';
                    map[y][x - 1] = player;
                    map[y][x - 2] = player;
                    map[y - 1][x + 1] = player;
                    map[y + 1][x + 1] = player;
                    look = "LEFT";
                }
            }
            if(GetAsyncKeyState(VK_RIGHT))
            {
                if(map[y + 1][x + 2] == ' ' && map[y - 1][x + 2] == ' ' && map[y][x + 3] == ' ' && map[y - 1][x + 1] == ' ' && map[y + 1][x + 1] == ' ')
                {
                    map[y - 1][x - 1] = ' ';
                    map[y - 1][x] = ' ';
                    map[y + 1][x - 1] = ' ';
                    map[y + 1][x] = ' ';
                    map[y][x] = ' ';
                    map[y][x + 1] = ' ';
                    map[y][x + 2] = ' ';
                    x++;
                    map[y - 1][x - 1] = player;
                    map[y - 1][x] = player;
                    map[y + 1][x - 1] = player;
                    map[y + 1][x] = player;
                    map[y][x] = player;
                    map[y][x + 1] = player;
                    map[y][x + 2] = player;
                }
            }
        }
        else if (look == "LEFT")
        {
            if(GetAsyncKeyState(VK_SPACE))
            {
                if(shot == false)
                {
                    shot_look = look;
                    shot_x = x - 3;
                    shot_y = y;
                    shot = true;
                }
            }
            else if(GetAsyncKeyState(VK_DOWN))
            {
                if(map[y][x + 1] == ' ' && map[y - 1][x - 1] == ' ' && map[y + 2][x] == ' ')
                {
                    map[y + 1][x + 1] = ' ';
                    map[y - 1][x] = ' ';
                    map[y][x - 2] = ' ';
                    map[y][x + 1] = player;
                    map[y - 1][x - 1] = player;
                    map[y + 2][x] = player;
                    look = "DOWN";
                }
            }
            if(GetAsyncKeyState(VK_UP))
            {
                if(map[y - 2][x] == ' ' && map[y][x + 1] == ' ' && map[y + 1][x - 1] == ' ')
                {
                    map[y + 1][x] = ' ';
                    map[y][x - 2] = ' ';
                    map[y - 1][x + 1] = ' ';
                    map[y + 1][x - 1] = player;
                    map[y][x + 1] = player;
                    map[y - 2][x] = player;
                    look = "UP";
                }
            }
            if(GetAsyncKeyState(VK_LEFT))
            {
                if(map[y + 1][x - 2] == ' ' && map[y - 1][x - 2] == ' ' && map[y][x - 3] == ' ' && map[y - 1][x - 1] == ' ' && map[y + 1][x - 1] == ' ')
                {
                    map[y - 1][x + 1] = ' ';
                    map[y - 1][x] = ' ';
                    map[y + 1][x + 1] = ' ';
                    map[y + 1][x] = ' ';
                    map[y][x] = ' ';
                    map[y][x - 1] = ' ';
                    map[y][x - 2] = ' ';
                    x--;
                    map[y - 1][x + 1] = player;
                    map[y - 1][x] = player;
                    map[y + 1][x + 1] = player;
                    map[y + 1][x] = player;
                    map[y][x] = player;
                    map[y][x - 1] = player;
                    map[y][x - 2] = player;
                }
            }
            if(GetAsyncKeyState(VK_RIGHT))
            {
                if(map[y][x + 1] == ' ' && map[y][x + 2] == ' ' && map[y - 1][x - 1] == ' ' && map[y + 1][x - 1] == ' ')
                {
                    map[y][x - 1] = ' ';
                    map[y][x - 2] = ' ';
                    map[y - 1][x + 1] = ' ';
                    map[y + 1][x + 1] = ' ';
                    map[y][x + 1] = player;
                    map[y][x + 2] = player;
                    map[y - 1][x - 1] = player;
                    map[y + 1][x - 1] = player;
                    look = "RIGHT";
                }
            }
        }
        else if (look == "UP")
        {
            if(GetAsyncKeyState(VK_SPACE))
            {
                if(shot == false)
                {
                    shot_look = look;
                    shot_x = x;
                    shot_y = y - 3;
                    shot = true;
                }
            }
            else if(GetAsyncKeyState(VK_DOWN))
            {
                if(map[y + 1][x] == ' ' && map[y + 2][x] == ' ' && map[y - 1][x - 1] == ' ' && map[y - 1][x + 1] == ' ')
                {
                    map[y - 1][x] = ' ';
                    map[y - 2][x] = ' ';
                    map[y + 1][x - 1] = ' ';
                    map[y + 1][x + 1] = ' ';
                    map[y - 1][x - 1] = player;
                    map[y - 1][x + 1] = player;
                    map[y + 1][x] = player;
                    map[y + 2][x] = player;
                    look = "DOWN";
                }
            }
            if(GetAsyncKeyState(VK_UP))
            {
                if(map[y - 2][x + 1] == ' ' && map[y - 2][x - 1] == ' ' && map[y - 3][x] == ' ' && map[y - 1][x - 1] == ' ' && map[y - 1][x + 1] == ' ')
                {
                    map[y + 1][x - 1] = ' ';
                    map[y + 1][x + 1] = ' ';
                    map[y][x] = ' ';
                    map[y][x + 1] = ' ';
                    map[y][x - 1] = ' ';
                    map[y - 1][x] = ' ';
                    map[y - 2][x] = ' ';
                    y--;
                    map[y + 1][x - 1] = player;
                    map[y + 1][x + 1] = player;
                    map[y][x] = player;
                    map[y][x + 1] = player;
                    map[y][x - 1] = player;
                    map[y - 1][x] = player;
                    map[y - 2][x] = player;
                }
            }
            if(GetAsyncKeyState(VK_LEFT))
            {
                if(map[y][x - 2] == ' ' && map[y - 1][x - 1] == ' ' && map[y + 1][x] == ' ')
                {
                    map[y - 2][x] = ' ';
                    map[y][x + 1] = ' ';
                    map[y + 1][x - 1] = ' ';
                    map[y - 1][x + 1] = player;
                    map[y + 1][x] = player;
                    map[y][x - 2] = player;
                    look = "LEFT";
                }
            }
            if(GetAsyncKeyState(VK_RIGHT))
            {
                if(map[y][x + 2] == ' ' && map[y - 1][x - 1] == ' ' && map[y + 1][x] == ' ')
                {
                    map[y - 2][x] = ' ';
                    map[y][x - 1] = ' ';
                    map[y + 1][x + 1] = ' ';
                    map[y][x + 2] = player;
                    map[y - 1][x - 1] = player;
                    map[y + 1][x] = player;
                    look = "RIGHT";
                }
            }
        }
        else if (look == "DOWN")
        {
            if(GetAsyncKeyState(VK_SPACE))
            {
                if(shot == false)
                {
                    shot_look = look;
                    shot_x = x;
                    shot_y = y + 3;
                    shot = true;
                }
            }
            else if(GetAsyncKeyState(VK_DOWN))
            {
                if(map[y + 2][x + 1] == ' ' && map[y + 2][x - 1] == ' ' && map[y + 3][x] == ' ' && map[y + 1][x - 1] == ' ' && map[y + 1][x + 1] == ' ')
                {
                    map[y - 1][x - 1] = ' ';
                    map[y - 1][x + 1] = ' ';
                    map[y][x] = ' ';
                    map[y][x + 1] = ' ';
                    map[y][x - 1] = ' ';
                    map[y + 1][x] = ' ';
                    map[y + 2][x] = ' ';
                    y++;
                    map[y - 1][x - 1] = player;
                    map[y - 1][x + 1] = player;
                    map[y][x] = player;
                    map[y][x + 1] = player;
                    map[y][x - 1] = player;
                    map[y + 1][x] = player;
                    map[y + 2][x] = player;
                }
            }
            if(GetAsyncKeyState(VK_UP))
            {
                if(map[y - 1][x] == ' ' && map[y - 2][x] == ' ' && map[y + 1][x + 1] == ' ' && map[y + 1][x - 1] == ' ')
                {
                    map[y - 1][x - 1] = ' ';
                    map[y - 1][x + 1] = ' ';
                    map[y + 1][x] = ' ';
                    map[y + 2][x] = ' ';
                    map[y - 1][x] = player;
                    map[y - 2][x] = player;
                    map[y + 1][x + 1] = player;
                    map[y + 1][x - 1] = player;
                    look = "UP";
                }
            }
            if(GetAsyncKeyState(VK_LEFT))
            {
                if(map[y][x - 2] == ' ' && map[y + 1][x + 1] == ' ' && map[y - 1][x] == ' ')
                {
                    map[y + 2][x] = ' ';
                    map[y][x + 1] = ' ';
                    map[y - 1][x - 1] = ' ';
                    map[y + 1][x + 1] = player;
                    map[y - 1][x] = player;
                    map[y][x - 2] = player;
                    look = "LEFT";
                }
            }
            if(GetAsyncKeyState(VK_RIGHT))
            {
                if(map[y][x + 2] == ' ' && map[y + 1][x - 1] == ' ' && map[y - 1][x] == ' ')
                {
                    map[y + 2][x] = ' ';
                    map[y][x - 1] = ' ';
                    map[y - 1][x + 1] = ' ';
                    map[y + 1][x - 1] = player;
                    map[y - 1][x] = player;
                    map[y][x + 2] = player;
                    look = "RIGHT";
                }
            }
        }
        //----------------------------SHOOTING----------------------------------//
        if(shot == true)
        {
            if(shot_look == "RIGHT")
            {
                if(map[shot_y][shot_x - 1] == bullet)
                {
                    map[shot_y][shot_x - 1] = ' ';
                }
                if(map[shot_y][shot_x] == ' ')
                {
                    map[shot_y][shot_x] = bullet;
                    shot_x++;
                }
                else
                {
                    shot = false;
                }
            }
            if(shot_look == "LEFT")
            {
                if(map[shot_y][shot_x + 1] == bullet)
                {
                    map[shot_y][shot_x + 1] = ' ';
                }
                if(map[shot_y][shot_x] == ' ')
                {
                    map[shot_y][shot_x] = bullet;
                    shot_x--;
                }
                else
                {
                    shot = false;
                }
            }
            if(shot_look == "UP")
            {
                if(map[shot_y + 1][shot_x] == bullet)
                {
                    map[shot_y + 1][shot_x] = ' ';
                }
                if(map[shot_y][shot_x] == ' ')
                {
                    map[shot_y][shot_x] = bullet;
                    shot_y--;
                }
                else
                {
                    shot = false;
                }
            }
            if(shot_look == "DOWN")
            {
                if(map[shot_y - 1][shot_x] == bullet)
                {
                    map[shot_y - 1][shot_x] = ' ';
                }
                if(map[shot_y][shot_x] == ' ')
                {
                    map[shot_y][shot_x] = bullet;
                    shot_y++;
                }
                else
                {
                    shot = false;
                }
            }
        }
        //---------------------------------ENEMIES-------------------------------------//
        if(enemy1_left_alive == true)
        {
            if(shot == true)
            {
                if((shot_x == enemy1_x && shot_y == enemy1_y) || (shot_x == enemy1_x - 1 && shot_y == enemy1_y) || (shot_x == enemy1_x && shot_y == enemy1_y - 1) || (shot_x == enemy1_x + 1 && shot_y == enemy1_y - 1) || (shot_x == enemy1_x && shot_y == enemy1_y + 1) || (shot_x == enemy1_x + 1 && shot_y == enemy1_y + 1))
                {
                    enemy1_hp -= damage;
                }
                if(enemy1_hp <= 0)
                {
                    enemy1_left_alive = false;
                    shot = false;
                    clear_shots_onfield();
                    payment();
                    map[enemy1_y][enemy1_x] = ' ';
                    map[enemy1_y][enemy1_x - 1] = ' ';
                    map[enemy1_y - 1][enemy1_x] = ' ';
                    map[enemy1_y - 1][enemy1_x + 1] = ' ';
                    map[enemy1_y + 1][enemy1_x] = ' ';
                    map[enemy1_y + 1][enemy1_x + 1] = ' ';
                    total_kills++;
                    kills_on_map += 1;
                }
            }
            for(int i = 1; i < (map_x - 1) - (map_x - enemy1_x); i++)
            {
                if((x == i && y - 1 == enemy1_y) || (x == i && y + 1 == enemy1_y) || (x == i && y == enemy1_y))
                {
                    if(enemy1_shot == false)
                    {
                        enemy1_shot_x = enemy1_x - 2;
                        enemy1_shot = true;
                    }
                }
            }
        }
        if(enemy1_shot == true)
        {
            if(map[enemy1_y][enemy1_shot_x] == player)
            {
                if(difficulty_level == 1){hp -= difficulty_lv1_damage;}
                else if(difficulty_level == 2){hp -= difficulty_lv2_damage;}
                else{hp -= difficulty_lv3_damage;}
            }
            if(map[enemy1_y][enemy1_shot_x + 1] == bullet)
            {
                map[enemy1_y][enemy1_shot_x + 1] = ' ';
            }
            if(map[enemy1_y][enemy1_shot_x] == ' ')
            {
                map[enemy1_y][enemy1_shot_x] = bullet;
                enemy1_shot_x--;
            }
            else
            {
                enemy1_shot = false;
            }
        }
        //--------------------------//
        if(enemy2_up_alive == true)
        {
            if(shot == true)
            {
                if((shot_x == enemy2_x + 1 && shot_y == enemy2_y + 1) || (shot_x == enemy2_x + 1 && shot_y == enemy2_y)
                || (shot_x == enemy2_x - 1 && shot_y == enemy2_y + 1) || (shot_x == enemy2_x - 1 && shot_y == enemy2_y)
                || (shot_x == enemy2_x && shot_y == enemy2_y - 1) || (shot_x == enemy2_x && shot_y == enemy2_y))
                {
                    enemy2_hp -= damage;
                }
                if(enemy2_hp <= 0)
                {
                    enemy2_up_alive = false;
                    shot = false;
                    clear_shots_onfield();
                    payment();
                    map[enemy2_y][enemy2_x] = ' ';
                    map[enemy2_y - 1][enemy2_x] = ' ';
                    map[enemy2_y][enemy2_x - 1] = ' ';
                    map[enemy2_y + 1][enemy2_x - 1] = ' ';
                    map[enemy2_y][enemy2_x + 1] = ' ';
                    map[enemy2_y + 1][enemy2_x + 1] = ' ';
                    total_kills++;
                    kills_on_map += 1;
                }
            }
            for(int i = 1; i < (map_y - 1) - (map_y - enemy2_y); i++)
            {
                if((x - 1 == enemy2_x && y == i) || (x + 1 == enemy2_x && y == i) || (x == enemy2_x && y == i))
                {
                    if(enemy2_shot == false)
                    {
                        enemy2_shot_y = enemy2_y - 2;
                        enemy2_shot = true;
                    }
                }
            }
        }
        if(enemy2_shot == true)
        {
            if(map[enemy2_shot_y][enemy2_x] == player)
            {
                if(difficulty_level == 1){hp -= difficulty_lv1_damage;}
                else if(difficulty_level == 2){hp -= difficulty_lv2_damage;}
                else{hp -= difficulty_lv3_damage;}
            }
            if(map[enemy2_shot_y + 1][enemy2_x] == bullet)
            {
                map[enemy2_shot_y + 1][enemy2_x] = ' ';
            }
            if(map[enemy2_shot_y][enemy2_x] == ' ')
            {
                map[enemy2_shot_y][enemy2_x] = bullet;
                enemy2_shot_y--;
            }
            else
            {
                enemy2_shot = false;
            }
        }
        //--------------------------//
        if(enemy3_down_alive == true)
        {
            if(shot == true)
            {
                if((shot_x == enemy3_x + 1 && shot_y == enemy3_y - 1) || (shot_x == enemy3_x + 1 && shot_y == enemy3_y)
                || (shot_x == enemy3_x - 1 && shot_y == enemy3_y - 1) || (shot_x == enemy3_x - 1 && shot_y == enemy3_y)
                || (shot_x == enemy3_x && shot_y == enemy3_y + 1) || (shot_x == enemy3_x && shot_y == enemy3_y))
                {
                    enemy3_hp -= damage;
                }
                if(enemy3_hp <= 0)
                {
                    enemy3_down_alive = false;
                    shot = false;
                    clear_shots_onfield();
                    payment();
                    map[enemy3_y][enemy3_x] = ' ';
                    map[enemy3_y + 1][enemy3_x] = ' ';
                    map[enemy3_y][enemy3_x - 1] = ' ';
                    map[enemy3_y - 1][enemy3_x - 1] = ' ';
                    map[enemy3_y][enemy3_x + 1] = ' ';
                    map[enemy3_y - 1][enemy3_x + 1] = ' ';
                    total_kills++;
                    kills_on_map += 1;
                }
            }
            for(int i = enemy3_y + 2; i < 29; i++)
            {
               if((x - 1 == enemy3_x && y == i) || (x + 1 == enemy3_x && y == i) || (x == enemy3_x && y == i))
                {
                    if(enemy3_shot == false)
                    {
                        enemy3_shot_y = enemy3_y + 2;
                        enemy3_shot = true;
                    }
                }
            }
            if(enemy3_shot == true)
            {
                if(map[enemy3_shot_y][enemy3_x] == player)
                {
                    if(difficulty_level == 1){hp -= difficulty_lv1_damage;}
                    else if(difficulty_level == 2){hp -= difficulty_lv2_damage;}
                    else{hp -= difficulty_lv3_damage;}
                }
                if(map[enemy3_shot_y - 1][enemy3_x] == bullet)
                {
                    map[enemy3_shot_y - 1][enemy3_x] = ' ';
                }
                if(map[enemy3_shot_y][enemy3_x] == ' ')
                {
                    map[enemy3_shot_y][enemy3_x] = bullet;
                    enemy3_shot_y++;
                }
                else
                {
                    enemy3_shot = false;
                }
            }
        }
        if(enemy3_shot == true)
        {
            if(map[enemy3_shot_y][enemy3_x] == player)
            {
                if(difficulty_level == 1){hp -= difficulty_lv1_damage;}
                else if(difficulty_level == 2){hp -= difficulty_lv2_damage;}
                else{hp -= difficulty_lv3_damage;}
            }
            if(map[enemy3_shot_y - 1][enemy3_x] == bullet)
            {
                map[enemy3_shot_y - 1][enemy3_x] = ' ';
            }
            if(map[enemy3_shot_y][enemy3_x] == ' ')
            {
                map[enemy3_shot_y][enemy3_x] = bullet;
                enemy3_shot_y++;
            }
            else
            {
                enemy3_shot = false;
            }
        }
        //--------------------------//
        if(enemy4_right_alive == true)
        {
            if(shot == true)
            {
                if((shot_x == enemy4_x && shot_y == enemy4_y) || (shot_x == enemy4_x + 1 && shot_y == enemy4_y) ||
                (shot_x == enemy4_x && shot_y == enemy4_y - 1) || (shot_x == enemy4_x - 1 && shot_y == enemy4_y - 1) ||
                (shot_x == enemy4_x && shot_y == enemy4_y + 1) || (shot_x == enemy4_x - 1 && shot_y == enemy4_y + 1))
                {
                    enemy4_hp -= damage;
                }
                if(enemy4_hp <= 0)
                {
                    enemy4_right_alive = false;
                    shot = false;
                    clear_shots_onfield();
                    payment();
                    map[enemy4_y][enemy4_x] = ' ';
                    map[enemy4_y][enemy4_x + 1] = ' ';
                    map[enemy4_y + 1][enemy4_x] = ' ';
                    map[enemy4_y + 1][enemy4_x - 1] = ' ';
                    map[enemy4_y - 1][enemy4_x] = ' ';
                    map[enemy4_y - 1][enemy4_x - 1] = ' ';
                    total_kills++;
                    kills_on_map += 1;
                }
            }
            for(int i = enemy4_x + 2; i < map_x - 2; i++)
            {
                if((x == i && y + 1 == enemy4_y) || (x == i && y - 1 == enemy4_y) || (x == i && y == enemy4_y))
                {
                    if(enemy4_shot == false)
                    {
                        enemy4_shot_x = enemy4_x + 2;
                        enemy4_shot = true;
                    }
                }
            }
        }
        if(enemy4_shot == true)
        {
            if(map[enemy4_y][enemy4_shot_x] == player)
            {
                if(difficulty_level == 1){hp -= difficulty_lv1_damage;}
                else if(difficulty_level == 2){hp -= difficulty_lv2_damage;}
                else{hp -= difficulty_lv3_damage;}
            }
            if(map[enemy4_y][enemy4_shot_x - 1] == bullet)
            {
                map[enemy4_y][enemy4_shot_x - 1] = ' ';
            }
            if(map[enemy4_y][enemy4_shot_x] == ' ')
            {
                map[enemy4_y][enemy4_shot_x] = bullet;
                enemy4_shot_x++;
            }
            else
            {
                enemy4_shot = false;
            }
        }
        //----------------------------------GAME END------------------------------------//
        if(hp <= 0)
        {
            clear_shots_onfield();
            for(int x = 0; x < map_y; x++)
            {
                for(int y = 0; y < map_x; y++)
                {
                    if(map[x][y] == player)
                    {
                        map[x][y] = ' ';
                    }
                }
            }
            for(int i = 20; i < 34;i++)
            {
                map[15][i] = '#';
            }
            map[16][20] = '#';
            map[16][21] = ' ';
            map[16][22] = 'G';
            map[16][23] = 'A';
            map[16][24] = 'M';
            map[16][25] = 'E';
            map[16][26] = ' ';
            map[16][27] = 'O';
            map[16][28] = 'V';
            map[16][29] = 'E';
            map[16][30] = 'R';
            map[16][31] = '!';
            map[16][32] = ' ';
            map[16][33] = '#';
            for(int i = 20; i < 34;i++)
            {
                map[17][i] = '#';
            }
            print();
            game_running = false;
        }
        if(kills_on_map == 4)// map rearrange
        {
            wave_count++;
            //check_for_achievement();
            if(wave_count == 2)//moving to wave 2
            {
                map[2][28] = ' ';
                map[2][29] = ' ';
                for(int x = 0; x < map_y; x++)
                {
                    for(int y = 0; y < map_x; y++)
                    {
                        if(map[x][y] == player)
                        {
                            map[x][y] = ' ';
                        }
                    }
                }
                if(difficulty_level == 1)
                {
                    enemy1_hp = difficulty_lv1_hp * 1.5;
                    enemy2_hp = difficulty_lv1_hp * 1.5;
                    enemy3_hp = difficulty_lv1_hp * 1.5;
                    enemy4_hp = difficulty_lv1_hp * 1.5;
                }
                if(difficulty_level == 2)
                {
                    enemy1_hp = difficulty_lv2_hp * 1.5;
                    enemy2_hp = difficulty_lv2_hp * 1.5;
                    enemy3_hp = difficulty_lv2_hp * 1.5;
                    enemy4_hp = difficulty_lv2_hp * 1.5;
                }
                if(difficulty_level == 3)
                {
                    enemy1_hp = difficulty_lv3_hp * 1.5;
                    enemy2_hp = difficulty_lv3_hp * 1.5;
                    enemy3_hp = difficulty_lv3_hp * 1.5;
                    enemy4_hp = difficulty_lv3_hp * 1.5;
                }
            //------------------------------------//

                x = 2;
                y = 2;
                look = "RIGHT";
                clear_shots_onfield();
                kills_on_map = 0;
                shot = false;
                wave = true;
            }
            else if(wave_count == 3)
            {
                map[14][17] = ' ';
                map[14][18] = ' ';
                map[14][37] = ' ';
                map[14][36] = ' ';
                map[14][47] = ' ';
                map[14][48] = ' ';
                for(int i = 10; i < 20; i++)
                {
                    map[i][24] = '#';
                    map[i][28] = '#';
                }
                for(int i = 18; i < 22; i++)
                {
                    map[i][31] = '#';
                    map[i][21] = '#';
                }
                for(int i = 10; i > 6; i--)
                {
                    map[i][31] = '#';
                    map[i][21] = '#';
                }
                if(difficulty_level == 1)
                {
                    enemy1_hp = difficulty_lv1_hp * 2;
                    enemy2_hp = difficulty_lv1_hp * 2;
                    enemy3_hp = difficulty_lv1_hp * 2;
                    enemy4_hp = difficulty_lv1_hp * 2;
                }
                if(difficulty_level == 2)
                {
                    enemy1_hp = difficulty_lv2_hp * 2;
                    enemy2_hp = difficulty_lv2_hp * 2;
                    enemy3_hp = difficulty_lv2_hp * 2;
                    enemy4_hp = difficulty_lv2_hp * 2;
                }
                if(difficulty_level == 3)
                {
                    enemy1_hp = difficulty_lv3_hp * 2;
                    enemy2_hp = difficulty_lv3_hp * 2;
                    enemy3_hp = difficulty_lv3_hp * 2;
                    enemy4_hp = difficulty_lv3_hp * 2;
                }
            //----------------------------//
                enemy1_y = 14;
                enemy1_x = 22;
                enemy4_y = 14;
                enemy4_x = 30;
                enemy2_y = 11;
                enemy2_x = 26;
                enemy3_y = 17;
                enemy3_x = 26;
                clear_shots_onfield();
                kills_on_map = 0;
                shot = false;
                wave = true;
            }
            else if(wave_count == 4)
            {
                game_end_win = true;
            }
        }
        if(game_end_win == true)
        {
            clear_shots_onfield();
            for(int i = 20; i < 34;i++)
            {
                map[15][i] = '#';
            }
            map[16][20] = '#';
            map[16][21] = ' ';
            map[16][22] = ' ';
            map[16][23] = 'Y';
            map[16][24] = 'O';
            map[16][25] = 'U';
            map[16][26] = ' ';
            map[16][27] = 'W';
            map[16][28] = 'I';
            map[16][29] = 'N';
            map[16][30] = '!';
            map[16][31] = ' ';
            map[16][32] = ' ';
            map[16][33] = '#';
            for(int i = 20; i < 34;i++)
            {
                map[17][i] = '#';
            }
            print();
            game_running = false;
        }
        //system("pause");
    }
    system("pause");
}

int main()
{
    loading_data();
    check_for_achievement();
    main_menu_text();
    bool program_running = true;
    while(program_running == true)
    {
        main_menu(program_running);
    }
    return 0;
}
