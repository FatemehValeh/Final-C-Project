#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

unsigned int n;
int cell_num; //number of cells
int player=1, x, y;
int x_choosed_cell, y_choosed_cell;//used when user want to choose his cell


typedef struct{
    int x;
    int y;
    int energy;
    char name[20];
    struct cell*next;
}cell;

void add_cell(cell**head, int x, int y, char name[], int energy){
    printf("*\n");
    cell*new_cell=malloc(sizeof(cell));
    new_cell->x=x;

    new_cell->y=y;

    strcpy(new_cell->name, name);

    new_cell->energy=energy;
    printf("energy=%d\n", new_cell->energy);

    cell*cur=*head;
    new_cell->next=NULL;
    if(*head==NULL){
        *head=new_cell;
    }
    else{
        for(cur; cur->next!=NULL; cur=cur->next);
        cur->next=new_cell;
    }
}

void remove_cell(cell**head, cell*found){
    cell*curr=*head;
    if(*head==found){
        *head=found->next;
        free(found);
        return;
    }
    while(curr!=NULL && curr->next!=found){
        curr=curr->next;
    }
    curr->next=found->next;
    free(found);
}

bool not_in_arr(int temp[6], int x){
    int i, counter=0;
    for(i=0; i<6; i++){
        if(temp[i]==x)
            counter++;
    }
    if(counter==0)
        return true;
    else
        return false;
}
/*bool check_mitosis(unsigned char map[n][n], int x, int y, int table[n][n], cell*found){
    int p, temp[6], i=0, counter=0;
    while(p<6){
        p=1;
        if(is_allowed_block(map, table, x, y-1, n)){
            temp[i]=p;
            i++;
            counter++;
        }
        p=2;
        if(is_allowed_block(map, table, x, y+1, n)){}
    }
    /*do{
        p=rand()%6+1;
        temp[i]=p;
        i++;
        counter++;
        printf("temp[%d]= %d , counter= %d\n", i, p, counter);
    }while(not_in_arr(temp, p));
    if(map[y][x]=='2' && found->energy >= 80  ){
        return true;
    }
    else{
        printf("can not split\n");
        return false;
    }
}*/

int neighbor(int table[n][n], int x, int y){
    int p;

    p= rand()%6+1;

}

/*bool is_allowed_block(unsigned char map[n][n], int table[n][n], int x, int y, unsigned int n){
    if( !(forbidden(map, x, y)) && !(occupied_table(table, x, y)) && in_map(n, x, y) ){
        return true;
    }
    else
        return false;
}*/
/*void mitose(unsigned char map[n][n], int table[n][n], cell*found , cell**head){
    int x, y;
    x=found->x;
    y=found->y;
    char name[20];
    strcpy(name, found->name);
    if(check_mitosis(map, x,y,table , found)){
        remove_cell(head, found);
        //add_cell(head, , , name, 40);

    }
}
*/
int rand_loc(){
    return rand()%n;
}

bool forbidden(unsigned char map[n][n], int x, int y){
    if(map[y][x]=='3'){
        printf("**forbidden\n");
        return true;
    }
    else
        return false;
}

bool occupied_table(int table[n][n], int x, int y){
    if(table[y][x]!= 0){
        printf("x=%d y=%d occupied\n", x, y);
         return true;
    }

    else
        return false;
}
bool in_map(unsigned int n, int x, int y){
    if(x>=0 && x<=n && y>=0 && y<=n)
        return true;
    else
        printf("not in map\n");
        return false;
}


/*void fill_table(int table[n][n], int x, int y, int player){ }//player=1 for single player, player=2 for second player
    table[y][x]=player;
}*/

void get_cells(cell**head, unsigned char map[n][n], int table[n][n]){
    printf("Please enter the number of your cells\n");
    scanf("%d", &cell_num);
    int t;
    for(t=0; t<cell_num; t++){
        printf("Please enter the name of the cell(It must be less than 20 characters)\n");
        char name[200];
        scanf("%s", name);
        getchar();
        printf("name is %s\n", name);
        x=rand_loc();
        printf("x=%d\n", x);
        y=rand_loc();
        printf("y=%d\n", y);
        while( forbidden(map, x, y) || occupied_table(table, x, y) ){
            printf("loop\n");
            x=rand_loc();
            printf("1x=%d\n", x);
            y=rand_loc();
            printf("1y=%d\n", y);
            printf("1map[%d][%d] = %c\n", y , x, map[y][x]);
            printf("1table[%d][%d] = %d\n", y, x , table[y][x]);
        }
        //fill_table(table, x, y, player);
        table[y][x]=player;
        add_cell(head, x, y, name, 0);
        printf("map[%d][%d] = %c\n", y , x, map[y][x]);
        printf("table[%d][%d] = %d\n", y, x , table[y][x]);

    }
}

void print_arr(int table[n][n]){
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
}
void print_list(cell*head){
    cell*curr=head;
    printf("cell_num in func=%d\n", cell_num);
    int i=1;
    while(curr!=NULL){
        printf("[%d] %s (%d,%d) energy:%d\n", i, curr->name, curr->x, curr->y, curr->energy);
        curr=curr->next;
        i++;
    }
    /*for(i=1; i<=cell_num , curr!=NULL; i++, curr=curr->next){
        printf("[%d] %s (%d,%d)\n", i, curr->name, curr->x, curr->y);
    }*/
}
void select_cell(cell*head){
    printf("Please choose one of your cells by its x and y\n");
    print_list(head);
    printf("x=");
    scanf("%d", &x_choosed_cell);
    printf("y=");
    scanf("%d", &y_choosed_cell);

}
cell* find_cell(cell*head, int x, int y){
    cell*curr=head;
    while(curr!=NULL && (curr->x!=x || curr->y!=y) ){
        curr=curr->next;
    }
    return curr;
}
void show_main_menu(){
    printf("[1]Move\n[2]Split a cell\n[3]Boost energy\n[4]Save\n[5]Exit\n");
}
void show_first_menu(){
    printf("[1]Load\n[2]New single player game\n[3]New multi player game\n[4]Exit\n");
}
void move_menu(unsigned char map[n][n], int table[n][n], cell*head, int x_choosed_cell, int y_choosed_cell){
    printf("[1]North\n[2]South\n[3]Northeast\n[4]Northwest\n[5]Southeast\n[6]southwest\n");
    int dest;
    scanf("%d", &dest);
    move(dest, map, table, head, x_choosed_cell, y_choosed_cell);
}
void move_north(unsigned char map[n][n], int table[n][n], cell*found, int x_choosed_cell, int y_choosed_cell){
    if( !(forbidden(map, x_choosed_cell, y_choosed_cell-1)) && !(occupied_table(table,x_choosed_cell, y_choosed_cell-1)) && in_map(n, x_choosed_cell, y_choosed_cell-1) ){
        printf("1\n");
        table[y_choosed_cell][x_choosed_cell]=0;
        table[y_choosed_cell-1][x_choosed_cell]=1;
        found->y=y_choosed_cell-1;
    }
}

void move_south(unsigned char map[n][n], int table[n][n], cell*found, int x_choosed_cell, int y_choosed_cell){
    if( !(forbidden(map, x_choosed_cell, y_choosed_cell+1)) && !(occupied_table(table,x_choosed_cell, y_choosed_cell+1)) && in_map(n, x_choosed_cell, y_choosed_cell+1) ){
        printf("2\n");
        table[y_choosed_cell][x_choosed_cell]=0;
        table[y_choosed_cell+1][x_choosed_cell]=1;
        found->y=y_choosed_cell+1;
    }
}

void evmove_northeast(unsigned char map[n][n], int table[n][n], cell*found, int x_choosed_cell, int y_choosed_cell){
    if( !(forbidden(map, x_choosed_cell+1, y_choosed_cell-1)) && !(occupied_table(table,x_choosed_cell+1, y_choosed_cell-1)) && in_map(n, x_choosed_cell+1, y_choosed_cell-1) ){
        printf("ev3\n");
        table[y_choosed_cell][x_choosed_cell]=0;
        table[y_choosed_cell-1][x_choosed_cell+1]=1;
        found->x=x_choosed_cell+1;
        found->y=y_choosed_cell-1;
    }
}

void odmove_northeast(unsigned char map[n][n], int table[n][n], cell*found, int x_choosed_cell, int y_choosed_cell){
    if( !(forbidden(map, x_choosed_cell+1, y_choosed_cell)) && !(occupied_table(table,x_choosed_cell+1, y_choosed_cell)) && in_map(n, x_choosed_cell+1, y_choosed_cell) ){
        printf("od3\n");
        table[y_choosed_cell][x_choosed_cell]=0;
        table[y_choosed_cell][x_choosed_cell+1]=1;
        found->x=x_choosed_cell+1;
        found->y=y_choosed_cell;
    }
}

void evmove_northwest(unsigned char map[n][n], int table[n][n], cell*found, int x_choosed_cell, int y_choosed_cell){
    if( !(forbidden(map, x_choosed_cell-1, y_choosed_cell-1)) && !(occupied_table(table,x_choosed_cell-1, y_choosed_cell-1)) && in_map(n, x_choosed_cell-1, y_choosed_cell-1) ){
        printf("ev4\n");
        table[y_choosed_cell][x_choosed_cell]=0;
        table[y_choosed_cell-1][x_choosed_cell-1]=1;
        found->x=x_choosed_cell-1;
        found->y=y_choosed_cell-1;
    }
}

void odmove_northwest(unsigned char map[n][n], int table[n][n], cell*found, int x_choosed_cell, int y_choosed_cell){
    if( !(forbidden(map, x_choosed_cell-1, y_choosed_cell)) && !(occupied_table(table,x_choosed_cell-1, y_choosed_cell)) && in_map(n, x_choosed_cell-1, y_choosed_cell) ){
        printf("od4\n");
        table[y_choosed_cell][x_choosed_cell]=0;
        table[y_choosed_cell][x_choosed_cell-1]=1;
        found->x=x_choosed_cell-1;
        found->y=y_choosed_cell;
    }
}

void evmove_southeast(unsigned char map[n][n], int table[n][n], cell*found, int x_choosed_cell, int y_choosed_cell){
    if( !(forbidden(map, x_choosed_cell+1, y_choosed_cell)) && !(occupied_table(table,x_choosed_cell+1, y_choosed_cell)) && in_map(n, x_choosed_cell+1, y_choosed_cell) ){
        printf("ev5\n");
        table[y_choosed_cell][x_choosed_cell]=0;
        table[y_choosed_cell][x_choosed_cell+1]=1;
        found->x=x_choosed_cell+1;
        found->y=y_choosed_cell;
    }
}

void odmove_southeast(unsigned char map[n][n], int table[n][n], cell*found, int x_choosed_cell, int y_choosed_cell){
    if( !(forbidden(map, x_choosed_cell+1, y_choosed_cell+1)) && !(occupied_table(table,x_choosed_cell+1, y_choosed_cell+1)) && in_map(n, x_choosed_cell+1, y_choosed_cell+1) ){
        printf("od5\n");
        table[y_choosed_cell][x_choosed_cell]=0;
        table[y_choosed_cell+1][x_choosed_cell+1]=1;
        found->x=x_choosed_cell+1;
        found->y=y_choosed_cell+1;
    }
}

void evmove_southwest(unsigned char map[n][n], int table[n][n], cell*found, int x_choosed_cell, int y_choosed_cell){
    if( !(forbidden(map, x_choosed_cell-1, y_choosed_cell)) && !(occupied_table(table,x_choosed_cell-1, y_choosed_cell)) && in_map(n, x_choosed_cell-1, y_choosed_cell) ){
        printf("ev6\n");
        table[y_choosed_cell][x_choosed_cell]=0;
        table[y_choosed_cell][x_choosed_cell-1]=1;
        found->x=x_choosed_cell-1;
        found->y=y_choosed_cell;
    }
}

void odmove_southwest(unsigned char map[n][n], int table[n][n], cell*found, int x_choosed_cell, int y_choosed_cell){
    if( !(forbidden(map, x_choosed_cell-1, y_choosed_cell+1)) && !(occupied_table(table,x_choosed_cell-1, y_choosed_cell+1)) && in_map(n, x_choosed_cell-1, y_choosed_cell+1) ){
        printf("od6\n");
        table[y_choosed_cell][x_choosed_cell]=0;
        table[y_choosed_cell+1][x_choosed_cell-1]=1;
        found->x=x_choosed_cell-1;
        found->y=y_choosed_cell+1;
    }
}

void move(int dest, unsigned char map[n][n], int table[n][n], cell*head, int x_choosed_cell, int y_choosed_cell){
    cell*curr=head;
    cell*found=find_cell(head, x_choosed_cell, y_choosed_cell);
    switch (dest){
    case 1:
        move_north(map, table, found, x_choosed_cell, y_choosed_cell);
        break;
    case 2:
        move_south(map, table, found, x_choosed_cell, y_choosed_cell);
        break;
    case 3:
        if(x_choosed_cell%2==0){
            evmove_northeast(map, table, found, x_choosed_cell, y_choosed_cell);
            break;
        }
        else{
            odmove_northeast(map, table, found, x_choosed_cell, y_choosed_cell);
            break;
        }
    case 4:
        if(x_choosed_cell%2==0){
            evmove_northwest(map, table, found, x_choosed_cell, y_choosed_cell);
            break;
        }
        else{
            odmove_northwest(map, table, found, x_choosed_cell, y_choosed_cell);
            break;
        }
    case 5:
        if(x_choosed_cell%2==0){
            evmove_southeast(map, table, found, x_choosed_cell, y_choosed_cell);
            break;
        }
        else{
            odmove_southeast(map, table, found, x_choosed_cell, y_choosed_cell);
            break;
        }
    case 6:
        if(x_choosed_cell%2==0){
            evmove_southwest(map, table, found, x_choosed_cell, y_choosed_cell);
            break;
        }
        else{
            odmove_southwest(map, table, found, x_choosed_cell, y_choosed_cell);
            break;
        }

    }
}

bool is_energy_block(unsigned char map[n][n], int x, int y){
    if(map[y][x]=='1')
        return true;
    else{
        printf("can not boost energy\n");
        return false;
    }
}

void boost_energy(cell*found, int energy[n][n], unsigned char map[n][n]){
    int x, y, energy1;
    x=found->x;
    y=found->y;
    energy1=found->energy;
    if(is_energy_block(map, x,y)){
            printf("if\n");
        if(energy[y][x]>=15 && energy1<=85){
            energy[y][x]=energy[y][x]-15;
            (found->energy)=(found->energy)+15;
            return;
        }
        else if(energy[y][x]>=15 && energy1>85){
            int tmp=100-energy1;
            energy[y][x]=energy[y][x]-tmp;
            found->energy=100;
            return;
        }
        else if(energy[y][x]<15){
            int tmp2=100-energy[y][x];
            if(energy1<=tmp2){
                (found->energy)=(found->energy)+energy[y][x];
                energy[y][x]=0;
                map[y][x]='4';
                return;
            }
        }
    }
}

void save(cell*head, unsigned char map[n][n]){
    printf("***|n=%d\n", n);
    int i, j;
    for(i=0; i<n; i++){
    for(j=0; j<n; j++){
        printf("***|map[%d][%d]= %c\n", i , j, map[i][j]);
    }

}
    FILE* savecells=fopen("D:\savecells.txt", "w");
    cell*temp=head;
    while(temp!=NULL){
        fprintf(savecells,"%s\nx=%d y=%d\nenergy=%d\n", temp->name, temp->x, temp->y, temp->energy );
        temp=temp->next;
    }
    fclose(savecells);
    FILE *savemap=fopen("D:\savemap.bin", "wb");
    cell*curr=head;
    int q,w;
    fwrite(&n, sizeof(unsigned int), 1 , savemap);
    for(q=0; q<n; q++){
        for(w=0; w<n; w++){
                printf("%c\n", map[q][w]);
            fwrite(&map[q][w], sizeof(unsigned char),1,savemap);
            printf("**\n");
        }
    }
}

cell* load(unsigned char map[n][n], int energy[n][n], int table[n][n]){

    FILE* openmap=fopen("D:\savemap.bin", "rb");
    fread(&n, sizeof(n), 1, openmap);
    printf("opened n=%ld\n", n);
    int t, k;
    memset(table, 0, sizeof(table)*2*2);
    for(t=0; t<n; t++){
        for(k=0; k<n; k++){
            printf("t=%d k=%d\n",t, k);
            //printf("*in loop energy[%d][%d]=%d\n",t, k, energy[t][k]);
            //printf("*in loop table[%d][%d]=%d\n",t, k, table[t][k]);

            energy[t][k]=0;
            //table[t][k]=0;
        //sleep(7);
            fread(&map[t][k], sizeof(unsigned char), 1, openmap);
            printf("in loop map[%d][%d]=%c\n",t, k, map[t][k]);
            printf("in loop energy[%d][%d]=%d\n",t, k, energy[t][k]);
            printf("in loop table[%d][%d]=%d\n",t, k, table[t][k]);
            if(map[t][k]=='1'){
                energy[t][k]=100;
            }
        }
    }
    printf("22\n");
    fclose(openmap);
    FILE* opencells=fopen("D:\savecells.txt", "r");
    printf("33\n");
    cell*head=malloc(sizeof(cell));
    head=NULL;
    char name[20];
    int x, y, energy1;
    while( !feof(opencells) ){
        fscanf(opencells, "%s\nx=%d y=%d\nenergy=%d\n", name, &x, &y, &energy1);
        printf("in file: %s\nx=%d y=%d\nenergy=%d\n",name, x, y, energy1);
        table[y][x]=1;
        printf("in file: table[%d][%d] = %d\n", y , x , table[y][x]);
        add_cell(&head, x,y, name, energy1);
        printf("44\n");
    }
    fclose(opencells);
    int v, p;
    for(v=0; v<n; v++){
                for(p=0; p<n; p++){
                    printf("*map[%d][%d]= %c\n", v, p , map[v][p]);
                    printf("*table[%d][%d]= %d\n", v, p , table[v][p]);
                    printf("*energy[%d][%d]= %d\n", v, p , energy[v][p]);
                }
            }

    return head;
}

void play_game(cell*head, unsigned char map[n][n], int table[n][n], int energy[n][n]){

    cell*founded;
int i, j;
    while(1){
                select_cell(head);
                show_main_menu();
                int second_decide;
                scanf("%d", &second_decide);
                switch(second_decide){
                case 1:
                    printf("x_choosed , y_choosed are %d %d\n", x_choosed_cell, y_choosed_cell);
                    move_menu(map, table , head, x_choosed_cell, y_choosed_cell);
                    print_arr(table);
                    break;
                case 2:
                    break;
                case 3:
                    founded=find_cell(head, x_choosed_cell, y_choosed_cell);
                    boost_energy(founded, energy, map);
                    break;
                case 4:

                    for(i=0; i<n; i++){
                        for(j=0; j<n; j++){
                            printf("***map[%d][%d]= %c\n", i , j, map[i][j]);
                        }

                    }
                    save(head,map);
                    break;
                case 5:
                    exit(0);

                }
            }

}
int main()
{
    srand(time(NULL));
    printf("welcome\n");

    FILE* fpp;
    cell*head;
    cell*head1;
    cell*head2;

    while(1){
        show_first_menu();
        int first_decide;
        scanf("%d", &first_decide);
        if(first_decide==1){
            unsigned char map[n][n];
            int table[n][n];//store cells; 0 means that block is void of cells, 1 for single player cells and 2 for second player cells
            int energy[n][n];//stores energy sources
            cell*head=load(map, energy, table);
            printf("%d*********\n", n);
            int v, p;
            for(v=0; v<n; v++){
                for(p=0; p<n; p++){
                    printf("map[%d][%d]= %c\n", v, p , map[v][p]);
                    printf("table[%d][%d]= %d\n", v, p , table[v][p]);
                    printf("energy[%d][%d]= %d\n", v, p , energy[v][p]);
                }
            }
            play_game(head, map,table,energy);
            break;
        }
        if(first_decide==2){
            fpp=fopen("D:\map.bin", "rb");
            fread(&n, sizeof(n), 1, fpp);
            printf("n=%ld\n", n);
            unsigned char map[n][n];
            int table[n][n];//store cells; 0 means that block is void of cells, 1 for single player cells and 2 for second player cells
            int energy[n][n];//stores energy sources

            int ii, jj;
            for(ii=0; ii<n; ii++){
                for(jj=0; jj<n; jj++){
                    table[ii][jj]=0;
                    energy[ii][jj]=0;
                    printf("*energy[%d][%d]=%d\n", ii, jj,energy[ii][jj]);
                }
            }
            int t, k;
            for(t=0; t<n; t++){
                for(k=0; k<n; k++){
                    fread(&map[t][k], sizeof(unsigned char), 1, fpp);
                    if(map[t][k]=='1'){
                        energy[t][k]=100;
                    }
                }
            }
            int i , j;
            for (i=0; i<n; i++){
                for(j=0; j<n; j++){
                    printf("map[%d][%d]= %c\n", i , j, map[i][j]);
                    printf("energy[%d][%d]= %d\n", i, j , energy[i][j]);
                }
            }
            head=NULL;
            get_cells(&head, map, table);
            print_arr(table);
            play_game(head, map, table, energy);

            break;
            }
            if(first_decide==3){
                fpp=fopen("D:\map.bin", "rb");
                fread(&n, sizeof(n), 1, fpp);
                printf("n=%ld\n", n);
                unsigned char map[n][n];
                int table[n][n];//store cells; 0 means that block is void of cells, 1 for single player cells and 2 for second player cells
                int energy[n][n];//stores energy sources

                int ii, jj;
                for(ii=0; ii<n; ii++){
                    for(jj=0; jj<n; jj++){
                        table[ii][jj]=0;
                        energy[ii][jj]=0;
                        printf("*energy[%d][%d]=%d\n", ii, jj,energy[ii][jj]);
                    }
                }
                int t, k;
                for(t=0; t<n; t++){
                    for(k=0; k<n; k++){
                        fread(&map[t][k], sizeof(unsigned char), 1, fpp);
                        if(map[t][k]=='1'){
                            energy[t][k]=100;
                        }
                    }
                }
                int i , j;
                for (i=0; i<n; i++){
                    for(j=0; j<n; j++){
                        printf("map[%d][%d]= %c\n", i , j, map[i][j]);
                        printf("energy[%d][%d]= %d\n", i, j , energy[i][j]);
                    }
                }
                head1=head2=NULL;
                printf("First player:\n");
                get_cells(&head1, map, table);
                print_arr(table);
                printf("Second player:\n");
                get_cells(&head2, map, table);
                print_arr(table);
                play_game(head1,map, table, energy);
                break;

            }
            if(first_decide==4){
                exit(0);
            }








    printf("\nx:%d and y:%d\n", x_choosed_cell, y_choosed_cell);
    cell*found=find_cell(head, x_choosed_cell, y_choosed_cell);
    printf("x found= %d y found=%d\n", found->x, found->y);
    ///move(map, table, head, x_choosed_cell, y_choosed_cell);
    //move_menu(map, table, head, x_choosed_cell, y_choosed_cell);
    ///print_arr(table);
    ///boost_energy(found, energy, map);
    printf("found energy is %d\n", found->energy);
    ///boost_energy(found, energy, map);

    //save(head, map);
    ///cell*loaded=load(map, energy);
    ///printf("* %s %d %d %d\n", loaded->name, loaded->x, loaded->y, loaded->energy);
    printf("cell_num= %d\n", cell_num);
    ///print_list(loaded);
    print_list(head);

    }
    return 0;
}
