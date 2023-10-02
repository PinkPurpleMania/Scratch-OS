#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "couche1.h"
#include <unistd.h>

//ecrire que le 1er oct libre pour les fichiers = taille superblock + taille tableau inode
int write_super_block(virtual_disk_t d, uint number_of_files, uint number_of_users, uint nb_blocks_used,uint first_free_byte){
    if(write_block(0, d, &number_of_files)!=0){
      printf("erreur 0 ecriture super bloc\n");
      return 1;
    }
    if(write_block(1, d, &number_of_users)!=0){
      printf("erreur 1 ecriture super bloc\n");
      return 2;
    }
    if(write_block(2, d, &nb_blocks_used)!=0){
      printf("erreur 2 ecriture super bloc\n");
      return 3;
    }
    if(write_block(3, d, &first_free_byte)!=0){
      printf("erreur 3 ecriture super bloc\n");
      return 4;
    }
  return 0;
}

int read_super_block(super_block_t super_block, virtual_disk_t d, void *p){
  for(int i=0;i<4;i++){
    if(read_block(i, d, p)!=0){
      printf("erreur %d lecture super bloc\n", i);
      return 1;
    }
  }
  return 0;
}

int change_first_free_byte(uint nb, virtual_disk_t d){
  uint new_free_bytes;
  if(read_block(3,d, &new_free_bytes)!=0){
    printf("erreur 3 lecture super bloc\n");
    return 1;
  }
  new_free_bytes=new_free_bytes+nb;
  if(write_block(3, d, &new_free_bytes)!=0){
    printf("erreur 3 ecriture super bloc\n");
    return 2;
  }
  return 0;
}

void read_inodes_table(virtual_disk_t d){
  //printf("cc");
  /*if(fseek(d->storage, 4, 0)!=0) {
    perror("erreur positionnement fichier");
    exit(1);
  }*/
//  if(fread(d->storage, sizeof(inode_table_t), 1, tab)!=0){
  //  printf("erreur lecture tab inode\n");
  //  return 2;
//  }
  for(int i=0; i<INODE_TABLE_SIZE;i++){
    d->inodes[i] = malloc(sizeof(inode_t));
    printf("filename %d [ %s ]\n",i,d->inodes[i]->filename);
  }
  //return *(d->inodes);
}

int write_inodes_table(virtual_disk_t d){
  if(fseek(d->storage, 16, 0)!=0) {
    perror("erreur positionnement fichier");
    exit(1);
  }
  if(fwrite(d->inodes, sizeof(inode_table_t), 1, d->storage)!=0){
    printf("erreur ecriture tab inode\n");
    return 1;
  }
  return 0;
}

void delete_inode(virtual_disk_t d, int indice ){
  free(d->inodes[indice]->filename);
  free(&(d->inodes[indice]->size));
  free(&(d->inodes[indice]->uid));
  free(&(d->inodes[indice]->uright));
  free(&(d->inodes[indice]->oright));
  free(d->inodes[indice]->ctimestamp);
  free(d->inodes[indice]->mtimestamp);
  free(&(d->inodes[indice]->nblock));
  free(&(d->inodes[indice]->first_byte));
  free(d->inodes[indice]);
  d->inodes[indice]=NULL;
}

uint get_unused_inode(virtual_disk_t d){
  uint nb;
  for(nb=0;nb<INODE_TABLE_SIZE;nb++)
    if(d->inodes[nb]==NULL) return nb;
  printf("erreur table inode complete\n");
  return 1;
}

void init_inode(char *nom, uint taille, uint pbyte, inode_t new_inode){
  char *t=timestamp();
  new_inode = malloc(sizeof(struct inode_s));
  for(int i=0; i<FILENAME_MAX_SIZE;i++){
    new_inode->filename[i] =nom[i];
  }
  new_inode->size = taille;
  for(int i=0; i<FILENAME_MAX_SIZE;i++){
    new_inode->ctimestamp[i] =t[i];
  }
  for(int i=0; i<FILENAME_MAX_SIZE;i++){
    new_inode->mtimestamp[i] =t[i];
  }
  new_inode->first_byte=pbyte;
}
