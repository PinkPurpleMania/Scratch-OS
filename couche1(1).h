#ifndef __DISQUE__
#define __DISQUE__

#define FILENAME_MAX_SIZE 32 // nb max de caractères des noms de fichiers
#define MAX_FILE_SIZE (2*1024) // taille max d'un fichier (uchar)
#define INODE_TABLE_SIZE 10 // taille fixe = nb max de fichiers dans le SE
#define MAX_MSG 1024 // uchar
#define TIMESTAMP_SIZE 24+2 // avec \0 et pour que ça tombe juste avec les blocs
#define NB_USERS 5
#define BLOCK_SIZE 4 // octets
#define SUPER_BLOCK_SIZE 4 // nb blocs
#define INODES_START SUPER_BLOCK_SIZE*BLOCK_SIZE+1 // en octets
#define INODE_SIZE FILENAME_MAX_SIZE/BLOCK_SIZE+6+(TIMESTAMP_SIZE*2)/BLOCK_SIZE
//= 27 en blocs = 8 blocs de filename+6 uint+timestamps
#define ROOT_UID 0
#define rw 0 // 00
#define rW 1 // 01
#define Rw 2 // 10
#define RW 3 // 11
#include "sha256.h"
#include "sha256_utils.h"

typedef unsigned int uint; // même taille que int
typedef unsigned char uchar; // 8 bits non signés = octet

/* Type of a block of data */
typedef struct block_s{
    uchar data[BLOCK_SIZE]; // une case par octet
} block_t;

// structure pour la table des utilisateurs
typedef struct user_s{
  char login[FILENAME_MAX_SIZE];
  char passwd[SHA256_BLOCK_SIZE*2 + 1]; // 64 hex char = haché du passwd
} user_t;

/* Type of the pseudo-inode structure */
typedef struct inode_s{
  // type file vs dir
  char filename[FILENAME_MAX_SIZE]; // dont '\0'
  uint size; // du fichier en octets
  uint uid; //user id proprio
  uint uright; //owner's rights between 0 and 3 coding rw in binary
  uint oright; // other's right idem
  char ctimestamp[TIMESTAMP_SIZE]; // date creation : 26 octets
  char mtimestamp[TIMESTAMP_SIZE]; // date dernière modif. : 26 octets
  uint nblock; // nblock du fichier = (size+BLOCK_SIZE-1)/BLOCK_SIZE ?
  uint first_byte; // number of the first byte on the virtual disk
} * inode_t;

/* Type of the inode table */
typedef inode_t inode_table_t[INODE_TABLE_SIZE];// la taille est fixe
typedef user_t users_table_t[NB_USERS]; // taille fixe. L'indice est l'uid.


// structure pour les fichiers
typedef struct file_s{
  uint size; // Size of file in bytes with pading ie compléter le dernier bloc avec des zéros
  uchar data [MAX_FILE_SIZE] ; // only text files
} *file_t ;

// pour gérer l'uid tout le long de la session
typedef struct session_s{
  int userid;
} session_t;


typedef struct super_block_s{
  uint number_of_files; // dans super bloc
  uint number_of_users; // idem
  uint nb_blocks_used ; //
  uint first_free_byte; // premier octet libre
  } super_block_t;

/* Type of the virtual disk system */
typedef struct virtual_disk_s {
    super_block_t super_block;
    users_table_t users_table; // tableau
    inode_table_t inodes;// tableau
    FILE *storage; //fichier vdisk du système de fichiers
} * virtual_disk_t;

// structure pour gérer les commandes de l'interprète
typedef struct cmd_s{
    char ** tabArgs; // tableau des arguments
    int nbArgs; // nombre d'arguments
} cmd_t;

// couche 1
void init_disk_sos(char* rep, virtual_disk_t disk);
void eteint(virtual_disk_t disk);
int compute_nblock(int n);
int write_block(int pos, virtual_disk_t disk, void *p);
int read_block(int pos,virtual_disk_t disk, void*p );
void print_bloc(block_t block);
// couche 2
int write_super_block(virtual_disk_t d, uint number_of_files, uint number_of_users, uint nb_blocks_used,uint first_free_byte);
int read_super_block(super_block_t super_block, virtual_disk_t d, void *p);
int change_first_free_byte(uint nb, virtual_disk_t d);
void read_inodes_table(virtual_disk_t d);
int write_inodes_table(virtual_disk_t d );
void delete_inode(virtual_disk_t d, int indice);
uint get_unused_inode(virtual_disk_t d);
void init_inode(char *nom, uint taille, uint pbyte, inode_t new_inode);
//couche 3
void init_tab_users(virtual_disk_t d);
int insert_user(virtual_disk_t d, user_t new_user);
//couche 4
int write_file(virtual_disk_t d, char *nom, file_t new_file);
file_t read_file(char* nom_fichier, file_t fichier, virtual_disk_t d, void*p, session_t s);
int delete_file(char* nom_fichier, virtual_disk_t d);
int load_file_from_host( char *nom_fichier, virtual_disk_t d, void *p, session_t s);
int store_file_to_host( char *nom_fichier, virtual_disk_t d,void*p);
// couche 5
int appel(char **tab, int nb, session_t s,virtual_disk_t d);
//time_
char *timestamp();

#endif
