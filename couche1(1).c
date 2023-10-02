#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "couche1.h"


void init_disk_sos(char* rep, virtual_disk_t disk){
  disk->storage=fopen(rep, "a");
  if(disk->storage==NULL){
    perror("probleme ouverture fichier");
  }
  //write_super_block(disk,0,0,0,0);
  read_inodes_table(disk);
  init_tab_users(disk);
}

void eteint(virtual_disk_t disk){
  if(fclose(disk->storage)!=0){
    perror("probleme fermeture fichier");
  }
}

int compute_nblock(int n){
  int nb_bloc=n/BLOCK_SIZE;
  if (nb_bloc%1!=0) nb_bloc++;
return nb_bloc;
}

int write_block(int pos, virtual_disk_t disk, void* p){
  int ret;
  if((ret=fseek(disk->storage, pos, 0))!=0) {
    perror("erreur positionnement fichier");
    return ret;
  }
  if((ret=fwrite(p, BLOCK_SIZE, 1, disk->storage))!=BLOCK_SIZE){
    perror("erreur ecriture");
    return ret;
  }
return 0;
}

int read_block(int pos,virtual_disk_t disk, void* p ){
  int ret;
  if((ret=fseek(disk->storage, pos, 0))!=0) {
    perror("erreur positionnement");
    return ret;
  }
  if((ret=fread(p, BLOCK_SIZE,1, disk->storage ))!=BLOCK_SIZE){
    perror("erreur lecture block");
    return ret;
  }
return 0;
}

void print_bloc(block_t block){
  for(int i=0; i<BLOCK_SIZE; i++){
    printf("%d", block.data[i] );
  }
printf("\n");
}
