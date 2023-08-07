/** Diana Ryzhkova
 *  id: 117431
 * **/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>          //Oznámenie knižníc
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct vypis{       //Vytvorenie štruktúry

    int id;
    char topic[156];
    struct authors *authors_;
    char type[50];
    char time[6];
    char date[11];

    struct vypis *next;
    struct vypis *pred;

}vypis_t;

typedef struct authors{      //Vytvorenie samostatnej štruktúry pre autorov

    char name[50];
    char surname[250];
    char type;

    struct authors *next;
    struct authors *pred;

}authors_t;

vypis_t *n_order(FILE *p_file,vypis_t *head, vypis_t *tail, int *str_count); //Oznámenie príkazov pre jednoduchú manipuláciu
vypis_t *clear_memory(vypis_t *head);
char v_order(vypis_t *head, int count);
vypis_t *a_order(vypis_t* head, int count);
vypis_t *p_order(vypis_t* head, int *count);
vypis_t *r_order(vypis_t* head, int count);
vypis_t *z_order(vypis_t* head, int *count);

char* get_data(char* str_buf){
    char *str = malloc(sizeof(char)*11);

    strncpy(str, str_buf,4);
    str [4] = '.';
    str [5] = str_buf [4];
    str [6] = str_buf [5];
    str [7] = '.';
    str [8] = str_buf [6];
    str [9] = str_buf [7];
    str [10] = '\0';

    return str;
}

char* get_time(char* str_buf){
    char *str = malloc(sizeof(char)*6);

    //strncpy(str, str_buf, 2);
    str [0] = str_buf [8];
    str [1] = str_buf [9];
    str [2] = ':';
    str [3] = str_buf [10];
    str [4] = str_buf [11];
    str [5] = '\0';
    //printf(str);
    return str;
}

vypis_t * get_vypis(vypis_t * current, int number)     //načítať prvok z prepojeného zoznamu
{
    vypis_t * buf = current;
    int num = 0;
    while (buf->next != NULL && num < number)
    {
        buf = buf->next;
        num++;
    }
    return buf;
}

authors_t * get_author(authors_t  *current, int number)     //načítať prvok z prepojeného zoznamu(pre štruktúru s autormi)
{
    authors_t * buf = current;
    int num = 0;
    while (buf->next != NULL && num < number)
    {
        buf = buf->next;
        num++;
    }
    return buf;
}

int get_num_authors(authors_t * head)           //funkcia na počítanie počtu položiek
{
    if (head == NULL)
        return 0;

    authors_t * tmp = head;            // premenná na označenie head na určitom mieste
    int amount = 1;

    while (tmp->next != NULL)
    {

        amount++;
        tmp = tmp->next;

    }

    return amount;
}

vypis_t * new_record()                       //na vytvorenie prepojeného zoznamu
{
    vypis_t * new_vypis = malloc(sizeof(vypis_t));  //prideľovanie pamäte
    new_vypis->next = NULL;
    new_vypis->pred = NULL;
    return new_vypis;
}

authors_t * new_author()                       //new stracture for name
{
    authors_t * new_aut = malloc(sizeof(authors_t));  //prideľovanie pamäte
    new_aut->next = NULL;
    new_aut->pred = NULL;
    return new_aut;
}


authors_t * pars_names(char *buf_str)          //funkcia na oddelenie mien autorov
{
    // Súbor znakov, ktoré sa majú zahrnúť do hľadaného segmentu
    char sep1[10] = "#";
    char sep2[10] = " ";
    // Premenná, do ktorej sa zapíšu počiatočné adresy častí
    // str
    char str_arr[10][150];
    char* istr1, *istr2, *a_name, *a_surname;

    int a_count = 0;
    authors_t *head = NULL, *tail = NULL, *curr_author;

    // Zvýraznenie prvej časti riadku
    istr1 = strtok(buf_str, sep1);

    // Zvýraznenie nasledujúcich častí
    while (istr1 != NULL)
    {

        strcpy(str_arr[a_count],istr1);
        a_count++;
        // Zvýraznenie ďalšej časti riadku
        istr1 = strtok(NULL, sep1);
    }

    for (int i = 0; i < a_count; i++) {
        istr2 = strtok(str_arr[i], sep2);
        if (strlen(istr2) < 3) {
            curr_author->type = istr2[0];
        } else {
            if (istr2 != NULL) a_name = istr2;
            else a_name = "";
            istr2 = strtok(NULL, sep2);
            if (istr2 != NULL) a_surname = istr2;
            else a_surname = "";
            istr2 = strtok(NULL, sep2);
            while (istr2 != NULL) {
                strcat(a_surname, " ");
                strcat(a_surname, istr2);
                istr2 = strtok(NULL, sep2);
            }

            curr_author = new_author();

            strcpy(curr_author->name, a_name);
            strcpy(curr_author->surname, a_surname);

            if (!head) {
                head = curr_author;
                tail = head;
            } else {
                tail->next = curr_author;
                curr_author->pred = tail;
                tail = curr_author;
            }
        }
    }
    return head;
}

int main() {

    int kol_vo = 0;                               //deklarácia premenných
    char order;
    vypis_t *head_r = NULL;
    vypis_t *tail_r = NULL;
    FILE* p_file = NULL;

    printf("Enter the command:");       //príkazový vstup
    while (scanf(" %c", &order) == 1 && (order != 'k') && (order != 'K')){        //Príkaz na ukončenie{// napíšeme naše menu pre volanie funkcií

        switch (order) {                           //volanie pokynov
            case 'v': {
                printf("\n");
                v_order(head_r, kol_vo);

                break;
            }
            case 'n': {
                printf("\n");
                head_r = n_order(p_file, head_r, tail_r, &kol_vo);
                break;
            }
            case 'r': {
                printf("\n");
                head_r = r_order(head_r, kol_vo);
                break;
            }
            case 'a': {
                printf("\n");
                head_r = a_order(head_r, kol_vo);
                break;
            }
            case 'z': {
                printf("\n");
                head_r = z_order(head_r, &kol_vo);
                break;
            }
            case 'p': {
                printf("\n");
                head_r = p_order(head_r, &kol_vo);
                break;
            }

            default:
                if ((order != 'k') && (order != 'K')) { printf("Wrong values entered\n"); }    //Kontrola správnosti zadanej hodnoty
        }
        printf("Enter the command:");       //príkazový vstup
    }

    if (p_file != NULL)
        fclose(p_file);

    if (head_r)
        clear_memory(head_r);

    return 0;
}

vypis_t *n_order(FILE *p_file,vypis_t *head, vypis_t *tail, int *str_count) {

    struct vypis *current;      //deklarácia premenných
    int s_len = 300;
    char buf_str[s_len];
    char * return_str;

    if (p_file == NULL) {
        p_file = fopen("KonferencnyZoznam2.txt", "r");

        if (p_file == NULL) {
            printf("Neotvoreny subor!");
            exit(1);
        }
    }
    if (head) {

        head = clear_memory(head); //Kontrola existujúcich polí, vymazanie pamäte, ak existujú

    }
    *str_count = 0; //počítadlo záznamov

    fseek(p_file, 0, SEEK_SET); //nastaviť ukazovateľ na začiatok súboru

    while (fgets(buf_str, s_len,p_file) != NULL) {

        if(!stricmp(buf_str, "$$$")){
            printf("miss \n");
            break;
        }

        current = new_record();//alokovať pamäť pre novú položku
        //Čítanie záznamov zo súboru

        current->id = *str_count+1;


        fgets(buf_str, s_len, p_file);
        buf_str[strlen(buf_str) - 1] = '\0';
        strcpy(current->type, buf_str);
        //printf("Type prezentovania: %s\n", current->type);

        fgets(buf_str, s_len, p_file);
        buf_str[strlen(buf_str) - 1] = '\0';
        strcpy(current->topic, buf_str);
        //printf("Topic prezentovania: %s\n", current->topic);

        fgets(buf_str, s_len, p_file);
        buf_str[strlen(buf_str) - 1] = '\0';
        current->authors_=pars_names(buf_str);

        fgets(buf_str, s_len, p_file);
        if (buf_str[strlen(buf_str) -1] == '\n')
            buf_str[strlen(buf_str) - 1] = '\0';
        else buf_str[strlen(buf_str)] = '\0';

        return_str = get_time (buf_str);
        strcpy(current->time, return_str);
        free(return_str);

        return_str = get_data (buf_str);
        strcpy(current->date,  return_str);
        free(return_str);

        *str_count=*str_count+1; //zvýšiť počítadlo záznamov o jednotku

        if (!head) {//ak naša prvá (head) jednotka nie je inicializovaná (nikde nehľadá)
            head = current;

        }    //zadajte údaje z aktuálneho bloku, pretože toto je náš prvý nahraný záznam
        else  // inak oznámiť chvostu, že jeho pole ukazujúce na ďalšiu položku (NULL) teraz ukazuje na oblasť pamäte
        {
            tail->next = current; // aktuálna jednotka prestáva byť kompletizačnou jednotkou a stáva sa ďalším vozňom.
            current->pred = tail;
        }
        tail = current;
        // Z bloku CURRENT sa stane TAIL a jeho pole adresy ďalšieho bloku vyzerá rovnako ako blok CURRENT - do nikam (NULL)
    }

    printf("loaded %d records. \n", *str_count);
    return head;
}

vypis_t *clear_memory(vypis_t *head) { //Čistenie pamäte
    vypis_t *buf;
    authors_t *auth, *buf_name;
    if(head == NULL)
        return head;

    while (head){
        auth = head->authors_;
        while (auth){
            buf_name = auth->next;
            free(auth);
            auth =  buf_name;
        }
        buf = head->next;
        free(head);
        head = buf;
    }

    return head;
}

char v_order(vypis_t *head, int count){

    printf("Records: %d\n", count);


    if (count > 0) {
        for (int i = 0; i < count; i++) {

            vypis_t *buf_rec = get_vypis(head, i);         //loading the current

            printf("%d. \n", i+1);
            printf("ID: %s\n", buf_rec->type);
            printf("Nazov prispevku: %s\n", buf_rec->topic);

            printf("Mena autorov: \n");

            for (int z = 0; z < get_num_authors(buf_rec->authors_); z++) {
                printf("    %d:  ", z+1);
                authors_t *buf_author = get_author(buf_rec->authors_, z);//loading the current
                printf("%s %s (%c)\n", buf_author->name, buf_author->surname, buf_author->type);
            }
            printf("Typ prezentovania: %s\n", buf_rec->type);
            printf("Cas prezentovania: %s\n", buf_rec->time);
            printf("Datum: %s\n", buf_rec->date);
        }
    }
    else
    {
        printf("Empty list of records! \n");
    }
}

vypis_t *r_order(vypis_t* head, int count)
{
    int c1 = 0;
    int c2 = 0;
    scanf("%d %d", &c1, &c2);

    if (c1 <= count && c1 > 0 && c2 <= count && c2 >0 && c1 !=c2)
    {
        c1--;
        c2--;

        vypis_t * temp, * mod1, * mod2;
        mod1 = get_vypis(head, c1);
        mod2 = get_vypis(head, c2);

        temp = mod1->next;         //zmena ďalších prvkov mod
        mod1->next = mod2->next;
        mod2->next = temp;

        temp = mod1->pred;         //zmena ďalších prvkov mod
        mod1->pred = mod2->pred;
        mod2->pred = temp;

        if(mod1->pred != NULL){
            if(abs(c2-c1) == 1){
                if(c2 >c1) mod1->pred = mod2;
            }
            temp=mod1->pred;
            temp->next = mod1;
        }
        else {
            if(abs(c2-c1) == 1) mod1->next = mod2;
            head = mod1;

        }

        if(mod2->pred != NULL){
            if(abs(c2-c1) == 1){
                if(c1 >c2) mod2->pred = mod1;
            }
            temp=mod2->pred;
            temp->next = mod2;
        }
        else {
            if(abs(c2-c1) == 1) mod2->next = mod1;
            head = mod2;
        }

    }

    return head;
}

vypis_t *a_order(vypis_t* head, int count)
{
    long long ent_num;
    char ent_typ[10];
    char st1[34];
    char st2[3];

    while(1)
    {
        scanf("%lld %s", &ent_num, &ent_typ);

        if ((ent_num % 15) != 0 || strlen(ent_typ) != 2 || !(strstr(ent_typ, "PD") || strstr(ent_typ, "UD") ||
            strstr(ent_typ, "PP") || strstr(ent_typ, "UP")))
            printf("Zadane udaje nie su korektne, zadaj novy retazec:\n");   //ak je vstup nesprávny

        else
        {
            ltoa(ent_num, st1, 10);

            for (int i = 0; i < count; i++)
            {
                vypis_t * buf_rec = get_vypis(head, i);

                if (strstr( buf_rec->type, st1))
                {
                    strncpy(st2, buf_rec->type, 2);
                    printf("Prezenter s menom ""%s"" bude prezentovat prispevok %s [%s]\n", buf_rec->topic, ent_typ, st2);
                    strcat(ent_typ, st1 );
                    strcpy(buf_rec->type, ent_typ);     //zmeniť typ
                }
            }
            break;
        }
    }

    return head;
}

vypis_t *z_order(vypis_t* head, int *count)
{
    int sum = *count;
    char name[50], surname[100];
    char buf_str[100];

    scanf("%s%s", &name, &surname);

    strcat(name, " ");
    strcat(name, surname);


    for (int i = 0; i < sum; i++)
    {
        vypis_t * temp = get_vypis(head, i);

        for (int z = 0; z < get_num_authors(temp->authors_); z++) {
            //printf("    %d:  ", z+1);
            authors_t *buf_author = get_author(temp->authors_, z);
            strcpy(buf_str, "");
            strcat(buf_str, buf_author->name);
            strcat(buf_str, " ");
            strcat(buf_str, buf_author->surname);
            if ((strcmpi(buf_str, name) == 0) && (buf_author->type == 'A'))
            {
                if (i > 0 ) get_vypis(head, i - 1)->next = temp->next;
                else head = temp->next;
                printf("Record: %s was deleted. \n", temp->topic);
                free(temp);
                *count = *count-1;

                i--;
                break;
            }

        }
    }

    return head;
}

vypis_t *p_order(vypis_t* head, int *count)
{
    int number = 0;
    vypis_t * tmp1, *tmp2;

    int s_len = 250;
    char buf_str[s_len];
    char * return_str;

    scanf("%d", &number);
    if(number > *count) number = *count+1;

    vypis_t * fresh_pr = new_record();
    fresh_pr->id = number;
    number--;

    getchar();

    gets(buf_str);
    strcpy(fresh_pr->type, buf_str);

    gets(buf_str);
    strcpy(fresh_pr->topic, buf_str);

    gets(buf_str);
    fresh_pr->authors_ =pars_names(buf_str);


    gets(buf_str);
    return_str = get_time (buf_str);
    strcpy(fresh_pr->time, return_str);

    return_str = get_data (buf_str);
    strcpy(fresh_pr->date, return_str) ;

    if(!head) {
        head = fresh_pr;
    }
    else {
        tmp1 = get_vypis(head, number - 1);
        tmp2 = get_vypis(head, number);
        fresh_pr->next = tmp2;
        fresh_pr->pred = tmp1;
        tmp1->next = fresh_pr;
        tmp2->pred = fresh_pr;
    }
    *count=*count+1;

    return head;
}