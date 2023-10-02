#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "couche1.h"
#include <sys/types.h> /* types implémentés différemment selon la version d’Unix */
#include <sys/stat.h> /* constantes symboliques pour les droits d’accès */
#include <fcntl.h>

int write_file(virtual_disk_t d, char nom[], file_t new_file){
  char *t=timestamp();
  int i=0;
  uint nblock_new; //nb de blocks nouveau fichier

  if(((new_file->size+BLOCK_SIZE-1)%BLOCK_SIZE)==0){
    nblock_new = (new_file->size+BLOCK_SIZE-1)/BLOCK_SIZE;
  }
  else{
    nblock_new = ((new_file->size+BLOCK_SIZE-1)/BLOCK_SIZE)+1;
  }

  //vérifier si le fichier existe déjà
  while(strcmp(d->inodes[i]->filename,nom) && i<INODE_TABLE_SIZE){
    i++;
  }

 //s'il existe
  if((strcmp(d->inodes[i]->filename,nom)==0)){
    if(d->inodes[i]->size>=new_file->size){
      for(int j=0; j<FILENAME_MAX_SIZE;j++){ // mettre j a la place de i? philippine
        d->inodes[i]->filename[j] =nom[j];
      }
      //d->inodes[i]->filename =nom;
      d->inodes[i]->size = new_file->size;
      d->inodes[i]->nblock = nblock_new;
      for(int j=0; j<FILENAME_MAX_SIZE;j++){ // mettre j a la place de i? philippine
        d->inodes[i]->mtimestamp[j] =t[j];
      }
      return 0;
    }
    else{
      delete_inode(d,i); //supprimer inode existant
    }
  }

  i = INODE_TABLE_SIZE-1;
  //vérifier espace dispo
  while( i>=0 && !strcmp(d->inodes[i]->filename,"")){
    i--;
  }

  if(i >= INODE_TABLE_SIZE-1){
    fprintf(stderr,"plus d'espace disponible.\n");
    return 1;
  }
  int pbyte= read_super_block(d, &pbyte);
  inode_t new_inode = init_inode(nom, new_file->size, pbyte, new_inode);
  new_inode->nblock = nblock_new;
  d->inodes[i+1] = new_inode;
  d->inodes[i+1]->oright=0;
  printf("n %d\n", nblock_new);
  for(int j=0; j<nblock_new; j++){//ecriture des infos dans le fichier
   if(write_block((new_inode->first_byte)+j*4,d,((new_file->data)+j*4))){// ici :
      fprintf(stderr,"erreur écriture du bloc %d du fichier\n",j);
      return 2;
    }
  }
  printf("nouveau fichier : %s\n",d->inodes[i+1]->filename);
  return 0;
}


file_t read_file(char* nom_fichier, file_t fichier, virtual_disk_t d, session_t s){
  int i=0;
  printf("hello\n");
  printf("%s\n",d->inodes[i]->filename);
  while(strcmp(d->inodes[i]->filename,nom_fichier) && i<INODE_TABLE_SIZE){
    i++;
  }
  printf("i est %d\n", i);
  if(i>=INODE_TABLE_SIZE) {
    printf("fichier non trouvé\n");
    return NULL;
  }

  FILE *fich = fopen(nom_fichier,"r");
  if(fich == NULL){
    perror("erreur ouverture ficher\n");
    return NULL;
  }// juste pour que ça compile (philippine)

  if((strcmp(d->inodes[i]->filename,nom_fichier))==0){
    printf("ici\n");
    /*for(int j=0; j<d->inodes[i]->nblock; j++){//ecriture des infos dans le fichier
      printf("hey\n");
      if(fread(&(fichier->data[j+4]),4,1, fich)!=1){
        fprintf(stderr,"erreur écriture du bloc %d du fichier\n",j);
        return NULL;
      }*/
      printf(" nb est %d \n", d->inodes[i]->nblock);
      fread(fichier->data,4,d->inodes[i]->nblock, fich);
      printf(" data %s\n", fichier->data);
  }
  return fichier;
}

int delete_file(char* nom_fichier, virtual_disk_t d){
  int i=0;
  while(strcmp(d->inodes[i]->filename,nom_fichier) && i<INODE_TABLE_SIZE){
    i++;
  }
  printf("delete file\n");
  if(i>=INODE_TABLE_SIZE){
    fprintf(stderr,"erreur supprimer fichier non trouver\n");
    return 1;
  }
  int j = 0;
  while(j<d->inodes[i]->size){
    if(write_block(j+i, d, NULL)!=0){
      fprintf(stderr,"erreur supprimer block du fichier\n");
      return 2;
    }
    j+=4;
  }
  delete_inode(d,i);
//  free(d->inodes[i]); //supprimer inode correspondant au fichier
return 0;
}

file_t load_file_from_host( char *nom_fichier, virtual_disk_t d, session_t s){
  file_t file=malloc(sizeof(struct file_s));
  if(read_file(nom_fichier, file, d,s)!=0){
    fprintf(stderr,"erreur recherche ficher\n");
    return NULL;
  }
  if(write_file(d, nom_fichier, file)!=0){
    fprintf(stderr,"erreur écriture ficher\n");
    return NULL;
  }
return file;
}

int store_file_to_host( char *nom_fichier, virtual_disk_t d, void *p){
  int i=0;
  FILE * fichier_ordi;
  while(strcmp(d->inodes[i]->filename,nom_fichier) && i<INODE_TABLE_SIZE){
    i++;
  }
  if(i>=INODE_TABLE_SIZE) return 1;
  if((fichier_ordi=fopen(nom_fichier, "a+"))!=0){ // ici modif philippine
    fprintf(stderr,"erreur création fichier ficher\n");
    return 2;
  }
  for(int j=0; j<d->inodes[i]->nblock; j++){//ecriture des infos dans le fichier
  //  if(fwrite(&((d->inodes[i]->first_byte)+j*4),4, 1,fichier_ordi)){
      fprintf(stderr,"erreur écriture du bloc %d du fichier\n",j);
      return 3;
    //}
  }
  pclose(fichier_ordi);
return 0;
}
