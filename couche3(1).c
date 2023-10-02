#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "couche1.h"

void init_tab_users(virtual_disk_t d){
  user_t user_root;
  char ch[5]={'r','o','o','t','\0'};
  for(int i=0; i<5;i++){
  user_root.login[i] =ch[i];
  user_root.passwd[i] =ch[i];
  }
  users_table_t tab_user;
  tab_user[ROOT_UID]=user_root;
  for(int i=0; i<5;i++){
    d->users_table[i] = tab_user[i];
  }
}

int insert_user(virtual_disk_t d, user_t new_user){
  int pos_new_user=ROOT_UID+1;
  while(pos_new_user<NB_USERS && strcmp(d->users_table[pos_new_user].login,"")) pos_new_user++;
  if(pos_new_user==NB_USERS){
    fprintf(stderr, "Nombre d'utilisateurs maximum atteint\n");
    return 1;
  }
  d->users_table[pos_new_user]=new_user;
  return 0;
}
