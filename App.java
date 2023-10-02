package essai;

import projet.System;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.BorderLayout;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.awt.event.ActionEvent;
import javax.swing.SwingConstants;
import javax.swing.JTextPane;
import javax.swing.JTextField;
import java.awt.Insets;
import java.awt.Component;
import java.awt.FlowLayout;
import javax.swing.JLabel;
import java.awt.Dimension;
import java.awt.Rectangle;

public class App {

	private JFrame frame;
	private JTextField designationFichier;
	private JTextField nbFichiers;
	private JTextField nbUtilisateurs;
	private JButton valideUsers;
	private JTextField nbBlocks;
	private JButton valideBlocks;
	private JTextField firstByte;
	private JButton valideByte;
	private JButton verif;
	private System s = new System();
	private String fichier;
	private String files;
	private int nbFiles;
	private String users;
	private int nbUsers;
	private String blocs;
	private int nbBlock;
	private String freeB;
	private int firstFreeByte;
	private JLabel saisieFichier;
	private JLabel lblSaisirNombreFichier;
	private JLabel lblSaisirNombreUsers;
	private JLabel lblSaisirNombreBlocks;
	private JLabel lblPremierOctetLibre;
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					App window = new App();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public App() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		BorderLayout borderLayout = (BorderLayout) frame.getContentPane().getLayout();
		borderLayout.setHgap(13);
		frame.setBounds(100, 100, 640, 395);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JPanel panel = new JPanel();
		FlowLayout flowLayout = (FlowLayout) panel.getLayout();
		flowLayout.setVgap(22);
		flowLayout.setHgap(125);
		frame.getContentPane().add(panel, BorderLayout.CENTER);
		
		saisieFichier = new JLabel("Nom Fichier");
		saisieFichier.setHorizontalTextPosition(SwingConstants.LEFT);
		saisieFichier.setHorizontalAlignment(SwingConstants.LEFT);
		saisieFichier.setPreferredSize(new Dimension(89, 22));
		saisieFichier.setMinimumSize(new Dimension(83, 17));
		saisieFichier.setBounds(new Rectangle(0, 0, 5, 3));
		saisieFichier.setMaximumSize(new Dimension(101, 31));
		panel.add(saisieFichier);
		
		designationFichier = new JTextField();
		panel.add(designationFichier);
		designationFichier.setColumns(10);
		
		JButton valideNomFich = new JButton("Valider");
		valideNomFich.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				fichier = designationFichier.getText();		
			}
		});
		panel.add(valideNomFich);
		
		lblSaisirNombreFichier = new JLabel("Nombre Fichier");
		lblSaisirNombreFichier.setPreferredSize(new Dimension(89, 22));
		lblSaisirNombreFichier.setMinimumSize(new Dimension(83, 17));
		lblSaisirNombreFichier.setMaximumSize(new Dimension(101, 31));
		lblSaisirNombreFichier.setHorizontalTextPosition(SwingConstants.LEFT);
		lblSaisirNombreFichier.setHorizontalAlignment(SwingConstants.LEFT);
		lblSaisirNombreFichier.setBounds(new Rectangle(0, 0, 5, 3));
		panel.add(lblSaisirNombreFichier);
		
		nbFichiers = new JTextField();
		panel.add(nbFichiers);
		nbFichiers.setColumns(10);
		
		JButton valideNbFich = new JButton("Valider");
		valideNbFich.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				files = nbFichiers.getText();
				nbFiles = Integer.parseInt(files);
			}
		});
		panel.add(valideNbFich);
		
		lblSaisirNombreUsers = new JLabel("Nombre users");
		lblSaisirNombreUsers.setPreferredSize(new Dimension(89, 22));
		lblSaisirNombreUsers.setMinimumSize(new Dimension(83, 17));
		lblSaisirNombreUsers.setMaximumSize(new Dimension(101, 31));
		lblSaisirNombreUsers.setHorizontalTextPosition(SwingConstants.LEFT);
		lblSaisirNombreUsers.setHorizontalAlignment(SwingConstants.LEFT);
		lblSaisirNombreUsers.setBounds(new Rectangle(0, 0, 5, 3));
		panel.add(lblSaisirNombreUsers);
		
		nbUtilisateurs = new JTextField();
		panel.add(nbUtilisateurs);
		nbUtilisateurs.setColumns(10);
		
		valideUsers = new JButton("Valider");
		valideUsers.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				users = nbUtilisateurs.getText();
				nbUsers = Integer.parseInt(users);
			}
		});
		panel.add(valideUsers);
		
		lblSaisirNombreBlocks = new JLabel("Nombre blocs");
		lblSaisirNombreBlocks.setPreferredSize(new Dimension(89, 22));
		lblSaisirNombreBlocks.setMinimumSize(new Dimension(83, 17));
		lblSaisirNombreBlocks.setMaximumSize(new Dimension(101, 31));
		lblSaisirNombreBlocks.setHorizontalTextPosition(SwingConstants.LEFT);
		lblSaisirNombreBlocks.setHorizontalAlignment(SwingConstants.LEFT);
		lblSaisirNombreBlocks.setBounds(new Rectangle(0, 0, 5, 3));
		panel.add(lblSaisirNombreBlocks);
		
		nbBlocks = new JTextField();
		panel.add(nbBlocks);
		nbBlocks.setColumns(10);
		
		valideBlocks = new JButton("Valider");
		valideBlocks.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				blocs = nbBlocks.getText();
				nbBlock = Integer.parseInt(blocs);
			}
		});
		panel.add(valideBlocks);
		
		lblPremierOctetLibre = new JLabel("Premier octet libre");
		lblPremierOctetLibre.setPreferredSize(new Dimension(89, 22));
		lblPremierOctetLibre.setMinimumSize(new Dimension(83, 17));
		lblPremierOctetLibre.setMaximumSize(new Dimension(101, 31));
		lblPremierOctetLibre.setHorizontalTextPosition(SwingConstants.LEFT);
		lblPremierOctetLibre.setHorizontalAlignment(SwingConstants.LEFT);
		lblPremierOctetLibre.setBounds(new Rectangle(0, 0, 5, 3));
		panel.add(lblPremierOctetLibre);
		
		firstByte = new JTextField();
		firstByte.setAlignmentY(Component.TOP_ALIGNMENT);
		firstByte.setAlignmentX(Component.RIGHT_ALIGNMENT);
		panel.add(firstByte);
		firstByte.setColumns(10);
		
		valideByte = new JButton("Valider");
		valideByte.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				freeB = firstByte.getText();
				firstFreeByte = Integer.parseInt(freeB);
			}
		});
		panel.add(valideByte);
		
		verif = new JButton("Lancer v\u00E9rification du syst\u00E8me");
		verif.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					s.verifSystem(fichier, nbFiles, nbUsers, nbBlock, firstFreeByte);
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		verif.setMargin(new Insets(6, 18, 6, 18));
		panel.add(verif);
		
	}

}
