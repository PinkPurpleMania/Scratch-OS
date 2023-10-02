#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "couche1.h"
#include <stddef.h>
#include <string.h>
#include <unistd.h>


int appel(char **tab, int nb, session_t s,virtual_disk_t d){
  inode_table_t ino_tab;
  //users_table_t users_tab;
  char p[255];
  file_t fichier = malloc(sizeof(file_t));
  printf("nb est %d\n", nb);
  if(strcmp(tab[0], "ls")==0){
    printf("dans ls\n");
    //read_inodes_table(d,&(ino_tab));
    printf("tab[1] = %s\n",tab[1]);
    if(strcmp(tab[1],"")){
      for(int i=0;i<INODE_TABLE_SIZE;i++){
        if(strcmp(d->inodes[i]->filename,"")) printf("%s %u %u %u %u %s %s %u %u\n",d->inodes[i]->filename, d->inodes[i]->size, d->inodes[i]->uid, d->inodes[i]->uright, d->inodes[i]->oright, d->inodes[i]->ctimestamp, d->inodes[i]->mtimestamp, d->inodes[i]->nblock, d->inodes[i]->first_byte);
      }
    }
    //traitement ls
    for(int i=0;i<INODE_TABLE_SIZE;i++){
        if(ino_tab[i]!=NULL) printf("%s %u\n",ino_tab[i]->filename, ino_tab[i]->size);
      }
  }
  if (strcmp(tab[0],"cat")==0){
    printf("on est dans cat\n");
    if(nb==2){
      //traitement cat
      int i;
      /*for( i=0;i<INODE_TABLE_SIZE && ino_tab[i]->filename!=tab[1] ;i++){
      }*/
      if(s.userid!=ROOT_UID){
        if(ino_tab[i]->uid==s.userid){
          if(ino_tab[i]->uright!=2 && ino_tab[i]->uright!=3){
            printf("erreur droit proprio\n");
            return(1);
          }
        }else{
          if(ino_tab[i]->oright!=2 && ino_tab[i]->oright!=3){
            printf("erreur droit proprio\n");
            return(2);
        }
        }
      }
      if((fichier=read_file(tab[1],fichier,d,s))==NULL){
        printf("erreur lecture fichier\n");
        return 666;
      }
      printf("%s\n",fichier->data);
      //execlp("cat","cat",tab[1], NULL);
    }
    else if(nb!=1){
      printf("erreur nombre d'arguments cat\n");
    }
    return(1);

  }
  if (strcmp(tab[0], "rm")==0){
    printf("dans rm\n");

    int i;
    if(strcmp(tab[1],"")){
      //traitement rm
      for( i=0;i<INODE_TABLE_SIZE && ino_tab[i]->filename!=tab[1] ;i++){
      }
      if(s.userid!=ROOT_UID){
        if(ino_tab[i]->uid==s.userid){
          if(ino_tab[i]->uright!=1 && ino_tab[i]->uright!=3){
            printf("erreur droit proprio\n");
            return(1);
          }
        }else{
          if(ino_tab[i]->oright!=1 && ino_tab[i]->oright!=3){
            printf("erreur droit proprio\n");
            return(2);
        }
        }
      }
      if(delete_file( tab[1], d)==0){
        printf("fichier effacer\n");
      }
      else{
        printf("erreur fichier non supprimer");
        return(2);
      }
    }
    printf("erreur nombre d'arguments rm\n");
    return(3);

  }
  if (strcmp(tab[0], "cr")==0){
    printf("dans cr\n");

    if(strcmp(tab[1],"")){
      //traitement cr
      load_file_from_host(tab[1], d, s);
      if(write_file(d,tab[1],fichier)==0){
        printf("fichier creer\n");
        return 0;
      }
      else{
        printf("erreur fichier non creer");
        return 4;
      }
    }
    printf("erreur nombre d'arguments cr\n");
    return(5);

  }
  if (strcmp(tab[0], "edit")==0){
    printf("dans edit\n");

    if(strcmp(tab[1],"")){
      int i;
      for( i=0;i<INODE_TABLE_SIZE && ino_tab[i]->filename!=tab[1] ;i++){
      }
      if(s.userid!=ROOT_UID){
        if(ino_tab[i]->uid==s.userid){
          if(ino_tab[i]->uright!=2 && ino_tab[i]->uright!=3){
            printf("erreur droit proprio\n");
            return(1);
          }
        }else{
          if(ino_tab[i]->oright!=2 && ino_tab[i]->oright!=3){
            printf("erreur droit proprio\n");
            return(2);
        }
        }
      }
      write_file(d,tab[1],fichier);
    }
    printf("erreur nombre d'arguments edit\n");
    return(5);
  }
  if (strcmp(tab[0], "load")==0){
    printf("dans load\n");

    if(strcmp(tab[1],"")){
      if(load_file_from_host(tab[1], d,s)!=0){
        printf("erreur load\n");
        return(3);
      }
    }
    printf("erreur nombre d'arguments load\n");
    return(5);
  }
  if (strcmp(tab[0],"store")==0){
    printf("dans store\n");

    if(strcmp(tab[1],"")){
      if(store_file_to_host(tab[1], d, p)!=0){
        printf("erreur load\n");
        return(3);
      }
    }
    printf("erreur nombre d'arguments store\n");
    return(5);
  }
  if (strcmp(tab[0], "chown")==0){
    printf("dans chown\n");

    if(strcmp(tab[1],"")){
      int i;
      for( i=0;i<INODE_TABLE_SIZE && ino_tab[i]->filename!=tab[1] ;i++){
      }
      if(s.userid!=ROOT_UID){
        if(ino_tab[i]->uid==s.userid){
          if(ino_tab[i]->uright!=2 && ino_tab[i]->uright!=3){
            printf("erreur droit proprio\n");
            return(1);
          }
        }else{
          if(ino_tab[i]->oright!=2 && ino_tab[i]->oright!=3){
            printf("erreur droit proprio\n");
            return(2);
        }
      }
    }
      char *t=timestamp();
      ino_tab[i]->uid=*tab[2];
      for(int j=0; j<TIMESTAMP_SIZE;j++){
        ino_tab[i]->mtimestamp[j] =t[j];
      }
    }
    printf("erreur nombre d'arguments chown\n");
    return(5);
  }
  if (strcmp(tab[0], "chmod")==0){
    printf("dans chmod\n");

    if(strcmp(tab[1],"")){
      int i;
      for( i=0;i<INODE_TABLE_SIZE && ino_tab[i]->filename!=tab[1] ;i++){
      }
      if(s.userid!=ROOT_UID){
        if(ino_tab[i]->uid==s.userid){
          if(ino_tab[i]->uright!=2 && ino_tab[i]->uright!=3){
            printf("erreur droit proprio\n");
            return(1);
          }
        }else{
          if(ino_tab[i]->oright!=2 && ino_tab[i]->oright!=3){
            printf("erreur droit proprio\n");
            return(2);
          }
        }
      }
        char *t=timestamp();
        ino_tab[i]->oright=*tab[2];
        for(int j=0; j<TIMESTAMP_SIZE;j++){
          ino_tab[i]->mtimestamp[j] =t[j];
        }
    }
    printf("erreur nombre d'arguments chmod\n");
    return(5);
    }
    if (strcmp(tab[0], "listusers")==0){
      printf(" dans list\n");

        for(int i=0;i<NB_USERS ;i++){
          printf("utilisateur %d est %s\n", i,d->users_table[i].login);
        }
    }
  if (strcmp(tab[0], "quit")==0){
    printf("dans quit\n");
    eteint(d);
      return 32;
  }

  if (strcmp(tab[0], "adduser")==0){ // ici c'est pas ouf
      printf("dans adduser\n");
      if(s.userid==ROOT_UID){
        char login[FILENAME_MAX_SIZE];
        char psswd[SHA256_BLOCK_SIZE*2 + 1];
        printf("saisir nom d'utilisateur : ");
        fgets(login,sizeof(login),stdin);
        printf("\nsaisir mot de passe : ");
        fgets(psswd,sizeof(psswd),stdin);
        user_t user;
        for(int i=0; i<FILENAME_MAX_SIZE; i++){
          user.login[i] = login[i];
        }
        for(int i=0; i<SHA256_BLOCK_SIZE*2+1; i++){
          user.passwd[i] = psswd[i];
        }
        if(insert_user(d,user)){
          printf("erreur utilisateur\n");
          return 7;
        }
      }
  }

  if (strcmp(tab[0], "rmuser")==0){
    printf("dans rmuser\n");
    printf("[%s] \n",tab[1]);
    if(strcmp(tab[1],"")!=0){
      for(int i=0;i<NB_USERS ;i++){
        if(strcmp(d->users_table[i].login,tab[1])==0){
          free(&d->users_table[i]);
        }
      }
    }
    printf("erreur nombre d'arguments rmusers\n");
    return(5);
  }
  return 0;
}

int main(int argc, char** argv){
  cmd_t cmd;
  cmd.tabArgs = malloc(4*sizeof(char**));
  for(int i=0; i<4; i++){
    cmd.tabArgs[i] = malloc(sizeof(char*));
  }
  char s[20];
  int userid= atoi(argv[2]);
  session_t session;
  session.userid = userid;
  virtual_disk_t d = malloc(sizeof(struct virtual_disk_s));
  init_disk_sos(argv[1],d);
  const char* separator=" ";
  while(true){
    int i=0;
    fgets(s,sizeof(s),stdin);
    cmd.nbArgs = 0;
    char*  mot = strtok(s, separator);
      while (mot != NULL ){
          strcpy(cmd.tabArgs[i],mot);
          mot = strtok(NULL, separator);
          (cmd.nbArgs)++;
          i++;
    }
      //printf("%d \n",cmd.nbArgs);
      //printf("%s \n",cmd.tabArgs[1]);
  //cmd.nbArgs=sizeof(cmd.tabArgs); mise en coms philippine
  if(appel(cmd.tabArgs, cmd.nbArgs, session,d)==32){
    return 1111;
  }
}
return 0;
}
