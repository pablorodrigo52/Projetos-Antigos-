
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Pablo Rodrigo
 */
public final class TelaConsultas extends JFrame {
    
    GridBagLayout gridbag = new GridBagLayout();
    GridBagConstraints constraints = new GridBagConstraints();
    
    private JTable tabelaBotao1;
    private final DefaultTableModel modelo = new DefaultTableModel();
    
    public TelaConsultas (){
        super("Exercicio - Consultas");
        Botoes();
    }
    
    public void Botoes(){
        getContentPane().setLayout(gridbag);
        constraints.anchor = GridBagConstraints.CENTER;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.insets = new Insets(4, 4, 4, 4);
        
        constraints.gridy = 0;
        constraints.gridx = 0;
        JButton botao1 = new JButton("Primeira Consulta");
        botao1.addActionListener((ActionEvent e) -> {
            ActionsBotoesConsultas abc = new ActionsBotoesConsultas();
            try {
                abc.CriaTabela1();
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(TelaConsultas.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
        getContentPane().add(botao1, constraints);
        
        
        
        
        constraints.gridy = 0;  // linha
        constraints.gridx = 1; // coluna
        JButton botao2 = new JButton("Segunda Consulta");
        botao2.addActionListener((ActionEvent e) -> {
            ActionsBotoesConsultas abc = new ActionsBotoesConsultas();
            try {
                abc.CriaTabela2();
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(TelaConsultas.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
        getContentPane().add(botao2, constraints);
        
        
        
        
        constraints.gridy = 1;  // linha
        constraints.gridx = 0; // coluna
        JButton botao3 = new JButton("Terceira Consulta");
        botao3.addActionListener((ActionEvent e) -> {
            ActionsBotoesConsultas abc = new ActionsBotoesConsultas();
            try {
                abc.CriaTabela3();
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(TelaConsultas.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
        getContentPane().add(botao3, constraints);
        
        
        
        
        constraints.gridy = 1;  // linha
        constraints.gridx = 1; // coluna
        JButton botao4 = new JButton("Quarta Consulta");
        botao4.addActionListener((ActionEvent e) -> {
            ActionsBotoesConsultas abc = new ActionsBotoesConsultas();
            try {
                abc.CriaTabela4();
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(TelaConsultas.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
        getContentPane().add(botao4, constraints);
        
        
        
        constraints.gridy = 2;  // linha
        constraints.gridx = 0; // coluna
        JButton botao5 = new JButton("Quinta Consulta");
        botao5.addActionListener((ActionEvent e) -> {
            ActionsBotoesConsultas abc = new ActionsBotoesConsultas();
            try {
                abc.CriaTabela5();
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(TelaConsultas.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
        getContentPane().add(botao5, constraints);
        
        
        
        constraints.gridy = 2;  // linha
        constraints.gridx = 1; // coluna
        JButton botao6 = new JButton("Sexta Consulta");
        botao6.addActionListener((ActionEvent e) -> {
            ActionsBotoesConsultas abc = new ActionsBotoesConsultas();
            try {
                abc.CriaTabela6();
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(TelaConsultas.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
        getContentPane().add(botao6, constraints);
        
        
        
        constraints.gridy = 3;  // linha
        constraints.gridx = 0; // coluna
        JButton botao7 = new JButton("Sétima Consulta");
        botao7.addActionListener((ActionEvent e) -> {
            ActionsBotoesConsultas abc = new ActionsBotoesConsultas();
            try {
                abc.CriaTabela7();
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(TelaConsultas.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
        getContentPane().add(botao7, constraints);
        
        
        
        constraints.gridy = 3;  // linha
        constraints.gridx = 1; // coluna
        JButton botao8 = new JButton("Oitava Consulta");
        botao8.addActionListener((ActionEvent e) -> {
            ActionsBotoesConsultas abc = new ActionsBotoesConsultas();
            try {
                abc.CriaTabela8();
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(TelaConsultas.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
        getContentPane().add(botao8, constraints);
        
        
        
        constraints.gridy = 4;  // linha
        constraints.gridx = 0; // coluna
        JButton botao9 = new JButton("Nona Consulta");
        botao9.addActionListener((ActionEvent e) -> {
            ActionsBotoesConsultas abc = new ActionsBotoesConsultas();
            try {
                abc.CriaTabela9();
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(TelaConsultas.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
        getContentPane().add(botao9, constraints);
        
        
        
        constraints.gridy = 4;  // linha
        constraints.gridx = 1; // coluna
        JButton botao10 = new JButton("Décima Consulta");
        botao10.addActionListener((ActionEvent e) -> {
            ActionsBotoesConsultas abc = new ActionsBotoesConsultas();
            try {
                abc.CriaTabela10();
            } catch (ClassNotFoundException ex) {
                Logger.getLogger(TelaConsultas.class.getName()).log(Level.SEVERE, null, ex);
            }
        });
        getContentPane().add(botao10, constraints);
    }
}
