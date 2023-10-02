package projet;
import java.io.*;

public class System {

	public System() {
	}
	
	//lis n octets du fichier
	private byte[] info(InputStream fluxFichier, int n) throws IOException {
		byte infos [] = new byte [Integer.parseInt("n")]; 
		if(fluxFichier.read(infos) <= 0) {
			java.lang.System.out.println("Erreur lecture fichier\n");
			return null;
		}
		return infos;
	}
	
	private int byteToInt(byte[] bytes, int size) {
		int n = 0;
		for(int i=0; i < size; i++) {
			n += bytes[i];
		}
		return n;
	}
	
	private String byteToString(byte[] bytes, int size){
		String s = "";
		for(int i=0; i < size; i++) {
			s += bytes[i];
		}
		return s;
	}
	
	public int verifSystem(String fichierDisque, int nb_files, int nb_users, int nb_block_used,int first_free_byte ) throws IOException {
		//ouverture du fichier
		File f = new File(fichierDisque);
		InputStream fluxFichier = new FileInputStream (f); 
		byte[] infos;
		
		//lecture du nb de fichiers du super_block
	    if((infos = info(fluxFichier,4)) == null) {
	    	return 1;
	    }
	    int nbFichiers = byteToInt(infos,4);
	    if(nbFichiers != nb_files) {
	    	java.lang.System.out.println("Nombre de fichiers incohérent\n");
	    }
	    
	    //lecture du nb de users du super_block
	    fluxFichier.skip(4); //se positionne sur le prochain entier à lire
	    if((infos = info(fluxFichier,4)) == null) {
	    	return 1;
	    }
	    int nbUsers = byteToInt(infos,4);
	    if(nbUsers != nb_users) {
	    	java.lang.System.out.println("Nombre d'utilisateurs incohérent\n");
	    }
	    
	    //lecture du nb_block du super_block
	    fluxFichier.skip(4); //se positionne sur le prochain entier à lire
	    if((infos = info(fluxFichier,4)) == null) {
	    	return 1;
	    }
	    int nbBlocks = byteToInt(infos,4);
	    if(nbBlocks != nb_block_used) {
	    	java.lang.System.out.println("Nombre de blocks utilisés incohérent\n");
	    }
	    
	    //lecture du first_free_byte du super_block
	    fluxFichier.skip(4); //se positionne sur le prochain entier à lire
	    if((infos = info(fluxFichier,4)) == null) {
	    	return 1;
	    }
	    int firstFreeB = byteToInt(infos,4);
	    if(firstFreeB != first_free_byte) {
	    	java.lang.System.out.println("Numero du premier octet libre incohérent\n");
	    }
	    
	    fluxFichier.skip(4); //saute la dernière info du super block
	    
	    //lecture premier inode
	    fluxFichier.skip(32); //saute le champs filename de l'inode
	    if((infos = info(fluxFichier,4)) == null) {
	    	return 1;
	    }
	    int size  = byteToInt(infos,4);	       
	    fluxFichier.skip(72); //se positionne sur le champs first_byte de l'inode
	    if((infos = info(fluxFichier,4)) == null) {
	    	return 1;
	    }
	    int firstByte = byteToInt(infos,4);   	    
	    int nextFile = firstByte + size; //calcule du premier octet du prochain fichier
	    fluxFichier.skip(4); //saute le champs first_byte pour passer au prochain inode
	    
	    for(int i=1; i < 10; i++) {
	    	fluxFichier.skip(32); //saute le champs filename de l'inode
	    	if((infos = info(fluxFichier,4)) == null) {
		    	return 1;
		    }
		    size  = byteToInt(infos,4);	       
		    fluxFichier.skip(72); 
		    if((infos = info(fluxFichier,4)) == null) {
		    	return 1;
		    }
		    firstByte = byteToInt(infos,4);
		    if(nextFile != size+firstByte) {
		    	java.lang.System.out.println("Erreur calcul du premier octet du fichier n°"+i+"\n");
		    }
		    nextFile = size+firstByte;
		    fluxFichier.skip(4); //passe au prochain inode
	    }
	    //TODO verifier le reste des infos ?
	    
	    
	    //vérifie la table des utilisateurs
	    if((infos = info(fluxFichier,32)) == null) {
	    	return 1;
	    }
	    String login = byteToString(infos, 32); //stocke le login de l'utilisateur 0    
	    if(!(login.equals("root"))) {
	    	java.lang.System.out.println("Erreur root user\n");
			return 1;
	    }	   
	    fluxFichier.close();
	    return 0;
	}
}
